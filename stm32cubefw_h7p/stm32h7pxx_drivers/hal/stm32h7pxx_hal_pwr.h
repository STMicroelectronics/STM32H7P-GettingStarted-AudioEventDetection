/**
  **********************************************************************************************************************
  * @file    stm32h7pxx_hal_pwr.h
  * @author  GPM Application Team
  * @brief   Header file of PWR HAL module.
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
#ifndef STM32H7PXX_HAL_PWR_H
#define STM32H7PXX_HAL_PWR_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* Includes ----------------------------------------------------------------------------------------------------------*/
#include "stm32h7pxx_hal_def.h"
#include "stm32h7pxx_ll_pwr.h"

/** @addtogroup STM32H7Pxx_HAL_Driver
  * @{
  */

/** @defgroup PWR PWR
  * @{
  */

/* Exported types ----------------------------------------------------------------------------------------------------*/
/** @defgroup PWR_Exported_Types PWR Exported Types
  * @{
  */

/*! HAL PWR wakeup pin polarity enumeration definition */
typedef enum
{
  HAL_PWR_WAKEUP_PIN_POLARITY_LOW  = LL_PWR_WAKEUP_PIN_POLARITY_LOW,  /*!< Wakeup pin low polarity  */
  HAL_PWR_WAKEUP_PIN_POLARITY_HIGH = LL_PWR_WAKEUP_PIN_POLARITY_HIGH  /*!< Wakeup pin high polarity */
} hal_pwr_wakeup_pin_polarity_t;

/*! HAL PWR wakeup pin pull configuration enumeration definition */
typedef enum
{
  HAL_PWR_WAKEUP_PIN_PULL_NO   = LL_PWR_WAKEUP_PIN_PULL_NO,  /*!< Wakeup pin no pull   */
  HAL_PWR_WAKEUP_PIN_PULL_UP   = LL_PWR_WAKEUP_PIN_PULL_UP,  /*!< Wakeup pin pull up   */
  HAL_PWR_WAKEUP_PIN_PULL_DOWN = LL_PWR_WAKEUP_PIN_PULL_DOWN /*!< Wakeup pin pull down */
} hal_pwr_wakeup_pin_pull_t;

/*! HAL PWR wakeup pin status enumeration definition */
typedef enum
{
  HAL_PWR_WAKEUP_PIN_DISABLED = 0U, /*!< Wakeup pin disabled */
  HAL_PWR_WAKEUP_PIN_ENABLED  = 1U  /*!< Wakeup pin enabled  */
} hal_pwr_wakeup_pin_status_t;

/*! HAL PWR wakeup pin configuration structure definition */
typedef struct
{
  hal_pwr_wakeup_pin_polarity_t polarity; /*!< Wakeup pin polarity */
  hal_pwr_wakeup_pin_pull_t     pull;     /*!< Wakeup pin pull     */
} hal_pwr_wakeup_pin_config_t;

/*! HAL PWR RTC domain write protection status enumeration definition */
typedef enum
{
  HAL_PWR_RTC_DOMAIN_WRP_DISABLED = 0U, /*!< RTC domain write protection disabled */
  HAL_PWR_RTC_DOMAIN_WRP_ENABLED  = 1U  /*!< RTC domain write protection enabled  */
} hal_pwr_rtc_domain_wrp_status_t;

/*! HAL PWR voltage scale range enumeration definition */
typedef enum
{
  HAL_PWR_VOLT_SCALE_0 = LL_PWR_REGU_VOLT_SCALE_0, /*!< Voltage scale range 0 */
  HAL_PWR_VOLT_SCALE_1 = LL_PWR_REGU_VOLT_SCALE_1, /*!< Voltage scale range 1 */
  HAL_PWR_VOLT_SCALE_2 = LL_PWR_REGU_VOLT_SCALE_2  /*!< Voltage scale range 2 */
} hal_pwr_volt_scale_range_t;

/*! HAL PWR Stop voltage scale range enumeration definition */
typedef enum
{
  HAL_PWR_STOP_VOLT_SCALE_LOW  = LL_PWR_REGU_STOP_VOLT_SCALE_LOW,  /*!< Voltage scale Low (lowest power) when system
                                                                        enters STOP mode      */
  HAL_PWR_STOP_VOLT_SCALE_HIGH = LL_PWR_REGU_STOP_VOLT_SCALE_HIGH, /*!< Voltage scale High (highest frequency) when
                                                                        system enters STOP mode */
} hal_pwr_stop_volt_scale_range_t;

