/**
  * @file Helpers functions used for DAC SW component
  * @author GPM Application Team
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  */

/**
 * Check if the channel_id has been configured in input
 * @param {object} channels list of configured channels
 * @param {integer} channel_id id of the channel
 * @param {string} path parameter to check
 * @returns {string} The value of the parameter if it exists, null otherwise
 */
function helper_dac_get_param_in_channel_config(channels, channel_id, path) {
  try {
    const channel = channels.find(function (channel) {
      return channel._foreignKey == channel_id;
    });

    if (channel) {
      if (path.includes('.')) {
        return path.split('.').reduce((obj, key) => (obj && obj[key] !== 'undefined') ? obj[key] : null, channel);
      } else {
        return channel[path] !== undefined ? channel[path] : null;
      }
    } else {
      return null;
    }
  } catch (e) {
    console.log(`[ERROR] helper_dac_get_param_in_channel_config: ${e}`);
    return null;
  }
}

/**
 * Returns 160 if the frequency is higher or equal to 160MHz,
 * 80 if it is between 160MHz and 80MHz, and 0 otherwise.
 * @param {number} frequency - The frequency in Hz.
 * @returns {number} - The corresponding value based on the frequency.
 */
function helper_dac_get_frequency_step(frequency) {
  const frequencyMHz = frequency / 1000000; // Convert Hz to MHz
  try {
    if (frequencyMHz >= 160) {
      return "ABOVE_160MHZ";
    } else if (frequencyMHz >= 80) {
      return "ABOVE_80MHZ";
    } else {
      return "DISABLED";
    }
  } catch (e) {
    console.log(`[ERROR] helper_adc_compute_sampling: ${e}`);
  }
}

/**
 * Calculate the timer output frequency based on prescaler and period values
 * @note  This api is used directly in the tim_parameters.json in advanced view
 * @param {integer} cycles Period set by the user
 * @param {integer} input_clock_frequency clock frequency in Hz
 * @returns {integer} Timer output cycle in us
 */
function helper_dac_compute_cycle_time(
  cycles,
  input_clock_frequency
) {
  let result = 0;
  try {
    /* Calculate the actual timer frequency */
    var dac_frequency_hz = input_clock_frequency;

    /* Calculate the actual output time */
    var cycle_time = (cycles * 1000000) / dac_frequency_hz;

    /* Return the output time */
    result = cycle_time;
  } catch (e) {
    console.log(`[ERROR] helper_dac_compute_cycle: ${e}`);
  }
  return result;
}

/**
 * Renames the trigger if it matches a specific value.
 * @param {string} trigger - The original trigger name.
 * @returns {string} - The renamed trigger if it matches, otherwise the original trigger.
 */
function helper_dac_rename_trigger(trigger){
  let result = trigger.toUpperCase();
  try {
    if(result.startsWith("SW") || result === "") {
      result = "SOFTWARE";
    } else if (result.startsWith("TIM")) {
      if (result.includes("_TGO")) {
        result = result.replace("_TGO", "_TRGO");
      }
      if (result.includes("_CKTIM")) {
        result = result.replace("_CKTIM", "");
      }
    } else if (result.startsWith("EXT")) {
      result = "EXTI" + result.match(/\[(\d+)\]/)[1];
    } else if (result.startsWith("HRTIM")) {
      if  (result.includes("_DAC_TRIG_OUT")) {
        result = result.replace("_DAC_TRIG_OUT", "_TRG");
      } else if (result.includes("_DAC_RST_TRIG_OUT")) {
        result = result.replace("_DAC_RST_TRIG_OUT", "_RST_TRG");
      }
    }
    else if (result.startsWith("PLAY")) {
      result = result.replace(/PLAY\d+_OUT\d+/g, "PLAY_OUT");
    }
  } catch (e) {
    console.error(`[ERROR] helper_dac_rename_trigger: ${e}`);
  }
  return result;
}

/**
 * Renames the noise amplitude value to a corresponding string representation.
 * @param {number} noise_amplitude - The noise amplitude value.
 * @returns {string} - The corresponding string representation of the noise amplitude.
 */
function helper_dac_rename_ll_noise(noise_amplitude){
  let result = noise_amplitude;
  try {
    const noise_map = {
          1: "BIT0",
          3: "BITS1_0",
          7: "BITS2_0",
         15: "BITS3_0",
         31: "BITS4_0",
         63: "BITS5_0",
        127: "BITS6_0",
        255: "BITS7_0",
        511: "BITS8_0",
       1023: "BITS9_0",
       2047: "BITS10_0",
       4095: "BITS11_0"
    };

    result = noise_map[noise_amplitude];
  } catch (e) {
    console.error(`[ERROR] helper_dac_rename_ll_noise: ${e}`);
  }
  return result;
}

module.exports = {
  helper_dac_compute_cycle_time,
  helper_dac_get_param_in_channel_config,
  helper_dac_get_frequency_step,
  helper_dac_rename_trigger,
  helper_dac_rename_ll_noise
};
