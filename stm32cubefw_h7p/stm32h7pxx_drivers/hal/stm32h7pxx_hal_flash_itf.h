/**
  **********************************************************************************************************************
  * @file    stm32h7pxx_hal_flash_itf.h
  * @author  GPM Application Team
  * @brief   Header file of FLASH ITF HAL module.
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

/* Define to prevent recursive inclusion -----------------------------------------------------------------------------*/
#ifndef STM32H7Pxx_HAL_ITF_H
#define STM32H7Pxx_HAL_ITF_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* Includes ----------------------------------------------------------------------------------------------------------*/
#include "stm32h7pxx_hal_def.h"
#include "stm32h7pxx_ll_flash.h"

/** @addtogroup STM32H7Pxx_HAL_Driver
  * @{
  */

/** @defgroup FLASH_ITF FLASH_ITF
  * @{
  */
/* Exported Constants ------------------------------------------------------------------------------------------------*/
/** @defgroup FLASH_ITF_Exported_Constants FLASH_ITF Exported Constants
  * @{
  */
#define HAL_FLASH_ITF_OB_STOP_MODE     1U /*!< FLASH ITF option bytes stop mode     */
#define HAL_FLASH_ITF_OB_STANDBY_MODE  2U /*!< FLASH ITF option bytes standby mode  */

#define HAL_FLASH_ITF_OB_IWDG          1U /*!< FLASH ITF option bytes IWDG          */
#define HAL_FLASH_ITF_OB_WWDG          2U /*!< FLASH ITF option bytes WWDG          */

#define HAL_FLASH_ITF_OB_SRAM          8U /*!< FLASH ITF option bytes SRAM          */

#define HAL_FLASH_ITF_OB_VDDIO         1U /*!< FLASH ITF option bytes VDDIO         */

