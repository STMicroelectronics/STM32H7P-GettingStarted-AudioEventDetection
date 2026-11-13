/**
  ******************************************************************************
  * @file    hsp_hw_if.h
  * @brief   Header file for hsp_hw_if.c.
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

#ifndef HSP_HW_IF_H
#define HSP_HW_IF_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* Includes ------------------------------------------------------------------*/
#include "hsp_conf.h"
#include "hsp_engine_rsrc_map.h"
#include "hsp_engine_assert.h"

/** @addtogroup HSP_ENGINE
  * @{
  */

/** @defgroup HSP_INTERFACES HSP Interfaces
  * @{
  */

/** @defgroup HSP_HW_IF HSP Hardware Interface
  * @{
  */

/* Exported constants --------------------------------------------------------*/
/** @defgroup HSP_HW_IF_Exported_Constants HSP_HW_IF Exported Constants
  * @{
  */
#define HSP_HW_IF_ERROR_MINOR  HAL_HSP_HW_ERROR_MINOR /*!< HSP HW minor error category */
#define HSP_HW_IF_ERROR_FAULT  HAL_HSP_HW_ERROR_FAULT  /*!< HSP HW fault error category */

#define HSP_HW_IF_ERROR_INFO_SLAVE_AHB_ACCESS     HAL_HSP_SPE_ERROR_INFO_SLAVE_AHB_ACCESS     /*!< Signal Processor Engine Slave AHB Access error                                */
#define HSP_HW_IF_ERROR_INFO_INTERNAL_AHB_ACCESS  HAL_HSP_SPE_ERROR_INFO_INTERNAL_AHB_ACCESS  /*!< Signal Processor Engine AHB Access error to HSP_CTRL                          */
#define HSP_HW_IF_ERROR_INFO_DATA_MEM_ACCESS      HAL_HSP_SPE_ERROR_INFO_DATA_MEM_ACCESS      /*!< Signal Processor Engine Data Memory Access error                              */
#define HSP_HW_IF_ERROR_INFO_CODE_MEM_ACCESS      HAL_HSP_SPE_ERROR_INFO_CODE_MEM_ACCESS      /*!< Signal Processor Engine Code Memory Access error                              */

#define HSP_HW_IF_ERROR_INFO_FPU_INEXACT   HAL_HSP_SPE_ERROR_INFO_FPU_INEXACT  /*!< Floating Point Unit Inexact Exception       */
#define HSP_HW_IF_ERROR_INFO_FPU_UDF       HAL_HSP_SPE_ERROR_INFO_FPU_UDF      /*!< Floating Point Unit Underflow error         */
#define HSP_HW_IF_ERROR_INFO_FPU_OVF       HAL_HSP_SPE_ERROR_INFO_FPU_OVF      /*!< Floating Point Unit Overflow error          */
#define HSP_HW_IF_ERROR_INFO_FPU_DIVZERO   HAL_HSP_SPE_ERROR_INFO_FPU_DIVZERO  /*!< Floating Point Unit Division By Zero error  */
#define HSP_HW_IF_ERROR_INFO_FPU_INVALID   HAL_HSP_SPE_ERROR_INFO_FPU_INVALID  /*!< Floating Point Unit Invalid Exception error */
#define HSP_HW_IF_ERROR_INFO_FPU_DENORMAL  HAL_HSP_SPE_ERROR_INFO_FPU_DENORMAL /*!< Floating Point Unit Denormal error          */

#define  HSP_HW_IF_SEQ_EVENT_SYNC_DISABLED  0xFFU

#define HSP_HW_IF_WRITE_PARAMR(hmw, param_id, val)  (*((hmw)->p_send_parameter_data + (uint32_t)(param_id)) = (val))
#define HSP_HW_IF_WRITE_DCMD_DATA_PTR(hmw, ptr_id, val)  (*((hmw)->p_send_dcmd_data_ptr + (uint32_t)(ptr_id)) = (val))

#define HSP_HW_IF_PARAM0   ((uint32_t)HAL_HSP_PARAM_0)
#define HSP_HW_IF_PARAM1   ((uint32_t)HAL_HSP_PARAM_1)
#define HSP_HW_IF_PARAM2   ((uint32_t)HAL_HSP_PARAM_2)
#define HSP_HW_IF_PARAM3   ((uint32_t)HAL_HSP_PARAM_3)
#define HSP_HW_IF_PARAM4   ((uint32_t)HAL_HSP_PARAM_4)
#define HSP_HW_IF_PARAM5   ((uint32_t)HAL_HSP_PARAM_5)
#define HSP_HW_IF_PARAM6   ((uint32_t)HAL_HSP_PARAM_6)
#define HSP_HW_IF_PARAM7   ((uint32_t)HAL_HSP_PARAM_7)
#define HSP_HW_IF_PARAM8   ((uint32_t)HAL_HSP_PARAM_8)
#define HSP_HW_IF_PARAM9   ((uint32_t)HAL_HSP_PARAM_9)
#define HSP_HW_IF_PARAM10  ((uint32_t)HAL_HSP_PARAM_10)
#define HSP_HW_IF_PARAM11  ((uint32_t)HAL_HSP_PARAM_11)
#define HSP_HW_IF_PARAM12  ((uint32_t)HAL_HSP_PARAM_12)
#define HSP_HW_IF_PARAM13  ((uint32_t)HAL_HSP_PARAM_13)
#define HSP_HW_IF_PARAM14  ((uint32_t)HAL_HSP_PARAM_14)
#define HSP_HW_IF_PARAM15  ((uint32_t)HAL_HSP_PARAM_15)

