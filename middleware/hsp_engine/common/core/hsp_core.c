/**
  ******************************************************************************
  * @file    hsp_core.c
  * @brief   This file implements the HSP Core functions.
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

/* Includes ------------------------------------------------------------------*/
#include "hsp_core.h"
#include "hsp_bram_if.h"
#include "hsp_fw_ram.h"
#if defined(USE_HSP_PROCLIST) && (USE_HSP_PROCLIST == 1)
#include "hsp_proclist.h"
#endif /* USE_HSP_PROCLIST */

/** @addtogroup HSP_ENGINE
  * @{
  */

/** @defgroup HSP_Engine_Configuration_Table HSP Engine Configuration Table
  * @{
  # Configuration inside the HSP Engine middleware

Software configuration defined in hsp_conf.h:
Prepocessor flags                      | Default value | Comment
-------------------------------------- | ------------- | ------------------------------------------------
USE_HSP_MODULES_DIRECT_LIB             |       1       | Enable HSP Engine Direct Command module
USE_HSP_MODULES_DSP_LIB                |       0       | Enable HSP Engine DSP module (ARM-like API)
USE_HSP_MODULES_CNN_LIB                |       0       | Enable HSP Engine CNN module
USE_HSP_MODULES_PROCLIST_COMPLEX       |       0       | Enable HSP Engine Proclist Complex module
USE_HSP_MODULES_PROCLIST_CONDITIONAL   |       0       | Enable HSP Engine Proclist Conditional module
USE_HSP_MODULES_PROCLIST_FILTER        |       0       | Enable HSP Engine Proclist Filter module
USE_HSP_MODULES_PROCLIST_MATRIX        |       0       | Enable HSP Engine Proclist Matrix module
USE_HSP_MODULES_PROCLIST_SCALAR        |       0       | Enable HSP Engine Proclist Scalar module
USE_HSP_MODULES_PROCLIST_TRANSFORM     |       0       | Enable HSP Engine Proclist Transform module
USE_HSP_MODULES_PROCLIST_VECTOR        |       0       | Enable HSP Engine Proclist Vector module
USE_HSP_MEMCPY                         |       1       | Enable HSP Engine memcopy function
USE_HSP_ENGINE_STREAM_BUFFER           |       0       | Enable HSP Engine STREAM Buffer feature
USE_HSP_ENGINE_TIMESTAMP_CAPTURE       |       0       | Enable HSP Engine Timestamp Capture feature
ENABLE_HSP_PERFORMANCE_MONITOR         |       0       | Enable the HSP Performance Monitor counter
HSP_BRAM_AI_SIZE                       |       0       | Configure the BRAMAB size reserved for CNN processing
USE_HSP_PLUGIN                         |       0       | Enable the HSP Engine Plugin feature

Software configuration defined in preprocessor environment:
Prepocessor flags              |   Default value   | Comment
------------------------------ | ----------------- | ------------------------------------------------
USE_ASSERT_DBG_PARAM           |    Not defined    | Enable check param for MW
USE_ASSERT_DBG_STATE           |    Not defined    | Enable check state for MW

  */

/**
  * @}
  */

/** @addtogroup HSP_CORE
  * @{
  */

/** @addtogroup HSP_CORE_Manager
  * @{
  */

/** @defgroup HSP_CORE_Init_Private_Functions HSP Core Private Functions
  * @{
  */
static hsp_core_status_t HSP_CORE_LoadFW(hsp_engine_context_t *hmw);
#if defined(USE_HSP_PLUGIN) && (USE_HSP_PLUGIN == 1)
static hsp_core_status_t HSP_CORE_LoadPlugins(hsp_engine_context_t *hmw);
#endif /* USE_HSP_PLUGIN */

/**
  * @}
  */

/* Exported Functions --------------------------------------------------------*/
/** @addtogroup HSP_CORE_Exported_Functions
  * @{
  */

/** @defgroup HSP_CORE_Exported_Functions_Group1 HSP Init functions
  * @{
  */
/**
  * @brief  Initialize the MW HSP Engine according to the associated driver.
  * @param  hmw       Pointer to a @ref hsp_engine_context_t.
  * @param  p_hw_ctx  Pointer to a @ref hsp_engine_hw_context_t.
  * @retval HSP_CORE_OK            Operation successful.
  * @retval HSP_CORE_INVALID_PARAM invalid parameter.
  * @retval HSP_CORE_ERROR         Operation failed.
  */
