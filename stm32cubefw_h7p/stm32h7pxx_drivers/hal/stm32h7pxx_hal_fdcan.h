/**
  **********************************************************************************************************************
  * @file    stm32h7pxx_hal_fdcan.h
  * @author  GPM Application Team
  * @brief   Header file of FDCAN HAL module.
  **********************************************************************************************************************
  * @attention
  *
  * Copyright (c) 2024-2025 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  **********************************************************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef STM32H7PXX_HAL_FDCAN_H
#define STM32H7PXX_HAL_FDCAN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ----------------------------------------------------------------------------------------------------------*/
#include "stm32h7pxx_hal_def.h"

#if defined(FDCAN1)

/** @addtogroup STM32H7PXX_HAL_Driver
  * @{
  */

/** @defgroup FDCAN FDCAN
  * @{
  */

/* Exported constants ------------------------------------------------------------------------------------------------*/
/** @defgroup FDCAN_Exported_Constants HAL FDCAN Constants
  * @{
  */

#if defined(USE_HAL_FDCAN_GET_LAST_ERRORS) && (USE_HAL_FDCAN_GET_LAST_ERRORS == 1)

/** @defgroup FDCAN_Error_Codes FDCAN Error Codes
  * @{
  */

#define HAL_FDCAN_ERROR_NONE                 (0UL)        /*!< No error                                               */
#define HAL_FDCAN_ERROR_LOG_OVERFLOW         (1UL << 0U)  /*!< Overflow of CAN Error Logging Counter                  */
#define HAL_FDCAN_ERROR_RAM_WDG              (1UL << 1U)  /*!< Message RAM Watchdog event occurred                    */
#define HAL_FDCAN_ERROR_PROTOCOL_ARBT        (1UL << 2U)  /*!< Protocol Error in Arbitration Phase (Nominal Bit Time) */
#define HAL_FDCAN_ERROR_PROTOCOL_DATA        (1UL << 3U)  /*!< Protocol Error in Data Phase (Data Bit Time)           */
#define HAL_FDCAN_ERROR_RESERVED_AREA        (1UL << 4U)  /*!< Access to Reserved Address                             */
#define HAL_FDCAN_ERROR_TIMEOUT_OCCURRED     (1UL << 5U)  /*!< Timeout Occurred                                       */
#define HAL_FDCAN_ERROR_RAM_ACCESS_FAILURE   (1UL << 6U)  /*!< Message RAM access failure occurred                    */
#define HAL_FDCAN_ERROR_BUS_FAULT_OFF        (1UL << 7U)  /*!< Bus_Off status changed                                 */
#define HAL_FDCAN_ERROR_BUS_FAULT_PASSIVE    (1UL << 8U)  /*!< Error_Passive status changed                           */
#define HAL_FDCAN_ERROR_BUS_FAULT_WARNING    (1UL << 9U)  /*!< Error_Warning status changed                           */

/**
  * @}
  */
#endif /* USE_HAL_FDCAN_GET_LAST_ERRORS */

/** @defgroup FDCAN_Interrupt_Groups FDCAN Interrupt Groups
  * @{
  */

/**
  * @brief Rx FIFO0 group.
  *        This group contains the following interrupts:
  *        - Rx FIFO0 new message
  *        - Rx FIFO0 full
  *        - Rx FIFO0 message lost
  */
#define HAL_FDCAN_IT_GROUP_RX_FIFO0       (FDCAN_ILS_RXFIFO0)

/**
  * @brief Rx FIFO1 group.
  *        This group contains the following interrupts:
  *        - Rx FIFO1 new message
  *        - Rx FIFO1 full
  *        - Rx FIFO1 message lost
  */
#define HAL_FDCAN_IT_GROUP_RX_FIFO1       (FDCAN_ILS_RXFIFO1)

/**
  * @brief Status message group.
  *        This group contains the following interrupts:
  *        - Rx high priority message
  *        - Tx complete
  *        - Tx abort complete
  */
#define HAL_FDCAN_IT_GROUP_STATUS_MSG     (FDCAN_ILS_SMSG)

/**
  * @brief Tx FIFO error group.
  *        This group contains the following interrupts:
  *        - Tx FIFO empty
  *        - Tx event FIFO new data
  *        - Tx event FIFO full
  *        - Tx event FIFO element lost
  */
#define HAL_FDCAN_IT_GROUP_TX_FIFO_ERROR  (FDCAN_ILS_TFERR)

/**
  * @brief Miscellaneous group.
  *        This group contains the following interrupts:
  *        - Timestamp wraparound
  *        - Message RAM access failure
  *        - Timeout occurred
  */
#define HAL_FDCAN_IT_GROUP_MISC           (FDCAN_ILS_MISC)

/**
  * @brief Bit and line error group.
  *        This group contains the following interrupts:
  *        - Error logging overflow
  *        - Error passive
  */
#define HAL_FDCAN_IT_GROUP_BIT_LINE_ERROR (FDCAN_ILS_BERR)

/**
  * @brief Protocol error group.
  *        This group contains the following interrupts:
  *        - Error warning
  *        - Bus off
  *        - Message RAM watchdog
  *        - Protocol error in arbitration phase
  *        - Protocol error in data phase
  *        - Reserved address access error
  */
#define HAL_FDCAN_IT_GROUP_PROTOCOL_ERROR (FDCAN_ILS_PERR)

/**
  * @}
  */

/** @defgroup FDCAN_Interrupt_Sources FDCAN Interrupt Sources
  * @{
  */

/* FDCAN interrupt group Rx FIFO0 */
#define HAL_FDCAN_IT_RX_FIFO0_NEW_MSG        FDCAN_IE_RF0NE /*!< Rx FIFO0 new message interrupt                      */
#define HAL_FDCAN_IT_RX_FIFO0_FULL           FDCAN_IE_RF0FE /*!< Rx FIFO0 full interrupt                             */
#define HAL_FDCAN_IT_RX_FIFO0_MSG_LOST       FDCAN_IE_RF0LE /*!< Rx FIFO0 message lost interrupt                     */

/* FDCAN interrupt group Rx FIFO1 */
#define HAL_FDCAN_IT_RX_FIFO1_NEW_MSG        FDCAN_IE_RF1NE /*!< Rx FIFO1 new message interrupt                      */
#define HAL_FDCAN_IT_RX_FIFO1_FULL           FDCAN_IE_RF1FE /*!< Rx FIFO1 full interrupt                             */
#define HAL_FDCAN_IT_RX_FIFO1_MSG_LOST       FDCAN_IE_RF1LE /*!< Rx FIFO1 message lost interrupt                     */

/* FDCAN interrupt group status message */
#define HAL_FDCAN_IT_RX_HIGH_PRIORITY_MSG    FDCAN_IE_HPME  /*!< High priority message received                      */
#define HAL_FDCAN_IT_TX_COMPLETE             FDCAN_IE_TCE   /*!< Transmission Completed                              */
#define HAL_FDCAN_IT_TX_ABORT_COMPLETE       FDCAN_IE_TCFE  /*!< Transmission Cancellation Finished                  */

/* FDCAN interrupt group Tx FIFO error */
#define HAL_FDCAN_IT_TX_FIFO_EMPTY           FDCAN_IE_TFEE  /*!< Tx FIFO Empty                                       */
#define HAL_FDCAN_IT_TX_EVT_FIFO_NEW_DATA    FDCAN_IE_TEFNE /*!< Tx Handler wrote Tx Event FIFO element              */
#define HAL_FDCAN_IT_TX_EVT_FIFO_FULL        FDCAN_IE_TEFFE /*!< Tx Event FIFO full                                  */
#define HAL_FDCAN_IT_TX_EVT_FIFO_ELT_LOST    FDCAN_IE_TEFLE /*!< Tx Event FIFO element lost                          */

/* FDCAN interrupt group misc. */
#define HAL_FDCAN_IT_TIMESTAMP_WRAPAROUND    FDCAN_IE_TSWE  /*!< Timestamp counter wrapped around                    */
#define HAL_FDCAN_IT_RAM_ACCESS_FAILURE      FDCAN_IE_MRAFE /*!< Message RAM access failure occurred                 */
#define HAL_FDCAN_IT_TIMEOUT_OCCURRED        FDCAN_IE_TOOE  /*!< Timeout reached                                     */

/* FDCAN interrupt group bit and line error */
#define HAL_FDCAN_IT_ERROR_LOGGING_OVERFLOW  FDCAN_IE_ELOE  /*!< Overflow of FDCAN Error Logging Counter occurred    */
#define HAL_FDCAN_IT_ERROR_PASSIVE           FDCAN_IE_EPE   /*!< Error_Passive status changed                        */

/* FDCAN interrupt group protocol error */
#define HAL_FDCAN_IT_ERROR_WARNING           FDCAN_IE_EWE   /*!< Error_Warning status changed                        */
#define HAL_FDCAN_IT_BUS_OFF                 FDCAN_IE_BOE   /*!< Bus_Off status changed                              */
#define HAL_FDCAN_IT_RAM_WATCHDOG            FDCAN_IE_WDIE  /*!< Message RAM Watchdog event due to missing READY     */
#define HAL_FDCAN_IT_ARB_PROTOCOL_ERROR      FDCAN_IE_PEAE  /*!< Protocol error in arbitration phase detected        */
#define HAL_FDCAN_IT_DATA_PROTOCOL_ERROR     FDCAN_IE_PEDE  /*!< Protocol error in data phase detected               */
#define HAL_FDCAN_IT_RESERVED_ADDRESS_ACCESS FDCAN_IE_ARAE  /*!< Access to reserved address occurred                 */

/**
  * @}
  */

/** @defgroup FDCAN_Interrupt_Flags FDCAN Interrupt Flags
  * @brief FDCAN interrupt register (FDCAN_IR): The flags are set when one of the listed conditions is detected.
  * @{
  */

/* FDCAN Interrupt flags for Rx FIFO0 */
#define HAL_FDCAN_FLAG_RX_FIFO0_MSG_LOST       FDCAN_IR_RF0L /*!< Rx FIFO 0 message lost                          */
#define HAL_FDCAN_FLAG_RX_FIFO0_FULL           FDCAN_IR_RF0F /*!< Rx FIFO 0 full                                  */
#define HAL_FDCAN_FLAG_RX_FIFO0_NEW_MSG        FDCAN_IR_RF0N /*!< New message written to Rx FIFO 0                */

/* FDCAN Interrupt flags for Rx FIFO1 */
#define HAL_FDCAN_FLAG_TX_EVT_FIFO_ELT_LOST    FDCAN_IR_TEFL /*!< Tx Event FIFO element lost                      */
#define HAL_FDCAN_FLAG_TX_EVT_FIFO_FULL        FDCAN_IR_TEFF /*!< Tx Event FIFO full                              */
#define HAL_FDCAN_FLAG_TX_EVT_FIFO_NEW_DATA    FDCAN_IR_TEFN /*!< Tx Handler wrote Tx Event FIFO element          */

/* FDCAN Interrupt flags for Tx FIFO error */
#define HAL_FDCAN_FLAG_RX_FIFO1_MSG_LOST       FDCAN_IR_RF1L /*!< Rx FIFO 1 message lost                          */
#define HAL_FDCAN_FLAG_RX_FIFO1_FULL           FDCAN_IR_RF1F /*!< Rx FIFO 1 full                                  */
#define HAL_FDCAN_FLAG_RX_FIFO1_NEW_MSG        FDCAN_IR_RF1N /*!< New message written to Rx FIFO 1                */

