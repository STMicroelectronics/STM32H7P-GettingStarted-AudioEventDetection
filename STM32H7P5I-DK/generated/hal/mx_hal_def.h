/**
  ******************************************************************************
  * @file           : mx_hal_def.h
  * @brief          : Exporting peripherals initialization
  *                   Include entry for the target folder to the application.
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
#ifndef MX_HAL_DEF_H
#define MX_HAL_DEF_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* Includes ------------------------------------------------------------------*/
#include "mx_def.h"
#include "stm32_hal.h"
#include "mx_adf1.h"
#include "mx_cortex_mpu.h"
#include "mx_cortex_nvic.h"
#include "mx_cortex_scb.h"
#include "mx_gpio_default.h"
#include "mx_hsp1.h"
#include "mx_pwr.h"
#include "mx_rcc.h"
#include "mx_spi1.h"
#include "mx_lpuart1.h"

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macros -----------------------------------------------------------*/

/* ########### Aliases to initialization functions ########### */

  /* *************************************************************
    ADF1: No software label has been defined for this peripheral instance
      in the STM32CubeMX2 configuration panel.
      As a result, no aliases are generated for mx_adf1_init
    ************************************************************* */

  /* *************************************************************
    Cortex_MPU: No software label has been defined for this peripheral instance
      in the STM32CubeMX2 configuration panel.
      As a result, no aliases are generated for mx_cortex_mpu_init
    ************************************************************* */

  /* *************************************************************
    Cortex_NVIC: No software label has been defined for this peripheral instance
      in the STM32CubeMX2 configuration panel.
      As a result, no aliases are generated for mx_cortex_nvic_init
    ************************************************************* */

  /* *************************************************************
    Cortex_SCB: No software label has been defined for this peripheral instance
      in the STM32CubeMX2 configuration panel.
      As a result, no aliases are generated for mx_cortex_scb_init
    ************************************************************* */

  /* *************************************************************
    gpio_default: No software label has been defined for this peripheral instance
      in the STM32CubeMX2 configuration panel.
      As a result, no aliases are generated for mx_gpio_default_init
    ************************************************************* */

  /* *************************************************************
    HSP1: No software label has been defined for this peripheral instance
      in the STM32CubeMX2 configuration panel.
      As a result, no aliases are generated for mx_hsp1_init
    ************************************************************* */

  /* *************************************************************
    PWR: No software label has been defined for this peripheral instance
      in the STM32CubeMX2 configuration panel.
      As a result, no aliases are generated for mx_pwr_init
    ************************************************************* */

  /* *************************************************************
    RCC: No software label has been defined for this peripheral instance
      in the STM32CubeMX2 configuration panel.
      As a result, no aliases are generated for mx_rcc_init
    ************************************************************* */

  /* ***********************************************************
      SPI1: aliases for initialization functions
    *********************************************************** */

/**
  * @brief  Initialize the mx_spi1 with HAL layer
  *         Name of the User label:
  *                   mx_display_bus
  * @retval hal_spi_handle_t Pointer on the handle on the SPI1 instance
  */
#define mx_display_bus_init mx_spi1_init

  /* *************************************************************
    LPUART1: No software label has been defined for this peripheral instance
      in the STM32CubeMX2 configuration panel.
      As a result, no aliases are generated for mx_lpuart1_uart_init
    ************************************************************* */

/* ########################################################### */

/* ########### Aliases to De-Initialization functions ########### */

  /* *************************************************************
    ADF1: No software label has been defined for this peripheral instance
      in the STM32CubeMX2 configuration panel.
      As a result, no aliases are generated for mx_adf1_deinit
    ************************************************************* */

  /* *************************************************************
    Cortex_MPU: No software label has been defined for this peripheral instance
      in the STM32CubeMX2 configuration panel.
      As a result, no aliases are generated for mx_cortex_mpu_deinit
    ************************************************************* */

  /* *************************************************************
    Cortex_NVIC: No software label has been defined for this peripheral instance
      in the STM32CubeMX2 configuration panel.
      As a result, no aliases are generated for mx_cortex_nvic_deinit
    ************************************************************* */

  /* *************************************************************
    Cortex_SCB: No software label has been defined for this peripheral instance
      in the STM32CubeMX2 configuration panel.
      As a result, no aliases are generated for mx_cortex_scb_deinit
    ************************************************************* */

  /* *************************************************************
    gpio_default: No software label has been defined for this peripheral instance
      in the STM32CubeMX2 configuration panel.
      As a result, no aliases are generated for mx_gpio_default_deinit
    ************************************************************* */

  /* *************************************************************
    HSP1: No software label has been defined for this peripheral instance
      in the STM32CubeMX2 configuration panel.
      As a result, no aliases are generated for mx_hsp1_deinit
    ************************************************************* */

  /* *************************************************************
    PWR: No software label has been defined for this peripheral instance
      in the STM32CubeMX2 configuration panel.
      As a result, no aliases are generated for mx_pwr_deinit
    ************************************************************* */

  /* ***********************************************************
      SPI1: aliases for De-Initialization functions
    *********************************************************** */

/**
  * @brief  De-Initialize the mx_spi1 with HAL layer
  *         Name of the User label:
  *                   mx_display_bus
  */
#define mx_display_bus_deinit mx_spi1_deinit

  /* *************************************************************
    LPUART1: No software label has been defined for this peripheral instance
      in the STM32CubeMX2 configuration panel.
      As a result, no aliases are generated for mx_lpuart1_uart_deinit
    ************************************************************* */

/* ########################################################### */

/* ########### Aliases to get HAL handle functions ########### */

  /* *************************************************************
    ADF1: No software label has been defined for this peripheral instance
      in the STM32CubeMX2 configuration panel.
      As a result, no aliases are generated for mx_adf1_gethandle
    ************************************************************* */

  /* *************************************************************
    HSP1: No software label has been defined for this peripheral instance
      in the STM32CubeMX2 configuration panel.
      As a result, no aliases are generated for mx_hsp1_gethandle
    ************************************************************* */

  /* ***********************************************************
      SPI1: aliases for get handle functions
    *********************************************************** *//**
  * @brief  Get the HAL handle for SPI1
  *         Name of the User label:
  *                   mx_display_bus
  * @retval hal_spi_handle_t Pointer on the handle on the SPI1 instance
  */
#define mx_display_bus_gethandle mx_spi1_gethandle

  /* *************************************************************
    LPUART1: No software label has been defined for this peripheral instance
      in the STM32CubeMX2 configuration panel.
      As a result, no aliases are generated for mx_lpuart1_uart_gethandle
    ************************************************************* */

/* ########################################################### */

/* ########### Aliases to get IRQ Handlers functions ########### */
  /* ########################################################### */

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* MX_HAL_DEF_H */
