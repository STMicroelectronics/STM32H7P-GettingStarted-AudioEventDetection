/**
  ******************************************************************************
  * @file           : mx_hsp1.h
  * @brief          : Header for mx_hsp1.c file.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023-2025 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef STM32_HSP1_H
#define STM32_HSP1_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* Includes ------------------------------------------------------------------*/
#include "stm32_hal.h"

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macros -----------------------------------------------------------*/
/* Exported variables --------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */

/******************************************************************************/
/* Exported functions for SW instance0 in HAL layer */
/******************************************************************************/
/**
  * @brief mx_hsp1_cfg1_hal init function.
  * This function configures the hardware resources used in this example
  * @retval pointer to handle or NULL in case of failure
  */
hal_hsp_handle_t *mx_hsp1_cfg1_hal_init(void);

/**
  * @brief  De-initialize mx_hsp1_cfg1_hal instance and return it.
  * @retval None
  */
void mx_hsp1_cfg1_hal_deinit(void);

/**
  * @brief mx_hsp1_cfg2_hal init function.
  * This function configures the hardware resources used in this example
  * @retval pointer to handle or NULL in case of failure
  */
hal_hsp_handle_t *mx_hsp1_cfg2_hal_init(void);

/**
  * @brief  De-initialize mx_hsp1_cfg2_hal instance and return it.
  * @retval None
  */
void mx_hsp1_cfg2_hal_deinit(void);

/**
  * @brief  Get the mx_hsp1_hal object.
  * @retval Pointer on the mx_hsp1_hal Handle
  */
hal_hsp_handle_t *mx_hsp1_hal_gethandle(void);

/******************************************************************************/
/*                     Interruption and Exception Handlers                    */
/******************************************************************************/
void HSP1_IRQHandler(void);
void HSP1_ERR_IRQHandler(void);
void HSP1_EVT_IRQHandler(void);
void HSP1_FWEVT_IRQHandler(void);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* STM32_HSP1_H */

