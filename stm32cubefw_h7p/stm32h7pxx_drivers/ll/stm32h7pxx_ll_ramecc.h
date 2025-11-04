/**
  **********************************************************************************************************************
  * @file   stm32h7pxx_ll_ramecc.h
  * @author GPM Application Team
  * @brief  Header file of RAMECC LL module.
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
/* Define to prevent recursive inclusion -----------------------------------------------------------------------------*/
#ifndef STM32H7PXX_LL_RAMECC_H
#define STM32H7PXX_LL_RAMECC_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ----------------------------------------------------------------------------------------------------------*/
#include "stm32h7pxx.h"

/** @addtogroup STM32H7Pxx_LL_Driver
  * @{
  */

/** @addtogroup RAMECC_LL RAMECC
  * @{
  */
/* Exported constants ------------------------------------------------------------------------------------------------*/
/** @defgroup RAMECC_LL_Exported_Constants RAMECC LL RAMECC Constants
  * @{
  */

/** @defgroup RAMECC_FLAG RAMECC Monitor Flags
  * @{
  */
#define LL_RAMECC_FLAG_SE       RAMECC_SR_SEDCF         /*!< RAMECC single error detected and corrected flag */
#define LL_RAMECC_FLAG_DE       RAMECC_SR_DEDF          /*!< RAMECC double error detected flag               */
#define LL_RAMECC_FLAG_DEBW     RAMECC_SR_DEBWDF        /*!< RAMECC double error on byte write detected flag */
#define LL_RAMECC_FLAG_ALL      (LL_RAMECC_FLAG_SE \
                                 | LL_RAMECC_FLAG_DE \
                                 | LL_RAMECC_FLAG_DEBW) /*!< RAMECC single error detected and corrected and
                                                             double error detected flags */
/**
  * @}
  */

/** @defgroup RAMECC_Global_Interrupt RAMECC Global Interrupts
  * @{
  */
#define  LL_RAMECC_IT_GLOBAL_SE   RAMECC_IER_GECCSEIE     /*!< RAMECC global single error interrupt               */
#define  LL_RAMECC_IT_GLOBAL_DE   RAMECC_IER_GECCDEIE     /*!< RAMECC global double error interrupt               */
#define  LL_RAMECC_IT_GLOBAL_DEBW RAMECC_IER_GECCDEBWIE   /*!< RAMECC global double error on byte write interrupt */
#define  LL_RAMECC_IT_GLOBAL_ALL  RAMECC_IER_GIE          /*!< RAMECC global all RAMECC interrupts                */
/**
  * @}
  */

/** @defgroup RAMECC_Interrupt RAMECC Interrupts
  * @{
  */
#define LL_RAMECC_IT_MONITOR_SE   RAMECC_CR_ECCSEIE     /*!< RAMECC single error interrupt               */
#define LL_RAMECC_IT_MONITOR_DE   RAMECC_CR_ECCDEIE     /*!< RAMECC double error interrupt               */
#define LL_RAMECC_IT_MONITOR_DEBW RAMECC_CR_ECCDEBWIE   /*!< RAMECC double error on byte write interrupt */
#define LL_RAMECC_IT_MONITOR_ALL  (LL_RAMECC_IT_MONITOR_SE \
                                   | LL_RAMECC_IT_MONITOR_DE \
                                   | LL_RAMECC_IT_MONITOR_DEBW) /*!< RAMECC all RAMECC interrupts        */
/**
  * @}
  */

/**
  * @}
  */

/* Exported macros ---------------------------------------------------------------------------------------------------*/
/** @defgroup RAMECC_LL_Exported_Macros RAMECC Exported Macros
  * @{
  */

/** @defgroup RAMECC_LL_EM_COMMON_READ_REGISTERS Common Read Registers macro
  * @{
  */

/**
  * @brief  Write a value in RAMECC register
  * @param  instance RAMECC Instance
  * @param  reg      Register to be written
  * @param  value    Value to be written in the register
  */
#define LL_RAMECC_WRITE_REG(instance, reg, value) STM32_WRITE_REG((instance)->reg, (value))

