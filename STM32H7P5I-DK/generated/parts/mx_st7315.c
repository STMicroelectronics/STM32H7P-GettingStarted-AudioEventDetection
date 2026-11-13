/**
  ******************************************************************************
  * file           : mx_st7315.c
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

/* Includes ------------------------------------------------------------------*/
#include "mx_st7315.h"

static st7315_obj_t  st7315_0_obj;

/**
  * @brief initialize the IO layer.
  * @param  pio      pointer to the part IO structure.
  * @retval error status.
  */
int32_t st7315_io_init(st7315_io_t *pio)
{
  /* Part Status */
  int32_t ret = 0;

  switch (pio->id)
  {
    case ST7315_0:
      pio->phspi    = ST7315_0_SPI_GETHANDLE();
      pio->rst_port = ST7315_0_RST_GPIO_PORT;
      pio->rst_pin  = ST7315_0_RST_GPIO_PIN;
      pio->cs_port  = ST7315_0_CS_GPIO_PORT;
      pio->cs_pin   = ST7315_0_CS_GPIO_PIN;
      pio->dc_port  = ST7315_0_DC_GPIO_PORT;
      pio->dc_pin   = ST7315_0_DC_GPIO_PIN;
      break;
 
 
    default:
      /* Error -- Unknown ID */
      ret = -1;
      break;
  }

  return ret;
}

/**
  * @brief Function to retrieve the Part object ST7315_0.
  * @retval part object.
  */
st7315_obj_t *mx_st7315_0_getobject(void)
{
  return &st7315_0_obj;
}
 
 
