/**
  ******************************************************************************
  * @file   : app_audio.h
  * @author : STMicroelectronics AIS application team
  * @brief  : Main program body
  * @version $Version$
  * @date    $Date$
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
#ifndef __APP_AUDIO_H_
#define __APP_AUDIO_H_

#include "audiopipeline_ai.h"
#include "audiopipeline_preproc.h"

typedef struct _AudPreProc_t
{
   AudioPreProcCtx_t audiopreproc_ctx;
   uint8_t           acq_p[AUDIO_BUFF_SIZE];
   int8_t*           out_p;
}AudPreProc_t;

typedef struct _AudProc_t
{
  AIProcCtx_t ai;
  int8_t*     ai_in_p;
  float*      ai_out_p;
}AudProc_t;

int audio_init(void);
int audio_deinit(void);
int audio_exec(void);

#endif /* __APP_AUDIO_H__ */
