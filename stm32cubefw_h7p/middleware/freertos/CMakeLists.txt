# origin-pack: STMicroelectronics::freertos@0.8.0
# created-by: conversion-manager@0.0.65
project(STMicroelectronics_freertos_0_8_0)
cmake_minimum_required(VERSION 3.20)
add_library(STMicroelectronics_freertos_0_8_0 INTERFACE)

# List of all CMSIS properties that influence conditions for this package
if(NOT DEFINED CMSIS_Dcore)
  set(CMSIS_Dcore "CMSIS_Dcore not set")
  message(DEBUG "CMSIS_Dcore is not set to any value")
endif()

if(NOT DEFINED CMSIS_Dname)
  set(CMSIS_Dname "CMSIS_Dname not set")
  message(DEBUG "CMSIS_Dname is not set to any value")
endif()

if(NOT DEFINED CMSIS_Dsecure)
  set(CMSIS_Dsecure "CMSIS_Dsecure not set")
  message(DEBUG "CMSIS_Dsecure is not set to any value")
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








# Enable all components in this package
if(CMSIS_ENTIRE_STMicroelectronics_freertos_0_8_0)
  set(CMSIS_USE_RTOS_FreeRTOS_Core_11_2_0 true)
  set(CMSIS_USE_RTOS_FreeRTOS_Stream_Buffer_11_2_0 true)
  set(CMSIS_USE_RTOS_FreeRTOS_MemMang_Heap_1_11_2_0 true)
  set(CMSIS_USE_RTOS_FreeRTOS_MemMang_Heap_2_11_2_0 true)
  set(CMSIS_USE_RTOS_FreeRTOS_MemMang_Heap_3_11_2_0 true)
  set(CMSIS_USE_RTOS_FreeRTOS_MemMang_Heap_4_11_2_0 true)
  set(CMSIS_USE_RTOS_FreeRTOS_MemMang_Heap_5_11_2_0 true)
endif()

# All conditions used by this package

# condition: STMicroelectronics.freertos.0.8.0
# description: 
if((CMSIS_Dname MATCHES "STM32.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13"))
  set(STMicroelectronics.freertos.0.8.0 true)
  message(DEBUG "CMSIS condition STMicroelectronics.freertos.0.8.0 enabled")
endif()


# condition: STMicroelectronics.freertos.0.8.0:CM0 GCC Condition
# description: Cortex M0 / GCC compiler
if((CMSIS_Dcore STREQUAL "Cortex-M0+" AND (CMSIS_Tcompiler STREQUAL "GCC" OR CMSIS_Tcompiler STREQUAL "ARMCC")))
  set(STMicroelectronics.freertos.0.8.0:CM0_GCC_Condition true)
  message(DEBUG "CMSIS condition STMicroelectronics.freertos.0.8.0:CM0_GCC_Condition enabled")
endif()


# condition: STMicroelectronics.freertos.0.8.0:CM0 IAR Condition
# description: Cortex M0 / IAR compiler
if((CMSIS_Dcore STREQUAL "Cortex-M0+" AND CMSIS_Tcompiler STREQUAL "IAR"))
  set(STMicroelectronics.freertos.0.8.0:CM0_IAR_Condition true)
  message(DEBUG "CMSIS condition STMicroelectronics.freertos.0.8.0:CM0_IAR_Condition enabled")
endif()


# condition: STMicroelectronics.freertos.0.8.0:CM33 TZ Disabled GCC Condition
# description: Cortex M33 TZ Disabled / GCC compiler
if((CMSIS_Dcore STREQUAL "Cortex-M33" AND CMSIS_Dsecure STREQUAL "TZ-disabled" AND (CMSIS_Tcompiler STREQUAL "GCC" OR CMSIS_Tcompiler STREQUAL "ARMCC")))
  set(STMicroelectronics.freertos.0.8.0:CM33_TZ_Disabled_GCC_Condition true)
  message(DEBUG "CMSIS condition STMicroelectronics.freertos.0.8.0:CM33_TZ_Disabled_GCC_Condition enabled")
endif()


