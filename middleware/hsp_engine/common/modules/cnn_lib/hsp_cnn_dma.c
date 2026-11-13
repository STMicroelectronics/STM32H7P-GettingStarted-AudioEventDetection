/**
  ******************************************************************************
  * @file hsp_cnn_dma.c
  * @brief API for HSP direct CNN functions using internal HSP DMA
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

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#if defined(__HSP_DMA__)

/* Includes ------------------------------------------------------------------*/
#include <stdlib.h>
#include "hsp_conf.h"
#include "hsp_cnn.h"
#include "hsp_cnn_dma.h"
#include "hsp_def.h"
#include "hsp_direct_command.h"
#include "hsp_hw_if.h"
#include "hsp_bram.h"
#include "hsp_bram_if.h"

#define HSP_MEMCPY memcpy
#define HSP_MEMSET memset

extern HSP_TypeDef *pHspReg;


/* Private types -----------------------------------------------------------*/
/** @defgroup HSP_CNN_Private_Types HSP_CNN Private Types
  * @{
  */
typedef uint8_t uint8_mema_t;
typedef int8_t int8_mema_t;
typedef uint8_t uint8_memb_t;
typedef int8_t int8_memb_t;
typedef uint32_t uint32_mema_t;
typedef int32_t int32_mema_t;
typedef uint32_t uint32_memb_t;
typedef int32_t int32_memb_t;

/**
  * @}
  */

/* Private defines -----------------------------------------------------------*/
/** @defgroup HSP_CNN_Private_Defines HSP_HW_CNN Private Defines
  * @{
  */
#define HSP_CNN_CDEG_EVT 27  /**< CDEG event number used for ARM/HSP sync during CNN direct functions */

/**
  * @}
  */

/** @addtogroup HSP_MODULES_CNN_LIBRARY
  * @{
  */

/**
  * @brief Direct CNN conv2D function with padding laft, right, top, bottom
  * (all sizes except WHC: 1x1x1, 1x2x1, 2x1x1, 1x3x1, 3x1x1, 1x4x1)
  * All input in MEMA and full kernels in MEMB, sync with HSP during HSP output lines
  * HSP send error report via FWERR register
  * @param hmw                 HSP middleware context.
  * @param in_w                Input dimension width
  * @param in_h                Input dimension height
  * @param in_c                Input dimension channel
  * @param k_w                 Kernel dimension width
  * @param k_h                 Kernel dimension height
  * @param ou_w                Output dimension width
  * @param ou_h                Output dimension height
  * @param ou_c                Output dimension channel
  * @param stridex             Stride on X
  * @param stridey             Stride on Y
  * @param *p_input_data       Input data pointer, int8_t data type
  * @param *p_filter_data      Kernel coefficient pointer, int8_t data type
  * @param *p_output_data      Output data pointer, int8_t data type
  * @param *p_bias_data        Bias data pointer, int32_t data type
  * @param in_scale            Input scale
  * @param out_scale           Output scale
  * @param p_wt_scale          Pointer in weight scales (one per output channel)
  * @param off_in              Input offset, int32_t data type
  * @param off_ou              Output offset, int32_t data type
  * @param sat_min             Min sat (Relu), int32_t data type
  * @param sat_max             Max sat (Relu), int32_t data type
  * @param padx_l              Pad on X left
  * @param padx_r              Pad on X right
  * @param pady_t              Pad on Y top
  * @param pady_b              Pad on Y bottom
  * @retval                    Core status.
 */
hsp_core_status_t HSP_ACC_CnnConv2d0D_s8(hsp_engine_context_t *hmw, uint32_t in_w, uint32_t in_h, uint32_t in_c,
                                         uint32_t k_w, uint32_t k_h, uint32_t ou_w, uint32_t ou_h, uint32_t ou_c,
                                         uint32_t stridex, uint32_t stridey, int8_t *p_input_data,
                                         int8_t *p_filter_data, int8_t *p_output_data, uint32_t *p_bias_data,
                                         float32_t in_scale, float32_t out_scale, const float32_t *p_wt_scale,
                                         uint32_t off_in, uint32_t off_ou, uint32_t sat_min, uint32_t sat_max,
                                         uint32_t padx0, uint32_t padx1, uint32_t pady0, uint32_t pady1)
{
  /* ToDo: check param values: HSP_CHECK_ASSERT_NRV(hhsp, (((((k_w * in_c) + 3) / 4) * k_h) > 1)); */

  /* First of all, wakeup HSP with Direct command */
  HSP_HW_IF_WRITE_DCMDIDR(hmw, HSP_DIRECT_CMD_CNN_CONV2D_I8);

#ifdef CNN_EVTENR_SUPPORT
  /* Save current EVTENR and clear all enable event for ARM/HSP CNN synchro */
  uint32_t evtenrSave = ((HSP_HandleTypeDef *)(hmw->hdriver))->Instance->EVTENR;
  ((HSP_HandleTypeDef *)(hmw->hdriver))->Instance->EVTENR = HSP_CNN_EVTENR_CLR;
#endif /* CNN_EVTENR_SUPPORT */

  /* Then update all parameters */
  uint32_t inp_w = in_w + (padx0 + padx1);
  uint32_t inp_h = in_h + (pady0 + pady1);
  HSP_HW_IF_WRITE_PARAMR0(hmw, inp_w | (inp_h << 16));
  HSP_HW_IF_WRITE_PARAMR1(hmw, 0);
  HSP_HW_IF_WRITE_PARAMR2(hmw, in_c | (ou_c << 16));
  HSP_HW_IF_WRITE_PARAMR3(hmw, k_w | (k_h << 16));
  HSP_HW_IF_WRITE_PARAMR4(hmw, (uint32_t) p_bias_data);
  HSP_HW_IF_WRITE_PARAMR5(hmw, ou_w | (ou_h << 16));
  HSP_HW_IF_WRITE_PARAMR6(hmw, *(uint32_t *) & (in_scale));
  HSP_HW_IF_WRITE_PARAMR7(hmw, *(uint32_t *) & (out_scale));
  HSP_HW_IF_WRITE_PARAMR8(hmw, stridex | (stridey << 16));
  HSP_HW_IF_WRITE_PARAMR9(hmw, padx0 | (padx1 << 8) | (pady0 << 16) | (pady1 << 24));
  HSP_HW_IF_WRITE_PARAMR10(hmw, off_in);
  HSP_HW_IF_WRITE_PARAMR11(hmw, off_ou);
  HSP_HW_IF_WRITE_PARAMR12(hmw, sat_min);
  HSP_HW_IF_WRITE_PARAMR13(hmw, sat_max);
  HSP_HW_IF_WRITE_PARAMR14(hmw, (uint32_t) p_wt_scale);
  HSP_HW_IF_WRITE_PARAMR15(hmw, HSP_CNN_CFG_MODE_0STEP | HSP_CNN_CFG_MODE_DMA);

  uint32_t *pSrcB = (uint32_t *) p_filter_data;
  uint32_t *pSrcA = (uint32_t *) p_input_data;
  uint32_t *pDst  = (uint32_t *) p_output_data;

  /* And finally sync with DCMD using DCMDPTR registers */
  HSP_HW_IF_WRITE_DCMDPTR0(hmw, (uint32_t) pSrcA);
  HSP_HW_IF_WRITE_DCMDPTR1(hmw, (uint32_t) pSrcB);
  HSP_HW_IF_WRITE_DCMDPTR2(hmw, (uint32_t) pDst);

  HSP_ACC_WAIT_END_OF_DIRECT_COMMAND(hmw);
  if (pHspReg->FWERR == 0x18)
  {
    return HSP_CORE_ERROR;
  }

  return HSP_CORE_OK;
}

/**
  * @brief Direct CNN conv2D function with circular mode with padding laft, right, top, bottom
  *        (all sizes except WHC: 1x1x1, 1x2x1, 2x1x1, 1x3x1, 3x1x1, 1x4x1)
  * Circular input and ping pong output in MEMA and full kernels in MEMB, sync with HSP during HSP output lines
  * HSP send error report via FWERR register
  * @param hmw                 HSP middleware context.
  * @param in_w                Input dimension width
  * @param in_h                Input dimension height
  * @param in_c                Input dimension channel
  * @param k_w                 Kernel dimension width
  * @param k_h                 Kernel dimension height
  * @param ou_w                Output dimension width
  * @param ou_h                Output dimension height
  * @param ou_c                Output dimension channel
  * @param stridex             Stride on X
  * @param stridey             Stride on Y
  * @param *p_input_data       Input data pointer, int8_t data type
  * @param *p_filter_data      Kernel coefficient pointer, int8_t data type
  * @param *p_output_data      Output data pointer, int8_t data type
  * @param *p_bias_data        Bias data pointer, int32_t data type
  * @param in_scale            Input scale
  * @param out_scale           Output scale
  * @param p_wt_scale          Pointer in weight scales (one per output channel)
  * @param off_in              Input offset, int32_t data type
  * @param off_ou              Output offset, int32_t data type
  * @param sat_min             Min sat (Relu), int32_t data type
  * @param sat_max             Max sat (Relu), int32_t data type
  * @param padx_l              Pad on X left
  * @param padx_r              Pad on X right
  * @param pady_t              Pad on Y top
  * @param pady_b              Pad on Y bottom
  * @param nb_line_per_blocks_m2  Number of output lines per output buffer - 2 (0 is for ping-pong)
  * @retval                    Core status.
  */
