/**
 * @file Common Helpers functions to provide service to the HAL components
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
 * Concatenate selections to be able to generate them in 1 time
 * @param {string} pins Global pins
 * @param {string} layer Current layer prefix keyword
 * @param {string} pin Current pin to add in the global pins
 * @returns {string} Current added in the global pins.
*/
function helper_sbs_concatenate_selections(pins, layer, pin) {
  let result = "";
  let current_pin = layer + pin;
  try {
    if (pins == "") {
      result = current_pin;
    }
    else {
      result = pins + " | " + current_pin;
    }
    //console.log(`[INFO] helper_concatenate_pins: result=${JSON.stringify(result)}`);
  } catch (e) {
    console.error(`[ERROR] helper_concatenate_pins: ${e}`);
  }
  return result;
}

/**
 * Check if the Object button is/are ticked(TRUE/ FALSE)
 * @param {string} obj Object button/s
 * @returns {boolean} Object button/s state.
*/
function helper_sbs_any_true(obj) {
  if (!obj || typeof obj !== 'object') {
    return false; // Return false if the object is invalid
  }

  for (const key in obj) {
    if (obj.hasOwnProperty(key) && obj[key] === true) {
      return true; // Return true if any property is true
    }
  }

  return false; // Return false if no property is true
}

module.exports = {
  helper_sbs_concatenate_selections,
  helper_sbs_any_true,
};
