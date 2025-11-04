/**
  **********************************************************************************************************************
  * @file    stm32h7pxx_hal_pwr.c
  * @author  GPM Application Team
  * @brief   PWR HAL module driver.
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

/* Includes ----------------------------------------------------------------------------------------------------------*/
#include "stm32_hal.h"

/** @addtogroup STM32H7Pxx_HAL_Driver
  * @{
  */

/** @addtogroup PWR
  * @{
  */
/** @defgroup PWR_Introduction PWR Introduction
  * @{

  - The PWR peripheral in STM32 manages power modes (sleep, stop, standby), voltage scaling and power supplies.
  - It reduces power consumption, supports multiple wakeup sources, and is essential for battery-powered applications.
  - Control is achieved through PWR registers; use HAL functions for simplified configuration.

  */
/**
  * @}
  */

/** @defgroup PWR_How_To_Use PWR How To Use
  * @{
# PWR peripheral overview

The Power control peripheral (PWR) provides an overview of the supply architecture for the different power domains
and of the supply configuration controller.

This file provides firmware functions to manage the following functionalities :
   - Wakeup pins management functions.
   - RTC domain access management functions.
   - Main regulator management functions.
   - Low power mode management functions.
   - Voltage monitoring management functions.
   - Memory retention management functions.
   - Memory low power management functions.
   - Battery management functions.
   - UCPD management functions.
   - I/O Pull management functions.

# How to use the PWR HAL module driver

## The PWR HAL driver can be used as follows:

This module manages all device power supplies and power modes transitions.

This module provides 10 different set of APIs that allows to :

1. Configure the wakeup pin :
   The wakeup pin is used to wakeup the system from low power modes.
   - Configure the wakeup pin polarity and selection independently and without enabling it :
     - This functionality is ensured by HAL_PWR_LP_SetConfigWakeupPin() function. The p_config pointer allows to
       configure wakeup polarity and selection.
       - When p_config is null,this function returns an HAL_INVALID_PARAM.
   - Get the wakeup pin polarity and selection configuration:
     - This functionality is ensured by HAL_PWR_LP_GetConfigWakeupPin() function.
   - Enable, disable and check the wakeup pin status :
     - These functionalities are ensured respectively by HAL_PWR_LP_EnableWakeupPin(), HAL_PWR_LP_DisableWakeupPin()
       and HAL_PWR_LP_IsEnabledWakeupPin() functions.

2. Manage RTC domain write protection :
   After a system reset, the RTC domain is protected against possible unwanted write accesses.
   - Enable, disable and check the write protection status of RTC domain :
     - These functionalities are ensured respectively by HAL_PWR_EnableRTCDomainWriteProtection(),
       HAL_PWR_DisableRTCDomainWriteProtection() and HAL_PWR_IsEnabledRTCDomainWriteProtection() functions.

3. Control power supply :
   The power supplies can be configured to manage application power consumption and performance.
   - Configure the main regulator voltage scaling range for different power modes :
     - This functionality is ensured by HAL_PWR_SetMainRegulatorVoltageScalingRange() function.
   - Get the voltage scaling range configuration :
     - This functionality is ensured by HAL_PWR_GetMainRegulatorVoltageScalingRange() function.
   - Configure the main regulator voltage scaling range for different power modes during low poser stop mode :
     - This functionality is ensured by HAL_PWR_LP_SetMainRegulatorStopVoltageScalingRange() function.
   - Get the voltage scaling range configuration during low power stop mode :
     - This functionality is ensured by HAL_PWR_LP_GetMainRegulatorStopVoltageScalingRange() function.
   - Set the Main Regulator supply source:
     - This functionality is ensured by HAL_PWR_SetMainRegulatorSupply() function.
   - Get the Main Regulator supply source :
     - This functionality is ensured by HAL_PWR_GetMainRegulatorSupply() function.
   - Set the Analog IO switch supply source:
     - This functionality is ensured by HAL_PWR_SetAnalogIOSwitchSupply() function.
   - Get the Analog IO switch supply source :
     - This functionality is ensured by HAL_PWR_GetAnalogIOSwitchSupply() function.

4. Manage low power modes:
   Several power modes are available to manage power consumption.
   - Clear Core pending event to clear internal cortex event before entering sleep or stop mode:
     - This functionality is ensured by HAL_PWR_ClearCorePendingEvent() function.
   - Enter the MCU to low power modes:
     - Enter the MCU to sleep mode through WFE or WFI request:
       - This functionality is ensured by HAL_PWR_EnterSleepMode() function.
     - Enter the MCU to stop mode through WFE or WFI request:
       - This functionality is ensured by HAL_PWR_EnterStopMode() function.
     - Enter the MCU to standby mode:
       - This functionality is ensured by HAL_PWR_EnterStandbyMode() function.
   - Configure the core deep sleep mode:
     - This functionality is ensured by HAL_PWR_SetCoreSleepMode() function.
   - Get the core deep sleep mode configuration:
     - This functionality is ensured by HAL_PWR_GetCoreSleepMode() function.
   - Enable, disable and check the core sleep on exit to re-entry in sleep mode after an interruption is over:
     - These functionalities are ensured respectively by HAL_PWR_EnableCoreSleepOnExit(),
        HAL_PWR_DisableCoreSleepOnExit() and HAL_PWR_IsEnabledCoreSleepOnExit() functions.
   - Enable, disable and check the core send event on pending to wakeup after any pending event/ interrupt:
     - these functionalities are ensured respectively by HAL_PWR_EnableCoreSendEventOnPending(),
         HAL_PWR_DisableCoreSendEventOnPending() and HAL_PWR_IsEnabledCoreSendEventOnPending() functions.

5. Monitor configuration:
   The monitor can be used to manage the power supplies and supply domains.
   - Configure the voltage threshold detector by the programmable voltage detector:
     - This functionality is ensured by HAL_PWR_SetProgrammableVoltageDetectorLevel() function.
   - Get the programmable voltage detector configuration:
     - This functionality is ensured by HAL_PWR_GetProgrammableVoltageDetectorLevel() function.
   - Enable, disable and check the programmable voltage detector status:
     - These functionalities are ensured respectively by HAL_PWR_EnableProgrammableVoltageDetector(),
       HAL_PWR_DisableProgrammableVoltageDetector() and HAL_PWR_IsEnabledProgrammableVoltageDetector() functions.
   - Configure the voltage threshold detector by the analog voltage detector:
     - This functionality is ensured by HAL_PWR_SetAnalogVoltageDetectorLevel() function.
   - Get the analog voltage detector configuration:
     - This functionality is ensured by HAL_PWR_GetAnalogVoltageDetectorLevel() function.
   - Enable, disable and check the analog voltage detector status:
     - These functionalities are ensured respectively by HAL_PWR_EnableAnalogVoltageDetector(),
       HAL_PWR_DisableAnalogVoltageDetector() and HAL_PWR_IsEnabledAnalogVoltageDetector() functions.
   - Enable, disable and check the peripheral voltage monitoring status:
     - These functionalities are ensured respectively by HAL_PWR_EnableTemperatureVbatMonitor(),
       HAL_PWR_DisableTemperatureVbatMonitor() and HAL_PWR_IsEnabledTemperatureVbatMonitor() functions.

6. Manage memory retention:
   After entering low power mode, the memories content retention can be managed.
   - Enable, disable and check the memory retention:
     - These functionalities are ensured by HAL_PWR_LP_EnableMemoryRetention(), HAL_PWR_LP_DisableMemoryRetention() and
       HAL_PWR_LP_IsEnabledMemoryRetention() functions.

7. Manage memory power modes:
   After entering low power mode, the Flash memory power mode can be managed.
   - Enable, disable and check the Flash low power mode in Stop modes:
     - These functionalities are ensured by HAL_PWR_LP_EnableFlashLowPWRMode(), HAL_PWR_LP_DisableFlashLowPWRMode() and
       HAL_PWR_LP_IsEnabledFlashLowPWRMode() functions.

8. Battery management:
   Several API are available to manage the battery charging:
   - Set and get battery charging resistor config:
     - These functionalities are ensured by HAL_PWR_SetConfigBatteryCharging() and HAL_PWR_GetConfigBatteryCharging().
   - Enable, disable and check the the battery charging:
     - These functionalities are ensured by HAL_PWR_EnableBatteryCharging(),
       HAL_PWR_DisableBatteryCharging() and HAL_PWR_IsEnabledBatteryCharging() functions.


9. UCPD management :
   Several API are available to enable or disable the UCPD dead battery feature:
   - Enable, disable and check UCPD dead battery: (*)
     - These functionalities are ensured by HAL_PWR_LP_EnableUCPDDeadBattery(), HAL_PWR_LP_DisableUCPDDeadBattery() and
       HAL_PWR_LP_IsEnabledUCPDDeadBattery() functions.
     - (*) feature not available in all devices
   - Enable, disable and check UCPD configuration retention: (*)
     - These functionalities are ensured by HAL_PWR_LP_EnableUCPDRetention(), HAL_PWR_LP_DisableUCPDRetention() and
       HAL_PWR_LP_IsEnabledUCPDRetention() functions.
     - (*) feature not available in all devices

10. Standby Pull management :
   Several API are available to manage pull-up or pull-down I/O for I3C and XSPI during standby.
   - Enable, disable and check pull status:
     - These functionalities are ensured by HAL_PWR_EnableGPIOPull(), HAL_PWR_DisableGPIOPull() and
       HAL_PWR_IsEnabledGPIOPull() functions.
   - Set and get pull config for I3C and XSPI:
     - These functionalities are ensured by HAL_PWR_SetConfigGPIOPull() and HAL_PWR_GetConfigGPIOPull().
  */
