/**
  ******************************************************************************
  * @file    hsp_proclist_vector.h
  * @brief   Header file for hsp_proclist_vector.c
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
#ifndef HSP_PROCLIST_VECTOR_H
#define HSP_PROCLIST_VECTOR_H

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

/** @addtogroup HSP_MODULES_PROCLIST
  * @{
  */

/** @defgroup HSP_MODULES_PROCLIST_VECTOR_LIBRARY HSP Proclist Vector Functions
  * @{
  */
/* Exported constants --------------------------------------------------------*/
/* Exported macros -----------------------------------------------------------*/

/* Exported types ------------------------------------------------------------*/
/** @defgroup  HSP_MODULES_PROCLIST_VECTOR_Exported_Types HSP Vector Exported Types
  * @{
  */
/**
  * @brief  HSP_CMD_CMPCNT configuration fields: [loTh, hiTh, maxCntLo, maxCntHi]
  */
typedef struct
{
  float32_t loTh;     /*!< Low threshold value */
  float32_t hiTh;     /*!< High threshold value */
  uint32_t maxCntLo;  /*!< LO counter value: for number of consecutive value bigger than loTh */
  uint32_t maxCntHi;  /*!< HI counter value: for number of consecutive value lower than hiTh */
} HSP_CmpCntBuffCfgTypeDef;

/**
  * @brief  HSP_CMD_CMPCNT counter fields: [cntLo, cntHi]
  */
typedef struct
{
  uint32_t cntLo; /*!< Low counter value (LO) */
  uint32_t cntHi; /*!< High counter value (HI) */
} HSP_CmpCntBuffCntTypeDef;

/**
  * @}
  */

/* Exported variables --------------------------------------------------------*/

/* Exported functions --------------------------------------------------------*/
/** @defgroup HSP_Vector_Exported_Functions HSP Vector Exported Functions
  * @{
  */
/** @defgroup HSP_Vector_Exported_Functions_Group1  Arithmetic Functions
  * @{
  */
hsp_core_status_t HSP_SEQ_VectAbs_f32(hsp_engine_context_t *hmw, float32_t *pSrc, float32_t *pDst,
                                      uint32_t nbSamples, uint32_t ioType);
hsp_core_status_t HSP_SEQ_VectAdd_f32(hsp_engine_context_t *hmw, float32_t *pSrcA, float32_t *pSrcB,
                                      float32_t *pDst, uint32_t nbSamples, uint32_t ioType);
hsp_core_status_t HSP_SEQ_VectAvg_f32(hsp_engine_context_t *hmw, float32_t *pSrc, float32_t *pDst, uint32_t nbSamples,
                                      uint32_t ioType);
hsp_core_status_t HSP_SEQ_VectDiv_f32(hsp_engine_context_t *hmw, float32_t *pSrcA, float32_t *pSrcB, float32_t *pDst,
                                      uint32_t nbSamples, uint32_t ioType);
hsp_core_status_t HSP_SEQ_VectDotProd_f32(hsp_engine_context_t *hmw, float32_t *pSrcA, float32_t *pSrcB,
                                          float32_t *pDst, uint32_t nbSamples, uint32_t ioType);
hsp_core_status_t HSP_SEQ_VectDecim_f32(hsp_engine_context_t *hmw, float32_t *pSrc, uint32_t decim,
                                        float32_t *pDst, uint32_t sizeOu, uint32_t ioType);
hsp_core_status_t HSP_SEQ_VectIOffset_f32(hsp_engine_context_t *hmw, float32_t *pSrc, float32_t offset, float32_t *pDst,
                                          uint32_t nbSamples, uint32_t ioType);
hsp_core_status_t HSP_SEQ_VectIScale_f32(hsp_engine_context_t *hmw, float32_t *pSrc, float32_t scale, float32_t *pDst,
                                         uint32_t nbSamples, uint32_t ioType);
hsp_core_status_t HSP_SEQ_VectOffset_f32(hsp_engine_context_t *hmw, float32_t *pSrc, float32_t *pOffset,
                                         float32_t *pDst, uint32_t nbSamples, uint32_t ioType);
hsp_core_status_t HSP_SEQ_VectScale_f32(hsp_engine_context_t *hmw, float32_t *pSrc, float32_t *pScale,
                                        float32_t *pDst, uint32_t nbSamples, uint32_t ioType);
hsp_core_status_t HSP_SEQ_VectMul_f32(hsp_engine_context_t *hmw, float32_t *pSrcA, float32_t *pSrcB,
                                      float32_t *pDst, uint32_t nbSamples, uint32_t ioType);
