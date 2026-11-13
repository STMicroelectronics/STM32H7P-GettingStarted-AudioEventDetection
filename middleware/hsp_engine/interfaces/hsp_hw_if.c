/**
  ******************************************************************************
  * @file    hsp_hw_if.c
  * @brief   This file implements the service provide by the HSP Hardware
  *          Interface.
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
#include "hsp_hw_if.h"
#include "hsp_fw_def.h"
#include "hsp_fw_ram.h"

/** @addtogroup HSP_ENGINE
  * @{
  */

/** @addtogroup HSP_INTERFACES
  * @{
  */

/** @addtogroup HSP_HW_IF
  * @{
  */

/* Private constants ---------------------------------------------------------*/
/** @defgroup HSP_HW_IF_Private_Constants HSP_HW_IF Private Constants
  * @{
  */
#define HSP_ENGINE_INSTANCE_COUNT 1U

#define GET_HAL_HSP_TRGIN_ID(trgin_id)  \
  ((trgin_id == 0U)?HAL_HSP_TRGIN_0:    \
   (trgin_id == 1U)?HAL_HSP_TRGIN_1:    \
   (trgin_id == 2U)?HAL_HSP_TRGIN_2:    \
   (trgin_id == 3U)?HAL_HSP_TRGIN_3:    \
   (trgin_id == 4U)?HAL_HSP_TRGIN_4:    \
   (trgin_id == 5U)?HAL_HSP_TRGIN_5:    \
   (trgin_id == 6U)?HAL_HSP_TRGIN_6:    \
   (trgin_id == 7U)?HAL_HSP_TRGIN_7:    \
   (trgin_id == 8U)?HAL_HSP_TRGIN_8:    \
   (trgin_id == 9U)?HAL_HSP_TRGIN_9:0xFFFFU)

#define HSP_EVENT_GET_FIRST_TRGIN_ID(evt_id)  (((evt_id) + 2U) % 5U)
#define HSP_EVENT_GET_SECOND_TRGIN_ID(evt_id)  ((HSP_EVENT_GET_FIRST_TRGIN_ID((evt_id))) + 5U)

#define HSP_EVENT_GET_FIRST_ADCIN_ID(evt_id)  ((((evt_id) - 1U) & 0x3U))
#define HSP_EVENT_GET_SECOND_ADCIN_ID(evt_id)  ((HSP_EVENT_GET_FIRST_ADCIN_ID((evt_id))) + 4U)
/**
  * @}
  */

/* Private macros ------------------------------------------------------------*/
/** @defgroup HSP_HW_IF_Private_Macros HSP_HW_IF Private Macros
  * @{
  */
#define POSITION_FIRST_ZERO(VAL) (__CLZ(__RBIT(~(VAL))))
#if defined(HAL_HSP_SMARTCLOCKING_HSPDMA)
#define HSP_HW_IF_GET_CLOCK(clock_id)                                             \
  (((clock_id) == HSP_HW_IF_SMARTCLOCKING_CTRL)?HAL_HSP_SMARTCLOCKING_CTRL:       \
   ((clock_id) == HSP_HW_IF_SMARTCLOCKING_SPE)?HAL_HSP_SMARTCLOCKING_SPE:         \
   ((clock_id) == HSP_HW_IF_SMARTCLOCKING_MMC)?HAL_HSP_SMARTCLOCKING_MMC:         \
   ((clock_id) == HSP_HW_IF_SMARTCLOCKING_HSPDMA)?HAL_HSP_SMARTCLOCKING_HSPDMA:0U)
#else /* HAL_HSP_SMARTCLOCKING_HSPDMA */
#define HSP_HW_IF_GET_CLOCK(clock_id)                                        \
  (((clock_id) == HSP_HW_IF_SMARTCLOCKING_CTRL)?HAL_HSP_SMARTCLOCKING_CTRL:  \
   ((clock_id) == HSP_HW_IF_SMARTCLOCKING_SPE)?HAL_HSP_SMARTCLOCKING_SPE:    \
   ((clock_id) == HSP_HW_IF_SMARTCLOCKING_MMC)?HAL_HSP_SMARTCLOCKING_MMC:0U)
#endif /* HAL_HSP_SMARTCLOCKING_HSPDMA */

/**
  * @brief Verify the PRC Event identifier.
  * @param  event_id  Event identifier.
  * @retval SET    event_id is valid.
  * @retval RESET  event_id is invalid.
  */
#define IS_HSP_HW_IF_PRC_EVENT_ID(event_id)  \
  (((event_id) >= HSP_HW_IF_PRC_EVENT_1) && ((event_id) <= HSP_HW_IF_PRC_EVENT_22))

#define IS_DMA_HSP_TRGO_0_TRIGGER_SOURCE(source) \
  (((source) == HAL_HPDMA1_TRIGGER_HSP1_TRGO0) || ((source) == HAL_GPDMA1_TRIGGER_HSP1_TRGO0))

#define IS_DMA_HSP_TRGO_1_TRIGGER_SOURCE(source) \
  (((source) == HAL_HPDMA1_TRIGGER_HSP1_TRGO1) || ((source) == HAL_GPDMA1_TRIGGER_HSP1_TRGO1))

#define IS_DMA_HSP_TRGO_2_TRIGGER_SOURCE(source) \
  (((source) == HAL_HPDMA1_TRIGGER_HSP1_TRGO2) || ((source) == HAL_GPDMA1_TRIGGER_HSP1_TRGO2))

#define IS_DMA_HSP_TRGO_3_TRIGGER_SOURCE(source) \
  (((source) == HAL_HPDMA1_TRIGGER_HSP1_TRGO3) || ((source) == HAL_GPDMA1_TRIGGER_HSP1_TRGO3))

/**
  * @}
  */

/* Private types -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/** @defgroup HSP_ENGINE_HW_IF_Private_Variables HSP_ENGINE_HW_IF Private Variables
  * @{
  */
hsp_hw_if_ctx_t hsp_hw_if_ctx[HSP_ENGINE_INSTANCE_COUNT];

/**
  * @}
  */

/* Private functions ---------------------------------------------------------*/
/** @defgroup HSP_ENGINE_HW_IF_Private_Functions HSP_ENGINE_HW_IF Private Functions
  * @{
  */
/* Overridden HAL Callbacks --------------------------------------------------*/
static void HSP_HW_IF_ErrorCallback(hal_hsp_handle_t *hhsp, hal_hsp_hw_error_status_t error_status,
                                    uint32_t fw_error_code, uint32_t spe_error_inf);
#if defined(USE_HSP_ENGINE_PROCLIST_NOTIFICATION_IT) && (USE_HSP_ENGINE_PROCLIST_NOTIFICATION_IT == 1U)
static void HSP_HW_IF_PROCLIST_EventsCallback(hal_hsp_handle_t *hhsp, uint32_t events_mask);
#endif /* USE_HSP_ENGINE_PROCLIST_NOTIFICATION_IT */
#if defined(USE_HSP_ENGINE_STREAM_BUFFER) && (USE_HSP_ENGINE_STREAM_BUFFER == 1U)
static void HSP_HW_IF_STREAM_BufferEmptyCallback(hal_hsp_handle_t *hhsp, uint32_t buffers_mask);
static void HSP_HW_IF_STREAM_BufferFullCallback(hal_hsp_handle_t *hhsp, uint32_t buffers_mask);
#endif /* USE_HSP_ENGINE_STREAM_BUFFER */
#if defined(USE_HSP_ENGINE_TCU_IT) && (USE_HSP_ENGINE_TCU_IT == 1U)
static void HSP_HW_IF_TCU_TaskStartedCallback(hal_hsp_handle_t *hhsp, uint32_t tcu_ids);
static void HSP_HW_IF_TCU_TaskEndedCallback(hal_hsp_handle_t *hhsp, uint32_t tcu_ids);
#endif /* USE_HSP_ENGINE_TCU_IT */

#if defined(USE_HSP_ENGINE_TIMESTAMPCAPTURE) && (USE_HSP_ENGINE_TIMESTAMPCAPTURE == 1U)
static void HSP_HW_IF_TSC_DMA_XferCpltCallback(hal_dma_handle_t *hdma);
static void HSP_HW_IF_TSC_DMA_ErrorCallback(hal_dma_handle_t *hdma);
#endif /* USE_HSP_ENGINE_TIMESTAMPCAPTURE */

static uint32_t HSP_HW_IF_Retrieve_TRGIN_HAL_Event_Source_Enum(uint32_t event_id, uint32_t trgin_id,
                                                               hal_hsp_event_source_t *enum_value);

#if defined(USE_HAL_HSP_ADCIN) && (USE_HAL_HSP_ADCIN == 1)
static uint32_t HSP_HW_IF_Retrieve_ADCIN_HAL_Event_Source_Enum(uint32_t event_id, uint32_t adcin_id,
                                                               hal_hsp_event_source_t *enum_value);
#endif /* USE_HAL_HSP_ADCIN */

#if defined(USE_HSP_ENGINE_STREAM_BUFFER) && (USE_HSP_ENGINE_STREAM_BUFFER == 1U)
static hal_hsp_stream_buffer_t HSP_HW_IF_RetrieveSTREAMBufferFromEventID(uint32_t pl_id);
#endif /* USE_HSP_ENGINE_STREAM_BUFFER */
#if defined(USE_HSP_ENGINE_TIMESTAMPCAPTURE) && (USE_HSP_ENGINE_TIMESTAMPCAPTURE == 1U)
static hsp_if_status_t HSP_HW_IF_TSC_SetTRGOConfigFromDMA(const hsp_hw_if_ctx_t *p_if_ctx);
#endif /* USE_HSP_ENGINE_TIMESTAMPCAPTURE */

/**
  * @}
  */

/* Exported functions --------------------------------------------------------*/
/** @addtogroup HSP_HW_IF_Exported_Functions
  * @{
  */
/**
  * @brief  Init the interface.
  * @param  p_if_ctx     Pointer to the interface context.
  * @param  hdriver      HSP Driver handle.
  * @param  p_user_data  Pointer to user data.
  */
void HSP_HW_IF_Init(hsp_hw_if_ctx_t *p_if_ctx, void *hdriver, void *p_user_data)
{
  hal_hsp_handle_t *hhsp;

  HSP_ASSERT_DBG_PARAM(p_if_ctx != NULL);
  HSP_ASSERT_DBG_PARAM(hdriver != NULL);

  hhsp = (hal_hsp_handle_t *)(hdriver);

  p_if_ctx->hdriver = hdriver;
  p_if_ctx->p_user_data = p_user_data;
#if defined(USE_HSP_ENGINE_ADCIN) && (USE_HSP_ENGINE_ADCIN == 1U)
  p_if_ctx->adcin_instances = 0U;
#endif /* USE_HSP_ENGINE_ADCIN */
  p_if_ctx->trgin_instances = 0U;

  (void)HAL_HSP_RegisterErrorCallback(hhsp, HSP_HW_IF_ErrorCallback);
#if defined(USE_HSP_ENGINE_PROCLIST_NOTIFICATION_IT) && (USE_HSP_ENGINE_PROCLIST_NOTIFICATION_IT == 1U)
  (void)HAL_HSP_RegisterProcessingEventCallback(hhsp, HSP_HW_IF_PROCLIST_EventsCallback);
#endif /* USE_HSP_ENGINE_PROCLIST_NOTIFICATION_IT */
#if defined(USE_HSP_ENGINE_STREAM_BUFFER) && (USE_HSP_ENGINE_STREAM_BUFFER == 1U)
  for (uint32_t i = 0U; i < 4U; i++)
  {
    p_if_ctx->a_user_stream_buffer[i].data_counter = 0U;
    p_if_ctx->a_user_stream_buffer[i].p_data = NULL;
  }

  (void)HAL_HSP_RegisterSTREAM_BufferEmptyCallback(hhsp, HSP_HW_IF_STREAM_BufferEmptyCallback);
  (void)HAL_HSP_RegisterSTREAM_BufferFullCallback(hhsp, HSP_HW_IF_STREAM_BufferFullCallback);
#endif /* USE_HSP_ENGINE_STREAM_BUFFER */

#if defined(USE_HSP_ENGINE_TCU_IT) && (USE_HSP_ENGINE_TCU_IT == 1U)
  (void)HAL_HSP_RegisterTCU_TaskStartedCallback(hhsp, HSP_HW_IF_TCU_TaskStartedCallback);
  (void)HAL_HSP_RegisterTCU_TaskEndedCallback(hhsp, HSP_HW_IF_TCU_TaskEndedCallback);
#endif /* USE_HSP_ENGINE_TCU_IT */

#if defined(USE_HSP_ENGINE_TIMESTAMPCAPTURE) && (USE_HSP_ENGINE_TIMESTAMPCAPTURE == 1U)
  p_if_ctx->p_tsc_complete_cb = NULL;
  p_if_ctx->p_tsc_error_cb = NULL;
#endif /* USE_HSP_ENGINE_TIMESTAMPCAPTURE */

  /* Link the Interface context the HAL Driver */
  HAL_HSP_SetUserData(hhsp, (void *)p_if_ctx);
}

/**
  * @brief  Deinit the interface.
  * @param  p_if_ctx  Pointer to the interface context.
  */
void HSP_HW_IF_DeInit(hsp_hw_if_ctx_t *p_if_ctx)
{
  hal_hsp_handle_t *hhsp;

  HSP_ASSERT_DBG_PARAM(p_if_ctx != NULL);

  hhsp = (hal_hsp_handle_t *)(p_if_ctx->hdriver);

  (void)HAL_HSP_RegisterErrorCallback(hhsp, HAL_HSP_ErrorCallback);
#if defined(USE_HSP_MODULES_PROCLIST) && (USE_HSP_MODULES_PROCLIST == 1U)
  (void)HAL_HSP_RegisterFWEVT_ProcessingEventCallback(hhsp, HAL_HSP_ProcessingEventCallback);
#endif /* USE_HSP_MODULES_PROCLIST */
#if defined(USE_HSP_ENGINE_STREAM_BUFFER) && (USE_HSP_ENGINE_STREAM_BUFFER == 1U)
  (void)HAL_HSP_RegisterSTREAM_BufferEmptyCallback(hhsp, HAL_HSP_STREAM_BufferEmptyCallback);
  (void)HAL_HSP_RegisterSTREAM_BufferFullCallback(hhsp, HAL_HSP_STREAM_BufferFullCallback);
#endif /* USE_HSP_ENGINE_STREAM_BUFFER */

#if defined(USE_HSP_ENGINE_TCU_IT) && (USE_HSP_ENGINE_TCU_IT == 1U)
  (void)HAL_HSP_RegisterTCU_TaskStartedCallback(hhsp, HAL_HSP_TCU_TaskStartedCallback);
  (void)HAL_HSP_RegisterTCU_TaskEndedCallback(hhsp, HAL_HSP_TCU_TaskEndedCallback);
#endif /* USE_HSP_ENGINE_TCU_IT */

#if defined(USE_HSP_ENGINE_TIMESTAMPCAPTURE) && (USE_HSP_ENGINE_TIMESTAMPCAPTURE == 1U)
  (void)HAL_HSP_RegisterTSC_TimestampReadyCallback(hhsp, HAL_HSP_TSC_TimestampReadyCallback);
#endif /* USE_HSP_ENGINE_TIMESTAMPCAPTURE */

  p_if_ctx->p_user_data = NULL;
}

/**
  * @brief  Get the Direct Command Hardware Information.
  * @param  p_if_ctx          Pointer to the interface context.
  * @param  p_dcmd_id         Pointer to the direct command ID register pointer.
  * @param  p_dcmd_data_ptr   Pointer to the direct command data register pointer.
  * @param  p_dcmd_param_data Pointer to the direct command parameter register pointer.
  */