#define HSP_HW_IF_WRITE_PARAMR0(hmw, val)   HSP_HW_IF_WRITE_PARAMR((hmw), 0U, (val))
#define HSP_HW_IF_WRITE_PARAMR1(hmw, val)   HSP_HW_IF_WRITE_PARAMR((hmw), 1U, (val))
#define HSP_HW_IF_WRITE_PARAMR2(hmw, val)   HSP_HW_IF_WRITE_PARAMR((hmw), 2U, (val))
#define HSP_HW_IF_WRITE_PARAMR3(hmw, val)   HSP_HW_IF_WRITE_PARAMR((hmw), 3U, (val))
#define HSP_HW_IF_WRITE_PARAMR4(hmw, val)   HSP_HW_IF_WRITE_PARAMR((hmw), 4U, (val))
#define HSP_HW_IF_WRITE_PARAMR5(hmw, val)   HSP_HW_IF_WRITE_PARAMR((hmw), 5U, (val))
#define HSP_HW_IF_WRITE_PARAMR6(hmw, val)   HSP_HW_IF_WRITE_PARAMR((hmw), 6U, (val))
#define HSP_HW_IF_WRITE_PARAMR7(hmw, val)   HSP_HW_IF_WRITE_PARAMR((hmw), 7U, (val))
#define HSP_HW_IF_WRITE_PARAMR8(hmw, val)   HSP_HW_IF_WRITE_PARAMR((hmw), 8U, (val))
#define HSP_HW_IF_WRITE_PARAMR9(hmw, val)   HSP_HW_IF_WRITE_PARAMR((hmw), 9U, (val))
#define HSP_HW_IF_WRITE_PARAMR10(hmw, val)  HSP_HW_IF_WRITE_PARAMR((hmw), 10U, (val))
#define HSP_HW_IF_WRITE_PARAMR11(hmw, val)  HSP_HW_IF_WRITE_PARAMR((hmw), 11U, (val))
#define HSP_HW_IF_WRITE_PARAMR12(hmw, val)  HSP_HW_IF_WRITE_PARAMR((hmw), 12U, (val))
#define HSP_HW_IF_WRITE_PARAMR13(hmw, val)  HSP_HW_IF_WRITE_PARAMR((hmw), 13U, (val))
#define HSP_HW_IF_WRITE_PARAMR14(hmw, val)  HSP_HW_IF_WRITE_PARAMR((hmw), 14U, (val))
#define HSP_HW_IF_WRITE_PARAMR15(hmw, val)  HSP_HW_IF_WRITE_PARAMR((hmw), 15U, (val))

#define HSP_HW_IF_WRITE_DCMDPTR0(hmw, val)  HSP_HW_IF_WRITE_DCMD_DATA_PTR((hmw), 0U, (val))
#define HSP_HW_IF_WRITE_DCMDPTR1(hmw, val)  HSP_HW_IF_WRITE_DCMD_DATA_PTR((hmw), 1U, (val))
#define HSP_HW_IF_WRITE_DCMDPTR2(hmw, val)  HSP_HW_IF_WRITE_DCMD_DATA_PTR((hmw), 2U, (val))

#define HSP_HW_IF_WRITE_DCMDIDR(hmw, val)  ((*(hmw)->p_send_dcmdid) = (val))

#define HSP_HW_IF_READ_PARAMR0()  (*((volatile uint32_t *)HAL_HSP1_PARAMR0_ADDRESS))
#define HSP_HW_IF_READ_PARAMR1()  (*((volatile uint32_t *)HAL_HSP1_PARAMR1_ADDRESS))
#define HSP_HW_IF_READ_PARAMR2()  (*((volatile uint32_t *)HAL_HSP1_PARAMR2_ADDRESS))
#define HSP_HW_IF_READ_PARAMR3()  (*((volatile uint32_t *)HAL_HSP1_PARAMR3_ADDRESS))
#define HSP_HW_IF_READ_PARAMR4()  (*((volatile uint32_t *)HAL_HSP1_PARAMR4_ADDRESS))
#define HSP_HW_IF_READ_PARAMR5()  (*((volatile uint32_t *)HAL_HSP1_PARAMR5_ADDRESS))
#define HSP_HW_IF_READ_PARAMR6()  (*((volatile uint32_t *)HAL_HSP1_PARAMR6_ADDRESS))
#define HSP_HW_IF_READ_PARAMR7()  (*((volatile uint32_t *)HAL_HSP1_PARAMR7_ADDRESS))
#define HSP_HW_IF_READ_PARAMR8()  (*((volatile uint32_t *)HAL_HSP1_PARAMR8_ADDRESS))
#define HSP_HW_IF_READ_PARAMR9()  (*((volatile uint32_t *)HAL_HSP1_PARAMR9_ADDRESS))
#define HSP_HW_IF_READ_PARAMR10() (*((volatile uint32_t *)HAL_HSP1_PARAMR10_ADDRESS))
#define HSP_HW_IF_READ_PARAMR11() (*((volatile uint32_t *)HAL_HSP1_PARAMR11_ADDRESS))
#define HSP_HW_IF_READ_PARAMR12() (*((volatile uint32_t *)HAL_HSP1_PARAMR12_ADDRESS))
#define HSP_HW_IF_READ_PARAMR13() (*((volatile uint32_t *)HAL_HSP1_PARAMR13_ADDRESS))
#define HSP_HW_IF_READ_PARAMR14() (*((volatile uint32_t *)HAL_HSP1_PARAMR14_ADDRESS))
#define HSP_HW_IF_READ_PARAMR15() (*((volatile uint32_t *)HAL_HSP1_PARAMR15_ADDRESS))

#define HSP_HW_IF_SMARTCLOCKING_CTRL    ((uint32_t)(HAL_HSP_SMARTCLOCKING_CTRL))
#define HSP_HW_IF_SMARTCLOCKING_SPE     ((uint32_t)(HAL_HSP_SMARTCLOCKING_SPE))
#define HSP_HW_IF_SMARTCLOCKING_MMC     ((uint32_t)(HAL_HSP_SMARTCLOCKING_MMC))
#ifdef __HSP_DMA__
#define HSP_HW_IF_SMARTCLOCKING_HSPDMA  ((uint32_t)(HAL_HSP_SMARTCLOCKING_STI))
#endif /* __HSP_DMA__ */

#define HSP_HW_IF_LOG2NBP_32    (5U)  /*!< Value of Log2(32) for FFT 32 points     */
#define HSP_HW_IF_LOG2NBP_64    (6U)  /*!< Value of Log2(64) for FFT 64 points     */
#define HSP_HW_IF_LOG2NBP_128   (7U)  /*!< Value of Log2(128) for FFT 128 points   */
#define HSP_HW_IF_LOG2NBP_256   (8U)  /*!< Value of Log2(256) for FFT 256 points   */
#define HSP_HW_IF_LOG2NBP_512   (9U)  /*!< Value of Log2(512) for FFT 512 points   */
#define HSP_HW_IF_LOG2NBP_1024  (10U) /*!< Value of Log2(1024) for FFT 1024 points */
#define HSP_HW_IF_LOG2NBP_2048  (11U) /*!< Value of Log2(2048) for FFT 2048 points */
#define HSP_HW_IF_LOG2NBP_4096  (12U) /*!< Value of Log2(4096) for FFT 4096 points */

