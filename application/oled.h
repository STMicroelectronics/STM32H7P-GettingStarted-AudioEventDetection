/**
  ******************************************************************************
  * @file           oled.h
  * @brief          OLED display interface.
  ******************************************************************************
  */

#ifndef OLED_H
#define OLED_H

#include <stdint.h>

#ifdef __cplusplus
extern "C"
{
#endif

/**
 * @brief Initializes the OLED controller.
 * @return 1 on success, otherwise 0.
 */
int oled_init(void);

/**
 * @brief Displays the OLED splash image.
 * @param p_image Pointer to the image data.
 * @param time_ms Splash duration in milliseconds.
 * @return 1 if the pictogram is displayed or deferred successfully, otherwise 0.
 */
int oled_load_splash_screen(const uint8_t *p_image, uint32_t time_ms);

/**
 * @brief Displays an OLED pictogram.
 * @param p_image Pointer to the image data.
 * @return 1 if the pictogram is synchronized successfully, otherwise 0.
 */
int oled_load_pict(const uint8_t *p_image);

/**
 * @brief De-initializes the OLED controller.
 * @return 1 on success, otherwise 0.
 */
int oled_deinit(void);

#ifdef __cplusplus
}
#endif

#endif /* OLED_H */
