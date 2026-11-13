/**
  ******************************************************************************
  * @file    : gs_utils.h
  * @brief   : Utility Module
  * @version $Version$
  * @date    $Date$
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

#ifndef GS_UTILS_H
#define GS_UTILS_H

/** @brief Prints the build/version UART header. */
extern void print_app_header(void);
/** @brief Displays the processing start header. */
extern void print_header(void);
/** @brief Displays the processing stop footer. */
extern void print_footer(void);
/** @brief Initializes CPU usage statistics. */
extern void init_cpu_stats(void);
/** @brief Displays the CPU usage summary. */
extern void print_cpu_stats_summary(void);
/**
 * @brief Displays the highest-confidence AI classification.
 * @param p_out Classification confidence array.
 * @param classes Classification labels.
 */
extern void print_ai_classes_output(float *p_out);
/** @brief Displays the system configuration. */
extern void print_system_setting(void);
/** @brief Updates the periodic status menu. */
extern void print_menu(void);

#endif /* GS_UTILS_H */
