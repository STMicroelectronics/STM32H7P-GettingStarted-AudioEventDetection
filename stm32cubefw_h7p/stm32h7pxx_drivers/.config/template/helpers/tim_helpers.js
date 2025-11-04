/**
 * @file Helpers functions used for TIM SW component
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
 * Check if the channel_id has been configured in input
 * @param {object} channels list of configured channels
 * @param {integer} channel_id id of the channel
 * @returns true or false
 */
function helper_tim_find_channel_config_in_input(channels, channel_id) {
  try {
    /*console.log(
      `[INFO] helper_tim_find_channel_config_in_input: channels=${JSON.stringify(
        channels
      )}, channel_id=${channel_id}`
    );*/
    if (channels === undefined || channel_id === undefined) {
      return false;
    }
    return (
      channels.find(function (channel) {
        return (
          channel["_foreignKey"] === channel_id.toString() &&
          channel.channel_direction === "Input"
        );
      }) !== undefined
    );
  } catch (e) {
    console.log(`[ERROR] helper_tim_find_channel_config_in_input: ${e}`);
    return false;
  }
}

/**
 * Check if the channel_id has been configured in indirect mode
 * @param {object} channels list of configured channels
 * @param {integer} channel_id id of the channel
 * @returns true or false
 */
function helper_tim_channel_check_indirect(channels, channel_id) {
  try {
    /*console.log(
      `[INFO] helper_tim_channel_check_indirect: channels=${JSON.stringify(
        channels
      )}, channel_id=${channel_id}`
    );*/
    if (channels === undefined || channel_id === undefined) {
      return false;
    }
    let channel_id_string = channel_id.toString();
    const map_indirect_channel = {
      CC1: "CC2",
      CC2: "CC1",
      CC3: "CC4",
      CC4: "CC3",
    };
    if (!map_indirect_channel.hasOwnProperty(channel_id_string)) {
      return false;
    }
    let indirect_channel = map_indirect_channel[channel_id_string];
    console.log(`   indirect_channel: ${indirect_channel}`);
    return (
      channels.find(function (channel) {
        return (
          channel["_foreignKey"] === indirect_channel.toString() &&
          channel.channel_direction === "Input" &&
          channel.input_configuration.capture_unit_configuration.source ===
            "DIRECT"
        );
      }) !== undefined
    );
  } catch (e) {
    console.log(`[ERROR] helper_tim_channel_check_indirect: ${e}`);
    return false;
  }
}

/**
 * Check if the channel_id is a complementary channel
 * @param {integer} channel_id id of the channel
 * @returns true or false
 */
function tim_check_if_complementary_channel(channel_id) {
  let result = false;
  try {
    /*console.log(
      `[INFO] tim_check_if_complementary_channel: channel_id=${channel_id}
      )}`
    );*/
    if (channel_id === undefined) {
      return false;
    }

    const regexCHxN = /^CC\dN$/;

    if (regexCHxN.test(channel_id)) {
      result = true;
    }
  } catch (e) {
    console.log(`[ERROR] tim_check_if_complementary_channel: ${e}`);
  }
  return result;
}

/**
 * Check if the channel_id needs to configure a GPIO
 * @param {object} channel element of the channels list
 * @param {integer} channel_id id of the channel
 * @returns true or false
 */
