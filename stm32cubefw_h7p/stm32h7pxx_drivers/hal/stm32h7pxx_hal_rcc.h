/**
  ******************************************************************************
  * @file    stm32h7pxx_hal_rcc.h
  * @author  GPM Application Team
  * @brief   Header file of RCC HAL module.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2021-2024 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef STM32H7PXX_HAL_RCC_H
#define STM32H7PXX_HAL_RCC_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32h7pxx_hal_def.h"
#include "stm32h7pxx_ll_rcc.h"
#include "stm32h7pxx_ll_bus.h"

/** @addtogroup STM32H7PXX_HAL_Driver
  * @{
  */

/** @addtogroup RCC
  * @{
  */

/* Exported constants --------------------------------------------------------*/

/** @defgroup RCC_Exported_Constants RCC Exported Constants
  * @{
  */

/**
  * @brief Oscillator enable status
  */
typedef enum
{
  HAL_RCC_OSC_DISABLED = 0,                      /*!< Oscillator is disable */
  HAL_RCC_OSC_ENABLED  = ! HAL_RCC_OSC_DISABLED, /*!< Oscillator is enable  */
} hal_rcc_osc_enable_status_t;

/**
  * @brief Oscillator ready status
  */
typedef enum
{
  HAL_RCC_OSC_NOT_READY = 0,                       /*!< Oscillator is not ready */
  HAL_RCC_OSC_READY     = ! HAL_RCC_OSC_NOT_READY, /*!< Oscillator is ready     */
} hal_rcc_osc_ready_status_t;

/**
  * @brief Oscillator Stop mode status
  */
typedef enum
{
  HAL_RCC_OSC_DISABLED_IN_STOP_MODE = 0,                                   /*!< Oscillator is enabled in Run mode only     */
  HAL_RCC_OSC_ENABLED_IN_STOP_MODE  = ! HAL_RCC_OSC_DISABLED_IN_STOP_MODE, /*!< Oscillator is enabled in Run and stop mode */
} hal_rcc_osc_stop_mode_status_t;

/**
  * @brief Peripheral clock activation status
  */
typedef enum
{
  HAL_RCC_CLK_DISABLED = 0,
  HAL_RCC_CLK_ENABLED = ! HAL_RCC_CLK_DISABLED
} hal_rcc_clk_status_t;

#if defined(HSE_VALUE)

/**
  * @brief HSE state
  */
typedef enum
{
  HAL_RCC_HSE_ON             = RCC_CR_HSEON,                                   /*!< HSE clock activation                        */
  HAL_RCC_HSE_BYPASS         = (RCC_CR_HSEON | RCC_CR_HSEBYP),                 /*!< External Analog clock source for HSE clock  */
  HAL_RCC_HSE_BYPASS_DIGITAL = (RCC_CR_HSEON | RCC_CR_HSEBYP | RCC_CR_HSEEXT), /*!< External Digital clock source for HSE clock */
} hal_rcc_hse_t;

#endif /* (HSE_VALUE) */

#if defined(LSE_VALUE)

/**
  * @brief LSE state
  */
typedef enum
{
  HAL_RCC_LSE_ON             = RCC_BDCR_LSEON,                                       /*!< LSE clock activation                        */
  HAL_RCC_LSE_BYPASS         = (RCC_BDCR_LSEON | RCC_BDCR_LSEBYP),                   /*!< External Analog clock source for LSE clock  */
  HAL_RCC_LSE_BYPASS_DIGITAL = (RCC_BDCR_LSEON | RCC_BDCR_LSEBYP | RCC_BDCR_LSEEXT), /*!< External Digital clock source for LSE clock */
} hal_rcc_lse_t;

/**
  * @brief LSE drive config
  */
typedef enum
{
  HAL_RCC_LSE_DRIVE_LOW        = LL_RCC_LSE_DRIVE_LOW,        /*!< Crystal mode lowest_drive driving capability     */
  HAL_RCC_LSE_DRIVE_MEDIUMLOW  = LL_RCC_LSE_DRIVE_MEDIUMLOW,  /*!< Crystal mode mediumlow_drive driving capability  */
  HAL_RCC_LSE_DRIVE_MEDIUMHIGH = LL_RCC_LSE_DRIVE_MEDIUMHIGH, /*!< Crystal mode mediumhigh_drive driving capability */
  HAL_RCC_LSE_DRIVE_HIGH       = LL_RCC_LSE_DRIVE_HIGH        /*!< Crystal mode highest_drive driving capability    */
} hal_rcc_lse_drive_t;

#endif /* (LSE_VALUE) */

/**
  * @brief HSI clock divider
  */
typedef enum
{
  HAL_RCC_HSI_DIV_1 = LL_RCC_HSI_DIV_1, /*!< HSI not divided  */
  HAL_RCC_HSI_DIV_2 = LL_RCC_HSI_DIV_2, /*!< HSI divided by 2 */
  HAL_RCC_HSI_DIV_4 = LL_RCC_HSI_DIV_4, /*!< HSI divided by 4 */
  HAL_RCC_HSI_DIV_8 = LL_RCC_HSI_DIV_8  /*!< HSI divided by 8 */
} hal_rcc_hsi_div_t;

/**
  * @brief Default HSI trimming value
  */
#define HAL_RCC_HSICALIBRATION_DEFAULT 0x40U /* Default HSI trimming value */

/**
  * @brief Default CSI trimming value
  */
#define HAL_RCC_CSICALIBRATION_DEFAULT 0x20U /* Default CSI trimming value */

/**
  * @brief Wake-Up from STOP Clock
  */
typedef enum
{
  HAL_RCC_STOP_WAKEUPCLOCK_HSI = LL_RCC_STOP_WAKEUPCLOCK_HSI, /*!< HSI clock used as system clock after wake-up from STOP */
  HAL_RCC_STOP_WAKEUPCLOCK_CSI = LL_RCC_STOP_WAKEUPCLOCK_CSI  /*!< CSI clock used as system clock after wake-up from STOP */
} hal_rcc_stop_wakeup_clk_t;

/**
  * @brief Wake-Up from STOP Kernel Clock
  */
typedef enum
{
  HAL_RCC_STOP_WAKEUPKERCLOCK_HSI = LL_RCC_STOP_WAKEUPKERCLOCK_HSI, /*!< HSI clock used as kernel clock after wake-up from STOP */
  HAL_RCC_STOP_WAKEUPKERCLOCK_CSI = LL_RCC_STOP_WAKEUPKERCLOCK_CSI  /*!< CSI clock used as kernel clock after wake-up from STOP */
} hal_rcc_stop_wakeup_kerclk_t;

/**
  * @brief System Clock Source
  */
typedef enum
{
  HAL_RCC_SYSCLK_SRC_HSI    = LL_RCC_SYS_CLKSOURCE_HSI,  /*!< HSI clock used as system clock  */
  HAL_RCC_SYSCLK_SRC_CSI    = LL_RCC_SYS_CLKSOURCE_CSI,  /*!< CSI clock used as system clock  */
  HAL_RCC_SYSCLK_SRC_HSE    = LL_RCC_SYS_CLKSOURCE_HSE,  /*!< HSE clock used as system clock  */
  HAL_RCC_SYSCLK_SRC_PLLCLK = LL_RCC_SYS_CLKSOURCE_PLL1  /*!< PLL1 clock used as system clock */
} hal_rcc_sysclk_src_t;

/**
  * @brief System Clock Divider
  * @note  The system clock divider for CPU clock and all bus matrix clocks
  */
typedef enum
{
  HAL_RCC_SYSCPUCLK_PRESCALER1   = LL_RCC_SYSCPUCLK_PRESCALER_1,   /*!< SYSCLK not divided    */
  HAL_RCC_SYSCPUCLK_PRESCALER2   = LL_RCC_SYSCPUCLK_PRESCALER_2,   /*!< SYSCLK divided by 2   */
  HAL_RCC_SYSCPUCLK_PRESCALER4   = LL_RCC_SYSCPUCLK_PRESCALER_4,   /*!< SYSCLK divided by 4   */
  HAL_RCC_SYSCPUCLK_PRESCALER8   = LL_RCC_SYSCPUCLK_PRESCALER_8,   /*!< SYSCLK divided by 8   */
  HAL_RCC_SYSCPUCLK_PRESCALER16  = LL_RCC_SYSCPUCLK_PRESCALER_16,  /*!< SYSCLK divided by 16  */
  HAL_RCC_SYSCPUCLK_PRESCALER64  = LL_RCC_SYSCPUCLK_PRESCALER_64,  /*!< SYSCLK divided by 64  */
  HAL_RCC_SYSCPUCLK_PRESCALER128 = LL_RCC_SYSCPUCLK_PRESCALER_128, /*!< SYSCLK divided by 128 */
  HAL_RCC_SYSCPUCLK_PRESCALER256 = LL_RCC_SYSCPUCLK_PRESCALER_256, /*!< SYSCLK divided by 256 */
  HAL_RCC_SYSCPUCLK_PRESCALER512 = LL_RCC_SYSCPUCLK_PRESCALER_512  /*!< SYSCLK divided by 512 */
} hal_rcc_sys_cpu_clk_prescaler_t;

/**
  * @brief AHB Clock Divider
  */
typedef enum
{
  HAL_RCC_HCLK_PRESCALER1 = LL_RCC_HCLK_PRESCALER_1, /*!< SYSCLK divided by HAL_RCC_SYSCLK_DIV_n only     */
  HAL_RCC_HCLK_PRESCALER2 = LL_RCC_HCLK_PRESCALER_2  /*!< SYSCLK divided by HAL_RCC_SYSCLK_DIV_n and by 2 */
} hal_rcc_hclk_prescaler_t;

/**
  * @brief APB1 APB2 APB3 Clock Source
  */
typedef enum
{
  HAL_RCC_PCLK_PRESCALER1  = LL_RCC_APB1_PRESCALER_1,  /*!< HCLK not divided   */
  HAL_RCC_PCLK_PRESCALER2  = LL_RCC_APB1_PRESCALER_2,  /*!< HCLK divided by 2  */
  HAL_RCC_PCLK_PRESCALER4  = LL_RCC_APB1_PRESCALER_4,  /*!< HCLK divided by 4  */
  HAL_RCC_PCLK_PRESCALER8  = LL_RCC_APB1_PRESCALER_8,  /*!< HCLK divided by 8  */
  HAL_RCC_PCLK_PRESCALER16 = LL_RCC_APB1_PRESCALER_16  /*!< HCLK divided by 16 */
} hal_rcc_pclk_prescaler_t;

/**
  * @brief RTC Clock Source
  */
typedef enum
{
  HAL_RCC_RTC_CLK_SRC_NONE      = LL_RCC_RTC_CLKSOURCE_NONE,                                /*!< NONE clock used as RTC clock                         */
  HAL_RCC_RTC_CLK_SRC_LSE       = LL_RCC_RTC_CLKSOURCE_LSE,                                 /*!< LSE clock used as RTC clock                          */
  HAL_RCC_RTC_CLK_SRC_LSI       = LL_RCC_RTC_CLKSOURCE_LSI,                                 /*!< LSI clock used as RTC clock                          */
  HAL_RCC_RTC_CLK_SRC_HSE_DIV2  = (LL_RCC_RTC_CLKSOURCE_HSE | (LL_RCC_RTC_HSE_DIV_2 << 16)), /*!< HSE oscillator clock divided by 2 used as RTC clock  */
  HAL_RCC_RTC_CLK_SRC_HSE_DIV3  = (LL_RCC_RTC_CLKSOURCE_HSE | (LL_RCC_RTC_HSE_DIV_3 << 16)), /*!< HSE oscillator clock divided by 3 used as RTC clock  */
  HAL_RCC_RTC_CLK_SRC_HSE_DIV4  = (LL_RCC_RTC_CLKSOURCE_HSE | (LL_RCC_RTC_HSE_DIV_4 << 16)), /*!< HSE oscillator clock divided by 4 used as RTC clock  */
  HAL_RCC_RTC_CLK_SRC_HSE_DIV5  = (LL_RCC_RTC_CLKSOURCE_HSE | (LL_RCC_RTC_HSE_DIV_5 << 16)), /*!< HSE oscillator clock divided by 5 used as RTC clock  */
  HAL_RCC_RTC_CLK_SRC_HSE_DIV6  = (LL_RCC_RTC_CLKSOURCE_HSE | (LL_RCC_RTC_HSE_DIV_6 << 16)), /*!< HSE oscillator clock divided by 6 used as RTC clock  */
  HAL_RCC_RTC_CLK_SRC_HSE_DIV7  = (LL_RCC_RTC_CLKSOURCE_HSE | (LL_RCC_RTC_HSE_DIV_7 << 16)), /*!< HSE oscillator clock divided by 7 used as RTC clock  */
  HAL_RCC_RTC_CLK_SRC_HSE_DIV8  = (LL_RCC_RTC_CLKSOURCE_HSE | (LL_RCC_RTC_HSE_DIV_8 << 16)), /*!< HSE oscillator clock divided by 8 used as RTC clock  */
  HAL_RCC_RTC_CLK_SRC_HSE_DIV9  = (LL_RCC_RTC_CLKSOURCE_HSE | (LL_RCC_RTC_HSE_DIV_9 << 16)), /*!< HSE oscillator clock divided by 9 used as RTC clock  */
  HAL_RCC_RTC_CLK_SRC_HSE_DIV10 = (LL_RCC_RTC_CLKSOURCE_HSE | (LL_RCC_RTC_HSE_DIV_10 << 16)), /*!< HSE oscillator clock divided by 10 used as RTC clock */
  HAL_RCC_RTC_CLK_SRC_HSE_DIV11 = (LL_RCC_RTC_CLKSOURCE_HSE | (LL_RCC_RTC_HSE_DIV_11 << 16)), /*!< HSE oscillator clock divided by 11 used as RTC clock */
  HAL_RCC_RTC_CLK_SRC_HSE_DIV12 = (LL_RCC_RTC_CLKSOURCE_HSE | (LL_RCC_RTC_HSE_DIV_12 << 16)), /*!< HSE oscillator clock divided by 12 used as RTC clock */
  HAL_RCC_RTC_CLK_SRC_HSE_DIV13 = (LL_RCC_RTC_CLKSOURCE_HSE | (LL_RCC_RTC_HSE_DIV_13 << 16)), /*!< HSE oscillator clock divided by 13 used as RTC clock */
  HAL_RCC_RTC_CLK_SRC_HSE_DIV14 = (LL_RCC_RTC_CLKSOURCE_HSE | (LL_RCC_RTC_HSE_DIV_14 << 16)), /*!< HSE oscillator clock divided by 14 used as RTC clock */
  HAL_RCC_RTC_CLK_SRC_HSE_DIV15 = (LL_RCC_RTC_CLKSOURCE_HSE | (LL_RCC_RTC_HSE_DIV_15 << 16)), /*!< HSE oscillator clock divided by 15 used as RTC clock */
  HAL_RCC_RTC_CLK_SRC_HSE_DIV16 = (LL_RCC_RTC_CLKSOURCE_HSE | (LL_RCC_RTC_HSE_DIV_16 << 16)), /*!< HSE oscillator clock divided by 16 used as RTC clock */
  HAL_RCC_RTC_CLK_SRC_HSE_DIV17 = (LL_RCC_RTC_CLKSOURCE_HSE | (LL_RCC_RTC_HSE_DIV_17 << 16)), /*!< HSE oscillator clock divided by 17 used as RTC clock */
  HAL_RCC_RTC_CLK_SRC_HSE_DIV18 = (LL_RCC_RTC_CLKSOURCE_HSE | (LL_RCC_RTC_HSE_DIV_18 << 16)), /*!< HSE oscillator clock divided by 18 used as RTC clock */
  HAL_RCC_RTC_CLK_SRC_HSE_DIV19 = (LL_RCC_RTC_CLKSOURCE_HSE | (LL_RCC_RTC_HSE_DIV_19 << 16)), /*!< HSE oscillator clock divided by 19 used as RTC clock */
  HAL_RCC_RTC_CLK_SRC_HSE_DIV20 = (LL_RCC_RTC_CLKSOURCE_HSE | (LL_RCC_RTC_HSE_DIV_20 << 16)), /*!< HSE oscillator clock divided by 20 used as RTC clock */
  HAL_RCC_RTC_CLK_SRC_HSE_DIV21 = (LL_RCC_RTC_CLKSOURCE_HSE | (LL_RCC_RTC_HSE_DIV_21 << 16)), /*!< HSE oscillator clock divided by 21 used as RTC clock */
  HAL_RCC_RTC_CLK_SRC_HSE_DIV22 = (LL_RCC_RTC_CLKSOURCE_HSE | (LL_RCC_RTC_HSE_DIV_22 << 16)), /*!< HSE oscillator clock divided by 22 used as RTC clock */
  HAL_RCC_RTC_CLK_SRC_HSE_DIV23 = (LL_RCC_RTC_CLKSOURCE_HSE | (LL_RCC_RTC_HSE_DIV_23 << 16)), /*!< HSE oscillator clock divided by 23 used as RTC clock */
  HAL_RCC_RTC_CLK_SRC_HSE_DIV24 = (LL_RCC_RTC_CLKSOURCE_HSE | (LL_RCC_RTC_HSE_DIV_24 << 16)), /*!< HSE oscillator clock divided by 24 used as RTC clock */
  HAL_RCC_RTC_CLK_SRC_HSE_DIV25 = (LL_RCC_RTC_CLKSOURCE_HSE | (LL_RCC_RTC_HSE_DIV_25 << 16)), /*!< HSE oscillator clock divided by 25 used as RTC clock */
  HAL_RCC_RTC_CLK_SRC_HSE_DIV26 = (LL_RCC_RTC_CLKSOURCE_HSE | (LL_RCC_RTC_HSE_DIV_26 << 16)), /*!< HSE oscillator clock divided by 26 used as RTC clock */
  HAL_RCC_RTC_CLK_SRC_HSE_DIV27 = (LL_RCC_RTC_CLKSOURCE_HSE | (LL_RCC_RTC_HSE_DIV_27 << 16)), /*!< HSE oscillator clock divided by 27 used as RTC clock */
  HAL_RCC_RTC_CLK_SRC_HSE_DIV28 = (LL_RCC_RTC_CLKSOURCE_HSE | (LL_RCC_RTC_HSE_DIV_28 << 16)), /*!< HSE oscillator clock divided by 28 used as RTC clock */
  HAL_RCC_RTC_CLK_SRC_HSE_DIV29 = (LL_RCC_RTC_CLKSOURCE_HSE | (LL_RCC_RTC_HSE_DIV_29 << 16)), /*!< HSE oscillator clock divided by 29 used as RTC clock */
  HAL_RCC_RTC_CLK_SRC_HSE_DIV30 = (LL_RCC_RTC_CLKSOURCE_HSE | (LL_RCC_RTC_HSE_DIV_30 << 16)), /*!< HSE oscillator clock divided by 30 used as RTC clock */
  HAL_RCC_RTC_CLK_SRC_HSE_DIV31 = (LL_RCC_RTC_CLKSOURCE_HSE | (LL_RCC_RTC_HSE_DIV_31 << 16)), /*!< HSE oscillator clock divided by 31 used as RTC clock */
  HAL_RCC_RTC_CLK_SRC_HSE_DIV32 = (LL_RCC_RTC_CLKSOURCE_HSE | (LL_RCC_RTC_HSE_DIV_32 << 16)), /*!< HSE oscillator clock divided by 32 used as RTC clock */
  HAL_RCC_RTC_CLK_SRC_HSE_DIV33 = (LL_RCC_RTC_CLKSOURCE_HSE | (LL_RCC_RTC_HSE_DIV_33 << 16)), /*!< HSE oscillator clock divided by 33 used as RTC clock */
  HAL_RCC_RTC_CLK_SRC_HSE_DIV34 = (LL_RCC_RTC_CLKSOURCE_HSE | (LL_RCC_RTC_HSE_DIV_34 << 16)), /*!< HSE oscillator clock divided by 34 used as RTC clock */
  HAL_RCC_RTC_CLK_SRC_HSE_DIV35 = (LL_RCC_RTC_CLKSOURCE_HSE | (LL_RCC_RTC_HSE_DIV_35 << 16)), /*!< HSE oscillator clock divided by 35 used as RTC clock */
  HAL_RCC_RTC_CLK_SRC_HSE_DIV36 = (LL_RCC_RTC_CLKSOURCE_HSE | (LL_RCC_RTC_HSE_DIV_36 << 16)), /*!< HSE oscillator clock divided by 36 used as RTC clock */
  HAL_RCC_RTC_CLK_SRC_HSE_DIV37 = (LL_RCC_RTC_CLKSOURCE_HSE | (LL_RCC_RTC_HSE_DIV_37 << 16)), /*!< HSE oscillator clock divided by 37 used as RTC clock */
  HAL_RCC_RTC_CLK_SRC_HSE_DIV38 = (LL_RCC_RTC_CLKSOURCE_HSE | (LL_RCC_RTC_HSE_DIV_38 << 16)), /*!< HSE oscillator clock divided by 38 used as RTC clock */
  HAL_RCC_RTC_CLK_SRC_HSE_DIV39 = (LL_RCC_RTC_CLKSOURCE_HSE | (LL_RCC_RTC_HSE_DIV_39 << 16)), /*!< HSE oscillator clock divided by 39 used as RTC clock */
  HAL_RCC_RTC_CLK_SRC_HSE_DIV40 = (LL_RCC_RTC_CLKSOURCE_HSE | (LL_RCC_RTC_HSE_DIV_40 << 16)), /*!< HSE oscillator clock divided by 40 used as RTC clock */
  HAL_RCC_RTC_CLK_SRC_HSE_DIV41 = (LL_RCC_RTC_CLKSOURCE_HSE | (LL_RCC_RTC_HSE_DIV_41 << 16)), /*!< HSE oscillator clock divided by 41 used as RTC clock */
  HAL_RCC_RTC_CLK_SRC_HSE_DIV42 = (LL_RCC_RTC_CLKSOURCE_HSE | (LL_RCC_RTC_HSE_DIV_42 << 16)), /*!< HSE oscillator clock divided by 42 used as RTC clock */
  HAL_RCC_RTC_CLK_SRC_HSE_DIV43 = (LL_RCC_RTC_CLKSOURCE_HSE | (LL_RCC_RTC_HSE_DIV_43 << 16)), /*!< HSE oscillator clock divided by 43 used as RTC clock */
  HAL_RCC_RTC_CLK_SRC_HSE_DIV44 = (LL_RCC_RTC_CLKSOURCE_HSE | (LL_RCC_RTC_HSE_DIV_44 << 16)), /*!< HSE oscillator clock divided by 44 used as RTC clock */
  HAL_RCC_RTC_CLK_SRC_HSE_DIV45 = (LL_RCC_RTC_CLKSOURCE_HSE | (LL_RCC_RTC_HSE_DIV_45 << 16)), /*!< HSE oscillator clock divided by 45 used as RTC clock */
  HAL_RCC_RTC_CLK_SRC_HSE_DIV46 = (LL_RCC_RTC_CLKSOURCE_HSE | (LL_RCC_RTC_HSE_DIV_46 << 16)), /*!< HSE oscillator clock divided by 46 used as RTC clock */
  HAL_RCC_RTC_CLK_SRC_HSE_DIV47 = (LL_RCC_RTC_CLKSOURCE_HSE | (LL_RCC_RTC_HSE_DIV_47 << 16)), /*!< HSE oscillator clock divided by 47 used as RTC clock */
  HAL_RCC_RTC_CLK_SRC_HSE_DIV48 = (LL_RCC_RTC_CLKSOURCE_HSE | (LL_RCC_RTC_HSE_DIV_48 << 16)), /*!< HSE oscillator clock divided by 48 used as RTC clock */
  HAL_RCC_RTC_CLK_SRC_HSE_DIV49 = (LL_RCC_RTC_CLKSOURCE_HSE | (LL_RCC_RTC_HSE_DIV_49 << 16)), /*!< HSE oscillator clock divided by 49 used as RTC clock */
  HAL_RCC_RTC_CLK_SRC_HSE_DIV50 = (LL_RCC_RTC_CLKSOURCE_HSE | (LL_RCC_RTC_HSE_DIV_50 << 16)), /*!< HSE oscillator clock divided by 50 used as RTC clock */
  HAL_RCC_RTC_CLK_SRC_HSE_DIV51 = (LL_RCC_RTC_CLKSOURCE_HSE | (LL_RCC_RTC_HSE_DIV_51 << 16)), /*!< HSE oscillator clock divided by 51 used as RTC clock */
  HAL_RCC_RTC_CLK_SRC_HSE_DIV52 = (LL_RCC_RTC_CLKSOURCE_HSE | (LL_RCC_RTC_HSE_DIV_52 << 16)), /*!< HSE oscillator clock divided by 52 used as RTC clock */
  HAL_RCC_RTC_CLK_SRC_HSE_DIV53 = (LL_RCC_RTC_CLKSOURCE_HSE | (LL_RCC_RTC_HSE_DIV_53 << 16)), /*!< HSE oscillator clock divided by 53 used as RTC clock */
  HAL_RCC_RTC_CLK_SRC_HSE_DIV54 = (LL_RCC_RTC_CLKSOURCE_HSE | (LL_RCC_RTC_HSE_DIV_54 << 16)), /*!< HSE oscillator clock divided by 54 used as RTC clock */
  HAL_RCC_RTC_CLK_SRC_HSE_DIV55 = (LL_RCC_RTC_CLKSOURCE_HSE | (LL_RCC_RTC_HSE_DIV_55 << 16)), /*!< HSE oscillator clock divided by 55 used as RTC clock */
  HAL_RCC_RTC_CLK_SRC_HSE_DIV56 = (LL_RCC_RTC_CLKSOURCE_HSE | (LL_RCC_RTC_HSE_DIV_56 << 16)), /*!< HSE oscillator clock divided by 56 used as RTC clock */
  HAL_RCC_RTC_CLK_SRC_HSE_DIV57 = (LL_RCC_RTC_CLKSOURCE_HSE | (LL_RCC_RTC_HSE_DIV_57 << 16)), /*!< HSE oscillator clock divided by 57 used as RTC clock */
  HAL_RCC_RTC_CLK_SRC_HSE_DIV58 = (LL_RCC_RTC_CLKSOURCE_HSE | (LL_RCC_RTC_HSE_DIV_58 << 16)), /*!< HSE oscillator clock divided by 58 used as RTC clock */
  HAL_RCC_RTC_CLK_SRC_HSE_DIV59 = (LL_RCC_RTC_CLKSOURCE_HSE | (LL_RCC_RTC_HSE_DIV_59 << 16)), /*!< HSE oscillator clock divided by 59 used as RTC clock */
  HAL_RCC_RTC_CLK_SRC_HSE_DIV60 = (LL_RCC_RTC_CLKSOURCE_HSE | (LL_RCC_RTC_HSE_DIV_60 << 16)), /*!< HSE oscillator clock divided by 60 used as RTC clock */
  HAL_RCC_RTC_CLK_SRC_HSE_DIV61 = (LL_RCC_RTC_CLKSOURCE_HSE | (LL_RCC_RTC_HSE_DIV_61 << 16)), /*!< HSE oscillator clock divided by 61 used as RTC clock */
  HAL_RCC_RTC_CLK_SRC_HSE_DIV62 = (LL_RCC_RTC_CLKSOURCE_HSE | (LL_RCC_RTC_HSE_DIV_62 << 16)), /*!< HSE oscillator clock divided by 62 used as RTC clock */
  HAL_RCC_RTC_CLK_SRC_HSE_DIV63 = (LL_RCC_RTC_CLKSOURCE_HSE | (LL_RCC_RTC_HSE_DIV_63 << 16)) /*!< HSE oscillator clock divided by 63 used as RTC clock */
} hal_rcc_rtc_clk_src_t;

/**
  * @brief MCOx Clock Source
  */
typedef enum
{
  HAL_RCC_MCO1_SRC_HSI    = LL_RCC_MCO1SOURCE_HSI,    /*!< HSI selection as MCO1 source    */
  HAL_RCC_MCO1_SRC_LSE    = LL_RCC_MCO1SOURCE_LSE,    /*!< LSE selection as MCO1 source    */
  HAL_RCC_MCO1_SRC_HSE    = LL_RCC_MCO1SOURCE_HSE,    /*!< HSE selection as MCO1 source    */
  HAL_RCC_MCO1_SRC_PLL1   = LL_RCC_MCO1SOURCE_PLL1,   /*!< PLL1 selection as MCO1 source   */
  HAL_RCC_MCO1_SRC_HSI48  = LL_RCC_MCO1SOURCE_HSI48,  /*!< HSI48 selection as MCO1 source  */
  HAL_RCC_MCO2_SRC_SYSTEM = LL_RCC_MCO2SOURCE_SYSTEM, /*!< SYSTEM selection as MCO2 source */
  HAL_RCC_MCO2_SRC_PLL2   = LL_RCC_MCO2SOURCE_PLL2,   /*!< PLL2 selection as MCO2 source   */
  HAL_RCC_MCO2_SRC_HSE    = LL_RCC_MCO2SOURCE_HSE,    /*!< HSE selection as MCO2 source    */
  HAL_RCC_MCO2_SRC_PLL1   = LL_RCC_MCO2SOURCE_PLL1,   /*!< PLL1 selection as MCO2 source   */
  HAL_RCC_MCO2_SRC_CSI    = LL_RCC_MCO2SOURCE_CSI,    /*!< CSI selection as MCO2 source    */
  HAL_RCC_MCO2_SRC_LSI    = LL_RCC_MCO2SOURCE_LSI,    /*!< LSI selection as MCO2 source    */
} hal_rcc_mco_src_t;

/**
  * @brief MCOx Clock Prescaler
  */
typedef enum
{
  HAL_RCC_MCO1_PRESCALERDIS = LL_RCC_MCO1_PRESCALER_DIS, /*!< MCO1 divider is disabled */
  HAL_RCC_MCO1_PRESCALER1   = LL_RCC_MCO1_PRESCALER_1,   /*!< MCO1 is not divided      */
  HAL_RCC_MCO1_PRESCALER2   = LL_RCC_MCO1_PRESCALER_2,   /*!< MCO1 is divided by 2     */
  HAL_RCC_MCO1_PRESCALER3   = LL_RCC_MCO1_PRESCALER_3,   /*!< MCO1 is divided by 3     */
  HAL_RCC_MCO1_PRESCALER4   = LL_RCC_MCO1_PRESCALER_4,   /*!< MCO1 is divided by 4     */
  HAL_RCC_MCO1_PRESCALER5   = LL_RCC_MCO1_PRESCALER_5,   /*!< MCO1 is divided by 5     */
  HAL_RCC_MCO1_PRESCALER6   = LL_RCC_MCO1_PRESCALER_6,   /*!< MCO1 is divided by 6     */
  HAL_RCC_MCO1_PRESCALER7   = LL_RCC_MCO1_PRESCALER_7,   /*!< MCO1 is divided by 7     */
  HAL_RCC_MCO1_PRESCALER8   = LL_RCC_MCO1_PRESCALER_8,   /*!< MCO1 is divided by 8     */
  HAL_RCC_MCO1_PRESCALER9   = LL_RCC_MCO1_PRESCALER_9,   /*!< MCO1 is divided by 9     */
  HAL_RCC_MCO1_PRESCALER10  = LL_RCC_MCO1_PRESCALER_10,  /*!< MCO1 is divided by 10    */
  HAL_RCC_MCO1_PRESCALER11  = LL_RCC_MCO1_PRESCALER_11,  /*!< MCO1 is divided by 11    */
  HAL_RCC_MCO1_PRESCALER12  = LL_RCC_MCO1_PRESCALER_12,  /*!< MCO1 is divided by 12    */
  HAL_RCC_MCO1_PRESCALER13  = LL_RCC_MCO1_PRESCALER_13,  /*!< MCO1 is divided by 13    */
  HAL_RCC_MCO1_PRESCALER14  = LL_RCC_MCO1_PRESCALER_14,  /*!< MCO1 is divided by 14    */
  HAL_RCC_MCO1_PRESCALER15  = LL_RCC_MCO1_PRESCALER_15,  /*!< MCO1 is divided by 15    */
  HAL_RCC_MCO2_PRESCALERDIS = LL_RCC_MCO2_PRESCALER_DIS, /*!< MCO2 divider is disabled */
  HAL_RCC_MCO2_PRESCALER1   = LL_RCC_MCO2_PRESCALER_1,   /*!< MCO2 is not divided      */
  HAL_RCC_MCO2_PRESCALER2   = LL_RCC_MCO2_PRESCALER_2,   /*!< MCO2 is divided by 2     */
  HAL_RCC_MCO2_PRESCALER3   = LL_RCC_MCO2_PRESCALER_3,   /*!< MCO2 is divided by 3     */
  HAL_RCC_MCO2_PRESCALER4   = LL_RCC_MCO2_PRESCALER_4,   /*!< MCO2 is divided by 4     */
  HAL_RCC_MCO2_PRESCALER5   = LL_RCC_MCO2_PRESCALER_5,   /*!< MCO2 is divided by 5     */
  HAL_RCC_MCO2_PRESCALER6   = LL_RCC_MCO2_PRESCALER_6,   /*!< MCO2 is divided by 6     */
  HAL_RCC_MCO2_PRESCALER7   = LL_RCC_MCO2_PRESCALER_7,   /*!< MCO2 is divided by 7     */
  HAL_RCC_MCO2_PRESCALER8   = LL_RCC_MCO2_PRESCALER_8,   /*!< MCO2 is divided by 8     */
  HAL_RCC_MCO2_PRESCALER9   = LL_RCC_MCO2_PRESCALER_9,   /*!< MCO2 is divided by 9     */
  HAL_RCC_MCO2_PRESCALER10  = LL_RCC_MCO2_PRESCALER_10,  /*!< MCO2 is divided by 10    */
  HAL_RCC_MCO2_PRESCALER11  = LL_RCC_MCO2_PRESCALER_11,  /*!< MCO2 is divided by 11    */
  HAL_RCC_MCO2_PRESCALER12  = LL_RCC_MCO2_PRESCALER_12,  /*!< MCO2 is divided by 12    */
  HAL_RCC_MCO2_PRESCALER13  = LL_RCC_MCO2_PRESCALER_13,  /*!< MCO2 is divided by 13    */
  HAL_RCC_MCO2_PRESCALER14  = LL_RCC_MCO2_PRESCALER_14,  /*!< MCO2 is divided by 14    */
  HAL_RCC_MCO2_PRESCALER15  = LL_RCC_MCO2_PRESCALER_15,  /*!< MCO2 is divided by 15    */
} hal_rcc_mco_prescaler_t;

/**
  * @brief PLL activation status
  */
typedef enum
{
  HAL_RCC_PLL_DISABLED = 0,
  HAL_RCC_PLL_ENABLED = ! HAL_RCC_PLL_DISABLED
} hal_rcc_pll_status_t;

/**
  * @brief RCC PLLx Clock Source
  */
typedef enum
{
  HAL_RCC_PLL_SRC_HSI  = LL_RCC_PLLSOURCE_HSI, /*!< HSI clock selected as PLLx entry clock source  */
  HAL_RCC_PLL_SRC_CSI  = LL_RCC_PLLSOURCE_CSI, /*!< CSI clock selected as PLLx entry clock source  */
  HAL_RCC_PLL_SRC_HSE  = LL_RCC_PLLSOURCE_HSE, /*!< HSE clock selected as PLLx entry clock source  */
  HAL_RCC_PLL_SRC_NONE = LL_RCC_PLLSOURCE_NONE /*!< NONE clock selected as PLLx entry clock source */
} hal_rcc_pll_src_t;

/**
  * @brief RCC PLL Spread-spectrum status
  */
typedef enum
{
  HAL_RCC_PLL_SSCG_DISABLE = 0U,
  HAL_RCC_PLL_SSCG_ENABLE  = ! HAL_RCC_PLL_SSCG_DISABLE
} hal_rcc_sscg_status_t;

/**
  * @brief RCC PLL Spread-spectrum Modulation spread Config
  */
typedef enum
{
  HAL_RCC_PLL_SSCG_SPREAD_CENTER = LL_RCC_PLL_SPREAD_CENTER, /*!< PLL center spread spectrum selection */
  HAL_RCC_PLL_SSCG_SPREAD_DOWN   = LL_RCC_PLL_SPREAD_DOWN,   /*!< PLL down spread spectrum selection   */
} hal_rcc_pll_sscg_mod_spread_t;

/**
  * @brief RCC PLL Spread-spectrum Dithering Config
  */
typedef enum
{
  HAL_RCC_PLL_SSCG_DITH_NO        = (RCC_PLL1SSCGR_RPDFNDIS | RCC_PLL1SSCGR_TPDFNDIS), /*!< Dithering noise control for PLL not enabled         */
  HAL_RCC_PLL_SSCG_DITH_RPDF      = RCC_PLL1SSCGR_RPDFNDIS,                            /*!< Dithering RPDF noise control for PLL enabled        */
  HAL_RCC_PLL_SSCG_DITH_TPDF      = RCC_PLL1SSCGR_TPDFNDIS,                            /*!< Dithering TPDF noise control for PLL enabled        */
  HAL_RCC_PLL_SSCG_DITH_RPDF_TPDF = 0U,                                                /*!< Dithering PRDF & TPDF noise control for PLL enabled */
} hal_rcc_pll_sscg_dith_ctrl_t;

/** @defgroup RCC_PLL1_Clock_Output RCC PLL1 Clock Output
  * @{
  */
#define HAL_RCC_PLL1_OUTPUT_P   LL_RCC_PLL1_OUTPUT_P                                                 /*!< Output used by XXX             */
#define HAL_RCC_PLL1_OUTPUT_Q   LL_RCC_PLL1_OUTPUT_Q                                                 /*!< Output used by XXX             */
#define HAL_RCC_PLL1_OUTPUT_S   LL_RCC_PLL1_OUTPUT_S                                                 /*!< Output used by XXX             */
#define HAL_RCC_PLL1_OUTPUT_ALL (LL_RCC_PLL1_OUTPUT_P | LL_RCC_PLL1_OUTPUT_Q | LL_RCC_PLL1_OUTPUT_S) /*!< All PLL1 outputs               */
#define HAL_RCC_PLL1_SYSCLK     HAL_RCC_PLL1_OUTPUT_P                                              /*!< Define used for legacy purpose */
/**
  * @}
  */ /* End of RCC_PLL1_Clock_Output */

/** @defgroup RCC_PLL2_Clock_Output RCC PLL2 Clock Output
  * @{
  */
#define HAL_RCC_PLL2_OUTPUT_P LL_RCC_PLL2_OUTPUT_P /*!< Output used by XXX */
#define HAL_RCC_PLL2_OUTPUT_Q LL_RCC_PLL2_OUTPUT_Q /*!< Output used by XXX */
#define HAL_RCC_PLL2_OUTPUT_R LL_RCC_PLL2_OUTPUT_R /*!< Output used by XXX */
#define HAL_RCC_PLL2_OUTPUT_S LL_RCC_PLL2_OUTPUT_S /*!< Output used by XXX */
#define HAL_RCC_PLL2_OUTPUT_T LL_RCC_PLL2_OUTPUT_T /*!< Output used by XXX */

#define HAL_RCC_PLL2_OUTPUT_ALL (LL_RCC_PLL2_OUTPUT_P | LL_RCC_PLL2_OUTPUT_Q | LL_RCC_PLL2_OUTPUT_R | \
                                 LL_RCC_PLL2_OUTPUT_S | LL_RCC_PLL2_OUTPUT_T) /*! All PLL2 outputs */
/**
  * @}
  */ /* End of RCC_PLL2_Clock_Output */


/** @defgroup RCC_PLL3_Clock_Output RCC PLL3 Clock Output
  * @{
  */
#define HAL_RCC_PLL3_OUTPUT_P LL_RCC_PLL3_OUTPUT_P /*!< Output used by XXX */
#define HAL_RCC_PLL3_OUTPUT_Q LL_RCC_PLL3_OUTPUT_Q /*!< Output used by XXX */
#define HAL_RCC_PLL3_OUTPUT_R LL_RCC_PLL3_OUTPUT_R /*!< Output used by XXX */
#define HAL_RCC_PLL3_OUTPUT_S LL_RCC_PLL3_OUTPUT_S /*!< Output used by XXX */

#define HAL_RCC_PLL3_OUTPUT_ALL (LL_RCC_PLL3_OUTPUT_P | LL_RCC_PLL3_OUTPUT_Q | LL_RCC_PLL3_OUTPUT_R | \
                                 LL_RCC_PLL3_OUTPUT_S) /*! All PLL3 outputs */
/**
  * @}
  */ /* End of RCC_PLL3_Clock_Output */

/** @defgroup RCC_Reset_Flag Reset Flag
  * @{
  */
#define HAL_RCC_RESET_FLAG_OBL  RCC_RSR_OBLRSTF  /*!< Option byte loading reset flag            */
#define HAL_RCC_RESET_FLAG_BOR  RCC_RSR_BORRSTF  /*!< BOR reset flag                            */
#define HAL_RCC_RESET_FLAG_PIN  RCC_RSR_PINRSTF  /*!< pin reset flag                            */
#define HAL_RCC_RESET_FLAG_POR  RCC_RSR_PORRSTF  /*!< POR/PDR reset flag                        */
#define HAL_RCC_RESET_FLAG_SFT  RCC_RSR_SFTRSTF  /*!< system reset from CPU reset flag          */
#define HAL_RCC_RESET_FLAG_IWDG RCC_RSR_IWDGRSTF /*!< independent watchdog reset flag           */
#define HAL_RCC_RESET_FLAG_WWDG RCC_RSR_WWDGRSTF /*!< window watchdog reset flag                */
#define HAL_RCC_RESET_FLAG_LPWR RCC_RSR_LPWRRSTF /*!< reset due to illegal Stop or Standby flag */

#define HAL_RCC_RESET_FLAG_ALL  (HAL_RCC_RESET_FLAG_OBL | HAL_RCC_RESET_FLAG_BOR | HAL_RCC_RESET_FLAG_PIN | \
                                 HAL_RCC_RESET_FLAG_POR | HAL_RCC_RESET_FLAG_SFT | HAL_RCC_RESET_FLAG_IWDG | \
                                 HAL_RCC_RESET_FLAG_WWDG | HAL_RCC_RESET_FLAG_LPWR ) /*!< Reset all the RCC flags */

/**
  * @}
  */ /* End of RCC_Reset_Flag */

/** @defgroup RCC_Periph_Clock_Source Peripheral clock source
  * @{
  */

/**
  * @brief FMC Clock Source
  */
typedef enum
{
  HAL_RCC_FMC_CLK_SRC_HCLK5 = LL_RCC_FMC_CLKSOURCE_HCLK5, /*!< HCLK5 selected as FMC kernel clock */
  HAL_RCC_FMC_CLK_SRC_PLL1Q = LL_RCC_FMC_CLKSOURCE_PLL1Q, /*!< PLL1Q selected as FMC kernel clock */
  HAL_RCC_FMC_CLK_SRC_PLL2R = LL_RCC_FMC_CLKSOURCE_PLL2R, /*!< PLL2R selected as FMC kernel clock */
  HAL_RCC_FMC_CLK_SRC_HSI   = LL_RCC_FMC_CLKSOURCE_HSI    /*!< HSI selected as FMC kernel clock   */
} hal_rcc_fmc_clk_src_t;

/**
  * @brief SDMMC1 Clock Source
  */
typedef enum
{
  HAL_RCC_SDMMC1_CLK_SRC_PLL2S = LL_RCC_SDMMC1_CLKSOURCE_PLL2S, /*!< PLL2S selected as SDMMC1 kernel clock */
  HAL_RCC_SDMMC1_CLK_SRC_PLL2T = LL_RCC_SDMMC1_CLKSOURCE_PLL2T  /*!< PLL2T selected as SDMMC1 kernel clock */
} hal_rcc_sdmmc1_clk_src_t;

/**
  * @brief XSPI1 Clock Source
  */
typedef enum
{
  HAL_RCC_XSPI1_CLK_SRC_HCLK5 = LL_RCC_XSPI1_CLKSOURCE_HCLK5, /*!< HCLK5 selected as XSPI1 kernel clock */
  HAL_RCC_XSPI1_CLK_SRC_PLL2S = LL_RCC_XSPI1_CLKSOURCE_PLL2S, /*!< PLL2S selected as XSPI1 kernel clock */
  HAL_RCC_XSPI1_CLK_SRC_PLL2T = LL_RCC_XSPI1_CLKSOURCE_PLL2T  /*!< PLL2T selected as XSPI1 kernel clock */
} hal_rcc_xspi1_clk_src_t;

/**
  * @brief OTGFS Clock Source
  */
typedef enum
{
  HAL_RCC_OTGFS_CLK_SRC_HSI48     = LL_RCC_OTGFS_CLKSOURCE_HSI48,     /*!< HSI48 selected as OTGFS kernel clock     */
  HAL_RCC_OTGFS_CLK_SRC_PLL3Q     = LL_RCC_OTGFS_CLKSOURCE_PLL3Q,     /*!< PLL3Q selected as OTGFS kernel clock     */
  HAL_RCC_OTGFS_CLK_SRC_HSE       = LL_RCC_OTGFS_CLKSOURCE_HSE,       /*!< HSE selected as OTGFS kernel clock       */
  HAL_RCC_OTGFS_CLK_SRC_CLK48MOHC = LL_RCC_OTGFS_CLKSOURCE_CLK48MOHC  /*!< CLK48MOHC selected as OTGFS kernel clock */
} hal_rcc_otgfs_clk_src_t;

/**
  * @brief ADF1 Clock Source
  */
typedef enum
{
  HAL_RCC_ADF1_CLK_SRC_HCLK1 = LL_RCC_ADF1_CLKSOURCE_HCLK1, /*!< HCLK1 selected as ADF1 kernel clock */
  HAL_RCC_ADF1_CLK_SRC_PLL2P = LL_RCC_ADF1_CLKSOURCE_PLL2P, /*!< PLL2P selected as ADF1 kernel clock */
  HAL_RCC_ADF1_CLK_SRC_PLL3P = LL_RCC_ADF1_CLKSOURCE_PLL3P, /*!< PLL2P selected as ADF1 kernel clock */
  HAL_RCC_ADF1_CLK_SRC_PIN   = LL_RCC_ADF1_CLKSOURCE_PIN,   /*!< PLL2P selected as ADF1 kernel clock */
  HAL_RCC_ADF1_CLK_SRC_CSI   = LL_RCC_ADF1_CLKSOURCE_CSI,   /*!< PLL2P selected as ADF1 kernel clock */
  HAL_RCC_ADF1_CLK_SRC_HSI   = LL_RCC_ADF1_CLKSOURCE_HSI    /*!< PLL2P selected as ADF1 kernel clock */
} hal_rcc_adf1_clk_src_t;

/**
  * @brief ADC Clock Source
  */
typedef enum
{
  HAL_RCC_ADC_CLK_SRC_HCLK3 = LL_RCC_ADC_CLKSOURCE_HCLK3, /*!< HCLK3 selected as ADC kernel clock */
  HAL_RCC_ADC_CLK_SRC_TIMX  = LL_RCC_ADC_CLKSOURCE_TIMX,  /*!< TIMX selected as ADC kernel clock  */
  HAL_RCC_ADC_CLK_SRC_HSI   = LL_RCC_ADC_CLKSOURCE_HSI,   /*!< HSI selected as ADC kernel clock  */
  HAL_RCC_ADC_CLK_SRC_HSE   = LL_RCC_ADC_CLKSOURCE_HSE,   /*!< HSE selected as ADC kernel clock  */
  HAL_RCC_ADC_CLK_SRC_PLL2P = LL_RCC_ADC_CLKSOURCE_PLL2P, /*!< PLL2P selected as ADC kernel clock  */
  HAL_RCC_ADC_CLK_SRC_PLL3R = LL_RCC_ADC_CLKSOURCE_PLL3R, /*!< PLL3R selected as ADC kernel clock  */
  HAL_RCC_ADC_CLK_SRC_PER   = LL_RCC_ADC_CLKSOURCE_PER    /*!< PER selected as ADC kernel clock  */
} hal_rcc_adc_clk_src_t;

/**
  * @brief CKPER Clock Source
  */
typedef enum
{
  HAL_RCC_CKPER_CLK_SRC_HSI = LL_RCC_CKPER_CLKSOURCE_HSI, /*!< HSI selected as CKPER kernel clock */
  HAL_RCC_CKPER_CLK_SRC_CSI = LL_RCC_CKPER_CLKSOURCE_CSI, /*!< CSI selected as CKPER kernel clock */
  HAL_RCC_CKPER_CLK_SRC_HSE = LL_RCC_CKPER_CLKSOURCE_HSE /*!< HSE selected as CKPER kernel clock */
} hal_rcc_ckper_clk_src_t;

/**
  * @brief UART234578 Clock Source
  */
typedef enum
{
  HAL_RCC_UART234578_CLK_SRC_PCLK1 = LL_RCC_UART234578_CLKSOURCE_PCLK1, /*!< PCLK1 selected as UART234578 kernel clock */
  HAL_RCC_UART234578_CLK_SRC_PLL2Q = LL_RCC_UART234578_CLKSOURCE_PLL2Q, /*!< PLL2Q selected as UART234578 kernel clock */
  HAL_RCC_UART234578_CLK_SRC_PLL3Q = LL_RCC_UART234578_CLKSOURCE_PLL3Q, /*!< PLL3Q selected as UART234578 kernel clock */
  HAL_RCC_UART234578_CLK_SRC_HSI   = LL_RCC_UART234578_CLKSOURCE_HSI,   /*!< HSI selected as UART234578 kernel clock   */
  HAL_RCC_UART234578_CLK_SRC_CSI   = LL_RCC_UART234578_CLKSOURCE_CSI,   /*!< CSI selected as UART234578 kernel clock   */
  HAL_RCC_UART234578_CLK_SRC_LSE   = LL_RCC_UART234578_CLKSOURCE_LSE    /*!< LSE selected as UART234578 kernel clock   */
} hal_rcc_uart234578_clk_src_t;

/**
  * @brief SPI23 Clock Source
  */
typedef enum
{
  HAL_RCC_SPI23_CLK_SRC_PLL1Q    = LL_RCC_SPI23_CLKSOURCE_PLL1Q,    /*!< PLL1Q selected as SPI23 kernel clock    */
  HAL_RCC_SPI23_CLK_SRC_PLL2P    = LL_RCC_SPI23_CLKSOURCE_PLL2P,    /*!< PLL2P selected as SPI23 kernel clock    */
  HAL_RCC_SPI23_CLK_SRC_PLL3P    = LL_RCC_SPI23_CLKSOURCE_PLL3P,    /*!< PLL3P selected as SPI23 kernel clock    */
  HAL_RCC_SPI23_CLK_SRC_AUDIOCLK = LL_RCC_SPI23_CLKSOURCE_AUDIOCLK, /*!< AUDIOCLK selected as SPI23 kernel clock */
  HAL_RCC_SPI23_CLK_SRC_PER      = LL_RCC_SPI23_CLKSOURCE_PER       /*!< PER selected as SPI23 kernel clock      */
} hal_rcc_spi23_clk_src_t;

/**
  * @brief I2C123 Clock Source
  */
typedef enum
{
  HAL_RCC_I2C123_CLK_SRC_PCLK1 = LL_RCC_I2C123_CLKSOURCE_PCLK1,  /*!< PCLK1 selected as I2C123 kernel clock */
  HAL_RCC_I2C123_CLK_SRC_PLL3R = LL_RCC_I2C123_CLKSOURCE_PLL3R,  /*!< PLL3R selected as I2C123 kernel clock */
  HAL_RCC_I2C123_CLK_SRC_HSI   = LL_RCC_I2C123_CLKSOURCE_HSI,    /*!< HSI selected as I2C123 kernel clock   */
  HAL_RCC_I2C123_CLK_SRC_CSI   = LL_RCC_I2C123_CLKSOURCE_CSI     /*!< CSI selected as I2C123 kernel clock   */
} hal_rcc_i2c123_clk_src_t;

/**
  * @brief I3C1 Clock Source
  */
typedef enum
{
  HAL_RCC_I3C1_CLK_SRC_PCLK1 = LL_RCC_I3C1_CLKSOURCE_PCLK1, /*!< PCLK1 selected as I3C1 kernel clock */
  HAL_RCC_I3C1_CLK_SRC_PLL3R = LL_RCC_I3C1_CLKSOURCE_PLL3R, /*!< PLL3R selected as I3C1 kernel clock */
  HAL_RCC_I3C1_CLK_SRC_HSI   = LL_RCC_I3C1_CLKSOURCE_HSI,   /*!< HSI selected as I3C1 kernel clock   */
  HAL_RCC_I3C1_CLK_SRC_CSI   = LL_RCC_I3C1_CLKSOURCE_CSI    /*!< CSI selected as I3C1 kernel clock   */
} hal_rcc_i3c1_clk_src_t;

/**
  * @brief LPTIM1 Clock Source
  */
typedef enum
{
  HAL_RCC_LPTIM1_CLK_SRC_PCLK1 = LL_RCC_LPTIM1_CLKSOURCE_PCLK1, /*!< PCLK1 selected as LPTIM1 kernel clock */
  HAL_RCC_LPTIM1_CLK_SRC_PLL2P = LL_RCC_LPTIM1_CLKSOURCE_PLL2P, /*!< PLL2P selected as LPTIM1 kernel clock */
  HAL_RCC_LPTIM1_CLK_SRC_PLL3R = LL_RCC_LPTIM1_CLKSOURCE_PLL3R, /*!< PLL3R selected as LPTIM1 kernel clock */
  HAL_RCC_LPTIM1_CLK_SRC_LSE   = LL_RCC_LPTIM1_CLKSOURCE_LSE,   /*!< LSE selected as LPTIM1 kernel clock   */
  HAL_RCC_LPTIM1_CLK_SRC_LSI   = LL_RCC_LPTIM1_CLKSOURCE_LSI,   /*!< LSI selected as LPTIM1 kernel clock   */
  HAL_RCC_LPTIM1_CLK_SRC_PER   = LL_RCC_LPTIM1_CLKSOURCE_PER    /*!< PER selected as LPTIM1 kernel clock   */
} hal_rcc_lptim1_clk_src_t;

/**
  * @brief FDCAN Clock Source
  */
typedef enum
{
  HAL_RCC_FDCAN_CLK_SRC_HSE   = LL_RCC_FDCAN_CLKSOURCE_HSE,   /*!< HSE selected as FDCAN kernel clock   */
  HAL_RCC_FDCAN_CLK_SRC_PLL1Q = LL_RCC_FDCAN_CLKSOURCE_PLL1Q, /*!< PLL1Q selected as FDCAN kernel clock */
  HAL_RCC_FDCAN_CLK_SRC_PLL2P = LL_RCC_FDCAN_CLKSOURCE_PLL2P, /*!< PLL2P selected as FDCAN kernel clock */
} hal_rcc_fdcan_clk_src_t;

/**
  * @brief USART16910 Clock Source
  */
typedef enum
{
  HAL_RCC_USART16910_CLK_SRC_PCLK2 = LL_RCC_USART16910_CLKSOURCE_PCLK2, /*!< PCLK2 selected as USART16910 kernel clock */
  HAL_RCC_USART16910_CLK_SRC_PLL2Q = LL_RCC_USART16910_CLKSOURCE_PLL2Q, /*!< PLL2Q selected as USART16910 kernel clock */
  HAL_RCC_USART16910_CLK_SRC_PLL3Q = LL_RCC_USART16910_CLKSOURCE_PLL3Q, /*!< PLL3Q selected as USART16910 kernel clock */
  HAL_RCC_USART16910_CLK_SRC_HSI   = LL_RCC_USART16910_CLKSOURCE_HSI,   /*!< HSI selected as USART16910 kernel clock   */
  HAL_RCC_USART16910_CLK_SRC_CSI   = LL_RCC_USART16910_CLKSOURCE_CSI,   /*!< CSI selected as USART16910 kernel clock   */
  HAL_RCC_USART16910_CLK_SRC_LSE   = LL_RCC_USART16910_CLKSOURCE_LSE    /*!< LSE selected as USART16910 kernel clock   */
} hal_rcc_usart16910_clk_src_t;

/**
  * @brief SPI45 Clock Source
  */
typedef enum
{
  HAL_RCC_SPI45_CLK_SRC_PCLK2 = LL_RCC_SPI45_CLKSOURCE_PCLK2, /*!< PCLK2 selected as SPI45 kernel clock  */
  HAL_RCC_SPI45_CLK_SRC_PLL2Q = LL_RCC_SPI45_CLKSOURCE_PLL2Q, /*!< PLL2_Q selected as SPI45 kernel clock */
  HAL_RCC_SPI45_CLK_SRC_PLL3Q = LL_RCC_SPI45_CLKSOURCE_PLL3Q, /*!< PLL3_Q selected as SPI45 kernel clock */
  HAL_RCC_SPI45_CLK_SRC_HSI   = LL_RCC_SPI45_CLKSOURCE_HSI,   /*!< HSI selected as SPI45 kernel clock    */
  HAL_RCC_SPI45_CLK_SRC_CSI   = LL_RCC_SPI45_CLKSOURCE_CSI,   /*!< CSI selected as SPI45 kernel clock    */
  HAL_RCC_SPI45_CLK_SRC_HSE   = LL_RCC_SPI45_CLKSOURCE_HSE    /*!< HSE selected as SPI45 kernel clock    */
} hal_rcc_spi45_clk_src_t;

/**
  * @brief SPI1 Clock Source
  */
typedef enum
{
  HAL_RCC_SPI1_CLK_SRC_PLL1Q    = LL_RCC_SPI1_CLKSOURCE_PLL1Q,    /*!< PLL1Q selected as SPI1 kernel clock    */
  HAL_RCC_SPI1_CLK_SRC_PLL2P    = LL_RCC_SPI1_CLKSOURCE_PLL2P,    /*!< PLL2P selected as SPI1 kernel clock    */
  HAL_RCC_SPI1_CLK_SRC_PLL3P    = LL_RCC_SPI1_CLKSOURCE_PLL3P,    /*!< PLL3P selected as SPI1 kernel clock    */
  HAL_RCC_SPI1_CLK_SRC_AUDIOCLK = LL_RCC_SPI1_CLKSOURCE_AUDIOCLK, /*!< AUDIOCLK selected as SPI1 kernel clock */
  HAL_RCC_SPI1_CLK_SRC_PER      = LL_RCC_SPI1_CLKSOURCE_PER       /*!< PER selected as SPI1 kernel clock      */
} hal_rcc_spi1_clk_src_t;

/**
  * @brief LPUART1 Clock Source
  */
typedef enum
{
  HAL_RCC_LPUART1_CLK_SRC_PCLK4 = LL_RCC_LPUART1_CLKSOURCE_PCLK4, /*!< PCLK4 selected as LPUART1 kernel clock  */
  HAL_RCC_LPUART1_CLK_SRC_PLL2Q = LL_RCC_LPUART1_CLKSOURCE_PLL2Q, /*!< PLL2_Q selected as LPUART1 kernel clock */
  HAL_RCC_LPUART1_CLK_SRC_PLL3Q = LL_RCC_LPUART1_CLKSOURCE_PLL3Q, /*!< PLL3_Q selected as LPUART1 kernel clock */
  HAL_RCC_LPUART1_CLK_SRC_HSI   = LL_RCC_LPUART1_CLKSOURCE_HSI,   /*!< HSI selected as LPUART1 kernel clock    */
  HAL_RCC_LPUART1_CLK_SRC_CSI   = LL_RCC_LPUART1_CLKSOURCE_CSI,   /*!< CSI selected as LPUART1 kernel clock    */
  HAL_RCC_LPUART1_CLK_SRC_LSE   = LL_RCC_LPUART1_CLKSOURCE_LSE    /*!< LSE selected as LPUART1 kernel clock    */
} hal_rcc_lpuart1_clk_src_t;

/**
  * @brief SPI6 Clock Source
  */
typedef enum
{
  HAL_RCC_SPI6_CLK_SRC_PCLK4 = LL_RCC_SPI6_CLKSOURCE_PCLK4, /*!< PCLK4 selected as SPI6 kernel clock */
  HAL_RCC_SPI6_CLK_SRC_PLL2Q = LL_RCC_SPI6_CLKSOURCE_PLL2Q, /*!< PLL2Q selected as SPI6 kernel clock */
  HAL_RCC_SPI6_CLK_SRC_PLL3Q = LL_RCC_SPI6_CLKSOURCE_PLL3Q, /*!< PLL3Q selected as SPI6 kernel clock */
  HAL_RCC_SPI6_CLK_SRC_HSI   = LL_RCC_SPI6_CLKSOURCE_HSI,   /*!< HSI selected as SPI6 kernel clock   */
  HAL_RCC_SPI6_CLK_SRC_CSI   = LL_RCC_SPI6_CLKSOURCE_CSI,   /*!< CSI selected as SPI6 kernel clock   */
  HAL_RCC_SPI6_CLK_SRC_HSE   = LL_RCC_SPI6_CLKSOURCE_HSE    /*!< HSE selected as SPI6 kernel clock   */
} hal_rcc_spi6_clk_src_t;

/**
  * @brief LPTIM23 Clock Source
  */
typedef enum
{
  HAL_RCC_LPTIM23_CLK_SRC_PCLK4 = LL_RCC_LPTIM23_CLKSOURCE_PCLK4, /*!< PCLK4 selected as LPTIM23 kernel clock */
  HAL_RCC_LPTIM23_CLK_SRC_PLL2P = LL_RCC_LPTIM23_CLKSOURCE_PLL2P, /*!< PLL2P selected as LPTIM23 kernel clock */
  HAL_RCC_LPTIM23_CLK_SRC_PLL3R = LL_RCC_LPTIM23_CLKSOURCE_PLL3R, /*!< PLL3R selected as LPTIM23 kernel clock */
  HAL_RCC_LPTIM23_CLK_SRC_LSE   = LL_RCC_LPTIM23_CLKSOURCE_LSE,   /*!< LSE selected as LPTIM23 kernel clock   */
  HAL_RCC_LPTIM23_CLK_SRC_LSI   = LL_RCC_LPTIM23_CLKSOURCE_LSI,   /*!< LSI selected as LPTIM23 kernel clock   */
  HAL_RCC_LPTIM23_CLK_SRC_PER   = LL_RCC_LPTIM23_CLKSOURCE_PER    /*!< PER selected as LPTIM23 kernel clock   */
} hal_rcc_lptim23_clk_src_t;

/**
  * @brief LPTIM45 Clock Source
  */
typedef enum
{
  HAL_RCC_LPTIM45_CLK_SRC_PCLK4 = LL_RCC_LPTIM45_CLKSOURCE_PCLK4, /*!< PCLK4 selected as LPTIM45 kernel clock */
  HAL_RCC_LPTIM45_CLK_SRC_PLL2P = LL_RCC_LPTIM45_CLKSOURCE_PLL2P, /*!< PLL2P selected as LPTIM45 kernel clock */
  HAL_RCC_LPTIM45_CLK_SRC_PLL3R = LL_RCC_LPTIM45_CLKSOURCE_PLL3R, /*!< PLL3R selected as LPTIM45 kernel clock */
  HAL_RCC_LPTIM45_CLK_SRC_LSE   = LL_RCC_LPTIM45_CLKSOURCE_LSE,   /*!< LSE selected as LPTIM45 kernel clock   */
  HAL_RCC_LPTIM45_CLK_SRC_LSI   = LL_RCC_LPTIM45_CLKSOURCE_LSI,   /*!< LSI selected as LPTIM45 kernel clock   */
  HAL_RCC_LPTIM45_CLK_SRC_PER   = LL_RCC_LPTIM45_CLKSOURCE_PER    /*!< PER selected as LPTIM45 kernel clock   */
} hal_rcc_lptim45_clk_src_t;

/**
  * @brief DAC1 Clock Source
  */
typedef enum
{
  HAL_RCC_DAC1_CLK_SRC_HCLK3 = LL_RCC_DAC1_CLKSOURCE_HCLK3, /*!< HCLK3 selected as DAC1 kernel clock */
  HAL_RCC_DAC1_CLK_SRC_TIM   = LL_RCC_DAC1_CLKSOURCE_TIM,   /*!< TIM selected as DAC1 kernel clock   */
  HAL_RCC_DAC1_CLK_SRC_ADC   = LL_RCC_DAC1_CLKSOURCE_ADC,   /*!< ADC selected as DAC1 kernel clock   */
  HAL_RCC_DAC1_CLK_SRC_HSE   = LL_RCC_DAC1_CLKSOURCE_HSE,   /*!< HSE selected as DAC1 kernel clock   */
  HAL_RCC_DAC1_CLK_SRC_HSI   = LL_RCC_DAC1_CLKSOURCE_HSI,   /*!< HSI selected as DAC1 kernel clock   */
  HAL_RCC_DAC1_CLK_SRC_PLL2P = LL_RCC_DAC1_CLKSOURCE_PLL2P, /*!< PLL2P selected as DAC1 kernel clock */
  HAL_RCC_DAC1_CLK_SRC_PLL3R = LL_RCC_DAC1_CLKSOURCE_PLL3R, /*!< PLL3R selected as DAC1 kernel clock */
  HAL_RCC_DAC1_CLK_SRC_PER   = LL_RCC_DAC1_CLKSOURCE_PER    /*!< PER selected as DAC1 kernel clock   */
} hal_rcc_dac1_clk_src_t;

/**
  * @brief DAC1 sample-and-hold clock source
  */
typedef enum
{
  HAL_RCC_DAC1_SH_CLK_SRC_LSE = LL_RCC_DAC1SH_CLKSOURCE_LSE, /*!< LSE selected as DAC1SH kernel clock */
  HAL_RCC_DAC1_SH_CLK_SRC_LSI = LL_RCC_DAC1SH_CLKSOURCE_LSI  /*!< LSI selected as DAC1SH kernel clock */
} hal_rcc_dac1_sh_clk_src_t;

/**
  * @brief DAC2 Clock Source
  */
typedef enum
{
  HAL_RCC_DAC2_CLK_SRC_HCLK3 = LL_RCC_DAC2_CLKSOURCE_HCLK3, /*!< HCLK3 selected as DAC2 kernel clock */
  HAL_RCC_DAC2_CLK_SRC_TIM   = LL_RCC_DAC2_CLKSOURCE_TIM,   /*!< TIM selected as DAC2 kernel clock   */
  HAL_RCC_DAC2_CLK_SRC_ADC   = LL_RCC_DAC2_CLKSOURCE_ADC,   /*!< ADC selected as DAC2 kernel clock   */
  HAL_RCC_DAC2_CLK_SRC_HSE   = LL_RCC_DAC2_CLKSOURCE_HSE,   /*!< HSE selected as DAC2 kernel clock   */
  HAL_RCC_DAC2_CLK_SRC_HSI   = LL_RCC_DAC2_CLKSOURCE_HSI,   /*!< HSI selected as DAC2 kernel clock   */
  HAL_RCC_DAC2_CLK_SRC_PLL2P = LL_RCC_DAC2_CLKSOURCE_PLL2P, /*!< PLL2P selected as DAC2 kernel clock */
  HAL_RCC_DAC2_CLK_SRC_PLL3R = LL_RCC_DAC2_CLKSOURCE_PLL3R, /*!< PLL3R selected as DAC2 kernel clock */
  HAL_RCC_DAC2_CLK_SRC_PER   = LL_RCC_DAC2_CLKSOURCE_PER    /*!< PER selected as DAC2 kernel clock   */
} hal_rcc_dac2_clk_src_t;

/**
  * @brief DAC3 Clock Source
  */
typedef enum
{
  HAL_RCC_DAC3_CLK_SRC_HCLK3 = LL_RCC_DAC3_CLKSOURCE_HCLK3, /*!< HCLK3 selected as DAC3 kernel clock */
  HAL_RCC_DAC3_CLK_SRC_TIM   = LL_RCC_DAC3_CLKSOURCE_TIM,   /*!< TIM selected as DAC3 kernel clock   */
  HAL_RCC_DAC3_CLK_SRC_ADC   = LL_RCC_DAC3_CLKSOURCE_ADC,   /*!< ADC selected as DAC3 kernel clock   */
  HAL_RCC_DAC3_CLK_SRC_HSE   = LL_RCC_DAC3_CLKSOURCE_HSE,   /*!< HSE selected as DAC3 kernel clock   */
  HAL_RCC_DAC3_CLK_SRC_HSI   = LL_RCC_DAC3_CLKSOURCE_HSI,   /*!< HSI selected as DAC3 kernel clock   */
  HAL_RCC_DAC3_CLK_SRC_PLL2P = LL_RCC_DAC3_CLKSOURCE_PLL2P, /*!< PLL2P selected as DAC3 kernel clock */
  HAL_RCC_DAC3_CLK_SRC_PLL3R = LL_RCC_DAC3_CLKSOURCE_PLL3R, /*!< PLL3R selected as DAC3 kernel clock */
  HAL_RCC_DAC3_CLK_SRC_PER   = LL_RCC_DAC3_CLKSOURCE_PER    /*!< PER selected as DAC3 kernel clock   */
} hal_rcc_dac3_clk_src_t;

/**
  * @brief DAC4 Clock Source
  */
typedef enum
{
  HAL_RCC_DAC4_CLK_SRC_HCLK3 = LL_RCC_DAC4_CLKSOURCE_HCLK3, /*!< HCLK3 selected as DAC4 kernel clock */
  HAL_RCC_DAC4_CLK_SRC_TIM   = LL_RCC_DAC4_CLKSOURCE_TIM,   /*!< TIM selected as DAC4 kernel clock   */
  HAL_RCC_DAC4_CLK_SRC_ADC   = LL_RCC_DAC4_CLKSOURCE_ADC,   /*!< ADC selected as DAC4 kernel clock   */
  HAL_RCC_DAC4_CLK_SRC_HSE   = LL_RCC_DAC4_CLKSOURCE_HSE,   /*!< HSE selected as DAC4 kernel clock   */
  HAL_RCC_DAC4_CLK_SRC_HSI   = LL_RCC_DAC4_CLKSOURCE_HSI,   /*!< HSI selected as DAC4 kernel clock   */
  HAL_RCC_DAC4_CLK_SRC_PLL2P = LL_RCC_DAC4_CLKSOURCE_PLL2P, /*!< PLL2P selected as DAC4 kernel clock */
  HAL_RCC_DAC4_CLK_SRC_PLL3R = LL_RCC_DAC4_CLKSOURCE_PLL3R, /*!< PLL3R selected as DAC4 kernel clock */
  HAL_RCC_DAC4_CLK_SRC_PER   = LL_RCC_DAC4_CLKSOURCE_PER    /*!< PER selected as DAC4 kernel clock   */
} hal_rcc_dac4_clk_src_t;

/**
  * @}
  */ /* End of RCC_Periph_Clock_Source */

/**
  * @}
  */ /* End of RCC_Exported_Constants */

/* Exported types ------------------------------------------------------------*/

/** @defgroup RCC_Exported_Types RCC Exported Types
  * @{
  */

/**
  * @brief RCC PLL Spread-Spectrum Modulation configuration structure definition
  */
typedef struct
{
  uint32_t mod_period; /*!< MODPER: PLL SSCG Modulation period. This parameter is calculated based on Fref clock and frequency modulation (FMOD). The value multiplied by INC_STEP must be lower than (2^13-1). */
  uint32_t mod_depth_adj; /*!< INCSTEP: PLL SSCG Modulation depth adjustment. This parameter is calculated based on DIVN, modulation depth (MD) and MOD_PER. The value multiplied by MOD_PER must be lower than (2^15-1). */
  hal_rcc_pll_sscg_mod_spread_t  mod_spread;    /*!< SPREADSEL: PLL SSCG Modulation spread, this can be one of the values defined in hal_rcc_pll_sscg_mod_spread_t */
  hal_rcc_pll_sscg_dith_ctrl_t   dith_control;  /*!< PLL SSCG dithering noise control config, this can be one of the values defined in hal_rcc_pll_sscg_dith_ctrl_t */
} hal_rcc_pll_sscg_config_t;

/**
  * @brief RCC PLL configuration structure definition
  * @note  VCO range is being calculated automatically in PLL configurations functions.
  */
typedef struct
{
  uint16_t pll_n; /*!< PLLN: Multiplication factor for PLL VCO output clock.
                            This parameter must be a number between Min_Data = 4 and Max_Data = 512   */

  uint16_t pll_fracn; /*!< PLLFRACN: Specifies Fractional Part Of The Multiplication Factor for
                            PLL1 VCO It must be a value between 0 and 32767                         */

  uint8_t pll_m; /*!< PLLM: Division factor for PLL VCO input clock.
                            This parameter must be a number between Min_Data = 0 and Max_Data = 63  */
  uint8_t pll_p; /*!< PLLP: Division factor for peripheral clocks.
                            This parameter must be a number between Min_Data = 1 and Max_Data = 2   */
  uint8_t pll_q; /*!< PLLQ: Division factor for peripheral clocks.
                            This parameter must be a number between Min_Data = 1 and Max_Data = 2   */
  uint8_t pll_s; /*!< PLLS: Division factor for peripheral clocks.
                            This parameter must be a number between Min_Data = 1 and Max_Data = 2   */
  uint8_t pll_r; /*!< PLLR: Division factor for peripheral clocks.
                            This parameter must be a number between Min_Data = 1 and Max_Data = 2   */
  uint8_t pll_t; /*!< PLLT: Division factor for peripheral clocks.
                            This parameter must be a number between Min_Data = 1 and Max_Data = 2   */

  hal_rcc_pll_src_t pll_source; /*!< RCC_PLLSource: PLL entry clock source                          */

  hal_rcc_sscg_status_t pll_sscg_status;     /*!< pll_sscg_status: PLL sscg mode status (enabled or disabled) */

  hal_rcc_pll_sscg_config_t pll_sscg_config;    /*!< RCC_SSCG: PLL Spread-Spectrum Modulation config  */

} hal_rcc_pll_config_t;

/**
  * @brief  RCC PLL Clocks structure definition
  */
typedef struct
{
  uint32_t pll_p_freq; /*!< PLLx outputP frequency */
  uint32_t pll_q_freq; /*!< PLLx outputQ frequency */
  uint32_t pll_s_freq; /*!< PLLx outputS frequency */
  uint32_t pll_r_freq; /*!< PLLx outputR frequency */
  uint32_t pll_t_freq; /*!< PLLx outputT frequency */
} hal_rcc_pll_output_freq_t;


/**
  * @brief  RCC System, AHB and APB busses clock configuration structure definition
  */
typedef struct
{
  hal_rcc_sys_cpu_clk_prescaler_t sys_cpu_clk_prescaler; /*!< The system clock divider for CPU clock and all bus matrix clocks */

  hal_rcc_hclk_prescaler_t hclk_prescaler; /*!< The AHB clock (HCLK) divider. This clock is derived from the system clock (SYSCLK). */

  hal_rcc_pclk_prescaler_t pclk1_prescaler; /*!< The APB1 clock (PCLK1) divider. This clock is derived from the AHB clock (HCLK). */

  hal_rcc_pclk_prescaler_t pclk2_prescaler; /*!< The APB2 clock (PCLK2) divider. This clock is derived from the AHB clock (HCLK). */

  hal_rcc_pclk_prescaler_t pclk4_prescaler; /*!< The APB4 clock (PCLK4) divider. This clock is derived from the AHB clock (HCLK). */
} hal_rcc_bus_clk_config_t;
/**
  * @}
  */ /* End of RCC_Exported_Types */

/* Exported macros -----------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/

/** @defgroup RCC_Exported_Functions RCC Exported Functions
  * @{
  */

/** @defgroup RCC_Exported_Functions_Group1 Oscillators, PLLs, bus configurations and system clock reset functions
  This section provides functions allowing to configure the internal and external oscillators
  (HSE, LSE, HSI, HSI48, CSI, LSI, PLL), CSS, MCO and the System busses clocks (SYSCLK, AHB, APB1, APB2, APB4, ).

  - Internal/external clock and PLL configuration:HSE

    - HSE (): xxxMhz ...LSE

    - LSE (): xxxMhz ...HSI

    - HSI (): xxxMhz ...HSI48

    - HSI48 (): xxxMhz ...CSI

    - CSI (): xxxMhz ...LSI,

    - LSI (): xxxMhz ...

    - PLL1 providing up to XXX independent output clocks:

    - PLL2 providing up to XXX independent output clocks:

    - PLL3 providing up to XXX independent output clocks:

#warning "CLOCK Description to be updated"
    - HSI (High-Speed Internal): 16 MHz factory-trimmed RC used directly or through
    the PLL as System clock source and also used for peripherals as kernel clock.

    - MSIS (Multiple Speed Internal System): MSIS configurable to several ranges, selecting automatically by hw
    corresponding RC and these RC are trimmable.
    The MSIS is used as System clock source or input from different PLLs.

    - MSIK (Multiple Speed Internal Kernel): MSIK configurable to several ranges, selecting automatically by hw
    corresponding RC and these RC are trimmable.
    It can be selected by some peripherals as kernel clock.

    - SW or HW MSI calibration

    - LSI (Low-Speed Internal): 32 kHz (or 250 Hz depending on the LSIPREDIV bit) low consumption RC used as IWDG
    and/or RTC clock source. It can be selected by some peripherals as kernel clock.

    - HSE (High-Speed External): crystal or clock, from 4 to 50 MHz, used directly or
    through the PLL as System clock source. Can be used also optionally as RTC clock source.

    - LSE (low-speed external): 32.768 kHz oscillator used optionally as RTC clock source.

    - PLL1 providing up to three independent output clocks:

      - as main PLL, PLL1, that is generally used to provide clocks to the CPU and to some
      peripherals

    - PLL2 & PLL3 providing up to three independent output clocks:

      - to generate the kernel clock for peripherals

  - System, AHB and APB busses clocks configuration:

    - Several clock sources can be used to drive the System clock (SYSCLK):

#warning "Description to be updated"
    The AHB clock (HCLK) is derived from System clock through configurable
    prescaler and used to clock the CPU, memory and peripherals mapped
    on AHB bus (DMA, GPIO...). APB1 (PCLK1), APB2 (PCLK2) and APB3 (PCLK3) clocks are derived
    from AHB clock through configurable prescalers and used to clock
    the peripherals mapped on these busses.

    - All the peripheral bus clocks are derived from the System clock (SYSCLK) except:

      - SAI: the SAI clock can be derived either from a specific PLL (PLL2 or PLL3) or
      from an external clock mapped on the SAI_CKIN pin.
      HAL_RCC_PeriphClockConfig() function can be used to configure this clock.
      - RTC: the RTC clock can be derived either from the LSI, LSE or HSE clock
      divided by 2 to 31.
      LL_RCC_EnableRTC() and HAL_RCC_PeriphClockConfig() functions can be used to configure this clock.
      - USB OTG FS, SDMMC1 and RNG: USB OTG FS requires a frequency equal to 48 MHz
      to work correctly, while the SDMMC1 and RNG peripherals require a frequency
      equal or lower than to 48 MHz. This clock is derived of the main PLL or PLL2
      through PLLQ divider. The peripheral clock must be enabled and HAL_RCC_PeriphClockConfig() function
      can be used to configure this clock.
      - IWDG clock which is always the LSI clock.

    - The maximum frequency of the SYSCLK, HCLK, PCLK1, PCLK2 and PCLK3 is 160 MHz.
    To correctly read data from Flash memory, the number of wait states (latency) must be
    correctly programmed in the FLASH register according to the
    frequency of the CPU clock (HCLK) and the internal voltage range of the device VCORE.
    The table below shows the correspondence between wait states and CPU clock frequency.

    Table 1. HCLK clock frequency for devices depending on FLASH latency and voltage range (LPM = 0).

    |   Latency       | range 1<br>1.1V-1.2V| range 2<br>1.0V-1.1V| range 3<br>0.9 V-1.0V| range 4<br>0.9V |
    |-----------------|---------------------|---------------------|----------------------|-----------------|
    |0WS(1 CPU cycles)|  0 < HCLK <= 32     |  0 < HCLK <= 30     |    0 < HCLK <= 24    |  0 < HCLK <= 12 |
    |1WS(2 CPU cycles)| 32 < HCLK <= 64     | 30 < HCLK <= 60     |   24 < HCLK <= 48    | 12 < HCLK <= 25 |
    |2WS(3 CPU cycles)| 64 < HCLK <= 96     | 60 < HCLK <= 90     |   48 < HCLK <= 55    |        -        |
    |3WS(4 CPU cycles)| 96 < HCLK <= 128    | 90 < HCLK <= 110    |         -            |        -        |
    |4WS(5 CPU cycles)|128 < HCLK <= 160    |         -           |         -            |        -        |

    The Flash memory supports a low-power read mode when setting the LPM bit in the FLASH
    register. The table below shows the correspondence between wait states and CPU clock frequency when LPM bit is set.

    Table 2. HCLK clock frequency for devices depending on FLASH latency and voltage range (LPM = 1).

    |   Latency         | range 1/2/3<br>0.9V-1.2V  | range 4<br>0.9V |
    |-------------------|---------------------------|-----------------|
    |0WS(1 CPU cycles)  |                           |  0 < HCLK <= 8  |
    |1WS(2 CPU cycles)  | WS >= HCLK (MHz) / 10 -1   |  8 < HCLK <= 16 |
    |2WS(3 CPU cycles)  |      Maximum HCLK         | 16 < HCLK <= 25 |
    |3WS(4 CPU cycles)  |      frequency is         |        -        |
    |       ...         |    given by Table 1       |        -        |
    |15WS(16 CPU cycles)|                           |        -        |

  - Reset function:

    - Reset the RCC clock configuration to the default system clock (HSI at XXXMhz).
  * @{
  */

/** @defgroup RCC_Exported_Functions_Group1_0 Reset System clock to default function
  * @brief    Functions to reset the system clock to HSI (XXXMhz)
  * @{
  */

void         HAL_RCC_Reset(void);
hal_status_t HAL_RCC_ResetSystemClock(void);

/**
  * @}
  */ /* RCC_Exported_Functions_Group1_0 */

/** @defgroup RCC_Exported_Functions_Group1_1 RCC oscillators config service
  * @brief    Functions to configure the different oscillators and the main PLL
  * @note     The following functions configure and activate the different oscillators.
  *           Configuration can be done:
  *           - using the atomic functions defined for each oscillators and PLL
  *             -# like HAL_RCC_{OSC}_Enable: {OSC} is HSE/LSE/HSI/HSI48/CSI/LSI
  *           - atomic function used for main PLL is described in the @ref RCC_Exported_Functions_Group1_3
  *
  *           example: enable HSE oscillator
  *           - using atomic function (footprint optimisation):
  *             @code
  *             HAL_RCC_HSE_Enable(HAL_RCC_HSE_ON);
  *             @endcode
  * @{
  */

#if defined(HSE_VALUE)
/* HSE oscillator configuration and activation    ******************************/
hal_status_t HAL_RCC_HSE_Enable(hal_rcc_hse_t mode);
hal_status_t HAL_RCC_HSE_Disable(void);
#endif /* HSE_VALUE */

#if defined(LSE_VALUE)
/* LSE oscillator configuration and activation    ******************************/
hal_status_t HAL_RCC_LSE_Enable(hal_rcc_lse_t mode, hal_rcc_lse_drive_t drive);
hal_status_t HAL_RCC_LSE_Disable(void);
#endif /* LSE_VALUE */

/* HSI oscillator configuration and activation    ******************************/
hal_status_t HAL_RCC_HSI_Enable(hal_rcc_hsi_div_t prescaler);
hal_status_t HAL_RCC_HSI_Disable(void);
hal_status_t HAL_RCC_HSI_EnableInStopMode(void);
hal_status_t HAL_RCC_HSI_DisableInStopMode(void);
void HAL_RCC_HSI_SetTrimming(uint32_t value);
uint32_t HAL_RCC_HSI_GetTrimming(void);
uint32_t  HAL_RCC_HSI_GetCalibration(void);
/* HSI48 oscillator configuration and activation    ******************************/
hal_status_t HAL_RCC_HSI48_Enable(void);
hal_status_t HAL_RCC_HSI48_Disable(void);
uint32_t  HAL_RCC_HSI48_GetCalibration(void);
/* CSI oscillator configuration and activation    ******************************/
hal_status_t HAL_RCC_CSI_Enable(void);
hal_status_t HAL_RCC_CSI_Disable(void);
hal_status_t HAL_RCC_CSI_EnableInStopMode(void);
hal_status_t HAL_RCC_CSI_DisableInStopMode(void);
void HAL_RCC_CSI_SetTrimming(uint32_t value);
uint32_t HAL_RCC_CSI_GetTrimming(void);
uint32_t  HAL_RCC_CSI_GetCalibration(void);
/* LSI oscillator configuration and activation    ******************************/
hal_status_t HAL_RCC_LSI_Enable(void);
hal_status_t HAL_RCC_LSI_Disable(void);

/**
  * @}
  */ /* RCC_Exported_Functions_Group1_1 */

/** @defgroup RCC_Exported_Functions_Group1_2 RCC clock config service
  * @brief    Functions to configure the bus prescalers and retrieve bus clock frequencies (SYSCLK, HCLK and PCLKx).
  * @note     Unitary functions can be used to configure independently each bus.
  *
  *           example: all the BUS prescalers are set
  *
  *           - Call the global @ref HAL_RCC_SetBusClockConfig
  *             @code
  *               HAL_FLASH_SetLatency(FLASH_LATENCY_4WS);
  *               HAL_RCC_SetSYSCLKSource(HAL_RCC_SYSCLKSOURCE_PLLCLK);
  *               hal_rcc_bus_clk_config_t config_bus;
  *               config_bus.sys_cpu_clk_prescaler = HAL_RCC_SYSCLK_DIV1;
  *               config_bus.hclk_prescaler = HAL_RCC_HCLK_PRESCALER1;
  *               config_bus.pclk1_prescaler = HAL_RCC_PCLK_PRESCALER1;
  *               config_bus.pclk2_prescaler = HAL_RCC_PCLK_PRESCALER1;
  *               config_bus.pclk4_prescaler = HAL_RCC_PCLK_PRESCALER1;
  *               HAL_RCC_SetBusClockConfig(&config_bus);
  *             @endcode
  * @{
  */
hal_status_t          HAL_RCC_SetSYSCLKSource(hal_rcc_sysclk_src_t source);
hal_rcc_sysclk_src_t  HAL_RCC_GetSYSCLKSource(void);
hal_status_t          HAL_RCC_SetSysClkPrescaler(hal_rcc_sys_cpu_clk_prescaler_t prescaler);
void                  HAL_RCC_SetHCLKPrescaler(hal_rcc_hclk_prescaler_t prescaler);
void                  HAL_RCC_SetPCLK1Prescaler(hal_rcc_pclk_prescaler_t prescaler);
void                  HAL_RCC_SetPCLK2Prescaler(hal_rcc_pclk_prescaler_t prescaler);
void                  HAL_RCC_SetPCLK4Prescaler(hal_rcc_pclk_prescaler_t prescaler);
hal_rcc_sys_cpu_clk_prescaler_t  HAL_RCC_GetSysClkPrescaler(void);
hal_rcc_hclk_prescaler_t    HAL_RCC_GetHCLKPrescaler(void);
hal_rcc_pclk_prescaler_t    HAL_RCC_GetPCLK1Prescaler(void);
hal_rcc_pclk_prescaler_t    HAL_RCC_GetPCLK2Prescaler(void);
hal_rcc_pclk_prescaler_t    HAL_RCC_GetPCLK4Prescaler(void);

hal_status_t          HAL_RCC_SetBusClockConfig(const hal_rcc_bus_clk_config_t *p_config);
void                  HAL_RCC_GetBusClockConfig(hal_rcc_bus_clk_config_t *p_config);
uint32_t              HAL_RCC_GetSYSCLKFreq(void);
uint32_t              HAL_RCC_GetHCLKFreq(void);
uint32_t              HAL_RCC_GetPCLK1Freq(void);
uint32_t              HAL_RCC_GetPCLK2Freq(void);
uint32_t              HAL_RCC_GetPCLK4Freq(void);
uint32_t              HAL_RCC_GetSysTickExternalClkFreq(void);

/**
  * @}
  */ /* RCC_Exported_Functions_Group1_2 */

/** @defgroup RCC_Exported_Functions_Group1_3 RCC management of PLL1
  * @brief    Functions to configure the different PLL1
  * @details  PLL1 (main PLL) might be used for system clock.
  *           PLL1 is configured and enabled respectively with HAL_RCC_PLL1_SetConfig() and HAL_RCC_PLL1_Enable().
  *           The following functions allow to control independently the configuration and activation
  *           for the PLL1.
  *
  *           example1: activation main PLL
  *
  *           - Call the unitary functions:
  *             @code
  *               HAL_RCC_HSI_Enable();
  *               hal_rcc_pll_config_t config_pll;
  *               config_pll.pll_source = HAL_RCC_PLL_SRC_HSI;
  *               config_pll.pll_m = 4;
  *               config_pll.pll_n = 75;
  *               config_pll.pll_p = 2;
  *               config_pll.pll_q = 2;
  *               config_pll.pll_r = 2
  *               HAL_RCC_PLL1_SetConfig(&config_pll);
  *               HAL_RCC_PLL1_Enable();
  *               HAL_RCC_PLL1_EnableOutput(HAL_RCC_PLL1_SYSCLK);
  *             @endcode
  * @{
  */

hal_status_t          HAL_RCC_PLL1_SetConfig(const hal_rcc_pll_config_t *p_config);
hal_status_t          HAL_RCC_PLL1_SetFractional(uint32_t fracn);
hal_status_t          HAL_RCC_PLL1_Enable(void);
hal_status_t          HAL_RCC_PLL1_Disable(void);
hal_status_t          HAL_RCC_PLL1_EnableOutput(uint32_t output);
hal_status_t          HAL_RCC_PLL1_DisableOutput(uint32_t output);
hal_status_t          HAL_RCC_PLL1_Reset(void);
void                  HAL_RCC_PLL1_GetConfig(hal_rcc_pll_config_t *p_config);
uint32_t              HAL_RCC_PLL1_GetOutput(void);
hal_rcc_pll_status_t  HAL_RCC_PLL1_IsReady(void);
void                  HAL_RCC_PLL1_GetClockFreq(hal_rcc_pll_output_freq_t *p_clk);

/**
  * @}
  */ /* RCC_Exported_Functions_Group1_3 */

/** @defgroup RCC_Exported_Functions_Group1_4 RCC management of PLL2
  * @brief    Functions to configure the different PLL2
  * @details  PLL2 (main PLL) might be used for system clock.
  *           PLL2 is configured and enabled respectively with HAL_RCC_PLL2_SetConfig() and HAL_RCC_PLL2_Enable().
  *           The following functions allow to control independently the configuration and activation
  *           for the PLL2.
  *
  *           example1: activation PLL2 only
  *
  *           - Call the unitary functions:
  *             @code
  *               HAL_RCC_HSI_Enable();
  *               hal_rcc_pll_config_t config_pll;
  *               config_pll.pll_source = HAL_RCC_PLL_SRC_HSI;
  *               config_pll.pll_m = 4;
  *               config_pll.pll_n = 75;
  *               config_pll.pll_p = 2;
  *               config_pll.pll_q = 2;
  *               config_pll.pll_r = 2
  *               HAL_RCC_PLL2_SetConfig(&config_pll);
  *               HAL_RCC_PLL2_Enable();
  *               HAL_RCC_PLL2_EnableOutput(HAL_RCC_PLL1_SYSCLK);
  *             @endcode
  * @{
  */

hal_status_t          HAL_RCC_PLL2_SetConfig(const hal_rcc_pll_config_t *p_config);
hal_status_t          HAL_RCC_PLL2_SetFractional(uint32_t fracn);
hal_status_t          HAL_RCC_PLL2_Enable(void);
hal_status_t          HAL_RCC_PLL2_Disable(void);
hal_status_t          HAL_RCC_PLL2_EnableOutput(uint32_t output);
hal_status_t          HAL_RCC_PLL2_DisableOutput(uint32_t output);
hal_status_t          HAL_RCC_PLL2_Reset(void);
void                  HAL_RCC_PLL2_GetConfig(hal_rcc_pll_config_t *p_config);
uint32_t              HAL_RCC_PLL2_GetOutput(void);
hal_rcc_pll_status_t  HAL_RCC_PLL2_IsReady(void);
void                  HAL_RCC_PLL2_GetClockFreq(hal_rcc_pll_output_freq_t *p_clk);

/**
  * @}
  */ /* RCC_Exported_Functions_Group1_4 */

/** @defgroup RCC_Exported_Functions_Group1_5 RCC management of PLL3
  * @brief    Functions to configure the different PLL3
  * @details  PLL3 (main PLL) might be used for system clock.
  *           PLL3 is configured and enabled respectively with HAL_RCC_PLL3_SetConfig() and HAL_RCC_PLL3_Enable().
  *           The following functions allow to control independently the configuration and activation
  *           for the PLL3.
  *
  *           example1: activation PLL3 only
  *
  *           - Call the unitary functions:
  *             @code
  *               HAL_RCC_HSI_Enable();
  *               hal_rcc_pll_config_t config_pll;
  *               config_pll.pll_source = HAL_RCC_PLL_SRC_HSI;
  *               config_pll.pll_m = 4;
  *               config_pll.pll_n = 75;
  *               config_pll.pll_p = 2;
  *               config_pll.pll_q = 2;
  *               config_pll.pll_r = 2
  *               HAL_RCC_PLL3_SetConfig(&config_pll);
  *               HAL_RCC_PLL3_Enable();
  *               HAL_RCC_PLL3_EnableOutput(HAL_RCC_PLL1_SYSCLK);
  *             @endcode
  * @{
  */

hal_status_t          HAL_RCC_PLL3_SetConfig(const hal_rcc_pll_config_t *p_config);
hal_status_t          HAL_RCC_PLL3_SetFractional(uint32_t fracn);
hal_status_t          HAL_RCC_PLL3_Enable(void);
hal_status_t          HAL_RCC_PLL3_Disable(void);
hal_status_t          HAL_RCC_PLL3_EnableOutput(uint32_t output);
hal_status_t          HAL_RCC_PLL3_DisableOutput(uint32_t output);
hal_status_t          HAL_RCC_PLL3_Reset(void);
void                  HAL_RCC_PLL3_GetConfig(hal_rcc_pll_config_t *p_config);
uint32_t              HAL_RCC_PLL3_GetOutput(void);
hal_rcc_pll_status_t  HAL_RCC_PLL3_IsReady(void);
void                  HAL_RCC_PLL3_GetClockFreq(hal_rcc_pll_output_freq_t *p_clk);

/**
  * @}
  */ /* RCC_Exported_Functions_Group1_5 */

/**
  * @}
  */ /* RCC_Exported_Functions_Group1 */

/** @defgroup RCC_Exported_Functions_Group2 Peripheral Clock management on buses
  This subsection provides a set of functions (on AHB1, AHB2, AHB3, AHB4, AHB5, APB1, APB1, APB2, APB4 or CKG buses)
  allowing to:

  - Enable or disable the peripherals clock.
  - Reset of peripherals clock.
  - Enable or disable the peripherals clock in low power mode.
  * @{
  */

/** @defgroup RCC_AHB1_Peripheral_Clock_Enable_Disable AHB1 Peripheral Clock Enable Disable
  * @brief  Enable or disable the AHB1 peripheral clock.
  * @note   After reset, the peripheral clock (used for registers read/write access) is disabled and
  *         the application software has to enable this clock before using it.
  * @{
  */

/**
  * @details This function enables the HSP clock.
  */
__STATIC_INLINE void HAL_RCC_HSP_EnableClock(void)
{
  LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_HSP);
}

/**
  * @details This function enables the GPDMA1 clock.
  */
__STATIC_INLINE void HAL_RCC_GPDMA1_EnableClock(void)
{
  LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPDMA1);
}

/**
  * @details This function enables the OTGFS clock.
  */
__STATIC_INLINE void HAL_RCC_OTGFS_EnableClock(void)
{
  LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_OTGFS);
}

/**
  * @details This function enables the ADF1 clock.
  */
__STATIC_INLINE void HAL_RCC_ADF1_EnableClock(void)
{
  LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_ADF1);
}

/**
  * @details This function disables the HSP clock.
  */
__STATIC_INLINE void HAL_RCC_HSP_DisableClock(void)
{
  LL_AHB1_GRP1_DisableClock(LL_AHB1_GRP1_PERIPH_HSP);
}

/**
  * @details This function disables the GPDMA1 clock.
  */
__STATIC_INLINE void HAL_RCC_GPDMA1_DisableClock(void)
{
  LL_AHB1_GRP1_DisableClock(LL_AHB1_GRP1_PERIPH_GPDMA1);
}

/**
  * @details This function disables the OTGFS clock.
  */
__STATIC_INLINE void HAL_RCC_OTGFS_DisableClock(void)
{
  LL_AHB1_GRP1_DisableClock(LL_AHB1_GRP1_PERIPH_OTGFS);
}

/**
  * @details This function disables the ADF1 clock.
  */
__STATIC_INLINE void HAL_RCC_ADF1_DisableClock(void)
{
  LL_AHB1_GRP1_DisableClock(LL_AHB1_GRP1_PERIPH_ADF1);
}

/**
  * @}
  */ /* RCC_AHB1_Peripheral_Clock_Enable_Disable */

/** @defgroup RCC_AHB2_Peripheral_Clock_Enable_Disable AHB2 Peripheral Clock Enable Disable
  * @brief  Enable or disable the AHB2 peripheral clock.
  * @note   After reset, the peripheral clock (used for registers read/write access) is disabled and
  *         the application software has to enable this clock before using it.
  * @{
  */

/**
  * @details This function enables the CORDIC clock.
  */
__STATIC_INLINE void HAL_RCC_CORDIC_EnableClock(void)
{
  LL_AHB2_GRP1_EnableClock(LL_AHB2_GRP1_PERIPH_CORDIC);
}

/**
  * @details This function enables the FMAC clock.
  */
__STATIC_INLINE void HAL_RCC_FMAC_EnableClock(void)
{
  LL_AHB2_GRP1_EnableClock(LL_AHB2_GRP1_PERIPH_FMAC1);
}

/**
  * @details This function enables the AHBSRAM1 clock.
  */
__STATIC_INLINE void HAL_RCC_AHBSRAM1_EnableClock(void)
{
  LL_AHB2_GRP1_EnableClock(LL_AHB2_GRP1_PERIPH_AHBSRAM1);
}

/**
  * @details This function enables the AHBSRAM2 clock.
  */
__STATIC_INLINE void HAL_RCC_AHBSRAM2_EnableClock(void)
{
  LL_AHB2_GRP1_EnableClock(LL_AHB2_GRP1_PERIPH_AHBSRAM2);
}

/**
  * @details This function enables the AHBSRAM3 clock.
  */
__STATIC_INLINE void HAL_RCC_AHBSRAM3_EnableClock(void)
{
  LL_AHB2_GRP1_EnableClock(LL_AHB2_GRP1_PERIPH_AHBSRAM3);
}

/**
  * @details This function disables the CORDIC clock.
  */
__STATIC_INLINE void HAL_RCC_CORDIC_DisableClock(void)
{
  LL_AHB2_GRP1_DisableClock(LL_AHB2_GRP1_PERIPH_CORDIC);
}

/**
  * @details This function disables the FMAC clock.
  */
__STATIC_INLINE void HAL_RCC_FMAC_DisableClock(void)
{
  LL_AHB2_GRP1_DisableClock(LL_AHB2_GRP1_PERIPH_FMAC1);
}

/**
  * @details This function disables the AHBSRAM1 clock.
  */
__STATIC_INLINE void HAL_RCC_AHBSRAM1_DisableClock(void)
{
  LL_AHB2_GRP1_DisableClock(LL_AHB2_GRP1_PERIPH_AHBSRAM1);
}

/**
  * @details This function disables the AHBSRAM2 clock.
  */
__STATIC_INLINE void HAL_RCC_AHBSRAM2_DisableClock(void)
{
  LL_AHB2_GRP1_DisableClock(LL_AHB2_GRP1_PERIPH_AHBSRAM2);
}

/**
  * @details This function disables the AHBSRAM3 clock.
  */
__STATIC_INLINE void HAL_RCC_AHBSRAM3_DisableClock(void)
{
  LL_AHB2_GRP1_DisableClock(LL_AHB2_GRP1_PERIPH_AHBSRAM3);
}

/**
  * @}
  */ /* RCC_AHB2_Peripheral_Clock_Enable_Disable */

/** @defgroup RCC_AHB3_Peripheral_Clock_Enable_Disable AHB3 Peripheral Clock Enable Disable
  * @brief  Enable or disable the AHB3 peripheral clock.
  * @note   After reset, the peripheral clock (used for registers read/write access) is disabled and
  *         the application software has to enable this clock before using it.
  * @{
  */

/**
  * @details This function enables the RNG clock.
  */
__STATIC_INLINE void HAL_RCC_RNG_EnableClock(void)
{
  LL_AHB3_GRP1_EnableClock(LL_AHB3_GRP1_PERIPH_RNG);
}

/**
  * @details This function enables the HASH clock.
  */
__STATIC_INLINE void HAL_RCC_HASH_EnableClock(void)
{
  LL_AHB3_GRP1_EnableClock(LL_AHB3_GRP1_PERIPH_HASH);
}

/**
  * @details This function enables the ADC12 clock.
  */
__STATIC_INLINE void HAL_RCC_ADC12_EnableClock(void)
{
  LL_AHB3_GRP1_EnableClock(LL_AHB3_GRP1_PERIPH_ADC12);
}

/**
  * @details This function enables the ADC34 clock.
  */
__STATIC_INLINE void HAL_RCC_ADC34_EnableClock(void)
{
  LL_AHB3_GRP1_EnableClock(LL_AHB3_GRP1_PERIPH_ADC34);
}

/**
  * @details This function enables the DAC1 clock.
  */
__STATIC_INLINE void HAL_RCC_DAC1_EnableClock(void)
{
  LL_AHB3_GRP1_EnableClock(LL_AHB3_GRP1_PERIPH_DAC1);
}

/**
  * @details This function enables the DAC2 clock.
  */
__STATIC_INLINE void HAL_RCC_DAC2_EnableClock(void)
{
  LL_AHB3_GRP1_EnableClock(LL_AHB3_GRP1_PERIPH_DAC2);
}

/**
  * @details This function enables the DAC3 clock.
  */
__STATIC_INLINE void HAL_RCC_DAC3_EnableClock(void)
{
  LL_AHB3_GRP1_EnableClock(LL_AHB3_GRP1_PERIPH_DAC3);
}

/**
  * @details This function enables the DAC4 clock.
  */
__STATIC_INLINE void HAL_RCC_DAC4_EnableClock(void)
{
  LL_AHB3_GRP1_EnableClock(LL_AHB3_GRP1_PERIPH_DAC4);
}

/**
  * @details This function disables the RNG clock.
  */
__STATIC_INLINE void HAL_RCC_RNG_DisableClock(void)
{
  LL_AHB3_GRP1_DisableClock(LL_AHB3_GRP1_PERIPH_RNG);
}

/**
  * @details This function disables the HASH clock.
  */
__STATIC_INLINE void HAL_RCC_HASH_DisableClock(void)
{
  LL_AHB3_GRP1_DisableClock(LL_AHB3_GRP1_PERIPH_HASH);
}

/**
  * @details This function disables the ADC12 clock.
  */
__STATIC_INLINE void HAL_RCC_ADC12_DisableClock(void)
{
  LL_AHB3_GRP1_DisableClock(LL_AHB3_GRP1_PERIPH_ADC12);
}

/**
  * @details This function disables the ADC34 clock.
  */
__STATIC_INLINE void HAL_RCC_ADC34_DisableClock(void)
{
  LL_AHB3_GRP1_DisableClock(LL_AHB3_GRP1_PERIPH_ADC34);
}

/**
  * @details This function disables the DAC1 clock.
  */
__STATIC_INLINE void HAL_RCC_DAC1_DisableClock(void)
{
  LL_AHB3_GRP1_DisableClock(LL_AHB3_GRP1_PERIPH_DAC1);
}

/**
  * @details This function disables the DAC2 clock.
  */
__STATIC_INLINE void HAL_RCC_DAC2_DisableClock(void)
{
  LL_AHB3_GRP1_DisableClock(LL_AHB3_GRP1_PERIPH_DAC2);
}

/**
  * @details This function disables the DAC3 clock.
  */
__STATIC_INLINE void HAL_RCC_DAC3_DisableClock(void)
{
  LL_AHB3_GRP1_DisableClock(LL_AHB3_GRP1_PERIPH_DAC3);
}

/**
  * @details This function disables the DAC4 clock.
  */
__STATIC_INLINE void HAL_RCC_DAC4_DisableClock(void)
{
  LL_AHB3_GRP1_DisableClock(LL_AHB3_GRP1_PERIPH_DAC4);
}

/**
  * @}
  */ /* RCC_AHB3_Peripheral_Clock_Enable_Disable */

/** @defgroup RCC_AHB4_Peripheral_Clock_Enable_Disable AHB4 Peripheral Clock Enable Disable
  * @brief  Enable or disable the AHB4 peripheral clock.
  * @note   After reset, the peripheral clock (used for registers read/write access) is disabled and
  *         the application software has to enable this clock before using it.
  * @{
  */

/**
  * @details This function enables the GPIOA clock.
  */
__STATIC_INLINE void HAL_RCC_GPIOA_EnableClock(void)
{
  LL_AHB4_GRP1_EnableClock(LL_AHB4_GRP1_PERIPH_GPIOA);
}

/**
  * @details This function enables the GPIOB clock.
  */
__STATIC_INLINE void HAL_RCC_GPIOB_EnableClock(void)
{
  LL_AHB4_GRP1_EnableClock(LL_AHB4_GRP1_PERIPH_GPIOB);
}

/**
  * @details This function enables the GPIOC clock.
  */
__STATIC_INLINE void HAL_RCC_GPIOC_EnableClock(void)
{
  LL_AHB4_GRP1_EnableClock(LL_AHB4_GRP1_PERIPH_GPIOC);
}

/**
  * @details This function enables the GPIOD clock.
  */
__STATIC_INLINE void HAL_RCC_GPIOD_EnableClock(void)
{
  LL_AHB4_GRP1_EnableClock(LL_AHB4_GRP1_PERIPH_GPIOD);
}

/**
  * @details This function enables the GPIOE clock.
  */
__STATIC_INLINE void HAL_RCC_GPIOE_EnableClock(void)
{
  LL_AHB4_GRP1_EnableClock(LL_AHB4_GRP1_PERIPH_GPIOE);
}

/**
  * @details This function enables the GPIOF clock.
  */
__STATIC_INLINE void HAL_RCC_GPIOF_EnableClock(void)
{
  LL_AHB4_GRP1_EnableClock(LL_AHB4_GRP1_PERIPH_GPIOF);
}

/**
  * @details This function enables the GPIOG clock.
  */
__STATIC_INLINE void HAL_RCC_GPIOG_EnableClock(void)
{
  LL_AHB4_GRP1_EnableClock(LL_AHB4_GRP1_PERIPH_GPIOG);
}

/**
  * @details This function enables the GPIOH clock.
  */
__STATIC_INLINE void HAL_RCC_GPIOH_EnableClock(void)
{
  LL_AHB4_GRP1_EnableClock(LL_AHB4_GRP1_PERIPH_GPIOH);
}

/**
  * @details This function enables the GPIOI clock.
  */
__STATIC_INLINE void HAL_RCC_GPIOI_EnableClock(void)
{
  LL_AHB4_GRP1_EnableClock(LL_AHB4_GRP1_PERIPH_GPIOI);
}

/**
  * @details This function enables the CRC clock.
  */
__STATIC_INLINE void HAL_RCC_CRC_EnableClock(void)
{
  LL_AHB4_GRP1_EnableClock(LL_AHB4_GRP1_PERIPH_CRC);
}

/**
  * @details This function enables the BKPRAM clock.
  */
__STATIC_INLINE void HAL_RCC_BKPRAM_EnableClock(void)
{
  LL_AHB4_GRP1_EnableClock(LL_AHB4_GRP1_PERIPH_BKPRAM);
}

/**
  * @details This function disables the GPIOA clock.
  */
__STATIC_INLINE void HAL_RCC_GPIOA_DisableClock(void)
{
  LL_AHB4_GRP1_DisableClock(LL_AHB4_GRP1_PERIPH_GPIOA);
}

/**
  * @details This function disables the GPIOB clock.
  */
__STATIC_INLINE void HAL_RCC_GPIOB_DisableClock(void)
{
  LL_AHB4_GRP1_DisableClock(LL_AHB4_GRP1_PERIPH_GPIOB);
}

/**
  * @details This function disables the GPIOC clock.
  */
__STATIC_INLINE void HAL_RCC_GPIOC_DisableClock(void)
{
  LL_AHB4_GRP1_DisableClock(LL_AHB4_GRP1_PERIPH_GPIOC);
}

/**
  * @details This function disables the GPIOD clock.
  */
__STATIC_INLINE void HAL_RCC_GPIOD_DisableClock(void)
{
  LL_AHB4_GRP1_DisableClock(LL_AHB4_GRP1_PERIPH_GPIOD);
}

/**
  * @details This function disables the GPIOE clock.
  */
__STATIC_INLINE void HAL_RCC_GPIOE_DisableClock(void)
{
  LL_AHB4_GRP1_DisableClock(LL_AHB4_GRP1_PERIPH_GPIOE);
}

/**
  * @details This function disables the GPIOF clock.
  */
__STATIC_INLINE void HAL_RCC_GPIOF_DisableClock(void)
{
  LL_AHB4_GRP1_DisableClock(LL_AHB4_GRP1_PERIPH_GPIOF);
}

/**
  * @details This function disables the GPIOG clock.
  */
__STATIC_INLINE void HAL_RCC_GPIOG_DisableClock(void)
{
  LL_AHB4_GRP1_DisableClock(LL_AHB4_GRP1_PERIPH_GPIOG);
}

/**
  * @details This function disables the GPIOH clock.
  */
__STATIC_INLINE void HAL_RCC_GPIOH_DisableClock(void)
{
  LL_AHB4_GRP1_DisableClock(LL_AHB4_GRP1_PERIPH_GPIOH);
}

/**
  * @details This function disables the GPIOI clock.
  */
__STATIC_INLINE void HAL_RCC_GPIOI_DisableClock(void)
{
  LL_AHB4_GRP1_DisableClock(LL_AHB4_GRP1_PERIPH_GPIOI);
}

/**
  * @details This function disables the CRC clock.
  */
__STATIC_INLINE void HAL_RCC_CRC_DisableClock(void)
{
  LL_AHB4_GRP1_DisableClock(LL_AHB4_GRP1_PERIPH_CRC);
}

/**
  * @details This function disables the BKPRAM clock.
  */
__STATIC_INLINE void HAL_RCC_BKPRAM_DisableClock(void)
{
  LL_AHB4_GRP1_DisableClock(LL_AHB4_GRP1_PERIPH_BKPRAM);
}

/**
  * @}
  */ /* RCC_AHB4_Peripheral_Clock_Enable_Disable */

/** @defgroup RCC_AHB5_Peripheral_Clock_Enable_Disable AHB5 Peripheral Clock Enable Disable
  * @brief  Enable or disable the AHB5 peripheral clock.
  * @note   After reset, the peripheral clock (used for registers read/write access) is disabled and
  *         the application software has to enable this clock before using it.
  * @{
  */

/**
  * @details This function enables the HPDMA1 clock.
  */
__STATIC_INLINE void HAL_RCC_HPDMA1_EnableClock(void)
{
  LL_AHB5_GRP1_EnableClock(LL_AHB5_GRP1_PERIPH_HPDMA1);
}

/**
  * @details This function enables the FMC clock.
  */
__STATIC_INLINE void HAL_RCC_FMC_EnableClock(void)
{
  LL_AHB5_GRP1_EnableClock(LL_AHB5_GRP1_PERIPH_FMC);
}

/**
  * @details This function enables the XSPI1 clock.
  */
__STATIC_INLINE void HAL_RCC_XSPI1_EnableClock(void)
{
  LL_AHB5_GRP1_EnableClock(LL_AHB5_GRP1_PERIPH_XSPI1);
}

/**
  * @details This function enables the SDMMC1 clock.
  */
__STATIC_INLINE void HAL_RCC_SDMMC1_EnableClock(void)
{
  LL_AHB5_GRP1_EnableClock(LL_AHB5_GRP1_PERIPH_SDMMC1);
}

/**
  * @details This function enables the NPU clock.
  */
__STATIC_INLINE void HAL_RCC_NPU_EnableClock(void)
{
  LL_AHB5_GRP1_EnableClock(LL_AHB5_GRP1_PERIPH_NPU);
}

/**
  * @details This function disables the HPDMA1 clock.
  */
__STATIC_INLINE void HAL_RCC_HPDMA1_DisableClock(void)
{
  LL_AHB5_GRP1_DisableClock(LL_AHB5_GRP1_PERIPH_HPDMA1);
}

/**
  * @details This function disables the FMC clock.
  */
__STATIC_INLINE void HAL_RCC_FMC_DisableClock(void)
{
  LL_AHB5_GRP1_DisableClock(LL_AHB5_GRP1_PERIPH_FMC);
}

/**
  * @details This function disables the XSPI1 clock.
  */
__STATIC_INLINE void HAL_RCC_XSPI1_DisableClock(void)
{
  LL_AHB5_GRP1_DisableClock(LL_AHB5_GRP1_PERIPH_XSPI1);
}

/**
  * @details This function disables the SDMMC1 clock.
  */
__STATIC_INLINE void HAL_RCC_SDMMC1_DisableClock(void)
{
  LL_AHB5_GRP1_DisableClock(LL_AHB5_GRP1_PERIPH_SDMMC1);
}

/**
  * @details This function disables the NPU clock.
  */
__STATIC_INLINE void HAL_RCC_NPU_DisableClock(void)
{
  LL_AHB5_GRP1_DisableClock(LL_AHB5_GRP1_PERIPH_NPU);
}

/**
  * @}
  */ /* RCC_AHB5_Peripheral_Clock_Enable_Disable */

/** @defgroup RCC_APB1_Peripheral_Clock_Enable_Disable APB1 Peripheral Clock Enable Disable
  * @brief  Enable or disable the APB1 peripheral clock.
  * @note   After reset, the peripheral clock (used for registers read/write access) is disabled and
  *         the application software has to enable this clock before using it.
  * @{
  */

/**
  * @details This function enables the TIM2 clock.
  */
__STATIC_INLINE void HAL_RCC_TIM2_EnableClock(void)
{
  LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_TIM2);
}

/**
  * @details This function enables the TIM3 clock.
  */
__STATIC_INLINE void HAL_RCC_TIM3_EnableClock(void)
{
  LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_TIM3);
}

/**
  * @details This function enables the TIM4 clock.
  */
__STATIC_INLINE void HAL_RCC_TIM4_EnableClock(void)
{
  LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_TIM4);
}

/**
  * @details This function enables the TIM5 clock.
  */
__STATIC_INLINE void HAL_RCC_TIM5_EnableClock(void)
{
  LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_TIM5);
}

/**
  * @details This function enables the TIM6 clock.
  */
__STATIC_INLINE void HAL_RCC_TIM6_EnableClock(void)
{
  LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_TIM6);
}

/**
  * @details This function enables the TIM7 clock.
  */
__STATIC_INLINE void HAL_RCC_TIM7_EnableClock(void)
{
  LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_TIM7);
}

/**
  * @details This function enables the TIM12 clock.
  */
__STATIC_INLINE void HAL_RCC_TIM12_EnableClock(void)
{
  LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_TIM12);
}

/**
  * @details This function enables the TIM13 clock.
  */
__STATIC_INLINE void HAL_RCC_TIM13_EnableClock(void)
{
  LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_TIM13);
}

/**
  * @details This function enables the TIM14 clock.
  */
__STATIC_INLINE void HAL_RCC_TIM14_EnableClock(void)
{
  LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_TIM14);
}

/**
  * @details This function enables the LPTIM1 clock.
  */
__STATIC_INLINE void HAL_RCC_LPTIM1_EnableClock(void)
{
  LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_LPTIM1);
}

/**
  * @details This function enables the WWDG clock.
  */
__STATIC_INLINE void HAL_RCC_WWDG_EnableClock(void)
{
  LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_WWDG);
}

/**
  * @details This function enables the TIM10 clock.
  */
__STATIC_INLINE void HAL_RCC_TIM10_EnableClock(void)
{
  LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_TIM10);
}

/**
  * @details This function enables the TIM11 clock.
  */
__STATIC_INLINE void HAL_RCC_TIM11_EnableClock(void)
{
  LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_TIM11);
}

/**
  * @details This function enables the SPI2 clock.
  */
__STATIC_INLINE void HAL_RCC_SPI2_EnableClock(void)
{
  LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_SPI2);
}

/**
  * @details This function enables the SPI3 clock.
  */
__STATIC_INLINE void HAL_RCC_SPI3_EnableClock(void)
{
  LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_SPI3);
}

/**
  * @details This function enables the USART2 clock.
  */
__STATIC_INLINE void HAL_RCC_USART2_EnableClock(void)
{
  LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_USART2);
}

/**
  * @details This function enables the USART3 clock.
  */
__STATIC_INLINE void HAL_RCC_USART3_EnableClock(void)
{
  LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_USART3);
}

/**
  * @details This function enables the UART4 clock.
  */
__STATIC_INLINE void HAL_RCC_UART4_EnableClock(void)
{
  LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_UART4);
}

/**
  * @details This function enables the UART5 clock.
  */
__STATIC_INLINE void HAL_RCC_UART5_EnableClock(void)
{
  LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_UART5);
}

/**
  * @details This function enables the I2C1 clock.
  */
__STATIC_INLINE void HAL_RCC_I2C1_EnableClock(void)
{
  LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_I2C1);
}

/**
  * @details This function enables the I2C2 clock.
  */
__STATIC_INLINE void HAL_RCC_I2C2_EnableClock(void)
{
  LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_I2C2);
}

/**
  * @details This function enables the I2C3 clock.
  */
__STATIC_INLINE void HAL_RCC_I2C3_EnableClock(void)
{
  LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_I2C3);
}

/**
  * @details This function enables the I3C1 clock.
  */
__STATIC_INLINE void HAL_RCC_I3C1_EnableClock(void)
{
  LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_I3C1);
}

/**
  * @details This function enables the UART7 clock.
  */
__STATIC_INLINE void HAL_RCC_UART7_EnableClock(void)
{
  LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_UART7);
}

/**
  * @details This function enables the UART8 clock.
  */
__STATIC_INLINE void HAL_RCC_UART8_EnableClock(void)
{
  LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_UART8);
}

/**
  * @details This function disables the TIM2 clock.
  */
__STATIC_INLINE void HAL_RCC_TIM2_DisableClock(void)
{
  LL_APB1_GRP1_DisableClock(LL_APB1_GRP1_PERIPH_TIM2);
}

/**
  * @details This function disables the TIM3 clock.
  */
__STATIC_INLINE void HAL_RCC_TIM3_DisableClock(void)
{
  LL_APB1_GRP1_DisableClock(LL_APB1_GRP1_PERIPH_TIM3);
}

/**
  * @details This function disables the TIM4 clock.
  */
__STATIC_INLINE void HAL_RCC_TIM4_DisableClock(void)
{
  LL_APB1_GRP1_DisableClock(LL_APB1_GRP1_PERIPH_TIM4);
}

/**
  * @details This function disables the TIM5 clock.
  */
__STATIC_INLINE void HAL_RCC_TIM5_DisableClock(void)
{
  LL_APB1_GRP1_DisableClock(LL_APB1_GRP1_PERIPH_TIM5);
}

/**
  * @details This function disables the TIM6 clock.
  */
__STATIC_INLINE void HAL_RCC_TIM6_DisableClock(void)
{
  LL_APB1_GRP1_DisableClock(LL_APB1_GRP1_PERIPH_TIM6);
}

/**
  * @details This function disables the TIM7 clock.
  */
__STATIC_INLINE void HAL_RCC_TIM7_DisableClock(void)
{
  LL_APB1_GRP1_DisableClock(LL_APB1_GRP1_PERIPH_TIM7);
}

/**
  * @details This function disables the TIM12 clock.
  */
__STATIC_INLINE void HAL_RCC_TIM12_DisableClock(void)
{
  LL_APB1_GRP1_DisableClock(LL_APB1_GRP1_PERIPH_TIM12);
}

/**
  * @details This function disables the TIM13 clock.
  */
__STATIC_INLINE void HAL_RCC_TIM13_DisableClock(void)
{
  LL_APB1_GRP1_DisableClock(LL_APB1_GRP1_PERIPH_TIM13);
}

/**
  * @details This function disables the TIM14 clock.
  */
__STATIC_INLINE void HAL_RCC_TIM14_DisableClock(void)
{
  LL_APB1_GRP1_DisableClock(LL_APB1_GRP1_PERIPH_TIM14);
}

/**
  * @details This function disables the LPTIM1 clock.
  */
__STATIC_INLINE void HAL_RCC_LPTIM1_DisableClock(void)
{
  LL_APB1_GRP1_DisableClock(LL_APB1_GRP1_PERIPH_LPTIM1);
}

/**
  * @details This function disables the WWDG clock.
  */
__STATIC_INLINE void HAL_RCC_WWDG_DisableClock(void)
{
  LL_APB1_GRP1_DisableClock(LL_APB1_GRP1_PERIPH_WWDG);
}

/**
  * @details This function disables the TIM10 clock.
  */
__STATIC_INLINE void HAL_RCC_TIM10_DisableClock(void)
{
  LL_APB1_GRP1_DisableClock(LL_APB1_GRP1_PERIPH_TIM10);
}

/**
  * @details This function disables the TIM11 clock.
  */
__STATIC_INLINE void HAL_RCC_TIM11_DisableClock(void)
{
  LL_APB1_GRP1_DisableClock(LL_APB1_GRP1_PERIPH_TIM11);
}

/**
  * @details This function disables the SPI2 clock.
  */
__STATIC_INLINE void HAL_RCC_SPI2_DisableClock(void)
{
  LL_APB1_GRP1_DisableClock(LL_APB1_GRP1_PERIPH_SPI2);
}

/**
  * @details This function disables the SPI3 clock.
  */
__STATIC_INLINE void HAL_RCC_SPI3_DisableClock(void)
{
  LL_APB1_GRP1_DisableClock(LL_APB1_GRP1_PERIPH_SPI3);
}

/**
  * @details This function disables the USART2 clock.
  */
__STATIC_INLINE void HAL_RCC_USART2_DisableClock(void)
{
  LL_APB1_GRP1_DisableClock(LL_APB1_GRP1_PERIPH_USART2);
}

/**
  * @details This function disables the USART3 clock.
  */
__STATIC_INLINE void HAL_RCC_USART3_DisableClock(void)
{
  LL_APB1_GRP1_DisableClock(LL_APB1_GRP1_PERIPH_USART3);
}

/**
  * @details This function disables the UART4 clock.
  */
__STATIC_INLINE void HAL_RCC_UART4_DisableClock(void)
{
  LL_APB1_GRP1_DisableClock(LL_APB1_GRP1_PERIPH_UART4);
}

/**
  * @details This function disables the UART5 clock.
  */
__STATIC_INLINE void HAL_RCC_UART5_DisableClock(void)
{
  LL_APB1_GRP1_DisableClock(LL_APB1_GRP1_PERIPH_UART5);
}

/**
  * @details This function disables the I2C1 clock.
  */
__STATIC_INLINE void HAL_RCC_I2C1_DisableClock(void)
{
  LL_APB1_GRP1_DisableClock(LL_APB1_GRP1_PERIPH_I2C1);
}

/**
  * @details This function disables the I2C2 clock.
  */
__STATIC_INLINE void HAL_RCC_I2C2_DisableClock(void)
{
  LL_APB1_GRP1_DisableClock(LL_APB1_GRP1_PERIPH_I2C2);
}

/**
  * @details This function disables the I2C3 clock.
  */
__STATIC_INLINE void HAL_RCC_I2C3_DisableClock(void)
{
  LL_APB1_GRP1_DisableClock(LL_APB1_GRP1_PERIPH_I2C3);
}

/**
  * @details This function disables the I3C1 clock.
  */
__STATIC_INLINE void HAL_RCC_I3C1_DisableClock(void)
{
  LL_APB1_GRP1_DisableClock(LL_APB1_GRP1_PERIPH_I3C1);
}

/**
  * @details This function disables the UART7 clock.
  */
__STATIC_INLINE void HAL_RCC_UART7_DisableClock(void)
{
  LL_APB1_GRP1_DisableClock(LL_APB1_GRP1_PERIPH_UART7);
}

/**
  * @details This function disables the UART8 clock.
  */
__STATIC_INLINE void HAL_RCC_UART8_DisableClock(void)
{
  LL_APB1_GRP1_DisableClock(LL_APB1_GRP1_PERIPH_UART8);
}

/**
  * @}
  */ /* RCC_APB1_Peripheral_Clock_Enable_Disable */

/** @defgroup RCC_APB1_Peripheral_Clock_Enable_Disable APB1 Peripheral Clock Enable Disable
  * @brief  Enable or disable the APB1 peripheral clock.
  * @note   After reset, the peripheral clock (used for registers read/write access) is disabled and
  *         the application software has to enable this clock before using it.
  * @{
  */

/**
  * @details This function enables the CRS clock.
  */
__STATIC_INLINE void HAL_RCC_CRS_EnableClock(void)
{
  LL_APB1_GRP2_EnableClock(LL_APB1_GRP2_PERIPH_CRS);
}

/**
  * @details This function enables the FDCAN clock.
  */
__STATIC_INLINE void HAL_RCC_FDCAN_EnableClock(void)
{
  LL_APB1_GRP2_EnableClock(LL_APB1_GRP2_PERIPH_FDCAN);
}

/**
  * @details This function enables the UCPD1 clock.
  */
__STATIC_INLINE void HAL_RCC_UCPD1_EnableClock(void)
{
  LL_APB1_GRP2_EnableClock(LL_APB1_GRP2_PERIPH_UCPD1);
}

/**
  * @details This function disables the CRS clock.
  */
__STATIC_INLINE void HAL_RCC_CRS_DisableClock(void)
{
  LL_APB1_GRP2_DisableClock(LL_APB1_GRP2_PERIPH_CRS);
}

/**
  * @details This function disables the FDCAN clock.
  */
__STATIC_INLINE void HAL_RCC_FDCAN_DisableClock(void)
{
  LL_APB1_GRP2_DisableClock(LL_APB1_GRP2_PERIPH_FDCAN);
}

/**
  * @details This function disables the UCPD1 clock.
  */
__STATIC_INLINE void HAL_RCC_UCPD1_DisableClock(void)
{
  LL_APB1_GRP2_DisableClock(LL_APB1_GRP2_PERIPH_UCPD1);
}

/**
  * @}
  */ /* RCC_APB1_Peripheral_Clock_Enable_Disable */

/** @defgroup RCC_APB2_Peripheral_Clock_Enable_Disable APB2 Peripheral Clock Enable Disable
  * @brief  Enable or disable the APB2 peripheral clock.
  * @note   After reset, the peripheral clock (used for registers read/write access) is disabled and
  *         the application software has to enable this clock before using it.
  * @{
  */

/**
  * @details This function enables the TIM1 clock.
  */
__STATIC_INLINE void HAL_RCC_TIM1_EnableClock(void)
{
  LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_TIM1);
}

/**
  * @details This function enables the TIM8 clock.
  */
__STATIC_INLINE void HAL_RCC_TIM8_EnableClock(void)
{
  LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_TIM8);
}

/**
  * @details This function enables the TIM20 clock.
  */
__STATIC_INLINE void HAL_RCC_TIM20_EnableClock(void)
{
  LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_TIM20);
}

/**
  * @details This function enables the USART1 clock.
  */
__STATIC_INLINE void HAL_RCC_USART1_EnableClock(void)
{
  LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_USART1);
}

/**
  * @details This function enables the USART6 clock.
  */
__STATIC_INLINE void HAL_RCC_USART6_EnableClock(void)
{
  LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_USART6);
}

/**
  * @details This function enables the UART9 clock.
  */
__STATIC_INLINE void HAL_RCC_UART9_EnableClock(void)
{
  LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_UART9);
}

/**
  * @details This function enables the USART10 clock.
  */
__STATIC_INLINE void HAL_RCC_USART10_EnableClock(void)
{
  LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_USART10);
}

/**
  * @details This function enables the SPI1 clock.
  */
__STATIC_INLINE void HAL_RCC_SPI1_EnableClock(void)
{
  LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_SPI1);
}

/**
  * @details This function enables the SPI4 clock.
  */
__STATIC_INLINE void HAL_RCC_SPI4_EnableClock(void)
{
  LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_SPI4);
}

/**
  * @details This function enables the TIM15 clock.
  */
__STATIC_INLINE void HAL_RCC_TIM15_EnableClock(void)
{
  LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_TIM15);
}

/**
  * @details This function enables the TIM16 clock.
  */
__STATIC_INLINE void HAL_RCC_TIM16_EnableClock(void)
{
  LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_TIM16);
}

/**
  * @details This function enables the TIM17 clock.
  */
__STATIC_INLINE void HAL_RCC_TIM17_EnableClock(void)
{
  LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_TIM17);
}

/**
  * @details This function enables the TIM9 clock.
  */
__STATIC_INLINE void HAL_RCC_TIM9_EnableClock(void)
{
  LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_TIM9);
}

/**
  * @details This function enables the SPI5 clock.
  */
__STATIC_INLINE void HAL_RCC_SPI5_EnableClock(void)
{
  LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_SPI5);
}

/**
  * @details This function enables the HRTIM1 clock.
  */
__STATIC_INLINE void HAL_RCC_HRTIM1_EnableClock(void)
{
  LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_HRTIM1);
}

/**
  * @details This function enables the HRTIM2 clock.
  */
__STATIC_INLINE void HAL_RCC_HRTIM2_EnableClock(void)
{
  LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_HRTIM2);
}

/**
  * @details This function disables the TIM1 clock.
  */
__STATIC_INLINE void HAL_RCC_TIM1_DisableClock(void)
{
  LL_APB2_GRP1_DisableClock(LL_APB2_GRP1_PERIPH_TIM1);
}

/**
  * @details This function disables the TIM8 clock.
  */
__STATIC_INLINE void HAL_RCC_TIM8_DisableClock(void)
{
  LL_APB2_GRP1_DisableClock(LL_APB2_GRP1_PERIPH_TIM8);
}

/**
  * @details This function disables the TIM20 clock.
  */
__STATIC_INLINE void HAL_RCC_TIM20_DisableClock(void)
{
  LL_APB2_GRP1_DisableClock(LL_APB2_GRP1_PERIPH_TIM20);
}

/**
  * @details This function disables the USART1 clock.
  */
__STATIC_INLINE void HAL_RCC_USART1_DisableClock(void)
{
  LL_APB2_GRP1_DisableClock(LL_APB2_GRP1_PERIPH_USART1);
}

/**
  * @details This function disables the USART6 clock.
  */
__STATIC_INLINE void HAL_RCC_USART6_DisableClock(void)
{
  LL_APB2_GRP1_DisableClock(LL_APB2_GRP1_PERIPH_USART6);
}

/**
  * @details This function disables the UART9 clock.
  */
__STATIC_INLINE void HAL_RCC_UART9_DisableClock(void)
{
  LL_APB2_GRP1_DisableClock(LL_APB2_GRP1_PERIPH_UART9);
}

/**
  * @details This function disables the USART10 clock.
  */
__STATIC_INLINE void HAL_RCC_USART10_DisableClock(void)
{
  LL_APB2_GRP1_DisableClock(LL_APB2_GRP1_PERIPH_USART10);
}

/**
  * @details This function disables the SPI1 clock.
  */
__STATIC_INLINE void HAL_RCC_SPI1_DisableClock(void)
{
  LL_APB2_GRP1_DisableClock(LL_APB2_GRP1_PERIPH_SPI1);
}

/**
  * @details This function disables the SPI4 clock.
  */
__STATIC_INLINE void HAL_RCC_SPI4_DisableClock(void)
{
  LL_APB2_GRP1_DisableClock(LL_APB2_GRP1_PERIPH_SPI4);
}

/**
  * @details This function disables the TIM15 clock.
  */
__STATIC_INLINE void HAL_RCC_TIM15_DisableClock(void)
{
  LL_APB2_GRP1_DisableClock(LL_APB2_GRP1_PERIPH_TIM15);
}

/**
  * @details This function disables the TIM16 clock.
  */
__STATIC_INLINE void HAL_RCC_TIM16_DisableClock(void)
{
  LL_APB2_GRP1_DisableClock(LL_APB2_GRP1_PERIPH_TIM16);
}

/**
  * @details This function disables the TIM17 clock.
  */
__STATIC_INLINE void HAL_RCC_TIM17_DisableClock(void)
{
  LL_APB2_GRP1_DisableClock(LL_APB2_GRP1_PERIPH_TIM17);
}

/**
  * @details This function disables the TIM9 clock.
  */
__STATIC_INLINE void HAL_RCC_TIM9_DisableClock(void)
{
  LL_APB2_GRP1_DisableClock(LL_APB2_GRP1_PERIPH_TIM9);
}

/**
  * @details This function disables the SPI5 clock.
  */
__STATIC_INLINE void HAL_RCC_SPI5_DisableClock(void)
{
  LL_APB2_GRP1_DisableClock(LL_APB2_GRP1_PERIPH_SPI5);
}

/**
  * @details This function disables the HRTIM1 clock.
  */
__STATIC_INLINE void HAL_RCC_HRTIM1_DisableClock(void)
{
  LL_APB2_GRP1_DisableClock(LL_APB2_GRP1_PERIPH_HRTIM1);
}

/**
  * @details This function disables the HRTIM2 clock.
  */
__STATIC_INLINE void HAL_RCC_HRTIM2_DisableClock(void)
{
  LL_APB2_GRP1_DisableClock(LL_APB2_GRP1_PERIPH_HRTIM2);
}

/**
  * @}
  */ /* RCC_APB2_Peripheral_Clock_Enable_Disable */

/** @defgroup RCC_APB4_Peripheral_Clock_Enable_Disable APB4 Peripheral Clock Enable Disable
  * @brief  Enable or disable the APB4 peripheral clock.
  * @note   After reset, the peripheral clock (used for registers read/write access) is disabled and
  *         the application software has to enable this clock before using it.
  * @{
  */

/**
  * @details This function enables the SBS clock.
  */
__STATIC_INLINE void HAL_RCC_SBS_EnableClock(void)
{
  LL_APB4_GRP1_EnableClock(LL_APB4_GRP1_PERIPH_SBS);
}

/**
  * @details This function enables the LPUART1 clock.
  */
__STATIC_INLINE void HAL_RCC_LPUART1_EnableClock(void)
{
  LL_APB4_GRP1_EnableClock(LL_APB4_GRP1_PERIPH_LPUART1);
}

/**
  * @details This function enables the SPI6 clock.
  */
__STATIC_INLINE void HAL_RCC_SPI6_EnableClock(void)
{
  LL_APB4_GRP1_EnableClock(LL_APB4_GRP1_PERIPH_SPI6);
}

/**
  * @details This function enables the LPTIM2 clock.
  */
__STATIC_INLINE void HAL_RCC_LPTIM2_EnableClock(void)
{
  LL_APB4_GRP1_EnableClock(LL_APB4_GRP1_PERIPH_LPTIM2);
}

/**
  * @details This function enables the LPTIM3 clock.
  */
__STATIC_INLINE void HAL_RCC_LPTIM3_EnableClock(void)
{
  LL_APB4_GRP1_EnableClock(LL_APB4_GRP1_PERIPH_LPTIM3);
}

/**
  * @details This function enables the LPTIM4 clock.
  */
__STATIC_INLINE void HAL_RCC_LPTIM4_EnableClock(void)
{
  LL_APB4_GRP1_EnableClock(LL_APB4_GRP1_PERIPH_LPTIM4);
}

/**
  * @details This function enables the LPTIM5 clock.
  */
__STATIC_INLINE void HAL_RCC_LPTIM5_EnableClock(void)
{
  LL_APB4_GRP1_EnableClock(LL_APB4_GRP1_PERIPH_LPTIM5);
}

/**
  * @details This function enables the VREF clock.
  */
__STATIC_INLINE void HAL_RCC_VREF_EnableClock(void)
{
  LL_APB4_GRP1_EnableClock(LL_APB4_GRP1_PERIPH_VREF);
}

/**
  * @details This function enables the RTCAPB clock.
  */
__STATIC_INLINE void HAL_RCC_RTCAPB_EnableClock(void)
{
  LL_APB4_GRP1_EnableClock(LL_APB4_GRP1_PERIPH_RTCAPB);
}

/**
  * @details This function enables the DTS clock.
  */
__STATIC_INLINE void HAL_RCC_DTS_EnableClock(void)
{
  LL_APB4_GRP1_EnableClock(LL_APB4_GRP1_PERIPH_DTS);
}

/**
  * @details This function enables the COMP12 clock.
  */
__STATIC_INLINE void HAL_RCC_COMP12_EnableClock(void)
{
  LL_APB4_GRP1_EnableClock(LL_APB4_GRP1_PERIPH_COMP12);
}

/**
  * @details This function enables the COMP34 clock.
  */
__STATIC_INLINE void HAL_RCC_COMP34_EnableClock(void)
{
  LL_APB4_GRP1_EnableClock(LL_APB4_GRP1_PERIPH_COMP34);
}

/**
  * @details This function enables the COMP56 clock.
  */
__STATIC_INLINE void HAL_RCC_COMP56_EnableClock(void)
{
  LL_APB4_GRP1_EnableClock(LL_APB4_GRP1_PERIPH_COMP56);
}

/**
  * @details This function enables the COMP78 clock.
  */
__STATIC_INLINE void HAL_RCC_COMP78_EnableClock(void)
{
  LL_APB4_GRP1_EnableClock(LL_APB4_GRP1_PERIPH_COMP78);
}

/**
  * @details This function disables the SBS clock.
  */
__STATIC_INLINE void HAL_RCC_SBS_DisableClock(void)
{
  LL_APB4_GRP1_DisableClock(LL_APB4_GRP1_PERIPH_SBS);
}

/**
  * @details This function disables the LPUART1 clock.
  */
__STATIC_INLINE void HAL_RCC_LPUART1_DisableClock(void)
{
  LL_APB4_GRP1_DisableClock(LL_APB4_GRP1_PERIPH_LPUART1);
}

/**
  * @details This function disables the SPI6 clock.
  */
__STATIC_INLINE void HAL_RCC_SPI6_DisableClock(void)
{
  LL_APB4_GRP1_DisableClock(LL_APB4_GRP1_PERIPH_SPI6);
}

/**
  * @details This function disables the LPTIM2 clock.
  */
__STATIC_INLINE void HAL_RCC_LPTIM2_DisableClock(void)
{
  LL_APB4_GRP1_DisableClock(LL_APB4_GRP1_PERIPH_LPTIM2);
}

/**
  * @details This function disables the LPTIM3 clock.
  */
__STATIC_INLINE void HAL_RCC_LPTIM3_DisableClock(void)
{
  LL_APB4_GRP1_DisableClock(LL_APB4_GRP1_PERIPH_LPTIM3);
}

/**
  * @details This function disables the LPTIM4 clock.
  */
__STATIC_INLINE void HAL_RCC_LPTIM4_DisableClock(void)
{
  LL_APB4_GRP1_DisableClock(LL_APB4_GRP1_PERIPH_LPTIM4);
}

/**
  * @details This function disables the LPTIM5 clock.
  */
__STATIC_INLINE void HAL_RCC_LPTIM5_DisableClock(void)
{
  LL_APB4_GRP1_DisableClock(LL_APB4_GRP1_PERIPH_LPTIM5);
}

/**
  * @details This function disables the VREF clock.
  */
__STATIC_INLINE void HAL_RCC_VREF_DisableClock(void)
{
  LL_APB4_GRP1_DisableClock(LL_APB4_GRP1_PERIPH_VREF);
}

/**
  * @details This function disables the RTCAPB clock.
  */
__STATIC_INLINE void HAL_RCC_RTCAPB_DisableClock(void)
{
  LL_APB4_GRP1_DisableClock(LL_APB4_GRP1_PERIPH_RTCAPB);
}

/**
  * @details This function disables the DTS clock.
  */
__STATIC_INLINE void HAL_RCC_DTS_DisableClock(void)
{
  LL_APB4_GRP1_DisableClock(LL_APB4_GRP1_PERIPH_DTS);
}

/**
  * @details This function disables the COMP12 clock.
  */
__STATIC_INLINE void HAL_RCC_COMP12_DisableClock(void)
{
  LL_APB4_GRP1_DisableClock(LL_APB4_GRP1_PERIPH_COMP12);
}

/**
  * @details This function disables the COMP34 clock.
  */
__STATIC_INLINE void HAL_RCC_COMP34_DisableClock(void)
{
  LL_APB4_GRP1_DisableClock(LL_APB4_GRP1_PERIPH_COMP34);
}

/**
  * @details This function disables the COMP56 clock.
  */
__STATIC_INLINE void HAL_RCC_COMP56_DisableClock(void)
{
  LL_APB4_GRP1_DisableClock(LL_APB4_GRP1_PERIPH_COMP56);
}

/**
  * @details This function disables the COMP78 clock.
  */
__STATIC_INLINE void HAL_RCC_COMP78_DisableClock(void)
{
  LL_APB4_GRP1_DisableClock(LL_APB4_GRP1_PERIPH_COMP78);
}

/**
  * @}
  */ /* RCC_APB4_Peripheral_Clock_Enable_Disable */

/** @defgroup RCC_CKG_Peripheral_Clock_Enable_Disable CKG Peripheral Clock Enable Disable
  * @brief  Enable or disable the CKG peripheral clock.
  * @note   After reset, the peripheral clock (used for registers read/write access) is disabled and
  *         the application software has to enable this clock before using it.
  * @{
  */

/**
  * @}
  */ /* RCC_CKG_Peripheral_Clock_Enable_Disable */

/** @defgroup RCC_AHB1_Peripheral_Clock_Enable_Status AHB1 Peripheral Clock Enabled Status
  * @brief  Check whether the AHB1 peripheral clock is enabled or not.
  * @note   After reset, the peripheral clock (used for registers read/write access) is disabled and
  *         the application software has to enable this clock before using it.
  * @{
  */

/**
  * @details This function checks if the HSP clock is enabled.
  * @retval HAL_RCC_CLK_DISABLED HSP clock is disabled
  * @retval HAL_RCC_CLK_ENABLED  HSP clock is enabled
 */
__STATIC_INLINE hal_rcc_clk_status_t HAL_RCC_HSP_IsEnabledClock(void)
{
  return (hal_rcc_clk_status_t)LL_AHB1_GRP1_IsEnabledClock(LL_AHB1_GRP1_PERIPH_HSP);
}

/**
  * @details This function checks if the GPDMA1 clock is enabled.
  * @retval HAL_RCC_CLK_DISABLED GPDMA1 clock is disabled
  * @retval HAL_RCC_CLK_ENABLED  GPDMA1 clock is enabled
 */
__STATIC_INLINE hal_rcc_clk_status_t HAL_RCC_GPDMA1_IsEnabledClock(void)
{
  return (hal_rcc_clk_status_t)LL_AHB1_GRP1_IsEnabledClock(LL_AHB1_GRP1_PERIPH_GPDMA1);
}

/**
  * @details This function checks if the OTGFS clock is enabled.
  * @retval HAL_RCC_CLK_DISABLED OTGFS clock is disabled
  * @retval HAL_RCC_CLK_ENABLED  OTGFS clock is enabled
 */
__STATIC_INLINE hal_rcc_clk_status_t HAL_RCC_OTGFS_IsEnabledClock(void)
{
  return (hal_rcc_clk_status_t)LL_AHB1_GRP1_IsEnabledClock(LL_AHB1_GRP1_PERIPH_OTGFS);
}

/**
  * @details This function checks if the ADF1 clock is enabled.
  * @retval HAL_RCC_CLK_DISABLED ADF1 clock is disabled
  * @retval HAL_RCC_CLK_ENABLED  ADF1 clock is enabled
 */
__STATIC_INLINE hal_rcc_clk_status_t HAL_RCC_ADF1_IsEnabledClock(void)
{
  return (hal_rcc_clk_status_t)LL_AHB1_GRP1_IsEnabledClock(LL_AHB1_GRP1_PERIPH_ADF1);
}

/**
  * @}
  */ /* RCC_AHB1_Peripheral_Clock_Enable_Status */

/** @defgroup RCC_AHB2_Peripheral_Clock_Enable_Status AHB2 Peripheral Clock Enabled Status
  * @brief  Check whether the AHB2 peripheral clock is enabled or not.
  * @note   After reset, the peripheral clock (used for registers read/write access) is disabled and
  *         the application software has to enable this clock before using it.
  * @{
  */

/**
  * @details This function checks if the CORDIC clock is enabled.
  * @retval HAL_RCC_CLK_DISABLED CORDIC clock is disabled
  * @retval HAL_RCC_CLK_ENABLED  CORDIC clock is enabled
 */
__STATIC_INLINE hal_rcc_clk_status_t HAL_RCC_CORDIC_IsEnabledClock(void)
{
  return (hal_rcc_clk_status_t)LL_AHB2_GRP1_IsEnabledClock(LL_AHB2_GRP1_PERIPH_CORDIC);
}

/**
  * @details This function checks if the FMAC clock is enabled.
  * @retval HAL_RCC_CLK_DISABLED FMAC clock is disabled
  * @retval HAL_RCC_CLK_ENABLED  FMAC clock is enabled
 */
__STATIC_INLINE hal_rcc_clk_status_t HAL_RCC_FMAC_IsEnabledClock(void)
{
  return (hal_rcc_clk_status_t)LL_AHB2_GRP1_IsEnabledClock(LL_AHB2_GRP1_PERIPH_FMAC1);
}

/**
  * @details This function checks if the AHBSRAM1 clock is enabled.
  * @retval HAL_RCC_CLK_DISABLED AHBSRAM1 clock is disabled
  * @retval HAL_RCC_CLK_ENABLED  AHBSRAM1 clock is enabled
 */
__STATIC_INLINE hal_rcc_clk_status_t HAL_RCC_AHBSRAM1_IsEnabledClock(void)
{
  return (hal_rcc_clk_status_t)LL_AHB2_GRP1_IsEnabledClock(LL_AHB2_GRP1_PERIPH_AHBSRAM1);
}

/**
  * @details This function checks if the AHBSRAM2 clock is enabled.
  * @retval HAL_RCC_CLK_DISABLED AHBSRAM2 clock is disabled
  * @retval HAL_RCC_CLK_ENABLED  AHBSRAM2 clock is enabled
 */
__STATIC_INLINE hal_rcc_clk_status_t HAL_RCC_AHBSRAM2_IsEnabledClock(void)
{
  return (hal_rcc_clk_status_t)LL_AHB2_GRP1_IsEnabledClock(LL_AHB2_GRP1_PERIPH_AHBSRAM2);
}

/**
  * @details This function checks if the AHBSRAM3 clock is enabled.
  * @retval HAL_RCC_CLK_DISABLED AHBSRAM3 clock is disabled
  * @retval HAL_RCC_CLK_ENABLED  AHBSRAM3 clock is enabled
 */
__STATIC_INLINE hal_rcc_clk_status_t HAL_RCC_AHBSRAM3_IsEnabledClock(void)
{
  return (hal_rcc_clk_status_t)LL_AHB2_GRP1_IsEnabledClock(LL_AHB2_GRP1_PERIPH_AHBSRAM3);
}

/**
  * @}
  */ /* RCC_AHB2_Peripheral_Clock_Enable_Status */

/** @defgroup RCC_AHB3_Peripheral_Clock_Enable_Status AHB3 Peripheral Clock Enabled Status
  * @brief  Check whether the AHB3 peripheral clock is enabled or not.
  * @note   After reset, the peripheral clock (used for registers read/write access) is disabled and
  *         the application software has to enable this clock before using it.
  * @{
  */

/**
  * @details This function checks if the RNG clock is enabled.
  * @retval HAL_RCC_CLK_DISABLED RNG clock is disabled
  * @retval HAL_RCC_CLK_ENABLED  RNG clock is enabled
 */
__STATIC_INLINE hal_rcc_clk_status_t HAL_RCC_RNG_IsEnabledClock(void)
{
  return (hal_rcc_clk_status_t)LL_AHB3_GRP1_IsEnabledClock(LL_AHB3_GRP1_PERIPH_RNG);
}

/**
  * @details This function checks if the HASH clock is enabled.
  * @retval HAL_RCC_CLK_DISABLED HASH clock is disabled
  * @retval HAL_RCC_CLK_ENABLED  HASH clock is enabled
 */
__STATIC_INLINE hal_rcc_clk_status_t HAL_RCC_HASH_IsEnabledClock(void)
{
  return (hal_rcc_clk_status_t)LL_AHB3_GRP1_IsEnabledClock(LL_AHB3_GRP1_PERIPH_HASH);
}

/**
  * @details This function checks if the ADC12 clock is enabled.
  * @retval HAL_RCC_CLK_DISABLED ADC12 clock is disabled
  * @retval HAL_RCC_CLK_ENABLED  ADC12 clock is enabled
 */
__STATIC_INLINE hal_rcc_clk_status_t HAL_RCC_ADC12_IsEnabledClock(void)
{
  return (hal_rcc_clk_status_t)LL_AHB3_GRP1_IsEnabledClock(LL_AHB3_GRP1_PERIPH_ADC12);
}

/**
  * @details This function checks if the ADC34 clock is enabled.
  * @retval HAL_RCC_CLK_DISABLED ADC34 clock is disabled
  * @retval HAL_RCC_CLK_ENABLED  ADC34 clock is enabled
 */
__STATIC_INLINE hal_rcc_clk_status_t HAL_RCC_ADC34_IsEnabledClock(void)
{
  return (hal_rcc_clk_status_t)LL_AHB3_GRP1_IsEnabledClock(LL_AHB3_GRP1_PERIPH_ADC34);
}

/**
  * @details This function checks if the DAC1 clock is enabled.
  * @retval HAL_RCC_CLK_DISABLED DAC1 clock is disabled
  * @retval HAL_RCC_CLK_ENABLED  DAC1 clock is enabled
 */
__STATIC_INLINE hal_rcc_clk_status_t HAL_RCC_DAC1_IsEnabledClock(void)
{
  return (hal_rcc_clk_status_t)LL_AHB3_GRP1_IsEnabledClock(LL_AHB3_GRP1_PERIPH_DAC1);
}

/**
  * @details This function checks if the DAC2 clock is enabled.
  * @retval HAL_RCC_CLK_DISABLED DAC2 clock is disabled
  * @retval HAL_RCC_CLK_ENABLED  DAC2 clock is enabled
 */
__STATIC_INLINE hal_rcc_clk_status_t HAL_RCC_DAC2_IsEnabledClock(void)
{
  return (hal_rcc_clk_status_t)LL_AHB3_GRP1_IsEnabledClock(LL_AHB3_GRP1_PERIPH_DAC2);
}

/**
  * @details This function checks if the DAC3 clock is enabled.
  * @retval HAL_RCC_CLK_DISABLED DAC3 clock is disabled
  * @retval HAL_RCC_CLK_ENABLED  DAC3 clock is enabled
 */
__STATIC_INLINE hal_rcc_clk_status_t HAL_RCC_DAC3_IsEnabledClock(void)
{
  return (hal_rcc_clk_status_t)LL_AHB3_GRP1_IsEnabledClock(LL_AHB3_GRP1_PERIPH_DAC3);
}

/**
  * @details This function checks if the DAC4 clock is enabled.
  * @retval HAL_RCC_CLK_DISABLED DAC4 clock is disabled
  * @retval HAL_RCC_CLK_ENABLED  DAC4 clock is enabled
 */
__STATIC_INLINE hal_rcc_clk_status_t HAL_RCC_DAC4_IsEnabledClock(void)
{
  return (hal_rcc_clk_status_t)LL_AHB3_GRP1_IsEnabledClock(LL_AHB3_GRP1_PERIPH_DAC4);
}

/**
  * @}
  */ /* RCC_AHB3_Peripheral_Clock_Enable_Status */

/** @defgroup RCC_AHB4_Peripheral_Clock_Enable_Status AHB4 Peripheral Clock Enabled Status
  * @brief  Check whether the AHB4 peripheral clock is enabled or not.
  * @note   After reset, the peripheral clock (used for registers read/write access) is disabled and
  *         the application software has to enable this clock before using it.
  * @{
  */

/**
  * @details This function checks if the GPIOA clock is enabled.
  * @retval HAL_RCC_CLK_DISABLED GPIOA clock is disabled
  * @retval HAL_RCC_CLK_ENABLED  GPIOA clock is enabled
 */
__STATIC_INLINE hal_rcc_clk_status_t HAL_RCC_GPIOA_IsEnabledClock(void)
{
  return (hal_rcc_clk_status_t)LL_AHB4_GRP1_IsEnabledClock(LL_AHB4_GRP1_PERIPH_GPIOA);
}

/**
  * @details This function checks if the GPIOB clock is enabled.
  * @retval HAL_RCC_CLK_DISABLED GPIOB clock is disabled
  * @retval HAL_RCC_CLK_ENABLED  GPIOB clock is enabled
 */
__STATIC_INLINE hal_rcc_clk_status_t HAL_RCC_GPIOB_IsEnabledClock(void)
{
  return (hal_rcc_clk_status_t)LL_AHB4_GRP1_IsEnabledClock(LL_AHB4_GRP1_PERIPH_GPIOB);
}

/**
  * @details This function checks if the GPIOC clock is enabled.
  * @retval HAL_RCC_CLK_DISABLED GPIOC clock is disabled
  * @retval HAL_RCC_CLK_ENABLED  GPIOC clock is enabled
 */
__STATIC_INLINE hal_rcc_clk_status_t HAL_RCC_GPIOC_IsEnabledClock(void)
{
  return (hal_rcc_clk_status_t)LL_AHB4_GRP1_IsEnabledClock(LL_AHB4_GRP1_PERIPH_GPIOC);
}

/**
  * @details This function checks if the GPIOD clock is enabled.
  * @retval HAL_RCC_CLK_DISABLED GPIOD clock is disabled
  * @retval HAL_RCC_CLK_ENABLED  GPIOD clock is enabled
 */
__STATIC_INLINE hal_rcc_clk_status_t HAL_RCC_GPIOD_IsEnabledClock(void)
{
  return (hal_rcc_clk_status_t)LL_AHB4_GRP1_IsEnabledClock(LL_AHB4_GRP1_PERIPH_GPIOD);
}

/**
  * @details This function checks if the GPIOE clock is enabled.
  * @retval HAL_RCC_CLK_DISABLED GPIOE clock is disabled
  * @retval HAL_RCC_CLK_ENABLED  GPIOE clock is enabled
 */
__STATIC_INLINE hal_rcc_clk_status_t HAL_RCC_GPIOE_IsEnabledClock(void)
{
  return (hal_rcc_clk_status_t)LL_AHB4_GRP1_IsEnabledClock(LL_AHB4_GRP1_PERIPH_GPIOE);
}

/**
  * @details This function checks if the GPIOF clock is enabled.
  * @retval HAL_RCC_CLK_DISABLED GPIOF clock is disabled
  * @retval HAL_RCC_CLK_ENABLED  GPIOF clock is enabled
 */
__STATIC_INLINE hal_rcc_clk_status_t HAL_RCC_GPIOF_IsEnabledClock(void)
{
  return (hal_rcc_clk_status_t)LL_AHB4_GRP1_IsEnabledClock(LL_AHB4_GRP1_PERIPH_GPIOF);
}

/**
  * @details This function checks if the GPIOG clock is enabled.
  * @retval HAL_RCC_CLK_DISABLED GPIOG clock is disabled
  * @retval HAL_RCC_CLK_ENABLED  GPIOG clock is enabled
 */
__STATIC_INLINE hal_rcc_clk_status_t HAL_RCC_GPIOG_IsEnabledClock(void)
{
  return (hal_rcc_clk_status_t)LL_AHB4_GRP1_IsEnabledClock(LL_AHB4_GRP1_PERIPH_GPIOG);
}

/**
  * @details This function checks if the GPIOH clock is enabled.
  * @retval HAL_RCC_CLK_DISABLED GPIOH clock is disabled
  * @retval HAL_RCC_CLK_ENABLED  GPIOH clock is enabled
 */
__STATIC_INLINE hal_rcc_clk_status_t HAL_RCC_GPIOH_IsEnabledClock(void)
{
  return (hal_rcc_clk_status_t)LL_AHB4_GRP1_IsEnabledClock(LL_AHB4_GRP1_PERIPH_GPIOH);
}

/**
  * @details This function checks if the GPIOI clock is enabled.
  * @retval HAL_RCC_CLK_DISABLED GPIOI clock is disabled
  * @retval HAL_RCC_CLK_ENABLED  GPIOI clock is enabled
 */
__STATIC_INLINE hal_rcc_clk_status_t HAL_RCC_GPIOI_IsEnabledClock(void)
{
  return (hal_rcc_clk_status_t)LL_AHB4_GRP1_IsEnabledClock(LL_AHB4_GRP1_PERIPH_GPIOI);
}

/**
  * @details This function checks if the CRC clock is enabled.
  * @retval HAL_RCC_CLK_DISABLED CRC clock is disabled
  * @retval HAL_RCC_CLK_ENABLED  CRC clock is enabled
 */
__STATIC_INLINE hal_rcc_clk_status_t HAL_RCC_CRC_IsEnabledClock(void)
{
  return (hal_rcc_clk_status_t)LL_AHB4_GRP1_IsEnabledClock(LL_AHB4_GRP1_PERIPH_CRC);
}

/**
  * @details This function checks if the BKPRAM clock is enabled.
  * @retval HAL_RCC_CLK_DISABLED BKPRAM clock is disabled
  * @retval HAL_RCC_CLK_ENABLED  BKPRAM clock is enabled
 */
__STATIC_INLINE hal_rcc_clk_status_t HAL_RCC_BKPRAM_IsEnabledClock(void)
{
  return (hal_rcc_clk_status_t)LL_AHB4_GRP1_IsEnabledClock(LL_AHB4_GRP1_PERIPH_BKPRAM);
}

/**
  * @}
  */ /* RCC_AHB4_Peripheral_Clock_Enable_Status */

/** @defgroup RCC_AHB5_Peripheral_Clock_Enable_Status AHB5 Peripheral Clock Enabled Status
  * @brief  Check whether the AHB5 peripheral clock is enabled or not.
  * @note   After reset, the peripheral clock (used for registers read/write access) is disabled and
  *         the application software has to enable this clock before using it.
  * @{
  */

/**
  * @details This function checks if the HPDMA1 clock is enabled.
  * @retval HAL_RCC_CLK_DISABLED HPDMA1 clock is disabled
  * @retval HAL_RCC_CLK_ENABLED  HPDMA1 clock is enabled
 */
__STATIC_INLINE hal_rcc_clk_status_t HAL_RCC_HPDMA1_IsEnabledClock(void)
{
  return (hal_rcc_clk_status_t)LL_AHB5_GRP1_IsEnabledClock(LL_AHB5_GRP1_PERIPH_HPDMA1);
}

/**
  * @details This function checks if the FMC clock is enabled.
  * @retval HAL_RCC_CLK_DISABLED FMC clock is disabled
  * @retval HAL_RCC_CLK_ENABLED  FMC clock is enabled
 */
__STATIC_INLINE hal_rcc_clk_status_t HAL_RCC_FMC_IsEnabledClock(void)
{
  return (hal_rcc_clk_status_t)LL_AHB5_GRP1_IsEnabledClock(LL_AHB5_GRP1_PERIPH_FMC);
}

/**
  * @details This function checks if the XSPI1 clock is enabled.
  * @retval HAL_RCC_CLK_DISABLED XSPI1 clock is disabled
  * @retval HAL_RCC_CLK_ENABLED  XSPI1 clock is enabled
 */
__STATIC_INLINE hal_rcc_clk_status_t HAL_RCC_XSPI1_IsEnabledClock(void)
{
  return (hal_rcc_clk_status_t)LL_AHB5_GRP1_IsEnabledClock(LL_AHB5_GRP1_PERIPH_XSPI1);
}

/**
  * @details This function checks if the SDMMC1 clock is enabled.
  * @retval HAL_RCC_CLK_DISABLED SDMMC1 clock is disabled
  * @retval HAL_RCC_CLK_ENABLED  SDMMC1 clock is enabled
 */
__STATIC_INLINE hal_rcc_clk_status_t HAL_RCC_SDMMC1_IsEnabledClock(void)
{
  return (hal_rcc_clk_status_t)LL_AHB5_GRP1_IsEnabledClock(LL_AHB5_GRP1_PERIPH_SDMMC1);
}

/**
  * @details This function checks if the NPU clock is enabled.
  * @retval HAL_RCC_CLK_DISABLED NPU clock is disabled
  * @retval HAL_RCC_CLK_ENABLED  NPU clock is enabled
 */
__STATIC_INLINE hal_rcc_clk_status_t HAL_RCC_NPU_IsEnabledClock(void)
{
  return (hal_rcc_clk_status_t)LL_AHB5_GRP1_IsEnabledClock(LL_AHB5_GRP1_PERIPH_NPU);
}

/**
  * @}
  */ /* RCC_AHB5_Peripheral_Clock_Enable_Status */

/** @defgroup RCC_APB1_Peripheral_Clock_Enable_Status APB1 Peripheral Clock Enabled Status
  * @brief  Check whether the APB1 peripheral clock is enabled or not.
  * @note   After reset, the peripheral clock (used for registers read/write access) is disabled and
  *         the application software has to enable this clock before using it.
  * @{
  */

/**
  * @details This function checks if the TIM2 clock is enabled.
  * @retval HAL_RCC_CLK_DISABLED TIM2 clock is disabled
  * @retval HAL_RCC_CLK_ENABLED  TIM2 clock is enabled
 */
__STATIC_INLINE hal_rcc_clk_status_t HAL_RCC_TIM2_IsEnabledClock(void)
{
  return (hal_rcc_clk_status_t)LL_APB1_GRP1_IsEnabledClock(LL_APB1_GRP1_PERIPH_TIM2);
}

/**
  * @details This function checks if the TIM3 clock is enabled.
  * @retval HAL_RCC_CLK_DISABLED TIM3 clock is disabled
  * @retval HAL_RCC_CLK_ENABLED  TIM3 clock is enabled
 */
__STATIC_INLINE hal_rcc_clk_status_t HAL_RCC_TIM3_IsEnabledClock(void)
{
  return (hal_rcc_clk_status_t)LL_APB1_GRP1_IsEnabledClock(LL_APB1_GRP1_PERIPH_TIM3);
}

/**
  * @details This function checks if the TIM4 clock is enabled.
  * @retval HAL_RCC_CLK_DISABLED TIM4 clock is disabled
  * @retval HAL_RCC_CLK_ENABLED  TIM4 clock is enabled
 */
__STATIC_INLINE hal_rcc_clk_status_t HAL_RCC_TIM4_IsEnabledClock(void)
{
  return (hal_rcc_clk_status_t)LL_APB1_GRP1_IsEnabledClock(LL_APB1_GRP1_PERIPH_TIM4);
}

/**
  * @details This function checks if the TIM5 clock is enabled.
  * @retval HAL_RCC_CLK_DISABLED TIM5 clock is disabled
  * @retval HAL_RCC_CLK_ENABLED  TIM5 clock is enabled
 */
__STATIC_INLINE hal_rcc_clk_status_t HAL_RCC_TIM5_IsEnabledClock(void)
{
  return (hal_rcc_clk_status_t)LL_APB1_GRP1_IsEnabledClock(LL_APB1_GRP1_PERIPH_TIM5);
}

/**
  * @details This function checks if the TIM6 clock is enabled.
  * @retval HAL_RCC_CLK_DISABLED TIM6 clock is disabled
  * @retval HAL_RCC_CLK_ENABLED  TIM6 clock is enabled
 */
__STATIC_INLINE hal_rcc_clk_status_t HAL_RCC_TIM6_IsEnabledClock(void)
{
  return (hal_rcc_clk_status_t)LL_APB1_GRP1_IsEnabledClock(LL_APB1_GRP1_PERIPH_TIM6);
}

/**
  * @details This function checks if the TIM7 clock is enabled.
  * @retval HAL_RCC_CLK_DISABLED TIM7 clock is disabled
  * @retval HAL_RCC_CLK_ENABLED  TIM7 clock is enabled
 */
__STATIC_INLINE hal_rcc_clk_status_t HAL_RCC_TIM7_IsEnabledClock(void)
{
  return (hal_rcc_clk_status_t)LL_APB1_GRP1_IsEnabledClock(LL_APB1_GRP1_PERIPH_TIM7);
}

/**
  * @details This function checks if the TIM12 clock is enabled.
  * @retval HAL_RCC_CLK_DISABLED TIM12 clock is disabled
  * @retval HAL_RCC_CLK_ENABLED  TIM12 clock is enabled
 */
__STATIC_INLINE hal_rcc_clk_status_t HAL_RCC_TIM12_IsEnabledClock(void)
{
  return (hal_rcc_clk_status_t)LL_APB1_GRP1_IsEnabledClock(LL_APB1_GRP1_PERIPH_TIM12);
}

/**
  * @details This function checks if the TIM13 clock is enabled.
  * @retval HAL_RCC_CLK_DISABLED TIM13 clock is disabled
  * @retval HAL_RCC_CLK_ENABLED  TIM13 clock is enabled
 */
__STATIC_INLINE hal_rcc_clk_status_t HAL_RCC_TIM13_IsEnabledClock(void)
{
  return (hal_rcc_clk_status_t)LL_APB1_GRP1_IsEnabledClock(LL_APB1_GRP1_PERIPH_TIM13);
}

/**
  * @details This function checks if the TIM14 clock is enabled.
  * @retval HAL_RCC_CLK_DISABLED TIM14 clock is disabled
  * @retval HAL_RCC_CLK_ENABLED  TIM14 clock is enabled
 */
__STATIC_INLINE hal_rcc_clk_status_t HAL_RCC_TIM14_IsEnabledClock(void)
{
  return (hal_rcc_clk_status_t)LL_APB1_GRP1_IsEnabledClock(LL_APB1_GRP1_PERIPH_TIM14);
}

/**
  * @details This function checks if the LPTIM1 clock is enabled.
  * @retval HAL_RCC_CLK_DISABLED LPTIM1 clock is disabled
  * @retval HAL_RCC_CLK_ENABLED  LPTIM1 clock is enabled
 */
__STATIC_INLINE hal_rcc_clk_status_t HAL_RCC_LPTIM1_IsEnabledClock(void)
{
  return (hal_rcc_clk_status_t)LL_APB1_GRP1_IsEnabledClock(LL_APB1_GRP1_PERIPH_LPTIM1);
}

/**
  * @details This function checks if the WWDG clock is enabled.
  * @retval HAL_RCC_CLK_DISABLED WWDG clock is disabled
  * @retval HAL_RCC_CLK_ENABLED  WWDG clock is enabled
 */
__STATIC_INLINE hal_rcc_clk_status_t HAL_RCC_WWDG_IsEnabledClock(void)
{
  return (hal_rcc_clk_status_t)LL_APB1_GRP1_IsEnabledClock(LL_APB1_GRP1_PERIPH_WWDG);
}

/**
  * @details This function checks if the TIM10 clock is enabled.
  * @retval HAL_RCC_CLK_DISABLED TIM10 clock is disabled
  * @retval HAL_RCC_CLK_ENABLED  TIM10 clock is enabled
 */
__STATIC_INLINE hal_rcc_clk_status_t HAL_RCC_TIM10_IsEnabledClock(void)
{
  return (hal_rcc_clk_status_t)LL_APB1_GRP1_IsEnabledClock(LL_APB1_GRP1_PERIPH_TIM10);
}

/**
  * @details This function checks if the TIM11 clock is enabled.
  * @retval HAL_RCC_CLK_DISABLED TIM11 clock is disabled
  * @retval HAL_RCC_CLK_ENABLED  TIM11 clock is enabled
 */
__STATIC_INLINE hal_rcc_clk_status_t HAL_RCC_TIM11_IsEnabledClock(void)
{
  return (hal_rcc_clk_status_t)LL_APB1_GRP1_IsEnabledClock(LL_APB1_GRP1_PERIPH_TIM11);
}

/**
  * @details This function checks if the SPI2 clock is enabled.
  * @retval HAL_RCC_CLK_DISABLED SPI2 clock is disabled
  * @retval HAL_RCC_CLK_ENABLED  SPI2 clock is enabled
 */
__STATIC_INLINE hal_rcc_clk_status_t HAL_RCC_SPI2_IsEnabledClock(void)
{
  return (hal_rcc_clk_status_t)LL_APB1_GRP1_IsEnabledClock(LL_APB1_GRP1_PERIPH_SPI2);
}

/**
  * @details This function checks if the SPI3 clock is enabled.
  * @retval HAL_RCC_CLK_DISABLED SPI3 clock is disabled
  * @retval HAL_RCC_CLK_ENABLED  SPI3 clock is enabled
 */
__STATIC_INLINE hal_rcc_clk_status_t HAL_RCC_SPI3_IsEnabledClock(void)
{
  return (hal_rcc_clk_status_t)LL_APB1_GRP1_IsEnabledClock(LL_APB1_GRP1_PERIPH_SPI3);
}

/**
  * @details This function checks if the USART2 clock is enabled.
  * @retval HAL_RCC_CLK_DISABLED USART2 clock is disabled
  * @retval HAL_RCC_CLK_ENABLED  USART2 clock is enabled
 */
__STATIC_INLINE hal_rcc_clk_status_t HAL_RCC_USART2_IsEnabledClock(void)
{
  return (hal_rcc_clk_status_t)LL_APB1_GRP1_IsEnabledClock(LL_APB1_GRP1_PERIPH_USART2);
}

/**
  * @details This function checks if the USART3 clock is enabled.
  * @retval HAL_RCC_CLK_DISABLED USART3 clock is disabled
  * @retval HAL_RCC_CLK_ENABLED  USART3 clock is enabled
 */
__STATIC_INLINE hal_rcc_clk_status_t HAL_RCC_USART3_IsEnabledClock(void)
{
  return (hal_rcc_clk_status_t)LL_APB1_GRP1_IsEnabledClock(LL_APB1_GRP1_PERIPH_USART3);
}

/**
  * @details This function checks if the UART4 clock is enabled.
  * @retval HAL_RCC_CLK_DISABLED UART4 clock is disabled
  * @retval HAL_RCC_CLK_ENABLED  UART4 clock is enabled
 */
__STATIC_INLINE hal_rcc_clk_status_t HAL_RCC_UART4_IsEnabledClock(void)
{
  return (hal_rcc_clk_status_t)LL_APB1_GRP1_IsEnabledClock(LL_APB1_GRP1_PERIPH_UART4);
}

/**
  * @details This function checks if the UART5 clock is enabled.
  * @retval HAL_RCC_CLK_DISABLED UART5 clock is disabled
  * @retval HAL_RCC_CLK_ENABLED  UART5 clock is enabled
 */
__STATIC_INLINE hal_rcc_clk_status_t HAL_RCC_UART5_IsEnabledClock(void)
{
  return (hal_rcc_clk_status_t)LL_APB1_GRP1_IsEnabledClock(LL_APB1_GRP1_PERIPH_UART5);
}

/**
  * @details This function checks if the I2C1 clock is enabled.
  * @retval HAL_RCC_CLK_DISABLED I2C1 clock is disabled
  * @retval HAL_RCC_CLK_ENABLED  I2C1 clock is enabled
 */
__STATIC_INLINE hal_rcc_clk_status_t HAL_RCC_I2C1_IsEnabledClock(void)
{
  return (hal_rcc_clk_status_t)LL_APB1_GRP1_IsEnabledClock(LL_APB1_GRP1_PERIPH_I2C1);
}

/**
  * @details This function checks if the I2C2 clock is enabled.
  * @retval HAL_RCC_CLK_DISABLED I2C2 clock is disabled
  * @retval HAL_RCC_CLK_ENABLED  I2C2 clock is enabled
 */
__STATIC_INLINE hal_rcc_clk_status_t HAL_RCC_I2C2_IsEnabledClock(void)
{
  return (hal_rcc_clk_status_t)LL_APB1_GRP1_IsEnabledClock(LL_APB1_GRP1_PERIPH_I2C2);
}

/**
  * @details This function checks if the I2C3 clock is enabled.
  * @retval HAL_RCC_CLK_DISABLED I2C3 clock is disabled
  * @retval HAL_RCC_CLK_ENABLED  I2C3 clock is enabled
 */
__STATIC_INLINE hal_rcc_clk_status_t HAL_RCC_I2C3_IsEnabledClock(void)
{
  return (hal_rcc_clk_status_t)LL_APB1_GRP1_IsEnabledClock(LL_APB1_GRP1_PERIPH_I2C3);
}

/**
  * @details This function checks if the I3C1 clock is enabled.
  * @retval HAL_RCC_CLK_DISABLED I3C1 clock is disabled
  * @retval HAL_RCC_CLK_ENABLED  I3C1 clock is enabled
 */
__STATIC_INLINE hal_rcc_clk_status_t HAL_RCC_I3C1_IsEnabledClock(void)
{
  return (hal_rcc_clk_status_t)LL_APB1_GRP1_IsEnabledClock(LL_APB1_GRP1_PERIPH_I3C1);
}

/**
  * @details This function checks if the UART7 clock is enabled.
  * @retval HAL_RCC_CLK_DISABLED UART7 clock is disabled
  * @retval HAL_RCC_CLK_ENABLED  UART7 clock is enabled
 */
__STATIC_INLINE hal_rcc_clk_status_t HAL_RCC_UART7_IsEnabledClock(void)
{
  return (hal_rcc_clk_status_t)LL_APB1_GRP1_IsEnabledClock(LL_APB1_GRP1_PERIPH_UART7);
}

/**
  * @details This function checks if the UART8 clock is enabled.
  * @retval HAL_RCC_CLK_DISABLED UART8 clock is disabled
  * @retval HAL_RCC_CLK_ENABLED  UART8 clock is enabled
 */
__STATIC_INLINE hal_rcc_clk_status_t HAL_RCC_UART8_IsEnabledClock(void)
{
  return (hal_rcc_clk_status_t)LL_APB1_GRP1_IsEnabledClock(LL_APB1_GRP1_PERIPH_UART8);
}

/**
  * @}
  */ /* RCC_APB1_Peripheral_Clock_Enable_Status */

/** @defgroup RCC_APB1_Peripheral_Clock_Enable_Status APB1 Peripheral Clock Enabled Status
  * @brief  Check whether the APB1 peripheral clock is enabled or not.
  * @note   After reset, the peripheral clock (used for registers read/write access) is disabled and
  *         the application software has to enable this clock before using it.
  * @{
  */

/**
  * @details This function checks if the CRS clock is enabled.
  * @retval HAL_RCC_CLK_DISABLED CRS clock is disabled
  * @retval HAL_RCC_CLK_ENABLED  CRS clock is enabled
 */
__STATIC_INLINE hal_rcc_clk_status_t HAL_RCC_CRS_IsEnabledClock(void)
{
  return (hal_rcc_clk_status_t)LL_APB1_GRP2_IsEnabledClock(LL_APB1_GRP2_PERIPH_CRS);
}

/**
  * @details This function checks if the FDCAN clock is enabled.
  * @retval HAL_RCC_CLK_DISABLED FDCAN clock is disabled
  * @retval HAL_RCC_CLK_ENABLED  FDCAN clock is enabled
 */
__STATIC_INLINE hal_rcc_clk_status_t HAL_RCC_FDCAN_IsEnabledClock(void)
{
  return (hal_rcc_clk_status_t)LL_APB1_GRP2_IsEnabledClock(LL_APB1_GRP2_PERIPH_FDCAN);
}

/**
  * @details This function checks if the UCPD1 clock is enabled.
  * @retval HAL_RCC_CLK_DISABLED UCPD1 clock is disabled
  * @retval HAL_RCC_CLK_ENABLED  UCPD1 clock is enabled
 */
__STATIC_INLINE hal_rcc_clk_status_t HAL_RCC_UCPD1_IsEnabledClock(void)
{
  return (hal_rcc_clk_status_t)LL_APB1_GRP2_IsEnabledClock(LL_APB1_GRP2_PERIPH_UCPD1);
}

/**
  * @}
  */ /* RCC_APB1_Peripheral_Clock_Enable_Status */

/** @defgroup RCC_APB2_Peripheral_Clock_Enable_Status APB2 Peripheral Clock Enabled Status
  * @brief  Check whether the APB2 peripheral clock is enabled or not.
  * @note   After reset, the peripheral clock (used for registers read/write access) is disabled and
  *         the application software has to enable this clock before using it.
  * @{
  */

/**
  * @details This function checks if the TIM1 clock is enabled.
  * @retval HAL_RCC_CLK_DISABLED TIM1 clock is disabled
  * @retval HAL_RCC_CLK_ENABLED  TIM1 clock is enabled
 */
__STATIC_INLINE hal_rcc_clk_status_t HAL_RCC_TIM1_IsEnabledClock(void)
{
  return (hal_rcc_clk_status_t)LL_APB2_GRP1_IsEnabledClock(LL_APB2_GRP1_PERIPH_TIM1);
}

/**
  * @details This function checks if the TIM8 clock is enabled.
  * @retval HAL_RCC_CLK_DISABLED TIM8 clock is disabled
  * @retval HAL_RCC_CLK_ENABLED  TIM8 clock is enabled
 */
__STATIC_INLINE hal_rcc_clk_status_t HAL_RCC_TIM8_IsEnabledClock(void)
{
  return (hal_rcc_clk_status_t)LL_APB2_GRP1_IsEnabledClock(LL_APB2_GRP1_PERIPH_TIM8);
}

/**
  * @details This function checks if the TIM20 clock is enabled.
  * @retval HAL_RCC_CLK_DISABLED TIM20 clock is disabled
  * @retval HAL_RCC_CLK_ENABLED  TIM20 clock is enabled
 */
__STATIC_INLINE hal_rcc_clk_status_t HAL_RCC_TIM20_IsEnabledClock(void)
{
  return (hal_rcc_clk_status_t)LL_APB2_GRP1_IsEnabledClock(LL_APB2_GRP1_PERIPH_TIM20);
}

/**
  * @details This function checks if the USART1 clock is enabled.
  * @retval HAL_RCC_CLK_DISABLED USART1 clock is disabled
  * @retval HAL_RCC_CLK_ENABLED  USART1 clock is enabled
 */
__STATIC_INLINE hal_rcc_clk_status_t HAL_RCC_USART1_IsEnabledClock(void)
{
  return (hal_rcc_clk_status_t)LL_APB2_GRP1_IsEnabledClock(LL_APB2_GRP1_PERIPH_USART1);
}

/**
  * @details This function checks if the USART6 clock is enabled.
  * @retval HAL_RCC_CLK_DISABLED USART6 clock is disabled
  * @retval HAL_RCC_CLK_ENABLED  USART6 clock is enabled
 */
__STATIC_INLINE hal_rcc_clk_status_t HAL_RCC_USART6_IsEnabledClock(void)
{
  return (hal_rcc_clk_status_t)LL_APB2_GRP1_IsEnabledClock(LL_APB2_GRP1_PERIPH_USART6);
}

/**
  * @details This function checks if the UART9 clock is enabled.
  * @retval HAL_RCC_CLK_DISABLED UART9 clock is disabled
  * @retval HAL_RCC_CLK_ENABLED  UART9 clock is enabled
 */
__STATIC_INLINE hal_rcc_clk_status_t HAL_RCC_UART9_IsEnabledClock(void)
{
  return (hal_rcc_clk_status_t)LL_APB2_GRP1_IsEnabledClock(LL_APB2_GRP1_PERIPH_UART9);
}

/**
  * @details This function checks if the USART10 clock is enabled.
  * @retval HAL_RCC_CLK_DISABLED USART10 clock is disabled
  * @retval HAL_RCC_CLK_ENABLED  USART10 clock is enabled
 */
__STATIC_INLINE hal_rcc_clk_status_t HAL_RCC_USART10_IsEnabledClock(void)
{
  return (hal_rcc_clk_status_t)LL_APB2_GRP1_IsEnabledClock(LL_APB2_GRP1_PERIPH_USART10);
}

/**
  * @details This function checks if the SPI1 clock is enabled.
  * @retval HAL_RCC_CLK_DISABLED SPI1 clock is disabled
  * @retval HAL_RCC_CLK_ENABLED  SPI1 clock is enabled
 */
__STATIC_INLINE hal_rcc_clk_status_t HAL_RCC_SPI1_IsEnabledClock(void)
{
  return (hal_rcc_clk_status_t)LL_APB2_GRP1_IsEnabledClock(LL_APB2_GRP1_PERIPH_SPI1);
}

/**
  * @details This function checks if the SPI4 clock is enabled.
  * @retval HAL_RCC_CLK_DISABLED SPI4 clock is disabled
  * @retval HAL_RCC_CLK_ENABLED  SPI4 clock is enabled
 */
__STATIC_INLINE hal_rcc_clk_status_t HAL_RCC_SPI4_IsEnabledClock(void)
{
  return (hal_rcc_clk_status_t)LL_APB2_GRP1_IsEnabledClock(LL_APB2_GRP1_PERIPH_SPI4);
}

/**
  * @details This function checks if the TIM15 clock is enabled.
  * @retval HAL_RCC_CLK_DISABLED TIM15 clock is disabled
  * @retval HAL_RCC_CLK_ENABLED  TIM15 clock is enabled
 */
__STATIC_INLINE hal_rcc_clk_status_t HAL_RCC_TIM15_IsEnabledClock(void)
{
  return (hal_rcc_clk_status_t)LL_APB2_GRP1_IsEnabledClock(LL_APB2_GRP1_PERIPH_TIM15);
}

/**
  * @details This function checks if the TIM16 clock is enabled.
  * @retval HAL_RCC_CLK_DISABLED TIM16 clock is disabled
  * @retval HAL_RCC_CLK_ENABLED  TIM16 clock is enabled
 */
__STATIC_INLINE hal_rcc_clk_status_t HAL_RCC_TIM16_IsEnabledClock(void)
{
  return (hal_rcc_clk_status_t)LL_APB2_GRP1_IsEnabledClock(LL_APB2_GRP1_PERIPH_TIM16);
}

/**
  * @details This function checks if the TIM17 clock is enabled.
  * @retval HAL_RCC_CLK_DISABLED TIM17 clock is disabled
  * @retval HAL_RCC_CLK_ENABLED  TIM17 clock is enabled
 */
__STATIC_INLINE hal_rcc_clk_status_t HAL_RCC_TIM17_IsEnabledClock(void)
{
  return (hal_rcc_clk_status_t)LL_APB2_GRP1_IsEnabledClock(LL_APB2_GRP1_PERIPH_TIM17);
}

/**
  * @details This function checks if the TIM9 clock is enabled.
  * @retval HAL_RCC_CLK_DISABLED TIM9 clock is disabled
  * @retval HAL_RCC_CLK_ENABLED  TIM9 clock is enabled
 */
__STATIC_INLINE hal_rcc_clk_status_t HAL_RCC_TIM9_IsEnabledClock(void)
{
  return (hal_rcc_clk_status_t)LL_APB2_GRP1_IsEnabledClock(LL_APB2_GRP1_PERIPH_TIM9);
}

/**
  * @details This function checks if the SPI5 clock is enabled.
  * @retval HAL_RCC_CLK_DISABLED SPI5 clock is disabled
  * @retval HAL_RCC_CLK_ENABLED  SPI5 clock is enabled
 */
__STATIC_INLINE hal_rcc_clk_status_t HAL_RCC_SPI5_IsEnabledClock(void)
{
  return (hal_rcc_clk_status_t)LL_APB2_GRP1_IsEnabledClock(LL_APB2_GRP1_PERIPH_SPI5);
}

/**
  * @details This function checks if the HRTIM1 clock is enabled.
  * @retval HAL_RCC_CLK_DISABLED HRTIM1 clock is disabled
  * @retval HAL_RCC_CLK_ENABLED  HRTIM1 clock is enabled
 */
__STATIC_INLINE hal_rcc_clk_status_t HAL_RCC_HRTIM1_IsEnabledClock(void)
{
  return (hal_rcc_clk_status_t)LL_APB2_GRP1_IsEnabledClock(LL_APB2_GRP1_PERIPH_HRTIM1);
}

/**
  * @details This function checks if the HRTIM2 clock is enabled.
  * @retval HAL_RCC_CLK_DISABLED HRTIM2 clock is disabled
  * @retval HAL_RCC_CLK_ENABLED  HRTIM2 clock is enabled
 */
__STATIC_INLINE hal_rcc_clk_status_t HAL_RCC_HRTIM2_IsEnabledClock(void)
{
  return (hal_rcc_clk_status_t)LL_APB2_GRP1_IsEnabledClock(LL_APB2_GRP1_PERIPH_HRTIM2);
}

/**
  * @}
  */ /* RCC_APB2_Peripheral_Clock_Enable_Status */

/** @defgroup RCC_APB4_Peripheral_Clock_Enable_Status APB4 Peripheral Clock Enabled Status
  * @brief  Check whether the APB4 peripheral clock is enabled or not.
  * @note   After reset, the peripheral clock (used for registers read/write access) is disabled and
  *         the application software has to enable this clock before using it.
  * @{
  */

/**
  * @details This function checks if the SBS clock is enabled.
  * @retval HAL_RCC_CLK_DISABLED SBS clock is disabled
  * @retval HAL_RCC_CLK_ENABLED  SBS clock is enabled
 */
__STATIC_INLINE hal_rcc_clk_status_t HAL_RCC_SBS_IsEnabledClock(void)
{
  return (hal_rcc_clk_status_t)LL_APB4_GRP1_IsEnabledClock(LL_APB4_GRP1_PERIPH_SBS);
}

/**
  * @details This function checks if the LPUART1 clock is enabled.
  * @retval HAL_RCC_CLK_DISABLED LPUART1 clock is disabled
  * @retval HAL_RCC_CLK_ENABLED  LPUART1 clock is enabled
 */
__STATIC_INLINE hal_rcc_clk_status_t HAL_RCC_LPUART1_IsEnabledClock(void)
{
  return (hal_rcc_clk_status_t)LL_APB4_GRP1_IsEnabledClock(LL_APB4_GRP1_PERIPH_LPUART1);
}

/**
  * @details This function checks if the SPI6 clock is enabled.
  * @retval HAL_RCC_CLK_DISABLED SPI6 clock is disabled
  * @retval HAL_RCC_CLK_ENABLED  SPI6 clock is enabled
 */
__STATIC_INLINE hal_rcc_clk_status_t HAL_RCC_SPI6_IsEnabledClock(void)
{
  return (hal_rcc_clk_status_t)LL_APB4_GRP1_IsEnabledClock(LL_APB4_GRP1_PERIPH_SPI6);
}

/**
  * @details This function checks if the LPTIM2 clock is enabled.
  * @retval HAL_RCC_CLK_DISABLED LPTIM2 clock is disabled
  * @retval HAL_RCC_CLK_ENABLED  LPTIM2 clock is enabled
 */
__STATIC_INLINE hal_rcc_clk_status_t HAL_RCC_LPTIM2_IsEnabledClock(void)
{
  return (hal_rcc_clk_status_t)LL_APB4_GRP1_IsEnabledClock(LL_APB4_GRP1_PERIPH_LPTIM2);
}

/**
  * @details This function checks if the LPTIM3 clock is enabled.
  * @retval HAL_RCC_CLK_DISABLED LPTIM3 clock is disabled
  * @retval HAL_RCC_CLK_ENABLED  LPTIM3 clock is enabled
 */
__STATIC_INLINE hal_rcc_clk_status_t HAL_RCC_LPTIM3_IsEnabledClock(void)
{
  return (hal_rcc_clk_status_t)LL_APB4_GRP1_IsEnabledClock(LL_APB4_GRP1_PERIPH_LPTIM3);
}

/**
  * @details This function checks if the LPTIM4 clock is enabled.
  * @retval HAL_RCC_CLK_DISABLED LPTIM4 clock is disabled
  * @retval HAL_RCC_CLK_ENABLED  LPTIM4 clock is enabled
 */
__STATIC_INLINE hal_rcc_clk_status_t HAL_RCC_LPTIM4_IsEnabledClock(void)
{
  return (hal_rcc_clk_status_t)LL_APB4_GRP1_IsEnabledClock(LL_APB4_GRP1_PERIPH_LPTIM4);
}

/**
  * @details This function checks if the LPTIM5 clock is enabled.
  * @retval HAL_RCC_CLK_DISABLED LPTIM5 clock is disabled
  * @retval HAL_RCC_CLK_ENABLED  LPTIM5 clock is enabled
 */
__STATIC_INLINE hal_rcc_clk_status_t HAL_RCC_LPTIM5_IsEnabledClock(void)
{
  return (hal_rcc_clk_status_t)LL_APB4_GRP1_IsEnabledClock(LL_APB4_GRP1_PERIPH_LPTIM5);
}

/**
  * @details This function checks if the VREF clock is enabled.
  * @retval HAL_RCC_CLK_DISABLED VREF clock is disabled
  * @retval HAL_RCC_CLK_ENABLED  VREF clock is enabled
 */
__STATIC_INLINE hal_rcc_clk_status_t HAL_RCC_VREF_IsEnabledClock(void)
{
  return (hal_rcc_clk_status_t)LL_APB4_GRP1_IsEnabledClock(LL_APB4_GRP1_PERIPH_VREF);
}

/**
  * @details This function checks if the RTCAPB clock is enabled.
  * @retval HAL_RCC_CLK_DISABLED RTCAPB clock is disabled
  * @retval HAL_RCC_CLK_ENABLED  RTCAPB clock is enabled
 */
__STATIC_INLINE hal_rcc_clk_status_t HAL_RCC_RTCAPB_IsEnabledClock(void)
{
  return (hal_rcc_clk_status_t)LL_APB4_GRP1_IsEnabledClock(LL_APB4_GRP1_PERIPH_RTCAPB);
}

/**
  * @details This function checks if the DTS clock is enabled.
  * @retval HAL_RCC_CLK_DISABLED DTS clock is disabled
  * @retval HAL_RCC_CLK_ENABLED  DTS clock is enabled
 */
__STATIC_INLINE hal_rcc_clk_status_t HAL_RCC_DTS_IsEnabledClock(void)
{
  return (hal_rcc_clk_status_t)LL_APB4_GRP1_IsEnabledClock(LL_APB4_GRP1_PERIPH_DTS);
}

/**
  * @details This function checks if the COMP12 clock is enabled.
  * @retval HAL_RCC_CLK_DISABLED COMP12 clock is disabled
  * @retval HAL_RCC_CLK_ENABLED  COMP12 clock is enabled
 */
__STATIC_INLINE hal_rcc_clk_status_t HAL_RCC_COMP12_IsEnabledClock(void)
{
  return (hal_rcc_clk_status_t)LL_APB4_GRP1_IsEnabledClock(LL_APB4_GRP1_PERIPH_COMP12);
}

/**
  * @details This function checks if the COMP34 clock is enabled.
  * @retval HAL_RCC_CLK_DISABLED COMP34 clock is disabled
  * @retval HAL_RCC_CLK_ENABLED  COMP34 clock is enabled
 */
__STATIC_INLINE hal_rcc_clk_status_t HAL_RCC_COMP34_IsEnabledClock(void)
{
  return (hal_rcc_clk_status_t)LL_APB4_GRP1_IsEnabledClock(LL_APB4_GRP1_PERIPH_COMP34);
}

/**
  * @details This function checks if the COMP56 clock is enabled.
  * @retval HAL_RCC_CLK_DISABLED COMP56 clock is disabled
  * @retval HAL_RCC_CLK_ENABLED  COMP56 clock is enabled
 */
__STATIC_INLINE hal_rcc_clk_status_t HAL_RCC_COMP56_IsEnabledClock(void)
{
  return (hal_rcc_clk_status_t)LL_APB4_GRP1_IsEnabledClock(LL_APB4_GRP1_PERIPH_COMP56);
}

/**
  * @details This function checks if the COMP78 clock is enabled.
  * @retval HAL_RCC_CLK_DISABLED COMP78 clock is disabled
  * @retval HAL_RCC_CLK_ENABLED  COMP78 clock is enabled
 */
__STATIC_INLINE hal_rcc_clk_status_t HAL_RCC_COMP78_IsEnabledClock(void)
{
  return (hal_rcc_clk_status_t)LL_APB4_GRP1_IsEnabledClock(LL_APB4_GRP1_PERIPH_COMP78);
}

/**
  * @}
  */ /* RCC_APB4_Peripheral_Clock_Enable_Status */

/** @defgroup RCC_CKG_Peripheral_Clock_Enable_Status CKG Peripheral Clock Enabled Status
  * @brief  Check whether the CKG peripheral clock is enabled or not.
  * @note   After reset, the peripheral clock (used for registers read/write access) is disabled and
  *         the application software has to enable this clock before using it.
  * @{
  */

/**
  * @}
  */ /* RCC_CKG_Peripheral_Clock_Enable_Status */

/** @defgroup RCC_AHB1_Reset AHB1 PeripheralReset
  * @brief  AHB1 peripheral reset.
  * @{
  */

/**
  * @details This function resets the HSP peripheral.
  */
__STATIC_INLINE void HAL_RCC_HSP_Reset(void)
{
  LL_AHB1_GRP1_ForceReset(LL_AHB1_GRP1_PERIPH_HSP);
  LL_AHB1_GRP1_ReleaseReset(LL_AHB1_GRP1_PERIPH_HSP);
}

/**
  * @details This function resets the GPDMA1 peripheral.
  */
__STATIC_INLINE void HAL_RCC_GPDMA1_Reset(void)
{
  LL_AHB1_GRP1_ForceReset(LL_AHB1_GRP1_PERIPH_GPDMA1);
  LL_AHB1_GRP1_ReleaseReset(LL_AHB1_GRP1_PERIPH_GPDMA1);
}

/**
  * @details This function resets the OTGFS peripheral.
  */
__STATIC_INLINE void HAL_RCC_OTGFS_Reset(void)
{
  LL_AHB1_GRP1_ForceReset(LL_AHB1_GRP1_PERIPH_OTGFS);
  LL_AHB1_GRP1_ReleaseReset(LL_AHB1_GRP1_PERIPH_OTGFS);
}

/**
  * @details This function resets the ADF1 peripheral.
  */
__STATIC_INLINE void HAL_RCC_ADF1_Reset(void)
{
  LL_AHB1_GRP1_ForceReset(LL_AHB1_GRP1_PERIPH_ADF1);
  LL_AHB1_GRP1_ReleaseReset(LL_AHB1_GRP1_PERIPH_ADF1);
}

/**
  * @}
  */ /* RCC_AHB1_Reset */

/** @defgroup RCC_AHB2_Reset AHB2 PeripheralReset
  * @brief  AHB2 peripheral reset.
  * @{
  */

/**
  * @details This function resets the CORDIC peripheral.
  */
__STATIC_INLINE void HAL_RCC_CORDIC_Reset(void)
{
  LL_AHB2_GRP1_ForceReset(LL_AHB2_GRP1_PERIPH_CORDIC);
  LL_AHB2_GRP1_ReleaseReset(LL_AHB2_GRP1_PERIPH_CORDIC);
}

/**
  * @details This function resets the FMAC peripheral.
  */
__STATIC_INLINE void HAL_RCC_FMAC_Reset(void)
{
  LL_AHB2_GRP1_ForceReset(LL_AHB2_GRP1_PERIPH_FMAC1);
  LL_AHB2_GRP1_ReleaseReset(LL_AHB2_GRP1_PERIPH_FMAC1);
}

/**
  * @}
  */ /* RCC_AHB2_Reset */

/** @defgroup RCC_AHB3_Reset AHB3 PeripheralReset
  * @brief  AHB3 peripheral reset.
  * @{
  */

/**
  * @details This function resets the RNG peripheral.
  */
__STATIC_INLINE void HAL_RCC_RNG_Reset(void)
{
  LL_AHB3_GRP1_ForceReset(LL_AHB3_GRP1_PERIPH_RNG);
  LL_AHB3_GRP1_ReleaseReset(LL_AHB3_GRP1_PERIPH_RNG);
}

/**
  * @details This function resets the HASH peripheral.
  */
__STATIC_INLINE void HAL_RCC_HASH_Reset(void)
{
  LL_AHB3_GRP1_ForceReset(LL_AHB3_GRP1_PERIPH_HASH);
  LL_AHB3_GRP1_ReleaseReset(LL_AHB3_GRP1_PERIPH_HASH);
}

/**
  * @details This function resets the ADC12 peripheral.
  */
__STATIC_INLINE void HAL_RCC_ADC12_Reset(void)
{
  LL_AHB3_GRP1_ForceReset(LL_AHB3_GRP1_PERIPH_ADC12);
  LL_AHB3_GRP1_ReleaseReset(LL_AHB3_GRP1_PERIPH_ADC12);
}

/**
  * @details This function resets the ADC34 peripheral.
  */
__STATIC_INLINE void HAL_RCC_ADC34_Reset(void)
{
  LL_AHB3_GRP1_ForceReset(LL_AHB3_GRP1_PERIPH_ADC34);
  LL_AHB3_GRP1_ReleaseReset(LL_AHB3_GRP1_PERIPH_ADC34);
}

/**
  * @details This function resets the DAC1 peripheral.
  */
__STATIC_INLINE void HAL_RCC_DAC1_Reset(void)
{
  LL_AHB3_GRP1_ForceReset(LL_AHB3_GRP1_PERIPH_DAC1);
  LL_AHB3_GRP1_ReleaseReset(LL_AHB3_GRP1_PERIPH_DAC1);
}

/**
  * @details This function resets the DAC2 peripheral.
  */
__STATIC_INLINE void HAL_RCC_DAC2_Reset(void)
{
  LL_AHB3_GRP1_ForceReset(LL_AHB3_GRP1_PERIPH_DAC2);
  LL_AHB3_GRP1_ReleaseReset(LL_AHB3_GRP1_PERIPH_DAC2);
}

/**
  * @details This function resets the DAC3 peripheral.
  */
__STATIC_INLINE void HAL_RCC_DAC3_Reset(void)
{
  LL_AHB3_GRP1_ForceReset(LL_AHB3_GRP1_PERIPH_DAC3);
  LL_AHB3_GRP1_ReleaseReset(LL_AHB3_GRP1_PERIPH_DAC3);
}

/**
  * @details This function resets the DAC4 peripheral.
  */
__STATIC_INLINE void HAL_RCC_DAC4_Reset(void)
{
  LL_AHB3_GRP1_ForceReset(LL_AHB3_GRP1_PERIPH_DAC4);
  LL_AHB3_GRP1_ReleaseReset(LL_AHB3_GRP1_PERIPH_DAC4);
}

/**
  * @}
  */ /* RCC_AHB3_Reset */

/** @defgroup RCC_AHB4_Reset AHB4 PeripheralReset
  * @brief  AHB4 peripheral reset.
  * @{
  */

/**
  * @details This function resets the GPIOA peripheral.
  */
__STATIC_INLINE void HAL_RCC_GPIOA_Reset(void)
{
  LL_AHB4_GRP1_ForceReset(LL_AHB4_GRP1_PERIPH_GPIOA);
  LL_AHB4_GRP1_ReleaseReset(LL_AHB4_GRP1_PERIPH_GPIOA);
}

/**
  * @details This function resets the GPIOB peripheral.
  */
__STATIC_INLINE void HAL_RCC_GPIOB_Reset(void)
{
  LL_AHB4_GRP1_ForceReset(LL_AHB4_GRP1_PERIPH_GPIOB);
  LL_AHB4_GRP1_ReleaseReset(LL_AHB4_GRP1_PERIPH_GPIOB);
}

/**
  * @details This function resets the GPIOC peripheral.
  */
__STATIC_INLINE void HAL_RCC_GPIOC_Reset(void)
{
  LL_AHB4_GRP1_ForceReset(LL_AHB4_GRP1_PERIPH_GPIOC);
  LL_AHB4_GRP1_ReleaseReset(LL_AHB4_GRP1_PERIPH_GPIOC);
}

/**
  * @details This function resets the GPIOD peripheral.
  */
__STATIC_INLINE void HAL_RCC_GPIOD_Reset(void)
{
  LL_AHB4_GRP1_ForceReset(LL_AHB4_GRP1_PERIPH_GPIOD);
  LL_AHB4_GRP1_ReleaseReset(LL_AHB4_GRP1_PERIPH_GPIOD);
}

/**
  * @details This function resets the GPIOE peripheral.
  */
__STATIC_INLINE void HAL_RCC_GPIOE_Reset(void)
{
  LL_AHB4_GRP1_ForceReset(LL_AHB4_GRP1_PERIPH_GPIOE);
  LL_AHB4_GRP1_ReleaseReset(LL_AHB4_GRP1_PERIPH_GPIOE);
}

/**
  * @details This function resets the GPIOF peripheral.
  */
__STATIC_INLINE void HAL_RCC_GPIOF_Reset(void)
{
  LL_AHB4_GRP1_ForceReset(LL_AHB4_GRP1_PERIPH_GPIOF);
  LL_AHB4_GRP1_ReleaseReset(LL_AHB4_GRP1_PERIPH_GPIOF);
}

/**
  * @details This function resets the GPIOG peripheral.
  */
__STATIC_INLINE void HAL_RCC_GPIOG_Reset(void)
{
  LL_AHB4_GRP1_ForceReset(LL_AHB4_GRP1_PERIPH_GPIOG);
  LL_AHB4_GRP1_ReleaseReset(LL_AHB4_GRP1_PERIPH_GPIOG);
}

/**
  * @details This function resets the GPIOH peripheral.
  */
__STATIC_INLINE void HAL_RCC_GPIOH_Reset(void)
{
  LL_AHB4_GRP1_ForceReset(LL_AHB4_GRP1_PERIPH_GPIOH);
  LL_AHB4_GRP1_ReleaseReset(LL_AHB4_GRP1_PERIPH_GPIOH);
}

/**
  * @details This function resets the GPIOI peripheral.
  */
__STATIC_INLINE void HAL_RCC_GPIOI_Reset(void)
{
  LL_AHB4_GRP1_ForceReset(LL_AHB4_GRP1_PERIPH_GPIOI);
  LL_AHB4_GRP1_ReleaseReset(LL_AHB4_GRP1_PERIPH_GPIOI);
}

/**
  * @details This function resets the CRC peripheral.
  */
__STATIC_INLINE void HAL_RCC_CRC_Reset(void)
{
  LL_AHB4_GRP1_ForceReset(LL_AHB4_GRP1_PERIPH_CRC);
  LL_AHB4_GRP1_ReleaseReset(LL_AHB4_GRP1_PERIPH_CRC);
}

/**
  * @}
  */ /* RCC_AHB4_Reset */

/** @defgroup RCC_AHB5_Reset AHB5 PeripheralReset
  * @brief  AHB5 peripheral reset.
  * @{
  */

/**
  * @details This function resets the HPDMA1 peripheral.
  */
__STATIC_INLINE void HAL_RCC_HPDMA1_Reset(void)
{
  LL_AHB5_GRP1_ForceReset(LL_AHB5_GRP1_PERIPH_HPDMA1);
  LL_AHB5_GRP1_ReleaseReset(LL_AHB5_GRP1_PERIPH_HPDMA1);
}

/**
  * @details This function resets the FMC peripheral.
  */
__STATIC_INLINE void HAL_RCC_FMC_Reset(void)
{
  LL_AHB5_GRP1_ForceReset(LL_AHB5_GRP1_PERIPH_FMC);
  LL_AHB5_GRP1_ReleaseReset(LL_AHB5_GRP1_PERIPH_FMC);
}

/**
  * @details This function resets the XSPI1 peripheral.
  */
__STATIC_INLINE void HAL_RCC_XSPI1_Reset(void)
{
  LL_AHB5_GRP1_ForceReset(LL_AHB5_GRP1_PERIPH_XSPI1);
  LL_AHB5_GRP1_ReleaseReset(LL_AHB5_GRP1_PERIPH_XSPI1);
}

/**
  * @details This function resets the SDMMC1 peripheral.
  */
__STATIC_INLINE void HAL_RCC_SDMMC1_Reset(void)
{
  LL_AHB5_GRP1_ForceReset(LL_AHB5_GRP1_PERIPH_SDMMC1);
  LL_AHB5_GRP1_ReleaseReset(LL_AHB5_GRP1_PERIPH_SDMMC1);
}

/**
  * @details This function resets the NPU peripheral.
  */
__STATIC_INLINE void HAL_RCC_NPU_Reset(void)
{
  LL_AHB5_GRP1_ForceReset(LL_AHB5_GRP1_PERIPH_NPU);
  LL_AHB5_GRP1_ReleaseReset(LL_AHB5_GRP1_PERIPH_NPU);
}

/**
  * @}
  */ /* RCC_AHB5_Reset */

/** @defgroup RCC_APB1_Reset APB1 PeripheralReset
  * @brief  APB1 peripheral reset.
  * @{
  */

/**
  * @details This function resets the TIM2 peripheral.
  */
__STATIC_INLINE void HAL_RCC_TIM2_Reset(void)
{
  LL_APB1_GRP1_ForceReset(LL_APB1_GRP1_PERIPH_TIM2);
  LL_APB1_GRP1_ReleaseReset(LL_APB1_GRP1_PERIPH_TIM2);
}

/**
  * @details This function resets the TIM3 peripheral.
  */
__STATIC_INLINE void HAL_RCC_TIM3_Reset(void)
{
  LL_APB1_GRP1_ForceReset(LL_APB1_GRP1_PERIPH_TIM3);
  LL_APB1_GRP1_ReleaseReset(LL_APB1_GRP1_PERIPH_TIM3);
}

/**
  * @details This function resets the TIM4 peripheral.
  */
__STATIC_INLINE void HAL_RCC_TIM4_Reset(void)
{
  LL_APB1_GRP1_ForceReset(LL_APB1_GRP1_PERIPH_TIM4);
  LL_APB1_GRP1_ReleaseReset(LL_APB1_GRP1_PERIPH_TIM4);
}

/**
  * @details This function resets the TIM5 peripheral.
  */
__STATIC_INLINE void HAL_RCC_TIM5_Reset(void)
{
  LL_APB1_GRP1_ForceReset(LL_APB1_GRP1_PERIPH_TIM5);
  LL_APB1_GRP1_ReleaseReset(LL_APB1_GRP1_PERIPH_TIM5);
}

/**
  * @details This function resets the TIM6 peripheral.
  */
__STATIC_INLINE void HAL_RCC_TIM6_Reset(void)
{
  LL_APB1_GRP1_ForceReset(LL_APB1_GRP1_PERIPH_TIM6);
  LL_APB1_GRP1_ReleaseReset(LL_APB1_GRP1_PERIPH_TIM6);
}

/**
  * @details This function resets the TIM7 peripheral.
  */
__STATIC_INLINE void HAL_RCC_TIM7_Reset(void)
{
  LL_APB1_GRP1_ForceReset(LL_APB1_GRP1_PERIPH_TIM7);
  LL_APB1_GRP1_ReleaseReset(LL_APB1_GRP1_PERIPH_TIM7);
}

/**
  * @details This function resets the TIM12 peripheral.
  */
__STATIC_INLINE void HAL_RCC_TIM12_Reset(void)
{
  LL_APB1_GRP1_ForceReset(LL_APB1_GRP1_PERIPH_TIM12);
  LL_APB1_GRP1_ReleaseReset(LL_APB1_GRP1_PERIPH_TIM12);
}

/**
  * @details This function resets the TIM13 peripheral.
  */
__STATIC_INLINE void HAL_RCC_TIM13_Reset(void)
{
  LL_APB1_GRP1_ForceReset(LL_APB1_GRP1_PERIPH_TIM13);
  LL_APB1_GRP1_ReleaseReset(LL_APB1_GRP1_PERIPH_TIM13);
}

/**
  * @details This function resets the TIM14 peripheral.
  */
__STATIC_INLINE void HAL_RCC_TIM14_Reset(void)
{
  LL_APB1_GRP1_ForceReset(LL_APB1_GRP1_PERIPH_TIM14);
  LL_APB1_GRP1_ReleaseReset(LL_APB1_GRP1_PERIPH_TIM14);
}

/**
  * @details This function resets the LPTIM1 peripheral.
  */
__STATIC_INLINE void HAL_RCC_LPTIM1_Reset(void)
{
  LL_APB1_GRP1_ForceReset(LL_APB1_GRP1_PERIPH_LPTIM1);
  LL_APB1_GRP1_ReleaseReset(LL_APB1_GRP1_PERIPH_LPTIM1);
}

/**
  * @details This function resets the TIM10 peripheral.
  */
__STATIC_INLINE void HAL_RCC_TIM10_Reset(void)
{
  LL_APB1_GRP1_ForceReset(LL_APB1_GRP1_PERIPH_TIM10);
  LL_APB1_GRP1_ReleaseReset(LL_APB1_GRP1_PERIPH_TIM10);
}

/**
  * @details This function resets the TIM11 peripheral.
  */
__STATIC_INLINE void HAL_RCC_TIM11_Reset(void)
{
  LL_APB1_GRP1_ForceReset(LL_APB1_GRP1_PERIPH_TIM11);
  LL_APB1_GRP1_ReleaseReset(LL_APB1_GRP1_PERIPH_TIM11);
}

/**
  * @details This function resets the SPI2 peripheral.
  */
__STATIC_INLINE void HAL_RCC_SPI2_Reset(void)
{
  LL_APB1_GRP1_ForceReset(LL_APB1_GRP1_PERIPH_SPI2);
  LL_APB1_GRP1_ReleaseReset(LL_APB1_GRP1_PERIPH_SPI2);
}

/**
  * @details This function resets the SPI3 peripheral.
  */
__STATIC_INLINE void HAL_RCC_SPI3_Reset(void)
{
  LL_APB1_GRP1_ForceReset(LL_APB1_GRP1_PERIPH_SPI3);
  LL_APB1_GRP1_ReleaseReset(LL_APB1_GRP1_PERIPH_SPI3);
}

/**
  * @details This function resets the USART2 peripheral.
  */
__STATIC_INLINE void HAL_RCC_USART2_Reset(void)
{
  LL_APB1_GRP1_ForceReset(LL_APB1_GRP1_PERIPH_USART2);
  LL_APB1_GRP1_ReleaseReset(LL_APB1_GRP1_PERIPH_USART2);
}

/**
  * @details This function resets the USART3 peripheral.
  */
__STATIC_INLINE void HAL_RCC_USART3_Reset(void)
{
  LL_APB1_GRP1_ForceReset(LL_APB1_GRP1_PERIPH_USART3);
  LL_APB1_GRP1_ReleaseReset(LL_APB1_GRP1_PERIPH_USART3);
}

/**
  * @details This function resets the UART4 peripheral.
  */
__STATIC_INLINE void HAL_RCC_UART4_Reset(void)
{
  LL_APB1_GRP1_ForceReset(LL_APB1_GRP1_PERIPH_UART4);
  LL_APB1_GRP1_ReleaseReset(LL_APB1_GRP1_PERIPH_UART4);
}

/**
  * @details This function resets the UART5 peripheral.
  */
__STATIC_INLINE void HAL_RCC_UART5_Reset(void)
{
  LL_APB1_GRP1_ForceReset(LL_APB1_GRP1_PERIPH_UART5);
  LL_APB1_GRP1_ReleaseReset(LL_APB1_GRP1_PERIPH_UART5);
}

/**
  * @details This function resets the I2C1 peripheral.
  */
__STATIC_INLINE void HAL_RCC_I2C1_Reset(void)
{
  LL_APB1_GRP1_ForceReset(LL_APB1_GRP1_PERIPH_I2C1);
  LL_APB1_GRP1_ReleaseReset(LL_APB1_GRP1_PERIPH_I2C1);
}

/**
  * @details This function resets the I2C2 peripheral.
  */
__STATIC_INLINE void HAL_RCC_I2C2_Reset(void)
{
  LL_APB1_GRP1_ForceReset(LL_APB1_GRP1_PERIPH_I2C2);
  LL_APB1_GRP1_ReleaseReset(LL_APB1_GRP1_PERIPH_I2C2);
}

/**
  * @details This function resets the I2C3 peripheral.
  */
__STATIC_INLINE void HAL_RCC_I2C3_Reset(void)
{
  LL_APB1_GRP1_ForceReset(LL_APB1_GRP1_PERIPH_I2C3);
  LL_APB1_GRP1_ReleaseReset(LL_APB1_GRP1_PERIPH_I2C3);
}

/**
  * @details This function resets the I3C1 peripheral.
  */
__STATIC_INLINE void HAL_RCC_I3C1_Reset(void)
{
  LL_APB1_GRP1_ForceReset(LL_APB1_GRP1_PERIPH_I3C1);
  LL_APB1_GRP1_ReleaseReset(LL_APB1_GRP1_PERIPH_I3C1);
}

/**
  * @details This function resets the UART7 peripheral.
  */
__STATIC_INLINE void HAL_RCC_UART7_Reset(void)
{
  LL_APB1_GRP1_ForceReset(LL_APB1_GRP1_PERIPH_UART7);
  LL_APB1_GRP1_ReleaseReset(LL_APB1_GRP1_PERIPH_UART7);
}

/**
  * @details This function resets the UART8 peripheral.
  */
__STATIC_INLINE void HAL_RCC_UART8_Reset(void)
{
  LL_APB1_GRP1_ForceReset(LL_APB1_GRP1_PERIPH_UART8);
  LL_APB1_GRP1_ReleaseReset(LL_APB1_GRP1_PERIPH_UART8);
}

/**
  * @}
  */ /* RCC_APB1_Reset */

/** @defgroup RCC_APB1_Reset APB1 PeripheralReset
  * @brief  APB1 peripheral reset.
  * @{
  */

/**
  * @details This function resets the CRS peripheral.
  */
__STATIC_INLINE void HAL_RCC_CRS_Reset(void)
{
  LL_APB1_GRP2_ForceReset(LL_APB1_GRP2_PERIPH_CRS);
  LL_APB1_GRP2_ReleaseReset(LL_APB1_GRP2_PERIPH_CRS);
}

/**
  * @details This function resets the FDCAN peripheral.
  */
__STATIC_INLINE void HAL_RCC_FDCAN_Reset(void)
{
  LL_APB1_GRP2_ForceReset(LL_APB1_GRP2_PERIPH_FDCAN);
  LL_APB1_GRP2_ReleaseReset(LL_APB1_GRP2_PERIPH_FDCAN);
}

/**
  * @details This function resets the UCPD1 peripheral.
  */
__STATIC_INLINE void HAL_RCC_UCPD1_Reset(void)
{
  LL_APB1_GRP2_ForceReset(LL_APB1_GRP2_PERIPH_UCPD1);
  LL_APB1_GRP2_ReleaseReset(LL_APB1_GRP2_PERIPH_UCPD1);
}

/**
  * @}
  */ /* RCC_APB1_Reset */

/** @defgroup RCC_APB2_Reset APB2 PeripheralReset
  * @brief  APB2 peripheral reset.
  * @{
  */

/**
  * @details This function resets the TIM1 peripheral.
  */
__STATIC_INLINE void HAL_RCC_TIM1_Reset(void)
{
  LL_APB2_GRP1_ForceReset(LL_APB2_GRP1_PERIPH_TIM1);
  LL_APB2_GRP1_ReleaseReset(LL_APB2_GRP1_PERIPH_TIM1);
}

/**
  * @details This function resets the TIM8 peripheral.
  */
__STATIC_INLINE void HAL_RCC_TIM8_Reset(void)
{
  LL_APB2_GRP1_ForceReset(LL_APB2_GRP1_PERIPH_TIM8);
  LL_APB2_GRP1_ReleaseReset(LL_APB2_GRP1_PERIPH_TIM8);
}

/**
  * @details This function resets the TIM20 peripheral.
  */
__STATIC_INLINE void HAL_RCC_TIM20_Reset(void)
{
  LL_APB2_GRP1_ForceReset(LL_APB2_GRP1_PERIPH_TIM20);
  LL_APB2_GRP1_ReleaseReset(LL_APB2_GRP1_PERIPH_TIM20);
}

/**
  * @details This function resets the USART1 peripheral.
  */
__STATIC_INLINE void HAL_RCC_USART1_Reset(void)
{
  LL_APB2_GRP1_ForceReset(LL_APB2_GRP1_PERIPH_USART1);
  LL_APB2_GRP1_ReleaseReset(LL_APB2_GRP1_PERIPH_USART1);
}

/**
  * @details This function resets the USART6 peripheral.
  */
__STATIC_INLINE void HAL_RCC_USART6_Reset(void)
{
  LL_APB2_GRP1_ForceReset(LL_APB2_GRP1_PERIPH_USART6);
  LL_APB2_GRP1_ReleaseReset(LL_APB2_GRP1_PERIPH_USART6);
}

/**
  * @details This function resets the UART9 peripheral.
  */
__STATIC_INLINE void HAL_RCC_UART9_Reset(void)
{
  LL_APB2_GRP1_ForceReset(LL_APB2_GRP1_PERIPH_UART9);
  LL_APB2_GRP1_ReleaseReset(LL_APB2_GRP1_PERIPH_UART9);
}

/**
  * @details This function resets the USART10 peripheral.
  */
__STATIC_INLINE void HAL_RCC_USART10_Reset(void)
{
  LL_APB2_GRP1_ForceReset(LL_APB2_GRP1_PERIPH_USART10);
  LL_APB2_GRP1_ReleaseReset(LL_APB2_GRP1_PERIPH_USART10);
}

/**
  * @details This function resets the SPI1 peripheral.
  */
__STATIC_INLINE void HAL_RCC_SPI1_Reset(void)
{
  LL_APB2_GRP1_ForceReset(LL_APB2_GRP1_PERIPH_SPI1);
  LL_APB2_GRP1_ReleaseReset(LL_APB2_GRP1_PERIPH_SPI1);
}

/**
  * @details This function resets the SPI4 peripheral.
  */
__STATIC_INLINE void HAL_RCC_SPI4_Reset(void)
{
  LL_APB2_GRP1_ForceReset(LL_APB2_GRP1_PERIPH_SPI4);
  LL_APB2_GRP1_ReleaseReset(LL_APB2_GRP1_PERIPH_SPI4);
}

/**
  * @details This function resets the TIM15 peripheral.
  */
__STATIC_INLINE void HAL_RCC_TIM15_Reset(void)
{
  LL_APB2_GRP1_ForceReset(LL_APB2_GRP1_PERIPH_TIM15);
  LL_APB2_GRP1_ReleaseReset(LL_APB2_GRP1_PERIPH_TIM15);
}

/**
  * @details This function resets the TIM16 peripheral.
  */
__STATIC_INLINE void HAL_RCC_TIM16_Reset(void)
{
  LL_APB2_GRP1_ForceReset(LL_APB2_GRP1_PERIPH_TIM16);
  LL_APB2_GRP1_ReleaseReset(LL_APB2_GRP1_PERIPH_TIM16);
}

/**
  * @details This function resets the TIM17 peripheral.
  */
__STATIC_INLINE void HAL_RCC_TIM17_Reset(void)
{
  LL_APB2_GRP1_ForceReset(LL_APB2_GRP1_PERIPH_TIM17);
  LL_APB2_GRP1_ReleaseReset(LL_APB2_GRP1_PERIPH_TIM17);
}

/**
  * @details This function resets the TIM9 peripheral.
  */
__STATIC_INLINE void HAL_RCC_TIM9_Reset(void)
{
  LL_APB2_GRP1_ForceReset(LL_APB2_GRP1_PERIPH_TIM9);
  LL_APB2_GRP1_ReleaseReset(LL_APB2_GRP1_PERIPH_TIM9);
}

/**
  * @details This function resets the SPI5 peripheral.
  */
__STATIC_INLINE void HAL_RCC_SPI5_Reset(void)
{
  LL_APB2_GRP1_ForceReset(LL_APB2_GRP1_PERIPH_SPI5);
  LL_APB2_GRP1_ReleaseReset(LL_APB2_GRP1_PERIPH_SPI5);
}

/**
  * @details This function resets the HRTIM1 peripheral.
  */
__STATIC_INLINE void HAL_RCC_HRTIM1_Reset(void)
{
  LL_APB2_GRP1_ForceReset(LL_APB2_GRP1_PERIPH_HRTIM1);
  LL_APB2_GRP1_ReleaseReset(LL_APB2_GRP1_PERIPH_HRTIM1);
}

/**
  * @details This function resets the HRTIM2 peripheral.
  */
__STATIC_INLINE void HAL_RCC_HRTIM2_Reset(void)
{
  LL_APB2_GRP1_ForceReset(LL_APB2_GRP1_PERIPH_HRTIM2);
  LL_APB2_GRP1_ReleaseReset(LL_APB2_GRP1_PERIPH_HRTIM2);
}

/**
  * @}
  */ /* RCC_APB2_Reset */

/** @defgroup RCC_APB4_Reset APB4 PeripheralReset
  * @brief  APB4 peripheral reset.
  * @{
  */

/**
  * @details This function resets the SBS peripheral.
  */
__STATIC_INLINE void HAL_RCC_SBS_Reset(void)
{
  LL_APB4_GRP1_ForceReset(LL_APB4_GRP1_PERIPH_SBS);
  LL_APB4_GRP1_ReleaseReset(LL_APB4_GRP1_PERIPH_SBS);
}

/**
  * @details This function resets the LPUART1 peripheral.
  */
__STATIC_INLINE void HAL_RCC_LPUART1_Reset(void)
{
  LL_APB4_GRP1_ForceReset(LL_APB4_GRP1_PERIPH_LPUART1);
  LL_APB4_GRP1_ReleaseReset(LL_APB4_GRP1_PERIPH_LPUART1);
}

/**
  * @details This function resets the SPI6 peripheral.
  */
__STATIC_INLINE void HAL_RCC_SPI6_Reset(void)
{
  LL_APB4_GRP1_ForceReset(LL_APB4_GRP1_PERIPH_SPI6);
  LL_APB4_GRP1_ReleaseReset(LL_APB4_GRP1_PERIPH_SPI6);
}

/**
  * @details This function resets the LPTIM2 peripheral.
  */
__STATIC_INLINE void HAL_RCC_LPTIM2_Reset(void)
{
  LL_APB4_GRP1_ForceReset(LL_APB4_GRP1_PERIPH_LPTIM2);
  LL_APB4_GRP1_ReleaseReset(LL_APB4_GRP1_PERIPH_LPTIM2);
}

/**
  * @details This function resets the LPTIM3 peripheral.
  */
__STATIC_INLINE void HAL_RCC_LPTIM3_Reset(void)
{
  LL_APB4_GRP1_ForceReset(LL_APB4_GRP1_PERIPH_LPTIM3);
  LL_APB4_GRP1_ReleaseReset(LL_APB4_GRP1_PERIPH_LPTIM3);
}

/**
  * @details This function resets the LPTIM4 peripheral.
  */
__STATIC_INLINE void HAL_RCC_LPTIM4_Reset(void)
{
  LL_APB4_GRP1_ForceReset(LL_APB4_GRP1_PERIPH_LPTIM4);
  LL_APB4_GRP1_ReleaseReset(LL_APB4_GRP1_PERIPH_LPTIM4);
}

/**
  * @details This function resets the LPTIM5 peripheral.
  */
__STATIC_INLINE void HAL_RCC_LPTIM5_Reset(void)
{
  LL_APB4_GRP1_ForceReset(LL_APB4_GRP1_PERIPH_LPTIM5);
  LL_APB4_GRP1_ReleaseReset(LL_APB4_GRP1_PERIPH_LPTIM5);
}

/**
  * @details This function resets the VREF peripheral.
  */
__STATIC_INLINE void HAL_RCC_VREF_Reset(void)
{
  LL_APB4_GRP1_ForceReset(LL_APB4_GRP1_PERIPH_VREF);
  LL_APB4_GRP1_ReleaseReset(LL_APB4_GRP1_PERIPH_VREF);
}

/**
  * @details This function resets the DTS peripheral.
  */
__STATIC_INLINE void HAL_RCC_DTS_Reset(void)
{
  LL_APB4_GRP1_ForceReset(LL_APB4_GRP1_PERIPH_DTS);
  LL_APB4_GRP1_ReleaseReset(LL_APB4_GRP1_PERIPH_DTS);
}

/**
  * @details This function resets the COMP12 peripheral.
  */
__STATIC_INLINE void HAL_RCC_COMP12_Reset(void)
{
  LL_APB4_GRP1_ForceReset(LL_APB4_GRP1_PERIPH_COMP12);
  LL_APB4_GRP1_ReleaseReset(LL_APB4_GRP1_PERIPH_COMP12);
}

/**
  * @details This function resets the COMP34 peripheral.
  */
__STATIC_INLINE void HAL_RCC_COMP34_Reset(void)
{
  LL_APB4_GRP1_ForceReset(LL_APB4_GRP1_PERIPH_COMP34);
  LL_APB4_GRP1_ReleaseReset(LL_APB4_GRP1_PERIPH_COMP34);
}

/**
  * @details This function resets the COMP56 peripheral.
  */
__STATIC_INLINE void HAL_RCC_COMP56_Reset(void)
{
  LL_APB4_GRP1_ForceReset(LL_APB4_GRP1_PERIPH_COMP56);
  LL_APB4_GRP1_ReleaseReset(LL_APB4_GRP1_PERIPH_COMP56);
}

/**
  * @details This function resets the COMP78 peripheral.
  */
__STATIC_INLINE void HAL_RCC_COMP78_Reset(void)
{
  LL_APB4_GRP1_ForceReset(LL_APB4_GRP1_PERIPH_COMP78);
  LL_APB4_GRP1_ReleaseReset(LL_APB4_GRP1_PERIPH_COMP78);
}

/**
  * @}
  */ /* RCC_APB4_Reset */

/** @defgroup RCC_AHB1_Peripheral_Clock_Sleep_Enable_Disable AHB1 Peripheral Clock Sleep Enable Disable
  * @brief  Enable or disable the AHB1 peripheral clock during Low Power (Sleep and Stop) mode.
  * @note   Peripheral clock gating in SLEEP and STOP modes can be used to further reduce power consumption.
  * @note   After wakeup from SLEEP or STOP modes, the peripheral clock is enabled again.
  * @note   By default, all peripheral clocks are enabled during SLEEP mode. In STOP mode peripheral clock
  *         is enabled only when a peripheral requests AHB clock.
  * @{
  */

/**
  * @details This function enables the HSP clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_HSP_EnableClockInSleepMode(void)
{
  LL_AHB1_GRP1_EnableClockLowPower(LL_AHB1_GRP1_PERIPH_HSP);
}

/**
  * @details This function enables the HSP clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_HSP_EnableClockInStopMode(void)
{
  LL_AHB1_GRP1_EnableClockLowPower(LL_AHB1_GRP1_PERIPH_HSP);
}

/**
  * @details This function enables the GPDMA1 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_GPDMA1_EnableClockInSleepMode(void)
{
  LL_AHB1_GRP1_EnableClockLowPower(LL_AHB1_GRP1_PERIPH_GPDMA1);
}

/**
  * @details This function enables the GPDMA1 clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_GPDMA1_EnableClockInStopMode(void)
{
  LL_AHB1_GRP1_EnableClockLowPower(LL_AHB1_GRP1_PERIPH_GPDMA1);
}

/**
  * @details This function enables the OTGFS clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_OTGFS_EnableClockInSleepMode(void)
{
  LL_AHB1_GRP1_EnableClockLowPower(LL_AHB1_GRP1_PERIPH_OTGFS);
}

/**
  * @details This function enables the OTGFS clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_OTGFS_EnableClockInStopMode(void)
{
  LL_AHB1_GRP1_EnableClockLowPower(LL_AHB1_GRP1_PERIPH_OTGFS);
}

/**
  * @details This function enables the ADF1 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_ADF1_EnableClockInSleepMode(void)
{
  LL_AHB1_GRP1_EnableClockLowPower(LL_AHB1_GRP1_PERIPH_ADF1);
}

/**
  * @details This function enables the ADF1 clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_ADF1_EnableClockInStopMode(void)
{
  LL_AHB1_GRP1_EnableClockLowPower(LL_AHB1_GRP1_PERIPH_ADF1);
}

/**
  * @details This function disables the HSP clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_HSP_DisableClockInSleepMode(void)
{
  LL_AHB1_GRP1_DisableClockLowPower(LL_AHB1_GRP1_PERIPH_HSP);
}

/**
  * @details This function disables the HSP clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_HSP_DisableClockInStopMode(void)
{
  LL_AHB1_GRP1_DisableClockLowPower(LL_AHB1_GRP1_PERIPH_HSP);
}

/**
  * @details This function disables the GPDMA1 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_GPDMA1_DisableClockInSleepMode(void)
{
  LL_AHB1_GRP1_DisableClockLowPower(LL_AHB1_GRP1_PERIPH_GPDMA1);
}

/**
  * @details This function disables the GPDMA1 clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_GPDMA1_DisableClockInStopMode(void)
{
  LL_AHB1_GRP1_DisableClockLowPower(LL_AHB1_GRP1_PERIPH_GPDMA1);
}

/**
  * @details This function disables the OTGFS clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_OTGFS_DisableClockInSleepMode(void)
{
  LL_AHB1_GRP1_DisableClockLowPower(LL_AHB1_GRP1_PERIPH_OTGFS);
}

/**
  * @details This function disables the OTGFS clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_OTGFS_DisableClockInStopMode(void)
{
  LL_AHB1_GRP1_DisableClockLowPower(LL_AHB1_GRP1_PERIPH_OTGFS);
}

/**
  * @details This function disables the ADF1 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_ADF1_DisableClockInSleepMode(void)
{
  LL_AHB1_GRP1_DisableClockLowPower(LL_AHB1_GRP1_PERIPH_ADF1);
}

/**
  * @details This function disables the ADF1 clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_ADF1_DisableClockInStopMode(void)
{
  LL_AHB1_GRP1_DisableClockLowPower(LL_AHB1_GRP1_PERIPH_ADF1);
}

/**
  * @}
  */ /* RCC_AHB1_Peripheral_Clock_Sleep_Enable_Disable */

/** @defgroup RCC_AHB2_Peripheral_Clock_Sleep_Enable_Disable AHB2 Peripheral Clock Sleep Enable Disable
  * @brief  Enable or disable the AHB2 peripheral clock during Low Power (Sleep and Stop) mode.
  * @note   Peripheral clock gating in SLEEP and STOP modes can be used to further reduce power consumption.
  * @note   After wakeup from SLEEP or STOP modes, the peripheral clock is enabled again.
  * @note   By default, all peripheral clocks are enabled during SLEEP mode. In STOP mode peripheral clock
  *         is enabled only when a peripheral requests AHB clock.
  * @{
  */

/**
  * @details This function enables the CORDIC clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_CORDIC_EnableClockInSleepMode(void)
{
  LL_AHB2_GRP1_EnableClockLowPower(LL_AHB2_GRP1_PERIPH_CORDIC);
}

/**
  * @details This function enables the CORDIC clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_CORDIC_EnableClockInStopMode(void)
{
  LL_AHB2_GRP1_EnableClockLowPower(LL_AHB2_GRP1_PERIPH_CORDIC);
}

/**
  * @details This function enables the FMAC clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_FMAC_EnableClockInSleepMode(void)
{
  LL_AHB2_GRP1_EnableClockLowPower(LL_AHB2_GRP1_PERIPH_FMAC);
}

/**
  * @details This function enables the FMAC clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_FMAC_EnableClockInStopMode(void)
{
  LL_AHB2_GRP1_EnableClockLowPower(LL_AHB2_GRP1_PERIPH_FMAC);
}

/**
  * @details This function enables the AHBSRAM1 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_AHBSRAM1_EnableClockInSleepMode(void)
{
  LL_AHB2_GRP1_EnableClockLowPower(LL_AHB2_GRP1_PERIPH_AHBSRAM1);
}

/**
  * @details This function enables the AHBSRAM1 clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_AHBSRAM1_EnableClockInStopMode(void)
{
  LL_AHB2_GRP1_EnableClockLowPower(LL_AHB2_GRP1_PERIPH_AHBSRAM1);
}

/**
  * @details This function enables the AHBSRAM2 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_AHBSRAM2_EnableClockInSleepMode(void)
{
  LL_AHB2_GRP1_EnableClockLowPower(LL_AHB2_GRP1_PERIPH_AHBSRAM2);
}

/**
  * @details This function enables the AHBSRAM2 clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_AHBSRAM2_EnableClockInStopMode(void)
{
  LL_AHB2_GRP1_EnableClockLowPower(LL_AHB2_GRP1_PERIPH_AHBSRAM2);
}

/**
  * @details This function enables the AHBSRAM3 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_AHBSRAM3_EnableClockInSleepMode(void)
{
  LL_AHB2_GRP1_EnableClockLowPower(LL_AHB2_GRP1_PERIPH_AHBSRAM3);
}

/**
  * @details This function enables the AHBSRAM3 clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_AHBSRAM3_EnableClockInStopMode(void)
{
  LL_AHB2_GRP1_EnableClockLowPower(LL_AHB2_GRP1_PERIPH_AHBSRAM3);
}

/**
  * @details This function disables the CORDIC clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_CORDIC_DisableClockInSleepMode(void)
{
  LL_AHB2_GRP1_DisableClockLowPower(LL_AHB2_GRP1_PERIPH_CORDIC);
}

/**
  * @details This function disables the CORDIC clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_CORDIC_DisableClockInStopMode(void)
{
  LL_AHB2_GRP1_DisableClockLowPower(LL_AHB2_GRP1_PERIPH_CORDIC);
}

/**
  * @details This function disables the FMAC clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_FMAC_DisableClockInSleepMode(void)
{
  LL_AHB2_GRP1_DisableClockLowPower(LL_AHB2_GRP1_PERIPH_FMAC);
}

/**
  * @details This function disables the FMAC clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_FMAC_DisableClockInStopMode(void)
{
  LL_AHB2_GRP1_DisableClockLowPower(LL_AHB2_GRP1_PERIPH_FMAC);
}

/**
  * @details This function disables the AHBSRAM1 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_AHBSRAM1_DisableClockInSleepMode(void)
{
  LL_AHB2_GRP1_DisableClockLowPower(LL_AHB2_GRP1_PERIPH_AHBSRAM1);
}

/**
  * @details This function disables the AHBSRAM1 clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_AHBSRAM1_DisableClockInStopMode(void)
{
  LL_AHB2_GRP1_DisableClockLowPower(LL_AHB2_GRP1_PERIPH_AHBSRAM1);
}

/**
  * @details This function disables the AHBSRAM2 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_AHBSRAM2_DisableClockInSleepMode(void)
{
  LL_AHB2_GRP1_DisableClockLowPower(LL_AHB2_GRP1_PERIPH_AHBSRAM2);
}

/**
  * @details This function disables the AHBSRAM2 clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_AHBSRAM2_DisableClockInStopMode(void)
{
  LL_AHB2_GRP1_DisableClockLowPower(LL_AHB2_GRP1_PERIPH_AHBSRAM2);
}

/**
  * @details This function disables the AHBSRAM3 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_AHBSRAM3_DisableClockInSleepMode(void)
{
  LL_AHB2_GRP1_DisableClockLowPower(LL_AHB2_GRP1_PERIPH_AHBSRAM3);
}

/**
  * @details This function disables the AHBSRAM3 clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_AHBSRAM3_DisableClockInStopMode(void)
{
  LL_AHB2_GRP1_DisableClockLowPower(LL_AHB2_GRP1_PERIPH_AHBSRAM3);
}

/**
  * @}
  */ /* RCC_AHB2_Peripheral_Clock_Sleep_Enable_Disable */

/** @defgroup RCC_AHB3_Peripheral_Clock_Sleep_Enable_Disable AHB3 Peripheral Clock Sleep Enable Disable
  * @brief  Enable or disable the AHB3 peripheral clock during Low Power (Sleep and Stop) mode.
  * @note   Peripheral clock gating in SLEEP and STOP modes can be used to further reduce power consumption.
  * @note   After wakeup from SLEEP or STOP modes, the peripheral clock is enabled again.
  * @note   By default, all peripheral clocks are enabled during SLEEP mode. In STOP mode peripheral clock
  *         is enabled only when a peripheral requests AHB clock.
  * @{
  */

/**
  * @details This function enables the RNG clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_RNG_EnableClockInSleepMode(void)
{
  LL_AHB3_GRP1_EnableClockLowPower(LL_AHB3_GRP1_PERIPH_RNG);
}

/**
  * @details This function enables the RNG clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_RNG_EnableClockInStopMode(void)
{
  LL_AHB3_GRP1_EnableClockLowPower(LL_AHB3_GRP1_PERIPH_RNG);
}

/**
  * @details This function enables the HASH clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_HASH_EnableClockInSleepMode(void)
{
  LL_AHB3_GRP1_EnableClockLowPower(LL_AHB3_GRP1_PERIPH_HASH);
}

/**
  * @details This function enables the HASH clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_HASH_EnableClockInStopMode(void)
{
  LL_AHB3_GRP1_EnableClockLowPower(LL_AHB3_GRP1_PERIPH_HASH);
}

/**
  * @details This function enables the ADC12 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_ADC12_EnableClockInSleepMode(void)
{
  LL_AHB3_GRP1_EnableClockLowPower(LL_AHB3_GRP1_PERIPH_ADC12);
}

/**
  * @details This function enables the ADC12 clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_ADC12_EnableClockInStopMode(void)
{
  LL_AHB3_GRP1_EnableClockLowPower(LL_AHB3_GRP1_PERIPH_ADC12);
}

/**
  * @details This function enables the ADC34 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_ADC34_EnableClockInSleepMode(void)
{
  LL_AHB3_GRP1_EnableClockLowPower(LL_AHB3_GRP1_PERIPH_ADC34);
}

/**
  * @details This function enables the ADC34 clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_ADC34_EnableClockInStopMode(void)
{
  LL_AHB3_GRP1_EnableClockLowPower(LL_AHB3_GRP1_PERIPH_ADC34);
}

/**
  * @details This function enables the DAC1 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_DAC1_EnableClockInSleepMode(void)
{
  LL_AHB3_GRP1_EnableClockLowPower(LL_AHB3_GRP1_PERIPH_DAC1);
}

/**
  * @details This function enables the DAC1 clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_DAC1_EnableClockInStopMode(void)
{
  LL_AHB3_GRP1_EnableClockLowPower(LL_AHB3_GRP1_PERIPH_DAC1);
}

/**
  * @details This function enables the DAC2 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_DAC2_EnableClockInSleepMode(void)
{
  LL_AHB3_GRP1_EnableClockLowPower(LL_AHB3_GRP1_PERIPH_DAC2);
}

/**
  * @details This function enables the DAC2 clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_DAC2_EnableClockInStopMode(void)
{
  LL_AHB3_GRP1_EnableClockLowPower(LL_AHB3_GRP1_PERIPH_DAC2);
}

/**
  * @details This function enables the DAC3 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_DAC3_EnableClockInSleepMode(void)
{
  LL_AHB3_GRP1_EnableClockLowPower(LL_AHB3_GRP1_PERIPH_DAC3);
}

/**
  * @details This function enables the DAC3 clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_DAC3_EnableClockInStopMode(void)
{
  LL_AHB3_GRP1_EnableClockLowPower(LL_AHB3_GRP1_PERIPH_DAC3);
}

/**
  * @details This function enables the DAC4 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_DAC4_EnableClockInSleepMode(void)
{
  LL_AHB3_GRP1_EnableClockLowPower(LL_AHB3_GRP1_PERIPH_DAC4);
}

/**
  * @details This function enables the DAC4 clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_DAC4_EnableClockInStopMode(void)
{
  LL_AHB3_GRP1_EnableClockLowPower(LL_AHB3_GRP1_PERIPH_DAC4);
}

/**
  * @details This function disables the RNG clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_RNG_DisableClockInSleepMode(void)
{
  LL_AHB3_GRP1_DisableClockLowPower(LL_AHB3_GRP1_PERIPH_RNG);
}

/**
  * @details This function disables the RNG clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_RNG_DisableClockInStopMode(void)
{
  LL_AHB3_GRP1_DisableClockLowPower(LL_AHB3_GRP1_PERIPH_RNG);
}

/**
  * @details This function disables the HASH clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_HASH_DisableClockInSleepMode(void)
{
  LL_AHB3_GRP1_DisableClockLowPower(LL_AHB3_GRP1_PERIPH_HASH);
}

/**
  * @details This function disables the HASH clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_HASH_DisableClockInStopMode(void)
{
  LL_AHB3_GRP1_DisableClockLowPower(LL_AHB3_GRP1_PERIPH_HASH);
}

/**
  * @details This function disables the ADC12 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_ADC12_DisableClockInSleepMode(void)
{
  LL_AHB3_GRP1_DisableClockLowPower(LL_AHB3_GRP1_PERIPH_ADC12);
}

/**
  * @details This function disables the ADC12 clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_ADC12_DisableClockInStopMode(void)
{
  LL_AHB3_GRP1_DisableClockLowPower(LL_AHB3_GRP1_PERIPH_ADC12);
}

/**
  * @details This function disables the ADC34 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_ADC34_DisableClockInSleepMode(void)
{
  LL_AHB3_GRP1_DisableClockLowPower(LL_AHB3_GRP1_PERIPH_ADC34);
}

/**
  * @details This function disables the ADC34 clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_ADC34_DisableClockInStopMode(void)
{
  LL_AHB3_GRP1_DisableClockLowPower(LL_AHB3_GRP1_PERIPH_ADC34);
}

/**
  * @details This function disables the DAC1 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_DAC1_DisableClockInSleepMode(void)
{
  LL_AHB3_GRP1_DisableClockLowPower(LL_AHB3_GRP1_PERIPH_DAC1);
}

/**
  * @details This function disables the DAC1 clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_DAC1_DisableClockInStopMode(void)
{
  LL_AHB3_GRP1_DisableClockLowPower(LL_AHB3_GRP1_PERIPH_DAC1);
}

/**
  * @details This function disables the DAC2 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_DAC2_DisableClockInSleepMode(void)
{
  LL_AHB3_GRP1_DisableClockLowPower(LL_AHB3_GRP1_PERIPH_DAC2);
}

/**
  * @details This function disables the DAC2 clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_DAC2_DisableClockInStopMode(void)
{
  LL_AHB3_GRP1_DisableClockLowPower(LL_AHB3_GRP1_PERIPH_DAC2);
}

/**
  * @details This function disables the DAC3 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_DAC3_DisableClockInSleepMode(void)
{
  LL_AHB3_GRP1_DisableClockLowPower(LL_AHB3_GRP1_PERIPH_DAC3);
}

/**
  * @details This function disables the DAC3 clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_DAC3_DisableClockInStopMode(void)
{
  LL_AHB3_GRP1_DisableClockLowPower(LL_AHB3_GRP1_PERIPH_DAC3);
}

/**
  * @details This function disables the DAC4 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_DAC4_DisableClockInSleepMode(void)
{
  LL_AHB3_GRP1_DisableClockLowPower(LL_AHB3_GRP1_PERIPH_DAC4);
}

/**
  * @details This function disables the DAC4 clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_DAC4_DisableClockInStopMode(void)
{
  LL_AHB3_GRP1_DisableClockLowPower(LL_AHB3_GRP1_PERIPH_DAC4);
}

/**
  * @}
  */ /* RCC_AHB3_Peripheral_Clock_Sleep_Enable_Disable */

/** @defgroup RCC_AHB4_Peripheral_Clock_Sleep_Enable_Disable AHB4 Peripheral Clock Sleep Enable Disable
  * @brief  Enable or disable the AHB4 peripheral clock during Low Power (Sleep and Stop) mode.
  * @note   Peripheral clock gating in SLEEP and STOP modes can be used to further reduce power consumption.
  * @note   After wakeup from SLEEP or STOP modes, the peripheral clock is enabled again.
  * @note   By default, all peripheral clocks are enabled during SLEEP mode. In STOP mode peripheral clock
  *         is enabled only when a peripheral requests AHB clock.
  * @{
  */

/**
  * @details This function enables the GPIOA clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_GPIOA_EnableClockInSleepMode(void)
{
  LL_AHB4_GRP1_EnableClockLowPower(LL_AHB4_GRP1_PERIPH_GPIOA);
}

/**
  * @details This function enables the GPIOA clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_GPIOA_EnableClockInStopMode(void)
{
  LL_AHB4_GRP1_EnableClockLowPower(LL_AHB4_GRP1_PERIPH_GPIOA);
}

/**
  * @details This function enables the GPIOB clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_GPIOB_EnableClockInSleepMode(void)
{
  LL_AHB4_GRP1_EnableClockLowPower(LL_AHB4_GRP1_PERIPH_GPIOB);
}

/**
  * @details This function enables the GPIOB clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_GPIOB_EnableClockInStopMode(void)
{
  LL_AHB4_GRP1_EnableClockLowPower(LL_AHB4_GRP1_PERIPH_GPIOB);
}

/**
  * @details This function enables the GPIOC clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_GPIOC_EnableClockInSleepMode(void)
{
  LL_AHB4_GRP1_EnableClockLowPower(LL_AHB4_GRP1_PERIPH_GPIOC);
}

/**
  * @details This function enables the GPIOC clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_GPIOC_EnableClockInStopMode(void)
{
  LL_AHB4_GRP1_EnableClockLowPower(LL_AHB4_GRP1_PERIPH_GPIOC);
}

/**
  * @details This function enables the GPIOD clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_GPIOD_EnableClockInSleepMode(void)
{
  LL_AHB4_GRP1_EnableClockLowPower(LL_AHB4_GRP1_PERIPH_GPIOD);
}

/**
  * @details This function enables the GPIOD clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_GPIOD_EnableClockInStopMode(void)
{
  LL_AHB4_GRP1_EnableClockLowPower(LL_AHB4_GRP1_PERIPH_GPIOD);
}

/**
  * @details This function enables the GPIOE clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_GPIOE_EnableClockInSleepMode(void)
{
  LL_AHB4_GRP1_EnableClockLowPower(LL_AHB4_GRP1_PERIPH_GPIOE);
}

/**
  * @details This function enables the GPIOE clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_GPIOE_EnableClockInStopMode(void)
{
  LL_AHB4_GRP1_EnableClockLowPower(LL_AHB4_GRP1_PERIPH_GPIOE);
}

/**
  * @details This function enables the GPIOF clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_GPIOF_EnableClockInSleepMode(void)
{
  LL_AHB4_GRP1_EnableClockLowPower(LL_AHB4_GRP1_PERIPH_GPIOF);
}

/**
  * @details This function enables the GPIOF clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_GPIOF_EnableClockInStopMode(void)
{
  LL_AHB4_GRP1_EnableClockLowPower(LL_AHB4_GRP1_PERIPH_GPIOF);
}

/**
  * @details This function enables the GPIOG clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_GPIOG_EnableClockInSleepMode(void)
{
  LL_AHB4_GRP1_EnableClockLowPower(LL_AHB4_GRP1_PERIPH_GPIOG);
}

/**
  * @details This function enables the GPIOG clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_GPIOG_EnableClockInStopMode(void)
{
  LL_AHB4_GRP1_EnableClockLowPower(LL_AHB4_GRP1_PERIPH_GPIOG);
}

/**
  * @details This function enables the GPIOH clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_GPIOH_EnableClockInSleepMode(void)
{
  LL_AHB4_GRP1_EnableClockLowPower(LL_AHB4_GRP1_PERIPH_GPIOH);
}

/**
  * @details This function enables the GPIOH clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_GPIOH_EnableClockInStopMode(void)
{
  LL_AHB4_GRP1_EnableClockLowPower(LL_AHB4_GRP1_PERIPH_GPIOH);
}

/**
  * @details This function enables the GPIOI clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_GPIOI_EnableClockInSleepMode(void)
{
  LL_AHB4_GRP1_EnableClockLowPower(LL_AHB4_GRP1_PERIPH_GPIOI);
}

/**
  * @details This function enables the GPIOI clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_GPIOI_EnableClockInStopMode(void)
{
  LL_AHB4_GRP1_EnableClockLowPower(LL_AHB4_GRP1_PERIPH_GPIOI);
}

/**
  * @details This function enables the CRC clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_CRC_EnableClockInSleepMode(void)
{
  LL_AHB4_GRP1_EnableClockLowPower(LL_AHB4_GRP1_PERIPH_CRC);
}

/**
  * @details This function enables the CRC clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_CRC_EnableClockInStopMode(void)
{
  LL_AHB4_GRP1_EnableClockLowPower(LL_AHB4_GRP1_PERIPH_CRC);
}

/**
  * @details This function enables the BKPRAM clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_BKPRAM_EnableClockInSleepMode(void)
{
  LL_AHB4_GRP1_EnableClockLowPower(LL_AHB4_GRP1_PERIPH_BKPRAM);
}

/**
  * @details This function enables the BKPRAM clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_BKPRAM_EnableClockInStopMode(void)
{
  LL_AHB4_GRP1_EnableClockLowPower(LL_AHB4_GRP1_PERIPH_BKPRAM);
}

/**
  * @details This function disables the GPIOA clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_GPIOA_DisableClockInSleepMode(void)
{
  LL_AHB4_GRP1_DisableClockLowPower(LL_AHB4_GRP1_PERIPH_GPIOA);
}

/**
  * @details This function disables the GPIOA clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_GPIOA_DisableClockInStopMode(void)
{
  LL_AHB4_GRP1_DisableClockLowPower(LL_AHB4_GRP1_PERIPH_GPIOA);
}

/**
  * @details This function disables the GPIOB clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_GPIOB_DisableClockInSleepMode(void)
{
  LL_AHB4_GRP1_DisableClockLowPower(LL_AHB4_GRP1_PERIPH_GPIOB);
}

/**
  * @details This function disables the GPIOB clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_GPIOB_DisableClockInStopMode(void)
{
  LL_AHB4_GRP1_DisableClockLowPower(LL_AHB4_GRP1_PERIPH_GPIOB);
}

/**
  * @details This function disables the GPIOC clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_GPIOC_DisableClockInSleepMode(void)
{
  LL_AHB4_GRP1_DisableClockLowPower(LL_AHB4_GRP1_PERIPH_GPIOC);
}

/**
  * @details This function disables the GPIOC clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_GPIOC_DisableClockInStopMode(void)
{
  LL_AHB4_GRP1_DisableClockLowPower(LL_AHB4_GRP1_PERIPH_GPIOC);
}

/**
  * @details This function disables the GPIOD clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_GPIOD_DisableClockInSleepMode(void)
{
  LL_AHB4_GRP1_DisableClockLowPower(LL_AHB4_GRP1_PERIPH_GPIOD);
}

/**
  * @details This function disables the GPIOD clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_GPIOD_DisableClockInStopMode(void)
{
  LL_AHB4_GRP1_DisableClockLowPower(LL_AHB4_GRP1_PERIPH_GPIOD);
}

/**
  * @details This function disables the GPIOE clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_GPIOE_DisableClockInSleepMode(void)
{
  LL_AHB4_GRP1_DisableClockLowPower(LL_AHB4_GRP1_PERIPH_GPIOE);
}

/**
  * @details This function disables the GPIOE clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_GPIOE_DisableClockInStopMode(void)
{
  LL_AHB4_GRP1_DisableClockLowPower(LL_AHB4_GRP1_PERIPH_GPIOE);
}

/**
  * @details This function disables the GPIOF clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_GPIOF_DisableClockInSleepMode(void)
{
  LL_AHB4_GRP1_DisableClockLowPower(LL_AHB4_GRP1_PERIPH_GPIOF);
}

/**
  * @details This function disables the GPIOF clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_GPIOF_DisableClockInStopMode(void)
{
  LL_AHB4_GRP1_DisableClockLowPower(LL_AHB4_GRP1_PERIPH_GPIOF);
}

/**
  * @details This function disables the GPIOG clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_GPIOG_DisableClockInSleepMode(void)
{
  LL_AHB4_GRP1_DisableClockLowPower(LL_AHB4_GRP1_PERIPH_GPIOG);
}

/**
  * @details This function disables the GPIOG clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_GPIOG_DisableClockInStopMode(void)
{
  LL_AHB4_GRP1_DisableClockLowPower(LL_AHB4_GRP1_PERIPH_GPIOG);
}

/**
  * @details This function disables the GPIOH clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_GPIOH_DisableClockInSleepMode(void)
{
  LL_AHB4_GRP1_DisableClockLowPower(LL_AHB4_GRP1_PERIPH_GPIOH);
}

/**
  * @details This function disables the GPIOH clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_GPIOH_DisableClockInStopMode(void)
{
  LL_AHB4_GRP1_DisableClockLowPower(LL_AHB4_GRP1_PERIPH_GPIOH);
}

/**
  * @details This function disables the GPIOI clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_GPIOI_DisableClockInSleepMode(void)
{
  LL_AHB4_GRP1_DisableClockLowPower(LL_AHB4_GRP1_PERIPH_GPIOI);
}

/**
  * @details This function disables the GPIOI clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_GPIOI_DisableClockInStopMode(void)
{
  LL_AHB4_GRP1_DisableClockLowPower(LL_AHB4_GRP1_PERIPH_GPIOI);
}

/**
  * @details This function disables the CRC clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_CRC_DisableClockInSleepMode(void)
{
  LL_AHB4_GRP1_DisableClockLowPower(LL_AHB4_GRP1_PERIPH_CRC);
}

/**
  * @details This function disables the CRC clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_CRC_DisableClockInStopMode(void)
{
  LL_AHB4_GRP1_DisableClockLowPower(LL_AHB4_GRP1_PERIPH_CRC);
}

/**
  * @details This function disables the BKPRAM clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_BKPRAM_DisableClockInSleepMode(void)
{
  LL_AHB4_GRP1_DisableClockLowPower(LL_AHB4_GRP1_PERIPH_BKPRAM);
}

/**
  * @details This function disables the BKPRAM clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_BKPRAM_DisableClockInStopMode(void)
{
  LL_AHB4_GRP1_DisableClockLowPower(LL_AHB4_GRP1_PERIPH_BKPRAM);
}

/**
  * @}
  */ /* RCC_AHB4_Peripheral_Clock_Sleep_Enable_Disable */

/** @defgroup RCC_AHB5_Peripheral_Clock_Sleep_Enable_Disable AHB5 Peripheral Clock Sleep Enable Disable
  * @brief  Enable or disable the AHB5 peripheral clock during Low Power (Sleep and Stop) mode.
  * @note   Peripheral clock gating in SLEEP and STOP modes can be used to further reduce power consumption.
  * @note   After wakeup from SLEEP or STOP modes, the peripheral clock is enabled again.
  * @note   By default, all peripheral clocks are enabled during SLEEP mode. In STOP mode peripheral clock
  *         is enabled only when a peripheral requests AHB clock.
  * @{
  */

/**
  * @details This function enables the HPDMA1 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_HPDMA1_EnableClockInSleepMode(void)
{
  LL_AHB5_GRP1_EnableClockLowPower(LL_AHB5_GRP1_PERIPH_HPDMA1);
}

/**
  * @details This function enables the HPDMA1 clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_HPDMA1_EnableClockInStopMode(void)
{
  LL_AHB5_GRP1_EnableClockLowPower(LL_AHB5_GRP1_PERIPH_HPDMA1);
}

/**
  * @details This function enables the FLASH clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_FLASH_EnableClockInSleepMode(void)
{
  LL_AHB5_GRP1_EnableClockLowPower(LL_AHB5_GRP1_PERIPH_FLASH);
}

/**
  * @details This function enables the FLASH clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_FLASH_EnableClockInStopMode(void)
{
  LL_AHB5_GRP1_EnableClockLowPower(LL_AHB5_GRP1_PERIPH_FLASH);
}

/**
  * @details This function enables the FMC clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_FMC_EnableClockInSleepMode(void)
{
  LL_AHB5_GRP1_EnableClockLowPower(LL_AHB5_GRP1_PERIPH_FMC);
}

/**
  * @details This function enables the FMC clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_FMC_EnableClockInStopMode(void)
{
  LL_AHB5_GRP1_EnableClockLowPower(LL_AHB5_GRP1_PERIPH_FMC);
}

/**
  * @details This function enables the XSPI1 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_XSPI1_EnableClockInSleepMode(void)
{
  LL_AHB5_GRP1_EnableClockLowPower(LL_AHB5_GRP1_PERIPH_XSPI1);
}

/**
  * @details This function enables the XSPI1 clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_XSPI1_EnableClockInStopMode(void)
{
  LL_AHB5_GRP1_EnableClockLowPower(LL_AHB5_GRP1_PERIPH_XSPI1);
}

/**
  * @details This function enables the SDMMC1 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_SDMMC1_EnableClockInSleepMode(void)
{
  LL_AHB5_GRP1_EnableClockLowPower(LL_AHB5_GRP1_PERIPH_SDMMC1);
}

/**
  * @details This function enables the SDMMC1 clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_SDMMC1_EnableClockInStopMode(void)
{
  LL_AHB5_GRP1_EnableClockLowPower(LL_AHB5_GRP1_PERIPH_SDMMC1);
}

/**
  * @details This function enables the AXISRAM clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_AXISRAM_EnableClockInSleepMode(void)
{
  LL_AHB5_GRP1_EnableClockLowPower(LL_AHB5_GRP1_PERIPH_AXISRAM);
}

/**
  * @details This function enables the AXISRAM clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_AXISRAM_EnableClockInStopMode(void)
{
  LL_AHB5_GRP1_EnableClockLowPower(LL_AHB5_GRP1_PERIPH_AXISRAM);
}

/**
  * @details This function enables the DTCM1 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_DTCM1_EnableClockInSleepMode(void)
{
  LL_AHB5_GRP1_EnableClockLowPower(LL_AHB5_GRP1_PERIPH_DTCM1);
}

/**
  * @details This function enables the DTCM1 clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_DTCM1_EnableClockInStopMode(void)
{
  LL_AHB5_GRP1_EnableClockLowPower(LL_AHB5_GRP1_PERIPH_DTCM1);
}

/**
  * @details This function enables the DTCM2 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_DTCM2_EnableClockInSleepMode(void)
{
  LL_AHB5_GRP1_EnableClockLowPower(LL_AHB5_GRP1_PERIPH_DTCM2);
}

/**
  * @details This function enables the DTCM2 clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_DTCM2_EnableClockInStopMode(void)
{
  LL_AHB5_GRP1_EnableClockLowPower(LL_AHB5_GRP1_PERIPH_DTCM2);
}

/**
  * @details This function enables the ITCM clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_ITCM_EnableClockInSleepMode(void)
{
  LL_AHB5_GRP1_EnableClockLowPower(LL_AHB5_GRP1_PERIPH_ITCM);
}

/**
  * @details This function enables the ITCM clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_ITCM_EnableClockInStopMode(void)
{
  LL_AHB5_GRP1_EnableClockLowPower(LL_AHB5_GRP1_PERIPH_ITCM);
}

/**
  * @details This function enables the NPU clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_NPU_EnableClockInSleepMode(void)
{
  LL_AHB5_GRP1_EnableClockLowPower(LL_AHB5_GRP1_PERIPH_NPU);
}

/**
  * @details This function enables the NPU clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_NPU_EnableClockInStopMode(void)
{
  LL_AHB5_GRP1_EnableClockLowPower(LL_AHB5_GRP1_PERIPH_NPU);
}

/**
  * @details This function disables the HPDMA1 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_HPDMA1_DisableClockInSleepMode(void)
{
  LL_AHB5_GRP1_DisableClockLowPower(LL_AHB5_GRP1_PERIPH_HPDMA1);
}

/**
  * @details This function disables the HPDMA1 clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_HPDMA1_DisableClockInStopMode(void)
{
  LL_AHB5_GRP1_DisableClockLowPower(LL_AHB5_GRP1_PERIPH_HPDMA1);
}

/**
  * @details This function disables the FLASH clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_FLASH_DisableClockInSleepMode(void)
{
  LL_AHB5_GRP1_DisableClockLowPower(LL_AHB5_GRP1_PERIPH_FLASH);
}

/**
  * @details This function disables the FLASH clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_FLASH_DisableClockInStopMode(void)
{
  LL_AHB5_GRP1_DisableClockLowPower(LL_AHB5_GRP1_PERIPH_FLASH);
}

/**
  * @details This function disables the FMC clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_FMC_DisableClockInSleepMode(void)
{
  LL_AHB5_GRP1_DisableClockLowPower(LL_AHB5_GRP1_PERIPH_FMC);
}

/**
  * @details This function disables the FMC clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_FMC_DisableClockInStopMode(void)
{
  LL_AHB5_GRP1_DisableClockLowPower(LL_AHB5_GRP1_PERIPH_FMC);
}

/**
  * @details This function disables the XSPI1 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_XSPI1_DisableClockInSleepMode(void)
{
  LL_AHB5_GRP1_DisableClockLowPower(LL_AHB5_GRP1_PERIPH_XSPI1);
}

/**
  * @details This function disables the XSPI1 clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_XSPI1_DisableClockInStopMode(void)
{
  LL_AHB5_GRP1_DisableClockLowPower(LL_AHB5_GRP1_PERIPH_XSPI1);
}

/**
  * @details This function disables the SDMMC1 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_SDMMC1_DisableClockInSleepMode(void)
{
  LL_AHB5_GRP1_DisableClockLowPower(LL_AHB5_GRP1_PERIPH_SDMMC1);
}

/**
  * @details This function disables the SDMMC1 clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_SDMMC1_DisableClockInStopMode(void)
{
  LL_AHB5_GRP1_DisableClockLowPower(LL_AHB5_GRP1_PERIPH_SDMMC1);
}

/**
  * @details This function disables the AXISRAM clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_AXISRAM_DisableClockInSleepMode(void)
{
  LL_AHB5_GRP1_DisableClockLowPower(LL_AHB5_GRP1_PERIPH_AXISRAM);
}

/**
  * @details This function disables the AXISRAM clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_AXISRAM_DisableClockInStopMode(void)
{
  LL_AHB5_GRP1_DisableClockLowPower(LL_AHB5_GRP1_PERIPH_AXISRAM);
}

/**
  * @details This function disables the DTCM1 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_DTCM1_DisableClockInSleepMode(void)
{
  LL_AHB5_GRP1_DisableClockLowPower(LL_AHB5_GRP1_PERIPH_DTCM1);
}

/**
  * @details This function disables the DTCM1 clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_DTCM1_DisableClockInStopMode(void)
{
  LL_AHB5_GRP1_DisableClockLowPower(LL_AHB5_GRP1_PERIPH_DTCM1);
}

/**
  * @details This function disables the DTCM2 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_DTCM2_DisableClockInSleepMode(void)
{
  LL_AHB5_GRP1_DisableClockLowPower(LL_AHB5_GRP1_PERIPH_DTCM2);
}

/**
  * @details This function disables the DTCM2 clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_DTCM2_DisableClockInStopMode(void)
{
  LL_AHB5_GRP1_DisableClockLowPower(LL_AHB5_GRP1_PERIPH_DTCM2);
}

/**
  * @details This function disables the ITCM clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_ITCM_DisableClockInSleepMode(void)
{
  LL_AHB5_GRP1_DisableClockLowPower(LL_AHB5_GRP1_PERIPH_ITCM);
}

/**
  * @details This function disables the ITCM clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_ITCM_DisableClockInStopMode(void)
{
  LL_AHB5_GRP1_DisableClockLowPower(LL_AHB5_GRP1_PERIPH_ITCM);
}

/**
  * @details This function disables the NPU clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_NPU_DisableClockInSleepMode(void)
{
  LL_AHB5_GRP1_DisableClockLowPower(LL_AHB5_GRP1_PERIPH_NPU);
}

/**
  * @details This function disables the NPU clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_NPU_DisableClockInStopMode(void)
{
  LL_AHB5_GRP1_DisableClockLowPower(LL_AHB5_GRP1_PERIPH_NPU);
}

/**
  * @}
  */ /* RCC_AHB5_Peripheral_Clock_Sleep_Enable_Disable */

/** @defgroup RCC_APB1_Peripheral_Clock_Sleep_Enable_Disable APB1 Peripheral Clock Sleep Enable Disable
  * @brief  Enable or disable the APB1 peripheral clock during Low Power (Sleep and Stop) mode.
  * @note   Peripheral clock gating in SLEEP and STOP modes can be used to further reduce power consumption.
  * @note   After wakeup from SLEEP or STOP modes, the peripheral clock is enabled again.
  * @note   By default, all peripheral clocks are enabled during SLEEP mode. In STOP mode peripheral clock
  *         is enabled only when a peripheral requests AHB clock.
  * @{
  */

/**
  * @details This function enables the TIM2 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_TIM2_EnableClockInSleepMode(void)
{
  LL_APB1_GRP1_EnableClockLowPower(LL_APB1_GRP1_PERIPH_TIM2);
}

/**
  * @details This function enables the TIM2 clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_TIM2_EnableClockInStopMode(void)
{
  LL_APB1_GRP1_EnableClockLowPower(LL_APB1_GRP1_PERIPH_TIM2);
}

/**
  * @details This function enables the TIM3 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_TIM3_EnableClockInSleepMode(void)
{
  LL_APB1_GRP1_EnableClockLowPower(LL_APB1_GRP1_PERIPH_TIM3);
}

/**
  * @details This function enables the TIM3 clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_TIM3_EnableClockInStopMode(void)
{
  LL_APB1_GRP1_EnableClockLowPower(LL_APB1_GRP1_PERIPH_TIM3);
}

/**
  * @details This function enables the TIM4 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_TIM4_EnableClockInSleepMode(void)
{
  LL_APB1_GRP1_EnableClockLowPower(LL_APB1_GRP1_PERIPH_TIM4);
}

/**
  * @details This function enables the TIM4 clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_TIM4_EnableClockInStopMode(void)
{
  LL_APB1_GRP1_EnableClockLowPower(LL_APB1_GRP1_PERIPH_TIM4);
}

/**
  * @details This function enables the TIM5 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_TIM5_EnableClockInSleepMode(void)
{
  LL_APB1_GRP1_EnableClockLowPower(LL_APB1_GRP1_PERIPH_TIM5);
}

/**
  * @details This function enables the TIM5 clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_TIM5_EnableClockInStopMode(void)
{
  LL_APB1_GRP1_EnableClockLowPower(LL_APB1_GRP1_PERIPH_TIM5);
}

/**
  * @details This function enables the TIM6 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_TIM6_EnableClockInSleepMode(void)
{
  LL_APB1_GRP1_EnableClockLowPower(LL_APB1_GRP1_PERIPH_TIM6);
}

/**
  * @details This function enables the TIM6 clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_TIM6_EnableClockInStopMode(void)
{
  LL_APB1_GRP1_EnableClockLowPower(LL_APB1_GRP1_PERIPH_TIM6);
}

/**
  * @details This function enables the TIM7 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_TIM7_EnableClockInSleepMode(void)
{
  LL_APB1_GRP1_EnableClockLowPower(LL_APB1_GRP1_PERIPH_TIM7);
}

/**
  * @details This function enables the TIM7 clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_TIM7_EnableClockInStopMode(void)
{
  LL_APB1_GRP1_EnableClockLowPower(LL_APB1_GRP1_PERIPH_TIM7);
}

/**
  * @details This function enables the TIM12 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_TIM12_EnableClockInSleepMode(void)
{
  LL_APB1_GRP1_EnableClockLowPower(LL_APB1_GRP1_PERIPH_TIM12);
}

/**
  * @details This function enables the TIM12 clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_TIM12_EnableClockInStopMode(void)
{
  LL_APB1_GRP1_EnableClockLowPower(LL_APB1_GRP1_PERIPH_TIM12);
}

/**
  * @details This function enables the TIM13 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_TIM13_EnableClockInSleepMode(void)
{
  LL_APB1_GRP1_EnableClockLowPower(LL_APB1_GRP1_PERIPH_TIM13);
}

/**
  * @details This function enables the TIM13 clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_TIM13_EnableClockInStopMode(void)
{
  LL_APB1_GRP1_EnableClockLowPower(LL_APB1_GRP1_PERIPH_TIM13);
}

/**
  * @details This function enables the TIM14 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_TIM14_EnableClockInSleepMode(void)
{
  LL_APB1_GRP1_EnableClockLowPower(LL_APB1_GRP1_PERIPH_TIM14);
}

/**
  * @details This function enables the TIM14 clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_TIM14_EnableClockInStopMode(void)
{
  LL_APB1_GRP1_EnableClockLowPower(LL_APB1_GRP1_PERIPH_TIM14);
}

/**
  * @details This function enables the LPTIM1 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LPTIM1_EnableClockInSleepMode(void)
{
  LL_APB1_GRP1_EnableClockLowPower(LL_APB1_GRP1_PERIPH_LPTIM1);
}

/**
  * @details This function enables the LPTIM1 clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_LPTIM1_EnableClockInStopMode(void)
{
  LL_APB1_GRP1_EnableClockLowPower(LL_APB1_GRP1_PERIPH_LPTIM1);
}

/**
  * @details This function enables the WWDG clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_WWDG_EnableClockInSleepMode(void)
{
  LL_APB1_GRP1_EnableClockLowPower(LL_APB1_GRP1_PERIPH_WWDG);
}

/**
  * @details This function enables the WWDG clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_WWDG_EnableClockInStopMode(void)
{
  LL_APB1_GRP1_EnableClockLowPower(LL_APB1_GRP1_PERIPH_WWDG);
}

/**
  * @details This function enables the TIM10 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_TIM10_EnableClockInSleepMode(void)
{
  LL_APB1_GRP1_EnableClockLowPower(LL_APB1_GRP1_PERIPH_TIM10);
}

/**
  * @details This function enables the TIM10 clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_TIM10_EnableClockInStopMode(void)
{
  LL_APB1_GRP1_EnableClockLowPower(LL_APB1_GRP1_PERIPH_TIM10);
}

/**
  * @details This function enables the TIM11 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_TIM11_EnableClockInSleepMode(void)
{
  LL_APB1_GRP1_EnableClockLowPower(LL_APB1_GRP1_PERIPH_TIM11);
}

/**
  * @details This function enables the TIM11 clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_TIM11_EnableClockInStopMode(void)
{
  LL_APB1_GRP1_EnableClockLowPower(LL_APB1_GRP1_PERIPH_TIM11);
}

/**
  * @details This function enables the SPI2 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_SPI2_EnableClockInSleepMode(void)
{
  LL_APB1_GRP1_EnableClockLowPower(LL_APB1_GRP1_PERIPH_SPI2);
}

/**
  * @details This function enables the SPI2 clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_SPI2_EnableClockInStopMode(void)
{
  LL_APB1_GRP1_EnableClockLowPower(LL_APB1_GRP1_PERIPH_SPI2);
}

/**
  * @details This function enables the SPI3 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_SPI3_EnableClockInSleepMode(void)
{
  LL_APB1_GRP1_EnableClockLowPower(LL_APB1_GRP1_PERIPH_SPI3);
}

/**
  * @details This function enables the SPI3 clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_SPI3_EnableClockInStopMode(void)
{
  LL_APB1_GRP1_EnableClockLowPower(LL_APB1_GRP1_PERIPH_SPI3);
}

/**
  * @details This function enables the USART2 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_USART2_EnableClockInSleepMode(void)
{
  LL_APB1_GRP1_EnableClockLowPower(LL_APB1_GRP1_PERIPH_USART2);
}

/**
  * @details This function enables the USART2 clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_USART2_EnableClockInStopMode(void)
{
  LL_APB1_GRP1_EnableClockLowPower(LL_APB1_GRP1_PERIPH_USART2);
}

/**
  * @details This function enables the USART3 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_USART3_EnableClockInSleepMode(void)
{
  LL_APB1_GRP1_EnableClockLowPower(LL_APB1_GRP1_PERIPH_USART3);
}

/**
  * @details This function enables the USART3 clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_USART3_EnableClockInStopMode(void)
{
  LL_APB1_GRP1_EnableClockLowPower(LL_APB1_GRP1_PERIPH_USART3);
}

/**
  * @details This function enables the UART4 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_UART4_EnableClockInSleepMode(void)
{
  LL_APB1_GRP1_EnableClockLowPower(LL_APB1_GRP1_PERIPH_UART4);
}

/**
  * @details This function enables the UART4 clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_UART4_EnableClockInStopMode(void)
{
  LL_APB1_GRP1_EnableClockLowPower(LL_APB1_GRP1_PERIPH_UART4);
}

/**
  * @details This function enables the UART5 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_UART5_EnableClockInSleepMode(void)
{
  LL_APB1_GRP1_EnableClockLowPower(LL_APB1_GRP1_PERIPH_UART5);
}

/**
  * @details This function enables the UART5 clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_UART5_EnableClockInStopMode(void)
{
  LL_APB1_GRP1_EnableClockLowPower(LL_APB1_GRP1_PERIPH_UART5);
}

/**
  * @details This function enables the I2C1 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_I2C1_EnableClockInSleepMode(void)
{
  LL_APB1_GRP1_EnableClockLowPower(LL_APB1_GRP1_PERIPH_I2C1);
}

/**
  * @details This function enables the I2C1 clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_I2C1_EnableClockInStopMode(void)
{
  LL_APB1_GRP1_EnableClockLowPower(LL_APB1_GRP1_PERIPH_I2C1);
}

/**
  * @details This function enables the I2C2 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_I2C2_EnableClockInSleepMode(void)
{
  LL_APB1_GRP1_EnableClockLowPower(LL_APB1_GRP1_PERIPH_I2C2);
}

/**
  * @details This function enables the I2C2 clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_I2C2_EnableClockInStopMode(void)
{
  LL_APB1_GRP1_EnableClockLowPower(LL_APB1_GRP1_PERIPH_I2C2);
}

/**
  * @details This function enables the I2C3 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_I2C3_EnableClockInSleepMode(void)
{
  LL_APB1_GRP1_EnableClockLowPower(LL_APB1_GRP1_PERIPH_I2C3);
}

/**
  * @details This function enables the I2C3 clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_I2C3_EnableClockInStopMode(void)
{
  LL_APB1_GRP1_EnableClockLowPower(LL_APB1_GRP1_PERIPH_I2C3);
}

/**
  * @details This function enables the I3C1 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_I3C1_EnableClockInSleepMode(void)
{
  LL_APB1_GRP1_EnableClockLowPower(LL_APB1_GRP1_PERIPH_I3C1);
}

/**
  * @details This function enables the I3C1 clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_I3C1_EnableClockInStopMode(void)
{
  LL_APB1_GRP1_EnableClockLowPower(LL_APB1_GRP1_PERIPH_I3C1);
}

/**
  * @details This function enables the UART7 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_UART7_EnableClockInSleepMode(void)
{
  LL_APB1_GRP1_EnableClockLowPower(LL_APB1_GRP1_PERIPH_UART7);
}

/**
  * @details This function enables the UART7 clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_UART7_EnableClockInStopMode(void)
{
  LL_APB1_GRP1_EnableClockLowPower(LL_APB1_GRP1_PERIPH_UART7);
}

/**
  * @details This function enables the UART8 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_UART8_EnableClockInSleepMode(void)
{
  LL_APB1_GRP1_EnableClockLowPower(LL_APB1_GRP1_PERIPH_UART8);
}

/**
  * @details This function enables the UART8 clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_UART8_EnableClockInStopMode(void)
{
  LL_APB1_GRP1_EnableClockLowPower(LL_APB1_GRP1_PERIPH_UART8);
}

/**
  * @details This function disables the TIM2 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_TIM2_DisableClockInSleepMode(void)
{
  LL_APB1_GRP1_DisableClockLowPower(LL_APB1_GRP1_PERIPH_TIM2);
}

/**
  * @details This function disables the TIM2 clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_TIM2_DisableClockInStopMode(void)
{
  LL_APB1_GRP1_DisableClockLowPower(LL_APB1_GRP1_PERIPH_TIM2);
}

/**
  * @details This function disables the TIM3 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_TIM3_DisableClockInSleepMode(void)
{
  LL_APB1_GRP1_DisableClockLowPower(LL_APB1_GRP1_PERIPH_TIM3);
}

/**
  * @details This function disables the TIM3 clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_TIM3_DisableClockInStopMode(void)
{
  LL_APB1_GRP1_DisableClockLowPower(LL_APB1_GRP1_PERIPH_TIM3);
}

/**
  * @details This function disables the TIM4 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_TIM4_DisableClockInSleepMode(void)
{
  LL_APB1_GRP1_DisableClockLowPower(LL_APB1_GRP1_PERIPH_TIM4);
}

/**
  * @details This function disables the TIM4 clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_TIM4_DisableClockInStopMode(void)
{
  LL_APB1_GRP1_DisableClockLowPower(LL_APB1_GRP1_PERIPH_TIM4);
}

/**
  * @details This function disables the TIM5 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_TIM5_DisableClockInSleepMode(void)
{
  LL_APB1_GRP1_DisableClockLowPower(LL_APB1_GRP1_PERIPH_TIM5);
}

/**
  * @details This function disables the TIM5 clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_TIM5_DisableClockInStopMode(void)
{
  LL_APB1_GRP1_DisableClockLowPower(LL_APB1_GRP1_PERIPH_TIM5);
}

/**
  * @details This function disables the TIM6 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_TIM6_DisableClockInSleepMode(void)
{
  LL_APB1_GRP1_DisableClockLowPower(LL_APB1_GRP1_PERIPH_TIM6);
}

/**
  * @details This function disables the TIM6 clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_TIM6_DisableClockInStopMode(void)
{
  LL_APB1_GRP1_DisableClockLowPower(LL_APB1_GRP1_PERIPH_TIM6);
}

/**
  * @details This function disables the TIM7 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_TIM7_DisableClockInSleepMode(void)
{
  LL_APB1_GRP1_DisableClockLowPower(LL_APB1_GRP1_PERIPH_TIM7);
}

/**
  * @details This function disables the TIM7 clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_TIM7_DisableClockInStopMode(void)
{
  LL_APB1_GRP1_DisableClockLowPower(LL_APB1_GRP1_PERIPH_TIM7);
}

/**
  * @details This function disables the TIM12 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_TIM12_DisableClockInSleepMode(void)
{
  LL_APB1_GRP1_DisableClockLowPower(LL_APB1_GRP1_PERIPH_TIM12);
}

/**
  * @details This function disables the TIM12 clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_TIM12_DisableClockInStopMode(void)
{
  LL_APB1_GRP1_DisableClockLowPower(LL_APB1_GRP1_PERIPH_TIM12);
}

/**
  * @details This function disables the TIM13 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_TIM13_DisableClockInSleepMode(void)
{
  LL_APB1_GRP1_DisableClockLowPower(LL_APB1_GRP1_PERIPH_TIM13);
}

/**
  * @details This function disables the TIM13 clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_TIM13_DisableClockInStopMode(void)
{
  LL_APB1_GRP1_DisableClockLowPower(LL_APB1_GRP1_PERIPH_TIM13);
}

/**
  * @details This function disables the TIM14 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_TIM14_DisableClockInSleepMode(void)
{
  LL_APB1_GRP1_DisableClockLowPower(LL_APB1_GRP1_PERIPH_TIM14);
}

/**
  * @details This function disables the TIM14 clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_TIM14_DisableClockInStopMode(void)
{
  LL_APB1_GRP1_DisableClockLowPower(LL_APB1_GRP1_PERIPH_TIM14);
}

/**
  * @details This function disables the LPTIM1 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LPTIM1_DisableClockInSleepMode(void)
{
  LL_APB1_GRP1_DisableClockLowPower(LL_APB1_GRP1_PERIPH_LPTIM1);
}

/**
  * @details This function disables the LPTIM1 clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_LPTIM1_DisableClockInStopMode(void)
{
  LL_APB1_GRP1_DisableClockLowPower(LL_APB1_GRP1_PERIPH_LPTIM1);
}

/**
  * @details This function disables the WWDG clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_WWDG_DisableClockInSleepMode(void)
{
  LL_APB1_GRP1_DisableClockLowPower(LL_APB1_GRP1_PERIPH_WWDG);
}

/**
  * @details This function disables the WWDG clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_WWDG_DisableClockInStopMode(void)
{
  LL_APB1_GRP1_DisableClockLowPower(LL_APB1_GRP1_PERIPH_WWDG);
}

/**
  * @details This function disables the TIM10 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_TIM10_DisableClockInSleepMode(void)
{
  LL_APB1_GRP1_DisableClockLowPower(LL_APB1_GRP1_PERIPH_TIM10);
}

/**
  * @details This function disables the TIM10 clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_TIM10_DisableClockInStopMode(void)
{
  LL_APB1_GRP1_DisableClockLowPower(LL_APB1_GRP1_PERIPH_TIM10);
}

/**
  * @details This function disables the TIM11 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_TIM11_DisableClockInSleepMode(void)
{
  LL_APB1_GRP1_DisableClockLowPower(LL_APB1_GRP1_PERIPH_TIM11);
}

/**
  * @details This function disables the TIM11 clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_TIM11_DisableClockInStopMode(void)
{
  LL_APB1_GRP1_DisableClockLowPower(LL_APB1_GRP1_PERIPH_TIM11);
}

/**
  * @details This function disables the SPI2 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_SPI2_DisableClockInSleepMode(void)
{
  LL_APB1_GRP1_DisableClockLowPower(LL_APB1_GRP1_PERIPH_SPI2);
}

/**
  * @details This function disables the SPI2 clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_SPI2_DisableClockInStopMode(void)
{
  LL_APB1_GRP1_DisableClockLowPower(LL_APB1_GRP1_PERIPH_SPI2);
}

/**
  * @details This function disables the SPI3 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_SPI3_DisableClockInSleepMode(void)
{
  LL_APB1_GRP1_DisableClockLowPower(LL_APB1_GRP1_PERIPH_SPI3);
}

/**
  * @details This function disables the SPI3 clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_SPI3_DisableClockInStopMode(void)
{
  LL_APB1_GRP1_DisableClockLowPower(LL_APB1_GRP1_PERIPH_SPI3);
}

/**
  * @details This function disables the USART2 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_USART2_DisableClockInSleepMode(void)
{
  LL_APB1_GRP1_DisableClockLowPower(LL_APB1_GRP1_PERIPH_USART2);
}

/**
  * @details This function disables the USART2 clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_USART2_DisableClockInStopMode(void)
{
  LL_APB1_GRP1_DisableClockLowPower(LL_APB1_GRP1_PERIPH_USART2);
}

/**
  * @details This function disables the USART3 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_USART3_DisableClockInSleepMode(void)
{
  LL_APB1_GRP1_DisableClockLowPower(LL_APB1_GRP1_PERIPH_USART3);
}

/**
  * @details This function disables the USART3 clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_USART3_DisableClockInStopMode(void)
{
  LL_APB1_GRP1_DisableClockLowPower(LL_APB1_GRP1_PERIPH_USART3);
}

/**
  * @details This function disables the UART4 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_UART4_DisableClockInSleepMode(void)
{
  LL_APB1_GRP1_DisableClockLowPower(LL_APB1_GRP1_PERIPH_UART4);
}

/**
  * @details This function disables the UART4 clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_UART4_DisableClockInStopMode(void)
{
  LL_APB1_GRP1_DisableClockLowPower(LL_APB1_GRP1_PERIPH_UART4);
}

/**
  * @details This function disables the UART5 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_UART5_DisableClockInSleepMode(void)
{
  LL_APB1_GRP1_DisableClockLowPower(LL_APB1_GRP1_PERIPH_UART5);
}

/**
  * @details This function disables the UART5 clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_UART5_DisableClockInStopMode(void)
{
  LL_APB1_GRP1_DisableClockLowPower(LL_APB1_GRP1_PERIPH_UART5);
}

/**
  * @details This function disables the I2C1 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_I2C1_DisableClockInSleepMode(void)
{
  LL_APB1_GRP1_DisableClockLowPower(LL_APB1_GRP1_PERIPH_I2C1);
}

/**
  * @details This function disables the I2C1 clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_I2C1_DisableClockInStopMode(void)
{
  LL_APB1_GRP1_DisableClockLowPower(LL_APB1_GRP1_PERIPH_I2C1);
}

/**
  * @details This function disables the I2C2 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_I2C2_DisableClockInSleepMode(void)
{
  LL_APB1_GRP1_DisableClockLowPower(LL_APB1_GRP1_PERIPH_I2C2);
}

/**
  * @details This function disables the I2C2 clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_I2C2_DisableClockInStopMode(void)
{
  LL_APB1_GRP1_DisableClockLowPower(LL_APB1_GRP1_PERIPH_I2C2);
}

/**
  * @details This function disables the I2C3 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_I2C3_DisableClockInSleepMode(void)
{
  LL_APB1_GRP1_DisableClockLowPower(LL_APB1_GRP1_PERIPH_I2C3);
}

/**
  * @details This function disables the I2C3 clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_I2C3_DisableClockInStopMode(void)
{
  LL_APB1_GRP1_DisableClockLowPower(LL_APB1_GRP1_PERIPH_I2C3);
}

/**
  * @details This function disables the I3C1 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_I3C1_DisableClockInSleepMode(void)
{
  LL_APB1_GRP1_DisableClockLowPower(LL_APB1_GRP1_PERIPH_I3C1);
}

/**
  * @details This function disables the I3C1 clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_I3C1_DisableClockInStopMode(void)
{
  LL_APB1_GRP1_DisableClockLowPower(LL_APB1_GRP1_PERIPH_I3C1);
}

/**
  * @details This function disables the UART7 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_UART7_DisableClockInSleepMode(void)
{
  LL_APB1_GRP1_DisableClockLowPower(LL_APB1_GRP1_PERIPH_UART7);
}

/**
  * @details This function disables the UART7 clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_UART7_DisableClockInStopMode(void)
{
  LL_APB1_GRP1_DisableClockLowPower(LL_APB1_GRP1_PERIPH_UART7);
}

/**
  * @details This function disables the UART8 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_UART8_DisableClockInSleepMode(void)
{
  LL_APB1_GRP1_DisableClockLowPower(LL_APB1_GRP1_PERIPH_UART8);
}

/**
  * @details This function disables the UART8 clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_UART8_DisableClockInStopMode(void)
{
  LL_APB1_GRP1_DisableClockLowPower(LL_APB1_GRP1_PERIPH_UART8);
}

/**
  * @}
  */ /* RCC_APB1_Peripheral_Clock_Sleep_Enable_Disable */

/** @defgroup RCC_APB1_Peripheral_Clock_Sleep_Enable_Disable APB1 Peripheral Clock Sleep Enable Disable
  * @brief  Enable or disable the APB1 peripheral clock during Low Power (Sleep and Stop) mode.
  * @note   Peripheral clock gating in SLEEP and STOP modes can be used to further reduce power consumption.
  * @note   After wakeup from SLEEP or STOP modes, the peripheral clock is enabled again.
  * @note   By default, all peripheral clocks are enabled during SLEEP mode. In STOP mode peripheral clock
  *         is enabled only when a peripheral requests AHB clock.
  * @{
  */

/**
  * @details This function enables the CRS clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_CRS_EnableClockInSleepMode(void)
{
  LL_APB1_GRP2_EnableClockLowPower(LL_APB1_GRP2_PERIPH_CRS);
}

/**
  * @details This function enables the CRS clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_CRS_EnableClockInStopMode(void)
{
  LL_APB1_GRP2_EnableClockLowPower(LL_APB1_GRP2_PERIPH_CRS);
}

/**
  * @details This function enables the FDCAN clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_FDCAN_EnableClockInSleepMode(void)
{
  LL_APB1_GRP2_EnableClockLowPower(LL_APB1_GRP2_PERIPH_FDCAN);
}

/**
  * @details This function enables the FDCAN clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_FDCAN_EnableClockInStopMode(void)
{
  LL_APB1_GRP2_EnableClockLowPower(LL_APB1_GRP2_PERIPH_FDCAN);
}

/**
  * @details This function enables the UCPD1 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_UCPD1_EnableClockInSleepMode(void)
{
  LL_APB1_GRP2_EnableClockLowPower(LL_APB1_GRP2_PERIPH_UCPD1);
}

/**
  * @details This function enables the UCPD1 clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_UCPD1_EnableClockInStopMode(void)
{
  LL_APB1_GRP2_EnableClockLowPower(LL_APB1_GRP2_PERIPH_UCPD1);
}

/**
  * @details This function disables the CRS clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_CRS_DisableClockInSleepMode(void)
{
  LL_APB1_GRP2_DisableClockLowPower(LL_APB1_GRP2_PERIPH_CRS);
}

/**
  * @details This function disables the CRS clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_CRS_DisableClockInStopMode(void)
{
  LL_APB1_GRP2_DisableClockLowPower(LL_APB1_GRP2_PERIPH_CRS);
}

/**
  * @details This function disables the FDCAN clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_FDCAN_DisableClockInSleepMode(void)
{
  LL_APB1_GRP2_DisableClockLowPower(LL_APB1_GRP2_PERIPH_FDCAN);
}

/**
  * @details This function disables the FDCAN clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_FDCAN_DisableClockInStopMode(void)
{
  LL_APB1_GRP2_DisableClockLowPower(LL_APB1_GRP2_PERIPH_FDCAN);
}

/**
  * @details This function disables the UCPD1 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_UCPD1_DisableClockInSleepMode(void)
{
  LL_APB1_GRP2_DisableClockLowPower(LL_APB1_GRP2_PERIPH_UCPD1);
}

/**
  * @details This function disables the UCPD1 clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_UCPD1_DisableClockInStopMode(void)
{
  LL_APB1_GRP2_DisableClockLowPower(LL_APB1_GRP2_PERIPH_UCPD1);
}

/**
  * @}
  */ /* RCC_APB1_Peripheral_Clock_Sleep_Enable_Disable */

/** @defgroup RCC_APB2_Peripheral_Clock_Sleep_Enable_Disable APB2 Peripheral Clock Sleep Enable Disable
  * @brief  Enable or disable the APB2 peripheral clock during Low Power (Sleep and Stop) mode.
  * @note   Peripheral clock gating in SLEEP and STOP modes can be used to further reduce power consumption.
  * @note   After wakeup from SLEEP or STOP modes, the peripheral clock is enabled again.
  * @note   By default, all peripheral clocks are enabled during SLEEP mode. In STOP mode peripheral clock
  *         is enabled only when a peripheral requests AHB clock.
  * @{
  */

/**
  * @details This function enables the TIM1 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_TIM1_EnableClockInSleepMode(void)
{
  LL_APB2_GRP1_EnableClockLowPower(LL_APB2_GRP1_PERIPH_TIM1);
}

/**
  * @details This function enables the TIM1 clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_TIM1_EnableClockInStopMode(void)
{
  LL_APB2_GRP1_EnableClockLowPower(LL_APB2_GRP1_PERIPH_TIM1);
}

/**
  * @details This function enables the TIM8 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_TIM8_EnableClockInSleepMode(void)
{
  LL_APB2_GRP1_EnableClockLowPower(LL_APB2_GRP1_PERIPH_TIM8);
}

/**
  * @details This function enables the TIM8 clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_TIM8_EnableClockInStopMode(void)
{
  LL_APB2_GRP1_EnableClockLowPower(LL_APB2_GRP1_PERIPH_TIM8);
}

/**
  * @details This function enables the TIM20 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_TIM20_EnableClockInSleepMode(void)
{
  LL_APB2_GRP1_EnableClockLowPower(LL_APB2_GRP1_PERIPH_TIM20);
}

/**
  * @details This function enables the TIM20 clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_TIM20_EnableClockInStopMode(void)
{
  LL_APB2_GRP1_EnableClockLowPower(LL_APB2_GRP1_PERIPH_TIM20);
}

/**
  * @details This function enables the USART1 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_USART1_EnableClockInSleepMode(void)
{
  LL_APB2_GRP1_EnableClockLowPower(LL_APB2_GRP1_PERIPH_USART1);
}

/**
  * @details This function enables the USART1 clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_USART1_EnableClockInStopMode(void)
{
  LL_APB2_GRP1_EnableClockLowPower(LL_APB2_GRP1_PERIPH_USART1);
}

/**
  * @details This function enables the USART6 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_USART6_EnableClockInSleepMode(void)
{
  LL_APB2_GRP1_EnableClockLowPower(LL_APB2_GRP1_PERIPH_USART6);
}

/**
  * @details This function enables the USART6 clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_USART6_EnableClockInStopMode(void)
{
  LL_APB2_GRP1_EnableClockLowPower(LL_APB2_GRP1_PERIPH_USART6);
}

/**
  * @details This function enables the UART9 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_UART9_EnableClockInSleepMode(void)
{
  LL_APB2_GRP1_EnableClockLowPower(LL_APB2_GRP1_PERIPH_UART9);
}

/**
  * @details This function enables the UART9 clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_UART9_EnableClockInStopMode(void)
{
  LL_APB2_GRP1_EnableClockLowPower(LL_APB2_GRP1_PERIPH_UART9);
}

/**
  * @details This function enables the USART10 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_USART10_EnableClockInSleepMode(void)
{
  LL_APB2_GRP1_EnableClockLowPower(LL_APB2_GRP1_PERIPH_USART10);
}

/**
  * @details This function enables the USART10 clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_USART10_EnableClockInStopMode(void)
{
  LL_APB2_GRP1_EnableClockLowPower(LL_APB2_GRP1_PERIPH_USART10);
}

/**
  * @details This function enables the SPI1 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_SPI1_EnableClockInSleepMode(void)
{
  LL_APB2_GRP1_EnableClockLowPower(LL_APB2_GRP1_PERIPH_SPI1);
}

/**
  * @details This function enables the SPI1 clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_SPI1_EnableClockInStopMode(void)
{
  LL_APB2_GRP1_EnableClockLowPower(LL_APB2_GRP1_PERIPH_SPI1);
}

/**
  * @details This function enables the SPI4 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_SPI4_EnableClockInSleepMode(void)
{
  LL_APB2_GRP1_EnableClockLowPower(LL_APB2_GRP1_PERIPH_SPI4);
}

/**
  * @details This function enables the SPI4 clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_SPI4_EnableClockInStopMode(void)
{
  LL_APB2_GRP1_EnableClockLowPower(LL_APB2_GRP1_PERIPH_SPI4);
}

/**
  * @details This function enables the TIM15 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_TIM15_EnableClockInSleepMode(void)
{
  LL_APB2_GRP1_EnableClockLowPower(LL_APB2_GRP1_PERIPH_TIM15);
}

/**
  * @details This function enables the TIM15 clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_TIM15_EnableClockInStopMode(void)
{
  LL_APB2_GRP1_EnableClockLowPower(LL_APB2_GRP1_PERIPH_TIM15);
}

/**
  * @details This function enables the TIM16 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_TIM16_EnableClockInSleepMode(void)
{
  LL_APB2_GRP1_EnableClockLowPower(LL_APB2_GRP1_PERIPH_TIM16);
}

/**
  * @details This function enables the TIM16 clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_TIM16_EnableClockInStopMode(void)
{
  LL_APB2_GRP1_EnableClockLowPower(LL_APB2_GRP1_PERIPH_TIM16);
}

/**
  * @details This function enables the TIM17 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_TIM17_EnableClockInSleepMode(void)
{
  LL_APB2_GRP1_EnableClockLowPower(LL_APB2_GRP1_PERIPH_TIM17);
}

/**
  * @details This function enables the TIM17 clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_TIM17_EnableClockInStopMode(void)
{
  LL_APB2_GRP1_EnableClockLowPower(LL_APB2_GRP1_PERIPH_TIM17);
}

/**
  * @details This function enables the TIM9 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_TIM9_EnableClockInSleepMode(void)
{
  LL_APB2_GRP1_EnableClockLowPower(LL_APB2_GRP1_PERIPH_TIM9);
}

/**
  * @details This function enables the TIM9 clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_TIM9_EnableClockInStopMode(void)
{
  LL_APB2_GRP1_EnableClockLowPower(LL_APB2_GRP1_PERIPH_TIM9);
}

/**
  * @details This function enables the SPI5 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_SPI5_EnableClockInSleepMode(void)
{
  LL_APB2_GRP1_EnableClockLowPower(LL_APB2_GRP1_PERIPH_SPI5);
}

/**
  * @details This function enables the SPI5 clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_SPI5_EnableClockInStopMode(void)
{
  LL_APB2_GRP1_EnableClockLowPower(LL_APB2_GRP1_PERIPH_SPI5);
}

/**
  * @details This function enables the HRTIM1 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_HRTIM1_EnableClockInSleepMode(void)
{
  LL_APB2_GRP1_EnableClockLowPower(LL_APB2_GRP1_PERIPH_HRTIM1);
}

/**
  * @details This function enables the HRTIM1 clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_HRTIM1_EnableClockInStopMode(void)
{
  LL_APB2_GRP1_EnableClockLowPower(LL_APB2_GRP1_PERIPH_HRTIM1);
}

/**
  * @details This function enables the HRTIM2 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_HRTIM2_EnableClockInSleepMode(void)
{
  LL_APB2_GRP1_EnableClockLowPower(LL_APB2_GRP1_PERIPH_HRTIM2);
}

/**
  * @details This function enables the HRTIM2 clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_HRTIM2_EnableClockInStopMode(void)
{
  LL_APB2_GRP1_EnableClockLowPower(LL_APB2_GRP1_PERIPH_HRTIM2);
}

/**
  * @details This function disables the TIM1 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_TIM1_DisableClockInSleepMode(void)
{
  LL_APB2_GRP1_DisableClockLowPower(LL_APB2_GRP1_PERIPH_TIM1);
}

/**
  * @details This function disables the TIM1 clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_TIM1_DisableClockInStopMode(void)
{
  LL_APB2_GRP1_DisableClockLowPower(LL_APB2_GRP1_PERIPH_TIM1);
}

/**
  * @details This function disables the TIM8 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_TIM8_DisableClockInSleepMode(void)
{
  LL_APB2_GRP1_DisableClockLowPower(LL_APB2_GRP1_PERIPH_TIM8);
}

/**
  * @details This function disables the TIM8 clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_TIM8_DisableClockInStopMode(void)
{
  LL_APB2_GRP1_DisableClockLowPower(LL_APB2_GRP1_PERIPH_TIM8);
}

/**
  * @details This function disables the TIM20 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_TIM20_DisableClockInSleepMode(void)
{
  LL_APB2_GRP1_DisableClockLowPower(LL_APB2_GRP1_PERIPH_TIM20);
}

/**
  * @details This function disables the TIM20 clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_TIM20_DisableClockInStopMode(void)
{
  LL_APB2_GRP1_DisableClockLowPower(LL_APB2_GRP1_PERIPH_TIM20);
}

/**
  * @details This function disables the USART1 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_USART1_DisableClockInSleepMode(void)
{
  LL_APB2_GRP1_DisableClockLowPower(LL_APB2_GRP1_PERIPH_USART1);
}

/**
  * @details This function disables the USART1 clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_USART1_DisableClockInStopMode(void)
{
  LL_APB2_GRP1_DisableClockLowPower(LL_APB2_GRP1_PERIPH_USART1);
}

/**
  * @details This function disables the USART6 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_USART6_DisableClockInSleepMode(void)
{
  LL_APB2_GRP1_DisableClockLowPower(LL_APB2_GRP1_PERIPH_USART6);
}

/**
  * @details This function disables the USART6 clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_USART6_DisableClockInStopMode(void)
{
  LL_APB2_GRP1_DisableClockLowPower(LL_APB2_GRP1_PERIPH_USART6);
}

/**
  * @details This function disables the UART9 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_UART9_DisableClockInSleepMode(void)
{
  LL_APB2_GRP1_DisableClockLowPower(LL_APB2_GRP1_PERIPH_UART9);
}

/**
  * @details This function disables the UART9 clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_UART9_DisableClockInStopMode(void)
{
  LL_APB2_GRP1_DisableClockLowPower(LL_APB2_GRP1_PERIPH_UART9);
}

/**
  * @details This function disables the USART10 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_USART10_DisableClockInSleepMode(void)
{
  LL_APB2_GRP1_DisableClockLowPower(LL_APB2_GRP1_PERIPH_USART10);
}

/**
  * @details This function disables the USART10 clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_USART10_DisableClockInStopMode(void)
{
  LL_APB2_GRP1_DisableClockLowPower(LL_APB2_GRP1_PERIPH_USART10);
}

/**
  * @details This function disables the SPI1 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_SPI1_DisableClockInSleepMode(void)
{
  LL_APB2_GRP1_DisableClockLowPower(LL_APB2_GRP1_PERIPH_SPI1);
}

/**
  * @details This function disables the SPI1 clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_SPI1_DisableClockInStopMode(void)
{
  LL_APB2_GRP1_DisableClockLowPower(LL_APB2_GRP1_PERIPH_SPI1);
}

/**
  * @details This function disables the SPI4 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_SPI4_DisableClockInSleepMode(void)
{
  LL_APB2_GRP1_DisableClockLowPower(LL_APB2_GRP1_PERIPH_SPI4);
}

/**
  * @details This function disables the SPI4 clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_SPI4_DisableClockInStopMode(void)
{
  LL_APB2_GRP1_DisableClockLowPower(LL_APB2_GRP1_PERIPH_SPI4);
}

/**
  * @details This function disables the TIM15 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_TIM15_DisableClockInSleepMode(void)
{
  LL_APB2_GRP1_DisableClockLowPower(LL_APB2_GRP1_PERIPH_TIM15);
}

/**
  * @details This function disables the TIM15 clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_TIM15_DisableClockInStopMode(void)
{
  LL_APB2_GRP1_DisableClockLowPower(LL_APB2_GRP1_PERIPH_TIM15);
}

/**
  * @details This function disables the TIM16 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_TIM16_DisableClockInSleepMode(void)
{
  LL_APB2_GRP1_DisableClockLowPower(LL_APB2_GRP1_PERIPH_TIM16);
}

/**
  * @details This function disables the TIM16 clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_TIM16_DisableClockInStopMode(void)
{
  LL_APB2_GRP1_DisableClockLowPower(LL_APB2_GRP1_PERIPH_TIM16);
}

/**
  * @details This function disables the TIM17 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_TIM17_DisableClockInSleepMode(void)
{
  LL_APB2_GRP1_DisableClockLowPower(LL_APB2_GRP1_PERIPH_TIM17);
}

/**
  * @details This function disables the TIM17 clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_TIM17_DisableClockInStopMode(void)
{
  LL_APB2_GRP1_DisableClockLowPower(LL_APB2_GRP1_PERIPH_TIM17);
}

/**
  * @details This function disables the TIM9 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_TIM9_DisableClockInSleepMode(void)
{
  LL_APB2_GRP1_DisableClockLowPower(LL_APB2_GRP1_PERIPH_TIM9);
}

/**
  * @details This function disables the TIM9 clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_TIM9_DisableClockInStopMode(void)
{
  LL_APB2_GRP1_DisableClockLowPower(LL_APB2_GRP1_PERIPH_TIM9);
}

/**
  * @details This function disables the SPI5 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_SPI5_DisableClockInSleepMode(void)
{
  LL_APB2_GRP1_DisableClockLowPower(LL_APB2_GRP1_PERIPH_SPI5);
}

/**
  * @details This function disables the SPI5 clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_SPI5_DisableClockInStopMode(void)
{
  LL_APB2_GRP1_DisableClockLowPower(LL_APB2_GRP1_PERIPH_SPI5);
}

/**
  * @details This function disables the HRTIM1 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_HRTIM1_DisableClockInSleepMode(void)
{
  LL_APB2_GRP1_DisableClockLowPower(LL_APB2_GRP1_PERIPH_HRTIM1);
}

/**
  * @details This function disables the HRTIM1 clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_HRTIM1_DisableClockInStopMode(void)
{
  LL_APB2_GRP1_DisableClockLowPower(LL_APB2_GRP1_PERIPH_HRTIM1);
}

/**
  * @details This function disables the HRTIM2 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_HRTIM2_DisableClockInSleepMode(void)
{
  LL_APB2_GRP1_DisableClockLowPower(LL_APB2_GRP1_PERIPH_HRTIM2);
}

/**
  * @details This function disables the HRTIM2 clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_HRTIM2_DisableClockInStopMode(void)
{
  LL_APB2_GRP1_DisableClockLowPower(LL_APB2_GRP1_PERIPH_HRTIM2);
}

/**
  * @}
  */ /* RCC_APB2_Peripheral_Clock_Sleep_Enable_Disable */

/** @defgroup RCC_APB4_Peripheral_Clock_Sleep_Enable_Disable APB4 Peripheral Clock Sleep Enable Disable
  * @brief  Enable or disable the APB4 peripheral clock during Low Power (Sleep and Stop) mode.
  * @note   Peripheral clock gating in SLEEP and STOP modes can be used to further reduce power consumption.
  * @note   After wakeup from SLEEP or STOP modes, the peripheral clock is enabled again.
  * @note   By default, all peripheral clocks are enabled during SLEEP mode. In STOP mode peripheral clock
  *         is enabled only when a peripheral requests AHB clock.
  * @{
  */

/**
  * @details This function enables the SBS clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_SBS_EnableClockInSleepMode(void)
{
  LL_APB4_GRP1_EnableClockLowPower(LL_APB4_GRP1_PERIPH_SBS);
}

/**
  * @details This function enables the SBS clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_SBS_EnableClockInStopMode(void)
{
  LL_APB4_GRP1_EnableClockLowPower(LL_APB4_GRP1_PERIPH_SBS);
}

/**
  * @details This function enables the LPUART1 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LPUART1_EnableClockInSleepMode(void)
{
  LL_APB4_GRP1_EnableClockLowPower(LL_APB4_GRP1_PERIPH_LPUART1);
}

/**
  * @details This function enables the LPUART1 clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_LPUART1_EnableClockInStopMode(void)
{
  LL_APB4_GRP1_EnableClockLowPower(LL_APB4_GRP1_PERIPH_LPUART1);
}

/**
  * @details This function enables the SPI6 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_SPI6_EnableClockInSleepMode(void)
{
  LL_APB4_GRP1_EnableClockLowPower(LL_APB4_GRP1_PERIPH_SPI6);
}

/**
  * @details This function enables the SPI6 clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_SPI6_EnableClockInStopMode(void)
{
  LL_APB4_GRP1_EnableClockLowPower(LL_APB4_GRP1_PERIPH_SPI6);
}

/**
  * @details This function enables the LPTIM2 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LPTIM2_EnableClockInSleepMode(void)
{
  LL_APB4_GRP1_EnableClockLowPower(LL_APB4_GRP1_PERIPH_LPTIM2);
}

/**
  * @details This function enables the LPTIM2 clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_LPTIM2_EnableClockInStopMode(void)
{
  LL_APB4_GRP1_EnableClockLowPower(LL_APB4_GRP1_PERIPH_LPTIM2);
}

/**
  * @details This function enables the LPTIM3 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LPTIM3_EnableClockInSleepMode(void)
{
  LL_APB4_GRP1_EnableClockLowPower(LL_APB4_GRP1_PERIPH_LPTIM3);
}

/**
  * @details This function enables the LPTIM3 clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_LPTIM3_EnableClockInStopMode(void)
{
  LL_APB4_GRP1_EnableClockLowPower(LL_APB4_GRP1_PERIPH_LPTIM3);
}

/**
  * @details This function enables the LPTIM4 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LPTIM4_EnableClockInSleepMode(void)
{
  LL_APB4_GRP1_EnableClockLowPower(LL_APB4_GRP1_PERIPH_LPTIM4);
}

/**
  * @details This function enables the LPTIM4 clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_LPTIM4_EnableClockInStopMode(void)
{
  LL_APB4_GRP1_EnableClockLowPower(LL_APB4_GRP1_PERIPH_LPTIM4);
}

/**
  * @details This function enables the LPTIM5 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LPTIM5_EnableClockInSleepMode(void)
{
  LL_APB4_GRP1_EnableClockLowPower(LL_APB4_GRP1_PERIPH_LPTIM5);
}

/**
  * @details This function enables the LPTIM5 clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_LPTIM5_EnableClockInStopMode(void)
{
  LL_APB4_GRP1_EnableClockLowPower(LL_APB4_GRP1_PERIPH_LPTIM5);
}

/**
  * @details This function enables the VREF clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_VREF_EnableClockInSleepMode(void)
{
  LL_APB4_GRP1_EnableClockLowPower(LL_APB4_GRP1_PERIPH_VREF);
}

/**
  * @details This function enables the VREF clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_VREF_EnableClockInStopMode(void)
{
  LL_APB4_GRP1_EnableClockLowPower(LL_APB4_GRP1_PERIPH_VREF);
}

/**
  * @details This function enables the RTCAPB clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_RTCAPB_EnableClockInSleepMode(void)
{
  LL_APB4_GRP1_EnableClockLowPower(LL_APB4_GRP1_PERIPH_RTCAPB);
}

/**
  * @details This function enables the RTCAPB clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_RTCAPB_EnableClockInStopMode(void)
{
  LL_APB4_GRP1_EnableClockLowPower(LL_APB4_GRP1_PERIPH_RTCAPB);
}

/**
  * @details This function enables the DTS clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_DTS_EnableClockInSleepMode(void)
{
  LL_APB4_GRP1_EnableClockLowPower(LL_APB4_GRP1_PERIPH_DTS);
}

/**
  * @details This function enables the DTS clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_DTS_EnableClockInStopMode(void)
{
  LL_APB4_GRP1_EnableClockLowPower(LL_APB4_GRP1_PERIPH_DTS);
}

/**
  * @details This function enables the COMP12 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_COMP12_EnableClockInSleepMode(void)
{
  LL_APB4_GRP1_EnableClockLowPower(LL_APB4_GRP1_PERIPH_COMP12);
}

/**
  * @details This function enables the COMP12 clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_COMP12_EnableClockInStopMode(void)
{
  LL_APB4_GRP1_EnableClockLowPower(LL_APB4_GRP1_PERIPH_COMP12);
}

/**
  * @details This function enables the COMP34 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_COMP34_EnableClockInSleepMode(void)
{
  LL_APB4_GRP1_EnableClockLowPower(LL_APB4_GRP1_PERIPH_COMP34);
}

/**
  * @details This function enables the COMP34 clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_COMP34_EnableClockInStopMode(void)
{
  LL_APB4_GRP1_EnableClockLowPower(LL_APB4_GRP1_PERIPH_COMP34);
}

/**
  * @details This function enables the COMP56 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_COMP56_EnableClockInSleepMode(void)
{
  LL_APB4_GRP1_EnableClockLowPower(LL_APB4_GRP1_PERIPH_COMP56);
}

/**
  * @details This function enables the COMP56 clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_COMP56_EnableClockInStopMode(void)
{
  LL_APB4_GRP1_EnableClockLowPower(LL_APB4_GRP1_PERIPH_COMP56);
}

/**
  * @details This function enables the COMP78 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_COMP78_EnableClockInSleepMode(void)
{
  LL_APB4_GRP1_EnableClockLowPower(LL_APB4_GRP1_PERIPH_COMP78);
}

/**
  * @details This function enables the COMP78 clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_COMP78_EnableClockInStopMode(void)
{
  LL_APB4_GRP1_EnableClockLowPower(LL_APB4_GRP1_PERIPH_COMP78);
}

/**
  * @details This function disables the SBS clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_SBS_DisableClockInSleepMode(void)
{
  LL_APB4_GRP1_DisableClockLowPower(LL_APB4_GRP1_PERIPH_SBS);
}

/**
  * @details This function disables the SBS clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_SBS_DisableClockInStopMode(void)
{
  LL_APB4_GRP1_DisableClockLowPower(LL_APB4_GRP1_PERIPH_SBS);
}

/**
  * @details This function disables the LPUART1 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LPUART1_DisableClockInSleepMode(void)
{
  LL_APB4_GRP1_DisableClockLowPower(LL_APB4_GRP1_PERIPH_LPUART1);
}

/**
  * @details This function disables the LPUART1 clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_LPUART1_DisableClockInStopMode(void)
{
  LL_APB4_GRP1_DisableClockLowPower(LL_APB4_GRP1_PERIPH_LPUART1);
}

/**
  * @details This function disables the SPI6 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_SPI6_DisableClockInSleepMode(void)
{
  LL_APB4_GRP1_DisableClockLowPower(LL_APB4_GRP1_PERIPH_SPI6);
}

/**
  * @details This function disables the SPI6 clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_SPI6_DisableClockInStopMode(void)
{
  LL_APB4_GRP1_DisableClockLowPower(LL_APB4_GRP1_PERIPH_SPI6);
}

/**
  * @details This function disables the LPTIM2 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LPTIM2_DisableClockInSleepMode(void)
{
  LL_APB4_GRP1_DisableClockLowPower(LL_APB4_GRP1_PERIPH_LPTIM2);
}

/**
  * @details This function disables the LPTIM2 clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_LPTIM2_DisableClockInStopMode(void)
{
  LL_APB4_GRP1_DisableClockLowPower(LL_APB4_GRP1_PERIPH_LPTIM2);
}

/**
  * @details This function disables the LPTIM3 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LPTIM3_DisableClockInSleepMode(void)
{
  LL_APB4_GRP1_DisableClockLowPower(LL_APB4_GRP1_PERIPH_LPTIM3);
}

/**
  * @details This function disables the LPTIM3 clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_LPTIM3_DisableClockInStopMode(void)
{
  LL_APB4_GRP1_DisableClockLowPower(LL_APB4_GRP1_PERIPH_LPTIM3);
}

/**
  * @details This function disables the LPTIM4 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LPTIM4_DisableClockInSleepMode(void)
{
  LL_APB4_GRP1_DisableClockLowPower(LL_APB4_GRP1_PERIPH_LPTIM4);
}

/**
  * @details This function disables the LPTIM4 clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_LPTIM4_DisableClockInStopMode(void)
{
  LL_APB4_GRP1_DisableClockLowPower(LL_APB4_GRP1_PERIPH_LPTIM4);
}

/**
  * @details This function disables the LPTIM5 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_LPTIM5_DisableClockInSleepMode(void)
{
  LL_APB4_GRP1_DisableClockLowPower(LL_APB4_GRP1_PERIPH_LPTIM5);
}

/**
  * @details This function disables the LPTIM5 clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_LPTIM5_DisableClockInStopMode(void)
{
  LL_APB4_GRP1_DisableClockLowPower(LL_APB4_GRP1_PERIPH_LPTIM5);
}

/**
  * @details This function disables the VREF clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_VREF_DisableClockInSleepMode(void)
{
  LL_APB4_GRP1_DisableClockLowPower(LL_APB4_GRP1_PERIPH_VREF);
}

/**
  * @details This function disables the VREF clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_VREF_DisableClockInStopMode(void)
{
  LL_APB4_GRP1_DisableClockLowPower(LL_APB4_GRP1_PERIPH_VREF);
}

/**
  * @details This function disables the RTCAPB clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_RTCAPB_DisableClockInSleepMode(void)
{
  LL_APB4_GRP1_DisableClockLowPower(LL_APB4_GRP1_PERIPH_RTCAPB);
}

/**
  * @details This function disables the RTCAPB clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_RTCAPB_DisableClockInStopMode(void)
{
  LL_APB4_GRP1_DisableClockLowPower(LL_APB4_GRP1_PERIPH_RTCAPB);
}

/**
  * @details This function disables the DTS clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_DTS_DisableClockInSleepMode(void)
{
  LL_APB4_GRP1_DisableClockLowPower(LL_APB4_GRP1_PERIPH_DTS);
}

/**
  * @details This function disables the DTS clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_DTS_DisableClockInStopMode(void)
{
  LL_APB4_GRP1_DisableClockLowPower(LL_APB4_GRP1_PERIPH_DTS);
}

/**
  * @details This function disables the COMP12 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_COMP12_DisableClockInSleepMode(void)
{
  LL_APB4_GRP1_DisableClockLowPower(LL_APB4_GRP1_PERIPH_COMP12);
}

/**
  * @details This function disables the COMP12 clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_COMP12_DisableClockInStopMode(void)
{
  LL_APB4_GRP1_DisableClockLowPower(LL_APB4_GRP1_PERIPH_COMP12);
}

/**
  * @details This function disables the COMP34 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_COMP34_DisableClockInSleepMode(void)
{
  LL_APB4_GRP1_DisableClockLowPower(LL_APB4_GRP1_PERIPH_COMP34);
}

/**
  * @details This function disables the COMP34 clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_COMP34_DisableClockInStopMode(void)
{
  LL_APB4_GRP1_DisableClockLowPower(LL_APB4_GRP1_PERIPH_COMP34);
}

/**
  * @details This function disables the COMP56 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_COMP56_DisableClockInSleepMode(void)
{
  LL_APB4_GRP1_DisableClockLowPower(LL_APB4_GRP1_PERIPH_COMP56);
}

/**
  * @details This function disables the COMP56 clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_COMP56_DisableClockInStopMode(void)
{
  LL_APB4_GRP1_DisableClockLowPower(LL_APB4_GRP1_PERIPH_COMP56);
}

/**
  * @details This function disables the COMP78 clock in sleep mode.
  */
__STATIC_INLINE void HAL_RCC_COMP78_DisableClockInSleepMode(void)
{
  LL_APB4_GRP1_DisableClockLowPower(LL_APB4_GRP1_PERIPH_COMP78);
}

/**
  * @details This function disables the COMP78 clock in stop mode.
  */
__STATIC_INLINE void HAL_RCC_COMP78_DisableClockInStopMode(void)
{
  LL_APB4_GRP1_DisableClockLowPower(LL_APB4_GRP1_PERIPH_COMP78);
}

/**
  * @}
  */ /* RCC_APB4_Peripheral_Clock_Sleep_Enable_Disable */

/** @defgroup RCC_CKG_Peripheral_Clock_Sleep_Enable_Disable CKG Peripheral Clock Sleep Enable Disable
  * @brief  Enable or disable the CKG peripheral clock during Low Power (Sleep and Stop) mode.
  * @note   Peripheral clock gating in SLEEP and STOP modes can be used to further reduce power consumption.
  * @note   After wakeup from SLEEP or STOP modes, the peripheral clock is enabled again.
  * @note   By default, all peripheral clocks are enabled during SLEEP mode. In STOP mode peripheral clock
  *         is enabled only when a peripheral requests AHB clock.
  * @{
  */

/**
  * @}
  */ /* RCC_CKG_Peripheral_Clock_Sleep_Enable_Disable */

/** @defgroup RCC_AXI_Clock_Gating_Enable_Disable AXI Clocks gating Enable Disable
  * @brief    Enable or disable the clock gating.
  * @note     The dynamic power consumption can be optimized by enabling the functional clock gating.
  *           After reset, the clock gating is enabled (except for JTAG if a JTAG connection has been detected).
  * @{
  */

/**
  * @details This function enables the AXI clock gating.
  */
__STATIC_INLINE void HAL_RCC_AXI_EnableClockGating(void)
{
  LL_CKG_Enable(LL_CKG_PERIPH_AXI);
}

/**
  * @details This function disables the AXI clock gating.
  */
__STATIC_INLINE void HAL_RCC_AXI_DisableClockGating(void)
{
  LL_CKG_Disable(LL_CKG_PERIPH_AXI);
}

/**
  * @details This function enables the AHBM clock gating.
  */
__STATIC_INLINE void HAL_RCC_AHBM_EnableClockGating(void)
{
  LL_CKG_Enable(LL_CKG_PERIPH_AHBM);
}

/**
  * @details This function disables the AHBM clock gating.
  */
__STATIC_INLINE void HAL_RCC_AHBM_DisableClockGating(void)
{
  LL_CKG_Disable(LL_CKG_PERIPH_AHBM);
}

/**
  * @details This function enables the SDMMC1 clock gating.
  */
__STATIC_INLINE void HAL_RCC_SDMMC1_EnableClockGating(void)
{
  LL_CKG_Enable(LL_CKG_PERIPH_SDMMC1);
}

/**
  * @details This function disables the SDMMC1 clock gating.
  */
__STATIC_INLINE void HAL_RCC_SDMMC1_DisableClockGating(void)
{
  LL_CKG_Disable(LL_CKG_PERIPH_SDMMC1);
}

/**
  * @details This function enables the HPDMA1 clock gating.
  */
__STATIC_INLINE void HAL_RCC_HPDMA1_EnableClockGating(void)
{
  LL_CKG_Enable(LL_CKG_PERIPH_HPDMA1);
}

/**
  * @details This function disables the HPDMA1 clock gating.
  */
__STATIC_INLINE void HAL_RCC_HPDMA1_DisableClockGating(void)
{
  LL_CKG_Disable(LL_CKG_PERIPH_HPDMA1);
}

/**
  * @details This function enables the CPU clock gating.
  */
__STATIC_INLINE void HAL_RCC_CPU_EnableClockGating(void)
{
  LL_CKG_Enable(LL_CKG_PERIPH_CPU);
}

/**
  * @details This function disables the CPU clock gating.
  */
__STATIC_INLINE void HAL_RCC_CPU_DisableClockGating(void)
{
  LL_CKG_Disable(LL_CKG_PERIPH_CPU);
}

/**
  * @details This function enables the AHBS clock gating.
  */
__STATIC_INLINE void HAL_RCC_AHBS_EnableClockGating(void)
{
  LL_CKG_Enable(LL_CKG_PERIPH_AHBS);
}

/**
  * @details This function disables the AHBS clock gating.
  */
__STATIC_INLINE void HAL_RCC_AHBS_DisableClockGating(void)
{
  LL_CKG_Disable(LL_CKG_PERIPH_AHBS);
}

/**
  * @details This function enables the AHBIC clock gating.
  */
__STATIC_INLINE void HAL_RCC_AHBIC_EnableClockGating(void)
{
  LL_CKG_Enable(LL_CKG_PERIPH_AHBIC);
}

/**
  * @details This function disables the AHBIC clock gating.
  */
__STATIC_INLINE void HAL_RCC_AHBIC_DisableClockGating(void)
{
  LL_CKG_Disable(LL_CKG_PERIPH_AHBIC);
}

/**
  * @details This function enables the FMC clock gating.
  */
__STATIC_INLINE void HAL_RCC_FMC_EnableClockGating(void)
{
  LL_CKG_Enable(LL_CKG_PERIPH_FMC);
}

/**
  * @details This function disables the FMC clock gating.
  */
__STATIC_INLINE void HAL_RCC_FMC_DisableClockGating(void)
{
  LL_CKG_Disable(LL_CKG_PERIPH_FMC);
}

/**
  * @details This function enables the XSPI1 clock gating.
  */
__STATIC_INLINE void HAL_RCC_XSPI1_EnableClockGating(void)
{
  LL_CKG_Enable(LL_CKG_PERIPH_XSPI1);
}

/**
  * @details This function disables the XSPI1 clock gating.
  */
__STATIC_INLINE void HAL_RCC_XSPI1_DisableClockGating(void)
{
  LL_CKG_Disable(LL_CKG_PERIPH_XSPI1);
}

/**
  * @details This function enables the AXISRAM4 clock gating.
  */
__STATIC_INLINE void HAL_RCC_AXISRAM4_EnableClockGating(void)
{
  LL_CKG_Enable(LL_CKG_PERIPH_AXISRAM4);
}

/**
  * @details This function disables the AXISRAM4 clock gating.
  */
__STATIC_INLINE void HAL_RCC_AXISRAM4_DisableClockGating(void)
{
  LL_CKG_Disable(LL_CKG_PERIPH_AXISRAM4);
}

/**
  * @details This function enables the AXISRAM3 clock gating.
  */
__STATIC_INLINE void HAL_RCC_AXISRAM3_EnableClockGating(void)
{
  LL_CKG_Enable(LL_CKG_PERIPH_AXISRAM3);
}

/**
  * @details This function disables the AXISRAM3 clock gating.
  */
__STATIC_INLINE void HAL_RCC_AXISRAM3_DisableClockGating(void)
{
  LL_CKG_Disable(LL_CKG_PERIPH_AXISRAM3);
}

/**
  * @details This function enables the AXISRAM2 clock gating.
  */
__STATIC_INLINE void HAL_RCC_AXISRAM2_EnableClockGating(void)
{
  LL_CKG_Enable(LL_CKG_PERIPH_AXISRAM2);
}

/**
  * @details This function disables the AXISRAM2 clock gating.
  */
__STATIC_INLINE void HAL_RCC_AXISRAM2_DisableClockGating(void)
{
  LL_CKG_Disable(LL_CKG_PERIPH_AXISRAM2);
}

/**
  * @details This function enables the AXISRAM1 clock gating.
  */
__STATIC_INLINE void HAL_RCC_AXISRAM1_EnableClockGating(void)
{
  LL_CKG_Enable(LL_CKG_PERIPH_AXISRAM1);
}

/**
  * @details This function disables the AXISRAM1 clock gating.
  */
__STATIC_INLINE void HAL_RCC_AXISRAM1_DisableClockGating(void)
{
  LL_CKG_Disable(LL_CKG_PERIPH_AXISRAM1);
}

/**
  * @details This function enables the FLASH clock gating.
  */
__STATIC_INLINE void HAL_RCC_FLASH_EnableClockGating(void)
{
  LL_CKG_Enable(LL_CKG_PERIPH_FLASH);
}

/**
  * @details This function disables the FLASH clock gating.
  */
__STATIC_INLINE void HAL_RCC_FLASH_DisableClockGating(void)
{
  LL_CKG_Disable(LL_CKG_PERIPH_FLASH);
}

/**
  * @details This function enables the EXTI clock gating.
  */
__STATIC_INLINE void HAL_RCC_EXTI_EnableClockGating(void)
{
  LL_CKG_Enable(LL_CKG_PERIPH_EXTI);
}

/**
  * @details This function disables the EXTI clock gating.
  */
__STATIC_INLINE void HAL_RCC_EXTI_DisableClockGating(void)
{
  LL_CKG_Disable(LL_CKG_PERIPH_EXTI);
}

/**
  * @details This function enables the JTAG clock gating.
  */
__STATIC_INLINE void HAL_RCC_JTAG_EnableClockGating(void)
{
  LL_CKG_Enable(LL_CKG_PERIPH_JTAG);
}

/**
  * @details This function disables the JTAG clock gating.
  */
__STATIC_INLINE void HAL_RCC_JTAG_DisableClockGating(void)
{
  LL_CKG_Disable(LL_CKG_PERIPH_JTAG);
}

/**
  * @}
  */ /* RCC_AXI_Clock_Gating_Enable_Disable */


/** @defgroup RCC_Backup_Domain_Reset RCC Backup Domain Reset
  * @{
  */

/** @brief    Function to force and release the Backup domain.
  * @details  When a Backup domain reset occurs, the following domains are impacted:
  *           - the RTC is stopped and all the RTC registers are set to their reset values
  *             (including the backup registers)
  *           - all TAMP registers can be read or written in both secure and non-secure modes.
  *             The secure boot code can change this security setup, making some registers secure
  *             or not as needed, using TAMP_SECCFGR register.
  *           - The SRAM2 and BKPSRAM are affected by this reset.
  *           - LSE crystal 32kHz oscillator
  *           - RCC_BDCR register
  */
__STATIC_INLINE void HAL_RCC_ResetBackupDomain(void)
{
  LL_RCC_ForceBackupDomainReset();
  LL_RCC_ReleaseBackupDomainReset();
}


/**
  * @}
  */ /* End of RCC_Backup_Domain_Reset */

/**
  * @}
  */ /* RCC_Exported_Functions_Group2 */

/** @defgroup RCC_Exported_Functions_Group3 RCC services functions
  This subsection provides a set of functions allowing to:

  - Configure the MCO.
    - MCO (Microcontroller Clock Output): used to output MSIS, MSIK, LSI, HSI16, HSI48, LSE, HSE,
    SYSCLK or main PLL clock (through a configurable prescaler) on a pin.

  - Get and clear reset flags

  - Enable the Clock Security System.
    - CSS (Clock Security System): once enabled, if a HSE clock failure occurs (HSE used directly or
    through PLL as System clock source), the System clock is automatically switched of the system clock to the XXX or
    the XX oscillator depending on the STOPWUCK configuration.
    The CSSI is linked to the Cortex-M33 NMI (non-maskable interrupt) exception vector.
    The NMI is executed indefinitely unless the CSSI pending bit is cleared. As a consequence, in the NMI ISR, the user
    must clear the CSSI by setting the CSSC bit.

  - Enable Clock security system on LSE.

  - Configure and get the oscillator clock source for wakeup from Stop and CSS backup clock.

  - Configure and get the oscillator Kernel clock source for wakeup from Stop.

  *
  * @{
  */

void HAL_RCC_SetConfigMCO(hal_rcc_mco_src_t mcox_src, hal_rcc_mco_prescaler_t mcox_prescaler);
uint32_t                     HAL_RCC_GetResetSource(void);
void                         HAL_RCC_ClearResetFlags(void);
void                         HAL_RCC_HSE_EnableCSS(void);
hal_status_t                 HAL_RCC_NMI_IRQHandler(void);
hal_status_t                 HAL_RCC_HSE_CSSCallback(void);
void                         HAL_RCC_SetClockAfterWakeFromStop(hal_rcc_stop_wakeup_clk_t wakeup_clk);
hal_rcc_stop_wakeup_clk_t    HAL_RCC_GetClockAfterWakeFromStop(void);
void                         HAL_RCC_SetKernelClkAfterWakeFromStop(hal_rcc_stop_wakeup_kerclk_t wakeup_clk);
hal_rcc_stop_wakeup_kerclk_t HAL_RCC_GetKernelClkAfterWakeFromStop(void);
#if defined(LSE_VALUE)
void                         HAL_RCC_LSE_EnableCSS(void);
void                         HAL_RCC_LSE_DisableCSS(void);
void                         HAL_RCC_LSECSS_IRQHandler(void);
void                         HAL_RCC_LSE_CSSCallback(void);
#endif /* LSE_VALUE */
hal_status_t                 HAL_RCC_RTC_EnableKernelClock(void);
hal_status_t                 HAL_RCC_RTC_DisableKernelClock(void);

/**
  * @}
  */ /* RCC_Exported_Functions_Group3 */

/** @defgroup RCC_Exported_Functions_Group4 Kernel clock source configuration for peripherals
  This subsection provides a set of functions:
  - to control Kernel clock source configuration for peripherals

  Only functions having a kernel clock are handled by these functions.

    The peripheral clock can be selected either using the function @ref HAL_RCC_PeriphClockConfig
    or through the independent API HAL_RCC_{PERIPHx}_SetKernelClkSource(hal_rcc_{periph}_clk_src_t clk_src)
    example: @ref HAL_RCC_USART1_SetKernelClkSource(hal_rcc_usart1_clk_src_t clk_src)

    Usage: activate SYSCLK as clock source of USART1

    - with @ref HAL_RCC_PeriphClockConfig function:
    @code
      hal_rcc_periph_clk_init_t exclk
      exclk.periph_clk_sel = HAL_RCC_PERIPHCLK_USART1;
      exclk.usart1_clk_sel = HAL_RCC_USART1_CLK_SRC_SYSCLK;
      HAL_RCC_PeriphClockConfig(&exclk);
    @endcode
    - with @ref HAL_RCC_USART1_SetKernelClkSource function:
    @code
      HAL_RCC_USART1_SetKernelClkSource(HAL_RCC_USART1_CLK_SRC_SYSCLK);
    @endcode

    - to get the peripheral Clocks frequencies:
      hal_rcc_{periph}_clk_src_t HAL_RCC_{PERIPHx}_GetKernelClkSource(void)

  @note Important note: Care must be taken when @ref HAL_RCC_PeriphClockConfig() is used to
      select the RTC clock source; in this case the Backup domain is reset in
      order to modify the RTC Clock source, as consequence RTC registers (including
      the backup registers) are set to their reset values.
  * @{
  */

hal_status_t HAL_RCC_FMC_SetKernelClkSource(hal_rcc_fmc_clk_src_t clk_src);
hal_status_t HAL_RCC_SDMMC1_SetKernelClkSource(hal_rcc_sdmmc1_clk_src_t clk_src);
hal_status_t HAL_RCC_XSPI1_SetKernelClkSource(hal_rcc_xspi1_clk_src_t clk_src);
hal_status_t HAL_RCC_OTGFS_SetKernelClkSource(hal_rcc_otgfs_clk_src_t clk_src);
hal_status_t HAL_RCC_ADF1_SetKernelClkSource(hal_rcc_adf1_clk_src_t clk_src);
hal_status_t HAL_RCC_ADC_SetKernelClkSource(hal_rcc_adc_clk_src_t clk_src);
hal_status_t HAL_RCC_CKPER_SetKernelClkSource(hal_rcc_ckper_clk_src_t clk_src);
hal_status_t HAL_RCC_UART234578_SetKernelClkSource(hal_rcc_uart234578_clk_src_t clk_src);
hal_status_t HAL_RCC_SPI1_SetKernelClkSource(hal_rcc_spi1_clk_src_t clk_src);
hal_status_t HAL_RCC_SPI6_SetKernelClkSource(hal_rcc_spi6_clk_src_t clk_src);
hal_status_t HAL_RCC_SPI23_SetKernelClkSource(hal_rcc_spi23_clk_src_t clk_src);
hal_status_t HAL_RCC_SPI45_SetKernelClkSource(hal_rcc_spi45_clk_src_t clk_src);
hal_status_t HAL_RCC_I2C123_SetKernelClkSource(hal_rcc_i2c123_clk_src_t clk_src);
hal_status_t HAL_RCC_I3C1_SetKernelClkSource(hal_rcc_i3c1_clk_src_t clk_src);
hal_status_t HAL_RCC_LPTIM1_SetKernelClkSource(hal_rcc_lptim1_clk_src_t clk_src);
hal_status_t HAL_RCC_LPTIM23_SetKernelClkSource(hal_rcc_lptim23_clk_src_t clk_src);
hal_status_t HAL_RCC_LPTIM45_SetKernelClkSource(hal_rcc_lptim45_clk_src_t clk_src);
hal_status_t HAL_RCC_FDCAN_SetKernelClkSource(hal_rcc_fdcan_clk_src_t clk_src);
hal_status_t HAL_RCC_USART16910_SetKernelClkSource(hal_rcc_usart16910_clk_src_t clk_src);
hal_status_t HAL_RCC_LPUART1_SetKernelClkSource(hal_rcc_lpuart1_clk_src_t clk_src);
hal_status_t HAL_RCC_DAC1_SetKernelClkSource(hal_rcc_dac1_clk_src_t clk_src);
hal_status_t HAL_RCC_DAC2_SetKernelClkSource(hal_rcc_dac2_clk_src_t clk_src);
hal_status_t HAL_RCC_DAC3_SetKernelClkSource(hal_rcc_dac3_clk_src_t clk_src);
hal_status_t HAL_RCC_DAC4_SetKernelClkSource(hal_rcc_dac4_clk_src_t clk_src);
hal_status_t HAL_RCC_DAC1SH_SetKernelClkSource(hal_rcc_dac1_sh_clk_src_t clk_src);
hal_status_t HAL_RCC_RTC_SetKernelClkSource(hal_rcc_rtc_clk_src_t clk_src);

hal_rcc_fmc_clk_src_t HAL_RCC_FMC_GetKernelClkSource(void);
hal_rcc_sdmmc1_clk_src_t HAL_RCC_SDMMC1_GetKernelClkSource(void);
hal_rcc_xspi1_clk_src_t HAL_RCC_XSPI1_GetKernelClkSource(void);
hal_rcc_otgfs_clk_src_t HAL_RCC_OTGFS_GetKernelClkSource(void);
hal_rcc_adf1_clk_src_t HAL_RCC_ADF1_GetKernelClkSource(void);
hal_rcc_adc_clk_src_t HAL_RCC_ADC_GetKernelClkSource(void);
hal_rcc_ckper_clk_src_t HAL_RCC_CKPER_GetKernelClkSource(void);
hal_rcc_uart234578_clk_src_t HAL_RCC_UART234578_GetKernelClkSource(void);
hal_rcc_spi1_clk_src_t HAL_RCC_SPI1_GetKernelClkSource(void);
hal_rcc_spi6_clk_src_t HAL_RCC_SPI6_GetKernelClkSource(void);
hal_rcc_spi23_clk_src_t HAL_RCC_SPI23_GetKernelClkSource(void);
hal_rcc_spi45_clk_src_t HAL_RCC_SPI45_GetKernelClkSource(void);
hal_rcc_i2c123_clk_src_t HAL_RCC_I2C123_GetKernelClkSource(void);
hal_rcc_i3c1_clk_src_t HAL_RCC_I3C1_GetKernelClkSource(void);
hal_rcc_lptim1_clk_src_t HAL_RCC_LPTIM1_GetKernelClkSource(void);
hal_rcc_lptim23_clk_src_t HAL_RCC_LPTIM23_GetKernelClkSource(void);
hal_rcc_lptim45_clk_src_t HAL_RCC_LPTIM45_GetKernelClkSource(void);
hal_rcc_fdcan_clk_src_t HAL_RCC_FDCAN_GetKernelClkSource(void);
hal_rcc_usart16910_clk_src_t HAL_RCC_USART16910_GetKernelClkSource(void);
hal_rcc_lpuart1_clk_src_t HAL_RCC_LPUART1_GetKernelClkSource(void);
hal_rcc_dac1_clk_src_t HAL_RCC_DAC1_GetKernelClkSource(void);
hal_rcc_dac2_clk_src_t HAL_RCC_DAC2_GetKernelClkSource(void);
hal_rcc_dac3_clk_src_t HAL_RCC_DAC3_GetKernelClkSource(void);
hal_rcc_dac4_clk_src_t HAL_RCC_DAC4_GetKernelClkSource(void);
hal_rcc_dac1_sh_clk_src_t HAL_RCC_DAC1SH_GetKernelClkSource(void);
hal_rcc_rtc_clk_src_t HAL_RCC_RTC_GetKernelClkSource(void);

uint32_t HAL_RCC_FMC_GetKernelClkFreq(void);
uint32_t HAL_RCC_SDMMC_GetKernelClkFreq(const SDMMC_TypeDef *sdmmcx);
uint32_t HAL_RCC_SDMMC1_GetKernelClkFreq(void);
uint32_t HAL_RCC_XSPI_GetKernelClkFreq(const XSPI_TypeDef *xspix);
uint32_t HAL_RCC_XSPI1_GetKernelClkFreq(void);
uint32_t HAL_RCC_OTGFS_GetKernelClkFreq(void);
uint32_t HAL_RCC_ADF1_GetKernelClkFreq(void);
uint32_t HAL_RCC_ADC_GetKernelClkFreq(void);
uint32_t HAL_RCC_CKPER_GetKernelClkFreq(void);
uint32_t HAL_RCC_UART_GetKernelClkFreq(const USART_TypeDef *uartx);
uint32_t HAL_RCC_USART_GetKernelClkFreq(const USART_TypeDef *usartx);
uint32_t HAL_RCC_UART234578_GetKernelClkFreq(void);
uint32_t HAL_RCC_USART16910_GetKernelClkFreq(void);
uint32_t HAL_RCC_LPUART1_GetKernelClkFreq(void);
uint32_t HAL_RCC_SPI_GetKernelClkFreq(const SPI_TypeDef *spix);
uint32_t HAL_RCC_SPI1_GetKernelClkFreq(void);
uint32_t HAL_RCC_SPI6_GetKernelClkFreq(void);
uint32_t HAL_RCC_SPI23_GetKernelClkFreq(void);
uint32_t HAL_RCC_SPI45_GetKernelClkFreq(void);
uint32_t HAL_RCC_I2C_GetKernelClkFreq(const I2C_TypeDef *i2cx);
uint32_t HAL_RCC_I2C123_GetKernelClkFreq(void);
uint32_t HAL_RCC_I3C_GetKernelClkFreq(const I3C_TypeDef *i3cx);
uint32_t HAL_RCC_I3C1_GetKernelClkFreq(void);
uint32_t HAL_RCC_HRTIM_GetKernelClkFreq(const HRTIM_TypeDef *hrtimx);
uint32_t HAL_RCC_HRTIM1_GetKernelClkFreq(void);
uint32_t HAL_RCC_HRTIM2_GetKernelClkFreq(void);
uint32_t HAL_RCC_TIM_GetKernelClkFreq(const TIM_TypeDef *timx);
uint32_t HAL_RCC_LPTIM_GetKernelClkFreq(const LPTIM_TypeDef *lptimx);
uint32_t HAL_RCC_LPTIM1_GetKernelClkFreq(void);
uint32_t HAL_RCC_LPTIM23_GetKernelClkFreq(void);
uint32_t HAL_RCC_LPTIM45_GetKernelClkFreq(void);
uint32_t HAL_RCC_FDCAN_GetKernelClkFreq(void);
uint32_t HAL_RCC_DAC_GetKernelClkFreq(const DAC_TypeDef *dacx);
uint32_t HAL_RCC_DAC1_GetKernelClkFreq(void);
uint32_t HAL_RCC_DAC2_GetKernelClkFreq(void);
uint32_t HAL_RCC_DAC3_GetKernelClkFreq(void);
uint32_t HAL_RCC_DAC4_GetKernelClkFreq(void);
uint32_t HAL_RCC_DAC_GetSampleHoldClkFreq(const DAC_TypeDef *dacshx);
uint32_t HAL_RCC_DAC1_GetSampleHoldClkFreq(void);
uint32_t HAL_RCC_COMP_GetKernelClkFreq(const COMP_TypeDef *compx);
uint32_t HAL_RCC_RTC_GetKernelClkFreq(void);

/**
  * @}
  */ /* RCC_Exported_Functions_Group4 */


/**
  * @}
  */ /* End of RCC_Exported_Functions */

/**
  * @}
  */ /* End of RCC */

/**
  * @}
  */ /* End of STM32H7PXX_HAL_Driver */


#ifdef __cplusplus
}
#endif

#endif /* STM32H7PXX_HAL_RCC_H */
