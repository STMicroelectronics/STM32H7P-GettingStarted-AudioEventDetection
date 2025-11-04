/**
  **********************************************************************************************************************
  * @file    stm32h7pxx_hal_i3c.c
  * @author  GMP Application Team
  * @brief   I3C HAL module driver.
  *          This file provides firmware functions to manage the following
  *          functionalities of the Improvement Inter Integrated Circuit (I3C) peripheral:
  *           + Initialization and de-initialization functions
  *           + IO operation functions
  *           + Peripheral state and errors functions
  *
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
  *********************************************************************************************************************/

/* Includes ----------------------------------------------------------------------------------------------------------*/
#include "stm32_hal.h"

/** @addtogroup STM32H7Pxx_HAL_Driver
  * @{
  */

/** @addtogroup I3C I3C
  * @{
  */
/** @defgroup I3C_Introduction I3C Introduction
  * @{
The STM32 Hardware Abstraction Layer for I3C provides a comprehensive software interface to support the I3C
communication protocol on STM32 microcontrollers. I3C (Improved Inter-Integrated Circuit) is an advanced, high-speed,
and energy-efficient serial bus protocol designed to enhance and replace traditional I2C, offering features such as
dynamic device management and higher data rates. While I3C maintains backward compatibility with many I2C devices,
certain I2C features as stretch mode are not supported.
This HAL driver abstracts low-level hardware details, enabling configuration, data transfer, and interrupt handling,
thereby accelerating development and ensuring robust and scalable embedded applications leveraging the full
capabilities of the I3C bus.
  */
/**
  * @}
  */

/** @defgroup I3C_How_To_Use I3C How To Use
  * @{

# How to use the I3C HAL module driver:

## Declare:
  - A hal_i3c_handle_t handle structure.<br>
    for example: hal_i3c_handle_t  hi3c;
  - A hal_i3c_xfer_ctx_t transfer descriptor structure (controller only). <br>
    for example: hal_i3c_xfer_ctx_t  my_xfer_ctx;

## Initialize the I3Cx driver with an I3C HW instance by calling the HAL_I3C_Init().
   The I3Cx clock is enabled inside the HAL_I3C_Init() if USE_HAL_I3C_CLK_ENABLE_MODEL > HAL_CLK_ENABLE_NO.

## Configure the low level hardware (GPIO, CLOCK, NVIC...etc):
  - Enable the I3Cx clock if USE_HAL_I3C_CLK_ENABLE_MODEL = HAL_CLK_ENABLE_NO.
  - I3Cx pins configuration:
    - Enable the clock for the I3Cx GPIOs.
    - Configure I3C pins as alternate function push-pull with no-pull.

  - NVIC configuration if you need to use interrupt process:
      - Configure the I3Cx interrupt priority.
      - Enable the NVIC I3C IRQ Channel.

  - DMA configuration if you need to use DMA process:
      - Declare a hal_dma_handle_t handle structure for the Control Register (CR) management channel.
      - Declare a hal_dma_handle_t handle structure for the transmit channel.
      - Declare a hal_dma_handle_t handle structure for the receive channel.
      - Enable the DMAx interface clock
      - Configure the DMA handle parameters
      - Configure the DMA Control Register (CR) channel.
      - Configure the DMA Tx channel.
      - Configure the DMA Rx channel.
      - Associate the initialized DMA handle to the hi3c DMA CR, Tx or Rx as necessary.
      - Configure the priority and enable the NVIC for the transfer complete interrupt on the DMA CR, Tx or Rx instance.

## Configure the communication mode:
      - Controller mode: HAL_I3C_CTRL_SetConfig()
      - Target mode: HAL_I3C_TGT_SetConfig()

## Configure FIFO parameters if needed:
     - Controller: HAL_I3C_CTRL_SetConfigFifo()
     - Target: HAL_I3C_TGT_SetConfigFifo()

## Before initiating any ENTDAA, the target must configure the target payload of the ENTDAA by using
   HAL_I3C_TGT_SetPayloadENTDAAConfig().

## Configure and/or enable advanced controller features if needed:
  - HAL_I3C_CTRL_SetConfigOwnDynamicAddress()
  - HAL_I3C_CTRL_EnableHotJoinAllowed()
  - HAL_I3C_CTRL_EnableHighKeeperSDA()
  - HAL_I3C_CTRL_SetConfigStallTime()
  - HAL_I3C_CTRL_SetConfigBusDevices()
  - HAL_I3C_CTRL_EnableResetPattern()

## Configure and/or enable advanced target features if needed:
  - HAL_I3C_TGT_SetConfigGETMXDS()
  - HAL_I3C_TGT_EnableGroupAddrCapability()
  - HAL_I3C_TGT_SetConfigMaxDataSize()
  - HAL_I3C_TGT_EnableIBI()
  - HAL_I3C_TGT_EnableHotJoinRequest()
  - HAL_I3C_TGT_EnableCtrlRoleRequest()

## Dynamic Address Assignment
  - Before initiating any IO operation, the controller application must launch an assignment of the different target
    dynamic address by using HAL_I3C_CTRL_DynAddrAssign() in polling mode or HAL_I3C_CTRL_DynAddrAssign_IT() in
    interrupt mode. This procedure is named Enter Dynamic Address Assignment (ENTDAA CCC command).
  - For the initiation of ENTDAA procedure, each target connected and powered on the I3C bus must respond to this
    particular Command Common Code (CCC) by sending its proper Payload (an amount of 48bits which contain the target
    characteristics). Each time a target responds to ENTDAA sequence, the controller application is informed through
    HAL_I3C_CTRL_TgtReqDynAddrCallback() of the reception of the target payload.
  - And then controller application must send an associated dynamic address through HAL_I3C_CTRL_SetDynAddr().
    This procedure loops automatically in hardware side until a target responds to repeated ENTDAA sequence.
  - The controller application is informed of the end of the procedure at reception of HAL_I3C_CTRL_DAACpltCallback().
  - Then controller application can easily retrieve ENTDAA payload information through
    HAL_I3C_CTRL_Get_ENTDAA_Payload_Info() function.
  - At the end of the procedure, the function HAL_I3C_CTRL_SetConfigBusDevices() must be called to store the target
    capabilities in the hardware register, including dynamic address, IBI support with or without additional data byte,
    Controller-Role request support, or controller automatic stop transfer after IBI.

## Before initiating any IO operation, the controller application must prepare the frame descriptors in transfer
    context with its associated buffer allocation. It is purely software, no i3c handle needed.
    Respect the following steps:
    - Reset the transfer context: HAL_I3C_CTRL_ResetXferCtx().
    - provide ctrl buffer: HAL_I3C_CTRL_InitXferCtxCtrl()
    - provide Tx buffer (if needed): HAL_I3C_CTRL_InitXferCtxCtrl()
    - provide Rx buffer (if needed): HAL_I3C_CTRL_InitXferCtxRx()
    - Build transfer context, Private: HAL_I3C_CTRL_BuildXferCtxPrivate() or CCC: HAL_I3C_CTRL_BuildXferCtxCCC()
    - The built transfer context is now ready to use for controller IO operation. It is not modified by the driver
    during IO operation. It can be reused, stored etc.

## The controller application can check if target device is ready for communication:
    - To check if I3C target device is ready for communication, use the function HAL_I3C_CTRL_IsDeviceI3C_Ready().
    - To check if I2C target device is ready for communication, use the function HAL_I3C_CTRL_IsDeviceI2C_Ready().

## The controller application can generated an arbitration:
    - To send a message header {S + 0x7E + W + STOP}, use the function HAL_I3C_CTRL_GenerateArbitration().

## Controller application can generated patterns:
    - To send a target reset pattern or HDR exit pattern, use the function HAL_I3C_CTRL_GeneratePatterns().

## To insert a target reset pattern before the STOP of a transmitted frame containing a RSTACT CCC command,
    the controller app must enable the reset pattern configuration using HAL_I3C_CTRL_EnableResetPattern()
    before calling HAL_I3C_CTRL_StartXfer().
    To have a standard STOP emitted at the end of a frame containing a RSTACT CCC command, the application must
    disable the reset pattern configuration using HAL_I3C_CTRL_DisableResetPattern() before calling
    HAL_I3C_CTRL_StartXfer.
    Use HAL_I3C_CTRL_IsEnabledResetPattern() to check Reset pattern configuration.

## For I3C IO operations, three operation modes are available within this driver :
  - Controller polling IO operation (blocking):
    - Start transfer in controller mode an amount of a Common Command Code in a direct or a direct receive CCC with
      defbyte or private data in an I2C or I3C communication : HAL_I3C_CTRL_StartXfer().

  - Target polling IO operation (blocking):
    - Transmit in target mode an amount of private data : HAL_I3C_TGT_Transmit()
    - Receive in target mode an amount of private data : HAL_I3C_TGT_Receive()
    - At the end of a transfer, the different FIFO can be flushed if necessary by using HAL_I3C_FlushAllFifo() for
      flush all the FIFO, or flush individually by using HAL_I3C_FlushTxFifo(), HAL_I3C_FlushRxFifo(),
      HAL_I3C_FlushControlFifo(), HAL_I3C_FlushstatusFifo().
    - Request a HotJoin in target mode : HAL_I3C_TGT_HotJoinReq()
    - Request a In Band Interrupt in target mode : HAL_I3C_TGT_IBIReq()
    - Request a Controller Role in target mode : HAL_I3C_TGT_ControlRoleReq()

  - Controller DMA and Interrupt mode IO operation:
    - Transmit and or receive an amount of private data in an I3C or an I2C or a broadcast or a  direct communication
      in non-blocking mode : HAL_I3C_CTRL_StartXfer_IT() or HAL_I3C_CTRL_StartXfer_DMA().
    - At transmission end of transfer, HAL_I3C_CTRL_XferCpltCallback() is executed and user can add his own code
      by overriding this weak callback function or by registering a callback function.

  - Target DMA and Interrupt mode IO operation:
    - Transmit in target mode an amount of private data in an I3C communication : using HAL_I3C_TGT_Transmit_IT() or
      HAL_I3C_TGT_Transmit_DMA().
    - At transmission end of transfer, HAL_I3C_TGT_TxCpltCallback() is executed and user can add his own code
      by overriding this weak callback function or by registering a callback function.
    - Receive in target mode an amount of private data in an I3C communication : HAL_I3C_TGT_Receive_IT() or
      HAL_I3C_TGT_Receive_DMA()
    - At reception end of transfer, HAL_I3C_TGT_RxCpltCallback() is executed and user can add his own code
      by overriding this weak callback function or by registering a callback function.

  - To get asynchronous events : HAL_I3C_CTRL_ActivateNotification() or HAL_I3C_TGT_ActivateNotification().
    Each time one or more event detected by hardware the HAL_I3C_NotifyCallback() is executed user can add his own code
    by overriding this weak callback function or by registering a callback function.
    Then application can easily retrieve some specific associated event data through HAL_I3C_GetCCCInfo() function.

  - At the end of a transfer, all FIFO can be flushed : HAL_I3C_FlushAllFifo(), or individually : HAL_I3C_FlushTxFifo(),
    HAL_I3C_FlushRxFifo(), HAL_I3C_FlushControlFifo(), HAL_I3C_FlushstatusFifo().

  - Request a HotJoin in target mode : HAL_I3C_TGT_HotJoinReq_IT().
    At completion, HAL_I3C_TGT_HotJoinCallback() is executed and user can add his own code by overriding this weak
    callback function or by registering a callback function.

  - Request an In Band Interrupt in target mode : HAL_I3C_TGT_IBIReq_IT()
    At completion, HAL_I3C_NotifyCallback() is executed and users can add their own code by customization of function
    pointer HAL_I3C_NotifyCallback()

  - Request a Controller Role in target mode : HAL_I3C_TGT_ControlRoleReq_IT()
    At completion, HAL_I3C_NotifyCallback() is executed and user can add his own code by overriding this weak  callback
    function or by registering a callback function.

  - To manage the wakeup capability, HAL_TGT_I3C_ActivateNotification() or HAL_I3C_DeactivateNotification() function is
    used for enable/disable wakeup interrupt. At wakeup detection the associated HAL_I3C_NotifyCallback() is executed.

  - In case of transfer Error, HAL_I3C_ErrorCallback() function is executed and user can add his own code by overriding
    this weak callback function or by registering a callback function.

  - Abort an I3C process communication with Interrupt using HAL_I3C_Abort_IT().
    End of abort process, HAL_I3C_AbortCpltCallback() is executed and user can add his own code by overriding this weak
    callback function or by registering a callback function.

## Callback registration
  - When the compilation flag USE_HAL_I3C_REGISTER_CALLBACKS is set to 1, it allows the user to configure dynamically
    the driver callbacks instead of weak functions.

  - When the compilation flag USE_HAL_I3C_REGISTER_CALLBACKS is set to 0 or not defined, the callback registration
    feature is not available and all callbacks are set to the corresponding weak functions.

Default weak value                      | Callback registration function
--------------------------------------- | ------------------------------------------------
HAL_I3C_CTRL_DAACpltCallback()          | HAL_I3C_CTRL_RegisterDAACpltCallback()
HAL_I3C_CTRL_XferCpltCallback()         | HAL_I3C_CTRL_RegisterXferCpltCallback()
HAL_I3C_CTRL_TgtReqDynAddrCallback()    | HAL_I3C_CTRL_RegisterTgtReqDynAddrCallback()
HAL_I3C_TGT_TxCpltCallback()            | HAL_I3C_TGT_RegisterTxCpltCallback()
HAL_I3C_TGT_RxCpltCallback()            | HAL_I3C_TGT_RegisterRxCpltCallback()
HAL_I3C_TGT_HotJoinCallback()           | HAL_I3C_TGT_RegisterHotJoinCallback()
HAL_I3C_NotifyCallback()                | HAL_I3C_RegisterNotifyCallback()
HAL_I3C_AbortCpltCallback()             | HAL_I3C_RegisterAbortCpltCallback()
HAL_I3C_ErrorCallback()                 | HAL_I3C_RegisterErrorCallback()

## Acquire/Release the i3c bus
  - When the compilation flag USE_HAL_MUTEX is set to 1, it allows the user to acquire/reserve the whole I3C bus for
    executing process.
    The HAL Acquire/Release are based on the HAL OS abstraction layer (stm32_hal_os.c/.h osal) :
      - HAL_I3C_AcquireBus() for acquire the bus or wait for it.
      - HAL_I3C_ReleaseBus() for releasing the bus.

  - When the compilation flag USE_HAL_MUTEX is set to 0 or not defined, HAL_I3C_AcquireBus() and HAL_I3C_ReleaseBus()
    are not available.
  */
/**
  * @}
  */

/** @defgroup I3C_Configuration_Table I3C Configuration Table
  * @{

# Configuration inside the I3C driver

Config defines                 | Description           | Default value | Note
------------------------------ | --------------------- | ------------- | --------------------------------------------
USE_HAL_I3C_CLK_ENABLE_MODEL   | stm32h7pxx_hal_conf.h | HAL_CLK_ENABLE_NO | Enable the gating of the periph clk
USE_HAL_I3C_MODULE             | stm32h7pxx_hal_conf.h | 1 | When set, HAL I3C module is enabled
USE_HAL_I3C_DMA                | stm32h7pxx_hal_conf.h | 1 | Enable DMA code inside I3C
USE_HAL_I3C_GET_LAST_ERRORS    | stm32h7pxx_hal_conf.h | 0 | Enable the get last process error
USE_HAL_I3C_USER_DATA          | stm32h7pxx_hal_conf.h | 0 | Enable the set/get user data
USE_HAL_I3C_REGISTER_CALLBACKS | stm32h7pxx_hal_conf.h | 0 | Enable the register callbacks assert
USE_HAL_CHECK_PARAM            | stm32h7pxx_hal_conf.h | 0 | Parameters (pointers or sizes) are checked in runtime
USE_HAL_CHECK_PROCESS_STATE    | stm32h7pxx_hal_conf.h | 0 | Enable atomic access to process state check
USE_HAL_MUTEX                  | stm32h7pxx_hal_conf.h | 0 | Enable the acquire/release bus services
USE_ASSERT_DBG_PARAM           | from PreProcessor env | NA | Enable the params assert
USE_ASSERT_DBG_STATE           | from PreProcessor env | NA | Enable the state assert
  */
/**
  * @}
  */
#if defined(USE_HAL_I3C_MODULE) && (USE_HAL_I3C_MODULE == 1)

/* Private typedef ---------------------------------------------------------------------------------------------------*/
/** @defgroup I3C_Private_Types I3C Private Types
  * @{
  */

/**
  * @brief Structure containing address device and message type used for the private function I3C_Ctrl_IsDevice_Ready()
  */
typedef struct
{
  uint8_t address; /*!< Dynamic or Static target Address */
  uint32_t message_type; /*!< Message Type */
} i3c_device_t;

/**
  * @}
  */

/* Private define ----------------------------------------------------------------------------------------------------*/
/** @defgroup I3C_Private_Constants I3C Private Constants
  * @{
  */

/* Private define to centralize the enable/disable of Interrupts */
#define I3C_CTRL_TX_IT  (LL_I3C_IER_FCIE | LL_I3C_IER_CFNFIE | LL_I3C_IER_TXFNFIE | LL_I3C_IER_ERRIE) /*!< Ctrl TX IT */
#define I3C_CTRL_RX_IT  (LL_I3C_IER_FCIE | LL_I3C_IER_CFNFIE | LL_I3C_IER_RXFNEIE | LL_I3C_IER_ERRIE) /*!< Ctrl RX IT */
#define I3C_CTRL_DAA_IT (LL_I3C_IER_FCIE | LL_I3C_IER_CFNFIE | LL_I3C_IER_TXFNFIE | LL_I3C_IER_ERRIE) /*!< Ctrl DAA IT*/
#define I3C_TGT_TX_IT       (LL_I3C_IER_FCIE | LL_I3C_IER_TXFNFIE | LL_I3C_IER_ERRIE) /*!< Tgt TX IT  */
#define I3C_TGT_RX_IT       (LL_I3C_IER_FCIE | LL_I3C_IER_RXFNEIE | LL_I3C_IER_ERRIE) /*!< Tgt RX IT */
#define I3C_TGT_CTRLROLE_IT (LL_I3C_IER_CRUPDIE | LL_I3C_IER_ERRIE) /*!< Tgt Controller-Role IT */
#define I3C_TGT_HOTJOIN_IT  (LL_I3C_IER_DAUPDIE | LL_I3C_IER_ERRIE) /*!< Tgt Hot-Join IT*/
#define I3C_TGT_IBI_IT      (LL_I3C_IER_IBIENDIE | LL_I3C_IER_ERRIE) /*!< Tgt IBI IT */
#define I3C_XFER_DMA        (LL_I3C_IER_FCIE | LL_I3C_IER_ERRIE) /*!< Tgt or Ctrl DMA IT */

/* Private defines for control buffer prior preparation */

#define I3C_OPERATION_TYPE_MASK     I3C_CR_MTYPE         /*!< Mask can be combined with hal_i3c_xfer_mode_t */
#define I3C_RESTART_STOP_MASK       LL_I3C_GENERATE_STOP /*!< Mask can be combined with hal_i3c_xfer_mode_t */
#define I3C_ARBITRATION_HEADER_MASK I3C_CFGR_NOARBH      /*!< Mask can be combined with hal_i3c_xfer_mode_t */
#define I3C_DEFINE_BYTE_MASK        HAL_I3C_DEFINE_BYTE  /*!< Mask can be combined with hal_i3c_xfer_mode_t */

/**
  * @brief All states
  */
#define I3C_STATE_ALL ( ((uint32_t) HAL_I3C_STATE_INIT)        \
                        | ((uint32_t) HAL_I3C_STATE_IDLE)      \
                        | ((uint32_t) HAL_I3C_STATE_TX)        \
                        | ((uint32_t) HAL_I3C_STATE_RX)        \
                        | ((uint32_t) HAL_I3C_STATE_TX_RX)     \
                        | ((uint32_t) HAL_I3C_STATE_DAA)       \
                        | ((uint32_t) HAL_I3C_STATE_TGT_REQ)   \
                        | ((uint32_t) HAL_I3C_STATE_ABORT) )

/**
  * @brief All states except Init HAL_I3C_STATE_INIT
  */
#define I3C_STATE_ALL_EXCEPT_INIT ( ((uint32_t) HAL_I3C_STATE_IDLE)       \
                                    | ((uint32_t) HAL_I3C_STATE_TX)       \
                                    | ((uint32_t) HAL_I3C_STATE_RX)       \
                                    | ((uint32_t) HAL_I3C_STATE_TX_RX)    \
                                    | ((uint32_t) HAL_I3C_STATE_DAA)      \
                                    | ((uint32_t) HAL_I3C_STATE_TGT_REQ)  \
                                    | ((uint32_t) HAL_I3C_STATE_ABORT) )
/**
  * @brief I3C timing register 1 (I3C_TIMINGR1) valid bit mask
  */
#define I3C_TIMINGR1_VALID_MSK (I3C_TIMINGR1_AVAL_Msk |\
                                I3C_TIMINGR1_ASNCR_Msk | I3C_TIMINGR1_FREE_Msk | I3C_TIMINGR1_SDA_HD_Msk)

/**
  * @}
  */

/* Private macro -----------------------------------------------------------------------------------------------------*/
/** @defgroup I3C_Private_Macros I3C Private Macros
  * @{
  */

/** @brief  Check whether the specified I3C flag is 1UL or 0UL.
  * @param  INSTANCE I3C instance
  * @param  FLAG Flag to check
  * @retval The new state of FLAG (1UL or 0UL)
  */
#define I3C_IS_ACTIVE_FLAG(INSTANCE, FLAG) (((((INSTANCE)->EVR) & (FLAG)) == (FLAG)) ? 1UL : 0UL)

/**
  * @brief Assert macro
  */
#define IS_I3C_MODE(MODE) (((MODE) == HAL_I3C_MODE_NONE) \
                           || ((MODE) == HAL_I3C_MODE_CTRL) \
                           || ((MODE) == HAL_I3C_MODE_TGT))

/**
  * @brief Assert macro
  */
#define IS_I3C_ENTDAA_OPTION(OPTION) (((OPTION) == HAL_I3C_DYN_ADDR_RSTDAA_THEN_ENTDAA) \
                                      || ((OPTION) == HAL_I3C_DYN_ADDR_ONLY_ENTDAA))

/**
  * @brief Assert macro
  */
#define IS_I3C_TX_FIFO_THRESHOLD(VALUE) (((VALUE) == HAL_I3C_TX_FIFO_THRESHOLD_1_4)\
                                         || ((VALUE) == HAL_I3C_TX_FIFO_THRESHOLD_4_4))

/**
  * @brief Assert macro
  */
#define IS_I3C_RX_FIFO_THRESHOLD(VALUE) (((VALUE) == HAL_I3C_RX_FIFO_THRESHOLD_1_4) \
                                         || ((VALUE) == HAL_I3C_RX_FIFO_THRESHOLD_4_4))

/**
  * @brief Assert macro
  */
#define IS_I3C_CTRL_FIFO(CONTROLFIFO) (((CONTROLFIFO) == HAL_I3C_CTRL_FIFO_NONE) \
                                       || ((CONTROLFIFO) == HAL_I3C_CTRL_FIFO_CONTROL_ONLY) \
                                       || ((CONTROLFIFO) == HAL_I3C_CTRL_FIFO_STATUS_ONLY) \
                                       || ((CONTROLFIFO) == HAL_I3C_CTRL_FIFO_ALL))

/**
  * @brief Assert macro
  */
#define IS_I3C_STATUS_FIFO(STATUSFIFO) (((STATUSFIFO) == HAL_I3C_STATUS_FIFO_DISABLED) \
                                        || ((STATUSFIFO) == HAL_I3C_STATUS_FIFO_ENABLED))

/**
  * @brief Assert macro
  */
#define IS_I3C_DEVICE(VALUE) (((VALUE) >= 1U) && ((VALUE) <= 4U))

/**
  * @brief Assert macro
  */
#define IS_I3C_DEVICE_INDEX(VALUE) ((VALUE) <= 3U)

/**
  * @brief Assert macro
  */
#define IS_I3C_DYNAMIC_ADDRESS(VALUE) ((VALUE) <= 0x7FU)

/**
  * @brief Assert macro
  */
#define IS_I3C_HANDOFF_ACTIVITY_STATE(VALUE) (((VALUE) == HAL_I3C_HANDOFF_ACTIVITY_STATE_0) \
                                              || ((VALUE) == HAL_I3C_HANDOFF_ACTIVITY_STATE_1) \
                                              || ((VALUE) == HAL_I3C_HANDOFF_ACTIVITY_STATE_2) \
                                              || ((VALUE) == HAL_I3C_HANDOFF_ACTIVITY_STATE_3))

/**
  * @brief Assert macro
  */
#define IS_I3C_TSCO_TIME(VALUE) (((VALUE) == HAL_I3C_TURNAROUND_TIME_TSCO_LESS_12NS) \
                                 || ((VALUE) == HAL_I3C_TURNAROUND_TIME_TSCO_GREATER_12NS))

/**
  * @brief Assert macro
  */
#define IS_I3C_MAX_SPEED_DATA(VALUE) (((VALUE) == HAL_I3C_GETMXDS_FORMAT_1    ) \
                                      || ((VALUE) == HAL_I3C_GETMXDS_FORMAT_2_LSB) \
                                      || ((VALUE) == HAL_I3C_GETMXDS_FORMAT_2_MID) \
                                      || ((VALUE) == HAL_I3C_GETMXDS_FORMAT_2_MSB))

/**
  * @brief Assert macro
  */
#define IS_I3C_IBI_PAYLOAD_SIZE(VALUE) (((VALUE) == HAL_I3C_PAYLOAD_EMPTY  ) \
                                        || ((VALUE) == HAL_I3C_PAYLOAD_1_BYTE ) \
                                        || ((VALUE) == HAL_I3C_PAYLOAD_2_BYTES) \
                                        || ((VALUE) == HAL_I3C_PAYLOAD_3_BYTES) \
                                        || ((VALUE) == HAL_I3C_PAYLOAD_4_BYTES))

/**
  * @brief Assert macro
  */
#define IS_I3C_MIPI_IDENTIFIER(VALUE) ((VALUE) <= 0x0FU)

/**
  * @brief Assert macro
  */
#define IS_I3C_MAX_READ_TURN_ARROUND(VALUE) ((VALUE) <= 0xFFU)

/**
  * @brief Assert macro
  */
#define I3C_CHECK_IT_SOURCE(IER, IT)  ((((IER) & (IT)) == (IT)) ? 1U : 0UL)

/**
  * @brief Assert macro
  */
#define I3C_CHECK_FLAG(ISR, FLAG) ((((ISR) & (FLAG)) == (FLAG)) ? 1U : 0UL)

/**
  * @brief Assert macro
  */
#define IS_I3C_DMA_SOURCE_BYTE(VALUE) ((VALUE) == HAL_DMA_SRC_DATA_WIDTH_BYTE)

/**
  * @brief Assert macro
  */
#define IS_I3C_DMA_SOURCE_WORD(VALUE) ((VALUE) == HAL_DMA_SRC_DATA_WIDTH_WORD)

/**
  * @brief Assert macro
  */
#define IS_I3C_DMA_DESTINATION_BYTE(VALUE) ((VALUE) == HAL_DMA_DEST_DATA_WIDTH_BYTE)

/**
  * @brief Assert macro
  */
#define IS_I3C_DMA_DESTINATION_WORD(VALUE) ((VALUE) == HAL_DMA_DEST_DATA_WIDTH_WORD)

/**
  * @brief Assert macro
  */
#define IS_I3C_PATTERN(PATTERN) (((PATTERN) == HAL_I3C_PATTERN_TGT_RESET) \
                                 || ((PATTERN) == HAL_I3C_PATTERN_HDR_EXIT))

/**
  * @brief Assert macro
  */
#define IS_I3C_RESET_PATTERN(RSTPTRN) (((RSTPTRN) == HAL_I3C_RESET_PATTERN_ENABLED) \
                                       || ((RSTPTRN) == HAL_I3C_RESET_PATTERN_DISABLED))

/**
  * @brief Assert macro
  */
#define IS_I3C_CTRL_CAPABILITY(CTRLCAP) (((CTRLCAP) == HAL_I3C_CTRL_CAPABILITY_DISABLED) \
                                         || ((CTRLCAP) == HAL_I3C_CTRL_CAPABILITY_ENABLED))

/**
  * @brief Assert macro
  */
#define IS_I3C_IBI_PAYLOAD(IBIPAYLOAD) (((IBIPAYLOAD) == HAL_I3C_IBI_PAYLOAD_DISABLED) \
                                        || ((IBIPAYLOAD) == HAL_I3C_IBI_PAYLOAD_ENABLED))
/**
  * @brief Assert macro
  */
#define IS_I3C_MAX_SPEED_LIMIT(MAX_SPEED) (((MAX_SPEED) == HAL_I3C_MAX_SPEED_LIMITATION_DISABLED) \
                                           || ((MAX_SPEED) == HAL_I3C_MAX_SPEED_LIMITATION_ENABLED))

/**
  * @brief Assert macro
  */
#define IS_I3C_ACK_STALL(ACKSTALL) (((ACKSTALL) == HAL_I3C_ACK_STALL_DISABLED) \
                                    || ((ACKSTALL) == HAL_I3C_ACK_STALL_ENABLED))
/**
  * @brief Assert macro
  */
#define IS_I3C_CCC_STALL(CCCSTALL) (((CCCSTALL) == HAL_I3C_CCC_STALL_DISABLED) \
                                    || ((CCCSTALL) == HAL_I3C_CCC_STALL_ENABLED))
/**
  * @brief Assert macro
  */
#define IS_I3C_TX_STALL(TXSTALL) (((TXSTALL) == HAL_I3C_TX_STALL_DISABLED) \
                                  || ((TXSTALL) == HAL_I3C_TX_STALL_ENABLED))
/**
  * @brief Assert macro
  */
#define IS_I3C_RX_STALL(RXSTALL) (((RXSTALL) == HAL_I3C_RX_STALL_DISABLED) \
                                  || ((RXSTALL) == HAL_I3C_RX_STALL_ENABLED))
/**
  * @brief Assert macro
  */
#define IS_I3C_ACK_I2C_STALL(ACKI2CSTALL) (((ACKI2CSTALL) == HAL_I3C_ACK_ADD_I2C_STALL_DISABLED) \
                                           || ((ACKI2CSTALL) == HAL_I3C_ACK_ADD_I2C_STALL_ENABLED))

/**
  * @brief Assert macro
  */
#define IS_I3C_TX_I2C_STALL(TXI2CSTALL) (((TXI2CSTALL) == HAL_I3C_TX_I2C_STALL_DISABLED) \
                                         || ((TXI2CSTALL) == HAL_I3C_TX_I2C_STALL_ENABLED))

/**
  * @brief Assert macro
  */
#define IS_I3C_RX_I2C_STALL(RXI2CSTALL) (((RXI2CSTALL) == HAL_I3C_RX_I2C_STALL_DISABLED) \
                                         || ((RXI2CSTALL) == HAL_I3C_RX_I2C_STALL_ENABLED))

/**
  * @brief Assert macro
  */
#define IS_I3C_CONTROLLER_ROLE(CTRL_ROLE) (((CTRL_ROLE) == HAL_I3C_CTRL_ROLE_DISABLED) \
                                           || ((CTRL_ROLE) == HAL_I3C_CTRL_ROLE_ENABLED))

/**
  * @brief Assert macro
  */
#define IS_I3C_STOP_XFER(VALUE) (((VALUE) == HAL_I3C_STOP_XFER_DISABLED) \
                                 || ((VALUE) == HAL_I3C_STOP_XFER_ENABLED))

/**
  * @brief Assert macro
  */
#define IS_I3C_HANDOFF_DELAY(HANDOFFDELAY) (((HANDOFFDELAY) == HAL_I3C_HAND_OFF_DELAY_DISABLED) \
                                            || ((HANDOFFDELAY) == HAL_I3C_HAND_OFF_DELAY_ENABLED))

/**
  * @brief Assert macro
  */
#define IS_I3C_IBI(IBI) (((IBI) == HAL_I3C_IBI_REQ_DISABLED) \
                         || ((IBI) == HAL_I3C_IBI_REQ_ENABLED))

/**
  * @brief Assert macro
  */
#define IS_I3C_PENDING_READ(PENDING_READ) (((PENDING_READ) == HAL_I3C_PENDING_READ_MDB_DISABLED) \
                                           || ((PENDING_READ) == HAL_I3C_PENDING_READ_MDB_ENABLED))

/**
  * @brief Assert macro
  */
#define IS_I3C_CTRL_STOP_TRANSFER(STOPTRANSFER) (((STOPTRANSFER) == HAL_I3C_STOP_TRANSFER_DISABLED) \
                                                 || ((STOPTRANSFER) == HAL_I3C_STOP_TRANSFER_ENABLED))

/**
  * @brief Assert macro
  */
#define IS_I3C_PRIVATE_MODE(MODE) (((MODE) == HAL_I3C_PRIVATE_WITH_ARB_STOP) \
                                   || ((MODE) == HAL_I3C_PRIVATE_WITHOUT_ARB_RESTART) \
                                   || ((MODE) == HAL_I3C_PRIVATE_WITHOUT_ARB_STOP) \
                                   || ((MODE) == HAL_I2C_PRIVATE_WITH_ARB_RESTART) \
                                   || ((MODE) == HAL_I2C_PRIVATE_WITH_ARB_STOP) \
                                   || ((MODE) == HAL_I2C_PRIVATE_WITHOUT_ARB_RESTART) \
                                   || ((MODE) == HAL_I2C_PRIVATE_WITHOUT_ARB_STOP))

/**
  * @brief Assert macro
  */
#define IS_I3C_CCC_MODE(MODE) (((MODE) == HAL_I3C_CCC_DIRECT_WITH_DEFBYTE_RESTART) \
                               || ((MODE) == HAL_I3C_CCC_DIRECT_WITH_DEFBYTE_STOP) \
                               || ((MODE) == HAL_I3C_CCC_DIRECT_WITHOUT_DEFBYTE_RESTART) \
                               || ((MODE) == HAL_I3C_CCC_DIRECT_WITHOUT_DEFBYTE_STOP) \
                               || ((MODE) == HAL_I3C_CCC_BROADCAST_WITH_DEFBYTE_RESTART) \
                               || ((MODE) == HAL_I3C_CCC_BROADCAST_WITH_DEFBYTE_STOP) \
                               || ((MODE) == HAL_I3C_CCC_BROADCAST_WITHOUT_DEFBYTE_RESTART) \
                               || ((MODE) == HAL_I3C_CCC_BROADCAST_WITHOUT_DEFBYTE_STOP))


/**
  * @brief Assert macro
  */
#define IS_I3C_DIRECTION(DIRECTION) (((DIRECTION) == HAL_I3C_DIRECTION_WRITE) \
                                     || ((DIRECTION) == HAL_I3C_DIRECTION_READ))


/**
  * @brief Assert macro
  */
#define IS_I3C_DIRECTION_CCC_BROADCAST(DIRECTION) ((DIRECTION) == HAL_I3C_DIRECTION_WRITE)

/**
  * @brief Get I3C cmsis instance from hal handle
  */
#define I3C_GET_INSTANCE(handle) ((I3C_TypeDef *)((uint32_t)((handle)->instance)))
/**
  * @}
  */

/**
  * @brief Wait for approximate delay in us.
  * @param delay_us Delay to wait for (unit: us)
  * @note  Compute number of CPU cycles to wait for, using CMSIS global variable "SystemCoreClock".
  * @note  Delay is approximate (depends on compilation optimization).
  * @note  Computation: variable is divided by 2 to compensate partially CPU processing cycles of wait loop
  *        (total shift right of 21 bits, including conversion from frequency in MHz).
  *        If system core clock frequency is below 500kHz, delay is fulfilled by few CPU processing cycles.
  */
#define I3C_DELAY_US(delay_us) \
  do { \
    volatile uint32_t wait_loop_index = ((delay_us * (SystemCoreClock >> 19U)) >> 2U); \
    while (wait_loop_index != 0U) { \
      wait_loop_index--; \
    } \
  } while(0)

/* Private function prototypes ---------------------------------------------------------------------------------------*/
/** @defgroup I3C_Private_Functions I3C Private Functions
  * @{
  */
static hal_status_t I3C_Tgt_Event_ISR(hal_i3c_handle_t *hi3c, uint32_t it_masks);
static hal_status_t I3C_Ctrl_Event_ISR(hal_i3c_handle_t *hi3c, uint32_t it_masks);
static hal_status_t I3C_Tgt_Tx_ISR(hal_i3c_handle_t *hi3c, uint32_t it_masks);
static hal_status_t I3C_Tgt_Rx_ISR(hal_i3c_handle_t *hi3c, uint32_t it_masks);
#if defined(USE_HAL_I3C_DMA) && (USE_HAL_I3C_DMA == 1)
static hal_status_t I3C_Tgt_Tx_DMA_ISR(hal_i3c_handle_t *hi3c, uint32_t it_masks);
static hal_status_t I3C_Tgt_Rx_DMA_ISR(hal_i3c_handle_t *hi3c, uint32_t it_masks);
#endif /* USE_HAL_I3C_DMA */
static hal_status_t I3C_Tgt_HotJoin_ISR(hal_i3c_handle_t *hi3c, uint32_t it_masks);
static hal_status_t I3C_Tgt_CtrlRole_ISR(hal_i3c_handle_t *hi3c, uint32_t it_masks);
static hal_status_t I3C_Tgt_IBI_ISR(hal_i3c_handle_t *hi3c, uint32_t it_masks);
static hal_status_t I3C_Ctrl_Multiple_Xfer_ISR(hal_i3c_handle_t *hi3c, uint32_t it_masks);
static hal_status_t I3C_Ctrl_Multiple_Xfer_Listen_Event_ISR(hal_i3c_handle_t *hi3c, uint32_t it_masks);
#if defined(USE_HAL_I3C_DMA) && (USE_HAL_I3C_DMA == 1)
static hal_status_t I3C_Ctrl_Multiple_Xfer_DMA_ISR(hal_i3c_handle_t *hi3c, uint32_t it_masks);
#endif /* USE_HAL_I3C_DMA */
static hal_status_t I3C_Ctrl_DAA_ISR(hal_i3c_handle_t *hi3c, uint32_t it_masks);
static hal_status_t I3C_Abort_ISR(hal_i3c_handle_t *hi3c, uint32_t it_masks);
static hal_status_t I3C_WaitForFlagSet(hal_i3c_handle_t *hi3c, uint32_t flag, uint32_t timeout_ms);
static void I3C_TransmitByteTreatment(hal_i3c_handle_t *hi3c);
static void I3C_TransmitWordTreatment(hal_i3c_handle_t *hi3c);
static void I3C_ReceiveByteTreatment(hal_i3c_handle_t *hi3c);
static void I3C_ReceiveWordTreatment(hal_i3c_handle_t *hi3c);
static void I3C_ControlDataTreatment(hal_i3c_handle_t *hi3c);
static void I3C_ErrorTreatment(hal_i3c_handle_t *hi3c);
#if defined(USE_HAL_I3C_GET_LAST_ERRORS) && (USE_HAL_I3C_GET_LAST_ERRORS == 1)
static void I3C_GetErrorSources(hal_i3c_handle_t *hi3c);
#endif /* USE_HAL_I3C_GET_LAST_ERRORS */

static void I3C_StateIdle(hal_i3c_handle_t *hi3c);
#if defined(USE_HAL_I3C_DMA) && (USE_HAL_I3C_DMA == 1)
static void I3C_DMAAbort(hal_dma_handle_t *hdma);
static void I3C_DMAControlTransmitCplt(hal_dma_handle_t *hdma);
static void I3C_DMADataTransmitCplt(hal_dma_handle_t *hdma);
static void I3C_DMADataReceiveCplt(hal_dma_handle_t *hdma);
static void I3C_DMAError(hal_dma_handle_t *hdma);
#endif /* USE_HAL_I3C_DMA */
static hal_status_t I3C_Ctrl_IsDevice_Ready(hal_i3c_handle_t *hi3c, const i3c_device_t *p_device, uint32_t trials,
                                            uint32_t timeout_ms);
static void I3C_TreatErrorCallback(hal_i3c_handle_t *hi3c);
/**
  * @}
  */

/* Exported functions ------------------------------------------------------------------------------------------------*/
/** @addtogroup I3C_Exported_Functions
  * @{
  */

/** @addtogroup I3C_Exported_Functions_Group1 Initialization and de-initialization functions
  * @{
A set of functions allowing to initialize and deinitialize the I3Cx peripheral:
 - HAL_I3C_Init(): initialize the selected device with the I3C instance.
 - HAL_I3C_DeInit(): disable the peripheral.
  */

/**
  * @brief  Initialize the I3C according to the associated handle.
  * @param  hi3c  Pointer to a hal_i3c_handle_t
  * @param  instance  HAL I3C instance
  * @retval HAL_OK  HAL I3C instance has been correctly initialized.
  * @retval HAL_INVALID_PARAM  HAL I3C instance is NULL
  * @retval HAL_ERROR  HAL I3C semaphore creation is failed (USE_HAL_MUTEX is Set to 1)
  */
hal_status_t HAL_I3C_Init(hal_i3c_handle_t *hi3c, hal_i3c_t instance)
{

  ASSERT_DBG_PARAM((hi3c != NULL));
  ASSERT_DBG_PARAM(IS_I3C_ALL_INSTANCE((I3C_TypeDef *)((uint32_t)instance)));

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (hi3c == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  hi3c->instance = instance;

#if defined(USE_HAL_I3C_REGISTER_CALLBACKS) && (USE_HAL_I3C_REGISTER_CALLBACKS == 1)
  /* Set I3C Callbacks to the weak function */
  hi3c->p_ctrl_xfer_cplt_cb = HAL_I3C_CTRL_XferCpltCallback;
  hi3c->p_ctrl_daa_cplt_cb = HAL_I3C_CTRL_DAACpltCallback;
  hi3c->p_ctrl_tgt_req_dyn_addr_cb = HAL_I3C_CTRL_TgtReqDynAddrCallback;
  hi3c->p_tgt_tx_cplt_cb = HAL_I3C_TGT_TxCpltCallback;
  hi3c->p_tgt_rx_cplt_cb = HAL_I3C_TGT_RxCpltCallback;
  hi3c->p_tgt_hot_join_cb = HAL_I3C_TGT_HotJoinCallback;
  hi3c->p_notify_cb = HAL_I3C_NotifyCallback;
  hi3c->p_error_cb = HAL_I3C_ErrorCallback;
  hi3c->p_abort_cplt_cb = HAL_I3C_AbortCpltCallback;
#endif /* USE_HAL_I3C_REGISTER_CALLBACKS */

  hi3c->mode = HAL_I3C_MODE_NONE;
  hi3c->listen = HAL_I3C_LISTEN_DISABLED;

#if defined(USE_HAL_I3C_GET_LAST_ERRORS) && (USE_HAL_I3C_GET_LAST_ERRORS == 1)
  hi3c->last_error_codes = HAL_I3C_ERROR_NONE;
#endif /* USE_HAL_I3C_GET_LAST_ERRORS */

#if defined(USE_HAL_I3C_DMA) && (USE_HAL_I3C_DMA == 1)
  hi3c->hdma_tx = (hal_dma_handle_t *) NULL;
  hi3c->hdma_rx = (hal_dma_handle_t *) NULL;
  hi3c->hdma_ctrl = (hal_dma_handle_t *) NULL;
#endif /* USE_HAL_I3C_DMA */

#if defined(USE_HAL_I3C_USER_DATA) && (USE_HAL_I3C_USER_DATA == 1)
  hi3c->p_user_data = (void *) NULL;
#endif /* USE_HAL_I3C_USER_DATA */

#if defined(USE_HAL_I3C_CLK_ENABLE_MODEL) && (USE_HAL_I3C_CLK_ENABLE_MODEL > HAL_CLK_ENABLE_NO)
  /* Enable I3Cx Clock */
  switch (instance)
  {
    case HAL_I3C1:
      HAL_RCC_I3C1_EnableClock();
      break;
    default:
      break;
  }
#endif /* USE_HAL_I3C_CLK_ENABLE_MODEL > HAL_CLK_ENABLE_NO */

#if defined(USE_HAL_MUTEX) && (USE_HAL_MUTEX == 1)
  if (HAL_OS_SemaphoreCreate(&hi3c->semaphore) != HAL_OS_OK)
  {
    return HAL_ERROR;
  }
#endif /* USE_HAL_MUTEX */

  /* Update I3C state */
  hi3c->global_state = HAL_I3C_STATE_INIT;

  return HAL_OK;
}

/**
  * @brief  Deinitialize the HAL I3C driver for the given handle and disable the peripheral.
  * @param  hi3c  Pointer to a hal_i3c_handle_t structure
  */
void HAL_I3C_DeInit(hal_i3c_handle_t *hi3c)
{
  I3C_TypeDef *p_i3cx;

  ASSERT_DBG_PARAM((hi3c != NULL));
  p_i3cx = I3C_GET_INSTANCE(hi3c);
  ASSERT_DBG_PARAM(IS_I3C_ALL_INSTANCE(p_i3cx));

  LL_I3C_Disable(p_i3cx);

#if defined(USE_HAL_MUTEX) && (USE_HAL_MUTEX == 1)
  (void) HAL_OS_SemaphoreDelete(&hi3c->semaphore);
#endif /* USE_HAL_MUTEX */

  hi3c->global_state = HAL_I3C_STATE_RESET;
}

/**
  * @}
  */

/** @addtogroup I3C_Exported_Functions_Group2 Configuration functions
  * @{
A set of functions allowing to configure the I3Cx peripheral:

- Global configuration (controller):
  - HAL_I3C_CTRL_SetConfig()
  - HAL_I3C_CTRL_GetConfig()

- Global configuration (target):
  - HAL_I3C_TGT_SetConfig()
  - HAL_I3C_TGT_GetConfig()

- Payload ENTDAA configuration (target):
  - HAL_I3C_TGT_SetPayloadENTDAAConfig()
  - HAL_I3C_TGT_GetPayloadENTDAAConfig()

- FIFO configuration (target):
  - HAL_I3C_TGT_SetConfigFifo()
  - HAL_I3C_TGT_GetConfigFifo()
- FIFO configuration (controller):
  - HAL_I3C_CTRL_GetConfigFifo()
  - HAL_I3C_CTRL_SetConfigFifo()

- FIFO configuration unitary functions:
  - HAL_I3C_SetRxFifoThreshold()
  - HAL_I3C_GetRxFifoThreshold()
  - HAL_I3C_SetTxFifoThreshold()
  - HAL_I3C_GetTxFifoThreshold()
  - HAL_I3C_CTRL_EnableControlFifo()
  - HAL_I3C_CTRL_DisableControlFifo()
  - HAL_I3C_CTRL_IsEnabledControlFifo()
  - HAL_I3C_CTRL_EnableStatusFifo()
  - HAL_I3C_CTRL_DisableStatusFifo()
  - HAL_I3C_CTRL_IsEnabledStatusFifo()

- Own dynamic address (controller):
  - HAL_I3C_CTRL_SetConfigOwnDynamicAddress()
  - HAL_I3C_CTRL_GetConfigOwnAddress()

- Hot-Join allowed (controller):
  - HAL_I3C_CTRL_EnableHotJoinAllowed()
  - HAL_I3C_CTRL_DisableHotJoinAllowed()
  - HAL_I3C_CTRL_IsEnabledHotJoinAllowed()

- High keeper SDA configuration (controller):
  - HAL_I3C_CTRL_EnableHighKeeperSDA()
  - HAL_I3C_CTRL_DisableHighKeeperSDA()
  - HAL_I3C_CTRL_IsEnabledHighKeeperSDA()

- Stall time configuration (controller):
  - HAL_I3C_CTRL_SetConfigStallTime()
  - HAL_I3C_CTRL_GetConfigStallTime()

- Controller-Role request configuration (target):
  - HAL_I3C_TGT_EnableCtrlRoleRequest()
  - HAL_I3C_TGT_DisableCtrlRoleRequest()
  - HAL_I3C_TGT_IsEnabledCtrlRoleRequest()

- Group management support configuration (target):
  - HAL_I3C_TGT_EnableGroupAddrCapability()
  - HAL_I3C_TGT_DisableGroupAddrCapability()
  - HAL_I3C_TGT_IsEnabledGroupAddrCapability()

- Hot-Join configuration (target):
  - HAL_I3C_TGT_EnableHotJoinRequest()
  - HAL_I3C_TGT_DisableHotJoinRequest()
  - HAL_I3C_TGT_IsEnabledHotJoinRequest()

- In-Band Interrupt configuration (target):
  - HAL_I3C_TGT_EnableIBI()
  - HAL_I3C_TGT_DisableIBI()
  - HAL_I3C_TGT_IsEnabledIBI()
  - HAL_I3C_TGT_GetConfigIBI()

- Max data size configuration (target):
  - HAL_I3C_TGT_SetConfigMaxDataSize()
  - HAL_I3C_TGT_GetConfigMaxDataSize()

- GET MaX Data Speed (GETMXDS) configuration (target):
  - HAL_I3C_TGT_SetConfigGETMXDS()
  - HAL_I3C_TGT_GetConfigGETMXDS()
  - HAL_I3C_TGT_SetConfigGETMXDS_Format()
  - HAL_I3C_TGT_GetConfigGETMXDS_Format()
  - HAL_I3C_TGT_SetConfigCtrlHandOffActivity()
  - HAL_I3C_TGT_GetConfigCtrlHandOffActivity()

- Bus device configuration configuration (controller):
  - HAL_I3C_CTRL_SetConfigBusDevices()
  - HAL_I3C_CTRL_GetConfigBusDevices()


- Reset pattern configuration (Controller):
  - HAL_I3C_CTRL_EnableResetPattern()
  - HAL_I3C_CTRL_DisableResetPattern()
  - HAL_I3C_CTRL_IsEnabledResetPattern()
  */

/**
  * @brief  Configure the I3C as controller.
  * @param  hi3c  Pointer to a hal_i3c_handle_t
  * @param  p_config  Pointer to the configuration structure
  * @retval HAL_OK  Operation completed successfully
  * @retval HAL_INVALID_PARAM  Invalid parameter
  */
hal_status_t HAL_I3C_CTRL_SetConfig(hal_i3c_handle_t *hi3c, const hal_i3c_ctrl_config_t *p_config)
{
  I3C_TypeDef *p_i3cx;

  ASSERT_DBG_PARAM((hi3c != NULL));
  ASSERT_DBG_PARAM((p_config != NULL));
  ASSERT_DBG_PARAM(((p_config->timing_reg1 & ~I3C_TIMINGR1_VALID_MSK) == 0));
  ASSERT_DBG_STATE(hi3c->global_state, (uint32_t)HAL_I3C_STATE_INIT | (uint32_t)HAL_I3C_STATE_IDLE);

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (p_config == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  p_i3cx = I3C_GET_INSTANCE(hi3c);
  LL_I3C_Disable(p_i3cx);
  LL_I3C_SetMode(p_i3cx, LL_I3C_MODE_CONTROLLER);
  hi3c->mode = HAL_I3C_MODE_CTRL;

  /* SCL signal waveform configuration: I3C timing register 0 (I3C_TIMINGR0) */
  LL_I3C_ConfigClockWaveForm(p_i3cx, p_config->timing_reg0);

  /* Timing configuration: I3C timing register 1 (I3C_TIMINGR1) */
  LL_I3C_SetBusCharacteristic(p_i3cx, p_config->timing_reg1);

  LL_I3C_Enable(p_i3cx);
  hi3c->global_state = HAL_I3C_STATE_IDLE;

  return HAL_OK;
}

/**
  * @brief  Retrieve the I3C controller configuration.
  * @param  hi3c  Pointer to a hal_i3c_handle_t
  * @param  p_config  Pointer to the configuration structure
  * @note   This configuration can be retrieved when the I3C is acting as controller.
  */
void HAL_I3C_CTRL_GetConfig(const hal_i3c_handle_t *hi3c, hal_i3c_ctrl_config_t *p_config)
{
  I3C_TypeDef *p_i3cx;

  ASSERT_DBG_PARAM((hi3c != NULL));
  ASSERT_DBG_PARAM((p_config != NULL));
  ASSERT_DBG_PARAM(hi3c->mode == HAL_I3C_MODE_CTRL);
  ASSERT_DBG_STATE(hi3c->global_state, I3C_STATE_ALL_EXCEPT_INIT);

  p_i3cx = I3C_GET_INSTANCE(hi3c);
  p_config->timing_reg0 = LL_I3C_GetClockWaveForm(p_i3cx);
  p_config->timing_reg1 = LL_I3C_GetBusCharacteristic(p_i3cx);
}

/**
  * @brief  Configure the I3C as target.
  * @param  hi3c  Pointer to a hal_i3c_handle_t
  * @param  p_config  Pointer to the configuration structure
  * @retval HAL_OK  Operation completed successfully
  * @retval HAL_INVALID_PARAM  Invalid parameter
  */
hal_status_t HAL_I3C_TGT_SetConfig(hal_i3c_handle_t *hi3c, const hal_i3c_tgt_config_t *p_config)
{
  I3C_TypeDef *p_i3cx;

  ASSERT_DBG_PARAM((hi3c != NULL));
  ASSERT_DBG_PARAM((p_config != NULL));
  ASSERT_DBG_PARAM(((p_config->timing_reg1 & ~I3C_TIMINGR1_VALID_MSK) == 0));
  ASSERT_DBG_STATE(hi3c->global_state, (uint32_t)HAL_I3C_STATE_INIT | (uint32_t)HAL_I3C_STATE_IDLE);

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (p_config == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  p_i3cx = I3C_GET_INSTANCE(hi3c);
  LL_I3C_Disable(p_i3cx);
  LL_I3C_SetMode(p_i3cx, LL_I3C_MODE_TARGET);
  hi3c->mode = HAL_I3C_MODE_TGT;

  /* Timing configuration: I3C timing register 1 (I3C_TIMINGR1) */
  LL_I3C_SetBusCharacteristic(p_i3cx, p_config->timing_reg1);

  LL_I3C_Enable(p_i3cx);
  hi3c->global_state = HAL_I3C_STATE_IDLE;

  return HAL_OK;
}

/**
  * @brief  Retrieve the I3C target configuration.
  * @param  hi3c  Pointer to a hal_i3c_handle_t
  * @param  p_config  Pointer to the configuration structure
  * @note   This configuration can be retrieved when the I3C is acting as target.
  */
void HAL_I3C_TGT_GetConfig(const hal_i3c_handle_t *hi3c, hal_i3c_tgt_config_t *p_config)
{
  I3C_TypeDef *p_i3cx;

  ASSERT_DBG_PARAM((hi3c != NULL));
  ASSERT_DBG_PARAM((p_config != NULL));
  ASSERT_DBG_PARAM(hi3c->mode == HAL_I3C_MODE_TGT);
  ASSERT_DBG_STATE(hi3c->global_state, I3C_STATE_ALL_EXCEPT_INIT);

  p_i3cx = I3C_GET_INSTANCE(hi3c);
  p_config->timing_reg1 = LL_I3C_GetBusCharacteristic(p_i3cx);
}

/**
  * @brief  Set payload ENTDAA configuration.
  * @param  hi3c  Pointer to a hal_i3c_handle_t
  * @param  p_config  Pointer to the configuration structure
  * @note   This configuration can be set when the I3C is acting as target.
  * @retval HAL_OK  Operation completed successfully
  * @retval HAL_INVALID_PARAM  Invalid parameter
  */
hal_status_t HAL_I3C_TGT_SetPayloadENTDAAConfig(const hal_i3c_handle_t *hi3c,
                                                const hal_i3c_tgt_config_payload_entdaa_t *p_config)
{
  I3C_TypeDef *p_i3cx;
  uint32_t bcr_value;

  ASSERT_DBG_PARAM((hi3c != NULL));
  ASSERT_DBG_PARAM((p_config != NULL));
  ASSERT_DBG_PARAM(IS_I3C_CTRL_CAPABILITY(p_config->ctrl_capability));
  ASSERT_DBG_PARAM(IS_I3C_IBI_PAYLOAD(p_config->ibi_payload));
  ASSERT_DBG_PARAM(IS_I3C_MAX_SPEED_LIMIT(p_config->max_speed_limitation));
  ASSERT_DBG_PARAM(hi3c->mode == HAL_I3C_MODE_TGT);
  ASSERT_DBG_STATE(hi3c->global_state, HAL_I3C_STATE_IDLE);

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (p_config == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  p_i3cx = I3C_GET_INSTANCE(hi3c);
  LL_I3C_Disable(p_i3cx);
  /* Set identifier value in DCR register */
  LL_I3C_SetDeviceCharacteristics(p_i3cx, p_config->identifier);
  /* Set MIPI identifier value in EPIDR register */
  LL_I3C_SetMIPIInstanceID(p_i3cx, p_config->mipi_identifier);

  bcr_value = (((uint32_t)p_config->max_speed_limitation << I3C_BCR_BCR0_Pos) |
               ((uint32_t)p_config->ibi_payload << I3C_BCR_BCR2_Pos)          |
               ((uint32_t)p_config->ctrl_capability << I3C_BCR_BCR6_Pos));

  /* Set control capability, IBI payload support and max speed limitation in BCR register */
  LL_I3C_ConfigPayloadEntDAA(p_i3cx, bcr_value);
  LL_I3C_Enable(p_i3cx);

  return HAL_OK;
}

/**
  * @brief  Retrieve payload ENTDAA configuration.
  * @param  hi3c  Pointer to a hal_i3c_handle_t
  * @param  p_config  Pointer to the configuration structure
  * @note   This configuration can be set when the I3C is acting as target.
  */
void HAL_I3C_TGT_GetPayloadENTDAAConfig(const hal_i3c_handle_t *hi3c, hal_i3c_tgt_config_payload_entdaa_t *p_config)
{
  I3C_TypeDef *p_i3cx;
  uint32_t bcr_value;

  ASSERT_DBG_PARAM((hi3c != NULL));
  ASSERT_DBG_PARAM((p_config != NULL));
  ASSERT_DBG_PARAM(hi3c->mode == HAL_I3C_MODE_TGT);
  ASSERT_DBG_STATE(hi3c->global_state, I3C_STATE_ALL_EXCEPT_INIT);

  p_i3cx = I3C_GET_INSTANCE(hi3c);
  /* Get identifier value in DCR register */
  p_config->identifier = (uint8_t) LL_I3C_GetDeviceCharacteristics(p_i3cx);
  /* Get MIPI identifier value in EPIDR register */
  p_config->mipi_identifier = (uint8_t) LL_I3C_GetMIPIInstanceID(p_i3cx);

  bcr_value = LL_I3C_READ_REG(p_i3cx, BCR);

  p_config->max_speed_limitation = (hal_i3c_max_speed_limit_status_t)((uint32_t)((bcr_value & I3C_BCR_BCR0)
                                                                                 >> I3C_BCR_BCR0_Pos));

  p_config->ibi_payload = (hal_i3c_ibi_payload_status_t)((uint32_t)((bcr_value & I3C_BCR_BCR2) >> I3C_BCR_BCR2_Pos));

  p_config->ctrl_capability = (hal_i3c_ctrl_capability_status_t)((uint32_t)((bcr_value & I3C_BCR_BCR6)
                                                                            >> I3C_BCR_BCR6_Pos));
}

/**
  * @brief  Set FIFO configuration when the I3C is acting as controller.
  * @param  hi3c  Pointer to a hal_i3c_handle_t
  * @param  p_config  Pointer to the configuration structure
  * @retval HAL_OK  Operation completed successfully
  * @retval HAL_INVALID_PARAM  Invalid parameter
  */
hal_status_t HAL_I3C_CTRL_SetConfigFifo(const hal_i3c_handle_t *hi3c, const hal_i3c_ctrl_fifo_config_t *p_config)
{
  I3C_TypeDef *p_i3cx;
  uint32_t cfgr_value;
  uint32_t cfgr_mask;

  ASSERT_DBG_PARAM((hi3c != NULL));
  ASSERT_DBG_PARAM((p_config != NULL));
  ASSERT_DBG_PARAM(IS_I3C_RX_FIFO_THRESHOLD(p_config->rx_fifo_threshold));
  ASSERT_DBG_PARAM(IS_I3C_TX_FIFO_THRESHOLD(p_config->tx_fifo_threshold));
  ASSERT_DBG_PARAM(IS_I3C_CTRL_FIFO(p_config->ctrl_fifo));
  ASSERT_DBG_PARAM(hi3c->mode == HAL_I3C_MODE_CTRL);
  ASSERT_DBG_STATE(hi3c->global_state, HAL_I3C_STATE_IDLE);

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (p_config == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  p_i3cx = I3C_GET_INSTANCE(hi3c);
  /* Set Tx and Rx Fifo threshold and enable fifo control and status */
  cfgr_value = (uint32_t)p_config->tx_fifo_threshold | (uint32_t)p_config->rx_fifo_threshold |
               (uint32_t)p_config->ctrl_fifo;
  cfgr_mask = I3C_CFGR_TXTHRES | I3C_CFGR_RXTHRES | I3C_CFGR_TMODE | I3C_CFGR_SMODE;

  STM32_MODIFY_REG(p_i3cx->CFGR, cfgr_mask, cfgr_value);

  return HAL_OK;
}

/**
  * @brief  Set FIFO configuration when the I3C is acting as target.
  * @param  hi3c  Pointer to a hal_i3c_handle_t
  * @param  p_config  Pointer to the configuration structure
  * @retval HAL_OK  Operation completed successfully
  * @retval HAL_INVALID_PARAM  Invalid parameter
  */
hal_status_t HAL_I3C_TGT_SetConfigFifo(const hal_i3c_handle_t *hi3c, const hal_i3c_tgt_fifo_config_t *p_config)
{
  I3C_TypeDef *p_i3cx;
  uint32_t cfgr_value;
  uint32_t cfgr_mask;

  ASSERT_DBG_PARAM((hi3c != NULL));
  ASSERT_DBG_PARAM((p_config != NULL));
  ASSERT_DBG_PARAM(IS_I3C_RX_FIFO_THRESHOLD(p_config->rx_fifo_threshold));
  ASSERT_DBG_PARAM(IS_I3C_TX_FIFO_THRESHOLD(p_config->tx_fifo_threshold));
  ASSERT_DBG_PARAM(hi3c->mode == HAL_I3C_MODE_TGT);
  ASSERT_DBG_STATE(hi3c->global_state, HAL_I3C_STATE_IDLE);

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (p_config == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */
  p_i3cx = I3C_GET_INSTANCE(hi3c);
  /* Set Tx and Rx Fifo threshold */
  cfgr_value = (uint32_t) p_config->tx_fifo_threshold | (uint32_t)p_config->rx_fifo_threshold;
  cfgr_mask = I3C_CFGR_TXTHRES | I3C_CFGR_RXTHRES;

  STM32_MODIFY_REG(p_i3cx->CFGR, cfgr_mask, cfgr_value);

  return HAL_OK;
}

/**
  * @brief  Retrieve FIFO configuration when the I3C is acting as controller.
  * @param  hi3c  Pointer to a hal_i3c_handle_t
  * @param  p_config  Pointer to the configuration structure
  */
void HAL_I3C_CTRL_GetConfigFifo(const hal_i3c_handle_t *hi3c, hal_i3c_ctrl_fifo_config_t *p_config)
{
  I3C_TypeDef *p_i3cx;

  ASSERT_DBG_PARAM((hi3c != NULL));
  ASSERT_DBG_PARAM((p_config != NULL));
  ASSERT_DBG_PARAM(hi3c->mode == HAL_I3C_MODE_CTRL);
  ASSERT_DBG_STATE(hi3c->global_state, I3C_STATE_ALL_EXCEPT_INIT);

  p_i3cx = I3C_GET_INSTANCE(hi3c);
  p_config->ctrl_fifo = (hal_i3c_ctrl_fifo_t)(uint32_t) STM32_READ_BIT(p_i3cx->CFGR, (I3C_CFGR_SMODE | I3C_CFGR_TMODE));
  p_config->tx_fifo_threshold = (hal_i3c_tx_fifo_threshold_t) LL_I3C_GetTxFIFOThreshold(p_i3cx);
  p_config->rx_fifo_threshold = (hal_i3c_rx_fifo_threshold_t) LL_I3C_GetRxFIFOThreshold(p_i3cx);
}

/**
  * @brief  Retrieve FIFO configuration when the I3C is acting as target.
  * @param  hi3c  Pointer to a hal_i3c_handle_t
  * @param  p_config  Pointer to the configuration structure
  */
void HAL_I3C_TGT_GetConfigFifo(const hal_i3c_handle_t *hi3c, hal_i3c_tgt_fifo_config_t *p_config)
{
  I3C_TypeDef *p_i3cx;

  ASSERT_DBG_PARAM((hi3c != NULL));
  ASSERT_DBG_PARAM((p_config != NULL));
  ASSERT_DBG_PARAM(hi3c->mode == HAL_I3C_MODE_TGT);
  ASSERT_DBG_STATE(hi3c->global_state, I3C_STATE_ALL_EXCEPT_INIT);

  p_i3cx = I3C_GET_INSTANCE(hi3c);
  p_config->tx_fifo_threshold = (hal_i3c_tx_fifo_threshold_t) LL_I3C_GetTxFIFOThreshold(p_i3cx);
  p_config->rx_fifo_threshold = (hal_i3c_rx_fifo_threshold_t) LL_I3C_GetRxFIFOThreshold(p_i3cx);
}

/**
  * @brief  Set the Receive FIFO Threshold level configuration.
  * @param  hi3c  Pointer to a hal_i3c_handle_t
  * @param  threshold the Rx FIFO threshold
  * @retval HAL_OK  Operation completed successfully
  */
hal_status_t HAL_I3C_SetRxFifoThreshold(const hal_i3c_handle_t *hi3c, const hal_i3c_rx_fifo_threshold_t threshold)
{
  I3C_TypeDef *p_i3cx;

  ASSERT_DBG_PARAM((hi3c != NULL));
  ASSERT_DBG_PARAM(IS_I3C_RX_FIFO_THRESHOLD(threshold));
  ASSERT_DBG_STATE(hi3c->global_state, HAL_I3C_STATE_IDLE);

  p_i3cx = I3C_GET_INSTANCE(hi3c);
  LL_I3C_SetRxFIFOThreshold(p_i3cx, (uint32_t)threshold);

  return HAL_OK;
}

/**
  * @brief  Get the receive FIFO threshold level configuration.
  * @param  hi3c  Pointer to a hal_i3c_handle_t
  * @retval HAL_I3C_RX_FIFO_THRESHOLD_1_4  Rx Fifo Threshold is 1 byte.
  * @retval HAL_I3C_RX_FIFO_THRESHOLD_4_4  Rx Fifo Threshold is 4 bytes.
  */
hal_i3c_rx_fifo_threshold_t HAL_I3C_GetRxFifoThreshold(const hal_i3c_handle_t *hi3c)
{
  I3C_TypeDef *p_i3cx;

  ASSERT_DBG_PARAM((hi3c != NULL));
  ASSERT_DBG_STATE(hi3c->global_state, I3C_STATE_ALL_EXCEPT_INIT);

  p_i3cx = I3C_GET_INSTANCE(hi3c);
  return (hal_i3c_rx_fifo_threshold_t) LL_I3C_GetRxFIFOThreshold(p_i3cx);
}

/**
  * @brief  Set the TX FIFO Threshold level configuration.
  * @param  hi3c  Pointer to a hal_i3c_handle_t
  * @param  threshold the Tx FIFO threshold
  * @retval HAL_OK  Operation completed successfully
  */
hal_status_t HAL_I3C_SetTxFifoThreshold(const hal_i3c_handle_t *hi3c, const hal_i3c_tx_fifo_threshold_t threshold)
{
  I3C_TypeDef *p_i3cx;

  ASSERT_DBG_PARAM((hi3c != NULL));
  ASSERT_DBG_PARAM(IS_I3C_TX_FIFO_THRESHOLD(threshold));
  ASSERT_DBG_STATE(hi3c->global_state, HAL_I3C_STATE_IDLE);

  p_i3cx = I3C_GET_INSTANCE(hi3c);
  LL_I3C_SetTxFIFOThreshold(p_i3cx, (uint32_t)threshold);

  return HAL_OK;
}

/**
  * @brief  Get the TX FIFO Threshold level configuration.
  * @param  hi3c  Pointer to a hal_i3c_handle_t
  * @retval HAL_I3C_TX_FIFO_THRESHOLD_1_4  Tx Fifo Threshold is 1 byte
  * @retval HAL_I3C_TX_FIFO_THRESHOLD_4_4  Tx Fifo Threshold is 4 bytes
  */
hal_i3c_tx_fifo_threshold_t HAL_I3C_GetTxFifoThreshold(const hal_i3c_handle_t *hi3c)
{
  I3C_TypeDef *p_i3cx;

  ASSERT_DBG_PARAM((hi3c != NULL));
  ASSERT_DBG_STATE(hi3c->global_state, I3C_STATE_ALL_EXCEPT_INIT);

  p_i3cx = I3C_GET_INSTANCE(hi3c);

  return (hal_i3c_tx_fifo_threshold_t)LL_I3C_GetTxFIFOThreshold(p_i3cx);
}

/**
  * @brief  Enable the Control FIFO.
  * @param  hi3c  Pointer to a hal_i3c_handle_t
  * @note   This configuration can be set when the I3C is acting as controller.
  * @retval HAL_OK  Operation completed successfully
  */
hal_status_t HAL_I3C_CTRL_EnableControlFifo(hal_i3c_handle_t *hi3c)
{
  ASSERT_DBG_PARAM((hi3c != NULL));
  ASSERT_DBG_PARAM(hi3c->mode == HAL_I3C_MODE_CTRL);
  ASSERT_DBG_STATE(hi3c->global_state, HAL_I3C_STATE_IDLE);

  LL_I3C_EnableControlFIFO(I3C_GET_INSTANCE(hi3c));

  return HAL_OK;
}

/**
  * @brief  Disable the Control FIFO.
  * @param  hi3c  Pointer to a hal_i3c_handle_t
  * @note   This configuration can be set when the I3C is acting as controller.
  * @retval HAL_OK  Operation completed successfully
  */
hal_status_t HAL_I3C_CTRL_DisableControlFifo(hal_i3c_handle_t *hi3c)
{
  ASSERT_DBG_PARAM((hi3c != NULL));
  ASSERT_DBG_PARAM(hi3c->mode == HAL_I3C_MODE_CTRL);
  ASSERT_DBG_STATE(hi3c->global_state, HAL_I3C_STATE_IDLE);

  LL_I3C_DisableControlFIFO(I3C_GET_INSTANCE(hi3c));

  return HAL_OK;
}

/**
  * @brief  Check if the Control FIFO is enabled.
  * @param  hi3c  Pointer to a hal_i3c_handle_t
  * @note   This configuration can be set when the I3C is acting as controller.
  * @retval HAL_I3C_CONTROL_FIFO_DISABLED  Control FIFO mode disabled
  * @retval HAL_I3C_CONTROL_FIFO_ENABLED   Control FIFO mode enabled
  */
hal_i3c_control_fifo_status_t HAL_I3C_CTRL_IsEnabledControlFifo(const hal_i3c_handle_t *hi3c)
{
  ASSERT_DBG_PARAM((hi3c != NULL));
  ASSERT_DBG_PARAM(hi3c->mode == HAL_I3C_MODE_CTRL);
  ASSERT_DBG_STATE(hi3c->global_state, I3C_STATE_ALL_EXCEPT_INIT);

  return (hal_i3c_control_fifo_status_t) LL_I3C_IsEnabledControlFIFO(I3C_GET_INSTANCE(hi3c));
}

/**
  * @brief  Enable the Status FIFO.
  * @param  hi3c  Pointer to a hal_i3c_handle_t
  * @note   This configuration can be set when the I3C is acting as controller.
  * @retval HAL_OK  Operation completed successfully
  */
hal_status_t HAL_I3C_CTRL_EnableStatusFifo(hal_i3c_handle_t *hi3c)
{
  ASSERT_DBG_PARAM((hi3c != NULL));
  ASSERT_DBG_PARAM(hi3c->mode == HAL_I3C_MODE_CTRL);
  ASSERT_DBG_STATE(hi3c->global_state, HAL_I3C_STATE_IDLE);

  LL_I3C_EnableStatusFIFO(I3C_GET_INSTANCE(hi3c));

  return HAL_OK;
}

/**
  * @brief  Disable the Status FIFO.
  * @param  hi3c  Pointer to a hal_i3c_handle_t
  * @note   This configuration can be set when the I3C is acting as controller.
  * @retval HAL_OK  Operation completed successfully
  */
hal_status_t HAL_I3C_CTRL_DisableStatusFifo(hal_i3c_handle_t *hi3c)
{
  ASSERT_DBG_PARAM((hi3c != NULL));
  ASSERT_DBG_PARAM(hi3c->mode == HAL_I3C_MODE_CTRL);
  ASSERT_DBG_STATE(hi3c->global_state, HAL_I3C_STATE_IDLE);

  LL_I3C_DisableStatusFIFO(I3C_GET_INSTANCE(hi3c));

  return HAL_OK;
}

/**
  * @brief  Check if the Status FIFO is enabled.
  * @param  hi3c  Pointer to a hal_i3c_handle_t
  * @note   This configuration can be set when the I3C is acting as controller.
  * @retval HAL_I3C_STATUS_FIFO_DISABLED  Status FIFO mode disabled
  * @retval HAL_I3C_STATUS_FIFO_ENABLED   Status FIFO mode enabled
  */
hal_i3c_status_fifo_status_t HAL_I3C_CTRL_IsEnabledStatusFifo(const hal_i3c_handle_t *hi3c)
{
  ASSERT_DBG_PARAM((hi3c != NULL));
  ASSERT_DBG_PARAM(hi3c->mode == HAL_I3C_MODE_CTRL);
  ASSERT_DBG_STATE(hi3c->global_state, I3C_STATE_ALL_EXCEPT_INIT);

  return (hal_i3c_status_fifo_status_t) LL_I3C_IsEnabledStatusFIFO(I3C_GET_INSTANCE(hi3c));
}

/**
  * @brief  Set dynamic address value.
  * @param  hi3c  Pointer to a hal_i3c_handle_t
  * @param  dynamic_address  Dynamic address
  * @note   This configuration can be set when the I3C is acting as controller.
  * @retval HAL_OK  Operation completed successfully
  */
hal_status_t HAL_I3C_CTRL_SetConfigOwnDynamicAddress(hal_i3c_handle_t *hi3c, uint32_t dynamic_address)
{
  ASSERT_DBG_PARAM((hi3c != NULL));
  ASSERT_DBG_PARAM(IS_I3C_DYNAMIC_ADDRESS(dynamic_address));
  ASSERT_DBG_PARAM(hi3c->mode == HAL_I3C_MODE_CTRL);
  ASSERT_DBG_STATE(hi3c->global_state, I3C_STATE_ALL_EXCEPT_INIT);

  LL_I3C_SetOwnDynamicAddress(I3C_GET_INSTANCE(hi3c), dynamic_address);
  LL_I3C_EnableOwnDynAddress(I3C_GET_INSTANCE(hi3c));

  return HAL_OK;
}

/**
  * @brief  Get dynamic address value.
  * @param  hi3c  Pointer to a hal_i3c_handle_t
  * @note   This configuration can be set when the I3C is acting as controller.
  * @retval The dynamic address
  */
uint32_t HAL_I3C_CTRL_GetConfigOwnDynamicAddress(const hal_i3c_handle_t *hi3c)
{
  ASSERT_DBG_PARAM((hi3c != NULL));
  ASSERT_DBG_PARAM(hi3c->mode == HAL_I3C_MODE_CTRL);
  ASSERT_DBG_STATE(hi3c->global_state, I3C_STATE_ALL_EXCEPT_INIT);

  return (LL_I3C_GetOwnDynamicAddress(I3C_GET_INSTANCE(hi3c)));
}

/**
  * @brief  Enable Hot-Join request acknowledgement allowed.
  * @param  hi3c  Pointer to a hal_i3c_handle_t
  * @note   This configuration can be set when the I3C is acting as controller.
  * @retval HAL_OK  Operation completed successfully
  */
hal_status_t HAL_I3C_CTRL_EnableHotJoinAllowed(hal_i3c_handle_t *hi3c)
{
  ASSERT_DBG_PARAM((hi3c != NULL));
  ASSERT_DBG_PARAM(hi3c->mode == HAL_I3C_MODE_CTRL);
  ASSERT_DBG_STATE(hi3c->global_state, I3C_STATE_ALL_EXCEPT_INIT);

  LL_I3C_EnableHJAck(I3C_GET_INSTANCE(hi3c));

  return HAL_OK;
}

/**
  * @brief  Disable Hot-Join request acknowledgement allowed.
  * @param  hi3c  Pointer to a hal_i3c_handle_t
  * @note   This configuration can be set when the I3C is acting as controller.
  * @retval HAL_OK  Operation completed successfully
  */
hal_status_t HAL_I3C_CTRL_DisableHotJoinAllowed(hal_i3c_handle_t *hi3c)
{
  ASSERT_DBG_PARAM((hi3c != NULL));
  ASSERT_DBG_PARAM(hi3c->mode == HAL_I3C_MODE_CTRL);
  ASSERT_DBG_STATE(hi3c->global_state, I3C_STATE_ALL_EXCEPT_INIT);

  LL_I3C_DisableHJAck(I3C_GET_INSTANCE(hi3c));

  return HAL_OK;
}

/**
  * @brief  Check if the Hot-Join request acknowledgement is enabled.
  * @param  hi3c  Pointer to a hal_i3c_handle_t
  * @note   This configuration can be set when the I3C is acting as controller.
  * @retval HAL_I3C_HOT_JOIN_DISABLED  Hot-Join disable
  * @retval HAL_I3C_HOT_JOIN_ENABLED   Hot-Join enable
  */
hal_i3c_hot_join_status_t HAL_I3C_CTRL_IsEnabledHotJoinAllowed(const hal_i3c_handle_t *hi3c)
{
  ASSERT_DBG_PARAM((hi3c != NULL));
  ASSERT_DBG_PARAM(hi3c->mode == HAL_I3C_MODE_CTRL);
  ASSERT_DBG_STATE(hi3c->global_state, I3C_STATE_ALL_EXCEPT_INIT);

  return (hal_i3c_hot_join_status_t) LL_I3C_IsEnabledHJAck(I3C_GET_INSTANCE(hi3c));
}

/**
  * @brief  Enable the high keeper SDA.
  * @param  hi3c  Pointer to a hal_i3c_handle_t
  * @note   This configuration can be set when the I3C is acting as controller.
  * @note   This configuration will be used in place of standard Open drain Pull Up device
  *         during handoff procedures
  * @retval HAL_OK  Operation completed successfully
  */
hal_status_t HAL_I3C_CTRL_EnableHighKeeperSDA(const hal_i3c_handle_t *hi3c)
{
  I3C_TypeDef *p_i3cx;

  ASSERT_DBG_PARAM((hi3c != NULL));
  ASSERT_DBG_PARAM(hi3c->mode == HAL_I3C_MODE_CTRL);
  ASSERT_DBG_STATE(hi3c->global_state, HAL_I3C_STATE_IDLE);

  p_i3cx = I3C_GET_INSTANCE(hi3c);
  LL_I3C_Disable(p_i3cx);
  LL_I3C_EnableHighKeeperSDA(p_i3cx);
  LL_I3C_Enable(p_i3cx);

  return HAL_OK;
}

/**
  * @brief  Disable the high keeper SDA.
  * @param  hi3c  Pointer to a hal_i3c_handle_t
  * @note   This configuration can be set when the I3C is acting as controller.
  * @retval HAL_OK  Operation completed successfully
  */
hal_status_t HAL_I3C_CTRL_DisableHighKeeperSDA(const hal_i3c_handle_t *hi3c)
{
  I3C_TypeDef *p_i3cx;

  ASSERT_DBG_PARAM((hi3c != NULL));
  ASSERT_DBG_PARAM(hi3c->mode == HAL_I3C_MODE_CTRL);
  ASSERT_DBG_STATE(hi3c->global_state, HAL_I3C_STATE_IDLE);

  p_i3cx = I3C_GET_INSTANCE(hi3c);
  LL_I3C_Disable(p_i3cx);
  LL_I3C_DisableHighKeeperSDA(p_i3cx);
  LL_I3C_Enable(p_i3cx);

  return HAL_OK;
}

/**
  * @brief  Check if high keeper SDA is enabled.
  * @param  hi3c  Pointer to a hal_i3c_handle_t
  * @note   This configuration can be set when the I3C is acting as controller.
  * @retval HAL_I3C_HIGH_KEEPER_SDA_DISABLED  The controller SDA high keeper disable
  * @retval HAL_I3C_HIGH_KEEPER_SDA_ENABLED   The controller SDA high keeper enable
  */
hal_i3c_high_keeper_sda_status_t HAL_I3C_CTRL_IsEnabledHighKeeperSDA(const hal_i3c_handle_t *hi3c)
{
  ASSERT_DBG_PARAM((hi3c != NULL));
  ASSERT_DBG_PARAM(hi3c->mode == HAL_I3C_MODE_CTRL);
  ASSERT_DBG_STATE(hi3c->global_state, I3C_STATE_ALL_EXCEPT_INIT);

  return (hal_i3c_high_keeper_sda_status_t) LL_I3C_IsEnabledHighKeeperSDA(I3C_GET_INSTANCE(hi3c));
}

/**
  * @brief  Set the SCL clock stalling configuration. All stall features not selected are disabled.
  * @param  hi3c  Pointer to a hal_i3c_handle_t
  * @param  stall_time Controller clock stall time in number of kernel clock cycles.
            This parameter must be a number between Min_Data=0x00 and Max_Data=0xFF.
  * @param  stall_features Features of the I3C controller to which the stall time will be applied.
            See @ref I3C_STALL_FEATURE_DEFINITION, this parameter is a combination of the following values:
              @ref HAL_I3C_STALL_ACK
              @ref HAL_I3C_STALL_CCC
              @ref HAL_I3C_STALL_TX
              @ref HAL_I3C_STALL_RX
              @ref HAL_I3C_STALL_I2C_ACK
              @ref HAL_I3C_STALL_I2C_TX
              @ref HAL_I3C_STALL_I2C_RX
              @ref HAL_I3C_STALL_ALL
              @ref HAL_I3C_STALL_NONE
  * @note   This configuration can be set when the I3C is acting as controller.
  * @retval HAL_OK  Operation completed successfully
  */
hal_status_t HAL_I3C_CTRL_SetConfigStallTime(const hal_i3c_handle_t *hi3c, uint32_t stall_time, uint32_t stall_features)
{
  uint32_t stall_config;
  I3C_TypeDef *p_i3cx;

  ASSERT_DBG_PARAM((hi3c != NULL));
  ASSERT_DBG_PARAM(stall_time <= 0xFF);
  ASSERT_DBG_PARAM((stall_features & HAL_I3C_STALL_ALL) == stall_features);
  ASSERT_DBG_PARAM(hi3c->mode == HAL_I3C_MODE_CTRL);
  ASSERT_DBG_STATE(hi3c->global_state, HAL_I3C_STATE_IDLE);

  p_i3cx = I3C_GET_INSTANCE(hi3c);
  stall_config = (((uint32_t) stall_time << I3C_TIMINGR2_STALL_Pos) | stall_features);
  LL_I3C_ConfigStallTime(p_i3cx, stall_config);

  return HAL_OK;
}

/**
  * @brief  Retrieve the SCL clock stalling configuration.
  * @param  hi3c  Pointer to a hal_i3c_handle_t
  * @param  stall_time  Controller clock stall time in number of kernel clock cycles. This parameter must be a number
                        between Min_Data=0x00 and Max_Data=0xFF.
  * @param  stall_features  Features of the I3C controller to which the stall time is applied.
                            See @ref I3C_STALL_FEATURE_DEFINITION,
                            this parameter is a combination of the following values:
                              @ref HAL_I3C_STALL_ACK
                              @ref HAL_I3C_STALL_CCC
                              @ref HAL_I3C_STALL_TX
                              @ref HAL_I3C_STALL_RX
                              @ref HAL_I3C_STALL_I2C_ACK
                              @ref HAL_I3C_STALL_I2C_TX
                              @ref HAL_I3C_STALL_I2C_RX
                              @ref HAL_I3C_STALL_ALL
  * @note   This configuration can be set when the I3C is acting as controller.
  * @retval HAL_OK  Operation completed successfully
  * @retval HAL_INVALID_PARAM  Invalid parameter
  */
hal_status_t HAL_I3C_CTRL_GetConfigStallTime(const hal_i3c_handle_t *hi3c, uint32_t *stall_time,
                                             uint32_t *stall_features)
{
  uint32_t timing2_value;
  const I3C_TypeDef *p_i3cx;

  ASSERT_DBG_PARAM((hi3c != NULL));
  ASSERT_DBG_PARAM((stall_time != NULL));
  ASSERT_DBG_PARAM((stall_features != NULL));
  ASSERT_DBG_PARAM(hi3c->mode == HAL_I3C_MODE_CTRL);
  ASSERT_DBG_STATE(hi3c->global_state, I3C_STATE_ALL_EXCEPT_INIT);

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if ((stall_time == NULL) || (stall_features == NULL))
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */
  p_i3cx = I3C_GET_INSTANCE(hi3c);
  /* Get value from timing 2 register */
  timing2_value = LL_I3C_READ_REG(p_i3cx, TIMINGR2);
  *stall_time = (uint32_t)(timing2_value >> I3C_TIMINGR2_STALL_Pos);
  *stall_features = timing2_value & (uint32_t) HAL_I3C_STALL_ALL;

  return HAL_OK;
}

/**
  * @brief  Set Controller-Role Request allowed.
  * @param  hi3c  Pointer to a hal_i3c_handle_t
  * @note   This configuration can be set when the I3C is acting as target.
  * @retval HAL_OK  Operation completed successfully
  */
hal_status_t HAL_I3C_TGT_EnableCtrlRoleRequest(const hal_i3c_handle_t *hi3c)
{
  I3C_TypeDef *p_i3cx;

  ASSERT_DBG_PARAM((hi3c != NULL));
  ASSERT_DBG_PARAM(hi3c->mode == HAL_I3C_MODE_TGT);
  ASSERT_DBG_STATE(hi3c->global_state, HAL_I3C_STATE_IDLE);

  p_i3cx = I3C_GET_INSTANCE(hi3c);
  LL_I3C_Disable(p_i3cx);
  LL_I3C_EnableControllerRoleReq(p_i3cx);
  LL_I3C_Enable(p_i3cx);

  return HAL_OK;
}

/**
  * @brief  Set Controller-Role Request as not-allowed.
  * @param  hi3c  Pointer to a hal_i3c_handle_t
  * @note   This configuration can be set when the I3C is acting as target.
  * @retval HAL_OK  Operation completed successfully
  */
hal_status_t HAL_I3C_TGT_DisableCtrlRoleRequest(const hal_i3c_handle_t *hi3c)
{
  I3C_TypeDef *p_i3cx;

  ASSERT_DBG_PARAM((hi3c != NULL));
  ASSERT_DBG_PARAM(hi3c->mode == HAL_I3C_MODE_TGT);
  ASSERT_DBG_STATE(hi3c->global_state, HAL_I3C_STATE_IDLE);

  p_i3cx = I3C_GET_INSTANCE(hi3c);
  LL_I3C_Disable(p_i3cx);
  LL_I3C_DisableControllerRoleReq(p_i3cx);
  LL_I3C_Enable(p_i3cx);

  return HAL_OK;
}

/**
  * @brief  Check if Controller-Role Request is allowed or not-allowed.
  * @param  hi3c  Pointer to a hal_i3c_handle_t
  * @note   This configuration can be set when the I3C is acting as target.
  * @retval HAL_I3C_CTRL_ROLE_DISABLED  Controller-Role disable
  * @retval HAL_I3C_CTRL_ROLE_ENABLED   Controller-Role enable
  */
hal_i3c_ctrl_role_status_t HAL_I3C_TGT_IsEnabledCtrlRoleRequest(const hal_i3c_handle_t *hi3c)
{
  ASSERT_DBG_PARAM((hi3c != NULL));
  ASSERT_DBG_PARAM(hi3c->mode == HAL_I3C_MODE_TGT);
  ASSERT_DBG_STATE(hi3c->global_state, I3C_STATE_ALL_EXCEPT_INIT);

  return (hal_i3c_ctrl_role_status_t) LL_I3C_IsEnabledControllerRoleReq(I3C_GET_INSTANCE(hi3c));
}

/**
  * @brief  Set hand off delay allowed.
  * @param  hi3c  Pointer to a hal_i3c_handle_t
  * @note   This configuration can be set when the I3C is acting as target.
  * @retval HAL_OK  Operation completed successfully
  */
hal_status_t HAL_I3C_TGT_EnableHandOffDelay(const hal_i3c_handle_t *hi3c)
{
  I3C_TypeDef *p_i3cx;

  ASSERT_DBG_PARAM((hi3c != NULL));
  ASSERT_DBG_PARAM(hi3c->mode == HAL_I3C_MODE_TGT);
  ASSERT_DBG_STATE(hi3c->global_state, HAL_I3C_STATE_IDLE);

  p_i3cx = I3C_GET_INSTANCE(hi3c);
  LL_I3C_Disable(p_i3cx);
  LL_I3C_EnableHandOffDelay(p_i3cx);
  LL_I3C_Enable(p_i3cx);

  return HAL_OK;
}

/**
  * @brief  Set hand off delay as not-allowed.
  * @param  hi3c  Pointer to a hal_i3c_handle_t
  * @note   This configuration can be set when the I3C is acting as target.
  * @retval HAL_OK  Operation completed successfully
  */
hal_status_t HAL_I3C_TGT_DisableHandOffDelay(const hal_i3c_handle_t *hi3c)
{
  I3C_TypeDef *p_i3cx;

  ASSERT_DBG_PARAM((hi3c != NULL));
  ASSERT_DBG_PARAM(hi3c->mode == HAL_I3C_MODE_TGT);
  ASSERT_DBG_STATE(hi3c->global_state, HAL_I3C_STATE_IDLE);

  p_i3cx = I3C_GET_INSTANCE(hi3c);
  LL_I3C_Disable(p_i3cx);
  LL_I3C_DisableHandOffDelay(p_i3cx);
  LL_I3C_Enable(p_i3cx);

  return HAL_OK;
}

/**
  * @brief  Check if hand off delay is allowed or not-allowed.
  * @param  hi3c  Pointer to a hal_i3c_handle_t
  * @note   This configuration can be set when the I3C is acting as target.
  * @retval HAL_I3C_END_OF_FRAME_CPLT_DISABLED  Hand off delay disable
  * @retval HAL_I3C_END_OF_FRAME_CPLT_ENABLED   Hand off delay enable
  */
hal_i3c_hand_off_delay_status_t HAL_I3C_TGT_IsEnabledHandOffDelay(const hal_i3c_handle_t *hi3c)
{
  ASSERT_DBG_PARAM((hi3c != NULL));
  ASSERT_DBG_PARAM(hi3c->mode == HAL_I3C_MODE_TGT);
  ASSERT_DBG_STATE(hi3c->global_state, I3C_STATE_ALL_EXCEPT_INIT);

  return (hal_i3c_hand_off_delay_status_t) LL_I3C_IsEnabledHandOffDelay(I3C_GET_INSTANCE(hi3c));
}

/**
  * @brief  Set the group address capability as supported.
  * @param  hi3c  Pointer to a hal_i3c_handle_t
  * @note   This configuration can be set when the I3C is acting as target.
  * @retval HAL_OK  Operation completed successfully
  */
hal_status_t HAL_I3C_TGT_EnableGroupAddrCapability(const hal_i3c_handle_t *hi3c)
{
  I3C_TypeDef *p_i3cx;

  ASSERT_DBG_PARAM((hi3c != NULL));
  ASSERT_DBG_PARAM(hi3c->mode == HAL_I3C_MODE_TGT);
  ASSERT_DBG_STATE(hi3c->global_state, HAL_I3C_STATE_IDLE);

  p_i3cx = I3C_GET_INSTANCE(hi3c);
  LL_I3C_Disable(p_i3cx);
  LL_I3C_SetGrpAddrHandoffSupport(p_i3cx, LL_I3C_HANDOFF_GRP_ADDR_SUPPORTED);
  LL_I3C_Enable(p_i3cx);

  return HAL_OK;
}

/**
  * @brief  Set the group address capability as not supported.
  * @param  hi3c  Pointer to a hal_i3c_handle_t
  * @note   This configuration can be set when the I3C is acting as target.
  * @retval HAL_OK  Operation completed successfully
  */
hal_status_t HAL_I3C_TGT_DisableGroupAddrCapability(const hal_i3c_handle_t *hi3c)
{
  I3C_TypeDef *p_i3cx;

  ASSERT_DBG_PARAM((hi3c != NULL));
  ASSERT_DBG_PARAM(hi3c->mode == HAL_I3C_MODE_TGT);
  ASSERT_DBG_STATE(hi3c->global_state, HAL_I3C_STATE_IDLE);

  p_i3cx = I3C_GET_INSTANCE(hi3c);
  LL_I3C_Disable(p_i3cx);
  LL_I3C_SetGrpAddrHandoffSupport(p_i3cx, LL_I3C_HANDOFF_GRP_ADDR_NOT_SUPPORTED);
  LL_I3C_Enable(p_i3cx);

  return HAL_OK;
}

/**
  * @brief  Check if the group address capability is supported or not-supported.
  * @param  hi3c  Pointer to a hal_i3c_handle_t
  * @note   This configuration can be set when the I3C is acting as target.
  * @retval HAL_I3C_GRP_ADDR_CAPABILITY_DISABLED  Group address capability disable
  * @retval HAL_I3C_GRP_ADDR_CAPABILITY_ENABLED   Group address capability enable
  */
hal_i3c_grp_addr_capability_status_t HAL_I3C_TGT_IsEnabledGroupAddrCapability(const hal_i3c_handle_t *hi3c)
{
  ASSERT_DBG_PARAM((hi3c != NULL));
  ASSERT_DBG_PARAM(hi3c->mode == HAL_I3C_MODE_TGT);
  ASSERT_DBG_STATE(hi3c->global_state, I3C_STATE_ALL_EXCEPT_INIT);

  if (LL_I3C_GetGrpAddrHandoffSupport(I3C_GET_INSTANCE(hi3c)) == LL_I3C_HANDOFF_GRP_ADDR_NOT_SUPPORTED)
  {
    return HAL_I3C_GRP_ADDR_CAPABILITY_DISABLED;
  }
  else
  {
    return HAL_I3C_GRP_ADDR_CAPABILITY_ENABLED;
  }
}

/**
  * @brief  Set Hot-Join allowed.
  * @param  hi3c  Pointer to a hal_i3c_handle_t
  * @note   This configuration can be set when the I3C is acting as target.
  * @retval HAL_OK  Operation completed successfully
  */
hal_status_t HAL_I3C_TGT_EnableHotJoinRequest(const hal_i3c_handle_t *hi3c)
{
  I3C_TypeDef *p_i3cx;

  ASSERT_DBG_PARAM((hi3c != NULL));
  ASSERT_DBG_PARAM(hi3c->mode == HAL_I3C_MODE_TGT);
  ASSERT_DBG_STATE(hi3c->global_state, HAL_I3C_STATE_IDLE);

  p_i3cx = I3C_GET_INSTANCE(hi3c);
  LL_I3C_Disable(p_i3cx);
  LL_I3C_EnableHotJoin(p_i3cx);
  LL_I3C_Enable(p_i3cx);

  return HAL_OK;
}

/**
  * @brief  Set Hot-Join as not-allowed.
  * @param  hi3c  Pointer to a hal_i3c_handle_t
  * @note   This configuration can be set when the I3C is acting as target.
  * @retval HAL_OK  Operation completed successfully
  */
hal_status_t HAL_I3C_TGT_DisableHotJoinRequest(const hal_i3c_handle_t *hi3c)
{
  I3C_TypeDef *p_i3cx;

  ASSERT_DBG_PARAM((hi3c != NULL));
  ASSERT_DBG_PARAM(hi3c->mode == HAL_I3C_MODE_TGT);
  ASSERT_DBG_STATE(hi3c->global_state, HAL_I3C_STATE_IDLE);

  p_i3cx = I3C_GET_INSTANCE(hi3c);
  LL_I3C_Disable(p_i3cx);
  LL_I3C_DisableHotJoin(p_i3cx);
  LL_I3C_Enable(p_i3cx);

  return HAL_OK;
}

/**
  * @brief  Check if Hot-Join is allowed or not-allowed.
  * @param  hi3c  Pointer to a hal_i3c_handle_t
  * @note   This configuration can be set when the I3C is acting as target.
  * @retval HAL_I3C_HOT_JOIN_DISABLED  Hot-Join disable
  * @retval HAL_I3C_HOT_JOIN_ENABLED   Hot-Join enable
  */
hal_i3c_hot_join_status_t HAL_I3C_TGT_IsEnabledHotJoinRequest(const hal_i3c_handle_t *hi3c)
{
  ASSERT_DBG_PARAM((hi3c != NULL));
  ASSERT_DBG_PARAM(hi3c->mode == HAL_I3C_MODE_TGT);
  ASSERT_DBG_STATE(hi3c->global_state, I3C_STATE_ALL_EXCEPT_INIT);

  return (hal_i3c_hot_join_status_t) LL_I3C_IsEnabledHotJoin(I3C_GET_INSTANCE(hi3c));
}

/**
  * @brief  Enable IBI request.
  * @param  hi3c  Pointer to a hal_i3c_handle_t
  * @param  p_config  Pointer to the configuration structure
  * @note   This configuration can be set when the I3C is acting as target.
  * @retval HAL_OK  Operation completed successfully
  * @retval HAL_INVALID_PARAM  Invalid parameter
  */
hal_status_t HAL_I3C_TGT_EnableIBI(const hal_i3c_handle_t *hi3c, const hal_i3c_tgt_ibi_config_t *p_config)
{
  I3C_TypeDef *p_i3cx;

  ASSERT_DBG_PARAM((hi3c != NULL));
  ASSERT_DBG_PARAM((p_config != NULL));
  ASSERT_DBG_PARAM(IS_I3C_IBI_PAYLOAD_SIZE(p_config->ibi_payload_size_byte));
  ASSERT_DBG_PARAM(IS_I3C_PENDING_READ(p_config->pending_read_mdb));
  ASSERT_DBG_PARAM(hi3c->mode == HAL_I3C_MODE_TGT);
  ASSERT_DBG_STATE(hi3c->global_state, HAL_I3C_STATE_IDLE);

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (p_config == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */
  p_i3cx = I3C_GET_INSTANCE(hi3c);
  LL_I3C_Disable(p_i3cx);
  LL_I3C_ConfigNbIBIAddData(p_i3cx, (uint32_t)p_config->ibi_payload_size_byte);
  LL_I3C_SetPendingReadMDB(p_i3cx, (uint32_t)p_config->pending_read_mdb);
  LL_I3C_EnableIBI(p_i3cx);
  LL_I3C_Enable(p_i3cx);

  return HAL_OK;
}

/**
  * @brief  Disable IBI request.
  * @param  hi3c  Pointer to a hal_i3c_handle_t
  * @note   This configuration can be set when the I3C is acting as target.
  * @retval HAL_OK  Operation completed successfully
  */
hal_status_t HAL_I3C_TGT_DisableIBI(const hal_i3c_handle_t *hi3c)
{
  I3C_TypeDef *p_i3cx;

  ASSERT_DBG_PARAM((hi3c != NULL));
  ASSERT_DBG_PARAM(hi3c->mode == HAL_I3C_MODE_TGT);
  ASSERT_DBG_STATE(hi3c->global_state, HAL_I3C_STATE_IDLE);

  p_i3cx = I3C_GET_INSTANCE(hi3c);
  LL_I3C_Disable(p_i3cx);
  LL_I3C_DisableIBI(p_i3cx);
  LL_I3C_Enable(p_i3cx);

  return HAL_OK;
}

/**
  * @brief  Get IBI configuration.
  * @param  hi3c  Pointer to a hal_i3c_handle_t
  * @param  p_config  Pointer to the configuration structure
  * @note   This configuration can be set when the I3C is acting as target.
  */
void HAL_I3C_TGT_GetConfigIBI(const hal_i3c_handle_t *hi3c, hal_i3c_tgt_ibi_config_t *p_config)
{
  I3C_TypeDef *p_i3cx;

  ASSERT_DBG_PARAM((hi3c != NULL));
  ASSERT_DBG_PARAM((p_config != NULL));
  ASSERT_DBG_PARAM(hi3c->mode == HAL_I3C_MODE_TGT);
  ASSERT_DBG_STATE(hi3c->global_state, I3C_STATE_ALL_EXCEPT_INIT);

  p_i3cx = I3C_GET_INSTANCE(hi3c);
  p_config->ibi_payload_size_byte = (hal_i3c_payload_size_t)LL_I3C_GetConfigNbIBIAddData(p_i3cx);
  p_config->pending_read_mdb = (hal_i3c_tgt_read_mdb_status_t) LL_I3C_GetPendingReadMDB(p_i3cx);
}

/**
  * @brief  Check if IBI procedure is allowed or not allowed.
  * @param  hi3c  Pointer to a hal_i3c_handle_t
  * @note   This configuration can be set when the I3C is acting as target.
  * @retval HAL_I3C_IBI_REQ_DISABLED  IBI request disable
  * @retval HAL_I3C_IBI_REQ_ENABLED   IBI request enable
  */
hal_i3c_ibi_req_status_t HAL_I3C_TGT_IsEnabledIBI(const hal_i3c_handle_t *hi3c)
{
  ASSERT_DBG_PARAM((hi3c != NULL));
  ASSERT_DBG_PARAM(hi3c->mode == HAL_I3C_MODE_TGT);
  ASSERT_DBG_STATE(hi3c->global_state, I3C_STATE_ALL_EXCEPT_INIT);

  return (hal_i3c_ibi_req_status_t) LL_I3C_IsEnabledIBI(I3C_GET_INSTANCE(hi3c));
}

/**
  * @brief  Set the max data size configuration.
  * @param  hi3c  Pointer to a hal_i3c_handle_t
  * @param  p_config  Pointer to the configuration structure
  * @note   This configuration can be set when the I3C is acting as target.
  * @retval HAL_OK  Operation completed successfully
  * @retval HAL_INVALID_PARAM  Invalid parameter
  */
hal_status_t HAL_I3C_TGT_SetConfigMaxDataSize(const hal_i3c_handle_t *hi3c,
                                              const hal_i3c_tgt_max_data_size_config_t *p_config)
{
  I3C_TypeDef *p_i3cx;

  ASSERT_DBG_PARAM((hi3c != NULL));
  ASSERT_DBG_PARAM((p_config != NULL));
  ASSERT_DBG_PARAM(hi3c->mode == HAL_I3C_MODE_TGT);
  ASSERT_DBG_STATE(hi3c->global_state, HAL_I3C_STATE_IDLE);

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (p_config == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */
  p_i3cx = I3C_GET_INSTANCE(hi3c);
  LL_I3C_Disable(p_i3cx);
  LL_I3C_SetMaxWriteLength(p_i3cx, p_config->max_write_data_size_byte);
  LL_I3C_SetMaxReadLength(p_i3cx, p_config->max_read_data_size_byte);
  LL_I3C_Enable(p_i3cx);

  return HAL_OK;
}

/**
  * @brief  Retrieve max data size configuration.
  * @param  hi3c  Pointer to a hal_i3c_handle_t
  * @param  p_config  Pointer to the configuration structure
  * @note   This configuration can be set when the I3C is acting as target.
  */
void HAL_I3C_TGT_GetConfigMaxDataSize(const hal_i3c_handle_t *hi3c,
                                      hal_i3c_tgt_max_data_size_config_t *p_config)
{
  I3C_TypeDef *p_i3cx;

  ASSERT_DBG_PARAM((hi3c != NULL));
  ASSERT_DBG_PARAM((p_config != NULL));
  ASSERT_DBG_PARAM(hi3c->mode == HAL_I3C_MODE_TGT);
  ASSERT_DBG_STATE(hi3c->global_state, I3C_STATE_ALL_EXCEPT_INIT);

  p_i3cx = I3C_GET_INSTANCE(hi3c);
  p_config->max_write_data_size_byte = (uint16_t) LL_I3C_GetMaxWriteLength(p_i3cx);
  p_config->max_read_data_size_byte = (uint16_t) LL_I3C_GetMaxReadLength(p_i3cx);
}

/**
  * @brief  Set the Max Data Speed configuration response for GETMXDS CCC.
  * @param  hi3c  Pointer to a hal_i3c_handle_t
  * @param  p_config  Pointer to the configuration structure
  * @note   This configuration can be set when the I3C is acting as target.
  * @retval HAL_OK  Operation completed successfully
  * @retval HAL_INVALID_PARAM  Invalid parameter
  */
hal_status_t HAL_I3C_TGT_SetConfigGETMXDS(const hal_i3c_handle_t *hi3c,
                                          const hal_i3c_tgt_getmxds_config_t *p_config)
{
  I3C_TypeDef *p_i3cx;
  uint32_t getmxdsr_value;

  ASSERT_DBG_PARAM((hi3c != NULL));
  ASSERT_DBG_PARAM((p_config != NULL));
  ASSERT_DBG_PARAM(IS_I3C_MAX_SPEED_DATA(p_config->GETMXDS_format));
  ASSERT_DBG_PARAM(IS_I3C_HANDOFF_ACTIVITY_STATE(p_config->ctrl_hand_off_activity));
  ASSERT_DBG_PARAM(IS_I3C_TSCO_TIME(p_config->data_turnaround_duration));
  ASSERT_DBG_PARAM(hi3c->mode == HAL_I3C_MODE_TGT);
  ASSERT_DBG_STATE(hi3c->global_state, HAL_I3C_STATE_IDLE);

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (p_config == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  p_i3cx = I3C_GET_INSTANCE(hi3c);
  LL_I3C_Disable(p_i3cx);
  /* Calculate value to be written in the GETMXDSR register */
  getmxdsr_value = ((uint32_t) p_config->ctrl_hand_off_activity |
                    (uint32_t) p_config->GETMXDS_format |
                    (uint32_t) p_config->data_turnaround_duration |
                    ((uint32_t)p_config->max_read_turnaround << I3C_GETMXDSR_RDTURN_Pos));

  /* Set value in GETMXDSR register */
  LL_I3C_WRITE_REG(p_i3cx, GETMXDSR, getmxdsr_value);
  LL_I3C_Enable(p_i3cx);

  return HAL_OK;
}

/**
  * @brief  Retrieve the Max Data Speed configuration response for GETMXDS CCC.
  * @param  hi3c  Pointer to a hal_i3c_handle_t
  * @param  p_config  Pointer to the configuration structure
  * @note   This configuration can be set when the I3C is acting as target.
  */
void HAL_I3C_TGT_GetConfigGETMXDS(const hal_i3c_handle_t *hi3c, hal_i3c_tgt_getmxds_config_t *p_config)
{
  const I3C_TypeDef *p_i3cx;
  uint32_t getmxdsr_value;

  ASSERT_DBG_PARAM((hi3c != NULL));
  ASSERT_DBG_PARAM((p_config != NULL));
  ASSERT_DBG_PARAM(hi3c->mode == HAL_I3C_MODE_TGT);
  ASSERT_DBG_STATE(hi3c->global_state, I3C_STATE_ALL_EXCEPT_INIT);

  p_i3cx = I3C_GET_INSTANCE(hi3c);
  getmxdsr_value = LL_I3C_READ_REG(p_i3cx, GETMXDSR);

  p_config->ctrl_hand_off_activity = (hal_i3c_handoff_activity_state_t)(uint32_t)(getmxdsr_value & I3C_GETMXDSR_HOFFAS);
  p_config->GETMXDS_format = (hal_i3c_GETMXDS_format_t)(uint32_t)(getmxdsr_value & I3C_GETMXDSR_FMT);
  p_config->data_turnaround_duration = (hal_i3c_turnaround_time_tSCO_t)(uint32_t)(getmxdsr_value & I3C_GETMXDSR_TSCO);
  p_config->max_read_turnaround = (uint8_t)((getmxdsr_value & I3C_GETMXDSR_RDTURN) >> I3C_GETMXDSR_RDTURN_Pos);
}

/**
  * @brief  Set the format of the response for GETMXDS CCC.
  * @param  hi3c  Pointer to a hal_i3c_handle_t
  * @param  format  GETMXDS format
  * @note   This configuration can be set when the I3C is acting as target.
  * @retval HAL_OK  Operation completed successfully
  */
hal_status_t HAL_I3C_TGT_SetConfigGETMXDS_Format(const hal_i3c_handle_t *hi3c, hal_i3c_GETMXDS_format_t format)
{
  I3C_TypeDef *p_i3cx;

  ASSERT_DBG_PARAM((hi3c != NULL));
  ASSERT_DBG_PARAM(IS_I3C_MAX_SPEED_DATA(format));
  ASSERT_DBG_PARAM(hi3c->mode == HAL_I3C_MODE_TGT);
  ASSERT_DBG_STATE(hi3c->global_state, I3C_STATE_ALL_EXCEPT_INIT);

  p_i3cx = I3C_GET_INSTANCE(hi3c);
  LL_I3C_Disable(p_i3cx);
  LL_I3C_SetMaxDataSpeedFormat(p_i3cx, (uint32_t) format);
  LL_I3C_Enable(p_i3cx);

  return HAL_OK;
}

/**
  * @brief  Get the format of the response for GETMXDS CCC.
  * @param  hi3c  Pointer to a hal_i3c_handle_t
  * @note   This configuration can be set when the I3C is acting as target.
  * @retval HAL_I3C_GETMXDS_FORMAT_1
  * @retval HAL_I3C_GETMXDS_FORMAT_2_LSB
  * @retval HAL_I3C_GETMXDS_FORMAT_2_MID
  * @retval HAL_I3C_GETMXDS_FORMAT_2_MSB
  */
hal_i3c_GETMXDS_format_t HAL_I3C_TGT_GetConfigGETMXDS_Format(const hal_i3c_handle_t *hi3c)
{
  ASSERT_DBG_PARAM((hi3c != NULL));
  ASSERT_DBG_PARAM(hi3c->mode == HAL_I3C_MODE_TGT);
  ASSERT_DBG_STATE(hi3c->global_state, I3C_STATE_ALL_EXCEPT_INIT);

  return (hal_i3c_GETMXDS_format_t) LL_I3C_GetMaxDataSpeedFormat(I3C_GET_INSTANCE(hi3c));
}

/**
  * @brief  Set the activity state after controllership handoff configuration.
  * @param  hi3c  Pointer to a hal_i3c_handle_t
  * @param  state Handoff activity state
  * @note   This configuration can be set when the I3C is acting as target.
  * @retval HAL_OK  Operation completed successfully
  */
hal_status_t HAL_I3C_TGT_SetConfigCtrlHandOffActivity(const hal_i3c_handle_t *hi3c,
                                                      hal_i3c_handoff_activity_state_t state)
{
  I3C_TypeDef *p_i3cx;

  ASSERT_DBG_PARAM((hi3c != NULL));
  ASSERT_DBG_PARAM(IS_I3C_HANDOFF_ACTIVITY_STATE(state));
  ASSERT_DBG_PARAM(hi3c->mode == HAL_I3C_MODE_TGT);
  ASSERT_DBG_STATE(hi3c->global_state, I3C_STATE_ALL_EXCEPT_INIT);

  p_i3cx = I3C_GET_INSTANCE(hi3c);
  LL_I3C_Disable(p_i3cx);
  LL_I3C_SetHandoffActivityState(I3C_GET_INSTANCE(hi3c), (uint32_t)state);
  LL_I3C_Enable(p_i3cx);

  return HAL_OK;
}

/**
  * @brief  Get the Activity State after controllership handoff.
  * @param  hi3c  Pointer to a hal_i3c_handle_t
  * @note   This configuration can be set when the I3C is acting as target.
  * @retval HAL_I3C_HANDOFF_ACTIVITY_STATE_0  Activity state 0 after handoff
  * @retval HAL_I3C_HANDOFF_ACTIVITY_STATE_1  Activity state 1 after handoff
  * @retval HAL_I3C_HANDOFF_ACTIVITY_STATE_2  Activity state 2 after handoff
  * @retval HAL_I3C_HANDOFF_ACTIVITY_STATE_3  Activity state 3 after handoff
  */
hal_i3c_handoff_activity_state_t HAL_I3C_TGT_GetConfigCtrlHandOffActivity(const hal_i3c_handle_t *hi3c)
{
  ASSERT_DBG_PARAM((hi3c != NULL));
  ASSERT_DBG_PARAM(hi3c->mode == HAL_I3C_MODE_TGT);
  ASSERT_DBG_STATE(hi3c->global_state, I3C_STATE_ALL_EXCEPT_INIT);

  return (hal_i3c_handoff_activity_state_t) LL_I3C_GetHandoffActivityState(I3C_GET_INSTANCE(hi3c));
}

/**
  * @brief  Set I3C bus devices configuration.
  * @param  hi3c  Pointer to a hal_i3c_handle_t
  * @param  p_desc Pointer to the configuration structure
  * @param  nb_device Number of devices to configure
  * @note   This configuration can be set when the I3C is acting as controller.
  * @retval HAL_OK  Operation completed successfully
  * @retval HAL_INVALID_PARAM  Invalid parameter
  */
hal_status_t HAL_I3C_CTRL_SetConfigBusDevices(const hal_i3c_handle_t *hi3c, const hal_i3c_ctrl_device_config_t *p_desc,
                                              uint32_t nb_device)
{
  uint32_t write_value;
  I3C_TypeDef *p_i3cx;

  ASSERT_DBG_PARAM((hi3c != NULL));
  ASSERT_DBG_PARAM((p_desc != NULL));
  ASSERT_DBG_PARAM(IS_I3C_DEVICE(nb_device));
  ASSERT_DBG_PARAM(hi3c->mode == HAL_I3C_MODE_CTRL);
  ASSERT_DBG_STATE(hi3c->global_state, HAL_I3C_STATE_IDLE);

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (p_desc == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */
  p_i3cx = I3C_GET_INSTANCE(hi3c);
  /* Loop on the nb_device to be treated */
  for (uint32_t i = 0U; i < nb_device; i++)
  {
    ASSERT_DBG_PARAM(IS_I3C_DEVICE_INDEX(p_desc[i].device_index));
    ASSERT_DBG_PARAM(IS_I3C_DYNAMIC_ADDRESS(p_desc[i].tgt_dynamic_addr));
    ASSERT_DBG_PARAM(IS_I3C_IBI(p_desc[i].ibi_ack));
    ASSERT_DBG_PARAM(IS_I3C_CTRL_CAPABILITY(p_desc[i].ctrl_role_req_ack));
    ASSERT_DBG_PARAM(IS_I3C_STOP_XFER(p_desc[i].ctrl_stop_transfer));
    ASSERT_DBG_PARAM(IS_I3C_IBI_PAYLOAD(p_desc[i].ibi_payload));

    /* Set value to be written */
    write_value = (((uint32_t)p_desc[i].tgt_dynamic_addr   << I3C_DEVRX_DA_Pos)     |
                   ((uint32_t)p_desc[i].ibi_ack            << I3C_DEVRX_IBIACK_Pos) |
                   ((uint32_t)p_desc[i].ctrl_role_req_ack  << I3C_DEVRX_CRACK_Pos)  |
                   ((uint32_t)p_desc[i].ctrl_stop_transfer << I3C_DEVRX_SUSP_Pos)   |
                   ((uint32_t)p_desc[i].ibi_payload        << I3C_DEVRX_IBIDEN_Pos));

    /* Write configuration in the DEVRx register */
    LL_I3C_WRITE_REG(p_i3cx, DEVRX[(p_desc[i].device_index)], write_value);
  }

  return HAL_OK;
}

/**
  * @brief  Retrieve I3C bus devices configuration.
  * @param  hi3c  Pointer to a hal_i3c_handle_t
  * @param  p_desc  Pointer to the configuration structure
  * @param  nb_device  Number of devices to retrieve the configuration
  * @note   This configuration can be set when the I3C is acting as controller.
  */
void HAL_I3C_CTRL_GetConfigBusDevices(const hal_i3c_handle_t *hi3c, hal_i3c_ctrl_device_config_t *p_desc,
                                      uint32_t                      nb_device)
{
  uint32_t read_value;
  const I3C_TypeDef *p_i3cx;

  ASSERT_DBG_PARAM((hi3c != NULL));
  ASSERT_DBG_PARAM((p_desc != NULL));
  ASSERT_DBG_PARAM(IS_I3C_DEVICE(nb_device));
  ASSERT_DBG_PARAM(hi3c->mode == HAL_I3C_MODE_CTRL);
  ASSERT_DBG_STATE(hi3c->global_state, I3C_STATE_ALL_EXCEPT_INIT);

  p_i3cx = I3C_GET_INSTANCE(hi3c);
  /* Loop on the nb_device to be treated */
  for (uint32_t i = 0U; i < nb_device; i++)
  {
    read_value = LL_I3C_READ_REG(p_i3cx, DEVRX[i]);
    p_desc[i].device_index = (uint8_t)i;
    p_desc[i].tgt_dynamic_addr = (uint8_t)(uint32_t)((read_value & I3C_DEVRX_DA_Msk) >> I3C_DEVRX_DA_Pos);
    p_desc[i].ibi_ack = (hal_i3c_ibi_req_status_t)(uint32_t)((read_value & I3C_DEVRX_IBIACK_Msk)
                                                             >> I3C_DEVRX_IBIACK_Pos);
    p_desc[i].ctrl_role_req_ack = (hal_i3c_ctrl_capability_status_t)(uint32_t)((read_value & I3C_DEVRX_CRACK_Msk)
                                                                               >> I3C_DEVRX_CRACK_Pos);
    p_desc[i].ctrl_stop_transfer = (hal_i3c_stop_xfer_status_t)(uint32_t)((read_value & I3C_DEVRX_SUSP_Msk)
                                                                          >> I3C_DEVRX_SUSP_Pos);
    p_desc[i].ibi_payload = (hal_i3c_ibi_payload_status_t)(uint32_t)((read_value & I3C_DEVRX_IBIDEN_Msk)
                                                                     >> I3C_DEVRX_IBIDEN_Pos);
  }
}

/**
  * @brief  Enable the inserted reset pattern at the end of a frame.
  * @param  hi3c  Pointer to a hal_i3c_handle_t
  * @note   This configuration can be set when the I3C is acting as controller.
  * @retval HAL_OK  Operation completed successfully
  */
hal_status_t HAL_I3C_CTRL_EnableResetPattern(hal_i3c_handle_t *hi3c)
{
  ASSERT_DBG_PARAM((hi3c != NULL));
  ASSERT_DBG_PARAM(hi3c->mode == HAL_I3C_MODE_CTRL);
  ASSERT_DBG_STATE(hi3c->global_state, HAL_I3C_STATE_IDLE);

  LL_I3C_EnableResetPattern(I3C_GET_INSTANCE(hi3c));

  return HAL_OK;
}

/**
  * @brief  Disable the inserted reset pattern at the end of a frame.
  * @param  hi3c  Pointer to a hal_i3c_handle_t
  * @note   This configuration can be set when the I3C is acting as controller.
  * @retval HAL_OK  Operation completed successfully
  */
hal_status_t HAL_I3C_CTRL_DisableResetPattern(hal_i3c_handle_t *hi3c)
{
  ASSERT_DBG_PARAM((hi3c != NULL));
  ASSERT_DBG_PARAM(hi3c->mode == HAL_I3C_MODE_CTRL);
  ASSERT_DBG_STATE(hi3c->global_state, HAL_I3C_STATE_IDLE);

  LL_I3C_DisableResetPattern(I3C_GET_INSTANCE(hi3c));

  return HAL_OK;
}

/**
  * @brief  Check if the inserted reset pattern at the end of a frame is enabled or disabled.
  * @param  hi3c  Pointer to a hal_i3c_handle_t
  * @note   This configuration can be set when the I3C is acting as controller.
  * @retval HAL_I3C_RESET_PATTERN_DISABLE  Standard STOP condition emitted at the end of a frame
  * @retval HAL_I3C_RESET_PATTERN_ENABLE  Reset pattern is inserted before the STOP condition of any emitted frame
  */
hal_i3c_reset_pattern_status_t HAL_I3C_CTRL_IsEnabledResetPattern(const hal_i3c_handle_t *hi3c)
{
  ASSERT_DBG_PARAM((hi3c != NULL));
  ASSERT_DBG_PARAM(hi3c->mode == HAL_I3C_MODE_CTRL);
  ASSERT_DBG_STATE(hi3c->global_state, I3C_STATE_ALL_EXCEPT_INIT);

  return (hal_i3c_reset_pattern_status_t) LL_I3C_IsEnabledResetPattern(I3C_GET_INSTANCE(hi3c));
}

#if defined(USE_HAL_I3C_REGISTER_CALLBACKS) && (USE_HAL_I3C_REGISTER_CALLBACKS == 1)
/**
  * @brief  Register the controller transfer complete callback.
  * @param  hi3c  Pointer to a hal_i3c_handle_t
  * @param  p_callback  Pointer to the controller transfer complete callback function
  * @retval HAL_OK  Operation completed successfully
  * @retval HAL_INVALID_PARAM  Invalid parameter
  */
hal_status_t HAL_I3C_CTRL_RegisterXferCpltCallback(hal_i3c_handle_t *hi3c, hal_i3c_cb_t p_callback)
{
  ASSERT_DBG_PARAM((hi3c != NULL));
  ASSERT_DBG_PARAM((p_callback != NULL));
  ASSERT_DBG_PARAM(hi3c->mode == HAL_I3C_MODE_CTRL);
  ASSERT_DBG_STATE(hi3c->global_state, (uint32_t)HAL_I3C_STATE_INIT | (uint32_t)HAL_I3C_STATE_IDLE);

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (p_callback == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  hi3c->p_ctrl_xfer_cplt_cb = p_callback;

  return HAL_OK;
}

/**
  * @brief  Register the controller dynamic address assignment complete callback.
  * @param  hi3c  Pointer to a hal_i3c_handle_t
  * @param  p_callback  Pointer to the controller dynamic address assignment complete callback function
  * @retval HAL_OK  Operation completed successfully
  * @retval HAL_INVALID_PARAM  Invalid parameter
  */
hal_status_t HAL_I3C_CTRL_RegisterDAACpltCallback(hal_i3c_handle_t *hi3c, hal_i3c_cb_t p_callback)
{
  ASSERT_DBG_PARAM((hi3c != NULL));
  ASSERT_DBG_PARAM((p_callback != NULL));
  ASSERT_DBG_PARAM(hi3c->mode == HAL_I3C_MODE_CTRL);
  ASSERT_DBG_STATE(hi3c->global_state, (uint32_t)HAL_I3C_STATE_INIT | (uint32_t)HAL_I3C_STATE_IDLE);

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (p_callback == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  hi3c->p_ctrl_daa_cplt_cb = p_callback;

  return HAL_OK;
}

/**
  * @brief  Register the target request dynamic address callback.
  * @param  hi3c  Pointer to a hal_i3c_handle_t
  * @param  p_callback  Pointer to the target request dynamic address callback function
  * @retval HAL_OK  Operation completed successfully
  * @retval HAL_INVALID_PARAM  Invalid parameter
  */
hal_status_t HAL_I3C_CTRL_RegisterTgtReqDynAddrCallback(hal_i3c_handle_t *hi3c,
                                                        hal_i3c_req_dyn_addr_cb_t p_callback)
{
  ASSERT_DBG_PARAM((hi3c != NULL));
  ASSERT_DBG_PARAM((p_callback != NULL));
  ASSERT_DBG_PARAM(hi3c->mode == HAL_I3C_MODE_CTRL);
  ASSERT_DBG_STATE(hi3c->global_state, (uint32_t)HAL_I3C_STATE_INIT | (uint32_t)HAL_I3C_STATE_IDLE);

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (p_callback == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  hi3c->p_ctrl_tgt_req_dyn_addr_cb = p_callback;

  return HAL_OK;
}

/**
  * @brief  Register the target transmission complete callback.
  * @param  hi3c  Pointer to a hal_i3c_handle_t
  * @param  p_callback  Pointer to the target transmission complete callback function
  * @retval HAL_OK  Operation completed successfully
  * @retval HAL_INVALID_PARAM  Invalid parameter
  */
hal_status_t HAL_I3C_TGT_RegisterTxCpltCallback(hal_i3c_handle_t *hi3c, hal_i3c_cb_t p_callback)
{
  ASSERT_DBG_PARAM((hi3c != NULL));
  ASSERT_DBG_PARAM((p_callback != NULL));
  ASSERT_DBG_PARAM(hi3c->mode == HAL_I3C_MODE_TGT);
  ASSERT_DBG_STATE(hi3c->global_state, (uint32_t)HAL_I3C_STATE_INIT | (uint32_t)HAL_I3C_STATE_IDLE);

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (p_callback == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  hi3c->p_tgt_tx_cplt_cb = p_callback;

  return HAL_OK;
}

/**
  * @brief  Register the target Reception complete callback.
  * @param  hi3c  Pointer to a hal_i3c_handle_t
  * @param  p_callback  Pointer to the target reception complete callback function
  * @retval HAL_OK  Operation completed successfully
  * @retval HAL_INVALID_PARAM  Invalid parameter
  */
hal_status_t HAL_I3C_TGT_RegisterRxCpltCallback(hal_i3c_handle_t *hi3c, hal_i3c_cb_t p_callback)
{
  ASSERT_DBG_PARAM((hi3c != NULL));
  ASSERT_DBG_PARAM((p_callback != NULL));
  ASSERT_DBG_PARAM(hi3c->mode == HAL_I3C_MODE_TGT);
  ASSERT_DBG_STATE(hi3c->global_state, (uint32_t)HAL_I3C_STATE_INIT | (uint32_t)HAL_I3C_STATE_IDLE);

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (p_callback == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  hi3c->p_tgt_rx_cplt_cb = p_callback;

  return HAL_OK;
}

/**
  * @brief  Register the target Hot-Join process complete callback.
  * @param  hi3c  Pointer to a hal_i3c_handle_t
  * @param  p_callback  Pointer to the target Hot-Join process complete callback function
  * @retval HAL_OK  Operation completed successfully
  * @retval HAL_INVALID_PARAM  Invalid parameter
  */
hal_status_t HAL_I3C_TGT_RegisterHotJoinCallback(hal_i3c_handle_t *hi3c, hal_i3c_tgt_hot_join_cb_t p_callback)
{
  ASSERT_DBG_PARAM((hi3c != NULL));
  ASSERT_DBG_PARAM((p_callback != NULL));
  ASSERT_DBG_PARAM(hi3c->mode == HAL_I3C_MODE_TGT);
  ASSERT_DBG_STATE(hi3c->global_state, (uint32_t)HAL_I3C_STATE_INIT | (uint32_t)HAL_I3C_STATE_IDLE);

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (p_callback == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  hi3c->p_tgt_hot_join_cb = p_callback;

  return HAL_OK;
}

/**
  * @brief  Register the target/controller Notification event callback.
  * @param  hi3c  Pointer to a hal_i3c_handle_t
  * @param  p_callback  Pointer to the target/controller Notification event callback function
  * @retval HAL_OK  Operation completed successfully
  * @retval HAL_INVALID_PARAM  Invalid parameter
  */
hal_status_t HAL_I3C_RegisterNotifyCallback(hal_i3c_handle_t *hi3c, hal_i3c_notify_cb_t p_callback)
{
  ASSERT_DBG_PARAM((hi3c != NULL));
  ASSERT_DBG_PARAM((p_callback != NULL));
  ASSERT_DBG_STATE(hi3c->global_state, (uint32_t)HAL_I3C_STATE_INIT | (uint32_t)HAL_I3C_STATE_IDLE);

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (p_callback == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  hi3c->p_notify_cb = p_callback;

  return HAL_OK;
}

/**
  * @brief  Register the abort complete callback.
  * @param  hi3c  Pointer to a hal_i3c_handle_t
  * @param  p_callback  Pointer to the abort complete callback function
  * @retval HAL_OK  Operation completed successfully
  * @retval HAL_INVALID_PARAM  Invalid parameter
  */
hal_status_t HAL_I3C_RegisterAbortCpltCallback(hal_i3c_handle_t *hi3c, hal_i3c_cb_t p_callback)
{
  ASSERT_DBG_PARAM((hi3c != NULL));
  ASSERT_DBG_PARAM((p_callback != NULL));
  ASSERT_DBG_STATE(hi3c->global_state, (uint32_t)HAL_I3C_STATE_INIT | (uint32_t)HAL_I3C_STATE_IDLE);

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (p_callback == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  hi3c->p_abort_cplt_cb = p_callback;

  return HAL_OK;
}

/**
  * @brief  Register the error callback.
  * @param  hi3c  Pointer to a hal_i3c_handle_t
  * @param  p_callback  Pointer to the error callback function
  * @retval HAL_OK  Operation completed successfully
  * @retval HAL_INVALID_PARAM  Invalid parameter
  */
hal_status_t HAL_I3C_RegisterErrorCallback(hal_i3c_handle_t *hi3c, hal_i3c_cb_t p_callback)
{
  ASSERT_DBG_PARAM((hi3c != NULL));
  ASSERT_DBG_PARAM((p_callback != NULL));
  ASSERT_DBG_STATE(hi3c->global_state, (uint32_t)HAL_I3C_STATE_INIT | (uint32_t)HAL_I3C_STATE_IDLE);

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (p_callback == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  hi3c->p_error_cb = p_callback;

  return HAL_OK;
}
#endif /* USE_HAL_I3C_REGISTER_CALLBACKS */

#if defined(USE_HAL_I3C_DMA) && (USE_HAL_I3C_DMA == 1)
/**
  * @brief  Link the transmit DMA handle to the I3C handle.
  * @param  hi3c  Pointer to a hal_i3c_handle_t
  * @param  hdma  Pointer to a hal_dma_handle_t structure
  * @retval HAL_OK  Operation completed successfully
  * @retval HAL_INVALID_PARAM  Invalid parameter
  */
hal_status_t HAL_I3C_SetTxDMA(hal_i3c_handle_t *hi3c, hal_dma_handle_t *hdma)
{
  ASSERT_DBG_PARAM((hi3c != NULL));
  ASSERT_DBG_PARAM((hdma != NULL));
  ASSERT_DBG_STATE(hi3c->global_state, (uint32_t) HAL_I3C_STATE_RESET | (uint32_t) HAL_I3C_STATE_INIT \
                   | (uint32_t)HAL_I3C_STATE_IDLE);

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (hdma == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  hi3c->hdma_tx = hdma;
  hdma->p_parent = hi3c;

  return HAL_OK;
}

/**
  * @brief  Link the receive DMA handle to the I3C handle.
  * @param  hi3c  Pointer to a hal_i3c_handle_t
  * @param  hdma  Pointer to a hal_dma_handle_t structure
  * @retval HAL_OK  Operation completed successfully
  * @retval HAL_INVALID_PARAM  Invalid parameter
  */
hal_status_t HAL_I3C_SetRxDMA(hal_i3c_handle_t *hi3c, hal_dma_handle_t *hdma)
{
  ASSERT_DBG_PARAM((hi3c != NULL));
  ASSERT_DBG_PARAM((hdma != NULL));
  ASSERT_DBG_STATE(hi3c->global_state, (uint32_t) HAL_I3C_STATE_RESET | (uint32_t) HAL_I3C_STATE_INIT \
                   | (uint32_t) HAL_I3C_STATE_IDLE);

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (hdma == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  hi3c->hdma_rx = hdma;
  hdma->p_parent = hi3c;

  return HAL_OK;
}

/**
  * @brief  Link the CR DMA handle to the I3C handle.
  * @param  hi3c  Pointer to a hal_i3c_handle_t
  * @param  hdma  Pointer to a hal_dma_handle_t structure
  * @retval HAL_OK  Operation completed successfully
  * @retval HAL_INVALID_PARAM  Invalid parameter
  */
hal_status_t HAL_I3C_SetCrDMA(hal_i3c_handle_t *hi3c, hal_dma_handle_t *hdma)
{
  ASSERT_DBG_PARAM((hi3c != NULL));
  ASSERT_DBG_PARAM((hdma != NULL));
  ASSERT_DBG_STATE(hi3c->global_state, (uint32_t)HAL_I3C_STATE_INIT | (uint32_t)HAL_I3C_STATE_IDLE);

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (hdma == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  hi3c->hdma_ctrl = hdma;
  hdma->p_parent = hi3c;

  return HAL_OK;
}
#endif /* USE_HAL_I3C_DMA */
/**
  * @}
  */

/** @addtogroup I3C_Exported_Functions_Group3 Interrupt and callback functions

A set of functions allowing to Notification management function in the I3Cx peripheral:
 - HAL_I3C_CTRL_ActivateNotification() to activate the I3C notifications in controller mode.
 - HAL_I3C_CTRL_DeactivateNotification() to deactivate the I3C notifications in controller mode.
 - HAL_I3C_TGT_ActivateNotification() to activate the I3C notifications in target mode.
 - HAL_I3C_TGT_DeactivateNotification() to deactivate the I3C notifications in target mode.
  * @{
  */

/**
  * @brief  Activate the I3C notifications in controller mode.
  * @param  hi3c  Pointer to a hal_i3c_handle_t
  * @param  notifications  Notification. It can be a combination value of @ref I3C_CTRL_NOTIFICATION
  * @warning This weak function must not be modified. When the callback is needed, it is overridden in the user file.
  * @retval HAL_OK  Operation completed successfully
  */
hal_status_t HAL_I3C_CTRL_ActivateNotification(hal_i3c_handle_t *hi3c, uint32_t notifications)
{
  I3C_TypeDef *p_i3cx;

  ASSERT_DBG_PARAM((hi3c != NULL));
  ASSERT_DBG_PARAM(hi3c->mode == HAL_I3C_MODE_CTRL);
  ASSERT_DBG_PARAM((notifications & ~HAL_I3C_CTRL_NOTIFICATION_ALL) == 0);
  ASSERT_DBG_STATE(hi3c->global_state, HAL_I3C_STATE_IDLE);

  p_i3cx = I3C_GET_INSTANCE(hi3c);
  hi3c->listen = HAL_I3C_LISTEN_ENABLED;
  hi3c->xfer_isr = I3C_Ctrl_Event_ISR;
  LL_I3C_EnableIT(p_i3cx, (notifications | LL_I3C_IER_ERRIE));
  return HAL_OK;
}

/**
  * @brief  Deactivate the I3C notifications.
  * @param  hi3c  Pointer to a hal_i3c_handle_t
  * @param  notifications  Notification. It can be a combination value of @ref I3C_CTRL_NOTIFICATION
  * @retval HAL_OK  Operation completed successfully
  */
hal_status_t HAL_I3C_CTRL_DeactivateNotification(hal_i3c_handle_t *hi3c, uint32_t notifications)
{
  I3C_TypeDef *p_i3cx;

  ASSERT_DBG_PARAM((hi3c != NULL));
  ASSERT_DBG_PARAM(hi3c->mode == HAL_I3C_MODE_CTRL);
  ASSERT_DBG_PARAM((notifications & ~HAL_I3C_CTRL_NOTIFICATION_ALL) == 0);
  ASSERT_DBG_STATE(hi3c->global_state, HAL_I3C_STATE_IDLE);

  p_i3cx = I3C_GET_INSTANCE(hi3c);
  LL_I3C_DisableIT(p_i3cx, (notifications | LL_I3C_IER_ERRIE));

  if (LL_I3C_READ_REG(p_i3cx, IER) == 0U)
  {
    hi3c->xfer_isr = NULL;
    hi3c->listen = HAL_I3C_LISTEN_DISABLED;
    hi3c->global_state = HAL_I3C_STATE_IDLE;
  }

  return HAL_OK;
}

/**
  * @brief  Activate the I3C notifications in target mode.
  * @param  hi3c  Pointer to a hal_i3c_handle_t
  * @param  p_data  Pointer to the retrieve data during broadcast CCC DEFTGTS and DEFGRPA.
  * @param  size_byte  Size of retrieved data.
  * @param  notifications  Notification. It can be a combination value of @ref I3C_TGT_NOTIFICATION
  * @retval HAL_OK  Operation completed successfully
  * @retval HAL_INVALID_PARAM  Invalid parameter
  */
hal_status_t HAL_I3C_TGT_ActivateNotification(hal_i3c_handle_t *hi3c, uint8_t *p_data, uint32_t size_byte,
                                              uint32_t notifications)
{
  I3C_TypeDef *p_i3cx;

  ASSERT_DBG_PARAM((hi3c != NULL));
  ASSERT_DBG_PARAM((notifications & ~HAL_I3C_TGT_NOTIFICATION_ALL) == 0);
  ASSERT_DBG_PARAM(hi3c->mode == HAL_I3C_MODE_TGT);
  ASSERT_DBG_PARAM(((notifications & (LL_I3C_IER_DEFIE | LL_I3C_IER_RXFNEIE | LL_I3C_IER_GRPIE \
                                      | LL_I3C_IER_RXFNEIE)) == 0U || (p_data != NULL && size_byte != 0U)));
  ASSERT_DBG_STATE(hi3c->global_state, HAL_I3C_STATE_IDLE);

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (((notifications & (LL_I3C_IER_DEFIE | LL_I3C_IER_RXFNEIE | LL_I3C_IER_GRPIE | LL_I3C_IER_RXFNEIE)) != 0U)
      && ((p_data == NULL) || (size_byte == 0U)))
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  p_i3cx = I3C_GET_INSTANCE(hi3c);
  hi3c->xfer_isr = I3C_Tgt_Event_ISR;
  hi3c->listen = HAL_I3C_LISTEN_ENABLED;

  if ((notifications & (LL_I3C_IER_DEFIE | LL_I3C_IER_RXFNEIE | LL_I3C_IER_GRPIE | LL_I3C_IER_RXFNEIE)) != 0U)
  {
    hi3c->p_rx_data = p_data;
    hi3c->rx_count = size_byte;

    if (LL_I3C_GetRxFIFOThreshold(p_i3cx) == LL_I3C_RXFIFO_THRESHOLD_1_4)
    {
      hi3c->p_rx_func = &I3C_ReceiveByteTreatment;
    }
    else
    {
      hi3c->p_rx_func = &I3C_ReceiveWordTreatment;
    }
  }

  LL_I3C_EnableIT(p_i3cx, (notifications | LL_I3C_IER_ERRIE));

  return HAL_OK;
}


/**
  * @brief  Deactivate the I3C notifications.
  * @param  hi3c  Pointer to a hal_i3c_handle_t
  * @param  notifications  Notification. It can be a combination value of @ref I3C_TGT_NOTIFICATION
  * @retval HAL_OK  Operation completed successfully
  */
hal_status_t HAL_I3C_TGT_DeactivateNotification(hal_i3c_handle_t *hi3c, uint32_t notifications)
{
  I3C_TypeDef *p_i3cx;

  ASSERT_DBG_PARAM((hi3c != NULL));
  ASSERT_DBG_PARAM((notifications & ~HAL_I3C_TGT_NOTIFICATION_ALL) == 0);
  ASSERT_DBG_PARAM(hi3c->mode == HAL_I3C_MODE_TGT);
  ASSERT_DBG_STATE(hi3c->global_state, HAL_I3C_STATE_IDLE);

  p_i3cx = I3C_GET_INSTANCE(hi3c);
  LL_I3C_DisableIT(p_i3cx, (notifications | LL_I3C_IER_ERRIE));

  if (LL_I3C_READ_REG(p_i3cx, IER) == 0U)
  {
    hi3c->xfer_isr = NULL;
    hi3c->listen = HAL_I3C_LISTEN_DISABLED;
    hi3c->global_state = HAL_I3C_STATE_IDLE;
  }

  return HAL_OK;
}
/**
  * @}
  */

/** @addtogroup I3C_Exported_Functions_Group4 IRQ Handlers
  * @{
A Set of function to handle the I3C interruptions:
  - I3C Event IRQ Handler: HAL_I3C_EV_IRQHandler()
  - I3C Error IRQ Handler: HAL_I3C_ERR_IRQHandler()

Depending on the process function one's use, different callback might be triggered:

| Process API \n \ \n Callbacks                | HAL_I3C_CTRL_DynAddrAssign_IT() |
|----------------------------------------------|:-------------------------------:|
| HAL_I3C_CTRL_DAACpltCallback()               |               x                 |
| HAL_I3C_CTRL_TgtReqDynAddrCallback()         |               x                 |
| HAL_I3C_ErrorCallback()                      |               x                 |

| Process API \n \ \n Callbacks                | HAL_I3C_CTRL_StartXfer_IT()     | HAL_I3C_CTRL_StartXfer_DMA()    |
|----------------------------------------------|:-------------------------------:|:-------------------------------:|
| HAL_I3C_CTRL_XferCpltCallback()              |               x                 |               x                 |
| HAL_I3C_NotifyCallback()*                    |               x                 |               x                 |
| HAL_I3C_ErrorCallback()                      |               x                 |               x                 |

| Process API \n \ \n Callbacks                | HAL_I3C_TGT_Transmit_IT()       | HAL_I3C_TGT_Transmit_DMA()      |
|----------------------------------------------|:-------------------------------:|:-------------------------------:|
| HAL_I3C_TGT_TxCpltCallback()                 |               x                 |               x                 |
| HAL_I3C_NotifyCallback()*                    |               x                 |               x                 |
| HAL_I3C_ErrorCallback()                      |               x                 |               x                 |

| Process API \n \ \n Callbacks                | HAL_I3C_TGT_Receive_IT()        | HAL_I3C_TGT_Receive_DMA()       |
|----------------------------------------------|:-------------------------------:|:-------------------------------:|
| HAL_I3C_TGT_RxCpltCallback()                 |               x                 |               x                 |
| HAL_I3C_NotifyCallback()*                    |               x                 |               x                 |
| HAL_I3C_ErrorCallback()                      |               x                 |               x                 |

| Process API \n \ \n Callbacks                | HAL_I3C_TGT_HotJoinReq_IT()     |
|----------------------------------------------|:-------------------------------:|
| HAL_I3C_TGT_HotJoinCallback()                |               x                 |
| HAL_I3C_ErrorCallback()                      |               x                 |

| Process API \n \ \n Callbacks                | HAL_I3C_TGT_ControlRoleReq_IT() |
|----------------------------------------------|:-------------------------------:|
| HAL_I3C_NotifyCallback(HAL_I3C_TGT_NOTIFICATION_GETACCCR)|   x                 |
| HAL_I3C_ErrorCallback()                      |               x                 |

| Process API \n \ \n Callbacks                | HAL_I3C_TGT_IBIReq_IT()         |
|----------------------------------------------|:-------------------------------:|
| HAL_I3C_NotifyCallback(HAL_I3C_TGT_NOTIFICATION_IBIEND)|     x                 |
| HAL_I3C_ErrorCallback()                      |               x                 |

| Process API \n \ \n Callbacks                | HAL_I3C_Abort_IT()              |
|----------------------------------------------|:-------------------------------:|
| HAL_I3C_AbortCpltCallback()                  |               x                 |

@note * HAL_I3C_NotifyCallback() is triggered if HAL_I3C_CTRL_ActivateNotification or HAL_I3C_TGT_ActivateNotification
        have been previously called in state HAL_I3C_STATE_IDLE
  */

/**
  * @brief  Handle I3C error interrupt request.
  * @param  hi3c  Pointer to a hal_i3c_handle_t
  */
void HAL_I3C_ERR_IRQHandler(hal_i3c_handle_t *hi3c)
{
  I3C_TypeDef *p_i3cx = I3C_GET_INSTANCE(hi3c);
  uint32_t it_flag = LL_I3C_READ_REG(p_i3cx, EVR);
  uint32_t it_source = LL_I3C_READ_REG(p_i3cx, IER);

  /* Check on the error interrupt flag and source */
  if ((I3C_CHECK_FLAG(it_flag, LL_I3C_EVR_ERRF) != 0U) && (I3C_CHECK_IT_SOURCE(it_source, LL_I3C_IER_ERRIE) != 0U))
  {
    LL_I3C_ClearFlag_ERR(p_i3cx);

#if defined(USE_HAL_I3C_GET_LAST_ERRORS) && (USE_HAL_I3C_GET_LAST_ERRORS == 1)
    if (hi3c->global_state != HAL_I3C_STATE_ABORT)
    {
      I3C_GetErrorSources(hi3c);
    }
#endif /* USE_HAL_I3C_GET_LAST_ERRORS */

    I3C_ErrorTreatment(hi3c);
  }
}

/**
  * @brief  Handle I3C event interrupt request.
  * @param  hi3c  Pointer to a hal_i3c_handle_t
  */
void HAL_I3C_EV_IRQHandler(hal_i3c_handle_t *hi3c)
{
  const I3C_TypeDef *p_i3cx = I3C_GET_INSTANCE(hi3c);

  uint32_t it_masks = LL_I3C_READ_REG(p_i3cx, MISR);

  /* I3C events treatment */
  if (hi3c->xfer_isr != NULL)
  {
    hi3c->xfer_isr(hi3c, it_masks);
  }
}

/**
  * @}
  */

/** @addtogroup I3C_Exported_Functions_Group5 FIFO management functions
  * @{
A set of functions allowing to manage I3C FIFOs:
  - HAL_I3C_FlushAllFifo() to flush the content of all used FIFOs (Control, Status, Tx and Rx FIFO).
  - HAL_I3C_FlushTxFifo() to flush only the content of Tx FIFO.
  - HAL_I3C_FlushRxFifo() to flush only the content of Rx FIFO.
  - HAL_I3C_FlushControlFifo() to flush only the content of Control FIFO.
    This function is called only when mode is controller.
  - HAL_I3C_FlushStatusFifo() to flush only the content of Status FIFO.
    This function is called only when mode is controller.
  */

/**
  * @brief  Flush all I3C FIFOs content.
  * @param  hi3c  Pointer to a hal_i3c_handle_t
  * @retval HAL_OK  Operation completed successfully
  */
hal_status_t HAL_I3C_FlushAllFifo(const hal_i3c_handle_t *hi3c)
{
  I3C_TypeDef *p_i3cx;
  uint32_t cfgr_value;

  ASSERT_DBG_PARAM((hi3c != NULL));
  ASSERT_DBG_STATE(hi3c->global_state, I3C_STATE_ALL_EXCEPT_INIT);

  p_i3cx = I3C_GET_INSTANCE(hi3c);

  /* Flush the content of Tx and Rx Fifo */
  cfgr_value = (I3C_CFGR_TXFLUSH | I3C_CFGR_RXFLUSH);

  /* Check on the I3C mode: Control and status FIFOs available only with controller mode */
  if (hi3c->mode == HAL_I3C_MODE_CTRL)
  {
    /* Flush the content of control and status Fifo */
    cfgr_value |= (I3C_CFGR_SFLUSH | I3C_CFGR_CFLUSH);
  }

  STM32_MODIFY_REG(p_i3cx->CFGR, cfgr_value, cfgr_value);

  return HAL_OK;
}

/**
  * @brief  Flush I3C Tx FIFO content.
  * @param  hi3c  Pointer to a hal_i3c_handle_t
  * @retval HAL_OK  Operation completed successfully
  */
hal_status_t HAL_I3C_FlushTxFifo(const hal_i3c_handle_t *hi3c)
{
  I3C_TypeDef *p_i3cx;

  ASSERT_DBG_PARAM((hi3c != NULL));
  ASSERT_DBG_STATE(hi3c->global_state, I3C_STATE_ALL_EXCEPT_INIT);

  p_i3cx = I3C_GET_INSTANCE(hi3c);
  LL_I3C_RequestTxFIFOFlush(p_i3cx);

  return HAL_OK;
}

/**
  * @brief  Flush I3C Rx FIFO content.
  * @param  hi3c  Pointer to a hal_i3c_handle_t
  * @retval HAL_OK  Operation completed successfully
  */
hal_status_t HAL_I3C_FlushRxFifo(const hal_i3c_handle_t *hi3c)
{
  I3C_TypeDef *p_i3cx;

  ASSERT_DBG_PARAM((hi3c != NULL));
  ASSERT_DBG_STATE(hi3c->global_state, I3C_STATE_ALL_EXCEPT_INIT);

  p_i3cx = I3C_GET_INSTANCE(hi3c);
  LL_I3C_RequestRxFIFOFlush(p_i3cx);

  return HAL_OK;
}

/**
  * @brief  Flush I3C control FIFO content.
  * @param  hi3c  Pointer to a hal_i3c_handle_t
  * @note   This API can be used when the I3C is acting as controller.
  * @retval HAL_OK  Operation completed successfully
  */
hal_status_t HAL_I3C_FlushControlFifo(const hal_i3c_handle_t *hi3c)
{
  I3C_TypeDef *p_i3cx;

  ASSERT_DBG_PARAM((hi3c != NULL));
  ASSERT_DBG_PARAM(hi3c->mode == HAL_I3C_MODE_CTRL);
  ASSERT_DBG_STATE(hi3c->global_state, I3C_STATE_ALL_EXCEPT_INIT);

  p_i3cx = I3C_GET_INSTANCE(hi3c);
  LL_I3C_RequestControlFIFOFlush(p_i3cx);

  return HAL_OK;
}

/**
  * @brief  Flush I3C status FIFO content.
  * @param  hi3c  Pointer to a hal_i3c_handle_t
  * @note   This API can be used when the I3C is acting as controller.
  * @retval HAL_OK  Operation completed successfully
  */
hal_status_t HAL_I3C_FlushStatusFifo(const hal_i3c_handle_t *hi3c)
{
  I3C_TypeDef *p_i3cx;

  ASSERT_DBG_PARAM((hi3c != NULL));
  ASSERT_DBG_PARAM(hi3c->mode == HAL_I3C_MODE_CTRL);
  ASSERT_DBG_STATE(hi3c->global_state, I3C_STATE_ALL_EXCEPT_INIT);

  p_i3cx = I3C_GET_INSTANCE(hi3c);
  LL_I3C_RequestStatusFIFOFlush(p_i3cx);

  return HAL_OK;
}

/**
  * @}
  */


/** @addtogroup I3C_Exported_Functions_Group6 Controller transfer operation functions
  * @{
 A set of functions allowing to manage controller I3C transfer operation:
  - HAL_I3C_CTRL_ResetXferCtx() to reset a transfer context.
  - HAL_I3C_CTRL_InitXferCtxCtrl() to provide a ctrl buffer. It will be filled by HAL_I3C_CTRL_BuildXferCtxPrivate() or
    HAL_I3C_CTRL_BuildXferCtxCCC().
  - HAL_I3C_CTRL_InitXferCtxTx() to provide the Tx buffer. It must be filled by application with concatenated Tx data.
  - HAL_I3C_CTRL_InitXferCtxRx() to provide the Rx buffer.
  - HAL_I3C_CTRL_BuildXferCtxPrivate() or HAL_I3C_CTRL_BuildXferCtxCCC() to build transfer context
  - HAL_I3C_CTRL_StartXfer() to start transfer I3C or I2C private data or CCC command in multiple direction
    in polling mode.
  - HAL_I3C_CTRL_StartXfer_IT() to start transfer I3C or I2C private data or CCC command in multiple direction
    in interrupt mode.
  - HAL_I3C_CTRL_StartXfer_DMA() to start transfer I3C or I2C private data or CCC command in multiple direction
    in DMA mode.
  - HAL_I3C_CTRL_DynAddrAssign() to send a broadcast ENTDAA CCC command in polling mode.
  - HAL_I3C_CTRL_DynAddrAssign_IT() to send a broadcast ENTDAA CCC command in interrupt mode.
  - HAL_I3C_CTRL_SetDynAddr() to set, associate the target dynamic address during the Dynamic Address Assignment
    process.
  - HAL_I3C_CTRL_IsDeviceI3C_Ready() to check if I3C target device is ready.
  - HAL_I3C_CTRL_IsDeviceI2C_Ready() to check if I2C target device is ready.
  - HAL_I3C_CTRL_GeneratePatterns() to send HDR exit pattern or target reset pattern.
  - HAL_I3C_CTRL_GenerateArbitration() to send arbitration (message header {S + 0x7E + W + STOP}) in polling mode.
  - HAL_I3C_CTRL_RecoverSCLToIDLE() to force the stop of the SCL clock.
  */


/**
  * @brief  Reset a controller transfer context.
  * @param  p_ctx  Pointer the transfer context
  * @retval HAL_OK  Operation completed successfully
  * @retval HAL_INVALID_PARAM  Invalid  parameter
  */
hal_status_t HAL_I3C_CTRL_ResetXferCtx(hal_i3c_xfer_ctx_t *p_ctx)
{
  ASSERT_DBG_PARAM((p_ctx != NULL));

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (p_ctx == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  p_ctx->p_ctrl_data = NULL;
  p_ctx->ctrl_size_word = 0UL;
  p_ctx->p_ctrl_data = NULL;
  p_ctx->ctrl_size_word = 0UL;
  p_ctx->p_tx_data = NULL;
  p_ctx->tx_size_byte = 0UL;
  p_ctx->p_rx_data = NULL;
  p_ctx->rx_size_byte = 0UL;
  p_ctx->xfer_mode = (hal_i3c_xfer_mode_t) 0UL;
#if defined(USE_ASSERT_DBG_PARAM) || (defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1))
  p_ctx->nb_tx_frame = 0UL;
#endif /* (USE_ASSERT_DBG_PARAM) | (USE_HAL_CHECK_PARAM) */

  return HAL_OK;
}


/**
  * @brief  Initialise the transfer context with ctrl buffer.
  * @param  p_ctx  Pointer the transfer context
  * @param  p_ctrl_buf Pointer the control buffer.
  * @param  size_word  Size in word of the to control buffer.
  *                    size word = 2* number of description in case of direct CCC transfers
  *                    size word = number of description for all other transfers
  *                    Use helper macro @ref HAL_I3C_GET_CTRL_BUFFER_SIZE_WORD
  * @retval HAL_OK  Operation completed successfully
  * @retval HAL_INVALID_PARAM  Invalid parameter
  */
hal_status_t HAL_I3C_CTRL_InitXferCtxCtrl(hal_i3c_xfer_ctx_t *p_ctx, uint32_t *p_ctrl_buf, uint32_t size_word)
{
  hal_status_t hal_status = HAL_OK;

  ASSERT_DBG_PARAM((p_ctx != NULL));
  ASSERT_DBG_PARAM((p_ctrl_buf != NULL));
  ASSERT_DBG_PARAM((size_word != 0U));

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if ((p_ctx == NULL) || (p_ctrl_buf == NULL) || (size_word == 0U))
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  p_ctx->p_ctrl_data = p_ctrl_buf;
  p_ctx->ctrl_size_word = size_word;

  return hal_status;
}

/**
  * @brief  Initialise the transfer context with Tx data.
  * @param  p_ctx  Pointer the transfer context
  * @param  p_tx_data  Pointer the Cumulated Tx buffer (@ref HAL_I3C_DIRECTION_WRITE)
  * @param  size_byte  Size in byte of Tx data
  * @retval HAL_OK  Operation completed successfully
  * @retval HAL_INVALID_PARAM  Invalid parameter
  */
hal_status_t HAL_I3C_CTRL_InitXferCtxTx(hal_i3c_xfer_ctx_t *p_ctx, const uint8_t *p_tx_data, uint32_t size_byte)
{
  hal_status_t hal_status = HAL_OK;

  ASSERT_DBG_PARAM((p_ctx != NULL));
  ASSERT_DBG_PARAM((p_tx_data != NULL));
  ASSERT_DBG_PARAM((size_byte != 0U));

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if ((p_ctx == NULL) || (p_tx_data == NULL) || (size_byte == 0U))
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  p_ctx->p_tx_data = p_tx_data;
  p_ctx->tx_size_byte = size_byte;

  return hal_status;
}

/**
  * @brief  Initialise the transfer context with Rx data.
  * @param  p_ctx  Pointer the transfer context
  * @param  p_rx_data  Pointer the Cumulated Rx buffer (@ref HAL_I3C_DIRECTION_WRITE)
  * @param  size_byte  Size in byte of Rx data
  * @retval HAL_OK  Operation completed successfully
  * @retval HAL_INVALID_PARAM  Invalid parameter
  */
hal_status_t HAL_I3C_CTRL_InitXferCtxRx(hal_i3c_xfer_ctx_t *p_ctx, uint8_t *p_rx_data, uint32_t size_byte)
{
  hal_status_t hal_status = HAL_OK;

  ASSERT_DBG_PARAM((p_ctx != NULL));
  ASSERT_DBG_PARAM((p_rx_data != NULL));
  ASSERT_DBG_PARAM((size_byte != 0U));

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if ((p_ctx == NULL) || (p_rx_data == NULL) || (size_byte == 0U))
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  p_ctx->p_rx_data = p_rx_data;
  p_ctx->rx_size_byte = size_byte;

  return hal_status;
}

/**
  * @brief  Build a transfer context from private transfer descriptors.
  * @param  p_ctx  Pointer the transfer context
  * @param  p_desc  Pointer to the private transfer descriptor table.
  * @param  nb_desc  The number private transfer descriptor.
  * @param  mode  Transfer mode. It must one of PRIVATE mode from @ref hal_i3c_xfer_mode_t
  * @note   This API can be used when the I3C is acting as controller.
  * @note   This transfer context must be previously initialized thanks to:
  *           - HAL_I3C_CTRL_ResetXferCtx(), mandatory
  *           - HAL_I3C_CTRL_InitXferCtxCtrl(), mandatory
  *           - HAL_I3C_CTRL_InitXferCtxTx(), not needed if no write in description
  *           - HAL_I3C_CTRL_InitXferCtxRx(), not needed if no read in description
  * @retval HAL_OK  Operation completed successfully
  * @retval HAL_ERROR  Operation completed with error
  * @retval HAL_INVALID_PARAM  Invalid parameter
  */
hal_status_t HAL_I3C_CTRL_BuildXferCtxPrivate(hal_i3c_xfer_ctx_t *p_ctx, const hal_i3c_private_desc_t *p_desc,
                                              uint32_t nb_desc, hal_i3c_xfer_mode_t mode)
{
  hal_status_t hal_status = HAL_OK;
  uint32_t stop_condition;
#if defined(USE_ASSERT_DBG_PARAM) || (defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1))
  uint32_t tx_cumul_size_byte = 0UL;
  uint32_t rx_cumul_size_byte = 0UL;
#endif /* USE_ASSERT_DBG_PARAM | USE_HAL_CHECK_PARAM */

  ASSERT_DBG_PARAM((p_ctx != NULL));
  ASSERT_DBG_PARAM((p_desc != NULL));
  ASSERT_DBG_PARAM((nb_desc != 0U));
  ASSERT_DBG_PARAM(IS_I3C_PRIVATE_MODE(mode));
  ASSERT_DBG_PARAM((p_ctx->p_ctrl_data != NULL));
  ASSERT_DBG_PARAM((p_ctx->ctrl_size_word == nb_desc));

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if ((p_desc == NULL) || (nb_desc == 0U) || (p_ctx == NULL) || (p_ctx->p_ctrl_data == NULL)
      || (p_ctx->ctrl_size_word != nb_desc))
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  p_ctx->xfer_mode = mode;
  stop_condition = (uint32_t)mode & (uint32_t)I3C_RESTART_STOP_MASK;
  /*-------------------------------------------- Private -------------------------------------------------------------*/
  for (uint32_t i = 0UL; i < nb_desc; i++)
  {
    uint32_t data_size_byte = p_desc[i].data_size_byte;
    uint32_t direction = (uint32_t) p_desc[i].direction;

    /* At the end, generate a stop condition */
    if (i == (nb_desc - 1U))
    {
      stop_condition = LL_I3C_GENERATE_STOP;
    }

    /* Update control buffer value */
    p_ctx->p_ctrl_data[i] = (data_size_byte | direction | ((uint32_t)p_desc[i].tgt_addr << I3C_CR_ADD_Pos)
                             | ((uint32_t)mode & (uint32_t)I3C_OPERATION_TYPE_MASK) | stop_condition);

#if defined(USE_ASSERT_DBG_PARAM) || (defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1))
    if (direction == (uint32_t) HAL_I3C_DIRECTION_WRITE)
    {
      tx_cumul_size_byte += data_size_byte;
    }
    else
    {
      rx_cumul_size_byte += data_size_byte;
    }
#endif /* USE_ASSERT_DBG_PARAM | USE_HAL_CHECK_PARAM */
  }

  ASSERT_DBG_PARAM((p_ctx->tx_size_byte == tx_cumul_size_byte));
  ASSERT_DBG_PARAM((p_ctx->rx_size_byte == rx_cumul_size_byte));
  ASSERT_DBG_PARAM((tx_cumul_size_byte == 0U) || (p_ctx->p_tx_data != NULL));
  ASSERT_DBG_PARAM((rx_cumul_size_byte == 0U) || (p_ctx->p_rx_data != NULL));

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if ((p_ctx->tx_size_byte != tx_cumul_size_byte)
      || (p_ctx->rx_size_byte != rx_cumul_size_byte)
      || ((tx_cumul_size_byte != 0U) && (p_ctx->p_tx_data == NULL))
      || ((rx_cumul_size_byte != 0U) && (p_ctx->p_rx_data == NULL)))
  {
    hal_status = HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  return hal_status;
}

/**
  * @brief  Build a transfer context from CCC transfer descriptor.
  * @param  p_desc  Pointer to the CCC transfer descriptor table
  * @param  nb_desc  The number CCC transfer descriptor
  * @param  p_ctx  Pointer the transfer context
  * @param  mode  Transfer mode. It must one of CCC mode from @ref hal_i3c_xfer_mode_t
  * @note   This API can be used when the I3C is acting as controller.
  * @note   This transfer context must be previously initialized thanks to:
  *           @ref HAL_I3C_CTRL_ResetXferCtx (mandatory)
  *           @ref HAL_I3C_CTRL_InitXferCtxCtrl (mandatory)
  *           @ref HAL_I3C_CTRL_InitXferCtxTx (not needed if no write in description)
  *           @ref HAL_I3C_CTRL_InitXferCtxRx (not needed if no read in description)
  * @retval HAL_OK  Operation completed successfully
  * @retval HAL_ERROR  Operation completed with error
  * @retval HAL_INVALID_PARAM  Invalid parameter
  */
hal_status_t HAL_I3C_CTRL_BuildXferCtxCCC(hal_i3c_xfer_ctx_t *p_ctx, const hal_i3c_ccc_desc_t *p_desc,
                                          uint32_t nb_desc, hal_i3c_xfer_mode_t mode)
{
  hal_status_t hal_status = HAL_OK;
  uint32_t stop_condition;
#if defined(USE_ASSERT_DBG_PARAM) || (defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1))
  uint32_t tx_cumul_size_byte = 0UL;
  uint32_t rx_cumul_size_byte = 0UL;
#endif /* USE_ASSERT_DBG_PARAM | USE_HAL_CHECK_PARAM */

  ASSERT_DBG_PARAM((p_desc != NULL));
  ASSERT_DBG_PARAM((nb_desc != 0U));
  ASSERT_DBG_PARAM((p_ctx != NULL));
  ASSERT_DBG_PARAM((p_ctx->p_ctrl_data != NULL));
  ASSERT_DBG_PARAM(IS_I3C_CCC_MODE(mode));

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if ((p_desc == NULL) || (nb_desc == 0U) || (p_ctx == NULL) || (p_ctx->p_ctrl_data == NULL))
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

#if defined(USE_ASSERT_DBG_PARAM) || (defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1))
  p_ctx->nb_tx_frame = 0UL;
#endif /* USE_ASSERT_DBG_PARAM | USE_HAL_CHECK_PARAM */

  stop_condition = (uint32_t)mode & (uint32_t)I3C_RESTART_STOP_MASK;
  p_ctx->xfer_mode = mode;

  if (((uint32_t)mode & (uint32_t)I3C_OPERATION_TYPE_MASK) == LL_I3C_CONTROLLER_MTYPE_CCC)
  {
    /*------------------------------------------ Broadcast CCC -------------------------------------------------------*/
    ASSERT_DBG_PARAM((p_ctx->ctrl_size_word >= nb_desc));

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
    if (p_ctx->ctrl_size_word !=  nb_desc)
    {
      return HAL_INVALID_PARAM;
    }
#endif /* USE_HAL_CHECK_PARAM */

    p_ctx->ctrl_size_word = nb_desc;

    for (uint32_t i = 0UL; i < nb_desc; i++)
    {
      ASSERT_DBG_PARAM(IS_I3C_DIRECTION_CCC_BROADCAST(p_desc[i].direction));
      uint32_t data_size_byte = p_desc[i].data_size_byte;

      /* Only HAL_I3C_DIRECTION_WRITE is allowed */
#if defined(USE_ASSERT_DBG_PARAM) || (defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1))
      tx_cumul_size_byte += data_size_byte;
      p_ctx->nb_tx_frame++;
#endif /* USE_ASSERT_DBG_PARAM | USE_HAL_CHECK_PARAM */

      /* Generate a stop condition at the end */
      if (i == (nb_desc - 1U))
      {
        stop_condition = LL_I3C_GENERATE_STOP;
      }

      /* Update control buffer value */
      p_ctx->p_ctrl_data[i] = data_size_byte | ((uint32_t)p_desc[i].ccc << I3C_CR_CCC_Pos)
                              | LL_I3C_CONTROLLER_MTYPE_CCC | stop_condition;
    }
  }
  else if (((uint32_t)mode & (uint32_t)I3C_OPERATION_TYPE_MASK) == LL_I3C_CONTROLLER_MTYPE_DIRECT)
  {
    /*------------------------------------------ Direct CCC ----------------------------------------------------------*/
    ASSERT_DBG_PARAM((p_ctx->ctrl_size_word >= (2UL * nb_desc)));

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
    if (p_ctx->ctrl_size_word != (2UL * nb_desc))
    {
      return HAL_INVALID_PARAM;
    }
#endif /* USE_HAL_CHECK_PARAM */

    uint32_t nb_define_bytes = ((uint32_t)mode & (uint32_t)I3C_DEFINE_BYTE_MASK);  /* 0 or 1 */
    p_ctx->ctrl_size_word = 2U * nb_desc;

    uint32_t i = 0U;
    uint32_t double_i = 0U;
    while (i < nb_desc)
    {
      uint32_t direction = (uint32_t)p_desc[i].direction;
      uint32_t data_size_byte = p_desc[i].data_size_byte;
      ASSERT_DBG_PARAM(IS_I3C_DIRECTION(direction));

#if defined(USE_ASSERT_DBG_PARAM) || (defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1))
      if (direction == (uint32_t) HAL_I3C_DIRECTION_READ)
      {
        tx_cumul_size_byte += nb_define_bytes;
        rx_cumul_size_byte += (data_size_byte - nb_define_bytes);
      }
      else  /* direction == HAL_I3C_DIRECTION_WRITE */
      {
        tx_cumul_size_byte += data_size_byte;
        p_ctx->nb_tx_frame++;
      }
#endif /* USE_ASSERT_DBG_PARAM | USE_HAL_CHECK_PARAM */

      /* Generate a stop condition at the end */
      if (i == (nb_desc - 1U))
      {
        stop_condition = LL_I3C_GENERATE_STOP;
      }

      /* Update control buffer value for the CCC command */
      p_ctx->p_ctrl_data[double_i] = nb_define_bytes | ((uint32_t)p_desc[i].ccc << I3C_CR_CCC_Pos)
                                     | LL_I3C_CONTROLLER_MTYPE_CCC | LL_I3C_GENERATE_RESTART;

      /* Update control buffer value for target address */
      p_ctx->p_ctrl_data[double_i + 1U] = (data_size_byte - nb_define_bytes) | direction |
                                          ((uint32_t)p_desc[i].tgt_addr << I3C_CR_ADD_Pos)
                                          | LL_I3C_CONTROLLER_MTYPE_DIRECT | stop_condition;
      i++;
      double_i += 2U;
    }
  }

  ASSERT_DBG_PARAM((p_ctx->tx_size_byte == tx_cumul_size_byte));
  ASSERT_DBG_PARAM((p_ctx->rx_size_byte == rx_cumul_size_byte));
  ASSERT_DBG_PARAM((tx_cumul_size_byte == 0U) || (p_ctx->p_tx_data != NULL));
  ASSERT_DBG_PARAM((rx_cumul_size_byte == 0U) || (p_ctx->p_rx_data != NULL));

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if ((p_ctx->tx_size_byte != tx_cumul_size_byte)
      || (p_ctx->rx_size_byte != rx_cumul_size_byte)
      || ((tx_cumul_size_byte != 0U) && (p_ctx->p_tx_data == NULL))
      || ((rx_cumul_size_byte != 0U) && (p_ctx->p_rx_data == NULL)))
  {
    hal_status = HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  return hal_status;
}

/**
  * @brief  Start transfer Direct CCC Command, I3C private or I2C transfer in polling mode.
  * @param  hi3c  Pointer to a hal_i3c_handle_t
  * @param  p_ctx  Pointer to a hal_i3c_xfer_ctx_t structure. It can be reused to start again the
                   same transfer. This transfer context is built by @ref HAL_I3C_CTRL_BuildXferCtxPrivate() or
  *                @ref HAL_I3C_CTRL_BuildXferCtxCCC().
  * @param  timeout_ms  Timeout duration in milliseconds
  * @note   This API can be used when the I3C is acting as controller.
  * @note   The function @ref HAL_I3C_CTRL_BuildXferCtxPrivate() must be called before initiate a private transfer or
  *         the function @ref HAL_I3C_CTRL_BuildXferCtxCCC() must be called before initiate a CCC transfer.
  * @retval HAL_OK  Operation completed successfully
  * @retval HAL_BUSY  Concurrent process ongoing
  * @retval HAL_TIMEOUT  Operation exceeds user timeout
  * @retval HAL_ERROR  Operation completed with error
  * @retval HAL_INVALID_PARAM  Invalid parameter
  */
hal_status_t HAL_I3C_CTRL_StartXfer(hal_i3c_handle_t *hi3c, const hal_i3c_xfer_ctx_t *p_ctx, uint32_t timeout_ms)
{
  I3C_TypeDef *p_i3cx;
  hal_status_t hal_status = HAL_OK;
  uint32_t tickstart;
  uint32_t exit_condition;

  ASSERT_DBG_PARAM((hi3c != NULL));
  ASSERT_DBG_PARAM((p_ctx != NULL));
  ASSERT_DBG_PARAM((p_ctx->rx_size_byte == 0U) || (p_ctx->p_rx_data != NULL));
  ASSERT_DBG_PARAM((p_ctx->tx_size_byte == 0U) || (p_ctx->p_tx_data != NULL));
  ASSERT_DBG_PARAM(p_ctx->p_ctrl_data != NULL);
  ASSERT_DBG_PARAM(p_ctx->ctrl_size_word != 0U);
  ASSERT_DBG_PARAM(hi3c->mode == HAL_I3C_MODE_CTRL);
  p_i3cx = I3C_GET_INSTANCE(hi3c);
  ASSERT_DBG_PARAM(!((LL_I3C_GetTxFIFOThreshold(p_i3cx) == LL_I3C_TXFIFO_THRESHOLD_4_4) && (p_ctx->nb_tx_frame > 1) \
                     && ((p_ctx->xfer_mode & I3C_OPERATION_TYPE_MASK) == LL_I3C_CONTROLLER_MTYPE_DIRECT)));
  ASSERT_DBG_STATE(hi3c->global_state, HAL_I3C_STATE_IDLE);

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  uint32_t is_invalid_param = 0U;

  if (p_ctx == NULL)
  {
    is_invalid_param = 1U;
  }
  else if ((p_ctx->p_rx_data == NULL) && (p_ctx->rx_size_byte != 0U))
  {
    is_invalid_param = 1U;
  }
  else if ((p_ctx->p_tx_data == NULL) && (p_ctx->tx_size_byte != 0U))
  {
    is_invalid_param = 1U;
  }
  else if (p_ctx->p_ctrl_data == NULL)
  {
    is_invalid_param = 1U;
  }
  else if ((p_ctx->p_ctrl_data == NULL) || (p_ctx->ctrl_size_word == 0U))
  {
    is_invalid_param = 1U;
  }
  else if ((LL_I3C_GetTxFIFOThreshold(p_i3cx) == LL_I3C_TXFIFO_THRESHOLD_4_4)
           && (p_ctx->nb_tx_frame > 1U)
           && (((uint32_t)p_ctx->xfer_mode & I3C_OPERATION_TYPE_MASK) == LL_I3C_CONTROLLER_MTYPE_DIRECT))
  {
    is_invalid_param = 1U;
  }
  else
  {
    /* nothing to do */
  }

  if (is_invalid_param == 1U)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */
  HAL_CHECK_UPDATE_STATE(hi3c, global_state, HAL_I3C_STATE_IDLE, HAL_I3C_STATE_TX_RX);

  /* Disable notification IT */
  uint32_t its = LL_I3C_READ_REG(p_i3cx, IER);
  LL_I3C_DisableIT(p_i3cx, its);

#if defined(USE_HAL_I3C_GET_LAST_ERRORS) && (USE_HAL_I3C_GET_LAST_ERRORS == 1)
  hi3c->last_error_codes = HAL_I3C_ERROR_NONE;
#endif /* USE_HAL_I3C_GET_LAST_ERRORS */
  hi3c->p_ctrl_data = p_ctx->p_ctrl_data;
  hi3c->p_tx_data = p_ctx->p_tx_data;
  hi3c->p_rx_data = p_ctx->p_rx_data;
  hi3c->ctrl_count = p_ctx->ctrl_size_word;
  hi3c->tx_count = p_ctx->tx_size_byte;
  hi3c->rx_count = p_ctx->rx_size_byte;

  /* Check on the deactivation of the arbitration */
  if (((uint32_t)p_ctx->xfer_mode & I3C_ARBITRATION_HEADER_MASK) == I3C_ARBITRATION_HEADER_MASK)
  {
    LL_I3C_DisableArbitrationHeader(p_i3cx);
  }
  else
  {
    LL_I3C_EnableArbitrationHeader(p_i3cx);
  }

  /* Check on the Tx threshold to know the Tx treatment process: byte or word */
  if (LL_I3C_GetTxFIFOThreshold(p_i3cx) == LL_I3C_TXFIFO_THRESHOLD_1_4)
  {
    hi3c->p_tx_func = &I3C_TransmitByteTreatment;
  }
  else
  {
    hi3c->p_tx_func = &I3C_TransmitWordTreatment;
  }

  /* Check on the Rx threshold to know the Rx treatment process: byte or word */
  if (LL_I3C_GetRxFIFOThreshold(p_i3cx) == LL_I3C_RXFIFO_THRESHOLD_1_4)
  {
    hi3c->p_rx_func = &I3C_ReceiveByteTreatment;
  }
  else
  {
    hi3c->p_rx_func = &I3C_ReceiveWordTreatment;
  }

  tickstart = HAL_GetTick();

  if (LL_I3C_IsEnabledControlFIFO(p_i3cx) == 1U)
  {
    /* Initiate a Start condition */
    LL_I3C_RequestTransfer(p_i3cx);
  }
  else
  {
    LL_I3C_WRITE_REG(p_i3cx, CR, *hi3c->p_ctrl_data);
    hi3c->p_ctrl_data++;
    hi3c->ctrl_count--;
  }

  /* Do while until FC (Frame Complete) is 1U or timeout */
  do
  {
    I3C_ControlDataTreatment(hi3c);
    hi3c->p_tx_func(hi3c);
    hi3c->p_rx_func(hi3c);

    /* Check for the timeout */
    if (timeout_ms != HAL_MAX_DELAY)
    {
      if (((HAL_GetTick() - tickstart) > timeout_ms) || (timeout_ms == 0U))
      {
        hal_status = HAL_TIMEOUT;
        break;
      }
    }

    if ((LL_I3C_IsActiveFlag_FC(p_i3cx) != 0U) && (hi3c->ctrl_count > 0UL))
    {
      LL_I3C_ClearFlag_FC(p_i3cx);
      /* Then Initiate a Start condition */
      LL_I3C_RequestTransfer(p_i3cx);
    }

    /* Calculate exit_condition value based on Frame complete and error flags */
    exit_condition = (LL_I3C_READ_REG(p_i3cx, EVR) & (I3C_EVR_FCF | I3C_EVR_ERRF));
  } while ((exit_condition == 0U) || ((exit_condition == I3C_EVR_FCF) && (hi3c->ctrl_count > 0UL)));

  if (LL_I3C_IsActiveFlag_FC(p_i3cx) != 0U)
  {
    LL_I3C_ClearFlag_FC(p_i3cx);
  }

  if (hal_status == HAL_OK)
  {
    if ((hi3c->tx_count != 0U) && (hi3c->rx_count != 0U))
    {
      hal_status = HAL_ERROR;
    }

    if (LL_I3C_IsActiveFlag_ERR(p_i3cx) != 0U)
    {
      LL_I3C_ClearFlag_ERR(p_i3cx);

#if defined(USE_HAL_I3C_GET_LAST_ERRORS) && (USE_HAL_I3C_GET_LAST_ERRORS == 1)
      I3C_GetErrorSources(hi3c);
#endif /* USE_HAL_I3C_GET_LAST_ERRORS */

      hal_status = HAL_ERROR;
    }
  }

  I3C_StateIdle(hi3c);

  /* Enable notification IT */
  LL_I3C_EnableIT(p_i3cx, its);

  return hal_status;
}

/**
  * @brief  Start transfer Direct CCC Command, I3C private or I2C transfer in interrupt mode.
  * @param  hi3c  Pointer to a hal_i3c_handle_t
  * @param  p_ctx  Pointer to a hal_i3c_xfer_ctx_t structure. It can be reused to start again the
                   same transfer. This transfer context is filled by @ref HAL_I3C_CTRL_BuildXferCtxPrivate() or
  *                @ref HAL_I3C_CTRL_BuildXferCtxCCC().
  * @note   This API can be used when the I3C is acting as controller.
  * @note   The function @ref HAL_I3C_CTRL_BuildXferCtxPrivate() must be called before initiate a private transfer or
  *         the function @ref HAL_I3C_CTRL_BuildXferCtxCCC() must be called before initiate a CCC transfer.
  * @note   The Tx FIFO threshold @ref HAL_I3C_TX_FIFO_THRESHOLD_4_4 is not allowed when the transfer descriptor
  *         contains multiple transmission frames.
  * @note   This function must be called to transfer read/write I3C or I2C private data or a direct read/write CCC.
  * @note   The tx_buf.size_byte must be equal to the sum of all tx_buf.size_byte exist in the descriptor.
  * @note   The rx_buf.size_byte must be equal to the sum of all rx_buf.size_byte exist in the descriptor.
  * @retval HAL_OK  Operation completed successfully
  * @retval HAL_BUSY  Concurrent process ongoing
  * @retval HAL_ERROR  Operation completed with error
  * @retval HAL_INVALID_PARAM  Invalid parameter
  */
hal_status_t HAL_I3C_CTRL_StartXfer_IT(hal_i3c_handle_t *hi3c, const hal_i3c_xfer_ctx_t *p_ctx)
{
  I3C_TypeDef *p_i3cx;
  hal_status_t hal_status = HAL_OK;

  ASSERT_DBG_PARAM((hi3c != NULL));
  ASSERT_DBG_PARAM((p_ctx != NULL));
  ASSERT_DBG_PARAM((p_ctx->rx_size_byte == 0U) || (p_ctx->p_rx_data != NULL));
  ASSERT_DBG_PARAM((p_ctx->tx_size_byte == 0U) || (p_ctx->p_tx_data != NULL));
  ASSERT_DBG_PARAM(p_ctx->p_ctrl_data != NULL);
  ASSERT_DBG_PARAM(p_ctx->ctrl_size_word != 0U);
  ASSERT_DBG_PARAM(hi3c->mode == HAL_I3C_MODE_CTRL);
  p_i3cx = I3C_GET_INSTANCE(hi3c);
  ASSERT_DBG_PARAM(!((LL_I3C_GetTxFIFOThreshold(p_i3cx) == LL_I3C_TXFIFO_THRESHOLD_4_4) && (p_ctx->nb_tx_frame > 1) \
                     && ((p_ctx->xfer_mode & I3C_OPERATION_TYPE_MASK) == LL_I3C_CONTROLLER_MTYPE_DIRECT)));
  ASSERT_DBG_STATE(hi3c->global_state, HAL_I3C_STATE_IDLE);

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  uint32_t is_invalid_param = 0U;

  if (p_ctx == NULL)
  {
    is_invalid_param = 1U;
  }
  else if ((p_ctx->p_rx_data == NULL) && (p_ctx->rx_size_byte != 0U))
  {
    is_invalid_param = 1U;
  }
  else if ((p_ctx->p_tx_data == NULL) && (p_ctx->tx_size_byte != 0U))
  {
    is_invalid_param = 1U;
  }
  else if (p_ctx->p_ctrl_data == NULL)
  {
    is_invalid_param = 1U;
  }
  else if ((p_ctx->p_ctrl_data == NULL) || (p_ctx->ctrl_size_word == 0U))
  {
    is_invalid_param = 1U;
  }
  else if ((LL_I3C_GetTxFIFOThreshold(p_i3cx) == LL_I3C_TXFIFO_THRESHOLD_4_4)
           && (p_ctx->nb_tx_frame > 1U)
           && (((uint32_t)p_ctx->xfer_mode & I3C_OPERATION_TYPE_MASK) == LL_I3C_CONTROLLER_MTYPE_DIRECT))
  {
    is_invalid_param = 1U;
  }
  else
  {
    /* nothing to do */
  }

  if (is_invalid_param == 1U)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  HAL_CHECK_UPDATE_STATE(hi3c, global_state, HAL_I3C_STATE_IDLE, HAL_I3C_STATE_TX_RX);

#if defined(USE_HAL_I3C_GET_LAST_ERRORS) && (USE_HAL_I3C_GET_LAST_ERRORS == 1)
  hi3c->last_error_codes = HAL_I3C_ERROR_NONE;
#endif /* USE_HAL_I3C_GET_LAST_ERRORS */

  if (hi3c->listen == HAL_I3C_LISTEN_DISABLED)
  {
    hi3c->xfer_isr = I3C_Ctrl_Multiple_Xfer_ISR;
  }
  else
  {
    hi3c->xfer_isr = I3C_Ctrl_Multiple_Xfer_Listen_Event_ISR;
  }

  /* Check on the deactivation of the arbitration */
  if (((uint32_t)p_ctx->xfer_mode & I3C_ARBITRATION_HEADER_MASK) == I3C_ARBITRATION_HEADER_MASK)
  {
    LL_I3C_DisableArbitrationHeader(p_i3cx);
  }
  else
  {
    LL_I3C_EnableArbitrationHeader(p_i3cx);
  }

  hi3c->p_ctrl_data = p_ctx->p_ctrl_data;
  hi3c->p_tx_data = p_ctx->p_tx_data;
  hi3c->p_rx_data = p_ctx->p_rx_data;
  hi3c->ctrl_count = p_ctx->ctrl_size_word;
  hi3c->tx_count = p_ctx->tx_size_byte;
  hi3c->rx_count = p_ctx->rx_size_byte;

  /* Check on the Tx threshold to know the Tx treatment process: byte or word */
  if (LL_I3C_GetTxFIFOThreshold(p_i3cx) == LL_I3C_TXFIFO_THRESHOLD_1_4)
  {
    hi3c->p_tx_func = &I3C_TransmitByteTreatment;
  }
  else
  {
    hi3c->p_tx_func = &I3C_TransmitWordTreatment;
  }

  /* Check on the Rx threshold to know the Rx treatment process: byte or word */
  if (LL_I3C_GetRxFIFOThreshold(p_i3cx) == LL_I3C_RXFIFO_THRESHOLD_1_4)
  {
    hi3c->p_rx_func = &I3C_ReceiveByteTreatment;
  }
  else
  {
    hi3c->p_rx_func = &I3C_ReceiveWordTreatment;
  }

  LL_I3C_EnableIT(p_i3cx, (I3C_CTRL_TX_IT | I3C_CTRL_RX_IT));

  /* Initiate a Start condition */
  LL_I3C_RequestTransfer(p_i3cx);

  return hal_status;
}

#if defined(USE_HAL_I3C_DMA) && (USE_HAL_I3C_DMA == 1)
/**
  * @brief  Start transfer Direct CCC Command, I3C private or I2C transfer in DMA mode.
  * @param  hi3c  Pointer to a hal_i3c_handle_t
  * @param  p_ctx  Pointer to a hal_i3c_xfer_ctx_t structure. It can be reused to start again the
                   same transfer. This transfer context is filled by @ref HAL_I3C_CTRL_BuildXferCtxPrivate() or
  *                @ref HAL_I3C_CTRL_BuildXferCtxCCC().
  * @note   This API can be used when the I3C is acting as controller.
  * @note   The function @ref HAL_I3C_CTRL_BuildXferCtxPrivate() must be called before initiate a private transfer or
  *         the function @ref HAL_I3C_CTRL_BuildXferCtxCCC() must be called before initiate a CCC transfer.
  * @note   The Tx FIFO threshold @ref HAL_I3C_TX_FIFO_THRESHOLD_4_4 is not allowed when the transfer descriptor
  *         contains multiple transmission frames.
  * @note   The tx_buf.size_byte must be equal to the sum of all tx_buf.size_byte exist in the descriptor.
  * @note   The rx_buf.size_byte must be equal to the sum of all rx_buf.size_byte exist in the descriptor.
  * @note   This function must be called to transfer read/write private data or a direct read/write CCC command.
  * @retval HAL_OK  Operation completed successfully
  * @retval HAL_BUSY  Concurrent process ongoing
  * @retval HAL_ERROR  Operation completed with error
  * @retval HAL_INVALID_PARAM  Invalid parameter
  */
hal_status_t HAL_I3C_CTRL_StartXfer_DMA(hal_i3c_handle_t *hi3c, const hal_i3c_xfer_ctx_t *p_ctx)
{
  I3C_TypeDef *p_i3cx;
  hal_status_t hal_status = HAL_OK;
  hal_status_t control_dma_status;
  hal_status_t tx_dma_status = HAL_OK;
  hal_status_t rx_dma_status = HAL_OK;
  uint32_t size_align_word;
#if defined(USE_ASSERT_DBG_PARAM)
  hal_dma_direct_xfer_config_t config_dma;
#endif /* USE_ASSERT_DBG_PARAM */

  ASSERT_DBG_PARAM((hi3c != NULL));
  ASSERT_DBG_PARAM((p_ctx != NULL));
  ASSERT_DBG_PARAM((p_ctx->rx_size_byte == 0U) || (p_ctx->p_rx_data != NULL));
  ASSERT_DBG_PARAM((p_ctx->rx_size_byte == 0U) || (hi3c->hdma_rx != NULL));
  ASSERT_DBG_PARAM((p_ctx->tx_size_byte == 0U) || (p_ctx->p_tx_data != NULL));
  ASSERT_DBG_PARAM((p_ctx->tx_size_byte == 0U) || (hi3c->hdma_tx != NULL));
  ASSERT_DBG_PARAM(p_ctx->p_ctrl_data != NULL);
  ASSERT_DBG_PARAM(p_ctx->ctrl_size_word != 0U);
  ASSERT_DBG_PARAM((hi3c->hdma_ctrl != NULL));
  ASSERT_DBG_PARAM(hi3c->mode == HAL_I3C_MODE_CTRL);
  p_i3cx = I3C_GET_INSTANCE(hi3c);
  ASSERT_DBG_PARAM(!((LL_I3C_GetTxFIFOThreshold(p_i3cx) == LL_I3C_TXFIFO_THRESHOLD_4_4) && (p_ctx->nb_tx_frame > 1) \
                     && ((p_ctx->xfer_mode & I3C_OPERATION_TYPE_MASK) == LL_I3C_CONTROLLER_MTYPE_DIRECT)));
  ASSERT_DBG_STATE(hi3c->global_state, HAL_I3C_STATE_IDLE);

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  uint32_t is_invalid_param = 0U;

  if (p_ctx == NULL)
  {
    is_invalid_param = 1U;
  }
  else if (((p_ctx->p_rx_data == NULL) || (hi3c->hdma_rx == NULL)) && (p_ctx->rx_size_byte != 0U))
  {
    is_invalid_param = 1U;
  }
  else if (((p_ctx->p_tx_data == NULL) || (hi3c->hdma_tx == NULL)) && (p_ctx->tx_size_byte != 0U))
  {
    is_invalid_param = 1U;
  }
  else if (p_ctx->p_ctrl_data == NULL)
  {
    is_invalid_param = 1U;
  }
  else if (hi3c->hdma_ctrl == NULL)
  {
    is_invalid_param = 1U;
  }
  else if ((p_ctx->p_ctrl_data == NULL) || (p_ctx->ctrl_size_word == 0U))
  {
    is_invalid_param = 1U;
  }
  else if ((LL_I3C_GetTxFIFOThreshold(p_i3cx) == LL_I3C_TXFIFO_THRESHOLD_4_4)
           && (p_ctx->nb_tx_frame > 1U)
           && (((uint32_t)p_ctx->xfer_mode & I3C_OPERATION_TYPE_MASK) == LL_I3C_CONTROLLER_MTYPE_DIRECT))
  {
    is_invalid_param = 1U;
  }
  else
  {
    /* nothing to do */
  }

  if (is_invalid_param == 1U)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  HAL_CHECK_UPDATE_STATE(hi3c, global_state, HAL_I3C_STATE_IDLE, HAL_I3C_STATE_TX_RX);

#if defined(USE_HAL_I3C_GET_LAST_ERRORS) && (USE_HAL_I3C_GET_LAST_ERRORS == 1)
  hi3c->last_error_codes = HAL_I3C_ERROR_NONE;
#endif /* USE_HAL_I3C_GET_LAST_ERRORS */
  hi3c->xfer_isr = I3C_Ctrl_Multiple_Xfer_DMA_ISR;

  /* Check on the deactivation of the arbitration */
  if (((uint32_t)p_ctx->xfer_mode & I3C_ARBITRATION_HEADER_MASK) == I3C_ARBITRATION_HEADER_MASK)
  {
    LL_I3C_DisableArbitrationHeader(p_i3cx);
  }
  else
  {
    LL_I3C_EnableArbitrationHeader(p_i3cx);
  }

  /*------------------------------------ I3C DMA channel for Control Data --------------------------------------------*/
  hi3c->hdma_ctrl->p_xfer_cplt_cb = I3C_DMAControlTransmitCplt;
  hi3c->hdma_ctrl->p_xfer_error_cb = I3C_DMAError;
  hi3c->hdma_ctrl->p_xfer_abort_cb = NULL;

#if defined(USE_ASSERT_DBG_PARAM)
  HAL_DMA_GetConfigDirectXfer(hi3c->hdma_ctrl, &config_dma);
#endif /* USE_ASSERT_DBG_PARAM */
  ASSERT_DBG_PARAM(IS_I3C_DMA_SOURCE_WORD(config_dma.src_data_width));
  ASSERT_DBG_PARAM(IS_I3C_DMA_DESTINATION_WORD(config_dma.dest_data_width));

  control_dma_status = HAL_DMA_StartDirectXfer_IT_Opt(hi3c->hdma_ctrl, (uint32_t)p_ctx->p_ctrl_data,
                                                      (uint32_t)&p_i3cx->CR, p_ctx->ctrl_size_word * 4U,
                                                      HAL_DMA_OPT_IT_NONE);

  /*------------------------------------ I3C DMA channel for the Rx Data ---------------------------------------------*/
  if (hi3c->hdma_rx != NULL)
  {
    hi3c->hdma_rx->p_xfer_abort_cb = NULL;
    if (p_ctx->rx_size_byte != 0U)
    {
      hi3c->hdma_rx->p_xfer_cplt_cb = I3C_DMADataReceiveCplt;
      hi3c->hdma_rx->p_xfer_error_cb = I3C_DMAError;

#if defined(USE_ASSERT_DBG_PARAM)
      HAL_DMA_GetConfigDirectXfer(hi3c->hdma_rx, &config_dma);
#endif /* USE_ASSERT_DBG_PARAM */

      /* Check on the Rx threshold to know the Rx treatment process: byte or word */
      if (LL_I3C_GetRxFIFOThreshold(p_i3cx) == LL_I3C_RXFIFO_THRESHOLD_1_4)
      {
        ASSERT_DBG_PARAM(IS_I3C_DMA_SOURCE_BYTE(config_dma.src_data_width));
        ASSERT_DBG_PARAM(IS_I3C_DMA_DESTINATION_BYTE(config_dma.dest_data_width));

        rx_dma_status = HAL_DMA_StartDirectXfer_IT_Opt(hi3c->hdma_rx, (uint32_t)&p_i3cx->RDR,
                                                       (uint32_t)p_ctx->p_rx_data, p_ctx->rx_size_byte,
                                                       HAL_DMA_OPT_IT_NONE);
      }
      else
      {
        ASSERT_DBG_PARAM(IS_I3C_DMA_SOURCE_WORD(config_dma.src_data_width));
        ASSERT_DBG_PARAM(IS_I3C_DMA_DESTINATION_WORD(config_dma.dest_data_width));

        /* Check to align data size in words */
        if ((p_ctx->rx_size_byte % 4U) == 0U)
        {
          size_align_word = p_ctx->rx_size_byte;
        }
        else
        {
          /* Modify size to be multiple of 4 */
          size_align_word = ((p_ctx->rx_size_byte + 4U) - (p_ctx->rx_size_byte % 4U));
        }
        rx_dma_status = HAL_DMA_StartDirectXfer_IT_Opt(hi3c->hdma_rx, (uint32_t)&p_i3cx->RDWR,
                                                       (uint32_t)p_ctx->p_rx_data, size_align_word,
                                                       HAL_DMA_OPT_IT_NONE);
      }
    }
  }

  /*------------------------------------ I3C DMA channel for the Tx Data ---------------------------------------------*/
  if (hi3c->hdma_tx != NULL)
  {
    hi3c->hdma_tx->p_xfer_abort_cb = NULL;
    if (p_ctx->tx_size_byte != 0U)
    {
      hi3c->hdma_tx->p_xfer_cplt_cb = I3C_DMADataTransmitCplt;
      hi3c->hdma_tx->p_xfer_error_cb = I3C_DMAError;

#if defined(USE_ASSERT_DBG_PARAM)
      HAL_DMA_GetConfigDirectXfer(hi3c->hdma_tx, &config_dma);
#endif /* USE_ASSERT_DBG_PARAM */

      /* Check on the Tx threshold to know the Tx treatment process: byte or word */
      if (LL_I3C_GetTxFIFOThreshold(p_i3cx) == LL_I3C_TXFIFO_THRESHOLD_1_4)
      {
        ASSERT_DBG_PARAM(IS_I3C_DMA_SOURCE_BYTE(config_dma.src_data_width));
        ASSERT_DBG_PARAM(IS_I3C_DMA_DESTINATION_BYTE(config_dma.dest_data_width));

        tx_dma_status = HAL_DMA_StartDirectXfer_IT_Opt(hi3c->hdma_tx, (uint32_t)p_ctx->p_tx_data,
                                                       (uint32_t)&p_i3cx->TDR, p_ctx->tx_size_byte,
                                                       HAL_DMA_OPT_IT_NONE);
      }
      else
      {
        ASSERT_DBG_PARAM(IS_I3C_DMA_SOURCE_WORD(config_dma.src_data_width));
        ASSERT_DBG_PARAM(IS_I3C_DMA_DESTINATION_WORD(config_dma.dest_data_width));

        /* Check to align data size in words */
        if ((p_ctx->tx_size_byte % 4U) == 0U)
        {
          size_align_word = p_ctx->tx_size_byte;
        }
        else
        {
          /* Modify size to be multiple of 4 */
          size_align_word = ((p_ctx->tx_size_byte + 4U) - (p_ctx->tx_size_byte % 4U));
        }

        tx_dma_status = HAL_DMA_StartDirectXfer_IT_Opt(hi3c->hdma_tx, (uint32_t)p_ctx->p_tx_data,
                                                       (uint32_t)&p_i3cx->TDWR, size_align_word, HAL_DMA_OPT_IT_NONE);
      }
    }
  }

  /* Check if DMA process is well started */
  uint32_t last_error_codes = hi3c->last_error_codes;
  if ((control_dma_status == HAL_OK) && (tx_dma_status == HAL_OK)
      && (rx_dma_status == HAL_OK) && (last_error_codes == HAL_I3C_ERROR_NONE))
  {
    LL_I3C_EnableIT(p_i3cx, I3C_XFER_DMA);
    LL_I3C_EnableDMAReq_Control(p_i3cx);

    if (p_ctx->rx_size_byte != 0U)
    {
      LL_I3C_EnableDMAReq_RX(p_i3cx);
    }

    if (p_ctx->tx_size_byte != 0U)
    {
      LL_I3C_EnableDMAReq_TX(p_i3cx);
    }

    /* Initiate a Start condition */
    LL_I3C_RequestTransfer(p_i3cx);
  }
  else
  {
    /* Set callback to NULL if DMA started */
    if (HAL_DMA_Abort(hi3c->hdma_ctrl) == HAL_OK)
    {
      hi3c->hdma_ctrl->p_xfer_cplt_cb = NULL;
      hi3c->hdma_ctrl->p_xfer_error_cb = NULL;
    }

    /* Set callback to NULL if DMA started */
    if (hi3c->hdma_tx != NULL)
    {
      if (HAL_DMA_Abort(hi3c->hdma_tx) == HAL_OK)
      {
        hi3c->hdma_tx->p_xfer_cplt_cb = NULL;
        hi3c->hdma_tx->p_xfer_error_cb = NULL;
      }
    }

    /* Set callback to NULL if DMA started */
    if (hi3c->hdma_rx != NULL)
    {
      if (HAL_DMA_Abort(hi3c->hdma_rx) == HAL_OK)
      {
        hi3c->hdma_rx->p_xfer_cplt_cb = NULL;
        hi3c->hdma_rx->p_xfer_error_cb = NULL;
      }
    }
#if defined(USE_HAL_I3C_GET_LAST_ERRORS) && (USE_HAL_I3C_GET_LAST_ERRORS == 1)
    hi3c->last_error_codes = HAL_I3C_ERROR_DMA;
#endif /* USE_HAL_I3C_GET_LAST_ERRORS */
    hal_status = HAL_ERROR;
    I3C_StateIdle(hi3c);
  }

  return hal_status;
}
#endif /* USE_HAL_I3C_DMA */
/**
  * @brief  Controller assign dynamic address (send a broadcast ENTDAA CCC command) in polling mode.
  * @param  hi3c  Pointer to a hal_i3c_handle_t
  * @param  p_target_payload  Pointer to the returned target payload value
  * @param  option  Parameter indicates the dynamic address assignment option
  * @param  timeout_ms  Timeout duration in milliseconds
  * @note   This API can be used when the I3C is acting as controller.
  * @retval HAL_OK  DAA process is ended without errors
  * @retval HAL_BUSY  A target has responded to the DAA process. Retry to get the other (if any)
  * @retval HAL_TIMEOUT  Operation exceeds user timeout
  * @retval HAL_ERROR  Operation completed with error
  * @retval HAL_INVALID_PARAM  Invalid parameter
  */
hal_status_t HAL_I3C_CTRL_DynAddrAssign(hal_i3c_handle_t *hi3c, uint64_t *p_target_payload,
                                        hal_i3c_dyn_addr_opt_t option, uint32_t timeout_ms)
{
  I3C_TypeDef *p_i3cx;
  hal_status_t hal_status = HAL_OK;

  ASSERT_DBG_PARAM((hi3c != NULL));
  ASSERT_DBG_PARAM((p_target_payload != NULL));
  ASSERT_DBG_PARAM(IS_I3C_ENTDAA_OPTION(option));
  ASSERT_DBG_PARAM(hi3c->mode == HAL_I3C_MODE_CTRL);
  ASSERT_DBG_STATE(hi3c->global_state, (uint32_t) HAL_I3C_STATE_IDLE | (uint32_t) HAL_I3C_STATE_DAA);

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (p_target_payload == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  p_i3cx = I3C_GET_INSTANCE(hi3c);

#if defined(USE_HAL_I3C_GET_LAST_ERRORS) && (USE_HAL_I3C_GET_LAST_ERRORS == 1)
  hi3c->last_error_codes = HAL_I3C_ERROR_NONE;
#endif /* USE_HAL_I3C_GET_LAST_ERRORS */

  /* Launch a RSTDAA procedure before launch ENTDAA */
  if ((hi3c->global_state == HAL_I3C_STATE_IDLE) && (option == HAL_I3C_DYN_ADDR_RSTDAA_THEN_ENTDAA))
  {
    hi3c->global_state = HAL_I3C_STATE_DAA;
    LL_I3C_EnableArbitrationHeader(p_i3cx);

    /* Write CCC information in the control register */
    LL_I3C_ControllerHandleCCC(p_i3cx, HAL_I3C_BROADCAST_RSTDAA, 0UL, LL_I3C_GENERATE_STOP);

    /* Wait Frame Complete flag */
    hal_status = I3C_WaitForFlagSet(hi3c, LL_I3C_EVR_FCF, timeout_ms);

    if (hal_status == HAL_OK)
    {
      LL_I3C_ClearFlag_FC(p_i3cx);
    }

    I3C_StateIdle(hi3c);
  }

  if (hal_status == HAL_OK)
  {
    if (hi3c->global_state != HAL_I3C_STATE_DAA)
    {
      hi3c->global_state = HAL_I3C_STATE_DAA;
      LL_I3C_EnableArbitrationHeader(p_i3cx);

      /* Write CCC information in the control register */
      LL_I3C_ControllerHandleCCC(p_i3cx, HAL_I3C_BROADCAST_ENTDAA, 0UL, LL_I3C_GENERATE_STOP);
    }

    hal_status = I3C_WaitForFlagSet(hi3c, (LL_I3C_EVR_FCF | I3C_EVR_TXFNFF), timeout_ms);

    /* Check TX FIFO not full flag */
    if (LL_I3C_IsActiveFlag_TXFNF(p_i3cx) != 0U)
    {
      /* Check on the Rx FIFO threshold to know the Rx treatment process: byte or word */
      if (LL_I3C_GetRxFIFOThreshold(p_i3cx) == LL_I3C_RXFIFO_THRESHOLD_1_4)
      {
        *p_target_payload = 0UL;

        /* For loop to get target payload */
        for (uint32_t index = 0UL; index < 8U; index++)
        {
          /* Retrieve payload byte by byte */
          *p_target_payload |= (uint64_t)((uint64_t)LL_I3C_ReceiveData8(p_i3cx) << (index * 8U));
        }
      }
      else
      {
        /* Retrieve first 32 bits payload */
        *p_target_payload = (uint64_t)LL_I3C_ReceiveData32(p_i3cx);

        /* Retrieve second 32 bits payload */
        *p_target_payload |= (uint64_t)((uint64_t)LL_I3C_ReceiveData32(p_i3cx) << 32U);
      }

      hal_status = HAL_BUSY;
    }
    else
    {
      if (LL_I3C_IsActiveFlag_FC(p_i3cx) != 0U)
      {
        LL_I3C_ClearFlag_FC(p_i3cx);
      }

      I3C_StateIdle(hi3c);
    }
  }

  return hal_status;
}

/**
  * @brief  Controller assign dynamic address (send a broadcast ENTDAA CCC command) in interrupt mode.
  * @param  hi3c  Pointer to a hal_i3c_handle_t
  * @param  option  Parameter indicates the dynamic address assignment option.
  * @note   This API can be used when the I3C is acting as controller.
  * @retval HAL_OK  Operation completed successfully
  * @retval HAL_BUSY  Concurrent process ongoing
  * @retval HAL_ERROR  Operation completed with error
  */
hal_status_t HAL_I3C_CTRL_DynAddrAssign_IT(hal_i3c_handle_t *hi3c, hal_i3c_dyn_addr_opt_t option)
{
  I3C_TypeDef *p_i3cx;
  hal_status_t hal_status = HAL_OK;

  ASSERT_DBG_PARAM((hi3c != NULL));
  ASSERT_DBG_PARAM(IS_I3C_ENTDAA_OPTION(option));
  ASSERT_DBG_PARAM(hi3c->mode == HAL_I3C_MODE_CTRL);
  ASSERT_DBG_STATE(hi3c->global_state, HAL_I3C_STATE_IDLE);

  p_i3cx = I3C_GET_INSTANCE(hi3c);

  HAL_CHECK_UPDATE_STATE(hi3c, global_state, HAL_I3C_STATE_IDLE, HAL_I3C_STATE_DAA);

#if defined(USE_HAL_I3C_GET_LAST_ERRORS) && (USE_HAL_I3C_GET_LAST_ERRORS == 1)
  hi3c->last_error_codes = HAL_I3C_ERROR_NONE;
#endif /* USE_HAL_I3C_GET_LAST_ERRORS */
  hi3c->xfer_isr = I3C_Ctrl_DAA_ISR;

  LL_I3C_EnableIT(p_i3cx, I3C_CTRL_DAA_IT);
  LL_I3C_EnableArbitrationHeader(p_i3cx);

  /* Launch a RSTDAA procedure before launch ENTDAA */
  if (option == HAL_I3C_DYN_ADDR_RSTDAA_THEN_ENTDAA)
  {
    /* Write RSTDAA CCC information in the control register */
    LL_I3C_ControllerHandleCCC(p_i3cx, HAL_I3C_BROADCAST_RSTDAA, 0UL, LL_I3C_GENERATE_RESTART);
  }
  else
  {
    /* Write ENTDAA CCC information in the control register */
    LL_I3C_ControllerHandleCCC(p_i3cx, HAL_I3C_BROADCAST_ENTDAA, 0UL, LL_I3C_GENERATE_STOP);
  }

  return hal_status;
}

/**
  * @brief  Controller Set dynamic address.
  * @param  hi3c  Pointer to a hal_i3c_handle_t
  * @param  target_address  Value of the dynamic address to be assigned
  * @note   This API can be used when the I3C is acting as controller.
  * @retval HAL_OK  Operation completed successfully
  * @retval HAL_ERROR  Operation completed with error
  */
hal_status_t HAL_I3C_CTRL_SetDynAddr(const hal_i3c_handle_t *hi3c, uint8_t target_address)
{
  I3C_TypeDef *p_i3cx;
  hal_status_t hal_status = HAL_OK;

  ASSERT_DBG_PARAM((hi3c != NULL));
  ASSERT_DBG_PARAM(hi3c->mode == HAL_I3C_MODE_CTRL);
  ASSERT_DBG_STATE(hi3c->global_state, (uint32_t) HAL_I3C_STATE_IDLE | (uint32_t) HAL_I3C_STATE_DAA);

  p_i3cx = I3C_GET_INSTANCE(hi3c);

  /* Check if Tx FIFO requests data */
  if (LL_I3C_IsActiveFlag_TXFNF(p_i3cx) != 0U)
  {
    /* Write device address in the TDR register */
    LL_I3C_TransmitData8(p_i3cx, target_address);
  }
  else
  {
    hal_status = HAL_ERROR;
  }

  return hal_status;
}

/**
  * @brief  Check if I3C target device is ready for communication.
  * @param  hi3c  Pointer to a hal_i3c_handle_t
  * @param  target_address  Value of the device dynamic address
  * @param  trials  Number of trials
  * @param  timeout_ms  Timeout duration
  * @note   This API can be used when the I3C is acting as controller.
  * @retval HAL_OK  Operation completed successfully
  * @retval HAL_TIMEOUT  Operation exceeds user timeout
  * @retval HAL_ERROR  Operation completed with error
  */
hal_status_t HAL_I3C_CTRL_IsDeviceI3C_Ready(hal_i3c_handle_t *hi3c, uint8_t target_address, uint32_t trials,
                                            uint32_t timeout_ms)
{
  hal_status_t hal_status = HAL_OK;
  i3c_device_t device;

  ASSERT_DBG_PARAM((hi3c != NULL));
  ASSERT_DBG_PARAM(hi3c->mode == HAL_I3C_MODE_CTRL);
  ASSERT_DBG_STATE(hi3c->global_state, HAL_I3C_STATE_IDLE);

  device.address = target_address;
  device.message_type = LL_I3C_CONTROLLER_MTYPE_PRIVATE;
  hal_status = I3C_Ctrl_IsDevice_Ready(hi3c, &device, trials, timeout_ms);

  return hal_status;
}

/**
  * @brief  Check if I2C target device is ready for communication.
  * @param  hi3c  Pointer to a hal_i3c_handle_t
  * @param  target_address  Value of the device dynamic address
  * @param  trials  Number of trials
  * @param  timeout_ms  Timeout duration.
  * @note   This API can be used when the I3C is acting as controller.
  * @retval HAL_OK  Operation completed successfully
  * @retval HAL_TIMEOUT  Operation exceeds user timeout
  * @retval HAL_ERROR  Operation completed with error
  */
hal_status_t HAL_I3C_CTRL_IsDeviceI2C_Ready(hal_i3c_handle_t *hi3c, uint8_t target_address, uint32_t trials,
                                            uint32_t timeout_ms)
{
  hal_status_t hal_status = HAL_OK;
  i3c_device_t device;

  ASSERT_DBG_PARAM((hi3c != NULL));
  ASSERT_DBG_PARAM(hi3c->mode == HAL_I3C_MODE_CTRL);
  ASSERT_DBG_STATE(hi3c->global_state, HAL_I3C_STATE_IDLE);

  /* Initiate a device address */
  device.address = target_address;

  /* Initiate a message type */
  device.message_type = LL_I3C_CONTROLLER_MTYPE_LEGACY_I2C;

  /* Check if the device is ready*/
  hal_status = I3C_Ctrl_IsDevice_Ready(hi3c, &device, trials, timeout_ms);

  return hal_status;
}

/**
  * @brief  Controller generates patterns (target reset pattern or HDR exit pattern) with arbitration in polling mode.
  * @param  hi3c  Pointer to a hal_i3c_handle_t
  * @param  pattern  The generated pattern.
  * @param  timeout_ms  Timeout duration in ms.
  * @retval HAL_OK  Operation completed successfully
  * @retval HAL_TIMEOUT  Operation exceeds user timeout
  * @retval HAL_BUSY  Concurrent process ongoing
  * @retval HAL_ERROR  Operation completed with error
  */
hal_status_t HAL_I3C_CTRL_GeneratePatterns(hal_i3c_handle_t *hi3c, hal_i3c_pattern_opt_t pattern, uint32_t timeout_ms)
{
  I3C_TypeDef *p_i3cx;
  hal_status_t status = HAL_OK;
  __IO uint32_t exit_condition;
  uint32_t tickstart;

  ASSERT_DBG_PARAM((hi3c != NULL));
  ASSERT_DBG_PARAM(IS_I3C_PATTERN(pattern));
  ASSERT_DBG_PARAM(hi3c->mode == HAL_I3C_MODE_CTRL);
  ASSERT_DBG_STATE(hi3c->global_state, HAL_I3C_STATE_IDLE);

  p_i3cx = I3C_GET_INSTANCE(hi3c);

  HAL_CHECK_UPDATE_STATE(hi3c, global_state, HAL_I3C_STATE_IDLE, HAL_I3C_STATE_TX);

#if defined(USE_HAL_I3C_GET_LAST_ERRORS) && (USE_HAL_I3C_GET_LAST_ERRORS == 1)
  hi3c->last_error_codes = HAL_I3C_ERROR_NONE;
#endif /* USE_HAL_I3C_GET_LAST_ERRORS */

  /* The target reset pattern is sent after the issued message header */
  if (pattern == HAL_I3C_PATTERN_TGT_RESET)
  {
    LL_I3C_EnableResetPattern(p_i3cx);
    LL_I3C_DisableExitPattern(p_i3cx);
  }
  /* The HDR exit pattern is sent after the issued message header */
  else
  {
    LL_I3C_DisableResetPattern(p_i3cx);
    LL_I3C_EnableExitPattern(p_i3cx);
  }

  /* Write message control register */
  LL_I3C_WRITE_REG(p_i3cx, CR, LL_I3C_CONTROLLER_MTYPE_HEADER | LL_I3C_GENERATE_STOP);

  /* Calculate exit_condition value based on Frame complete and error flags */
  exit_condition = (LL_I3C_READ_REG(p_i3cx, EVR) & (I3C_EVR_FCF | I3C_EVR_ERRF));

  tickstart = HAL_GetTick();

  while (exit_condition == 0U)
  {
    if (timeout_ms != HAL_MAX_DELAY)
    {
      if (((HAL_GetTick() - tickstart) > timeout_ms) || (timeout_ms == 0U))
      {
        status = HAL_TIMEOUT;
        break;
      }
    }
    /* Calculate exit_condition value based on Frame complete and error flags */
    exit_condition = (LL_I3C_READ_REG(p_i3cx, EVR) & (I3C_EVR_FCF | I3C_EVR_ERRF));
  }

  if (status == HAL_OK)
  {
    if (LL_I3C_IsActiveFlag_FC(p_i3cx) != 0U)
    {
      LL_I3C_ClearFlag_FC(p_i3cx);
    }
    else
    {
      LL_I3C_ClearFlag_ERR(p_i3cx);
#if defined(USE_HAL_I3C_GET_LAST_ERRORS) && (USE_HAL_I3C_GET_LAST_ERRORS == 1)
      I3C_GetErrorSources(hi3c);
#endif /* USE_HAL_I3C_GET_LAST_ERRORS */
      status = HAL_ERROR;
    }
  }

  I3C_StateIdle(hi3c);

  return status;
}

/**
  * @brief  Controller generates arbitration (message header {S/Sr + 0x7E addr + W}) in polling mode.
  * @param  hi3c  Pointer to a hal_i3c_handle_t
  * @param  timeout_ms  Timeout duration
  * @note   This API can be used when the I3C is acting as controller.
  * @retval HAL_OK  Operation completed successfully
  * @retval HAL_BUSY  Concurrent process ongoing
  * @retval HAL_TIMEOUT  Operation exceeds user timeout
  * @retval HAL_ERROR  Operation completed with error
  */
hal_status_t HAL_I3C_CTRL_GenerateArbitration(hal_i3c_handle_t *hi3c, uint32_t timeout_ms)
{
  I3C_TypeDef *p_i3cx;
  hal_status_t hal_status = HAL_OK;
  volatile uint32_t exit_condition;
  uint32_t tickstart;

  ASSERT_DBG_PARAM((hi3c != NULL));
  ASSERT_DBG_PARAM(hi3c->mode == HAL_I3C_MODE_CTRL);
  ASSERT_DBG_STATE(hi3c->global_state, HAL_I3C_STATE_IDLE);

  p_i3cx = I3C_GET_INSTANCE(hi3c);

  HAL_CHECK_UPDATE_STATE(hi3c, global_state, HAL_I3C_STATE_IDLE, HAL_I3C_STATE_TX);

#if defined(USE_HAL_I3C_GET_LAST_ERRORS) && (USE_HAL_I3C_GET_LAST_ERRORS == 1)
  hi3c->last_error_codes = HAL_I3C_ERROR_NONE;
#endif /* USE_HAL_I3C_GET_LAST_ERRORS */

  LL_I3C_DisableExitPattern(p_i3cx);
  LL_I3C_DisableResetPattern(p_i3cx);

  /* Write message control register */
  LL_I3C_WRITE_REG(p_i3cx, CR, LL_I3C_CONTROLLER_MTYPE_HEADER | LL_I3C_GENERATE_STOP);

  /* Calculate exit_condition value based on Frame complete and error flags */
  exit_condition = (LL_I3C_READ_REG(p_i3cx, EVR) & (I3C_EVR_FCF | I3C_EVR_ERRF));

  tickstart = HAL_GetTick();

  while (exit_condition == 0U)
  {
    if (timeout_ms != HAL_MAX_DELAY)
    {
      if (((HAL_GetTick() - tickstart) > timeout_ms) || (timeout_ms == 0U))
      {
        hal_status = HAL_TIMEOUT;
        break;
      }
    }
    /* Calculate exit_condition value based on Frame complete and error flags */
    exit_condition = (LL_I3C_READ_REG(p_i3cx, EVR) & (I3C_EVR_FCF | I3C_EVR_ERRF));
  }

  if (hal_status == HAL_OK)
  {
    if (LL_I3C_IsActiveFlag_FC(p_i3cx) != 0U)
    {
      LL_I3C_ClearFlag_FC(p_i3cx);
    }
    else
    {
      LL_I3C_ClearFlag_ERR(p_i3cx);
#if defined(USE_HAL_I3C_GET_LAST_ERRORS) && (USE_HAL_I3C_GET_LAST_ERRORS == 1)
      I3C_GetErrorSources(hi3c);
#endif /* USE_HAL_I3C_GET_LAST_ERRORS */
      hal_status = HAL_ERROR;
    }
  }

  I3C_StateIdle(hi3c);

  return hal_status;
}

/**
  * @brief  Recover the stuck SCL in case of CE1 error. It Forces the stop of the SCL clock.
  * @param  hi3c  Pointer to a hal_i3c_handle_t
  * @note   This API can be used when the I3C is acting as controller.
  * @note   A minimum delay of 150 microseconds is required before emitting another message.
  *         This delay is approximately managed within this function.
  * @retval HAL_OK  Operation completed successfully
  */
hal_status_t HAL_I3C_CTRL_RecoverSCLToIDLE(const hal_i3c_handle_t *hi3c)
{
  I3C_TypeDef *p_i3cx;
  hal_status_t hal_status = HAL_OK;

  ASSERT_DBG_PARAM((hi3c != NULL));
  ASSERT_DBG_PARAM(hi3c->mode == HAL_I3C_MODE_CTRL);
  ASSERT_DBG_STATE(hi3c->global_state, HAL_I3C_STATE_IDLE);

  p_i3cx = I3C_GET_INSTANCE(hi3c);

  /* Write message control register */
  LL_I3C_WRITE_REG(p_i3cx, CR, (uint32_t)(LL_I3C_CONTROLLER_MTYPE_RELEASE | LL_I3C_GENERATE_STOP));

  /* Wait at least 150 micro seconds */
  I3C_DELAY_US(200U);

  return hal_status;
}
/**
  * @}
  */

/** @addtogroup I3C_Exported_Functions_Group7 Target operational functions
  * @{
A set of functions allowing to manage target I3C operation:
  - HAL_I3C_TGT_Transmit() to transmit private data in polling mode.
  - HAL_I3C_TGT_Transmit_IT() to transmit private data in interrupt mode.
  - HAL_I3C_TGT_Transmit_DMA() to transmit private data in DMA mode.
  - HAL_I3C_TGT_Receive() to receive private data in polling mode.
  - HAL_I3C_TGT_Receive_IT() to receive private data in interrupt mode.
  - HAL_I3C_TGT_Receive_DMA() to receive private data in DMA mode.
  - HAL_I3C_TGT_ControlRoleReq() to send a control-role request in polling mode.
  - HAL_I3C_TGT_ControlRoleReq_IT() to send a control-role request in interrupt mode.
  - HAL_I3C_TGT_HotJoinReq() to send a Hot-Join request in polling mode.
  - HAL_I3C_TGT_HotJoinReq_IT() to send a Hot-Join request in interrupt mode.
  - HAL_I3C_TGT_IBIReq() to send an IBI request in polling mode.
  - HAL_I3C_TGT_IBIReq_IT() to send an IBI request in interrupt mode.
  */

/**
  * @brief  Target transmit private data in polling mode.
  * @param  hi3c  Pointer to a hal_i3c_handle_t
  * @param  p_data  Pointer to the data
  * @param  size_byte  Size of the data in bytes
  * @param  timeout_ms  Timeout duration in milliseconds
  * @note   This API can be used when the I3C is acting as target.
  * @note   Target FIFO preload data is forced within this API for timing purpose.
  * @retval HAL_OK  Operation completed successfully
  * @retval HAL_BUSY  Concurrent process ongoing
  * @retval HAL_TIMEOUT  Operation exceeds user timeout
  * @retval HAL_ERROR  Operation completed with error
  * @retval HAL_INVALID_PARAM  Invalid parameter
  */
hal_status_t HAL_I3C_TGT_Transmit(hal_i3c_handle_t *hi3c, const uint8_t *p_data, uint32_t size_byte,
                                  uint32_t timeout_ms)
{
  I3C_TypeDef *p_i3cx;
  hal_status_t hal_status = HAL_OK;
  uint32_t tickstart;

  ASSERT_DBG_PARAM((hi3c != NULL));
  ASSERT_DBG_PARAM((p_data != NULL));
  ASSERT_DBG_PARAM((size_byte != 0U));
  ASSERT_DBG_PARAM(hi3c->mode == HAL_I3C_MODE_TGT);
  ASSERT_DBG_STATE(hi3c->global_state, HAL_I3C_STATE_IDLE);

  p_i3cx = I3C_GET_INSTANCE(hi3c);

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if ((p_data == NULL) || (size_byte == 0U))
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  if (LL_I3C_IsEnabledOwnDynAddress(p_i3cx) == 0U)
  {
    return HAL_ERROR;
  }

  HAL_CHECK_UPDATE_STATE(hi3c, global_state, HAL_I3C_STATE_IDLE, HAL_I3C_STATE_TX);

  /* Disable notification IT */
  uint32_t its = LL_I3C_READ_REG(p_i3cx, IER);
  LL_I3C_DisableIT(p_i3cx, its);

#if defined(USE_HAL_I3C_GET_LAST_ERRORS) && (USE_HAL_I3C_GET_LAST_ERRORS == 1)
  hi3c->last_error_codes = HAL_I3C_ERROR_NONE;
#endif /* USE_HAL_I3C_GET_LAST_ERRORS */
  hi3c->p_tx_data = p_data;
  hi3c->tx_count = size_byte;

  /* Check on the Tx threshold to know the Tx treatment process: byte or word */
  if (LL_I3C_GetTxFIFOThreshold(p_i3cx) == LL_I3C_TXFIFO_THRESHOLD_1_4)
  {
    hi3c->p_tx_func = &I3C_TransmitByteTreatment;
  }
  else
  {
    hi3c->p_tx_func = &I3C_TransmitWordTreatment;
  }

  /* Set Preload information */
  LL_I3C_ConfigTxPreload(p_i3cx, (uint16_t)hi3c->tx_count);

  /* Init tickstart for timeout management */
  tickstart = HAL_GetTick();

  /* Do while until FC (Frame Complete) is 1U or timeout */
  do
  {
    hi3c->p_tx_func(hi3c);

    /* Check for the timeout_ms */
    if (timeout_ms != HAL_MAX_DELAY)
    {
      if (((HAL_GetTick() - tickstart) > timeout_ms) || (timeout_ms == 0U))
      {
        hal_status = HAL_TIMEOUT;

        break;
      }
    }
    /* Exit loop on Frame complete or error flags */
  } while ((LL_I3C_READ_REG(p_i3cx, EVR) & (LL_I3C_EVR_FCF | I3C_EVR_ERRF)) == 0U);

  if (LL_I3C_IsActiveFlag_FC(p_i3cx) != 0U)
  {
    LL_I3C_ClearFlag_FC(p_i3cx);
  }

  /* Check if all data bytes are transmitted */
  if ((LL_I3C_GetXferDataCount(p_i3cx) != size_byte) && (hal_status == HAL_OK))
  {
    hal_status = HAL_ERROR;
  }

  if (LL_I3C_IsActiveFlag_ERR(p_i3cx) != 0U)
  {
    LL_I3C_ClearFlag_ERR(p_i3cx);

#if defined(USE_HAL_I3C_GET_LAST_ERRORS) && (USE_HAL_I3C_GET_LAST_ERRORS == 1)
    I3C_GetErrorSources(hi3c);
#endif /* USE_HAL_I3C_GET_LAST_ERRORS */

    hal_status = HAL_ERROR;
  }

  I3C_StateIdle(hi3c);

  /* Enable notification IT */
  LL_I3C_EnableIT(p_i3cx, its);

  return hal_status;
}

/**
  * @brief  Target transmit private data in interrupt mode.
  * @param  hi3c  Pointer to a hal_i3c_handle_t
  * @param  p_data  Pointer to the data
  * @param  size_byte  Size of the data in bytes
  * @note   This API can be used when the I3C is acting as target.
  * @retval HAL_OK  Operation completed successfully
  * @retval HAL_BUSY  Concurrent process ongoing
  * @retval HAL_ERROR  Operation completed with error
  * @retval HAL_INVALID_PARAM  Invalid parameter
  */
hal_status_t HAL_I3C_TGT_Transmit_IT(hal_i3c_handle_t *hi3c, const uint8_t *p_data, uint32_t size_byte)
{
  I3C_TypeDef *p_i3cx;
  hal_status_t hal_status = HAL_OK;
  uint32_t it_source;

  ASSERT_DBG_PARAM((hi3c != NULL));
  ASSERT_DBG_PARAM((p_data != NULL));
  ASSERT_DBG_PARAM((size_byte != 0U));
  ASSERT_DBG_PARAM(hi3c->mode == HAL_I3C_MODE_TGT);
  ASSERT_DBG_STATE(hi3c->global_state, HAL_I3C_STATE_IDLE);

  p_i3cx = I3C_GET_INSTANCE(hi3c);

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if ((p_data == NULL) || (size_byte == 0U))
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  /* Read IER register */
  it_source = LL_I3C_READ_REG(p_i3cx, IER);

  /* Check if DEF or GRP CCC notifications are enabled */
  if ((I3C_CHECK_IT_SOURCE(it_source, (LL_I3C_IER_DEFIE | LL_I3C_IER_RXFNEIE)) != 0U)
      || (I3C_CHECK_IT_SOURCE(it_source, (LL_I3C_IER_GRPIE | LL_I3C_IER_RXFNEIE)) != 0U))
  {
    return HAL_ERROR;
  }

  /* Verify the dynamic address validity */
  if (LL_I3C_IsEnabledOwnDynAddress(p_i3cx) == 0U)
  {
    return HAL_ERROR;
  }

  HAL_CHECK_UPDATE_STATE(hi3c, global_state, HAL_I3C_STATE_IDLE, HAL_I3C_STATE_TX);

#if defined(USE_HAL_I3C_GET_LAST_ERRORS) && (USE_HAL_I3C_GET_LAST_ERRORS == 1)
  hi3c->last_error_codes = HAL_I3C_ERROR_NONE;
#endif /* USE_HAL_I3C_GET_LAST_ERRORS */
  hi3c->p_tx_data = p_data;
  hi3c->data_size = size_byte;
  hi3c->tx_count = size_byte;
  hi3c->xfer_isr = I3C_Tgt_Tx_ISR;

  /* Check on the Tx threshold to know the Tx treatment process: byte or word */
  if (LL_I3C_GetTxFIFOThreshold(p_i3cx) == LL_I3C_TXFIFO_THRESHOLD_1_4)
  {
    hi3c->p_tx_func = &I3C_TransmitByteTreatment;
  }
  else
  {
    hi3c->p_tx_func = &I3C_TransmitWordTreatment;
  }

  LL_I3C_ConfigTxPreload(p_i3cx, (uint16_t)hi3c->tx_count);
  LL_I3C_EnableIT(p_i3cx, I3C_TGT_TX_IT);

  return hal_status;
}

#if defined(USE_HAL_I3C_DMA) && (USE_HAL_I3C_DMA == 1)
/**
  * @brief  Target transmit private data in DMA mode.
  * @param  hi3c  Pointer to a hal_i3c_handle_t
  * @param  p_data  Pointer to the data
  * @param  size_byte  Size of the data in bytes
  * @note   This API can be used when the I3C is acting as target.
  * @retval HAL_OK  Operation completed successfully
  * @retval HAL_BUSY  Concurrent process ongoing
  * @retval HAL_ERROR  Operation completed with error
  * @retval HAL_INVALID_PARAM  Invalid parameter
  */
hal_status_t HAL_I3C_TGT_Transmit_DMA(hal_i3c_handle_t *hi3c, const uint8_t *p_data, uint32_t size_byte)
{
  I3C_TypeDef *p_i3cx;
  hal_status_t hal_status = HAL_OK;
  uint32_t it_source;
  hal_status_t tx_dma_status;
  uint32_t size_align_word;
#if defined(USE_ASSERT_DBG_PARAM)
  hal_dma_direct_xfer_config_t config_dma;
#endif /* USE_ASSERT_DBG_PARAM */

  ASSERT_DBG_PARAM((hi3c != NULL));
  ASSERT_DBG_PARAM((p_data != NULL));
  ASSERT_DBG_PARAM((size_byte != 0U));
  ASSERT_DBG_PARAM(hi3c->mode == HAL_I3C_MODE_TGT);
  ASSERT_DBG_STATE(hi3c->global_state, HAL_I3C_STATE_IDLE);

  p_i3cx = I3C_GET_INSTANCE(hi3c);

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if ((p_data == NULL) || (size_byte == 0U))
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  /* Read IER register */
  it_source = LL_I3C_READ_REG(p_i3cx, IER);

  /* Check if DEF or GRP CCC notifications are enabled */
  if ((I3C_CHECK_IT_SOURCE(it_source, (LL_I3C_IER_DEFIE | LL_I3C_IER_RXFNEIE)) != 0U)
      || (I3C_CHECK_IT_SOURCE(it_source, (LL_I3C_IER_GRPIE | LL_I3C_IER_RXFNEIE)) != 0U))
  {
    return HAL_ERROR;
  }

  /* Verify the dynamic address validity */
  if (LL_I3C_IsEnabledOwnDynAddress(p_i3cx) == 0U)
  {
    return HAL_ERROR;
  }

  HAL_CHECK_UPDATE_STATE(hi3c, global_state, HAL_I3C_STATE_IDLE, HAL_I3C_STATE_TX);

#if defined(USE_HAL_I3C_GET_LAST_ERRORS) && (USE_HAL_I3C_GET_LAST_ERRORS == 1)
  hi3c->last_error_codes = HAL_I3C_ERROR_NONE;
#endif /* USE_HAL_I3C_GET_LAST_ERRORS */
  hi3c->p_tx_data = p_data;
  hi3c->tx_count = size_byte;
  hi3c->xfer_isr = I3C_Tgt_Tx_DMA_ISR;

  /* Set Preload information */
  LL_I3C_ConfigTxPreload(p_i3cx, (uint16_t)hi3c->tx_count);

  /*------------------------------------ I3C DMA channel for the tx data ---------------------------------------------*/
  hi3c->hdma_tx->p_xfer_cplt_cb = I3C_DMADataTransmitCplt;
  hi3c->hdma_tx->p_xfer_error_cb = I3C_DMAError;
  hi3c->hdma_tx->p_xfer_abort_cb = NULL;
  hi3c->hdma_rx->p_xfer_abort_cb = NULL;

#if defined(USE_ASSERT_DBG_PARAM)
  HAL_DMA_GetConfigDirectXfer(hi3c->hdma_tx, &config_dma);
#endif /* USE_ASSERT_DBG_PARAM */

  /* Check on the Tx threshold to know the Tx treatment process: byte or word */
  if (LL_I3C_GetTxFIFOThreshold(p_i3cx) == LL_I3C_TXFIFO_THRESHOLD_1_4)
  {
    ASSERT_DBG_PARAM(IS_I3C_DMA_SOURCE_BYTE(config_dma.src_data_width));
    ASSERT_DBG_PARAM(IS_I3C_DMA_DESTINATION_BYTE(config_dma.dest_data_width));

    tx_dma_status = HAL_DMA_StartDirectXfer_IT(hi3c->hdma_tx, (uint32_t)hi3c->p_tx_data, (uint32_t)&p_i3cx->TDR,
                                               hi3c->tx_count);
  }
  else
  {
    ASSERT_DBG_PARAM(IS_I3C_DMA_SOURCE_WORD(config_dma.src_data_width));
    ASSERT_DBG_PARAM(IS_I3C_DMA_DESTINATION_WORD(config_dma.dest_data_width));

    /* Check to align data size in words */
    if ((hi3c->tx_count % 4U) == 0U)
    {
      size_align_word = hi3c->tx_count;
    }
    else
    {
      /* Modify size to be multiple of 4 */
      size_align_word = ((hi3c->tx_count + 4U) - (hi3c->tx_count % 4U));
    }

    tx_dma_status = HAL_DMA_StartDirectXfer_IT(hi3c->hdma_tx, (uint32_t)hi3c->p_tx_data, (uint32_t)&p_i3cx->TDWR,
                                               size_align_word);
  }

  if (tx_dma_status == HAL_OK)
  {
    LL_I3C_EnableIT(p_i3cx, I3C_XFER_DMA);
    hi3c->tx_count = 0UL;
    LL_I3C_EnableDMAReq_TX(p_i3cx);
  }
  else
  {
    hi3c->hdma_tx->p_xfer_cplt_cb = NULL;
    hi3c->hdma_tx->p_xfer_error_cb = NULL;

#if defined(USE_HAL_I3C_GET_LAST_ERRORS) && (USE_HAL_I3C_GET_LAST_ERRORS == 1)
    hi3c->last_error_codes = HAL_I3C_ERROR_DMA;
#endif /* USE_HAL_I3C_GET_LAST_ERRORS */
    hal_status = HAL_ERROR;
    I3C_StateIdle(hi3c);
  }

  return hal_status;
}
#endif /* USE_HAL_I3C_DMA */

/**
  * @brief  Target receive private data in polling mode.
  * @param  hi3c  Pointer to a hal_i3c_handle_t
  * @param  p_data  Pointer to the data
  * @param  size_byte  Size of the data in bytes
  * @param  timeout_ms    Timeout duration in milliseconds
  * @note   This API can be used when the I3C is acting as target.
  * @retval HAL_OK  Operation completed successfully
  * @retval HAL_BUSY  Concurrent process ongoing
  * @retval HAL_TIMEOUT  Operation exceeds user timeout
  * @retval HAL_ERROR  Operation completed with error
  * @retval HAL_INVALID_PARAM  Invalid parameter
  */
hal_status_t HAL_I3C_TGT_Receive(hal_i3c_handle_t *hi3c, uint8_t *p_data, uint32_t size_byte, uint32_t timeout_ms)
{
  I3C_TypeDef *p_i3cx;
  hal_status_t hal_status = HAL_OK;
  uint32_t it_source;
  uint32_t tickstart;

  ASSERT_DBG_PARAM((hi3c != NULL));
  ASSERT_DBG_PARAM((p_data != NULL));
  ASSERT_DBG_PARAM((size_byte != 0U));
  ASSERT_DBG_PARAM(hi3c->mode == HAL_I3C_MODE_TGT);
  ASSERT_DBG_STATE(hi3c->global_state, HAL_I3C_STATE_IDLE);

  p_i3cx = I3C_GET_INSTANCE(hi3c);

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if ((p_data == NULL) || (size_byte == 0U))
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  /* Read IER register */
  it_source = LL_I3C_READ_REG(p_i3cx, IER);

  /* Check if DEF or GRP CCC notifications are enabled */
  if ((I3C_CHECK_IT_SOURCE(it_source, (LL_I3C_IER_DEFIE | LL_I3C_IER_RXFNEIE)) != 0U)
      || (I3C_CHECK_IT_SOURCE(it_source, (LL_I3C_IER_GRPIE | LL_I3C_IER_RXFNEIE)) != 0U))
  {
    return HAL_ERROR;
  }

  /* Verify the dynamic address validity */
  if (LL_I3C_IsEnabledOwnDynAddress(p_i3cx) == 0U)
  {
    return HAL_ERROR;
  }

  HAL_CHECK_UPDATE_STATE(hi3c, global_state, HAL_I3C_STATE_IDLE, HAL_I3C_STATE_RX);

  /* Disable notification IT */
  uint32_t its = LL_I3C_READ_REG(p_i3cx, IER);
  LL_I3C_DisableIT(p_i3cx, its);

#if defined(USE_HAL_I3C_GET_LAST_ERRORS) && (USE_HAL_I3C_GET_LAST_ERRORS == 1)
  hi3c->last_error_codes = HAL_I3C_ERROR_NONE;
#endif /* USE_HAL_I3C_GET_LAST_ERRORS */
  hi3c->p_rx_data = p_data;
  hi3c->rx_count = size_byte;

  /* Check on the Rx threshold to know the Rx treatment process: byte or word */
  if (LL_I3C_GetRxFIFOThreshold(p_i3cx) == LL_I3C_RXFIFO_THRESHOLD_1_4)
  {
    hi3c->p_rx_func = &I3C_ReceiveByteTreatment;
  }
  else
  {
    hi3c->p_rx_func = &I3C_ReceiveWordTreatment;
  }

  /* Init tickstart for timeout management */
  tickstart = HAL_GetTick();

  /* Do while until FC (Frame Complete) is 1U or timeout */
  do
  {
    if (hi3c->rx_count > 0UL)
    {
      hi3c->p_rx_func(hi3c);
    }

    /* Check for the timeout_ms */
    if (timeout_ms != HAL_MAX_DELAY)
    {
      if (((HAL_GetTick() - tickstart) > timeout_ms) || (timeout_ms == 0U))
      {
        hal_status = HAL_TIMEOUT;
        break;
      }
    }
    /* Exit loop on Frame complete or error flags */
  } while ((LL_I3C_READ_REG(p_i3cx, EVR) & (I3C_EVR_FCF | I3C_EVR_ERRF)) == 0U);

  if (LL_I3C_IsActiveFlag_FC(p_i3cx) != 0U)
  {
    LL_I3C_ClearFlag_FC(p_i3cx);
  }

  /* Check if all data bytes are received */
  if ((LL_I3C_GetXferDataCount(p_i3cx) != size_byte) && (hal_status == HAL_OK))
  {
    hal_status = HAL_ERROR;
  }

  if (LL_I3C_IsActiveFlag_ERR(p_i3cx) != 0U)
  {
    LL_I3C_ClearFlag_ERR(p_i3cx);

#if defined(USE_HAL_I3C_GET_LAST_ERRORS) && (USE_HAL_I3C_GET_LAST_ERRORS == 1)
    I3C_GetErrorSources(hi3c);
#endif /* USE_HAL_I3C_GET_LAST_ERRORS */

    hal_status = HAL_ERROR;
  }

  I3C_StateIdle(hi3c);

  /* Enable notification IT */
  LL_I3C_EnableIT(p_i3cx, its);

  return hal_status;
}

/**
  * @brief  Target receive private data in interrupt mode.
  * @param  hi3c  Pointer to a hal_i3c_handle_t
  * @param  p_data  Pointer to the data
  * @param  size_byte  Size of the data in bytes
  * @note   This API can be used when the I3C is acting as target.
  * @retval HAL_OK  Operation completed successfully
  * @retval HAL_BUSY  Concurrent process ongoing
  * @retval HAL_ERROR  Operation completed with error
  * @retval HAL_INVALID_PARAM  Invalid parameter
  */
hal_status_t HAL_I3C_TGT_Receive_IT(hal_i3c_handle_t *hi3c, uint8_t *p_data, uint32_t size_byte)
{
  I3C_TypeDef *p_i3cx;
  hal_status_t hal_status = HAL_OK;
  uint32_t it_source;

  ASSERT_DBG_PARAM((hi3c != NULL));
  ASSERT_DBG_PARAM((p_data != NULL));
  ASSERT_DBG_PARAM((size_byte != 0U));
  ASSERT_DBG_PARAM(hi3c->mode == HAL_I3C_MODE_TGT);
  ASSERT_DBG_STATE(hi3c->global_state, HAL_I3C_STATE_IDLE);

  p_i3cx = I3C_GET_INSTANCE(hi3c);

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if ((p_data == NULL) || (size_byte == 0U))
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  /* Read IER register */
  it_source = LL_I3C_READ_REG(p_i3cx, IER);

  /* Check if DEF or GRP CCC notifications are enabled */
  if ((I3C_CHECK_IT_SOURCE(it_source, (LL_I3C_IER_DEFIE | LL_I3C_IER_RXFNEIE)) != 0U)
      || (I3C_CHECK_IT_SOURCE(it_source, (LL_I3C_IER_GRPIE | LL_I3C_IER_RXFNEIE)) != 0U))
  {
    return HAL_ERROR;
  }

  /* Verify the dynamic address validity */
  if (LL_I3C_IsEnabledOwnDynAddress(p_i3cx) == 0U)
  {
    return HAL_ERROR;
  }

  HAL_CHECK_UPDATE_STATE(hi3c, global_state, HAL_I3C_STATE_IDLE, HAL_I3C_STATE_RX);

#if defined(USE_HAL_I3C_GET_LAST_ERRORS) && (USE_HAL_I3C_GET_LAST_ERRORS == 1)
  hi3c->last_error_codes = HAL_I3C_ERROR_NONE;
#endif /* USE_HAL_I3C_GET_LAST_ERRORS */
  hi3c->p_rx_data = p_data;
  hi3c->data_size = size_byte;
  hi3c->rx_count = size_byte;
  hi3c->xfer_isr = I3C_Tgt_Rx_ISR;

  /* Check on the Rx threshold to know the Rx treatment process: byte or word */
  if (LL_I3C_GetRxFIFOThreshold(p_i3cx) == LL_I3C_RXFIFO_THRESHOLD_1_4)
  {
    hi3c->p_rx_func = &I3C_ReceiveByteTreatment;
  }
  else
  {
    hi3c->p_rx_func = &I3C_ReceiveWordTreatment;
  }

  LL_I3C_EnableIT(p_i3cx, I3C_TGT_RX_IT);

  return hal_status;
}

#if defined(USE_HAL_I3C_DMA) && (USE_HAL_I3C_DMA == 1)
/**
  * @brief  Target receive private data in DMA mode.
  * @param  hi3c  Pointer to a hal_i3c_handle_t
  * @param  p_data  Pointer to the data
  * @param  size_byte  Size of the data in bytes
  * @note   This API can be used when the I3C is acting as target.
  * @retval HAL_OK  Operation completed successfully
  * @retval HAL_BUSY  Concurrent process ongoing
  * @retval HAL_ERROR  Operation completed with error
  * @retval HAL_INVALID_PARAM  Invalid parameter
  */
hal_status_t HAL_I3C_TGT_Receive_DMA(hal_i3c_handle_t *hi3c, uint8_t *p_data, uint32_t size_byte)
{
  I3C_TypeDef *p_i3cx;
  hal_status_t hal_status = HAL_OK;
  uint32_t it_source;
  hal_status_t rx_dma_status;
  uint32_t size_align_word;
#if defined(USE_ASSERT_DBG_PARAM)
  hal_dma_direct_xfer_config_t config_dma;
#endif /* USE_ASSERT_DBG_PARAM */

  ASSERT_DBG_PARAM((hi3c != NULL));
  ASSERT_DBG_PARAM((p_data != NULL));
  ASSERT_DBG_PARAM((size_byte != 0U));
  ASSERT_DBG_PARAM(hi3c->mode == HAL_I3C_MODE_TGT);
  ASSERT_DBG_STATE(hi3c->global_state, HAL_I3C_STATE_IDLE);

  p_i3cx = I3C_GET_INSTANCE(hi3c);

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if ((p_data == NULL) || (size_byte == 0U))
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  /* Read IER register */
  it_source = LL_I3C_READ_REG(p_i3cx, IER);

  /* Check if DEF or GRP CCC notifications are enabled */
  if ((I3C_CHECK_IT_SOURCE(it_source, (LL_I3C_IER_DEFIE | LL_I3C_IER_RXFNEIE)) != 0U)
      || (I3C_CHECK_IT_SOURCE(it_source, (LL_I3C_IER_GRPIE | LL_I3C_IER_RXFNEIE)) != 0U))
  {
    return HAL_ERROR;
  }

  /* Verify the dynamic address validity */
  if (LL_I3C_IsEnabledOwnDynAddress(p_i3cx) == 0U)
  {
    return HAL_ERROR;
  }

  HAL_CHECK_UPDATE_STATE(hi3c, global_state, HAL_I3C_STATE_IDLE, HAL_I3C_STATE_RX);

#if defined(USE_HAL_I3C_GET_LAST_ERRORS) && (USE_HAL_I3C_GET_LAST_ERRORS == 1)
  hi3c->last_error_codes = HAL_I3C_ERROR_NONE;
#endif /* USE_HAL_I3C_GET_LAST_ERRORS */
  hi3c->p_rx_data = p_data;
  hi3c->rx_count = size_byte;
  hi3c->xfer_isr = I3C_Tgt_Rx_DMA_ISR;

  /*------------------------------------ I3C DMA channel for the Rx Data ---------------------------------------------*/
  hi3c->hdma_rx->p_xfer_cplt_cb = I3C_DMADataReceiveCplt;
  hi3c->hdma_rx->p_xfer_error_cb = I3C_DMAError;
  hi3c->hdma_rx->p_xfer_abort_cb = NULL;
  hi3c->hdma_tx->p_xfer_abort_cb = NULL;

#if defined(USE_ASSERT_DBG_PARAM)
  HAL_DMA_GetConfigDirectXfer(hi3c->hdma_rx, &config_dma);
#endif /* USE_ASSERT_DBG_PARAM */

  /* Check on the Rx threshold to know the Rx treatment process: byte or word */
  if (LL_I3C_GetRxFIFOThreshold(p_i3cx) == LL_I3C_RXFIFO_THRESHOLD_1_4)
  {
    ASSERT_DBG_PARAM(IS_I3C_DMA_SOURCE_BYTE(config_dma.src_data_width));
    ASSERT_DBG_PARAM(IS_I3C_DMA_DESTINATION_BYTE(config_dma.dest_data_width));

    rx_dma_status = HAL_DMA_StartDirectXfer_IT(hi3c->hdma_rx, (uint32_t)&p_i3cx->RDR, (uint32_t)hi3c->p_rx_data,
                                               hi3c->rx_count);
  }
  else
  {
    ASSERT_DBG_PARAM(IS_I3C_DMA_SOURCE_WORD(config_dma.src_data_width));
    ASSERT_DBG_PARAM(IS_I3C_DMA_DESTINATION_WORD(config_dma.dest_data_width));

    /* Check to align data size in words */
    if ((hi3c->rx_count % 4U) == 0U)
    {
      size_align_word = hi3c->rx_count;
    }
    else
    {
      /* Modify size to be multiple of 4 */
      size_align_word = ((hi3c->rx_count + 4U) - (hi3c->rx_count % 4U));
    }

    rx_dma_status = HAL_DMA_StartDirectXfer_IT(hi3c->hdma_rx, (uint32_t)&p_i3cx->RDWR, (uint32_t)hi3c->p_rx_data,
                                               size_align_word);
  }

  if (rx_dma_status == HAL_OK)
  {
    LL_I3C_EnableIT(p_i3cx, I3C_XFER_DMA);
    hi3c->rx_count = 0UL;
    LL_I3C_EnableDMAReq_RX(p_i3cx);
  }
  else
  {
    hi3c->hdma_rx->p_xfer_cplt_cb = NULL;
    hi3c->hdma_rx->p_xfer_error_cb = NULL;
#if defined(USE_HAL_I3C_GET_LAST_ERRORS) && (USE_HAL_I3C_GET_LAST_ERRORS == 1)
    hi3c->last_error_codes = HAL_I3C_ERROR_DMA;
#endif /* USE_HAL_I3C_GET_LAST_ERRORS */
    hal_status = HAL_ERROR;
    I3C_StateIdle(hi3c);
  }

  return hal_status;
}
#endif /* USE_HAL_I3C_DMA */

/**
  * @brief  Target send Controller-Role request in polling mode.
  * @param  hi3c  Pointer to a hal_i3c_handle_t
  * @param  timeout_ms    Timeout duration in milliseconds
  * @note   This API can be used when the I3C is acting as target.
  * @note   After receiving the controller's response to the Controller-Role request, the application must configure
  *         the I3C as a controller using the HAL_I3C_CTRL_SetConfig() function.
  * @retval HAL_OK  Operation completed successfully
  * @retval HAL_BUSY  Concurrent process ongoing
  * @retval HAL_TIMEOUT  Operation exceeds user timeout
  * @retval HAL_ERROR  Operation completed with error
  */
hal_status_t HAL_I3C_TGT_ControlRoleReq(hal_i3c_handle_t *hi3c, uint32_t timeout_ms)
{
  I3C_TypeDef *p_i3cx;
  hal_status_t hal_status;

  ASSERT_DBG_PARAM((hi3c != NULL));
  ASSERT_DBG_PARAM(hi3c->mode == HAL_I3C_MODE_TGT);
  ASSERT_DBG_STATE(hi3c->global_state, HAL_I3C_STATE_IDLE);

  p_i3cx = I3C_GET_INSTANCE(hi3c);

  if (LL_I3C_IsEnabledOwnDynAddress(p_i3cx) == 0U)
  {
    return HAL_ERROR;
  }

  if (LL_I3C_IsEnabledControllerRoleReq(p_i3cx) == 0U)
  {
    return HAL_ERROR;
  }

  HAL_CHECK_UPDATE_STATE(hi3c, global_state, HAL_I3C_STATE_IDLE, HAL_I3C_STATE_TGT_REQ);

#if defined(USE_HAL_I3C_GET_LAST_ERRORS) && (USE_HAL_I3C_GET_LAST_ERRORS == 1)
  hi3c->last_error_codes = HAL_I3C_ERROR_NONE;
#endif /* USE_HAL_I3C_GET_LAST_ERRORS */

  /* Request Controllership */
  LL_I3C_TargetHandleMessage(p_i3cx, LL_I3C_TARGET_MTYPE_CONTROLLER_ROLE_REQ, 0UL);

  /* Wait Controllership completion confirmation flag */
  hal_status = I3C_WaitForFlagSet(hi3c, LL_I3C_EVR_CRUPDF, timeout_ms);

  if (hal_status == HAL_OK)
  {
    LL_I3C_ClearFlag_CRUPD(p_i3cx);
  }

  I3C_StateIdle(hi3c);

  return hal_status;
}

/**
  * @brief  Target send Controller-Role request in interrupt mode.
  * @param  hi3c  Pointer to a hal_i3c_handle_t
  * @note   This API can be used when the I3C is acting as target.
  * @note   After receiving the controller's response to the Controller-Role request, the application must configure
  *         the I3C as a controller using the HAL_I3C_CTRL_SetConfig() function.
  * @retval HAL_OK  Operation completed successfully
  * @retval HAL_BUSY  Concurrent process ongoing
  * @retval HAL_ERROR  Operation completed with error
  */
hal_status_t HAL_I3C_TGT_ControlRoleReq_IT(hal_i3c_handle_t *hi3c)
{
  I3C_TypeDef *p_i3cx;

  ASSERT_DBG_PARAM((hi3c != NULL));
  ASSERT_DBG_PARAM(hi3c->mode == HAL_I3C_MODE_TGT);
  ASSERT_DBG_STATE(hi3c->global_state, HAL_I3C_STATE_IDLE);

  p_i3cx = I3C_GET_INSTANCE(hi3c);

  /* Verify the dynamic address validity */
  if (LL_I3C_IsEnabledOwnDynAddress(p_i3cx) == 0U)
  {
    return HAL_ERROR;
  }

  /* Verify if Controller-Role request feature is enabled */
  if (LL_I3C_IsEnabledControllerRoleReq(p_i3cx) == 0U)
  {
    return HAL_ERROR;
  }

  HAL_CHECK_UPDATE_STATE(hi3c, global_state, HAL_I3C_STATE_IDLE, HAL_I3C_STATE_TGT_REQ);

#if defined(USE_HAL_I3C_GET_LAST_ERRORS) && (USE_HAL_I3C_GET_LAST_ERRORS == 1)
  hi3c->last_error_codes = HAL_I3C_ERROR_NONE;
#endif /* USE_HAL_I3C_GET_LAST_ERRORS */
  hi3c->xfer_isr = I3C_Tgt_CtrlRole_ISR;

  LL_I3C_EnableIT(p_i3cx, I3C_TGT_CTRLROLE_IT);

  /* Request Controllership */
  LL_I3C_TargetHandleMessage(p_i3cx, LL_I3C_TARGET_MTYPE_CONTROLLER_ROLE_REQ, 0UL);

  return HAL_OK;
}

/**
  * @brief  Target send Hot-Join request in polling mode.
  * @param  hi3c  Pointer to a hal_i3c_handle_t
  * @param  p_own_dynamic_address  Pointer to the target own dynamic address assigned by the controller.
  * @param  timeout_ms  Timeout duration in milliseconds
  * @note   This API can be used when the I3C is acting as target.
  * @retval HAL_OK  Operation completed successfully
  * @retval HAL_TIMEOUT  Operation exceeds user timeout
  * @retval HAL_BUSY  Concurrent process ongoing
  * @retval HAL_ERROR  Operation completed with error
  * @retval HAL_INVALID_PARAM  Invalid parameter
  */
hal_status_t HAL_I3C_TGT_HotJoinReq(hal_i3c_handle_t *hi3c, uint8_t *p_own_dynamic_address, uint32_t timeout_ms)
{
  I3C_TypeDef *p_i3cx;
  hal_status_t hal_status;

  ASSERT_DBG_PARAM((hi3c != NULL));
  ASSERT_DBG_PARAM((p_own_dynamic_address != NULL));
  ASSERT_DBG_PARAM(hi3c->mode == HAL_I3C_MODE_TGT);
  ASSERT_DBG_STATE(hi3c->global_state, HAL_I3C_STATE_IDLE);

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if ((p_own_dynamic_address == NULL))
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */
  p_i3cx = I3C_GET_INSTANCE(hi3c);

  if (LL_I3C_IsEnabledHotJoin(p_i3cx) == 0U)
  {
    return HAL_ERROR;
  }

  HAL_CHECK_UPDATE_STATE(hi3c, global_state, HAL_I3C_STATE_IDLE, HAL_I3C_STATE_TGT_REQ);

#if defined(USE_HAL_I3C_GET_LAST_ERRORS) && (USE_HAL_I3C_GET_LAST_ERRORS == 1)
  hi3c->last_error_codes = HAL_I3C_ERROR_NONE;
#endif /* USE_HAL_I3C_GET_LAST_ERRORS */

  /* Request Hot-Join */
  LL_I3C_TargetHandleMessage(p_i3cx, LL_I3C_TARGET_MTYPE_HOT_JOIN, 0UL);

  /* Wait Hot-Join completion confirmation flag */
  hal_status = I3C_WaitForFlagSet(hi3c, LL_I3C_EVR_DAUPDF, timeout_ms);

  if (hal_status == HAL_OK)
  {
    /* Clear dynamic address update flag */
    LL_I3C_ClearFlag_DAUPD(p_i3cx);
  }

  /* Check the validity of the own dynamic address */
  if (LL_I3C_IsEnabledOwnDynAddress(p_i3cx) == 0U)
  {
#if defined(USE_HAL_I3C_GET_LAST_ERRORS) && (USE_HAL_I3C_GET_LAST_ERRORS == 1)
    hi3c->last_error_codes = HAL_I3C_ERROR_DYNAMIC_ADDR;
#endif /* USE_HAL_I3C_GET_LAST_ERRORS */
    hal_status = HAL_ERROR;
  }
  else
  {
    *p_own_dynamic_address = LL_I3C_GetOwnDynamicAddress(p_i3cx);
  }

  I3C_StateIdle(hi3c);

  return hal_status;
}

/**
  * @brief  Target send Hot-Join request in interrupt mode.
  * @param  hi3c  Pointer to a hal_i3c_handle_t
  * @note   This API can be used when the I3C is acting as target.
  * @retval HAL_OK  Operation completed successfully
  * @retval HAL_BUSY  Concurrent process ongoing
  * @retval HAL_ERROR  Operation completed with error
  */
hal_status_t HAL_I3C_TGT_HotJoinReq_IT(hal_i3c_handle_t *hi3c)
{
  I3C_TypeDef *p_i3cx;

  ASSERT_DBG_PARAM((hi3c != NULL));
  ASSERT_DBG_PARAM(hi3c->mode == HAL_I3C_MODE_TGT);
  ASSERT_DBG_STATE(hi3c->global_state, HAL_I3C_STATE_IDLE);

  p_i3cx = I3C_GET_INSTANCE(hi3c);

  /* Check on the Hot-Join request feature */
  if (LL_I3C_IsEnabledHotJoin(p_i3cx) == 0U)
  {
    return HAL_ERROR;
  }

  HAL_CHECK_UPDATE_STATE(hi3c, global_state, HAL_I3C_STATE_IDLE, HAL_I3C_STATE_TGT_REQ);

#if defined(USE_HAL_I3C_GET_LAST_ERRORS) && (USE_HAL_I3C_GET_LAST_ERRORS == 1)
  hi3c->last_error_codes = HAL_I3C_ERROR_NONE;
#endif /* USE_HAL_I3C_GET_LAST_ERRORS */
  hi3c->xfer_isr = I3C_Tgt_HotJoin_ISR;

  LL_I3C_EnableIT(p_i3cx, I3C_TGT_HOTJOIN_IT);

  /* Request Hot-Join */
  LL_I3C_TargetHandleMessage(p_i3cx, LL_I3C_TARGET_MTYPE_HOT_JOIN, 0UL);

  return HAL_OK;
}

/**
  * @brief  Target send IBI request in polling mode.
  * @param  hi3c  Pointer to a hal_i3c_handle_t
  * @param  p_payload     Pointer to the buffer contains the payload data
  * @param  payload_size_byte  Payload buffer size in bytes
  * @param  timeout_ms    Timeout duration in milliseconds
  * @note   This API can be used when the I3C is acting as target.
  * @retval HAL_OK  Operation completed successfully
  * @retval HAL_BUSY  Concurrent process ongoing
  * @retval HAL_TIMEOUT  Operation exceeds user timeout
  * @retval HAL_ERROR  Operation completed with error
  * @retval HAL_INVALID_PARAM  Invalid parameter
  */
hal_status_t HAL_I3C_TGT_IBIReq(hal_i3c_handle_t *hi3c,
                                const uint8_t *p_payload,
                                uint32_t payload_size_byte,
                                uint32_t timeout_ms)
{
  I3C_TypeDef *p_i3cx;
  hal_status_t hal_status;
  uint32_t payload_value = 0UL;

  ASSERT_DBG_PARAM((hi3c != NULL));
  ASSERT_DBG_PARAM(hi3c->mode == HAL_I3C_MODE_TGT);
  ASSERT_DBG_STATE(hi3c->global_state, HAL_I3C_STATE_IDLE);

  p_i3cx = I3C_GET_INSTANCE(hi3c);

  if (LL_I3C_IsEnabledOwnDynAddress(p_i3cx) == 0U)
  {
    return HAL_ERROR;
  }

  if (LL_I3C_IsEnabledIBI(p_i3cx) == 0U)
  {
    return HAL_ERROR;
  }

  /* Update handle parameters */
  HAL_CHECK_UPDATE_STATE(hi3c, global_state, HAL_I3C_STATE_IDLE, HAL_I3C_STATE_TGT_REQ);

#if defined(USE_HAL_I3C_GET_LAST_ERRORS) && (USE_HAL_I3C_GET_LAST_ERRORS == 1)
  hi3c->last_error_codes = HAL_I3C_ERROR_NONE;
#endif /* USE_HAL_I3C_GET_LAST_ERRORS */

  /* Check on the IBI additional data */
  if (LL_I3C_GetDeviceIBIPayload(p_i3cx) == LL_I3C_IBI_ADDITIONAL_DATA)
  {
    ASSERT_DBG_PARAM((p_payload != NULL));
    ASSERT_DBG_PARAM(payload_size_byte != 0U);
#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
    /* Check on the p_payload and payload_size values */
    if ((p_payload == NULL) || (payload_size_byte == 0U))
    {
      I3C_StateIdle(hi3c);
      return HAL_INVALID_PARAM;
    }
#endif /* USE_HAL_CHECK_PARAM */

    /* For loop to calculate the payload value */
    for (uint32_t index = 0UL; index < payload_size_byte; index++)
    {
      payload_value |= ((uint32_t)p_payload[index] << (index * 8U));
    }

    /* Load IBI payload data */
    LL_I3C_SetIBIPayload(p_i3cx, payload_value);
  }

  /* Request IBI */
  LL_I3C_TargetHandleMessage(p_i3cx, LL_I3C_TARGET_MTYPE_IBI, payload_size_byte);

  /* Wait IBI completion confirmation flag */
  hal_status = I3C_WaitForFlagSet(hi3c, LL_I3C_EVR_IBIENDF, timeout_ms);

  if (hal_status == HAL_OK)
  {
    /* Clear IBI end process flag */
    LL_I3C_ClearFlag_IBIEND(p_i3cx);
  }

  I3C_StateIdle(hi3c);

  return hal_status;
}

/**
  * @brief  Target send IBI request in interrupt mode.
  * @param  hi3c  Pointer to a hal_i3c_handle_t
  * @param  p_payload     Pointer to the buffer contains the payload data
  * @param  payload_size_byte  Payload buffer size in bytes
  * @note   This API can be used when the I3C is acting as target.
  * @retval HAL_OK  Operation completed successfully
  * @retval HAL_BUSY  Concurrent process ongoing
  * @retval HAL_ERROR  Operation completed with error
  * @retval HAL_INVALID_PARAM  Invalid parameter
  */
hal_status_t HAL_I3C_TGT_IBIReq_IT(hal_i3c_handle_t *hi3c, const uint8_t *p_payload, uint32_t payload_size_byte)
{
  I3C_TypeDef *p_i3cx;
  hal_status_t hal_status = HAL_OK;
  uint32_t payload_value = 0UL;

  ASSERT_DBG_PARAM((hi3c != NULL));
  ASSERT_DBG_PARAM(hi3c->mode == HAL_I3C_MODE_TGT);
  ASSERT_DBG_STATE(hi3c->global_state, HAL_I3C_STATE_IDLE);

  p_i3cx = I3C_GET_INSTANCE(hi3c);

  if (LL_I3C_IsEnabledOwnDynAddress(p_i3cx) == 0U)
  {
    return HAL_ERROR;
  }

  if (LL_I3C_IsEnabledIBI(p_i3cx) == 0U)
  {
    return HAL_ERROR;
  }

  HAL_CHECK_UPDATE_STATE(hi3c, global_state, HAL_I3C_STATE_IDLE, HAL_I3C_STATE_TGT_REQ);

#if defined(USE_HAL_I3C_GET_LAST_ERRORS) && (USE_HAL_I3C_GET_LAST_ERRORS == 1)
  hi3c->last_error_codes = HAL_I3C_ERROR_NONE;
#endif /* USE_HAL_I3C_GET_LAST_ERRORS */
  hi3c->xfer_isr = I3C_Tgt_IBI_ISR;

  /* Check on the IBI additional data */
  if (LL_I3C_GetDeviceIBIPayload(p_i3cx) == LL_I3C_IBI_ADDITIONAL_DATA)
  {
    ASSERT_DBG_PARAM((p_payload != NULL));
    ASSERT_DBG_PARAM(payload_size_byte != 0U);
#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
    /* Check on the p_payload and payload_size values */
    if ((p_payload == NULL) || (payload_size_byte == 0U))
    {
      I3C_StateIdle(hi3c);
      return HAL_INVALID_PARAM;
    }
#endif /* USE_HAL_CHECK_PARAM */
    /* For loop to calculate the payload value */
    for (uint32_t index = 0UL; index < payload_size_byte; index++)
    {
      payload_value |= ((uint32_t)p_payload[index] << (index * 8U));
    }

    /* Load IBI payload data */
    LL_I3C_SetIBIPayload(p_i3cx, payload_value);
  }

  LL_I3C_EnableIT(p_i3cx, I3C_TGT_IBI_IT);

  /* Request IBI */
  LL_I3C_TargetHandleMessage(p_i3cx, LL_I3C_TARGET_MTYPE_IBI, payload_size_byte);

  return hal_status;
}

/**
  * @}
  */

/** @addtogroup I3C_Exported_Functions_Group8 Weak callback functions
  * @{
A set of Weak functions (or default Callbacks functions if USE_HAL_I3C_REGISTER_CALLBACKS is set to 1) which are used
to asynchronously informed the application in non-blocking modes (interrupt and DMA):
 - HAL_I3C_CTRL_XferCpltCallback()         : Controller Multiple transfer completed callback.
 - HAL_I3C_CTRL_DAACpltCallback()          : Controller Dynamic Address Assignment complete callback.
 - HAL_I3C_CTRL_TgtReqDynAddrCallback()    : Target request Dynamic Address callback.
 - HAL_I3C_TGT_TxCpltCallback()            : Target transmission complete callback.
 - HAL_I3C_TGT_RxCpltCallback()            : Target reception complete callback.
 - HAL_I3C_TGT_HotJoinCallback()           : Target Hot-Join process complete callback.
 - HAL_I3C_NotifyCallback()                : Target/Controller notification event callback.
 - HAL_I3C_ErrorCallback()                 : I3C error callback.
 - HAL_I3C_AbortCpltCallback()             : I3C abort callback.
  */

/**
  * @brief  Controller Multiple transfer completed callback.
  * @param  hi3c  Pointer to a hal_i3c_handle_t
  * @warning  This weak function must not be modified. When the callback is needed, it is overridden in the user file.
  */
__WEAK void HAL_I3C_CTRL_XferCpltCallback(hal_i3c_handle_t *hi3c)
{
  /* Prevent unused argument(s) compilation warning */
  STM32_UNUSED(hi3c);

  /* NOTE: This function must not be modified, when the callback is needed,
     the HAL_I3C_CTRL_XferCpltCallback must be implemented in the user file
  */
}

/**
  * @brief  Controller dynamic address assignment complete callback.
  * @param  hi3c  Pointer to a hal_i3c_handle_t
  * @warning  This weak function must not be modified. When the callback is needed, it is overridden in the user file.
  */
__WEAK void HAL_I3C_CTRL_DAACpltCallback(hal_i3c_handle_t *hi3c)
{
  /* Prevent unused argument(s) compilation warning */
  STM32_UNUSED(hi3c);

  /* NOTE: This function must not be modified, when the callback is needed,
     the HAL_I3C_CTRL_DAACpltCallback must be implemented in the user file
  */
}

/**
  * @brief  Target Request Dynamic Address callback.
  * @param  hi3c  Pointer to a hal_i3c_handle_t
  * @param  target_payload  Parameter indicates the target payload
  * @warning  This weak function must not be modified. When the callback is needed, it is overridden in the user file.
  */
__WEAK void HAL_I3C_CTRL_TgtReqDynAddrCallback(hal_i3c_handle_t *hi3c, uint64_t target_payload)
{
  /* Prevent unused argument(s) compilation warning */
  STM32_UNUSED(hi3c);
  STM32_UNUSED(target_payload);

  /* NOTE: This function must not be modified, when the callback is needed,
     the HAL_I3C_CTRL_TgtReqDynAddrCallback must be implemented in the user file
  */
}

/**
  * @brief  Target Transmission complete callback.
  * @param  hi3c  Pointer to a hal_i3c_handle_t
  * @warning  This weak function must not be modified. When the callback is needed, it is overridden in the user file.
  */
__WEAK void HAL_I3C_TGT_TxCpltCallback(hal_i3c_handle_t *hi3c)
{
  /* Prevent unused argument(s) compilation warning */
  STM32_UNUSED(hi3c);

  /* NOTE: This function must not be modified, when the callback is needed,
     the HAL_I3C_TGT_TxCpltCallback must be implemented in the user file
  */
}

/**
  * @brief  Target Reception complete callback.
  * @param  hi3c  Pointer to a hal_i3c_handle_t
  * @warning  This weak function must not be modified. When the callback is needed, it is overridden in the user file.
  */
__WEAK void HAL_I3C_TGT_RxCpltCallback(hal_i3c_handle_t *hi3c)
{
  /* Prevent unused argument(s) compilation warning */
  STM32_UNUSED(hi3c);

  /** NOTE: This function must not be modified, when the callback is needed,
    * the HAL_I3C_TGT_RxCpltCallback must be implemented in the user file
    */
}

/**
  * @brief  Target Hot-Join process complete callback.
  * @param  hi3c  Pointer to a hal_i3c_handle_t
  * @param  dynamic_address The returned dynamic address value after the Hot-Join process
  * @warning  This weak function must not be modified. When the callback is needed, it is overridden in the user file.
  */
__WEAK void HAL_I3C_TGT_HotJoinCallback(hal_i3c_handle_t *hi3c, uint8_t dynamic_address)
{
  /* Prevent unused argument(s) compilation warning */
  STM32_UNUSED(hi3c);
  STM32_UNUSED(dynamic_address);

  /** NOTE: This function must not be modified, when the callback is needed,
    * the HAL_I3C_TGT_HotJoinCallback must be implemented in the user file
    */
}

/**
  * @brief  Target/Controller Notification event callback.
  * @param  hi3c  Pointer to a hal_i3c_handle_t
  * @param  notifications  Parameter indicates which notification is signaled
  *                            It can be a combination value of @ref I3C_CTRL_NOTIFICATION or @ref I3C_TGT_NOTIFICATION.
  * @warning  This weak function must not be modified. When the callback is needed, it is overridden in the user file.
  */
__WEAK void HAL_I3C_NotifyCallback(hal_i3c_handle_t *hi3c, uint32_t notifications)
{
  /* Prevent unused argument(s) compilation warning */
  STM32_UNUSED(hi3c);
  STM32_UNUSED(notifications);

  /**  NOTE: This function must not be modified, when the callback is needed,
    *  the HAL_I3C_NotifyCallback must be implemented in the user file
    */
}

/**
  * @brief  Error callback.
  * @param  hi3c  Pointer to a hal_i3c_handle_t
  * @warning  This weak function must not be modified. When the callback is needed, it is overridden in the user file.
  */
__WEAK void HAL_I3C_ErrorCallback(hal_i3c_handle_t *hi3c)
{
  /* Prevent unused argument(s) compilation warning */
  STM32_UNUSED(hi3c);

  /**  NOTE: This function must not be modified, when the callback is needed,
    *  the HAL_I3C_ErrorCallback must be implemented in the user file
    */
}

/**
  * @brief  Abort complete callback.
  * @param  hi3c  Pointer to a hal_i3c_handle_t
  * @warning  This weak function must not be modified. When the callback is needed, it is overridden in the user file.
  */
__WEAK void HAL_I3C_AbortCpltCallback(hal_i3c_handle_t *hi3c)
{
  /* Prevent unused argument(s) compilation warning */
  STM32_UNUSED(hi3c);

  /**  NOTE: This function must not be modified, when the callback is needed,
    *  the HAL_I3C_AbortCpltCallback must be implemented in the user file
    */
}

/**
  * @}
  */

/** @addtogroup I3C_Exported_Functions_Group9 Generic and common functions
  * @{
A set of functions allowing to Abort transfer or to get in run-time the status of the peripheral:
  - HAL_I3C_Abort_IT() to abort the current transfer either in DMA or IT.
  - HAL_I3C_GetState() to get the I3C handle state.
  - HAL_I3C_GetMode() to get the I3C handle mode.
  - HAL_I3C_GetLastErrorCodes() to get the last error code.
  - HAL_I3C_GetClockFreq() to get the kernel clock frequency
  - HAL_I3C_CTRL_GetENTDAA_PayloadInfo() to get BCR, DCR and PID information after ENTDAA.
  - HAL_I3C_GetCCCInfo() to retrieve some specific associated CCC event data.
  - HAL_I3C_GetDataCounter() to get the counter data.
  */

/**
  * @brief  Abort an I3C IT or DMA process communication with Interrupt.
  * @param  hi3c  Pointer to a hal_i3c_handle_t
  * @retval HAL_OK  Operation completed successfully
  */
hal_status_t HAL_I3C_Abort_IT(hal_i3c_handle_t *hi3c)
{
  I3C_TypeDef *p_i3cx;

  ASSERT_DBG_PARAM((hi3c != NULL));
  ASSERT_DBG_STATE(hi3c->global_state, I3C_STATE_ALL_EXCEPT_INIT);

  p_i3cx = I3C_GET_INSTANCE(hi3c);

  if (hi3c->global_state != HAL_I3C_STATE_ABORT)
  {
    hi3c->global_state = HAL_I3C_STATE_ABORT;
#if defined(USE_HAL_I3C_GET_LAST_ERRORS) && (USE_HAL_I3C_GET_LAST_ERRORS == 1)
    hi3c->last_error_codes = HAL_I3C_ERROR_NONE;
#endif /* USE_HAL_I3C_GET_LAST_ERRORS */

    LL_I3C_DisableIT_ERR(p_i3cx);
    hi3c->xfer_isr = I3C_Abort_ISR;

    /* Flush the different Fifos to generate an automatic stop mode link to underflow or overflow detection timeout */
    LL_I3C_RequestTxFIFOFlush(p_i3cx);
    LL_I3C_RequestRxFIFOFlush(p_i3cx);

    if (hi3c->mode == HAL_I3C_MODE_CTRL)
    {
      LL_I3C_RequestControlFIFOFlush(p_i3cx);
      LL_I3C_RequestStatusFIFOFlush(p_i3cx);
    }

    /* Disable all DMA Requests */
    LL_I3C_DisableDMAReq_Control(p_i3cx);
    LL_I3C_DisableDMAReq_RX(p_i3cx);
    LL_I3C_DisableDMAReq_TX(p_i3cx);
    LL_I3C_DisableDMAReq_Status(p_i3cx);

    if (hi3c->mode == HAL_I3C_MODE_CTRL)
    {
      LL_I3C_EnableIT(p_i3cx, I3C_CTRL_RX_IT | I3C_CTRL_TX_IT);
    }
    else
    {
      LL_I3C_EnableIT(p_i3cx, I3C_TGT_RX_IT);
    }
  }

  return HAL_OK;
}

/**
  * @brief  Return the I3C handle state.
  * @param  hi3c  Pointer to a hal_i3c_handle_t
  * @retval global_state:
  *  - HAL_I3C_STATE_RESET    Not yet Initialized
  *  - HAL_I3C_STATE_INIT     I3C is initialized but not yet configured
  *  - HAL_I3C_STATE_IDLE     I3C initialized and a global config applied
  *  - HAL_I3C_STATE_TX       Data Transmission process is ongoing
  *  - HAL_I3C_STATE_RX       Data Reception process is ongoing
  *  - HAL_I3C_STATE_TX_RX    Data Multiple Transfer process is ongoing
  *  - HAL_I3C_STATE_DAA      Dynamic address assignment process is ongoing
  *  - HAL_I3C_STATE_TGT_REQ  Target request process is ongoing
  *  - HAL_I3C_STATE_ABORT    Abort user request ongoing
  */
hal_i3c_state_t HAL_I3C_GetState(const hal_i3c_handle_t *hi3c)
{
  return hi3c->global_state;
}

/**
  * @brief  Returns the I3C handle mode.
  * @param  hi3c  Pointer to a hal_i3c_handle_t
  * @retval Mode:
  *  - HAL_I3C_MODE_NONE          No I3C communication on going
  *  - HAL_I3C_MODE_CTRL    I3C communication is in controller Mode
  *  - HAL_I3C_MODE_TGT        I3C communication is in target Mode
  */
hal_i3c_mode_t HAL_I3C_GetMode(const hal_i3c_handle_t *hi3c)
{
  ASSERT_DBG_STATE(hi3c->global_state, I3C_STATE_ALL_EXCEPT_INIT);
  return hi3c->mode;
}
#if defined(USE_HAL_I3C_GET_LAST_ERRORS) && (USE_HAL_I3C_GET_LAST_ERRORS == 1)
/**
  * @brief  Returns errors limited to the last process.
  * @param  hi3c  Pointer to a hal_i3c_handle_t
  * @retval uint32_t last error code. It can be HAL_I3C_ERROR_NONE or a combinaison of the following values:
  * HAL_I3C_ERROR_DATA_HAND_OFF
  * HAL_I3C_ERROR_DATA_NACK
  * HAL_I3C_ERROR_ADDRESS_NACK
  * HAL_I3C_ERROR_COVR
  * HAL_I3C_ERROR_DOVR
  * HAL_I3C_ERROR_STALL
  * HAL_I3C_ERROR_DMA
  * HAL_I3C_ERROR_DMA
  * HAL_I3C_ERROR_DYNAMIC_ADDR
  */
uint32_t HAL_I3C_GetLastErrorCodes(const hal_i3c_handle_t *hi3c)
{
  ASSERT_DBG_PARAM((hi3c != NULL));
  ASSERT_DBG_STATE(hi3c->global_state, I3C_STATE_ALL_EXCEPT_INIT);

  return hi3c->last_error_codes;
}
#endif /* USE_HAL_I3C_GET_LAST_ERRORS */

/**
  * @brief  Get the data counter according to the current usecase (tgt/ctrl, transfer or not).
  * @param  hi3c  Pointer to a hal_i3c_handle_t
  * @retval data counter:
  *    - During the Dynamic Address Assignment process (ENTDAA CCC):
  *        - When the I3C acts as controller: number of targets detected.
  *        - When the I3C acts as target: number of transmitted bytes.
  *    - During the transfer:
  *        - Whatever the I3C acts as controller or target: number of data bytes read from or transmitted
             on the I3C bus during the message.
  */
uint32_t HAL_I3C_GetDataCounter(hal_i3c_handle_t *hi3c)
{
  ASSERT_DBG_PARAM((hi3c != NULL));
  ASSERT_DBG_STATE(hi3c->global_state, I3C_STATE_ALL_EXCEPT_INIT);

  return LL_I3C_GetXferDataCount(I3C_GET_INSTANCE(hi3c));
}

/**
  * @brief  Target/Controller get the Common Command Code (CCC) information updated after notifications.
  *  |-------------------------------------|----------------------------------------------------- |
  *  | CCC Notification                    | Updated fields in p_ccc_info                         |
  *  |-------------------------------------|----------------------------------------------------- |
  *  | HAL_I3C_TGT_NOTIFICATION_DAU        | dynamic_addr, dynamic_addr_valid                     |
  *  | HAL_I3C_TGT_NOTIFICATION_SETMWL     | max_write_length                                     |
  *  | HAL_I3C_TGT_NOTIFICATION_SETMRL     | max_read_length                                      |
  *  | HAL_I3C_TGT_NOTIFICATION_RSTACT     | reset_action                                         |
  *  | HAL_I3C_TGT_NOTIFICATION_ENTAS_X    | activity_state                                       |
  *  | HAL_I3C_TGT_NOTIFICATION_ENEC_DISEC | hot_join_allowed, in_band_allowed, ctrl_role_allowed |
  *  | HAL_I3C_CTRL_NOTIFICATION_IBI       | ibi_cr_tgt_addr, ibi_tgt_nb_payload, ibi_tgt_payload |
  *  | HAL_I3C_CTRL_NOTIFICATION_CR        | ibi_cr_tgt_addr                                      |
  *  |-------------------------------------|----------------------------------------------------- |
  * @param  hi3c  Pointer to a hal_i3c_handle_t
  * @param  notifications  Notification. It can be a combination value of @ref I3C_CTRL_NOTIFICATION
                               or @ref I3C_TGT_NOTIFICATION
  * @param  p_ccc_info  Pointer to an I3C_CCCInfoTypeDef structure that contains the CCC information
  *                     updated after CCC event.
  * @retval HAL_OK  Operation completed successfully
  * @retval HAL_INVALID_PARAM  Invalid parameter
  */
hal_status_t HAL_I3C_GetCCCInfo(const hal_i3c_handle_t *hi3c, uint32_t notifications,
                                hal_i3c_ccc_info_t *p_ccc_info)
{
  I3C_TypeDef *p_i3cx;
  hal_status_t hal_status = HAL_OK;

  ASSERT_DBG_PARAM((hi3c != NULL));
  ASSERT_DBG_PARAM((p_ccc_info != NULL));
  ASSERT_DBG_STATE(hi3c->global_state, HAL_I3C_STATE_IDLE);

  p_i3cx = I3C_GET_INSTANCE(hi3c);

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if ((p_ccc_info == NULL))
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  /* Retrieve Target Dynamic Address value and Validity (target/controller) */
  if ((notifications & HAL_I3C_TGT_NOTIFICATION_DAU) == HAL_I3C_TGT_NOTIFICATION_DAU)
  {
    p_ccc_info->dynamic_addr_valid = LL_I3C_IsEnabledOwnDynAddress(p_i3cx);
    p_ccc_info->dynamic_addr = LL_I3C_GetOwnDynamicAddress(p_i3cx);
  }

  /* Retrieve Maximum Write Data Length (target) */
  if ((notifications & HAL_I3C_TGT_NOTIFICATION_SETMWL) == HAL_I3C_TGT_NOTIFICATION_SETMWL)
  {
    p_ccc_info->max_write_length = LL_I3C_GetMaxWriteLength(p_i3cx);
  }

  /* Retrieve Maximum Read Data Length (target) */
  if ((notifications & HAL_I3C_TGT_NOTIFICATION_SETMRL) == HAL_I3C_TGT_NOTIFICATION_SETMRL)
  {
    p_ccc_info->max_read_length = LL_I3C_GetMaxReadLength(p_i3cx);
  }

  /* RetrieveResetAction/Level on receivedResetpattern (target) */
  if ((notifications & HAL_I3C_TGT_NOTIFICATION_RSTACT) == HAL_I3C_TGT_NOTIFICATION_RSTACT)
  {
    p_ccc_info->reset_action = (hal_i3c_reset_action_t) LL_I3C_GetResetAction(p_i3cx);
  }

  /* Retrieve Activity State (target) */
  if ((notifications & HAL_I3C_TGT_NOTIFICATION_ENTAS_X) == HAL_I3C_TGT_NOTIFICATION_ENTAS_X)
  {
    p_ccc_info->activity_state = (hal_i3c_activity_state_t) LL_I3C_GetActivityState(p_i3cx);
  }

  /* Retrieve Interrupt allowed status (target) */
  if ((notifications & HAL_I3C_TGT_NOTIFICATION_ENEC_DISEC) == HAL_I3C_TGT_NOTIFICATION_ENEC_DISEC)
  {
    p_ccc_info->hot_join_allowed = LL_I3C_IsEnabledHotJoin(p_i3cx);
    p_ccc_info->in_band_allowed = LL_I3C_IsEnabledIBI(p_i3cx);
    p_ccc_info->ctrl_role_allowed = LL_I3C_IsEnabledControllerRoleReq(p_i3cx);
  }

  /* Retrieve In Band Interrupt information (controller) */
  if ((notifications & HAL_I3C_CTRL_NOTIFICATION_IBI) == HAL_I3C_CTRL_NOTIFICATION_IBI)
  {
    p_ccc_info->ibi_cr_tgt_addr = LL_I3C_GetIBITargetAddr(p_i3cx);
    p_ccc_info->ibi_tgt_nb_payload = LL_I3C_GetNbIBIAddData(p_i3cx);
    p_ccc_info->ibi_tgt_payload = LL_I3C_GetIBIPayload(p_i3cx);
  }

  /* Retrieve Controller-Role request Interrupt information (controller) */
  if ((notifications & HAL_I3C_CTRL_NOTIFICATION_CR) == HAL_I3C_CTRL_NOTIFICATION_CR)
  {
    p_ccc_info->ibi_cr_tgt_addr = LL_I3C_GetIBITargetAddr(p_i3cx);
  }

  return hal_status;
}

/** @brief  Return the peripheral clock frequency for I3C.
  * @param  hi3c  Pointer to a hal_i3c_handle_t
  * @retval uint32_t Frequency in Hz.
  *                  0 if the source clock of the I3C is not configured or not ready.
  */
uint32_t HAL_I3C_GetClockFreq(const hal_i3c_handle_t *hi3c)
{
  ASSERT_DBG_PARAM((hi3c != NULL));
  ASSERT_DBG_STATE(hi3c->global_state, I3C_STATE_ALL);

  return HAL_RCC_I3C_GetKernelClkFreq(I3C_GET_INSTANCE(hi3c));
}

/**
  * @brief  Get BCR, DCR and PID information after ENTDAA.
  * @param  entdaa_payload   Payload received after ENTDAA
  * @param  p_entdaa_payload Pointer to an I3C_ENTDAAPayloadTypeDef structure that contains the BCR, DCR and PID
  *                          information.
  * @note   This API can be used when the I3C is acting as controller.
  * @retval HAL_OK  Operation completed successfully
  * @retval HAL_INVALID_PARAM  Invalid parameter
  */
hal_status_t HAL_I3C_CTRL_GetENTDAA_PayloadInfo(uint64_t entdaa_payload,
                                                hal_i3c_entdaa_payload_t *p_entdaa_payload)
{
  hal_status_t hal_status = HAL_OK;
  uint32_t bcr;
  uint64_t pid;

  ASSERT_DBG_PARAM((p_entdaa_payload != NULL));

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (p_entdaa_payload == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  /* Get bus characterics */
  bcr = HAL_I3C_GET_BCR(entdaa_payload);

  /* Retrieve BCR information */
  p_entdaa_payload->bcr.ibi_payload = (hal_i3c_ibi_payload_status_t) HAL_I3C_GET_IBI_PAYLOAD(bcr);
  p_entdaa_payload->bcr.ibi_request_capable = (hal_i3c_ibi_req_status_t) HAL_I3C_GET_IBI_CAPABLE(bcr);
  p_entdaa_payload->bcr.device_role = (hal_i3c_ctrl_role_status_t) HAL_I3C_GET_CR_CAPABLE(bcr);
  p_entdaa_payload->bcr.advanced_capabilities = (hal_i3c_adv_capabilities_status_t) HAL_I3C_GET_ADVANCED_CAPABLE(bcr);
  p_entdaa_payload->bcr.offline_capable = (hal_i3c_offline_capable_status_t) HAL_I3C_GET_OFFLINE_CAPABLE(bcr);
  p_entdaa_payload->bcr.virtual_target_support = (hal_i3c_virtual_tgt_status_t) HAL_I3C_GET_VIRTUAL_TGT(bcr);
  p_entdaa_payload->bcr.max_data_speed_limitation = (hal_i3c_max_speed_limit_status_t)
                                                    HAL_I3C_GET_MAX_DATA_SPEED_LIMIT(bcr);

  /* Get device characterics */
  p_entdaa_payload->dcr = HAL_I3C_GET_DCR(entdaa_payload);

  /* Get provisioned ID */
  pid = HAL_I3C_GET_PID(entdaa_payload);

  /* Change PID from big endian to litlle endian */
  pid = (uint64_t)((((uint64_t)HAL_I3C_BIG_TO_LITTLE_ENDIAN((uint32_t) pid) << 32) |
                    ((uint64_t)HAL_I3C_BIG_TO_LITTLE_ENDIAN((uint32_t)(pid >> 32)))) >> 16);

  /* Retrieve PID information */
  p_entdaa_payload->pid.mipi_manuf_id = HAL_I3C_GET_MIPIMID(pid);
  p_entdaa_payload->pid.id_type_sel = HAL_I3C_GET_IDTSEL(pid);
  p_entdaa_payload->pid.part_id = HAL_I3C_GET_PART_ID(pid);
  p_entdaa_payload->pid.mipi_id = HAL_I3C_GET_MIPIID(pid);

  return hal_status;
}

/**
  * @}
  */

#if defined(USE_HAL_MUTEX) && (USE_HAL_MUTEX == 1)
/** @defgroup I3C_Exported_Functions_Group10 Acquire/release the bus
  * @{
A set of functions allowing to acquire/release the bus based on the HAL OS abstraction layer (stm32_hal_os.c/.h osal):
 - HAL_I3C_AcquireBus() acquires the I3C bus.
 - HAL_I3C_ReleaseBus() releases the I3C bus.
  */

/**
  * @brief  Acquire the I3C bus thanks to the HAL OS abstraction layer (stm32_hal_os.c/.h osal).
  * @param  hi3c  Pointer to a hal_i3c_handle_t
  * @param  timeout_ms  Timeout duration in milliseconds
  * @note   The HAL_I3C_AcquireBus() must be called from thread mode only (not from handler mode i.e from ISR).
  * @retval HAL_OK  Operation completed successfully
  * @retval HAL_ERROR Operation completed with error
  */
hal_status_t HAL_I3C_AcquireBus(hal_i3c_handle_t *hi3c, uint32_t timeout_ms)
{
  hal_status_t hal_status = HAL_ERROR;

  ASSERT_DBG_PARAM((hi3c != NULL));
  ASSERT_DBG_STATE(hi3c->global_state, I3C_STATE_ALL);

  if (HAL_OS_SemaphoreTake(&hi3c->semaphore, timeout_ms) == HAL_OS_OK)
  {
    hal_status = HAL_OK;
  }

  return hal_status;
}

/**
  * @brief  Release the I3C bus thanks to the HAL OS abstraction layer (stm32_hal_os.c/.h osal).
  * @param  hi3c  Pointer to a hal_i3c_handle_t
  * @note   The HAL_I3C_ReleaseBus() must be called from thread mode only (not from handler mode i.e from ISR).
  * @retval HAL_OK  Operation completed successfully
  * @retval HAL_ERROR Operation completed with error
  */
hal_status_t HAL_I3C_ReleaseBus(hal_i3c_handle_t *hi3c)
{
  hal_status_t hal_status = HAL_ERROR;

  ASSERT_DBG_PARAM((hi3c != NULL));
  ASSERT_DBG_STATE(hi3c->global_state, I3C_STATE_ALL);

  if (HAL_OS_SemaphoreRelease(&hi3c->semaphore) == HAL_OS_OK)
  {
    hal_status = HAL_OK;
  }

  return hal_status;
}

/**
  * @}
  */
#endif /* USE_HAL_MUTEX */

#if defined(USE_HAL_I3C_USER_DATA) && (USE_HAL_I3C_USER_DATA == 1)
/** @defgroup I3C_Exported_Functions_Group11 Set/get user data
  * @{
A set of functions allowing to manage a user data pointer stored to the I3C handle:
 - HAL_I3C_SetUserData() set the user data into the handle
 - HAL_I3C_GetUserData() get the user data from the handle
  */

/**
  * @brief  Set the user data pointer into the handle.
  * @param  hi3c  Pointer to a hal_i3c_handle_t
  * @param  p_user_data  Pointer to the user data
  */
void HAL_I3C_SetUserData(hal_i3c_handle_t *hi3c, const void *p_user_data)
{
  ASSERT_DBG_PARAM(hi3c != NULL);
  ASSERT_DBG_STATE(hi3c->global_state, I3C_STATE_ALL);

  hi3c->p_user_data = p_user_data;
}

/**
  * @brief  Get the user data pointer from the handle.
  * @param  hi3c  Pointer to a hal_i3c_handle_t
  * @retval void*  Pointer to the user data
  */
const void *HAL_I3C_GetUserData(const hal_i3c_handle_t *hi3c)
{
  ASSERT_DBG_PARAM(hi3c != NULL);
  ASSERT_DBG_STATE(hi3c->global_state, I3C_STATE_ALL);

  return (hi3c->p_user_data);
}

/**
  * @}
  */
#endif /* USE_HAL_I3C_USER_DATA */

/**
  * @}
  */

/* Private functions -------------------------------------------------------------------------------------------------*/
/** @addtogroup I3C_Private_Functions I3C Private Functions
  * @{
  */

/**
  * @brief  Interrupt Sub-Routine which handles target received events.
  * @param  hi3c  Pointer to a hal_i3c_handle_t
  * @param  it_masks  Flag Interrupt Masks flags to handle
  * @retval HAL_OK  Operation completed successfully
  */
static hal_status_t I3C_Tgt_Event_ISR(hal_i3c_handle_t *hi3c, uint32_t it_masks)
{
  uint32_t event = 0UL;
  I3C_TypeDef *p_i3cx = I3C_GET_INSTANCE(hi3c);

  /* I3C Rx FIFO not empty interrupt Check */
  if (I3C_CHECK_FLAG(it_masks, LL_I3C_MISR_RXFNEMIS) != 0U)
  {
    hi3c->p_rx_func(hi3c);
  }

  /* I3C target complete Controller-Role hand-off procedure (direct GETACCR CCC) event management --------------------*/
  if (I3C_CHECK_FLAG(it_masks, LL_I3C_MISR_CRUPDMIS) != 0U)
  {
    LL_I3C_ClearFlag_CRUPD(p_i3cx);
    event |= HAL_I3C_TGT_NOTIFICATION_GETACCCR;
  }

  /* I3C target receive any direct GETxxx CCC event management -------------------------------------------------------*/
  if (I3C_CHECK_FLAG(it_masks, LL_I3C_MISR_GETMIS) != 0U)
  {
    LL_I3C_ClearFlag_GET(p_i3cx);
    event |= HAL_I3C_TGT_NOTIFICATION_GET_X;
  }

  /* I3C target receive get status command (direct GETSTATUS CCC) event management -----------------------------------*/
  if (I3C_CHECK_FLAG(it_masks, LL_I3C_MISR_STAMIS) != 0U)
  {
    LL_I3C_ClearFlag_STA(p_i3cx);
    event |= HAL_I3C_TGT_NOTIFICATION_GET_STATUS;
  }

  /* I3C target receive a dynamic address update (ENTDAA/RSTDAA/SETNEWDA CCC) event management -----------------------*/
  if (I3C_CHECK_FLAG(it_masks, LL_I3C_MISR_DAUPDMIS) != 0U)
  {
    LL_I3C_ClearFlag_DAUPD(p_i3cx);
    event |= HAL_I3C_TGT_NOTIFICATION_DAU;
  }

  /* I3C target receive maximum write length update (direct SETMWL CCC) event management -----------------------------*/
  if (I3C_CHECK_FLAG(it_masks, LL_I3C_MISR_MWLUPDMIS) != 0U)
  {
    LL_I3C_ClearFlag_MWLUPD(p_i3cx);
    event |= HAL_I3C_TGT_NOTIFICATION_SETMWL;
  }

  /* I3C target receive maximum read length update(direct SETMRL CCC) event management -------------------------------*/
  if (I3C_CHECK_FLAG(it_masks, LL_I3C_MISR_MRLUPDMIS) != 0U)
  {
    LL_I3C_ClearFlag_MRLUPD(p_i3cx);
    event |= HAL_I3C_TGT_NOTIFICATION_SETMRL;
  }

  /* I3C target detectResetpattern (broadcast or direct RSTACT CCC) event management -------------------------------*/
  if (I3C_CHECK_FLAG(it_masks, LL_I3C_MISR_RSTMIS) != 0U)
  {
    LL_I3C_ClearFlag_RST(p_i3cx);
    event |= HAL_I3C_TGT_NOTIFICATION_RSTACT;
  }

  /* I3C target receive activity state update (direct or broadcast ENTASx) CCC event management ----------------------*/
  if (I3C_CHECK_FLAG(it_masks, LL_I3C_MISR_ASUPDMIS) != 0U)
  {
    LL_I3C_ClearFlag_ASUPD(p_i3cx);
    event |= HAL_I3C_TGT_NOTIFICATION_ENTAS_X;
  }

  /* I3C target receive a direct or broadcast ENEC/DISEC CCC event management ----------------------------------------*/
  if (I3C_CHECK_FLAG(it_masks, LL_I3C_MISR_INTUPDMIS) != 0U)
  {
    LL_I3C_ClearFlag_INTUPD(p_i3cx);
    event |= HAL_I3C_TGT_NOTIFICATION_ENEC_DISEC;
  }

  /* I3C target receive a broadcast DEFTGTS CCC event management -----------------------------------------------------*/
  if (I3C_CHECK_FLAG(it_masks, LL_I3C_MISR_DEFMIS) != 0U)
  {
    LL_I3C_ClearFlag_DEF(p_i3cx);
    event |= HAL_I3C_TGT_NOTIFICATION_DEFTGTS;
  }

  /* I3C target receive a group addressing (broadcast DEFGRPA CCC) event management ----------------------------------*/
  if (I3C_CHECK_FLAG(it_masks, LL_I3C_MISR_GRPMIS) != 0U)
  {
    LL_I3C_ClearFlag_GRP(p_i3cx);
    event |= HAL_I3C_TGT_NOTIFICATION_DEFGRPA;
  }

  /* I3C target wakeup event management ----------------------------------*/
  if (I3C_CHECK_FLAG(it_masks, LL_I3C_MISR_WKPMIS) != 0U)
  {
    LL_I3C_ClearFlag_WKP(p_i3cx);
    event |= HAL_I3C_TGT_NOTIFICATION_WKP;
  }

  if (event != 0U)
  {
#if (USE_HAL_I3C_REGISTER_CALLBACKS) && (USE_HAL_I3C_REGISTER_CALLBACKS == 1)
    hi3c->p_notify_cb(hi3c, event);
#else
    HAL_I3C_NotifyCallback(hi3c, event);
#endif /* USE_HAL_I3C_REGISTER_CALLBACKS */
  }

  return HAL_OK;
}

/**
  * @brief  Interrupt Sub-Routine which handles Controller received events.
  * @param  hi3c  Pointer to a hal_i3c_handle_t
  * @param  it_masks  Flag Interrupt Masks flags to handle
  * @retval HAL_OK  Operation completed successfully
  */
static hal_status_t I3C_Ctrl_Event_ISR(hal_i3c_handle_t *hi3c, uint32_t it_masks)
{
  I3C_TypeDef *p_i3cx;

  p_i3cx = I3C_GET_INSTANCE(hi3c);

  /* I3C controller receive IBI event management ---------------------------------------------------------------------*/
  if (I3C_CHECK_FLAG(it_masks, LL_I3C_MISR_IBIMIS) != 0U)
  {
    /* Clear IBI request flag */
    LL_I3C_ClearFlag_IBI(p_i3cx);
#if (USE_HAL_I3C_REGISTER_CALLBACKS) && (USE_HAL_I3C_REGISTER_CALLBACKS == 1)
    hi3c->p_notify_cb(hi3c, HAL_I3C_CTRL_NOTIFICATION_IBI);
#else
    HAL_I3C_NotifyCallback(hi3c, HAL_I3C_CTRL_NOTIFICATION_IBI);
#endif /* USE_HAL_I3C_REGISTER_CALLBACKS */
  }

  /* I3C controller Controller-Role request event management ---------------------------------------------------------*/
  if (I3C_CHECK_FLAG(it_masks, LL_I3C_MISR_CRMIS) != 0U)
  {
    /* Clear Controller-Role request flag */
    LL_I3C_ClearFlag_CR(p_i3cx);

#if (USE_HAL_I3C_REGISTER_CALLBACKS) && (USE_HAL_I3C_REGISTER_CALLBACKS == 1)
    hi3c->p_notify_cb(hi3c, HAL_I3C_CTRL_NOTIFICATION_CR);
#else
    HAL_I3C_NotifyCallback(hi3c, HAL_I3C_CTRL_NOTIFICATION_CR);
#endif /* USE_HAL_I3C_REGISTER_CALLBACKS */
  }

  /* I3C controller hot-join event management ------------------------------------------------------------------------*/
  if (I3C_CHECK_FLAG(it_masks, LL_I3C_MISR_HJMIS) != 0U)
  {
    /* Clear hot-join flag */
    LL_I3C_ClearFlag_HJ(p_i3cx);

#if (USE_HAL_I3C_REGISTER_CALLBACKS) && (USE_HAL_I3C_REGISTER_CALLBACKS == 1)
    hi3c->p_notify_cb(hi3c, HAL_I3C_CTRL_NOTIFICATION_HJ);
#else
    HAL_I3C_NotifyCallback(hi3c, HAL_I3C_CTRL_NOTIFICATION_HJ);
#endif /* USE_HAL_I3C_REGISTER_CALLBACKS */
  }

  return HAL_OK;
}

/**
  * @brief  Interrupt Sub-Routine which handles target Hot-Join event.
  * @param  hi3c  Pointer to a hal_i3c_handle_t
  * @param  it_masks  Flag Interrupt Masks flags to handle
  * @retval HAL_OK  Operation completed successfully
  */
static hal_status_t I3C_Tgt_HotJoin_ISR(hal_i3c_handle_t *hi3c, uint32_t it_masks)
{
  I3C_TypeDef *p_i3cx;

  p_i3cx = I3C_GET_INSTANCE(hi3c);

  /* I3C target receive a dynamic address update event management */
  if (I3C_CHECK_FLAG(it_masks, LL_I3C_MISR_DAUPDMIS) != 0U)
  {
    LL_I3C_ClearFlag_DAUPD(p_i3cx);
    LL_I3C_DisableIT(p_i3cx, I3C_TGT_HOTJOIN_IT);

    /* Check the validity of the own dynamic address */
    if (LL_I3C_IsEnabledOwnDynAddress(p_i3cx) == 1U)
    {
      I3C_StateIdle(hi3c);
#if (USE_HAL_I3C_REGISTER_CALLBACKS) && (USE_HAL_I3C_REGISTER_CALLBACKS == 1)
      hi3c->p_tgt_hot_join_cb(hi3c, (uint8_t)LL_I3C_GetOwnDynamicAddress(p_i3cx));
#else
      HAL_I3C_TGT_HotJoinCallback(hi3c, (uint8_t)LL_I3C_GetOwnDynamicAddress(p_i3cx));
#endif /* USE_HAL_I3C_REGISTER_CALLBACKS */
    }
    else
    {
#if defined(USE_HAL_I3C_GET_LAST_ERRORS) && (USE_HAL_I3C_GET_LAST_ERRORS == 1)
      hi3c->last_error_codes = HAL_I3C_ERROR_DYNAMIC_ADDR;
#endif /* USE_HAL_I3C_GET_LAST_ERRORS */

      I3C_ErrorTreatment(hi3c);
    }
  }
  return HAL_OK;
}

/**
  * @brief  Interrupt Sub-Routine which handles target Controller-Role event.
  * @param  hi3c  Pointer to a hal_i3c_handle_t
  * @param  it_masks  Flag Interrupt Masks flags to handle
  * @retval HAL_OK  Operation completed successfully
  */
static hal_status_t I3C_Tgt_CtrlRole_ISR(hal_i3c_handle_t *hi3c, uint32_t it_masks)
{
  I3C_TypeDef *p_i3cx;

  p_i3cx = I3C_GET_INSTANCE(hi3c);

  if (I3C_CHECK_FLAG(it_masks, LL_I3C_MISR_CRUPDMIS) != 0U)
  {
    LL_I3C_ClearFlag_CRUPD(p_i3cx);
    LL_I3C_DisableIT(p_i3cx, I3C_TGT_CTRLROLE_IT);
    I3C_StateIdle(hi3c);
#if (USE_HAL_I3C_REGISTER_CALLBACKS) && (USE_HAL_I3C_REGISTER_CALLBACKS == 1)
    hi3c->p_notify_cb(hi3c, HAL_I3C_TGT_NOTIFICATION_GETACCCR);
#else
    HAL_I3C_NotifyCallback(hi3c, HAL_I3C_TGT_NOTIFICATION_GETACCCR);
#endif /* USE_HAL_I3C_REGISTER_CALLBACKS */
  }
  return HAL_OK;
}

/**
  * @brief  Interrupt Sub-Routine which handles target IBI event.
  * @param  hi3c  Pointer to a hal_i3c_handle_t
  * @param  it_masks  Flag Interrupt Masks flags to handle
  * @retval HAL_OK  Operation completed successfully
  */
static hal_status_t I3C_Tgt_IBI_ISR(hal_i3c_handle_t *hi3c, uint32_t it_masks)
{
  I3C_TypeDef *p_i3cx;

  p_i3cx = I3C_GET_INSTANCE(hi3c);

  /* I3C target IBI end process event management ---------------------------------------------------------------------*/
  if (I3C_CHECK_FLAG(it_masks, LL_I3C_MISR_IBIENDMIS) != 0U)
  {
    LL_I3C_ClearFlag_IBIEND(p_i3cx);
    LL_I3C_DisableIT(p_i3cx, I3C_TGT_IBI_IT);
    I3C_StateIdle(hi3c);
#if (USE_HAL_I3C_REGISTER_CALLBACKS) && (USE_HAL_I3C_REGISTER_CALLBACKS == 1)
    hi3c->p_notify_cb(hi3c, HAL_I3C_TGT_NOTIFICATION_IBIEND);
#else
    HAL_I3C_NotifyCallback(hi3c, HAL_I3C_TGT_NOTIFICATION_IBIEND);
#endif /* USE_HAL_I3C_REGISTER_CALLBACKS */
  }
  return HAL_OK;
}

/**
  * @brief  Interrupt Sub-Routine which handles target transmit data in Interrupt mode.
  * @param  hi3c  Pointer to a hal_i3c_handle_t
  * @param  it_masks  Flag Interrupt Masks flags to handle
  * @retval HAL_OK  Operation completed successfully
  */
static hal_status_t I3C_Tgt_Tx_ISR(hal_i3c_handle_t *hi3c, uint32_t it_masks)
{
  I3C_TypeDef *p_i3cx;

  p_i3cx = I3C_GET_INSTANCE(hi3c);

  /* I3C Tx FIFO not full interrupt Check */
  if (I3C_CHECK_FLAG(it_masks, LL_I3C_MISR_TXFNFMIS) != 0U)
  {
    if (hi3c->tx_count > 0UL)
    {
      hi3c->p_tx_func(hi3c);
    }
  }

  /* I3C target frame complete event Check */
  if (I3C_CHECK_FLAG(it_masks, LL_I3C_MISR_FCMIS) != 0U)
  {
    LL_I3C_ClearFlag_FC(p_i3cx);

    /* Check if all data bytes are transmitted */
    if (LL_I3C_GetXferDataCount(p_i3cx) == hi3c->data_size)
    {
      LL_I3C_DisableIT(p_i3cx, I3C_TGT_TX_IT);
      I3C_StateIdle(hi3c);
#if (USE_HAL_I3C_REGISTER_CALLBACKS) && (USE_HAL_I3C_REGISTER_CALLBACKS == 1)
      hi3c->p_tgt_tx_cplt_cb(hi3c);
#else
      HAL_I3C_TGT_TxCpltCallback(hi3c);
#endif /* USE_HAL_I3C_REGISTER_CALLBACKS */
    }
    else
    {
      I3C_ErrorTreatment(hi3c);
    }
  }

  /* I3C target wakeup event management ----------------------------------*/
  if (I3C_CHECK_FLAG(it_masks, LL_I3C_MISR_WKPMIS) != 0U)
  {
    /* Clear WKP flag */
    LL_I3C_ClearFlag_WKP(p_i3cx);

#if (USE_HAL_I3C_REGISTER_CALLBACKS) && (USE_HAL_I3C_REGISTER_CALLBACKS == 1)
    hi3c->p_notify_cb(hi3c, HAL_I3C_TGT_NOTIFICATION_WKP);
#else
    HAL_I3C_NotifyCallback(hi3c, HAL_I3C_TGT_NOTIFICATION_WKP);
#endif /* USE_HAL_I3C_REGISTER_CALLBACKS */
  }

  return HAL_OK;
}

/**
  * @brief  Interrupt Sub-Routine which handles target receive data in Interrupt mode.
  * @param  hi3c  Pointer to a hal_i3c_handle_t
  * @param  it_masks  Flag Interrupt Masks flags to handle
  * @retval HAL_OK  Operation completed successfully
  */
static hal_status_t I3C_Tgt_Rx_ISR(hal_i3c_handle_t *hi3c, uint32_t it_masks)
{
  I3C_TypeDef *p_i3cx;

  p_i3cx = I3C_GET_INSTANCE(hi3c);

  /* I3C Rx FIFO not empty interrupt Check */
  if (I3C_CHECK_FLAG(it_masks, LL_I3C_MISR_RXFNEMIS) != 0U)
  {
    if (hi3c->rx_count > 0UL)
    {
      hi3c->p_rx_func(hi3c);
    }
  }

  /* I3C target frame complete event Check */
  if (I3C_CHECK_FLAG(it_masks, LL_I3C_MISR_FCMIS) != 0U)
  {
    LL_I3C_ClearFlag_FC(p_i3cx);

    /* Check if all data bytes are received */
    if (LL_I3C_GetXferDataCount(p_i3cx) == hi3c->data_size)
    {
      LL_I3C_DisableIT(p_i3cx, I3C_TGT_RX_IT);
      I3C_StateIdle(hi3c);
#if (USE_HAL_I3C_REGISTER_CALLBACKS) && (USE_HAL_I3C_REGISTER_CALLBACKS == 1)
      hi3c->p_tgt_rx_cplt_cb(hi3c);
#else
      HAL_I3C_TGT_RxCpltCallback(hi3c);
#endif /* USE_HAL_I3C_REGISTER_CALLBACKS */
    }
    else
    {
      I3C_ErrorTreatment(hi3c);
    }
  }

  /* I3C target wakeup event management ----------------------------------*/
  if (I3C_CHECK_FLAG(it_masks, LL_I3C_MISR_WKPMIS) != 0U)
  {
    /* Clear WKP flag */
    LL_I3C_ClearFlag_WKP(p_i3cx);

#if (USE_HAL_I3C_REGISTER_CALLBACKS) && (USE_HAL_I3C_REGISTER_CALLBACKS == 1)
    hi3c->p_notify_cb(hi3c, HAL_I3C_TGT_NOTIFICATION_WKP);
#else
    HAL_I3C_NotifyCallback(hi3c, HAL_I3C_TGT_NOTIFICATION_WKP);
#endif /* USE_HAL_I3C_REGISTER_CALLBACKS */
  }

  return HAL_OK;
}

#if defined(USE_HAL_I3C_DMA) && (USE_HAL_I3C_DMA == 1)
/**
  * @brief  Interrupt Sub-Routine which handles target transmit data in DMA mode.
  * @param  hi3c  Pointer to a hal_i3c_handle_t
  * @param  it_masks  Flag Interrupt Masks flags to handle
  * @retval HAL_OK  Operation completed successfully
  */
static hal_status_t I3C_Tgt_Tx_DMA_ISR(hal_i3c_handle_t *hi3c, uint32_t it_masks)
{
  I3C_TypeDef *p_i3cx;

  p_i3cx = I3C_GET_INSTANCE(hi3c);

  /* I3C target frame complete event Check */
  if (I3C_CHECK_FLAG(it_masks, LL_I3C_MISR_FCMIS) != 0U)
  {
    LL_I3C_ClearFlag_FC(p_i3cx);

    /* Check if all data bytes are transmitted */
    if (HAL_DMA_GetDirectXferRemainingDataByte(hi3c->hdma_tx) == 0U)
    {
      LL_I3C_DisableIT(p_i3cx, I3C_XFER_DMA);
      hi3c->tx_count = 0UL;
      I3C_StateIdle(hi3c);
#if (USE_HAL_I3C_REGISTER_CALLBACKS) && (USE_HAL_I3C_REGISTER_CALLBACKS == 1)
      hi3c->p_tgt_tx_cplt_cb(hi3c);
#else
      HAL_I3C_TGT_TxCpltCallback(hi3c);
#endif /* USE_HAL_I3C_REGISTER_CALLBACKS */
    }
    else
    {
      I3C_ErrorTreatment(hi3c);
    }
  }

  /* I3C target wakeup event management ----------------------------------*/
  if (I3C_CHECK_FLAG(it_masks, LL_I3C_MISR_WKPMIS) != 0U)
  {
    /* Clear WKP flag */
    LL_I3C_ClearFlag_WKP(p_i3cx);

#if (USE_HAL_I3C_REGISTER_CALLBACKS) && (USE_HAL_I3C_REGISTER_CALLBACKS == 1)
    hi3c->p_notify_cb(hi3c, HAL_I3C_TGT_NOTIFICATION_WKP);
#else
    HAL_I3C_NotifyCallback(hi3c, HAL_I3C_TGT_NOTIFICATION_WKP);
#endif /* USE_HAL_I3C_REGISTER_CALLBACKS */
  }

  return HAL_OK;
}

/**
  * @brief  Interrupt Sub-Routine which handles target receive data in DMA mode.
  * @param  hi3c  Pointer to a hal_i3c_handle_t
  * @param  it_masks  Flag Interrupt Masks flags to handle
  * @retval HAL_OK  Operation completed successfully
  */
static hal_status_t I3C_Tgt_Rx_DMA_ISR(hal_i3c_handle_t *hi3c, uint32_t it_masks)
{
  I3C_TypeDef *p_i3cx = I3C_GET_INSTANCE(hi3c);

  /* I3C target frame complete event Check */
  if (I3C_CHECK_FLAG(it_masks, LL_I3C_MISR_FCMIS) != 0U)
  {
    LL_I3C_ClearFlag_FC(p_i3cx);

    /* Check if all data bytes are received */
    if (HAL_DMA_GetDirectXferRemainingDataByte(hi3c->hdma_rx) == 0U)
    {
      LL_I3C_DisableIT(p_i3cx, I3C_XFER_DMA);
      hi3c->rx_count = 0UL;
      I3C_StateIdle(hi3c);
#if (USE_HAL_I3C_REGISTER_CALLBACKS) && (USE_HAL_I3C_REGISTER_CALLBACKS == 1)
      hi3c->p_tgt_rx_cplt_cb(hi3c);
#else
      HAL_I3C_TGT_RxCpltCallback(hi3c);
#endif /* USE_HAL_I3C_REGISTER_CALLBACKS */
    }
    else
    {
      I3C_ErrorTreatment(hi3c);
    }
  }

  /* I3C target wakeup event management ----------------------------------*/
  if (I3C_CHECK_FLAG(it_masks, LL_I3C_MISR_WKPMIS) != 0U)
  {
    /* Clear WKP flag */
    LL_I3C_ClearFlag_WKP(p_i3cx);

#if (USE_HAL_I3C_REGISTER_CALLBACKS) && (USE_HAL_I3C_REGISTER_CALLBACKS == 1)
    hi3c->p_notify_cb(hi3c, HAL_I3C_TGT_NOTIFICATION_WKP);
#else
    HAL_I3C_NotifyCallback(hi3c, HAL_I3C_TGT_NOTIFICATION_WKP);
#endif /* USE_HAL_I3C_REGISTER_CALLBACKS */
  }

  return HAL_OK;
}
#endif /* USE_HAL_I3C_DMA */

/**
  * @brief  Interrupt Sub-Routine which handles controller multiple transmission/reception in interrupt mode.
  * @param  hi3c  Pointer to a hal_i3c_handle_t
  * @param  it_masks  Flag Interrupt Masks flags to handle
  * @retval HAL_OK  Operation completed successfully
  */
static hal_status_t I3C_Ctrl_Multiple_Xfer_ISR(hal_i3c_handle_t *hi3c, uint32_t it_masks)
{
  I3C_TypeDef *p_i3cx;

  p_i3cx = I3C_GET_INSTANCE(hi3c);

  /* Check if Control FIFO requests data */
  if (I3C_CHECK_FLAG(it_masks, LL_I3C_MISR_CFNFMIS) != 0U)
  {
    if (hi3c->ctrl_count > 0UL)
    {
      I3C_ControlDataTreatment(hi3c);
    }
  }

  /* I3C Tx FIFO not full interrupt Check */
  if (I3C_CHECK_FLAG(it_masks, LL_I3C_MISR_TXFNFMIS) != 0U)
  {
    if (hi3c->tx_count > 0UL)
    {
      hi3c->p_tx_func(hi3c);
    }
  }

  /* I3C Rx FIFO not empty interrupt Check */
  if (I3C_CHECK_FLAG(it_masks, LL_I3C_MISR_RXFNEMIS) != 0U)
  {
    if (hi3c->rx_count > 0UL)
    {
      hi3c->p_rx_func(hi3c);
    }
  }

  /* I3C target frame complete event Check */
  if (I3C_CHECK_FLAG(it_masks, LL_I3C_MISR_FCMIS) != 0U)
  {
    LL_I3C_ClearFlag_FC(p_i3cx);

    if (hi3c->ctrl_count == 0U)
    {
      LL_I3C_DisableIT(p_i3cx, I3C_CTRL_TX_IT | I3C_CTRL_RX_IT);
      I3C_StateIdle(hi3c);
#if (USE_HAL_I3C_REGISTER_CALLBACKS) && (USE_HAL_I3C_REGISTER_CALLBACKS == 1)
      hi3c->p_ctrl_xfer_cplt_cb(hi3c);
#else
      HAL_I3C_CTRL_XferCpltCallback(hi3c);
#endif /* USE_HAL_I3C_REGISTER_CALLBACKS */
    }
    else
    {
      /* Then Initiate a Start condition */
      LL_I3C_RequestTransfer(p_i3cx);
    }
  }

  return HAL_OK;
}

/**
  * @brief  Interrupt Sub-Routine which handles controller multiple transmission/reception and controller received
  *         eventsin interrupt mode.
  * @param  hi3c  Pointer to a hal_i3c_handle_t
  * @param  it_masks  Flag Interrupt Masks flags to handle
  * @retval HAL_OK  Operation completed successfully
  */
static hal_status_t I3C_Ctrl_Multiple_Xfer_Listen_Event_ISR(hal_i3c_handle_t *hi3c, uint32_t it_masks)
{
  I3C_TypeDef *p_i3cx;

  p_i3cx = I3C_GET_INSTANCE(hi3c);

  /* I3C controller receive IBI event management ---------------------------------------------------------------------*/
  if (I3C_CHECK_FLAG(it_masks, LL_I3C_MISR_IBIMIS) != 0U)
  {
    /* Clear IBI request flag */
    LL_I3C_ClearFlag_IBI(p_i3cx);

#if (USE_HAL_I3C_REGISTER_CALLBACKS) && (USE_HAL_I3C_REGISTER_CALLBACKS == 1)
    hi3c->p_notify_cb(hi3c, HAL_I3C_CTRL_NOTIFICATION_IBI);
#else
    HAL_I3C_NotifyCallback(hi3c, HAL_I3C_CTRL_NOTIFICATION_IBI);
#endif /* USE_HAL_I3C_REGISTER_CALLBACKS */
  }

  /* I3C controller Controller-Role request event management ---------------------------------------------------------*/
  if (I3C_CHECK_FLAG(it_masks, LL_I3C_MISR_CRMIS) != 0U)
  {
    /* Clear Controller-Role request flag */
    LL_I3C_ClearFlag_CR(p_i3cx);

#if (USE_HAL_I3C_REGISTER_CALLBACKS) && (USE_HAL_I3C_REGISTER_CALLBACKS == 1)
    hi3c->p_notify_cb(hi3c, HAL_I3C_CTRL_NOTIFICATION_CR);
#else
    HAL_I3C_NotifyCallback(hi3c, HAL_I3C_CTRL_NOTIFICATION_CR);
#endif /* USE_HAL_I3C_REGISTER_CALLBACKS */
  }

  /* I3C controller hot-join event management ------------------------------------------------------------------------*/
  if (I3C_CHECK_FLAG(it_masks, LL_I3C_MISR_HJMIS) != 0U)
  {
    /* Clear hot-join flag */
    LL_I3C_ClearFlag_HJ(p_i3cx);

#if (USE_HAL_I3C_REGISTER_CALLBACKS) && (USE_HAL_I3C_REGISTER_CALLBACKS == 1)
    hi3c->p_notify_cb(hi3c, HAL_I3C_CTRL_NOTIFICATION_HJ);
#else
    HAL_I3C_NotifyCallback(hi3c, HAL_I3C_CTRL_NOTIFICATION_HJ);
#endif /* USE_HAL_I3C_REGISTER_CALLBACKS */
  }

  /* ISR controller transmission/reception */
  return (I3C_Ctrl_Multiple_Xfer_ISR(hi3c, it_masks));
}
/**
  * @brief  Interrupt Sub-Routine which handles controller CCC Dynamic Address Assignment command in interrupt mode.
  * @param  hi3c  Pointer to a hal_i3c_handle_t
  * @param  it_masks  Flag Interrupt Masks flags to handle
  * @retval HAL_OK  Operation completed successfully
  */
static hal_status_t I3C_Ctrl_DAA_ISR(hal_i3c_handle_t *hi3c, uint32_t it_masks)
{
  I3C_TypeDef *p_i3cx;

  p_i3cx = I3C_GET_INSTANCE(hi3c);

  uint64_t target_payload = 0UL;

  /* I3C Control FIFO not full interrupt Check */
  if (I3C_CHECK_FLAG(it_masks, LL_I3C_MISR_CFNFMIS) != 0U)
  {
    /* Write ENTDAA CCC information in the control register */
    LL_I3C_ControllerHandleCCC(p_i3cx, HAL_I3C_BROADCAST_ENTDAA, 0UL, LL_I3C_GENERATE_STOP);
  }

  /* I3C Tx FIFO not full interrupt Check */
  if (I3C_CHECK_FLAG(it_masks, LL_I3C_MISR_TXFNFMIS) != 0U)
  {
    /* Check on the Rx FIFO threshold to know the Dynamic Address Assignment treatment process: byte or word */
    if (LL_I3C_GetRxFIFOThreshold(p_i3cx) == LL_I3C_RXFIFO_THRESHOLD_1_4)
    {
      /* For loop to get target payload */
      for (uint32_t index = 0UL; index < 8U; index++)
      {
        /* Retrieve payload byte by byte */
        target_payload |= (uint64_t)((uint64_t)LL_I3C_ReceiveData8(p_i3cx) << (index * 8U));
      }
    }
    else
    {
      /* Retrieve first 32 bits payload */
      target_payload = (uint64_t)LL_I3C_ReceiveData32(p_i3cx);

      /* Retrieve second 32 bits payload */
      target_payload |= (uint64_t)((uint64_t)LL_I3C_ReceiveData32(p_i3cx) << 32U);
    }

#if (USE_HAL_I3C_REGISTER_CALLBACKS) && (USE_HAL_I3C_REGISTER_CALLBACKS == 1)
    hi3c->p_ctrl_tgt_req_dyn_addr_cb(hi3c, target_payload);
#else
    HAL_I3C_CTRL_TgtReqDynAddrCallback(hi3c, target_payload);
#endif /* USE_HAL_I3C_REGISTER_CALLBACKS */
  }

  /* I3C frame complete event Check */
  if (I3C_CHECK_FLAG(it_masks, LL_I3C_MISR_FCMIS) != 0U)
  {
    LL_I3C_ClearFlag_FC(p_i3cx);
    LL_I3C_DisableIT(p_i3cx, I3C_CTRL_DAA_IT);
    I3C_StateIdle(hi3c);
#if (USE_HAL_I3C_REGISTER_CALLBACKS) && (USE_HAL_I3C_REGISTER_CALLBACKS == 1)
    hi3c->p_ctrl_daa_cplt_cb(hi3c);
#else
    HAL_I3C_CTRL_DAACpltCallback(hi3c);
#endif /* USE_HAL_I3C_REGISTER_CALLBACKS */
  }

  return HAL_OK;
}

#if defined(USE_HAL_I3C_DMA) && (USE_HAL_I3C_DMA == 1)
/**
  * @brief  Interrupt Sub-Routine which handles controller multiple receive and transmit data in DMA mode.
  * @param  hi3c  Pointer to a hal_i3c_handle_t
  * @param  it_masks  Flag Interrupt Masks flags to handle
  * @retval HAL_OK  Operation completed successfully
  */
static hal_status_t I3C_Ctrl_Multiple_Xfer_DMA_ISR(hal_i3c_handle_t *hi3c, uint32_t it_masks)
{
  I3C_TypeDef *p_i3cx;

  p_i3cx = I3C_GET_INSTANCE(hi3c);

  /* I3C target frame complete event Check */
  if (I3C_CHECK_FLAG(it_masks, LL_I3C_MISR_FCMIS) != 0U)
  {
    LL_I3C_ClearFlag_FC(p_i3cx);

    if (HAL_DMA_GetDirectXferRemainingDataByte(hi3c->hdma_ctrl) == 0U)
    {
      /* Check if all data bytes are received or transmitted */
      if (HAL_DMA_GetDirectXferRemainingDataByte(hi3c->hdma_rx) == 0U)
      {
        if (HAL_DMA_GetDirectXferRemainingDataByte(hi3c->hdma_tx) == 0U)
        {
          LL_I3C_DisableIT(p_i3cx, I3C_XFER_DMA);
          hi3c->rx_count = 0UL;
          hi3c->tx_count = 0UL;
          I3C_StateIdle(hi3c);
#if (USE_HAL_I3C_REGISTER_CALLBACKS) && (USE_HAL_I3C_REGISTER_CALLBACKS == 1)
          hi3c->p_ctrl_xfer_cplt_cb(hi3c);
#else
          HAL_I3C_CTRL_XferCpltCallback(hi3c);
#endif /* USE_HAL_I3C_REGISTER_CALLBACKS */
        }
        else
        {
          I3C_ErrorTreatment(hi3c);
        }
      }
      else
      {
        I3C_ErrorTreatment(hi3c);
      }
    }
    else
    {
      /* Then Initiate a Start condition */
      LL_I3C_RequestTransfer(p_i3cx);
    }
  }
  return HAL_OK;
}
#endif /* USE_HAL_I3C_DMA */

/**
  * @brief  Interrupt Sub-Routine which handles abort process in interrupt mode.
  * @param  hi3c  Pointer to a hal_i3c_handle_t
  * @param  it_masks  Flag Interrupt Masks flags to handle
  * @retval HAL_OK  Operation completed successfully
  */
static hal_status_t I3C_Abort_ISR(hal_i3c_handle_t *hi3c, uint32_t it_masks)
{
  I3C_TypeDef *p_i3cx;

  p_i3cx = I3C_GET_INSTANCE(hi3c);

  /* I3C Rx FIFO not empty interrupt Check */
  if (I3C_CHECK_FLAG(it_masks, LL_I3C_MISR_RXFNEMIS) != 0U)
  {
    if (LL_I3C_IsActiveFlag_DOVR(p_i3cx) == 1U)
    {
      /* Flush remaining Rx data */
      LL_I3C_RequestRxFIFOFlush(p_i3cx);
    }
  }

  /** I3C Abort frame complete event Check
    * Evenif abort is called, the Frame completion can arrive if abort is requested at the end of the process
    * Evenif completion occurs, treat this end of process as abort completion process
    */
  if (I3C_CHECK_FLAG(it_masks, LL_I3C_MISR_FCMIS) != 0U)
  {
    /* Clear frame complete flag */
    LL_I3C_ClearFlag_FC(p_i3cx);

    I3C_ErrorTreatment(hi3c);
  }

  return HAL_OK;
}

#if defined(USE_HAL_I3C_DMA) && (USE_HAL_I3C_DMA == 1)
/**
  * @brief  DMA I3C control transmit process complete callback.
  * @param  hdma  Pointer to a hal_dma_handle_t structure that contains the configuration information
  *               for the specified DMA channel
  */
static void I3C_DMAControlTransmitCplt(hal_dma_handle_t *hdma)
{
  I3C_TypeDef *p_i3cx;

  hal_i3c_handle_t *hi3c = (hal_i3c_handle_t *)(((hal_dma_handle_t *)hdma)->p_parent);
  p_i3cx = I3C_GET_INSTANCE(hi3c);
  LL_I3C_DisableDMAReq_Control(p_i3cx);
}

/**
  * @brief  DMA I3C transmit data process complete callback.
  * @param  hdma  Pointer to a hal_dma_handle_t structure that contains the configuration information
  *               for the specified DMA channel
  */
static void I3C_DMADataTransmitCplt(hal_dma_handle_t *hdma)
{
  I3C_TypeDef *p_i3cx;

  hal_i3c_handle_t *hi3c = (hal_i3c_handle_t *)(((hal_dma_handle_t *)hdma)->p_parent);
  p_i3cx = I3C_GET_INSTANCE(hi3c);
  LL_I3C_DisableDMAReq_TX(p_i3cx);
}

/**
  * @brief  DMA I3C receive data process complete callback.
  * @param  hdma  Pointer to a hal_dma_handle_t structure that contains the configuration information
  *               for the specified DMA channel
  */
static void I3C_DMADataReceiveCplt(hal_dma_handle_t *hdma)
{
  I3C_TypeDef *p_i3cx;

  hal_i3c_handle_t *hi3c = (hal_i3c_handle_t *)(((hal_dma_handle_t *)hdma)->p_parent);
  p_i3cx = I3C_GET_INSTANCE(hi3c);
  LL_I3C_DisableDMAReq_RX(p_i3cx);
}

/**
  * @brief  DMA I3C communication error callback.
  * @param  hdma  Pointer to a hal_dma_handle_t structure that contains the configuration information
  *               for the specified DMA channel
  */
static void I3C_DMAError(hal_dma_handle_t *hdma)
{
  hal_i3c_handle_t *hi3c = (hal_i3c_handle_t *)(((hal_dma_handle_t *)hdma)->p_parent);
  hi3c->last_error_codes |= HAL_I3C_ERROR_DMA;
}

/**
  * @brief  DMA I3C communication abort callback to be called at end of DMA Abort procedure.
  * @param  hdma  Pointer to a hal_dma_handle_t structure that contains the configuration information
  *               for the specified DMA channel
  */
static void I3C_DMAAbort(hal_dma_handle_t *hdma)
{
  hal_i3c_handle_t *hi3c = (hal_i3c_handle_t *)(((hal_dma_handle_t *)hdma)->p_parent);
  hal_dma_channel_t dma_instance = hdma->instance;
  uint32_t no_callback = 0UL;

  if (hi3c->hdma_tx != NULL)
  {
    if (hi3c->hdma_tx->instance == dma_instance)
    {
      hi3c->hdma_tx->p_xfer_abort_cb = NULL;
    }
    else if (hi3c->hdma_tx->p_xfer_abort_cb != NULL)
    {
      no_callback++;
    }
    else
    {
      /* nothing to do */
    }
  }

  if (hi3c->hdma_rx != NULL)
  {
    if (hi3c->hdma_rx->instance == dma_instance)
    {
      hi3c->hdma_rx->p_xfer_abort_cb = NULL;
    }
    else if (hi3c->hdma_rx->p_xfer_abort_cb != NULL)
    {
      no_callback++;
    }
    else
    {
      /* nothing to do */
    }
  }

  if (hi3c->hdma_ctrl != NULL)
  {
    if (hi3c->hdma_ctrl->instance == dma_instance)
    {
      hi3c->hdma_ctrl->p_xfer_abort_cb = NULL;
    }
    else if (hi3c->hdma_ctrl->p_xfer_abort_cb != NULL)
    {
      no_callback++;
    }
    else
    {
      /* nothing to do */
    }
  }

  if (no_callback == 0U)
  {
    I3C_TreatErrorCallback(hi3c);
  }
}
#endif /* USE_HAL_I3C_DMA */

/**
  * @brief  Wait on flag set until timeout.
  * @param  hi3c  Pointer to a hal_i3c_handle_t
  * @param  flag  Flag to check.
  * @param  timeout_ms  Timeout duration in milliseconds
  * @retval HAL_OK  Operation completed successfully
  * @retval HAL_TIMEOUT  Operation exceeds user timeout
  * @retval HAL_ERROR  Operation completed with error
  */
static hal_status_t I3C_WaitForFlagSet(hal_i3c_handle_t *hi3c, uint32_t flag, uint32_t timeout_ms)
{
  hal_status_t hal_status = HAL_OK;
  I3C_TypeDef *p_i3cx = I3C_GET_INSTANCE(hi3c);
  uint32_t tickstart = HAL_GetTick();

  do
  {
    /* Check if an error occurs during Flag waiting */
    if (LL_I3C_IsActiveFlag_ERR(p_i3cx) != 0U)
    {
      LL_I3C_ClearFlag_ERR(p_i3cx);
#if defined(USE_HAL_I3C_GET_LAST_ERRORS) && (USE_HAL_I3C_GET_LAST_ERRORS == 1)
      I3C_GetErrorSources(hi3c);
#endif /* USE_HAL_I3C_GET_LAST_ERRORS */
      hal_status = HAL_ERROR;
    }
    /* Check for the timeout */
    else if (timeout_ms != HAL_MAX_DELAY)
    {
      if (((HAL_GetTick() - tickstart) > timeout_ms) || (timeout_ms == 0U))
      {
        if ((LL_I3C_READ_REG(p_i3cx, EVR) & (flag)) == 0U)
        {
          hal_status = HAL_TIMEOUT;
        }
      }
    }
    else
    {
      /* do nothing */
    }
  } while (((LL_I3C_READ_REG(p_i3cx, EVR) & (flag)) == 0U) && (hal_status == HAL_OK));

  return hal_status;
}

/**
  * @brief  I3C transmit by byte.
  * @param  hi3c  Pointer to a hal_i3c_handle_t
  */
static void I3C_TransmitByteTreatment(hal_i3c_handle_t *hi3c)
{
  I3C_TypeDef *p_i3cx = I3C_GET_INSTANCE(hi3c);

  /* Check TX FIFO not full flag */
  while ((LL_I3C_IsActiveFlag_TXFNF(p_i3cx) != 0U) && (hi3c->tx_count > 0UL))
  {
    LL_I3C_TransmitData8(p_i3cx, *hi3c->p_tx_data);
    hi3c->p_tx_data++;
    hi3c->tx_count--;
  }
}

/**
  * @brief  I3C transmit by word.
  * @param  hi3c  Pointer to a hal_i3c_handle_t
  */
static void I3C_TransmitWordTreatment(hal_i3c_handle_t *hi3c)
{
  I3C_TypeDef *p_i3cx = I3C_GET_INSTANCE(hi3c);

  /* Check TX FIFO not full flag */
  while (LL_I3C_IsActiveFlag_TXFNF(p_i3cx) == 1U)
  {
    LL_I3C_TransmitData32(p_i3cx, *((uint32_t *)(uint32_t)hi3c->p_tx_data));
    hi3c->p_tx_data += sizeof(uint32_t);

    if (hi3c->tx_count < sizeof(uint32_t))
    {
      hi3c->tx_count = 0UL;
    }
    else
    {
      hi3c->tx_count -= sizeof(uint32_t);
    }
  }
}

/**
  * @brief  I3C receive by byte.
  * @param  hi3c  Pointer to a hal_i3c_handle_t
  */
static void I3C_ReceiveByteTreatment(hal_i3c_handle_t *hi3c)
{
  I3C_TypeDef *p_i3cx = I3C_GET_INSTANCE(hi3c);

  /* Check RX FIFO not empty flag */
  while (LL_I3C_IsActiveFlag_RXFNE(p_i3cx) != 0U)
  {
    *hi3c->p_rx_data = LL_I3C_ReceiveData8(p_i3cx);
    hi3c->p_rx_data++;
    hi3c->rx_count--;
  }
}

/**
  * @brief  I3C receive by word.
  * @param  hi3c  Pointer to a hal_i3c_handle_t
  */
static void I3C_ReceiveWordTreatment(hal_i3c_handle_t *hi3c)
{
  I3C_TypeDef *p_i3cx = I3C_GET_INSTANCE(hi3c);

  /* Check RX FIFO not empty flag */
  while (LL_I3C_IsActiveFlag_RXFNE(p_i3cx) != 0U)
  {
    *((uint32_t *)(uint32_t)hi3c->p_rx_data) = LL_I3C_ReceiveData32(p_i3cx);
    hi3c->p_rx_data += sizeof(uint32_t);
    if (hi3c->rx_count > sizeof(uint32_t))
    {
      hi3c->rx_count -= sizeof(uint32_t);
    }
    else
    {
      hi3c->rx_count = 0UL;
    }
  }
}

/**
  * @brief  I3C Control data treatment.
  * @param  hi3c  Pointer to a hal_i3c_handle_t
  */
static void I3C_ControlDataTreatment(hal_i3c_handle_t *hi3c)
{
  I3C_TypeDef *p_i3cx = I3C_GET_INSTANCE(hi3c);

  /* Check if Control FIFO requests data */
  if (LL_I3C_IsActiveFlag_CFNF(p_i3cx) != 0U)
  {
    LL_I3C_WRITE_REG(p_i3cx, CR, *hi3c->p_ctrl_data);
    hi3c->p_ctrl_data++;
    hi3c->ctrl_count--;
  }
}

/**
  * @brief  I3C state change to HAL_I3C_STATE_IDLE.
  * @param  hi3c  Pointer to a hal_i3c_handle_t
  */
static void I3C_StateIdle(hal_i3c_handle_t *hi3c)
{
  if (hi3c->listen == HAL_I3C_LISTEN_ENABLED)
  {
    if (hi3c->mode == HAL_I3C_MODE_TGT)
    {
      hi3c->xfer_isr = I3C_Tgt_Event_ISR;
    }
    else
    {
      hi3c->xfer_isr = I3C_Ctrl_Event_ISR;
    }
  }
  else
  {
    hi3c->xfer_isr = NULL;
  }

  hi3c->global_state = HAL_I3C_STATE_IDLE;
}

#if defined(USE_HAL_I3C_GET_LAST_ERRORS) && (USE_HAL_I3C_GET_LAST_ERRORS == 1)
/**
  * @brief  I3C get error source.
  * @param  hi3c  Pointer to a hal_i3c_handle_t
  */
static void I3C_GetErrorSources(hal_i3c_handle_t *hi3c)
{
  const I3C_TypeDef *p_i3cx = I3C_GET_INSTANCE(hi3c);
  uint32_t error = (LL_I3C_READ_REG(p_i3cx, SER) & (I3C_SER_CODERR_Msk | I3C_SER_STALL_Msk | I3C_SER_DOVR_Msk
                                                    | I3C_SER_COVR_Msk | I3C_SER_ANACK_Msk | I3C_SER_DNACK_Msk
                                                    | I3C_SER_DERR_Msk));
  hi3c->last_error_codes |= error;
}
#endif /* USE_HAL_I3C_GET_LAST_ERRORS */

/**
  * @brief  Check if target device is ready for communication.
  * @param  hi3c  Pointer to a hal_i3c_handle_t
  * @param  p_device  Structure to define the device address and the device type.
  * @param  trials  Number of trials
  * @param  timeout_ms  Timeout duration
  * @retval HAL_OK  Operation completed successfully
  * @retval HAL_BUSY  Concurrent process ongoing
  * @retval HAL_ERROR  Operation completed with error
  * @retval HAL_TIMEOUT  Operation exceeds user timeout
  */
static hal_status_t I3C_Ctrl_IsDevice_Ready(hal_i3c_handle_t *hi3c,
                                            const i3c_device_t *p_device,
                                            uint32_t           trials,
                                            uint32_t           timeout_ms)
{
  volatile uint32_t I3C_Trials = 0UL;
  volatile uint32_t exit_condition;
  uint32_t CR_tmp;
  uint32_t tickstart;
  hal_status_t hal_status = HAL_OK;
  uint32_t arbitration_previous_state;
  I3C_TypeDef *p_i3cx;

  p_i3cx = I3C_GET_INSTANCE(hi3c);

  HAL_CHECK_UPDATE_STATE(hi3c, global_state, HAL_I3C_STATE_IDLE, HAL_I3C_STATE_TX);
#if defined(USE_HAL_I3C_GET_LAST_ERRORS) && (USE_HAL_I3C_GET_LAST_ERRORS == 1)
  hi3c->last_error_codes = HAL_I3C_ERROR_NONE;
#endif /* USE_HAL_I3C_GET_LAST_ERRORS */

  arbitration_previous_state = LL_I3C_IsEnabledArbitrationHeader(p_i3cx);
  LL_I3C_DisableArbitrationHeader(p_i3cx);

  /* HAL_I3C_DIRECTION_WRITE = 0 */
  CR_tmp = (((uint32_t)p_device->address << I3C_CR_ADD_Pos)    |
            p_device->message_type | LL_I3C_GENERATE_STOP);

  do
  {
    /* Initiate a start condition by writing in the CR register */
    LL_I3C_WRITE_REG(p_i3cx, CR, CR_tmp);

    exit_condition = (LL_I3C_READ_REG(p_i3cx, EVR) & (I3C_EVR_FCF | I3C_EVR_ERRF));

    tickstart = HAL_GetTick();

    while (exit_condition == 0U)
    {
      if (timeout_ms != HAL_MAX_DELAY)
      {
        if (((HAL_GetTick() - tickstart) > timeout_ms) || (timeout_ms == 0U))
        {
          hal_status = HAL_TIMEOUT;

          break;
        }
      }
      exit_condition = (LL_I3C_READ_REG(p_i3cx, EVR) & (I3C_EVR_FCF | I3C_EVR_ERRF));
    }

    if (hal_status == HAL_OK)
    {
      if (LL_I3C_IsActiveFlag_FC(p_i3cx) != 0U)
      {
        LL_I3C_ClearFlag_FC(p_i3cx);
        /* Device is ready */
        break;
      }
      else
      {
        LL_I3C_ClearFlag_ERR(p_i3cx);
      }
    }

    I3C_Trials++;

  } while ((I3C_Trials < trials) && (hal_status == HAL_OK));

  /* Device is not ready */
  if (trials == I3C_Trials)
  {
#if defined(USE_HAL_I3C_GET_LAST_ERRORS) && (USE_HAL_I3C_GET_LAST_ERRORS == 1)
    hi3c->last_error_codes |= HAL_I3C_ERROR_ADDRESS_NACK;
#endif /* USE_HAL_I3C_GET_LAST_ERRORS */
    hal_status = HAL_ERROR;
  }

  I3C_StateIdle(hi3c);

  if (arbitration_previous_state != 0U)
  {
    LL_I3C_EnableArbitrationHeader(p_i3cx);
  }

  return hal_status;
}

/**
  * @brief  I3C error treatment.
  * @param  hi3c  Pointer to a hal_i3c_handle_t
  */
static void I3C_ErrorTreatment(hal_i3c_handle_t *hi3c)
{
#if defined(USE_HAL_I3C_DMA) && (USE_HAL_I3C_DMA == 1)
  uint32_t dma_abort_ctrl = 0UL;
  uint32_t dma_abort_rx = 0UL;
  uint32_t dma_abort_tx = 0UL;
  uint32_t dma_abort_it = 0UL;
#endif /* USE_HAL_I3C_DMA */
  I3C_TypeDef *p_i3cx = I3C_GET_INSTANCE(hi3c);

  if (hi3c->global_state == HAL_I3C_STATE_TGT_REQ)
  {
    I3C_StateIdle(hi3c);
    LL_I3C_DisableIT(p_i3cx, (I3C_TGT_IBI_IT | I3C_TGT_HOTJOIN_IT | I3C_TGT_CTRLROLE_IT));
  }
  else
  {
    LL_I3C_DisableIT(p_i3cx, I3C_CTRL_RX_IT | I3C_CTRL_TX_IT);
    hi3c->tx_count = 0UL;
    hi3c->rx_count = 0UL;
    hi3c->ctrl_count = 0UL;
    hi3c->p_tx_func = NULL;
    hi3c->p_rx_func = NULL;

    /* Flush all FIFOs */
    LL_I3C_RequestTxFIFOFlush(p_i3cx);
    LL_I3C_RequestRxFIFOFlush(p_i3cx);

    /* Control and status FIFOs available only with controller mode */
    if (hi3c->mode == HAL_I3C_MODE_CTRL)
    {
      LL_I3C_RequestControlFIFOFlush(p_i3cx);
      LL_I3C_RequestStatusFIFOFlush(p_i3cx);
    }

#if defined(USE_HAL_I3C_DMA) && (USE_HAL_I3C_DMA == 1)
    /* Prepare abort DMA transfer if any */
    if (hi3c->hdma_ctrl != NULL)
    {
      LL_I3C_DisableDMAReq_Control(p_i3cx);

      if (HAL_DMA_GetState(hi3c->hdma_ctrl) != HAL_DMA_STATE_IDLE)
      {
        hi3c->hdma_ctrl->p_xfer_abort_cb = I3C_DMAAbort;
        dma_abort_ctrl = 1U;
      }
    }

    if (hi3c->hdma_rx != NULL)
    {
      LL_I3C_DisableDMAReq_RX(p_i3cx);

      if (HAL_DMA_GetState(hi3c->hdma_rx) != HAL_DMA_STATE_IDLE)
      {
        hi3c->hdma_rx->p_xfer_abort_cb = I3C_DMAAbort;
        dma_abort_rx = 1U;
      }
    }

    if (hi3c->hdma_tx != NULL)
    {
      LL_I3C_DisableDMAReq_TX(p_i3cx);

      if (HAL_DMA_GetState(hi3c->hdma_tx) != HAL_DMA_STATE_IDLE)
      {
        hi3c->hdma_tx->p_xfer_abort_cb = I3C_DMAAbort;
        dma_abort_tx = 1U;
      }
    }

    /* Abort control DMA transfer if any */
    if (dma_abort_ctrl != 0U)
    {
      dma_abort_it++;
      if (HAL_DMA_Abort_IT(hi3c->hdma_ctrl) != HAL_OK)
      {
        /* Call Directly XferAbortCallback function in case of error */
        hi3c->hdma_ctrl->p_xfer_abort_cb(hi3c->hdma_ctrl);
      }
    }

    if (dma_abort_rx != 0U)
    {
      dma_abort_it++;
      if (HAL_DMA_Abort_IT(hi3c->hdma_rx) != HAL_OK)
      {
        /* Call Directly XferAbortCallback function in case of error */
        hi3c->hdma_rx->p_xfer_abort_cb(hi3c->hdma_rx);
      }
    }

    if (dma_abort_tx != 0U)
    {
      dma_abort_it++;
      if (HAL_DMA_Abort_IT(hi3c->hdma_tx) != HAL_OK)
      {
        /* Call Directly XferAbortCallback function in case of error */
        hi3c->hdma_tx->p_xfer_abort_cb(hi3c->hdma_tx);
      }
    }

    if (dma_abort_it == 0U)
    {
      I3C_TreatErrorCallback(hi3c);
    }
#else /* USE_HAL_I3C_DMA */
    I3C_TreatErrorCallback(hi3c);
#endif /* USE_HAL_I3C_DMA */
  }
}

/**
  * @brief  I3C Error callback treatment.
  * @param  hi3c  Pointer to a hal_i3c_handle_t
  */
static void I3C_TreatErrorCallback(hal_i3c_handle_t *hi3c)
{
  if (hi3c->global_state == HAL_I3C_STATE_ABORT)
  {
    I3C_StateIdle(hi3c);

#if (USE_HAL_I3C_REGISTER_CALLBACKS) && (USE_HAL_I3C_REGISTER_CALLBACKS == 1)
    hi3c->p_abort_cplt_cb(hi3c);
#else
    HAL_I3C_AbortCpltCallback(hi3c);
#endif /* USE_HAL_I3C_REGISTER_CALLBACKS */
  }
  else
  {
    I3C_StateIdle(hi3c);

#if (USE_HAL_I3C_REGISTER_CALLBACKS) && (USE_HAL_I3C_REGISTER_CALLBACKS == 1)
    hi3c->p_error_cb(hi3c);
#else
    HAL_I3C_ErrorCallback(hi3c);
#endif /* USE_HAL_I3C_REGISTER_CALLBACKS */
  }
}

/**
  * @}
  */

#endif /* HAL_I3C_MODULE_ENABLED */

/**
  * @}
  */

/**
  * @}
  */
