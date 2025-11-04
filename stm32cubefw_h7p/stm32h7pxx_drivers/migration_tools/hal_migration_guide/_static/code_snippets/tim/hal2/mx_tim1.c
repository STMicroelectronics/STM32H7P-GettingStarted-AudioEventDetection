/**
  ******************************************************************************
  * @file           : mx_tim1.c
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
#include "mx_tim1.h"
#include "mx_hal_def.h"

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/

/* Private variables  -------------------------------------------*/

/* Private functions ---------------------------------------------------------*/
/* Exported variables by reference -------------------------------------------*/
/* TIM handle */
static hal_tim_handle_t hTIM;
static hal_dma_handle_t gh_dma1_channel0;
hal_dma_node_t  TIMNode;

/**
  * @brief Timer Initialization Function
  * @param None
  * @retval -1 in case of failure
  */
hal_tim_handle_t *mx_tim1_cfg1_init(void)
{
  hal_tim_config_t tim_config;
  hal_tim_oc_compare_unit_config_t tim_oc_compare_unit_config;
  hal_tim_oc_channel_config_t tim_oc_channel_config;

  HAL_RCC_TIM1_EnableClock();

  /* Init Timer PWM */
  if (HAL_TIM_Init(&hTIM, HAL_TIM1) != HAL_OK)
  {
    return NULL;
  }

  tim_config.prescaler = MX_PRESCALER_VALUE;
  tim_config.counter_mode = HAL_TIM_COUNTER_UP;
  tim_config.period = MX_PERIOD_VALUE;
  tim_config.clock_division = HAL_TIM_CLK_DIVISION_DIV1;
  tim_config.repetition_counter = 0;
  tim_config.clock_sel.clock_source = HAL_TIM_CLK_INTERNAL;
  tim_config.clock_sel.trigger = HAL_TIM_TRIG_ITR0;
  if (HAL_TIM_SetConfig(&hTIM, &tim_config) != HAL_OK)
  {
    return NULL;
  }

  /* TIM1 interrupt Init */
  HAL_CORTEX_NVIC_SetPriority(TIM1_IRQn, HAL_CORTEX_NVIC_PREEMP_PRIORITY_0, HAL_CORTEX_NVIC_SUB_PRIORITY_0);
  HAL_CORTEX_NVIC_EnableIRQ(TIM1_IRQn);
  
  tim_oc_compare_unit_config.mode = HAL_TIM_OC_PWM1;
  tim_oc_compare_unit_config.pulse = 0;
  if (HAL_TIM_OC_SetConfigCompareUnit(&hTIM, HAL_TIM_OC_COMPARE_UNIT_1, &tim_oc_compare_unit_config) != HAL_OK)
  {
    return NULL;
  }

  tim_oc_channel_config.polarity = HAL_TIM_OC_HIGH;
  tim_oc_channel_config.idle_state = HAL_TIM_OC_IDLE_STATE_RESET;
  if (HAL_TIM_OC_SetConfigChannel(&hTIM, HAL_TIM_CHANNEL_1, &tim_oc_channel_config) != HAL_OK)
  {
    return NULL;
  }

  if (HAL_TIM_OC_EnableChannelComparePreload(&hTIM, HAL_TIM_CHANNEL_1) != HAL_OK)
  {
    return NULL;
  }

  hal_dma_direct_xfer_config_t p_config;
  gh_dma1_channel0.xfer_mode = HAL_DMA_XFER_MODE_LINKEDLIST_CIRCULAR;

  /* Enable GPDMA1 clock */
  HAL_RCC_GPDMA1_EnableClock();

  /* Initialize the DMA channel0 handle in direct programming mode */
  gh_dma1_channel0.instance  = HAL_GPDMA1_CH0;
  if (HAL_DMA_Init(&gh_dma1_channel0, HAL_GPDMA1_CH0) != HAL_OK)
  {
    return NULL;
  }
  /* GPDMA1 interrupts Init */
  HAL_CORTEX_NVIC_SetPriority(GPDMA1_CH0_IRQn, HAL_CORTEX_NVIC_PREEMP_PRIORITY_0, HAL_CORTEX_NVIC_SUB_PRIORITY_0);
  HAL_CORTEX_NVIC_EnableIRQ(GPDMA1_CH0_IRQn);

  /* Set the DMA channel linked-list transfer configuration */
  p_config.request  = HAL_GPDMA1_REQUEST_TIM1_CC1;
  p_config.direction = HAL_DMA_DIRECTION_MEMORY_TO_PERIPH;
  p_config.src_inc = HAL_DMA_SRC_ADDR_INCREMENTED;
  p_config.dest_inc = HAL_DMA_DEST_ADDR_FIXED;
  p_config.src_data_width = HAL_DMA_SRC_DATA_WIDTH_WORD;
  p_config.dest_data_width = HAL_DMA_DEST_DATA_WIDTH_WORD;
  p_config.priority = HAL_DMA_PRIORITY_HIGH;

  if (HAL_DMA_SetConfigPeriphLinkedListCircularXfer(&gh_dma1_channel0, &TIMNode, &p_config) != HAL_OK)
  {
    return NULL;
  }

  /* Link the DMA handle to the TIM handle */
  HAL_TIM_SetDMA(&hTIM, HAL_TIM_DMA_ID_CC1, &gh_dma1_channel0);

  /* PE9  <= GPIO_PWM_TIM1_CH1 */
  hal_gpio_config_t  config_gpio;

  HAL_RCC_GPIOE_EnableClock();

  config_gpio.mode        = HAL_GPIO_MODE_ALTERNATE;
  config_gpio.pull        = HAL_GPIO_PULL_NO;
  config_gpio.speed       = HAL_GPIO_SPEED_FREQ_VERY_HIGH;
  config_gpio.output_type = HAL_GPIO_OUTPUT_PUSHPULL;
  config_gpio.alternate   = HAL_GPIO_AF1_TIM1;
  HAL_GPIO_Init(HAL_GPIOE, HAL_GPIO_PIN_9, &config_gpio);

  return &hTIM;
}

/**
  * @brief  Get the TIM1 object.
  * @param None
  * @retval Pointer on the TIM1 Handle
  */
void *mx_tim1_gethandle(void)
{
  return (void *)&hTIM;
}

/**
  * @brief Timer peripheral deinitialization function
  * @param None
  * @retval -1 in case of failure
  */
int32_t mx_tim1_cfg1_deinit(void)
{
  int32_t ret = 0;

  HAL_CORTEX_NVIC_DisableIRQ(TIM1_IRQn);

  /* Stop PWM generation on CHANNEL 1 */
  if (HAL_TIM_OC_StopChannel_DMA(&hTIM, HAL_TIM_CHANNEL_1) != HAL_OK)
  {
    ret = -1;
  }

  /* Deinitialization the timer peripheral */
  HAL_TIM_DeInit(&hTIM);

  /* De-initialize the DMA channel */
  HAL_DMA_DeInit(&gh_dma1_channel0);

  /* PE9  <= GPIO_PWM_TIM1_CH1 */
  HAL_GPIO_DeInit(HAL_GPIOE, HAL_GPIO_PIN_9);

  return ret;
}


/******************************************************************************/
/*                     Interruption and Exception Handlers                    */
/******************************************************************************/
/**
* @brief This function handles TIM1 interrupt.
*/
void TIM1_IRQHandler(void)
{
  HAL_TIM_IRQHandler(&hTIM);
}

/**
  * @brief IRQ DMA1 channel0 Handler
  */
void GPDMA1_CH0_IRQHandler()
{
  HAL_DMA_IRQHandler(&gh_dma1_channel0);
}