/*! HAL PWR main regulator source enumeration definition */
typedef enum
{
  HAL_PWR_MAIN_REGULATOR_NOT_BYPASSED_SUPPLY  = LL_PWR_MAIN_REGU_SUPPLY_NOT_BYPASSED, /*!< PWR SMPS and LDO regulators
                                                                                           are not bypassed */
  HAL_PWR_MAIN_REGULATOR_BYPASSED_SUPPLY      = LL_PWR_MAIN_REGU_SUPPLY_BYPASSED,     /*!< PWR SMPS and LDO regulators
                                                                                           are bypassed */
  HAL_PWR_MAIN_REGULATOR_SMPS_SUPPLY          = LL_PWR_MAIN_REGU_SUPPLY_SMPS_ENABLED, /*!< PWR SMPS is the main
                                                                                           regulator supply */
  HAL_PWR_MAIN_REGULATOR_LDO_SUPPLY           = LL_PWR_MAIN_REGU_SUPPLY_LDO_ENABLED,  /*!< PWR LDO is the main
                                                                                           regulator supply */
} hal_pwr_main_regulator_supply_t;

/*! HAL PWR analog IO switch enumeration definition */
typedef enum
{
  HAL_PWR_ANALOG_IO_SWITCH_VDDA_SUPPLY      = LL_PWR_ANALOG_IO_SWITCH_VDDA_SUPPLY,    /*!< PWR Analog IO switch to VddA
                                                                                           supply */
  HAL_PWR_ANALOG_IO_SWITCH_BOOSTER_SUPPLY   = LL_PWR_ANALOG_IO_SWITCH_BOOSTER_SUPPLY  /*!< PWR Analog IO switch to
                                                                                           Booster supply */
} hal_pwr_analog_io_switch_supply_t;

/*! HAL PWR low power mode entry request enumeration definition */
typedef enum
{
  HAL_PWR_LOW_PWR_MODE_WFE = 0U, /*!< Low power mode wait for event request     */
  HAL_PWR_LOW_PWR_MODE_WFI = 1U  /*!< Low power mode wait for interrupt request */
} hal_pwr_low_pwr_mode_entry_t;

/*! HAL PWR Stop mode enumeration definition */
typedef enum
{
  HAL_PWR_STOP_MODE = LL_PWR_STOP_MODE /*!< Stop mode */
} hal_pwr_stop_mode_t;

/*! HAL PWR core sleep enumeration definition */
typedef enum
{
  HAL_PWR_CORE_SLEEP      = LL_PWR_CORE_SLEEP,      /*!< Core sleep mode      */
  HAL_PWR_CORE_DEEP_SLEEP = LL_PWR_CORE_DEEP_SLEEP  /*!< Core deep sleep mode */
} hal_pwr_core_sleep_mode_t;

/*! HAL PWR core sleep enumeration definition */
typedef enum
{
  HAL_PWR_CORE_SLEEP_ON_EXIT_DISABLED = 0U, /*!< PWR Core sleep on exit disabled */
  HAL_PWR_CORE_SLEEP_ON_EXIT_ENABLED  = 1U  /*!< PWR Core sleep on exit enabled  */
} hal_pwr_core_sleep_on_exit_status_t;

/*! HAL PWR core send event on pending status enumeration definition */
typedef enum
{
  HAL_PWR_CORE_SEV_ON_PENDING_DISABLED = 0U, /*!< Core send event on pending disabled */
  HAL_PWR_CORE_SEV_ON_PENDING_ENABLED  = 1U  /*!< Core send event on pending enabled  */
} hal_pwr_core_sev_on_pending_status_t;