/*! HAL FLASH ITF option bytes WRP pages definition */
#define  HAL_FLASH_ITF_OB_WRP_PAGE_0TO3       LL_FLASH_OB_WRP_PAGE_0TO3         /*!< Write protection of Pages 0 to 3     */
#define  HAL_FLASH_ITF_OB_WRP_PAGE_4TO7       LL_FLASH_OB_WRP_PAGE_4TO7         /*!< Write protection of Pages 4 to 7     */
#define  HAL_FLASH_ITF_OB_WRP_PAGE_8TO11      LL_FLASH_OB_WRP_PAGE_8TO11        /*!< Write protection of Pages 8 to 11    */
#define  HAL_FLASH_ITF_OB_WRP_PAGE_12TO15     LL_FLASH_OB_WRP_PAGE_12TO15       /*!< Write protection of Pages 12 to 15   */
#define  HAL_FLASH_ITF_OB_WRP_PAGE_16TO19     LL_FLASH_OB_WRP_PAGE_16TO19       /*!< Write protection of Pages 16 to 19   */
#define  HAL_FLASH_ITF_OB_WRP_PAGE_20TO23     LL_FLASH_OB_WRP_PAGE_20TO23       /*!< Write protection of Pages 20 to 23   */
#define  HAL_FLASH_ITF_OB_WRP_PAGE_24TO27     LL_FLASH_OB_WRP_PAGE_24TO27       /*!< Write protection of Pages 24 to 27   */
#define  HAL_FLASH_ITF_OB_WRP_PAGE_28TO31     LL_FLASH_OB_WRP_PAGE_28TO31       /*!< Write protection of Pages 28 to 31   */
#define  HAL_FLASH_ITF_OB_WRP_PAGE_32TO35     LL_FLASH_OB_WRP_PAGE_32TO35       /*!< Write protection of Pages 32 to 35   */
#define  HAL_FLASH_ITF_OB_WRP_PAGE_36TO39     LL_FLASH_OB_WRP_PAGE_36TO39       /*!< Write protection of Pages 36 to 39   */
#define  HAL_FLASH_ITF_OB_WRP_PAGE_40TO43     LL_FLASH_OB_WRP_PAGE_40TO43       /*!< Write protection of Pages 40 to 43   */
#define  HAL_FLASH_ITF_OB_WRP_PAGE_44TO47     LL_FLASH_OB_WRP_PAGE_44TO47       /*!< Write protection of Pages 44 to 47   */
#define  HAL_FLASH_ITF_OB_WRP_PAGE_48TO51     LL_FLASH_OB_WRP_PAGE_48TO51       /*!< Write protection of Pages 48 to 51   */
#define  HAL_FLASH_ITF_OB_WRP_PAGE_52TO55     LL_FLASH_OB_WRP_PAGE_52TO55       /*!< Write protection of Pages 52 to 55   */
#define  HAL_FLASH_ITF_OB_WRP_PAGE_56TO59     LL_FLASH_OB_WRP_PAGE_56TO59       /*!< Write protection of Pages 56 to 59   */
#define  HAL_FLASH_ITF_OB_WRP_PAGE_60TO63     LL_FLASH_OB_WRP_PAGE_60TO63       /*!< Write protection of Pages 60 to 63   */
#define  HAL_FLASH_ITF_OB_WRP_PAGE_64TO67     LL_FLASH_OB_WRP_PAGE_64TO67       /*!< Write protection of Pages 64 to 67   */
#define  HAL_FLASH_ITF_OB_WRP_PAGE_68TO71     LL_FLASH_OB_WRP_PAGE_68TO71       /*!< Write protection of Pages 68 to 71   */
#define  HAL_FLASH_ITF_OB_WRP_PAGE_72TO75     LL_FLASH_OB_WRP_PAGE_72TO75       /*!< Write protection of Pages 72 to 75   */
#define  HAL_FLASH_ITF_OB_WRP_PAGE_76TO79     LL_FLASH_OB_WRP_PAGE_76TO79       /*!< Write protection of Pages 76 to 79   */
#define  HAL_FLASH_ITF_OB_WRP_PAGE_80TO83     LL_FLASH_OB_WRP_PAGE_80TO83       /*!< Write protection of Pages 80 to 83   */
#define  HAL_FLASH_ITF_OB_WRP_PAGE_84TO87     LL_FLASH_OB_WRP_PAGE_84TO87       /*!< Write protection of Pages 84 to 87   */
#define  HAL_FLASH_ITF_OB_WRP_PAGE_88TO91     LL_FLASH_OB_WRP_PAGE_88TO91       /*!< Write protection of Pages 88 to 91   */
#define  HAL_FLASH_ITF_OB_WRP_PAGE_92TO95     LL_FLASH_OB_WRP_PAGE_92TO95       /*!< Write protection of Pages 92 to 95   */
#define  HAL_FLASH_ITF_OB_WRP_PAGE_96TO99     LL_FLASH_OB_WRP_PAGE_96TO99       /*!< Write protection of Pages 96 to 99   */
#define  HAL_FLASH_ITF_OB_WRP_PAGE_100TO103   LL_FLASH_OB_WRP_PAGE_100TO103     /*!< Write protection of Pages 100 to 103 */
#define  HAL_FLASH_ITF_OB_WRP_PAGE_104TO107   LL_FLASH_OB_WRP_PAGE_104TO107     /*!< Write protection of Pages 104 to 107 */
#define  HAL_FLASH_ITF_OB_WRP_PAGE_108TO111   LL_FLASH_OB_WRP_PAGE_108TO111     /*!< Write protection of Pages 108 to 111 */
#define  HAL_FLASH_ITF_OB_WRP_PAGE_112TO115   LL_FLASH_OB_WRP_PAGE_112TO115     /*!< Write protection of Pages 112 to 115 */
#define  HAL_FLASH_ITF_OB_WRP_PAGE_116TO119   LL_FLASH_OB_WRP_PAGE_116TO119     /*!< Write protection of Pages 116 to 119 */
#define  HAL_FLASH_ITF_OB_WRP_PAGE_120TO123   LL_FLASH_OB_WRP_PAGE_120TO123     /*!< Write protection of Pages 120 to 123 */
#define  HAL_FLASH_ITF_OB_WRP_PAGE_124TO127   LL_FLASH_OB_WRP_PAGE_124TO127     /*!< Write protection of Pages 124 to 127 */
#define  HAL_FLASH_ITF_OB_WRP_PAGE_ALL        LL_FLASH_OB_WRP_PAGE_ALL          /*!< Write protection of all Pages        */