# condition: STMicroelectronics.freertos.0.8.0:CM33 TZ Disabled IAR Condition
# description: Cortex M33 TZ Disabled / IAR compiler
if((CMSIS_Dcore STREQUAL "Cortex-M33" AND CMSIS_Dsecure STREQUAL "TZ-disabled" AND CMSIS_Tcompiler STREQUAL "IAR"))
  set(STMicroelectronics.freertos.0.8.0:CM33_TZ_Disabled_IAR_Condition true)
  message(DEBUG "CMSIS condition STMicroelectronics.freertos.0.8.0:CM33_TZ_Disabled_IAR_Condition enabled")
endif()


# condition: STMicroelectronics.freertos.0.8.0:CM7 CM4 GCC Condition
# description: Cortex M7 / GCC compiler
if(((CMSIS_Dcore STREQUAL "Cortex-M7" OR CMSIS_Dcore STREQUAL "Cortex-M4") AND 
   (CMSIS_Tcompiler STREQUAL "GCC" OR CMSIS_Tcompiler STREQUAL "ARMCC")))
  set(STMicroelectronics.freertos.0.8.0:CM7_CM4_GCC_Condition true)
  message(DEBUG "CMSIS condition STMicroelectronics.freertos.0.8.0:CM7_CM4_GCC_Condition enabled")
endif()


# condition: STMicroelectronics.freertos.0.8.0:CM7 CM4 IAR Condition
# description: Cortex M7 (newer than r0p1) and CM4 / IAR compiler
if(((CMSIS_Dcore STREQUAL "Cortex-M7" OR CMSIS_Dcore STREQUAL "Cortex-M4") AND 
   CMSIS_Tcompiler STREQUAL "IAR"))
  set(STMicroelectronics.freertos.0.8.0:CM7_CM4_IAR_Condition true)
  message(DEBUG "CMSIS condition STMicroelectronics.freertos.0.8.0:CM7_CM4_IAR_Condition enabled")
endif()


# condition: STMicroelectronics.freertos.0.8.0:CM85 GCC Condition
# description: Cortex M85 / GCC compiler
if(((CMSIS_Dsecure STREQUAL "Secure" OR CMSIS_Dsecure STREQUAL "Secure-only") AND 
   (CMSIS_Dcore STREQUAL "Cortex-M85" AND (CMSIS_Tcompiler STREQUAL "GCC" OR CMSIS_Tcompiler STREQUAL "ARMCC"))))
  set(STMicroelectronics.freertos.0.8.0:CM85_GCC_Condition true)
  message(DEBUG "CMSIS condition STMicroelectronics.freertos.0.8.0:CM85_GCC_Condition enabled")
endif()


# condition: STMicroelectronics.freertos.0.8.0:CM85 IAR Condition
# description: Cortex M85 / IAR compiler
if(((CMSIS_Dsecure STREQUAL "Secure" OR CMSIS_Dsecure STREQUAL "Secure-only") AND 
   (CMSIS_Dcore STREQUAL "Cortex-M85" AND CMSIS_Tcompiler STREQUAL "IAR")))
  set(STMicroelectronics.freertos.0.8.0:CM85_IAR_Condition true)
  message(DEBUG "CMSIS condition STMicroelectronics.freertos.0.8.0:CM85_IAR_Condition enabled")
endif()


# condition: STMicroelectronics.freertos.0.8.0:FreeRTOS Init condition
# description: STMicroelectronics FreeRTOS Init
set(STMicroelectronics.freertos.0.8.0:FreeRTOS_Init_condition true)
message(DEBUG "CMSIS condition STMicroelectronics.freertos.0.8.0:FreeRTOS_Init_condition enabled")


# condition: STMicroelectronics.freertos.0.8.0:FreeRTOS Memory Heap condition
# description:  Memory Heap condition 
set(STMicroelectronics.freertos.0.8.0:FreeRTOS_Memory_Heap_condition true)
message(DEBUG "CMSIS condition STMicroelectronics.freertos.0.8.0:FreeRTOS_Memory_Heap_condition enabled")


# condition: STMicroelectronics.freertos.0.8.0:GCC Compiler Condition
# description: Combined condition to check for GCC and AC6 compilers
if((CMSIS_Tcompiler STREQUAL "GCC" OR CMSIS_Tcompiler STREQUAL "ARMCC"))
  set(STMicroelectronics.freertos.0.8.0:GCC_Compiler_Condition true)
  message(DEBUG "CMSIS condition STMicroelectronics.freertos.0.8.0:GCC_Compiler_Condition enabled")
