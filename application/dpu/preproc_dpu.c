/**
  ******************************************************************************
  * @file    preproc_dpu.c
  * @author  MCD Application Team
  * @brief   This file is implementing pre-processing functions that are making
  *      use of Audio pre-processing libraries
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


/* Includes ------------------------------------------------------------------*/
#include "preproc_dpu.h"
#include "app_config.h"
#include "main.h"
#include "mcu_cache.h"
#include "cpu_stats.h"
#include "ai_device_adaptor.h"

#ifdef USE_HSP
#include "mx_hsp_engine_app.h"
hsp_engine_context_t *p_hmw;
#endif /* USE_HSP */

/**
 * @brief Initializes the audio preprocessing context.
 * @param p_ctx Pointer to the preprocessing context.
 * @return DPU_OK on success, otherwise DPU_ERROR.
 */
DPU_StatusTypeDef pre_proc_dpu_init(pre_proc_dpu_ctx_t *p_ctx)
{
  ASSERT_DBG_PARAM(AI_SPECT_NFFT >= AI_SPECT_WIN_LEN);
  ASSERT_DBG_PARAM(AI_SPECT_NFFT >= AI_SPECT_NMEL);
  uint32_t pad = AI_SPECT_NFFT - AI_SPECT_WIN_LEN;
  p_ctx->S_Spectr.Type                     = AI_SPECT_TYPE;
  p_ctx->S_Spectr.pWindow                  = (float32_t *)user_win;
  p_ctx->S_Spectr.SampRate                 = AI_SENSOR_ODR;
  p_ctx->S_Spectr.FrameLen                 = AI_SPECT_WIN_LEN;
  p_ctx->S_Spectr.FFTLen                   = AI_SPECT_NFFT;
  p_ctx->S_Spectr.pad_left                 = pad / 2;
  p_ctx->S_Spectr.pad_right                = pad / 2 + (pad & 0x1);
  p_ctx->S_MelFilter.pStartIndices         = (uint32_t *)user_melFilterStartIndices;
  p_ctx->S_MelFilter.pStopIndices          = (uint32_t *)user_melFilterStopIndices;
  p_ctx->S_MelFilter.pCoefficients         = (float32_t *)user_melFilterLut;
  p_ctx->S_MelFilter.NumMels               = AI_SPECT_NMEL;
  p_ctx->S_MelFilter.FFTLen                = AI_SPECT_NFFT;
  p_ctx->S_MelFilter.SampRate              = AI_SENSOR_ODR;
  p_ctx->S_MelFilter.FMin                  = AI_SPECT_FMIN;
  p_ctx->S_MelFilter.FMax                  = AI_SPECT_FMAX;
  p_ctx->S_MelFilter.Formula               = AI_SPECT_FORMULA;
  p_ctx->S_MelFilter.Normalize             = AI_SPECT_NORMALIZE;
  p_ctx->S_MelFilter.Mel2F                 = 1U;
  p_ctx->S_MelSpectr.SpectrogramConf       = &p_ctx->S_Spectr;
  p_ctx->S_MelSpectr.MelFilter             = &p_ctx->S_MelFilter;
  p_ctx->S_LogMelSpectr.MelSpectrogramConf = &p_ctx->S_MelSpectr;
  p_ctx->S_LogMelSpectr.LogFormula         = AI_SPECT_LOG_FORMULA;
  p_ctx->S_LogMelSpectr.Ref                = 1.0f;
  p_ctx->S_LogMelSpectr.TopdB              = HUGE_VALF;
#ifdef USE_HSP
  p_hmw = mx_hsp_engine_get_context_hsp1();
  p_ctx->S_Spectr.pWindow = (float32_t *)HSP_BRAM_Malloc(p_hmw, AI_SPECT_WIN_LEN / 2, HSP_BRAM_ALLOCATION_DEFAULT);
  p_ctx->S_Spectr.pScratch1 = (float32_t *)HSP_BRAM_Malloc(p_hmw, AI_SPECT_NFFT, HSP_BRAM_ALLOCATION_DEFAULT);
  p_ctx->S_Spectr.pScratch2 = (float32_t *)HSP_BRAM_Malloc(p_hmw, AI_SPECT_NFFT, HSP_BRAM_ALLOCATION_DEFAULT);
  p_ctx->S_MelFilter.pStartIndices = (uint32_t *)HSP_BRAM_Malloc(p_hmw, AI_SPECT_NMEL, HSP_BRAM_ALLOCATION_DEFAULT);
  p_ctx->S_MelFilter.pBandLens = (uint32_t *)HSP_BRAM_Malloc(p_hmw, AI_SPECT_NMEL, HSP_BRAM_ALLOCATION_DEFAULT);
  p_ctx->S_MelFilter.pCoefficients = (float32_t *)HSP_BRAM_Malloc(p_hmw, AI_SPECT_MEL_FILT_LEN, HSP_BRAM_ALLOCATION_DEFAULT);
  memcpy(p_ctx->S_Spectr.pWindow, user_win, 4 * AI_SPECT_WIN_LEN / 2);
  memcpy(p_ctx->S_MelFilter.pStartIndices, user_melFilterStartIndices, 4 * AI_SPECT_NMEL);
  memcpy(p_ctx->S_MelFilter.pCoefficients, user_melFilterLut, 4 * AI_SPECT_MEL_FILT_LEN);
  for (int i = 0; i < AI_SPECT_NMEL; i++)
  {
    p_ctx->S_MelFilter.pBandLens[i] = ((uint32_t *)user_melFilterStopIndices)[i] -
                                      ((uint32_t *)user_melFilterStartIndices)[i] + 1;
  }
#else
  arm_rfft_fast_init_f32(&p_ctx->S_Rfft, AI_SPECT_NFFT);
  p_ctx->S_Spectr.pRfft                    = &p_ctx->S_Rfft;
  p_ctx->S_Spectr.pScratch1                = p_ctx->pSpectrScratchBuffer1;
  p_ctx->S_Spectr.pScratch2                = p_ctx->pSpectrScratchBuffer2;
#endif /* USE_HSP */
  PRINTF("MEL spectrogram %d mel x %d col\n\r", AI_SPECT_NMEL, AI_SPECT_COL);
  PRINTF("- window length : %u samples\n\r", AI_SPECT_WIN_LEN);
  PRINTF("- hop length    : %u samples\n\r", AI_SPECT_HOP_LEN);
  return DPU_OK;
}
/**
 * @brief Converts an audio buffer into a quantized log-Mel spectrogram.
 * @param p_ctx Pointer to the preprocessing context.
 * @param p_data_in Pointer to the input audio samples.
 * @param p_spectro Pointer to the output spectrogram buffer.
 * @return DPU_OK on success, otherwise DPU_ERROR.
 */
