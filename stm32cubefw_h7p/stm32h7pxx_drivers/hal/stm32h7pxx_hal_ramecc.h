/**
  **********************************************************************************************************************
  * @file    stm32h7pxx_hal_ramecc.h
  * @author  GPM Application Team
  * @brief   Header file of RAMECC HAL module.
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
#ifndef STM32H7PXX_HAL_RAMECC_H
#define STM32H7PXX_HAL_RAMECC_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* Includes ----------------------------------------------------------------------------------------------------------*/
#include "stm32h7pxx_hal_def.h"
#include "stm32h7pxx_ll_ramecc.h"

/** @addtogroup STM32H7Pxx_HAL_Driver
  * @{
  */

/** @addtogroup RAMECC
  * @{
  */

/* Exported constants ---------------------------------------------------------*/
/** @defgroup RAMECC_Exported_Constants RAMECC Exported Constants
  * @{
  */

/** @defgroup  RAMECC_Global_Interrupts RAMECC global interrupts
  * @{
  */
#define HAL_RAMECC_IT_GLOBAL_SE    LL_RAMECC_IT_GLOBAL_SE   /*!< RAMECC global single error interrupt               */
#define HAL_RAMECC_IT_GLOBAL_DE    LL_RAMECC_IT_GLOBAL_DE   /*!< RAMECC global double error interrupt               */
#define HAL_RAMECC_IT_GLOBAL_DEBW  LL_RAMECC_IT_GLOBAL_DEBW /*!< RAMECC global double error on byte write interrupt */
#define HAL_RAMECC_IT_GLOBAL_ALL   LL_RAMECC_IT_GLOBAL_ALL  /*!< RAMECC global all RAMECC interrupts                */
/**
  * @}
  */

/** @defgroup  RAMECC_Monitor_Interrupts RAMECC monitor interrupts
  * @{
  */
#define HAL_RAMECC_IT_MONITOR_SE   LL_RAMECC_IT_MONITOR_SE   /*!< RAMECC monitor single error interrupt               */
#define HAL_RAMECC_IT_MONITOR_DE   LL_RAMECC_IT_MONITOR_DE   /*!< RAMECC monitor double error interrupt               */
#define HAL_RAMECC_IT_MONITOR_DEBW LL_RAMECC_IT_MONITOR_DEBW /*!< RAMECC monitor double error on byte write interrupt */
#define HAL_RAMECC_IT_MONITOR_ALL  LL_RAMECC_IT_MONITOR_ALL  /*!< RAMECC monitor all RAMECC interrupts                */
/**
  * @}
  */

/**
  * @}
  */

/* Exported types ----------------------------------------------------------------------------------------------------*/
/** @defgroup RAMECC_Exported_Types HAL RAMECC Types
  * @{
  */

/*! HAL RAMECC instance enumeration definition */
typedef enum
{
  HAL_RAMECC1 = RAMECC1_BASE,  /*!< RAMECC unit 1 instance  */
  HAL_RAMECC2 = RAMECC2_BASE   /*!< RAMECC unit 2 instance  */
} hal_ramecc_t;

/*! HAL RAMECC monitor instance enumeration definition */
typedef enum
{
  HAL_RAMECC_MONITOR_AXISRAM1 = RAMECC1_AXISRAM1_BASE,  /*!< RAMECC AXISRAM1 monitor instance */
  HAL_RAMECC_MONITOR_AXISRAM2 = RAMECC1_AXISRAM2_BASE,  /*!< RAMECC AXISRAM2 monitor instance */
  HAL_RAMECC_MONITOR_AXISRAM3 = RAMECC1_AXISRAM3_BASE,  /*!< RAMECC AXISRAM3 monitor instance */
  HAL_RAMECC_MONITOR_AXISRAM4 = RAMECC1_AXISRAM4_BASE,  /*!< RAMECC AXISRAM4 monitor instance */
  HAL_RAMECC_MONITOR_ITCM = RAMECC1_ITCM_BASE,      /*!< RAMECC ITCM monitor instance     */
  HAL_RAMECC_MONITOR_DTCM0 = RAMECC1_DTCM0_BASE,     /*!< RAMECC DTCM0 monitor instance    */
  HAL_RAMECC_MONITOR_DTCM1 = RAMECC1_DTCM1_BASE,     /*!< RAMECC DTCM1 monitor instance    */
  HAL_RAMECC_MONITOR_BKPSRAM = RAMECC2_BKPSRAM_BASE    /*!< RAMECC BKPSRAM monitor instance   */
} hal_ramecc_monitor_t;

