/**
  ******************************************************************************
  * @file    hsp_proclist.h
  * @brief   Header file for hsp_proclist.c
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

/* Define to prevent recursive  ----------------------------------------------*/
#ifndef HSP_PROCLIST_H
#define HSP_PROCLIST_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "hsp_def.h"

/** @addtogroup HSP_ENGINE
  * @{
  */

/** @addtogroup HSP_CORE HSP Core
  * @{
  */

/** @defgroup HSP_PROCLIST HSP Processing List Management
  * @{
  */

/** @defgroup HSP_PROCLIST_Exported_Defines HSP Processing List Exported Constants
  * @{
  */
#define HSP_SEQ_TRGIN_0  0U
#define HSP_SEQ_TRGIN_1  1U
#define HSP_SEQ_TRGIN_2  2U
#define HSP_SEQ_TRGIN_3  3U
#define HSP_SEQ_TRGIN_4  4U
#define HSP_SEQ_TRGIN_5  5U
#define HSP_SEQ_TRGIN_6  6U
#define HSP_SEQ_TRGIN_7  7U
#define HSP_SEQ_TRGIN_8  8U
#define HSP_SEQ_TRGIN_9  9U

#define HSP_SEQ_STREAM_BUFFER_0  0U
#define HSP_SEQ_STREAM_BUFFER_1  1U
#define HSP_SEQ_STREAM_BUFFER_2  2U
#define HSP_SEQ_STREAM_BUFFER_3  3U

#define HSP_SEQ_TASK_COMPARATOR_0  0U
#define HSP_SEQ_TASK_COMPARATOR_1  1U
#define HSP_SEQ_TASK_COMPARATOR_2  2U
#define HSP_SEQ_TASK_COMPARATOR_3  3U

/**
  * @}
  */

/** @defgroup HSP_PROCLIST_Exported_Macros HSP Processing List Exported Macros
  * @{
  */
/**
  * @brief   Convert an event id number to a bit mask value
  * @param   evt_id  value in range [0..31]
  * @return  bitmask value
  */
#define HSP_SEQ_EVENT_ID_TO_BITMASK(evt_id)  (0x1UL << (evt_id))

 /**
  * @}
  */

/** @defgroup HSP_PROCLIST_Exported_Types HSP Processing List Exported Types
  * @{
  */
typedef enum
{
  HSP_SEQ_EVENT_1 = 1U,
  HSP_SEQ_EVENT_2 = 2U,
  HSP_SEQ_EVENT_3 = 3U,
  HSP_SEQ_EVENT_4 = 4U,
  HSP_SEQ_EVENT_5 = 5U,
  HSP_SEQ_EVENT_6 = 6U,
  HSP_SEQ_EVENT_7 = 7U,
  HSP_SEQ_EVENT_8 = 8U,
  HSP_SEQ_EVENT_9 = 9U,
  HSP_SEQ_EVENT_10 = 10U,
  HSP_SEQ_EVENT_11 = 11U,
  HSP_SEQ_EVENT_12 = 12U,
  HSP_SEQ_EVENT_13 = 13U,
  HSP_SEQ_EVENT_14 = 14U,
  HSP_SEQ_EVENT_15 = 15U,
  HSP_SEQ_EVENT_16 = 16U,
  HSP_SEQ_EVENT_17 = 17U,
  HSP_SEQ_EVENT_18 = 18U,
  HSP_SEQ_EVENT_19 = 19U,
  HSP_SEQ_EVENT_20 = 20U,
  HSP_SEQ_EVENT_21 = 21U,
  HSP_SEQ_EVENT_22 = 22U,
} hsp_seq_event_t;

/* Value of Trigger */
/*  +--- ... ---+------------------+------------------+------------------+ */
/*  |  Reserved | Event ID (5-bit) | Type ITF (5-bit) |  Idx ITF (4-bit) | */
/*  +--- ... ---+------------------+------------------+------------------+ */
#define HSP_SEQ_EVENT_ID_POS             (9U)
#define HSP_SEQ_EVENT_ID_MSK             (0x1FUL << HSP_SEQ_EVENT_ID_POS)
#define HSP_SEQ_EVENT_ITF_TYPE_POS       (4U)
#define HSP_SEQ_EVENT_ITF_TYPE_MSK       (0x1FUL << HSP_SEQ_EVENT_ITF_TYPE_POS)
#define HSP_SEQ_EVENT_ITF_ID_POS         (0U)
#define HSP_SEQ_EVENT_ITF_ID_MSK         (0xFUL  << HSP_SEQ_EVENT_ITF_ID_POS)

