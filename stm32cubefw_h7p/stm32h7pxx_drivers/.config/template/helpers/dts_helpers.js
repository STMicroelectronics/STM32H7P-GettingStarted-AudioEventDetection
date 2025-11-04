/**
  * @file Helpers functions used for DTS SW component
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
 * Renames the trigger if it matches a specific value.
 * @param {string} trigger - The original trigger name.
 * @returns {string} - The renamed trigger if it matches, otherwise the original trigger.
 */
function helper_dts_rename_trigger(trigger){
  let result = trigger.toUpperCase();
  try {
    if(result.startsWith("SW") || result === "") {
      result = "SOFTWARE";
    } else if (result.startsWith("TIM")) {
        result = result.replace("_CKTIM", "");
    } else if (result.startsWith("EXT")) {
      result = "EXTI" + result.match(/\[(\d+)\]/)[1];
    }
  } catch (e) {
    console.error(`[ERROR] helper_dts_rename_trigger: ${e}`);
  }
  return result;
}

module.exports = {
  helper_dts_rename_trigger
};
