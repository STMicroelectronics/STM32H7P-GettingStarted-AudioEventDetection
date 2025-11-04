# origin-pack: STMicroelectronics::stm32h7pxx_dfp@2.0.0-beta.1
# created-by: conversion-manager@0.0.64
project(STMicroelectronics_stm32h7pxx_dfp_2_0_0_beta_1)
cmake_minimum_required(VERSION 3.20)
add_library(STMicroelectronics_stm32h7pxx_dfp_2_0_0_beta_1 INTERFACE)

# List of all CMSIS properties that influence conditions for this package
if(NOT DEFINED CMSIS_Dname)
  set(CMSIS_Dname "CMSIS_Dname not set")
  message(DEBUG "CMSIS_Dname is not set to any value")
endif()

if(NOT DEFINED CMSIS_Dvendor)
  set(CMSIS_Dvendor "CMSIS_Dvendor not set")
  message(DEBUG "CMSIS_Dvendor is not set to any value")
endif()

if(NOT DEFINED CMSIS_Tcompiler)
  set(CMSIS_Tcompiler "CMSIS_Tcompiler not set")
  message(DEBUG "CMSIS_Tcompiler is not set to any value")
endif()


# Device specific defined symbols
if(CMSIS_Dname STREQUAL "STM32H7P4IGK6")
    target_compile_definitions(STMicroelectronics_stm32h7pxx_dfp_2_0_0_beta_1 INTERFACE STM32H7P4xx)
endif()
if(CMSIS_Dname STREQUAL "STM32H7P4IGT6")
    target_compile_definitions(STMicroelectronics_stm32h7pxx_dfp_2_0_0_beta_1 INTERFACE STM32H7P4xx)
endif()
if(CMSIS_Dname STREQUAL "STM32H7P4IIK6")
    target_compile_definitions(STMicroelectronics_stm32h7pxx_dfp_2_0_0_beta_1 INTERFACE STM32H7P4xx)
endif()
if(CMSIS_Dname STREQUAL "STM32H7P4IIK6Q")
    target_compile_definitions(STMicroelectronics_stm32h7pxx_dfp_2_0_0_beta_1 INTERFACE STM32H7P4xx)
endif()
if(CMSIS_Dname STREQUAL "STM32H7P4IIT6")
    target_compile_definitions(STMicroelectronics_stm32h7pxx_dfp_2_0_0_beta_1 INTERFACE STM32H7P4xx)
endif()
if(CMSIS_Dname STREQUAL "STM32H7P4IIT6Q")
    target_compile_definitions(STMicroelectronics_stm32h7pxx_dfp_2_0_0_beta_1 INTERFACE STM32H7P4xx)
endif()
if(CMSIS_Dname STREQUAL "STM32H7P4IIZ3Q")
    target_compile_definitions(STMicroelectronics_stm32h7pxx_dfp_2_0_0_beta_1 INTERFACE STM32H7P4xx)
endif()
if(CMSIS_Dname STREQUAL "STM32H7P4QGT6")
    target_compile_definitions(STMicroelectronics_stm32h7pxx_dfp_2_0_0_beta_1 INTERFACE STM32H7P4xx)
endif()
if(CMSIS_Dname STREQUAL "STM32H7P4QIT6")
    target_compile_definitions(STMicroelectronics_stm32h7pxx_dfp_2_0_0_beta_1 INTERFACE STM32H7P4xx)
endif()
if(CMSIS_Dname STREQUAL "STM32H7P4QIT6Q")
    target_compile_definitions(STMicroelectronics_stm32h7pxx_dfp_2_0_0_beta_1 INTERFACE STM32H7P4xx)
endif()
if(CMSIS_Dname STREQUAL "STM32H7P4VGH6")
    target_compile_definitions(STMicroelectronics_stm32h7pxx_dfp_2_0_0_beta_1 INTERFACE STM32H7P4xx)
endif()
if(CMSIS_Dname STREQUAL "STM32H7P4VGT6")
    target_compile_definitions(STMicroelectronics_stm32h7pxx_dfp_2_0_0_beta_1 INTERFACE STM32H7P4xx)