#define HSP_SEQ_EVENT_ITF_CSEG           (0x1UL  << HSP_SEQ_EVENT_ITF_ID_POS)
#define HSP_SEQ_EVENT_ITF_HSEG           (0x2UL  << HSP_SEQ_EVENT_ITF_ID_POS)
#define HSP_SEQ_EVENT_ITF_TRGIN          (0x4UL  << HSP_SEQ_EVENT_ITF_ID_POS)
#define HSP_SEQ_EVENT_ITF_STREAM_BUFFER  (0x8UL  << HSP_SEQ_EVENT_ITF_ID_POS)
#define HSP_SEQ_EVENT_ITF_ADCIN          (0x10UL << HSP_SEQ_EVENT_ITF_ID_POS)

typedef enum
{
  /* Event 1 source Matrix ****************************************************/
  HSP_SEQ_EVENT_1_STREAM0   = ((1UL  << HSP_SEQ_EVENT_ID_POS) | HSP_SEQ_EVENT_ITF_STREAM_BUFFER | 0UL),
  HSP_SEQ_EVENT_1_TRGIN3    = ((1UL  << HSP_SEQ_EVENT_ID_POS) | HSP_SEQ_EVENT_ITF_TRGIN         | 3UL),
  HSP_SEQ_EVENT_1_TRGIN8    = ((1UL  << HSP_SEQ_EVENT_ID_POS) | HSP_SEQ_EVENT_ITF_TRGIN         | 8UL),
  HSP_SEQ_EVENT_1_HSEG      = ((1UL  << HSP_SEQ_EVENT_ID_POS) | HSP_SEQ_EVENT_ITF_HSEG          | 0UL),
  HSP_SEQ_EVENT_1_CSEG      = ((1UL  << HSP_SEQ_EVENT_ID_POS) | HSP_SEQ_EVENT_ITF_CSEG          | 0UL),
  /* Event 2 source Matrix ****************************************************/
  HSP_SEQ_EVENT_2_STREAM1   = ((2UL  << HSP_SEQ_EVENT_ID_POS) | HSP_SEQ_EVENT_ITF_STREAM_BUFFER | 1UL),
  HSP_SEQ_EVENT_2_TRGIN4    = ((2UL  << HSP_SEQ_EVENT_ID_POS) | HSP_SEQ_EVENT_ITF_TRGIN         | 4UL), 
  HSP_SEQ_EVENT_2_TRGIN9    = ((2UL  << HSP_SEQ_EVENT_ID_POS) | HSP_SEQ_EVENT_ITF_TRGIN         | 9UL), 
  HSP_SEQ_EVENT_2_HSEG      = ((2UL  << HSP_SEQ_EVENT_ID_POS) | HSP_SEQ_EVENT_ITF_HSEG          | 0UL),
  HSP_SEQ_EVENT_2_CSEG      = ((2UL  << HSP_SEQ_EVENT_ID_POS) | HSP_SEQ_EVENT_ITF_CSEG          | 0UL),
  /* Event 3 source Matrix ****************************************************/
  HSP_SEQ_EVENT_3_STREAM2   = ((3UL  << HSP_SEQ_EVENT_ID_POS) | HSP_SEQ_EVENT_ITF_STREAM_BUFFER | 2UL),
  HSP_SEQ_EVENT_3_TRGIN0    = ((3UL  << HSP_SEQ_EVENT_ID_POS) | HSP_SEQ_EVENT_ITF_TRGIN         | 0UL),
  HSP_SEQ_EVENT_3_TRGIN5    = ((3UL  << HSP_SEQ_EVENT_ID_POS) | HSP_SEQ_EVENT_ITF_TRGIN         | 5UL),
  HSP_SEQ_EVENT_3_HSEG      = ((3UL  << HSP_SEQ_EVENT_ID_POS) | HSP_SEQ_EVENT_ITF_HSEG          | 0UL),
  HSP_SEQ_EVENT_3_CSEG      = ((3UL  << HSP_SEQ_EVENT_ID_POS) | HSP_SEQ_EVENT_ITF_CSEG          | 0UL),
  /* Event 4 source Matrix ****************************************************/
  HSP_SEQ_EVENT_4_STREAM3   = ((4UL  << HSP_SEQ_EVENT_ID_POS) | HSP_SEQ_EVENT_ITF_STREAM_BUFFER | 3UL),
  HSP_SEQ_EVENT_4_TRGIN1    = ((4UL  << HSP_SEQ_EVENT_ID_POS) | HSP_SEQ_EVENT_ITF_TRGIN         | 1UL),
  HSP_SEQ_EVENT_4_TRGIN6    = ((4UL  << HSP_SEQ_EVENT_ID_POS) | HSP_SEQ_EVENT_ITF_TRGIN         | 6UL),
  HSP_SEQ_EVENT_4_HSEG      = ((4UL  << HSP_SEQ_EVENT_ID_POS) | HSP_SEQ_EVENT_ITF_HSEG          | 0UL),
  HSP_SEQ_EVENT_4_CSEG      = ((4UL  << HSP_SEQ_EVENT_ID_POS) | HSP_SEQ_EVENT_ITF_CSEG          | 0UL),
  /* Event 5 source Matrix ****************************************************/
  HSP_SEQ_EVENT_5_STREAM0   = ((5UL  << HSP_SEQ_EVENT_ID_POS) | HSP_SEQ_EVENT_ITF_STREAM_BUFFER | 0UL),
  HSP_SEQ_EVENT_5_TRGIN2    = ((5UL  << HSP_SEQ_EVENT_ID_POS) | HSP_SEQ_EVENT_ITF_TRGIN         | 2UL),
  HSP_SEQ_EVENT_5_TRGIN7    = ((5UL  << HSP_SEQ_EVENT_ID_POS) | HSP_SEQ_EVENT_ITF_TRGIN         | 7UL),
  HSP_SEQ_EVENT_5_HSEG      = ((5UL  << HSP_SEQ_EVENT_ID_POS) | HSP_SEQ_EVENT_ITF_HSEG          | 0UL),
  HSP_SEQ_EVENT_5_CSEG      = ((5UL  << HSP_SEQ_EVENT_ID_POS) | HSP_SEQ_EVENT_ITF_CSEG          | 0UL),
  /* Event 6 source Matrix ****************************************************/
  HSP_SEQ_EVENT_6_STREAM1   = ((6UL  << HSP_SEQ_EVENT_ID_POS) | HSP_SEQ_EVENT_ITF_STREAM_BUFFER | 1UL),
  HSP_SEQ_EVENT_6_TRGIN3    = ((6UL  << HSP_SEQ_EVENT_ID_POS) | HSP_SEQ_EVENT_ITF_TRGIN         | 3UL),
  HSP_SEQ_EVENT_6_TRGIN8    = ((6UL  << HSP_SEQ_EVENT_ID_POS) | HSP_SEQ_EVENT_ITF_TRGIN         | 8UL),
  HSP_SEQ_EVENT_6_HSEG      = ((6UL  << HSP_SEQ_EVENT_ID_POS) | HSP_SEQ_EVENT_ITF_HSEG          | 0UL),
  HSP_SEQ_EVENT_6_CSEG      = ((6UL  << HSP_SEQ_EVENT_ID_POS) | HSP_SEQ_EVENT_ITF_CSEG          | 0UL),
  /* Event 7 source Matrix ****************************************************/
  HSP_SEQ_EVENT_7_STREAM2   = ((7UL  << HSP_SEQ_EVENT_ID_POS) | HSP_SEQ_EVENT_ITF_STREAM_BUFFER | 2UL),
  HSP_SEQ_EVENT_7_TRGIN4    = ((7UL  << HSP_SEQ_EVENT_ID_POS) | HSP_SEQ_EVENT_ITF_TRGIN         | 4UL),
  HSP_SEQ_EVENT_7_TRGIN9    = ((7UL  << HSP_SEQ_EVENT_ID_POS) | HSP_SEQ_EVENT_ITF_TRGIN         | 9UL),
  HSP_SEQ_EVENT_7_HSEG      = ((7UL  << HSP_SEQ_EVENT_ID_POS) | HSP_SEQ_EVENT_ITF_HSEG          | 0UL),
  HSP_SEQ_EVENT_7_CSEG      = ((7UL  << HSP_SEQ_EVENT_ID_POS) | HSP_SEQ_EVENT_ITF_CSEG          | 0UL),
  /* Event 8 source Matrix ****************************************************/
  HSP_SEQ_EVENT_8_STREAM3   = ((8UL  << HSP_SEQ_EVENT_ID_POS) | HSP_SEQ_EVENT_ITF_STREAM_BUFFER | 3UL),
  HSP_SEQ_EVENT_8_TRGIN0    = ((8UL  << HSP_SEQ_EVENT_ID_POS) | HSP_SEQ_EVENT_ITF_TRGIN         | 0UL),
  HSP_SEQ_EVENT_8_TRGIN5    = ((8UL  << HSP_SEQ_EVENT_ID_POS) | HSP_SEQ_EVENT_ITF_TRGIN         | 5UL),
  HSP_SEQ_EVENT_8_HSEG      = ((8UL  << HSP_SEQ_EVENT_ID_POS) | HSP_SEQ_EVENT_ITF_HSEG          | 0UL),
  HSP_SEQ_EVENT_8_CSEG      = ((8UL  << HSP_SEQ_EVENT_ID_POS) | HSP_SEQ_EVENT_ITF_CSEG          | 0UL),
  /* Event 9 source Matrix ****************************************************/
  HSP_SEQ_EVENT_9_STREAM0   = ((9UL  << HSP_SEQ_EVENT_ID_POS) | HSP_SEQ_EVENT_ITF_STREAM_BUFFER | 0UL),
  HSP_SEQ_EVENT_9_TRGIN1    = ((9UL  << HSP_SEQ_EVENT_ID_POS) | HSP_SEQ_EVENT_ITF_TRGIN         | 1UL),
  HSP_SEQ_EVENT_9_TRGIN6    = ((9UL  << HSP_SEQ_EVENT_ID_POS) | HSP_SEQ_EVENT_ITF_TRGIN         | 6UL),
  HSP_SEQ_EVENT_9_HSEG      = ((9UL  << HSP_SEQ_EVENT_ID_POS) | HSP_SEQ_EVENT_ITF_HSEG          | 0UL),
  HSP_SEQ_EVENT_9_CSEG      = ((9UL  << HSP_SEQ_EVENT_ID_POS) | HSP_SEQ_EVENT_ITF_CSEG          | 0UL),
  /* Event 10 source Matrix ***************************************************/
  HSP_SEQ_EVENT_10_STREAM1  = ((10UL << HSP_SEQ_EVENT_ID_POS) | HSP_SEQ_EVENT_ITF_STREAM_BUFFER | 1UL),
  HSP_SEQ_EVENT_10_TRGIN2   = ((10UL << HSP_SEQ_EVENT_ID_POS) | HSP_SEQ_EVENT_ITF_TRGIN         | 2UL),
  HSP_SEQ_EVENT_10_TRGIN7   = ((10UL << HSP_SEQ_EVENT_ID_POS) | HSP_SEQ_EVENT_ITF_TRGIN         | 7UL),
  HSP_SEQ_EVENT_10_HSEG     = ((10UL << HSP_SEQ_EVENT_ID_POS) | HSP_SEQ_EVENT_ITF_HSEG          | 0UL),
  HSP_SEQ_EVENT_10_CSEG     = ((10UL << HSP_SEQ_EVENT_ID_POS) | HSP_SEQ_EVENT_ITF_CSEG          | 0UL),
  /* Event 11 source Matrix ***************************************************/
  HSP_SEQ_EVENT_11_STREAM2  = ((11UL << HSP_SEQ_EVENT_ID_POS) | HSP_SEQ_EVENT_ITF_STREAM_BUFFER | 1UL),
  HSP_SEQ_EVENT_11_TRGIN3   = ((11UL << HSP_SEQ_EVENT_ID_POS) | HSP_SEQ_EVENT_ITF_TRGIN         | 2UL),
  HSP_SEQ_EVENT_11_TRGIN8   = ((11UL << HSP_SEQ_EVENT_ID_POS) | HSP_SEQ_EVENT_ITF_TRGIN         | 7UL),
  HSP_SEQ_EVENT_11_HSEG     = ((11UL << HSP_SEQ_EVENT_ID_POS) | HSP_SEQ_EVENT_ITF_HSEG          | 0UL),
  HSP_SEQ_EVENT_11_CSEG     = ((11UL << HSP_SEQ_EVENT_ID_POS) | HSP_SEQ_EVENT_ITF_CSEG          | 0UL),
  /* Event 12 source Matrix ***************************************************/
  HSP_SEQ_EVENT_12_STREAM3  = ((12UL << HSP_SEQ_EVENT_ID_POS) | HSP_SEQ_EVENT_ITF_STREAM_BUFFER | 3UL),
  HSP_SEQ_EVENT_12_TRGIN4   = ((12UL << HSP_SEQ_EVENT_ID_POS) | HSP_SEQ_EVENT_ITF_TRGIN         | 4UL),
  HSP_SEQ_EVENT_12_TRGIN9   = ((12UL << HSP_SEQ_EVENT_ID_POS) | HSP_SEQ_EVENT_ITF_TRGIN         | 9UL),
  HSP_SEQ_EVENT_12_HSEG     = ((12UL << HSP_SEQ_EVENT_ID_POS) | HSP_SEQ_EVENT_ITF_HSEG          | 0UL),
  HSP_SEQ_EVENT_12_CSEG     = ((12UL << HSP_SEQ_EVENT_ID_POS) | HSP_SEQ_EVENT_ITF_CSEG          | 0UL),
  /* Event 13 source Matrix ***************************************************/
  HSP_SEQ_EVENT_13_STREAM0  = ((13UL << HSP_SEQ_EVENT_ID_POS) | HSP_SEQ_EVENT_ITF_STREAM_BUFFER | 0UL),
  HSP_SEQ_EVENT_13_TRGIN0   = ((13UL << HSP_SEQ_EVENT_ID_POS) | HSP_SEQ_EVENT_ITF_TRGIN         | 0UL),
  HSP_SEQ_EVENT_13_TRGIN5   = ((13UL << HSP_SEQ_EVENT_ID_POS) | HSP_SEQ_EVENT_ITF_TRGIN         | 5UL),
  HSP_SEQ_EVENT_13_HSEG     = ((13UL << HSP_SEQ_EVENT_ID_POS) | HSP_SEQ_EVENT_ITF_HSEG          | 0UL),
  HSP_SEQ_EVENT_13_CSEG     = ((13UL << HSP_SEQ_EVENT_ID_POS) | HSP_SEQ_EVENT_ITF_CSEG          | 0UL),
  /* Event 14 source Matrix ***************************************************/
  HSP_SEQ_EVENT_14_STREAM1  = ((14UL << HSP_SEQ_EVENT_ID_POS) | HSP_SEQ_EVENT_ITF_STREAM_BUFFER | 1UL),
  HSP_SEQ_EVENT_14_TRGIN1   = ((14UL << HSP_SEQ_EVENT_ID_POS) | HSP_SEQ_EVENT_ITF_TRGIN         | 1UL),
  HSP_SEQ_EVENT_14_TRGIN6   = ((14UL << HSP_SEQ_EVENT_ID_POS) | HSP_SEQ_EVENT_ITF_TRGIN         | 6UL),
  HSP_SEQ_EVENT_14_HSEG     = ((14UL << HSP_SEQ_EVENT_ID_POS) | HSP_SEQ_EVENT_ITF_HSEG          | 0UL),
  HSP_SEQ_EVENT_14_CSEG     = ((14UL << HSP_SEQ_EVENT_ID_POS) | HSP_SEQ_EVENT_ITF_CSEG          | 0UL),
  /* Event 15 source Matrix ***************************************************/
  HSP_SEQ_EVENT_15_STREAM2  = ((15UL << HSP_SEQ_EVENT_ID_POS) | HSP_SEQ_EVENT_ITF_STREAM_BUFFER | 2UL),
  HSP_SEQ_EVENT_15_TRGIN2   = ((15UL << HSP_SEQ_EVENT_ID_POS) | HSP_SEQ_EVENT_ITF_TRGIN         | 2UL),
  HSP_SEQ_EVENT_15_TRGIN7   = ((15UL << HSP_SEQ_EVENT_ID_POS) | HSP_SEQ_EVENT_ITF_TRGIN         | 7UL),
  HSP_SEQ_EVENT_15_HSEG     = ((15UL << HSP_SEQ_EVENT_ID_POS) | HSP_SEQ_EVENT_ITF_HSEG          | 0UL),
  HSP_SEQ_EVENT_15_CSEG     = ((15UL << HSP_SEQ_EVENT_ID_POS) | HSP_SEQ_EVENT_ITF_CSEG          | 0UL),
  /* Event 16 source Matrix ***************************************************/
  HSP_SEQ_EVENT_16_STREAM3  = ((16UL << HSP_SEQ_EVENT_ID_POS) | HSP_SEQ_EVENT_ITF_STREAM_BUFFER | 3UL),
  HSP_SEQ_EVENT_16_TRGIN3   = ((16UL << HSP_SEQ_EVENT_ID_POS) | HSP_SEQ_EVENT_ITF_TRGIN         | 3UL),
  HSP_SEQ_EVENT_16_TRGIN8   = ((16UL << HSP_SEQ_EVENT_ID_POS) | HSP_SEQ_EVENT_ITF_TRGIN         | 8UL),
  HSP_SEQ_EVENT_16_HSEG     = ((16UL << HSP_SEQ_EVENT_ID_POS) | HSP_SEQ_EVENT_ITF_HSEG          | 0UL),
  HSP_SEQ_EVENT_16_CSEG     = ((16UL << HSP_SEQ_EVENT_ID_POS) | HSP_SEQ_EVENT_ITF_CSEG          | 0UL),
  /* Event 17 source Matrix ***************************************************/
  HSP_SEQ_EVENT_17_STREAM0  = ((17UL << HSP_SEQ_EVENT_ID_POS) | HSP_SEQ_EVENT_ITF_STREAM_BUFFER | 0UL),
  HSP_SEQ_EVENT_17_TRGIN4   = ((17UL << HSP_SEQ_EVENT_ID_POS) | HSP_SEQ_EVENT_ITF_TRGIN         | 4UL),
  HSP_SEQ_EVENT_17_TRGIN9   = ((17UL << HSP_SEQ_EVENT_ID_POS) | HSP_SEQ_EVENT_ITF_TRGIN         | 9UL),
  HSP_SEQ_EVENT_17_HSEG     = ((17UL << HSP_SEQ_EVENT_ID_POS) | HSP_SEQ_EVENT_ITF_HSEG          | 0UL),
  HSP_SEQ_EVENT_17_CSEG     = ((17UL << HSP_SEQ_EVENT_ID_POS) | HSP_SEQ_EVENT_ITF_CSEG          | 0UL),
  /* Event 18 source Matrix ***************************************************/
  HSP_SEQ_EVENT_18_STREAM1  = ((18UL << HSP_SEQ_EVENT_ID_POS) | HSP_SEQ_EVENT_ITF_STREAM_BUFFER | 1UL),
  HSP_SEQ_EVENT_18_TRGIN0   = ((18UL << HSP_SEQ_EVENT_ID_POS) | HSP_SEQ_EVENT_ITF_TRGIN         | 0UL),
  HSP_SEQ_EVENT_18_TRGIN5   = ((18UL << HSP_SEQ_EVENT_ID_POS) | HSP_SEQ_EVENT_ITF_TRGIN         | 5UL),
  HSP_SEQ_EVENT_18_HSEG     = ((18UL << HSP_SEQ_EVENT_ID_POS) | HSP_SEQ_EVENT_ITF_HSEG          | 0UL),
  HSP_SEQ_EVENT_18_CSEG     = ((18UL << HSP_SEQ_EVENT_ID_POS) | HSP_SEQ_EVENT_ITF_CSEG          | 0UL),
  /* Event 19 source Matrix ***************************************************/
  HSP_SEQ_EVENT_19_STREAM2  = ((19UL << HSP_SEQ_EVENT_ID_POS) | HSP_SEQ_EVENT_ITF_STREAM_BUFFER | 2UL),
  HSP_SEQ_EVENT_19_TRGIN1   = ((19UL << HSP_SEQ_EVENT_ID_POS) | HSP_SEQ_EVENT_ITF_TRGIN         | 1UL),
  HSP_SEQ_EVENT_19_TRGIN6   = ((19UL << HSP_SEQ_EVENT_ID_POS) | HSP_SEQ_EVENT_ITF_TRGIN         | 6UL),
  HSP_SEQ_EVENT_19_HSEG     = ((19UL << HSP_SEQ_EVENT_ID_POS) | HSP_SEQ_EVENT_ITF_HSEG          | 0UL),
  HSP_SEQ_EVENT_19_CSEG     = ((19UL << HSP_SEQ_EVENT_ID_POS) | HSP_SEQ_EVENT_ITF_CSEG          | 0UL),
  /* Event 20 source Matrix ***************************************************/
  HSP_SEQ_EVENT_20_STREAM3  = ((20UL << HSP_SEQ_EVENT_ID_POS) | HSP_SEQ_EVENT_ITF_STREAM_BUFFER | 3UL),
  HSP_SEQ_EVENT_20_TRGIN2   = ((20UL << HSP_SEQ_EVENT_ID_POS) | HSP_SEQ_EVENT_ITF_TRGIN         | 2UL),
  HSP_SEQ_EVENT_20_TRGIN7   = ((20UL << HSP_SEQ_EVENT_ID_POS) | HSP_SEQ_EVENT_ITF_TRGIN         | 7UL),
  HSP_SEQ_EVENT_20_HSEG     = ((20UL << HSP_SEQ_EVENT_ID_POS) | HSP_SEQ_EVENT_ITF_HSEG          | 0UL),
  HSP_SEQ_EVENT_20_CSEG     = ((20UL << HSP_SEQ_EVENT_ID_POS) | HSP_SEQ_EVENT_ITF_CSEG          | 0UL),
  /* Event 21 source Matrix ***************************************************/
  HSP_SEQ_EVENT_21_STREAM0  = ((21UL << HSP_SEQ_EVENT_ID_POS) | HSP_SEQ_EVENT_ITF_STREAM_BUFFER | 0UL),
  HSP_SEQ_EVENT_21_TRGIN3   = ((21UL << HSP_SEQ_EVENT_ID_POS) | HSP_SEQ_EVENT_ITF_TRGIN         | 3UL),
  HSP_SEQ_EVENT_21_TRGIN8   = ((21UL << HSP_SEQ_EVENT_ID_POS) | HSP_SEQ_EVENT_ITF_TRGIN         | 8UL),
  HSP_SEQ_EVENT_21_HSEG     = ((21UL << HSP_SEQ_EVENT_ID_POS) | HSP_SEQ_EVENT_ITF_HSEG          | 0UL),
  HSP_SEQ_EVENT_21_CSEG     = ((21UL << HSP_SEQ_EVENT_ID_POS) | HSP_SEQ_EVENT_ITF_CSEG          | 0UL),
  /* Event 22 source Matrix ***************************************************/
  HSP_SEQ_EVENT_22_STREAM1  = ((22UL << HSP_SEQ_EVENT_ID_POS) | HSP_SEQ_EVENT_ITF_STREAM_BUFFER | 1UL),
  HSP_SEQ_EVENT_22_TRGIN4   = ((22UL << HSP_SEQ_EVENT_ID_POS) | HSP_SEQ_EVENT_ITF_TRGIN         | 4UL),
  HSP_SEQ_EVENT_22_TRGIN9   = ((22UL << HSP_SEQ_EVENT_ID_POS) | HSP_SEQ_EVENT_ITF_TRGIN         | 9UL),
  HSP_SEQ_EVENT_22_HSEG     = ((22UL << HSP_SEQ_EVENT_ID_POS) | HSP_SEQ_EVENT_ITF_HSEG          | 0UL),
  HSP_SEQ_EVENT_22_CSEG     = ((22UL << HSP_SEQ_EVENT_ID_POS) | HSP_SEQ_EVENT_ITF_CSEG          | 0UL),
} hsp_seq_event_source_t;

