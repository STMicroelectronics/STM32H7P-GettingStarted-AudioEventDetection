/**
 * @file Helpers functions used for WWDG SW component
 * @author GPM Application Team
 * @license
 * Copyright (c) 2024 STMicroelectronics.
 * All rights reserved.
 *
 * This software is licensed under terms that can be found in the LICENSE file
 * in the root directory of this software component.
 * If no LICENSE file comes with this software, it is provided AS-IS.
 */

const WWDG_MIN_RELOAD = 1;
const WWDG_MAX_RELOAD = 4096;
const WWDG_MIN_PRESCALER = 4;
const WWDG_MAX_STEP_NUMBER = 64;
const WWDG_MAX_PRESCALER = 128;
const WWDG_MAX_PRESCALER_REG = 8;
const WWDG_TIME_CONVERSION = 1000;


/**
 * This function returns the correct unit title depending on the unit const.
 * @param {string}  unit  Time unit selected by the user in Core window
 * @returns {string} Unit (us, ms, s)
 */
function helper_wwdg_stringify_unit(unit) {

  try {
    console.log(`[INFO] helper_wwdg_stringify_unit, unit=${JSON.stringify(unit)}`);
    unit = (unit === 'HAL_WWDG_TIME_UNIT_S' ? 's' : unit === 'HAL_WWDG_TIME_UNIT_MS' ? 'ms' : unit === 'HAL_WWDG_TIME_UNIT_US' ? 'us' : '');

  } catch (e) {
    console.log(`[ERROR] helper_wwdg_check_time: ${e}`);
  }

  return unit;
}

/**
 * This function computes the minimum time input allowed.
 * @param {integer} freq WWDG input frequency (Hz)
 * @param {string}  unit  Time unit selected by the user in Core window
 * @returns {integer} Minimum time allowed for a specified unit
 */
function helper_wwdg_get_min_allowed_time(freq, unit) {
  let allowed_min = 0;

  try {
    console.log(`[INFO] helper_wwdg_min_allowed_time, freq=${JSON.stringify(freq)}, unit=${JSON.stringify(unit)}`);
    allowed_min = ((WWDG_MIN_PRESCALER * WWDG_MIN_RELOAD * WWDG_TIME_CONVERSION) / freq);

    if (unit === 'HAL_WWDG_TIME_UNIT_US') {
      allowed_min = allowed_min * WWDG_TIME_CONVERSION;
    } else if (unit === 'HAL_WWDG_TIME_UNIT_MS') {
      /* Do nothing */
    } else if (unit === 'HAL_WWDG_TIME_UNIT_S') {
      allowed_min = allowed_min / WWDG_TIME_CONVERSION;
    } else {
      throw new Error('Unsupported time unit');
    }

  } catch (e) {
    console.log(`[ERROR] helper_wwdg_min_allowed_time: ${e}`);
  }

  return Math.ceil(allowed_min);
}

/**
 * This function computes the maximum time input allowed.
 * @param {integer} freq WWDG input frequency (Hz)
 * @param {string}  unit  Time unit selected by the user in Core window
 * @returns {integer} Maximum time allowed for a specified unit
 */
function helper_wwdg_get_max_allowed_time(freq, unit) {
  let allowed_max = 0;

  try {
    console.log(`[INFO] helper_wwdg_get_max_allowed_time, freq=${JSON.stringify(freq)}, unit=${JSON.stringify(unit)}`);

    allowed_max = ((WWDG_MAX_PRESCALER * WWDG_MAX_RELOAD * WWDG_MAX_STEP_NUMBER * WWDG_TIME_CONVERSION) / freq);
    if (unit === 'HAL_WWDG_TIME_UNIT_US') {
      allowed_max = allowed_max * WWDG_TIME_CONVERSION;
    } else if (unit === 'HAL_WWDG_TIME_UNIT_MS') {
      /* Do nothing */
    } else if (unit === 'HAL_WWDG_TIME_UNIT_S') {
      allowed_max = allowed_max / WWDG_TIME_CONVERSION;
    } else {
      throw new Error('Unsupported time unit');
    }

  } catch (e) {
    console.log(`[ERROR] helper_wwdg_get_max_allowed_time: ${e}`);
  }

  return Math.ceil(allowed_max);
}

