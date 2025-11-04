/**
  ******************************************************************************
  * @file           : mx_tim2.c
  * @brief          : Peripheral initialization
  *                   File per peripheral instance that is handling the peripheral
  *                   initialization and the IRQ handlers. Init parameters provided
  *                   as a set of defines configurable/generated for a given target
  *                   through the  hal_tim_settings.json and the config tool.
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
/* Includes ------------------------------------------------------------------*/
#include "mx_tim2.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private functions prototype------------------------------------------------*/

/* Exported variables by reference--------------------------------------------*/
static hal_tim_handle_t hTIM2;

/* Exported function definition ----------------------------------------------*/
/******************************************************************************/
/* Exported functions for SW instance4 in HAL layer */
/******************************************************************************/

hal_tim_handle_t *mx_tim2_cfg1_hal_init(void)
{
  hal_tim_config_t  config;

  if (HAL_TIM_Init(&hTIM2, HAL_TIM2) != HAL_OK)
  {
    return NULL;
  }

  HAL_RCC_TIM2_EnableClock();

  /* Timer configuration to reach the output frequency at 2441 Hz */
  config.prescaler              = 0;
  config.counter_mode           = HAL_TIM_COUNTER_UP;
  config.period                 = 0xFFFF;
  config.clock_division         = HAL_TIM_CLK_DIVISION_DIV1;
  config.repetition_counter     = 0;
  config.clock_sel.clock_source = HAL_TIM_CLK_INTERNAL;
  if (HAL_TIM_SetConfig(&hTIM2, &config) != HAL_OK)
  {
    return NULL;
  }

  /* Configure Channels */
  hal_tim_oc_channel_config_t oc_config;

  oc_config.polarity    = HAL_TIM_OC_HIGH;
  oc_config.idle_state  = HAL_TIM_OC_IDLE_STATE_RESET;
  if (HAL_TIM_OC_SetConfigChannel(&hTIM2, HAL_TIM_CHANNEL_1, &oc_config) != HAL_OK)
  {
    return NULL;
  }

  hal_tim_oc_compare_unit_config_t oc_compare_unit_config;

  oc_compare_unit_config.mode  = HAL_TIM_OC_FROZEN;
  oc_compare_unit_config.pulse = 0x00000000;
  if (HAL_TIM_OC_SetConfigCompareUnit(&hTIM2, hal_tim_oc_channel_to_compare_unit(HAL_TIM_CHANNEL_1),
                                      &oc_compare_unit_config) != HAL_OK)
  {
    return NULL;
  }

  /* Any events generate an update interrupt or DMA request if enabled (default) */
  /* HAL_TIM_SetUpdateSource(&hTIM2, HAL_TIM_UPDATE_REGULAR); */
  /* UEV event generation is enabled by default */
  /* HAL_TIM_EnableUpdateGeneration(&hTIM2); */

  /* Configure Master mode */
  /* HAL_TIM_SetTriggerOutput(&hTIM2, HAL_TIM_TRGO_RESET); */

  /* Configure Encoder interface */

  /* Configure the Pulse generator */
  hal_tim_pulse_generator_config_t pulse_generator;
  pulse_generator.pulse_width = 0;
  pulse_generator.prescaler = HAL_TIM_PULSE_DIV1;
  HAL_TIM_OC_SetPulseGenerator(&hTIM2, &pulse_generator);

  /* HAL_TIM_SetCaptureCompareDMAReqSource(&hTIM2, HAL_TIM_CC_DMAREQ_CC); */

  HAL_TIM_SetLockLevel(&hTIM2, HAL_TIM_LOCK_);

  /* GPIO configuration for channel1 */
  HAL_RCC_GPIOA_EnableClock();


  hal_gpio_config_t  gpio_config;

  /**
    TIM2 GPIO Configuration
    HW labels: PA0 GPIO Configuration

    PA0
                            --------->  TIM2_CH1
    **/
  gpio_config.mode        = HAL_GPIO_MODE_ALTERNATE;
  gpio_config.output_type = HAL_GPIO_OUTPUT_PUSHPULL;
  gpio_config.pull        = HAL_GPIO_PULL_NO;
  gpio_config.speed       = HAL_GPIO_SPEED_FREQ_LOW;
  gpio_config.alternate   = HAL_GPIO_AF_1;
  HAL_GPIO_Init(HAL_GPIOA, HAL_GPIO_PIN_0, &gpio_config);


  return &hTIM2;
}

void mx_tim2_cfg1_hal_deinit(void)
{
  (void)HAL_TIM_DeInit(&hTIM2);

  HAL_RCC_TIM2_Reset();

  HAL_RCC_TIM2_DisableClock();

  /* ###  GPIO pins de-initialization ################################# */
  /* Deinitialization of TIM2: TIM2_CH1  */
  HAL_GPIO_DeInit(HAL_GPIOA, HAL_GPIO_PIN_0);


}

hal_tim_handle_t *mx_tim2_hal_gethandle(void)
{
  return &hTIM2;
}

