/**
  ******************************************************************************
  * @file    stm32h7pxx_hal_i2s.c
  * @author  MCD Application Team
  * @brief   I2S HAL module driver.
  *          This file provides firmware functions to manage the following
  *          functionalities of the Integrated Interchip Sound (I2S) peripheral:
  *           + Initialization and de-initialization functions
  *           + IO operation functions
  *           + Peripheral Control functions
  *           + Peripheral State functions.
  *
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024-2025 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "stm32_hal.h"

/** @addtogroup STM32H7Pxx_HAL_Driver
  * @{
  */

/** @addtogroup I2S
  * @{
# How to use the I2S HAL module driver

1. Declare a hal_i2s_handle_t handle structure and initialize the I2Sx driver with a SPI HW instance
   by calling HAL_I2S_Init().
    Note: Enable the I2S interface clock if you have set USE_HAL_I2S_CLK_ENABLE_MODEL to HAL_CLK_ENABLE_PERIPH_ONLY
          or HAL_CLK_ENABLE_PERIPH_PWR_SYSTEM (in those cases HAL_I2S_Init() will enable the clock).

2. Configure the low level hardware (GPIO, CLOCK, NVIC, etc.):
      - Enable I2Sx interface clock
      - I2Sx pins configuration:
        - Enable the clock for the I2Sx GPIOs
        - Configure these I2S pins as alternate function pull-up
      - NVIC configuration if you need to use interrupt process:
        - Configure the I2Sx interrupt priority
        - Enable the NVIC I2Sx IRQ handle
      - DMA configuration if you need to use DMA process:
        - Declare a hal_dma_handle_t handle structure for the transmit or receive Stream/Channel
        - Enable the DMAx clock
        - Configure the DMA handle parameters
        - Configure the DMA Tx or Rx Stream/Channel
        - Associate the initialized hdma_tx handle to the hi2s DMA Tx or Rx handle
        - For each DMA channel (Tx and Rx), configure the corresponding NVIC line priorirty and enable Tx
                    or Rx Stream/Channel

3. Set the generic configuration of the I2S with HAL_I2S_SetConfig() to chose:
      - The mode
      - The standard
      - The data format
      - The audio frequency
      - The clock polarity
      - The bit order

4. For advanced configuration, use the following function:
      - HAL_I2S_EnableMclkOutput() to enable the Master Clock Output feature
      - HAL_I2S_EnableWSInversion() to enable the Word Select Inversion feature
      - HAL_I2S_EnableMasterKeepIOState() to enable the Master Keep IO State feature
      - HAL_I2S_EnableIOSwap() to enable the IO Swap feature
      - HAL_I2S_EnableChannelDetectionErr() to enable the Channel Length Detection error feature
      - HAL_I2S_LockIOConfig() to enable the Lock of IO configuration feature

5. Callback registration:
The compilation flag USE_HAL_I2S_REGISTER_CALLBACKS allows the user to configure dynamically the driver callbacks.
Use following functions to register an interrupt callback.
      - Function HAL_I2S_RegisterErrorCallback() allows to register I2S Error callback.
      - Function HAL_I2S_RegisterTxCpltCallback() allows to register I2S Tx Completed callback.
      - Function HAL_I2S_RegisterRxCpltCallback() allows to register I2S Rx Completed callback.
      - Function HAL_I2S_RegisterTxRxCpltCallback() allows to register I2S TxRx Completed callback.
      - Function HAL_I2S_RegisterTxHalfCpltCallback() allows to register I2S Tx Half Completed callback.
      - Function HAL_I2S_RegisterRxHalfCpltCallback() allows to register I2S Rx Half Completed callback.
      - Function HAL_I2S_RegisterTxRxCpltCallback() allows to register I2S TxRx Completed callback.
      - Function HAL_I2S_RegisterTxRxHalfCpltCallback() allows to register I2S Tx/Rx Half Completed callback.
      - Function HAL_I2S_RegisterAbortCpltCallback() allows to register I2S Abort Completed callback.
These functions take as parameters the HAL peripheral handle and a pointer to the user callback function

By default, after the HAL_I2S_Init() and when the state is HAL_I2S_STATE_INIT all callbacks are set to the
corresponding weak functions.
Callbacks can be registered in HAL_I2S_STATE_IDLE state only.
When the compilation define USE_HAL_I2S_REGISTER_CALLBACKS is set to 0 or not defined, the callback registering
feature is not available and weak (surcharged) callbacks are used.

6. Configuration inside the I2S driver
Config defines                 | Where            | Default value     | Note
------------------------------ | -----------------| ------------------| -------------------------------------------
USE_HAL_I2S_MODULE             | hal_conf.h       |         1U        | Enable the HAL I2S module.
USE_HAL_I2S_DMA                | hal_conf.h       |         1U        | Enable the use of DMA in the HAL driver
USE_HAL_I2S_GET_LAST_ERRORS    | hal_conf.h       |         1U        | Enable retrieving last processes error codes
USE_HAL_I2S_OVR_UDR_ERRORS     | hal_conf.h       |         1U        | Enable retrieving overrun and underrun error
USE_HAL_I2S_REGISTER_CALLBACKS | hal_conf.h       |         0U        | Enable the register callbacks assert
USE_HAL_I2S_USER_DATA          | hal_conf.h       |         0U        | Add an user data inside HAL I2S handle
USE_HAL_I2S_CLK_ENABLE_MODEL   | hal_conf.h       | HAL_CLK_ENABLE_NO | Enable peripheral clock inside the HAL_I2S_Init
USE_HAL_CHECK_PARAM            | hal_conf.h       |         0U        | Enable checking of vital parameters at runtime
USE_HAL_MUTEX                  | hal_conf.h       |         0U        | Enable the use of semaphore in the HAL driver
USE_ASSERT_DBG_PARAM           | PreProcessor env |         NA        | Enable the params assert
USE_ASSERT_DBG_STATE           | PreProcessor env |         NA        | Enable the state assert
 */

#if defined(USE_HAL_I2S_MODULE) && (USE_HAL_I2S_MODULE == 1U)
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/** @defgroup I2S_Private_Constants I2S Private Constants
  * @{
  */

#define I2S_DEFAULT_TIMEOUT  0xFFFFUL  /*!< Timeout default value */
#define I2S_FIFO_SIZE        8UL       /*!< Standard size 8-Bytes */

/* Private macro -------------------------------------------------------------*/
/** @defgroup I2S_Private_Macros I2S Private Macros
  * @{
  */

/**
  * @brief Check if the mode is type of hal_i2s_mode_t.
  */
#define IS_I2S_MODE(mode) (((mode) == HAL_I2S_MODE_SLAVE_TX)             \
                           || ((mode) == HAL_I2S_MODE_SLAVE_RX)          \
                           || ((mode) == HAL_I2S_MODE_MASTER_TX)         \
                           || ((mode) == HAL_I2S_MODE_MASTER_RX)         \
                           || ((mode) == HAL_I2S_MODE_SLAVE_FULL_DUPLEX) \
                           || ((mode) == HAL_I2S_MODE_MASTER_FULL_DUPLEX))

/**
  * @brief Check if the mode is Full Duplex mode.
  */
#define IS_I2S_MODE_FULL_DUPLEX(mode) (((mode) == HAL_I2S_MODE_SLAVE_FULL_DUPLEX) \
                                       || ((mode) == HAL_I2S_MODE_MASTER_FULL_DUPLEX))

/**
  * @brief Check if the mode is Master mode.
  */
#define IS_I2S_MODE_MASTER(mode) (((mode) == HAL_I2S_MODE_MASTER_TX)    \
                                  || ((mode) == HAL_I2S_MODE_MASTER_RX) \
                                  || ((mode) == HAL_I2S_MODE_MASTER_FULL_DUPLEX))

/**
  * @brief Check if the mode is Tx direction mode.
  */
#define IS_I2S_MODE_TX(mode) (((mode) == HAL_I2S_MODE_SLAVE_TX) \
                              || ((mode) == HAL_I2S_MODE_MASTER_TX))

/**
  * @brief Check if the mode is Rx direction mode.
  */
#define IS_I2S_MODE_RX(mode) (((mode) == HAL_I2S_MODE_SLAVE_RX) \
                              || ((mode) == HAL_I2S_MODE_MASTER_RX))

/**
  * @brief Check if the standard is type of hal_i2s_standard_t.
  */
#define IS_I2S_STANDARD(standard) (((standard) == HAL_I2S_STANDARD_PHILIPS)      \
                                   || ((standard) == HAL_I2S_STANDARD_MSB)       \
                                   || ((standard) == HAL_I2S_STANDARD_LSB)       \
                                   || ((standard) == HAL_I2S_STANDARD_PCM_SHORT) \
                                   || ((standard) == HAL_I2S_STANDARD_PCM_LONG))

/**
  * @brief Check if the data format is type of hal_i2s_data_format_t.
  */
#define IS_I2S_DATA_FORMAT(data_format) (((data_format) == HAL_I2S_DATA_FORMAT_16_BIT)             \
                                         || ((data_format) == HAL_I2S_DATA_FORMAT_16_BIT_EXTENDED) \
                                         || ((data_format) == HAL_I2S_DATA_FORMAT_24_BIT)          \
                                         || ((data_format) == HAL_I2S_DATA_FORMAT_32_BIT))

/**
  * @brief Check if the audio frequency is type of hal_i2s_audio_frequency_t.
  */
#define IS_I2S_AUDIO_FREQUENCY(audio_frequency) (((audio_frequency) == HAL_I2S_AUDIO_FREQ_192_KHZ)   \
                                                 || ((audio_frequency) == HAL_I2S_AUDIO_FREQ_96_KHZ) \
                                                 || ((audio_frequency) == HAL_I2S_AUDIO_FREQ_48_KHZ) \
                                                 || ((audio_frequency) == HAL_I2S_AUDIO_FREQ_44_KHZ) \
                                                 || ((audio_frequency) == HAL_I2S_AUDIO_FREQ_32_KHZ) \
                                                 || ((audio_frequency) == HAL_I2S_AUDIO_FREQ_22_KHZ) \
                                                 || ((audio_frequency) == HAL_I2S_AUDIO_FREQ_16_KHZ) \
                                                 || ((audio_frequency) == HAL_I2S_AUDIO_FREQ_11_KHZ) \
                                                 || ((audio_frequency) == HAL_I2S_AUDIO_FREQ_8_KHZ)  \
                                                 || ((audio_frequency) == HAL_I2S_AUDIO_FREQ_DEFAULT))

/**
  * @brief Check if the audio frequency is type of hal_i2s_clock_polarity_t.
  */
#define IS_I2S_CLOCK_POLARITY(clock_polarity) (((clock_polarity) == HAL_I2S_CLOCK_POLARITY_LOW) \
                                               || ((clock_polarity) == HAL_I2S_CLOCK_POLARITY_HIGH))

/**
  * @brief Check if the audio frequency is type of hal_i2s_bit_order_t.
  */
#define IS_I2S_BIT_ORDER(bit_order) (((bit_order) == HAL_I2S_MSB_FIRST) \
                                     || ((bit_order) == HAL_I2S_LSB_FIRST))

/**
  * @brief Check if the audio frequency is type of hal_i2s_fifo_threshold_t.
  */
#define IS_I2S_FIFO_THRESHOLD(fifo_threshold) (((fifo_threshold) == HAL_I2S_FIFO_THRESHOLD_1_DATA)    \
                                               || ((fifo_threshold) == HAL_I2S_FIFO_THRESHOLD_2_DATA) \
                                               || ((fifo_threshold) == HAL_I2S_FIFO_THRESHOLD_3_DATA) \
                                               || ((fifo_threshold) == HAL_I2S_FIFO_THRESHOLD_4_DATA) \
                                               || ((fifo_threshold) == HAL_I2S_FIFO_THRESHOLD_5_DATA) \
                                               || ((fifo_threshold) == HAL_I2S_FIFO_THRESHOLD_6_DATA) \
                                               || ((fifo_threshold) == HAL_I2S_FIFO_THRESHOLD_7_DATA) \
                                               || ((fifo_threshold) == HAL_I2S_FIFO_THRESHOLD_8_DATA))

/**
  * @brief Check if the master clock output state is type of hal_i2s_mclk_output_status_t.
  */
#define IS_I2S_MCLK_OUTPUT(state) (((state) == HAL_I2S_MCLK_OUTPUT_DISABLED) \
                                   || ((state) == HAL_I2S_MCLK_OUTPUT_ENABLED))

/**
  * @brief Check if the word select inversion state is type of hal_i2s_ws_inversion_status_t.
  */
#define IS_I2S_WS_INVERSION(state) (((state) == HAL_I2S_WS_INVERSION_DISABLED) \
                                    || ((state) == HAL_I2S_WS_INVERSION_ENABLED))

/**
  * @brief Check if the master keep IO state is type of hal_i2s_master_keep_io_state_status_t.
  */
#define IS_I2S_MASTER_KEEP_IO_STATE(state) (((state) == HAL_I2S_MASTER_KEEP_IO_STATE_DISABLED) \
                                            || ((state) == HAL_I2S_MASTER_KEEP_IO_STATE_ENABLED))

/**
  * @brief Check if the swap IO state is type of hal_i2s_io_swap_status_t.
  */
#define IS_I2S_IO_SWAP(state) (((state) == HAL_I2S_IO_SWAP_DISABLED) \
                               || ((state) == HAL_I2S_IO_SWAP_ENABLED))


/**
  * @brief Check if the slave channel length detector state is type of hal_i2s_channel_detection_err_status_t.
  */
#define IS_I2S_CHANNEL_DETECTION_ERR(state) (((state) == HAL_I2S_CHANNEL_DETECTION_ERR_DISABLED) \
                                             || ((state) == HAL_I2S_CHANNEL_DETECTION_ERR_ENABLED))

/**
  * @brief Check if the IO configuration feature state is type of hal_i2s_io_cfg_status_t.
  */
#define IS_I2S_IO_CFG(state) (((state) == HAL_I2S_IO_CFG_UNLOCKED) \
                              || ((state) == HAL_I2S_IO_CFG_LOCKED))

/**
  * @brief Retrieve I2S instance from handle.
  * @param handle specifies the I2S handle
  */
#define I2S_GET_INSTANCE(handle) ((SPI_TypeDef*)((uint32_t)(handle)->instance))

/**
  * @}
  */
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/** @defgroup I2S_Private_Functions I2S Private Functions
  * @{
  */
#if defined(USE_HAL_I2S_DMA) && (USE_HAL_I2S_DMA == 1U)
static void          I2S_DMATxCplt(hal_dma_handle_t *hdma);
static void          I2S_DMATxHalfCplt(hal_dma_handle_t *hdma);
static void          I2S_DMARxCplt(hal_dma_handle_t *hdma);
static void          I2S_DMARxHalfCplt(hal_dma_handle_t *hdma);
static void          I2S_DMATxRxCplt(hal_dma_handle_t *hdma);
static void          I2S_DMATxRxHalfCplt(hal_dma_handle_t *hdma);
static void          I2S_DMAError(hal_dma_handle_t *hdma);
static void          I2S_DMATxAbortCallback(hal_dma_handle_t *hdma);
static void          I2S_DMARxAbortCallback(hal_dma_handle_t *hdma);
#endif /* USE_HAL_I2S_DMA */
static void          I2S_Transmit_16Bit_IT(hal_i2s_handle_t *hi2s);
static void          I2S_Transmit_32Bit_IT(hal_i2s_handle_t *hi2s);
static void          I2S_Receive_16Bit_IT(hal_i2s_handle_t *hi2s);
static void          I2S_Receive_32Bit_IT(hal_i2s_handle_t *hi2s);
static void          I2S_AbortTransfer(hal_i2s_handle_t *hi2s);
static hal_status_t  I2S_WaitOnFlagUntilTimeout(hal_i2s_handle_t *hi2s, uint32_t flag, uint32_t status,
                                                uint32_t tick_start, uint32_t timeout_ms);
static hal_status_t  I2S_CloseTransfer(hal_i2s_handle_t *hi2s);
/**
  * @}
  */

/* Exported functions ---------------------------------------------------------*/

/** @defgroup I2S_Exported_Functions I2S Exported Functions
  * @{
  */

/** @defgroup  I2S_Exported_Functions_Group1 Initialization and de-initialization functions
  *  @brief    Initialization and Configuration functions
  *
@verbatim
 ===============================================================================
              ##### Initialization and de-initialization functions #####
 ===============================================================================
    [..]  This subsection provides a set of functions allowing to initialize and
          de-initialize the I2Sx peripheral in simplex mode:

      (+) User must Implement HAL_I2S_MspInit() function in which he configures
          all related peripherals resources (CLOCK, GPIO, DMA, IT and NVIC ).

      (+) Call the function HAL_I2S_Init() to configure the selected device with
          the selected configuration:
        (++) Mode
        (++) Standard
        (++) Data Format
        (++) MCLK Output
        (++) Audio frequency
        (++) Polarity

     (+) Call the function HAL_I2S_DeInit() to restore the default configuration
          of the selected I2Sx peripheral.
  @endverbatim
  * @{
  */

/**
  * @brief  Initialize the SPI according to the associated handle.
  * @param  hi2s Pointer to a @ref hal_i2s_handle_t structure that contains
  *              the configuration information for I2S module.
  * @param  instance I2S instance.
  * @retval HAL_INVALID_PARAM When the handle is NULL.
  * @retval HAL_ERROR When the MUTEX cannot be created.
  * @retval HAL_OK HAL I2S driver correctly initialized for the given SPI instance.
  */
hal_status_t HAL_I2S_Init(hal_i2s_handle_t *hi2s, hal_i2s_t instance)
{
  /* Check parameters*/
  ASSERT_DBG_PARAM((hi2s != NULL));
  ASSERT_DBG_PARAM(IS_I2S_ALL_INSTANCE((SPI_TypeDef *)((uint32_t)instance)));

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1U)
  /* Check the handle struct pointer */
  if (hi2s == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  hi2s->instance = instance;

#if defined(USE_HAL_I2S_REGISTER_CALLBACKS) && (USE_HAL_I2S_REGISTER_CALLBACKS == 1U)
  /* Init the I2S callback settings */
  hi2s->p_error_cb           = HAL_I2S_ErrorCallback;
  hi2s->p_tx_cplt_cb         = HAL_I2S_TxCpltCallback;
  hi2s->p_tx_half_cplt_cb    = HAL_I2S_TxHalfCpltCallback;
  hi2s->p_rx_cplt_cb         = HAL_I2S_RxCpltCallback;
  hi2s->p_rx_half_cplt_cb    = HAL_I2S_RxHalfCpltCallback;
  hi2s->p_tx_rx_cplt_cb      = HAL_I2S_TxRxCpltCallback;
  hi2s->p_tx_rx_half_cplt_cb = HAL_I2S_TxRxHalfCpltCallback;
  hi2s->p_abort_cplt_cb      = HAL_I2S_AbortCpltCallback;
#endif  /* USE_HAL_I2S_REGISTER_CALLBACKS */

  /* Other internal fields */
  hi2s->previous_state = (hal_i2s_state_t) 0U;
  hi2s->p_tx_buff      = (uint16_t *) NULL;
  hi2s->tx_xfer_size   = (uint16_t) 0U;
  hi2s->tx_xfer_count  = (uint16_t) 0U;
  hi2s->p_rx_buff      = (uint16_t *) NULL;
  hi2s->rx_xfer_size   = (uint16_t) 0U;
  hi2s->rx_xfer_count  = (uint16_t) 0U;

#if defined (USE_HAL_I2S_DMA) && (USE_HAL_I2S_DMA == 1U)
  hi2s->hdma_tx        = (hal_dma_handle_t *) NULL;
  hi2s->hdma_rx        = (hal_dma_handle_t *) NULL;
#endif /* USE_HAL_I2S_DMA  */

#if defined(USE_HAL_I2S_USER_DATA) && (USE_HAL_I2S_USER_DATA == 1U)
  /*Init the userdata pointer to NULL*/
  hi2s->p_user_data    = NULL;
#endif /* USE_HAL_SPI_USER_DATA */

#if defined (USE_HAL_I2S_GET_LAST_ERRORS) && (USE_HAL_I2S_GET_LAST_ERRORS == 1U)
  /* Reset the last_error_codes variable storing the last errors */
  hi2s->last_error_codes = HAL_I2S_ERROR_NONE;
#endif /* USE_HAL_I2S_GET_LAST_ERRORS */

#if defined(USE_HAL_I2S_CLK_ENABLE_MODEL) && (USE_HAL_I2S_CLK_ENABLE_MODEL > HAL_CLK_ENABLE_NO)
  /* Enable the I2S Peripheral Clock */
  switch (hi2s->instance)
  {
#if defined(SPI1)
    case HAL_I2S1:
      HAL_RCC_SPI1_EnableClock();
      break;
#endif /* SPI1 */
#if defined(SPI2)
    case HAL_I2S2:
      HAL_RCC_SPI2_EnableClock();
      break;
#endif /* SPI2 */
#if defined(SPI3)
    case HAL_I2S3:
      HAL_RCC_SPI3_EnableClock();
      break;
#endif /* SPI3 */
    default:
      break;
  }
#endif /* USE_HAL_I2S_CLK_ENABLE_MODEL */

#if defined(USE_HAL_MUTEX) && (USE_HAL_MUTEX == 1U)
  /* Create the I2S semaphore */
  if (HAL_OS_SemaphoreCreate(&hi2s->semaphore) != HAL_OS_OK)
  {
    return HAL_ERROR;
  }
#endif /* USE_HAL_MUTEX */

  /* Init the global state */
  hi2s->global_state = HAL_I2S_STATE_INIT;

  return HAL_OK;
}

/**
  * @brief  DeInitialize the I2S driver for the given handle.
  * @param  hi2s pointer to a @ref hal_i2s_handle_t structure that contains
  *         the configuration information for I2S module
  */
void HAL_I2S_DeInit(hal_i2s_handle_t *hi2s)
{
  /* Check the I2S handle allocation */
  ASSERT_DBG_PARAM(hi2s != NULL);

  /* Check the state */
  ASSERT_DBG_STATE(hi2s->global_state, ((uint32_t)HAL_I2S_STATE_IDLE)         \
                   | ((uint32_t)HAL_I2S_STATE_TX_ACTIVE)    \
                   | ((uint32_t)HAL_I2S_STATE_RX_ACTIVE)    \
                   | ((uint32_t)HAL_I2S_STATE_TX_RX_ACTIVE) \
                   | ((uint32_t)HAL_I2S_STATE_PAUSED)       \
                   | ((uint32_t)HAL_I2S_STATE_ABORT)
                   | HAL_I2S_STATE_INIT);

  /* Disable I2S peripheral */
  LL_I2S_DisableI2SMode(I2S_GET_INSTANCE(hi2s));
  LL_I2S_Disable(I2S_GET_INSTANCE(hi2s));

  /* Reset all data */
#if defined(USE_HAL_I2S_REGISTER_CALLBACKS) && (USE_HAL_I2S_REGISTER_CALLBACKS == 1U)
  /* Init the I2S callback settings */
  hi2s->p_error_cb           = HAL_I2S_ErrorCallback;
  hi2s->p_tx_cplt_cb         = HAL_I2S_TxCpltCallback;
  hi2s->p_tx_half_cplt_cb    = HAL_I2S_TxHalfCpltCallback;
  hi2s->p_rx_cplt_cb         = HAL_I2S_RxCpltCallback;
  hi2s->p_rx_half_cplt_cb    = HAL_I2S_RxHalfCpltCallback;
  hi2s->p_tx_rx_cplt_cb      = HAL_I2S_TxRxCpltCallback;
  hi2s->p_tx_rx_half_cplt_cb = HAL_I2S_TxRxHalfCpltCallback;
  hi2s->p_abort_cplt_cb      = HAL_I2S_AbortCpltCallback;
#endif  /* USE_HAL_I2S_REGISTER_CALLBACKS */

  /* Other internal fields */
  hi2s->previous_state = (hal_i2s_state_t) 0U;
  hi2s->p_tx_buff      = (uint16_t *) NULL;
  hi2s->tx_xfer_size   = (uint16_t) 0U;
  hi2s->tx_xfer_count  = (uint16_t) 0U;
  hi2s->p_rx_buff      = (uint16_t *) NULL;
  hi2s->rx_xfer_size   = (uint16_t) 0U;
  hi2s->rx_xfer_count  = (uint16_t) 0U;

#if defined (USE_HAL_I2S_DMA) && (USE_HAL_I2S_DMA == 1U)
  hi2s->hdma_tx        = (hal_dma_handle_t *) NULL;
  hi2s->hdma_rx        = (hal_dma_handle_t *) NULL;
#endif /* USE_HAL_I2S_DMA  */

#if defined (USE_HAL_I2S_GET_LAST_ERRORS) && (USE_HAL_I2S_GET_LAST_ERRORS == 1U)
  /* Reset the last_error_codes variable storing the last errors */
  hi2s->last_error_codes = HAL_I2S_ERROR_NONE;
#endif /* USE_HAL_I2S_GET_LAST_ERRORS */

#if defined(USE_HAL_MUTEX) && (USE_HAL_MUTEX == 1U)
  /* Delete the I2S semaphore */
  (void)HAL_OS_SemaphoreDelete(&hi2s->semaphore);
#endif /* USE_HAL_MUTEX */

  /* Reset the global state */
  hi2s->global_state = HAL_I2S_STATE_RESET;
}

/**
  * @}
  */