hsp_core_status_t HSP_ACC_CnnConv2d1D_s8(hsp_engine_context_t *hmw, uint32_t in_w, uint32_t in_h, uint32_t in_c,
                                         uint32_t k_w, uint32_t k_h, uint32_t ou_w, uint32_t ou_h, uint32_t ou_c,
                                         uint32_t stridex, uint32_t stridey, int8_t *p_input_data,
                                         int8_t *p_filter_data, int8_t *p_output_data, uint32_t *p_bias_data,
                                         float32_t in_scale, float32_t out_scale, const float32_t *p_wt_scale,
                                         uint32_t off_in, uint32_t off_ou, uint32_t sat_min, uint32_t sat_max,
                                         uint32_t padx0, uint32_t padx1, uint32_t pady0, uint32_t pady1,
                                         uint32_t nb_line_per_blocks_m2)
{
  /* ToDo: check param values: @todo HSP_CHECK_ASSERT_NRV(hhsp, (((((k_w * in_c) + 3) / 4) * k_h) > 1));*/

  /* First of all, wakeup HSP with Direct command */
  HSP_HW_IF_WRITE_DCMDIDR(hmw, HSP_DIRECT_CMD_CNN_CONV2D_I8);

#ifdef CNN_EVTENR_SUPPORT
  /* Save current EVTENR and clear all enable event for ARM/HSP CNN synchro */
  uint32_t evtenrSave = ((HSP_HandleTypeDef *)(hmw->hdriver))->Instance->EVTENR;
  ((HSP_HandleTypeDef *)(hmw->hdriver))->Instance->EVTENR = HSP_CNN_EVTENR_CLR;
#endif /* CNN_EVTENR_SUPPORT */

  /* Then update all parameters */
  uint32_t inp_w = in_w + (padx0 + padx1);
  uint32_t inp_h = in_h + (pady0 + pady1);
  HSP_HW_IF_WRITE_PARAMR0(hmw, inp_w | (inp_h << 16));
  HSP_HW_IF_WRITE_PARAMR1(hmw, 0);
  HSP_HW_IF_WRITE_PARAMR2(hmw, in_c | (ou_c << 16));
  HSP_HW_IF_WRITE_PARAMR3(hmw, k_w | (k_h << 16));
  HSP_HW_IF_WRITE_PARAMR4(hmw, (uint32_t) p_bias_data);
  HSP_HW_IF_WRITE_PARAMR5(hmw, ou_w | (ou_h << 16));
  HSP_HW_IF_WRITE_PARAMR6(hmw, *(uint32_t *) & (in_scale));
  HSP_HW_IF_WRITE_PARAMR7(hmw, *(uint32_t *) & (out_scale));
  HSP_HW_IF_WRITE_PARAMR8(hmw, stridex | (stridey << 16));
  HSP_HW_IF_WRITE_PARAMR9(hmw, padx0 | (padx1 << 8) | (pady0 << 16) | (pady1 << 24));
  HSP_HW_IF_WRITE_PARAMR10(hmw, off_in);
  HSP_HW_IF_WRITE_PARAMR11(hmw, off_ou);
  HSP_HW_IF_WRITE_PARAMR12(hmw, sat_min);
  HSP_HW_IF_WRITE_PARAMR13(hmw, sat_max);
  HSP_HW_IF_WRITE_PARAMR14(hmw, (uint32_t) p_wt_scale);

  uint32_t nbLinePerBlocks = nb_line_per_blocks_m2 + 2;
  uint32_t circiLines = (stridey > 1) ? (k_h * stridey) : (k_h + stridey); /* For circular mode */
  if ((stridey > 1) && (k_h == 1))
  {
    circiLines = 2 * stridey;
  }
  if (circiLines > inp_h)
  {
    circiLines = inp_h;
  }

  HSP_HW_IF_WRITE_PARAMR15(hmw, (circiLines << HSP_CNN_CFG_NB_IN_LINE_SHIFT) |
                           (nbLinePerBlocks << HSP_CNN_CFG_NB_OU_LINE_SHIFT) |
                           HSP_CNN_CFG_MODE_1STEP | HSP_CNN_CFG_MODE_DMA);

  uint32_t *pSrcB = (uint32_t *) p_filter_data;
  uint32_t *pSrcA = (uint32_t *) p_input_data;
  uint32_t *pDst  = (uint32_t *) p_output_data;
  /* And finally sync with DCMD using DCMDPTR registers */
  HSP_HW_IF_WRITE_DCMDPTR0(hmw, (uint32_t) pSrcA);
  HSP_HW_IF_WRITE_DCMDPTR1(hmw, (uint32_t) pSrcB);
  HSP_HW_IF_WRITE_DCMDPTR2(hmw, (uint32_t) pDst);

  HSP_ACC_WAIT_END_OF_DIRECT_COMMAND(hmw);

  if (pHspReg->FWERR == 0x18)
  {
    return HSP_CORE_ERROR;
  }

  return HSP_CORE_OK;
}

/**
  * @brief Direct CNN conv2D function with circular mode in 2 steps with padding
  *        (all sizes except WHC: 1x1x1, 1x2x1, 2x1x1, 1x3x1, 3x1x1, 1x4x1, 3x3x1, 3x3x3)
  * Circular input and ping pong output in MEMA and full kernels in MEMB, sync with HSP during HSP output lines
  * Split code in 2 steps
  * First loop is on kernel to load all kernels, while HSP working on first channel
  * Then loop on all other channels
  * HSP send error report via FWERR register
  * @param hmw                 HSP middleware context.
  * @param in_w                Input dimension width
  * @param in_h                Input dimension height
  * @param in_c                Input dimension channel
  * @param k_w                 Kernel dimension width
  * @param k_h                 Kernel dimension height
  * @param ou_w                Output dimension width
  * @param ou_h                Output dimension height
  * @param ou_c                Output dimension channel
  * @param stridex             Stride on X
  * @param stridey             Stride on Y
  * @param *p_input_data       Input data pointer, int8_t data type
  * @param *p_filter_data      Kernel coefficient pointer, int8_t data type
  * @param *p_output_data      Output data pointer, int8_t data type
  * @param *p_bias_data        Bias data pointer, int32_t data type
  * @param in_scale            Input scale
  * @param out_scale           Output scale
  * @param p_wt_scale          Pointer in weight scales (one per output channel)
  * @param off_in              Input offset, int32_t data type
  * @param off_ou              Output offset, int32_t data type
  * @param sat_min             Min sat (Relu), int32_t data type
  * @param sat_max             Max sat (Relu), int32_t data type
  * @param padx_l              Pad on X left
  * @param padx_r              Pad on X right
  * @param pady_t              Pad on Y top
  * @param pady_b              Pad on Y bottom
  * @param nb_line_per_blocks_m2  Number of output lines per output buffer - 2 (0 is for ping-pong)
   * @retval                   Core status.
 */
hsp_core_status_t HSP_ACC_CnnConv2d2D_s8(hsp_engine_context_t *hmw, uint32_t in_w, uint32_t in_h, uint32_t in_c,
                                         uint32_t k_w, uint32_t k_h, uint32_t ou_w, uint32_t ou_h, uint32_t ou_c,
                                         uint32_t stridex, uint32_t stridey, int8_t *p_input_data,
                                         int8_t *p_filter_data, int8_t *p_output_data, uint32_t *p_bias_data,
                                         float32_t in_scale, float32_t out_scale, const float32_t *p_wt_scale,
                                         uint32_t off_in, uint32_t off_ou, uint32_t sat_min, uint32_t sat_max,
                                         uint32_t padx0, uint32_t padx1, uint32_t pady0, uint32_t pady1,
                                         uint32_t nb_line_per_blocks_m2)
{
  /* @ToDo HSP_CHECK_ASSERT_NRV(hmw, (((((k_w * in_c) + 3) / 4) * k_h) > 1)); */
  /* First of all, wakeup HSP with Direct command */
  HSP_HW_IF_WRITE_DCMDIDR(hmw, HSP_DIRECT_CMD_CNN_CONV2D_I8);

#ifdef CNN_EVTENR_SUPPORT
  /* Save current EVTENR and clear all enable event for ARM/HSP CNN synchro */
  uint32_t evtenrSave = ((HSP_HandleTypeDef *)(hmw->hdriver))->Instance->EVTENR;
  ((HSP_HandleTypeDef *)(hmw->hdriver))->Instance->EVTENR = HSP_CNN_EVTENR_CLR;
#endif /* CNN_EVTENR_SUPPORT */

  /* Then update all parameters */
  uint32_t inp_w = in_w + (padx0 + padx1);
  uint32_t inp_h = in_h + (pady0 + pady1);
  HSP_HW_IF_WRITE_PARAMR0(hmw, inp_w | (inp_h << 16));
  HSP_HW_IF_WRITE_PARAMR1(hmw, 0);
  HSP_HW_IF_WRITE_PARAMR2(hmw, in_c | (ou_c << 16));
  HSP_HW_IF_WRITE_PARAMR3(hmw, k_w | (k_h << 16));
  HSP_HW_IF_WRITE_PARAMR4(hmw, (uint32_t) p_bias_data);
  HSP_HW_IF_WRITE_PARAMR5(hmw, ou_w | (ou_h << 16));
  HSP_HW_IF_WRITE_PARAMR6(hmw, *(uint32_t *) & (in_scale));
  HSP_HW_IF_WRITE_PARAMR7(hmw, *(uint32_t *) & (out_scale));
  HSP_HW_IF_WRITE_PARAMR8(hmw, stridex | (stridey << 16));
  HSP_HW_IF_WRITE_PARAMR9(hmw, padx0 | (padx1 << 8) | (pady0 << 16) | (pady1 << 24));
  HSP_HW_IF_WRITE_PARAMR10(hmw, off_in);
  HSP_HW_IF_WRITE_PARAMR11(hmw, off_ou);
  HSP_HW_IF_WRITE_PARAMR12(hmw, sat_min);
  HSP_HW_IF_WRITE_PARAMR13(hmw, sat_max);
  HSP_HW_IF_WRITE_PARAMR14(hmw, (uint32_t) p_wt_scale);

  uint32_t nbLinePerBlocks = nb_line_per_blocks_m2 + 2;

  uint32_t circiLines = (stridey > 1) ? (k_h * stridey) : (k_h + stridey); /* For circular mode */
  if ((stridey > 1) && (k_h == 1))
  {
    circiLines = 2 * stridey;
  }
  if (circiLines > inp_h)
  {
    circiLines = inp_h;
  }

  uint32_t *pSrcB = (uint32_t *) p_filter_data;
  uint32_t *pSrcA = (uint32_t *) p_input_data;
  uint32_t *pDst  = (uint32_t *) p_output_data;

  HSP_HW_IF_WRITE_PARAMR15(hmw, (circiLines << HSP_CNN_CFG_NB_IN_LINE_SHIFT) |
                           (nbLinePerBlocks << HSP_CNN_CFG_NB_OU_LINE_SHIFT) |
                           HSP_CNN_CFG_MODE_2STEP | HSP_CNN_CFG_MODE_DMA);

  /* And finally sync with DCMD using DCMDPTR registers */
  HSP_HW_IF_WRITE_DCMDPTR0(hmw, (uint32_t) pSrcA);
  HSP_HW_IF_WRITE_DCMDPTR1(hmw, (uint32_t) pSrcB);
  HSP_HW_IF_WRITE_DCMDPTR2(hmw, (uint32_t) pDst);

  HSP_ACC_WAIT_END_OF_DIRECT_COMMAND(hmw);

  if (pHspReg->FWERR == 0x18)
  {
    return HSP_CORE_ERROR;
  }

  return HSP_CORE_OK;
}

