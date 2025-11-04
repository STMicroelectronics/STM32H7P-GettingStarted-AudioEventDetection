/**
  **********************************************************************************************************************
  * @file    stm32h7pxx_hal_i3c.h
  * @author  GPM Application Team
  * @brief   Header file of I3C HAL module.
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

/* Define to prevent recursive inclusion -----------------------------------------------------------------------------*/
#ifndef STM32H7PXX_HAL_I3C_H
#define STM32H7PXX_HAL_I3C_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ----------------------------------------------------------------------------------------------------------*/
#include "stm32h7pxx_hal_def.h"
#include "stm32h7pxx_ll_i3c.h"

/** @addtogroup STM32H7Pxx_HAL_Driver
  * @{
  */

/** @defgroup I3C I3C
  * @{
  */

/* Exported constants ------------------------------------------------------------------------------------------------*/
/** @defgroup I3C_Exported_Constants HAL I3C Constants
  * @{
  */

/** @defgroup I3C_ERROR_CODE_DEFINITION ERROR CODE DEFINITION
  * @{
  */
#define HAL_I3C_ERROR_NONE (0x00000000U) /*!< No error */

#define HAL_I3C_ERROR_CE0  LL_I3C_CONTROLLER_ERROR_CE0 /*!< 0x0: Ctrl: Illegally formatted CCC */
#define HAL_I3C_ERROR_CE1  LL_I3C_CONTROLLER_ERROR_CE1 /*!< 0x1: Ctrl: Tx data on the bus is different than expected */
#define HAL_I3C_ERROR_CE2  LL_I3C_CONTROLLER_ERROR_CE2 /*!< 0x2: Ctrl: Broadcast address7'h7E has been nacked */
#define HAL_I3C_ERROR_CE3  LL_I3C_CONTROLLER_ERROR_CE3 /*!< 0x3: Ctrl: New ctrl did not drive the bus after ctrl-role
                                                                       handoff */
#define HAL_I3C_ERROR_TE0  LL_I3C_TARGET_ERROR_TE0 /*!< 0x8: Tgt: Invalid broadcast address */
#define HAL_I3C_ERROR_TE1  LL_I3C_TARGET_ERROR_TE1 /*!< 0x9: Tgt: Invalid CCC Code */
#define HAL_I3C_ERROR_TE2  LL_I3C_TARGET_ERROR_TE2 /*!< 0xA: Tgt: Parity error during a write data */
#define HAL_I3C_ERROR_TE3  LL_I3C_TARGET_ERROR_TE3 /*!< 0xB: Tgt: Parity error on assigned address during DAA */
#define HAL_I3C_ERROR_TE4  LL_I3C_TARGET_ERROR_TE4 /*!< 0xC: Tgt: 7'h7E missing after restart during DAA procedure */
#define HAL_I3C_ERROR_TE5  LL_I3C_TARGET_ERROR_TE5 /*!< 0xD: Tgt: Illegally formatted CCC */
#define HAL_I3C_ERROR_TE6  LL_I3C_TARGET_ERROR_TE6 /*!< 0xE: Tgt: Tx data on the bus is different than expected */
#define HAL_I3C_ERROR_STALL         I3C_SER_STALL  /*!< 0x20: SCL stall error */
#define HAL_I3C_ERROR_DOVR          I3C_SER_DOVR   /*!< 0x40: Rx FIFO over-Run or Tx FIFO under-Run error */
#define HAL_I3C_ERROR_COVR          I3C_SER_COVR   /*!< 0x80: S FIFO over-Run or C FIFO under-Run error */
#define HAL_I3C_ERROR_ADDRESS_NACK  I3C_SER_ANACK  /*!< 0x100: Address not acknowledged error */
#define HAL_I3C_ERROR_DATA_NACK     I3C_SER_DNACK  /*!< 0x200: Data not acknowledged error */
#define HAL_I3C_ERROR_DATA_HAND_OFF I3C_SER_DERR   /*!< 0x400: Data error during Controller-Role hand-off process */
#define HAL_I3C_ERROR_DMA           0x00010000U    /*!< 0x10000: DMA transfer error */
#define HAL_I3C_ERROR_DYNAMIC_ADDR  0x00020000U    /*!< 0x20000: Dynamic address error */
/**
  * @}
  */


/** @defgroup I3C_STALL_FEATURE_DEFINITION STALL FEATURE DEFINITION
  * @{
  */
#define HAL_I3C_STALL_ACK      I3C_TIMINGR2_STALLA /*!< Ctrl clock stall on the ACK phase */
#define HAL_I3C_STALL_CCC      I3C_TIMINGR2_STALLC /*!< Ctrl clock stall on the T bit phase of a CCC communication
                                                        to allow the target to decode command */
#define HAL_I3C_STALL_TX       I3C_TIMINGR2_STALLD /*!< Ctrl clock stall on parity phase of data to allow the
                                                        target to read received data */
#define HAL_I3C_STALL_RX       I3C_TIMINGR2_STALLT /*!< Ctrl clock stall on the T bit phase of data enable to
                                                        allow the target to prepare data to be sent */
#define HAL_I3C_STALL_I2C_ACK  I3C_TIMINGR2_STALLL /*!< Ctrl clock stall on the address ACK/NACK phase of a legacy
                                                        I2C read/write message phase, to allows the I2C target to
                                                        prepare the next message */
#define HAL_I3C_STALL_I2C_TX   I3C_TIMINGR2_STALLS /*!< Ctrl clock stall on the data ACK/NACK phase of a legacy
                                                        I2C write message phase, to allows the I2C target to prepare
                                                        the next data byte to receive */
#define HAL_I3C_STALL_I2C_RX   I3C_TIMINGR2_STALLR /*!< Ctrl clock stall on the data ACK/NACK phase of a legacy
                                                        I2C read message phase, to allows the I2C target to prepare the
                                                        next data byte to send */

#define HAL_I3C_STALL_ALL      (HAL_I3C_STALL_ACK | HAL_I3C_STALL_CCC | HAL_I3C_STALL_TX | HAL_I3C_STALL_RX \
                                | HAL_I3C_STALL_I2C_ACK | HAL_I3C_STALL_I2C_TX | HAL_I3C_STALL_I2C_RX) /*!< All */
#define HAL_I3C_STALL_NONE     0UL                   /*!< None */
/**
  * @}
  */

/** @defgroup I3C_PAYLOAD_BIT_DEFINITION PAYLOAD BIT DEFINITION
  * @{
  */

/* Private define for CCC command */
#define HAL_I3C_BROADCAST_RSTDAA     LL_I3C_BROADCAST_RSTDAA     /*!< Bit definition to manage RSTDAA */
#define HAL_I3C_BROADCAST_ENTDAA     LL_I3C_BROADCAST_ENTDAA     /*!< Bit definition to manage ENTDAA */

/* Private define to split ENTDAA payload */
#define HAL_I3C_BCR_IN_PAYLOAD_SHIFT LL_I3C_BCR_IN_PAYLOAD_SHIFT /*!< BCR Position can be used with ENTDAA payload */
#define HAL_I3C_DCR_IN_PAYLOAD_SHIFT LL_I3C_DCR_IN_PAYLOAD_SHIFT /*!< DCR Position can be used with ENTDAA payload */
#define HAL_I3C_PID_IN_PAYLOAD_MASK  LL_I3C_PID_IN_PAYLOAD_MASK  /*!< Mask can be combined with ENTDAA payload */

/* Private define to split PID */
/* Bits[47:33]: MIPI Manufacturer ID */
#define HAL_I3C_MIPIMID_PID_SHIFT    LL_I3C_MIPIMID_PID_SHIFT    /*!< MIPIMID Position can be used with PID */
#define HAL_I3C_MIPIMID_PID_MASK     LL_I3C_MIPIMID_PID_MASK     /*!< Mask can be combined with PID */

/* Bit[32]: Provisioned ID Type Selector */
#define HAL_I3C_IDTSEL_PID_SHIFT     LL_I3C_IDTSEL_PID_SHIFT     /*!< IDTSEL Position can be used with PID */
#define HAL_I3C_IDTSEL_PID_MASK      LL_I3C_IDTSEL_PID_MASK      /*!< Mask can be combined with PID */

/* Bits[31:16]: Part ID */
#define HAL_I3C_PART_ID_PID_SHIFT    LL_I3C_PART_ID_PID_SHIFT    /*!< Part ID Position can be used with PID */
#define HAL_I3C_PART_ID_PID_MASK     LL_I3C_PART_ID_PID_MASK     /*!< Mask can be combined with PID */

/* Bits[15:12]: MIPI Instance ID */
#define HAL_I3C_MIPIID_PID_SHIFT     LL_I3C_MIPIID_PID_SHIFT     /*!< MIPI Instance ID Position can be used with PID */
#define HAL_I3C_MIPIID_PID_MASK      LL_I3C_MIPIID_PID_MASK      /*!< Mask can be combined with PID */

/* MIPI BCR Bits */
#define HAL_LL_I3C_BCR_BCR_POS       LL_I3C_BCR_BCR_POS          /*!< Bus Characteristics */
#define HAL_I3C_BCR_BCR_MSK          LL_I3C_BCR_BCR_MSK          /*!< 0x000000FF */
#define HAL_I3C_BCR_BCR0_POS         LL_I3C_BCR_BCR0_POS         /*!< Max Data Speed Limitation */
#define HAL_I3C_BCR_BCR0_MSK         LL_I3C_BCR_BCR0_MSK         /*!< 0x00000001 */
#define HAL_I3C_BCR_BCR1_POS         LL_I3C_BCR_BCR1_POS         /*!< IBI Request capable */
#define HAL_I3C_BCR_BCR1_MSK         LL_I3C_BCR_BCR1_MSK         /*!< 0x00000002 */
#define HAL_I3C_BCR_BCR2_POS         LL_I3C_BCR_BCR2_POS         /*!< IBI Payload additional Mandatory Data Byte */
#define HAL_I3C_BCR_BCR2_MSK         LL_I3C_BCR_BCR2_MSK         /*!< 0x00000004 */
#define HAL_I3C_BCR_BCR3_POS         LL_I3C_BCR_BCR3_POS         /*!< Offline capable */
#define HAL_I3C_BCR_BCR3_MSK         LL_I3C_BCR_BCR3_MSK         /*!< 0x00000008 */
#define HAL_I3C_BCR_BCR4_POS         LL_I3C_BCR_BCR4_POS         /*!< Virtual target support */
#define HAL_I3C_BCR_BCR4_MSK         LL_I3C_BCR_BCR4_MSK         /*!< 0x00000010 */
#define HAL_I3C_BCR_BCR5_POS         LL_I3C_BCR_BCR5_POS         /*!< Advanced capabilities */
#define HAL_I3C_BCR_BCR5_MSK         LL_I3C_BCR_BCR5_MSK         /*!< 0x00000020 */
#define HAL_I3C_BCR_BCR6_POS         LL_I3C_BCR_BCR6_POS         /*!< Device role shared during Dyn Addr Assignment */
#define HAL_I3C_BCR_BCR6_MSK         LL_I3C_BCR_BCR6_MSK         /*!< 0x00000040 */
/**
  * @}
  */

/**
  * @}
  */

