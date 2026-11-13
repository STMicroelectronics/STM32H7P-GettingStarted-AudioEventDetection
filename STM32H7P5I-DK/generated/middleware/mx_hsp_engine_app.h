/**
  ******************************************************************************
  * @file    mx_hsp_engine_app.h
  * @brief   HSP Engine applicative header file
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
  *//* Define to prevent recursive inclusion -------------------------------------*/
#ifndef MX_HSP_ENGINE_APP_H
#define MX_HSP_ENGINE_APP_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* Includes ------------------------------------------------------------------*/
#include "mx_hal_def.h"
#include "hsp.h"
#include <stdint.h>

/* Exported constants --------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/
/* Exported macros -----------------------------------------------------------*/
/* Exported functions prototypes ---------------------------------------------*/
uint32_t mx_hsp_engine_init_hsp1(void);
void mx_hsp_engine_deinit_hsp1(void);
hsp_engine_context_t *mx_hsp_engine_get_context_hsp1(void);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* MX_HSP_ENGINE_APP_H */
