/**
  ******************************************************************************
  * @file    : gs_utils.h
  * @brief   : Utility Module
  * @version $Version$
  * @date    $Date$
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

#ifndef GS_AUDIO_SENSING_UTILS_H
#define GS_AUDIO_SENSING_UTILS_H

void PrintHeader(void);
void PrintFooter(void);
void InitCpuStats(void);
void PrintCpuStatsSummary(void);
void PrintAIClassesOutput(float *p_out, const char ** classes);
void PrintSystemSetting(void);
void PrintMenu(void);

#endif /* GS_AUDIO_SENSING_UTILS_H */