endif()


# condition: STMicroelectronics.freertos.0.8.0:Stream Buffers condition
# description: Stream Buffers condition
set(STMicroelectronics.freertos.0.8.0:Stream_Buffers_condition true)
message(DEBUG "CMSIS condition STMicroelectronics.freertos.0.8.0:Stream_Buffers_condition enabled")

# Files and components in this package
if(CMSIS_USE_RTOS_FreeRTOS_Core_11_2_0)  # FreeRTOS Core component 
  message(DEBUG "Using component RTOS_FreeRTOS_Core_11_2_0")
  if(STMicroelectronics.freertos.0.8.0:FreeRTOS_Memory_Heap_condition)
    target_compile_definitions(STMicroelectronics_freertos_0_8_0 INTERFACE -DCMSIS_USE_RTOS_FreeRTOS_Core_11_2_0=1)
    target_include_directories(STMicroelectronics_freertos_0_8_0 INTERFACE include)
    target_include_directories(STMicroelectronics_freertos_0_8_0 INTERFACE include/)
    target_sources(STMicroelectronics_freertos_0_8_0 INTERFACE croutine.c)
    target_sources(STMicroelectronics_freertos_0_8_0 INTERFACE event_groups.c)
    target_sources(STMicroelectronics_freertos_0_8_0 INTERFACE list.c)
    target_sources(STMicroelectronics_freertos_0_8_0 INTERFACE queue.c)
    target_sources(STMicroelectronics_freertos_0_8_0 INTERFACE tasks.c)
    target_sources(STMicroelectronics_freertos_0_8_0 INTERFACE timers.c)
    if(STMicroelectronics.freertos.0.8.0:CM0_GCC_Condition)
      target_include_directories(STMicroelectronics_freertos_0_8_0 INTERFACE portable/GCC/ARM_CM0)
      target_include_directories(STMicroelectronics_freertos_0_8_0 INTERFACE portable/GCC/ARM_CM0/)
      target_sources(STMicroelectronics_freertos_0_8_0 INTERFACE portable/GCC/ARM_CM0/mpu_wrappers_v2_asm.c)
      target_sources(STMicroelectronics_freertos_0_8_0 INTERFACE portable/GCC/ARM_CM0/port.c)
      target_sources(STMicroelectronics_freertos_0_8_0 INTERFACE portable/GCC/ARM_CM0/portasm.c)
    endif()
    if(STMicroelectronics.freertos.0.8.0:CM0_IAR_Condition)
      target_include_directories(STMicroelectronics_freertos_0_8_0 INTERFACE portable/IAR/ARM_CM0)
      target_include_directories(STMicroelectronics_freertos_0_8_0 INTERFACE portable/IAR/ARM_CM0/)
      target_sources(STMicroelectronics_freertos_0_8_0 INTERFACE portable/IAR/ARM_CM0/port.c)
      target_sources(STMicroelectronics_freertos_0_8_0 INTERFACE portable/IAR/ARM_CM0/portasm.s)
    endif()
    if(STMicroelectronics.freertos.0.8.0:CM33_TZ_Disabled_GCC_Condition)
      target_include_directories(STMicroelectronics_freertos_0_8_0 INTERFACE portable/GCC/ARM_CM33_NTZ/non_secure)
      target_include_directories(STMicroelectronics_freertos_0_8_0 INTERFACE portable/GCC/ARM_CM33_NTZ/non_secure/)
      target_sources(STMicroelectronics_freertos_0_8_0 INTERFACE portable/GCC/ARM_CM33_NTZ/non_secure/mpu_wrappers_v2_asm.c)
      target_sources(STMicroelectronics_freertos_0_8_0 INTERFACE portable/GCC/ARM_CM33_NTZ/non_secure/port.c)
      target_sources(STMicroelectronics_freertos_0_8_0 INTERFACE portable/GCC/ARM_CM33_NTZ/non_secure/portasm.c)
    endif()
    if(STMicroelectronics.freertos.0.8.0:CM33_TZ_Disabled_IAR_Condition)
      target_include_directories(STMicroelectronics_freertos_0_8_0 INTERFACE portable/IAR/ARM_CM33_NTZ/non_secure)
      target_include_directories(STMicroelectronics_freertos_0_8_0 INTERFACE portable/IAR/ARM_CM33_NTZ/non_secure/)
      target_sources(STMicroelectronics_freertos_0_8_0 INTERFACE portable/IAR/ARM_CM33_NTZ/non_secure/port.c)
      target_sources(STMicroelectronics_freertos_0_8_0 INTERFACE portable/IAR/ARM_CM33_NTZ/non_secure/portasm.s)
      target_sources(STMicroelectronics_freertos_0_8_0 INTERFACE portable/IAR/ARM_CM33_NTZ/non_secure/mpu_wrappers_v2_asm.S)
    endif()
    if(STMicroelectronics.freertos.0.8.0:CM7_CM4_GCC_Condition)
      target_include_directories(STMicroelectronics_freertos_0_8_0 INTERFACE portable/GCC/ARM_CM4F)
      target_include_directories(STMicroelectronics_freertos_0_8_0 INTERFACE portable/GCC/ARM_CM4F/)
      target_sources(STMicroelectronics_freertos_0_8_0 INTERFACE portable/GCC/ARM_CM4F/port.c)
    endif()
    if(STMicroelectronics.freertos.0.8.0:CM7_CM4_IAR_Condition)
      target_include_directories(STMicroelectronics_freertos_0_8_0 INTERFACE portable/IAR/ARM_CM4F)
      target_include_directories(STMicroelectronics_freertos_0_8_0 INTERFACE portable/IAR/ARM_CM4F/)
      target_sources(STMicroelectronics_freertos_0_8_0 INTERFACE portable/IAR/ARM_CM4F/port.c)
      target_sources(STMicroelectronics_freertos_0_8_0 INTERFACE portable/IAR/ARM_CM4F/portasm.s)
    endif()
    if(STMicroelectronics.freertos.0.8.0:CM85_GCC_Condition)
      target_include_directories(STMicroelectronics_freertos_0_8_0 INTERFACE portable/GCC/ARM_CM85_NTZ/non_secure)
      target_include_directories(STMicroelectronics_freertos_0_8_0 INTERFACE portable/GCC/ARM_CM85_NTZ/non_secure/)
      target_sources(STMicroelectronics_freertos_0_8_0 INTERFACE portable/GCC/ARM_CM85_NTZ/non_secure/mpu_wrappers_v2_asm.c)
      target_sources(STMicroelectronics_freertos_0_8_0 INTERFACE portable/GCC/ARM_CM85_NTZ/non_secure/port.c)
      target_sources(STMicroelectronics_freertos_0_8_0 INTERFACE portable/GCC/ARM_CM85_NTZ/non_secure/portasm.c)
    endif()
    if(STMicroelectronics.freertos.0.8.0:CM85_IAR_Condition)
      target_include_directories(STMicroelectronics_freertos_0_8_0 INTERFACE portable/IAR/ARM_CM85_NTZ/non_secure)
      target_include_directories(STMicroelectronics_freertos_0_8_0 INTERFACE portable/IAR/ARM_CM85_NTZ/non_secure/)
      target_sources(STMicroelectronics_freertos_0_8_0 INTERFACE portable/IAR/ARM_CM85_NTZ/non_secure/port.c)
      target_sources(STMicroelectronics_freertos_0_8_0 INTERFACE portable/IAR/ARM_CM85_NTZ/non_secure/mpu_wrappers_v2_asm.S)
      target_sources(STMicroelectronics_freertos_0_8_0 INTERFACE portable/IAR/ARM_CM85_NTZ/non_secure/portasm.s)
    endif()
  endif()
