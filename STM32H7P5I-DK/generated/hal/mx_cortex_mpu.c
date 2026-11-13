/**
  ******************************************************************************
  * @file           : mx_cortex_mpu.c
  * @brief          : CORTEX_MPU Peripheral initialization
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2026 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the mx_stm32h7pxx_hal_drivers_license.md file
  * in the same directory as the generated code.
  * If no mx_stm32h7pxx_hal_drivers_license.md file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "mx_cortex_mpu.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private functions prototype------------------------------------------------*/
/* Exported variables by reference--------------------------------------------*/
/******************************************************************************/
/* Exported functions for CORTEX_MPU in HAL layer */
/******************************************************************************/

system_status_t mx_cortex_mpu_init(void)
{
  /* Disables the MPU */
  HAL_CORTEX_MPU_Disable();

  /*
     Initializes and configures the MPU Region
  */
  hal_cortex_mpu_region_config_t p_region_config = {0};

  p_region_config.base_addr = 0x30018000;
  p_region_config.size = HAL_CORTEX_MPU_REGION_SIZE_128KB;
  p_region_config.access_attr = HAL_CORTEX_MPU_REGION_ALL_RW;
  p_region_config.mem_attr = HAL_CORTEX_MPU_NORMAL_MEM_SHAREABLE_IO_NCACHEABLE;
  p_region_config.exec_attr = HAL_CORTEX_MPU_EXECUTION_ATTR_ENABLE;
  p_region_config.sub_region = HAL_CORTEX_MPU_SUB_REGION_ENABLE_ALL;
  HAL_CORTEX_MPU_SetConfigRegion(HAL_CORTEX_MPU_REGION_0, &p_region_config);

  HAL_CORTEX_MPU_EnableRegion(HAL_CORTEX_MPU_REGION_0);

  /* Enables the MPU */
  HAL_CORTEX_MPU_Enable(HAL_CORTEX_MPU_HARDFAULT_NMI_ENABLE, HAL_CORTEX_MPU_ACCESS_FAULT_ONLY_PRIV);

  return SYSTEM_OK;
}

void mx_cortex_mpu_deinit(void)
{
  /* Disables the MPU and MPU regions*/
  HAL_CORTEX_MPU_Disable();

  HAL_CORTEX_MPU_DisableRegion(HAL_CORTEX_MPU_REGION_0);
  HAL_CORTEX_MPU_DisableRegion(HAL_CORTEX_MPU_REGION_1);
  HAL_CORTEX_MPU_DisableRegion(HAL_CORTEX_MPU_REGION_2);
  HAL_CORTEX_MPU_DisableRegion(HAL_CORTEX_MPU_REGION_3);
  HAL_CORTEX_MPU_DisableRegion(HAL_CORTEX_MPU_REGION_4);
  HAL_CORTEX_MPU_DisableRegion(HAL_CORTEX_MPU_REGION_5);
  HAL_CORTEX_MPU_DisableRegion(HAL_CORTEX_MPU_REGION_6);
  HAL_CORTEX_MPU_DisableRegion(HAL_CORTEX_MPU_REGION_7);
  HAL_CORTEX_MPU_DisableRegion(HAL_CORTEX_MPU_REGION_8);
  HAL_CORTEX_MPU_DisableRegion(HAL_CORTEX_MPU_REGION_9);
  HAL_CORTEX_MPU_DisableRegion(HAL_CORTEX_MPU_REGION_10);
  HAL_CORTEX_MPU_DisableRegion(HAL_CORTEX_MPU_REGION_11);
  HAL_CORTEX_MPU_DisableRegion(HAL_CORTEX_MPU_REGION_12);
  HAL_CORTEX_MPU_DisableRegion(HAL_CORTEX_MPU_REGION_13);
  HAL_CORTEX_MPU_DisableRegion(HAL_CORTEX_MPU_REGION_14);
  HAL_CORTEX_MPU_DisableRegion(HAL_CORTEX_MPU_REGION_15);

  /*
     Deinitializes and configures the MPU Region to default
  */
  hal_cortex_mpu_region_config_t p_region_config = {0};

  p_region_config.base_addr = 0x00000000;
  p_region_config.size = HAL_CORTEX_MPU_REGION_SIZE_256B;
  p_region_config.access_attr = HAL_CORTEX_MPU_REGION_ONLY_PRIV_RW;
  p_region_config.mem_attr = HAL_CORTEX_MPU_SO_MEM_SHAREABLE;
  p_region_config.exec_attr = HAL_CORTEX_MPU_EXECUTION_ATTR_ENABLE;
  p_region_config.sub_region = HAL_CORTEX_MPU_SUB_REGION_ENABLE_ALL;

  HAL_CORTEX_MPU_SetConfigRegion(HAL_CORTEX_MPU_REGION_0, &p_region_config);
  HAL_CORTEX_MPU_SetConfigRegion(HAL_CORTEX_MPU_REGION_1, &p_region_config);
  HAL_CORTEX_MPU_SetConfigRegion(HAL_CORTEX_MPU_REGION_2, &p_region_config);
  HAL_CORTEX_MPU_SetConfigRegion(HAL_CORTEX_MPU_REGION_3, &p_region_config);
  HAL_CORTEX_MPU_SetConfigRegion(HAL_CORTEX_MPU_REGION_4, &p_region_config);
  HAL_CORTEX_MPU_SetConfigRegion(HAL_CORTEX_MPU_REGION_5, &p_region_config);
  HAL_CORTEX_MPU_SetConfigRegion(HAL_CORTEX_MPU_REGION_6, &p_region_config);
  HAL_CORTEX_MPU_SetConfigRegion(HAL_CORTEX_MPU_REGION_7, &p_region_config);
  HAL_CORTEX_MPU_SetConfigRegion(HAL_CORTEX_MPU_REGION_8, &p_region_config);
  HAL_CORTEX_MPU_SetConfigRegion(HAL_CORTEX_MPU_REGION_9, &p_region_config);
  HAL_CORTEX_MPU_SetConfigRegion(HAL_CORTEX_MPU_REGION_10, &p_region_config);
  HAL_CORTEX_MPU_SetConfigRegion(HAL_CORTEX_MPU_REGION_11, &p_region_config);
  HAL_CORTEX_MPU_SetConfigRegion(HAL_CORTEX_MPU_REGION_12, &p_region_config);
  HAL_CORTEX_MPU_SetConfigRegion(HAL_CORTEX_MPU_REGION_13, &p_region_config);
  HAL_CORTEX_MPU_SetConfigRegion(HAL_CORTEX_MPU_REGION_14, &p_region_config);
  HAL_CORTEX_MPU_SetConfigRegion(HAL_CORTEX_MPU_REGION_15, &p_region_config);
}