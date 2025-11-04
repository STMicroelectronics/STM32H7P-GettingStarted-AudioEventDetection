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
#ifndef STM32_LX_NOR_FLASH_SIMULATOR_DRIVER_H
#define STM32_LX_NOR_FLASH_SIMULATOR_DRIVER_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* Includes ------------------------------------------------------------------*/
#include "stm32_lx_nor_flash_driver_context.h"

/* Exported types ------------------------------------------------------------*/

/* Exported constants --------------------------------------------------------*/

/* Exported macro ------------------------------------------------------------*/

/* Exported functions prototypes ---------------------------------------------*/
UINT stm32_lx_nor_flash_simulator_initialize(LX_NOR_FLASH *nor_flash);

/* Private defines -----------------------------------------------------------*/

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* STM32_LX_NOR_FLASH_SIMULATOR_DRIVER_H */