void HSP_HW_IF_GetDCMDHWInfo(hsp_hw_if_ctx_t *p_if_ctx,
                             volatile uint32_t **p_dcmd_id, volatile uint32_t **p_dcmd_data_ptr,
                             volatile uint32_t **p_dcmd_param_data)
{
  hal_hsp_handle_t *hhsp;
  hal_hsp_hw_info_t hsp_hwinfo;

  HSP_ASSERT_DBG_PARAM(p_if_ctx != NULL);

  hhsp = (hal_hsp_handle_t *)(p_if_ctx->hdriver);

  HSP_ASSERT_DBG_PARAM(p_dcmd_id != NULL);
  HSP_ASSERT_DBG_PARAM(p_dcmd_data_ptr != NULL);
  HSP_ASSERT_DBG_PARAM(p_dcmd_param_data != NULL);

  HAL_HSP_GetHWInfo(hhsp, &hsp_hwinfo);

  *p_dcmd_id = hsp_hwinfo.p_dcmd_cmdid;
  *p_dcmd_data_ptr = hsp_hwinfo.p_dcmd_data;
  *p_dcmd_param_data = hsp_hwinfo.p_dcmd_param;
}

/**
  * @brief  Load a Firmware OpCode & data respectively in CRAM & DRAM.
  * @param  p_if_ctx   Pointer to the interface context.
  * @param  p_fw_cram  Pointer to CRAM Firmware structure
  * @param  p_fw_dram  Pointer to DRAM Firmware structure
  * @retval HSP_IF_OK     Load complete successfully
  * @retval HSP_IF_ERROR  Load failed
  */
hsp_if_status_t HSP_HW_IF_LoadFW(hsp_hw_if_ctx_t *p_if_ctx, const void *p_fw_cram, const void *p_fw_dram)
{
  hal_hsp_handle_t *hhsp;
  hsp_fw_descriptor_t *p_cram;
  hsp_fw_descriptor_t *p_dram;

  HSP_ASSERT_DBG_PARAM(p_if_ctx != NULL);
  HSP_ASSERT_DBG_PARAM(p_fw_cram != NULL);
  HSP_ASSERT_DBG_PARAM(p_fw_dram != NULL);

  hhsp = (hal_hsp_handle_t *)(p_if_ctx->hdriver);
  p_cram = (hsp_fw_descriptor_t *)p_fw_cram;
  p_dram = (hsp_fw_descriptor_t *)p_fw_dram;

  if (HAL_HSP_LoadFirmware(hhsp,
                           p_cram->p_binary, p_cram->size_byte,
                           p_dram->p_binary, p_dram->size_byte) != HAL_OK)
  {
    return HSP_IF_ERROR;
  }

  return HSP_IF_OK;
}

/**
  * @brief  Load a Plugin in CRAM.
  * @param  hdriver    HSP Driver handle.
  * @param  p_bin      Pointer to the Plugin binary.
  * @param  size_byte  Size in byte of Plugin binary.
  * @retval HSP_IF_OK     Load complete successfully
  * @retval HSP_IF_ERROR  Load failed
  */
hsp_if_status_t HSP_HW_IF_LoadPlugin(void *hdriver, const uint8_t *p_bin, uint32_t size_byte)
{
  HSP_ASSERT_DBG_PARAM(hdriver != NULL);
  HSP_ASSERT_DBG_PARAM(p_bin != NULL);

  if (HAL_HSP_LoadPlugin((hal_hsp_handle_t *)(hdriver), p_bin, size_byte) != HAL_OK)
  {
    return HSP_IF_ERROR;
  }

  return HSP_IF_OK;
}

/**
  * @brief  Boot the HSP.
  * @param  p_if_ctx          Pointer to the interface context.
  * @param  enableCycleCount  Enable cycle count on HSP side
  * @retval HSP_IF_OK     Boot complete successfully
  * @retval HSP_IF_ERROR  Boot failed
  */
hsp_if_status_t HSP_HW_IF_Boot(hsp_hw_if_ctx_t *p_if_ctx, uint32_t enableCycleCount)
{
  uint32_t boot_error_code;
  hal_hsp_handle_t *hhsp;
  hal_hsp_boot_config_t boot_cfg;

  HSP_ASSERT_DBG_PARAM(p_if_ctx != NULL);

  hhsp = (hal_hsp_handle_t *)(p_if_ctx->hdriver);
  boot_cfg.boot_cmd_id = HSP_CMD_FW_START;
  boot_cfg.boot_success_code = HSP_BSTAT_BOOTOK;
  if (enableCycleCount)
  {
    boot_cfg.perf_monitor_state = HAL_HSP_PERF_MONITOR_ENABLE;
  }
  else
  {
    boot_cfg.perf_monitor_state = HAL_HSP_PERF_MONITOR_DISABLE;
  }

  if ((HAL_HSP_Boot(hhsp, &boot_cfg, &boot_error_code) != HAL_OK)
      || (boot_error_code != HSP_BSTAT_BOOTOK))
  {
    return HSP_IF_ERROR;
  }

#if 0
  hal_hsp_fw_version_t rom_version;
  if (HAL_HSP_GetCROMVersion(&(h_hw_hsp_if[hsp_id].hhsp), &rom_version) != HAL_OK)
  {
    return HSP_IF_ERROR;
  }

  if (rom_version.major != HSP_FW_DEF_ROM_VERSION_MAJOR)
  {
    return HSP_IF_ERROR;
  }

  if (rom_version.minor != HSP_FW_DEF_ROM_VERSION_MINOR)
  {
    return HSP_IF_ERROR;
  }

  hal_hsp_fw_version_t ram_version;
  if (HAL_HSP_GetCRAMVersion(&(h_hw_hsp_if[hsp_id].hhsp), &ram_version) != HAL_OK)
  {
    return HSP_IF_ERROR;
  }

  if (ram_version.major != HSP_FW_DEF_RAM_VERSION_MAJOR)
  {
    return HSP_IF_ERROR;
  }

  if (ram_version.minor != HSP_FW_DEF_RAM_VERSION_MINOR)
  {
    return HSP_IF_ERROR;
  }
#endif /* if 0 */
  return HSP_IF_OK;
}

/* API to communicate with the HSP -------------------------------------------*/
/**
  * @brief Send a command with MsgBox Interface.
  * @param  hdriver     HSP Driver handle.
  * @param  command_id  Command ID.
  * @retval HSP_IF_OK     Action complete successfully
  * @retval HSP_IF_ERROR  Action failed
  */
hsp_if_status_t HSP_HW_IF_SendCommand(void *hdriver, uint32_t command_id)
{
  hal_hsp_handle_t *hhsp;
  uint32_t tickstart;
  uint32_t spe_answer;

  HSP_ASSERT_DBG_PARAM(hdriver != NULL);

  hhsp = (hal_hsp_handle_t *)(hdriver);

  if (HAL_HSP_MSGBOX_SendMessage(hhsp, command_id) != HAL_OK)
  {
    return HSP_IF_ERROR;
  }

  /* Wait the answer of SPE */
  tickstart = HAL_GetTick();

  while (HAL_HSP_MSGBOX_IsMessageAvailable(hhsp) == HAL_HSP_MSGBOX_SEMAPHORE_NO_MSG)
  {
    /* Check for the Timeout */
    if ((HAL_GetTick() - tickstart) > HSP_TIMEOUT_MS)
    {
      return HSP_IF_ERROR;
    }
  }

  /* Read the SPE answer via HSP_H2CMSGDR register (HSP to CPU message data register). */
  spe_answer = HAL_HSP_MSGBOX_GetMessage(hhsp);

  /* Indicate to the HSP that the message is read */
  /* When CPU writes the bit H2CSEM to 1, it clears it to 0 ! */
  HAL_HSP_MSGBOX_AckSemaphore(hhsp);

  /* Check the HSP status */
  if (spe_answer != 0U)
  {
    return HSP_IF_ERROR;
  }

  return HSP_IF_OK;
}

/**
  * @brief  Write a parameter data for a Direct Command or a MsgBox.
  * @param  hdriver   HSP Driver handle.
  * @param  param_id  Parameter ID.
  * @param  value     Value to set.
  */
void HSP_HW_IF_WriteParameter(void *hdriver, uint32_t param_id, uint32_t value)
{
  HSP_ASSERT_DBG_PARAM(hdriver != NULL);

  hal_hsp_handle_t *hhsp = (hal_hsp_handle_t *)(hdriver);

  (void) HAL_HSP_WriteParameter(hhsp, (hal_hsp_param_t)param_id, value);
}

/**
  * @brief Read the parameter data of a Direct Command or a MsgBox.
  * @param  p_if_ctx  Pointer to the interface context.
  * @param  param_id  Parameter ID.
  * @return Value of parameter.
  */
uint32_t HSP_HW_IF_ReadParameter(const hsp_hw_if_ctx_t *p_if_ctx, uint32_t param_id)
{
  hal_hsp_handle_t *hhsp;

  HSP_ASSERT_DBG_PARAM(p_if_ctx != NULL);

  hhsp = (hal_hsp_handle_t *)(p_if_ctx->hdriver);

  return HAL_HSP_ReadParameter(hhsp, (hal_hsp_param_t)param_id);
}

/**
  * @brief Clear the Firmware Error Code.
  * @param  hdriver   HSP Driver handle.
  * @return  Firmware Error Code.
  */
uint32_t HSP_HW_IF_ClearFWERR(void *hdriver)
{
  uint32_t tickstart;

  HSP_ASSERT_DBG_PARAM(hdriver != NULL);

  hal_hsp_handle_t *hhsp = (hal_hsp_handle_t *)(hdriver);

  HAL_HSP_DCMD_WriteCommand(hhsp, HSP_DIRECT_CMD_CLR_FWERR);

  /* Wait until the command is done */
  tickstart = HAL_GetTick();
  while (HAL_HSP_DCMD_GetStatus(hhsp) != HAL_HSP_DCMD_READY)
  {
    /* Check for the Timeout */
    if ((HAL_GetTick() - tickstart) > HSP_TIMEOUT_MS)
    {
      return 0U;
    }
  }

  return HAL_HSP_ReadParameter(hhsp, HAL_HSP_PARAM_0);
}

/* API to manage the SmartClocking -------------------------------------------*/
/**
  * @brief Enable SmartClocking capabilities of HSP blocks.
  * @param  hdriver   HSP Driver handle.
  * @param  clock_id  Clock ID
  * @retval HSP_IF_OK     Action complete successfully
  * @retval HSP_IF_ERROR  Action failed
  */
hsp_if_status_t HSP_HW_IF_EnableSmartClocking(void *hdriver, uint32_t clock_id)
{
  HSP_ASSERT_DBG_PARAM(hdriver != NULL);

  hal_hsp_handle_t *hhsp = (hal_hsp_handle_t *)(hdriver);

  if (HAL_HSP_SMARTCLOCKING_Enable(hhsp, clock_id) != HAL_OK)
  {
    return HSP_IF_ERROR;
  }
  return HSP_IF_OK;
}

/**
  * @brief Disable SmartClocking capabilities of HSP blocks.
  * @param  hdriver   HSP Driver handle.
  * @param  clock_id  Clock ID
  * @retval HSP_IF_OK     Action complete successfully
  * @retval HSP_IF_ERROR  Action failed
  */
hsp_if_status_t HSP_HW_IF_DisableSmartClocking(void *hdriver, uint32_t clock_id)
{
  HSP_ASSERT_DBG_PARAM(hdriver != NULL);

  hal_hsp_handle_t *hhsp = (hal_hsp_handle_t *)(hdriver);

  if (HAL_HSP_SMARTCLOCKING_Disable(hhsp, clock_id) != HAL_OK)
  {
    return HSP_IF_ERROR;
  }
  return HSP_IF_OK;
}

/**
  * @brief Return the SmartClocking status of a HSP block.
  * @param  p_if_ctx  Pointer to the interface context.
  * @param  clock_id  Clock ID
  * @retval 0U  SmartClocking disabled
  * @retval 1U  SmartClocking enabled
  */
uint32_t HSP_HW_IF_IsEnabledSmartClocking(const hsp_hw_if_ctx_t *p_if_ctx, uint32_t clock_id)
{
  const hal_hsp_handle_t *hhsp;

  HSP_ASSERT_DBG_PARAM(p_if_ctx != NULL);

  hhsp = (const hal_hsp_handle_t *)(p_if_ctx->hdriver);

  return (uint32_t)HAL_HSP_SMARTCLOCKING_IsEnabled(hhsp, clock_id);
}

/* API to manage OUTPUT ------------------------------------------------------*/
/**
  * @brief Configure the source of a TRGO output.
  * @param  p_if_ctx  Pointer to the interface context.
  * @param  trgo_id   TRGO output ID.
  * @param  source    Source value.
  * @retval HSP_IF_OK     Action complete successfully
  * @retval HSP_IF_ERROR  Action failed
  */
hsp_if_status_t HSP_HW_IF_OUTPUT_SetConfig(hsp_hw_if_ctx_t *p_if_ctx, uint32_t trgo_id, uint32_t source)
{
  hal_hsp_handle_t *hhsp;
  hal_hsp_trgo_config_t trgo_cfg;

  HSP_ASSERT_DBG_PARAM(p_if_ctx != NULL);

  hhsp = (hal_hsp_handle_t *)(p_if_ctx->hdriver);

  trgo_cfg.trigger_id = (hal_hsp_trgo_trigger_t)trgo_id;
  trgo_cfg.source = (hal_hsp_trgo_source_t)source;
  if (HAL_HSP_TRGO_SetMultiConfig(hhsp, &trgo_cfg, 1U) != HAL_OK)
  {
    return HSP_IF_ERROR;
  }
  return HSP_IF_OK;
}

/**
  * @brief Enable GPO & TRGO outputs.
  * @param  p_if_ctx  Pointer to the interface context.
  * @retval HSP_IF_OK     Action complete successfully
  * @retval HSP_IF_ERROR  Action failed
  */
hsp_if_status_t HSP_HW_IF_OUTPUT_Enable(hsp_hw_if_ctx_t *p_if_ctx)
{
  hal_hsp_handle_t *hhsp;

  HSP_ASSERT_DBG_PARAM(p_if_ctx != NULL);

  hhsp = (hal_hsp_handle_t *)(p_if_ctx->hdriver);

  if (HAL_HSP_TRGO_Enable(hhsp) != HAL_OK)
  {
    return HSP_IF_ERROR;
  }

  return HSP_IF_OK;
}

/**
  * @brief Disable GPO & TRGO outputs.
  * @param  p_if_ctx  Pointer to the interface context.
  * @retval HSP_IF_OK     Action complete successfully
  * @retval HSP_IF_ERROR  Action failed
  */
hsp_if_status_t HSP_HW_IF_OUTPUT_Disable(hsp_hw_if_ctx_t *p_if_ctx)
{
  hal_hsp_handle_t *hhsp;

  HSP_ASSERT_DBG_PARAM(p_if_ctx != NULL);

  hhsp = (hal_hsp_handle_t *)(p_if_ctx->hdriver);

  if (HAL_HSP_TRGO_Disable(hhsp) != HAL_OK)
  {
    return HSP_IF_ERROR;
  }

  return HSP_IF_OK;
}

/**
  * @brief Return the enabling status of HSP Outputs.
  * @param  p_if_ctx  Pointer to the interface context.
  * @retval HSP_IF_ACTIVATION_DISABLED  HSP Outputs are disabled
  * @retval HSP_IF_ACTIVATION_ENABLED   HSP Outputs are enabled
  */
hsp_if_activation_status_t  HSP_HW_IF_OUTPUT_IsEnabled(const hsp_hw_if_ctx_t *p_if_ctx)
{
  const hal_hsp_handle_t *hhsp;

  HSP_ASSERT_DBG_PARAM(p_if_ctx != NULL);

  hhsp = (hal_hsp_handle_t *)(p_if_ctx->hdriver);

  if (HAL_HSP_TRGO_IsEnabled(hhsp) == HAL_HSP_TRGO_DISABLED)
  {
    return HSP_IF_ACTIVATION_DISABLED;
  }
  return HSP_IF_ACTIVATION_ENABLED;
}

/* API to manage Processing List ---------------------------------------------*/
/**
  * @brief  Start the record of a Processing List.
  * @param  p_if_ctx  Pointer to the interface context.
  * @param  pl_id     Processing List ID
  * @retval HSP_IF_OK     Action complete successfully
  * @retval HSP_IF_ERROR  Action failed
  */
