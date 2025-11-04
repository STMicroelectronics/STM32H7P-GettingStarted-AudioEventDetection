"""
/**
  *************************************************************************************************
  * @file    services.py
  * @brief   Provides HAL1 detection script common services
  *************************************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file in the root
  * directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  *************************************************************************************************
  */
"""

import os
import re
import sys
import csv
import logging
from typing import List, Dict, Any, Optional
from concurrent.futures import ThreadPoolExecutor, as_completed

import pandas as pd

from hal_detection_stubbing_script.core.log.log_messages import warning_log_messages, console_log_messages


def find_column(content: str, token: Any) -> int:
    """
    Find the column number of a token in the content.
    """
    last_cr = content.rfind('\n', 0, token.lexpos)
    if last_cr < 0:
        last_cr = -1
    return token.lexpos - last_cr


def extract_identifiers_tokens(tokens: List[Any]) -> List[str]:
    """
    Extracts identifier values from a list of tokens.
    """
    return [tok.value for tok in tokens if getattr(tok, 'type', None) == 'IDENTIFIER']


def remove_duplicates(identifiers_list: List[str]) -> pd.DataFrame:
    """
    Removes duplicate identifiers and returns a DataFrame.
    """
    ids_df = pd.DataFrame(identifiers_list, columns=['api'])
    return ids_df.drop_duplicates(subset=['api'])


def tokens_to_dicts(
    content: str,
    tokens: List[Any],
    ids_data_frame_list: List[pd.DataFrame]
) -> List[Dict[str, Any]]:
    """
    Converts tokens to enriched dictionaries with metadata from DataFrames.
    """
    db_data_frame = pd.concat(ids_data_frame_list, ignore_index=True).drop_duplicates(subset=['api'])
    db_data_frame_dict = db_data_frame.set_index('api').to_dict(orient='index')

    result = []
    for token in tokens:
        row = db_data_frame_dict.get(token.value)
        result.append({
            "module": row.get('module') if row else None,
            "layer": row.get('layer') if row else None,
            "value": token.value,
            "type": token.type,
            "file": row.get('file') if row else None,
            "link": row.get('link') if row else None,
            "line": token.lineno,
            "position": token.lexpos,
            "column": find_column(content, token),
            "for_stub": bool(row),
            "hal_api_type": row.get('type') if row else None,
            "variable_type": None
        })
    return result


def add_stub_file_comment(
    content: str,
    text: str = warning_log_messages["STUBBED_HEADER_MESSAGE"],
    border_char: str = warning_log_messages["STUBBED_HEADER_BORDER_CHAR"],
    comment_length: int = 120
) -> str:
    """
    Adds a stub file comment header to the content.
    """
    border_length = (comment_length - len(text) - 4) // 2
    comment = f"/*{border_char * border_length} {text} {border_char * border_length}*/"
    return f"{comment}\n{content}"


def get_src_files(
    src_folder: str,
    excluded_drivers: List[str],
    patterns: List[str],
    special_files: List[str]
) -> List[str]:
    """
    Find the list of source files under the source folder, excluding certain patterns and files.
    """
    list_files = []
    for dirpath, _, filenames in os.walk(src_folder):
        for filename in filenames:
            if not re.match(r".*\.(c|h)$", filename):
                continue
            file_excluded = False
            for pattern in patterns:
                if (
                    re.match(pattern, filename) or filename in excluded_drivers
                ) and filename not in special_files:
                    file_excluded = True
                    break
            if not file_excluded:
                list_files.append(os.path.join(dirpath, filename))
    return sort_by_extension(list_files)


def sort_by_extension(file_list: List[str]) -> List[str]:
    """
    Sorts files by extension: header files (.h) first, then source files (.c).
    """
    return sorted(file_list, key=lambda x: (0 if x.endswith('.h') else 1, x))


def filter_used_hal_apis(
    db_data_frame_list: List[pd.DataFrame],
    ids_data_frame: pd.DataFrame
) -> List[pd.DataFrame]:
    """
    Filters used HAL1 APIs by performing an inner join for each DataFrame in the list.
    """
    return [
        pd.merge(df, ids_data_frame, on='api', how='inner')
        for df in db_data_frame_list
    ]


def load_csv(file_path: str, doc_path: str) -> pd.DataFrame:
    """
    Helper function to load a CSV file and prepend doc_path to the 'link' column.
    """
    try:
        df = pd.read_csv(file_path)
        if 'link' in df.columns:
            df['link'] = doc_path + df['link']
        if df.isnull().any().any():
            logging.warning("Empty values in the database: %s", file_path)
            return pd.DataFrame()
        return df
    except pd.errors.EmptyDataError:
        logging.warning('%s %s', console_log_messages["EMPTY_CSV_FILE"], file_path)
    except FileNotFoundError:
        logging.error('%s %s', console_log_messages["DATABASE_NOT_FOUND"], file_path)
    except (OSError, pd.errors.ParserError) as e:
        logging.error("%s: %s", file_path, e)

    return pd.DataFrame()

def load_stub_csv(
    db_names: List[str],
    modules: Optional[List[str]],
    doc_path: str
) -> List[pd.DataFrame]:
    """
    Load model data from multiple CSV files using multithreading.

    Args:
        db_names (list): List of database CSV file names.
        modules (list): List of module names to filter, or None.
        doc_path (str): Path to the document directory.

    Returns:
        list: A list of DataFrames corresponding to the order of db_names.
    """
    file_paths = [
        os.path.join('hal_detection_stubbing_script', 'db', f'{db_name}.csv')
        for db_name in db_names
    ]
    dataframes = {db_name: pd.DataFrame() for db_name in db_names}

    # Check if all required files exist
    missing_files = [file_path for file_path in file_paths if not os.path.exists(file_path)]
    if missing_files:
        for missing_file in missing_files:
            logging.error('%s %s', console_log_messages["DATABASE_NOT_FOUND"], missing_file)
        sys.exit(1)

    with ThreadPoolExecutor(max_workers=8) as executor:
        future_to_file = {
            executor.submit(load_csv, file_path, doc_path): file_path
            for file_path in file_paths
        }
        for future in as_completed(future_to_file):
            file_path = future_to_file[future]
            try:
                df = future.result()
                if not df.empty:
                    db_name = os.path.basename(file_path).replace('.csv', '')
                    if modules is not None and 'module' in df.columns:
                        df = df[df['module'].isin(modules)]
                    dataframes[db_name] = df
            except (pd.errors.ParserError, OSError, ValueError) as e:
                logging.error("Error processing file %s: %s", file_path, e)

    return [dataframes[db_name] for db_name in db_names]


def read_modules_from_csv(file_path: str) -> List[str]:
    """
    Reads a CSV file containing module names and returns them as a list.
    """
    modules = []
    try:
        with open(file_path, mode='r', newline='', encoding='utf-8') as csvfile:
            reader = csv.reader(csvfile)
            for row in reader:
                modules.extend(row)
        return modules
    except FileNotFoundError:
        logging.error('%s %s', console_log_messages["MODULES_NOT_FOUND"], file_path)
    except (OSError, csv.Error) as e:
        logging.error("An error occurred while reading %s: %s", file_path, e)
    return modules