/* Exported types ----------------------------------------------------------------------------------------------------*/
/** @defgroup I3C_Exported_Types HAL I3C Types
  * @{
  */

/**
  * @brief    HAL I3C functional mode
  */
typedef enum
{
  HAL_I3C_MODE_NONE = 0U,  /*!< No I3C communication on going */
  HAL_I3C_MODE_CTRL = 1U,  /*!< I3C communication is in controller Mode */
  HAL_I3C_MODE_TGT  = 2U   /*!< I3C communication is in target Mode */
} hal_i3c_mode_t;


/**
  * @brief    HAL I3C functional mode
  */
typedef enum
{
  HAL_I3C_LISTEN_DISABLED = 0U, /*!< Listen mode disabled */
  HAL_I3C_LISTEN_ENABLED = 1U,  /*!< Listen mode enabled */
} hal_i3c_listen_mode_t;

/**
  * @brief    I3C State structure definition
  */
typedef enum
{
  HAL_I3C_STATE_RESET    = (0UL),        /*!< Not yet Initialized */
  HAL_I3C_STATE_INIT     = (1UL << 31),  /*!< I3C is initialized but not yet configured */
  HAL_I3C_STATE_IDLE     = (1UL << 30),  /*!< I3C initialized and a global config applied */
  HAL_I3C_STATE_TX       = (1UL << 29),  /*!< Data transmission process is ongoing */
  HAL_I3C_STATE_RX       = (1UL << 28),  /*!< Data reception process is ongoing */
  HAL_I3C_STATE_TX_RX    = (1UL << 27),  /*!< Data multiple Transfer process is ongoing */
  HAL_I3C_STATE_DAA      = (1UL << 26),  /*!< Dynamic address assignment process is ongoing */
  HAL_I3C_STATE_TGT_REQ  = (1UL << 25),  /*!< Target request process is ongoing */
  HAL_I3C_STATE_ABORT    = (1UL << 24)   /*!< Abort user request ongoing */
} hal_i3c_state_t;

/** @defgroup I3C_CTRL_NOTIFICATION I3C notification id in controller mode
  * @{
  */
#define HAL_I3C_CTRL_NOTIFICATION_IBI  LL_I3C_IER_IBIIE    /*!< Receive IBI */
#define HAL_I3C_CTRL_NOTIFICATION_CR   LL_I3C_IER_CRIE     /*!< Controller-Role request */
#define HAL_I3C_CTRL_NOTIFICATION_HJ   LL_I3C_IER_HJIE     /*!< Hot-join */
#define HAL_I3C_CTRL_NOTIFICATION_ALL (LL_I3C_IER_IBIIE | LL_I3C_IER_CRIE | LL_I3C_IER_HJIE) /*!< All notif */
/**
  * @}
  */

/** @defgroup I3C_TGT_NOTIFICATION I3C notification id in target mode
  * @{
  */
#define HAL_I3C_TGT_NOTIFICATION_GETACCCR   LL_I3C_IER_CRUPDIE  /*!< Controller-Role hand-off, direct GETACCR CCC */
#define HAL_I3C_TGT_NOTIFICATION_IBIEND     LL_I3C_IER_IBIENDIE /*!< IBI end process */
#define HAL_I3C_TGT_NOTIFICATION_DAU        LL_I3C_IER_DAUPDIE  /*!< Dynamic Address Update: ENTDAA, RSTDAA or SETNEWDA.
        To discrimate RSTDAA from other CCC, call HAL_I3C_GetCCCInfo() and check the field dynamic_addr_valid of 
        hal_i3c_ccc_info_t structure */
#define HAL_I3C_TGT_NOTIFICATION_GET_X      LL_I3C_IER_GETIE    /*!< Any direct GETxxx CCC */
#define HAL_I3C_TGT_NOTIFICATION_GET_STATUS LL_I3C_IER_STAIE    /*!< Get status command, direct GETstatus CCC */
#define HAL_I3C_TGT_NOTIFICATION_SETMWL     LL_I3C_IER_MWLUPDIE /*!< Max write length update, direct SETMWL CCC */
#define HAL_I3C_TGT_NOTIFICATION_SETMRL     LL_I3C_IER_MRLUPDIE /*!< Max read length update, direct SETMRL CCC */
#define HAL_I3C_TGT_NOTIFICATION_RSTACT     LL_I3C_IER_RSTIE    /*!< Reset pattern,  broadcast or direct RSTACT CCC */
#define HAL_I3C_TGT_NOTIFICATION_ENTAS_X    LL_I3C_IER_ASUPDIE  /*!< Activity state update, direct or broadcast ENTASx*/
#define HAL_I3C_TGT_NOTIFICATION_ENEC_DISEC LL_I3C_IER_INTUPDIE /*!< Receive a direct or broadcast ENEC/DISEC CCC */
#define HAL_I3C_TGT_NOTIFICATION_WKP        LL_I3C_IER_WKPIE    /*!< Wakeup */
#define HAL_I3C_TGT_NOTIFICATION_DEFTGTS    (LL_I3C_IER_DEFIE | LL_I3C_IER_RXFNEIE) /*!< Broadcast  DEFTGTS CCC */
#define HAL_I3C_TGT_NOTIFICATION_DEFGRPA    (LL_I3C_IER_GRPIE | LL_I3C_IER_RXFNEIE) /*!< Group addressing, broadcast
                                                                                         DEFGRPA CCC */
#define HAL_I3C_TGT_NOTIFICATION_ALL  ( \
                                        HAL_I3C_TGT_NOTIFICATION_GETACCCR   | \
                                        HAL_I3C_TGT_NOTIFICATION_IBIEND     | \
                                        HAL_I3C_TGT_NOTIFICATION_DAU        | \
                                        HAL_I3C_TGT_NOTIFICATION_GET_X      | \
                                        HAL_I3C_TGT_NOTIFICATION_GET_STATUS | \
                                        HAL_I3C_TGT_NOTIFICATION_SETMWL     | \
                                        HAL_I3C_TGT_NOTIFICATION_SETMRL     | \
                                        HAL_I3C_TGT_NOTIFICATION_RSTACT     | \
                                        HAL_I3C_TGT_NOTIFICATION_ENTAS_X    | \
                                        HAL_I3C_TGT_NOTIFICATION_ENEC_DISEC | \
                                        HAL_I3C_TGT_NOTIFICATION_WKP        | \
                                        HAL_I3C_TGT_NOTIFICATION_DEFTGTS    | \
                                        HAL_I3C_TGT_NOTIFICATION_DEFGRPA      ) /*!< All notifications */
/**
  * @}
  */

#define HAL_I3C_DEFINE_BYTE (0x00000001U) /*!< Private hal define used to construct enum @ref hal_i3c_xfer_mode_t */

/**
  * @brief  I3C transfer mode.
  *  HAL I3C mode value coding follow below described bitmap:
  *  b31
  *       0: message end type restart
  *       1: message end type stop (I3C_CR_MEND / LL_I3C_GENERATE_STOP)
  *  b30-b29-b28-b27
  *       0010: Private I3C message   (I3C_CR_MTYPE_1 / LL_I3C_CONTROLLER_MTYPE_PRIVATE)
  *       0100: Private I2C message   (I3C_CR_MTYPE_2 / LL_I3C_CONTROLLER_MTYPE_LEGACY_I2C)
  *       0011: CCC direct message    (I3C_CR_MTYPE_1 | I3C_CR_MTYPE_0 / LL_I3C_CONTROLLER_MTYPE_DIRECT)
  *       0110: CCC broadcast message (I3C_CR_MTYPE_2 | I3C_CR_MTYPE_1 / LL_I3C_CONTROLLER_MTYPE_CCC)
  *  b2
  *       1: message without arbitration header (I3C_CFGR_NOARBH)
  *       0: message with arbitration header
  *  b0
  *       0: message without defining byte
  *       1: message with defining byte (HAL_I3C_DEFINE_BYTE)
  *
  *  other bits (not used).
  */
typedef enum
{
  HAL_I3C_PRIVATE_WITH_ARB_RESTART = (LL_I3C_GENERATE_STOP), /*!<  Restart between each I3C private message then Stop
  request for last message. */

  HAL_I3C_PRIVATE_WITH_ARB_STOP = (LL_I3C_GENERATE_STOP | LL_I3C_CONTROLLER_MTYPE_PRIVATE), /*!<  Stop between each I3C
  private message. Each message start with an arbitration header after start bit condition. */

  HAL_I3C_PRIVATE_WITHOUT_ARB_RESTART = (LL_I3C_CONTROLLER_MTYPE_PRIVATE | I3C_CFGR_NOARBH), /*!<  Restart between each
  I3C message then stop request for last message. Each message start with target address after start bit condition. */

  HAL_I3C_PRIVATE_WITHOUT_ARB_STOP = (LL_I3C_GENERATE_STOP | LL_I3C_CONTROLLER_MTYPE_PRIVATE | I3C_CFGR_NOARBH), /*!<
  Stop between each I3C private message. Each message start with target address after start bit condition. */

  HAL_I2C_PRIVATE_WITH_ARB_RESTART = (LL_I3C_CONTROLLER_MTYPE_LEGACY_I2C), /*!<  Restart between each I2C private
  message then stop request for last message. Each message start with an arbitration header after start bit condition.*/

  HAL_I2C_PRIVATE_WITH_ARB_STOP = (LL_I3C_GENERATE_STOP | LL_I3C_CONTROLLER_MTYPE_LEGACY_I2C), /*!<  Stop between each
  I2C private message. Each message start with an arbitration header after start bit condition. */

  HAL_I2C_PRIVATE_WITHOUT_ARB_RESTART = (LL_I3C_CONTROLLER_MTYPE_LEGACY_I2C | I3C_CFGR_NOARBH), /*!<  Restart between
  each I2C message then stop request for last message. Each message start with target address after start bit condition.
  */

  HAL_I2C_PRIVATE_WITHOUT_ARB_STOP = (LL_I3C_GENERATE_STOP | LL_I3C_CONTROLLER_MTYPE_LEGACY_I2C | I3C_CFGR_NOARBH), /*!<
  Stop between each I2C private message. Each message start with target address after start bit condition. */

  HAL_I3C_CCC_DIRECT_WITH_DEFBYTE_RESTART = (LL_I3C_CONTROLLER_MTYPE_DIRECT | HAL_I3C_DEFINE_BYTE), /*!< Restart
  between each direct command then stop request for last command. Each command has an associated defining byte */

  HAL_I3C_CCC_DIRECT_WITH_DEFBYTE_STOP = (LL_I3C_GENERATE_STOP | LL_I3C_CONTROLLER_MTYPE_DIRECT  | HAL_I3C_DEFINE_BYTE),
  /*!< Stop between each direct command.  Each command has an associated defining byte. */

  HAL_I3C_CCC_DIRECT_WITHOUT_DEFBYTE_RESTART = (LL_I3C_CONTROLLER_MTYPE_DIRECT), /*!< Restart between each direct
  command then stop request for last command. Each command does not have an associated defining byte. */

  HAL_I3C_CCC_DIRECT_WITHOUT_DEFBYTE_STOP = (LL_I3C_GENERATE_STOP | LL_I3C_CONTROLLER_MTYPE_DIRECT), /*!< Stop
  between each direct command. Each command does not have an associated defining byte. */

  HAL_I3C_CCC_BROADCAST_WITH_DEFBYTE_RESTART = (LL_I3C_CONTROLLER_MTYPE_CCC | HAL_I3C_DEFINE_BYTE), /*!< Restart between
  each broadcast command then stop request for last command. Each command has an associated defining byte. */

  HAL_I3C_CCC_BROADCAST_WITH_DEFBYTE_STOP = (LL_I3C_GENERATE_STOP | LL_I3C_CONTROLLER_MTYPE_CCC | HAL_I3C_DEFINE_BYTE),
  /*!< Stop between each broadcast command. Each command has an associated defining byte. */

  HAL_I3C_CCC_BROADCAST_WITHOUT_DEFBYTE_RESTART = (LL_I3C_CONTROLLER_MTYPE_CCC), /*!< Restart between each broadcast
  command then stop request for last command. Each command does not have an associated defining byte. */

  HAL_I3C_CCC_BROADCAST_WITHOUT_DEFBYTE_STOP = (LL_I3C_GENERATE_STOP | LL_I3C_CONTROLLER_MTYPE_CCC) /*!< Stop between
  each broadcast command. Each command does not have an associated defining byte. */
} hal_i3c_xfer_mode_t;