/**
  * @brief  Read a value in RAMECC register.
  * @param  instance RAMECC Instance.
  * @param  reg      Register to be read.
  * @return Register value.
  */
#define LL_RAMECC_READ_REG(instance, reg) STM32_READ_REG((instance)->reg)
/**
  * @}
  */

/**
  * @}
  */

/* Exported functions ------------------------------------------------------------------------------------------------*/
/** @defgroup RAMECC_LL_Exported_Functions RAMECC Exported Functions
  * @{
  */

/**
  * @brief  Enable the RAMECC monitor instance address latching error.
  * @rmtoll
  *  CR           ECCELEN            LL_RAMECC_EnableAddressLatch
  * @param  p_ramecc RAMECC Instance.
  */
__STATIC_INLINE void LL_RAMECC_EnableAddressLatch(RAMECC_Monitor_TypeDef *p_ramecc)
{
  STM32_SET_BIT(p_ramecc->CR, RAMECC_CR_ECCELEN);
}

/**
  * @brief  Disable the RAMECC monitor instance address latching error.
  * @rmtoll
  *  CR           ECCELEN            LL_RAMECC_DisableAddressLatch
  * @param  p_ramecc RAMECC Monitor Instance.
  */
__STATIC_INLINE void LL_RAMECC_DisableAddressLatch(RAMECC_Monitor_TypeDef *p_ramecc)
{
  STM32_CLEAR_BIT(p_ramecc->CR, RAMECC_CR_ECCELEN);
}

/**
  * @brief  Check whether the RAMECC monitor instance address latching error is enabled or not.
  * @rmtoll
  *  CR           ECCELEN            LL_RAMECC_IsEnabledAddressLatch
  * @param  p_ramecc RAMECC Monitor Instance.
  * @return State of address latching error (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RAMECC_IsEnabledAddressLatch(const RAMECC_Monitor_TypeDef *p_ramecc)
{
  return ((STM32_READ_BIT(p_ramecc->CR, RAMECC_CR_ECCELEN) == (RAMECC_CR_ECCELEN)) ? 1UL : 0UL);
}

/**
  * @brief  Get the RAMECC error failing address.
  * @rmtoll
  *  FAR           FAR           LL_RAMECC_GetErrorAddress
  * @param  p_ramecc RAMECC Monitor Instance.
  * @return Error address offset.
  */
__STATIC_INLINE uint32_t LL_RAMECC_GetErrorAddress(const RAMECC_Monitor_TypeDef *p_ramecc)
{
  return ((uint32_t)STM32_READ_REG(p_ramecc->FAR));
}

/**
  * @brief  Get the RAMECC error failing data low bytes.
  * @rmtoll
  *  FDRL           FDRL         LL_RAMECC_GetErrorDataLowBytes
  * @param  p_ramecc RAMECC Monitor Instance.
  * @return Error data low bytes.
  */
__STATIC_INLINE uint32_t LL_RAMECC_GetErrorDataLowBytes(const RAMECC_Monitor_TypeDef *p_ramecc)
{
  return ((uint32_t)STM32_READ_REG(p_ramecc->FDRL));
}

/**
  * @brief  Get the RAMECC error failing data high bytes.
  * @rmtoll
  *  FDRH           FDRH         LL_RAMECC_GetErrorDataHighBytes
  * @param  p_ramecc RAMECC Monitor Instance.
  * @return Error data high bytes.
  */
__STATIC_INLINE uint32_t LL_RAMECC_GetErrorDataHighBytes(const RAMECC_Monitor_TypeDef *p_ramecc)
{
  return ((uint32_t)STM32_READ_REG(p_ramecc->FDRH));
}

/**
  * @brief  Get the RAMECC error failing code.
  * @rmtoll
  *  FEC           FEC           LL_RAMECC_GetErrorCode
  * @param  p_ramecc RAMECC Monitor Instance.
  * @return Error code offset.
  */
__STATIC_INLINE uint32_t LL_RAMECC_GetErrorCode(const RAMECC_Monitor_TypeDef *p_ramecc)
{
  return ((uint32_t)STM32_READ_REG(p_ramecc->FECR));
}

