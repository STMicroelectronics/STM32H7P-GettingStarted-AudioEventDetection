/**
  ******************************************************************************
  * @file    hsp_proclist.c
  * @brief   This file implements the functions for the proclist management
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
#include "hsp_proclist.h"
#include "hsp_hw_if.h"

/** @addtogroup HSP_ENGINE
  * @{
  */

/** @addtogroup HSP_PROCLIST
  * @{
  */

/** @addtogroup HSP_PROCLIST_Exported_Functions
  * @{
  */

/** @addtogroup HSP_PROCLIST_Exported_Functions_Group1
  * @{
  */
/**
  * @brief Start the record of a processing list.
  * @param hmw    Pointer to a @ref hsp_engine_context_t.
  * @param pl_id  ID of the new processing list.
  * @retval HSP_CORE_OK     Operation successful.
  * @retval HSP_CORE_BUSY   Wrong state.
  * @retval HSP_CORE_ERROR  Operation failed.
  */
hsp_core_status_t HSP_SEQ_StartRecordPL(hsp_engine_context_t *hmw, uint32_t pl_id)
{
  HSP_ASSERT_DBG_PARAM((hmw != NULL));
  HSP_CHECK_UPDATE_STATE(hmw, global_state, HSP_CORE_STATE_IDLE, HSP_CORE_STATE_PROCLIST_RECORDING);

  if (HSP_HW_IF_SEQ_StartRecord(&(hmw->hw_if_ctx), pl_id) != HSP_IF_OK)
  {
    return HSP_CORE_ERROR;
  }

  return HSP_CORE_OK;
}

/**
  * @brief Stop the record of a processing list.
  * @param  hmw  Pointer to a @ref hsp_engine_context_t.
  * @retval HSP_CORE_OK     Operation successful.
  * @retval HSP_CORE_BUSY   Wrong state.
  * @retval HSP_CORE_ERROR  Operation failed.
  */
hsp_core_status_t HSP_SEQ_StopRecordPL(hsp_engine_context_t *hmw)
{
  HSP_ASSERT_DBG_PARAM((hmw != NULL));
  HSP_CHECK_UPDATE_STATE(hmw, global_state, HSP_CORE_STATE_PROCLIST_RECORDING, HSP_CORE_STATE_IDLE);

  if (HSP_HW_IF_SEQ_StopRecord(&(hmw->hw_if_ctx)) != HSP_IF_OK)
  {
    return HSP_CORE_ERROR;
  }

  return HSP_CORE_OK;
}

/**
  * @brief Run a processing list with the lowest priority.
  * @param  hmw        Pointer to a @ref hsp_engine_context_t.
  * @param pl_id       ID of the processing list
  * @param timeout_ms  Timeout in millisecond
  * @retval HSP_CORE_OK     Operation successful.
  * @retval HSP_CORE_ERROR  Operation failed.
  */
hsp_core_status_t HSP_SEQ_RunTask(hsp_engine_context_t *hmw, uint32_t pl_id, uint32_t timeout_ms)
{
  HSP_ASSERT_DBG_PARAM((hmw != NULL));
  HSP_ASSERT_DBG_STATE(hmw->global_state, (uint32_t)HSP_CORE_STATE_IDLE);

  if (HSP_HW_IF_SEQ_RunTask(hmw->hdriver, pl_id, timeout_ms) != HSP_IF_OK)
  {
    return HSP_CORE_ERROR;
  }

  return HSP_CORE_OK;
}

/**
  * @brief Reset (remove) all the processing list in HSP.
  * @param  hmw  Pointer to a @ref hsp_engine_context_t.
  * @retval HSP_CORE_OK     Operation successful.
  * @retval HSP_CORE_ERROR  Operation failed.
  */
hsp_core_status_t HSP_SEQ_ResetPL(hsp_engine_context_t *hmw)
{
  HSP_ASSERT_DBG_PARAM((hmw != NULL));
  HSP_ASSERT_DBG_STATE(hmw->global_state, (uint32_t)HSP_CORE_STATE_IDLE);

  if (HSP_HW_IF_SEQ_ResetPL(&(hmw->hw_if_ctx)) != HSP_IF_OK)
  {
    return HSP_CORE_ERROR;
  }

  return HSP_CORE_OK;
}
/**
  * @}
  */

/** @addtogroup HSP_PROCLIST_Exported_Functions_Group2
  * @{
  */
#if defined(USE_HSP_ENGINE_STREAM_BUFFER) && (USE_HSP_ENGINE_STREAM_BUFFER == 1U)
/* Event configuration -------------------------------------------------------*/
/**
  * @brief Configure a HSP Event with a STREAM Buffer as trigger source.
  * @param  hmw       Pointer to a @ref hsp_engine_context_t.
  * @param  evt_id    HSP Event ID.
  * @param  p_config  Pointer to a hsp_seq_event_stream_buffer_config_t.
  * @retval HSP_CORE_OK     Operation successful.
  * @retval HSP_CORE_ERROR  Operation failed.
  */
