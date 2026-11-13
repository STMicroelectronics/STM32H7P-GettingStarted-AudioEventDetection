# origin-pack: generated_STMicroelectronics::hsp_engine@0.0.1
# file-format: 1.0.0
project(generated_STMicroelectronics_hsp_engine_0_0_1)
cmake_minimum_required(VERSION 3.30)
add_library(generated_STMicroelectronics_hsp_engine_0_0_1 INTERFACE)

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

if(NOT DEFINED CMSIS_Toptions)
  set(CMSIS_Toptions "CMSIS_Toptions not set")
  message(DEBUG "CMSIS_Toptions is not set to any value")
endif()


# Device specific defined symbols








# Enable all components in this package
if(CMSIS_ENTIRE_generated_STMicroelectronics_hsp_engine_0_0_1)
  list(APPEND CMSIS_COMPONENTS_LIST "Cvendor:STMicroelectronics#Cclass:Utility#Cgroup:STM32CubeMX2 Config#Csub:HSP Engine#Cversion:2.0.0#generated:true")
endif()

# All conditions used by this package

# condition: generated_STMicroelectronics.hsp_engine.0.0.1:ARMASM
# description: 
if((CMSIS_Tcompiler STREQUAL "ARMCC" AND CMSIS_Toptions STREQUAL "AC5"))
  set(generated_STMicroelectronics.hsp_engine.0.0.1_ARMASM "1")
  message(DEBUG "CMSIS condition generated_STMicroelectronics.hsp_engine.0.0.1_ARMASM enabled")
else()
  set(generated_STMicroelectronics.hsp_engine.0.0.1_ARMASM 0)
endif()


# condition: generated_STMicroelectronics.hsp_engine.0.0.1:ARMCLANG
# description: 
if((CMSIS_Tcompiler STREQUAL "ARMCC" AND CMSIS_Toptions STREQUAL "AC6"))
  set(generated_STMicroelectronics.hsp_engine.0.0.1_ARMCLANG "1")
  message(DEBUG "CMSIS condition generated_STMicroelectronics.hsp_engine.0.0.1_ARMCLANG enabled")
else()
  set(generated_STMicroelectronics.hsp_engine.0.0.1_ARMCLANG 0)
endif()


# condition: generated_STMicroelectronics.hsp_engine.0.0.1:GCC
# description: 
if(CMSIS_Tcompiler STREQUAL "GCC")
  set(generated_STMicroelectronics.hsp_engine.0.0.1_GCC "1")
  message(DEBUG "CMSIS condition generated_STMicroelectronics.hsp_engine.0.0.1_GCC enabled")
else()
  set(generated_STMicroelectronics.hsp_engine.0.0.1_GCC 0)
endif()


# condition: generated_STMicroelectronics.hsp_engine.0.0.1:GNU ASM
# description: 
if((CMSIS_Tcompiler STREQUAL "GCC" OR (CMSIS_Tcompiler STREQUAL "ARMCC" AND CMSIS_Toptions STREQUAL "AC6")))
  set(generated_STMicroelectronics.hsp_engine.0.0.1_GNU_ASM "1")
  message(DEBUG "CMSIS condition generated_STMicroelectronics.hsp_engine.0.0.1_GNU_ASM enabled")
else()
  set(generated_STMicroelectronics.hsp_engine.0.0.1_GNU_ASM 0)
endif()


# condition: generated_STMicroelectronics.hsp_engine.0.0.1:HSP Engine HAL Interfaces
# description: HSP Engine Interfaces build with HSP HAL Driver
set(generated_STMicroelectronics.hsp_engine.0.0.1_HSP_Engine_HAL_Interfaces "$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 HAL#.*Csub:HSP(#.*|$)>,>>")
message(DEBUG "CMSIS condition generated_STMicroelectronics.hsp_engine.0.0.1_HSP_Engine_HAL_Interfaces enabled")


