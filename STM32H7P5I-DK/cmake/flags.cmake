# file-format: 1.0.0
if(CMAKE_BUILD_TYPE STREQUAL "debug_GCC_STM32H7P5I-DK")
  set_target_properties(${CMAKE_PROJECT_NAME} PROPERTIES SUFFIX ".elf")
  target_compile_options(${CMAKE_PROJECT_NAME} PUBLIC ${CPU_FLAGS})
  target_compile_options(${CMAKE_PROJECT_NAME} PUBLIC "SHELL:-g3 -O0 -fdata-sections -ffunction-sections -std=gnu11 -Wall -fstack-usage --specs=nano.specs --specs=nosys.specs -Werror=implicit-function-declaration ${CC_SECURE}")
  target_include_directories(${CMAKE_PROJECT_NAME} PUBLIC . generated/hal generated/middleware generated/parts generated/utilities user_modifiable/_debug_GCC_STM32H7P5I-DK ../arch/cmsis/CMSIS/Core/Include ../middleware/hsp_engine/common/core ../middleware/hsp_engine/common/core/legacy ../middleware/hsp_engine/common/modules ../middleware/hsp_engine/common/modules/direct_lib ../middleware/hsp_engine/common/modules/firmware ../middleware/hsp_engine/common/modules/firmware/crom_1_1_10/cram_1_7 ../middleware/hsp_engine/common/utilities ../middleware/hsp_engine/interfaces ../middleware/hsp_engine/interfaces/services ../part_drivers/led/gpio ../part_drivers/st7315 ../part_drivers/st7315/interfaces/spi ../stm32h7pxx_dfp/Include ../stm32h7pxx_drivers/hal ../stm32h7pxx_drivers/ll ../stm32h7pxx_drivers/timebases ../utilities/basic_stdio ../utilities/basic_stdio/interface_io)
  target_compile_definitions(${CMAKE_PROJECT_NAME} PUBLIC STM32H7P5xx _RTE_)
  target_link_options(${CMAKE_PROJECT_NAME} PUBLIC -Wl,-Map=././STM32H7P-GettingStarted-AED.map -Wl,--gc-sections -Wl,--start-group -lc -lm -Wl,--end-group -static --specs=nano.specs --specs=nosys.specs ${CC_SECURE})
  target_link_options(${CMAKE_PROJECT_NAME} PUBLIC ${CPU_FLAGS})
endif()

# Clean .map and .elf file
set_property(DIRECTORY APPEND PROPERTY ADDITIONAL_CLEAN_FILES "${CMAKE_SOURCE_DIR}/build/${CMAKE_BUILD_TYPE}/${CMAKE_PROJECT_NAME}.map")
set_property(DIRECTORY APPEND PROPERTY ADDITIONAL_CLEAN_FILES "${CMAKE_SOURCE_DIR}/build/${CMAKE_BUILD_TYPE}/${CMAKE_PROJECT_NAME}.elf")