/**
 ******************************************************************************
 * @file    dpu.h
 * @author  STMicroelectronics - AIS - MCD Team
 * @version $Version$
 * @date    $Date$
 * @brief   Configure the getting started functionality
 *
 * Each logic module of the application should define a DEBUG control byte
 * used to turn on/off the log for the module.
 *
 *******************************************************************************
 * @attention
 *
 * Copyright (c) 2026 STMicroelectronics
 * All rights reserved.
 *
 * This software is licensed under terms that can be found in the LICENSE file
 * in the root directory of this software component.
 * If no LICENSE file comes with this software, it is provided AS-IS.
 *******************************************************************************
 */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef DPU_H_
#define DPU_H_

#ifdef __cplusplus
extern "C" {
#endif

typedef enum
{
  DPU_OK       = 0x00,
  DPU_ERROR    = 0x01,
} DPU_StatusTypeDef;

#ifdef __cplusplus
}
#endif

#endif /* DPU_H_ */

