/**
  ******************************************************************************
  * @file           : mx_hsp_engine_app.c
  * @brief          : HSP Engine applicative file.
 ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025-2026 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the mx_freertos_license.md file
  * in the same directory as the generated code.
  * If no mx_freertos_license.md file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  *//* Includes ------------------------------------------------------------------*/
#include "mx_hsp_engine_app.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
static hsp_engine_context_t g_hsp_engine_ctx_hsp1;

/* Private function prototypes -----------------------------------------------*/
/**
  * @brief  Application HSP Engine Initialization for instance HSP1.
  * @retval int
  */

uint32_t mx_hsp_engine_init_hsp1(void)
{
  uint32_t status = 0U;
  hsp_engine_hw_context_t hsp_engine_hw_ctx;

  hsp_engine_hw_ctx.hhsp_driver = mx_hsp1_gethandle();

  if (HSP_CORE_Init(&g_hsp_engine_ctx_hsp1, &hsp_engine_hw_ctx) != HSP_CORE_OK)
  {
    return 1;
  }

  /* HSP Engine Configuration */

   return status;
}

/**
  * @brief  Application HSP Engine Deinitialization for instance HSP1.
  */
void mx_hsp_engine_deinit_hsp1(void)
{
  HSP_CORE_DeInit(&g_hsp_engine_ctx_hsp1);
}

/** 
  * @brief  Get the HSP Engine context for instance HSP1.
  * @return Pointer to a @ref hsp_engine_context_t structure.
  */
hsp_engine_context_t *mx_hsp_engine_get_context_hsp1(void)
{
  return &g_hsp_engine_ctx_hsp1;
}
