/**
  **********************************************************************************************************************
  * @file    stm32h7pxx_hal_ramecc.c
  * @author  GPM Application Team
  * @brief   This file provides firmware functions to manage the functionalities
  *          of the RAMs configuration controller peripheral
  **********************************************************************************************************************
    * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  **********************************************************************************************************************
  */

/* Includes ----------------------------------------------------------------------------------------------------------*/
#include "stm32_hal.h"
/** @addtogroup STM32H7Pxx_HAL_Driver
  * @{
  */

/** @addtogroup RAMECC
  * @brief RAMECC HAL module driver
  * @{
  */

/** @defgroup RAMECC_Introduction RAMECC Introduction
  * @{

  - This introduction is under development.

  */
/**
  * @}
  */

/** @defgroup RAMECC_How_To_Use RAMECC How To Use
  * @{
# The RAMECC main features:

  - This section is under development.

  */
/**
  * @}
  */

/** @defgroup RAMECC_Configuration_Table RAMECC Configuration Table
  * @{
## Configuration inside the RAMECC driver

Config defines                    | Description      | Default value     | Note
--------------------------------- | ---------------- | ----------------- | --------------------------------------
PRODUCT                           | from IDE         | NA                | Ex:STM32H7P62XX.
USE_ASSERT_DBG_PARAM              | from IDE         | None              | Enable the parameters asserts.
USE_HAL_RAMECC_MODULE             | from hal_conf.h  | 1                 | Enable the HAL RAMECC module.

  */
/**
  * @}
  */

#if defined (USE_HAL_RAMECC_MODULE) && (USE_HAL_RAMECC_MODULE == 1)

/* Private types -----------------------------------------------------------------------------------------------------*/
/* Private variables -------------------------------------------------------------------------------------------------*/
/* Private constants -------------------------------------------------------------------------------------------------*/

/** @defgroup RAMECC_Private_Constants RAMECC Private Constants
  * @{
  */

/**
  * @}
  */

/* Private macros ----------------------------------------------------------------------------------------------------*/
/** @defgroup RAMECC_Private_Macros RAMECC Private Macros
  * @{
  */

/*! Get RAMECC instance */
#define RAMECC_GET_INSTANCE(instance) ((RAMECC_TypeDef *)((uint32_t)(instance)))

/*! Get RAMECC monitor instance */
#define RAMECC_GET_MONITOR_INSTANCE(instance) ((RAMECC_Monitor_TypeDef *)((uint32_t)(instance)))

/*! Macro to check global interrupts */
#define IS_RAMECC_GLOBAL_INTERRUPT(interrupt) (((interrupt) & (HAL_RAMECC_IT_GLOBAL_SE \
                                                               | HAL_RAMECC_IT_GLOBAL_DE \
                                                               | HAL_RAMECC_IT_GLOBAL_DEBW \
                                                               | HAL_RAMECC_IT_GLOBAL_ALL)) == (interrupt))

/*! Macro to check monitor interrupts */
#define IS_RAMECC_MONITOR_INTERRUPT(interrupt) (((interrupt) & (HAL_RAMECC_IT_MONITOR_SE \
                                                                | HAL_RAMECC_IT_MONITOR_DE \
                                                                | HAL_RAMECC_IT_MONITOR_DEBW)) == (interrupt))

/**
  * @}
  */

/* Exported functions ------------------------------------------------------------------------------------------------*/

/** @addtogroup RAMECC_Exported_Functions
  * @{
  */

/** @addtogroup RAMECC_Exported_Functions_Group1
  * @{
This section provides functions allowing to manage ECC feature provided by the RAMECC peripheral.

- Call the function HAL_RAMECC_EnableGlobalIT() to enable an ECC error global interrupt.

- Call the function HAL_RAMECC_DisableGlobalIT() to disable an ECC error global interrupt.

- Call the function HAL_RAMECC_IsEnabledGlobalIT() to check if an ECC error global interrupt is enabled or disabled.

- Call the function HAL_RAMECC_EnableMonitorIT() to enable an ECC error monitor interrupt.

- Call the function HAL_RAMECC_DisableMonitorIT() to disable an ECC error monitor interrupt.

- Call the function HAL_RAMECC_IsEnabledMonitorIT() to check if an ECC error monitor interrupt is enabled or disabled.

- Call the function HAL_RAMECC_EnableErrorAddressLatching() to enable the ECC error address latching for the given
  monitor instance.

- Call the function HAL_RAMECC_DisableErrorAddressLatching() to disable the ECC error address latching for the given
  monitor instance.

- Call the function HAL_RAMECC_IsEnabledErrorAddressLatching() to check if the ECC error address latching is enabled or
  disabled for the given monitor instance.

- Call the function HAL_RAMECC_ECC_GetFailInfo() to retrieve the ECC fail information for the given monitor instance.
  */

