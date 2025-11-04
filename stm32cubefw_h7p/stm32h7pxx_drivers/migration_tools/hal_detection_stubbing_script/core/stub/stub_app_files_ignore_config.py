"""
/**
  *************************************************************************************************
  * @file    stub_app_files_ignore_config.py
  * @brief   provides hal detection stubbing script stub application files ignore config services
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

# List of drivers
excluded_drivers = [
                    "stm32_hal_legacy.h",
                    "stm32_assert_template.h",
                    "systmem.c",
                    "syscalls.c",
                   ]
# List of patterns
patterns = [
    r"stm32(\w+)xx\.(c|h)",                         # exclude stm32{*}xx.h
    r"stm32(\w+)xxxx\.(c|h)",                       # exclude stm32{*}xxxx.h
    r"(\w+)_conf\.(h)",                             # exclude stm32{*}_nucleo_conf.h
    r"system_stm32(\w+)xx\.(c|h)",                  # exclude system_stm32{*}xx.c/h
    r"partition_stm32(\w+)xx\.(c|h)",               # exclude partition_stm32{*}xx.h
    r"partition_stm32(\w+)xxxx\.(c|h)",             # exclude partition_stm32{*}xxxx.h
    r"startup_stm32(\w+)xx\.(c|h)",                 # exclude startup_stm32{*}xx.c
    r"startup_stm32(\w+)xxxx\.(c|h)",               # exclude startup_stm32{*}xxxx.c
    r"startup_stm32(\w+)xxxx_s\.(c|h)",             # exclude startup_stm32{*}xxxx_s.c
    r"startup_stm32(\w+)xxxx_ns\.(c|h)",            # exclude startup_stm32{*}xxxx_ns.c
    r"stm32(\w+)xx_(hal|ll)_(?!msp)(\w+)\.(c|h)",   # exclude stm32tnxx_ll_*.c/h, stm32tnxx_hal_*.c/h except _msp.c
    r"stm32[a-zA-Z0-9]+xx_hal_msp_template\.c",     # exclude stm32tnxx_hal_msp_template.c
    r"stm32[a-zA-Z0-9]+xx_hal\.(c|h)",              # exclude stm32tnxx_hal.c/h
]

# The script shall stub these files when found
special_files = []