/*! HAL PWR power voltage detector level enumeration definition */
typedef enum
{
  HAL_PWR_PVD_LEVEL_1   = LL_PWR_PVDLEVEL_1,   /*!< Voltage threshold detected by PVD XXX_SI V                     */
  HAL_PWR_PVD_LEVEL_2   = LL_PWR_PVDLEVEL_2,   /*!< Voltage threshold detected by PVD XXX_SI V                     */
  HAL_PWR_PVD_LEVEL_3   = LL_PWR_PVDLEVEL_3,   /*!< Voltage threshold detected by PVD XXX_SI V                     */
  HAL_PWR_PVD_LEVEL_4   = LL_PWR_PVDLEVEL_4,   /*!< Voltage threshold detected by PVD XXX_SI V                     */
  HAL_PWR_PVD_LEVEL_5   = LL_PWR_PVDLEVEL_5,   /*!< Voltage threshold detected by PVD XXX_SI V                     */
  HAL_PWR_PVD_LEVEL_6   = LL_PWR_PVDLEVEL_6,   /*!< Voltage threshold detected by PVD XXX_SI V                     */
  HAL_PWR_PVD_LEVEL_7   = LL_PWR_PVDLEVEL_7,   /*!< Voltage threshold detected by PVD XXX_SI V                     */
  HAL_PWR_PVD_LEVEL_8   = LL_PWR_PVDLEVEL_8    /*!< External input on PVD_IN pin, compared to internal VREFINT level */
} hal_pwr_pvd_level_t;

/*! HAL PWR programmable voltage detector status enumeration definition */
typedef enum
{
  HAL_PWR_PVD_DISABLED = 0U, /*!< PWR PVD disabled */
  HAL_PWR_PVD_ENABLED  = 1U  /*!< PWR PVD enabled  */
} hal_pwr_pvd_status_t;

/*! HAL PWR analog voltage detector level enumeration definition */
typedef enum
{
  HAL_PWR_AVD_LEVEL_1 = LL_PWR_AVDLEVEL_1, /*!< Voltage threshold detected by AVD XXX_SI  V                         */
  HAL_PWR_AVD_LEVEL_2 = LL_PWR_AVDLEVEL_2, /*!< Voltage threshold detected by AVD XXX_SI  V                         */
  HAL_PWR_AVD_LEVEL_3 = LL_PWR_AVDLEVEL_3, /*!< Voltage threshold detected by AVD XXX_SI  V                         */
  HAL_PWR_AVD_LEVEL_4 = LL_PWR_AVDLEVEL_4, /*!< Voltage threshold detected by AVD XXX_SI  V                         */
} hal_pwr_avd_level_t;

/*! HAL PWR analog voltage detector status enumeration definition */
typedef enum
{
  HAL_PWR_AVD_DISABLED = 0U, /*!< PWR AVD disabled */
  HAL_PWR_AVD_ENABLED  = 1U  /*!< PWR AVD enabled  */
} hal_pwr_avd_status_t;

/*! HAL PWR power voltage monitor status definition */
typedef enum
{
  HAL_PWR_MONITOR_DISABLED = 0U, /*!< Monitoring disabled */
  HAL_PWR_MONITOR_ENABLED  = 1U  /*!< Monitoring enabled  */
} hal_pwr_monitor_status_t;

/*! HAL PWR memory retention enumeration definition */
typedef enum
{
  HAL_PWR_MEMORY_RETENTION_BKPRAM_STANDBY_VBAT = 0U  /*!< Backup RAM memory retention in Standby mode  */
} hal_pwr_memory_retention_t;

/*! HAL PWR memory retention status enumeration definition */
typedef enum
{
  HAL_PWR_MEMORY_RETENTION_DISABLED = 0U, /*!< Memory retention in Standby mode disabled */
  HAL_PWR_MEMORY_RETENTION_ENABLED  = 1U  /*!< Memory retention in Standby mode enabled  */
} hal_pwr_memory_retention_status_t;

/*! HAL PWR FLASH memory low power mode status enumeration definition */
typedef enum
{
  HAL_PWR_FLASH_LOW_PWR_MODE_DISABLED = 0U, /*!< PWR FLASH memory low power mode disabled */
  HAL_PWR_FLASH_LOW_PWR_MODE_ENABLED  = 1U  /*!< PWR FLASH memory low power mode enabled  */
} hal_pwr_flash_low_pwr_mode_status_t;

/*! HAL PWR USB Type-c and Power delivery Standby mode enumeration definition */
typedef enum
{
  HAL_PWR_UCPD_RETENTION_DISABLED = 0U, /*!< UCPD configuration retention in Standby mode disabled */
  HAL_PWR_UCPD_RETENTION_ENABLED  = 1U  /*!< UCPD configuration retention in Standby mode enabled  */
} hal_pwr_ucpd_retention_status_t;

/*! HAL PWR battery charging resistor value enumeration definition */
typedef enum
{
  HAL_PWR_BATTERY_CHARGING_RES_5K   = LL_PWR_BATT_CHARG_RESISTOR_5K,  /*!< Battery charging resistor 5KOhm   */
  HAL_PWR_BATTERY_CHARGING_RES_1_5K = LL_PWR_BATT_CHARG_RESISTOR_1_5K /*!< Battery charging resistor 1.5KOhm */
} hal_pwr_battery_charging_res_value_t;