hsp_core_status_t HSP_CORE_Init(hsp_engine_context_t *hmw, const hsp_engine_hw_context_t *p_hw_ctx)
{
  HSP_ASSERT_DBG_PARAM((hmw != NULL));
  HSP_ASSERT_DBG_PARAM((p_hw_ctx != NULL));
  HSP_ASSERT_DBG_PARAM((p_hw_ctx->hhsp_driver != NULL));

#if defined(USE_HSP_CHECK_PARAM) && (USE_HSP_CHECK_PARAM == 1)
  /* Check whether the HSP handle is valid */
  if (hmw == NULL)
  {
    return HSP_CORE_INVALID_PARAM;
  }

  if (p_hw_ctx == NULL)
  {
    return HSP_CORE_INVALID_PARAM;
  }

  if (p_hw_ctx->hhsp_driver == NULL)
  {
    return HSP_CORE_INVALID_PARAM;
  }
#endif /* USE_HSP_CHECK_PARAM */

  /* Link the HSP Driver to the MW Context -----------------------------------*/
  hmw->hdriver = p_hw_ctx->hhsp_driver;

  /* Interfaces Initialization -----------------------------------------------*/
#if defined(USE_HAL_HSP_CUBE1_LEGACY)
  HSP_HW_IF_Init(&(hmw->hw_if_ctx), p_hw_ctx->hhsp_driver, hmw, 0U);
#else
  HSP_HW_IF_Init(&(hmw->hw_if_ctx), p_hw_ctx->hhsp_driver, hmw);
#if defined(USE_HSP_ENGINE_TIMESTAMPCAPTURE) && (USE_HSP_ENGINE_TIMESTAMPCAPTURE == 1U)
  if (HSP_HW_IF_TSC_SetDMA(&(hmw->hw_if_ctx), p_hw_ctx->hdma_tsc) != HSP_IF_OK)
  {
    return HSP_CORE_ERROR;
  }
#endif /* USE_HSP_ENGINE_TIMESTAMPCAPTURE */
  HSP_HW_IF_GetDCMDHWInfo(&(hmw->hw_if_ctx),
                          &(hmw->p_send_dcmdid), &(hmw->p_send_dcmd_data_ptr),
                          &(hmw->p_send_parameter_data));
#endif /* USE_HAL_HSP_CUBE1_LEGACY */

  /* Initialize the BRAM memory interface */
  if (HSP_BRAM_IF_Init(&(hmw->hbram), p_hw_ctx->hhsp_driver) != HSP_IF_OK)
  {
    return HSP_CORE_ERROR;
  }

  /* Load the Firmware & Plugin ----------------------------------------------*/
  /* Call the private function to load Firmware */
  if (HSP_CORE_LoadFW(hmw) != HSP_CORE_OK)
  {
    return HSP_CORE_ERROR;
  }

#if defined(USE_HSP_PLUGIN) && (USE_HSP_PLUGIN == 1)
  /* Call the weak function to load Plugins */
  if (HSP_CORE_LoadPlugins(hmw) != HSP_CORE_OK)
  {
    return HSP_CORE_ERROR;
  }
#endif /* USE_HSP_PLUGIN */

  /* Change HSP Middleware state */
  hmw->global_state = HSP_CORE_STATE_READY;

  /* Boot the HSP */
  if (HSP_HW_IF_Boot(&(hmw->hw_if_ctx), ENABLE_HSP_PERFORMANCE_MONITOR) != HSP_IF_OK)
  {
    return HSP_CORE_ERROR;
  }

  /* Register Default Callbacks */
  HSP_HW_IF_RegisterErrorCallback(&(hmw->hw_if_ctx), HSP_CORE_ErrorCallback);

  /* Change HSP Middleware state */
  hmw->global_state = HSP_CORE_STATE_IDLE;

  /* Call the weak function to allocate BRAM */
  if (HSP_BRAM_AllocateHook(hmw) != 0U)
  {
    return HSP_CORE_ERROR;
  }

  /* Call the weak function to record and configure all Processing lists */
#if defined(USE_HSP_PROCLIST) && (USE_HSP_PROCLIST == 1)
  if (HSP_SEQ_RecordPLHook(hmw) != 0U)
  {
    return HSP_CORE_ERROR;
  }
#endif /* USE_HSP_PROCLIST */

  return HSP_CORE_OK;
}

/**
  * @brief  DeInitialize the MW HSP Engine.
  * @param  hmw  Pointer to a @ref hsp_engine_context_t.
  */