/**
  * @brief  Enable the given global ECC interrupt for the given RAMECC instance.
  * @param  instance RAMECC instance.
  * @param  interrupt
  *         This parameter can be any combination of the following values:
  *         @arg @ref HAL_RAMECC_IT_GLOBAL_SE
  *         @arg @ref HAL_RAMECC_IT_GLOBAL_DE
  *         @arg @ref HAL_RAMECC_IT_GLOBAL_DEBW
  *         @arg @ref HAL_RAMECC_IT_GLOBAL_ALL
  * @retval HAL_OK RAMECC global interrupt has been successfully enabled.
  */
hal_status_t HAL_RAMECC_EnableGlobalIT(hal_ramecc_t instance, uint32_t interrupt)
{
  ASSERT_DBG_PARAM(IS_RAMECC_ALL_INSTANCE(RAMECC_GET_INSTANCE(instance)));
  ASSERT_DBG_PARAM(IS_RAMECC_GLOBAL_INTERRUPT(interrupt));

  LL_RAMECC_EnableGlobalIT(RAMECC_GET_INSTANCE(instance), interrupt);

  return HAL_OK;
}

/**
  * @brief  Disable the given global ECC interrupt for the given RAMECC instance.
  * @param  instance RAMECC instance.
  * @param  interrupt
  *         This parameter can be any combination of the following values:
  *         @arg @ref HAL_RAMECC_IT_GLOBAL_SE
  *         @arg @ref HAL_RAMECC_IT_GLOBAL_DE
  *         @arg @ref HAL_RAMECC_IT_GLOBAL_DEBW
  *         @arg @ref HAL_RAMECC_IT_GLOBAL_ALL
  * @retval HAL_OK RAMECC global interrupt has been successfully disabled.
  */
hal_status_t HAL_RAMECC_DisableGlobalIT(hal_ramecc_t instance, uint32_t interrupt)
{
  ASSERT_DBG_PARAM(IS_RAMECC_ALL_INSTANCE(RAMECC_GET_INSTANCE(instance)));
  ASSERT_DBG_PARAM(IS_RAMECC_GLOBAL_INTERRUPT(interrupt));

  LL_RAMECC_DisableGlobalIT(RAMECC_GET_INSTANCE(instance), interrupt);

  return HAL_OK;
}

/**
  * @brief  Check if the given global ECC interrupt is enabled or disabled for the given RAMECC instance.
  * @param  instance RAMECC instance.
  * @param  interrupt
  *         This parameter can take one of the following values:
  *         @arg @ref HAL_RAMECC_IT_GLOBAL_SE
  *         @arg @ref HAL_RAMECC_IT_GLOBAL_DE
  *         @arg @ref HAL_RAMECC_IT_GLOBAL_DEBW
  *         @arg @ref HAL_RAMECC_IT_GLOBAL_ALL
  * @retval Return value can be one element of \ref hal_ramecc_it_status_t enumeration.
  */
hal_ramecc_it_status_t HAL_RAMECC_IsEnabledGlobalIT(const hal_ramecc_t instance, uint32_t interrupt)
{
  ASSERT_DBG_PARAM(IS_RAMECC_ALL_INSTANCE(RAMECC_GET_INSTANCE(instance)));
  ASSERT_DBG_PARAM(IS_RAMECC_GLOBAL_INTERRUPT(interrupt));

  return (hal_ramecc_it_status_t)LL_RAMECC_IsEnabledGlobalIT(RAMECC_GET_INSTANCE(instance), interrupt);
}

/**
  * @brief  Enable the given monitor ECC interrupt for the given RAMECC instance.
  * @param  instance RAMECC monitor instance.
  * @param  interrupt
  *         This parameter can be any combination of the following values:
  *         @arg @ref HAL_RAMECC_IT_MONITOR_SE
  *         @arg @ref HAL_RAMECC_IT_MONITOR_DE
  *         @arg @ref HAL_RAMECC_IT_MONITOR_DEBW
  *         @arg @ref HAL_RAMECC_IT_MONITOR_ALL
  * @retval HAL_OK RAMECC monitor interrupt has been successfully enabled.
  */
hal_status_t HAL_RAMECC_EnableMonitorIT(hal_ramecc_monitor_t instance, uint32_t interrupt)
{
  ASSERT_DBG_PARAM(IS_RAMECC_MONITOR_ALL_INSTANCE(RAMECC_GET_MONITOR_INSTANCE(instance)));
  ASSERT_DBG_PARAM(IS_RAMECC_MONITOR_INTERRUPT(interrupt));

  LL_RAMECC_EnableMonitorIT(RAMECC_GET_MONITOR_INSTANCE(instance), interrupt);

  return HAL_OK;
}

