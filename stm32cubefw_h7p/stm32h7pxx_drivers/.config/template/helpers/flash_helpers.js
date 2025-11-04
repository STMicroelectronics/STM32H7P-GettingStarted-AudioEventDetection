/**
 * @file Helpers functions used for FLASH SW component
 * @author GPAM Application Team
 * @license
 * Copyright (c) 2025 STMicroelectronics.
 * All rights reserved.
 *
 * This software is licensed under terms that can be found in the LICENSE file
 * in the root directory of this software component.
 * If no LICENSE file comes with this software, it is provided AS-IS.
 */

/* Private constants -----------------------------------------------------------------------------------------------*/

/* Private variables -----------------------------------------------------------------------------------------------*/
const global_api = {};           /* The list of global APIs */
const flash_resource_state = {}; /* Object containing the resources that are enabled */

/* Private function ------------------------------------------------------------------------------------------------*/

/* Exported functions ----------------------------------------------------------------------------------------------*/

/**
 * Globalize the application API, for them to be usable anywhere in helpers
 * @param {object} root is program root
 * @returns None
 */
function helper_flash_globalize_API(root){
  global_api['SWConfigurationAPI'] = root.SWConfigurationAPI;
  global_api['peripheralsResourceManagerAPI'] = root.peripheralsResourceManagerAPI;
}

/**
 * Break the javascript execution
 * @note This function is for Debug purpose only - Can be called into the template to watch assigned variables.
You need to toggle a breakpoint for the code to break.
 * @param {Number} code A code to indicate where the function has been called (can be the line number)
 * @param {any} root
 */
function helper_breakpoint(code, root){
  let ret = code;
}

module.exports = {
  helper_flash_globalize_API,
  helper_breakpoint
};