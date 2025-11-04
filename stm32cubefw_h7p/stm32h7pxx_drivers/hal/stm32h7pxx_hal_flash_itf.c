/**
  **********************************************************************************************************************
  * @file    stm32h7pxx_hal_flash_itf.c
  * @author  GPM Application Team
  * @brief   This file provides FLASH peripheral services.
  **********************************************************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  **********************************************************************************************************************
  */

/* Includes ----------------------------------------------------------------------------------------------------------*/
#include "stm32_hal.h"

/** @addtogroup STM32H7Pxx_HAL_Driver
  * @{
  */

/** @addtogroup FLASH_ITF
  * @{
This file provides firmware functions to manage the following functionalities of FLASH option bytes peripheral:

- Control functions
- Lock and Unclock functions
- Configuration functions
- IRQHandler and Callback functions
- Status functions
- Launch functions

# FLASH interface main features

- The Flash Option Bytes, often referred to as "Option Bytes" or "OB" in the context of microcontrollers, are a set of
  configuration settings that can be programmed to customize the Behavior of the flash memory and other features of a
  microcontroller. These Option Bytes are typically stored in a special area of the flash memory and are used to control
  various aspects of the device's operation.

## Security context agnostic APIs :

  - It must be used by all the secure and non-secure users.
  - These APIs give to the user the granularity to start any operation within the secure world and non-secure world
    application by using the same APIs.

## Non-secure APIs :

  - It must be used only by secure user.
  - These APIs give to the user the hand to start non-secure operation within the secure world.
  - The non-secure APIs have the suffix _NS and flagged by the __ARM_FEATURE_CMSE define.

## Lock mechanism :

  - After reset, the FLASH control registers access are protected.
    The Unlock sequence is necessary to run any operation on the FLASH.

## Read access latency :
  - To correctly read data from flash memory, the number of wait states (latency) must be correctly programmed
    according to the frequency of the CPU clock, and the internal voltage range of the device VCORE.

## Prefetch :

  - Prefetch tends to increase the code execution performance at the cost extra flash memory accesses.
    It must be used carefully in low-power applications.

## Power down in run mode :

  - After reset, both banks are in normal mode. In order to reduce power consumption, each bank can be independently
    put in power-down mode.

## Power down in sleep mode :

  - After reset, the flash memory is in idle mode during sleep mode. In order to reduce power consumption, the flash
    memory can be put in power down mode during sleep mode.

## Low power read mode :

  - After reset, the flash memory is not in low power read mode. In order to reduce power consumption, the flash memory
    can be put in low power read mode.

## Error Code Correction :

  - Data in flash memory are 137-bit wide: Nine bits are added per quad-word (128 bits).
    The ECC mechanism supports :
      - One error detection and correction.
      - Two errors detection. In this case an NMI is generated.

## Option bytes :

  - Lock mechanism : After reset, the FLASH option bytes are write-protected.
                     The Unlock sequence is necessary to run any operation on the FLASH option bytes.

  - Write protection area : The user area in flash memory can be protected against unwanted write operations.
                            Two write-protected (WRP) areas can be defined in each bank.

  - Readout protection : The readout protection protects the flash main memory, the option bytes, the backup registers,
                         the backup RAM and the SRAM. To reach the highest level of security.
                         - When the TrustZone disable; 3 levels (0, 1 and 2) of protection available.
                         - When the TrustZone enabled; 4 levels (0, 0.5, 1 and 2) of protection available.
                         - It is recommended to set a password for the level1 and level2.

  - Secure Watermark area : Available only when the TrustZone enabled, a part of the flash memory can be protected
                            against non-secure read and write accesses. One area per bank can be selected.

  - Secure hide protection area : Available only when the TrustZone enabled, a part of the flash memory secure
                                  watermark area. Access to this area can be denied by using the
                                  LL_FLASH_DisableHDPAreaAccess() function.

  - Boot lock : Available only when the TrustZone enabled,some option bytes cannot be modified when the boot lock
                mechanism enabled.

  - Boot address : The boot address option bytes are used to program any boot memory address. However, the allowed
                   address space depends on flash memory read protection RDP level.

  - User option bytes : There are option bytes to include additional option to customize the behavior.
                        - Brown-out reset level, reset generation in low power mode, erase memories, watchdog selection,
                          Independent watchdog counter freeze, Bank swapping, Single/Dual bank, Memories ECC, Boot0,
                          I/O PullUP, High speed Low VDD, TrustZone

## Launch : When all new options are updated in the flash memory but they are not applied to the system.
            They affect the system when they are loaded. The option bytes loading is performed in two cases:
            - When OBL_LAUNCH is set in FLASH_NSCR
            - After a power reset (BOR reset or exit from Standby or Shutdown mode)

# How to use the FLASH_ITF HAL module driver

## Lock and Unclock functions :

- Use the HAL_FLASH_ITF_Lock() and FLASH_ITF_Unlock() functions to to lock and unlock the access to the FLASH control
  register.
- Use the FLASH_ITF_IsLocked() function to check the lock access state to the FLASH control register.
- Use the HAL_FLASH_ITFNS_Lock() and HAL_FLASH_ITFNS_Unlock() functions functions to lock and unlock the access to the
  non-secure FLASH control register.
- Use the HAL_FLASH_ITFNS_IsLocked() function to check the lock access state to the non-secure FLASH control register.

## Configuration functions :

- Use the HAL_FLASH_ITF_SetLatency() function to set the FLASH latency.
- Use the HAL_FLASH_ITF_GetLatency() function to get the FLASH latency.
- Use the HAL_FLASH_ITF_EnablePrefetch() function to enable the FLASH prefetch.
- Use the HAL_FLASH_ITF_DisablePrefetch() function to disable the FLASH prefetch.
- Use the HAL_FLASH_ITF_IsEnabledPrefetch() function to check if the FLASH prefetch is enabled or disabled.
- Use the HAL_FLASH_ITF_EnablePWRDownRunMode() function to enable the FLASH power down in running mode.
- Use the HAL_FLASH_ITF_IsEnabledPWRDownRunMode() function to check if the FLASH power down in running mode is enabled.
- Use the HAL_FLASH_ITF_EnablePWRDownSleepMode() function to enable the FLASH power down in sleep mode.
- Use the HAL_FLASH_ITF_DisablePWRDownSleepMode() function to disable the FLASH power down in sleep mode.
- Use the HAL_FLASH_ITF_IsEnabledPWRDownSleepMode() function to check if the FLASH power down in sleep mode is enabled
  or disabled.
- Use the HAL_FLASH_ITF_EnableLowPWRReadMode() function to enable the FLASH low power read mode.
- Use the HAL_FLASH_ITF_DisableLowPWRReadMode() function disable the FLASH low power read mode.
- Use the HAL_FLASH_ITF_IsEnabledLowPWRReadMode() function to check if the FLASH low power in read mode is enabled
  or disabled.
- Use the  HAL_FLASH_ITF_ECC_EnableIT() function to enable the FLASH ECC interruption.
- Use the  HAL_FLASH_ITF_ECC_DisableIT() function to disable the FLASH ECC interruption.

### Option Bytes Lock and Unclock functions :

- Use the HAL_FLASH_ITF_OB_Lock() function to lock the access to the FLASH option bytes registers.
- Use the HAL_FLASH_ITF_OB_Unlock() function to unlock the access to the FLASH option bytes registers.
- Use the HAL_FLASH_ITF_OB_IsLocked() function to check the lock state of the access to the FLASH option bytes
  registers.

### Write protection area configuration :

- Use the HAL_FLASH_ITF_OB_SetWRPArea() function to set the FLASH ITF OB write protection area configuration.
- Use the HAL_FLASH_ITF_OB_GetWRPArea() function to get the FLASH ITF OB write protection area configuration.
- Use the HAL_FLASH_ITF_OB_LockWRPAreaConfig() function to lock the FLASH option bytes write protection area
- Use the HAL_FLASH_ITF_OB_UnlockWRPAreaConfig() function to unlock the FLASH option bytes write protection area
  configuration.
- Use the HAL_FLASH_ITF_OB_IsLockedWRPAreaConfig() function to Check if the FLASH ITF OB write protection area
  configuration is locked or unlocked.

### Read out protection configuration :

- Use the HAL_FLASH_ITF_OB_SetRDPLevel() function to set the FLASH ITF OB readout protection level.
- Use the HAL_FLASH_ITF_OB_GetRDPLevel() function to get the FLASH ITF OB readout protection level.
- Use the HAL_FLASH_ITF_OB_SetRDPOEMKey() function to set the FLASH ITF OB readout protection OEM keys.

### BOR level configuration :

- Use the HAL_FLASH_ITF_OB_SetBORLevel() function to set the FLASH ITF OB BOR level.
- Use the HAL_FLASH_ITF_OB_GetBORLevel() function to get the FLASH ITF OB BOR level.

### Enter low power mode by reset generation configuration :

- Use the HAL_FLASH_ITF_OB_SetEnterLowPWRModeRstGeneration() function to set the FLASH ITF OB enter stop mode,
  standby mode or shutdown mode reset generation configuration.
- Use the HAL_FLASH_ITF_OB_GetEnterLowPWRModeRstGeneration() function to get the FLASH ITF OB enter stop mode,
  standby mode or shutdown mode reset generation configuration.

### SRAM System reset erase configuration :

- Use the HAL_FLASH_ITF_OB_SetSystemRstSRAMErase() function to set the FLASH ITF OB system reset SRAM and SRAM2 erase
  configuration.
- Use the HAL_FLASH_ITF_OB_GetSystemRstSRAMErase() function to get the FLASH ITF OB system reset SRAM and SRAM2 erase
  configuration.

### WDG Mode configuration :

- Use the HAL_FLASH_ITF_OB_SetxWDGMode() function to set the FLASH ITF OB IWDG and WWDG mode configuration.
- Use the HAL_FLASH_ITF_OB_GetxWDGMode() function to get the FLASH ITF OB IWDG and WWDG mode configuration.

### WDG counter freeze configuration :

- Use the HAL_FLASH_ITF_OB_FreezexWDGCounterLowPWRMode() function to freeze the FLASH ITF OB IWDG for stop and standby
  counter configuration.
- Use the HAL_FLASH_ITF_OB_UnfreezexWDGCounterLowPWRMode() function to unfreeze the FLASH ITF OB IWDG stop and standby
  counter configuration.
- Use the HAL_FLASH_ITF_OB_IsFrozenxWDGCounterLowPWRMode() function to check the FLASH ITF OB IWDG stop and standby
  counter configuration is enabled.

### Bank swapping configuration :

- Use the HAL_FLASH_ITF_OB_SetBankSwap() function to set the FLASH ITF OB swap bank configuration.
- Use the HAL_FLASH_ITF_OB_GetBankSwap() function to get the FLASH ITF OB swap bank configuration.

### Bank configuration :

- Use the HAL_FLASH_ITF_OB_SetBankTopology() function to set the FLASH ITF OB single dual bank configuration.
- Use the HAL_FLASH_ITF_OB_GetBankTopology() function to get the FLASH ITF OB single dual bank configuration.

### SRAM ECC configuration :

- Use the HAL_FLASH_ITF_OB_EnableSRAMECC() function to enable the FLASH ITF OB for BKPRAM, SRAM2 and SRAM3 ECC
  configuration.
- Use the HAL_FLASH_ITF_OB_DisableSRAMECC() function to disable the FLASH ITF OB for BKPRAM, SRAM2 and SRAM3 ECC
  configuration.
- Use the HAL_FLASH_ITF_OB_IsEnabledSRAMECC() function to check the FLASH ITF OB for BKPRAM, SRAM2 and SRAM3 ECC
  configuration is enabled.

### Boot0 configuration :

- Use the HAL_FLASH_ITF_OB_SetBoot0() function to set the FLASH ITF OB boot0 configuration.
- Use the HAL_FLASH_ITF_OB_GetBoot0() function to get the FLASH ITF OB boot0 configuration.

### I/O PullUP configuration :

- Use the HAL_FLASH_ITF_OB_SetIOPull() function to enable and disable the FLASH ITF OB PA15 PullUP configuration.
- Use the HAL_FLASH_ITF_OB_GetIOPull() function to check if the FLASH ITF OB PA15 PullUP configuration is enabled.

### VDD High speed Low configuration :

- Use the HAL_FLASH_ITF_OB_EnableVddxHighSpeedLowVoltage() function to enable the FLASH ITF OB High speed Low
  VDDIO/VDDIO2 configuration.
- Use the HAL_FLASH_ITF_OB_DisableVddxHighSpeedLowVoltage() function to disable the FLASH ITF OB High speed Low
  VDDIO/VDDIO2 configuration.
- Use the HAL_FLASH_ITF_OB_IsEnabledVddxHighSpeedLowVoltage() function to check the FLASH ITF OB High speed Low
  VDDIO/VDDIO2 configuration is enabled.

### TrustZone configuration :

- Use the HAL_FLASH_ITF_OB_EnableTrustZone() function to enable the FLASH ITF OB TrustZone configuration.
- Use the HAL_FLASH_ITF_OB_DisableTrustZone() function to disable the FLASH ITF OB TrustZone configuration.
- Use the HAL_FLASH_ITF_OB_IsEnabledTrustZone() function to check the FLASH ITF OB TrustZone configuration is enabled.

### WaterMark configuration :

- Use the HAL_FLASH_ITF_OB_SetSecureWMArea() function to set the FLASH ITF OB secure watermark area configuration.
- Use the HAL_FLASH_ITF_OB_GetSecureWMArea() function to get the FLASH ITF OB secure watermark area configuration.

### Hide protection configuration :

- Use the HAL_FLASH_ITF_OB_SetConfigHDPArea() function to set the FLASH ITF OB hide protection area configuration.
- Use the HAL_FLASH_ITF_OB_GetConfigHDPArea() function to get the FLASH ITF OB hide protection area configuration.
- Use the HAL_FLASH_ITF_OB_EnableHDPArea() function to enable the FLASH ITF OB hide protection area configuration.
- Use the HAL_FLASH_ITF_OB_DisableHDPArea() function to disable the FLASH ITF OB hide protection area configuration.
- Use the HAL_FLASH_ITF_OB_IsEnabledHDPArea() function to check if the FLASH ITF OB hide protection area configuration
  is enabled or disabled.

### Boot address configuration :

- Use the HAL_FLASH_ITF_OB_SetSecureBootAddr() function to set the FLASH OB secure boot address configuration.
- Use the HAL_FLASH_ITF_OB_GetSecureBootAddr() function to get the FLASH OB secure boot address configuration.
- Use the HAL_FLASH_ITF_OB_SetNSecureBootAddr() function to set the FLASH OB non-secure boot address configuration.
- Use the HAL_FLASH_ITF_OB_GetNSecureBootAddr() function to get the FLASH OB non-secure boot address configuration.
- Use the HAL_FLASH_ITF_OB_LockBootConfig() function to lock the FLASH option bytes secure boot address
  configuration.
- Use the HAL_FLASH_ITF_OB_UnlockBootConfig() function to unlock the FLASH option bytes secure boot address
  configuration.
- Use the HAL_FLASH_ITF_OB_IsLockedBootConfig() function to Check if the FLASH ITF OB secure boot address configuration
  is locked or unlocked.

### IRQHandler and Callback functions :

- Use the HAL_FLASH_ITF_IRQHandler() function to handle Flash ECC error correction and OB write/error operations.
- Use the HAL_FLASH_ITF_NMI_IRQHandler() function which called under NMI_IRQHandler interrupt subroutine to handle the
  ECCD interrupt.
- Use the HAL_FLASH_ITF_ECC_IRQHandler() function to handle any enabled interrupt and call its corresponding callback.
- Use the HAL_FLASH_ITF_NMI_ECC_IRQHandler() function to Handle the FLASH ECCD interrupt request.
- Use the HAL_FLASH_ITF_ECC_ErrorCallback() function to be redefined within application for the ecc error correction
  callback.
- Use the HAL_FLASH_ITF_OB_ProgramCpltCallback() function to handle the OB complete write operations.
- Use the HAL_FLASH_ITF_OB_ErrorCallback() function to handle OB write error operation.

### Status functions :

- Use the HAL_FLASH_ITF_ECC_GetFailInfo() to get the FLASH ITF ECC fail information.

## Launch functions

- Use HAL_FLASH_ITF_OB_Launch() function to launch the reload of the FLASH option bytes.

# Configuration inside the FLASH driver

Configuration defines         | Description     | Default value   | Note                                               |
------------------------------|-----------------|-----------------|----------------------------------------------------|
PRODUCT                       | from IDE        |        NA       | The selected device (ex STM32H7P75xx)              |
USE_HAL_FLASH_MODULE          | from hal_conf.h |        1        | Allows to use HAL FLASH ITF module.                |
USE_ASSERT_DBG_PARAM          | from IDE        |      None       | Allows to use the assert check parameters.         |
USE_HAL_FLASH_ECC             | from hal_conf.h |        1        | Allows to use ECC errors features APIs.            |
  */

