# origin-pack: STMicroelectronics::levelx@0.7.0
# created-by: conversion-manager@0.0.46
project(STMicroelectronics_levelx_0_7_0)
cmake_minimum_required(VERSION 3.20)
add_library(STMicroelectronics_levelx_0_7_0 INTERFACE)

# List of all CMSIS properties that influence conditions for this package
if(NOT DEFINED CMSIS_Dname)
  set(CMSIS_Dname "CMSIS_Dname not set")
  message(DEBUG "CMSIS_Dname is not set to any value")
endif()

if(NOT DEFINED CMSIS_Dvendor)
  set(CMSIS_Dvendor "CMSIS_Dvendor not set")
  message(DEBUG "CMSIS_Dvendor is not set to any value")
endif()


# Device specific defined symbols


# Include RTE_Components.h globally if needed


# Include Pre_Include_Global.h globally if needed


# Enable all components in this package
if(CMSIS_ENTIRE_STMicroelectronics_levelx_0_7_0)
  set(CMSIS_USE_File_System_LevelX_NOR_Flash_Core_6_4_1 true)
  set(CMSIS_USE_File_System_LevelX_NAND_Flash_Core_6_4_1 true)
  set(CMSIS_USE_File_System_LevelX_nor_flash_simulator_itf_6_4_1 true)
  set(CMSIS_USE_File_System_LevelX_mx25lm51245g_nor_polling_itf_6_4_1 true)
  set(CMSIS_USE_File_System_LevelX_mx25lm51245g_nor_dma_no_os_itf_6_4_1 true)
  set(CMSIS_USE_File_System_LevelX_mx25lm51245g_nor_dma_os_itf_6_4_1 true)
  set(CMSIS_USE_File_System_LevelX_mx66lm1g45g_nor_polling_itf_6_4_1 true)
  set(CMSIS_USE_File_System_LevelX_mx66lm1g45g_nor_dma_no_os_itf_6_4_1 true)
  set(CMSIS_USE_File_System_LevelX_mx66lm1g45g_nor_dma_os_itf_6_4_1 true)
  set(CMSIS_USE_File_System_LevelX_w25q128j_nor_polling_itf_6_4_1 true)
  set(CMSIS_USE_File_System_LevelX_w25q128j_nor_dma_no_os_itf_6_4_1 true)
  set(CMSIS_USE_File_System_LevelX_w25q128j_nor_dma_os_itf_6_4_1 true)
  set(CMSIS_USE_File_System_LevelX_w25n01gvxx_nand_polling_itf_6_4_1 true)
  set(CMSIS_USE_File_System_LevelX_w25n01gvxx_nand_dma_no_os_itf_6_4_1 true)
  set(CMSIS_USE_File_System_LevelX_w25n01gvxx_nand_dma_os_itf_6_4_1 true)
  set(CMSIS_USE_File_System_LevelX_mx66uw1g45g_nor_polling_itf_6_4_1 true)
endif()

# All conditions used by this package

# condition: STMicroelectronics.levelx.0.7.0:LX Core condition
# description: levelx core dependency
set(STMicroelectronics.levelx.0.7.0:LX_Core_condition true)
message(DEBUG "CMSIS condition STMicroelectronics.levelx.0.7.0:LX_Core_condition enabled")


# condition: STMicroelectronics.levelx.0.7.0
# description: 
if((CMSIS_Dname MATCHES "STM32.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13"))
  set(STMicroelectronics.levelx.0.7.0 true)
  message(DEBUG "CMSIS condition STMicroelectronics.levelx.0.7.0 enabled")
endif()


# condition: STMicroelectronics.levelx.0.7.0:USE W25N01GVXX POLLING
# description: LX W25N01GVXX POLLING interface dependency
set(STMicroelectronics.levelx.0.7.0:USE_W25N01GVXX_POLLING true)
message(DEBUG "CMSIS condition STMicroelectronics.levelx.0.7.0:USE_W25N01GVXX_POLLING enabled")


# condition: STMicroelectronics.levelx.0.7.0:LX NOR Flash Core condition
# description: LX NOR Flash Core dependency
set(STMicroelectronics.levelx.0.7.0:LX_NOR_Flash_Core_condition true)
message(DEBUG "CMSIS condition STMicroelectronics.levelx.0.7.0:LX_NOR_Flash_Core_condition enabled")