typedef enum
{
  HSP_SEQ_EVENT_SYNC_TCU_0 = 0U,
  HSP_SEQ_EVENT_SYNC_TCU_1 = 1U,
  HSP_SEQ_EVENT_SYNC_TCU_2 = 2U,
  HSP_SEQ_EVENT_SYNC_TCU_3 = 3U,
  HSP_SEQ_EVENT_SYNC_TCU_DISABLED = 0xFFU
} hsp_seq_event_sync_tcu_t;

typedef struct
{
  hsp_seq_event_source_t source;
  hsp_seq_event_sync_tcu_t sync;
} hsp_seq_event_config_t;

typedef enum
{
  HSP_SEQ_TRGIN_POLARITY_RISING = 0U,
  HSP_SEQ_TRGIN_POLARITY_FALLING = 1U,
} hsp_seq_trgin_polarity_t;

typedef struct
{
  uint32_t instance;
  hsp_seq_trgin_polarity_t polarity;
  uint32_t source;
  hsp_seq_event_sync_tcu_t evt_sync;
} hsp_seq_event_trigger_config_t;

typedef enum
{
  HSP_SEQ_STREAM_BUFFER_RX = 0U,
  HSP_SEQ_STREAM_BUFFER_TX = 1U,
} hsp_seq_stream_buffer_direction_t;