endif()
if(CMSIS_Dname STREQUAL "STM32H7P4VIH6")
    target_compile_definitions(STMicroelectronics_stm32h7pxx_dfp_2_0_0_beta_1 INTERFACE STM32H7P4xx)
endif()
if(CMSIS_Dname STREQUAL "STM32H7P4VIH6Q")
    target_compile_definitions(STMicroelectronics_stm32h7pxx_dfp_2_0_0_beta_1 INTERFACE STM32H7P4xx)
endif()
if(CMSIS_Dname STREQUAL "STM32H7P4VIT6")
    target_compile_definitions(STMicroelectronics_stm32h7pxx_dfp_2_0_0_beta_1 INTERFACE STM32H7P4xx)
endif()
if(CMSIS_Dname STREQUAL "STM32H7P4VIT6Q")
    target_compile_definitions(STMicroelectronics_stm32h7pxx_dfp_2_0_0_beta_1 INTERFACE STM32H7P4xx)
endif()
if(CMSIS_Dname STREQUAL "STM32H7P4VIZ3Q")
    target_compile_definitions(STMicroelectronics_stm32h7pxx_dfp_2_0_0_beta_1 INTERFACE STM32H7P4xx)
endif()
if(CMSIS_Dname STREQUAL "STM32H7P4ZGT6")
    target_compile_definitions(STMicroelectronics_stm32h7pxx_dfp_2_0_0_beta_1 INTERFACE STM32H7P4xx)
endif()
if(CMSIS_Dname STREQUAL "STM32H7P4ZIT6")
    target_compile_definitions(STMicroelectronics_stm32h7pxx_dfp_2_0_0_beta_1 INTERFACE STM32H7P4xx)
endif()
if(CMSIS_Dname STREQUAL "STM32H7P4ZIT6Q")
    target_compile_definitions(STMicroelectronics_stm32h7pxx_dfp_2_0_0_beta_1 INTERFACE STM32H7P4xx)
endif()
if(CMSIS_Dname STREQUAL "STM32H7P4ZIZ3Q")
    target_compile_definitions(STMicroelectronics_stm32h7pxx_dfp_2_0_0_beta_1 INTERFACE STM32H7P4xx)
endif()
if(CMSIS_Dname STREQUAL "STM32H7P5IGK6")
    target_compile_definitions(STMicroelectronics_stm32h7pxx_dfp_2_0_0_beta_1 INTERFACE STM32H7P5xx)
endif()
if(CMSIS_Dname STREQUAL "STM32H7P5IGT6")
    target_compile_definitions(STMicroelectronics_stm32h7pxx_dfp_2_0_0_beta_1 INTERFACE STM32H7P5xx)
endif()
if(CMSIS_Dname STREQUAL "STM32H7P5IIK6")
    target_compile_definitions(STMicroelectronics_stm32h7pxx_dfp_2_0_0_beta_1 INTERFACE STM32H7P5xx)
endif()
if(CMSIS_Dname STREQUAL "STM32H7P5IIK6Q")
    target_compile_definitions(STMicroelectronics_stm32h7pxx_dfp_2_0_0_beta_1 INTERFACE STM32H7P5xx)
endif()
if(CMSIS_Dname STREQUAL "STM32H7P5IIT6")
    target_compile_definitions(STMicroelectronics_stm32h7pxx_dfp_2_0_0_beta_1 INTERFACE STM32H7P5xx)
endif()
if(CMSIS_Dname STREQUAL "STM32H7P5IIT6Q")
    target_compile_definitions(STMicroelectronics_stm32h7pxx_dfp_2_0_0_beta_1 INTERFACE STM32H7P5xx)
endif()
if(CMSIS_Dname STREQUAL "STM32H7P5IIZ3Q")
    target_compile_definitions(STMicroelectronics_stm32h7pxx_dfp_2_0_0_beta_1 INTERFACE STM32H7P5xx)
endif()
if(CMSIS_Dname STREQUAL "STM32H7P5QGT6")
    target_compile_definitions(STMicroelectronics_stm32h7pxx_dfp_2_0_0_beta_1 INTERFACE STM32H7P5xx)
