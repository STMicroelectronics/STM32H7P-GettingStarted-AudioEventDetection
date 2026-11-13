/**
  ******************************************************************************
  * @file    hsp_hw_if.c
  * @author  GPM Application Team
  * @brief   This file implements the service provide by the HSP Hardware
  *          Interface
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
#include "hsp_conf.h"
#include "hsp_if_conf.h"
#include "hsp_fw_def_generic.h"


/** @addtogroup HSP_ENGINE
  * @{
  */

/** @addtogroup HSP_INTERFACES
  * @{
  */

/** @addtogroup HSP_HW_IF
  * @{
  */

/* Private types -----------------------------------------------------------*/
/** @defgroup HSP_HW_IF_Private_Types HSP_HW_IF Private Types
  * @{
  */

/**
  * @}
  */

/* Private constants ---------------------------------------------------------*/
/** @defgroup HSP_HW_IF_Private_Constants HSP_HW_IF Private Constants
  * @{
  */

#define HSP_HW_IF_EVENT_SOURCE_GET_ENUM_FOR_CSEG  HAL_HSP_EVENT_SOURCE_GET_ENUM_FOR_CSEG
/**
  * @}
  */

/* Private macros -------------------------------------------------------------*/
/** @defgroup HSP_HW_IF_Private_Macros HSP_HW_IF Private Macros
  * @{
  */
#define POSITION_FIRST_ZERO(VAL) (__CLZ(__RBIT(~(VAL))))
#if defined(HAL_HSP_SMARTCLOCKING_HSPDMA)
#define HSP_HW_IF_GET_CLOCK(clock_id)                                               \
  (((clock_id) == HSP_HW_IF_SMARTCLOCKING_CTRL)?HAL_HSP_SMARTCLOCKING_CTRL:       \
   ((clock_id) == HSP_HW_IF_SMARTCLOCKING_SPE)?HAL_HSP_SMARTCLOCKING_SPE:         \
   ((clock_id) == HSP_HW_IF_SMARTCLOCKING_MMC)?HAL_HSP_SMARTCLOCKING_MMC: bb      \
   ((clock_id) == HSP_HW_IF_SMARTCLOCKING_HSPDMA)?HAL_HSP_SMARTCLOCKING_HSPDMA:0U)
#else
#define HSP_HW_IF_GET_CLOCK(clock_id)                                          \
  (((clock_id) == HSP_HW_IF_SMARTCLOCKING_CTRL)?HAL_HSP_SMARTCLOCKING_CTRL:  \
   ((clock_id) == HSP_HW_IF_SMARTCLOCKING_SPE)?HAL_HSP_SMARTCLOCKING_SPE:    \
   ((clock_id) == HSP_HW_IF_SMARTCLOCKING_MMC)?HAL_HSP_SMARTCLOCKING_MMC:0U)
#endif /* HAL_HSP_SMARTCLOCKING_HSPDMA */
/**
  * @}
  */

/* Private functions ---------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/

/* Exported functions --------------------------------------------------------*/
/** @addtogroup HSP_HW_IF_Exported_Functions
  * @{
  */

/**
  * @brief  Deinit the interface
  * @param  hdriver   HSP Driver handle.
  * @return None
  */
void HSP_HW_IF_DeInit(void *hdriver)
{
  /* User code */
}

/**
  * @brief  Load a Firmware OpCode & data respectively in CRAM & DRAM
  * @param  hdriver   HSP Driver handle.
  * @param  p_fw      Pointer to Firmware structure
  * @return HSP_IF_OK     Load complete successfully
  * @return HSP_IF_ERROR  Load failed
  */
hsp_if_status_t HSP_HW_IF_LoadFW(void *hdriver, const hsp_hw_if_firmware_t *p_fw)
{
  /* User code */
}

/**
  * @brief  Load a Plugin in CRAM.
  * @param  hdriver    HSP Driver handle.
  * @param  p_bin      Pointer to the Plugin data.
  * @param  size_word  Size in word of Plugin data.
  * @return HSP_IF_OK     Load complete successfully
  * @return HSP_IF_ERROR  Load failed
  */
hsp_if_status_t HSP_HW_IF_LoadPlugin(void *hdriver, const uint32_t *p_bin, uint32_t size_word)
{
  /* User code */
}

/**
  * @brief Boot the HSP.
  * @param  hdriver           HSP Driver handle.
  * @param  enableCycleCount  Enable cycle count on HSP side
  * @return HSP_IF_OK     Boot complete successfully
  * @return HSP_IF_ERROR  Boot failed
  */
hsp_if_status_t HSP_HW_IF_Boot(void *hdriver, uint32_t enableCycleCount)
{
  /* User code */
}

/* API to manage the SmartClocking -------------------------------------------*/
/**
  * @brief Enable SmartClocking capabilities of HSP blocks.
  * @param  hdriver   HSP Driver handle.
  * @param clock_id   Clock ID
  * @return HSP_IF_OK     Action complete successfully
  * @return HSP_IF_ERROR  Action failed
  */
hsp_if_status_t HSP_HW_IF_EnableSmartClocking(void *hdriver, uint32_t clock_id)
{
  /* User code */
}

/**
  * @brief Disable SmartClocking capabilities of HSP blocks.
  * @param  hdriver   HSP Driver handle.
  * @param  clock_id  Clock ID
  * @return HSP_IF_OK     Action complete successfully
  * @return HSP_IF_ERROR  Action failed
  */
hsp_if_status_t HSP_HW_IF_DisableSmartClocking(void *hdriver, uint32_t clock_id)
{
  /* User code */
}

/* API to configure STI AP Port  ---------------------------------------------*/
hsp_if_status_t HSP_HW_IF_STI_SetPortAddress(void *hdriver, uint32_t port_id, uint32_t block_address)
{
  /* User code */
}

/* API to manage OUTPUT ------------------------------------------------------*/
/**
  * @brief Configure the source of a TRGO output.
  * @param  hdriver   HSP Driver handle.
  * @param  trgo_id   TRGO output ID.
  * @param  source    Source value.
  * @return HSP_IF_OK     Action complete successfully
  * @return HSP_IF_ERROR  Action failed
  */
hsp_if_status_t HSP_HW_IF_OUTPUT_SetConfig(void *hdriver, hsp_hw_if_output_trigger_t trgo_id, uint32_t source)
{
  /* User code */
}

/**
  * @brief Enable GPO & TRGO outputs.
  * @param  hdriver   HSP Driver handle.
  * @return HSP_IF_OK     Action complete successfully
  * @return HSP_IF_ERROR  Action failed
  */
hsp_if_status_t HSP_HW_IF_OUTPUT_Enable(void *hdriver)
{
  /* User code */
}

/**
  * @brief Enable GPO & TRGO outputs.
  * @param  hdriver   HSP Driver handle.
  * @return HSP_IF_OK     Action complete successfully
  * @return HSP_IF_ERROR  Action failed
  */
hsp_if_status_t HSP_HW_IF_OUTPUT_Disable(void *hdriver)
{
  /* User code */
}

/**
  * @brief Return the enabling status of HSP Outputs
  * @param  hdriver   HSP Driver handle.
  * @return IF_ACTIVATION_DISABLED  HSP Outputs are disabled
  * @return IF_ACTIVATION_ENABLED   HSP Outputs are enabled
  */
if_activation_status_t HSP_HW_IF_OUTPUT_IsEnabled(void *hdriver)
{
  /* User code */
}

/* API to manage Direct Command ----------------------------------------------*/
/**
  * @brief Send a command with MsgBox Interface.
  * @param  hdriver     HSP Driver handle.
  * @param  command_id  Command ID.
  * @return HSP_IF_OK     Action complete successfully
  * @return HSP_IF_ERROR  Action failed
  */
hsp_if_status_t HSP_HW_IF_SendCommand(void *hdriver, uint32_t command_id)
{
  /* User code */
}

/* API to manage Processing List ---------------------------------------------*/
/**
  * @brief  Start the record of a Processing List
  * @param  hdriver  HSP Driver handle.
  * @param  pl_id    Processing List ID
  * @return HSP_IF_OK     Action complete successfully
  * @return HSP_IF_ERROR  Action failed
  */
hsp_if_status_t HSP_HW_IF_SEQ_StartRecord(void *hdriver, uint32_t pl_id)
{
  /* User code */
}

/**
  * @brief  Stop the record of the Processing List
  * @param  hdriver   HSP Driver handle.
  * @return HSP_IF_OK     Action complete successfully
  * @return HSP_IF_ERROR  Action failed
  */
hsp_if_status_t HSP_HW_IF_SEQ_StopRecord(void *hdriver)
{
  /* User code */
}

/**
  * @brief  Reset all Processing List
  * @retval HSP_IF_OK success
  *         HSP_IF_ERROR failure
  */
hsp_if_status_t HSP_HW_IF_SEQ_ResetPL(void *hdriver)
{
  /* User code */
}

hsp_if_status_t HSP_HW_IF_SEQ_RunTask(void *hdriver, uint32_t task_id, uint32_t timeout_ms)
{
  HSP_ASSERT_DBG_PARAM(hdriver != NULL);

  hal_hsp_handle_t *hhsp = (hal_hsp_handle_t *)(hdriver);

  if (HAL_HSP_TASK_Run(hhsp, (hal_hsp_task_t)task_id, timeout_ms) != HAL_OK)
  {
    return HSP_IF_ERROR;
  }

  return HSP_IF_OK;
}

/* API to manage Trigger & Event configuration -------------------------------*/
/**
  * @brief Configure an event with a STREAM Buffer as source.
  * @param  hdriver   HSP Driver handle.
  * @param  event_id  Event ID.
  * @param  p_config  Pointer to the config
  * @note  The enable of STREAM is not perform at the end of the configuration wotherwise it will be impossible
  *        to configure the next Stream Buffer.
  *        The application must do it after all STREAM Buffer configurations.
  * @return HSP_IF_OK     Action complete successfully
  * @return HSP_IF_ERROR  Action failed
  */
hsp_if_status_t HSP_HW_IF_EVENT_SetConfig_StreamBuffer(void *hdriver, uint32_t event_id,
                                                       const hsp_hw_if_stream_config_t *p_config)
{
  /* User code */
}

/**
  * @brief Configure an event with a TRGIN trigger as source.
  * @param  hdriver   HSP Driver handle.
  * @param  event_id  Event ID.
  * @param  p_config  Pointer to the config
  * @return HSP_IF_OK     Action complete successfully
  * @return HSP_IF_ERROR  Action failed
  */
hsp_if_status_t HSP_HW_IF_EVENT_SetConfig_Trigger(void *hdriver, uint32_t event_id,
                                                  const hsp_hw_if_trigger_config_t *p_config)
{
  /* User code */
}

/**
  * @brief Configure an event with the CSEG interface as source.
  * @param  hdriver   HSP Driver handle.
  * @param  event_id  Event ID.
  * @param  p_sync    Pointer to the Event Synchronization config
  * @return HSP_IF_OK     Action complete successfully
  * @return HSP_IF_ERROR  Action failed
  */
hsp_if_status_t HSP_HW_IF_EVENT_SetConfig_CSEG(void *hdriver, uint32_t event_id, const hsp_hw_if_event_sync_t *p_sync)
{
  /* User code */
}

/**
  * @brief Configure an event with the HSEG interface as source.
  * @param  hdriver   HSP Driver handle.
  * @param  event_id  Event ID.
  * @param  p_sync    Pointer to the Event Synchronization config
  * @return HSP_IF_OK     Action complete successfully
  * @return HSP_IF_ERROR  Action failed
  */
hsp_if_status_t HSP_HW_IF_EVENT_SetConfig_SPE(void *hdriver, uint32_t event_id, const hsp_hw_if_event_sync_t *p_sync)
{
  /* User code */
}

hsp_if_status_t HSP_HW_IF_EVENT_Enable(void *hdriver, uint32_t events_mask)
{
  /* User code */
}

hsp_if_status_t HSP_HW_IF_EVENT_Disable(void *hdriver, uint32_t events_mask)
{
  /* User code */
}

hsp_if_status_t HSP_HW_IF_SEQ_EVENT_Trig_CSEG(void *hdriver, uint32_t events)
{
  /* User code */
}


/* API to BRAM Access control ------------------------------------------------*/
hsp_if_status_t HSP_HW_IF_BRAM_EnableConflictAccessCounter(void *hdriver)
{
  /* User code */

  return HSP_IF_OK;
}

hsp_if_status_t HSP_HW_IF_BRAM_DisableConflictAccessCounter(void *hdriver)
{
  /* User code */

  return HSP_IF_OK;
}

uint32_t HSP_HW_IF_BRAM_GetConflictAccessCounter(void *hdriver)
{
  /* User code */
}

hsp_if_status_t HSP_HW_IF_BRAM_SetBandwidthArbitration(void *hdriver, uint32_t mode)
{
  /* User code */

  return HSP_IF_OK;
}

uint32_t HSP_HW_IF_BRAM_GetBandwidthArbitration(void *hdriver)
{
  /* User code */
}

/* API for secure Access -----------------------------------------------------*/
hsp_if_status_t HSP_HW_IF_Lock(void *hdriver)
{
  /* User code */

  return HSP_IF_OK;
}


/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */
