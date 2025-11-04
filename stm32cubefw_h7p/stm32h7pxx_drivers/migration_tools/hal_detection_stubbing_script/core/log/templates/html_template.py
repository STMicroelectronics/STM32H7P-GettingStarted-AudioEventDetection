"""
/**
  *************************************************************************************************
  * @file    html_template.py
  * @brief   provides hal detection stubbing script log file template
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
from pathlib import Path
from hal_detection_stubbing_script.core.log.log_messages import log_file_messages
from hal1_detection_config import (
    UseLogFileLineNumber,
    UseLogFileAPIType,
    UseLogFileAPILayer,
    UseLogFileAPIDriverFile,
)

images_path = Path(__file__).parents[4]
logo_path = os.path.join(images_path, '_htmresc', 'st_logo_2020.png')

HTML_HEADER_LEFT = f"""<!DOCTYPE html>
<html lang="en">
<head>
    <title>{log_file_messages["HTML_FILE_TITLE"]}</title>
    <style>
        :root {{
            --fore-color: #03234b;
            --secondary-fore-color: #03234b;
            --back-color: #ffffff;
            --secondary-back-color: #ffffff;
            --blockquote-color: #e6007e;
            --pre-color: #e6007e;
            --border-color: #3cb4e6;
            --secondary-border-color: #3cb4e6;
            --heading-ratio: 1.2;
            --universal-margin: 0.5rem;
            --universal-padding: 0.25rem;
            --universal-border-radius: 0.075rem;
            --background-margin: 1.5%;
            --a-link-color: #3cb4e6;
            --a-visited-color: #8c0078;
            --table-border-color: #03234b;
            --table-border-separator-color: #03234b;
            --table-head-back-color: #03234b;
            --table-head-fore-color: #ffffff;
            --table-body-back-color: #ffffff;
            --table-body-fore-color: #03234b;
            --table-body-alt-back-color: #f4f4f4;
        }}

        body {{
            margin-left: 2%;
            background: white linear-gradient(#ffd200, #ffd200) repeat-y left top;
            background-size: 1.5%;
            color: var(--fore-color);
            font-family: -apple-system, BlinkMacSystemFont, Helvetica, arial, sans-serif;
            line-height: 1.25;
            font-size: 13.5px;
        }}

        table {{
            border-collapse: separate;
            border-spacing: 0;
            margin: 0;
            flex-flow: row wrap;
            padding-top: 0;
            width: 96%;
        }}

        table, th, td {{
            border: 1px solid var(--table-border-color);
        }}

        th {{
            background-color: var(--table-head-back-color);
            color: var(--table-head-fore-color);
            padding: var(--universal-padding);
        }}

        td {{
            background-color: var(--table-body-back-color);
            color: var(--table-body-fore-color);
            padding: var(--universal-padding);
        }}

        tr:nth-child(even) td {{
            background-color: var(--table-body-alt-back-color);
        }}

        h1 mark {{
            background-color: #3cb4e6; /* Updated mark background color */
            color: #ffffff; /* Set text color to white */
        }}
    </style>
</head>
<body>
<center>
<h1 id="hal-migration-checklist"><mark> {log_file_messages["HTML_FILE_TITLE"]} </mark></h1>
<img src="{logo_path}"  width="400px" />
</a>
</center>
"""

TABLE_HEADER_LEFT = """
    <div style="border: 1px solid #03234b; padding: 10px; margin: 20px auto; width: 98%; text-align: left;
    background-color: #FFd200;">
        <p style="font-weight: bold; font-size: 14px; margin-left: 10px;">{log_msg_title}</p>
        <table style="margin: 0 auto; border-collapse: collapse; width: 100%;">
            <thead>
                <tr>
"""
if UseLogFileLineNumber:
    TABLE_HEADER_LEFT +=    """
                                <th style="border: 1px solid #03234b; background-color: #03234b;
                                color: #ffffff; padding: 8px;"> Line number </th>
                            """
TABLE_HEADER_LEFT +=        """
                                <th style="border: 1px solid #03234b; background-color: #03234b;
                                color: #ffffff; padding: 8px;"> HAL1 api name </th>
                            """
if UseLogFileAPIType:
    TABLE_HEADER_LEFT +=    """
                                <th style="border: 1px solid #03234b; background-color: #03234b;
                                color: #ffffff; padding: 8px;"> HAL1 api type </th>
                            """
if UseLogFileAPILayer:
    TABLE_HEADER_LEFT +=    """
                                <th style="border: 1px solid #03234b; background-color: #03234b;
                                color: #ffffff; padding: 8px;"> HAL1 api layer </th>
                            """
if UseLogFileAPIDriverFile:
    TABLE_HEADER_LEFT +=    """
                                <th style="border: 1px solid #03234b; background-color: #03234b;
                                color: #ffffff; padding: 8px;"> Driver file name </th>
                            """

TABLE_HEADER_LEFT +=    """
                                <th style="border: 1px solid #03234b; background-color: #03234b;
                                color: #ffffff; padding: 8px;"> Documentation link</th>
                                </tr>
                                </thead>
                                    <tbody>
                        """

TABLE_HEADER_RIGHT =    """
                                </tbody>
                                </table>
                                </div>
                        """

HTML_HEADER_RIGHT =     """</table> </body> </html>"""


CSS_C_SOURCE_HTML =     """
                            .custom-tooltip {
                                display: none;
                                position: absolute;
                                background: #fff;         /* Light background */
                                color: #222;              /* Dark text */
                                padding: 6px 12px;
                                border-radius: 4px;
                                font-size: 14px;
                                z-index: 1000;
                                pointer-events: none;
                                max-width: 450px;
                                white-space: pre-line;
                                border: 1px solid #222;   /* Optional: dark border for contrast */
                                box-shadow: 0 2px 8px rgba(0,0,0,0.08); /* Optional: subtle shadow */
                            }
                            table.code-table { border-collapse: collapse; }
                            td.line-number {
                                text-align: right;
                                padding-right: 16px;
                                color: #888;
                                background: #f0f0f0;
                                user-select: none;
                                border-right: 1px solid #ddd;
                            }
                            td.code-line {
                                white-space: pre;
                                font-family: monospace;
                                background: #eee;
                            }
                        """

JS_C_SOURCE_HTML =  """
                    const tooltip = document.getElementById('tooltip');
                    tooltip.setAttribute('aria-live', 'polite');

                    document.querySelectorAll('.hal-api-link').forEach(link => {
                        link.addEventListener('mouseover', function(e) {
                            const apiName = this.getAttribute('data-api');
                            tooltip.innerHTML = `<strong>Click here for HAL1 API Migration Documentation Link</strong>
                            <strong>HAL1 API Info:</strong> <br> ${apiName ? apiName : 'Unknown API'}`;
                            tooltip.style.display = 'block';
                            // Get the link's position and size
                            const rect = this.getBoundingClientRect();
                            // Position tooltip just below the link
                            tooltip.style.left = (window.scrollX + rect.left) + 'px';
                            tooltip.style.top = (window.scrollY + rect.bottom + 4) + 'px'; // 4px gap
                        });

                        link.addEventListener('mouseout', function() {
                            tooltip.style.display = 'none';
                        });
                    });
                """


def get_c_source_html_content(html_file_name, code_with_line_numbers):
    """
    Generate the complete HTML content for displaying C source code with line numbers.

    Args:
        html_file_name (str): The name of the HTML file or the title to display.
        code_with_line_numbers (str): HTML string containing table rows with code lines and line numbers.

    Returns:
        str: The full HTML content as a string, ready to be written to a file.
    """
    c_source_html_content = f"""<!DOCTYPE html>
        <html lang="en">
        <head>
            <meta charset="UTF-8">
            <title>{html_file_name}</title>
            <style>
                body {{ font-family: monospace; background: #f9f9f9; }}
                {CSS_C_SOURCE_HTML}
            </style>
        </head>
        <body>
            <h2>{html_file_name}</h2>
            <table class="code-table">
                <tbody>
                    {code_with_line_numbers}
                </tbody>
            </table>
            <div id="tooltip" class="custom-tooltip"></div>
            <div id="external-content"></div>
            <script>
            {JS_C_SOURCE_HTML}
            </script>
        </body>
        </html>
        """
    return c_source_html_content


def get_code_with_line_numbers(idx, line):
    """
    Generate an HTML table row with a line number and corresponding code line.

    Args:
        idx (int): The line number to display.
        line (str): The code line content.

    Returns:
        str: An HTML string representing a table row with the line number and code.
    """
    return (
        f"<tr>"
        f"<td class='line-number'>{idx}</td>"
        f"<td class='code-line'>{line}</td>"
        f"</tr>\n"
    )
