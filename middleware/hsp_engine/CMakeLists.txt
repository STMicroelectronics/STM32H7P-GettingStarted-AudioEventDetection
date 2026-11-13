# origin-pack: STMicroelectronics::hsp_engine@2.0.0
# file-format: 1.0.0
project(STMicroelectronics_hsp_engine_2_0_0)
cmake_minimum_required(VERSION 3.30)
add_library(STMicroelectronics_hsp_engine_2_0_0 INTERFACE)

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
if(CMSIS_ENTIRE_STMicroelectronics_hsp_engine_2_0_0)
  list(APPEND CMSIS_COMPONENTS_LIST "Cvendor:STMicroelectronics#Cclass:Utility#Cgroup:HSP Engine#Csub:Core#Cversion:2.0.0")
  list(APPEND CMSIS_COMPONENTS_LIST "Cvendor:STMicroelectronics#Cclass:Utility#Cgroup:HSP Engine#Csub:Firmware#Cversion:2.0.0")
  list(APPEND CMSIS_COMPONENTS_LIST "Cvendor:STMicroelectronics#Cclass:Utility#Cgroup:HSP Engine#Csub:Interfaces#Cversion:2.0.0")
  list(APPEND CMSIS_COMPONENTS_LIST "Cvendor:STMicroelectronics#Cclass:Utility#Cgroup:HSP Engine#Csub:DSP#Cversion:2.0.0")
  list(APPEND CMSIS_COMPONENTS_LIST "Cvendor:STMicroelectronics#Cclass:Utility#Cgroup:HSP Engine#Csub:CNN#Cversion:2.0.0")
  list(APPEND CMSIS_COMPONENTS_LIST "Cvendor:STMicroelectronics#Cclass:Utility#Cgroup:HSP Engine#Csub:Processing List#Cversion:2.0.0")
endif()

# All conditions used by this package

# condition: STMicroelectronics.hsp_engine.2.0.0
# description: 
if((CMSIS_Dname MATCHES "STM32.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13"))
  set(STMicroelectronics.hsp_engine.2.0.0 "1")
  message(DEBUG "CMSIS condition STMicroelectronics.hsp_engine.2.0.0 enabled")
else()
  set(STMicroelectronics.hsp_engine.2.0.0 0)
endif()


# condition: STMicroelectronics.hsp_engine.2.0.0:ARMASM
# description: 
if((CMSIS_Tcompiler STREQUAL "ARMCC" AND CMSIS_Toptions STREQUAL "AC5"))
  set(STMicroelectronics.hsp_engine.2.0.0_ARMASM "1")
  message(DEBUG "CMSIS condition STMicroelectronics.hsp_engine.2.0.0_ARMASM enabled")
else()
  set(STMicroelectronics.hsp_engine.2.0.0_ARMASM 0)
endif()


# condition: STMicroelectronics.hsp_engine.2.0.0:ARMCLANG
# description: 
if((CMSIS_Tcompiler STREQUAL "ARMCC" AND CMSIS_Toptions STREQUAL "AC6"))
  set(STMicroelectronics.hsp_engine.2.0.0_ARMCLANG "1")
  message(DEBUG "CMSIS condition STMicroelectronics.hsp_engine.2.0.0_ARMCLANG enabled")
else()
  set(STMicroelectronics.hsp_engine.2.0.0_ARMCLANG 0)
endif()


# condition: STMicroelectronics.hsp_engine.2.0.0:GCC
# description: 
if(CMSIS_Tcompiler STREQUAL "GCC")
  set(STMicroelectronics.hsp_engine.2.0.0_GCC "1")
  message(DEBUG "CMSIS condition STMicroelectronics.hsp_engine.2.0.0_GCC enabled")
else()
  set(STMicroelectronics.hsp_engine.2.0.0_GCC 0)
endif()


# condition: STMicroelectronics.hsp_engine.2.0.0:GNU ASM
# description: 
if((CMSIS_Tcompiler STREQUAL "GCC" OR (CMSIS_Tcompiler STREQUAL "ARMCC" AND CMSIS_Toptions STREQUAL "AC6")))
  set(STMicroelectronics.hsp_engine.2.0.0_GNU_ASM "1")
  message(DEBUG "CMSIS condition STMicroelectronics.hsp_engine.2.0.0_GNU_ASM enabled")
else()
  set(STMicroelectronics.hsp_engine.2.0.0_GNU_ASM 0)
endif()


