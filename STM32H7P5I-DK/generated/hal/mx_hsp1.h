/**
  ******************************************************************************
  * @file           : mx_hsp1.h
  * @brief          : Header for mx_hsp1.c file.
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
#ifndef MX_HSP1_H
#define MX_HSP1_H

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
/* Exported functions for HSP in HAL layer */
/******************************************************************************/
/**
  * @brief mx_hsp1 init function
  * This function configures the hardware resources used in this example
  * @retval pointer to handle or NULL in case of failure
  */
hal_hsp_handle_t *mx_hsp1_init(void);

/**
  * @brief  De-initialize hsp1 instance and return it.
  */
void mx_hsp1_deinit(void);

/**
  * @brief  Get the HSP1 object.
  * @retval Pointer on the HSP1 Handle
  */
hal_hsp_handle_t *mx_hsp1_gethandle(void);

/******************************************************************************/
/*                            HSP global interrupt                            */
/******************************************************************************/
void HSP1_IRQHandler(void);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* MX_HSP1_H */