/** @addtogroup I2S_Exported_Functions_Group2 Configuration functions
  * @{
  This subsection provides a set of functions allowing to configure the I2Sx peripheral:
    - Call the function HAL_I2S_SetConfig() to configure the selected device with the selected configuration:
      - Mode
      - Standard
      - Data format
      - Audio frequency selected
      - Clock polarity
      - Bit order
    - Call the function HAL_I2S_GetConfig() to retrieve the current global configuration set by the user.
  */

/**
  * @brief  Set the configuration to the I2S peripheral.
  * @param  hi2s Pointer to a @ref hal_i2s_handle_t structure that contains
  *              the configuration information for I2S module.
  * @param  p_config Pointer to hal_i2s_config_t configuration structure.
  * @retval HAL_INVALID_PARAM Invalid parameters.
  * @retval HAL_ERROR When io locked.
  * @retval HAL_OK I2S instance has been correctly configured.
  */
hal_status_t HAL_I2S_SetConfig(hal_i2s_handle_t *hi2s, const hal_i2s_config_t *p_config)
{
  /* Check parameters allocation */
  ASSERT_DBG_PARAM(hi2s != NULL);
  ASSERT_DBG_PARAM(p_config != NULL);
  ASSERT_DBG_PARAM(IS_I2S_MODE(p_config->mode));
  ASSERT_DBG_PARAM(IS_I2S_STANDARD(p_config->standard));
  ASSERT_DBG_PARAM(IS_I2S_DATA_FORMAT(p_config->data_format));
  ASSERT_DBG_PARAM(IS_I2S_AUDIO_FREQUENCY(p_config->audio_frequency));
  ASSERT_DBG_PARAM(IS_I2S_CLOCK_POLARITY(p_config->clock_polarity));
  ASSERT_DBG_PARAM(IS_I2S_BIT_ORDER(p_config->bit_order));

  /* Check the state */
  ASSERT_DBG_STATE(hi2s->global_state, HAL_I2S_STATE_IDLE | HAL_I2S_STATE_INIT);

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1U)
  /* Check the config struct pointer */
  if (p_config == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  /* Check for IOLock */
  if ((LL_I2S_IsEnabledIOLock(I2S_GET_INSTANCE(hi2s))) == 1U)
  {
#if defined(USE_HAL_I2S_GET_LAST_ERRORS) && (USE_HAL_I2S_GET_LAST_ERRORS == 1U)
    hi2s->last_error_codes = HAL_I2S_ERROR_IO_LOCKED;
#endif /* USE_HAL_I2S_GET_LAST_ERRORS */
    return HAL_ERROR;
  }

  /* Disable I2S if I2S is enabled */
  if (LL_I2S_IsEnabled(I2S_GET_INSTANCE(hi2s)) != 0U)
  {
    LL_I2S_Disable(I2S_GET_INSTANCE(hi2s));
    LL_I2S_ClearFlag(I2S_GET_INSTANCE(hi2s),
                     (LL_I2S_FLAG_UDR | LL_I2S_FLAG_OVR | LL_I2S_FLAG_TIFRE | LL_I2S_FLAG_SUSP));
  }

  /* Enable I2S peripheral */
  LL_I2S_EnableI2SMode(I2S_GET_INSTANCE(hi2s));

  /* Configure the I2Sx transfer mode */
  LL_I2S_SetTransferMode(I2S_GET_INSTANCE(hi2s), (uint32_t)(p_config->mode));

  /* Configure the I2Sx standard */
  LL_I2S_SetStandard(I2S_GET_INSTANCE(hi2s), (uint32_t)(p_config->standard));

  /* Configure the data format */
  LL_I2S_SetDataFormat(I2S_GET_INSTANCE(hi2s), (uint32_t)(p_config->data_format));

  /* Configure the clock polarity */
  LL_I2S_SetClockPolarity(I2S_GET_INSTANCE(hi2s), (uint32_t)(p_config->clock_polarity));

  /* Configure the bit order */
  LL_I2S_SetTransferBitOrder(I2S_GET_INSTANCE(hi2s), (uint32_t)(p_config->bit_order));

  if (IS_I2S_MODE_MASTER(p_config->mode))
  {
    /* Configure the audio frequency */
    if (HAL_I2S_SetAudioFrequency(hi2s, p_config->audio_frequency) != HAL_OK)
    {
      return HAL_ERROR;
    }
  }

  /* Set I2S global state */
  hi2s->global_state = HAL_I2S_STATE_IDLE;

  return HAL_OK;
}

/**
  * @brief Retrieve the configuration to the I2S peripheral.
  * @param hi2s Pointer to a @ref hal_i2s_handle_t structure that contains
  *             the configuration information for I2S module.
  * @param p_config Pointer to hal_i2s_config_t configuration structure.
  */
void HAL_I2S_GetConfig(hal_i2s_handle_t *hi2s, hal_i2s_config_t *p_config)
{
  /* Check parameters allocation */
  ASSERT_DBG_PARAM(hi2s != NULL);
  ASSERT_DBG_PARAM(p_config != NULL);

  /* Check the global state */
  ASSERT_DBG_STATE(hi2s->global_state, (((uint32_t)HAL_I2S_STATE_IDLE)           \
                                        | ((uint32_t)HAL_I2S_STATE_TX_ACTIVE)    \
                                        | ((uint32_t)HAL_I2S_STATE_RX_ACTIVE)    \
                                        | ((uint32_t)HAL_I2S_STATE_TX_RX_ACTIVE) \
                                        | ((uint32_t)HAL_I2S_STATE_PAUSED)       \
                                        | ((uint32_t)HAL_I2S_STATE_ABORT)));

  p_config->mode = (hal_i2s_mode_t)LL_I2S_GetTransferMode(I2S_GET_INSTANCE(hi2s));
  p_config->standard = (hal_i2s_standard_t)LL_I2S_GetStandard(I2S_GET_INSTANCE(hi2s));
  p_config->data_format = (hal_i2s_data_format_t)LL_I2S_GetDataFormat(I2S_GET_INSTANCE(hi2s));
  p_config->clock_polarity = (hal_i2s_clock_polarity_t)LL_I2S_GetClockPolarity(I2S_GET_INSTANCE(hi2s));
  p_config->bit_order = (hal_i2s_bit_order_t)LL_I2S_GetTransferBitOrder(I2S_GET_INSTANCE(hi2s));
  p_config->audio_frequency = (hal_i2s_audio_frequency_t)HAL_I2S_GetAudioFrequency(hi2s);
}

/**
  * @}
  */

/** @addtogroup I2S_Exported_Functions_Group3 Features functions
  * @{
  This subsection provides a set of functions allowing to configure some additional
  features for the selected I2Sx peripheral.

- Master Clock Output general call:
  - HAL_I2S_EnableMclkOutput
  - HAL_I2S_DisableMclkOutput
  - HAL_I2S_IsEnabledMclkOutput

- Word Select Inversion general call:
  - HAL_I2S_EnableWSInversion
  - HAL_I2S_DisableWSInversion
  - HAL_I2S_IsEnabledWSInversion

- Master Keep IO State general call:
  - HAL_I2S_EnableMasterKeepIOState
  - HAL_I2S_DisableMasterKeepIOState
  - HAL_I2S_IsEnabledMasterKeepIOState

- IO Swap general call:
  - HAL_I2S_EnableIOSwap
  - HAL_I2S_DisableIOSwap
  - HAL_I2S_IsEnabledIOSwap

- Channel Length Detection Error general call:
  - HAL_I2S_EnableChannelDetectionErr
  - HAL_I2S_DisableChannelDetectionErr
  - HAL_I2S_IsEnabledChannelDetectionErr

- IO lock configuration:
  - HAL_I2S_LockIOConfig
  - HAL_I2S_IsLockedIOConfig
  */

/**
  * @brief  Enable I2S Master Clock Output.
  * @param  hi2s Pointer to a @ref hal_i2s_handle_t
  * @retval HAL_OK Operation completed successfully
  */
hal_status_t HAL_I2S_EnableMclkOutput(hal_i2s_handle_t *hi2s)
{
  hal_i2s_audio_frequency_t audio_freq;
  hal_status_t status = HAL_OK;

  /* Check the parameters */
  ASSERT_DBG_PARAM(hi2s != NULL);

  /* Check the global state */
  ASSERT_DBG_STATE(hi2s->global_state, (uint32_t)HAL_I2S_STATE_IDLE);

  if (LL_I2S_IsEnabledMasterClock(I2S_GET_INSTANCE(hi2s)) == 0U)
  {
    /* Disable I2S if I2S is enabled */
    if (LL_I2S_IsEnabled(I2S_GET_INSTANCE(hi2s)) != 0U)
    {
      LL_I2S_Disable(I2S_GET_INSTANCE(hi2s));
    }

    audio_freq = HAL_I2S_GetAudioFrequency(hi2s);

    LL_I2S_EnableMasterClock(I2S_GET_INSTANCE(hi2s));

    status = HAL_I2S_SetAudioFrequency(hi2s, audio_freq);
  }

  return status;
}

/**
  * @brief  Disable I2S Master Clock Output.
  * @param  hi2s Pointer to a @ref hal_i2s_handle_t
  * @retval HAL_OK Operation completed successfully
  */
hal_status_t HAL_I2S_DisableMclkOutput(hal_i2s_handle_t *hi2s)
{
  hal_i2s_audio_frequency_t audio_freq;
  hal_status_t status = HAL_OK;

  /* Check the parameters */
  ASSERT_DBG_PARAM(hi2s != NULL);

  /* Check the global state */
  ASSERT_DBG_STATE(hi2s->global_state, (uint32_t)HAL_I2S_STATE_IDLE);

  if (LL_I2S_IsEnabledMasterClock(I2S_GET_INSTANCE(hi2s)) != 0U)
  {
    /* Disable I2S if I2S is enabled */
    if (LL_I2S_IsEnabled(I2S_GET_INSTANCE(hi2s)) != 0U)
    {
      LL_I2S_Disable(I2S_GET_INSTANCE(hi2s));
    }

    audio_freq = HAL_I2S_GetAudioFrequency(hi2s);

    LL_I2S_DisableMasterClock(I2S_GET_INSTANCE(hi2s));

    status = HAL_I2S_SetAudioFrequency(hi2s, audio_freq);
  }

  return status;
}

/**
  * @brief  Check I2S Master Clock Output status.
  * @param  hi2s Pointer to a @ref hal_i2s_handle_t
  * @retval HAL_I2S_MCLK_OUTPUT_ENABLED  Master Clock Output is enabled
  * @retval HAL_I2S_MCLK_OUTPUT_DISABLED Master Clock Output is disabled
  */
hal_i2s_mclk_output_status_t HAL_I2S_IsEnabledMclkOutput(hal_i2s_handle_t *hi2s)
{
  /* Check the parameters */
  ASSERT_DBG_PARAM(hi2s != NULL);

  /* Check the global state */
  ASSERT_DBG_STATE(hi2s->global_state, (((uint32_t)HAL_I2S_STATE_IDLE)           \
                                        | ((uint32_t)HAL_I2S_STATE_TX_ACTIVE)    \
                                        | ((uint32_t)HAL_I2S_STATE_RX_ACTIVE)    \
                                        | ((uint32_t)HAL_I2S_STATE_TX_RX_ACTIVE) \
                                        | ((uint32_t)HAL_I2S_STATE_PAUSED)       \
                                        | ((uint32_t)HAL_I2S_STATE_ABORT)));

  return (hal_i2s_mclk_output_status_t)LL_I2S_IsEnabledMasterClock(I2S_GET_INSTANCE(hi2s));
}

/**
  * @brief  Enable I2S Word Select Inversion.
  * @param  hi2s Pointer to a @ref hal_i2s_handle_t
  * @retval HAL_OK Operation completed successfully
  */
hal_status_t HAL_I2S_EnableWSInversion(hal_i2s_handle_t *hi2s)
{
  /* Check the parameters */
  ASSERT_DBG_PARAM(hi2s != NULL);

  /* Check the global state */
  ASSERT_DBG_STATE(hi2s->global_state, (uint32_t)HAL_I2S_STATE_IDLE);

  /* Disable I2S if I2S is enabled */
  if (LL_I2S_IsEnabled(I2S_GET_INSTANCE(hi2s)) != 0U)
  {
    LL_I2S_Disable(I2S_GET_INSTANCE(hi2s));
  }

  LL_I2S_EnableWordSelectInversion(I2S_GET_INSTANCE(hi2s));

  return HAL_OK;
}

/**
  * @brief  Disable I2S Word Select Inversion.
  * @param  hi2s Pointer to a @ref hal_i2s_handle_t
  * @retval HAL_OK Operation completed successfully
  */
hal_status_t HAL_I2S_DisableWSInversion(hal_i2s_handle_t *hi2s)
{
  /* Check the parameters */
  ASSERT_DBG_PARAM(hi2s != NULL);

  /* Check the global state */
  ASSERT_DBG_STATE(hi2s->global_state, (uint32_t)HAL_I2S_STATE_IDLE);

  /* Disable I2S if I2S is enabled */
  if (LL_I2S_IsEnabled(I2S_GET_INSTANCE(hi2s)) != 0U)
  {
    LL_I2S_Disable(I2S_GET_INSTANCE(hi2s));
  }

  LL_I2S_DisableWordSelectInversion(I2S_GET_INSTANCE(hi2s));

  return HAL_OK;
}

/**
  * @brief  Check I2S Word Select Inversion status.
  * @param  hi2s Pointer to a @ref hal_i2s_handle_t
  * @retval HAL_I2S_WS_INVERSION_ENABLED  Word Select Inversion is enabled
  * @retval HAL_I2S_WS_INVERSION_DISABLED Word Select Inversion is disabled
  */
hal_i2s_ws_inversion_status_t HAL_I2S_IsEnabledWSInversion(hal_i2s_handle_t *hi2s)
{
  /* Check the parameters */
  ASSERT_DBG_PARAM(hi2s != NULL);

  /* Check the global state */
  ASSERT_DBG_STATE(hi2s->global_state, (((uint32_t)HAL_I2S_STATE_IDLE)           \
                                        | ((uint32_t)HAL_I2S_STATE_TX_ACTIVE)    \
                                        | ((uint32_t)HAL_I2S_STATE_RX_ACTIVE)    \
                                        | ((uint32_t)HAL_I2S_STATE_TX_RX_ACTIVE) \
                                        | ((uint32_t)HAL_I2S_STATE_PAUSED)       \
                                        | ((uint32_t)HAL_I2S_STATE_ABORT)));

  return (hal_i2s_ws_inversion_status_t)LL_I2S_IsEnabledWordSelectInversion(I2S_GET_INSTANCE(hi2s));
}

/**
  * @brief  Enable Master Keep IO State.
  * @param  hi2s Pointer to a @ref hal_i2s_handle_t
  * @retval HAL_OK Operation completed successfully
  * @retval HAL_ERROR When IO is locked
  */
hal_status_t HAL_I2S_EnableMasterKeepIOState(hal_i2s_handle_t *hi2s)
{
  hal_i2s_mode_t mode;

  /* Check the parameters */
  ASSERT_DBG_PARAM(hi2s != NULL);

  /* Check the global state */
  ASSERT_DBG_STATE(hi2s->global_state, (uint32_t)HAL_I2S_STATE_IDLE);

  mode = HAL_I2S_GetMode(hi2s);

  if (IS_I2S_MODE_MASTER(mode))
  {
    /* Check for IOLock */
    if (LL_I2S_IsEnabledIOLock(I2S_GET_INSTANCE(hi2s)) == 1U)
    {
#if defined(USE_HAL_I2S_GET_LAST_ERRORS) && (USE_HAL_I2S_GET_LAST_ERRORS == 1U)
      hi2s->last_error_codes = HAL_I2S_ERROR_IO_LOCKED;
#endif /* USE_HAL_I2S_GET_LAST_ERRORS */
      return HAL_ERROR;
    }

    /* Disable I2S if I2S is enabled */
    if (LL_I2S_IsEnabled(I2S_GET_INSTANCE(hi2s)) != 0U)
    {
      LL_I2S_Disable(I2S_GET_INSTANCE(hi2s));
    }

    LL_I2S_EnableGPIOControl(I2S_GET_INSTANCE(hi2s));
  }

  return HAL_OK;
}

/**
  * @brief  Disable Master Keep IO State.
  * @param  hi2s Pointer to a @ref hal_i2s_handle_t
  * @retval HAL_OK Operation completed successfully
  * @retval HAL_ERROR When IO is locked
  */
hal_status_t HAL_I2S_DisableMasterKeepIOState(hal_i2s_handle_t *hi2s)
{
  hal_i2s_mode_t mode;

  /* Check the parameters */
  ASSERT_DBG_PARAM(hi2s != NULL);

  /* Check the global state */
  ASSERT_DBG_STATE(hi2s->global_state, (uint32_t)HAL_I2S_STATE_IDLE);

  mode = HAL_I2S_GetMode(hi2s);

  if (IS_I2S_MODE_MASTER(mode))
  {
    /* Check for IOLock */
    if (LL_I2S_IsEnabledIOLock(I2S_GET_INSTANCE(hi2s)) == 1U)
    {
#if defined(USE_HAL_I2S_GET_LAST_ERRORS) && (USE_HAL_I2S_GET_LAST_ERRORS == 1U)
      hi2s->last_error_codes = HAL_I2S_ERROR_IO_LOCKED;
#endif /* USE_HAL_I2S_GET_LAST_ERRORS */
      return HAL_ERROR;
    }

    /* Disable I2S if I2S is enabled */
    if (LL_I2S_IsEnabled(I2S_GET_INSTANCE(hi2s)) != 0U)
    {
      LL_I2S_Disable(I2S_GET_INSTANCE(hi2s));
    }

    /* Disable the Master Keep IO State */
    LL_I2S_DisableGPIOControl(I2S_GET_INSTANCE(hi2s));
  }

  return HAL_OK;
}

/**
  * @brief  Check I2S Master Keep IO State status.
  * @param  hi2s Pointer to a @ref hal_i2s_handle_t
  * @retval HAL_I2S_MASTER_KEEP_IO_STATE_ENABLED  Master Keep IO State is enabled
  * @retval HAL_I2S_MASTER_KEEP_IO_STATE_DISABLED Master Keep IO State is disabled
  */
hal_i2s_master_keep_io_state_status_t HAL_I2S_IsEnabledMasterKeepIOState(hal_i2s_handle_t *hi2s)
{
  /* Check the parameters */
  ASSERT_DBG_PARAM(hi2s != NULL);

  /* Check the global state */
  ASSERT_DBG_STATE(hi2s->global_state, (((uint32_t)HAL_I2S_STATE_IDLE)           \
                                        | ((uint32_t)HAL_I2S_STATE_TX_ACTIVE)    \
                                        | ((uint32_t)HAL_I2S_STATE_RX_ACTIVE)    \
                                        | ((uint32_t)HAL_I2S_STATE_TX_RX_ACTIVE) \
                                        | ((uint32_t)HAL_I2S_STATE_PAUSED)       \
                                        | ((uint32_t)HAL_I2S_STATE_ABORT)));

  return (hal_i2s_master_keep_io_state_status_t)LL_I2S_IsEnabledGPIOControl(I2S_GET_INSTANCE(hi2s));
}

/**
  * @brief  Enable IO Swap.
  * @param  hi2s Pointer to a @ref hal_i2s_handle_t
  * @retval HAL_OK Operation completed successfully
  * @retval HAL_ERROR When IO is locked
  */
hal_status_t HAL_I2S_EnableIOSwap(hal_i2s_handle_t *hi2s)
{
  /* Check the parameters */
  ASSERT_DBG_PARAM(hi2s != NULL);

  /* Check the global state */
  ASSERT_DBG_STATE(hi2s->global_state, (uint32_t)HAL_I2S_STATE_IDLE);

  /* Check for IOLock */
  if (LL_I2S_IsEnabledIOLock(I2S_GET_INSTANCE(hi2s)) == 1U)
  {
#if defined(USE_HAL_I2S_GET_LAST_ERRORS) && (USE_HAL_I2S_GET_LAST_ERRORS == 1U)
    hi2s->last_error_codes = HAL_I2S_ERROR_IO_LOCKED;
#endif /* USE_HAL_I2S_GET_LAST_ERRORS */
    return HAL_ERROR;
  }

  /* Disable I2S if I2S is enabled */
  if (LL_I2S_IsEnabled(I2S_GET_INSTANCE(hi2s)) != 0U)
  {
    LL_I2S_Disable(I2S_GET_INSTANCE(hi2s));
  }

  /* Enable the IO Swap */
  LL_I2S_EnableIOSwap(I2S_GET_INSTANCE(hi2s));

  return HAL_OK;
}

/**
  * @brief  Disable IO Swap.
  * @param  hi2s Pointer to a @ref hal_i2s_handle_t
  * @retval HAL_OK Operation completed successfully
  * @retval HAL_ERROR When IO is locked
  */
hal_status_t HAL_I2S_DisableIOSwap(hal_i2s_handle_t *hi2s)
{
  /* Check the parameters */
  ASSERT_DBG_PARAM(hi2s != NULL);

  /* Check the global state */
  ASSERT_DBG_STATE(hi2s->global_state, (uint32_t)HAL_I2S_STATE_IDLE);

  /* Check for IOLock */
  if (LL_I2S_IsEnabledIOLock(I2S_GET_INSTANCE(hi2s)) == 1U)
  {
#if defined(USE_HAL_I2S_GET_LAST_ERRORS) && (USE_HAL_I2S_GET_LAST_ERRORS == 1U)
    hi2s->last_error_codes = HAL_I2S_ERROR_IO_LOCKED;
#endif /* USE_HAL_I2S_GET_LAST_ERRORS */
    return HAL_ERROR;
  }

  /* Disable I2S if I2S is enabled */
  if (LL_I2S_IsEnabled(I2S_GET_INSTANCE(hi2s)) != 0U)
  {
    LL_I2S_Disable(I2S_GET_INSTANCE(hi2s));
  }

  /* Disable the IO Swap */
  LL_I2S_DisableIOSwap(I2S_GET_INSTANCE(hi2s));

  return HAL_OK;
}

/**
  * @brief  Check I2S Master Keep IO State status.
  * @param  hi2s Pointer to a @ref hal_i2s_handle_t
  * @retval HAL_I2S_IO_SWAP_ENABLED  IO Swap feature is enabled
  * @retval HAL_I2S_IO_SWAP_DISABLED IO Swap feature is disabled
  */
hal_i2s_io_swap_status_t HAL_I2S_IsEnabledIOSwap(hal_i2s_handle_t *hi2s)
{
  /* Check the parameters */
  ASSERT_DBG_PARAM(hi2s != NULL);

  /* Check the global state */
  ASSERT_DBG_STATE(hi2s->global_state, (((uint32_t)HAL_I2S_STATE_IDLE)           \
                                        | ((uint32_t)HAL_I2S_STATE_TX_ACTIVE)    \
                                        | ((uint32_t)HAL_I2S_STATE_RX_ACTIVE)    \
                                        | ((uint32_t)HAL_I2S_STATE_TX_RX_ACTIVE) \
                                        | ((uint32_t)HAL_I2S_STATE_PAUSED)       \
                                        | ((uint32_t)HAL_I2S_STATE_ABORT)));

  return (hal_i2s_io_swap_status_t)LL_I2S_IsEnabledIOSwap(I2S_GET_INSTANCE(hi2s));
}

/**
  * @brief  Enable Channel Length detection error only in slave mode.
  * @param  hi2s Pointer to a @ref hal_i2s_handle_t
  * @retval HAL_OK Operation completed successfully
  */
hal_status_t HAL_I2S_EnableChannelDetectionErr(hal_i2s_handle_t *hi2s)
{
  /* Check the parameters */
  ASSERT_DBG_PARAM(hi2s != NULL);

  /* Check the global state */
  ASSERT_DBG_STATE(hi2s->global_state, (uint32_t)HAL_I2S_STATE_IDLE);

  /* Disable I2S if I2S is enabled */
  if (LL_I2S_IsEnabled(I2S_GET_INSTANCE(hi2s)) != 0U)
  {
    LL_I2S_Disable(I2S_GET_INSTANCE(hi2s));
  }

  /* Enable the channel length detection error */
  LL_I2S_EnableChannelDetectionErr(I2S_GET_INSTANCE(hi2s));

  return HAL_OK;
}

/**
  * @brief  Disable Channel Length detection error only in slave mode.
  * @param  hi2s Pointer to a @ref hal_i2s_handle_t
  * @retval HAL_OK Operation completed successfully
  */
hal_status_t HAL_I2S_DisableChannelDetectionErr(hal_i2s_handle_t *hi2s)
{
  /* Check the parameters */
  ASSERT_DBG_PARAM(hi2s != NULL);

  /* Check the global state */
  ASSERT_DBG_STATE(hi2s->global_state, (uint32_t)HAL_I2S_STATE_IDLE);

  /* Disable I2S if I2S is enabled */
  if (LL_I2S_IsEnabled(I2S_GET_INSTANCE(hi2s)) != 0U)
  {
    LL_I2S_Disable(I2S_GET_INSTANCE(hi2s));
  }

  /* Disable the channel length detection error */
  LL_I2S_DisableChannelDetectionErr(I2S_GET_INSTANCE(hi2s));

  return HAL_OK;
}

/**
  * @brief  Check I2S Channel Length detection error status only in slave mode.
  * @param  hi2s Pointer to a @ref hal_i2s_handle_t
  * @retval HAL_I2S_CHANNEL_DETECTION_ERR_ENABLED  Channel Length detection error is enabled
  * @retval HAL_I2S_CHANNEL_DETECTION_ERR_DISABLED Channel Length detection error is disabled
  */
