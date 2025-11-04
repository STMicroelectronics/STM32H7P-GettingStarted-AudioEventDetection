# **STM32V9xx Device Family PACK (DFP)**

**STM32Cube** is an STMicroelectronics original initiative to ease the developers life by reducing efforts, time and cost.

## 1. Overview

**STM32V9xx DFP** contains essential information and files for IDEs, toolchains and software applications to support STM32V9xx devices.

This DFP includes the following components

* **Documentation**
  * Device documentation (Reference Manuals, Datasheets, ...) links are provided in the DFP Pack description file (`STMicroelectronics.stm32xxxx_dfp.pdsc` file)
  * Readme
  * Release Notes
* **CMSIS-Core Device Files**
  * `startup_stm32h7pxxx.c` : device startup file
  * `system_stm32h7px<|_s|_ns>.<c|h>` : device system configuration files
  * `stm32h7pxxx.h` : device header file
  * `stm32h7pxxx.<ld|sct|icf>` device linker configuration file
* **IDE/Tools Device Support Files**
  * `Flash/*.FLM` : Flash Programming Algorithms for erasing and downloading code into on-chip Flash
  * `SVD/*.SVD` : System View Description Files describing the programmer's view of the device's peripherals
  * `.iar/*`: IAR flashloader, debugger and device configuration files
  * `Descriptors` : Device descriptor files for bus, clock, option bytes, memory, peripherals and pinout

## 2.Release notes

Details about the content of this release are available in the release note [here](Release_Notes.html).

## 3.License

Copyright (c) 2022 STMicroelectronics.

This software is licensed under terms that can be found in the LICENSE.txt file in the root directory of this software component.
If no LICENSE.txt file comes with this software, it is provided AS-IS.
