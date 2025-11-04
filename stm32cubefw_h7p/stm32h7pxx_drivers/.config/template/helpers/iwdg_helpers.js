/**
 * @file Helpers functions used for PPP SW component
 * @author GPM Application Team
 * @license
 * Copyright (c) 2024 STMicroelectronics.
 * All rights reserved.
 *
 * This software is licensed under terms that can be found in the LICENSE file
 * in the root directory of this software component.
 * If no LICENSE file comes with this software, it is provided AS-IS.
 */

const IWDG_MIN_RELOAD = 1;
const IWDG_MAX_RELOAD = 4096;
const IWDG_MIN_PRESCALER = 4;
const IWDG_MAX_PRESCALER = 1024;
const IWDG_MAX_PRESCALER_REG = 8;
const IWDG_TIME_CONVERSION = 1000;

/**
 * This function returns the correct unit title depending on the unit constant.
 * @param {string}  unit  Time unit selected by the user in Core window
 * @returns {string} Unit (us, ms, s)
 */
function helper_iwdg_stringify_unit(unit) {

  try {
    console.log(`[INFO] helper_iwdg_stringify_unit, unit=${JSON.stringify(unit)}`);
    unit = (unit === 'HAL_IWDG_TIME_UNIT_S' ? 's' : unit=== 'HAL_IWDG_TIME_UNIT_MS' ? 'ms' : unit=== 'HAL_IWDG_TIME_UNIT_US' ? 'us' : '');

  } catch (e) {
    console.log(`[ERROR] helper_iwdg_stringify_unit: ${e}`);
  }

  return unit;
}

/**
 * This function computes the minimum time input allowed.
 * @param {integer} freq IWDG input frequency (Hz)
 * @param {string}  unit  Time unit selected by the user in Core window
 * @returns {integer} Minimum time allowed for a specified unit
 */
function helper_iwdg_get_min_allowed_time(freq, unit) {
  let allowed_min = 0;

  try {
    console.log(`[INFO] helper_iwdg_get_min_allowed_time, freq=${JSON.stringify(freq)}, unit=${JSON.stringify(unit)}`);

    allowed_min = ((IWDG_MIN_PRESCALER * IWDG_MIN_RELOAD * IWDG_TIME_CONVERSION) / freq);
    if (unit === 'HAL_IWDG_TIME_UNIT_US') {
      allowed_min = allowed_min * IWDG_TIME_CONVERSION;
    } else if (unit === 'HAL_IWDG_TIME_UNIT_MS') {
      /* Do nothing */
    } else if (unit === 'HAL_IWDG_TIME_UNIT_S') {
      allowed_min = allowed_min / IWDG_TIME_CONVERSION;
    } else {
      throw new Error('Unsupported time unit');
    }

  } catch (e) {
    console.log(`[ERROR] helper_iwdg_get_min_allowed_time: ${e}`);
  }

  return Math.ceil(allowed_min);
}

/**
 * This function computes the maximum time input allowed.
 * @param {integer} freq IWDG input frequency (Hz)
 * @param {string}  unit  Time unit selected by the user in Core window
 * @returns {integer} Maximum time allowed for a specified unit
 */
function helper_iwdg_get_max_allowed_time(freq, unit) {
  let allowed_max = 0;

  try {
    console.log(`[INFO] helper_iwdg_get_max_allowed_time, freq=${JSON.stringify(freq)}, unit=${JSON.stringify(unit)}`);

    allowed_max = ((IWDG_MAX_PRESCALER * IWDG_MAX_RELOAD * IWDG_TIME_CONVERSION) / freq);
    if (unit === 'HAL_IWDG_TIME_UNIT_US') {
      allowed_max = allowed_max * IWDG_TIME_CONVERSION;
    } else if (unit === 'HAL_IWDG_TIME_UNIT_MS') {
      /* Do nothing */
    } else if (unit === 'HAL_IWDG_TIME_UNIT_S') {
      allowed_max = allowed_max / IWDG_TIME_CONVERSION;
    } else {
      throw new Error('Unsupported time unit');
    }

  } catch (e) {
    console.log(`[ERROR] helper_iwdg_get_max_allowed_time: ${e}`);
  }

  return  Math.ceil(allowed_max);
}

