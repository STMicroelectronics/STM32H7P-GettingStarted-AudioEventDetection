"""
/**
  *************************************************************************************************
  * @file    hal_detection_stubbing_default_config.py
  * @brief   provides HAL1 detection script default configuration
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

CONFIG_FILENAME = "hal1_detection_config.py"
DEFAULT_CONFIG = '''"""
/**
  *************************************************************************************************
  * @file    hal1_detection_config.py
  * @brief   provides HAL1 detection script configuration
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

# Specifies the stubbing compilation flag to be generated within warning messages
StubbingCompilationFlag              = "TO_DO_RESOLVE_STUB"

# Specifies the stubbing of warning messages generation within applicative file
UseWarningMessage = True

# Specifies the stubbing warning messages fields separators
StubbingWarningMessageSeparator      = "**"

# Specifies the generic message within warning messages
UseWarningMessageGenericMessage      = True
StubbingWarningMessageGenericMessage = "STUB TO RESOLVE"

# Specifies the line number within warning messages
UseWarningMessageLineNumber          = True

# Specifies the API name within warning messages
UseWarningMessageAPIName             = True

# Specifies the API type within warning messages
UseWarningMessageAPIType             = True

# Specifies the API layer within warning messages
UseWarningMessageAPILayer            = True

# Specifies the API driver file within warning messages
UseWarningMessageAPIDriverFile       = True

# Specifies the line number within log file
UseLogFileLineNumber                 = True

# Specifies the API type within log file
UseLogFileAPIType                    = True

# Specifies the API layer within log file
UseLogFileAPILayer                   = True

# Specifies the API driver file within log file
UseLogFileAPIDriverFile              = True
'''

ALL_DISABLED_DEFAULT_CONFIG = '''"""
/**
  *************************************************************************************************
  * @file    hal1_detection_config.py
  * @brief   provides HAL1 detection script configuration
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

# Specifies the stubbing compilation flag to be generated within warning messages
StubbingCompilationFlag              = "TO_DO_RESOLVE_STUB"

# Specifies the stubbing of warning messages generation within applicative file
UseWarningMessage = False

# Specifies the stubbing warning messages fields separators
StubbingWarningMessageSeparator      = ""

# Specifies the generic message within warning messages
UseWarningMessageGenericMessage      = False
StubbingWarningMessageGenericMessage = ""

# Specifies the line number within warning messages
UseWarningMessageLineNumber          = False

# Specifies the API name within warning messages
UseWarningMessageAPIName             = False

# Specifies the API type within warning messages
UseWarningMessageAPIType             = False

# Specifies the API layer within warning messages
UseWarningMessageAPILayer            = False

# Specifies the API driver file within warning messages
UseWarningMessageAPIDriverFile       = False

# Specifies the line number within log file
UseLogFileLineNumber                 = False

# Specifies the API type within log file
UseLogFileAPIType                    = False

# Specifies the API layer within log file
UseLogFileAPILayer                   = False

# Specifies the API driver file within log file
UseLogFileAPIDriverFile              = False
'''
