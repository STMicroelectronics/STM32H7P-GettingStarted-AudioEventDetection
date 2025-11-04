/**
 * @file Helpers functions used for FDCAN SW component
 * @author GPM Application Team
 * @license
 * Copyright (c) 2025 STMicroelectronics.
 * All rights reserved.
 *
 * This software is licensed under terms that can be found in the LICENSE file
 * in the root directory of this software component.
 * If no LICENSE file comes with this software, it is provided AS-IS.
 */

/* Internal cache for memoization of bit timing calculations */
const _fdcan_bit_timing_cache = {};

/**
 * Calculate Time Quantum
 * @param   {number} input_clock FDCAN input clock
 * @param   {number} prescaler FDCAN prescaler
 * @param   {number} clock_divider FDCAN Clock Divider
 * @returns {number} time_quantum Time Quantum
 */
function helper_fdcan_calculate_time_quantum(input_clock, prescaler, clock_divider) {
  let time_quantum;
  try {
    console.log(
      `[INFO] helper_fdcan_calculate_time_quantum: input_clock=${input_clock}, prescaler=${prescaler},clock_divider=${clock_divider} `
    );

    let time_quantum = ((prescaler * clock_divider) / input_clock) * 1e+9;
    console.log(`[INFO] helper_fdcan_calculate_time_quantum: ${time_quantum}`);
    return time_quantum;

  } catch (e) {
    console.log(`[ERROR] helper_fdcan_calculate_time_quantum: ${e}`);
    return 0;
  }
}

/**
 * Calculate Bit Time
 * @param   {number} bit_time_segment1 Time segment1
 * @param   {number} bit_time_segment2 Time segment2
 * @param   {number} tq Time Quantum in ns
 * @returns {number} Bit Time in ns
 */
function helper_fdcan_calculate_bit_time(bit_time_segment1, bit_time_segment2, tq) {
  let bit_time;
  try {
    console.log(
      `[INFO] helper_fdcan_calculate_bit_time: bit_time_segment1=${bit_time_segment1}, bit_time_segment2=${bit_time_segment2}, tq=${tq}`);
    /* Multiply the total number of segments by the time quantum to get the  bit time */
    bit_time = tq * (bit_time_segment1 + bit_time_segment2 + 1);
    console.log(`[INFO] helper_fdcan_calculate_bit_time: ${bit_time}`);
    return bit_time;
  } catch (e) {
    console.log(`[ERROR] helper_fdcan_calculate_bit_time: ${e}`);
    return 0;
  }
}

/**
  * Calculate  Bitrate of FDCAN
  * @param   {number} input_clock FDCAN input clock
  * @param   {number} prescaler FDCAN prescaler
  * @param   {number} clock_divider FDCAN Clock Divider
  * @param   {number} bit_time_segment1 Bit time segment1
  * @param   {number} bit_time_segment2 Bit time segment2
  * @returns {number} Bitrate in bps
 */
function helper_fdcan_calculate_bitrate(input_clock, prescaler, clock_divider, bit_time_segment1, bit_time_segment2) {
  let bitrate;
  try {
    console.log(
      `[INFO] helper_fdcan_calculate_bitrate: input_clock=${input_clock}, prescaler=${prescaler}, clock_divider=${clock_divider}, bit_time_segment1=${bit_time_segment1}, bit_time_segment2=${bit_time_segment2}`);
    bitrate = (input_clock / ((bit_time_segment1 + bit_time_segment2 + 1) * prescaler * clock_divider));
    console.log(`[INFO] helper_fdcan_calculate_bitrate: bitrate=${bitrate}`);
    return bitrate;

  } catch (e) {
    console.log(`[ERROR] helper_fdcan_calculate_bitrate: ${e}`);
    return 0;
  }
}

/**
 * Calculate sampling point
 * @param   {number} bit_time_segment1 Bit time segment1
 * @param   {number} bit_time_segment2 Bit time segment2
 * @returns {number} Sampling point in permille
 */
function helper_fdcan_calculate_sampling_point(bit_time_segment1, bit_time_segment2) {
  let sampling_point;
  try {
    console.log(
      `[INFO] helper_fdcan_calculate_sampling_point: bit_time_segment1=${bit_time_segment1}, bit_time_segment2=${bit_time_segment2}`);

    /* Calculate the sampling point */
    sampling_point = ((bit_time_segment1 * 1000) + 1000) / (bit_time_segment1 + bit_time_segment2 + 1);

    console.log(`[INFO] helper_fdcan_calculate_sampling_point: ${sampling_point}`);
    return sampling_point;
  } catch (e) {
    console.log(`[ERROR] helper_fdcan_calculate_sampling_point: ${e}`);
    return 0;
  }
}