/**
  * @brief  Disable the given monitor ECC interrupt for the given RAMECC instance.
  * @param  instance RAMECC monitor instance.
  * @param  interrupt
  *         This parameter can be any combination of the following values:
  *         @arg @ref HAL_RAMECC_IT_MONITOR_SE
  *         @arg @ref HAL_RAMECC_IT_MONITOR_DE
  *         @arg @ref HAL_RAMECC_IT_MONITOR_DEBW
  * @retval HAL_OK RAMECC monitor interrupt has been successfully disabled.
  */
hal_status_t HAL_RAMECC_DisableMonitorIT(hal_ramecc_monitor_t instance, uint32_t interrupt)
{
  ASSERT_DBG_PARAM(IS_RAMECC_MONITOR_ALL_INSTANCE(RAMECC_GET_MONITOR_INSTANCE(instance)));
  ASSERT_DBG_PARAM(IS_RAMECC_MONITOR_INTERRUPT(interrupt));

  LL_RAMECC_DisableMonitorIT(RAMECC_GET_MONITOR_INSTANCE(instance), interrupt);

  return HAL_OK;
}

/**
  * @brief  Check if the given monitor ECC interrupt is enabled or disabled for the given RAMECC instance.
  * @param  instance RAMECC monitor instance.
  * @param  interrupt
  *         This parameter can take one of the following values:
  *         @arg @ref HAL_RAMECC_IT_MONITOR_SE
  *         @arg @ref HAL_RAMECC_IT_MONITOR_DE
  *         @arg @ref HAL_RAMECC_IT_MONITOR_DEBW
  * @retval Return value can be one element of \ref hal_ramecc_it_status_t enumeration.
  */
hal_ramecc_it_status_t HAL_RAMECC_IsEnabledMonitorIT(const hal_ramecc_monitor_t instance, uint32_t interrupt)
{
  ASSERT_DBG_PARAM(IS_RAMECC_MONITOR_ALL_INSTANCE(RAMECC_GET_MONITOR_INSTANCE(instance)));
  ASSERT_DBG_PARAM(IS_RAMECC_MONITOR_INTERRUPT(interrupt));

  return (hal_ramecc_it_status_t)LL_RAMECC_IsEnabledMonitorIT(RAMECC_GET_MONITOR_INSTANCE(instance), interrupt);
}

/**
  * @brief  Enable the ECC error address latching for the given RAMECC instance.
  * @param  instance RAMECC monitor instance.
  * @retval HAL_OK RAMECC error address latching has been successfully enabled.
  */
hal_status_t HAL_RAMECC_EnableErrorAddressLatching(hal_ramecc_monitor_t instance)
{
  ASSERT_DBG_PARAM(IS_RAMECC_MONITOR_ALL_INSTANCE(RAMECC_GET_MONITOR_INSTANCE(instance)));

  LL_RAMECC_EnableAddressLatch(RAMECC_GET_MONITOR_INSTANCE(instance));

  return HAL_OK;
}

/**
  * @brief  Disable the ECC error address latching for the given RAMECC instance.
  * @param  instance RAMECC monitor instance.
  * @retval HAL_OK RAMECC error address latching has been successfully disabled.
  */
hal_status_t HAL_RAMECC_DisableErrorAddressLatching(hal_ramecc_monitor_t instance)
{
  ASSERT_DBG_PARAM(IS_RAMECC_MONITOR_ALL_INSTANCE(RAMECC_GET_MONITOR_INSTANCE(instance)));

  LL_RAMECC_DisableAddressLatch(RAMECC_GET_MONITOR_INSTANCE(instance));

  return HAL_OK;
}

/**
  * @brief  Check if the ECC error address latching is enabled or disabled for the given RAMECC instance.
  * @param  instance RAMECC monitor instance.
  * @retval Return value can be one element of \ref hal_ramecc_addr_latching_status_t enumeration.
  */
hal_ramecc_addr_latching_status_t HAL_RAMECC_IsEnabledErrorAddressLatching(const hal_ramecc_monitor_t instance)
{
  ASSERT_DBG_PARAM(IS_RAMECC_MONITOR_ALL_INSTANCE(RAMECC_GET_MONITOR_INSTANCE(instance)));

  return (hal_ramecc_addr_latching_status_t)LL_RAMECC_IsEnabledAddressLatch(RAMECC_GET_MONITOR_INSTANCE(instance));
}

/**
  * @brief   Get the ECC fail information.
  * @param   instance RAMECC monitor instance.
  * @param   p_info Pointer to a @ref hal_ramecc_fail_info_t structure.
  */
