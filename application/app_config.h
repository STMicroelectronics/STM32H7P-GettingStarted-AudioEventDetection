/**
  ******************************************************************************
  * @file    app_config.h
  * @author  STMicroelectronics AIS application team
  * @version $Version$
  * @date    $Date$
  *
  * @brief
  *
  * <DESCRIPTIOM>
  *
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

#ifndef __APP_CONFIG_H__
#define __APP_CONFIG_H__
#include <stdio.h>

#define AI_SENSOR_ODR        (16000.0F)
#define MENU_DISP_PERIOD     (923)
#define AI_DISP_PERIOD       (2000)
#define AI_SPECT_SILENCE_THR (2500U)

#define APP_CONF_STR "Bare Metal"
#define SEPARATION_LINE       "-----------------------------------------\n\r"
#define SEPARATION_LINE_SHORT "--------------------------------\n\r"

#define APP_VERSION_STRING "1.0.0"
#if !defined(APP_GIT_SHA1_STRING)
#define APP_GIT_SHA1_STRING ""
#endif

#if defined(USE_TRACE) && USE_TRACE != 0
#define PRINTF(...)    printf(__VA_ARGS__)
#else
#define PRINTF(...)
#endif /* defined(USE_TRACE) && USE_TRACE != 0 */

#endif /* __APP_CONFIG_H__ */
