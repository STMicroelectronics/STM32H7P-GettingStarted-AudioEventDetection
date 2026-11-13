/**
  ******************************************************************************
  * @file    mx_app_hsp_engine_bram_alloc.h
  * @brief   Header file
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef MX_APP_HSP_ENGINE_BRAM_ALLOC_H
#define MX_APP_HSP_ENGINE_BRAM_ALLOC_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* Includes ------------------------------------------------------------------*/
#include "hsp_def.h"

/* Exported types ------------------------------------------------------------*/
/*
typedef {
  /* HSP BRAM Resources allocated statically */
  float32_t *my_vect1;
  float32_t *my_vect2;

  /* HSP BRAM Resources allocated dynamically */
  hsp_filter_state_identifier_t fir_state_id;
  hsp_filter_state_identifier_t biquad_state_id;
  float32_t *p_buff_in;
  float32_t *p_coef;
  float32_t *p_buff_out;
} hsp1_bram_resources_t;
*/

/* Exported constants --------------------------------------------------------*/
/* Declare #define related to the buffer dimensions */
/*
#define HSP_BRAM_RSRC_VECTOR1_SIZE  10U
#define HSP_BRAM_RSRC_VECTOR2_SIZE  11U
#define HSP_BRAM_RSRC_FIR_SAMPLES_IN_NBR  32U
#define HSP_BRAM_RSRC_FIR_COEF_NBR  6U
#define HSP_BRAM_RSRC_FIR_STATE_TAPS_NBR  6U
#define HSP_BRAM_RSRC_FIR_RESULTS_NBR  32U
...
*/

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* MX_APP_HSP_ENGINE_BRAM_ALLOC_H */
