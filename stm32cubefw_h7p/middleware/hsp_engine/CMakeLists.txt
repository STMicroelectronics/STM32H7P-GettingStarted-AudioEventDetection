# origin-pack: STMicroelectronics::hsp_engine@2.0.0-alpha.1
# created-by: conversion-manager@0.0.64
project(STMicroelectronics_hsp_engine_2_0_0_alpha_1)
cmake_minimum_required(VERSION 3.20)
add_library(STMicroelectronics_hsp_engine_2_0_0_alpha_1 INTERFACE)

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








# Enable all components in this package
if(CMSIS_ENTIRE_STMicroelectronics_hsp_engine_2_0_0_alpha_1)
  set(CMSIS_USE_HSP_HSP_Engine_Core_2_0_0_alpha_1 true)
  set(CMSIS_USE_HSP_HSP_Engine_HSP_ProcList_2_0_0_alpha_1 true)
endif()

# All conditions used by this package

# condition: STMicroelectronics.hsp_engine.2.0.0-alpha.1
# description: 
if((CMSIS_Dname MATCHES "STM32.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13"))
  set(STMicroelectronics.hsp_engine.2.0.0-alpha.1 true)
  message(DEBUG "CMSIS condition STMicroelectronics.hsp_engine.2.0.0-alpha.1 enabled")
endif()


# condition: STMicroelectronics.hsp_engine.2.0.0-alpha.1:ARMCC
# description: 
if(CMSIS_Tcompiler STREQUAL "ARMCC")
  set(STMicroelectronics.hsp_engine.2.0.0-alpha.1:ARMCC true)
  message(DEBUG "CMSIS condition STMicroelectronics.hsp_engine.2.0.0-alpha.1:ARMCC enabled")
endif()


# condition: STMicroelectronics.hsp_engine.2.0.0-alpha.1:GCC
# description: 
if(CMSIS_Tcompiler STREQUAL "GCC")
  set(STMicroelectronics.hsp_engine.2.0.0-alpha.1:GCC true)
  message(DEBUG "CMSIS condition STMicroelectronics.hsp_engine.2.0.0-alpha.1:GCC enabled")
endif()


# condition: STMicroelectronics.hsp_engine.2.0.0-alpha.1:HSP ACC mode
# description: 
set(STMicroelectronics.hsp_engine.2.0.0-alpha.1:HSP_ACC_mode true)
message(DEBUG "CMSIS condition STMicroelectronics.hsp_engine.2.0.0-alpha.1:HSP_ACC_mode enabled")


# condition: STMicroelectronics.hsp_engine.2.0.0-alpha.1:HSP ADCIN feature
# description: 
if((CMSIS_Dname MATCHES "STM32G5DS.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13"))
  set(STMicroelectronics.hsp_engine.2.0.0-alpha.1:HSP_ADCIN_feature true)
  message(DEBUG "CMSIS condition STMicroelectronics.hsp_engine.2.0.0-alpha.1:HSP_ADCIN_feature enabled")
endif()


# condition: STMicroelectronics.hsp_engine.2.0.0-alpha.1:HSP FW RAM v1.6
# description: HSP FW RAM version 1.6
if((CMSIS_Dname MATCHES "STM32H7P.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13"))
  set(STMicroelectronics.hsp_engine.2.0.0-alpha.1:HSP_FW_RAM_v1.6 true)
  message(DEBUG "CMSIS condition STMicroelectronics.hsp_engine.2.0.0-alpha.1:HSP_FW_RAM_v1.6 enabled")
endif()


# condition: STMicroelectronics.hsp_engine.2.0.0-alpha.1:HSP FW ROM v1.1.10
# description: HSP embedded FW ROM v1.1.10
if((CMSIS_Dname MATCHES "STM32H7P.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13"))
  set(STMicroelectronics.hsp_engine.2.0.0-alpha.1:HSP_FW_ROM_v1.1.10 true)
  message(DEBUG "CMSIS condition STMicroelectronics.hsp_engine.2.0.0-alpha.1:HSP_FW_ROM_v1.1.10 enabled")