hal_i2s_channel_detection_err_status_t HAL_I2S_IsEnabledChannelDetectionErr(hal_i2s_handle_t *hi2s)
{
  /* Check the parameters */
  ASSERT_DBG_PARAM(hi2s != NULL);

  /* Check the global state */
  ASSERT_DBG_STATE(hi2s->global_state, (((uint32_t)HAL_I2S_STATE_IDLE)           \
                                        | ((uint32_t)HAL_I2S_STATE_TX_ACTIVE)    \
                                        | ((uint32_t)HAL_I2S_STATE_RX_ACTIVE)    \
                                        | ((uint32_t)HAL_I2S_STATE_TX_RX_ACTIVE) \
                                        | ((uint32_t)HAL_I2S_STATE_PAUSED)       \
                                        | ((uint32_t)HAL_I2S_STATE_ABORT)));

  return (hal_i2s_channel_detection_err_status_t)LL_I2S_IsEnabledChannelDetectionErr(I2S_GET_INSTANCE(hi2s));
}

/**
  * @brief Lock the IO configuration for the dedicated I2S.
  * @param hi2s Pointer to a @ref hal_i2s_handle_t structure that contains
  *             the configuration information for I2S module.
  * @note   The reset of the IOLock bit is done by hardware.
  * @retval HAL_OK Operation completed successfully.
  */
hal_status_t HAL_I2S_LockIOConfig(hal_i2s_handle_t *hi2s)
{
  /* Check parameters allocation */
  ASSERT_DBG_PARAM(hi2s != NULL);

  /* Check the I2S channel state */
  ASSERT_DBG_STATE(hi2s->global_state, (uint32_t)HAL_I2S_STATE_IDLE);

  /* Disable I2S if I2S is enabled */
  if (LL_I2S_IsEnabled(I2S_GET_INSTANCE(hi2s)) != 0U)
  {
    LL_I2S_Disable(I2S_GET_INSTANCE(hi2s));
  }

  LL_I2S_EnableIOLock(I2S_GET_INSTANCE(hi2s));

  return HAL_OK;
}

/**
  * @brief Retrieve the IO configuration status for the dedicated SPI.
  * @param hi2s Pointer to a hal_spi_handle_t structure that contains
  *             the configuration information for SPI module.
  * @retval hal_i2s_io_cfg_status_t.
  */
hal_i2s_io_cfg_status_t HAL_I2S_IsLockedIOConfig(hal_i2s_handle_t *hi2s)
{
  /* Check the I2S handle allocation */
  ASSERT_DBG_PARAM(hi2s != NULL);

  /* Check the I2S state */
  ASSERT_DBG_STATE(hi2s->global_state, (((uint32_t)HAL_I2S_STATE_IDLE)           \
                                        | ((uint32_t)HAL_I2S_STATE_TX_ACTIVE)    \
                                        | ((uint32_t)HAL_I2S_STATE_RX_ACTIVE)    \
                                        | ((uint32_t)HAL_I2S_STATE_TX_RX_ACTIVE) \
                                        | ((uint32_t)HAL_I2S_STATE_PAUSED)       \
                                        | ((uint32_t)HAL_I2S_STATE_ABORT)));

  return (hal_i2s_io_cfg_status_t)LL_I2S_IsEnabledIOLock(I2S_GET_INSTANCE(hi2s));
}
/**
  * @}
  */

/** @addtogroup I2S_Exported_Functions_Group4 Items functions
  * @{
  This subsection provides a set of functions allowing the change and retrieve a single configuration in the
  IDLE state.
  - HAL_I2S_SetMode: Set the mode of the I2S peripheral.
  - HAL_I2S_GetMode: Retrieve the mode of the I2S peripheral.
  - HAL_I2S_SetStandard: Set the standard of the I2S peripheral.
  - HAL_I2S_GetStandard: Retrieve the standard of the I2S peripheral.
  - HAL_I2S_SetDataFormat: Set the data format of the I2S peripheral.
  - HAL_I2S_GetDataFormat: Retrieve the data format of the I2S peripheral.
  - HAL_I2S_SetAudioFrequency: Set the audio frequency of the I2S peripheral.
  - HAL_I2S_GetAudioFrequency: Retrieve the audio frequency of the I2S peripheral.
  - HAL_I2S_SetClockPolarity: Set the clock polarity of the I2S peripheral.
  - HAL_I2S_GetClockPolarity: Retrieve the clock polarity of the I2S peripheral.
  - HAL_I2S_SetBitOrder: Set the bit order for data transfers (MSB or LSB bit first) of the I2S peripheral.
  - HAL_I2S_GetBitOrder: Retrieve the bit order for data transfers (MSB or LSB bit first) of the I2S peripheral.
  - HAL_I2S_SetFifoThreshold: Set the FIFO threshold level for the I2S peripheral.
  - HAL_I2S_GetFifoThreshold: Retrieve the FIFO threshold level for the I2S peripheral.
  */

/**
  * @brief  Set the transfer mode for the I2S peripheral.
  * @param  hi2s Pointer to a @ref hal_i2s_handle_t structure that contains
  *              the configuration information of the I2S module.
  * @param  mode This parameter must be a value of hal_i2s_mode_t.
  * @retval HAL_OK Operation completed successfully.
  */
hal_status_t HAL_I2S_SetMode(hal_i2s_handle_t *hi2s, const hal_i2s_mode_t mode)
{
  /* Check the I2S handle allocation */
  ASSERT_DBG_PARAM(hi2s != NULL);
  ASSERT_DBG_PARAM(IS_I2S_MODE(mode));

  /* Check the global state */
  ASSERT_DBG_STATE(hi2s->global_state, HAL_I2S_STATE_IDLE);

  /* Disable I2S if I2S is enabled */
  if (LL_I2S_IsEnabled(I2S_GET_INSTANCE(hi2s)) != 0U)
  {
    LL_I2S_Disable(I2S_GET_INSTANCE(hi2s));
  }

  LL_I2S_SetTransferMode(I2S_GET_INSTANCE(hi2s), (uint32_t)mode);

  return HAL_OK;
}

/**
  * @brief  Retrieve the transfer mode for the I2S peripheral.
  * @param  hi2s Pointer to a @ref hal_i2s_handle_t structure that contains
  *              the configuration information of the I2S module.
  * @retval hal_i2s_mode_t Current I2S mode configuration
  */
hal_i2s_mode_t HAL_I2S_GetMode(const hal_i2s_handle_t *hi2s)
{
  /* Check the I2S handle allocation */
  ASSERT_DBG_PARAM(hi2s != NULL);

  /* Check the global state */
  ASSERT_DBG_STATE(hi2s->global_state, (((uint32_t)HAL_I2S_STATE_IDLE)           \
                                        | ((uint32_t)HAL_I2S_STATE_TX_ACTIVE)    \
                                        | ((uint32_t)HAL_I2S_STATE_RX_ACTIVE)    \
                                        | ((uint32_t)HAL_I2S_STATE_TX_RX_ACTIVE) \
                                        | ((uint32_t)HAL_I2S_STATE_PAUSED)       \
                                        | ((uint32_t)HAL_I2S_STATE_ABORT)));

  return (hal_i2s_mode_t)LL_I2S_GetTransferMode(I2S_GET_INSTANCE(hi2s));
}

/**
  * @brief  Set the standard for the I2S peripheral.
  * @param  hi2s Pointer to a @ref hal_i2s_handle_t structure that contains
  *              the configuration information of the I2S module.
  * @param  standard This parameter must be a value of hal_i2s_standard_t.
  * @retval HAL_OK Operation completed successfully.
  */
hal_status_t HAL_I2S_SetStandard(hal_i2s_handle_t *hi2s, const hal_i2s_standard_t standard)
{
  /* Check the I2S handle allocation */
  ASSERT_DBG_PARAM(hi2s != NULL);
  ASSERT_DBG_PARAM(IS_I2S_STANDARD(standard));

  /* Check the global state */
  ASSERT_DBG_STATE(hi2s->global_state, HAL_I2S_STATE_IDLE);

  /* Disable I2S if I2S is enabled */
  if (LL_I2S_IsEnabled(I2S_GET_INSTANCE(hi2s)) != 0U)
  {
    LL_I2S_Disable(I2S_GET_INSTANCE(hi2s));
  }

  LL_I2S_SetStandard(I2S_GET_INSTANCE(hi2s), (uint32_t)standard);

  return HAL_OK;
}

/**
  * @brief  Retrieve the standard for the I2S peripheral.
  * @param  hi2s Pointer to a @ref hal_i2s_handle_t structure that contains
  *              the configuration information of the I2S module.
  * @retval hal_i2s_standard_t Current I2S standard configuration
  */
hal_i2s_standard_t HAL_I2S_GetStandard(const hal_i2s_handle_t *hi2s)
{
  /* Check the I2S handle allocation */
  ASSERT_DBG_PARAM(hi2s != NULL);

  /* Check the global state */
  ASSERT_DBG_STATE(hi2s->global_state, (((uint32_t)HAL_I2S_STATE_IDLE)           \
                                        | ((uint32_t)HAL_I2S_STATE_TX_ACTIVE)    \
                                        | ((uint32_t)HAL_I2S_STATE_RX_ACTIVE)    \
                                        | ((uint32_t)HAL_I2S_STATE_TX_RX_ACTIVE) \
                                        | ((uint32_t)HAL_I2S_STATE_PAUSED)       \
                                        | ((uint32_t)HAL_I2S_STATE_ABORT)));

  return (hal_i2s_standard_t)LL_I2S_GetStandard(I2S_GET_INSTANCE(hi2s));
}

/**
  * @brief  Set the data format for the I2S peripheral.
  * @param  hi2s Pointer to a @ref hal_i2s_handle_t structure that contains
  *              the configuration information of the I2S module.
  * @param  format This parameter must be a value of hal_i2s_data_format_t.
  * @retval HAL_OK Operation completed successfully.
  */
hal_status_t HAL_I2S_SetDataFormat(hal_i2s_handle_t *hi2s, const hal_i2s_data_format_t format)
{
  /* Check the I2S handle allocation */
  ASSERT_DBG_PARAM(hi2s != NULL);
  ASSERT_DBG_PARAM(IS_I2S_DATA_FORMAT(format));

  /* Check the global state */
  ASSERT_DBG_STATE(hi2s->global_state, HAL_I2S_STATE_IDLE);

  /* Disable I2S if I2S is enabled */
  if (LL_I2S_IsEnabled(I2S_GET_INSTANCE(hi2s)) != 0U)
  {
    LL_I2S_Disable(I2S_GET_INSTANCE(hi2s));
  }

  LL_I2S_SetDataFormat(I2S_GET_INSTANCE(hi2s), (uint32_t)format);

  return HAL_OK;
}

/**
  * @brief  Retrieve the data format for the I2S peripheral.
  * @param  hi2s Pointer to a @ref hal_i2s_handle_t structure that contains
  *              the configuration information of the I2S module.
  * @retval hal_i2s_data_format_t Current I2S data format configuration
  */
hal_i2s_data_format_t HAL_I2S_GetDataFormat(const hal_i2s_handle_t *hi2s)
{
  /* Check the I2S handle allocation */
  ASSERT_DBG_PARAM(hi2s != NULL);

  /* Check the global state */
  ASSERT_DBG_STATE(hi2s->global_state, (((uint32_t)HAL_I2S_STATE_IDLE)           \
                                        | ((uint32_t)HAL_I2S_STATE_TX_ACTIVE)    \
                                        | ((uint32_t)HAL_I2S_STATE_RX_ACTIVE)    \
                                        | ((uint32_t)HAL_I2S_STATE_TX_RX_ACTIVE) \
                                        | ((uint32_t)HAL_I2S_STATE_PAUSED)       \
                                        | ((uint32_t)HAL_I2S_STATE_ABORT)));

  return (hal_i2s_data_format_t)LL_I2S_GetDataFormat(I2S_GET_INSTANCE(hi2s));
}

/**
  * @brief  Set the data alignment to right for the I2S peripheral.
  * @param  hi2s Pointer to a @ref hal_i2s_handle_t structure that contains
  *              the configuration information of the I2S module.
  * @retval HAL_OK Operation completed successfully.
  */
hal_status_t HAL_I2S_SetData24BitsAlignedRight(hal_i2s_handle_t *hi2s)
{
  /* Check the I2S handle allocation */
  ASSERT_DBG_PARAM(hi2s != NULL);

  /* Check the global state */
  ASSERT_DBG_STATE(hi2s->global_state, HAL_I2S_STATE_IDLE);

  /* Disable I2S if I2S is enabled */
  if (LL_I2S_IsEnabled(I2S_GET_INSTANCE(hi2s)) != 0U)
  {
    LL_I2S_Disable(I2S_GET_INSTANCE(hi2s));
  }

  if (LL_I2S_GetDataFormat(I2S_GET_INSTANCE(hi2s)) == LL_I2S_DATA_FORMAT_24_BIT)
  {
    LL_I2S_SetDataAlignmentRight(I2S_GET_INSTANCE(hi2s));
  }

  return HAL_OK;
}

/**
  * @brief  Set the data alignment to left for the I2S peripheral.
  * @param  hi2s Pointer to a @ref hal_i2s_handle_t structure that contains
  *              the configuration information of the I2S module.
  * @retval HAL_OK Operation completed successfully.
  */
hal_status_t HAL_I2S_SetData24BitsAlignedLeft(hal_i2s_handle_t *hi2s)
{
  /* Check the I2S handle allocation */
  ASSERT_DBG_PARAM(hi2s != NULL);

  /* Check the global state */
  ASSERT_DBG_STATE(hi2s->global_state, HAL_I2S_STATE_IDLE);

  /* Disable I2S if I2S is enabled */
  if (LL_I2S_IsEnabled(I2S_GET_INSTANCE(hi2s)) != 0U)
  {
    LL_I2S_Disable(I2S_GET_INSTANCE(hi2s));
  }

  if (LL_I2S_GetDataFormat(I2S_GET_INSTANCE(hi2s)) == LL_I2S_DATA_FORMAT_24_BIT)
  {
    LL_I2S_SetDataAlignmentLeft(I2S_GET_INSTANCE(hi2s));
  }

  return HAL_OK;
}

/**
  * @brief  Set the audio frequency for the I2S peripheral.
  * @param  hi2s Pointer to a @ref hal_i2s_handle_t structure that contains
  *              the configuration information of the I2S module.
  * @param  frequency This parameter must be a value of hal_i2s_audio_frequency_t.
  * @retval HAL_OK Operation completed successfully.
  */
hal_status_t HAL_I2S_SetAudioFrequency(hal_i2s_handle_t *hi2s, const hal_i2s_audio_frequency_t frequency)
{
  uint32_t i2s_clk;
  uint32_t tmp;
  uint32_t i2s_div;
  uint32_t i2s_odd;
  uint32_t ispcm = 0U;
  uint32_t channel_length = 1U;
  hal_i2s_data_format_t data_format;
  hal_i2s_standard_t standard;
  hal_i2s_mode_t mode;

  /* Check the I2S handle allocation */
  ASSERT_DBG_PARAM(hi2s != NULL);
  ASSERT_DBG_PARAM(IS_I2S_AUDIO_FREQUENCY(frequency));

  /* Check the global state */
  ASSERT_DBG_STATE(hi2s->global_state, HAL_I2S_STATE_INIT | HAL_I2S_STATE_IDLE);

  i2s_clk = HAL_I2S_GetClockFreq(hi2s);

  if (i2s_clk == 0U)
  {
    return HAL_ERROR;
  }

  standard = (hal_i2s_standard_t)LL_I2S_GetStandard(I2S_GET_INSTANCE(hi2s));
  data_format = (hal_i2s_data_format_t)LL_I2S_GetDataFormat(I2S_GET_INSTANCE(hi2s));
  mode = (hal_i2s_mode_t)LL_I2S_GetTransferMode(I2S_GET_INSTANCE(hi2s));

  if (IS_I2S_MODE_MASTER(mode))
  {
    if (frequency != HAL_I2S_AUDIO_FREQ_DEFAULT)
    {

      if ((standard == HAL_I2S_STANDARD_PCM_SHORT) || (standard == HAL_I2S_STANDARD_PCM_LONG))
      {
        ispcm = 1U;
      }

      if (data_format != HAL_I2S_DATA_FORMAT_16_BIT)
      {
        /* Channel length is 32 bits */
        channel_length = 2U;
      }

      if (LL_I2S_IsEnabledMasterClock(I2S_GET_INSTANCE(hi2s)) != 0U)
      {
        tmp = (uint32_t)((((i2s_clk / ((uint32_t)(256UL >> ispcm))) * 10U) / (uint32_t)frequency) + 5U);
      }
      else
      {
        tmp = (uint32_t)((((i2s_clk / (((uint32_t)(32UL >> ispcm)) * channel_length)) * 10U)
                          / (uint32_t)frequency) + 5U);
      }

      /* Remove the flatting point */
      tmp = tmp / 10U;

      /* Check the parity of the divider */
      i2s_odd = (uint32_t)(tmp & (uint32_t)1U);

      /* Compute the i2sdiv prescaler */
      i2s_div = (uint32_t)((tmp - i2s_odd) / 2U);
    }
    else
    {
      /* Set the default values */
      i2s_div = 2U;
      i2s_odd = 0U;
    }

    /* Test if the obtain values are forbidden or out of range */
    if (((i2s_odd == 1U) && (i2s_div == 1U)) || (i2s_div > 0xFFU))
    {
      return HAL_ERROR;
    }

    /* Force i2smod to 1 just to be sure that (2xi2sdiv + i2sodd) is always higher than 0 */
    if (i2s_div == 0U)
    {
      i2s_odd = 1U;
    }

    /* Disable I2S if I2S is enabled */
    if (LL_I2S_IsEnabled(I2S_GET_INSTANCE(hi2s)) != 0U)
    {
      LL_I2S_Disable(I2S_GET_INSTANCE(hi2s));
    }

    STM32_MODIFY_REG(I2S_GET_INSTANCE(hi2s)->I2SCFGR, (SPI_I2SCFGR_I2SDIV | SPI_I2SCFGR_ODD),
                     ((i2s_div << SPI_I2SCFGR_I2SDIV_Pos) | (i2s_odd << SPI_I2SCFGR_ODD_Pos)));
  }

  return HAL_OK;
}

/**
  * @brief  Retrieve the audio frequency for the I2S peripheral.
  * @param  hi2s Pointer to a @ref hal_i2s_handle_t structure that contains
  *              the configuration information of the I2S module.
  * @retval hal_i2s_audio_frequency_t Current I2S audio frequency configuration
  */
hal_i2s_audio_frequency_t HAL_I2S_GetAudioFrequency(const hal_i2s_handle_t *hi2s)
{
  uint32_t tmp_index = 0U;
  uint32_t index = 0U;
  uint32_t real_freq = 0U;
  uint32_t min_diff = 0U;
  uint32_t diff = 0U;

  const uint32_t audio_frequencies[10U] = {(uint32_t)HAL_I2S_AUDIO_FREQ_DEFAULT, \
                                           (uint32_t)HAL_I2S_AUDIO_FREQ_8_KHZ,   \
                                           (uint32_t)HAL_I2S_AUDIO_FREQ_11_KHZ,  \
                                           (uint32_t)HAL_I2S_AUDIO_FREQ_16_KHZ,  \
                                           (uint32_t)HAL_I2S_AUDIO_FREQ_22_KHZ,  \
                                           (uint32_t)HAL_I2S_AUDIO_FREQ_32_KHZ,  \
                                           (uint32_t)HAL_I2S_AUDIO_FREQ_44_KHZ,  \
                                           (uint32_t)HAL_I2S_AUDIO_FREQ_48_KHZ,  \
                                           (uint32_t)HAL_I2S_AUDIO_FREQ_96_KHZ,  \
                                           (uint32_t)HAL_I2S_AUDIO_FREQ_192_KHZ
                                          };

  /* Check the I2S handle allocation */
  ASSERT_DBG_PARAM(hi2s != NULL);

  /* Check the global state */
  ASSERT_DBG_STATE(hi2s->global_state, (((uint32_t)HAL_I2S_STATE_IDLE)           \
                                        | ((uint32_t)HAL_I2S_STATE_TX_ACTIVE)    \
                                        | ((uint32_t)HAL_I2S_STATE_RX_ACTIVE)    \
                                        | ((uint32_t)HAL_I2S_STATE_TX_RX_ACTIVE) \
                                        | ((uint32_t)HAL_I2S_STATE_PAUSED)       \
                                        | ((uint32_t)HAL_I2S_STATE_ABORT)));

  real_freq = HAL_I2S_GetRealAudioFrequency(hi2s);

  if (real_freq > audio_frequencies[0])
  {
    min_diff = (real_freq - audio_frequencies[0]);
  }
  else
  {
    min_diff = (audio_frequencies[0] - real_freq);
  }

  for (tmp_index = 1U; tmp_index < 10U; tmp_index++)
  {
    if (real_freq > audio_frequencies[tmp_index])
    {
      diff = (real_freq - audio_frequencies[tmp_index]);
    }
    else
    {
      diff = (audio_frequencies[tmp_index] - real_freq);
    }

    if (diff < min_diff)
    {
      min_diff = diff;
      index = tmp_index;
    }
  }

  return (hal_i2s_audio_frequency_t)audio_frequencies[index];
}

/**
  * @brief  Set the clock polarity for the I2S peripheral.
  * @param  hi2s Pointer to a @ref hal_i2s_handle_t structure that contains
  *              the configuration information of the I2S module.
  * @param  clock_polarity This parameter must be a value of hal_i2s_clock_polarity_t.
  * @retval HAL_OK Operation completed successfully.
  */
hal_status_t HAL_I2S_SetClockPolarity(hal_i2s_handle_t *hi2s, const hal_i2s_clock_polarity_t clock_polarity)
{
  /* Check the I2S handle allocation */
  ASSERT_DBG_PARAM(hi2s != NULL);
  ASSERT_DBG_PARAM(IS_I2S_CLOCK_POLARITY(clock_polarity));

  /* Check the global state */
  ASSERT_DBG_STATE(hi2s->global_state, HAL_I2S_STATE_IDLE);

  /* Disable I2S if I2S is enabled */
  if (LL_I2S_IsEnabled(I2S_GET_INSTANCE(hi2s)) != 0U)
  {
    LL_I2S_Disable(I2S_GET_INSTANCE(hi2s));
  }

  LL_I2S_SetClockPolarity(I2S_GET_INSTANCE(hi2s), (uint32_t)clock_polarity);

  return HAL_OK;
}

/**
  * @brief  Retrieve the clock polarity for the I2S peripheral.
  * @param  hi2s Pointer to a @ref hal_i2s_handle_t structure that contains
  *              the configuration information of the I2S module.
  * @retval hal_i2s_clock_polarity_t Current I2S clock polarity configuration
  */
hal_i2s_clock_polarity_t HAL_I2S_GetClockPolarity(const hal_i2s_handle_t *hi2s)
{
  /* Check the I2S handle allocation */
  ASSERT_DBG_PARAM(hi2s != NULL);

  /* Check the global state */
  ASSERT_DBG_STATE(hi2s->global_state, (((uint32_t)HAL_I2S_STATE_IDLE)           \
                                        | ((uint32_t)HAL_I2S_STATE_TX_ACTIVE)    \
                                        | ((uint32_t)HAL_I2S_STATE_RX_ACTIVE)    \
                                        | ((uint32_t)HAL_I2S_STATE_TX_RX_ACTIVE) \
                                        | ((uint32_t)HAL_I2S_STATE_PAUSED)       \
                                        | ((uint32_t)HAL_I2S_STATE_ABORT)));

  return (hal_i2s_clock_polarity_t)LL_I2S_GetClockPolarity(I2S_GET_INSTANCE(hi2s));
}

/**
  * @brief  Set the bit order for data transfers (MSB or LSB bit first) for the I2S peripheral.
  * @param  hi2s Pointer to a @ref hal_i2s_handle_t structure that contains
  *              the configuration information of the I2S module.
  * @param  bit_order This parameter must be a value of hal_i2s_bit_order_t.
  * @retval HAL_ERROR When io is locked.
  * @retval HAL_OK Operation completed successfully.
  */
hal_status_t HAL_I2S_SetBitOrder(hal_i2s_handle_t *hi2s, const hal_i2s_bit_order_t bit_order)
{
  /* Check the I2S handle allocation */
  ASSERT_DBG_PARAM(hi2s != NULL);
  ASSERT_DBG_PARAM(IS_I2S_BIT_ORDER(bit_order));

  /* Check the global state */
  ASSERT_DBG_STATE(hi2s->global_state, HAL_I2S_STATE_IDLE);

  /* Check for IOLock */
  if (LL_I2S_IsEnabledIOLock(I2S_GET_INSTANCE(hi2s)) == 1U)
  {
#if defined(USE_HAL_I2S_GET_LAST_ERRORS) && (USE_HAL_I2S_GET_LAST_ERRORS == 1U)
    hi2s->last_error_codes = HAL_I2S_ERROR_IO_LOCKED;
#endif /* USE_HAL_I2S_GET_LAST_ERRORS */
    return HAL_ERROR;
  }

  /* Disable I2S if I2S is enabled */
  if (LL_I2S_IsEnabled(I2S_GET_INSTANCE(hi2s)) != 0U)
  {
    LL_I2S_Disable(I2S_GET_INSTANCE(hi2s));
  }

  LL_I2S_SetTransferBitOrder(I2S_GET_INSTANCE(hi2s), (uint32_t)bit_order);

  return HAL_OK;
}

