/**
  ******************************************************************************
  * @file           : mx_adf1.c
  * @brief          : ADF1 Peripheral initialization
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2026 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the mx_stm32h7pxx_hal_drivers_license.md file
  * in the same directory as the generated code.
  * If no mx_stm32h7pxx_hal_drivers_license.md file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "mx_adf1.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private functions prototype------------------------------------------------*/
/* Exported variables by reference--------------------------------------------*/
static hal_adf_handle_t hADF1;

/* DMA nodes must be 8-byte aligned. */
__attribute__((section("non_cacheable_area"), aligned(8)))
static hal_dma_node_t DMA_Node_ADF1_FLT0;

static hal_dma_handle_t hGPDMA1_CH0;

/********************************************/
/* Exported functions for ADF1 in HAL layer */
/********************************************/
hal_adf_handle_t *mx_adf1_init(void)
{
  hal_adf_serial_interface_config_t sitf_0_config;
  hal_adf_digital_filter_config_t dflt_0_config;
  hal_adf_sad_config_t sad_0_config;

  if (HAL_ADF_Init(&hADF1, HAL_ADF1) != HAL_OK)
  {
    return NULL;
  }

  HAL_RCC_ADF1_EnableClock();

  if (HAL_RCC_ADF1_SetKernelClkSource(HAL_RCC_ADF1_CLK_SRC_HSI) != HAL_OK)
  {
    return NULL;
  }

  /* Global ADF1 configuration */
  if (HAL_ADF_SetConfig(&hADF1, 4) != HAL_OK)
  {
    return NULL;
  }
  if (HAL_ADF_SetConfigOutputClock(&hADF1, HAL_ADF_OUTPUT_CLOCK_CCK0, 8) != HAL_OK)
  {
    return NULL;
  }
  if (HAL_ADF_EnableOutputClock(&hADF1, HAL_ADF_OUTPUT_CLOCK_CCK0) != HAL_OK)
  {
    return NULL;
  }
if (HAL_ADF_Start(&hADF1) != HAL_OK)
  {
    return NULL;
  }

  /* Serial interface 0 configuration */
  sitf_0_config.mode = HAL_ADF_SITF_MODE_NORMAL_SPI;
  sitf_0_config.clock_source = HAL_ADF_SITF_CLOCK_SOURCE_CCK0;
  sitf_0_config.threshold = 31U;
  if (HAL_ADF_SITF_SetConfig(&hADF1, HAL_ADF_BLOCK_INDEX_0, &sitf_0_config) != HAL_OK)
  {
    return NULL;
  }
  if (HAL_ADF_SITF_Start(&hADF1, HAL_ADF_BLOCK_INDEX_0) != HAL_OK)
  {
    return NULL;
  }

  /* Bitstream matrix 0 configuration */
  if (HAL_ADF_BSMX_SetConfig(&hADF1, HAL_ADF_BLOCK_INDEX_0, HAL_ADF_BLOCK_INDEX_0, HAL_ADF_BSMX_INPUT_RISING) != HAL_OK)
  {
    return NULL;
  }

  /* Digital filter 0 configuration */
  dflt_0_config.data_source = HAL_ADF_DFLT_DATA_SOURCE_BSMX;
  dflt_0_config.cic_mode = HAL_ADF_DFLT_CIC_ONE_FILTER_SINC5;
  dflt_0_config.decimation_ratio = 32U;
  dflt_0_config.gain = 5;
  dflt_0_config.acquisition_mode = HAL_ADF_DFLT_ACQ_MODE_ASYNC_CONT;
  dflt_0_config.trigger.source = HAL_ADF_DFLT_TRIG_EXTI15;
  dflt_0_config.trigger.edge = HAL_ADF_DFLT_TRIG_RISING_EDGE;
  if (HAL_ADF_DFLT_SetConfig(&hADF1, HAL_ADF_BLOCK_INDEX_0, &dflt_0_config) != HAL_OK)
  {
    return NULL;
  }
  if (HAL_ADF_DFLT_SetFifoThreshold(&hADF1, HAL_ADF_BLOCK_INDEX_0, HAL_ADF_DFLT_FIFO_THRESHOLD_NOT_EMPTY) != HAL_OK)
  {
    return NULL;
  }
  if (HAL_ADF_DFLT_EnableReshapeFilter(&hADF1, HAL_ADF_BLOCK_INDEX_0, HAL_ADF_DFLT_RSF_DR_4) != HAL_OK)
  {
    return NULL;
  }
  if (HAL_ADF_DFLT_EnableHighPassFilter(&hADF1, HAL_ADF_BLOCK_INDEX_0, HAL_ADF_DFLT_HPF_CUT_OFF_0_000625FPCM) != HAL_OK)
  {
    return NULL;
  }

  /* Sound activity detector 0 configuration */
  sad_0_config.mode = HAL_ADF_SAD_MODE_SOUND;
  sad_0_config.memory_transfer = HAL_ADF_SAD_MEMORY_TRANSFER_DURING_DETECTION;
  sad_0_config.trigger_event = HAL_ADF_SAD_TRIGGER_ENTER_EXIT_DETECT;
  sad_0_config.minimum_ambient_noise = 4000U;
  if (HAL_ADF_SAD_SetConfig(&hADF1, HAL_ADF_BLOCK_INDEX_0, &sad_0_config) != HAL_OK)
  {
    return NULL;
  }
  if (HAL_ADF_SAD_SetFrameSize(&hADF1, HAL_ADF_BLOCK_INDEX_0, HAL_ADF_SAD_FRAME_SIZE_64_PCM_SAMPLES) != HAL_OK)
  {
    return NULL;
  }
  if (HAL_ADF_SAD_SetSignalToNoiseThreshold(&hADF1, HAL_ADF_BLOCK_INDEX_0, HAL_ADF_SAD_SIGNAL_TO_NOISE_6_DB) != HAL_OK)
  {
    return NULL;
  }
  if (HAL_ADF_SAD_SetHangoverTimeWindow(&hADF1, HAL_ADF_BLOCK_INDEX_0, HAL_ADF_SAD_HANGOVER_TIME_256_FRAMES) != HAL_OK)
  {
    return NULL;
  }
  if (HAL_ADF_SAD_EnableHysteresis(&hADF1, HAL_ADF_BLOCK_INDEX_0) != HAL_OK)
  {
    return NULL;
  }
  /* ### ADF1 GPIO Configuration ########################### */
  /* GPIO Clocks activation */
  HAL_RCC_GPIOG_EnableClock();

  hal_gpio_config_t  gpio_config;

  /**
    [GPIO Pin] ------> [Signal Name]

       PG11    ------>   ADF1_CCK0
       PG14    ------>   ADF1_SDI0
    **/
  gpio_config.mode        = HAL_GPIO_MODE_ALTERNATE;
  gpio_config.output_type = HAL_GPIO_OUTPUT_PUSHPULL;
  gpio_config.pull        = HAL_GPIO_PULL_NO;
  gpio_config.speed       = HAL_GPIO_SPEED_FREQ_LOW;
  gpio_config.alternate   = HAL_GPIO_AF_14;
  HAL_GPIO_Init(HAL_GPIOG, HAL_GPIO_PIN_11 | HAL_GPIO_PIN_14, &gpio_config);

  /* Configure the DMA for digital filter 0 */

  /* Configure the GPDMA1_CH0 DMA channel for ADF1 flt0 */
  if (HAL_DMA_Init(&hGPDMA1_CH0, HAL_GPDMA1_CH0) != HAL_OK)
  {
    return NULL;
  }

  HAL_RCC_GPDMA1_EnableClock();

  hal_dma_direct_xfer_config_t xfer_cfg_adf1_flt0_dma;
  xfer_cfg_adf1_flt0_dma.request         = HAL_GPDMA1_REQUEST_ADF1_FLT0;
  xfer_cfg_adf1_flt0_dma.direction       = HAL_DMA_DIRECTION_PERIPH_TO_MEMORY;
  xfer_cfg_adf1_flt0_dma.src_inc         = HAL_DMA_SRC_ADDR_FIXED;
  xfer_cfg_adf1_flt0_dma.dest_inc        = HAL_DMA_DEST_ADDR_INCREMENTED;
  xfer_cfg_adf1_flt0_dma.src_data_width  = HAL_DMA_SRC_DATA_WIDTH_HALFWORD;
  xfer_cfg_adf1_flt0_dma.dest_data_width = HAL_DMA_DEST_DATA_WIDTH_HALFWORD;
  xfer_cfg_adf1_flt0_dma.priority        = HAL_DMA_PRIORITY_LOW_WEIGHT_LOW;

  if (HAL_DMA_SetConfigPeriphLinkedListCircularXfer(&hGPDMA1_CH0, &DMA_Node_ADF1_FLT0, &xfer_cfg_adf1_flt0_dma) != HAL_OK)
  {
    return NULL;
  }

  if (HAL_DMA_SetLinkedListXferFetchNodePort(&hGPDMA1_CH0, HAL_DMA_PORT0) != HAL_OK)
  {
    return NULL;
  }

  /* Enable the interruption for GPDMA1_CH0 */
  HAL_CORTEX_NVIC_SetPriority(GPDMA1_CH0_IRQn, HAL_CORTEX_NVIC_PREEMP_PRIORITY_1, HAL_CORTEX_NVIC_SUB_PRIORITY_0);
  HAL_CORTEX_NVIC_EnableIRQ(GPDMA1_CH0_IRQn);

  /* Link the DMA handle to the ADF handle */
  if (HAL_ADF_SetDMA(&hADF1, HAL_ADF_BLOCK_INDEX_0, &hGPDMA1_CH0) != HAL_OK)
  {
    return NULL;
  }

  /* Enable the interruption for ADF block 0 */
  HAL_CORTEX_NVIC_SetPriority(ADF1_FLT0_IRQn, HAL_CORTEX_NVIC_PREEMP_PRIORITY_0, HAL_CORTEX_NVIC_SUB_PRIORITY_0);
  HAL_CORTEX_NVIC_EnableIRQ(ADF1_FLT0_IRQn);

  return &hADF1;
}

