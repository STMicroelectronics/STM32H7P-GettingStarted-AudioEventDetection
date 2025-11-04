/**
  ******************************************************************************
  * @file           : mx_tim1.h
  * @brief          : Header for mx_tim1.c file.
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
#ifndef STM32_TIM1_H
#define STM32_TIM1_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32_hal.h"

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/

/* Compute the prescaler value to have TIMx counter clock equal to 1000000 Hz */
#define MX_PRESCALER_VALUE      159U

/* Compute the Auto Reload Register value to have the expected PWM frequency */
#define MX_PERIOD_VALUE       249U              /* Period Value  */
/* Exported variables --------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/

/**
  * @brief tim1 init function
  * This function configures the hardware resources used in this example
  * @param None
  * @retval -1 in case of failure
  */
hal_tim_handle_t *mx_tim1_cfg1_init(void);


/**
  * @brief  Get the TIM1 object.
  * @param None
  * @retval Pointer on the TIM1 Handle
  */
void *mx_tim1_gethandle(void);


/**
  * @brief Timer peripheral deinitialization function
  * @param None
  * @retval -1 in case of failure
  */
int32_t mx_tim1_cfg1_deinit(void);

/**
  * @brief IRQ DMA1 channel0 Handler
  * @param None
  * @retval None
  */
void GPDMA1_CH0_IRQHandler(void);


#ifdef __cplusplus
}
#endif

#endif /* STM32_TIM1_H */