# condition: STMicroelectronics.levelx.0.7.0:LX DMA OS condition
# description: RTOS dependency
set(STMicroelectronics.levelx.0.7.0:LX_DMA_OS_condition true)
message(DEBUG "CMSIS condition STMicroelectronics.levelx.0.7.0:LX_DMA_OS_condition enabled")


# condition: STMicroelectronics.levelx.0.7.0:Use NAND Flash Core
# description: LevelX NAND Flash Core dependency
set(STMicroelectronics.levelx.0.7.0:Use_NAND_Flash_Core true)
message(DEBUG "CMSIS condition STMicroelectronics.levelx.0.7.0:Use_NAND_Flash_Core enabled")


# condition: STMicroelectronics.levelx.0.7.0:LX DMA NO OS condition
# description: NO RTOS dependency
set(STMicroelectronics.levelx.0.7.0:LX_DMA_NO_OS_condition true)
message(DEBUG "CMSIS condition STMicroelectronics.levelx.0.7.0:LX_DMA_NO_OS_condition enabled")


# condition: STMicroelectronics.levelx.0.7.0:USE MX66UW1G45G POLLING
# description: LX MX66UW1G45G POLLING interface dependency
set(STMicroelectronics.levelx.0.7.0:USE_MX66UW1G45G_POLLING true)
message(DEBUG "CMSIS condition STMicroelectronics.levelx.0.7.0:USE_MX66UW1G45G_POLLING enabled")


# condition: STMicroelectronics.levelx.0.7.0:Use NOR Flash Core
# description: LevelX NOR Flash Core dependency
set(STMicroelectronics.levelx.0.7.0:Use_NOR_Flash_Core true)
message(DEBUG "CMSIS condition STMicroelectronics.levelx.0.7.0:Use_NOR_Flash_Core enabled")


# condition: STMicroelectronics.levelx.0.7.0:LX W25Q128J condition
# description: LX W25Q128J interface dependency
set(STMicroelectronics.levelx.0.7.0:LX_W25Q128J_condition true)
message(DEBUG "CMSIS condition STMicroelectronics.levelx.0.7.0:LX_W25Q128J_condition enabled")


# condition: STMicroelectronics.levelx.0.7.0:LX MX66LM1G45G condition
# description: LX MX66LM1G45G interface dependency
set(STMicroelectronics.levelx.0.7.0:LX_MX66LM1G45G_condition true)
message(DEBUG "CMSIS condition STMicroelectronics.levelx.0.7.0:LX_MX66LM1G45G_condition enabled")


# condition: STMicroelectronics.levelx.0.7.0:USE W25N01GVXX DMA OS
# description: LX W25N01GVXX DMA OS interface dependency
set(STMicroelectronics.levelx.0.7.0:USE_W25N01GVXX_DMA_OS true)
message(DEBUG "CMSIS condition STMicroelectronics.levelx.0.7.0:USE_W25N01GVXX_DMA_OS enabled")


# condition: STMicroelectronics.levelx.0.7.0:USE W25N01GVXX DMA NO OS
# description: LX W25N01GVXX NO OS interface dependency
set(STMicroelectronics.levelx.0.7.0:USE_W25N01GVXX_DMA_NO_OS true)
message(DEBUG "CMSIS condition STMicroelectronics.levelx.0.7.0:USE_W25N01GVXX_DMA_NO_OS enabled")


# condition: STMicroelectronics.levelx.0.7.0:LX MX25LM51245G condition
# description: LX MX25LM51245G interface dependency
set(STMicroelectronics.levelx.0.7.0:LX_MX25LM51245G_condition true)
message(DEBUG "CMSIS condition STMicroelectronics.levelx.0.7.0:LX_MX25LM51245G_condition enabled")