#if defined (USE_HAL_FLASH_MODULE) && (USE_HAL_FLASH_MODULE == 1)

/* Private Constants -------------*/
/** @defgroup FLASH_ITF_Private_Constants FLASH ITF Private Constants
  * @{
  */
#define FLASH_ITF_OB_TIMEOUT      1000U                                                        /*!< FLASH default OB timeout */
#define FLASH_ITF_OB_LOW_PWR_MSK  (HAL_FLASH_ITF_OB_STOP_MODE | HAL_FLASH_ITF_OB_STANDBY_MODE) /*!< FLASH low power mask     */
#define FLASH_ITF_OB_WDG_MSK      (HAL_FLASH_ITF_OB_IWDG)                                      /*!< FLASH wdg mask           */
#define FLASH_ITF_OB_SRAM_ECC_MSK (HAL_FLASH_ITF_OB_SRAM)                                      /*!< FLASH sram ecc mask      */
#define FLASH_ITF_OB_VDDIO_MSK    (HAL_FLASH_ITF_OB_VDDIO)                                     /*!< FLASH vdd mask           */
/**
  * @}
  */

/* Private macros ----------------*/
/** @defgroup FLASH_ITF_Private_Macros FLASH ITF Private Macros
  * @{
  */

/*! Macro to check FLASH instance */
#define IS_FLASH_INSTANCE(instance) ((instance) == HAL_FLASH)

/*! Macro to check FLASH memory bank */
#define IS_FLASH_BANK(value) (((value) == HAL_FLASH_BANK_1) || ((value) == HAL_FLASH_BANK_2))

/*! Macro to check FLASH ITF latency */
#define IS_FLASH_ITF_LATENCY(value) (((value) == HAL_FLASH_ITF_LATENCY_0)     \
                                     || ((value) == HAL_FLASH_ITF_LATENCY_1)  \
                                     || ((value) == HAL_FLASH_ITF_LATENCY_2)  \
                                     || ((value) == HAL_FLASH_ITF_LATENCY_3)  \
                                     || ((value) == HAL_FLASH_ITF_LATENCY_4)  \
                                     || ((value) == HAL_FLASH_ITF_LATENCY_5)  \
                                     || ((value) == HAL_FLASH_ITF_LATENCY_6)  \
                                     || ((value) == HAL_FLASH_ITF_LATENCY_7)  \
                                     || ((value) == HAL_FLASH_ITF_LATENCY_8)  \
                                     || ((value) == HAL_FLASH_ITF_LATENCY_9)  \
                                     || ((value) == HAL_FLASH_ITF_LATENCY_10) \
                                     || ((value) == HAL_FLASH_ITF_LATENCY_11) \
                                     || ((value) == HAL_FLASH_ITF_LATENCY_12) \
                                     || ((value) == HAL_FLASH_ITF_LATENCY_13) \
                                     || ((value) == HAL_FLASH_ITF_LATENCY_14) \
                                     || ((value) == HAL_FLASH_ITF_LATENCY_15))

/*! Macro to check FLASH memory programming delay */
#define IS_FLASH_ITF_PROGRAM_DELAY(value) (((value) == HAL_FLASH_ITF_PROGRAM_DELAY_0)    \
                                           || ((value) == HAL_FLASH_ITF_PROGRAM_DELAY_1) \
                                           || ((value) == HAL_FLASH_ITF_PROGRAM_DELAY_2) \
                                           || ((value) == HAL_FLASH_ITF_PROGRAM_DELAY_3))

/*! Macro to check FLASH ITF hdp extension state */
#define IS_FLASH_ITF_HDP_EXT_STATE(value) (((value) == HAL_FLASH_ITF_HDP_NO_ACCESS_PROTECTION)  \
                                           || ((value) == HAL_FLASH_ITF_HDP_ONLY_AREA_ACCESS_PROTECTION) \
                                           || ((value) == HAL_FLASH_ITF_HDP_ALL_ACCESS_PROTECTION))

/*! Macro to check FLASH ITF OB bank area */
#define IS_FLASH_ITF_OB_BANK_AREA(value) (((value) == HAL_FLASH_ITF_OB_BANK_AREA_A) \
                                          || ((value) == HAL_FLASH_ITF_OB_BANK_AREA_B))

/*! Macro to check FLASH ITF OB key hdp level */
#define IS_FLASH_ITF_OBK_HDPL(value) (((value) == HAL_FLASH_ITF_OBK_LEVEL_CURRENT) \
                                      || ((value) == HAL_FLASH_ITF_OBK_LEVEL_NEXT) \
                                      || ((value) == HAL_FLASH_ITF_OBK_LEVEL_PLUS_TWO))

/*! Macro to check FLASH ITF OB debug authentication method */
#define IS_FLASH_ITF_OB_DBG_AUTH(value) (((value) == HAL_FLASH_ITF_OB_DBG_AUTH_DEFAULT) \
                                         || ((value) == HAL_FLASH_ITF_OB_DBG_AUTH_PASSWORD) \
                                         || ((value) == HAL_FLASH_ITF_OB_DBG_AUTH_LOCKED))

/*! Macro to check FLASH ITF OB OEM provisioning state */
#define IS_FLASH_ITF_OB_OEM_PROV(value) (((value) == HAL_FLASH_ITF_OB_OEM_PROVD_ENABLE) \
                                         || ((value) == HAL_FLASH_ITF_OB_OEM_PROVD_DEFAULT))

/*! Macro to check FLASH ITF OB boot lock state */
#define IS_FLASH_ITF_OB_BOOT_LOCK_STATE(value) (((value) == HAL_FLASH_ITF_OB_BOOT_UNLOCKED) \
                                                || ((value) == HAL_FLASH_ITF_OB_BOOT_LOCKED))

/*! Macro to check FLASH ITF OB bor level */
#define IS_FLASH_ITF_OB_BOR_LEVEL(value) (((value) == HAL_FLASH_ITF_OB_BOR_LEVEL_0) \
                                          || ((value) == HAL_FLASH_ITF_OB_BOR_LEVEL_1) \
                                          || ((value) == HAL_FLASH_ITF_OB_BOR_LEVEL_2) \
                                          || ((value) == HAL_FLASH_ITF_OB_BOR_LEVEL_3))

/*! Macro to check FLASH ITF OB non-volatile state */
#define IS_FLASH_ITF_OB_NVSTATE(value) (((value) == HAL_FLASH_ITF_OB_NVSTATE_OPEN) \
                                        || ((value) == HAL_FLASH_ITF_OB_NVSTATE_CLOSE))

/*! Macro to check FLASH ITF OB low power mode */
#define IS_FLASH_ITF_OB_LOW_PWR_MODE(value) (((value) == HAL_FLASH_ITF_OB_STOP_MODE) \
                                             || ((value) == HAL_FLASH_ITF_OB_STANDBY_MODE))

/*! Macro to check FLASH ITF OB low power reset generation */
#define IS_FLASH_ITF_OB_RST_GENERATION_STATUS(value) (((value) == HAL_FLASH_ITF_OB_RST_GENERATION) \
                                                      || ((value) == HAL_FLASH_ITF_OB_NO_RST_GENERATION))

/*! Macro to check FLASH ITF OB wdg */
#define IS_FLASH_ITF_OB_WDG(value) (((value) == HAL_FLASH_ITF_OB_IWDG))

/*! Macro to check FLASH ITF OB wdg hardware/software mode */
#define IS_FLASH_ITF_OB_WDG_HW_SW_MODE(value) (((value) == HAL_FLASH_ITF_OB_WDG_HARDWARE) \
                                               || ((value) == HAL_FLASH_ITF_OB_WDG_SOFTWARE))

/*! Macro to check FLASH ITF OB swap bank */
#define IS_FLASH_ITF_OB_SWAP_BANK(value) (((value) == HAL_FLASH_ITF_OB_BANK_NO_SWAP) \
                                          || ((value) == HAL_FLASH_ITF_OB_BANK_SWAP))

/*! Macro to check FLASH ITF OB single dual bank */
#define IS_FLASH_ITF_OB_SINGLE_DUAL_BANK(value) (((value) == HAL_FLASH_ITF_OB_SINGLE_BANK) \
                                                 || ((value) == HAL_FLASH_ITF_OB_DUAL_BANK))

/*! Macro to check FLASH ITF OB sram ecc */
#define IS_FLASH_ITF_OB_SRAM_ECC(value) (((value) == HAL_FLASH_ITF_OB_SRAM))

/*! Macro to check FLASH ITF OB vdd */
#define IS_FLASH_ITF_OB_VDD(value) (((value) == HAL_FLASH_ITF_OB_VDDIO))

/*! Macro to get the FLASH ITF instance */
#define FLASH_ITF_GET_INSTANCE(instance) ((FLASH_TypeDef *)((uint32_t)instance))
/**
  * @}
  */

/* Private Functions Prototypes --------------------------------------------------------------------------------------*/
/** @defgroup FLASH_ITF_Private_Functions FLASH ITF Private Functions
  * @{
  */
static hal_status_t FLASH_ITF_CheckForEndOfOperation(hal_flash_t instance);
/**
  * @}
  */

/* Exported functions ------------------------------------------------------------------------------------------------*/
/** @addtogroup FLASH_ITF_Exported_Functions
  * @{
  */