/**
  * @}
  */

/** @defgroup PWR_Configuration_Table PWR Configuration Table
  * @{
## Configuration inside the PWR driver

Config defines       | Description        | Default value | Note
---------------------| ---------------    | ------------- | ------------------------------------------------------------
PRODUCT              | from IDE           | NA            | The selected device
USE_HAL_PWR_MODULE   | from hal_conf.h    | 1U            | When set, HAL PWR module is enabled.
USE_ASSERT_DBG_PARAM | from IDE           | None          | When defined, enable the params assert.
USE_HAL_CHECK_PARAM  | from hal_conf.h    | 0U            | When set, parameters are checked in runtime.
  */
/**
  * @}
  */
#if defined(USE_HAL_PWR_MODULE) && (USE_HAL_PWR_MODULE == 1)

/* Private typedef ---------------------------------------------------------------------------------------------------*/
/* Private defines ---------------------------------------------------------------------------------------------------*/
/** @defgroup PWR_Private_Constants PWR Private Constants
  * @{
  */
/* Time out value of flags setting */
#define PWR_VOS_SELECT_MAX_DELAY                 0x32U   /*!< Max VOS timeout              */
#define PWR_BACKUPRAM_ENABLE_MAX_DELAY           0x32U   /*!< Max BACKUPRAM timeout        */
/**
  * @}
  */

/* Private variables -------------------------------------------------------------------------------------------------*/
/** @defgroup PWR_Private_Variables PWR Private Variables
  * @{
  */

/**
  * @}
  */

/* Private macros ----------------------------------------------------------------------------------------------------*/
/** @defgroup PWR_Private_Macros PWR Private Macros
  * @{
  */

/*! Set wakeup pins check macro */
#define IS_PWR_SET_WAKEUP_PIN(pin) \
  ((((pin) & HAL_PWR_WAKEUP_PIN_ALL) != 0U) && (((pin) & (~HAL_PWR_WAKEUP_PIN_ALL)) == 0U))

/*! Wakeup pin polarity check macro */
#define IS_PWR_WAKEUP_PIN_POLARITY(polarity) \
  (((polarity) == HAL_PWR_WAKEUP_PIN_POLARITY_HIGH ) || ((polarity) == HAL_PWR_WAKEUP_PIN_POLARITY_LOW))

/*! Wakeup pin pull check macro */
#define IS_PWR_WAKEUP_PIN_PULL(pull) \
  (((pull) == HAL_PWR_WAKEUP_PIN_PULL_NO ) || ((pull) == HAL_PWR_WAKEUP_PIN_PULL_UP) \
   || ((pull) == HAL_PWR_WAKEUP_PIN_PULL_DOWN))

/*! Get wakeup pins check macro */
#define IS_PWR_GET_WAKEUP_PIN(pin)    \
  (((pin) == HAL_PWR_WAKEUP_PIN_1)    \
   || ((pin) == HAL_PWR_WAKEUP_PIN_2) \
   || ((pin) == HAL_PWR_WAKEUP_PIN_3) \
   || ((pin) == HAL_PWR_WAKEUP_PIN_4) \
   || ((pin) == HAL_PWR_WAKEUP_PIN_5) \
   || ((pin) == HAL_PWR_WAKEUP_PIN_6) \
   || ((pin) == HAL_PWR_WAKEUP_PIN_7) \
   || ((pin) == HAL_PWR_WAKEUP_PIN_8))

/*! Voltage scaling range check macro */
#define IS_PWR_VOLT_SCALE_RANGE(range)  \
  (((range) == HAL_PWR_VOLT_SCALE_0)    \
   || ((range) == HAL_PWR_VOLT_SCALE_1) \
   || ((range) == HAL_PWR_VOLT_SCALE_2))

/*! Stop voltage scaling range check macro */
#define IS_PWR_STOP_VOLT_SCALE_RANGE(range)  \
  (((range) == LL_PWR_REGU_STOP_VOLT_SCALE_LOW)    \
   || ((range) == LL_PWR_REGU_STOP_VOLT_SCALE_HIGH))

/*! Main regulator supply check macro */
#define IS_PWR_SET_MAIN_REGULATOR_SUPPLY(regulator) \
  ((regulator) == HAL_PWR_MAIN_REGULATOR_NOT_BYPASSED_SUPPLY \
   || ((regulator == HAL_PWR_MAIN_REGULATOR_BYPASSED_SUPPLY)))

/*! Analog IO switch supply check macro */
#define IS_PWR_ANALOG_IO_SWITCH_SUPPLY(analog_switch_supply)              \
  (((analog_switch_supply) == HAL_PWR_ANALOG_IO_SWITCH_VDDA_SUPPLY)       \
   || ((analog_switch_supply) == HAL_PWR_ANALOG_IO_SWITCH_BOOSTER_SUPPLY))

/*! Low power mode entry check macro */
#define IS_PWR_LP_MODE_ENTRY(entry) \
  (((entry) == HAL_PWR_LOW_PWR_MODE_WFE) || ((entry) == HAL_PWR_LOW_PWR_MODE_WFI))

/*! Stop mode check macro */
#define IS_PWR_STOP_MODE(mode)  \
  ((mode) == HAL_PWR_STOP_MODE)

/*! Core sleep mode check macro */
#define IS_PWR_CORE_SLEEP_MODE(mode) \
  (((mode) == HAL_PWR_CORE_SLEEP) || ((mode) == HAL_PWR_CORE_DEEP_SLEEP))

/*! PVD level check macro */
#define IS_PWR_PVD_LEVEL(level)          \
  (((level) == HAL_PWR_PVD_LEVEL_1)      \
   || ((level) == HAL_PWR_PVD_LEVEL_2)   \
   || ((level) == HAL_PWR_PVD_LEVEL_3)   \
   || ((level) == HAL_PWR_PVD_LEVEL_4)   \
   || ((level) == HAL_PWR_PVD_LEVEL_5)   \
   || ((level) == HAL_PWR_PVD_LEVEL_6)   \
   || ((level) == HAL_PWR_PVD_LEVEL_7)   \
   || ((level) == HAL_PWR_PVD_LEVEL_8))

/*! AVD level check macro */
#define IS_PWR_AVD_LEVEL(level)        \
  (((level) == HAL_PWR_AVD_LEVEL_1)    \
   || ((level) == HAL_PWR_AVD_LEVEL_2)\
   || ((level) == HAL_PWR_AVD_LEVEL_3)\
   || ((level) == HAL_PWR_AVD_LEVEL_4))

/*! Memory retention check macro */
#define IS_PWR_MEMORY_RETENTION(memory)                       \
  ((memory) == HAL_PWR_MEMORY_RETENTION_BKPRAM_STANDBY_VBAT)

/*! Battery charging resistor selection check macro */
#define IS_PWR_BATTERY_RESISTOR_SELECT(resistor) \
  (((resistor) == HAL_PWR_BATTERY_CHARGING_RES_5K) || ((resistor) == HAL_PWR_BATTERY_CHARGING_RES_1_5K))

/*! I3C standby pull set config check macro */
#define IS_PWR_I3C_GPIO_PULL_SET_CONFIG(gpio, pull)                     \
  (((gpio >= HAL_PWR_I3C_PULL_PA15)&&(gpio <= HAL_PWR_I3C_PULL_PI2))    \
   && (((pull) == HAL_PWR_GPIO_PULL_NO)                                  \
       || ((pull) == HAL_PWR_GPIO_PULL_UP)))