void mx_adf1_deinit(void)
{
  /* Disable the interruption for ADF block 0 */
  HAL_CORTEX_NVIC_DisableIRQ(ADF1_FLT0_IRQn);

  (void)HAL_ADF_SITF_Stop(&hADF1, HAL_ADF_BLOCK_INDEX_0);
  (void)HAL_ADF_Stop(&hADF1);
  (void)HAL_ADF_DeInit(&hADF1);

  HAL_RCC_ADF1_DisableClock();

  HAL_RCC_ADF1_Reset();

  /* De-initialize all GPIOG pins associated with ADF1 */
  HAL_GPIO_DeInit(HAL_GPIOG, HAL_GPIO_PIN_11 | HAL_GPIO_PIN_14);

  /* De-initialize the DMA channel */
  HAL_DMA_DeInit(&hGPDMA1_CH0);

  /* Disable the interruption for DMA */
  HAL_CORTEX_NVIC_DisableIRQ(GPDMA1_CH0_IRQn);
}

hal_adf_handle_t *mx_adf1_gethandle(void)
{
  return &hADF1;
}

/******************************************************************************/
/*                     GPDMA1 channel 0 interrupt                    */
/******************************************************************************/
void GPDMA1_CH0_IRQHandler(void)
{
  HAL_DMA_IRQHandler(&hGPDMA1_CH0);
}

/******************************************************************************/
/*                     ADF1 filter 0 global interrupt                    */
/******************************************************************************/
void ADF1_FLT0_IRQHandler(void)
{
  HAL_ADF_IRQHandler(&hADF1, HAL_ADF_BLOCK_INDEX_0);
}