# condition: generated_STMicroelectronics.hsp_engine.0.0.1:HSP Engine Modules CNN
# description: 
set(generated_STMicroelectronics.hsp_engine.0.0.1_HSP_Engine_Modules_CNN "1")
message(DEBUG "CMSIS condition generated_STMicroelectronics.hsp_engine.0.0.1_HSP_Engine_Modules_CNN enabled")


# condition: generated_STMicroelectronics.hsp_engine.0.0.1:HSP Engine Modules CNN DMA
# description: 
if((CMSIS_Dname MATCHES "STM32G5[CDRS].*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13"))
  set(generated_STMicroelectronics.hsp_engine.0.0.1_HSP_Engine_Modules_CNN_DMA "1")
  message(DEBUG "CMSIS condition generated_STMicroelectronics.hsp_engine.0.0.1_HSP_Engine_Modules_CNN_DMA enabled")
else()
  set(generated_STMicroelectronics.hsp_engine.0.0.1_HSP_Engine_Modules_CNN_DMA 0)
endif()


# condition: generated_STMicroelectronics.hsp_engine.0.0.1:HSP Engine Modules DSP
# description: 
if((CMSIS_Dname MATCHES "STM32.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13"))
  set(generated_STMicroelectronics.hsp_engine.0.0.1_HSP_Engine_Modules_DSP "1")
  message(DEBUG "CMSIS condition generated_STMicroelectronics.hsp_engine.0.0.1_HSP_Engine_Modules_DSP enabled")
else()
  set(generated_STMicroelectronics.hsp_engine.0.0.1_HSP_Engine_Modules_DSP 0)
endif()


# condition: generated_STMicroelectronics.hsp_engine.0.0.1:HSP Engine Modules Proclist Digital Control
# description: 
if((CMSIS_Dname MATCHES "STM32G5[CDRS].*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13"))
  set(generated_STMicroelectronics.hsp_engine.0.0.1_HSP_Engine_Modules_Proclist_Digital_Control "1")
  message(DEBUG "CMSIS condition generated_STMicroelectronics.hsp_engine.0.0.1_HSP_Engine_Modules_Proclist_Digital_Control enabled")
else()
  set(generated_STMicroelectronics.hsp_engine.0.0.1_HSP_Engine_Modules_Proclist_Digital_Control 0)
endif()


# condition: generated_STMicroelectronics.hsp_engine.0.0.1:HSP FW ROM v1.1.10
# description: HSP embedded FW ROM v1.1.10
if((CMSIS_Dname MATCHES "STM32H7P.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13"))
  set(generated_STMicroelectronics.hsp_engine.0.0.1_HSP_FW_ROM_v1.1.10 "1")
  message(DEBUG "CMSIS condition generated_STMicroelectronics.hsp_engine.0.0.1_HSP_FW_ROM_v1.1.10 enabled")
else()
  set(generated_STMicroelectronics.hsp_engine.0.0.1_HSP_FW_ROM_v1.1.10 0)
endif()


# condition: generated_STMicroelectronics.hsp_engine.0.0.1:HSP FW ROM v2.1.4
# description: HSP embedded FW ROM v2.1.4
if((CMSIS_Dname MATCHES "STM32G5[CDRS].*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13"))
  set(generated_STMicroelectronics.hsp_engine.0.0.1_HSP_FW_ROM_v2.1.4 "1")
  message(DEBUG "CMSIS condition generated_STMicroelectronics.hsp_engine.0.0.1_HSP_FW_ROM_v2.1.4 enabled")
else()
  set(generated_STMicroelectronics.hsp_engine.0.0.1_HSP_FW_ROM_v2.1.4 0)
endif()


# condition: generated_STMicroelectronics.hsp_engine.0.0.1:HSP Sequencer mode
# description: 
set(generated_STMicroelectronics.hsp_engine.0.0.1_HSP_Sequencer_mode "1")
message(DEBUG "CMSIS condition generated_STMicroelectronics.hsp_engine.0.0.1_HSP_Sequencer_mode enabled")


