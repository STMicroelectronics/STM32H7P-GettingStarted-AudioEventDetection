/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file   mx_app_hsp_engine_process.c
  * @brief  This file implements the HSP_Engine Process functions
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
/* USER CODE END Header */

#include "main.h"
#include "mx_app_hsp_bram_alloc.h"
#include "mx_app_hsp_engine_seq.h"
#include "mx_app_hsp_engine_process.h"
#include "hsp_core.h"
#include "hsp_proclist.h"
#include "hsp_if_conf.h"

#include <string.h>

/* Private includes ----------------------------------------------------------*/
/* Add #include related to the HSP Modules required by the Application */
/*
  ex: "#include "hsp_direct_command.h" for processing by HSP Direct Command
  ex: "#include "hsp_dsp.h" for processing by HSP DSP functions
  ...
 */

/* Private typedef -----------------------------------------------------------*/

/* Private define ------------------------------------------------------------*/

/* Private macro -------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/

/* Private function prototypes -----------------------------------------------*/

/* Private user code ---------------------------------------------------------*/

/**
  * @brief Run Biquad Cascade DF1 filter with HSP Engine.
  * @param None
  * @retval 0 if success, other failed
  */
/*uint32_t APP_HSP_Engine_Process_Direct_BiquadCascadeDF1(void)
{
  ...
  return 0;
}
*/
