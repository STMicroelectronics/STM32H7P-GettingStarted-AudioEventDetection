/**
  ******************************************************************************
  * @file    audiopipeline_preproc.c
  * @author  MCD Application Team
  * @brief   This file is implementing pre-processing functions that are making
  * 		 use of Audio pre-processing libraries
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */


/* Includes ------------------------------------------------------------------*/
#include "audiopipeline_preproc.h"
#include "main.h"
#include "cpu_stats.h"
#include "ai_device_adaptor.h"
#ifdef USE_HSP
#include "hsp_cnn.h"
#include "hsp_direct_command.h"
#include "hsp_bram.h"
#include "hsp_bram_if.h"
#endif


/* Private defines ---------------------------------------------------------- */
#define AI_AUDIOPIPELINE_G_TO_MS_2 (9.8F)
#define AI_LSB_16B       (1.0F/32768)

/* External functions --------------------------------------------------------*/
#ifdef USE_HSP
extern hsp_core_handle_t hmw;
#endif

/**
 * @brief initializes preprocessing for Audio
 * @param pxCtx pointer to preprocessing context
 * @retval AUDIOPIPELINE_OK if success, AUDIOPIPELINE_ERROR else
 */
AudioPipeline_StatusTypeDef AudioPipeline_PreprocInit(AudioPreProcCtx_t *pxCtx)
{

  uint32_t pad;

  ASSERT_DBG_PARAM( CTRL_X_CUBE_AI_SPECTROGRAM_NFFT >= CTRL_X_CUBE_AI_SPECTROGRAM_WINDOW_LENGTH );
  ASSERT_DBG_PARAM( CTRL_X_CUBE_AI_SPECTROGRAM_NFFT >= CTRL_X_CUBE_AI_SPECTROGRAM_NMEL);

  pxCtx->type = SPECTROGRAM_LOG_MEL;

  pxCtx->out_Q_inv_scale = 0.0F;
  pxCtx->out_Q_offset  = 0;

  /* Init RFFT */
#ifndef USE_HSP
  arm_rfft_fast_init_f32(&pxCtx->S_Rfft, CTRL_X_CUBE_AI_SPECTROGRAM_NFFT);

  /* Init Spectrogram */
  pxCtx->S_Spectr.pRfft                    = &pxCtx->S_Rfft;
#endif
  pxCtx->S_Spectr.Type                     = CTRL_X_CUBE_AI_SPECTROGRAM_TYPE;
#ifdef USE_HSP
  pxCtx->S_Spectr.pWindow                  = (float32_t *) HSP_BRAM_Malloc(&hmw, CTRL_X_CUBE_AI_SPECTROGRAM_WINDOW_LENGTH/2, HSP_BRAM_ALLOCATION_DEFAULT);
#else
  pxCtx->S_Spectr.pWindow                  = (float32_t *) CTRL_X_CUBE_AI_SPECTROGRAM_WIN;
#endif
  pxCtx->S_Spectr.SampRate                 = CTRL_X_CUBE_AI_SENSOR_ODR;
  pxCtx->S_Spectr.FrameLen                 = CTRL_X_CUBE_AI_SPECTROGRAM_WINDOW_LENGTH;
  pxCtx->S_Spectr.FFTLen                   = CTRL_X_CUBE_AI_SPECTROGRAM_NFFT;

#ifdef USE_HSP
  pxCtx->S_Spectr.pScratch1                = (float32_t *) HSP_BRAM_Malloc(&hmw, CTRL_X_CUBE_AI_SPECTROGRAM_NFFT, HSP_BRAM_ALLOCATION_DEFAULT);
  pxCtx->S_Spectr.pScratch2                = (float32_t *) HSP_BRAM_Malloc(&hmw, CTRL_X_CUBE_AI_SPECTROGRAM_NFFT, HSP_BRAM_ALLOCATION_DEFAULT);
#else
  pxCtx->S_Spectr.pScratch1                = pxCtx->pSpectrScratchBuffer1;
  pxCtx->S_Spectr.pScratch2                = pxCtx->pSpectrScratchBuffer2;
#endif

  pad                                      = CTRL_X_CUBE_AI_SPECTROGRAM_NFFT - CTRL_X_CUBE_AI_SPECTROGRAM_WINDOW_LENGTH;
  pxCtx->S_Spectr.pad_left                 = pad/2;
  pxCtx->S_Spectr.pad_right                = pad/2 + (pad & 0x1);

  /* Init mel filterbank */
#ifdef USE_HSP
  pxCtx->S_MelFilter.pStartIndices         = (uint32_t *)  HSP_BRAM_Malloc(&hmw, CTRL_X_CUBE_AI_SPECTROGRAM_NMEL, HSP_BRAM_ALLOCATION_DEFAULT);
  pxCtx->S_MelFilter.pBandLens             = (uint32_t *)  HSP_BRAM_Malloc(&hmw, CTRL_X_CUBE_AI_SPECTROGRAM_NMEL, HSP_BRAM_ALLOCATION_DEFAULT);
  pxCtx->S_MelFilter.pCoefficients         = (float32_t *) HSP_BRAM_Malloc(&hmw, 462, HSP_BRAM_ALLOCATION_DEFAULT);
#else
  pxCtx->S_MelFilter.pStartIndices         = (uint32_t *)  CTRL_X_CUBE_AI_SPECTROGRAM_MEL_START_IDX;
  pxCtx->S_MelFilter.pCoefficients         = (float32_t *) CTRL_X_CUBE_AI_SPECTROGRAM_MEL_LUT;
#endif
  pxCtx->S_MelFilter.pStopIndices          = (uint32_t *)  CTRL_X_CUBE_AI_SPECTROGRAM_MEL_STOP_IDX;
  pxCtx->S_MelFilter.NumMels               = CTRL_X_CUBE_AI_SPECTROGRAM_NMEL;
  pxCtx->S_MelFilter.FFTLen                = CTRL_X_CUBE_AI_SPECTROGRAM_NFFT;
  pxCtx->S_MelFilter.SampRate              = (uint32_t) CTRL_X_CUBE_AI_SENSOR_ODR;
  pxCtx->S_MelFilter.FMin                  = (float32_t) CTRL_X_CUBE_AI_SPECTROGRAM_FMIN;
  pxCtx->S_MelFilter.FMax                  = (float32_t) CTRL_X_CUBE_AI_SPECTROGRAM_FMAX;
  pxCtx->S_MelFilter.Formula               = CTRL_X_CUBE_AI_SPECTROGRAM_FORMULA;
  pxCtx->S_MelFilter.Normalize             = CTRL_X_CUBE_AI_SPECTROGRAM_NORMALIZE;
  pxCtx->S_MelFilter.Mel2F                 = 1U;

  /* Init MelSpectrogram */
  pxCtx->S_MelSpectr.SpectrogramConf       = &pxCtx->S_Spectr;
  pxCtx->S_MelSpectr.MelFilter             = &pxCtx->S_MelFilter;

  /* Init LogMelSpectrogram */
  pxCtx->S_LogMelSpectr.MelSpectrogramConf = &pxCtx->S_MelSpectr;
  pxCtx->S_LogMelSpectr.LogFormula         = CTRL_X_CUBE_AI_SPECTROGRAM_LOG_FORMULA;
  pxCtx->S_LogMelSpectr.Ref                = 1.0f;
  pxCtx->S_LogMelSpectr.TopdB              = HUGE_VALF;

#ifdef USE_HSP
    memcpy(pxCtx->S_Spectr.pWindow, CTRL_X_CUBE_AI_SPECTROGRAM_WIN, 4 * CTRL_X_CUBE_AI_SPECTROGRAM_WINDOW_LENGTH/2);
    memcpy(pxCtx->S_MelFilter.pStartIndices, CTRL_X_CUBE_AI_SPECTROGRAM_MEL_START_IDX, 4 * CTRL_X_CUBE_AI_SPECTROGRAM_NMEL);
    memcpy(pxCtx->S_MelFilter.pCoefficients, CTRL_X_CUBE_AI_SPECTROGRAM_MEL_LUT, 4 * 462);
    for(int i = 0; i < CTRL_X_CUBE_AI_SPECTROGRAM_NMEL; i++)
    {
        pxCtx->S_MelFilter.pBandLens[i] = ((uint32_t *)  CTRL_X_CUBE_AI_SPECTROGRAM_MEL_STOP_IDX)[i] - ((uint32_t *)  CTRL_X_CUBE_AI_SPECTROGRAM_MEL_START_IDX)[i] + 1;  
    }

#endif

  LogInfo("MEL spectrogram %d mel x %d col\n\r", CTRL_X_CUBE_AI_SPECTROGRAM_NMEL, CTRL_X_CUBE_AI_SPECTROGRAM_COL);
  LogInfo("- sampling freq : %u Hz\n\r", (uint32_t)CTRL_X_CUBE_AI_SENSOR_ODR);
  LogInfo("- acq period    : %u ms\n\r", (uint32_t)CTRL_X_CUBE_AI_ACQ_LENGTH_MS);
  LogInfo("- window length : %u samples\n\r", CTRL_X_CUBE_AI_SPECTROGRAM_WINDOW_LENGTH);
  LogInfo("- hop length    : %u samples\n\r", CTRL_X_CUBE_AI_SPECTROGRAM_HOP_LENGTH);

#ifdef USE_HSP
  LogInfo("Free BRAM DEFAULT : %u\n\r", HSP_BRAM_IF_GetFreeSize(&hmw.hbram, HSP_BRAM_ALLOCATION_DEFAULT));
  LogInfo("Free BRAM PERSISTENT : %u\n\r", HSP_BRAM_IF_GetFreeSize(&hmw.hbram, HSP_BRAM_ALLOCATION_PERSISTENT));
#endif


  return AUDIOPIPELINE_OK;
}