typedef enum
{
  HSP_SEQ_STREAM_BUFFER_SYNC_DISABLE,
  HSP_SEQ_STREAM_BUFFER_SYNC_ENABLE,
} hsp_seq_stream_buffer_sync_state_t;

typedef struct
{
  uint32_t instance;
  hsp_seq_stream_buffer_direction_t direction;
  hsp_seq_stream_buffer_sync_state_t sync;
  hsp_seq_event_sync_tcu_t evt_sync;
} hsp_seq_event_stream_buffer_config_t;

/**
  * @}
  */

/** @defgroup HSP_PROCLIST_Exported_Macros HSP Processing List Exported Macros
  * @{
  */

/**
  * @}
  */

/** @defgroup HSP_PROCLIST_Exported_Functions HSP Processing List Exported Functions
  * @{
  */
/** @defgroup HSP_PROCLIST_Exported_Functions_Group1 HSP Processing List Recording
  * @{
  */
hsp_core_status_t HSP_SEQ_StartRecordPL(hsp_core_handle_t *hmw, uint32_t pl_id);
hsp_core_status_t HSP_SEQ_StopRecordPL(hsp_core_handle_t *hmw);
hsp_core_status_t HSP_SEQ_RunTask(hsp_core_handle_t *hmw, uint32_t pl_id, uint32_t timeout_ms);
hsp_core_status_t HSP_SEQ_ResetPL(hsp_core_handle_t *hmw);