/** @addtogroup FLASH_ITF_Exported_Functions_Group1
  * @{

This subsection provides a set of functions allowing to lock/unlock and configure the FLASH ITF peripheral:

- Call the function HAL_FLASH_ITF_Lock() to lock the access to the FLASH control register for both bank.

- Call the function HAL_FLASH_ITF_Unlock() to unlock the access to the FLASH control register for both bank.

- Call the function HAL_FLASH_ITF_IsLocked() to check the lock access state to the FLASH control register for both bank.

- Call the function HAL_FLASH_ITF_LockBank() to lock the access to the FLASH control register by bank.

- Call the function HAL_FLASH_ITF_UnlockBank() to unlock the access to the FLASH control register by bank.

- Call the function HAL_FLASH_ITF_IsLockedBank() to check the lock access state to the FLASH control register by bank.

- Call the function HAL_FLASH_ITF_SetLatency() to set the latency according to selected parameter within
  hal_flash_itf_latency_t enumeration.

- Call the function HAL_FLASH_ITF_GetLatency() to get the current configured latency.

- Call the function HAL_FLASH_ITF_SetProgrammingDelay() to set the programming delay according to selected parameter
  within hal_flash_itf_program_delay_t enumeration.

- Call the function HAL_FLASH_ITF_GetProgrammingDelay() to get the current configured programming delay.


- Call the function HAL_FLASH_ITF_SetHDPExtArea() to set the HDP extended area.

- Call the function HAL_FLASH_ITF_GetHDPExtArea() to get the HDP extended area.

- Call the function HAL_FLASH_ITF_SetHDPExtAccessProtection() to set the HDP extended access protection according to
  selected parameter within hal_flash_itf_hdp_access_protection_t enumeration.

- Call the function HAL_FLASH_ITF_GetHDPExtAccessProtection() to get the HDP extended access protection.

- Call the function HAL_FLASH_ITF_ECC_EnableSingleErrorIT() to enable the single ECC interruption.

- Call the function HAL_FLASH_ITF_ECC_DisableSingleErrorIT() to disable the single ECC interruption.

- Call the function HAL_FLASH_ITF_ECC_IsEnabledSingleErrorIT() to check if the single ECC interruption is enabled.

- Call the function HAL_FLASH_ITF_ECC_EnableDoubleErrorIT() to enable the double ECC interruption.

- Call the function HAL_FLASH_ITF_ECC_DisableDoubleErrorIT() to disable the double ECC interruption.

- Call the function HAL_FLASH_ITF_ECC_IsEnabledDoubleErrorIT() to check if the double ECC interruption is enabled.

  */

/**
  * @brief  Lock the FLASH ITF control register access for both bank.
  * @param  instance This parameter is one element of \ref hal_flash_t enumeration.
  * @retval HAL_OK The FLASH registers access locked.
  */
hal_status_t HAL_FLASH_ITF_Lock(hal_flash_t instance)
{
  ASSERT_DBG_PARAM(IS_FLASH_INSTANCE(instance));

  LL_FLASH_Lock(FLASH_ITF_GET_INSTANCE(instance), LL_FLASH_BANK_1);
  LL_FLASH_Lock(FLASH_ITF_GET_INSTANCE(instance), LL_FLASH_BANK_2);

  return HAL_OK;
}

/**
  * @brief  Unlock the FLASH ITF control register access for both bank.
  * @param  instance This parameter is one element of \ref hal_flash_t enumeration.
  * @retval HAL_OK The FLASH registers access unlocked.
  */
hal_status_t HAL_FLASH_ITF_Unlock(hal_flash_t instance)
{
  ASSERT_DBG_PARAM(IS_FLASH_INSTANCE(instance));

  if (LL_FLASH_IsLocked(FLASH_ITF_GET_INSTANCE(instance), LL_FLASH_BANK_1) != 0U)
  {
    LL_FLASH_SetUnlockKey(FLASH_ITF_GET_INSTANCE(instance), LL_FLASH_BANK_1, LL_FLASH_KEY1);
    LL_FLASH_SetUnlockKey(FLASH_ITF_GET_INSTANCE(instance), LL_FLASH_BANK_1, LL_FLASH_KEY2);
  }

  if (LL_FLASH_IsLocked(FLASH_ITF_GET_INSTANCE(instance), LL_FLASH_BANK_2) != 0U)
  {
    LL_FLASH_SetUnlockKey(FLASH_ITF_GET_INSTANCE(instance), LL_FLASH_BANK_2, LL_FLASH_KEY1);
    LL_FLASH_SetUnlockKey(FLASH_ITF_GET_INSTANCE(instance), LL_FLASH_BANK_2, LL_FLASH_KEY2);
  }

  return HAL_OK;
}

/**
  * @brief  Check if the FLASH ITF control register access is locked or unlocked for both bank.
  * @param  instance This parameter is one element of \ref hal_flash_t enumeration.
  * @retval hal_flash_itf_lock_status_t FLASH control register access lock status.
  */
hal_flash_itf_lock_status_t HAL_FLASH_ITF_IsLocked(hal_flash_t instance)
{
  uint32_t is_locked;

  ASSERT_DBG_PARAM(IS_FLASH_INSTANCE(instance));

  is_locked = LL_FLASH_IsLocked(FLASH_ITF_GET_INSTANCE(instance), LL_FLASH_BANK_1);
  is_locked = (is_locked == 0U) ? LL_FLASH_IsLocked(FLASH_ITF_GET_INSTANCE(instance), LL_FLASH_BANK_2) : 1U;

  return ((hal_flash_itf_lock_status_t)is_locked);
}

/**
  * @brief  Lock the FLASH ITF control register access by bank.
  * @param  instance This parameter is one element of \ref hal_flash_t enumeration.
  * @param  bank This parameter is one element of \ref hal_flash_bank_t enumeration.
  * @retval HAL_OK The FLASH registers access locked.
  */
hal_status_t HAL_FLASH_ITF_LockBank(hal_flash_t instance, hal_flash_bank_t bank)
{
  ASSERT_DBG_PARAM(IS_FLASH_INSTANCE(instance));
  ASSERT_DBG_PARAM(IS_FLASH_BANK(bank));

  LL_FLASH_Lock(FLASH_ITF_GET_INSTANCE(instance), (uint32_t) bank);

  return HAL_OK;
}

/**
  * @brief  Unlock the FLASH ITF control register access by bank.
  * @param  instance This parameter is one element of \ref hal_flash_t enumeration.
  * @param  bank This parameter is one element of \ref hal_flash_bank_t enumeration.
  * @retval HAL_OK The FLASH registers access unlocked.
  */
hal_status_t HAL_FLASH_ITF_UnlockBank(hal_flash_t instance, hal_flash_bank_t bank)
{
  ASSERT_DBG_PARAM(IS_FLASH_INSTANCE(instance));
  ASSERT_DBG_PARAM(IS_FLASH_BANK(bank));

  if (LL_FLASH_IsLocked(FLASH_ITF_GET_INSTANCE(instance), (uint32_t)bank) != 0U)
  {
    LL_FLASH_SetUnlockKey(FLASH_ITF_GET_INSTANCE(instance), (uint32_t)bank, LL_FLASH_KEY1);
    LL_FLASH_SetUnlockKey(FLASH_ITF_GET_INSTANCE(instance), (uint32_t)bank, LL_FLASH_KEY2);
  }

  return HAL_OK;
}

/**
  * @brief  Check if the FLASH ITF control register access is locked or unlocked by bank.
  * @param  instance This parameter is one element of \ref hal_flash_t enumeration.
  * @param  bank This parameter is one element of \ref hal_flash_bank_t enumeration.
  * @retval hal_flash_itf_lock_status_t FLASH control register access lock status.
  */
hal_flash_itf_lock_status_t HAL_FLASH_ITF_IsLockedBank(hal_flash_t instance, hal_flash_bank_t bank)
{
  ASSERT_DBG_PARAM(IS_FLASH_INSTANCE(instance));
  ASSERT_DBG_PARAM(IS_FLASH_BANK(bank));

  return ((hal_flash_itf_lock_status_t)LL_FLASH_IsLocked(FLASH_ITF_GET_INSTANCE(instance), (uint32_t) bank));
}

/**
  * @brief  Set the FLASH ITF latency configuration.
  * @param  instance This parameter is one element of \ref hal_flash_t enumeration.
  * @param  latency This parameter is one element of \ref hal_flash_itf_latency_t enumeration.
  * @retval HAL_OK  Latency is successfully configured.
  */
hal_status_t HAL_FLASH_ITF_SetLatency(hal_flash_t instance, hal_flash_itf_latency_t latency)
{
  ASSERT_DBG_PARAM(IS_FLASH_INSTANCE(instance));
  ASSERT_DBG_PARAM(IS_FLASH_ITF_LATENCY(latency));

  LL_FLASH_SetLatency(FLASH_ITF_GET_INSTANCE(instance), (uint32_t)latency);

  return HAL_OK;
}

/**
  * @brief  Get the FLASH ITF latency configuration.
  * @param  instance This parameter is one element of \ref hal_flash_t enumeration.
  * @retval hal_flash_itf_latency_t Latency value.
  */
hal_flash_itf_latency_t HAL_FLASH_ITF_GetLatency(hal_flash_t instance)
{
  ASSERT_DBG_PARAM(IS_FLASH_INSTANCE(instance));

  return ((hal_flash_itf_latency_t)LL_FLASH_GetLatency(FLASH_ITF_GET_INSTANCE(instance)));
}

/**
  * @brief  Set the FLASH programming delay configuration.
  * @param  instance This parameter is one element of \ref hal_flash_t enumeration.
  * @param  prog_delay This parameter is one element of \ref hal_flash_itf_programming_delay_t enumeration.
  * @retval HAL_OK  Programming Delay is successfully configured.
  */
hal_status_t HAL_FLASH_ITF_SetProgrammingDelay(hal_flash_t instance, hal_flash_itf_program_delay_t prog_delay)
{
  ASSERT_DBG_PARAM(IS_FLASH_INSTANCE(instance));
  ASSERT_DBG_PARAM(IS_FLASH_ITF_PROGRAM_DELAY(prog_delay));

  LL_FLASH_SetProgrammingDelay(FLASH_ITF_GET_INSTANCE(instance), (uint32_t)prog_delay);

  return HAL_OK;
}

/**
  * @brief  Get the FLASH programming delay configuration.
  * @param  instance This parameter is one element of \ref hal_flash_t enumeration.
  * @retval hal_flash_itf_program_delay_t programming delay value.
  */
hal_flash_itf_program_delay_t HAL_FLASH_ITF_GetProgrammingDelay(hal_flash_t instance)
{
  ASSERT_DBG_PARAM(IS_FLASH_INSTANCE(instance));

  return ((hal_flash_itf_program_delay_t)LL_FLASH_GetProgrammingDelay(FLASH_ITF_GET_INSTANCE(instance)));
}

/**
  * @brief  Set the HDP Extended area.
  * @param  instance This parameter is one element of \ref hal_flash_t enumeration.
  * @param  bank     This parameter is one element of \ref hal_flash_ob_bank_t enumeration.
  * @param  page     This parameter can be any value between 0 and the maximum number of pages per bank.
  * @retval HAL_OK HDP Extended area number of pages set.
  */
hal_status_t HAL_FLASH_ITF_SetHDPExtArea(hal_flash_t instance, hal_flash_bank_t bank, uint32_t page)
{
  ASSERT_DBG_PARAM(IS_FLASH_INSTANCE(instance));
  ASSERT_DBG_PARAM(IS_FLASH_BANK(bank));
  ASSERT_DBG_PARAM(page < FLASH_PAGE_NB);

  LL_FLASH_SetHDPExtArea(FLASH_ITF_GET_INSTANCE(instance), (uint32_t)bank, page);

  return HAL_OK;
}

/**
  * @brief  Get the HDP Extended area.
  * @param  instance This parameter is one element of \ref hal_flash_t enumeration.
  * @param  bank     This parameter is one element of \ref hal_flash_ob_bank_t enumeration.
  * @retval uint32_t HDP Extended area number of pages value, between 0 and the maximum number of pages per bank.
  */
uint32_t HAL_FLASH_ITF_GetHDPExtArea(hal_flash_t instance, hal_flash_bank_t bank)
{
  ASSERT_DBG_PARAM(IS_FLASH_INSTANCE(instance));
  ASSERT_DBG_PARAM(IS_FLASH_BANK(bank));

  return LL_FLASH_GetHDPExtArea(FLASH_ITF_GET_INSTANCE(instance), (uint32_t)bank);
}

/**
  * @brief  Set the HDP Extended state.
  * @param  instance      This parameter is one element of \ref hal_flash_t enumeration.
  * @param  bank          This parameter is one element of \ref hal_flash_bank_t enumeration.
  * @param  hdp_ext_state This parameter is one element of \ref hal_flash_itf_hdp_access_protection_t enumeration.
  * @retval HAL_OK HDP Extended state set.
  */
hal_status_t HAL_FLASH_ITF_SetHDPExtAccessProtection(hal_flash_t instance,
                                                     hal_flash_bank_t bank,
                                                     hal_flash_itf_hdp_access_protection_t hdp_ext_access)
{
  ASSERT_DBG_PARAM(IS_FLASH_INSTANCE(instance));
  ASSERT_DBG_PARAM(IS_FLASH_BANK(bank));
  ASSERT_DBG_PARAM(IS_FLASH_ITF_HDP_EXT_STATE(hdp_ext_access));

  LL_FLASH_SetHDPExtAccessProtection(FLASH_ITF_GET_INSTANCE(instance), (uint32_t)bank, (uint32_t)hdp_ext_access);

  return HAL_OK;
}

