/**
  ******************************************************************************
  * @file    hsp_bram_if.c
  * @author  GPM Application Team
  * @brief   This file implements the service provide by the HSP BRAM Interface
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
#include "hsp_def.h"
#include "interface.h"
#include "hsp_bram.h"
#include "hsp_bram_if.h"
#include "hsp_conf.h"
#include "hsp_if_conf.h"
#include "hsp_fw_def_generic.h"

#if defined(__ARMCC_VERSION) && (__ARMCC_VERSION >= 6100100)
#elif defined (__GNUC__)
extern char __section_static_hsp_data_bram_start__;
extern char __section_static_hsp_data_bram_end__;
#elif defined (__ICCARM__)
#pragma section="HSP_DATA_BRAM"
#endif /* __ICCARM__ */

#ifdef GCC_BUILD

#endif /* GCC_BUILD */

/** @addtogroup HSP_ENGINE
  * @{
  */

/** @addtogroup HSP_INTERFACES
  * @{
  */

/** @addtogroup HSP_BRAM_IF
  * @{
  */

/* Private types -----------------------------------------------------------*/
/** @defgroup HSP_BRAM_IF_Private_Types HSP_BRAM_IF Private Types
  * @{
  */
/**
  * @}
  */

/* Private constants ---------------------------------------------------------*/
/** @defgroup HSP_BRAM_IF_Private_Constants HSP_BRAM_IF Private Constants
  * @{
  */
#define IF_SIZEOF_HEADER_STATE_BUFF  20U  /*!< Sizeof struct hsp_hw_if_filter_state_t */
#define IF_SIZEOF_HEADER_FIR_DECIM_STATE_BUFF  28U  /*!< Sizeof struct hsp_hw_if_filter_state_t */
/**
  * @}
  */

/* Private macros -------------------------------------------------------------*/
/** @defgroup HSP_BRAM_IF_Private_Macros HSP_BRAM_IF Private Macros
  * @{
  */

/**
  * @}
  */

/* Private functions ---------------------------------------------------------*/
static hsp_hw_if_filter_state_t *HSP_BRAM_IF_MallocStateBuffer(hsp_bram_handle_t *hhsp_bram, uint32_t stateSize,
                                                               uint32_t info, hsp_bram_allocation_t area);

/* Exported functions --------------------------------------------------------*/
/** @addtogroup HSP_BRAM_IF_Exported_Functions
  * @{
  */
/**
  * @brief Returns the free space in word in MEMAB.
  * @param  hmw      HSP handle
  * @retval          Number of free word, 0 if error
  */
uint32_t HSP_BRAM_IF_GetFreeSize(hsp_bram_handle_t *hhsp_bram, hsp_bram_allocation_t area)
{
  /*
    User Code
  */
}

/**
  * @brief  Initialize BRAM interface.
  * @param  hhsp_bram  HSP BRAM handle
  * @param  hdriver    Pointer the HSP Driver
  * @retval            HSP_IF_OK  Init success
  *                    HSP_IF_ERROR Init failure
  */
hsp_if_status_t HSP_BRAM_IF_Init(hsp_bram_handle_t *hhsp_bram, void *hdriver)
{
  /* User code */
  return HSP_IF_OK;
}

/**
  * @brief  DeInitialize timer.
  */
void HSP_BRAM_IF_DeInit(hsp_bram_handle_t *hhsp_bram)
{
  /* User code */
}

/**
  * @brief  Allocation in BRAM_AB.
  * @param  hhsp_bram            HSP BRAM handle
  * @param  alloc_size_in_word   Number of word to allocate
  * @param area                  HSP_BRAM_ALLOCATION_DEFAULT: allocation in all BRAM
  *                              HSP_BRAM_ALLOCATION_PERSISTENT: allocation in persistent memory
  * @retval                      NULL  Allocation failure
  *                              Address value if success
  */
void *HSP_BRAM_IF_Malloc(hsp_bram_handle_t *hhsp_bram, uint32_t alloc_size_in_word, hsp_bram_allocation_t area)
{
  /* User code */
}