/*! HAL FLASH ITF option bytes OTP lock blocks definition */
#define HAL_FLASH_ITF_OB_OTP_LOCK_BLOCK_0        LL_FLASH_OB_OTP_LOCK_BLOCK_0    /*!< OTP Lock Block0      */
#define HAL_FLASH_ITF_OB_OTP_LOCK_BLOCK_1        LL_FLASH_OB_OTP_LOCK_BLOCK_1    /*!< OTP Lock Block1      */
#define HAL_FLASH_ITF_OB_OTP_LOCK_BLOCK_2        LL_FLASH_OB_OTP_LOCK_BLOCK_2    /*!< OTP Lock Block2      */
#define HAL_FLASH_ITF_OB_OTP_LOCK_BLOCK_3        LL_FLASH_OB_OTP_LOCK_BLOCK_3    /*!< OTP Lock Block3      */
#define HAL_FLASH_ITF_OB_OTP_LOCK_BLOCK_4        LL_FLASH_OB_OTP_LOCK_BLOCK_4    /*!< OTP Lock Block4      */
#define HAL_FLASH_ITF_OB_OTP_LOCK_BLOCK_5        LL_FLASH_OB_OTP_LOCK_BLOCK_5    /*!< OTP Lock Block5      */
#define HAL_FLASH_ITF_OB_OTP_LOCK_BLOCK_6        LL_FLASH_OB_OTP_LOCK_BLOCK_6    /*!< OTP Lock Block6      */
#define HAL_FLASH_ITF_OB_OTP_LOCK_BLOCK_7        LL_FLASH_OB_OTP_LOCK_BLOCK_7    /*!< OTP Lock Block7      */
#define HAL_FLASH_ITF_OB_OTP_LOCK_BLOCK_8        LL_FLASH_OB_OTP_LOCK_BLOCK_8    /*!< OTP Lock Block8      */
#define HAL_FLASH_ITF_OB_OTP_LOCK_BLOCK_9        LL_FLASH_OB_OTP_LOCK_BLOCK_9    /*!< OTP Lock Block9      */
#define HAL_FLASH_ITF_OB_OTP_LOCK_BLOCK_10       LL_FLASH_OB_OTP_LOCK_BLOCK_10   /*!< OTP Lock Block10     */
#define HAL_FLASH_ITF_OB_OTP_LOCK_BLOCK_11       LL_FLASH_OB_OTP_LOCK_BLOCK_11   /*!< OTP Lock Block11     */
#define HAL_FLASH_ITF_OB_OTP_LOCK_BLOCK_12       LL_FLASH_OB_OTP_LOCK_BLOCK_12   /*!< OTP Lock Block12     */
#define HAL_FLASH_ITF_OB_OTP_LOCK_BLOCK_13       LL_FLASH_OB_OTP_LOCK_BLOCK_13   /*!< OTP Lock Block13     */
#define HAL_FLASH_ITF_OB_OTP_LOCK_BLOCK_14       LL_FLASH_OB_OTP_LOCK_BLOCK_14   /*!< OTP Lock Block14     */
#define HAL_FLASH_ITF_OB_OTP_LOCK_BLOCK_15       LL_FLASH_OB_OTP_LOCK_BLOCK_15   /*!< OTP Lock Block15     */
#define HAL_FLASH_ITF_OB_OTP_LOCK_BLOCK_ALL      LL_FLASH_OB_OTP_LOCK_BLOCK_ALL  /*!< OTP Lock All Blocks  */
/**
  * @}
  */

/* Exported types ----------------------------------------------------------------------------------------------------*/
/** @defgroup FLASH_ITF_Exported_Types FLASH_ITF Exported Types
  * @{
  */

/*! HAL FLASH instances enumeration definition */
typedef enum
{
  HAL_FLASH = (uint32_t)FLASH, /*!< FLASH Instance */
} hal_flash_t;

/*! HAL FLASH bank enumeration definition */
typedef enum
{
  HAL_FLASH_BANK_1 = LL_FLASH_BANK_1, /*!< FLASH bank 1   */
  HAL_FLASH_BANK_2 = LL_FLASH_BANK_2, /*!< FLASH bank 2   */
} hal_flash_bank_t;

/*! HAL FLASH ITF lock status enumeration definition */
typedef enum
{
  HAL_FLASH_ITF_UNLOCKED = 0U, /*!< FLASH unlocked */
  HAL_FLASH_ITF_LOCKED   = 1U  /*!< FLASH locked   */
} hal_flash_itf_lock_status_t;

