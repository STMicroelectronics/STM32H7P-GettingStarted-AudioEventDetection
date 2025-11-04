/***************************************************************************
  * Copyright (c) 2024 Microsoft Corporation
  * Copyright (c) 2025 STMicroelectronics
  *
  * This program and the accompanying materials are made available under the
  * terms of the MIT License which is available at
  * https://opensource.org/licenses/MIT.
  *
  * SPDX-License-Identifier: MIT
  **************************************************************************/


/* Include necessary system files.  */
#include "stm32_lx_nor_flash_simulator_driver.h"

#ifndef LX_NOR_ENABLE_CONTROL_BLOCK_FOR_DRIVER_INTERFACE
#error "Make sure to define LX_NOR_ENABLE_CONTROL_BLOCK_FOR_DRIVER_INTERFACE in the lx_user.h"
#endif /* LX_NOR_ENABLE_CONTROL_BLOCK_FOR_DRIVER_INTERFACE */

static UINT lx_nor_flash_simulator_read(struct LX_NOR_FLASH_STRUCT *nor_flash, ULONG *flash_address, ULONG *destination,
                                        ULONG words);
static UINT lx_nor_flash_simulator_write(struct LX_NOR_FLASH_STRUCT *nor_flash, ULONG *flash_address, ULONG *source,
                                         ULONG words);

static UINT lx_nor_flash_simulator_block_erase(struct LX_NOR_FLASH_STRUCT *nor_flash, ULONG block, ULONG erase_count);
static UINT lx_nor_flash_simulator_block_erased_verify(struct LX_NOR_FLASH_STRUCT *nor_flash, ULONG block);

UINT lx_nor_flash_simulator_system_error(struct LX_NOR_FLASH_STRUCT *nor_flash, UINT error_code);

/**
  * @brief  initialize simulator memory.
  * @param  LX_NOR_FLASH * the levelx NOR flash main instance.
  * @retval LX_SUCCESS if simulator memory is ready, LX_ERROR otherwise
  */
UINT stm32_lx_nor_flash_simulator_initialize(LX_NOR_FLASH *nor_flash)
{
  STM32_LX_NOR_FLASH_DRIVER_CONTEXT *simulator_config  =
    (STM32_LX_NOR_FLASH_DRIVER_CONTEXT *) nor_flash->lx_nor_flash_info_ptr;

  /* Check if simulator_config is NULL to prevent a hard fault.  */
  if (simulator_config == NULL)
  {
    return LX_ERROR;
  }
  /* Setup the base address of the flash memory.  */
  nor_flash->lx_nor_flash_base_address                 = (ULONG *)simulator_config->nor_flash_start_address;

  /* Setup geometry of the flash.  */
  nor_flash->lx_nor_flash_total_blocks                 =
    simulator_config->nor_flash_size / simulator_config->nor_flash_block_size;
  nor_flash->lx_nor_flash_words_per_block              = simulator_config->nor_flash_block_size / sizeof(ULONG);

  /* Setup function pointers for the NOR flash services.  */
  nor_flash->lx_nor_flash_driver_read                  = lx_nor_flash_simulator_read;
  nor_flash->lx_nor_flash_driver_write                 = lx_nor_flash_simulator_write;
  nor_flash->lx_nor_flash_driver_block_erase           = lx_nor_flash_simulator_block_erase;
  nor_flash->lx_nor_flash_driver_block_erased_verify   = lx_nor_flash_simulator_block_erased_verify;
  nor_flash->lx_nor_flash_driver_system_error          = lx_nor_flash_simulator_system_error;

#ifndef LX_DIRECT_READ
  /* Setup local buffer for NOR flash operation. This buffer must be the sector size of the NOR flash memory.  */
  nor_flash->lx_nor_flash_sector_buffer                = simulator_config->nor_flash_read_buffer;

#endif /* LX_DIRECT_READ */

  /* Return success.  */
  return (LX_SUCCESS);
}

/**
  * @brief  read data from flash memory address into a destination buffer.
  * @param  ULONG* flash_address the flash address to read from.
  * @param  ULONG* destination the buffer to hold the read data.
  * @param  ULONG words the number of words to read.
  * @retval LX_SUCCESS if data is read correctly, LX_ERROR on errors.
  */