/**
 * @brief spectral preprocessing Audio samples
 * @param pxCtx pointer to preprocessing context
 * @param pDataIn pointer to audio impit samples
 * @param p_spectro pointer to output spectrgramme
 * @retval AUDIOPIPELINE_OK if success, AUDIOPIPELINE_ERROR else
 */
AudioPipeline_StatusTypeDef AudioPipeline_Preproc(AudioPreProcCtx_t * pxCtx, uint8_t *pDataIn, int8_t *p_spectro)
{
  ASSERT_DBG_PARAM( NULL != pxCtx );
  ASSERT_DBG_PARAM( SPECTROGRAM_LOG_MEL == pxCtx->type );
  ASSERT_DBG_PARAM( CTRL_X_CUBE_AI_SPECTROGRAM_NMEL == pxCtx->S_MelFilter.NumMels);

  int16_t *p_in;

  int8_t out_of_preproc[CTRL_X_CUBE_AI_SPECTROGRAM_NMEL] ;

  port_dwt_reset();

#ifdef USE_HSP
    memcpy(pxCtx->S_Spectr.pWindow, CTRL_X_CUBE_AI_SPECTROGRAM_WIN, 4 * CTRL_X_CUBE_AI_SPECTROGRAM_WINDOW_LENGTH/2);
    memcpy(pxCtx->S_MelFilter.pStartIndices, CTRL_X_CUBE_AI_SPECTROGRAM_MEL_START_IDX, 4 * CTRL_X_CUBE_AI_SPECTROGRAM_NMEL);
    memcpy(pxCtx->S_MelFilter.pCoefficients, CTRL_X_CUBE_AI_SPECTROGRAM_MEL_LUT, 4 * 462);
    for(int i = 0; i < CTRL_X_CUBE_AI_SPECTROGRAM_NMEL; i++)
    {
        pxCtx->S_MelFilter.pBandLens[i] = ((uint32_t *)  CTRL_X_CUBE_AI_SPECTROGRAM_MEL_STOP_IDX)[i] - ((uint32_t *)  CTRL_X_CUBE_AI_SPECTROGRAM_MEL_START_IDX)[i] + 1;  
    }
#endif

  /* Create a quantized Mel-scaled spectrogram column */
  for (uint32_t i = 0; i < CTRL_X_CUBE_AI_SPECTROGRAM_COL; i++ )
  {
    p_in = (int16_t *)pDataIn + CTRL_X_CUBE_AI_SPECTROGRAM_HOP_LENGTH * i;

    LogMelSpectrogramColumn_q15_Q8(&pxCtx->S_LogMelSpectr, p_in, out_of_preproc, pxCtx->out_Q_offset, pxCtx->out_Q_inv_scale);

#ifdef NO_TRANSPOSE
    memcpy(p_spectro + i * pxCtx->S_MelFilter.NumMels, out_of_preproc, pxCtx->S_MelFilter.NumMels);
#else
    /* transpose */
    for (uint32_t j=0; j < pxCtx->S_MelFilter.NumMels; j++ )
    {
      p_spectro[i+CTRL_X_CUBE_AI_SPECTROGRAM_COL*j] = out_of_preproc[j];
    }
#endif
     mcu_cache_clean_invalidate_range((uint32_t)p_spectro, (uint32_t)(p_spectro+
		  CTRL_X_CUBE_AI_SPECTROGRAM_NMEL*CTRL_X_CUBE_AI_SPECTROGRAM_COL));
  }

  time_stats_store(TIME_STAT_PRE_PROC,port_dwt_get_cycles()*1000.0F/port_hal_get_cpu_freq());

  return AUDIOPIPELINE_OK;
}
