/**
  ******************************************************************************
  * @file    hsp_monitoring.c
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
#include "hsp_monitoring.h"
#include "hsp_hw_if.h"

/** @addtogroup HSP_ENGINE
  * @{
  */

/** @addtogroup HSP_MONITORING
  * @{
  */

/** @addtogroup HSP_MONITORING_Exported_Functions
  * @{
  */

/** @addtogroup HSP_MONITORING_Exported_Functions_Group1
  * @{
  */
#if defined(USE_HSP_ENGINE_TCU_IT) && (USE_HSP_ENGINE_TCU_IT == 1U)
/**
  * @brief Configure and start the monitoring of a Task in IT mode.
  * @param  hmw      Pointer to a hsp_engine_context_t.
  * @param  tcu_id   ID of the Task Comparator Unit.
  * @param  task_id  Task ID to monitor.
  * @retval HSP_CORE_OK     Operation successful.
  * @retval HSP_CORE_ERROR  Operation failed.
  */
hsp_core_status_t HSP_MONITOR_StartTaskComparator(const hsp_engine_context_t *hmw, uint32_t tcu_id, uint32_t task_id)
{
  HSP_ASSERT_DBG_PARAM((hmw != NULL));

  HSP_ASSERT_DBG_STATE(hmw->global_state, (uint32_t)HSP_CORE_STATE_IDLE);

  if (HSP_HW_IF_StartTaskComparator_IT(&(hmw->hw_if_ctx), tcu_id, task_id) != HSP_IF_OK)
  {
    return HSP_CORE_ERROR;
  }

  return HSP_CORE_OK;
}

/**
  * @brief Stop the monitoring of a Task.
  * @param  hmw     Pointer to a hsp_engine_context_t.
  * @param  tcu_id  ID of the Task Comparator Unit.
  * @retval HSP_CORE_OK     Operation successful.
  * @retval HSP_CORE_ERROR  Operation failed.
  */
hsp_core_status_t HSP_MONITOR_StopTaskComparator(const hsp_engine_context_t *hmw, uint32_t tcu_id)
{
  HSP_ASSERT_DBG_PARAM((hmw != NULL));

  HSP_ASSERT_DBG_STATE(hmw->global_state, (uint32_t)HSP_CORE_STATE_IDLE);

  if (HSP_HW_IF_StopTaskComparator(&(hmw->hw_if_ctx), tcu_id) != HSP_IF_OK)
  {
    return HSP_CORE_ERROR;
  }

  return HSP_CORE_OK;
}
#endif /* USE_HSP_ENGINE_TCU_IT */

/**
  * @}
  */

/** @addtogroup HSP_MONITORING_Exported_Functions_Group2
  * @{
  */
#if defined(USE_HSP_ENGINE_TIMESTAMPCAPTURE) && (USE_HSP_ENGINE_TIMESTAMPCAPTURE == 1U)
/**
  * @brief  Enable the Timestamp capture.
  * @param  hmw   Pointer to a @ref hsp_engine_context_t.
  * @param  mode  Mode of capture.
  * @retval HSP_CORE_OK     Operation successful.
  * @retval HSP_CORE_ERROR  Operation failed.
  */
hsp_core_status_t HSP_MONITOR_SetConfigTimestampCapture(const hsp_engine_context_t *hmw,
                                                        const hsp_monitor_tsc_config_t *p_config)
{
  hsp_hw_if_ctx_t *p_if_ctx;

  HSP_ASSERT_DBG_PARAM(hmw != NULL);
  HSP_ASSERT_DBG_PARAM(p_config != NULL);

  p_if_ctx = (hsp_hw_if_ctx_t *) & (hmw->hw_if_ctx);

  /* Check and register uninitialized TSC callbacks */
  if (HSP_HW_IF_TSC_IsCompleteCallback(p_if_ctx) != HSP_IF_OK)
  {
    HSP_HW_IF_RegisterTSC_CompleteCallback(p_if_ctx, HSP_MONITOR_TSC_CompleteCallback);
  }

  if (HSP_HW_IF_TSC_IsErrorCallback(p_if_ctx) != HSP_IF_OK)
  {
    HSP_HW_IF_RegisterTSC_ErrorCallback(p_if_ctx, HSP_MONITOR_TSC_ErrorCallback);
  }

  /* Set the TSC configuration */
  if (HSP_HW_IF_TSC_SetConfig(p_if_ctx, p_config->prescaler, p_config->task_filter) != HSP_IF_OK)
  {
    return HSP_CORE_ERROR;
  }

  return HSP_CORE_OK;
}

