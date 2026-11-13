/**
  ******************************************************************************
  * @file    hsp_proclist_digital_control.c
  * @brief   This file implements the HSP DIGITAL CONTROL Processing functions
  *          used to record a processing list
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

/* Includes ------------------------------------------------------------------*/
#include "hsp_proclist_digital_control.h"
#include "hsp_hw_if.h"
#include "hsp_services.h"

/** @addtogroup HSP_ENGINE
  * @{
  */

/** @addtogroup HSP_MODULES
  * @{
  */

/** @addtogroup HSP_MODULES_PROCLIST
  * @{
  */

/** @addtogroup HSP_MODULES_PROCLIST_DIGITAL_CONTROL_LIBRARY
  * @{
  */
/* Private defines -----------------------------------------------------------*/
/* Private typedef -----------------------------------------------------------*/
/* Private macros ------------------------------------------------------------*/
#define HSP_CHECK_CMD_SIZE_NULL(a, b)
#define HSP_CHECK_ASSERT(a, b)

/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/

/* Exported functions --------------------------------------------------------*/
/** @addtogroup HSP_DIGITAL_CONTROL_Exported_Functions
  * @{
  */
#if defined(__HSP_DMA__)
/**
  * @brief This function is the PI serial controller named SCA_PIDP1_F1
  * @param hmw       HSP middleware context.
  * @param pSrc      Input A Buffer address
  * @param pSet      Input B Buffer address
  * @param pDst      Output Buffer address
  * @param pCfg      Config struct address (hyp_dc_pidpx_ctrl_t)
  * @param ioType    User iotype information
  * @retval          Status returned.
  */
hsp_core_status_t HSP_SEQ_DcPidP1_f32(hsp_engine_context_t *hmw, float32_t *pSrc, float32_t *pSet, float32_t *pDst,
                                      hyp_dc_pidpx_ctrl_t *pCfg, uint32_t ioType)
{
  uint32_t encoded = 0;
  uint32_t ouAddr1;
  uint32_t ouAddr2;
  uint32_t ouAddr3;
  uint32_t ouAddr4;

  if (HSP_UTILITIES_BuildParam(hmw, ioType, &encoded, (uint32_t) pSrc, &ouAddr1,
                               (uint32_t) pSet, &ouAddr2, (uint32_t) pDst, &ouAddr3, 3) == HSP_IF_ERROR)
  {
    return HSP_CORE_ERROR;
  }

  if (HSP_UTILITIES_ToBramABAddress(hmw, (uint32_t) pCfg, &ouAddr4) == HSP_IF_ERROR)
  {
    return HSP_CORE_ERROR;
  }

  HSP_HW_IF_WriteParameter(hmw->hdriver, HSP_HW_IF_PARAM0, ouAddr1);
  HSP_HW_IF_WriteParameter(hmw->hdriver, HSP_HW_IF_PARAM1, ouAddr2);
  HSP_HW_IF_WriteParameter(hmw->hdriver, HSP_HW_IF_PARAM2, ouAddr3);
  HSP_HW_IF_WriteParameter(hmw->hdriver, HSP_HW_IF_PARAM3, ouAddr4);
  HSP_HW_IF_WriteParameter(hmw->hdriver, HSP_HW_IF_PARAM4, 0); /* Must init */
  HSP_HW_IF_WriteParameter(hmw->hdriver, HSP_HW_IF_PARAM15, encoded);

  if (HSP_HW_IF_SendCommand(hmw->hdriver, HSP_CMD_DC_PIDP1_F32) != HSP_IF_OK)
  {
    return HSP_CORE_ERROR;
  }

  return HSP_CORE_OK;
}

/**
  * @brief This function is the PI serial controller named SCA_PIDP1_F1
  * @param hmw      HSP middleware context.
  * @param pSrc      Input A Buffer address
  * @param pSet      Input B Buffer address
  * @param pDst      Output Buffer address
  * @param pCfg      Config struct address
  * @param ioType    User iotype information
  * @retval          Status returned.
  */