/* FDCAN Interrupt flags for status message */
#define HAL_FDCAN_FLAG_RX_HIGH_PRIORITY_MSG    FDCAN_IR_HPM  /*!< High priority message received                  */
#define HAL_FDCAN_FLAG_TX_COMPLETE             FDCAN_IR_TC   /*!< Transmission Completed                          */
#define HAL_FDCAN_FLAG_TX_ABORT_COMPLETE       FDCAN_IR_TCF  /*!< Transmission Cancellation Finished              */

/**
  * @}
  */

/** @defgroup FDCAN_IT_Tx_Complete_Buffers_select FDCAN Interrupt Tx Complete Buffers select
  * @{
  */

#define HAL_FDCAN_IT_TX_CPLT_BUFFER_0   (1UL << 0U)      /*!< Tx complete interrupt on Tx buffer 0    */
#define HAL_FDCAN_IT_TX_CPLT_BUFFER_1   (1UL << 1U)      /*!< Tx complete interrupt on Tx buffer 1    */
#define HAL_FDCAN_IT_TX_CPLT_BUFFER_2   (1UL << 2U)      /*!< Tx complete interrupt on Tx buffer 2    */
#define HAL_FDCAN_IT_TX_CPLT_BUFFER_ALL FDCAN_TXBTIE_TIE /*!< Tx complete interrupt on all Tx buffers */

/**
  * @}
  */

/**  @defgroup FDCAN_IT_Tx_Abort_Buffers_select FDCAN Interrupt Tx Abort Buffer select
  * @{
  */

#define HAL_FDCAN_IT_TX_ABORT_BUFFER_0   (1UL << 0U)       /*!< Tx abort interrupt on Tx buffer 0    */
#define HAL_FDCAN_IT_TX_ABORT_BUFFER_1   (1UL << 1U)       /*!< Tx abort interrupt on Tx buffer 1    */
#define HAL_FDCAN_IT_TX_ABORT_BUFFER_2   (1UL << 2U)       /*!< Tx abort interrupt on Tx buffer 2    */
#define HAL_FDCAN_IT_TX_ABORT_BUFFER_ALL FDCAN_TXBCIE_CFIE /*!< Tx abort interrupt on all Tx buffers */

/**
  * @}
  */

/** @defgroup FDCAN_Tx_Buffer_location HAL FDCAN Tx Location
  * @{
  */

#define HAL_FDCAN_TX_BUFFER_NONE 0U             /*!< No selected Tx Buffer */
#define HAL_FDCAN_TX_BUFFER0     (1UL << 0U)    /*!< Tx Buffer 0           */
#define HAL_FDCAN_TX_BUFFER1     (1UL << 1U)    /*!< Tx Buffer 1           */
#define HAL_FDCAN_TX_BUFFER2     (1UL << 2U)    /*!< Tx Buffer 2           */
#define HAL_FDCAN_TX_BUFFER_ALL  FDCAN_TXBAR_AR /*!< All Tx Buffers        */

/**
  * @}
  */

/** @defgroup FDCAN_Interrupt_Lines FDCAN Interrupt Lines
  * @brief    FDCAN Interrupt lines
  * @{
  */

#define HAL_FDCAN_IT_LINE_0 (1UL << 0U) /*!< Interrupt line 0 */
#define HAL_FDCAN_IT_LINE_1 (1UL << 1U) /*!< Interrupt line 1 */

/**
  * @}
  */

/**
  * @brief  HAL FDCAN Frame Type
  */
typedef enum
{
  HAL_FDCAN_FRAME_DATA   = 0U,  /*!< Data frame type   */
  HAL_FDCAN_FRAME_REMOTE = 1U   /*!< Remote frame type */
} hal_fdcan_frame_type_t;

/**
  * @brief  HAL FDCAN ID type
  */
typedef enum
{
  HAL_FDCAN_ID_STANDARD = 0U, /*!< Standard ID type */
  HAL_FDCAN_ID_EXTENDED = 1U  /*!< Extended ID type */
} hal_fdcan_id_type_t;

/**
  * @brief  HAL FDCAN error state indicator
  */
typedef enum
{
  HAL_FDCAN_ERROR_STATE_IND_ACTIVE  = 0U, /*!< Active error state indicator  */
  HAL_FDCAN_ERROR_STATE_IND_PASSIVE = 1U  /*!< Passive error state indicator */
} hal_fdcan_error_state_t;

/**
  * @brief  HAL FDCAN bit rate switching
  */
typedef enum
{
  HAL_FDCAN_BIT_RATE_SWITCH_OFF = 0U, /*!< Bit rate switching OFF */
  HAL_FDCAN_BIT_RATE_SWITCH_ON  = 1U  /*!< Bit rate switching ON  */
} hal_fdcan_bit_rate_switch_t;

/**
  * @brief  HAL FDCAN header frame format
  */
typedef enum
{
  HAL_FDCAN_HEADER_FRAME_FORMAT_CAN    = 0U, /*!< Standard frame format                        */
  HAL_FDCAN_HEADER_FRAME_FORMAT_FD_CAN = 1U  /*!< CAN-FD frame format (new DLC-coding and CRC) */
} hal_fdcan_header_frame_format_t;

/**
  * @brief  HAL FDCAN event FIFO
  */
typedef enum
{
  HAL_FDCAN_TX_EVENTS_FIFO_NO    = 0U, /*!< Do not store Tx event in FIFO */
  HAL_FDCAN_TX_EVENTS_FIFO_STORE = 1U  /*!< Store Tx event in FIFO        */
} hal_fdcan_tx_event_fifo_t;

/**
  * @brief  HAL FDCAN Tx event type
  */
typedef enum
{
  HAL_FDCAN_TX_EVENT                   = 1U, /*!< A successful frame transmission                                     */
  HAL_FDCAN_TX_EVENT_IN_SPITE_OF_ABORT = 2U  /*!< Transmission in spite of cancellation. Both Corresponding Tx Buffer
                                                  Transmission occurred bit @ref FDCAN_IT_Tx_Complete_Buffers_select
                                                  and Cancellation finished bit @ref FDCAN_IT_Tx_Abort_Buffers_select
                                                  are set.
                                                  This event Type is set in case of:
                                                  - A successful frame transmission.
                                                  - A Disabled auto-retransmission (DAR), that means:
                                                  @ref hal_fdcan_config_t.auto_retransmission equals to
                                                  @ref HAL_FDCAN_AUTO_RETRANSMISSION_DISABLED.
                                                  - Storage of Tx events is enabled, that means:
                                                  @ref hal_fdcan_tx_header_t.event_fifo_control equals to
                                                  @ref HAL_FDCAN_TX_EVENTS_FIFO_STORE.                                */
} hal_fdcan_tx_event_type_t;

/**
  * @brief  HAL FDCAN Data Length Code
  *         The definition is the following one:
  *          - For Classic CAN:
  *            - 0 to 8: received frame has 0 to 8 data bytes
  *            - 9 to 15: received frame has 8 data bytes (max)
  *          - For CAN-FD:
  *            - 0 to 8: received frame has 0 to 8 data bytes
  *            - 9 to 15:received frame has 12/16/20/24/32/48/64 data bytes
  */
typedef enum
{
  HAL_FDCAN_DATA_LGTH_CAN_FDCAN_0BYTE = 0x0U, /*!< 0 byte data length code   */
  HAL_FDCAN_DATA_LGTH_CAN_FDCAN_1BYTE = 0x1U, /*!< 1 bytes data length code  */
  HAL_FDCAN_DATA_LGTH_CAN_FDCAN_2BYTE = 0x2U, /*!< 2 bytes data length code  */
  HAL_FDCAN_DATA_LGTH_CAN_FDCAN_3BYTE = 0x3U, /*!< 3 bytes data length code  */
  HAL_FDCAN_DATA_LGTH_CAN_FDCAN_4BYTE = 0x4U, /*!< 4 bytes data length code  */
  HAL_FDCAN_DATA_LGTH_CAN_FDCAN_5BYTE = 0x5U, /*!< 5 bytes data length code  */
  HAL_FDCAN_DATA_LGTH_CAN_FDCAN_6BYTE = 0x6U, /*!< 6 bytes data length code  */
  HAL_FDCAN_DATA_LGTH_CAN_FDCAN_7BYTE = 0x7U, /*!< 7 bytes data length code  */
  HAL_FDCAN_DATA_LGTH_CAN_FDCAN_8BYTE = 0x8U, /*!< 8 bytes data length code  */
  HAL_FDCAN_DATA_LGTH_FDCAN_12BYTE    = 0x9U, /*!< 12 bytes data length code */
  HAL_FDCAN_DATA_LGTH_FDCAN_16BYTE    = 0xAU, /*!< 16 bytes data length code */
  HAL_FDCAN_DATA_LGTH_FDCAN_20BYTE    = 0xBU, /*!< 20 bytes data length code */
  HAL_FDCAN_DATA_LGTH_FDCAN_24BYTE    = 0xCU, /*!< 24 bytes data length code */
  HAL_FDCAN_DATA_LGTH_FDCAN_32BYTE    = 0xDU, /*!< 32 bytes data length code */
  HAL_FDCAN_DATA_LGTH_FDCAN_48BYTE    = 0xEU, /*!< 48 bytes data length code */
  HAL_FDCAN_DATA_LGTH_FDCAN_64BYTE    = 0xFU  /*!< 64 bytes data length code */
} hal_fdcan_data_length_code_t;

/**
  * @brief  HAL FDCAN received frame status
  */
typedef enum
{
  HAL_FDCAN_RX_FRAME_MATCHED     = 0U, /*!< Received frame matches filter index FIDx           */
  HAL_FDCAN_RX_FRAME_NOT_MATCHED = 1U  /*!< Received frame did not match any Rx filter element */
} hal_fdcan_rx_frame_status_t;

/**
  * @}
  */

/* Exported types ----------------------------------------------------------------------------------------------------*/
/** @defgroup FDCAN_Exported_Types HAL FDCAN Types
  * @{
  */

/**
  * @brief  FDCAN Frame Format
  */
typedef enum
{
  HAL_FDCAN_FRAME_CLASSIC_CAN = 0U,                                            /*!< Classic mode                      */
  HAL_FDCAN_FRAME_FD_NO_BRS   = FDCAN_CCCR_FDOE,                               /*!< FD mode without BitRate Switching */
  HAL_FDCAN_FRAME_FD_BRS      = (uint32_t)(FDCAN_CCCR_FDOE | FDCAN_CCCR_BRSE), /*!< FD mode with BitRate Switching    */
} hal_fdcan_frame_format_t;

/**
  * @brief  FDCAN Timestamp Selection
  */
typedef enum
{
  HAL_FDCAN_TIMESTAMP_SOURCE_ZERO        = 0U,                            /*!< Timestamp counter value is 0x0000 */
  HAL_FDCAN_TIMESTAMP_SOURCE_INTERNAL    = (0x1UL << FDCAN_TSCC_TSS_Pos), /*!< Timestamp counter value is incrementing
                                                                               according to TCP                  */
  HAL_FDCAN_TIMESTAMP_SOURCE_EXTERNAL    = (0x2UL << FDCAN_TSCC_TSS_Pos), /*!< External timestamp counter        */
} hal_fdcan_timestamp_source_t;

