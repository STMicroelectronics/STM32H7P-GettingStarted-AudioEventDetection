
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
 * Check if at least one DMA channel has been enabled
 * @param {object} dma_settings System.DMA_Settings object
 * @returns true or false
 */
function helper_lptim_check_if_at_least_one_dma_channel(dma_settings) {
  let result = false;
  try {
    console.log(
      `[INFO] helper_lptim_check_if_at_least_one_dma_channel: dma_settings=${JSON.stringify(
        dma_settings
      )}`
    );
    if (dma_settings === undefined) {
      return false;
    }
    if (
      dma_settings.EnableDMA_CC1 !== undefined &&
      dma_settings.EnableDMA_CC1
    ) {
      result = true;
      console.log(`   DMA Channel1 found`);
      return result;
    }
    if (
      dma_settings.EnableDMA_CC2 !== undefined &&
      dma_settings.EnableDMA_CC2
    ) {
      result = true;
      console.log(`   DMA Channel2 found`);
      return result;
    }
    if (dma_settings.EnableDMA_UP !== undefined && dma_settings.EnableDMA_UP) {
      result = true;
      console.log(`   DMA update found`);
      return result;
    }
    if (
      dma_settings.EnableDMA_UE !== undefined &&
      dma_settings.EnableDMA_UE
    ) {
      result = true;
      console.log(`   DMA update event found`);
      return result;
    }
  } catch (e) {
    console.log(`[ERROR] helper_lptim_check_if_at_least_one_dma_channel: ${e}`);
    return result;
  }
}
/**
 * Check if channel_id has been configured (output or input)
 * @param {object} channels list of configured channels
 * @param {integer} channel_id id of the channel
 * @returns true or false
 */
