"""
/**
  *************************************************************************************************
  * @file    sequencer.py
  * @brief   provides hal1 detection script sequencer services
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
import sys
import logging
from typing import List, Tuple, Any
from pathlib import Path
from itertools import chain
from concurrent.futures import ThreadPoolExecutor, as_completed

from tqdm import tqdm

from hal_detection_stubbing_script.core import services
from hal_detection_stubbing_script.core.stub import stub_lexer
from hal_detection_stubbing_script.core.log import log
from hal_detection_stubbing_script.core.stub import stub_statement_extractor
from hal_detection_stubbing_script.core.stub.stub_message_generator import StubMessages
from hal_detection_stubbing_script.core.log.log_messages import console_log_messages, warning_log_messages
from hal_detection_stubbing_script.core.migration_core import LOG_DIR, LOG_HTML_FOLDER_NAME
from hal1_detection_config import UseWarningMessage

root_dir = os.path.abspath(os.path.dirname(__file__))
sys.path.append(root_dir)



logging.basicConfig(
    level=logging.INFO,
    format='%(message)s'
)
logger = logging.getLogger(__name__)

def process_file(src_file: str, db_data_frame_list: list, dryrun: bool, use_warning_message: bool) -> bool:
    """
    Processes a single source file for HAL stubbing.

    Steps:
        1. Checks if the file is already stubbed.
        2. Reads the file content.
        3. Tokenizes the content.
        4. Extracts and filters identifiers using the provided database.
        5. Processes statements for stubbing.
        6. Collects, sorts, and inserts block messages.
        7. Optionally writes the updated content back to the file.
        8. Logs the processing results.

    Args:
        src_file (str): Path to the source file to process.
        db_data_frame_list (list): List of data frames for HAL1 API filtering.
        dryrun (bool): If True, do not write changes to the file.
        use_warning_message (bool): If True, include warning messages in output.

    Returns:
        bool: True if the file was stubbed, False otherwise.
    """
    try:
        with open(src_file, "r+", encoding="utf-8") as f:
            if is_already_stubbed(f, src_file):
                return False

            content, origin_content = read_file_content(f)
            tokens = get_tokens(content)
            ids_data_frame_list = get_filtered_identifiers(tokens, db_data_frame_list)

            if not all(df.empty for df in ids_data_frame_list):
                content, statements = process_statements(content, tokens, ids_data_frame_list)
                sorted_messages = get_sorted_messages(statements, use_warning_message)
                content = insert_stubbing_messages(content, sorted_messages)

                if not dryrun:
                    content = services.add_stub_file_comment(content)
                    write_file_content(f, content)

                log.save_c_source_html(origin_content, src_file, LOG_DIR, LOG_HTML_FOLDER_NAME, statements)
                log_and_wrap(src_file)
                return True

    except FileNotFoundError as fnf_error:
        logger.error(console_log_messages["ERROR_PROCESSING_FILE"], fnf_error)
    except IOError as io_error:
        logger.error(console_log_messages["IO_ERROR"], str(io_error))
    except Exception as e:
        logger.error("Unexpected error processing %s: %s", src_file, e)
        raise
    return False

def is_already_stubbed(f, src_file) -> bool:
    """
    Checks if the file is already stubbed by inspecting the first line.

    Args:
        f: Opened file object.
        src_file (str): Path to the source file.

    Returns:
        bool: True if the file is already stubbed, False otherwise.
    """
    first_line = f.readline().strip()
    if warning_log_messages["STUBBED_HEADER_MESSAGE"] in first_line:
        logger.warning('\n\033[93m{"%s"} %s\033[0m', Path(src_file).name, console_log_messages["STUBBED_FILE"])
        return True
    f.seek(0)
    return False

def read_file_content(f) -> tuple:
    """
    Reads the entire content of the file.

    Args:
        f: Opened file object.

    Returns:
        tuple: (content, original_content)
    """
    content = f.read()
    return content, content

def get_tokens(content: str) -> list:
    """
    Tokenizes the file content using the stub lexer.

    Args:
        content (str): The file content.

    Returns:
        list: List of tokens.
    """
    lexer = stub_lexer.StubLexer(c_version='c23')
    lexer.lexer.input(content)
    return list(lexer.lexer)

def get_filtered_identifiers(tokens: list, db_data_frame_list: list) -> list:
    """
    Extracts identifiers from tokens and filters them using the provided database.

    Args:
        tokens (list): List of tokens.
        db_data_frame_list (list): List of data frames for filtering.

    Returns:
        list: Filtered data frames of identifiers.
    """
    identifiers_list = services.extract_identifiers_tokens(tokens)
    ids_data_frame = services.remove_duplicates(identifiers_list)
    return services.filter_used_hal_apis(db_data_frame_list, ids_data_frame)

def process_statements(content: str, tokens: list, ids_data_frame_list: list) -> tuple:
    """
    Processes statements for stubbing and updates the content if needed.

    Args:
        content (str): The file content.
        tokens (list): List of tokens.
        ids_data_frame_list (list): Filtered data frames of identifiers.

    Returns:
        tuple: (updated_content, statements)
    """
    tokens_dict = services.tokens_to_dicts(content, tokens, ids_data_frame_list)
    statements = stub_statement_extractor.StatementExtractor(tokens_dict).extract()
    if stub_statement_extractor.count_insert_lines(statements) > 0:
        positions = stub_statement_extractor.extract_insert_positions(statements)
        stub_statement_extractor.increment_lines_for_insertions(statements)
        content = stub_statement_extractor.split_lines_at_positions(content, positions)
    return content, statements

def get_sorted_messages(statements: list, use_warning_message: bool) -> list:
    """
    Collects, filters, and sorts block messages from statements.

    Args:
        statements (list): List of statement objects.
        use_warning_message (bool): Whether to include warning messages.

    Returns:
        list: Sorted messages for insertion.
    """
    stub_messages_list = list(
        chain.from_iterable(
            StubMessages.construct_from_statement(stmt)
            for stmt in statements
        )
    )
    stub_messages_list = filter_blocks(stub_messages_list, 'is_struct')
    stub_messages_list = filter_blocks(stub_messages_list, 'is_chain')
    return collect_and_sort_messages(stub_messages_list, use_warning_message)

def write_file_content(f, content: str) -> None:
    """
    Writes the updated content back to the file.

    Args:
        f: Opened file object.
        content (str): The content to write.
    """
    f.seek(0)
    f.write(content)
    f.truncate()

def log_and_wrap(src_file: str) -> None:
    """
    Collects log messages and wraps them for the processed file.

    Args:
        src_file (str): Path to the source file.
    """
    file_logs = log.get_log_messages()
    processed_file_log = "".join(file_logs)
    log.wrap_log_messages((Path(src_file).name, processed_file_log))
    log.myLogList = []

def apply_stubbing(src_files, modules, dryrun):
    """
    Apply the stubbing process to a list of source files in parallel.
    Display progress and summary information.
    """

    stubbed_files = 0
    logger.info('%s',console_log_messages["START_HAL_AUTOMATIC_SCRIPT"])
    logger.info('%s %d',console_log_messages["STUB_APP_FILES_NBR"],len(src_files))

    doc_path = (
        "file:///"
        + Path.cwd().as_posix()
        + "/hal_migration_guide/docs/markup/drivers_documentation"
        )
    # for on-line documentation
    # doc_path = (
    #     "http://localhost:8000"
    #     # + Path.cwd().as_posix()
    #     + "/docs/markup/drivers_documentation"
    #     )

    db_file_list = ["functions_macros","structures_enumerations", "constants_enumerators"]
    db_data_frame_list = services.load_stub_csv(db_file_list, modules, doc_path)

    # Use ThreadPoolExecutor to process files in parallel
    with ThreadPoolExecutor(max_workers = 1) as executor:
        futures = {
                    executor.submit(
                                    process_file,
                                    src_file,db_data_frame_list,
                                    dryrun,
                                    UseWarningMessage
                                    ): src_file for src_file in src_files
                  }
        # Display the overall progress bar at the end
        for future in tqdm(
                            as_completed(futures),
                            total=len(src_files),
                            desc=console_log_messages["STUB_PROGRESS_MSG"],
                            unit="file",
                            ncols=150,
                            leave=True,
                            bar_format='{l_bar}{bar}| {n_fmt}/{total_fmt}',
                        ):

                # result = future.result()
            try:
                # Retrieve the result of the completed future (if needed)
                result = future.result()
                if result is True:
                    stubbed_files += 1
            except Exception as e:
                logger.error('%s %s %s',console_log_messages["ERROR_PROCESSING_FILE"],futures[future], e )
                raise

    logger.info('%s %d',console_log_messages["STUBBED_APP_FILES_NBR"],stubbed_files)


def filter_blocks(stub_messages_list: List[Any], block_flag: str) -> List[Any]:
    """
    Groups consecutive messages with the specified block_flag into a single block,
    aggregating their warning messages.
    """
    filtered_list = []
    block = None
    all_warnings = []

    for message in stub_messages_list:
        is_block = getattr(message, block_flag, False)
        if is_block:
            if block is None:
                # Initialize a new block
                block = StubMessages(
                    start_stub_line=message.start_stub_line,
                    end_stub_line=message.end_stub_line,
                    warnings_messages="",  # Will be set later
                    msg_stub_begin=message.msg_stub_begin,
                    msg_stub_end=message.msg_stub_end,
                    **{block_flag: True}
                )
                all_warnings = []

            # Collect warnings
            warnings = message.warnings_messages
            if isinstance(warnings, list):
                all_warnings.extend(warnings)
            elif warnings:
                all_warnings.append(warnings)

            # Update block's end line and end message
            block.end_stub_line = message.end_stub_line
            block.msg_stub_end = message.msg_stub_end

        else:
            if block is not None:
                # Finalize and append the current block
                block.warnings_messages = "\n".join(all_warnings)
                filtered_list.append(block)
                block = None
                all_warnings = []

            filtered_list.append(message)

    # Append any remaining block at the end
    if block is not None:
        block.warnings_messages = "\n".join(all_warnings)
        filtered_list.append(block)

    return filtered_list


def insert_stubbing_messages(content, sorted_messages):
    """
    Inserts stubbing messages into the file content at specified positions.
    Returns the updated file content as a string.
    """
    lines = content.split("\n")
    for line_no, text in sorted_messages:
        if 0 <= line_no <= len(lines):
            lines.insert(line_no, text)
        else:
            pass
    return  '\n'.join(lines)



def collect_and_sort_messages(stub_messages_list: List[Any], use_warning_message: bool) -> List[Tuple[int, str]]:
    """
    Collects and sorts begin and end messages from stub_messages_list by line number in descending order.

    Args:
        stub_messages_list: List of message objects with start_stub_line, end_stub_line, warnings_messages,
        msg_stub_begin, msg_stub_end.
        use_warning_message: Whether to include warning messages in the output.

    Returns:
        A list of tuples (line_number, message), sorted in descending order by line_number.
    """
    begin_msgs = [
        (
            msg.start_stub_line,
            ("".join(msg.warnings_messages) + "\n" if use_warning_message else "") + msg.msg_stub_begin
        )
        for msg in stub_messages_list
    ]
    end_msgs = [
        (msg.end_stub_line, msg.msg_stub_end) for msg in stub_messages_list
    ]
    collected_messages = begin_msgs + end_msgs

    # Sort in descending order by line number
    sorted_messages = sorted(collected_messages, key=lambda x: x[0], reverse=True)

    return sorted_messages