#define HSP_HW_IF_SEQ_EVENT_SYNC_DISABLE  HAL_HSP_EVENT_SYNC_DISABLE
#define HSP_HW_IF_SEQ_EVENT_SYNC_ENABLE  HAL_HSP_EVENT_SYNC_ENABLE

/** @defgroup HSP_MSGBOX_Constants HSP Message Box Constants
  * @{
  */
#define HSP_HW_IF_MSGBOX_NO_MSG         (HAL_HSP_MSGBOX_NO_MSG)         /*!< No message in the mailbox. */
#define HSP_HW_IF_MSGBOX_MSG_AVAILABLE  (HAL_HSP_MSGBOX_MSG_AVAILABLE)  /*!< Message available in the mailbox. */

/**
  * @}
  */

/** @defgroup HSP_STREAM_Buffer_Constants HSP STREAM Buffer Constants
  * @{
  */
#define HSP_HW_IF_STREAM_BUFFER_0  (HAL_HSP_STREAM_BUFFER_0)
#define HSP_HW_IF_STREAM_BUFFER_1  (HAL_HSP_STREAM_BUFFER_1)
#define HSP_HW_IF_STREAM_BUFFER_2  (HAL_HSP_STREAM_BUFFER_2)
#define HSP_HW_IF_STREAM_BUFFER_3  (HAL_HSP_STREAM_BUFFER_3)

#define HSP_HW_IF_STREAM_BUFFER_SYNC_DISABLE  (HAL_HSP_STREAM_SYNC_DISABLE)
#define HSP_HW_IF_STREAM_BUFFER_SYNC_ENABLE   (HAL_HSP_STREAM_SYNC_ENABLE)

/**
  * @}
  */

/** @defgroup HSP_ADCIN_Constants HSP ADCIN interface Constants
  * @{
  */
#define HSP_HW_IF_ADCIN_FILTER_CHANNEL_0  (HAL_HSP_ADCIN_FILTER_CHANNEL_0)
#define HSP_HW_IF_ADCIN_FILTER_CHANNEL_1  (HAL_HSP_ADCIN_FILTER_CHANNEL_1)
#define HSP_HW_IF_ADCIN_FILTER_CHANNEL_2  (HAL_HSP_ADCIN_FILTER_CHANNEL_2)
#define HSP_HW_IF_ADCIN_FILTER_CHANNEL_3  (HAL_HSP_ADCIN_FILTER_CHANNEL_3)
#define HSP_HW_IF_ADCIN_FILTER_CHANNEL_4  (HAL_HSP_ADCIN_FILTER_CHANNEL_4)
#define HSP_HW_IF_ADCIN_FILTER_CHANNEL_5  (HAL_HSP_ADCIN_FILTER_CHANNEL_5)
#define HSP_HW_IF_ADCIN_FILTER_CHANNEL_6  (HAL_HSP_ADCIN_FILTER_CHANNEL_6)
#define HSP_HW_IF_ADCIN_FILTER_CHANNEL_7  (HAL_HSP_ADCIN_FILTER_CHANNEL_7)
#define HSP_HW_IF_ADCIN_FILTER_CHANNEL_8  (HAL_HSP_ADCIN_FILTER_CHANNEL_8)
#define HSP_HW_IF_ADCIN_FILTER_CHANNEL_9  (HAL_HSP_ADCIN_FILTER_CHANNEL_9)
#define HSP_HW_IF_ADCIN_FILTER_CHANNEL_10 (HAL_HSP_ADCIN_FILTER_CHANNEL_10)
#define HSP_HW_IF_ADCIN_FILTER_CHANNEL_11 (HAL_HSP_ADCIN_FILTER_CHANNEL_11)
#define HSP_HW_IF_ADCIN_FILTER_CHANNEL_12 (HAL_HSP_ADCIN_FILTER_CHANNEL_12)
#define HSP_HW_IF_ADCIN_FILTER_CHANNEL_13 (HAL_HSP_ADCIN_FILTER_CHANNEL_13)
#define HSP_HW_IF_ADCIN_FILTER_CHANNEL_14 (HAL_HSP_ADCIN_FILTER_CHANNEL_14)
#define HSP_HW_IF_ADCIN_FILTER_CHANNEL_15  (HAL_HSP_ADCIN_FILTER_CHANNEL_15)
#define HSP_HW_IF_ADCIN_FILTER_CHANNEL_NONE  (HAL_HSP_ADCIN_FILTER_CHANNEL_NONE)

/**
  * @}
  */


/** @defgroup HSP_PRC_EVENT_Constants HSP Priority Encoder Event Constants
  * @{
  */
#define HSP_HW_IF_PRC_EVENT_1   (1U)
#define HSP_HW_IF_PRC_EVENT_2   (2U)
#define HSP_HW_IF_PRC_EVENT_3   (3U)
#define HSP_HW_IF_PRC_EVENT_4   (4U)
#define HSP_HW_IF_PRC_EVENT_5   (5U)
#define HSP_HW_IF_PRC_EVENT_6   (6U)
#define HSP_HW_IF_PRC_EVENT_7   (7U)
#define HSP_HW_IF_PRC_EVENT_8   (8U)
#define HSP_HW_IF_PRC_EVENT_9   (9U)
#define HSP_HW_IF_PRC_EVENT_10  (10U)
#define HSP_HW_IF_PRC_EVENT_11  (11U)
#define HSP_HW_IF_PRC_EVENT_12  (12U)
#define HSP_HW_IF_PRC_EVENT_13  (13U)
#define HSP_HW_IF_PRC_EVENT_14  (14U)
#define HSP_HW_IF_PRC_EVENT_15  (15U)
#define HSP_HW_IF_PRC_EVENT_16  (16U)
#define HSP_HW_IF_PRC_EVENT_17  (17U)
#define HSP_HW_IF_PRC_EVENT_18  (18U)
#define HSP_HW_IF_PRC_EVENT_19  (19U)
#define HSP_HW_IF_PRC_EVENT_20  (20U)
#define HSP_HW_IF_PRC_EVENT_21  (21U)
#define HSP_HW_IF_PRC_EVENT_22  (22U)

