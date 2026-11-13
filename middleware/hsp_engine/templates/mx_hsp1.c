/**
  ******************************************************************************
  * @file           : mx_hsp1.c
  * @brief          : Peripheral initialization
  *                   File per peripheral instance that is handling the peripheral
  *                   initialization and the IRQ handlers. Init parameters provided
  *                   as a set of defines configurable/generated for a given target
  *                   through the  hal_tim_settings.json and the config tool.
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
/* Includes ------------------------------------------------------------------*/
#include "mx_hsp1.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private functions prototype------------------------------------------------*/

/* Exported variables by reference--------------------------------------------*/
static hal_hsp_handle_t hHSP1;

/* Exported function definition ----------------------------------------------*/
/******************************************************************************/
/* Exported functions for SW instance0 in HAL layer */
/******************************************************************************/

hal_hsp_handle_t *mx_hsp1_cfg1_hal_init(void)
{
  if (HAL_HSP_Init(&hHSP1, HAL_HSP1) != HAL_OK)
  {
    return NULL;
  }

  HAL_RCC_HSP1_EnableClock();

  /* Enable Timer update interrupt */
  HAL_CORTEX_NVIC_SetPriority(HSP1_IRQn, HAL_CORTEX_NVIC_PREEMP_PRIORITY_0, HAL_CORTEX_NVIC_SUB_PRIORITY_0);
  HAL_CORTEX_NVIC_EnableIRQ(HSP1_IRQn);

  return &hHSP1;
}

void mx_hsp1_cfg1_hal_deinit(void)
{
  /* Disable Timer update interrupt */
  HAL_CORTEX_NVIC_DisableIRQ(HSP1_IRQn);

  (void)HAL_HSP_DeInit(&hHSP1);

  HAL_RCC_HSP1_Reset();

  HAL_RCC_HSP1_DisableClock();
}

hal_hsp_handle_t *mx_hsp1_cfg2_hal_init(void)
{
  if (HAL_HSP_Init(&hHSP1, HAL_HSP1) != HAL_OK)
  {
    return NULL;
  }

  HAL_RCC_HSP1_EnableClock();

  /* Enable HSP update interrupt */
  HAL_CORTEX_NVIC_SetPriority(HSP1_ERR_IRQn, HAL_CORTEX_NVIC_PREEMP_PRIORITY_0, HAL_CORTEX_NVIC_SUB_PRIORITY_0);
  HAL_CORTEX_NVIC_EnableIRQ(HSP1_ERR_IRQn);
  HAL_CORTEX_NVIC_SetPriority(HSP1_EVT_IRQn, HAL_CORTEX_NVIC_PREEMP_PRIORITY_0, HAL_CORTEX_NVIC_SUB_PRIORITY_0);
  HAL_CORTEX_NVIC_EnableIRQ(HSP1_EVT_IRQn);
  HAL_CORTEX_NVIC_SetPriority(HSP1_FWEVT_IRQn, HAL_CORTEX_NVIC_PREEMP_PRIORITY_0, HAL_CORTEX_NVIC_SUB_PRIORITY_0);
  HAL_CORTEX_NVIC_EnableIRQ(HSP1_FWEVT_IRQn);

  return &hHSP1;
}

void mx_hsp1_cfg2_hal_deinit(void)
{
  /* Disable HSP update interrupt */
  HAL_CORTEX_NVIC_DisableIRQ(HSP1_ERR_IRQn);
  HAL_CORTEX_NVIC_DisableIRQ(HSP1_EVT_IRQn);
  HAL_CORTEX_NVIC_DisableIRQ(HSP1_FWEVT_IRQn);

  (void)HAL_HSP_DeInit(&hHSP1);

  HAL_RCC_HSP1_Reset();

  HAL_RCC_HSP1_DisableClock();
}

hal_hsp_handle_t *mx_hsp1_hal_gethandle(void)
{
  return &hHSP1;
}

/******************************************************************************/
/*                     Interruption and Exception Handlers                    */
/******************************************************************************/
void HSP1_IRQHandler(void)
{
  HAL_HSP_IRQHandler(&hHSP1);
}

void HSP1_ERR_IRQHandler(void)
{
  HAL_HSP_ERR_IRQHandler(&hHSP1);
}

void HSP1_EVT_IRQHandler(void)
{
  HAL_HSP_EVT_IRQHandler(&hHSP1);
}

void HSP1_FWEVT_IRQHandler(void)
{
  HAL_HSP_FWEVT_IRQHandler(&hHSP1);
}
