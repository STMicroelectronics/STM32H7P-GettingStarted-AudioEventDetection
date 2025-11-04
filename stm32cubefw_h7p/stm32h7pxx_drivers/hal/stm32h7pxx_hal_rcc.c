/**
  ******************************************************************************
  * @file    stm32h7pxx_hal_rcc.c
  * @author  GPM Application Team
  * @brief   RCC HAL module driver.
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
  */

/* Includes ------------------------------------------------------------------*/
#include "stm32_hal.h"

/** @addtogroup STM32H7PXX_HAL_Driver
  * @{
  */

/** @defgroup RCC RCC
  * @{
This file provides firmware functions to manage the following
functionalities of the Reset and Clock Control (RCC) peripheral:

- Configuration and reset functions
- Oscillators and Peripherals Control functions
- Bus configuration functions

Main APIs are not allowed to perform any other actions that their main objectif (for instance, it is not allowed to
disable a PLL or an oscillator inside an enable function).

For performance reasons, few functionalities are not supported by the HAL driver but these functionalities are covered
by the LL driver (for instance, interrupt management).

The driver is responsible of the update of SystemCoreClock variable (used by CMSIS) and System tick.

## RCC specific features

After exiting from standby or reset, the device is running from High Speed Internal (HSI) oscillator
(by default to 64MHz but ...).

- There is no prescaler on High speed (AHBs) and Low speed (APBs) busses:
all peripherals mapped on these busses are running at sysclk frequency.
- The clock for all peripherals is switched off, except the SRAM and FLASH.

Once the device started from reset, the user application could:

- Configure the clock source to be used to drive the System clock
(if the application needs higher frequency/performance)
- Configure the System clock frequency and Flash settings
- Configure the AHB and APB busses prescalers
- Enable the clock for the peripheral(s) to be used
- Configure the clock source(s) for peripherals which clocks receive an independent kernel clocks.
- Configure peripherals supporting the autonomous mode (These peripherals are able to generate a kernel clock
request and a AHB/APB bus clock request when they need, in order to operate and update their status register
even in Stop mode).

## Configuration inside the RCC driver

Config defines            | Description               | Default value | Note
------------------------- | ------------------------- | ------------- | ------------------------------------
PRODUCT                   | from IDE                  | Defined       | The selected product (ex STM32U585xx)
PERIPHERAL                | from CMSIS                | Defined       | Periph. available on the selected product
USE_ASSERT_DBG_PARAM      | from IDE                  | None          | When defined, enable the params assert
USE_HAL_CHECK_PARAM       | from hal_conf.h           | 0             | When set, parameters are checked in runtime
USE_HAL_RCC_MODULE        | from hal_conf.h           | 1             | When set, HAL RCC module is enabled
USE_EXTERNAL_ENV          | from IDE                  | Defined       | When set, ext. oscillators values are defined
LSE_VALUE                 | From stm32_external_env.h | 32 Khz        | Frequency of LSE oscillator (USE_EXTERNAL_ENV)
HSE_VALUE                 | From stm32_external_env.h | 32 Mhz        | Frequency of HSE oscillator (USE_EXTERNAL_ENV)
__ARM_FEATURE_CMSE        | Trust Zone                | NA            | Defined in secure context
HSI_VALUE                 | "stm32"h7pxxxxxx.h              | 64 MHz        | Frequency of HSI oscillator
  *
  */

#if defined(USE_HAL_RCC_MODULE) && (USE_HAL_RCC_MODULE == 1)

/* Private typedef -----------------------------------------------------------*/

/** @defgroup RCC_Private_Typedef RCC Private Type definition
  * @{
  */
typedef  uint32_t (*rcc_cb_timeout_t)(void); /*!< RCC internal Callback pointer definition */
/**
  * @}
  */ /* End of RCC_Private_Typedef */

/* Private constants ---------------------------------------------------------*/

/** @defgroup RCC_Private_Constants RCC Private Constants and enumerations
  * @{
  */

/**
  * @brief Timeout values
  * @{
  */
#if defined(HSE_VALUE)
#define RCC_HSE_TIMEOUT_VALUE   HSE_STARTUP_TIMEOUT                /*!< HSE Timeout value                         */
#endif /* HSE_VALUE */
#if defined(LSE_VALUE)
#define RCC_LSE_TIMEOUT_VALUE   LSE_STARTUP_TIMEOUT                /*!< LSE Timeout value                         */
#endif /* LSE_VALUE */
#define RCC_HSI_TIMEOUT_VALUE   2U                                 /*!< 2 ms (minimum Tick + 1) timeout for HSI   */
#define RCC_HSI48_TIMEOUT_VALUE 2U                                 /*!< 2 ms (minimum Tick + 1) timeout for HSI48 */
#define RCC_CSI_TIMEOUT_VALUE   2U                                 /*!< 2 ms (minimum Tick + 1) timeout for CSI   */
#define RCC_LSI_TIMEOUT_VALUE   ((10u * 128u * 1000u) / LSI_VALUE) /*!< 40 ms for LSI at 32KHz                    */

#define RCC_PLL1_TIMEOUT_VALUE  2UL                                /*!< 2 ms (minimum Tick + 1)                   */
#define RCC_PLL2_TIMEOUT_VALUE  2UL                                /*!< 2 ms (minimum Tick + 1)                   */
#define RCC_PLL3_TIMEOUT_VALUE  2UL                                /*!< 2 ms (minimum Tick + 1)                   */
#define RCC_PLL_FRAC_WAIT_VALUE 1U                                 /*!< PLL Fractional part waiting time before new latch enable : 1 ms */

#define RCC_CLOCKSWITCH_TIMEOUT_VALUE 5000UL                       /*!< 5 s                                       */

/**
  * @}
  */

/**
  * @brief PLL index to define PLL1, PLL2 or PLL3
  * @{
  */
typedef enum
{
  PLL_1 = 0U, /*!< ID on PLL1 */
  PLL_2 = 1U, /*!< ID on PLL2 */
  PLL_3 = 2U, /*!< ID on PLL3 */
} rcc_pll_id_t;
/**
  * @}
  */

/**
  * @brief PLL range limits
  * @{
  */
#define RCC_PLL_INPUTRANGE0_FREQMIN   1000000U  /* 1 MHz is minimum frequency for VCO input range 0 */
#define RCC_PLL_INPUTRANGE0_FREQMAX   2000000U  /* 2 MHz is maximum frequency for VCO input range 0 */
#define RCC_PLL_INPUTRANGE1_FREQMIN   2000000U  /* 2 MHz is minimum frequency for VCO input range 1 */
#define RCC_PLL_INPUTRANGE1_FREQMAX   4000000U  /* 4 MHz is maximum frequency for VCO input range 1 */
#define RCC_PLL_INPUTRANGE2_FREQMIN   4000000U  /* 4 MHz is minimum frequency for VCO input range 2 */
#define RCC_PLL_INPUTRANGE2_FREQMAX   8000000U  /* 8 MHz is maximum frequency for VCO input range 2 */
#define RCC_PLL_INPUTRANGE3_FREQMIN   8000000U  /* 8 MHz is maximum frequency for VCO input range 3 */
#define RCC_PLL_INPUTRANGE3_FREQMAX   16000000U  /* 16 MHz is maximum frequency for VCO input range 3 */

#define RCC_PLL_VCOL_FREQMIN   150000000U  /* 150 MHz is minimum frequency for VCO output range in low-range */
#define RCC_PLL_VCOL_FREQMAX   420000000U  /* 420 MHz is maximum frequency for VCO output range in low-range */
#define RCC_PLL_VCOH_FREQMIN   384000000U  /* 384 MHz is minimum frequency for VCO output range in wide-range */
#define RCC_PLL_VCOH_FREQMAX   1672000000U  /* 1672 MHz is maximum frequency for for VCO output range in wide-range */
/**
  * @}
  */

/**
  * @}
  */ /* End of RCC_Private_Constants */

/* Private macros ------------------------------------------------------------*/

/** @defgroup RCC_Private_Macros RCC Private Macros
  * @{
  */

/**
  * @brief Calculate the HSI frequency depending of HSI divider
  */
#define RCC_GET_HSI_FREQUENCY() (HSI_VALUE >> (LL_RCC_HSI_GetDivider() >> RCC_CR_HSIDIV_Pos))


#define IS_RCC_HSE_MODE_ENABLE(mode) (((mode) == HAL_RCC_HSE_ON)          \
                                      || ((mode) == HAL_RCC_HSE_BYPASS)   \
                                      || ((mode) == HAL_RCC_HSE_BYPASS_DIGITAL))

#define IS_RCC_LSE_MODE_ENABLE(mode) (((mode) == HAL_RCC_LSE_ON)          \
                                      || ((mode) == HAL_RCC_LSE_BYPASS)   \
                                      || ((mode) == HAL_RCC_LSE_BYPASS_DIGITAL))

#define IS_RCC_LSE_DRIVE(drive) (((drive) == HAL_RCC_LSE_DRIVE_LOW)           \
                                 || ((drive) == HAL_RCC_LSE_DRIVE_MEDIUMLOW)  \
                                 || ((drive) == HAL_RCC_LSE_DRIVE_MEDIUMHIGH) \
                                 || ((drive) == HAL_RCC_LSE_DRIVE_HIGH))

#define IS_RCC_HSI_DIV(hsi_div) (((hsi_div) == HAL_RCC_HSI_DIV_1)  \
                                 || ((hsi_div) == HAL_RCC_HSI_DIV_2)  \
                                 || ((hsi_div) == HAL_RCC_HSI_DIV_4)  \
                                 || ((hsi_div) == HAL_RCC_HSI_DIV_8))

#define IS_RCC_HSI_CALIBRATION_VALUE(value) ((value) <= (uint32_t)( RCC_HSICFGR_HSITRIM  >> RCC_HSICFGR_HSITRIM_Pos))

#define IS_RCC_CSI_CALIBRATION_VALUE(value) ((value) <= (uint32_t)( RCC_CSICFGR_CSITRIM  >> RCC_CSICFGR_CSITRIM_Pos))

#define IS_RCC_STOP_WAKEUPCLOCK(source) (((source) == HAL_RCC_STOP_WAKEUPCLOCK_HSI)  \
                                         || ((source) == HAL_RCC_STOP_WAKEUPCLOCK_CSI))

#define IS_RCC_STOP_KERWAKEUPCLOCK(source) (((source) == HAL_RCC_STOP_WAKEUPKERCLOCK_HSI)  \
                                            || ((source) == HAL_RCC_STOP_WAKEUPKERCLOCK_CSI))

#define IS_RCC_SYSCLKSOURCE(source) (((source) == HAL_RCC_SYSCLK_SRC_HSI)     \
                                     || ((source) == HAL_RCC_SYSCLK_SRC_CSI)  \
                                     || ((source) == HAL_RCC_SYSCLK_SRC_HSE)  \
                                     || ((source) == HAL_RCC_SYSCLK_SRC_PLLCLK))

#define IS_RCC_SYSCPUCLK(syscpuclk) (((syscpuclk) == HAL_RCC_SYSCPUCLK_PRESCALER1)      \
                                     || ((syscpuclk) == HAL_RCC_SYSCPUCLK_PRESCALER2)   \
                                     || ((syscpuclk) == HAL_RCC_SYSCPUCLK_PRESCALER4)   \
                                     || ((syscpuclk) == HAL_RCC_SYSCPUCLK_PRESCALER8)   \
                                     || ((syscpuclk) == HAL_RCC_SYSCPUCLK_PRESCALER16)  \
                                     || ((syscpuclk) == HAL_RCC_SYSCPUCLK_PRESCALER64)  \
                                     || ((syscpuclk) == HAL_RCC_SYSCPUCLK_PRESCALER128) \
                                     || ((syscpuclk) == HAL_RCC_SYSCPUCLK_PRESCALER256) \
                                     || ((syscpuclk) == HAL_RCC_SYSCPUCLK_PRESCALER512))

#define IS_RCC_HCLK(hclk) (((hclk) == HAL_RCC_HCLK_PRESCALER1) \
                           || ((hclk) == HAL_RCC_HCLK_PRESCALER2))

#define IS_RCC_PCLK(pclk) (((pclk) == HAL_RCC_PCLK_PRESCALER1)  \
                           || ((pclk) == HAL_RCC_PCLK_PRESCALER2)  \
                           || ((pclk) == HAL_RCC_PCLK_PRESCALER4)  \
                           || ((pclk) == HAL_RCC_PCLK_PRESCALER8)  \
                           || ((pclk) == HAL_RCC_PCLK_PRESCALER16))

#define IS_RCC_RTC_CLK(source) (((source) == HAL_RCC_RTC_CLK_SRC_NONE)    \
                                || ((source) == HAL_RCC_RTC_CLK_SRC_LSE)  \
                                || ((source) == HAL_RCC_RTC_CLK_SRC_LSI)  \
                                || ((source) == HAL_RCC_RTC_CLK_SRC_HSE_DIV2)  \
                                || ((source) == HAL_RCC_RTC_CLK_SRC_HSE_DIV3)  \
                                || ((source) == HAL_RCC_RTC_CLK_SRC_HSE_DIV4)  \
                                || ((source) == HAL_RCC_RTC_CLK_SRC_HSE_DIV5)  \
                                || ((source) == HAL_RCC_RTC_CLK_SRC_HSE_DIV6)  \
                                || ((source) == HAL_RCC_RTC_CLK_SRC_HSE_DIV7)  \
                                || ((source) == HAL_RCC_RTC_CLK_SRC_HSE_DIV8)  \
                                || ((source) == HAL_RCC_RTC_CLK_SRC_HSE_DIV9)  \
                                || ((source) == HAL_RCC_RTC_CLK_SRC_HSE_DIV10) \
                                || ((source) == HAL_RCC_RTC_CLK_SRC_HSE_DIV11) \
                                || ((source) == HAL_RCC_RTC_CLK_SRC_HSE_DIV12) \
                                || ((source) == HAL_RCC_RTC_CLK_SRC_HSE_DIV13) \
                                || ((source) == HAL_RCC_RTC_CLK_SRC_HSE_DIV14) \
                                || ((source) == HAL_RCC_RTC_CLK_SRC_HSE_DIV15) \
                                || ((source) == HAL_RCC_RTC_CLK_SRC_HSE_DIV16) \
                                || ((source) == HAL_RCC_RTC_CLK_SRC_HSE_DIV17) \
                                || ((source) == HAL_RCC_RTC_CLK_SRC_HSE_DIV18) \
                                || ((source) == HAL_RCC_RTC_CLK_SRC_HSE_DIV19) \
                                || ((source) == HAL_RCC_RTC_CLK_SRC_HSE_DIV20) \
                                || ((source) == HAL_RCC_RTC_CLK_SRC_HSE_DIV21) \
                                || ((source) == HAL_RCC_RTC_CLK_SRC_HSE_DIV22) \
                                || ((source) == HAL_RCC_RTC_CLK_SRC_HSE_DIV23) \
                                || ((source) == HAL_RCC_RTC_CLK_SRC_HSE_DIV24) \
                                || ((source) == HAL_RCC_RTC_CLK_SRC_HSE_DIV25) \
                                || ((source) == HAL_RCC_RTC_CLK_SRC_HSE_DIV26) \
                                || ((source) == HAL_RCC_RTC_CLK_SRC_HSE_DIV27) \
                                || ((source) == HAL_RCC_RTC_CLK_SRC_HSE_DIV28) \
                                || ((source) == HAL_RCC_RTC_CLK_SRC_HSE_DIV29) \
                                || ((source) == HAL_RCC_RTC_CLK_SRC_HSE_DIV30) \
                                || ((source) == HAL_RCC_RTC_CLK_SRC_HSE_DIV31) \
                                || ((source) == HAL_RCC_RTC_CLK_SRC_HSE_DIV32) \
                                || ((source) == HAL_RCC_RTC_CLK_SRC_HSE_DIV33) \
                                || ((source) == HAL_RCC_RTC_CLK_SRC_HSE_DIV34) \
                                || ((source) == HAL_RCC_RTC_CLK_SRC_HSE_DIV35) \
                                || ((source) == HAL_RCC_RTC_CLK_SRC_HSE_DIV36) \
                                || ((source) == HAL_RCC_RTC_CLK_SRC_HSE_DIV37) \
                                || ((source) == HAL_RCC_RTC_CLK_SRC_HSE_DIV38) \
                                || ((source) == HAL_RCC_RTC_CLK_SRC_HSE_DIV39) \
                                || ((source) == HAL_RCC_RTC_CLK_SRC_HSE_DIV40) \
                                || ((source) == HAL_RCC_RTC_CLK_SRC_HSE_DIV41) \
                                || ((source) == HAL_RCC_RTC_CLK_SRC_HSE_DIV42) \
                                || ((source) == HAL_RCC_RTC_CLK_SRC_HSE_DIV43) \
                                || ((source) == HAL_RCC_RTC_CLK_SRC_HSE_DIV44) \
                                || ((source) == HAL_RCC_RTC_CLK_SRC_HSE_DIV45) \
                                || ((source) == HAL_RCC_RTC_CLK_SRC_HSE_DIV46) \
                                || ((source) == HAL_RCC_RTC_CLK_SRC_HSE_DIV47) \
                                || ((source) == HAL_RCC_RTC_CLK_SRC_HSE_DIV48) \
                                || ((source) == HAL_RCC_RTC_CLK_SRC_HSE_DIV49) \
                                || ((source) == HAL_RCC_RTC_CLK_SRC_HSE_DIV50) \
                                || ((source) == HAL_RCC_RTC_CLK_SRC_HSE_DIV51) \
                                || ((source) == HAL_RCC_RTC_CLK_SRC_HSE_DIV52) \
                                || ((source) == HAL_RCC_RTC_CLK_SRC_HSE_DIV53) \
                                || ((source) == HAL_RCC_RTC_CLK_SRC_HSE_DIV54) \
                                || ((source) == HAL_RCC_RTC_CLK_SRC_HSE_DIV55) \
                                || ((source) == HAL_RCC_RTC_CLK_SRC_HSE_DIV56) \
                                || ((source) == HAL_RCC_RTC_CLK_SRC_HSE_DIV57) \
                                || ((source) == HAL_RCC_RTC_CLK_SRC_HSE_DIV58) \
                                || ((source) == HAL_RCC_RTC_CLK_SRC_HSE_DIV59) \
                                || ((source) == HAL_RCC_RTC_CLK_SRC_HSE_DIV60) \
                                || ((source) == HAL_RCC_RTC_CLK_SRC_HSE_DIV61) \
                                || ((source) == HAL_RCC_RTC_CLK_SRC_HSE_DIV62) \
                                || ((source) == HAL_RCC_RTC_CLK_SRC_HSE_DIV63))

#define IS_RCC_MCOSOURCE(source) (((source) == HAL_RCC_MCO1_SRC_HSI)    \
                                  || ((source) == HAL_RCC_MCO1_SRC_LSE)    \
                                  || ((source) == HAL_RCC_MCO1_SRC_HSE)    \
                                  || ((source) == HAL_RCC_MCO1_SRC_PLL1)   \
                                  || ((source) == HAL_RCC_MCO1_SRC_HSI48)  \
                                  || ((source) == HAL_RCC_MCO2_SRC_SYSTEM) \
                                  || ((source) == HAL_RCC_MCO2_SRC_PLL2)   \
                                  || ((source) == HAL_RCC_MCO2_SRC_HSE)    \
                                  || ((source) == HAL_RCC_MCO2_SRC_PLL1)   \
                                  || ((source) == HAL_RCC_MCO2_SRC_CSI)    \
                                  || ((source) == HAL_RCC_MCO2_SRC_LSI))

#define IS_RCC_MCOPRE(div) (((div) == HAL_RCC_MCO1_PRESCALERDIS) \
                            || ((div) == HAL_RCC_MCO1_PRESCALER1)  \
                            || ((div) == HAL_RCC_MCO1_PRESCALER2)  \
                            || ((div) == HAL_RCC_MCO1_PRESCALER3)  \
                            || ((div) == HAL_RCC_MCO1_PRESCALER4)  \
                            || ((div) == HAL_RCC_MCO1_PRESCALER5)  \
                            || ((div) == HAL_RCC_MCO1_PRESCALER6)  \
                            || ((div) == HAL_RCC_MCO1_PRESCALER7)  \
                            || ((div) == HAL_RCC_MCO1_PRESCALER8)  \
                            || ((div) == HAL_RCC_MCO1_PRESCALER9)  \
                            || ((div) == HAL_RCC_MCO1_PRESCALER10) \
                            || ((div) == HAL_RCC_MCO1_PRESCALER11) \
                            || ((div) == HAL_RCC_MCO1_PRESCALER12) \
                            || ((div) == HAL_RCC_MCO1_PRESCALER13) \
                            || ((div) == HAL_RCC_MCO1_PRESCALER14) \
                            || ((div) == HAL_RCC_MCO1_PRESCALER15) \
                            || ((div) == HAL_RCC_MCO2_PRESCALERDIS) \
                            || ((div) == HAL_RCC_MCO2_PRESCALER1)  \
                            || ((div) == HAL_RCC_MCO2_PRESCALER2)  \
                            || ((div) == HAL_RCC_MCO2_PRESCALER3)  \
                            || ((div) == HAL_RCC_MCO2_PRESCALER4)  \
                            || ((div) == HAL_RCC_MCO2_PRESCALER5)  \
                            || ((div) == HAL_RCC_MCO2_PRESCALER6)  \
                            || ((div) == HAL_RCC_MCO2_PRESCALER7)  \
                            || ((div) == HAL_RCC_MCO2_PRESCALER8)  \
                            || ((div) == HAL_RCC_MCO2_PRESCALER9)  \
                            || ((div) == HAL_RCC_MCO2_PRESCALER10) \
                            || ((div) == HAL_RCC_MCO2_PRESCALER11) \
                            || ((div) == HAL_RCC_MCO2_PRESCALER12) \
                            || ((div) == HAL_RCC_MCO2_PRESCALER13) \
                            || ((div) == HAL_RCC_MCO2_PRESCALER14) \
                            || ((div) == HAL_RCC_MCO2_PRESCALER15))

#define IS_RCC_PLL_SRC(source) (((source) == HAL_RCC_PLL_SRC_HSI)  \
                                || ((source) == HAL_RCC_PLL_SRC_CSI)  \
                                || ((source) == HAL_RCC_PLL_SRC_HSE)  \
                                || ((source) == HAL_RCC_PLL_SRC_NONE))

#define IS_RCC_PLLM_VALUE(value) ((1U <= (value)) && ((value) <= 64U))

#define IS_RCC_PLLN_VALUE(value) ((8U <= (value)) && ((value) <= 420U))

#define IS_RCC_PLL_SSCG_STATUS(status) (((status) == HAL_RCC_PLL_SSCG_DISABLE) \
                                        || ((status) == HAL_RCC_PLL_SSCG_ENABLE))

#define IS_RCC_PLL_FRACN_VALUE(value) ((value) <= 8191U)

#define IS_RCC_PLL_SSCG_MOD_PER_VALUE(value) ((value) <= 8191U)

#define IS_RCC_PLL_SSCG_MOD_DEPTH_ADJ_VALUE(value) ((value) <= 32767U)

#define IS_RCC_PLL_SSCG_MOD_SPREAD_VALUE(value) (((value) == HAL_RCC_PLL_SSCG_SPREAD_CENTER) \
                                                 || ((value) == HAL_RCC_PLL_SSCG_SPREAD_DOWN))

#define IS_RCC_PLL_SSCG_DITH_CTRL_VALUE(value) (((value) == HAL_RCC_PLL_SSCG_DITH_NO)       \
                                                || ((value) == HAL_RCC_PLL_SSCG_DITH_RPDF)    \
                                                || ((value) == HAL_RCC_PLL_SSCG_DITH_TPDF)    \
                                                || ((value) == HAL_RCC_PLL_SSCG_DITH_RPDF_TPDF))

#define IS_RCC_PLLP_VALUE(value) ((1U <= (value)) && ((value) <= 128U))

#define IS_RCC_PLLQ_VALUE(value) ((1U <= (value)) && ((value) <= 128U))

#define IS_RCC_PLLR_VALUE(value) ((1U <= (value)) && ((value) <= 128U))

#define IS_RCC_PLLS_VALUE(value) ((1U <= (value)) && ((value) <= 8U))

#define IS_RCC_PLLT_VALUE(value) ((1U <= (value)) && ((value) <= 8U))

#define IS_RCC_PLL1_OUTPUT(value) ((((value) & (HAL_RCC_PLL1_OUTPUT_ALL)) != 0x00u) \
                                   && (((value) & ~(HAL_RCC_PLL1_OUTPUT_ALL)) == 0x00u))

#define IS_RCC_PLL2_OUTPUT(value) ((((value) & (HAL_RCC_PLL2_OUTPUT_ALL)) != 0x00u) \
                                   && (((value) & ~(HAL_RCC_PLL2_OUTPUT_ALL)) == 0x00u))

#define IS_RCC_PLL3_OUTPUT(value) ((((value) & (HAL_RCC_PLL3_OUTPUT_ALL)) != 0x00u) \
                                   && (((value) & ~(HAL_RCC_PLL3_OUTPUT_ALL)) == 0x00u))

#define IS_RCC_FMC_CLK(source) (((source) == HAL_RCC_FMC_CLK_SRC_HCLK5)  \
                                || ((source) == HAL_RCC_FMC_CLK_SRC_PLL1Q) \
                                || ((source) == HAL_RCC_FMC_CLK_SRC_PLL2R) \
                                || ((source) == HAL_RCC_FMC_CLK_SRC_HSI))

#define IS_RCC_SDMMC1_CLK(source) (((source) == HAL_RCC_SDMMC1_CLK_SRC_PLL2S) \
                                   || ((source) == HAL_RCC_SDMMC1_CLK_SRC_PLL2T))

#define IS_RCC_XSPI1_CLK(source) (((source) == HAL_RCC_XSPI1_CLK_SRC_HCLK5) \
                                  || ((source) == HAL_RCC_XSPI1_CLK_SRC_PLL2S) \
                                  || ((source) == HAL_RCC_XSPI1_CLK_SRC_PLL2T)) \

#define IS_RCC_OTGFS_CLK(source) (((source) == HAL_RCC_OTGFS_CLK_SRC_HSI48) \
                                  || ((source) == HAL_RCC_OTGFS_CLK_SRC_PLL3Q) \
                                  || ((source) == HAL_RCC_OTGFS_CLK_SRC_HSE))

#define IS_RCC_ADF1_CLK(source) (((source) == HAL_RCC_ADF1_CLK_SRC_HCLK1) \
                                 || ((source) == HAL_RCC_ADF1_CLK_SRC_PLL2P) \
                                 || ((source) == HAL_RCC_ADF1_CLK_SRC_PLL3P) \
                                 || ((source) == HAL_RCC_ADF1_CLK_SRC_PIN) \
                                 || ((source) == HAL_RCC_ADF1_CLK_SRC_CSI) \
                                 || ((source) == HAL_RCC_ADF1_CLK_SRC_HSI))

#define IS_RCC_ADC_CLK(source) (((source) == HAL_RCC_ADC_CLK_SRC_HCLK3) \
                                || ((source) == HAL_RCC_ADC_CLK_SRC_TIMX) \
                                || ((source) == HAL_RCC_ADC_CLK_SRC_HSI) \
                                || ((source) == HAL_RCC_ADC_CLK_SRC_HSE) \
                                || ((source) == HAL_RCC_ADC_CLK_SRC_PLL2P) \
                                || ((source) == HAL_RCC_ADC_CLK_SRC_PLL3R) \
                                || ((source) == HAL_RCC_ADC_CLK_SRC_PER))

#define IS_RCC_CKPER_CLK(source) (((source) == HAL_RCC_CKPER_CLK_SRC_HSI) \
                                  || ((source) == HAL_RCC_CKPER_CLK_SRC_CSI) \
                                  || ((source) == HAL_RCC_CKPER_CLK_SRC_HSE))

#define IS_RCC_UART234578_CLK(source) (((source) == HAL_RCC_UART234578_CLK_SRC_PCLK1) \
                                       || ((source) == HAL_RCC_UART234578_CLK_SRC_PLL2Q) \
                                       || ((source) == HAL_RCC_UART234578_CLK_SRC_PLL3Q) \
                                       || ((source) == HAL_RCC_UART234578_CLK_SRC_HSI) \
                                       || ((source) == HAL_RCC_UART234578_CLK_SRC_CSI) \
                                       || ((source) == HAL_RCC_UART234578_CLK_SRC_LSE))

#define IS_RCC_SPI23_CLK(source) (((source) == HAL_RCC_SPI23_CLK_SRC_PLL1Q) \
                                  || ((source) == HAL_RCC_SPI23_CLK_SRC_PLL2P) \
                                  || ((source) == HAL_RCC_SPI23_CLK_SRC_PLL3P) \
                                  || ((source) == HAL_RCC_SPI23_CLK_SRC_AUDIOCLK) \
                                  || ((source) == HAL_RCC_SPI23_CLK_SRC_PER))

#define IS_RCC_I2C123_CLK(source) (((source) == HAL_RCC_I2C123_CLK_SRC_PCLK1) \
                                   || ((source) == HAL_RCC_I2C123_CLK_SRC_PLL3R) \
                                   || ((source) == HAL_RCC_I2C123_CLK_SRC_HSI) \
                                   || ((source) == HAL_RCC_I2C123_CLK_SRC_CSI))

#define IS_RCC_I3C1_CLK(source) (((source) == HAL_RCC_I3C1_CLK_SRC_PCLK1) \
                                 || ((source) == HAL_RCC_I3C1_CLK_SRC_PLL3R) \
                                 || ((source) == HAL_RCC_I3C1_CLK_SRC_HSI) \
                                 || ((source) == HAL_RCC_I3C1_CLK_SRC_CSI))

#define IS_RCC_LPTIM1_CLK(source) (((source) == HAL_RCC_LPTIM1_CLK_SRC_PCLK1) \
                                   || ((source) == HAL_RCC_LPTIM1_CLK_SRC_PLL2P) \
                                   || ((source) == HAL_RCC_LPTIM1_CLK_SRC_PLL3R) \
                                   || ((source) == HAL_RCC_LPTIM1_CLK_SRC_LSE) \
                                   || ((source) == HAL_RCC_LPTIM1_CLK_SRC_LSI) \
                                   || ((source) == HAL_RCC_LPTIM1_CLK_SRC_PER))