/** @defgroup RAMECC_LL_FLAG_Management Flag_Management
  * @{
  */

/**
  * @brief  Clear the RAMECC monitor pending flags
  * @rmtoll
  *  SR           SEDCF           LL_RAMECC_ClearFlag \n
  *  SR           DEDF            LL_RAMECC_ClearFlag \n
  *  SR           DEBWDF          LL_RAMECC_ClearFlag
  * @param  p_ramecc RAMECC Monitor Instance.
  * @param  flags    Flags to clear.
  *         This parameter can be one of the following values:
  *            @arg @ref LL_RAMECC_FLAG_SE   : Single Error Detected and Corrected Flag.
  *            @arg @ref LL_RAMECC_FLAG_DE   : Double Error Detected Flag.
  *            @arg @ref LL_RAMECC_FLAG_DEBW : Double Error on Byte Write Detected Flag.
  *            @arg @ref LL_RAMECC_FLAG_ALL  : RAMECC All Error Flags.
  */
__STATIC_INLINE void LL_RAMECC_ClearFlag(RAMECC_Monitor_TypeDef *p_ramecc, uint32_t flags)
{
  STM32_MODIFY_REG(p_ramecc->SR, flags, ~flags);
}

/**
  * @brief  Clear the RAMECC Single Error Detected and Corrected flag.
  * @rmtoll
  *  SR           SEDCF           LL_RAMECC_ClearFlag_SE
  * @param  p_ramecc RAMECC Monitor Instance.
  */
__STATIC_INLINE void LL_RAMECC_ClearFlag_SE(RAMECC_Monitor_TypeDef *p_ramecc)
{
  STM32_CLEAR_BIT(p_ramecc->SR, LL_RAMECC_FLAG_SE);
}

/**
  * @brief  Clear the RAMECC Double Error Detected flag.
  * @rmtoll
  *  SR           DEDF            LL_RAMECC_ClearFlag_DE
  * @param  p_ramecc RAMECC Monitor Instance.
  */
__STATIC_INLINE void LL_RAMECC_ClearFlag_DE(RAMECC_Monitor_TypeDef *p_ramecc)
{
  STM32_CLEAR_BIT(p_ramecc->SR, LL_RAMECC_FLAG_DE);
}

/**
  * @brief  Clear the RAMECC Double Error on Byte Write Detected flag.
  * @rmtoll
  *  SR           DEBWDF            LL_RAMECC_ClearFlag_DE
  * @param  p_ramecc RAMECC Monitor Instance.
  */
__STATIC_INLINE void LL_RAMECC_ClearFlag_DEBW(RAMECC_Monitor_TypeDef *p_ramecc)
{
  STM32_CLEAR_BIT(p_ramecc->SR, LL_RAMECC_FLAG_DEBW);
}


/**
  * @brief  Clear the RAMECC monitor pending flags
  * @rmtoll
  *  SR           SEDCF           LL_RAMECC_ClearFlag \n
  *  SR           DEDF            LL_RAMECC_ClearFlag \n
  *  SR           DEBWDF          LL_RAMECC_ClearFlag
  * @param  p_ramecc RAMECC Monitor Instance.
  * @param  flags    Flags to read.
  *         This parameter can be one of the following values:
  *            @arg @ref LL_RAMECC_FLAG_SE   : Single Error Detected and Corrected Flag.
  *            @arg @ref LL_RAMECC_FLAG_DE   : Double Error Detected Flag.
  *            @arg @ref LL_RAMECC_FLAG_DEBW : Double Error on Byte Write Detected Flag.
  *            @arg @ref LL_RAMECC_FLAG_ALL  : RAMECC All Error Flags.
  * @retval State of selected flags.
            The return value can be a combination of the following values:
              @arg @ref LL_RAMECC_FLAG_SE
              @arg @ref LL_RAMECC_FLAG_DE
              @arg @ref LL_RAMECC_FLAG_DEBW
              @arg @ref LL_RAMECC_FLAG_ALL
  */
__STATIC_INLINE uint32_t LL_RAMECC_ReadFlag(const RAMECC_Monitor_TypeDef *p_ramecc, uint32_t flags)
{
  return STM32_READ_BIT(p_ramecc->SR, flags);
}