/**
  * @brief  Get the HDP Extended state.
  * @param  instance This parameter is one element of \ref hal_flash_t enumeration.
  * @param  bank     This parameter is one element of \ref hal_flash_ob_bank_t enumeration.
  * @retval hal_flash_itf_hdp_access_protection_t HDP extension state.
  */
hal_flash_itf_hdp_access_protection_t HAL_FLASH_ITF_GetHDPExtAccessProtection(hal_flash_t instance,
                                                                              hal_flash_bank_t bank)
{
  ASSERT_DBG_PARAM(IS_FLASH_INSTANCE(instance));
  ASSERT_DBG_PARAM(IS_FLASH_BANK(bank));

  return (hal_flash_itf_hdp_access_protection_t)LL_FLASH_GetHDPExtAccessProtection(FLASH_ITF_GET_INSTANCE(instance),
         (uint32_t)bank);
}

#if defined (USE_HAL_FLASH_ECC) && (USE_HAL_FLASH_ECC == 1U)
/**
  * @brief  Enable the FLASH ITF ECC interruption.
  * @param  instance This parameter is one element of \ref hal_flash_t enumeration.
  * @param  bank     This parameter is one element of \ref hal_flash_bank_t enumeration.
  * @retval HAL_OK ECC interruption enabled.
  */
hal_status_t HAL_FLASH_ITF_ECC_EnableSingleErrorIT(hal_flash_t instance, hal_flash_bank_t bank)
{
  ASSERT_DBG_PARAM(IS_FLASH_INSTANCE(instance));
  ASSERT_DBG_PARAM(IS_FLASH_BANK(bank));

  LL_FLASH_EnableIT_SNECCERR(FLASH_ITF_GET_INSTANCE(instance), (uint32_t)bank);

  return HAL_OK;
}

/**
  * @brief  Disable the FLASH ITF ECC interruption.
  * @param  instance This parameter is one element of \ref hal_flash_t enumeration.
  * @param  bank     This parameter is one element of \ref hal_flash_bank_t enumeration.
  * @retval HAL_OK ECC interruption disabled.
  */
hal_status_t HAL_FLASH_ITF_ECC_DisableSingleErrorIT(hal_flash_t instance, hal_flash_bank_t bank)
{
  ASSERT_DBG_PARAM(IS_FLASH_INSTANCE(instance));
  ASSERT_DBG_PARAM(IS_FLASH_BANK(bank));

  LL_FLASH_DisableIT_SNECCERR(FLASH_ITF_GET_INSTANCE(instance), (uint32_t)bank);

  return HAL_OK;
}

/**
  * @brief  Check if the FLASH ITF ECC interruption is enabled.
  * @param  instance This parameter is one element of \ref hal_flash_t enumeration.
  * @param  bank     This parameter is one element of \ref hal_flash_bank_t enumeration.
  * @retval HAL_OK ECC interruption disabled.
  */
hal_flash_itf_ecc_it_status_t HAL_FLASH_ITF_ECC_IsEnabledSingleErrorIT(hal_flash_t instance, hal_flash_bank_t bank)
{
  ASSERT_DBG_PARAM(IS_FLASH_INSTANCE(instance));
  ASSERT_DBG_PARAM(IS_FLASH_BANK(bank));

  return (hal_flash_itf_ecc_it_status_t)LL_FLASH_IsEnabledIT_SNECCERR(FLASH_ITF_GET_INSTANCE(instance), (uint32_t)bank);
}

/**
  * @brief  Enable the FLASH ITF ECC interruption.
  * @param  instance This parameter is one element of \ref hal_flash_t enumeration.
  * @param  bank     This parameter is one element of \ref hal_flash_bank_t enumeration.
  * @retval HAL_OK ECC interruption enabled.
  */
hal_status_t HAL_FLASH_ITF_ECC_EnableDoubleErrorIT(hal_flash_t instance, hal_flash_bank_t bank)
{
  ASSERT_DBG_PARAM(IS_FLASH_INSTANCE(instance));
  ASSERT_DBG_PARAM(IS_FLASH_BANK(bank));

  LL_FLASH_EnableIT_DBECCERR(FLASH_ITF_GET_INSTANCE(instance), (uint32_t)bank);

  return HAL_OK;
}

/**
  * @brief  Disable the FLASH ITF ECC interruption.
  * @param  instance This parameter is one element of \ref hal_flash_t enumeration.
  * @param  bank     This parameter is one element of \ref hal_flash_bank_t enumeration.
  * @retval HAL_OK ECC interruption disabled.
  */
hal_status_t HAL_FLASH_ITF_ECC_DisableDoubleErrorIT(hal_flash_t instance, hal_flash_bank_t bank)
{
  ASSERT_DBG_PARAM(IS_FLASH_INSTANCE(instance));
  ASSERT_DBG_PARAM(IS_FLASH_BANK(bank));

  LL_FLASH_DisableIT_DBECCERR(FLASH_ITF_GET_INSTANCE(instance), (uint32_t)bank);

  return HAL_OK;
}

/**
  * @brief  Check if the FLASH ITF ECC interruption is enabled.
  * @param  instance This parameter is one element of \ref hal_flash_t enumeration.
  * @param  bank     This parameter is one element of \ref hal_flash_bank_t enumeration.
  * @retval HAL_OK ECC interruption disabled.
  */
hal_flash_itf_ecc_it_status_t HAL_FLASH_ITF_ECC_IsEnabledDoubleErrorIT(hal_flash_t instance, hal_flash_bank_t bank)
{
  ASSERT_DBG_PARAM(IS_FLASH_INSTANCE(instance));
  ASSERT_DBG_PARAM(IS_FLASH_BANK(bank));

  return (hal_flash_itf_ecc_it_status_t)LL_FLASH_IsEnabledIT_DBECCERR(FLASH_ITF_GET_INSTANCE(instance), (uint32_t)bank);
}
#endif /* USE_HAL_FLASH_ECC */
/**
  * @}
  */

/** @addtogroup FLASH_ITF_OB_Exported_Functions_Group2
  * @{

This subsection provides a set of functions allowing to to lock/unlock and configure the FLASH ITF peripheral option
bytes :

- Call the function HAL_FLASH_ITF_OB_Lock() to lock the access to the FLASH ITF OB control register.

- Call the function HAL_FLASH_ITF_OB_Unlock() to unlock the access to the FLASH ITF OB control register.

- Call the function HAL_FLASH_ITF_OB_IsLocked() to check the lock access registers state to the FLASH ITF OB control
  register.

- Call the function HAL_FLASH_ITF_OB_SetWRPArea() to set the FLASH ITF OB write protection area configuration.

- Call the function HAL_FLASH_ITF_OB_GetWRPArea() to get the FLASH ITF OB write protection area configuration.

- Call the function HAL_FLASH_ITF_OB_LockWRPAreaConfig() to lock the FLASH ITF OB write protection area configuration.

- Call the function HAL_FLASH_ITF_OB_UnlockWRPAreaConfig() to unlock the FLASH ITF OB write protection area
  configuration.

- Call the function HAL_FLASH_ITF_OB_IsLockedWRPAreaConfig() to Check if the FLASH ITF OB write protection area
  configuration is locked or unlocked.

- Call the function HAL_FLASH_ITF_OB_SetHDPExtPages() to set the HDP extension pages.

- Call the function HAL_FLASH_ITF_OB_GetHDPExtPages() to get the HDP extension pages.

- Call the function HAL_FLASH_ITF_OB_SetHDPExtState() to set the HDP extension state.

- Call the function HAL_FLASH_ITF_OB_GetHDPExtState() to get the HDP extension state.

- Call the function HAL_FLASH_ITF_OB_SetRDPLevel() to set the FLASH ITF OB readout protection level.

- Call the function HAL_FLASH_ITF_OB_GetRDPLevel() to get the FLASH ITF OB readout protection level.

- Call the function HAL_FLASH_ITF_OB_SetRDPOEMKey() to set the FLASH ITF OB readout protection OEM keys.

- Call the function HAL_FLASH_ITF_OB_SetBORLevel() to set the FLASH ITF OB BOR level.

- Call the function HAL_FLASH_ITF_OB_GetBORLevel() to get the FLASH ITF OB BOR level.

- Call the function HAL_FLASH_ITF_OB_SetEnterLowPWRModeRstGeneration() to set the FLASH ITF OB enter
  stop/standby/shutdown modes by reset generation configuration.

- Call the function HAL_FLASH_ITF_OB_GetEnterLowPWRModeRstGeneration() to get the FLASH ITF OB enter
  stop/standby/shutdown modes by reset generation configuration.

- Call the function HAL_FLASH_ITF_OB_SetSystemRstSRAMErase() to set the FLASH ITF OB system reset SRAM/SRAM2 erase
  configuration.

- Call the function HAL_FLASH_ITF_OB_GetSystemRstSRAMErase() to get the FLASH ITF OB system reset SRAM/SRAM2 erase
  configuration.

- Call the function HAL_FLASH_ITF_OB_SetxWDGMode() to set the FLASH ITF OB IWDG/WWDG mode.

- Call the function HAL_FLASH_ITF_OB_GetxWDGMode() to get the FLASH ITF OB IWDG/WWDG mode.

- Call the function HAL_FLASH_ITF_OB_FreezexWDGCounterLowPWRMode() to freeze the FLASH ITF OB IWDG stop/standby counter
  configuration.

- Call the function HAL_FLASH_ITF_OB_UnfreezexWDGCounterLowPWRMode() to unfreeze the FLASH ITF OB IWDG stop/standby
  counter configuration.

- Call the function HAL_FLASH_ITF_OB_IsFrozenxWDGCounterLowPWRMode() to check the FLASH ITF OB IWDG stop/standby counter
  configuration is frozen.

- Call the function HAL_FLASH_ITF_OB_SetBankSwap() to set the FLASH ITF OB bank swapping configuration.

- Call the function HAL_FLASH_ITF_OB_GetBankSwap() to get the FLASH ITF OB bank swapping configuration.

- Call the function HAL_FLASH_ITF_OB_SetBankTopology() to set the FLASH ITF OB single dual bank configuration.

- Call the function HAL_FLASH_ITF_OB_GetBankTopology() to get the FLASH ITF OB single dual bank configuration.

- Call the function HAL_FLASH_ITF_OB_EnableSRAMECC() to enable the FLASH ITF OB BKPRAM/SRAM2/SRAM3 ECC configuration.

- Call the function HAL_FLASH_ITF_OB_DisableSRAMECC() to disable the FLASH ITF OB BKPRAM/SRAM2/SRAM3 ECC configuration.

- Call the function HAL_FLASH_ITF_OB_IsEnabledSRAMECC() to check the FLASH ITF OB BKPRAM/SRAM2/SRAM3 ECC configuration
  is enabled.

- Call the function HAL_FLASH_ITF_OB_SetBoot0() to set the FLASH ITF OB boot0 configuration.

- Call the function HAL_FLASH_ITF_OB_GetBoot0() to get the FLASH ITF OB boot0 configuration.

- Call the function HAL_FLASH_ITF_OB_SetIOPull() to enable the FLASH ITF OB PA15 pullup configuration.

- Call the function HAL_FLASH_ITF_OB_GetIOPull() to disable the FLASH ITF OB PA15 pullup configuration.

- Call the function HAL_FLASH_ITF_OB_EnableVddxHighSpeedLowVoltage() to enable the FLASH ITF OB High speed Low VDDIO
  and VDDIO2 configuration.

- Call the function HAL_FLASH_ITF_OB_DisableVddxHighSpeedLowVoltage() to disable the FLASH ITF OB High speed Low VDDIO
  and VDDIO2 configuration.

- Call the function HAL_FLASH_ITF_OB_IsEnabledVddxHighSpeedLowVoltage() to check the FLASH ITF OB High speed Low VDDIO
  and VDDIO2 configuration is enabled.

- Call the function HAL_FLASH_ITF_OB_EnableTrustZone() to enable the FLASH ITF OB TrustZone configuration.

- Call the function HAL_FLASH_ITF_OB_DisableTrustZone() to disable the FLASH ITF OB TrustZone configuration.

- Call the function HAL_FLASH_ITF_OB_IsEnabledTrustZone() to check the FLASH ITF OB TrustZone configuration is enabled.

- Call the function HAL_FLASH_ITF_OB_SetSecureWMArea() to set the FLASH ITF OB secure watermark area configuration.

- Call the function HAL_FLASH_ITF_OB_GetSecureWMArea() to get the FLASH ITF OB secure watermark area configuration.

- Call the function HAL_FLASH_ITF_OB_SetConfigHDPArea() to set the FLASH ITF OB hide protection area configuration.

- Call the function HAL_FLASH_ITF_OB_GetConfigHDPArea() to get the FLASH ITF OB hide protection area configuration.

- Call the function HAL_FLASH_ITF_OB_EnableHDPArea() to enable the FLASH ITF OB hide protection area configuration.

- Call the function HAL_FLASH_ITF_OB_DisableHDPArea() to disable the FLASH ITF OB hide protection area configuration.

- Call the function HAL_FLASH_ITF_OB_IsEnabledHDPArea() to check if the FLASH ITF OB hide protection area configuration
  is enabled or disabled.

- Call the function HAL_FLASH_ITF_OB_SetNSecureBootAddr() to set the FLASH ITF OB non-secure boot address 0 and boot
  address 1 configuration.

- Call the function HAL_FLASH_ITF_OB_GetNSecureBootAddr() to get the FLASH ITF OB non-secure boot address 0 and boot
  address 1 configuration.

- Call the function HAL_FLASH_ITF_OB_SetSecureBootAddr() to set the FLASH ITF OB secure boot address 0 and boot
  address 1 configuration.

- Call the function HAL_FLASH_ITF_OB_GetSecureBootAddr() to get the FLASH ITF OB secure boot address 0  and boot
  address 1 configuration.

- Call the function HAL_FLASH_ITF_OB_LockBootConfig() to lock the FLASH ITF OB secure boot address configuration.

- Call the function HAL_FLASH_ITF_OB_UnlockBootConfig() to unlock the FLASH ITF OB secure boot address configuration.

- Call the function HAL_FLASH_ITF_OB_IsLockedBootConfig() to Check if the FLASH ITF OB secure boot address
  configuration is locked or unlocked.
  */