/*! HAL FLASH ITF latency enumeration definition */
typedef enum
{
  HAL_FLASH_ITF_LATENCY_0  = LL_FLASH_LATENCY_0WS,  /*!< FLASH ITF zero wait state      */
  HAL_FLASH_ITF_LATENCY_1  = LL_FLASH_LATENCY_1WS,  /*!< FLASH ITF one wait state       */
  HAL_FLASH_ITF_LATENCY_2  = LL_FLASH_LATENCY_2WS,  /*!< FLASH ITF two wait states      */
  HAL_FLASH_ITF_LATENCY_3  = LL_FLASH_LATENCY_3WS,  /*!< FLASH ITF three wait states    */
  HAL_FLASH_ITF_LATENCY_4  = LL_FLASH_LATENCY_4WS,  /*!< FLASH ITF four wait states     */
  HAL_FLASH_ITF_LATENCY_5  = LL_FLASH_LATENCY_5WS,  /*!< FLASH ITF five wait states     */
  HAL_FLASH_ITF_LATENCY_6  = LL_FLASH_LATENCY_6WS,  /*!< FLASH ITF six wait states      */
  HAL_FLASH_ITF_LATENCY_7  = LL_FLASH_LATENCY_7WS,  /*!< FLASH ITF seven wait states    */
  HAL_FLASH_ITF_LATENCY_8  = LL_FLASH_LATENCY_8WS,  /*!< FLASH ITF eight wait states    */
  HAL_FLASH_ITF_LATENCY_9  = LL_FLASH_LATENCY_9WS,  /*!< FLASH ITF nine wait states     */
  HAL_FLASH_ITF_LATENCY_10 = LL_FLASH_LATENCY_10WS, /*!< FLASH ITF ten wait states      */
  HAL_FLASH_ITF_LATENCY_11 = LL_FLASH_LATENCY_11WS, /*!< FLASH ITF eleven wait states   */
  HAL_FLASH_ITF_LATENCY_12 = LL_FLASH_LATENCY_12WS, /*!< FLASH ITF twelve wait states   */
  HAL_FLASH_ITF_LATENCY_13 = LL_FLASH_LATENCY_13WS, /*!< FLASH ITF thirteen wait states */
  HAL_FLASH_ITF_LATENCY_14 = LL_FLASH_LATENCY_14WS, /*!< FLASH ITF fourteen wait states */
  HAL_FLASH_ITF_LATENCY_15 = LL_FLASH_LATENCY_15WS  /*!< FLASH ITF fifteen wait states  */
} hal_flash_itf_latency_t;

/*! HAL FLASH ITF programming delay enumeration definition */
typedef enum
{
  HAL_FLASH_ITF_PROGRAM_DELAY_0  = LL_FLASH_PROGRAM_DELAY_0,  /*!< FLASH 0 programming delay */
  HAL_FLASH_ITF_PROGRAM_DELAY_1  = LL_FLASH_PROGRAM_DELAY_1,  /*!< FLASH 1 programming delay */
  HAL_FLASH_ITF_PROGRAM_DELAY_2  = LL_FLASH_PROGRAM_DELAY_2,  /*!< FLASH 2 programming delay */
  HAL_FLASH_ITF_PROGRAM_DELAY_3  = LL_FLASH_PROGRAM_DELAY_3,  /*!< FLASH 3 programming delay */
} hal_flash_itf_program_delay_t;

/*! HAL FLASH ITF option bytes lock status enumeration definition */
typedef enum
{
  HAL_FLASH_ITF_OB_UNLOCKED = 0U, /*!< FLASH ITF option bytes unlocked */
  HAL_FLASH_ITF_OB_LOCKED   = 1U  /*!< FLASH ITF option bytes locked   */
} hal_flash_itf_ob_lock_status_t;

/*! HAL FLASH ITF option bytes BOR Level enumeration definition */
typedef enum
{
  HAL_FLASH_ITF_OB_BOR_LEVEL_0 = LL_FLASH_OB_BOR_LEVEL_0, /*!< FLASH ITF option bytes BOR level 0 */
  HAL_FLASH_ITF_OB_BOR_LEVEL_1 = LL_FLASH_OB_BOR_LEVEL_1, /*!< FLASH ITF option bytes BOR level 1 */
  HAL_FLASH_ITF_OB_BOR_LEVEL_2 = LL_FLASH_OB_BOR_LEVEL_2, /*!< FLASH ITF option bytes BOR level 2 */
  HAL_FLASH_ITF_OB_BOR_LEVEL_3 = LL_FLASH_OB_BOR_LEVEL_3, /*!< FLASH ITF option bytes BOR level 3 */
} hal_flash_itf_ob_bor_level_t;

/*! HAL FLASH ITF option bytes key HDP Level enumeration definition */
typedef enum
{
  HAL_FLASH_ITF_OBK_LEVEL_CURRENT  = LL_FLASH_OBK_LEVEL_CURRENT,   /*!< Key stored for the HDPL indicated in SBS_HDPLSR  */
  HAL_FLASH_ITF_OBK_LEVEL_NEXT     = LL_FLASH_OBK_LEVEL_NEXT,      /*!< Key stored for the HDPL indicated in SBS_HDPLSR + 1  */
  HAL_FLASH_ITF_OBK_LEVEL_PLUS_TWO = LL_FLASH_OBK_LEVEL_PLUS_TWO,  /*!< Key stored for the HDPL indicated in SBS_HDPLSR + 2  */
} hal_flash_itf_obk_hpdl_t;

