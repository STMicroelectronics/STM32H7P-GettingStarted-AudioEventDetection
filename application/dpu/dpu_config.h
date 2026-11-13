/**
  ******************************************************************************
  * @file    dpu_config.h
  * @author  STMicroelectronics - AIS - MCD Team
  * @version $Version$
  * @date    $Date$
  * @brief   Configure the getting started functionality
  *
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
#ifndef DPU_CONFIG_H_
#define DPU_CONFIG_H_

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* Includes ------------------------------------------------------------------*/
#include "ai_model_config.h"

/* Exported constants --------------------------------------------------------*/
#ifndef AI_MODEL_CLASS_NUMBER
#define AI_MODEL_CLASS_NUMBER  (5U)
#endif /* !AI_MODEL_CLASS_NUMBER */
#ifndef AI_MODEL_CLASS_LIST
#define AI_MODEL_CLASS_LIST    {"chirping_birds","clapping",\
                                                  "crying_baby","dog","rooster"}
#endif /* !AI_MODEL_CLASS_LIST */
#ifndef AI_OOD_THR
#define AI_OOD_THR             (0.8F)
#endif /* !AI_OOD_THR */
#ifndef AI_SPECT_NMEL
#define AI_SPECT_NMEL          (64U)
#endif /* !AI_SPECT_NMEL */
#ifndef AI_SPECT_MEL_FILT_LEN
#define AI_SPECT_MEL_FILT_LEN  (462U)
#endif /* !AI_SPECT_MEL_FILT_LEN */
#ifndef AI_SPECT_COL
#define AI_SPECT_COL           (96U)
#endif /* !AI_SPECT_COL */
#ifndef AI_SPECT_HOP_LEN
#define AI_SPECT_HOP_LEN       (160U)
#endif /* !AI_SPECT_HOP_LEN */
#ifndef AI_SPECT_NFFT
#define AI_SPECT_NFFT          (512U)
#endif /* !AI_SPECT_NFFT */
#ifndef AI_SPECT_WIN_LEN
#define AI_SPECT_WIN_LEN       (400U)
#endif /* !AI_SPECT_WIN_LEN */
#ifndef AI_SPECT_NORMALIZE
#define AI_SPECT_NORMALIZE     (1U)
#endif /* !AI_SPECT_NORMALIZE */
#ifndef AI_SPECT_FORMULA
#define AI_SPECT_FORMULA       (MEL_HTK)
#endif /* !AI_SPECT_FORMULA */
#ifndef AI_SPECT_FMIN
#define AI_SPECT_FMIN          (125U)
#endif /* !AI_SPECT_FMIN */
#ifndef AI_SPECT_FMAX
#define AI_SPECT_FMAX          (7500U)
#endif /* !AI_SPECT_FMAX */
#ifndef AI_SPECT_TYPE
#define AI_SPECT_TYPE          (SPECTRUM_TYPE_POWER)
#endif /* !AI_SPECT_TYPE */
#ifndef AI_SPECT_LOG_FORMULA
#define AI_SPECT_LOG_FORMULA   (LOGMELSPECTROGRAM_SCALE_LOG) /* LOGMELSPECTROGRAM_SCALE_DB */
#endif /* !AI_SPECT_LOG_FORMULA */

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* DPU_CONFIG_H_ */