/**
  * @brief    I3C dynamic address options definition
  */
typedef enum
{
  HAL_I3C_DYN_ADDR_RSTDAA_THEN_ENTDAA = 1U, /*!< Initiate a RSTDAA before a ENTDAA procedure */
  HAL_I3C_DYN_ADDR_ONLY_ENTDAA        = 2U  /*!< Initiate a ENTDAA without RSTDAA */
} hal_i3c_dyn_addr_opt_t;

/**
  * @brief    I3C pattern configuration
  */
typedef enum
{
  HAL_I3C_PATTERN_TGT_RESET = 1U, /*!< Target reset pattern */
  HAL_I3C_PATTERN_HDR_EXIT  = 2U  /*!< HDR exit pattern */
} hal_i3c_pattern_opt_t;

/**
  * @brief    I3C transfer direction
  */
typedef enum
{
  HAL_I3C_DIRECTION_WRITE = LL_I3C_DIRECTION_WRITE, /*!< Write transfer */
  HAL_I3C_DIRECTION_READ  = LL_I3C_DIRECTION_READ,  /*!< Read transfer */
} hal_i3c_direction_t;

/**
  * @brief    I3C Rx FIFO threshold
  */
typedef enum
{
  HAL_I3C_RX_FIFO_THRESHOLD_1_4 = LL_I3C_RXFIFO_THRESHOLD_1_4, /*!< Rx FIFO threshold is 1 byte */
  HAL_I3C_RX_FIFO_THRESHOLD_4_4 = LL_I3C_RXFIFO_THRESHOLD_4_4  /*!< Rx FIFO threshold is 4 bytes */
} hal_i3c_rx_fifo_threshold_t;

/**
  * @brief    I3C Tx FIFO threshold
  */
typedef enum
{
  HAL_I3C_TX_FIFO_THRESHOLD_1_4 = LL_I3C_TXFIFO_THRESHOLD_1_4, /*!< Tx Fifo threshold is 1 byte */
  HAL_I3C_TX_FIFO_THRESHOLD_4_4 = LL_I3C_TXFIFO_THRESHOLD_4_4  /*!< Tx Fifo threshold is 4 bytes */
} hal_i3c_tx_fifo_threshold_t;

/**
  * @brief    I3C Tx FIFO threshold
  */
typedef enum
{
  HAL_I3C_CTRL_FIFO_NONE         = LL_I3C_CTRL_FIFO_NONE,         /*!< Control and status FIFO disable */
  HAL_I3C_CTRL_FIFO_CONTROL_ONLY = LL_I3C_CTRL_FIFO_CONTROL_ONLY, /*!< Control FIFO enable */
  HAL_I3C_CTRL_FIFO_STATUS_ONLY  = LL_I3C_CTRL_FIFO_STATUS_ONLY,  /*!< Status FIFO enable */
  HAL_I3C_CTRL_FIFO_ALL          = LL_I3C_CTRL_FIFO_ALL           /*!< Control and status FIFO enable */
} hal_i3c_ctrl_fifo_t;

/**
  * @brief    I3C Control FIFO status
  */
typedef enum
{
  HAL_I3C_CONTROL_FIFO_DISABLED = 0U, /*!< Control FIFO mode is disabled */
  HAL_I3C_CONTROL_FIFO_ENABLED  = 1U  /*!< Control FIFO mode is enabled */
} hal_i3c_control_fifo_status_t;

/**
  * @brief    I3C status-FIFO status
  */
typedef enum
{
  HAL_I3C_STATUS_FIFO_DISABLED = 0U, /*!< Status FIFO mode is disabled */
  HAL_I3C_STATUS_FIFO_ENABLED  = 1U  /*!< Status FIFO mode is enabled */
} hal_i3c_status_fifo_status_t;

/**
  * @brief    I3C Payload Size
  */
typedef enum
{
  HAL_I3C_PAYLOAD_EMPTY   = LL_I3C_PAYLOAD_EMPTY,   /*!< Empty payload, no additional data after IBI acknowledge */
  HAL_I3C_PAYLOAD_1_BYTE  = LL_I3C_PAYLOAD_1_BYTE,  /*!< 1 additional data byte after IBI acknowledge */
  HAL_I3C_PAYLOAD_2_BYTES = LL_I3C_PAYLOAD_2_BYTES, /*!< 2 additional data bytes after IBI acknowledge */
  HAL_I3C_PAYLOAD_3_BYTES = LL_I3C_PAYLOAD_3_BYTES, /*!< 3 additional data bytes after IBI acknowledge */
  HAL_I3C_PAYLOAD_4_BYTES = LL_I3C_PAYLOAD_4_BYTES  /*!< 4 additional data bytes after IBI acknowledge */
} hal_i3c_payload_size_t;

/**
  * @brief    I3C activity state
  */
typedef enum
{
  HAL_I3C_ACTIVITY_STATE_0 = LL_I3C_BUS_ACTIVITY_STATE_0, /*!< Activity state 0 */
  HAL_I3C_ACTIVITY_STATE_1 = LL_I3C_BUS_ACTIVITY_STATE_1, /*!< Activity state 1 */
  HAL_I3C_ACTIVITY_STATE_2 = LL_I3C_BUS_ACTIVITY_STATE_2, /*!< Activity state 2 */
  HAL_I3C_ACTIVITY_STATE_3 = LL_I3C_BUS_ACTIVITY_STATE_3  /*!< Activity state 3 */
} hal_i3c_activity_state_t;

/**
  * @brief    I3C reset action
  */
typedef enum
{
  HAL_I3C_RESET_ACTION_NONE    = LL_I3C_RESET_ACTION_NONE,    /*!< No reset action required */
  HAL_I3C_RESET_ACTION_PARTIAL = LL_I3C_RESET_ACTION_PARTIAL, /*!< Reset of some internal registers of the peripheral */
  HAL_I3C_RESET_ACTION_FULL    = LL_I3C_RESET_ACTION_FULL     /*!< Reset all internal registers of the peripheral */
} hal_i3c_reset_action_t;

/**
  * @brief    I3C handoff activity state
  */
typedef enum
{
  HAL_I3C_HANDOFF_ACTIVITY_STATE_0 = LL_I3C_HANDOFF_ACTIVITY_STATE_0,  /*!< Activity state 0 after handoff */
  HAL_I3C_HANDOFF_ACTIVITY_STATE_1 = LL_I3C_HANDOFF_ACTIVITY_STATE_1,  /*!< Activity state 1 after handoff */
  HAL_I3C_HANDOFF_ACTIVITY_STATE_2 = LL_I3C_HANDOFF_ACTIVITY_STATE_2,  /*!< Activity state 2 after handoff */
  HAL_I3C_HANDOFF_ACTIVITY_STATE_3 = LL_I3C_HANDOFF_ACTIVITY_STATE_3   /*!< Activity state 3 after handoff */
} hal_i3c_handoff_activity_state_t;

/**
  * @brief    I3C turnaround time TSCO
  */
typedef enum
{
  HAL_I3C_TURNAROUND_TIME_TSCO_LESS_12NS    = LL_I3C_TURNAROUND_TIME_TSCO_LESS_12NS,   /*!< clock-to-data turnaround
                                                                                            time tSCO <= 12ns */
  HAL_I3C_TURNAROUND_TIME_TSCO_GREATER_12NS = LL_I3C_TURNAROUND_TIME_TSCO_GREATER_12NS /*!< clock-to-data turnaround
                                                                                            time tSCO > 12ns  */
} hal_i3c_turnaround_time_tSCO_t;


/**
  * @brief    I3C controller capability status
  */
typedef enum
{
  HAL_I3C_CTRL_CAPABILITY_DISABLED = 0U, /*!< Controller capability is disabled */
  HAL_I3C_CTRL_CAPABILITY_ENABLED  = 1U  /*!< Controller capability is enabled */
} hal_i3c_ctrl_capability_status_t;

/**
  * @brief    I3C IBI payload status
  */
typedef enum
{
  HAL_I3C_IBI_PAYLOAD_DISABLED = 0U, /*!< Sending data payload after an accepted IBI is disabled */
  HAL_I3C_IBI_PAYLOAD_ENABLED  = 1U  /*!< Sending data payload after an accepted IBI is enabled */
} hal_i3c_ibi_payload_status_t;

/**
  * @brief    I3C Max data speed limitation status
  */
typedef enum
{
  HAL_I3C_MAX_SPEED_LIMITATION_DISABLED = 0U, /*!< Max data speed limitation is disabled */
  HAL_I3C_MAX_SPEED_LIMITATION_ENABLED  = 1U  /*!< Max data speed limitation is enabled */
} hal_i3c_max_speed_limit_status_t;

/**
  * @brief    I3C Controller-Role status
  */
typedef enum
{
  HAL_I3C_CTRL_ROLE_DISABLED = 0U, /*!< Controller-Role is disabled */
  HAL_I3C_CTRL_ROLE_ENABLED  = 1U  /*!< Controller-Role is enabled */
} hal_i3c_ctrl_role_status_t;

/**
  * @brief    I3C hand off delay status
  */
typedef enum
{
  HAL_I3C_HAND_OFF_DELAY_DISABLED = 0U, /*!< Hand off delay is disabled */
  HAL_I3C_HAND_OFF_DELAY_ENABLED  = 1U  /*!< Hand off delay is enabled */
} hal_i3c_hand_off_delay_status_t;

/**
  * @brief    I3C Group address capability status
  */
typedef enum
{
  HAL_I3C_GRP_ADDR_CAPABILITY_DISABLED = 0U, /*!< Group address capability is disabled */
  HAL_I3C_GRP_ADDR_CAPABILITY_ENABLED  = 1U  /*!< Group address capability is enabled */
} hal_i3c_grp_addr_capability_status_t;

/**
  * @brief    I3C IBI request status
  */
