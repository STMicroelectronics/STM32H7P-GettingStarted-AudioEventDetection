/**
 * @file Helpers functions used for USART SW component
 * @author GPM Application Team
 * @license
 * Copyright (c) 2024 STMicroelectronics.
 * All rights reserved.
 *
 * This software is licensed under terms that can be found in the LICENSE file
 * in the root directory of this software component.
 * If no LICENSE file comes with this software, it is provided AS-IS.
 */

/**
 * Computes Minimal baudrate
 * @param {integer} input_clock USART input clock
 * @param {integer} prescaler USART prescaler
 * @returns {integer} Minimal baudrate computed
 */
function helper_usart_get_min_baudrate(input_clock, prescaler) {
  let result = [];
  try {
    console.log(
      `[INFO] helper_usart_get_min_baudrate: input_clock=${input_clock}, prescaler=${prescaler} `
    );

    /* USART/USART */
    result = Math.ceil(((input_clock * (16 / 8)) / (prescaler * 0xFFFF)));

    console.log(`[INFO] helper_usart_get_min_baudrate: Min Baudrate: ${result}`);
    return result;
  } catch (e) {
    console.log(`[ERROR] helper_usart_get_min_baudrate: ${e}`);
  }
}

/**
 * Computes Maximal baudrate
 * @param {integer} input_clock USART input clock
 * @param {integer} prescaler USART prescaler
 * @returns {integer} Maximal baudrate computed
 */
function helper_usart_get_max_baudrate(input_clock, prescaler) {
  let result = 0;
  try {
    console.log(
      `[INFO] helper_usart_get_max_baudrate: input_clock=${input_clock}, prescaler=${prescaler}`
    );
    /* USART/USART */
    /* USARDIV must be greater or equal to 16 (oversampling 8 or 16) */
    result = Math.floor((input_clock * (16 / 8) / (prescaler * 16)));

    console.log(`[INFO] helper_usart_get_max_baudrate: Max Baudrate: ${result}`);
    return result;
  } catch (e) {
    console.log(`[ERROR] helper_usart_get_max_baudrate: ${e}`);
  }
}

module.exports = {

  helper_usart_get_min_baudrate,
  helper_usart_get_max_baudrate,

};
