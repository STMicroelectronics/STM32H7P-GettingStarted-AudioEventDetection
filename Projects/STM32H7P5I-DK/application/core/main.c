/**
  ******************************************************************************
  * file           : main.c
  * brief          : Main program body
  *                  Calls target system initialization then loop in main.
  ******************************************************************************
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
#include "main.h"
#include "gs_utils.h"
#include "app_audio.h"
#ifdef USE_HSP
#include "hsp_conf.h"
#include "hsp_def.h"
#include "hsp_core.h"
#include "hsp_proclist.h"
#endif
#include "assert.h"
#include <stdio.h>

static __IO uint32_t exit_loop = 0;

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
hal_uart_handle_t uart_vcp;
hal_adf_handle_t AdfHandle0;
hal_dma_handle_t hdma;
__ALIGNED(64)
hal_dma_node_t dma_node;
#ifdef USE_HSP
hal_hsp_handle_t hhsp1;
hsp_core_handle_t hmw;
#endif
/* Private functions prototype -----------------------------------------------*/
void init_LED(void);
void init_UART(void);
void init_NPU(void);
uint8_t led_pattern_step(void);

void init_dwt();
void time_in(void);
uint32_t time_out(void);
static void run_audio(void);
static void ADF1_Init(void);
static void GPDMA1_Init(void);
#ifdef USE_HSP
static void MPU_HSP_Config(void);
static void MPU_AdjustRegionAddresssize(uint32_t Address, uint32_t size, hal_cortex_mpu_region_config_t* pInit);
static void HSP_Init(void);
#endif
static void SystemClock_Config(void);

int main(void)
{
  int ret;

  ret = HAL_Init();
  assert(ret == HAL_OK);

  HAL_CORTEX_NVIC_SetPriorityGrouping(HAL_CORTEX_NVIC_PRIORITY_GROUP_4);

  /* Configure the system clock */
  SystemClock_Config();

  #if defined(USE_HSP)
  HSP_Init();
  #endif
  /* Enable Cache */
  SCB_EnableICache();
  SCB_EnableDCache();
  HAL_DBGMCU_EnableDebugLowPowerMode(HAL_DBGMCU_LP_MODE_DEBUG_ALL);

  /* Initialize all configured peripherals */
  init_UART();
  init_NPU();
  ADF1_Init();
  GPDMA1_Init();

  PrintSystemSetting();
  run_audio();
}


static void run_audio(void)
{
  unsigned char c;

  InitCpuStats();

  audio_init();

  PrintHeader();
  HAL_UART_Receive_IT(&uart_vcp, &c, 1);
  while (exit_loop == 0)
  {
    PrintMenu();
    audio_exec();
  }

  audio_deinit();
  PrintFooter();
  PrintCpuStatsSummary();
}

#ifdef USE_HSP
static void HSP_Init(void)
{
  if (HAL_HSP_Init(&hhsp1, HAL_HSP1) != HAL_OK)
  {
      Error_Handler();
  }

  HAL_RCC_HSP_Reset();

  hmw.hdriver = &hhsp1;
  if (HSP_CORE_Init(&hmw) != HSP_CORE_OK)
  {
      while(1);
  }

  MPU_HSP_Config();
}