typedef enum
{
  HAL_I3C_IBI_REQ_DISABLED = 0U, /*!< IBI request is disabled */
  HAL_I3C_IBI_REQ_ENABLED  = 1U  /*!< IBI request is enabled */
} hal_i3c_ibi_req_status_t;

/**
  * @brief    I3C offline capable status
  */
typedef enum
{
  HAL_I3C_OFFLINE_CAPABLE_DISABLED = 0U, /*!< Offline capable is disabled */
  HAL_I3C_OFFLINE_CAPABLE_ENABLED  = 1U  /*!< Offline capable is enabled */
} hal_i3c_offline_capable_status_t;

/**
  * @brief    I3C virtual target support status
  */
typedef enum
{
  HAL_I3C_VIRTUAL_TGT_DISABLED = 0U, /*!< Virtual target support is disabled */
  HAL_I3C_VIRTUAL_TGT_ENABLED  = 1U  /*!< Virtual target support is enabled */
} hal_i3c_virtual_tgt_status_t;

/**
  * @brief    I3C advanced capabilities status
  */
typedef enum
{
  HAL_I3C_ADV_CAPABILITIES_DISABLED = 0U, /*!< Advanced capabilities is disabled */
  HAL_I3C_ADV_CAPABILITIES_ENABLED  = 1U  /*!< Advanced capabilities is enabled */
} hal_i3c_adv_capabilities_status_t;

/**
  * @brief    I3C controller stop transfer status
  */
typedef enum
{
  HAL_I3C_STOP_XFER_DISABLED = 0U, /*!< Controller stop transfer is disabled */
  HAL_I3C_STOP_XFER_ENABLED  = 1U  /*!< Controller stop transfer is enabled */
} hal_i3c_stop_xfer_status_t;

/**
  * @brief    I3C GETMXDS format
  */
typedef enum
{
  HAL_I3C_GETMXDS_FORMAT_1     = LL_I3C_GETMXDS_FORMAT_1,     /*!< GETMXDS CCC Format 1 is used, no MaxRdTurn
                                                                   field in response */
  HAL_I3C_GETMXDS_FORMAT_2_LSB = LL_I3C_GETMXDS_FORMAT_2_LSB, /*!< GETMXDS CCC Format 2 is used, MaxRdTurn field
                                                                   in response, LSB = RDTURN[7:0] */
  HAL_I3C_GETMXDS_FORMAT_2_MID = LL_I3C_GETMXDS_FORMAT_2_MID, /*!< GETMXDS CCC Format 2 is used, MaxRdTurn field
                                                                   in response, Middle byte = RDTURN[7:0] */
  HAL_I3C_GETMXDS_FORMAT_2_MSB = LL_I3C_GETMXDS_FORMAT_2_MSB  /*!< GETMXDS CCC Format 2 is used, MaxRdTurn field
                                                                    in response, MSB = RDTURN[7:0] */
} hal_i3c_GETMXDS_format_t;

/**
  * @brief    I3C Hot-Join status
  */
typedef enum
{
  HAL_I3C_HOT_JOIN_DISABLED = 0U, /*!< Hot-Join is disabled */
  HAL_I3C_HOT_JOIN_ENABLED  = 1U  /*!< Hot-Join is enabled */
} hal_i3c_hot_join_status_t;

/**
  * @brief    I3C controller SDA high keeper status
  */
typedef enum
{
  HAL_I3C_HIGH_KEEPER_SDA_DISABLED = 0U, /*!< The controller SDA high keeper is disabled */
  HAL_I3C_HIGH_KEEPER_SDA_ENABLED  = 1U  /*!< The controller SDA high keeper is enabled */
} hal_i3c_high_keeper_sda_status_t;

/**
  * @brief    I3C Reset Pattern status
  */
typedef enum
{
  HAL_I3C_RESET_PATTERN_DISABLED = 0U, /*!< Standard STOP condition emitted at the end of a frame */
  HAL_I3C_RESET_PATTERN_ENABLED  = 1U  /*!< Reset pattern is inserted before the STOP condition of any emitted frame */
} hal_i3c_reset_pattern_status_t;

/**
  * @brief    I3C pending read mandatory data bytes status
  */
typedef enum
{
  HAL_I3C_PENDING_READ_MDB_DISABLED = LL_I3C_MDB_NO_PENDING_READ_NOTIFICATION, /*!< Pending read mandatory data bytes
                                                                                    is disabled */
  HAL_I3C_PENDING_READ_MDB_ENABLED  = LL_I3C_MDB_PENDING_READ_NOTIFICATION     /*!< Pending read mandatory data bytes
                                                                                    is enabled */
} hal_i3c_tgt_read_mdb_status_t;

/**
  * @brief    I3C hal_i3c_ccc_desc_t Structure definition
  */
typedef struct
{
  uint8_t  tgt_addr;              /*!< Dynamic or static target address */
  uint8_t  ccc;                   /*!< CCC value code */
  uint32_t data_size_byte;        /*!< The size of the associated data (size of the defining byte included) */
  hal_i3c_direction_t direction;  /*!< CCC read or write direction message. Write Only with broadcast */
} hal_i3c_ccc_desc_t;

/**
  * @brief    I3C hal_bcr_t Structure definition
  */
typedef struct
{
  hal_i3c_max_speed_limit_status_t   max_data_speed_limitation;  /*!< Max data speed limitation */
  hal_i3c_ibi_req_status_t           ibi_request_capable;        /*!< IBI request capable */
  hal_i3c_ibi_payload_status_t       ibi_payload;                /*!< IBI payload data */
  hal_i3c_offline_capable_status_t   offline_capable;            /*!< Offline capable */
  hal_i3c_virtual_tgt_status_t       virtual_target_support;     /*!< Virtual target support */
  hal_i3c_adv_capabilities_status_t  advanced_capabilities;      /*!< Advanced capabilities */
  hal_i3c_ctrl_role_status_t         device_role;                /*!< Device role */
} hal_i3c_bcr_t;

/**
  * @brief    I3C hal_pid_t structure definition
  */
typedef struct
{
  uint16_t  mipi_manuf_id; /*!< MIPI manufacturer ID */
  uint8_t   id_type_sel;   /*!< Provisioned ID type selector */
  uint16_t  part_id;       /*!< Part ID device vendor to define */
  uint8_t   mipi_id;       /*!< Instance ID */
} hal_i3c_pid_t;

/**
  * @brief    I3C hal_i3c_private_desc_t structure definition
  */
typedef struct
{
  uint8_t              tgt_addr;        /*!< Dynamic or static target address */
  uint32_t             data_size_byte;  /*!< Size of data to transmit or receive */
  hal_i3c_direction_t  direction;       /*!< Read and/or write message */
} hal_i3c_private_desc_t;

/**
  * @brief    I3C hal_i3c_xfer_ctx_t structure definition.
  */
typedef struct
{
  uint32_t *p_ctrl_data;    /*!< Control buffer pointer */
  uint32_t ctrl_size_word;  /*!< Control buffer size in word. See @ref HAL_I3C_GET_CTRL_BUFFER_SIZE_WORD */
  const uint8_t *p_tx_data; /*!< Cumulated tx buffer pointer */
  uint32_t tx_size_byte;    /*!< Cumulated tx buffer size in byte. It must be set to OU if no tx data */
  uint8_t *p_rx_data;       /*!< Cumulated rx buffer pointer */
  uint32_t rx_size_byte;    /*!< Cumulated rx buffer size in byte. It must be set to OU if no rx data */
  hal_i3c_xfer_mode_t xfer_mode; /*!< One of HAL_I3C_PRIVATE_xxx or one of HAL_I3C_CCC_xxx */
#if defined(USE_ASSERT_DBG_PARAM) || (defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1))
  uint32_t nb_tx_frame;     /*!< Store tx frame number for debug purpose */
#endif /* (USE_ASSERT_DBG_PARAM) | (USE_HAL_CHECK_PARAM) */
} hal_i3c_xfer_ctx_t;

/**
  * @brief    HAL I3C global configuration I3C controller
  */
typedef struct
{
  uint32_t  timing_reg0;  /*!< I3C_TIMINGR0 register value calculated by referring to I3C initialization section
                               in Reference Manual. This value is directly calculated by CubeMx2. A calculation helper
                               is also available in the package, please look at stm32_utils_i3c.c/.h */

  uint32_t  timing_reg1;  /*!< I3C_TIMINGR1 register value calculated by referring to I3C initialization section
                               in Reference Manual. This value is directly calculated by CubeMx2. A calculation helper
                               is also available in the package, please look at stm32_utils_i3c.c/.h */
} hal_i3c_ctrl_config_t;

/**
  * @brief    HAL I3C global configuration I3C target
  */
typedef struct
{
  uint32_t timing_reg1;   /*!< I3C_TIMINGR1 register value calculated by referring to I3C initialization section
                               in Reference Manual. This value is directly calculated by CubeMx2. A calculation helper
                               is also available in the package, please look at stm32_utils_i3c.c/.h */
} hal_i3c_tgt_config_t;

/**
  * @brief    HAL I3C payload ENTDAA configuration structure definition
  */
typedef struct
{
  uint8_t identifier;      /*!< Target characteristic ID (MIPI named reference DCR). This parameter must be a number
                                between Min_Data=0x00 and Max_Data=0xFF*/

  uint8_t mipi_identifier; /*!< Bits [12-15] of the 48-provisioned ID (MIPI named reference PID),
                                other 48-provisioned  ID are hardcoded. This parameter must be a number
                                between Min_Data=0x00 and Max_Data=0x0F */

  hal_i3c_ctrl_capability_status_t  ctrl_capability;      /*!< Target controller capability (for BCR) */
  hal_i3c_ibi_payload_status_t      ibi_payload;          /*!< Sending data payload after an accepted IBI (for BCR) */
  hal_i3c_max_speed_limit_status_t  max_speed_limitation; /*!< Target max data speed limitation (for BCR) */
} hal_i3c_tgt_config_payload_entdaa_t;

/**
  * @brief    HAL I3C controller FIFO configuration structure definition
  */
typedef struct
{
  hal_i3c_rx_fifo_threshold_t  rx_fifo_threshold; /*!< I3C Rx FIFO threshold level */
  hal_i3c_tx_fifo_threshold_t  tx_fifo_threshold; /*!< I3C Tx FIFO threshold level */
  hal_i3c_ctrl_fifo_t          ctrl_fifo;         /*!< I3C control and status activation */
} hal_i3c_ctrl_fifo_config_t;

/**
  * @brief    HAL I3C target FIFO configuration structure definition
  */
typedef struct
{
  hal_i3c_rx_fifo_threshold_t  rx_fifo_threshold; /*!< I3C Rx FIFO threshold level */
  hal_i3c_tx_fifo_threshold_t  tx_fifo_threshold; /*!< I3C Tx FIFO threshold level */
} hal_i3c_tgt_fifo_config_t;

/**
  * @brief    HAL I3C in band interrupt configuration structure definition
  */
typedef struct
{
  hal_i3c_payload_size_t         ibi_payload_size_byte; /*!< I3C target payload data size */
  hal_i3c_tgt_read_mdb_status_t  pending_read_mdb;      /*!< Transmission of a mandatory data bytes indicating a pending
                                                             read notification for GETCAPR CCC command */
} hal_i3c_tgt_ibi_config_t;

