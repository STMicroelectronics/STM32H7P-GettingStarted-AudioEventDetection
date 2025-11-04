# origin-pack: STMicroelectronics::usbpd@0.1.5
# created-by: conversion-manager@0.0.63
project(STMicroelectronics_usbpd_0_1_5)
cmake_minimum_required(VERSION 3.20)
add_library(STMicroelectronics_usbpd_0_1_5 INTERFACE)

# List of all CMSIS properties that influence conditions for this package
if(NOT DEFINED CMSIS_Dcore)
  set(CMSIS_Dcore "CMSIS_Dcore not set")
  message(DEBUG "CMSIS_Dcore is not set to any value")
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
if(CMSIS_ENTIRE_STMicroelectronics_usbpd_0_1_5)
  set(CMSIS_USE_USB_USBPD_Core_0_1_0 true)
  set(CMSIS_USE_USB_USBPD_Lib_USBPD_PD3FULL_0_1_0 true)
  set(CMSIS_USE_USB_USBPD_Lib_USBPD_PD3MINDRP_0_1_0 true)
  set(CMSIS_USE_USB_USBPD_Lib_USBPD_PD3MINSRC_0_1_0 true)
  set(CMSIS_USE_USB_USBPD_Lib_USBPD_PD3MINSNK_0_1_0 true)
  set(CMSIS_USE_USB_USBPD_Lib_USBPD_PD3SPR_0_1_0 true)
  set(CMSIS_USE_USB_USBPD_Lib_USBPD_PD3TYPEC_0_1_0 true)
  set(CMSIS_USE_USB_USBPD_Utils_tracer_0_1_0 true)
  set(CMSIS_USE_USB_USBPD_Utils_monitor_0_1_0 true)
  set(CMSIS_USE_USB_USBPD_Interface_phy_0_1_0 true)
  set(CMSIS_USE_USB_USBPD_Interface_pwr_tcpp01_0_1_0 true)
  set(CMSIS_USE_USB_USBPD_Interface_pwr_tcpp03_0_1_0 true)
  set(CMSIS_USE_USB_USBPD_Interface_trace_0_1_0 true)
  set(CMSIS_USE_USB_USBPD_Interface_timerserver_0_1_0 true)
  set(CMSIS_USE_USB_USBPD_Interface_monitor_0_1_0 true)
  set(CMSIS_USE_USB_USBPD_Interface_usb_0_1_0 true)
endif()

# All conditions used by this package

# condition: STMicroelectronics.usbpd.0.1.5:ARMCC GCC IAR
# description: 
if((CMSIS_Tcompiler STREQUAL "ARMCC" OR CMSIS_Tcompiler STREQUAL "GCC" OR CMSIS_Tcompiler STREQUAL "IAR"))
  set(STMicroelectronics.usbpd.0.1.5:ARMCC_GCC_IAR true)
  message(DEBUG "CMSIS condition STMicroelectronics.usbpd.0.1.5:ARMCC_GCC_IAR enabled")
endif()


# condition: STMicroelectronics.usbpd.0.1.5:M0PLUS
# description: 
if(((CMSIS_Tcompiler STREQUAL "ARMCC" OR CMSIS_Tcompiler STREQUAL "GCC" OR CMSIS_Tcompiler STREQUAL "IAR") AND (CMSIS_Dvendor STREQUAL "STMicroelectronics:13" AND CMSIS_Dcore STREQUAL "Cortex-M0+")))
  set(STMicroelectronics.usbpd.0.1.5:M0PLUS true)
  message(DEBUG "CMSIS condition STMicroelectronics.usbpd.0.1.5:M0PLUS enabled")
endif()


# condition: STMicroelectronics.usbpd.0.1.5:M33
# description: 
if(((CMSIS_Tcompiler STREQUAL "ARMCC" OR CMSIS_Tcompiler STREQUAL "GCC" OR CMSIS_Tcompiler STREQUAL "IAR") AND (CMSIS_Dvendor STREQUAL "STMicroelectronics:13" AND CMSIS_Dcore STREQUAL "Cortex-M33")))
  set(STMicroelectronics.usbpd.0.1.5:M33 true)
  message(DEBUG "CMSIS condition STMicroelectronics.usbpd.0.1.5:M33 enabled")
endif()