/*! HAL RAMECC ECC interrupt status enumeration definition */
typedef enum
{
  HAL_RAMECC_IT_DISABLED = 0U, /*!< RAMECC ECC interrupt disabled */
  HAL_RAMECC_IT_ENABLED  = 1U  /*!< RAMECC ECC interrupt enabled  */
} hal_ramecc_it_status_t;

/*! HAL RAMECC ECC fail type enumeration definition */
typedef enum
{
  HAL_RAMECC_ERROR_ECC_NONE = 0U,                  /*!< RAMECC ECC fail none                                  */
  HAL_RAMECC_ERROR_ECC_SE   = LL_RAMECC_FLAG_SE,   /*!< RAMECC ECC fail single error detection and correction */
  HAL_RAMECC_ERROR_ECC_DE   = LL_RAMECC_FLAG_DE,   /*!< RAMECC ECC fail double error detection                */
  HAL_RAMECC_ERROR_ECC_DEBW = LL_RAMECC_FLAG_DEBW  /*!< RAMECC ECC fail double error on byte write detection  */
} hal_ramecc_fail_type_t;

/*! HAL RAMECC ECC fail structure definition */
typedef struct
{
  hal_ramecc_fail_type_t type;    /*!< RAMECC ECC fail type    */
  uint32_t                   address; /*!< RAMECC ECC fail address */
  uint32_t                   code;    /*!< RAMECC ECC fail code    */
  uint64_t                   data;    /*!< RAMECC ECC fail data    */
} hal_ramecc_fail_info_t;

/*! HAL RAMECC ECC error address latching status enumeration definition */
typedef enum
{
  HAL_RAMECC_ADDR_LATCHING_DISABLED = 0U, /*!< RAMECC ECC error address latching disabled */
  HAL_RAMECC_ADDR_LATCHING_ENABLED  = 1U  /*!< RAMECC ECC error address latching enabled  */
} hal_ramecc_addr_latching_status_t;

/**
  * @}
  */

/* Exported functions ------------------------------------------------------------------------------------------------*/
/** @defgroup RAMECC_Exported_Functions HAL RAMECC Functions
  * @{
  */

/** @defgroup RAMECC_Exported_Functions_Group1 ECC operation functions
  * @{
  */

hal_status_t HAL_RAMECC_EnableGlobalIT(hal_ramecc_t instance, uint32_t interrupt);
hal_status_t HAL_RAMECC_DisableGlobalIT(hal_ramecc_t instance, uint32_t interrupt);
hal_ramecc_it_status_t HAL_RAMECC_IsEnabledGlobalIT(const hal_ramecc_t instance, uint32_t interrupt);

hal_status_t HAL_RAMECC_EnableMonitorIT(hal_ramecc_monitor_t instance, uint32_t interrupt);
hal_status_t HAL_RAMECC_DisableMonitorIT(hal_ramecc_monitor_t instance, uint32_t interrupt);
hal_ramecc_it_status_t HAL_RAMECC_IsEnabledMonitorIT(const hal_ramecc_monitor_t instance, uint32_t interrupt);

hal_status_t HAL_RAMECC_EnableErrorAddressLatching(hal_ramecc_monitor_t instance);
hal_status_t HAL_RAMECC_DisableErrorAddressLatching(hal_ramecc_monitor_t instance);
hal_ramecc_addr_latching_status_t HAL_RAMECC_IsEnabledErrorAddressLatching(const hal_ramecc_monitor_t instance);

void HAL_RAMECC_ECC_GetFailInfo(const hal_ramecc_monitor_t instance, hal_ramecc_fail_info_t *p_info);
/**
  * @}
  */

/** @defgroup RAMECC_Exported_Functions_Group2 Handle interrupt and callbacks functions
  * @{
  */
/* IRQHandler APIs */
void HAL_RAMECC_IRQHandler(hal_ramecc_monitor_t instance);

/* Callback APIs */
void HAL_RAMECC_ErrorCallback(hal_ramecc_monitor_t instance);

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
#endif
#endif /* STM32H7PXX_HAL_RAMECC_H */