/**
  * @brief  Retrieve the bit order for data transfers (MSB or LSB bit first) the I2S peripheral.
  * @param  hi2s Pointer to a @ref hal_i2s_handle_t structure that contains
  *              the configuration information of the I2S module.
  * @retval hal_i2s_bit_order_t Current I2S bit order configuration
  */
hal_i2s_bit_order_t HAL_I2S_GetBitOrder(const hal_i2s_handle_t *hi2s)
{
  /* Check the I2S handle allocation */
  ASSERT_DBG_PARAM(hi2s != NULL);

  /* Check the global state */
  ASSERT_DBG_STATE(hi2s->global_state, (((uint32_t)HAL_I2S_STATE_IDLE)           \
                                        | ((uint32_t)HAL_I2S_STATE_TX_ACTIVE)    \
                                        | ((uint32_t)HAL_I2S_STATE_RX_ACTIVE)    \
                                        | ((uint32_t)HAL_I2S_STATE_TX_RX_ACTIVE) \
                                        | ((uint32_t)HAL_I2S_STATE_PAUSED)       \
                                        | ((uint32_t)HAL_I2S_STATE_ABORT)));

  return (hal_i2s_bit_order_t)LL_I2S_GetTransferBitOrder(I2S_GET_INSTANCE(hi2s));
}

/**
  * @brief  Set the FIFO threshold level for the I2S peripheral.
  * @param  hi2s Pointer to a @ref hal_i2s_handle_t structure that contains
  *              the configuration information of the I2S module.
  * @param  fifo_threshold This parameter must be a value of hal_i2s_fifo_threshold_t.
  * @retval HAL_OK Operation completed successfully.
  */
hal_status_t HAL_I2S_SetFifoThreshold(hal_i2s_handle_t *hi2s, const hal_i2s_fifo_threshold_t fifo_threshold)
{
  /* Check the I2S handle allocation */
  ASSERT_DBG_PARAM(hi2s != NULL);
  ASSERT_DBG_PARAM(IS_I2S_FIFO_THRESHOLD(fifo_threshold));

  /* Check the global state */
  ASSERT_DBG_STATE(hi2s->global_state, HAL_I2S_STATE_IDLE);

  /* Disable I2S if I2S is enabled */
  if (LL_I2S_IsEnabled(I2S_GET_INSTANCE(hi2s)) != 0U)
  {
    LL_I2S_Disable(I2S_GET_INSTANCE(hi2s));
  }

  LL_I2S_SetFIFOThreshold(I2S_GET_INSTANCE(hi2s), (uint32_t)fifo_threshold);

  return HAL_OK;
}

/**
  * @brief  Retrieve the bit order for data transfers (MSB or LSB bit first) the I2S peripheral.
  * @param  hi2s Pointer to a @ref hal_i2s_handle_t structure that contains
  *              the configuration information of the I2S module.
  * @retval hal_i2s_fifo_threshold_t Current I2S FIFO threshold level configuration
  */
hal_i2s_fifo_threshold_t HAL_I2S_GetFifoThreshold(const hal_i2s_handle_t *hi2s)
{
  /* Check the I2S handle allocation */
  ASSERT_DBG_PARAM(hi2s != NULL);

  /* Check the global state */
  ASSERT_DBG_STATE(hi2s->global_state, (((uint32_t)HAL_I2S_STATE_IDLE)           \
                                        | ((uint32_t)HAL_I2S_STATE_TX_ACTIVE)    \
                                        | ((uint32_t)HAL_I2S_STATE_RX_ACTIVE)    \
                                        | ((uint32_t)HAL_I2S_STATE_TX_RX_ACTIVE) \
                                        | ((uint32_t)HAL_I2S_STATE_PAUSED)       \
                                        | ((uint32_t)HAL_I2S_STATE_ABORT)));

  return (hal_i2s_fifo_threshold_t)LL_I2S_GetFIFOThreshold(I2S_GET_INSTANCE(hi2s));
}


#if defined(USE_HAL_I2S_DMA) && (USE_HAL_I2S_DMA == 1U)
/**
  * @brief  Link the Transmit DMA handle to the I2S handle.
  * @param  hi2s Pointer to a @ref hal_i2s_handle_t structure.
  * @param  hdma Pointer to a hal_dma_handle_t structure.
  * @retval HAL_OK Operation completed successfully.
  * @retval HAL_INVALID_PARAM Invalid parameter.
  */
hal_status_t HAL_I2S_SetTxDMA(hal_i2s_handle_t *hi2s, hal_dma_handle_t *hdma)
{
  /* Check the I2S and DMA handle */
  ASSERT_DBG_PARAM(hi2s != NULL);
  ASSERT_DBG_PARAM(hdma != NULL);

  /* Check the state */
  ASSERT_DBG_STATE(hi2s->global_state, (uint32_t)HAL_I2S_STATE_INIT | (uint32_t)HAL_I2S_STATE_IDLE);

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1U)
  if (hdma == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  /* Link the DMA handle to the I2S handle */
  hi2s->hdma_tx = hdma;
  hdma->p_parent = hi2s;

  return HAL_OK;
}

/**
  * @brief  Link the Receive DMA handle to the I2S handle.
  * @param  hi2s Pointer to a @ref hal_i2s_handle_t
  * @param  hdma Pointer to a hal_dma_handle_t structure
  * @retval HAL_OK Operation completed successfully
  * @retval HAL_INVALID_PARAM Invalid parameter
  */
hal_status_t HAL_I2S_SetRxDMA(hal_i2s_handle_t *hi2s, hal_dma_handle_t *hdma)
{
  /* Check the I2S and DMA handle */
  ASSERT_DBG_PARAM(hi2s != NULL);
  ASSERT_DBG_PARAM(hdma != NULL);

  /* Check the state */
  ASSERT_DBG_STATE(hi2s->global_state, (uint32_t)HAL_I2S_STATE_INIT | (uint32_t)HAL_I2S_STATE_IDLE);

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1U)
  if (hdma == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  /* Link the DMA handle to the SPI handle */
  hi2s->hdma_rx = hdma;
  hdma->p_parent = hi2s;

  return HAL_OK;
}
#endif /* USE_HAL_I2S_DMA */

/**
  * @}
  */

/** @addtogroup I2S_Exported_Functions_Group5 IO operation functions
  * @{
  * This subsection provides a set of functions allowing to manage the I2S data transfers.
  *
  * The I2S supports both master and slave mode:
  * There are two mode of transfer:
  *  - Blocking mode: The communication is performed in polling mode.
  *    The status of all data processing is returned by the same function after finishing the transfer.
  *  - No-Blocking mode: The communication is performed using Interrupts of DMA.
  *    These functions return the status of the transfer startup.
  *    The end of the data processing will be indicated through the dedicated I2S IRQ when using
  *    Interrupt mode or the DMA IRQ when using DMA mode.
  */

/**
  * @brief  Return the real audio frequency.
  * @param  hi2s Pointer to a @ref hal_i2s_handle_t
  * @retval uint32_t Real audio frequency in hz
  */
uint32_t HAL_I2S_GetRealAudioFrequency(const hal_i2s_handle_t *hi2s)
{
  uint32_t frequency_hz = 0U;
  uint32_t i2s_clk = 0U;
  uint32_t channel_length = 1U;
  uint32_t i2s_odd = 0U;
  uint32_t i2s_div = 0U;
  uint32_t ispcm = 0U;
  uint32_t prescaler = 0U;
  hal_i2s_standard_t standard;
  hal_i2s_data_format_t data_format;

  /* Check the I2S handle allocation */
  ASSERT_DBG_PARAM(hi2s != NULL);

  /* Check the global state */
  ASSERT_DBG_STATE(hi2s->global_state, (((uint32_t)HAL_I2S_STATE_IDLE)           \
                                        | ((uint32_t)HAL_I2S_STATE_TX_ACTIVE)    \
                                        | ((uint32_t)HAL_I2S_STATE_RX_ACTIVE)    \
                                        | ((uint32_t)HAL_I2S_STATE_TX_RX_ACTIVE) \
                                        | ((uint32_t)HAL_I2S_STATE_PAUSED)       \
                                        | ((uint32_t)HAL_I2S_STATE_ABORT)));

  i2s_clk = HAL_I2S_GetClockFreq(hi2s);

  if (i2s_clk == 0U)
  {
    return (uint32_t)HAL_ERROR;
  }

  data_format = (hal_i2s_data_format_t)LL_I2S_GetDataFormat(I2S_GET_INSTANCE(hi2s));
  i2s_odd = LL_I2S_GetPrescalerParity(I2S_GET_INSTANCE(hi2s));
  i2s_div = LL_I2S_GetPrescalerLinear(I2S_GET_INSTANCE(hi2s));
  standard = (hal_i2s_standard_t)LL_I2S_GetStandard(I2S_GET_INSTANCE(hi2s));

  if (i2s_div == 0U)
  {
    /* Force prescaler to 1 just to be sure that (2xi2sdiv + i2sodd) is always higher than 0 */
    prescaler = 1U;
  }
  else
  {
    prescaler = (uint32_t)((2U * i2s_div) + i2s_odd);
  }

  if ((standard == HAL_I2S_STANDARD_PCM_SHORT) || (standard == HAL_I2S_STANDARD_PCM_LONG))
  {
    ispcm = 1U;
  }

  if (data_format != HAL_I2S_DATA_FORMAT_16_BIT)
  {
    /* Channel length is 32 bits */
    channel_length = 2U;
  }

  if (LL_I2S_IsEnabledMasterClock(I2S_GET_INSTANCE(hi2s)) != 0U)
  {
    frequency_hz = (uint32_t)((((i2s_clk / ((uint32_t)(256UL >> ispcm))) * 10U) / prescaler) + 5U);
  }
  else
  {
    frequency_hz = (uint32_t)((((i2s_clk / (((uint32_t)(32UL >> ispcm)) * channel_length)) * 10U) / prescaler) + 5U);
  }

  /* Remove the flatting point */
  frequency_hz = frequency_hz / 10U;

  return frequency_hz;
}

/**
  * @brief Transmit an amount of data in blocking mode.
  * @param  hi2s Pointer to a @ref hal_i2s_handle_t
  * @param  p_data Pointer to data buffer
  * @param  transfer_size Amount of data to send in bytes
  * @param  timeout_ms Timeout duration
  * @retval HAL_OK Operation completed successfully
  * @retval HAL_BUSY Concurrent process ongoing
  * @retval HAL_ERROR Operation completed with error
  * @retval HAL_TIMEOUT Operation exceeds user timeout
  */
hal_status_t HAL_I2S_Transmit(hal_i2s_handle_t *hi2s, const void *p_data, uint32_t transfer_size, uint32_t timeout_ms)
{
  hal_status_t hal_status = HAL_OK;
  uint32_t tickstart;
  hal_i2s_data_format_t data_format;

  /* Check the I2S handle allocation */
  ASSERT_DBG_PARAM(hi2s != NULL);
  ASSERT_DBG_PARAM(p_data != NULL);
  ASSERT_DBG_PARAM(transfer_size != 0U);
#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1U)
  if ((p_data == NULL) || (transfer_size == 0U))
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  /* Check the global state */
  ASSERT_DBG_STATE(hi2s->global_state, HAL_I2S_STATE_IDLE);

#if defined(USE_ASSERT_DBG_PARAM)
  ASSERT_DBG_PARAM(IS_I2S_MODE_TX(HAL_I2S_GetMode(hi2s)));
#endif /* USE_ASSERT_DBG_PARAM */

  HAL_CHECK_UPDATE_STATE(hi2s, global_state, HAL_I2S_STATE_IDLE, HAL_I2S_STATE_TX_ACTIVE);

  /* Init tickstart for timeout management */
  tickstart = HAL_GetTick();

  data_format = (hal_i2s_data_format_t)LL_I2S_GetDataFormat(I2S_GET_INSTANCE(hi2s));

  /* Set the state and reset error code */
  hi2s->global_state = HAL_I2S_STATE_TX_ACTIVE;
  hi2s->previous_state = HAL_I2S_STATE_IDLE;
#if defined(USE_HAL_I2S_GET_LAST_ERRORS) && (USE_HAL_I2S_GET_LAST_ERRORS == 1U)
  hi2s->last_error_codes = HAL_I2S_ERROR_NONE;
#endif /* USE_HAL_I2S_GET_LAST_ERRORS */
  hi2s->p_tx_buff = (const uint16_t *)p_data;
  hi2s->tx_xfer_size = (uint16_t)transfer_size;
  hi2s->tx_xfer_count = (uint16_t)transfer_size;

  /* Initialize fields not used in handle to zero */
  hi2s->p_rx_buff  = (uint16_t *)NULL;
  hi2s->rx_xfer_size  = (uint16_t) 0U;
  hi2s->rx_xfer_count = (uint16_t) 0U;

  LL_I2S_Enable(I2S_GET_INSTANCE(hi2s));

  LL_I2S_StartTransfer(I2S_GET_INSTANCE(hi2s));

  while (hi2s->tx_xfer_count > 0U)
  {
    /* Wait until TXP flag is set */
    if (I2S_WaitOnFlagUntilTimeout(hi2s, LL_I2S_FLAG_TXP, 1U, tickstart, timeout_ms) != HAL_OK)
    {
      hi2s->global_state = HAL_I2S_STATE_IDLE;
      return HAL_TIMEOUT;
    }

    if ((data_format == HAL_I2S_DATA_FORMAT_24_BIT)
        || (data_format == HAL_I2S_DATA_FORMAT_32_BIT))
    {
      /* Transmit data in 32bit mode */
      LL_I2S_TransmitData32(I2S_GET_INSTANCE(hi2s), *((const uint32_t *)hi2s->p_tx_buff));
      hi2s->p_tx_buff += 2U;
      hi2s->tx_xfer_count--;
    }
    else
    {
      /* Transmit data in 16 Bit mode */
      LL_I2S_TransmitData16(I2S_GET_INSTANCE(hi2s), *((const uint16_t *)hi2s->p_tx_buff));
      hi2s->p_tx_buff++;
      hi2s->tx_xfer_count--;
    }
  }

  hal_status = I2S_CloseTransfer(hi2s);

  return hal_status;
}

/**
  * @brief  Receive an amount of data in blocking mode.
  * @param  hi2s Pointer to a @ref hal_i2s_handle_t
  * @param  p_data Pointer to data buffer
  * @param  transfer_size Amount of data to receive
  * @param  timeout_ms Timeout duration
  * @retval HAL_OK Operation completed successfully
  * @retval HAL_BUSY Concurrent process ongoing
  * @retval HAL_ERROR Operation completed with error
  * @retval HAL_TIMEOUT Operation exceeds user timeout
  */
hal_status_t HAL_I2S_Receive(hal_i2s_handle_t *hi2s, void *p_data, uint32_t transfer_size, uint32_t timeout_ms)
{
  hal_status_t hal_status = HAL_OK;
  uint32_t tickstart;
  hal_i2s_data_format_t data_format;

  /* Check the I2S handle allocation */
  ASSERT_DBG_PARAM(hi2s != NULL);
  ASSERT_DBG_PARAM(p_data != NULL);
  ASSERT_DBG_PARAM(transfer_size != 0U);
#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1U)
  if ((p_data == NULL) || (transfer_size == 0U))
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  /* Check the global state */
  ASSERT_DBG_STATE(hi2s->global_state, HAL_I2S_STATE_IDLE);

#if defined(USE_ASSERT_DBG_PARAM)
  ASSERT_DBG_PARAM(IS_I2S_MODE_RX(HAL_I2S_GetMode(hi2s)));
#endif /* USE_ASSERT_DBG_PARAM */

  HAL_CHECK_UPDATE_STATE(hi2s, global_state, HAL_I2S_STATE_IDLE, HAL_I2S_STATE_RX_ACTIVE);

  /* Init tickstart for timeout management */
  tickstart = HAL_GetTick();

  data_format = (hal_i2s_data_format_t)LL_I2S_GetDataFormat(I2S_GET_INSTANCE(hi2s));

  /* Set the state and reset error code */
  hi2s->global_state = HAL_I2S_STATE_RX_ACTIVE;
  hi2s->previous_state = HAL_I2S_STATE_IDLE;
#if defined(USE_HAL_I2S_GET_LAST_ERRORS) && (USE_HAL_I2S_GET_LAST_ERRORS == 1U)
  hi2s->last_error_codes = HAL_I2S_ERROR_NONE;
#endif /* USE_HAL_I2S_GET_LAST_ERRORS */
  hi2s->p_rx_buff = (uint16_t *)p_data;
  hi2s->rx_xfer_size = (uint16_t)transfer_size;
  hi2s->rx_xfer_count = (uint16_t)transfer_size;

  /* Initialize fields not used in handle to zero */
  hi2s->p_tx_buff  = (uint16_t *)NULL;
  hi2s->tx_xfer_size  = (uint16_t) 0U;
  hi2s->tx_xfer_count = (uint16_t) 0U;

  LL_I2S_Enable(I2S_GET_INSTANCE(hi2s));

  /* Start transfer */
  LL_I2S_StartTransfer(I2S_GET_INSTANCE(hi2s));

  /* Receive data */
  while (hi2s->rx_xfer_count > 0U)
  {
    if (I2S_WaitOnFlagUntilTimeout(hi2s, LL_I2S_FLAG_RXP, 1U, tickstart, timeout_ms) != HAL_OK)
    {
      hi2s->global_state = HAL_I2S_STATE_IDLE;
      return HAL_TIMEOUT;
    }

    if ((data_format == HAL_I2S_DATA_FORMAT_24_BIT)
        || (data_format == HAL_I2S_DATA_FORMAT_32_BIT))
    {
      /* Receive data in 32bit mode */
      *((uint32_t *)hi2s->p_rx_buff) = LL_I2S_ReceiveData32(I2S_GET_INSTANCE(hi2s));
      hi2s->p_rx_buff += 2U;
      hi2s->rx_xfer_count--;
    }
    else
    {
      /* Receive data in 16bit mode */
      *((uint16_t *)hi2s->p_rx_buff) = LL_I2S_ReceiveData16(I2S_GET_INSTANCE(hi2s));
      hi2s->p_rx_buff++;
      hi2s->rx_xfer_count--;
    }
  }

  hal_status = I2S_CloseTransfer(hi2s);

  return hal_status;
}

/**
  * @brief Transmit and Receive an amount of data in blocking mode.
  * @param  hi2s Pointer to a @ref hal_i2s_handle_t
  * @param  p_tx_data Pointer to data buffer to transmit
  * @param  p_rx_data Pointer to data buffer to receive
  * @param  transfer_size Amount of data to send and receive
  * @param  timeout_ms Timeout duration
  * @retval HAL_OK Operation completed successfully
  * @retval HAL_BUSY Concurrent process ongoing
  * @retval HAL_ERROR Operation completed with error
  * @retval HAL_TIMEOUT Operation exceeds user timeout
  */
hal_status_t HAL_I2S_TransmitReceive(hal_i2s_handle_t *hi2s, const void *p_tx_data, void *p_rx_data,
                                     uint32_t transfer_size, uint32_t timeout_ms)
{
  uint32_t tickstart;
  uint32_t tmp_tx_xfer_count;
  uint32_t tmp_rx_xfer_count;
  hal_i2s_data_format_t data_format;

  /* Check the I2S handle allocation */
  ASSERT_DBG_PARAM(hi2s != NULL);
  ASSERT_DBG_PARAM(p_tx_data != NULL);
  ASSERT_DBG_PARAM(p_rx_data != NULL);
  ASSERT_DBG_PARAM(transfer_size != 0U);
#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1U)
  if ((p_tx_data == NULL) || (p_rx_data == NULL) || (transfer_size == 0U))
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  /* Check the global state */
  ASSERT_DBG_STATE(hi2s->global_state, HAL_I2S_STATE_IDLE);

#if defined(USE_ASSERT_DBG_PARAM)
  ASSERT_DBG_PARAM(IS_I2S_MODE_FULL_DUPLEX(HAL_I2S_GetMode(hi2s)));
#endif /* USE_ASSERT_DBG_PARAM */

  HAL_CHECK_UPDATE_STATE(hi2s, global_state, HAL_I2S_STATE_IDLE, HAL_I2S_STATE_TX_RX_ACTIVE);

  /* Init tickstart for timeout management */
  tickstart = HAL_GetTick();

  data_format = (hal_i2s_data_format_t)LL_I2S_GetDataFormat(I2S_GET_INSTANCE(hi2s));

  /* Set the state and reset error code */
  hi2s->global_state = HAL_I2S_STATE_TX_RX_ACTIVE;
  hi2s->previous_state = HAL_I2S_STATE_IDLE;
#if defined(USE_HAL_I2S_GET_LAST_ERRORS) && (USE_HAL_I2S_GET_LAST_ERRORS == 1U)
  hi2s->last_error_codes = HAL_I2S_ERROR_NONE;
#endif /* USE_HAL_I2S_GET_LAST_ERRORS */
  hi2s->p_tx_buff = (const uint16_t *)p_tx_data;;
  hi2s->tx_xfer_size = (uint16_t)transfer_size;
  hi2s->tx_xfer_count = (uint16_t)transfer_size;
  hi2s->p_rx_buff = (uint16_t *)p_rx_data;
  hi2s->rx_xfer_size = (uint16_t)transfer_size;
  hi2s->rx_xfer_count = (uint16_t)transfer_size;

  tmp_tx_xfer_count = hi2s->tx_xfer_count;
  tmp_rx_xfer_count = hi2s->rx_xfer_count;

  LL_I2S_Enable(I2S_GET_INSTANCE(hi2s));

  /* Start the transfer */
  LL_I2S_StartTransfer(I2S_GET_INSTANCE(hi2s));

  if ((data_format == HAL_I2S_DATA_FORMAT_24_BIT)
      || (data_format == HAL_I2S_DATA_FORMAT_32_BIT))
  {
    while ((tmp_tx_xfer_count > 0U) || (tmp_rx_xfer_count > 0U))
    {
      if ((LL_I2S_IsActiveFlag_TXP(I2S_GET_INSTANCE(hi2s)) == 1U) && (tmp_tx_xfer_count != 0U))
      {
        /* Transmit data in 32bit mode */
        LL_I2S_TransmitData32(I2S_GET_INSTANCE(hi2s), *((const uint32_t *)hi2s->p_tx_buff));
        hi2s->p_tx_buff += 2U;
        tmp_tx_xfer_count--;
      }

      if ((LL_I2S_IsActiveFlag_RXP(I2S_GET_INSTANCE(hi2s)) == 1U) && (tmp_rx_xfer_count != 0U))
      {
        /* Receive data in 32bit mode */
        *((uint32_t *)hi2s->p_rx_buff) = LL_I2S_ReceiveData32(I2S_GET_INSTANCE(hi2s));
        hi2s->p_rx_buff += 2U;
        tmp_rx_xfer_count--;
      }

      /* Timeout management */
      if ((((HAL_GetTick() - tickstart) >= timeout_ms) && (timeout_ms != HAL_MAX_DELAY)) || (timeout_ms == 0U))
      {
        return HAL_TIMEOUT;
      }
    }
  }
  else
  {
    while ((tmp_tx_xfer_count > 0U) || (tmp_rx_xfer_count > 0U))
    {
      if ((LL_I2S_IsActiveFlag_TXP(I2S_GET_INSTANCE(hi2s)) == 1U) && (tmp_tx_xfer_count != 0U))
      {
        /* Transmit data in 16bit mode */
        LL_I2S_TransmitData16(I2S_GET_INSTANCE(hi2s), *((const uint16_t *)hi2s->p_tx_buff));
        hi2s->p_tx_buff++;
        tmp_tx_xfer_count--;
      }

      if ((LL_I2S_IsActiveFlag_RXP(I2S_GET_INSTANCE(hi2s)) == 1U) && (tmp_rx_xfer_count != 0U))
      {
        /* Receive data in 16bit mode */
        *((uint16_t *)hi2s->p_rx_buff) = LL_I2S_ReceiveData16(I2S_GET_INSTANCE(hi2s));
        hi2s->p_rx_buff++;
        tmp_rx_xfer_count--;
      }

      /* Timeout management */
      if ((((HAL_GetTick() - tickstart) >= timeout_ms) && (timeout_ms != HAL_MAX_DELAY)) || (timeout_ms == 0U))
      {
        return HAL_TIMEOUT;
      }
    }
  }

  return I2S_CloseTransfer(hi2s);
}

/**
  * @brief  Transmit an amount of data in Interrupt mode.
  * @param  hi2s Pointer to a @ref hal_i2s_handle_t
  * @param  p_data Pointer to data buffer
  * @param  transfer_size Amount of data to send
  * @retval HAL_OK Operation completed successfully
  * @retval HAL_BUSY Concurrent process ongoing
  */