/**
 * This function compute the prescaler then used by adjust_time for Max, Min and EWI time
 * @param {integer} freq WWDG input frequency (Hz)
 * @param {integer} max_time Max time requested by the user
 * @param {string}  unit  Time unit selected by the user in Core window
 * @returns {integer} WWDG prescaler
 */
function helper_wwdg_compute_prescaler(freq,max_time,unit) {
  let prescaler = 0;
  let max_period;
  try {
    if (unit === 'HAL_WWDG_TIME_UNIT_US') {
      max_period = max_time * WWDG_TIME_CONVERSION;
    } else if (unit === 'HAL_WWDG_TIME_UNIT_MS') {
      max_period = max_time;
    } else if (unit === 'HAL_WWDG_TIME_UNIT_S') {
      max_period = max_time / WWDG_TIME_CONVERSION;
    } else {
      throw new Error("Unsupported time unit");
    }
    /* Return the calculated prescaler */
    console.log(`[INFO] helper_wwdg_compute_prescaler, converted_max_time=${JSON.stringify(max_period)}`);

    max_period = Math.floor(((max_period * freq) / WWDG_TIME_CONVERSION) / (4 * WWDG_MAX_RELOAD));
    prescaler = 32 - Math.clz32(max_period);

    console.log(`[INFO] helper_wwdg_compute_prescaler, prescaler=${JSON.stringify(prescaler)}`);

    if (prescaler > WWDG_MAX_PRESCALER_REG) {
      prescaler = WWDG_MAX_PRESCALER_REG;
    }

  } catch (error) {
    console.error('Error calculating prescaler:', error);
    return prescaler;
  }
}

/**
 * This function compute the step then used by adjust_time for Max, Min and EWI time
 * @param {integer} freq IWDG input frequency (Hz)
 * @param {integer} prescaler IWDG prescaler
 * @param {string}  unit  Time unit selected by the user in Core window
 * @returns {float} IWDG time step
 */
function helper_wwdg_compute_step(freq, prescaler, unit) {
  let step = 0;

  try {
    console.log(`[INFO] helper_wwdg_compute_step, freq=${JSON.stringify(freq)}, prescaler=${JSON.stringify(prescaler)}, unit=${JSON.stringify(unit)}`);

    /* Calculate step (ms) */
    prescaler = Math.pow(2, prescaler + 2);
    step = prescaler * WWDG_TIME_CONVERSION / freq;

    /* Adjust Max time value */
    if (unit === 'HAL_WWDG_TIME_UNIT_US') {
      step = (step * WWDG_TIME_CONVERSION);
    } else if (unit === 'HAL_WWDG_TIME_UNIT_MS') {
      /* Do nothing */
    } else if (unit === 'HAL_WWDG_TIME_UNIT_S') {
      step = (step / WWDG_TIME_CONVERSION);
    } else {
      throw new Error('Unsupported time unit');
    }

    console.log(`[INFO] helper_wwdg_compute_step, step=${JSON.stringify(step)}`);

  } catch (e) {
    console.log(`[ERROR] helper_wwdg_compute_step: ${e}`);
  }

  return Number(step.toFixed(3));;
}

/**
 * This function suggest a new time based on the step between two possible
 * values
 * @param {float} step WWDG time step
 * @param {integer} input_time Time requested by the user
 * @returns {integer} Adjusted time
 */
function helper_wwdg_adjust_time(step, input_time) {
  let adjusted_time = 0;
  let remainder = 0;

  try {
    console.log(`[INFO] helper_wwdg_adjust_time, step=${JSON.stringify(step)}, input_time=${JSON.stringify(input_time)}`);

    remainder = input_time % step;
    console.log(`[INFO] helper_wwdg_adjust_time, remainder_step=${JSON.stringify(remainder)}`);
    if (input_time < step) {
      adjusted_time = 0;
    } else {
      adjusted_time = input_time - remainder;
      if (remainder > (step / 2)) {
        adjusted_time += step;
      }
    }
    console.log(`[INFO] helper_wwdg_adjust_time, adjusted_time=${JSON.stringify(adjusted_time)}`);

  } catch (e) {
    console.log(`[ERROR] helper_wwdg_adjust_time: ${e}`);
  }
  return Number(adjusted_time.toFixed(2));
}