function tim_need_gpio(channel, channel_id) {
  let result = false;
  try {
    if (channel === undefined || channel_id === undefined) {
      return false;
    }
    if (
      channel !== undefined &&
      channel.use_channel !== undefined &&
      channel.use_channel
    ) {
      /* in input mode, GPIO must be configured only if the input capture source is set to tim_tix_in0
         and with at least 'AFI' or 'Input pins' source.
         e.g. AFI
              Input Pins
              AFI (TIM_CH1)
         Check with in0 to avoid AFI include in another interconnect signal (e.g. ti2_in2 - AFI_TIM3_CH2). */
      if (
        channel.channel_direction === "Input" &&
        channel.input_configuration !== undefined &&
        /(AFI|Input pins)/i.test(channel.input_configuration.input_channel_configuration.input_selection.source) &&
        /^ti\d_in0$/.test(channel.input_configuration.input_channel_configuration.input_selection.ip_signal) &&
        !tim_check_if_complementary_channel(channel_id)
      ) {
        result = true;
        /*console.log(
          `   Input Channel ${channel_id} configured to GPIO`
        );*/
      } else if (
        channel.channel_direction === "Output" &&
        channel.output_configuration !== undefined &&
        channel.output_configuration.compare_unit_configuration !==
          undefined &&
        channel.output_configuration.compare_unit_configuration.mode !==
          "FROZEN" &&
        (tim_check_if_complementary_channel(channel_id) ?
         channel.output_configuration.ocxn_channel_config.chxn_gpio :
         channel.output_configuration.ocx_channel_config.chx_gpio)
      ) {
        result = true;
        /*console.log(
          `   Output Channel ${channel_id} with GPIO`
        );*/
      }
    }
  } catch (e) {
    console.log(`[ERROR] tim_need_gpio: ${e}`);
  }
  return result;
}

/**
 * Check if a GPIO is used
 * @param {object} basic basic view configuration
 * @param {object} additional_view additional view configuration
 * @returns true or false
 */
function helper_tim_need_at_least_one_gpio(basic, additional_view) {
  let result = false;
  try {
    /*console.log(
      `[INFO] helper_tim_need_at_least_one_gpio: basic=${JSON.stringify(basic)} 
      additional_view=${JSON.stringify(additional_view)}`
    );*/
    if (basic === undefined || additional_view === undefined) {
      return false;
    }

    /* Check channel GPIOs */
    const channels = basic.input_output_channels?.channels || [];
    for (const config_ch of channels) {
      result = tim_need_gpio(config_ch, config_ch._foreignKey) || tim_need_gpio(config_ch, config_ch._foreignKey + 'N');
      if (result) return result;
    }

    /* Check break GPIOs */
    const breaks = additional_view.break_configuration?.breaks || [];
    result = helper_tim_need_gpio_break(breaks, 1) || helper_tim_need_gpio_break(breaks, 2);
    if (result) return result;

    /* Check ETR GPIO */
    const sources = ['Input pins', 'AFI'];
    result = sources.includes(basic.time_base.clock_source_configuration?.external_trigger?.source) ||
    sources.includes(additional_view.external_trigger_configuration?.external_trigger?.source);
    if (result) return result;

  } catch (e) {
    console.log(`[ERROR] helper_tim_need_at_least_one_gpio: ${e}`);
  }
  return result;
}

/**
 * Check if the channel_id needs to configure a GPIO
 * @param {object} channels list of configured channels
 * @param {integer} channel_id id of the channel
 * @returns true or false
 */
function helper_tim_need_gpio_channel(channels, channel_id) {
  let result = false;
  try {
    /*console.log(
      `[INFO] helper_tim_need_gpio_channel: channels=${JSON.stringify(
        channels
      )}, channel_id=${channel_id}`
    );*/
    if (channels === undefined || channel_id === undefined) {
      return false;
    }
    const channel_id_str = channel_id.toString();
    const channel_id_base = channel_id_str.endsWith('N') ?
                            channel_id_str.slice(0, -1) :
                            channel_id_str; /* e.g. CCxN -> CCx */
    /*console.log(
      `[INFO] helper_tim_need_gpio_channel: channel_id_base=${channel_id_base}`
    );*/

    let config_ch = channels.find(function (channel) {
      return channel["_foreignKey"] === channel_id_base;
    });
    result = tim_need_gpio(config_ch, channel_id);
  } catch (e) {
    console.log(`[ERROR] helper_tim_need_gpio_channel: ${e}`);
  }
  return result;
}

/**
 * Check if the break_id needs to configure a GPIO
 * @param {object} breaks list of configured breaks
 * @param {integer} break_id id of the break
 * @returns true or false
 */