# Files and components in this package
if(CMSIS_USE_File_System_LevelX_NOR_Flash_Core_6_4_1)  # Component to support NOR flash
  message(DEBUG "Using component File_System_LevelX_NOR_Flash_Core_6_4_1")
  if(STMicroelectronics.levelx.0.7.0:Use_NOR_Flash_Core)
    target_compile_definitions(STMicroelectronics_levelx_0_7_0 INTERFACE -DCMSIS_USE_File_System_LevelX_NOR_Flash_Core_6_4_1=1)
    target_sources(STMicroelectronics_levelx_0_7_0 INTERFACE common/src/lx_nor_flash_block_reclaim.c)
    target_sources(STMicroelectronics_levelx_0_7_0 INTERFACE common/src/lx_nor_flash_close.c)
    target_sources(STMicroelectronics_levelx_0_7_0 INTERFACE common/src/lx_nor_flash_defragment.c)
    target_sources(STMicroelectronics_levelx_0_7_0 INTERFACE common/src/lx_nor_flash_driver_block_erase.c)
    target_sources(STMicroelectronics_levelx_0_7_0 INTERFACE common/src/lx_nor_flash_driver_read.c)
    target_sources(STMicroelectronics_levelx_0_7_0 INTERFACE common/src/lx_nor_flash_driver_write.c)
    target_sources(STMicroelectronics_levelx_0_7_0 INTERFACE common/src/lx_nor_flash_extended_cache_enable.c)
    target_sources(STMicroelectronics_levelx_0_7_0 INTERFACE common/src/lx_nor_flash_initialize.c)
    target_sources(STMicroelectronics_levelx_0_7_0 INTERFACE common/src/lx_nor_flash_logical_sector_find.c)
    target_sources(STMicroelectronics_levelx_0_7_0 INTERFACE common/src/lx_nor_flash_next_block_to_erase_find.c)
    target_sources(STMicroelectronics_levelx_0_7_0 INTERFACE common/src/lx_nor_flash_open.c)
    target_sources(STMicroelectronics_levelx_0_7_0 INTERFACE common/src/lx_nor_flash_partial_defragment.c)
    target_sources(STMicroelectronics_levelx_0_7_0 INTERFACE common/src/lx_nor_flash_physical_sector_allocate.c)
    target_sources(STMicroelectronics_levelx_0_7_0 INTERFACE common/src/lx_nor_flash_sector_mapping_cache_invalidate.c)
    target_sources(STMicroelectronics_levelx_0_7_0 INTERFACE common/src/lx_nor_flash_sector_read.c)
    target_sources(STMicroelectronics_levelx_0_7_0 INTERFACE common/src/lx_nor_flash_sector_release.c)
    target_sources(STMicroelectronics_levelx_0_7_0 INTERFACE common/src/lx_nor_flash_sector_write.c)
    target_sources(STMicroelectronics_levelx_0_7_0 INTERFACE common/src/lx_nor_flash_system_error.c)
    target_include_directories(STMicroelectronics_levelx_0_7_0 INTERFACE common/inc)
    if(STMicroelectronics.levelx.0.7.0:LX_DMA_OS_condition)
      target_include_directories(STMicroelectronics_levelx_0_7_0 INTERFACE ports/freertos/inc/)
    endif()
    if(STMicroelectronics.levelx.0.7.0:LX_DMA_NO_OS_condition)
      target_include_directories(STMicroelectronics_levelx_0_7_0 INTERFACE ports/generic/inc/)
    endif()
  endif()
endif()

