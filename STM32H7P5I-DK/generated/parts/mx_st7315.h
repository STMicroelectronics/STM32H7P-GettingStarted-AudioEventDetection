/**
  ******************************************************************************
  * file           : mx_st7315.h
  * brief          : Code generation for the ST7315 part driver.
  ******************************************************************************
  * attention
  *
  * Copyright (c) 2026 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the mx_st7315_part_drivers_license.md file
  * in the same directory as the generated code.
  * If no mx_st7315_part_drivers_license.md file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef MX_ST7315_H
#define MX_ST7315_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "st7315.h"
#include "mx_hal_def.h"

/* Exported macro ------------------------------------------------------------*/
/* Part Config ID */
#define ST7315_0                              0 /* Main label */
/* No label has been defined for this part driver instance,
 * so no alias is generated for ST7315_0 or mx_st7315_0_getobject(). */

/* Resource bindings */
/* Part interface Properties */
#define ST7315_0_SPI_GETHANDLE      mx_spi1_gethandle

#define ST7315_0_RST_GPIO_PORT          HAL_GPIOE
#define ST7315_0_RST_GPIO_PIN           HAL_GPIO_PIN_1

#define ST7315_0_CS_GPIO_PORT           HAL_GPIOG
#define ST7315_0_CS_GPIO_PIN            HAL_GPIO_PIN_4

#define ST7315_0_DC_GPIO_PORT           HAL_GPIOG
#define ST7315_0_DC_GPIO_PIN            HAL_GPIO_PIN_6
 
 

/* Functions to retrieve the part object */
st7315_obj_t *mx_st7315_0_getobject(void);
 
 

#ifdef __cplusplus
}
#endif

#endif /* MX_ST7315_H */