/*! HAL FLASH ITF option bytes boot address lock status enumeration definition */
typedef enum
{
  HAL_FLASH_ITF_OB_BOOT_UNLOCKED = 0U, /*!< FLASH ITF option bytes boot unlocked */
  HAL_FLASH_ITF_OB_BOOT_LOCKED   = 1U  /*!< FLASH ITF option bytes boot locked   */
} hal_flash_itf_ob_boot_lock_status_t;

/*! HAL FLASH ITF option bytes hide protection area enumeration definition*/
typedef enum
{
  HAL_FLASH_ITF_HDP_NO_ACCESS_PROTECTION        = LL_FLASH_HDP_NO_ACCESS_PROTECTION,        /*!< HDP extension is not active and can be configured with HDPEXT */
  HAL_FLASH_ITF_HDP_ONLY_AREA_ACCESS_PROTECTION = LL_FLASH_HDP_ONLY_AREA_ACCESS_PROTECTION, /*!< HDP extension is active and can only be increased with HDPEXT */
  HAL_FLASH_ITF_HDP_ALL_ACCESS_PROTECTION       = LL_FLASH_HDP_ALL_ACCESS_PROTECTION        /*!< HDP extension is active and its configuration is locked until reset */
} hal_flash_itf_hdp_access_protection_t;

/*! HAL FLASH ITF ECC interruption status enumeration definition */
typedef enum
{
  HAL_FLASH_ITF_ECC_IT_DISABLED = 0U, /*!< FLASH ITF ECC interruption disabled */
  HAL_FLASH_ITF_ECC_IT_ENABLED  = 1U  /*!< FLASH ITF ECC interruption enabled  */
} hal_flash_itf_ecc_it_status_t;

/*! HAL FLASH ITF option bytes Erased sram when system reset enumeration definition */
typedef enum
{
  HAL_FLASH_ITF_OB_NVSTATE_OPEN  = LL_FLASH_OB_NVSTATE_OPEN,   /*!< FLASH ITF option bytes Open non-volatile state   */
  HAL_FLASH_ITF_OB_NVSTATE_CLOSE = LL_FLASH_OB_NVSTATE_CLOSE  /*!< FLASH ITF option bytes Closed non-volatile state */
} hal_flash_itf_ob_nv_state_t;

/*! HAL FLASH ITF option bytes Erased sram when system reset enumeration definition */
typedef enum
{
  HAL_FLASH_ITF_OB_DBG_AUTH_DEFAULT  = LL_FLASH_OB_DBG_AUTH_DEFAULT,     /*!< FLASH ITF option bytes Locked device (no debug allowed)      */
  HAL_FLASH_ITF_OB_DBG_AUTH_PASSWORD = LL_FLASH_OB_DBG_AUTH_PASSWORD,    /*!< FLASH ITF option bytes Authentication method using password  */
  HAL_FLASH_ITF_OB_DBG_AUTH_LOCKED   = LL_FLASH_OB_DBG_AUTH_LOCKED       /*!< FLASH ITF option bytes No authentication method selected (default value) */
} hal_flash_itf_ob_dbg_auth_t;

/*! HAL FLASH ITF option bytes Erased sram when system reset enumeration definition */
typedef enum
{
  HAL_FLASH_ITF_OB_OEM_PROVD_ENABLE  = LL_FLASH_OB_OEM_PROVD_ENABLE,  /*!< FLASH ITF option bytes Device is in OEM provisioned state     */
  HAL_FLASH_ITF_OB_OEM_PROVD_DEFAULT = LL_FLASH_OB_OEM_PROVD_DEFAULT  /*!< FLASH ITF option bytes Device is not in OEM provisioned state */
} hal_flash_itf_ob_oem_provd_t;

/*! HAL FLASH ITF option bytes reset generation when enter in low power mode enumeration definition */
typedef enum
{
  HAL_FLASH_ITF_OB_RST_GENERATION    = 0U, /*!< FLASH ITF OB reset generation when enter in low power mode */
  HAL_FLASH_ITF_OB_NO_RST_GENERATION = 1U  /*!< FLASH ITF OB no reset generation when enter in low power mode */
} hal_flash_itf_ob_rst_generation_status_t;