function helper_tim_need_gpio_break(breaks, break_id) {
  let result = false;
  try {
    /*console.log(
      `[INFO] helper_tim_need_gpio_break: breaks=${JSON.stringify(
        breaks
      )}, break_id=${break_id}`
    );*/
    if (breaks === undefined || break_id === undefined) {
      return false;
    }
    const brk = {
      breaksArray: breaks,
    };
    /*console.log(
      `[INFO] helper_tim_need_gpio_break: brk.breaksArray=${JSON.stringify(brk.breaksArray)}`
    );*/

    const breakConfig = brk.breaksArray.find(b => b._foreignKey === break_id);
    if (breakConfig &&
        breakConfig.break_input_sources_configuration &&
        (breakConfig.break_input_sources_configuration.some(source => (source._foreignKey === "AFI" || source._foreignKey === "Input pins") && source.enable_break_input_source === true))) {
      result = true;
    }
  } catch (e) {
    console.log(`[ERROR] helper_tim_need_gpio_break: ${e}`);
  }
  return result;
}

/**
 * Check if at least one channel is in output mode
 * @param {object} channels list of configured channels
 * @returns true or false
 */
function helper_tim_check_if_at_least_one_channel_in_output(channels) {
  try {
    /*console.log(
      `[INFO] helper_tim_check_if_at_least_one_channel_in_output: channels=${JSON.stringify(
        channels
      )}`
    );*/
    if (channels === undefined) {
      return false;
    }
    return channels.find((channel) => channel.channel_direction === "Output") !== undefined;
  } catch (e) {
    console.log(
      `[ERROR] helper_tim_check_if_at_least_one_channel_in_output: ${e}`
    );
    return false;
  }
}

/**
 * Check if at least one channel is in input mode connected to TRC
 * @param {object} channels list of configured channels
 * @returns true or false
 */
function helper_tim_check_if_at_least_one_channel_in_input_trc(channels) {
  try {
    /*console.log(
      `[INFO] helper_tim_check_if_at_least_one_channel_in_input_trc: channels=${JSON.stringify(
        channels
      )}`
    );*/
    if (channels === undefined) {
      return false;
    }
    return (
      channels.find(function (channel) {
        return (
          channel["channel_direction"] === "Input" &&
          channel.input_configuration !== undefined &&
          channel.input_configuration.capture_unit_configuration.source === "TRC"
        );
      }) !== undefined
    );
  } catch (e) {
    console.log(
      `[ERROR] helper_tim_check_if_at_least_one_channel_in_input_trc: ${e}`
    );
    return false;
  }
}

/**
 * Check if at least one channel is in output mode or input mode
 * @param {object} channels list of configured channels
 * @returns true or false
 */
function helper_tim_check_if_at_least_one_channel_in_input_or_output(channels) {
  let result = false;
  try {
    /*console.log(
      `[INFO] helper_tim_check_if_at_least_one_channel_in_input_or_output: channels=${JSON.stringify(
        channels
      )}`
    );*/
    if (channels === undefined) {
      return false;
    }
    for (let i = 0; i < channels.length; i++) {
      if (
        channels[i].use_channel !== undefined &&
        channels[i].use_channel &&
        (channels[i]._foreignKey === "CC1" ||
          channels[i]._foreignKey === "CC2" ||
          channels[i]._foreignKey === "CC3" ||
          channels[i]._foreignKey === "CC4")
      ) {
        result = true;
        console.log(`   Channel: ${channels[i]._foreignKey} found`);
        break;
      }
    }
  } catch (e) {
    console.log(
      `[ERROR] helper_tim_check_if_at_least_one_channel_in_input_or_output: ${e}`
    );
  }
  return result;
}

/**
 * Check if at least one channel uses ocref clear
 * @param {object} channels list of configured channels
 * @returns true or false
 */