hsp_if_status_t HSP_HW_IF_SEQ_StartRecord(hsp_hw_if_ctx_t *p_if_ctx, uint32_t pl_id)
{
  hal_hsp_handle_t *hhsp;

  HSP_ASSERT_DBG_PARAM(p_if_ctx != NULL);

  hhsp = (hal_hsp_handle_t *)(p_if_ctx->hdriver);

  if (HAL_HSP_PRC_SWRequestLowestPriorityTask(hhsp, HAL_HSP_TASK_SUPERVISOR, HAL_HSP_PRC_TASK_SYNC_NONE,
                                              HAL_HSP_IT_NONE) != HAL_OK)
  {
    return HSP_IF_ERROR;
  }

  HAL_HSP_WriteParameter(hhsp, HAL_HSP_PARAM_0, pl_id);

  if (HSP_HW_IF_SendCommand(hhsp, HSP_CMD_PRO_CFG_START) != HSP_IF_OK)
  {
    return HSP_IF_ERROR;
  }
  return HSP_IF_OK;
}

/**
  * @brief  Stop the record of the Processing List.
  * @param  p_if_ctx  Pointer to the interface context.
  * @retval HSP_IF_OK     Action complete successfully
  * @retval HSP_IF_ERROR  Action failed
  */
hsp_if_status_t HSP_HW_IF_SEQ_StopRecord(hsp_hw_if_ctx_t *p_if_ctx)
{
  hal_hsp_handle_t *hhsp;

  HSP_ASSERT_DBG_PARAM(p_if_ctx != NULL);

  hhsp = (hal_hsp_handle_t *)(p_if_ctx->hdriver);

  if (HSP_HW_IF_SendCommand(hhsp, HSP_CMD_PRO_CFG_END) != HSP_IF_OK)
  {
    return HSP_IF_ERROR;
  }

  return HSP_IF_OK;
}

/**
  * @brief  Reset all Processing List.
  * @param  p_if_ctx  Pointer to the interface context.
  * @retval HSP_IF_OK success
  *         HSP_IF_ERROR failure
  */
hsp_if_status_t HSP_HW_IF_SEQ_ResetPL(const hsp_hw_if_ctx_t *p_if_ctx)
{
  hal_hsp_handle_t *hhsp;
  uint32_t tickstart;

  HSP_ASSERT_DBG_PARAM(p_if_ctx != NULL);

  hhsp = (hal_hsp_handle_t *)(p_if_ctx->hdriver);

  if (HAL_HSP_PRC_SWRequestLowestPriorityTask(hhsp, HAL_HSP_TASK_SUPERVISOR, HAL_HSP_PRC_TASK_SYNC_NONE,
                                              HAL_HSP_IT_NONE) != HAL_OK)
  {
    return HSP_IF_ERROR;
  }

  /* Wait until the request is done */
  tickstart = HAL_GetTick();
  while (HAL_HSP_PRC_GetSWRequestLowestPriorityStatusAndClearFlag(hhsp) == HAL_HSP_PRC_LOWEST_PRIO_TASK_ONGOING)
  {
    /* Check for the Timeout */
    if ((HAL_GetTick() - tickstart) > HSP_TIMEOUT_MS)
    {
      return HSP_IF_ERROR;
    }
  }

  HAL_HSP_WriteParameter(hhsp, HAL_HSP_PARAM_1, ENABLE_HSP_PERFORMANCE_MONITOR);

  if (HSP_HW_IF_SendCommand(hhsp, HSP_CMD_PL_RESET) != HSP_IF_OK)
  {
    return HSP_IF_ERROR;
  }

  return HSP_IF_OK;
}

/**
  * @brief  Execute a Task/Processing list with the lowest priority.
  * @param  p_if_ctx  Pointer to the interface context.
  * @param  task_id   Task Identifier
  * @param  timeout_ms  Timeout in millisecond
  * @retval HSP_IF_OK success
  *         HSP_IF_ERROR failure
  */
hsp_if_status_t HSP_HW_IF_SEQ_RunTask(void *hdriver, uint32_t task_id, uint32_t timeout_ms)
{
  hal_hsp_handle_t *hhsp;
  uint32_t tickstart;

  HSP_ASSERT_DBG_PARAM(hdriver != NULL);

  hhsp = (hal_hsp_handle_t *)(hdriver);

  if (HAL_HSP_PRC_SWRequestLowestPriorityTask(hhsp, (hal_hsp_task_t)task_id, HAL_HSP_PRC_TASK_SYNC_NONE,
                                              HAL_HSP_IT_NONE) != HAL_OK)
  {
    return HSP_IF_ERROR;
  }

  /* Wait until the request is done */
  tickstart = HAL_GetTick();
  while (HAL_HSP_PRC_GetSWRequestLowestPriorityStatusAndClearFlag(hhsp) == HAL_HSP_PRC_LOWEST_PRIO_TASK_ONGOING)
  {
    /* Check for the Timeout */
    if ((HAL_GetTick() - tickstart) > timeout_ms)
    {
      return HSP_IF_ERROR;
    }
  }

  return HSP_IF_OK;
}

#if defined(USE_HSP_ENGINE_PROCLIST_NOTIFICATION_IT) && (USE_HSP_ENGINE_PROCLIST_NOTIFICATION_IT == 1)
/**
  * @brief  Enable all Processing List ITs.
  * @param  p_if_ctx  Pointer to the interface context.
  * @retval HSP_IF_OK success
  *         HSP_IF_ERROR failure
  */
hsp_if_status_t HSP_HW_IF_SEQ_EnableProclistNotificationIT(const hsp_hw_if_ctx_t *p_if_ctx, uint32_t interrupts)
{
  hal_hsp_handle_t *hhsp;

  HSP_ASSERT_DBG_PARAM(p_if_ctx != NULL);

  hhsp = (hal_hsp_handle_t *)(p_if_ctx->hdriver);

  if (HAL_HSP_PROCLIST_EnableIT(hhsp, interrupts) != HAL_OK)
  {
    return HSP_IF_ERROR;
  }

  return HSP_IF_OK;
}

/**
  * @brief  Disable all Processing List ITs.
  * @param  p_if_ctx  Pointer to the interface context.
  * @retval HSP_IF_OK success
  *         HSP_IF_ERROR failure
  */
hsp_if_status_t HSP_HW_IF_SEQ_DisableProclistNotificationIT(const hsp_hw_if_ctx_t *p_if_ctx, uint32_t interrupts)
{
  hal_hsp_handle_t *hhsp;

  HSP_ASSERT_DBG_PARAM(p_if_ctx != NULL);

  hhsp = (hal_hsp_handle_t *)(p_if_ctx->hdriver);

  if (HAL_HSP_PROCLIST_DisableIT(hhsp, interrupts) != HAL_OK)
  {
    return HSP_IF_ERROR;
  }

  return HSP_IF_OK;
}
#endif /* USE_HSP_ENGINE_PROCLIST_NOTIFICATION_IT */

/**
  * @brief  Poll for Processing List notifications.
  * @param  p_if_ctx  Pointer to the interface context.
  * @retval HSP_IF_OK success
  * @retval HSP_IF_ERROR failure
  */
hsp_if_status_t HSP_HW_IF_SEQ_PollForProclistNotification(const hsp_hw_if_ctx_t *p_if_ctx, uint32_t pfct_events,
                                                          uint32_t timeout_ms)
{
  hal_hsp_handle_t *hhsp;
  uint32_t pfct_events_status;

  HSP_ASSERT_DBG_PARAM(p_if_ctx != NULL);

  hhsp = (hal_hsp_handle_t *)(p_if_ctx->hdriver);

  pfct_events_status = 0U;
  if (HAL_HSP_PROCLIST_PollForNotification(hhsp, HAL_HSP_POLLING_FOR_ALL_EVENT, pfct_events, timeout_ms,
                                           &pfct_events_status) != HAL_OK)
  {
    return HSP_IF_ERROR;
  }

  return HSP_IF_OK;
}

/* API to manage Trigger & Event configuration -------------------------------*/
#if defined(USE_HSP_ENGINE_STREAM_BUFFER) && (USE_HSP_ENGINE_STREAM_BUFFER == 1U)
/**
  * @brief Configure an event with a STREAM Buffer as source.
  * @param  hdriver           HSP Driver handle.
  * @param  event_id          Event identifier in range [1..22].
  * @param  stream_buffer_id  STREAM Buffer Identifier.
  * @param  direction         STREAM Buffer Direction (0:RX, 1:TX)
  * @param  buffer_sync       Synchronization with the adjacent STREAM Buffer
  * @param  tcu_sync          Task Comparator Synchronization
  * @note  The enable of STREAM is not perform at the end of the configuration otherwise it will be impossible
  *        to configure the next Stream Buffer.
  *        The application must do it after all STREAM Buffer configurations.
  * @retval HSP_IF_OK     Action complete successfully
  * @retval HSP_IF_ERROR  Action failed
  */
hsp_if_status_t HSP_HW_IF_SEQ_EVENT_SetConfig_StreamBuffer(void *hdriver, uint32_t event_id,
                                                           uint32_t stream_buffer_id,
                                                           uint32_t direction, uint32_t buffer_sync,
                                                           uint32_t tcu_sync)
{
  hal_hsp_handle_t *hhsp;
  hal_hsp_stream_buffer_config_t stream_cfg;
  hal_hsp_prc_task_config_t evt_cfg;

  HSP_ASSERT_DBG_PARAM(hdriver != NULL);
  HSP_ASSERT_DBG_PARAM(IS_HSP_HW_IF_PRC_EVENT_ID(event_id));

  hhsp = (hal_hsp_handle_t *)(hdriver);

  /* Config the stream */
  /* to validate: stream_cfg.buffer_id = HSP_HW_IF_RetrieveSTREAMBufferFromEventID(event_id);*/
  stream_cfg.buffer_id = (hal_hsp_stream_buffer_t)(stream_buffer_id);
  stream_cfg.direction = (hal_hsp_stream_buffer_direction_t)direction;

  if (buffer_sync == 0U)
  {
    stream_cfg.sync_state = HAL_HSP_STREAM_BUFFER_SYNC_DISABLE;
  }
  else
  {
    stream_cfg.sync_state = HAL_HSP_STREAM_BUFFER_SYNC_ENABLE;
  }

  if (HAL_HSP_STREAM_SetMultiConfig(hhsp, &stream_cfg, 1U) != HAL_OK)
  {
    return HSP_IF_ERROR;
  }

  /* Configure the Event */
  evt_cfg.source = HAL_HSP_EVENT_SOURCE_GET_ENUM_FOR_STREAM(event_id);
  if (evt_cfg.source == HAL_HSP_EVENT_RESERVED)
  {
    return HSP_IF_ERROR;
  }

  if (tcu_sync == HSP_HW_IF_SEQ_EVENT_SYNC_DISABLED)
  {
    evt_cfg.sync = HAL_HSP_PRC_TASK_SYNC_NONE;
  }
  else
  {
    evt_cfg.sync = (hal_hsp_prc_task_sync_source_t)tcu_sync;
  }

  if (HAL_HSP_PRC_SetMultiTaskConfig(hhsp, &evt_cfg, 1U) != HAL_OK)
  {
    return HSP_IF_ERROR;
  }

  return HSP_IF_OK;
}

/**
  * @brief Enable the Integer To Float conversion for all STREAM Buffers.
  * @param  hdriver   HSP Driver handle.
  * @retval HSP_IF_OK     Action complete successfully
  * @retval HSP_IF_ERROR  Action failed
  */
hsp_if_status_t HSP_HW_IF_SEQ_STREAM_EnableIntToFloat(void *hdriver)
{
  HSP_ASSERT_DBG_PARAM(hdriver != NULL);

  hal_hsp_handle_t *hhsp = (hal_hsp_handle_t *)(hdriver);

  if (HAL_HSP_STREAM_EnableIntToFloat(hhsp) != HAL_OK)
  {
    return HSP_IF_ERROR;
  }

  return HSP_IF_OK;
}

/**
  * @brief Disable the Integer To Float conversion for all STREAM Buffers.
  * @param  hdriver   HSP Driver handle.
  * @retval HSP_IF_OK     Action complete successfully
  * @retval HSP_IF_ERROR  Action failed
  */
hsp_if_status_t HSP_HW_IF_SEQ_STREAM_DisableIntToFloat(void *hdriver)
{
  HSP_ASSERT_DBG_PARAM(hdriver != NULL);

  hal_hsp_handle_t *hhsp = (hal_hsp_handle_t *)(hdriver);

  if (HAL_HSP_STREAM_DisableIntToFloat(hhsp) != HAL_OK)
  {
    return HSP_IF_ERROR;
  }

  return HSP_IF_OK;
}

/**
  * @brief Enable all STREAM Buffers.
  * @param  p_if_ctx  Pointer to the interface context.
  * @retval HSP_IF_OK     Action complete successfully
  * @retval HSP_IF_ERROR  Action failed
  */
hsp_if_status_t HSP_HW_IF_SEQ_STREAM_Enable(hsp_hw_if_ctx_t *p_if_ctx)
{
  hal_hsp_handle_t *hhsp;

  HSP_ASSERT_DBG_PARAM(p_if_ctx != NULL);

  hhsp = (hal_hsp_handle_t *)(p_if_ctx->hdriver);

  /* Build STREAM Buffer IT to enable */
  uint32_t evt_its = 0U;
  uint32_t err_its = 0U;
  for (uint32_t i = 0U; i < 4U; i++)
  {
    hsp_hw_if_buffer_t *p_buffer = &(p_if_ctx->a_user_stream_buffer[i]);
    if (p_buffer->data_counter > 0U)
    {
      evt_its |= (HAL_HSP_STREAM_IT_BUFFER_0_READY << i);
      err_its |= (HAL_HSP_STREAM_ERR_IT_BUFFER_0_OVR << i);
    }
  }

  if (HAL_HSP_STREAM_Start(hhsp, evt_its, err_its) != HAL_OK)
  {
    return HSP_IF_ERROR;
  }

  return HSP_IF_OK;
}

/**
  * @brief Disable all STREAM Buffers.
  * @param  p_if_ctx  Pointer to the interface context.
  * @retval HSP_IF_OK     Action complete successfully
  * @retval HSP_IF_ERROR  Action failed
  */
hsp_if_status_t HSP_HW_IF_SEQ_STREAM_Disable(hsp_hw_if_ctx_t *p_if_ctx)
{
  hal_hsp_handle_t *hhsp;

  HSP_ASSERT_DBG_PARAM(p_if_ctx != NULL);

  hhsp = (hal_hsp_handle_t *)(p_if_ctx->hdriver);

  if (HAL_HSP_STREAM_Stop(hhsp) != HAL_OK)
  {
    return HSP_IF_ERROR;
  }

  return HSP_IF_OK;
}

/**
  * @brief  Get a STREAM Buffer address.
  * @param  hdriver  Pointer to a driver.
  * @param  stream_buffer_id  Stream buffer id.
  * @return Buffer address.
  */
volatile uint32_t *HSP_HW_IF_SEQ_STREAM_GetBufferAddress(void *hdriver, uint32_t stream_buffer_id)
{
  HSP_ASSERT_DBG_PARAM(hdriver != NULL);

  hal_hsp_handle_t *hhsp = (hal_hsp_handle_t *)(hdriver);

  return HAL_HSP_STREAM_GetDataRegAddress(hhsp, (hal_hsp_stream_buffer_t)stream_buffer_id);
}

/**
  * @brief  Retrieve the STREAM Buffer address from Processing List identifier.
  * @param  hdriver  Pointer to a driver.
  * @param  pl_id  Processing List identifier.
  * @return Buffer address.
  */
volatile uint32_t *HSP_HW_IF_SEQ_STREAM_GetBufferAddressFromPLID(void *hdriver, uint32_t pl_id)
{
  hal_hsp_stream_buffer_t stream_buffer_id;

  HSP_ASSERT_DBG_PARAM(hdriver != NULL);
  HSP_ASSERT_DBG_PARAM(IS_HSP_HW_IF_PRC_EVENT_ID(pl_id));

  hal_hsp_handle_t *hhsp = (hal_hsp_handle_t *)(hdriver);

  if (!IS_HSP_HW_IF_PRC_EVENT_ID(pl_id))
  {
    return NULL;
  }

  /* The processing list identifier must has the same value of PRC Event identifier attached to the STREAM Buffer */
  stream_buffer_id = HSP_HW_IF_RetrieveSTREAMBufferFromEventID(pl_id);

  return HAL_HSP_STREAM_GetDataRegAddress(hhsp, stream_buffer_id);
}