/**
  * @brief Direct CNN conv2D function with circular mode in 3 steps with padding
  *        (all sizes except: ((k_w * in_c) < 5) WHC: 3x3x1, 3x3x3),
  * Circular input in MEMA and output in MEMB and ping pong on kernels in MEMB, in 3 steps, sync according to step
  * First step, loop on all input lines with first kernel to get lines from ARM, sync on input line
  * Then loop on all channel (exclude first and last) as classical cio sync by output channel
  * And finally loop on last channel, sync on output line
  * Then play again 3 steps if necessary
  * HSP send error report via FWERR register
  * @param hmw                 HSP middleware context.
  * @param in_w                Input dimension width
  * @param in_h                Input dimension height
  * @param in_c                Input dimension channel
  * @param k_w                 Kernel dimension width
  * @param k_h                 Kernel dimension height
  * @param ou_w                Output dimension width
  * @param ou_h                Output dimension height
  * @param ou_c                Output dimension channel
  * @param stridex             Stride on X
  * @param stridey             Stride on Y
  * @param *p_input_data       Input data pointer, int8_t data type
  * @param *p_filter_data      Kernel coefficient pointer, int8_t data type
  * @param *p_output_data      Output data pointer, int8_t data type
  * @param *p_bias_data        Bias data pointer, int32_t data type
  * @param in_scale            Input scale
  * @param out_scale           Output scale
  * @param p_wt_scale          Pointer in weight scales (one per output channel)
  * @param off_in              Input offset, int32_t data type
  * @param off_ou              Output offset, int32_t data type
  * @param sat_min             Min sat (Relu), int32_t data type
  * @param sat_max             Max sat (Relu), int32_t data type
  * @param padx_l              Pad on X left
  * @param padx_r              Pad on X right
  * @param pady_t              Pad on Y top
  * @param pady_b              Pad on Y bottom
  * @param nb_line_per_blocks  Number of output lines per output buffer
  * @retval                    Core status.
  */
hsp_core_status_t HSP_ACC_CnnConv2d3D_s8(hsp_engine_context_t *hmw, uint32_t in_w, uint32_t in_h, uint32_t in_c,
                                         uint32_t k_w, uint32_t k_h, uint32_t ou_w, uint32_t ou_h, uint32_t ou_c,
                                         uint32_t stridex, uint32_t stridey, int8_t *p_input_data,
                                         int8_t *p_filter_data, int8_t *p_output_data, uint32_t *p_bias_data,
                                         float32_t in_scale, float32_t out_scale, const float32_t *p_wt_scale,
                                         uint32_t off_in, uint32_t off_ou, uint32_t sat_min, uint32_t sat_max,
                                         uint32_t padx0, uint32_t padx1, uint32_t pady0, uint32_t pady1,
                                         uint32_t nb_line_per_blocks)
{
  /* @ToDo
  HSP_CHECK_ASSERT_NRV(hmw, ((((k_w * in_c) + 3) / 4) * k_h));
  HSP_CHECK_ASSERT_NRV(hmw, ((ou_c) >= 3));
  HSP_CHECK_ASSERT_NRV(hmw, ((ou_h) >= 3)); */

  /* First of all, wakeup HSP with Direct command */
  HSP_HW_IF_WRITE_DCMDIDR(hmw, HSP_DIRECT_CMD_CNN_CONV2D_I8);

#ifdef CNN_EVTENR_SUPPORT
  /* Save current EVTENR and clear all enable event for ARM/HSP CNN synchro */
  uint32_t evtenrSave = h_hw_hsp_if[0].hmw.Instance->EVTENR;
  h_hw_hsp_if[0].hmw.Instance->EVTENR = HSP_CNN_EVTENR_CLR;
#endif /* CNN_EVTENR_SUPPORT */

  /* Then update all parameters */
  uint32_t inp_w = in_w + (padx0 + padx1);
  uint32_t inp_h = in_h + (pady0 + pady1);
  HSP_HW_IF_WRITE_PARAMR0(hmw, inp_w | (inp_h << 16));
  HSP_HW_IF_WRITE_PARAMR1(hmw, 0);
  HSP_HW_IF_WRITE_PARAMR2(hmw, in_c | (ou_c << 16));
  HSP_HW_IF_WRITE_PARAMR3(hmw, k_w | (k_h << 16));
  HSP_HW_IF_WRITE_PARAMR4(hmw, (uint32_t) p_bias_data);
  HSP_HW_IF_WRITE_PARAMR5(hmw, ou_w | (ou_h << 16));
  HSP_HW_IF_WRITE_PARAMR6(hmw, *(uint32_t *) & (in_scale));
  HSP_HW_IF_WRITE_PARAMR7(hmw, *(uint32_t *) & (out_scale));
  HSP_HW_IF_WRITE_PARAMR8(hmw, stridex | (stridey << 16));
  HSP_HW_IF_WRITE_PARAMR9(hmw, padx0 | (padx1 << 8) | (pady0 << 16) | (pady1 << 24));
  HSP_HW_IF_WRITE_PARAMR10(hmw, off_in);
  HSP_HW_IF_WRITE_PARAMR11(hmw, off_ou);
  HSP_HW_IF_WRITE_PARAMR12(hmw, sat_min);
  HSP_HW_IF_WRITE_PARAMR13(hmw, sat_max);
  HSP_HW_IF_WRITE_PARAMR14(hmw, (uint32_t) p_wt_scale);

  uint32_t nbLineInPerBlocks = (nb_line_per_blocks * stridey) + k_h - stridey; /* For circular mode */
  uint32_t circiLines = nbLineInPerBlocks; /* For circular mode */
  if (stridey > 1u)
  {
    uint32_t rem = nbLineInPerBlocks % stridey;
    if (rem != 0u)
    {
      circiLines += (stridey - rem);
    }
  }
  if (circiLines > inp_h)
  {
    circiLines = inp_h; /* Circular size is input size */
  }
  HSP_HW_IF_WRITE_PARAMR15(hmw, (circiLines << HSP_CNN_CFG_NB_IN_LINE_SHIFT) |
                           (nb_line_per_blocks << HSP_CNN_CFG_NB_OU_LINE_SHIFT) |
                           HSP_CNN_CFG_MODE_3STEP | HSP_CNN_CFG_MODE_DMA);

  uint32_t *pSrcB = (uint32_t *) p_filter_data;
  uint32_t *pSrcA = (uint32_t *) p_input_data;
  uint32_t *pDst  = (uint32_t *) p_output_data;
  /* And finally sync with DCMD using DCMDPTR registers */
  HSP_HW_IF_WRITE_DCMDPTR0(hmw, (uint32_t) pSrcA);
  HSP_HW_IF_WRITE_DCMDPTR1(hmw, (uint32_t) pSrcB);
  HSP_HW_IF_WRITE_DCMDPTR2(hmw, (uint32_t) pDst);

  HSP_ACC_WAIT_END_OF_DIRECT_COMMAND(hmw);

  if (pHspReg->FWERR == 0x18)
  {
    return HSP_CORE_ERROR;
  }

  return HSP_CORE_OK;
}

/**
  * @brief CNN fully connected function
  * @param hmw                 HSP middleware context.
  * @param in_c                Input dimension channel
  * @param ou_c                Output dimension channel
  * @param *p_input_data       Input data pointer, int8_t data type
  * @param *p_filter_data      Kernel coefficient pointer, int8_t data type
  * @param *p_output_data      Output data pointer, int8_t data type
  * @param *p_bias_data        Bias data pointer, int32_t data type
  * @param in_scale            Input scale
  * @param out_scale           Output scale
  * @param p_wt_scale          Pointer in weight scales (one per output channel)
  * @param off_in              Input offset, int32_t data type
  * @param off_ou              Output offset, int32_t data type
  * @param sat_min             Min sat (Relu), int32_t data type
  * @param sat_max             Max sat (Relu), int32_t data type
  * @retval                    Core status.
  */
hsp_core_status_t HSP_ACC_CnnFullyConnected0D_s8(hsp_engine_context_t *hmw, uint32_t in_c, uint32_t ou_c,
                                                 int8_t *p_input_data, int8_t *p_filter_data, int8_t *p_output_data,
                                                 uint32_t *p_bias_data, float32_t in_scale, float32_t out_scale,
                                                 float32_t wt_scale, uint32_t off_in, uint32_t off_ou,
                                                 uint32_t sat_min, uint32_t sat_max)
{
  /* First of all, wakeup HSP with Direct command */
  HSP_HW_IF_WRITE_DCMDIDR(hmw, (uint32_t) HSP_DIRECT_CMD_CNN_FC_I8);

#ifdef CNN_EVTENR_SUPPORT
  /* Save current EVTENR and clear all enable event for ARM/HSP CNN synchro */
  uint32_t evtenrSave = h_hw_hsp_if[0].hmw.Instance->EVTENR;
  h_hw_hsp_if[0].hmw.Instance->EVTENR = HSP_CNN_EVTENR_CLR;
#endif /* CNN_EVTENR_SUPPORT */

  /* Then update all parameters */
  HSP_HW_IF_WRITE_PARAMR1(hmw, 0);
  HSP_HW_IF_WRITE_PARAMR2(hmw, in_c);
  HSP_HW_IF_WRITE_PARAMR6(hmw, *(uint32_t *) & (wt_scale));
  HSP_HW_IF_WRITE_PARAMR7(hmw, ou_c);
  HSP_HW_IF_WRITE_PARAMR8(hmw, *(uint32_t *) & (in_scale));
  HSP_HW_IF_WRITE_PARAMR9(hmw, *(uint32_t *) & (out_scale));
  HSP_HW_IF_WRITE_PARAMR10(hmw, off_in);
  HSP_HW_IF_WRITE_PARAMR11(hmw, off_ou);
  HSP_HW_IF_WRITE_PARAMR12(hmw, sat_min);
  HSP_HW_IF_WRITE_PARAMR13(hmw, sat_max);

  HSP_HW_IF_WRITE_PARAMR14(hmw, (uint32_t) p_bias_data);
  HSP_HW_IF_WRITE_PARAMR15(hmw, HSP_CNN_CFG_MODE_0STEP | HSP_CNN_CFG_MODE_DMA);

  /* And finally sync with DCMD using DCMDPTR registers */
  HSP_HW_IF_WRITE_DCMDPTR0(hmw, (uint32_t) p_input_data);
  HSP_HW_IF_WRITE_DCMDPTR1(hmw, (uint32_t) p_filter_data);
  HSP_HW_IF_WRITE_DCMDPTR2(hmw, (uint32_t) p_output_data);

  HSP_ACC_WAIT_END_OF_DIRECT_COMMAND(hmw);
  if (pHspReg->FWERR == 0x18)
  {
    return HSP_CORE_ERROR;
  }
  return HSP_CORE_OK;
}

