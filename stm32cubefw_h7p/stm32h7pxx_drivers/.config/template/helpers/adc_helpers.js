/**
 * @file Helpers functions used for ADC SW component
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
 * Get first character of adc post processing config
 * @param {string} str : left_bit_shift
 * @returns {string} First character of left_bit_shift value
 */
function helper_adc_post_processing_get_firstChar (str) {
  try {
    console.log(
      `[INFO] helper_adc_post_processing_get_firstChar: left_bit_shift=${str}}`
    );
    if (typeof str === 'string' && str.length > 0) {
      console.log(`[INFO] helper_adc_post_processing_get_firstChar: left_bit_shift : ${str}`);
      return str.charAt(0);
    } else {
      return '';
    }
  } catch (e) {
    console.log(`[ERROR] helper_adc_post_processing_get_firstChar: ${e}`);
  }
}
/**
 * Remove underscore character
 * @param {string} str
 * @returns {string} str without underscore
 */
function helper_adc_removeUnderscore (str) {
  try {
    console.log(
      `[INFO] helper_adc_removeUnderscore: ${str}}`
    );
    if (typeof str === 'string' && str.length > 0) {
      console.log(`[INFO] helper_adc_removeUnderscore: ${str}`);
      return str.replace(/_/g, '');
    } else {
      return '';
    }
  } catch (e) {
    console.log(`[ERROR] helper_adc_removeUnderscore: ${e}`);
  }
}

/**
 * Calculate the timer output frequency based on prescaler and period values
 * @note  This api is used directly in the tim_parameters.json in advanced view
 * @param {integer} input_clock_frequency System clock frequency in Hz
 * @param {integer} prescaler Prescaler set by the user
 * @param {integer} period Period set by the user
 * @returns {integer} Timer output frequency in Hz
 */
function helper_adc_compute_sampling(
  input_clock_frequency,
  prescaler,
  cycles
) {
  let result = 10000; /* default value to 10KHz */
  try {
    /* Convert input parameters to integer */
    var prescaler_num = parseInt(prescaler.replace('ASYNC_DIV', ''), 10);

    var cycle_num = parseInt(cycles.replace('CYCLES', ''), 10);

    /* Calculate the actual timer frequency */
    var adc_frequency_hz = input_clock_frequency / (prescaler_num);

    /* Calculate the actual output frequency */
    var sampling_time = (cycle_num * 1000000000) / adc_frequency_hz;

    /* Return the output frequency */
    result = Math.floor(sampling_time);
  } catch (e) {
    console.log(`[ERROR] helper_adc_compute_sampling: ${e}`);
  }
  return result;
}

/**
 * Calculate the timer output frequency based on prescaler and period values
 * @note  This api is used directly in the tim_parameters.json in advanced view
 * @param {integer} input_clock_frequency System clock frequency in Hz
 * @param {integer} prescaler Prescaler set by the user
 * @returns {integer} Timer output frequency in Hz
 */
function helper_adc_compute_frequency(
  input_clock_frequency,
  prescaler,
) {
  let result = 10000; /* default value to 10KHz */
  try {
    /* Convert input parameters to integer */
    var prescaler_num = parseInt(prescaler.replace('ASYNC_DIV', ''), 10);

    /* Calculate the actual timer frequency */
    var adc_frequency_hz = input_clock_frequency / (prescaler_num);

    /* Return the output frequency */
    result = Math.floor(adc_frequency_hz);
  } catch (e) {
    console.log(`[ERROR] helper_adc_compute_sampling: ${e}`);
  }
  return result;
}

/**
 * Check if the channel_id has been configured in input
 * @param {object} channels list of configured channels
 * @param {integer} channel_id id of the channel
 * @returns true or false
 */
function helper_adc_find_channel_enable(channels, channel_id) {
  try {
    console.log(
      `[INFO] helper_tim_find_channel_config_in_input: channels=${JSON.stringify(
        channels
      )}, channel_id=${channel_id}`
    );
    if (channels === undefined) {
      return false;
    }
    return (
      channels.find(function (channel) {
        return (
          channel["_foreignKey"] === channel_id.toString() &&
          channel.mode === "Input"
        );
      }) !== undefined
    );
  } catch (e) {
    console.log(`[ERROR] helper_tim_find_channel_config_in_input: ${e}`);
    return false;
  }
}
/**
 * Increment the given value by 1.
 * @param {number} value - The value to be incremented.
 * @returns {number} The incremented value.
 */
function helper_adc_increment(value) {
  try {
    return value + 1;
  } catch (e) {
    console.log(`[ERROR] increment: ${e}`);
    return null;
  }
}

/**
 * Transform the channel name to its corresponding ADC channel name.
 * @param {string} channel - The channel name to be transformed.
 * @returns {string} The transformed channel name.
 */