# condition: STMicroelectronics.usbpd.0.1.5:M55
# description: 
if(((CMSIS_Tcompiler STREQUAL "ARMCC" OR CMSIS_Tcompiler STREQUAL "GCC" OR CMSIS_Tcompiler STREQUAL "IAR") AND (CMSIS_Dvendor STREQUAL "STMicroelectronics:13" AND CMSIS_Dcore STREQUAL "Cortex-M55")))
  set(STMicroelectronics.usbpd.0.1.5:M55 true)
  message(DEBUG "CMSIS condition STMicroelectronics.usbpd.0.1.5:M55 enabled")
endif()


# condition: STMicroelectronics.usbpd.0.1.5:M7
# description: 
if(((CMSIS_Tcompiler STREQUAL "ARMCC" OR CMSIS_Tcompiler STREQUAL "GCC" OR CMSIS_Tcompiler STREQUAL "IAR") AND (CMSIS_Dvendor STREQUAL "STMicroelectronics:13" AND CMSIS_Dcore STREQUAL "Cortex-M7")))
  set(STMicroelectronics.usbpd.0.1.5:M7 true)
  message(DEBUG "CMSIS condition STMicroelectronics.usbpd.0.1.5:M7 enabled")
endif()


# condition: STMicroelectronics.usbpd.0.1.5:usbpd core condition
# description: USBPD Core dependency
set(STMicroelectronics.usbpd.0.1.5:usbpd_core_condition true)
message(DEBUG "CMSIS condition STMicroelectronics.usbpd.0.1.5:usbpd_core_condition enabled")


# condition: STMicroelectronics.usbpd.0.1.5:usbpd lib condition
# description: USBPD Lib dependency
set(STMicroelectronics.usbpd.0.1.5:usbpd_lib_condition true)
message(DEBUG "CMSIS condition STMicroelectronics.usbpd.0.1.5:usbpd_lib_condition enabled")


# condition: STMicroelectronics.usbpd.0.1.5:usbpd tim peripheral condition
# description: USBPD TIM interface dependency
set(STMicroelectronics.usbpd.0.1.5:usbpd_tim_peripheral_condition true)
message(DEBUG "CMSIS condition STMicroelectronics.usbpd.0.1.5:usbpd_tim_peripheral_condition enabled")


# condition: STMicroelectronics.usbpd.0.1.5:usbpd uart peripheral condition
# description: USBPD UART interface dependency
set(STMicroelectronics.usbpd.0.1.5:usbpd_uart_peripheral_condition true)
message(DEBUG "CMSIS condition STMicroelectronics.usbpd.0.1.5:usbpd_uart_peripheral_condition enabled")


# condition: STMicroelectronics.usbpd.0.1.5:usbpd ucpd peripheral condition
# description: USBPD UCPD interface dependency
set(STMicroelectronics.usbpd.0.1.5:usbpd_ucpd_peripheral_condition true)
message(DEBUG "CMSIS condition STMicroelectronics.usbpd.0.1.5:usbpd_ucpd_peripheral_condition enabled")


# condition: STMicroelectronics.usbpd.0.1.5:usbpd utils tracer condition
# description: USBPD Utils tracer dependency
set(STMicroelectronics.usbpd.0.1.5:usbpd_utils_tracer_condition true)
message(DEBUG "CMSIS condition STMicroelectronics.usbpd.0.1.5:usbpd_utils_tracer_condition enabled")

# Files and components in this package
if(CMSIS_USE_USB_USBPD_Core_0_1_0)  # USB Common Core
  message(DEBUG "Using component USB_USBPD_Core_0_1_0")
  if(STMicroelectronics.usbpd.0.1.5:usbpd_lib_condition)
    target_compile_definitions(STMicroelectronics_usbpd_0_1_5 INTERFACE -DCMSIS_USE_USB_USBPD_Core_0_1_0=1)
    target_include_directories(STMicroelectronics_usbpd_0_1_5 INTERFACE common/core/)
    target_sources(STMicroelectronics_usbpd_0_1_5 INTERFACE common/core/usbpd_phy.c)
    target_sources(STMicroelectronics_usbpd_0_1_5 INTERFACE common/core/usbpd_pwr.c)
    target_sources(STMicroelectronics_usbpd_0_1_5 INTERFACE common/core/usbpd_timersserver.c)
    target_sources(STMicroelectronics_usbpd_0_1_5 INTERFACE common/core/usbpd_trace.c)
  endif()