hsp_core_status_t HSP_SEQ_DcPidP2_f32(hsp_engine_context_t *hmw, float32_t *pSrc, float32_t *pSet, float32_t *pDst,
                                      hyp_dc_pidpx_ctrl_t *pCfg, uint32_t ioType)
{
  uint32_t encoded = 0;
  uint32_t ouAddr1;
  uint32_t ouAddr2;
  uint32_t ouAddr3;
  uint32_t ouAddr4;

  if (HSP_UTILITIES_BuildParam(hmw, ioType, &encoded, (uint32_t) pSrc, &ouAddr1,
                               (uint32_t) pSet, &ouAddr2, (uint32_t) pDst, &ouAddr3, 3) == HSP_IF_ERROR)
  {
    return HSP_CORE_ERROR;
  }

  if (HSP_UTILITIES_ToBramABAddress(hmw, (uint32_t) pCfg, &ouAddr4) == HSP_IF_ERROR)
  {
    return HSP_CORE_ERROR;
  }

  HSP_HW_IF_WriteParameter(hmw->hdriver, HSP_HW_IF_PARAM0, ouAddr1);
  HSP_HW_IF_WriteParameter(hmw->hdriver, HSP_HW_IF_PARAM1, ouAddr2);
  HSP_HW_IF_WriteParameter(hmw->hdriver, HSP_HW_IF_PARAM2, ouAddr3);
  HSP_HW_IF_WriteParameter(hmw->hdriver, HSP_HW_IF_PARAM3, ouAddr4);
  HSP_HW_IF_WriteParameter(hmw->hdriver, HSP_HW_IF_PARAM4, 0); /* Must init */
  HSP_HW_IF_WriteParameter(hmw->hdriver, HSP_HW_IF_PARAM15, encoded);

  if (HSP_HW_IF_SendCommand(hmw->hdriver, HSP_CMD_DC_PIDP2_F32) != HSP_IF_OK)
  {
    return HSP_CORE_ERROR;
  }

  return HSP_CORE_OK;
}

/**
  * @brief This function is the PI serial controller named SCA_PIDP1_F1
  * @param hmw     HSP middleware context.
  * @param pSrc    Input A Buffer address
  * @param pSet    Input B Buffer address
  * @param pDst    Output Buffer address
  * @param pCfg    Config struct address
  * @param ioType  User iotype information
  * @retval        Status returned.
  */
hsp_core_status_t HSP_SEQ_DcPidP3_f32(hsp_engine_context_t *hmw, float32_t *pSrc, float32_t *pSet, float32_t *pDst,
                                      hyp_dc_pidpx_ctrl_t *pCfg, uint32_t ioType)
{
  uint32_t encoded = 0;
  uint32_t ouAddr1;
  uint32_t ouAddr2;
  uint32_t ouAddr3;
  uint32_t ouAddr4;

  if (HSP_UTILITIES_BuildParam(hmw, ioType, &encoded, (uint32_t) pSrc, &ouAddr1,
                               (uint32_t) pSet, &ouAddr2, (uint32_t) pDst, &ouAddr3, 3) == HSP_IF_ERROR)
  {
    return HSP_CORE_ERROR;
  }

  if (HSP_UTILITIES_ToBramABAddress(hmw, (uint32_t) pCfg, &ouAddr4) == HSP_IF_ERROR)
  {
    return HSP_CORE_ERROR;
  }

  HSP_HW_IF_WriteParameter(hmw->hdriver, HSP_HW_IF_PARAM0, ouAddr1);
  HSP_HW_IF_WriteParameter(hmw->hdriver, HSP_HW_IF_PARAM1, ouAddr2);
  HSP_HW_IF_WriteParameter(hmw->hdriver, HSP_HW_IF_PARAM2, ouAddr3);
  HSP_HW_IF_WriteParameter(hmw->hdriver, HSP_HW_IF_PARAM3, ouAddr4);
  HSP_HW_IF_WriteParameter(hmw->hdriver, HSP_HW_IF_PARAM4, 0); /* Must init */
  HSP_HW_IF_WriteParameter(hmw->hdriver, HSP_HW_IF_PARAM15, encoded);

  if (HSP_HW_IF_SendCommand(hmw->hdriver, HSP_CMD_DC_PIDP3_F32) != HSP_IF_OK)
  {
    return HSP_CORE_ERROR;
  }

  return HSP_CORE_OK;
}