/**
  * @brief  Start the Timestamp capture.
  * @param  hmw   Pointer to a @ref hsp_engine_context_t.
  * @param  mode  Mode of capture.
  * @param  p_output_buffer  Pointer to the output buffer.
  * @param  output_buffer_size  Size of the output buffer.
  * @retval HSP_CORE_OK     Operation successful.
  * @retval HSP_CORE_ERROR  Operation failed.
  */
hsp_core_status_t HSP_MONITOR_StartTimestampCapture(hsp_engine_context_t *hmw, hsp_monitor_tsc_mode_t mode,
                                                    void *p_output_buffer, uint32_t output_buffer_size)
{
  HSP_ASSERT_DBG_PARAM(hmw != NULL);

  if (HSP_HW_IF_DMA_Start(hmw->hw_if_ctx.hdma_tsc, (uint32_t)HSP_HW_IF_TSC_GetBufferAddress(&(hmw->hw_if_ctx)),
                          (uint32_t)p_output_buffer, output_buffer_size) != HSP_IF_OK)
  {
    return HSP_CORE_ERROR;
  }

  if (HSP_HW_IF_TSC_Start(&(hmw->hw_if_ctx), (uint32_t)mode) != HSP_IF_OK)
  {
    return HSP_CORE_ERROR;
  }

  return HSP_CORE_OK;
}

/**
  * @brief  Stop the Timestamp capture.
  * @param  hmw   Pointer to a @ref hsp_engine_context_t.
  * @retval HSP_CORE_OK     Operation successful.
  * @retval HSP_CORE_ERROR  Operation failed.
  */
hsp_core_status_t HSP_MONITOR_StopTimestampCapture(const hsp_engine_context_t *hmw)
{
  HSP_ASSERT_DBG_PARAM(hmw != NULL);

  if (HSP_HW_IF_TSC_Stop(&(hmw->hw_if_ctx)) != HSP_IF_OK)
  {
    return HSP_CORE_ERROR;
  }

  return HSP_CORE_OK;
}

/**
  * @brief  Get the Timestamp Capture buffer address.
  * @param  hmw   Pointer to a @ref hsp_engine_context_t.
  * @retval Buffer address.
  */
volatile const uint32_t *HSP_MONITOR_GetTimestampCaptureBufferAddress(const hsp_engine_context_t *hmw)
{
  HSP_ASSERT_DBG_PARAM(hmw != NULL);

  return HSP_HW_IF_TSC_GetBufferAddress(&(hmw->hw_if_ctx));
}

#endif /* USE_HSP_ENGINE_TIMESTAMPCAPTURE */

/**
  * @}
  */

/** @addtogroup HSP_MONITORING_Exported_Functions_Group4
  * @{
  */
/**
  * @brief Get HSP Performance counter.
  * @param  hmw  Pointer to a @ref hsp_engine_context_t.
  * @return  counter value
  */
uint32_t HSP_MONITOR_GetPerformanceCounter(const hsp_engine_context_t *hmw)
{
  HSP_ASSERT_DBG_PARAM((hmw != NULL));

  return *(hmw->hbram.p_perf_monitor_counter);
}

/**
  * @}
  */

/** @addtogroup HSP_MONITORING_Exported_Functions_Group5
  * @{
  */
hsp_core_status_t HSP_MONITOR_SetBreakMultiOutput(hsp_engine_context_t *hmw,
                                                  const uint32_t *p_config_array, uint32_t config_array_size)
{
  HSP_ASSERT_DBG_PARAM((hmw != NULL));
  HSP_ASSERT_DBG_PARAM((p_config_array != NULL));

  HSP_ASSERT_DBG_STATE(hmw->global_state, (uint32_t)HSP_CORE_STATE_IDLE);

  if (HSP_HW_IF_BREAK_SetMultiOutput(&(hmw->hw_if_ctx), p_config_array, config_array_size) != HSP_IF_OK)
  {
    return HSP_CORE_ERROR;
  }

  return HSP_CORE_OK;
}

