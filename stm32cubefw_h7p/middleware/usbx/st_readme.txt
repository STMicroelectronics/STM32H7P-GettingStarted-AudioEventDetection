  /**
  ******************************************************************************
  * @file    st_readme.txt
  * @brief   This file lists the main changes done by STMicroelectronics on
  *          USBX for STM32 devices.
  /*****************************************************************************
  * Copyright (c) 2025 STMicroelectronics.
  *
  * This program and the accompanying materials are made available under the
  * terms of the MIT License which is available at
  * https://opensource.org/licenses/MIT.
  *
  * SPDX-License-Identifier: MIT
  *****************************************************************************/

=======

### V6.4.1_30092025 (2025-09-30) ###
============================
-  Updated the JSON and HBS files.
-  Removed the dry-run feature.
-  Added entry points for release notes and overview.
-  Renamed components containing only template files for code generation.

### V6.4.1_19082025 (2025-08-19) ###
============================
-  Added metadata to help with pack relocation into the IDE project structure.
-  Updated the JSON file with the new layout.
-  Updated the HBS files to align with the new layout.

### V6.4.1_15052025 (2025-05-15) ###
============================
-  Added support for the following device classes: DFU, CCID, Printer, Audio, Video.
-  Updated generated files.
-  Changed the new grammar support.

### V6.4.1_23042025 (2025-04-23) ###
============================
-  Added support for the following host classes: GSER, PROLIFIC, SWAR.
-  Added DFU device class.
-  Added generated files.
-  Updated name generated files.
-  Minor update in the .bat/.sh scripts

### V6.4.1_24032025 (2025-03-24) ###
============================
-  Minor update in PDSC file: using the new version format and adding ECCN.

### V6.4.1_21022025 (2025-02-21) ###
============================
- Support for the following device classes in JSON file: HID, CDC, MSC, and MTP.
- Support for the following host classes in JSON file: HID, MSC, and HUB.
- Code generation of HBS files for the UX stack.
- Updated the declaration of user-friendly name components and entry points.
- Added support for the following device classes: MTP, VIDEO, PRINTER, AUDIO, and CCID.
- Added support for the following host classes: PRINTER, HUB, and MTP.

### V6.4.1_22102024 (2024-10-22) ###
============================
- Add .config folder with configuration parameters files: Json and Hbs files
- Resolved Issues with Generated Common Include Files

### V6.4.1_05092024 (05-09-2024) ###
============================
- Update utility files to be RTOS agnostic.
- Update controllers to be compatible with the new HAL version.
- Add CDC ACM descriptor support.

### V6.4.1_04062024 (04-06-2024) ###
============================
- Add RTOS agnostic support features

### V6.4.1 (22-03-2024) ###
============================
- Add USBX 6.4.1 from Eclipse ThreadX
- Add app_samples folder with applicative files