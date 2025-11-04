  /**
  ******************************************************************************
  * @file    st_readme.txt
  * @brief   This file lists the main changes done by STMicroelectronics on
  *          LevelX for STM32 devices.
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
### V6.4.1_250922 (10-10-2025) ###
=========================
- Add Interface configuration panel for W25N01GVXX and MX66UW1G45G parts
- Add changelog reference check in pdsc to avoid missing release notes
- Add MX66UW1G45G nor polling interface component
- Add W25Q128J nor interface components

### V6.4.1_250818 (18-08-2025) ###
=========================
- Add some metadata into LevelX pack to help pack relocation into IDE project structure
- Update MX25LM51245G nor interfaces
- Add W25N01GVXX nand interface components
- Add a memory open check in the user NOR and NAND APIs to prevent unexpected behavior after flash memory closure
- Rename generator into levelx_mx2codegen

### V6.4.1_250520 (30-05-2025) ###
=========================
- Support CodeGen new grammar version 3.1
- Update .json file
- Add mx_levelx_app.c/.h hbs template files
- Update MX25LM51245G and MX66LM1G45G nor interfaces
- Update CMakeLists.txt
- Add the sbom_cdx.json file

### V6.4.1_250428 (28-04-2025) ###
=========================
- Update pack and gpdsc naming
- Update MX25LM51245G and MX66LM1G45G nor interfaces to use memory mapped base address getter function
- CodeGen update: Add Main and Applicative configuration panels and implement progressive view
- Remove double quotes from .bat/.sh scripts

### V6.4.1_250324 (24-03-2025) ###
=========================
- Minor update in PDSC file: using the new version format and adding ECCN

### V6.4.1_250224 (24-02-2025) ###
============================
- Add .config folder with configuration parameters files: json and hbs files
- Update the declaration of user-friendly name components and entry points
- Add MX25LM51245G nor interface components
- Add MX66LM1G45G nor interface components

### V6.4.1_241021 (21-10-2024) ###
============================
- Implement RTOS agnostic support features
- Update pdsc file

### V6.4.1_240906 (06-09-2024) ###
============================
- Add LevelX 6.4.1 from Eclipse ThreadX
- Add app_samples folder with applicative files
- Add the pdsc file