/**
  * @brief Set value address in pointer of pointer in HSP memory mapping.
  * @param hhsp_bram   HSP BRAM handle
  * @param pop         Pointer of pointer
  * @param addr        Address to set in pointer of pointer
  * @retval            HSP_IF_OK : success
  */
hsp_if_status_t HSP_BRAM_IF_SetPopAddress(hsp_bram_handle_t *hhsp_bram, uint32_t *pop, uint32_t addr)
{
  /* User code */
}

/**
  * @brief Create FIR filter state in HSP internal memory.
  * @param hhsp_bram   HSP BRAM handle
  * @param nbTaps      Number of filter taps
  * @param nbSamples   Number of float elements to proceed
  * @param area        HSP_BRAM_ALLOCATION_DEFAULT: allocation in all BRAM
  *                    HSP_BRAM_ALLOCATION_PERSISTENT: allocation in persistent memory
  * @retval            If allocation succeed, returns identifier of the created filter state
  *                    otherwise returns 0
  */
hsp_filter_state_identifier_t HSP_BRAM_IF_MallocStateBuffer_Fir(hsp_bram_handle_t *hhsp_bram, uint32_t nbTaps,
                                                                uint32_t nbSamples, hsp_bram_allocation_t area)
{
  /* User code */
}

/**
  * @brief Create FIR DECIMATE filter state in HSP internal memory.
  * @param hhsp_bram    HSP BRAM handle
  * @param nbTaps       Number of filter taps
  * @param nbSamples    Number of float elements to proceed
  * @param decimFactor  Decimation factor
  * @param area         HSP_BRAM_ALLOCATION_DEFAULT: allocation in all BRAM
  *                     HSP_BRAM_ALLOCATION_PERSISTENT: allocation in persistent memory
  * @retval             If allocation succeed, returns identifier of the created filter state
  *                     otherwise returns 0
  */
hsp_filter_state_identifier_t HSP_BRAM_IF_MallocStateBuffer_FirDecimate(hsp_bram_handle_t *hhsp_bram, uint32_t nbTaps,
                                                                        uint32_t nbSamples, uint32_t decimFactor,
                                                                        hsp_bram_allocation_t area)
{
  /* User code */
}

/**
  * @brief Create BIQUAD Cascade Df1 filter state in HSP internal memory.
  * @param hhsp_bram      HSP BRAM handle
  * @param nbStages       Number of stage
  * @param area           HSP_BRAM_ALLOCATION_DEFAULT: allocation in all BRAM
  *                       HSP_BRAM_ALLOCATION_PERSISTENT: allocation in persistent memory
  * @retval               If allocation succeed, returns identifier of the created filter state
  *                       otherwise returns 0
  */
hsp_filter_state_identifier_t HSP_BRAM_IF_MallocStateBuffer_BiquadCascadeDf1(hsp_bram_handle_t *hhsp_bram,
                                                                             uint32_t nbStages,
                                                                             hsp_bram_allocation_t area)
{
  /* User code */
}

/**
  * @brief Create BIQUAD Cascade Df2T filter state in HSP internal memory.
  * @param hhsp_bram    HSP BRAM handle
  * @param nbStages     Number of stage
  * @param area         HSP_BRAM_ALLOCATION_DEFAULT: allocation in all BRAM
  *                     HSP_BRAM_ALLOCATION_PERSISTENT: allocation in persistent memory
  * @retval             If allocation succeed, returns identifier of the created filter state
  *                     otherwise returns 0
  */
hsp_filter_state_identifier_t HSP_BRAM_IF_MallocStateBuffer_BiquadCascadeDf2t(hsp_bram_handle_t *hhsp_bram,
                                                                              uint32_t nbStages,
                                                                              hsp_bram_allocation_t area)
{
  /* User code */
}

/**
  * @brief Create LMS filter state in HSP internal memory.
  * @param hhsp_bram     HSP BRAM handle
  * @param nbTaps        Number of filter taps
  * @param area          HSP_BRAM_ALLOCATION_DEFAULT: allocation in all BRAM
  *                      HSP_BRAM_ALLOCATION_PERSISTENT: allocation in persistent memory
  * @retval              If allocation succeed, returns identifier of the created filter state
  *                      otherwise returns 0
  */