/**
 * Compute the FDCAN nominal or data bit timings from input bus parameters.
 * This function mimics the logic of STM32_UTILS_FDCAN_ComputeBitTiming (C),
 * It iterates over possible prescaler values to find a configuration that matches
 * the requested bitrate and sample point within tolerance.
 * @param {Object} bus_param - Input bus parameters:
 *                 {number} fdcan_ker_clk_khz - FDCAN kernel clock in kHz
 *                 {number} desired_bitrate_kbps - Desired bitrate in kbps
 *                 {number} sample_point_per_mille - Desired sample point in permille (e.g. 875 for 87.5%)
 *                 {number} bitrate_tolerance_per_mille - Allowed bitrate deviation in permille
 * @param {string} bit_timing_type - 'nominal' or 'data'
 * @returns {Object} Result object with:
 *                   {Object} bit_timing - { prescaler, time_seg1, time_seg2 }
 *                   {boolean} found_status - true if a valid configuration was found, false otherwise
 */
function helper_fdcan_compute_bit_timing(bus_param, bit_timing_type) {
  /* Memoization: cache results for repeated calls with same parameters */
  const cacheKey = JSON.stringify({ bus_param, bit_timing_type });
  if (_fdcan_bit_timing_cache.hasOwnProperty(cacheKey)) {
    return _fdcan_bit_timing_cache[cacheKey];
  }
  try {
    /* Timing limits */
    const NOMINAL = { PRESCALER_MIN: 1, PRESCALER_MAX: 512, TIME_SEG1_MIN: 2, TIME_SEG1_MAX: 256, TIME_SEG2_MIN: 2, TIME_SEG2_MAX: 128 };
    const DATA = { PRESCALER_MIN: 1, PRESCALER_MAX: 32, TIME_SEG1_MIN: 1, TIME_SEG1_MAX: 32, TIME_SEG2_MIN: 1, TIME_SEG2_MAX: 16 };

    if (!bus_param) {
      console.log(`[ERROR] helper_fdcan_compute_bit_timing: Invalid input parameter (bus_param is null or undefined)`);
      return {
        bit_timing: { prescaler: 1, time_seg1: 1, time_seg2: 1 },
        found_status: false
      };
    }

    const LIM = (bit_timing_type === 'nominal') ? NOMINAL : DATA;
    let found = false;
    let result = {
      bit_timing: { prescaler: 1, time_seg1: 1, time_seg2: 1 },
      found_status: false
    };

    /* Precompute values as floats */
    const clk = bus_param.fdcan_ker_clk_khz;
    const sp = bus_param.sample_point_per_mille;
    const bitrate = bus_param.desired_bitrate_kbps;
    const tol = bus_param.bitrate_tolerance_per_mille;
    const tmp_multiply_clk_sample_point = clk * sp;
    const tmp_num = (1000 * clk) - tmp_multiply_clk_sample_point;

    for (let prescaler = LIM.PRESCALER_MIN; prescaler <= LIM.PRESCALER_MAX; prescaler++) {
      const product_presc_bitrate = prescaler * bitrate * 1000;
      if (product_presc_bitrate === 0) continue;

      /* Use Math.round for closest integer, but keep all math as float */
      const tseg1 = Math.round(tmp_multiply_clk_sample_point / product_presc_bitrate) - 1;
      const tseg2 = Math.round(tmp_num / product_presc_bitrate);

      if (
        tseg1 >= LIM.TIME_SEG1_MIN && tseg1 <= LIM.TIME_SEG1_MAX &&
        tseg2 >= LIM.TIME_SEG2_MIN && tseg2 <= LIM.TIME_SEG2_MAX
      ) {
        /* Compute real sample point and bitrate as floats */
        const real_sample_point_per_mille = Math.round((1000 + 1000 * tseg1) / (1 + tseg1 + tseg2));
        const real_bitrate_kbps = Math.round((clk * real_sample_point_per_mille) / (1000 * (prescaler * (1 + tseg1))));

        /* Compute deviation in permille */
        const sum = bitrate + real_bitrate_kbps;
        const diff = Math.abs(bitrate - real_bitrate_kbps);
        const deviation = Math.ceil((2 * 1000 * diff) / sum);

        if (deviation > tol) continue;

        /* Found a valid configuration */
        result = {
          bit_timing: {
            prescaler: prescaler,
            time_seg1: tseg1,
            time_seg2: tseg2
          },
          found_status: true
        };
        found = true;
        break;
      }
    }
    if (!found) {
      console.log(`[INFO] helper_fdcan_compute_bit_timing: No valid parameters found for input:`, bus_param, `bit_timing_type=${bit_timing_type}`);
    }

    /* Store in cache before returning */
    _fdcan_bit_timing_cache[cacheKey] = result;
    return result;
  } catch (e) {
    console.log(`[ERROR] helper_fdcan_compute_bit_timing: ${e}`);
    const errorResult = {
      bit_timing: { prescaler: 1, time_seg1: 1, time_seg2: 1 },
      found_status: false
    };
    _fdcan_bit_timing_cache[cacheKey] = errorResult;
    return errorResult;
  }
}

module.exports = {
  helper_fdcan_calculate_bitrate,
  helper_fdcan_calculate_time_quantum,
  helper_fdcan_calculate_bit_time,
  helper_fdcan_calculate_sampling_point,
  helper_fdcan_compute_bit_timing
};