#define IS_RCC_FDCAN_CLK(source) (((source) == HAL_RCC_FDCAN_CLK_SRC_HSE) \
                                  || ((source) == HAL_RCC_FDCAN_CLK_SRC_PLL1Q) \
                                  || ((source) == HAL_RCC_FDCAN_CLK_SRC_PLL2P))

#define IS_RCC_USART16910_CLK(source) (((source) == HAL_RCC_USART16910_CLK_SRC_PCLK2) \
                                       || ((source) == HAL_RCC_USART16910_CLK_SRC_PLL2Q) \
                                       || ((source) == HAL_RCC_USART16910_CLK_SRC_PLL3Q) \
                                       || ((source) == HAL_RCC_USART16910_CLK_SRC_HSI) \
                                       || ((source) == HAL_RCC_USART16910_CLK_SRC_CSI) \
                                       || ((source) == HAL_RCC_USART16910_CLK_SRC_LSE))

#define IS_RCC_SPI45_CLK(source) (((source) == HAL_RCC_SPI45_CLK_SRC_PCLK2) \
                                  || ((source) == HAL_RCC_SPI45_CLK_SRC_PLL2Q) \
                                  || ((source) == HAL_RCC_SPI45_CLK_SRC_PLL3Q) \
                                  || ((source) == HAL_RCC_SPI45_CLK_SRC_HSI) \
                                  || ((source) == HAL_RCC_SPI45_CLK_SRC_CSI) \
                                  || ((source) == HAL_RCC_SPI45_CLK_SRC_HSE))

#define IS_RCC_SPI1_CLK(source) (((source) == HAL_RCC_SPI1_CLK_SRC_PLL1Q) \
                                 || ((source) == HAL_RCC_SPI1_CLK_SRC_PLL2P) \
                                 || ((source) == HAL_RCC_SPI1_CLK_SRC_PLL3P) \
                                 || ((source) == HAL_RCC_SPI1_CLK_SRC_AUDIOCLK) \
                                 || ((source) == HAL_RCC_SPI1_CLK_SRC_PER))

#define IS_RCC_LPUART1_CLK(source) (((source) == HAL_RCC_LPUART1_CLK_SRC_PCLK4) \
                                    || ((source) == HAL_RCC_LPUART1_CLK_SRC_PLL2Q) \
                                    || ((source) == HAL_RCC_LPUART1_CLK_SRC_PLL3Q) \
                                    || ((source) == HAL_RCC_LPUART1_CLK_SRC_HSI) \
                                    || ((source) == HAL_RCC_LPUART1_CLK_SRC_CSI) \
                                    || ((source) == HAL_RCC_LPUART1_CLK_SRC_LSE))

#define IS_RCC_SPI6_CLK(source) (((source) == HAL_RCC_SPI6_CLK_SRC_PCLK4) \
                                 || ((source) == HAL_RCC_SPI6_CLK_SRC_PLL2Q) \
                                 || ((source) == HAL_RCC_SPI6_CLK_SRC_PLL3Q) \
                                 || ((source) == HAL_RCC_SPI6_CLK_SRC_HSI) \
                                 || ((source) == HAL_RCC_SPI6_CLK_SRC_CSI) \
                                 || ((source) == HAL_RCC_SPI6_CLK_SRC_HSE))

#define IS_RCC_LPTIM23_CLK(source) (((source) == HAL_RCC_LPTIM23_CLK_SRC_PCLK4) \
                                    || ((source) == HAL_RCC_LPTIM23_CLK_SRC_PLL2P) \
                                    || ((source) == HAL_RCC_LPTIM23_CLK_SRC_PLL3R) \
                                    || ((source) == HAL_RCC_LPTIM23_CLK_SRC_LSE) \
                                    || ((source) == HAL_RCC_LPTIM23_CLK_SRC_LSI) \
                                    || ((source) == HAL_RCC_LPTIM23_CLK_SRC_PER))

#define IS_RCC_LPTIM45_CLK(source) (((source) == HAL_RCC_LPTIM45_CLK_SRC_PCLK4) \
                                    || ((source) == HAL_RCC_LPTIM45_CLK_SRC_PLL2P) \
                                    || ((source) == HAL_RCC_LPTIM45_CLK_SRC_PLL3R) \
                                    || ((source) == HAL_RCC_LPTIM45_CLK_SRC_LSE) \
                                    || ((source) == HAL_RCC_LPTIM45_CLK_SRC_LSI) \
                                    || ((source) == HAL_RCC_LPTIM45_CLK_SRC_PER))

#define IS_RCC_DAC1_CLK(source) (((source) == HAL_RCC_DAC1_CLK_SRC_HCLK3) \
                                 || ((source) == HAL_RCC_DAC1_CLK_SRC_TIM) \
                                 || ((source) == HAL_RCC_DAC1_CLK_SRC_ADC) \
                                 || ((source) == HAL_RCC_DAC1_CLK_SRC_HSE) \
                                 || ((source) == HAL_RCC_DAC1_CLK_SRC_HSI) \
                                 || ((source) == HAL_RCC_DAC1_CLK_SRC_PLL2P) \
                                 || ((source) == HAL_RCC_DAC1_CLK_SRC_PLL3R) \
                                 || ((source) == HAL_RCC_DAC1_CLK_SRC_PER))

#define IS_RCC_DAC1SH_CLK(source) (((source) == HAL_RCC_DAC1_SH_CLK_SRC_LSE) \
                                   || ((source) == HAL_RCC_DAC1_SH_CLK_SRC_LSI))

#define IS_RCC_DAC2_CLK(source) (((source) == HAL_RCC_DAC2_CLK_SRC_HCLK3) \
                                 || ((source) == HAL_RCC_DAC2_CLK_SRC_TIM) \
                                 || ((source) == HAL_RCC_DAC2_CLK_SRC_ADC) \
                                 || ((source) == HAL_RCC_DAC2_CLK_SRC_HSE) \
                                 || ((source) == HAL_RCC_DAC2_CLK_SRC_HSI) \
                                 || ((source) == HAL_RCC_DAC2_CLK_SRC_PLL2P) \
                                 || ((source) == HAL_RCC_DAC2_CLK_SRC_PLL3R) \
                                 || ((source) == HAL_RCC_DAC2_CLK_SRC_PER))

#define IS_RCC_DAC3_CLK(source) (((source) == HAL_RCC_DAC3_CLK_SRC_HCLK3) \
                                 || ((source) == HAL_RCC_DAC3_CLK_SRC_TIM) \
                                 || ((source) == HAL_RCC_DAC3_CLK_SRC_ADC) \
                                 || ((source) == HAL_RCC_DAC3_CLK_SRC_HSE) \
                                 || ((source) == HAL_RCC_DAC3_CLK_SRC_HSI) \
                                 || ((source) == HAL_RCC_DAC3_CLK_SRC_PLL2P) \
                                 || ((source) == HAL_RCC_DAC3_CLK_SRC_PLL3R) \
                                 || ((source) == HAL_RCC_DAC3_CLK_SRC_PER))

#define IS_RCC_DAC4_CLK(source) (((source) == HAL_RCC_DAC4_CLK_SRC_HCLK3) \
                                 || ((source) == HAL_RCC_DAC4_CLK_SRC_TIM) \
                                 || ((source) == HAL_RCC_DAC4_CLK_SRC_ADC) \
                                 || ((source) == HAL_RCC_DAC4_CLK_SRC_HSE) \
                                 || ((source) == HAL_RCC_DAC4_CLK_SRC_HSI) \
                                 || ((source) == HAL_RCC_DAC4_CLK_SRC_PLL2P) \
                                 || ((source) == HAL_RCC_DAC4_CLK_SRC_PLL3R) \
                                 || ((source) == HAL_RCC_DAC4_CLK_SRC_PER))

#define RCC_UPDATE_SYSTEMCORECLOCK()  (SystemCoreClock = (HAL_RCC_GetSYSCLKFreq()))

/**
  * @}
  */ /* End of RCC_Private_Macros */


/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/** @defgroup RCC_Private_Functions RCC Private Functions
  * @{
  */
static hal_status_t RCC_WaitForTimeout(const rcc_cb_timeout_t p_timeout_cb, uint32_t timeout, uint32_t status);
static hal_status_t RCC_PLL_SetConfig(rcc_pll_id_t pll_id, const hal_rcc_pll_config_t *p_config);
static void         RCC_PLL_GetConfig(rcc_pll_id_t pll_id, hal_rcc_pll_config_t *p_config);
static void         RCC_PLL_GetClockFreq(rcc_pll_id_t pll_id, hal_rcc_pll_output_freq_t *p_clk);
static uint32_t     RCC_HSI_GetCkFreq(void);
/**
  * @}
  */ /* End of RCC_Private_Functions */

/* Exported functions --------------------------------------------------------*/

/** @addtogroup RCC_Exported_Functions
  * @{
  */

/** @addtogroup RCC_Exported_Functions_Group1
  * @{
  */

/** @addtogroup RCC_Exported_Functions_Group1_0
  * @{
  */

/**
  * @brief   Reset the RCC clock configuration to the default reset state.
  * @note    SystemCoreClock and HAL timebase are updated in this function.
  * @note    Resources under backup domain reset if USE_HAL_RCC_RESET_RTC_DOMAIN set to 1U
  * @note    Peripherals clock enable and source selection reset if USE_HAL_RCC_RESET_PERIPH_CLOCK_MANAGEMENT set to 1U
  * @warning Access to RTC domain must be enabled to disable RTC domain source clock.
  */
void HAL_RCC_Reset(void)
{
  uint32_t tickstart;
  uint32_t read_value;

  /* Disable RCC interrupts */
#define RCC_IT_RESET (LL_RCC_IT_LSIRDY | LL_RCC_IT_LSERDY | LL_RCC_IT_HSIRDY | LL_RCC_IT_HSERDY | LL_RCC_IT_CSIRDY | \
                      LL_RCC_IT_HSI48RDY | LL_RCC_IT_PLL1RDY | LL_RCC_IT_PLL2RDY| LL_RCC_IT_PLL3RDY | LL_RCC_IT_LSECSS)
  LL_RCC_DisableIT(RCC_IT_RESET);

#if defined(USE_HAL_RCC_RESET_PERIPH_CLOCK_MANAGEMENT) && (USE_HAL_RCC_RESET_PERIPH_CLOCK_MANAGEMENT == 1U)
  /* Reset peripheral clock enable */
  LL_CKG_Enable(LL_CKG_PERIPH_ALL);

  LL_AHB1_GRP1_DisableClock(LL_AHB1_GRP1_PERIPH_ALL);
  LL_AHB2_GRP1_DisableClock(LL_AHB2_GRP1_PERIPH_ALL & (~(LL_AHB2_GRP1_PERIPH_AHBSRAM1 | LL_AHB2_GRP1_PERIPH_AHBSRAM2 |
                                                         LL_AHB2_GRP1_PERIPH_AHBSRAM3)));
  LL_AHB3_GRP1_DisableClock(LL_AHB3_GRP1_PERIPH_ALL);
  LL_AHB4_GRP1_DisableClock(LL_AHB4_GRP1_PERIPH_ALL);
  LL_AHB5_GRP1_DisableClock(LL_AHB5_GRP1_PERIPH_ALL);

  LL_APB1_GRP1_DisableClock(LL_APB1_GRP1_PERIPH_ALL);
  LL_APB1_GRP2_DisableClock(LL_APB1_GRP2_PERIPH_ALL);
  LL_APB2_GRP1_DisableClock(LL_APB2_GRP1_PERIPH_ALL);
  LL_APB4_GRP1_DisableClock(LL_APB4_GRP1_PERIPH_ALL);

  LL_AHB1_GRP1_EnableClockLowPower(LL_AHB1_GRP1_PERIPH_ALL);
  LL_AHB2_GRP1_EnableClockLowPower(LL_AHB2_GRP1_PERIPH_ALL);
  LL_AHB3_GRP1_EnableClockLowPower(LL_AHB3_GRP1_PERIPH_ALL);
  LL_AHB4_GRP1_EnableClockLowPower(LL_AHB4_GRP1_PERIPH_ALL);
  LL_AHB5_GRP1_EnableClockLowPower(LL_AHB5_GRP1_PERIPH_ALL);
  LL_APB1_GRP1_EnableClockLowPower(LL_APB1_GRP1_PERIPH_ALL);
  LL_APB1_GRP2_EnableClockLowPower(LL_APB1_GRP2_PERIPH_ALL);
  LL_APB2_GRP1_EnableClockLowPower(LL_APB2_GRP1_PERIPH_ALL);
  LL_APB4_GRP1_EnableClockLowPower(LL_APB4_GRP1_PERIPH_ALL);

  /* Reset peripheral clock source selection */
#define RCC_CCIPR1_RESET (RCC_CCIPR1_FMCSEL | RCC_CCIPR1_SDMMC1SEL | RCC_CCIPR1_XSPI1SEL | RCC_CCIPR1_OTGFSSEL \
                          | RCC_CCIPR1_ADF1SEL| RCC_CCIPR1_ADCDIV | RCC_CCIPR1_ADCSEL | RCC_CCIPR1_CKPERSEL)
  read_value = LL_RCC_READ_REG(CCIPR1);
  LL_RCC_WRITE_REG(CCIPR1, (read_value & ~RCC_CCIPR1_RESET));

#define RCC_CCIPR2_RESET (RCC_CCIPR2_UART234578SEL | RCC_CCIPR2_SPI23SEL | RCC_CCIPR2_I2C123SEL | RCC_CCIPR2_I3C1SEL \
                          | RCC_CCIPR2_LPTIM1SEL | RCC_CCIPR2_FDCANSEL)
  read_value = LL_RCC_READ_REG(CCIPR2);
  LL_RCC_WRITE_REG(CCIPR2, (read_value & ~RCC_CCIPR2_RESET));

#define RCC_CCIPR3_RESET (RCC_CCIPR3_USART16910SEL | RCC_CCIPR3_SPI45SEL | RCC_CCIPR3_SPI1SEL)
  read_value = LL_RCC_READ_REG(CCIPR3);
  LL_RCC_WRITE_REG(CCIPR3, (read_value & ~RCC_CCIPR3_RESET));


#define RCC_CCIPR4_RESET (RCC_CCIPR4_LPUART1SEL | RCC_CCIPR4_SPI6SEL | RCC_CCIPR4_LPTIM23SEL | RCC_CCIPR4_LPTIM45SEL \
                          | RCC_CCIPR4_DAC1SEL | RCC_CCIPR4_DAC1SHSEL | RCC_CCIPR4_DAC2SEL | RCC_CCIPR4_DAC3SEL \
                          | RCC_CCIPR4_DAC4SEL)
  read_value = LL_RCC_READ_REG(CCIPR4);
  LL_RCC_WRITE_REG(CCIPR4, (read_value & ~RCC_CCIPR4_RESET));

#endif /* USE_HAL_RCC_RESET_PERIPH_CLOCK_MANAGEMENT */

  /* Reset System clock */
  LL_RCC_HSI_SetDivider(LL_RCC_HSI_DIV_1);
  LL_RCC_HSI_Enable();

  (void)RCC_WaitForTimeout(LL_RCC_HSI_IsReady, RCC_HSI_TIMEOUT_VALUE, 1U);

  tickstart = HAL_GetTick();

  /* HSI is selected as system clock source */
  LL_RCC_SetSysClkSource(LL_RCC_SYS_CLKSOURCE_HSI);

  /* Wait till clock switch is ready */
  while (LL_RCC_GetSysClkSource() != LL_RCC_SYS_CLKSOURCE_STATUS_HSI)
  {
    if ((HAL_GetTick() - tickstart) > RCC_CLOCKSWITCH_TIMEOUT_VALUE)
    {
      break;
    }
  }

  /* Reset all bus dividers */
  LL_RCC_SetSysPrescaler(LL_RCC_SYSCPUCLK_PRESCALER_1);
  LL_RCC_ConfigBusClock((uint32_t)LL_RCC_HCLK_PRESCALER_1, (uint32_t)LL_RCC_APB1_PRESCALER_1 |
                        (uint32_t)LL_RCC_APB2_PRESCALER_1 |
                        (uint32_t)LL_RCC_APB4_PRESCALER_1);

  SystemCoreClock = HSI_VALUE;

  /* Adapt Systick interrupt period */
  HAL_InitTick(HAL_TICK_FREQ_DEFAULT, uwTickPrio);

#if defined(USE_HAL_RCC_RESET_RTC_DOMAIN) && (USE_HAL_RCC_RESET_RTC_DOMAIN == 1U)
  /* Reset backup domain */
  LL_RCC_ForceBackupDomainReset();
  LL_RCC_ReleaseBackupDomainReset();
#endif /* USE_HAL_RCC_RESET_RTC_DOMAIN */

  /* Reset all remaining oscillators not in backup domain (excepted the one used for System clock) */
  read_value = LL_RCC_READ_REG(CR);
#define RCC_CR_RESET1 (RCC_CR_HSIKERON |RCC_CR_CSION | RCC_CR_CSIKERON | RCC_CR_HSI48ON | RCC_CR_HSEON | RCC_CR_PLL1ON \
                       | RCC_CR_PLL2ON | RCC_CR_PLL3ON)
#define RCC_CR_RESET2 (RCC_CR_RESET1 | RCC_CR_HSEBYP | RCC_CR_HSEEXT)
  LL_RCC_WRITE_REG(CR, (read_value & ~RCC_CR_RESET1));
  LL_RCC_WRITE_REG(CR, (read_value & ~RCC_CR_RESET2));   /* HSE EXT and BYP disabled only when HSE has been disabled */

  LL_RCC_LSI_Disable();

  RCC_WaitForTimeout(LL_RCC_PLL1_IsReady, RCC_PLL1_TIMEOUT_VALUE, 0U);
  RCC_WaitForTimeout(LL_RCC_PLL2_IsReady, RCC_PLL1_TIMEOUT_VALUE, 0U);
  RCC_WaitForTimeout(LL_RCC_PLL3_IsReady, RCC_PLL3_TIMEOUT_VALUE, 0U);

  /* Reset MCO, RTC prescaler and wake up system clock */
  read_value = LL_RCC_READ_REG(CFGR);
#if defined(USE_HAL_RCC_RESET_PERIPH_CLOCK_MANAGEMENT) && (USE_HAL_RCC_RESET_PERIPH_CLOCK_MANAGEMENT == 1U)
#define RCC_CFGR_RESET (RCC_CFGR_RTCPRE | RCC_CFGR_MCO1PRE | RCC_CFGR_MCO1SEL | RCC_CFGR_MCO2PRE | RCC_CFGR_MCO2SEL)
#else
#define RCC_CFGR_RESET (RCC_CFGR_MCO1PRE | RCC_CFGR_MCO1SEL | RCC_CFGR_MCO2PRE | RCC_CFGR_MCO2SEL)
#endif /* USE_HAL_RCC_RESET_PERIPH_CLOCK_MANAGEMENT */

  LL_RCC_WRITE_REG(CFGR, (read_value & ~RCC_CFGR_RESET));

  /* Reset PLLs */
#define RCC_PLLCKSELR_RESET (RCC_PLLCKSELR_PLLSRC | RCC_PLLCKSELR_DIVM1 | RCC_PLLCKSELR_DIVM2 | RCC_PLLCKSELR_DIVM3)
#define RCC_PLLCFGR_RESET (RCC_PLLCFGR_PLL1FRACEN | RCC_PLLCFGR_PLL1VCOSEL | RCC_PLLCFGR_PLL1SSCGEN \
                           | RCC_PLLCFGR_PLL1RGE | RCC_PLLCFGR_PLL1PEN | RCC_PLLCFGR_PLL1QEN | RCC_PLLCFGR_PLL1SEN \
                           | RCC_PLLCFGR_PLL2FRACLEN | RCC_PLLCFGR_PLL2VCOSEL | RCC_PLLCFGR_PLL2SSCGEN \
                           | RCC_PLLCFGR_PLL2RGE | RCC_PLLCFGR_PLL2PEN | RCC_PLLCFGR_PLL2QEN | RCC_PLLCFGR_PLL2REN \
                           | RCC_PLLCFGR_PLL2SEN | RCC_PLLCFGR_PLL2TEN \
                           | RCC_PLLCFGR_PLL3FRACEN | RCC_PLLCFGR_PLL3VCOSEL | RCC_PLLCFGR_PLL3SSCGEN \
                           | RCC_PLLCFGR_PLL3RGE | RCC_PLLCFGR_PLL3PEN | RCC_PLLCFGR_PLL3QEN | RCC_PLLCFGR_PLL3REN \
                           | RCC_PLLCFGR_PLL3SEN)
#define RCC_PLLFRACR_RESET (RCC_PLL1FRACR_FRACN)
#define RCC_PLLSSCGR_RESET (RCC_PLL1SSCGR_MODPER | RCC_PLL1SSCGR_TPDFNDIS | RCC_PLL1SSCGR_RPDFNDIS \
                            | RCC_PLL1SSCGR_SPREADSEL | RCC_PLL1SSCGR_INCSTEP)

  read_value = LL_RCC_READ_REG(PLLCKSELR);
  LL_RCC_WRITE_REG(PLLCKSELR, (read_value & ~RCC_PLLCKSELR_RESET));
  read_value = LL_RCC_READ_REG(PLLCFGR);
  LL_RCC_WRITE_REG(PLLCFGR, (read_value & ~RCC_PLLCFGR_RESET));

#define RCC_PLL1DIVR1_RESET (RCC_PLL1DIVR1_DIVN | RCC_PLL1DIVR1_DIVP | RCC_PLL1DIVR1_DIVQ)
#define RCC_PLL1DIVR2_RESET (RCC_PLL1DIVR2_DIVS)
#define PLL1DIVR1_DEFAULT (0x01010280U)
#define PLL1DIVR2_DEFAULT (0x00000101U)
  read_value = LL_RCC_READ_REG(PLL1DIVR1);
  LL_RCC_WRITE_REG(PLL1DIVR1, ((read_value & ~RCC_PLL1DIVR1_RESET) | PLL1DIVR1_DEFAULT));
  read_value = LL_RCC_READ_REG(PLL1DIVR2);
  LL_RCC_WRITE_REG(PLL1DIVR2, ((read_value & ~RCC_PLL1DIVR2_RESET) | PLL1DIVR2_DEFAULT));
  read_value = LL_RCC_READ_REG(PLL1FRACR);
  LL_RCC_WRITE_REG(PLL1FRACR, (read_value & ~RCC_PLLFRACR_RESET));
  read_value = LL_RCC_READ_REG(PLL1SSCGR);
  LL_RCC_WRITE_REG(PLL1SSCGR, (read_value & ~RCC_PLLSSCGR_RESET));

#define RCC_PLL2DIVR1_RESET (RCC_PLL2DIVR1_DIVN | RCC_PLL2DIVR1_DIVP | RCC_PLL2DIVR1_DIVQ | RCC_PLL2DIVR1_DIVR)
#define RCC_PLL2DIVR2_RESET (RCC_PLL2DIVR2_DIVS | RCC_PLL2DIVR2_DIVT)
#define PLL2DIVR1_DEFAULT (0x01010280U)
#define PLL2DIVR2_DEFAULT (0x00000101U)
  read_value = LL_RCC_READ_REG(PLL2DIVR1);
  LL_RCC_WRITE_REG(PLL2DIVR1, ((read_value & ~RCC_PLL2DIVR1_RESET) | PLL2DIVR1_DEFAULT));
  read_value = LL_RCC_READ_REG(PLL2DIVR2);
  LL_RCC_WRITE_REG(PLL2DIVR2, ((read_value & ~RCC_PLL2DIVR2_RESET) | PLL2DIVR2_DEFAULT));
  read_value = LL_RCC_READ_REG(PLL2FRACR);
  LL_RCC_WRITE_REG(PLL2FRACR, (read_value & ~RCC_PLLFRACR_RESET));
  read_value = LL_RCC_READ_REG(PLL2SSCGR);
  LL_RCC_WRITE_REG(PLL2SSCGR, (read_value & ~RCC_PLLSSCGR_RESET));

#define RCC_PLL3DIVR1_RESET (RCC_PLL3DIVR1_DIVN | RCC_PLL3DIVR1_DIVP | RCC_PLL3DIVR1_DIVQ | RCC_PLL3DIVR1_DIVR)
#define RCC_PLL3DIVR2_RESET (RCC_PLL3DIVR2_DIVS)
#define PLL3DIVR1_DEFAULT (0x01010280U)
#define PLL3DIVR2_DEFAULT (0x00000101U)
  read_value = LL_RCC_READ_REG(PLL3DIVR1);
  LL_RCC_WRITE_REG(PLL3DIVR1, ((read_value & ~RCC_PLL3DIVR1_RESET) | PLL3DIVR1_DEFAULT));
  read_value = LL_RCC_READ_REG(PLL3DIVR2);
  LL_RCC_WRITE_REG(PLL3DIVR2, ((read_value & ~RCC_PLL3DIVR2_RESET) | PLL3DIVR2_DEFAULT));
  read_value = LL_RCC_READ_REG(PLL3FRACR);
  LL_RCC_WRITE_REG(PLL3FRACR, (read_value & ~RCC_PLLFRACR_RESET));
  read_value = LL_RCC_READ_REG(PLL3SSCGR);
  LL_RCC_WRITE_REG(PLL3SSCGR, (read_value & ~RCC_PLLSSCGR_RESET));

  /* Clear RCC flags */
  LL_RCC_ClearFlag(RCC_IT_RESET | LL_RCC_IT_HSECSS);
  LL_RCC_ClearResetFlags();
}

/**
  * @brief  Reset the RCC clock configuration to the default system clock (HSI at XXXMhz)
  * @note   SystemCoreClock and Systick are updated in this function.
  * @retval HAL_OK    System clock switched to HSI (XXXMhz)
  * @retval HAL_ERROR Timeout issue to enable the HSI oscillator\n
  *                   Switch to HSI as source clock failed\n
  *                   Issue to reconfigure the System tick
  */
hal_status_t HAL_RCC_ResetSystemClock(void)
{
  uint32_t tickstart;

  LL_RCC_HSI_SetDivider(LL_RCC_HSI_DIV_1);
  LL_RCC_HSI_Enable();

  if (RCC_WaitForTimeout(LL_RCC_HSI_IsReady, RCC_HSI_TIMEOUT_VALUE, 1U) != HAL_OK)
  {
    return HAL_ERROR;
  }

  tickstart = HAL_GetTick();

  LL_RCC_SetSysClkSource(LL_RCC_SYS_CLKSOURCE_HSI);

  /* Wait till clock switch is ready */
  while (LL_RCC_GetSysClkSource() != LL_RCC_SYS_CLKSOURCE_STATUS_HSI)
  {
    if ((HAL_GetTick() - tickstart) > RCC_CLOCKSWITCH_TIMEOUT_VALUE)
    {
      /* New check to avoid false timeout detection in case of preemption */
      if (LL_RCC_GetSysClkSource() != LL_RCC_SYS_CLKSOURCE_STATUS_HSI)
      {
        return HAL_ERROR;
      }
    }
  }
  LL_RCC_SetSysPrescaler(LL_RCC_SYSCPUCLK_PRESCALER_1);
  LL_RCC_SetAHBPrescaler(LL_RCC_HCLK_PRESCALER_1);
  SystemCoreClock = HSI_VALUE;

  /* Adapt Systick interrupt period */
  return (HAL_InitTick(HAL_TICK_FREQ_DEFAULT, TICK_INT_PRIORITY));
}

/**
  * @}
  */ /* End of RCC_Exported_Functions_Group1_0 */


/** @addtogroup RCC_Exported_Functions_Group1_1
  * @{
  */

#if defined(HSE_VALUE)

/**
  * @brief  Enable the HSE oscillator in the selected mode.
  * @param  mode        HSE mode.\n This parameter can be one of the following values:
  *         @arg @ref HAL_RCC_HSE_ON
  *         @arg @ref HAL_RCC_HSE_BYPASS
  *         @arg @ref HAL_RCC_HSE_BYPASS_DIGITAL
  * @note   Transitions HSE Bypass to HSE On and HSE On to HSE Bypass are not
  *         supported by this function.
  * @retval HAL_OK      HSE oscillator has been activated successfully
  * @retval HAL_ERROR   Timeout linked to HSE ready flag not set
  */
hal_status_t HAL_RCC_HSE_Enable(hal_rcc_hse_t mode)
{
  ASSERT_DBG_PARAM(IS_RCC_HSE_MODE_ENABLE(mode));

  /* Set the new HSE configuration */
  if (((uint32_t)mode & RCC_CR_HSEBYP) == RCC_CR_HSEBYP)
  {
    LL_RCC_HSE_ConfigBypass((uint32_t)mode & RCC_CR_HSEEXT);
  }

  LL_RCC_HSE_Enable();

  return RCC_WaitForTimeout(LL_RCC_HSE_IsReady, RCC_HSE_TIMEOUT_VALUE, 1U);
}

/**
  * @brief  Disable the HSE oscillator.
  * @warning This oscillator might be used as peripheral clock source
  *         and this function will stop any peripheral functions.
  * @retval HAL_OK      HSE oscillator has been deactivated successfully
  * @retval HAL_ERROR   HSE is used as system clock or source clock of the main PLL used as system clock\n
  *                     Timeout linked to HSE ready flag not reset
  */
hal_status_t HAL_RCC_HSE_Disable(void)
{
  hal_status_t status;
  uint32_t sysclk_source;
  uint32_t pll_source;

  sysclk_source = LL_RCC_GetSysClkSource();
  pll_source    = LL_RCC_PLL_GetSource();

  /* Check that HSE is not used as system clock or as PLL source when PLL is selected as system clock */
  if ((sysclk_source == LL_RCC_SYS_CLKSOURCE_STATUS_HSE)
      || ((sysclk_source == LL_RCC_SYS_CLKSOURCE_STATUS_PLL1) && (pll_source == LL_RCC_PLLSOURCE_HSE)))
  {
    status = HAL_ERROR;
  }
  else
  {
    LL_RCC_HSE_Disable();
    LL_RCC_HSE_DisableBypass();
    LL_RCC_HSE_SetClockMode(LL_RCC_HSE_ANALOG_MODE);
    status = RCC_WaitForTimeout(LL_RCC_HSE_IsReady, RCC_HSE_TIMEOUT_VALUE, 0U);
  }

  return status;
}