DPU_StatusTypeDef pre_proc_dpu_process(pre_proc_dpu_ctx_t *p_ctx,
                                       volatile uint8_t *p_data_in,
                                       int8_t *p_spectro)
{
  ASSERT_DBG_PARAM(NULL != p_ctx);

  int16_t *p_in;
  int8_t out_of_preproc[AI_SPECT_NMEL];
  port_dwt_reset();

#ifdef USE_HSP
    memcpy(p_ctx->S_Spectr.pWindow, user_win, 4 * AI_SPECT_WIN_LEN / 2);
        memcpy(p_ctx->S_MelFilter.pStartIndices, user_melFilterStartIndices,
          4 * AI_SPECT_NMEL);
    memcpy(p_ctx->S_MelFilter.pCoefficients, user_melFilterLut, 4 * AI_SPECT_MEL_FILT_LEN);
    for (int i = 0; i < AI_SPECT_NMEL; i++)
    {
      p_ctx->S_MelFilter.pBandLens[i] = ((uint32_t *)user_melFilterStopIndices)[i] -
                                        ((uint32_t *)user_melFilterStartIndices)[i] + 1;
    }
#endif

  /* Create a quantized Mel-scaled spectrogram column */
  for (uint32_t i = 0; i < AI_SPECT_COL; i++)
  {
    p_in = (int16_t *)p_data_in + AI_SPECT_HOP_LEN * i;

    LogMelSpectrogramColumn_q15_Q8(&p_ctx->S_LogMelSpectr, p_in,
                     out_of_preproc, p_ctx->out_Q_offset,
                     p_ctx->out_Q_inv_scale);

#if (AI_MODEL_TRANSPOSE == 1U)
    /* transpose */
    for (uint32_t j = 0; j < p_ctx->S_MelFilter.NumMels; j++)
    {
      p_spectro[i + AI_SPECT_COL * j] = out_of_preproc[j];
    }

#else
    memcpy(p_spectro + i * p_ctx->S_MelFilter.NumMels,
              out_of_preproc, p_ctx->S_MelFilter.NumMels);
#endif /* AI_MODEL_TRANSPOSE */
  }
  mcu_cache_clean_range((uint32_t)p_spectro,
                        (uint32_t)(p_spectro + AI_SPECT_NMEL * AI_SPECT_COL));
  time_stats_store(TIME_STAT_PRE_PROC,
                   port_dwt_get_cycles() * 1000.0F / port_hal_get_cpu_freq());
  return DPU_OK;
}