endif()


# condition: STMicroelectronics.hsp_engine.2.0.0-alpha.1:HSP Modules CNN
# description: 
set(STMicroelectronics.hsp_engine.2.0.0-alpha.1:HSP_Modules_CNN true)
message(DEBUG "CMSIS condition STMicroelectronics.hsp_engine.2.0.0-alpha.1:HSP_Modules_CNN enabled")


# condition: STMicroelectronics.hsp_engine.2.0.0-alpha.1:HSP Modules Complex
# description: 
set(STMicroelectronics.hsp_engine.2.0.0-alpha.1:HSP_Modules_Complex true)
message(DEBUG "CMSIS condition STMicroelectronics.hsp_engine.2.0.0-alpha.1:HSP_Modules_Complex enabled")


# condition: STMicroelectronics.hsp_engine.2.0.0-alpha.1:HSP Modules Conditional
# description: 
set(STMicroelectronics.hsp_engine.2.0.0-alpha.1:HSP_Modules_Conditional true)
message(DEBUG "CMSIS condition STMicroelectronics.hsp_engine.2.0.0-alpha.1:HSP_Modules_Conditional enabled")


# condition: STMicroelectronics.hsp_engine.2.0.0-alpha.1:HSP Modules DSP
# description: 
set(STMicroelectronics.hsp_engine.2.0.0-alpha.1:HSP_Modules_DSP true)
message(DEBUG "CMSIS condition STMicroelectronics.hsp_engine.2.0.0-alpha.1:HSP_Modules_DSP enabled")


# condition: STMicroelectronics.hsp_engine.2.0.0-alpha.1:HSP Modules Filter
# description: 
set(STMicroelectronics.hsp_engine.2.0.0-alpha.1:HSP_Modules_Filter true)
message(DEBUG "CMSIS condition STMicroelectronics.hsp_engine.2.0.0-alpha.1:HSP_Modules_Filter enabled")


# condition: STMicroelectronics.hsp_engine.2.0.0-alpha.1:HSP Modules Matrix
# description: 
set(STMicroelectronics.hsp_engine.2.0.0-alpha.1:HSP_Modules_Matrix true)
message(DEBUG "CMSIS condition STMicroelectronics.hsp_engine.2.0.0-alpha.1:HSP_Modules_Matrix enabled")


# condition: STMicroelectronics.hsp_engine.2.0.0-alpha.1:HSP Modules Scalar
# description: 
set(STMicroelectronics.hsp_engine.2.0.0-alpha.1:HSP_Modules_Scalar true)
message(DEBUG "CMSIS condition STMicroelectronics.hsp_engine.2.0.0-alpha.1:HSP_Modules_Scalar enabled")


# condition: STMicroelectronics.hsp_engine.2.0.0-alpha.1:HSP Modules Transform
# description: 
set(STMicroelectronics.hsp_engine.2.0.0-alpha.1:HSP_Modules_Transform true)
message(DEBUG "CMSIS condition STMicroelectronics.hsp_engine.2.0.0-alpha.1:HSP_Modules_Transform enabled")


# condition: STMicroelectronics.hsp_engine.2.0.0-alpha.1:HSP Modules Vector
# description: 
set(STMicroelectronics.hsp_engine.2.0.0-alpha.1:HSP_Modules_Vector true)
message(DEBUG "CMSIS condition STMicroelectronics.hsp_engine.2.0.0-alpha.1:HSP_Modules_Vector enabled")


# condition: STMicroelectronics.hsp_engine.2.0.0-alpha.1:HSP SEQ mode
# description: 
set(STMicroelectronics.hsp_engine.2.0.0-alpha.1:HSP_SEQ_mode true)
message(DEBUG "CMSIS condition STMicroelectronics.hsp_engine.2.0.0-alpha.1:HSP_SEQ_mode enabled")


