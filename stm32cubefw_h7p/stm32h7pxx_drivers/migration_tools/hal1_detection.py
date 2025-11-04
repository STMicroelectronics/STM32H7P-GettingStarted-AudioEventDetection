"""
/**
  *************************************************************************************************
  * @file    hal1_detection.py
  * @brief   provides hal detection stubbing script entry point
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

import subprocess
import sys
import traceback
import logging
import time
import os
import re
import shutil
import pandas as pd
import tqdm
import ply
from ply import lex

if getattr(sys, 'frozen', False):
    app_path = os.path.dirname(sys.executable)
else:
    app_path = os.path.dirname(os.path.abspath(__file__))

sys.path.insert(1, app_path)

def main():
    """
    Entry point for the HAL detection stubbing script.

    This function executes the migration core logic by running the
    'hal_detection_stubbing_script/core/migration_core.py' script.
    """
    with open('hal_detection_stubbing_script/core/migration_core.py', encoding='utf-8') as f:
        exec(f.read())
    # exec(open('hal_detection_stubbing_script/core/migration_core.py').read())

if __name__ == "__main__":
    main()