/**
  * @brief  FDCAN High Priority filter list definition
  */
typedef enum
{
  HAL_FDCAN_HIGH_PRIO_FILTER_STANDARD = 0U,              /*!< Standard filter list */
  HAL_FDCAN_HIGH_PRIO_FILTER_EXTENDED = FDCAN_HPMS_FLST, /*!< Extended filter list */
} hal_fdcan_high_prio_filter_list_t;

/**
  * @brief  FDCAN Error Status definition
  */
typedef enum
{
  HAL_FDCAN_ERROR_ACTIVE  = 0U, /*!< Error_Active state  */
  HAL_FDCAN_ERROR_PASSIVE = 1U, /*!< Error_Passive state */
} hal_fdcan_protocol_error_status_t;

/**
  * @brief  FDCAN Receive Error passive level definition
  */
typedef enum
{
  HAL_FDCAN_RX_ERROR_PASSIVE_BELOW_LEVEL = 0U,           /*!< The receive error counter is below
                                                              the error passive level of 128 */
  HAL_FDCAN_RX_ERROR_PASSIVE_REACH_LEVEL = FDCAN_ECR_RP, /*!< The receive error counter has reached
                                                              the error passive level of 128 */
} hal_fdcan_rx_error_passive_level_t;

/**
  * @brief  FDCAN State structures definition
  */
typedef enum
{
  HAL_FDCAN_STATE_RESET      = 0U,           /*!< Not yet Initialized                               */
  HAL_FDCAN_STATE_INIT       = (1UL << 31U), /*!< Initialized but not yet configured                */
  HAL_FDCAN_STATE_IDLE       = (1UL << 30U), /*!< Initialized and a global config applied           */
  HAL_FDCAN_STATE_ACTIVE     = (1UL << 29U), /*!< The peripheral is running                         */
  HAL_FDCAN_STATE_POWER_DOWN = (1UL << 28U), /*!< The peripheral is in power down mode (sleep mode) */
} hal_fdcan_state_t;

/**
  * @brief  HAL FDCAN mode enumeration definition
  */
typedef enum
{
  HAL_FDCAN_MODE_NORMAL               = 0U, /*!< Normal mode               */
  HAL_FDCAN_MODE_RESTRICTED_OPERATION = 1U, /*!< Restricted Operation mode */
  HAL_FDCAN_MODE_BUS_MONITORING       = 2U, /*!< Bus Monitoring mode       */
  HAL_FDCAN_MODE_INTERNAL_LOOPBACK    = 3U, /*!< Internal LoopBack mode    */
  HAL_FDCAN_MODE_EXTERNAL_LOOPBACK    = 4U, /*!< External LoopBack mode    */
  HAL_FDCAN_MODE_INVALID              = 5U, /*!< FDCAN Invalid mode        */
} hal_fdcan_mode_t;

/**
  * @brief  HAL FDCAN Auto Retransmission setting
  */
typedef enum
{
  HAL_FDCAN_AUTO_RETRANSMISSION_ENABLED  = 0U, /*!< Transmitter Auto retransmission enabled  */
  HAL_FDCAN_AUTO_RETRANSMISSION_DISABLED = 1U, /*!< Transmitter Auto retransmission disabled */
} hal_fdcan_auto_retransmission_status_t;

/**
  * @brief  HAL FDCAN Transmit Pause setting
  */
typedef enum
{
  HAL_FDCAN_TRANSMIT_PAUSE_DISABLED = 0U, /*!< Transmitter transmit pause disabled */
  HAL_FDCAN_TRANSMIT_PAUSE_ENABLED  = 1U, /*!< Transmitter transmit pause enabled  */
} hal_fdcan_transmit_pause_status_t;

/**
  * @brief  HAL FDCAN Protocol exception setting
  */
typedef enum
{
  HAL_FDCAN_PROTOCOL_EXCEPTION_ENABLED  = 0U, /*!< Transmitter protocol exception enabled  */
  HAL_FDCAN_PROTOCOL_EXCEPTION_DISABLED = 1U, /*!< Transmitter protocol exception disabled */
} hal_fdcan_protocol_exception_status_t;

/**
  * @brief  HAL FDCAN Transmitter delay Compensation setting
  */
typedef enum
{
  HAL_FDCAN_TX_DLY_COMPENSATION_DISABLED = 0U, /*!< Transmitter delay compensation disabled */
  HAL_FDCAN_TX_DLY_COMPENSATION_ENABLED  = 1U, /*!< Transmitter delay compensation enabled  */
} hal_fdcan_transmitter_delay_comp_status_t;

/**
  * @brief  HAL FDCAN ISO Mode setting
  */
typedef enum
{
  HAL_FDCAN_ISO_MODE_ENABLED  = 0U, /*!< Protocol configured for ISO mode         */
  HAL_FDCAN_ISO_MODE_DISABLED = 1U, /*!< Protocol configured for CAN FD v2.0 mode */
} hal_fdcan_iso_mode_status_t;

/**
  * @brief  HAL FDCAN Tx Buffer pending status
  */
typedef enum
{
  HAL_FDCAN_TX_BUFFER_NOT_PENDING = 0U, /*!< No buffer pending           */
  HAL_FDCAN_TX_BUFFER_PENDING     = 1U, /*!< At least one buffer pending */
} hal_fdcan_tx_buffer_status_t;

/**
  * @brief  HAL FDCAN Restricted Operation Mode setting
  */
typedef enum
{
  HAL_FDCAN_RESTRICTED_MODE_DISABLED = 0U, /*!< Restricted mode disabled */
  HAL_FDCAN_RESTRICTED_MODE_ENABLED  = 1U, /*!< Restricted mode enabled  */
} hal_fdcan_restricted_op_mode_status_t;

/**
  * @brief  HAL FDCAN Edge filtering setting
  */
typedef enum
{
  HAL_FDCAN_EDGE_FILTERING_DISABLED = 0U, /*!< Edge Filtering disabled */
  HAL_FDCAN_EDGE_FILTERING_ENABLED  = 1U, /*!< Edge Filtering enabled  */
} hal_fdcan_edge_filtering_status_t;

/**
  * @brief  HAL FDCAN FIFO operation mode
  */
typedef enum
{
  HAL_FDCAN_RX_FIFO_BLOCKING  = 0U, /*!< Rx FIFO blocking mode  */
  HAL_FDCAN_RX_FIFO_OVERWRITE = 1U, /*!< Rx FIFO overwrite mode */
} hal_fdcan_rx_fifo_operative_mode_t;

/**
  * @brief  HAL FDCAN Fifo/Queue status- free or full
  */
typedef enum
{
  HAL_FDCAN_FIFO_STATUS_FREE = 0U,               /*!< Tx FIFO queue not full */
  HAL_FDCAN_FIFO_STATUS_FULL = FDCAN_TXFQS_TFQF, /*!< Tx FIFO queue full     */
} hal_fdcan_fifo_status_t;

/**
  * @brief  FDCAN filter type, used for standard and extended filters.
  * The case @ref HAL_FDCAN_FILTER_RANGE_NO_EIDM must be processed differently depending on standard or extended filter.
  */
typedef enum
{
  HAL_FDCAN_FILTER_RANGE         = 0U, /*!< Range filter from FilterID1 to FilterID2                        */
  HAL_FDCAN_FILTER_DUAL          = 1U, /*!< Dual ID filter for FilterID1 or FilterID2                       */
  HAL_FDCAN_FILTER_CLASSIC       = 2U, /*!< Classic filter: FilterID1 = filter, FilterID2 = mask            */
  HAL_FDCAN_FILTER_RANGE_NO_EIDM = 3U, /*!< Range filter from FilterID1 to FilterID2, EIDM mask not applied */
} hal_fdcan_filter_type_t;

/**
  * @brief  HAL FDCAN Timeout Counter configuration
  */
typedef enum
{
  HAL_FDCAN_TIMEOUT_COUNTER_DISABLED = 0U, /*!< Timeout counter disabled */
  HAL_FDCAN_TIMEOUT_COUNTER_ENABLED  = 1U, /*!< Timeout counter enabled  */
} hal_fdcan_timeout_counter_status_t;

/**
  * @brief  HAL FDCAN Timestamp Counter configuration
  */
typedef enum
{
  HAL_FDCAN_TIMESTAMP_COUNTER_DISABLED = 0U, /*!< Timestamp counter disabled */
  HAL_FDCAN_TIMESTAMP_COUNTER_ENABLED  = 1U, /*!< Timestamp counter enabled  */
} hal_fdcan_timestamp_counter_status_t;

/**
  * @brief  FDCAN kernel clock divider
  */
typedef enum
{
  HAL_FDCAN_CLOCK_DIV1  = 0U,  /*!< Divide kernel clock by 1  */
  HAL_FDCAN_CLOCK_DIV2  = 1U,  /*!< Divide kernel clock by 2  */
  HAL_FDCAN_CLOCK_DIV4  = 2U,  /*!< Divide kernel clock by 4  */
  HAL_FDCAN_CLOCK_DIV6  = 3U,  /*!< Divide kernel clock by 6  */
  HAL_FDCAN_CLOCK_DIV8  = 4U,  /*!< Divide kernel clock by 8  */
  HAL_FDCAN_CLOCK_DIV10 = 5U,  /*!< Divide kernel clock by 10 */
  HAL_FDCAN_CLOCK_DIV12 = 6U,  /*!< Divide kernel clock by 12 */
  HAL_FDCAN_CLOCK_DIV14 = 7U,  /*!< Divide kernel clock by 14 */
  HAL_FDCAN_CLOCK_DIV16 = 8U,  /*!< Divide kernel clock by 16 */
  HAL_FDCAN_CLOCK_DIV18 = 9U,  /*!< Divide kernel clock by 18 */
  HAL_FDCAN_CLOCK_DIV20 = 10U, /*!< Divide kernel clock by 20 */
  HAL_FDCAN_CLOCK_DIV22 = 11U, /*!< Divide kernel clock by 22 */
  HAL_FDCAN_CLOCK_DIV24 = 12U, /*!< Divide kernel clock by 24 */
  HAL_FDCAN_CLOCK_DIV26 = 13U, /*!< Divide kernel clock by 26 */
  HAL_FDCAN_CLOCK_DIV28 = 14U, /*!< Divide kernel clock by 28 */
  HAL_FDCAN_CLOCK_DIV30 = 15U, /*!< Divide kernel clock by 30 */
} hal_fdcan_clock_divider_t;

/**
  * @brief  FDCAN Tx FIFO/Queue mode
  */
typedef enum
{
  HAL_FDCAN_TX_MODE_FIFO  = 0U,              /*!< Tx FIFO mode  */
  HAL_FDCAN_TX_MODE_QUEUE = FDCAN_TXBC_TFQM, /*!< Tx Queue mode */
} hal_fdcan_tx_mode_t;

/**
  * @brief  FDCAN Interrupts status
  */
typedef enum
{
  HAL_FDCAN_IT_DISABLED = 0U, /*!< Interrupt disabled */
  HAL_FDCAN_IT_ENABLED  = 1U, /*!< Interrupt enabled  */
} hal_fdcan_it_status_t;

/**
  * @brief  FDCAN Interrupt Lines status
  */
typedef enum
{
  HAL_FDCAN_IT_LINE_DISABLED = 0U, /*!< Interrupt line disabled */
  HAL_FDCAN_IT_LINE_ENABLED  = 1U, /*!< Interrupt line enabled  */
} hal_fdcan_it_lines_status_t;

/**
  * @brief  FDCAN Tx buffer transmission complete interrupt status
  */
typedef enum
{
  HAL_FDCAN_IT_TXBUFFER_COMPLETE_DISABLED = 0U, /*!< Tx buffer transmission complete interrupt disabled */
  HAL_FDCAN_IT_TXBUFFER_COMPLETE_ENABLED  = 1U, /*!< Tx buffer transmission complete interrupt enabled  */
} hal_fdcan_it_txbuffer_complete_status_t;

/**
  * @brief  FDCAN Tx buffer abort finished interrupt status
  */
typedef enum
{
  HAL_FDCAN_IT_TXBUFFER_ABORT_DISABLED  = 0U, /*!< Tx buffer abort finished interrupt disabled */
  HAL_FDCAN_IT_TXBUFFER_ABORT_ENABLED   = 1U, /*!< Tx buffer abort finished interrupt enabled  */
} hal_fdcan_it_txbuffer_abort_status_t;

/**
  * @brief  FDCAN High Priority Storage
  */
typedef enum
{
  HAL_FDCAN_HIGH_PRIO_STORAGE_NO_FIFO  = 0U,                            /*!< No FIFO selected         */
  HAL_FDCAN_HIGH_PRIO_STORAGE_MSG_LOST = (0x1UL << FDCAN_HPMS_MSI_Pos), /*!< FIFO message lost        */
  HAL_FDCAN_HIGH_PRIO_STORAGE_RXFIFO0  = (0x2UL << FDCAN_HPMS_MSI_Pos), /*!< Message stored in FIFO 0 */
  HAL_FDCAN_HIGH_PRIO_STORAGE_RXFIFO1  = FDCAN_HPMS_MSI,                /*!< Message stored in FIFO 1 */
} hal_fdcan_high_prio_storage_t;

/**
  * @brief  FDCAN Warning Status
  */
typedef enum
{
  HAL_FDCAN_WARNING_ERROR_COUNTERS_UNDER_LIMIT = 0U, /*!< Both error counters are below the Error_Warning of 96 */
  HAL_FDCAN_WARNING_ERROR_COUNTER_OVER_LIMIT   = 1U, /*!< At least one of the error counter has reached
                                                          the Error_Warning limit of 96                         */
} hal_fdcan_warning_status_t;

/**
  * @brief  FDCAN Bus_Off Status
  */
typedef enum
{
  HAL_FDCAN_BUS_OFF_DISABLED = 0U, /*!< The FDCAN is not in BUS_OFF state */
  HAL_FDCAN_BUS_OFF_ENABLED  = 1U, /*!< The FDCAN is in BUS_OFF state     */
} hal_fdcan_bus_off_status_t;

/**
  * @brief  FDCAN ESI flag of last received FDCAN message
  */
typedef enum
{
  HAL_FDCAN_ESI_FLAG_RESET = 0U, /*!< Last received FDCAN message did not have its ESI flag set */
  HAL_FDCAN_ESI_FLAG_SET   = 1U, /*!< Last received FDCAN message has its ESI flag set          */
} hal_fdcan_esi_flag_status_t;

/**
  * @brief  FDCAN BRS flag of last received FDCAN message
  */
typedef enum
{
  HAL_FDCAN_BRS_FLAG_RESET = 0U, /*!< Last received FDCAN message did not have its BRS flag set */
  HAL_FDCAN_BRS_FLAG_SET   = 1U, /*!< Last received FDCAN message has its BRS flag set          */
} hal_fdcan_brs_flag_status_t;

/**
  * @brief  FDCAN received FDCAN EDL (Extended Data length) message.
  */
typedef enum
{
  HAL_FDCAN_EDL_FLAG_RESET = 0U, /*!< No FDCAN Message has been received since this bit was reset by CPU */
  HAL_FDCAN_EDL_FLAG_SET   = 1U, /*!< Message in FDCAN format with EDL flag                              */
} hal_fdcan_edl_flag_status_t;

/**
  * @brief  FDCAN protocol exception event
  */
typedef enum
{
  HAL_FDCAN_PROTOCOL_NO_EVENT_OCCURRED = 0U, /*!< No protocol event occurred since last read access */
  HAL_FDCAN_PROTOCOL_EVENT_OCCURRED    = 1U, /*!< Protocol event occurred                           */
} hal_fdcan_protocol_exception_event_t;

/**
  * @brief  Filter Configuration
  */
typedef enum
{
  HAL_FDCAN_FILTER_DISABLE       = 0U, /*!< Disable filter element                                     */
  HAL_FDCAN_FILTER_TO_RXFIFO0    = 1U, /*!< Store in Rx FIFO 0 if filter matches                       */
  HAL_FDCAN_FILTER_TO_RXFIFO1    = 2U, /*!< Store in Rx FIFO 1 if filter matches                       */
  HAL_FDCAN_FILTER_REJECT        = 3U, /*!< Reject ID if filter matches                                */
  HAL_FDCAN_FILTER_HP            = 4U, /*!< Set high priority if filter matches                        */
  HAL_FDCAN_FILTER_TO_RXFIFO0_HP = 5U, /*!< Set high priority and store in FIFO 0 if filter matches    */
  HAL_FDCAN_FILTER_TO_RXFIFO1_HP = 6U, /*!< Set high priority and store in FIFO 1 if filter matches    */
} hal_fdcan_filter_config_t;

/**
  * @brief  HAL FDCAN Rx Location
  */
typedef enum
{
  HAL_FDCAN_RX_FIFO0    = 0U, /*!< Index for access to Rx FIFO 0     */
  HAL_FDCAN_RX_FIFO1    = 1U, /*!< Index for access to Rx FIFO 1     */
} hal_fdcan_rx_location_t;

/**
  * @brief  HAL FDCAN protocol error code
  */
typedef enum
{
  HAL_FDCAN_PROTOCOL_ERROR_NONE      = 0U, /*!< No error occurred         */
  HAL_FDCAN_PROTOCOL_ERROR_STUFF     = 1U, /*!< Stuff error               */
  HAL_FDCAN_PROTOCOL_ERROR_FORM      = 2U, /*!< Form error                */
  HAL_FDCAN_PROTOCOL_ERROR_ACK       = 3U, /*!< Acknowledge error         */
  HAL_FDCAN_PROTOCOL_ERROR_BIT1      = 4U, /*!< Bit 1 (recessive) error   */
  HAL_FDCAN_PROTOCOL_ERROR_BIT0      = 5U, /*!< Bit 0 (dominant) error    */
  HAL_FDCAN_PROTOCOL_ERROR_CRC       = 6U, /*!< CRC check sum error       */
  HAL_FDCAN_PROTOCOL_ERROR_NO_CHANGE = 7U, /*!< No change since last read */
} hal_fdcan_protocol_error_code_t;

/**
  * @brief  HAL FDCAN communication state
  */
typedef enum
{
  HAL_FDCAN_COM_STATE_SYNC = 0U,                           /*!< Node is synchronizing on CAN communication */
  HAL_FDCAN_COM_STATE_IDLE = (0x1UL << FDCAN_PSR_ACT_Pos), /*!< Node is neither receiver nor transmitter   */
  HAL_FDCAN_COM_STATE_RX   = (0x2UL << FDCAN_PSR_ACT_Pos), /*!< Node is operating as receiver              */
  HAL_FDCAN_COM_STATE_TX   = FDCAN_PSR_ACT,                /*!< Node is operating as transmitter           */
} hal_fdcan_communication_state_t;

/**
  * @brief  HAL FDCAN non-matching frames - Acceptance can be enabled via RXGFC[ANFS] and RXGFC[ANFE].
  */
typedef enum
{
  HAL_FDCAN_NON_MATCHING_ACCEPT_RX_FIFO0 = 0U, /*!< Accept non-matching frames in Rx FIFO 0 */
  HAL_FDCAN_NON_MATCHING_ACCEPT_RX_FIFO1 = 1U, /*!< Accept non-matching frames in Rx FIFO 1 */
  HAL_FDCAN_NON_MATCHING_REJECT          = 2U, /*!< Reject non-matching frames              */
} hal_fdcan_acceptance_non_matching_frame_t;

/**
  * @brief  HAL FDCAN reject remote frames
  */
typedef enum
{
  HAL_FDCAN_REMOTE_ACCEPT = 0U, /*!< Accept remote frames     */
  HAL_FDCAN_REMOTE_REJECT = 1U, /*!< Reject all remote frames */
} hal_fdcan_acceptance_remote_frame_t;

/**
  * @brief  HAL FDCAN timestamp prescaler
  */
typedef enum
{
  HAL_FDCAN_TIMESTAMP_PRESC_1  = 0U,                            /*!< Timestamp counter time unit is x1 CAN bit time  */
  HAL_FDCAN_TIMESTAMP_PRESC_2  = (0x1UL << FDCAN_TSCC_TCP_Pos), /*!< Timestamp counter time unit is x2 CAN bit time  */
  HAL_FDCAN_TIMESTAMP_PRESC_3  = (0x2UL << FDCAN_TSCC_TCP_Pos), /*!< Timestamp counter time unit is x3 CAN bit time  */
  HAL_FDCAN_TIMESTAMP_PRESC_4  = (0x3UL << FDCAN_TSCC_TCP_Pos), /*!< Timestamp counter time unit is x4 CAN bit time  */
  HAL_FDCAN_TIMESTAMP_PRESC_5  = (0x4UL << FDCAN_TSCC_TCP_Pos), /*!< Timestamp counter time unit is x5 CAN bit time  */
  HAL_FDCAN_TIMESTAMP_PRESC_6  = (0x5UL << FDCAN_TSCC_TCP_Pos), /*!< Timestamp counter time unit is x6 CAN bit time  */
  HAL_FDCAN_TIMESTAMP_PRESC_7  = (0x6UL << FDCAN_TSCC_TCP_Pos), /*!< Timestamp counter time unit is x7 CAN bit time  */
  HAL_FDCAN_TIMESTAMP_PRESC_8  = (0x7UL << FDCAN_TSCC_TCP_Pos), /*!< Timestamp counter time unit is x8 CAN bit time  */
  HAL_FDCAN_TIMESTAMP_PRESC_9  = (0x8UL << FDCAN_TSCC_TCP_Pos), /*!< Timestamp counter time unit is x9 CAN bit time  */
  HAL_FDCAN_TIMESTAMP_PRESC_10 = (0x9UL << FDCAN_TSCC_TCP_Pos), /*!< Timestamp counter time unit is x10 CAN bit time */
  HAL_FDCAN_TIMESTAMP_PRESC_11 = (0xAUL << FDCAN_TSCC_TCP_Pos), /*!< Timestamp counter time unit is x11 CAN bit time */
  HAL_FDCAN_TIMESTAMP_PRESC_12 = (0xBUL << FDCAN_TSCC_TCP_Pos), /*!< Timestamp counter time unit is x12 CAN bit time */
  HAL_FDCAN_TIMESTAMP_PRESC_13 = (0xCUL << FDCAN_TSCC_TCP_Pos), /*!< Timestamp counter time unit is x13 CAN bit time */
  HAL_FDCAN_TIMESTAMP_PRESC_14 = (0xDUL << FDCAN_TSCC_TCP_Pos), /*!< Timestamp counter time unit is x14 CAN bit time */
  HAL_FDCAN_TIMESTAMP_PRESC_15 = (0xEUL << FDCAN_TSCC_TCP_Pos), /*!< Timestamp counter time unit is x15 CAN bit time */
  HAL_FDCAN_TIMESTAMP_PRESC_16 = (0xFUL << FDCAN_TSCC_TCP_Pos), /*!< Timestamp counter time unit is x16 CAN bit time */
} hal_fdcan_timestamp_prescaler_t;

/**
  * @brief  HAL FDCAN Tx FIFO free level
  */
typedef enum
{
  HAL_FDCAN_TX_FIFO_FREE_LEVEL_0  = 0U,  /*!< Tx FIFO Full - no free FIFO slot        */
  HAL_FDCAN_TX_FIFO_FREE_LEVEL_1  = 1U,  /*!< 1 free FIFO slot available in Tx FIFO   */
  HAL_FDCAN_TX_FIFO_FREE_LEVEL_2  = 2U,  /*!< 2 free FIFO slots available in Tx FIFO  */
  HAL_FDCAN_TX_FIFO_FREE_LEVEL_3  = 3U,  /*!< 3 free FIFO slots available in Tx FIFO  */
} hal_fdcan_tx_fifo_free_level_t;

/**
  * @brief  HAL FDCAN timeout operation
  */
typedef enum
{
  HAL_FDCAN_TIMEOUT_CONTINUOUS    = 0U,                          /*!< Timeout continuous operation        */
  HAL_FDCAN_TIMEOUT_TX_EVENT_FIFO = (1UL << FDCAN_TOCC_TOS_Pos), /*!< Timeout controlled by Tx Event FIFO */
  HAL_FDCAN_TIMEOUT_RX_FIFO0      = (2UL << FDCAN_TOCC_TOS_Pos), /*!< Timeout controlled by Rx FIFO 0     */
  HAL_FDCAN_TIMEOUT_RX_FIFO1      = (3UL << FDCAN_TOCC_TOS_Pos), /*!< Timeout controlled by Rx FIFO 1     */
} hal_fdcan_timeout_operation_t;

/**
  * @brief  HAL FDCAN instance definition
  */
typedef enum
{
  HAL_FDCAN1 = FDCAN1_BASE, /*!< Peripheral instance FDCAN1 */
  HAL_FDCAN2 = FDCAN2_BASE, /*!< Peripheral instance FDCAN2 */
  HAL_FDCAN3 = FDCAN3_BASE, /*!< Peripheral instance FDCAN3 */
} hal_fdcan_t;

/**
  * @brief  FDCAN Rx element header definition
  */
typedef union
{
  uint64_t d64;                                                 /*!< 64-bit FDCAN Rx element header                   */
  struct
  {
    uint32_t                        identifier            : 29; /*!< Received identifier. A standard identifier
                                                                     is stored in bits [28:18]                        */
    hal_fdcan_frame_type_t          frame_type            : 1;  /*!< Frame type                                       */
    hal_fdcan_id_type_t             identifier_type       : 1;  /*!< Received identifier type                         */
    hal_fdcan_error_state_t         error_state_indicator : 1;  /*!< Error state indicator                            */
    uint32_t                        rx_timestamp          : 16; /*!< Rx timestamp. Timestamp counter value is
                                                                     captured at the start of frame reception.
                                                                     Resolution depends on the Timestamp Counter
                                                                     Prescaler                                        */
    hal_fdcan_data_length_code_t    data_length           : 4;  /*!< Received frame Data Length Code                  */
    hal_fdcan_bit_rate_switch_t     bit_rate_switch       : 1;  /*!< Bit rate switch indicator                        */
    hal_fdcan_header_frame_format_t frame_format          : 1;  /*!< Received frame format                            */
    uint32_t                                              : 2;  /*!< Rx Reserved                                      */
    uint32_t                        filter_index          : 7;  /*!< Filter index.
                                                                     - 0-127: index of matching Rx acceptance
                                                                     filter element,
                                                                     invalid if the received frame did not match
                                                                     any Rx filter element:
                                                                     @ref hal_fdcan_rx_header_t.frame_status
                                                                     is @ref HAL_FDCAN_RX_FRAME_NOT_MATCHED
                                                                     - Range is:
                                                                     0 to @ref hal_fdcan_config_t::std_filters_nbr
                                                                     or 0 to @ref hal_fdcan_config_t::ext_filters_nbr */
    hal_fdcan_rx_frame_status_t     frame_status          : 1;  /*!< Bit fields of the received frame status.
                                                                     It is useful when the acceptance of non-matching
                                                                     frames is enabled by selecting
                                                                     @ref HAL_FDCAN_NON_MATCHING_ACCEPT_RX_FIFO0
                                                                     or HAL_FDCAN_NON_MATCHING_ACCEPT_RX_FIFO1        */
  } b;                                                          /*!< Bit fields of the 64-bit rx header               */
} hal_fdcan_rx_header_t;

/**
  * @brief  FDCAN Tx element header definition
  */
typedef union
{
  uint64_t d64;                                                     /*!< 64-bit FDCAN Tx element header               */
  struct
  {
    uint32_t                        identifier                 : 29; /*!< Frame identifier. A standard identifier
                                                                          is stored in bits [28:18]                   */
    hal_fdcan_frame_type_t          frame_type                 : 1;  /*!< Frame type                                  */
    hal_fdcan_id_type_t             identifier_type            : 1;  /*!< Identifier type                             */
    hal_fdcan_error_state_t         error_state_indicator      : 1;  /*!< Error state indicator                       */
    uint32_t                                                   : 16; /*! Tx reserved field                            */
    hal_fdcan_data_length_code_t    data_length                : 4;  /*!< Data length code                            */
    hal_fdcan_bit_rate_switch_t     bit_rate_switch            : 1;  /*!< Bit rate switch                             */
    hal_fdcan_header_frame_format_t frame_format               : 1;  /*!< Frame format                                */
    uint32_t                                                   : 1;  /*!< Tx reserved bit                             */
    hal_fdcan_tx_event_fifo_t       event_fifo_control         : 1;  /*!< Event FIFO control                          */
    uint32_t                        message_marker             : 8;  /*!< Message marker.
                                                                          Written by CPU during Tx buffer configuration.
                                                                          Copied into Tx event FIFO element
                                                                          for identification of Tx message status     */
  } b;                                                               /*!< Bit fields of the 64-bit tx header          */
} hal_fdcan_tx_header_t;

/**
  * @brief  FDCAN Tx Event FIFO element header definition
  */
typedef union
{
  uint64_t d64;                                                 /*!< 64-bit FDCAN Tx Event FIFO element header        */
  struct
  {
    uint32_t                        identifier            : 29; /*!< Frame identifier, standard or extended.
                                                                     A standardidentifier is stored into ID[28:18] field
                                                                     of Rx element                                    */
    hal_fdcan_frame_type_t          frame_type            : 1;  /*!< Frame type                                       */
    hal_fdcan_id_type_t             identifier_type       : 1;  /*!< Identifier type                                  */
    hal_fdcan_error_state_t         error_state_indicator : 1;  /*!< Error state indicator                            */
    uint32_t                        tx_timestamp          : 16; /*!< Tx Timestamp. The timestamp counter value is
                                                                     captured on start of frame transmission.
                                                                     Resolution depends on the configuration of the
                                                                     timestamp counter prescaler                      */
    hal_fdcan_data_length_code_t    data_length           : 4;  /*!< Data length code                                 */
    hal_fdcan_bit_rate_switch_t     bit_rate_switch       : 1;  /*!< Bit rate switch                                  */
    hal_fdcan_header_frame_format_t frame_format          : 1;  /*!< Frame format                                     */
    hal_fdcan_tx_event_type_t       event_type            : 2;  /*!< Event type                                       */
    uint32_t                        message_marker        : 8;  /*!< Message marker. Copied from Tx event FIFO element
                                                                     for identification of Tx message status          */
  } b;                                                          /*!< Bit fields of the 64-bit tx event fifo header    */
} hal_fdcan_tx_evt_fifo_header_t;

/**
  * @brief  HAL FDCAN Global filter parameters
  */
typedef struct
{
  hal_fdcan_acceptance_non_matching_frame_t acceptance_non_matching_std; /*!< Acceptance of standard non-matching
                                                                              frames                               */
  hal_fdcan_acceptance_non_matching_frame_t acceptance_non_matching_ext; /*!< Acceptance of extended non-matching
                                                                              frames                               */
  hal_fdcan_acceptance_remote_frame_t       acceptance_remote_std;       /*!< Acceptance of standard remote frames */
  hal_fdcan_acceptance_remote_frame_t       acceptance_remote_ext;       /*!< Acceptance of extended remote frames */
} hal_fdcan_global_filter_config_t;

/**
  * @brief  HAL FDCAN Timestamp parameters
  */
typedef struct
{
  hal_fdcan_timestamp_source_t    timestamp_source;    /*!< Timestamp source                         */
  hal_fdcan_timestamp_prescaler_t timestamp_prescaler; /*!< Value of the timestamp prescaler counter */
}  hal_fdcan_timestamp_config_t;

/**
  * @brief  HAL FDCAN Timeout parameters
  */
typedef struct
{
  hal_fdcan_timeout_operation_t timeout_operation; /*!< Timeout select                              */
  uint32_t                      timeout_period;    /*!< Value of the timeout counter (down-counter) */
}  hal_fdcan_timeout_config_t;

/**
  * @brief  HAL FDCAN Tx Delay Compensation parameters
  */
typedef struct
{
  uint32_t tx_delay_comp_offset;     /*!< Transmitter delay compensation offset between 0 and 0x7F               */
  uint32_t tx_delay_comp_win_length; /*!< Transmitter delay compensation filter window length between 0 and 0x7F */
} hal_fdcan_tx_delay_compensation_config_t;

/**
  * @brief  HAL FDCAN filter structure definition
  */
typedef struct
{
  hal_fdcan_id_type_t          id_type;            /*!< Specifies the identifier type.                                */
  uint32_t                     filter_index;       /*!< Specifies the filter index. The range of this parameter depends
                                                        on the filter identifier type: @ref hal_fdcan_filter_t::id_type.
                                                        - if @ref HAL_FDCAN_ID_STANDARD :
                                                          value between 0 and 27
                                                        - if @ref HAL_FDCAN_ID_EXTENDED :
                                                          value between 0 and 7 */
  hal_fdcan_filter_type_t      filter_type;        /*!< Specifies the filter type. @ref HAL_FDCAN_FILTER_RANGE_NO_EIDM
                                                        is permitted only when @ref hal_fdcan_filter_t::id_type is
                                                        @ref HAL_FDCAN_ID_EXTENDED                                    */
  hal_fdcan_filter_config_t    filter_config;      /*!< Specifies the filter configuration                            */
  uint32_t                     filter_id1;         /*!< Specifies the filter first identifier.
                                                        The range of this parameter depends on the configured
                                                        @ref hal_fdcan_filter_t::id_type, if:
                                                        - @ref HAL_FDCAN_ID_STANDARD : value between 0 and 0x7FF,
                                                        - @ref HAL_FDCAN_ID_EXTENDED : value between 0 and 0x1FFFFFFF */
  uint32_t                     filter_id2;         /*!< Specifies the filter second identifier.
                                                        The range of this parameter depends on the configured
                                                        @ref hal_fdcan_filter_t::id_type, if:
                                                        - @ref HAL_FDCAN_ID_STANDARD : value between 0 and 0x7FF,
                                                        - @ref HAL_FDCAN_ID_EXTENDED : value between 0 and 0x1FFFFFFF */
} hal_fdcan_filter_t;

/**
  * @brief  HAL FDCAN High Priority Message Status structure definition
  */
typedef struct
{
  hal_fdcan_high_prio_filter_list_t filter_list;             /*!< Filter list of the matching filter elements         */
  uint32_t                          filter_index;            /*!< Index of matching filter element. This index only
                                                                  correspond to a previously configured filter        */
  hal_fdcan_high_prio_storage_t     message_location_status; /*!< High Priority Message Storage                       */
  uint32_t                          message_index;           /*!< Index of Rx FIFO element to which the message was
                                                                  stored. This parameter is valid only when
                                                                  @ref HAL_FDCAN_HIGH_PRIO_STORAGE_RXFIFO0 or
                                                                  @ref HAL_FDCAN_HIGH_PRIO_STORAGE_RXFIFO1
                                                                  are selected as High Priority Message Storage       */
} hal_fdcan_high_prio_msg_status_t;

/**
  * @brief  FDCAN Protocol Status structure definition
  */
typedef struct
{
  hal_fdcan_protocol_error_code_t      last_error_code;      /*!< Type of the last error that occurred
                                                                  on the FDCAN bus                                    */
  hal_fdcan_protocol_error_code_t      data_last_error_code; /*!< Type of the last error that occurred in the data
                                                                  phase of a CAN FD format frame with its Bit Rate
                                                                  Switching flag set                                  */
  hal_fdcan_communication_state_t      activity;             /*!< Communication state                                 */
  hal_fdcan_protocol_error_status_t    error_status;         /*!< Error status                                        */
  hal_fdcan_warning_status_t           error_warning;        /*!< Warning status                                      */
  hal_fdcan_bus_off_status_t           bus_off;              /*!< Bus_Off status                                      */
  hal_fdcan_esi_flag_status_t          rx_esi_flag;          /*!< Error State Indicator flag of last received
                                                                  CAN FD message                                      */
  hal_fdcan_brs_flag_status_t          rx_brs_flag;          /*!< Switching flag of last received CAN FD message      */
  hal_fdcan_edl_flag_status_t          rx_fdf_flag;          /*!< Specifies if CAN FD message (FDF flag set) has been
                                                                  received since last protocol status                 */
  hal_fdcan_protocol_exception_event_t protocol_exception;   /*!< Protocol Exception status                           */
  uint32_t                             tdc_value;            /*!< Transmitter Delay Compensation Value.
                                                                  This parameter can be a number between 0 and 127    */
} hal_fdcan_protocol_status_t;

/**
  * @brief  FDCAN Error Counters structure definition
  */
typedef struct
{
  uint32_t                           tx_error_cnt;            /*!< Specifies the Transmit Error Counter Value.
                                                                   This parameter can be a number between 0 and 255 */
  uint32_t                           rx_error_cnt;            /*!< Specifies the Receive Error Counter Value.
                                                                   This parameter can be a number between 0 and 127 */
  hal_fdcan_rx_error_passive_level_t rx_error_passive_status; /*!< Specifies the Receive Error Passive status       */
  uint32_t                           global_cnt;              /*!< Specifies the Transmit/Receive error logging
                                                                   counter value. This parameter can be a number
                                                                   between 0 and 255. This counter is incremented
                                                                   each time when a FDCAN protocol error causes the
                                                                   TxErrorCnt or the RxErrorCnt to be incremented.
                                                                   The counter stops at 255; the next increment of
                                                                   TxErrorCnt or RxErrorCnt sets the interrupt
                                                                   flag HAL_FDCAN_FLAG_ERROR_LOGGING_OVERFLOW       */
} hal_fdcan_error_counters_t;

/**
  * @brief  HAL FDCAN Message RAM blocks
  */
typedef struct
{
  uint32_t std_filter_start_addr;  /*!< Specifies the standard filter list start address */
  uint32_t ext_filter_start_addr;  /*!< Specifies the extended filter list start address */
  uint32_t rx_fifo0_start_addr;    /*!< Specifies the Rx FIFO 0 start address            */
  uint32_t rx_fifo1_start_addr;    /*!< Specifies the Rx FIFO 1 start address            */
  uint32_t tx_event_start_addr;    /*!< Specifies the Tx event FIFO start address        */
  uint32_t tx_fifo_start_addr;     /*!< Specifies the Tx FIFO/Queue start address        */
} hal_fdcan_msg_ram_address_t;

/**
  * @brief  FDCAN Nominal Bit Timing structure definition
  */
typedef struct
{
  uint32_t nominal_prescaler;  /*!< Specifies the value by which the oscillator frequency is divided for generating
                                    the nominal bit time quanta. This parameter must be a number between 1 and 512  */
  uint32_t nominal_jump_width; /*!< Specifies the maximum number of time quanta the FDCAN hardware is allowed to
                                    lengthen or shorten a bit to perform resynchronization.
                                    This parameter must be a number between 1 and 128                               */
  uint32_t nominal_time_seg1;  /*!< Specifies the number of time quanta in Bit Segment 1.
                                    This parameter must be a number between 2 and 256                               */
  uint32_t nominal_time_seg2;  /*!< Specifies the number of time quanta in Bit Segment 2.
                                    This parameter must be a number between 2 and 128                               */
} hal_fdcan_nominal_bit_timing_t;

/**
  * @brief  FDCAN Data Bit Timing structure definition
  */
typedef struct
{
  uint32_t data_prescaler;  /*!< Specifies the value by which the oscillator frequency is divided for generating
                                 the Data bit time quanta. This parameter must be a number between 1 and 32      */
  uint32_t data_jump_width; /*!< Specifies the maximum number of time quanta the FDCAN hardware is allowed to
                                 lengthen or shorten a Data bit to perform resynchronization.
                                 This parameter must be a number between 1 and 16                                */
  uint32_t data_time_seg1;  /*!< Specifies the number of time quanta in Data Bit Segment 1.
                                 This parameter must be a number between 1 and 32                                */
  uint32_t data_time_seg2;  /*!< Specifies the number of time quanta in Data Bit Segment 2.
                                 This parameter must be a number between 1 and 16                                */
} hal_fdcan_data_bit_timing_t;

/**
  * @brief  HAL FDCAN Global Configuration Structure definition
  * After reset, the configuration for CCCR register is as follow:
  *           - NISO = 0: CAN FD frame according to ISO11898-1
  *           - TXP  = 0: FDCAN pauses for 2 CAN bits before next transmission is disabled
  *           - EFBI = 0: Edge Filtering during bus integration is disabled
  *           - PXHD = 0: Protocol Exception handling is enabled
  *           - BRSE = 0: FDCAN bit rate switch is disabled
  *           - FDOE = 0: FD operation is disabled
  *           - TEST = 0: Test Mode is normal mode
  *           - DAR  = 0: Disable Automatic Retransmission is enabled
  *           - MON  = 0: Bus Monitoring mode is disabled
  *           - CSR  = 0: Clock Stop Request: No clock stop request
  *           - CSA  = 0: Clock Stop Acknowledge - No clock stop acknowledged
  *           - ASM  = 0: ASM restricted operation mode - Normal CAN operation
  *           - CCE  = 0: Configuration Change Enable - No write access to the protected registers
  *           - INIT = 1: Initialization started
  */
typedef struct
{
  hal_fdcan_nominal_bit_timing_t         nominal_bit_timing;  /*!< Nominal bit timing                                 */
  hal_fdcan_data_bit_timing_t            data_bit_timing;     /*!< Data Bit Timing                                    */
  hal_fdcan_mode_t                       mode;                /*!< FDCAN mode                                         */
  hal_fdcan_frame_format_t               frame_format;        /*!< FDCAN frame format                                 */
  hal_fdcan_auto_retransmission_status_t auto_retransmission; /*!< FDCAN automatic retransmission mode                */
  hal_fdcan_transmit_pause_status_t      transmit_pause;      /*!< FDCAN Transmit Pause feature                       */
  hal_fdcan_protocol_exception_status_t  protocol_exception;  /*!< FDCAN Protocol Exception Handling                  */
  uint32_t                               std_filters_nbr;     /*!< Number of standard Message ID filters.
                                                                   This parameter must be a number between 0 and 28   */
  uint32_t                               ext_filters_nbr;     /*!< Number of extended Message ID filters.
                                                                   This parameter must be a number between 0 and 8    */
  hal_fdcan_tx_mode_t                    tx_fifo_queue_mode;  /*!< Tx FIFO/Queue mode selection                       */
} hal_fdcan_config_t;

typedef struct hal_fdcan_handle_s hal_fdcan_handle_t; /*!< FDCAN handle Structure type */

#if defined(USE_HAL_FDCAN_REGISTER_CALLBACKS) && (USE_HAL_FDCAN_REGISTER_CALLBACKS == 1U)
/**
  * @brief  HAL FDCAN Callback pointer definition
  */

typedef void (*hal_fdcan_fifo_cb_t)(hal_fdcan_handle_t *hfdcan,
                                    uint32_t interrupts_list);      /*!< Pointer to interrupts list FDCAN callback
                                                                         function                                     */
typedef void (*hal_fdcan_tx_buffer_cb_t)(hal_fdcan_handle_t *hfdcan,
                                         uint32_t buffer_indexes);  /*!< Pointer to interrupts Tx Buffer Complete/Abort
                                                                         FDCAN callback function                      */
typedef void (*hal_fdcan_cb_t)(hal_fdcan_handle_t *hfdcan);         /*!< Pointer to a generic FDCAN callback function */

#endif /* USE_HAL_FDCAN_REGISTER_CALLBACKS */

/**
  * @brief  HAL FDCAN handle structure definition
  */
struct hal_fdcan_handle_s
{
  hal_fdcan_t                    instance;                  /*!< FDCAN Instance                                  */

  hal_fdcan_msg_ram_address_t    msg_ram;                   /*!< Message RAM blocks                              */
  volatile hal_fdcan_state_t     global_state;              /*!< Communication current state                     */
  hal_fdcan_state_t              previous_state;            /*!< Communication previous state                    */

#if defined(USE_HAL_FDCAN_GET_LAST_ERRORS) && (USE_HAL_FDCAN_GET_LAST_ERRORS == 1)
  volatile uint32_t              last_error_codes;          /*!< Last error codes                                */
#endif /* USE_HAL_FDCAN_GET_LAST_ERRORS */