function helper_adc_transform_channel_name(channel) {
  try {
    // Normalize the input string to uppercase for comparison
    const channelUpper = channel.toUpperCase();

    // Special cases with uppercase keys
    const specialCases = {
      'VREFINT': 'ADC_CHANNEL_VREFINT',
      'VSENS': 'ADC_CHANNEL_TEMPSENSOR',
      'VSENSE': 'ADC_CHANNEL_TEMPSENSOR',
      'VBAT/4': 'ADC_CHANNEL_VBAT',
      'VDDCORE': 'ADC_CHANNEL_VDDCORE',
      'OPAMP1_INT': 'ADC_CHANNEL_OPAMP1_OUT',
      'OPAMP2_INT': 'ADC_CHANNEL_OPAMP2_OUT',
      'OPAMP3_INST': 'ADC_CHANNEL_OPAMP3_OUT'
    };
    if (specialCases[channelUpper]) {
      return specialCases[channelUpper];
    }

    // Regular expressions to test against the original channel string
    const patterns = [
      /ADC1_IN(\d+)/,
      /ADC2_IN(\d+)/,
      /ADC3_IN(\d+)/,
      /ADC4_IN(\d+)/,
      /ADC1_INP(\d+)/,
      /ADC2_INP(\d+)/,
      /ADC3_INP(\d+)/,
      /ADC4_INP(\d+)/,
      /ADC12_INP(\d+)/,
      /ADC123_INP(\d+)/
    ];

    // Iterate over patterns and return transformed channel if matched
    for (const pattern of patterns) {
      const match = channel.match(pattern);
      if (match) {
        return `ADC_CHANNEL_${match[1]}`;
      }
    }

    // Default case: return the original channel string
    return channel;
  } catch (e) {
    console.log(`[ERROR] transform_channel_name: ${e}`);
    return null;
  }
}

/**
 * Lookup a channel by its foreign key in the list of channels.
 * @param {Array} channels - The list of channels.
 * @param {string} source - The foreign key to lookup.
 * @returns {object|null} The found channel object or null if not found.
 */
function helper_adc_lookup_channel(channels, source) {
  try {
    return channels.find(channel => channel._foreignKey === source);
  } catch (e) {
    console.log(`[ERROR] lookup_channel: ${e}`);
    return null;
  }
}

/**
 * Get the length of the given array.
 * @param {Array} array - The array whose length is to be determined.
 * @returns {number} The length of the array, or 1 if the array is empty.
 */
function helper_adc_get_sequencer_length(array) {
  try {
    const length = array.length;
    return length === 0 ? 1 : length;
  } catch (e) {
    console.log(`[ERROR] sequencer_length: ${e}`);
    return null;
  }
}

/**
 * Check if the given array has more than one element.
 * @param {Array} array - The array to be checked.
 * @returns {number} Returns 1 if the array has more than one element, otherwise returns 0.
 */
function helper_adc_is_sequencer_not_empty(array) {
  try {
    return (array && array.length >= 1) ? 1 : 0;
  } catch (e) {
    console.log(`[ERROR] helper_adc_is_sequencer_not_empty: ${e}`);
    return null;
  }
}

/**
 * Transform the trigger name by removing suffix 'ADC_A' or 'ADC_S', replacing 'OC' or 'CC' with 'CH',
 * handling specific cases like 'EXT_IT[X]' to 'EXTIX', 'HRTIM_ADC_TRGX' to 'HRTIM_TRGX', and 'LPTIMERX_CH1' to 'LPTIMX_CH1'.
 * @param {string} trigger - The trigger name to be transformed.
 * @returns {string} The transformed trigger name.
 */
function helper_adc_transform_trigger_name(trigger) {
  try {
    // Validate input
    if (!trigger || typeof trigger !== 'string') {
      console.log('[ERROR] Invalid trigger input');
      return null;
    }

    // Handle specific case for EXTIn or EXT_IT[n] to EXTIn
    const match = trigger.match(/^(EXT_IT|EXTI).*?(\d+)/);
    if (match) {
      const number = match[2];
      return `EXTI${number}`;
    }

    // Handle specific case for HRTIM_ADC_TRGX
    const hrtimMatch = trigger.match(/HRTIM_ADC_TRG(\d+)/);
    if (hrtimMatch) {
      return `HRTIM_TRG${hrtimMatch[1]}`;
    }

    // Handle specific case for LPTIMERX_CH1
    const lptimerMatch = trigger.match(/LPTIMER(\d+)_CH(\d+)/);
    if (lptimerMatch) {
      return `LPTIM${lptimerMatch[1]}_CH${lptimerMatch[2]}`;
    }

    // Set to uppercase for comparison
    trigger = trigger.toUpperCase();

    // Replace 'TGO' or 'TGO2' by 'TRGO' or 'TRGO2'
    trigger = trigger.replace(/TGO(2?)/g, 'TRGO$1');

    // Remove the suffix 'ADC_A' or 'ADC_S' if it is present
    if (trigger.endsWith('ADC_A')) {
      trigger = trigger.slice(0, -'ADC_A'.length);
    } else if (trigger.endsWith('ADC_S')) {
      trigger = trigger.slice(0, -'ADC_S'.length);
    }

    // Replace 'OC' or 'CC' with 'CH'
    trigger = trigger.replace(/OC|CC/g, 'CH');

    // Remove trailing underscore if present
    if (trigger.endsWith('_')) {
      trigger = trigger.slice(0, -1);
    }

    return trigger;
  } catch (e) {
    console.log(`[ERROR] transform_trigger_name: ${e}`);
    return null;
  }
}

/**
 * Transform the trigger name by applying specific rules:
 * - Add 'LINE' to triggers starting with 'EXTI' followed by a number (e.g., 'EXTI11' to 'EXTI_LINE11').
 * - Remove suffix 'ADC_A' or 'ADC_S'.
 * - Replace 'OC' or 'CC' with 'CH'.
 * - Handle specific cases like 'HRTIM_ADC_TRGX' to 'HRTIM_TRGX', and 'LPTIMERX_CH1' to 'LPTIMX_CH1'.
 * - Remove trailing underscores.
 * @param {string} trigger - The trigger name to be transformed.
 * @returns {string|null} The transformed trigger name, or null if an error occurs.
 */
function helper_ll_adc_transform_trigger_name(trigger) {
  try {
    // Validate input
    if (!trigger || typeof trigger !== 'string') {
      console.log('[ERROR] Invalid trigger input');
      return null;
    }

    // Handle specific case for EXTIn or EXT_IT[n] to EXTIn
    const match = trigger.match(/^(EXT_IT|EXTI).*?(\d+)/);
    if (match) {
      const number = match[2];
      return `EXTI_LINE${number}`;
    }

    // Handle specific case for HRTIM_ADC_TRGX to HRTIM_TRGX
    const hrtimMatch = trigger.match(/HRTIM_ADC_TRG(\d+)/);
    if (hrtimMatch) {
      return `HRTIM_TRG${hrtimMatch[1]}`;
    }

    // Handle specific case for LPTIMERX_CH1 to LPTIMX_CH1
    const lptimerMatch = trigger.match(/LPTIMER(\d+)_CH(\d+)/);
    if (lptimerMatch) {
      return `LPTIM${lptimerMatch[1]}_CH${lptimerMatch[2]}`;
    }

    // Set to uppercase for comparison
    trigger = trigger.toUpperCase();

    // Replace 'TGO' or 'TGO2' by 'TRGO' or 'TRGO2'
    trigger = trigger.replace(/TGO(2?)/g, 'TRGO$1');

    // Remove the suffix 'ADC_A' or 'ADC_S'
    if (trigger.endsWith('ADC_A')) {
      trigger = trigger.slice(0, -'ADC_A'.length);
    } else if (trigger.endsWith('ADC_S')) {
      trigger = trigger.slice(0, -'ADC_S'.length);
    }

    // Replace 'OC' or 'CC' with 'CH'
    trigger = trigger.replace(/OC|CC/g, 'CH');

    // Remove trailing underscore if present
    if (trigger.endsWith('_')) {
      trigger = trigger.slice(0, -1);
    }

    // Return the transformed trigger
    return trigger;
  } catch (e) {
    console.log(`[ERROR] helper_ll_adc_transform_trigger_name: ${e}`);
    return null;
  }
}

/**
 * Check if the channel_id has been configured in input
 * @param {object} channels list of configured channels
 * @param {string} adc_id id of the ADC (e.g., 'ADC1', 'ADC2', 'ADC3')
 * @param {string} channel_id id of the channel (e.g., 'INP0')
 * @param {string} path parameter to check
 * @returns {string} The value of the parameter if it exists, null otherwise
 */
function helper_adc_get_param_in_channel_config(channels, adc_id, channel_id, path) {
  try {
    // Create a regex pattern to match the full channel identifier
    const pattern = new RegExp(`^ADC(\\d+|12|123)_${channel_id}$`);

    const channel = channels.find(function (channel) {
      return pattern.test(channel._foreignKey);
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
    console.log(`[ERROR] helper_adc_get_param_in_channel_config: ${e}`);
    return null;
  }
}

/**
 * Transform a boolean value to "ENABLE" or "DISABLE".
 * @param {boolean} value - The boolean value to be transformed.
 * @returns {string} "ENABLE" if the value is true, "DISABLE" if the value is false.
 */
function helper_adc_boolean_to_enable_disable(value) {
  try {
    if (typeof value === 'boolean') {
      return value ? 'ENABLE' : 'DISABLE';
    }
    return 'DISABLE'; // Default to DISABLE if the value is not a boolean
  } catch (e) {
    console.log(`[ERROR] helper_enable_disable: ${e}`);
    return 'DISABLE';
  }
}

/**
 * Helper to get the AWD panels from the context and return them in an array.
 * Each panel is included if its selection property (awd1_sel, awd2_sel, awd3_sel) is true.
 * @param {object} context - The context object containing the feat_opt property.
 * @param {object} options - Handlebars options object.
 * @returns {string} The rendered template with the AWD panels.
 */
function helper_adc_get_awd_panels(context, options) {
  const awdPanels = [];
  // Check if AWD1 panel is selected and add it to the array
  if (context.feat_opt.awd1_panel && context.feat_opt.awd1_panel.awd1_sel) {
    awdPanels.push({ panel: context.feat_opt.awd1_panel, awd_number: 1 });
  }
  // Check if AWD2 panel is selected and add it to the array
  if (context.feat_opt.awd2_panel && context.feat_opt.awd2_panel.awd2_sel) {
    awdPanels.push({ panel: context.feat_opt.awd2_panel, awd_number: 2 });
  }
  // Check if AWD3 panel is selected and add it to the array
  if (context.feat_opt.awd3_panel && context.feat_opt.awd3_panel.awd3_sel) {
    awdPanels.push({ panel: context.feat_opt.awd3_panel, awd_number: 3 });
  }
  // Return the rendered template with the AWD panels
  return options.fn({ awdPanels });
}

/**
 * Helper to get the offset panels from the context and return them in an array.
 * Each panel is included if its selection property (offset_1_sel, offset_2_sel, offset_3_sel, offset_4_sel) is true.
 * @param {object} context - The context object containing the feat_opt property.
 * @param {object} options - Handlebars options object.
 * @returns {string} The rendered template with the offset panels.
 */
function helper_adc_get_offset_panels(context, options) {
  const offsetPanels = [];
  // Check if offset 1 panel is selected and add it to the array
  if (context.feat_opt.offset_1_panel && context.feat_opt.offset_1_panel.offset_1_sel) {
    offsetPanels.push({ panel: context.feat_opt.offset_1_panel, offset_number: 1 });
  }
  // Check if offset 2 panel is selected and add it to the array
  if (context.feat_opt.offset_2_panel && context.feat_opt.offset_2_panel.offset_2_sel) {
    offsetPanels.push({ panel: context.feat_opt.offset_2_panel, offset_number: 2 });
  }
  // Check if offset 3 panel is selected and add it to the array
  if (context.feat_opt.offset_3_panel && context.feat_opt.offset_3_panel.offset_3_sel) {
    offsetPanels.push({ panel: context.feat_opt.offset_3_panel, offset_number: 3 });
  }
  // Check if offset 4 panel is selected and add it to the array
  if (context.feat_opt.offset_4_panel && context.feat_opt.offset_4_panel.offset_4_sel) {
    offsetPanels.push({ panel: context.feat_opt.offset_4_panel, offset_number: 4 });
  }
  // Return the rendered template with the offset panels
  return options.fn({ offsetPanels });
}

/**
 * Handlebars Helper: helper_adc_remove_suffix
 * Removes the suffix '_BIT' or '_BITS' (case-insensitive) from the end of a string.
 * @param {string} input - The input string.
 * @returns {string} - The string without the suffix, or original if no suffix found.
 */
function helper_adc_remove_suffix(input) {
  try {
    if (typeof input !== 'string') {
      return input;
    }
    const pattern = /_BIT(S)?$/i;

    return input.replace(pattern, '');
  } catch (e) {
    console.error(`[ERROR] helper_adc_remove_suffix: ${e}`);
    return input;
  }
}

module.exports = {
  helper_adc_increment,
  helper_adc_lookup_channel,
  helper_adc_transform_channel_name,
  helper_adc_transform_trigger_name,
  helper_adc_get_sequencer_length,
  helper_adc_post_processing_get_firstChar,
  helper_adc_removeUnderscore,
  helper_adc_compute_sampling,
  helper_adc_compute_frequency,
  helper_adc_get_param_in_channel_config,
  helper_adc_find_channel_enable,
  helper_adc_boolean_to_enable_disable,
  helper_adc_get_awd_panels,
  helper_adc_get_offset_panels,
  helper_adc_is_sequencer_not_empty,
  helper_ll_adc_transform_trigger_name,
  helper_adc_remove_suffix
};