/**
  * @brief CNN fully connected function, with background kernel transfer
  * @param hmw                 HSP middleware context.
  * @param in_c                Input dimension channel
  * @param ou_c                Output dimension channel
  * @param *p_input_data       Input data pointer, int8_t data type
  * @param *p_filter_data      Kernel coefficient pointer, int8_t data type
  * @param *p_output_data      Output data pointer, int8_t data type
  * @param *p_bias_data        Bias data pointer, int32_t data type
  * @param in_scale            Input scale
  * @param out_scale           Output scale
  * @param p_wt_scale          Pointer in weight scales (one per output channel)
  * @param off_in              Input offset, int32_t data type
  * @param off_ou              Output offset, int32_t data type
  * @param sat_min             Min sat (Relu), int32_t data type
  * @param sat_max             Max sat (Relu), int32_t data type
  * @retval                    Core status.
  */
hsp_core_status_t HSP_ACC_CnnFullyConnected1D_s8(hsp_engine_context_t *hmw, uint32_t in_c, uint32_t ou_c,
                                                 int8_t *p_input_data, int8_t *p_filter_data, int8_t *p_output_data,
                                                 uint32_t *p_bias_data, float32_t in_scale, float32_t out_scale,
                                                 float32_t wt_scale, uint32_t off_in, uint32_t off_ou,
                                                 uint32_t sat_min, uint32_t sat_max)
{
  /* First of all, wakeup HSP with Direct command */
  HSP_HW_IF_WRITE_DCMDIDR(hmw, (uint32_t) HSP_DIRECT_CMD_CNN_FC_I8);

#ifdef CNN_EVTENR_SUPPORT
  /* Save current EVTENR and clear all enable event for ARM/HSP CNN synchro */
  uint32_t evtenrSave = h_hw_hsp_if[0].hmw.Instance->EVTENR;
  h_hw_hsp_if[0].hmw.Instance->EVTENR = HSP_CNN_EVTENR_CLR;
#endif /* CNN_EVTENR_SUPPORT */

  /* Force BARB here for the moment */
  pHspReg->CAPCR = HSP_CAPCR_CCNTREN;
  pHspReg->CR |= (2 << HSP_CR_BARB_Pos);

  /* Then update all parameters */
  HSP_HW_IF_WRITE_PARAMR1(hmw, 0);
  HSP_HW_IF_WRITE_PARAMR2(hmw, in_c);
  HSP_HW_IF_WRITE_PARAMR6(hmw, *(uint32_t *) & (wt_scale));
  HSP_HW_IF_WRITE_PARAMR7(hmw, ou_c);
  HSP_HW_IF_WRITE_PARAMR8(hmw, *(uint32_t *) & (in_scale));
  HSP_HW_IF_WRITE_PARAMR9(hmw, *(uint32_t *) & (out_scale));
  HSP_HW_IF_WRITE_PARAMR10(hmw, off_in);
  HSP_HW_IF_WRITE_PARAMR11(hmw, off_ou);
  HSP_HW_IF_WRITE_PARAMR12(hmw, sat_min);
  HSP_HW_IF_WRITE_PARAMR13(hmw, sat_max);

  HSP_HW_IF_WRITE_PARAMR14(hmw, (uint32_t) p_bias_data);
  HSP_HW_IF_WRITE_PARAMR15(hmw, HSP_CNN_CFG_MODE_FCPP | HSP_CNN_CFG_MODE_DMA);

  /* And finally sync with DCMD using DCMDPTR registers */
  HSP_HW_IF_WRITE_DCMDPTR0(hmw, (uint32_t) p_input_data);
  HSP_HW_IF_WRITE_DCMDPTR1(hmw, (uint32_t) p_filter_data);
  HSP_HW_IF_WRITE_DCMDPTR2(hmw, (uint32_t) p_output_data);

  HSP_ACC_WAIT_END_OF_DIRECT_COMMAND(hmw);

#ifdef CNN_EVTENR_SUPPORT
  h_hw_hsp_if[0].hmw.Instance->EVTENR = evtenrSave; /* Restore previous EVTENR value */
#endif /* CNN_EVTENR_SUPPORT */

  if (pHspReg->FWERR == 0x18)
  {
    return HSP_CORE_ERROR;
  }

  return HSP_CORE_OK;
}

/**
  * @brief Direct CNN Pooling function
  * HSP send error report via FWERR register
  * @param hmw                  HSP middleware context.
  * @param in_w                 Input dimension width
  * @param in_h                 Input dimension height
  * @param in_c                 Input dimension channel
  * @param k_w                  Kernel dimension width
  * @param k_h                  Kernel dimension height
  * @param ou_w                 Output dimension width
  * @param ou_h                 Output dimension height
  * @param ou_c                 Output dimension channel
  * @param stridex              Stride on X
  * @param stridey              Stride on Y
  * @param *p_input_data        Input data pointer, int8_t data type
  * @param *p_output_data       Output data pointer, int8_t data type
  * @param sat_min              Min sat (Relu), int32_t data type
  * @param sat_max              Max sat (Relu), int32_t data type
  * @param pool_type            Pooling type, 1 is avg, 0 is max
  * @retval                     Core status.
 */
hsp_core_status_t HSP_ACC_CnnPool0D_s8(hsp_engine_context_t *hmw, uint32_t in_w, uint32_t in_h, uint32_t in_c,
                                       uint32_t k_w, uint32_t k_h, uint32_t ou_w, uint32_t ou_h, uint32_t ou_c,
                                       uint32_t stridex, uint32_t stridey, int8_t *p_input_data, int8_t *p_output_data,
                                       uint32_t sat_min, uint32_t sat_max, uint32_t type)
{
  /* First of all, wakeup HSP with Direct command */
  HSP_HW_IF_WRITE_DCMDIDR(hmw, (uint32_t) HSP_DIRECT_CMD_CNN_POOL_I8);

#ifdef CNN_EVTENR_SUPPORT
  /* Save current EVTENR and clear all enable event for ARM/HSP CNN synchro */
  uint32_t evtenrSave = h_hw_hsp_if[0].hmw.Instance->EVTENR;
  h_hw_hsp_if[0].hmw.Instance->EVTENR = HSP_CNN_EVTENR_CLR;
#endif /* CNN_EVTENR_SUPPORT */

  /* Then update all parameters */
  uint32_t inp_w = in_w;
  uint32_t inp_h = in_h;
  HSP_HW_IF_WRITE_PARAMR0(hmw, inp_w | (inp_h << 16));
  HSP_HW_IF_WRITE_PARAMR1(hmw, 0);
  HSP_HW_IF_WRITE_PARAMR2(hmw, in_c);
  HSP_HW_IF_WRITE_PARAMR3(hmw, k_w | (k_h << 16));
  HSP_HW_IF_WRITE_PARAMR5(hmw, ou_w);
  HSP_HW_IF_WRITE_PARAMR6(hmw, ou_h);
  HSP_HW_IF_WRITE_PARAMR7(hmw, ou_c);
  HSP_HW_IF_WRITE_PARAMR8(hmw, stridex | (stridey << 16));
  HSP_HW_IF_WRITE_PARAMR9(hmw, 0);
  HSP_HW_IF_WRITE_PARAMR12(hmw, sat_min);
  HSP_HW_IF_WRITE_PARAMR13(hmw, sat_max);

  uint32_t circiLines = inp_h;
  uint32_t nb_line_per_blocks = ou_h;

  uint32_t *pSrcA = (uint32_t *) p_input_data;
  uint32_t *pDst  = (uint32_t *) p_output_data;

  HSP_HW_IF_WRITE_PARAMR14(hmw, type);
  HSP_HW_IF_WRITE_PARAMR15(hmw, (circiLines << HSP_CNN_CFG_NB_IN_LINE_SHIFT) |
                           (nb_line_per_blocks << HSP_CNN_CFG_NB_OU_LINE_SHIFT) | HSP_CNN_CFG_MODE_DMA);

  /* And finally sync with DCMD using DCMDPTR registers */
  HSP_HW_IF_WRITE_DCMDPTR0(hmw, (uint32_t) pSrcA);
  HSP_HW_IF_WRITE_DCMDPTR2(hmw, (uint32_t) pDst);

  HSP_ACC_WAIT_END_OF_DIRECT_COMMAND(hmw);

  if (pHspReg->FWERR == 0x18)
  {
    return HSP_CORE_ERROR;
  }

  return HSP_CORE_OK;
}

/**
  * @brief Direct CNN Pooling function with circular in and ping pong on nbOlines out.
  *        For Avg pool, padding is forbidden
  * HSP send error report via FWERR register
  * @param hmw                  HSP middleware context.
  * @param in_w                 Input dimension width
  * @param in_h                 Input dimension height
  * @param in_c                 Input dimension channel
  * @param k_w                  Kernel dimension width
  * @param k_h                  Kernel dimension height
  * @param ou_w                 Output dimension width
  * @param ou_h                 Output dimension height
  * @param ou_c                 Output dimension channel
  * @param stridex              Stride on X
  * @param stridey              Stride on Y
  * @param *p_input_data        Input data pointer, int8_t data type
  * @param *p_output_data       Output data pointer, int8_t data type
  * @param sat_min              Min sat (Relu), int32_t data type
  * @param sat_max              Max sat (Relu), int32_t data type
  * @param padx_l               Pad on X left (only supported for Maxpool)
  * @param padx_r               Pad on X right (only supported for Maxpool)
  * @param pady_t               Pad on Y top (only supported for Maxpool)
  * @param pady_b               Pad on Y bottom (only supported for Maxpool)
  * @param pool_type            0: max pool 1: avg pool
  * @param nb_line_per_blocks   Number of output lines per block
  * @retval                     Core status.
 */
