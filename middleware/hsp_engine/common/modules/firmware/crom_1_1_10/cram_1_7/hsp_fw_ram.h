/**
  ******************************************************************************
  * @file    hsp_fw_ram.h
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

#ifndef HSP_FW_RAM_H
#define HSP_FW_RAM_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* Includes ------------------------------------------------------------------*/
#include <stdint.h>

/* Exported Types ------------------------------------------------------------*/
typedef struct
{
  const uint8_t *p_binary;
  const uint32_t size_byte;
} hsp_fw_descriptor_t;

/* Exported Functions --------------------------------------------------------*/
const hsp_fw_descriptor_t *hsp_fw_getcram(void);
const hsp_fw_descriptor_t *hsp_fw_getdram(void);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* HSP_FW_RAM_H */