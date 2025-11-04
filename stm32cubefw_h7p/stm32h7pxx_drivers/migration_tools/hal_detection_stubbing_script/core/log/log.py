"""
/**
  *************************************************************************************************
  * @file    log.py
  * @brief   provides hal detection stubbing script log services
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

import sys
import os
import html
import re
from pathlib import Path
from typing import List

from hal_detection_stubbing_script.core.stub import stub_statement_extractor
import hal1_detection_config

from .templates import html_template
from .templates.html_template import  get_c_source_html_content,  get_code_with_line_numbers

sys.path.append(os.path.abspath(os.path.join(os.path.dirname(__file__), '....')))


warnings_config = [
                    hal1_detection_config.UseWarningMessageGenericMessage,
                    hal1_detection_config.UseWarningMessageLineNumber,
                    hal1_detection_config.UseWarningMessageAPIName,
                    hal1_detection_config.UseWarningMessageAPIType,
                    hal1_detection_config.UseWarningMessageAPILayer,
                    hal1_detection_config.UseWarningMessageAPIDriverFile
                ]

def init():
    """
    Initialize or reset global variables used for logging and message collection.

    This function sets the global lists `myLogList`, `src_file_names`, and `collected_messages`
    to empty lists, preparing them for a new logging session or clearing previous data.
    """
    global myLogList
    global src_file_names
    global collected_messages
    src_file_names = []
    myLogList = []
    collected_messages = []

def create_message(api_name, api_type, layer, driver_file, doc_link, lineo):
    """
    Create warning and log messages for a stubbed API, including compilation flags and formatted output.

    Args:
        api_name (str): Name of the API being stubbed.
        api_type (str): Type/category of the API.
        layer (str): Software layer where the API resides.
        driver_file (str): Name of the driver file containing the API.
        doc_link (str): Documentation link for the API.
        lineo (int): Line number in the source file where the API is located.

    Returns:
        tuple: A tuple containing:
            - msg_warning (str): The formatted warning message for code annotation.
            - msg_log (str): The formatted log message for logging purposes.
            - msg_begin (str): The #ifdef compilation flag line.
            - msg_end (str): The #endif compilation flag line.
    """
    stubbing_compilation_flag = hal1_detection_config.StubbingCompilationFlag
    separator = hal1_detection_config.StubbingWarningMessageSeparator
    separator_mid = " " + separator + " "

    stub_warning_msg = hal1_detection_config.StubbingWarningMessageGenericMessage

    msg_log_parts = [
        f'{lineo}',
        f'{api_name}',
        f'{api_type}',
        f'{layer}',
        f'{driver_file}',
        f'{doc_link}'
    ]
    msg_warning_parts = [
        f'{stub_warning_msg}',
        f'Line : {lineo}',
        f'API : {api_name}',
        f'API type : {api_type}',
        f'Layer : {layer}',
        f'Driver file : {driver_file} {separator}'
    ]
    allmessages = ['#warning "']
    for idx, el in enumerate(warnings_config):
        if el is True:
            allmessages.append(msg_warning_parts[idx])
    msg_warning = allmessages[0] + separator + " "
    msg_warning += separator_mid.join(allmessages[1:])
    msg_warning += '"'
    msg_log = format_row(msg_log_parts)
    msg_begin = f"#ifdef {stubbing_compilation_flag}"
    msg_end = f"#endif /* {stubbing_compilation_flag} */"
    return msg_warning, msg_log, msg_begin, msg_end

def add_msg_log(msg):
    """
    Add a log message to the global myLogList.

    Args:
        msg (str): The log message to append.
    """
    myLogList.append(msg)

def format_row(row):
    """
    Format a list of values into an HTML table row for logging purposes.

    The function expects a list with exactly 6 elements, corresponding to:
    [line number, API name, API type, layer, driver file, documentation link].
    The inclusion of certain columns is controlled by configuration flags.

    Args:
        row (list): A list of 6 elements representing log data.

    Returns:
        str: An HTML string representing a table row with the provided data.

    Raises:
        ValueError: If the input list does not have exactly 6 elements.
    """
    if len(row) != 6:
        raise ValueError("Row must have exactly 6 elements to format properly.")

    column_widths = [10, 20, 10, 10, 20, 10]

    cells = []
    if hal1_detection_config.UseLogFileLineNumber:
        cells.append(f'<td style="width: {column_widths[0]}%;">{row[0]}</td>')
    cells.append(f'<td style="width: {column_widths[1]}%;">{row[1]}</td>')
    if hal1_detection_config.UseLogFileAPIType:
        cells.append(f'<td style="width: {column_widths[2]}%;">{row[2]}</td>')
    if hal1_detection_config.UseLogFileAPILayer:
        cells.append(f'<td style="width: {column_widths[3]}%;">{row[3]}</td>')
    if hal1_detection_config.UseLogFileAPIDriverFile:
        cells.append(f'<td style="width: {column_widths[4]}%;">{row[4]}</td>')

    link_cell = f"""<td style="width: {column_widths[5]}%;"><a href="{row[5]}"
                    target="_blank" rel="noopener noreferrer">Link</a></td>
                """
    cells.append(link_cell)

    formatted_line = f"<tr>{''.join(cells)}</tr>"
    return formatted_line

def get_log_messages():
    """
    Retrieve the list of collected log messages.

    Returns:
        list: The global list of log messages (myLogList).
    """
    return myLogList

def insert_src_files(src_files):
    """
    Store the list of source file names in a formatted HTML string for later use.

    Args:
        src_files (list): List of source file names to be formatted and stored globally.
    """
    global src_file_names
    src_file_names = ["<br><p></p><p> - Applicative file name : "+str(filename)+" </p>" for filename in src_files]

def create_file_messages_sections(path_log_html):
    """
    Generate HTML sections for each file's log messages.

    Args:
        path_log_html (str): The path to the main HTML log file.

    Returns:
        str: HTML content containing sections for each file's log messages.
    """
    output = ""
    for log_msg in collected_messages:

        file_path_log_html = path_log_html[:-5] + '/' + log_msg[0].replace('.','_') + ".html"
        log_msg_title = f"File: <a href= \"{file_path_log_html}\">{log_msg[0]}</a>"

        if log_msg[1] != "":
            output += ( html_template.TABLE_HEADER_LEFT.format(log_msg_title=log_msg_title)
                        + log_msg[1] + '\n'+ html_template.TABLE_HEADER_RIGHT
            )
        else:
            output += f"""
                <div style="border: 1px solid #03234b; padding: 10px; margin: 20px auto; width: 98%; text-align: left;">
                    <p style="font-weight: bold; font-size: 14px; margin-left: 10px;">{log_msg_title}</p>
                    <p style="margin-left: 10px;">Nothing to be stubbed in this file.</p>
                </div>
            """
    return output

def wrap_log_messages(log_message):
    """
    Append a log message to the global collected_messages list.

    Args:
        log_message (tuple): The log message to append, typically containing file name and message content.
    """
    collected_messages.append(log_message)

def write_html_file(path_log_html):
    """
    Write the complete HTML log file using the collected messages and HTML templates.

    Args:
        path_log_html (str): The path where the HTML log file will be written.
    """
    html_content =  (
                html_template.HTML_HEADER_LEFT
                + create_file_messages_sections(path_log_html)
                + html_template.HTML_HEADER_RIGHT
    )
    with open(path_log_html, "w", encoding= "utf-8") as html_file:
        html_file.write(html_content)

def save_c_source_html(
    content: str,
    src_file: str,
    log_dir: str,
    log_html_folder_name: str,
    statements : List[stub_statement_extractor.Statement]
) -> Path:
    """
    Highlights C source code and saves it as an HTML file in the specified log directory.

    Args:
        content (str): The C source code to highlight.
        src_file (str): The path to the source file (used for naming).
        log_dir (str): The base directory for logs.
        log_html_folder_name (str): The subfolder name for HTML logs.

    Returns:
        Path: The path to the generated HTML file.
    """
    log_html_folder_path = os.path.join(log_dir, log_html_folder_name)
    if not os.path.exists(log_html_folder_path):
        os.makedirs(log_html_folder_path, exist_ok=True)

    src_path = Path(src_file)
    log_dir_path = Path(log_html_folder_path)

    # Replace '.' with '_' in the file name (excluding extension)
    file_base_name = src_path.name.replace('.', '_')
    html_file_name = file_base_name + '.html'
    html_dest_path = log_dir_path / html_file_name

    content =  html.escape(content)
    content = replace_identifiers_in_html(content, statements)

    lines = content.splitlines()
    # Generate HTML table rows with line numbers
    code_with_line_numbers = ""
    for idx, line in enumerate(lines, 1):
        code_with_line_numbers += get_code_with_line_numbers(idx, line)
    # Create HTML content
    html_content  = get_c_source_html_content(html_file_name, code_with_line_numbers)

    with open(html_dest_path, 'w', encoding="utf-8") as htm_file:
        htm_file.write(html_content)

    return html_dest_path

def is_inside_a_tag(line, match_start):
    """
    Returns True if the match_start index is inside an <a ...>...</a> block in the line.
    """
    for m in re.finditer(r'<a\b[^>]*>.*?</a>', line, re.IGNORECASE | re.DOTALL):
        if m.start() <= match_start < m.end():
            return True
    return False

def replace_identifiers_in_html(html_content, statements):
    """
    Replace identifiers in HTML with links, only for lines between start_line and end_line,
    and only for identifiers where for_stub is True and link is not None.
    Only the first occurrence per line is replaced, and never inside <a>...</a> blocks.
    """
    html_lines = html_content.splitlines(keepends=True)

    def process_statement(stmt, html_lines):
        for ident in getattr(stmt, 'identifiers_for_stub', []):
            if ident.get('for_stub') and ident.get('link'):
                value = ident['value']
                link = ident['link']
                hal_api_type = html.escape(ident['hal_api_type'])
                module = html.escape(ident['module'])
                layer = html.escape(ident['layer'])
                # Escape for HTML safety
                hal_api = html.escape(value)
                api_link = html.escape(link)
                pattern = re.compile(rf'\b{re.escape(value)}\b')
                data_api = (
                    f'<strong>HAL1 api name:</strong> {hal_api}',
                    f'<strong>HAL1 api type:</strong> {hal_api_type}',
                    f'<strong>Layer:</strong> {layer}',
                    f'<strong>Module:</strong> {module}',
                )
                data_api_str = '<br>'.join(data_api)
                safe_data_api = html.escape(data_api_str)
                replacement = (
                    f'<a href="{api_link}" class="hal-api-link" data-api="{safe_data_api}">{hal_api}</a>'
                )
                # Only process lines in the specified range
                if getattr(stmt, "origin_position", None) is not None:
                    pos = stmt.origin_position
                    start_line = pos.line_start
                    end_line = pos.line_end
                else:
                    start_line = stmt.start_line
                    end_line = stmt.end_line
                for i in range(start_line - 1, end_line):
                    line = html_lines[i]
                    for m in pattern.finditer(line):
                        if not is_inside_a_tag(line, m.start()):
                            new_line = (
                                line[:m.start()] +
                                replacement +
                                line[m.end():]
                            )
                            html_lines[i] = new_line
        # Recursively process children
        for child in getattr(stmt, 'children', []):
            html_lines = process_statement(child, html_lines)
        return html_lines

    for stmt in statements:
        html_lines = process_statement(stmt, html_lines)
    return ''.join(html_lines)