hsp_core_status_t HSP_SEQ_EVENT_SetConfig_StreamBuffer(hsp_engine_context_t *hmw, hsp_seq_event_t evt_id,
                                                       const hsp_seq_event_stream_buffer_config_t *p_config)
{
  HSP_ASSERT_DBG_PARAM((hmw != NULL));
  HSP_ASSERT_DBG_PARAM((p_config != NULL));

  HSP_ASSERT_DBG_STATE(hmw->global_state, (uint32_t)HSP_CORE_STATE_IDLE);

  if (HSP_HW_IF_SEQ_EVENT_SetConfig_StreamBuffer(hmw->hdriver, (uint32_t)evt_id,
                                                 p_config->instance, (uint32_t)p_config->direction, (uint32_t)p_config->sync,
                                                 (uint32_t)p_config->evt_sync) != HSP_IF_OK)
  {
    return HSP_CORE_ERROR;
  }

  return HSP_CORE_OK;
}

/**
  * @brief Get the Stream Buffer Address.
  * @param  hmw               Pointer to a @ref hsp_engine_context_t.
  * @param  stream_buffer_id  Stream Buffer ID.
  * @return Stream Buffer Address
  */
volatile uint32_t *HSP_SEQ_STREAM_GetBufferAddress(hsp_engine_context_t *hmw, uint32_t stream_buffer_id)
{
  HSP_ASSERT_DBG_PARAM((hmw != NULL));

  return HSP_HW_IF_SEQ_STREAM_GetBufferAddress(hmw->hdriver, stream_buffer_id);
}

/**
  * @brief Retrieve the Stream Buffer Address from the processing list identifier.
  * @param  hmw    Pointer to a @ref hsp_engine_context_t.
  * @param  pl_id  Processing List identifier.
  * @return Stream Buffer Address or NULL if incorrect processing list identifier.
  */
volatile uint32_t *HSP_SEQ_STREAM_GetBufferAddressFromPLID(hsp_engine_context_t *hmw, uint32_t pl_id)
{
  HSP_ASSERT_DBG_PARAM((hmw != NULL));

  return HSP_HW_IF_SEQ_STREAM_GetBufferAddressFromPLID(hmw->hdriver, pl_id);
}

/**
  * @brief Transmit the Application RX/TX buffer to the MW to link to a STREAM Buffer.
  * @param  hmw               Pointer to a @ref hsp_engine_context_t.
  * @param  stream_buffer_id  Stream Buffer ID.
  * @param  p_buffer          Pointer to the application buffer.
  * @param  buffer_size       Size of the buffer in word.
  * @retval HSP_CORE_OK     Operation successful.
  * @retval HSP_CORE_ERROR  Operation failed.
  */
hsp_core_status_t HSP_SEQ_STREAM_Buffer_Start(hsp_engine_context_t *hmw, uint32_t stream_buffer_id,
                                              const int32_t *p_buffer, uint32_t buffer_size)
{
  HSP_ASSERT_DBG_PARAM((hmw != NULL));
  HSP_ASSERT_DBG_PARAM((p_buffer != NULL));

  HSP_ASSERT_DBG_STATE(hmw->global_state, (uint32_t)HSP_CORE_STATE_IDLE);

  if (HSP_HW_IF_SEQ_STREAM_Buffer_Start(&(hmw->hw_if_ctx), stream_buffer_id, p_buffer, buffer_size) != HSP_IF_OK)
  {
    return HSP_CORE_ERROR;
  }

  return HSP_CORE_OK;
}

/**
  * @brief Enable Integer to Float data conversion for STREAM Buffers.
  * @param  hmw  Pointer to a @ref hsp_engine_context_t.
  * @retval HSP_CORE_OK     Operation successful.
  * @retval HSP_CORE_ERROR  Operation failed.
  */
hsp_core_status_t HSP_SEQ_STREAM_EnableIntToFloat(hsp_engine_context_t *hmw)
{
  HSP_ASSERT_DBG_PARAM((hmw != NULL));

  HSP_ASSERT_DBG_STATE(hmw->global_state, (uint32_t)HSP_CORE_STATE_IDLE);

  if (HSP_HW_IF_SEQ_STREAM_EnableIntToFloat(hmw->hdriver) != HSP_IF_OK)
  {
    return HSP_CORE_ERROR;
  }

  return HSP_CORE_OK;
}

/**
  * @brief Disable Integer to Float data conversion for STREAM Buffers.
  * @param  hmw  Pointer to a @ref hsp_engine_context_t.
  * @retval HSP_CORE_OK     Operation successful.
  * @retval HSP_CORE_ERROR  Operation failed.
  */
hsp_core_status_t HSP_SEQ_STREAM_DisableIntToFloat(hsp_engine_context_t *hmw)
{
  HSP_ASSERT_DBG_PARAM((hmw != NULL));

  HSP_ASSERT_DBG_STATE(hmw->global_state, (uint32_t)HSP_CORE_STATE_IDLE);

  if (HSP_HW_IF_SEQ_STREAM_DisableIntToFloat(hmw->hdriver) != HSP_IF_OK)
  {
    return HSP_CORE_ERROR;
  }

  return HSP_CORE_OK;
}

/**
  * @brief Enable all the STREAM Buffers.
  * @param  hmw  Pointer to a @ref hsp_engine_context_t.
  * @retval HSP_CORE_OK     Operation successful.
  * @retval HSP_CORE_ERROR  Operation failed.
  */