/**
  * @brief  Get the RAMECC Single Error Detected and Corrected flag.
  * @rmtoll
  *  SR           SEDCF               LL_RAMECC_IsActiveFlag_SE
  * @param  p_ramecc RAMECC Monitor Instance.
  * @return State of SE flag (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RAMECC_IsActiveFlag_SE(const RAMECC_Monitor_TypeDef *p_ramecc)
{
  return ((STM32_READ_BIT(p_ramecc->SR, LL_RAMECC_FLAG_SE) == (LL_RAMECC_FLAG_SE)) ? 1UL : 0UL);
}

/**
  * @brief  Get the RAMECC Double Error Detected flag.
  * @rmtoll
  *  SR           DEDF                LL_RAMECC_IsActiveFlag_DE
  * @param  p_ramecc RAMECC Monitor Instance.
  * @return State of DE flag (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RAMECC_IsActiveFlag_DE(const RAMECC_Monitor_TypeDef *p_ramecc)
{
  return ((STM32_READ_BIT(p_ramecc->SR, LL_RAMECC_FLAG_DE) == (LL_RAMECC_FLAG_DE)) ? 1UL : 0UL);
}

/**
  * @brief  Get the RAMECC Double Error on Byte Write Detected flag.
  * @rmtoll
  *  SR           DEBWDF              LL_RAMECC_IsActiveFlag_DEBW
  * @param  p_ramecc RAMECC Monitor Instance.
  * @return State of DEBW flag (1 or 0).
  */
__STATIC_INLINE uint32_t LL_RAMECC_IsActiveFlag_DEBW(const RAMECC_Monitor_TypeDef *p_ramecc)
{
  return ((STM32_READ_BIT(p_ramecc->SR, LL_RAMECC_FLAG_DEBW) == (LL_RAMECC_FLAG_DEBW)) ? 1UL : 0UL);
}

/**
  * @}
  */

/** @defgroup RAMECC_LL_EF_IT_Management IT_Management
  * @{
  */

/**
  * @brief  Enable the specified RAMECC interrupts.
  * @rmtoll
  *  CR           ECCSEIE           LL_RAMECC_EnableMonitorIT \n
  *  CR           ECCDEIE           LL_RAMECC_EnableMonitorIT \n
  *  CR           ECCDEBWIE         LL_RAMECC_EnableMonitorIT
  * @param  p_ramecc RAMECC Instance.
  * @param  mask Interrupt sources to enable.
  *         This parameter can be a combination of the following values:
  *           @arg @ref LL_RAMECC_IT_MONITOR_SE    : Single Error Interrupt Mask.
  *           @arg @ref LL_RAMECC_IT_MONITOR_DE    : Double Error Interrupt Mask.
  *           @arg @ref LL_RAMECC_IT_MONITOR_DEBW  : Double Error on Byte Write Interrupt Mask.
  *           @arg @ref LL_RAMECC_IT_MONITOR_ALL   : All Interrupt Mask.
  */
__STATIC_INLINE void LL_RAMECC_EnableMonitorIT(RAMECC_Monitor_TypeDef *p_ramecc, uint32_t mask)
{
  STM32_SET_BIT(p_ramecc->CR, mask);
}

/**
  * @brief  Disable the specified RAMECC interrupts.
  * @rmtoll
  *  CR           ECCSEIE           LL_RAMECC_DisableMonitorIT \n
  *  CR           ECCDEIE           LL_RAMECC_DisableMonitorIT \n
  *  CR           ECCDEBWIE         LL_RAMECC_DisableMonitorIT
  * @param  p_ramecc RAMECC Instance.
  * @param  mask Interrupt sources to enable.
  *         This parameter can be a combination of the following values:
  *           @arg @ref LL_RAMECC_IT_MONITOR_SE    : Single Error Interrupt Mask.
  *           @arg @ref LL_RAMECC_IT_MONITOR_DE    : Double Error Interrupt Mask.
  *           @arg @ref LL_RAMECC_IT_MONITOR_DEBW  : Double Error on Byte Write Interrupt Mask.
  *           @arg @ref LL_RAMECC_IT_MONITOR_ALL   : All Interrupt Mask.
  */
