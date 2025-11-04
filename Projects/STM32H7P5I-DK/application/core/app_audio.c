/**
  ******************************************************************************
  * @file    app_audio.c
  * @author  STMicroelectronics AIS application team
  * @brief   bare metal audio
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

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include <stdio.h>
#include "audiopipeline_preproc.h"
#include "app_audio.h"
#include "cpu_stats.h"
#include "gs_utils.h"

// /* Globals--------------------------------------------------------------------*/
AudPreProc_t audio_pre_proc_ctx ;
AudProc_t    audio_proc_ctx ;
volatile int audio_acq_buff_size;
volatile uint8_t * p_acquired_audio_samples;

// /* Private function prototypes -----------------------------------------------*/
static void StartAudioSensors(void);
static void StopAudioSensors(void);
// /* Private variables ---------------------------------------------------------*/
static const char *sAiAudioClassLabels[CTRL_X_CUBE_AI_MODEL_CLASS_NUMBER] = \
                                                 CTRL_X_CUBE_AI_MODEL_CLASS_LIST;
extern hal_adf_handle_t AdfHandle0;


int audio_deinit(void)
{
  AudioPipeline_AIReleaseModel(&audio_proc_ctx.ai);
  StopAudioSensors();

  return 0;
}

int audio_init(void)
{
  /* get the AI model   */
  if (AUDIOPIPELINE_OK != AudioPipeline_AILoadModel(&audio_proc_ctx.ai))
  {
    Error_Handler();
  }
  audio_proc_ctx.ai.classes = sAiAudioClassLabels;
  audio_proc_ctx.ai_in_p    = (int8_t* ) audio_proc_ctx.ai.p_stai_inputs[0];
  audio_proc_ctx.ai_out_p   = (float* )  audio_proc_ctx.ai.p_stai_outputs[0];
  AudioPipeline_PreprocInit( &audio_pre_proc_ctx.audiopreproc_ctx) ;

  /* transfer quantization parameters included in AI model to the Audio audiopreproc_ctx */
  audio_pre_proc_ctx.audiopreproc_ctx.out_Q_offset    = audio_proc_ctx.ai.input_Q_offset;
  audio_pre_proc_ctx.audiopreproc_ctx.out_Q_inv_scale = audio_proc_ctx.ai.input_Q_inv_scale;
  audio_pre_proc_ctx.out_p = audio_proc_ctx.ai_in_p ;

  StartAudioSensors();

  return 0;
}

int audio_exec(void)
{
  if (audio_acq_buff_size >=  AUDIO_HALF_BUFF_SIZE)
  {
    audio_acq_buff_size -= AUDIO_HALF_BUFF_SIZE;
    uint8_t* p_in = (uint8_t* )p_acquired_audio_samples;

    AudioPipeline_Preproc(&audio_pre_proc_ctx.audiopreproc_ctx, p_in, audio_pre_proc_ctx.out_p);

    if (audio_pre_proc_ctx.audiopreproc_ctx.S_Spectr.spectro_sum > CTRL_X_CUBE_AI_SPECTROGRAM_SILENCE_THR)
    {
      AudioPipeline_AIProcess(&audio_proc_ctx.ai, audio_proc_ctx.ai_out_p);
      PrintAIClassesOutput(audio_proc_ctx.ai_out_p, audio_proc_ctx.ai.classes);
    }
    audio_pre_proc_ctx.audiopreproc_ctx.S_Spectr.spectro_sum = 0;
  }
  return 0;
}

/* Callback Definition -------------------------------------------------------*/
/**
  * @brief  MDF acquisition complete callback.
  * @param  hmdf MDF handle.
  * @retval None.
  */
void HAL_ADF_DFLT_AcqCpltCallback(hal_adf_handle_t *hadf, hal_adf_block_index_t digital_filter_index)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(hadf);
  audio_acq_buff_size += AUDIO_HALF_BUFF_SIZE;
  p_acquired_audio_samples = audio_pre_proc_ctx.acq_p;
}

/**
  * @brief  MDF acquisition half complete callback.
  * @param  hmdf MDF handle.
  * @retval None.
  */
void HAL_ADF_DFLT_AcqHalfCpltCallback(hal_adf_handle_t *hadf, hal_adf_block_index_t digital_filter_index)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(hadf);
  audio_acq_buff_size += AUDIO_HALF_BUFF_SIZE;
  p_acquired_audio_samples = audio_pre_proc_ctx.acq_p + AUDIO_HALF_BUFF_SIZE;
}

/**
 * @brief Initializes the audio sensor (digital microphone)
 * @retval None
 */
static void StartAudioSensors(void)
{
  assert_param(AUDIO_BUFF_SIZE < 0xFFFF );
  hal_adf_dma_config_t dma_config;
  dma_config.address    = (uint32_t)audio_pre_proc_ctx.acq_p;
  dma_config.data_length_byte = AUDIO_BUFF_SIZE;
  dma_config.data_resolution  = HAL_ADF_DMA_DATA_RESOLUTION_MSB_ONLY;

  if (HAL_OK != HAL_ADF_DFLT_StartAcq_DMA(&AdfHandle0, HAL_ADF_BLOCK_INDEX_0, &dma_config))
  {
    Error_Handler();
  }

}

/**
 * @brief Stop the audio sensor (digital microphone)
 * @retval None
 */
static void StopAudioSensors(void)
{
  if (HAL_OK != HAL_ADF_DFLT_StopAcq_DMA(&AdfHandle0, HAL_ADF_BLOCK_INDEX_0))
  {
    Error_Handler();
  }
}