hsp_core_status_t HSP_SEQ_STREAM_Enable(hsp_engine_context_t *hmw)
{
  HSP_ASSERT_DBG_PARAM((hmw != NULL));

  HSP_ASSERT_DBG_STATE(hmw->global_state, (uint32_t)HSP_CORE_STATE_IDLE);

  if (HSP_HW_IF_SEQ_STREAM_Enable(&(hmw->hw_if_ctx)) != HSP_IF_OK)
  {
    return HSP_CORE_ERROR;
  }

  return HSP_CORE_OK;
}

/**
  * @brief Disable all the STREAM Buffers.
  * @param  hmw  Pointer to a @ref hsp_engine_context_t.
  * @retval HSP_CORE_OK     Operation successful.
  * @retval HSP_CORE_ERROR  Operation failed.
  */
hsp_core_status_t HSP_SEQ_STREAM_Disable(hsp_engine_context_t *hmw)
{
  HSP_ASSERT_DBG_PARAM((hmw != NULL));

  HSP_ASSERT_DBG_STATE(hmw->global_state, (uint32_t)HSP_CORE_STATE_IDLE);

  if (HSP_HW_IF_SEQ_STREAM_Disable(&(hmw->hw_if_ctx)) != HSP_IF_OK)
  {
    return HSP_CORE_ERROR;
  }

  return HSP_CORE_OK;
}

#endif /* USE_HSP_ENGINE_STREAM_BUFFER */
#if defined(USE_HSP_ENGINE_ADCIN) && (USE_HSP_ENGINE_ADCIN == 1U)
/**
  * @brief Enable the ADCIN interface.
  * @param  hmw  Pointer to a @ref hsp_engine_context_t.
  * @retval HSP_CORE_OK     Operation successful.
  * @retval HSP_CORE_ERROR  Operation failed.
  */
hsp_core_status_t HSP_SEQ_ADCIN_Enable(hsp_engine_context_t *hmw)
{
  HSP_ASSERT_DBG_PARAM((hmw != NULL));

  HSP_ASSERT_DBG_STATE(hmw->global_state, (uint32_t)HSP_CORE_STATE_IDLE);

  if (HSP_HW_IF_SEQ_ADCIN_Enable(&(hmw->hw_if_ctx)) != HSP_IF_OK)
  {
    return HSP_CORE_ERROR;
  }

  return HSP_CORE_OK;
}

/**
  * @brief Disable the ADCIN interface.
  * @param  hmw  Pointer to a @ref hsp_engine_context_t.
  * @retval HSP_CORE_OK     Operation successful.
  * @retval HSP_CORE_ERROR  Operation failed.
  */
hsp_core_status_t HSP_SEQ_ADCIN_Disable(hsp_engine_context_t *hmw)
{
  HSP_ASSERT_DBG_PARAM((hmw != NULL));

  HSP_ASSERT_DBG_STATE(hmw->global_state, (uint32_t)HSP_CORE_STATE_IDLE);

  if (HSP_HW_IF_SEQ_ADCIN_Disable(&(hmw->hw_if_ctx)) != HSP_IF_OK)
  {
    return HSP_CORE_ERROR;
  }

  return HSP_CORE_OK;
}

/**
  * @brief  Configure an event with a ADCIN trigger as source.
  * @param  hmw             Pointer to a @ref hsp_engine_context_t.
  * @param  evt_id          HSP Event ID.
  * @param  evt_sync        Enable Synchronisation with End Of Task.
  * @param  p_config_array  Pointer to ADCIN configuration array.
  * @param  array_size      Number of elements in the configuration array.
  * @param  p_reg_address_array  Pointer to ADCIN register address array.
  * @note For multiple ADCIN configurations, the "array_size - 1" first element are automatiicaly combined
  *  and the event is attached to the ADCIN interface selected for the first ADCIN configuration.
  *  The pointer to the Register Address array will contains the ADCIN register address of the ADCIN interface
  *  selected for each configuration. This allows the application to use theses addresses as input of processing
  *  functions recorded in processing list.
  * @retval HSP_IF_OK     Action complete successfully
  * @retval HSP_IF_ERROR  Action failed
  */
hsp_core_status_t HSP_SEQ_EVENT_SetConfig_ADCIN(hsp_engine_context_t *hmw,
                                                hsp_seq_event_t evt_id, hsp_seq_event_sync_tcu_t evt_sync,
                                                const hsp_seq_event_adcin_config_t *p_config_array, uint32_t array_size,
                                                uint32_t *p_reg_address_array)
{
  HSP_ASSERT_DBG_PARAM((hmw != NULL));
  HSP_ASSERT_DBG_PARAM((p_config_array != NULL));
  HSP_ASSERT_DBG_PARAM((array_size > 0U));
  HSP_ASSERT_DBG_PARAM((p_reg_address_array != NULL));

  HSP_ASSERT_DBG_STATE(hmw->global_state, (uint32_t)HSP_CORE_STATE_IDLE);

  if (HSP_HW_IF_SEQ_EVENT_SetConfig_ADCIN(&(hmw->hw_if_ctx), (uint32_t)evt_id, (uint32_t)evt_sync,
                                          p_config_array, array_size, p_reg_address_array) != HSP_IF_OK)
  {
    return HSP_CORE_ERROR;
  }

  return HSP_CORE_OK;
}

