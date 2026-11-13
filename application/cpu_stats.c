/**
 ******************************************************************************
 * @file    cpu_stats.c
 * @author  STMicroelectronics AIS application team
 * @version $Version$
 * @date    $Date$
 * @brief   utility to collect satistics
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

/* Includes ------------------------------------------------------------------*/
#include "cpu_stats.h"
#include "ai_device_adaptor.h"

#include <string.h>
#include <float.h>
#include <stdint.h>

typedef struct
{
  float latest;
  unsigned int cnt;
  float sum;
  float min;
  float max;
} time_stats_t;

static time_stats_t time_stats_buf[TIME_STAT_NB_ENTRIES];
static uint32_t time_from_init_in_ms;

/**
 * @brief Initializes all timing statistics.
 */
void time_stats_init(void)
{
  /* Clear buffer */
  memset(time_stats_buf, 0, sizeof(time_stats_buf));
  for (int i = 0; i < TIME_STAT_NB_ENTRIES; i++)
  {
    time_stats_buf[i].min = FLT_MAX;
  }
  time_from_init_in_ms = HAL_GetTick();
}

/**
 * @brief Resets one timing statistic entry.
 * @param idx Index of the statistic entry.
 */
void time_stats_reset(unsigned int idx)
{
  /* Clear buffer */
  memset(&time_stats_buf[idx], 0, sizeof(time_stats_t));
  time_stats_buf[idx].min = FLT_MAX;
}

/**
 * @brief Stores a timing measurement.
 * @param idx Index of the statistic entry.
 * @param time_in_ms Measured duration in milliseconds.
 */
void time_stats_store(unsigned int idx, float time_in_ms)
{
  ASSERT_DBG_PARAM(idx < TIME_STAT_NB_ENTRIES);
  time_stats_buf[idx].latest = time_in_ms;
  time_stats_buf[idx].sum   += time_in_ms;
  time_stats_buf[idx].cnt++;
  if (time_in_ms < time_stats_buf[idx].min)
  {
    time_stats_buf[idx].min = time_in_ms;
  }
  if (time_in_ms > time_stats_buf[idx].max)
  {
    time_stats_buf[idx].max = time_in_ms;
  }
}
/**
 * @brief Returns the elapsed time since statistics initialization.
 * @return Elapsed time in milliseconds.
 */
float time_stats_get_runtime(void)
{
  return ((float)(HAL_GetTick() - time_from_init_in_ms));
}

/**
 * @brief Returns the accumulated duration for an entry.
 * @param idx Index of the statistic entry.
 * @return Accumulated duration in milliseconds.
 */
float time_stats_get_sum(unsigned int idx)
{
  return (time_stats_buf[idx].sum);
}
/**
 * @brief Returns the average duration for an entry.
 * @param idx Index of the statistic entry.
 * @return Average duration in milliseconds, or zero if unused.
 */
float time_stats_get_avg(unsigned int idx)
{
    return (time_stats_buf[idx].cnt == 0) ? 0.0F :
      time_stats_buf[idx].sum / time_stats_buf[idx].cnt;
}
/**
 * @brief Returns the minimum duration for an entry.
 * @param idx Index of the statistic entry.
 * @return Minimum duration in milliseconds, or zero if unused.
 */
float time_stats_get_min(unsigned int idx)
{
  return (time_stats_buf[idx].cnt == 0) ? 0.0F : time_stats_buf[idx].min;
}
/**
 * @brief Returns the maximum duration for an entry.
 * @param idx Index of the statistic entry.
 * @return Maximum duration in milliseconds.
 */
float time_stats_get_max(unsigned int idx)
{
  return (time_stats_buf[idx].max);
}
/**
 * @brief Returns the latest duration for an entry.
 * @param idx Index of the statistic entry.
 * @return Latest duration in milliseconds.
 */
float time_stats_get_latest(unsigned int idx)
{
  return (time_stats_buf[idx].latest);
}
/**
 * @brief Returns the number of measurements stored for an entry.
 * @param idx Index of the statistic entry.
 * @return Number of stored measurements.
 */
unsigned int time_stats_get_cnt(unsigned int idx)
{
  return (time_stats_buf[idx].cnt);
}
