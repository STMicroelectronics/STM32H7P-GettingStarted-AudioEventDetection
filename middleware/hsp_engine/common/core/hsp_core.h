/**
  ******************************************************************************
  * @file    hsp_core.h
  * @brief   Header file for hsp_core.c
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */

/* Define to prevent recursive  ----------------------------------------------*/
#ifndef HSP_CORE_H
#define HSP_CORE_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* Includes ------------------------------------------------------------------*/
#include "hsp_conf.h"
#include "hsp_engine_rsrc_map.h"
#include "hsp_api_def.h"
#include "hsp_hw_if.h"
#if defined(USE_HSP_PLUGIN) && (USE_HSP_PLUGIN == 1)
#include "hsp_plugin_def.h"
#endif /* USE_HSP_PLUGIN */

/** @addtogroup HSP_ENGINE
  * @{
  */

/** @defgroup HSP_CORE HSP Core
  * @{
  */

/** @defgroup HSP_CORE_Manager HSP Core Manager
  * @{
  */

/* Exported constants --------------------------------------------------------*/
/** @defgroup HSP_CORE_Exported_Constants HSP Core Exported Constants
  * @{
  */

/** @defgroup HSP_CORE_Error_Code  HSP Error Code
  * @{
  */
#define HSP_CORE_ERROR_NONE           (0UL)            /*!< HSP no error */
#define HSP_CORE_ERROR_INIT           (0x01UL << 1U)   /*!< HSP init failed as it was already done */
#define HSP_CORE_ERROR_INVALID_PARAM  (0x01UL << 2U)   /*!< HSP invalid parameter */

#define HSP_CORE_HW_ERROR_MINOR  HSP_HW_IF_ERROR_MINOR  /*!< HSP HW minor error category */
#define HSP_CORE_HW_ERROR_FAULT  HSP_HW_IF_ERROR_FAULT  /*!< HSP HW fault error category */

#define HSP_CORE_HW_ERROR_INFO_SLAVE_AHB_ACCESS     HSP_HW_IF_ERROR_INFO_SLAVE_AHB_ACCESS     /*!< Signal Processor Engine Slave AHB Access error                                */
#define HSP_CORE_HW_ERROR_INFO_INTERNAL_AHB_ACCESS  HSP_HW_IF_ERROR_INFO_INTERNAL_AHB_ACCESS  /*!< Signal Processor Engine AHB Access error to HSP_CTRL                          */
#define HSP_CORE_HW_ERROR_INFO_DATA_MEM_ACCESS      HSP_HW_IF_ERROR_INFO_DATA_MEM_ACCESS      /*!< Signal Processor Engine Data Memory Access error                              */
#define HSP_CORE_HW_ERROR_INFO_CODE_MEM_ACCESS      HSP_HW_IF_ERROR_INFO_CODE_MEM_ACCESS      /*!< Signal Processor Engine Code Memory Access error                              */

#define HSP_CORE_HW_ERROR_INFO_FPU_INEXACT   HSP_HW_IF_ERROR_INFO_FPU_INEXACT  /*!< Floating Point Unit Inexact Exception       */
#define HSP_CORE_HW_ERROR_INFO_FPU_UDF       HSP_HW_IF_ERROR_INFO_FPU_UDF      /*!< Floating Point Unit Underflow error         */
#define HSP_CORE_HW_ERROR_INFO_FPU_OVF       HSP_HW_IF_ERROR_INFO_FPU_OVF      /*!< Floating Point Unit Overflow error          */
#define HSP_CORE_HW_ERROR_INFO_FPU_DIVZERO   HSP_HW_IF_ERROR_INFO_FPU_DIVZERO  /*!< Floating Point Unit Division By Zero error  */
#define HSP_CORE_HW_ERROR_INFO_FPU_INVALID   HSP_HW_IF_ERROR_INFO_FPU_INVALID  /*!< Floating Point Unit Invalid Exception error */
#define HSP_CORE_HW_ERROR_INFO_FPU_DENORMAL  HSP_HW_IF_ERROR_INFO_FPU_DENORMAL /*!< Floating Point Unit Denormal error          */

/**
  * @}
  */

#define HSP_CORE_TRGO_0  ((uint32_t)HSP_HW_IF_TRGO_0)
#define HSP_CORE_TRGO_1  ((uint32_t)HSP_HW_IF_TRGO_1)
#define HSP_CORE_TRGO_2  ((uint32_t)HSP_HW_IF_TRGO_2)
#define HSP_CORE_TRGO_3  ((uint32_t)HSP_HW_IF_TRGO_3)

#define HSP_CORE_TRGO_SRC_STREAM  ((uint32_t)HSP_HW_IF_TRGO_SOURCE_STREAM)
#define HSP_CORE_TRGO_SRC_SPE     ((uint32_t)HSP_HW_IF_TRGO_SOURCE_SPE)
#define HSP_CORE_TRGO_SRC_TSC     ((uint32_t)HSP_HW_IF_TRGO_SOURCE_TSC)