# condition: STMicroelectronics.hsp_engine.2.0.0:HSP Engine HAL Interfaces
# description: HSP Engine Interfaces build with HSP HAL Driver
set(STMicroelectronics.hsp_engine.2.0.0_HSP_Engine_HAL_Interfaces "$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 HAL#.*Csub:HSP(#.*|$)>,>>")
message(DEBUG "CMSIS condition STMicroelectronics.hsp_engine.2.0.0_HSP_Engine_HAL_Interfaces enabled")


# condition: STMicroelectronics.hsp_engine.2.0.0:HSP Engine Modules CNN
# description: 
set(STMicroelectronics.hsp_engine.2.0.0_HSP_Engine_Modules_CNN "1")
message(DEBUG "CMSIS condition STMicroelectronics.hsp_engine.2.0.0_HSP_Engine_Modules_CNN enabled")


# condition: STMicroelectronics.hsp_engine.2.0.0:HSP Engine Modules CNN DMA
# description: 
if((CMSIS_Dname MATCHES "STM32G5[CDRS].*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13"))
  set(STMicroelectronics.hsp_engine.2.0.0_HSP_Engine_Modules_CNN_DMA "1")
  message(DEBUG "CMSIS condition STMicroelectronics.hsp_engine.2.0.0_HSP_Engine_Modules_CNN_DMA enabled")
else()
  set(STMicroelectronics.hsp_engine.2.0.0_HSP_Engine_Modules_CNN_DMA 0)
endif()


# condition: STMicroelectronics.hsp_engine.2.0.0:HSP Engine Modules DSP
# description: 
if((CMSIS_Dname MATCHES "STM32.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13"))
  set(STMicroelectronics.hsp_engine.2.0.0_HSP_Engine_Modules_DSP "1")
  message(DEBUG "CMSIS condition STMicroelectronics.hsp_engine.2.0.0_HSP_Engine_Modules_DSP enabled")
else()
  set(STMicroelectronics.hsp_engine.2.0.0_HSP_Engine_Modules_DSP 0)
endif()


# condition: STMicroelectronics.hsp_engine.2.0.0:HSP Engine Modules Proclist Digital Control
# description: 
if((CMSIS_Dname MATCHES "STM32G5[CDRS].*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13"))
  set(STMicroelectronics.hsp_engine.2.0.0_HSP_Engine_Modules_Proclist_Digital_Control "1")
  message(DEBUG "CMSIS condition STMicroelectronics.hsp_engine.2.0.0_HSP_Engine_Modules_Proclist_Digital_Control enabled")
else()
  set(STMicroelectronics.hsp_engine.2.0.0_HSP_Engine_Modules_Proclist_Digital_Control 0)
endif()


# condition: STMicroelectronics.hsp_engine.2.0.0:HSP FW ROM v1.1.10
# description: HSP embedded FW ROM v1.1.10
if((CMSIS_Dname MATCHES "STM32H7P.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13"))
  set(STMicroelectronics.hsp_engine.2.0.0_HSP_FW_ROM_v1.1.10 "1")
  message(DEBUG "CMSIS condition STMicroelectronics.hsp_engine.2.0.0_HSP_FW_ROM_v1.1.10 enabled")
else()
  set(STMicroelectronics.hsp_engine.2.0.0_HSP_FW_ROM_v1.1.10 0)
endif()


# condition: STMicroelectronics.hsp_engine.2.0.0:HSP FW ROM v2.1.4
# description: HSP embedded FW ROM v2.1.4
if((CMSIS_Dname MATCHES "STM32G5[CDRS].*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13"))
  set(STMicroelectronics.hsp_engine.2.0.0_HSP_FW_ROM_v2.1.4 "1")
  message(DEBUG "CMSIS condition STMicroelectronics.hsp_engine.2.0.0_HSP_FW_ROM_v2.1.4 enabled")
else()
  set(STMicroelectronics.hsp_engine.2.0.0_HSP_FW_ROM_v2.1.4 0)
endif()


# condition: STMicroelectronics.hsp_engine.2.0.0:HSP Sequencer mode
# description: 
set(STMicroelectronics.hsp_engine.2.0.0_HSP_Sequencer_mode "1")
message(DEBUG "CMSIS condition STMicroelectronics.hsp_engine.2.0.0_HSP_Sequencer_mode enabled")


