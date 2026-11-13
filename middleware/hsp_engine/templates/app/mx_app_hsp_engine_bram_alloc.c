/**
  ******************************************************************************
  * @file    mx_app_hsp_engine_bram_alloc.c
  * @brief   This file contains resources allocated in HSP BRAM region memory
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

#include "mx_app_hsp_engine_bram_alloc.h"
#include "hsp_bram.h"

/* Exported variables by reference -------------------------------------------*/
static hsp1_bram_resources_t g_hsp1_bram_resources;

/* BRAM Resources Static Allocation ------------------------------------------*/
/* Example of static allocations
static float32_t my_vect1[HSP_BRAM_RSRC_VECTOR1_SIZE] __attribute__((section(".HSP_DATA_BRAM"))) = {
  0.1f, 1.2f, -0.2f, -1000.0f, -8502.f, -123.545f, 5.0f, .035456464f, 1.54564646f, 798.22545f
};

static float32_t my_vect2[HSP_BRAM_RSRC_VECTOR2_SIZE] __attribute__((section(".HSP_DATA_BRAM"))) = {
  1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f
};

*/

/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
static uint32_t mx_app_hsp_engine_bram_allocate_hsp1(const hsp_engine_context_t *hmw, void *p_bram_resources);

/* Exported function prototypes ----------------------------------------------*/
uint32_t HSP_BRAM_AllocateHook(hsp_engine_context_t *hmw)
{
  uint32_t error = 0UL;

  if (HSP_CORE_GetPeripheral() == HSP1)
  {
    error = mx_app_hsp_engine_bram_allocate_hsp1(hmw);
    *p_bram_resources = (void *)&g_hsp1_bram_resources;
  }

  return error;
}

/* Private function ----------------------------------------------------------*/
uint32_t mx_app_hsp_engine_bram_allocate_hsp1(const hsp_engine_context_t *hmw)
{
  uint32_t error = 0UL;
  /* Set Static resources in hsp_bram_resources context: g_bram_resources */
  /*
  g_bram_resources.my_vect1 = &my_vect1[0];
  g_bram_resources.my_vect1 = &my_vect2[0];
  */

  /* Dynamic allocation in HSP BRAMAB */
  /*
  g_bram_resources.fir_state_id = HSP_BRAM_MallocStateBuffer_Fir(hmw, HSP_BRAM_RSRC_FIR_STATE_TAPS_NBR,
                                                                 FIR_SAMPLES_IN_NBR, HSP_BRAM_ALLOCATION_DEFAULT);
  if (g_bram_resources.fir_state_id == 0UL) error++;

  g_bram_resources.biquad_state_id = HSP_BRAM_MallocStateBuffer_BiquadCascadeDf1(hmw, HSP_BRAM_RSRC_FIR_STATE_TAPS_NBR,
                                                                                 FIR_SAMPLES_IN_NBR,
                                                                                 HSP_BRAM_ALLOCATION_DEFAULT);
  if (g_bram_resources.biquad_state_id == 0UL) error++;

  g_bram_resources.p_buff_in = (float32_t *)HSP_BRAM_Malloc(hmw, HSP_BRAM_RSRC_FIR_SAMPLES_IN_NBR,
                                                            HSP_BRAM_ALLOCATION_DEFAULT);
  if (p_buff_in == NULL) error++;

  g_bram_resources.p_coef = (float32_t *)HSP_BRAM_Malloc(hmw, HSP_BRAM_RSRC_FIR_COEF_NBR, HSP_BRAM_ALLOCATION_DEFAULT);
  if (g_bram_resources.p_coef == NULL) error++;

  g_bram_resources.p_buff_out = (float32_t *)HSP_BRAM_Malloc(hmw, HSP_BRAM_RSRC_FIR_RESULTS_NBR,
                                                             HSP_BRAM_ALLOCATION_DEFAULT);
  if (g_bram_resources.p_buff_out == NULL) error++;
  */

  return error;
}