hsp_core_status_t HSP_MONITOR_SetDebugBreakEvents(hsp_engine_context_t *hmw, uint32_t break_events)
{
  HSP_ASSERT_DBG_PARAM((hmw != NULL));

  HSP_ASSERT_DBG_STATE(hmw->global_state, (uint32_t)HSP_CORE_STATE_IDLE);

  if (HSP_HW_IF_BREAK_SetDebugEvents(&(hmw->hw_if_ctx), break_events) != HSP_IF_OK)
  {
    return HSP_CORE_ERROR;
  }

  return HSP_CORE_OK;
}

hsp_core_status_t HSP_MONITOR_ResumeDebugBreakEvents(hsp_engine_context_t *hmw)
{
  HSP_ASSERT_DBG_PARAM((hmw != NULL));

  HSP_ASSERT_DBG_STATE(hmw->global_state, (uint32_t)HSP_CORE_STATE_IDLE);

  if (HSP_HW_IF_BREAK_ResumeDebugEvents(&(hmw->hw_if_ctx)) != HSP_IF_OK)
  {
    return HSP_CORE_ERROR;
  }

  return HSP_CORE_OK;
}

/**
  * @}
  */

/** @addtogroup HSP_MONITORING_Exported_Functions_Group6
  * @{
  */
#if defined(USE_HSP_ENGINE_TCU_IT) && (USE_HSP_ENGINE_TCU_IT == 1U)
hsp_core_status_t HSP_MONITOR_RegisterTCU_TaskStartedCallback(hsp_engine_context_t *hmw,
                                                              p_hsp_engine_one_param_cb_t p_callback)
{
  HSP_ASSERT_DBG_PARAM((hmw != NULL));

  if (HSP_HW_IF_RegisterTCU_TaskStartedCallback(&(hmw->hw_if_ctx), p_callback) != HSP_IF_OK)
  {
    return HSP_CORE_ERROR;
  }

  return HSP_CORE_OK;
}

hsp_core_status_t HSP_MONITOR_RegisterTCU_TaskEndedCallback(hsp_engine_context_t *hmw,
                                                            p_hsp_engine_one_param_cb_t p_callback)
{
  HSP_ASSERT_DBG_PARAM((hmw != NULL));

  if (HSP_HW_IF_RegisterTCU_TaskEndedCallback(&(hmw->hw_if_ctx), p_callback) != HSP_IF_OK)
  {
    return HSP_CORE_ERROR;
  }

  return HSP_CORE_OK;
}
#endif /* USE_HSP_ENGINE_TCU_IT */

#if defined(USE_HSP_ENGINE_TIMESTAMPCAPTURE) && (USE_HSP_ENGINE_TIMESTAMPCAPTURE == 1U)
/**
  * @brief  TimeStamp Capture Complete callback.
  * @param  hmw  Pointer to a @ref hsp_engine_context_t.
  */
__WEAK void HSP_MONITOR_TSC_CompleteCallback(void *hmw)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(hmw);

  /* NOTE: This function must not be modified. When the callback is needed,
           function HSP_MONITOR_TSC_CompleteCallback must be implemented in the user file.
   */
}

/**
  * @brief  TimeStamp Capture Error callback.
  * @param  hmw  Pointer to a @ref hsp_engine_context_t.
  */
__WEAK void HSP_MONITOR_TSC_ErrorCallback(void *hmw)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(hmw);

  /* NOTE: This function must not be modified. When the callback is needed,
           function HSP_MONITOR_TSC_ErrorCallback must be implemented in the user file.
   */
}

hsp_core_status_t HSP_MONITOR_RegisterTSC_CompleteCallback(hsp_engine_context_t *hmw,
                                                           p_hsp_engine_cb_t p_callback)
{
  HSP_ASSERT_DBG_PARAM((hmw != NULL));

  if (HSP_HW_IF_RegisterTSC_CompleteCallback(&(hmw->hw_if_ctx), p_callback) != HSP_IF_OK)
  {
    return HSP_CORE_ERROR;
  }

  return HSP_CORE_OK;
}

hsp_core_status_t HSP_MONITOR_RegisterTSC_ErrorCallback(hsp_engine_context_t *hmw,
                                                        p_hsp_engine_cb_t p_callback)
{
  HSP_ASSERT_DBG_PARAM((hmw != NULL));

  if (HSP_HW_IF_RegisterTSC_ErrorCallback(&(hmw->hw_if_ctx), p_callback) != HSP_IF_OK)
  {
    return HSP_CORE_ERROR;
  }

  return HSP_CORE_OK;
}
#endif /* USE_HSP_ENGINE_TIMESTAMPCAPTURE */

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
