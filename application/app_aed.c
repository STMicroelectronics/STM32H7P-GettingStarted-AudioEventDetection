/**
  ******************************************************************************
  * file           : app_aed.c
  * brief          : AED example application
  ******************************************************************************
  *
  * Copyright (c) 2026 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "app_aed.h"
#include "app_config.h"
#include "dpu.h"
#include "mx_hsp_engine_app.h"
#include "dpu_config.h"
#include "mx_led.h"
#include "preproc_dpu.h"
#include "ai_dpu.h"
#include "mx_basic_stdio_app.h"
#include "gs_utils.h"
#ifdef APP_LCD
#include "oled.h"
#include "pict_st_logo.h"
#endif

/* Private define ------------------------------------------------------------*/
#define AUDIO_PATCH_LEN (AI_SPECT_WIN_LEN + (AI_SPECT_COL - 1) * AI_SPECT_HOP_LEN)
#define AUDIO_ACQ_LEN (AI_SPECT_COL * AI_SPECT_HOP_LEN)
#define AUDIO_ACQ_LEN_MS ((uint32_t)(1000.0F * (float)AUDIO_ACQ_LEN / (float)AI_SENSOR_ODR))
#define AUDIO_HALF_BUFF_SIZE (AUDIO_PATCH_LEN * 2)
#define AUDIO_BUFF_SIZE (AUDIO_HALF_BUFF_SIZE * 2)

/**
 * @brief Context used for pre-processing audio data.
 */
typedef struct
{
  pre_proc_dpu_ctx_t dpu_ctx;
  uint8_t acq_buff[AUDIO_BUFF_SIZE];
  int8_t *out_p;
} pre_proc_ctx_t;

/**
 * @brief Context used to run AI inference.
 */
typedef struct
{
  ai_dpu_ctx_t dpu_ctx;
  int8_t *ai_in_p;
  float *ai_out_p;
} ai_proc_ctx_t;

static pre_proc_ctx_t pre_proc_ctx;
static ai_proc_ctx_t ai_proc_ctx;

/* Private variables ---------------------------------------------------------*/
volatile int audio_acq_buff_size;
volatile uint8_t *p_acquired_audio_samples;
static unsigned char c;
static int exit_loop;

/* Private function prototypes -----------------------------------------------*/
static void start_audio_sensors(void);
static void stop_audio_sensors(void);
static void error_handler(void);

/* Exported functions --------------------------------------------------------*/

/**
  * @brief Initializes the application and its processing components.
  * @return Application initialization status.
  *
  * No initialization is required here for the LED part. The GPIO resource is
  * already configured at system initialization.
  */
app_status_t app_init(void)
{
  if (SYSTEM_OK != mx_basic_stdio_init())
  {
    goto app_init_exit;
  }
#ifdef APP_LCD
  if (!oled_init())
  {
    goto app_init_exit;
  }
  if (!oled_load_splash_screen(pict_st_logo, 3000))
  {
    goto app_init_exit;
  }
#endif

#ifdef USE_HSP
  /* Initialize the Middleware HSP Engine */
  if (HSP_CORE_OK != mx_hsp_engine_init_hsp1())
  {
    goto app_init_exit;
  }
#endif /* USE_HSP */
  print_app_header();
  print_system_setting();

  if (DPU_OK != ai_dpu_load_model(&ai_proc_ctx.dpu_ctx))
  {
    goto app_init_exit;
  }
  ai_proc_ctx.ai_in_p = (int8_t *)ai_proc_ctx.dpu_ctx.p_stai_inputs[0];
  ai_proc_ctx.ai_out_p = (float *)ai_proc_ctx.dpu_ctx.p_stai_outputs[0];

  if (DPU_OK != pre_proc_dpu_init(&pre_proc_ctx.dpu_ctx))
  {
    goto app_init_exit;
  }

  /* transfer quantization parameters included in AI model to preproc_ctx */
  pre_proc_ctx.dpu_ctx.out_Q_offset = ai_proc_ctx.dpu_ctx.input_Q_offset;
  pre_proc_ctx.dpu_ctx.out_Q_inv_scale = ai_proc_ctx.dpu_ctx.input_Q_inv_scale;
  pre_proc_ctx.out_p = ai_proc_ctx.ai_in_p;

  start_audio_sensors();
  init_cpu_stats();
  print_header();
  HAL_DBGMCU_EnableDebugLowPowerMode(HAL_DBGMCU_LP_MODE_DEBUG_ALL);
  HAL_UART_Receive_IT(BASIC_STDIO_UART_GETHANDLE(), &c, 1);
  exit_loop = 0;

  return EXEC_STATUS_INIT_OK;
app_init_exit:
  return EXEC_STATUS_ERROR;
} /* end app_init */

/**
  * @brief Processes pending audio data and updates the user interface.
  * @return Application processing status, or EXEC_STATUS_EXIT on request.
  */