#endif /* USE_HSP_ENGINE_ADCIN */
/**
  * @brief Configure a HSP Event with a TRGIN as trigger source.
  * @param  hmw  Pointer to a @ref hsp_engine_context_t.
  * @param  evt_id    HSP Event ID.
  * @param  p_config  Pointer to a hsp_seq_event_trigger_config_t.
  * @retval HSP_CORE_OK     Operation successful.
  * @retval HSP_CORE_ERROR  Operation failed.
  */
hsp_core_status_t HSP_SEQ_EVENT_SetConfig_Trigger(hsp_engine_context_t *hmw, hsp_seq_event_t evt_id,
                                                  const hsp_seq_event_trigger_config_t *p_config)
{
  HSP_ASSERT_DBG_PARAM((hmw != NULL));
  HSP_ASSERT_DBG_PARAM((p_config != NULL));

  HSP_ASSERT_DBG_STATE(hmw->global_state, (uint32_t)HSP_CORE_STATE_IDLE);

  if (HSP_HW_IF_SEQ_EVENT_SetConfig_Trigger(&(hmw->hw_if_ctx), (uint32_t)evt_id, p_config->source,
                                            (uint32_t)p_config->polarity, (uint32_t)p_config->evt_sync) != HSP_IF_OK)
  {
    return HSP_CORE_ERROR;
  }

  return HSP_CORE_OK;
}

/**
  * @brief Configure a HSP Event with a CSEG trigger.
  * @param  hmw  Pointer to a @ref hsp_engine_context_t.
  * @param  evt_id    HSP Event ID.
  * @param  tcu_sync  Synchronisation from the end of task
  * @retval HSP_CORE_OK     Operation successful.
  * @retval HSP_CORE_ERROR  Operation failed.
  */
hsp_core_status_t HSP_SEQ_EVENT_SetConfig_CSEG(hsp_engine_context_t *hmw, hsp_seq_event_t evt_id,
                                               hsp_seq_event_sync_tcu_t tcu_sync)
{
  HSP_ASSERT_DBG_PARAM((hmw != NULL));

  HSP_ASSERT_DBG_STATE(hmw->global_state, (uint32_t)HSP_CORE_STATE_IDLE);

  if (HSP_HW_IF_SEQ_EVENT_SetConfig_CSEG(hmw->hdriver, (uint32_t)evt_id, (uint32_t)tcu_sync) != HSP_IF_OK)
  {
    return HSP_CORE_ERROR;
  }

  return HSP_CORE_OK;
}

/**
  * @brief Configure a HSP Event with a HSEG trigger.
  * @param  hmw  Pointer to a @ref hsp_engine_context_t.
  * @param  evt_id    HSP Event ID.
  * @param  tcu_sync  Synchronisation from the end of task
  * @retval HSP_CORE_OK     Operation successful.
  * @retval HSP_CORE_ERROR  Operation failed.
  */
hsp_core_status_t HSP_SEQ_EVENT_SetConfig_SPE(hsp_engine_context_t *hmw, hsp_seq_event_t evt_id,
                                              hsp_seq_event_sync_tcu_t tcu_sync)
{
  HSP_ASSERT_DBG_PARAM((hmw != NULL));

  HSP_ASSERT_DBG_STATE(hmw->global_state, (uint32_t)HSP_CORE_STATE_IDLE);

  if (HSP_HW_IF_SEQ_EVENT_SetConfig_SPE(hmw->hdriver, (uint32_t)evt_id, (uint32_t)tcu_sync) != HSP_IF_OK)
  {
    return HSP_CORE_ERROR;
  }

  return HSP_CORE_OK;
}

/* Event Control -------------------------------------------------------------*/
/**
  * @brief Enable a set of HSP Events.
  * @param  hmw  Pointer to a @ref hsp_engine_context_t.
  * @param  events_mask  Mask of HSP events.
  * @retval HSP_CORE_OK     Operation successful.
  * @retval HSP_CORE_ERROR  Operation failed.
  */
hsp_core_status_t HSP_SEQ_EVENT_Enable(hsp_engine_context_t *hmw, uint32_t events_mask)
{
  HSP_ASSERT_DBG_PARAM((hmw != NULL));
  HSP_ASSERT_DBG_STATE(hmw->global_state, (uint32_t)HSP_CORE_STATE_IDLE);

  if (HSP_HW_IF_SEQ_EVENT_Enable(hmw->hdriver, events_mask) != HSP_IF_OK)
  {
    return HSP_CORE_ERROR;
  }

  return HSP_CORE_OK;
}

/**
  * @brief Disable a set of HSP Events.
  * @param  hmw  Pointer to a @ref hsp_engine_context_t.
  * @param  events_mask  Mask of HSP events.
  * @retval HSP_CORE_OK     Operation successful.
  * @retval HSP_CORE_ERROR  Operation failed.
  */
hsp_core_status_t HSP_SEQ_EVENT_Disable(hsp_engine_context_t *hmw, uint32_t events_mask)
{
  HSP_ASSERT_DBG_PARAM((hmw != NULL));
  HSP_ASSERT_DBG_STATE(hmw->global_state, (uint32_t)HSP_CORE_STATE_IDLE);

  if (HSP_HW_IF_SEQ_EVENT_Disable(hmw->hdriver, events_mask) != HSP_IF_OK)
  {
    return HSP_CORE_ERROR;
  }

  return HSP_CORE_OK;
}

/**
  * @brief Get the enabled status of all HSP Events.
  * @param  hmw  Pointer to a @ref hsp_engine_context_t.
  * @return Mask of enabled HSP Events.
  */