static void MPU_HSP_Config(void)
{
  hal_cortex_mpu_region_config_t p_region_config = {0};
  uint32_t address;
  uint32_t size;
  hal_cortex_mpu_region_idx_t index = HAL_CORTEX_MPU_REGION_0;

  /* Disables the MPU */
  HAL_CORTEX_MPU_Disable();

  p_region_config.base_addr = 0x00000000;
  p_region_config.size = HAL_CORTEX_MPU_REGION_SIZE_4GB;
  p_region_config.access_attr = HAL_CORTEX_MPU_REGION_ALL_RW_FAULT;
  p_region_config.mem_attr = HAL_CORTEX_MPU_NORMAL_MEM_SHAREABLE_IO_NCACHEABLE;
  p_region_config.exec_attr = HAL_CORTEX_MPU_EXECUTION_ATTR_DISABLE;
  p_region_config.sub_region = HAL_CORTEX_MPU_SUB_REGION_DISABLE_7 | HAL_CORTEX_MPU_SUB_REGION_DISABLE_2 \
                               | HAL_CORTEX_MPU_SUB_REGION_DISABLE_1 |HAL_CORTEX_MPU_SUB_REGION_DISABLE_0;
  p_region_config.access_attr = HAL_CORTEX_MPU_REGION_ALL_RW;

  HAL_CORTEX_MPU_SetConfigRegion(HAL_CORTEX_MPU_REGION_0, &p_region_config);
  HAL_CORTEX_MPU_EnableRegion(HAL_CORTEX_MPU_REGION_0);

  index++;

  /* Initialize the non cacheable region */
#if defined ( __ICCARM__ )
  /* get the region attribute form the icf file */
  extern uint32_t __region_HSP_BRAMAB_start__;
  extern uint32_t __region_HSP_BRAMAB_end__;

  address = (uint32_t)&__region_HSP_BRAMAB_start__;
  size =  (uint32_t) &__region_HSP_BRAMAB_end__ - address + 1;


#elif defined (__CC_ARM) || defined(__ARMCC_VERSION)
  extern uint32_t Image$$RW_NONCACHEABLEBUFFER$$Base;
  extern uint32_t Image$$RW_NONCACHEABLEBUFFER$$Length;
  extern uint32_t Image$$RW_NONCACHEABLEBUFFER$$ZI$$Length;

  address = (uint32_t)&Image$$RW_NONCACHEABLEBUFFER$$Base;
  size  = (uint32_t)&Image$$RW_NONCACHEABLEBUFFER$$Length + (uint32_t)&Image$$RW_NONCACHEABLEBUFFER$$ZI$$Length;
#elif defined ( __GNUC__ )
  extern int __NONCACHEABLEBUFFER_BEGIN;
  extern int __NONCACHEABLEBUFFER_END;

  address = (uint32_t)&__NONCACHEABLEBUFFER_BEGIN;
  size  = (uint32_t)&__NONCACHEABLEBUFFER_END - (uint32_t)&__NONCACHEABLEBUFFER_BEGIN;
#else
#error "Compiler toolchain is unsupported"
#endif


  if (size != 0)
  {
    /* Configure the MPU attributes as Normal Non Cacheable */
    p_region_config.access_attr = HAL_CORTEX_MPU_REGION_ALL_RW;
//    p_region_config.mem_attr = HAL_CORTEX_MPU_NORMAL_MEM_NSHAREABLE_IO_NCACHEABLE;
    p_region_config.mem_attr = HAL_CORTEX_MPU_NORMAL_MEM_SHAREABLE_IO_WB_RWA;
    p_region_config.exec_attr = HAL_CORTEX_MPU_EXECUTION_ATTR_DISABLE;
    p_region_config.sub_region = HAL_CORTEX_MPU_SUB_REGION_ENABLE_ALL;

    MPU_AdjustRegionAddresssize(address, size, &p_region_config);
    HAL_CORTEX_MPU_SetConfigRegion(index, &p_region_config);
    HAL_CORTEX_MPU_EnableRegion(index);
    index++;
  }

  /* Reset unused MPU regions */
  for(; index < __MPU_REGIONCOUNT ; index++)
  {
    /* All unused regions disabled */
    HAL_CORTEX_MPU_DisableRegion(index);
  }

  /* Enables the MPU */
  HAL_CORTEX_MPU_Enable(HAL_CORTEX_MPU_HARDFAULT_NMI_DISABLE, HAL_CORTEX_MPU_ACCESS_FAULT_ONLY_PRIV);
}

/**
  * @brief This function adjusts the MPU region Address and size within an MPU configuration.
  * @param Address memory address
  * @param size memory size
  * @param pInit pointer to an MPU initialization structure
  * @retval None
  */
static void MPU_AdjustRegionAddresssize(uint32_t Address, uint32_t size, hal_cortex_mpu_region_config_t* pInit)
{
  static uint8_t loopcontrol = 0;
  uint32_t Modulo;

  /* control the loop increment */
  loopcontrol++;

  if (loopcontrol > 3)
  {
    /* the scatter file input is too complex to determine the MPU configuration */
    Error_Handler();
  }

  /* Compute the MPU region size */
  pInit->size = (hal_cortex_mpu_region_size_t)((31 - __CLZ(size)) - 1);
  if (size > (1 << (pInit->size + 1)))
  {
    pInit->size++;
  }
  Modulo = Address % (1 << (pInit->size + 1));
  if (0 != Modulo)
  {
    /* Align address with MPU region size considering there is no need to increase the size */
    MPU_AdjustRegionAddresssize(Address - Modulo, size + Modulo, pInit);
  }
  else
  {
    pInit->base_addr = Address;
  }

  /* control the loop decrement */
  loopcontrol--;
}
#endif