__STATIC_INLINE void LL_RAMECC_DisableMonitorIT(RAMECC_Monitor_TypeDef *p_ramecc, uint32_t mask)
{
  STM32_CLEAR_BIT(p_ramecc->CR, mask);
}

/**
  * @brief  Check if the specified RAMECC interrupt is enabled or disabled.
  * @rmtoll
  *  IER           GECCSEIE           LL_RAMECC_EnableGlobalIT \n
  *  IER           GECCDEIE           LL_RAMECC_EnableGlobalIT \n
  *  IER           GECCDEBWIE         LL_RAMECC_EnableGlobalIT
  * @param  p_ramecc RAMECC Instance.
  * @param  interrupt Interrupt sources to enable.
  *         This parameter can take one of the following values:
  *           @arg @ref  LL_RAMECC_IT_MONITOR_SE    : Single Error Interrupt Mask.
  *           @arg @ref  LL_RAMECC_IT_MONITOR_DE    : Double Error Interrupt Mask.
  *           @arg @ref  LL_RAMECC_IT_MONITOR_DEBW  : Double Error on Byte Write Interrupt Mask.
  * @return State of the state interrupt (1: enabled or 0: disabled).
  */
__STATIC_INLINE uint32_t LL_RAMECC_IsEnabledMonitorIT(const RAMECC_Monitor_TypeDef *p_ramecc, uint32_t interrupt)
{
  return ((STM32_READ_BIT(p_ramecc->CR,  interrupt) == (interrupt)) ? 1UL : 0UL);
}

/**
  * @brief  Enable the ECC single error RAMECC interrupt.
  * @rmtoll
  *  CR           ECCSEIE              LL_RAMECC_EnableMonitorIT_SE
  * @param  p_ramecc RAMECC Instance.
  */
__STATIC_INLINE void LL_RAMECC_EnableMonitorIT_SE(RAMECC_Monitor_TypeDef *p_ramecc)
{
  STM32_SET_BIT(p_ramecc->CR, LL_RAMECC_IT_MONITOR_SE);
}

/**
  * @brief  Disable the ECC single error RAMECC interrupt.
  * @rmtoll
  *  CR           ECCSEIE              LL_RAMECC_DisableMonitorIT_SE
  * @param  p_ramecc RAMECC Instance.
  */
__STATIC_INLINE void LL_RAMECC_DisableMonitorIT_SE(RAMECC_Monitor_TypeDef *p_ramecc)
{
  STM32_CLEAR_BIT(p_ramecc->CR, LL_RAMECC_IT_MONITOR_SE);
}

/**
  * @brief  Check whether the ECC single error RAMECC interrupt is enabled or not.
  * @rmtoll
  *  CR           ECCSEIE              LL_RAMECC_IsEnabledMonitorIT_SE
  * @param  p_ramecc RAMECC Instance.
  * @return State of ECC single error interrupt (1: enabled or 0: disabled).
  */
__STATIC_INLINE uint32_t LL_RAMECC_IsEnabledMonitorIT_SE(const RAMECC_Monitor_TypeDef *p_ramecc)
{
  return ((STM32_READ_BIT(p_ramecc->CR, LL_RAMECC_IT_MONITOR_SE) == (LL_RAMECC_IT_MONITOR_SE)) ? 1UL : 0UL);
}

/**
  * @brief  Enable the ECC double error RAMECC interrupt.
  * @rmtoll
  *  CR           ECCDEIE              LL_RAMECC_EnableMonitorIT_DE
  * @param  p_ramecc RAMECC Instance.
  */
__STATIC_INLINE void LL_RAMECC_EnableMonitorIT_DE(RAMECC_Monitor_TypeDef *p_ramecc)
{
  STM32_SET_BIT(p_ramecc->CR, LL_RAMECC_IT_MONITOR_DE);
}

/**
  * @brief  Disable the ECC double error RAMECC interrupt.
  * @rmtoll
  *  CR           ECCDEIE              LL_RAMECC_DisableMonitorIT_DE
  * @param  p_ramecc RAMECC Instance.
  */
__STATIC_INLINE void LL_RAMECC_DisableMonitorIT_DE(RAMECC_Monitor_TypeDef *p_ramecc)
{
  STM32_CLEAR_BIT(p_ramecc->CR, LL_RAMECC_IT_MONITOR_DE);
}

/**
  * @brief  Check whether the ECC double error RAMECC interrupt is enabled or not.
  * @rmtoll
  *  CR           ECCDEIE              LL_RAMECC_IsEnabledMonitorIT_DE
  * @param  p_ramecc RAMECC Instance.
  * @return State of ECC double error interrupt (1: enabled or 0: disabled).
  */
__STATIC_INLINE uint32_t LL_RAMECC_IsEnabledMonitorIT_DE(const RAMECC_Monitor_TypeDef *p_ramecc)
{
  return ((STM32_READ_BIT(p_ramecc->CR, LL_RAMECC_IT_MONITOR_DE) == (LL_RAMECC_IT_MONITOR_DE)) ? 1UL : 0UL);
}

/**
  * @brief  Enable the ECC double error RAMECC interrupt.
  * @rmtoll
  *  CR           ECCDEBWIE            LL_RAMECC_EnableMonitorIT_DEBW
  * @param  p_ramecc RAMECC Instance.
  */
__STATIC_INLINE void LL_RAMECC_EnableMonitorIT_DEBW(RAMECC_Monitor_TypeDef *p_ramecc)
{
  STM32_SET_BIT(p_ramecc->CR, LL_RAMECC_IT_MONITOR_DEBW);
}

/**
  * @brief  Disable the ECC double error RAMECC interrupt.
  * @rmtoll
  *  CR           ECCDEBWIE            LL_RAMECC_DisableMonitorIT_DEBW
  * @param  p_ramecc RAMECC Instance.
  */
__STATIC_INLINE void LL_RAMECC_DisableMonitorIT_DEBW(RAMECC_Monitor_TypeDef *p_ramecc)
{
  STM32_CLEAR_BIT(p_ramecc->CR, LL_RAMECC_IT_MONITOR_DEBW);
}

/**
  * @brief  Check whether the ECC double error RAMECC interrupt is enabled or not.
  * @rmtoll
  *  CR           ECCDEBWIE            LL_RAMECC_IsEnabledMonitorIT_DEBW
  * @param  p_ramecc RAMECC Instance.
  * @return State of ECC double error interrupt (1: enabled or 0: disabled).
  */
__STATIC_INLINE uint32_t LL_RAMECC_IsEnabledMonitorIT_DEBW(const RAMECC_Monitor_TypeDef *p_ramecc)
{
  return ((STM32_READ_BIT(p_ramecc->CR, LL_RAMECC_IT_MONITOR_DEBW) == (LL_RAMECC_IT_MONITOR_DEBW)) ? 1UL : 0UL);
}

/**
  * @brief  Enable the specified RAMECC global interrupts.
  * @rmtoll
  *  IER           GECCSEIE           LL_RAMECC_EnableGlobalIT \n
  *  IER           GECCDEIE           LL_RAMECC_EnableGlobalIT \n
  *  IER           GECCDEBWIE         LL_RAMECC_EnableGlobalIT
  * @param  p_ramecc RAMECC Instance.
  * @param  interrupt Interrupt sources to enable.
  *         This parameter can be a combination of the following values:
  *           @arg @ref  LL_RAMECC_IT_GLOBAL_SE    : Single Error Interrupt Mask.
  *           @arg @ref  LL_RAMECC_IT_GLOBAL_DE    : Double Error Interrupt Mask.
  *           @arg @ref  LL_RAMECC_IT_GLOBAL_DEBW  : Double Error on Byte Write Interrupt Mask.
  *           @arg @ref  LL_RAMECC_IT_GLOBAL_ALL   : All Interrupt Mask.
  */
__STATIC_INLINE void LL_RAMECC_EnableGlobalIT(RAMECC_TypeDef *p_ramecc, uint32_t interrupt)
{
  STM32_SET_BIT(p_ramecc->IER, interrupt);
}

