/**
 * @file Helpers functions used for UART SW component
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
 * Computes Minimal baud rate
 * @param {integer} input_clock UART input clock
 * @param {integer} prescaler Uart prescaler
 * @param {string} oversampling : '1' oversampling activated; '0' oversampling deactivated
 * @param {integer} baudgen_type Hardware 'generic' deined in DFP
 * @returns {integer} Minimal baud rate computed
 */
function helper_uart_get_min_baud_rate(input_clock, prescaler, oversampling, baudgen_type) {
  let result = [];
  try {
    console.log(
      `[INFO] helper_uart_get_min_baud_rate: input_clock=${input_clock}, prescaler=${prescaler}, oversampling=${oversampling}, baudgen_type=${baudgen_type}`
    );
    if (baudgen_type === 0) {
      /* UART/USART */
      result = Math.ceil(((input_clock * (16 / oversampling)) / (prescaler * 0xFFFF)));
    } else {
      /* LPUART */
      result = Math.ceil(((input_clock * 256) / (prescaler * 0xFFFFF)));
    }
    console.log(`[INFO] helper_uart_get_min_baud_rate: Min Baud rate: ${result}`);
    return result;
  } catch (e) {
    console.log(`[ERROR] helper_uart_get_min_baud_rate: ${e}`);
  }
}

/**
 * Computes Maximal baud rate
 * @param {integer} input_clock UART input clock
 * @param {integer} prescaler Uart prescaler
 * @param {string} oversampling : '1' oversampling activated; '0' oversampling deactivated
 * @param {integer} baudgen_type Hardware 'generic' deined in DFP
 * @returns {integer} Minimal baud rate computed
 */
function helper_uart_get_max_baud_rate(input_clock, prescaler, oversampling, baudgen_type) {
  let result = 0;
  try {
    console.log(
      `[INFO] helper_uart_get_max_baud_rate: input_clock=${input_clock}, prescaler=${prescaler}, oversampling=${oversampling}, baudgen_type=${baudgen_type}`
    );
    if (baudgen_type === 0) {
      /* UART/USART */
      /* USARDIV must be greater or equal to 16 (oversampling 8 or 16) */
      result = Math.floor((input_clock * (16 / oversampling) / (prescaler * 16)));
    } else {
      /* LPUART */
      /* USARDIV must be greater or equal to 0x300 */
      result = Math.floor(((input_clock * 256) / (prescaler * 0x300)));
    }
    console.log(`[INFO] helper_uart_get_max_baud_rate: Max Baud rate: ${result}`);
    return result;
  } catch (e) {
    console.log(`[ERROR] helper_uart_get_max_baud_rate: ${e}`);
  }
}

module.exports = {

  helper_uart_get_min_baud_rate,
  helper_uart_get_max_baud_rate,

};