# condition: STMicroelectronics.hsp_engine.2.0.0:IAR
# description: 
if(CMSIS_Tcompiler STREQUAL "IAR")
  set(STMicroelectronics.hsp_engine.2.0.0_IAR "1")
  message(DEBUG "CMSIS condition STMicroelectronics.hsp_engine.2.0.0_IAR enabled")
else()
  set(STMicroelectronics.hsp_engine.2.0.0_IAR 0)
endif()


# condition: STMicroelectronics.hsp_engine.2.0.0:MX HSP Engine needed components
# description: Mandatory files to include in code generation of HSP Engine Middleware
set(STMicroelectronics.hsp_engine.2.0.0_MX_HSP_Engine_needed_components "$<AND:$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Utility#.*Cgroup:HSP Engine#.*Csub:Core(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Utility#.*Cgroup:HSP Engine#.*Csub:Interfaces(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Utility#.*Cgroup:HSP Engine#.*Csub:Firmware(#.*|$)>,>>>")
message(DEBUG "CMSIS condition STMicroelectronics.hsp_engine.2.0.0_MX_HSP_Engine_needed_components enabled")


# condition: STMicroelectronics.hsp_engine.2.0.0:ROM v1.1.10 AND RAM v1.7
# description: HSP FW ROM version 1.1.10 AND RAM version 1.7
if((CMSIS_Dname MATCHES "STM32H7P.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13"))
  set(STMicroelectronics.hsp_engine.2.0.0_ROM_v1.1.10_AND_RAM_v1.7 "1")
  message(DEBUG "CMSIS condition STMicroelectronics.hsp_engine.2.0.0_ROM_v1.1.10_AND_RAM_v1.7 enabled")
else()
  set(STMicroelectronics.hsp_engine.2.0.0_ROM_v1.1.10_AND_RAM_v1.7 0)
endif()


# condition: STMicroelectronics.hsp_engine.2.0.0:ROM v2.1.4 AND RAM v1.0
# description: HSP FW ROM version 2.1.4 AND RAM version 1.0
if((CMSIS_Dname MATCHES "STM32G5[CDRS].*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13"))
  set(STMicroelectronics.hsp_engine.2.0.0_ROM_v2.1.4_AND_RAM_v1.0 "1")
  message(DEBUG "CMSIS condition STMicroelectronics.hsp_engine.2.0.0_ROM_v2.1.4_AND_RAM_v1.0 enabled")
else()
  set(STMicroelectronics.hsp_engine.2.0.0_ROM_v2.1.4_AND_RAM_v1.0 0)
endif()

# Files and components in this package
if("Cvendor:STMicroelectronics#Cclass:Utility#Cgroup:HSP Engine#Csub:Core#Cversion:2.0.0" IN_LIST CMSIS_COMPONENTS_LIST)  # HSP Engine Common Core
  message(DEBUG "Using component Utility_HSP_Engine_Core_2_0_0")
  target_compile_definitions(STMicroelectronics_hsp_engine_2_0_0 INTERFACE "-DCMSIS_USE_Utility_HSP_Engine_Core_2_0_0=1")
  target_include_directories(STMicroelectronics_hsp_engine_2_0_0 INTERFACE "${CMAKE_CURRENT_LIST_DIR}/common/core/")
  target_include_directories(STMicroelectronics_hsp_engine_2_0_0 INTERFACE "${CMAKE_CURRENT_LIST_DIR}/common/core/legacy/")
  target_include_directories(STMicroelectronics_hsp_engine_2_0_0 INTERFACE "${CMAKE_CURRENT_LIST_DIR}/common/modules/")
  target_include_directories(STMicroelectronics_hsp_engine_2_0_0 INTERFACE "${CMAKE_CURRENT_LIST_DIR}/common/modules/direct_lib/")
  target_include_directories(STMicroelectronics_hsp_engine_2_0_0 INTERFACE "${CMAKE_CURRENT_LIST_DIR}/common/utilities/")
  target_sources(STMicroelectronics_hsp_engine_2_0_0 INTERFACE "${CMAKE_CURRENT_LIST_DIR}/common/core/hsp_bram.c")
  target_sources(STMicroelectronics_hsp_engine_2_0_0 INTERFACE "${CMAKE_CURRENT_LIST_DIR}/common/core/hsp_core.c")
  target_sources(STMicroelectronics_hsp_engine_2_0_0 INTERFACE "${CMAKE_CURRENT_LIST_DIR}/common/modules/direct_lib/hsp_direct_command.c")
  target_sources(STMicroelectronics_hsp_engine_2_0_0 INTERFACE "${CMAKE_CURRENT_LIST_DIR}/common/utilities/hsp_memcpy.c")
  target_sources(STMicroelectronics_hsp_engine_2_0_0 INTERFACE "$<${STMicroelectronics.hsp_engine.2.0.0_ARMASM}:${CMAKE_CURRENT_LIST_DIR}/common/utilities/portable/Keil/st_hsp_memcpy32.s>")
  target_sources(STMicroelectronics_hsp_engine_2_0_0 INTERFACE "$<${STMicroelectronics.hsp_engine.2.0.0_GNU_ASM}:${CMAKE_CURRENT_LIST_DIR}/common/utilities/portable/GCC/st_hsp_memcpy32.S>")
  target_sources(STMicroelectronics_hsp_engine_2_0_0 INTERFACE "$<${STMicroelectronics.hsp_engine.2.0.0_IAR}:${CMAKE_CURRENT_LIST_DIR}/common/utilities/portable/IAR/st_hsp_memcpy32.s>")
