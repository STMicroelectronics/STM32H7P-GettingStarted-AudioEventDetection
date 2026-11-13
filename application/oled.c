/**
  ******************************************************************************
  * @file           oled.c
  * @brief          OLED display implementation.
  ******************************************************************************
  */

#include "oled.h"
#include "mx_st7315.h"
#include <string.h>

/* Application-owned frame buffer (ST7315_COLUMN_NUMBER * ST7315_PAGE_NUMBER =
   1024 bytes) */
static uint8_t frame_buffer[ST7315_FRAME_BUFFER_SIZE];

/* ST7315 instance */
static st7315_obj_t *p_oled_obj;
static uint32_t splash_tick;

static void draw_pixel(uint8_t *fb, uint16_t xpos, uint16_t ypos, uint8_t color);
static void draw_mono_image(uint8_t *fb, const uint8_t *image, uint16_t width, uint16_t height);

/**
 * @brief Displays the splash image and prevents pictogram updates temporarily.
 * @param p_image Pointer to the monochrome image data.
 * @param time_ms Splash display duration in milliseconds.
 * @return 1 if the pictogram is displayed or deferred successfully, otherwise 0.
 */
int oled_load_splash_screen(const uint8_t *p_image, uint32_t time_ms)
{
  int ret = oled_load_pict(p_image);
  splash_tick = time_ms + HAL_GetTick();
  return ret;
}

/**
 * @brief Displays a monochrome pictogram on the OLED.
 * @param p_image Pointer to the monochrome image data.
 * @return 1 if the pictogram is synchronized successfully, otherwise 0.
 */
int oled_load_pict(const uint8_t *p_image)
{
  if (HAL_GetTick() > splash_tick)
  {
    draw_mono_image(frame_buffer, p_image, ST7315_PIXEL_WIDTH, ST7315_PIXEL_HEIGHT);

    if (st7315_synchronize(p_oled_obj) != ST7315_OK)
    {
      return 0;
    }
  }
  return 1;
}

/**
 * @brief Initializes the OLED controller and its frame buffer.
 * @return 1 if the OLED controller is initialized successfully, otherwise 0.
 */
int oled_init(void)
{
  p_oled_obj = mx_st7315_0_getobject();

  if (st7315_init(p_oled_obj, ST7315_0) != ST7315_OK)
  {
    goto oled_init_exit;
  }

  if (st7315_set_frame_buffer(p_oled_obj, frame_buffer) != ST7315_OK)
  {
    goto oled_init_exit;
  }

  (void)memset(frame_buffer, 0x00U, sizeof(frame_buffer));

  if (st7315_synchronize(p_oled_obj) != ST7315_OK)
  {
    goto oled_init_exit;
  }

  return 1;
oled_init_exit:
  return 0;
}

/**
 * @brief Clears and deinitializes the OLED controller.
 * @return 1 if the OLED controller is deinitialized successfully, otherwise 0.
 */
int oled_deinit(void)
{
  (void)memset(frame_buffer, 0x00U, sizeof(frame_buffer));
  if (st7315_synchronize(p_oled_obj) != ST7315_OK)
  {
    goto oled_deinit_exit;
  }
  if (st7315_deinit(p_oled_obj) != ST7315_OK)
  {
    goto oled_deinit_exit;
  }
  return 1;
oled_deinit_exit:
  return 0;
}
/* The ST7315 stores pixels in pages: each byte covers 8 vertically stacked pixels. */
/**
 * @brief Sets or clears one pixel in the OLED frame buffer.
 * @param fb Pointer to the frame buffer.
 * @param xpos Horizontal pixel coordinate.
 * @param ypos Vertical pixel coordinate.
 * @param color Pixel color.
 */
static void draw_pixel(uint8_t *fb, uint16_t xpos, uint16_t ypos, uint8_t color)
{
  if (color == ST7315_COLOR_WHITE)
  {
    fb[xpos + (ypos / 8U) * ST7315_PIXEL_WIDTH] |= (uint8_t)(1U << (ypos % 8U));
  }
  else
  {
    fb[xpos + (ypos / 8U) * ST7315_PIXEL_WIDTH] &= (uint8_t)(~(1U << (ypos % 8U)));
  }
}

/* Cleared bits in the raw image are drawn lit on a black background. */
/**
 * @brief Converts a packed monochrome image into the OLED frame buffer.
 * @param fb Pointer to the destination frame buffer.
 * @param image Pointer to the packed source image.
 * @param width Image width in pixels.
 * @param height Image height in pixels.
 */
static void draw_mono_image(uint8_t *fb, const uint8_t *image, uint16_t width, uint16_t height)
{
  uint16_t bytes_per_row = (uint16_t)(width / 8U);

  for (uint16_t y = 0U; y < height; y++)
  {
    for (uint16_t x = 0U; x < width; x++)
    {
      uint8_t bit = (uint8_t)((image[(y * bytes_per_row) + (x / 8U)] >>
                               (7U - (x % 8U))) & 0x01U);
      draw_pixel(fb, x, y,
                 (bit == 0U) ? ST7315_COLOR_WHITE : ST7315_COLOR_BLACK);
    }
  }
}
