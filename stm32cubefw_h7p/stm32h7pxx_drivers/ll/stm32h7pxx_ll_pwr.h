/**
  **********************************************************************************************************************
  * @file    stm32h7pxx_ll_pwr.h
  * @author  GPM Application Team
  * @brief   Header file of PWR LL module.
  **********************************************************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file in the root directory of this software
  * component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  **********************************************************************************************************************
  */

/* Define to prevent recursive inclusion -----------------------------------------------------------------------------*/
#ifndef STM32H7Pxx_LL_PWR_H
#define STM32H7Pxx_LL_PWR_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ----------------------------------------------------------------------------------------------------------*/
#include "stm32h7pxx.h"

/** @addtogroup STM32H7Pxx_LL_Driver
  * @{
  */

#if defined (PWR)

/** @defgroup PWR_LL PWR
  * @{
  */

/* Private types -----------------------------------------------------------------------------------------------------*/
/* Private variables -------------------------------------------------------------------------------------------------*/
/* Private constants -------------------------------------------------------------------------------------------------*/
/** @defgroup PWR_LL_Private_Constants PWR Private Constants
  * @{
  */

/** @defgroup PWR_LL_WAKEUP_PIN_OFFSET Wake-Up Pins register offsets Defines
  * @brief    Flags defines which can be used with LL_PWR_WRITE_REG function.
  * @{
  */
/* Wake-Up Pins PWR register offsets */
#define LL_PWR_WAKEUP_PINS_PULL_SHIFT_OFFSET    2UL
#define LL_PWR_WAKEUP_PINS_MAX_SHIFT_MASK       0x1FU
#define LL_PWR_WAKEUP_PIN_EN_REF                PWR_WKUPEPR_WKUPEN1
#define LL_PWR_WAKEUP_PIN_EN_REF_POS            PWR_WKUPEPR_WKUPEN1_Pos
#define LL_PWR_WAKEUP_PIN_PP_REF                PWR_WKUPEPR_WKUPP1
#define LL_PWR_WAKEUP_PIN_PP_REF_POS            PWR_WKUPEPR_WKUPP1_Pos
#define LL_PWR_WAKEUP_PIN_PULL_REF              PWR_WKUPEPR_WKUPPUPD1
#define LL_PWR_WAKEUP_PIN_PULL_REF_POS          PWR_WKUPEPR_WKUPPUPD1_Pos
/**
  * @}
  */
/**
  * @}
  */
/* Private macros ----------------------------------------------------------------------------------------------------*/
/* Exported types ----------------------------------------------------------------------------------------------------*/
/* Exported constants ------------------------------------------------------------------------------------------------*/
/** @defgroup PWR_LL_Exported_Constants PWR Exported Constants
  * @{
  */

/** @defgroup PWR_LL_EC_CLEAR_FLAG Clear flags defines
  * @brief    Flags defines which can be used with LL_PWR_WRITE_REG function.
  * @{
  */
#define LL_PWR_SR_CSSF                 PWR_CSR3_CSSF                           /*!< Clear Stop and Standby flags */
/**
  * @}
  */

/** @defgroup PWR_LL_EC_GET_FLAG Get flags defines
  * @brief    Flags defines which can be used with LL_PWR_READ_REG function.
  * @{
  */
#define LL_PWR_FLAG_VOSRDY             PWR_CSR4_VOSRDY                         /*!< Voltage scaling ready flag */
#define LL_PWR_FLAG_STOPF              PWR_CSR3_STOPF                          /*!< Stop flag                  */
#define LL_PWR_FLAG_SBF                PWR_CSR3_SBF                            /*!< Standby flag               */
#define LL_PWR_WAKEUP_FLAG1            PWR_WKUPFR_WKUPF1                       /*!< Wakeup flag 1              */
#define LL_PWR_WAKEUP_FLAG2            PWR_WKUPFR_WKUPF2                       /*!< Wakeup flag 2              */
#define LL_PWR_WAKEUP_FLAG3            PWR_WKUPFR_WKUPF3                       /*!< Wakeup flag 3              */
#define LL_PWR_WAKEUP_FLAG4            PWR_WKUPFR_WKUPF4                       /*!< Wakeup flag 4              */
#define LL_PWR_WAKEUP_FLAG5            PWR_WKUPFR_WKUPF5                       /*!< Wakeup flag 5              */
#define LL_PWR_WAKEUP_FLAG6            PWR_WKUPFR_WKUPF6                       /*!< Wakeup flag 6              */
#define LL_PWR_WAKEUP_FLAG7            PWR_WKUPFR_WKUPF7                       /*!< Wakeup flag 7              */
#define LL_PWR_WAKEUP_FLAG8            PWR_WKUPFR_WKUPF8                       /*!< Wakeup flag 8              */
/**
  * @}
  */

/** @defgroup PWR_LL_EC_LOW_POWER_MODE_SELECTION  Low Power Mode Selection
  * @{
  */
#define LL_PWR_STOP_MODE    0U                     /*!< STOP mode    */
#define LL_PWR_STANDBY_MODE PWR_CSR3_PDDS          /*!< STANDBY mode   */
/**
  * @}
  */

/** @defgroup PWR_LL_EC_VOLTAGE_SCALING_RANGE_SELECTION PWR Voltage scaling range selection
  * @{
  */
#define LL_PWR_REGU_VOLT_SCALE_POS  PWR_CSR4_VOS_Pos               /*!< Voltage scaling range register position */
#define LL_PWR_REGU_VOLT_SCALE_0    (0x3UL << PWR_CSR4_VOS_Pos)    /*!< Voltage scaling range 0 */
#define LL_PWR_REGU_VOLT_SCALE_1    (0x2UL << PWR_CSR4_VOS_Pos)    /*!< Voltage scaling range 1 */
#define LL_PWR_REGU_VOLT_SCALE_2    (0x1UL << PWR_CSR4_VOS_Pos)    /*!< Voltage scaling range 2 */
/**
  * @}
  */

/** @defgroup PWR_LL_EC_ACTIVE_VOLTAGE_SCALING_RANGE_SELECTION PWR Voltage scaling range selection
  * @{
  */
#define LL_PWR_ACTIVE_VOLT_SCALE_POS  PWR_SR1_ACTVOS_Pos        /*!< Active voltage scaling range register position */
#define LL_PWR_ACTIVE_VOLT_SCALE_0    (0x3UL << PWR_SR1_ACTVOS_Pos)   /*!< Voltage scaling range 0 */
#define LL_PWR_ACTIVE_VOLT_SCALE_1    (0x2UL << PWR_SR1_ACTVOS_Pos)   /*!< Voltage scaling range 1 */
#define LL_PWR_ACTIVE_VOLT_SCALE_2    (0x1UL << PWR_SR1_ACTVOS_Pos)   /*!< Voltage scaling range 2 */
/**
  * @}
  */

/** @defgroup PWR_LL_EC_STOP_MODE_REGU_VOLTAGE Stop mode Regulator Voltage Scaling
  * @{
  */
#define LL_PWR_REGU_STOP_VOLT_SCALE_HIGH     PWR_CR1_SVOS    /*!< Voltage scaling High (highest frequency) STOP mode */
#define LL_PWR_REGU_STOP_VOLT_SCALE_LOW      0U              /*!< Voltage scaling Low (lowest power) STOP mode       */
/**
  * @}
  */

/** @defgroup PWR_LL_EC_PVDLEVEL Power Digital Voltage Level Detector
  * @{
  */
#define LL_PWR_PVDLEVEL_1              (0U << PWR_CR1_PLS_Pos)   /*!< PVD level 1 */
#define LL_PWR_PVDLEVEL_2              (1U << PWR_CR1_PLS_Pos)   /*!< PVD level 2 */
#define LL_PWR_PVDLEVEL_3              (2U << PWR_CR1_PLS_Pos)   /*!< PVD level 3 */
#define LL_PWR_PVDLEVEL_4              (3U << PWR_CR1_PLS_Pos)   /*!< PVD level 4 */
#define LL_PWR_PVDLEVEL_5              (4U << PWR_CR1_PLS_Pos)   /*!< PVD level 5 */
#define LL_PWR_PVDLEVEL_6              (5U << PWR_CR1_PLS_Pos)   /*!< PVD level 6 */
#define LL_PWR_PVDLEVEL_7              (6U << PWR_CR1_PLS_Pos)   /*!< PVD level 7 */
#define LL_PWR_PVDLEVEL_8              (7U << PWR_CR1_PLS_Pos)   /*!< PVD level 7 */
/*!< External voltage level on PVD_IN pin, compared to internal VREFINT level */
/**
  * @}
  */

/** @defgroup PWR_LL_EC_AVDLEVEL Power Analog Voltage Level Detector
  * @{
  */
#define LL_PWR_AVDLEVEL_1              (0U << PWR_CR1_ALS_Pos)  /*!< Analog Voltage detector level 1 */
#define LL_PWR_AVDLEVEL_2              (1U << PWR_CR1_ALS_Pos)  /*!< Analog Voltage detector level 2 */
#define LL_PWR_AVDLEVEL_3              (2U << PWR_CR1_ALS_Pos)  /*!< Analog Voltage detector level 3 */
#define LL_PWR_AVDLEVEL_4              (3u << PWR_CR1_ALS_Pos)  /*!< Analog Voltage detector level 4 */
/**
  * @}
  */

/** @defgroup PWR_LL_EC_BATT_CHARG_RESISTOR Battery Charge Resistor
  * @{
  */
#define LL_PWR_BATT_CHARG_RESISTOR_5K   0U                 /*!< Charge the Battery through a 5 kO resistor   */
#define LL_PWR_BATT_CHARG_RESISTOR_1_5K PWR_CSR2_VBRS      /*!< Charge the Battery through a 1.5 kO resistor */
/**
  * @}
  */

/** @defgroup PWR_LL_EC_WAKEUP_PIN  Wakeup Pins
  * @{
  */
#define LL_PWR_WAKEUP_PIN_1            PWR_WKUPEPR_WKUPEN1      /*!< Wakeup pin 1 : PA0    */
#define LL_PWR_WAKEUP_PIN_2            PWR_WKUPEPR_WKUPEN2      /*!< Wakeup pin 2 : PA2    */
#define LL_PWR_WAKEUP_PIN_3            PWR_WKUPEPR_WKUPEN3      /*!< Wakeup pin 3 : PI8    */
#define LL_PWR_WAKEUP_PIN_4            PWR_WKUPEPR_WKUPEN4      /*!< Wakeup pin 4 : PC13   */
#define LL_PWR_WAKEUP_PIN_5            PWR_WKUPEPR_WKUPEN5      /*!< Wakeup pin 5 : PB9    */
#define LL_PWR_WAKEUP_PIN_6            PWR_WKUPEPR_WKUPEN6      /*!< Wakeup pin 6 : PC1    */
#define LL_PWR_WAKEUP_PIN_7            PWR_WKUPEPR_WKUPEN7      /*!< Wakeup pin 7 : PC0    */
#define LL_PWR_WAKEUP_PIN_8            PWR_WKUPEPR_WKUPEN8      /*!< Wakeup pin 8 : PD2    */
#define LL_PWR_WAKEUP_PIN_ALL          0x000000FFUL             /*!< Wakeup all pin enable */
/**
  * @}
  */

/** @defgroup PWR_LL_EC_WAKEUP_PIN_PULL  Wakeup Pins pull configuration
  * @{
  */
#define LL_PWR_WAKEUP_PIN_PULL_NO        0UL          /*!< Configure Wakeup pin in no pull   */
#define LL_PWR_WAKEUP_PIN_PULL_UP        1UL          /*!< Configure Wakeup pin in pull Up   */
#define LL_PWR_WAKEUP_PIN_PULL_DOWN      2UL          /*!< Configure Wakeup pin in pull Down */
/**
  * @}
  */