app_status_t app_process(void)
{
  if (audio_acq_buff_size >= AUDIO_HALF_BUFF_SIZE)
  {
    audio_acq_buff_size -= AUDIO_HALF_BUFF_SIZE;
    if (DPU_OK != pre_proc_dpu_process(&pre_proc_ctx.dpu_ctx,
                                       p_acquired_audio_samples,
                                       pre_proc_ctx.out_p))
    {
      goto app_process_exit;
    }
    
    if (pre_proc_ctx.dpu_ctx.S_Spectr.spectro_sum > AI_SPECT_SILENCE_THR)
    {
      if (DPU_OK != ai_dpu_process(&ai_proc_ctx.dpu_ctx))
      {
        goto app_process_exit;
      }
      print_ai_classes_output(ai_proc_ctx.ai_out_p);
    }
    pre_proc_ctx.dpu_ctx.S_Spectr.spectro_sum = 0;
  }

  print_menu();

  if (exit_loop)
  {
    print_footer();
    return EXEC_STATUS_EXIT;
  }

  return EXEC_STATUS_OK;
app_process_exit:
  return EXEC_STATUS_ERROR;
}
/**
  * @brief De-initializes the application before leaving the scenario.
  * @return Application de-initialization status.
  */
app_status_t app_deinit(void)
{
  /* No de-init concept for a LED part. */
  /* Stop audio sensors */
  stop_audio_sensors();
  print_cpu_stats_summary();
#ifdef APP_LCD
  oled_deinit();
#endif
  return EXEC_STATUS_OK;
} /* end app_deinit */

/* Callback Definition -------------------------------------------------------*/
/**
  * @brief Handles completion of a UART receive interrupt.
  * @param huart UART handle.
  * @param size_byte Number of received bytes.
  * @param rx_event UART receive event type.
  */
void HAL_UART_RxCpltCallback(hal_uart_handle_t *huart, uint32_t size_byte,\
                             hal_uart_rx_event_types_t rx_event)
{
  /* Prevent unused argument(s) compilation warning */
  STM32_UNUSED(huart);
  STM32_UNUSED(size_byte);
  STM32_UNUSED(rx_event);
  exit_loop = 1;
}

/**
  * @brief  MDF acquisition complete callback.
  * @param  hadf ADF handle.
  * @param  digital_filter_index Digital filter that generated the event.
  */
void HAL_ADF_DFLT_AcqCpltCallback(hal_adf_handle_t *hadf,\
                                   hal_adf_block_index_t digital_filter_index)
{
  /* Prevent unused argument(s) compilation warning */
  STM32_UNUSED(hadf);
  audio_acq_buff_size += AUDIO_HALF_BUFF_SIZE;
  p_acquired_audio_samples = pre_proc_ctx.acq_buff;
}

/**
  * @brief  MDF acquisition half complete callback.
  * @param  hadf ADF handle.
  * @param  digital_filter_index Digital filter that generated the event.
  */
void HAL_ADF_DFLT_AcqHalfCpltCallback(hal_adf_handle_t *hadf,\
                                      hal_adf_block_index_t digital_filter_index)
{
  /* Prevent unused argument(s) compilation warning */
  STM32_UNUSED(hadf);
  audio_acq_buff_size += AUDIO_HALF_BUFF_SIZE;
  p_acquired_audio_samples = pre_proc_ctx.acq_buff + AUDIO_HALF_BUFF_SIZE;
}

/* local functions */
static void start_audio_sensors(void)
{
  ASSERT_DBG_PARAM(AUDIO_BUFF_SIZE < 0xFFFF);
  if (HAL_OK != HAL_ADF_DFLT_StartAcq_DMA(mx_adf1_gethandle(), \
    HAL_ADF_BLOCK_INDEX_0, \
    &(hal_adf_dma_config_t){.address = (uint32_t)pre_proc_ctx.acq_buff, \
                            .data_length_byte = AUDIO_BUFF_SIZE, \
                            .data_resolution = HAL_ADF_DMA_DATA_RESOLUTION_MSB_ONLY}))
  {
    error_handler();
  }
  if (HAL_OK != HAL_ADF_SAD_Start_IT(mx_adf1_gethandle(), HAL_ADF_BLOCK_INDEX_0))
  {
    error_handler();
  } 
  PRINTF("Audio acquisition\n\r");
  PRINTF("- sampling freq : %lu Hz\n\r", (uint32_t)AI_SENSOR_ODR);
  PRINTF("- acq period    : %lu ms\n\r", (uint32_t)AUDIO_ACQ_LEN_MS);
}

static void stop_audio_sensors(void)
{
  if (HAL_OK != HAL_ADF_DFLT_StopAcq_DMA(mx_adf1_gethandle(), HAL_ADF_BLOCK_INDEX_0))
  {
    error_handler();
  }
  if (HAL_OK != HAL_ADF_SAD_Stop_IT(mx_adf1_gethandle(), HAL_ADF_BLOCK_INDEX_0))
  {
    error_handler();
  } 
}

static void error_handler(void)
{
  while (1)
  {
    /* Repeated flashing status LED (100ms) when execution loop is exited */
    led_toggle(ERROR_LED);
    HAL_Delay(100);

  }
} /* end error_handler */
