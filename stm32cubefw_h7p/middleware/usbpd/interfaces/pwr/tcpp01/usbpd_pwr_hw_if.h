/**
  ******************************************************************************
  * @file    usbpd_pwr_hw_if.h
  * @brief   Header file for usbpd_pwr_hw_if.c.
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

#ifndef USBPD_PWR_HW_IF_H
#define USBPD_PWR_HW_IF_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* Includes ------------------------------------------------------------------*/
#include "usbpd_core.h"
#include "stm32_hal.h"
#include "mx_hal_def.h"
#include "usbpd_trace.h"

#include "tcpp01.h"

/** @addtogroup STM32_USBPD_LIBRARY
  * @{
  */

/** @addtogroup USBPD_PWR_HW_IF
  * @{
  */

/* Exported constants ---------------------------------------------------------*/
/** @defgroup USBPD_PWR_HW_IF_Exported_Constants USBPD_PWR_HW_IF Exported Constants
  * @{
  */

#define USBPD_PWR_HW_IF_HIGH_VBUS_THRESHOLD     (4750U)  /*!< VBUS threshold for Vsafe5V */
#define USBPD_PWR_HW_IF_LOW_VBUS_THRESHOLD      (800U)   /*!< VBUS threshold for Vsafe0V */

#define USBPD_PWR_HW_IF_VBUS_THRESHOLD_5V       (3900U)  /*!< VBUS threshold for 5V      */
#define USBPD_PWR_HW_IF_VBUS_THRESHOLD_9V       (7000U)  /*!< VBUS threshold for 9V      */
#define USBPD_PWR_HW_IF_VBUS_THRESHOLD_15V      (12500U) /*!< VBUS threshold for 15V     */
#define USBPD_PWR_HW_IF_VBUS_THRESHOLD_20V      (17000U) /*!< VBUS threshold for 20V     */
#define USBPD_PWR_HW_IF_VBUS_THRESHOLD_APDO     (2150U)  /*!< VBUS threshold for APDO    */

#define USBPD_PWR_HW_IF_VBUS_5V                 (5000U)  /*!< VBUS value for 5V. Do not modify */

/**
  * @}
  */

/* Exported types ------------------------------------------------------------*/
/** @defgroup  USBPD_PWR_HW_IF_Exported_Types USBPD_PWR_HW_IF Exported Types
  * @{
  */

/**
  * @brief  Power roles.
  */
typedef enum
{
  USBPD_PWR_HW_IF_ROLE_SOURCE = 0U, /*!< Power role source */
  USBPD_PWR_HW_IF_ROLE_SINK   = 1U, /*!< Power role sink   */
  USBPD_PWR_HW_IF_ROLE_DUAL   = 2U, /*!< Power role dual   */
} usbpd_pwr_hw_if_role_t;

/**
  * @brief  Power modes of TypeC ports.
  */
typedef enum
{
  USBPD_PWR_HW_IF_MODE_OFF       = 0U, /*!< Port is off               */
  USBPD_PWR_HW_IF_MODE_HIBERNATE = 1U, /*!< Port is in hibernate mode */
  USBPD_PWR_HW_IF_MODE_LOWPOWER  = 2U, /*!< Port is in low power mode */
  USBPD_PWR_HW_IF_MODE_NORMAL    = 3U, /*!< Port is in normal mode    */
} usbpd_pwr_hw_if_mode_t;

/**
  * @}
  */

/* Exported functions ---------------------------------------------------------*/
/** @defgroup USBPD_PWR_HW_IF_Exported_Functions USBPD_PWR_HW_IF Exported Functions
  * @{
  */

usbpd_status_t            USBPD_PWR_HW_IF_Init(uint8_t port_num);
void                      USBPD_PWR_HW_IF_DeInit(uint8_t port_num);

usbpd_status_t            USBPD_PWR_HW_IF_VBUSInit(uint8_t port_num);
void                      USBPD_PWR_HW_IF_VBUSDeInit(uint8_t port_num);

usbpd_status_t            USBPD_PWR_HW_IF_EnableVBUS(uint8_t port_num);
usbpd_status_t            USBPD_PWR_HW_IF_DisableVBUS(uint8_t port_num);
usbpd_functional_status_t USBPD_PWR_HW_IF_IsEnabledVBUS(uint8_t port_num);

usbpd_status_t            USBPD_PWR_HW_IF_VConnInit(uint8_t port_num);
void                      USBPD_PWR_HW_IF_VConnDeInit(uint8_t port_num);

usbpd_status_t            USBPD_PWR_HW_IF_EnableVConn(uint8_t port_num, usbpd_cc_line_t cc_pin);
usbpd_status_t            USBPD_PWR_HW_IF_DisableVConn(uint8_t port_num, usbpd_cc_line_t cc_pin);
usbpd_functional_status_t USBPD_PWR_HW_IF_IsEnabledVConn(uint8_t port_num, usbpd_cc_line_t cc_pin);

uint32_t                  USBPD_PWR_HW_IF_VBUSGetVoltage(uint8_t port_num);
int16_t                   USBPD_PWR_HW_IF_VBUSGetCurrent(uint8_t port_num);

usbpd_status_t            USBPD_PWR_HW_IF_VBUSSetVoltage_Fixed(uint8_t port_num,
                                                               uint32_t vbus_target_mv,
                                                               uint32_t operating_current_ma,
                                                               uint32_t max_operating_current_ma);

usbpd_status_t            USBPD_PWR_HW_IF_VBUSSetVoltage_Variable(uint8_t port_num,
                                                                  uint32_t vbus_target_max_mv,
                                                                  uint32_t vbus_target_min_mv,
                                                                  uint32_t operating_current_ma,
                                                                  uint32_t max_operating_current_ma);

usbpd_status_t            USBPD_PWR_HW_IF_VBUSSetVoltage_Battery(uint8_t port_num,
                                                                 uint32_t vbus_target_min_mv,
                                                                 uint32_t vbus_target_max_mv,
                                                                 uint32_t operating_power_mw,
                                                                 uint32_t max_operating_power_mw);

usbpd_status_t            USBPD_PWR_HW_IF_VBUSSetVoltage_APDO(uint8_t port_num,
                                                              uint32_t vbus_target_mv,
                                                              uint32_t operating_current_ma,
                                                              int32_t  delta_mv);

usbpd_status_t            USBPD_PWR_HW_IF_SetRole(uint8_t port_num, usbpd_pwr_hw_if_role_t pwr_role);
usbpd_status_t            USBPD_PWR_HW_IF_SetPowerMode(uint8_t port_num, usbpd_pwr_hw_if_mode_t pwr_mode);

usbpd_status_t            USBPD_PWR_HW_IF_RegisterVBUSDetectCallback(uint8_t port_num,
                                                                     const usbpd_pwr_vbusdetect_cb_t pCallback);

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

#endif /* USBPD_PWR_HW_IF_H */
