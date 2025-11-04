/**
 * @file Helpers functions used for RTC SW component
 * @author GPM Application Team
 * @license
 * Copyright (c) 2025 STMicroelectronics.
 * All rights reserved.
 *
 * This software is licensed under terms that can be found in the LICENSE file
 * in the root directory of this software component.
 * If no LICENSE file comes with this software, it is provided AS-IS.
 */

/**
 * Calculate the wakeup minimum period based on RTC clock frequency, wakeup divider, 
 * asynchronous predivider and synchronous predivider
 * @param {integer} rtc_clock_frequency System clock frequency in Hz
 * @param {string} divider Wakeup divider choose by the user
 * @param {integer} asynchronous_predivider Asynchronous divider set by the user
 * @param {integer} synchronous_predivider Synchronous divider set by the user
 * @returns {integer} Wakeup minimum period in second or microsecond
 */
function helper_rtc_compute_wakeup_minimum_period(
  rtc_clock_frequency,
  divider,
  asynchronous_predivider,
  synchronous_predivider
){
  /* Default value : 1s */
  let result = 1;
  var period = 0;

  try {
    switch (divider) {
      case "RTCCLK_DIV16":
        divider = 16;
        /* Calculate the minimum period in microsecond */
        period = (divider * 1000000) / rtc_clock_frequency;
        break;
      case "RTCCLK_DIV8":
        divider = 8;
        /* Calculate the minimum period in microsecond */
        period = (divider * 1000000) / rtc_clock_frequency;
        break;
      case "RTCCLK_DIV4":
        divider = 4;
        /* Calculate the minimum period in microsecond */
        period = (divider * 1000000) / rtc_clock_frequency;
        break;
      case "RTCCLK_DIV2":
        divider = 2;
        /* Calculate the minimum period in microsecond */
        period = (divider * 1000000) / rtc_clock_frequency;
        break;
      case "SECONDS":
      case "SECONDS_ADD_1BIT":
        divider = (asynchronous_predivider + 1) * (synchronous_predivider + 1);
        /* Calculate the minimum period in second */
        period = divider / rtc_clock_frequency;
        break;
      default:
        console.log("Wrong divider.");
        break;
    }

    /* Return the output frequency */
    result = parseFloat(period.toFixed(3));
  } catch (e) {
    console.log(`[ERROR] helper_rtc_compute_wakeup_minimum_period: ${e}`);
  }
  return result;
}

module.exports = {
  helper_rtc_compute_wakeup_minimum_period
};
