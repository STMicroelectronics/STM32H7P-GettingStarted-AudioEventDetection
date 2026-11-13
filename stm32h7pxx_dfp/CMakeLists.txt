# origin-pack: STMicroelectronics::stm32h7pxx_dfp@2.0.0
# file-format: 1.0.0
project(STMicroelectronics_stm32h7pxx_dfp_2_0_0)
cmake_minimum_required(VERSION 3.30)
add_library(STMicroelectronics_stm32h7pxx_dfp_2_0_0 INTERFACE)

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
    target_compile_definitions(STMicroelectronics_stm32h7pxx_dfp_2_0_0 INTERFACE STM32H7P4xx)
endif()
if(CMSIS_Dname STREQUAL "STM32H7P4IGT6")
    target_compile_definitions(STMicroelectronics_stm32h7pxx_dfp_2_0_0 INTERFACE STM32H7P4xx)
endif()
if(CMSIS_Dname STREQUAL "STM32H7P4IIK6")
    target_compile_definitions(STMicroelectronics_stm32h7pxx_dfp_2_0_0 INTERFACE STM32H7P4xx)
endif()
if(CMSIS_Dname STREQUAL "STM32H7P4IIK6Q")
    target_compile_definitions(STMicroelectronics_stm32h7pxx_dfp_2_0_0 INTERFACE STM32H7P4xx)
endif()
if(CMSIS_Dname STREQUAL "STM32H7P4IIT6")
    target_compile_definitions(STMicroelectronics_stm32h7pxx_dfp_2_0_0 INTERFACE STM32H7P4xx)
endif()
if(CMSIS_Dname STREQUAL "STM32H7P4IIT6Q")
    target_compile_definitions(STMicroelectronics_stm32h7pxx_dfp_2_0_0 INTERFACE STM32H7P4xx)
endif()
if(CMSIS_Dname STREQUAL "STM32H7P4IIZ3Q")
    target_compile_definitions(STMicroelectronics_stm32h7pxx_dfp_2_0_0 INTERFACE STM32H7P4xx)
endif()
if(CMSIS_Dname STREQUAL "STM32H7P4QGT6")
    target_compile_definitions(STMicroelectronics_stm32h7pxx_dfp_2_0_0 INTERFACE STM32H7P4xx)
endif()
if(CMSIS_Dname STREQUAL "STM32H7P4QIT6")
    target_compile_definitions(STMicroelectronics_stm32h7pxx_dfp_2_0_0 INTERFACE STM32H7P4xx)
endif()
if(CMSIS_Dname STREQUAL "STM32H7P4QIT6Q")
    target_compile_definitions(STMicroelectronics_stm32h7pxx_dfp_2_0_0 INTERFACE STM32H7P4xx)
endif()
if(CMSIS_Dname STREQUAL "STM32H7P4VGH6")
    target_compile_definitions(STMicroelectronics_stm32h7pxx_dfp_2_0_0 INTERFACE STM32H7P4xx)
endif()
if(CMSIS_Dname STREQUAL "STM32H7P4VGT6")
    target_compile_definitions(STMicroelectronics_stm32h7pxx_dfp_2_0_0 INTERFACE STM32H7P4xx)
endif()
if(CMSIS_Dname STREQUAL "STM32H7P4VIH6")
    target_compile_definitions(STMicroelectronics_stm32h7pxx_dfp_2_0_0 INTERFACE STM32H7P4xx)
endif()
if(CMSIS_Dname STREQUAL "STM32H7P4VIH6Q")
    target_compile_definitions(STMicroelectronics_stm32h7pxx_dfp_2_0_0 INTERFACE STM32H7P4xx)
endif()
if(CMSIS_Dname STREQUAL "STM32H7P4VIT6")
    target_compile_definitions(STMicroelectronics_stm32h7pxx_dfp_2_0_0 INTERFACE STM32H7P4xx)
endif()
if(CMSIS_Dname STREQUAL "STM32H7P4VIT6Q")
    target_compile_definitions(STMicroelectronics_stm32h7pxx_dfp_2_0_0 INTERFACE STM32H7P4xx)
endif()
if(CMSIS_Dname STREQUAL "STM32H7P4VIZ3Q")
    target_compile_definitions(STMicroelectronics_stm32h7pxx_dfp_2_0_0 INTERFACE STM32H7P4xx)
endif()
if(CMSIS_Dname STREQUAL "STM32H7P4ZGT6")
    target_compile_definitions(STMicroelectronics_stm32h7pxx_dfp_2_0_0 INTERFACE STM32H7P4xx)
endif()
if(CMSIS_Dname STREQUAL "STM32H7P4ZIT6")
    target_compile_definitions(STMicroelectronics_stm32h7pxx_dfp_2_0_0 INTERFACE STM32H7P4xx)
endif()
if(CMSIS_Dname STREQUAL "STM32H7P4ZIT6Q")
    target_compile_definitions(STMicroelectronics_stm32h7pxx_dfp_2_0_0 INTERFACE STM32H7P4xx)
endif()
if(CMSIS_Dname STREQUAL "STM32H7P4ZIZ3Q")
    target_compile_definitions(STMicroelectronics_stm32h7pxx_dfp_2_0_0 INTERFACE STM32H7P4xx)
endif()
if(CMSIS_Dname STREQUAL "STM32H7P5IGK6")
    target_compile_definitions(STMicroelectronics_stm32h7pxx_dfp_2_0_0 INTERFACE STM32H7P5xx)
endif()
if(CMSIS_Dname STREQUAL "STM32H7P5IGT6")
    target_compile_definitions(STMicroelectronics_stm32h7pxx_dfp_2_0_0 INTERFACE STM32H7P5xx)
endif()
if(CMSIS_Dname STREQUAL "STM32H7P5IIK6")
    target_compile_definitions(STMicroelectronics_stm32h7pxx_dfp_2_0_0 INTERFACE STM32H7P5xx)
endif()
if(CMSIS_Dname STREQUAL "STM32H7P5IIK6Q")
    target_compile_definitions(STMicroelectronics_stm32h7pxx_dfp_2_0_0 INTERFACE STM32H7P5xx)
endif()
if(CMSIS_Dname STREQUAL "STM32H7P5IIT6")
    target_compile_definitions(STMicroelectronics_stm32h7pxx_dfp_2_0_0 INTERFACE STM32H7P5xx)
endif()
if(CMSIS_Dname STREQUAL "STM32H7P5IIT6Q")
    target_compile_definitions(STMicroelectronics_stm32h7pxx_dfp_2_0_0 INTERFACE STM32H7P5xx)
endif()
if(CMSIS_Dname STREQUAL "STM32H7P5IIZ3Q")
    target_compile_definitions(STMicroelectronics_stm32h7pxx_dfp_2_0_0 INTERFACE STM32H7P5xx)