/** @defgroup PWR_LL_EC_WAKEUP_PIN_POLARITY  Wakeup Pins polarity
  * @{
  */
#define LL_PWR_WAKEUP_PIN_POLARITY_HIGH     0x00000000UL   /*!< Wakeup pin polarity high  */
#define LL_PWR_WAKEUP_PIN_POLARITY_LOW      0x00000001UL   /*!< Wakeup pin polarity low   */
/**
  * @}
  */


/** @defgroup PWR_LL_EC_INTERNAL_REGULATORS_BYPASS PWR SMPS and LDO internal regulators bypass in Range 0 definition
  * @{
  */
#define LL_PWR_MAIN_REGU_SUPPLY_NOT_BYPASSED  0U              /*!< SMPS and LDO internal regulators bypass in Range 0 */
#define LL_PWR_MAIN_REGU_SUPPLY_BYPASSED      PWR_CSR2_BYPASS /*!< SMPS and LDO internal regulators bypass in Range 0 */
/**
  * @}
  */


/** @defgroup PWR_LL_EC_INTERNAL_REGULATOR_SUPPLY PWR Regulator supply
  * @{
  */
#define LL_PWR_MAIN_REGU_SUPPLY_LDO_ENABLED    PWR_CSR2_LDOEN  /*!< LDO regulator supply  */
#define LL_PWR_MAIN_REGU_SUPPLY_SMPS_ENABLED   PWR_CSR2_SMPSEN /*!< SMPS regulator supply */
/**
  * @}
  */

/** @defgroup PWR_LL_EC_ANALOG_IO_SWITCH_SUPPLY PWR Analog IO switch supply definitions
  * @{
  */
#define LL_PWR_ANALOG_IO_SWITCH_VDDA_SUPPLY            0U               /*!< Analog IO switch to VddA supply     */
#define LL_PWR_ANALOG_IO_SWITCH_BOOSTER_SUPPLY         (PWR_CR1_AVDREADY | \
                                                        PWR_CR1_BOOSTE) /*!< Analog IO switch to Booster supply  */

/**
  * @}
  */

/** @defgroup PWR_LL_EC_CORE_SLEEP_MODE  Core sleep mode
  * @{
  */
#define LL_PWR_CORE_SLEEP       0U                    /*!< Core sleep mode      */
#define LL_PWR_CORE_DEEP_SLEEP  SCB_SCR_SLEEPDEEP_Msk /*!< Core deep sleep mode */
/**
  * @}
  */

/** @defgroup PWR_LL_EC_SUPPLY_PWR Power supply source configuration
  * @{
  */
#define LL_PWR_LDO_SUPPLY               PWR_CSR2_LDOEN    /*!< Core domains are supplied from the LDO  */
#define LL_PWR_DIRECT_SMPS_SUPPLY       PWR_CSR2_SMPSEN   /*!< Core domains are supplied from the SMPS */
#define LL_PWR_EXTERNAL_SOURCE_SUPPLY   PWR_CSR2_BYPASS   /*!< Core supplied from an external source   */
/**
  * @}
  */


/** @defgroup PWR_LL_EC_I3C_PULLUP I3C Pull-Up Pins
  * @{
  */
#define LL_PWR_I3C_PULLUP_PA15         PWR_I3CPUCR_I3CPA15_PU     /*!< Port PA15 I3C pull-up bit */
#define LL_PWR_I3C_PULLUP_PB3          PWR_I3CPUCR_I3CPB3_PU      /*!< Port PB3 I3C pull-up bit */
#define LL_PWR_I3C_PULLUP_PB4          PWR_I3CPUCR_I3CPB4_PU      /*!< Port PB4 I3C pull-up bit */
#define LL_PWR_I3C_PULLUP_PB8          PWR_I3CPUCR_I3CPB8_PU      /*!< Port PB8 I3C pull-up bit */
#define LL_PWR_I3C_PULLUP_PB9          PWR_I3CPUCR_I3CPB9_PU      /*!< Port PB9 I3C pull-up bit */
#define LL_PWR_I3C_PULLUP_PC8          PWR_I3CPUCR_I3CPC8_PU      /*!< Port PC8 I3C pull-up bit */
#define LL_PWR_I3C_PULLUP_PC9          PWR_I3CPUCR_I3CPC9_PU      /*!< Port PC9 I3C pull-up bit */
#define LL_PWR_I3C_PULLUP_PD0          PWR_I3CPUCR_I3CPD0_PU      /*!< Port PD0 I3C pull-up bit */
#define LL_PWR_I3C_PULLUP_PD1          PWR_I3CPUCR_I3CPD1_PU      /*!< Port PD1 I3C pull-up bit */
#define LL_PWR_I3C_PULLUP_PD6          PWR_I3CPUCR_I3CPD6_PU      /*!< Port PD6 I3C pull-up bit */
#define LL_PWR_I3C_PULLUP_PD7          PWR_I3CPUCR_I3CPD7_PU      /*!< Port PD7 I3C pull-up bit */
#define LL_PWR_I3C_PULLUP_PE5          PWR_I3CPUCR_I3CPE5_PU      /*!< Port PE5 I3C pull-up bit */
#define LL_PWR_I3C_PULLUP_PE6          PWR_I3CPUCR_I3CPE6_PU      /*!< Port PE6 I3C pull-up bit */
#define LL_PWR_I3C_PULLUP_PG13         PWR_I3CPUCR_I3CPG13_PU     /*!< Port PG13 I3C pull-up bit */
#define LL_PWR_I3C_PULLUP_PG14         PWR_I3CPUCR_I3CPG14_PU     /*!< Port PG14 I3C pull-up bit */
#define LL_PWR_I3C_PULLUP_PH11         PWR_I3CPUCR_I3CPH11_PU     /*!< Port PH11 I3C pull-up bit */
#define LL_PWR_I3C_PULLUP_PH12         PWR_I3CPUCR_I3CPH12_PU     /*!< Port PH12 I3C pull-up bit */
#define LL_PWR_I3C_PULLUP_PI2          PWR_I3CPUCR_I3CPI2_PU      /*!< Port PI2 I3C pull-up bit */
/**
  * @}
  */

/** @defgroup PWR_LL_EC_XSPI_PULLUP XSPI Pull-Up Pins
  * @{
  */
#define LL_PWR_XSPI_PULLUP_PH0         PWR_XSPIPUCR_XSPIPH0_PU    /*!< Port PH0 XSPI pull-up bit */
#define LL_PWR_XSPI_PULLUP_PH1         PWR_XSPIPUCR_XSPIPH1_PU    /*!< Port PH1 XSPI pull-up bit */
#define LL_PWR_XSPI_PULLUP_PF2         PWR_XSPIPUCR_XSPIPF2_PU    /*!< Port PF2 XSPI pull-up bit */
#define LL_PWR_XSPI_PULLUP_PA0         PWR_XSPIPUCR_XSPIPA0_PU    /*!< Port PA0 XSPI pull-up bit */
#define LL_PWR_XSPI_PULLUP_PA2         PWR_XSPIPUCR_XSPIPA2_PU    /*!< Port PA2 XSPI pull-up bit */
#define LL_PWR_XSPI_PULLUP_PA3         PWR_XSPIPUCR_XSPIPA3_PU    /*!< Port PA3 XSPI pull-up bit */
#define LL_PWR_XSPI_PULLUP_PA4         PWR_XSPIPUCR_XSPIPA4_PU    /*!< Port PA4 XSPI pull-up bit */
#define LL_PWR_XSPI_PULLUP_PA5         PWR_XSPIPUCR_XSPIPA5_PU    /*!< Port PA5 XSPI pull-up bit */
#define LL_PWR_XSPI_PULLUP_PB1         PWR_XSPIPUCR_XSPIPB1_PU    /*!< Port PB1 XSPI pull-up bit */
#define LL_PWR_XSPI_PULLUP_PB2         PWR_XSPIPUCR_XSPIPB2_PU    /*!< Port PB2 XSPI pull-up bit */
#define LL_PWR_XSPI_PULLUP_PD0         PWR_XSPIPUCR_XSPIPD0_PU    /*!< Port PD0 XSPI pull-up bit */
#define LL_PWR_XSPI_PULLUP_PD1         PWR_XSPIPUCR_XSPIPD1_PU    /*!< Port PD1 XSPI pull-up bit */
#define LL_PWR_XSPI_PULLUP_PD2         PWR_XSPIPUCR_XSPIPD2_PU    /*!< Port PD2 XSPI pull-up bit */
#define LL_PWR_XSPI_PULLUP_PD3         PWR_XSPIPUCR_XSPIPD3_PU    /*!< Port PD3 XSPI pull-up bit */
#define LL_PWR_XSPI_PULLUP_PG10        PWR_XSPIPUCR_XSPIPG10_PU   /*!< Port PG10 XSPI pull-up bit */
/**
  * @}
  */


/** @defgroup PWR_LL_EC_XSPI_PULLDOWN XSPI Pull-Down Pins
  * @{
  */
#define LL_PWR_XSPI_PULLDOWN_PH0         PWR_XSPIPDCR_XSPIPH0_PD    /*!< Port PH0 XSPI pull-down bit */
#define LL_PWR_XSPI_PULLDOWN_PH1         PWR_XSPIPDCR_XSPIPH1_PD    /*!< Port PH1 XSPI pull-down bit */
#define LL_PWR_XSPI_PULLDOWN_PF2         PWR_XSPIPDCR_XSPIPF2_PD    /*!< Port PF2 XSPI pull-down bit */
#define LL_PWR_XSPI_PULLDOWN_PA0         PWR_XSPIPDCR_XSPIPA0_PD    /*!< Port PA0 XSPI pull-down bit */
#define LL_PWR_XSPI_PULLDOWN_PA2         PWR_XSPIPDCR_XSPIPA2_PD    /*!< Port PA2 XSPI pull-down bit */
#define LL_PWR_XSPI_PULLDOWN_PA3         PWR_XSPIPDCR_XSPIPA3_PD    /*!< Port PA3 XSPI pull-down bit */
#define LL_PWR_XSPI_PULLDOWN_PA4         PWR_XSPIPDCR_XSPIPA4_PD    /*!< Port PA4 XSPI pull-down bit */
#define LL_PWR_XSPI_PULLDOWN_PA5         PWR_XSPIPDCR_XSPIPA5_PD    /*!< Port PA5 XSPI pull-down bit */
#define LL_PWR_XSPI_PULLDOWN_PB1         PWR_XSPIPDCR_XSPIPB1_PD    /*!< Port PB1 XSPI pull-down bit */
#define LL_PWR_XSPI_PULLDOWN_PB2         PWR_XSPIPDCR_XSPIPB2_PD    /*!< Port PB2 XSPI pull-down bit */
#define LL_PWR_XSPI_PULLDOWN_PD0         PWR_XSPIPDCR_XSPIPD0_PD    /*!< Port PD0 XSPI pull-down bit */
#define LL_PWR_XSPI_PULLDOWN_PD1         PWR_XSPIPDCR_XSPIPD1_PD    /*!< Port PD1 XSPI pull-down bit */
#define LL_PWR_XSPI_PULLDOWN_PD2         PWR_XSPIPDCR_XSPIPD2_PD    /*!< Port PD2 XSPI pull-down bit */
#define LL_PWR_XSPI_PULLDOWN_PD3         PWR_XSPIPDCR_XSPIPD3_PD    /*!< Port PD3 XSPI pull-down bit */
#define LL_PWR_XSPI_PULLDOWN_PG10        PWR_XSPIPDCR_XSPIPG10_PD   /*!< Port PG10 XSPI pull-down bit */
/**
  * @}
  */

/**
  * @}
  */
/* Exported macro ---------------------------------------------------------------------------------------------------*/
/** @defgroup PWR_LL_Exported_Macros PWR Exported Macros
  * @{
  */