hal_status_t HAL_I2S_Transmit_IT(hal_i2s_handle_t *hi2s, const void *p_data, uint32_t transfer_size)
{
  hal_i2s_data_format_t data_format;

  /* Check the I2S handle allocation */
  ASSERT_DBG_PARAM(hi2s != NULL);
  ASSERT_DBG_PARAM(p_data != NULL);
  ASSERT_DBG_PARAM(transfer_size != 0U);
#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1U)
  if ((p_data == NULL) || (transfer_size == 0U))
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  /* Check the global state */
  ASSERT_DBG_STATE(hi2s->global_state, HAL_I2S_STATE_IDLE);

#if defined(USE_ASSERT_DBG_PARAM)
  ASSERT_DBG_PARAM(IS_I2S_MODE_TX(HAL_I2S_GetMode(hi2s)));
#endif /* USE_ASSERT_DBG_PARAM */

  HAL_CHECK_UPDATE_STATE(hi2s, global_state, HAL_I2S_STATE_IDLE, HAL_I2S_STATE_TX_ACTIVE);

  data_format = (hal_i2s_data_format_t)LL_I2S_GetDataFormat(I2S_GET_INSTANCE(hi2s));

  /* Set state and reset error code */
  hi2s->global_state     = HAL_I2S_STATE_TX_ACTIVE;
#if defined(USE_HAL_I2S_GET_LAST_ERRORS) && (USE_HAL_I2S_GET_LAST_ERRORS == 1U)
  hi2s->last_error_codes = HAL_I2S_ERROR_NONE;
#endif /* USE_HAL_I2S_GET_LAST_ERRORS */
  hi2s->p_tx_buff  = (const uint16_t *)p_data;
  hi2s->tx_xfer_size  = (uint16_t)transfer_size;
  hi2s->tx_xfer_count = (uint16_t)transfer_size;

  /* Initialize fields not used in handle to zero */
  hi2s->p_rx_buff  = (uint16_t *)NULL;
  hi2s->rx_xfer_size  = (uint16_t) 0U;
  hi2s->rx_xfer_count = (uint16_t) 0U;

  /* Set the function for IT treatment */
  if ((data_format == HAL_I2S_DATA_FORMAT_24_BIT)
      || (data_format == HAL_I2S_DATA_FORMAT_32_BIT))
  {
    hi2s->p_tx_isr = I2S_Transmit_32Bit_IT;
  }
  else
  {
    hi2s->p_tx_isr = I2S_Transmit_16Bit_IT;
  }

  /* Enable I2S peripheral */
  LL_I2S_Enable(I2S_GET_INSTANCE(hi2s));

  LL_I2S_EnableIT_TXP(I2S_GET_INSTANCE(hi2s));

#if defined(USE_HAL_I2S_OVR_UDR_ERRORS) && (USE_HAL_I2S_OVR_UDR_ERRORS == 1U)
  LL_I2S_EnableIT_UDR(I2S_GET_INSTANCE(hi2s));
#endif /* USE_HAL_I2S_OVR_UDR_ERRORS */

  /* Enable TIFRE interrupt if the mode is Slave  */
  if (HAL_I2S_GetMode(hi2s) == HAL_I2S_MODE_SLAVE_TX)
  {
    LL_I2S_EnableIT_FRE(I2S_GET_INSTANCE(hi2s));
  }

  /* Start the transfer */
  LL_I2S_StartTransfer(I2S_GET_INSTANCE(hi2s));

  return HAL_OK;
}

/**
  * @brief  Receive an amount of data in Interrupt mode.
  * @param  hi2s Pointer to a @ref hal_i2s_handle_t
  * @param  p_data Pointer to data buffer
  * @param  transfer_size Amount of data to receive
  * @retval HAL_OK Operation completed successfully
  * @retval HAL_BUSY Concurrent process ongoing
  */
hal_status_t HAL_I2S_Receive_IT(hal_i2s_handle_t *hi2s, void *p_data, uint32_t transfer_size)
{
  hal_i2s_data_format_t data_format;

  /* Check the I2S handle allocation */
  ASSERT_DBG_PARAM(hi2s != NULL);
  ASSERT_DBG_PARAM(p_data != NULL);
  ASSERT_DBG_PARAM(transfer_size != 0U);
#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1U)
  if ((p_data == NULL) || (transfer_size == 0U))
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  /* Check the global state */
  ASSERT_DBG_STATE(hi2s->global_state, HAL_I2S_STATE_IDLE);

#if defined(USE_ASSERT_DBG_PARAM)
  ASSERT_DBG_PARAM(IS_I2S_MODE_RX(HAL_I2S_GetMode(hi2s)));
#endif /* USE_ASSERT_DBG_PARAM */

  HAL_CHECK_UPDATE_STATE(hi2s, global_state, HAL_I2S_STATE_IDLE, HAL_I2S_STATE_RX_ACTIVE);

  data_format = (hal_i2s_data_format_t)LL_I2S_GetDataFormat(I2S_GET_INSTANCE(hi2s));

  /* Set state and reset error code */
  hi2s->global_state = HAL_I2S_STATE_RX_ACTIVE;
#if defined(USE_HAL_I2S_GET_LAST_ERRORS) && (USE_HAL_I2S_GET_LAST_ERRORS == 1U)
  hi2s->last_error_codes = HAL_I2S_ERROR_NONE;
#endif /* USE_HAL_I2S_GET_LAST_ERRORS */
  hi2s->p_rx_buff = (uint16_t *)p_data;
  hi2s->rx_xfer_size = (uint16_t)transfer_size;
  hi2s->rx_xfer_count = (uint16_t)transfer_size;

  /* Initialize fields not used in handle to zero */
  hi2s->p_tx_buff = (uint16_t *)NULL;
  hi2s->tx_xfer_size = (uint16_t)0U;
  hi2s->tx_xfer_count = (uint16_t)0U;

  /* Set the function for IT treatment */
  if ((data_format == HAL_I2S_DATA_FORMAT_24_BIT)
      || (data_format == HAL_I2S_DATA_FORMAT_32_BIT))
  {
    hi2s->p_rx_isr = I2S_Receive_32Bit_IT;
  }
  else
  {
    hi2s->p_rx_isr = I2S_Receive_16Bit_IT;
  }

  /* Enable I2S peripheral */
  LL_I2S_Enable(I2S_GET_INSTANCE(hi2s));

  LL_I2S_EnableIT_RXP(I2S_GET_INSTANCE(hi2s));

#if defined(USE_HAL_I2S_OVR_UDR_ERRORS) && (USE_HAL_I2S_OVR_UDR_ERRORS == 1U)
  LL_I2S_EnableIT_OVR(I2S_GET_INSTANCE(hi2s));
#endif /* USE_HAL_I2S_OVR_UDR_ERRORS */

  /* Enable TIFRE interrupt if the mode is Slave  */
  if (HAL_I2S_GetMode(hi2s) == HAL_I2S_MODE_SLAVE_RX)
  {
    LL_I2S_EnableIT_FRE(I2S_GET_INSTANCE(hi2s));
  }

  /* Start the transfer */
  LL_I2S_StartTransfer(I2S_GET_INSTANCE(hi2s));

  return HAL_OK;
}

/**
  * @brief  Transmit and Receive an amount of data in Interrupt mode.
  * @param  hi2s Pointer to a @ref hal_i2s_handle_t
  * @param  p_tx_data Pointer to data buffer to transmit
  * @param  p_rx_data Pointer to data buffer to receive
  * @param  transfer_size Amount of data to send and receive
  * @retval HAL_OK Operation completed successfully
  * @retval HAL_BUSY Concurrent process ongoing
  */
hal_status_t HAL_I2S_TransmitReceive_IT(hal_i2s_handle_t *hi2s, const void *p_tx_data, void *p_rx_data,
                                        uint32_t transfer_size)
{
  hal_i2s_data_format_t data_format;

  /* Check the I2S handle allocation */
  ASSERT_DBG_PARAM(hi2s != NULL);
  ASSERT_DBG_PARAM(p_tx_data != NULL);
  ASSERT_DBG_PARAM(p_rx_data != NULL);
  ASSERT_DBG_PARAM(transfer_size != 0U);
#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1U)
  if ((p_tx_data == NULL) || (p_rx_data == NULL) || (transfer_size == 0U))
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  /* Check the global state */
  ASSERT_DBG_STATE(hi2s->global_state, HAL_I2S_STATE_IDLE);

#if defined(USE_ASSERT_DBG_PARAM)
  ASSERT_DBG_PARAM(IS_I2S_MODE_FULL_DUPLEX(HAL_I2S_GetMode(hi2s)));
#endif /* USE_ASSERT_DBG_PARAM */

  HAL_CHECK_UPDATE_STATE(hi2s, global_state, HAL_I2S_STATE_IDLE, HAL_I2S_STATE_TX_RX_ACTIVE);

  data_format = (hal_i2s_data_format_t)LL_I2S_GetDataFormat(I2S_GET_INSTANCE(hi2s));

  hi2s->p_tx_buff  = (const uint16_t *)p_tx_data;
  hi2s->p_rx_buff  = (uint16_t *)p_rx_data;

  hi2s->tx_xfer_size  = (uint16_t)transfer_size;
  hi2s->tx_xfer_count = (uint16_t)transfer_size;
  hi2s->rx_xfer_size  = (uint16_t)transfer_size;
  hi2s->rx_xfer_count = (uint16_t)transfer_size;

#if defined(USE_HAL_I2S_GET_LAST_ERRORS) && (USE_HAL_I2S_GET_LAST_ERRORS == 1U)
  hi2s->last_error_codes = HAL_I2S_ERROR_NONE;
#endif /* USE_HAL_I2S_GET_LAST_ERRORS */

  /* Set the function for IT treatment */
  if ((data_format == HAL_I2S_DATA_FORMAT_24_BIT)
      || (data_format == HAL_I2S_DATA_FORMAT_32_BIT))
  {
    hi2s->p_tx_isr = I2S_Transmit_32Bit_IT;
    hi2s->p_rx_isr = I2S_Receive_32Bit_IT;
  }
  else
  {
    hi2s->p_tx_isr = I2S_Transmit_16Bit_IT;
    hi2s->p_rx_isr = I2S_Receive_16Bit_IT;
  }

  /* Enable I2S peripheral */
  LL_I2S_Enable(I2S_GET_INSTANCE(hi2s));

  /* Enable TXP, RXP interrupts */
  LL_I2S_EnableIT(I2S_GET_INSTANCE(hi2s), (LL_I2S_IT_TXP | LL_I2S_IT_RXP | LL_I2S_IT_DXP));

#if defined(USE_HAL_I2S_OVR_UDR_ERRORS) && (USE_HAL_I2S_OVR_UDR_ERRORS == 1U)
  LL_I2S_EnableIT(I2S_GET_INSTANCE(hi2s), (LL_I2S_IT_UDR | LL_I2S_IT_OVR));
#endif /* USE_HAL_I2S_OVR_UDR_ERRORS */

  /* Enable TIFRE interrupt if the mode is Slave  */
  if (HAL_I2S_GetMode(hi2s) == HAL_I2S_MODE_SLAVE_FULL_DUPLEX)
  {
    LL_I2S_EnableIT_FRE(I2S_GET_INSTANCE(hi2s));
  }

  /* Start the transfer */
  LL_I2S_StartTransfer(I2S_GET_INSTANCE(hi2s));

  return HAL_OK;
}

/**
  * @brief  Pause the process in Interrupt mode.
  * @param  hi2s Pointer to a @ref hal_i2s_handle_t
  * @retval HAL_OK Operation completed successfully
  * @retval HAL_ERROR No process ongoing
  */
hal_status_t HAL_I2S_Master_Pause_IT(hal_i2s_handle_t *hi2s)
{
  uint32_t tickstart;
  hal_status_t status;
  hal_i2s_mode_t mode;

  ASSERT_DBG_PARAM(hi2s != NULL);

  hi2s->previous_state = hi2s->global_state;

  /* Check the global state */
  ASSERT_DBG_STATE(hi2s->global_state, HAL_I2S_STATE_TX_ACTIVE | HAL_I2S_STATE_RX_ACTIVE | HAL_I2S_STATE_TX_RX_ACTIVE);

  tickstart = HAL_GetTick();

  mode = HAL_I2S_GetMode(hi2s);

  if (IS_I2S_MODE_MASTER(mode))
  {
    /* Check if there is a transfer ongoing */
    if (LL_I2S_IsActiveTransfer(I2S_GET_INSTANCE(hi2s)) == 1U)
    {
      LL_I2S_SuspendTransfer(I2S_GET_INSTANCE(hi2s));

      while (LL_I2S_IsActiveTransfer(I2S_GET_INSTANCE(hi2s)) != 0U)
      {
        if ((((HAL_GetTick() - tickstart) >= I2S_DEFAULT_TIMEOUT) && (I2S_DEFAULT_TIMEOUT != HAL_MAX_DELAY))
            || (I2S_DEFAULT_TIMEOUT == 0U))
        {
          hi2s->global_state = HAL_I2S_STATE_IDLE;

          return HAL_TIMEOUT;
        }
      }
      LL_I2S_Disable(I2S_GET_INSTANCE(hi2s));

      hi2s->global_state = HAL_I2S_STATE_PAUSED;

      status = HAL_OK;
    }
    else
    {
      /* No ongoing transfer */
      hi2s->global_state = HAL_I2S_STATE_IDLE;

      status = HAL_ERROR;
    }
  }
  else
  {
    hi2s->global_state = HAL_I2S_STATE_IDLE;

    status = HAL_ERROR;
  }

  return status;
}

/**
  * @brief  Resume the process in Interrupt mode.
  * @param  hi2s Pointer to a @ref hal_i2s_handle_t
  * @retval HAL_OK Operation completed successfully
  * @retval HAL_ERROR No process paused
  */
hal_status_t HAL_I2S_Master_Resume_IT(hal_i2s_handle_t *hi2s)
{
  hal_i2s_mode_t mode;

  ASSERT_DBG_PARAM(hi2s != NULL);

  /* Check the global state */
  ASSERT_DBG_STATE(hi2s->global_state, HAL_I2S_STATE_PAUSED);

  HAL_CHECK_UPDATE_STATE(hi2s, global_state, HAL_I2S_STATE_PAUSED,
                         hi2s->previous_state);

  mode = HAL_I2S_GetMode(hi2s);

  if (IS_I2S_MODE_MASTER(mode))
  {
    if (IS_I2S_MODE_FULL_DUPLEX(mode))
    {
      hi2s->global_state = HAL_I2S_STATE_TX_RX_ACTIVE;
    }
    else if (IS_I2S_MODE_TX(mode))
    {
      hi2s->global_state = HAL_I2S_STATE_TX_ACTIVE;
    }
    else
    {
      hi2s->global_state = HAL_I2S_STATE_RX_ACTIVE;
    }

#if defined(USE_HAL_I2S_GET_LAST_ERRORS) && (USE_HAL_I2S_GET_LAST_ERRORS == 1U)
    hi2s->last_error_codes = HAL_I2S_ERROR_NONE;
#endif /* USE_HAL_I2S_GET_LAST_ERRORS */

    LL_I2S_Enable(I2S_GET_INSTANCE(hi2s));

    LL_I2S_StartTransfer(I2S_GET_INSTANCE(hi2s));

    return HAL_OK;
  }
  else
  {
    hi2s->global_state = HAL_I2S_STATE_IDLE;

    return HAL_ERROR;
  }
}


#if defined(USE_HAL_I2S_DMA) && (USE_HAL_I2S_DMA == 1U)
/**
  * @brief  Transmit an amount of data in DMA mode.
  * @param  hi2s Pointer to a @ref hal_i2s_handle_t
  * @param  p_data Pointer to data buffer
  * @param  transfer_size Amount of data to send
  * @retval HAL_OK Operation completed successfully
  * @retval HAL_BUSY Concurrent process ongoing
  * @retval HAL_ERROR Operation completed with error
  */
hal_status_t HAL_I2S_Transmit_DMA(hal_i2s_handle_t *hi2s, const void *p_data, uint32_t transfer_size)
{
  /* Check the I2S handle allocation */
  ASSERT_DBG_PARAM(hi2s != NULL);
  ASSERT_DBG_PARAM(p_data != NULL);
  ASSERT_DBG_PARAM(transfer_size != 0U);
#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1U)
  if ((p_data == NULL) || (transfer_size == 0U))
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  /* Check the global state */
  ASSERT_DBG_STATE(hi2s->global_state, HAL_I2S_STATE_IDLE);

#if defined(USE_ASSERT_DBG_PARAM)
  ASSERT_DBG_PARAM(IS_I2S_MODE_TX(HAL_I2S_GetMode(hi2s)));
#endif /* USE_ASSERT_DBG_PARAM */

  HAL_CHECK_UPDATE_STATE(hi2s, global_state, HAL_I2S_STATE_IDLE, HAL_I2S_STATE_TX_ACTIVE);

  hal_dma_direct_xfer_config_t p_dma_tx_config;
#if defined(USE_HAL_DMA_LINKEDLIST) && (USE_HAL_DMA_LINKEDLIST == 1U)
  hal_dma_node_config_t p_dma_tx_node_config;
  hal_dma_node_type_t p_node_type = HAL_DMA_NODE_LINEAR_ADDRESSING;
#endif /* USE_HAL_DMA_LINKEDLIST */

  hal_i2s_data_format_t data_format = (hal_i2s_data_format_t)LL_I2S_GetDataFormat(I2S_GET_INSTANCE(hi2s));

#if defined(USE_HAL_I2S_GET_LAST_ERRORS) && (USE_HAL_I2S_GET_LAST_ERRORS == 1U)
  hi2s->last_error_codes = HAL_I2S_ERROR_NONE;
#endif /* USE_HAL_I2S_GET_LAST_ERRORS */
  hi2s->p_tx_buff = (const uint16_t *)p_data;
  hi2s->tx_xfer_size = (uint16_t)transfer_size;
  hi2s->tx_xfer_count = (uint16_t)transfer_size;

  /* Initialize fields not used in handle to zero */
  hi2s->p_rx_buff = (uint16_t *)NULL;
  hi2s->rx_xfer_size = (uint16_t)0U;
  hi2s->rx_xfer_count = (uint16_t)0U;
  hi2s->p_rx_isr = NULL;
  hi2s->p_tx_isr = NULL;

  hi2s->hdma_tx->p_xfer_halfcplt_cb = I2S_DMATxHalfCplt;
  hi2s->hdma_tx->p_xfer_cplt_cb = I2S_DMATxCplt;
  hi2s->hdma_tx->p_xfer_error_cb = I2S_DMAError;

#if defined (USE_HAL_DMA_LINKEDLIST) && (USE_HAL_DMA_LINKEDLIST == 1U)
  if (hi2s->hdma_tx->xfer_mode == HAL_DMA_XFER_MODE_LINKEDLIST_CIRCULAR)
  {
    /* Get DMA channel circular transfer configuration */
    HAL_DMA_GetNodeConfig(hi2s->hdma_tx->p_head_node, &p_dma_tx_node_config, &p_node_type);
    p_dma_tx_config.src_data_width = p_dma_tx_node_config.xfer.src_data_width;
  }
  else
  {
    /* Get DMA channel direct transfer configuration */
    HAL_DMA_GetConfigDirectXfer(hi2s->hdma_tx, &p_dma_tx_config);
  }
#else
  HAL_DMA_GetConfigDirectXfer(hi2s->hdma_tx, &p_dma_tx_config);
#endif /* USE_HAL_DMA_LINKEDLIST */

  if (((data_format == HAL_I2S_DATA_FORMAT_16_BIT)
       && (p_dma_tx_config.src_data_width != HAL_DMA_SRC_DATA_WIDTH_HALFWORD))
      || ((data_format == HAL_I2S_DATA_FORMAT_16_BIT_EXTENDED)
          && (p_dma_tx_config.src_data_width != HAL_DMA_SRC_DATA_WIDTH_HALFWORD))
      || ((data_format == HAL_I2S_DATA_FORMAT_24_BIT)
          && (p_dma_tx_config.src_data_width != HAL_DMA_SRC_DATA_WIDTH_WORD))
      || ((data_format == HAL_I2S_DATA_FORMAT_32_BIT)
          && (p_dma_tx_config.src_data_width != HAL_DMA_SRC_DATA_WIDTH_WORD)))
  {
#if defined(USE_HAL_I2S_GET_LAST_ERRORS) &&(USE_HAL_I2S_GET_LAST_ERRORS == 1U)
    hi2s->last_error_codes = HAL_I2S_ERROR_DMA;
#endif /* USE_HAL_I2S_GET_LAST_ERRORS */
    hi2s->global_state = HAL_I2S_STATE_IDLE;
    return HAL_ERROR;
  }

  if ((data_format == HAL_I2S_DATA_FORMAT_16_BIT) || (data_format == HAL_I2S_DATA_FORMAT_16_BIT_EXTENDED))
  {
    hi2s->tx_xfer_count = (uint16_t)(transfer_size * 2U);
  }
  else
  {
    hi2s->tx_xfer_count = (uint16_t)(transfer_size * 4U);
  }

  if (HAL_DMA_StartPeriphXfer_IT_Opt(hi2s->hdma_tx,
                                     (uint32_t)hi2s->p_tx_buff,
                                     (uint32_t) &((SPI_TypeDef *)((uint32_t)hi2s->instance))->TXDR,
                                     hi2s->tx_xfer_count, HAL_DMA_OPT_IT_DEFAULT) != HAL_OK)
  {
#if defined(USE_HAL_I2S_GET_LAST_ERRORS) &&(USE_HAL_I2S_GET_LAST_ERRORS == 1U)
    hi2s->last_error_codes = HAL_I2S_ERROR_DMA;
#endif /* USE_HAL_I2S_GET_LAST_ERRORS */
    hi2s->global_state = HAL_I2S_STATE_IDLE;
    return HAL_ERROR;
  }

  if (STM32_IS_BIT_CLR(I2S_GET_INSTANCE(hi2s)->CFG1, SPI_CFG1_TXDMAEN))
  {
    LL_I2S_EnableDMAReq_TX(I2S_GET_INSTANCE(hi2s));
  }

  LL_I2S_Enable(I2S_GET_INSTANCE(hi2s));

  LL_I2S_StartTransfer(I2S_GET_INSTANCE(hi2s));

  return HAL_OK;
}

/**
  * @brief  Receive an amount of data in DMA mode.
  * @param  hi2s Pointer to a @ref hal_i2s_handle_t
  * @param  p_data Pointer to data buffer
  * @param  transfer_size Amount of data to receive
  * @retval HAL_OK Operation completed successfully
  * @retval HAL_BUSY Concurrent process ongoing
  * @retval HAL_ERROR Operation completed with error
  */
hal_status_t HAL_I2S_Receive_DMA(hal_i2s_handle_t *hi2s, void *p_data, uint32_t transfer_size)
{
  /* Check the I2S allocation */
  ASSERT_DBG_PARAM(hi2s != NULL);
  ASSERT_DBG_PARAM(p_data != NULL);
  ASSERT_DBG_PARAM(transfer_size != 0U);
#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1U)
  if ((p_data == NULL) || (transfer_size == 0U))
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  /* Check the global state */
  ASSERT_DBG_STATE(hi2s->global_state, HAL_I2S_STATE_IDLE);

#if defined(USE_ASSERT_DBG_PARAM)
  ASSERT_DBG_PARAM(IS_I2S_MODE_RX(HAL_I2S_GetMode(hi2s)));
#endif /* USE_ASSERT_DBG_PARAM */

  HAL_CHECK_UPDATE_STATE(hi2s, global_state, HAL_I2S_STATE_IDLE, HAL_I2S_STATE_RX_ACTIVE);

  hal_dma_direct_xfer_config_t p_dma_rx_config;
#if defined (USE_HAL_DMA_LINKEDLIST) && (USE_HAL_DMA_LINKEDLIST == 1U)
  hal_dma_node_config_t p_dma_rx_node_config;
  hal_dma_node_type_t  p_node_type = HAL_DMA_NODE_LINEAR_ADDRESSING;
#endif /* USE_HAL_DMA_LINKEDLIST */
  hal_i2s_data_format_t data_format = (hal_i2s_data_format_t)LL_I2S_GetDataFormat(I2S_GET_INSTANCE(hi2s));

#if defined(USE_HAL_I2S_GET_LAST_ERRORS) && (USE_HAL_I2S_GET_LAST_ERRORS == 1U)
  hi2s->last_error_codes = HAL_I2S_ERROR_NONE;
#endif /* USE_HAL_I2S_GET_LAST_ERRORS */
  hi2s->p_rx_buff = (uint16_t *)p_data;
  hi2s->rx_xfer_size = (uint16_t)transfer_size;
  hi2s->rx_xfer_count = (uint16_t)transfer_size;

  /* Initialize fields not used in handle to zero */
  hi2s->p_tx_buff = (uint16_t *)NULL;
  hi2s->tx_xfer_size = (uint16_t)0U;
  hi2s->tx_xfer_count = (uint16_t)0U;
  hi2s->p_rx_isr = NULL;
  hi2s->p_tx_isr = NULL;

  hi2s->hdma_rx->p_xfer_halfcplt_cb = I2S_DMARxHalfCplt;
  hi2s->hdma_rx->p_xfer_cplt_cb = I2S_DMARxCplt;
  hi2s->hdma_rx->p_xfer_error_cb = I2S_DMAError;

  if ((data_format == HAL_I2S_DATA_FORMAT_16_BIT) || (data_format == HAL_I2S_DATA_FORMAT_16_BIT_EXTENDED))
  {
    hi2s->rx_xfer_count = (uint16_t)(transfer_size * 2U);
  }
  else
  {
    hi2s->rx_xfer_count = (uint16_t)(transfer_size * 4U);
  }

#if defined (USE_HAL_DMA_LINKEDLIST) && (USE_HAL_DMA_LINKEDLIST == 1U)
  if (hi2s->hdma_rx->xfer_mode == HAL_DMA_XFER_MODE_LINKEDLIST_CIRCULAR)
  {
    /* Get DMA channel circular transfer configuration */
    HAL_DMA_GetNodeConfig(hi2s->hdma_rx->p_head_node, &p_dma_rx_node_config, &p_node_type);
    p_dma_rx_config.dest_data_width = p_dma_rx_node_config.xfer.dest_data_width;
  }
  else
  {
    /* Get DMA channel direct transfer configuration */
    HAL_DMA_GetConfigDirectXfer(hi2s->hdma_rx, &p_dma_rx_config);
  }
#else
  HAL_DMA_GetConfigDirectXfer(hi2s->hdma_rx, &p_dma_rx_config);
#endif /* USE_HAL_DMA_LINKEDLIST */

  if (((data_format == HAL_I2S_DATA_FORMAT_16_BIT)
       && (p_dma_rx_config.dest_data_width != HAL_DMA_DEST_DATA_WIDTH_HALFWORD))
      || ((data_format == HAL_I2S_DATA_FORMAT_16_BIT_EXTENDED)
          && (p_dma_rx_config.dest_data_width != HAL_DMA_DEST_DATA_WIDTH_HALFWORD))
      || ((data_format == HAL_I2S_DATA_FORMAT_24_BIT)
          && (p_dma_rx_config.dest_data_width != HAL_DMA_DEST_DATA_WIDTH_WORD))
      || ((data_format == HAL_I2S_DATA_FORMAT_32_BIT)
          && (p_dma_rx_config.dest_data_width != HAL_DMA_DEST_DATA_WIDTH_WORD)))
  {
#if defined(USE_HAL_I2S_GET_LAST_ERRORS) &&(USE_HAL_I2S_GET_LAST_ERRORS == 1U)
    hi2s->last_error_codes = HAL_I2S_ERROR_DMA;
#endif /* USE_HAL_I2S_GET_LAST_ERRORS */
    hi2s->global_state = HAL_I2S_STATE_IDLE;
    return HAL_ERROR;
  }

  if (HAL_DMA_StartPeriphXfer_IT_Opt(hi2s->hdma_rx,
                                     (uint32_t) &((SPI_TypeDef *)((uint32_t)hi2s->instance))->RXDR,
                                     (uint32_t)hi2s->p_rx_buff,
                                     hi2s->rx_xfer_count, HAL_DMA_OPT_IT_DEFAULT) != HAL_OK)
  {
#if defined(USE_HAL_I2S_GET_LAST_ERRORS) &&(USE_HAL_I2S_GET_LAST_ERRORS == 1U)
    hi2s->last_error_codes = HAL_I2S_ERROR_DMA;
#endif /* USE_HAL_I2S_GET_LAST_ERRORS */
    hi2s->global_state = HAL_I2S_STATE_IDLE;
    return HAL_ERROR;
  }

  if (STM32_IS_BIT_CLR(I2S_GET_INSTANCE(hi2s)->CFG1, SPI_CFG1_RXDMAEN))
  {
    LL_I2S_EnableDMAReq_RX(I2S_GET_INSTANCE(hi2s));
  }

  LL_I2S_Enable(I2S_GET_INSTANCE(hi2s));

  LL_I2S_StartTransfer(I2S_GET_INSTANCE(hi2s));

  return HAL_OK;
}