function helper_tim_check_if_at_least_one_channel_uses_ocref_clear(channels) {
  try {
    /*console.log(
      `[INFO] helper_tim_check_if_at_least_one_channel_uses_ocref_clear: channels=${JSON.stringify(
        channels
      )}`
    );*/
    if (channels === undefined) {
      return false;
    }
    return (
      channels.find(function (channel) {
        return (
          channel.output_configuration !== undefined &&
          channel.output_configuration.compare_unit_configuration.ocref_clear === true
        );
      }) !== undefined
    );
  } catch (e) {
    console.log(
      `[ERROR] helper_tim_check_if_at_least_one_channel_uses_ocref_clear: ${e}`
    );
    return false;
  }
}

/**
 * Check if at least one DMA channel for TIM channels has been enabled
 * @param {object} dma_settings System.dma_settings object
 * @returns true or false
 */
function helper_tim_check_if_at_least_one_cc_dma_channel(dma_settings) {
  try {
    /*console.log(
      `[INFO] helper_tim_check_if_at_least_one_cc_dma_channel: dma_settings=${JSON.stringify(
        dma_settings
      )}`
    );*/
    if (dma_settings === undefined) {
      return false;
    }
    for (let i = 1; i <= 4; i++) {
      if (dma_settings[`enable_dma_cc${i}`]) {
        /*console.log(`   DMA Channel${i} found`);*/
        return true;
      }
    }
  } catch (e) {
    console.log(`[ERROR] helper_tim_check_if_at_least_one_cc_dma_channel: ${e}`);
  }
  return false;
}

/**
 * Check if channel3 or channel4 has been configured in pulse generator mode
 * @param {object} channels list of configured channels
 * @returns true or false
 */
function helper_tim_check_if_pulse_generator_ch3_ch4(channels) {
  let result = false;
  try {
    /*console.log(
      `[INFO] helper_tim_check_if_pulse_generator_ch3_ch4: channels=${JSON.stringify(
        channels
      )}`
    );*/
    if (channels === undefined) {
      return false;
    }
    for (let i = 0; i < channels.length; i++) {
      if (
        channels[i].use_channel !== undefined &&
        channels[i].use_channel &&
        (channels[i]._foreignKey === "CC3" || channels[i]._foreignKey === "CC4")
      ) {
        if (
          channels[i].channel_direction === "Output" &&
          channels[i].output_configuration !== undefined &&
          channels[i].output_configuration.compare_unit_configuration !==
            undefined &&
          channels[i].output_configuration.compare_unit_configuration
            .mode === "PULSE_ON_COMPARE"
        ) {
          result = true;
          /*console.log(
            `   Output Channel set to PULSE_ON_COMPARE found on ${channels[i]._foreignKey}`
          );*/
          break;
        }
      }
    }
  } catch (e) {
    console.log(`[ERROR] helper_tim_check_if_pulse_generator_ch3_ch4: ${e}`);
  }
  return result;
}

/**
 * Check if the channel_id has been configured in output
 * @param {object} channels list of configured channels
 * @param {integer} channel_id id of the channel
 * @returns true or false
 */
function helper_tim_find_channel_config_in_output(channels, channel_id) {
  try {
    /*console.log(
      `[INFO] helper_tim_find_channel_config_in_output: channels=${JSON.stringify(
        channels
      )}, channel_id=${channel_id}`
    );*/
    if (channels === undefined || channel_id === undefined) {
      return false;
    }
    return (
      channels.find(function (channel) {
        return (
          channel._foreignKey === channel_id.toString() &&
          channel["channel_direction"] === "Output"
        );
      }) !== undefined
    );
  } catch (e) {
    console.log(`[ERROR] helper_tim_find_channel_config_in_output: ${e}`);
    return false;
  }
}

/**
 * Check if at least one channel has been configured in output physically
 * (CHx & CHxN GPIOs enabled)
 * @param {object} channels list of configured channels
 * @returns true or false
 */