/**
  * @}
  */

/* Exported Types ------------------------------------------------------------*/
/** @addtogroup HSP_CORE_Exported_Types
  * @{
  */

/** @defgroup HSP_CORE_SmartClocking  HSP Core SmartClocking Enumerations
  * @{
  */
typedef enum
{
  HSP_CORE_SMART_CLOCKING_SPE = (HSP_HW_IF_SMARTCLOCKING_SPE),
  HSP_CORE_SMART_CLOCKING_MMC = (HSP_HW_IF_SMARTCLOCKING_MMC),
  HSP_CORE_SMART_CLOCKING_CTRL = (HSP_HW_IF_SMARTCLOCKING_CTRL),
#ifdef __HSP_DMA__
  HSP_CORE_SMART_CLOCKING_HSPDMA = (HSP_HW_IF_SMARTCLOCKING_HSPDMA)
#endif /* __HSP_DMA__ */
} hsp_core_smart_clocking_t;

typedef enum
{
  HSP_CORE_SMART_CLOCKING_DISABLED = 0U,
  HSP_CORE_SMART_CLOCKING_ENABLED = 1U,
} hsp_core_smart_clocking_status_t;

/**
  * @}
  */

/**
  * @}
  */

/* Exported Functions --------------------------------------------------------*/
/** @defgroup HSP_CORE_Exported_Functions HSP Core Exported Functions
  * @{
  */

/** @defgroup HSP_CORE_Exported_Functions_Group1 HSP Init functions
  * @{
  */
hsp_core_status_t HSP_CORE_Init(hsp_engine_context_t *hmw, const hsp_engine_hw_context_t *p_hw_ctx);
void HSP_CORE_DeInit(hsp_engine_context_t *hmw);

/**
  * @}
  */

/** @defgroup HSP_CORE_Exported_Functions_Group2 HSP Output Trigger Management
  * @{
  */
hsp_core_status_t HSP_CORE_OUTPUT_SetConfig(hsp_engine_context_t *hmw, uint32_t trgo_id,
                                            uint32_t source);
hsp_core_status_t HSP_CORE_OUTPUT_Enable(hsp_engine_context_t *hmw);
hsp_core_status_t HSP_CORE_OUTPUT_Disable(hsp_engine_context_t *hmw);
uint32_t HSP_CORE_OUTPUT_IsEnabled(const hsp_engine_context_t *hmw);

/**
  * @}
  */

/** @defgroup HSP_CORE_Exported_Functions_Group3 HSP Smart Clocking Management
  * @{
  */
hsp_core_status_t HSP_CORE_EnableSmartClocking(hsp_engine_context_t *hmw, hsp_core_smart_clocking_t clock);
hsp_core_status_t HSP_CORE_DisableSmartClocking(hsp_engine_context_t *hmw, hsp_core_smart_clocking_t clock);
hsp_core_smart_clocking_status_t HSP_CORE_GetSmartClockingStatus(const hsp_engine_context_t *hmw,
                                                                 hsp_core_smart_clocking_t clock);

/**
  * @}
  */

/** @defgroup HSP_CORE_Exported_Functions_Group4 HSP Protection
  * @{
  */
hsp_core_status_t HSP_CORE_Lock(hsp_engine_context_t *hmw);

/**
  * @}
  */

/** @defgroup HSP_CORE_Exported_Functions_Group10 Generic and common functions
  * @{
  */
hsp_core_state_t HSP_CORE_GetState(const hsp_engine_context_t *hmw);
void *HSP_CORE_GetBRAMResources(const hsp_engine_context_t *hmw);

/**
  * @}
  */

/** @defgroup HSP_CORE_Exported_Functions_Group20  HSP Engine Callback functions
  * @{
  */
void HSP_CORE_ErrorCallback(void *hmw, uint32_t hw_status, uint32_t fw_error_code, uint32_t spe_error_inf);

hsp_core_status_t HSP_CORE_RegisterErrorCallback(hsp_engine_context_t *hmw, p_hsp_engine_error_cb_t p_callback);

/**
  * @}
  */

#if defined(USE_HSP_PLUGIN) && (USE_HSP_PLUGIN == 1)
/** @defgroup HSP_CORE_Exported_Functions_Group21 HSP Application Plugins Selection Management
  * @{
  */
void HSP_CORE_GetPluginsHook(hsp_engine_context_t *hmw,
                             hsp_plugin_register_t **a_hsp_plugins,
                             uint32_t *hsp_plugin_nb);
/**
  * @}
  */
#endif /* USE_HSP_PLUGIN */

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

#endif /* HSP_CORE_H */