/**
  * @}
  */

/** @defgroup HSP_BRAM_LATENCY_Constants HSP BRAM Latency Constants
  * @{
  */
#define HSP_HW_IF_BRAM_ARBITRATION_LATENCY_16_CYCLES ((uint32_t)HAL_HSP_BRAM_LATENCY_16_CYCLES)
#define HSP_HW_IF_BRAM_ARBITRATION_LATENCY_8_CYCLES  ((uint32_t)HAL_HSP_BRAM_LATENCY_8_CYCLES)
#define HSP_HW_IF_BRAM_ARBITRATION_LATENCY_4_CYCLES  ((uint32_t)HAL_HSP_BRAM_LATENCY_4_CYCLES)

/**
  * @}
  */

/** @defgroup HSP_Processing_Function_Event_Interrupts_Constants HSP Processing Function Event Interrupts Constants
  * @{
  */
#define HSP_HW_IF_PROCLIST_NOTIF_PFCTEVT_0    (HAL_HSP_PROCLIST_IT_PFCTEVT_0)
#define HSP_HW_IF_PROCLIST_NOTIF_PFCTEVT_1    (HAL_HSP_PROCLIST_IT_PFCTEVT_1)
#define HSP_HW_IF_PROCLIST_NOTIF_PFCTEVT_2    (HAL_HSP_PROCLIST_IT_PFCTEVT_2)
#define HSP_HW_IF_PROCLIST_NOTIF_PFCTEVT_3    (HAL_HSP_PROCLIST_IT_PFCTEVT_3)
#define HSP_HW_IF_PROCLIST_NOTIF_PFCTEVT_4    (HAL_HSP_PROCLIST_IT_PFCTEVT_4)
#define HSP_HW_IF_PROCLIST_NOTIF_PFCTEVT_5    (HAL_HSP_PROCLIST_IT_PFCTEVT_5)
#define HSP_HW_IF_PROCLIST_NOTIF_PFCTEVT_6    (HAL_HSP_PROCLIST_IT_PFCTEVT_6)
#define HSP_HW_IF_PROCLIST_NOTIF_PFCTEVT_7    (HAL_HSP_PROCLIST_IT_PFCTEVT_7)
#define HSP_HW_IF_PROCLIST_NOTIF_PFCTEVT_8    (HAL_HSP_PROCLIST_IT_PFCTEVT_8)
#define HSP_HW_IF_PROCLIST_NOTIF_PFCTEVT_9    (HAL_HSP_PROCLIST_IT_PFCTEVT_9)
#define HSP_HW_IF_PROCLIST_NOTIF_PFCTEVT_10   (HAL_HSP_PROCLIST_IT_PFCTEVT_10)
#define HSP_HW_IF_PROCLIST_NOTIF_PFCTEVT_11   (HAL_HSP_PROCLIST_IT_PFCTEVT_11)
#define HSP_HW_IF_PROCLIST_NOTIF_PFCTEVT_12   (HAL_HSP_PROCLIST_IT_PFCTEVT_12)
#define HSP_HW_IF_PROCLIST_NOTIF_PFCTEVT_13   (HAL_HSP_PROCLIST_IT_PFCTEVT_13)
#define HSP_HW_IF_PROCLIST_NOTIF_PFCTEVT_14   (HAL_HSP_PROCLIST_IT_PFCTEVT_14)
#define HSP_HW_IF_PROCLIST_NOTIF_PFCTEVT_15   (HAL_HSP_PROCLIST_IT_PFCTEVT_15)
#define HSP_HW_IF_PROCLIST_NOTIF_PFCTEVT_16   (HAL_HSP_PROCLIST_IT_PFCTEVT_16)
#define HSP_HW_IF_PROCLIST_NOTIF_PFCTEVT_17   (HAL_HSP_PROCLIST_IT_PFCTEVT_17)
#define HSP_HW_IF_PROCLIST_NOTIF_PFCTEVT_18   (HAL_HSP_PROCLIST_IT_PFCTEVT_18)
#define HSP_HW_IF_PROCLIST_NOTIF_PFCTEVT_19   (HAL_HSP_PROCLIST_IT_PFCTEVT_19)
#define HSP_HW_IF_PROCLIST_NOTIF_PFCTEVT_20   (HAL_HSP_PROCLIST_IT_PFCTEVT_20)
#define HSP_HW_IF_PROCLIST_NOTIF_PFCTEVT_21   (HAL_HSP_PROCLIST_IT_PFCTEVT_21)
#define HSP_HW_IF_PROCLIST_NOTIF_PFCTEVT_22   (HAL_HSP_PROCLIST_IT_PFCTEVT_22)
#define HSP_HW_IF_PROCLIST_NOTIF_PFCTEVT_23   (HAL_HSP_PROCLIST_IT_PFCTEVT_23)
#define HSP_HW_IF_PROCLIST_NOTIF_PFCTEVT_24   (HAL_HSP_PROCLIST_IT_PFCTEVT_24)
#define HSP_HW_IF_PROCLIST_NOTIF_PFCTEVT_25   (HAL_HSP_PROCLIST_IT_PFCTEVT_25)
#define HSP_HW_IF_PROCLIST_NOTIF_PFCTEVT_26   (HAL_HSP_PROCLIST_IT_PFCTEVT_26)
#define HSP_HW_IF_PROCLIST_NOTIF_PFCTEVT_27   (HAL_HSP_PROCLIST_IT_PFCTEVT_27)
#define HSP_HW_IF_PROCLIST_NOTIF_PFCTEVT_28   (HAL_HSP_PROCLIST_IT_PFCTEVT_28)
#define HSP_HW_IF_PROCLIST_NOTIF_PFCTEVT_29   (HAL_HSP_PROCLIST_IT_PFCTEVT_29)
#define HSP_HW_IF_PROCLIST_NOTIF_PFCTEVT_30   (HAL_HSP_PROCLIST_IT_PFCTEVT_30)
#define HSP_HW_IF_PROCLIST_NOTIF_PFCTEVT_31   (HAL_HSP_PROCLIST_IT_PFCTEVT_31)
#define HSP_HW_IF_PROCLIST_NOTIF_PFCTEVT_ALL  (HAL_HSP_PROCLIST_IT_PFCTEVT_ALL)
/**
  * @}
  */

/** @defgroup HSP_Task_Comparator_Constants HSP Task Comparator Unit Constants
  * @{
  */
/* Defines for HSP TASK comparators ------------------------------------------*/
#define HSP_HW_IF_TASK_COMPARATOR_0  (HAL_HSP_TASK_COMPARATOR_0)
#define HSP_HW_IF_TASK_COMPARATOR_1  (HAL_HSP_TASK_COMPARATOR_1)
#define HSP_HW_IF_TASK_COMPARATOR_2  (HAL_HSP_TASK_COMPARATOR_2)
#define HSP_HW_IF_TASK_COMPARATOR_3  (HAL_HSP_TASK_COMPARATOR_3)

#define HSP_HW_IF_TCU_TASK_EVT_STARTED_MASK(tcuid)                                \
  ((tcuid == HSP_HW_IF_TASK_COMPARATOR_0)?HAL_HSP_FLAG_TCU_CMP_0_TASK_STARTED:    \
   (tcuid == HSP_HW_IF_TASK_COMPARATOR_1)?HAL_HSP_FLAG_TCU_CMP_1_TASK_STARTED:    \
   (tcuid == HSP_HW_IF_TASK_COMPARATOR_2)?HAL_HSP_FLAG_TCU_CMP_2_TASK_STARTED:    \
   (tcuid == HSP_HW_IF_TASK_COMPARATOR_3)?HAL_HSP_FLAG_TCU_CMP_3_TASK_STARTED: 0U)

#define HSP_HW_IF_TCU_TASK_EVT_ENDED_MASK(tcuid)                                \
  ((tcuid == HSP_HW_IF_TASK_COMPARATOR_0)?HAL_HSP_FLAG_TCU_CMP_0_TASK_ENDED:    \
   (tcuid == HSP_HW_IF_TASK_COMPARATOR_1)?HAL_HSP_FLAG_TCU_CMP_1_TASK_ENDED:    \
   (tcuid == HSP_HW_IF_TASK_COMPARATOR_2)?HAL_HSP_FLAG_TCU_CMP_2_TASK_ENDED:    \
   (tcuid == HSP_HW_IF_TASK_COMPARATOR_3)?HAL_HSP_FLAG_TCU_CMP_3_TASK_ENDED: 0U)

/**
  * @}
  */

/** @defgroup HSP_TimeStampCapture_Constants HSP TimeStamp Capture Constants
  * @{
  */
#define HSP_HW_IF_TSC_PRESCALER_DISABLE  (0xFFFFFFFFU)  /*!< Constant to disable the Timestamp Capture prescaler and then the Free-Running Counter */
#define HSP_HW_IF_TSC_MODE_SPE_BREAK    HAL_HSP_TSC_CAPTURE_MODE_SPE_BREAKS
#define HSP_HW_IF_TSC_MODE_TASK_CHANGE  HAL_HSP_TSC_CAPTURE_MODE_TASK_NBR_CHANGES
#define HSP_HW_IF_TSC_MODE_PFCT_CHANGE  HAL_HSP_TSC_CAPTURE_MODE_PFCT_NBR_CHANGES

/**
  * @}
  */

/** @defgroup HSP_BREAK_Event_Constants HSP BREAK Event Constants
  * @{
  */
#define HSP_HW_IF_BREAK_EVENT_MEMORY_ACCESS  HAL_HSP_BREAK_EVENT_MEMORY_ACCESS
#define HSP_HW_IF_BREAK_EVENT_FPU  HAL_HSP_BREAK_EVENT_FPU
#define HSP_HW_IF_BREAK_EVENT_OPCODE  HAL_HSP_BREAK_EVENT_OPCODE
#define HSP_HW_IF_BREAK_EVENT_PFCT28  HAL_HSP_BREAK_EVENT_PFCT_28
#define HSP_HW_IF_BREAK_EVENT_PFCT29  HAL_HSP_BREAK_EVENT_PFCT_29
#define HSP_HW_IF_BREAK_EVENT_PFCT30  HAL_HSP_BREAK_EVENT_PFCT_30
#define HSP_HW_IF_BREAK_EVENT_PFCT31  HAL_HSP_BREAK_EVENT_PFCT_31
#define HSP_HW_IF_BREAK_EVENT_FIRMWARE  HAL_HSP_BREAK_EVENT_FIRMWARE
#define HSP_HW_IF_BREAK_EVENT_SPE_OVR  HAL_HSP_BREAK_EVENT_SPE_OVR
#define HSP_HW_IF_BREAK_EVENT_FPU_SATURATION  HAL_HSP_BREAK_EVENT_FPU_SATURATION

#define HSP_HW_IF_BREAK_EVENT_SINGLE_STEP  HAL_HSP_BREAK_EVENT_SINGLE_STEP

/**
  * @}
  */

/** @defgroup HSP_TRGO_Constants HSP TRGO interface Constants
  * @{
  */
#define HSP_HW_IF_TRGO_0  ((uint32_t)HAL_HSP_TRGO_TRIGGER_0)
#define HSP_HW_IF_TRGO_1  ((uint32_t)HAL_HSP_TRGO_TRIGGER_1)
#define HSP_HW_IF_TRGO_2  ((uint32_t)HAL_HSP_TRGO_TRIGGER_2)
#define HSP_HW_IF_TRGO_3  ((uint32_t)HAL_HSP_TRGO_TRIGGER_3)

#define HSP_HW_IF_TRGO_SOURCE_STREAM  ((uint32_t)HAL_HSP_TRGO_SRC_STREAM)
#define HSP_HW_IF_TRGO_SOURCE_SPE     ((uint32_t)HAL_HSP_TRGO_SRC_SPE)
#define HSP_HW_IF_TRGO_SOURCE_TSC     ((uint32_t)HAL_HSP_TRGO_SRC_TIMESTAMPCAPTURE)

/**
  * @}
  */

/**
  * @}
  */

/* Exported macros -----------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/
/** @defgroup  HSP_HW_IF_Exported_Types HSP_HW_IF Exported Types
  * @{
  */
#define hsp_hw_if_firmware_t  hsp_fw_firmware_t

typedef struct
{
  uint32_t adc_source;
  uint32_t adc_channel_filter;
} hsp_hw_if_adcin_config_t;

/**
  * @}
  */

/* Exported functions --------------------------------------------------------*/
/** @defgroup HSP_HW_IF_Exported_Functions HSP_HW_IF Exported Functions
  * @{
  */
void HSP_HW_IF_Init(hsp_hw_if_ctx_t *p_if_ctx, void *hdriver, void *p_user_data);
void HSP_HW_IF_DeInit(hsp_hw_if_ctx_t *p_if_ctx);
void HSP_HW_IF_GetDCMDHWInfo(hsp_hw_if_ctx_t *p_if_ctx,
                             volatile uint32_t **p_dcmd_id, volatile uint32_t **p_dcmd_data_ptr,
                             volatile uint32_t **p_dcmd_param_data);

/* API to manage the FW & Plugin ---------------------------------------------*/
hsp_if_status_t HSP_HW_IF_LoadFW(hsp_hw_if_ctx_t *p_if_ctx, const void *p_fw_cram, const void *p_fw_dram);
hsp_if_status_t HSP_HW_IF_LoadPlugin(void *hdriver, const uint8_t *p_bin, uint32_t size_byte);

/* API to boot the HSP           ---------------------------------------------*/
hsp_if_status_t HSP_HW_IF_Boot(hsp_hw_if_ctx_t *p_if_ctx, uint32_t enableCycleCount);

/* API to communicate with the HSP -------------------------------------------*/
hsp_if_status_t HSP_HW_IF_SendCommand(void *hdriver, uint32_t command_id);
void HSP_HW_IF_WriteParameter(void *hdriver, uint32_t param_id, uint32_t value);
uint32_t HSP_HW_IF_ReadParameter(const hsp_hw_if_ctx_t *p_if_ctx, uint32_t param_id);

/**
  * @brief Wait until Direct Command Interface is free.
  * @param  p_if_ctx  Pointer to the HSP HW interface context.
  */
__STATIC_FORCEINLINE void HSP_HW_IF_WaitEndOfDirectCommand(const hsp_hw_if_ctx_t *p_if_ctx)
{
  while (HAL_HSP_DCMD_GetStatus((hal_hsp_handle_t *)(p_if_ctx->hdriver)) == HAL_HSP_DCMD_BUSY) {};
}

/**
  * @brief Return the status of the Message Box.
  * @param  p_if_ctx  Pointer to the HSP HW interface context.
  * @retval HSP_HW_IF_MSGBOX_NO_MSG  No message in the mailbox.
  * @retval HSP_HW_IF_MSGBOX_MSG_AVAILABLE  Message available in the mailbox.
  */
__STATIC_FORCEINLINE uint32_t HSP_HW_IF_MSGBOX_IsMsgAvailable(const hsp_hw_if_ctx_t *p_if_ctx)
{
  return (uint32_t)HAL_HSP_MSGBOX_IsMessageAvailable((hal_hsp_handle_t *)(p_if_ctx->hdriver));
}

/**
  * @brief Acknowledge the MSGBOX Semaphore to inform the HSP that the CPU has read the message.
  * @param  p_if_ctx  Pointer to the HSP HW interface context.
  */
__STATIC_FORCEINLINE void HSP_HW_IF_MSGBOX_ReleaseSemaphore(const hsp_hw_if_ctx_t *p_if_ctx)
{
  HAL_HSP_MSGBOX_AckSemaphore((hal_hsp_handle_t *)(p_if_ctx->hdriver));
}

uint32_t HSP_HW_IF_ClearFWERR(void *hdriver);

/* API to manage the SmartClocking -------------------------------------------*/
hsp_if_status_t HSP_HW_IF_EnableSmartClocking(void *hdriver, uint32_t clock_id);
hsp_if_status_t HSP_HW_IF_DisableSmartClocking(void *hdriver, uint32_t clock_id);
uint32_t HSP_HW_IF_IsEnabledSmartClocking(const hsp_hw_if_ctx_t *p_if_ctx, uint32_t clock_id);

/* API to manage OUTPUT ------------------------------------------------------*/
hsp_if_status_t HSP_HW_IF_OUTPUT_SetConfig(hsp_hw_if_ctx_t *p_if_ctx, uint32_t trgo_id, uint32_t source);

hsp_if_status_t HSP_HW_IF_OUTPUT_Enable(hsp_hw_if_ctx_t *p_if_ctx);
hsp_if_status_t HSP_HW_IF_OUTPUT_Disable(hsp_hw_if_ctx_t *p_if_ctx);
hsp_if_activation_status_t HSP_HW_IF_OUTPUT_IsEnabled(const hsp_hw_if_ctx_t *p_if_ctx);

/* API to manage Processing List ---------------------------------------------*/
hsp_if_status_t HSP_HW_IF_SEQ_StartRecord(hsp_hw_if_ctx_t *p_if_ctx, uint32_t pl_id);
hsp_if_status_t HSP_HW_IF_SEQ_StopRecord(hsp_hw_if_ctx_t *p_if_ctx);
hsp_if_status_t HSP_HW_IF_SEQ_ResetPL(const hsp_hw_if_ctx_t *p_if_ctx);

hsp_if_status_t HSP_HW_IF_SEQ_RunTask(void *hdriver, uint32_t task_id, uint32_t timeout_ms);
#if defined(USE_HSP_ENGINE_PROCLIST_NOTIFICATION_IT) && (USE_HSP_ENGINE_PROCLIST_NOTIFICATION_IT == 1)
hsp_if_status_t HSP_HW_IF_SEQ_EnableProclistNotificationIT(const hsp_hw_if_ctx_t *p_if_ctx, uint32_t interrupts);
hsp_if_status_t HSP_HW_IF_SEQ_DisableProclistNotificationIT(const hsp_hw_if_ctx_t *p_if_ctx, uint32_t interrupts);
#endif /* USE_HSP_ENGINE_PROCLIST_NOTIFICATION_IT */
hsp_if_status_t HSP_HW_IF_SEQ_PollForProclistNotification(const hsp_hw_if_ctx_t *p_if_ctx, uint32_t events,
                                                          uint32_t timeout_ms);

/* API to manage Trigger & Event configuration -------------------------------*/
#if defined(USE_HSP_ENGINE_STREAM_BUFFER) && (USE_HSP_ENGINE_STREAM_BUFFER == 1U)
hsp_if_status_t HSP_HW_IF_SEQ_EVENT_SetConfig_StreamBuffer(void *hdriver, uint32_t event_id,
                                                           uint32_t stream_buffer_id,
                                                           uint32_t direction, uint32_t buffer_sync,
                                                           uint32_t tcu_sync);

hsp_if_status_t HSP_HW_IF_SEQ_STREAM_EnableIntToFloat(void *hdriver);
hsp_if_status_t HSP_HW_IF_SEQ_STREAM_DisableIntToFloat(void *hdriver);

hsp_if_status_t HSP_HW_IF_SEQ_STREAM_Enable(hsp_hw_if_ctx_t *p_if_ctx);
hsp_if_status_t HSP_HW_IF_SEQ_STREAM_Disable(hsp_hw_if_ctx_t *p_if_ctx);
volatile uint32_t *HSP_HW_IF_SEQ_STREAM_GetBufferAddress(void *hdriver, uint32_t stream_buffer_id);
volatile uint32_t *HSP_HW_IF_SEQ_STREAM_GetBufferAddressFromPLID(void *hdriver, uint32_t pl_id);

hsp_if_status_t HSP_HW_IF_SEQ_STREAM_Buffer_Start(hsp_hw_if_ctx_t *p_if_ctx, uint32_t stream_buffer_id,
                                                  const int32_t *p_buffer,
                                                  uint32_t buffer_size);

#endif /* USE_HSP_ENGINE_STREAM_BUFFER */
#if defined(USE_HSP_ENGINE_ADCIN) && (USE_HSP_ENGINE_ADCIN == 1U)
hsp_if_status_t HSP_HW_IF_SEQ_EVENT_SetConfig_ADCIN(hsp_hw_if_ctx_t *p_if_ctx,
                                                    uint32_t evt_id, uint32_t evt_sync,
                                                    const hsp_hw_if_adcin_config_t *p_config_array, uint32_t array_size,
                                                    uint32_t *p_adcin_id_array);

hsp_if_status_t HSP_HW_IF_SEQ_ADCIN_Enable(hsp_hw_if_ctx_t *p_if_ctx);
hsp_if_status_t HSP_HW_IF_SEQ_ADCIN_Disable(hsp_hw_if_ctx_t *p_if_ctx);

const volatile uint32_t *HSP_HW_IF_SEQ_ADCIN_GetBufferAddress(void *hdriver, uint32_t adcin_id);

#endif /* USE_HSP_ENGINE_ADCIN */
hsp_if_status_t HSP_HW_IF_SEQ_EVENT_SetConfig_Trigger(hsp_hw_if_ctx_t *p_if_ctx, uint32_t evt_id,
                                                      uint32_t trigger_source, uint32_t polarity,
                                                      uint32_t evt_sync);
hsp_if_status_t HSP_HW_IF_SEQ_EVENT_SetConfig_CSEG(void *hdriver, uint32_t evt_id, uint32_t evt_sync);
hsp_if_status_t HSP_HW_IF_SEQ_EVENT_SetConfig_SPE(void *hdriver, uint32_t evt_id, uint32_t evt_sync);

hsp_if_status_t HSP_HW_IF_SEQ_EVENT_Enable(void *hdriver, uint32_t events_mask);
hsp_if_status_t HSP_HW_IF_SEQ_EVENT_Disable(void *hdriver, uint32_t events_mask);
uint32_t HSP_HW_IF_SEQ_EVENT_GetStatus(void *hdriver);

hsp_if_status_t HSP_HW_IF_SEQ_EVENT_Trig_CSEG(void *hdriver, uint32_t events_mask);
hsp_if_status_t HSP_HW_IF_SEQ_EVENT_PollForPending(void *hdriver, uint32_t events_mask, uint32_t timeout_ms);

/* API to BRAM Bandwidth Access control --------------------------------------*/
hsp_if_status_t HSP_HW_IF_BRAM_EnableConflictAccessCounter(void *hdriver);
hsp_if_status_t HSP_HW_IF_BRAM_DisableConflictAccessCounter(void *hdriver);
uint32_t HSP_HW_IF_BRAM_GetConflictAccessCounter(void *hdriver);
hsp_if_status_t HSP_HW_IF_BRAM_SetBandwidthArbitration(void *hdriver, uint32_t mode);
uint32_t HSP_HW_IF_BRAM_GetBandwidthArbitration(void *hdriver);

/* API for secure Access -----------------------------------------------------*/
hsp_if_status_t HSP_HW_IF_Lock(const hsp_hw_if_ctx_t *p_if_ctx);

/* API for TimeStamp Capture -------------------------------------------------*/
#if defined(USE_HSP_ENGINE_TIMESTAMPCAPTURE) && (USE_HSP_ENGINE_TIMESTAMPCAPTURE == 1U)
hsp_if_status_t HSP_HW_IF_TSC_SetDMA(hsp_hw_if_ctx_t *p_if_ctx, void *hdma);
hsp_if_status_t HSP_HW_IF_TSC_SetConfig(const hsp_hw_if_ctx_t *p_if_ctx,
                                        uint32_t prescaler, uint32_t task_id);
hsp_if_status_t HSP_HW_IF_TSC_Start(hsp_hw_if_ctx_t *p_if_ctx, uint32_t mode);
hsp_if_status_t HSP_HW_IF_TSC_Stop(const hsp_hw_if_ctx_t *p_if_ctx);
volatile const uint32_t *HSP_HW_IF_TSC_GetBufferAddress(const hsp_hw_if_ctx_t *p_if_ctx);
#endif /* USE_HSP_ENGINE_TIMESTAMPCAPTURE */

/* API for Task Comparator ---------------------------------------------------*/
hsp_if_status_t HSP_HW_IF_StartTaskComparator(const hsp_hw_if_ctx_t *p_if_ctx, uint32_t tcu_id, uint32_t task_id);
#if defined(USE_HSP_ENGINE_TCU_IT) && (USE_HSP_ENGINE_TCU_IT == 1U)
hsp_if_status_t HSP_HW_IF_StartTaskComparator_IT(const hsp_hw_if_ctx_t *p_if_ctx, uint32_t tcu_id, uint32_t task_id);
#endif /* USE_HSP_ENGINE_TCU_IT */
hsp_if_status_t HSP_HW_IF_StopTaskComparator(const hsp_hw_if_ctx_t *p_if_ctx, uint32_t tcu_id);

uint32_t HSP_HW_IF_GetFirmwareError(void *hdriver);

hsp_if_status_t HSP_HW_IF_WaitAndReleaseSemaphore(void *hdriver);
hsp_if_status_t HSP_HW_IF_WaitSemaphore(void *hdriver);
void HSP_HW_IF_ReleaseSemaphore(void *hdriver);

/* API for CNN ---------------------------------------------------------------*/
hsp_if_status_t HSP_HW_IF_CNN_Begin(void *hdriver, uint32_t cmd_id);
hsp_if_status_t HSP_HW_IF_CNN_StartOfProcess(void *hdriver, uint32_t cnn_cmd_id);
hsp_if_status_t HSP_HW_IF_CNN_WaitEndOfProcess(void *hdriver);
hsp_if_status_t HSP_HW_IF_CNN_End(void *hdriver);

/* API for BREAK -------------------------------------------------------------*/
hsp_if_status_t HSP_HW_IF_BREAK_SetMultiOutput(hsp_hw_if_ctx_t *p_if_ctx, const uint32_t *p_config_array,
                                               uint32_t config_array_size);
hsp_if_status_t HSP_HW_IF_BREAK_SetDebugEvents(hsp_hw_if_ctx_t *p_if_ctx, uint32_t debug_events);
hsp_if_status_t HSP_HW_IF_BREAK_ResumeDebugEvents(hsp_hw_if_ctx_t *p_if_ctx);

/* API for STI ---------------------------------------------------------------*/
#if defined(USE_HSP_STI_AP_PORT) && (USE_HSP_STI_AP_PORT == 1)
hsp_if_status_t HSP_HW_IF_STI_SetPortAddress(hsp_hw_if_ctx_t *p_if_ctx, uint32_t sti_port_id, uint32_t block_address);
#endif /* USE_HSP_STI_AP_PORT */

#if defined(USE_HSP_ENGINE_TIMESTAMPCAPTURE) && (USE_HSP_ENGINE_TIMESTAMPCAPTURE == 1U)
/* API for DMA ---------------------------------------------------------------*/
hsp_if_status_t HSP_HW_IF_DMA_Start(void *hdma, uint32_t src_addr, uint32_t dest_addr, uint32_t data_size);
#endif /* USE_HSP_ENGINE_TIMESTAMPCAPTURE */

/* API Register MW Callbacks ------------------------------------------------ */
hsp_if_status_t HSP_HW_IF_RegisterErrorCallback(hsp_hw_if_ctx_t *p_if_ctx, p_hsp_engine_error_cb_t p_callback);

#if defined(USE_HSP_ENGINE_STREAM_BUFFER) && (USE_HSP_ENGINE_STREAM_BUFFER == 1U)
hsp_if_status_t HSP_HW_IF_RegisterStreamBufferWriteCpltCallback(hsp_hw_if_ctx_t *p_if_ctx,
                                                                p_hsp_engine_one_param_cb_t p_callback);
hsp_if_status_t HSP_HW_IF_RegisterStreamBufferReadCpltCallback(hsp_hw_if_ctx_t *p_if_ctx,
                                                               p_hsp_engine_one_param_cb_t p_callback);
#endif /* USE_HSP_ENGINE_STREAM_BUFFER */

#if defined(USE_HSP_ENGINE_TCU_IT) && (USE_HSP_ENGINE_TCU_IT == 1U)
hsp_if_status_t HSP_HW_IF_RegisterTCU_TaskStartedCallback(hsp_hw_if_ctx_t *p_if_ctx,
                                                          p_hsp_engine_one_param_cb_t p_callback);
hsp_if_status_t HSP_HW_IF_RegisterTCU_TaskEndedCallback(hsp_hw_if_ctx_t *p_if_ctx,
                                                        p_hsp_engine_one_param_cb_t p_callback);
#endif /* USE_HSP_ENGINE_TCU_IT */

#if defined(USE_HSP_ENGINE_TIMESTAMPCAPTURE) && (USE_HSP_ENGINE_TIMESTAMPCAPTURE == 1U)
hsp_if_status_t HSP_HW_IF_TSC_IsCompleteCallback(hsp_hw_if_ctx_t *p_if_ctx);
hsp_if_status_t HSP_HW_IF_TSC_IsErrorCallback(hsp_hw_if_ctx_t *p_if_ctx);
hsp_if_status_t HSP_HW_IF_RegisterTSC_CompleteCallback(hsp_hw_if_ctx_t *p_if_ctx,
                                                       p_hsp_engine_cb_t p_callback);
hsp_if_status_t HSP_HW_IF_RegisterTSC_ErrorCallback(hsp_hw_if_ctx_t *p_if_ctx,
                                                    p_hsp_engine_cb_t p_callback);
#endif /* USE_HSP_ENGINE_TIMESTAMPCAPTURE */
#if defined(USE_HSP_ENGINE_PROCLIST_NOTIFICATION_IT) && (USE_HSP_ENGINE_PROCLIST_NOTIFICATION_IT == 1U)
hsp_if_status_t HSP_HW_IF_RegisterProcessingEventCallback(hsp_hw_if_ctx_t *p_if_ctx,
                                                          p_hsp_engine_one_param_cb_t p_callback);
#endif /* USE_HSP_ENGINE_PROCLIST_NOTIFICATION_IT */

/**
  * @}
  */

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
#endif /* __cplusplus */

#endif /* HSP_HW_IF_H */