/** @defgroup PWR_LL_EM_WRITE_READ Common write and read registers Macros
  * @{
  */

/**
  * @brief  Write a value in PWR register.
  * @param  reg      Register to be written.
  * @param  value    Value to be written in the register.
  */
#define LL_PWR_WRITE_REG(reg, value) STM32_WRITE_REG((PWR)->reg, (value))

/**
  * @brief  Read a value in PWR register.
  * @param  reg      Register to be read.
  * @retval Register value
  */
#define LL_PWR_READ_REG(reg) STM32_READ_REG((PWR)->reg)
/**
  * @}
  */

/**
  * @}
  */
/* Exported functions -----------------------------------------------------------------------------------------------*/
/** @defgroup PWR_LL_Exported_Functions PWR Exported Functions
  * @{
  */

/** @defgroup PWR_LL_EF_Configuration PWR Configuration
  * @{
  */

/**
  * @brief  Enable Power Voltage Detector.
  * @rmtoll
  *   CR1        PVDE            LL_PWR_EnablePVD
  */
__STATIC_INLINE void LL_PWR_EnablePVD(void)
{
  STM32_SET_BIT(PWR->CR1, PWR_CR1_PVDE);
}

/**
  * @brief  Disable Power Voltage Detector.
  * @rmtoll
  *   CR1        PVDE            LL_PWR_DisablePVD
  */
__STATIC_INLINE void LL_PWR_DisablePVD(void)
{
  STM32_CLEAR_BIT(PWR->CR1, PWR_CR1_PVDE);
}

/**
  * @brief  Check if Power Voltage Detector is enabled.
  * @rmtoll
  *   CR1        PVDE            LL_PWR_IsEnabledPVD
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsEnabledPVD(void)
{
  return ((STM32_READ_BIT(PWR->CR1, PWR_CR1_PVDE) == (PWR_CR1_PVDE)) ? 1UL : 0UL);
}

/**
  * @brief  Configure the voltage threshold detected by the Power Voltage Detector.
  * @rmtoll
  *   CR1        PLS             LL_PWR_SetPVDLevel
  * @param  pvdlevel This parameter can be one of the following values:
  *         @arg @ref LL_PWR_PVDLEVEL_1
  *         @arg @ref LL_PWR_PVDLEVEL_2
  *         @arg @ref LL_PWR_PVDLEVEL_3
  *         @arg @ref LL_PWR_PVDLEVEL_4
  *         @arg @ref LL_PWR_PVDLEVEL_5
  *         @arg @ref LL_PWR_PVDLEVEL_6
  *         @arg @ref LL_PWR_PVDLEVEL_7
  *         @arg @ref LL_PWR_PVDLEVEL_8
  */
__STATIC_INLINE void LL_PWR_SetPVDLevel(uint32_t pvdlevel)
{
  STM32_MODIFY_REG(PWR->CR1, PWR_CR1_PLS, pvdlevel);
}

/**
  * @brief  Get the voltage threshold detection.
  * @rmtoll
  *   CR1        PLS             LL_PWR_GetPVDLevel
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_PWR_PVDLEVEL_1
  *         @arg @ref LL_PWR_PVDLEVEL_2
  *         @arg @ref LL_PWR_PVDLEVEL_3
  *         @arg @ref LL_PWR_PVDLEVEL_4
  *         @arg @ref LL_PWR_PVDLEVEL_5
  *         @arg @ref LL_PWR_PVDLEVEL_6
  *         @arg @ref LL_PWR_PVDLEVEL_7
  *         @arg @ref LL_PWR_PVDLEVEL_8
  */
__STATIC_INLINE uint32_t LL_PWR_GetPVDLevel(void)
{
  return STM32_READ_BIT(PWR->CR1, PWR_CR1_PLS);
}

/**
  * @brief  Enable access to the backup domain.
  * @rmtoll
  *   CR1        DBP             LL_PWR_DisableBackupDomainWriteProtection
  */
__STATIC_INLINE void LL_PWR_DisableBackupDomainWriteProtection(void)
{
  STM32_SET_BIT(PWR->CR1, PWR_CR1_DBP);
}

/**
  * @brief  Disable access to the backup domain.
  * @rmtoll
  *   CR1        DBP             LL_PWR_EnableBackupDomainWriteProtection
  */
__STATIC_INLINE void LL_PWR_EnableBackupDomainWriteProtection(void)
{
  STM32_CLEAR_BIT(PWR->CR1, PWR_CR1_DBP);
}

/**
  * @brief  Check if the backup domain is enabled.
  * @rmtoll
  *   CR1        DBP             LL_PWR_IsEnabledBackupWriteProtection
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsEnabledBackupWriteProtection(void)
{
  return ((STM32_READ_BIT(PWR->CR1, PWR_CR1_DBP) == (PWR_CR1_DBP)) ? 0UL : 1UL);
}

/**
  * @brief  Enable the Flash low-power mode in Stop Mode.
  * @rmtoll
  *   CR1        FLPS            LL_PWR_EnableFlashLowPWRMode
  */
__STATIC_INLINE void LL_PWR_EnableFlashLowPWRMode(void)
{
  STM32_SET_BIT(PWR->CR1, PWR_CR1_FLPS);
}

/**
  * @brief  Disable the Flash low-power mode in Stop Mode.
  * @rmtoll
  *   CR1        FLPS            LL_PWR_DisableFlashLowPWRMode
  */
__STATIC_INLINE void LL_PWR_DisableFlashLowPWRMode(void)
{
  STM32_CLEAR_BIT(PWR->CR1, PWR_CR1_FLPS);
}

/**
  * @brief  Check if the Flash low-power mode in Stop Mode is enabled.
  * @rmtoll
  *   CR1        FLPS            LL_PWR_IsEnabledFlashLowPWRMode
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsEnabledFlashLowPWRMode(void)
{
  return ((STM32_READ_BIT(PWR->CR1, PWR_CR1_FLPS) == (PWR_CR1_FLPS)) ? 1UL : 0UL);
}

/**
  * @brief  Enable the Analog Voltage Booster.
  * @rmtoll
  *   CR1        BOOSTE          LL_PWR_EnableAnalogBooster
  */
__STATIC_INLINE void LL_PWR_EnableAnalogBooster(void)
{
  STM32_SET_BIT(PWR->CR1, PWR_CR1_BOOSTE);
}

/**
  * @brief  Disable the Analog Voltage Booster.
  * @rmtoll
  *   CR1        BOOSTE          LL_PWR_DisableAnalogBooster
  */
__STATIC_INLINE void LL_PWR_DisableAnalogBooster(void)
{
  STM32_CLEAR_BIT(PWR->CR1, PWR_CR1_BOOSTE);
}

/**
  * @brief  Check if the Analog Voltage Booster is enabled.
  * @rmtoll
  *   CR1        BOOSTE          LL_PWR_IsEnabledAnalogBooster
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsEnabledAnalogBooster(void)
{
  return ((STM32_READ_BIT(PWR->CR1, PWR_CR1_BOOSTE) == (PWR_CR1_BOOSTE)) ? 1UL : 0UL);
}

/**
  * @brief  Enable the Analog Voltage Ready.
  * @rmtoll
  *   CR1        AVDREADY        LL_PWR_EnableAnalogVoltageReady
  */
__STATIC_INLINE void LL_PWR_EnableAnalogVoltageReady(void)
{
  STM32_SET_BIT(PWR->CR1, PWR_CR1_AVDREADY);
}

/**
  * @brief  Disable the Analog Voltage Ready.
  * @rmtoll
  *   CR1        AVDREADY        LL_PWR_DisableAnalogVoltageReady
  */
__STATIC_INLINE void LL_PWR_DisableAnalogVoltageReady(void)
{
  STM32_CLEAR_BIT(PWR->CR1, PWR_CR1_AVDREADY);
}

/**
  * @brief  Check if the Analog Voltage Ready is enabled.
  * @rmtoll
  *   CR1        AVDREADY        LL_PWR_IsEnabledAnalogVoltageReady
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsEnabledAnalogVoltageReady(void)
{
  return ((STM32_READ_BIT(PWR->CR1, PWR_CR1_AVDREADY) == (PWR_CR1_AVDREADY)) ? 1UL : 0UL);
}

/**
  * @brief  Enable Analog Power Voltage Monitor.
  * @rmtoll
  *   CR1        AVDEN           LL_PWR_EnableAVD
  */
__STATIC_INLINE void LL_PWR_EnableAVD(void)
{
  STM32_SET_BIT(PWR->CR1, PWR_CR1_AVDEN);
}

/**
  * @brief  Disable Analog Power Voltage Monitor.
  * @rmtoll
  *   CR1        AVDEN           LL_PWR_DisableAVD
  */
__STATIC_INLINE void LL_PWR_DisableAVD(void)
{
  STM32_CLEAR_BIT(PWR->CR1, PWR_CR1_AVDEN);
}

/**
  * @brief  Check if Analog Power Voltage Monitor is enabled.
  * @rmtoll
  *   CR1        AVDEN           LL_PWR_IsEnabledAVD
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsEnabledAVD(void)
{
  return ((STM32_READ_BIT(PWR->CR1, PWR_CR1_AVDEN) == (PWR_CR1_AVDEN)) ? 1UL : 0UL);
}

/**
  * @brief  Set the Analog Voltage detector level.
  * @rmtoll
  *   CR1        ALS             LL_PWR_SetAVDLevel
  * @param  avdLevel This parameter can be one of the following values:
  *         @arg @ref LL_PWR_AVDLEVEL_1
  *         @arg @ref LL_PWR_AVDLEVEL_2
  *         @arg @ref LL_PWR_AVDLEVEL_3
  *         @arg @ref LL_PWR_AVDLEVEL_4
  */
__STATIC_INLINE void LL_PWR_SetAVDLevel(uint32_t avdLevel)
{
  STM32_MODIFY_REG(PWR->CR1, PWR_CR1_ALS, avdLevel);
}

/**
  * @brief  Get the Analog Voltage detector level selected.
  * @rmtoll
  *   CR1        ALS             LL_PWR_GetAVDLevel
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_PWR_AVDLEVEL_1
  *         @arg @ref LL_PWR_AVDLEVEL_2
  *         @arg @ref LL_PWR_AVDLEVEL_3
  *         @arg @ref LL_PWR_AVDLEVEL_4
  */
__STATIC_INLINE uint32_t LL_PWR_GetAVDLevel(void)
{
  return STM32_READ_BIT(PWR->CR1, PWR_CR1_ALS);
}

/**
  * @brief  Enable Backup Regulator.
  * @rmtoll
  *   CSR1       BREN            LL_PWR_EnableBkULL_PWR_EnableBackupRegulatorpRegulator
  * @note When set, the Backup Regulator (used to maintain backup SRAM content in Standby and
  *       VBAT modes) is enabled. If BRE is reset, the backup Regulator is switched off. The backup
  *       SRAM can still be used but its content will be lost in the Standby and VBAT modes. Once set,
  *       the application must wait that the Backup Regulator Ready flag (BRR) is set to indicate that
  *       the data written into the RAM will be maintained in the Standby and VBAT modes.
  */
__STATIC_INLINE void LL_PWR_EnableBackupRegulator(void)
{
  STM32_SET_BIT(PWR->CSR1, PWR_CSR1_BREN);
}

/**
  * @brief  Disable Backup Regulator.
  * @rmtoll
  *   CSR1       BREN            LL_PWR_DisableBackupRegulator
  */
__STATIC_INLINE void LL_PWR_DisableBackupRegulator(void)
{
  STM32_CLEAR_BIT(PWR->CSR1, PWR_CSR1_BREN);
}