/**
 * This function compute the step then used by adjust_time for Max, Min and EWI time
 * @param {integer} freq IWDG input frequency (Hz)
 * @param {integer} max_time Max time requested by the user
 * @param {string}  unit  Time unit selected by the user in Core window
 * @returns {integer} IWDG precaler
 */
function helper_iwdg_compute_prescaler(freq, max_time, unit) {
  let prescaler = 0;
  let tmp = 0;

  try {
    console.log(`[INFO] helper_iwdg_compute_prescaler, freq=${JSON.stringify(freq)}, max_time=${JSON.stringify(max_time)}, unit=${JSON.stringify(unit)}`);

    if (unit === 'HAL_IWDG_TIME_UNIT_US') {
      tmp = max_time / IWDG_TIME_CONVERSION;
    } else if (unit === 'HAL_IWDG_TIME_UNIT_MS') {
      tmp = max_time;
    } else if (unit === 'HAL_IWDG_TIME_UNIT_S') {
      tmp = max_time * IWDG_TIME_CONVERSION;
    } else {
      throw new Error('Unsupported time unit');
    }
    console.log(`[INFO] helper_iwdg_compute_prescaler, converted_max_time=${JSON.stringify(tmp)}`);

    tmp = Math.floor(((tmp * freq) / IWDG_TIME_CONVERSION) / (4 * IWDG_MAX_RELOAD));
    prescaler = 32 - Math.clz32(tmp);
    console.log(`[INFO] helper_iwdg_compute_prescaler, prescaler=${JSON.stringify(prescaler)}`);

    if (prescaler > IWDG_MAX_PRESCALER_REG) {
      prescaler = IWDG_MAX_PRESCALER_REG;
    }
  } catch (e) {
    console.log(`[ERROR] helper_iwdg_compute_prescaler: ${e}`);
  }

  return prescaler;
}

/**
 * This function compute the step then used by adjust_time for Max, Min and EWI time
 * @param {integer} freq IWDG input frequency (Hz)
 * @param {integer} prescaler IWDG prescaler
 * @param {string}  unit  Time unit selected by the user in Core window
 * @returns {float} IWDG time step
 */
function helper_iwdg_compute_step(freq, prescaler, unit) {
  let step = 0;
  let tmp = 0;

  try {
    console.log(`[INFO] helper_iwdg_compute_step, freq=${JSON.stringify(freq)}, prescaler=${JSON.stringify(prescaler)}, unit=${JSON.stringify(unit)}`);

    /* Calculate step (ms) */
    prescaler = Math.pow(2, prescaler + 2);
    step = prescaler * IWDG_TIME_CONVERSION / freq;

    /* Adjust Max time value */
    if (unit === 'HAL_IWDG_TIME_UNIT_US') {
      step = (step * IWDG_TIME_CONVERSION);
    } else if (unit === 'HAL_IWDG_TIME_UNIT_MS') {
      /* Do nothing */
    } else if (unit === 'HAL_IWDG_TIME_UNIT_S') {
      step = (step / IWDG_TIME_CONVERSION);
    } else {
      throw new Error('Unsupported time unit');
    }

    console.log(`[INFO] helper_iwdg_compute_step, step=${JSON.stringify(step)}`);

  } catch (e) {
    console.log(`[ERROR] helper_iwdg_compute_step: ${e}`);
  }

  return Number(step.toFixed(3));
}

/**
 * This function compute the step then used by adjust_time for Max, Min and EWI time
 * @param {integer} freq IWDG input frequency (Hz)
 * @param {integer} prescaler IWDG prescaler
 * @param {integer} max_time Max time requested by the user
 * @param {string}  unit  Time unit selected by the user in Core window
 * @returns {integer} IWDG reload
 */
