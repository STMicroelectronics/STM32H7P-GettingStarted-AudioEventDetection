/**
  ******************************************************************************
  * @file           : mx_gpio_default.h
  * @brief          : Header for mx_gpio_default.c file.
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
#ifndef MX_GPIO_DEFAULT_H
#define MX_GPIO_DEFAULT_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* Includes ------------------------------------------------------------------*/
#include "stm32_hal.h"
#include "mx_def.h"

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/******************************************************************************/
/* Exported defines for gpio_default in HAL layer                             */
/******************************************************************************/

/* GPIO pin aliases for PE1 */
#define PE1_PORT                                        HAL_GPIOE
#define PE1_PIN                                         HAL_GPIO_PIN_1
#define PE1_INIT_STATE                                  HAL_GPIO_PIN_RESET
#define PE1_ACTIVE_STATE                                HAL_GPIO_PIN_SET
#define PE1_INACTIVE_STATE                              HAL_GPIO_PIN_RESET

/* GPIO pin aliases for PG1 */
#define PG1_PORT                                        HAL_GPIOG
#define PG1_PIN                                         HAL_GPIO_PIN_1
#define PG1_INIT_STATE                                  HAL_GPIO_PIN_SET
#define PG1_ACTIVE_STATE                                HAL_GPIO_PIN_RESET
#define PG1_INACTIVE_STATE                              HAL_GPIO_PIN_SET

/* GPIO pin aliases for PG4 */
#define CS_DISP_PORT                                    HAL_GPIOG
#define CS_DISP_PIN                                     HAL_GPIO_PIN_4
#define CS_DISP_INIT_STATE                              HAL_GPIO_PIN_RESET
#define CS_DISP_ACTIVE_STATE                            HAL_GPIO_PIN_SET
#define CS_DISP_INACTIVE_STATE                          HAL_GPIO_PIN_RESET

/* GPIO pin aliases for PG6 */
#define D_C_DISP_PORT                                   HAL_GPIOG
#define D_C_DISP_PIN                                    HAL_GPIO_PIN_6
#define D_C_DISP_INIT_STATE                             HAL_GPIO_PIN_RESET
#define D_C_DISP_ACTIVE_STATE                           HAL_GPIO_PIN_SET
#define D_C_DISP_INACTIVE_STATE                         HAL_GPIO_PIN_RESET

/* GPIO pin aliases for PH6 */
#define MKB_SCK_PORT                                    HAL_GPIOH
#define MKB_SCK_PIN                                     HAL_GPIO_PIN_6
#define MKB_SCK_INIT_STATE                              HAL_GPIO_PIN_RESET
#define MKB_SCK_ACTIVE_STATE                            HAL_GPIO_PIN_SET
#define MKB_SCK_INACTIVE_STATE                          HAL_GPIO_PIN_RESET

/* Exported macros -----------------------------------------------------------*/
/* Exported variables --------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
/******************************************************************************/
/* Exported functions for gpio_default in HAL layer                           */
/******************************************************************************/
/**
  * @brief mx_gpio_default init function
  * This function configures the hardware resources used in this example
  * @retval 0  GPIO group correctly initialized
  * @retval -1 Issue detected during GPIO group initialization
  */
system_status_t mx_gpio_default_init(void);

/**
  * @brief  De-initialize gpio_default instance.
  */
system_status_t mx_gpio_default_deinit(void);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* MX_GPIO_DEFAULT_H */