function helper_tim_check_if_at_least_channel_and_complementary_in_output(
  channels
) {
  let result = false;
  try {
    /*console.log(
      `[INFO] helper_tim_check_if_at_least_channel_and_complementary_in_output: channels=${JSON.stringify(
        channels
      )}`
    );*/
    if (channels === undefined) {
      return false;
    }

    for (let i = 0; i < channels.length; i++) {
      if (channels[i].channel_direction === "Output" &&
          channels[i].output_configuration.ocx_channel_config.chx_gpio &&
          channels[i].output_configuration.ocxn_channel_config.chxn_gpio
      ) {
        result = true;
        /*console.log(
          `   Output Channel and its complementary found on ${channels[i]._foreignKey}`
        );*/
        break;
      }
    }
  } catch (e) {
    console.log(
      `[ERROR] helper_tim_check_if_at_least_channel_and_complementary_in_output: ${e}`
    );
  }
  return result;
}

/**
 * Check if channel_id has been configured (output or input)
 * @param {object} channels list of configured channels
 * @param {integer} channel_id id of the channel
 * @returns true or false
 */
function helper_tim_find_channel_config(channels, channel_id) {
  let result = false;
  try {
    /*console.log(
      `[INFO] helper_tim_find_channel_config: channels=${JSON.stringify(
        channels
      )}, channel_id=${channel_id}`
    );*/
    if (channels === undefined || channel_id === undefined) {
      return false;
    }

    result = channels.some(channel =>
      channel.use_channel && channel._foreignKey === channel_id.toString()
    );
  } catch (e) {
    console.log(`[ERROR] helper_tim_find_channel_config: ${e}`);
  }
  return result;
}

/**
 * Calculate the timer output frequency based on prescaler and period values
 * @note  This api is used directly in the tim_parameters.json in advanced view
 * @param {integer} input_clock_frequency System clock frequency in Hz
 * @param {integer} prescaler Prescaler set by the user
 * @param {integer} period Period set by the user
 * @returns {integer} Timer output frequency in Hz
 */
function helper_tim_compute_frequency(
  input_clock_frequency,
  prescaler,
  period
) {
  let result = 10000; /* default value to 10KHz */
  try {
    console.log(
      `[INFO] helper_tim_compute_frequency: input_clock_frequency=${input_clock_frequency}, prescaler=${prescaler}, period=${period}`
    );
    if (input_clock_frequency === undefined || prescaler === undefined || period === undefined) {
      return false;
    }

    /* Calculate the actual timer frequency */
    var timer_frequency = input_clock_frequency / (prescaler + 1);

    /* Calculate the actual output frequency */
    var output_frequency = timer_frequency / (period + 1);

    /* Return the output frequency */
    result = Math.floor(output_frequency);
  } catch (e) {
    console.log(`[ERROR] helper_tim_compute_frequency: ${e}`);
  }
  return result;
}

/**
 * Calculate the prescaler
 * @note  This api is used directly in the tim_parameters.json in basic view
 * @param {integer} input_clock_frequency System clock frequency in Hz
 * @param {integer} output_frequency output frequency in Hz
 * @returns Prescaler values
 */
function helper_tim_compute_prescaler(input_clock_frequency, output_frequency) {
  let result = 123456789;
  try {
    console.log(
      `[INFO] helper_tim_compute_prescaler: input_clock_frequency=${input_clock_frequency}, output_frequency=${output_frequency}`
    );
    if (input_clock_frequency === undefined || output_frequency === undefined) {
      return false;
    }

    if (output_frequency != 0) {
      /* Calculate the prescaler value */
      var prescaler = input_clock_frequency / output_frequency - 1;

      /* Return the prescale value */
      result = Math.floor(prescaler);
    }
  } catch (e) {
    console.log(`[ERROR] helper_tim_compute_prescaler: ${e}`);
  }
  return result;
}

/**
 * Calculate the period
 * @note  This api is used directly in the tim_parameters.json in basic view
 * @param {integer} input_clock_frequency System clock frequency in Hz
 * @param {integer} output_frequency output frequency in Hz
 * @returns Period values
 */