/**
  * @brief This function is the PI parallel controller named SCA_PIP1
  * @param hmw     HSP middleware context.
  * @param pSrc    Input A Buffer address
  * @param pSet    Input B Buffer address
  * @param pDst    Output Buffer address
  * @param pCfg    Config struct address
  * @param ioType  User iotype information
  * @retval        Status returned.
  */
hsp_core_status_t HSP_SEQ_DcPip1_f32(hsp_engine_context_t *hmw, float32_t *pSrc, float32_t *pSet, float32_t *pDst,
                                     hyp_dc_pipx_ctrl_t *pCfg, uint32_t ioType)
{
  uint32_t encoded = 0;
  uint32_t ouAddr1;
  uint32_t ouAddr2;
  uint32_t ouAddr3;
  uint32_t ouAddr4;

  if (HSP_UTILITIES_BuildParam(hmw, ioType, &encoded, (uint32_t) pSrc, &ouAddr1,
                               (uint32_t) pSet, &ouAddr2, (uint32_t) pDst, &ouAddr3, 3) == HSP_IF_ERROR)
  {
    return HSP_CORE_ERROR;
  }

  if (HSP_UTILITIES_ToBramABAddress(hmw, (uint32_t) pCfg, &ouAddr4) == HSP_IF_ERROR)
  {
    return HSP_CORE_ERROR;
  }

  HSP_HW_IF_WriteParameter(hmw->hdriver, HSP_HW_IF_PARAM0, ouAddr1);
  HSP_HW_IF_WriteParameter(hmw->hdriver, HSP_HW_IF_PARAM1, ouAddr2);
  HSP_HW_IF_WriteParameter(hmw->hdriver, HSP_HW_IF_PARAM2, ouAddr3);
  HSP_HW_IF_WriteParameter(hmw->hdriver, HSP_HW_IF_PARAM3, ouAddr4);
  HSP_HW_IF_WriteParameter(hmw->hdriver, HSP_HW_IF_PARAM15, encoded);

  if (HSP_HW_IF_SendCommand(hmw->hdriver, HSP_CMD_DC_PIP1_F32) != HSP_IF_OK)
  {
    return HSP_CORE_ERROR;
  }

  return HSP_CORE_OK;
}

/**
  * @brief This function is the PI parallel controller named SCA_PIP1
  * @param hmw     HSP middleware context.
  * @param pSrc    Input A Buffer address
  * @param pSet    Input B Buffer address
  * @param pDst    Output Buffer address
  * @param pCfg    Config struct address
  * @param ioType  User iotype information
  * @retval        Status returned.
  */
hsp_core_status_t HSP_SEQ_DcPip2_f32(hsp_engine_context_t *hmw, float32_t *pSrc, float32_t *pSet, float32_t *pDst,
                                     hyp_dc_pipx_ctrl_t *pCfg, uint32_t ioType)
{
  uint32_t encoded = 0;
  uint32_t ouAddr1;
  uint32_t ouAddr2;
  uint32_t ouAddr3;
  uint32_t ouAddr4;

  if (HSP_UTILITIES_BuildParam(hmw, ioType, &encoded, (uint32_t) pSrc, &ouAddr1,
                               (uint32_t) pSet, &ouAddr2, (uint32_t) pDst, &ouAddr3, 3) == HSP_IF_ERROR)
  {
    return HSP_CORE_ERROR;
  }

  if (HSP_UTILITIES_ToBramABAddress(hmw, (uint32_t) pCfg, &ouAddr4) == HSP_IF_ERROR)
  {
    return HSP_CORE_ERROR;
  }

  HSP_HW_IF_WriteParameter(hmw->hdriver, HSP_HW_IF_PARAM0, ouAddr1);
  HSP_HW_IF_WriteParameter(hmw->hdriver, HSP_HW_IF_PARAM1, ouAddr2);
  HSP_HW_IF_WriteParameter(hmw->hdriver, HSP_HW_IF_PARAM2, ouAddr3);
  HSP_HW_IF_WriteParameter(hmw->hdriver, HSP_HW_IF_PARAM3, ouAddr4);
  HSP_HW_IF_WriteParameter(hmw->hdriver, HSP_HW_IF_PARAM15, encoded);

  if (HSP_HW_IF_SendCommand(hmw->hdriver, HSP_CMD_DC_PIP2_F32) != HSP_IF_OK)
  {
    return HSP_CORE_ERROR;
  }

  return HSP_CORE_OK;
}

