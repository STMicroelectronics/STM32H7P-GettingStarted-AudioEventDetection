"""
/**
  *************************************************************************************************
  * @file    migration_core.py
  * @brief   provides hal detection stubbing script core services
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

import logging
import time
from datetime import datetime
import os
from pathlib import Path

from hal_detection_stubbing_script.core import sequencer
from hal_detection_stubbing_script.core.cmd import cmd_line
from hal_detection_stubbing_script.core.log import log
from hal_detection_stubbing_script.core.log.log_messages import console_log_messages



timestamp = datetime.now().strftime('%d-%m-%Y_%H-%M-%S')
LOG_DIR = 'hal1_detection_script_log'
LOG_HTML_FILE_NAME = f'log_{timestamp}.html'
LOG_HTML_FOLDER_NAME = f'log_{timestamp}'

if not os.path.exists(LOG_DIR):
    os.makedirs(LOG_DIR)

logging.basicConfig(
    level=logging.INFO,
    format='%(message)s'
)
logger = logging.getLogger(__name__)

if __name__ == "__main__":

    src_folder, src_files, modules, isDryRun= cmd_line.get_args()

    log.init()
    log.insert_src_files(src_files)

    t_exec_init = time.time()


    sequencer.apply_stubbing(src_files, modules, isDryRun)

    log_html_path = (
      Path.cwd().as_posix()
      + "/hal1_detection_script_log/"
      + LOG_HTML_FILE_NAME
    )

    log.write_html_file(log_html_path)

    logger.info('%s \n\033[92m%s\033[0m',console_log_messages["GENERATED_FILE_UNDER"],log_html_path)


    t_exec_end = time.time()
    logger.info('%s %.3f seconds',console_log_messages["EXECUTION_TIME"],round(t_exec_end - t_exec_init,3))

    logger.info('%s',console_log_messages["HAL_AUTOMATIC_SCRIPT_SUCCESS"])