/**
  * @brief   Lock the FLASH ITF OB control register access.
  * @param   instance This parameter is one element of \ref hal_flash_t enumeration.
  * @warning When locking the flash OB, the flash will not be locked.
  * @retval  HAL_OK   FLASH ITF OB is successfully locked.
  */
hal_status_t HAL_FLASH_ITF_OB_Lock(hal_flash_t instance)
{
  ASSERT_DBG_PARAM(IS_FLASH_INSTANCE(instance));

  LL_FLASH_OB_Lock(FLASH_ITF_GET_INSTANCE(instance));

  return HAL_OK;
}

/**
  * @brief   Unlock the FLASH ITF OB control register access.
  * @param   instance This parameter is one element of \ref hal_flash_t enumeration.
  * @warning When unlocking the flash OB, the flash is unlocked as side effect.
  * @retval  HAL_OK   FLASH ITF OB is successfully unlocked.
  */
hal_status_t HAL_FLASH_ITF_OB_Unlock(hal_flash_t instance)
{
  ASSERT_DBG_PARAM(IS_FLASH_INSTANCE(instance));

  if (LL_FLASH_OB_IsLocked(FLASH_ITF_GET_INSTANCE(instance)) == 1U)
  {
    LL_FLASH_OB_SetUnlockKey(FLASH_ITF_GET_INSTANCE(instance), LL_FLASH_OB_OPTKEY1);
    LL_FLASH_OB_SetUnlockKey(FLASH_ITF_GET_INSTANCE(instance), LL_FLASH_OB_OPTKEY2);
  }

  return HAL_OK;
}

/**
  * @brief  Check if the FLASH ITF OB control register access is locked or unlocked.
  * @param  instance This parameter is one element of \ref hal_flash_t enumeration.
  * @retval hal_flash_itf_ob_lock_status_t FLASH ITF OB control register access lock status.
  */
hal_flash_itf_ob_lock_status_t HAL_FLASH_ITF_OB_IsLocked(hal_flash_t instance)
{
  ASSERT_DBG_PARAM(IS_FLASH_INSTANCE(instance));

  return (hal_flash_itf_ob_lock_status_t)LL_FLASH_OB_IsLocked(FLASH_ITF_GET_INSTANCE(instance));
}

/**
  * @brief  Enable the write protection feature on the selected pages of the given bank.
  * @param  instance   This parameter is one element of \ref hal_flash_t enumeration.
  * @param  bank       This parameter is one element of \ref hal_flash_bank_t enumeration.
  * @param  pages      This parameter can be any combinations of @ref HAL_FLASH_ITF_OB_Write_Protection_Pages values.
  * @note   To configure the write protected pages, the option lock bit OPTLOCK must be
  *         cleared with the call of the HAL_FLASH_ITF_OB_Unlock() function.
  * @retval HAL_OK     FLASH OB write protection area is successfully configured.
  * @retval HAL_ERROR  FLASH OB write error generated.
  */
hal_status_t HAL_FLASH_ITF_OB_EnablePageWRP(hal_flash_t instance, hal_flash_bank_t bank, uint32_t pages)
{
  ASSERT_DBG_PARAM(IS_FLASH_INSTANCE(instance));
  ASSERT_DBG_PARAM(IS_FLASH_BANK(bank));

  if (LL_FLASH_IsActiveFlag(FLASH_ITF_GET_INSTANCE(instance),
                            (uint32_t)bank, (LL_FLASH_FLAG_STATUS_ALL | LL_FLASH_FLAG_ERRORS_ALL)) != 0U)
  {
    return HAL_ERROR;
  }

  LL_FLASH_OB_EnablePageWRP(FLASH_ITF_GET_INSTANCE(instance), (uint32_t)bank, (uint32_t)pages);

  return HAL_OK;
}

/**
  * @brief  Disable the write protection feature on the selected pages of the given bank.
  * @param  instance   This parameter is one element of \ref hal_flash_t enumeration.
  * @param  bank       This parameter is one element of \ref hal_flash_bank_t enumeration.
  * @param  pages      This parameter can be any combinations @ref HAL_FLASH_ITF_OB_Write_Protection_Pages.
  * @note   To configure the write protected pages, the option lock bit OPTLOCK must be
  *         cleared with the call of the HAL_FLASH_ITF_OB_Unlock() function.
  * @retval HAL_OK     FLASH OB write protection area is successfully configured.
  * @retval HAL_ERROR  FLASH OB write error generated.
  */
hal_status_t HAL_FLASH_ITF_OB_DisablePageWRP(hal_flash_t instance, hal_flash_bank_t bank, uint32_t pages)
{
  ASSERT_DBG_PARAM(IS_FLASH_INSTANCE(instance));
  ASSERT_DBG_PARAM(IS_FLASH_BANK(bank));

  if (LL_FLASH_IsActiveFlag(FLASH_ITF_GET_INSTANCE(instance),
                            (uint32_t)bank, (LL_FLASH_FLAG_STATUS_ALL | LL_FLASH_FLAG_ERRORS_ALL)) != 0U)
  {
    return HAL_ERROR;
  }

  LL_FLASH_OB_DisablePageWRP(FLASH_ITF_GET_INSTANCE(instance), (uint32_t)bank, (uint32_t)pages);

  return HAL_OK;
}

/**
  * @brief  Get the state  of page write protection configuration for the selected pages of the given bank.
  * @param  instance This parameter is one element of \ref hal_flash_t enumeration.
  * @param  bank     This parameter is one element of \ref hal_flash_bank_t enumeration.
  * @param  pages    This parameter can be any combinations @ref HAL_FLASH_ITF_OB_Write_Protection_Pages.
  * @retval 1 if all selected pages are write protected, 0 otherwise.
  */
uint32_t HAL_FLASH_ITF_OB_IsEnabledPageWRP(hal_flash_t instance, hal_flash_bank_t bank, uint32_t pages)
{
  ASSERT_DBG_PARAM(IS_FLASH_INSTANCE(instance));
  ASSERT_DBG_PARAM(IS_FLASH_BANK(bank));

  return LL_FLASH_OB_IsEnabledPageWRP(FLASH_ITF_GET_INSTANCE(instance), (uint32_t)bank, (uint32_t)pages);
}

/**
  * @brief  Set the HDP area start page.
  * @param  instance   This parameter is one element of \ref hal_flash_t enumeration.
  * @param  bank       This parameter is one element of \ref hal_flash_bank_t enumeration.
  * @param  start_page This parameter can take any value between 0 and the maximum number of pages.
  * @note   To configure the HDP area start page, the option lock bit OPTLOCK must be
  *         cleared with the call of the HAL_FLASH_ITF_OB_Unlock() function.
  * @retval HAL_OK     FLASH OB HDP area start page is successfully configured.
  * @retval HAL_ERROR  FLASH OB write error generated.
  */
hal_status_t HAL_FLASH_ITF_OB_SetHDPArea(hal_flash_t instance,
                                         hal_flash_bank_t bank,
                                         uint32_t start_page,
                                         uint32_t page_nbr)
{
  ASSERT_DBG_PARAM(IS_FLASH_INSTANCE(instance));
  ASSERT_DBG_PARAM(IS_FLASH_BANK(bank));
  ASSERT_DBG_PARAM(start_page < FLASH_PAGE_NB);

  if (LL_FLASH_IsActiveFlag(FLASH_ITF_GET_INSTANCE(instance),
                            (uint32_t)bank, (LL_FLASH_FLAG_STATUS_ALL | LL_FLASH_FLAG_ERRORS_ALL)) != 0U)
  {
    return HAL_ERROR;
  }

  LL_FLASH_OB_ConfigHDPArea(FLASH_ITF_GET_INSTANCE(instance), (uint32_t)bank, start_page, start_page + page_nbr - 1U);

  return HAL_OK;
}

/**
  * @brief  Get the HDP area start page.
  * @param  bank     This parameter is one element of \ref hal_flash_bank_t enumeration.
  * @param  instance This parameter is one element of \ref hal_flash_t enumeration.
  * @retval Return value can be any value between 0 and the maximum number of pages per bank.
  */
void HAL_FLASH_ITF_OB_GetHDPArea(hal_flash_t instance,
                                 hal_flash_bank_t bank,
                                 uint32_t *p_start_page,
                                 uint32_t *p_page_nbr)
{
  ASSERT_DBG_PARAM(IS_FLASH_INSTANCE(instance));
  ASSERT_DBG_PARAM(IS_FLASH_BANK(bank));
  ASSERT_DBG_PARAM(p_start_page != NULL);
  ASSERT_DBG_PARAM(p_page_nbr != NULL);

  *p_start_page = LL_FLASH_OB_GetHDPAreaStartPage(FLASH_ITF_GET_INSTANCE(instance), (uint32_t)bank);
  *p_page_nbr   = (LL_FLASH_OB_GetHDPAreaEndPage(FLASH_ITF_GET_INSTANCE(instance), (uint32_t)bank) \
                   - *p_start_page + 1U);
}

/**
  * @brief  Lock the selected blocks of the OTP flash area.
  * @param instance This parameter is one element of \ref hal_flash_t enumeration.
  * @param  blocks     This parameter can be any combinations of @ref HAL_FLASH_ITF_OB_OTP_Lock_Blocks values.
  * @note   To configure the locked OTP blocks, the option lock bit OPTLOCK must be
  *         cleared with the call of the HAL_FLASH_ITF_OB_Unlock() function.
  * @retval HAL_OK     FLASH OB OTP blocks are successfully locked.
  * @retval HAL_ERROR  FLASH OB write error generated.
  */
hal_status_t HAL_FLASH_ITF_OB_LockOTPBlock(hal_flash_t instance, uint32_t blocks)
{
  ASSERT_DBG_PARAM(IS_FLASH_INSTANCE(instance));
  ASSERT_DBG_PARAM(blocks < HAL_FLASH_ITF_OB_OTP_LOCK_BLOCK_ALL);

  if (FLASH_ITF_CheckForEndOfOperation(instance) != HAL_OK)
  {
    return HAL_ERROR;
  }

  LL_FLASH_OB_LockOTPBlock(FLASH_ITF_GET_INSTANCE(instance), blocks);

  return HAL_OK;
}

/**
  * @brief  Check if the selected OTP blocks are locked.
  * @param  instance This parameter is one element of \ref hal_flash_t enumeration.
  * @param  blocks   This parameter can be any combinations of @ref HAL_FLASH_ITF_OB_OTP_Lock_Blocks values.
  * @retval 1 if all selected blocks are locked, 0 otherwise.
  */
uint32_t HAL_FLASH_ITF_OB_IsLockedOTPBlock(hal_flash_t instance, uint32_t blocks)
{
  ASSERT_DBG_PARAM(IS_FLASH_INSTANCE(instance));
  ASSERT_DBG_PARAM(blocks < HAL_FLASH_ITF_OB_OTP_LOCK_BLOCK_ALL);

  return LL_FLASH_OB_IsLockedOTPBlock(FLASH_ITF_GET_INSTANCE(instance), blocks);
}

/**
  * @brief  Set the Non-Volatile State.
  * @param instance This parameter is one element of \ref hal_flash_t enumeration.
  * @param  nv_state   This parameter is one element of \ref hal_flash_itf_ob_nv_state_t enumeration.
  * @note   To configure the Non-Volatile state, the option lock bit OPTLOCK must be
  *         cleared with the call of the HAL_FLASH_ITF_OB_Unlock() function.
  * @retval HAL_OK     FLASH OB Non-Volatile state has been successfully set.
  * @retval HAL_ERROR  FLASH OB write error generated.
  */
hal_status_t HAL_FLASH_ITF_OB_SetNVState(hal_flash_t instance, hal_flash_itf_ob_nv_state_t nv_state)
{
  ASSERT_DBG_PARAM(IS_FLASH_INSTANCE(instance));
  ASSERT_DBG_PARAM(IS_FLASH_ITF_OB_NVSTATE(nv_state));

  if (FLASH_ITF_CheckForEndOfOperation(instance) != HAL_OK)
  {
    return HAL_ERROR;
  }

  LL_FLASH_OB_SetNVState(FLASH_ITF_GET_INSTANCE(instance), (uint32_t)nv_state);

  return HAL_OK;
}

/**
  * @brief  Get the Non-Volatile state configuration.
  * @param  instance This parameter is one element of \ref hal_flash_t enumeration.
  * @retval Return value can be one element of \ref hal_flash_itf_ob_nv_state_t enumeration..
  */