/**
  * @brief  Transmit and Receive an amount of data in DMA mode.
  * @param  hi2s Pointer to a @ref hal_i2s_handle_t
  * @param  p_tx_data Pointer to data buffer to transmit
  * @param  p_rx_data Pointer to data buffer to receive
  * @param  transfer_size Amount of data to send and receive
  * @retval HAL_OK Operation completed successfully
  * @retval HAL_BUSY Concurrent process ongoing
  * @retval HAL_ERROR Operation completed with error
  */
hal_status_t HAL_I2S_TransmitReceive_DMA(hal_i2s_handle_t *hi2s, const void *p_tx_data, void *p_rx_data,
                                         uint32_t transfer_size)
{
  /* Check the I2S handle allocation */
  ASSERT_DBG_PARAM(hi2s != NULL);
  ASSERT_DBG_PARAM(p_tx_data != NULL);
  ASSERT_DBG_PARAM(p_rx_data != NULL);
  ASSERT_DBG_PARAM(transfer_size != 0U);
#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1U)
  if ((p_tx_data == NULL) || (p_rx_data == NULL) || (transfer_size == 0U))
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  /* Check the global state */
  ASSERT_DBG_STATE(hi2s->global_state, HAL_I2S_STATE_IDLE);

#if defined(USE_ASSERT_DBG_PARAM)
  ASSERT_DBG_PARAM(IS_I2S_MODE_FULL_DUPLEX(HAL_I2S_GetMode(hi2s)));
#endif /* USE_ASSERT_DBG_PARAM */

  HAL_CHECK_UPDATE_STATE(hi2s, global_state, HAL_I2S_STATE_IDLE, HAL_I2S_STATE_TX_RX_ACTIVE);

  hal_dma_direct_xfer_config_t p_dma_rx_config;
  hal_dma_direct_xfer_config_t p_dma_tx_config;
#if defined (USE_HAL_DMA_LINKEDLIST) && (USE_HAL_DMA_LINKEDLIST == 1U)
  hal_dma_node_config_t p_dma_rx_node_config;
  hal_dma_node_config_t p_dma_tx_node_config;
  hal_dma_node_type_t  p_node_type = HAL_DMA_NODE_LINEAR_ADDRESSING;
#endif /* USE_HAL_DMA_LINKEDLIST */
  hal_i2s_data_format_t data_format = (hal_i2s_data_format_t)LL_I2S_GetDataFormat(I2S_GET_INSTANCE(hi2s));

  hi2s->p_tx_buff = (const uint16_t *)p_tx_data;
  hi2s->p_rx_buff = (uint16_t *)p_rx_data;

  hi2s->tx_xfer_count = (uint16_t)transfer_size;
  hi2s->tx_xfer_size = (uint16_t)transfer_size;
  hi2s->rx_xfer_count = (uint16_t)transfer_size;
  hi2s->rx_xfer_size = (uint16_t)transfer_size;
#if defined(USE_HAL_I2S_GET_LAST_ERRORS) &&(USE_HAL_I2S_GET_LAST_ERRORS == 1U)
  hi2s->last_error_codes = HAL_I2S_ERROR_NONE;
#endif /* USE_HAL_I2S_GET_LAST_ERRORS */

  LL_I2S_DisableDMAReq_TX(I2S_GET_INSTANCE(hi2s));
  LL_I2S_DisableDMAReq_RX(I2S_GET_INSTANCE(hi2s));

  hi2s->hdma_rx->p_xfer_halfcplt_cb = I2S_DMATxRxHalfCplt;
  hi2s->hdma_rx->p_xfer_cplt_cb = I2S_DMATxRxCplt;
  hi2s->hdma_rx->p_xfer_error_cb = I2S_DMAError;

#if defined (USE_HAL_DMA_LINKEDLIST) && (USE_HAL_DMA_LINKEDLIST == 1U)
  if (hi2s->hdma_tx->xfer_mode == HAL_DMA_XFER_MODE_LINKEDLIST_CIRCULAR)
  {
    /* Get DMA channel circular transfer configuration */
    HAL_DMA_GetNodeConfig(hi2s->hdma_tx->p_head_node, &p_dma_tx_node_config, &p_node_type);
    p_dma_tx_config.src_data_width = p_dma_tx_node_config.xfer.src_data_width;
  }
  else
  {
    /* Get DMA channel direct transfer configuration */
    HAL_DMA_GetConfigDirectXfer(hi2s->hdma_tx, &p_dma_tx_config);
  }

  if (hi2s->hdma_rx->xfer_mode == HAL_DMA_XFER_MODE_LINKEDLIST_CIRCULAR)
  {
    /* Get DMA channel circular transfer configuration */
    HAL_DMA_GetNodeConfig(hi2s->hdma_rx->p_head_node, &p_dma_rx_node_config, &p_node_type);
    p_dma_rx_config.dest_data_width = p_dma_rx_node_config.xfer.dest_data_width;
  }
  else
  {
    /* Get DMA channel direct transfer configuration */
    HAL_DMA_GetConfigDirectXfer(hi2s->hdma_rx, &p_dma_rx_config);
  }

#else
  HAL_DMA_GetConfigDirectXfer(hi2s->hdma_tx, &p_dma_tx_config);
  HAL_DMA_GetConfigDirectXfer(hi2s->hdma_rx, &p_dma_rx_config);
#endif /* USE_HAL_DMA_LINKEDLIST */

  if (((data_format == HAL_I2S_DATA_FORMAT_16_BIT)
       && (p_dma_rx_config.dest_data_width != HAL_DMA_DEST_DATA_WIDTH_HALFWORD))
      || ((data_format == HAL_I2S_DATA_FORMAT_16_BIT)
          && (p_dma_tx_config.src_data_width != HAL_DMA_SRC_DATA_WIDTH_HALFWORD))
      || ((data_format == HAL_I2S_DATA_FORMAT_16_BIT_EXTENDED)
          && (p_dma_rx_config.dest_data_width != HAL_DMA_DEST_DATA_WIDTH_HALFWORD))
      || ((data_format == HAL_I2S_DATA_FORMAT_16_BIT_EXTENDED)
          && (p_dma_tx_config.src_data_width != HAL_DMA_SRC_DATA_WIDTH_HALFWORD))
      || ((data_format == HAL_I2S_DATA_FORMAT_24_BIT)
          && (p_dma_rx_config.dest_data_width != HAL_DMA_DEST_DATA_WIDTH_WORD))
      || ((data_format == HAL_I2S_DATA_FORMAT_24_BIT)
          && (p_dma_tx_config.src_data_width != HAL_DMA_SRC_DATA_WIDTH_WORD))
      || ((data_format == HAL_I2S_DATA_FORMAT_32_BIT)
          && (p_dma_rx_config.dest_data_width != HAL_DMA_DEST_DATA_WIDTH_WORD))
      || ((data_format == HAL_I2S_DATA_FORMAT_32_BIT)
          && (p_dma_tx_config.src_data_width != HAL_DMA_SRC_DATA_WIDTH_WORD)))
  {
#if defined(USE_HAL_I2S_GET_LAST_ERRORS) &&(USE_HAL_I2S_GET_LAST_ERRORS == 1U)
    hi2s->last_error_codes = HAL_I2S_ERROR_DMA;
#endif /* USE_HAL_I2S_GET_LAST_ERRORS */
    hi2s->global_state = HAL_I2S_STATE_IDLE;
    return HAL_ERROR;
  }

  if ((data_format == HAL_I2S_DATA_FORMAT_16_BIT) || (data_format == HAL_I2S_DATA_FORMAT_16_BIT_EXTENDED))
  {
    hi2s->tx_xfer_count = (uint16_t)(transfer_size * 2U);
  }
  else
  {
    hi2s->tx_xfer_count = (uint16_t)(transfer_size * 4U);
  }

  if (HAL_DMA_StartPeriphXfer_IT_Opt(hi2s->hdma_tx,
                                     (uint32_t)hi2s->p_tx_buff,
                                     (uint32_t) &((SPI_TypeDef *)((uint32_t)hi2s->instance))->TXDR,
                                     hi2s->tx_xfer_count, HAL_DMA_OPT_IT_DEFAULT) != HAL_OK)
  {
#if defined(USE_HAL_I2S_GET_LAST_ERRORS) &&(USE_HAL_I2S_GET_LAST_ERRORS == 1U)
    hi2s->last_error_codes = HAL_I2S_ERROR_DMA;
#endif /* USE_HAL_I2S_GET_LAST_ERRORS */
    hi2s->global_state = HAL_I2S_STATE_IDLE;
    return HAL_ERROR;
  }

  if (STM32_IS_BIT_CLR(I2S_GET_INSTANCE(hi2s)->CFG1, SPI_CFG1_TXDMAEN))
  {
    LL_I2S_EnableDMAReq_TX(I2S_GET_INSTANCE(hi2s));
  }


  if ((data_format == HAL_I2S_DATA_FORMAT_16_BIT) || (data_format == HAL_I2S_DATA_FORMAT_16_BIT_EXTENDED))
  {
    hi2s->rx_xfer_count = (uint16_t)(transfer_size * 2U);
  }
  else
  {
    hi2s->rx_xfer_count = (uint16_t)(transfer_size * 4U);
  }

  if (HAL_DMA_StartPeriphXfer_IT_Opt(hi2s->hdma_rx,
                                     (uint32_t) &((SPI_TypeDef *)((uint32_t)hi2s->instance))->RXDR,
                                     (uint32_t)hi2s->p_rx_buff,
                                     hi2s->rx_xfer_count, HAL_DMA_OPT_IT_DEFAULT) != HAL_OK)
  {
#if defined(USE_HAL_I2S_GET_LAST_ERRORS) &&(USE_HAL_I2S_GET_LAST_ERRORS == 1U)
    hi2s->last_error_codes = HAL_I2S_ERROR_DMA;
#endif /* USE_HAL_I2S_GET_LAST_ERRORS */
    hi2s->global_state = HAL_I2S_STATE_IDLE;
    return HAL_ERROR;
  }

  if (STM32_IS_BIT_CLR(I2S_GET_INSTANCE(hi2s)->CFG1, SPI_CFG1_RXDMAEN))
  {
    LL_I2S_EnableDMAReq_RX(I2S_GET_INSTANCE(hi2s));
  }

  LL_I2S_Enable(I2S_GET_INSTANCE(hi2s));

  LL_I2S_StartTransfer(I2S_GET_INSTANCE(hi2s));

  return HAL_OK;
}

/**
  * @brief  Pause the process in DMA mode.
  * @param  hi2s Pointer to hal_i2s_handle_t
  * @retval HAL_OK Operation completed successfully
  * @retval HAL_ERROR No process ongoing
  */
hal_status_t HAL_I2S_Master_Pause_DMA(hal_i2s_handle_t *hi2s)
{
  ASSERT_DBG_PARAM(hi2s != NULL);

  hi2s->previous_state = hi2s->global_state;

  /* Check the global state */
  ASSERT_DBG_STATE(hi2s->global_state, HAL_I2S_STATE_TX_ACTIVE | HAL_I2S_STATE_RX_ACTIVE | HAL_I2S_STATE_TX_RX_ACTIVE);
  return HAL_OK;
}

/**
  * @brief  Resume the process in DMA mode.
  * @param  hi2s Pointer to a @ref hal_i2s_handle_t
  * @retval HAL_OK Operation completed successfully
  * @retval HAL_ERROR No process ongoing
  */
hal_status_t HAL_I2S_Master_Resume_DMA(hal_i2s_handle_t *hi2s)
{
  ASSERT_DBG_PARAM(hi2s != NULL);

  /* Check the global state */
  ASSERT_DBG_STATE(hi2s->global_state, HAL_I2S_STATE_PAUSED);

  HAL_CHECK_UPDATE_STATE(hi2s, global_state, HAL_I2S_STATE_PAUSED,
                         hi2s->previous_state);

  return HAL_OK;
}
#endif /* USE_HAL_I2S_DMA */

/**
  * @brief  Abort ongoing transfer in blocking mode.
  * @param  hi2s Pointer to a @ref hal_i2s_handle_t
  * @retval HAL_OK Operation completed successfully.
  * @retval HAL_ERROR Operation completed with error.
  */
hal_status_t HAL_I2S_Abort(hal_i2s_handle_t *hi2s)
{
  hal_status_t errorcode = HAL_OK;

  volatile uint32_t count;

  /* Check the I2S handle allocation */
  ASSERT_DBG_PARAM(hi2s != NULL);

  /* Check the state */
  ASSERT_DBG_STATE(hi2s->global_state, HAL_I2S_STATE_TX_ACTIVE | HAL_I2S_STATE_RX_ACTIVE
                   | HAL_I2S_STATE_TX_RX_ACTIVE | HAL_I2S_STATE_PAUSED);

  /* Set I2S global state to aborting to avoid any interaction */
  hi2s->global_state = HAL_I2S_STATE_ABORT;

  count = I2S_DEFAULT_TIMEOUT * (SystemCoreClock / 24U / 1000U);

  if (LL_I2S_IsActiveTransfer(I2S_GET_INSTANCE(hi2s)) == 1U)
  {
    /* Request a suspend transfer */
    LL_I2S_SuspendTransfer(I2S_GET_INSTANCE(hi2s));

    do
    {
      count--;

      if (count == 0U)
      {
        errorcode = HAL_ERROR;
        break;
      }
    } while (LL_I2S_IsActiveTransfer(I2S_GET_INSTANCE(hi2s)) == 1U);

    /* Clear SUSP flag */
    LL_I2S_ClearFlag_SUSP(I2S_GET_INSTANCE(hi2s));

    do
    {
      count--;

      if (count == 0U)
      {
        errorcode = HAL_ERROR;
        break;
      }
    } while (LL_I2S_IsActiveFlag_SUSP(I2S_GET_INSTANCE(hi2s)) == 1U);
  }

#if defined(USE_HAL_I2S_DMA) && (USE_HAL_I2S_DMA == 1U)
  /* Disable the I2S DMA Tx request if enabled */
  if (LL_I2S_IsEnabledDMAReq_TX(I2S_GET_INSTANCE(hi2s)) == 1U)
  {
    if (hi2s->hdma_tx != NULL)
    {
      /* Abort the I2S DMA Tx Stream/Channel: use blocking DMA Abort API (no callback) */
      hi2s->hdma_tx->p_xfer_abort_cb = NULL;

      /* Abort DMA Tx handle linked to I2S peripheral */
      if (HAL_DMA_Abort(hi2s->hdma_tx) != HAL_OK)
      {
        errorcode = HAL_ERROR;
      }
    }
  }

  /* Disable the I2S DMA Rx request if enabled */
  if (LL_I2S_IsEnabledDMAReq_RX(I2S_GET_INSTANCE(hi2s)) == 1U)
  {
    if (hi2s->hdma_rx != NULL)
    {
      /* Abort the I2S DMA Rx Stream/Channel: use blocking DMA Abort API (no callback) */
      hi2s->hdma_rx->p_xfer_abort_cb = NULL;

      /* Abort DMA Rx handle linked to I2S peripheral */
      if (HAL_DMA_Abort(hi2s->hdma_rx) != HAL_OK)
      {
        errorcode = HAL_ERROR;
      }
    }
  }
#endif /* USE_HAL_I2S_DMA */

  I2S_AbortTransfer(hi2s);

  /* Restore hi2s state */
  hi2s->global_state = HAL_I2S_STATE_IDLE;

  return errorcode;
}

/**
  * @brief  Abort ongoing transfer in no-blocking mode.
  * @param  hi2s Pointer to a @ref hal_i2s_handle_t
  * @retval HAL_OK Operation completed successfully.
  * @retval HAL_ERROR Operation completed with error.
  */
hal_status_t HAL_I2S_Abort_IT(hal_i2s_handle_t *hi2s)
{
  hal_status_t errorcode = HAL_OK;

  volatile uint32_t count;

  /* Check the I2S handle allocation */
  ASSERT_DBG_PARAM(hi2s != NULL);

  /* Check the state */
  ASSERT_DBG_STATE(hi2s->global_state, HAL_I2S_STATE_TX_ACTIVE | HAL_I2S_STATE_RX_ACTIVE
                   | HAL_I2S_STATE_TX_RX_ACTIVE | HAL_I2S_STATE_PAUSED);

  /* Set I2S global state to aborting to avoid any interaction */
  hi2s->global_state = HAL_I2S_STATE_ABORT;

  count = I2S_DEFAULT_TIMEOUT * (SystemCoreClock / 24U / 1000U);

  if (LL_I2S_IsActiveTransfer(I2S_GET_INSTANCE(hi2s)) == 1U)
  {
    /* Request a suspend transfer */
    LL_I2S_SuspendTransfer(I2S_GET_INSTANCE(hi2s));

    do
    {
      count--;

      if (count == 0U)
      {
        errorcode = HAL_ERROR;
        break;
      }
    } while (LL_I2S_IsActiveTransfer(I2S_GET_INSTANCE(hi2s)) == 1U);

    /* Clear SUSP flag */
    LL_I2S_ClearFlag_SUSP(I2S_GET_INSTANCE(hi2s));

    do
    {
      count--;

      if (count == 0U)
      {
        errorcode = HAL_ERROR;
        break;
      }
    } while (LL_I2S_IsActiveFlag_SUSP(I2S_GET_INSTANCE(hi2s)) == 1U);
  }

#if defined(USE_HAL_I2S_DMA) && (USE_HAL_I2S_DMA == 1U)
  /* If DMA Tx and/or DMA Rx handles are associated to I2S handle, DMA Abort complete callbacks must be initialized
     before any call to DMA Abort functions */
  if (hi2s->hdma_tx != NULL)
  {
    if (LL_I2S_IsEnabledDMAReq_TX(I2S_GET_INSTANCE(hi2s)) == 1U)
    {
      /* Set DMA Abort complete callback if I2S DMA Tx request is enabled */
      hi2s->hdma_tx->p_xfer_abort_cb = I2S_DMATxAbortCallback;

      /* Abort DMA Tx handle linked to I2S peripheral */
      if (HAL_DMA_Abort_IT(hi2s->hdma_tx) != HAL_OK)
      {
        errorcode = HAL_ERROR;
      }
    }
    else
    {
      hi2s->hdma_tx->p_xfer_abort_cb = NULL;
    }
  }

  if (hi2s->hdma_rx != NULL)
  {
    if (LL_I2S_IsEnabledDMAReq_RX(I2S_GET_INSTANCE(hi2s)) == 1U)
    {
      /* Set DMA Abort complete callback if I2S DMA Rx request is enabled */
      hi2s->hdma_rx->p_xfer_abort_cb = I2S_DMARxAbortCallback;

      /* Abort DMA Rx handle linked to I2S peripheral */
      if (HAL_DMA_Abort_IT(hi2s->hdma_rx) != HAL_OK)
      {
        errorcode = HAL_ERROR;
      }
    }
    else
    {
      hi2s->hdma_rx->p_xfer_abort_cb = NULL;
    }
  }
#endif /* USE_HAL_I2S_DMA */

  /* Proceed with abort procedure */
  I2S_AbortTransfer(hi2s);

  /* Restore I2S state */
  hi2s->global_state = HAL_I2S_STATE_IDLE;

  /* Call user Abort complete callback */
#if defined(USE_HAL_I2S_REGISTER_CALLBACKS) && (USE_HAL_I2S_REGISTER_CALLBACKS == 1U)
  hi2s->p_abort_cplt_cb(hi2s);
#else
  HAL_I2S_AbortCpltCallback(hi2s);
#endif /* USE_HAL_I2S_REGISTER_CALLBACKS */

  return errorcode;
}
/**
  * @}
  */

/** @defgroup I2S_Exported_Functions_Group6 IRQ handler/callbacks/register callbacks functions
  * @{
  * This subsection provides a set of functions allowing to register the I2S process and error callbacks:
  *  - The function HAL_I2S_IRQHandler() to handle all I2S interrupts
  *
  * There are two ways to use callbacks:
  * Override weak callbacks functions:
  *  - Call the function HAL_I2S_ErrorCallback() to indicate invalidate operation is completed
  *  - Call the function HAL_I2S_TxCpltCallback() to indicate Tx transfer is completed
  *  - Call the function HAL_I2S_RxCpltCallback() to indicate Rx transfer is completed
  *  - Call the function HAL_I2S_TxRxCpltCallback() to indicate Tx/Rx transfer is completed
  *  - Call the function HAL_I2S_TxHalfCpltCallback() to indicate Tx half transfer is completed
  *  - Call the function HAL_I2S_RxHalfCpltCallback() to indicate Rx half transfer is completed
  *  - Call the function HAL_I2S_TxRxHalfCpltCallback() to indicate Tx/Rx half transfer is completed
  *  - Call the function HAL_I2S_AbortCpltCallback() to indicate Abort operation is completed
  *
  * Register callbacks user:
  *  - Call the function HAL_I2S_RegisterErrorCallback() to register the Error callback
  *  - Call the function HAL_I2S_RegisterTxCpltCallback() to register the Tx transfer complete callback
  *  - Call the function HAL_I2S_RegisterRxCpltCallback() to register the Rx transfer complete callback
  *  - Call the function HAL_I2S_RegisterTxRxCpltCallback() to register the Tx/Rx transfer complete callback
  *  - Call the function HAL_I2S_RegisterTxHalfCpltCallback() to register the Tx half transfer complete callback
  *  - Call the function HAL_I2S_RegisterRxHalfCpltCallback() to register the Rx half transfer complete callback
  *  - Call the function HAL_I2S_RegisterTxRxHalfCpltCallback() to register the Tx/Rx half transfer complete callback
  *  - Call the function HAL_I2S_RegisterAbortCpltCallback() to register the Abort operation complete callback
  */

/**
  * @brief Handle I2S interrupt request.
  * @param hi2s Pointer to hal_i2s_handle_t
  */
