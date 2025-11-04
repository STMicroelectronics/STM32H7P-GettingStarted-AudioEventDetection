/**
  ******************************************************************************
  * @file    Pre_Include_Global.h
  * @brief   Header to enable global STFCF configuration file
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
#ifndef PRE_INCLUDE_GLOBAL_H_STMicroelectronics_stfcf
#define PRE_INCLUDE_GLOBAL_H_STMicroelectronics_stfcf

#ifdef __cplusplus
extern "C" {
#endif

/* origin-pack: STMicroelectronics::stfcf@0.6.0 */
/* created-by: conversion-manager@0.0.65 */

/* Device headers and defines */


/* RTE Content */
#if (CMSIS_USE_Security_STM32CubeMX2_Config_STFCF_0_6_0)
/* Enabling global STFCF configuration file */
#define MBEDTLS_CONFIG_FILE "mx_stfcf_config.h"
#endif /* CMSIS_USE_Security_STM32CubeMX2_Config_STFCF_0_6_0 */

#ifdef __cplusplus
}
#endif

#endif /* PRE_INCLUDE_GLOBAL_H_STMicroelectronics_stfcf */