/**
  * @brief This function is the PI parallel controller named DC_PIS2
  * @param hmw     HSP middleware context.
  * @param pSrc    Input A Buffer address
  * @param pSet    Input B Buffer address
  * @param pDst    Output Buffer address
  * @param pCfg    Config struct address
  * @param ioType  User iotype information
  * @retval        Status returned.
  */
hsp_core_status_t HSP_SEQ_DcPis2_f32(hsp_engine_context_t *hmw, float32_t *pSrc, float32_t *pSet, float32_t *pDst,
                                     hyp_dc_pipx_ctrl_t *pCfg, uint32_t ioType)
{
  uint32_t encoded = 0;
  uint32_t ouAddr1;
  uint32_t ouAddr2;
  uint32_t ouAddr3;
  uint32_t ouAddr4;

  if (HSP_UTILITIES_BuildParam(hmw, ioType, &encoded, (uint32_t) pSrc, &ouAddr1,
                               (uint32_t) pSet, &ouAddr2, (uint32_t) pDst, &ouAddr3, 3) == HSP_IF_ERROR)
  {
    return HSP_CORE_ERROR;
  }

  if (HSP_UTILITIES_ToBramABAddress(hmw, (uint32_t) pCfg, &ouAddr4) == HSP_IF_ERROR)
  {
    return HSP_CORE_ERROR;
  }

  HSP_HW_IF_WriteParameter(hmw->hdriver, HSP_HW_IF_PARAM0, ouAddr1);
  HSP_HW_IF_WriteParameter(hmw->hdriver, HSP_HW_IF_PARAM1, ouAddr2);
  HSP_HW_IF_WriteParameter(hmw->hdriver, HSP_HW_IF_PARAM2, ouAddr3);
  HSP_HW_IF_WriteParameter(hmw->hdriver, HSP_HW_IF_PARAM3, ouAddr4);
  HSP_HW_IF_WriteParameter(hmw->hdriver, HSP_HW_IF_PARAM15, encoded);

  if (HSP_HW_IF_SendCommand(hmw->hdriver, HSP_CMD_DC_PIS2_F32) != HSP_IF_OK)
  {
    return HSP_CORE_ERROR;
  }

  return HSP_CORE_OK;
}

/**
  * @brief This function is the PI parallel controller named DC_PIS3
  * @param hmw     HSP middleware context.
  * @param pSrc    Input A Buffer address
  * @param pSet    Input B Buffer address
  * @param pDst    Output Buffer address
  * @param pCfg    Config struct address
  * @param ioType  User iotype information
  * @retval        Status returned.
  */
hsp_core_status_t HSP_SEQ_DcPis3_f32(hsp_engine_context_t *hmw, float32_t *pSrc, float32_t *pSet, float32_t *pDst,
                                     hyp_dc_pis3_ctrl_t *pCfg, uint32_t ioType)
{
  uint32_t encoded = 0;
  uint32_t ouAddr1;
  uint32_t ouAddr2;
  uint32_t ouAddr3;
  uint32_t ouAddr4;

  if (HSP_UTILITIES_BuildParam(hmw, ioType, &encoded, (uint32_t) pSrc, &ouAddr1,
                               (uint32_t) pSet, &ouAddr2, (uint32_t) pDst, &ouAddr3, 3) == HSP_IF_ERROR)
  {
    return HSP_CORE_ERROR;
  }

  if (HSP_UTILITIES_ToBramABAddress(hmw, (uint32_t) pCfg, &ouAddr4) == HSP_IF_ERROR)
  {
    return HSP_CORE_ERROR;
  }

  HSP_HW_IF_WriteParameter(hmw->hdriver, HSP_HW_IF_PARAM0, ouAddr1);
  HSP_HW_IF_WriteParameter(hmw->hdriver, HSP_HW_IF_PARAM1, ouAddr2);
  HSP_HW_IF_WriteParameter(hmw->hdriver, HSP_HW_IF_PARAM2, ouAddr3);
  HSP_HW_IF_WriteParameter(hmw->hdriver, HSP_HW_IF_PARAM3, ouAddr4);
  HSP_HW_IF_WriteParameter(hmw->hdriver, HSP_HW_IF_PARAM15, encoded);

  if (HSP_HW_IF_SendCommand(hmw->hdriver, HSP_CMD_DC_PIS3_F32) != HSP_IF_OK)
  {
    return HSP_CORE_ERROR;
  }

  return HSP_CORE_OK;
}