/**
  * @brief    HAL I3C target max data size configuration structure definition
  */
typedef struct
{
  uint16_t  max_read_data_size_byte;  /*!< Numbers of data bytes that the target can read at maximum.
                                           This parameter must be a number between Min_Data=0x0 and Max_Data=0xFFFF */

  uint16_t  max_write_data_size_byte; /*!< Numbers of data bytes that the target can write at maximum.
                                           This parameter must be a number between Min_Data=0x0 and Max_Data=0xFFFF */
} hal_i3c_tgt_max_data_size_config_t;

/**
  * @brief    HAL I3C target GETMXDS configuration structure definition
  */
typedef struct
{
  hal_i3c_GETMXDS_format_t          GETMXDS_format;           /*!< GETMXDS CCC Format */
  hal_i3c_handoff_activity_state_t  ctrl_hand_off_activity;   /*!< I3C Target activity when becoming controller */
  hal_i3c_turnaround_time_tSCO_t    data_turnaround_duration; /*!< I3C target clock-to-data turnaround time */
  uint8_t max_read_turnaround;  /*!< Target maximum read turnaround byte. This parameter must be a number
                                     between Min_Data=0x00 and Max_Data=0xFF*/
} hal_i3c_tgt_getmxds_config_t;

/**
  * @brief    HAL I3C device configuration structure definition
  */
typedef struct
{
  uint8_t device_index;       /*!< Index value of the target device in the DEVRx register.
                                   This parameter must be a number between Min_Data=0 and Max_Data=3 */
  uint8_t tgt_dynamic_addr;   /*!< Dynamic address of the device.
                                   This parameter must be a number between Min_Data=0x00 and Max_Data=0x7F */
  hal_i3c_ibi_req_status_t         ibi_ack;            /*!< ACK when receiving an IBI from the device */
  hal_i3c_ibi_payload_status_t     ibi_payload;        /*!< Receive IBI payload after acknowledging an IBI  */
  hal_i3c_ctrl_capability_status_t ctrl_role_req_ack;  /*!< ACK when receiving a control request from the device */
  hal_i3c_stop_xfer_status_t       ctrl_stop_transfer; /*!< Stop transfer after receiving an IBI from the device */
} hal_i3c_ctrl_device_config_t;

/**
  * @brief    I3C ENTDAA payload structure definition
  */
typedef struct
{
  hal_i3c_bcr_t  bcr; /*!< Bus characteristics register */
  uint32_t       dcr; /*!< Device characteristics register */
  hal_i3c_pid_t  pid; /*!< Provisioned ID */
} hal_i3c_entdaa_payload_t;

/**
  * @brief    I3C CCC info structure definition
  */
typedef struct
{
  uint32_t dynamic_addr_valid;  /*!< I3C target dynamic address validity (updated during ENTDAA/RSTDAA/SETNEWDA CCC)
                                     This parameter=1U after an ENTDAA or a SETNEWDA
                                     This parameter=0U after a RSTDAA */

  uint32_t dynamic_addr;  /*!< I3C target dynamic address (updated during ENTDAA/RSTDAA/SETNEWDA CCC)
                               This parameter can be between Min_Data=0 and Max_Data=0x7F. */

  uint32_t max_write_length;  /*!< I3C target maximum write length (updated during SETMWL CCC)
                                   This parameter can be between Min_Data=0x0 and Max_Data=0xFFFFF */

  uint32_t max_read_length;  /*!< I3C target maximum read length (updated during SETMRL CCC)
                                  This parameter can be between Min_Data=0x0 and Max_Data=0xFFFFF */

  hal_i3c_reset_action_t reset_action;  /*!< I3C target reset action level (updated during RSTACT CCC) */

  hal_i3c_activity_state_t  activity_state;  /*!< I3C target activity state (updated during ENTASx CCC) */

  uint32_t hot_join_allowed;  /*!< I3C target Hot-Join (updated during ENEC/DISEC CCC)
                                   This parameter can be allowed=1U or not allowed=0U */

  uint32_t in_band_allowed;  /*!< I3C target in band interrupt (updated during ENEC/DISEC CCC)
                                  This parameter can be allowed=1U or not allowed=0U */

  uint32_t ctrl_role_allowed;  /*!< I3C target Controller-Role request (updated during ENEC/DISEC CCC)
                                    This parameter can be allowed=1U or not allowed=0U */

  uint32_t ibi_cr_tgt_addr;  /*!< I3C controller receive target address during IBI or Controller-Role request event
                                  This parameter can be between Min_Data=0 to Max_Data=0x3F */

  uint32_t ibi_tgt_nb_payload;  /*!< I3C controller get number of data payload after an IBI event
                                     This parameter can be between between Min_Data=0 to Max_Data=0x7 */

  uint32_t ibi_tgt_payload;     /*!< I3C controller receive IBI payload after an IBI event
                                     Content of register is filled in Little Endian :
                                      - Mean MSB correspond to last IBI data byte,
                                      - LSB correspond to first IBI data byte.
                                     This parameter can be between  Min_Data=0 to Max_Data=0xFFFFFFFF  */
} hal_i3c_ccc_info_t;

/**
  * @brief HAL I3C instance
  */
typedef enum
{
  HAL_I3C1 = I3C1_BASE, /*!< Peripheral instance I3C1 */
} hal_i3c_t;

typedef struct hal_i3c_handle_s hal_i3c_handle_t; /*!< I3C handle structure type */

#if defined(USE_HAL_I3C_REGISTER_CALLBACKS) && (USE_HAL_I3C_REGISTER_CALLBACKS == 1U)

/**
  * @brief pointer to an I3C callback function
  */
typedef  void (*hal_i3c_cb_t)(hal_i3c_handle_t *hi3c);

/**
  * @brief pointer to an I3C notification callback function
  */
typedef  void (*hal_i3c_notify_cb_t)(hal_i3c_handle_t *hi3c, uint32_t notify_id);

/**
  * @brief pointer to an I3C target hot-join callback function
  */
typedef  void (*hal_i3c_tgt_hot_join_cb_t)(hal_i3c_handle_t *hi3c, uint8_t dynamic_address);

/**
  * @brief pointer to a target request dynamic address I3C callback function
  */
typedef  void (*hal_i3c_req_dyn_addr_cb_t)(hal_i3c_handle_t *hi3c, uint64_t target_payload);

#endif /* USE_HAL_I3C_REGISTER_CALLBACKS */

/**
  * @brief    I3C handle structure definition
  */
struct hal_i3c_handle_s
{
  hal_i3c_t instance;  /*!< Peripheral instance */
  hal_i3c_mode_t mode;  /*!< Communication mode */
  hal_i3c_listen_mode_t listen; /*!< Listen mode */
  volatile hal_i3c_state_t global_state;  /*!< Communication state */

#if (defined(USE_HAL_I3C_GET_LAST_ERRORS) && (USE_HAL_I3C_GET_LAST_ERRORS == 1)) \
    || (defined(USE_HAL_I3C_DMA) && (USE_HAL_I3C_DMA == 1))
  volatile uint32_t last_error_codes;  /*!< Errors limited to the last process
                                            This parameter can be a combination of @ref I3C_ERROR_CODE_DEFINITION */
#endif /* USE_HAL_I3C_GET_LAST_ERRORS || USE_HAL_I3C_DMA */
  const uint32_t *p_ctrl_data; /*!< Data ctrl */
  const uint8_t *p_tx_data;    /*!< Data tx */
  uint8_t *p_rx_data;          /*!< Data rx */
  uint32_t ctrl_count;         /*!< Remaining ctrl to do */
  uint32_t data_size;          /*!< Data size (rx or tx)*/
  uint32_t tx_count;           /*!< Remaining data to transmit */
  uint32_t rx_count;           /*!< Remaining data to receive */
  hal_status_t(*xfer_isr)(hal_i3c_handle_t *hi3c, uint32_t itMasks); /*!< Transfer IRQ handler function pointer */
  void(*p_tx_func)(hal_i3c_handle_t *hi3c);  /*!< Transmit function pointer */
  void(*p_rx_func)(hal_i3c_handle_t *hi3c);  /*!< Receive function pointer */

#if defined(USE_HAL_I3C_DMA) && (USE_HAL_I3C_DMA == 1)
  hal_dma_handle_t *hdma_ctrl; /*!< Control DMA handle */
  hal_dma_handle_t *hdma_tx;   /*!< Tx DMA handle */
  hal_dma_handle_t *hdma_rx;   /*!< Rx DMA handle */
#endif /* USE_HAL_I3C_DMA */

#if defined(USE_HAL_I3C_USER_DATA) && (USE_HAL_I3C_USER_DATA == 1)
  const void *p_user_data;  /*!< User data pointer */
#endif /* USE_HAL_I3C_USER_DATA */

#if defined(USE_HAL_MUTEX) && (USE_HAL_MUTEX == 1)
  hal_os_semaphore_t semaphore;  /*!< OS semaphore */
#endif /* USE_HAL_MUTEX */

#if defined(USE_HAL_I3C_REGISTER_CALLBACKS) && (USE_HAL_I3C_REGISTER_CALLBACKS == 1U)
  hal_i3c_cb_t  p_ctrl_xfer_cplt_cb; /*!< Ctrl multiple direct CCC, I3C private or I2C transfer completed cb */
  hal_i3c_cb_t  p_ctrl_daa_cplt_cb; /*!< Ctrl Dynamic Address Assignment completed cb */
  hal_i3c_req_dyn_addr_cb_t  p_ctrl_tgt_req_dyn_addr_cb; /*!< Ctrl get tgt dynamic address request during DAA process */
  hal_i3c_cb_t  p_tgt_tx_cplt_cb; /*!< Tgt private data tx transfer completed cb */
  hal_i3c_cb_t  p_tgt_rx_cplt_cb; /*!< Tgt private data rx transfer completed cb */
  hal_i3c_tgt_hot_join_cb_t p_tgt_hot_join_cb;  /*!< Tgt hot-join cb */
  hal_i3c_notify_cb_t  p_notify_cb; /*!< Tgt/ctrl asynchronous events cb */
  hal_i3c_cb_t  p_error_cb; /*!< Tgt/ctrl Error cb */
  hal_i3c_cb_t  p_abort_cplt_cb; /*!< Tgt/ctrl Abort complete cb */
#endif  /* USE_HAL_I3C_REGISTER_CALLBACKS */
};

/**
  * @}
  */

/* Exported macro ----------------------------------------------------------------------------------------------------*/
/** @defgroup I3C_Exported_Macros HAL I3C Macros
  * @{
  */

/**
  * @brief Get the ctrl_buf size needed for a specific usecase.
  * @param  NB_DESC  Number of descriptions used in the transfer context
  * @param  MODE     Mode of the transfer used in the transfer context See hal_i3c_xfer_mode_t
  * @retval 2*NB_DESC in case of direct CCC transfers or NB_DESC for all other transfers
  */
#define HAL_I3C_GET_CTRL_BUFFER_SIZE_WORD(NB_DESC, MODE) \
  (((MODE & LL_I3C_CONTROLLER_MTYPE_DIRECT) == LL_I3C_CONTROLLER_MTYPE_DIRECT) ? (2U * NB_DESC) : NB_DESC)

