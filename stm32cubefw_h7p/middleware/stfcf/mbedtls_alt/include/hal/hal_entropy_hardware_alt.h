/**
  ******************************************************************************
  * @file    entropy_hardware_alt.h
  * @brief   Header for entropy_hardware_alt module
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
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef HAL_ENTROPY_HARDWARE_ALT_H
#define HAL_ENTROPY_HARDWARE_ALT_H

/* Includes ------------------------------------------------------------------*/
#include "mbedtls/entropy.h"

#ifdef __cplusplus
extern "C"
{
#endif /* __cplusplus */
/* Exported functions ------------------------------------------------------- */
/**
  * brief :  Entropy poll callback for a hardware source (provided to mbed crypto)
  * data  :  unused parameter (can be NULL)
  * output:  the random bytes
  * len   :  the requested number of random bytes
  * olen  :  the actual number of random bytes in output
  * retval:  0 in case of success, the entropy source failure code from entropy.h in case of failure
  *
  * note  :  Accepts NULL as its first argument (unused).
  */
int32_t mbedtls_hardware_poll(void *data, unsigned char *output, size_t len, size_t *olen);

#ifdef __cplusplus
} /* extern "C" */
#endif /* __cplusplus */

#endif /* HAL_ENTROPY_HARDWARE_ALT_H */
