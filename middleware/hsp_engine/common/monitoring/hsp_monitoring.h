/**
  ******************************************************************************
  * @file    hsp_monitoring.h
  * @brief   Header file for hsp_monitoring.c
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
#ifndef HSP_MONITORING_H
#define HSP_MONITORING_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* Includes ------------------------------------------------------------------*/
#include "hsp_api_def.h"
#include "hsp_conf.h"
#include "hsp_hw_if.h"

/** @addtogroup HSP_ENGINE
  * @{
  */

/** @defgroup HSP_MONITORING HSP Monitoring
  * @{
  */
#define HSP_MONITOR_TASK_COMPARATOR_0  HSP_HW_IF_TASK_COMPARATOR_0
#define HSP_MONITOR_TASK_COMPARATOR_1  HSP_HW_IF_TASK_COMPARATOR_1
#define HSP_MONITOR_TASK_COMPARATOR_2  HSP_HW_IF_TASK_COMPARATOR_2
#define HSP_MONITOR_TASK_COMPARATOR_3  HSP_HW_IF_TASK_COMPARATOR_3

#define HSP_MONITOR_TCU_START_EVT_MASK  HSP_HW_IF_TCU_START_EVT_MASK
#define HSP_MONITOR_TCU_END_EVT_MASK  HSP_HW_IF_TCU_END_EVT_MASK
#define HSP_MONITOR_TCU_START_EVT_0  HSP_HW_IF_TCU_START_EVT_0
#define HSP_MONITOR_TCU_START_EVT_1  HSP_HW_IF_TCU_START_EVT_1
#define HSP_MONITOR_TCU_START_EVT_2  HSP_HW_IF_TCU_START_EVT_2
#define HSP_MONITOR_TCU_START_EVT_3  HSP_HW_IF_TCU_START_EVT_3

#define HSP_MONITOR_TCU_TASK_EVT_STARTED_MASK(tcuid)  HSP_HW_IF_TCU_TASK_EVT_STARTED_MASK((tcuid))
#define HSP_MONITOR_TCU_TASK_EVT_ENDED_MASK(tcuid)  HSP_HW_IF_TCU_TASK_EVT_ENDED_MASK((tcuid))

#define HSP_MONITOR_TSC_TASK_FILTER_NONE  (0xFFFFUL)
#define HSP_MONITOR_TSC_PRESCALER_DISABLE  HSP_HW_IF_TSC_PRESCALER_DISABLE  /*!< Constant to disable the Timestamp Capture prescaler and then the Free-Running Counter */

#define HSP_MONITOR_DEBUG_BREAK_EVENT_MEMORY_ACCESS   HSP_HW_IF_BREAK_EVENT_MEMORY_ACCESS
#define HSP_MONITOR_DEBUG_BREAK_EVENT_FPU             HSP_HW_IF_BREAK_EVENT_FPU
#define HSP_MONITOR_DEBUG_BREAK_EVENT_OPCODE          HSP_HW_IF_BREAK_EVENT_OPCODE
#define HSP_MONITOR_DEBUG_BREAK_EVENT_PFCT28          HSP_HW_IF_BREAK_EVENT_PFCT28
#define HSP_MONITOR_DEBUG_BREAK_EVENT_PFCT29          HSP_HW_IF_BREAK_EVENT_PFCT29
#define HSP_MONITOR_DEBUG_BREAK_EVENT_PFCT30          HSP_HW_IF_BREAK_EVENT_PFCT30
#define HSP_MONITOR_DEBUG_BREAK_EVENT_PFCT31          HSP_HW_IF_BREAK_EVENT_PFCT31
#define HSP_MONITOR_DEBUG_BREAK_EVENT_FIRMWARE        HSP_HW_IF_BREAK_EVENT_FIRMWARE
#define HSP_MONITOR_DEBUG_BREAK_EVENT_SPE_OVR         HSP_HW_IF_BREAK_EVENT_SPE_OVR
#define HSP_MONITOR_DEBUG_BREAK_EVENT_FPU_SATURATION  HSP_HW_IF_BREAK_EVENT_FPU_SATURATION


typedef enum
{
  HSP_MONITOR_TSC_SPE_BREAK   = HSP_HW_IF_TSC_MODE_SPE_BREAK,
  HSP_MONITOR_TSC_TASK_CHANGE = HSP_HW_IF_TSC_MODE_TASK_CHANGE,
  HSP_MONITOR_TSC_PFCT_CHANGE = HSP_HW_IF_TSC_MODE_PFCT_CHANGE,
} hsp_monitor_tsc_mode_t;

typedef struct
{
  uint32_t prescaler;    /*! Prescaler for the Timestamp counter */
  uint32_t task_filter;  /*! ID of task to monitor */
} hsp_monitor_tsc_config_t;


/** HAL HSP TimeStamp Data structure.
  * This type provides the raw 32-bit value read from CAPDR and 2 bitfield views:
  * - free_counter     : layout when HSP_CAPCR_FRCNTEN is set
  * - no_free_counter  : alternate layout when HSP_CAPCR_FRCNTEN is cleared
  */