/** @brief  Get Provisioned ID in payload (64bits) receive during ENTDAA procedure.
  * @param  PAYLOAD  Device Characteristics capabilities retrieve during ENTDAA procedure
  *         This parameter must be a number between Min_Data=0x00(uint64_t) and Max_Data=0xFFFFFFFFFFFFFFF
  * @retval The value of PID Return value between Min_Data=0x00 and Max_Data=0xFFFFFFFFFFF
  */
#define HAL_I3C_GET_PID(PAYLOAD) ((uint64_t)(PAYLOAD) & HAL_I3C_PID_IN_PAYLOAD_MASK)

/** @brief  Get MIPI Manufacturer ID in PID (48bits).
  * @param  PID  Provisioned ID retrieve during ENTDAA procedure
  *         This parameter must be a number between Min_Data=0x00(uint64_t) and Max_Data=0xFFFFFFFFFFFF
  * @retval The value of MIPI ID Return value between Min_Data=0x00 and Max_Data=0x7FFF
  */
#define HAL_I3C_GET_MIPIMID(PID) ((uint16_t)((uint64_t)(PID) >> HAL_I3C_MIPIMID_PID_SHIFT) & HAL_I3C_MIPIMID_PID_MASK)

/** @brief  Get Type Selector in PID (48bits).
  * @param  PID  Provisioned ID retrieve during ENTDAA procedure
  *         This parameter must be a number between Min_Data=0x00(uint64_t) and Max_Data=0xFFFFFFFFFFFF
  * @retval The value of Type Selector Return 0 or 1
  */
#define HAL_I3C_GET_IDTSEL(PID) ((uint8_t)((uint64_t)(PID) >> HAL_I3C_IDTSEL_PID_SHIFT) &  HAL_I3C_IDTSEL_PID_MASK)

/** @brief  Get Part ID in PID (48bits).
  * @param  PID  Provisioned ID retrieve during ENTDAA procedure
  *         This parameter must be a number between Min_Data=0x00(uint64_t) and Max_Data=0xFFFFFFFFFFFF
  * @retval The value of Part ID Return value between Min_Data=0x00 and Max_Data=0xFFF
  */
#define HAL_I3C_GET_PART_ID(PID) ((uint16_t)((uint64_t)(PID) >> HAL_I3C_PART_ID_PID_SHIFT) & HAL_I3C_PART_ID_PID_MASK)

/** @brief  Get Instance ID in PID (48bits).
  * @param  PID  Provisioned ID retrieve during ENTDAA procedure
  *         This parameter must be a number between Min_Data=0x00(uint64_t) and Max_Data=0xFFFFFFFFFFFF
  * @retval The value of Instance ID Return value between Min_Data=0x00 and Max_Data=0xF
  */
#define HAL_I3C_GET_MIPIID(PID) ((uint8_t)((uint64_t)(PID) >> HAL_I3C_MIPIID_PID_SHIFT) & HAL_I3C_MIPIID_PID_MASK)

/** @brief  Get Device Characterics in payload (64bits) receive during ENTDAA procedure.
  * @param  PAYLOAD  Device Characteristics capabilities retrieve during ENTDAA procedure
  *         This parameter must be a number between Min_Data=0x00(uint64_t) and Max_Data=0xFFFFFFFFFFFFFFFFF
  * @retval The value of BCR Return value between Min_Data=0x00 and Max_Data=0xFF
  */
#define HAL_I3C_GET_DCR(PAYLOAD) (((uint32_t)((uint64_t)(PAYLOAD) >> HAL_I3C_DCR_IN_PAYLOAD_SHIFT)) & I3C_DCR_DCR)

/** @brief  Get Bus Characterics in payload (64bits) receive during ENTDAA procedure.
  * @param  PAYLOAD  Bus Characteristics capabilities retrieve during ENTDAA procedure
  *         This parameter must be a number between Min_Data=0x00(uint64_t) and Max_Data=0xFFFFFFFFFFFFFFFFF
  * @retval The value of BCR Return value between Min_Data=0x00 and Max_Data=0xFF
  */
#define HAL_I3C_GET_BCR(PAYLOAD) (((uint32_t)((uint64_t)(PAYLOAD) >> HAL_I3C_BCR_IN_PAYLOAD_SHIFT)) \
                                  & HAL_I3C_BCR_BCR_MSK)

/** @brief  Get Advanced Capabilities.
  * @param  BCR  Bus Characteristics capabilities retrieve during ENTDAA procedure
  *         This parameter must be a number between Min_Data=0x00 and Max_Data=0xFF
  * @retval The value of advanced capabilities:
  *           ENABLE: supports optional advanced capabilities
  *           DISABLE: not supports optional advanced capabilities
  */
#define HAL_I3C_GET_ADVANCED_CAPABLE(BCR) (((((BCR) & HAL_I3C_BCR_BCR5_MSK) >> HAL_I3C_BCR_BCR5_POS) == 1U) ? \
                                           HAL_I3C_ADV_CAPABILITIES_ENABLED : HAL_I3C_ADV_CAPABILITIES_DISABLED)
/** @brief  Get virtual target support.
  * @param  BCR  Bus Characteristics capabilities retrieve during ENTDAA procedure
  *         This parameter must be a number between Min_Data=0x00 and Max_Data=0xFF
  * @retval The value of offline capable:
  *           1U: is a Virtual Target
  *           DISABLE: is not a Virtual Target
  */
#define HAL_I3C_GET_VIRTUAL_TGT(BCR) (((((BCR) & HAL_I3C_BCR_BCR4_MSK) >> HAL_I3C_BCR_BCR4_POS) == 1U) ? \
                                      HAL_I3C_VIRTUAL_TGT_ENABLED : HAL_I3C_VIRTUAL_TGT_DISABLED)

/** @brief  Get offline capable.
  * @param  BCR  Bus Characteristics capabilities retrieve during ENTDAA procedure
  *         This parameter must be a number between Min_Data=0x00 and Max_Data=0xFF
  * @retval The value of offline capable
  *           HAL_I3C_OFFLINE_CAPABLE_ENABLED: Device will not always respond to I3C Bus commands
  *           HAL_I3C_OFFLINE_CAPABLE_DISABLED: Device will always respond to I3C Bus commands
  */
#define HAL_I3C_GET_OFFLINE_CAPABLE(BCR) (((((BCR) & HAL_I3C_BCR_BCR3_MSK) >>  HAL_I3C_BCR_BCR3_POS) == 1U) ? \
                                          HAL_I3C_OFFLINE_CAPABLE_ENABLED : HAL_I3C_OFFLINE_CAPABLE_DISABLED)

/** @brief  Get Max data speed limitation.
  * @param  BCR  Bus Characteristics capabilities retrieve during ENTDAA procedure
  *         This parameter must be a number between Min_Data=0x00 and Max_Data=0xFF
  * @retval The value of offline capable:
  *           1U: Limitation
  *           DISABLE: No Limitation
  */
#define HAL_I3C_GET_MAX_DATA_SPEED_LIMIT(BCR) (((((BCR) & HAL_I3C_BCR_BCR0_MSK) >> HAL_I3C_BCR_BCR0_POS) == 1U) ? \
                                               HAL_I3C_MAX_SPEED_LIMITATION_ENABLED : \
                                               HAL_I3C_MAX_SPEED_LIMITATION_DISABLED)

/** @brief  Check IBI request capabilities.
  * @param  BCR  Bus Characteristics capabilities retrieve during ENTDAA procedure
  *         This parameter must be a number between Min_Data=0x00 and Max_Data=0xFF
  * @retval IBI request capabilities (HAL_I3C_IBI_REQ_ENABLED or HAL_I3C_IBI_REQ_DISABLED).
  */
#define HAL_I3C_GET_IBI_CAPABLE(BCR) (((((BCR) & HAL_I3C_BCR_BCR1_MSK) >> HAL_I3C_BCR_BCR1_POS) == 1U) ? \
                                      HAL_I3C_IBI_REQ_ENABLED : HAL_I3C_IBI_REQ_DISABLED)

/** @brief  Check IBI additional data byte capabilities.
  * @param  BCR  Bus Characteristics capabilities retrieve during ENTDAA procedure
  *         This parameter must be a number between Min_Data=0x00 and Max_Data=0xFF
  * @retval IBI additional data byte capabilities (HAL_I3C_IBI_PAYLOAD_ENABLED or HAL_I3C_IBI_PAYLOAD_DISABLED)
  */
#define HAL_I3C_GET_IBI_PAYLOAD(BCR) (((((BCR) & HAL_I3C_BCR_BCR2_MSK) >> HAL_I3C_BCR_BCR2_POS) == 1U) ? \
                                      HAL_I3C_IBI_PAYLOAD_ENABLED : HAL_I3C_IBI_PAYLOAD_DISABLED)

/** @brief  Check Controller-Role request capabilities.
  * @param  BCR  Bus Characteristics capabilities retrieve during ENTDAA procedure
  *         This parameter must be a number between Min_Data=0x00 and Max_Data=0xFF
  * @retval Controller-Role request capabilities (HAL_I3C_CTRL_CAPABILITY_ENABLED or HAL_I3C_CTRL_CAPABILITY_DISABLED)
  */
#define HAL_I3C_GET_CR_CAPABLE(BCR) (((((BCR) & HAL_I3C_BCR_BCR6_MSK) >> HAL_I3C_BCR_BCR6_POS) == 1U) ? \
                                     HAL_I3C_CTRL_CAPABILITY_ENABLED : HAL_I3C_CTRL_CAPABILITY_DISABLED)

/** @brief  Change uint32_t variable form big endian to little endian.
  * @param  DATA uint32_t variable in big endian
  *         This parameter must be a number between Min_Data=0x00(uint32_t) and Max_Data=0xFFFFFFFF
  * @retval uint32_t variable in little endian
  */
#define HAL_I3C_BIG_TO_LITTLE_ENDIAN(DATA) ((uint32_t)((((DATA) & 0xff000000U) >> 24) \
                                                       | (((DATA) & 0x00ff0000U) >> 8) \
                                                       | (((DATA) & 0x0000ff00U) << 8) \
                                                       | (((DATA) & 0x000000ffU) << 24)))
/**
  * @}
  */

/* Exported functions ------------------------------------------------------------------------------------------------*/
/** @addtogroup I3C_Exported_Functions HAL I3C Functions
  * @{
  */

/** @addtogroup I3C_Exported_Functions_Group1 Initialization and de-initialization functions
  * @{
  */
hal_status_t HAL_I3C_Init(hal_i3c_handle_t *hi3c, hal_i3c_t instance);
void HAL_I3C_DeInit(hal_i3c_handle_t *hi3c);
/**
  * @}
  */

/** @defgroup I3C_Exported_Functions_Group2 Configuration functions
  * @{
  */

/* Global configuration */
/* Global configuration (controller) */
hal_status_t HAL_I3C_CTRL_SetConfig(hal_i3c_handle_t *hi3c, const hal_i3c_ctrl_config_t *p_config);
void HAL_I3C_CTRL_GetConfig(const hal_i3c_handle_t *hi3c, hal_i3c_ctrl_config_t *p_config);