hsp_filter_state_identifier_t HSP_BRAM_IF_MallocStateBuffer_Lms(hsp_bram_handle_t *hhsp_bram, uint32_t nbTaps,
                                                                hsp_bram_allocation_t area)
{
  /* User code */
}

/**
  * @brief Create IIR Lattice filter state in HSP internal memory.
  * @param hhsp_bram     HSP BRAM handle
  * @param nbStages      Number of stage
  * @param area          HSP_BRAM_ALLOCATION_DEFAULT: allocation in all BRAM
  *                      HSP_BRAM_ALLOCATION_PERSISTENT: allocation in persistent memory
  * @retval              If allocation succeed, returns identifier of the created filter state
  *                      otherwise returns 0
  */
hsp_filter_state_identifier_t HSP_BRAM_IF_MallocStateBuffer_IirLattice(hsp_bram_handle_t *hhsp_bram, uint32_t nbStages,
                                                                       hsp_bram_allocation_t area)
{
  /* User code */
}

/**
  * @brief Create IIR Df1 filter state in HSP internal memory.
  * @param hhsp_bram     HSP BRAM handle
  * @param nbStages      Number of stage
  * @param area          HSP_BRAM_ALLOCATION_DEFAULT: allocation in all BRAM
  *                      HSP_BRAM_ALLOCATION_PERSISTENT: allocation in persistent memory
  * @retval              If allocation succeed, returns identifier of the created filter state
  *                      otherwise returns 0
  */
hsp_filter_state_identifier_t HSP_BRAM_IF_MallocStateBuffer_IirDf1(hsp_bram_handle_t *hhsp_bram, uint32_t nbStages,
                                                                   hsp_bram_allocation_t area)
{
  /* User code */
}

/**
  * @brief Create IIR 3p3z filter state in HSP internal memory.
  * @param hhsp_bram     HSP BRAM handle
  * @param area          HSP_BRAM_ALLOCATION_DEFAULT: allocation in all BRAM
  *                      HSP_BRAM_ALLOCATION_PERSISTENT: allocation in persistent memory
  * @retval              If allocation succeed, returns identifier of the created filter state
  *                      otherwise returns 0
  */
hsp_filter_state_identifier_t HSP_BRAM_IF_MallocStateBuffer_Iir3p3z(hsp_bram_handle_t *hhsp_bram,
                                                                    hsp_bram_allocation_t area)
{
  /* User code */
}

/**
  * @brief Create IIR 2p2z filter state in HSP internal memory.
  * @param hhsp_bram     HSP BRAM handle
  * @param area          HSP_BRAM_ALLOCATION_DEFAULT: allocation in all BRAM
  *                      HSP_BRAM_ALLOCATION_PERSISTENT: allocation in persistent memory
  * @retval              If allocation succeed, returns identifier of the created filter state
  *                      otherwise returns 0
  */
hsp_filter_state_identifier_t HSP_BRAM_IF_MallocStateBuffer_Iir2p2z(hsp_bram_handle_t *hhsp_bram,
                                                                    hsp_bram_allocation_t area)
{
  /* User code */
}

/** @defgroup HSP_BRAM_IF_Private_Functions HSP_BRAM_IF Private Functions
  * @{
  */
/**
  * @brief Create filter state in HSP internal memory.
  * @param hhsp_bram     HSP BRAM handle.
  * @param stateSize     State size needed by filter
  * @param info          Information needed by FW depending of filter type
  * @param area          HSP_BRAM_ALLOCATION_DEFAULT: allocation in all BRAM
  *                      HSP_BRAM_ALLOCATION_PERSISTENT: allocation in persistent memory
  * @retval              If allocation succeed, returns a filter state structure
  *                      otherwise returns 0
  */
static hsp_hw_if_filter_state_t *HSP_BRAM_IF_MallocStateBuffer(hsp_bram_handle_t *hhsp_bram, uint32_t stateSize,
                                                               uint32_t info, hsp_bram_allocation_t area)
{
  /* User code */
}
/**
  * @}
  */