#endif /* HSE_VALUE */

#if defined(LSE_VALUE)

/**
  * @brief  Enable the LSE oscillator in the selected mode with a oscillator drive capability.
  * @param  mode        LSE mode.\n This parameter can be one of the following values:
  *         @arg @ref HAL_RCC_LSE_ON
  *         @arg @ref HAL_RCC_LSE_BYPASS
  * @param  drive         LSE drive capability
  * @warning Access to backup domain must be enabled.
  * @note   Drive capability is relevant only in Xtal mode (means not in bypass mode)
  * @retval HAL_OK      LSE oscillator has been configured successfully
  * @retval HAL_ERROR   Backup domain is not enabled\n
  *                     Timeout linked to LSE ready flag not set\n
  *                     LSE propagation enable issue (HAL_RCC_LSE_ON or HAL_RCC_LSE_BYPASS)\n
  *                     LSE propagation disable issue (HAL_RCC_LSE_ON_RTC_ONLY or HAL_RCC_LSE_BYPASS_RTC_ONLY)
  */
hal_status_t HAL_RCC_LSE_Enable(hal_rcc_lse_t mode, hal_rcc_lse_drive_t drive)
{
  ASSERT_DBG_PARAM(IS_RCC_LSE_MODE_ENABLE(mode));
  ASSERT_DBG_PARAM(IS_RCC_LSE_DRIVE(drive));

  if (LL_PWR_IsEnabledBackupWriteProtection() != 0U)
  {
    return HAL_ERROR;
  }
  /* Set the new LSE configuration ---------------------------------------*/
  if (((uint32_t)mode & RCC_BDCR_LSEBYP) == RCC_BDCR_LSEBYP)
  {
    LL_RCC_LSE_EnableBypass();
  }
  else
  {
    /* LSE drive capability can be configured */
    LL_RCC_LSE_SetDriveCapability((uint32_t)drive);
  }

  /* Enable LSE and wait for activation */
  LL_RCC_LSE_Enable();
  if (RCC_WaitForTimeout(LL_RCC_LSE_IsReady, RCC_LSE_TIMEOUT_VALUE, 1U) != HAL_OK)
  {
    return HAL_ERROR;
  }

  return HAL_OK;
}

/**
  * @brief  Disable the LSE oscillator.
  * @warning This oscillator might be used as peripheral clock source
  *         and this function will stop any peripheral functions.
  * @note   Transitions LSE Bypass to LSE On and LSE On to LSE Bypass are not
  *         supported by this function.
  * @warning Access to backup domain must be enabled.
  * @retval HAL_OK      LSE oscillator has been configured successfully
  * @retval HAL_ERROR   Backup domain is not enabled\n
  *                     Timeout linked to LSE ready flag not reset\n
  *                     LSE propagation not disabled
  */
hal_status_t HAL_RCC_LSE_Disable(void)
{
  if (LL_PWR_IsEnabledBackupWriteProtection() != 0U)
  {
    return HAL_ERROR;
  }
  LL_RCC_LSE_Disable();
  LL_RCC_LSE_DisableBypass();
  if (RCC_WaitForTimeout(LL_RCC_LSE_IsReady, RCC_LSE_TIMEOUT_VALUE, 0U) != HAL_OK)
  {
    return HAL_ERROR;
  }

  /* Reset LSE drive to low value (default) */
  LL_RCC_LSE_SetDriveCapability(LL_RCC_LSE_DRIVE_LOW);

  return HAL_OK;
}
#endif /* LSE_VALUE */

/**
  * @brief  Enable the HSI oscillator.
  * @param  prescaler  Prescaler value
  * @retval HAL_OK      HSI oscillator has been activated successfully
  * @retval HAL_ERROR   HSI is used as source clock of any active PLL\n
  *                     Timeout linked to HSI Divider ready flag not set\n
  *                     Timeout linked to HSI ready flag not set
  */
hal_status_t HAL_RCC_HSI_Enable(hal_rcc_hsi_div_t prescaler)
{
  hal_status_t status = HAL_OK;
  uint32_t divider;
  uint32_t pll_source;

  divider = LL_RCC_HSI_GetDivider();

  /* Check if HSI already has the correct configuration */
  if ((divider != prescaler) || (LL_RCC_HSI_IsReady() == 0U))
  {
    pll_source = LL_RCC_PLL_GetSource();
    /* Check that HSI is not used as system clock or as PLL source of any active PLL */
    if ((pll_source == LL_RCC_PLLSOURCE_HSI)
        && (((LL_RCC_PLL1_IsReady() == 1U)) || (LL_RCC_PLL2_IsReady() == 1U) || (LL_RCC_PLL3_IsReady() == 1U)))
    {
      status = HAL_ERROR;
    }
    else
    {
      LL_RCC_HSI_SetDivider(prescaler);
      LL_RCC_HSI_Enable();

      status = RCC_WaitForTimeout(LL_RCC_HSI_IsDividerReady, RCC_HSI_TIMEOUT_VALUE, 1U);
      if (status == HAL_OK)
      {
        status = RCC_WaitForTimeout(LL_RCC_HSI_IsReady, RCC_HSI_TIMEOUT_VALUE, 1U);
      }
    }
  }
  return status;
}

/**
  * @brief  Disable the HSI oscillator.
  * @warning This oscillator might be used as peripheral clock source
  *         and this function will stop any peripheral functions.
  * @retval HAL_OK      HSI oscillator has been deactivated successfully
  * @retval HAL_ERROR   HSI is used as system clock or source clock of the main PLL used as system clock\n
  *                     Timeout linked to HSI ready flag not reset
  */
hal_status_t HAL_RCC_HSI_Disable(void)
{
  hal_status_t status;
  uint32_t sysclk_source;
  uint32_t pll_source;

  sysclk_source = LL_RCC_GetSysClkSource();
  pll_source    = LL_RCC_PLL_GetSource();

  /* Check that HSI is not used as system clock or as PLL source when PLL is selected as system clock */
  if ((sysclk_source == LL_RCC_SYS_CLKSOURCE_STATUS_HSI)
      || ((sysclk_source == LL_RCC_SYS_CLKSOURCE_STATUS_PLL1) && (pll_source == LL_RCC_PLLSOURCE_HSI)))
  {
    status = HAL_ERROR;
  }
  else
  {
    LL_RCC_HSI_Disable();
    status = RCC_WaitForTimeout(LL_RCC_HSI_IsReady, RCC_HSI_TIMEOUT_VALUE, 0U);
  }

  return status;
}

/**
  * @brief  Configure the HSI oscillator trimming value.
  * @param  value  Trimming value (default is @ref HAL_RCC_HSICALIBRATION_DEFAULT).
  *                This parameter must be a number between 0 and 127.
  * @note   The trimming is used to compensate for the variations in voltage
  *         and temperature that influence the frequency of the internal HSI RC.
  * @note   The trimming value might be updated while the HSI oscillator is enabled.
  */
void HAL_RCC_HSI_SetTrimming(uint32_t value)
{
  ASSERT_DBG_PARAM(IS_RCC_HSI_CALIBRATION_VALUE(value));

  LL_RCC_HSI_SetCalibTrimming(value);
}

/**
  * @brief  Get the HSI oscillator trimming value.
  * @retval Trimming Number between 0 and 127.
  */
uint32_t HAL_RCC_HSI_GetTrimming(void)
{
  return LL_RCC_HSI_GetCalibTrimming();
}

/**
  * @brief  Get the HSI oscillator calibration value.
  * @retval Calibration Number between 0 and 4095.
  */
uint32_t  HAL_RCC_HSI_GetCalibration(void)
{
  return LL_RCC_HSI_GetCalibration();
}

/**
  * @brief  Enable the HSI48 oscillator.
  * @retval HAL_OK      HSI48 oscillator has been activated successfully
  * @retval HAL_ERROR   Timeout linked to HSI48 ready flag not set
  */
hal_status_t HAL_RCC_HSI48_Enable(void)
{
  LL_RCC_HSI48_Enable();

  return RCC_WaitForTimeout(LL_RCC_HSI48_IsReady, RCC_HSI48_TIMEOUT_VALUE, 1U);
}

/**
  * @brief  Disable the HSI48 oscillator.
  * @warning This oscillator might be used as peripheral clock source
  *         and this function will stop any peripheral functions.
  * @retval HAL_OK      HSI48 oscillator has been deactivated successfully
  * @retval HAL_ERROR   Timeout linked to HSI48 ready flag not reset
  */
hal_status_t HAL_RCC_HSI48_Disable(void)
{
  LL_RCC_HSI48_Disable();

  return RCC_WaitForTimeout(LL_RCC_HSI48_IsReady, RCC_HSI48_TIMEOUT_VALUE, 0U);
}

/**
  * @brief  Get the HSI48 oscillator calibration value.
  * @retval Calibration Number between 0 and 1023.
  */
uint32_t  HAL_RCC_HSI48_GetCalibration(void)
{
  return LL_RCC_HSI48_GetCalibration();
}


/**
  * @brief  Enable the CSI oscillator.
  * @retval HAL_OK      CSI oscillator has been activated successfully
  * @retval HAL_ERROR   Timeout linked to CSI ready flag not set
  */
hal_status_t HAL_RCC_CSI_Enable(void)
{
  LL_RCC_CSI_Enable();

  return RCC_WaitForTimeout(LL_RCC_CSI_IsReady, RCC_CSI_TIMEOUT_VALUE, 1U);
}

/**
  * @brief  Disable the CSI oscillator.
  * @warning This oscillator might be used as peripheral clock source
  *         and this function will stop any peripheral functions.
  * @retval HAL_OK      CSI oscillator has been deactivated successfully
  * @retval HAL_ERROR   CSI is used as system clock or source clock of the main PLL used as system clock\n
  *                     Timeout linked to CSI ready flag not reset
  */
hal_status_t HAL_RCC_CSI_Disable(void)
{
  hal_status_t status;
  uint32_t sysclk_source;
  uint32_t pll_source;

  sysclk_source = LL_RCC_GetSysClkSource();
  pll_source    = LL_RCC_PLL_GetSource();

  /* Check that CSI is not used as system clock or as PLL source when PLL is selected as system clock */
  if ((sysclk_source == LL_RCC_SYS_CLKSOURCE_STATUS_CSI)
      || ((sysclk_source == LL_RCC_SYS_CLKSOURCE_STATUS_PLL1) && (pll_source == LL_RCC_PLLSOURCE_CSI)))
  {
    status = HAL_ERROR;
  }
  else
  {
    LL_RCC_CSI_Disable();
    status = RCC_WaitForTimeout(LL_RCC_CSI_IsReady, RCC_CSI_TIMEOUT_VALUE, 0U);
  }

  return status;
}

/**
  * @brief  Configure the CSI oscillator trimming value.
  * @param  value  Trimming value (default is @ref HAL_RCC_CSICALIBRATION_DEFAULT).
  *                This parameter must be a number between 0 and 63.
  * @note   The trimming is used to compensate for the variations in voltage
  *         and temperature that influence the frequency of the internal HSI RC.
  * @note   The trimming value might be updated while the HSI oscillator is enabled.
  */
void HAL_RCC_CSI_SetTrimming(uint32_t value)
{
  ASSERT_DBG_PARAM(IS_RCC_CSI_CALIBRATION_VALUE(value));

  LL_RCC_CSI_SetCalibTrimming(value);
}

/**
  * @brief  Get the CSI oscillator trimming value.
  * @retval Trimming Number between 0 and 63.
  */
uint32_t HAL_RCC_CSI_GetTrimming(void)
{
  return LL_RCC_CSI_GetCalibTrimming();
}

/**
  * @brief  Get the CSI oscillator calibration value.
  * @retval Calibration Number between 0 and 255.
  */
uint32_t  HAL_RCC_CSI_GetCalibration(void)
{
  return LL_RCC_CSI_GetCalibration();
}

/**
  * @brief  Enable the Internal Low Speed oscillator (LSI).
  * @warning Access to backup domain must be enabled.
  * @retval HAL_OK      LSI oscillator has been configured successfully
  * @retval HAL_ERROR   Timeout linked to LSI ready flag not set\n
  *                     Backup domain is not enabled
  */
hal_status_t HAL_RCC_LSI_Enable(void)
{
  /* Enable the Internal Low Speed oscillator (LSI) */
  LL_RCC_LSI_Enable();

  return RCC_WaitForTimeout(LL_RCC_LSI_IsReady, RCC_LSI_TIMEOUT_VALUE, 1U);
}

/**
  * @brief  Disable the LSI oscillator.
  * @warning This oscillator might be used as peripheral clock source
  *          and this function will stop any peripheral functions.
  * @warning Access to backup domain must be enabled.
  * @retval HAL_OK      LSI oscillator has been deactivated successfully
  * @retval HAL_ERROR   Timeout linked to LSI ready flag not reset\n
  *                     Backup domain is not enabled
  */
hal_status_t HAL_RCC_LSI_Disable(void)
{
  LL_RCC_LSI_Disable();

  return RCC_WaitForTimeout(LL_RCC_LSI_IsReady, RCC_LSI_TIMEOUT_VALUE, 0U);
}

/**
  * @}
  */ /* End of RCC_Exported_Functions_Group1_1 */


/** @addtogroup RCC_Exported_Functions_Group1_2
  * @{
  */

/**
  * @brief  Set the system bus clock source (SYSCLK).
  * @param  source  System clock source based on @ref hal_rcc_sysclk_src_t
  * @note   SystemCoreClock and Systick are updated in this function.
  * @retval HAL_OK    Success\n
  * @retval HAL_ERROR System clock source has not been applied\n
  *                   Source is not enable
  *                   Output PLL1R not enabled to switch to PLLCLK\n
  *                   Issue to reconfigure the System tick
  */
hal_status_t HAL_RCC_SetSYSCLKSource(hal_rcc_sysclk_src_t source)
{
  uint32_t tickstart;
  hal_status_t status = HAL_OK;

  ASSERT_DBG_PARAM(IS_RCC_SYSCLKSOURCE(source));

  LL_RCC_SetSysClkSource((uint32_t)source);

  tickstart = HAL_GetTick();

  while (HAL_RCC_GetSYSCLKSource() != source)
  {
    if ((HAL_GetTick() - tickstart) > RCC_CLOCKSWITCH_TIMEOUT_VALUE)
    {
      status = HAL_ERROR;
      break;
    }
  }

  if (status == HAL_OK)
  {
    RCC_UPDATE_SYSTEMCORECLOCK();

    /* Configure the source of time base considering new system clocks settings*/
    status = HAL_InitTick(uwTickFreq, uwTickPrio);
  }

  return status;
}

/**
  * @brief   Get the system clock source (SYSCLK).
  * @retval  hal_rcc_sysclk_src_t System Clock source
  */
hal_rcc_sysclk_src_t HAL_RCC_GetSYSCLKSource(void)
{
  return (hal_rcc_sysclk_src_t)(uint32_t)((LL_RCC_GetSysClkSource() >> RCC_CFGR_SWS_Pos) << RCC_CFGR_SW_Pos);
}

/**
  * @brief  Set the system clock (CPRE) divider.
  * @param  prescaler  Prescaler value
  * @note   SystemCoreClock and Systick are updated in this function.
  * @retval HAL_OK     CPRE prescaler has been changed successfully
  * @retval HAL_ERROR  Issue to reconfigure the System tick
  */
hal_status_t HAL_RCC_SetSysClkPrescaler(hal_rcc_sys_cpu_clk_prescaler_t prescaler)
{
  ASSERT_DBG_PARAM(IS_RCC_SYSCPUCLK(prescaler));

  LL_RCC_SetSysPrescaler((uint32_t)prescaler);

  RCC_UPDATE_SYSTEMCORECLOCK();

  /* Configure the source of time base considering new system clocks settings */
  return HAL_InitTick(uwTickFreq, uwTickPrio);
}

/**
  * @brief  Set the AHB clock (HCLK) divider.
  * @param  prescaler  Prescaler value
  */
void HAL_RCC_SetHCLKPrescaler(hal_rcc_hclk_prescaler_t prescaler)
{
  ASSERT_DBG_PARAM(IS_RCC_HCLK(prescaler));

  LL_RCC_SetAHBPrescaler((uint32_t)prescaler);
}

/**
  * @brief  Set the APB1 clock (PCLK1) divider
  * @param prescaler  Prescaler value
  */
void HAL_RCC_SetPCLK1Prescaler(hal_rcc_pclk_prescaler_t prescaler)
{
  ASSERT_DBG_PARAM(IS_RCC_PCLK(prescaler));

  LL_RCC_SetAPB1Prescaler(((uint32_t)prescaler) << RCC_APBCFGR_PPRE1_Pos);
}

/**
  * @brief  Set the APB2 clock (PCLK2) divider
  * @param prescaler  Prescaler value
  */
void HAL_RCC_SetPCLK2Prescaler(hal_rcc_pclk_prescaler_t prescaler)
{
  ASSERT_DBG_PARAM(IS_RCC_PCLK(prescaler));

  LL_RCC_SetAPB2Prescaler(((uint32_t)prescaler) << RCC_APBCFGR_PPRE2_Pos);
}

/**
  * @brief  Set the APB4 clock (PCLK4) divider
  * @param prescaler  Prescaler value
  */
void HAL_RCC_SetPCLK4Prescaler(hal_rcc_pclk_prescaler_t prescaler)
{
  ASSERT_DBG_PARAM(IS_RCC_PCLK(prescaler));

  LL_RCC_SetAPB4Prescaler(((uint32_t)prescaler) << RCC_APBCFGR_PPRE4_Pos);
}

/**
  * @brief  Get the AHB bus clock prescaler (HCLK).
  * @retval hal_rcc_hclk_prescaler_t Prescaler value
  */
hal_rcc_hclk_prescaler_t HAL_RCC_GetHCLKPrescaler(void)
{
  return (hal_rcc_hclk_prescaler_t)LL_RCC_GetAHBPrescaler();
}

/**
  * @brief  Set the APB1 bus clock prescaler (PCLK1).
  * @retval hal_rcc_pclk_prescaler_t Prescaler value
  */
hal_rcc_pclk_prescaler_t HAL_RCC_GetPCLK1Prescaler(void)
{
  return (hal_rcc_pclk_prescaler_t)(uint32_t)(LL_RCC_GetAPB1Prescaler() >> RCC_APBCFGR_PPRE1_Pos);
}

/**
  * @brief  Set the APB2 bus clock prescaler (PCLK2).
  * @retval hal_rcc_pclk_prescaler_t Prescaler value
  */
hal_rcc_pclk_prescaler_t HAL_RCC_GetPCLK2Prescaler(void)
{
  return (hal_rcc_pclk_prescaler_t)(uint32_t)(LL_RCC_GetAPB2Prescaler() >> RCC_APBCFGR_PPRE2_Pos);
}

/**
  * @brief  Set the APB4 bus clock prescaler (PCLK4).
  * @retval hal_rcc_pclk_prescaler_t Prescaler value
  */
hal_rcc_pclk_prescaler_t HAL_RCC_GetPCLK4Prescaler(void)
{
  return (hal_rcc_pclk_prescaler_t)(uint32_t)(LL_RCC_GetAPB4Prescaler() >> RCC_APBCFGR_PPRE4_Pos);
}

/**
  * @brief  Configure the bus dividers
  * @param  p_config Pointer based on @ref hal_rcc_bus_clk_config_t structure
  * @note   SystemCoreClock and Systick are updated in this function.
  * @warning FLASH latency must be adjusted according to the targeted system clock
  *          frequency and voltage scaling.
  * @retval HAL_OK            Success
  * @retval HAL_ERROR         Issue to reconfigure the System tick
  * @retval HAL_INVALID_PARAM Input parameter not valid (USE_HAL_CHECK_PARAM enabled)
  */
hal_status_t HAL_RCC_SetBusClockConfig(const hal_rcc_bus_clk_config_t *p_config)
{
  ASSERT_DBG_PARAM(p_config != (void *)NULL);
#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (p_config == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */
  ASSERT_DBG_PARAM(IS_RCC_SYSCPUCLK(p_config->sys_cpu_clk_prescaler));
  ASSERT_DBG_PARAM(IS_RCC_HCLK(p_config->hclk_prescaler));
  ASSERT_DBG_PARAM(IS_RCC_PCLK(p_config->pclk1_prescaler));
  ASSERT_DBG_PARAM(IS_RCC_PCLK(p_config->pclk2_prescaler));
  ASSERT_DBG_PARAM(IS_RCC_PCLK(p_config->pclk4_prescaler));

  /* Configure prescalers for the available Bus */
  LL_RCC_SetSysPrescaler((uint32_t)p_config->sys_cpu_clk_prescaler);

  LL_RCC_ConfigBusClock((uint32_t)p_config->hclk_prescaler,
                        ((uint32_t)p_config->pclk1_prescaler |
                         (uint32_t)((uint32_t)p_config->pclk2_prescaler << (RCC_APBCFGR_PPRE2_Pos)) |
                         (uint32_t)((uint32_t)p_config->pclk4_prescaler << (RCC_APBCFGR_PPRE4_Pos))));

  RCC_UPDATE_SYSTEMCORECLOCK();

  /* Configure the source of time base considering new system clocks settings*/
  return HAL_InitTick(uwTickFreq, uwTickPrio);
}

/**
  * @brief Retrieve the bus dividers
  * @param p_config Pointer on @ref hal_rcc_bus_clk_config_t structure
  */
void HAL_RCC_GetBusClockConfig(hal_rcc_bus_clk_config_t *p_config)
{
  ASSERT_DBG_PARAM(p_config != (void *)NULL);

  /* Get Bus prescalers */
  p_config->sys_cpu_clk_prescaler = (hal_rcc_sys_cpu_clk_prescaler_t)LL_RCC_GetSysPrescaler();
  p_config->hclk_prescaler = (hal_rcc_hclk_prescaler_t)LL_RCC_GetAHBPrescaler();
  p_config->pclk1_prescaler = (hal_rcc_pclk_prescaler_t)(uint32_t)(LL_RCC_GetAPB1Prescaler() >> RCC_APBCFGR_PPRE1_Pos);
  p_config->pclk2_prescaler = (hal_rcc_pclk_prescaler_t)(uint32_t)(LL_RCC_GetAPB2Prescaler() >> RCC_APBCFGR_PPRE2_Pos);
  p_config->pclk4_prescaler = (hal_rcc_pclk_prescaler_t)(uint32_t)(LL_RCC_GetAPB4Prescaler() >> RCC_APBCFGR_PPRE4_Pos);
}

/**
  * @brief   Return the SYSCLK frequency.
  * @note    The system frequency computed by this function is not the real
  *          frequency in the chip. It is calculated based on the predefined
  *          constant and the selected clock source.
  * @note    If SYSCLK source is HSI, function returns values based on HSI_VALUE.
  * @note    If SYSCLK source is CSI, function returns values based on CSI_VALUE.
  * @note    If SYSCLK source is HSE, function returns values based on HSE_VALUE.
  * @note    If SYSCLK source is PLL1, function returns values based on HSI_VALUE, \
  *          CSI_VALUE and HSE_VALUE multiplied/divided by the PLL factors.
  * @note    This function can be used by the user application to compute the baudrate for the communication
  *          peripherals or configure other parameters.
  * @warning Each time SYSCLK changes, this function must be called to update the right SYSCLK value.
  *          Otherwise, any configuration based on this function will be incorrect.
  * @retval  uint32_t SYSCLK frequency in Hz
  */
uint32_t HAL_RCC_GetSYSCLKFreq(void)
{
  uint32_t sysclockfreq;
  uint32_t sysclk_source;

  sysclk_source = LL_RCC_GetSysClkSource();

  if (sysclk_source == LL_RCC_SYS_CLKSOURCE_STATUS_HSI)
  {
    /* HSI used as system clock source */
    sysclockfreq = RCC_HSI_GetCkFreq();
  }

  else if (sysclk_source == LL_RCC_SYS_CLKSOURCE_STATUS_CSI)
  {
    /* CSI used as system clock source */
    sysclockfreq = CSI_VALUE;
  }
#if defined(HSE_VALUE)

  else if (sysclk_source == LL_RCC_SYS_CLKSOURCE_STATUS_HSE)
  {
    /* HSE used as system clock source */
    sysclockfreq = HSE_VALUE;
  }
#endif /* HSE_VALUE */

  else
  {
    /* PLL1 used as system clock source */
    hal_rcc_pll_output_freq_t pll_freq;
    HAL_RCC_PLL1_GetClockFreq(&pll_freq);
    sysclockfreq = pll_freq.pll_p_freq;
  }
  sysclockfreq = sysclockfreq >> CPUPrescTable[LL_RCC_GetSysPrescaler()];

  return sysclockfreq;
}

/**
  * @brief  Return the HCLK frequency.
  * @warning Each time HCLK changes, this function must be called to update the
  *          right HCLK value. Otherwise, any configuration based on this function will be incorrect.
  * @note   The SystemCoreClock CMSIS variable is used to store System Clock Frequency.
  * @retval uint32_t HCLK frequency in Hz
  */
uint32_t HAL_RCC_GetHCLKFreq(void)
{
  RCC_UPDATE_SYSTEMCORECLOCK();
  return (SystemCoreClock >> AHBPrescTable[LL_RCC_GetAHBPrescaler()]);
}

/**
  * @brief  Return the PCLK1 frequency.
  * @warning Each time PCLK1 changes, this function must be called to update the
  *          right PCLK1 value. Otherwise, any configuration based on this function will be incorrect.
  * @retval uint32_t PCLK1 frequency in Hz
  */
uint32_t HAL_RCC_GetPCLK1Freq(void)
{
  /* Get HCLK source and Compute PCLK1 frequency */
  return (HAL_RCC_GetHCLKFreq() >> APBPrescTable[LL_RCC_GetAPB1Prescaler() >> RCC_APBCFGR_PPRE1_Pos]);
}

/**
  * @brief  Return the PCLK2 frequency.
  * @warning Each time PCLK2 changes, this function must be called to update the
  *          right PCLK2 value. Otherwise, any configuration based on this function will be incorrect.
  * @retval uint32_t PCLK2 frequency in Hz
  */
uint32_t HAL_RCC_GetPCLK2Freq(void)
{
  /* Get HCLK source and Compute PCLK2 frequency */
  return (HAL_RCC_GetHCLKFreq() >> APBPrescTable[LL_RCC_GetAPB2Prescaler() >> RCC_APBCFGR_PPRE2_Pos]);
}

/**
  * @brief  Return the PCLK4 frequency.
  * @warning Each time PCLK4 changes, this function must be called to update the
  *          right PCLK4 value. Otherwise, any configuration based on this function will be incorrect.
  * @retval uint32_t PCLK4 frequency in Hz
  */
uint32_t HAL_RCC_GetPCLK4Freq(void)
{
  /* Get HCLK source and Compute PCLK4 frequency */
  return (HAL_RCC_GetHCLKFreq() >> APBPrescTable[LL_RCC_GetAPB4Prescaler() >> RCC_APBCFGR_PPRE4_Pos]);
}

/**
  * @brief  Return the SysTick clock frequency.
  * @retval uint32_t  SysTick frequency in Hz
  * @note   This function returns the RCC systick clock frequency. Depending on the cortex systick clock source
  *         selection, the systick core frequency is equal to this frequency or to the system frequency.
  */
uint32_t HAL_RCC_GetSysTickExternalClkFreq(void)
{
  return (HAL_RCC_GetSYSCLKFreq() >> 3);
}

/**
  * @}
  */ /* End of RCC_Exported_Functions_Group1_2 */


/** @addtogroup RCC_Exported_Functions_Group1_31
  * @{
  */

/**
  * @brief   Configure PLL1 without enabling outputs.
  * @details The config function will perform the following actions:
  *           - Check in PLL1 is well deactivated (if enabled exit from this function)
  *           - Configure the PLL1 with full list of parameters
  * @param p_config pointer to a @ref hal_rcc_pll_config_t structure that
  *          contains the configuration information for the PLL1
  * @retval HAL_OK            PLL1 has been correctly configured
  * @retval HAL_INVALID_PARAM Input parameter not valid (USE_HAL_CHECK_PARAM enabled)
  * @retval HAL_ERROR         PLL1 is already enabled and can not be modified.
  */
hal_status_t HAL_RCC_PLL1_SetConfig(const hal_rcc_pll_config_t *p_config)
{
  ASSERT_DBG_PARAM(p_config != (void *)NULL);
#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (p_config == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */
  ASSERT_DBG_PARAM(IS_RCC_PLL_SRC(p_config->pll_source));
  ASSERT_DBG_PARAM(IS_RCC_PLLM_VALUE(p_config->pll_m));
  ASSERT_DBG_PARAM(IS_RCC_PLLN_VALUE(p_config->pll_n));

  ASSERT_DBG_PARAM(IS_RCC_PLL_SSCG_STATUS(p_config->pll_sscg_status));
  if ((p_config->pll_sscg_status) == HAL_RCC_PLL_SSCG_DISABLE)
  {
    ASSERT_DBG_PARAM(IS_RCC_PLL_FRACN_VALUE(p_config->pll_fracn));
  }
  else if ((p_config->pll_sscg_status) == HAL_RCC_PLL_SSCG_ENABLE)
  {
    ASSERT_DBG_PARAM(IS_RCC_PLL_SSCG_MOD_PER_VALUE(p_config->pll_sscg_config.mod_period));
    ASSERT_DBG_PARAM(IS_RCC_PLL_SSCG_MOD_DEPTH_ADJ_VALUE(p_config->pll_sscg_config.mod_depth_adj));
    ASSERT_DBG_PARAM(IS_RCC_PLL_SSCG_MOD_SPREAD_VALUE(p_config->pll_sscg_config.mod_spread));
    ASSERT_DBG_PARAM(IS_RCC_PLL_SSCG_DITH_CTRL_VALUE(p_config->pll_sscg_config.dith_control));
  }

  ASSERT_DBG_PARAM(IS_RCC_PLLP_VALUE(p_config->pll_p));
  ASSERT_DBG_PARAM(IS_RCC_PLLQ_VALUE(p_config->pll_q));
  ASSERT_DBG_PARAM(IS_RCC_PLLS_VALUE(p_config->pll_s));

  return RCC_PLL_SetConfig(PLL_1, p_config);
}