/*! HAL PWR battery charging status enumeration definition */
typedef enum
{
  HAL_PWR_BATTERY_CHARGING_DISABLED = 0U, /*!< Battery charging disabled */
  HAL_PWR_BATTERY_CHARGING_ENABLED  = 1U  /*!< Battery charging enabled  */
} hal_pwr_battery_charging_status_t;

/*! HAL PWR USB Type-C and power delivery dead battery mode status enumeration definition */
typedef enum
{
  HAL_PWR_DEAD_BATTERY_MODE_DISABLED = 0U, /*!< USB Type-c and Power delivery dead battery mode disabled */
  HAL_PWR_DEAD_BATTERY_MODE_ENABLED  = 1U  /*!< USB Type-c and Power delivery dead battery mode enabled  */
} hal_pwr_dead_battery_mode_status_t;

/*! HAL PWR gpio pull enumeration definition */
typedef enum
{
  HAL_PWR_GPIO_PULL_NO   = 0U, /*!< GPIO no pull   */
  HAL_PWR_GPIO_PULL_UP   = 1U, /*!< GPIO pull up   */
  HAL_PWR_GPIO_PULL_DOWN = 2U  /*!< GPIO pull down */
} hal_pwr_gpio_pull_t;

/*! HAL PWR peripheral pull configuration selection enumeration definition */
typedef enum
{
  HAL_PWR_PULL_PERIPH_I3C, /*!< I3C selected */
  HAL_PWR_PULL_PERIPH_XSPI /*!< XSPI selected */
} hal_pwr_pull_periph_t;

/*! HAL PWR gpio pull configuration status enumeration definition */
typedef enum
{
  HAL_PWR_GPIO_CONFIG_NOT_APPLIED = 0U, /*!< GPIO pull configuration not applied */
  HAL_PWR_GPIO_CONFIG_APPLIED     = 1U  /*!< GPIO pull configuration applied     */
} hal_pwr_gpio_pull_config_status_t;
/*! HAL PWR gpio pull configuration I3C enumeration definition */

/*! HAL PWR gpio pull configuration xSPI enumeration definition */

/**
  * @}
  */

/* Exported constants -----------------------------------------------------------------------------------------------*/
/** @defgroup PWR_Exported_Constants PWR Exported Constants
  * @{
  */

/** @defgroup PWR_wakeup_pin PWR wakeup pin definition
  * @{
  */
#define HAL_PWR_WAKEUP_PIN_1   LL_PWR_WAKEUP_PIN_1    /*!< Wakeup pin 1 : PA0  */
#define HAL_PWR_WAKEUP_PIN_2   LL_PWR_WAKEUP_PIN_2    /*!< Wakeup pin 2 : PA2  */
#define HAL_PWR_WAKEUP_PIN_3   LL_PWR_WAKEUP_PIN_3    /*!< Wakeup pin 3 : PI8  */
#define HAL_PWR_WAKEUP_PIN_4   LL_PWR_WAKEUP_PIN_4    /*!< Wakeup pin 4 : PC13 */
#define HAL_PWR_WAKEUP_PIN_5   LL_PWR_WAKEUP_PIN_5    /*!< Wakeup pin 5 : PB9  */
#define HAL_PWR_WAKEUP_PIN_6   LL_PWR_WAKEUP_PIN_6    /*!< Wakeup pin 6 : PC1  */
#define HAL_PWR_WAKEUP_PIN_7   LL_PWR_WAKEUP_PIN_7    /*!< Wakeup pin 7 : PC0  */
#define HAL_PWR_WAKEUP_PIN_8   LL_PWR_WAKEUP_PIN_8    /*!< Wakeup pin 8 : PD2  */
#define HAL_PWR_WAKEUP_PIN_ALL LL_PWR_WAKEUP_PIN_ALL  /*!< Wakeup pin all      */
/**
  * @}
  */

/** @defgroup PWR_I3C_pull PWR I3C pull pin definition
  * @{
  */