/**
  * @brief This function is a generic PID controller
  * @param hmw     HSP middleware context.
  * @param pSrc    Input A Buffer address
  * @param pSet    Input B Buffer address
  * @param pDst    Output Buffer address
  * @param pCfg    Config struct address
  * @param ioType  User iotype information
  * @retval        Status returned.
  */
hsp_core_status_t HSP_SEQ_DcGPid_f32(hsp_engine_context_t *hmw, float32_t *pSrc, float32_t *pSet, float32_t *pDst,
                                     hyp_dc_gpid_ctrl_t *pCfg, uint32_t ioType)
{
  uint32_t encoded = 0;
  uint32_t ouAddr1;
  uint32_t ouAddr2;
  uint32_t ouAddr3;
  uint32_t ouAddr4;

  if (HSP_UTILITIES_BuildParam(hmw, ioType, &encoded, (uint32_t) pSrc, &ouAddr1,
                               (uint32_t) pSet, &ouAddr2, (uint32_t) pDst, &ouAddr3, 3) == HSP_IF_ERROR)
  {
    return HSP_CORE_ERROR;
  }

  if (HSP_UTILITIES_ToBramABAddress(hmw, (uint32_t) pCfg, &ouAddr4) == HSP_IF_ERROR)
  {
    return HSP_CORE_ERROR;
  }

  HSP_HW_IF_WriteParameter(hmw->hdriver, HSP_HW_IF_PARAM0, ouAddr1);
  HSP_HW_IF_WriteParameter(hmw->hdriver, HSP_HW_IF_PARAM1, ouAddr2);
  HSP_HW_IF_WriteParameter(hmw->hdriver, HSP_HW_IF_PARAM2, ouAddr3);
  HSP_HW_IF_WriteParameter(hmw->hdriver, HSP_HW_IF_PARAM3, ouAddr4);
  HSP_HW_IF_WriteParameter(hmw->hdriver, HSP_HW_IF_PARAM4, 0); /* Must init */
  HSP_HW_IF_WriteParameter(hmw->hdriver, HSP_HW_IF_PARAM15, encoded);

  if (HSP_HW_IF_SendCommand(hmw->hdriver, HSP_CMD_DC_GPID_F32) != HSP_IF_OK)
  {
    return HSP_CORE_ERROR;
  }

  return HSP_CORE_OK;
}

/**
  * @brief This function is a proportional resonant
  * @param hmw     HSP middleware context.
  * @param pSrc    Input A Buffer address
  * @param pSet    Input B Buffer address
  * @param pDst    Output Buffer address
  * @param pCfg    Config struct address
  * @param pState  State buffer
  * @param ioType  User iotype information
  * @retval        Status returned.
  */