/* Global configuration (target) */
hal_status_t HAL_I3C_TGT_SetConfig(hal_i3c_handle_t *hi3c, const hal_i3c_tgt_config_t *p_config);
void HAL_I3C_TGT_GetConfig(const hal_i3c_handle_t *hi3c, hal_i3c_tgt_config_t *p_config);

/* Payload ENTDAA configuration (target) */
hal_status_t HAL_I3C_TGT_SetPayloadENTDAAConfig(const hal_i3c_handle_t *hi3c,
                                                const hal_i3c_tgt_config_payload_entdaa_t *p_config);
void HAL_I3C_TGT_GetPayloadENTDAAConfig(const hal_i3c_handle_t *hi3c, hal_i3c_tgt_config_payload_entdaa_t *p_config);

/* FIFO configuration (controller) */
hal_status_t HAL_I3C_CTRL_SetConfigFifo(const hal_i3c_handle_t *hi3c, const hal_i3c_ctrl_fifo_config_t *p_config);
void HAL_I3C_CTRL_GetConfigFifo(const hal_i3c_handle_t *hi3c, hal_i3c_ctrl_fifo_config_t *p_config);

/* FIFO configuration (target) */
hal_status_t HAL_I3C_TGT_SetConfigFifo(const hal_i3c_handle_t *hi3c, const hal_i3c_tgt_fifo_config_t *p_config);
void HAL_I3C_TGT_GetConfigFifo(const hal_i3c_handle_t *hi3c, hal_i3c_tgt_fifo_config_t *p_config);

/* FIFO configuration unitary functions */
hal_status_t HAL_I3C_SetRxFifoThreshold(const hal_i3c_handle_t *hi3c, const hal_i3c_rx_fifo_threshold_t threshold);
hal_i3c_rx_fifo_threshold_t HAL_I3C_GetRxFifoThreshold(const hal_i3c_handle_t *hi3c);
hal_status_t HAL_I3C_SetTxFifoThreshold(const hal_i3c_handle_t *hi3c, const hal_i3c_tx_fifo_threshold_t threshold);
hal_i3c_tx_fifo_threshold_t HAL_I3C_GetTxFifoThreshold(const hal_i3c_handle_t *hi3c);
hal_status_t HAL_I3C_CTRL_EnableControlFifo(hal_i3c_handle_t *hi3c);
hal_status_t HAL_I3C_CTRL_DisableControlFifo(hal_i3c_handle_t *hi3c);
hal_i3c_control_fifo_status_t HAL_I3C_CTRL_IsEnabledControlFifo(const hal_i3c_handle_t *hi3c);
hal_status_t HAL_I3C_CTRL_EnableStatusFifo(hal_i3c_handle_t *hi3c);
hal_status_t HAL_I3C_CTRL_DisableStatusFifo(hal_i3c_handle_t *hi3c);
hal_i3c_status_fifo_status_t HAL_I3C_CTRL_IsEnabledStatusFifo(const hal_i3c_handle_t *hi3c);

/* Own dynamic address (controller) */
hal_status_t HAL_I3C_CTRL_SetConfigOwnDynamicAddress(hal_i3c_handle_t *hi3c, uint32_t dynamic_address);
uint32_t HAL_I3C_CTRL_GetConfigOwnDynamicAddress(const hal_i3c_handle_t *hi3c);

/* Hot-Join allowed (controller) */
hal_status_t HAL_I3C_CTRL_EnableHotJoinAllowed(hal_i3c_handle_t *hi3c);
hal_status_t HAL_I3C_CTRL_DisableHotJoinAllowed(hal_i3c_handle_t *hi3c);
hal_i3c_hot_join_status_t HAL_I3C_CTRL_IsEnabledHotJoinAllowed(const hal_i3c_handle_t *hi3c);

/* High keeper SDA configuration (controller) */
hal_status_t HAL_I3C_CTRL_EnableHighKeeperSDA(const hal_i3c_handle_t *hi3c);
hal_status_t HAL_I3C_CTRL_DisableHighKeeperSDA(const hal_i3c_handle_t *hi3c);
hal_i3c_high_keeper_sda_status_t HAL_I3C_CTRL_IsEnabledHighKeeperSDA(const hal_i3c_handle_t *hi3c);

/* Stall time configuration (controller) */
hal_status_t HAL_I3C_CTRL_SetConfigStallTime(const hal_i3c_handle_t *hi3c, uint32_t stall_time,
                                             uint32_t stall_features);
hal_status_t HAL_I3C_CTRL_GetConfigStallTime(const hal_i3c_handle_t *hi3c, uint32_t *stall_time,
                                             uint32_t *stall_features);

/* Controller-Role request configuration (target) */
hal_status_t HAL_I3C_TGT_EnableCtrlRoleRequest(const hal_i3c_handle_t *hi3c);
hal_status_t HAL_I3C_TGT_DisableCtrlRoleRequest(const hal_i3c_handle_t *hi3c);
hal_i3c_ctrl_role_status_t HAL_I3C_TGT_IsEnabledCtrlRoleRequest(const hal_i3c_handle_t *hi3c);

hal_status_t HAL_I3C_TGT_EnableHandOffDelay(const hal_i3c_handle_t *hi3c);
hal_status_t HAL_I3C_TGT_DisableHandOffDelay(const hal_i3c_handle_t *hi3c);
hal_i3c_hand_off_delay_status_t HAL_I3C_TGT_IsEnabledHandOffDelay(const hal_i3c_handle_t *hi3c);

/* Group management support configuration (target) */
hal_status_t HAL_I3C_TGT_EnableGroupAddrCapability(const hal_i3c_handle_t *hi3c);
hal_status_t HAL_I3C_TGT_DisableGroupAddrCapability(const hal_i3c_handle_t *hi3c);
hal_i3c_grp_addr_capability_status_t HAL_I3C_TGT_IsEnabledGroupAddrCapability(const hal_i3c_handle_t *hi3c);

/* Hot-Join configuration (target) */
hal_status_t HAL_I3C_TGT_EnableHotJoinRequest(const hal_i3c_handle_t *hi3c);
hal_status_t HAL_I3C_TGT_DisableHotJoinRequest(const hal_i3c_handle_t *hi3c);
hal_i3c_hot_join_status_t HAL_I3C_TGT_IsEnabledHotJoinRequest(const hal_i3c_handle_t *hi3c);

/* IBI configuration (target) */
hal_status_t HAL_I3C_TGT_EnableIBI(const hal_i3c_handle_t *hi3c, const hal_i3c_tgt_ibi_config_t *p_config);
hal_status_t HAL_I3C_TGT_DisableIBI(const hal_i3c_handle_t *hi3c);
void HAL_I3C_TGT_GetConfigIBI(const hal_i3c_handle_t *hi3c, hal_i3c_tgt_ibi_config_t *p_config);
hal_i3c_ibi_req_status_t HAL_I3C_TGT_IsEnabledIBI(const hal_i3c_handle_t *hi3c);

/* Max data size configuration (target) */
hal_status_t HAL_I3C_TGT_SetConfigMaxDataSize(const hal_i3c_handle_t *hi3c,
                                              const hal_i3c_tgt_max_data_size_config_t *p_config);
void HAL_I3C_TGT_GetConfigMaxDataSize(const hal_i3c_handle_t *hi3c,
                                      hal_i3c_tgt_max_data_size_config_t *p_config);

/* GET MaX Data Speed (GETMXDS) configuration (target) */
hal_status_t HAL_I3C_TGT_SetConfigGETMXDS(const hal_i3c_handle_t *hi3c, const hal_i3c_tgt_getmxds_config_t *p_config);
void HAL_I3C_TGT_GetConfigGETMXDS(const hal_i3c_handle_t *hi3c, hal_i3c_tgt_getmxds_config_t *p_config);
/* GET MaX Data Speed (GETMXDS) unitary functions */
hal_status_t HAL_I3C_TGT_SetConfigGETMXDS_Format(const hal_i3c_handle_t *hi3c, hal_i3c_GETMXDS_format_t format);
hal_i3c_GETMXDS_format_t HAL_I3C_TGT_GetConfigGETMXDS_Format(const hal_i3c_handle_t *hi3c);
hal_status_t HAL_I3C_TGT_SetConfigCtrlHandOffActivity(const hal_i3c_handle_t *hi3c,
                                                      hal_i3c_handoff_activity_state_t state);
hal_i3c_handoff_activity_state_t HAL_I3C_TGT_GetConfigCtrlHandOffActivity(const hal_i3c_handle_t *hi3c);

/* Bus device configuration configuration (controller) */
hal_status_t HAL_I3C_CTRL_SetConfigBusDevices(const hal_i3c_handle_t *hi3c, const hal_i3c_ctrl_device_config_t *p_desc,
                                              uint32_t nb_device);
void HAL_I3C_CTRL_GetConfigBusDevices(const hal_i3c_handle_t *hi3c, hal_i3c_ctrl_device_config_t *p_desc,
                                      uint32_t nb_device);

/* Reset pattern configuration (controller) */
hal_status_t HAL_I3C_CTRL_EnableResetPattern(hal_i3c_handle_t *hi3c);
hal_status_t HAL_I3C_CTRL_DisableResetPattern(hal_i3c_handle_t *hi3c);
hal_i3c_reset_pattern_status_t HAL_I3C_CTRL_IsEnabledResetPattern(const hal_i3c_handle_t *hi3c);

#if defined(USE_HAL_I3C_REGISTER_CALLBACKS) && (USE_HAL_I3C_REGISTER_CALLBACKS == 1U)
/* Register callbacks */
hal_status_t HAL_I3C_CTRL_RegisterXferCpltCallback(hal_i3c_handle_t *hi3c, hal_i3c_cb_t p_callback);
hal_status_t HAL_I3C_CTRL_RegisterDAACpltCallback(hal_i3c_handle_t *hi3c, hal_i3c_cb_t p_callback);
hal_status_t HAL_I3C_CTRL_RegisterTgtReqDynAddrCallback(hal_i3c_handle_t *hi3c,
                                                        hal_i3c_req_dyn_addr_cb_t p_callback);
hal_status_t HAL_I3C_TGT_RegisterTxCpltCallback(hal_i3c_handle_t *hi3c, hal_i3c_cb_t p_callback);
hal_status_t HAL_I3C_TGT_RegisterRxCpltCallback(hal_i3c_handle_t *hi3c, hal_i3c_cb_t p_callback);
hal_status_t HAL_I3C_TGT_RegisterHotJoinCallback(hal_i3c_handle_t *hi3c, hal_i3c_tgt_hot_join_cb_t p_callback);
hal_status_t HAL_I3C_RegisterNotifyCallback(hal_i3c_handle_t *hi3c, hal_i3c_notify_cb_t p_callback);
hal_status_t HAL_I3C_RegisterAbortCpltCallback(hal_i3c_handle_t *hi3c, hal_i3c_cb_t p_callback);
hal_status_t HAL_I3C_RegisterErrorCallback(hal_i3c_handle_t *hi3c, hal_i3c_cb_t p_callback);
#endif /* USE_HAL_I3C_REGISTER_CALLBACKS */