function helper_tim_compute_period(input_clock_frequency, output_frequency) {
  let result = 123456789;
  try {
    console.log(
      `[INFO] helper_tim_compute_period: input_clock_frequency=${input_clock_frequency}, output_frequency=${output_frequency}`
    );
    if (input_clock_frequency === undefined || output_frequency === undefined) {
      return false;
    }

    /* Calculate the actual output frequency */
    var period = output_frequency - 1;

    /* Return the period value */
    return Math.floor(period);
  } catch (e) {
    console.log(`[ERROR] helper_tim_compute_period: ${e}`);
  }
  return result;
}

/**
 * Calculate the sampling clock value.
 * @note  This api is used directly in the tim_parameters.json in basic view
 * @param {integer} input_clock_frequency System clock frequency in Hz
 * @param {integer} clock_divider Clock divider value (CKD)
 * @param {string} sampling_ck_div Sampling clock divider name
 * @returns fSAMPLING (Hz)
 */
function helper_tim_compute_sampling_clock(input_clock_frequency, clock_divider, sampling_ck_div) {
  let result = 123456789;
  const regex = /FDIV(\d+)_?/;
  try {
    console.log(
      `[INFO] helper_tim_compute_sampling_clock: input_clock_frequency=${input_clock_frequency}, clock_divider=${clock_divider},
      sampling_ck_div=${sampling_ck_div}, samp_ck_div=${samp_ck_div}`
    );
    if (input_clock_frequency === undefined || clock_divider === undefined || sampling_ck_div === undefined) {
      return false;
    }

    const samp_ck_div = sampling_ck_div.match(regex);

    if (samp_ck_div === 1) {
      /* DIV1: fSAMPLING = ftim_ker_ck */
      result = input_clock_frequency;
    }
    else {
      /* DIVx: fSAMPLING = fDTS / x ; with fDTS = ftim_ker_ck / CKD */
      result = input_clock_frequency / clock_divider / samp_ck_div;
    }

    result = Math.floor(result);
  } catch (e) {
    console.log(`[ERROR] helper_tim_compute_sampling_clock: ${e}`);
  }
  return result;
}

/**
 * Convert HW Channel ID (CHx) to HAL channel ID (CHANNEL_x)
 * @note  This api is used directly in the tim_parameters.json in basic view
 * @param {string} channel channel ID (CHx)
 * @returns {string} HAL or LL channel ID (CHANNEL_x)
 */
function helper_tim_convert_channel(channel) {
  try {
    /*     console.log(
      `[INFO] helper_tim_convert_channel: channel=${channel}`
    );
 */
    if (channel === undefined) {
      return false;
    }

    const map_channel = {
      CC1: "1",
      CC2: "2",
      CC3: "3",
      CC4: "4",
      CC5: "5",
      CC6: "6",
      CC7: "7",
    };

    return map_channel[channel] || "";
  } catch (e) {
    console.log(`[ERROR] helper_tim_convert_channel: ${e}`);
    return "";
  }
}

/**
 * Convert HW input capture ID (TIx_y) to HAL Input ID (TI1_GPIO) or LL Input ID (TI1_RMP_GPIO)
 * @note  This api is used directly in the tim_parameters.json in basic view
 * @param {string} channel channel ID (CHx)
 * @param {string} source input source selection (ex 'Input pins')
 * @param {string} layer HAL or LL
 * @returns {string} HAL Input ID (TI1_GPIO) or LL Input ID (TI1_RMP_GPIO)
 */
function helper_tim_convert_input_src(channel, source, layer) {
  try {
    /*console.log(
      `[INFO] helper_tim_convert_input_src: channel=${channel} layer=${layer}`
    );*/
    if (channel === undefined || source === undefined || layer === undefined) {
      return false;
    }

    const map_input_source = {
      "Input pins": "GPIO",
      "AFI": "GPIO",
    };
    let source_map = source;
    if (map_input_source.hasOwnProperty(source)) {
      source_map = map_input_source[source];
    } else {
      source_map = source;
    }
    const map_input = {
      CC1: "TI1",
      CC2: "TI2",
      CC3: "TI3",
      CC4: "TI4",
    };
    if (layer === "HAL") {
      return map_input[channel] + "_" + source_map;
    } else if (layer === "LL") {
      return map_input[channel] + "_RMP_" + source_map;
    } else {
      console.log(`[ERROR] helper_tim_convert_input_src: Invalid layer ${layer}`);
      return "";
    }
  } catch (e) {
    console.log(`[ERROR] helper_tim_convert_input_src: ${e}`);
    return "";
  }
}