if(CMSIS_USE_File_System_LevelX_NAND_Flash_Core_6_4_1)  # Component to support NAND flash
  message(DEBUG "Using component File_System_LevelX_NAND_Flash_Core_6_4_1")
  if(STMicroelectronics.levelx.0.7.0:Use_NAND_Flash_Core)
    target_compile_definitions(STMicroelectronics_levelx_0_7_0 INTERFACE -DCMSIS_USE_File_System_LevelX_NAND_Flash_Core_6_4_1=1)
    target_sources(STMicroelectronics_levelx_0_7_0 INTERFACE common/src/lx_nand_flash_256byte_ecc_check.c)
    target_sources(STMicroelectronics_levelx_0_7_0 INTERFACE common/src/lx_nand_flash_256byte_ecc_compute.c)
    target_sources(STMicroelectronics_levelx_0_7_0 INTERFACE common/src/lx_nand_flash_block_allocate.c)
    target_sources(STMicroelectronics_levelx_0_7_0 INTERFACE common/src/lx_nand_flash_block_data_move.c)
    target_sources(STMicroelectronics_levelx_0_7_0 INTERFACE common/src/lx_nand_flash_block_find.c)
    target_sources(STMicroelectronics_levelx_0_7_0 INTERFACE common/src/lx_nand_flash_block_mapping_set.c)
    target_sources(STMicroelectronics_levelx_0_7_0 INTERFACE common/src/lx_nand_flash_block_status_set.c)
    target_sources(STMicroelectronics_levelx_0_7_0 INTERFACE common/src/lx_nand_flash_close.c)
    target_sources(STMicroelectronics_levelx_0_7_0 INTERFACE common/src/lx_nand_flash_data_page_copy.c)
    target_sources(STMicroelectronics_levelx_0_7_0 INTERFACE common/src/lx_nand_flash_defragment.c)
    target_sources(STMicroelectronics_levelx_0_7_0 INTERFACE common/src/lx_nand_flash_driver_block_erase.c)
    target_sources(STMicroelectronics_levelx_0_7_0 INTERFACE common/src/lx_nand_flash_driver_block_erased_verify.c)
    target_sources(STMicroelectronics_levelx_0_7_0 INTERFACE common/src/lx_nand_flash_driver_block_status_get.c)
    target_sources(STMicroelectronics_levelx_0_7_0 INTERFACE common/src/lx_nand_flash_driver_block_status_set.c)
    target_sources(STMicroelectronics_levelx_0_7_0 INTERFACE common/src/lx_nand_flash_driver_page_erased_verify.c)
    target_sources(STMicroelectronics_levelx_0_7_0 INTERFACE common/src/lx_nand_flash_erase_count_set.c)
    target_sources(STMicroelectronics_levelx_0_7_0 INTERFACE common/src/lx_nand_flash_extended_cache_enable.c)
    target_sources(STMicroelectronics_levelx_0_7_0 INTERFACE common/src/lx_nand_flash_format.c)
    target_sources(STMicroelectronics_levelx_0_7_0 INTERFACE common/src/lx_nand_flash_free_block_list_add.c)
    target_sources(STMicroelectronics_levelx_0_7_0 INTERFACE common/src/lx_nand_flash_initialize.c)
    target_sources(STMicroelectronics_levelx_0_7_0 INTERFACE common/src/lx_nand_flash_mapped_block_list_add.c)
    target_sources(STMicroelectronics_levelx_0_7_0 INTERFACE common/src/lx_nand_flash_mapped_block_list_get.c)
    target_sources(STMicroelectronics_levelx_0_7_0 INTERFACE common/src/lx_nand_flash_mapped_block_list_remove.c)
    target_sources(STMicroelectronics_levelx_0_7_0 INTERFACE common/src/lx_nand_flash_memory_initialize.c)
    target_sources(STMicroelectronics_levelx_0_7_0 INTERFACE common/src/lx_nand_flash_metadata_allocate.c)
    target_sources(STMicroelectronics_levelx_0_7_0 INTERFACE common/src/lx_nand_flash_metadata_build.c)
    target_sources(STMicroelectronics_levelx_0_7_0 INTERFACE common/src/lx_nand_flash_metadata_write.c)
    target_sources(STMicroelectronics_levelx_0_7_0 INTERFACE common/src/lx_nand_flash_open.c)
    target_sources(STMicroelectronics_levelx_0_7_0 INTERFACE common/src/lx_nand_flash_page_ecc_check.c)
    target_sources(STMicroelectronics_levelx_0_7_0 INTERFACE common/src/lx_nand_flash_page_ecc_compute.c)
    target_sources(STMicroelectronics_levelx_0_7_0 INTERFACE common/src/lx_nand_flash_partial_defragment.c)
    target_sources(STMicroelectronics_levelx_0_7_0 INTERFACE common/src/lx_nand_flash_sector_read.c)
    target_sources(STMicroelectronics_levelx_0_7_0 INTERFACE common/src/lx_nand_flash_sector_release.c)
    target_sources(STMicroelectronics_levelx_0_7_0 INTERFACE common/src/lx_nand_flash_sector_write.c)
    target_sources(STMicroelectronics_levelx_0_7_0 INTERFACE common/src/lx_nand_flash_sectors_read.c)
    target_sources(STMicroelectronics_levelx_0_7_0 INTERFACE common/src/lx_nand_flash_sectors_release.c)
    target_sources(STMicroelectronics_levelx_0_7_0 INTERFACE common/src/lx_nand_flash_sectors_write.c)
    target_sources(STMicroelectronics_levelx_0_7_0 INTERFACE common/src/lx_nand_flash_system_error.c)
    target_include_directories(STMicroelectronics_levelx_0_7_0 INTERFACE common/inc)
    if(STMicroelectronics.levelx.0.7.0:LX_DMA_OS_condition)
      target_include_directories(STMicroelectronics_levelx_0_7_0 INTERFACE ports/freertos/inc/)
    endif()
    if(STMicroelectronics.levelx.0.7.0:LX_DMA_NO_OS_condition)
      target_include_directories(STMicroelectronics_levelx_0_7_0 INTERFACE ports/generic/inc/)
    endif()
  endif()
