/**
  ******************************************************************************
  * @file    user_mel_tables.h
  * @author  MCD Application Team
  * @brief   Header for common_tables.c module
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
  
#ifndef _USER_MEL_TABLES_H
#define _USER_MEL_TABLES_H

#include "arm_math.h"
#include "ai_model_config.h"

extern const float32_t user_win[AI_SPECT_WIN_LEN];
extern const float32_t user_melFilterLut[AI_SPECT_MEL_FILT_LEN];
extern const uint32_t  user_melFilterStartIndices[AI_SPECT_NMEL];
extern const uint32_t  user_melFilterStopIndices[AI_SPECT_NMEL];

#endif /* _USER_MEL_TABLES_H */