/**
  * @brief   Configure PLL1 FracN on-the-fly
  * @param   fracn, new fracn value to be set
  * @retval HAL_OK     PLL1 FracN has been correctly configured
  * @retval HAL_ERROR  PLL1 is not in fractional mode
  */
hal_status_t HAL_RCC_PLL1_SetFractional(uint32_t fracn)
{
  hal_status_t status = HAL_ERROR;

  if (LL_RCC_PLL1_GetFRACN() != 0U)
  {
    ASSERT_DBG_PARAM(IS_RCC_PLL_FRACN_VALUE(fracn));

    LL_RCC_PLL1FRACN_Disable();
    LL_RCC_PLL1_SetFRACN(fracn);
    LL_RCC_PLL1FRACN_Enable();
    status = HAL_OK;
  }

  return status;
}

/**
  * @brief Enable output(s) of PLL1.
  * @param output Output to enable for PLL1
  *               It can be a combination of the following values:
  *                 @arg @ref HAL_RCC_PLL1_OUTPUT_P or @ref HAL_RCC_PLL1_SYSCLK   XXX
  *                 @arg @ref HAL_RCC_PLL1_OUTPUT_Q or @ref HAL_RCC_PLL1_SYSCLK   XXX
  *                 @arg @ref HAL_RCC_PLL1_OUTPUT_S or @ref HAL_RCC_PLL1_SYSCLK   XXX
  *                 @arg @ref HAL_RCC_PLL1_OUTPUT_ALL
  * @retval HAL_OK    Output(s) has been activated
  */
hal_status_t HAL_RCC_PLL1_EnableOutput(uint32_t output)
{
  ASSERT_DBG_PARAM(IS_RCC_PLL1_OUTPUT(output));

  LL_RCC_PLL1_EnableOutput(output);

  return HAL_OK;
}

/**
  * @brief  Disable output(s) of PLL1.
  * @param  output Output to disable for PLL1
  *                It can be a combination of the following values:
  *                 @arg @ref HAL_RCC_PLL1_OUTPUT_P
  *                 @arg @ref HAL_RCC_PLL1_OUTPUT_Q
  *                 @arg @ref HAL_RCC_PLL1_OUTPUT_S
  *                 @arg @ref HAL_RCC_PLL1_OUTPUT_ALL
  * @retval HAL_OK    Output(s) has been deactivated
  * @retval HAL_ERROR Output is used as system clock and cannot be deactivated
  */
hal_status_t HAL_RCC_PLL1_DisableOutput(uint32_t output)
{
  hal_rcc_sysclk_src_t src_clk;
  hal_status_t status = HAL_ERROR;
  ASSERT_DBG_PARAM(IS_RCC_PLL1_OUTPUT(output));
  /*
    - If output is used as system clock => return an error
    - else disable output(s) of the PLL1
  */

  src_clk = HAL_RCC_GetSYSCLKSource();
  if ((src_clk != HAL_RCC_SYSCLK_SRC_PLLCLK)
      || ((src_clk == HAL_RCC_SYSCLK_SRC_PLLCLK)
          && ((output & HAL_RCC_PLL1_OUTPUT_P) != HAL_RCC_PLL1_OUTPUT_P)))
  {
    LL_RCC_PLL1_DisableOutput(output);
    status = HAL_OK;
  }

  return status;
}

/**
  * @brief  Enable PLL1.
  * @note   If PLL is not enabled, enable it and wait for RDY state.
  * @retval HAL_OK    PLL1 correctly enabled or already enabled.
  * @retval HAL_ERROR Timeout detected during enabling of the PLL1
  */
hal_status_t HAL_RCC_PLL1_Enable(void)
{
  hal_status_t status = HAL_OK;
  /* If PLL not enabled => enable it and wait for RDY state (error only if pb to enable) */
  if (LL_RCC_PLL1_IsReady() == 0U)
  {
    LL_RCC_PLL1_Enable();
    status = RCC_WaitForTimeout(LL_RCC_PLL1_IsReady, RCC_PLL1_TIMEOUT_VALUE, 1U);
  }

  return status;
}

/**
  * @brief   Disable PLL1.
  * @details PLL1 cannot be disabled if used as system level
  *           - If PLL1 Output is as used as system level => return an error
  *           - If PLL1 enabled => disable PLL1 and wait for deactivation (error only if pb to disable)
  * @retval HAL_OK    PLL1 correctly deactivated or already deactivated.
  * @retval HAL_ERROR PLL1 is used as system level and cannot be deactivated\n
  *                   Timeout detected during disabling of the PLL1
  */
hal_status_t HAL_RCC_PLL1_Disable(void)
{
  hal_status_t status = HAL_ERROR;
  /*
    - If PLL1 is as used as system level => return an error
    - Else disable PLL1 and wait for deactivation (error only if pb to disable)
  */
  if (HAL_RCC_GetSYSCLKSource() != HAL_RCC_SYSCLK_SRC_PLLCLK)
  {
    LL_RCC_PLL1_Disable();
    status = RCC_WaitForTimeout(LL_RCC_PLL1_IsReady, RCC_PLL1_TIMEOUT_VALUE, 0U);
  }
  return status;
}

/**
  * @brief    Disable PLL1 for power consumption perspective.
  * @warning  To enable again PLL1, a new configuration must be applied.
  * @details  This function resets all the parameters which might impact power like divm, outputs...
  * @note     As the source is shared with other PLLs, it is not reset
  * @retval HAL_OK    PLL1 is correctly disabled\n
  * @retval HAL_ERROR Output is used as system level and cannot be disabled\n
  *                   Timeout to disable PLL1
  */
hal_status_t HAL_RCC_PLL1_Reset(void)
{
  hal_status_t status = HAL_ERROR;

  if (HAL_RCC_GetSYSCLKSource() != HAL_RCC_SYSCLK_SRC_PLLCLK)
  {
    LL_RCC_PLL1_Disable();
    if (RCC_WaitForTimeout(LL_RCC_PLL1_IsReady, RCC_PLL1_TIMEOUT_VALUE, 0U) == HAL_OK)
    {
      /* To save power disable the PLL1 Source, FRACN and Clock outputs */
      STM32_CLEAR_BIT(RCC->PLLCFGR, RCC_PLLCFGR_PLL1PEN | RCC_PLLCFGR_PLL1QEN | RCC_PLLCFGR_PLL1SEN
                      | RCC_PLLCFGR_PLL1SSCGEN | RCC_PLLCFGR_PLL1FRACEN);
      status = HAL_OK;
    }
  }
  return status;
}

/**
  * @brief Return the configuration of PLL1.
  * @param p_config  pointer to a @ref hal_rcc_pll_config_t structure that
  *          contains the configuration information for the PLL1
  */
void HAL_RCC_PLL1_GetConfig(hal_rcc_pll_config_t *p_config)
{
  ASSERT_DBG_PARAM(p_config != (void *)NULL);

  RCC_PLL_GetConfig(PLL_1, p_config);
}

/**
  * @brief  Return the enabled output(s) of PLL1.
  * @retval output PLL1 outputs.
  *         It can be a combination of the following values:
  *            @arg @ref HAL_RCC_PLL1_OUTPUT_P or @ref HAL_RCC_PLL1_SYSCLK   XXX
  *            @arg @ref HAL_RCC_PLL1_OUTPUT_Q or @ref HAL_RCC_PLL1_SYSCLK   XXX
  *            @arg @ref HAL_RCC_PLL1_OUTPUT_S or @ref HAL_RCC_PLL1_SYSCLK   XXX
  */
uint32_t HAL_RCC_PLL1_GetOutput(void)
{
  return LL_RCC_PLL1_GetOutput();
}

/**
  * @brief Check if the PLL1 is ready.
  * @retval HAL_RCC_PLL_ENABLED  PLL1 is ready
  * @retval HAL_RCC_PLL_DISABLED PLL1 is not ready
  */
hal_rcc_pll_status_t HAL_RCC_PLL1_IsReady(void)
{
  return (hal_rcc_pll_status_t)LL_RCC_PLL1_IsReady();
}

/**
  * @brief  Returns the PLL1 clock frequencies: pll_p_freq, pll_q_freq and pll_r_freq
  * @param  p_clk Contains the frequency for each PLL1 output (in Hz).
  * @note   The PLL1 clock frequencies computed by this function is not the real
  *         frequency in the chip. It is calculated based on the predefined
  *         constant and the selected clock source.
  * @note   The function returns values based on HSE_VALUE, HSI_VALUE or MSI Value multiplied/divided by the PLL
  *         factors.
  * @note   This function can be used by the user application to compute the
  *         baud-rate for the communication peripherals or configure other parameters.
  * @warning Each time PLL1CLK changes, this function must be called to update the
  *          right PLL1CLK value. Otherwise, any configuration based on this function will be incorrect.
  */
void HAL_RCC_PLL1_GetClockFreq(hal_rcc_pll_output_freq_t *p_clk)
{
  ASSERT_DBG_PARAM(p_clk != (void *)NULL);

  p_clk->pll_p_freq = 0U;
  p_clk->pll_q_freq = 0U;
  p_clk->pll_r_freq = 0U;
  p_clk->pll_s_freq = 0U;
  p_clk->pll_t_freq = 0U;

  /* If PLL1 is not ready, return directly all the outputs frequencies set at 0 */
  if (LL_RCC_PLL1_IsReady() == 0U)
  {
    return;
  }

  RCC_PLL_GetClockFreq(PLL_1, p_clk);
}

/**
  * @}
  */ /* End of RCC_Exported_Functions_Group1_31 */


/** @addtogroup RCC_Exported_Functions_Group1_32
  * @{
  */

/**
  * @brief   Configure PLL2 without enabling outputs.
  * @details The config function will perform the following actions:
  *           - Check in PLL2 is well deactivated (if enabled exit from this function)
  *           - Configure the PLL2 with full list of parameters
  * @param p_config pointer to a @ref hal_rcc_pll_config_t structure that
  *          contains the configuration information for the PLL2
  * @retval HAL_OK            PLL2 has been correctly configured
  * @retval HAL_INVALID_PARAM Input parameter not valid (USE_HAL_CHECK_PARAM enabled)
  * @retval HAL_ERROR         PLL2 is already enabled and can not be modified.
  */
hal_status_t HAL_RCC_PLL2_SetConfig(const hal_rcc_pll_config_t *p_config)
{
  ASSERT_DBG_PARAM(p_config != (void *)NULL);
#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (p_config == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */
  ASSERT_DBG_PARAM(IS_RCC_PLL_SRC(p_config->pll_source));
  ASSERT_DBG_PARAM(IS_RCC_PLLM_VALUE(p_config->pll_m));
  ASSERT_DBG_PARAM(IS_RCC_PLLN_VALUE(p_config->pll_n));

  ASSERT_DBG_PARAM(IS_RCC_PLL_SSCG_STATUS(p_config->pll_sscg_status));
  if ((p_config->pll_sscg_status) == HAL_RCC_PLL_SSCG_DISABLE)
  {
    ASSERT_DBG_PARAM(IS_RCC_PLL_FRACN_VALUE(p_config->pll_fracn));
  }
  else  if ((p_config->pll_sscg_status) == HAL_RCC_PLL_SSCG_ENABLE)
  {
    ASSERT_DBG_PARAM(IS_RCC_PLL_SSCG_MOD_PER_VALUE(p_config->pll_sscg_config.mod_period));
    ASSERT_DBG_PARAM(IS_RCC_PLL_SSCG_MOD_DEPTH_ADJ_VALUE(p_config->pll_sscg_config.mod_depth_adj));
    ASSERT_DBG_PARAM(IS_RCC_PLL_SSCG_MOD_SPREAD_VALUE(p_config->pll_sscg_config.mod_spread));
    ASSERT_DBG_PARAM(IS_RCC_PLL_SSCG_DITH_CTRL_VALUE(p_config->pll_sscg_config.dith_control));
  }

  ASSERT_DBG_PARAM(IS_RCC_PLLP_VALUE(p_config->pll_p));
  ASSERT_DBG_PARAM(IS_RCC_PLLQ_VALUE(p_config->pll_q));
  ASSERT_DBG_PARAM(IS_RCC_PLLR_VALUE(p_config->pll_r));
  ASSERT_DBG_PARAM(IS_RCC_PLLS_VALUE(p_config->pll_s));
  ASSERT_DBG_PARAM(IS_RCC_PLLT_VALUE(p_config->pll_t));

  return RCC_PLL_SetConfig(PLL_2, p_config);
}

/**
  * @brief   Configure PLL2 FracN on-the-fly
  * @param   fracn, new fracn value to be set
  * @retval HAL_OK     PLL2 FracN has been correctly configured
  * @retval HAL_ERROR  PLL2 is not in fractional mode
  */
hal_status_t HAL_RCC_PLL2_SetFractional(uint32_t fracn)
{
  hal_status_t status = HAL_ERROR;

  if (LL_RCC_PLL2_GetFRACN() != 0U)
  {
    ASSERT_DBG_PARAM(IS_RCC_PLL_FRACN_VALUE(fracn));

    LL_RCC_PLL2FRACN_Disable();
    LL_RCC_PLL2_SetFRACN(fracn);
    LL_RCC_PLL2FRACN_Enable();
    status = HAL_OK;
  }

  return status;
}

/**
  * @brief Enable output(s) of PLL2.
  * @param output Output to enable for PLL2
  *               It can be a combination of the following values:
  *                 @arg @ref HAL_RCC_PLL2_OUTPUT_P or @ref HAL_RCC_PLL2_SYSCLK   XXX
  *                 @arg @ref HAL_RCC_PLL2_OUTPUT_Q or @ref HAL_RCC_PLL2_SYSCLK   XXX
  *                 @arg @ref HAL_RCC_PLL2_OUTPUT_R or @ref HAL_RCC_PLL2_SYSCLK   XXX
  *                 @arg @ref HAL_RCC_PLL2_OUTPUT_S or @ref HAL_RCC_PLL2_SYSCLK   XXX
  *                 @arg @ref HAL_RCC_PLL2_OUTPUT_T or @ref HAL_RCC_PLL2_SYSCLK   XXX
  *                 @arg @ref HAL_RCC_PLL2_OUTPUT_ALL
  * @retval HAL_OK    Output(s) has been activated
  */
hal_status_t HAL_RCC_PLL2_EnableOutput(uint32_t output)
{
  ASSERT_DBG_PARAM(IS_RCC_PLL2_OUTPUT(output));

  LL_RCC_PLL2_EnableOutput(output);

  return HAL_OK;
}

/**
  * @brief  Disable output(s) of PLL2.
  * @param  output Output to disable for PLL2
  *                It can be a combination of the following values:
  *                 @arg @ref HAL_RCC_PLL2_OUTPUT_P or @ref HAL_RCC_PLL2_SYSCLK   XXX
  *                 @arg @ref HAL_RCC_PLL2_OUTPUT_Q or @ref HAL_RCC_PLL2_SYSCLK   XXX
  *                 @arg @ref HAL_RCC_PLL2_OUTPUT_R or @ref HAL_RCC_PLL2_SYSCLK   XXX
  *                 @arg @ref HAL_RCC_PLL2_OUTPUT_S or @ref HAL_RCC_PLL2_SYSCLK   XXX
  *                 @arg @ref HAL_RCC_PLL2_OUTPUT_T or @ref HAL_RCC_PLL2_SYSCLK   XXX
  *                 @arg @ref HAL_RCC_PLL2_OUTPUT_ALL
  * @retval HAL_OK    Output(s) has been deactivated
  * @retval HAL_ERROR Output is used as system clock and cannot be deactivated
  */
hal_status_t HAL_RCC_PLL2_DisableOutput(uint32_t output)
{
  ASSERT_DBG_PARAM(IS_RCC_PLL2_OUTPUT(output));

  LL_RCC_PLL2_DisableOutput(output);

  return HAL_OK;
}

/**
  * @brief  Enable PLL2.
  * @note   If PLL is not enabled, enable it and wait for RDY state.
  * @retval HAL_OK    PLL2 correctly enabled or already enabled.
  * @retval HAL_ERROR Timeout detected during enabling of the PLL2
  */
hal_status_t HAL_RCC_PLL2_Enable(void)
{
  hal_status_t status = HAL_OK;
  /* If PLL not enabled => enable it and wait for RDY state (error only if pb to enable) */
  if (LL_RCC_PLL2_IsReady() == 0U)
  {
    LL_RCC_PLL2_Enable();
    status = RCC_WaitForTimeout(LL_RCC_PLL2_IsReady, RCC_PLL2_TIMEOUT_VALUE, 1U);
  }

  return status;
}

/**
  * @brief   Disable PLL2.
  * @details PLL2 cannot be disabled if used as system level
  *           - If PLL2 Output is as used as system level => return an error
  *           - If PLL2 enabled => disable PLL2 and wait for deactivation (error only if pb to disable)
  * @retval HAL_OK    PLL2 correctly deactivated or already deactivated.
  * @retval HAL_ERROR PLL2 is used as system level and cannot be deactivated\n
  *                   Timeout detected during disabling of the PLL2
  */
hal_status_t HAL_RCC_PLL2_Disable(void)
{
  /* Before Disabling PLL, it is recommended to disable all PLL outputs */
  LL_RCC_PLL2_DisableOutput((uint32_t) HAL_RCC_PLL2_OUTPUT_ALL);

  LL_RCC_PLL2_Disable();

  return RCC_WaitForTimeout(LL_RCC_PLL2_IsReady, RCC_PLL2_TIMEOUT_VALUE, 0U);
}

/**
  * @brief    Disable PLL2 for power consumption perspective.
  * @warning  To enable again PLL2, a new configuration must be applied.
  * @details  This function allow to reset all the parameters which might impact power
  *           like PLLSRC, outputs...
  * @retval HAL_OK    PLL2 is correctly disabled\n
  * @retval HAL_ERROR Output is used as system level and cannot be disabled\n
  *                   Timeout to disable PLL2
  */
hal_status_t HAL_RCC_PLL2_Reset(void)
{
  hal_status_t status = HAL_ERROR;

  LL_RCC_PLL2_Disable();
  if (RCC_WaitForTimeout(LL_RCC_PLL2_IsReady, RCC_PLL2_TIMEOUT_VALUE, 0U) == HAL_OK)
  {
    /* To save power disable the PLL1 Source, FRACN and Clock outputs */
    STM32_CLEAR_BIT(RCC->PLLCFGR, RCC_PLLCFGR_PLL2PEN | RCC_PLLCFGR_PLL2QEN | RCC_PLLCFGR_PLL2REN |
                    RCC_PLLCFGR_PLL2SEN | RCC_PLLCFGR_PLL2TEN | RCC_PLLCFGR_PLL2SSCGEN |
                    RCC_PLLCFGR_PLL2FRACLEN);
    status = HAL_OK;
  }

  return status;
}

/**
  * @brief Return the configuration of PLL2.
  * @param p_config  pointer to a @ref hal_rcc_pll_config_t structure that
  *          contains the configuration information for the PLL2
  */
void HAL_RCC_PLL2_GetConfig(hal_rcc_pll_config_t *p_config)
{
  ASSERT_DBG_PARAM(p_config != (void *)NULL);

  RCC_PLL_GetConfig(PLL_2, p_config);
}

/**
  * @brief  Return the enabled output(s) of PLL2.
  * @retval output PLL2 outputs.
  *         It can be a combination of the following values:
  *            @arg @ref HAL_RCC_PLL2_OUTPUT_P or @ref HAL_RCC_PLL2_SYSCLK   XXX
  *            @arg @ref HAL_RCC_PLL2_OUTPUT_Q or @ref HAL_RCC_PLL2_SYSCLK   XXX
  *            @arg @ref HAL_RCC_PLL2_OUTPUT_R or @ref HAL_RCC_PLL2_SYSCLK   XXX
  *            @arg @ref HAL_RCC_PLL2_OUTPUT_S or @ref HAL_RCC_PLL2_SYSCLK   XXX
  *            @arg @ref HAL_RCC_PLL2_OUTPUT_T or @ref HAL_RCC_PLL2_SYSCLK   XXX
  */
uint32_t HAL_RCC_PLL2_GetOutput(void)
{
  return LL_RCC_PLL2_GetOutput();
}

/**
  * @brief Check if the PLL2 is ready.
  * @retval HAL_RCC_PLL_ENABLED  PLL2 is ready
  * @retval HAL_RCC_PLL_DISABLED PLL2 is not ready
  */
hal_rcc_pll_status_t HAL_RCC_PLL2_IsReady(void)
{
  return (hal_rcc_pll_status_t)LL_RCC_PLL2_IsReady();
}

/**
  * @brief  Returns the PLL2 clock frequencies: pll_p_freq, pll_q_freq and pll_r_freq
  * @param  p_clk Contains the frequency for each PLL2 output (in Hz).
  * @note   The PLL2 clock frequencies computed by this function is not the real
  *         frequency in the chip. It is calculated based on the predefined
  *         constant and the selected clock source.
  * @note   The function returns values based on HSE_VALUE, HSI_VALUE or MSI Value multiplied/divided by the PLL
  *         factors.
  * @note   This function can be used by the user application to compute the
  *         baud-rate for the communication peripherals or configure other parameters.
  * @warning Each time PLL2CLK changes, this function must be called to update the
  *          right PLL2CLK value. Otherwise, any configuration based on this function will be incorrect.
  */
void HAL_RCC_PLL2_GetClockFreq(hal_rcc_pll_output_freq_t *p_clk)
{
  ASSERT_DBG_PARAM(p_clk != (void *)NULL);

  p_clk->pll_p_freq = 0U;
  p_clk->pll_q_freq = 0U;
  p_clk->pll_r_freq = 0U;
  p_clk->pll_s_freq = 0U;
  p_clk->pll_t_freq = 0U;

  /* If PLL2 is not ready, return directly all the outputs frequencies set at 0 */
  if (LL_RCC_PLL2_IsReady() == 0U)
  {
    return;
  }

  RCC_PLL_GetClockFreq(PLL_2, p_clk);
}

/**
  * @}
  */ /* RCC_Exported_Functions_Group1_3XXX */

/** @addtogroup RCC_Exported_Functions_Group1_3XXX
  * @{
  */

/**
  * @brief   Configure PLL3 without enabling outputs.
  * @details The config function will perform the following actions:
  *           - Check in PLL3 is well deactivated (if enabled exit from this function)
  *           - Configure the PLL3 with full list of parameters
  * @param p_config pointer to a @ref hal_rcc_pll_config_t structure that
  *          contains the configuration information for the PLL3
  * @retval HAL_OK            PLL3 has been correctly configured
  * @retval HAL_INVALID_PARAM Input parameter not valid (USE_HAL_CHECK_PARAM enabled)
  * @retval HAL_ERROR         PLL3 is already enabled and can not be modified.
  */
hal_status_t HAL_RCC_PLL3_SetConfig(const hal_rcc_pll_config_t *p_config)
{
  ASSERT_DBG_PARAM(p_config != (void *)NULL);
#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (p_config == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */
  ASSERT_DBG_PARAM(IS_RCC_PLL_SRC(p_config->pll_source));
  ASSERT_DBG_PARAM(IS_RCC_PLLM_VALUE(p_config->pll_m));
  ASSERT_DBG_PARAM(IS_RCC_PLLN_VALUE(p_config->pll_n));

  ASSERT_DBG_PARAM(IS_RCC_PLL_SSCG_STATUS(p_config->pll_sscg_status));
  if ((p_config->pll_sscg_status) == HAL_RCC_PLL_SSCG_DISABLE)
  {
    ASSERT_DBG_PARAM(IS_RCC_PLL_FRACN_VALUE(p_config->pll_fracn));
  }
  else if ((p_config->pll_sscg_status) == HAL_RCC_PLL_SSCG_ENABLE)
  {
    ASSERT_DBG_PARAM(IS_RCC_PLL_SSCG_MOD_PER_VALUE(p_config->pll_sscg_config.mod_period));
    ASSERT_DBG_PARAM(IS_RCC_PLL_SSCG_MOD_DEPTH_ADJ_VALUE(p_config->pll_sscg_config.mod_depth_adj));
    ASSERT_DBG_PARAM(IS_RCC_PLL_SSCG_MOD_SPREAD_VALUE(p_config->pll_sscg_config.mod_spread));
    ASSERT_DBG_PARAM(IS_RCC_PLL_SSCG_DITH_CTRL_VALUE(p_config->pll_sscg_config.dith_control));
  }

  ASSERT_DBG_PARAM(IS_RCC_PLLP_VALUE(p_config->pll_p));
  ASSERT_DBG_PARAM(IS_RCC_PLLQ_VALUE(p_config->pll_q));
  ASSERT_DBG_PARAM(IS_RCC_PLLR_VALUE(p_config->pll_r));
  ASSERT_DBG_PARAM(IS_RCC_PLLS_VALUE(p_config->pll_s));

  return RCC_PLL_SetConfig(PLL_3, p_config);
}

/**
  * @brief   Configure PLL3 FracN on-the-fly
  * @param   fracn, new fracn value to be set
  * @retval HAL_OK     PLL3 FracN has been correctly configured
  * @retval HAL_ERROR  PLL3 is not in fractional mode
  */
hal_status_t HAL_RCC_PLL3_SetFractional(uint32_t fracn)
{
  hal_status_t status = HAL_ERROR;

  if (LL_RCC_PLL3_GetFRACN() != 0U)
  {
    ASSERT_DBG_PARAM(IS_RCC_PLL_FRACN_VALUE(fracn));

    LL_RCC_PLL3FRACN_Disable();
    LL_RCC_PLL3_SetFRACN(fracn);
    LL_RCC_PLL3FRACN_Enable();
    status = HAL_OK;
  }

  return status;
}

/**
  * @brief Enable output(s) of PLL3.
  * @param output Output to enable for PLL3
  *               It can be a combination of the following values:
  *                 @arg @ref HAL_RCC_PLL3_OUTPUT_P or @ref HAL_RCC_PLL3_SYSCLK   XXX
  *                 @arg @ref HAL_RCC_PLL3_OUTPUT_Q or @ref HAL_RCC_PLL3_SYSCLK   XXX
  *                 @arg @ref HAL_RCC_PLL3_OUTPUT_R or @ref HAL_RCC_PLL3_SYSCLK   XXX
  *                 @arg @ref HAL_RCC_PLL3_OUTPUT_S or @ref HAL_RCC_PLL3_SYSCLK   XXX
  *                 @arg @ref HAL_RCC_PLL3_OUTPUT_ALL
  * @retval HAL_OK    Output(s) has been activated
  */
hal_status_t HAL_RCC_PLL3_EnableOutput(uint32_t output)
{
  ASSERT_DBG_PARAM(IS_RCC_PLL3_OUTPUT(output));

  LL_RCC_PLL3_EnableOutput(output);

  return HAL_OK;
}

/**
  * @brief  Disable output(s) of PLL3.
  * @param  output Output to disable for PLL3
  *                It can be a combination of the following values:
  *                 @arg @ref HAL_RCC_PLL3_OUTPUT_P or @ref HAL_RCC_PLL3_SYSCLK   XXX
  *                 @arg @ref HAL_RCC_PLL3_OUTPUT_Q or @ref HAL_RCC_PLL3_SYSCLK   XXX
  *                 @arg @ref HAL_RCC_PLL3_OUTPUT_R or @ref HAL_RCC_PLL3_SYSCLK   XXX
  *                 @arg @ref HAL_RCC_PLL3_OUTPUT_S or @ref HAL_RCC_PLL3_SYSCLK   XXX
  *                 @arg @ref HAL_RCC_PLL3_OUTPUT_ALL
  * @retval HAL_OK    Output(s) has been deactivated
  * @retval HAL_ERROR Output is used as system clock and cannot be deactivated
  */
hal_status_t HAL_RCC_PLL3_DisableOutput(uint32_t output)
{
  ASSERT_DBG_PARAM(IS_RCC_PLL3_OUTPUT(output));

  LL_RCC_PLL3_DisableOutput(output);

  return HAL_OK;
}

/**
  * @brief  Enable PLL3.
  * @note   If PLL is not enabled, enable it and wait for RDY state.
  * @retval HAL_OK    PLL3 correctly enabled or already enabled.
  * @retval HAL_ERROR Timeout detected during enabling of the PLL3
  */
hal_status_t HAL_RCC_PLL3_Enable(void)
{
  hal_status_t status = HAL_OK;
  /* If PLL not enabled => enable it and wait for RDY state (error only if pb to enable) */
  if (LL_RCC_PLL3_IsReady() == 0U)
  {
    LL_RCC_PLL3_Enable();
    status = RCC_WaitForTimeout(LL_RCC_PLL3_IsReady, RCC_PLL3_TIMEOUT_VALUE, 1U);
  }

  return status;
}

/**
  * @brief   Disable PLL3.
  * @details PLL3 cannot be disabled if used as system level
  *           - If PLL3 Output is as used as system level => return an error
  *           - If PLL3 enabled => disable PLL3 and wait for deactivation (error only if pb to disable)
  * @retval HAL_OK    PLL3 correctly deactivated or already deactivated.
  * @retval HAL_ERROR PLL3 is used as system level and cannot be deactivated\n
  *                   Timeout detected during disabling of the PLL3
  */
hal_status_t HAL_RCC_PLL3_Disable(void)
{
  /* Before Disabling PLL, it is recommended to disable all PLL outputs */
  LL_RCC_PLL3_DisableOutput((uint32_t) HAL_RCC_PLL3_OUTPUT_ALL);

  LL_RCC_PLL3_Disable();

  return RCC_WaitForTimeout(LL_RCC_PLL3_IsReady, RCC_PLL3_TIMEOUT_VALUE, 0U);
}

/**
  * @brief    Disable PLL3 for power consumption perspective.
  * @warning  To enable again PLL3, a new configuration must be applied.
  * @details  This function allow to reset all the parameters which might impact power
  *           like PLLSRC, outputs...
  * @retval HAL_OK    PLL3 is correctly disabled\n
  * @retval HAL_ERROR Output is used as system level and cannot be disabled\n
  *                   Timeout to disable PLL3
  */