hsp_core_status_t HSP_ACC_CnnPool1D_s8(hsp_engine_context_t *hmw, uint32_t in_w, uint32_t in_h, uint32_t in_c,
                                       uint32_t k_w, uint32_t k_h, uint32_t ou_w, uint32_t ou_h, uint32_t ou_c,
                                       uint32_t stridex, uint32_t stridey, int8_t *p_input_data,
                                       int8_t *p_output_data, uint32_t sat_min, uint32_t sat_max,
                                       uint32_t padx0, uint32_t padx1, uint32_t pady0, uint32_t pady1,
                                       uint32_t type, uint32_t nb_line_per_blocks)
{
  /* ToDo:
  HSP_CHECK_ASSERT_NRV(hmw, (nbOlines > 1));
  HSP_CHECK_ASSERT_NRV(hmw, (nbOlines <= ou_h));
  Check padding = 0 for AVG POOL !!! */

  /* First of all, wakeup HSP with Direct command */
  HSP_HW_IF_WRITE_DCMDIDR(hmw, (uint32_t) HSP_DIRECT_CMD_CNN_POOL_I8);

#ifdef CNN_EVTENR_SUPPORT
  /* Save current EVTENR and clear all enable event for ARM/HSP CNN synchro */
  uint32_t evtenrSave = h_hw_hsp_if[0].hmw.Instance->EVTENR;
  h_hw_hsp_if[0].hmw.Instance->EVTENR = HSP_CNN_EVTENR_CLR;
#endif /* CNN_EVTENR_SUPPORT */

  /* Then update all parameters */
  uint32_t inp_w = in_w + (padx0 + padx1);
  uint32_t inp_h = in_h + (pady0 + pady1);
  HSP_HW_IF_WRITE_PARAMR0(hmw, inp_w | (inp_h << 16));
  HSP_HW_IF_WRITE_PARAMR1(hmw, 0);
  HSP_HW_IF_WRITE_PARAMR2(hmw, in_c);
  HSP_HW_IF_WRITE_PARAMR3(hmw, k_w | (k_h << 16));
  HSP_HW_IF_WRITE_PARAMR5(hmw, ou_w);
  HSP_HW_IF_WRITE_PARAMR6(hmw, ou_h);
  HSP_HW_IF_WRITE_PARAMR7(hmw, ou_c);
  HSP_HW_IF_WRITE_PARAMR8(hmw, stridex | (stridey << 16));
  HSP_HW_IF_WRITE_PARAMR9(hmw, padx0 | (padx1 << 8) | (pady0 << 16) | (pady1 << 24));
  HSP_HW_IF_WRITE_PARAMR12(hmw, sat_min);
  HSP_HW_IF_WRITE_PARAMR13(hmw, sat_max);

  uint32_t circiLines = (stridey > 1) ? (k_h * stridey) : (k_h + stridey); /* For circular mode */
  if ((stridey > 1) && (k_h == 1))
  {
    circiLines = 2 * stridey;
  }
  if (circiLines > inp_h)
  {
    circiLines = inp_h;
  }

  uint32_t *pSrcA = (uint32_t *) p_input_data;
  uint32_t *pDst  = (uint32_t *) p_output_data;

  HSP_HW_IF_WRITE_PARAMR14(hmw, type);

  HSP_HW_IF_WRITE_PARAMR15(hmw, (circiLines << HSP_CNN_CFG_NB_IN_LINE_SHIFT) |
                           (nb_line_per_blocks << HSP_CNN_CFG_NB_OU_LINE_SHIFT) |
                           HSP_CNN_CFG_MODE_PCIRC | HSP_CNN_CFG_MODE_DMA);

  /* And finally sync with DCMD using DCMDPTR registers */
  HSP_HW_IF_WRITE_DCMDPTR0(hmw, (uint32_t) pSrcA);
  HSP_HW_IF_WRITE_DCMDPTR2(hmw, (uint32_t) pDst);

  HSP_ACC_WAIT_END_OF_DIRECT_COMMAND(hmw);

  if (pHspReg->FWERR == 0x18)
  {
    return HSP_CORE_ERROR;
  }

  return HSP_CORE_OK;
}

/**
  * @brief Direct CNN depthwise function with circular mode
  * Circular input and ping pong output in MEMA and full kernels in MEMB, sync with HSP during HSP output lines
  * HSP send error report via FWERR register
  * @param hmw                 HSP middleware context.
  * @param in_w                Input dimension width
  * @param in_h                Input dimension height
  * @param in_c                Input dimension channel
  * @param k_w                 Kernel dimension width
  * @param k_h                 Kernel dimension height
  * @param ou_w                Output dimension width
  * @param ou_h                Output dimension height
  * @param ou_c                Output dimension channel
  * @param stridex             Stride on X
  * @param stridey             Stride on Y
  * @param *p_input_data       Input data pointer, int8_t data type
  * @param *p_filter_data      Kernel coefficient pointer, int8_t data type
  * @param *p_output_data      Output data pointer, int8_t data type
  * @param *p_bias_data        Bias data pointer, int32_t data type
  * @param in_scale            Input scale
  * @param out_scale           Output scale
  * @param p_wt_scale          Pointer in weight scales (one per output channel)
  * @param off_in              Input offset, int32_t data type
  * @param off_ou              Output offset, int32_t data type
  * @param sat_min             Min sat (Relu), int32_t data type
  * @param sat_max             Max sat (Relu), int32_t data type
  * @param padx_l              Pad on X left
  * @param padx_r              Pad on X right
  * @param pady_t              Pad on Y top
  * @param pady_b              Pad on Y bottom
  * @retval                    Core status.
  */
hsp_core_status_t HSP_ACC_CnnConvDepthwise1D_s8(hsp_engine_context_t *hmw,
                                                uint32_t in_w, uint32_t in_h, uint32_t in_c,
                                                uint32_t k_w, uint32_t k_h,
                                                uint32_t ou_w, uint32_t ou_h, uint32_t ou_c,
                                                uint32_t stridex, uint32_t stridey,
                                                int8_t *p_input_data, int8_t *p_filter_data, int8_t *p_output_data,
                                                int32_t *p_bias_data,
                                                float32_t in_scale, float32_t out_scale, const float32_t *p_wt_scale,
                                                int32_t off_in, int32_t off_ou, int32_t sat_min, int32_t sat_max,
                                                uint32_t padx_l, uint32_t padx_r, uint32_t pady_t, uint32_t pady_b)
{
  int32_t *pBias = (int32_t *)p_bias_data;
  int8_t *pSrcB = (int8_t *) p_filter_data;
  int8_t *pSrcA = (int8_t *) p_input_data;
  int8_t *pDst  = (int8_t *) p_output_data;

  /* First of all, wakeup HSP with Direct command */
  HSP_HW_IF_WRITE_DCMDIDR(hmw, HSP_DIRECT_CMD_CNN_CONVDW_I8);

#ifdef CNN_EVTENR_SUPPORT
  /* Save current EVTENR and clear all enable event for ARM/HSP CNN synchro */
  uint32_t evtenrSave = ((HSP_HandleTypeDef *)(hmw->hdriver))->Instance->EVTENR;
  ((HSP_HandleTypeDef *)(hmw->hdriver))->Instance->EVTENR = HSP_CNN_EVTENR_CLR;
#endif /* CNN_EVTENR_SUPPORT */

  /* Then update all parameters */
  uint32_t inp_w = in_w + (padx_l + padx_r);
  uint32_t inp_h = in_h + (pady_t + pady_b);

  /* Then update all parameters */
  HSP_HW_IF_WRITE_PARAMR0(hmw, inp_w | (inp_h << 16));
  HSP_HW_IF_WRITE_PARAMR1(hmw, 0);
  HSP_HW_IF_WRITE_PARAMR2(hmw, in_c | (ou_c << 16));
  HSP_HW_IF_WRITE_PARAMR3(hmw, k_w | (k_h << 16));
  HSP_HW_IF_WRITE_PARAMR4(hmw, padx_l | (padx_r << 8) | (pady_t << 16) | (pady_b << 24));
  HSP_HW_IF_WRITE_PARAMR5(hmw, ou_w | (ou_h << 16));
  HSP_HW_IF_WRITE_PARAMR6(hmw, *(uint32_t *) & (in_scale));
  HSP_HW_IF_WRITE_PARAMR7(hmw, *(uint32_t *) & (out_scale));
  HSP_HW_IF_WRITE_PARAMR8(hmw, stridex | (stridey << 16));
  HSP_HW_IF_WRITE_PARAMR9(hmw, off_in);
  HSP_HW_IF_WRITE_PARAMR10(hmw, off_ou);
  HSP_HW_IF_WRITE_PARAMR11(hmw, sat_min);
  HSP_HW_IF_WRITE_PARAMR12(hmw, sat_max);
  HSP_HW_IF_WRITE_PARAMR13(hmw, (uint32_t) pBias); /* bias followed by quant */
  HSP_HW_IF_WRITE_PARAMR14(hmw, (uint32_t) p_wt_scale);

  uint32_t circiLines = (stridey > 1) ? (k_h * stridey) : (k_h + stridey); /* For circular mode */
  if ((stridey > 1) && (k_h == 1))
  {
    circiLines = 2 * stridey;
  }
  if (circiLines > inp_h)
  {
    circiLines = inp_h;
  }

  HSP_HW_IF_WRITE_PARAMR15(hmw, (circiLines << HSP_CNN_CFG_NB_IN_LINE_SHIFT) |
                           (2 << HSP_CNN_CFG_NB_OU_LINE_SHIFT) |  HSP_CNN_CFG_MODE_1STEP | HSP_CNN_CFG_MODE_DMA);

  /* And finally sync with DCMD using DCMDPTR registers */
  HSP_HW_IF_WRITE_DCMDPTR0(hmw, (uint32_t)pSrcA);
  HSP_HW_IF_WRITE_DCMDPTR1(hmw, (uint32_t)pSrcB);
  HSP_HW_IF_WRITE_DCMDPTR2(hmw, (uint32_t)pDst);

  HSP_ACC_WAIT_END_OF_DIRECT_COMMAND(hmw);

  if (pHspReg->FWERR == 0x18)
  {
    return HSP_CORE_ERROR;
  }

  return HSP_CORE_OK;
}