hal_flash_itf_ob_nv_state_t HAL_FLASH_ITF_OB_GetNVState(hal_flash_t instance)
{
  ASSERT_DBG_PARAM(IS_FLASH_INSTANCE(instance));

  return ((hal_flash_itf_ob_nv_state_t)LL_FLASH_OB_GetNVState(FLASH_ITF_GET_INSTANCE(instance)));
}

/**
  * @brief  Lock the boot configuration.
  * @param  instance This parameter is one element of \ref hal_flash_t enumeration.
  * @retval HAL_OK     FLASH OB boot configuration has been successfully locked.
  * @retval HAL_ERROR  FLASH OB write error generated.
  */
hal_status_t HAL_FLASH_ITF_OB_LockBootConfig(hal_flash_t instance)
{
  ASSERT_DBG_PARAM(IS_FLASH_INSTANCE(instance));

  if (FLASH_ITF_CheckForEndOfOperation(instance) != HAL_OK)
  {
    return HAL_ERROR;
  }

  LL_FLASH_OB_LockBootConfig(FLASH_ITF_GET_INSTANCE(instance));

  return HAL_OK;
}

/**
  * @brief  Unlock the boot configuration.
  * @param  instance This parameter is one element of \ref hal_flash_t enumeration.
  * @retval HAL_OK     FLASH OB boot configuration has been successfully unlocked.
  * @retval HAL_ERROR  FLASH OB write error generated.
  */
hal_status_t HAL_FLASH_ITF_OB_UnlockBootConfig(hal_flash_t instance)
{
  ASSERT_DBG_PARAM(IS_FLASH_INSTANCE(instance));

  if (FLASH_ITF_CheckForEndOfOperation(instance) != HAL_OK)
  {
    return HAL_ERROR;
  }

  LL_FLASH_OB_UnlockBootConfig(FLASH_ITF_GET_INSTANCE(instance));

  return HAL_OK;
}

/**
  * @brief  Get the boot configuration lock state.
  * @param  instance This parameter is one element of \ref hal_flash_t enumeration.
  * @retval Return value can be one element of \ref hal_flash_itf_ob_boot_lock_status_t enumeration..
  */
hal_flash_itf_ob_boot_lock_status_t HAL_FLASH_ITF_OB_IsLockedBootConfig(hal_flash_t instance)
{
  ASSERT_DBG_PARAM(IS_FLASH_INSTANCE(instance));

  return ((hal_flash_itf_ob_boot_lock_status_t)LL_FLASH_OB_IsLockedBootConfig(FLASH_ITF_GET_INSTANCE(instance)));
}

/**
  * @brief  Set the debug authentication method configuration.
  * @param  instance This parameter is one element of \ref hal_flash_t enumeration.
  * @param  dbg_auth This parameter is one element of \ref hal_flash_itf_ob_dbg_auth_t enumeration.
  * @retval HAL_OK     FLASH OB debug authenticayion method has been successfully unlocked.
  * @retval HAL_ERROR  FLASH OB write error generated.
  */
hal_status_t HAL_FLASH_ITF_OB_SetDebugAuthenticationMethod(hal_flash_t instance, hal_flash_itf_ob_dbg_auth_t dbg_auth)
{
  ASSERT_DBG_PARAM(IS_FLASH_INSTANCE(instance));

  if (FLASH_ITF_CheckForEndOfOperation(instance) != HAL_OK)
  {
    return HAL_ERROR;
  }

  LL_FLASH_OB_SetDebugAuthenticationMethod(FLASH_ITF_GET_INSTANCE(instance), (uint32_t)dbg_auth);

  return HAL_OK;
}

/**
  * @brief  Get the debug authentication method configuration state.
  * @param  instance This parameter is one element of \ref hal_flash_t enumeration.
  * @retval Return value can be one element of \ref hal_flash_itf_ob_dbg_auth_t enumeration.
  */
hal_flash_itf_ob_dbg_auth_t HAL_FLASH_ITF_OB_GetDebugAuthenticationMethod(hal_flash_t instance)
{
  ASSERT_DBG_PARAM(IS_FLASH_INSTANCE(instance));

  return ((hal_flash_itf_ob_dbg_auth_t)LL_FLASH_OB_GetDebugAuthenticationMethod(FLASH_ITF_GET_INSTANCE(instance)));
}

/**
  * @brief  Set the OEM provisioning configuration.
  * @param  instance This parameter is one element of \ref hal_flash_t enumeration.
  * @param  oem_provd This parameter is one element of \ref hal_flash_itf_ob_oem_provd_t enumeration.
  * @retval HAL_OK     FLASH OB OEM provd has been successfully unlocked.
  * @retval HAL_ERROR  FLASH OB write error generated.
  */
hal_status_t HAL_FLASH_ITF_OB_SetOEMProvisioning(hal_flash_t instance, hal_flash_itf_ob_oem_provd_t oem_provd)
{
  ASSERT_DBG_PARAM(IS_FLASH_INSTANCE(instance));

  if (FLASH_ITF_CheckForEndOfOperation(instance) != HAL_OK)
  {
    return HAL_ERROR;
  }

  LL_FLASH_OB_SetOEMProvisioningState(FLASH_ITF_GET_INSTANCE(instance), (uint32_t)oem_provd);

  return HAL_OK;
}

/**
  * @brief  Get the OEM provisioning configuration state.
  * @param  instance This parameter is one element of \ref hal_flash_t enumeration.
  * @retval Return value can be one element of \ref hal_flash_itf_ob_oem_provd_t enumeration..
  */
hal_flash_itf_ob_oem_provd_t HAL_FLASH_ITF_OB_GetOEMProvisioning(hal_flash_t instance)
{
  ASSERT_DBG_PARAM(IS_FLASH_INSTANCE(instance));

  return ((hal_flash_itf_ob_oem_provd_t)LL_FLASH_OB_GetOEMProvisioningState(FLASH_ITF_GET_INSTANCE(instance)));
}

/**
  * @brief  Set the FLASH ITF OB BOR level.
  * @param  instance  This parameter is one element of \ref hal_flash_t enumeration.
  * @param  bor_level This parameter is one element of \ref hal_flash_itf_ob_bor_level_t enumeration.
  * @retval HAL_OK    FLASH ITF OB BOR level is successfully configured.
  * @retval HAL_ERROR FLASH ITF OB write error generated.
  */
hal_status_t HAL_FLASH_ITF_OB_SetBORLevel(hal_flash_t instance, hal_flash_itf_ob_bor_level_t bor_level)
{
  ASSERT_DBG_PARAM(IS_FLASH_INSTANCE(instance));
  ASSERT_DBG_PARAM(IS_FLASH_ITF_OB_BOR_LEVEL(bor_level));

  if (FLASH_ITF_CheckForEndOfOperation(instance) != HAL_OK)
  {
    return HAL_ERROR;
  }

  LL_FLASH_OB_SetBORLevel(FLASH_ITF_GET_INSTANCE(instance), (uint32_t)bor_level);

  return HAL_OK;
}

/**
  * @brief  Get the FLASH ITF OB BOR level.
  * @param  instance This parameter is one element of \ref hal_flash_t enumeration.
  * @retval hal_flash_itf_ob_bor_level_t FLASH ITF OB BOR level.
  */
hal_flash_itf_ob_bor_level_t HAL_FLASH_ITF_OB_GetBORLevel(hal_flash_t instance)
{
  ASSERT_DBG_PARAM(IS_FLASH_INSTANCE(instance));

  return ((hal_flash_itf_ob_bor_level_t)((uint32_t)LL_FLASH_OB_GetBORLevel(FLASH_ITF_GET_INSTANCE(instance))));
}

/**
  * @brief  Set the FLASH ITF OB low power mode reset generation configuration.
  * @param  instance This parameter is one element of \ref hal_flash_t enumeration.
  * @param  low_pwr_mode low power mode param selection.
  * @param  rst_gen      Element from the \ref hal_flash_itf_ob_enter_stop_rst_generation_t enumeration.
  * @retval HAL_OK       FLASH ITF OB low power mode reset generation is successfully configured.
  * @retval HAL_ERROR    FLASH ITF OB write error generated.
  */
hal_status_t HAL_FLASH_ITF_OB_SetEnterLowPWRModeRstGeneration(hal_flash_t instance, uint32_t low_pwr_mode,
                                                              hal_flash_itf_ob_rst_generation_status_t rst_gen)
{
  ASSERT_DBG_PARAM(IS_FLASH_INSTANCE(instance));
  ASSERT_DBG_PARAM((low_pwr_mode & FLASH_ITF_OB_LOW_PWR_MSK) == low_pwr_mode);
  ASSERT_DBG_PARAM(IS_FLASH_ITF_OB_RST_GENERATION_STATUS(rst_gen));

  if (FLASH_ITF_CheckForEndOfOperation(instance) != HAL_OK)
  {
    return HAL_ERROR;
  }

  if ((low_pwr_mode & HAL_FLASH_ITF_OB_STOP_MODE) == HAL_FLASH_ITF_OB_STOP_MODE)
  {
    LL_FLASH_OB_SetNRSTStopMode(FLASH_ITF_GET_INSTANCE(instance), (uint32_t)rst_gen * LL_FLASH_OB_NO_RST_STOP_MODE);
  }

  if ((low_pwr_mode & HAL_FLASH_ITF_OB_STANDBY_MODE) == HAL_FLASH_ITF_OB_STANDBY_MODE)
  {
    LL_FLASH_OB_SetNRSTStandbyMode(FLASH_ITF_GET_INSTANCE(instance), (uint32_t)rst_gen * LL_FLASH_OB_NO_RST_STDBY_MODE);
  }

  return HAL_OK;
}

/**
  * @brief  Get the FLASH ITF OB low power reset generation configuration.
  * @param  instance This parameter is one element of \ref hal_flash_t enumeration.
  * @param  low_pwr_mode low power mode selection.
  * @retval hal_flash_itf_ob_rst_generation_status_t FLASH ITF OB low power mode reset generation configuration.
  */
hal_flash_itf_ob_rst_generation_status_t HAL_FLASH_ITF_OB_GetEnterLowPWRModeRstGeneration(hal_flash_t instance,
    uint32_t low_pwr_mode)
{
  ASSERT_DBG_PARAM(IS_FLASH_INSTANCE(instance));
  ASSERT_DBG_PARAM(IS_FLASH_ITF_OB_LOW_PWR_MODE(low_pwr_mode));

  if (low_pwr_mode == HAL_FLASH_ITF_OB_STOP_MODE)
  {
    return (hal_flash_itf_ob_rst_generation_status_t)
           ((uint32_t)(LL_FLASH_OB_GetNRSTStopMode(FLASH_ITF_GET_INSTANCE(instance)) >> FLASH_OBW1SR_NRST_STOP_Pos));
  }
  else
  {
    return (hal_flash_itf_ob_rst_generation_status_t)
           ((uint32_t)(LL_FLASH_OB_GetNRSTStandbyMode(FLASH_ITF_GET_INSTANCE(instance)) >> FLASH_OBW1SR_NRST_STBY_Pos));
  }
}

/**
  * @brief  Set the FLASH ITF OB WDG mode configuration.
  * @param  instance  This parameter is one element of \ref hal_flash_t enumeration.
  * @param  mode      Element from the \ref hal_flash_itf_ob_iwdg_mode_t enumeration.
  * @retval HAL_OK    FLASH ITF OB WDG mode is successfully configured.
  * @retval HAL_ERROR FLASH ITF OB write error generated.
  */
hal_status_t HAL_FLASH_ITF_OB_SetIWDGMode(hal_flash_t instance, hal_flash_itf_ob_wdg_mode_t mode)
{
  ASSERT_DBG_PARAM(IS_FLASH_INSTANCE(instance));
  ASSERT_DBG_PARAM(IS_FLASH_ITF_OB_WDG_HW_SW_MODE(mode));

  if (FLASH_ITF_CheckForEndOfOperation(instance) != HAL_OK)
  {
    return HAL_ERROR;
  }

  LL_FLASH_OB_SetIWDGSelection(FLASH_ITF_GET_INSTANCE(instance), (uint32_t)mode * LL_FLASH_OB_IWDG_SW);

  return HAL_OK;
}

/**
  * @brief  Get the FLASH ITF OB xWDG mode configuration.
  * @param  instance This parameter is one element of \ref hal_flash_t enumeration.
  * @retval hal_flash_itf_ob_wdg_mode_t FLASH ITF OB xWDG mode configuration.
  */
hal_flash_itf_ob_wdg_mode_t HAL_FLASH_ITF_OB_GetIWDGMode(hal_flash_t instance)
{
  ASSERT_DBG_PARAM(IS_FLASH_INSTANCE(instance));

  return (hal_flash_itf_ob_wdg_mode_t)
         ((uint32_t)(LL_FLASH_OB_GetIWDGSelection(FLASH_ITF_GET_INSTANCE(instance)) >> FLASH_OBW1SR_IWDG_HW_Pos));
}

/**
  * @brief  Freeze the FLASH ITF OB IWDG low power counter configuration.
  * @param  instance     This parameter is one element of \ref hal_flash_t enumeration.
  * @param  low_pwr_mode low power mode selection.
  * @retval HAL_OK       FLASH ITF OB IWDG low power counter is frozen.
  * @retval HAL_ERROR    FLASH ITF OB write error generated.
  */