void HSP_CORE_DeInit(hsp_engine_context_t *hmw)
{
  HSP_ASSERT_DBG_PARAM((hmw != NULL));

  /* DeInit the Hardware interface */
  HSP_HW_IF_DeInit(&(hmw->hw_if_ctx));

  /* DeInit the BRAM Memory interface */
  HSP_BRAM_IF_DeInit(&(hmw->hbram));
}

/**
  * @}
  */

/** @addtogroup HSP_CORE_Exported_Functions_Group2
  * @{
  */
/**
  * @brief Configure a TRGO.
  * @param  hmw  Pointer to a @ref hsp_engine_context_t.
  * @param  trgo_id  TRGO ID
  * @param  source   Trigger source
  * @note literals are defined in hsp_if_conf.h
  * @retval HSP_CORE_OK     Operation successful.
  * @retval HSP_CORE_ERROR  Operation failed.
  */
hsp_core_status_t HSP_CORE_OUTPUT_SetConfig(hsp_engine_context_t *hmw, uint32_t trgo_id, uint32_t source)
{
  HSP_ASSERT_DBG_PARAM((hmw != NULL));
  HSP_ASSERT_DBG_STATE(hmw->global_state, (uint32_t)HSP_CORE_STATE_IDLE);

  if (HSP_HW_IF_OUTPUT_SetConfig(&(hmw->hw_if_ctx), trgo_id, source) != HSP_IF_OK)
  {
    return HSP_CORE_ERROR;
  }

  return HSP_CORE_OK;
}

/**
  * @brief Enable the HSP Outputs.
  * @param  hmw  Pointer to a @ref hsp_engine_context_t.
  * @retval HSP_CORE_OK     Operation successful.
  * @retval HSP_CORE_ERROR  Operation failed.
  */
hsp_core_status_t HSP_CORE_OUTPUT_Enable(hsp_engine_context_t *hmw)
{
  HSP_ASSERT_DBG_PARAM((hmw != NULL));
  HSP_ASSERT_DBG_STATE(hmw->global_state, (uint32_t)HSP_CORE_STATE_IDLE);

  if (HSP_HW_IF_OUTPUT_Enable(&(hmw->hw_if_ctx)) != HSP_IF_OK)
  {
    return HSP_CORE_ERROR;
  }

  return HSP_CORE_OK;
}

/**
  * @brief Disable the HSP Outputs.
  * @param  hmw  Pointer to a @ref hsp_engine_context_t.
  * @retval HSP_CORE_OK     Operation successful.
  * @retval HSP_CORE_ERROR  Operation failed.
  */
hsp_core_status_t HSP_CORE_OUTPUT_Disable(hsp_engine_context_t *hmw)
{
  HSP_ASSERT_DBG_PARAM((hmw != NULL));
  HSP_ASSERT_DBG_STATE(hmw->global_state, (uint32_t)HSP_CORE_STATE_IDLE);

  if (HSP_HW_IF_OUTPUT_Disable(&(hmw->hw_if_ctx)) != HSP_IF_OK)
  {
    return HSP_CORE_ERROR;
  }

  return HSP_CORE_OK;
}

/**
  * @brief Get the HSP Outputs enabling status.
  * @param  hmw  Pointer to a @ref hsp_engine_context_t.
  * @retval 0U  TRGO Disabled.
  * @retval > 0U TRGO Enabled.
  */
uint32_t HSP_CORE_OUTPUT_IsEnabled(const hsp_engine_context_t *hmw)
{
  HSP_ASSERT_DBG_PARAM((hmw != NULL));

  return (uint32_t)HSP_HW_IF_OUTPUT_IsEnabled(&(hmw->hw_if_ctx));
}

/**
  * @}
  */

/** @addtogroup HSP_CORE_Exported_Functions_Group3
  * @{
  */
/**
  * @brief Enable the SmartClocking of HSP block.
  * @param  hmw    Pointer to a @ref hsp_engine_context_t.
  * @param  clock  Block clock
  * @retval HSP_CORE_OK     Operation successful.
  * @retval HSP_CORE_ERROR  Operation failed.
  */
hsp_core_status_t HSP_CORE_EnableSmartClocking(hsp_engine_context_t *hmw, hsp_core_smart_clocking_t clock)
{
  HSP_ASSERT_DBG_PARAM((hmw != NULL));

  HSP_ASSERT_DBG_STATE(hmw->global_state, (uint32_t)HSP_CORE_STATE_IDLE);

  if (HSP_HW_IF_EnableSmartClocking(&(hmw->hw_if_ctx), (uint32_t)clock) != HSP_IF_OK)
  {
    return HSP_CORE_ERROR;
  }

  return HSP_CORE_OK;
}

