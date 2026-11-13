/**
  ******************************************************************************
  * @file    hsp_engine_legacy.h
  * @author  MCD Application Team
  * @brief   This file contains aliases definition for the HSP Engine constants,
  *          macros and functions maintained for legacy purpose.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2026 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef HSP_ENGINE_LEGACY
#define HSP_ENGINE_LEGACY

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* Includes ------------------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macros -----------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/

/** @defgroup HSP_CORE_Aliased_Defines HSP CORE Aliased Defines maintained for legacy purpose
  * @{
  */
#if defined(USE_HSP_ENGINE_STREAM_BUFFER) && (USE_HSP_ENGINE_STREAM_BUFFER == 1U)
#define HSP_CORE_RegisterStreamBufferWriteCpltCallback(hmw, p_callback)  \
  HSP_SEQ_RegisterStreamBufferWriteCpltCallback((hmw), (p_callback))

#define HSP_CORE_RegisterStreamBufferReadCpltCallback(hmw, p_callback)  \
  HSP_SEQ_RegisterStreamBufferReadCpltCallback((hmw), (p_callback))
#endif /* USE_HSP_ENGINE_STREAM_BUFFER */

#if defined(USE_HSP_ENGINE_LEGACY_INIT) && (USE_HSP_ENGINE_LEGACY_INIT == 1)
#define HSP_CORE_Init(hmw, hdriver) \
  HSP_CORE_Init((hmw), &(hsp_engine_hw_context_t){ .hhsp_driver = (hdriver) })
#endif /* USE_HSP_ENGINE_LEGACY_INIT */

#define HSP_TRGO_0  HSP_SEQ_TRGO_0
#define HSP_TRGO_1  HSP_SEQ_TRGO_1
#define HSP_TRGO_2  HSP_SEQ_TRGO_2
#define HSP_TRGO_3  HSP_SEQ_TRGO_3

/**
  * @}
  */

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* HSP_ENGINE_LEGACY */