endif()

if("Cvendor:STMicroelectronics#Cclass:Utility#Cgroup:HSP Engine#Csub:Firmware#Cversion:2.0.0" IN_LIST CMSIS_COMPONENTS_LIST)  # HSP Engine Common Modules Firmware
  message(DEBUG "Using component Utility_HSP_Engine_Firmware_2_0_0")
  target_compile_definitions(STMicroelectronics_hsp_engine_2_0_0 INTERFACE "-DCMSIS_USE_Utility_HSP_Engine_Firmware_2_0_0=1")
  target_include_directories(STMicroelectronics_hsp_engine_2_0_0 INTERFACE "${CMAKE_CURRENT_LIST_DIR}/common/modules/firmware/")
  target_include_directories(STMicroelectronics_hsp_engine_2_0_0 INTERFACE "$<${STMicroelectronics.hsp_engine.2.0.0_ROM_v1.1.10_AND_RAM_v1.7}:${CMAKE_CURRENT_LIST_DIR}/common/modules/firmware/crom_1_1_10/cram_1_7/>")
  target_sources(STMicroelectronics_hsp_engine_2_0_0 INTERFACE "$<${STMicroelectronics.hsp_engine.2.0.0_ROM_v1.1.10_AND_RAM_v1.7}:${CMAKE_CURRENT_LIST_DIR}/common/modules/firmware/crom_1_1_10/cram_1_7/hsp_fw_ram.c>")
  target_include_directories(STMicroelectronics_hsp_engine_2_0_0 INTERFACE "$<${STMicroelectronics.hsp_engine.2.0.0_ROM_v2.1.4_AND_RAM_v1.0}:${CMAKE_CURRENT_LIST_DIR}/common/modules/firmware/crom_2_1_4/cram_1_0/>")
  target_sources(STMicroelectronics_hsp_engine_2_0_0 INTERFACE "$<${STMicroelectronics.hsp_engine.2.0.0_ROM_v2.1.4_AND_RAM_v1.0}:${CMAKE_CURRENT_LIST_DIR}/common/modules/firmware/crom_2_1_4/cram_1_0/hsp_fw_ram.c>")
endif()

if("Cvendor:STMicroelectronics#Cclass:Utility#Cgroup:HSP Engine#Csub:Interfaces#Cversion:2.0.0" IN_LIST CMSIS_COMPONENTS_LIST)  # HSP Engine Interfaces build on HSP HAL Driver
  message(DEBUG "Using component Utility_HSP_Engine_Interfaces_2_0_0")
  target_compile_definitions(STMicroelectronics_hsp_engine_2_0_0 INTERFACE "$<${STMicroelectronics.hsp_engine.2.0.0_HSP_Engine_HAL_Interfaces}:-DCMSIS_USE_Utility_HSP_Engine_Interfaces_2_0_0=1>")
  target_include_directories(STMicroelectronics_hsp_engine_2_0_0 INTERFACE "$<${STMicroelectronics.hsp_engine.2.0.0_HSP_Engine_HAL_Interfaces}:${CMAKE_CURRENT_LIST_DIR}/interfaces/>")
  target_sources(STMicroelectronics_hsp_engine_2_0_0 INTERFACE "$<${STMicroelectronics.hsp_engine.2.0.0_HSP_Engine_HAL_Interfaces}:${CMAKE_CURRENT_LIST_DIR}/interfaces/hsp_bram_if.c>")
  target_sources(STMicroelectronics_hsp_engine_2_0_0 INTERFACE "$<${STMicroelectronics.hsp_engine.2.0.0_HSP_Engine_HAL_Interfaces}:${CMAKE_CURRENT_LIST_DIR}/interfaces/hsp_hw_if.c>")
  target_include_directories(STMicroelectronics_hsp_engine_2_0_0 INTERFACE "$<$<AND:${STMicroelectronics.hsp_engine.2.0.0_HSP_Engine_HAL_Interfaces},${STMicroelectronics.hsp_engine.2.0.0_HSP_Sequencer_mode}>:${CMAKE_CURRENT_LIST_DIR}/interfaces/services/>")
  target_sources(STMicroelectronics_hsp_engine_2_0_0 INTERFACE "$<$<AND:${STMicroelectronics.hsp_engine.2.0.0_HSP_Engine_HAL_Interfaces},${STMicroelectronics.hsp_engine.2.0.0_HSP_Sequencer_mode}>:${CMAKE_CURRENT_LIST_DIR}/interfaces/services/hsp_services.c>")
