/**
  ******************************************************************************
  * @file    hsp_memcpy.c
  * @brief   This file implements the optimized memcpy function
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
#include <string.h>
#include "hsp_memcpy.h"

/** @addtogroup HSP_ENGINE
  * @{
  */

/** @addtogroup HSP_CORE
  * @{
  */

/** @addtogroup HSP_UTILITIES
  * @{
  */

/** @addtogroup HSP_MEMCPY_Exported_Functions
  * @{
  */
extern void st_hsp_memcpy32(int8_t *pDst, int8_t *pSrc, uint32_t blockSize);

/**
  * @brief Copies a vector into another vector.
  * @param pDst      Pointer to output vector.
  * @param pSrc      Pointer to input vector.
  * @param blockSize length of the output vector.
  */
void *stm32_hsp_memcpy(void *pDst, const void *pSrc, uint32_t blockSize)
{
  /* trivial sanity check */
  if ((pSrc == pDst) || (blockSize == 0))
  {
    return pDst;
  }

  int8_t *pDst_int = (int8_t *)pDst;
  int8_t *pSrc_int = (int8_t *)pSrc;

  /* Handle buffers overlapping when address of dst is > address of src */
  const int8_t *pSrcEnd = pSrc_int + blockSize;
  if ((pDst_int > pSrc_int) && (pDst_int < pSrcEnd))
  {
    pDst_int += blockSize;
    while (pSrcEnd > pSrc_int)
    {
      *(--pDst_int) = *(--pSrcEnd);
    }
    return pDst;
  }

  if (blockSize < 4)
  {
    while (blockSize-- > 0)
    {
      __asm volatile("ldrb r3, [%[in]], #1\n\t"
                     "strb r3, [%[out]], #1\n\t"
                     : [out] "+r"(pDst_int), [in] "+r"(pSrc_int) :: "r3");
    }
    return pDst;
  }

  intptr_t pDst_offset = ((intptr_t) pDst_int) & 0x3;
  intptr_t pSrc_offset = ((intptr_t) pSrc_int) & 0x3;
  int32_t alignmentBytes = (4 - pDst_offset) % 4;

  blockSize -= alignmentBytes;

  while (alignmentBytes-- > 0)
  {
    __asm volatile("ldrb r3, [%[in]], #1\n\t"
                   "strb r3, [%[out]], #1\n\t"
                   : [out] "+r"(pDst_int), [in] "+r"(pSrc_int) :: "r3");
  }

  if (pDst_offset == pSrc_offset)
  {
    /* Both input and output are 32 bits aligned */
    st_hsp_memcpy32(pDst_int, pSrc_int, blockSize);
  }
  else
  {
    memcpy(pDst_int, pSrc_int, blockSize);
  }

  return pDst;
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

/**
  * @}
  */
