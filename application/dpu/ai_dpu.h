/**
  ******************************************************************************
  * @file    ai_dpu.h
  * @author  MCD Application Team
  * @brief   Header for ai_dpu.c module
  * @version $Version$
  * @date    $Date$
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
#ifndef _AI_DPU_H
#define _AI_DPU_H

/* Includes ------------------------------------------------------------------*/
#include "dpu.h"
#include "stai.h"     /* include ST Edge AI macros, types and data structures */
#include "stai_network.h"


/* Exported constants --------------------------------------------------------*/
#define AI_DPU_BATCH         (0)
#define AI_DPU_HEIGHT        (1)
#define AI_DPU_WIDTH         (2)
#define AI_DPU_CHANNEL       (3)
#define AI_DPU_API_MAJOR     (1)
#define AI_DPU_API_MINOR     (0)
#define AI_DPU_API_MICRO     (0)
#define AI_DPU_NB_MAX_INPUT  (1U)
#define AI_DPU_NB_MAX_OUTPUT (1U)

/* Exported types ------------------------------------------------------------*/

typedef struct _ai_dpu_ctx_t {
  
  stai_network *p_network;    /* Global handle to reference the inst. C-model */
  stai_ptr *p_stai_inputs;
  stai_ptr *p_stai_outputs;
  stai_network_info info;
  stai_format input_format;    /* input format, output format is always float */
  float input_Q_inv_scale;                    /* quantization scale parameter */
  int16_t input_Q_offset;                    /* quantization offset parameter */
  int in_height;
  int in_width;
  int out_height;
} ai_dpu_ctx_t;

/* Exported functions --------------------------------------------------------*/
/**
 * @brief Loads and initializes the AI model.
 * @param p_ctx Pointer to the AI DPU context.
 * @return DPU_OK on success, otherwise DPU_ERROR.
 */
DPU_StatusTypeDef ai_dpu_load_model(ai_dpu_ctx_t *p_ctx);
/**
 * @brief Releases the AI model and runtime resources.
 * @param p_ctx Pointer to the AI DPU context.
 * @return DPU_OK on success, otherwise DPU_ERROR.
 */
DPU_StatusTypeDef ai_dpu_release_model(ai_dpu_ctx_t *p_ctx);
/**
 * @brief Runs inference using the configured AI model.
 * @param p_ctx Pointer to the AI DPU context.
 * @return DPU_OK on success, otherwise DPU_ERROR.
 */
DPU_StatusTypeDef ai_dpu_process(ai_dpu_ctx_t *p_ctx);

#endif /* _AI_DPU_H */