endif()

if(CMSIS_USE_File_System_LevelX_nor_flash_simulator_itf_6_4_1)  # Simulator interface for NOR flash 
  message(DEBUG "Using component File_System_LevelX_nor_flash_simulator_itf_6_4_1")
  if(STMicroelectronics.levelx.0.7.0:LX_NOR_Flash_Core_condition)
    target_compile_definitions(STMicroelectronics_levelx_0_7_0 INTERFACE -DCMSIS_USE_File_System_LevelX_nor_flash_simulator_itf_6_4_1=1)
    target_sources(STMicroelectronics_levelx_0_7_0 INTERFACE interfaces/nor/simulator/stm32_lx_nor_flash_simulator_driver.c)
    target_include_directories(STMicroelectronics_levelx_0_7_0 INTERFACE interfaces/nor/simulator)
    target_include_directories(STMicroelectronics_levelx_0_7_0 INTERFACE interfaces/nor/)
    target_include_directories(STMicroelectronics_levelx_0_7_0 INTERFACE interfaces/nor/simulator/)
  endif()
endif()

if(CMSIS_USE_File_System_LevelX_mx25lm51245g_nor_polling_itf_6_4_1)  # Polling interface for NOR flash mx25lm51245g
  message(DEBUG "Using component File_System_LevelX_mx25lm51245g_nor_polling_itf_6_4_1")
  if(STMicroelectronics.levelx.0.7.0:LX_MX25LM51245G_condition)
    target_compile_definitions(STMicroelectronics_levelx_0_7_0 INTERFACE -DCMSIS_USE_File_System_LevelX_mx25lm51245g_nor_polling_itf_6_4_1=1)
    target_sources(STMicroelectronics_levelx_0_7_0 INTERFACE interfaces/nor/mx25lm51245g/stm32_lx_mx25lm51245g_nor_flash_polling_driver.c)
    target_include_directories(STMicroelectronics_levelx_0_7_0 INTERFACE interfaces/nor/mx25lm51245g)
    target_include_directories(STMicroelectronics_levelx_0_7_0 INTERFACE interfaces/nor/)
    target_include_directories(STMicroelectronics_levelx_0_7_0 INTERFACE interfaces/nor/mx25lm51245g/)
  endif()
endif()

if(CMSIS_USE_File_System_LevelX_mx25lm51245g_nor_dma_no_os_itf_6_4_1)  # DMA no os interface for NOR flash mx25lm51245g
  message(DEBUG "Using component File_System_LevelX_mx25lm51245g_nor_dma_no_os_itf_6_4_1")
  if(STMicroelectronics.levelx.0.7.0:LX_MX25LM51245G_condition)
    target_compile_definitions(STMicroelectronics_levelx_0_7_0 INTERFACE -DCMSIS_USE_File_System_LevelX_mx25lm51245g_nor_dma_no_os_itf_6_4_1=1)
    target_sources(STMicroelectronics_levelx_0_7_0 INTERFACE interfaces/nor/mx25lm51245g/stm32_lx_mx25lm51245g_nor_flash_dma_no_os_driver.c)
    target_include_directories(STMicroelectronics_levelx_0_7_0 INTERFACE interfaces/nor/mx25lm51245g)
    target_include_directories(STMicroelectronics_levelx_0_7_0 INTERFACE interfaces/nor/)
    target_include_directories(STMicroelectronics_levelx_0_7_0 INTERFACE interfaces/nor/mx25lm51245g/)
  endif()
endif()

