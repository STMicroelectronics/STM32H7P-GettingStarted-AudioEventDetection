/**
  ******************************************************************************
  * @file    interface.h
  * @brief   global Header file for all "interface" .c files .
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

#ifndef INTERFACE_H
#define INTERFACE_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* Includes ------------------------------------------------------------------*/
#include <stdint.h>

/** @addtogroup HSP_ENGINE
  * @{
  */

/** @addtogroup HSP_INTERFACES
  * @{
  */

/* Exported types ------------------------------------------------------------*/
/** @defgroup  HSP_INTERFACES_Exported_Types HSP Interfaces Exported Types
  * @{
  */
typedef enum
{
  HSP_IF_OK,
  HSP_IF_ERROR
} hsp_if_status_t;

typedef enum
{
  HSP_IF_ACTIVATION_DISABLED = 0U,
  HSP_IF_ACTIVATION_ENABLED  = 1U
} hsp_if_activation_status_t;

typedef struct
{
  uint32_t *p_data;
  uint32_t data_counter;
} hsp_hw_if_buffer_t;

/** Pointer to a HSP Error callback function */
typedef void (*p_hsp_engine_error_cb_t)(void *p_mw_ctx,
                                        uint32_t err_status, uint32_t value1, uint32_t value2);

typedef void (*p_hsp_engine_cb_t)(void *p_mw_ctx);
typedef void (*p_hsp_engine_one_param_cb_t)(void *p_mw_ctx, uint32_t value);
typedef void (*p_hsp_engine_two_params_cb_t)(void *p_mw_ctx, uint32_t value1, uint32_t value2);

typedef struct
{
  void *hdriver;

  /** HSP Error callback function pointer */
  p_hsp_engine_error_cb_t p_error_cb;

#if defined(USE_HSP_ENGINE_PROCLIST_NOTIFICATION_IT) && (USE_HSP_ENGINE_PROCLIST_NOTIFICATION_IT == 1U)
  p_hsp_engine_one_param_cb_t p_proclist_event_cb;
#endif  /* USE_HSP_ENGINE_PROCLIST_NOTIFICATION_IT */
#if defined(USE_HSP_ENGINE_STREAM_BUFFER) && (USE_HSP_ENGINE_STREAM_BUFFER == 1U)
  p_hsp_engine_one_param_cb_t p_stream_buffer_write_cplt_cb;
  p_hsp_engine_one_param_cb_t p_stream_buffer_read_cplt_cb;

  hsp_hw_if_buffer_t a_user_stream_buffer[4U];
#endif /* USE_HSP_ENGINE_STREAM_BUFFER */

#if defined(USE_HSP_ENGINE_ADCIN) && (USE_HSP_ENGINE_ADCIN == 1U)
  uint32_t adcin_instances; /* bitfields to identify which ADCIN are free or configured */
#endif /* USE_HSP_ENGINE_ADCIN */
  uint32_t trgin_instances; /* bitfields to identify which TRGIN are free or configured */

#if defined(USE_HSP_ENGINE_TCU_IT) && (USE_HSP_ENGINE_TCU_IT == 1U)
  p_hsp_engine_one_param_cb_t p_tcu_task_started_cb;
  p_hsp_engine_one_param_cb_t p_tcu_task_ended_cb;
#endif /* USE_HSP_ENGINE_TCU_IT */

#if defined(USE_HSP_ENGINE_TIMESTAMPCAPTURE) && (USE_HSP_ENGINE_TIMESTAMPCAPTURE == 1U)
  void *hdma_tsc;
  p_hsp_engine_cb_t p_tsc_complete_cb;
  p_hsp_engine_cb_t p_tsc_error_cb;
#endif /* USE_HSP_ENGINE_TIMESTAMPCAPTURE */

  void *p_user_data;
} hsp_hw_if_ctx_t;

/**
  * @brief HSP BRAM Handle Type Structure Definition
  */
typedef struct hsp_bram_handle_s hsp_bram_handle_t;

/**
  * @brief HSP BRAM Handle Structure Definition
  */
struct hsp_bram_handle_s
{
  uint32_t baseSharedAddr;          /*!< Base address of the shared memory */
  uint32_t topSharedAddr;           /*!< Top address of the shared memory */
  uint32_t currentSharedAddr;       /*!< Current top address of the shared memory */
  uint32_t maxSizeToAllocate;       /*!< Maximum size that can be allocated */
  uint32_t maxSizePersistent;       /*!< Maximum size that can be allocated in persistent memory */
  uint32_t currentSharedOffset;     /*!< Start offset to allocate shared memory buffer */
  uint32_t currentPersistentOffset; /*!< Start offset to allocate shared memory buffer */
  int32_t  bramOffset;              /*!< Offset used to calculate HSP shared address */
  uint32_t baseSharedAddrA;         /*!< Base address of the MEMA memory */
  uint32_t baseSharedAddrB;         /*!< Base address of the MEMB memory */
  uint32_t maxSizeToAllocateA;      /*!< Maximum size that can be allocated in MEMA */
  uint32_t maxSizeToAllocateB;      /*!< Maximum size that can be allocated in MEMB */
  uint32_t currentSharedAddrA;      /*!< Current top address of the shared memory MEMA */
  uint32_t currentSharedAddrB;      /*!< Current top address of the shared memory MEMB */
  uint32_t currentSharedOffsetA;    /*!< Start offset to allocate shared memory buffer in MEMA */
  uint32_t currentSharedOffsetB;    /*!< Start offset to allocate shared memory buffer in MEMB */

  uint32_t *p_perf_monitor_counter; /*!< Pointer to the performance monitor counter in BRAM, NULL if not supported */
};

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

#endif /* INTERFACE_H */
