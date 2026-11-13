/**
  ******************************************************************************
  * @file    hsp_cnn_dma.h
  * @brief   API for HSP direct CNN functions using internal HSP DMA
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
#ifndef HSP_CNN_DMA_H
#define HSP_CNN_DMA_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#if defined(__HSP_DMA__)
/* Includes ------------------------------------------------------------------*/
#include "hsp_def.h"

/** @addtogroup HSP_ENGINE
  * @{
  */

/** @defgroup HSP_MODULES_CNN_LIBRARY HSP Modules CNN Library
  * @{
  */
/* Exported constants --------------------------------------------------------*/
/* Exported macros -----------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/
/* Exported variables --------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/

hsp_core_status_t HSP_ACC_CnnConv2d0D_s8(hsp_engine_context_t *hmw, uint32_t in_w, uint32_t in_h, uint32_t in_c,
                                         uint32_t k_w, uint32_t k_h, uint32_t ou_w, uint32_t ou_h, uint32_t ou_c,
                                         uint32_t stridex, uint32_t stridey, int8_t *p_input_data,
                                         int8_t *p_filter_data, int8_t *p_output_data, uint32_t *p_bias_data,
                                         float32_t in_scale, float32_t out_scale, const float32_t *p_wt_scale,
                                         uint32_t off_in, uint32_t off_ou, uint32_t sat_min, uint32_t sat_max,
                                         uint32_t padx0, uint32_t padx1, uint32_t pady0, uint32_t pady1);

hsp_core_status_t HSP_ACC_CnnConv2d1D_s8(hsp_engine_context_t *hmw, uint32_t in_w, uint32_t in_h, uint32_t in_c,
                                         uint32_t k_w, uint32_t k_h, uint32_t ou_w, uint32_t ou_h, uint32_t ou_c,
                                         uint32_t stridex, uint32_t stridey, int8_t *p_input_data,
                                         int8_t *p_filter_data, int8_t *p_output_data, uint32_t *p_bias_data,
                                         float32_t in_scale, float32_t out_scale, const float32_t *p_wt_scale,
                                         uint32_t off_in, uint32_t off_ou, uint32_t sat_min, uint32_t sat_max,
                                         uint32_t padx0, uint32_t padx1, uint32_t pady0, uint32_t pady1,
                                         uint32_t nb_line_per_blocks);

hsp_core_status_t HSP_ACC_CnnConv2d2D_s8(hsp_engine_context_t *hmw, uint32_t in_w, uint32_t in_h, uint32_t in_c,
                                         uint32_t k_w, uint32_t k_h, uint32_t ou_w, uint32_t ou_h, uint32_t ou_c,
                                         uint32_t stridex, uint32_t stridey, int8_t *p_input_data,
                                         int8_t *p_filter_data, int8_t *p_output_data, uint32_t *p_bias_data,
                                         float32_t in_scale, float32_t out_scale, const float32_t *p_wt_scale,
                                         uint32_t off_in, uint32_t off_ou, uint32_t sat_min, uint32_t sat_max,
                                         uint32_t padx0, uint32_t padx1, uint32_t pady0, uint32_t pady1,
                                         uint32_t nb_line_per_blocks);

hsp_core_status_t HSP_ACC_CnnConv2d3D_s8(hsp_engine_context_t *hmw, uint32_t in_w, uint32_t in_h, uint32_t in_c,
                                         uint32_t k_w, uint32_t k_h, uint32_t ou_w, uint32_t ou_h, uint32_t ou_c,
                                         uint32_t stridex, uint32_t stridey, int8_t *p_input_data,
                                         int8_t *p_filter_data, int8_t *p_output_data, uint32_t *p_bias_data,
                                         float32_t in_scale, float32_t out_scale, const float32_t *p_wt_scale,
                                         uint32_t off_in, uint32_t off_ou, uint32_t sat_min, uint32_t sat_max,
                                         uint32_t padx0, uint32_t padx1, uint32_t pady0, uint32_t pady1,
                                         uint32_t nb_line_per_blocks);

hsp_core_status_t HSP_ACC_CnnFullyConnected0D_s8(hsp_engine_context_t *hmw, uint32_t in_c, uint32_t ou_c,
                                                 int8_t *p_input_data, int8_t *p_filter_data, int8_t *p_output_data,
                                                 uint32_t *p_bias_data, float32_t in_scale, float32_t out_scale,
                                                 float32_t wt_scale, uint32_t off_in, uint32_t off_ou,
                                                 uint32_t sat_min, uint32_t sat_max);

hsp_core_status_t HSP_ACC_CnnFullyConnected1D_s8(hsp_engine_context_t *hmw, uint32_t in_c, uint32_t ou_c,
                                                 int8_t *p_input_data, int8_t *p_filter_data, int8_t *p_output_data,
                                                 uint32_t *p_bias_data, float32_t in_scale, float32_t out_scale,
                                                 float32_t wt_scale, uint32_t off_in, uint32_t off_ou,
                                                 uint32_t sat_min, uint32_t sat_max);

hsp_core_status_t HSP_ACC_CnnPool0D_s8(hsp_engine_context_t *hmw, uint32_t in_w, uint32_t in_h, uint32_t in_c,
                                       uint32_t k_w, uint32_t k_h, uint32_t ou_w, uint32_t ou_h, uint32_t ou_c,
                                       uint32_t stridex, uint32_t stridey, int8_t *p_input_data, int8_t *p_output_data,
                                       uint32_t sat_min, uint32_t sat_max, uint32_t type);

hsp_core_status_t HSP_ACC_CnnPool1D_s8(hsp_engine_context_t *hmw, uint32_t in_w, uint32_t in_h, uint32_t in_c,
                                       uint32_t k_w, uint32_t k_h, uint32_t ou_w, uint32_t ou_h, uint32_t ou_c,
                                       uint32_t stridex, uint32_t stridey, int8_t *p_input_data,
                                       int8_t *p_output_data, uint32_t sat_min, uint32_t sat_max,
                                       uint32_t padx0, uint32_t padx1, uint32_t pady0, uint32_t pady1,
                                       uint32_t type, uint32_t nb_line_per_blocks);

hsp_core_status_t HSP_ACC_CnnConvDepthwise1D_s8(hsp_engine_context_t *hmw,
                                                uint32_t in_w, uint32_t in_h, uint32_t in_c,
                                                uint32_t k_w, uint32_t k_h,
                                                uint32_t ou_w, uint32_t ou_h, uint32_t ou_c,
                                                uint32_t stridex, uint32_t stridey,
                                                int8_t *p_input_data, int8_t *p_filter_data, int8_t *p_output_data,
                                                int32_t *p_bias_data,
                                                float32_t in_scale, float32_t out_scale, const float32_t *p_wt_scale,
                                                int32_t off_in, int32_t off_ou, int32_t sat_min, int32_t sat_max,
                                                uint32_t padx_l, uint32_t padx_r, uint32_t pady_t, uint32_t pady_b);
hsp_core_status_t HSP_ACC_CnnConvDepthwise2D_s8(hsp_engine_context_t *hmw,
                                                uint32_t in_w, uint32_t in_h, uint32_t in_c,
                                                uint32_t k_w, uint32_t k_h,
                                                uint32_t ou_w, uint32_t ou_h, uint32_t ou_c,
                                                uint32_t stridex, uint32_t stridey,
                                                int8_t *p_input_data, int8_t *p_filter_data, int8_t *p_output_data,
                                                int32_t *p_bias_data,
                                                float32_t in_scale, float32_t out_scale, const float32_t *p_wt_scale,
                                                int32_t off_in, int32_t off_ou, int32_t sat_min, int32_t sat_max,
                                                uint32_t padx_l, uint32_t padx_r, uint32_t pady_t, uint32_t pady_b,
                                                uint32_t nb_line_per_blocks);
hsp_core_status_t HSP_ACC_CnnConvDepthwise3D_s8(hsp_engine_context_t *hmw,
                                                uint32_t in_w, uint32_t in_h, uint32_t in_c,
                                                uint32_t k_w, uint32_t k_h,
                                                uint32_t ou_w, uint32_t ou_h, uint32_t ou_c,
                                                uint32_t stridex, uint32_t stridey,
                                                int8_t *p_input_data, int8_t *p_filter_data, int8_t *p_output_data,
                                                int32_t *p_bias_data,
                                                float32_t in_scale, float32_t out_scale, const float32_t *p_wt_scale,
                                                int32_t off_in, int32_t off_ou, int32_t sat_min, int32_t sat_max,
                                                uint32_t padx_l, uint32_t padx_r, uint32_t pady_t, uint32_t pady_b,
                                                uint32_t nb_line_per_blocks);
hsp_core_status_t HSP_ACC_CnnConvPointwise0D_s8(hsp_engine_context_t *hmw,
                                                uint32_t in_w, uint32_t in_h, uint32_t in_c,
                                                uint32_t ou_w, uint32_t ou_h, uint32_t ou_c,
                                                uint32_t stridex, uint32_t stridey,
                                                int8_t *p_input_data, int8_t *p_filter_data, int8_t *p_output_data,
                                                int32_t *p_bias_data,
                                                float32_t in_scale, float32_t out_scale, const float32_t *p_wt_scale,
                                                int32_t off_in, int32_t off_ou, int32_t sat_min, int32_t sat_max);
hsp_core_status_t HSP_ACC_CnnConvPointwise1D_s8(hsp_engine_context_t *hmw,
                                                uint32_t in_w, uint32_t in_h, uint32_t in_c,
                                                uint32_t ou_w, uint32_t ou_h, uint32_t ou_c,
                                                uint32_t stridex, uint32_t stridey,
                                                int8_t *p_input_data, int8_t *p_filter_data, int8_t *p_output_data,
                                                int32_t *p_bias_data,
                                                float32_t in_scale, float32_t out_scale, const float32_t *p_wt_scale,
                                                int32_t off_in, int32_t off_ou, int32_t sat_min, int32_t sat_max);
hsp_core_status_t HSP_ACC_CnnConvPointwise2D_s8(hsp_engine_context_t *hmw,
                                                uint32_t in_w, uint32_t in_h, uint32_t in_c,
                                                uint32_t ou_w, uint32_t ou_h, uint32_t ou_c,
                                                uint32_t stridex, uint32_t stridey,
                                                int8_t *p_input_data, int8_t *p_filter_data, int8_t *p_output_data,
                                                int32_t *p_bias_data,
                                                float32_t in_scale, float32_t out_scale, const float32_t *p_wt_scale,
                                                int32_t off_in, int32_t off_ou, int32_t sat_min, int32_t sat_max,
                                                uint32_t nb_line_per_blocks);
hsp_core_status_t HSP_ACC_CnnConvPointwise3D_s8(hsp_engine_context_t *hmw,
                                                uint32_t in_w, uint32_t in_h, uint32_t in_c,
                                                uint32_t ou_w, uint32_t ou_h, uint32_t ou_c,
                                                uint32_t stridex, uint32_t stridey,
                                                int8_t *p_input_data, int8_t *p_filter_data, int8_t *p_output_data,
                                                int32_t *p_bias_data,
                                                float32_t in_scale, float32_t out_scale, const float32_t *p_wt_scale,
                                                int32_t off_in, int32_t off_ou, int32_t sat_min, int32_t sat_max,
                                                uint32_t nb_line_per_blocks);

/**
  * @}
  */

/**
  * @}
  */

#endif /* __HSP_DMA__ */

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* HSP_CNN_DMA_H */