# condition: generated_STMicroelectronics.hsp_engine.0.0.1:IAR
# description: 
if(CMSIS_Tcompiler STREQUAL "IAR")
  set(generated_STMicroelectronics.hsp_engine.0.0.1_IAR "1")
  message(DEBUG "CMSIS condition generated_STMicroelectronics.hsp_engine.0.0.1_IAR enabled")
else()
  set(generated_STMicroelectronics.hsp_engine.0.0.1_IAR 0)
endif()


# condition: generated_STMicroelectronics.hsp_engine.0.0.1:MX HSP Engine needed components
# description: Mandatory files to include in code generation of HSP Engine Middleware
set(generated_STMicroelectronics.hsp_engine.0.0.1_MX_HSP_Engine_needed_components "$<AND:$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Utility#.*Cgroup:HSP Engine#.*Csub:Core(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Utility#.*Cgroup:HSP Engine#.*Csub:Interfaces(#.*|$)>,>>>")
message(DEBUG "CMSIS condition generated_STMicroelectronics.hsp_engine.0.0.1_MX_HSP_Engine_needed_components enabled")


# condition: generated_STMicroelectronics.hsp_engine.0.0.1:ROM v1.1.10 AND RAM v1.7
# description: HSP FW ROM version 1.1.10 AND RAM version 1.7
if((CMSIS_Dname MATCHES "STM32H7P.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13"))
  set(generated_STMicroelectronics.hsp_engine.0.0.1_ROM_v1.1.10_AND_RAM_v1.7 "1")
  message(DEBUG "CMSIS condition generated_STMicroelectronics.hsp_engine.0.0.1_ROM_v1.1.10_AND_RAM_v1.7 enabled")
else()
  set(generated_STMicroelectronics.hsp_engine.0.0.1_ROM_v1.1.10_AND_RAM_v1.7 0)
endif()


# condition: generated_STMicroelectronics.hsp_engine.0.0.1:ROM v2.1.4 AND RAM v1.0
# description: HSP FW ROM version 2.1.4 AND RAM version 1.0
if((CMSIS_Dname MATCHES "STM32G5[CDRS].*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13"))
  set(generated_STMicroelectronics.hsp_engine.0.0.1_ROM_v2.1.4_AND_RAM_v1.0 "1")
  message(DEBUG "CMSIS condition generated_STMicroelectronics.hsp_engine.0.0.1_ROM_v2.1.4_AND_RAM_v1.0 enabled")
else()
  set(generated_STMicroelectronics.hsp_engine.0.0.1_ROM_v2.1.4_AND_RAM_v1.0 0)
endif()

# Files and components in this package
if("Cvendor:STMicroelectronics#Cclass:Utility#Cgroup:STM32CubeMX2 Config#Csub:HSP Engine#Cversion:2.0.0#generated:true" IN_LIST CMSIS_COMPONENTS_LIST)  # TO BE DEFINED
  message(DEBUG "Using component generated_Utility_STM32CubeMX2_Config_HSP_Engine_2_0_0")
  target_compile_definitions(generated_STMicroelectronics_hsp_engine_0_0_1 INTERFACE "$<${generated_STMicroelectronics.hsp_engine.0.0.1_MX_HSP_Engine_needed_components}:-DCMSIS_USE_generated_Utility_STM32CubeMX2_Config_HSP_Engine_2_0_0=1>")
  target_include_directories(generated_STMicroelectronics_hsp_engine_0_0_1 INTERFACE "$<${generated_STMicroelectronics.hsp_engine.0.0.1_MX_HSP_Engine_needed_components}:${CMAKE_CURRENT_LIST_DIR}/.>")
  target_sources(generated_STMicroelectronics_hsp_engine_0_0_1 INTERFACE "$<${generated_STMicroelectronics.hsp_engine.0.0.1_MX_HSP_Engine_needed_components}:${CMAKE_CURRENT_LIST_DIR}/mx_hsp_engine_app.c>")
endif()