/*! xSPI standby pull set config check macro */
#define IS_PWR_XSPI_GPIO_PULL_SET_CONFIG(gpio, pull)                      \
  (((gpio >= HAL_PWR_XSPI_PULL_PG10)&&(gpio <= HAL_PWR_XSPI_PULL_PH0))    \
   && (((pull) == HAL_PWR_GPIO_PULL_NO)                                    \
       || ((pull) == HAL_PWR_GPIO_PULL_UP)                                 \
       || ((pull) == HAL_PWR_GPIO_PULL_DOWN)))

/*! Peripherals standby pull set config check macro */
#define IS_PWR_PERIPH_GPIO_PULL_SET_CONFIG(periph, gpio, pull)                              \
  (((periph == HAL_PWR_PULL_PERIPH_XSPI)&&(IS_PWR_XSPI_GPIO_PULL_SET_CONFIG(gpio, pull)))   \
   || ((periph == HAL_PWR_PULL_PERIPH_I3C)&&(IS_PWR_I3C_GPIO_PULL_SET_CONFIG(gpio, pull))))

/*! Peripherals standby pull get config check macro */
#define IS_PWR_PERIPH_GPIO_PULL_GET_CONFIG(periph, gpio)                                                        \
  (((periph == HAL_PWR_PULL_PERIPH_XSPI)&&((gpio >= HAL_PWR_XSPI_PULL_PG10)&&(gpio <= HAL_PWR_XSPI_PULL_PH0)))  \
   ||((periph == HAL_PWR_PULL_PERIPH_I3C)&&((gpio >= HAL_PWR_I3C_PULL_PA15)&&(gpio <= HAL_PWR_I3C_PULL_PI2))))
/**
  * @}
  */

/* Exported functions ------------------------------------------------------------------------------------------------*/
/** @addtogroup PWR_Exported_Functions PWR Exported Functions
  * @{
  */

/** @addtogroup PWR_Exported_Functions_Group1 Wakeup pins management functions
  * @{
  This section provides functions allowing to configure the wakeup pins:
  - Call HAL_PWR_LP_SetConfigWakeupPin() function to configure wakeup pin.
  - Call HAL_PWR_LP_GetConfigWakeupPin() function to get wakeup pin configuration.
  - Call HAL_PWR_LP_EnableWakeupPin() function to enable wakeup pin.
  - Call HAL_PWR_LP_DisableWakeupPin() function to disable wakeup pin.
  - Call HAL_PWR_LP_IsEnabledWakeupPin() function to check that wakeup pin is enabled.
  */

/**
  * @brief  Set wakeup pin configuration.
  * @param  wakeup_pin        This parameter can be a combination of HAL_PWR_WAKEUP_PIN_x where x can be (1..8).
  * @param  p_config          Pointer to a @ref hal_pwr_wakeup_pin_config_t structure.
  * @retval HAL_INVALID_PARAM p_config pointer is NULL.
  * @retval HAL_OK            Wakeup pin has been correctly configured.
  */
