
  @verbatim
  ******************************************************************************
  * @file    st_readme.txt
  * @brief   This file lists the main modification done by STMicroelectronics on
  *          FreeRTOS for integration with STM32Cube solution.
  *          For more details on FreeRTOS implementation on STM32Cube, please refer
  *          to UM1722 "Developing Applications on STM32Cube with FreeRTOS"
  ******************************************************************************
  *
  * Copyright (c) 2023-2025 STMicroelectronics. All rights reserved.
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                       opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  @endverbatim

=======

### 03-October-2025 ###
=========================
  This pack version is based on FreeRTOS 11.2.0 version
  + Add Changelogs section to the .pdsc file
  + Remove dry-run from FreeRTOS JSON file
  + Update JSON file with new layout proposal
  + Add helper function to retrieve the used FreeRTOS port
  + Add missing condition for some freertos parameters
  + Add CPU and systick frequency getters for H7P, G5 and C0 families.
  + Update Flags from List Type (Enabled/Disabled) to Boolean Type.

### 18-August-2025 ###
=========================
  This pack version is based on FreeRTOS 11.2.0 version
  + Align generator naming with SAD 1.2
  + Add some metadata to help pack relocation into IDE project structure
  + Update FreeRTOSConfig_template.h to version 11.2.0
  + Enhance Warning Messages in the GUI for users
  + Support Sytick_frequency getter for V8 family
  + Update the license file of FreeRTOSConfig_template.h.hbs

### 30-May-2025 ###
=========================
  This pack version is based on FreeRTOS 11.2.0 version
  + Support the new grammar 3.1 version
  + Align template files naming with SAD 1.2
  + Implement Stream Buffer component with dry-run functionality
  + Add missing configurable parameters for all RTOS objects
  + Add freertos_helpers.js file
  + Add the getters for system clock and cpu clock frequencies
  + Add the sbom_cdx.json file

### 02-May-2025 ###
=========================
  This pack version is based on FreeRTOS 11.2.0 version
  + Support of the new version FreeRTOS 11.2.0
  + template files naming alignment with SAD 1.2
  + Parameters file update to support new FreeRTOS version
  + Progressive view integration

### 11-April-2025 ###
=========================
  This pack version is based on FreeRTOS 10.6.2 version
  + Minor update in the .bat/.sh scripts and mx_freertos.c.hbs file

### 21-March-2025 ###
=========================
  This pack version is based on FreeRTOS 10.6.2 version
  + Minor update in PDSC file: using the new version format and adding ECCN
  + Minor update in the mx_freertos.c.hbs, mx_freertos.h.hbs and Json files

### 24-Febrruary-2025 ###
=========================
  + Update Open-CMSIS-Pack version
  + Add reference to specific grammars
  + Update Cortex M85 condition
  + Add missing header files
  + Update the declaration of user-friendly name components and entry points
  + Align the pack .bat/.sh scripts with the newly delivered versions
  + Update the mx_freertos.c.hbs, mx_freertos.h.hbs and Json files

### 18-October-2024 ###
=========================
  + Update to FreeRTOS 10.6.2 version
  + Update configuration parameters files
  + Add mx_freertos.c/.h.hbs files
  + Update pdsc file: add support of CM85 core

### 06-September-2024 ###
=========================
  + Update configuration parameters files: Json and Hbs files
  + Update pdsc file.

### 31-May-2024 ###
=========================
  + Add .config folder with configuration parameters files
  + Update pdsc file.

### 22-March-2024 ###
=========================
  + Add app_samples folder with applicative files
  + Update pdsc file.

### 14-September-2023 ###
=========================
  + Update to FreeRTOS 10.5.1 version
  + Add pdsc file.