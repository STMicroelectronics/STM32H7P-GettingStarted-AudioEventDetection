# origin-pack: generated_STMicroelectronics::st7315_part_drivers@0.0.1
# file-format: 1.0.0
project(generated_STMicroelectronics_st7315_part_drivers_0_0_1)
cmake_minimum_required(VERSION 3.30)
add_library(generated_STMicroelectronics_st7315_part_drivers_0_0_1 INTERFACE)

# List of all CMSIS properties that influence conditions for this package


# Device specific defined symbols








# Enable all components in this package
if(CMSIS_ENTIRE_generated_STMicroelectronics_st7315_part_drivers_0_0_1)
  list(APPEND CMSIS_COMPONENTS_LIST "Cvendor:STMicroelectronics#Cclass:Board Part#Cgroup:STM32CubeMX2 Config#Csub:ST7315#Cversion:1.0.0#generated:true")
endif()

# All conditions used by this package

# condition: generated_STMicroelectronics.st7315_part_drivers.0.0.1:ST7315 CFG Condition
# description: STMicroelectronics configuration for ST7315 part driver
set(generated_STMicroelectronics.st7315_part_drivers.0.0.1_ST7315_CFG_Condition "$<AND:$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Board Part#.*Cgroup:OLED#.*Csub:ST7315 Core(#.*|$)>,>>,$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Board Part#.*Cgroup:OLED#.*Csub:ST7315 IO#.*Cvariant:SPI Polling(#.*|$)>,>>>")
message(DEBUG "CMSIS condition generated_STMicroelectronics.st7315_part_drivers.0.0.1_ST7315_CFG_Condition enabled")


# condition: generated_STMicroelectronics.st7315_part_drivers.0.0.1:ST7315 Core Condition
# description: STMicroelectronics ST7315 Core Driver
set(generated_STMicroelectronics.st7315_part_drivers.0.0.1_ST7315_Core_Condition "$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Board Part#.*Cgroup:OLED#.*Csub:ST7315 IO(#.*|$)>,>>")
message(DEBUG "CMSIS condition generated_STMicroelectronics.st7315_part_drivers.0.0.1_ST7315_Core_Condition enabled")


# condition: generated_STMicroelectronics.st7315_part_drivers.0.0.1:ST7315 Custom IO Condition
# description: STMicroelectronics custom io configuration for ST7315 part driver
set(generated_STMicroelectronics.st7315_part_drivers.0.0.1_ST7315_Custom_IO_Condition "1")
message(DEBUG "CMSIS condition generated_STMicroelectronics.st7315_part_drivers.0.0.1_ST7315_Custom_IO_Condition enabled")


# condition: generated_STMicroelectronics.st7315_part_drivers.0.0.1:ST7315 IO SPI Polling Condition
# description: STMicroelectronics ST7315 IO SPI Polling Driver
set(generated_STMicroelectronics.st7315_part_drivers.0.0.1_ST7315_IO_SPI_Polling_Condition "$<NOT:$<STREQUAL:$<FILTER:${CMSIS_COMPONENTS_LIST},INCLUDE,.*Cclass:Device#.*Cgroup:STM32 HAL#.*Csub:SPI(#.*|$)>,>>")
message(DEBUG "CMSIS condition generated_STMicroelectronics.st7315_part_drivers.0.0.1_ST7315_IO_SPI_Polling_Condition enabled")

# Files and components in this package
if("Cvendor:STMicroelectronics#Cclass:Board Part#Cgroup:STM32CubeMX2 Config#Csub:ST7315#Cversion:1.0.0#generated:true" IN_LIST CMSIS_COMPONENTS_LIST)  # TO BE DEFINED
  message(DEBUG "Using component generated_Board_Part_STM32CubeMX2_Config_ST7315_1_0_0")
  target_compile_definitions(generated_STMicroelectronics_st7315_part_drivers_0_0_1 INTERFACE "$<${generated_STMicroelectronics.st7315_part_drivers.0.0.1_ST7315_CFG_Condition}:-DCMSIS_USE_generated_Board_Part_STM32CubeMX2_Config_ST7315_1_0_0=1>")
  target_include_directories(generated_STMicroelectronics_st7315_part_drivers_0_0_1 INTERFACE "$<${generated_STMicroelectronics.st7315_part_drivers.0.0.1_ST7315_CFG_Condition}:${CMAKE_CURRENT_LIST_DIR}/.>")
  target_sources(generated_STMicroelectronics_st7315_part_drivers_0_0_1 INTERFACE "$<${generated_STMicroelectronics.st7315_part_drivers.0.0.1_ST7315_CFG_Condition}:${CMAKE_CURRENT_LIST_DIR}/mx_st7315.c>")
endif()