hal_status_t HAL_FLASH_ITF_OB_FreezeIWDGCounterLowPWRMode(hal_flash_t instance, uint32_t low_pwr_mode)
{
  ASSERT_DBG_PARAM(IS_FLASH_INSTANCE(instance));
  ASSERT_DBG_PARAM((low_pwr_mode & FLASH_ITF_OB_LOW_PWR_MSK) == low_pwr_mode);

  if (FLASH_ITF_CheckForEndOfOperation(instance) != HAL_OK)
  {
    return HAL_ERROR;
  }

  if ((low_pwr_mode & HAL_FLASH_ITF_OB_STOP_MODE) == HAL_FLASH_ITF_OB_STOP_MODE)
  {
    LL_FLASH_OB_FreezeIWDGStopMode(FLASH_ITF_GET_INSTANCE(instance));
  }

  if ((low_pwr_mode & HAL_FLASH_ITF_OB_STANDBY_MODE) == HAL_FLASH_ITF_OB_STANDBY_MODE)
  {
    LL_FLASH_OB_FreezeIWDGStandbyMode(FLASH_ITF_GET_INSTANCE(instance));
  }

  return HAL_OK;
}

/**
  * @brief  Unfreeze the FLASH ITF OB IWDG low power counter configuration.
  * @param  instance     This parameter is one element of \ref hal_flash_t enumeration.
  * @param  low_pwr_mode low power mode selection.
  * @retval HAL_OK       FLASH ITF OB IWDG low power mode counter is not frozen.
  * @retval HAL_ERROR    FLASH ITF OB write error generated.
  */
hal_status_t HAL_FLASH_ITF_OB_UnfreezeIWDGCounterLowPWRMode(hal_flash_t instance, uint32_t low_pwr_mode)
{
  ASSERT_DBG_PARAM(IS_FLASH_INSTANCE(instance));
  ASSERT_DBG_PARAM((low_pwr_mode & FLASH_ITF_OB_LOW_PWR_MSK) == low_pwr_mode);

  if (FLASH_ITF_CheckForEndOfOperation(instance) != HAL_OK)
  {
    return HAL_ERROR;
  }

  if ((low_pwr_mode & HAL_FLASH_ITF_OB_STOP_MODE) == HAL_FLASH_ITF_OB_STOP_MODE)
  {
    LL_FLASH_OB_UnfreezeIWDGStopMode(FLASH_ITF_GET_INSTANCE(instance));
  }

  if ((low_pwr_mode & HAL_FLASH_ITF_OB_STANDBY_MODE) == HAL_FLASH_ITF_OB_STANDBY_MODE)
  {
    LL_FLASH_OB_UnfreezeIWDGStandbyMode(FLASH_ITF_GET_INSTANCE(instance));
  }

  return HAL_OK;
}

/**
  * @brief  Check the FLASH ITF OB IWDG low power counter configuration is frozen.
  * @param  instance     This parameter is one element of \ref hal_flash_t enumeration.
  * @param  low_pwr_mode low power mode selection.
  * @retval hal_flash_itf_ob_wdg_freeze_status_t FLASH ITF OB IWDG low power counter configuration status.
  */
hal_flash_itf_ob_wdg_freeze_status_t HAL_FLASH_ITF_OB_IsFrozenIWDGCounterLowPWRMode(hal_flash_t instance,
    uint32_t low_pwr_mode)
{
  ASSERT_DBG_PARAM(IS_FLASH_INSTANCE(instance));
  ASSERT_DBG_PARAM(IS_FLASH_ITF_OB_LOW_PWR_MODE(low_pwr_mode));

  if (low_pwr_mode == HAL_FLASH_ITF_OB_STOP_MODE)
  {
    return (hal_flash_itf_ob_wdg_freeze_status_t)LL_FLASH_OB_IsFrozenIWDGStopMode(FLASH_ITF_GET_INSTANCE(instance));
  }
  else
  {
    return (hal_flash_itf_ob_wdg_freeze_status_t)LL_FLASH_OB_IsFrozenIWDGStandbyMode(FLASH_ITF_GET_INSTANCE(instance));
  }
}

/**
  * @brief  Set the FLASH ITF OB bank swapping configuration.
  * @param  instance  This parameter is one element of \ref hal_flash_t enumeration.
  * @param  bank_swap This parameter is one element of \ref hal_flash_itf_ob_bank_swap_t enumeration.
  * @retval HAL_OK    FLASH ITF OB bank swapping is successfully configured.
  * @retval HAL_ERROR FLASH ITF OB write error generated.
  */
hal_status_t HAL_FLASH_ITF_OB_SetBankSwap(hal_flash_t instance, hal_flash_itf_ob_bank_swap_t bank_swap)
{
  ASSERT_DBG_PARAM(IS_FLASH_INSTANCE(instance));
  ASSERT_DBG_PARAM(IS_FLASH_ITF_OB_SWAP_BANK(bank_swap));

  if (FLASH_ITF_CheckForEndOfOperation(instance) != HAL_OK)
  {
    return HAL_ERROR;
  }

  LL_FLASH_OB_SetSwapBank(FLASH_ITF_GET_INSTANCE(instance), (uint32_t)bank_swap);

  return HAL_OK;
}

/**
  * @brief  Get the FLASH ITF OB bank swapping configuration.
  * @param  instance This parameter is one element of \ref hal_flash_t enumeration.
  * @retval hal_flash_itf_ob_bank_swap_t FLASH ITF OB bank swapping configuration.
  */
hal_flash_itf_ob_bank_swap_t HAL_FLASH_ITF_OB_GetBankSwap(hal_flash_t instance)
{
  ASSERT_DBG_PARAM(IS_FLASH_INSTANCE(instance));

  return ((hal_flash_itf_ob_bank_swap_t)LL_FLASH_OB_GetSwapBank(FLASH_ITF_GET_INSTANCE(instance)));
}

/**
  * @brief  Enable the FLASH ITF OB BKPRAM ECC configuration.
  * @param  instance  This parameter is one element of \ref hal_flash_t enumeration.
  * @param  sram      SRAM to be enabled.
  * @retval HAL_OK    FLASH ITF OB BKPRAM ECC is successfully enabled.
  * @retval HAL_ERROR FLASH ITF OB write error generated.
  */
hal_status_t HAL_FLASH_ITF_OB_EnableSRAMECC(hal_flash_t instance, uint32_t sram)
{
  ASSERT_DBG_PARAM(IS_FLASH_INSTANCE(instance));
  ASSERT_DBG_PARAM((sram & FLASH_ITF_OB_SRAM_ECC_MSK) == sram);

  if (FLASH_ITF_CheckForEndOfOperation(instance) != HAL_OK)
  {
    return HAL_ERROR;
  }

  if ((sram & HAL_FLASH_ITF_OB_SRAM) == HAL_FLASH_ITF_OB_SRAM)
  {
    LL_FLASH_OB_EnableEccOnSram(FLASH_ITF_GET_INSTANCE(instance));
  }

  LL_FLASH_OB_StartModification(FLASH_ITF_GET_INSTANCE(instance));

  return HAL_OK;
}

/**
  * @brief  Disable the FLASH ITF OB BKPRAM ECC configuration.
  * @param  instance  This parameter is one element of \ref hal_flash_t enumeration.
  * @param  sram      SRAM to be disabled.
  * @retval HAL_OK    FLASH ITF OB memories ECC is successfully configured.
  * @retval HAL_ERROR FLASH ITF OB write error generated.
  */
hal_status_t HAL_FLASH_ITF_OB_DisableSRAMECC(hal_flash_t instance, uint32_t sram)
{
  ASSERT_DBG_PARAM(IS_FLASH_INSTANCE(instance));
  ASSERT_DBG_PARAM((sram & FLASH_ITF_OB_SRAM_ECC_MSK) == sram);

  if (FLASH_ITF_CheckForEndOfOperation(instance) != HAL_OK)
  {
    return HAL_ERROR;
  }

  if ((sram & HAL_FLASH_ITF_OB_SRAM) == HAL_FLASH_ITF_OB_SRAM)
  {
    LL_FLASH_OB_DisableEccOnSram(FLASH_ITF_GET_INSTANCE(instance));
  }

  LL_FLASH_OB_StartModification(FLASH_ITF_GET_INSTANCE(instance));

  return HAL_OK;
}

/**
  * @brief  Check the FLASH ITF OB BKPRAM ECC configuration is enabled or disabled.
  * @param  instance This parameter is one element of \ref hal_flash_t enumeration.
  * @param  sram     SRAM to be checked.
  * @retval hal_flash_itf_ob_sram_ecc_status_t FLASH ITF OB BKPRAM ECC configuration status.
  */
hal_flash_itf_ob_sram_ecc_status_t HAL_FLASH_ITF_OB_IsEnabledSRAMECC(hal_flash_t instance, uint32_t sram)
{
  ASSERT_DBG_PARAM(IS_FLASH_INSTANCE(instance));
  ASSERT_DBG_PARAM(IS_FLASH_ITF_OB_SRAM_ECC(sram));

  return (hal_flash_itf_ob_sram_ecc_status_t)LL_FLASH_OB_IsEnabledEccOnSram(FLASH_ITF_GET_INSTANCE(instance));
}

/**
  * @brief  Enable the FLASH ITF OB high speed low VDD io configuration.
  * @param  instance  This parameter is one element of \ref hal_flash_t enumeration.
  * @param  vdd       Vdd high speed low voltage selection.
  * @retval HAL_OK    FLASH ITF OB high speed low VDD io is successfully enabled.
  * @retval HAL_ERROR FLASH ITF OB write error generated.
  */
hal_status_t HAL_FLASH_ITF_OB_EnableVddxHighSpeedLowVoltage(hal_flash_t instance, uint32_t vdd)
{
  ASSERT_DBG_PARAM(IS_FLASH_INSTANCE(instance));
  ASSERT_DBG_PARAM((vdd & FLASH_ITF_OB_VDDIO_MSK) == vdd);

  if (FLASH_ITF_CheckForEndOfOperation(instance) != HAL_OK)
  {
    return HAL_ERROR;
  }

  if ((vdd & HAL_FLASH_ITF_OB_VDDIO) == HAL_FLASH_ITF_OB_VDDIO)
  {
    LL_FLASH_OB_EnableHighSpeedLowVddIO(FLASH_ITF_GET_INSTANCE(instance));
  }

  LL_FLASH_OB_StartModification(FLASH_ITF_GET_INSTANCE(instance));

  return HAL_OK;
}

/**
  * @brief  Disable the FLASH ITF OB high speed low VDD io configuration.
  * @param  instance  This parameter is one element of \ref hal_flash_t enumeration.
  * @param  vdd       Vdd high speed low voltage selection.
  * @retval HAL_OK    FLASH ITF OB high speed low VDD io is successfully disabled.
  * @retval HAL_ERROR FLASH ITF OB write error generated.
  */
hal_status_t HAL_FLASH_ITF_OB_DisableVddxHighSpeedLowVoltage(hal_flash_t instance, uint32_t vdd)
{
  ASSERT_DBG_PARAM(IS_FLASH_INSTANCE(instance));
  ASSERT_DBG_PARAM((vdd & FLASH_ITF_OB_VDDIO_MSK) == vdd);

  if (FLASH_ITF_CheckForEndOfOperation(instance) != HAL_OK)
  {
    return HAL_ERROR;
  }

  if ((vdd & HAL_FLASH_ITF_OB_VDDIO) == HAL_FLASH_ITF_OB_VDDIO)
  {
    LL_FLASH_OB_DisableHighSpeedLowVddIO(FLASH_ITF_GET_INSTANCE(instance));
  }

  LL_FLASH_OB_StartModification(FLASH_ITF_GET_INSTANCE(instance));

  return HAL_OK;
}

/**
  * @brief  Check the FLASH ITF OB high speed low VDD io configuration is enabled or disabled.
  * @param  instance This parameter is one element of \ref hal_flash_t enumeration.
  * @param  vdd      Vdd high speed low voltage selection.
  * @retval hal_flash_itf_ob_vddio_hslv_status_t FLASH ITF OB high speed low VDD io configuration status.
  */
hal_flash_itf_ob_vddx_hslv_status_t HAL_FLASH_ITF_OB_IsEnabledVddxHighSpeedLowVoltage(hal_flash_t instance,
    uint32_t vdd)
{
  ASSERT_DBG_PARAM(IS_FLASH_INSTANCE(instance));
  ASSERT_DBG_PARAM(IS_FLASH_ITF_OB_VDD(vdd));

  return (hal_flash_itf_ob_vddx_hslv_status_t)LL_FLASH_OB_IsEnabledHighSpeedLowVddIO(FLASH_ITF_GET_INSTANCE(instance));
}

/**
  * @brief  Program the option byte key.
  * @param  instance  This parameter is one element of \ref hal_flash_t enumeration.
  * @param  hdp_level This parameter is one element of \ref hal_flash_itf_ob_hpdl_t enumeration.
  * @param  index     to do.
  * @param  key_value to do.
  * @retval HAL_ERROR Returned an error occurred.
  * @retval HAL_OK    Returned when the programming option byte key complete successfully.
  */
