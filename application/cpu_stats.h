/**
  ******************************************************************************
  * @file    cpu_stats.h
  * @version $Version$
  * @date    $Date$
  * @brief
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2026 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */


/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __CPU_STATS_H
#define __CPU_STATS_H

#ifdef __cplusplus
extern "C" {
#endif
 

/* Includes ------------------------------------------------------------------*/

/* Exported macro ------------------------------------------------------------*/
/* Define the maximum number of log entries */
#define TIME_STAT_PRE_PROC   (0)
#define TIME_STAT_AI_PROC    (1)
#define TIME_STAT_POST_PROC  (2)
#define TIME_STAT_TOT        (3)
#define TIME_STAT_NB_ENTRIES (TIME_STAT_TOT + 1)

/** @brief Initializes all timing statistics. */
void time_stats_init(void);
/** @brief Resets one timing statistic entry. @param idx Entry index. */
void time_stats_reset(unsigned int idx);
/** @brief Stores a timing measurement in milliseconds. @param idx Entry index. @param time_in_ms Measured duration. */
void time_stats_store(unsigned int idx, float time_in_ms);
/** @brief Returns elapsed time since initialization, in milliseconds. */
float time_stats_get_runtime(void);
/** @brief Returns the accumulated duration. @param idx Entry index. */
float time_stats_get_sum(unsigned int idx);
/** @brief Returns the average duration. @param idx Entry index. */
float time_stats_get_avg(unsigned int idx);
/** @brief Returns the minimum duration. @param idx Entry index. */
float time_stats_get_min(unsigned int idx);
/** @brief Returns the maximum duration. @param idx Entry index. */
float time_stats_get_max(unsigned int idx);
/** @brief Returns the latest duration. @param idx Entry index. */
float time_stats_get_latest(unsigned int idx);
/** @brief Returns the number of stored measurements. @param idx Entry index. */
unsigned int time_stats_get_cnt(unsigned int idx);

#ifdef __cplusplus
}
#endif

#endif /* __CPU_STATS_H */