void HAL_I2S_IRQHandler(hal_i2s_handle_t *hi2s)
{
  uint32_t i2sier   = I2S_GET_INSTANCE(hi2s)->IER;
  uint32_t i2ssr    = I2S_GET_INSTANCE(hi2s)->SR;
  uint32_t trigger  = i2sier & i2ssr;

  if (STM32_IS_BIT_SET(trigger, LL_I2S_FLAG_DXP))
  {
    hi2s->p_tx_isr(hi2s);
    hi2s->p_rx_isr(hi2s);
  }

  if (STM32_IS_BIT_SET(trigger, LL_I2S_FLAG_RXP) && STM32_IS_BIT_CLR(trigger, LL_I2S_FLAG_DXP))
  {
    hi2s->p_rx_isr(hi2s);
  }

  if (STM32_IS_BIT_SET(trigger, LL_I2S_FLAG_TXP) && STM32_IS_BIT_CLR(trigger, LL_I2S_FLAG_DXP))
  {
    hi2s->p_tx_isr(hi2s);
  }

#if defined(USE_HAL_I2S_OVR_UDR_ERRORS) && (USE_HAL_I2S_OVR_UDR_ERRORS == 1U)
  if (STM32_IS_BIT_SET(trigger, LL_I2S_FLAG_UDR))
  {
    LL_I2S_DisableIT(I2S_GET_INSTANCE(hi2s), (LL_I2S_IT_TXP | LL_I2S_IT_RXP | LL_I2S_IT_UDR
                                              | LL_I2S_IT_OVR | LL_I2S_IT_TIFRE));

    LL_I2S_ClearFlag_UDR(I2S_GET_INSTANCE(hi2s));

    hi2s->global_state = HAL_I2S_STATE_IDLE;

#if defined(USE_HAL_I2S_GET_LAST_ERRORS) && (USE_HAL_I2S_GET_LAST_ERRORS == 1U)
    STM32_SET_BIT(hi2s->last_error_codes, HAL_I2S_ERROR_UDR);
#endif /* USE_HAL_I2S_GET_LAST_ERRORS */
#if (USE_HAL_I2S_REGISTER_CALLBACKS == 1U)
    hi2s->p_error_cb(hi2s);
#else
    HAL_I2S_ErrorCallback(hi2s);
#endif /* USE_HAL_I2S_REGISTER_CALLBACKS */
  }

  /* I2S Overrun error interrupt occurred */
  if (STM32_IS_BIT_SET(trigger, LL_I2S_FLAG_OVR))
  {
    LL_I2S_DisableIT(I2S_GET_INSTANCE(hi2s), (LL_I2S_IT_TXP | LL_I2S_IT_RXP | LL_I2S_IT_UDR
                                              | LL_I2S_IT_OVR | LL_I2S_IT_TIFRE));

    LL_I2S_ClearFlag_OVR(I2S_GET_INSTANCE(hi2s));

    hi2s->global_state = HAL_I2S_STATE_IDLE;

#if defined(USE_HAL_I2S_GET_LAST_ERRORS) && (USE_HAL_I2S_GET_LAST_ERRORS == 1U)
    STM32_SET_BIT(hi2s->last_error_codes, HAL_I2S_ERROR_OVR);
#endif /* USE_HAL_I2S_GET_LAST_ERRORS */
#if (USE_HAL_I2S_REGISTER_CALLBACKS == 1UL)
    hi2s->p_error_cb(hi2s);
#else
    HAL_I2S_ErrorCallback(hi2s);
#endif /* USE_HAL_I2S_REGISTER_CALLBACKS */
  }
#endif /* USE_HAL_I2S_OVR_UDR_ERRORS */
}

/**
  * @brief I2S Error callback.
  * @param hi2s Pointer to hal_i2s_handle_t
  */
__weak void HAL_I2S_ErrorCallback(hal_i2s_handle_t *hi2s)
{
  /* Check the I2S handle allocation */
  ASSERT_DBG_PARAM(hi2s != NULL);

  /* Prevent unused argument(s) compilation warning */
  STM32_UNUSED(hi2s);

  /* NOTE : This function must not be modified, when the callback is needed,
            the HAL_I2S_ErrorCallback must be implemented in the user file
   */
  /* NOTE : The ErrorCode parameter in the hi2s handle is updated by the I2S processes
            and user can use HAL_I2S_GetError() API to check the latest error occurred.
   */
}

/**
  * @brief Tx transfer complete callback.
  * @param hi2s Pointer to hal_i2s_handle_t
  */
__weak void HAL_I2S_TxCpltCallback(hal_i2s_handle_t *hi2s)
{
  /* Check the I2S handle allocation */
  ASSERT_DBG_PARAM(hi2s != NULL);

  /* Prevent unused argument(s) compilation warning */
  STM32_UNUSED(hi2s);

  /* NOTE : This function must not be modified, when the callback is needed,
            the HAL_I2S_TxCpltCallback must be implemented in the user file
   */
}

/**
  * @brief Rx transfer complete callback.
  * @param hi2s Pointer to hal_i2s_handle_t
  */
__weak void HAL_I2S_RxCpltCallback(hal_i2s_handle_t *hi2s)
{
  /* Check the I2S handle allocation */
  ASSERT_DBG_PARAM(hi2s != NULL);

  /* Prevent unused argument(s) compilation warning */
  STM32_UNUSED(hi2s);

  /* NOTE : This function must not be modified, when the callback is needed,
            the HAL_I2S_RxCpltCallback must be implemented in the user file
   */
}

/**
  * @brief Tx and Rx transfer complete callback.
  * @param hi2s Pointer to hal_i2s_handle_t
  */
__weak void HAL_I2S_TxRxCpltCallback(hal_i2s_handle_t *hi2s)
{
  /* Check the I2S handle allocation */
  ASSERT_DBG_PARAM(hi2s != NULL);

  /* Prevent unused argument(s) compilation warning */
  STM32_UNUSED(hi2s);

  /* NOTE : This function must not be modified, when the callback is needed,
            the HAL_I2S_TxRxCpltCallback must be implemented in the user file
   */
}

/**
  * @brief Tx half transfer complete callback.
  * @param hi2s Pointer to hal_i2s_handle_t
  */
__weak void HAL_I2S_TxHalfCpltCallback(hal_i2s_handle_t *hi2s)
{
  /* Check the I2S handle allocation */
  ASSERT_DBG_PARAM(hi2s != NULL);

  /* Prevent unused argument(s) compilation warning */
  STM32_UNUSED(hi2s);

  /* NOTE : This function must not be modified, when the callback is needed,
            the HAL_I2S_TxHalfCpltCallback must be implemented in the user file
   */
}

/**
  * @brief Rx half transfer complete callback.
  * @param hi2s Pointer to hal_i2s_handle_t
  */
__weak void HAL_I2S_RxHalfCpltCallback(hal_i2s_handle_t *hi2s)
{
  /* Check the I2S handle allocation */
  ASSERT_DBG_PARAM(hi2s != NULL);

  /* Prevent unused argument(s) compilation warning */
  STM32_UNUSED(hi2s);

  /* NOTE : This function must not be modified, when the callback is needed,
            the HAL_I2S_RxHalfCpltCallback must be implemented in the user file
   */
}

/**
  * @brief Tx and Rx half transfer complete callback.
  * @param hi2s Pointer to hal_i2s_handle_t
  */
__weak void HAL_I2S_TxRxHalfCpltCallback(hal_i2s_handle_t *hi2s)
{
  /* Check the I2S handle allocation */
  ASSERT_DBG_PARAM(hi2s != NULL);

  /* Prevent unused argument(s) compilation warning */
  STM32_UNUSED(hi2s);

  /* NOTE : This function must not be modified, when the callback is needed,
            the HAL_I2S_TxRxHalfCpltCallback must be implemented in the user file
   */
}

/**
  * @brief I2S Abort complete callback.
  * @param hi2s Pointer to hal_i2s_handle_t
  */
__weak void HAL_I2S_AbortCpltCallback(hal_i2s_handle_t *hi2s)
{
  /* Check the I2S handle allocation */
  ASSERT_DBG_PARAM(hi2s != NULL);

  /* Prevent unused argument(s) compilation warning */
  STM32_UNUSED(hi2s);

  /* NOTE : This function must not be modified, when the callback is needed,
            the HAL_I2S_AbortCpltCallback must be implemented in the user file
   */
}

#if defined(USE_HAL_I2S_REGISTER_CALLBACKS) && (USE_HAL_I2S_REGISTER_CALLBACKS == 1U)
/**
  * @brief  Register the Error callback.
  * @param  hi2s Pointer to a @ref hal_i2s_handle_t
  * @param  p_callback Pointer to the Error callback function
  * @retval HAL_INVALID_PARAM Invalid Callback pointer
  * @retval HAL_OK Register completed successfully
  */
hal_status_t HAL_I2S_RegisterErrorCallback(hal_i2s_handle_t *hi2s, hal_i2s_cb_t p_callback)
{
  /* Check the parameters */
  ASSERT_DBG_PARAM(hi2s != NULL);
  ASSERT_DBG_PARAM(p_callback != NULL);

  ASSERT_DBG_STATE(hi2s->global_state, (uint32_t)HAL_I2S_STATE_INIT | (uint32_t)HAL_I2S_STATE_IDLE);

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1U)
  if (p_callback == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  hi2s->p_error_cb = p_callback;

  return HAL_OK;
}

/**
  * @brief  Register the Tx Cplt callback.
  * @param  hi2s Pointer to a @ref hal_i2s_handle_t
  * @param  p_callback Pointer to the Tx Cplt callback function
  * @retval HAL_INVALID_PARAM Invalid Callback pointer
  * @retval HAL_OK Register completed successfully
  */
hal_status_t HAL_I2S_RegisterTxCpltCallback(hal_i2s_handle_t *hi2s, hal_i2s_cb_t p_callback)
{
  /* Check the parameters */
  ASSERT_DBG_PARAM(hi2s != NULL);
  ASSERT_DBG_PARAM(p_callback != NULL);

  ASSERT_DBG_STATE(hi2s->global_state, (uint32_t)HAL_I2S_STATE_INIT | (uint32_t)HAL_I2S_STATE_IDLE);

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1U)
  if (p_callback == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  hi2s->p_tx_cplt_cb = p_callback;

  return HAL_OK;
}

/**
  * @brief  Register the Rx Cplt callback.
  * @param  hi2s Pointer to a @ref hal_i2s_handle_t
  * @param  p_callback Pointer to the Rx Cplt callback function
  * @retval HAL_INVALID_PARAM Invalid Callback pointer
  * @retval HAL_OK Register completed successfully
  */
hal_status_t HAL_I2S_RegisterRxCpltCallback(hal_i2s_handle_t *hi2s, hal_i2s_cb_t p_callback)
{
  /* Check the parameters */
  ASSERT_DBG_PARAM(hi2s != NULL);
  ASSERT_DBG_PARAM(p_callback != NULL);

  ASSERT_DBG_STATE(hi2s->global_state, (uint32_t)HAL_I2S_STATE_INIT | (uint32_t)HAL_I2S_STATE_IDLE);

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1U)
  if (p_callback == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  hi2s->p_rx_cplt_cb = p_callback;

  return HAL_OK;
}

/**
  * @brief  Register the Tx/Rx Cplt callback.
  * @param  hi2s Pointer to a @ref hal_i2s_handle_t
  * @param  p_callback Pointer to the Tx/Rx Cplt callback function
  * @retval HAL_INVALID_PARAM Invalid Callback pointer
  * @retval HAL_OK Register completed successfully
  */
hal_status_t HAL_I2S_RegisterTxRxCpltCallback(hal_i2s_handle_t *hi2s, hal_i2s_cb_t p_callback)
{
  /* Check the parameters */
  ASSERT_DBG_PARAM(hi2s != NULL);
  ASSERT_DBG_PARAM(p_callback != NULL);

  ASSERT_DBG_STATE(hi2s->global_state, (uint32_t)HAL_I2S_STATE_INIT | (uint32_t)HAL_I2S_STATE_IDLE);

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1U)
  if (p_callback == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  hi2s->p_tx_rx_cplt_cb = p_callback;

  return HAL_OK;
}

/**
  * @brief  Register the Tx half Cplt callback.
  * @param  hi2s Pointer to a @ref hal_i2s_handle_t
  * @param  p_callback Pointer to the Tx half Cplt callback function
  * @retval HAL_INVALID_PARAM Invalid Callback pointer
  * @retval HAL_OK Register completed successfully
  */
hal_status_t HAL_I2S_RegisterTxHalfCpltCallback(hal_i2s_handle_t *hi2s, hal_i2s_cb_t p_callback)
{
  /* Check the parameters */
  ASSERT_DBG_PARAM(hi2s != NULL);
  ASSERT_DBG_PARAM(p_callback != NULL);

  ASSERT_DBG_STATE(hi2s->global_state, (uint32_t)HAL_I2S_STATE_INIT | (uint32_t)HAL_I2S_STATE_IDLE);

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1U)
  if (p_callback == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  hi2s->p_tx_half_cplt_cb = p_callback;

  return HAL_OK;
}

/**
  * @brief  Registerthe Rx half Cplt callback.
  * @param  hi2s Pointer to a @ref hal_i2s_handle_t
  * @param  p_callback Pointer to the Rx half Cplt callback function
  * @retval HAL_INVALID_PARAM Invalid Callback pointer
  * @retval HAL_OK Register completed successfully
  */
hal_status_t HAL_I2S_RegisterRxHalfCpltCallback(hal_i2s_handle_t *hi2s, hal_i2s_cb_t p_callback)
{
  /* Check the parameters */
  ASSERT_DBG_PARAM(hi2s != NULL);
  ASSERT_DBG_PARAM(p_callback != NULL);

  ASSERT_DBG_STATE(hi2s->global_state, (uint32_t)HAL_I2S_STATE_INIT | (uint32_t)HAL_I2S_STATE_IDLE);

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1U)
  if (p_callback == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  hi2s->p_rx_half_cplt_cb = p_callback;

  return HAL_OK;
}

/**
  * @brief  Register the Tx/Rx half Cplt callback.
  * @param  hi2s Pointer to a @ref hal_i2s_handle_t
  * @param  p_callback Pointer to the Tx/Rx half cplt callback function
  * @retval HAL_INVALID_PARAM Invalid Callback pointer
  * @retval HAL_OK Register completed successfully
  */
hal_status_t HAL_I2S_RegisterTxRxHalfCpltCallback(hal_i2s_handle_t *hi2s, hal_i2s_cb_t p_callback)
{
  /* Check the parameters */
  ASSERT_DBG_PARAM(hi2s != NULL);
  ASSERT_DBG_PARAM(p_callback != NULL);

  ASSERT_DBG_STATE(hi2s->global_state, (uint32_t)HAL_I2S_STATE_INIT | (uint32_t)HAL_I2S_STATE_IDLE);

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1U)
  if (p_callback == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  hi2s->p_tx_rx_half_cplt_cb = p_callback;

  return HAL_OK;
}

/**
  * @brief  Register the Abort Cplt callback.
  * @param  hi2s Pointer to a @ref hal_i2s_handle_t
  * @param  p_callback Pointer to the Abort cplt callback function
  * @retval HAL_INVALID_PARAM Invalid Callback pointer
  * @retval HAL_OK Register completed successfully
  */
hal_status_t HAL_I2S_RegisterAbortCpltCallback(hal_i2s_handle_t *hi2s, hal_i2s_cb_t p_callback)
{
  /* Check the parameters */
  ASSERT_DBG_PARAM(hi2s != NULL);
  ASSERT_DBG_PARAM(p_callback != NULL);

  ASSERT_DBG_STATE(hi2s->global_state, (uint32_t)HAL_I2S_STATE_INIT | (uint32_t)HAL_I2S_STATE_IDLE);

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1U)
  if (p_callback == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  hi2s->p_abort_cplt_cb = p_callback;

  return HAL_OK;
}
#endif /* USE_HAL_I2S_REGISTER_CALLBACKS */
/**
  * @}
  */

/** @defgroup I2S_Exported_Functions_Group7 Peripheral current frequency, state and errors functions
  * @{
  * This subsection provides 4 functions allowing to read peripheral current frequency, current and
  * previous state and last occurred errors.
  *  - HAL_I2S GetClockFreq() function to retrieve the current clock frequency of the I2S peripheral.
  *  - HAL_I2S_GetState() function to retrieve the current state of the I2S peripheral.
  *  - HAL_I2S_GetPreviousState() function to retrieve the previous state of the I2S peripheral.
  *  - HAL_GetLastErrorsCodes() function to retrieve the error codes in case of HAL_ERROR return
  *    available under the compilation switch USE_HAL_I2S_GET_LAST_ERRORS.
  */

/**
  * @brief  Return the peripheral clock frequency for I2S.
  * @param  hi2s Pointer to a @ref hal_i2s_handle_t
  * @retval uint32_t Frequency in Hz
  * @retval 0 Source clock of the hi2s not configured or not ready
  */
uint32_t HAL_I2S_GetClockFreq(const hal_i2s_handle_t *hi2s)
{
  /* Check the I2S handle & config allocation */
  ASSERT_DBG_PARAM(hi2s != NULL);

  /* Check the global state, the driver must be at least configured */
  ASSERT_DBG_STATE(hi2s->global_state, (((uint32_t)HAL_I2S_STATE_IDLE)           \
                                        | ((uint32_t)HAL_I2S_STATE_TX_ACTIVE)    \
                                        | ((uint32_t)HAL_I2S_STATE_RX_ACTIVE)    \
                                        | ((uint32_t)HAL_I2S_STATE_TX_RX_ACTIVE) \
                                        | ((uint32_t)HAL_I2S_STATE_PAUSED)       \
                                        | ((uint32_t)HAL_I2S_STATE_ABORT)        \
                                        | ((uint32_t)HAL_I2S_STATE_INIT)));

  return HAL_RCC_SPI_GetKernelClkFreq(I2S_GET_INSTANCE(hi2s));
}

/**
  * @brief  Retrieve the I2S handle state.
  * @param  hi2s Pointer to a @ref hal_i2s_handle_t
  * @retval hal_i2s_state_t I2S state
  */
hal_i2s_state_t HAL_I2S_GetState(const hal_i2s_handle_t *hi2s)
{
  /* Check the parameters */
  ASSERT_DBG_PARAM((hi2s != NULL));

  /* Check the state */
  ASSERT_DBG_STATE(hi2s->global_state, (((uint32_t)HAL_I2S_STATE_IDLE)           \
                                        | ((uint32_t)HAL_I2S_STATE_TX_ACTIVE)    \
                                        | ((uint32_t)HAL_I2S_STATE_RX_ACTIVE)    \
                                        | ((uint32_t)HAL_I2S_STATE_TX_RX_ACTIVE) \
                                        | ((uint32_t)HAL_I2S_STATE_PAUSED)       \
                                        | ((uint32_t)HAL_I2S_STATE_ABORT)        \
                                        | ((uint32_t)HAL_I2S_STATE_INIT)));

  /* Return I2S handle state */
  return hi2s->global_state;
}


/**
  * @brief  Retrieve the previous I2S handle state.
  * @param  hi2s Pointer to a @ref hal_i2s_handle_t
  * @retval hal_i2s_state_t I2S previous state
  */
hal_i2s_state_t HAL_I2S_GetPreviousState(const hal_i2s_handle_t *hi2s)
{
  /* Check the parameters */
  ASSERT_DBG_PARAM((hi2s != NULL));

  /* Check the state */
  ASSERT_DBG_STATE(hi2s->global_state, (((uint32_t)HAL_I2S_STATE_IDLE)           \
                                        | ((uint32_t)HAL_I2S_STATE_TX_ACTIVE)    \
                                        | ((uint32_t)HAL_I2S_STATE_RX_ACTIVE)    \
                                        | ((uint32_t)HAL_I2S_STATE_TX_RX_ACTIVE) \
                                        | ((uint32_t)HAL_I2S_STATE_PAUSED)       \
                                        | ((uint32_t)HAL_I2S_STATE_ABORT)        \
                                        | ((uint32_t)HAL_I2S_STATE_INIT)));

  /* Return I2S handle previous state */
  return hi2s->previous_state;
}

#if defined(USE_HAL_I2S_GET_LAST_ERRORS) && (USE_HAL_I2S_GET_LAST_ERRORS == 1U)
/**
  * @brief  Retrieve the I2S errors codes.
  * @param  hi2s Pointer to a @ref hal_i2s_handle_t
  * @retval uint32_t Returned value can be a combination of the following values:
  *         @arg HAL_I2S_ERROR_NONE
  *         @arg HAL_I2S_ERROR_OVR
  *         @arg HAL_I2S_ERROR_UDR
  *         @arg HAL_I2S_ERROR_DMA
  *         @arg HAL_I2S_ERROR_FRE
  *         @arg HAL_I2S_ERROR_IO_LOCKED
  */
uint32_t HAL_I2S_GetLastErrorsCodes(const hal_i2s_handle_t *hi2s)
{
  /* Check the SPI handle */
  ASSERT_DBG_PARAM(hi2s != (void *)NULL);

  /* Check the state */
  ASSERT_DBG_STATE(hi2s->global_state, (((uint32_t)HAL_I2S_STATE_IDLE)           \
                                        | ((uint32_t)HAL_I2S_STATE_TX_ACTIVE)    \
                                        | ((uint32_t)HAL_I2S_STATE_RX_ACTIVE)    \
                                        | ((uint32_t)HAL_I2S_STATE_TX_RX_ACTIVE) \
                                        | ((uint32_t)HAL_I2S_STATE_PAUSED)       \
                                        | ((uint32_t)HAL_I2S_STATE_ABORT)        \
                                        | ((uint32_t)HAL_I2S_STATE_INIT)));

  return hi2s->last_error_codes;
}
#endif /* USE_HAL_I2S_GET_LAST_ERRORS */
/**
  * @}
  */

#if defined(USE_HAL_MUTEX) && (USE_HAL_MUTEX == 1U)
/** @defgroup I2S_Exported_Functions_Group7 Acquire/release Bus functions
  * @{
  * This subsection provides a set of functions allowing to Acquire/Release the bus based on the HAL OS
  * abstraction layer (stm32_hal_os.c/.h osal):

  * - The HAL_I2S_AcquireBus() must be called from thread mode only (not from handler mode i.e from ISR).
  * - The HAL_I2S_ReleaseBus() can be called from thread mode or from handler mode i.e from ISR.
 */
/**
  * @brief  Acquire the I2S bus thanks to the the HAL OS abstraction layer (stm32_hal_os.c/.h osal).
  * @param  hi2s Pointer to a @ref hal_i2s_handle_t
  * @param  timeout_ms Time to wait before the the bus is occupied by the handle.
  * @note The HAL_I2S_AcquireBus function must be called from thread mode only (not from handler mode i.e from ISR).
  * @retval HAL_OK Operation started successfully.
  * @retval HAL_ERROR Operation completed with error.
  */
hal_status_t HAL_I2S_AcquireBus(hal_i2s_handle_t *hi2s, uint32_t timeout_ms)
{
  hal_status_t status = HAL_ERROR;

  /* Check the parameters */
  ASSERT_DBG_PARAM((hi2s != NULL));

  /* Check the state */
  ASSERT_DBG_STATE(hi2s->global_state, (((uint32_t)HAL_I2S_STATE_IDLE)           \
                                        | ((uint32_t)HAL_I2S_STATE_TX_ACTIVE)    \
                                        | ((uint32_t)HAL_I2S_STATE_RX_ACTIVE)    \
                                        | ((uint32_t)HAL_I2S_STATE_TX_RX_ACTIVE) \
                                        | ((uint32_t)HAL_I2S_STATE_PAUSED)       \
                                        | ((uint32_t)HAL_I2S_STATE_ABORT)        \
                                        | ((uint32_t)HAL_I2S_STATE_INIT)));

  if (HAL_OS_SemaphoreTake(&hi2s->semaphore, timeout_ms) == HAL_OS_OK)
  {
    status = HAL_OK;
  }

  return status;
}

/**
  * @brief  Release the I2S bus thanks to the the HAL OS abstraction layer (stm32_hal_os.c/.h osal).
  * @param  hi2s Pointer to a @ref hal_i2s_handle_t
  * @note   The HAL_I2S_ReleaseBus function can be called from thread mode or from handler mode i.e from ISR
  * @retval HAL_OK Operation started successfully.
  * @retval HAL_ERROR Operation completed with error.
  */
hal_status_t HAL_I2S_ReleaseBus(hal_i2s_handle_t *hi2s)
{
  hal_status_t status = HAL_ERROR;

  /* Check the parameters */
  ASSERT_DBG_PARAM((hi2s != NULL));

  /* Check the state */
  ASSERT_DBG_STATE(hi2s->global_state, (((uint32_t)HAL_I2S_STATE_IDLE)           \
                                        | ((uint32_t)HAL_I2S_STATE_TX_ACTIVE)    \
                                        | ((uint32_t)HAL_I2S_STATE_RX_ACTIVE)    \
                                        | ((uint32_t)HAL_I2S_STATE_TX_RX_ACTIVE) \
                                        | ((uint32_t)HAL_I2S_STATE_PAUSED)       \
                                        | ((uint32_t)HAL_I2S_STATE_ABORT)        \
                                        | ((uint32_t)HAL_I2S_STATE_INIT)));

  if (HAL_OS_SemaphoreRelease(&hi2s->semaphore) == HAL_OS_OK)
  {
    status = HAL_OK;
  }

  return status;
}
/**
  * @}
  */
#endif /* USE_HAL_MUTEX */

#if defined (USE_HAL_I2S_USER_DATA) && (USE_HAL_I2S_USER_DATA == 1U)
/** @defgroup I2S_Exported_Functions_Group8 Set/Get user data
  * @{
  * A set of functions allowing to manage a user data pointer stored to the I2S handle:
  *  - HAL_I2S_SetUserData() Set the user data into the handle
  *  - HAL_I2S_GetUserData() Get the user data from the handle
  */