/**
  * @brief  Check if the backup Regulator is enabled.
  * @rmtoll
  *   CSR1       BREN            LL_PWR_IsEnabledBackupRegulator
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsEnabledBackupRegulator(void)
{
  return ((STM32_READ_BIT(PWR->CSR1, PWR_CSR1_BREN) == (PWR_CSR1_BREN)) ? 1UL : 0UL);
}

/**
  * @brief  Enable VBAT and Temperature monitoring.
  * @rmtoll
  *   CSR1       MONEN           LL_PWR_EnableMonitoring
  */
__STATIC_INLINE void LL_PWR_EnableMonitoring(void)
{
  STM32_SET_BIT(PWR->CSR1, PWR_CSR1_MONEN);
}

/**
  * @brief  Disable VBAT and Temperature monitoring.
  * @rmtoll
  *   CSR1       MONEN           LL_PWR_DisableMonitoring
  */
__STATIC_INLINE void LL_PWR_DisableMonitoring(void)
{
  STM32_CLEAR_BIT(PWR->CSR1, PWR_CSR1_MONEN);
}

/**
  * @brief  Check if the VBAT and Temperature monitoring is enabled.
  * @rmtoll
  *   CSR1       MONEN           LL_PWR_IsEnabledMonitoring
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsEnabledMonitoring(void)
{
  return ((STM32_READ_BIT(PWR->CSR1, PWR_CSR1_MONEN) == (PWR_CSR1_MONEN)) ? 1UL : 0UL);
}

/**
  * @brief  Enable power management unit bypass.
  * @param  None.
  * @note   Once set, only a complete power cycle can clear this bit. Every other write access will be ignored.
  * @note   This API or LL_PWR_EnableInternalRegulator must be called at startup.
  * @rmtoll CSR2          BYPASS     LL_PWR_EnableBypass
  */
__STATIC_INLINE void LL_PWR_EnableBypass(void)
{
  STM32_SET_BIT(PWR->CSR2, PWR_CSR2_BYPASS);
}

/**
  * @brief  Enable Internal regulator, Vcore supplied by internal regulator LDO SMPS.
  * @param  None.
  * @note   Once PWR_CSR2_BYPASS bit reset, only a complete power cycle can allow this bit to be written.
  * @note   Every write access will be ignored.
  * @note   This API or LL_PWR_EnableBypass must be called at startup.
  * @rmtoll CSR2          BYPASS     LL_PWR_DisableBypass
  */
__STATIC_INLINE void LL_PWR_EnableInternalRegulator(void)
{
  STM32_CLEAR_BIT(PWR->CSR2, PWR_CSR2_BYPASS);
}

/**
  * @brief  Check if the PWR management unit bypass is enabled or disabled.
  * @rmtoll CSR2          BYPASS     LL_PWR_IsEnabledBypass
  * @param  None.
  * @retval 0 if disabled, 1 if enabled.
  */
__STATIC_INLINE uint32_t LL_PWR_IsEnabledBypass(void)
{
  return ((STM32_READ_BIT(PWR->CSR2, PWR_CSR2_BYPASS) == PWR_CSR2_BYPASS) ? 1UL : 0UL);
}

/**
  * @brief  Get the LDO supply status.
  * @rmtoll CSR2          LDOEN     LL_PWR_IsEnabledLDOSupply
  * @param  None.
  * @retval 0 if disabled, 1 if enabled.
  */
__STATIC_INLINE uint32_t LL_PWR_IsEnabledLDOSupply(void)
{
  return ((STM32_READ_BIT(PWR->CSR2, PWR_CSR2_LDOEN) == PWR_CSR2_LDOEN) ? 1UL : 0UL);
}

/**
  * @brief  Get the SMPS supply status.
  * @rmtoll CSR2          SMPSEN     LL_PWR_IsEnabledLDOSupply
  * @param  None.
  * @retval 0 if disabled, 1 if enabled.
  */
__STATIC_INLINE uint32_t LL_PWR_IsEnabledSMPSSupply(void)
{
  return ((STM32_READ_BIT(PWR->CSR2, PWR_CSR2_SMPSEN) == PWR_CSR2_SMPSEN) ? 1UL : 0UL);
}

/**
  * @brief  Enable VBAT battery charging.
  * @rmtoll
  *   CSR2       VBE             LL_PWR_EnableBatteryCharging
  */
__STATIC_INLINE void LL_PWR_EnableBatteryCharging(void)
{
  STM32_SET_BIT(PWR->CSR2, PWR_CSR2_VBE);
}

/**
  * @brief  Disable VBAT battery charging.
  * @rmtoll
  *   CSR2       VBE             LL_PWR_DisableBatteryCharging
  */
__STATIC_INLINE void LL_PWR_DisableBatteryCharging(void)
{
  STM32_CLEAR_BIT(PWR->CSR2, PWR_CSR2_VBE);
}

/**
  * @brief  Check if VBAT battery charging is enabled.
  * @rmtoll
  *   CSR2       VBE             LL_PWR_IsEnabledBatteryCharging
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsEnabledBatteryCharging(void)
{
  return ((STM32_READ_BIT(PWR->CSR2, PWR_CSR2_VBE) == (PWR_CSR2_VBE)) ? 1UL : 0UL);
}

/**
  * @brief  Set the Battery charge resistor impedance.
  * @rmtoll
  *   CSR2       VBRS            LL_PWR_SetBattChargResistor
  * @param  resistor This parameter can be one of the following values:
  *         @arg @ref LL_PWR_BATT_CHARG_RESISTOR_5K
  *         @arg @ref LL_PWR_BATT_CHARG_RESISTOR_1_5K
  */
__STATIC_INLINE void LL_PWR_SetBattChargResistor(uint32_t resistor)
{
  STM32_MODIFY_REG(PWR->CSR2, PWR_CSR2_VBRS, resistor);
}

/**
  * @brief  Get the Battery charge resistor impedance.
  * @rmtoll
  *   CSR2       VBRS            LL_PWR_GetBattChargResistor
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_PWR_BATT_CHARG_RESISTOR_5K
  *         @arg @ref LL_PWR_BATT_CHARG_RESISTOR_1_5K
  */
__STATIC_INLINE uint32_t LL_PWR_GetBattChargResistor(void)
{
  return (STM32_READ_BIT(PWR->CSR2, PWR_CSR2_VBRS));
}

/**
  * @brief Enable UCPD configuration memorization in Standby.
  * @rmtoll
  *   UCPDR      UCPD_STBY       LL_PWR_EnableUCPDRetentionStandbyMode
  * @note  This function must be called just before entering Standby mode when using UCPD.
  */
__STATIC_INLINE void LL_PWR_EnableUCPDRetentionStandbyMode(void)
{
  /* Memorize UCPD configuration when entering standby mode */
  STM32_SET_BIT(PWR->UCPDR, PWR_UCPDR_UCPD_STBY);
}

/**
  * @brief Disable UCPD configuration memorization in Standby.
  * @rmtoll
  *   UCPDR      UCPD_STBY       LL_PWR_DisableUCPDRetentionStandbyMode
  * @note  This function must be called on exiting the Standby mode and before any UCPD
  *        configuration update.
  */
__STATIC_INLINE void LL_PWR_DisableUCPDRetentionStandbyMode(void)
{
  STM32_CLEAR_BIT(PWR->UCPDR, PWR_UCPDR_UCPD_STBY);
}

/**
  * @brief  Check if the UCPD configuration memorization in Standby is enabled.
  * @rmtoll
  *   UCPDR      UCPD_STBY       LL_PWR_IsEnabledUCPDRetentionStandbyMode
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsEnabledUCPDRetentionStandbyMode(void)
{
  return ((STM32_READ_BIT(PWR->UCPDR, PWR_UCPDR_UCPD_STBY) == (PWR_UCPDR_UCPD_STBY)) ? 1UL : 0UL);
}

/**
  * @brief  Enable the UCPD dead battery behavior.
  * @rmtoll
  *   UCPDR       UCPD_DBDIS      LL_PWR_EnableUCPDDeadBattery
  */
__STATIC_INLINE void LL_PWR_EnableUCPDDeadBattery(void)
{
  STM32_CLEAR_BIT(PWR->UCPDR, PWR_UCPDR_UCPD_DBDIS);
}

/**
  * @brief  Disable the UCPD dead battery behavior.
  * @rmtoll
  *   UCPDR       UCPD_DBDIS      LL_PWR_DisableUCPDDeadBattery
  */
__STATIC_INLINE void LL_PWR_DisableUCPDDeadBattery(void)
{
  STM32_SET_BIT(PWR->UCPDR, PWR_UCPDR_UCPD_DBDIS);
}

/**
  * @brief  Check if the UCPD dead battery behavior is enabled.
  * @warning when PWR_UCPDR_UCPD_DBDIS bit is set UCPD dead battery disabled
  * @rmtoll
  *   UCPDR       UCPD_DBDIS      LL_PWR_IsEnabledUCPDDeadBattery
  * @retval 1 if Enable 0 if disable.
  */
__STATIC_INLINE uint32_t LL_PWR_IsEnabledUCPDDeadBattery(void)
{
  return ((STM32_READ_BIT(PWR->UCPDR, PWR_UCPDR_UCPD_DBDIS) == (PWR_UCPDR_UCPD_DBDIS)) ? 0UL : 1UL);
}

/**
  * @brief  Set system power mode.
  * @rmtoll
  *   CSR3       PDDS            LL_PWR_SetPowerMode
  * @param  mode : This parameter can be one of the following values:
  *         @arg @ref LL_PWR_STOP_MODE
  *         @arg @ref LL_PWR_STANDBY_MODE
  */
__STATIC_INLINE void LL_PWR_SetPowerMode(uint32_t mode)
{
  STM32_MODIFY_REG(PWR->CSR3, PWR_CSR3_PDDS, mode);
}

/**
  * @brief  Get system power mode.
  * @rmtoll
  *   CSR3       PDDS            LL_PWR_GetPowerMode
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_PWR_STOP_MODE
  *         @arg @ref LL_PWR_STANDBY_MODE
  */
__STATIC_INLINE uint32_t LL_PWR_GetPowerMode(void)
{
  return (STM32_READ_BIT(PWR->CSR3, PWR_CSR3_PDDS));
}

/**
  * @brief  Set the main internal Regulator output voltage.
  * @rmtoll
  *   CSR4       VOS             LL_PWR_SetRegulatorVoltageScaling
  * @param  voltagescaling This parameter can be one of the following values:
  *         @arg @ref LL_PWR_REGU_VOLT_SCALE_0
  *         @arg @ref LL_PWR_REGU_VOLT_SCALE_1
  *         @arg @ref LL_PWR_REGU_VOLT_SCALE_2
  */
__STATIC_INLINE void LL_PWR_SetRegulatorVoltageScaling(uint32_t voltagescaling)
{
  STM32_MODIFY_REG(PWR->CSR4, PWR_CSR4_VOS, voltagescaling);
}

/**
  * @brief  Get the main internal Regulator output voltage.
  * @rmtoll
  *   CSR4       VOS             LL_PWR_GetRegulatorVoltageScaling
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_PWR_REGU_VOLT_SCALE_0
  *         @arg @ref LL_PWR_REGU_VOLT_SCALE_1
  *         @arg @ref LL_PWR_REGU_VOLT_SCALE_2
  */
__STATIC_INLINE uint32_t LL_PWR_GetRegulatorVoltageScaling(void)
{
  return (uint32_t)(STM32_READ_BIT(PWR->CSR4, PWR_CSR4_VOS));
}

/**
  * @brief  Get current voltage scaling applied to VCORE.
  * @rmtoll
  *   SR1            ACTVOS[1:0]          LL_PWR_GetActiveRegulatorVoltageScaling
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_PWR_ACTIVE_VOLT_SCALE_0
  *         @arg @ref LL_PWR_ACTIVE_VOLT_SCALE_1
  *         @arg @ref LL_PWR_ACTIVE_VOLT_SCALE_2
  */