/**
  * @brief  Disable the specified RAMECC global interrupts.
  * @rmtoll
  *  IER           GECCSEIE           LL_RAMECC_EnableGlobalIT \n
  *  IER           GECCDEIE           LL_RAMECC_EnableGlobalIT \n
  *  IER           GECCDEBWIE         LL_RAMECC_EnableGlobalIT
  * @param  p_ramecc RAMECC Instance.
  * @param  interrupt Interrupt sources to enable.
  *         This parameter can be a combination of the following values:
  *           @arg @ref  LL_RAMECC_IT_GLOBAL_SE    : Single Error Interrupt Mask.
  *           @arg @ref  LL_RAMECC_IT_GLOBAL_DE    : Double Error Interrupt Mask.
  *           @arg @ref  LL_RAMECC_IT_GLOBAL_DEBW  : Double Error on Byte Write Interrupt Mask.
  *           @arg @ref  LL_RAMECC_IT_GLOBAL_ALL   : All Interrupt Mask.
  */
__STATIC_INLINE void LL_RAMECC_DisableGlobalIT(RAMECC_TypeDef *p_ramecc, uint32_t interrupt)
{
  STM32_CLEAR_BIT(p_ramecc->IER, interrupt);
}

/**
  * @brief  Check if the specified RAMECC global interrupt is enabled or disabled.
  * @rmtoll
  *  IER           GECCSEIE           LL_RAMECC_EnableGlobalIT \n
  *  IER           GECCDEIE           LL_RAMECC_EnableGlobalIT \n
  *  IER           GECCDEBWIE         LL_RAMECC_EnableGlobalIT
  * @param  p_ramecc RAMECC Instance.
  * @param  interrupt Interrupt sources to enable.
  *         This parameter can take one of the following values:
  *           @arg @ref  LL_RAMECC_IT_GLOBAL_SE    : Single Error Interrupt Mask.
  *           @arg @ref  LL_RAMECC_IT_GLOBAL_DE    : Double Error Interrupt Mask.
  *           @arg @ref  LL_RAMECC_IT_GLOBAL_DEBW  : Double Error on Byte Write Interrupt Mask.
  *           @arg @ref  LL_RAMECC_IT_GLOBAL_ALL   : All Interrupt Mask.
  * @return State of the specified global interrupt (1: enabled or 0: disabled).
  */
__STATIC_INLINE uint32_t LL_RAMECC_IsEnabledGlobalIT(const RAMECC_TypeDef *p_ramecc, uint32_t interrupt)
{
  return ((STM32_READ_BIT(p_ramecc->IER,  interrupt) == (interrupt)) ? 1UL : 0UL);
}

/**
  * @brief  Check if the ECC single error RAMECC global interrupt.
  * @rmtoll
  *  IER           GECCSEIE              LL_RAMECC_EnableGlobalIT_SE
  * @param  p_ramecc RAMECC Instance.
  */
__STATIC_INLINE void LL_RAMECC_EnableGlobalIT_SE(RAMECC_TypeDef *p_ramecc)
{
  STM32_SET_BIT(p_ramecc->IER,  LL_RAMECC_IT_GLOBAL_SE);
}


/**
  * @brief  Disable the ECC single error RAMECC global interrupt.
  * @rmtoll
  *  IER           GECCSEIE              LL_RAMECC_DisableGlobalIT_SE
  * @param  p_ramecc RAMECC Instance.
  */
__STATIC_INLINE void LL_RAMECC_DisableGlobalIT_SE(RAMECC_TypeDef *p_ramecc)
{
  STM32_CLEAR_BIT(p_ramecc->IER,  LL_RAMECC_IT_GLOBAL_SE);
}

/**
  * @brief  Check whether the ECC single error RAMECC global interrupt is enabled or not.
  * @rmtoll
  *  IER           GECCSEIE              LL_RAMECC_IsEnabledGlobalIT_SE
  * @param  p_ramecc RAMECC Instance.
  * @return State of ECC single error global interrupt (1: enabled or 0: disabled).
  */