void HAL_RAMECC_ECC_GetFailInfo(const hal_ramecc_monitor_t instance, hal_ramecc_fail_info_t *p_info)
{
  uint32_t flags;

  ASSERT_DBG_PARAM(p_info != NULL);
  ASSERT_DBG_PARAM(IS_RAMECC_MONITOR_ALL_INSTANCE(RAMECC_GET_MONITOR_INSTANCE(instance)));


  flags = LL_RAMECC_ReadFlag(RAMECC_GET_MONITOR_INSTANCE(instance), LL_RAMECC_FLAG_ALL);

  if (flags == 0U)
  {
    p_info->type = HAL_RAMECC_ERROR_ECC_NONE;
  }
  else
  {
    p_info->address = LL_RAMECC_GetErrorAddress(RAMECC_GET_MONITOR_INSTANCE(instance));
    p_info->data = (uint64_t)LL_RAMECC_GetErrorDataLowBytes(RAMECC_GET_MONITOR_INSTANCE(instance));
    if (instance != HAL_RAMECC_MONITOR_BKPSRAM)
    {
      p_info->data += (((uint64_t)LL_RAMECC_GetErrorDataHighBytes(RAMECC_GET_MONITOR_INSTANCE(instance))) << 32U);
    }
    p_info->code = LL_RAMECC_GetErrorCode(RAMECC_GET_MONITOR_INSTANCE(instance));

    if ((flags & LL_RAMECC_FLAG_DE) != 0U)
    {
      p_info->type = HAL_RAMECC_ERROR_ECC_DE;
    }
    else if ((flags & LL_RAMECC_FLAG_DEBW) != 0U)
    {
      p_info->type = HAL_RAMECC_ERROR_ECC_DEBW;
    }
    else
    {
      p_info->type = HAL_RAMECC_ERROR_ECC_SE;
    }
  }
}
/**
  * @}
  */

/** @addtogroup RAMECC_Exported_Functions_Group5
  * @{

This section provides functions to handle RAMECC interrupts and register different callbacks.
- Call the function HAL_RAMECC_IRQHandler() within RAMECC vector to handle any RAMECC interrupt. This API must
 be executed in handler mode.
- The function HAL_RAMECC_ErrorCallback() is to be redefined within user application for the error callback.
  */

/**
  * @brief  Handle RAMECC interrupt request.
  * @param  instance RAMECC instance.
  */
void HAL_RAMECC_IRQHandler(hal_ramecc_monitor_t instance)
{
  uint32_t flags;

  ASSERT_DBG_PARAM(IS_RAMECC_MONITOR_ALL_INSTANCE(RAMECC_GET_MONITOR_INSTANCE(instance)));

  flags = LL_RAMECC_ReadFlag(RAMECC_GET_MONITOR_INSTANCE(instance), LL_RAMECC_FLAG_ALL);

  /* Single Error Interrupt Management */
  if ((LL_RAMECC_IsEnabledMonitorIT_SE(RAMECC_GET_MONITOR_INSTANCE(instance)) != 0U) \
      && ((flags & LL_RAMECC_FLAG_SE) != 0U))
  {
    HAL_RAMECC_ErrorCallback(instance);
    LL_RAMECC_ClearFlag_SE(RAMECC_GET_MONITOR_INSTANCE(instance));
  }

  /* Double Error Interrupt Management */
  if ((LL_RAMECC_IsEnabledMonitorIT_DE(RAMECC_GET_MONITOR_INSTANCE(instance)) != 0U) \
      && ((flags & LL_RAMECC_FLAG_DE) != 0U))
  {
    HAL_RAMECC_ErrorCallback(instance);
    LL_RAMECC_ClearFlag_DE(RAMECC_GET_MONITOR_INSTANCE(instance));
  }

  /* Double Error Interrupt Management */
  if ((LL_RAMECC_IsEnabledMonitorIT_DEBW(RAMECC_GET_MONITOR_INSTANCE(instance)) != 0U) \
      && ((flags & LL_RAMECC_FLAG_DEBW) != 0U))
  {
    HAL_RAMECC_ErrorCallback(instance);
    LL_RAMECC_ClearFlag_DEBW(RAMECC_GET_MONITOR_INSTANCE(instance));
  }
}

/**
  * @brief  RAMECC error callback.
  * @param  instance RAMECC monitor instance.
  */
__WEAK void HAL_RAMECC_ErrorCallback(hal_ramecc_monitor_t instance)
{
  /* Prevent unused argument(s) compilation warning */
  STM32_UNUSED(instance);

  /* NOTE : This function must not be modified, when the callback is needed,
            the HAL_RAMECC_ErrorCallback can be implemented in
            the user file.                                                    */
}

/**
  * @}
  */

/**
  * @}
  */
#endif /* USE_HAL_RAMECC_MODULE */

/**
  * @}
  */

/**
  * @}
  */