/**
  * Does not support nb chan <= 4
  * @brief Direct CNN depthwise function with circular mode in 2 steps with padding
  * Circular input and ping pong output in MEMA and full kernels in MEMB, sync with HSP during HSP output lines
  * Split code in 2 steps
  * First loop is on kernel to load all kernels, while HSP working on first channel
  * Then loop on all other channels
  * HSP send error report via FWERR register
  * @param hmw                 HSP middleware context.
  * @param in_w                Input dimension width
  * @param in_h                Input dimension height
  * @param in_c                Input dimension channel
  * @param k_w                 Kernel dimension width
  * @param k_h                 Kernel dimension height
  * @param ou_w                Output dimension width
  * @param ou_h                Output dimension height
  * @param ou_c                Output dimension channel
  * @param stridex             Stride on X
  * @param stridey             Stride on Y
  * @param *p_input_data       Input data pointer, int8_t data type
  * @param *p_filter_data      Kernel coefficient pointer, int8_t data type
  * @param *p_output_data      Output data pointer, int8_t data type
  * @param *p_bias_data        Bias data pointer, int32_t data type
  * @param in_scale            Input scale
  * @param out_scale           Output scale
  * @param p_wt_scale          Pointer in weight scales (one per output channel)
  * @param off_in              Input offset, int32_t data type
  * @param off_ou              Output offset, int32_t data type
  * @param sat_min             Min sat (Relu), int32_t data type
  * @param sat_max             Max sat (Relu), int32_t data type
  * @param padx_l              Pad on X left
  * @param padx_r              Pad on X right
  * @param pady_t              Pad on Y top
  * @param pady_b              Pad on Y bottom
  * @param nb_line_per_blocks  Number of output lines per output buffer
  * @retval                    Core status.
  */
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
                                                uint32_t nb_line_per_blocks)
{
  int8_t *pSrcB = p_filter_data;
  int8_t *pSrcA = p_input_data;
  int8_t *pDst = p_output_data;
  int32_t *pBias = p_bias_data;

  /* First of all, wakeup HSP with Direct command */
  HSP_HW_IF_WRITE_DCMDIDR(hmw, HSP_DIRECT_CMD_CNN_CONVDW_I8);

#ifdef CNN_EVTENR_SUPPORT
  /* Save current EVTENR and clear all enable event for ARM/HSP CNN synchro */
  uint32_t evtenrSave = ((HSP_HandleTypeDef *)(hmw->hdriver))->Instance->EVTENR;
  ((HSP_HandleTypeDef *)(hmw->hdriver))->Instance->EVTENR = HSP_CNN_EVTENR_CLR;
#endif /* CNN_EVTENR_SUPPORT */

  /* Then update all parameters */
  uint32_t inp_w = in_w + (padx_l + padx_r);
  uint32_t inp_h = in_h + (pady_t + pady_b);

  /* Then update all parameters */
  HSP_HW_IF_WRITE_PARAMR0(hmw, inp_w | (inp_h << 16));
  HSP_HW_IF_WRITE_PARAMR1(hmw, 0);
  HSP_HW_IF_WRITE_PARAMR2(hmw, in_c | (ou_c << 16));
  HSP_HW_IF_WRITE_PARAMR3(hmw, k_w | (k_h << 16));
  HSP_HW_IF_WRITE_PARAMR4(hmw, padx_l | (padx_r << 8) | (pady_t << 16) | (pady_b << 24));
  HSP_HW_IF_WRITE_PARAMR5(hmw, ou_w | (ou_h << 16));
  HSP_HW_IF_WRITE_PARAMR6(hmw, *(uint32_t *) & (in_scale));
  HSP_HW_IF_WRITE_PARAMR7(hmw, *(uint32_t *) & (out_scale));
  HSP_HW_IF_WRITE_PARAMR8(hmw, stridex | (stridey << 16));
  HSP_HW_IF_WRITE_PARAMR9(hmw, off_in);
  HSP_HW_IF_WRITE_PARAMR10(hmw, off_ou);
  HSP_HW_IF_WRITE_PARAMR11(hmw, sat_min);
  HSP_HW_IF_WRITE_PARAMR12(hmw, sat_max);
  HSP_HW_IF_WRITE_PARAMR13(hmw, (uint32_t) pBias); /* bias followed by quant */
  HSP_HW_IF_WRITE_PARAMR14(hmw, (uint32_t) p_wt_scale);

  uint32_t circiLines = (stridey > 1) ? (k_h * stridey) : (k_h + stridey); /* For circular mode */
  if ((stridey > 1) && (k_h == 1))
  {
    circiLines = 2 * stridey;
  }
  if (circiLines > inp_h)
  {
    circiLines = inp_h;
  }

  HSP_HW_IF_WRITE_PARAMR15(hmw, (circiLines << HSP_CNN_CFG_NB_IN_LINE_SHIFT) |
                           (nb_line_per_blocks << HSP_CNN_CFG_NB_OU_LINE_SHIFT) |
                           HSP_CNN_CFG_MODE_2STEP | HSP_CNN_CFG_MODE_DMA);

  /* And finally sync with DCMD using DCMDPTR registers */
  HSP_HW_IF_WRITE_DCMDPTR0(hmw, (uint32_t) pSrcA);
  HSP_HW_IF_WRITE_DCMDPTR1(hmw, (uint32_t) pSrcB);
  HSP_HW_IF_WRITE_DCMDPTR2(hmw, (uint32_t) pDst);

  HSP_ACC_WAIT_END_OF_DIRECT_COMMAND(hmw);

  if (pHspReg->FWERR == 0x18)
  {
    return HSP_CORE_ERROR;
  }

  return HSP_CORE_OK;
}

/**
  * Does not support nb chan <= 4
  * @brief Direct CNN depthwise function with circular mode in 3 steps with padding
  * Circular input and ping pong output in MEMA and full kernels in MEMB, sync with HSP during HSP output lines
  * Split code in 3 steps
  * First step, loop on all input lines with first kernel to get lines from ARM, sync on input line
  * Then loop on all channel (exclude first and last) as classical cio sync by output channel
  * And finally loop on last channel, sync on output line
  * Then play again 3 steps if necessary
  * HSP send error report via FWERR register
  * @param hmw                 HSP middleware context.
  * @param in_w                Input dimension width
  * @param in_h                Input dimension height
  * @param in_c                Input dimension channel
  * @param k_w                 Kernel dimension width
  * @param k_h                 Kernel dimension height
  * @param ou_w                Output dimension width
  * @param ou_h                Output dimension height
  * @param ou_c                Output dimension channel
  * @param stridex             Stride on X
  * @param stridey             Stride on Y
  * @param *p_input_data       Input data pointer, int8_t data type
  * @param *p_filter_data      Kernel coefficient pointer, int8_t data type
  * @param *p_output_data      Output data pointer, int8_t data type
  * @param *p_bias_data        Bias data pointer, int32_t data type
  * @param in_scale            Input scale
  * @param out_scale           Output scale
  * @param p_wt_scale          Pointer in weight scales (one per output channel)
  * @param off_in              Input offset, int32_t data type
  * @param off_ou              Output offset, int32_t data type
  * @param sat_min             Min sat (Relu), int32_t data type
  * @param sat_max             Max sat (Relu), int32_t data type
  * @param padx_l              Pad on X left
  * @param padx_r              Pad on X right
  * @param pady_t              Pad on Y top
  * @param pady_b              Pad on Y bottom
  * @param nb_line_per_blocks  Represents the Nb line to output in buffer and
  *                            the Nb line in input buffer multiplied by the stride y.
  * @retval                    Core status.
  */
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
                                                uint32_t nb_line_per_blocks)
{
  int8_t *pSrcB = p_filter_data;
  int8_t *pSrcA = p_input_data;
  int8_t *pDst = p_output_data;
  int32_t *pBias = p_bias_data;

  /* First of all, wakeup HSP with Direct command */
  HSP_HW_IF_WRITE_DCMDIDR(hmw, HSP_DIRECT_CMD_CNN_CONVDW_I8);

#ifdef CNN_EVTENR_SUPPORT
  /* Save current EVTENR and clear all enable event for ARM/HSP CNN synchro */
  uint32_t evtenrSave = ((HSP_HandleTypeDef *)(hmw->hdriver))->Instance->EVTENR;
  ((HSP_HandleTypeDef *)(hmw->hdriver))->Instance->EVTENR = HSP_CNN_EVTENR_CLR;
#endif /* CNN_EVTENR_SUPPORT */

  /* Then update all parameters */
  uint32_t inp_w = in_w + (padx_l + padx_r);
  uint32_t inp_h = in_h + (pady_t + pady_b);

  /* Then update all parameters */
  HSP_HW_IF_WRITE_PARAMR0(hmw, inp_w | (inp_h << 16));
  HSP_HW_IF_WRITE_PARAMR1(hmw, 0); /* shared mem offset */
  HSP_HW_IF_WRITE_PARAMR2(hmw, in_c | (ou_c << 16));
  HSP_HW_IF_WRITE_PARAMR3(hmw, k_w | (k_h << 16));
  HSP_HW_IF_WRITE_PARAMR4(hmw, padx_l | (padx_r << 8) | (pady_t << 16) | (pady_b << 24));
  HSP_HW_IF_WRITE_PARAMR5(hmw, ou_w | (ou_h << 16));
  HSP_HW_IF_WRITE_PARAMR6(hmw, *(uint32_t *) & (in_scale));
  HSP_HW_IF_WRITE_PARAMR7(hmw, *(uint32_t *) & (out_scale));
  HSP_HW_IF_WRITE_PARAMR8(hmw, stridex | (stridey << 16));
  HSP_HW_IF_WRITE_PARAMR9(hmw, off_in);
  HSP_HW_IF_WRITE_PARAMR10(hmw, off_ou);
  HSP_HW_IF_WRITE_PARAMR11(hmw, sat_min);
  HSP_HW_IF_WRITE_PARAMR12(hmw, sat_max);
  HSP_HW_IF_WRITE_PARAMR13(hmw, (uint32_t) pBias); /* bias followed by quant */
  HSP_HW_IF_WRITE_PARAMR14(hmw, (uint32_t) p_wt_scale);

  uint32_t nbLineInPerBlocks = (nb_line_per_blocks * stridey) + k_h - stridey; /* For circular mode */
  uint32_t circiLines = nbLineInPerBlocks; /* For circular mode */
  if (stridey > 1u)
  {
    uint32_t rem = nbLineInPerBlocks % stridey;
    if (rem != 0u)
    {
      circiLines += (stridey - rem);
    }
  }
  if (circiLines > inp_h)
  {
    circiLines = inp_h; /* Circular size is input size */
  }

  HSP_HW_IF_WRITE_PARAMR15(hmw, (circiLines << HSP_CNN_CFG_NB_IN_LINE_SHIFT) |
                           (nb_line_per_blocks << HSP_CNN_CFG_NB_OU_LINE_SHIFT) |
                           HSP_CNN_CFG_MODE_3STEP | HSP_CNN_CFG_MODE_DMA);

  /* And finally sync with DCMD using DCMDPTR registers */
  HSP_HW_IF_WRITE_DCMDPTR0(hmw, (uint32_t) pSrcA);
  HSP_HW_IF_WRITE_DCMDPTR1(hmw, (uint32_t) pSrcB);
  HSP_HW_IF_WRITE_DCMDPTR2(hmw, (uint32_t) pDst);

  HSP_ACC_WAIT_END_OF_DIRECT_COMMAND(hmw);

  if (pHspReg->FWERR == 0x18)
  {
    return HSP_CORE_ERROR;
  }

  return HSP_CORE_OK;
}