endif()
if(CMSIS_Dname STREQUAL "STM32H7P5QIT6")
    target_compile_definitions(STMicroelectronics_stm32h7pxx_dfp_2_0_0_beta_1 INTERFACE STM32H7P5xx)
endif()
if(CMSIS_Dname STREQUAL "STM32H7P5QIT6Q")
    target_compile_definitions(STMicroelectronics_stm32h7pxx_dfp_2_0_0_beta_1 INTERFACE STM32H7P5xx)
endif()
if(CMSIS_Dname STREQUAL "STM32H7P5VGH6")
    target_compile_definitions(STMicroelectronics_stm32h7pxx_dfp_2_0_0_beta_1 INTERFACE STM32H7P5xx)
endif()
if(CMSIS_Dname STREQUAL "STM32H7P5VGT6")
    target_compile_definitions(STMicroelectronics_stm32h7pxx_dfp_2_0_0_beta_1 INTERFACE STM32H7P5xx)
endif()
if(CMSIS_Dname STREQUAL "STM32H7P5VIH6")
    target_compile_definitions(STMicroelectronics_stm32h7pxx_dfp_2_0_0_beta_1 INTERFACE STM32H7P5xx)
endif()
if(CMSIS_Dname STREQUAL "STM32H7P5VIH6Q")
    target_compile_definitions(STMicroelectronics_stm32h7pxx_dfp_2_0_0_beta_1 INTERFACE STM32H7P5xx)
endif()
if(CMSIS_Dname STREQUAL "STM32H7P5VIT6")
    target_compile_definitions(STMicroelectronics_stm32h7pxx_dfp_2_0_0_beta_1 INTERFACE STM32H7P5xx)
endif()
if(CMSIS_Dname STREQUAL "STM32H7P5VIT6Q")
    target_compile_definitions(STMicroelectronics_stm32h7pxx_dfp_2_0_0_beta_1 INTERFACE STM32H7P5xx)
endif()
if(CMSIS_Dname STREQUAL "STM32H7P5VIZ3Q")
    target_compile_definitions(STMicroelectronics_stm32h7pxx_dfp_2_0_0_beta_1 INTERFACE STM32H7P5xx)
endif()
if(CMSIS_Dname STREQUAL "STM32H7P5ZGT6")
    target_compile_definitions(STMicroelectronics_stm32h7pxx_dfp_2_0_0_beta_1 INTERFACE STM32H7P5xx)
endif()
if(CMSIS_Dname STREQUAL "STM32H7P5ZIT6")
    target_compile_definitions(STMicroelectronics_stm32h7pxx_dfp_2_0_0_beta_1 INTERFACE STM32H7P5xx)
endif()
if(CMSIS_Dname STREQUAL "STM32H7P5ZIT6Q")
    target_compile_definitions(STMicroelectronics_stm32h7pxx_dfp_2_0_0_beta_1 INTERFACE STM32H7P5xx)
endif()
if(CMSIS_Dname STREQUAL "STM32H7P5ZIZ3Q")
    target_compile_definitions(STMicroelectronics_stm32h7pxx_dfp_2_0_0_beta_1 INTERFACE STM32H7P5xx)
endif()


# Include RTE_Components.h globally if needed
if(CMSIS_Tcompiler STREQUAL "IAR")
    target_compile_options(STMicroelectronics_stm32h7pxx_dfp_2_0_0_beta_1 INTERFACE "SHELL:--preinclude ${CMAKE_CURRENT_LIST_DIR}/RTE_Components.h")
else()
    target_compile_options(STMicroelectronics_stm32h7pxx_dfp_2_0_0_beta_1 INTERFACE "SHELL:-include ${CMAKE_CURRENT_LIST_DIR}/RTE_Components.h")
endif()





# Enable all components in this package
if(CMSIS_ENTIRE_STMicroelectronics_stm32h7pxx_dfp_2_0_0_beta_1)
  set(CMSIS_USE_Device_Startup_2_0_0_beta_1 true)
  set(CMSIS_USE_Device_Startup_SRAM_2_0_0_beta_1 true)
endif()