endif()

if(CMSIS_USE_USB_USBPD_Lib_USBPD_PD3FULL_0_1_0)  # USB Common Lib Full
  message(DEBUG "Using component USB_USBPD_Lib_USBPD_PD3FULL_0_1_0")
  target_compile_definitions(STMicroelectronics_usbpd_0_1_5 INTERFACE -DCMSIS_USE_USB_USBPD_Lib_USBPD_PD3FULL_0_1_0=1)
  if(STMicroelectronics.usbpd.0.1.5:M0PLUS)
    target_link_libraries(STMicroelectronics_usbpd_0_1_5 INTERFACE ${CMAKE_CURRENT_LIST_DIR}/common/lib/USBPD_LIB_FULL_CM0PLUS_wc32.a)
  endif()
  if(STMicroelectronics.usbpd.0.1.5:M33)
    target_link_libraries(STMicroelectronics_usbpd_0_1_5 INTERFACE ${CMAKE_CURRENT_LIST_DIR}/common/lib/USBPD_LIB_FULL_CM33_wc32.a)
  endif()
  if(STMicroelectronics.usbpd.0.1.5:M55)
    target_link_libraries(STMicroelectronics_usbpd_0_1_5 INTERFACE ${CMAKE_CURRENT_LIST_DIR}/common/lib/USBPD_LIB_FULL_CM55_wc32.a)
  endif()
  if(STMicroelectronics.usbpd.0.1.5:M7)
    target_link_libraries(STMicroelectronics_usbpd_0_1_5 INTERFACE ${CMAKE_CURRENT_LIST_DIR}/common/lib/USBPD_LIB_FULL_CM7_wc32.a)
  endif()
endif()

if(CMSIS_USE_USB_USBPD_Lib_USBPD_PD3MINDRP_0_1_0)  # USB Common Lib MinDRP
  message(DEBUG "Using component USB_USBPD_Lib_USBPD_PD3MINDRP_0_1_0")
  target_compile_definitions(STMicroelectronics_usbpd_0_1_5 INTERFACE -DCMSIS_USE_USB_USBPD_Lib_USBPD_PD3MINDRP_0_1_0=1)
  if(STMicroelectronics.usbpd.0.1.5:M0PLUS)
    target_link_libraries(STMicroelectronics_usbpd_0_1_5 INTERFACE ${CMAKE_CURRENT_LIST_DIR}/common/lib/USBPD_LIB_CONFIG_MINDRP_CM0PLUS_wc32.a)
  endif()
  if(STMicroelectronics.usbpd.0.1.5:M33)
    target_link_libraries(STMicroelectronics_usbpd_0_1_5 INTERFACE ${CMAKE_CURRENT_LIST_DIR}/common/lib/USBPD_LIB_CONFIG_MINDRP_CM33_wc32.a)
  endif()
  if(STMicroelectronics.usbpd.0.1.5:M55)
    target_link_libraries(STMicroelectronics_usbpd_0_1_5 INTERFACE ${CMAKE_CURRENT_LIST_DIR}/common/lib/USBPD_LIB_CONFIG_MINDRP_CM55_wc32.a)
  endif()
  if(STMicroelectronics.usbpd.0.1.5:M7)
    target_link_libraries(STMicroelectronics_usbpd_0_1_5 INTERFACE ${CMAKE_CURRENT_LIST_DIR}/common/lib/USBPD_LIB_CONFIG_MINDRP_CM7_wc32.a)
  endif()
endif()

