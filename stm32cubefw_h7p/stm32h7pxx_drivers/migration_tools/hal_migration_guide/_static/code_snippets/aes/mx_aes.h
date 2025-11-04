/**
  ******************************************************************************
  * @file           : mx_aes.h
  * @brief          : Header for mx_aes.c file.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef MX_AES_H
#define MX_AES_H

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
/* Exported functions for AES in HAL layer */
/******************************************************************************/
/**
  * @brief mx_aes_cfg1_hal init function
  * This function configures the hardware resources used in this example
  * @retval pointer to handle or NULL in case of failure
  */
hal_aes_handle_t *mx_aes_cfg1_hal_init(void);

/**
  * @brief  De-initialize aes instance and return it.
  */
void mx_aes_cfg1_hal_deinit(void);

/**
  * @brief  Get the AES object.
  * @retval Pointer on the AES Handle
  */
hal_aes_handle_t *mx_aes_hal_gethandle(void);

/******************************************************************************/
/*                     LPDMA1 channel1 global interrupt                    */
/******************************************************************************/
void LPDMA1_CH1_IRQHandler(void);

/******************************************************************************/
/*                     LPDMA1 channel0 global interrupt                    */
/******************************************************************************/
void LPDMA1_CH0_IRQHandler(void);


#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* MX_AES_H */