hal_status_t HAL_RCC_PLL3_Reset(void)
{
  hal_status_t status = HAL_ERROR;

  LL_RCC_PLL3_Disable();
  if (RCC_WaitForTimeout(LL_RCC_PLL3_IsReady, RCC_PLL3_TIMEOUT_VALUE, 0U) == HAL_OK)
  {
    /* To save power disable the PLL1 Source, FRACN and Clock outputs */
    STM32_CLEAR_BIT(RCC->PLLCFGR, RCC_PLLCFGR_PLL3PEN | RCC_PLLCFGR_PLL3QEN | RCC_PLLCFGR_PLL3REN |
                    RCC_PLLCFGR_PLL3SEN | RCC_PLLCFGR_PLL3SSCGEN | RCC_PLLCFGR_PLL3FRACEN);
    status = HAL_OK;
  }

  return status;
}

/**
  * @brief Return the configuration of PLL3.
  * @param p_config  pointer to a @ref hal_rcc_pll_config_t structure that
  *          contains the configuration information for the PLL3
  */
void HAL_RCC_PLL3_GetConfig(hal_rcc_pll_config_t *p_config)
{
  ASSERT_DBG_PARAM(p_config != (void *)NULL);

  RCC_PLL_GetConfig(PLL_3, p_config);
}

/**
  * @brief  Return the enabled output(s) of PLL3.
  * @retval output PLL3 outputs.
  *         It can be a combination of the following values:
  *            @arg @ref HAL_RCC_PLL3_OUTPUT_P or @ref HAL_RCC_PLL3_SYSCLK   XXX
  *            @arg @ref HAL_RCC_PLL3_OUTPUT_Q or @ref HAL_RCC_PLL3_SYSCLK   XXX
  *            @arg @ref HAL_RCC_PLL3_OUTPUT_R or @ref HAL_RCC_PLL3_SYSCLK   XXX
  *            @arg @ref HAL_RCC_PLL3_OUTPUT_S or @ref HAL_RCC_PLL3_SYSCLK   XXX
  */
uint32_t HAL_RCC_PLL3_GetOutput(void)
{
  return LL_RCC_PLL3_GetOutput();
}

/**
  * @brief Check if the PLL3 is ready.
  * @retval HAL_RCC_PLL_ENABLED  PLL3 is ready
  * @retval HAL_RCC_PLL_DISABLED PLL3 is not ready
  */
hal_rcc_pll_status_t HAL_RCC_PLL3_IsReady(void)
{
  return (hal_rcc_pll_status_t)LL_RCC_PLL3_IsReady();
}

/**
  * @brief  Returns the PLL3 clock frequencies: pll_p_freq, pll_q_freq and pll_r_freq
  * @param  p_clk Contains the frequency for each PLL3 output (in Hz).
  * @note   The PLL3 clock frequencies computed by this function is not the real
  *         frequency in the chip. It is calculated based on the predefined
  *         constant and the selected clock source.
  * @note   The function returns values based on HSE_VALUE, HSI_VALUE or MSI Value multiplied/divided by the PLL
  *         factors.
  * @note   This function can be used by the user application to compute the
  *         baud-rate for the communication peripherals or configure other parameters.
  * @warning Each time PLL3CLK changes, this function must be called to update the
  *          right PLL3CLK value. Otherwise, any configuration based on this function will be incorrect.
  */
void HAL_RCC_PLL3_GetClockFreq(hal_rcc_pll_output_freq_t *p_clk)
{
  ASSERT_DBG_PARAM(p_clk != (void *)NULL);

  p_clk->pll_p_freq = 0U;
  p_clk->pll_q_freq = 0U;
  p_clk->pll_r_freq = 0U;
  p_clk->pll_s_freq = 0U;
  p_clk->pll_t_freq = 0U;

  /* If PLL3 is not ready, return directly all the outputs frequencies set at 0 */
  if (LL_RCC_PLL3_IsReady() == 0U)
  {
    return;
  }

  RCC_PLL_GetClockFreq(PLL_3, p_clk);
}

/**
  * @}
  */ /* End of RCC_Exported_Functions_Group1_33 */

/**
  * @}
  */ /* End of RCC_Exported_Functions_Group1 */

/** @addtogroup RCC_Exported_Functions_Group2
  * @{
  */
/**
  * @brief  Select the clock source to output on MCOx pin.
  * @param  mcox_src  specifies the clock source to output.
  *          This parameter can be one of the following values:
  *            @arg HAL_RCC_MCO1_SRC_HSI
  *            @arg HAL_RCC_MCO1_SRC_LSE
  *            @arg HAL_RCC_MCO1_SRC_HSE
  *            @arg HAL_RCC_MCO1_SRC_PLL1
  *            @arg HAL_RCC_MCO1_SRC_HSI48
  *            @arg HAL_RCC_MCO2_SRC_SYSTEM
  *            @arg HAL_RCC_MCO2_SRC_PLL2
  *            @arg HAL_RCC_MCO2_SRC_HSE
  *            @arg HAL_RCC_MCO2_SRC_PLL1
  *            @arg HAL_RCC_MCO2_SRC_CSI
  *            @arg HAL_RCC_MCO2_SRC_LSI
  * @param  mcox_prescaler  specifies the MCOx prescaler. This parameter can be one of the following
  *         values depending on which MCOx source was selected (MCO1 or MCO2):
  *            @arg HAL_RCC_MCO1_PRESCALERDIS
  *            @arg HAL_RCC_MCO1_PRESCALER1
  *            @arg HAL_RCC_MCO1_PRESCALER2
  *            @arg HAL_RCC_MCO1_PRESCALER3
  *            @arg HAL_RCC_MCO1_PRESCALER4
  *            @arg HAL_RCC_MCO1_PRESCALER5
  *            @arg HAL_RCC_MCO1_PRESCALER6
  *            @arg HAL_RCC_MCO1_PRESCALER7
  *            @arg HAL_RCC_MCO1_PRESCALER8
  *            @arg HAL_RCC_MCO1_PRESCALER9
  *            @arg HAL_RCC_MCO1_PRESCALER10
  *            @arg HAL_RCC_MCO1_PRESCALER11
  *            @arg HAL_RCC_MCO1_PRESCALER12
  *            @arg HAL_RCC_MCO1_PRESCALER13
  *            @arg HAL_RCC_MCO1_PRESCALER14
  *            @arg HAL_RCC_MCO1_PRESCALER15
  *            @arg HAL_RCC_MCO2_PRESCALERDIS
  *            @arg HAL_RCC_MCO2_PRESCALER1
  *            @arg HAL_RCC_MCO2_PRESCALER2
  *            @arg HAL_RCC_MCO2_PRESCALER3
  *            @arg HAL_RCC_MCO2_PRESCALER4
  *            @arg HAL_RCC_MCO2_PRESCALER5
  *            @arg HAL_RCC_MCO2_PRESCALER6
  *            @arg HAL_RCC_MCO2_PRESCALER7
  *            @arg HAL_RCC_MCO2_PRESCALER8
  *            @arg HAL_RCC_MCO2_PRESCALER9
  *            @arg HAL_RCC_MCO2_PRESCALER10
  *            @arg HAL_RCC_MCO2_PRESCALER11
  *            @arg HAL_RCC_MCO2_PRESCALER12
  *            @arg HAL_RCC_MCO2_PRESCALER13
  *            @arg HAL_RCC_MCO2_PRESCALER14
  *            @arg HAL_RCC_MCO2_PRESCALER15
  * @warning MCO selected pin must be configured in alternate function mode.
  */
void HAL_RCC_SetConfigMCO(hal_rcc_mco_src_t mcox_src, hal_rcc_mco_prescaler_t mcox_prescaler)
{
  ASSERT_DBG_PARAM(IS_RCC_MCOSOURCE(mcox_src));
  ASSERT_DBG_PARAM(IS_RCC_MCOPRE(mcox_prescaler));

  LL_RCC_ConfigMCO((uint32_t)mcox_src, (uint32_t)mcox_prescaler);

}

/**
  * @brief  Get and clear reset flags
  * @note   Once reset flags are retrieved, this API is clearing them in order to isolate next reset source.
  * @retval uint32_t Reset flags based on a combination of @ref RCC_Reset_Flag
  */
uint32_t HAL_RCC_GetResetSource(void)
{
  uint32_t reset;

  /* Get all reset flags */

  reset = RCC->RSR & HAL_RCC_RESET_FLAG_ALL;

  LL_RCC_ClearResetFlags();

  return reset;
}

/**
  * @brief  Clear reset flags.
  */
void HAL_RCC_ClearResetFlags(void)
{
  LL_RCC_ClearResetFlags();
}

/**
  * @brief  Enable the Clock Security System.
  * @note   If a failure is detected on the HSE oscillator clock, this oscillator
  *         is automatically disabled and an interrupt is generated to inform the
  *         software about the failure (Clock Security System Interrupt, CSSI),
  *         allowing the MCU to perform rescue operations. The CSSI is linked to
  *         the Cortex-M33 NMI (Non-Maskable Interrupt) exception vector.
  * @note   The Clock Security System can only be cleared by reset.
  */
void HAL_RCC_HSE_EnableCSS(void)
{
  LL_RCC_HSE_EnableCSS();
}

/**
  * @brief Handle the RCC Clock Security System interrupt request.
  * @warning This API must be called under the NMI_Handler().
  * @retval HAL_OK    NMI has been managed and NMI_Handler() might exit
  * @retval HAL_ERROR NMI has not been managed and NMI_Handler() might exit
  */
hal_status_t  HAL_RCC_NMI_IRQHandler(void)
{
  hal_status_t cb_status = HAL_ERROR;

  if (LL_RCC_IsActiveFlag(LL_RCC_IT_HSECSS) != 0U)
  {
    if (HAL_RCC_HSE_CSSCallback() == HAL_OK)
    {
      LL_RCC_ClearFlag(LL_RCC_IT_HSECSS);
      cb_status = HAL_OK;
    }
  }

  return cb_status;
}

/**
  * @brief  RCC Clock Security System interrupt callback.
  */
__WEAK hal_status_t HAL_RCC_HSE_CSSCallback(void)
{
  /* NOTE : This function must not be modified, when the callback is needed,
            the HAL_RCC_HSE_CSSCallback must be implemented in the user file
   */
  /* Status to be updated to HAL_OK when the user callback managed the HSECSS error */
  return HAL_ERROR;
}

/**
  * @brief   Configure the oscillator clock source for wakeup from Stop and CSS backup clock.
  * @param   wakeup_clk  Wakeup clock
  *          This parameter can be one of the following values:
  *            @arg @ref HAL_RCC_STOP_WAKEUPCLOCK_MSI  MSI oscillator selection
  *            @arg @ref HAL_RCC_STOP_WAKEUPCLOCK_HSI  HSI oscillator selection
  * @warning This function must not be called after the Clock Security System on HSE has been enabled.
  */
void HAL_RCC_SetClockAfterWakeFromStop(hal_rcc_stop_wakeup_clk_t wakeup_clk)
{
  ASSERT_DBG_PARAM(IS_RCC_STOP_WAKEUPCLOCK(wakeup_clk));

  LL_RCC_SetClkAfterWakeFromStop((uint32_t)wakeup_clk);
}

/**
  * @brief   Get the oscillator clock source for wakeup from Stop and CSS backup clock.
  * @retval  hal_rcc_stop_wakeup_clk_t  Wakeup clock source
  */
hal_rcc_stop_wakeup_clk_t HAL_RCC_GetClockAfterWakeFromStop(void)
{
  return (hal_rcc_stop_wakeup_clk_t)LL_RCC_GetClkAfterWakeFromStop();
}

/**
  * @brief  Configure the oscillator Kernel clock source for wakeup from Stop
  * @param  wakeup_clk Kernel Wakeup clock
  */
void HAL_RCC_SetKernelClkAfterWakeFromStop(hal_rcc_stop_wakeup_kerclk_t wakeup_clk)
{
  ASSERT_DBG_PARAM(IS_RCC_STOP_KERWAKEUPCLOCK(wakeup_clk));

  LL_RCC_SetKerClkAfterWakeFromStop((uint32_t)wakeup_clk);
}

/**
  * @brief  Get the oscillator Kernel clock source for wakeup from Stop
  * @retval hal_rcc_stop_wakeup_kerclk_t Kernel Wakeup clock
  */
hal_rcc_stop_wakeup_kerclk_t HAL_RCC_GetKernelClkAfterWakeFromStop(void)
{
  return (hal_rcc_stop_wakeup_kerclk_t)LL_RCC_GetKerClkAfterWakeFromStop();
}

#if defined(LSE_VALUE)
/**
  * @brief  Enable the LSE Clock Security System.
  * @note   Prior to enable the LSE Clock Security System, LSE oscillator is to be enabled
  *         with HAL_RCC_OscConfig() and the LSE oscillator clock is to be selected as RTC
  *         clock with HAL_RCC_PeriphClockConfig().
  */
void HAL_RCC_LSE_EnableCSS(void)
{
  LL_RCC_LSE_EnableCSS();
}

/**
  * @brief  Disable the LSE Clock Security System.
  * @note   LSE Clock Security System can only be disabled after a LSE failure detection.
  */
void HAL_RCC_LSE_DisableCSS(void)
{
  LL_RCC_LSE_DisableCSS();
}

/**
  * @brief   Handle the RCC LSE Clock Security System interrupt request.
  * @warning TAMP3 interruption line must be previously configured and enabled to detect this interruption.
  * @note    LSECSS EXTI interrupt line available in U5 except STM32U575/585 rev. X and STM32U59x/5Ax rev. B/Y devices.
  */
void HAL_RCC_LSECSS_IRQHandler(void)
{
  if (LL_RCC_LSE_IsCSSDetected() != 0U)
  {
    /* RCC LSE Clock Security System interrupt user callback */
    HAL_RCC_LSE_CSSCallback();
  }
}

/**
  * @brief  RCC LSE Clock Security System interrupt callback.
  */
__WEAK void HAL_RCC_LSE_CSSCallback(void)
{
  /* NOTE : This function must not be modified, when the callback is needed,
            the @ref HAL_RCC_LSE_CSSCallback must be implemented in the user file
   */
}

#endif /* LSE_VALUE */

/**
  * @brief Enable RTC and TAMP kernel clock.
  * @note  PWR and backup domain are to enabled before calling this function.
  * @retval HAL_OK      RTC and TAMP kernel clock enabled
  * @retval HAL_ERROR   Backup domain is not enabled
  */
hal_status_t HAL_RCC_RTC_EnableKernelClock(void)
{
  if (LL_PWR_IsEnabledBackupWriteProtection() != 0U)
  {
    return HAL_ERROR;
  }
  LL_RCC_EnableRTC();

  return HAL_OK;
}

/**
  * @brief Disable RTC and TAMP kernel clock.
  * @note  PWR and backup domain are to enabled before calling this function.
  * @retval HAL_OK      RTC and TAMP kernel clock disabled
  * @retval HAL_ERROR   Backup domain is not enabled
  */
hal_status_t HAL_RCC_RTC_DisableKernelClock(void)
{
  if (LL_PWR_IsEnabledBackupWriteProtection() != 0U)
  {
    return HAL_ERROR;
  }

  LL_RCC_DisableRTC();

  return HAL_OK;
}
#if 0
/**
  * @brief  Set the Clocks sources for TIM16,TIM17 and LPTIM2 internal input capture
  * @param  clk_src Clock source selection based on @ref hal_rcc_timic_clk_src_t
  * @retval HAL_OK    Source clock has been selected
  */
hal_status_t HAL_RCC_SetTimerInputCaptureClockSource(hal_rcc_timic_clk_src_t clk_src)
{
  ASSERT_DBG_PARAM(IS_RCC_TIMIC_CLK(clk_src));

  LL_RCC_SetTIMICClockSource((uint32_t)clk_src);

  return HAL_OK;
}

/**
  * @brief  Get the Clocks sources for TIM16,TIM17 and LPTIM2 internal input capture
  * @retval clk_src Clock source based on @ref hal_rcc_timic_clk_src_t
  */
hal_rcc_timic_clk_src_t HAL_RCC_GetTimerInputCaptureClockSource(void)
{
  return (hal_rcc_timic_clk_src_t)LL_RCC_GetTIMICClockSource();
}
#endif /* 0 */

/**
  * @}
  */ /* End of RCC_Exported_Functions_Group2 */

/** @addtogroup RCC_Exported_Functions_Group3
  * @{
  */

/**
  * @brief  Set the FMC clock source
  * @param  clk_src Clock source selection based on @ref hal_rcc_fmc_clk_src_t
  * @retval HAL_OK    Source clock has been selected
  */
hal_status_t HAL_RCC_FMC_SetKernelClkSource(hal_rcc_fmc_clk_src_t clk_src)
{
  ASSERT_DBG_PARAM(IS_RCC_FMC_CLK(clk_src));

  LL_RCC_SetFMCClockSource((uint32_t)clk_src);
  return HAL_OK;
}

/**
  * @brief  Set the SDMMC1 clock source
  * @param  clk_src Clock source selection based on @ref hal_rcc_sdmmc1_clk_src_t
  * @retval HAL_OK    Source clock has been selected
  */
hal_status_t HAL_RCC_SDMMC1_SetKernelClkSource(hal_rcc_sdmmc1_clk_src_t clk_src)
{
  ASSERT_DBG_PARAM(IS_RCC_SDMMC1_CLK(clk_src));

  LL_RCC_SetSDMMCClockSource((uint32_t)clk_src);
  return HAL_OK;
}

/**
  * @brief  Set the XSPI1 clock source
  * @param  clk_src Clock source selection based on @ref hal_rcc_xspi1_clk_src_t
  * @retval HAL_OK    Source clock has been selected
  */
hal_status_t HAL_RCC_XSPI1_SetKernelClkSource(hal_rcc_xspi1_clk_src_t clk_src)
{
  ASSERT_DBG_PARAM(IS_RCC_XSPI1_CLK(clk_src));

  LL_RCC_SetXSPIClockSource((uint32_t)clk_src);
  return HAL_OK;
}

/**
  * @brief  Set the OTGFS clock source
  * @param  clk_src Clock source selection based on @ref hal_rcc_otgfs_clk_src_t
  * @retval HAL_OK    Source clock has been selected
  */
hal_status_t HAL_RCC_OTGFS_SetKernelClkSource(hal_rcc_otgfs_clk_src_t clk_src)
{
  ASSERT_DBG_PARAM(IS_RCC_OTGFS_CLK(clk_src));

  LL_RCC_SetOTGFSClockSource((uint32_t)clk_src);
  return HAL_OK;
}

/**
  * @brief  Set the ADF1 clock source
  * @param  clk_src Clock source selection based on @ref hal_rcc_adf1_clk_src_t
  * @retval HAL_OK    Source clock has been selected
  */
hal_status_t HAL_RCC_ADF1_SetKernelClkSource(hal_rcc_adf1_clk_src_t clk_src)
{
  ASSERT_DBG_PARAM(IS_RCC_ADF1_CLK(clk_src));

  LL_RCC_SetADFClockSource((uint32_t)clk_src);
  return HAL_OK;
}

/**
  * @brief  Set the ADC clock source
  * @param  clk_src Clock source selection based on @ref hal_rcc_adc_clk_src_t
  * @retval HAL_OK    Source clock has been selected
  */
hal_status_t HAL_RCC_ADC_SetKernelClkSource(hal_rcc_adc_clk_src_t clk_src)
{
  ASSERT_DBG_PARAM(IS_RCC_ADC_CLK(clk_src));

  LL_RCC_SetADCClockSource((uint32_t)clk_src);
  return HAL_OK;
}

/**
  * @brief  Set the CKPER clock source
  * @param  clk_src Clock source selection based on @ref hal_rcc_ckper_clk_src_t
  * @retval HAL_OK    Source clock has been selected
  */
hal_status_t HAL_RCC_CKPER_SetKernelClkSource(hal_rcc_ckper_clk_src_t clk_src)
{
  ASSERT_DBG_PARAM(IS_RCC_CKPER_CLK(clk_src));

  LL_RCC_SetCKPERClockSource((uint32_t)clk_src);
  return HAL_OK;
}

/**
  * @brief  Set the UART4, 5, 6, 7, 8 and USART2, 3 clock source
  * @param  clk_src Clock source selection based on @ref hal_rcc_uart234578_clk_src_t
  * @retval HAL_OK    Source clock has been selected
  */
hal_status_t HAL_RCC_UART234578_SetKernelClkSource(hal_rcc_uart234578_clk_src_t clk_src)
{
  ASSERT_DBG_PARAM(IS_RCC_UART234578_CLK(clk_src));

  LL_RCC_SetUARTClockSource((uint32_t)clk_src);
  return HAL_OK;
}

/**
  * @brief  Set the SPI1 clock source
  * @param  clk_src Clock source selection based on @ref hal_rcc_spi1_clk_src_t
  * @retval HAL_OK    Source clock has been selected
  */
hal_status_t HAL_RCC_SPI1_SetKernelClkSource(hal_rcc_spi1_clk_src_t clk_src)
{
  ASSERT_DBG_PARAM(IS_RCC_SPI1_CLK(clk_src));

  LL_RCC_SetSPIClockSource((uint32_t)clk_src);
  return HAL_OK;
}

/**
  * @brief  Set the SPI6 clock source
  * @param  clk_src Clock source selection based on @ref hal_rcc_spi6_clk_src_t
  * @retval HAL_OK    Source clock has been selected
  */
hal_status_t HAL_RCC_SPI6_SetKernelClkSource(hal_rcc_spi6_clk_src_t clk_src)
{
  ASSERT_DBG_PARAM(IS_RCC_SPI6_CLK(clk_src));

  LL_RCC_SetSPIClockSource((uint32_t)clk_src);
  return HAL_OK;
}

/**
  * @brief  Set the SPI23 clock source
  * @param  clk_src Clock source selection based on @ref hal_rcc_spi23_clk_src_t
  * @retval HAL_OK    Source clock has been selected
  */
hal_status_t HAL_RCC_SPI23_SetKernelClkSource(hal_rcc_spi23_clk_src_t clk_src)
{
  ASSERT_DBG_PARAM(IS_RCC_SPI23_CLK(clk_src));

  LL_RCC_SetSPIClockSource((uint32_t)clk_src);
  return HAL_OK;
}

/**
  * @brief  Set the SPI45 clock source
  * @param  clk_src Clock source selection based on @ref hal_rcc_spi45_clk_src_t
  * @retval HAL_OK    Source clock has been selected
  */
hal_status_t HAL_RCC_SPI45_SetKernelClkSource(hal_rcc_spi45_clk_src_t clk_src)
{
  ASSERT_DBG_PARAM(IS_RCC_SPI45_CLK(clk_src));

  LL_RCC_SetSPIClockSource((uint32_t)clk_src);
  return HAL_OK;
}

/**
  * @brief  Set the I2C123 clock source
  * @param  clk_src Clock source selection based on @ref hal_rcc_i2c123_clk_src_t
  * @retval HAL_OK    Source clock has been selected
  */
hal_status_t HAL_RCC_I2C123_SetKernelClkSource(hal_rcc_i2c123_clk_src_t clk_src)
{
  ASSERT_DBG_PARAM(IS_RCC_I2C123_CLK(clk_src));

  LL_RCC_SetI2CClockSource((uint32_t)clk_src);
  return HAL_OK;
}

/**
  * @brief  Set the I3C1 clock source
  * @param  clk_src Clock source selection based on @ref hal_rcc_i3c1_clk_src_t
  * @retval HAL_OK    Source clock has been selected
  */
hal_status_t HAL_RCC_I3C1_SetKernelClkSource(hal_rcc_i3c1_clk_src_t clk_src)
{
  ASSERT_DBG_PARAM(IS_RCC_I3C1_CLK(clk_src));

  LL_RCC_SetI3CClockSource((uint32_t)clk_src);
  return HAL_OK;
}

/**
  * @brief  Set the LPTIM1 clock source
  * @param  clk_src Clock source selection based on @ref hal_rcc_lptim1_clk_src_t
  * @retval HAL_OK    Source clock has been selected
  */
hal_status_t HAL_RCC_LPTIM1_SetKernelClkSource(hal_rcc_lptim1_clk_src_t clk_src)
{
  ASSERT_DBG_PARAM(IS_RCC_LPTIM1_CLK(clk_src));

  LL_RCC_SetLPTIMClockSource((uint32_t)clk_src);
  return HAL_OK;
}

/**
  * @brief  Set the LPTIM23 clock source
  * @param  clk_src Clock source selection based on @ref hal_rcc_lptim23_clk_src_t
  * @retval HAL_OK    Source clock has been selected
  */
hal_status_t HAL_RCC_LPTIM23_SetKernelClkSource(hal_rcc_lptim23_clk_src_t clk_src)
{
  ASSERT_DBG_PARAM(IS_RCC_LPTIM23_CLK(clk_src));

  LL_RCC_SetLPTIMClockSource((uint32_t)clk_src);
  return HAL_OK;
}

/**
  * @brief  Set the LPTIM45 clock source
  * @param  clk_src Clock source selection based on @ref hal_rcc_lptim45_clk_src_t
  * @retval HAL_OK    Source clock has been selected
  */
hal_status_t HAL_RCC_LPTIM45_SetKernelClkSource(hal_rcc_lptim45_clk_src_t clk_src)
{
  ASSERT_DBG_PARAM(IS_RCC_LPTIM45_CLK(clk_src));

  LL_RCC_SetLPTIMClockSource((uint32_t)clk_src);
  return HAL_OK;
}

/**
  * @brief  Set the FDCAN clock source
  * @param  clk_src Clock source selection based on @ref hal_rcc_fdcan_clk_src_t
  * @retval HAL_OK    Source clock has been selected
  */
hal_status_t HAL_RCC_FDCAN_SetKernelClkSource(hal_rcc_fdcan_clk_src_t clk_src)
{
  ASSERT_DBG_PARAM(IS_RCC_FDCAN_CLK(clk_src));

  LL_RCC_SetFDCANClockSource((uint32_t)clk_src);
  return HAL_OK;
}

/**
  * @brief  Set the USART1, 6, 10 and UART9 clock source
  * @param  clk_src Clock source selection based on @ref hal_rcc_usart16910_clk_src_t
  * @retval HAL_OK    Source clock has been selected
  */
hal_status_t HAL_RCC_USART16910_SetKernelClkSource(hal_rcc_usart16910_clk_src_t clk_src)
{
  ASSERT_DBG_PARAM(IS_RCC_USART16910_CLK(clk_src));

  LL_RCC_SetUSARTClockSource((uint32_t)clk_src);
  return HAL_OK;
}

/**
  * @brief  Set the LPUART1 clock source
  * @param  clk_src Clock source selection based on @ref hal_rcc_lpuart1_clk_src_t
  * @retval HAL_OK    Source clock has been selected
  */
hal_status_t HAL_RCC_LPUART1_SetKernelClkSource(hal_rcc_lpuart1_clk_src_t clk_src)
{
  ASSERT_DBG_PARAM(IS_RCC_LPUART1_CLK(clk_src));

  LL_RCC_SetLPUARTClockSource((uint32_t)clk_src);
  return HAL_OK;
}

/**
  * @brief  Set the DAC1 clock source
  * @param  clk_src Clock source selection based on @ref hal_rcc_dac1_clk_src_t
  * @retval HAL_OK    Source clock has been selected
  */
hal_status_t HAL_RCC_DAC1_SetKernelClkSource(hal_rcc_dac1_clk_src_t clk_src)
{
  ASSERT_DBG_PARAM(IS_RCC_DAC1_CLK(clk_src));

  LL_RCC_SetDACClockSource((uint32_t)clk_src);
  return HAL_OK;
}

/**
  * @brief  Set the DAC2 clock source
  * @param  clk_src Clock source selection based on @ref hal_rcc_dac2_clk_src_t
  * @retval HAL_OK    Source clock has been selected
  */
hal_status_t HAL_RCC_DAC2_SetKernelClkSource(hal_rcc_dac2_clk_src_t clk_src)
{
  ASSERT_DBG_PARAM(IS_RCC_DAC2_CLK(clk_src));

  LL_RCC_SetDACClockSource((uint32_t)clk_src);
  return HAL_OK;
}

/**
  * @brief  Set the DAC3 clock source
  * @param  clk_src Clock source selection based on @ref hal_rcc_dac3_clk_src_t
  * @retval HAL_OK    Source clock has been selected
  */
hal_status_t HAL_RCC_DAC3_SetKernelClkSource(hal_rcc_dac3_clk_src_t clk_src)
{
  ASSERT_DBG_PARAM(IS_RCC_DAC3_CLK(clk_src));

  LL_RCC_SetDACClockSource((uint32_t)clk_src);
  return HAL_OK;
}

/**
  * @brief  Set the DAC4 clock source
  * @param  clk_src Clock source selection based on @ref hal_rcc_dac4_clk_src_t
  * @retval HAL_OK    Source clock has been selected
  */
hal_status_t HAL_RCC_DAC4_SetKernelClkSource(hal_rcc_dac4_clk_src_t clk_src)
{
  ASSERT_DBG_PARAM(IS_RCC_DAC4_CLK(clk_src));

  LL_RCC_SetDACClockSource((uint32_t)clk_src);
  return HAL_OK;
}

/**
  * @brief  Set the DAC1SH clock source
  * @param  clk_src Clock source selection based on @ref hal_rcc_dac1_sh_clk_src_t
  * @retval HAL_OK    Source clock has been selected
  */
hal_status_t HAL_RCC_DAC1SH_SetKernelClkSource(hal_rcc_dac1_sh_clk_src_t clk_src)
{
  ASSERT_DBG_PARAM(IS_RCC_DAC1SH_CLK(clk_src));

  LL_RCC_SetDACSHClockSource((uint32_t)clk_src);
  return HAL_OK;
}

/**
  * @brief  Set the RTC clock source
  * @param  clk_src Clock source selection based on @ref hal_rcc_rtc_clk_src_t
  * @note   Access to Backup domain has to be enabled.
  * @retval HAL_OK    RTC source clock has been selected
  * @retval HAL_ERROR LSE activation failed after reset of Backup domain
  */