function helper_lptim_find_channel_config(channels, channel_id) {
  let result = false;
  try {
    console.log(
      `[INFO] helper_lptim_find_channel_config: channels=${JSON.stringify(
        channels
      )}, channel_id=${channel_id}`
    );
    if (channels === undefined) {
      return false;
    }
    for (var i = 0; i < channels.length; i++) {
      if (
        channels[i].use_channel !== undefined &&
        channels[i].use_channel &&
        channels[i].channel_direction === "Input" &&
        channels[i]._foreignKey === channel_id.toString()
      ) {
        result = true;
        console.log(
          `   Channel configuration found on ${channels[i]._foreignKey}`
        );
        break;
      }
    }
  } catch (e) {
    console.log(`[ERROR] helper_lptim_find_channel_config: ${e}`);
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
function helper_lptim_compute_frequency(
  input_clock_frequency,
  prescaler,
  period
) {
  let result = 10000; /* default value to 10KHz */
  try {
    console.log(
      `[INFO] helper_lptim_compute_frequency: input_clock_frequency=${input_clock_frequency}, prescaler=${prescaler}, period=${period}`
    );
    /* get value prescaler (ex : From DIV4 -> to 4) */
    var pattern = /\d+/g;
    var prescaler_id = prescaler.match(pattern);
    /* Calculate the actual timer frequency */
    var lptimer_frequency = input_clock_frequency / (prescaler_id + 1);
    /* Calculate the actual output frequency */
    var output_frequency = lptimer_frequency / (period + 1);
    /* Return the output frequency */
    result = Math.floor(output_frequency);
  } catch (e) {
    console.log(`[ERROR] helper_lptim_compute_frequency: ${e}`);
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
function helper_lptim_compute_prescaler(input_clock_frequency, output_frequency) {
  let result = 123456789;
  try {
    console.log(
      `[INFO] helper_lptim_compute_prescaler: input_clock_frequency=${input_clock_frequency}, output_frequency=${output_frequency}`
    );
    if (output_frequency != 0) {
      /* Calculate the prescaler value */
      var prescaler = input_clock_frequency / output_frequency - 1;
      /* Return the prescale value */
      result = Math.floor(prescaler);
    }
  } catch (e) {
    console.log(`[ERROR] helper_lptim_compute_prescaler: ${e}`);
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
function helper_lptim_compute_period(input_clock_frequency, output_frequency) {
  let result = 123456789;
  try {
    console.log(
      `[INFO] helper_lptim_compute_period: input_clock_frequency=${input_clock_frequency}, output_frequency=${output_frequency}`
    );
    /* Calculate the actual output frequency */
    var period = output_frequency - 1;
    /* Return the period value */
    return Math.floor(period);
  } catch (e) {
    console.log(`[ERROR] helper_lptim_compute_period: ${e}`);
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
function helper_lptim_compute_sampling_clock(input_clock_frequency, clock_divider, sampling_ck_div) {
  let result = input_clock_frequency;
  const regex = /FDIV(\d+)_?/;
  const samp_ck_div = sampling_ck_div.match(regex);
  try {
    console.log(
      `[INFO] helper_lptim_compute_sampling_clock: input_clock_frequency=${input_clock_frequency}, clock_divider=${clock_divider},
      sampling_ck_div=${sampling_ck_div}, samp_ck_div=${samp_ck_div}`
    );
    if (samp_ck_div === 1) {
      /* DIV1: fSAMPLING = ftim_ker_ck */
      /* result = input_clock_frequency; */
    }
    else {
      /* DIVx: fSAMPLING = fDTS / x ; with fDTS = ftim_ker_ck / CKD */
      result = input_clock_frequency / clock_divider / samp_ck_div;
    }
    result = Math.floor(result);
  } catch (e) {
    console.log(`[ERROR] helper_lptim_compute_sampling_clock: ${e}`);
  }
  return result;
}
/**
 * Check if the channel_id needs to configure a GPIO
 * @param {object} channel element of the channels list
 * @param {integer} channel_id id of the channel
 * @returns true or false
 */
function lptim_need_gpio(channel, channel_id) {
  let result = false;
  console.log(
    `[INFO] helper_need_gpio: channel=${JSON.stringify(
      channel
    )}, channel_id=${channel_id}`
  );
  try {
    if (channel === undefined || channel_id === undefined) {
      return false;
    }
    if (
      channel !== undefined &&
      channel.use_channel !== undefined &&
      channel.use_channel
    ) {
      /* in input mode, GPIO must be configured only if the input capture source is set to ic1_mux1 */
      if (
        channel.channel_direction === "Input" &&
        channel.ic_source !== undefined &&
        channel.ic_source.source === "I/O")
      {
        result = true;
        console.log(
          `[INFO] lptim_need_gpio Input Channel ${channel_id} configured to GPIO`
        );
      }
    }
  } catch (e) {
    console.log(`[ERROR] lptim_need_gpio: ${e}`);
  }
  return result;
}
/**
 * Check if the channel_id needs to configure a GPIO
 * @param {object} channels list of configured channels
 * @param {integer} channel_id id of the channel
 * @returns true or false
 */
function helper_lptim_need_gpio_channel(data, channel_id) {
  let result = false;
  try {
    console.log(
      `[INFO] helper_lptim_need_gpio_channel: data=${JSON.stringify(
        data
      )}, channel_id=${channel_id}`
    );
    if (data === undefined || channel_id === undefined) {
      return false;
    }
    const channel_id_str = channel_id.toString();
    let config_ch = data.channels.find(function (channel) {
      return channel["_foreignKey"] === channel_id_str;
    });
    if (config_ch.use_channel == true &&
       (config_ch.channel_direction === 'Output' ) ||
       (config_ch.channel_direction === 'Input' &&
       (config_ch.input_configuration.ic_source.source === 'I/O' || 
        config_ch.input_configuration.ic_source.source === 'GPIO'))) {
        result = true;
        console.log(`[INFO] helper_lptim_need_gpio_channel: Use Channel and GPIO is true`);
    }
  } catch (e) {
    console.log(`[ERROR] helper_lptim_need_gpio_channel: ${e}`);
  }
  return result;
}
/**
 * Check if the input_id needs to configure a GPIO
 * @param {object} data list of input config
 * @returns true or false
 */
function helper_lptim_need_gpio_input(data) {
  let result = false;
  try {
    console.log(
      `[INFO] helper_lptim_need_gpio_input: data=${JSON.stringify(
        data
      )}`
    );
    if (data === undefined) {
      return false;
    }
    if (data.source === 'I/O' || data.source === 'GPIO')
    {
      result = true;
      console.log(`[INFO] helper_lptim_need_gpio_input: Use ${data.ip_signal} and GPIO is active`);
    }
  } catch (e) {
    console.log(`[ERROR] helper_lptim_need_gpio_input: ${e}`);
  }
  return result;
}
/**
 * Return id channel from his channel name. CH2 return 2.
 * @param {string} source Channel's name
 * @returns Channel's number
 */
function helper_lptim_get_channel_id(source)
{
  var id = 0;
  if (source === undefined)
  {
    console.warning(`[ERROR] helper_lptim_get_channel_id: source undefined`);
    return 0;
  }
  try {
    var pattern = /\d+/g;
    id = source.match(pattern);
  }
  catch {
    console.error(`[ERROR] helper_lptim_get_channel_id: source undefined`);
  }
    return id;
}
/**
 * Convert HW input enum ID to HAL Input ID
 * @note  This api is used directly in the lptim_parameters.json in basic view
 * @param {string} source input source selection (ex 'COMP1_OUT')
 * @param {string} layer HAL
 * @returns {string} HAL Input ID (COMP1)
 */
function helper_lptim_convert_input_src(source, layer = "HAL") {
  try {
    console.log(
      `[INFO] helper_lptim_convert_input_src: source=${source}, layer=${layer}`
    );
    // Define the layered map
    let source_upper = source.toUpperCase();
    const map_input = {
      HAL: {
        "I/O": "GPIO",
        "COMP1_OUT": "COMP1",
        "COMP2_OUT": "COMP2",
        "COMP3_OUT": "COMP3",
        "COMP4_OUT": "COMP4",
        "COMP5_OUT": "COMP5",
        "COMP6_OUT": "COMP6",
        "RCC_MCO1": "MCO1",
        "RTC_ALRA_TRG": "RTC_ALMA",
        "RTC_ALRB_TRG": "RTC_ALMB",
        "LPDMA1_CH1_TCF": "LPDMA_CH1_TC",
        "GPDMA_CH1_TCF": "GPDMA_CH1_TC",
        "TAMP_TRG1": "TAMP1",
        "TAMP_TRG2": "TAMP2",
        "TAMP_TRG3": "TAMP3",
        "HSI/256": "HSI_256",
        "HSI/1024": "HSI_1024",
        "MSI/1024": "MSI_1024",
        "MSI/4": "MSI_4",
        "PLAY1_OUT8": "PLAYOUT8",
        "PLAY1_OUT9": "PLAYOUT9",
        "PLAY1_OUT10": "PLAYOUT10",
        "MCG_SYS_CK/4096": "MCG256_1024",
        "MCG_AUDIO_CK /64": "MCG3072_128",
        "I3C2_IBIACKTI": "I3C2_IBIACK",
        "I3C1_IBIACKTI": "I3C1_IBIACK"
      },
      LL: {
        "I/O": "GPIO",
        "COMP1_OUT": "COMP1",
        "COMP2_OUT": "COMP2",
        "COMP3_OUT": "COMP3",
        "COMP4_OUT": "COMP4",
        "COMP5_OUT": "COMP5",
        "COMP6_OUT": "COMP6",
        "RCC_MCO1": "MCO1",
        "RTC_ALRA_TRG": "RTC_ALMA",
        "RTC_ALRB_TRG": "RTC_ALMB",
        "LPDMA1_CH1_TCF": "LPDMA_CH1_TC",
        "GPDMA_CH1_TCF": "GPDMA_CH1_TC",
        "TAMP_TRG1": "RTC_TAMP1",
        "TAMP_TRG2": "RTC_TAMP2",
        "TAMP_TRG3": "RTC_TAMP3",
        "HSI/256": "HSI_256",
        "HSI/1024": "HSI_1024",
        "MSI/1024": "MSI_1024",
        "MSI/4": "MSI_4",
        "PLAY1_OUT8": "PLAYOUT8",
        "PLAY1_OUT9": "PLAYOUT9",
        "PLAY1_OUT10": "PLAYOUT10",
        "MCG_SYS_CK/4096": "MCG256_1024",
        "MCG_AUDIO_CK /64": "MCG3072_128",
        "I3C2_IBIACKTI": "I3C2_IBIACK",
        "I3C1_IBIACKTI": "I3C1_IBIACK"
      }
    };
    // Select the correct map for the layer
    const selected_map = map_input[layer] || map_input["HAL"];
    // Keep your original logic
    let source_map = source_upper;
    if (selected_map.hasOwnProperty(source_upper)) {
      source_map = selected_map[source_upper];
    }
    return source_map;
  } catch (e) {
    console.log(`[ERROR] helper_lptim_convert_input_src: ${e}`);
    return "";
  }
}
module.exports = {
  helper_lptim_get_channel_id,
  helper_lptim_check_if_at_least_one_dma_channel,
  helper_lptim_find_channel_config,
  helper_lptim_need_gpio_channel,
  helper_lptim_need_gpio_input,
  helper_lptim_compute_frequency,
  helper_lptim_compute_prescaler,
  helper_lptim_compute_period,
  helper_lptim_compute_sampling_clock,
  helper_lptim_convert_input_src,
};
