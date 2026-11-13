/**
  ******************************************************************************
  * @file    hsp_proclist_digital_control.h
  * @brief   Header file for hsp_proclist_digital_control.c
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

/* Define to prevent recursive  ----------------------------------------------*/
#ifndef HSP_PROCLIST_DIGITAL_CONTROL_H
#define HSP_PROCLIST_DIGITAL_CONTROL_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* Includes ------------------------------------------------------------------*/
#include "hsp_proclist_def.h"

/** @addtogroup HSP_ENGINE
  * @{
  */

/** @addtogroup HSP_MODULES
  * @{
  */

/** @defgroup HSP_MODULES_PROCLIST HSP Modules Processing List
  * @details
  * This section includes all functions and definitions related to the sequencer (SEQ) mode of the HSP
  * @{
  */

/** @defgroup HSP_MODULES_PROCLIST_DIGITAL_CONTROL_LIBRARY HSP Proclist Digital Control Functions
  * @{
  */

/** @defgroup HSP_DIGITAL_CONTROL_Exported_Functions HSP DIGITAL CONTROL Exported Functions
  * @{
  */
#if defined(__HSP_DMA__)
hsp_core_status_t HSP_SEQ_DcPidP1_f32(hsp_engine_context_t *hmw, float32_t *pSrc, float32_t *pSet, float32_t *pDst,
                                      hyp_dc_pidpx_ctrl_t *pCfg, uint32_t ioType);
hsp_core_status_t HSP_SEQ_DcPidP2_f32(hsp_engine_context_t *hmw, float32_t *pSrc, float32_t *pSet, float32_t *pDst,
                                      hyp_dc_pidpx_ctrl_t *pCfg, uint32_t ioType);
hsp_core_status_t HSP_SEQ_DcPidP3_f32(hsp_engine_context_t *hmw, float32_t *pSrc, float32_t *pSet, float32_t *pDst,
                                      hyp_dc_pidpx_ctrl_t *pCfg, uint32_t ioType);
hsp_core_status_t HSP_SEQ_DcPip1_f32(hsp_engine_context_t *hmw, float32_t *pSrc, float32_t *pSet, float32_t *pDst,
                                     hyp_dc_pipx_ctrl_t *pCfg, uint32_t ioType);
hsp_core_status_t HSP_SEQ_DcPip2_f32(hsp_engine_context_t *hmw, float32_t *pSrc, float32_t *pSet, float32_t *pDst,
                                     hyp_dc_pipx_ctrl_t *pCfg, uint32_t ioType);
hsp_core_status_t HSP_SEQ_DcPis2_f32(hsp_engine_context_t *hmw, float32_t *pSrc, float32_t *pSet, float32_t *pDst,
                                     hyp_dc_pipx_ctrl_t *pCfg, uint32_t ioType);
hsp_core_status_t HSP_SEQ_DcPis3_f32(hsp_engine_context_t *hmw, float32_t *pSrc, float32_t *pSet, float32_t *pDst,
                                     hyp_dc_pis3_ctrl_t *pCfg, uint32_t ioType);
hsp_core_status_t HSP_SEQ_DcGPid_f32(hsp_engine_context_t *hmw, float32_t *pSrc, float32_t *pSet, float32_t *pDst,
                                     hyp_dc_gpid_ctrl_t *pCfg, uint32_t ioType);
hsp_core_status_t HSP_SEQ_DcPpr1_f32(hsp_engine_context_t *hmw, float32_t *pSrc, float32_t *pSet, float32_t *pDst,
                                     hyp_dc_ppr1_ctrl_t *pCfg, hyp_dc_ppr1_sta_t *pState, uint32_t ioType);
hsp_core_status_t HSP_SEQ_DcClarke3_f32(hsp_engine_context_t *hmw, float32_t *pSrc, float32_t *pDst, uint32_t ioType);
hsp_core_status_t HSP_SEQ_DcIclarke3_f32(hsp_engine_context_t *hmw, float32_t *pSrc, float32_t *pDst, uint32_t ioType);
hsp_core_status_t HSP_SEQ_DcPark2_f32(hsp_engine_context_t *hmw, float32_t *pTheta, float32_t *pSrc, float32_t *pDst,
                                      uint32_t ioType);
hsp_core_status_t HSP_SEQ_DcIpark2_f32(hsp_engine_context_t *hmw, float32_t *pTheta, float32_t *pSrc, float32_t *pDst,
                                       uint32_t ioType);
hsp_core_status_t HSP_SEQ_DcFPark_f32(hsp_engine_context_t *hmw, uint32_t *pTheta, float32_t *pSrc, float32_t *pDst,
                                      uint32_t ioType);
hsp_core_status_t HSP_SEQ_DcFIpark_f32(hsp_engine_context_t *hmw, uint32_t *pTheta, float32_t *pSrc, float32_t *pDst,
                                       uint32_t ioType);

#endif /* __HSP_DMA__ */

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

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* HSP_PROCLIST_DIGITAL_CONTROL_H */