function helper_iwdg_compute_reload(freq, prescaler, max_time, unit) {
  let reload = 0;
  let tmp = 0;

  try {
    console.log(`[INFO] helper_iwdg_compute_reload, freq=${JSON.stringify(freq)}, prescaler=${JSON.stringify(prescaler)}, max_time=${JSON.stringify(max_time)}, unit=${JSON.stringify(unit)}`);

    if (unit === 'HAL_IWDG_TIME_UNIT_US') {
      tmp = max_time;
    } else if (unit === 'HAL_IWDG_TIME_UNIT_MS') {
      tmp = max_time * IWDG_TIME_CONVERSION;
    } else if (unit === 'HAL_IWDG_TIME_UNIT_S') {
      tmp = max_time * IWDG_TIME_CONVERSION * IWDG_TIME_CONVERSION;
    } else {
      throw new Error('Unsupported time unit');
    }

    reload = Math.ceil(((tmp * freq) / (IWDG_TIME_CONVERSION * IWDG_TIME_CONVERSION * Math.pow(2, Number(prescaler) + 2))) - 1);

    if (reload > (IWDG_MAX_RELOAD - 1)) {
      reload = IWDG_MAX_RELOAD - 1;
    }

    console.log(`[INFO] helper_iwdg_compute_reload, reload=${JSON.stringify(reload)}`);
  } catch (e) {
    console.log(`[ERROR] helper_iwdg_compute_reload: ${e}`);
  }

  return  reload;
}


/**
 * This function compute the step then used by adjust_time for Max, Min and EWI time
 * @param {integer} freq IWDG input frequency (Hz)
 * @param {integer} prescaler IWDG prescaler
 * @param {integer} reload Max time requested by the user
 * @param {integer} param Max time requested by the user
 * @param {string}  unit  Time unit selected by the user in Core window
 * @returns {integer} IWDG window
 */
function helper_iwdg_compute_param(freq, prescaler, reload, param, unit) {
  let tmp = 0;

  try {
    console.log(`[INFO] helper_iwdg_compute_param, freq=${JSON.stringify(freq)}, prescaler=${JSON.stringify(Number(prescaler))}, reload=${JSON.stringify(reload)},  param=${JSON.stringify(param)}, unit=${JSON.stringify(unit)}`);

    if (param <= 0) {
      return 0;
    }

    if (unit === 'HAL_IWDG_TIME_UNIT_US') {
      tmp = param;
    } else if (unit === 'HAL_IWDG_TIME_UNIT_MS') {
      tmp = param * IWDG_TIME_CONVERSION;
    } else if (unit === 'HAL_IWDG_TIME_UNIT_S') {
      tmp = param * IWDG_TIME_CONVERSION * IWDG_TIME_CONVERSION;
    } else {
      throw new Error('Unsupported time unit');
    }

      param = Math.ceil(reload - ((tmp * freq) / (IWDG_TIME_CONVERSION * IWDG_TIME_CONVERSION * Math.pow(2, Number(prescaler) + 2))));
      console.log(`[ERROR] helper_iwdg_compute_param: param=${JSON.stringify(param)}`);
    } catch (e) {
    console.log(`[ERROR] helper_iwdg_compute_param: ${e}`);
  }

  return param;
}


/**
 * This function suggest a new time based on the step between two possible
 * values
 * @param {float} step IWDG time step
 * @param {integer} input_time Time requested by the user
 * @returns {integer} Adjusted time
 */
function helper_iwdg_adjust_time(step, input_time) {
  let adjusted_time = 0;
  let remainder = 0;

  try {
    console.log(`[INFO] helper_iwdg_adjust_time, step=${JSON.stringify(step)}, input_time=${JSON.stringify(input_time)}`);

    remainder = input_time % step;
    console.log(`[INFO] helper_iwdg_adjust_time, remainder_step=${JSON.stringify(remainder)}`);
    if (input_time < step) {
      adjusted_time = 0;
    } else {
      adjusted_time = input_time - remainder;
      if (remainder > (step / 2)) {
        adjusted_time += step;
      }
    }
    console.log(`[INFO] helper_iwdg_adjust_time, adjusted_time=${JSON.stringify(adjusted_time)}`);

  } catch (e) {
    console.log(`[ERROR] helper_iwdg_adjust_time: ${e}`);
  }
  return Number(adjusted_time.toFixed(2));
}

module.exports = {
  helper_iwdg_stringify_unit,
  helper_iwdg_get_min_allowed_time,
  helper_iwdg_get_max_allowed_time,
  helper_iwdg_compute_prescaler,
  helper_iwdg_compute_step,
  helper_iwdg_compute_reload,
  helper_iwdg_compute_param,
  helper_iwdg_adjust_time
};
