
/**
  ******************************************************************************
  * @file           : mx_hsp1.c
  * @brief          : HSP1 Peripheral initialization
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

/* Includes ------------------------------------------------------------------*/
#include "mx_hsp1.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private functions prototype------------------------------------------------*/
/* Exported variables by reference--------------------------------------------*/
static hal_hsp_handle_t hHSP1;
/******************************************************************************/
/* Exported functions for HSP1 in HAL layer */
/******************************************************************************/
hal_hsp_handle_t *mx_hsp1_init(void)
{
  HAL_RCC_HSP1_EnableClock();

  if (HAL_HSP_Init(&hHSP1, HAL_HSP1) != HAL_OK)
  {
    return NULL;
  }

  /* No GPIO configuration required for HSP1 */

  /* Smart clocking is enabled by default, no need to enable it */

  HAL_CORTEX_NVIC_SetPriority(HSP1_IRQn, HAL_CORTEX_NVIC_PREEMP_PRIORITY_0, HAL_CORTEX_NVIC_SUB_PRIORITY_0);
  HAL_CORTEX_NVIC_EnableIRQ(HSP1_IRQn);

  return &hHSP1;
}

void mx_hsp1_deinit(void)
{
  HAL_CORTEX_NVIC_DisableIRQ(HSP1_IRQn);

  HAL_HSP_DeInit(&hHSP1);

  HAL_RCC_HSP1_DisableClock();

  HAL_RCC_HSP1_Reset();

  /* No GPIO de-initialization required for HSP1 */
}

hal_hsp_handle_t *mx_hsp1_gethandle(void)
{
  return &hHSP1;
}

/******************************************************************************/
/*                            HSP global interrupt                            */
/******************************************************************************/
void HSP1_IRQHandler(void)
{
  HAL_HSP_IRQHandler(&hHSP1);
}