/**
  * @brief Execute CMSIS CNN Convolution pointwise with coeff fully loaded in memory and
  *        data (input, output) loaded fully.
  * @param hmw             HSP middleware context.
  * @param in_w            Input dimension width
  * @param in_h            Input dimension height
  * @param in_c            Input dimension channel
  * @param ou_w            Output dimension width
  * @param ou_h            Output dimension height
  * @param ou_c            Output dimension channel
  * @param stridex         Stride on X
  * @param stridey         Stride on Y
  * @param *p_input_data   Input data pointer, int8_t data type
  * @param *p_filter_data  Kernel coefficient pointer, int8_t data type
  * @param *p_output_data  Output data pointer, int8_t data type
  * @param *p_bias_data    Bias data pointer, int32_t data type
  * @param in_scale        Input scale
  * @param out_scale       Output scale
  * @param p_wt_scale      Pointer in weight scales (one per output channel)
  * @param off_in          Input offset, int32_t data type
  * @param off_ou          Output offset, int32_t data type
  * @param sat_min         Min sat (Relu), int32_t data type
  * @param sat_max         Max sat (Relu), int32_t data type
  * @retval                Core status.
  * @details
  * Coefficients and data are loaded before running convolution on HSP
  */
hsp_core_status_t HSP_ACC_CnnConvPointwise0D_s8(hsp_engine_context_t *hmw,
                                                uint32_t in_w, uint32_t in_h, uint32_t in_c,
                                                uint32_t ou_w, uint32_t ou_h, uint32_t ou_c,
                                                uint32_t stridex, uint32_t stridey,
                                                int8_t *p_input_data, int8_t *p_filter_data, int8_t *p_output_data,
                                                int32_t *p_bias_data,
                                                float32_t in_scale, float32_t out_scale, const float32_t *p_wt_scale,
                                                int32_t off_in, int32_t off_ou, int32_t sat_min, int32_t sat_max)
{
  /* First of all, wakeup HSP with Direct command */
  HSP_HW_IF_WRITE_DCMDIDR(hmw, HSP_DIRECT_CMD_CNN_CONVPW_I8);

  int8_t *pDst = p_output_data;
  int8_t *pSrcA = p_input_data;
  int8_t *pSrcB = p_filter_data;
  int32_t *pBias = p_bias_data;

#ifdef CNN_EVTENR_SUPPORT
  /*  Save current EVTENR and clear all enable event for ARM/HSP CNN synchro */
  uint32_t evtenrSave = pHspReg->EVTENR;
  pHspReg->EVTENR = HSP_CNN_EVTENR_CLR;
#endif /* CNN_EVTENR_SUPPORT */

  pHspReg->ITFENR = 0xE0000000;

  /* Parameter must be written before accessing blocking register */
  HSP_HW_IF_WRITE_PARAMR0(hmw, in_w | (in_h << 16));
  HSP_HW_IF_WRITE_PARAMR1(hmw, 0); /* Meme shared offset */
  HSP_HW_IF_WRITE_PARAMR2(hmw, in_c);
  HSP_HW_IF_WRITE_PARAMR3(hmw, ou_w | (ou_h << 16));
  HSP_HW_IF_WRITE_PARAMR4(hmw, ou_c);
  HSP_HW_IF_WRITE_PARAMR6(hmw, *(uint32_t *) & (in_scale));
  HSP_HW_IF_WRITE_PARAMR7(hmw, *(uint32_t *) & (out_scale));
  HSP_HW_IF_WRITE_PARAMR8(hmw, (stridex & 0xffff) | (stridey << 16));
  HSP_HW_IF_WRITE_PARAMR9(hmw, (uint32_t)off_in);
  HSP_HW_IF_WRITE_PARAMR10(hmw, (uint32_t)off_ou);
  HSP_HW_IF_WRITE_PARAMR11(hmw, (uint32_t)sat_min);
  HSP_HW_IF_WRITE_PARAMR12(hmw, (uint32_t)sat_max);
  HSP_HW_IF_WRITE_PARAMR13(hmw, (uint32_t)pBias);

  HSP_HW_IF_WRITE_PARAMR14(hmw, (uint32_t)p_wt_scale);
  HSP_HW_IF_WRITE_PARAMR15(hmw, HSP_CNN_CFG_MODE_0STEP | HSP_CNN_CFG_MODE_DMA);

  HSP_HW_IF_WRITE_DCMDPTR0(hmw, (uint32_t)pSrcA);
  HSP_HW_IF_WRITE_DCMDPTR1(hmw, (uint32_t)pSrcB);
  HSP_HW_IF_WRITE_DCMDPTR2(hmw, (uint32_t)pDst);

  HSP_ACC_WAIT_END_OF_DIRECT_COMMAND(hmw);

  if (pHspReg->FWERR == 0x18)
  {
    return HSP_CORE_ERROR;
  }

  return HSP_CORE_OK;
}

/**
  * @brief Execute CMSIS CNN Convolution pointwise with coeff fully loaded in memory and
  *        data (input, output) loaded in circular buffer.
  * @param hmw                 HSP middleware context.
  * @param in_w                Input dimension width
  * @param in_h                Input dimension height
  * @param in_c                Input dimension channel
  * @param ou_w                Output dimension width
  * @param ou_h                Output dimension height
  * @param ou_c                Output dimension channel
  * @param stridex             Stride on X
  * @param stridey             Stride on Y
  * @param *p_input_data       Input data pointer, int8_t data type
  * @param *p_filter_data      Kernel coefficient pointer, int8_t data type
  * @param *p_output_data      Output data pointer, int8_t data type
  * @param *p_bias_data        Bias data pointer, int32_t data type
  * @param in_scale            Input scale
  * @param out_scale           Output scale
  * @param p_wt_scale          Pointer in weight scales (one per output channel)
  * @param off_in              Input offset, int32_t data type
  * @param off_ou              Output offset, int32_t data type
  * @param sat_min             Min sat (Relu), int32_t data type
  * @param sat_max             Max sat (Relu), int32_t data type
  * @param nb_line_per_blocks  Nb line to output in buffer
  * @retval                    Core status.
  * @details
  * Coefficients and data are loaded before running convolution on HSP
  * This variant support channel <= 4
  * @retval               None
  */
hsp_core_status_t HSP_ACC_CnnConvPointwise1D_s8(hsp_engine_context_t *hmw,
                                                uint32_t in_w, uint32_t in_h, uint32_t in_c,
                                                uint32_t ou_w, uint32_t ou_h, uint32_t ou_c,
                                                uint32_t stridex, uint32_t stridey,
                                                int8_t *p_input_data, int8_t *p_filter_data, int8_t *p_output_data,
                                                int32_t *p_bias_data,
                                                float32_t in_scale, float32_t out_scale, const float32_t *p_wt_scale,
                                                int32_t off_in, int32_t off_ou, int32_t sat_min, int32_t sat_max)
{
  int8_t *pDst = p_output_data;
  int8_t *pSrcA = p_input_data;
  int8_t *pSrcB = p_filter_data;
  int32_t *pBias = p_bias_data;

  /* First of all, wakeup HSP with Direct command */
  HSP_HW_IF_WRITE_DCMDIDR(hmw, HSP_DIRECT_CMD_CNN_CONVPW_I8);

#ifdef CNN_EVTENR_SUPPORT
  /*  Save current EVTENR and clear all enable event for ARM/HSP CNN synchro */
  uint32_t evtenrSave = ((HSP_HandleTypeDef *)(hmw->hdriver))->Instance->EVTENR;
  ((HSP_HandleTypeDef *)(hmw->hdriver))->Instance->EVTENR = HSP_CNN_EVTENR_CLR;
#endif /* CNN_EVTENR_SUPPORT */

  /* @todo */
  pHspReg->ITFENR = 0xE0000000;

  /* Parameter must be written before accessing blocking register */
  HSP_HW_IF_WRITE_PARAMR0(hmw, in_w | (in_h << 16));
  HSP_HW_IF_WRITE_PARAMR1(hmw, 0); /* Meme shared offset */
  HSP_HW_IF_WRITE_PARAMR2(hmw, in_c);
  HSP_HW_IF_WRITE_PARAMR3(hmw, ou_w | (ou_h << 16));
  HSP_HW_IF_WRITE_PARAMR4(hmw, ou_c);
  HSP_HW_IF_WRITE_PARAMR6(hmw, *(uint32_t *) & (in_scale));
  HSP_HW_IF_WRITE_PARAMR7(hmw, *(uint32_t *) & (out_scale));
  HSP_HW_IF_WRITE_PARAMR8(hmw, (stridex & 0xffff) | (stridey << 16));
  HSP_HW_IF_WRITE_PARAMR9(hmw, (uint32_t)off_in);
  HSP_HW_IF_WRITE_PARAMR10(hmw, (uint32_t)off_ou);
  HSP_HW_IF_WRITE_PARAMR11(hmw, (uint32_t)sat_min);
  HSP_HW_IF_WRITE_PARAMR12(hmw, (uint32_t)sat_max);

  HSP_HW_IF_WRITE_PARAMR13(hmw, (uint32_t)pBias);

  HSP_HW_IF_WRITE_PARAMR14(hmw, (uint32_t)p_wt_scale);
  /* Choose the circular size buffer */
  HSP_HW_IF_WRITE_PARAMR15(hmw, ((2 << HSP_CNN_CFG_NB_OU_LINE_SHIFT) | (2 << HSP_CNN_CFG_NB_IN_LINE_SHIFT)
                                 | HSP_CNN_CFG_MODE_1STEP | HSP_CNN_CFG_MODE_DMA));

  HSP_HW_IF_WRITE_DCMDPTR0(hmw, (uint32_t)pSrcA);
  HSP_HW_IF_WRITE_DCMDPTR1(hmw, (uint32_t)pSrcB);
  HSP_HW_IF_WRITE_DCMDPTR2(hmw, (uint32_t)pDst);

  HSP_ACC_WAIT_END_OF_DIRECT_COMMAND(hmw);

  if (pHspReg->FWERR == 0x18)
  {
    return HSP_CORE_ERROR;
  }

  return HSP_CORE_OK;
}