hsp_core_status_t HSP_SEQ_VectRms_f32(hsp_engine_context_t *hmw, float32_t *pSrc, float32_t *pDst, uint32_t nbSamples,
                                      uint32_t ioType);
hsp_core_status_t HSP_SEQ_VectSqrt_f32(hsp_engine_context_t *hmw, float32_t *pSrc, float32_t *pDst, uint32_t nbSamples,
                                       uint32_t ioType);
hsp_core_status_t HSP_SEQ_VectSub_f32(hsp_engine_context_t *hmw, float32_t *pSrcA, float32_t *pSrcB, float32_t *pDst,
                                      uint32_t nbSamples, uint32_t ioType);
hsp_core_status_t HSP_SEQ_VectAbsmax_f32(hsp_engine_context_t *hmw, float32_t *pSrc, float32_t *outVal,
                                         uint32_t *outIdx, uint32_t nbSamples, uint32_t ioType);
hsp_core_status_t HSP_SEQ_VectMulCos_f32(hsp_engine_context_t *hmw, float32_t *pSrc, uint32_t *pIndex,
                                         float32_t *pDst,
                                         uint32_t nbSamples, int32_t step, uint32_t ioType);
hsp_core_status_t HSP_SEQ_VectMulSin_f32(hsp_engine_context_t *hmw, float32_t *pSrc, uint32_t *pIndex,
                                         float32_t *pDst,
                                         uint32_t nbSamples, int32_t step, uint32_t ioType);
hsp_core_status_t HSP_SEQ_VectMax_f32(hsp_engine_context_t *hmw, float32_t *pSrc, float32_t *outVal,
                                      uint32_t *outIdx, uint32_t nbSamples, uint32_t ioType);
hsp_core_status_t HSP_SEQ_VectMin_f32(hsp_engine_context_t *hmw, float32_t *pSrc, float32_t *outVal,
                                      uint32_t *outIdx, uint32_t nbSamples, uint32_t ioType);
hsp_core_status_t HSP_SEQ_VectSat_f32(hsp_engine_context_t *hmw, float32_t *pSrc, float32_t *pSat, float32_t *pDst,
                                      uint32_t nbSamples, uint32_t *pRes, uint32_t ioType);
/**
  * @}
  */

/** @defgroup HSP_Vector_Exported_Functions_Group2  Exponential & Logarithmic Functions
  * @{
  */
hsp_core_status_t HSP_SEQ_VectExp_f32(hsp_engine_context_t *hmw, float32_t *pSrc, float32_t *pDst, uint32_t nbSamples,
                                      uint32_t ioType);
hsp_core_status_t HSP_SEQ_VectExp10_f32(hsp_engine_context_t *hmw, float32_t *pSrc, float32_t *pDst, uint32_t nbSamples,
                                        uint32_t ioType);
hsp_core_status_t HSP_SEQ_VectLn_f32(hsp_engine_context_t *hmw, float32_t *pSrc, float32_t *pDst, uint32_t nbSamples,
                                     uint32_t ioType);
hsp_core_status_t HSP_SEQ_VectLog10_f32(hsp_engine_context_t *hmw, float32_t *pSrc, float32_t *pDst, uint32_t nbSamples,
                                        uint32_t ioType);
hsp_core_status_t HSP_SEQ_VectFastLn_f32(hsp_engine_context_t *hmw, float32_t *pSrc, float32_t *pDst,
                                         uint32_t nbSamples,
                                         uint32_t ioType);
hsp_core_status_t HSP_SEQ_VectFastLog10_f32(hsp_engine_context_t *hmw, float32_t *pSrc, float32_t *pDst,
                                            uint32_t nbSamples,
                                            uint32_t ioType);
hsp_core_status_t HSP_SEQ_VectFastLog2_f32(hsp_engine_context_t *hmw, float32_t *pSrc, float32_t *pDst,
                                           uint32_t nbSamples,
                                           uint32_t ioType);
hsp_core_status_t HSP_SEQ_VectFastLogdB_f32(hsp_engine_context_t *hmw, float32_t *pSrc, float32_t *pDst,
                                            uint32_t nbSamples,
                                            uint32_t ioType);
hsp_core_status_t HSP_SEQ_VectFastExpe_f32(hsp_engine_context_t *hmw, float32_t *pSrc, float32_t *pDst,
                                           uint32_t nbSamples,
                                           uint32_t ioType);