# All conditions used by this package

# condition: STMicroelectronics.stm32h7pxx_dfp.2.0.0-beta.1:STM32H7P
# description: 
if((CMSIS_Dname MATCHES "STM32H7P.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13"))
  set(STMicroelectronics.stm32h7pxx_dfp.2.0.0-beta.1:STM32H7P true)
  message(DEBUG "CMSIS condition STMicroelectronics.stm32h7pxx_dfp.2.0.0-beta.1:STM32H7P enabled")
endif()


# condition: STMicroelectronics.stm32h7pxx_dfp.2.0.0-beta.1:STM32H7P4
# description: 
if((CMSIS_Dname MATCHES "STM32H7P4.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13"))
  set(STMicroelectronics.stm32h7pxx_dfp.2.0.0-beta.1:STM32H7P4 true)
  message(DEBUG "CMSIS condition STMicroelectronics.stm32h7pxx_dfp.2.0.0-beta.1:STM32H7P4 enabled")
endif()


# condition: STMicroelectronics.stm32h7pxx_dfp.2.0.0-beta.1:STM32H7P5
# description: 
if((CMSIS_Dname MATCHES "STM32H7P5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13"))
  set(STMicroelectronics.stm32h7pxx_dfp.2.0.0-beta.1:STM32H7P5 true)
  message(DEBUG "CMSIS condition STMicroelectronics.stm32h7pxx_dfp.2.0.0-beta.1:STM32H7P5 enabled")
endif()