typedef union
{
  /*! Raw 32-bit value */
  uint32_t raw;

  /** Timestamp format with FreeCounter enabled */
  struct
  {
    uint32_t timestamp   : 14;
    uint32_t if_history  : 8;
    uint32_t if_counter  : 4;
    uint32_t task_number : 6;
  } free_counter;

  /** Timestamp format with FreeCounter disabled */
  struct
  {
    uint32_t if_history  : 15;
    uint32_t reserved0   : 1;
    uint32_t pfct_number : 6;
    uint32_t if_counter  : 4;
    uint32_t task_number : 6;
  } no_free_counter;
} hsp_monitor_tsc_timestamp_t;

/** @defgroup HSP_MONITORING_Exported_Functions HSP Core Exported Functions
  * @{
  */

/** @defgroup HSP_CORE_Exported_Functions_Group1 HSP Task Comparator Management
  * @{
  */
#if defined(USE_HSP_ENGINE_TCU_IT) && (USE_HSP_ENGINE_TCU_IT == 1U)
hsp_core_status_t HSP_MONITOR_StartTaskComparator(const hsp_engine_context_t *hmw, uint32_t tcu_id, uint32_t task_id);
hsp_core_status_t HSP_MONITOR_StopTaskComparator(const hsp_engine_context_t *hmw, uint32_t tcu_id);
#endif /* USE_HSP_ENGINE_TCU_IT */

/**
  * @}
  */

/** @defgroup HSP_MONITORING_Exported_Functions_Group2 HSP TimeStamp Capture
  * @{
  */
#if defined(USE_HSP_ENGINE_TIMESTAMPCAPTURE) && (USE_HSP_ENGINE_TIMESTAMPCAPTURE == 1U)
hsp_core_status_t HSP_MONITOR_SetConfigTimestampCapture(const hsp_engine_context_t *hmw,
                                                        const hsp_monitor_tsc_config_t *p_config);
hsp_core_status_t HSP_MONITOR_StartTimestampCapture(hsp_engine_context_t *hmw, hsp_monitor_tsc_mode_t mode,
                                                    void *p_output_buffer, uint32_t output_buffer_size);
hsp_core_status_t HSP_MONITOR_StopTimestampCapture(const hsp_engine_context_t *hmw);
volatile const uint32_t *HSP_MONITOR_GetTimestampCaptureBufferAddress(const hsp_engine_context_t *hmw);
#endif /* USE_HSP_ENGINE_TIMESTAMPCAPTURE */

/**
  * @}
  */

/** @defgroup HSP_MONITORING_Exported_Functions_Group4 HSP Counters
  * @{
  */
uint32_t HSP_MONITOR_GetPerformanceCounter(const hsp_engine_context_t *hmw);

/**
  * @}
  */

/** @defgroup HSP_MONITORING_Exported_Functions_Group5 HSP Break management
  * @{
  */
hsp_core_status_t HSP_MONITOR_SetBreakMultiOutput(hsp_engine_context_t *hmw,
                                                  const uint32_t *p_config_array, uint32_t config_array_size);

hsp_core_status_t HSP_MONITOR_SetDebugBreakEvents(hsp_engine_context_t *hmw, uint32_t break_events);
hsp_core_status_t HSP_MONITOR_ResumeDebugBreakEvents(hsp_engine_context_t *hmw);
/**
  * @}
  */

/** @defgroup HSP_MONITORING_Exported_Functions_Group6 HSP Callbacks
  * @{
  */
#if defined(USE_HSP_ENGINE_TCU_IT) && (USE_HSP_ENGINE_TCU_IT == 1U)
hsp_core_status_t HSP_MONITOR_RegisterTCU_TaskStartedCallback(hsp_engine_context_t *hmw,
                                                              p_hsp_engine_one_param_cb_t p_callback);
hsp_core_status_t HSP_MONITOR_RegisterTCU_TaskEndedCallback(hsp_engine_context_t *hmw,
                                                            p_hsp_engine_one_param_cb_t p_callback);
#endif /* USE_HSP_ENGINE_TCU_IT */

#if defined(USE_HSP_ENGINE_TIMESTAMPCAPTURE) && (USE_HSP_ENGINE_TIMESTAMPCAPTURE == 1U)
void HSP_MONITOR_TSC_CompleteCallback(void *hmw);
void HSP_MONITOR_TSC_ErrorCallback(void *hmw);
hsp_core_status_t HSP_MONITOR_RegisterTSC_CompleteCallback(hsp_engine_context_t *hmw,
                                                           p_hsp_engine_cb_t p_callback);
hsp_core_status_t HSP_MONITOR_RegisterTSC_ErrorCallback(hsp_engine_context_t *hmw,
                                                        p_hsp_engine_cb_t p_callback);
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

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* HSP_MONITORING_H */