  uint32_t                       latest_tx_fifo_q_request;  /*!< Tx buffer index of latest Tx FIFO/Queue request */

#if defined(USE_HAL_MUTEX) && (USE_HAL_MUTEX == 1)
  hal_os_semaphore_t             semaphore;                 /*!< FDCAN OS semaphore                              */
#endif /* USE_HAL_MUTEX */

#if defined(USE_HAL_FDCAN_USER_DATA) && (USE_HAL_FDCAN_USER_DATA == 1)
  const void                    *p_user_data;               /*!< User Data Pointer                               */
#endif /* USE_HAL_FDCAN_USER_DATA */

#if defined(USE_HAL_FDCAN_REGISTER_CALLBACKS) && (USE_HAL_FDCAN_REGISTER_CALLBACKS == 1U)
  hal_fdcan_fifo_cb_t            p_tx_eventfifo_cb;         /*!< Tx Event FIFO callback                          */
  hal_fdcan_fifo_cb_t            p_rx_fifo0_cb;             /*!< Rx FIFO 0 callback                              */
  hal_fdcan_fifo_cb_t            p_rx_fifo1_cb;             /*!< Rx FIFO 1 callback                              */
  hal_fdcan_cb_t                 p_tx_fifoempty_cb;         /*!< Tx FIFO Empty callback                          */
  hal_fdcan_tx_buffer_cb_t       p_tx_buffercomplete_cb;    /*!< Tx Buffer complete callback                     */
  hal_fdcan_tx_buffer_cb_t       p_tx_bufferabort_cb;       /*!< Tx Buffer abort callback                        */
  hal_fdcan_cb_t                 p_highpriority_msg_cb;     /*!< High priority message callback                  */
  hal_fdcan_cb_t                 p_ts_wraparound_cb;        /*!< Timestamp wraparound callback                   */
  hal_fdcan_cb_t                 p_error_cb;                /*!< Error callback                                  */
#endif /* USE_HAL_FDCAN_REGISTER_CALLBACKS */
};

/**
  * @}
  */

/* Exported functions --------------------------------------------------------*/
/** @defgroup FDCAN_Exported_Functions HAL FDCAN Functions
  * @{
  */

/** @defgroup FDCAN_Exported_Functions_Group1 Initialization and de-initialization functions
  * @{
  */

hal_status_t HAL_FDCAN_Init(hal_fdcan_handle_t *hfdcan, hal_fdcan_t instance);
void         HAL_FDCAN_DeInit(hal_fdcan_handle_t *hfdcan);

/**
  * @}
  */

/** @defgroup FDCAN_Exported_Functions_Group2 Enter and Exit Power Down mode
  * @{
  */

/* Power Down Mode */
hal_status_t HAL_FDCAN_EnterPowerDownMode(hal_fdcan_handle_t *hfdcan);
hal_status_t HAL_FDCAN_ExitPowerDownMode(hal_fdcan_handle_t *hfdcan);

/**
  * @}
  */

/** @defgroup FDCAN_Exported_Functions_Group3 Configuration functions
  * @{
  */

/* Global configuration */
hal_status_t HAL_FDCAN_SetConfig(hal_fdcan_handle_t *hfdcan, const hal_fdcan_config_t *p_config);
void         HAL_FDCAN_GetConfig(const hal_fdcan_handle_t *hfdcan, hal_fdcan_config_t *p_config);

/* Nominal Bit Timing */
hal_status_t HAL_FDCAN_SetNominalBitTiming(const hal_fdcan_handle_t *hfdcan,
                                           const hal_fdcan_nominal_bit_timing_t *p_nominal_bit_timing);
void         HAL_FDCAN_GetNominalBitTiming(const hal_fdcan_handle_t *hfdcan,
                                           hal_fdcan_nominal_bit_timing_t *nominal_bit_timing);

/* Data Bit Timing */
hal_status_t HAL_FDCAN_SetDataBitTiming(const hal_fdcan_handle_t *hfdcan,
                                        const hal_fdcan_data_bit_timing_t *p_data_bit_timing);
void         HAL_FDCAN_GetDataBitTiming(const hal_fdcan_handle_t *hfdcan, hal_fdcan_data_bit_timing_t *data_bit_timing);

/* Filter - To set/get the acceptance filters parameters for standard and extended filters */
hal_status_t HAL_FDCAN_SetFilter(const hal_fdcan_handle_t *hfdcan, const hal_fdcan_filter_t *p_filter_config);
void         HAL_FDCAN_GetFilter(const hal_fdcan_handle_t *hfdcan, hal_fdcan_filter_t *p_filter_config,
                                 uint32_t filter_index, hal_fdcan_id_type_t id_type);

/* Global filter configuration */
hal_status_t HAL_FDCAN_SetGlobalFilter(const hal_fdcan_handle_t *hfdcan,
                                       const hal_fdcan_global_filter_config_t *p_global_filter_config);
void         HAL_FDCAN_GetGlobalFilter(const hal_fdcan_handle_t *hfdcan,
                                       hal_fdcan_global_filter_config_t *p_global_filter_config);

/* Extended ID mask for acceptance filtering */
hal_status_t HAL_FDCAN_SetExtendedIdMask(const hal_fdcan_handle_t *hfdcan, uint32_t mask);
uint32_t     HAL_FDCAN_GetExtendedIdMask(const hal_fdcan_handle_t *hfdcan);

/* Clock divider */
hal_status_t              HAL_FDCAN_SetClockDivider(const hal_fdcan_handle_t *hfdcan,
                                                    hal_fdcan_clock_divider_t clock_divider);
hal_fdcan_clock_divider_t HAL_FDCAN_GetClockDivider(const hal_fdcan_handle_t *hfdcan);

/* Rx FIFO Overwrite */
hal_status_t HAL_FDCAN_SetRxFifoOverwrite(const hal_fdcan_handle_t *hfdcan, hal_fdcan_rx_location_t rx_fifo_idx,
                                          hal_fdcan_rx_fifo_operative_mode_t operation_mode);
void         HAL_FDCAN_GetRxFifoOverwrite(const hal_fdcan_handle_t *hfdcan, hal_fdcan_rx_location_t rx_fifo_sel,
                                          hal_fdcan_rx_fifo_operative_mode_t *p_rx_operation);

/* RAM Watchdog */
hal_status_t HAL_FDCAN_SetRamWatchdog(const hal_fdcan_handle_t *hfdcan, uint32_t counter_start_value);
uint32_t     HAL_FDCAN_GetRamWatchdog(const hal_fdcan_handle_t *hfdcan);

/* TimeStamp counter */
hal_status_t HAL_FDCAN_SetConfigTimestampCounter(const hal_fdcan_handle_t *hfdcan,
                                                 const hal_fdcan_timestamp_config_t *p_timestamp_config);
void         HAL_FDCAN_GetConfigTimestampCounter(const hal_fdcan_handle_t *hfdcan,
                                                 hal_fdcan_timestamp_config_t *p_timestamp_config);
uint16_t     HAL_FDCAN_GetTimestampCounter(const hal_fdcan_handle_t *hfdcan);
hal_status_t HAL_FDCAN_ResetTimestampCounter(const hal_fdcan_handle_t *hfdcan);

/* Timeout counter */
hal_status_t HAL_FDCAN_SetConfigTimeoutCounter(const hal_fdcan_handle_t *hfdcan,
                                               const hal_fdcan_timeout_config_t *p_timeout_param);
void         HAL_FDCAN_GetConfigTimeoutCounter(const hal_fdcan_handle_t *hfdcan,
                                               hal_fdcan_timeout_config_t *p_timeout_param);
hal_status_t HAL_FDCAN_EnableTimeoutCounter(const hal_fdcan_handle_t *hfdcan);
hal_status_t HAL_FDCAN_DisableTimeoutCounter(const hal_fdcan_handle_t *hfdcan);
hal_fdcan_timeout_counter_status_t HAL_FDCAN_IsEnabledTimeoutCounter(const hal_fdcan_handle_t *hfdcan);

uint32_t     HAL_FDCAN_GetTimeoutCounter(const hal_fdcan_handle_t *hfdcan);
hal_status_t HAL_FDCAN_ResetTimeoutCounter(const hal_fdcan_handle_t *hfdcan);

/* Delay compensation mechanism to compensate the CAN transmitter loop delay */
hal_status_t HAL_FDCAN_SetConfigTxDelayCompensation(const hal_fdcan_handle_t *hfdcan,
                                                    const hal_fdcan_tx_delay_compensation_config_t *p_tx_delay_param);
void         HAL_FDCAN_GetConfigTxDelayCompensation(const hal_fdcan_handle_t *hfdcan,
                                                    hal_fdcan_tx_delay_compensation_config_t *p_tx_delay_param);
hal_status_t HAL_FDCAN_EnableTxDelayCompensation(const hal_fdcan_handle_t *hfdcan);
hal_status_t HAL_FDCAN_DisableTxDelayCompensation(const hal_fdcan_handle_t *hfdcan);
hal_fdcan_transmitter_delay_comp_status_t HAL_FDCAN_IsEnabledTxDelayCompensation(const hal_fdcan_handle_t *hfdcan);

/* ISO Mode - ISO11898-1 or CAN FD Specification V1.0 */
hal_status_t                HAL_FDCAN_DisableISOMode(const hal_fdcan_handle_t *hfdcan);
hal_status_t                HAL_FDCAN_EnableISOMode(const hal_fdcan_handle_t *hfdcan);
hal_fdcan_iso_mode_status_t HAL_FDCAN_IsEnabledISOMode(const hal_fdcan_handle_t *hfdcan);

/* Edge filtering */
hal_status_t                      HAL_FDCAN_DisableEdgeFiltering(const hal_fdcan_handle_t *hfdcan);
hal_status_t                      HAL_FDCAN_EnableEdgeFiltering(const hal_fdcan_handle_t *hfdcan);
hal_fdcan_edge_filtering_status_t HAL_FDCAN_IsEnabledEdgeFiltering(const hal_fdcan_handle_t *hfdcan);

/* Operating mode */
hal_status_t     HAL_FDCAN_SetMode(const hal_fdcan_handle_t *hfdcan, hal_fdcan_mode_t mode);
hal_fdcan_mode_t HAL_FDCAN_GetMode(const hal_fdcan_handle_t *hfdcan);

/* Frame format */
hal_status_t          HAL_FDCAN_SetFrameFormat(const hal_fdcan_handle_t *hfdcan, hal_fdcan_frame_format_t frame_format);
hal_fdcan_frame_format_t HAL_FDCAN_GetFrameFormat(const hal_fdcan_handle_t *hfdcan);

/* Auto retransmission of unsuccessful messages */
hal_status_t                    HAL_FDCAN_SetAutoRetransmission(const hal_fdcan_handle_t *hfdcan,
                                                                hal_fdcan_auto_retransmission_status_t auto_retransmit);
hal_fdcan_auto_retransmission_status_t HAL_FDCAN_GetAutoRetransmission(const hal_fdcan_handle_t *hfdcan);

/* Transmit pause */
hal_status_t                      HAL_FDCAN_SetTransmitPause(const hal_fdcan_handle_t *hfdcan,
                                                             hal_fdcan_transmit_pause_status_t transmit_pause);
hal_fdcan_transmit_pause_status_t HAL_FDCAN_GetTransmitPause(const hal_fdcan_handle_t *hfdcan);

/* Protocol exception */
hal_status_t                   HAL_FDCAN_SetProtocolException(const hal_fdcan_handle_t *hfdcan,
                                                              hal_fdcan_protocol_exception_status_t protocol_exception);
hal_fdcan_protocol_exception_status_t HAL_FDCAN_GetProtocolException(const hal_fdcan_handle_t *hfdcan);