hal_status_t HAL_RCC_RTC_SetKernelClkSource(hal_rcc_rtc_clk_src_t clk_src)
{
  hal_status_t status = HAL_OK;

  ASSERT_DBG_PARAM(IS_RCC_RTC_CLK(clk_src));

  /* Reset the Backup domain only if the RTC Clock source selection is modified from default */
  uint32_t tmpregister = LL_RCC_GetRTCClockSource();

  if ((tmpregister != LL_RCC_RTC_CLKSOURCE_NONE) && (tmpregister != (uint32_t)clk_src))
  {
    /* Store the content of BDCR register before the reset of Backup Domain */
    tmpregister = STM32_READ_BIT(RCC->BDCR, ~(RCC_BDCR_RTCSEL));
    /* RTC Clock selection can be changed only if the Backup Domain is reset */
    HAL_RCC_ResetBackupDomain();
    /* Restore the Content of BDCR register */
    RCC->BDCR = tmpregister;

    if ((clk_src & RCC_BDCR_RTCSEL) == LL_RCC_RTC_CLKSOURCE_HSE)
    {
      /* Set the HSE Prescaler */
      LL_RCC_SetRTC_HSEPrescaler(clk_src >> 16);
    }
    else
    {
      LL_RCC_SetRTC_HSEPrescaler(LL_RCC_RTC_HSE_DIV_DIS);
    }
  }

#if defined(LSE_VALUE)
  /* Wait for LSE reactivation if LSE was enable prior to Backup Domain reset */
  if (STM32_IS_BIT_SET(tmpregister, RCC_BDCR_LSEON))
  {
    status = RCC_WaitForTimeout(LL_RCC_LSE_IsReady, RCC_LSE_TIMEOUT_VALUE, 1U);
  }
  if (status == HAL_OK)
#endif /* LSE_VALUE */
  {
    /* Apply new RTC clock source selection */
    LL_RCC_SetRTCClockSource((uint32_t)clk_src);
  }

  return status;
}

/**
  * @brief  Get the FMC clock source
  * @retval clk_src Clock source based on @ref hal_rcc_fmc_clk_src_t
  */
hal_rcc_fmc_clk_src_t HAL_RCC_FMC_GetKernelClkSource(void)
{
  return (hal_rcc_fmc_clk_src_t)LL_RCC_GetFMCClockSource(LL_RCC_FMC_CLKSOURCE);
}

/**
  * @brief  Get the SDMMC1 clock source
  * @retval clk_src Clock source based on @ref hal_rcc_sdmmc1_clk_src_t
  */
hal_rcc_sdmmc1_clk_src_t HAL_RCC_SDMMC1_GetKernelClkSource(void)
{
  return (hal_rcc_sdmmc1_clk_src_t)LL_RCC_GetSDMMCClockSource(LL_RCC_SDMMC1_CLKSOURCE);
}

/**
  * @brief  Get the XSPI1 clock source
  * @retval clk_src Clock source based on @ref hal_rcc_xspi1_clk_src_t
  */
hal_rcc_xspi1_clk_src_t HAL_RCC_XSPI1_GetKernelClkSource(void)
{
  return (hal_rcc_xspi1_clk_src_t)LL_RCC_GetXSPIClockSource(LL_RCC_XSPI1_CLKSOURCE);
}

/**
  * @brief  Get the OTGFS clock source
  * @retval clk_src Clock source based on @ref hal_rcc_otgfs_clk_src_t
  */
hal_rcc_otgfs_clk_src_t HAL_RCC_OTGFS_GetKernelClkSource(void)
{
  return (hal_rcc_otgfs_clk_src_t)LL_RCC_GetOTGFSClockSource(LL_RCC_OTGFS_CLKSOURCE);
}

/**
  * @brief  Get the ADF1 clock source
  * @retval clk_src Clock source based on @ref hal_rcc_adf1_clk_src_t
  */
hal_rcc_adf1_clk_src_t HAL_RCC_ADF1_GetKernelClkSource(void)
{
  return (hal_rcc_adf1_clk_src_t)LL_RCC_GetADFClockSource(LL_RCC_ADF1_CLKSOURCE);
}

/**
  * @brief  Get the ADC clock source
  * @retval clk_src Clock source based on @ref hal_rcc_adc_clk_src_t
  */
hal_rcc_adc_clk_src_t HAL_RCC_ADC_GetKernelClkSource(void)
{
  return (hal_rcc_adc_clk_src_t)LL_RCC_GetADCClockSource(LL_RCC_ADC_CLKSOURCE);
}

/**
  * @brief  Get the CKPER clock source
  * @retval clk_src Clock source based on @ref hal_rcc_ckper_clk_src_t
  */
hal_rcc_ckper_clk_src_t HAL_RCC_CKPER_GetKernelClkSource(void)
{
  return (hal_rcc_ckper_clk_src_t)LL_RCC_GetCKPERClockSource(LL_RCC_CKPER_CLKSOURCE);
}

/**
  * @brief  Get the UART4, 5, 6, 7, 8 and USART2, 3 clock source
  * @retval clk_src Clock source based on @ref hal_rcc_uart234578_clk_src_t
  */
hal_rcc_uart234578_clk_src_t HAL_RCC_UART234578_GetKernelClkSource(void)
{
  return (hal_rcc_uart234578_clk_src_t)LL_RCC_GetUARTClockSource(LL_RCC_UART234578_CLKSOURCE);
}

/**
  * @brief  Get the SPI1 clock source
  * @retval clk_src Clock source based on @ref hal_rcc_spi1_clk_src_t
  */
hal_rcc_spi1_clk_src_t HAL_RCC_SPI1_GetKernelClkSource(void)
{
  return (hal_rcc_spi1_clk_src_t)LL_RCC_GetSPIClockSource(LL_RCC_SPI1_CLKSOURCE);
}

/**
  * @brief  Get the SPI6 clock source
  * @retval clk_src Clock source based on @ref hal_rcc_spi6_clk_src_t
  */
hal_rcc_spi6_clk_src_t HAL_RCC_SPI6_GetKernelClkSource(void)
{
  return (hal_rcc_spi6_clk_src_t)LL_RCC_GetSPIClockSource(LL_RCC_SPI6_CLKSOURCE);
}

/**
  * @brief  Get the SPI23 clock source
  * @retval clk_src Clock source based on @ref hal_rcc_spi23_clk_src_t
  */
hal_rcc_spi23_clk_src_t HAL_RCC_SPI23_GetKernelClkSource(void)
{
  return (hal_rcc_spi23_clk_src_t)LL_RCC_GetSPIClockSource(LL_RCC_SPI23_CLKSOURCE);
}

/**
  * @brief  Get the SPI45 clock source
  * @retval clk_src Clock source based on @ref hal_rcc_spi45_clk_src_t
  */
hal_rcc_spi45_clk_src_t HAL_RCC_SPI45_GetKernelClkSource(void)
{
  return (hal_rcc_spi45_clk_src_t)LL_RCC_GetSPIClockSource(LL_RCC_SPI45_CLKSOURCE);
}

/**
  * @brief  Get the I2C123 clock source
  * @retval clk_src Clock source based on @ref hal_rcc_i2c123_clk_src_t
  */
hal_rcc_i2c123_clk_src_t HAL_RCC_I2C123_GetKernelClkSource(void)
{
  return (hal_rcc_i2c123_clk_src_t)LL_RCC_GetI2CClockSource(LL_RCC_I2C123_CLKSOURCE);
}

/**
  * @brief  Get the I3C1 clock source
  * @retval clk_src Clock source based on @ref hal_rcc_i3c1_clk_src_t
  */
hal_rcc_i3c1_clk_src_t HAL_RCC_I3C1_GetKernelClkSource(void)
{
  return (hal_rcc_i3c1_clk_src_t)LL_RCC_GetI3CClockSource(LL_RCC_I3C1_CLKSOURCE);
}

/**
  * @brief  Get the LPTIM1 clock source
  * @retval clk_src Clock source based on @ref hal_rcc_lptim1_clk_src_t
  */
hal_rcc_lptim1_clk_src_t HAL_RCC_LPTIM1_GetKernelClkSource(void)
{
  return (hal_rcc_lptim1_clk_src_t)LL_RCC_GetLPTIMClockSource(LL_RCC_LPTIM1_CLKSOURCE);
}

/**
  * @brief  Get the LPTIM23 clock source
  * @retval clk_src Clock source based on @ref hal_rcc_lptim23_clk_src_t
  */
hal_rcc_lptim23_clk_src_t HAL_RCC_LPTIM23_GetKernelClkSource(void)
{
  return (hal_rcc_lptim23_clk_src_t)LL_RCC_GetLPTIMClockSource(LL_RCC_LPTIM23_CLKSOURCE);
}

/**
  * @brief  Get the LPTIM45 clock source
  * @retval clk_src Clock source based on @ref hal_rcc_lptim45_clk_src_t
  */
hal_rcc_lptim45_clk_src_t HAL_RCC_LPTIM45_GetKernelClkSource(void)
{
  return (hal_rcc_lptim45_clk_src_t)LL_RCC_GetLPTIMClockSource(LL_RCC_LPTIM45_CLKSOURCE);
}

/**
  * @brief  Get the FDCAN clock source
  * @retval clk_src Clock source based on @ref hal_rcc_fdcan_clk_src_t
  */
hal_rcc_fdcan_clk_src_t HAL_RCC_FDCAN_GetKernelClkSource(void)
{
  return (hal_rcc_fdcan_clk_src_t)LL_RCC_GetFDCANClockSource(LL_RCC_FDCAN_CLKSOURCE);
}

/**
  * @brief  Get the USART1, 6, 10 and UART9 clock source
  * @retval clk_src Clock source based on @ref hal_rcc_usart16910_clk_src_t
  */
hal_rcc_usart16910_clk_src_t HAL_RCC_USART16910_GetKernelClkSource(void)
{
  return (hal_rcc_usart16910_clk_src_t)LL_RCC_GetUSARTClockSource(LL_RCC_USART16910_CLKSOURCE);
}

/**
  * @brief  Get the LPUART1 clock source
  * @retval clk_src Clock source based on @ref hal_rcc_lpuart1_clk_src_t
  */
hal_rcc_lpuart1_clk_src_t HAL_RCC_LPUART1_GetKernelClkSource(void)
{
  return (hal_rcc_lpuart1_clk_src_t)LL_RCC_GetLPUARTClockSource(LL_RCC_LPUART1_CLKSOURCE);
}

/**
  * @brief  Get the DAC1 clock source
  * @retval clk_src Clock source based on @ref hal_rcc_DAC1_clk_src_t
  */
hal_rcc_dac1_clk_src_t HAL_RCC_DAC1_GetKernelClkSource(void)
{
  return (hal_rcc_dac1_clk_src_t)LL_RCC_GetDACClockSource(LL_RCC_DAC1_CLKSOURCE);
}

/**
  * @brief  Get the DAC2 clock source
  * @retval clk_src Clock source based on @ref hal_rcc_DAC2_clk_src_t
  */
hal_rcc_dac2_clk_src_t HAL_RCC_DAC2_GetKernelClkSource(void)
{
  return (hal_rcc_dac2_clk_src_t)LL_RCC_GetDACClockSource(LL_RCC_DAC2_CLKSOURCE);
}

/**
  * @brief  Get the DAC3 clock source
  * @retval clk_src Clock source based on @ref hal_rcc_DAC3_clk_src_t
  */
hal_rcc_dac3_clk_src_t HAL_RCC_DAC3_GetKernelClkSource(void)
{
  return (hal_rcc_dac3_clk_src_t)LL_RCC_GetDACClockSource(LL_RCC_DAC3_CLKSOURCE);
}

/**
  * @brief  Get the DAC4 clock source
  * @retval clk_src Clock source based on @ref hal_rcc_DAC4_clk_src_t
  */
hal_rcc_dac4_clk_src_t HAL_RCC_DAC4_GetKernelClkSource(void)
{
  return (hal_rcc_dac4_clk_src_t)LL_RCC_GetDACClockSource(LL_RCC_DAC4_CLKSOURCE);
}

/**
  * @brief  Get the DAC1SH clock source
  * @retval clk_src Clock source based on @ref hal_rcc_DAC1sh_clk_src_t
  */
hal_rcc_dac1_sh_clk_src_t HAL_RCC_DAC1SH_GetKernelClkSource(void)
{
  return (hal_rcc_dac1_sh_clk_src_t)LL_RCC_GetDACSHClockSource(LL_RCC_DAC1SH_CLKSOURCE);
}

/**
  * @brief  Get the RTC clock source
  * @retval clk_src Clock source based on @ref hal_rcc_rtc_clk_src_t
  */
hal_rcc_rtc_clk_src_t HAL_RCC_RTC_GetKernelClkSource(void)
{
  return (hal_rcc_rtc_clk_src_t)LL_RCC_GetRTCClockSource();
}

/**
  * @brief  Return the peripheral clock frequency for FMC
  * @retval uint32_t Frequency in Hz
  * @retval 0        Frequency not calculated (Oscillator not ready)
  */
uint32_t HAL_RCC_FMC_GetKernelClkFreq(void)
{
  uint32_t frequency = 0U;
  uint32_t srcclk;
  hal_rcc_pll_output_freq_t pll_clocks;

  srcclk = LL_RCC_GetFMCClockSource(LL_RCC_FMC_CLKSOURCE);

  switch (srcclk)
  {
    case LL_RCC_FMC_CLKSOURCE_HCLK5:

      frequency = HAL_RCC_GetHCLKFreq();
      break;

    case LL_RCC_FMC_CLKSOURCE_PLL1Q:

      HAL_RCC_PLL1_GetClockFreq(&pll_clocks);
      frequency = pll_clocks.pll_q_freq;
      break;

    case LL_RCC_FMC_CLKSOURCE_PLL2R:

      HAL_RCC_PLL2_GetClockFreq(&pll_clocks);
      frequency = pll_clocks.pll_r_freq;
      break;

    case LL_RCC_FMC_CLKSOURCE_HSI:

      if (LL_RCC_HSI_IsReady() != 0U)
      {
        frequency = RCC_HSI_GetCkFreq();
      }
      break;

    default:
      break;
  }

  return frequency;
}

/**
  * @brief  Return the peripheral clock frequency for SDMMC
  * @param  sdmmcx SDMMC instance
  * @retval uint32_t Frequency in Hz
  * @retval 0        Frequency not calculated (Oscillator or PLL not ready, peripheral clock source not set...)
  */
uint32_t HAL_RCC_SDMMC_GetKernelClkFreq(const SDMMC_TypeDef *sdmmcx)
{
  uint32_t frequency = 0U;

  switch ((uint32_t)sdmmcx)
  {
    case (uint32_t)SDMMC1:
      frequency = HAL_RCC_SDMMC1_GetKernelClkFreq();
      break;

    default:
      break;
  }

  return frequency;
}

/**
  * @brief  Return the peripheral clock frequency for SDMMC1
  * @retval uint32_t Frequency in Hz
  * @retval 0        Frequency not calculated (Oscillator not ready)
  */
uint32_t HAL_RCC_SDMMC1_GetKernelClkFreq(void)
{
  uint32_t frequency = 0U;
  uint32_t srcclk;
  hal_rcc_pll_output_freq_t pll_clocks;

  srcclk = LL_RCC_GetSDMMCClockSource(LL_RCC_SDMMC1_CLKSOURCE);

  switch (srcclk)
  {
    case LL_RCC_SDMMC1_CLKSOURCE_PLL2S:

      HAL_RCC_PLL2_GetClockFreq(&pll_clocks);
      frequency = pll_clocks.pll_s_freq;
      break;

    case LL_RCC_SDMMC1_CLKSOURCE_PLL2T:

      HAL_RCC_PLL2_GetClockFreq(&pll_clocks);
      frequency = pll_clocks.pll_t_freq;
      break;

    default :
      break;
  }

  return frequency;
}

/**
  * @brief  Return the peripheral clock frequency for XSPI
  * @param  xspix XSPI instance
  * @retval uint32_t Frequency in Hz
  * @retval 0        Frequency not calculated (Oscillator or PLL not ready, peripheral clock source not set...)
  */
uint32_t HAL_RCC_XSPI_GetKernelClkFreq(const XSPI_TypeDef *xspix)
{
  uint32_t frequency = 0U;

  switch ((uint32_t)xspix)
  {
    case (uint32_t)XSPI1:
      frequency = HAL_RCC_XSPI1_GetKernelClkFreq();
      break;

    default:
      break;
  }

  return frequency;
}

/**
  * @brief  Return the peripheral clock frequency for XSPI1
  * @retval uint32_t Frequency in Hz
  * @retval 0        Frequency not calculated (Oscillator not ready)
  */
uint32_t HAL_RCC_XSPI1_GetKernelClkFreq(void)
{
  uint32_t frequency = 0U;
  uint32_t srcclk;
  hal_rcc_pll_output_freq_t pll_clocks;

  srcclk = LL_RCC_GetXSPIClockSource(LL_RCC_XSPI1_CLKSOURCE);

  switch (srcclk)
  {
    case LL_RCC_XSPI1_CLKSOURCE_HCLK5:

      frequency = HAL_RCC_GetHCLKFreq();
      break;

    case LL_RCC_XSPI1_CLKSOURCE_PLL2S:

      HAL_RCC_PLL2_GetClockFreq(&pll_clocks);
      frequency = pll_clocks.pll_s_freq;
      break;

    case LL_RCC_XSPI1_CLKSOURCE_PLL2T:

      HAL_RCC_PLL2_GetClockFreq(&pll_clocks);
      frequency = pll_clocks.pll_t_freq;
      break;

    default:
      break;
  }

  return frequency;
}

/**
  * @brief  Return the peripheral clock frequency for OTGFS
  * @retval uint32_t Frequency in Hz
  * @retval 0        Frequency not calculated (Oscillator not ready)
  */
uint32_t HAL_RCC_OTGFS_GetKernelClkFreq(void)
{
  uint32_t frequency = 0U;
  uint32_t srcclk;
  hal_rcc_pll_output_freq_t pll_clocks;

  srcclk = LL_RCC_GetOTGFSClockSource(LL_RCC_OTGFS_CLKSOURCE);

  switch (srcclk)
  {
    case LL_RCC_OTGFS_CLKSOURCE_HSI48:

      if (LL_RCC_HSI48_IsReady() != 0U)
      {
        frequency = HSI48_VALUE;
      }
      break;

    case LL_RCC_OTGFS_CLKSOURCE_PLL3Q:

      HAL_RCC_PLL3_GetClockFreq(&pll_clocks);
      frequency = pll_clocks.pll_q_freq;
      break;

#if defined(HSE_VALUE)
    case LL_RCC_OTGFS_CLKSOURCE_HSE:

      if (LL_RCC_HSE_IsReady() != 0U)
      {
        frequency = HSE_VALUE;
      }
      break;
#endif /* HSE_VALUE */

    case LL_RCC_OTGFS_CLKSOURCE_CLK48MOHC:

      /* frequency = HAL_RCC_GetCLK48MOHCFreq(); */
      break;

    default:
      break;
  }

  return frequency;
}

/**
  * @brief  Return the peripheral clock frequency for ADF1
  * @retval uint32_t Frequency in Hz
  * @retval 0        Frequency not calculated (Oscillator not ready)
  */
uint32_t HAL_RCC_ADF1_GetKernelClkFreq(void)
{
  uint32_t frequency = 0U;
  uint32_t srcclk;
  hal_rcc_pll_output_freq_t pll_clocks;

  srcclk = LL_RCC_GetADFClockSource(LL_RCC_ADF1_CLKSOURCE);

  switch (srcclk)
  {
    case LL_RCC_ADF1_CLKSOURCE_HCLK1:
      frequency = HAL_RCC_GetHCLKFreq();
      break;

    case LL_RCC_ADF1_CLKSOURCE_PLL2P:

      HAL_RCC_PLL2_GetClockFreq(&pll_clocks);
      frequency = pll_clocks.pll_p_freq;
      break;

    case LL_RCC_ADF1_CLKSOURCE_PLL3P:

      HAL_RCC_PLL3_GetClockFreq(&pll_clocks);
      frequency = pll_clocks.pll_p_freq;
      break;

#if defined(AUDIO_CLOCK_VALUE)
    case LL_RCC_ADF1_CLKSOURCE_PIN:

      frequency = AUDIO_CLOCK_VALUE;
      break;
#endif /* AUDIO_CLOCK_VALUE */

    case LL_RCC_ADF1_CLKSOURCE_CSI:

      if (LL_RCC_CSI_IsReady() != 0U)
      {
        frequency = CSI_VALUE;
      }
      break;

    case LL_RCC_ADF1_CLKSOURCE_HSI:

      if (LL_RCC_HSI_IsReady() != 0U)
      {
        frequency = RCC_HSI_GetCkFreq();
      }
      break;

    default:
      break;
  }

  return frequency;
}

/**
  * @brief  Return the peripheral clock frequency for ADC
  * @retval uint32_t Frequency in Hz
  * @retval 0        Frequency not calculated (Oscillator not ready)
  */
uint32_t HAL_RCC_ADC_GetKernelClkFreq(void)
{
  uint32_t frequency = 0U;
  uint32_t srcclk;
  hal_rcc_pll_output_freq_t pll_clocks;

  srcclk = LL_RCC_GetADCClockSource(LL_RCC_ADC_CLKSOURCE);

  switch (srcclk)
  {
    case LL_RCC_ADC_CLKSOURCE_HCLK3:
      frequency = HAL_RCC_GetHCLKFreq();
      break;

    case LL_RCC_ADC_CLKSOURCE_TIMX:
      frequency = HAL_RCC_TIM_GetKernelClkFreq(NULL);
      break;

    case LL_RCC_ADC_CLKSOURCE_HSI:

      if (LL_RCC_HSI_IsReady() != 0U)
      {
        frequency = RCC_HSI_GetCkFreq();
      }
      break;

#if defined(HSE_VALUE)
    case LL_RCC_ADC_CLKSOURCE_HSE:

      if (LL_RCC_HSE_IsReady() != 0U)
      {
        frequency = HSE_VALUE;
      }
      break;
#endif /* HSE_VALUE */

    case LL_RCC_ADC_CLKSOURCE_PLL2P:

      HAL_RCC_PLL2_GetClockFreq(&pll_clocks);
      frequency = pll_clocks.pll_p_freq;
      break;

    case LL_RCC_ADC_CLKSOURCE_PLL3R:

      HAL_RCC_PLL3_GetClockFreq(&pll_clocks);
      frequency = pll_clocks.pll_r_freq;
      break;

    case LL_RCC_ADC_CLKSOURCE_PER:

      frequency = HAL_RCC_CKPER_GetKernelClkFreq();
      break;

    default:
      break;
  }

  return frequency;
}

/**
  * @brief  Return the peripheral clock frequency for CKPER
  * @retval uint32_t Frequency in Hz
  * @retval 0        Frequency not calculated (Oscillator not ready)
  */
uint32_t HAL_RCC_CKPER_GetKernelClkFreq(void)
{
  uint32_t frequency = 0U;
  uint32_t srcclk;

  srcclk = LL_RCC_GetCKPERClockSource(LL_RCC_CKPER_CLKSOURCE);

  switch (srcclk)
  {
    case LL_RCC_CKPER_CLKSOURCE_HSI:

      if (LL_RCC_HSI_IsReady() != 0U)
      {
        frequency = RCC_HSI_GetCkFreq();
      }
      break;

    case LL_RCC_CKPER_CLKSOURCE_CSI:

      if (LL_RCC_CSI_IsReady() != 0U)
      {
        frequency = CSI_VALUE;
      }
      break;

#if defined(HSE_VALUE)
    case LL_RCC_CKPER_CLKSOURCE_HSE:

      if (LL_RCC_HSE_IsReady() != 0U)
      {
        frequency = HSE_VALUE;
      }
      break;
#endif /* HSE_VALUE */

    default:
      break;
  }

  return frequency;
}

/**
  * @brief  Return the peripheral clock frequency for UART
  * @param  uartx USART instance
  * @retval uint32_t Frequency in Hz
  * @retval 0        Frequency not calculated (Oscillator or PLL not ready, peripheral clock source not set...)
  */
uint32_t HAL_RCC_UART_GetKernelClkFreq(const USART_TypeDef *uartx)
{
  uint32_t frequency;

  if (uartx == USART1)
  {
    frequency = HAL_RCC_USART16910_GetKernelClkFreq();
  }
  else if (uartx == USART2)
  {
    frequency = HAL_RCC_UART234578_GetKernelClkFreq();
  }
  else if (uartx == USART3)
  {
    frequency = HAL_RCC_UART234578_GetKernelClkFreq();
  }
  else if (uartx == UART4)
  {
    frequency = HAL_RCC_UART234578_GetKernelClkFreq();
  }
  else if (uartx == UART5)
  {
    frequency = HAL_RCC_UART234578_GetKernelClkFreq();
  }
  else if (uartx == USART6)
  {
    frequency = HAL_RCC_USART16910_GetKernelClkFreq();
  }
  else if (uartx == UART7)
  {
    frequency = HAL_RCC_UART234578_GetKernelClkFreq();
  }
  else if (uartx == UART8)
  {
    frequency = HAL_RCC_UART234578_GetKernelClkFreq();
  }
  else if (uartx == UART9)
  {
    frequency = HAL_RCC_USART16910_GetKernelClkFreq();
  }
  else if (uartx == USART10)
  {
    frequency = HAL_RCC_USART16910_GetKernelClkFreq();
  }
  else if (uartx == LPUART1)
  {
    frequency = HAL_RCC_LPUART1_GetKernelClkFreq();
  }
  else
  {
    frequency = 0U;
  }
  return frequency;
}

/**
  * @brief  Return the peripheral clock frequency for USART
  * @param  usartx USART instance
  * @retval uint32_t Frequency in Hz
  * @retval 0        Frequency not calculated (Oscillator or PLL not ready, peripheral clock source not set...)
  */
uint32_t HAL_RCC_USART_GetKernelClkFreq(const USART_TypeDef *usartx)
{
  uint32_t frequency = 0U;

  switch ((uint32_t)usartx)
  {
    case (uint32_t)USART1:
      frequency = HAL_RCC_USART16910_GetKernelClkFreq();
      break;

    case (uint32_t)USART2:
      frequency = HAL_RCC_UART234578_GetKernelClkFreq();
      break;

    case (uint32_t)USART3:
      frequency = HAL_RCC_UART234578_GetKernelClkFreq();
      break;

    case (uint32_t)USART6:
      frequency = HAL_RCC_USART16910_GetKernelClkFreq();
      break;

    case (uint32_t)USART10:
      frequency = HAL_RCC_USART16910_GetKernelClkFreq();
      break;

    default:
      break;
  }

  return frequency;
}


/**
  * @brief  Return the peripheral clock frequency for UART4, 5, 6, 7, 8 and USART2, 3
  * @retval uint32_t Frequency in Hz
  * @retval 0        Frequency not calculated (Oscillator not ready)
  */
uint32_t HAL_RCC_UART234578_GetKernelClkFreq(void)
{
  uint32_t frequency = 0U;
  uint32_t srcclk;
  hal_rcc_pll_output_freq_t pll_clocks;

  srcclk = LL_RCC_GetUARTClockSource(LL_RCC_UART234578_CLKSOURCE);

  switch (srcclk)
  {
    case LL_RCC_UART234578_CLKSOURCE_PCLK1:
      frequency = HAL_RCC_GetPCLK1Freq();
      break;

    case LL_RCC_UART234578_CLKSOURCE_PLL2Q:

      HAL_RCC_PLL2_GetClockFreq(&pll_clocks);
      frequency = pll_clocks.pll_q_freq;
      break;

    case LL_RCC_UART234578_CLKSOURCE_PLL3Q:

      HAL_RCC_PLL3_GetClockFreq(&pll_clocks);
      frequency = pll_clocks.pll_q_freq;
      break;

    case LL_RCC_UART234578_CLKSOURCE_HSI:

      if (LL_RCC_HSI_IsReady() != 0U)
      {
        frequency = RCC_HSI_GetCkFreq();
      }
      break;

    case LL_RCC_UART234578_CLKSOURCE_CSI:

      if (LL_RCC_CSI_IsReady() != 0U)
      {
        frequency = CSI_VALUE;
      }
      break;

#if defined(LSE_VALUE)
    case LL_RCC_UART234578_CLKSOURCE_LSE:

      if (LL_RCC_LSE_IsReady() != 0U)
      {
        frequency = LSE_VALUE;
      }
      break;
#endif /* LSE_VALUE */

    default:
      break;
  }

  return frequency;
}

/**
  * @brief  Return the peripheral clock frequency for USART1, 6, 10 and UART9
  * @retval uint32_t Frequency in Hz
  * @retval 0        Frequency not calculated (Oscillator not ready)
  */
uint32_t HAL_RCC_USART16910_GetKernelClkFreq(void)
{
  uint32_t frequency = 0U;
  uint32_t srcclk;
  hal_rcc_pll_output_freq_t pll_clocks;

  srcclk = LL_RCC_GetUSARTClockSource(LL_RCC_USART16910_CLKSOURCE);

  switch (srcclk)
  {
    case LL_RCC_USART16910_CLKSOURCE_PCLK2:

      frequency = HAL_RCC_GetPCLK2Freq();
      break;

    case LL_RCC_USART16910_CLKSOURCE_PLL2Q:

      HAL_RCC_PLL2_GetClockFreq(&pll_clocks);
      frequency = pll_clocks.pll_q_freq;
      break;

    case LL_RCC_USART16910_CLKSOURCE_PLL3Q:

      HAL_RCC_PLL3_GetClockFreq(&pll_clocks);
      frequency = pll_clocks.pll_q_freq;
      break;

    case LL_RCC_USART16910_CLKSOURCE_HSI:

      if (LL_RCC_HSI_IsReady() != 0U)
      {
        frequency = RCC_HSI_GetCkFreq();
      }
      break;

    case LL_RCC_USART16910_CLKSOURCE_CSI:

      if (LL_RCC_CSI_IsReady() != 0U)
      {
        frequency = CSI_VALUE;
      }
      break;

#if defined(LSE_VALUE)
    case LL_RCC_USART16910_CLKSOURCE_LSE:

      if (LL_RCC_LSE_IsReady() != 0U)
      {
        frequency = LSE_VALUE;
      }

      break;
#endif /* LSE_VALUE */

    default:
      break;
  }

  return frequency;
}