if(CMSIS_USE_USB_USBPD_Lib_USBPD_PD3MINSRC_0_1_0)  # USB Common Lib MinSRC
  message(DEBUG "Using component USB_USBPD_Lib_USBPD_PD3MINSRC_0_1_0")
  target_compile_definitions(STMicroelectronics_usbpd_0_1_5 INTERFACE -DCMSIS_USE_USB_USBPD_Lib_USBPD_PD3MINSRC_0_1_0=1)
  if(STMicroelectronics.usbpd.0.1.5:M0PLUS)
    target_link_libraries(STMicroelectronics_usbpd_0_1_5 INTERFACE ${CMAKE_CURRENT_LIST_DIR}/common/lib/USBPD_LIB_CONFIG_MINSRC_CM0PLUS_wc32.a)
  endif()
  if(STMicroelectronics.usbpd.0.1.5:M33)
    target_link_libraries(STMicroelectronics_usbpd_0_1_5 INTERFACE ${CMAKE_CURRENT_LIST_DIR}/common/lib/USBPD_LIB_CONFIG_MINSRC_CM33_wc32.a)
  endif()
  if(STMicroelectronics.usbpd.0.1.5:M55)
    target_link_libraries(STMicroelectronics_usbpd_0_1_5 INTERFACE ${CMAKE_CURRENT_LIST_DIR}/common/lib/USBPD_LIB_CONFIG_MINSRC_CM55_wc32.a)
  endif()
  if(STMicroelectronics.usbpd.0.1.5:M7)
    target_link_libraries(STMicroelectronics_usbpd_0_1_5 INTERFACE ${CMAKE_CURRENT_LIST_DIR}/common/lib/USBPD_LIB_CONFIG_MINSRC_CM7_wc32.a)
  endif()
endif()

if(CMSIS_USE_USB_USBPD_Lib_USBPD_PD3MINSNK_0_1_0)  # USB Common Lib MinSNK
  message(DEBUG "Using component USB_USBPD_Lib_USBPD_PD3MINSNK_0_1_0")
  target_compile_definitions(STMicroelectronics_usbpd_0_1_5 INTERFACE -DCMSIS_USE_USB_USBPD_Lib_USBPD_PD3MINSNK_0_1_0=1)
  if(STMicroelectronics.usbpd.0.1.5:M0PLUS)
    target_link_libraries(STMicroelectronics_usbpd_0_1_5 INTERFACE ${CMAKE_CURRENT_LIST_DIR}/common/lib/USBPD_LIB_CONFIG_MINSNK_CM0PLUS_wc32.a)
  endif()
  if(STMicroelectronics.usbpd.0.1.5:M33)
    target_link_libraries(STMicroelectronics_usbpd_0_1_5 INTERFACE ${CMAKE_CURRENT_LIST_DIR}/common/lib/USBPD_LIB_CONFIG_MINSNK_CM33_wc32.a)
  endif()
  if(STMicroelectronics.usbpd.0.1.5:M55)
    target_link_libraries(STMicroelectronics_usbpd_0_1_5 INTERFACE ${CMAKE_CURRENT_LIST_DIR}/common/lib/USBPD_LIB_CONFIG_MINSNK_CM55_wc32.a)
  endif()
  if(STMicroelectronics.usbpd.0.1.5:M7)
    target_link_libraries(STMicroelectronics_usbpd_0_1_5 INTERFACE ${CMAKE_CURRENT_LIST_DIR}/common/lib/USBPD_LIB_CONFIG_MINSNK_CM7_wc32.a)
  endif()
endif()

if(CMSIS_USE_USB_USBPD_Lib_USBPD_PD3SPR_0_1_0)  # USB Common Lib SPR
  message(DEBUG "Using component USB_USBPD_Lib_USBPD_PD3SPR_0_1_0")
  target_compile_definitions(STMicroelectronics_usbpd_0_1_5 INTERFACE -DCMSIS_USE_USB_USBPD_Lib_USBPD_PD3SPR_0_1_0=1)
  if(STMicroelectronics.usbpd.0.1.5:M0PLUS)
    target_link_libraries(STMicroelectronics_usbpd_0_1_5 INTERFACE ${CMAKE_CURRENT_LIST_DIR}/common/lib/USBPD_LIB_CONFIG_SPR_CM0PLUS_wc32.a)
  endif()
  if(STMicroelectronics.usbpd.0.1.5:M33)
    target_link_libraries(STMicroelectronics_usbpd_0_1_5 INTERFACE ${CMAKE_CURRENT_LIST_DIR}/common/lib/USBPD_LIB_CONFIG_SPR_CM33_wc32.a)
  endif()
  if(STMicroelectronics.usbpd.0.1.5:M55)
    target_link_libraries(STMicroelectronics_usbpd_0_1_5 INTERFACE ${CMAKE_CURRENT_LIST_DIR}/common/lib/USBPD_LIB_CONFIG_SPR_CM55_wc32.a)
  endif()
  if(STMicroelectronics.usbpd.0.1.5:M7)
    target_link_libraries(STMicroelectronics_usbpd_0_1_5 INTERFACE ${CMAKE_CURRENT_LIST_DIR}/common/lib/USBPD_LIB_CONFIG_SPR_CM7_wc32.a)
  endif()