/**
 * Convert HW input capture ID (TIx_y) to HAL Input ID (TI1_GPIO) or LL Input ID (TI1_RMP_GPIO)
 * @note  This api is used directly in the tim_parameters.json in basic view
 * @param {string} break_name Break input name (e.g. "Input pins", "AFI")
 * @returns {string} HAL Input ID (TI1_GPIO) or LL Input ID (TI1_RMP_GPIO)
 */
function helper_tim_convert_break_input(break_name) {
  try {
    /*console.log(
      `[INFO] helper_tim_convert_break_input: break_name=${break_name}`
    );*/
    if (break_name === undefined) {
      return false;
    }

    const map_break_input = {
      "Input pins": "GPIO",
      "AFI": "GPIO",
    };
    let source_map = break_name;
    if (map_break_input.hasOwnProperty(break_name)) {
      source_map = map_break_input[break_name];
    }
    if (source_map.includes('mdf')) {
      source_map = "MDF1";
    }
    return source_map;
  } catch (e) {
    console.log(`[ERROR] helper_tim_convert_break_input: ${e}`);
    return "";
  }
}

/**
 * Get the synchronized break inputs for a given break number
 * @param {integer} break_number Break number (1 or 2)
 * @param {object} resources List of resources
 * @param {object} interconnect List of interconnects
 * @returns {object} Filtered interconnects for the specified break
 */
function helper_tim_synchronized_breaks(break_number, resources, interconnect) {
  try {
    /*console.log(
      `[INFO] helper_tim_synchronized_breaks: resources=${JSON.stringify(
        resources
      )} interconnect=${JSON.stringify(interconnect)}`
    );*/
    if (break_number === undefined || resources === undefined || interconnect === undefined) {
      return false;
    }

    let break_string = "Break";
    if (break_number == 2) break_string = "Break2";
    const resource = resources.filter(
      (element) =>
        element.features.break_unit === break_string &&
        element.resourceType === "timer_break_input"
    );

    const break_id = resource.map((break_name) => break_name.id);

    /*console.log(
      `[INFO]                 : resource=${JSON.stringify(break_id)}`
    );*/
    return interconnect.filter((interconnect) =>
      break_id.includes(interconnect.ip_signal)
    );
  } catch (e) {
    console.log(`[ERROR] helper_tim_synchronized_breaks: ${e}`);
    return "";
  }
}

/**
 * Check if the break line has a configurable polarity
 * @param {string} break_line Break line ID
 * @param {object} resources List of resources
 * @returns {boolean} true if the break line has a configurable polarity, false otherwise
 */
function helper_tim_check_break_polarity(break_line, resources) {
  try {
    /*console.log(
      `[INFO] helper_tim_check_break_polarity: break_line=${break_line} resources=${JSON.stringify(
        resources
      )}`
    );*/
    if (break_line === undefined || resources === undefined) {
      return false;
    }

    const resource = resources.find((resource) => resource.id === break_line);
    /*console.log(
      `[INFO]                 : resource=${JSON.stringify(resource)}`
    );*/
    if (resource == undefined) return false;
    return resource.features.configurable_polarity;
  } catch (e) {
    console.log(`[ERROR] helper_tim_check_break_polarity: ${e}`);
    return false;
  }
}

/**
 * Check if input_source string needs to enable HSE32EN
 * @param {string} input_source
 * @returns {boolean} true if "HSE_DIV32" is found, false otherwise
 */