/**
  * @brief  Start the write/read of data to/from a STREAM Buffer in IT mode.
  *         The Write or Read is depend of the Stream Buffer Direction.
  * @param  p_if_ctx           Pointer to the interface context.
  * @param  stream_buffer_id  Stream buffer id.
  * @param  p_buffer          Data buffer.
  * @param  buffer_size       Number of data.
  */
hsp_if_status_t HSP_HW_IF_SEQ_STREAM_Buffer_Start(hsp_hw_if_ctx_t *p_if_ctx, uint32_t stream_buffer_id,
                                                  const int32_t *p_buffer,
                                                  uint32_t buffer_size)
{
  HSP_ASSERT_DBG_PARAM(p_if_ctx != NULL);
  HSP_ASSERT_DBG_PARAM(p_buffer != NULL);

  /* Store the data buffer in the Interface Context */
  hsp_hw_if_buffer_t *p_if_buffer = &(p_if_ctx->a_user_stream_buffer[stream_buffer_id]);
  p_if_buffer->p_data = (uint32_t *)p_buffer;
  p_if_buffer->data_counter = buffer_size;

  return HSP_IF_OK;
}

#endif /* USE_HSP_ENGINE_STREAM_BUFFER */
#if defined(USE_HSP_ENGINE_ADCIN) && (USE_HSP_ENGINE_ADCIN == 1U)
/**
  * @brief  Configure an event with a ADCIN trigger as source.
  * @param  p_if_ctx        Pointer to the interface context.
  * @param  event_id        Event ID.
  * @param  event_sync      Enable Synchronisation with End Of Task.
  * @param  p_config_array  Pointer to ADCIN configuration array.
  * @param  array_size      Number of elements in the configuration array.
  * @param  p_reg_address_array  Pointer to ADCIN register address array.
  * @note For multiple ADCIN configurations, the "array_size - 1" first element are automatiicaly combined
  *  and the event is attached to the ADCIN interface selected for the first ADCIN configuration.
  *  The pointer to the Register Address array will contains the ADCIN register address of the ADCIN interface
  *  selected for each configuration. This allows the application to use theses addresses as input of processing
  *  functions recorded in processing list.
  * @retval HSP_IF_OK     Action complete successfully
  * @retval HSP_IF_ERROR  Action failed
  */
hsp_if_status_t HSP_HW_IF_SEQ_EVENT_SetConfig_ADCIN(hsp_hw_if_ctx_t *p_if_ctx,
                                                    uint32_t event_id, uint32_t evt_sync,
                                                    const hsp_hw_if_adcin_config_t *p_config_array, uint32_t array_size,
                                                    uint32_t *p_reg_address_array)
{
#if defined(USE_HAL_HSP_ADCIN) && (USE_HAL_HSP_ADCIN == 1)
  hal_hsp_handle_t *hhsp;
  uint32_t adcin_instances;
  uint32_t first_adcin_id;
  uint32_t second_adcin_id;
  uint32_t selected_adcin_id;
  uint32_t reserved_mask = 0U;
  hal_hsp_prc_task_config_t evt_cfg;

  HSP_ASSERT_DBG_PARAM(p_if_ctx != NULL);
  HSP_ASSERT_DBG_PARAM(p_config_array != NULL);
  HSP_ASSERT_DBG_PARAM(array_size > 0U);
  HSP_ASSERT_DBG_PARAM((event_id >= 1U) && (event_id <= 22U));
  HSP_ASSERT_DBG_PARAM(p_reg_address_array != NULL);

  hhsp = (hal_hsp_handle_t *)(p_if_ctx->hdriver);

  /* Get the ADCIN used status */
  adcin_instances = p_if_ctx->adcin_instances;
  first_adcin_id = HSP_EVENT_GET_FIRST_ADCIN_ID(event_id);
  second_adcin_id = HSP_EVENT_GET_SECOND_ADCIN_ID(event_id);

  if ((adcin_instances & (1UL << first_adcin_id)) == 0U)
  {
    selected_adcin_id = first_adcin_id;
  }
  else if ((adcin_instances & (1UL << second_adcin_id)) == 0U)
  {
    selected_adcin_id = second_adcin_id;
  }
  else
  {
    /* No ADCIN available */
    return HSP_IF_ERROR;
  }

  if ((selected_adcin_id + array_size) > 8U)
  {
    /* No Enough ADCIN available */
    return HSP_IF_ERROR;
  }

  /* Check that all required ADCIN interface are available for the configuration */
  uint32_t *p_reg_address_selector = p_reg_address_array;
  for (uint32_t i = 0U; i < array_size; i++)
  {
    uint32_t adcin_id = selected_adcin_id + i;

    if ((adcin_instances & (1UL << adcin_id)) != 0U)
    {
      return HSP_IF_ERROR;
    }

    reserved_mask |= (1UL << adcin_id);
    *p_reg_address_selector = (uint32_t)HAL_HSP_ADCIN_GetBufferAddress(hhsp, (hal_hsp_adcin_t)adcin_id);
    p_reg_address_selector++;
  }

  /* Configure all the required ADCIN interfaces */
  for (uint32_t i = 0U; i < array_size; i++)
  {
    hal_hsp_adcin_config_t adcin_cfg;

    adcin_cfg.adcin_id = (hal_hsp_adcin_t)(selected_adcin_id + i);
    if (i == (array_size - 1U))
    {
      adcin_cfg.sync_state = HAL_HSP_ADCIN_SYNC_DISABLE;
    }
    else
    {
      adcin_cfg.sync_state = HAL_HSP_ADCIN_SYNC_ENABLE;
    }

    adcin_cfg.source = (hal_hsp_adcin_source_t)p_config_array[i].adc_source;
    adcin_cfg.channel_flt = (hal_hsp_adcin_filter_channel_t)p_config_array[i].adc_channel_filter;

    if (HAL_HSP_ADCIN_SetMultiConfig(hhsp, &adcin_cfg, 1U) != HAL_OK)
    {
      return HSP_IF_ERROR;
    }
  }

  if (HSP_HW_IF_Retrieve_ADCIN_HAL_Event_Source_Enum(event_id, selected_adcin_id, &evt_cfg.source) != 0U)
  {
    return HSP_IF_ERROR;
  }

  if (evt_sync == HSP_HW_IF_SEQ_EVENT_SYNC_DISABLED)
  {
    evt_cfg.sync = HAL_HSP_PRC_TASK_SYNC_NONE;
  }
  else
  {
    evt_cfg.sync = (hal_hsp_prc_task_sync_source_t)evt_sync;
  }

  if (HAL_HSP_PRC_SetMultiTaskConfig(hhsp, &evt_cfg, 1U) != HAL_OK)
  {
    return HSP_IF_ERROR;
  }

  /* Update the mask of ADCIN instances used */
  p_if_ctx->adcin_instances = adcin_instances | reserved_mask;

  return HSP_IF_OK;
#else
  UNUSED(p_if_ctx);
  UNUSED(event_id);
  UNUSED(evt_sync);
  UNUSED(p_config_array);
  UNUSED(array_size);
  UNUSED(p_reg_address_array);

  return HSP_IF_ERROR;
#endif /* USE_HAL_HSP_ADCIN */
}

/**
  * @brief Enable the ADCIN interface.
  * @param  p_if_ctx  Pointer to the interface context.
  * @retval HSP_IF_OK     Action complete successfully
  * @retval HSP_IF_ERROR  Action failed
  */
hsp_if_status_t HSP_HW_IF_SEQ_ADCIN_Enable(hsp_hw_if_ctx_t *p_if_ctx)
{
#if defined(USE_HAL_HSP_ADCIN) && (USE_HAL_HSP_ADCIN == 1)
  hal_hsp_handle_t *hhsp;

  HSP_ASSERT_DBG_PARAM(p_if_ctx != NULL);

  hhsp = (hal_hsp_handle_t *)(p_if_ctx->hdriver);

  if (HAL_HSP_ADCIN_Start(hhsp, 0U) != HAL_OK)
  {
    return HSP_IF_ERROR;
  }

  return HSP_IF_OK;
#else
  UNUSED(p_if_ctx);

  return HSP_IF_ERROR;
#endif /* USE_HAL_HSP_ADCIN */
}

/**
  * @brief Disable the ADCIN interface.
  * @param  p_if_ctx  Pointer to the interface context.
  * @retval HSP_IF_OK     Action complete successfully
  * @retval HSP_IF_ERROR  Action failed
  */
hsp_if_status_t HSP_HW_IF_SEQ_ADCIN_Disable(hsp_hw_if_ctx_t *p_if_ctx)
{
#if defined(USE_HAL_HSP_ADCIN) && (USE_HAL_HSP_ADCIN == 1)
  hal_hsp_handle_t *hhsp;

  HSP_ASSERT_DBG_PARAM(p_if_ctx != NULL);

  hhsp = (hal_hsp_handle_t *)(p_if_ctx->hdriver);

  if (HAL_HSP_ADCIN_Stop(hhsp) != HAL_OK)
  {
    return HSP_IF_ERROR;
  }

  return HSP_IF_OK;
#else
  UNUSED(p_if_ctx);

  return HSP_IF_ERROR;
#endif /* USE_HAL_HSP_ADCIN */
}

/**
  * @brief  Get an ADCIN Buffer address.
  * @param  hdriver  Pointer to a driver.
  * @param  adcin_id  ADCIN buffer identifier.
  * @return Buffer address.
  */
const volatile uint32_t *HSP_HW_IF_SEQ_ADCIN_GetBufferAddress(void *hdriver, uint32_t adcin_id)
{
#if defined(USE_HAL_HSP_ADCIN) && (USE_HAL_HSP_ADCIN == 1)
  HSP_ASSERT_DBG_PARAM(hdriver != NULL);
  hal_hsp_handle_t *hhsp = (hal_hsp_handle_t *)(hdriver);
  return HAL_HSP_ADCIN_GetBufferAddress(hhsp, (hal_hsp_adcin_t)adcin_id);
#else
  UNUSED(hdriver);
  UNUSED(adcin_id);

  return NULL;
#endif /* USE_HAL_HSP_ADCIN */
}

#endif /* USE_HSP_ENGINE_ADCIN */
/**
  * @brief Configure an event with a TRGIN trigger as source.
  * @param  p_if_ctx        Pointer to the interface context.
  * @param  event_id        Event ID.
  * @param  trigger_source  TRGIN Source
  * @param  polarity        Rising or Falling edge
  * @param  event_sync      Enable Synchronisation with End Of Task.
  * @retval HSP_IF_OK     Action complete successfully
  * @retval HSP_IF_ERROR  Action failed
  */
hsp_if_status_t HSP_HW_IF_SEQ_EVENT_SetConfig_Trigger(hsp_hw_if_ctx_t *p_if_ctx, uint32_t event_id,
                                                      uint32_t trigger_source, uint32_t polarity,
                                                      uint32_t event_sync)
{
  hal_hsp_handle_t *hhsp;
  uint32_t trgin_instances;
  uint32_t first_trgin_id;
  uint32_t second_trgin_id;
  uint32_t selected_trgin_id;
  uint32_t hal_trgin_id;
  hal_hsp_trgin_config_t trgin_cfg;
  hal_hsp_prc_task_config_t evt_cfg;

  HSP_ASSERT_DBG_PARAM(p_if_ctx != NULL);
  HSP_ASSERT_DBG_PARAM(IS_HSP_HW_IF_PRC_EVENT_ID(event_id));

  hhsp = (hal_hsp_handle_t *)(p_if_ctx->hdriver);

  /* Get the TRGIN used status */
  trgin_instances = p_if_ctx->trgin_instances;

  first_trgin_id = HSP_EVENT_GET_FIRST_TRGIN_ID(event_id);
  second_trgin_id = HSP_EVENT_GET_SECOND_TRGIN_ID(event_id);

  if ((trgin_instances & (1UL << first_trgin_id)) == 0U)
  {
    selected_trgin_id = first_trgin_id;
  }
  else if ((trgin_instances & (1UL << second_trgin_id)) == 0U)
  {
    selected_trgin_id = second_trgin_id;
  }
  else
  {
    return HSP_IF_ERROR;
  }

  /* Get the HAL HSP TRGIN define value */
  hal_trgin_id = GET_HAL_HSP_TRGIN_ID(selected_trgin_id);
  if (hal_trgin_id == 0xFFFFU)
  {
    return HSP_IF_ERROR;
  }

  /* Config the TRGINx */
  trgin_cfg.polarity = (hal_hsp_trgin_polarity_t)polarity;
  trgin_cfg.source = (hal_hsp_trgin_source_t)trigger_source;

  if (HAL_HSP_TRGIN_SetConfigTriggers(hhsp, hal_trgin_id, &trgin_cfg) != HAL_OK)
  {
    return HSP_IF_ERROR;
  }

  /* Configure the Event */
  if (HSP_HW_IF_Retrieve_TRGIN_HAL_Event_Source_Enum(event_id, selected_trgin_id, &evt_cfg.source) != 0U)
  {
    return HSP_IF_ERROR;
  }

  if (event_sync == HSP_HW_IF_SEQ_EVENT_SYNC_DISABLED)
  {
    evt_cfg.sync = HAL_HSP_PRC_TASK_SYNC_NONE;
  }
  else
  {
    evt_cfg.sync = (hal_hsp_prc_task_sync_source_t)event_sync;
  }

  if (HAL_HSP_PRC_SetMultiTaskConfig(hhsp, &evt_cfg, 1U) != HAL_OK)
  {
    return HSP_IF_ERROR;
  }

  /* Enable the TRGINx instance */
  if (HAL_HSP_TRGIN_EnableTriggers(hhsp, hal_trgin_id) != HAL_OK)
  {
    return HSP_IF_ERROR;
  }

  /* Update the mask of TRGIN instances used */
  p_if_ctx->trgin_instances = (trgin_instances | (1UL << selected_trgin_id));

  return HSP_IF_OK;
}

/**
  * @brief Configure an event with the CSEG interface as source.
  * @param  hdriver   HSP Driver handle.
  * @param  event_id  Event ID.
  * @param  tcu_sync  Task Comparator Synchronization
  * @retval HSP_IF_OK     Action complete successfully
  * @retval HSP_IF_ERROR  Action failed
  */
hsp_if_status_t HSP_HW_IF_SEQ_EVENT_SetConfig_CSEG(void *hdriver, uint32_t event_id, uint32_t tcu_sync)
{
  hal_hsp_handle_t *hhsp;
  hal_hsp_prc_task_config_t evt_cfg;

  HSP_ASSERT_DBG_PARAM(hdriver != NULL);

  hhsp = (hal_hsp_handle_t *)(hdriver);

  evt_cfg.source = HAL_HSP_EVENT_SOURCE_GET_ENUM_FOR_CSEG(event_id);

  if (tcu_sync == HSP_HW_IF_SEQ_EVENT_SYNC_DISABLED)
  {
    evt_cfg.sync = HAL_HSP_PRC_TASK_SYNC_NONE;
  }
  else
  {
    evt_cfg.sync = (hal_hsp_prc_task_sync_source_t)tcu_sync;
  }

  if (HAL_HSP_PRC_SetMultiTaskConfig(hhsp, &evt_cfg, 1U) != HAL_OK)
  {
    return HSP_IF_ERROR;
  }

  return HSP_IF_OK;
}

/**
  * @brief Configure an event with the HSEG interface as source.
  * @param  hdriver   HSP Driver handle.
  * @param  event_id  Event ID.
  * @param  tcu_sync  Task Comparator Synchronization
  * @retval HSP_IF_OK     Action complete successfully
  * @retval HSP_IF_ERROR  Action failed
  */
hsp_if_status_t HSP_HW_IF_SEQ_EVENT_SetConfig_SPE(void *hdriver, uint32_t event_id, uint32_t tcu_sync)
{
  hal_hsp_handle_t *hhsp;
  hal_hsp_prc_task_config_t evt_cfg;

  HSP_ASSERT_DBG_PARAM(hdriver != NULL);

  hhsp = (hal_hsp_handle_t *)(hdriver);

  evt_cfg.source = HAL_HSP_EVENT_SOURCE_GET_ENUM_FOR_HSEG(event_id);

  if (tcu_sync == HSP_HW_IF_SEQ_EVENT_SYNC_DISABLED)
  {
    evt_cfg.sync = HAL_HSP_PRC_TASK_SYNC_NONE;
  }
  else
  {
    evt_cfg.sync = (hal_hsp_prc_task_sync_source_t)tcu_sync;
  }

  if (HAL_HSP_PRC_SetMultiTaskConfig(hhsp, &evt_cfg, 1U) != HAL_OK)
  {
    return HSP_IF_ERROR;
  }

  return HSP_IF_OK;
}

/**
  * @brief Enable HSP events attached to Processing Lists.
  * @param  hdriver   HSP Driver handle.
  * @param  events_mask  Mask of Events to enable.
  * @retval HSP_IF_OK     Action complete successfully
  * @retval HSP_IF_ERROR  Action failed
  */
hsp_if_status_t HSP_HW_IF_SEQ_EVENT_Enable(void *hdriver, uint32_t events_mask)
{
  HSP_ASSERT_DBG_PARAM(hdriver != NULL);

  hal_hsp_handle_t *hhsp = (hal_hsp_handle_t *)(hdriver);

  if (HAL_HSP_PRC_EnableEvents(hhsp, events_mask) != HAL_OK)
  {
    return HSP_IF_ERROR;
  }

  return HSP_IF_OK;
}

/**
  * @brief Disable HSP events attached to Processing Lists.
  * @param  hdriver   HSP Driver handle.
  * @param  events_mask  Mask of Events to disable.
  * @retval HSP_IF_OK     Action complete successfully
  * @retval HSP_IF_ERROR  Action failed
  */
hsp_if_status_t HSP_HW_IF_SEQ_EVENT_Disable(void *hdriver, uint32_t events_mask)
{
  hal_hsp_handle_t *hhsp;

  HSP_ASSERT_DBG_PARAM(hdriver != NULL);

  hhsp = (hal_hsp_handle_t *)(hdriver);

  if (HAL_HSP_PRC_DisableEvents(hhsp, events_mask) != HAL_OK)
  {
    return HSP_IF_ERROR;
  }

  return HSP_IF_OK;
}

/**
  * @brief Get the enabling status of HSP events.
  * @param  hdriver   HSP Driver handle.
  * @return Mask of enabled HSP Events
  */
uint32_t HSP_HW_IF_SEQ_EVENT_GetStatus(void *hdriver)
{
  hal_hsp_handle_t *hhsp;

  HSP_ASSERT_DBG_PARAM(hdriver != NULL);

  hhsp = (hal_hsp_handle_t *)(hdriver);

  return HAL_HSP_PRC_GetActiveEvents(hhsp);
}

/**
  * @brief Request execution of Processing Lists attached to CSEG interface.
  * @param  hdriver   HSP Driver handle.
  * @param  events_mask  Mask of Events to trig.
  * @retval HSP_IF_OK     Action complete successfully
  * @retval HSP_IF_ERROR  Action failed
  */
hsp_if_status_t HSP_HW_IF_SEQ_EVENT_Trig_CSEG(void *hdriver, uint32_t events_mask)
{
  HSP_ASSERT_DBG_PARAM(hdriver != NULL);

  hal_hsp_handle_t *hhsp = (hal_hsp_handle_t *)(hdriver);

  if (HAL_HSP_PRC_SWRequestTask(hhsp, events_mask) != HAL_OK)
  {
    return HSP_IF_ERROR;
  }

  return HSP_IF_OK;
}

/**
  * @brief Poll until the Request execution is taken into account.
  * @param  hdriver   HSP Driver handle.
  * @param  events_mask  Mask of Events to poll.
  * @param  timeout_ms   Timeout in millisecond
  * @retval HSP_IF_OK     Action complete successfully
  * @retval HSP_IF_ERROR  Action failed
  */
hsp_if_status_t HSP_HW_IF_SEQ_EVENT_PollForPending(void *hdriver, uint32_t events_mask, uint32_t timeout_ms)
{
  HSP_ASSERT_DBG_PARAM(hdriver != NULL);

  hal_hsp_handle_t *hhsp = (hal_hsp_handle_t *)(hdriver);
  uint32_t event_status = 0U;

  if (HAL_HSP_PRC_PollForEvent(hhsp, HAL_HSP_POLLING_FOR_ALL_EVENT,
                               events_mask, timeout_ms, &event_status) != HAL_OK)
  {
    return HSP_IF_ERROR;
  }

  return HSP_IF_OK;
}

/* API to BRAM Access control ------------------------------------------------*/
hsp_if_status_t HSP_HW_IF_BRAM_EnableConflictAccessCounter(void *hdriver)
{
  hal_hsp_handle_t *hhsp;

  HSP_ASSERT_DBG_PARAM(hdriver != NULL);

  hhsp = (hal_hsp_handle_t *)(hdriver);

  if (HAL_HSP_BRAM_EnableConflictAccessCounter(hhsp) != HAL_OK)
  {
    return HSP_IF_ERROR;
  }

  return HSP_IF_OK;
}

hsp_if_status_t HSP_HW_IF_BRAM_DisableConflictAccessCounter(void *hdriver)
{
  hal_hsp_handle_t *hhsp;

  HSP_ASSERT_DBG_PARAM(hdriver != NULL);

  hhsp = (hal_hsp_handle_t *)(hdriver);

  if (HAL_HSP_BRAM_DisableConflictAccessCounter(hhsp) != HAL_OK)
  {
    return HSP_IF_ERROR;
  }

  return HSP_IF_OK;
}

uint32_t HSP_HW_IF_BRAM_GetConflictAccessCounter(void *hdriver)
{
  hal_hsp_handle_t *hhsp;

  HSP_ASSERT_DBG_PARAM(hdriver != NULL);

  hhsp = (hal_hsp_handle_t *)(hdriver);

  return HAL_HSP_BRAM_GetConflictAccessCounter(hhsp);
}

hsp_if_status_t HSP_HW_IF_BRAM_SetBandwidthArbitration(void *hdriver, uint32_t latency)
{
  hal_hsp_handle_t *hhsp;
  hal_hsp_bram_latency_t hal_latency;

  HSP_ASSERT_DBG_PARAM(hdriver != NULL);

  hhsp = (hal_hsp_handle_t *)(hdriver);

  switch (latency)
  {
    case 0 :
      hal_latency = HAL_HSP_BRAM_LATENCY_16_CYCLES;
      break;
    case 1 :
      hal_latency = HAL_HSP_BRAM_LATENCY_8_CYCLES;
      break;
    case 2 :
      hal_latency = HAL_HSP_BRAM_LATENCY_4_CYCLES;
      break;
    default:
      return HSP_IF_ERROR;
  }

  if (HAL_HSP_BRAM_SetLatency(hhsp, hal_latency) != HAL_OK)
  {
    return HSP_IF_ERROR;
  }

  return HSP_IF_OK;
}

uint32_t HSP_HW_IF_BRAM_GetBandwidthArbitration(void *hdriver)
{
  hal_hsp_handle_t *hhsp;
  hal_hsp_bram_latency_t hal_value;
  uint32_t mw_hsp_latency;

  HSP_ASSERT_DBG_PARAM(hdriver != NULL);

  hhsp = (hal_hsp_handle_t *)(hdriver);

  hal_value = HAL_HSP_BRAM_GetLatency(hhsp);
  switch (hal_value)
  {
    case HAL_HSP_BRAM_LATENCY_16_CYCLES:
      mw_hsp_latency = 0U;
      break;
    case HAL_HSP_BRAM_LATENCY_8_CYCLES:
      mw_hsp_latency = 1U;
      break;
    case HAL_HSP_BRAM_LATENCY_4_CYCLES:
      mw_hsp_latency = 2U;
      break;
    default:
      return 0U;
  }

  return mw_hsp_latency;
}

/* API for secure Access -----------------------------------------------------*/
hsp_if_status_t HSP_HW_IF_Lock(const hsp_hw_if_ctx_t *p_if_ctx)
{
  hal_hsp_handle_t *hhsp;

  HSP_ASSERT_DBG_PARAM(p_if_ctx != NULL);

  hhsp = (hal_hsp_handle_t *)(p_if_ctx->hdriver);

  if (HAL_HSP_Lock(hhsp) != HAL_OK)
  {
    return HSP_IF_ERROR;
  }

  return HSP_IF_OK;
}

#if defined(USE_HSP_MODULES_PROCLIST) && (USE_HSP_MODULES_PROCLIST == 1U)
hsp_if_status_t HSP_HW_IF_SEQ_EnableProclistEventsIT(void *hdriver, uint32_t interrupts)
{
  HSP_ASSERT_DBG_PARAM(hdriver != NULL);

  hal_hsp_handle_t *hhsp = (hal_hsp_handle_t *)(hdriver);

  if (HAL_HSP_PROCLIST_EnableIT(hhsp, interrupts) != HAL_OK)
  {
    return HSP_IF_ERROR;
  }

  return HSP_IF_OK;
}

hsp_if_status_t HSP_HW_IF_SEQ_DisableProclistEventsIT(void *hdriver, uint32_t interrupts)
{
  HSP_ASSERT_DBG_PARAM(hdriver != NULL);

  hal_hsp_handle_t *hhsp = (hal_hsp_handle_t *)(hdriver);

  if (HAL_HSP_PROCLIST_DisableIT(hhsp, interrupts) != HAL_OK)
  {
    return HSP_IF_ERROR;
  }

  return HSP_IF_OK;
}
#endif /* USE_HSP_MODULES_PROCLIST */

/* API to manage Task Comparator Unit ----------------------------------------*/

/**
  * @brief Configure and start a Task Comparator.
  * @param  p_if_ctx  Pointer to the interface context.
  * @param  tcu_id    ID of the Task Comparator Unit.
  * @param  task_id   Task ID to monitor.
  * @retval HSP_IF_OK     Action complete successfully
  * @retval HSP_IF_ERROR  Action failed
  */
hsp_if_status_t HSP_HW_IF_StartTaskComparator(const hsp_hw_if_ctx_t *p_if_ctx, uint32_t tcu_id, uint32_t task_id)
{
  hal_hsp_handle_t *hhsp;

  HSP_ASSERT_DBG_PARAM((p_if_ctx != NULL));

  hhsp = (hal_hsp_handle_t *)(p_if_ctx->hdriver);

  if (HAL_HSP_TCU_StartComparator(hhsp, (hal_hsp_task_comparator_t)tcu_id,
                                  (hal_hsp_task_t)task_id, HAL_HSP_IT_NONE) != HAL_OK)
  {
    return HSP_IF_ERROR;
  }

  return HSP_IF_OK;
}

#if defined(USE_HSP_ENGINE_TCU_IT) && (USE_HSP_ENGINE_TCU_IT == 1U)
/**
  * @brief Configure and start a Task Comparator in IT mode.
  * @param  p_if_ctx  Pointer to the interface context.
  * @param  tcu_id    ID of the Task Comparator Unit.
  * @param  task_id   Task ID to monitor.
  * @retval HSP_IF_OK     Action complete successfully
  * @retval HSP_IF_ERROR  Action failed
  */
hsp_if_status_t HSP_HW_IF_StartTaskComparator_IT(const hsp_hw_if_ctx_t *p_if_ctx, uint32_t tcu_id, uint32_t task_id)
{
  hal_hsp_handle_t *hhsp;
  uint32_t interrupts;

  HSP_ASSERT_DBG_PARAM((p_if_ctx != NULL));

  hhsp = (hal_hsp_handle_t *)(p_if_ctx->hdriver);

  interrupts = (HAL_HSP_TCU_IT_CMP_0_ALL << tcu_id);

  if (HAL_HSP_TCU_StartComparator(hhsp, (hal_hsp_task_comparator_t)tcu_id,
                                  (hal_hsp_task_t)task_id, interrupts) != HAL_OK)
  {
    return HSP_IF_ERROR;
  }

  return HSP_IF_OK;
}
#endif /* USE_HSP_ENGINE_TCU_IT */

/**
  * @brief Stop a Task Comparator.
  * @param  p_if_ctx  Pointer to the interface context.
  * @param  tcu_id    ID of the Task Comparator Unit.
  * @retval HSP_IF_OK     Action complete successfully
  * @retval HSP_IF_ERROR  Action failed
  */
hsp_if_status_t HSP_HW_IF_StopTaskComparator(const hsp_hw_if_ctx_t *p_if_ctx, uint32_t tcu_id)
{
  hal_hsp_handle_t *hhsp;

  HSP_ASSERT_DBG_PARAM((p_if_ctx != NULL));

  hhsp = (hal_hsp_handle_t *)(p_if_ctx->hdriver);

  if (HAL_HSP_TCU_StopComparator(hhsp, (hal_hsp_task_comparator_t)tcu_id) != HAL_OK)
  {
    return HSP_IF_ERROR;
  }

  return HSP_IF_OK;
}

/* API for TimeStamp Capture -------------------------------------------------*/
#if defined(USE_HSP_ENGINE_TIMESTAMPCAPTURE) && (USE_HSP_ENGINE_TIMESTAMPCAPTURE == 1U)
/**
  * @brief Set the TimeStamp Capture DMA handle.
  * @param  p_if_ctx  Pointer to the interface context.
  * @param  hdma      Pointer to a DMA handle.
  * @retval HSP_IF_OK     Action complete successfully
  * @retval HSP_IF_ERROR  Action failed
  */
hsp_if_status_t HSP_HW_IF_TSC_SetDMA(hsp_hw_if_ctx_t *p_if_ctx, void *hdma)
{
  HSP_ASSERT_DBG_PARAM((p_if_ctx != NULL));
  HSP_ASSERT_DBG_PARAM((hdma != NULL));

  p_if_ctx->hdma_tsc = hdma;

  return HSP_IF_OK;
}

/**
  * @brief Configure the TimeStamp Capture.
  * @param  p_if_ctx    Pointer to the interface context.
  * @param  prescaler  Timestamp counter prescaler
  * @param  task_id    Task ID to monitor
  * @retval HSP_IF_OK     Action complete successfully
  * @retval HSP_IF_ERROR  Action failed
  */
hsp_if_status_t HSP_HW_IF_TSC_SetConfig(const hsp_hw_if_ctx_t *p_if_ctx,
                                        uint32_t prescaler, uint32_t task_id)
{
  hal_hsp_handle_t *hhsp;
  hal_hsp_tsc_config_t tsc_cfg;

  HSP_ASSERT_DBG_PARAM((p_if_ctx != NULL));

  hhsp = (hal_hsp_handle_t *)(p_if_ctx->hdriver);

  if (prescaler == HSP_HW_IF_TSC_PRESCALER_DISABLE)
  {
    tsc_cfg.prescaler = HAL_HSP_TSC_PRESCALER_BYPASSED;
    tsc_cfg.counter = HAL_HSP_TSC_FREE_COUNTER_DISABLE;
  }
  else
  {
    tsc_cfg.prescaler = (hal_hsp_tsc_prescaler_t)prescaler;
    tsc_cfg.counter = HAL_HSP_TSC_FREE_COUNTER_ENABLE;
  }

  if (task_id < (uint32_t)HAL_HSP_TASK_SUPERVISOR)
  {
    tsc_cfg.filter = HAL_HSP_TSC_TASK_FILTER_TSKCMP0;

    if (HAL_HSP_TCU_StartComparator(hhsp, HAL_HSP_TASK_COMPARATOR_0,
                                    (hal_hsp_task_t)task_id, HAL_HSP_IT_NONE) != HAL_OK)
    {
      return HSP_IF_ERROR;
    }
  }
  else
  {
    tsc_cfg.filter = HAL_HSP_TSC_TASK_FILTER_NONE;
  }

  if (HAL_HSP_TSC_SetConfig(hhsp, &tsc_cfg) != HAL_OK)
  {
    return HSP_IF_ERROR;
  }

  if (HSP_HW_IF_TSC_SetTRGOConfigFromDMA(p_if_ctx) != HSP_IF_OK)
  {
    return HSP_IF_ERROR;
  }

  return HSP_IF_OK;
}

/**
  * @brief  Start the TimeStamp Capture.
  * @param  p_if_ctx  Pointer to the interface context.
  * @param  mode      Mode of capture
  * @retval HSP_IF_OK     Action complete successfully
  * @retval HSP_IF_ERROR  Action failed
  */
hsp_if_status_t HSP_HW_IF_TSC_Start(hsp_hw_if_ctx_t *p_if_ctx, uint32_t mode)
{
  hal_hsp_handle_t *hhsp;

  HSP_ASSERT_DBG_PARAM((p_if_ctx != NULL));

  hhsp = (hal_hsp_handle_t *)(p_if_ctx->hdriver);

  /* Enable the HSP TRGO interface to allow to trigger a DMA at each TimeStamp Capture data */
  if (HAL_HSP_TRGO_Enable(hhsp) != HAL_OK)
  {
    return HSP_IF_ERROR;
  }

  if (HAL_HSP_TSC_Start(hhsp, (hal_hsp_tsc_capture_mode_t)mode, HAL_HSP_IT_NONE, HAL_HSP_IT_NONE) != HAL_OK)
  {
    return HSP_IF_ERROR;
  }

  return HSP_IF_OK;
}

/**
  * @brief Stop the TimeStamp Capture.
  * @param  p_if_ctx  Pointer to the interface context.
  * @retval HSP_IF_OK     Action complete successfully
  * @retval HSP_IF_ERROR  Action failed
  */
hsp_if_status_t HSP_HW_IF_TSC_Stop(const hsp_hw_if_ctx_t *p_if_ctx)
{
  hal_hsp_handle_t *hhsp;

  HSP_ASSERT_DBG_PARAM((p_if_ctx != NULL));

  hhsp = (hal_hsp_handle_t *)(p_if_ctx->hdriver);

  if (HAL_HSP_TSC_Stop(hhsp) != HAL_OK)
  {
    return HSP_IF_ERROR;
  }

  if (HAL_HSP_TCU_StopComparator(hhsp, HAL_HSP_TASK_COMPARATOR_0) != HAL_OK)
  {
    return HSP_IF_ERROR;
  }

  return HSP_IF_OK;
}

/**
  * @brief  Get the address of the TimeStamp Capture buffer.
  * @param  p_if_ctx  Pointer to the interface context.
  * @retval Pointer to the TimeStamp Capture buffer
  */
volatile const uint32_t *HSP_HW_IF_TSC_GetBufferAddress(const hsp_hw_if_ctx_t *p_if_ctx)
{
  hal_hsp_handle_t *hhsp;

  HSP_ASSERT_DBG_PARAM(p_if_ctx != NULL);

  hhsp = (hal_hsp_handle_t *)(p_if_ctx->hdriver);

  return &(((HSP_TypeDef *)(hhsp->instance))->CAPDR); /* HAL_HSP_TSC_GetBufferAddress(hhsp);*/
}

#endif /* USE_HSP_ENGINE_TIMESTAMPCAPTURE */

/**
  * @brief Retrieve the HSP Firmware Error Code.
  * @param  hdriver  Pointer to a HSP handle.
  * @return FW Error Code
  */
uint32_t HSP_HW_IF_GetFirmwareError(void *hdriver)
{
  hal_hsp_handle_t *hhsp;

  HSP_ASSERT_DBG_PARAM(hdriver != NULL);

  hhsp = (hal_hsp_handle_t *)(hdriver);

  return HAL_HSP_GetFirmwareErrorCode(hhsp);
}

/**
  * @brief Wait semaphore and release semaphore.
  * @param  hdriver  Pointer to a HSP handle.
  * @retval HSP_IF_OK     Action complete successfully
  */
hsp_if_status_t HSP_HW_IF_WaitAndReleaseSemaphore(void *hdriver)
{
  hal_hsp_handle_t *hhsp;

  HSP_ASSERT_DBG_PARAM(hdriver != NULL);

  hhsp = (hal_hsp_handle_t *)(hdriver);

  /* Wait direct command done */
  while (HAL_HSP_MSGBOX_IsMessageAvailable(hhsp) == HAL_HSP_MSGBOX_SEMAPHORE_NO_MSG);

  /* Clear Semahore */
  HAL_HSP_MSGBOX_AckSemaphore(hhsp);

  return HSP_IF_OK;
}

/**
  * @brief Wait semaphore and release semaphore.
  * @param  hdriver  Pointer to a HSP handle.
  * @retval HSP_IF_OK     Action complete successfully
  */
hsp_if_status_t HSP_HW_IF_WaitSemaphore(void *hdriver)
{
  hal_hsp_handle_t *hhsp;

  HSP_ASSERT_DBG_PARAM(hdriver != NULL);

  hhsp = (hal_hsp_handle_t *)(hdriver);

  /* Wait direct command done */
  while (HAL_HSP_MSGBOX_IsMessageAvailable(hhsp) == HAL_HSP_MSGBOX_SEMAPHORE_NO_MSG);

  return HSP_IF_OK;
}

/**
  * @brief Release Semaphore.
  * @param  hdriver  Pointer to a HSP handle.
  */
void HSP_HW_IF_ReleaseSemaphore(void *hdriver)
{
  HSP_ASSERT_DBG_PARAM(hdriver != NULL);

  hal_hsp_handle_t *hhsp = (hal_hsp_handle_t *)(hdriver);

  /* Clear Semaphore */
  HAL_HSP_MSGBOX_AckSemaphore(hhsp);
}

/* API for CNN ---------------------------------------------------------------*/
/**
  * @brief Prepare the HSP to execute the CNN.
  *   The function disables all HSP Event & ITs to avoid any interruption during the CNN processing.
  * @param  hdriver  Pointer to a HSP handle.
  * @param  cmd_id   CNN Command ID.
  * @retval HSP_IF_OK     Action complete successfully
  * @retval HSP_IF_ERROR  Action failed
  */
hsp_if_status_t HSP_HW_IF_CNN_Begin(void *hdriver, uint32_t cmd_id)
{
  hal_hsp_handle_t *hhsp;

  HSP_ASSERT_DBG_PARAM(hdriver != NULL);

  hhsp = (hal_hsp_handle_t *)(hdriver);
  /* Send the CNN Direct Command */
  (void) HAL_HSP_DCMD_WriteCommand(hhsp, cmd_id);

  if (HAL_HSP_CNN_EnterSafeMode(hhsp) != HAL_OK)
  {
    return HSP_IF_ERROR;
  }

  return HSP_IF_OK;
}

/**
  * @brief Run the computing of a CNN.
  * @param  hdriver     Pointer to a HSP handle.
  * @param  cnn_cmd_id  CNN Command ID.
  * @retval HSP_IF_OK   Action complete successfully
  */
hsp_if_status_t HSP_HW_IF_CNN_StartOfProcess(void *hdriver, uint32_t cnn_cmd_id)
{
  hal_hsp_handle_t *hhsp;

  HSP_ASSERT_DBG_PARAM(hdriver != NULL);

  hhsp = (hal_hsp_handle_t *)(hdriver);

  if (HAL_HSP_PRC_SWRequestLowestPriorityTask(hhsp, (hal_hsp_task_t)cnn_cmd_id, HAL_HSP_PRC_TASK_SYNC_NONE,
                                              HAL_HSP_IT_NONE) != HAL_OK)
  {
    return HSP_IF_ERROR;
  }

  return HSP_IF_OK;
}

/**
  * @brief Wait End of CNN .
  * @param  hdriver  Pointer to a HSP handle.
  * @retval HSP_IF_OK     Action complete successfully
  */
hsp_if_status_t HSP_HW_IF_CNN_WaitEndOfProcess(void *hdriver)
{
  hal_hsp_handle_t *hhsp;

  HSP_ASSERT_DBG_PARAM(hdriver != NULL);

  hhsp = (hal_hsp_handle_t *)(hdriver);
  /* Wait direct command done */
  while (HAL_HSP_MSGBOX_IsMessageAvailable(hhsp) == HAL_HSP_MSGBOX_SEMAPHORE_NO_MSG);

  /* Clear Semahore */
  HAL_HSP_MSGBOX_AckSemaphore(hhsp);

  return HSP_IF_OK;
}

/**
  * @brief End the process of a CNN.
  * @param  hdriver  Pointer to a HSP handle.
  * @retval HSP_IF_OK     Action complete successfully
  * @retval HSP_IF_ERROR  Action failed
  */
hsp_if_status_t HSP_HW_IF_CNN_End(void *hdriver)
{
  HSP_ASSERT_DBG_PARAM(hdriver != NULL);
  hal_hsp_handle_t *hhsp = (hal_hsp_handle_t *)(hdriver);

  if (HAL_HSP_CNN_ExitSafeMode(hhsp) != HAL_OK)
  {
    return HSP_IF_ERROR;
  }

  return HSP_IF_OK;
}

/* API for BREAK -------------------------------------------------------------*/
hsp_if_status_t HSP_HW_IF_BREAK_SetMultiOutput(hsp_hw_if_ctx_t *p_if_ctx,
                                               const uint32_t *p_config_array, uint32_t config_array_size)
{
  hal_hsp_handle_t *hhsp;
  hal_hsp_break_output_config_t break_config;

  HSP_ASSERT_DBG_PARAM(p_if_ctx != NULL);
  HSP_ASSERT_DBG_PARAM(p_config_array != NULL);
  HSP_ASSERT_DBG_PARAM(config_array_size > 0U);

  hhsp = (hal_hsp_handle_t *)(p_if_ctx->hdriver);

  for (uint32_t idx = 0U; idx < config_array_size; idx++)
  {
    break_config.output_id = (hal_hsp_break_output_t)idx;
    break_config.critical_events = p_config_array[idx];
    if (HAL_HSP_BREAK_SetMultiConfigOutput(hhsp, &break_config, 1U) != HAL_OK)
    {
      return HSP_IF_ERROR;
    }
  }

  return HSP_IF_OK;
}

hsp_if_status_t HSP_HW_IF_BREAK_SetDebugEvents(hsp_hw_if_ctx_t *p_if_ctx, uint32_t debug_events)
{
  hal_hsp_handle_t *hhsp;

  HSP_ASSERT_DBG_PARAM(p_if_ctx != NULL);

  hhsp = (hal_hsp_handle_t *)(p_if_ctx->hdriver);

  if (HAL_HSP_BREAK_SetDebugEvents(hhsp, debug_events) != HAL_OK)
  {
    return HSP_IF_ERROR;
  }

  return HSP_IF_OK;
}

hsp_if_status_t HSP_HW_IF_BREAK_ResumeDebugEvents(hsp_hw_if_ctx_t *p_if_ctx)
{
  hal_hsp_handle_t *hhsp;

  HSP_ASSERT_DBG_PARAM(p_if_ctx != NULL);

  hhsp = (hal_hsp_handle_t *)(p_if_ctx->hdriver);

  if (HAL_HSP_BREAK_ResumeDebugEvents(hhsp) != HAL_OK)
  {
    return HSP_IF_ERROR;
  }

  return HSP_IF_OK;
}

/* API for STI ---------------------------------------------------------------*/
#if defined(USE_HSP_STI_AP_PORT) && (USE_HSP_STI_AP_PORT == 1)
hsp_if_status_t HSP_HW_IF_STI_SetPortAddress(hsp_hw_if_ctx_t *p_if_ctx, uint32_t sti_port_id, uint32_t block_address)
{
  hal_hsp_handle_t *hhsp;

  HSP_ASSERT_DBG_PARAM(p_if_ctx != NULL);

  hhsp = (hal_hsp_handle_t *)(p_if_ctx->hdriver);

  if (HAL_HSP_STI_SetPortAddress(hhsp, (hal_hsp_sti_ap_port_t)sti_port_id, block_address) != HAL_OK)
  {
    return HSP_IF_ERROR;
  }

  return HSP_IF_OK;
}
#endif /* USE_HSP_STI_AP_PORT */

#if defined(USE_HSP_ENGINE_TIMESTAMPCAPTURE) && (USE_HSP_ENGINE_TIMESTAMPCAPTURE == 1U)
/* API for DMA ---------------------------------------------------------------*/
hsp_if_status_t HSP_HW_IF_DMA_Start(void *hdma, uint32_t src_addr, uint32_t dest_addr, uint32_t data_size)
{
  hal_dma_handle_t *hhdma;

  HSP_ASSERT_DBG_PARAM(hdma != NULL);

  hhdma = (hal_dma_handle_t *)(hdma);

  if (HAL_DMA_StartDirectXfer_IT(hhdma, src_addr, dest_addr, data_size) != HAL_OK)
  {
    return HSP_IF_ERROR;
  }

  return HSP_IF_OK;
}
#endif /* USE_HSP_ENGINE_TIMESTAMPCAPTURE */

/* API Register MW Callbacks ------------------------------------------------ */
/**
  * @brief  Register a User HSP callback for any Error Event.
  * @param  p_if_ctx    Pointer to the interface context.
  * @param  p_callback  Pointer to the callback function.
  * @retval HSP_IF_OK   Registering completed successfully.
  */
hsp_if_status_t HSP_HW_IF_RegisterErrorCallback(hsp_hw_if_ctx_t *p_if_ctx, p_hsp_engine_error_cb_t p_callback)
{
  HSP_ASSERT_DBG_PARAM(p_if_ctx != NULL);
  HSP_ASSERT_DBG_PARAM(p_callback != NULL);

  p_if_ctx->p_error_cb = p_callback;

  return HSP_IF_OK;
}

#if defined(USE_HSP_MODULES_PROCLIST) && (USE_HSP_MODULES_PROCLIST == 1U)
/**
  * @brief  Register a User HSP callback for any Processing List Event.
  * @param  p_if_ctx    Pointer to the interface context.
  * @param  p_callback  Pointer to the callback function.
  * @retval HSP_IF_OK   Registering completed successfully.
  */
hsp_if_status_t HSP_HW_IF_RegisterProcListEventsCallback(hsp_hw_if_ctx_t *p_if_ctx,
                                                         p_hsp_engine_one_param_cb_t p_callback)
{
  HSP_ASSERT_DBG_PARAM(p_if_ctx != NULL);
  HSP_ASSERT_DBG_PARAM(p_callback != NULL);

  p_if_ctx->ProcListEventsCallback = p_callback;

  return HSP_IF_OK;
}
#endif /* USE_HSP_MODULES_PROCLIST */

#if defined(USE_HSP_ENGINE_STREAM_BUFFER) && (USE_HSP_ENGINE_STREAM_BUFFER == 1U)
/**
  * @brief  Register a User HSP callback for any Stream Buffer Write Complete Event.
  * @param  p_if_ctx    Pointer to the interface context.
  * @param  p_callback  Pointer to the callback function.
  * @retval HSP_IF_OK   Registering completed successfully.
  */
hsp_if_status_t HSP_HW_IF_RegisterStreamBufferWriteCpltCallback(hsp_hw_if_ctx_t *p_if_ctx,
                                                                p_hsp_engine_one_param_cb_t p_callback)
{
  HSP_ASSERT_DBG_PARAM(p_if_ctx != NULL);
  HSP_ASSERT_DBG_PARAM(p_callback != NULL);

  p_if_ctx->p_stream_buffer_write_cplt_cb = p_callback;

  return HSP_IF_OK;
}

/**
  * @brief  Register a User HSP callback for any Stream Buffer Read Complete Event.
  * @param  p_if_ctx    Pointer to the interface context
  * @param  p_callback  Pointer to the callback function.
  * @retval HSP_IF_OK   Registering completed successfully.
  */
hsp_if_status_t HSP_HW_IF_RegisterStreamBufferReadCpltCallback(hsp_hw_if_ctx_t *p_if_ctx,
                                                               p_hsp_engine_one_param_cb_t p_callback)
{
  HSP_ASSERT_DBG_PARAM(p_if_ctx != NULL);
  HSP_ASSERT_DBG_PARAM(p_callback != NULL);

  p_if_ctx->p_stream_buffer_read_cplt_cb = p_callback;

  return HSP_IF_OK;
}
#endif /* USE_HSP_ENGINE_STREAM_BUFFER */

#if defined(USE_HSP_ENGINE_TCU_IT) && (USE_HSP_ENGINE_TCU_IT == 1U)
/**
  * @brief  Register a User HSP callback for Task Comparator Started IT.
  * @param  p_if_ctx    Pointer to the interface context
  * @param  p_callback  Pointer to the callback function.
  * @retval HSP_IF_OK   Registering completed successfully.
  */
hsp_if_status_t HSP_HW_IF_RegisterTCU_TaskStartedCallback(hsp_hw_if_ctx_t *p_if_ctx,
                                                          p_hsp_engine_one_param_cb_t p_callback)
{
  HSP_ASSERT_DBG_PARAM(p_if_ctx != NULL);
  HSP_ASSERT_DBG_PARAM(p_callback != NULL);

  p_if_ctx->p_tcu_task_started_cb = p_callback;

  return HSP_IF_OK;
}

/**
  * @brief  Register a User HSP callback for Task Comparator Ended IT.
  * @param  p_if_ctx    Pointer to the interface context
  * @param  p_callback  Pointer to the callback function.
  * @retval HSP_IF_OK   Registering completed successfully.
  */
hsp_if_status_t HSP_HW_IF_RegisterTCU_TaskEndedCallback(hsp_hw_if_ctx_t *p_if_ctx,
                                                        p_hsp_engine_one_param_cb_t p_callback)
{
  HSP_ASSERT_DBG_PARAM(p_if_ctx != NULL);
  HSP_ASSERT_DBG_PARAM(p_callback != NULL);

  p_if_ctx->p_tcu_task_ended_cb = p_callback;

  return HSP_IF_OK;
}
#endif /* USE_HSP_ENGINE_TCU_IT */

#if defined(USE_HSP_ENGINE_PROCLIST_NOTIFICATION_IT) && (USE_HSP_ENGINE_PROCLIST_NOTIFICATION_IT == 1U)
/**
  * @brief  Register a User HSP callback for Processing List Notification by interrupt.
  * @param  p_if_ctx    Pointer to the interface context
  * @param  p_callback  Pointer to the callback function.
  * @retval HSP_IF_OK   Registering completed successfully.
  */
hsp_if_status_t HSP_HW_IF_RegisterProcessingEventCallback(hsp_hw_if_ctx_t *p_if_ctx,
                                                          p_hsp_engine_one_param_cb_t p_callback)
{
  HSP_ASSERT_DBG_PARAM(p_if_ctx != NULL);
  HSP_ASSERT_DBG_PARAM(p_callback != NULL);

  p_if_ctx->p_proclist_event_cb = p_callback;

  return HSP_IF_OK;
}
#endif /* USE_HSP_ENGINE_PROCLIST_NOTIFICATION_IT */

#if defined(USE_HSP_ENGINE_TIMESTAMPCAPTURE) && (USE_HSP_ENGINE_TIMESTAMPCAPTURE == 1U)
/**
  * @brief Check if a User HSP callback for Timestamp Capture Complete is registered.
  * @param  p_if_ctx    Pointer to the interface context
  * @retval HSP_IF_ERROR  No callback registered
  * @retval HSP_IF_OK     Callback registered
  */
hsp_if_status_t HSP_HW_IF_TSC_IsCompleteCallback(hsp_hw_if_ctx_t *p_if_ctx)
{
  HSP_ASSERT_DBG_PARAM(p_if_ctx != NULL);

  return (p_if_ctx->p_tsc_complete_cb == NULL) ? HSP_IF_ERROR : HSP_IF_OK;
}

/**
  * @brief Check if a User HSP callback for Timestamp Capture Error is registered.
  * @param  p_if_ctx    Pointer to the interface context
  * @retval HSP_IF_ERROR  No callback registered
  * @retval HSP_IF_OK     Callback registered
  */
hsp_if_status_t HSP_HW_IF_TSC_IsErrorCallback(hsp_hw_if_ctx_t *p_if_ctx)
{
  HSP_ASSERT_DBG_PARAM(p_if_ctx != NULL);

  return (p_if_ctx->p_tsc_error_cb == NULL) ? HSP_IF_ERROR : HSP_IF_OK;
}

/**
  * @brief  Register a User HSP callback to inform the Timestamp Capture is completed.
  * @param  p_if_ctx    Pointer to the interface context
  * @param  p_callback  Pointer to the callback function.
  * @retval HSP_IF_OK   Registering completed successfully.
  */
hsp_if_status_t HSP_HW_IF_RegisterTSC_CompleteCallback(hsp_hw_if_ctx_t *p_if_ctx,
                                                       p_hsp_engine_cb_t p_callback)
{
  HSP_ASSERT_DBG_PARAM(p_if_ctx != NULL);
  HSP_ASSERT_DBG_PARAM(p_callback != NULL);

  p_if_ctx->p_tsc_complete_cb = p_callback;

  return HSP_IF_OK;
}

/**
  * @brief  Register a User HSP callback to inform an error on the Timestamp Capture service.
  * @param  p_if_ctx    Pointer to the interface context
  * @param  p_callback  Pointer to the callback function.
  * @retval HSP_IF_OK   Registering completed successfully.
  */
hsp_if_status_t HSP_HW_IF_RegisterTSC_ErrorCallback(hsp_hw_if_ctx_t *p_if_ctx,
                                                    p_hsp_engine_cb_t p_callback)
{
  HSP_ASSERT_DBG_PARAM(p_if_ctx != NULL);
  HSP_ASSERT_DBG_PARAM(p_callback != NULL);

  p_if_ctx->p_tsc_error_cb = p_callback;

  return HSP_IF_OK;
}
#endif /* USE_HSP_ENGINE_TIMESTAMPCAPTURE */

/**
  * @}
  */

/* Private functions ---------------------------------------------------------*/
/** @addtogroup HSP_ENGINE_HW_IF_Private_Functions
  * @{
  */
/**
  * @brief  Error callback.
  * @param  hhsp          Pointer to a @ref hal_hsp_handle_t.
  * @param  error_status  HSP hardware error status.
  * @param  fw_error_code  FW Error Code value.
  * @param  spe_error_inf  SPE Error information value.
  */
static void HSP_HW_IF_ErrorCallback(hal_hsp_handle_t *hhsp, hal_hsp_hw_error_status_t error_status,
                                    uint32_t fw_error_code, uint32_t spe_error_inf)
{
  const hsp_hw_if_ctx_t *p_if_ctx;

  p_if_ctx = (const hsp_hw_if_ctx_t *)HAL_HSP_GetUserData(hhsp);

  p_if_ctx->p_error_cb(p_if_ctx->p_user_data, (uint32_t) error_status, fw_error_code, spe_error_inf);
}

#if defined(USE_HSP_ENGINE_PROCLIST_NOTIFICATION_IT) && (USE_HSP_ENGINE_PROCLIST_NOTIFICATION_IT == 1U)
/**
  * @brief  Processing List Events callback.
  * @param  hhsp         Pointer to a @ref hal_hsp_handle_t.
  * @param  events_mask  Mask of Processing list events.
  */
static void HSP_HW_IF_PROCLIST_EventsCallback(hal_hsp_handle_t *hhsp, uint32_t events_mask)
{
  const hsp_hw_if_ctx_t *p_if_ctx;

  p_if_ctx = (const hsp_hw_if_ctx_t *)HAL_HSP_GetUserData(hhsp);

  p_if_ctx->p_proclist_event_cb(p_if_ctx->p_user_data, events_mask);
}
#endif /* USE_HSP_ENGINE_PROCLIST_NOTIFICATION_IT */

#if defined(USE_HSP_ENGINE_STREAM_BUFFER) && (USE_HSP_ENGINE_STREAM_BUFFER == 1U)
/**
  * @brief  Stream Buffer Empty callback.
  * @param  hhsp          Pointer to a @ref hal_hsp_handle_t.
  * @param  buffers_mask  Mask of Empty STREAM Buffers.
  */
static void HSP_HW_IF_STREAM_BufferEmptyCallback(hal_hsp_handle_t *hhsp, uint32_t buffers_mask)
{
  uint32_t buffer_cplt = 0U;
  const hsp_hw_if_ctx_t *p_if_ctx;

  p_if_ctx = (const hsp_hw_if_ctx_t *)HAL_HSP_GetUserData(hhsp);

  for (uint8_t id = 0U; id < 4U; id++)
  {
    if ((buffers_mask & (1UL << id)) != 0U)
    {
      /* The STREAM Buffer <id> is empty */
      hsp_hw_if_buffer_t *p_buffer = (hsp_hw_if_buffer_t *) & (p_if_ctx->a_user_stream_buffer[id]);
      HAL_HSP_STREAM_WriteBufferData(hhsp, (hal_hsp_stream_buffer_t) id, *(p_buffer->p_data));

      p_buffer->p_data++;
      p_buffer->data_counter--;
      if (p_buffer->data_counter == 0U)
      {
        p_buffer->p_data = NULL;
        buffer_cplt |= (1UL << id);
      }
      else
      {
        /* RE enable the IT which are automatically disabled by the HAL IRQ Handler */
        HAL_HSP_STREAM_Start(hhsp, HAL_HSP_STREAM_IT_BUFFER_0_READY << id, HAL_HSP_STREAM_ERR_IT_BUFFER_0_OVR << id);
      }
    }
  }

  if (buffer_cplt != 0U)
  {
    p_if_ctx->p_stream_buffer_write_cplt_cb(p_if_ctx->p_user_data, buffer_cplt);
  }
}

/**
  * @brief  Stream Buffer Full callback.
  * @param  hhsp Pointer to a @ref hal_hsp_handle_t.
  * @param  buffers_mask  Mask of Full STREAM Buffers.
  */
static void HSP_HW_IF_STREAM_BufferFullCallback(hal_hsp_handle_t *hhsp, uint32_t buffers_mask)
{
  uint32_t buffer_cplt = 0U;
  const hsp_hw_if_ctx_t *p_if_ctx;

  p_if_ctx = (const hsp_hw_if_ctx_t *)HAL_HSP_GetUserData(hhsp);

  for (uint8_t id = 0U; id < 4U; id++)
  {
    if ((buffers_mask & (1UL << id)) != 0U)
    {
      /* The STREAM Buffer <id> is full */
      hsp_hw_if_buffer_t *p_buffer = (hsp_hw_if_buffer_t *) & (p_if_ctx->a_user_stream_buffer[id]);
      *(p_buffer->p_data) = HAL_HSP_STREAM_ReadBufferData(hhsp, (hal_hsp_stream_buffer_t) id);

      p_buffer->p_data++;
      p_buffer->data_counter--;
      if (p_buffer->data_counter == 0U)
      {
        p_buffer->p_data = NULL;
        buffer_cplt |= (1UL << id);
      }
      else
      {
        /* RE enable the IT which are automatically disabled by the HAL IRQ Handler */
        HAL_HSP_STREAM_Start(hhsp, HAL_HSP_STREAM_IT_BUFFER_0_READY << id, HAL_HSP_STREAM_ERR_IT_BUFFER_0_OVR << id);
      }
    }
  }

  if (buffer_cplt != 0U)
  {
    p_if_ctx->p_stream_buffer_read_cplt_cb(p_if_ctx->p_user_data, buffers_mask);
  }
}
#endif /* USE_HSP_ENGINE_STREAM_BUFFER */

#if defined(USE_HSP_ENGINE_TCU_IT) && (USE_HSP_ENGINE_TCU_IT == 1U)
/**
  * @brief  TCU Started Task callback.
  * @param  hhsp    Pointer to a @ref hal_hsp_handle_t.
  * @param tcu_ids  TCU IDs mask.
  */
static void HSP_HW_IF_TCU_TaskStartedCallback(hal_hsp_handle_t *hhsp, uint32_t tcu_ids)
{
  const hsp_hw_if_ctx_t *p_if_ctx;

  p_if_ctx = (const hsp_hw_if_ctx_t *)HAL_HSP_GetUserData(hhsp);

  p_if_ctx->p_tcu_task_started_cb(p_if_ctx->p_user_data, tcu_ids);
}

/**
  * @brief  TCU Ended Task callback.
  * @param  hhsp    Pointer to a @ref hal_hsp_handle_t.
  * @param tcu_ids  TCU IDs mask.
  */
static void HSP_HW_IF_TCU_TaskEndedCallback(hal_hsp_handle_t *hhsp, uint32_t tcu_ids)
{
  const hsp_hw_if_ctx_t *p_if_ctx;

  p_if_ctx = (const hsp_hw_if_ctx_t *)HAL_HSP_GetUserData(hhsp);

  p_if_ctx->p_tcu_task_ended_cb(p_if_ctx->p_user_data, tcu_ids);
}
#endif /* USE_HSP_ENGINE_TCU_IT */

#if defined(USE_HSP_ENGINE_TIMESTAMPCAPTURE) && (USE_HSP_ENGINE_TIMESTAMPCAPTURE == 1U)
/**
  * @brief  DMA Xfer Complete callback for Timestamp Capture.
  * @param  hdma  Pointer to a @ref hal_dma_handle_t.
  */
static void HSP_HW_IF_TSC_DMA_XferCpltCallback(hal_dma_handle_t *hdma)
{
  const hsp_hw_if_ctx_t *p_if_ctx;

  p_if_ctx = (const hsp_hw_if_ctx_t *)HAL_DMA_GetUserData(hdma);

  p_if_ctx->p_tsc_complete_cb(p_if_ctx->p_user_data);
}

/**
  * @brief  DMA Error callback for Timestamp Capture.
  * @param  hdma  Pointer to a @ref hal_dma_handle_t.
  */
static void HSP_HW_IF_TSC_DMA_ErrorCallback(hal_dma_handle_t *hdma)
{
  const hsp_hw_if_ctx_t *p_if_ctx;

  p_if_ctx = (const hsp_hw_if_ctx_t *)HAL_DMA_GetUserData(hdma);

  p_if_ctx->p_tsc_error_cb(p_if_ctx->p_user_data);
}
#endif /* USE_HSP_ENGINE_TIMESTAMPCAPTURE */

/**
  * @brief  Retrieve the HAL enum value of Event TRGIN source related to event ID and TRGIN ID.
  * @param  event_id  Event ID.
  * @param  trgin_id  TRGIN ID.
  * @param  enum_value Pointer to hal_hsp_event_source_t to be filled.
  * @retval 0 Success.
  * @retval 1 Error.
  */
static uint32_t HSP_HW_IF_Retrieve_TRGIN_HAL_Event_Source_Enum(uint32_t event_id, uint32_t trgin_id,
                                                               hal_hsp_event_source_t *enum_value)
{
  HSP_ASSERT_DBG_PARAM(enum_value != NULL);

  switch (event_id)
  {
    case 1U:
    {
      if (trgin_id == 3U) { *enum_value = HAL_HSP_EVENT_1_TRGIN3; }
      else if (trgin_id == 8U) { *enum_value = HAL_HSP_EVENT_1_TRGIN8; }
      else return 1U;
      break;
    }
    case 2U:
    {
      if (trgin_id == 4U) { *enum_value = HAL_HSP_EVENT_2_TRGIN4; }
      else if (trgin_id == 9U) { *enum_value = HAL_HSP_EVENT_2_TRGIN9; }
      else return 1U;
      break;
    }
    case 3U:
    {
      if (trgin_id == 0U) { *enum_value = HAL_HSP_EVENT_3_TRGIN0; }
      else if (trgin_id == 5U) { *enum_value = HAL_HSP_EVENT_3_TRGIN5; }
      else return 1U;
      break;
    }
    case 4U:
    {
      if (trgin_id == 1U) { *enum_value = HAL_HSP_EVENT_4_TRGIN1; }
      else if (trgin_id == 6U) { *enum_value = HAL_HSP_EVENT_4_TRGIN6; }
      else return 1U;
      break;
    }
    case 5U:
    {
      if (trgin_id == 2U) { *enum_value = HAL_HSP_EVENT_5_TRGIN2; }
      else if (trgin_id == 7U) { *enum_value = HAL_HSP_EVENT_5_TRGIN7; }
      else return 1U;
      break;
    }
    case 6U:
    {
      if (trgin_id == 3U) { *enum_value = HAL_HSP_EVENT_6_TRGIN3; }
      else if (trgin_id == 8U) { *enum_value = HAL_HSP_EVENT_6_TRGIN8; }
      else return 1U;
      break;
    }
    case 7U:
    {
      if (trgin_id == 4U) { *enum_value = HAL_HSP_EVENT_7_TRGIN4; }
      else if (trgin_id == 9U) { *enum_value = HAL_HSP_EVENT_7_TRGIN9; }
      else return 1U;
      break;
    }
    case 8U:
    {
      if (trgin_id == 0U) { *enum_value = HAL_HSP_EVENT_8_TRGIN0; }
      else if (trgin_id == 5U) { *enum_value = HAL_HSP_EVENT_8_TRGIN5; }
      else return 1U;
      break;
    }
    case 9U:
    {
      if (trgin_id == 1U) { *enum_value = HAL_HSP_EVENT_9_TRGIN1; }
      else if (trgin_id == 6U) { *enum_value = HAL_HSP_EVENT_9_TRGIN6; }
      else return 1U;
      break;
    }
    case 10U:
    {
      if (trgin_id == 2U) { *enum_value = HAL_HSP_EVENT_10_TRGIN2; }
      else if (trgin_id == 7U) { *enum_value = HAL_HSP_EVENT_10_TRGIN7; }
      else return 1U;
      break;
    }
    case 11U:
    {
      if (trgin_id == 3U) { *enum_value = HAL_HSP_EVENT_11_TRGIN3; }
      else if (trgin_id == 8U) { *enum_value = HAL_HSP_EVENT_11_TRGIN8; }
      else return 1U;
      break;
    }
    case 12U:
    {
      if (trgin_id == 4U) { *enum_value = HAL_HSP_EVENT_12_TRGIN4; }
      else if (trgin_id == 9U) { *enum_value = HAL_HSP_EVENT_12_TRGIN9; }
      else return 1U;
      break;
    }
    case 13U:
    {
      if (trgin_id == 0U) { *enum_value = HAL_HSP_EVENT_13_TRGIN0; }
      else if (trgin_id == 5U) { *enum_value = HAL_HSP_EVENT_13_TRGIN5; }
      else return 1U;
      break;
    }
    case 14U:
    {
      if (trgin_id == 1U) { *enum_value = HAL_HSP_EVENT_14_TRGIN1; }
      else if (trgin_id == 6U) { *enum_value = HAL_HSP_EVENT_14_TRGIN6; }
      else return 1U;
      break;
    }
    case 15U:
    {
      if (trgin_id == 2U) { *enum_value = HAL_HSP_EVENT_15_TRGIN2; }
      else if (trgin_id == 7U) { *enum_value = HAL_HSP_EVENT_15_TRGIN7; }
      else return 1U;
      break;
    }
    case 16U:
    {
      if (trgin_id == 3U) { *enum_value = HAL_HSP_EVENT_16_TRGIN3; }
      else if (trgin_id == 8U) { *enum_value = HAL_HSP_EVENT_16_TRGIN8; }
      else return 1U;
      break;
    }
    case 17U:
    {
      if (trgin_id == 4U) { *enum_value = HAL_HSP_EVENT_17_TRGIN4; }
      else if (trgin_id == 9U) { *enum_value = HAL_HSP_EVENT_17_TRGIN9; }
      else return 1U;
      break;
    }
    case 18U:
    {
      if (trgin_id == 0U) { *enum_value = HAL_HSP_EVENT_18_TRGIN0; }
      else if (trgin_id == 5U) { *enum_value = HAL_HSP_EVENT_18_TRGIN5; }
      else return 1U;
      break;
    }
    case 19U:
    {
      if (trgin_id == 1U) { *enum_value = HAL_HSP_EVENT_19_TRGIN1; }
      else if (trgin_id == 6U) { *enum_value = HAL_HSP_EVENT_19_TRGIN6; }
      else return 1U;
      break;
    }
    case 20U:
    {
      if (trgin_id == 2U) { *enum_value = HAL_HSP_EVENT_20_TRGIN2; }
      else if (trgin_id == 7U) { *enum_value = HAL_HSP_EVENT_20_TRGIN7; }
      else return 1U;
      break;
    }
    case 21U:
    {
      if (trgin_id == 3U) { *enum_value = HAL_HSP_EVENT_21_TRGIN3; }
      else if (trgin_id == 8U) { *enum_value = HAL_HSP_EVENT_21_TRGIN8; }
      else return 1U;
      break;
    }
    case 22U:
    {
      if (trgin_id == 4U) { *enum_value = HAL_HSP_EVENT_22_TRGIN4; }
      else if (trgin_id == 9U) { *enum_value = HAL_HSP_EVENT_22_TRGIN9; }
      else return 1U;
      break;
    }
    default:
      return 1U;
  }

  return 0U;
}

#if defined(USE_HSP_ENGINE_STREAM_BUFFER) && (USE_HSP_ENGINE_STREAM_BUFFER == 1U)
/**
  * @brief  Retrieve the HAL STREAM Buffer enum value from the HSP PRC Event identifier.
  * @param  event_id  Event Identifier in range [1..22].
  * @param  enum_value Pointer to hal_hsp_event_source_t to be filled.
  * @note  The Processing List identifier has the same value than the HSP PRC Event identifier
  *        if attached to a STREAM Buffer
  * @retval 0 Success.
  * @retval 1 Error.
  */
static hal_hsp_stream_buffer_t HSP_HW_IF_RetrieveSTREAMBufferFromEventID(uint32_t evt_id)
{
  return (hal_hsp_stream_buffer_t)((evt_id - 1U) % 4U);
}
#endif /* USE_HSP_ENGINE_STREAM_BUFFER */

#if defined(USE_HSP_ENGINE_TIMESTAMPCAPTURE) && (USE_HSP_ENGINE_TIMESTAMPCAPTURE == 1U)
/**
  * @brief Configure the TRGO output for TimeStamp Capture based on DMA configuration.
  * @param  p_if_ctx  Pointer to the interface context.
  * @retval HSP_IF_OK     Action complete successfully
  * @retval HSP_IF_ERROR  Action failed
  */
static hsp_if_status_t HSP_HW_IF_TSC_SetTRGOConfigFromDMA(const hsp_hw_if_ctx_t *p_if_ctx)
{
  hal_hsp_handle_t *hhsp;
  hal_dma_handle_t *hhdma;
  hal_dma_trigger_config_t dma_trigger_cfg;
  hal_hsp_trgo_config_t trgo_cfg;

  hhsp = (hal_hsp_handle_t *)(p_if_ctx->hdriver);
  hhdma = (hal_dma_handle_t *)(p_if_ctx->hdma_tsc);

  if (hhdma == NULL)
  {
    return HSP_IF_ERROR;
  }

  /* Get the DMA configuration to retrieve the TRGO Trigger Source */
  HAL_DMA_GetConfigDirectXferTrigger(hhdma, &dma_trigger_cfg);
#if 0
  if (IS_DMA_HSP_TRGO_0_TRIGGER_SOURCE(dma_trigger_cfg.source))
  {
    trgo_cfg.trigger_id = (hal_hsp_trgo_trigger_t)HSP_HW_IF_TRGO_0;
  }
  else if (IS_DMA_HSP_TRGO_1_TRIGGER_SOURCE(dma_trigger_cfg.source))
  {
    trgo_cfg.trigger_id = (hal_hsp_trgo_trigger_t)HSP_HW_IF_TRGO_1;
  }
  else if (IS_DMA_HSP_TRGO_2_TRIGGER_SOURCE(dma_trigger_cfg.source))
  {
    trgo_cfg.trigger_id = (hal_hsp_trgo_trigger_t)HSP_HW_IF_TRGO_2;
  }
  else if (IS_DMA_HSP_TRGO_3_TRIGGER_SOURCE(dma_trigger_cfg.source))
  {
    trgo_cfg.trigger_id = (hal_hsp_trgo_trigger_t)HSP_HW_IF_TRGO_3;
  }
  else
  {
    return HSP_IF_ERROR;
  }

  trgo_cfg.source = HAL_HSP_TRGO_SRC_TIMESTAMPCAPTURE;
  if (HAL_HSP_TRGO_SetMultiConfig(hhsp, &trgo_cfg, 1U) != HAL_OK)
  {
    return HSP_IF_ERROR;
  }

  if (HAL_DMA_RegisterXferCpltCallback(hhdma, HSP_HW_IF_TSC_DMA_XferCpltCallback) != HAL_OK)
  {
    return HSP_IF_ERROR;
  }

  if (HAL_DMA_RegisterXferErrorCallback(hhdma, HSP_HW_IF_TSC_DMA_ErrorCallback) != HAL_OK)
  {
    return HSP_IF_ERROR;
  }

  /* Link the Interface context to the HAL DMA Driver to allow any HSP_HW_IF_TSC_DMA callbacks to retrieve it
     and call the HSP Engine applicative callbacks with the correct hsp_engine_ctx_t structure */
  HAL_DMA_SetUserData(hhdma, (void *)p_if_ctx);

  return HSP_IF_OK;
#endif /* 0 */
  return HSP_IF_ERROR;
}
#endif /* USE_HSP_ENGINE_TIMESTAMPCAPTURE */

#if defined(USE_HAL_HSP_ADCIN) && (USE_HAL_HSP_ADCIN == 1)
/**
  * @brief  Retrieve the HAL enum value of an Event ADCIN source.
  * @param  event_id    Event ID.
  * @param  adcin_id    ADCIN instance ID.
  * @param  enum_value  Pointer to hal_hsp_event_source_t to be filled.
  * @retval 0 Success.
  * @retval 1 Error.
  */
static uint32_t HSP_HW_IF_Retrieve_ADCIN_HAL_Event_Source_Enum(uint32_t event_id, uint32_t adcin_id,
                                                               hal_hsp_event_source_t *enum_value)
{
  HSP_ASSERT_DBG_PARAM(enum_value != NULL);

  switch (event_id)
  {
    case 1U:
    {
      if (adcin_id == 0U) { *enum_value = HAL_HSP_EVENT_1_ADC0; }
      else if (adcin_id == 4U) { *enum_value = HAL_HSP_EVENT_1_ADC4; }
      else { return 1U; }
      break;
    }
    case 2U:
    {
      if (adcin_id == 1U) { *enum_value = HAL_HSP_EVENT_2_ADC1; }
      else if (adcin_id == 5U) { *enum_value = HAL_HSP_EVENT_2_ADC5; }
      else { return 1U; }
      break;
    }
    case 3U:
    {
      if (adcin_id == 2U) { *enum_value = HAL_HSP_EVENT_3_ADC2; }
      else if (adcin_id == 6U) { *enum_value = HAL_HSP_EVENT_3_ADC6; }
      else { return 1U; }
      break;
    }
    case 4U:
    {
      if (adcin_id == 3U) { *enum_value = HAL_HSP_EVENT_4_ADC3; }
      else if (adcin_id == 7U) { *enum_value = HAL_HSP_EVENT_4_ADC7; }
      else { return 1U; }
      break;
    }
    case 5U:
    {
      if (adcin_id == 0U) { *enum_value = HAL_HSP_EVENT_5_ADC0; }
      else if (adcin_id == 4U) { *enum_value = HAL_HSP_EVENT_5_ADC4; }
      else { return 1U; }
      break;
    }
    case 6U:
    {
      if (adcin_id == 1U) { *enum_value = HAL_HSP_EVENT_6_ADC1; }
      else if (adcin_id == 5U) { *enum_value = HAL_HSP_EVENT_6_ADC5; }
      else { return 1U; }
      break;
    }
    case 7U:
    {
      if (adcin_id == 2U) { *enum_value = HAL_HSP_EVENT_7_ADC2; }
      else if (adcin_id == 6U) { *enum_value = HAL_HSP_EVENT_7_ADC6; }
      else { return 1U; }
      break;
    }
    case 8U:
    {
      if (adcin_id == 3U) { *enum_value = HAL_HSP_EVENT_8_ADC3; }
      else if (adcin_id == 7U) { *enum_value = HAL_HSP_EVENT_8_ADC7; }
      else { return 1U; }
      break;
    }
    case 9U:
    {
      if (adcin_id == 0U) { *enum_value = HAL_HSP_EVENT_9_ADC0; }
      else if (adcin_id == 4U) { *enum_value = HAL_HSP_EVENT_9_ADC4; }
      else { return 1U; }
      break;
    }
    case 10U:
    {
      if (adcin_id == 1U) { *enum_value = HAL_HSP_EVENT_10_ADC1; }
      else if (adcin_id == 5U) { *enum_value = HAL_HSP_EVENT_10_ADC5; }
      else { return 1U; }
      break;
    }
    case 11U:
    {
      if (adcin_id == 2U) { *enum_value = HAL_HSP_EVENT_11_ADC2; }
      else if (adcin_id == 6U) { *enum_value = HAL_HSP_EVENT_11_ADC6; }
      else { return 1U; }
      break;
    }
    case 12U:
    {
      if (adcin_id == 3U) { *enum_value = HAL_HSP_EVENT_12_ADC3; }
      else if (adcin_id == 7U) { *enum_value = HAL_HSP_EVENT_12_ADC7; }
      else { return 1U; }
      break;
    }
    case 13U:
    {
      if (adcin_id == 0U) { *enum_value = HAL_HSP_EVENT_13_ADC0; }
      else if (adcin_id == 4U) { *enum_value = HAL_HSP_EVENT_13_ADC4; }
      else { return 1U; }
      break;
    }
    case 14U:
    {
      if (adcin_id == 1U) { *enum_value = HAL_HSP_EVENT_14_ADC1; }
      else if (adcin_id == 5U) { *enum_value = HAL_HSP_EVENT_14_ADC5; }
      else { return 1U; }
      break;
    }
    case 15U:
    {
      if (adcin_id == 2U) { *enum_value = HAL_HSP_EVENT_15_ADC2; }
      else if (adcin_id == 6U) { *enum_value = HAL_HSP_EVENT_15_ADC6; }
      else { return 1U; }
      break;
    }
    case 16U:
    {
      if (adcin_id == 3U) { *enum_value = HAL_HSP_EVENT_16_ADC3; }
      else if (adcin_id == 7U) { *enum_value = HAL_HSP_EVENT_16_ADC7; }
      else { return 1U; }
      break;
    }
    case 17U:
    {
      if (adcin_id == 0U) { *enum_value = HAL_HSP_EVENT_17_ADC0; }
      else if (adcin_id == 4U) { *enum_value = HAL_HSP_EVENT_17_ADC4; }
      else { return 1U; }
      break;
    }
    case 18U:
    {
      if (adcin_id == 1U) { *enum_value = HAL_HSP_EVENT_18_ADC1; }
      else if (adcin_id == 5U) { *enum_value = HAL_HSP_EVENT_18_ADC5; }
      else { return 1U; }
      break;
    }
    case 19U:
    {
      if (adcin_id == 2U) { *enum_value = HAL_HSP_EVENT_19_ADC2; }
      else if (adcin_id == 6U) { *enum_value = HAL_HSP_EVENT_19_ADC6; }
      else { return 1U; }
      break;
    }
    case 20U:
    {
      if (adcin_id == 3U) { *enum_value = HAL_HSP_EVENT_20_ADC3; }
      else if (adcin_id == 7U) { *enum_value = HAL_HSP_EVENT_20_ADC7; }
      else { return 1U; }
      break;
    }
    case 21U:
    {
      if (adcin_id == 0U) { *enum_value = HAL_HSP_EVENT_21_ADC0; }
      else if (adcin_id == 4U) { *enum_value = HAL_HSP_EVENT_21_ADC4; }
      else { return 1U; }
      break;
    }
    case 22U:
    {
      if (adcin_id == 1U) { *enum_value = HAL_HSP_EVENT_22_ADC1; }
      else if (adcin_id == 5U) { *enum_value = HAL_HSP_EVENT_22_ADC5; }
      else { return 1U; }
      break;
    }
    default:
    {
      return 1U;
    }
  }

  return 0U;
}
#endif /* USE_HAL_HSP_ADCIN */

/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */
