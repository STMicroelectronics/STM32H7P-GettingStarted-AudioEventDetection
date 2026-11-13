# STM32H7Pxx DFP Software Pack

![tag](https://img.shields.io/badge/tag-v2.0.0-brightgreen.svg)
[![release note](https://img.shields.io/badge/release_note-view_html-gold.svg)](https://htmlpreview.github.io/?https://github.com/STMicroelectronics/stm32h7pxx-dfp/blob/main/Release_Notes.html)

## Overview

**STM32H7Pxx DFP** contains essential information and files for IDEs, toolchains and software applications to support STM32H7Pxx devices.

## Description and Usage

This DFP includes the following components

* **Documentation**
  * Device documentation (Reference Manuals, Datasheets, ...) links are provided in the DFP Pack description file (`STMicroelectronics.stm32h7pxx_dfp.pdsc` file)
  * Readme
  * Release Notes
* **CMSIS-Core Device Files**
  * `startup_stm32h7pxxxx.c` : device startup file (should be compiled with C compiler)
  * `system_stm32h7pxx.{c|h}` : device system configuration files
  * `stm32h7pxxxx.h` : device header file
  * `stm32h7pxxxx.{ld|sct|icf}` device linker configuration file
* **IDE/Tools Device Support Files**
  * `Flash/*.xldr` : Flash Programming Algorithms for erasing and downloading code into on-chip Flash
  * `SVD/*.svd` : System View Description Files describing the programmer's view of the device's peripherals
  * `Descriptors` : Device descriptor files (clock, peripherals pinout, ...)
  * `IDEs_patches/EWARM` : needed patches to add STM32H7Pxx devices support in IAR Embedded Workbench for ARM