__STATIC_INLINE uint32_t LL_PWR_GetActiveRegulatorVoltageScaling(void)
{
  return (STM32_READ_BIT(PWR->SR1, PWR_SR1_ACTVOS));
}

/**
  * @brief  Set the internal Regulator output voltage in STOP mode.
  * @rmtoll
  *   CR1        SVOS            LL_PWR_SetStopRegulatorVoltageScaling
  * @param  voltagescaling This parameter can be one of the following values:
  *         @arg @ref LL_PWR_REGU_STOP_VOLT_SCALE_HIGH
  *         @arg @ref LL_PWR_REGU_STOP_VOLT_SCALE_LOW
  */
__STATIC_INLINE void LL_PWR_SetStopRegulatorVoltageScaling(uint32_t voltagescaling)
{
  STM32_MODIFY_REG(PWR->CR1, PWR_CR1_SVOS, voltagescaling);
}

/**
  * @brief  Get the internal Regulator output voltage in STOP mode.
  * @rmtoll
  *   CR1        SVOS            LL_PWR_GetStopRegulatorVoltageScaling
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_PWR_REGU_STOP_VOLT_SCALE_HIGH
  *         @arg @ref LL_PWR_REGU_STOP_VOLT_SCALE_LOW
  */
__STATIC_INLINE uint32_t LL_PWR_GetStopRegulatorVoltageScaling(void)
{
  return STM32_READ_BIT(PWR->CR1, PWR_CR1_SVOS);
}

/**
  * @brief  Enable the WakeUp PINx functionality.
  * @rmtoll
  *   WKUPEPR    WKUPENx         LL_PWR_EnableWakeUpPin
  * @param  wakeup_pin This parameter can be one of the following values:
  *         @arg @ref LL_PWR_WAKEUP_PIN_1
  *         @arg @ref LL_PWR_WAKEUP_PIN_2
  *         @arg @ref LL_PWR_WAKEUP_PIN_3
  *         @arg @ref LL_PWR_WAKEUP_PIN_4
  *         @arg @ref LL_PWR_WAKEUP_PIN_5
  *         @arg @ref LL_PWR_WAKEUP_PIN_6
  *         @arg @ref LL_PWR_WAKEUP_PIN_7
  *         @arg @ref LL_PWR_WAKEUP_PIN_8
  *         @arg @ref LL_PWR_WAKEUP_PIN_ALL
  */
__STATIC_INLINE void LL_PWR_EnableWakeUpPin(uint32_t wakeup_pin)
{
  STM32_SET_BIT(PWR->WKUPEPR, wakeup_pin);
}

/**
  * @brief  Disable the WakeUp PINx functionality.
  * @rmtoll
  *   WKUPEPR   WKUPENx          LL_PWR_DisableWakeUpPin
  * @param  wakeup_pin This parameter can be one of the following values:
  *         @arg @ref LL_PWR_WAKEUP_PIN_1
  *         @arg @ref LL_PWR_WAKEUP_PIN_2
  *         @arg @ref LL_PWR_WAKEUP_PIN_3
  *         @arg @ref LL_PWR_WAKEUP_PIN_4
  *         @arg @ref LL_PWR_WAKEUP_PIN_5
  *         @arg @ref LL_PWR_WAKEUP_PIN_6
  *         @arg @ref LL_PWR_WAKEUP_PIN_7
  *         @arg @ref LL_PWR_WAKEUP_PIN_8
  *         @arg @ref LL_PWR_WAKEUP_PIN_ALL
  */
__STATIC_INLINE void LL_PWR_DisableWakeUpPin(uint32_t wakeup_pin)
{
  STM32_CLEAR_BIT(PWR->WKUPEPR, wakeup_pin);
}

/**
  * @brief  Check if the WakeUp PINx functionality is enabled.
  * @rmtoll
  *   WKUPEPR    WKUPENx         LL_PWR_IsEnabledWakeUpPin
  * @param  wakeup_pin This parameter can be one of the following values:
  *         @arg @ref LL_PWR_WAKEUP_PIN_1
  *         @arg @ref LL_PWR_WAKEUP_PIN_2
  *         @arg @ref LL_PWR_WAKEUP_PIN_3
  *         @arg @ref LL_PWR_WAKEUP_PIN_4
  *         @arg @ref LL_PWR_WAKEUP_PIN_5
  *         @arg @ref LL_PWR_WAKEUP_PIN_6
  *         @arg @ref LL_PWR_WAKEUP_PIN_7
  *         @arg @ref LL_PWR_WAKEUP_PIN_8
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsEnabledWakeUpPin(uint32_t wakeup_pin)
{
  return ((STM32_READ_BIT(PWR->WKUPEPR, wakeup_pin) == (wakeup_pin)) ? 1UL : 0UL);
}

/**
  * @brief  Set the Wake-Up pin polarity low for the event detection.
  * @rmtoll
  *   WKUPEPR    WKUPPx          LL_PWR_SetWakeUpPinPolarityLow
  * @param  wakeup_pin This parameter can be one of the following values:
  *         @arg @ref LL_PWR_WAKEUP_PIN_1
  *         @arg @ref LL_PWR_WAKEUP_PIN_2
  *         @arg @ref LL_PWR_WAKEUP_PIN_3
  *         @arg @ref LL_PWR_WAKEUP_PIN_4
  *         @arg @ref LL_PWR_WAKEUP_PIN_5
  *         @arg @ref LL_PWR_WAKEUP_PIN_6
  *         @arg @ref LL_PWR_WAKEUP_PIN_7
  *         @arg @ref LL_PWR_WAKEUP_PIN_8
  *         @arg @ref LL_PWR_WAKEUP_PIN_ALL
  */
__STATIC_INLINE void LL_PWR_SetWakeUpPinPolarityLow(uint32_t wakeup_pin)
{
  STM32_SET_BIT(PWR->WKUPEPR, (wakeup_pin << PWR_WKUPEPR_WKUPP1_Pos));
}

/**
  * @brief  Set the Wake-Up pin polarity high for the event detection.
  * @rmtoll
  *   WKUPEPR    WKUPPx          LL_PWR_SetWakeUpPinPolarityHigh
  * @param  wakeup_pin This parameter can be one of the following values:
  *         @arg @ref LL_PWR_WAKEUP_PIN_1
  *         @arg @ref LL_PWR_WAKEUP_PIN_2
  *         @arg @ref LL_PWR_WAKEUP_PIN_3
  *         @arg @ref LL_PWR_WAKEUP_PIN_4
  *         @arg @ref LL_PWR_WAKEUP_PIN_5
  *         @arg @ref LL_PWR_WAKEUP_PIN_6
  *         @arg @ref LL_PWR_WAKEUP_PIN_7
  *         @arg @ref LL_PWR_WAKEUP_PIN_8
  *         @arg @ref LL_PWR_WAKEUP_PIN_ALL
  */
__STATIC_INLINE void LL_PWR_SetWakeUpPinPolarityHigh(uint32_t wakeup_pin)
{
  STM32_CLEAR_BIT(PWR->WKUPEPR, (wakeup_pin << PWR_WKUPEPR_WKUPP1_Pos));
}

/**
  * @brief  Set the wake up pin polarity low for the event detection.
  * @rmtoll
  *   WKUPEPR          WUPPx       LL_PWR_SetWakeupPinPolarity
  * @param  wakeup_pin This parameter can be one of the following values:
  *         @arg @ref LL_PWR_WAKEUP_PIN_1
  *         @arg @ref LL_PWR_WAKEUP_PIN_2
  *         @arg @ref LL_PWR_WAKEUP_PIN_3
  *         @arg @ref LL_PWR_WAKEUP_PIN_4
  *         @arg @ref LL_PWR_WAKEUP_PIN_5
  *         @arg @ref LL_PWR_WAKEUP_PIN_6
  *         @arg @ref LL_PWR_WAKEUP_PIN_7
  *         @arg @ref LL_PWR_WAKEUP_PIN_8
  * @param  polarity This parameter can be one of the following values:
  *         @arg @ref LL_PWR_WAKEUP_PIN_POLARITY_HIGH
  *         @arg @ref LL_PWR_WAKEUP_PIN_POLARITY_LOW
  */
__STATIC_INLINE void LL_PWR_SetWakeUpPinPolarity(uint32_t wakeup_pin, uint32_t polarity)
{
  STM32_MODIFY_REG(PWR->WKUPEPR, (uint32_t)(PWR_WKUPEPR_WKUPP1 << STM32_POSITION_VAL(wakeup_pin)), \
                   (uint32_t)(polarity << (PWR_WKUPEPR_WKUPP1_Pos + STM32_POSITION_VAL(wakeup_pin))));
}

/**
  * @brief  Get the wake up pin polarity for the event detection.
  * @rmtoll
  *   WKUPEPR          WUPPx       LL_PWR_GetWakeUpPinPolarity
  * @param  wakeup_pin This parameter can be one of the following values:
  *         @arg @ref LL_PWR_WAKEUP_PIN_1
  *         @arg @ref LL_PWR_WAKEUP_PIN_2
  *         @arg @ref LL_PWR_WAKEUP_PIN_3
  *         @arg @ref LL_PWR_WAKEUP_PIN_4
  *         @arg @ref LL_PWR_WAKEUP_PIN_5
  *         @arg @ref LL_PWR_WAKEUP_PIN_6
  *         @arg @ref LL_PWR_WAKEUP_PIN_7
  *         @arg @ref LL_PWR_WAKEUP_PIN_8
  * @retval State of bit (1 : polarity low or 0 : polarity high).
  */
__STATIC_INLINE uint32_t LL_PWR_GetWakeUpPinPolarity(uint32_t wakeup_pin)
{
  uint32_t mask = (uint32_t)(PWR_WKUPEPR_WKUPP1 << STM32_POSITION_VAL(wakeup_pin));
  uint32_t bit_set = STM32_READ_BIT(PWR->WKUPEPR, mask);

  return (bit_set != 0U) ? 1UL : 0UL;
}

/**
  * @brief  Set the Wake-Up pin Pull None.
  * @rmtoll
  *   WKUPEPR    WKUPPUPDx       LL_PWR_SetWakeUpPinPullNone
  * @param  wakeup_pin This parameter can be one of the following values:
  *         @arg @ref LL_PWR_WAKEUP_PIN_1
  *         @arg @ref LL_PWR_WAKEUP_PIN_2
  *         @arg @ref LL_PWR_WAKEUP_PIN_3
  *         @arg @ref LL_PWR_WAKEUP_PIN_4
  *         @arg @ref LL_PWR_WAKEUP_PIN_5
  *         @arg @ref LL_PWR_WAKEUP_PIN_6
  *         @arg @ref LL_PWR_WAKEUP_PIN_7
  *         @arg @ref LL_PWR_WAKEUP_PIN_8
  */
__STATIC_INLINE void LL_PWR_SetWakeUpPinPullNone(uint32_t wakeup_pin)
{
  uint32_t clear = (PWR_WKUPEPR_WKUPPUPD1 <<                                             \
                    ((LL_PWR_WAKEUP_PINS_PULL_SHIFT_OFFSET * STM32_POSITION_VAL(wakeup_pin)) \
                     & LL_PWR_WAKEUP_PINS_MAX_SHIFT_MASK));

  uint32_t set =                                                                                              \
      (LL_PWR_WAKEUP_PIN_PULL_NO <<                                                                           \
       ((PWR_WKUPEPR_WKUPPUPD1_Pos + (LL_PWR_WAKEUP_PINS_PULL_SHIFT_OFFSET * STM32_POSITION_VAL(wakeup_pin))) \
        & LL_PWR_WAKEUP_PINS_MAX_SHIFT_MASK));

  STM32_MODIFY_REG(PWR->WKUPEPR, clear, set);
}