hal_status_t HAL_FLASH_ITF_OB_ProgramKey(hal_flash_t instance,
                                         hal_flash_itf_obk_hpdl_t hdp_level,
                                         uint32_t index,
                                         const hal_flash_itf_ob_obk_t *key)
{
  uint32_t val0;
  uint32_t val1;
  uint32_t val2;
  uint32_t val3;

  ASSERT_DBG_PARAM(IS_FLASH_INSTANCE(instance));
  ASSERT_DBG_PARAM(IS_FLASH_ITF_OBK_HDPL(hdp_level));

  if (FLASH_ITF_CheckForEndOfOperation(instance) != HAL_OK)
  {
    return HAL_ERROR;
  }

  LL_FLASH_SetOBKData0(FLASH_ITF_GET_INSTANCE(instance), key->key_w0);
  LL_FLASH_SetOBKData1(FLASH_ITF_GET_INSTANCE(instance), key->key_w1);
  LL_FLASH_SetOBKData2(FLASH_ITF_GET_INSTANCE(instance), key->key_w2);
  LL_FLASH_SetOBKData3(FLASH_ITF_GET_INSTANCE(instance), key->key_w3);

  LL_FLASH_SetOBKIndex(FLASH_ITF_GET_INSTANCE(instance), index);
  LL_FLASH_SetOBKeyNextHDPLevel(FLASH_ITF_GET_INSTANCE(instance), (uint32_t)hdp_level);

  LL_FLASH_EnableOBKeyProgramming(FLASH_ITF_GET_INSTANCE(instance));
  LL_FLASH_StartOBKeyOperation(FLASH_ITF_GET_INSTANCE(instance));

  while (LL_FLASH_OB_IsActiveFlag_KEYSTART(FLASH_ITF_GET_INSTANCE(instance)) != 0U)
  {
  }

  LL_FLASH_DisableOBKeyProgramming(FLASH_ITF_GET_INSTANCE(instance));
  LL_FLASH_StartOBKeyOperation(FLASH_ITF_GET_INSTANCE(instance));

  while (LL_FLASH_OB_IsActiveFlag_KEYSTART(FLASH_ITF_GET_INSTANCE(instance)) != 0U)
  {
  }

  val0 = LL_FLASH_GetOBKData0(FLASH_ITF_GET_INSTANCE(instance));
  val1 = LL_FLASH_GetOBKData1(FLASH_ITF_GET_INSTANCE(instance));
  val2 = LL_FLASH_GetOBKData2(FLASH_ITF_GET_INSTANCE(instance));
  val3 = LL_FLASH_GetOBKData3(FLASH_ITF_GET_INSTANCE(instance));

  if ((val0 != key->key_w0) || (val1 != key->key_w1) || (val2 != key->key_w2) || (val3 != key->key_w3))
  {
    return HAL_ERROR;
  }

  return HAL_OK;
}

/**
  * @brief  Erase the option byte key.
  * @param  instance  This parameter is one element of \ref hal_flash_t enumeration.
  * @param  hdp_level This parameter is one element of \ref hal_flash_itf_ob_hpdl_t enumeration.
  * @param  index     to do.
  * @retval HAL_ERROR Returned an error occurred.
  * @retval HAL_OK    Returned when the erase option byte key complete successfully.
  */
hal_status_t HAL_FLASH_ITF_OB_EraseKey(hal_flash_t instance, hal_flash_itf_obk_hpdl_t hdp_level, uint32_t index)
{
  ASSERT_DBG_PARAM(IS_FLASH_INSTANCE(instance));
  ASSERT_DBG_PARAM(IS_FLASH_ITF_OBK_HDPL(hdp_level));

  if (FLASH_ITF_CheckForEndOfOperation(instance) != HAL_OK)
  {
    return HAL_ERROR;
  }

  LL_FLASH_SetOBKEraseKeyIndex(FLASH_ITF_GET_INSTANCE(instance), index);
  LL_FLASH_SetOBKeyNextHDPLevel(FLASH_ITF_GET_INSTANCE(instance), (uint32_t)hdp_level);

  LL_FLASH_EnableOBKeyErase(FLASH_ITF_GET_INSTANCE(instance));
  LL_FLASH_StartOBKeyOperation(FLASH_ITF_GET_INSTANCE(instance));

  while (LL_FLASH_OB_IsActiveFlag_KEYSTART(FLASH_ITF_GET_INSTANCE(instance)) != 0U)
  {
  }

  LL_FLASH_DisableOBKeyErase(FLASH_ITF_GET_INSTANCE(instance));

  return HAL_OK;
}

/**
  * @brief  Get the option byte key.
  * @param  instance  This parameter is one element of \ref hal_flash_t enumeration.
  * @param  hdp_level This parameter is one element of \ref hal_flash_itf_ob_hpdl_t enumeration.
  * @param  index     to do.
  * @param  key_value to do.
  * @retval HAL_ERROR Returned an error occurred.
  * @retval HAL_OK    Returned when the retrieve of the option byte key complete successfully.
  */
hal_status_t HAL_FLASH_ITF_OB_GetKey(hal_flash_t instance,
                                     hal_flash_itf_obk_hpdl_t hdp_level, uint32_t index, hal_flash_itf_ob_obk_t *key)
{
  ASSERT_DBG_PARAM(IS_FLASH_INSTANCE(instance));
  ASSERT_DBG_PARAM(IS_FLASH_ITF_OBK_HDPL(hdp_level));

  if (FLASH_ITF_CheckForEndOfOperation(instance) != HAL_OK)
  {
    return HAL_ERROR;
  }

  LL_FLASH_DisableOBKeyErase(FLASH_ITF_GET_INSTANCE(instance));
  LL_FLASH_DisableOBKeyProgramming(FLASH_ITF_GET_INSTANCE(instance));

  LL_FLASH_SetOBKIndex(FLASH_ITF_GET_INSTANCE(instance), index);
  LL_FLASH_SetOBKeyNextHDPLevel(FLASH_ITF_GET_INSTANCE(instance), (uint32_t)hdp_level);

  LL_FLASH_StartOBKeyOperation(FLASH_ITF_GET_INSTANCE(instance));

  while (LL_FLASH_OB_IsActiveFlag_KEYSTART(FLASH_ITF_GET_INSTANCE(instance)) != 0U)
  {
  }

  key->key_w0 = LL_FLASH_GetOBKData0(FLASH_ITF_GET_INSTANCE(instance));
  key->key_w1 = LL_FLASH_GetOBKData1(FLASH_ITF_GET_INSTANCE(instance));
  key->key_w2 = LL_FLASH_GetOBKData2(FLASH_ITF_GET_INSTANCE(instance));
  key->key_w3 = LL_FLASH_GetOBKData3(FLASH_ITF_GET_INSTANCE(instance));

  return HAL_OK;
}

/**
  * @}
  */

/** @addtogroup FLASH_ITF_Exported_Functions_Group3
  * @{
This subsection provides a set of functions allowing to handle the FLASH ITF ECC interrupt subroutines:

- Call the function HAL_FLASH_ITF_IRQHandler() to handle Flash OB write operations.

- Call the function HAL_FLASH_ITF_OB_ProgramCpltCallback() to be redefined within application for the OB complete write
  operation callback.

- Call the function HAL_FLASH_ITF_OB_ErrorCallback() to be redefined within application the OB write error operation
  callback.
  */

/**
  * @brief  Handle the FLASH ITF interrupt request.
  *
  * @param  flashx  The FLASH instance.
  */
void HAL_FLASH_ITF_IRQHandler(hal_flash_t instance)
{
  uint32_t         flags;
  uint32_t         its;
  hal_flash_bank_t bank;

  ASSERT_DBG_PARAM(IS_FLASH_INSTANCE(instance));

  for (uint32_t bank_idx = 0U; bank_idx < 2U; bank_idx ++)
  {
    if (bank_idx == 0U)
    {
      its = LL_FLASH_READ_REG(FLASH_ITF_GET_INSTANCE(instance), AIER) & (LL_FLASH_FLAG_EOPF | LL_FLASH_FLAG_OBLERR);
    }
    else
    {
      its = LL_FLASH_READ_REG(FLASH_ITF_GET_INSTANCE(instance), BIER) & (LL_FLASH_FLAG_EOPF | LL_FLASH_FLAG_OBLERR);
    }

    bank = (bank_idx == 0U) ? HAL_FLASH_BANK_1 : HAL_FLASH_BANK_2;

    flags = LL_FLASH_ReadFlag(FLASH_ITF_GET_INSTANCE(instance),
                              (uint32_t)bank, (LL_FLASH_FLAG_EOPF | LL_FLASH_FLAG_OBLERR));

    if ((STM32_READ_BIT(flags, its) & LL_FLASH_FLAG_EOPF) != 0U)
    {
      LL_FLASH_ClearFlag(FLASH_ITF_GET_INSTANCE(instance), (uint32_t)bank, LL_FLASH_FLAG_EOPF);
      HAL_FLASH_ITF_OB_ProgramCpltCallback(instance);
    }

    if ((STM32_READ_BIT(flags, its) & LL_FLASH_FLAG_OBLERR) != 0U)
    {
      LL_FLASH_ClearFlag(FLASH_ITF_GET_INSTANCE(instance), (uint32_t)bank, LL_FLASH_FLAG_OBLERR);
      HAL_FLASH_ITF_OB_ErrorCallback(instance);
    }
  }
}

/**
  * @brief  FLASH ITF option bytes write complete callback.
  *
  * @param  flashx The FLASH instance.
  */
__WEAK void HAL_FLASH_ITF_OB_ProgramCpltCallback(hal_flash_t instance)
{
  ASSERT_DBG_PARAM(IS_FLASH_INSTANCE(instance));

  /* Prevent unused argument(s) compilation warning */
  STM32_UNUSED(instance);

  /*! <b>WARNING:</b> This function must not be modified, when the callback is needed, the
                      HAL_FLASH_ITF_OB_ProgramCpltCallback() could be implemented in the user file */
}

/**
  * @brief  FLASH ITF option bytes write error callback.
  *
  * @param  flashx The FLASH instance.
  */
__WEAK void HAL_FLASH_ITF_OB_ErrorCallback(hal_flash_t instance)
{
  ASSERT_DBG_PARAM(IS_FLASH_INSTANCE(instance));

  /* Prevent unused argument(s) compilation warning */
  STM32_UNUSED(instance);

  /*! <b>WARNING:</b> This function must not be modified, when the callback is needed, the
                      HAL_FLASH_ITF_OB_ErrorCallback() could be implemented in the user file */
}
/**
  * @}
  */

/** @addtogroup FLASH_ITF_Exported_Functions_Group4
  * @{
This subsection provides a set of functions allowing to program the option-bytes functions configuration:

- Call the function FLASH_ITF_OB_Program() to program the FLASH option-bytes.
  */

/**
  * @brief  Program the FLASH ITF option-bytes.
  * @param  instance  This parameter is one element of \ref hal_flash_t enumeration.
  * @retval HAL_ERROR Generated when an error occurred.
  * @retval HAL_OK    No error occurred.
  */
hal_status_t HAL_FLASH_ITF_OB_Program(hal_flash_t instance)
{
  ASSERT_DBG_PARAM(IS_FLASH_INSTANCE(instance));

  uint32_t tick_start;

  LL_FLASH_OB_StartModification(FLASH_ITF_GET_INSTANCE(instance));

  tick_start = HAL_GetTick();

  /* Wait for BSY flag to be cleared */
  while (LL_FLASH_IsActiveFlag_QW(FLASH_ITF_GET_INSTANCE(instance), LL_FLASH_BANK_1) != 0U)
  {
    if ((HAL_GetTick() - tick_start) > FLASH_ITF_OB_TIMEOUT)
    {
      /* Timeout occurred while waiting for end of operation */
      return HAL_ERROR;
    }
  }

  if (LL_FLASH_ReadFlag(FLASH_ITF_GET_INSTANCE(instance), LL_FLASH_BANK_1, LL_FLASH_FLAG_OPTERR) != 0U)
  {
    LL_FLASH_ClearFlag_OBLERRF(FLASH_ITF_GET_INSTANCE(instance), LL_FLASH_BANK_1);
    return HAL_ERROR;
  }

  return HAL_OK;
}
/**
  * @}
  */

/**
  * @}
  */

/** @addtogroup FLASH_ITF_Private_Functions
  * @{
  */

/**
  * @brief  Check the end of FLASH operation.
  * @retval HAL_ERROR There is an operation in progress.
  * @retval HAL_OK    No operation in progress.
  */
static hal_status_t FLASH_ITF_CheckForEndOfOperation(hal_flash_t instance)
{
  uint32_t status_asr;
  uint32_t status_bsr;
  uint32_t error_aisr;
  uint32_t error_bisr;

  status_asr = LL_FLASH_READ_BIT(FLASH_ITF_GET_INSTANCE(instance), ASR, LL_FLASH_FLAG_STATUS_ALL);
  status_bsr = LL_FLASH_READ_BIT(FLASH_ITF_GET_INSTANCE(instance), BSR, LL_FLASH_FLAG_STATUS_ALL);
  error_aisr = LL_FLASH_READ_BIT(FLASH_ITF_GET_INSTANCE(instance), AISR, LL_FLASH_FLAG_ERRORS_ALL);
  error_bisr = LL_FLASH_READ_BIT(FLASH_ITF_GET_INSTANCE(instance), BISR, LL_FLASH_FLAG_ERRORS_ALL);

  if ((status_asr != 0U) || (status_bsr != 0U) || (error_aisr != 0U) || (error_bisr != 0U))
  {
    return HAL_ERROR;
  }

  return HAL_OK;
}
/**
  * @}
  */
#endif /* USE_HAL_FLASH_MODULE */

/**
  * @}
  */

/**
  * @}
  */