/**
  * @brief Execute CMSIS CNN Convolution pointwise with coeff fully loaded in memory by block and data (input, output)
  *        partially loaded in memory.
  *        First loop is on kernel to load all kernels, while HSP working on first channel
  *        Then loop on all other channels.
  * @param hmw                 HSP middleware context.
  * @param in_w                Input dimension width
  * @param in_h                Input dimension height
  * @param in_c                Input dimension channel
  * @param ou_w                Output dimension width
  * @param ou_h                Output dimension height
  * @param ou_c                Output dimension channel
  * @param stridex             Stride on X
  * @param stridey             Stride on Y
  * @param *p_input_data       Input data pointer, int8_t data type
  * @param *p_filter_data      Kernel coefficient pointer, int8_t data type
  * @param *p_output_data      Output data pointer, int8_t data type
  * @param *p_bias_data        Bias data pointer, int32_t data type
  * @param in_scale            Input scale
  * @param out_scale           Output scale
  * @param p_wt_scale          Pointer in weight scales (one per output channel)
  * @param off_in              Input offset, int32_t data type
  * @param off_ou              Output offset, int32_t data type
  * @param sat_min             Min sat (Relu), int32_t data type
  * @param sat_max             Max sat (Relu), int32_t data type
  * @param nb_line_per_blocks  Nb line to output in buffer
  * @retval                    Core status.
  * @details
  * This variant does not support channel <= 4
  */
hsp_core_status_t HSP_ACC_CnnConvPointwise2D_s8(hsp_engine_context_t *hmw,
                                                uint32_t in_w, uint32_t in_h, uint32_t in_c,
                                                uint32_t ou_w, uint32_t ou_h, uint32_t ou_c,
                                                uint32_t stridex, uint32_t stridey,
                                                int8_t *p_input_data, int8_t *p_filter_data, int8_t *p_output_data,
                                                int32_t *p_bias_data,
                                                float32_t in_scale, float32_t out_scale, const float32_t *p_wt_scale,
                                                int32_t off_in, int32_t off_ou, int32_t sat_min, int32_t sat_max,
                                                uint32_t nb_line_per_blocks)
{
  int8_t *pDst = p_output_data;
  int8_t *pSrcA = p_input_data;
  int8_t *pSrcB = p_filter_data;
  int32_t *pBias = p_bias_data;

  /* First of all, wakeup HSP with Direct command */
  HSP_HW_IF_WRITE_DCMDIDR(hmw, HSP_DIRECT_CMD_CNN_CONVPW_I8);

#ifdef CNN_EVTENR_SUPPORT
  /*  Save current EVTENR and clear all enable event for ARM/HSP CNN synchro */
  uint32_t evtenrSave = pHspReg->EVTENR;
  pHspReg->EVTENR = HSP_CNN_EVTENR_CLR;
#endif /* CNN_EVTENR_SUPPORT */

  pHspReg->ITFENR = 0xE0000000;

  uint32_t nbinLine = 2; /* For circular mode */

  /* Parameter must be written before accessing blocking register */
  HSP_HW_IF_WRITE_PARAMR0(hmw, in_w | (in_h << 16));
  HSP_HW_IF_WRITE_PARAMR1(hmw, 0); /* Meme shared offset */
  HSP_HW_IF_WRITE_PARAMR2(hmw, in_c);
  HSP_HW_IF_WRITE_PARAMR3(hmw, ou_w | (ou_h << 16));
  HSP_HW_IF_WRITE_PARAMR4(hmw, ou_c);
  HSP_HW_IF_WRITE_PARAMR6(hmw, *(uint32_t *) & (in_scale));
  HSP_HW_IF_WRITE_PARAMR7(hmw, *(uint32_t *) & (out_scale));
  HSP_HW_IF_WRITE_PARAMR8(hmw, (stridex & 0xffff) | (stridey << 16));
  HSP_HW_IF_WRITE_PARAMR9(hmw, (uint32_t)off_in);
  HSP_HW_IF_WRITE_PARAMR10(hmw, (uint32_t)off_ou);
  HSP_HW_IF_WRITE_PARAMR11(hmw, (uint32_t)sat_min);
  HSP_HW_IF_WRITE_PARAMR12(hmw, (uint32_t)sat_max);
  HSP_HW_IF_WRITE_PARAMR13(hmw, (uint32_t)pBias);

  /* Set circular buffer size and pw cmd mode */
  HSP_HW_IF_WRITE_PARAMR14(hmw, (uint32_t)p_wt_scale);
  HSP_HW_IF_WRITE_PARAMR15(hmw, ((nb_line_per_blocks << HSP_CNN_CFG_NB_OU_LINE_SHIFT)
                                 | (nbinLine << HSP_CNN_CFG_NB_IN_LINE_SHIFT)
                                 | HSP_CNN_CFG_MODE_2STEP | HSP_CNN_CFG_MODE_DMA));
  HSP_HW_IF_WRITE_DCMDPTR0(hmw, (uint32_t)pSrcA);
  HSP_HW_IF_WRITE_DCMDPTR1(hmw, (uint32_t)pSrcB);
  HSP_HW_IF_WRITE_DCMDPTR2(hmw, (uint32_t)pDst);

  HSP_ACC_WAIT_END_OF_DIRECT_COMMAND(hmw);

  if (pHspReg->FWERR == 0x18)
  {
    return HSP_CORE_ERROR;
  }
  return HSP_CORE_OK;
}

/**
  * @brief Execute CMSIS CNN Convolution pointwise in 3 steps. Circular input in MEMA and output in MEMB
  *        and ping pong on kernels in MEMB.
  *        First step: loop on all input lines with first kernel to get lines from ARM, sync on input line
  *        Second step: loop on all channel (exclude first and last) as classical cio sync by output channel
  *        Third step: finally loop on last channel, sync on output line
  *        HSP send error report via FWERR register
  *        Then play again 3 steps if necessary.
  * @param hmw                 HSP middleware context.
  * @param in_w                Input dimension width
  * @param in_h                Input dimension height
  * @param in_c                Input dimension channel
  * @param ou_w                Output dimension width
  * @param ou_h                Output dimension height
  * @param ou_c                Output dimension channel
  * @param stridex             Stride on X
  * @param stridey             Stride on Y
  * @param *p_input_data       Input data pointer, int8_t data type
  * @param *p_filter_data      Kernel coefficient pointer, int8_t data type
  * @param *p_output_data      Output data pointer, int8_t data type
  * @param *p_bias_data        Bias data pointer, int32_t data type
  * @param in_scale            Input scale
  * @param out_scale           Output scale
  * @param p_wt_scale          Pointer in weight scales (one per output channel)
  * @param off_in              Input offset, int32_t data type
  * @param off_ou              Output offset, int32_t data type
  * @param sat_min             Min sat (Relu), int32_t data type
  * @param sat_max             Max sat (Relu), int32_t data type
  * @param nb_line_per_blocks  Nb line to output in buffer
  * @retval                    Core status.
  * @details
  * This variant does not support channel <= 4
  *
  */
hsp_core_status_t HSP_ACC_CnnConvPointwise3D_s8(hsp_engine_context_t *hmw,
                                                uint32_t in_w, uint32_t in_h, uint32_t in_c,
                                                uint32_t ou_w, uint32_t ou_h, uint32_t ou_c,
                                                uint32_t stridex, uint32_t stridey,
                                                int8_t *p_input_data, int8_t *p_filter_data, int8_t *p_output_data,
                                                int32_t *p_bias_data,
                                                float32_t in_scale, float32_t out_scale, const float32_t *p_wt_scale,
                                                int32_t off_in, int32_t off_ou, int32_t sat_min, int32_t sat_max,
                                                uint32_t nb_line_per_blocks)
{
  int8_t *pDst = p_output_data;
  int8_t *pSrcA = p_input_data;
  int8_t *pSrcB = p_filter_data;
  int32_t *pBias = p_bias_data;

  /* First of all, wakeup HSP with Direct command */
  HSP_HW_IF_WRITE_DCMDIDR(hmw, HSP_DIRECT_CMD_CNN_CONVPW_I8);

#ifdef CNN_EVTENR_SUPPORT
  /*  Save current EVTENR and clear all enable event for ARM/HSP CNN synchro */
  uint32_t evtenrSave = pHspReg->EVTENR;
  pHspReg->EVTENR = HSP_CNN_EVTENR_CLR;
#endif /* CNN_EVTENR_SUPPORT */

  pHspReg->ITFENR = 0xE0000000;

  HSP_HW_IF_WRITE_PARAMR0(hmw, in_w | (in_h << 16));
  HSP_HW_IF_WRITE_PARAMR1(hmw, 0); /* Meme shared offset */
  HSP_HW_IF_WRITE_PARAMR2(hmw, in_c);
  HSP_HW_IF_WRITE_PARAMR3(hmw, ou_w | (ou_h << 16));
  HSP_HW_IF_WRITE_PARAMR4(hmw, ou_c);
  HSP_HW_IF_WRITE_PARAMR6(hmw, *(uint32_t *) & (in_scale));
  HSP_HW_IF_WRITE_PARAMR7(hmw, *(uint32_t *) & (out_scale));
  HSP_HW_IF_WRITE_PARAMR8(hmw, (stridex & 0xffff) | (stridey << 16));
  HSP_HW_IF_WRITE_PARAMR9(hmw, (uint32_t)off_in);
  HSP_HW_IF_WRITE_PARAMR10(hmw, (uint32_t)off_ou);
  HSP_HW_IF_WRITE_PARAMR11(hmw, (uint32_t)sat_min);
  HSP_HW_IF_WRITE_PARAMR12(hmw, (uint32_t)sat_max);
  HSP_HW_IF_WRITE_PARAMR13(hmw, (uint32_t)pBias);
  HSP_HW_IF_WRITE_PARAMR14(hmw, (uint32_t)p_wt_scale);

  /* Set circular buffer size and pw cmd mode */
  HSP_HW_IF_WRITE_PARAMR15(hmw, ((nb_line_per_blocks) << HSP_CNN_CFG_NB_IN_LINE_SHIFT) |
                           (nb_line_per_blocks << HSP_CNN_CFG_NB_OU_LINE_SHIFT) |
                           HSP_CNN_CFG_MODE_3STEP | HSP_CNN_CFG_MODE_DMA);

  HSP_HW_IF_WRITE_DCMDPTR0(hmw, (uint32_t)pSrcA);
  HSP_HW_IF_WRITE_DCMDPTR1(hmw, (uint32_t)pSrcB);
  HSP_HW_IF_WRITE_DCMDPTR2(hmw, (uint32_t)pDst);

  HSP_ACC_WAIT_END_OF_DIRECT_COMMAND(hmw);
  if (pHspReg->FWERR == 0x18)
  {
    return HSP_CORE_ERROR;
  }

  return HSP_CORE_OK;
}

/**
  * @}
  */

#endif /* __HSP_DMA__ */

#ifdef __cplusplus
}
#endif /* __cplusplus */
