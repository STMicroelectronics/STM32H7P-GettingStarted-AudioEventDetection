/**
  ******************************************************************************
  * @file           : mx_aes.c
  * @brief          : AES Peripheral initialization
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
/* Includes ------------------------------------------------------------------*/
#include "mx_aes.h"



/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private functions prototype------------------------------------------------*/
/* Exported variables by reference--------------------------------------------*/
static hal_aes_handle_t hAES;
  static hal_dma_handle_t hLPDMA1_CH0;
static hal_dma_handle_t hLPDMA1_CH1;

/******************************************************************************/
/* Exported functions for AES in HAL layer (SW instance MyAES_1) */
/******************************************************************************/
hal_aes_handle_t *mx_aes_cfg1_hal_init(void)
{
  if (HAL_AES_Init(&hAES, HAL_AES) != HAL_OK)
  {
    return NULL;
  }
  HAL_RCC_AES_EnableClock();

  hal_aes_gcm_config_t p_gcm_config;

  const uint32_t AESKey[4]          = {0xC939CC13, 0x397C1D37, 0xDE6AE0E1, 0xCB7C423C};
  hal_aes_key_size_t key_size       = HAL_AES_KEY_SIZE_128BIT;
  hal_aes_data_swapping_t data_swap = HAL_AES_DATA_SWAPPING_NO;

  uint32_t InitVector[4]            = {0x00000000, 0x00000000, 0x00000000, 0x00000002};

  uint32_t HeaderMessage[4]        = {0x24825602, 0xBD12A984, 0xE0092D3E, 0x448EDA5F};
  p_gcm_config.p_init_vect          = InitVector;
  p_gcm_config.p_header             = HeaderMessage;
  p_gcm_config.header_size_byte     = 16;

  if (HAL_AES_GCM_GMAC_SetConfig(&hAES, &p_gcm_config) != HAL_OK)
  {
    return NULL;
  }

  HAL_AES_SetNormalKey(&hAES, key_size, AESKey);
  HAL_AES_SetDataSwapping(&hAES, data_swap);
  /* Configure the DMA OUT */
          
  HAL_RCC_LPDMA1_EnableClock();

  if (HAL_DMA_Init(&hLPDMA1_CH1, HAL_LPDMA1_CH1) != HAL_OK)
  {
    return NULL;
  }


  hal_dma_direct_xfer_config_t xfer_cfg1;
  xfer_cfg1.request         = HAL_DMA_REQUEST_SW;
  xfer_cfg1.direction       = HAL_DMA_DIRECTION_PERIPH_TO_MEMORY;
  xfer_cfg1.src_inc         = HAL_DMA_SRC_ADDR_FIXED;
  xfer_cfg1.dest_inc        = HAL_DMA_DEST_ADDR_INCREMENTED;
  xfer_cfg1.src_data_width  = HAL_DMA_SRC_DATA_WIDTH_WORD;
  xfer_cfg1.dest_data_width = HAL_DMA_DEST_DATA_WIDTH_BYTE;
  xfer_cfg1.priority        = HAL_DMA_PRIORITY_LOW_WEIGHT_LOW;

  if (HAL_DMA_SetConfigPeriphDirectXfer(&hLPDMA1_CH1, &xfer_cfg1) != HAL_OK)
  {
    return NULL;
  }
    /* Enable the interruption for LPDMA1_CH1 */
  HAL_CORTEX_NVIC_SetPriority(LPDMA1_CH1_IRQn, HAL_CORTEX_NVIC_PREEMP_PRIORITY_0, HAL_CORTEX_NVIC_SUB_PRIORITY_0);
  HAL_CORTEX_NVIC_EnableIRQ(LPDMA1_CH1_IRQn);


  /* Link the Output DMA handle to the AES handle */
  if (HAL_AES_SetOutDMA(&hAES, &hLPDMA1_CH1) != HAL_OK)
  {
    return NULL;
  }

  /* Configure the DMA IN */
      
  HAL_RCC_LPDMA1_EnableClock();

  if (HAL_DMA_Init(&hLPDMA1_CH0, HAL_LPDMA1_CH0) != HAL_OK)
  {
    return NULL;
  }


    
  hal_dma_direct_xfer_config_t xfer_cfg_aes_in_dma;
  xfer_cfg_aes_in_dma.request         = HAL_LPDMA1_REQUEST_AES_IN;
  xfer_cfg_aes_in_dma.direction       = HAL_DMA_DIRECTION_MEMORY_TO_PERIPH;
  xfer_cfg_aes_in_dma.src_inc         = HAL_DMA_SRC_ADDR_INCREMENTED;
  xfer_cfg_aes_in_dma.dest_inc        = HAL_DMA_DEST_ADDR_FIXED;
  xfer_cfg_aes_in_dma.src_data_width  = HAL_DMA_SRC_DATA_WIDTH_BYTE;
  xfer_cfg_aes_in_dma.dest_data_width = HAL_DMA_DEST_DATA_WIDTH_WORD;
  xfer_cfg_aes_in_dma.priority        = HAL_DMA_PRIORITY_LOW_WEIGHT_LOW;

  if (HAL_DMA_SetConfigPeriphDirectXfer(&hLPDMA1_CH0, &xfer_cfg_aes_in_dma) != HAL_OK)
  {
    return NULL;
  }
    /* Enable the interruption for LPDMA1_CH0 */
  HAL_CORTEX_NVIC_SetPriority(LPDMA1_CH0_IRQn, HAL_CORTEX_NVIC_PREEMP_PRIORITY_0, HAL_CORTEX_NVIC_SUB_PRIORITY_0);
  HAL_CORTEX_NVIC_EnableIRQ(LPDMA1_CH0_IRQn);


  /* Link the Input DMA handle to the AES handle */
  if (HAL_AES_SetInDMA(&hAES, &hLPDMA1_CH0) != HAL_OK)
  {
    return NULL;
  }




  return &hAES;
}

void mx_aes_cfg1_hal_deinit(void)
{


  (void)HAL_AES_DeInit(&hAES);
  HAL_RCC_AES_Reset();
  HAL_RCC_AES_DisableClock();
  /* De-initialize the DMA channel */
  HAL_DMA_DeInit(&hLPDMA1_CH1);

  /* Disable the interruption for DMA */
  HAL_CORTEX_NVIC_DisableIRQ(LPDMA1_CH1_IRQn);

  /* De-initialize the DMA channel */
  HAL_DMA_DeInit(&hLPDMA1_CH0);

  /* Disable the interruption for DMA */
  HAL_CORTEX_NVIC_DisableIRQ(LPDMA1_CH0_IRQn);

}

hal_aes_handle_t *mx_aes_hal_gethandle(void)
{
  return &hAES;
}

/******************************************************************************/
/*                     LPDMA1 channel1 global interrupt                    */
/******************************************************************************/
void LPDMA1_CH1_IRQHandler(void)
{
  HAL_DMA_IRQHandler(&hLPDMA1_CH1);
}

/******************************************************************************/
/*                     LPDMA1 channel0 global interrupt                    */
/******************************************************************************/
void LPDMA1_CH0_IRQHandler(void)
{
  HAL_DMA_IRQHandler(&hLPDMA1_CH0);
}