endif()

if(CMSIS_USE_USB_USBPD_Lib_USBPD_PD3TYPEC_0_1_0)  # USB Common Lib TypeC
  message(DEBUG "Using component USB_USBPD_Lib_USBPD_PD3TYPEC_0_1_0")
  target_compile_definitions(STMicroelectronics_usbpd_0_1_5 INTERFACE -DCMSIS_USE_USB_USBPD_Lib_USBPD_PD3TYPEC_0_1_0=1)
  if(STMicroelectronics.usbpd.0.1.5:M0PLUS)
    target_link_libraries(STMicroelectronics_usbpd_0_1_5 INTERFACE ${CMAKE_CURRENT_LIST_DIR}/common/lib/USBPD_LIB_NO_PD_CM0PLUS_wc32.a)
  endif()
  if(STMicroelectronics.usbpd.0.1.5:M33)
    target_link_libraries(STMicroelectronics_usbpd_0_1_5 INTERFACE ${CMAKE_CURRENT_LIST_DIR}/common/lib/USBPD_LIB_NO_PD_CM33_wc32.a)
  endif()
  if(STMicroelectronics.usbpd.0.1.5:M55)
    target_link_libraries(STMicroelectronics_usbpd_0_1_5 INTERFACE ${CMAKE_CURRENT_LIST_DIR}/common/lib/USBPD_LIB_NO_PD_CM55_wc32.a)
  endif()
  if(STMicroelectronics.usbpd.0.1.5:M7)
    target_link_libraries(STMicroelectronics_usbpd_0_1_5 INTERFACE ${CMAKE_CURRENT_LIST_DIR}/common/lib/USBPD_LIB_NO_PD_CM7_wc32.a)
  endif()
endif()

if(CMSIS_USE_USB_USBPD_Utils_tracer_0_1_0)  # USB Common Utils
  message(DEBUG "Using component USB_USBPD_Utils_tracer_0_1_0")
  if(STMicroelectronics.usbpd.0.1.5:usbpd_core_condition)
    target_compile_definitions(STMicroelectronics_usbpd_0_1_5 INTERFACE -DCMSIS_USE_USB_USBPD_Utils_tracer_0_1_0=1)
    target_include_directories(STMicroelectronics_usbpd_0_1_5 INTERFACE common/utils/tracer/)
    target_sources(STMicroelectronics_usbpd_0_1_5 INTERFACE common/utils/tracer/usbpd_utils_tracer.c)
  endif()
endif()

if(CMSIS_USE_USB_USBPD_Utils_monitor_0_1_0)  # USB Common Utils
  message(DEBUG "Using component USB_USBPD_Utils_monitor_0_1_0")
  if(STMicroelectronics.usbpd.0.1.5:usbpd_utils_tracer_condition)
    target_compile_definitions(STMicroelectronics_usbpd_0_1_5 INTERFACE -DCMSIS_USE_USB_USBPD_Utils_monitor_0_1_0=1)
    target_include_directories(STMicroelectronics_usbpd_0_1_5 INTERFACE common/utils/monitor/)
    target_sources(STMicroelectronics_usbpd_0_1_5 INTERFACE common/utils/monitor/usbpd_utils_monitor.c)
    target_sources(STMicroelectronics_usbpd_0_1_5 INTERFACE common/utils/monitor/usbpd_utils_monitor_tlv.c)
  endif()
endif()

if(CMSIS_USE_USB_USBPD_Interface_phy_0_1_0)  # USBPD interface phy
  message(DEBUG "Using component USB_USBPD_Interface_phy_0_1_0")
  if(STMicroelectronics.usbpd.0.1.5:usbpd_ucpd_peripheral_condition)
    target_compile_definitions(STMicroelectronics_usbpd_0_1_5 INTERFACE -DCMSIS_USE_USB_USBPD_Interface_phy_0_1_0=1)
    target_include_directories(STMicroelectronics_usbpd_0_1_5 INTERFACE interfaces/phy/)
    target_sources(STMicroelectronics_usbpd_0_1_5 INTERFACE interfaces/phy/usbpd_cad_hw_if.c)
    target_sources(STMicroelectronics_usbpd_0_1_5 INTERFACE interfaces/phy/usbpd_phy_hw_if.c)
  endif()