uint32_t HSP_SEQ_EVENT_GetStatus(hsp_engine_context_t *hmw)
{
  HSP_ASSERT_DBG_PARAM((hmw != NULL));

  return HSP_HW_IF_SEQ_EVENT_GetStatus(hmw->hdriver);
}

/**
  * @brief Trig an HSP Event configured with CSEG interface.
  * @param  hmw  Pointer to a @ref hsp_engine_context_t.
  * @param  events_mask  Mask of HSP events.
  * @retval HSP_CORE_OK     Operation successful.
  * @retval HSP_CORE_ERROR  Operation failed.
  */
hsp_core_status_t HSP_SEQ_EVENT_Trig_CSEG(hsp_engine_context_t *hmw, uint32_t events_mask)
{
  HSP_ASSERT_DBG_PARAM((hmw != NULL));
  HSP_ASSERT_DBG_STATE(hmw->global_state, (uint32_t)HSP_CORE_STATE_IDLE);

  if (HSP_HW_IF_SEQ_EVENT_Trig_CSEG(hmw->hdriver, events_mask) != HSP_IF_OK)
  {
    return HSP_CORE_ERROR;
  }

  return HSP_CORE_OK;
}

/**
  * @brief Poll on HSP event in Pending status.
  * @param  hmw  Pointer to a @ref hsp_engine_context_t.
  * @param  events_mask  Mask of HSP events.
  * @param  timeout_ms  Timeout in millisecond.
  * @retval HSP_CORE_OK     Operation successful.
  * @retval HSP_CORE_ERROR  Operation failed.
  */
hsp_core_status_t HSP_SEQ_EVENT_PollForPending(hsp_engine_context_t *hmw, uint32_t events_mask, uint32_t timeout_ms)
{
  HSP_ASSERT_DBG_PARAM((hmw != NULL));
  HSP_ASSERT_DBG_STATE(hmw->global_state, (uint32_t)HSP_CORE_STATE_IDLE);

  if (HSP_HW_IF_SEQ_EVENT_PollForPending(hmw->hdriver, events_mask, timeout_ms) != HSP_IF_OK)
  {
    return HSP_CORE_ERROR;
  }

  return HSP_CORE_OK;
}

/**
  * @brief Record and configure all Processing lists.
  * @param  hmw  Pointer to a @ref hsp_engine_context_t.
  * @return error value (0U - no error)
  */
__weak uint32_t HSP_SEQ_RecordPLHook(hsp_engine_context_t *hmw)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(hmw);

  /* NOTE: This function must not be modified.
           The function HSP_SEQ_RecordPLHook must be implemented in the application file.
   */

  return 0U;
}

/**
  * @}
  */

/** @addtogroup HSP_PROCLIST_Exported_Functions_Group3
  * @{
  */
#if defined(USE_HSP_ENGINE_PROCLIST_NOTIFICATION_IT) && (USE_HSP_ENGINE_PROCLIST_NOTIFICATION_IT == 1U)
/**
  * @brief  Enable Processing Function Event Interrupts.
  * @param  hmw         Pointer to a @ref hsp_engine_context_t.
  * @param  interrupts  Mask of Processing Function Event Interrupts
  *         This parameter can be a combination of following values:
  *             @arg HSP_SEQ_PROCLIST_NOTIF_0:   The Interrupt of Processing Function Event 0
  *             @arg HSP_SEQ_PROCLIST_NOTIF_1:   The Interrupt of Processing Function Event 1
  *             @arg HSP_SEQ_PROCLIST_NOTIF_2:   The Interrupt of Processing Function Event 2
  *             @arg HSP_SEQ_PROCLIST_NOTIF_3:   The Interrupt of Processing Function Event 3
  *             @arg HSP_SEQ_PROCLIST_NOTIF_4:   The Interrupt of Processing Function Event 4
  *             @arg HSP_SEQ_PROCLIST_NOTIF_5:   The Interrupt of Processing Function Event 5
  *             @arg HSP_SEQ_PROCLIST_NOTIF_6:   The Interrupt of Processing Function Event 6
  *             @arg HSP_SEQ_PROCLIST_NOTIF_7:   The Interrupt of Processing Function Event 7
  *             @arg HSP_SEQ_PROCLIST_NOTIF_8:   The Interrupt of Processing Function Event 8
  *             @arg HSP_SEQ_PROCLIST_NOTIF_9:   The Interrupt of Processing Function Event 9
  *             @arg HSP_SEQ_PROCLIST_NOTIF_10:  The Interrupt of Processing Function Event 10
  *             @arg HSP_SEQ_PROCLIST_NOTIF_11:  The Interrupt of Processing Function Event 11
  *             @arg HSP_SEQ_PROCLIST_NOTIF_12:  The Interrupt of Processing Function Event 12
  *             @arg HSP_SEQ_PROCLIST_NOTIF_13:  The Interrupt of Processing Function Event 13
  *             @arg HSP_SEQ_PROCLIST_NOTIF_14:  The Interrupt of Processing Function Event 14
  *             @arg HSP_SEQ_PROCLIST_NOTIF_15:  The Interrupt of Processing Function Event 15
  *             @arg HSP_SEQ_PROCLIST_NOTIF_16:  The Interrupt of Processing Function Event 16
  *             @arg HSP_SEQ_PROCLIST_NOTIF_17:  The Interrupt of Processing Function Event 17
  *             @arg HSP_SEQ_PROCLIST_NOTIF_18:  The Interrupt of Processing Function Event 18
  *             @arg HSP_SEQ_PROCLIST_NOTIF_19:  The Interrupt of Processing Function Event 19
  *             @arg HSP_SEQ_PROCLIST_NOTIF_20:  The Interrupt of Processing Function Event 20
  *             @arg HSP_SEQ_PROCLIST_NOTIF_21:  The Interrupt of Processing Function Event 21
  *             @arg HSP_SEQ_PROCLIST_NOTIF_22:  The Interrupt of Processing Function Event 22
  *             @arg HSP_SEQ_PROCLIST_NOTIF_23:  The Interrupt of Processing Function Event 23
  *             @arg HSP_SEQ_PROCLIST_NOTIF_24:  The Interrupt of Processing Function Event 24
  *             @arg HSP_SEQ_PROCLIST_NOTIF_25:  The Interrupt of Processing Function Event 25
  *             @arg HSP_SEQ_PROCLIST_NOTIF_26:  The Interrupt of Processing Function Event 26
  *             @arg HSP_SEQ_PROCLIST_NOTIF_27:  The Interrupt of Processing Function Event 27
  *             @arg HSP_SEQ_PROCLIST_NOTIF_28:  The Interrupt of Processing Function Event 28
  *             @arg HSP_SEQ_PROCLIST_NOTIF_29:  The Interrupt of Processing Function Event 29
  *             @arg HSP_SEQ_PROCLIST_NOTIF_30:  The Interrupt of Processing Function Event 30
  *             @arg HSP_SEQ_PROCLIST_NOTIF_31:  The Interrupt of Processing Function Event 31
  *             @arg HSP_SEQ_PROCLIST_NOTIF_ALL: All Interrupts of Processing Function Event
  * @retval HSP_CORE_OK  Operation completed successfully.
  * @retval HSP_CORE_ERROR  Operation failed.
  */