#define HAL_PWR_I3C_PULL_PA15    LL_PWR_I3C_PULLUP_PA15   /*!< Port PA15 I3C pull-up bit */
#define HAL_PWR_I3C_PULL_PB3     LL_PWR_I3C_PULLUP_PB3    /*!< Port PB3 I3C pull-up bit  */
#define HAL_PWR_I3C_PULL_PB4     LL_PWR_I3C_PULLUP_PB4    /*!< Port PB4 I3C pull-up bit  */
#define HAL_PWR_I3C_PULL_PB8     LL_PWR_I3C_PULLUP_PB8    /*!< Port PB8 I3C pull-up bit  */
#define HAL_PWR_I3C_PULL_PB9     LL_PWR_I3C_PULLUP_PB9    /*!< Port PB9 I3C pull-up bit  */
#define HAL_PWR_I3C_PULL_PC8     LL_PWR_I3C_PULLUP_PC8    /*!< Port PC8 I3C pull-up bit  */
#define HAL_PWR_I3C_PULL_PC9     LL_PWR_I3C_PULLUP_PC9    /*!< Port PC9 I3C pull-up bit  */
#define HAL_PWR_I3C_PULL_PD0     LL_PWR_I3C_PULLUP_PD0    /*!< Port PD0 I3C pull-up bit  */
#define HAL_PWR_I3C_PULL_PD1     LL_PWR_I3C_PULLUP_PD1    /*!< Port PD1 I3C pull-up bit  */
#define HAL_PWR_I3C_PULL_PD6     LL_PWR_I3C_PULLUP_PD6    /*!< Port PD6 I3C pull-up bit  */
#define HAL_PWR_I3C_PULL_PD7     LL_PWR_I3C_PULLUP_PD7    /*!< Port PD7 I3C pull-up bit  */
#define HAL_PWR_I3C_PULL_PE5     LL_PWR_I3C_PULLUP_PE5    /*!< Port PE5 I3C pull-up bit  */
#define HAL_PWR_I3C_PULL_PE6     LL_PWR_I3C_PULLUP_PE6    /*!< Port PE6 I3C pull-up bit  */
#define HAL_PWR_I3C_PULL_PG13    LL_PWR_I3C_PULLUP_PG13   /*!< Port PG13 I3C pull-up bit */
#define HAL_PWR_I3C_PULL_PG14    LL_PWR_I3C_PULLUP_PG14   /*!< Port PG14 I3C pull-up bit */
#define HAL_PWR_I3C_PULL_PH11    LL_PWR_I3C_PULLUP_PH11   /*!< Port PH11 I3C pull-up bit */
#define HAL_PWR_I3C_PULL_PH12    LL_PWR_I3C_PULLUP_PH12   /*!< Port PH12 I3C pull-up bit */
#define HAL_PWR_I3C_PULL_PI2     LL_PWR_I3C_PULLUP_PI2    /*!< Port PI2 I3C pull-up bit  */
/**
  * @}
  */

/** @defgroup PWR_XSPI_pull PWR XSPI pull pin definition
  * @{
  */
#define HAL_PWR_XSPI_PULL_PH0     LL_PWR_XSPI_PULLUP_PH0   /*!< Port PH0 xSPI pull bit  */
#define HAL_PWR_XSPI_PULL_PH1     LL_PWR_XSPI_PULLUP_PH1   /*!< Port PH1 xSPI pull bit  */
#define HAL_PWR_XSPI_PULL_PF2     LL_PWR_XSPI_PULLUP_PF2   /*!< Port PF2 xSPI pull bit  */
#define HAL_PWR_XSPI_PULL_PA0     LL_PWR_XSPI_PULLUP_PA0   /*!< Port PA0 xSPI pull bit  */
#define HAL_PWR_XSPI_PULL_PA2     LL_PWR_XSPI_PULLUP_PA2   /*!< Port PA2 xSPI pull bit  */
#define HAL_PWR_XSPI_PULL_PA3     LL_PWR_XSPI_PULLUP_PA3   /*!< Port PA3 xSPI pull bit  */
#define HAL_PWR_XSPI_PULL_PA4     LL_PWR_XSPI_PULLUP_PA4   /*!< Port PA4 xSPI pull bit  */
#define HAL_PWR_XSPI_PULL_PA5     LL_PWR_XSPI_PULLUP_PA5   /*!< Port PA5 xSPI pull bit  */
#define HAL_PWR_XSPI_PULL_PB1     LL_PWR_XSPI_PULLUP_PB1   /*!< Port PB1 xSPI pull bit  */
#define HAL_PWR_XSPI_PULL_PB2     LL_PWR_XSPI_PULLUP_PB2   /*!< Port PB2 xSPI pull bit  */
#define HAL_PWR_XSPI_PULL_PD0     LL_PWR_XSPI_PULLUP_PD0   /*!< Port PD0 xSPI pull bit  */
#define HAL_PWR_XSPI_PULL_PD1     LL_PWR_XSPI_PULLUP_PD1   /*!< Port PD1 xSPI pull bit  */
#define HAL_PWR_XSPI_PULL_PD2     LL_PWR_XSPI_PULLUP_PD2   /*!< Port PD2 xSPI pull bit  */
#define HAL_PWR_XSPI_PULL_PD3     LL_PWR_XSPI_PULLUP_PD3   /*!< Port PD3 xSPI pull bit  */
#define HAL_PWR_XSPI_PULL_PG10    LL_PWR_XSPI_PULLUP_PG10  /*!< Port PG10 xSPI pull bit */
/**
  * @}
  */

/**
  * @}
  */

/* Exported functions ------------------------------------------------------------------------------------------------*/
/** @defgroup PWR_Exported_Functions PWR Exported Functions
  * @{
  */

/** @defgroup PWR_Exported_Functions_Group1 Wakeup pins management functions
  * @{
  */
hal_status_t HAL_PWR_LP_SetConfigWakeupPin(uint32_t wakeup_pin, const hal_pwr_wakeup_pin_config_t *p_config);
void HAL_PWR_LP_GetConfigWakeupPin(uint32_t wakeup_pin, hal_pwr_wakeup_pin_config_t *p_config);
void HAL_PWR_LP_EnableWakeupPin(uint32_t wakeup_pin);
void HAL_PWR_LP_DisableWakeupPin(uint32_t wakeup_pin);
hal_pwr_wakeup_pin_status_t HAL_PWR_LP_IsEnabledWakeupPin(uint32_t wakeup_pin);
/**
  * @}
  */

/** @defgroup PWR_Exported_Functions_Group2 RTC domain write protection management functions
  * @{
  */
void HAL_PWR_EnableRTCDomainWriteProtection(void);
void HAL_PWR_DisableRTCDomainWriteProtection(void);
hal_pwr_rtc_domain_wrp_status_t HAL_PWR_IsEnabledRTCDomainWriteProtection(void);
/**
  * @}
  */

/** @defgroup PWR_Exported_Functions_Group3 Power supply management functions
  * @{
  */
hal_status_t HAL_PWR_SetMainRegulatorVoltageScalingRange(hal_pwr_volt_scale_range_t range);
hal_pwr_volt_scale_range_t HAL_PWR_GetMainRegulatorVoltageScalingRange(void);

void HAL_PWR_LP_SetMainRegulatorStopVoltageScalingRange(hal_pwr_stop_volt_scale_range_t range);
hal_pwr_stop_volt_scale_range_t HAL_PWR_LP_GetMainRegulatorStopVoltageScalingRange(void);

hal_status_t HAL_PWR_SetMainRegulatorSupply(hal_pwr_main_regulator_supply_t regulator);
hal_pwr_main_regulator_supply_t HAL_PWR_GetMainRegulatorSupply(void);

void HAL_PWR_SetAnalogIOSwitchSupply(hal_pwr_analog_io_switch_supply_t analog_switch_supply);
hal_pwr_analog_io_switch_supply_t HAL_PWR_GetAnalogIOSwitchSupply(void);
/**
  * @}
  */


/** @defgroup PWR_Exported_Functions_Group4 Low power mode management functions
  * @{
  */
void HAL_PWR_ClearCorePendingEvent(void);
void HAL_PWR_EnterSleepMode(hal_pwr_low_pwr_mode_entry_t sleep_entry);
void HAL_PWR_EnterStopMode(hal_pwr_low_pwr_mode_entry_t stop_entry, hal_pwr_stop_mode_t stop_mode);
void HAL_PWR_EnterStandbyMode(void);
void HAL_PWR_SetCoreSleepMode(hal_pwr_core_sleep_mode_t sleep_mode);
hal_pwr_core_sleep_mode_t HAL_PWR_GetCoreSleepMode(void);