endif()

if(CMSIS_USE_USB_USBPD_Interface_pwr_tcpp01_0_1_0)  # USBPD interface pwr for TCPP01
  message(DEBUG "Using component USB_USBPD_Interface_pwr_tcpp01_0_1_0")
  target_compile_definitions(STMicroelectronics_usbpd_0_1_5 INTERFACE -DCMSIS_USE_USB_USBPD_Interface_pwr_tcpp01_0_1_0=1)
  target_include_directories(STMicroelectronics_usbpd_0_1_5 INTERFACE interfaces/pwr/tcpp01/)
  target_sources(STMicroelectronics_usbpd_0_1_5 INTERFACE interfaces/pwr/tcpp01/usbpd_pwr_hw_if.c)
endif()

if(CMSIS_USE_USB_USBPD_Interface_pwr_tcpp03_0_1_0)  # USBPD interface pwr for TCPP03
  message(DEBUG "Using component USB_USBPD_Interface_pwr_tcpp03_0_1_0")
  target_compile_definitions(STMicroelectronics_usbpd_0_1_5 INTERFACE -DCMSIS_USE_USB_USBPD_Interface_pwr_tcpp03_0_1_0=1)
  target_include_directories(STMicroelectronics_usbpd_0_1_5 INTERFACE interfaces/pwr/tcpp03/)
  target_sources(STMicroelectronics_usbpd_0_1_5 INTERFACE interfaces/pwr/tcpp03/usbpd_pwr_hw_if.c)
endif()

if(CMSIS_USE_USB_USBPD_Interface_trace_0_1_0)  # USBPD interface trace
  message(DEBUG "Using component USB_USBPD_Interface_trace_0_1_0")
  if(STMicroelectronics.usbpd.0.1.5:usbpd_uart_peripheral_condition)
    target_compile_definitions(STMicroelectronics_usbpd_0_1_5 INTERFACE -DCMSIS_USE_USB_USBPD_Interface_trace_0_1_0=1)
    target_include_directories(STMicroelectronics_usbpd_0_1_5 INTERFACE interfaces/trace/)
    target_sources(STMicroelectronics_usbpd_0_1_5 INTERFACE interfaces/trace/usbpd_utils_tracer_hw_if.c)
  endif()
endif()

if(CMSIS_USE_USB_USBPD_Interface_timerserver_0_1_0)  # USBPD interface timerserver
  message(DEBUG "Using component USB_USBPD_Interface_timerserver_0_1_0")
  if(STMicroelectronics.usbpd.0.1.5:usbpd_tim_peripheral_condition)
    target_compile_definitions(STMicroelectronics_usbpd_0_1_5 INTERFACE -DCMSIS_USE_USB_USBPD_Interface_timerserver_0_1_0=1)
    target_include_directories(STMicroelectronics_usbpd_0_1_5 INTERFACE interfaces/timerserver/)
    target_sources(STMicroelectronics_usbpd_0_1_5 INTERFACE interfaces/timerserver/usbpd_timerserver_hw_if.c)
  endif()
endif()

if(CMSIS_USE_USB_USBPD_Interface_monitor_0_1_0)  # USBPD interface monitor
  message(DEBUG "Using component USB_USBPD_Interface_monitor_0_1_0")
  target_compile_definitions(STMicroelectronics_usbpd_0_1_5 INTERFACE -DCMSIS_USE_USB_USBPD_Interface_monitor_0_1_0=1)
  target_include_directories(STMicroelectronics_usbpd_0_1_5 INTERFACE interfaces/monitor/)
  target_sources(STMicroelectronics_usbpd_0_1_5 INTERFACE interfaces/monitor/usbpd_utils_monitor_hw_if.c)
endif()

if(CMSIS_USE_USB_USBPD_Interface_usb_0_1_0)  # USBPD interface usb
  message(DEBUG "Using component USB_USBPD_Interface_usb_0_1_0")
  target_compile_definitions(STMicroelectronics_usbpd_0_1_5 INTERFACE -DCMSIS_USE_USB_USBPD_Interface_usb_0_1_0=1)
  target_include_directories(STMicroelectronics_usbpd_0_1_5 INTERFACE interfaces/usb/)
  target_sources(STMicroelectronics_usbpd_0_1_5 INTERFACE interfaces/usb/usbpd_usb_if.c)
endif()