if(CMSIS_USE_File_System_LevelX_mx25lm51245g_nor_dma_os_itf_6_4_1)  # DMA os interface for NOR flash mx25lm51245g
  message(DEBUG "Using component File_System_LevelX_mx25lm51245g_nor_dma_os_itf_6_4_1")
  if(STMicroelectronics.levelx.0.7.0:LX_MX25LM51245G_condition)
    target_compile_definitions(STMicroelectronics_levelx_0_7_0 INTERFACE -DCMSIS_USE_File_System_LevelX_mx25lm51245g_nor_dma_os_itf_6_4_1=1)
    target_sources(STMicroelectronics_levelx_0_7_0 INTERFACE interfaces/nor/mx25lm51245g/stm32_lx_mx25lm51245g_nor_flash_dma_os_driver.c)
    target_include_directories(STMicroelectronics_levelx_0_7_0 INTERFACE interfaces/nor/mx25lm51245g)
    target_include_directories(STMicroelectronics_levelx_0_7_0 INTERFACE interfaces/nor/)
    target_include_directories(STMicroelectronics_levelx_0_7_0 INTERFACE interfaces/nor/mx25lm51245g/)
  endif()
endif()

if(CMSIS_USE_File_System_LevelX_mx66lm1g45g_nor_polling_itf_6_4_1)  # Polling interface for NOR flash mx66lm1g45g
  message(DEBUG "Using component File_System_LevelX_mx66lm1g45g_nor_polling_itf_6_4_1")
  if(STMicroelectronics.levelx.0.7.0:LX_MX66LM1G45G_condition)
    target_compile_definitions(STMicroelectronics_levelx_0_7_0 INTERFACE -DCMSIS_USE_File_System_LevelX_mx66lm1g45g_nor_polling_itf_6_4_1=1)
    target_sources(STMicroelectronics_levelx_0_7_0 INTERFACE interfaces/nor/mx66lm1g45g/stm32_lx_mx66lm1g45g_nor_flash_polling_driver.c)
    target_include_directories(STMicroelectronics_levelx_0_7_0 INTERFACE interfaces/nor/mx66lm1g45g)
    target_include_directories(STMicroelectronics_levelx_0_7_0 INTERFACE interfaces/nor/)
    target_include_directories(STMicroelectronics_levelx_0_7_0 INTERFACE interfaces/nor/mx66lm1g45g/)
  endif()
endif()

if(CMSIS_USE_File_System_LevelX_mx66lm1g45g_nor_dma_no_os_itf_6_4_1)  # DMA no os interface for NOR flash mx66lm1g45g
  message(DEBUG "Using component File_System_LevelX_mx66lm1g45g_nor_dma_no_os_itf_6_4_1")
  if(STMicroelectronics.levelx.0.7.0:LX_MX66LM1G45G_condition)
    target_compile_definitions(STMicroelectronics_levelx_0_7_0 INTERFACE -DCMSIS_USE_File_System_LevelX_mx66lm1g45g_nor_dma_no_os_itf_6_4_1=1)
    target_sources(STMicroelectronics_levelx_0_7_0 INTERFACE interfaces/nor/mx66lm1g45g/stm32_lx_mx66lm1g45g_nor_flash_dma_no_os_driver.c)
    target_include_directories(STMicroelectronics_levelx_0_7_0 INTERFACE interfaces/nor/mx66lm1g45g)
    target_include_directories(STMicroelectronics_levelx_0_7_0 INTERFACE interfaces/nor/)
    target_include_directories(STMicroelectronics_levelx_0_7_0 INTERFACE interfaces/nor/mx66lm1g45g/)
  endif()
endif()

if(CMSIS_USE_File_System_LevelX_mx66lm1g45g_nor_dma_os_itf_6_4_1)  # DMA os interface for NOR flash mx66lm1g45g
  message(DEBUG "Using component File_System_LevelX_mx66lm1g45g_nor_dma_os_itf_6_4_1")
  if(STMicroelectronics.levelx.0.7.0:LX_MX66LM1G45G_condition)
    target_compile_definitions(STMicroelectronics_levelx_0_7_0 INTERFACE -DCMSIS_USE_File_System_LevelX_mx66lm1g45g_nor_dma_os_itf_6_4_1=1)
    target_sources(STMicroelectronics_levelx_0_7_0 INTERFACE interfaces/nor/mx66lm1g45g/stm32_lx_mx66lm1g45g_nor_flash_dma_os_driver.c)
    target_include_directories(STMicroelectronics_levelx_0_7_0 INTERFACE interfaces/nor/mx66lm1g45g)
    target_include_directories(STMicroelectronics_levelx_0_7_0 INTERFACE interfaces/nor/)
    target_include_directories(STMicroelectronics_levelx_0_7_0 INTERFACE interfaces/nor/mx66lm1g45g/)
  endif()
endif()

if(CMSIS_USE_File_System_LevelX_w25q128j_nor_polling_itf_6_4_1)  # Polling interface for NOR flash w25q128j
  message(DEBUG "Using component File_System_LevelX_w25q128j_nor_polling_itf_6_4_1")
  if(STMicroelectronics.levelx.0.7.0:LX_W25Q128J_condition)
    target_compile_definitions(STMicroelectronics_levelx_0_7_0 INTERFACE -DCMSIS_USE_File_System_LevelX_w25q128j_nor_polling_itf_6_4_1=1)
    target_sources(STMicroelectronics_levelx_0_7_0 INTERFACE interfaces/nor/w25q128j/stm32_lx_w25q128j_nor_flash_polling_driver.c)
    target_include_directories(STMicroelectronics_levelx_0_7_0 INTERFACE interfaces/nor/w25q128j)
    target_include_directories(STMicroelectronics_levelx_0_7_0 INTERFACE interfaces/nor/)
    target_include_directories(STMicroelectronics_levelx_0_7_0 INTERFACE interfaces/nor/w25q128j/)
  endif()
endif()

if(CMSIS_USE_File_System_LevelX_w25q128j_nor_dma_no_os_itf_6_4_1)  # DMA no os interface for NOR flash w25q128j
  message(DEBUG "Using component File_System_LevelX_w25q128j_nor_dma_no_os_itf_6_4_1")
  if(STMicroelectronics.levelx.0.7.0:LX_W25Q128J_condition)
    target_compile_definitions(STMicroelectronics_levelx_0_7_0 INTERFACE -DCMSIS_USE_File_System_LevelX_w25q128j_nor_dma_no_os_itf_6_4_1=1)
    target_sources(STMicroelectronics_levelx_0_7_0 INTERFACE interfaces/nor/w25q128j/stm32_lx_w25q128j_nor_flash_dma_no_os_driver.c)
    target_include_directories(STMicroelectronics_levelx_0_7_0 INTERFACE interfaces/nor/w25q128j)
    target_include_directories(STMicroelectronics_levelx_0_7_0 INTERFACE interfaces/nor/)
    target_include_directories(STMicroelectronics_levelx_0_7_0 INTERFACE interfaces/nor/w25q128j/)
  endif()
endif()

if(CMSIS_USE_File_System_LevelX_w25q128j_nor_dma_os_itf_6_4_1)  # DMA os interface for NOR flash w25q128j
  message(DEBUG "Using component File_System_LevelX_w25q128j_nor_dma_os_itf_6_4_1")
  if(STMicroelectronics.levelx.0.7.0:LX_W25Q128J_condition)
    target_compile_definitions(STMicroelectronics_levelx_0_7_0 INTERFACE -DCMSIS_USE_File_System_LevelX_w25q128j_nor_dma_os_itf_6_4_1=1)
    target_sources(STMicroelectronics_levelx_0_7_0 INTERFACE interfaces/nor/w25q128j/stm32_lx_w25q128j_nor_flash_dma_os_driver.c)
    target_include_directories(STMicroelectronics_levelx_0_7_0 INTERFACE interfaces/nor/w25q128j)
    target_include_directories(STMicroelectronics_levelx_0_7_0 INTERFACE interfaces/nor/)
    target_include_directories(STMicroelectronics_levelx_0_7_0 INTERFACE interfaces/nor/w25q128j/)
  endif()
endif()

if(CMSIS_USE_File_System_LevelX_w25n01gvxx_nand_polling_itf_6_4_1)  # Polling interface for NAND flash w25n01gvxx
  message(DEBUG "Using component File_System_LevelX_w25n01gvxx_nand_polling_itf_6_4_1")
  if(STMicroelectronics.levelx.0.7.0:USE_W25N01GVXX_POLLING)
    target_compile_definitions(STMicroelectronics_levelx_0_7_0 INTERFACE -DCMSIS_USE_File_System_LevelX_w25n01gvxx_nand_polling_itf_6_4_1=1)
    target_sources(STMicroelectronics_levelx_0_7_0 INTERFACE interfaces/nand/w25n01gvxx/stm32_lx_w25n01gvxx_nand_flash_polling_driver.c)
    target_include_directories(STMicroelectronics_levelx_0_7_0 INTERFACE interfaces/nand/w25n01gvxx)
    target_include_directories(STMicroelectronics_levelx_0_7_0 INTERFACE interfaces/nand/)
    target_include_directories(STMicroelectronics_levelx_0_7_0 INTERFACE interfaces/nand/w25n01gvxx/)
  endif()
endif()

if(CMSIS_USE_File_System_LevelX_w25n01gvxx_nand_dma_no_os_itf_6_4_1)  # DMA no os interface for NAND flash w25n01gvxx
  message(DEBUG "Using component File_System_LevelX_w25n01gvxx_nand_dma_no_os_itf_6_4_1")
  if(STMicroelectronics.levelx.0.7.0:USE_W25N01GVXX_DMA_NO_OS)
    target_compile_definitions(STMicroelectronics_levelx_0_7_0 INTERFACE -DCMSIS_USE_File_System_LevelX_w25n01gvxx_nand_dma_no_os_itf_6_4_1=1)
    target_sources(STMicroelectronics_levelx_0_7_0 INTERFACE interfaces/nand/w25n01gvxx/stm32_lx_w25n01gvxx_nand_flash_dma_no_os_driver.c)
    target_include_directories(STMicroelectronics_levelx_0_7_0 INTERFACE interfaces/nand/w25n01gvxx)
    target_include_directories(STMicroelectronics_levelx_0_7_0 INTERFACE interfaces/nand/)
    target_include_directories(STMicroelectronics_levelx_0_7_0 INTERFACE interfaces/nand/w25n01gvxx/)
  endif()
endif()

if(CMSIS_USE_File_System_LevelX_w25n01gvxx_nand_dma_os_itf_6_4_1)  # DMA os interface for NAND flash w25n01gvxx
  message(DEBUG "Using component File_System_LevelX_w25n01gvxx_nand_dma_os_itf_6_4_1")
  if(STMicroelectronics.levelx.0.7.0:USE_W25N01GVXX_DMA_OS)
    target_compile_definitions(STMicroelectronics_levelx_0_7_0 INTERFACE -DCMSIS_USE_File_System_LevelX_w25n01gvxx_nand_dma_os_itf_6_4_1=1)
    target_sources(STMicroelectronics_levelx_0_7_0 INTERFACE interfaces/nand/w25n01gvxx/stm32_lx_w25n01gvxx_nand_flash_dma_os_driver.c)
    target_include_directories(STMicroelectronics_levelx_0_7_0 INTERFACE interfaces/nand/w25n01gvxx)
    target_include_directories(STMicroelectronics_levelx_0_7_0 INTERFACE interfaces/nand/)
    target_include_directories(STMicroelectronics_levelx_0_7_0 INTERFACE interfaces/nand/w25n01gvxx/)
  endif()
endif()

if(CMSIS_USE_File_System_LevelX_mx66uw1g45g_nor_polling_itf_6_4_1)  # Polling interface for NOR flash mx66uw1g45g
  message(DEBUG "Using component File_System_LevelX_mx66uw1g45g_nor_polling_itf_6_4_1")
  if(STMicroelectronics.levelx.0.7.0:USE_MX66UW1G45G_POLLING)
    target_compile_definitions(STMicroelectronics_levelx_0_7_0 INTERFACE -DCMSIS_USE_File_System_LevelX_mx66uw1g45g_nor_polling_itf_6_4_1=1)
    target_sources(STMicroelectronics_levelx_0_7_0 INTERFACE interfaces/nor/mx66uw1g45g/stm32_lx_mx66uw1g45g_nor_flash_polling_driver.c)
    target_include_directories(STMicroelectronics_levelx_0_7_0 INTERFACE interfaces/nor/mx66uw1g45g)
    target_include_directories(STMicroelectronics_levelx_0_7_0 INTERFACE interfaces/nor/)
    target_include_directories(STMicroelectronics_levelx_0_7_0 INTERFACE interfaces/nor/mx66uw1g45g/)
  endif()
endif()