/**
  * @brief  Return the peripheral clock frequency for LPUART1
  * @retval uint32_t Frequency in Hz
  * @retval 0        Frequency not calculated (Oscillator not ready)
  */
uint32_t HAL_RCC_LPUART1_GetKernelClkFreq(void)
{
  uint32_t frequency = 0U;
  uint32_t srcclk;
  hal_rcc_pll_output_freq_t pll_clocks;

  srcclk = LL_RCC_GetLPUARTClockSource(LL_RCC_LPUART1_CLKSOURCE);

  switch (srcclk)
  {
    case LL_RCC_LPUART1_CLKSOURCE_PCLK4:

      frequency = HAL_RCC_GetPCLK4Freq();
      break;

    case LL_RCC_LPUART1_CLKSOURCE_PLL2Q:

      HAL_RCC_PLL2_GetClockFreq(&pll_clocks);
      frequency = pll_clocks.pll_q_freq;
      break;

    case LL_RCC_LPUART1_CLKSOURCE_PLL3Q:

      HAL_RCC_PLL3_GetClockFreq(&pll_clocks);
      frequency = pll_clocks.pll_q_freq;
      break;

    case LL_RCC_LPUART1_CLKSOURCE_HSI:

      if (LL_RCC_HSI_IsReady() != 0U)
      {
        frequency = RCC_HSI_GetCkFreq();
      }
      break;

    case LL_RCC_LPUART1_CLKSOURCE_CSI:

      if (LL_RCC_CSI_IsReady() != 0U)
      {
        frequency = CSI_VALUE;
      }
      break;

#if defined(LSE_VALUE)
    case LL_RCC_LPUART1_CLKSOURCE_LSE:

      if (LL_RCC_LSE_IsReady() != 0U)
      {
        frequency = LSE_VALUE;
      }
      break;
#endif /* LSE_VALUE */

    default:
      break;
  }

  return frequency;
}

/**
  * @brief  Return the peripheral clock frequency for SPI
  * @param  spix SPI instance
  * @retval uint32_t Frequency in Hz
  * @retval 0        Frequency not calculated (Oscillator or PLL not ready, peripheral clock source not set...)
  */
uint32_t HAL_RCC_SPI_GetKernelClkFreq(const SPI_TypeDef *spix)
{
  uint32_t frequency = 0U;

  switch ((uint32_t)spix)
  {
    case (uint32_t)SPI1:
      frequency = HAL_RCC_SPI1_GetKernelClkFreq();
      break;

    case (uint32_t)SPI2:
      frequency = HAL_RCC_SPI23_GetKernelClkFreq();
      break;

    case (uint32_t)SPI3:
      frequency = HAL_RCC_SPI23_GetKernelClkFreq();
      break;

    case (uint32_t)SPI4:
      frequency = HAL_RCC_SPI45_GetKernelClkFreq();
      break;

    case (uint32_t)SPI5:
      frequency = HAL_RCC_SPI45_GetKernelClkFreq();
      break;

    case (uint32_t)SPI6:
      frequency = HAL_RCC_SPI6_GetKernelClkFreq();
      break;

    default:
      break;
  }

  return frequency;
}

/**
  * @brief  Return the peripheral clock frequency for SPI1
  * @retval uint32_t Frequency in Hz
  * @retval 0        Frequency not calculated (Oscillator not ready)
  */
uint32_t HAL_RCC_SPI1_GetKernelClkFreq(void)
{
  uint32_t frequency = 0U;
  uint32_t srcclk;
  hal_rcc_pll_output_freq_t pll_clocks;

  srcclk = LL_RCC_GetSPIClockSource(LL_RCC_SPI1_CLKSOURCE);

  switch (srcclk)
  {
    case LL_RCC_SPI1_CLKSOURCE_PLL1Q:

      HAL_RCC_PLL1_GetClockFreq(&pll_clocks);
      frequency = pll_clocks.pll_q_freq;
      break;

    case LL_RCC_SPI1_CLKSOURCE_PLL2P:

      HAL_RCC_PLL2_GetClockFreq(&pll_clocks);
      frequency = pll_clocks.pll_p_freq;
      break;

    case LL_RCC_SPI1_CLKSOURCE_PLL3P:

      HAL_RCC_PLL3_GetClockFreq(&pll_clocks);
      frequency = pll_clocks.pll_p_freq;
      break;

#if defined(AUDIO_CLOCK_VALUE)
    case LL_RCC_SPI1_CLKSOURCE_AUDIOCLK:

      frequency = AUDIO_CLOCK_VALUE;
      break;
#endif /* AUDIO_CLOCK_VALUE */

    case LL_RCC_SPI1_CLKSOURCE_PER:

      frequency = HAL_RCC_CKPER_GetKernelClkFreq();
      break;

    default:
      break;
  }

  return frequency;
}

/**
  * @brief  Return the peripheral clock frequency for SPI6
  * @retval uint32_t Frequency in Hz
  * @retval 0        Frequency not calculated (Oscillator not ready)
  */
uint32_t HAL_RCC_SPI6_GetKernelClkFreq(void)
{
  uint32_t frequency = 0U;
  uint32_t srcclk;
  hal_rcc_pll_output_freq_t pll_clocks;

  srcclk = LL_RCC_GetSPIClockSource(LL_RCC_SPI6_CLKSOURCE);

  switch (srcclk)
  {
    case LL_RCC_SPI6_CLKSOURCE_PCLK4:

      frequency = HAL_RCC_GetPCLK4Freq();
      break;

    case LL_RCC_SPI6_CLKSOURCE_PLL2Q:

      HAL_RCC_PLL2_GetClockFreq(&pll_clocks);
      frequency = pll_clocks.pll_q_freq;
      break;

    case LL_RCC_SPI6_CLKSOURCE_PLL3Q:

      HAL_RCC_PLL3_GetClockFreq(&pll_clocks);
      frequency = pll_clocks.pll_q_freq;
      break;

    case LL_RCC_SPI6_CLKSOURCE_HSI:

      if (LL_RCC_HSI_IsReady() != 0U)
      {
        frequency = RCC_HSI_GetCkFreq();
      }
      break;

    case LL_RCC_SPI6_CLKSOURCE_CSI:

      if (LL_RCC_CSI_IsReady() != 0U)
      {
        frequency = CSI_VALUE;
      }
      break;

#if defined(HSE_VALUE)
    case LL_RCC_SPI6_CLKSOURCE_HSE:

      if (LL_RCC_HSE_IsReady() != 0U)
      {
        frequency = HSE_VALUE;
      }
      break;
#endif /* HSE_VALUE */

    default:
      break;
  }

  return frequency;
}

/**
  * @brief  Return the peripheral clock frequency for SPI23
  * @retval uint32_t Frequency in Hz
  * @retval 0        Frequency not calculated (Oscillator not ready)
  */
uint32_t HAL_RCC_SPI23_GetKernelClkFreq(void)
{
  uint32_t frequency = 0U;
  uint32_t srcclk;
  hal_rcc_pll_output_freq_t pll_clocks;

  srcclk = LL_RCC_GetSPIClockSource(LL_RCC_SPI23_CLKSOURCE);

  switch (srcclk)
  {
    case LL_RCC_SPI23_CLKSOURCE_PLL1Q:

      HAL_RCC_PLL1_GetClockFreq(&pll_clocks);
      frequency = pll_clocks.pll_q_freq;
      break;

    case LL_RCC_SPI23_CLKSOURCE_PLL2P:

      HAL_RCC_PLL2_GetClockFreq(&pll_clocks);
      frequency = pll_clocks.pll_p_freq;
      break;

    case LL_RCC_SPI23_CLKSOURCE_PLL3P:

      HAL_RCC_PLL3_GetClockFreq(&pll_clocks);
      frequency = pll_clocks.pll_p_freq;
      break;

#if defined(AUDIO_CLOCK_VALUE)
    case LL_RCC_SPI23_CLKSOURCE_AUDIOCLK:

      frequency = AUDIO_CLOCK_VALUE;
      break;
#endif /* AUDIO_CLOCK_VALUE */

    case LL_RCC_SPI23_CLKSOURCE_PER:

      frequency = HAL_RCC_CKPER_GetKernelClkFreq();
      break;

    default:
      break;
  }

  return frequency;
}

/**
  * @brief  Return the peripheral clock frequency for SPI45
  * @retval uint32_t Frequency in Hz
  * @retval 0        Frequency not calculated (Oscillator not ready)
  */
uint32_t HAL_RCC_SPI45_GetKernelClkFreq(void)
{
  uint32_t frequency = 0U;
  uint32_t srcclk;
  hal_rcc_pll_output_freq_t pll_clocks;

  srcclk = LL_RCC_GetSPIClockSource(LL_RCC_SPI45_CLKSOURCE);

  switch (srcclk)
  {
    case LL_RCC_SPI45_CLKSOURCE_PCLK2:

      frequency = HAL_RCC_GetPCLK2Freq();
      break;

    case LL_RCC_SPI45_CLKSOURCE_PLL2Q:

      HAL_RCC_PLL2_GetClockFreq(&pll_clocks);
      frequency = pll_clocks.pll_q_freq;
      break;

    case LL_RCC_SPI45_CLKSOURCE_PLL3Q:

      HAL_RCC_PLL3_GetClockFreq(&pll_clocks);
      frequency = pll_clocks.pll_q_freq;
      break;

    case LL_RCC_SPI45_CLKSOURCE_HSI:

      if (LL_RCC_HSI_IsReady() != 0U)
      {
        frequency = RCC_HSI_GetCkFreq();
      }
      break;

    case LL_RCC_SPI45_CLKSOURCE_CSI:

      if (LL_RCC_CSI_IsReady() != 0U)
      {
        frequency = CSI_VALUE;
      }
      break;

#if defined(HSE_VALUE)
    case LL_RCC_SPI45_CLKSOURCE_HSE:

      if (LL_RCC_HSE_IsReady() != 0U)
      {
        frequency = HSE_VALUE;
      }
      break;
#endif /* HSE_VALUE */

    default:
      break;
  }

  return frequency;
}

/**
  * @brief  Return the peripheral clock frequency for I2C
  * @param  i2cx I2C instance
  * @retval uint32_t Frequency in Hz
  * @retval 0        Frequency not calculated (Oscillator or PLL not ready, peripheral clock source not set...)
  */
uint32_t HAL_RCC_I2C_GetKernelClkFreq(const I2C_TypeDef *i2cx)
{
  STM32_UNUSED(i2cx);
  return HAL_RCC_I2C123_GetKernelClkFreq();
}

/**
  * @brief  Return the peripheral clock frequency for I2C123
  * @retval uint32_t Frequency in Hz
  * @retval 0        Frequency not calculated (Oscillator not ready)
  */
uint32_t HAL_RCC_I2C123_GetKernelClkFreq(void)
{
  uint32_t frequency = 0U;
  uint32_t srcclk;
  hal_rcc_pll_output_freq_t pll_clocks;

  srcclk = LL_RCC_GetI2CClockSource(LL_RCC_I2C123_CLKSOURCE);

  switch (srcclk)
  {
    case LL_RCC_I2C123_CLKSOURCE_PCLK1:

      frequency = HAL_RCC_GetPCLK1Freq();
      break;

    case LL_RCC_I2C123_CLKSOURCE_PLL3R:

      HAL_RCC_PLL3_GetClockFreq(&pll_clocks);
      frequency = pll_clocks.pll_r_freq;
      break;

    case LL_RCC_I2C123_CLKSOURCE_HSI:

      if (LL_RCC_HSI_IsReady() != 0U)
      {
        frequency = RCC_HSI_GetCkFreq();
      }
      break;

    case LL_RCC_I2C123_CLKSOURCE_CSI:

      if (LL_RCC_CSI_IsReady() != 0U)
      {
        frequency = CSI_VALUE;
      }
      break;

    default:
      break;
  }

  return frequency;
}

/**
  * @brief  Return the peripheral clock frequency for I3C
  * @param  i3cx I3C instance
  * @retval uint32_t Frequency in Hz
  * @retval 0        Frequency not calculated (Oscillator or PLL not ready, peripheral clock source not set...)
  */
uint32_t HAL_RCC_I3C_GetKernelClkFreq(const I3C_TypeDef *i3cx)
{
  STM32_UNUSED(i3cx);
  return HAL_RCC_I3C1_GetKernelClkFreq();
}

/**
  * @brief  Return the peripheral clock frequency for I3C1
  * @retval uint32_t Frequency in Hz
  * @retval 0        Frequency not calculated (Oscillator not ready)
  */
uint32_t HAL_RCC_I3C1_GetKernelClkFreq(void)
{
  uint32_t frequency = 0U;
  uint32_t srcclk;
  hal_rcc_pll_output_freq_t pll_clocks;

  srcclk = LL_RCC_GetI3CClockSource(LL_RCC_I3C1_CLKSOURCE);

  switch (srcclk)
  {
    case LL_RCC_I3C1_CLKSOURCE_PCLK1:

      frequency = HAL_RCC_GetPCLK1Freq();
      break;

    case LL_RCC_I3C1_CLKSOURCE_PLL3R:

      HAL_RCC_PLL3_GetClockFreq(&pll_clocks);
      frequency = pll_clocks.pll_r_freq;
      break;

    case LL_RCC_I3C1_CLKSOURCE_HSI:

      if (LL_RCC_HSI_IsReady() != 0U)
      {
        frequency = RCC_HSI_GetCkFreq();
      }
      break;

    case LL_RCC_I3C1_CLKSOURCE_CSI:

      if (LL_RCC_CSI_IsReady() != 0U)
      {
        frequency = CSI_VALUE;
      }
      break;

    default :
      break;
  }

  return frequency;
}

/**
  * @brief  Return the peripheral clock frequency for HRTIM
  * @param  hrtimx HRTIM instance
  * @retval uint32_t Frequency in Hz
  * @retval 0        Frequency not calculated (Oscillator or PLL not ready, peripheral clock source not set...)
  */
uint32_t HAL_RCC_HRTIM_GetKernelClkFreq(const HRTIM_TypeDef *hrtimx)
{
  STM32_UNUSED(hrtimx);
  return HAL_RCC_GetSYSCLKFreq();
}

/**
  * @brief  Return the peripheral clock frequency for HRTIM1
  * @retval uint32_t Frequency in Hz
  * @retval 0        Frequency not calculated (Oscillator not ready)
  */
uint32_t HAL_RCC_HRTIM1_GetKernelClkFreq(void)
{
  return HAL_RCC_GetSYSCLKFreq();
}

/**
  * @brief  Return the peripheral clock frequency for HRTIM2
  * @retval uint32_t Frequency in Hz
  * @retval 0        Frequency not calculated (Oscillator not ready)
  */
uint32_t HAL_RCC_HRTIM2_GetKernelClkFreq(void)
{
  return HAL_RCC_GetSYSCLKFreq();
}

/**
  * @brief  Return the peripheral clock frequency for TIM
  * @param  timx TIM instance
  * @retval uint32_t Frequency in Hz
  * @retval 0        Frequency not calculated (Oscillator or PLL not ready, peripheral clock source not set...)
  */
uint32_t HAL_RCC_TIM_GetKernelClkFreq(const TIM_TypeDef *timx)
{
  STM32_UNUSED(timx);
  return HAL_RCC_GetSYSCLKFreq();
}

/**
  * @brief  Return the peripheral clock frequency for LPTIM
  * @param  lptimx LPTIM instance
  * @retval uint32_t Frequency in Hz
  * @retval 0        Frequency not calculated (Oscillator or PLL not ready, peripheral clock source not set...)
  */
uint32_t HAL_RCC_LPTIM_GetKernelClkFreq(const LPTIM_TypeDef *lptimx)
{
  uint32_t frequency = 0U;

  switch ((uint32_t)lptimx)
  {
    case (uint32_t)LPTIM1:
      frequency = HAL_RCC_LPTIM1_GetKernelClkFreq();
      break;

    case (uint32_t)LPTIM2:
      frequency = HAL_RCC_LPTIM23_GetKernelClkFreq();
      break;

    case (uint32_t)LPTIM3:
      frequency = HAL_RCC_LPTIM23_GetKernelClkFreq();
      break;

    case (uint32_t)LPTIM4:
      frequency = HAL_RCC_LPTIM45_GetKernelClkFreq();
      break;

    case (uint32_t)LPTIM5:
      frequency = HAL_RCC_LPTIM45_GetKernelClkFreq();
      break;

    default:
      break;
  }

  return frequency;
}

/**
  * @brief  Return the peripheral clock frequency for LPTIM1
  * @retval uint32_t Frequency in Hz
  * @retval 0        Frequency not calculated (Oscillator not ready)
  */
uint32_t HAL_RCC_LPTIM1_GetKernelClkFreq(void)
{
  uint32_t frequency = 0U;
  uint32_t srcclk;
  hal_rcc_pll_output_freq_t pll_clocks;

  srcclk = LL_RCC_GetLPTIMClockSource(LL_RCC_LPTIM1_CLKSOURCE);

  switch (srcclk)
  {
    case LL_RCC_LPTIM1_CLKSOURCE_PCLK1:
      frequency = HAL_RCC_GetPCLK1Freq();
      break;

    case LL_RCC_LPTIM1_CLKSOURCE_PLL2P:

      HAL_RCC_PLL2_GetClockFreq(&pll_clocks);
      frequency = pll_clocks.pll_p_freq;
      break;

    case LL_RCC_LPTIM1_CLKSOURCE_PLL3R:

      HAL_RCC_PLL3_GetClockFreq(&pll_clocks);
      frequency = pll_clocks.pll_r_freq;
      break;

#if defined(LSE_VALUE)
    case LL_RCC_LPTIM1_CLKSOURCE_LSE:

      if (LL_RCC_LSE_IsReady() != 0U)
      {
        frequency = LSE_VALUE;
      }
      break;
#endif /* LSE_VALUE */

    case LL_RCC_LPTIM1_CLKSOURCE_LSI:

      if (LL_RCC_LSI_IsReady() != 0U)
      {
        frequency = LSI_VALUE;
      }
      break;

    case LL_RCC_LPTIM1_CLKSOURCE_PER:

      frequency = HAL_RCC_CKPER_GetKernelClkFreq();
      break;

    default:
      break;
  }

  return frequency;
}

/**
  * @brief  Return the peripheral clock frequency for LPTIM23
  * @retval uint32_t Frequency in Hz
  * @retval 0        Frequency not calculated (Oscillator not ready)
  */
uint32_t HAL_RCC_LPTIM23_GetKernelClkFreq(void)
{
  uint32_t frequency = 0U;
  uint32_t srcclk;
  hal_rcc_pll_output_freq_t pll_clocks;

  srcclk = LL_RCC_GetLPTIMClockSource(LL_RCC_LPTIM23_CLKSOURCE);

  switch (srcclk)
  {
    case LL_RCC_LPTIM23_CLKSOURCE_PCLK4:

      frequency = HAL_RCC_GetPCLK4Freq();
      break;

    case LL_RCC_LPTIM23_CLKSOURCE_PLL2P:

      HAL_RCC_PLL2_GetClockFreq(&pll_clocks);
      frequency = pll_clocks.pll_p_freq;
      break;

    case LL_RCC_LPTIM23_CLKSOURCE_PLL3R:

      HAL_RCC_PLL3_GetClockFreq(&pll_clocks);
      frequency = pll_clocks.pll_r_freq;
      break;

#if defined(LSE_VALUE)
    case LL_RCC_LPTIM23_CLKSOURCE_LSE:

      if (LL_RCC_LSE_IsReady() != 0U)
      {
        frequency = LSE_VALUE;
      }
      break;
#endif /* LSE_VALUE */

    case LL_RCC_LPTIM23_CLKSOURCE_LSI:

      if (LL_RCC_LSI_IsReady() != 0U)
      {
        frequency = LSI_VALUE;
      }
      break;

    case LL_RCC_LPTIM23_CLKSOURCE_PER:

      frequency = HAL_RCC_CKPER_GetKernelClkFreq();
      break;

    default:
      break;
  }

  return frequency;
}

/**
  * @brief  Return the peripheral clock frequency for LPTIM45
  * @retval uint32_t Frequency in Hz
  * @retval 0        Frequency not calculated (Oscillator not ready)
  */
uint32_t HAL_RCC_LPTIM45_GetKernelClkFreq(void)
{
  uint32_t frequency = 0U;
  uint32_t srcclk;
  hal_rcc_pll_output_freq_t pll_clocks;

  srcclk = LL_RCC_GetLPTIMClockSource(LL_RCC_LPTIM45_CLKSOURCE);

  switch (srcclk)
  {
    case LL_RCC_LPTIM45_CLKSOURCE_PCLK4:

      frequency = HAL_RCC_GetPCLK4Freq();
      break;

    case LL_RCC_LPTIM45_CLKSOURCE_PLL2P:

      HAL_RCC_PLL2_GetClockFreq(&pll_clocks);
      frequency = pll_clocks.pll_p_freq;
      break;

    case LL_RCC_LPTIM45_CLKSOURCE_PLL3R:

      HAL_RCC_PLL3_GetClockFreq(&pll_clocks);
      frequency = pll_clocks.pll_r_freq;
      break;

#if defined(LSE_VALUE)

    case LL_RCC_LPTIM45_CLKSOURCE_LSE:

      if (LL_RCC_LSE_IsReady() != 0U)
      {
        frequency = LSE_VALUE;
      }
      break;
#endif /* LSE_VALUE */

    case LL_RCC_LPTIM45_CLKSOURCE_LSI:

      if (LL_RCC_LSI_IsReady() != 0U)
      {
        frequency = LSI_VALUE;
      }
      break;

    case LL_RCC_LPTIM45_CLKSOURCE_PER:

      frequency = HAL_RCC_CKPER_GetKernelClkFreq();
      break;

    default:
      break;
  }

  return frequency;
}

/**
  * @brief  Return the peripheral clock frequency for FDCAN
  * @retval uint32_t Frequency in Hz
  * @retval 0        Frequency not calculated (Oscillator not ready)
  */
uint32_t HAL_RCC_FDCAN_GetKernelClkFreq(void)
{
  uint32_t frequency = 0U;
  uint32_t srcclk;
  hal_rcc_pll_output_freq_t pll_clocks;

  srcclk = LL_RCC_GetFDCANClockSource(LL_RCC_FDCAN_CLKSOURCE);

  switch (srcclk)
  {
#if defined(HSE_VALUE)
    case LL_RCC_FDCAN_CLKSOURCE_HSE:

      if (LL_RCC_HSE_IsReady() != 0U)
      {
        frequency = HSE_VALUE;
      }
      break;
#endif /* HSE_VALUE */

    case LL_RCC_FDCAN_CLKSOURCE_PLL1Q:

      HAL_RCC_PLL1_GetClockFreq(&pll_clocks);
      frequency = pll_clocks.pll_q_freq;
      break;

    case LL_RCC_FDCAN_CLKSOURCE_PLL2P:

      HAL_RCC_PLL2_GetClockFreq(&pll_clocks);
      frequency = pll_clocks.pll_p_freq;
      break;

    default:
      break;
  }

  return frequency;
}

/**
  * @brief  Return the peripheral clock frequency for DAC
  * @param  dacx DAC instance
  * @retval uint32_t Frequency in Hz
  * @retval 0        Frequency not calculated (Oscillator or PLL not ready, peripheral clock source not set...)
  */
uint32_t HAL_RCC_DAC_GetKernelClkFreq(const DAC_TypeDef *dacx)
{
  uint32_t frequency = 0U;

  switch ((uint32_t)dacx)
  {
    case (uint32_t)DAC1:
      frequency = HAL_RCC_DAC1_GetKernelClkFreq();
      break;

    case (uint32_t)DAC2:
      frequency = HAL_RCC_DAC1_GetKernelClkFreq();
      break;

    case (uint32_t)DAC3:
      frequency = HAL_RCC_DAC3_GetKernelClkFreq();
      break;

    case (uint32_t)DAC4:
      frequency = HAL_RCC_DAC4_GetKernelClkFreq();
      break;

    default:
      break;
  }

  return frequency;
}

/**
  * @brief  Return the peripheral clock frequency for DAC1
  * @retval uint32_t Frequency in Hz
  * @retval 0        Frequency not calculated (Oscillator not ready)
  */
uint32_t HAL_RCC_DAC1_GetKernelClkFreq(void)
{
  uint32_t frequency = 0U;
  uint32_t srcclk;
  hal_rcc_pll_output_freq_t pll_clocks;

  srcclk = LL_RCC_GetDACClockSource(LL_RCC_DAC1_CLKSOURCE);

  switch (srcclk)
  {
    case LL_RCC_DAC1_CLKSOURCE_HCLK3:

      frequency = HAL_RCC_GetHCLKFreq();
      break;

    case LL_RCC_DAC1_CLKSOURCE_TIM:

      frequency = HAL_RCC_TIM_GetKernelClkFreq(NULL);
      break;

    case LL_RCC_DAC1_CLKSOURCE_ADC:

      frequency = HAL_RCC_ADC_GetKernelClkFreq();
      break;

#if defined(HSE_VALUE)

    case LL_RCC_DAC1_CLKSOURCE_HSE:

      if (LL_RCC_HSE_IsReady() != 0U)
      {
        frequency = HSE_VALUE;
      }
      break;
#endif /* HSE_VALUE */

    case LL_RCC_DAC1_CLKSOURCE_HSI:

      if (LL_RCC_HSI_IsReady() != 0U)
      {
        frequency = RCC_HSI_GetCkFreq();
      }
      break;

    case LL_RCC_DAC1_CLKSOURCE_PLL2P:

      HAL_RCC_PLL2_GetClockFreq(&pll_clocks);
      frequency = pll_clocks.pll_p_freq;
      break;

    case LL_RCC_DAC1_CLKSOURCE_PLL3R:

      HAL_RCC_PLL3_GetClockFreq(&pll_clocks);
      frequency = pll_clocks.pll_r_freq;
      break;

    case LL_RCC_DAC1_CLKSOURCE_PER:

      frequency = HAL_RCC_CKPER_GetKernelClkFreq();
      break;

    default:
      break;
  }

  return frequency;
}

/**
  * @brief  Return the peripheral clock frequency for DAC2
  * @retval uint32_t Frequency in Hz
  * @retval 0        Frequency not calculated (Oscillator not ready)
  */
uint32_t HAL_RCC_DAC2_GetKernelClkFreq(void)
{
  uint32_t frequency = 0U;
  uint32_t srcclk;
  hal_rcc_pll_output_freq_t pll_clocks;

  srcclk = LL_RCC_GetDACClockSource(LL_RCC_DAC2_CLKSOURCE);

  switch (srcclk)
  {
    case LL_RCC_DAC2_CLKSOURCE_HCLK3:

      frequency = HAL_RCC_GetHCLKFreq();
      break;

    case LL_RCC_DAC2_CLKSOURCE_TIM:

      frequency = HAL_RCC_TIM_GetKernelClkFreq(NULL);
      break;

    case LL_RCC_DAC2_CLKSOURCE_ADC:

      frequency = HAL_RCC_ADC_GetKernelClkFreq();
      break;

#if defined(HSE_VALUE)

    case LL_RCC_DAC2_CLKSOURCE_HSE:

      if (LL_RCC_HSE_IsReady() != 0U)
      {
        frequency = HSE_VALUE;
      }
      break;
#endif /* HSE_VALUE */

    case LL_RCC_DAC2_CLKSOURCE_HSI:

      if (LL_RCC_HSI_IsReady() != 0U)
      {
        frequency = RCC_HSI_GetCkFreq();
      }
      break;

    case LL_RCC_DAC2_CLKSOURCE_PLL2P:

      HAL_RCC_PLL2_GetClockFreq(&pll_clocks);
      frequency = pll_clocks.pll_p_freq;
      break;

    case LL_RCC_DAC2_CLKSOURCE_PLL3R:

      HAL_RCC_PLL3_GetClockFreq(&pll_clocks);
      frequency = pll_clocks.pll_r_freq;
      break;

    case LL_RCC_DAC2_CLKSOURCE_PER:

      frequency = HAL_RCC_CKPER_GetKernelClkFreq();
      break;

    default:
      break;
  }

  return frequency;
}

/**
  * @brief  Return the peripheral clock frequency for DAC3
  * @retval uint32_t Frequency in Hz
  * @retval 0        Frequency not calculated (Oscillator not ready)
  */
uint32_t HAL_RCC_DAC3_GetKernelClkFreq(void)
{
  uint32_t frequency = 0U;
  uint32_t srcclk;
  hal_rcc_pll_output_freq_t pll_clocks;

  srcclk = LL_RCC_GetDACClockSource(LL_RCC_DAC3_CLKSOURCE);

  switch (srcclk)
  {
    case LL_RCC_DAC3_CLKSOURCE_HCLK3:

      frequency = HAL_RCC_GetHCLKFreq();
      break;

    case LL_RCC_DAC3_CLKSOURCE_TIM:

      frequency = HAL_RCC_TIM_GetKernelClkFreq(NULL);
      break;

    case LL_RCC_DAC3_CLKSOURCE_ADC:

      frequency = HAL_RCC_ADC_GetKernelClkFreq();
      break;

#if defined(HSE_VALUE)
    case LL_RCC_DAC3_CLKSOURCE_HSE:

      if (LL_RCC_HSE_IsReady() != 0U)
      {
        frequency = HSE_VALUE;
      }
      break;
#endif /* HSE_VALUE */

    case LL_RCC_DAC3_CLKSOURCE_PLL2P:

      HAL_RCC_PLL2_GetClockFreq(&pll_clocks);
      frequency = pll_clocks.pll_p_freq;
      break;

    case LL_RCC_DAC3_CLKSOURCE_PLL3R:

      HAL_RCC_PLL3_GetClockFreq(&pll_clocks);
      frequency = pll_clocks.pll_r_freq;
      break;

    case LL_RCC_DAC3_CLKSOURCE_PER:

      frequency = HAL_RCC_CKPER_GetKernelClkFreq();
      break;

    default:
      break;
  }

  return frequency;
}