hsp_core_status_t HSP_SEQ_EnableProclistNotificationIT(const hsp_engine_context_t *hmw, uint32_t interrupts)
{
  HSP_ASSERT_DBG_PARAM((hmw != NULL));
  HSP_ASSERT_DBG_STATE(hmw->global_state, (uint32_t)HSP_CORE_STATE_IDLE);

  if (HSP_HW_IF_SEQ_EnableProclistNotificationIT(&(hmw->hw_if_ctx), interrupts) != HSP_IF_OK)
  {
    return HSP_CORE_ERROR;
  }

  return HSP_CORE_OK;
}

/**
  * @brief  Disable Processing Function Event Interrupts.
  * @param  hmw         Pointer to a @ref hsp_engine_context_t.
  * @param  interrupts  Mask of Processing Function Event Interrupts
  *         This parameter can be a combination of following values:
  *             @arg HSP_SEQ_PROCLIST_NOTIF_0:   The Interrupt of Processing Function Event 0
  *             @arg HSP_SEQ_PROCLIST_NOTIF_1:   The Interrupt of Processing Function Event 1
  *             @arg HSP_SEQ_PROCLIST_NOTIF_2:   The Interrupt of Processing Function Event 2
  *             @arg HSP_SEQ_PROCLIST_NOTIF_3:   The Interrupt of Processing Function Event 3
  *             @arg HSP_SEQ_PROCLIST_NOTIF_4:   The Interrupt of Processing Function Event 4
  *             @arg HSP_SEQ_PROCLIST_NOTIF_5:   The Interrupt of Processing Function Event 5
  *             @arg HSP_SEQ_PROCLIST_NOTIF_6:   The Interrupt of Processing Function Event 6
  *             @arg HSP_SEQ_PROCLIST_NOTIF_7:   The Interrupt of Processing Function Event 7
  *             @arg HSP_SEQ_PROCLIST_NOTIF_8:   The Interrupt of Processing Function Event 8
  *             @arg HSP_SEQ_PROCLIST_NOTIF_9:   The Interrupt of Processing Function Event 9
  *             @arg HSP_SEQ_PROCLIST_NOTIF_10:  The Interrupt of Processing Function Event 10
  *             @arg HSP_SEQ_PROCLIST_NOTIF_11:  The Interrupt of Processing Function Event 11
  *             @arg HSP_SEQ_PROCLIST_NOTIF_12:  The Interrupt of Processing Function Event 12
  *             @arg HSP_SEQ_PROCLIST_NOTIF_13:  The Interrupt of Processing Function Event 13
  *             @arg HSP_SEQ_PROCLIST_NOTIF_14:  The Interrupt of Processing Function Event 14
  *             @arg HSP_SEQ_PROCLIST_NOTIF_15:  The Interrupt of Processing Function Event 15
  *             @arg HSP_SEQ_PROCLIST_NOTIF_16:  The Interrupt of Processing Function Event 16
  *             @arg HSP_SEQ_PROCLIST_NOTIF_17:  The Interrupt of Processing Function Event 17
  *             @arg HSP_SEQ_PROCLIST_NOTIF_18:  The Interrupt of Processing Function Event 18
  *             @arg HSP_SEQ_PROCLIST_NOTIF_19:  The Interrupt of Processing Function Event 19
  *             @arg HSP_SEQ_PROCLIST_NOTIF_20:  The Interrupt of Processing Function Event 20
  *             @arg HSP_SEQ_PROCLIST_NOTIF_21:  The Interrupt of Processing Function Event 21
  *             @arg HSP_SEQ_PROCLIST_NOTIF_22:  The Interrupt of Processing Function Event 22
  *             @arg HSP_SEQ_PROCLIST_NOTIF_23:  The Interrupt of Processing Function Event 23
  *             @arg HSP_SEQ_PROCLIST_NOTIF_24:  The Interrupt of Processing Function Event 24
  *             @arg HSP_SEQ_PROCLIST_NOTIF_25:  The Interrupt of Processing Function Event 25
  *             @arg HSP_SEQ_PROCLIST_NOTIF_26:  The Interrupt of Processing Function Event 26
  *             @arg HSP_SEQ_PROCLIST_NOTIF_27:  The Interrupt of Processing Function Event 27
  *             @arg HSP_SEQ_PROCLIST_NOTIF_28:  The Interrupt of Processing Function Event 28
  *             @arg HSP_SEQ_PROCLIST_NOTIF_29:  The Interrupt of Processing Function Event 29
  *             @arg HSP_SEQ_PROCLIST_NOTIF_30:  The Interrupt of Processing Function Event 30
  *             @arg HSP_SEQ_PROCLIST_NOTIF_31:  The Interrupt of Processing Function Event 31
  *             @arg HSP_SEQ_PROCLIST_NOTIF_ALL: All Interrupts of Processing Function Event
  * @retval HSP_CORE_OK  Operation completed successfully.
  * @retval HSP_CORE_ERROR  Operation failed.
  */