hal_status_t HAL_PWR_LP_SetConfigWakeupPin(uint32_t wakeup_pin, const hal_pwr_wakeup_pin_config_t *p_config)
{
  uint32_t temp_pin = wakeup_pin;
  __IO uint32_t register_value = LL_PWR_READ_REG(WKUPEPR);
  uint32_t position;
  uint32_t current_pin;

  ASSERT_DBG_PARAM(p_config != NULL);
  ASSERT_DBG_PARAM(IS_PWR_SET_WAKEUP_PIN(wakeup_pin));
  ASSERT_DBG_PARAM(IS_PWR_WAKEUP_PIN_POLARITY(p_config->polarity));
  ASSERT_DBG_PARAM(IS_PWR_WAKEUP_PIN_PULL(p_config->pull));

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (p_config == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  /* Get wakeup pin information */
  position    = STM32_POSITION_VAL(temp_pin);
  current_pin = 1UL << position;

  while (temp_pin != 0U)
  {
    /* Mask values which will be modified */
    register_value &= ~(uint32_t)((LL_PWR_WAKEUP_PIN_PP_REF << position) \
                                  + (LL_PWR_WAKEUP_PIN_PULL_REF << (position * LL_PWR_WAKEUP_PINS_PULL_SHIFT_OFFSET)));

    /* Compute new value */
    register_value |= (uint32_t)(((uint32_t)(p_config->polarity) << (LL_PWR_WAKEUP_PIN_PP_REF_POS + position)) \
                                 + ((uint32_t)(p_config->pull) << (LL_PWR_WAKEUP_PIN_PULL_REF_POS \
                                                                   + (position \
                                                                      * LL_PWR_WAKEUP_PINS_PULL_SHIFT_OFFSET))));

    /* Update wakeup pin information */
    temp_pin    &= (~current_pin);
    position    = STM32_POSITION_VAL(temp_pin);
    current_pin = (uint32_t)(1UL << position);
  }

  /* Set new value in one register access */
  LL_PWR_WRITE_REG(WKUPEPR, register_value);

  return HAL_OK;
}

/**
  * @brief  Get wakeup pin configuration.
  * @param  wakeup_pin This parameter can be one of HAL_PWR_WAKEUP_PIN_x where x can be (1..8).
  * @param  p_config   Pointer to a @ref hal_pwr_wakeup_pin_config_t structure.
  */
void HAL_PWR_LP_GetConfigWakeupPin(uint32_t wakeup_pin, hal_pwr_wakeup_pin_config_t *p_config)
{
  ASSERT_DBG_PARAM(p_config != NULL);
  ASSERT_DBG_PARAM(IS_PWR_GET_WAKEUP_PIN(wakeup_pin));

  p_config->polarity = (hal_pwr_wakeup_pin_polarity_t)LL_PWR_GetWakeUpPinPolarity(wakeup_pin);
  p_config->pull     = (hal_pwr_wakeup_pin_pull_t)LL_PWR_GetWakeUpPinPull(wakeup_pin);
}

/**
  * @brief  Enable the wakeup pin configuration.
  * @param  wakeup_pin This parameter can be a combination of HAL_PWR_WAKEUP_PIN_x where x can be (1..8).
  * @note   Wakeup pins are used to wake up the system from Standby mode.
  */
void HAL_PWR_LP_EnableWakeupPin(uint32_t wakeup_pin)
{
  ASSERT_DBG_PARAM(IS_PWR_SET_WAKEUP_PIN(wakeup_pin));

  LL_PWR_EnableWakeUpPin(wakeup_pin);
}

/**
  * @brief  Disable the wakeup pin configuration.
  * @param  wakeup_pin This parameter can be a combination of HAL_PWR_WAKEUP_PIN_x where x can be (1..8).
  * @note   Wakeup pins are used to wake up the system from Standby mode.
  */
void HAL_PWR_LP_DisableWakeupPin(uint32_t wakeup_pin)
{
  ASSERT_DBG_PARAM(IS_PWR_SET_WAKEUP_PIN(wakeup_pin));

  LL_PWR_DisableWakeUpPin(wakeup_pin);
}

/**
  * @brief  Check that wakeup pin is enabled.
  * @param  wakeup_pin                  This parameter can be one of HAL_PWR_WAKEUP_PIN_x where x can be (1..8).
  * @retval HAL_PWR_WAKEUP_PIN_DISABLED Wakeup pin disabled
  * @retval HAL_PWR_WAKEUP_PIN_ENABLED  Wakeup pin enabled
  */
hal_pwr_wakeup_pin_status_t HAL_PWR_LP_IsEnabledWakeupPin(uint32_t wakeup_pin)
{
  ASSERT_DBG_PARAM(IS_PWR_GET_WAKEUP_PIN(wakeup_pin));

  return ((hal_pwr_wakeup_pin_status_t)LL_PWR_IsEnabledWakeUpPin(wakeup_pin));
}
/**
  * @}
  */

/** @addtogroup PWR_Exported_Functions_Group2 RTC domain write protection management functions
  * @{
  This section provides functions allowing to manage RTC domain access:
  - Call HAL_PWR_EnableRTCDomainWriteProtection() to enable RTC domain write protection.
  - Call HAL_PWR_DisableRTCDomainWriteProtection() to disable RTC domain write protection.
  - Call HAL_PWR_IsEnabledRTCDomainWriteProtection() to check that RTC domain write protection is enabled.
  */

/**
  * @brief  Enable the RTC domain write protection (RCC RTC domain control register RCC_RTCCR, RTC registers,
  *         TAMP registers, backup registers and backup SRAM).
  */
void HAL_PWR_EnableRTCDomainWriteProtection(void)
{
  LL_PWR_EnableBackupDomainWriteProtection();
}

/**
  * @brief  Disable the RTC domain write protection (RCC RTC domain control register RCC_RTCCR, RTC registers,
  *         TAMP registers, backup registers and backup SRAM).
  * @note   After a system reset, the RTC domain is protected against possible unwanted write accesses.
  */
void HAL_PWR_DisableRTCDomainWriteProtection(void)
{
  LL_PWR_DisableBackupDomainWriteProtection();
}

/**
  * @brief  Check that RTC domain access is enabled.
  * @retval HAL_PWR_RTC_DOMAIN_WRP_DISABLED RTC domain write protection disabled.
  * @retval HAL_PWR_RTC_DOMAIN_WRP_ENABLED  RTC domain write protection enabled.
  */
hal_pwr_rtc_domain_wrp_status_t HAL_PWR_IsEnabledRTCDomainWriteProtection(void)
{
  return ((hal_pwr_rtc_domain_wrp_status_t)LL_PWR_IsEnabledBackupWriteProtection());
}
/**
  * @}
  */

/** @addtogroup PWR_Exported_Functions_Group3 Power supply management functions
  * @{
  This section provides functions allowing to control power supply.
  - Call HAL_PWR_SetMainRegulatorSupply() function to configure the main regulator supply.
  - Call HAL_PWR_GetMainRegulatorSupply() function to get the main regulator supply configuration.
  - Call HAL_PWR_SetMainRegulatorVoltageScalingRange() function to configure voltage scaling range.
  - Call HAL_PWR_GetMainRegulatorVoltageScalingRange() function to get voltage scaling range configuration.
  - Call HAL_PWR_LP_SetMainRegulatorStopVoltageScalingRange function to set the regulator voltage scaling
range during stop mode.
  - Call HAL_PWR_LP_GetMainRegulatorStopVoltageScalingRange function to get the regulator voltage scaling
range during stop mode.
  - Call HAL_PWR_SetAnalogIOSwitchSupply function to set the analog IO switch supply.
  - Call HAL_PWR_GetAnalogIOSwitchSupply function to get the analog IO switch supply.
  */

/**
  * @brief   Set the regulator voltage scaling range.
  * @param   range     This parameter is an element of @ref hal_pwr_volt_scale_range_t enumeration.
  * @warning After reset, the system starts from HSI with VOS1.
  * @warning To increase the frequency, first increase the VOS to a higher level (VOS0 > VOS1 > VOS2).
  * @warning To decrease the frequency, first decrease the system frequency, then set the VOS to a lower level.
  * @warning Before moving to voltage scaling range 1, it is mandatory to ensure that the system frequency is above
  *          XXX_SI MHz.
  * @warning Before moving to voltage scaling range 0, it is mandatory to ensure that the system frequency is above
  *          XXX_SI MHz.
  * @warning When bypassing the internal regulator, we must ensure that SRAM operation speed has correctly adjusted
  *          before continuing.
  * @retval  HAL_ERROR VOS setting timeout.
  * @retval  HAL_OK    Regulator voltage scaling range has been correctly configured.
  */
hal_status_t HAL_PWR_SetMainRegulatorVoltageScalingRange(hal_pwr_volt_scale_range_t range)
{
  uint32_t timeout = ((PWR_VOS_SELECT_MAX_DELAY * (SystemCoreClock / 1000U)) / 1000U) + 1U;
  uint32_t vos = 0U;
  uint32_t actvos = 0U;

  ASSERT_DBG_PARAM(IS_PWR_VOLT_SCALE_RANGE(range));

  LL_PWR_SetRegulatorVoltageScaling((uint32_t)range);

  /* Check if the internal regulator is bypassed */
  if (LL_PWR_IsEnabledBypass() == LL_PWR_MAIN_REGU_SUPPLY_NOT_BYPASSED)
  {
    /* Polling on vos and actvos flags */
    do
    {
      vos = LL_PWR_IsActiveFlag_VOS();
      actvos = LL_PWR_IsActiveFlag_ACTVOS();
      timeout--;
    } while (((vos == 0U) || (actvos == 0U)) && (timeout != 0U));
  }
  else
  {
    /* In Bypass Voltage scaling cannot be set */
    return HAL_ERROR;
  }

  if (timeout == 0U)
  {
    return HAL_TIMEOUT;
  }

  return HAL_OK;
}

/**
  * @brief   Get the active regulator voltage scaling range.
  *
  * @retval  Returns hal_pwr_volt_scale_range_t enumeration value.
  *          @arg @ref HAL_PWR_VOLT_SCALE_0
  *          @arg @ref HAL_PWR_VOLT_SCALE_1
  *          @arg @ref HAL_PWR_VOLT_SCALE_2.
  */
hal_pwr_volt_scale_range_t HAL_PWR_GetMainRegulatorVoltageScalingRange(void)
{
  uint32_t actvos = 0U;

  /* get ACTVOS register content */
  actvos = LL_PWR_GetActiveRegulatorVoltageScaling();

  return (hal_pwr_volt_scale_range_t)actvos;
}

/**
  * @brief   Set the regulator voltage scaling range during stop mode.
  * @param   range     This parameter is an element of @ref hal_pwr_stop_volt_scale_range_t enumeration.
  * @warning By default the system stop mode regulator voltage scale is HAL_PWR_STOP_VOLT_SCALE_HIGH.
  * @warning HAL_PWR_STOP_VOLT_SCALE_LOW lowest power consumption in stop but add some latency in exit stop mode.
  * @warning HAL_PWR_STOP_VOLT_SCALE_HIGH lowest latency in exit from stop mode but higher consumption
  */
void HAL_PWR_LP_SetMainRegulatorStopVoltageScalingRange(hal_pwr_stop_volt_scale_range_t range)
{
  ASSERT_DBG_PARAM(IS_PWR_STOP_VOLT_SCALE_RANGE(range));

  LL_PWR_SetStopRegulatorVoltageScaling((uint32_t)range);
}

/**
  * @brief   Get the stop regulator voltage scaling range.
  *
  * @retval  Returns hal_pwr_stop_volt_scale_range_t enumeration value.
  *          @arg @ref HAL_PWR_STOP_VOLT_SCALE_LOW
  *          @arg @ref HAL_PWR_STOP_VOLT_SCALE_HIGH
  */
hal_pwr_stop_volt_scale_range_t HAL_PWR_LP_GetMainRegulatorStopVoltageScalingRange(void)
{
  return (hal_pwr_stop_volt_scale_range_t)LL_PWR_GetStopRegulatorVoltageScaling();
}

/**
  * @brief  Set the system supply regulator configuration.
  * @param  regulator HAL_PWR_MAIN_REGULATOR_NOT_BYPASSED_SUPPLY for internal regulator (SMPS/LDO)
  *                   HAL_PWR_MAIN_REGULATOR_BYPASSED_SUPPLY for external regulator (BYPASS)
  * @note   The bypass mode can be used only in Range 0.
  * @warning BYPASS bit MUST be programmed after power-up to select the VCORE supply configuration
  * (internal or external). If not programmed some power feature will not be available (VOS scaling for example).
  * @warning After programming it can not be changed without a power down reset !
  * @warning Software cannot select LDO or SMPS (set by package) but MUST program BYPASS bit to activate internal
  * regulator full feature.
  * @retval HAL_OK    System supply regulator has been correctly configured.
  * @retval HAL_ERROR System supply regulator has already been configured.
  */
hal_status_t HAL_PWR_SetMainRegulatorSupply(hal_pwr_main_regulator_supply_t regulator)
{
  hal_status_t status = HAL_OK;
  ASSERT_DBG_PARAM(IS_PWR_SET_MAIN_REGULATOR_SUPPLY(regulator));

  if (regulator == HAL_PWR_MAIN_REGULATOR_BYPASSED_SUPPLY)
  {
    LL_PWR_EnableBypass();

    if (LL_PWR_IsEnabledBypass() == 0UL)
    {
      /* After programming BYPASS bit can not be changed without a power down reset ! */
      status = HAL_ERROR;
    }
  }

  if (regulator != HAL_PWR_MAIN_REGULATOR_BYPASSED_SUPPLY)
  {
    if (LL_PWR_IsEnabledBypass() == 1UL)
    {
      /* After programming BYPASS bit can not be changed without a power down reset ! */
      status = HAL_ERROR;
    }

    /* BYPASS bit reset => internal regulator */
    LL_PWR_EnableInternalRegulator();

    /* After selecting internal regulator, ACTVOS Ready flag must be set by hardware */
    while (LL_PWR_IsActiveFlag_ACTVOS() == 0UL)
    {
      /* Wait until ACTVOS flag is set */
    }
  }
  return status;
}

/**
  * @brief  Get the system supply regulator configuration.
  * @retval Element of \ref hal_pwr_main_regulator_supply_t enumeration.
  */
hal_pwr_main_regulator_supply_t HAL_PWR_GetMainRegulatorSupply(void)
{
  hal_pwr_main_regulator_supply_t regulator;

  /* Check if the internal regulators are bypassed */
  if (LL_PWR_IsEnabledBypass() == LL_PWR_MAIN_REGU_SUPPLY_BYPASSED)
  {
    regulator = HAL_PWR_MAIN_REGULATOR_BYPASSED_SUPPLY;
  }
  else
  {
    /* Check if the SMPS is enabled, otherwise return LDO */
    if (LL_PWR_IsEnabledSMPSSupply() == 1UL)
    {
      regulator = HAL_PWR_MAIN_REGULATOR_SMPS_SUPPLY;
    }
    else
    {
      regulator = HAL_PWR_MAIN_REGULATOR_LDO_SUPPLY;
    }
  }

  return regulator;
}

/**
  * @brief Set the analog IO switch supply.
  * @param analog_switch_supply This parameter is an element of \ref hal_pwr_analog_io_switch_supply_t enumeration.
  * @note  The correct analog supply level is indicated by the AVD output after enabling the AVD and selecting the
  *        supply level to be monitored.
  * @note  The booster guarantees the analog switch AC performance when the VDD supply voltage is below 2.7 V
  *        (reduction of the total harmonic distortion to have the same switch performance over the full supply
  *        voltage range).
  */
void HAL_PWR_SetAnalogIOSwitchSupply(hal_pwr_analog_io_switch_supply_t analog_switch_supply)
{
  ASSERT_DBG_PARAM(IS_PWR_ANALOG_IO_SWITCH_SUPPLY(analog_switch_supply));

  /* If the selected supply is the Booster supply, check the state of Analog Voltage supply */
  if (analog_switch_supply == HAL_PWR_ANALOG_IO_SWITCH_BOOSTER_SUPPLY)
  {
    /* If Analog Voltage is not ready, enable it */
    if (LL_PWR_IsEnabledAnalogVoltageReady() == 0UL)
    {
      LL_PWR_EnableAnalogVoltageReady();
    }

    /* Enable Analog Booster */
    LL_PWR_EnableAnalogBooster();
  }
  else
  {
    /* Disable Analog Booster */
    LL_PWR_DisableAnalogBooster();
  }
}

/**
  * @brief  Get the analog IO switch supply.
  * @retval Returned value is an element of \ref hal_pwr_analog_io_switch_supply_t enumeration.
  */
hal_pwr_analog_io_switch_supply_t HAL_PWR_GetAnalogIOSwitchSupply(void)
{
  uint32_t booster_enabled = LL_PWR_IsEnabledAnalogBooster();
  uint32_t voltage_ready = LL_PWR_IsEnabledAnalogVoltageReady();

  /* Check if both booster and analog voltage are enabled */
  if ((booster_enabled == 1U) && (voltage_ready == 1U))
  {
    return HAL_PWR_ANALOG_IO_SWITCH_BOOSTER_SUPPLY;
  }
  else
  {
    return HAL_PWR_ANALOG_IO_SWITCH_VDDA_SUPPLY;
  }
}
/**
  * @}
  */

/** @addtogroup PWR_Exported_Functions_Group4 Low power mode management functions
  * @{
  This section provides functions allowing to manage low power modes:
  - Call HAL_PWR_ClearCorePendingEvent() function to clear the internal cortex event before entering low power mode.
  - Call HAL_PWR_EnterSleepMode() function to enter the Core in sleep mode.
  - Call HAL_PWR_EnterStopMode() function to enter the MCU in stop x mode
  - Call HAL_PWR_EnterStandbyMode() function to enter the MCU in standby mode.
  - Call HAL_PWR_SetCoreSleepMode() function to configure the Core in sleep or deep sleep mode.
  - Call HAL_PWR_GetCoreSleepMode() function to get Core sleep mode configuration.
  - Call HAL_PWR_EnableCoreSleepOnExit() function to enable Core to re-entry in sleep mode after an interrupt is over.
  - Call HAL_PWR_DisableCoreSleepOnExit() function to disable Core to re-entry in sleep mode after an interrupt is over.
  - Call HAL_PWR_IsEnabledCoreSleepOnExit() function to check Core to re-entry in sleep mode after an interrupt status.
  - Call HAL_PWR_EnableCoreSendEventOnPending() function to enable Core to wakeup after any pending event/ interrupt.
  - Call HAL_PWR_DisableCoreSendEventOnPending() function to disable Core to wakeup after any pending event/ interrupt.
  - Call HAL_PWR_IsEnabledCoreSendEventOnPending() function to check that core send event on pending is enabled.
  */

/**
  * @brief   Clear core pending event.
  * @note    This API clears the pending event in order to enter a given core to Sleep or Stop mode with WFE entry.
  * @warning It must be called just before APIs performing enter Sleep and Stop mode using Wait For Event request
  */
void HAL_PWR_ClearCorePendingEvent(void)
{
  /* ARMV7m specificity : Use DSB to ensure outstanding memory transactions complete before calling WFE/WFI. */
  __DSB();
  __ISB();
  __SEV();
  __WFE();
}

/**
  * @brief  Enter the core in Sleep mode.
  * @param  sleep_entry Parameter to @ref hal_pwr_low_pwr_mode_entry_t enumeration.
  * @param  sleep_mode  Parameter to @ref hal_pwr_sleep_mode_t enumeration
  */
void HAL_PWR_EnterSleepMode(hal_pwr_low_pwr_mode_entry_t sleep_entry)
{
  ASSERT_DBG_PARAM(IS_PWR_LP_MODE_ENTRY(sleep_entry));

  /* Clear SLEEPDEEP bit of Cortex System Control Register */
  STM32_CLEAR_BIT(SCB->SCR, SCB_SCR_SLEEPDEEP_Msk);

  /* ARMV7m specificity : Use DSB to ensure outstanding memory transactions complete before entering sleep mode. */
  __DSB();
  __ISB();

  if (sleep_entry == HAL_PWR_LOW_PWR_MODE_WFE)
  {
    /* Wait For Event Request */
    __WFE();
  }
  else
  {
    /* Wait For Interrupt Request */
    __WFI();
  }
}

/**
  * @brief  Enter the MCU in Stop mode.
  * @param  stop_entry This parameter is an element of @ref hal_pwr_low_pwr_mode_entry_t enumeration.
  * @param  stop_mode  This parameter is an element of @ref hal_pwr_stop_mode_t enumeration.
  */
void HAL_PWR_EnterStopMode(hal_pwr_low_pwr_mode_entry_t stop_entry, hal_pwr_stop_mode_t stop_mode)
{
  ASSERT_DBG_PARAM(IS_PWR_LP_MODE_ENTRY(stop_entry));
  ASSERT_DBG_PARAM(IS_PWR_STOP_MODE(stop_mode));

  /* Set SLEEPDEEP bit of Cortex System Control Register */
  STM32_SET_BIT(SCB->SCR, SCB_SCR_SLEEPDEEP_Msk);

  LL_PWR_SetPowerMode((uint32_t)stop_mode);

  /* ARMV7m specificity : Use DSB to ensure outstanding memory transactions complete before entering stop mode. */
  __DSB();
  __ISB();

  if (stop_entry == HAL_PWR_LOW_PWR_MODE_WFE)
  {
    /* Wait For Event Request */
    __WFE();
  }
  else
  {
    /* Wait For Interrupt Request */
    __WFI();
  }
}

/**
  * @brief   Enter the MCU in Standby mode.
  * @warning The Standby mode must not be used if VCORE is provided from an external supply.
  */
void HAL_PWR_EnterStandbyMode(void)
{
  /* Set SLEEPDEEP bit of Cortex System Control Register */
  STM32_SET_BIT(SCB->SCR, ((uint32_t)SCB_SCR_SLEEPDEEP_Msk));

  LL_PWR_SetPowerMode(LL_PWR_STANDBY_MODE);

  /* ARMV7m specificity : Use DSB to ensure outstanding memory transactions complete before entering stanby mode. */
  __DSB();
  __ISB();

  /* Wait For Interrupt Request */
  __WFI();
}

/**
  * @brief  Set the core sleep mode configuration.
  * @param  sleep_mode This parameter is an element of @ref hal_pwr_core_sleep_mode_t enumeration.
  */
void HAL_PWR_SetCoreSleepMode(hal_pwr_core_sleep_mode_t sleep_mode)
{
  ASSERT_DBG_PARAM(IS_PWR_CORE_SLEEP_MODE(sleep_mode));

  STM32_MODIFY_REG(SCB->SCR, SCB_SCR_SLEEPDEEP_Msk, (uint32_t)sleep_mode);
}

/**
  * @brief  Get the core sleep mode configuration.
  * @retval HAL_PWR_CORE_SLEEP      Core sleep mode.
  * @retval HAL_PWR_CORE_DEEP_SLEEP Core deep sleep mode.
  */
hal_pwr_core_sleep_mode_t HAL_PWR_GetCoreSleepMode(void)
{
  return ((hal_pwr_core_sleep_mode_t)((uint32_t)STM32_READ_BIT(SCB->SCR, SCB_SCR_SLEEPDEEP_Msk)));
}

/**
  * @brief  Enable SLEEP-ON-EXIT feature when returning from handler mode to thread mode.
  */
void HAL_PWR_EnableCoreSleepOnExit(void)
{
  STM32_SET_BIT(SCB->SCR, SCB_SCR_SLEEPONEXIT_Msk);
}

/**
  * @brief  Disable SLEEP-ON-EXIT feature when returning from handler mode to thread mode.
  */
void HAL_PWR_DisableCoreSleepOnExit(void)
{
  STM32_CLEAR_BIT(SCB->SCR, SCB_SCR_SLEEPONEXIT_Msk);
}

/**
  * @brief  Check if the Core SLEEP-ON-EXIT is enabled or disabled.
  * @retval hal_pwr_core_sleep_on_exit_status_t Core send event on pending status.
  */
hal_pwr_core_sleep_on_exit_status_t HAL_PWR_IsEnabledCoreSleepOnExit(void)
{
  uint32_t dummy = STM32_READ_BIT(SCB->SCR, SCB_SCR_SLEEPONEXIT_Msk) >> SCB_SCR_SLEEPONEXIT_Pos;

  return ((hal_pwr_core_sleep_on_exit_status_t)(dummy));
}

/**
  * @brief  Enable core Send Event On Pending feature.
  */
void HAL_PWR_EnableCoreSendEventOnPending(void)
{
  STM32_SET_BIT(SCB->SCR, SCB_SCR_SEVONPEND_Msk);
}

/**
  * @brief  Disable core Send Event On Pending.
  */
void HAL_PWR_DisableCoreSendEventOnPending(void)
{
  STM32_CLEAR_BIT(SCB->SCR, SCB_SCR_SEVONPEND_Msk);
}

/**
  * @brief  Get core Send Event On Pending.
  * @retval HAL_PWR_CORE_SEV_ON_PENDING_DISABLED Core send event on pending disabled.
  * @retval HAL_PWR_CORE_SEV_ON_PENDING_ENABLED  Core send event on pending enabled.
  */
hal_pwr_core_sev_on_pending_status_t HAL_PWR_IsEnabledCoreSendEventOnPending(void)
{
  uint32_t dummy = STM32_READ_BIT(SCB->SCR, SCB_SCR_SEVONPEND_Msk) >> SCB_SCR_SEVONPEND_Pos;

  return ((hal_pwr_core_sev_on_pending_status_t)(dummy));
}
/**
  * @}
  */

/** @addtogroup PWR_Exported_Functions_Group5 Voltage monitoring management functions
  * @{
  This section provides functions allowing to configure voltage monitoring.
  - Call HAL_PWR_SetProgrammableVoltageDetectorLevel() function to configure the programmable voltage detector.
  - Call HAL_PWR_GetProgrammableVoltageDetectorLevel() function to get the programmable voltage detector configuration.
  - Call HAL_PWR_EnableProgrammableVoltageDetector() function to enable the Programmable Voltage Detector.
  - Call HAL_PWR_DisableProgrammableVoltageDetector() function to disable the Programmable Voltage Detector.
  - Call HAL_PWR_IsEnabledProgrammableVoltageDetector() function to check the Programmable Voltage Detector status.
  - Call HAL_PWR_EnableTemperatureVbatMonitor() function to enable the temperature and VBAT monitor.
  - Call HAL_PWR_DisableTemperatureVbatMonitor() function to disable the temperature and VBAT monitor.
  - Call HAL_PWR_IsEnabledTemperatureVbatMonitor() function to check the temperature and VBAT monitor status.
  */

/**
  * @brief  Set the voltage threshold detection by the Programmable Voltage Detector (PVD).
  * @param  level This parameter is an element of @ref hal_pwr_pvd_level_t enumeration.
  */
void HAL_PWR_SetProgrammableVoltageDetectorLevel(hal_pwr_pvd_level_t level)
{
  ASSERT_DBG_PARAM(IS_PWR_PVD_LEVEL(level));

  LL_PWR_SetPVDLevel((uint32_t)level);
}

/**
  * @brief  Get the voltage threshold detection by the Programmable Voltage Detector (PVD).
  * @retval Level The current PVD level.
  */
hal_pwr_pvd_level_t HAL_PWR_GetProgrammableVoltageDetectorLevel(void)
{
  return ((hal_pwr_pvd_level_t)LL_PWR_GetPVDLevel());
}

/**
  * @brief  Enable the voltage threshold detection by the Programmable Voltage Detector (PVD).
  */
void HAL_PWR_EnableProgrammableVoltageDetector(void)
{
  LL_PWR_EnablePVD();
}

/**
  * @brief  Disable the voltage threshold detection by the Programmable Voltage Detector (PVD).
  */
void HAL_PWR_DisableProgrammableVoltageDetector(void)
{
  LL_PWR_DisablePVD();
}

/**
  * @brief  Check if the programmable voltage detection is enabled.
  * @retval HAL_PWR_PVD_DISABLED Programmable voltage detection disabled.
  * @retval HAL_PWR_PVD_ENABLED  Programmable voltage detection enabled.
  */
hal_pwr_pvd_status_t HAL_PWR_IsEnabledProgrammableVoltageDetector(void)
{
  return ((hal_pwr_pvd_status_t)LL_PWR_IsEnabledPVD());
}

/**
  * @brief  Set the voltage threshold detection by the Analog Voltage Detector (AVD).
  * @param  level This parameter is an element of @ref hal_pwr_avd_level_t enumeration.
  */
void HAL_PWR_SetAnalogVoltageDetectorLevel(hal_pwr_avd_level_t level)
{
  ASSERT_DBG_PARAM(IS_PWR_AVD_LEVEL(level));

  LL_PWR_SetAVDLevel((uint32_t)level);
}

/**
  * @brief  Get the voltage threshold detection by the Analog Voltage Detector (AVD).
  * @retval Level The current AVD level.
  */
hal_pwr_avd_level_t HAL_PWR_GetAnalogVoltageDetectorLevel(void)
{
  return ((hal_pwr_avd_level_t)LL_PWR_GetAVDLevel());
}

/**
  * @brief  Enable the voltage threshold detection by the Analog Voltage Detector (AVD).
  */
void HAL_PWR_EnableAnalogVoltageDetector(void)
{
  LL_PWR_EnableAVD();
}

/**
  * @brief  Disable the voltage threshold detection by the Analog Voltage Detector (AVD).
  */
void HAL_PWR_DisableAnalogVoltageDetector(void)
{
  LL_PWR_DisableAVD();
}

/**
  * @brief  Check if the Analog voltage detection is enabled.
  * @retval HAL_PWR_AVD_DISABLED Analog voltage detection disabled.
  * @retval HAL_PWR_AVD_ENABLED  Analog voltage detection enabled.
  */
hal_pwr_avd_status_t HAL_PWR_IsEnabledAnalogVoltageDetector(void)
{
  return ((hal_pwr_avd_status_t)LL_PWR_IsEnabledAVD());
}

/**
  * @brief Enable the temperature and VBAT monitor.
  * @warning RTC domain write protection must be disabled to enable temperature and Vbat monitoring.
  * @warning Temperature VBAT monitor is available only when Backup regulator is enabled.
  */
void HAL_PWR_EnableTemperatureVbatMonitor(void)
{
  /* Enabling temp and VBAT monitoring needs backup access */
  LL_PWR_EnableMonitoring();

}

/**
  * @brief Disable the temperature and VBAT monitor.
  * @warning RTC domain write protection must be disabled to disable temperature and Vbat monitoring.
  */
void HAL_PWR_DisableTemperatureVbatMonitor(void)
{
  /* disabling temp and VBAT monitoring needs backup access */
  LL_PWR_DisableMonitoring();
}

/**
  * @brief  Check if the temperature and VBAT monitor is enabled or disabled.
  * @retval hal_pwr_monitor_status_t The temperature and VBAT monitor status.
  */
hal_pwr_monitor_status_t HAL_PWR_IsEnabledTemperatureVbatMonitor(void)
{
  return ((hal_pwr_monitor_status_t)LL_PWR_IsEnabledMonitoring());
}

/**
  * @}
  */

/** @addtogroup PWR_Exported_Functions_Group6 Memory Retention management functions
  * @{
 This section provides functions allowing to manage memory content retention.
 - Call HAL_PWR_LP_EnableMemoryRetention() function to enable memory Retention.
 - Call HAL_PWR_LP_DisableMemoryRetention() function to disable memory Retention.
 - Call HAL_PWR_LP_IsEnabledMemoryRetention() to check the selected memory retention status.
  */

/**
  * @brief  Enable memory retention in LP Mode.
  * @param  memory This parameter is an element of @ref hal_pwr_memory_retention_t enumeration.
  * @warning RTC domain write protection must be disabled to enable memory retention if not HAL_ERROR.
  * @retval hal_status_t HAL_TIMEOUT, HAL_ERROR or HAL_OK.
  */
hal_status_t HAL_PWR_LP_EnableMemoryRetention(hal_pwr_memory_retention_t memory)
{
  uint32_t timeout = ((PWR_BACKUPRAM_ENABLE_MAX_DELAY * (SystemCoreClock / 1000U)) / 1000U) + 1U;
  uint32_t brrdy = 0;
  ASSERT_DBG_PARAM(IS_PWR_MEMORY_RETENTION(memory));

  STM32_UNUSED(memory);

  /* Enabling backup regulator needs backup access */
  if (LL_PWR_IsEnabledBackupWriteProtection() == 1UL)
  {
    return HAL_ERROR;
  }

  /* Enable backup RAM retention in standby */
  LL_PWR_EnableBackupRegulator();

  /* Polling on brrdy flags */
  do
  {
    brrdy = LL_PWR_IsActiveFlag_BRRDY();
    timeout--;
  } while ((brrdy == 0U) && (timeout != 0U));

  if (timeout == 0U)
  {
    return HAL_ERROR;
  }

  return HAL_OK;
}

/**
  * @brief  Disable memory retention in LP Mode.
  * @param  memory  This parameter is an element of @ref hal_pwr_memory_retention_t enumeration.
  * @warning RTC domain write protection must be disabled to disable memory retention.
  */
hal_status_t HAL_PWR_LP_DisableMemoryRetention(hal_pwr_memory_retention_t memory)
{
  ASSERT_DBG_PARAM(IS_PWR_MEMORY_RETENTION(memory));

  STM32_UNUSED(memory);

  /* Enabling backup regulator needs backup access */
  if (LL_PWR_IsEnabledBackupWriteProtection() == 1UL)
  {
    return HAL_ERROR;
  }

  /* Disable backup RAM retention in standby */
  LL_PWR_DisableBackupRegulator();

  return HAL_OK;
}

/**
  * @brief  Get memory retention status.
  * @param  memory  This parameter is an element of @ref hal_pwr_memory_retention_t enumeration.
  * @retval HAL_PWR_MEMORY_RETENTION_DISABLED if the selected memory is not retained in LP Mode.
  * @retval HAL_PWR_MEMORY_RETENTION_ENABLED  if the selected memory is retained in LP Mode.
  */
hal_pwr_memory_retention_status_t HAL_PWR_LP_IsEnabledMemoryRetention(hal_pwr_memory_retention_t memory)
{
  ASSERT_DBG_PARAM(IS_PWR_MEMORY_RETENTION(memory));

  STM32_UNUSED(memory);

  /* Backup RAM retention in standby mode is ready when PWR_CSR1_BRRDY is set */
  return ((hal_pwr_memory_retention_status_t)LL_PWR_IsActiveFlag_BRRDY());
}

/**
  * @}
  */

/** @addtogroup PWR_Exported_Functions_Group7 Memory management functions
  * @{
 This section provides functions allowing to manage Flash memory low power modes.
 - Call HAL_PWR_LP_EnableFlashLowPWRMode() function to enable Flash memory power down in Stop Mode.
 - Call HAL_PWR_LP_DisableFlashLowPWRMode() function to disable Flash memory power down in Stop Mode.
 - Call HAL_PWR_LP_IsEnabledFlashLowPWRMode() function to check the Flash memory power down in Stop Mode status.
  */
/**
  * @brief  Enable the Flash low power mode.
  */
void HAL_PWR_LP_EnableFlashLowPWRMode(void)
{
  LL_PWR_EnableFlashLowPWRMode();
}

/**
  * @brief  Disable the Flash low power mode.
  */
void HAL_PWR_LP_DisableFlashLowPWRMode(void)
{
  LL_PWR_DisableFlashLowPWRMode();
}

/**
  * @brief  Check if the Flash low power mode is enabled or disabled.
  * @retval hal_pwr_Flash_low_pwr_mode_status_t Flash low power mode status.
  */
hal_pwr_flash_low_pwr_mode_status_t HAL_PWR_LP_IsEnabledFlashLowPWRMode(void)
{
  return (hal_pwr_flash_low_pwr_mode_status_t)LL_PWR_IsEnabledFlashLowPWRMode();
}
/**
  * @}
  */

/** @addtogroup PWR_Exported_Functions_Group8 battery charging functions
  * @{
  This section provides functions allowing to manage battery charging.
  - Call HAL_PWR_SetConfigBatteryCharging Set the Battery charging resistor.
  - Call HAL_PWR_GetConfigBatteryCharging Get the Battery charging resistor.
  - Call HAL_PWR_EnableBatteryCharging Enable the Battery charging.
  - Call HAL_PWR_DisableBatteryCharging Disable the Battery charging.
  - Call HAL_PWR_IsEnabledBatteryCharging Check that battery charging is enabled.
  */

/**
  * @brief  Set the Battery charging resistor.
  * @param  value Specifies the charging resistor.
  *               This parameter can be one of the following values:
  *               @arg HAL_PWR_BATTERY_CHARGING_RES_5K   : 5 KOhm resistor.
  *               @arg HAL_PWR_BATTERY_CHARGING_RES_1_5K : 1.5 KOhm resistor.
  * @note   When Vdd is present, charge the external battery through an internal resistor.
  */
void HAL_PWR_SetConfigBatteryCharging(hal_pwr_battery_charging_res_value_t value)
{
  ASSERT_DBG_PARAM(IS_PWR_BATTERY_RESISTOR_SELECT(value));

  LL_PWR_SetBattChargResistor((uint32_t)value);
}

/**
  * @brief  Get the Battery charging resistor.
  * @note   When Vdd is present, charge the external battery through an internal resistor.
  * @retval hal_pwr_battery_charging_res_value_t The battery charging resistor value.
  */
hal_pwr_battery_charging_res_value_t HAL_PWR_GetConfigBatteryCharging(void)
{
  return ((hal_pwr_battery_charging_res_value_t)LL_PWR_GetBattChargResistor());
}

/**
  * @brief  Enable the Battery charging.
  */
void HAL_PWR_EnableBatteryCharging(void)
{
  LL_PWR_EnableBatteryCharging();
}

/**
  * @brief  Disable the Battery charging.
  */
void HAL_PWR_DisableBatteryCharging(void)
{
  LL_PWR_DisableBatteryCharging();
}

/**
  * @brief  Check that battery charging is enabled.
  * @retval hal_pwr_battery_charging_status_t The battery charging status.
  */
hal_pwr_battery_charging_status_t HAL_PWR_IsEnabledBatteryCharging(void)
{
  return ((hal_pwr_battery_charging_status_t)LL_PWR_IsEnabledBatteryCharging());
}

/**
  * @}
  */

/** @addtogroup PWR_Exported_Functions_Group9 UCPD management functions
  * @{
  This section provides functions allowing to manage UCPD battery charging.
  - Call HAL_PWR_LP_EnableUCPDDeadBattery() function to enable the UCPD dead battery behavior.
  - Call HAL_PWR_LP_DisableUCPDDeadBattery() function to disable the UCPD dead battery behavior.
  - Call HAL_PWR_LP_IsEnabledUCPDDeadBattery() function to check the UCPD dead battery behavior status.
  - Call HAL_PWR_LP_EnableUCPDRetention() function to enable the UCPD configuration retention in Standby mode.
  - Call HAL_PWR_LP_DisableUCPDRetention() function to disable the UCPD configuration retention in Standby mode.
  - Call HAL_PWR_LP_IsEnabledUCPDRetention() function to check the UCPD configuration retention in Standby mode status.
  */

/**
  * @brief  Enable dead battery behavior.
  * @note   After exiting reset, the USB Type-C (dead battery) behavior is enabled, which might have a pull-down effect
  *         on CC1 and CC2 pins. It is recommended to disable it in all cases, either to stop this pull-down or to
  *         handover control to the UCPD (the UCPD must be initialized before doing the disable).
  */
void HAL_PWR_LP_EnableUCPDDeadBattery(void)
{
  LL_PWR_EnableUCPDDeadBattery();
}

/**
  * @brief  Disable dead battery behavior.
  * @note   After exiting reset, the USB Type-C (dead battery) behavior is enabled, which might have a pull-down effect
  *         on CC1 and CC2 pins. It is recommended to disable it in all cases, either to stop this pull-down or to
  *         handover control to the UCPD (the UCPD must be initialized before doing the disable).
  */
void HAL_PWR_LP_DisableUCPDDeadBattery(void)
{
  LL_PWR_DisableUCPDDeadBattery();
}

/**
  * @brief  Check dead battery behavior.
  * @note   After exiting reset, the USB Type-C (dead battery) behavior is enabled, which might have a pull-down effect
  *         on CC1 and CC2 pins. It is recommended to disable it in all cases, either to stop this pull-down or to
  *         handover control to the UCPD (the UCPD must be initialized before doing the disable).
  * @retval HAL_PWR_DEAD_BATTERY_MODE_DISABLED  Disable USB Type-C dead battery pull-down behavior
  * @retval HAL_PWR_DEAD_BATTERY_MODE_ENABLED   Enable USB Type-C dead battery pull-down behavior
  */
hal_pwr_dead_battery_mode_status_t HAL_PWR_LP_IsEnabledUCPDDeadBattery(void)
{
  return (hal_pwr_dead_battery_mode_status_t)(LL_PWR_IsEnabledUCPDDeadBattery());
}

/**
  * @brief  Enable UCPD configuration memorization in Standby mode.
  * @note   This function must be called on exiting the Standby mode and before any UCPD configuration update.
  */
void HAL_PWR_LP_EnableUCPDRetention(void)
{
  LL_PWR_EnableUCPDRetentionStandbyMode();
}

/**
  * @brief  Disable UCPD configuration memorization in Standby mode.
  * @note   This function must be called on exiting the Standby mode and before any UCPD configuration update.
  */
void HAL_PWR_LP_DisableUCPDRetention(void)
{
  LL_PWR_DisableUCPDRetentionStandbyMode();
}

/**
  * @brief  Disable UCPD configuration memorization in Standby mode.
  * @note   This function must be called on exiting the Standby mode and before any UCPD configuration update.
  * @retval HAL_PWR_UCPD_RETENTION_ENABLED
  * @retval HAL_PWR_UCPD_RETENTION_DISABLED
  */
hal_pwr_ucpd_retention_status_t HAL_PWR_LP_IsEnabledUCPDRetention(void)
{
  return ((hal_pwr_ucpd_retention_status_t)LL_PWR_IsEnabledUCPDRetentionStandbyMode());
}
/**
  * @}
  */

/** @addtogroup PWR_Exported_Functions_Group10 Standby Pull management functions
  * @{
  This section provides functions allowing to manage standby mode pull.
  - Call HAL_PWR_EnableGPIOPull Enable GPIO pull configuration.
  - Call HAL_PWR_DisableGPIOPull Disable GPIO pull configuration.
  - Call HAL_PWR_IsEnabledGPIOPull Check that gpio pull is enabled.
  - Call HAL_PWR_SetConfigGPIOPull Set I3C or XSPI GPIO pull configuration during standby.
  - Call HAL_PWR_GetConfigGPIOPull Get I3C or XSPI GPIO pull configuration during standby.
  */

/**
  * @brief   Enable GPIO pull configuration.
  * @warning When APC bit is set, the I/O pull-up and pull-down configurations defined in PWR_I3CPUCR and PWR_XSPIPxCR
  *          registers are applied.
  * @note    Pull-up set by XSPIxxx_PU bit of PWR_XSPIPUCR register is not activated if the corresponding XSPIxxx_PD
  *          bit of PWR_XSPIPDCR register is also set (pull-down configuration priority is higher).
  *          HAL_PWR_LP_SetConfigGPIOPull() API ensure there is no conflict when setting XSPIxxx_PU or XSPIxxx_PD bit.
  *
  */
void HAL_PWR_EnableGPIOPull(void)
{
  LL_PWR_EnablePUPDConfig();
}

/**
  * @brief   Disable GPIO pull configuration.
  * @warning When APC bit is cleared, the I/O pull-up and pull-down configurations defined in PWR_I3CPUCR and
  *          PWR_XSPIPxCR registers are not applied.
  */
void HAL_PWR_DisableGPIOPull(void)
{
  LL_PWR_DisablePUPDConfig();
}

/**
  * @brief   Check that gpio pull is enabled.
  * @warning When APC bit is cleared, the I/O pull-up and pull-down configurations defined in PWR_I3CPUCR and
  *          PWR_XSPIPxCR registers are not applied.
  * @retval  hal_pwr_gpio_pull_config_status_t The GPIO pull status.
  */
hal_pwr_gpio_pull_config_status_t HAL_PWR_IsEnabledGPIOPull(void)
{
  return (hal_pwr_gpio_pull_config_status_t)LL_PWR_IsEnabledPUPDConfig();
}

/**
  * @brief Set peripheral(I3C or XSPI) GPIO pull configuration during standby.
  * @param periph This parameter is an element of \ref hal_pwr_pull_periph_t enumeration.
  * @param gpio This parameter is an element of \ref HAL_PWR_XSPI_PULL_PXXX or HAL_PWR_I3C_PULL_PXXX.
  * @param pull This parameter is an element of \ref hal_pwr_gpio_pull_t enumeration.
  * @warning configuration is applied on hardware system only if bit PWR_APCR_APC is set.
  * @retval HAL_OK XSPI pull standby has been correctly configured.
  */
void HAL_PWR_SetConfigGPIOPull(hal_pwr_pull_periph_t periph, uint32_t gpio, hal_pwr_gpio_pull_t pull)
{
  ASSERT_DBG_PARAM(IS_PWR_PERIPH_GPIO_PULL_SET_CONFIG(periph, gpio, pull));

  if (periph == HAL_PWR_PULL_PERIPH_I3C)
  {
    if (pull == HAL_PWR_GPIO_PULL_UP)
    {
      LL_PWR_EnableI3CPullUp(gpio);
    }
    else if (pull == HAL_PWR_GPIO_PULL_NO)
    {
      LL_PWR_DisableI3CPullUp(gpio);
    }
    else
    {
      /* Do nothing, I3C pin cannot be configurated in Pulldown */
    }
  }
  else
  {
    if (pull == HAL_PWR_GPIO_PULL_UP)
    {
      LL_PWR_DisableXSPIPullUp(gpio);
      LL_PWR_DisableXSPIPullDown(gpio);
    }
    else if (pull == HAL_PWR_GPIO_PULL_UP)
    {
      LL_PWR_EnableXSPIPullUp(gpio);
      /* Disable Pull Down XSPI GPIO cannot be in pull down and pull up*/
      LL_PWR_DisableXSPIPullDown(gpio);
    }
    else
    {
      LL_PWR_EnableXSPIPullDown(gpio);
      /* Disable Pull Down XSPI GPIO cannot be in pull down and pull up*/
      LL_PWR_DisableXSPIPullUp(gpio);
    }
  }
}

/**
  * @brief Get peripheral (I3C or XSPI) GPIO pull configuration during standby.
  * @param periph This parameter is an element of \ref hal_pwr_pull_periph_t enumeration.
  * @param gpio This parameter is an element of \ref HAL_PWR_XSPI_PULL_PXXX or HAL_PWR_I3C_PULL_PXXX.
  * @retval hal_pwr_gpio_pull_t The GPIO pull config.
  */
hal_pwr_gpio_pull_t HAL_PWR_GetConfigGPIOPull(hal_pwr_pull_periph_t periph, uint32_t gpio)
{
  hal_pwr_gpio_pull_t pull = HAL_PWR_GPIO_PULL_NO;
  uint32_t xspi_pull_up = 0;
  uint32_t xspi_pull_down = 0;

  ASSERT_DBG_PARAM(IS_PWR_PERIPH_GPIO_PULL_GET_CONFIG(periph, gpio));

  xspi_pull_up = LL_PWR_IsEnabledXSPIPullUp(gpio);
  xspi_pull_down = LL_PWR_IsEnabledXSPIPullDown(gpio);

  if (periph == HAL_PWR_PULL_PERIPH_I3C)
  {
    pull = (hal_pwr_gpio_pull_t)LL_PWR_IsEnabledI3CPullUp(gpio);
  }
  else
  {
    if ((xspi_pull_up == 1UL) && (xspi_pull_down == 0UL))
    {
      pull = HAL_PWR_GPIO_PULL_UP;
    }

    if ((xspi_pull_up == 0UL) && (xspi_pull_down == 1UL))
    {
      pull = HAL_PWR_GPIO_PULL_DOWN;
    }
  }

  return pull;
}
/**
  * @}
  */

/**
  * @}
  */

#endif /* USE_HAL_PWR_MODULE */
/**
  * @}
  */

/**
  * @}
  */