function helper_tim_input_source_is_hse_div32(input_source) {
  try {
    if (typeof input_source !== "string") {
      return false;
    }
    return input_source.includes("HSE_DIV32");
  } catch (e) {
    console.log(`[ERROR] helper_tim_input_source_is_hse_div32: ${e}`);
    return false;
  }
}

/**
 * Check if the input channel is used as a clock source for polarity and filter parameters
 * @param {string} channel Channel ID (e.g., "CC1", "CC2")
 * @param {object} trigger_input Clock Source trigger input
 * @returns {string} If the channel is used as a clock source:
 *                    - returns "PF" if polarity and filter from clock source are needed.
 *                    - returns "F" if only filter from clock source is needed, polarity from channel parameters.
 *                    - returns "" if channel polarity and filter parameters must be used.
 */
function helper_tim_input_channel_clock_source(channel, trigger_input) {
  try {
    /*console.log(
      `[INFO] helper_tim_input_channel_clock_source: channel=${JSON.stringify(channel)}, trigger_input=${JSON.stringify(trigger_input)}`
    );*/
    if (typeof channel !== "string" || typeof trigger_input !== "string") {
      console.log(`[WARNING] helper_tim_input_channel_clock_source: Invalid parameters`);
      return "WARNING";
    }
    const map = {
      CC1: { TI1FP1: "PF", TI1F_ED: "F" },
      CC2: { TI2FP2: "PF" }
    };
    return (map[channel] && map[channel][trigger_input]) || "";
  } catch (e) {
    console.log(`[ERROR] helper_tim_input_channel_clock_source: ${e}`);
    return "ERROR";
  }
}

/**
 * Check if any channel has a delayed break mode matching the given delay string
 * @param {string} delay_str Delay string ("DELAY1", "DELAY2", etc.)
 * @param {object} channels list of configured channels
 * @returns true if at least one break_mode matches delay_str
 */
function helper_tim_check_if_channel_delayed_break(delay_str, channels) {
  let result = false;
  try {
    /*console.log(
      `[INFO] helper_tim_check_if_channel_delayed_break: delay_str= ${JSON.stringify(
        delay_str)}, channels=${JSON.stringify(channels)}`
    );*/
    if (
      typeof delay_str !== "string" ||
      !delay_str.startsWith("DELAY") ||
      channels === undefined
    ) {
      return false;
    }
    result = channels.some(ch => {
      if (!ch.use_channel) return false;
      const ocx = ch.output_configuration?.ocx_channel_config?.break_mode;
      const ocxn = ch.output_configuration?.ocxn_channel_config?.break_mode;
      return ocx === delay_str || ocxn === delay_str;
    });
  } catch (e) {
    console.log(`[ERROR] helper_tim_check_if_channel_delayed_break: ${e}`);
  }
  return result;
}

module.exports = {
  helper_tim_synchronized_breaks,

  helper_tim_check_break_polarity,

  helper_tim_find_channel_config_in_input,

  helper_tim_channel_check_indirect,

  helper_tim_need_at_least_one_gpio,

  helper_tim_need_gpio_channel,

  helper_tim_need_gpio_break,

  helper_tim_check_if_at_least_one_channel_in_output,

  helper_tim_check_if_at_least_one_channel_in_input_trc,

  helper_tim_check_if_at_least_one_channel_in_input_or_output,

  helper_tim_check_if_at_least_one_channel_uses_ocref_clear,

  helper_tim_check_if_at_least_one_cc_dma_channel,

  helper_tim_check_if_pulse_generator_ch3_ch4,

  helper_tim_find_channel_config_in_output,

  helper_tim_check_if_at_least_channel_and_complementary_in_output,

  helper_tim_find_channel_config,

  helper_tim_compute_frequency,

  helper_tim_compute_prescaler,

  helper_tim_compute_period,

  helper_tim_compute_sampling_clock,

  helper_tim_convert_channel,

  helper_tim_convert_input_src,

  helper_tim_convert_break_input,

  helper_tim_input_source_is_hse_div32,

  helper_tim_input_channel_clock_source,

  helper_tim_check_if_channel_delayed_break
};