/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  /* Set FLASH latency */
  if (HAL_FLASH_ITF_SetLatency(HAL_FLASH, HAL_FLASH_ITF_LATENCY_4) != HAL_OK)
  {
    Error_Handler();
  }
  while(HAL_FLASH_ITF_GetLatency(HAL_FLASH) != HAL_FLASH_ITF_LATENCY_4);

  /* Set the regulator supply output voltage */
  if (HAL_PWR_SetMainRegulatorSupply(HAL_PWR_MAIN_REGULATOR_NOT_BYPASSED_SUPPLY) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_PWR_SetMainRegulatorVoltageScalingRange(HAL_PWR_VOLT_SCALE_0) != HAL_OK)
  {
    Error_Handler();
  }

  if (HAL_RCC_HSI_Enable(HAL_RCC_HSI_DIV_1) != HAL_OK)
  {
    Error_Handler();
  }

  /* Configure and enable main PLL */
  hal_rcc_pll_config_t pll_config = {
   .pll_source      = HAL_RCC_PLL_SRC_HSI, /* 64MHz */
   .pll_sscg_status = HAL_RCC_PLL_SSCG_DISABLE,
   .pll_m           = 4U, /* =DIVM */
   .pll_n           = 25U,
   .pll_fracn       = 0U,
   .pll_p           = 1U,
   .pll_q           = 1U,
   .pll_r           = 1U,
   .pll_s           = 1U,
   .pll_t           = 1U
  };

  /* PLL1 configuration for system clock (PLL1_P at 400MHz) */
  if (HAL_RCC_PLL1_SetConfig(&pll_config) != HAL_OK)
  {
    Error_Handler();
  }

  if (HAL_RCC_PLL1_Enable() != HAL_OK)
  {
    Error_Handler();
  }

  /* Enable PLL Output */
  if (HAL_RCC_PLL1_EnableOutput(HAL_RCC_PLL1_OUTPUT_P) != HAL_OK)
  {
    Error_Handler();
  }

  hal_rcc_bus_clk_config_t config_bus = {
   .sys_cpu_clk_prescaler = HAL_RCC_SYSCPUCLK_PRESCALER1, /* 400MHz */
   .hclk_prescaler        = HAL_RCC_HCLK_PRESCALER2,      /* 200MHz */
   .pclk1_prescaler       = HAL_RCC_PCLK_PRESCALER2,      /* 200MHz */
   .pclk2_prescaler       = HAL_RCC_PCLK_PRESCALER2,      /* 200MHz */
   .pclk4_prescaler       = HAL_RCC_PCLK_PRESCALER2       /* 200MHz */
  };

  /* Set AXI, AHBs and APBs prescalers */
  if (HAL_RCC_SetBusClockConfig(&config_bus) != HAL_OK)
  {
    Error_Handler();
  }

  /* PLL1_P as system clock */
  if (HAL_RCC_SetSYSCLKSource(HAL_RCC_SYSCLK_SRC_PLLCLK) != HAL_OK)
  {
    Error_Handler();
  }

  /* Insure 1us transition state at intermediate medium speed clock based on DWT*/
  CoreDebug->DEMCR |= CoreDebug_DEMCR_TRCENA_Msk;

  DWT->CTRL |= DWT_CTRL_CYCCNTENA_Msk;
  DWT->CYCCNT = 0;
  while(DWT->CYCCNT < 100);

  /* Update SysTick */
  SystemCoreClockUpdate();

  if (HAL_InitTick(uwTickFreq, uwTickPrio) != HAL_OK)
  {
    Error_Handler();
  }
}

void init_NPU(void)
{
  HAL_RCC_NPU_EnableClock();    // NPU clocks are = CPU clocks on h7p
  HAL_RCC_NPU_EnableClockInSleepMode();
}

