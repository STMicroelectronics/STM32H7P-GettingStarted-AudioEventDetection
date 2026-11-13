/**
  ******************************************************************************
  * @file    preproc_dpu.h
  * @author  MCD Application Team
  * @brief   Header for preproc_dpu.c module
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
#ifndef _PREPROC_DPU_H
#define _PREPROC_DPU_H

/* Includes ------------------------------------------------------------------*/
#include "dpu.h"
#include "dpu_config.h"
#include "feature_extraction.h"
#include "mel_filterbank.h"
#include "user_mel_tables.h"

/* Exported constants --------------------------------------------------------*/

/* Exported types ------------------------------------------------------------*/
typedef enum {
  SPECTROGRAM_BYPASS,
  SPECTROGRAM_MEL,
  SPECTROGRAM_LOG_MEL,
  SPECTROGRAM_MFCC
}spectrogram_type_t;

typedef struct _pre_proc_dpu_ctx_t{
  spectrogram_type_t         type;

#ifndef USE_HSP
  arm_rfft_fast_instance_f32 S_Rfft;
  float32_t pSpectrScratchBuffer1[AI_SPECT_NFFT];
  float32_t pSpectrScratchBuffer2[AI_SPECT_NFFT];
#endif

  MelFilterTypeDef           S_MelFilter;
  SpectrogramTypeDef         S_Spectr;
  MelSpectrogramTypeDef      S_MelSpectr;
  LogMelSpectrogramTypeDef   S_LogMelSpectr;
  DCT_InstanceTypeDef        S_DCT;
  MfccTypeDef                S_Mfcc;

  float32_t out_Q_inv_scale;
  int8_t    out_Q_offset;
}pre_proc_dpu_ctx_t;


/* Exported functions --------------------------------------------------------*/
/**
 * @brief Initializes the audio preprocessing context.
 * @param px_ctx Pointer to the preprocessing context.
 * @return DPU_OK on success, otherwise DPU_ERROR.
 */
DPU_StatusTypeDef pre_proc_dpu_init(pre_proc_dpu_ctx_t *px_ctx);
/**
 * @brief Generates a quantized log-Mel spectrogram from audio samples.
 * @param pxCtx Pointer to the preprocessing context.
 * @param pDataIn Pointer to the input audio samples.
 * @param p_spectro Pointer to the output spectrogram buffer.
 * @return DPU_OK on success, otherwise DPU_ERROR.
 */
DPU_StatusTypeDef pre_proc_dpu_process(pre_proc_dpu_ctx_t *pxCtx, volatile uint8_t *pDataIn, int8_t *p_spectro);

#endif /* _PREPROC_DPU_H*/