/**
  * @brief Disable the SmartClocking of HSP block.
  * @param  hmw    Pointer to a @ref hsp_engine_context_t.
  * @param  clock  Block clock
  * @retval HSP_CORE_OK     Operation successful.
  * @retval HSP_CORE_ERROR  Operation failed.
  */
hsp_core_status_t HSP_CORE_DisableSmartClocking(hsp_engine_context_t *hmw, hsp_core_smart_clocking_t clock)
{
  HSP_ASSERT_DBG_PARAM((hmw != NULL));

  HSP_ASSERT_DBG_STATE(hmw->global_state, (uint32_t)HSP_CORE_STATE_IDLE);

  if (HSP_HW_IF_DisableSmartClocking(&(hmw->hw_if_ctx), (uint32_t)clock) != HSP_IF_OK)
  {
    return HSP_CORE_ERROR;
  }

  return HSP_CORE_OK;
}

/**
  * @brief Get the SmartClocking of HSP block status.
  * @param  hmw  Pointer to a @ref hsp_engine_context_t.
  * @param  clock  Block clock.
  * @retval HSP_CORE_SMART_CLOCKING_DISABLED  SmartClocking is disabled.
  * @retval HSP_CORE_SMART_CLOCKING_ENABLED   SmartClocking is enabled.
  */
hsp_core_smart_clocking_status_t HSP_CORE_GetSmartClockingStatus(const hsp_engine_context_t *hmw,
                                                                 hsp_core_smart_clocking_t clock)
{
  HSP_ASSERT_DBG_PARAM((hmw != NULL));

  return ((HSP_HW_IF_IsEnabledSmartClocking(&(hmw->hw_if_ctx), (uint32_t)clock) == 0U) ?
          HSP_CORE_SMART_CLOCKING_DISABLED : HSP_CORE_SMART_CLOCKING_ENABLED);
}

/**
  * @}
 */

/** @addtogroup HSP_CORE_Exported_Functions_Group4
  * @{
  */
/**
  * @brief Lock the HSP configuration.
  * @param  hmw  Pointer to a @ref hsp_engine_context_t.
  * @retval HSP_CORE_OK     Operation successful.
  * @retval HSP_CORE_ERROR  Operation failed.
  */
hsp_core_status_t HSP_CORE_Lock(hsp_engine_context_t *hmw)
{
  HSP_ASSERT_DBG_PARAM((hmw != NULL));
  HSP_ASSERT_DBG_STATE(hmw->global_state, (uint32_t)HSP_CORE_STATE_IDLE);

  if (HSP_HW_IF_Lock(&(hmw->hw_if_ctx)) != HSP_IF_OK)
  {
    return HSP_CORE_ERROR;
  }

  return HSP_CORE_OK;
}

/**
  * @}
  */

/** @addtogroup HSP_CORE_Exported_Functions_Group10
  * @{
A set of functions allowing to retrieve middleware state and BRAM resources information.
 - HSP_CORE_GetState()         : return the HSP Engine state.
 - HSP_CORE_GetBRAMResources() : return the HSP Engine BRAM resources pointer.
  */
/**
  * @brief  Return the HSP Engine state.
  * @param  hmw  Pointer to a @ref hsp_engine_context_t.
  * @return hsp_core_state_t enum value.
  */
hsp_core_state_t HSP_CORE_GetState(const hsp_engine_context_t *hmw)
{
  HSP_ASSERT_DBG_PARAM((hmw != NULL));

  return hmw->global_state;
}

/**
  * @brief  Return the HSP Engine BRAM resources.
  * @param  hmw  Pointer to a @ref hsp_engine_context_t.
  * @return Pointer to the BRAM resources.
  */
void *HSP_CORE_GetBRAMResources(const hsp_engine_context_t *hmw)
{
  HSP_ASSERT_DBG_PARAM((hmw != NULL));

  return hmw->p_bram_resources;
}

/**
  * @}
  */

/** @addtogroup HSP_CORE_Exported_Functions_Group20
  * @{
  */
/**
  * @brief  Error callback.
  * @param  hmw  Pointer to a @ref hsp_engine_context_t.
  * @param  hw_status  HSP Hardwre status.
  * @param  fw_error_code  FW Error Code value.
  * @param  spe_error_inf  SPE Error information value.
  */