void init_UART(void)
{
  hal_gpio_config_t uart_gpioconfig;
  hal_uart_config_t uart_config;


  uart_gpioconfig.mode = HAL_GPIO_MODE_ALTERNATE;
  uart_gpioconfig.alternate = HAL_GPIO_AF_7;       // USART2 -> AF7 for both Rx/Tx on PA3/PA2
  uart_gpioconfig.speed = HAL_GPIO_SPEED_FREQ_VERY_HIGH;
  uart_gpioconfig.output_type = HAL_GPIO_OUTPUT_PUSHPULL;
  uart_gpioconfig.pull = HAL_GPIO_PULL_UP;

  uart_config.baud_rate=115200;
  uart_config.parity = HAL_UART_PARITY_NONE;
  uart_config.hw_flow_ctl = HAL_UART_HW_CONTROL_NONE;
  uart_config.stop_bits = HAL_UART_STOP_BIT_1;
  uart_config.word_length = HAL_UART_WORD_LENGTH_8_BIT;
  uart_config.direction = HAL_UART_DIRECTION_TX_RX;
  uart_config.oversampling = HAL_UART_OVERSAMPLING_16;
  uart_config.one_bit_sampling = HAL_UART_ONE_BIT_SAMPLE_DISABLE;
  uart_config.clock_prescaler = HAL_UART_PRESCALER_DIV1;

  HAL_RCC_GPIOA_EnableClock();
  HAL_GPIO_Init(HAL_GPIOA, HAL_GPIO_PIN_3, &uart_gpioconfig);
  HAL_GPIO_Init(HAL_GPIOA, HAL_GPIO_PIN_2, &uart_gpioconfig);
  HAL_RCC_USART2_EnableClock();

  if (HAL_UART_Init(&uart_vcp, HAL_UART2) != HAL_OK)
  {
    Error_Handler();
  }

  HAL_CORTEX_NVIC_SetPriority(USART2_IRQn, HAL_CORTEX_NVIC_PREEMP_PRIORITY_1, HAL_CORTEX_NVIC_SUB_PRIORITY_0);
  HAL_CORTEX_NVIC_EnableIRQ(USART2_IRQn);

  if (HAL_UART_SetConfig(&uart_vcp, &uart_config) != HAL_OK)
  {
    Error_Handler();
  }

  if (HAL_UART_SetTxFifoThreshold(&uart_vcp, HAL_UART_FIFO_THRESHOLD_1_8) != HAL_OK)
  {
    Error_Handler();
  }

  if (HAL_UART_SetRxFifoThreshold(&uart_vcp, HAL_UART_FIFO_THRESHOLD_1_8) != HAL_OK)
  {
    Error_Handler();
  }

  if (HAL_UART_DisableFifoMode(&uart_vcp) != HAL_OK)
  {
    Error_Handler();
  }


}


/**
 * @brief ADF1 Initialization Function
 * @param None
 * @retval None
 */