hsp_core_status_t HSP_SEQ_VectFastExp10_f32(hsp_engine_context_t *hmw, float32_t *pSrc, float32_t *pDst,
                                            uint32_t nbSamples,
                                            uint32_t ioType);
hsp_core_status_t HSP_SEQ_VectFastExp2_f32(hsp_engine_context_t *hmw, float32_t *pSrc, float32_t *pDst,
                                           uint32_t nbSamples,
                                           uint32_t ioType);
hsp_core_status_t HSP_SEQ_VectFastExpdB_f32(hsp_engine_context_t *hmw, float32_t *pSrc, float32_t *pDst,
                                            uint32_t nbSamples,
                                            uint32_t ioType);

/**
  * @}
  */

/** @defgroup HSP_Vector_Exported_Functions_Group3 Trigonometric Functions
  * @{
  */
hsp_core_status_t HSP_SEQ_VectCos_f32(hsp_engine_context_t *hmw, float32_t *pSrc, float32_t *pDst, uint32_t nbSamples,
                                      uint32_t ioType);
hsp_core_status_t HSP_SEQ_VectSin_f32(hsp_engine_context_t *hmw, float32_t *pSrc, float32_t *pDst, uint32_t nbSamples,
                                      uint32_t ioType);
hsp_core_status_t HSP_SEQ_VectSinCos_f32(hsp_engine_context_t *hmw, float32_t *pSrc, float32_t *pDst,
                                         uint32_t nbSamples, uint32_t ioType);
hsp_core_status_t HSP_SEQ_VectAtan2_f32(hsp_engine_context_t *hmw, float32_t *pSrcA, float32_t *pSrcB,
                                        float32_t *pDst, uint32_t nbSamples, uint32_t ioType);
/**
  * @}
  */

/** @defgroup HSP_Vector_Exported_Functions_Group4  Support Functions
  * @{
  */
hsp_core_status_t HSP_SEQ_VectF2I(hsp_engine_context_t *hmw, float32_t *pSrc, int32_t *pDst, uint32_t nbSamples,
                                  uint32_t ioType);
hsp_core_status_t HSP_SEQ_VectF2Q15(hsp_engine_context_t *hmw, float32_t *pSrc, int32_t *pDst, uint32_t nbSamples,
                                    uint32_t ioType);
hsp_core_status_t HSP_SEQ_VectF2Q31(hsp_engine_context_t *hmw, float32_t *pSrc, int32_t *pDst, uint32_t nbSamples,
                                    uint32_t ioType);
hsp_core_status_t HSP_SEQ_VectF2U(hsp_engine_context_t *hmw, float32_t *pSrc, uint32_t *pDst, uint32_t nbSamples,
                                  uint32_t ioType);
hsp_core_status_t HSP_SEQ_VectQ152F(hsp_engine_context_t *hmw, int32_t *pSrc, float32_t *pDst, uint32_t nbSamples,
                                    uint32_t ioType);
hsp_core_status_t HSP_SEQ_VectQ312F(hsp_engine_context_t *hmw, int32_t *pSrc, float32_t *pDst, uint32_t nbSamples,
                                    uint32_t ioType);
hsp_core_status_t HSP_SEQ_VectI2F(hsp_engine_context_t *hmw, int32_t *pSrc, float32_t *pDst, uint32_t nbSamples,
                                  uint32_t ioType);
hsp_core_status_t HSP_SEQ_VectU2F(hsp_engine_context_t *hmw, uint32_t *pSrc, float32_t *pDst, uint32_t nbSamples,
                                  uint32_t ioType);
hsp_core_status_t HSP_SEQ_Vect24s2F(hsp_engine_context_t *hmw, int32_t *pSrc, float32_t *pDst, uint32_t nbSamples,
                                    uint32_t ioType);
#if defined(HSP_CMD_VEC_F2U8)
hsp_core_status_t HSP_SEQ_VectF2U8(hsp_engine_context_t *hmw, float32_t *pSrc, uint8_t *pDst, uint32_t nbSamples,
                                   uint32_t ioType);
#endif /* HSP_CMD_VEC_F2U8 */
#if defined(HSP_CMD_VEC_F2I8)
hsp_core_status_t HSP_SEQ_VectF2I8(hsp_engine_context_t *hmw, float32_t *pSrc, int8_t *pDst, uint32_t nbSamples,
                                   uint32_t ioType);
#endif /* HSP_CMD_VEC_F2I8 */
#if defined(HSP_CMD_VEC_F2U8Q)
hsp_core_status_t HSP_SEQ_VectF2U8Q(hsp_engine_context_t *hmw, float32_t *pSrc, float32_t *pCfg, uint8_t *pDst,
                                    uint32_t nbSamples, uint32_t ioType);