__WEAK void HSP_CORE_ErrorCallback(void *hmw, uint32_t hw_status, uint32_t fw_error_code, uint32_t spe_error_inf)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(hmw);
  UNUSED(hw_status);
  UNUSED(fw_error_code);
  UNUSED(spe_error_inf);

  /* NOTE: This function must not be modified. When the callback is needed,
           function HSP_CORE_ErrorCallback must be implemented in the user file.
   */
}

/**
  * @brief  Register a User HSP callback for Error interrupt.
  * @param  hmw  Pointer to a @ref hsp_engine_context_t.
  * @param  p_callback  Pointer to the callback function.
  * @retval HSP_CORE_OK     Operation successful.
  * @retval HSP_CORE_ERROR  Operation failed.
  */
hsp_core_status_t HSP_CORE_RegisterErrorCallback(hsp_engine_context_t *hmw, p_hsp_engine_error_cb_t p_callback)
{
  HSP_ASSERT_DBG_PARAM((hmw != NULL));

  if (HSP_HW_IF_RegisterErrorCallback(&(hmw->hw_if_ctx), p_callback) != HSP_IF_OK)
  {
    return HSP_CORE_ERROR;
  }

  return HSP_CORE_OK;
}

/**
  * @}
  */

/** @addtogroup HSP_CORE_Init_Private_Functions
  * @{
  */
/**
  * @brief  Load the HSP Firmware.
  * @param  hmw  Pointer to a @ref hsp_engine_context_t.
  * @retval HSP_CORE_OK     Operation successful.
  * @retval HSP_CORE_BUSY   Wrong state
  * @retval HSP_CORE_ERROR  Operation failed.
  */
static hsp_core_status_t HSP_CORE_LoadFW(hsp_engine_context_t *hmw)
{
  HSP_ASSERT_DBG_PARAM((hmw != NULL));
  HSP_ASSERT_DBG_STATE(hmw->global_state, (uint32_t)HSP_CORE_STATE_RESET);

  if (HSP_HW_IF_LoadFW(&(hmw->hw_if_ctx), hsp_fw_getcram(), hsp_fw_getdram()) != HSP_IF_OK)
  {
    return HSP_CORE_ERROR;
  }

  HSP_CHECK_UPDATE_STATE(hmw, global_state, HSP_CORE_STATE_RESET, HSP_CORE_STATE_FW_LOADED);
  return HSP_CORE_OK;
}

#if defined(USE_HSP_PLUGIN) && (USE_HSP_PLUGIN == 1)
/**
  * @brief  Load the HSP Plugins.
  * @param  hmw  Pointer to a @ref hsp_engine_context_t.
  * @retval HSP_CORE_OK     Operation successful.
  * @retval HSP_CORE_ERROR  Operation failed.
  */
static hsp_core_status_t HSP_CORE_LoadPlugins(hsp_engine_context_t *hmw)
{
  hsp_plugin_register_t *a_hsp_plugins = NULL;
  uint32_t hsp_plugin_nb = 0U;
  HSP_ASSERT_DBG_PARAM((hmw != NULL));

  /* Call the weak function to the array of plugins to load */
  HSP_CORE_GetPluginsHook(hmw, &a_hsp_plugins, &hsp_plugin_nb);

  /* Load a set of Plugins */
  for (uint32_t id = 0UL; id < hsp_plugin_nb; id++)
  {
    const hsp_plugin_fw_descriptor_t *p_descriptor = a_hsp_plugins[id](id);

    if (HSP_HW_IF_LoadPlugin(hmw->hdriver, p_descriptor->p_binary, p_descriptor->size_byte) != HSP_IF_OK)
    {
      return HSP_CORE_ERROR;
    }
  }

  return HSP_CORE_OK;
}

/**
  * @brief Get the array of plugins to load and the number of plugins.
  * @param  hmw  Pointer to a @ref hsp_engine_context_t.
  * @param  a_hsp_plugins  Pointer to the array of plugins.
  * @param  hsp_plugin_nb  Pointer to the number of plugins.
  * @return error value (0U - no error)
  */
__weak void HSP_CORE_GetPluginsHook(hsp_engine_context_t *hmw, hsp_plugin_register_t **a_hsp_plugins,
                                    uint32_t *hsp_plugin_nb)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(hmw);

  *a_hsp_plugins = NULL;
  *hsp_plugin_nb = 0U;

  /* NOTE: This function must not be modified.
           The function HSP_CORE_GetPluginsHook must be implemented in the application file.
   */
}
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

/**
  * @}
  */