/**
  * @brief Store User Data pointer into the handle.
  * @param hi2s Pointer to a @ref hal_i2s_handle_t
  * @param p_user_data Pointer to the user data.
  */
void HAL_I2S_SetUserData(hal_i2s_handle_t *hi2s, const void *p_user_data)
{
  /* Check parameters allocation */
  ASSERT_DBG_PARAM(hi2s != NULL);
  ASSERT_DBG_PARAM(p_user_data != NULL);

  /* Check the global state */
  ASSERT_DBG_STATE(hi2s->global_state, HAL_I2S_STATE_IDLE);

  hi2s->p_user_data = p_user_data;
}

/**
  * @brief  Retrieve User Data pointer from the handle.
  * @param  hi2s Pointer to a @ref hal_i2s_handle_t
  * @retval Pointer to the user data.
  */
const void *HAL_I2S_GetUserData(const hal_i2s_handle_t *hi2s)
{
  /* Check parameters allocation */
  ASSERT_DBG_PARAM(hi2s != NULL);

  /* Check the global state */
  ASSERT_DBG_STATE(hi2s->global_state, (((uint32_t)HAL_I2S_STATE_IDLE)           \
                                        | ((uint32_t)HAL_I2S_STATE_TX_ACTIVE)    \
                                        | ((uint32_t)HAL_I2S_STATE_RX_ACTIVE)    \
                                        | ((uint32_t)HAL_I2S_STATE_TX_RX_ACTIVE) \
                                        | ((uint32_t)HAL_I2S_STATE_PAUSED)       \
                                        | ((uint32_t)HAL_I2S_STATE_ABORT)));

  return (hi2s->p_user_data);
}
/**
  * @}
  */
#endif /* USE_HAL_I2S_USER_DATA */
#if defined(USE_HAL_I2S_DMA) && (USE_HAL_I2S_DMA == 1U)
/**
  * @brief DMA I2S transmit process complete callback.
  * @param hdma Pointer to a hal_dma_handle_t structure that contains
  *               the configuration information for the specified DMA module.
  */
static void I2S_DMATxCplt(hal_dma_handle_t *hdma)
{
  hal_i2s_handle_t *hi2s = (hal_i2s_handle_t *)((hal_dma_handle_t *)hdma)->p_parent;

#if defined(USE_HAL_DMA_LINKEDLIST) && (USE_HAL_DMA_LINKEDLIST == 1U)
  if (hi2s->hdma_tx->xfer_mode == HAL_DMA_XFER_MODE_DIRECT)
#endif /* USE_HAL_DMA_LINKEDLIST */
  {
    /* Disable Tx DMA Request */
    STM32_CLEAR_BIT(I2S_GET_INSTANCE(hi2s)->CFG1, SPI_CFG1_TXDMAEN);
    hi2s->tx_xfer_count = (uint16_t)0U;
    hi2s->global_state = HAL_I2S_STATE_IDLE;
  }
  /* Call user Rx complete callback */
#if defined(USE_HAL_I2S_REGISTER_CALLBACKS) && (USE_HAL_I2S_REGISTER_CALLBACKS == 1U)
  hi2s->p_tx_cplt_cb(hi2s);
#else
  HAL_I2S_TxCpltCallback(hi2s);
#endif /* USE_HAL_I2S_REGISTER_CALLBACKS */
}

/**
  * @brief  DMA I2S transmit process half complete callback.
  * @param  hdma pointer to a hal_dma_handle_t structure that contains
  *         the configuration information for the specified DMA module.
  * @retval None
  */
static void I2S_DMATxHalfCplt(hal_dma_handle_t *hdma)
{
  hal_i2s_handle_t *hi2s = (hal_i2s_handle_t *)((hal_dma_handle_t *)hdma)->p_parent;

  /* Call user Tx half complete callback */
#if defined(USE_HAL_I2S_REGISTER_CALLBACKS) && (USE_HAL_I2S_REGISTER_CALLBACKS == 1U)
  hi2s->p_tx_half_cplt_cb(hi2s);
#else
  HAL_I2S_TxHalfCpltCallback(hi2s);
#endif /* USE_HAL_I2S_REGISTER_CALLBACKS */
}

/**
  * @brief  DMA I2S receive process complete callback.
  * @param  hdma pointer to a hal_dma_handle_t structure that contains
  *         the configuration information for the specified DMA module.
  * @retval None
  */
static void I2S_DMARxCplt(hal_dma_handle_t *hdma)
{
  hal_i2s_handle_t *hi2s = (hal_i2s_handle_t *)((hal_dma_handle_t *)hdma)->p_parent;

#if defined(USE_HAL_DMA_LINKEDLIST) && (USE_HAL_DMA_LINKEDLIST == 1U)
  if (hi2s->hdma_rx->xfer_mode == HAL_DMA_XFER_MODE_DIRECT)
#endif /* USE_HAL_DMA_LINKEDLIST */
  {
    /* Disable Rx DMA Request */
    STM32_CLEAR_BIT(I2S_GET_INSTANCE(hi2s)->CFG1, SPI_CFG1_RXDMAEN);
    hi2s->rx_xfer_count = (uint16_t)0U;
    hi2s->global_state = HAL_I2S_STATE_IDLE;
  }
  /* Call user Rx complete callback */
#if defined(USE_HAL_I2S_REGISTER_CALLBACKS) && (USE_HAL_I2S_REGISTER_CALLBACKS == 1U)
  hi2s->p_rx_cplt_cb(hi2s);
#else
  HAL_I2S_RxCpltCallback(hi2s);
#endif /* USE_HAL_I2S_REGISTER_CALLBACKS */
}

/**
  * @brief  DMA I2S receive process half complete callback.
  * @param  hdma pointer to a hal_dma_handle_t structure that contains
  *         the configuration information for the specified DMA module.
  * @retval None
  */
static void I2S_DMARxHalfCplt(hal_dma_handle_t *hdma)
{
  hal_i2s_handle_t *hi2s = (hal_i2s_handle_t *)((hal_dma_handle_t *)hdma)->p_parent;

  /* Call user Rx half complete callback */
#if defined(USE_HAL_I2S_REGISTER_CALLBACKS) && (USE_HAL_I2S_REGISTER_CALLBACKS == 1U)
  hi2s->p_rx_half_cplt_cb(hi2s);
#else
  HAL_I2S_RxHalfCpltCallback(hi2s);
#endif /* USE_HAL_I2S_REGISTER_CALLBACKS */
}

/**
  * @brief  DMA I2S transmit receive process complete callback.
  * @param  hdma pointer to a hal_dma_handle_t structure that contains
  *               the configuration information for the specified DMA module.
  * @retval None
  */
static void I2S_DMATxRxCplt(hal_dma_handle_t *hdma)
{
  hal_i2s_handle_t *hi2s = (hal_i2s_handle_t *)((hal_dma_handle_t *)hdma)->p_parent;

#if defined(USE_HAL_DMA_LINKEDLIST) && (USE_HAL_DMA_LINKEDLIST == 1U)
  if (hi2s->hdma_rx->xfer_mode == HAL_DMA_XFER_MODE_DIRECT)
#endif /* USE_HAL_DMA_LINKEDLIST */
  {
    /* Disable Tx DMA Request */
    STM32_CLEAR_BIT(I2S_GET_INSTANCE(hi2s)->CFG1, SPI_CFG1_TXDMAEN);
    hi2s->tx_xfer_count = (uint16_t)0U;

    /* Disable Rx DMA Request */
    STM32_CLEAR_BIT(I2S_GET_INSTANCE(hi2s)->CFG1, SPI_CFG1_RXDMAEN);
    hi2s->rx_xfer_count = (uint16_t)0U;

    hi2s->global_state = HAL_I2S_STATE_IDLE;
  }
  /* Call user Rx complete callback */
#if defined(USE_HAL_I2S_REGISTER_CALLBACKS) && (USE_HAL_I2S_REGISTER_CALLBACKS == 1U)
  hi2s->p_tx_rx_cplt_cb(hi2s);
#else
  HAL_I2S_TxRxCpltCallback(hi2s);
#endif /* USE_HAL_I2S_REGISTER_CALLBACKS */
}

/**
  * @brief  DMA I2S transmit receive process half complete callback.
  * @param  hdma pointer to a hal_dma_handle_t structure that contains
  *               the configuration information for the specified DMA module.
  * @retval None
  */
static void I2S_DMATxRxHalfCplt(hal_dma_handle_t *hdma)
{
  hal_i2s_handle_t *hi2s = (hal_i2s_handle_t *)((hal_dma_handle_t *)hdma)->p_parent;

  /* Call user TxRx Half complete callback */
#if defined(USE_HAL_I2S_REGISTER_CALLBACKS) && (USE_HAL_I2S_REGISTER_CALLBACKS == 1U)
  hi2s->p_tx_rx_half_cplt_cb(hi2s);
#else
  HAL_I2S_TxRxHalfCpltCallback(hi2s);
#endif /* USE_HAL_I2S_REGISTER_CALLBACKS */
}

/**
  * @brief  DMA I2S communication error callback.
  * @param  hdma pointer to a hal_dma_handle_t structure that contains
  *         the configuration information for the specified DMA module.
  * @retval None
  */
static void I2S_DMAError(hal_dma_handle_t *hdma)
{
  hal_i2s_handle_t *hi2s = (hal_i2s_handle_t *)((hal_dma_handle_t *)hdma)->p_parent;

  /* Disable Rx and Tx DMA Request */
  STM32_CLEAR_BIT(I2S_GET_INSTANCE(hi2s)->CFG1, (SPI_CFG1_RXDMAEN | SPI_CFG1_TXDMAEN));
  hi2s->tx_xfer_count = (uint16_t) 0UL;
  hi2s->rx_xfer_count = (uint16_t) 0UL;

  hi2s->global_state = HAL_I2S_STATE_IDLE;

#if defined(USE_HAL_I2S_GET_LAST_ERRORS) && (USE_HAL_I2S_GET_LAST_ERRORS == 1U)
  /* Set the error code and execute error callback*/
  STM32_SET_BIT(hi2s->last_error_codes, HAL_I2S_ERROR_DMA);
#endif /* USE_HAL_I2S_GET_LAST_ERRORS */

  /* Call user error callback */
#if defined(USE_HAL_I2S_REGISTER_CALLBACKS) && (USE_HAL_I2S_REGISTER_CALLBACKS == 1U)
  hi2s->p_error_cb(hi2s);
#else
  HAL_I2S_ErrorCallback(hi2s);
#endif /* USE_HAL_I2S_REGISTER_CALLBACKS */
}
#endif /* USE_HAL_I2S_DMA */

/**
  * @brief  Manage the transmission 16-bit in Interrupt context.
  * @param  hi2s pointer to a hal_i2s_handle_t structure that contains
  *         the configuration information for I2S module
  * @retval None
  */
static void I2S_Transmit_16Bit_IT(hal_i2s_handle_t *hi2s)
{
  LL_I2S_TransmitData16(I2S_GET_INSTANCE(hi2s), *hi2s->p_tx_buff);
  hi2s->p_tx_buff++;
  hi2s->tx_xfer_count--;

  if (hi2s->tx_xfer_count == 0U)
  {
    /* Disable TXP, DXP, UDR, OVR and TIFRE interrupt */
    LL_I2S_DisableIT(I2S_GET_INSTANCE(hi2s), (LL_I2S_IT_TXP | LL_I2S_IT_DXP | LL_I2S_IT_UDR
                                              | LL_I2S_IT_OVR | LL_I2S_IT_TIFRE));

    if (hi2s->global_state == HAL_I2S_STATE_TX_ACTIVE)
    {
      hi2s->global_state = HAL_I2S_STATE_IDLE;

      /* Call user Tx complete callback */
#if (USE_HAL_I2S_REGISTER_CALLBACKS == 1UL)
      hi2s->p_tx_cplt_cb(hi2s);
#else
      HAL_I2S_TxCpltCallback(hi2s);
#endif /* USE_HAL_I2S_REGISTER_CALLBACKS */
    }
  }
}

/**
  * @brief  Manage the transmission 32-bit in Interrupt context.
  * @param  hi2s pointer to a hal_i2s_handle_t structure that contains
  *         the configuration information for I2S module
  * @retval None
  */
static void I2S_Transmit_32Bit_IT(hal_i2s_handle_t *hi2s)
{
  LL_I2S_TransmitData32(I2S_GET_INSTANCE(hi2s), *((const uint32_t *)hi2s->p_tx_buff));
  hi2s->p_tx_buff += 2U;
  hi2s->tx_xfer_count--;

  if (hi2s->tx_xfer_count == 0U)
  {
    /* Disable TXP, DXP, UDR, OVR and TIFRE interrupt */
    LL_I2S_DisableIT(I2S_GET_INSTANCE(hi2s), (LL_I2S_IT_TXP | LL_I2S_IT_DXP | LL_I2S_IT_UDR
                                              | LL_I2S_IT_OVR | LL_I2S_IT_TIFRE));

    if (hi2s->global_state == HAL_I2S_STATE_TX_ACTIVE)
    {
      hi2s->global_state = HAL_I2S_STATE_IDLE;

      /* Call user Tx complete callback */
#if (USE_HAL_I2S_REGISTER_CALLBACKS == 1UL)
      hi2s->p_tx_cplt_cb(hi2s);
#else
      HAL_I2S_TxCpltCallback(hi2s);
#endif /* USE_HAL_I2S_REGISTER_CALLBACKS */
    }
  }
}

/**
  * @brief  Manage the reception 16-bit in Interrupt context.
  * @param  hi2s pointer to a hal_i2s_handle_t structure that contains
  *         the configuration information for I2S module
  * @retval None
  */
static void I2S_Receive_16Bit_IT(hal_i2s_handle_t *hi2s)
{
  *((uint16_t *)hi2s->p_rx_buff) = LL_I2S_ReceiveData16(I2S_GET_INSTANCE(hi2s));
  hi2s->p_rx_buff++;
  hi2s->rx_xfer_count--;

  if (hi2s->rx_xfer_count == 0U)
  {
    if (hi2s->global_state == HAL_I2S_STATE_TX_RX_ACTIVE)
    {
      /* Disable TXP, RXP, DXP, UDR, OVR and TIFRE interrupt */
      LL_I2S_DisableIT(I2S_GET_INSTANCE(hi2s), (LL_I2S_IT_RXP | LL_I2S_IT_TXP | LL_I2S_IT_DXP
                                                | LL_I2S_IT_UDR | LL_I2S_IT_OVR | LL_I2S_IT_TIFRE));
    }
    else
    {
      /* Disable RXP, UDR, OVR and TIFRE interrupt */
      LL_I2S_DisableIT(I2S_GET_INSTANCE(hi2s), (LL_I2S_IT_RXP | LL_I2S_IT_UDR | LL_I2S_IT_OVR | LL_I2S_IT_TIFRE));
    }

    hi2s->previous_state = hi2s->global_state;
    hi2s->global_state = HAL_I2S_STATE_IDLE;

#if (USE_HAL_I2S_REGISTER_CALLBACKS == 1U)
    if (hi2s->previous_state == HAL_I2S_STATE_TX_RX_ACTIVE)
    {
      hi2s->p_tx_rx_cplt_cb(hi2s);
    }
    else
    {
      hi2s->p_rx_cplt_cb(hi2s);
    }
#else
    if (hi2s->previous_state == HAL_I2S_STATE_TX_RX_ACTIVE)
    {
      HAL_I2S_TxRxCpltCallback(hi2s);
    }
    else
    {
      HAL_I2S_RxCpltCallback(hi2s);
    }
#endif /* USE_HAL_I2S_REGISTER_CALLBACKS */
  }
}

/**
  * @brief  Manage the reception 32-bit in Interrupt context.
  * @param  hi2s pointer to a hal_i2s_handle_t structure that contains
  *         the configuration information for I2S module
  * @retval None
  */
static void I2S_Receive_32Bit_IT(hal_i2s_handle_t *hi2s)
{
  *((uint32_t *)hi2s->p_rx_buff) = LL_I2S_ReceiveData32(I2S_GET_INSTANCE(hi2s));
  hi2s->p_rx_buff += 2U;
  hi2s->rx_xfer_count--;

  if (hi2s->rx_xfer_count == 0UL)
  {
    if (hi2s->global_state == HAL_I2S_STATE_TX_RX_ACTIVE)
    {
      /* Disable RXP, TXP, DXP, UDR, OVR and TIFRE interrupt */
      LL_I2S_DisableIT(I2S_GET_INSTANCE(hi2s), (LL_I2S_IT_RXP | LL_I2S_IT_TXP | LL_I2S_IT_DXP
                                                | LL_I2S_IT_UDR | LL_I2S_IT_OVR | LL_I2S_IT_TIFRE));
    }
    else
    {
      /* Disable RXP, UDR, OVR and TIFRE interrupt */
      LL_I2S_DisableIT(I2S_GET_INSTANCE(hi2s), (LL_I2S_IT_RXP | LL_I2S_IT_UDR | LL_I2S_IT_OVR | LL_I2S_IT_TIFRE));
    }

    hi2s->previous_state = hi2s->global_state;
    hi2s->global_state = HAL_I2S_STATE_IDLE;

#if (USE_HAL_I2S_REGISTER_CALLBACKS == 1U)
    if (hi2s->previous_state == HAL_I2S_STATE_TX_RX_ACTIVE)
    {
      hi2s->p_tx_rx_cplt_cb(hi2s);
    }
    else
    {
      hi2s->p_rx_cplt_cb(hi2s);
    }
#else
    if (hi2s->previous_state == HAL_I2S_STATE_TX_RX_ACTIVE)
    {
      HAL_I2S_TxRxCpltCallback(hi2s);
    }
    else
    {
      HAL_I2S_RxCpltCallback(hi2s);
    }
#endif /* USE_HAL_I2S_REGISTER_CALLBACKS */
  }
}

/**
  * @brief  Abort Transfer and clear flags.
  * @param hi2s Pointer to a hal_i2s_handle_t structure that contains
  *               the configuration information for I2S module.
  */
static void I2S_AbortTransfer(hal_i2s_handle_t *hi2s)
{
  /* Disable I2S peripheral */
  LL_I2S_Disable(I2S_GET_INSTANCE(hi2s));

  /* Disable ITs */
  LL_I2S_DisableIT(I2S_GET_INSTANCE(hi2s),
                   LL_I2S_IT_TXP | LL_I2S_IT_RXP | LL_I2S_IT_OVR | LL_I2S_IT_UDR | LL_I2S_IT_TIFRE);

#if defined(USE_HAL_I2S_DMA) && (USE_HAL_I2S_DMA == 1U)
  /* Disable DMA request */
  LL_I2S_DisableDMAReq_TX(I2S_GET_INSTANCE(hi2s));
  LL_I2S_DisableDMAReq_RX(I2S_GET_INSTANCE(hi2s));
#endif /* USE_HAL_I2S_DMA */

  /* Clear the error flags in the SR register */
#if defined(USE_HAL_I2S_OVR_UDR_ERRORS) && (USE_HAL_I2S_OVR_UDR_ERRORS == 1U)
  LL_I2S_ClearFlag_OVR(I2S_GET_INSTANCE(hi2s));
  LL_I2S_ClearFlag_UDR(I2S_GET_INSTANCE(hi2s));
#endif /* USE_HAL_I2S_OVR_UDR_ERRORS */
  LL_I2S_ClearFlag_SUSP(I2S_GET_INSTANCE(hi2s));
  LL_I2S_ClearFlag_FRE(I2S_GET_INSTANCE(hi2s));

  hi2s->tx_xfer_count = (uint16_t)0U;
  hi2s->rx_xfer_count = (uint16_t)0U;
}

/**
  * @brief Close Transfer and clear flags.
  * @param hi2s Pointer to a \ref hal_i2s_handle_t structure which contains
  *             the I2S instance.
  * @retval HAL_OK Operation completed successfully.
  * @retval HAL_ERROR Operation completed with error.
  */
static hal_status_t I2S_CloseTransfer(hal_i2s_handle_t *hi2s)
{
  hal_status_t status = HAL_OK;

  LL_I2S_DisableIT(I2S_GET_INSTANCE(hi2s), (LL_I2S_IT_TXP | LL_I2S_IT_RXP | LL_I2S_IT_OVR |
                                            LL_I2S_IT_UDR | LL_I2S_IT_TIFRE));

#if defined(USE_HAL_I2S_DMA) && (USE_HAL_I2S_DMA == 1U)
  LL_I2S_DisableDMAReq_TX(I2S_GET_INSTANCE(hi2s));
  LL_I2S_DisableDMAReq_RX(I2S_GET_INSTANCE(hi2s));
#endif /* USE_HAL_I2S_DMA */

  /* I2S frame error interrupt occurred */
  if (LL_I2S_IsActiveFlag_FRE(I2S_GET_INSTANCE(hi2s)) != 0U)
  {
#if defined(USE_HAL_I2S_GET_LAST_ERRORS) && (USE_HAL_I2S_GET_LAST_ERRORS == 1U)
    STM32_SET_BIT(hi2s->last_error_codes, HAL_I2S_ERROR_FRE);
#endif /* USE_HAL_I2S_GET_LAST_ERRORS */
    LL_I2S_ClearFlag_FRE(I2S_GET_INSTANCE(hi2s));
    status = HAL_ERROR;
  }

  hi2s->tx_xfer_count = (uint16_t)0U;
  hi2s->rx_xfer_count = (uint16_t)0U;

  hi2s->previous_state = hi2s->global_state;
  hi2s->global_state = HAL_I2S_STATE_IDLE;

  return status;
}

#if defined(USE_HAL_I2S_DMA) && (USE_HAL_I2S_DMA == 1U)
/**
  * @brief DMA I2S Tx communication abort callback, when initiated by user
  *         (To be called at end of DMA Tx Abort procedure following user abort request).
  * @param hdma DMA handle.
  * @warning When this callback is executed, User Abort complete callback is called only if no
  *         Abort still ongoing for Rx DMA Handle.
  */
static void I2S_DMATxAbortCallback(hal_dma_handle_t *hdma)
{
  hal_i2s_handle_t *hi2s = (hal_i2s_handle_t *)((hal_dma_handle_t *)hdma)->p_parent;

  hi2s->hdma_tx->p_xfer_abort_cb = NULL;

  /* Check if an Abort process is still ongoing */
  if (hi2s->hdma_rx != NULL)
  {
    if (hi2s->hdma_rx->p_xfer_abort_cb != NULL)
    {
      return;
    }
  }

  /* Call the Abort procedure */
  I2S_AbortTransfer(hi2s);

  hi2s->global_state = HAL_I2S_STATE_IDLE;

#if defined(USE_HAL_I2S_REGISTER_CALLBACKS) && (USE_HAL_I2S_REGISTER_CALLBACKS == 1U)
  hi2s->p_abort_cplt_cb(hi2s);
#else
  HAL_I2S_AbortCpltCallback(hi2s);
#endif /* USE_HAL_I2S_REGISTER_CALLBACKS */
}

/**
  * @brief DMA I2S Rx communication abort callback, when initiated by user
  *         (To be called at end of DMA Rx Abort procedure following user abort request).
  * @param hdma DMA handle.
  * @warning When this callback is executed, User Abort complete call back is called only if no
  *         Abort still ongoing for Tx DMA Handle.
  */
static void I2S_DMARxAbortCallback(hal_dma_handle_t *hdma)
{
  hal_i2s_handle_t *hi2s = (hal_i2s_handle_t *)((hal_dma_handle_t *)hdma)->p_parent;

  hi2s->hdma_rx->p_xfer_abort_cb = NULL;

  /* Check if an Abort process is still ongoing */
  if (hi2s->hdma_tx != NULL)
  {
    if (hi2s->hdma_tx->p_xfer_abort_cb != NULL)
    {
      return;
    }
  }

  /* Call the Abort procedure */
  I2S_AbortTransfer(hi2s);

  hi2s->global_state = HAL_I2S_STATE_IDLE;

#if defined(USE_HAL_I2S_REGISTER_CALLBACKS) && (USE_HAL_I2S_REGISTER_CALLBACKS == 1U)
  hi2s->p_abort_cplt_cb(hi2s);
#else
  HAL_I2S_AbortCpltCallback(hi2s);
#endif /* USE_HAL_I2S_REGISTER_CALLBACKS */
}
#endif /* USE_HAL_I2S_DMA */

/**
  * @brief  This function handles I2S Communication Timeout.
  * @param  hi2s pointer to a hal_i2s_handle_t structure that contains
  *         the configuration information for I2S module
  * @param  flag Flag checked
  * @param  status Value of the flag expected
  * @param  tick_start Tick start value
  * @param  timeout_ms Duration of the timeout
  * @retval HAL status
  */
static hal_status_t I2S_WaitOnFlagUntilTimeout(hal_i2s_handle_t *hi2s, uint32_t flag, uint32_t status,
                                               uint32_t tick_start, uint32_t timeout_ms)
{
  /* Wait until flag is set to status*/
  while (((LL_I2S_IsActiveFlag((SPI_TypeDef *)((uint32_t)hi2s->instance), flag)) != status))
  {
    if (timeout_ms != HAL_MAX_DELAY)
    {
      if (((HAL_GetTick() - tick_start) >= timeout_ms) || (timeout_ms == 0UL))
      {
        /* Set the I2S State idle */
        hi2s->global_state = HAL_I2S_STATE_IDLE;

        return HAL_TIMEOUT;
      }
    }
  }
  return HAL_OK;
}
/**
  * @}
  */

#endif /* USE_HAL_I2S_MODULE */

/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */
