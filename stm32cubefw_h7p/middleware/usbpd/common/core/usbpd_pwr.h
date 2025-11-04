/**
  ******************************************************************************
  * @file    usbpd_pwr.h
  * @brief   Header file for usbpd_pwr.c.
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

#ifndef USBPD_PWR_H
#define USBPD_PWR_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* Includes ------------------------------------------------------------------*/
#include "usbpd_pwr_hw_if.h"

#include "usbpd_core.h"
#include "usbpd_dpm_conf.h"

#include <string.h>

/** @addtogroup STM32_USBPD_LIBRARY
  * @{
  */

/** @addtogroup USBPD_PWR
  * @{
  */

/* Exported constants ---------------------------------------------------------*/
/** @defgroup USBPD_PWR_Exported_Constants USBPD_PWR Exported Constants
  * @{
  */

#define USBPD_PWR_VBUS_5V          (5000U)  /*!< 5V power definition  */
#define USBPD_PWR_VBUS_9V          (9000U)  /*!< 9V power definition  */
#define USBPD_PWR_VBUS_15V         (15000U) /*!< 15V power definition */
#define USBPD_PWR_VBUS_20V         (20000U) /*!< 20V power definition */

#define USBPD_PWR_NB_PDO_SNK_INDEX (0U)     /*!< Index in PDO count array for SNK PDOs */
#define USBPD_PWR_NB_PDO_SRC_INDEX (1U)     /*!< Index in PDO count array for SRc PDOs */
#define USBPD_PWR_PDO_SNK_SRC      (2U)     /*!< Number of element in PDO count array, one for Sink, one for Sounrce */


/**
  * @}
  */

/* Exported types ------------------------------------------------------------*/
/** @defgroup  USBPD_PWR_Exported_Types USBPD_PWR Exported Types
  * @{
  */

/**
  * @brief  Power PDO Structure definition.
  */
typedef struct
{
  uint32_t *pdo_list;  /*!< Pointer on Power Data Objects list, defining port capabilities */
  uint8_t  *pdo_count; /*!< Number of Power Data Objects defined in pdo_list
                            This parameter must be set at max to @ref USBPD_MAX_NB_PDO value */
} usbpd_pwr_port_pdo_t;

/**
  * @brief  Power PDO Storage Structure definition.
  */
typedef struct
{
  usbpd_pwr_port_pdo_t source_pdos; /*!< SRC Power Data Objects */
  usbpd_pwr_port_pdo_t sink_pdos;   /*!< SNK Power Data Objects */
} usbpd_pwr_port_pdo_storage_t;

/**
  * @brief  Power VBUS status.
  */
typedef enum
{
  USBPD_PWR_BELOW_VSAFE0V = 1U, /*!< VBUS is below Vsafe0V                           */
  USBPD_PWR_ABOVE_VSAFE0V = 2U, /*!< VBUS is above Vsafe0V                           */
  USBPD_PWR_BELOW_VSAFE5V = 3U, /*!< VBUS is below Vsafe5V                           */
  USBPD_PWR_ABOVE_VSAFE5V = 4U, /*!< VBUS is above Vsafe5V                           */
  USBPD_PWR_SNKDETACH     = 5U, /*!< VBUS is low enough to be considered as detached */
} usbpd_pwr_vbus_vsafe_status_t;

/**
  * @brief  Power roles.
  */
typedef enum
{
  USBPD_PWR_ROLE_SOURCE = USBPD_PWR_HW_IF_ROLE_SOURCE, /*!< Power role source */
  USBPD_PWR_ROLE_SINK   = USBPD_PWR_HW_IF_ROLE_SINK,   /*!< Power role sink   */
  USBPD_PWR_ROLE_DUAL   = USBPD_PWR_HW_IF_ROLE_DUAL,   /*!< Power role dual   */
} usbpd_pwr_role_t;

/**
  * @brief  Power modes of TypeC ports.
  */