# condition: STMicroelectronics.stm32h7pxx_dfp.2.0.0-beta.1:STM32H7PxxG ARMCC
# description: 
if(((CMSIS_Dname MATCHES "STM32H7P..G.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND CMSIS_Tcompiler STREQUAL "ARMCC"))
  set(STMicroelectronics.stm32h7pxx_dfp.2.0.0-beta.1:STM32H7PxxG_ARMCC true)
  message(DEBUG "CMSIS condition STMicroelectronics.stm32h7pxx_dfp.2.0.0-beta.1:STM32H7PxxG_ARMCC enabled")
endif()


# condition: STMicroelectronics.stm32h7pxx_dfp.2.0.0-beta.1:STM32H7PxxG GCC
# description: 
if(((CMSIS_Dname MATCHES "STM32H7P..G.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND CMSIS_Tcompiler STREQUAL "GCC"))
  set(STMicroelectronics.stm32h7pxx_dfp.2.0.0-beta.1:STM32H7PxxG_GCC true)
  message(DEBUG "CMSIS condition STMicroelectronics.stm32h7pxx_dfp.2.0.0-beta.1:STM32H7PxxG_GCC enabled")
endif()


# condition: STMicroelectronics.stm32h7pxx_dfp.2.0.0-beta.1:STM32H7PxxG IAR
# description: 
if(((CMSIS_Dname MATCHES "STM32H7P..G.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND CMSIS_Tcompiler STREQUAL "IAR"))
  set(STMicroelectronics.stm32h7pxx_dfp.2.0.0-beta.1:STM32H7PxxG_IAR true)
  message(DEBUG "CMSIS condition STMicroelectronics.stm32h7pxx_dfp.2.0.0-beta.1:STM32H7PxxG_IAR enabled")
endif()


# condition: STMicroelectronics.stm32h7pxx_dfp.2.0.0-beta.1:STM32H7PxxI ARMCC
# description: 
if(((CMSIS_Dname MATCHES "STM32H7P..I.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND CMSIS_Tcompiler STREQUAL "ARMCC"))
  set(STMicroelectronics.stm32h7pxx_dfp.2.0.0-beta.1:STM32H7PxxI_ARMCC true)
  message(DEBUG "CMSIS condition STMicroelectronics.stm32h7pxx_dfp.2.0.0-beta.1:STM32H7PxxI_ARMCC enabled")
endif()


# condition: STMicroelectronics.stm32h7pxx_dfp.2.0.0-beta.1:STM32H7PxxI GCC
# description: 
if(((CMSIS_Dname MATCHES "STM32H7P..I.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND CMSIS_Tcompiler STREQUAL "GCC"))
  set(STMicroelectronics.stm32h7pxx_dfp.2.0.0-beta.1:STM32H7PxxI_GCC true)
  message(DEBUG "CMSIS condition STMicroelectronics.stm32h7pxx_dfp.2.0.0-beta.1:STM32H7PxxI_GCC enabled")
endif()


# condition: STMicroelectronics.stm32h7pxx_dfp.2.0.0-beta.1:STM32H7PxxI IAR
# description: 
if(((CMSIS_Dname MATCHES "STM32H7P..I.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND CMSIS_Tcompiler STREQUAL "IAR"))
  set(STMicroelectronics.stm32h7pxx_dfp.2.0.0-beta.1:STM32H7PxxI_IAR true)
  message(DEBUG "CMSIS condition STMicroelectronics.stm32h7pxx_dfp.2.0.0-beta.1:STM32H7PxxI_IAR enabled")
endif()


# condition: STMicroelectronics.stm32h7pxx_dfp.2.0.0-beta.1:STM32H7Pxxx ARMCC
# description: 
if(((CMSIS_Dname MATCHES "STM32H7P....*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND CMSIS_Tcompiler STREQUAL "ARMCC"))
  set(STMicroelectronics.stm32h7pxx_dfp.2.0.0-beta.1:STM32H7Pxxx_ARMCC true)
  message(DEBUG "CMSIS condition STMicroelectronics.stm32h7pxx_dfp.2.0.0-beta.1:STM32H7Pxxx_ARMCC enabled")
endif()


# condition: STMicroelectronics.stm32h7pxx_dfp.2.0.0-beta.1:STM32H7Pxxx GCC
# description: 
if(((CMSIS_Dname MATCHES "STM32H7P....*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND CMSIS_Tcompiler STREQUAL "GCC"))
  set(STMicroelectronics.stm32h7pxx_dfp.2.0.0-beta.1:STM32H7Pxxx_GCC true)
  message(DEBUG "CMSIS condition STMicroelectronics.stm32h7pxx_dfp.2.0.0-beta.1:STM32H7Pxxx_GCC enabled")
endif()


# condition: STMicroelectronics.stm32h7pxx_dfp.2.0.0-beta.1:STM32H7Pxxx IAR
# description: 
if(((CMSIS_Dname MATCHES "STM32H7P....*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND CMSIS_Tcompiler STREQUAL "IAR"))
  set(STMicroelectronics.stm32h7pxx_dfp.2.0.0-beta.1:STM32H7Pxxx_IAR true)
  message(DEBUG "CMSIS condition STMicroelectronics.stm32h7pxx_dfp.2.0.0-beta.1:STM32H7Pxxx_IAR enabled")
endif()

# Files and components in this package
if(CMSIS_USE_Device_Startup_2_0_0_beta_1)  # System Startup for STMicroelectronics STM32H7P Series
  message(DEBUG "Using component Device_Startup_2_0_0_beta_1")
  if(STMicroelectronics.stm32h7pxx_dfp.2.0.0-beta.1:STM32H7P)
    target_compile_definitions(STMicroelectronics_stm32h7pxx_dfp_2_0_0_beta_1 INTERFACE -DCMSIS_USE_Device_Startup_2_0_0_beta_1=1)
    target_include_directories(STMicroelectronics_stm32h7pxx_dfp_2_0_0_beta_1 INTERFACE Include)
    target_include_directories(STMicroelectronics_stm32h7pxx_dfp_2_0_0_beta_1 INTERFACE Include/)
    target_include_directories(STMicroelectronics_stm32h7pxx_dfp_2_0_0_beta_1 INTERFACE Include/Templates)
    target_sources(STMicroelectronics_stm32h7pxx_dfp_2_0_0_beta_1 INTERFACE Source/Templates/system_stm32h7pxx.c)
    if(STMicroelectronics.stm32h7pxx_dfp.2.0.0-beta.1:STM32H7P4)
      target_sources(STMicroelectronics_stm32h7pxx_dfp_2_0_0_beta_1 INTERFACE Source/startup_stm32h7p4xx.c)
    endif()
    if(STMicroelectronics.stm32h7pxx_dfp.2.0.0-beta.1:STM32H7P5)
      target_sources(STMicroelectronics_stm32h7pxx_dfp_2_0_0_beta_1 INTERFACE Source/startup_stm32h7p5xx.c)
    endif()
    if(STMicroelectronics.stm32h7pxx_dfp.2.0.0-beta.1:STM32H7PxxG_ARMCC)
    endif()
    if(STMicroelectronics.stm32h7pxx_dfp.2.0.0-beta.1:STM32H7PxxG_GCC)
      target_link_options(STMicroelectronics_stm32h7pxx_dfp_2_0_0_beta_1 INTERFACE -T${CMAKE_CURRENT_LIST_DIR}/Source/Templates/gcc/linker/stm32h7pxxg_flash.ld)
    endif()
    if(STMicroelectronics.stm32h7pxx_dfp.2.0.0-beta.1:STM32H7PxxG_IAR)
    endif()
    if(STMicroelectronics.stm32h7pxx_dfp.2.0.0-beta.1:STM32H7PxxI_ARMCC)
    endif()
    if(STMicroelectronics.stm32h7pxx_dfp.2.0.0-beta.1:STM32H7PxxI_GCC)
      target_link_options(STMicroelectronics_stm32h7pxx_dfp_2_0_0_beta_1 INTERFACE -T${CMAKE_CURRENT_LIST_DIR}/Source/Templates/gcc/linker/stm32h7pxxi_flash.ld)
    endif()
    if(STMicroelectronics.stm32h7pxx_dfp.2.0.0-beta.1:STM32H7PxxI_IAR)
    endif()
  endif()
endif()

if(CMSIS_USE_Device_Startup_SRAM_2_0_0_beta_1)  # System Startup for STMicroelectronics STM32H7P Series
  message(DEBUG "Using component Device_Startup_SRAM_2_0_0_beta_1")
  if(STMicroelectronics.stm32h7pxx_dfp.2.0.0-beta.1:STM32H7P)
    target_compile_definitions(STMicroelectronics_stm32h7pxx_dfp_2_0_0_beta_1 INTERFACE -DCMSIS_USE_Device_Startup_SRAM_2_0_0_beta_1=1)
    target_include_directories(STMicroelectronics_stm32h7pxx_dfp_2_0_0_beta_1 INTERFACE Include)
    target_include_directories(STMicroelectronics_stm32h7pxx_dfp_2_0_0_beta_1 INTERFACE Include/)
    target_include_directories(STMicroelectronics_stm32h7pxx_dfp_2_0_0_beta_1 INTERFACE Include/Templates)
    target_sources(STMicroelectronics_stm32h7pxx_dfp_2_0_0_beta_1 INTERFACE Source/Templates/system_stm32h7pxx.c)
    if(STMicroelectronics.stm32h7pxx_dfp.2.0.0-beta.1:STM32H7P4)
      target_sources(STMicroelectronics_stm32h7pxx_dfp_2_0_0_beta_1 INTERFACE Source/startup_stm32h7p4xx.c)
    endif()
    if(STMicroelectronics.stm32h7pxx_dfp.2.0.0-beta.1:STM32H7P5)
      target_sources(STMicroelectronics_stm32h7pxx_dfp_2_0_0_beta_1 INTERFACE Source/startup_stm32h7p5xx.c)
    endif()
    if(STMicroelectronics.stm32h7pxx_dfp.2.0.0-beta.1:STM32H7Pxxx_ARMCC)
    endif()
    if(STMicroelectronics.stm32h7pxx_dfp.2.0.0-beta.1:STM32H7Pxxx_GCC)
      target_link_options(STMicroelectronics_stm32h7pxx_dfp_2_0_0_beta_1 INTERFACE -T${CMAKE_CURRENT_LIST_DIR}/Source/Templates/gcc/linker/stm32h7pxxx_sram.ld)
    endif()
    if(STMicroelectronics.stm32h7pxx_dfp.2.0.0-beta.1:STM32H7Pxxx_IAR)
    endif()
  endif()
endif()