static void ADF1_Init(void)
{
  /* GPIO Ports Clock Enable */
  HAL_RCC_GPIOG_EnableClock();

  /** ADF1 GPIO Configuration
    PG11     ------> ADF1_CCK0
    PG14     ------> ADF1_SDI0
    */
  hal_gpio_config_t  gpio_config;
  gpio_config.mode        = HAL_GPIO_MODE_ALTERNATE;
  gpio_config.output_type = HAL_GPIO_OUTPUT_PUSHPULL;
  gpio_config.pull        = HAL_GPIO_PULL_NO;
  gpio_config.speed       = HAL_GPIO_SPEED_FREQ_VERY_HIGH;
  gpio_config.alternate   = HAL_GPIO_AF_14;

  if (HAL_GPIO_Init(HAL_GPIOG, HAL_GPIO_PIN_11 | HAL_GPIO_PIN_14, &gpio_config) != HAL_OK)
  {
    Error_Handler();
  }

  /* HSI at 64MHz */
  if (HAL_RCC_ADF1_SetKernelClkSource(HAL_RCC_ADF1_CLK_SRC_HSI) != HAL_OK)
  {
    Error_Handler();
  }

  if (HAL_ADF_Init(&AdfHandle0, HAL_ADF1) != HAL_OK)
  {
    Error_Handler();
  }

  if (HAL_ADF_SetConfig(&AdfHandle0, 8U) != HAL_OK)
  {
    Error_Handler();
  }

  if (HAL_ADF_SetConfigOutputClock(&AdfHandle0, HAL_ADF_OUTPUT_CLOCK_CCK0, 4U) != HAL_OK)
  {
    Error_Handler();
  }

  if (HAL_ADF_EnableOutputClock(&AdfHandle0, HAL_ADF_OUTPUT_CLOCK_CCK0) != HAL_OK)
  {
    Error_Handler();
  }

  if (HAL_ADF_DisableOutputClockTrigger(&AdfHandle0) != HAL_OK)
  {
    Error_Handler();
  }

  if (HAL_ADF_Start(&AdfHandle0) != HAL_OK)
  {
    Error_Handler();
  }

  hal_adf_serial_interface_config_t serial_interface_config;
  serial_interface_config.mode         = HAL_ADF_SITF_MODE_NORMAL_SPI;
  serial_interface_config.clock_source = HAL_ADF_SITF_CLOCK_SOURCE_CCK0;
  serial_interface_config.threshold    = 31;
  if (HAL_ADF_SITF_SetConfig(&AdfHandle0, HAL_ADF_BLOCK_INDEX_0, &serial_interface_config) != HAL_OK)
  {
    Error_Handler();
  }

  if (HAL_ADF_SITF_Start(&AdfHandle0, HAL_ADF_BLOCK_INDEX_0) != HAL_OK)
  {
    Error_Handler();
  }

  if (HAL_ADF_BSMX_SetConfig(&AdfHandle0, HAL_ADF_BLOCK_INDEX_0,
                             HAL_ADF_BLOCK_INDEX_0, HAL_ADF_BSMX_INPUT_RISING) != HAL_OK)
  {
    Error_Handler();
  }

  hal_adf_digital_filter_config_t digital_filter_config;
  digital_filter_config.data_source = HAL_ADF_DFLT_DATA_SOURCE_BSMX;
  digital_filter_config.cic_mode = HAL_ADF_DFLT_CIC_ONE_FILTER_SINC4;
  digital_filter_config.decimation_ratio = 32;
  digital_filter_config.gain = 15;
  digital_filter_config.acquisition_mode = HAL_ADF_DFLT_ACQ_MODE_ASYNC_CONT;
  digital_filter_config.trigger.source = HAL_ADF_DFLT_TRIG_TRGO;
  digital_filter_config.trigger.edge = HAL_ADF_DFLT_TRIG_RISING_EDGE;

  hal_adf_sad_config_t sad_config;
  sad_config.mode = HAL_ADF_SAD_MODE_SOUND;
  sad_config.memory_transfer = HAL_ADF_SAD_MEMORY_TRANSFER_DURING_DETECTION;
  sad_config.trigger_event = HAL_ADF_SAD_TRIGGER_ENTER_EXIT_DETECT;
  sad_config.minimum_ambient_noise = 1000;

  if (HAL_ADF_DFLT_SetConfig(&AdfHandle0, HAL_ADF_BLOCK_INDEX_0, &digital_filter_config) != HAL_OK)
  {
    Error_Handler();
  }

  if (HAL_ADF_DFLT_EnableReshapeFilter(&AdfHandle0, HAL_ADF_BLOCK_INDEX_0,
                                       HAL_ADF_DFLT_RSF_DR_4) != HAL_OK)
  {
    Error_Handler();
  }

  if (HAL_ADF_DFLT_EnableHighPassFilter(&AdfHandle0, HAL_ADF_BLOCK_INDEX_0,
                                        HAL_ADF_DFLT_HPF_CUT_OFF_0_000625FPCM) != HAL_OK)
  {
    Error_Handler();
  }

  if (HAL_ADF_SAD_SetConfig(&AdfHandle0, HAL_ADF_BLOCK_INDEX_0, &sad_config) != HAL_OK)
  {
    Error_Handler();
  }

  if (HAL_ADF_SAD_SetFrameSize(&AdfHandle0, HAL_ADF_BLOCK_INDEX_0,
                               HAL_ADF_SAD_FRAME_SIZE_64_PCM_SAMPLES) != HAL_OK)
  {
    Error_Handler();
  }

  if (HAL_ADF_SAD_SetLearningFrames(&AdfHandle0, HAL_ADF_BLOCK_INDEX_0,
                                     HAL_ADF_SAD_LEARNING_FRAMES_2) != HAL_OK)
  {
    Error_Handler();
  }

  if (HAL_ADF_SAD_SetSignalToNoiseThreshold(&AdfHandle0, HAL_ADF_BLOCK_INDEX_0,
                                            HAL_ADF_SAD_SIGNAL_TO_NOISE_6_DB) != HAL_OK)
  {
    Error_Handler();
  }

  if (HAL_ADF_SAD_SetHangoverTimeWindow(&AdfHandle0, HAL_ADF_BLOCK_INDEX_0,
                                         HAL_ADF_SAD_HANGOVER_TIME_512_FRAMES) != HAL_OK)
  {
    Error_Handler();
  }

  if (HAL_ADF_SAD_EnableHysteresis(&AdfHandle0, HAL_ADF_BLOCK_INDEX_0) != HAL_OK)
  {
    Error_Handler();
  }

  if(HAL_ADF_SAD_Start_IT(&AdfHandle0, HAL_ADF_BLOCK_INDEX_0) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief GPDMA1 Initialization Function
  * @param None
  * @retval None
  */
static void GPDMA1_Init(void)
{
  /* ADF Filter0 DMA Request Configuration */
  HAL_RCC_GPDMA1_EnableClock();

  if (HAL_DMA_Init(&hdma, HAL_GPDMA1_CH0) != HAL_OK)
  {
    Error_Handler();
  }

  hal_dma_direct_xfer_config_t xfer_cfg_adf1_flt0_dma;
  xfer_cfg_adf1_flt0_dma.request         = HAL_GPDMA1_REQUEST_ADF1_FLT0;
  xfer_cfg_adf1_flt0_dma.direction       = HAL_DMA_DIRECTION_PERIPH_TO_MEMORY;
  xfer_cfg_adf1_flt0_dma.src_inc         = HAL_DMA_SRC_ADDR_FIXED;
  xfer_cfg_adf1_flt0_dma.dest_inc        = HAL_DMA_DEST_ADDR_INCREMENTED;
  xfer_cfg_adf1_flt0_dma.src_data_width  = HAL_DMA_SRC_DATA_WIDTH_HALFWORD;
  xfer_cfg_adf1_flt0_dma.dest_data_width = HAL_DMA_DEST_DATA_WIDTH_HALFWORD;
  xfer_cfg_adf1_flt0_dma.priority        = HAL_DMA_PRIORITY_LOW_WEIGHT_LOW;

  if (HAL_DMA_SetConfigPeriphLinkedListCircularXfer(&hdma, &dma_node, &xfer_cfg_adf1_flt0_dma) != HAL_OK)
  {
    Error_Handler();
  }

  if (HAL_DMA_SetLinkedListXferFetchNodePort(&hdma, HAL_DMA_PORT0) != HAL_OK)
  {
    Error_Handler();
  }

  /* Enable the interruption for GPDMA1_CH0 */
  HAL_CORTEX_NVIC_SetPriority(GPDMA1_CH0_IRQn, HAL_CORTEX_NVIC_PREEMP_PRIORITY_1, HAL_CORTEX_NVIC_SUB_PRIORITY_0);
  HAL_CORTEX_NVIC_EnableIRQ(GPDMA1_CH0_IRQn);

  /* Link DMA request handle to the ADF handle */
  if (HAL_ADF_SetDMA(&AdfHandle0, HAL_ADF_BLOCK_INDEX_0, &hdma) != HAL_OK)
  {
    Error_Handler();
  }
}


void HAL_UART_RxCpltCallback(hal_uart_handle_t *huart, uint32_t size_byte, hal_uart_rx_event_types_t rx_event)
{
  STM32_UNUSED(huart);
  STM32_UNUSED(size_byte);
  STM32_UNUSED(rx_event);
  exit_loop = 1;
}


void assert_dbg_param_failed(uint8_t *file, uint32_t line)
{
    /* User can add his own implementation to report the file name and line number,
       ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
    while(1)
    {
        /* Infinite loop */
    }
}

void assert_dbg_state_failed(uint8_t *file, uint32_t line)
{
    // Handle the assert failure, e.g., log error, halt system, etc.
    while(1);
}


/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t* file, uint32_t line)
{
  UNUSED(file);
  UNUSED(line);
  __BKPT(0);
  while (1)
  {
  }
}
