/**
  ******************************************************************************
  * @file    hsp_engine_rsrc_map_template.h
  * @brief   Header file for interfaces
 ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025-2026 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the mx_freertos_license.md file
  * in the same directory as the generated code.
  * If no mx_freertos_license.md file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  *//* Define to prevent recursive inclusion -------------------------------------*/
#ifndef HSP_IF_CONF_TEMPLATE_H
#define HSP_IF_CONF_TEMPLATE_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* Includes ------------------------------------------------------------------*/
#include "interface.h"
#include "stm32_hal.h"
#include "hsp_api_def.h"

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Defines for TRGIN signals -------------------------------------------------*/
/*
  For ADF: #define HSP_TRGIN_ADF_x  HAL_HSP_TRGIN_ADFxxxxx
    #define HSP_TRGIN_ADF_0  HAL_HSP_TRGIN_ADF1_SAD_DET

  For DMA Transfer Complete: #define HSP_TRGIN_DMA_TC_x  HAL_HSP_TRGIN_<G|H|LP>DMA<y>_CH<z>_TC
    ex: #define HSP_TRGIN_DMA_TC_5  HAL_HSP_TRGIN_HDMA2_CH12_TC

  For EXTI: #define HSP_TRGIN_EXTI_x  HAL_HSP_TRGIN_EXT<y>
    ex: #define HSP_TRGIN_EXTI_5  HAL_HSP_TRGIN_EXTI0

  For LPTIM: #define HSP_TRGIN_LPTIM_x  HAL_HSP_TRGIN_LPTIM<y>_CH<z>
    ex: #define HSP_TRGIN_LPTIM_17  HAL_HSP_TRGIN_LPTIM2_CH2

  For MDF Filter RX Interrupt: #define HSP_TRGIN_MDF_FLT_RX_IT_x  HAL_HSP_TRGIN_MDF_FLT<y>_RX_IT
    ex: #define HSP_TRGIN_MDF_FLT_RX_IT_3 HAL_HSP_TRGIN_MDF_FLT1_RX_IT

  For NPU : #define HSP_TRGIN_NPU_x  HAL_HSP_TRGIN_NPU_<literal><[0..9]*>
    ex: #define HSP_TRGIN_NPU_0  HAL_HSP_TRGIN_NPU_HOST_IN3

  For TIM TRGO: #define HSP_TRGIN_TIM_TRGO_x  HAL_HSP_TRGIN_TIM<y>_TRGO<empty | [0..9]>
    ex: #define HSP_TRGIN_TIM_TRGO_1 HAL_HSP_TRGIN_TIM7_TRGO
    ex: #define HSP_TRGIN_TIM_TRGO_5 HAL_HSP_TRGIN_TIM25_TRGO2

  For PLAY OUT: #define HSP_TRGIN_PLAY_OUT_x  HAL_HSP_TRGIN_PLAY<y>_OUT<z>
    ex: #define HSP_TRGIN_PLAY_OUT_0 HAL_HSP_TRGIN_PLAY1_OUT6

  */

/* Defines for TRGO signals --------------------------------------------------*/
/*
  For DMA Trigger: #define HSP_TRGO_DMA_TRIG_x  HAL_HSP_TRGO_<G|H|LP>DMA<y>_TRIG<z>
    #define HSP_TRGO_DMA_TRIG_0  HAL_HSP_TRGO_GPDMA1_TRIG34

  */

/* Defines for GPO signals ---------------------------------------------------*/
/*
  For DMA Trigger: #define HSP_GPO_DMA_TRIG_x  HAL_HSP_GPO_<G|H|LP>DMA<y>_TRIG<z>
    #define HSP_GPO_DMA_TRIG_0  HAL_HSP_GPO_GPDMA1_TRIG38

  */

/* Exported macro ------------------------------------------------------------*/
/* Exported functions prototypes ---------------------------------------------*/


#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* HSP_IF_CONF_TEMPLATE_H */