hsp_core_status_t HSP_SEQ_DisableProclistNotificationIT(const hsp_engine_context_t *hmw, uint32_t interrupts)
{
  HSP_ASSERT_DBG_PARAM((hmw != NULL));
  HSP_ASSERT_DBG_STATE(hmw->global_state, (uint32_t)HSP_CORE_STATE_IDLE);

  if (HSP_HW_IF_SEQ_DisableProclistNotificationIT(&(hmw->hw_if_ctx), interrupts) != HSP_IF_OK)
  {
    return HSP_CORE_ERROR;
  }

  return HSP_CORE_OK;
}

/**
  * @brief  Poll until selected Processing Function Event Flags are triggered.
  * @param  hhsp         Pointer to a @ref hal_hsp_handle_t.
  * @param  poll_mode    Polling mode.
  * @param  pfct_events  Mask of events to poll.
  *         This parameter can be a combination of the following values:
  *             @arg HSP_SEQ_PROCLIST_NOTIF_0:   The Flag of Processing Function Event 0
  *             @arg HSP_SEQ_PROCLIST_NOTIF_1:   The Flag of Processing Function Event 1
  *             @arg HSP_SEQ_PROCLIST_NOTIF_2:   The Flag of Processing Function Event 2
  *             @arg HSP_SEQ_PROCLIST_NOTIF_3:   The Flag of Processing Function Event 3
  *             @arg HSP_SEQ_PROCLIST_NOTIF_4:   The Flag of Processing Function Event 4
  *             @arg HSP_SEQ_PROCLIST_NOTIF_5:   The Flag of Processing Function Event 5
  *             @arg HSP_SEQ_PROCLIST_NOTIF_6:   The Flag of Processing Function Event 6
  *             @arg HSP_SEQ_PROCLIST_NOTIF_7:   The Flag of Processing Function Event 7
  *             @arg HSP_SEQ_PROCLIST_NOTIF_8:   The Flag of Processing Function Event 8
  *             @arg HSP_SEQ_PROCLIST_NOTIF_9:   The Flag of Processing Function Event 9
  *             @arg HSP_SEQ_PROCLIST_NOTIF_10:  The Flag of Processing Function Event 10
  *             @arg HSP_SEQ_PROCLIST_NOTIF_11:  The Flag of Processing Function Event 11
  *             @arg HSP_SEQ_PROCLIST_NOTIF_12:  The Flag of Processing Function Event 12
  *             @arg HSP_SEQ_PROCLIST_NOTIF_13:  The Flag of Processing Function Event 13
  *             @arg HSP_SEQ_PROCLIST_NOTIF_14:  The Flag of Processing Function Event 14
  *             @arg HSP_SEQ_PROCLIST_NOTIF_15:  The Flag of Processing Function Event 15
  *             @arg HSP_SEQ_PROCLIST_NOTIF_16:  The Flag of Processing Function Event 16
  *             @arg HSP_SEQ_PROCLIST_NOTIF_17:  The Flag of Processing Function Event 17
  *             @arg HSP_SEQ_PROCLIST_NOTIF_18:  The Flag of Processing Function Event 18
  *             @arg HSP_SEQ_PROCLIST_NOTIF_19:  The Flag of Processing Function Event 19
  *             @arg HSP_SEQ_PROCLIST_NOTIF_20:  The Flag of Processing Function Event 20
  *             @arg HSP_SEQ_PROCLIST_NOTIF_21:  The Flag of Processing Function Event 21
  *             @arg HSP_SEQ_PROCLIST_NOTIF_22:  The Flag of Processing Function Event 22
  *             @arg HSP_SEQ_PROCLIST_NOTIF_23:  The Flag of Processing Function Event 23
  *             @arg HSP_SEQ_PROCLIST_NOTIF_24:  The Flag of Processing Function Event 24
  *             @arg HSP_SEQ_PROCLIST_NOTIF_25:  The Flag of Processing Function Event 25
  *             @arg HSP_SEQ_PROCLIST_NOTIF_26:  The Flag of Processing Function Event 26
  *             @arg HSP_SEQ_PROCLIST_NOTIF_27:  The Flag of Processing Function Event 27
  *             @arg HSP_SEQ_PROCLIST_NOTIF_28:  The Flag of Processing Function Event 28
  *             @arg HSP_SEQ_PROCLIST_NOTIF_29:  The Flag of Processing Function Event 29
  *             @arg HSP_SEQ_PROCLIST_NOTIF_30:  The Flag of Processing Function Event 30
  *             @arg HSP_SEQ_PROCLIST_NOTIF_31:  The Flag of Processing Function Event 31
  *             @arg HSP_SEQ_PROCLIST_NOTIF_ALL: All Flags of Processing Function Event
  * @param  timeout_ms  Timeout duration (in ms).
  * @retval HSP_CORE_OK     Operation completed successfully.
  * @retval HSP_CORE_ERROR  Operation failed.
  */
