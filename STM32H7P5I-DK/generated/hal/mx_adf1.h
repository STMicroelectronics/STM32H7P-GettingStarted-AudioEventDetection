/**
  ******************************************************************************
  * @file           : mx_adf1.h
  * @brief          : Header for mx_adf1.c file.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2026 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the mx_stm32h7pxx_hal_drivers_license.md file
  * in the same directory as the generated code.
  * If no mx_stm32h7pxx_hal_drivers_license.md file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef MX_ADF1_H
#define MX_ADF1_H

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
/* Exported functions for ADF in HAL layer */
/******************************************************************************/
/**
  * @brief mx_adf1 init function
  * This function configures the hardware resources used in this example
  * @retval pointer to handle or NULL in case of failure
  */
hal_adf_handle_t *mx_adf1_init(void);

/**
  * @brief  De-initialize adf1 instance and return it.
  */
void mx_adf1_deinit(void);

/**
  * @brief  Get the ADF1 object.
  * @retval Pointer on the ADF1 Handle
  */
hal_adf_handle_t *mx_adf1_gethandle(void);

/******************************************************************************/
/*                     GPDMA1 channel 0 interrupt                    */
/******************************************************************************/
void GPDMA1_CH0_IRQHandler(void);

/******************************************************************************/
/*                     ADF1 filter 0 global interrupt                    */
/******************************************************************************/
void ADF1_FLT0_IRQHandler(void);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* MX_ADF1_H */