/**
  * @brief  Set the Wake-Up pin Pull Up.
  * @rmtoll
  *   WKUPEPR    WKUPPUPDx       LL_PWR_SetWakeUpPinPullUp
  * @param  wakeup_pin This parameter can be one of the following values:
  *         @arg @ref LL_PWR_WAKEUP_PIN_1
  *         @arg @ref LL_PWR_WAKEUP_PIN_2
  *         @arg @ref LL_PWR_WAKEUP_PIN_3
  *         @arg @ref LL_PWR_WAKEUP_PIN_4
  *         @arg @ref LL_PWR_WAKEUP_PIN_5
  *         @arg @ref LL_PWR_WAKEUP_PIN_6
  *         @arg @ref LL_PWR_WAKEUP_PIN_7
  *         @arg @ref LL_PWR_WAKEUP_PIN_8
  */
__STATIC_INLINE void LL_PWR_SetWakeUpPinPullUp(uint32_t wakeup_pin)
{
  uint32_t clear = (PWR_WKUPEPR_WKUPPUPD1 <<                                             \
                    ((LL_PWR_WAKEUP_PINS_PULL_SHIFT_OFFSET * STM32_POSITION_VAL(wakeup_pin))    \
                     & LL_PWR_WAKEUP_PINS_MAX_SHIFT_MASK));

  uint32_t set =                                                                                              \
      (LL_PWR_WAKEUP_PIN_PULL_UP <<                                                                           \
       ((PWR_WKUPEPR_WKUPPUPD1_Pos + (LL_PWR_WAKEUP_PINS_PULL_SHIFT_OFFSET * STM32_POSITION_VAL(wakeup_pin))) \
        & LL_PWR_WAKEUP_PINS_MAX_SHIFT_MASK));

  STM32_MODIFY_REG(PWR->WKUPEPR, clear, set);
}

/**
  * @brief  Set the Wake-Up pin Pull Down.
  * @rmtoll
  *   WKUPEPR    WKUPPUPDx       LL_PWR_SetWakeUpPinPullDown
  * @param  wakeup_pin This parameter can be one of the following values:
  *         @arg @ref LL_PWR_WAKEUP_PIN_1
  *         @arg @ref LL_PWR_WAKEUP_PIN_2
  *         @arg @ref LL_PWR_WAKEUP_PIN_3
  *         @arg @ref LL_PWR_WAKEUP_PIN_4
  *         @arg @ref LL_PWR_WAKEUP_PIN_5
  *         @arg @ref LL_PWR_WAKEUP_PIN_6
  *         @arg @ref LL_PWR_WAKEUP_PIN_7
  *         @arg @ref LL_PWR_WAKEUP_PIN_8
  */
__STATIC_INLINE void LL_PWR_SetWakeUpPinPullDown(uint32_t wakeup_pin)
{
  uint32_t clear = (PWR_WKUPEPR_WKUPPUPD1 <<                                          \
                    ((LL_PWR_WAKEUP_PINS_PULL_SHIFT_OFFSET * STM32_POSITION_VAL(wakeup_pin)) \
                     & LL_PWR_WAKEUP_PINS_MAX_SHIFT_MASK));

  uint32_t set =                                                                                              \
      (LL_PWR_WAKEUP_PIN_PULL_DOWN <<                                                                         \
       ((PWR_WKUPEPR_WKUPPUPD1_Pos + (LL_PWR_WAKEUP_PINS_PULL_SHIFT_OFFSET * STM32_POSITION_VAL(wakeup_pin))) \
        & LL_PWR_WAKEUP_PINS_MAX_SHIFT_MASK));

  STM32_MODIFY_REG(PWR->WKUPEPR, clear, set);
}

/**
  * @brief  Set the Wake-Up pin pull.
  * @rmtoll
  *   WKUPEPR   WUPPUPDx       LL_PWR_SetWakeUpPinPull
  * @param  wakeup_pin This parameter can be one of the following values:
  *         @arg @ref LL_PWR_WAKEUP_PIN_1
  *         @arg @ref LL_PWR_WAKEUP_PIN_2
  *         @arg @ref LL_PWR_WAKEUP_PIN_3
  *         @arg @ref LL_PWR_WAKEUP_PIN_4
  *         @arg @ref LL_PWR_WAKEUP_PIN_5
  *         @arg @ref LL_PWR_WAKEUP_PIN_6
  *         @arg @ref LL_PWR_WAKEUP_PIN_7
  *         @arg @ref LL_PWR_WAKEUP_PIN_8
  * @param  pull This parameter can be one of the following values:
  *         @arg @ref LL_PWR_WAKEUP_PIN_PULL_NO
  *         @arg @ref LL_PWR_WAKEUP_PIN_PULL_UP
  *         @arg @ref LL_PWR_WAKEUP_PIN_PULL_DOWN
  */
__STATIC_INLINE void LL_PWR_SetWakeUpPinPull(uint32_t wakeup_pin, uint32_t pull)
{
  uint32_t clear = (PWR_WKUPEPR_WKUPPUPD1 << (LL_PWR_WAKEUP_PINS_PULL_SHIFT_OFFSET * (STM32_POSITION_VAL(wakeup_pin))));

  uint32_t set =                                                                                               \
      (pull <<                                                                                                 \
       (PWR_WKUPEPR_WKUPPUPD1_Pos + (LL_PWR_WAKEUP_PINS_PULL_SHIFT_OFFSET * (STM32_POSITION_VAL(wakeup_pin)))));

  STM32_MODIFY_REG(PWR->WKUPEPR, clear, set);
}

/**
  * @brief  Get the Wake-Up pin pull.
  * @rmtoll
  *   WKUPEPR    WKUPPUPDx       LL_PWR_GetWakeUpPinPull
  * @param  wakeup_pin This parameter can be one of the following values:
  *         @arg @ref LL_PWR_WAKEUP_PIN_1
  *         @arg @ref LL_PWR_WAKEUP_PIN_2
  *         @arg @ref LL_PWR_WAKEUP_PIN_3
  *         @arg @ref LL_PWR_WAKEUP_PIN_4
  *         @arg @ref LL_PWR_WAKEUP_PIN_5
  *         @arg @ref LL_PWR_WAKEUP_PIN_6
  *         @arg @ref LL_PWR_WAKEUP_PIN_7
  *         @arg @ref LL_PWR_WAKEUP_PIN_8
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_PWR_WAKEUP_PIN_PULL_NO
  *         @arg @ref LL_PWR_WAKEUP_PIN_PULL_UP
  *         @arg @ref LL_PWR_WAKEUP_PIN_PULL_DOWN
  */
__STATIC_INLINE uint32_t LL_PWR_GetWakeUpPinPull(uint32_t wakeup_pin)
{
  uint32_t regValue = STM32_READ_BIT(PWR->WKUPEPR,                                                             \
                                     (PWR_WKUPEPR_WKUPPUPD1 <<                                                 \
                                      ((LL_PWR_WAKEUP_PINS_PULL_SHIFT_OFFSET * STM32_POSITION_VAL(wakeup_pin)) \
                                       & LL_PWR_WAKEUP_PINS_MAX_SHIFT_MASK)));

  regValue = (regValue >>                                                                                     \
              ((PWR_WKUPEPR_WKUPPUPD1_Pos + (LL_PWR_WAKEUP_PINS_PULL_SHIFT_OFFSET * STM32_POSITION_VAL(wakeup_pin))) \
               & LL_PWR_WAKEUP_PINS_MAX_SHIFT_MASK));

  return regValue;
}

/**
  * @brief  Enable the pull-up and pull-down configuration.
  * @rmtoll
  *   APCR          APC           LL_PWR_EnablePUPDConfig
  */
__STATIC_INLINE void LL_PWR_EnablePUPDConfig(void)
{
  STM32_SET_BIT(PWR->APCR, PWR_APCR_APC);
}

/**
  * @brief  Disable the pull-up and pull-down configuration.
  * @rmtoll
  *   APCR          APC           LL_PWR_DisablePUPDConfig
  */
__STATIC_INLINE void LL_PWR_DisablePUPDConfig(void)
{
  STM32_CLEAR_BIT(PWR->APCR, PWR_APCR_APC);
}

/**
  * @brief  Check if the pull-up and pull-down configuration is enabled.
  * @rmtoll
  *   APCR          APC           LL_PWR_IsEnabledPUPDConfig
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsEnabledPUPDConfig(void)
{
  return ((STM32_READ_BIT(PWR->APCR, PWR_APCR_APC) == (PWR_APCR_APC)) ? 1UL : 0UL);
}

/**
  * @brief  Enable the I3C pull-up functionality for the specified pin.
  * @rmtoll
  *   I3CPUCR    I3CPxxx_PU      LL_PWR_EnableI3CPullUp
  * @param  i3cpullup_pin This parameter can be one of the following values:
  *         @arg @ref LL_PWR_I3C_PULLUP_PA15
  *         @arg @ref LL_PWR_I3C_PULLUP_PB3
  *         @arg @ref LL_PWR_I3C_PULLUP_PB4
  *         @arg @ref LL_PWR_I3C_PULLUP_PB8
  *         @arg @ref LL_PWR_I3C_PULLUP_PB9
  *         @arg @ref LL_PWR_I3C_PULLUP_PC8
  *         @arg @ref LL_PWR_I3C_PULLUP_PC9
  *         @arg @ref LL_PWR_I3C_PULLUP_PD0
  *         @arg @ref LL_PWR_I3C_PULLUP_PD1
  *         @arg @ref LL_PWR_I3C_PULLUP_PD6
  *         @arg @ref LL_PWR_I3C_PULLUP_PD7
  *         @arg @ref LL_PWR_I3C_PULLUP_PE5
  *         @arg @ref LL_PWR_I3C_PULLUP_PE6
  *         @arg @ref LL_PWR_I3C_PULLUP_PG13
  *         @arg @ref LL_PWR_I3C_PULLUP_PG14
  *         @arg @ref LL_PWR_I3C_PULLUP_PH11
  *         @arg @ref LL_PWR_I3C_PULLUP_PH12
  *         @arg @ref LL_PWR_I3C_PULLUP_PI2
  */
__STATIC_INLINE void LL_PWR_EnableI3CPullUp(uint32_t i3cpullup_pin)
{
  STM32_SET_BIT(PWR->I3CPUCR, i3cpullup_pin);
}

/**
  * @brief  Disable the I3C pull-up functionality for the specified pin.
  * @rmtoll
  *   I3CPUCR    I3CPxxx_PU      LL_PWR_DisableI3CPullUp
  * @param  i3cpullup_pin This parameter can be one of the following values:
  *         @arg @ref LL_PWR_I3C_PULLUP_PA15
  *         @arg @ref LL_PWR_I3C_PULLUP_PB3
  *         @arg @ref LL_PWR_I3C_PULLUP_PB4
  *         @arg @ref LL_PWR_I3C_PULLUP_PB8
  *         @arg @ref LL_PWR_I3C_PULLUP_PB9
  *         @arg @ref LL_PWR_I3C_PULLUP_PC8
  *         @arg @ref LL_PWR_I3C_PULLUP_PC9
  *         @arg @ref LL_PWR_I3C_PULLUP_PD0
  *         @arg @ref LL_PWR_I3C_PULLUP_PD1
  *         @arg @ref LL_PWR_I3C_PULLUP_PD6
  *         @arg @ref LL_PWR_I3C_PULLUP_PD7
  *         @arg @ref LL_PWR_I3C_PULLUP_PE5
  *         @arg @ref LL_PWR_I3C_PULLUP_PE6
  *         @arg @ref LL_PWR_I3C_PULLUP_PG13
  *         @arg @ref LL_PWR_I3C_PULLUP_PG14
  *         @arg @ref LL_PWR_I3C_PULLUP_PH11
  *         @arg @ref LL_PWR_I3C_PULLUP_PH12
  *         @arg @ref LL_PWR_I3C_PULLUP_PI2
  */
