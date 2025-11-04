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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef FX_STM32_NAND_FLASH_DRIVER_CONTEXT_H
#define FX_STM32_NAND_FLASH_DRIVER_CONTEXT_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "fx_api.h"
#include "lx_api.h"
/* Exported types ------------------------------------------------------------*/

typedef enum
{
  STM32_FX_NAND_FLAG_NONE                   = 0x00000000,
  STM32_FX_NAND_FLAG_FORMAT_ON_INIT         = 0x00000001,
  STM32_FX_NAND_FLAG_ALL                    = 0x00000001,
} STM32_FX_NAND_FLASH_DRIVER_FLAGS;

typedef struct STM32_FX_NAND_FLASH_DRIVER_CONTEXT_STURCT
{
  UINT                                  stm32_fx_nand_flash_flags;
  LX_NAND_FLASH                         *stm32_lx_nand_flash_handle;
  CHAR                                  stm32_lx_nand_flash_name[16];
  ULONG                                 nand_flash_op_timeout;
  UINT                                (*stm32_lx_nand_flash_driver_init)(LX_NAND_FLASH *);
} STM32_FX_NAND_FLASH_DRIVER_CONTEXT;

/* Exported constants --------------------------------------------------------*/

/* Exported macro ------------------------------------------------------------*/

/* Exported functions prototypes ---------------------------------------------*/

/* Private defines -----------------------------------------------------------*/

#ifdef __cplusplus
}
#endif

#endif /* FX_STM32_NOR_FLASH_DRIVER_CONTEXT_H */