hsp_core_status_t HSP_SEQ_DcPpr1_f32(hsp_engine_context_t *hmw, float32_t *pSrc, float32_t *pSet, float32_t *pDst,
                                     hyp_dc_ppr1_ctrl_t *pCfg, hyp_dc_ppr1_sta_t *pState, uint32_t ioType)
{
  uint32_t encoded = 0;
  uint32_t ouAddr1;
  uint32_t ouAddr2;
  uint32_t ouAddr3;
  uint32_t ouAddr4;
  uint32_t ouAddr5;

  if (HSP_UTILITIES_BuildParam(hmw, ioType, &encoded, (uint32_t) pSrc, &ouAddr1,
                               (uint32_t) pSet, &ouAddr2, (uint32_t) pDst, &ouAddr3, 3) == HSP_IF_ERROR)
  {
    return HSP_CORE_ERROR;
  }

  if (HSP_UTILITIES_ToBramABAddress(hmw, (uint32_t) pCfg, &ouAddr4) == HSP_IF_ERROR)
  {
    return HSP_CORE_ERROR;
  }

  if (HSP_UTILITIES_ToBramABAddress(hmw, (uint32_t) pState, &ouAddr5) == HSP_IF_ERROR)
  {
    return HSP_CORE_ERROR;
  }

  HSP_HW_IF_WriteParameter(hmw->hdriver, HSP_HW_IF_PARAM0, ouAddr1);
  HSP_HW_IF_WriteParameter(hmw->hdriver, HSP_HW_IF_PARAM1, ouAddr2);
  HSP_HW_IF_WriteParameter(hmw->hdriver, HSP_HW_IF_PARAM2, ouAddr3);
  HSP_HW_IF_WriteParameter(hmw->hdriver, HSP_HW_IF_PARAM3, ouAddr4);
  HSP_HW_IF_WriteParameter(hmw->hdriver, HSP_HW_IF_PARAM4, ouAddr5);
  HSP_HW_IF_WriteParameter(hmw->hdriver, HSP_HW_IF_PARAM15, encoded);

  if (HSP_HW_IF_SendCommand(hmw->hdriver, HSP_CMD_DC_PPR1_F32) != HSP_IF_OK)
  {
    return HSP_CORE_ERROR;
  }

  return HSP_CORE_OK;
}

/**
  * @brief The Clarke transform converts the instantaneous stator phases into a three-coordinate
  * stationary vector. This function uses three-phase currents fa, fb and fc to calculate currents
  * in the three-phase orthogonal stator axis fa, fb and fo
  * @param hmw     HSP middleware context.
  * @param pSrc    Input Buffer address (fa, fb and fc)
  * @param pDst    Output Buffer address (fa, fb and fo)
  * @param ioType  User iotype information
  * @retval        Status returned.
  */
hsp_core_status_t HSP_SEQ_DcClarke3_f32(hsp_engine_context_t *hmw, float32_t *pSrc, float32_t *pDst, uint32_t ioType)
{
  uint32_t encoded = 0;
  uint32_t ouAddr1;
  uint32_t ouAddr2;

  if (HSP_UTILITIES_BuildParam(hmw, ioType, &encoded, (uint32_t) pSrc, &ouAddr1,
                               (uint32_t) pDst, &ouAddr2, 0, NULL, 2) == HSP_IF_ERROR)
  {
    return HSP_CORE_ERROR;
  }

  HSP_HW_IF_WriteParameter(hmw->hdriver, HSP_HW_IF_PARAM0, ouAddr1);
  HSP_HW_IF_WriteParameter(hmw->hdriver, HSP_HW_IF_PARAM1, ouAddr2);
  HSP_HW_IF_WriteParameter(hmw->hdriver, HSP_HW_IF_PARAM15, encoded);

  if (HSP_HW_IF_SendCommand(hmw->hdriver, HSP_CMD_DC_CLARKE_3P_F32) != HSP_IF_OK)
  {
    return HSP_CORE_ERROR;
  }

  return HSP_CORE_OK;
}

/**
  * @brief The inverse Clarke transform converts the two-coordinate time invariant vector into
  * instantaneous stator phases.
  * The functions compute fa, fb and fc where fa, fb and fc are the instantaneous stator phases
  * and fa and fb are the two coordinates of the stationary vector, Io represents the homopolar component.
  * @param hmw     HSP middleware context.
  * @param pSrc    Input Buffer address (fa, fb and fo)
  * @param pDst    Output Buffer address (fa, fb and fc)
  * @param ioType  User iotype information
  * @retval        Status returned.
  */