#if defined(USE_HAL_I3C_DMA) && (USE_HAL_I3C_DMA == 1)
hal_status_t HAL_I3C_SetTxDMA(hal_i3c_handle_t *hi3c, hal_dma_handle_t *hdma);
hal_status_t HAL_I3C_SetRxDMA(hal_i3c_handle_t *hi3c, hal_dma_handle_t *hdma);
hal_status_t HAL_I3C_SetCrDMA(hal_i3c_handle_t *hi3c, hal_dma_handle_t *hdma);
#endif /* USE_HAL_I3C_DMA */
/**
  * @}
  */

/** @addtogroup I3C_Exported_Functions_Group3 Interrupt and callback functions
  * @{
  */
hal_status_t HAL_I3C_CTRL_ActivateNotification(hal_i3c_handle_t *hi3c, uint32_t notifications);
hal_status_t HAL_I3C_CTRL_DeactivateNotification(hal_i3c_handle_t *hi3c, uint32_t notifications);
hal_status_t HAL_I3C_TGT_ActivateNotification(hal_i3c_handle_t *hi3c, uint8_t *p_data, uint32_t size_byte,
                                              uint32_t notifications);
hal_status_t HAL_I3C_TGT_DeactivateNotification(hal_i3c_handle_t *hi3c, uint32_t notifications);
/**
  * @}
  */

/** @defgroup I3C_Exported_Functions_Group4 IRQ Handlers
  * @{
  */
void HAL_I3C_ERR_IRQHandler(hal_i3c_handle_t *hi3c);
void HAL_I3C_EV_IRQHandler(hal_i3c_handle_t *hi3c);
/**
  * @}
  */

/** @defgroup I3C_Exported_Functions_Group5 FIFO management functions
  * @{
  */
hal_status_t HAL_I3C_FlushAllFifo(const hal_i3c_handle_t *hi3c);
hal_status_t HAL_I3C_FlushTxFifo(const hal_i3c_handle_t *hi3c);
hal_status_t HAL_I3C_FlushRxFifo(const hal_i3c_handle_t *hi3c);
hal_status_t HAL_I3C_FlushControlFifo(const hal_i3c_handle_t *hi3c);
hal_status_t HAL_I3C_FlushStatusFifo(const hal_i3c_handle_t *hi3c);
/**
  * @}
  */

/** @defgroup I3C_Exported_Functions_Group6 Controller transfer operation functions
  * @{
  */
/* Controller transfer operation */
hal_status_t HAL_I3C_CTRL_ResetXferCtx(hal_i3c_xfer_ctx_t *p_ctx);
hal_status_t HAL_I3C_CTRL_InitXferCtxCtrl(hal_i3c_xfer_ctx_t *p_ctx, uint32_t *p_ctrl_buf, uint32_t size_word);
hal_status_t HAL_I3C_CTRL_InitXferCtxTx(hal_i3c_xfer_ctx_t *p_ctx, const uint8_t *p_tx_data, uint32_t size_byte);
hal_status_t HAL_I3C_CTRL_InitXferCtxRx(hal_i3c_xfer_ctx_t *p_ctx, uint8_t *p_rx_data, uint32_t size_byte);

hal_status_t HAL_I3C_CTRL_BuildXferCtxPrivate(hal_i3c_xfer_ctx_t *p_ctx, const hal_i3c_private_desc_t *p_desc,
                                              uint32_t nb_desc, hal_i3c_xfer_mode_t mode);
hal_status_t HAL_I3C_CTRL_BuildXferCtxCCC(hal_i3c_xfer_ctx_t *p_ctx, const hal_i3c_ccc_desc_t *p_desc, uint32_t nb_desc,
                                          hal_i3c_xfer_mode_t mode);
hal_status_t HAL_I3C_CTRL_StartXfer(hal_i3c_handle_t *hi3c, const hal_i3c_xfer_ctx_t *p_ctx, uint32_t timeout_ms);
hal_status_t HAL_I3C_CTRL_StartXfer_IT(hal_i3c_handle_t *hi3c, const hal_i3c_xfer_ctx_t *p_ctx);
hal_status_t HAL_I3C_CTRL_StartXfer_DMA(hal_i3c_handle_t *hi3c, const hal_i3c_xfer_ctx_t *p_ctx);

/* Controller assign dynamic address APIs */
hal_status_t HAL_I3C_CTRL_SetDynAddr(const hal_i3c_handle_t *hi3c, uint8_t target_address);
hal_status_t HAL_I3C_CTRL_DynAddrAssign_IT(hal_i3c_handle_t *hi3c, hal_i3c_dyn_addr_opt_t option);
hal_status_t HAL_I3C_CTRL_DynAddrAssign(hal_i3c_handle_t *hi3c, uint64_t *p_target_payload,
                                        hal_i3c_dyn_addr_opt_t option, uint32_t timeout_ms);

/* Controller check device ready APIs */
hal_status_t HAL_I3C_CTRL_IsDeviceI3C_Ready(hal_i3c_handle_t *hi3c, uint8_t target_address, uint32_t trials,
                                            uint32_t timeout_ms);
hal_status_t HAL_I3C_CTRL_IsDeviceI2C_Ready(hal_i3c_handle_t *hi3c, uint8_t target_address, uint32_t trials,
                                            uint32_t timeout_ms);
/* Controller patterns APIs */
hal_status_t HAL_I3C_CTRL_GeneratePatterns(hal_i3c_handle_t *hi3c, hal_i3c_pattern_opt_t pattern, uint32_t timeout_ms);

/* Controller arbitration API */
hal_status_t HAL_I3C_CTRL_GenerateArbitration(hal_i3c_handle_t *hi3c, uint32_t timeout_ms);

/* Controller stop SCL API in case of CE1 error */
hal_status_t HAL_I3C_CTRL_RecoverSCLToIDLE(const hal_i3c_handle_t *hi3c);
/**
  * @}
  */

/** @defgroup I3C_Exported_Functions_Group7 Target operational functions
  * @{
  */
hal_status_t HAL_I3C_TGT_Transmit(hal_i3c_handle_t *hi3c, const uint8_t *p_data, uint32_t size_byte,
                                  uint32_t timeout_ms);
hal_status_t HAL_I3C_TGT_Transmit_IT(hal_i3c_handle_t *hi3c, const uint8_t *p_data, uint32_t size_byte);
hal_status_t HAL_I3C_TGT_Transmit_DMA(hal_i3c_handle_t *hi3c, const uint8_t *p_data, uint32_t size_byte);
hal_status_t HAL_I3C_TGT_Receive(hal_i3c_handle_t *hi3c, uint8_t *p_data, uint32_t size_byte, uint32_t timeout_ms);
hal_status_t HAL_I3C_TGT_Receive_IT(hal_i3c_handle_t *hi3c, uint8_t *p_data, uint32_t size_byte);
hal_status_t HAL_I3C_TGT_Receive_DMA(hal_i3c_handle_t *hi3c, uint8_t *p_data, uint32_t size_byte);
hal_status_t HAL_I3C_TGT_ControlRoleReq(hal_i3c_handle_t *hi3c, uint32_t timeout_ms);
hal_status_t HAL_I3C_TGT_ControlRoleReq_IT(hal_i3c_handle_t *hi3c);
hal_status_t HAL_I3C_TGT_HotJoinReq(hal_i3c_handle_t *hi3c, uint8_t *p_own_dynamic_address, uint32_t timeout_ms);
hal_status_t HAL_I3C_TGT_HotJoinReq_IT(hal_i3c_handle_t *hi3c);
hal_status_t HAL_I3C_TGT_IBIReq(hal_i3c_handle_t *hi3c, const uint8_t *p_payload, uint32_t payload_size_byte,
                                uint32_t timeout_ms);
hal_status_t HAL_I3C_TGT_IBIReq_IT(hal_i3c_handle_t *hi3c, const uint8_t *p_payload, uint32_t payload_size_byte);
/**
  * @}
  */

/** @defgroup I3C_Exported_Functions_Group8 Weak callback functions
  * @{
  */
void HAL_I3C_CTRL_XferCpltCallback(hal_i3c_handle_t *hi3c);
void HAL_I3C_CTRL_DAACpltCallback(hal_i3c_handle_t *hi3c);
void HAL_I3C_CTRL_TgtReqDynAddrCallback(hal_i3c_handle_t *hi3c, uint64_t target_payload);
void HAL_I3C_TGT_TxCpltCallback(hal_i3c_handle_t *hi3c);
void HAL_I3C_TGT_RxCpltCallback(hal_i3c_handle_t *hi3c);
void HAL_I3C_TGT_HotJoinCallback(hal_i3c_handle_t *hi3c, uint8_t dynamic_address);
void HAL_I3C_NotifyCallback(hal_i3c_handle_t *hi3c, uint32_t notify_id);
void HAL_I3C_ErrorCallback(hal_i3c_handle_t *hi3c);
void HAL_I3C_AbortCpltCallback(hal_i3c_handle_t *hi3c);
/**
  * @}
  */

/** @defgroup I3C_Exported_Functions_Group9 Generic and common functions
  * @{
  */
hal_i3c_state_t HAL_I3C_GetState(const hal_i3c_handle_t *hi3c);
hal_i3c_mode_t HAL_I3C_GetMode(const hal_i3c_handle_t *hi3c);
#if defined(USE_HAL_I3C_GET_LAST_ERRORS) && (USE_HAL_I3C_GET_LAST_ERRORS == 1)
uint32_t HAL_I3C_GetLastErrorCodes(const hal_i3c_handle_t *hi3c);
#endif /* USE_HAL_I3C_GET_LAST_ERRORS */
uint32_t HAL_I3C_GetClockFreq(const hal_i3c_handle_t *hi3c);
hal_status_t HAL_I3C_Abort_IT(hal_i3c_handle_t *hi3c);
hal_status_t HAL_I3C_GetCCCInfo(const hal_i3c_handle_t *hi3c, uint32_t notifications, hal_i3c_ccc_info_t *p_ccc_info);
hal_status_t HAL_I3C_CTRL_GetENTDAA_PayloadInfo(uint64_t entdaa_payload, hal_i3c_entdaa_payload_t *p_entdaa_payload);
uint32_t HAL_I3C_GetDataCounter(hal_i3c_handle_t *hi3c);
/**
  * @}
  */

#if defined(USE_HAL_MUTEX) && (USE_HAL_MUTEX == 1)
/** @defgroup I3C_Exported_Functions_Group10 Acquire/release the bus
  * @{
  */
hal_status_t HAL_I3C_AcquireBus(hal_i3c_handle_t *hi3c, uint32_t timeout_ms);
hal_status_t HAL_I3C_ReleaseBus(hal_i3c_handle_t *hi3c);
/**
  * @}
  */
#endif /* USE_HAL_MUTEX */

#if defined(USE_HAL_I3C_USER_DATA) && (USE_HAL_I3C_USER_DATA == 1)
/** @defgroup I3C_Exported_Functions_Group11 Set/get user data
  * @{
  */
void HAL_I3C_SetUserData(hal_i3c_handle_t *hi3c, const void *p_user_data);
const void *HAL_I3C_GetUserData(const hal_i3c_handle_t *hi3c);
/**
  * @}
  */
#endif /* USE_HAL_I3C_USER_DATA */

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

#endif /* STM32H7Pxx_HAL_I3C_H */