endif()

if(CMSIS_USE_RTOS_FreeRTOS_Stream_Buffer_11_2_0)  # FreeRTOS Stream Buffer component 
  message(DEBUG "Using component RTOS_FreeRTOS_Stream_Buffer_11_2_0")
  if(STMicroelectronics.freertos.0.8.0:Stream_Buffers_condition)
    target_compile_definitions(STMicroelectronics_freertos_0_8_0 INTERFACE -DCMSIS_USE_RTOS_FreeRTOS_Stream_Buffer_11_2_0=1)
    target_include_directories(STMicroelectronics_freertos_0_8_0 INTERFACE include/)
    target_sources(STMicroelectronics_freertos_0_8_0 INTERFACE stream_buffer.c)
  endif()
endif()

if(CMSIS_USE_RTOS_FreeRTOS_MemMang_Heap_1_11_2_0)  # FreeRTOS  Memory Heap (Heap 1) component 
  message(DEBUG "Using component RTOS_FreeRTOS_MemMang_Heap_1_11_2_0")
  if(STMicroelectronics.freertos.0.8.0:FreeRTOS_Memory_Heap_condition)
    target_compile_definitions(STMicroelectronics_freertos_0_8_0 INTERFACE -DCMSIS_USE_RTOS_FreeRTOS_MemMang_Heap_1_11_2_0=1)
    target_include_directories(STMicroelectronics_freertos_0_8_0 INTERFACE include/)
    target_sources(STMicroelectronics_freertos_0_8_0 INTERFACE portable/MemMang/heap_1.c)
  endif()