/*! HAL FLASH ITF option bytes WDG hardware/software mode enumeration definition */
typedef enum
{
  HAL_FLASH_ITF_OB_WDG_HARDWARE = 0U, /*!< FLASH ITF option bytes WDG hardware select */
  HAL_FLASH_ITF_OB_WDG_SOFTWARE = 1U  /*!< FLASH ITF option bytes WDG software select */
} hal_flash_itf_ob_wdg_mode_t;

/*! HAL FLASH ITF option bytes WDG counter low power mode freeze enumeration definition */
typedef enum
{
  HAL_FLASH_ITF_OB_WDG_FROZEN   = 1U, /*!< FLASH ITF OB WDG counter low power mode frozen  */
  HAL_FLASH_ITF_OB_WDG_UNFROZEN = 0U  /*!< FLASH ITF OB WDG counter low power mode running */
} hal_flash_itf_ob_wdg_freeze_status_t;

/*! HAL FLASH ITF option bytes Swapping bank enumeration definition */
typedef enum
{
  HAL_FLASH_ITF_OB_BANK_NO_SWAP = LL_FLASH_OB_BANK_NOT_SWAPPED, /*!< FLASH ITF option bytes Bank not swapped */
  HAL_FLASH_ITF_OB_BANK_SWAP    = LL_FLASH_OB_BANK_SWAPPED      /*!< FLASH ITF option bytes Bank swapped     */
} hal_flash_itf_ob_bank_swap_t;

/*! HAL FLASH ITF option bytes SRAM ECC enumeration definition */
typedef enum
{
  HAL_FLASH_ITF_OB_SRAM_ECC_DISABLED = 0U, /*!< FLASH ITF option bytes SRAM ECC disable */
  HAL_FLASH_ITF_OB_SRAM_ECC_ENABLED  = 1U  /*!< FLASH ITF option bytes SRAM ECC enable  */
} hal_flash_itf_ob_sram_ecc_status_t ;

/*! HAL FLASH ITF option bytes VDDI HSLV enumeration definition */
typedef enum
{
  HAL_FLASH_ITF_OB_VDDX_HSLV_DISABLED = 0U, /*!< FLASH ITF option bytes VDD HSLV disable */
  HAL_FLASH_ITF_OB_VDDX_HSLV_ENABLED  = 1U  /*!< FLASH ITF option bytes VDD HSLV enable  */
} hal_flash_itf_ob_vddx_hslv_status_t;

typedef struct
{
  uint32_t key_w0; /*!< FLASH ITF OBK word 0 */
  uint32_t key_w1; /*!< FLASH ITF OBK word 1 */
  uint32_t key_w2; /*!< FLASH ITF OBK word 2 */
  uint32_t key_w3; /*!< FLASH ITF OBK word 3 */
} hal_flash_itf_ob_obk_t;

/**
  * @}
  */

/* Exported functions ------------*/
/** @defgroup FLASH_ITF_Exported_Functions FLASH ITF Exported Functions
  * @{
  */

/** @defgroup FLASH_ITF_Exported_Functions_Group1 FLASH ITF Control and Lock/Unlock functions
  * @{
  */
hal_status_t                HAL_FLASH_ITF_Lock(hal_flash_t instance);
hal_status_t                HAL_FLASH_ITF_Unlock(hal_flash_t instance);
hal_flash_itf_lock_status_t HAL_FLASH_ITF_IsLocked(hal_flash_t instance);

hal_status_t                HAL_FLASH_ITF_LockBank(hal_flash_t instance, hal_flash_bank_t bank);
hal_status_t                HAL_FLASH_ITF_UnlockBank(hal_flash_t instance, hal_flash_bank_t bank);
hal_flash_itf_lock_status_t HAL_FLASH_ITF_IsLockedBank(hal_flash_t instance, hal_flash_bank_t bank);

hal_status_t            HAL_FLASH_ITF_SetLatency(hal_flash_t instance, hal_flash_itf_latency_t latency);
hal_flash_itf_latency_t HAL_FLASH_ITF_GetLatency(hal_flash_t instance);

hal_status_t HAL_FLASH_ITF_SetProgrammingDelay(hal_flash_t instance, hal_flash_itf_program_delay_t prog_delay);
hal_flash_itf_program_delay_t HAL_FLASH_ITF_GetProgrammingDelay(hal_flash_t instance);