/**
  * @}
  */

/** @defgroup HSP_PROCLIST_Exported_Functions_Group2 HSP Processing List Event Management
  * @{
  */
/* Event configuration -------------------------------------------------------*/
hsp_core_status_t HSP_SEQ_EVENT_SetConfig_StreamBuffer(hsp_core_handle_t *hmw, hsp_seq_event_t evt_id,
                                                       const hsp_seq_event_stream_buffer_config_t *p_config);
hsp_core_status_t HSP_SEQ_STREAM_Enable(hsp_core_handle_t *hmw);
hsp_core_status_t HSP_SEQ_STREAM_Disable(hsp_core_handle_t *hmw);

hsp_core_status_t HSP_SEQ_EVENT_SetConfig_Trigger(hsp_core_handle_t *hmw, hsp_seq_event_t evt_id,
                                                  const hsp_seq_event_trigger_config_t *p_config);
hsp_core_status_t HSP_SEQ_EVENT_SetConfig_CSEG(hsp_core_handle_t *hmw, hsp_seq_event_t evt_id,
                                               hsp_seq_event_sync_tcu_t tcu_sync);
hsp_core_status_t HSP_SEQ_EVENT_SetConfig_SPE(hsp_core_handle_t *hmw, hsp_seq_event_t evt_id,
                                              hsp_seq_event_sync_tcu_t tcu_sync);