static UINT lx_nor_flash_simulator_read(struct LX_NOR_FLASH_STRUCT *nor_flash, ULONG *flash_address, ULONG *destination,
                                        ULONG words)
{
  LX_PARAMETER_NOT_USED(nor_flash);

  memcpy((VOID *)destination, (VOID *)flash_address, words * sizeof(ULONG));
  return (LX_SUCCESS);
}

/**
  * @brief  write source buffer into flash memory address.
  * @param  ULONG* flash_address the flash address to write into.
  * @param  ULONG* source the data buffer to be written.
  * @param  ULONG words the number of words to write.
  * @retval LX_SUCCESS if data is written correctly, LX_ERROR on errors.
  */
static UINT lx_nor_flash_simulator_write(struct LX_NOR_FLASH_STRUCT *nor_flash, ULONG *flash_address, ULONG *source,
                                         ULONG words)
{
  LX_PARAMETER_NOT_USED(nor_flash);

  memcpy((VOID *)flash_address, (VOID *)source, words * sizeof(ULONG));
  return (LX_SUCCESS);
}

/**
  * @brief  erases the specified block of the OSPI memory.
  * @param  nor_flash: pointer to the LX_NOR_FLASH_STRUCT instance.
  * @param  ULONG block: the block to be erased.
  * @retval LX_SUCCESS on Success, LX_ERROR on errors.
  */
static UINT lx_nor_flash_simulator_block_erase(struct LX_NOR_FLASH_STRUCT *nor_flash, ULONG block, ULONG erase_count)
{
  LX_PARAMETER_NOT_USED(erase_count);
  STM32_LX_NOR_FLASH_DRIVER_CONTEXT *simulator_config  =
    (STM32_LX_NOR_FLASH_DRIVER_CONTEXT *) nor_flash->lx_nor_flash_info_ptr;
  ULONG  *pointer;

  /* Setup pointer.  */
  pointer = (ULONG *)simulator_config->nor_flash_start_address
            + (block * simulator_config->nor_flash_block_size / sizeof(ULONG));
  /* Loop to erase block.  */
  memset((VOID *) pointer, 0xff, simulator_config->nor_flash_block_size);

  return (LX_SUCCESS);
}

/**
  * @brief  Check that a block was actually erased.
  * @param  nor_flash: pointer to the LX_NOR_FLASH_STRUCT instance.
  * @param  ULONG  block: the block to be checked.
  * @retval LX_SUCCESS if data is erased correctly, LX_ERROR on errors.
  */
static UINT lx_nor_flash_simulator_block_erased_verify(struct LX_NOR_FLASH_STRUCT *nor_flash, ULONG block)
{
  ULONG *word_ptr;
  ULONG words;
  STM32_LX_NOR_FLASH_DRIVER_CONTEXT *simulator_config  =
    (STM32_LX_NOR_FLASH_DRIVER_CONTEXT *) nor_flash->lx_nor_flash_info_ptr;

  /* Determine if the block is completely erased.  */
  word_ptr = (ULONG *)simulator_config->nor_flash_start_address
             + (block * simulator_config->nor_flash_block_size / sizeof(ULONG));

  /* Calculate the number of words in a block.  */
  words =  simulator_config->nor_flash_block_size / sizeof(ULONG);

  /* Loop to check if the block is erased.  */
  while (words--)
  {
    /* Check that the word is erased.  */
    if (*word_ptr++ != 0xFFFFFFFF)
    {
      return (LX_ERROR);
    }
  }

  /* Return success.  */
  return (LX_SUCCESS);
}

/**
  * @brief  Handles system errors for the NOR flash driver
  * @param  nor_flash: a pointer to the LX_NOR_FLASH_STRUCT instance.
  * @param  error_code: the error code that indicates the type of error encountered.
  * @retval Returns LX_ERROR to indicate an error has occurred.
  */
UINT __attribute__((weak)) lx_nor_flash_simulator_system_error(struct LX_NOR_FLASH_STRUCT *nor_flash, UINT error_code)
{
  LX_PARAMETER_NOT_USED(nor_flash);
  LX_PARAMETER_NOT_USED(error_code);

  return LX_ERROR;
}