# condition: STMicroelectronics.hsp_engine.2.0.0-alpha.1:IAR
# description: 
if(CMSIS_Tcompiler STREQUAL "IAR")
  set(STMicroelectronics.hsp_engine.2.0.0-alpha.1:IAR true)
  message(DEBUG "CMSIS condition STMicroelectronics.hsp_engine.2.0.0-alpha.1:IAR enabled")
endif()

# Files and components in this package
if(CMSIS_USE_HSP_HSP_Engine_Core_2_0_0_alpha_1)  # HSP Engine Common Core
  message(DEBUG "Using component HSP_HSP_Engine_Core_2_0_0_alpha_1")
  target_compile_definitions(STMicroelectronics_hsp_engine_2_0_0_alpha_1 INTERFACE -DCMSIS_USE_HSP_HSP_Engine_Core_2_0_0_alpha_1=1)
  target_include_directories(STMicroelectronics_hsp_engine_2_0_0_alpha_1 INTERFACE common/core/)
  target_include_directories(STMicroelectronics_hsp_engine_2_0_0_alpha_1 INTERFACE common/modules/)
  target_include_directories(STMicroelectronics_hsp_engine_2_0_0_alpha_1 INTERFACE common/modules/direct_lib/)
  target_include_directories(STMicroelectronics_hsp_engine_2_0_0_alpha_1 INTERFACE common/modules/firmware/)
  target_include_directories(STMicroelectronics_hsp_engine_2_0_0_alpha_1 INTERFACE common/utilities/)
  target_include_directories(STMicroelectronics_hsp_engine_2_0_0_alpha_1 INTERFACE interfaces/)
  target_sources(STMicroelectronics_hsp_engine_2_0_0_alpha_1 INTERFACE common/core/hsp_bram.c)
  target_sources(STMicroelectronics_hsp_engine_2_0_0_alpha_1 INTERFACE common/core/hsp_core.c)
  target_sources(STMicroelectronics_hsp_engine_2_0_0_alpha_1 INTERFACE common/modules/direct_lib/hsp_direct_command.c)
  target_sources(STMicroelectronics_hsp_engine_2_0_0_alpha_1 INTERFACE common/utilities/hsp_memcpy.c)
  target_sources(STMicroelectronics_hsp_engine_2_0_0_alpha_1 INTERFACE interfaces/hsp_bram_if.c)
  target_sources(STMicroelectronics_hsp_engine_2_0_0_alpha_1 INTERFACE interfaces/hsp_hw_if.c)
  if(STMicroelectronics.hsp_engine.2.0.0-alpha.1:ARMCC)
    target_sources(STMicroelectronics_hsp_engine_2_0_0_alpha_1 INTERFACE common/utilities/portable/Keil/st_hsp_memcpy32.s)
  endif()
  if(STMicroelectronics.hsp_engine.2.0.0-alpha.1:GCC)
    target_sources(STMicroelectronics_hsp_engine_2_0_0_alpha_1 INTERFACE common/utilities/portable/GCC/st_hsp_memcpy32.S)
  endif()
  if(STMicroelectronics.hsp_engine.2.0.0-alpha.1:HSP_FW_RAM_v1.6)
    target_include_directories(STMicroelectronics_hsp_engine_2_0_0_alpha_1 INTERFACE common/modules/firmware/crom_1.1.10/cram_1.6/)
    target_sources(STMicroelectronics_hsp_engine_2_0_0_alpha_1 INTERFACE common/modules/firmware/crom_1.1.10/cram_1.6/hsp_fw_ram.c)
  endif()
  if(STMicroelectronics.hsp_engine.2.0.0-alpha.1:HSP_Modules_CNN)
    target_include_directories(STMicroelectronics_hsp_engine_2_0_0_alpha_1 INTERFACE common/modules/cnn_lib/)
    target_sources(STMicroelectronics_hsp_engine_2_0_0_alpha_1 INTERFACE common/modules/cnn_lib/hsp_cnn.c)
  endif()
  if(STMicroelectronics.hsp_engine.2.0.0-alpha.1:HSP_Modules_DSP)
    target_include_directories(STMicroelectronics_hsp_engine_2_0_0_alpha_1 INTERFACE common/modules/dsp_lib/)
    target_sources(STMicroelectronics_hsp_engine_2_0_0_alpha_1 INTERFACE common/modules/dsp_lib/hsp_dsp.c)
  endif()
  if(STMicroelectronics.hsp_engine.2.0.0-alpha.1:HSP_SEQ_mode)
    target_sources(STMicroelectronics_hsp_engine_2_0_0_alpha_1 INTERFACE interfaces/hsp_utilities.c)
  endif()
  if(STMicroelectronics.hsp_engine.2.0.0-alpha.1:IAR)
    target_sources(STMicroelectronics_hsp_engine_2_0_0_alpha_1 INTERFACE common/utilities/portable/IAR/st_hsp_memcpy32.s)
  endif()