endif()

if(CMSIS_USE_RTOS_FreeRTOS_MemMang_Heap_2_11_2_0)  # FreeRTOS  Memory Heap (Heap 2) component 
  message(DEBUG "Using component RTOS_FreeRTOS_MemMang_Heap_2_11_2_0")
  if(STMicroelectronics.freertos.0.8.0:FreeRTOS_Memory_Heap_condition)
    target_compile_definitions(STMicroelectronics_freertos_0_8_0 INTERFACE -DCMSIS_USE_RTOS_FreeRTOS_MemMang_Heap_2_11_2_0=1)
    target_include_directories(STMicroelectronics_freertos_0_8_0 INTERFACE include/)
    target_sources(STMicroelectronics_freertos_0_8_0 INTERFACE portable/MemMang/heap_2.c)
  endif()
endif()

if(CMSIS_USE_RTOS_FreeRTOS_MemMang_Heap_3_11_2_0)  # FreeRTOS  Memory Heap (Heap 3) component 
  message(DEBUG "Using component RTOS_FreeRTOS_MemMang_Heap_3_11_2_0")
  if(STMicroelectronics.freertos.0.8.0:FreeRTOS_Memory_Heap_condition)
    target_compile_definitions(STMicroelectronics_freertos_0_8_0 INTERFACE -DCMSIS_USE_RTOS_FreeRTOS_MemMang_Heap_3_11_2_0=1)
    target_include_directories(STMicroelectronics_freertos_0_8_0 INTERFACE include/)
    target_sources(STMicroelectronics_freertos_0_8_0 INTERFACE portable/MemMang/heap_3.c)
  endif()
endif()

if(CMSIS_USE_RTOS_FreeRTOS_MemMang_Heap_4_11_2_0)  # FreeRTOS  Memory Heap (Heap 4) component 
  message(DEBUG "Using component RTOS_FreeRTOS_MemMang_Heap_4_11_2_0")
  if(STMicroelectronics.freertos.0.8.0:FreeRTOS_Memory_Heap_condition)
    target_compile_definitions(STMicroelectronics_freertos_0_8_0 INTERFACE -DCMSIS_USE_RTOS_FreeRTOS_MemMang_Heap_4_11_2_0=1)
    target_include_directories(STMicroelectronics_freertos_0_8_0 INTERFACE include/)
    target_sources(STMicroelectronics_freertos_0_8_0 INTERFACE portable/MemMang/heap_4.c)
  endif()
endif()

if(CMSIS_USE_RTOS_FreeRTOS_MemMang_Heap_5_11_2_0)  # FreeRTOS  Memory Heap (Heap 5) component 
  message(DEBUG "Using component RTOS_FreeRTOS_MemMang_Heap_5_11_2_0")
  if(STMicroelectronics.freertos.0.8.0:FreeRTOS_Memory_Heap_condition)
    target_compile_definitions(STMicroelectronics_freertos_0_8_0 INTERFACE -DCMSIS_USE_RTOS_FreeRTOS_MemMang_Heap_5_11_2_0=1)
    target_include_directories(STMicroelectronics_freertos_0_8_0 INTERFACE include/)
    target_sources(STMicroelectronics_freertos_0_8_0 INTERFACE portable/MemMang/heap_5.c)
  endif()
endif()