/* Event Control -------------------------------------------------------------*/
hsp_core_status_t HSP_SEQ_EVENT_Enable(hsp_core_handle_t *hmw, uint32_t events_mask);
hsp_core_status_t HSP_SEQ_EVENT_Disable(hsp_core_handle_t *hmw, uint32_t events_mask);
uint32_t HSP_SEQ_EVENT_GetStatus(hsp_core_handle_t *hmw);

hsp_core_status_t HSP_SEQ_EVENT_Trig_CSEG(hsp_core_handle_t *hmw, uint32_t events_mask);
hsp_core_status_t HSP_SEQ_EVENT_PollForPending(hsp_core_handle_t *hmw, uint32_t events_mask, uint32_t timeout_ms);

/**
  * @}
  */

/** @defgroup HSP_PROCLIST_Exported_Functions_Group3 HSP Stream Buffer Data Management
  * @{
  */
volatile uint32_t *HSP_SEQ_STREAM_GetBufferAddress(hsp_core_handle_t *hmw, uint32_t stream_buffer_id);

/* IT mode ------------------------------------------------------------- */
#if defined(USE_HSP_ENGINE_STREAM_BUFFER) && (USE_HSP_ENGINE_STREAM_BUFFER == 1U)
hsp_core_status_t HSP_SEQ_STREAM_Buffer_Start_IT(hsp_core_handle_t *hmw, uint32_t stream_buffer_id, const int32_t *p_buffer, uint32_t buffer_size);
#endif /* USE_HSP_ENGINE_STREAM_BUFFER */

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

/**
  * @}
  */

#ifdef __cplusplus
}
#endif

#endif /* HSP_PROCLIST_H */
