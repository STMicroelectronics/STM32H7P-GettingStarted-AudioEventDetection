"""
/**
  *************************************************************************************************
  * @file    log_messages.py
  * @brief   provides hal detection stubbing script log messages services
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

console_log_messages = {
                          "START_HAL_AUTOMATIC_SCRIPT" : (
                                                            "HAL1 automatic detection"
                                                            " started successfully"
                                                         ),
                          "STUB_APP_FILES_NBR":"HAL1 automatic detection applicative files number: ",
                          "STUB_PROGRESS_MSG":"HAL1 automatic detection progression",
                          "HAL_AUTOMATIC_SCRIPT_SUCCESS": (
                                                            "HAL1 automatic detection"
                                                            "execution completed successfully"
                                                          ),
                          "GENERATED_FILE_UNDER":"HAL1 automatic detection log file is generated under: ",
                          "EXECUTION_TIME":"HAL1 automatic detection execution time:",
                          "STUBBED_APP_FILES_NBR":  (
                                                      "HAL1 automatic detection applicative "
                                                      "detected files number: "
                                                    ),
                          "DATABASE_NOT_FOUND" : "[ERROR] Database not found issue:",
                          "MODULES_NOT_FOUND" : "[ERROR] Module(s) not found in database issue:",
                          "EMPTY_CSV_FILE" : "[ERROR] Empty database issue",
                          "ERROR_LOADING_DATABASE" : "[ERROR] Database loading issue",
                          "ERROR_PROCESSING_FILE" : "[ERROR] Applicative file processing issue: %s",
                          "FILE_NOT_FOUND" : "[ERROR] File not found:",
                          "IO_ERROR" : "[ERROR] I/O issue: %s",
                          "PATHSOURCE_HELP_MESSAGE" : "Select the directory path of HAL1 based application",
                          "MODULES_HELP_MESSAGE" :  (
                                                      "Select the list of HAL1 modules to be stubbed within HAL1 "
                                                      "based application. When using all, all HAL1 modules "
                                                      "are stubbed otherwise only listed modules will be stubbed."
                                                    ),
                          "DETECTION_HELP_MESSAGE" :  (
                                                        "Select the -d dry-run option. When using -d dry-run, "
                                                        "the HAL1 automatic detection and stubbing script "
                                                        "will detect only HAL1 APIs and when using -d stub "
                                                        "the HAL1 automatic detection and stubbing script "
                                                        "will detect and stub HAL1 APIs."
                                                      ),
                          "STUBBED_FILE" : "applicative file is already stubbed.",
                       }

warning_log_messages = {
                          "STUBBED_HEADER_MESSAGE":"THIS FILE IS YET STUBBED",
                          "STUBBED_HEADER_BORDER_CHAR":"#",
                          "ADDITIONAL_COMPILATION_FLAG": (
                                                          "This compilation flag is added to prevent "
                                                          "compilation errors."
                                                          " It shall be commented once resolve stubbing in line"
                                                         ),
                          "MODIFIED_LINE" : "*** MODIFIED LINE ***",
                          "WARNING" : '#warning "',
                       }


log_file_messages =   {
                          "HTML_FILE_TITLE" : "HAL1 automatic detection log",
                      }
