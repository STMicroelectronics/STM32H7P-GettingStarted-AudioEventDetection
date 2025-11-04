  /**
  ******************************************************************************
  * @file    st_readme.txt
  * @brief   This file lists the main changes done by STMicroelectronics on
  *          FileX for STM32 devices.
  ******************************************************************************
  * Copyright (c) 2025 STMicroelectronics
  *
  * This program and the accompanying materials are made available under the
  * terms of the MIT License which is available at
  * https://opensource.org/licenses/MIT.
  *
  * SPDX-License-Identifier: MIT
  **************************************************************************/

=======

### V6.4.1_22092025 (22-09-2025) ###
=========================
- Add changelog reference check in pdsc to avoid missing release notes.
- Update FileX JSON by removing the dry-run feature when unnecessary for configuration.
### V6.4.1_18082025 (18-08-2025) ###
=========================
- Add metadata to help relocate the FileX pack in the IDE project structure.
- Implement the MMC interface in both RTOS and standalone modes.
- Implement the FileX NAND Flash interface.
- Update FileX JSON with new layout proposal.
### V6.4.1_20052025 (30-05-2025) ###
=========================
- Update configuration code generation for Grammar version 3.0
- Add mx_filex_interfaces.c and mx_filex_interfaces.h template files
- Add the sbom_cdx.json file
### V6.4.1_28042025 (28-04-2025) ###
=========================
- Add generated files
- Minor update in the .bat/.sh scripts
- Align component names with the FileX SAD 1.2
### V6.4.1_24032025 (24-03-2025) ###
=========================
- Minor update in PDSC file: using the new version format and adding ECCN
### V6.4.1_24022025 (24-02-2025) ###
- Update the declaration of user-friendly name components and entry points
- Add pre alpha version NOR Flash interface
- Add the Progressive Configuration
### V6.4.1_21102024 (21-10-2024) ###
========================
- Add .config folder with configuration parameters files: Json and Hbs files
- Update the pdsc file.
### V6.4.1_06092024 (06-09-2024) ###
========================
- Include the necessary header files.
- Update the pdsc file.

### v6.4.1_03062024 (03-06-2024) ###
============================
- Add RTOS agnostic support features
- Implement RTOS agnostic capabilities to support FreeRTOS and standalone modes

### V6.4.1 (22-03-2024) ###
============================
- Add FileX 6.4.1 from Eclipse ThreadX
- Add app_samples folder with applicative files
- Add the .pdsc file