hsp_core_status_t HSP_SEQ_DcIclarke3_f32(hsp_engine_context_t *hmw, float32_t *pSrc, float32_t *pDst, uint32_t ioType)
{
  uint32_t encoded = 0;
  uint32_t ouAddr1;
  uint32_t ouAddr2;

  if (HSP_UTILITIES_BuildParam(hmw, ioType, &encoded, (uint32_t) pSrc, &ouAddr1,
                               (uint32_t) pDst, &ouAddr2, 0, NULL, 2) == HSP_IF_ERROR)
  {
    return HSP_CORE_ERROR;
  }

  HSP_HW_IF_WriteParameter(hmw->hdriver, HSP_HW_IF_PARAM0, ouAddr1);
  HSP_HW_IF_WriteParameter(hmw->hdriver, HSP_HW_IF_PARAM1, ouAddr2);
  HSP_HW_IF_WriteParameter(hmw->hdriver, HSP_HW_IF_PARAM15, encoded);

  if (HSP_HW_IF_SendCommand(hmw->hdriver, HSP_CMD_DC_ICLARKE_3P_F32) != HSP_IF_OK)
  {
    return HSP_CORE_ERROR;
  }

  return HSP_CORE_OK;
}

/**
  * @brief The Park transform can be used to realize the transformation of the fa and the fb currents
  * from the stationary to the moving reference frame and control the spatial relationship
  * between the stator vector current and rotor flux vector.
  * @param hmw     HSP middleware context.
  * @param pTheta  Input angle address
  * @param pSrc    Input Buffer address (fa, fb)
  * @param pDst    Output Buffer address (d, q)
  * @param ioType  User iotype information
  * @retval        Status returned.
  */
hsp_core_status_t HSP_SEQ_DcPark2_f32(hsp_engine_context_t *hmw, float32_t *pTheta, float32_t *pSrc, float32_t *pDst,
                                      uint32_t ioType)
{
  uint32_t encoded = 0;
  uint32_t ouAddr1;
  uint32_t ouAddr2;
  uint32_t ouAddr3;

  if (HSP_UTILITIES_BuildParam(hmw, ioType, &encoded, (uint32_t) pTheta, &ouAddr1,
                               (uint32_t) pSrc, &ouAddr2, (uint32_t) pDst, &ouAddr3, 3) == HSP_IF_ERROR)
  {
    return HSP_CORE_ERROR;
  }

  HSP_HW_IF_WriteParameter(hmw->hdriver, HSP_HW_IF_PARAM0, ouAddr1);
  HSP_HW_IF_WriteParameter(hmw->hdriver, HSP_HW_IF_PARAM1, ouAddr2);
  HSP_HW_IF_WriteParameter(hmw->hdriver, HSP_HW_IF_PARAM2, ouAddr3);
  HSP_HW_IF_WriteParameter(hmw->hdriver, HSP_HW_IF_PARAM15, encoded);

  if (HSP_HW_IF_SendCommand(hmw->hdriver, HSP_CMD_DC_PARK_2P_F32) != HSP_IF_OK)
  {
    return HSP_CORE_ERROR;
  }

  return HSP_CORE_OK;
}

/**
  * @brief The inverse Park transform can be used to convert rotating d and q components back to
  * stationary alpha and beta components
  * @param hmw     HSP middleware context.
  * @param pTheta  Input angle address
  * @param pSrc    Input Buffer address (d, q)
  * @param pDst    Output Buffer address (fa, fb)
  * @param ioType  User iotype information
  * @retval        Status returned.
  */
hsp_core_status_t HSP_SEQ_DcIpark2_f32(hsp_engine_context_t *hmw, float32_t *pTheta, float32_t *pSrc, float32_t *pDst,
                                       uint32_t ioType)
{
  uint32_t encoded = 0;
  uint32_t ouAddr1;
  uint32_t ouAddr2;
  uint32_t ouAddr3;

  if (HSP_UTILITIES_BuildParam(hmw, ioType, &encoded, (uint32_t) pTheta, &ouAddr1,
                               (uint32_t) pSrc, &ouAddr2, (uint32_t) pDst, &ouAddr3, 3) == HSP_IF_ERROR)
  {
    return HSP_CORE_ERROR;
  }

  HSP_HW_IF_WriteParameter(hmw->hdriver, HSP_HW_IF_PARAM0, ouAddr1);
  HSP_HW_IF_WriteParameter(hmw->hdriver, HSP_HW_IF_PARAM1, ouAddr2);
  HSP_HW_IF_WriteParameter(hmw->hdriver, HSP_HW_IF_PARAM2, ouAddr3);
  HSP_HW_IF_WriteParameter(hmw->hdriver, HSP_HW_IF_PARAM15, encoded);

  if (HSP_HW_IF_SendCommand(hmw->hdriver, HSP_CMD_DC_IPARK_2P_F32) != HSP_IF_OK)
  {
    return HSP_CORE_ERROR;
  }

  return HSP_CORE_OK;
}

