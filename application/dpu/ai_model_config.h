/**
 ******************************************************************************
 * @file    ai_model_config.h
 * @author  STMicroelectronics - AIS - MCD Team
 * @version $Version$
 * @date    $Date$
 * @brief   Configure the getting started functionality
 *
 * Each logic module of the application should define a DEBUG control byte
 * used to turn on/off the log for the module.
 *
 *********************************************************************************
 * @attention
 *
 * Copyright (c) 2026 STMicroelectronics
 * All rights reserved.
 *
 * This software is licensed under terms that can be found in the LICENSE file in
 * the root directory of this software component.
 * If no LICENSE file comes with this software, it is provided AS-IS.
 *********************************************************************************
 */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef AI_MODEL_CONFIG_H
#define AI_MODEL_CONFIG_H

#ifdef __cplusplus
extern "C" {
#endif

/* Exported constants --------------------------------------------------------*/
#define AI_MODEL_CLASS_NUMBER  (5U)
#define AI_MODEL_CLASS_LIST    {"chirping_birds","clapping",\
                                                  "crying_baby","dog","rooster"}
#define AI_OOD_THR             (0.8F)
#define AI_SPECT_NMEL          (64U)
#define AI_SPECT_COL           (96U)
#define AI_SPECT_HOP_LEN       (160U)
#define AI_SPECT_NFFT          (512U)
#define AI_SPECT_WIN_LEN       (400U)
#define AI_SPECT_MEL_FILT_LEN  (462U)
#define AI_SPECT_NORMALIZE     (0U)
#define AI_SPECT_FORMULA       (MEL_HTK)
#define AI_SPECT_FMIN          (125U)
#define AI_SPECT_FMAX          (7500U)
#define AI_SPECT_TYPE          (SPECTRUM_TYPE_MAGNITUDE)
#define AI_SPECT_LOG_FORMULA   (LOGMELSPECTROGRAM_SCALE_LOG)

#ifdef __cplusplus
}
#endif

#endif /* AI_MODEL_CONFIG_H */

