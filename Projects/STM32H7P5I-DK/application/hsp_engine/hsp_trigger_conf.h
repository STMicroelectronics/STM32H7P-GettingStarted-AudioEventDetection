/**
  ******************************************************************************
  * @file    stm32_hsp_trigger_conf.h
  * @author  GPM Application Team
  * @brief   Header file for input trigger definition
  ******************************************************************************
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
#ifndef STM32_HSP_TRIGGER_CONF_H
#define STM32_HSP_TRIGGER_CONF_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* Includes ------------------------------------------------------------------*/

/** @addtogroup STM32_HSP_LIBRARY
  * @{
  */

/** @defgroup STM32_HSP_CONF
  * @{
  */

/** @defgroup STM32_HSP_TRIGGERCONF
  * @{
  */

/** @defgroup STM32_HSP_TRIGGER_CONF_Exported_Constants
  * @{
  */
/**
  * @brief Defines to identify all the input triggers interconnected with the HSP.
  * Ex of trigger input definitions for STM32U3C5
  *   #define HSP_DMA1_CHANNEL8_TC  HSP_CORE_TRGI_0
  *   #define HSP_DMA1_CHANNEL9_TC  HSP_CORE_TRGI_1
  *   #define HSP_DMA1_CHANNEL10_TC  HSP_CORE_TRGI_2
  *   ...
  */
/* #define HSP_<literal>  HSP_CORE_TRGI<x> */
#define HSP_DMA1_CHANNEL8_TC   HSP_CORE_TRGI_0
#define HSP_DMA1_CHANNEL9_TC   HSP_CORE_TRGI_1
#define HSP_DMA1_CHANNEL10_TC  HSP_CORE_TRGI_2
#define HSP_DMA1_CHANNEL11_TC  HSP_CORE_TRGI_3
#define HSP_EXTI0              HSP_CORE_TRGI_4
#define HSP_EXTI1              HSP_CORE_TRGI_5
#define HSP_TIM1_TRGO          HSP_CORE_TRGI_6
#define HSP_TIM1_TRGO2         HSP_CORE_TRGI_7
#define HSP_TIM2_TRGO          HSP_CORE_TRGI_8
#define HSP_TIM3_TRGO          HSP_CORE_TRGI_9
#define HSP_TIM6_TRGO          HSP_CORE_TRGI_10
#define HSP_TIM7_TRGO          HSP_CORE_TRGI_11
#define HSP_TIM8_TRGO          HSP_CORE_TRGI_12
#define HSP_TIM8_TRGO2         HSP_CORE_TRGI_13
#define HSP_TIM15_TRGO         HSP_CORE_TRGI_14
#define HSP_LPTIM1_CH1         HSP_CORE_TRGI_15
#define HSP_LPTIM1_CH2         HSP_CORE_TRGI_16
#define HSP_LPTIM2_CH1         HSP_CORE_TRGI_17
#define HSP_LPTIM2_CH2         HSP_CORE_TRGI_18
#define HSP_ADF1_SAD_det       HSP_CORE_TRGI_19

/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */
 
/**
  * @}
  */
#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* STM32_HSP_TRIGGER_CONF_H */