typedef enum
{
  USBPD_PWR_MODE_OFF       = USBPD_PWR_HW_IF_MODE_OFF,       /*!< Port is off               */
  USBPD_PWR_MODE_HIBERNATE = USBPD_PWR_HW_IF_MODE_HIBERNATE, /*!< Port is in hibernate mode */
  USBPD_PWR_MODE_LOWPOWER  = USBPD_PWR_HW_IF_MODE_LOWPOWER,  /*!< Port is in low power mode */
  USBPD_PWR_MODE_NORMAL    = USBPD_PWR_HW_IF_MODE_NORMAL,    /*!< Port is in normal mode    */
} usbpd_pwr_mode_t;

/**
  * @brief  Check if the port number is valid.
  * @param  port_num Port number.
  * @retval boolean comparison result.
  */
#define USBPD_PWR_ISPORTVALID(port_num) ((port_num) < ((uint8_t)USBPD_PORT_COUNT))

/**
  * @}
  */

/* Exported variables ---------------------------------------------------------*/
/** @defgroup USBPD_PWR_Exported_Variables USBPD_PWR Exported Variables
  * @{
  */

extern usbpd_pwr_port_pdo_storage_t USBPD_PWR_Port_PDO_Storage[USBPD_PORT_COUNT]; /*!< PDO Storage array declaration */

/**
  * @}
  */

/* Exported functions ---------------------------------------------------------*/
/** @defgroup USBPD_PWR_Exported_Functions USBPD_PWR Exported Functions
  * @{
  */

/**
  * @brief  Initialize structures and variables related to power board profiles.
  *         used by Sink and Source, for all available ports.
  * @retval USBPD status.
  */
usbpd_status_t   USBPD_PWR_Init(uint8_t port_num);
void             USBPD_PWR_DeInit(uint8_t port_num);

usbpd_status_t   USBPD_PWR_VBUSInit(uint8_t port_num);
void             USBPD_PWR_VBUSDeInit(uint8_t port_num);

usbpd_status_t   USBPD_PWR_EnableVBUS(uint8_t port_num);
usbpd_status_t   USBPD_PWR_DisableVBUS(uint8_t port_num);
usbpd_functional_status_t USBPD_PWR_IsEnabledVBUS(uint8_t port_num);

usbpd_status_t   USBPD_PWR_VConnInit(uint8_t port_num);
void             USBPD_PWR_VConnDeInit(uint8_t port_num);

usbpd_status_t   USBPD_PWR_EnableVConn(uint8_t port_num, usbpd_cc_line_t cc_pin);
usbpd_status_t   USBPD_PWR_DisableVConn(uint8_t port_num, usbpd_cc_line_t cc_pin);
usbpd_functional_status_t USBPD_PWR_IsEnabledVConn(uint8_t port_num, usbpd_cc_line_t cc_pin);

usbpd_status_t   USBPD_PWR_SetRole(uint8_t port_num, usbpd_pwr_role_t pwr_role);
usbpd_status_t   USBPD_PWR_SetPowerMode(uint8_t port_num, usbpd_pwr_mode_t pwr_mode);

usbpd_status_t   USBPD_PWR_SetProfile(uint8_t port_num);

usbpd_status_t   USBPD_PWR_IsSupplyReady(uint8_t port_num, usbpd_vsafe_status_t vsafe_status);

void             USBPD_PWR_GetPortPDOs(uint8_t port_num, usbpd_core_datainfo_type_t data_id, uint8_t *ptr,
                                       uint32_t *size);

usbpd_status_t   USBPD_PWR_SearchRequestedPDO(uint8_t port_num, uint32_t rdo_pos, uint32_t *pPdo);

uint8_t          USBPD_PWR_GetVBUSStatus(uint8_t port_num, usbpd_pwr_vbus_vsafe_status_t pwr_vbus_status);

void             USBPD_PWR_UpdateVbusThreshold(uint8_t port_num);

void             USBPD_PWR_ResetVbusThreshold(uint8_t port_num);


usbpd_status_t   USBPD_PWR_RegisterVBUSDetectCallback(uint8_t port_num, usbpd_pwr_vbusdetect_cb_t pCallback);

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

#endif /* USBPD_PWR_H */