/* Tx mode */
hal_status_t        HAL_FDCAN_SetTxMode(const hal_fdcan_handle_t *hfdcan, hal_fdcan_tx_mode_t tx_mode);
hal_fdcan_tx_mode_t HAL_FDCAN_GetTxMode(const hal_fdcan_handle_t *hfdcan);

/* FDCAN current clock frequency */
uint32_t HAL_FDCAN_GetClockFreq(const hal_fdcan_handle_t *hfdcan);

#if defined(USE_HAL_FDCAN_REGISTER_CALLBACKS) && (USE_HAL_FDCAN_REGISTER_CALLBACKS == 1U)
/* Callbacks registering */
hal_status_t HAL_FDCAN_RegisterTxEventFifoCallback(hal_fdcan_handle_t *hfdcan, hal_fdcan_fifo_cb_t p_callback);
hal_status_t HAL_FDCAN_RegisterRxFifo0Callback(hal_fdcan_handle_t *hfdcan, hal_fdcan_fifo_cb_t p_callback);
hal_status_t HAL_FDCAN_RegisterRxFifo1Callback(hal_fdcan_handle_t *hfdcan, hal_fdcan_fifo_cb_t p_callback);
hal_status_t HAL_FDCAN_RegisterTxFifoEmptyCallback(hal_fdcan_handle_t *hfdcan, hal_fdcan_cb_t p_callback);
hal_status_t HAL_FDCAN_RegisterTxBufferCompleteCallback(hal_fdcan_handle_t *hfdcan,
                                                        hal_fdcan_tx_buffer_cb_t p_callback);
hal_status_t HAL_FDCAN_RegisterTxBufferAbortCallback(hal_fdcan_handle_t *hfdcan, hal_fdcan_tx_buffer_cb_t p_callback);
hal_status_t HAL_FDCAN_RegisterHighPriorityMessageCallback(hal_fdcan_handle_t *hfdcan, hal_fdcan_cb_t p_callback);
hal_status_t HAL_FDCAN_RegisterTimestampWraparoundCallback(hal_fdcan_handle_t *hfdcan, hal_fdcan_cb_t p_callback);
hal_status_t HAL_FDCAN_RegisterErrorCallback(hal_fdcan_handle_t *hfdcan, hal_fdcan_cb_t p_callback);
#endif /* USE_HAL_FDCAN_REGISTER_CALLBACKS */

/**
  * @}
  */

/** @defgroup FDCAN_Exported_Functions_Group4 Control Functions
  * @{
  */

/* Start / Stop the FDCAN module */
hal_status_t HAL_FDCAN_Start(hal_fdcan_handle_t *hfdcan);
hal_status_t HAL_FDCAN_Stop(hal_fdcan_handle_t *hfdcan);

/* Functions involved in Transmission process */
hal_status_t HAL_FDCAN_ReqTransmitMsgFromFIFOQ(hal_fdcan_handle_t *hfdcan,
                                               const hal_fdcan_tx_header_t *p_tx_element_header,
                                               const uint8_t *p_tx_data);
hal_fdcan_fifo_status_t HAL_FDCAN_GetTxFifoStatus(const hal_fdcan_handle_t *hfdcan);
uint32_t HAL_FDCAN_GetLatestTxFifoQRequestBuffer(const hal_fdcan_handle_t *hfdcan);
hal_fdcan_tx_fifo_free_level_t HAL_FDCAN_GetTxFifoFreeLevel(const hal_fdcan_handle_t *hfdcan);
hal_status_t HAL_FDCAN_ReqAbortOfTxBuffer(const hal_fdcan_handle_t *hfdcan, uint32_t buffer_index);
hal_status_t HAL_FDCAN_GetTxEvent(const hal_fdcan_handle_t *hfdcan, hal_fdcan_tx_evt_fifo_header_t *p_tx_event);
hal_fdcan_tx_buffer_status_t HAL_FDCAN_GetTxBufferMessageStatus(const hal_fdcan_handle_t *hfdcan,
                                                                uint32_t tx_buffer_index);

/* Functions involved in Receiving process */
hal_status_t HAL_FDCAN_GetReceivedMessage(const hal_fdcan_handle_t *hfdcan, hal_fdcan_rx_location_t rx_location,
                                          hal_fdcan_rx_header_t *p_rx_header, uint8_t *p_rx_data);
void         HAL_FDCAN_GetRxFifoFillLevel(const hal_fdcan_handle_t *hfdcan, hal_fdcan_rx_location_t rx_fifo_sel,
                                          uint32_t *p_fill_level);

/* Functions involved in general Tx/Rx process */
hal_status_t HAL_FDCAN_GetHighPriorityMessageStatus(const hal_fdcan_handle_t *hfdcan,
                                                    hal_fdcan_high_prio_msg_status_t *p_hp_msg_status);
hal_status_t HAL_FDCAN_GetProtocolStatus(const hal_fdcan_handle_t *hfdcan,
                                         hal_fdcan_protocol_status_t *p_protocol_status);
hal_status_t HAL_FDCAN_GetErrorCounters(const hal_fdcan_handle_t *hfdcan, hal_fdcan_error_counters_t *p_error_counters);

/* Restricted operation mode */
hal_status_t                          HAL_FDCAN_EnableRestrictedOperationMode(const hal_fdcan_handle_t *hfdcan);
hal_status_t                          HAL_FDCAN_DisableRestrictedOperationMode(const hal_fdcan_handle_t *hfdcan);
hal_fdcan_restricted_op_mode_status_t HAL_FDCAN_IsEnabledRestrictedOperationMode(const hal_fdcan_handle_t *hfdcan);

/* Bus Off error Recovery  */
hal_status_t HAL_FDCAN_Recover(const hal_fdcan_handle_t *hfdcan);

/**
  * @}
  */

/** @defgroup FDCAN_Exported_Functions_Group5 Interrupts Management Functions
  * @{
  */

void HAL_FDCAN_IRQHandler(hal_fdcan_handle_t *hfdcan);

hal_status_t HAL_FDCAN_SetInterruptGroupsToLine(const hal_fdcan_handle_t *hfdcan, uint32_t interrupt_groups,
                                                uint32_t it_line);
uint32_t     HAL_FDCAN_GetLineFromInterruptGroup(const hal_fdcan_handle_t *hfdcan, uint32_t interrupt_group);

hal_status_t          HAL_FDCAN_EnableInterrupts(const hal_fdcan_handle_t *hfdcan, uint32_t interrupts);
hal_status_t          HAL_FDCAN_DisableInterrupts(const hal_fdcan_handle_t *hfdcan, uint32_t interrupts);
hal_fdcan_it_status_t HAL_FDCAN_IsEnabledInterrupt(const hal_fdcan_handle_t *hfdcan, uint32_t interrupt);

hal_status_t                HAL_FDCAN_EnableInterruptLines(const hal_fdcan_handle_t *hfdcan, uint32_t it_lines);
hal_status_t                HAL_FDCAN_DisableInterruptLines(const hal_fdcan_handle_t *hfdcan, uint32_t it_lines);
hal_fdcan_it_lines_status_t HAL_FDCAN_IsEnabledInterruptLine(const hal_fdcan_handle_t *hfdcan, uint32_t it_line);

hal_status_t         HAL_FDCAN_EnableTxBufferCompleteInterrupts(const hal_fdcan_handle_t *hfdcan, uint32_t buffer_idx);
hal_status_t         HAL_FDCAN_DisableTxBufferCompleteInterrupts(const hal_fdcan_handle_t *hfdcan, uint32_t buffer_idx);
hal_fdcan_it_txbuffer_complete_status_t HAL_FDCAN_IsEnabledTxBufferCompleteInterrupt(const hal_fdcan_handle_t *hfdcan,
    uint32_t buffer_idx);

hal_status_t     HAL_FDCAN_EnableTxBufferCancellationInterrupts(const hal_fdcan_handle_t *hfdcan, uint32_t buffer_idx);
hal_status_t     HAL_FDCAN_DisableTxBufferCancellationInterrupts(const hal_fdcan_handle_t *hfdcan, uint32_t buffer_idx);
hal_fdcan_it_txbuffer_abort_status_t HAL_FDCAN_IsEnabledTxBufferCancellationInterrupt(const hal_fdcan_handle_t *hfdcan,
    uint32_t buffer_idx);

/**
  * @}
  */

/** @defgroup FDCAN_Exported_Functions_Group6 Weak Callback Functions
  * @{
  */

void HAL_FDCAN_TxEventFifoCallback(hal_fdcan_handle_t *hfdcan, uint32_t tx_event_fifo_interrupts);
void HAL_FDCAN_RxFifo0Callback(hal_fdcan_handle_t *hfdcan, uint32_t rx_fifo0_interrupts);
void HAL_FDCAN_RxFifo1Callback(hal_fdcan_handle_t *hfdcan, uint32_t rx_fifo1_interrupts);
void HAL_FDCAN_TxFifoEmptyCallback(hal_fdcan_handle_t *hfdcan);
void HAL_FDCAN_TxBufferCompleteCallback(hal_fdcan_handle_t *hfdcan, uint32_t buffer_indexes);
void HAL_FDCAN_TxBufferAbortCallback(hal_fdcan_handle_t *hfdcan, uint32_t buffer_indexes);
void HAL_FDCAN_HighPriorityMessageCallback(hal_fdcan_handle_t *hfdcan);
void HAL_FDCAN_TimestampWraparoundCallback(hal_fdcan_handle_t *hfdcan);
void HAL_FDCAN_ErrorCallback(hal_fdcan_handle_t *hfdcan);

/**
  * @}
  */

/** @defgroup FDCAN_Exported_Functions_Group7 Error and State functions
  * @{
  */

#if defined(USE_HAL_FDCAN_GET_LAST_ERRORS) && (USE_HAL_FDCAN_GET_LAST_ERRORS == 1)
uint32_t HAL_FDCAN_GetLastErrorCodes(const hal_fdcan_handle_t *hfdcan);
#endif /* USE_HAL_FDCAN_GET_LAST_ERRORS */

hal_fdcan_state_t HAL_FDCAN_GetState(const hal_fdcan_handle_t *hfdcan);

/**
  * @}
  */

#if defined(USE_HAL_MUTEX) && (USE_HAL_MUTEX == 1)
/** @defgroup FDCAN_Exported_Functions_Group8 Peripheral Acquire/Release/Free the bus
  * @{
  */

hal_status_t HAL_FDCAN_AcquireBus(hal_fdcan_handle_t *hfdcan, uint32_t timeout_ms);
hal_status_t HAL_FDCAN_ReleaseBus(hal_fdcan_handle_t *hfdcan);

/**
  * @}
  */

#endif /* USE_HAL_MUTEX */

#if defined(USE_HAL_FDCAN_USER_DATA) && (USE_HAL_FDCAN_USER_DATA == 1)
/** @defgroup FDCAN_Exported_Functions_Group9 User data Set/Get
  * @{
  */

void       HAL_FDCAN_SetUserData(hal_fdcan_handle_t *hfdcan, const void *p_user_data);
const void *HAL_FDCAN_GetUserData(const hal_fdcan_handle_t *hfdcan);

/**
  * @}
  */
#endif /* USE_HAL_FDCAN_USER_DATA */

/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

#endif /* FDCAN1 */

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* STM32H7PXX_HAL_FDCAN_H */