__STATIC_INLINE uint32_t LL_RAMECC_IsEnabledGlobalIT_SE(const RAMECC_TypeDef *p_ramecc)
{
  return ((STM32_READ_BIT(p_ramecc->IER,  LL_RAMECC_IT_GLOBAL_SE) == (LL_RAMECC_IT_GLOBAL_SE)) ? 1UL : 0UL);
}

/**
  * @brief  Enable the ECC double error RAMECC global interrupt.
  * @rmtoll
  *  IER           GECCDEIE              LL_RAMECC_EnableGlobalIT_DE
  * @param  p_ramecc RAMECC Instance.
  */
__STATIC_INLINE void LL_RAMECC_EnableGlobalIT_DE(RAMECC_TypeDef *p_ramecc)
{
  STM32_SET_BIT(p_ramecc->IER,  LL_RAMECC_IT_GLOBAL_DE);
}

/**
  * @brief  Disable the ECC double error RAMECC global interrupt.
  * @rmtoll
  *  IER           GECCDEIE              LL_RAMECC_DisableGlobalIT_DE
  * @param  p_ramecc RAMECC Instance.
  */
__STATIC_INLINE void LL_RAMECC_DisableGlobalIT_DE(RAMECC_TypeDef *p_ramecc)
{
  STM32_CLEAR_BIT(p_ramecc->IER,  LL_RAMECC_IT_GLOBAL_DE);
}

/**
  * @brief  Check whether the ECC double error RAMECC global interrupt is enabled or not.
  * @rmtoll
  *  IER           GECCDEIE              LL_RAMECC_IsEnabledGlobalIT_DE
  * @param  p_ramecc RAMECC Instance.
  * @return State of ECC double error global interrupt (1: enabled or 0: disabled).
  */
__STATIC_INLINE uint32_t LL_RAMECC_IsEnabledGlobalIT_DE(const RAMECC_TypeDef *p_ramecc)
{
  return ((STM32_READ_BIT(p_ramecc->IER,  LL_RAMECC_IT_GLOBAL_DE) == (LL_RAMECC_IT_GLOBAL_DE)) ? 1UL : 0UL);
}

/**
  * @brief  Enable the ECC double error on byte write RAMECC global interrupt.
  * @rmtoll
  *  IER           GECCDEBWIE            LL_RAMECC_EnableGlobalIT_DEBW
  * @param  p_ramecc RAMECC Instance.
  */
__STATIC_INLINE void LL_RAMECC_EnableGlobalIT_DEBW(RAMECC_TypeDef *p_ramecc)
{
  STM32_SET_BIT(p_ramecc->IER,  LL_RAMECC_IT_GLOBAL_DEBW);
}

/**
  * @brief  Disable the ECC double error on byte write RAMECC global interrupt.
  * @rmtoll
  *  IER           GECCDEBWIE            LL_RAMECC_DisableGlobalIT_DEBW
  * @param  p_ramecc RAMECC Instance.
  */
__STATIC_INLINE void LL_RAMECC_DisableGlobalIT_DEBW(RAMECC_TypeDef *p_ramecc)
{
  STM32_CLEAR_BIT(p_ramecc->IER,  LL_RAMECC_IT_GLOBAL_DEBW);
}

/**
  * @brief  Check whether the ECC double error on byte write RAMECC global interrupt is enabled or not.
  * @rmtoll
  *  IER           GECCDEBWIE            LL_RAMECC_IsEnabledGlobalIT_DEBW
  * @param  p_ramecc RAMECC Instance.
  * @return State of ECC double error on byte write global interrupt (1: enabled or 0: disabled).
  */
__STATIC_INLINE uint32_t LL_RAMECC_IsEnabledGlobalIT_DEBW(const RAMECC_TypeDef *p_ramecc)
{
  return ((STM32_READ_BIT(p_ramecc->IER,  LL_RAMECC_IT_GLOBAL_DEBW) == (LL_RAMECC_IT_GLOBAL_DEBW)) ? 1UL : 0UL);
}

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
#endif

#endif /* STM32H7PXX_LL_RAMECC_H */