endif()
if(CMSIS_Dname STREQUAL "STM32H7P5QGT6")
    target_compile_definitions(STMicroelectronics_stm32h7pxx_dfp_2_0_0 INTERFACE STM32H7P5xx)
endif()
if(CMSIS_Dname STREQUAL "STM32H7P5QIT6")
    target_compile_definitions(STMicroelectronics_stm32h7pxx_dfp_2_0_0 INTERFACE STM32H7P5xx)
endif()
if(CMSIS_Dname STREQUAL "STM32H7P5QIT6Q")
    target_compile_definitions(STMicroelectronics_stm32h7pxx_dfp_2_0_0 INTERFACE STM32H7P5xx)
endif()
if(CMSIS_Dname STREQUAL "STM32H7P5VGH6")
    target_compile_definitions(STMicroelectronics_stm32h7pxx_dfp_2_0_0 INTERFACE STM32H7P5xx)
endif()
if(CMSIS_Dname STREQUAL "STM32H7P5VGT6")
    target_compile_definitions(STMicroelectronics_stm32h7pxx_dfp_2_0_0 INTERFACE STM32H7P5xx)
endif()
if(CMSIS_Dname STREQUAL "STM32H7P5VIH6")
    target_compile_definitions(STMicroelectronics_stm32h7pxx_dfp_2_0_0 INTERFACE STM32H7P5xx)
endif()
if(CMSIS_Dname STREQUAL "STM32H7P5VIH6Q")
    target_compile_definitions(STMicroelectronics_stm32h7pxx_dfp_2_0_0 INTERFACE STM32H7P5xx)
endif()
if(CMSIS_Dname STREQUAL "STM32H7P5VIT6")
    target_compile_definitions(STMicroelectronics_stm32h7pxx_dfp_2_0_0 INTERFACE STM32H7P5xx)
endif()
if(CMSIS_Dname STREQUAL "STM32H7P5VIT6Q")
    target_compile_definitions(STMicroelectronics_stm32h7pxx_dfp_2_0_0 INTERFACE STM32H7P5xx)
endif()
if(CMSIS_Dname STREQUAL "STM32H7P5VIZ3Q")
    target_compile_definitions(STMicroelectronics_stm32h7pxx_dfp_2_0_0 INTERFACE STM32H7P5xx)
endif()
if(CMSIS_Dname STREQUAL "STM32H7P5ZGT6")
    target_compile_definitions(STMicroelectronics_stm32h7pxx_dfp_2_0_0 INTERFACE STM32H7P5xx)
endif()
if(CMSIS_Dname STREQUAL "STM32H7P5ZIT6")
    target_compile_definitions(STMicroelectronics_stm32h7pxx_dfp_2_0_0 INTERFACE STM32H7P5xx)
endif()
if(CMSIS_Dname STREQUAL "STM32H7P5ZIT6Q")
    target_compile_definitions(STMicroelectronics_stm32h7pxx_dfp_2_0_0 INTERFACE STM32H7P5xx)
endif()
if(CMSIS_Dname STREQUAL "STM32H7P5ZIZ3Q")
    target_compile_definitions(STMicroelectronics_stm32h7pxx_dfp_2_0_0 INTERFACE STM32H7P5xx)
endif()


# Include RTE_Components.h globally if needed
if(CMSIS_Tcompiler STREQUAL "IAR")
    target_compile_options(STMicroelectronics_stm32h7pxx_dfp_2_0_0 INTERFACE "SHELL:--preinclude $<QUOTE>${CMAKE_CURRENT_LIST_DIR}/RTE_Components.h$<QUOTE>")
else()
    target_compile_options(STMicroelectronics_stm32h7pxx_dfp_2_0_0 INTERFACE "SHELL:-include $<QUOTE>${CMAKE_CURRENT_LIST_DIR}/RTE_Components.h$<QUOTE>")
endif()





# Enable all components in this package
if(CMSIS_ENTIRE_STMicroelectronics_stm32h7pxx_dfp_2_0_0)
  list(APPEND CMSIS_COMPONENTS_LIST "Cvendor:STMicroelectronics#Cclass:Device#Cgroup:Startup#Cversion:2.0.0")
  list(APPEND CMSIS_COMPONENTS_LIST "Cvendor:STMicroelectronics#Cclass:Device#Cgroup:Startup#Cvariant:SRAM#Cversion:2.0.0")
endif()

# All conditions used by this package

# condition: STMicroelectronics.stm32h7pxx_dfp.2.0.0-beta.2:STM32H7P
# description: 
if((CMSIS_Dname MATCHES "STM32H7P.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13"))
  set(STMicroelectronics.stm32h7pxx_dfp.2.0.0-beta.2_STM32H7P "$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:CMSIS#.*Cgroup:CORE(#.*|$)>,>>")
  message(DEBUG "CMSIS condition STMicroelectronics.stm32h7pxx_dfp.2.0.0-beta.2_STM32H7P enabled")
else()
  set(STMicroelectronics.stm32h7pxx_dfp.2.0.0-beta.2_STM32H7P 0)
endif()


# condition: STMicroelectronics.stm32h7pxx_dfp.2.0.0-beta.2:STM32H7P4
# description: 
if((CMSIS_Dname MATCHES "STM32H7P4.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13"))
  set(STMicroelectronics.stm32h7pxx_dfp.2.0.0-beta.2_STM32H7P4 "1")
  message(DEBUG "CMSIS condition STMicroelectronics.stm32h7pxx_dfp.2.0.0-beta.2_STM32H7P4 enabled")
else()
  set(STMicroelectronics.stm32h7pxx_dfp.2.0.0-beta.2_STM32H7P4 0)
endif()