__STATIC_INLINE void LL_PWR_DisableI3CPullUp(uint32_t i3cpullup_pin)
{
  STM32_CLEAR_BIT(PWR->I3CPUCR, i3cpullup_pin);
}

/**
  * @brief  Check if the I3C pull-up functionality is enabled for the specified pin.
  * @rmtoll
  *   I3CPUCR    I3CPxxx_PU      LL_PWR_IsEnabledI3CPullUp
  * @param  i3cpullup_pin This parameter can be one of the following values:
  *         @arg @ref LL_PWR_I3C_PULLUP_PA15
  *         @arg @ref LL_PWR_I3C_PULLUP_PB3
  *         @arg @ref LL_PWR_I3C_PULLUP_PB4
  *         @arg @ref LL_PWR_I3C_PULLUP_PB8
  *         @arg @ref LL_PWR_I3C_PULLUP_PB9
  *         @arg @ref LL_PWR_I3C_PULLUP_PC8
  *         @arg @ref LL_PWR_I3C_PULLUP_PC9
  *         @arg @ref LL_PWR_I3C_PULLUP_PD0
  *         @arg @ref LL_PWR_I3C_PULLUP_PD1
  *         @arg @ref LL_PWR_I3C_PULLUP_PD6
  *         @arg @ref LL_PWR_I3C_PULLUP_PD7
  *         @arg @ref LL_PWR_I3C_PULLUP_PE5
  *         @arg @ref LL_PWR_I3C_PULLUP_PE6
  *         @arg @ref LL_PWR_I3C_PULLUP_PG13
  *         @arg @ref LL_PWR_I3C_PULLUP_PG14
  *         @arg @ref LL_PWR_I3C_PULLUP_PH11
  *         @arg @ref LL_PWR_I3C_PULLUP_PH12
  *         @arg @ref LL_PWR_I3C_PULLUP_PI2
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsEnabledI3CPullUp(uint32_t i3cpullup_pin)
{
  return ((STM32_READ_BIT(PWR->I3CPUCR, i3cpullup_pin) == (i3cpullup_pin)) ? 1UL : 0UL);
}


/**
  * @brief  Enable the XSPI pull-up functionality for the specified pin.
  * @rmtoll
  *   XSPIPUCR    XSPIPxxx_PU      LL_PWR_EnableXSPIPullUp
  * @param  xspipullup_pin This parameter can be one of the following values:
  *         @arg @ref LL_PWR_XSPI_PULLUP_PH0
  *         @arg @ref LL_PWR_XSPI_PULLUP_PH1
  *         @arg @ref LL_PWR_XSPI_PULLUP_PF2
  *         @arg @ref LL_PWR_XSPI_PULLUP_PA0
  *         @arg @ref LL_PWR_XSPI_PULLUP_PA2
  *         @arg @ref LL_PWR_XSPI_PULLUP_PA3
  *         @arg @ref LL_PWR_XSPI_PULLUP_PA4
  *         @arg @ref LL_PWR_XSPI_PULLUP_PA5
  *         @arg @ref LL_PWR_XSPI_PULLUP_PB1
  *         @arg @ref LL_PWR_XSPI_PULLUP_PB2
  *         @arg @ref LL_PWR_XSPI_PULLUP_PD0
  *         @arg @ref LL_PWR_XSPI_PULLUP_PD1
  *         @arg @ref LL_PWR_XSPI_PULLUP_PD2
  *         @arg @ref LL_PWR_XSPI_PULLUP_PD3
  *         @arg @ref LL_PWR_XSPI_PULLUP_PG10
  */
__STATIC_INLINE void LL_PWR_EnableXSPIPullUp(uint32_t xspipullup_pin)
{
  STM32_SET_BIT(PWR->XSPIPUCR, xspipullup_pin);
}

/**
  * @brief  Disable the XSPI pull-up functionality for the specified pin.
  * @rmtoll
  *   XSPIPUCR    XSPIPxxx_PU      LL_PWR_DisableXSPIPullUp
  * @param  xspipullup_pin This parameter can be one of the following values:
  *         @arg @ref LL_PWR_XSPI_PULLUP_PH0
  *         @arg @ref LL_PWR_XSPI_PULLUP_PH1
  *         @arg @ref LL_PWR_XSPI_PULLUP_PF2
  *         @arg @ref LL_PWR_XSPI_PULLUP_PA0
  *         @arg @ref LL_PWR_XSPI_PULLUP_PA2
  *         @arg @ref LL_PWR_XSPI_PULLUP_PA3
  *         @arg @ref LL_PWR_XSPI_PULLUP_PA4
  *         @arg @ref LL_PWR_XSPI_PULLUP_PA5
  *         @arg @ref LL_PWR_XSPI_PULLUP_PB1
  *         @arg @ref LL_PWR_XSPI_PULLUP_PB2
  *         @arg @ref LL_PWR_XSPI_PULLUP_PD0
  *         @arg @ref LL_PWR_XSPI_PULLUP_PD1
  *         @arg @ref LL_PWR_XSPI_PULLUP_PD2
  *         @arg @ref LL_PWR_XSPI_PULLUP_PD3
  *         @arg @ref LL_PWR_XSPI_PULLUP_PG10
  */
__STATIC_INLINE void LL_PWR_DisableXSPIPullUp(uint32_t xspipullup_pin)
{
  STM32_CLEAR_BIT(PWR->XSPIPUCR, xspipullup_pin);
}

/**
  * @brief  Check if the XSPI pull-up functionality is enabled for the specified pin.
  * @rmtoll
  *   XSPIPUCR    XSPIPxxx_PU      LL_PWR_IsEnabledXSPIPullUp
  * @param  xspipullup_pin This parameter can be one of the following values:
  *         @arg @ref LL_PWR_XSPI_PULLUP_PH0
  *         @arg @ref LL_PWR_XSPI_PULLUP_PH1
  *         @arg @ref LL_PWR_XSPI_PULLUP_PF2
  *         @arg @ref LL_PWR_XSPI_PULLUP_PA0
  *         @arg @ref LL_PWR_XSPI_PULLUP_PA2
  *         @arg @ref LL_PWR_XSPI_PULLUP_PA3
  *         @arg @ref LL_PWR_XSPI_PULLUP_PA4
  *         @arg @ref LL_PWR_XSPI_PULLUP_PA5
  *         @arg @ref LL_PWR_XSPI_PULLUP_PB1
  *         @arg @ref LL_PWR_XSPI_PULLUP_PB2
  *         @arg @ref LL_PWR_XSPI_PULLUP_PD0
  *         @arg @ref LL_PWR_XSPI_PULLUP_PD1
  *         @arg @ref LL_PWR_XSPI_PULLUP_PD2
  *         @arg @ref LL_PWR_XSPI_PULLUP_PD3
  *         @arg @ref LL_PWR_XSPI_PULLUP_PG10
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsEnabledXSPIPullUp(uint32_t xspipullup_pin)
{
  return ((STM32_READ_BIT(PWR->XSPIPUCR, xspipullup_pin) == (xspipullup_pin)) ? 1UL : 0UL);
}

/**
  * @brief  Enable the XSPI pull-down functionality for the specified pin.
  * @rmtoll
  *   XSPIPDCR    XSPIPxxx_PD      LL_PWR_EnableXSPIPullDown
  * @param  xspipulldown_pin This parameter can be one of the following values:
  *         @arg @ref LL_PWR_XSPI_PULLDOWN_PH0
  *         @arg @ref LL_PWR_XSPI_PULLDOWN_PH1
  *         @arg @ref LL_PWR_XSPI_PULLDOWN_PF2
  *         @arg @ref LL_PWR_XSPI_PULLDOWN_PA0
  *         @arg @ref LL_PWR_XSPI_PULLDOWN_PA2
  *         @arg @ref LL_PWR_XSPI_PULLDOWN_PA3
  *         @arg @ref LL_PWR_XSPI_PULLDOWN_PA4
  *         @arg @ref LL_PWR_XSPI_PULLDOWN_PA5
  *         @arg @ref LL_PWR_XSPI_PULLDOWN_PB1
  *         @arg @ref LL_PWR_XSPI_PULLDOWN_PB2
  *         @arg @ref LL_PWR_XSPI_PULLDOWN_PD0
  *         @arg @ref LL_PWR_XSPI_PULLDOWN_PD1
  *         @arg @ref LL_PWR_XSPI_PULLDOWN_PD2
  *         @arg @ref LL_PWR_XSPI_PULLDOWN_PD3
  *         @arg @ref LL_PWR_XSPI_PULLDOWN_PG10
  */
__STATIC_INLINE void LL_PWR_EnableXSPIPullDown(uint32_t xspipulldown_pin)
{
  STM32_SET_BIT(PWR->XSPIPDCR, xspipulldown_pin);
}

/**
  * @brief  Disable the XSPI pull-down functionality for the specified pin.
  * @rmtoll
  *   XSPIPDCR    XSPIPxxx_PD      LL_PWR_DisableXSPIPullDown
  * @param  xspipulldown_pin This parameter can be one of the following values:
  *         @arg @ref LL_PWR_XSPI_PULLDOWN_PH0
  *         @arg @ref LL_PWR_XSPI_PULLDOWN_PH1
  *         @arg @ref LL_PWR_XSPI_PULLDOWN_PF2
  *         @arg @ref LL_PWR_XSPI_PULLDOWN_PA0
  *         @arg @ref LL_PWR_XSPI_PULLDOWN_PA2
  *         @arg @ref LL_PWR_XSPI_PULLDOWN_PA3
  *         @arg @ref LL_PWR_XSPI_PULLDOWN_PA4
  *         @arg @ref LL_PWR_XSPI_PULLDOWN_PA5
  *         @arg @ref LL_PWR_XSPI_PULLDOWN_PB1
  *         @arg @ref LL_PWR_XSPI_PULLDOWN_PB2
  *         @arg @ref LL_PWR_XSPI_PULLDOWN_PD0
  *         @arg @ref LL_PWR_XSPI_PULLDOWN_PD1
  *         @arg @ref LL_PWR_XSPI_PULLDOWN_PD2
  *         @arg @ref LL_PWR_XSPI_PULLDOWN_PD3
  *         @arg @ref LL_PWR_XSPI_PULLDOWN_PG10
  */
__STATIC_INLINE void LL_PWR_DisableXSPIPullDown(uint32_t xspipulldown_pin)
{
  STM32_CLEAR_BIT(PWR->XSPIPDCR, xspipulldown_pin);
}

/**
  * @brief  Check if the XSPI pull-down functionality is enabled for the specified pin.
  * @rmtoll
  *   XSPIPDCR    XSPIPxxx_PD      LL_PWR_IsEnabledXSPIPullDown
  * @param  xspipulldown_pin This parameter can be one of the following values:
  *         @arg @ref LL_PWR_XSPI_PULLDOWN_PH0
  *         @arg @ref LL_PWR_XSPI_PULLDOWN_PH1
  *         @arg @ref LL_PWR_XSPI_PULLDOWN_PF2
  *         @arg @ref LL_PWR_XSPI_PULLDOWN_PA0
  *         @arg @ref LL_PWR_XSPI_PULLDOWN_PA2
  *         @arg @ref LL_PWR_XSPI_PULLDOWN_PA3
  *         @arg @ref LL_PWR_XSPI_PULLDOWN_PA4
  *         @arg @ref LL_PWR_XSPI_PULLDOWN_PA5
  *         @arg @ref LL_PWR_XSPI_PULLDOWN_PB1
  *         @arg @ref LL_PWR_XSPI_PULLDOWN_PB2
  *         @arg @ref LL_PWR_XSPI_PULLDOWN_PD0
  *         @arg @ref LL_PWR_XSPI_PULLDOWN_PD1
  *         @arg @ref LL_PWR_XSPI_PULLDOWN_PD2
  *         @arg @ref LL_PWR_XSPI_PULLDOWN_PD3
  *         @arg @ref LL_PWR_XSPI_PULLDOWN_PG10
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsEnabledXSPIPullDown(uint32_t xspipulldown_pin)
{
  return ((STM32_READ_BIT(PWR->XSPIPDCR, xspipulldown_pin) == (xspipulldown_pin)) ? 1UL : 0UL);
}

/** @defgroup PWR_LL_EF_FLAG_MANAGEMENT PWR Flag management
  * @{
  */