hsp_core_status_t HSP_SEQ_PollForProclistNotification(const hsp_engine_context_t *hmw,
                                                      uint32_t pfct_events, uint32_t timeout_ms)
{
  HSP_ASSERT_DBG_PARAM((hmw != NULL));
  HSP_ASSERT_DBG_STATE(hmw->global_state, (uint32_t)HSP_CORE_STATE_IDLE);

  if (HSP_HW_IF_SEQ_PollForProclistNotification(&(hmw->hw_if_ctx), pfct_events, timeout_ms) != HSP_IF_OK)
  {
    return HSP_CORE_ERROR;
  }

  return HSP_CORE_OK;
}
#endif /* USE_HSP_ENGINE_PROCLIST_NOTIFICATION_IT */

/**
  * @}
  */


/** @addtogroup HSP_PROCLIST_Exported_Functions_Group4
  * @{
  */
#if defined(USE_HSP_ENGINE_PROCLIST_NOTIFICATION_IT) && (USE_HSP_ENGINE_PROCLIST_NOTIFICATION_IT == 1U)
/**
  * @brief  Register a User HSP callback for Processing List Notification by interrupt.
  * @param  hmw  Pointer to a @ref hsp_engine_context_t.
  * @param  p_callback  Pointer to the callback function.
  * @retval HSP_CORE_OK     Operation successful.
  * @retval HSP_CORE_ERROR  Operation failed.
  */
hsp_core_status_t HSP_SEQ_RegisterProcListEventsCallback(hsp_engine_context_t *hmw,
                                                         p_hsp_engine_one_param_cb_t p_callback)
{
  HSP_ASSERT_DBG_PARAM((hmw != NULL));

  if (HSP_HW_IF_RegisterProcessingEventCallback(&(hmw->hw_if_ctx), p_callback) != HSP_IF_OK)
  {
    return HSP_CORE_ERROR;
  }

  return HSP_CORE_OK;
}
#endif /* USE_HSP_ENGINE_PROCLIST_NOTIFICATION_IT */

#if defined(USE_HSP_ENGINE_STREAM_BUFFER) && (USE_HSP_ENGINE_STREAM_BUFFER == 1U)
/**
  * @brief  Register a User HSP callback for STREAM Buffer Write complete interrupt.
  * @param  hmw  Pointer to a @ref hsp_engine_context_t.
  * @param  p_callback  Pointer to the callback function.
  * @retval HSP_CORE_OK     Operation successful.
  * @retval HSP_CORE_ERROR  Operation failed.
  */
hsp_core_status_t HSP_SEQ_RegisterStreamBufferWriteCpltCallback(hsp_engine_context_t *hmw,
                                                                p_hsp_engine_one_param_cb_t p_callback)
{
  HSP_ASSERT_DBG_PARAM((hmw != NULL));

  if (HSP_HW_IF_RegisterStreamBufferWriteCpltCallback(&(hmw->hw_if_ctx), p_callback) != HSP_IF_OK)
  {
    return HSP_CORE_ERROR;
  }

  return HSP_CORE_OK;
}

/**
  * @brief  Register a User HSP callback for STREAM Buffer Read complete interrupt.
  * @param  hmw  Pointer to a @ref hsp_engine_context_t.
  * @param  p_callback  Pointer to the callback function.
  * @retval HSP_CORE_OK     Operation successful.
  * @retval HSP_CORE_ERROR  Operation failed.
  */
hsp_core_status_t HSP_SEQ_RegisterStreamBufferReadCpltCallback(hsp_engine_context_t *hmw,
                                                               p_hsp_engine_one_param_cb_t p_callback)
{
  HSP_ASSERT_DBG_PARAM((hmw != NULL));

  if (HSP_HW_IF_RegisterStreamBufferReadCpltCallback(&(hmw->hw_if_ctx), p_callback) != HSP_IF_OK)
  {
    return HSP_CORE_ERROR;
  }

  return HSP_CORE_OK;
}

#endif /* USE_HSP_ENGINE_STREAM_BUFFER */

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
