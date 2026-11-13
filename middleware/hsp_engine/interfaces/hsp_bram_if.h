/**
  ******************************************************************************
  * @file    hsp_bram_if.h
  * @brief   Header file for hsp_bram_if.c.
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

#ifndef HSP_BRAM_IF_H
#define HSP_BRAM_IF_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* Includes ------------------------------------------------------------------*/
#include "hsp_conf.h"
#include "hsp_engine_rsrc_map.h"
#include "interface.h"
#include "hsp_bram.h"

/** @addtogroup HSP_ENGINE
  * @{
  */

/** @defgroup HSP_INTERFACES HSP Interfaces
  * @{
  */

/** @defgroup HSP_BRAM_IF HSP BRAM Manager Interface
  * @{
  */

/* Exported constants --------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/
/**
  * @brief  Filter state structure
  */
typedef struct
{
  uint32_t dirCmd;  /**< Direct command */
  uint32_t addrHsp; /**< State buffer address in HSP memory */
  float32_t *addr;  /**< Buffer address */
  float32_t *ptr;   /**< Current pointer position */
  uint32_t size;    /**< Contains information according filter type */
} hsp_hw_if_filter_state_t;

/**
  * @brief  FIR Decimate Filter state structure
  */
typedef struct
{
  uint32_t dirCmd;     /**< Direct command */
  uint32_t addrHsp;    /**< State buffer address in HSP memory */
  float32_t *addr;     /**< Buffer address */
  float32_t *ptr;      /**< Current pointer position */
  uint32_t size;       /**< Contains information according filter type */
  uint32_t firstLoop;  /**<  Number of iteration to compute state values */
  uint32_t secondLoop; /**< Number of iteration to compute remaining data */
} hsp_hw_if_fir_decimate_filter_state_t;

/* Exported functions --------------------------------------------------------*/
/** @defgroup HSP_BRAM_IF_Exported_Functions HSP_BRAM_IF Exported Functions
  * @{
  */
hsp_if_status_t HSP_BRAM_IF_Init(hsp_bram_handle_t *hhsp_bram, void *hdriver);
void HSP_BRAM_IF_DeInit(hsp_bram_handle_t *hhsp_bram);
void *HSP_BRAM_IF_Malloc(hsp_bram_handle_t *hhsp_bram, uint32_t alloc_size_in_word, hsp_bram_allocation_t area);
uint32_t HSP_BRAM_IF_GetFreeSize(hsp_bram_handle_t *hhsp_bram, hsp_bram_allocation_t area);
hsp_if_status_t HSP_BRAM_IF_SetPopAddress(hsp_bram_handle_t *hhsp_bram, uint32_t *pop, uint32_t addr);
hsp_filter_state_identifier_t HSP_BRAM_IF_MallocStateBuffer_Fir(hsp_bram_handle_t *hhsp_bram, uint32_t nbTaps,
                                                                uint32_t nbSamples, hsp_bram_allocation_t area);
hsp_filter_state_identifier_t HSP_BRAM_IF_MallocStateBuffer_FirDecimate(hsp_bram_handle_t *hhsp_bram, uint32_t nbTaps,
                                                                        uint32_t nbSamples, uint32_t decimFactor,
                                                                        hsp_bram_allocation_t area);
hsp_filter_state_identifier_t HSP_BRAM_IF_MallocStateBuffer_BiquadCascadeDf1(hsp_bram_handle_t *hhsp_bram,
                                                                             uint32_t nbStages,
                                                                             hsp_bram_allocation_t area);
hsp_filter_state_identifier_t HSP_BRAM_IF_MallocStateBuffer_BiquadCascadeDf2t(hsp_bram_handle_t *hhsp_bram,
                                                                              uint32_t nbStages,
                                                                              hsp_bram_allocation_t area);
hsp_filter_state_identifier_t HSP_BRAM_IF_MallocStateBuffer_Lms(hsp_bram_handle_t *hhsp_bram, uint32_t nbTaps,
                                                                hsp_bram_allocation_t area);
hsp_filter_state_identifier_t HSP_BRAM_IF_MallocStateBuffer_IirLattice(hsp_bram_handle_t *hhsp_bram, uint32_t nbStages,
                                                                       hsp_bram_allocation_t area);
hsp_filter_state_identifier_t HSP_BRAM_IF_MallocStateBuffer_IirDf1(hsp_bram_handle_t *hhsp_bram, uint32_t nbStages,
                                                                   hsp_bram_allocation_t area);
#if defined(__HSP_DMA__)
hsp_filter_state_identifier_t HSP_BRAM_IF_MallocStateBuffer_Iir4p4z(hsp_bram_handle_t *hhsp_bram,
                                                                    hsp_bram_allocation_t area);
hsp_filter_state_identifier_t HSP_BRAM_IF_MallocStateBuffer_Iir5p5z(hsp_bram_handle_t *hhsp_bram,
                                                                    hsp_bram_allocation_t area);
#endif /* __HSP_DMA__ */
hsp_filter_state_identifier_t HSP_BRAM_IF_MallocStateBuffer_Iir3p3z(hsp_bram_handle_t *hhsp_bram,
                                                                    hsp_bram_allocation_t area);
hsp_filter_state_identifier_t HSP_BRAM_IF_MallocStateBuffer_Iir2p2z(hsp_bram_handle_t *hhsp_bram,
                                                                    hsp_bram_allocation_t area);
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

#endif /* HSP_BRAM_IF_H */