endif()

if("Cvendor:STMicroelectronics#Cclass:Utility#Cgroup:HSP Engine#Csub:DSP#Cversion:2.0.0" IN_LIST CMSIS_COMPONENTS_LIST)  # HSP Engine Common Modules DSP
  message(DEBUG "Using component Utility_HSP_Engine_DSP_2_0_0")
  target_compile_definitions(STMicroelectronics_hsp_engine_2_0_0 INTERFACE "$<${STMicroelectronics.hsp_engine.2.0.0_HSP_Engine_Modules_DSP}:-DCMSIS_USE_Utility_HSP_Engine_DSP_2_0_0=1>")
  target_include_directories(STMicroelectronics_hsp_engine_2_0_0 INTERFACE "$<${STMicroelectronics.hsp_engine.2.0.0_HSP_Engine_Modules_DSP}:${CMAKE_CURRENT_LIST_DIR}/common/modules/dsp_lib/>")
  target_sources(STMicroelectronics_hsp_engine_2_0_0 INTERFACE "$<${STMicroelectronics.hsp_engine.2.0.0_HSP_Engine_Modules_DSP}:${CMAKE_CURRENT_LIST_DIR}/common/modules/dsp_lib/hsp_dsp.c>")
endif()

if("Cvendor:STMicroelectronics#Cclass:Utility#Cgroup:HSP Engine#Csub:CNN#Cversion:2.0.0" IN_LIST CMSIS_COMPONENTS_LIST)  # HSP Engine Common Modules CNN
  message(DEBUG "Using component Utility_HSP_Engine_CNN_2_0_0")
  target_compile_definitions(STMicroelectronics_hsp_engine_2_0_0 INTERFACE "$<${STMicroelectronics.hsp_engine.2.0.0_HSP_Engine_Modules_CNN}:-DCMSIS_USE_Utility_HSP_Engine_CNN_2_0_0=1>")
  target_include_directories(STMicroelectronics_hsp_engine_2_0_0 INTERFACE "$<${STMicroelectronics.hsp_engine.2.0.0_HSP_Engine_Modules_CNN}:${CMAKE_CURRENT_LIST_DIR}/common/modules/cnn_lib/>")
  target_sources(STMicroelectronics_hsp_engine_2_0_0 INTERFACE "$<${STMicroelectronics.hsp_engine.2.0.0_HSP_Engine_Modules_CNN}:${CMAKE_CURRENT_LIST_DIR}/common/modules/cnn_lib/hsp_cnn.c>")
  target_sources(STMicroelectronics_hsp_engine_2_0_0 INTERFACE "$<$<AND:${STMicroelectronics.hsp_engine.2.0.0_HSP_Engine_Modules_CNN},${STMicroelectronics.hsp_engine.2.0.0_HSP_Engine_Modules_CNN_DMA}>:${CMAKE_CURRENT_LIST_DIR}/common/modules/cnn_lib/hsp_cnn_dma.c>")
endif()

if("Cvendor:STMicroelectronics#Cclass:Utility#Cgroup:HSP Engine#Csub:Processing List#Cversion:2.0.0" IN_LIST CMSIS_COMPONENTS_LIST)  # HSP Engine Common Modules Proclist
  message(DEBUG "Using component Utility_HSP_Engine_Processing_List_2_0_0")
  target_compile_definitions(STMicroelectronics_hsp_engine_2_0_0 INTERFACE "$<${STMicroelectronics.hsp_engine.2.0.0_HSP_Sequencer_mode}:-DCMSIS_USE_Utility_HSP_Engine_Processing_List_2_0_0=1>")
  target_include_directories(STMicroelectronics_hsp_engine_2_0_0 INTERFACE "$<${STMicroelectronics.hsp_engine.2.0.0_HSP_Sequencer_mode}:${CMAKE_CURRENT_LIST_DIR}/common/modules/>")
  target_include_directories(STMicroelectronics_hsp_engine_2_0_0 INTERFACE "$<${STMicroelectronics.hsp_engine.2.0.0_HSP_Sequencer_mode}:${CMAKE_CURRENT_LIST_DIR}/common/modules/proclist_lib/>")
  target_include_directories(STMicroelectronics_hsp_engine_2_0_0 INTERFACE "$<${STMicroelectronics.hsp_engine.2.0.0_HSP_Sequencer_mode}:${CMAKE_CURRENT_LIST_DIR}/common/monitoring/>")
  target_include_directories(STMicroelectronics_hsp_engine_2_0_0 INTERFACE "$<${STMicroelectronics.hsp_engine.2.0.0_HSP_Sequencer_mode}:${CMAKE_CURRENT_LIST_DIR}/common/proclist/>")
  target_sources(STMicroelectronics_hsp_engine_2_0_0 INTERFACE "$<${STMicroelectronics.hsp_engine.2.0.0_HSP_Sequencer_mode}:${CMAKE_CURRENT_LIST_DIR}/common/modules/proclist_lib/hsp_proclist_complex.c>")
  target_sources(STMicroelectronics_hsp_engine_2_0_0 INTERFACE "$<${STMicroelectronics.hsp_engine.2.0.0_HSP_Sequencer_mode}:${CMAKE_CURRENT_LIST_DIR}/common/modules/proclist_lib/hsp_proclist_conditional.c>")
  target_sources(STMicroelectronics_hsp_engine_2_0_0 INTERFACE "$<${STMicroelectronics.hsp_engine.2.0.0_HSP_Sequencer_mode}:${CMAKE_CURRENT_LIST_DIR}/common/modules/proclist_lib/hsp_proclist_filter.c>")
  target_sources(STMicroelectronics_hsp_engine_2_0_0 INTERFACE "$<${STMicroelectronics.hsp_engine.2.0.0_HSP_Sequencer_mode}:${CMAKE_CURRENT_LIST_DIR}/common/modules/proclist_lib/hsp_proclist_matrix.c>")
  target_sources(STMicroelectronics_hsp_engine_2_0_0 INTERFACE "$<${STMicroelectronics.hsp_engine.2.0.0_HSP_Sequencer_mode}:${CMAKE_CURRENT_LIST_DIR}/common/modules/proclist_lib/hsp_proclist_scalar.c>")
  target_sources(STMicroelectronics_hsp_engine_2_0_0 INTERFACE "$<${STMicroelectronics.hsp_engine.2.0.0_HSP_Sequencer_mode}:${CMAKE_CURRENT_LIST_DIR}/common/modules/proclist_lib/hsp_proclist_transform.c>")
  target_sources(STMicroelectronics_hsp_engine_2_0_0 INTERFACE "$<${STMicroelectronics.hsp_engine.2.0.0_HSP_Sequencer_mode}:${CMAKE_CURRENT_LIST_DIR}/common/modules/proclist_lib/hsp_proclist_vector.c>")
  target_sources(STMicroelectronics_hsp_engine_2_0_0 INTERFACE "$<${STMicroelectronics.hsp_engine.2.0.0_HSP_Sequencer_mode}:${CMAKE_CURRENT_LIST_DIR}/common/monitoring/hsp_monitoring.c>")
  target_sources(STMicroelectronics_hsp_engine_2_0_0 INTERFACE "$<${STMicroelectronics.hsp_engine.2.0.0_HSP_Sequencer_mode}:${CMAKE_CURRENT_LIST_DIR}/common/proclist/hsp_proclist.c>")
  target_sources(STMicroelectronics_hsp_engine_2_0_0 INTERFACE "$<$<AND:${STMicroelectronics.hsp_engine.2.0.0_HSP_Sequencer_mode},${STMicroelectronics.hsp_engine.2.0.0_HSP_Engine_Modules_Proclist_Digital_Control}>:${CMAKE_CURRENT_LIST_DIR}/common/modules/proclist_lib/hsp_proclist_digital_control.c>")
endif()