hal_status_t HAL_FLASH_ITF_SetHDPExtArea(hal_flash_t instance, hal_flash_bank_t bank, uint32_t page);
uint32_t     HAL_FLASH_ITF_GetHDPExtArea(hal_flash_t instance, hal_flash_bank_t bank);

hal_status_t HAL_FLASH_ITF_SetHDPExtAccessProtection(hal_flash_t instance,
                                                     hal_flash_bank_t bank,
                                                     hal_flash_itf_hdp_access_protection_t hdp_ext_access);
hal_flash_itf_hdp_access_protection_t HAL_FLASH_ITF_GetHDPExtAccessProtection(hal_flash_t instance,
                                                                              hal_flash_bank_t bank);

#if defined (USE_HAL_FLASH_ECC) && (USE_HAL_FLASH_ECC == 1U)
hal_status_t HAL_FLASH_ITF_ECC_EnableSingleErrorIT(hal_flash_t instance, hal_flash_bank_t bank);
hal_status_t HAL_FLASH_ITF_ECC_DisableSingleErrorIT(hal_flash_t instance, hal_flash_bank_t bank);
hal_flash_itf_ecc_it_status_t HAL_FLASH_ITF_ECC_IsEnabledSingleErrorIT(hal_flash_t instance, hal_flash_bank_t bank);

hal_status_t HAL_FLASH_ITF_ECC_EnableDoubleErrorIT(hal_flash_t instance, hal_flash_bank_t bank);
hal_status_t HAL_FLASH_ITF_ECC_DisableDoubleErrorIT(hal_flash_t instance, hal_flash_bank_t bank);
hal_flash_itf_ecc_it_status_t HAL_FLASH_ITF_ECC_IsEnabledDoubleErrorIT(hal_flash_t instance, hal_flash_bank_t bank);
#endif /* USE_HAL_FLASH_ECC */
/**
  * @}
  */

/** @defgroup FLASH_ITF_Exported_Functions_Group2 FLASH ITF Configure option bytes functions
  * @{
  */
hal_status_t                   HAL_FLASH_ITF_OB_Lock(hal_flash_t instance);
hal_status_t                   HAL_FLASH_ITF_OB_Unlock(hal_flash_t instance);
hal_flash_itf_ob_lock_status_t HAL_FLASH_ITF_OB_IsLocked(hal_flash_t instance);

hal_status_t HAL_FLASH_ITF_OB_EnablePageWRP(hal_flash_t instance, hal_flash_bank_t bank, uint32_t pages);
hal_status_t HAL_FLASH_ITF_OB_DisablePageWRP(hal_flash_t instance, hal_flash_bank_t bank, uint32_t pages);
uint32_t HAL_FLASH_ITF_OB_IsEnabledPageWRP(hal_flash_t instance, hal_flash_bank_t bank, uint32_t pages);

hal_status_t HAL_FLASH_ITF_OB_SetHDPArea(hal_flash_t instance,
                                         hal_flash_bank_t bank,
                                         uint32_t start_page,
                                         uint32_t page_nbr);
void HAL_FLASH_ITF_OB_GetHDPArea(hal_flash_t instance,
                                 hal_flash_bank_t bank,
                                 uint32_t *p_start_page,
                                 uint32_t *p_page_nbr);

hal_status_t HAL_FLASH_ITF_OB_LockOTPBlock(hal_flash_t instance, uint32_t blocks);
uint32_t HAL_FLASH_ITF_OB_IsLockedOTPBlock(hal_flash_t instance, uint32_t blocks);

hal_status_t HAL_FLASH_ITF_OB_SetNVState(hal_flash_t instance, hal_flash_itf_ob_nv_state_t nv_state);
hal_flash_itf_ob_nv_state_t HAL_FLASH_ITF_OB_GetNVState(hal_flash_t instance);

hal_status_t                        HAL_FLASH_ITF_OB_LockBootConfig(hal_flash_t instance);
hal_status_t                        HAL_FLASH_ITF_OB_UnlockBootConfig(hal_flash_t instance);
hal_flash_itf_ob_boot_lock_status_t HAL_FLASH_ITF_OB_IsLockedBootConfig(hal_flash_t instance);

hal_status_t HAL_FLASH_ITF_OB_SetDebugAuthenticationMethod(hal_flash_t instance, hal_flash_itf_ob_dbg_auth_t dbg_auth);
hal_flash_itf_ob_dbg_auth_t HAL_FLASH_ITF_OB_GetDebugAuthenticationMethod(hal_flash_t instance);