# condition: STMicroelectronics.stm32h7pxx_dfp.2.0.0-beta.2:STM32H7P4xG ARMCC
# description: 
if(((CMSIS_Dname MATCHES "STM32H7P4.G.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND CMSIS_Tcompiler STREQUAL "ARMCC"))
  set(STMicroelectronics.stm32h7pxx_dfp.2.0.0-beta.2_STM32H7P4xG_ARMCC "1")
  message(DEBUG "CMSIS condition STMicroelectronics.stm32h7pxx_dfp.2.0.0-beta.2_STM32H7P4xG_ARMCC enabled")
else()
  set(STMicroelectronics.stm32h7pxx_dfp.2.0.0-beta.2_STM32H7P4xG_ARMCC 0)
endif()


# condition: STMicroelectronics.stm32h7pxx_dfp.2.0.0-beta.2:STM32H7P4xG GCC
# description: 
if(((CMSIS_Dname MATCHES "STM32H7P4.G.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND CMSIS_Tcompiler STREQUAL "GCC"))
  set(STMicroelectronics.stm32h7pxx_dfp.2.0.0-beta.2_STM32H7P4xG_GCC "1")
  message(DEBUG "CMSIS condition STMicroelectronics.stm32h7pxx_dfp.2.0.0-beta.2_STM32H7P4xG_GCC enabled")
else()
  set(STMicroelectronics.stm32h7pxx_dfp.2.0.0-beta.2_STM32H7P4xG_GCC 0)
endif()


# condition: STMicroelectronics.stm32h7pxx_dfp.2.0.0-beta.2:STM32H7P4xG IAR
# description: 
if(((CMSIS_Dname MATCHES "STM32H7P4.G.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND CMSIS_Tcompiler STREQUAL "IAR"))
  set(STMicroelectronics.stm32h7pxx_dfp.2.0.0-beta.2_STM32H7P4xG_IAR "1")
  message(DEBUG "CMSIS condition STMicroelectronics.stm32h7pxx_dfp.2.0.0-beta.2_STM32H7P4xG_IAR enabled")
else()
  set(STMicroelectronics.stm32h7pxx_dfp.2.0.0-beta.2_STM32H7P4xG_IAR 0)
endif()


# condition: STMicroelectronics.stm32h7pxx_dfp.2.0.0-beta.2:STM32H7P4xI ARMCC
# description: 
if(((CMSIS_Dname MATCHES "STM32H7P4.I.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND CMSIS_Tcompiler STREQUAL "ARMCC"))
  set(STMicroelectronics.stm32h7pxx_dfp.2.0.0-beta.2_STM32H7P4xI_ARMCC "1")
  message(DEBUG "CMSIS condition STMicroelectronics.stm32h7pxx_dfp.2.0.0-beta.2_STM32H7P4xI_ARMCC enabled")
else()
  set(STMicroelectronics.stm32h7pxx_dfp.2.0.0-beta.2_STM32H7P4xI_ARMCC 0)
endif()


# condition: STMicroelectronics.stm32h7pxx_dfp.2.0.0-beta.2:STM32H7P4xI GCC
# description: 
if(((CMSIS_Dname MATCHES "STM32H7P4.I.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND CMSIS_Tcompiler STREQUAL "GCC"))
  set(STMicroelectronics.stm32h7pxx_dfp.2.0.0-beta.2_STM32H7P4xI_GCC "1")
  message(DEBUG "CMSIS condition STMicroelectronics.stm32h7pxx_dfp.2.0.0-beta.2_STM32H7P4xI_GCC enabled")
else()
  set(STMicroelectronics.stm32h7pxx_dfp.2.0.0-beta.2_STM32H7P4xI_GCC 0)
endif()


# condition: STMicroelectronics.stm32h7pxx_dfp.2.0.0-beta.2:STM32H7P4xI IAR
# description: 
if(((CMSIS_Dname MATCHES "STM32H7P4.I.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND CMSIS_Tcompiler STREQUAL "IAR"))
  set(STMicroelectronics.stm32h7pxx_dfp.2.0.0-beta.2_STM32H7P4xI_IAR "1")
  message(DEBUG "CMSIS condition STMicroelectronics.stm32h7pxx_dfp.2.0.0-beta.2_STM32H7P4xI_IAR enabled")
else()
  set(STMicroelectronics.stm32h7pxx_dfp.2.0.0-beta.2_STM32H7P4xI_IAR 0)
endif()


# condition: STMicroelectronics.stm32h7pxx_dfp.2.0.0-beta.2:STM32H7P4xx ARMCC
# description: 
if(((CMSIS_Dname MATCHES "STM32H7P4...*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND CMSIS_Tcompiler STREQUAL "ARMCC"))
  set(STMicroelectronics.stm32h7pxx_dfp.2.0.0-beta.2_STM32H7P4xx_ARMCC "1")
  message(DEBUG "CMSIS condition STMicroelectronics.stm32h7pxx_dfp.2.0.0-beta.2_STM32H7P4xx_ARMCC enabled")
else()
  set(STMicroelectronics.stm32h7pxx_dfp.2.0.0-beta.2_STM32H7P4xx_ARMCC 0)
endif()


# condition: STMicroelectronics.stm32h7pxx_dfp.2.0.0-beta.2:STM32H7P4xx GCC
# description: 
if(((CMSIS_Dname MATCHES "STM32H7P4...*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND CMSIS_Tcompiler STREQUAL "GCC"))
  set(STMicroelectronics.stm32h7pxx_dfp.2.0.0-beta.2_STM32H7P4xx_GCC "1")
  message(DEBUG "CMSIS condition STMicroelectronics.stm32h7pxx_dfp.2.0.0-beta.2_STM32H7P4xx_GCC enabled")
else()
  set(STMicroelectronics.stm32h7pxx_dfp.2.0.0-beta.2_STM32H7P4xx_GCC 0)
endif()


# condition: STMicroelectronics.stm32h7pxx_dfp.2.0.0-beta.2:STM32H7P4xx IAR
# description: 
if(((CMSIS_Dname MATCHES "STM32H7P4...*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND CMSIS_Tcompiler STREQUAL "IAR"))
  set(STMicroelectronics.stm32h7pxx_dfp.2.0.0-beta.2_STM32H7P4xx_IAR "1")
  message(DEBUG "CMSIS condition STMicroelectronics.stm32h7pxx_dfp.2.0.0-beta.2_STM32H7P4xx_IAR enabled")
else()
  set(STMicroelectronics.stm32h7pxx_dfp.2.0.0-beta.2_STM32H7P4xx_IAR 0)
endif()


# condition: STMicroelectronics.stm32h7pxx_dfp.2.0.0-beta.2:STM32H7P5
# description: 
if((CMSIS_Dname MATCHES "STM32H7P5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13"))
  set(STMicroelectronics.stm32h7pxx_dfp.2.0.0-beta.2_STM32H7P5 "1")
  message(DEBUG "CMSIS condition STMicroelectronics.stm32h7pxx_dfp.2.0.0-beta.2_STM32H7P5 enabled")
else()
  set(STMicroelectronics.stm32h7pxx_dfp.2.0.0-beta.2_STM32H7P5 0)
endif()


# condition: STMicroelectronics.stm32h7pxx_dfp.2.0.0-beta.2:STM32H7P5xG ARMCC
# description: 
if(((CMSIS_Dname MATCHES "STM32H7P5.G.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND CMSIS_Tcompiler STREQUAL "ARMCC"))
  set(STMicroelectronics.stm32h7pxx_dfp.2.0.0-beta.2_STM32H7P5xG_ARMCC "1")
  message(DEBUG "CMSIS condition STMicroelectronics.stm32h7pxx_dfp.2.0.0-beta.2_STM32H7P5xG_ARMCC enabled")
else()
  set(STMicroelectronics.stm32h7pxx_dfp.2.0.0-beta.2_STM32H7P5xG_ARMCC 0)
endif()


# condition: STMicroelectronics.stm32h7pxx_dfp.2.0.0-beta.2:STM32H7P5xG GCC
# description: 
if(((CMSIS_Dname MATCHES "STM32H7P5.G.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND CMSIS_Tcompiler STREQUAL "GCC"))
  set(STMicroelectronics.stm32h7pxx_dfp.2.0.0-beta.2_STM32H7P5xG_GCC "1")
  message(DEBUG "CMSIS condition STMicroelectronics.stm32h7pxx_dfp.2.0.0-beta.2_STM32H7P5xG_GCC enabled")
else()
  set(STMicroelectronics.stm32h7pxx_dfp.2.0.0-beta.2_STM32H7P5xG_GCC 0)
endif()


# condition: STMicroelectronics.stm32h7pxx_dfp.2.0.0-beta.2:STM32H7P5xG IAR
# description: 
if(((CMSIS_Dname MATCHES "STM32H7P5.G.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND CMSIS_Tcompiler STREQUAL "IAR"))
  set(STMicroelectronics.stm32h7pxx_dfp.2.0.0-beta.2_STM32H7P5xG_IAR "1")
  message(DEBUG "CMSIS condition STMicroelectronics.stm32h7pxx_dfp.2.0.0-beta.2_STM32H7P5xG_IAR enabled")
else()
  set(STMicroelectronics.stm32h7pxx_dfp.2.0.0-beta.2_STM32H7P5xG_IAR 0)
endif()


# condition: STMicroelectronics.stm32h7pxx_dfp.2.0.0-beta.2:STM32H7P5xI ARMCC
# description: 
if(((CMSIS_Dname MATCHES "STM32H7P5.I.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND CMSIS_Tcompiler STREQUAL "ARMCC"))
  set(STMicroelectronics.stm32h7pxx_dfp.2.0.0-beta.2_STM32H7P5xI_ARMCC "1")
  message(DEBUG "CMSIS condition STMicroelectronics.stm32h7pxx_dfp.2.0.0-beta.2_STM32H7P5xI_ARMCC enabled")
else()
  set(STMicroelectronics.stm32h7pxx_dfp.2.0.0-beta.2_STM32H7P5xI_ARMCC 0)
endif()


# condition: STMicroelectronics.stm32h7pxx_dfp.2.0.0-beta.2:STM32H7P5xI GCC
# description: 
if(((CMSIS_Dname MATCHES "STM32H7P5.I.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND CMSIS_Tcompiler STREQUAL "GCC"))
  set(STMicroelectronics.stm32h7pxx_dfp.2.0.0-beta.2_STM32H7P5xI_GCC "1")
  message(DEBUG "CMSIS condition STMicroelectronics.stm32h7pxx_dfp.2.0.0-beta.2_STM32H7P5xI_GCC enabled")
else()
  set(STMicroelectronics.stm32h7pxx_dfp.2.0.0-beta.2_STM32H7P5xI_GCC 0)
endif()


# condition: STMicroelectronics.stm32h7pxx_dfp.2.0.0-beta.2:STM32H7P5xI IAR
# description: 
if(((CMSIS_Dname MATCHES "STM32H7P5.I.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND CMSIS_Tcompiler STREQUAL "IAR"))
  set(STMicroelectronics.stm32h7pxx_dfp.2.0.0-beta.2_STM32H7P5xI_IAR "1")
  message(DEBUG "CMSIS condition STMicroelectronics.stm32h7pxx_dfp.2.0.0-beta.2_STM32H7P5xI_IAR enabled")
else()
  set(STMicroelectronics.stm32h7pxx_dfp.2.0.0-beta.2_STM32H7P5xI_IAR 0)
endif()


# condition: STMicroelectronics.stm32h7pxx_dfp.2.0.0-beta.2:STM32H7P5xx ARMCC
# description: 
if(((CMSIS_Dname MATCHES "STM32H7P5...*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND CMSIS_Tcompiler STREQUAL "ARMCC"))
  set(STMicroelectronics.stm32h7pxx_dfp.2.0.0-beta.2_STM32H7P5xx_ARMCC "1")
  message(DEBUG "CMSIS condition STMicroelectronics.stm32h7pxx_dfp.2.0.0-beta.2_STM32H7P5xx_ARMCC enabled")
else()
  set(STMicroelectronics.stm32h7pxx_dfp.2.0.0-beta.2_STM32H7P5xx_ARMCC 0)
endif()


# condition: STMicroelectronics.stm32h7pxx_dfp.2.0.0-beta.2:STM32H7P5xx GCC
# description: 
if(((CMSIS_Dname MATCHES "STM32H7P5...*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND CMSIS_Tcompiler STREQUAL "GCC"))
  set(STMicroelectronics.stm32h7pxx_dfp.2.0.0-beta.2_STM32H7P5xx_GCC "1")
  message(DEBUG "CMSIS condition STMicroelectronics.stm32h7pxx_dfp.2.0.0-beta.2_STM32H7P5xx_GCC enabled")
else()
  set(STMicroelectronics.stm32h7pxx_dfp.2.0.0-beta.2_STM32H7P5xx_GCC 0)
endif()


# condition: STMicroelectronics.stm32h7pxx_dfp.2.0.0-beta.2:STM32H7P5xx IAR
# description: 
if(((CMSIS_Dname MATCHES "STM32H7P5...*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND CMSIS_Tcompiler STREQUAL "IAR"))
  set(STMicroelectronics.stm32h7pxx_dfp.2.0.0-beta.2_STM32H7P5xx_IAR "1")
  message(DEBUG "CMSIS condition STMicroelectronics.stm32h7pxx_dfp.2.0.0-beta.2_STM32H7P5xx_IAR enabled")
else()
  set(STMicroelectronics.stm32h7pxx_dfp.2.0.0-beta.2_STM32H7P5xx_IAR 0)
endif()


# condition: STMicroelectronics.stm32h7pxx_dfp.2.0.0:STM32H7P
# description: 
if((CMSIS_Dname MATCHES "STM32H7P.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13"))
  set(STMicroelectronics.stm32h7pxx_dfp.2.0.0_STM32H7P "$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:CMSIS#.*Cgroup:CORE(#.*|$)>,>>")
  message(DEBUG "CMSIS condition STMicroelectronics.stm32h7pxx_dfp.2.0.0_STM32H7P enabled")
else()
  set(STMicroelectronics.stm32h7pxx_dfp.2.0.0_STM32H7P 0)
endif()


# condition: STMicroelectronics.stm32h7pxx_dfp.2.0.0:STM32H7P4
# description: 
if((CMSIS_Dname MATCHES "STM32H7P4.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13"))
  set(STMicroelectronics.stm32h7pxx_dfp.2.0.0_STM32H7P4 "1")
  message(DEBUG "CMSIS condition STMicroelectronics.stm32h7pxx_dfp.2.0.0_STM32H7P4 enabled")
else()
  set(STMicroelectronics.stm32h7pxx_dfp.2.0.0_STM32H7P4 0)
endif()


# condition: STMicroelectronics.stm32h7pxx_dfp.2.0.0:STM32H7P4xG ARMCC
# description: 
if(((CMSIS_Dname MATCHES "STM32H7P4.G.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND CMSIS_Tcompiler STREQUAL "ARMCC"))
  set(STMicroelectronics.stm32h7pxx_dfp.2.0.0_STM32H7P4xG_ARMCC "1")
  message(DEBUG "CMSIS condition STMicroelectronics.stm32h7pxx_dfp.2.0.0_STM32H7P4xG_ARMCC enabled")
else()
  set(STMicroelectronics.stm32h7pxx_dfp.2.0.0_STM32H7P4xG_ARMCC 0)
endif()


# condition: STMicroelectronics.stm32h7pxx_dfp.2.0.0:STM32H7P4xG GCC
# description: 
if(((CMSIS_Dname MATCHES "STM32H7P4.G.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND CMSIS_Tcompiler STREQUAL "GCC"))
  set(STMicroelectronics.stm32h7pxx_dfp.2.0.0_STM32H7P4xG_GCC "1")
  message(DEBUG "CMSIS condition STMicroelectronics.stm32h7pxx_dfp.2.0.0_STM32H7P4xG_GCC enabled")
else()
  set(STMicroelectronics.stm32h7pxx_dfp.2.0.0_STM32H7P4xG_GCC 0)
endif()


# condition: STMicroelectronics.stm32h7pxx_dfp.2.0.0:STM32H7P4xG IAR
# description: 
if(((CMSIS_Dname MATCHES "STM32H7P4.G.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND CMSIS_Tcompiler STREQUAL "IAR"))
  set(STMicroelectronics.stm32h7pxx_dfp.2.0.0_STM32H7P4xG_IAR "1")
  message(DEBUG "CMSIS condition STMicroelectronics.stm32h7pxx_dfp.2.0.0_STM32H7P4xG_IAR enabled")
else()
  set(STMicroelectronics.stm32h7pxx_dfp.2.0.0_STM32H7P4xG_IAR 0)
endif()


# condition: STMicroelectronics.stm32h7pxx_dfp.2.0.0:STM32H7P4xI ARMCC
# description: 
if(((CMSIS_Dname MATCHES "STM32H7P4.I.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND CMSIS_Tcompiler STREQUAL "ARMCC"))
  set(STMicroelectronics.stm32h7pxx_dfp.2.0.0_STM32H7P4xI_ARMCC "1")
  message(DEBUG "CMSIS condition STMicroelectronics.stm32h7pxx_dfp.2.0.0_STM32H7P4xI_ARMCC enabled")
else()
  set(STMicroelectronics.stm32h7pxx_dfp.2.0.0_STM32H7P4xI_ARMCC 0)
endif()


# condition: STMicroelectronics.stm32h7pxx_dfp.2.0.0:STM32H7P4xI GCC
# description: 
if(((CMSIS_Dname MATCHES "STM32H7P4.I.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND CMSIS_Tcompiler STREQUAL "GCC"))
  set(STMicroelectronics.stm32h7pxx_dfp.2.0.0_STM32H7P4xI_GCC "1")
  message(DEBUG "CMSIS condition STMicroelectronics.stm32h7pxx_dfp.2.0.0_STM32H7P4xI_GCC enabled")
else()
  set(STMicroelectronics.stm32h7pxx_dfp.2.0.0_STM32H7P4xI_GCC 0)
endif()


# condition: STMicroelectronics.stm32h7pxx_dfp.2.0.0:STM32H7P4xI IAR
# description: 
if(((CMSIS_Dname MATCHES "STM32H7P4.I.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND CMSIS_Tcompiler STREQUAL "IAR"))
  set(STMicroelectronics.stm32h7pxx_dfp.2.0.0_STM32H7P4xI_IAR "1")
  message(DEBUG "CMSIS condition STMicroelectronics.stm32h7pxx_dfp.2.0.0_STM32H7P4xI_IAR enabled")
else()
  set(STMicroelectronics.stm32h7pxx_dfp.2.0.0_STM32H7P4xI_IAR 0)
endif()


# condition: STMicroelectronics.stm32h7pxx_dfp.2.0.0:STM32H7P4xx ARMCC
# description: 
if(((CMSIS_Dname MATCHES "STM32H7P4...*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND CMSIS_Tcompiler STREQUAL "ARMCC"))
  set(STMicroelectronics.stm32h7pxx_dfp.2.0.0_STM32H7P4xx_ARMCC "1")
  message(DEBUG "CMSIS condition STMicroelectronics.stm32h7pxx_dfp.2.0.0_STM32H7P4xx_ARMCC enabled")
else()
  set(STMicroelectronics.stm32h7pxx_dfp.2.0.0_STM32H7P4xx_ARMCC 0)
endif()


# condition: STMicroelectronics.stm32h7pxx_dfp.2.0.0:STM32H7P4xx GCC
# description: 
if(((CMSIS_Dname MATCHES "STM32H7P4...*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND CMSIS_Tcompiler STREQUAL "GCC"))
  set(STMicroelectronics.stm32h7pxx_dfp.2.0.0_STM32H7P4xx_GCC "1")
  message(DEBUG "CMSIS condition STMicroelectronics.stm32h7pxx_dfp.2.0.0_STM32H7P4xx_GCC enabled")
else()
  set(STMicroelectronics.stm32h7pxx_dfp.2.0.0_STM32H7P4xx_GCC 0)
endif()


# condition: STMicroelectronics.stm32h7pxx_dfp.2.0.0:STM32H7P4xx IAR
# description: 
if(((CMSIS_Dname MATCHES "STM32H7P4...*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND CMSIS_Tcompiler STREQUAL "IAR"))
  set(STMicroelectronics.stm32h7pxx_dfp.2.0.0_STM32H7P4xx_IAR "1")
  message(DEBUG "CMSIS condition STMicroelectronics.stm32h7pxx_dfp.2.0.0_STM32H7P4xx_IAR enabled")
else()
  set(STMicroelectronics.stm32h7pxx_dfp.2.0.0_STM32H7P4xx_IAR 0)
endif()


# condition: STMicroelectronics.stm32h7pxx_dfp.2.0.0:STM32H7P5
# description: 
if((CMSIS_Dname MATCHES "STM32H7P5.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13"))
  set(STMicroelectronics.stm32h7pxx_dfp.2.0.0_STM32H7P5 "1")
  message(DEBUG "CMSIS condition STMicroelectronics.stm32h7pxx_dfp.2.0.0_STM32H7P5 enabled")
else()
  set(STMicroelectronics.stm32h7pxx_dfp.2.0.0_STM32H7P5 0)
endif()


# condition: STMicroelectronics.stm32h7pxx_dfp.2.0.0:STM32H7P5xG ARMCC
# description: 
if(((CMSIS_Dname MATCHES "STM32H7P5.G.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND CMSIS_Tcompiler STREQUAL "ARMCC"))
  set(STMicroelectronics.stm32h7pxx_dfp.2.0.0_STM32H7P5xG_ARMCC "1")
  message(DEBUG "CMSIS condition STMicroelectronics.stm32h7pxx_dfp.2.0.0_STM32H7P5xG_ARMCC enabled")
else()
  set(STMicroelectronics.stm32h7pxx_dfp.2.0.0_STM32H7P5xG_ARMCC 0)
endif()


# condition: STMicroelectronics.stm32h7pxx_dfp.2.0.0:STM32H7P5xG GCC
# description: 
if(((CMSIS_Dname MATCHES "STM32H7P5.G.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND CMSIS_Tcompiler STREQUAL "GCC"))
  set(STMicroelectronics.stm32h7pxx_dfp.2.0.0_STM32H7P5xG_GCC "1")
  message(DEBUG "CMSIS condition STMicroelectronics.stm32h7pxx_dfp.2.0.0_STM32H7P5xG_GCC enabled")
else()
  set(STMicroelectronics.stm32h7pxx_dfp.2.0.0_STM32H7P5xG_GCC 0)
endif()


# condition: STMicroelectronics.stm32h7pxx_dfp.2.0.0:STM32H7P5xG IAR
# description: 
if(((CMSIS_Dname MATCHES "STM32H7P5.G.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND CMSIS_Tcompiler STREQUAL "IAR"))
  set(STMicroelectronics.stm32h7pxx_dfp.2.0.0_STM32H7P5xG_IAR "1")
  message(DEBUG "CMSIS condition STMicroelectronics.stm32h7pxx_dfp.2.0.0_STM32H7P5xG_IAR enabled")
else()
  set(STMicroelectronics.stm32h7pxx_dfp.2.0.0_STM32H7P5xG_IAR 0)
endif()


# condition: STMicroelectronics.stm32h7pxx_dfp.2.0.0:STM32H7P5xI ARMCC
# description: 
if(((CMSIS_Dname MATCHES "STM32H7P5.I.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND CMSIS_Tcompiler STREQUAL "ARMCC"))
  set(STMicroelectronics.stm32h7pxx_dfp.2.0.0_STM32H7P5xI_ARMCC "1")
  message(DEBUG "CMSIS condition STMicroelectronics.stm32h7pxx_dfp.2.0.0_STM32H7P5xI_ARMCC enabled")
else()
  set(STMicroelectronics.stm32h7pxx_dfp.2.0.0_STM32H7P5xI_ARMCC 0)
endif()


# condition: STMicroelectronics.stm32h7pxx_dfp.2.0.0:STM32H7P5xI GCC
# description: 
if(((CMSIS_Dname MATCHES "STM32H7P5.I.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND CMSIS_Tcompiler STREQUAL "GCC"))
  set(STMicroelectronics.stm32h7pxx_dfp.2.0.0_STM32H7P5xI_GCC "1")
  message(DEBUG "CMSIS condition STMicroelectronics.stm32h7pxx_dfp.2.0.0_STM32H7P5xI_GCC enabled")
else()
  set(STMicroelectronics.stm32h7pxx_dfp.2.0.0_STM32H7P5xI_GCC 0)
endif()


# condition: STMicroelectronics.stm32h7pxx_dfp.2.0.0:STM32H7P5xI IAR
# description: 
if(((CMSIS_Dname MATCHES "STM32H7P5.I.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND CMSIS_Tcompiler STREQUAL "IAR"))
  set(STMicroelectronics.stm32h7pxx_dfp.2.0.0_STM32H7P5xI_IAR "1")
  message(DEBUG "CMSIS condition STMicroelectronics.stm32h7pxx_dfp.2.0.0_STM32H7P5xI_IAR enabled")
else()
  set(STMicroelectronics.stm32h7pxx_dfp.2.0.0_STM32H7P5xI_IAR 0)
endif()


# condition: STMicroelectronics.stm32h7pxx_dfp.2.0.0:STM32H7P5xx ARMCC
# description: 
if(((CMSIS_Dname MATCHES "STM32H7P5...*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND CMSIS_Tcompiler STREQUAL "ARMCC"))
  set(STMicroelectronics.stm32h7pxx_dfp.2.0.0_STM32H7P5xx_ARMCC "1")
  message(DEBUG "CMSIS condition STMicroelectronics.stm32h7pxx_dfp.2.0.0_STM32H7P5xx_ARMCC enabled")
else()
  set(STMicroelectronics.stm32h7pxx_dfp.2.0.0_STM32H7P5xx_ARMCC 0)
endif()


# condition: STMicroelectronics.stm32h7pxx_dfp.2.0.0:STM32H7P5xx GCC
# description: 
if(((CMSIS_Dname MATCHES "STM32H7P5...*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND CMSIS_Tcompiler STREQUAL "GCC"))
  set(STMicroelectronics.stm32h7pxx_dfp.2.0.0_STM32H7P5xx_GCC "1")
  message(DEBUG "CMSIS condition STMicroelectronics.stm32h7pxx_dfp.2.0.0_STM32H7P5xx_GCC enabled")
else()
  set(STMicroelectronics.stm32h7pxx_dfp.2.0.0_STM32H7P5xx_GCC 0)
endif()


# condition: STMicroelectronics.stm32h7pxx_dfp.2.0.0:STM32H7P5xx IAR
# description: 
if(((CMSIS_Dname MATCHES "STM32H7P5...*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND CMSIS_Tcompiler STREQUAL "IAR"))
  set(STMicroelectronics.stm32h7pxx_dfp.2.0.0_STM32H7P5xx_IAR "1")
  message(DEBUG "CMSIS condition STMicroelectronics.stm32h7pxx_dfp.2.0.0_STM32H7P5xx_IAR enabled")
else()
  set(STMicroelectronics.stm32h7pxx_dfp.2.0.0_STM32H7P5xx_IAR 0)
endif()

# Files and components in this package
if("Cvendor:STMicroelectronics#Cclass:Device#Cgroup:Startup#Cversion:2.0.0" IN_LIST CMSIS_COMPONENTS_LIST)  # System Startup for STMicroelectronics STM32H7P Series
  message(DEBUG "Using component Device_Startup_2_0_0")
  target_compile_definitions(STMicroelectronics_stm32h7pxx_dfp_2_0_0 INTERFACE "$<${STMicroelectronics.stm32h7pxx_dfp.2.0.0_STM32H7P}:-DCMSIS_USE_Device_Startup_2_0_0=1>")
  target_include_directories(STMicroelectronics_stm32h7pxx_dfp_2_0_0 INTERFACE "$<${STMicroelectronics.stm32h7pxx_dfp.2.0.0_STM32H7P}:${CMAKE_CURRENT_LIST_DIR}/Include>")
  target_include_directories(STMicroelectronics_stm32h7pxx_dfp_2_0_0 INTERFACE "$<${STMicroelectronics.stm32h7pxx_dfp.2.0.0_STM32H7P}:${CMAKE_CURRENT_LIST_DIR}/Include/>")
  if(EXISTS ${CMSIS_RTE_FOLDER}/Device/${CMSIS_Dname}/system_stm32h7pxx.c)
    target_sources(STMicroelectronics_stm32h7pxx_dfp_2_0_0 INTERFACE "$<${STMicroelectronics.stm32h7pxx_dfp.2.0.0_STM32H7P}:${CMSIS_RTE_FOLDER}/Device/${CMSIS_Dname}/system_stm32h7pxx.c>")
  else()
    target_sources(STMicroelectronics_stm32h7pxx_dfp_2_0_0 INTERFACE "$<${STMicroelectronics.stm32h7pxx_dfp.2.0.0_STM32H7P}:${CMAKE_CURRENT_LIST_DIR}/Source/Templates/system_stm32h7pxx.c>")
  endif()
  if(EXISTS ${CMSIS_RTE_FOLDER}/Device/${CMSIS_Dname}/startup_stm32h7p4xx.c)
    target_sources(STMicroelectronics_stm32h7pxx_dfp_2_0_0 INTERFACE "$<$<AND:${STMicroelectronics.stm32h7pxx_dfp.2.0.0_STM32H7P},${STMicroelectronics.stm32h7pxx_dfp.2.0.0_STM32H7P4}>:${CMSIS_RTE_FOLDER}/Device/${CMSIS_Dname}/startup_stm32h7p4xx.c>")
  else()
    target_sources(STMicroelectronics_stm32h7pxx_dfp_2_0_0 INTERFACE "$<$<AND:${STMicroelectronics.stm32h7pxx_dfp.2.0.0_STM32H7P},${STMicroelectronics.stm32h7pxx_dfp.2.0.0_STM32H7P4}>:${CMAKE_CURRENT_LIST_DIR}/Source/startup_stm32h7p4xx.c>")
  endif()
  if(EXISTS ${CMSIS_RTE_FOLDER}/Device/${CMSIS_Dname}/stm32h7p4xg_flash.ld)
    target_link_options(STMicroelectronics_stm32h7pxx_dfp_2_0_0 INTERFACE "$<$<AND:${STMicroelectronics.stm32h7pxx_dfp.2.0.0_STM32H7P},${STMicroelectronics.stm32h7pxx_dfp.2.0.0_STM32H7P4xG_GCC}>:-T${CMSIS_RTE_FOLDER}/Device/${CMSIS_Dname}/stm32h7p4xg_flash.ld>")
  else()
    target_link_options(STMicroelectronics_stm32h7pxx_dfp_2_0_0 INTERFACE "$<$<AND:${STMicroelectronics.stm32h7pxx_dfp.2.0.0_STM32H7P},${STMicroelectronics.stm32h7pxx_dfp.2.0.0_STM32H7P4xG_GCC}>:-T${CMAKE_CURRENT_LIST_DIR}/Source/Templates/gcc/linker/stm32h7p4xg_flash.ld>")
  endif()
  if(EXISTS ${CMSIS_RTE_FOLDER}/Device/${CMSIS_Dname}/stm32h7p4xi_flash.ld)
    target_link_options(STMicroelectronics_stm32h7pxx_dfp_2_0_0 INTERFACE "$<$<AND:${STMicroelectronics.stm32h7pxx_dfp.2.0.0_STM32H7P},${STMicroelectronics.stm32h7pxx_dfp.2.0.0_STM32H7P4xI_GCC}>:-T${CMSIS_RTE_FOLDER}/Device/${CMSIS_Dname}/stm32h7p4xi_flash.ld>")
  else()
    target_link_options(STMicroelectronics_stm32h7pxx_dfp_2_0_0 INTERFACE "$<$<AND:${STMicroelectronics.stm32h7pxx_dfp.2.0.0_STM32H7P},${STMicroelectronics.stm32h7pxx_dfp.2.0.0_STM32H7P4xI_GCC}>:-T${CMAKE_CURRENT_LIST_DIR}/Source/Templates/gcc/linker/stm32h7p4xi_flash.ld>")
  endif()
  if(EXISTS ${CMSIS_RTE_FOLDER}/Device/${CMSIS_Dname}/startup_stm32h7p5xx.c)
    target_sources(STMicroelectronics_stm32h7pxx_dfp_2_0_0 INTERFACE "$<$<AND:${STMicroelectronics.stm32h7pxx_dfp.2.0.0_STM32H7P},${STMicroelectronics.stm32h7pxx_dfp.2.0.0_STM32H7P5}>:${CMSIS_RTE_FOLDER}/Device/${CMSIS_Dname}/startup_stm32h7p5xx.c>")
  else()
    target_sources(STMicroelectronics_stm32h7pxx_dfp_2_0_0 INTERFACE "$<$<AND:${STMicroelectronics.stm32h7pxx_dfp.2.0.0_STM32H7P},${STMicroelectronics.stm32h7pxx_dfp.2.0.0_STM32H7P5}>:${CMAKE_CURRENT_LIST_DIR}/Source/startup_stm32h7p5xx.c>")
  endif()
  if(EXISTS ${CMSIS_RTE_FOLDER}/Device/${CMSIS_Dname}/stm32h7p5xg_flash.ld)
    target_link_options(STMicroelectronics_stm32h7pxx_dfp_2_0_0 INTERFACE "$<$<AND:${STMicroelectronics.stm32h7pxx_dfp.2.0.0_STM32H7P},${STMicroelectronics.stm32h7pxx_dfp.2.0.0_STM32H7P5xG_GCC}>:-T${CMSIS_RTE_FOLDER}/Device/${CMSIS_Dname}/stm32h7p5xg_flash.ld>")
  else()
    target_link_options(STMicroelectronics_stm32h7pxx_dfp_2_0_0 INTERFACE "$<$<AND:${STMicroelectronics.stm32h7pxx_dfp.2.0.0_STM32H7P},${STMicroelectronics.stm32h7pxx_dfp.2.0.0_STM32H7P5xG_GCC}>:-T${CMAKE_CURRENT_LIST_DIR}/Source/Templates/gcc/linker/stm32h7p5xg_flash.ld>")
  endif()
  if(EXISTS ${CMSIS_RTE_FOLDER}/Device/${CMSIS_Dname}/stm32h7p5xi_flash.ld)
    target_link_options(STMicroelectronics_stm32h7pxx_dfp_2_0_0 INTERFACE "$<$<AND:${STMicroelectronics.stm32h7pxx_dfp.2.0.0_STM32H7P},${STMicroelectronics.stm32h7pxx_dfp.2.0.0_STM32H7P5xI_GCC}>:-T${CMSIS_RTE_FOLDER}/Device/${CMSIS_Dname}/stm32h7p5xi_flash.ld>")
  else()
    target_link_options(STMicroelectronics_stm32h7pxx_dfp_2_0_0 INTERFACE "$<$<AND:${STMicroelectronics.stm32h7pxx_dfp.2.0.0_STM32H7P},${STMicroelectronics.stm32h7pxx_dfp.2.0.0_STM32H7P5xI_GCC}>:-T${CMAKE_CURRENT_LIST_DIR}/Source/Templates/gcc/linker/stm32h7p5xi_flash.ld>")
  endif()
endif()

if("Cvendor:STMicroelectronics#Cclass:Device#Cgroup:Startup#Cvariant:SRAM#Cversion:2.0.0" IN_LIST CMSIS_COMPONENTS_LIST)  # System Startup for STMicroelectronics STM32H7P Series
  message(DEBUG "Using component Device_Startup_SRAM_2_0_0")
  target_compile_definitions(STMicroelectronics_stm32h7pxx_dfp_2_0_0 INTERFACE "$<${STMicroelectronics.stm32h7pxx_dfp.2.0.0_STM32H7P}:-DCMSIS_USE_Device_Startup_SRAM_2_0_0=1>")
  target_include_directories(STMicroelectronics_stm32h7pxx_dfp_2_0_0 INTERFACE "$<${STMicroelectronics.stm32h7pxx_dfp.2.0.0_STM32H7P}:${CMAKE_CURRENT_LIST_DIR}/Include>")
  target_include_directories(STMicroelectronics_stm32h7pxx_dfp_2_0_0 INTERFACE "$<${STMicroelectronics.stm32h7pxx_dfp.2.0.0_STM32H7P}:${CMAKE_CURRENT_LIST_DIR}/Include/>")
  if(EXISTS ${CMSIS_RTE_FOLDER}/Device/${CMSIS_Dname}/system_stm32h7pxx.c)
    target_sources(STMicroelectronics_stm32h7pxx_dfp_2_0_0 INTERFACE "$<${STMicroelectronics.stm32h7pxx_dfp.2.0.0_STM32H7P}:${CMSIS_RTE_FOLDER}/Device/${CMSIS_Dname}/system_stm32h7pxx.c>")
  else()
    target_sources(STMicroelectronics_stm32h7pxx_dfp_2_0_0 INTERFACE "$<${STMicroelectronics.stm32h7pxx_dfp.2.0.0_STM32H7P}:${CMAKE_CURRENT_LIST_DIR}/Source/Templates/system_stm32h7pxx.c>")
  endif()
  if(EXISTS ${CMSIS_RTE_FOLDER}/Device/${CMSIS_Dname}/startup_stm32h7p4xx.c)
    target_sources(STMicroelectronics_stm32h7pxx_dfp_2_0_0 INTERFACE "$<$<AND:${STMicroelectronics.stm32h7pxx_dfp.2.0.0_STM32H7P},${STMicroelectronics.stm32h7pxx_dfp.2.0.0_STM32H7P4}>:${CMSIS_RTE_FOLDER}/Device/${CMSIS_Dname}/startup_stm32h7p4xx.c>")
  else()
    target_sources(STMicroelectronics_stm32h7pxx_dfp_2_0_0 INTERFACE "$<$<AND:${STMicroelectronics.stm32h7pxx_dfp.2.0.0_STM32H7P},${STMicroelectronics.stm32h7pxx_dfp.2.0.0_STM32H7P4}>:${CMAKE_CURRENT_LIST_DIR}/Source/startup_stm32h7p4xx.c>")
  endif()
  if(EXISTS ${CMSIS_RTE_FOLDER}/Device/${CMSIS_Dname}/stm32h7p4xx_sram.ld)
    target_link_options(STMicroelectronics_stm32h7pxx_dfp_2_0_0 INTERFACE "$<$<AND:${STMicroelectronics.stm32h7pxx_dfp.2.0.0_STM32H7P},${STMicroelectronics.stm32h7pxx_dfp.2.0.0_STM32H7P4xx_GCC}>:-T${CMSIS_RTE_FOLDER}/Device/${CMSIS_Dname}/stm32h7p4xx_sram.ld>")
  else()
    target_link_options(STMicroelectronics_stm32h7pxx_dfp_2_0_0 INTERFACE "$<$<AND:${STMicroelectronics.stm32h7pxx_dfp.2.0.0_STM32H7P},${STMicroelectronics.stm32h7pxx_dfp.2.0.0_STM32H7P4xx_GCC}>:-T${CMAKE_CURRENT_LIST_DIR}/Source/Templates/gcc/linker/stm32h7p4xx_sram.ld>")
  endif()
  if(EXISTS ${CMSIS_RTE_FOLDER}/Device/${CMSIS_Dname}/startup_stm32h7p5xx.c)
    target_sources(STMicroelectronics_stm32h7pxx_dfp_2_0_0 INTERFACE "$<$<AND:${STMicroelectronics.stm32h7pxx_dfp.2.0.0_STM32H7P},${STMicroelectronics.stm32h7pxx_dfp.2.0.0_STM32H7P5}>:${CMSIS_RTE_FOLDER}/Device/${CMSIS_Dname}/startup_stm32h7p5xx.c>")
  else()
    target_sources(STMicroelectronics_stm32h7pxx_dfp_2_0_0 INTERFACE "$<$<AND:${STMicroelectronics.stm32h7pxx_dfp.2.0.0_STM32H7P},${STMicroelectronics.stm32h7pxx_dfp.2.0.0_STM32H7P5}>:${CMAKE_CURRENT_LIST_DIR}/Source/startup_stm32h7p5xx.c>")
  endif()
  if(EXISTS ${CMSIS_RTE_FOLDER}/Device/${CMSIS_Dname}/stm32h7p5xx_sram.ld)
    target_link_options(STMicroelectronics_stm32h7pxx_dfp_2_0_0 INTERFACE "$<$<AND:${STMicroelectronics.stm32h7pxx_dfp.2.0.0_STM32H7P},${STMicroelectronics.stm32h7pxx_dfp.2.0.0_STM32H7P5xx_GCC}>:-T${CMSIS_RTE_FOLDER}/Device/${CMSIS_Dname}/stm32h7p5xx_sram.ld>")
  else()
    target_link_options(STMicroelectronics_stm32h7pxx_dfp_2_0_0 INTERFACE "$<$<AND:${STMicroelectronics.stm32h7pxx_dfp.2.0.0_STM32H7P},${STMicroelectronics.stm32h7pxx_dfp.2.0.0_STM32H7P5xx_GCC}>:-T${CMAKE_CURRENT_LIST_DIR}/Source/Templates/gcc/linker/stm32h7p5xx_sram.ld>")
  endif()
endif()

