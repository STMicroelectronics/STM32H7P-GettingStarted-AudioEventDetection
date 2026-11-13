/**
  ******************************************************************************
  * file           : app_aed.h
  * brief          : Header for app_aed.c.
  *                  This file contains app_aed-specific declarations to 
  *                  interface with main().
  ******************************************************************************
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
#ifndef APP_AED_H
#define APP_AED_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* Exported types ------------------------------------------------------------*/
typedef volatile enum
{
  EXEC_STATUS_ERROR   = -1,                    /* problem encountered         */
  EXEC_STATUS_UNKNOWN = 0,                     /* default value               */
  EXEC_STATUS_INIT_OK = 1,                     /* app_init ran as expected    */
  EXEC_STATUS_OK      = 2,                     /* application ran as expected */
  EXEC_STATUS_EXIT    = 3                      /* application requested exit  */
} app_status_t;

/**
 * @brief Initializes the application.
 * @return Application initialization status.
 */
app_status_t app_init(void);

/**
 * @brief Processes one application iteration.
 * @return Application processing status.
 */
app_status_t app_process(void);

/**
 * @brief De-initializes the application.
 * @return Application de-initialization status.
 */
app_status_t app_deinit(void);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* APP_AED_H */