/**
 * This function calculate the WWDG reload .
 * @param {integer} freq WWDG input frequency (Hz)
 * @param {integer} max_time Max time requested by the user
 * @param {string}  unit  Time unit selected by the user in Core window
 * @returns {integer} Calclated value for reload 
 */
function helper_wwdg_compute_reload(freq, prescaler, max_time, unit) {
  let tmp;
  let reload;
  let clk_divider;

  try {
    console.log(`[INFO] helper_wwdg_compute_reload, freq=${JSON.stringify(freq)}, prescaler=${JSON.stringify(prescaler)}, max_time=${JSON.stringify(max_time)}, unit=${JSON.stringify(unit)}`);
    /* Calculate the clock divider */
    clk_divider = Math.pow(2, prescaler & 0x7);
    tmp = (((max_time * (freq / clk_divider)) / WWDG_MAX_RELOAD) / 1000) + WWDG_MAX_STEP_NUMBER;

    if (unit === 'HAL_WWDG_TIME_UNIT_US') {
      reload = tmp * WWDG_TIME_CONVERSION;
    } else if (unit === 'HAL_WWDG_TIME_UNIT_MS') {
      reload = tmp;
    } else if (unit === 'HAL_WWDG_TIME_UNIT_S') {
      reload = tmp / WWDG_TIME_CONVERSION;
    } else {
      throw new Error('Unsupported time unit');
    }
    console.log(`[INFO] helper_wwdg_compute_reload, reload=${JSON.stringify(reload)}`);
  } catch (e) {
    console.log(`[ERROR] helper_wwdg_compute_reload: ${e}`);
  }

  return Math.ceil(reload);
}

/**
 * This function calculate the WWDG window .
 * @param {integer} freq WWDG input frequency (Hz)
 * @param {integer} prescaler WWDG prescaler
 * @param {integer} reload Max time requested by the user
 * @param {integer} param Max time requested by the user
 * @param {string}  unit  Time unit selected by the user in Core window
 * @returns {integer} WWDG window
 */
function helper_wwdg_compute_param(freq, prescaler, reload, param, unit) {
  let tmp = 0;

  try {
    console.log(`[INFO] helper_wwdg_compute_param, freq=${JSON.stringify(freq)}, prescaler=${JSON.stringify(Number(prescaler))}, reload=${JSON.stringify(reload)},  param=${JSON.stringify(param)}, unit=${JSON.stringify(unit)}`);

    if (unit === 'HAL_WWDG_TIME_UNIT_US') {
      tmp = param * WWDG_TIME_CONVERSION;
    } else if ('unit === HAL_WWDG_TIME_UNIT_MS') {
      tmp = param ;
    } else if (unit === 'HAL_WWDG_TIME_UNIT_S') {
      tmp = param / WWDG_TIME_CONVERSION; 
    }

    param = reload - ((tmp * freq) / (WWDG_TIME_CONVERSION * WWDG_TIME_CONVERSION * Math.pow(2, Number(prescaler) + 2)));
    console.log(`[ERROR] helper_wwdg_compute_param: param=${JSON.stringify(param)}`);
  } catch (e) {
    console.log(`[ERROR] helper_wwdg_compute_param: ${e}`);
  }

  return Math.floor(param);
}

module.exports = {
  helper_wwdg_stringify_unit,
  helper_wwdg_compute_step,
  helper_wwdg_get_min_allowed_time,
  helper_wwdg_get_max_allowed_time,
  helper_wwdg_adjust_time,
  helper_wwdg_compute_prescaler,
  helper_wwdg_compute_reload,
  helper_wwdg_compute_param

};