/**
  * @brief  Return the peripheral clock frequency for DAC4
  * @retval uint32_t Frequency in Hz
  * @retval 0        Frequency not calculated (Oscillator not ready)
  */
uint32_t HAL_RCC_DAC4_GetKernelClkFreq(void)
{
  uint32_t frequency = 0U;
  uint32_t srcclk;
  hal_rcc_pll_output_freq_t pll_clocks;

  srcclk = LL_RCC_GetDACClockSource(LL_RCC_DAC4_CLKSOURCE);

  switch (srcclk)
  {
    case LL_RCC_DAC4_CLKSOURCE_HCLK3:

      frequency = HAL_RCC_GetHCLKFreq();
      break;

    case LL_RCC_DAC4_CLKSOURCE_TIM:

      frequency = HAL_RCC_TIM_GetKernelClkFreq(NULL);
      break;

    case LL_RCC_DAC4_CLKSOURCE_ADC:

      frequency = HAL_RCC_ADC_GetKernelClkFreq();
      break;

#if defined(HSE_VALUE)
    case LL_RCC_DAC4_CLKSOURCE_HSE:

      if (LL_RCC_HSE_IsReady() != 0U)
      {
        frequency = HSE_VALUE;
      }
      break;
#endif /* HSE_VALUE */

    case LL_RCC_DAC4_CLKSOURCE_HSI:

      if (LL_RCC_HSI_IsReady() != 0U)
      {
        frequency = RCC_HSI_GetCkFreq();
      }
      break;

    case LL_RCC_DAC4_CLKSOURCE_PLL2P:

      HAL_RCC_PLL2_GetClockFreq(&pll_clocks);
      frequency = pll_clocks.pll_p_freq;
      break;

    case LL_RCC_DAC4_CLKSOURCE_PLL3R:

      HAL_RCC_PLL3_GetClockFreq(&pll_clocks);
      frequency = pll_clocks.pll_r_freq;
      break;

    case LL_RCC_DAC4_CLKSOURCE_PER:

      frequency = HAL_RCC_CKPER_GetKernelClkFreq();
      break;

    default:
      break;
  }

  return frequency;
}

/**
  * @brief  Return the peripheral clock frequency for DACSH
  * @param  dacshx DACSH instance
  * @retval uint32_t Frequency in Hz
  * @retval 0        Frequency not calculated (Oscillator or PLL not ready, peripheral clock source not set...)
  */
uint32_t HAL_RCC_DAC_GetSampleHoldClkFreq(const DAC_TypeDef *dacshx)
{
  uint32_t frequency;

  if ((dacshx == DAC1) || (dacshx == DAC2) || (dacshx == DAC3) || (dacshx == DAC4))
  {
    frequency = HAL_RCC_DAC1_GetKernelClkFreq();
  }
  else
  {
    frequency = 0U;
  }
  return frequency;
}

/**
  * @brief  Return the peripheral clock frequency for DAC1SH
  * @retval uint32_t Frequency in Hz
  * @retval 0        Frequency not calculated (Oscillator not ready)
  */
uint32_t HAL_RCC_DAC1_GetSampleHoldClkFreq(void)
{
  uint32_t frequency = 0U;
  uint32_t srcclk;

  srcclk = LL_RCC_GetDACSHClockSource(LL_RCC_DAC1SH_CLKSOURCE);

  switch (srcclk)
  {
    case LL_RCC_DAC1SH_CLKSOURCE_LSI:

      if (LL_RCC_LSI_IsReady() != 0U)
      {
        frequency = LSI_VALUE;
      }
      break;

#if defined(LSE_VALUE)
    case LL_RCC_DAC1SH_CLKSOURCE_LSE:

      if (LL_RCC_LSE_IsReady() != 0U)
      {
        frequency = LSE_VALUE;
      }
      break;
#endif /* LSE_VALUE */

    default:
      break;
  }

  return frequency;
}

/**
  * @brief  Return the peripheral clock frequency for COMP
  * @param  compx COMP instance
  * @retval uint32_t Frequency in Hz
  * @retval 0        Frequency not calculated (Oscillator or PLL not ready, peripheral clock source not set...)
  */
uint32_t HAL_RCC_COMP_GetKernelClkFreq(const COMP_TypeDef *compx)
{
  STM32_UNUSED(compx);
  return HAL_RCC_GetPCLK4Freq();
}


/**
  * @brief  Return the peripheral clock frequency for RTC
  * @retval uint32_t Frequency in Hz
  * @retval 0        Frequency not calculated (Oscillator not ready)
  */
uint32_t HAL_RCC_RTC_GetKernelClkFreq(void)
{
  uint32_t frequency = 0U;
  uint32_t srcclk ;

  srcclk = LL_RCC_GetRTCClockSource();

  switch (srcclk)
  {
    case LL_RCC_RTC_CLKSOURCE_LSI:

      if (LL_RCC_LSI_IsReady() != 0U)
      {
        frequency = LSI_VALUE;
      }
      break;

#if defined(LSE_VALUE)
    case LL_RCC_RTC_CLKSOURCE_LSE:

      if (LL_RCC_LSE_IsReady() != 0U)
      {
        frequency = LSE_VALUE;
      }
      break;
#endif /* LSE_VALUE */

#if defined(HSE_VALUE)
    case LL_RCC_RTC_CLKSOURCE_HSE:

      if (LL_RCC_HSE_IsReady() != 0U)
      {
        uint32_t Prescaler = LL_RCC_GetRTC_HSEPrescaler();
        if (Prescaler >= LL_RCC_RTC_HSE_DIV_2)
        {
          frequency = HSE_VALUE / Prescaler;
        }
      }
      break;
#endif /* HSE_VALUE */

    default:
      break;
  }

  return frequency;
}

/**
  * @}
  */ /* End of RCC_Exported_Functions_Group3 */

/**
  * @}
  */ /* End of RCC_Exported_Functions */


/* Private function prototypes -----------------------------------------------*/

/** @addtogroup RCC_Private_Functions
  * @{
  */
/** @brief  Wait for clock timeout
  * @param  p_timeout_cb Callback on the timeout function
  * @param  timeout      Timeout value
  * @param  status       Status to be checked
  * @retval HAL_OK       Not timeout detected
  * @retval HAL_ERROR    Timeout detected during clock activation or deactivation
  */
static hal_status_t RCC_WaitForTimeout(const rcc_cb_timeout_t p_timeout_cb, uint32_t timeout, uint32_t status)
{
  uint32_t tickstart;
  hal_status_t hal_status = HAL_OK;
  tickstart = HAL_GetTick();

  while (p_timeout_cb() != status)
  {
    if ((HAL_GetTick() - tickstart) > timeout)
    {
      /* New check to avoid false timeout detection in case of preemption */
      if (p_timeout_cb() != status)
      {
        hal_status = HAL_ERROR;
        break;
      }
    }
  }

  return hal_status;
}

/**
  * @brief   Configure PLLx without enabling outputs.
  * @details The config function will perform the following actions:
  *           - Check in PLLx is well deactivated (if enabled exit from this function)
  *           - Configure the PLLx with full list of parameters
  * @param pll_id   ID on the targeted PLLx (PLL1, PLL2 or PLL3)
  * @param p_config pointer to a @ref hal_rcc_pll_config_t structure that
  *          contains the configuration information for the PLLx
  * @retval HAL_OK            PLLx has been correctly configured\n
  * @retval HAL_ERROR         PLLx is already enabled and can not be modified.
  */
static hal_status_t RCC_PLL_SetConfig(rcc_pll_id_t pll_id, const hal_rcc_pll_config_t *p_config)
{
  hal_status_t status = HAL_ERROR;

  /*
    The config function will perform the following actions:
    - Check in PLLx is well deactivated (if enabled exit from this function)
    - Configure the PLLx with full list of parameters
  */
  if ((STM32_READ_BIT(RCC->CR, (1UL << (RCC_CR_PLL1RDY_Pos + ((uint32_t)pll_id * 2U))))) == 0U)
  {
    uint32_t pll_ref_ck = 0U;
    uint32_t pllvco_freq = 0U;
    volatile uint32_t *p_addr_pllcfgr;
    volatile uint32_t *p_addr_reg2;
    uint32_t vci;
    uint32_t vco;
    uint32_t tickstart;

    /* Configure the PLL clock source and main division factor */
    p_addr_reg2 = (volatile uint32_t *)((uint32_t)&RCC->PLLCKSELR);
    STM32_MODIFY_REG(*p_addr_reg2, (RCC_PLLCKSELR_PLLSRC | (RCC_PLLCKSELR_DIVM1 << (pll_id * 8U))),
                     ((uint32_t)p_config->pll_source << RCC_PLLCKSELR_PLLSRC_Pos)
                     | ((uint32_t)(p_config->pll_m) << (RCC_PLLCKSELR_DIVM1_Pos + (pll_id * 8U))));

    /* Configure PLLx DIVN */
    p_addr_reg2 = (volatile uint32_t *)((uint32_t)&RCC->PLL1DIVR1 + ((uint32_t)pll_id * 0x08U));
    STM32_MODIFY_REG(*p_addr_reg2, RCC_PLL1DIVR1_DIVN, ((uint32_t)(p_config->pll_n - 1UL) << RCC_PLL1DIVR1_DIVN_Pos));

    /* Mode Configuration */
    /* Configure PLLx FRACN */
    p_addr_pllcfgr = (volatile uint32_t *)((uint32_t)&RCC->PLLCFGR);
    p_addr_reg2 = (volatile uint32_t *)((uint32_t)&RCC->PLL1FRACR + ((uint32_t)pll_id * 0x08U));

    STM32_CLEAR_BIT(*p_addr_pllcfgr, (RCC_PLLCFGR_PLL1FRACEN << (pll_id * 11U)));
    if ((p_config->pll_fracn) != 0U)
    {
      STM32_MODIFY_REG(*p_addr_reg2, RCC_PLL1FRACR_FRACN, ((uint32_t)(p_config->pll_fracn) << RCC_PLL1FRACR_FRACN_Pos));
    }
    else
    {
      STM32_MODIFY_REG(*p_addr_reg2, RCC_PLL1FRACR_FRACN, 0U);
    }
    STM32_SET_BIT(*p_addr_pllcfgr, (RCC_PLLCFGR_PLL1FRACEN << (pll_id * 11U)));

    /* 5 us required for value to be latched */
    tickstart = HAL_GetTick();
    while ((HAL_GetTick() - tickstart) < RCC_PLL_FRAC_WAIT_VALUE)
    {
    }

    /* Configure PLL Spread-Spectrum Modulation (SSCG) and enable it */
    if ((p_config->pll_sscg_status) == HAL_RCC_PLL_SSCG_ENABLE)
    {
      p_addr_reg2 = (volatile uint32_t *)((uint32_t)&RCC->PLL1SSCGR + ((uint32_t)pll_id * 0x04U));
      STM32_MODIFY_REG(*p_addr_reg2, RCC_PLL1SSCGR_MODPER | RCC_PLL1SSCGR_INCSTEP | RCC_PLL1SSCGR_SPREADSEL | \
                       RCC_PLL1SSCGR_RPDFNDIS | RCC_PLL1SSCGR_TPDFNDIS,
                       ((((uint32_t)(p_config->pll_sscg_config.mod_period) << \
                          RCC_PLL1SSCGR_MODPER_Pos) & RCC_PLL1SSCGR_MODPER)  |
                        (((uint32_t)(p_config->pll_sscg_config.mod_depth_adj) << \
                          RCC_PLL1SSCGR_INCSTEP_Pos) & RCC_PLL1SSCGR_INCSTEP) |
                        (p_config->pll_sscg_config.mod_spread) | (p_config->pll_sscg_config.dith_control)));
      STM32_SET_BIT(*p_addr_pllcfgr, (RCC_PLLCFGR_PLL1SSCGEN << (pll_id * 11U))); /* PLL SSCG enable */
    }
    else
    {
      STM32_CLEAR_BIT(*p_addr_pllcfgr, (RCC_PLLCFGR_PLL1SSCGEN << (pll_id * 11U)));
    }

    /* Ranges configuration when divm prescaler is not disabled */
    if (p_config->pll_m != 0U)
    {

      switch (p_config->pll_source)
      {
        case HAL_RCC_PLL_SRC_HSI:
          pll_ref_ck = RCC_HSI_GetCkFreq() / p_config->pll_m;
          break;
        case HAL_RCC_PLL_SRC_CSI:
          pll_ref_ck = CSI_VALUE / p_config->pll_m;
          break;
#if defined(HSE_VALUE)
        case HAL_RCC_PLL_SRC_HSE:
          pll_ref_ck = HSE_VALUE / p_config->pll_m;
          break;
#endif /* HSE_VALUE */
        default:
          break;
      }

      pllvco_freq = (uint32_t)(pll_ref_ck * ((float_t)p_config->pll_n + (p_config->pll_fracn / (float_t)0x2000)));

      /* Configure the PLLx input and output frequency range
          - if ref_ck input between 1 and 2MHz  => low-range
          - if ref_ck input between 2 and 16MHz => wide range */

      if ((pll_ref_ck >= RCC_PLL_INPUTRANGE0_FREQMIN) && (pll_ref_ck < RCC_PLL_INPUTRANGE0_FREQMAX))
      {
        vci = LL_RCC_PLL1_INPUTRANGE_1_2;
        if ((pllvco_freq >= RCC_PLL_VCOL_FREQMIN) && (pllvco_freq < RCC_PLL_VCOL_FREQMAX))
        {
          vco = LL_RCC_PLL1_OUTPUTRANGE_150_420;
        }
        else
        {
          /* PLLx VCO frequency not accessible */
          return HAL_ERROR;
        }
      }
      else
      {
        if ((pll_ref_ck >= RCC_PLL_INPUTRANGE1_FREQMIN) && (pll_ref_ck < RCC_PLL_INPUTRANGE1_FREQMAX))
        {
          vci = LL_RCC_PLL1_INPUTRANGE_2_4;
        }
        else if ((pll_ref_ck >= RCC_PLL_INPUTRANGE2_FREQMIN) && (pll_ref_ck < RCC_PLL_INPUTRANGE2_FREQMAX))
        {
          vci = LL_RCC_PLL1_INPUTRANGE_4_8;
        }
        else if ((pll_ref_ck >= RCC_PLL_INPUTRANGE3_FREQMIN) && (pll_ref_ck <= RCC_PLL_INPUTRANGE3_FREQMAX))
        {
          vci = LL_RCC_PLL1_INPUTRANGE_8_16;
        }
        else
        {
          /* PLLx input reference frequency is outside supported ranges (under 1Mhz or more than 16Mhz)*/
          return HAL_ERROR;
        }
        pllvco_freq = pllvco_freq * 2;    /* vco_freq multiplied by 2 in VCO wide range */
        if ((pllvco_freq >= RCC_PLL_VCOH_FREQMIN) && (pllvco_freq < RCC_PLL_VCOH_FREQMAX))
        {
          vco = LL_RCC_PLL1_OUTPUTRANGE_384_1672;
        }
        else
        {
          /* PLLx VCO frequency not accessible */
          return HAL_ERROR;
        }
      }

      STM32_MODIFY_REG(*p_addr_pllcfgr, ((RCC_PLLCFGR_PLL1RGE | RCC_PLLCFGR_PLL1VCOSEL) << (pll_id * 11U)),
                       ((vco | vci) << (pll_id * 11U)));
    }

    /* Configure PLLx Output Dividers - Specific for each PLL */
    if (pll_id == PLL_1)
    {
      p_addr_reg2 = (volatile uint32_t *)((uint32_t)&RCC->PLL1DIVR1);
      STM32_MODIFY_REG(*p_addr_reg2, (RCC_PLL1DIVR1_DIVP | RCC_PLL1DIVR1_DIVQ),
                       ((((uint32_t)(p_config->pll_p - 1UL) << RCC_PLL1DIVR1_DIVP_Pos) & RCC_PLL1DIVR1_DIVP) |
                        (((uint32_t)(p_config->pll_q - 1UL) << RCC_PLL1DIVR1_DIVQ_Pos) & RCC_PLL1DIVR1_DIVQ)));

      p_addr_reg2 = (volatile uint32_t *)((uint32_t)&RCC->PLL1DIVR2);
      STM32_MODIFY_REG(*p_addr_reg2, (RCC_PLL1DIVR2_DIVS),
                       ((((uint32_t)(p_config->pll_s - 1UL) << RCC_PLL1DIVR2_DIVS_Pos) & RCC_PLL1DIVR2_DIVS)));
    }
    else if (pll_id == PLL_2)
    {
      p_addr_reg2 = (volatile uint32_t *)((uint32_t)&RCC->PLL2DIVR1);
      STM32_MODIFY_REG(*p_addr_reg2, (RCC_PLL2DIVR1_DIVP | RCC_PLL2DIVR1_DIVQ | RCC_PLL2DIVR1_DIVR),
                       ((((uint32_t)(p_config->pll_p - 1UL) << RCC_PLL2DIVR1_DIVP_Pos) & RCC_PLL2DIVR1_DIVP) |
                        (((uint32_t)(p_config->pll_q - 1UL) << RCC_PLL2DIVR1_DIVQ_Pos) & RCC_PLL2DIVR1_DIVQ) |
                        (((uint32_t)(p_config->pll_r - 1UL) << RCC_PLL2DIVR1_DIVR_Pos) & RCC_PLL2DIVR1_DIVR)));

      p_addr_reg2 = (volatile uint32_t *)((uint32_t)&RCC->PLL2DIVR2);
      STM32_MODIFY_REG(*p_addr_reg2, (RCC_PLL2DIVR2_DIVS | RCC_PLL2DIVR2_DIVT),
                       ((((uint32_t)(p_config->pll_s - 1UL) << RCC_PLL2DIVR2_DIVS_Pos) & RCC_PLL2DIVR2_DIVS) |
                        (((uint32_t)(p_config->pll_t - 1UL) << RCC_PLL2DIVR2_DIVT_Pos) & RCC_PLL2DIVR2_DIVT)));
    }
    else if (pll_id == PLL_3)
    {
      p_addr_reg2 = (volatile uint32_t *)((uint32_t)&RCC->PLL3DIVR1);
      STM32_MODIFY_REG(*p_addr_reg2, (RCC_PLL3DIVR1_DIVP | RCC_PLL3DIVR1_DIVQ | RCC_PLL3DIVR1_DIVR),
                       ((((uint32_t)(p_config->pll_p - 1UL) << RCC_PLL3DIVR1_DIVP_Pos) & RCC_PLL3DIVR1_DIVP) |
                        (((uint32_t)(p_config->pll_q - 1UL) << RCC_PLL3DIVR1_DIVQ_Pos) & RCC_PLL3DIVR1_DIVQ) |
                        (((uint32_t)(p_config->pll_r - 1UL) << RCC_PLL3DIVR1_DIVR_Pos) & RCC_PLL3DIVR1_DIVR)));

      p_addr_reg2 = (volatile uint32_t *)((uint32_t)&RCC->PLL3DIVR2);
      STM32_MODIFY_REG(*p_addr_reg2, (RCC_PLL3DIVR2_DIVS),
                       ((((uint32_t)(p_config->pll_s - 1UL) << RCC_PLL3DIVR2_DIVS_Pos) & RCC_PLL3DIVR2_DIVS)));
    }
    else
    {
      return HAL_ERROR;
    }

    status = HAL_OK;
  }
  return status;
}

/**
  * @brief Return the configuration of PLLx.
  * @param pll_id    ID on the targeted PLLx (PLL1, PLL2 or PLL3)
  * @param p_config  pointer to a @ref hal_rcc_pll_config_t structure that
  *          contains the configuration information for the PLLx
  */
static void RCC_PLL_GetConfig(rcc_pll_id_t pll_id, hal_rcc_pll_config_t *p_config)
{
  uint32_t temp_reg;

  /* Read PLLCKSELR register */
  temp_reg = RCC->PLLCKSELR;
  p_config->pll_source  = (hal_rcc_pll_src_t)(uint32_t)(STM32_READ_BIT(temp_reg, RCC_PLLCKSELR_PLLSRC));
  p_config->pll_m       = (uint8_t)(STM32_READ_BIT(temp_reg, (RCC_PLLCKSELR_DIVM1 << (pll_id * 8U))) >> \
                                    (RCC_PLLCKSELR_DIVM1_Pos + (pll_id * 8U)));

  /* Read PLLxDIVR1 register */
  temp_reg = (uint32_t) * (STM32_READ_REG((volatile uint32_t *)((uint32_t)&RCC->PLL1DIVR1 + ((uint32_t)pll_id * 8U))));
  p_config->pll_n = (uint16_t)((STM32_READ_BIT(temp_reg, RCC_PLL1DIVR1_DIVN) >>  RCC_PLL1DIVR1_DIVN_Pos) + 1UL);
  p_config->pll_p = (uint8_t)((STM32_READ_BIT(temp_reg, RCC_PLL1DIVR1_DIVP) >>  RCC_PLL1DIVR1_DIVP_Pos) + 1UL);
  p_config->pll_q = (uint8_t)((STM32_READ_BIT(temp_reg, RCC_PLL1DIVR1_DIVQ) >>  RCC_PLL1DIVR1_DIVQ_Pos) + 1UL);
  p_config->pll_r = (uint8_t)((STM32_READ_BIT(temp_reg, RCC_PLL2DIVR1_DIVR) >>  RCC_PLL2DIVR1_DIVR_Pos) + 1UL);

  /* Read PLLxDIVR2 register */
  temp_reg = (uint32_t) * (STM32_READ_REG((volatile uint32_t *)((uint32_t)&RCC->PLL1DIVR2 + ((uint32_t)pll_id * 4U))));
  p_config->pll_s = (uint8_t)((STM32_READ_BIT(temp_reg, RCC_PLL2DIVR2_DIVS) >>  RCC_PLL2DIVR2_DIVS_Pos) + 1UL);
  p_config->pll_t = (uint8_t)((STM32_READ_BIT(temp_reg, RCC_PLL2DIVR2_DIVT) >>  RCC_PLL2DIVR2_DIVT_Pos) + 1UL);


  /* Read PLLxFRACR register */
  temp_reg = (uint32_t) * (STM32_READ_REG((volatile uint32_t *)((uint32_t)&RCC->PLL1FRACR + ((uint32_t)pll_id * 8U))));
  p_config->pll_fracn = (uint16_t)(STM32_READ_BIT(temp_reg, RCC_PLL1FRACR_FRACN) >>  RCC_PLL1FRACR_FRACN_Pos);

  /* Read PLLCFGR register - Get PLLx Mode*/
  temp_reg = (uint32_t) * (STM32_READ_REG((volatile uint32_t *)((uint32_t)&RCC->PLLCFGR)));
  if (STM32_READ_BIT(temp_reg, (RCC_PLLCFGR_PLL1SSCGEN << (pll_id * 11U))) == (RCC_PLLCFGR_PLL1SSCGEN << \
                                                                               (pll_id * 11U)))
  {
    p_config->pll_sscg_status = HAL_RCC_PLL_SSCG_ENABLE;
  }
  else
  {
    p_config->pll_sscg_status = HAL_RCC_PLL_SSCG_DISABLE;
  }

  /* Read SSCG register */
  temp_reg = (uint32_t) * (STM32_READ_REG((volatile uint32_t *)((uint32_t)&RCC->PLL1SSCGR + ((uint32_t)pll_id * 8U))));
  p_config->pll_sscg_config.mod_period = (uint8_t)(STM32_READ_BIT(temp_reg, RCC_PLL1SSCGR_MODPER) >>  \
                                                   RCC_PLL1SSCGR_MODPER_Pos);
  p_config->pll_sscg_config.mod_depth_adj = (uint8_t)(STM32_READ_BIT(temp_reg, RCC_PLL1SSCGR_INCSTEP) >>  \
                                                      RCC_PLL1SSCGR_INCSTEP_Pos);
  p_config->pll_sscg_config.mod_spread = (hal_rcc_pll_sscg_mod_spread_t)(STM32_READ_BIT(temp_reg, \
                                                                         RCC_PLL1SSCGR_SPREADSEL));
  p_config->pll_sscg_config.dith_control = (hal_rcc_pll_sscg_dith_ctrl_t)(STM32_READ_BIT(temp_reg, \
                                                                          RCC_PLL1SSCGR_RPDFNDIS |
                                                                          RCC_PLL1SSCGR_TPDFNDIS));

}

/**
  * @brief  Compute PLLx VCO output frequency
  * @retval Value of PLLx VCO output frequency
  */
static void RCC_PLL_GetClockFreq(rcc_pll_id_t pll_id, hal_rcc_pll_output_freq_t *p_clk)
{
  uint32_t temp_reg;
  uint32_t pll_src;
  uint32_t pll_m;
  uint32_t pll_n;
  uint32_t pll_p;
  uint32_t pll_q;
  uint32_t pll_r;
  uint32_t pll_s;
  uint32_t pll_t;
  uint32_t pll_fracn;
  uint32_t pll_src_clk;
  float_t pll_vco_clk;

  /* Get PLL1 CFGR and DIVR register values */
  temp_reg = RCC->PLLCKSELR;
  pll_src = (uint32_t)(STM32_READ_BIT(temp_reg, RCC_PLLCKSELR_PLLSRC));
  pll_m = (uint32_t)(STM32_READ_BIT(temp_reg, (RCC_PLLCKSELR_DIVM1 << (pll_id * 8U))) >> \
                     (RCC_PLLCKSELR_DIVM1_Pos + (pll_id * 8U)));

  /* Read PLLxDIVR1 register */
  temp_reg = (uint32_t) * (STM32_READ_REG((volatile uint32_t *)((uint32_t)&RCC->PLL1DIVR1 + ((uint32_t)pll_id * 8U))));
  pll_n = (uint32_t)((STM32_READ_BIT(temp_reg, RCC_PLL1DIVR1_DIVN) >>  RCC_PLL1DIVR1_DIVN_Pos) + 1UL);
  pll_p = (uint32_t)((STM32_READ_BIT(temp_reg, RCC_PLL1DIVR1_DIVP) >>  RCC_PLL1DIVR1_DIVP_Pos) + 1UL);
  pll_q = (uint32_t)((STM32_READ_BIT(temp_reg, RCC_PLL1DIVR1_DIVQ) >>  RCC_PLL1DIVR1_DIVQ_Pos) + 1UL);
  pll_r = (uint32_t)((STM32_READ_BIT(temp_reg, RCC_PLL2DIVR1_DIVR) >>  RCC_PLL2DIVR1_DIVR_Pos) + 1UL);

  temp_reg = (uint32_t) * (STM32_READ_REG((volatile uint32_t *)((uint32_t)&RCC->PLL1DIVR2 + ((uint32_t)pll_id * 4U))));
  pll_s = (uint32_t)((STM32_READ_BIT(temp_reg, RCC_PLL2DIVR2_DIVS) >>  RCC_PLL2DIVR2_DIVS_Pos) + 1UL);
  pll_t = (uint32_t)((STM32_READ_BIT(temp_reg, RCC_PLL2DIVR2_DIVT) >>  RCC_PLL2DIVR2_DIVT_Pos) + 1UL);


  temp_reg = (uint32_t) * (STM32_READ_REG((volatile uint32_t *)((uint32_t)&RCC->PLL1FRACR + ((uint32_t)pll_id * 8U))));
  pll_fracn = (uint16_t)(STM32_READ_BIT(temp_reg, RCC_PLL1FRACR_FRACN) >>  RCC_PLL1FRACR_FRACN_Pos);

  switch (pll_src)
  {
    case HAL_RCC_PLL_SRC_HSI:
      pll_src_clk = RCC_HSI_GetCkFreq();
      break;
    case HAL_RCC_PLL_SRC_CSI:
      pll_src_clk = CSI_VALUE;
      break;
#if defined(HSE_VALUE)
    case HAL_RCC_PLL_SRC_HSE:
      pll_src_clk = HSE_VALUE;
      break;
#endif /* HSE_VALUE */
    default:
      pll_src_clk = 0U;
      break;
  }

  if (pll_m == 0U)
  {
    pll_vco_clk = 0;
  }
  else
  {
    pll_vco_clk = (((float_t)pll_src_clk / (float_t)pll_m) * ((float_t)pll_n + (pll_fracn / (float_t)0x2000U)));
  }

  temp_reg = RCC->PLLCFGR;
  if (STM32_IS_BIT_SET(temp_reg, (LL_RCC_PLL1_OUTPUT_P << (pll_id * 11U))))
  {
    p_clk->pll_p_freq = (uint32_t)(pll_vco_clk / ((float_t)pll_p));
  }

  if (STM32_IS_BIT_SET(temp_reg, (LL_RCC_PLL1_OUTPUT_Q << (pll_id * 11U))))
  {
    p_clk->pll_q_freq = (uint32_t)(pll_vco_clk / ((float_t)pll_q));
  }

  if (STM32_IS_BIT_SET(temp_reg, (LL_RCC_PLL2_OUTPUT_R << ((pll_id - 1U) * 11U))))
  {
    p_clk->pll_r_freq = (uint32_t)(pll_vco_clk / ((float_t)pll_r));
  }

  if (STM32_IS_BIT_SET(temp_reg, (LL_RCC_PLL1_OUTPUT_S << (pll_id * 11U))))
  {
    p_clk->pll_s_freq = (uint32_t)(pll_vco_clk / ((float_t)pll_s));
  }

  if (STM32_IS_BIT_SET(temp_reg, (LL_RCC_PLL2_OUTPUT_T << ((pll_id - 1U) * 11U))))
  {
    p_clk->pll_t_freq = (uint32_t)(pll_vco_clk / ((float_t)pll_t));
  }

}


/**
  * @brief Return the HSI clock Frequency.
  * @retval uint32_t Frequency in Hz
  * @retval 0        Frequency not calculated (Oscillator not ready)
  */
static uint32_t RCC_HSI_GetCkFreq(void)
{
  return (HSI_VALUE >> (LL_RCC_HSI_GetDivider() >> RCC_CR_HSIDIV_Pos));
}

/**
  * @}
  */ /* End of RCC_Private_Functions */

#endif /* USE_HAL_RCC_MODULE */


/**
  * @}
  */ /* End of RCC */

/**
  * @}
  */ /* End of STM32H7PXX_HAL_Driver */