hal_status_t HAL_FLASH_ITF_OB_SetOEMProvisioning(hal_flash_t instance, hal_flash_itf_ob_oem_provd_t oem_provd);
hal_flash_itf_ob_oem_provd_t HAL_FLASH_ITF_OB_GetOEMProvisioning(hal_flash_t instance);

hal_status_t HAL_FLASH_ITF_OB_SetBORLevel(hal_flash_t instance, hal_flash_itf_ob_bor_level_t bor_level);
hal_flash_itf_ob_bor_level_t HAL_FLASH_ITF_OB_GetBORLevel(hal_flash_t instance);

hal_status_t HAL_FLASH_ITF_OB_SetEnterLowPWRModeRstGeneration(hal_flash_t instance, uint32_t low_pwr_mode,
                                                              hal_flash_itf_ob_rst_generation_status_t rst_gen);
hal_flash_itf_ob_rst_generation_status_t HAL_FLASH_ITF_OB_GetEnterLowPWRModeRstGeneration(hal_flash_t instance,
    uint32_t low_pwr_mode);

hal_status_t HAL_FLASH_ITF_OB_SetIWDGMode(hal_flash_t instance, hal_flash_itf_ob_wdg_mode_t mode);
hal_flash_itf_ob_wdg_mode_t HAL_FLASH_ITF_OB_GetIWDGMode(hal_flash_t instance);

hal_status_t HAL_FLASH_ITF_OB_FreezeIWDGCounterLowPWRMode(hal_flash_t instance, uint32_t low_pwr_mode);
hal_status_t HAL_FLASH_ITF_OB_UnfreezeIWDGCounterLowPWRMode(hal_flash_t instance, uint32_t low_pwr_mode);
hal_flash_itf_ob_wdg_freeze_status_t HAL_FLASH_ITF_OB_IsFrozenIWDGCounterLowPWRMode(hal_flash_t instance,
    uint32_t low_pwr_mode);

hal_status_t HAL_FLASH_ITF_OB_SetBankSwap(hal_flash_t instance, hal_flash_itf_ob_bank_swap_t bank_swap);
hal_flash_itf_ob_bank_swap_t HAL_FLASH_ITF_OB_GetBankSwap(hal_flash_t instance);

hal_status_t HAL_FLASH_ITF_OB_EnableSRAMECC(hal_flash_t instance, uint32_t sram);
hal_status_t HAL_FLASH_ITF_OB_DisableSRAMECC(hal_flash_t instance, uint32_t sram);
hal_flash_itf_ob_sram_ecc_status_t HAL_FLASH_ITF_OB_IsEnabledSRAMECC(hal_flash_t instance, uint32_t sram);

hal_status_t HAL_FLASH_ITF_OB_EnableVddxHighSpeedLowVoltage(hal_flash_t instance, uint32_t vdd);
hal_status_t HAL_FLASH_ITF_OB_DisableVddxHighSpeedLowVoltage(hal_flash_t instance, uint32_t vdd);
hal_flash_itf_ob_vddx_hslv_status_t HAL_FLASH_ITF_OB_IsEnabledVddxHighSpeedLowVoltage(hal_flash_t instance,
    uint32_t vdd);

hal_status_t HAL_FLASH_ITF_OB_ProgramKey(hal_flash_t instance,
                                         hal_flash_itf_obk_hpdl_t hdp_level,
                                         uint32_t index,
                                         const hal_flash_itf_ob_obk_t *key);
hal_status_t HAL_FLASH_ITF_OB_EraseKey(hal_flash_t instance, hal_flash_itf_obk_hpdl_t hdp_level, uint32_t index);
hal_status_t HAL_FLASH_ITF_OB_GetKey(hal_flash_t instance,
                                     hal_flash_itf_obk_hpdl_t hdp_level, uint32_t index, hal_flash_itf_ob_obk_t *key);
/**
  * @}
  */

/** @defgroup FLASH_ITF_Exported_Functions_Group3 FLASH ITF IRQHandler and callback functions
  * @{
  */
void HAL_FLASH_ITF_IRQHandler(hal_flash_t instance);

void HAL_FLASH_ITF_OB_ProgramCpltCallback(hal_flash_t instance);
void HAL_FLASH_ITF_OB_ErrorCallback(hal_flash_t instance);
/**
  * @}
  */

/** @defgroup FLASH_ITF_Exported_Functions_Group4 FLASH ITF program option-bytes functions configuration
  * @{
  */
hal_status_t HAL_FLASH_ITF_OB_Program(hal_flash_t instance);
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

#endif /* STM32H7Pxx_HAL_ITF_H */