endif()

if(CMSIS_USE_HSP_HSP_Engine_HSP_ProcList_2_0_0_alpha_1)  # HSP Engine Common Modules Proclist
  message(DEBUG "Using component HSP_HSP_Engine_HSP_ProcList_2_0_0_alpha_1")
  if(STMicroelectronics.hsp_engine.2.0.0-alpha.1:HSP_SEQ_mode)
    target_compile_definitions(STMicroelectronics_hsp_engine_2_0_0_alpha_1 INTERFACE -DCMSIS_USE_HSP_HSP_Engine_HSP_ProcList_2_0_0_alpha_1=1)
    target_include_directories(STMicroelectronics_hsp_engine_2_0_0_alpha_1 INTERFACE common/modules/)
    target_include_directories(STMicroelectronics_hsp_engine_2_0_0_alpha_1 INTERFACE common/modules/proclist_lib/)
    target_include_directories(STMicroelectronics_hsp_engine_2_0_0_alpha_1 INTERFACE common/proclist/)
    target_sources(STMicroelectronics_hsp_engine_2_0_0_alpha_1 INTERFACE common/proclist/hsp_proclist.c)
    if(STMicroelectronics.hsp_engine.2.0.0-alpha.1:HSP_Modules_Complex)
      target_sources(STMicroelectronics_hsp_engine_2_0_0_alpha_1 INTERFACE common/modules/proclist_lib/hsp_proclist_complex.c)
    endif()
    if(STMicroelectronics.hsp_engine.2.0.0-alpha.1:HSP_Modules_Conditional)
      target_sources(STMicroelectronics_hsp_engine_2_0_0_alpha_1 INTERFACE common/modules/proclist_lib/hsp_proclist_conditional.c)
    endif()
    if(STMicroelectronics.hsp_engine.2.0.0-alpha.1:HSP_Modules_Filter)
      target_sources(STMicroelectronics_hsp_engine_2_0_0_alpha_1 INTERFACE common/modules/proclist_lib/hsp_proclist_filter.c)
    endif()
    if(STMicroelectronics.hsp_engine.2.0.0-alpha.1:HSP_Modules_Matrix)
      target_sources(STMicroelectronics_hsp_engine_2_0_0_alpha_1 INTERFACE common/modules/proclist_lib/hsp_proclist_matrix.c)
    endif()
    if(STMicroelectronics.hsp_engine.2.0.0-alpha.1:HSP_Modules_Scalar)
      target_sources(STMicroelectronics_hsp_engine_2_0_0_alpha_1 INTERFACE common/modules/proclist_lib/hsp_proclist_scalar.c)
    endif()
    if(STMicroelectronics.hsp_engine.2.0.0-alpha.1:HSP_Modules_Transform)
      target_sources(STMicroelectronics_hsp_engine_2_0_0_alpha_1 INTERFACE common/modules/proclist_lib/hsp_proclist_transform.c)
    endif()
    if(STMicroelectronics.hsp_engine.2.0.0-alpha.1:HSP_Modules_Vector)
      target_sources(STMicroelectronics_hsp_engine_2_0_0_alpha_1 INTERFACE common/modules/proclist_lib/hsp_proclist_vector.c)
    endif()
  endif()
endif()