void HAL_PWR_EnableCoreSleepOnExit(void);
void HAL_PWR_DisableCoreSleepOnExit(void);
hal_pwr_core_sleep_on_exit_status_t HAL_PWR_IsEnabledCoreSleepOnExit(void);
void HAL_PWR_EnableCoreSendEventOnPending(void);
void HAL_PWR_DisableCoreSendEventOnPending(void);
hal_pwr_core_sev_on_pending_status_t HAL_PWR_IsEnabledCoreSendEventOnPending(void);
/**
  * @}
  */

/** @defgroup PWR_Exported_Functions_Group5 Voltage monitoring management functions
  * @{
  */
void HAL_PWR_SetProgrammableVoltageDetectorLevel(hal_pwr_pvd_level_t level);
hal_pwr_pvd_level_t HAL_PWR_GetProgrammableVoltageDetectorLevel(void);
void HAL_PWR_EnableProgrammableVoltageDetector(void);
void HAL_PWR_DisableProgrammableVoltageDetector(void);
hal_pwr_pvd_status_t HAL_PWR_IsEnabledProgrammableVoltageDetector(void);

void HAL_PWR_SetAnalogVoltageDetectorLevel(hal_pwr_avd_level_t level);
hal_pwr_avd_level_t HAL_PWR_GetAnalogVoltageDetectorLevel(void);
void HAL_PWR_EnableAnalogVoltageDetector(void);
void HAL_PWR_DisableAnalogVoltageDetector(void);
hal_pwr_avd_status_t HAL_PWR_IsEnabledAnalogVoltageDetector(void);

void HAL_PWR_EnableTemperatureVbatMonitor(void);
void HAL_PWR_DisableTemperatureVbatMonitor(void);
hal_pwr_monitor_status_t HAL_PWR_IsEnabledTemperatureVbatMonitor(void);
/**
  * @}
  */

/** @defgroup PWR_Exported_Functions_Group6 Memory Retention management functions
  * @{
  */
hal_status_t HAL_PWR_LP_EnableMemoryRetention(hal_pwr_memory_retention_t memory);
hal_status_t HAL_PWR_LP_DisableMemoryRetention(hal_pwr_memory_retention_t memory);
hal_pwr_memory_retention_status_t HAL_PWR_LP_IsEnabledMemoryRetention(hal_pwr_memory_retention_t memory);
/**
  * @}
  */

/** @defgroup PWR_Exported_Functions_Group7 Memory management functions
  * @{
  */
void HAL_PWR_LP_EnableFlashLowPWRMode(void);
void HAL_PWR_LP_DisableFlashLowPWRMode(void);
hal_pwr_flash_low_pwr_mode_status_t HAL_PWR_LP_IsEnabledFlashLowPWRMode(void);
/**
  * @}
  */


/** @defgroup PWR_Exported_Functions_Group8 Battery management functions
  * @{
  */
void HAL_PWR_SetConfigBatteryCharging(hal_pwr_battery_charging_res_value_t value);
hal_pwr_battery_charging_res_value_t HAL_PWR_GetConfigBatteryCharging(void);
void HAL_PWR_EnableBatteryCharging(void);
void HAL_PWR_DisableBatteryCharging(void);
hal_pwr_battery_charging_status_t HAL_PWR_IsEnabledBatteryCharging(void);
/**
  * @}
  */

/** @defgroup PWR_Exported_Functions_Group9 UCPD management functions
  * @{
  */
void HAL_PWR_LP_EnableUCPDDeadBattery(void);
void HAL_PWR_LP_DisableUCPDDeadBattery(void);
hal_pwr_dead_battery_mode_status_t HAL_PWR_LP_IsEnabledUCPDDeadBattery(void);
void HAL_PWR_LP_EnableUCPDRetention(void);
void HAL_PWR_LP_DisableUCPDRetention(void);
hal_pwr_ucpd_retention_status_t HAL_PWR_LP_IsEnabledUCPDRetention(void);
/**
  * @}
  */

/** @defgroup PWR_Exported_Functions_Group10 Standby Pull management functions
  * @{
  */
void HAL_PWR_EnableGPIOPull(void);
void HAL_PWR_DisableGPIOPull(void);
hal_pwr_gpio_pull_config_status_t HAL_PWR_IsEnabledGPIOPull(void);

void HAL_PWR_SetConfigGPIOPull(hal_pwr_pull_periph_t periph, uint32_t gpio, hal_pwr_gpio_pull_t pull);
hal_pwr_gpio_pull_t HAL_PWR_GetConfigGPIOPull(hal_pwr_pull_periph_t periph, uint32_t gpio);
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

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* STM32H7PXX_HAL_PWR_H */