/**
  * @brief The Park transform can be used to realize the transformation of the fa and the fb currents
  * from the stationary to the moving reference frame and control the spatial relationship
  * between the stator vector current and rotor flux vector.
  * @param hmw     HSP middleware context.
  * @param pTheta  Input angle address: unsigned integer number representing a angle.
  * @param pSrc    Input Buffer address (fa, fb)
  * @param pDst    Output Buffer address (d, q)
  * @param ioType  User iotype information
  * @retval        Status returned.
  */
hsp_core_status_t HSP_SEQ_DcFPark_f32(hsp_engine_context_t *hmw, uint32_t *pTheta, float32_t *pSrc, float32_t *pDst,
                                      uint32_t ioType)
{
  uint32_t encoded = 0;
  uint32_t ouAddr1;
  uint32_t ouAddr2;
  uint32_t ouAddr3;

  if (HSP_UTILITIES_BuildParam(hmw, ioType, &encoded, (uint32_t) pTheta, &ouAddr1,
                               (uint32_t) pSrc, &ouAddr2, (uint32_t) pDst, &ouAddr3, 3) == HSP_IF_ERROR)
  {
    return HSP_CORE_ERROR;
  }

  HSP_HW_IF_WriteParameter(hmw->hdriver, HSP_HW_IF_PARAM0, ouAddr1);
  HSP_HW_IF_WriteParameter(hmw->hdriver, HSP_HW_IF_PARAM1, ouAddr2);
  HSP_HW_IF_WriteParameter(hmw->hdriver, HSP_HW_IF_PARAM2, ouAddr3);
  HSP_HW_IF_WriteParameter(hmw->hdriver, HSP_HW_IF_PARAM15, encoded);

  if (HSP_HW_IF_SendCommand(hmw->hdriver, HSP_CMD_DC_FPARK_F32) != HSP_IF_OK)
  {
    return HSP_CORE_ERROR;
  }

  return HSP_CORE_OK;
}

/**
  * @brief The inverse Park transform can be used to convert rotating d and q components back to
  * stationary alpha and beta components
  * @param hmw     HSP middleware context.
  * @param pTheta  Input angle address: unsigned integer number representing a angle.
  * @param pSrc    Input Buffer address (d, q)
  * @param pDst    Output Buffer address (fa, fb)
  * @param ioType  User iotype information
  * @retval        Status returned.
  */
hsp_core_status_t HSP_SEQ_DcFIpark_f32(hsp_engine_context_t *hmw, uint32_t *pTheta, float32_t *pSrc, float32_t *pDst,
                                       uint32_t ioType)
{
  uint32_t encoded = 0;
  uint32_t ouAddr1;
  uint32_t ouAddr2;
  uint32_t ouAddr3;

  if (HSP_UTILITIES_BuildParam(hmw, ioType, &encoded, (uint32_t) pTheta, &ouAddr1,
                               (uint32_t) pSrc, &ouAddr2, (uint32_t) pDst, &ouAddr3, 3) == HSP_IF_ERROR)
  {
    return HSP_CORE_ERROR;
  }

  HSP_HW_IF_WriteParameter(hmw->hdriver, HSP_HW_IF_PARAM0, ouAddr1);
  HSP_HW_IF_WriteParameter(hmw->hdriver, HSP_HW_IF_PARAM1, ouAddr2);
  HSP_HW_IF_WriteParameter(hmw->hdriver, HSP_HW_IF_PARAM2, ouAddr3);
  HSP_HW_IF_WriteParameter(hmw->hdriver, HSP_HW_IF_PARAM15, encoded);

  if (HSP_HW_IF_SendCommand(hmw->hdriver, HSP_CMD_DC_FIPARK_F32) != HSP_IF_OK)
  {
    return HSP_CORE_ERROR;
  }

  return HSP_CORE_OK;
}
#endif /*__HSP_DMA__ */

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

/**
  * @}
  */
