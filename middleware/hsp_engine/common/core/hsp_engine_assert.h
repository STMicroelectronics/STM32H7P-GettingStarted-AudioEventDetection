/**
  ******************************************************************************
  * @file    hsp_engine_assert.h
  * @brief   HSP Engine assert template file.
  *          This file must be copied to the application folder and renamed
  *          to hsp_engine_assert.h.
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
#ifndef HSP_ENGINE_ASSERT_H
#define HSP_ENGINE_ASSERT_H

#ifdef __cplusplus
extern "C" {
#endif

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Includes ------------------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
#if defined(USE_HSP_ASSERT_DBG_PARAM) && (USE_HSP_ASSERT_DBG_PARAM == 1)
/**
  * @brief  The HSP_ASSERT_DBG_PARAM macro is used for function's parameters check.
  * @param  expr If expr is false, it calls hsp_assert_dbg_param_failed function
  *         which reports the name of the source file and the source
  *         line number of the call that failed.
  *         If expr is true, it returns no value.
  * @retval None
  */
#define HSP_ASSERT_DBG_PARAM(expr) ((expr) ? (void)0U : hsp_assert_dbg_param_failed((uint8_t *)__FILE__, __LINE__))
/* Exported functions ------------------------------------------------------- */
void hsp_assert_dbg_param_failed(uint8_t *file, uint32_t line);
#else /* USE_HSP_ASSERT_DBG_PARAM */
#define HSP_ASSERT_DBG_PARAM(expr) ((void)0U)
#endif /* USE_HSP_ASSERT_DBG_PARAM */

#if defined(USE_HSP_ASSERT_DBG_STATE) && (USE_HSP_ASSERT_DBG_STATE == 1)
/**
  * @brief  The HSP_ASSERT_DBG_STATE macro is used for function's states check.
  * @param  __STATE__ the state filed within the PPP handle
  * @param  __VAL__ the authorized states value(s) to be checked
  *                 can be a combination of states
  * @note   if __STATE__ & __VAL__ is zero (unauthorized state) then
  * @note   assert_dbg_state_failed function is called which reports
  *         the name of the source file and the source line number of the call that failed.
  *         if __STATE__ & __VAL__ is zero (unauthorized state) then, the HSP_ASSERT_DBG_STATE macro returns no value.
  */
#define HSP_ASSERT_DBG_STATE(__STATE__,__VAL__) (((((uint32_t)(__STATE__)) &  ((uint32_t)(__VAL__))) != 0U) ?  \
                                                 (void)0U :                                                    \
                                                 hsp_assert_dbg_state_failed((uint8_t *)__FILE__, __LINE__))
/* Exported functions ------------------------------------------------------- */
void hsp_assert_dbg_state_failed(uint8_t *file, uint32_t line);
#else /* USE_HSP_ASSERT_DBG_STATE */
#define HSP_ASSERT_DBG_STATE(__STATE__,__VAL__) ((void)0U)
#endif /* USE_HSP_ASSERT_DBG_STATE */


#ifdef __cplusplus
}
#endif

#endif /* HSP_ENGINE_ASSERT_H */