#endif /* HSP_CMD_VEC_F2U8Q */
#if defined(HSP_CMD_VEC_F2I8Q)
hsp_core_status_t HSP_SEQ_VectF2I8Q(hsp_engine_context_t *hmw, float32_t *pSrc, float32_t *pCfg, int8_t *pDst,
                                    uint32_t nbSamples, uint32_t ioType);
#endif /* HSP_CMD_VEC_F2I8Q */
#if defined(HSP_CMD_VEC_U82F)
hsp_core_status_t HSP_SEQ_VectU82F(hsp_engine_context_t *hmw, uint8_t *pSrc, float32_t *pDst,
                                   uint32_t nbSamples, uint32_t ioType);
#endif /* HSP_CMD_VEC_U82F */
#if defined(HSP_CMD_VEC_I82F)
hsp_core_status_t HSP_SEQ_VectI82F(hsp_engine_context_t *hmw, int8_t *pSrc, float32_t *pDst,
                                   uint32_t nbSamples, uint32_t ioType);
#endif /* HSP_CMD_VEC_I82F */
#if defined(HSP_CMD_VEC_F2U16)
hsp_core_status_t HSP_SEQ_VectF2U16(hsp_engine_context_t *hmw, float32_t *pSrc, uint16_t *pDst, uint32_t nbSamples,
                                    uint32_t ioType);
#endif /* HSP_CMD_VEC_F2U16 */
#if defined(HSP_CMD_VEC_F2I16)
hsp_core_status_t HSP_SEQ_VectF2I16(hsp_engine_context_t *hmw, float32_t *pSrc, int16_t *pDst, uint32_t nbSamples,
                                    uint32_t ioType);
#endif /* HSP_CMD_VEC_F2I16 */
#if defined(HSP_CMD_VEC_U162F)
hsp_core_status_t HSP_SEQ_VectU162F(hsp_engine_context_t *hmw, uint16_t *pSrc, float32_t *pDst,
                                    uint32_t nbSamples, uint32_t ioType);
#endif /* HSP_CMD_VEC_U162F */
#if defined(HSP_CMD_VEC_I162F)
hsp_core_status_t HSP_SEQ_VectI162F(hsp_engine_context_t *hmw, int16_t *pSrc, float32_t *pDst,
                                    uint32_t nbSamples, uint32_t ioType);
#endif /* HSP_CMD_VEC_I162F */
hsp_core_status_t HSP_SEQ_VectSet_f32(hsp_engine_context_t *hmw, float32_t *pSrc, float32_t *pDst, uint32_t nbSamples,
                                      uint32_t ioType);
hsp_core_status_t HSP_SEQ_VectISet_f32(hsp_engine_context_t *hmw, float32_t value, float32_t *pDst, uint32_t nbSamples,
                                       uint32_t ioType);
hsp_core_status_t HSP_SEQ_VectCopy_f32(hsp_engine_context_t *hmw, float32_t *pSrc, float32_t *pDst, uint32_t nbSamples,
                                       uint32_t ioType);
hsp_core_status_t HSP_SEQ_VectZins_f32(hsp_engine_context_t *hmw, float32_t *pSrc, uint32_t znb, float32_t *pDst,
                                       uint32_t sizeIn, uint32_t ioType);
hsp_core_status_t HSP_SEQ_VectCmp_f32(hsp_engine_context_t *hmw, float32_t *pSrc, float32_t *pLim, uint32_t *pRes,
                                      uint32_t nbSamples, hsp_proclist_cmp_vect_cond_cmd_t cmpType, uint32_t ioType);
#if defined(__HSP_DMA__)
#if defined(HSP_CMD_VEC_FSQRT_F32)
hsp_core_status_t HSP_SEQ_VectFastSqrt_f32(hsp_engine_context_t *hmw, float32_t *pSrc, float32_t *pDst,
                                           uint32_t nbSamples, uint32_t ioType);
#endif /* HSP_CMD_VEC_FSQRT_F32 */
#if defined(HSP_CMD_VEC_FRSQRT_F32)
hsp_core_status_t HSP_SEQ_VectFastRsqrt_f32(hsp_engine_context_t *hmw, float32_t *pSrc, float32_t *pDst,
                                            uint32_t nbSamples, uint32_t ioType);