/**
  * @brief  Indicate whether the voltage level is ready for current actual used VOS.
  * @rmtoll
  *   SR1        ACTVOSRDY       LL_PWR_IsActiveFlag_ACTVOS
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsActiveFlag_ACTVOS(void)
{
  return ((STM32_READ_BIT(PWR->SR1, PWR_SR1_ACTVOSRDY) == (PWR_SR1_ACTVOSRDY)) ? 1UL : 0UL);
}

/**
  * @brief  Indicate whether VDD voltage is below the selected PVD threshold.
  * @rmtoll
  *   SR1        PVDO            LL_PWR_IsActiveFlag_PVDO
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsActiveFlag_PVDO(void)
{
  return ((STM32_READ_BIT(PWR->SR1, PWR_SR1_PVDO) == (PWR_SR1_PVDO)) ? 1UL : 0UL);
}

/**
  * @brief  Indicate whether VDDA voltage is below the selected AVD threshold.
  * @rmtoll
  *   SR1        AVDO            LL_PWR_IsActiveFlag_AVDO
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsActiveFlag_AVDO(void)
{
  return ((STM32_READ_BIT(PWR->SR1, PWR_SR1_AVDO) == (PWR_SR1_AVDO)) ? 1UL : 0UL);
}

/**
  * @brief  Get Backup Regulator ready Flag.
  * @rmtoll
  *   CSR1       BRRDY           LL_PWR_IsActiveFlag_BRRDY
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsActiveFlag_BRRDY(void)
{
  return ((STM32_READ_BIT(PWR->CSR1, PWR_CSR1_BRRDY) == (PWR_CSR1_BRRDY)) ? 1UL : 0UL);
}

/**
  * @brief  Indicate whether the VBAT level is above or below low threshold.
  * @rmtoll
  *   CSR1       VBATL           LL_PWR_IsActiveFlag_VBATL
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsActiveFlag_VBATL(void)
{
  return ((STM32_READ_BIT(PWR->CSR1, PWR_CSR1_VBATL) == (PWR_CSR1_VBATL)) ? 1UL : 0UL);
}

/**
  * @brief  Indicate whether the VBAT level is above or below high threshold.
  * @rmtoll
  *   CSR1       VBATH           LL_PWR_IsActiveFlag_VBATH
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsActiveFlag_VBATH(void)
{
  return ((STM32_READ_BIT(PWR->CSR1, PWR_CSR1_VBATH) == (PWR_CSR1_VBATH)) ? 1UL : 0UL);
}

/**
  * @brief  Indicate whether the Core temperature level is above or below low threshold.
  * @rmtoll
  *   CSR1       TEMPL           LL_PWR_IsActiveFlag_TEMPL
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsActiveFlag_TEMPL(void)
{
  return ((STM32_READ_BIT(PWR->CSR1, PWR_CSR1_TEMPL) == (PWR_CSR1_TEMPL)) ? 1UL : 0UL);
}

/**
  * @brief  Indicate whether the Core temperature level is above or below high threshold.
  * @rmtoll
  *   CSR1       TEMPH           LL_PWR_IsActiveFlag_TEMPH
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsActiveFlag_TEMPH(void)
{
  return ((STM32_READ_BIT(PWR->CSR1, PWR_CSR1_TEMPH) == (PWR_CSR1_TEMPH)) ? 1UL : 0UL);
}

/**
  * @brief  Indicate whether the SMPS step-down converter supply is ready.
  * @rmtoll
  *   CSR2        SDRDY       LL_PWR_IsActiveFlag_SDRDY
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsActiveFlag_SDRDY(void)
{
  return ((STM32_READ_BIT(PWR->CSR2, PWR_CSR2_SDRDY) == (PWR_CSR2_SDRDY)) ? 1UL : 0UL);
}

/**
  * @brief  Get System Stop Flag.
  * @rmtoll
  *   CSR3       STOPF           LL_PWR_IsActiveFlag_STOP
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsActiveFlag_STOP(void)
{
  return ((STM32_READ_BIT(PWR->CSR3, PWR_CSR3_STOPF) == (PWR_CSR3_STOPF)) ? 1UL : 0UL);
}

/**
  * @brief  Get System Standby Flag.
  * @rmtoll
  *   CSR3       SBF             LL_PWR_IsActiveFlag_SB
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsActiveFlag_SB(void)
{
  return ((STM32_READ_BIT(PWR->CSR3, PWR_CSR3_SBF) == (PWR_CSR3_SBF)) ? 1UL : 0UL);
}

/**
  * @brief  Indicate whether the Regulator is ready in the selected voltage range.
  *         or if its output voltage is still changing to the required voltage level
  * @rmtoll
  *   CSR4       VOSRDY          LL_PWR_IsActiveFlag_VOS
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsActiveFlag_VOS(void)
{
  return ((STM32_READ_BIT(PWR->CSR4, PWR_CSR4_VOSRDY) == (PWR_CSR4_VOSRDY)) ? 1UL : 0UL);
}

/**
  * @brief  Get Wake-up Flag 1.
  * @rmtoll
  *   WKUPFR     WKUPF1          LL_PWR_IsActiveFlag_WU1
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsActiveFlag_WU1(void)
{
  return ((STM32_READ_BIT(PWR->WKUPFR, PWR_WKUPFR_WKUPF1) == (PWR_WKUPFR_WKUPF1)) ? 1UL : 0UL);
}

/**
  * @brief  Get Wake-up Flag 2.
  * @rmtoll
  *   WKUPFR     WKUPF2          LL_PWR_IsActiveFlag_WU2
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsActiveFlag_WU2(void)
{
  return ((STM32_READ_BIT(PWR->WKUPFR, PWR_WKUPFR_WKUPF2) == (PWR_WKUPFR_WKUPF2)) ? 1UL : 0UL);
}

/**
  * @brief  Get Wake-up Flag 3.
  * @rmtoll
  *   WKUPFR     WKUPF3          LL_PWR_IsActiveFlag_WU3
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsActiveFlag_WU3(void)
{
  return ((STM32_READ_BIT(PWR->WKUPFR, PWR_WKUPFR_WKUPF3) == (PWR_WKUPFR_WKUPF3)) ? 1UL : 0UL);
}

/**
  * @brief  Get Wake-up Flag 4.
  * @rmtoll
  *   WKUPFR     WKUPF4          LL_PWR_IsActiveFlag_WU4
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsActiveFlag_WU4(void)
{
  return ((STM32_READ_BIT(PWR->WKUPFR, PWR_WKUPFR_WKUPF4) == (PWR_WKUPFR_WKUPF4)) ? 1UL : 0UL);
}

/**
  * @brief  Get Wake-up Flag 5.
  * @rmtoll
  *   WKUPFR     WKUPF5          LL_PWR_IsActiveFlag_WU5
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsActiveFlag_WU5(void)
{
  return ((STM32_READ_BIT(PWR->WKUPFR, PWR_WKUPFR_WKUPF5) == (PWR_WKUPFR_WKUPF5)) ? 1UL : 0UL);
}

/**
  * @brief  Get Wake-up Flag 6.
  * @rmtoll
  *   WKUPFR     WKUPF6          LL_PWR_IsActiveFlag_WU6
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsActiveFlag_WU6(void)
{
  return ((STM32_READ_BIT(PWR->WKUPFR, PWR_WKUPFR_WKUPF6) == (PWR_WKUPFR_WKUPF6)) ? 1UL : 0UL);
}

/**
  * @brief  Get Wake-up Flag 7.
  * @rmtoll
  *   WKUPFR     WKUPF7          LL_PWR_IsActiveFlag_WU7
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsActiveFlag_WU7(void)
{
  return ((STM32_READ_BIT(PWR->WKUPFR, PWR_WKUPFR_WKUPF7) == (PWR_WKUPFR_WKUPF7)) ? 1UL : 0UL);
}

/**
  * @brief  Get Wake-up Flag 8.
  * @rmtoll
  *   WKUPFR     WKUPF8          LL_PWR_IsActiveFlag_WU8
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_PWR_IsActiveFlag_WU8(void)
{
  return ((STM32_READ_BIT(PWR->WKUPFR, PWR_WKUPFR_WKUPF8) == (PWR_WKUPFR_WKUPF8)) ? 1UL : 0UL);
}

/**
  * @brief  Check if a wakeup event is detected on a selected wakeup pin or not.
  * @rmtoll
  *   WKUPFR           WKUPFx[1:8]           LL_PWR_IsActiveFlag_WU
  * @param  wakeup_pin
  *         This parameter can be one of the following values:
  *         @arg @ref LL_PWR_WAKEUP_PIN_1
  *         @arg @ref LL_PWR_WAKEUP_PIN_2
  *         @arg @ref LL_PWR_WAKEUP_PIN_3
  *         @arg @ref LL_PWR_WAKEUP_PIN_4
  *         @arg @ref LL_PWR_WAKEUP_PIN_5
  *         @arg @ref LL_PWR_WAKEUP_PIN_6
  *         @arg @ref LL_PWR_WAKEUP_PIN_7
  *         @arg @ref LL_PWR_WAKEUP_PIN_8
  * @retval Status of WU flag (1 active / 0 not active).
  */
__STATIC_INLINE uint32_t LL_PWR_IsActiveFlag_WU(uint32_t wakeup_pin)
{
  return ((STM32_READ_BIT(PWR->WKUPFR, wakeup_pin) == (wakeup_pin)) ? 1UL : 0UL);
}

/**
  * @brief  Clear STOP flags.
  * @rmtoll
  *   CSR3       CSSF            LL_PWR_ClearFlag_STOP
  */
__STATIC_INLINE void LL_PWR_ClearFlag_STOP(void)
{
  STM32_SET_BIT(PWR->CSR3, PWR_CSR3_CSSF);
}


/**
  * @brief  Clear STANDBY flags.
  * @rmtoll
  *   CSR3       CSSF            LL_PWR_ClearFlag_SB
  */
__STATIC_INLINE void LL_PWR_ClearFlag_SB(void)
{
  STM32_SET_BIT(PWR->CSR3, PWR_CSR3_CSSF);
}

/**
  * @brief  Clear all wake up flags.
  * @rmtoll
  *   WUSCR          WKUPC         LL_PWR_ClearFlag_WU
  * @param  wakeup_pin This parameter can be one of the following values:
  *         @arg @ref LL_PWR_WAKEUP_PIN_1
  *         @arg @ref LL_PWR_WAKEUP_PIN_2
  *         @arg @ref LL_PWR_WAKEUP_PIN_3
  *         @arg @ref LL_PWR_WAKEUP_PIN_4
  *         @arg @ref LL_PWR_WAKEUP_PIN_5
  *         @arg @ref LL_PWR_WAKEUP_PIN_6
  *         @arg @ref LL_PWR_WAKEUP_PIN_7
  *         @arg @ref LL_PWR_WAKEUP_PIN_8
  *         @arg @ref LL_PWR_WAKEUP_PIN_ALL
  */
__STATIC_INLINE void LL_PWR_ClearFlag_WU(uint32_t wakeup_pin)
{
  STM32_WRITE_REG(PWR->WKUPCR, wakeup_pin);
}

/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

#endif /* defined (PWR) */

/**
  * @}
  */

#ifdef __cplusplus
}
#endif

#endif /* STM32H7Pxx_LL_PWR_H */