#endif /* HSP_CMD_VEC_FRSQRT_F32 */
#if defined(HSP_CMD_VEC_REC_F32)
hsp_core_status_t HSP_SEQ_VectRec_f32(hsp_engine_context_t *hmw, float32_t *pSrc, float32_t *pDst,
                                      uint32_t nbSamples, uint32_t ioType);
#endif /* HSP_CMD_VEC_REC_F32 */
#if defined(HSP_CMD_VEC_FRECP_F32)
hsp_core_status_t HSP_SEQ_VectFastRecPos_f32(hsp_engine_context_t *hmw, float32_t *pSrc, float32_t *pDst,
                                             uint32_t nbSamples, uint32_t ioType);
#endif /* HSP_CMD_VEC_FRECP_F32 */
#if defined(HSP_CMD_VEC_POW_F32)
hsp_core_status_t HSP_SEQ_VectPower_f32(hsp_engine_context_t *hmw, float32_t *pBase, float32_t *pExponent,
                                        float32_t *pDst, uint32_t nbSamples, uint32_t ioType);
#endif /* HSP_CMD_VEC_POW_F32 */
#if defined(HSP_CMD_VEC_FPOW_F32)
hsp_core_status_t HSP_SEQ_VectFastPower_f32(hsp_engine_context_t *hmw, float32_t *pBase, float32_t *pExponent,
                                            float32_t *pDst, uint32_t nbSamples, uint32_t ioType);
#endif /* HSP_CMD_VEC_FPOW_F32 */
#endif /* __HSP_DMA__ */
/**
  * @}
  */

#if defined(__HSP_DMA__)
/**
  * @defgroup HSP_Vector_Exported_Functions_Group5  Memory Transfer
  * @{
  */
hsp_core_status_t HSP_SEQ_Ext2Int(hsp_engine_context_t *hmw, float32_t *pSrc, float32_t *pDst, uint32_t nbElems,
                                  uint32_t eltFormat, uint32_t iJump, uint32_t nbIterIn, uint32_t offsetIn,
                                  uint32_t oJump, uint32_t nbIterOu, uint32_t offsetOu);
hsp_core_status_t HSP_SEQ_Int2Ext(hsp_engine_context_t *hmw, float32_t *pSrc, float32_t *pDst, uint32_t nbElems,
                                  uint32_t eltFormat, uint32_t iJump, uint32_t nbIterIn, uint32_t offsetIn,
                                  uint32_t oJump, uint32_t nbIterOu, uint32_t offsetOu);
hsp_core_status_t HSP_SEQ_Int2Int(hsp_engine_context_t *hmw, float32_t *pSrc, float32_t *pDst, uint32_t nbElems,
                                  uint32_t eltFormat, uint32_t iJump, uint32_t nbIterIn, uint32_t offsetIn,
                                  uint32_t oJump, uint32_t nbIterOu, uint32_t offsetOu);
hsp_core_status_t HSP_SEQ_BgndExt2Int(hsp_engine_context_t *hmw, float32_t *pSrc, float32_t *pDst,
                                      uint32_t nbElems, uint32_t eltFormat, uint32_t chanId, uint32_t iJump,
                                      uint32_t nbIterIn, uint32_t offsetIn, uint32_t oJump, uint32_t nbIterOu,
                                      uint32_t offsetOu, uint32_t nextOffsetIn, uint32_t nextOffsetOu);
hsp_core_status_t HSP_SEQ_BgndInt2Ext(hsp_engine_context_t *hmw, float32_t *pSrc, float32_t *pDst,
                                      uint32_t nbElems, uint32_t eltFormat, uint32_t chanId, uint32_t iJump,
                                      uint32_t nbIterIn, uint32_t offsetIn, uint32_t oJump, uint32_t nbIterOu,
                                      uint32_t offsetOu, uint32_t nextOffsetIn, uint32_t nextOffsetOu);
hsp_core_status_t HSP_SEQ_BgndInt2Int(hsp_engine_context_t *hmw, float32_t *pSrc, float32_t *pDst,
                                      uint32_t nbElems, uint32_t eltFormat, uint32_t chanId, uint32_t iJump,
                                      uint32_t nbIterIn, uint32_t offsetIn, uint32_t oJump, uint32_t nbIterOu,
                                      uint32_t offsetOu, uint32_t nextOffsetIn, uint32_t nextOffsetOu);
hsp_core_status_t HSP_SEQ_BgndCmd(hsp_engine_context_t *hmw, uint32_t cmd, uint32_t chanId);

/**
  * @}
  */
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

#endif /* HSP_PROCLIST_VECTOR_H */
