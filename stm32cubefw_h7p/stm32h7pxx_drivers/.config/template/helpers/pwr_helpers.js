/**
 * @file Helpers functions used for PWR SW component
 * @author GPM Application Team
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
const global_api = {};  /* The list of global APIs */
const pvdin_level = {}; /* LEVEL corresponding to PVDIN signal */
const pwr_config = {}; /* Object containing the PWR resources that are enabled ()*/

const Wkup_LUT = {};

const LL_PWR_functionsV1 = {
  LL_PWR_SetRegulatorVoltageScaling: ["LL_PWR_REGU_VOLT_SCALE_1"],
  LL_PWR_SetStopRegulatorVoltageScaling: ["LL_PWR_REGU_STOP_VOLT_SCALE_HIGH"],
  LL_PWR_SetPVDLevel: ["LL_PWR_PVDLEVEL_1"],
  LL_PWR_SetAVDLevel: ["LL_PWR_AVDLEVEL_1"],
  LL_PWR_SetBattChargResistor: ["LL_PWR_BATT_CHARG_RESISTOR_5K"],
  LL_PWR_SetWakeUpPinPolarity: [["LL_PWR_WAKEUP_PIN_1", "LL_PWR_WAKEUP_PIN_2", "LL_PWR_WAKEUP_PIN_3", "LL_PWR_WAKEUP_PIN_4", "LL_PWR_WAKEUP_PIN_5", "LL_PWR_WAKEUP_PIN_6", "LL_PWR_WAKEUP_PIN_7", "LL_PWR_WAKEUP_PIN_8"], "LL_PWR_WAKEUP_PIN_POLARITY_HIGH"],
  LL_PWR_SetWakeUpPinPull: [["LL_PWR_WAKEUP_PIN_1", "LL_PWR_WAKEUP_PIN_2", "LL_PWR_WAKEUP_PIN_3", "LL_PWR_WAKEUP_PIN_4", "LL_PWR_WAKEUP_PIN_5", "LL_PWR_WAKEUP_PIN_6", "LL_PWR_WAKEUP_PIN_7", "LL_PWR_WAKEUP_PIN_8"], "LL_PWR_WAKEUP_PIN_PULL_NO"],
};

/* Private function ------------------------------------------------------------------------------------------------*/

/* Exported functions ----------------------------------------------------------------------------------------------*/
/**
 * Returns the LUT table used in LL code optimization common helpers.
 *
 * @param {String} ip_version - Version of IP must be 'V1".
 * @returns {Tab}
 */
function helper_pwr_get_lut_table(ip_version) {
  if (ip_version == 'V1'){
    return LL_PWR_functionsV1;
  }
  else{
    console.error(`[ERROR] helper_pwr_get_lut_table bad input`);
    return null;
  }
}

/**
 * Returns sring associated to wake up initialization.
 *
 * @param {String} serie - Current Serie must be 'C5', 'G5', 'H7P', 'V8', 'V9', 'C0', 'U0', 'U5'.
 * @returns {String} - Code to print in handlbars template
 */
function helper_pwr_get_ll_wkup_pin_codegen_init(serie)
{
  Wkup_LUT['C5'] = {conf:"pol_pull", reg:"WUCR",
      polref:"LL_PWR_WAKEUP_PIN_REF", pullref:"LL_PWR_WAKEUP_PIN_PULL_REF",
      pullshift:"LL_PWR_WAKEUP_PINS_PULL_SHIFT_OFFSET",
      polrefpos:"LL_PWR_WAKEUP_PIN_REF_POS", pullrefpos:"LL_PWR_WAKEUP_PIN_PULL_REF_POS"};

  Wkup_LUT['G5'] = {conf:"pol_pull", reg:"WUCR",
      polref:"LL_PWR_WAKEUP_PIN_REF", pullref:"LL_PWR_WAKEUP_PIN_PULL_REF",
      pullshift:"LL_PWR_WAKEUP_PINS_PULL_SHIFT_OFFSET",
      polrefpos:"LL_PWR_WAKEUP_PIN_REF_POS", pullrefpos:"LL_PWR_WAKEUP_PIN_PULL_REF_POS"};

  Wkup_LUT['H7P'] = {conf:"pol_pull", reg:"WKUPEPR",
      polref:"LL_PWR_WAKEUP_PIN_PP_REF", pullref:"LL_PWR_WAKEUP_PIN_PULL_REF",
      pullshift:"LL_PWR_WAKEUP_PINS_PULL_SHIFT_OFFSET",
      polrefpos:"LL_PWR_WAKEUP_PIN_PP_REF_POS", pullrefpos:"LL_PWR_WAKEUP_PIN_PULL_REF_POS"};

  Wkup_LUT['V8'] = {conf:"pol_pull", reg:"WKUPCR",
      polref:"LL_PWR_WAKEUP_PIN_POLARITY_REF", pullref:"LL_PWR_WAKEUP_PIN_PULL_REF",
      pullshift:"LL_PWR_WAKEUP_PINS_PULL_SHIFT_OFFSET",
      polrefpos:"LL_PWR_WAKEUP_PIN_POLARITY_REF_POS", pullrefpos:"LL_PWR_WAKEUP_PIN_PULL_REF_POS"};

  Wkup_LUT['V9'] = {conf:"pol_pull", reg:"WKUPCR",
      polref:"LL_PWR_WKUPP1_LOW_LEVEL", pullref:"LL_PWR_WAKEUP_PIN1_PULL_UP",
      pullshift:"LL_PWR_WAKEUP_PINS_PULL_SHIFT_OFFSET",
      polrefpos:"LL_PWR_WKUPEPR_WKUPP1_POS", pullrefpos:"LL_PWR_WKUPEPR_WKUPPUPD1_POS"};

  Wkup_LUT['C0'] = {conf:"pol"};

  Wkup_LUT['U0'] = {conf:"pol"};

  Wkup_LUT['U5'] = {conf:"pol_source"};


  let result = '';
  try {
    if (Wkup_LUT[serie].conf === "pol_pull") {
      result =  `  uint32_t temp_pin = 0;\r\n`;
      result += `  __IO uint32_t register_value;\r\n`;
      result += `  uint32_t position;\r\n`;
      result += `  uint32_t current_pin;`;
    }
    else if (Wkup_LUT[serie].conf === "pol_source") {
      result =  '  uint32_t tmp_pins_msk = 0;\r\n';
      result += '  uint32_t position;\r\n';
      result += '  uint32_t iocurrent;';
    }
    else if (Wkup_LUT[serie].conf === "pol")
    {
      result = '';
    }
    else
    {
      console.error(`[ERROR] helper_pwr_get_ll_wkup_pin_codegen_init Unknow serie: ${serie}`);
    }
    console.log(`[INFO] helper_pwr_get_ll_wkup_pin_codegen_init result : \r\n ${result}`);
  } catch (e) {
    console.error(`[ERROR] helper_pwr_get_ll_wkup_pin_codegen_init: ${e}`);
  }
  return result;
}

/**
 * Returns sring associated to wake up pin configuration mechanism when several wake pin has the same config.
 * this mechanism allows to write only one time in register.
 * @param {String} serie - Current Serie must be 'C5', 'G5', 'H7P', 'V8', 'V9', 'C0', 'U0', 'U5'.
 * @param {String} wakeuppin - List of wake up pin to configurate ( ex : 'LL_PWR_WAKEUP_PIN_1 | LL_PWR_WAKEUP_PIN_2')
 * @param {String} polarity - LL_PWR_WAKEUP_PIN_POLARITY_HIGH or LL_PWR_WAKEUP_PIN_POLARITY_LOW
 * @param {String} pull - LL_PWR_WAKEUP_PIN_PULL_NO or LL_PWR_WAKEUP_PIN_PULL_UP or LL_PWR_WAKEUP_PIN_PULL_DOWN
 * @param {String} source - LL_PWR_WAKEUP_PIN_SELECTION_X
 * @returns {String} - Code to print in handlbars template
 */
function helper_pwr_get_ll_wkup_pin_codegen_core(serie, wakeuppin, polarity, pull = null, source = null)
{
  let result = '';

  console.log(`[INFO] helper_pwr_get_ll_wkup_pin_codegen_core input serie : ${serie}`);
  console.log(`[INFO] helper_pwr_get_ll_wkup_pin_codegen_core input wakeuppin : ${wakeuppin}`);
  console.log(`[INFO] helper_pwr_get_ll_wkup_pin_codegen_core input polarity : ${polarity}`);
  console.log(`[INFO] helper_pwr_get_ll_wkup_pin_codegen_core input pull : ${pull}`);
  console.log(`[INFO] helper_pwr_get_ll_wkup_pin_codegen_core input source : ${source}`);

  try {
    if (Wkup_LUT[serie].conf === "pol_pull") {
      result =  `  /* Get wakeup pin information */\r\n`;
      result += `  register_value = LL_PWR_READ_REG(${Wkup_LUT[serie].reg});\r\n`;
      result += `  temp_pin = ${wakeuppin};\r\n`;
      result += `  position    = STM32_POSITION_VAL(temp_pin);\r\n`;
      result += `  current_pin = 1UL << position;\r\n`;
      result += `  while (temp_pin != 0U)\r\n`;
      result += `  {\r\n`;
      result += `    /* Mask values which will be modified */\r\n`;
      result += `    register_value &= ~(uint32_t)((${Wkup_LUT[serie].polref} << position) \\\r\n`;
      result += `                                  + (${Wkup_LUT[serie].pullref} << (position * ${Wkup_LUT[serie].pullshift})));\r\n`;
      result += '    /* Compute new value */\r\n';
      result += `    register_value |= (uint32_t)(((uint32_t)(${polarity}) << (${Wkup_LUT[serie].polrefpos} + position))\\\r\n`;
      result += `                                 + ((uint32_t)(${pull}) << (${Wkup_LUT[serie].pullrefpos} \\\r\n`;
      result += `                                 + (position * ${Wkup_LUT[serie].pullshift}))));\r\n`;
      result += `    /* Update wakeup pin information */\r\n`;
      result += `    temp_pin    &= (~current_pin);\r\n`;
      result += `    position    = STM32_POSITION_VAL(temp_pin);\r\n`;
      result += `    current_pin = 1UL << position;\r\n`;
      result += `  }\r\n`;
      result += `  /* Set new value in one register access */\r\n`;
      result += `  LL_PWR_WRITE_REG(${Wkup_LUT[serie].reg}, register_value);`;
    }
    else if (Wkup_LUT[serie].conf === "pol_source") {
      if ('LOW' in polarity) {
        result =  `  LL_PWR_SetWakeUpPinPolarityLow(${wakeuppin});`;
      }
      else{
        result =  `  LL_PWR_SetWakeUpPinPolarityHigh(${wakeuppin});`;
      }
      result += `  /* Get wakeup pin information */\r\n`;
      result += `  position = STM32_POSITION_VAL(tmp_pins_msk);\r\n`;
      result += `  iocurrent = 1UL << position;\r\n`;
      result += `\r\n`;
      result += `  while (tmp_pins_msk != 0U)\r\n`;
      result += `  {\r\n`;
      result += `    LL_PWR_SetWakeupPinSelection(iocurrent, (uint32_t)${source});\r\n`;
      result += `\r\n`;
      result += `    /* Update wakeup pin information */\r\n`;
      result += `    tmp_pins_msk &= (~iocurrent);\r\n`;
      result += `    position = STM32_POSITION_VAL(tmp_pins_msk);\r\n`;
      result += `    iocurrent = 1UL << position;\r\n`;
      result += `  }`;
    }
    else if (Wkup_LUT[serie].conf === "pol")
    {
      if ('LOW' in polarity) {
        result =  `  LL_PWR_SetWakeUpPinPolarityLow(${wakeuppin});`;
      }
      else{
        result =  `  LL_PWR_SetWakeUpPinPolarityHigh(${wakeuppin});`;
      }
    }
    else
    {
      console.error(`[ERROR] helper_pwr_get_ll_wkup_pin_codegen_core Unknow serie: ${serie}`);
    }
    console.log(`[INFO] helper_pwr_get_ll_wkup_pin_codegen_core result : \r\n ${result}`);
  } catch (e) {
    console.error(`[ERROR] helper_pwr_get_ll_wkup_pin_codegen_core: ${e}`);
  }
  return result;
}
/**
 * Globalize the application API, for them to be usable anywhere in helpers
 * @param {object} root is program root
 * @returns None
 */
function helper_pwr_globalize_API(root){
  global_api['SWConfigurationAPI'] = root.SWConfigurationAPI;
  global_api['peripheralsResourceManagerAPI'] = root.peripheralsResourceManagerAPI;
}

/**
 * Get the context of the selected component IP
 * @param {string} componentId is the identifier of the component as referenced by SW Config in its store,
 *                             or a meaningful subpart of the full componentId.
 *                             example: "STMicroelectronics::Device:STM32CubeMX2 Config:PWR"
 * @returns {object} context of the componentIP
 */
function helper_pwr_get_context(componentId){
  let context;
  try {
    const instance = global_api.SWConfigurationAPI.getInstances(componentId);
    const configuration = global_api.SWConfigurationAPI.getSwInstanceConfiguration(instance[0]);
    context = configuration;
    console.log(`[INFO] helper_pwr_get_context: context=${JSON.stringify(context)}`);
  } catch (error) {
    console.error(`[ERROR] helper_pwr_get_context: ${error}`);
    return null;
  }
  return context;
}

/**
 * Returns the string to be displayed in config panel
 *
 * @param {String} level - The Level being processed.
 * @param {String} description - Level description
 * @param {String} pvdin_signal - signal description
 * @param {String} value - const value of OneOf
 * @returns {String} String to be displayed
 */
function helper_pwr_get_level_string(level, description, pvdin_signal, value) {
  let levelString = '';

  try {
    console.log(`[INFO] helper_pwr_get_level_string: level=${JSON.stringify(level)}`);
    console.log(`[INFO] helper_pwr_get_level_string: description=${JSON.stringify(description)}`);
    console.log(`[INFO] helper_pwr_get_level_string: level_const=${JSON.stringify(value)}`);

    if (description === 'PVD_IN') {
      levelString = `${level} (External input voltage using ${pvdin_signal})`
      pvdin_level.level = value;
    } else {
      levelString = `${level} (${description})`
    }

    console.log(`[INFO] helper_pwr_get_level_string: output=${JSON.stringify(levelString)}`);

  } catch (e) {
    console.error('[ERROR] helper_pwr_get_level_string: ${e}');
  }
  return levelString;
}

/**
 * Returns if PVDIN GPIO must be configured or not
 *
 * @param {String} level - The Level title being processed.
 * @param {String} signal - signal name
 * @param {String} enable - PVD state
 * @returns {Boolean} true if the selected level contains the PVDIN signal name as description, false otherwise
 */
function helper_pwr_pvdin_conf_check(level, signal, enable) {
  let ret = false;

  try {
    console.log(`[INFO] helper_pwr_pvdin_conf_check: level=${JSON.stringify(level)}`);
    console.log(`[INFO] helper_pwr_pvdin_conf_check: enable=${JSON.stringify(enable)}`);
    console.log(`[INFO] helper_pwr_pvdin_conf_check: pvdin_level=${JSON.stringify(pvdin_level)}`);

    if ((level === pvdin_level.level) && (enable)) {
      ret = true;
    }
  } catch (e) {
    console.error('[ERROR] helper_pwr_get_level_string: ${e}');
  }
  return ret;
}

/**
 * Check if at least one EXTI is enabled.
 *
 * (*) : Those properties presence depends on the serie
 *
 * @param {Object} config - The JSON configuration object.
 * @returns {Boolean} 1 if at least one EXTI is available, 0 otherwise
 */
function helper_pwr_is_exti_configured(config) {
  let found = false;

  try {
    console.log(`[INFO] helper_pwr_is_exti_configured input : ${JSON.stringify(config)}`);

    function recurse(current) {
      if (typeof current === 'object' && current !== null) {
        // Check if both fields are present and true in the current object
        if (current.enableEXTI === true && current.enable === true) {
          found = true;
          return; // Early exit for efficiency
        }
        // Recurse into nested objects
        for (const key in current) {
          if (typeof current[key] === 'object' && current[key] !== null) {
            recurse(current[key]);
            if (found) return; // Early exit if already found
          }
        }
      }
    }

    recurse(config);
  } catch (e) {
    console.error('[ERROR] helper_pwr_is_exti_configured: ${e}');
  }

  return found;
}

/**
 * Check if at least one GPIO is enabled.
 *
 * (*) : Those properties presence depends on the serie
 *
 * @param {Object} statusPinConfig - The JSON configuration object for status pins.
 * @param {Object} pvdConfig - The PVD configuration.
 * @returns {Boolean} 1 if at least one GPIO is available, 0 otherwise
 */
function helper_pwr_is_gpio_configured(statusPinConfig, pvdConfig) {
  let found = false;

  try {
    console.log(`[INFO] helper_pwr_is_gpio_configured status pin input : ${JSON.stringify(statusPinConfig)}`);
    console.log(`[INFO] helper_pwr_is_gpio_configured PVD config input : ${JSON.stringify(pvdConfig)}`);

    /* Check Status pins */
    if (typeof statusPinConfig === 'object' && statusPinConfig !== null) {
      const trueBooleans = Object.values(statusPinConfig)
        .filter(value => typeof value === 'boolean' && value === true);

      if (trueBooleans.length > 0) {
        console.log(`[INFO] helper_pwr_is_gpio_configured status : FOUND status pins`);
        found = true;
      }
    }

    /* Check PVD_IN */
    if(typeof pvdConfig === 'object' && pvdConfig !== null) {
      if (pvdConfig.level_selection === 'LEVEL_8' && pvdConfig.level_selection !== null && pvdConfig.enable === true) {
        console.log(`[INFO] helper_pwr_is_gpio_configured status : FOUND PVD pin`);
        found = true;
      }
    }
  } catch (e) {
    console.error('[ERROR] helper_pwr_is_gpio_configured: ${e}');
  }

  return found;
}

/**
 * Processes the wakeup pin configurations from the given JSON configuration object
 * and returns an array of objects representing the wakeup pin settings.
 *
 * (*) : Those properties presence depends on the serie
 *
 * @param {Object} config - The JSON configuration object containing wakeup pin settings.
 * @param {String} layer - Generation layer chosen by the user
 * @param {Object} context - PWR peripheral parameters
 * @returns {Array} An array of objects, each representing the configuration of a wakeup pin.
 *                  Each object contains the following properties:
 *                  - pin: The name of the wakeup pin (e.g., "WAKEUP_PIN_1").
 *                  - enable: A boolean indicating whether the wakeup pin is enabled.
 *                  - polarity: A string representing the polarity of the wakeup pin ("HIGH" or "LOW").
 *                  - pull (*): A string representing the pull configuration of the wakeup pin ("NONE", "PULLUP", or "PULLDOWN").
 *                  - source (*): A string representing the source selection of the wakeup pin (e.g., "SOURCE_0").
 *                  - pinsnum : number of pin concanated in pin argument
 */
function helper_pwr_get_wakeup_settings(config, layer, context) {
  const configArray = Object.entries(config);
  let wakeupSettings = [], existingConfig = false, wkup_config, enable, pull, source, polarity;

  try {
    console.log(`[INFO] helper_pwr_get_wakeup_settings: config=${JSON.stringify(config)}`);
    console.log(`[INFO] helper_pwr_get_wakeup_settings: layer=${JSON.stringify(layer)}`);

    // Iterate over each wakeup pin configuration
    for (let i = 1; i <= 8; i++) {
      wkup_config = `Wk_${JSON.stringify(i)}_configuration`;
      if(configArray.find(setting => setting[0] == wkup_config)) {
        const pinConfig = (configArray.find(setting => setting[0] == wkup_config))[1];
        if (pinConfig && pinConfig && pinConfig.enable) {
          if(pinConfig.pull) {
            pull = pinConfig.pull;
          } else {
            source = pinConfig.source;
          };

          // Check if there is an existing configuration with the same settings
          if (wakeupSettings.length != 0)
          {
            existingConfig = pinConfig.pull
            ? wakeupSettings.find(setting =>
              setting.enable === pinConfig.enable &&
              setting.polarity === pinConfig.polarity &&
              setting.pull === pinConfig.pull
              )
            : wakeupSettings.find(setting =>
              setting.enable === pinConfig.enable &&
              setting.polarity === pinConfig.polarity &&
              setting.source === pinConfig.source
            );
          };

          if (existingConfig) {
            // Concatenate the pin name if the configuration is the same
            existingConfig.pins += ` | ${layer}_PWR_WAKEUP_PIN_${i}`;
            existingConfig.pinsnum += 1;
          } else {
            // Add a new configuration if it doesn't exist
            if (pinConfig.pull) {
              wakeupSettings.push({
                pins: `${layer}_PWR_WAKEUP_PIN_${i}`,
                enable: pinConfig.enable,
                polarity: pinConfig.polarity,
                pull: pinConfig.pull,
                pinsnum : 1
              });
            } else {
              wakeupSettings.push({
                pins: `${layer}_PWR_WAKEUP_PIN_${i}`,
                enable: pinConfig.enable,
                polarity: pinConfig.polarity,
                source: pinConfig.source,
                pinsnum : 1
              });
            }
          }
        }
      }
    }
  } catch (e) {
    console.error('[ERROR] helper_pwr_get_wakeup_settings: ${e}');
  }
  return wakeupSettings;
}

/**
 * Returns max number of wake up pin concanated (wake up pin with same config).
 * @param {array} wkupsettings (returned by helper_pwr_get_wakeup_settings)
 */
function helper_pwr_get_max_wakeup_settings_pin_num(wkupsettings) {
  let maxpinnum = 0;

  try {
    console.log(`[INFO] helper_pwr_get_max_wakeup_settings_pin_num input : ${wkupsettings}`);
    for (const setting of wkupsettings) {
      if (setting.pinsnum > maxpinnum)
      {
        maxpinnum = setting.pinsnum
      }
    }
  } catch (e) {
    console.error('[ERROR] helper_pwr_get_max_wakeup_settings_pin_num: ${e}');
  }
  console.log(`[INFO] helper_pwr_get_max_wakeup_settings_pin_num output : ${maxpinnum}`);
  return maxpinnum
}


/**
 * Concatenate pins to be able to generate them in 1 time
 * @param {string} new_pins Current pin to add in the global pins
 * @param {string} global_pins Global pins
 * @returns {string} Current added in the global pins.
*/
function helper_pwr_concatenate_pins(new_pins, global_pins) {
  let result = '';
  try {
    if (global_pins.length === 0) {
      result = new_pins;
    }
    else {
      result = global_pins + " | " + new_pins;
    }
    //console.log('[INFO] helper_concatenate_pins: result=${JSON.stringify(result)}');
  } catch (e) {
    console.error(`[ERROR] helper_concatenate_pins: ${e}`);
  }
  return result;
}

/**
 * Reorder wakeup pins order to enhance code clarity
 * @param {string} pins Current pins to reorder
 * @returns {string} Reordered pins.
 */
function helper_pwr_reorder_pins(pins) {
  let result = [];
  try {
    // Split the string by '|' and trim each pin
    result = pins.split('|').map(pin => pin.trim());

    // Sort the pins
    result.sort((a, b) => {
      // Extract the numeric part of the pin for comparison
      const numA = parseInt(a.replace(/\D/g, ''), 10);
      const numB = parseInt(b.replace(/\D/g, ''), 10);
      return numA - numB;
    });

    // Join the sorted pins back into a string
    result = result.join(' | ');
  } catch (e) {
    console.error(`[ERROR] helper_pwr_reorder_pins: ${e}`);
  }
  return result;
}

/**
 * Checks in peripheral.json that at least one wakeup pin is available to display the Wakeup pin configuration section
 * @param {Object} feat - Object containing all features
 * @returns {Boolean} 1 if at least one wakeup pin is available, 0 otherwise
 */
function helper_pwr_is_wakeup_available(feat) {
  let state = false;

  try {
    console.log(`[INFO] helper_pwr_is_wakeup_available: config=${JSON.stringify(feat)}`);

    // Iterate over each wakeup pin configuration
    for (let i = 0; i <= 16; i++) {
      const key = `wkup${i}`;
      if (feat[key] === true) {
        state = true;
      }
    }
  } catch (error) {
    console.error(`[ERROR] helper_pwr_is_wakeup_available: ${error}`);
    return null;
  }
  return state;
}

/**
 * Checks if the wakeupSettings array contains either 'pull' or 'source' properties.
 *
 * @param {Array} wakeupSettings - An array of wakeup settings objects.
 * @returns {number} - Returns 1 if 'pull' is found, 0 if 'source' is found, and -1 if neither is found.
 */
function helper_pwr_pull_or_source(wakeupSettings) {
  for (const setting of wakeupSettings) {
    if ('pull' in setting) {
      return 1;
    } else if ('source' in setting) {
      return 0;
    }
  }
  // Return -1 if neither 'pull' nor 'source' is found -> DBG purpose
  return -1;
}

/**
 * Checks if at least one RAM is configurable in the selected mode.
 *
 * @param {Object} feat - Object containing all features
 * @param {String} mode - String matching the mode to check
 * @returns {Boolean} - Returns true if at least one sram is configurable in this mode, otherwise returns false
 */
function helper_pwr_sram_mode_availability(feat, mode) {
  let state = false;
  try {
    console.log(`[INFO] helper_pwr_sram_mode_availability: feat=${JSON.stringify(feat)}`);
    console.log(`[INFO] helper_pwr_sram_mode_availability: mode=${JSON.stringify(mode)}`);

    // Iterate over each SRAM possible
    for (let i = 1; i <= 16; i++) {
      const key = `sram_${i}_${mode}`;
      const key_pages = `sram_${i}_pages_${mode}`
      if ((feat[key] === true) && (feat[key_pages] > 0)) {
        state = true;
        break; // Exit the loop early if a true value is found
      }
    }
  } catch (error) {
    console.error(`[ERROR] helper_pwr_sram_mode_availability: ${error}`);
    return null;
  }
  return state;
}

/**
 * Extract the SRAMs configuration settings for the selected mode.
 *
 * @param {Object} feat - Object containing all features
 * @param {String} mode - String matching the mode to check
 * @returns {Array} - Array containing the SRAM name and the number of pages
 */
function helper_pwr_sram_mode_get_info(feat, mode) {
  let settingsArray = [];
  try {
    console.log(`[INFO] helper_pwr_sram_mode_get_info: feat=${JSON.stringify(feat)}`);
    console.log(`[INFO] helper_pwr_sram_mode_get_info: mode=${JSON.stringify(mode)}`);

    // Iterate over each SRAM possible
    for (let i = 1; i <= 16; i++) {
      const key = `sram_${i}_${mode}`;
      const pagesKey = `sram_${i}_pages_${mode}`;

      // Check if the SRAM is configured in the specified mode
      if (feat[key] === true) {
        const sramName = `SRAM${i}`;
        const numberOfPages = feat[pagesKey] || 0; // Default to 0 if pages are not defined

        // Add the SRAM name and number of pages to the settings array
        settingsArray.push({ name: sramName, pages: numberOfPages });
      }
    }
    console.log(`[INFO] helper_pwr_sram_mode_get_info: output=${JSON.stringify(settingsArray)}`);
  } catch (error) {
    console.error(`[ERROR] helper_pwr_sram_mode_get_info: ${error}`);
    return null;
  }
  return settingsArray;
}

/**
 * Extract the SRAMs configuration settings for the selected mode.
 *
 * @param {Array} items - Array containing the pages number for this SRAM
 * @returns {Array} - Array containing the SRAM Page names
 */
function helper_pwr_srampages_info(numpages) {
  let settingsArray = [];
  try {
    console.log(`[INFO] helper_pwr_srampages_info: numpages=${JSON.stringify(numpages)}`);

    if (numpages.pages > 1)
    {
      // Iterate over each SRAM possible
      for (let i = 1; i <= numpages.pages; i++) {
        const sramPageName = `Page ${i}`;

        // Add the SRAM name and number of pages to the settings array
        settingsArray.push({ pagename: sramPageName, state: true});
      }
    } else {
      const sramPageName = `Full ${numpages.name} retention`;

      // Add the SRAM name and number of pages to the settings array
      settingsArray.push({ pagename: sramPageName, state: true});
    }

    console.log(`[INFO] helper_pwr_srampages_info: output=${JSON.stringify(settingsArray)}`);
  } catch (error) {
    console.error(`[ERROR] helper_pwr_srampages_info: ${error}`);
    return null;
  }
  return settingsArray;
}

/**
  * Get the binary status of voltage scaling ranges based on the targeted frequency.
  * @param {Object} feat - Object containing all features
  * @param {Number} frequency The MCU Core clock frequency
  * @returns {Array} An array of integers representing the available voltage scaling ranges.
  */
function helper_pwr_get_voltage_scaling(feat, frequency) {
  let frequencyRanges = [];

  try {
    console.log(`[INFO] helper_pwr_get_voltage_scaling: targeted_freq=${frequency}`);
    console.log(`[INFO] helper_pwr_get_voltage_scaling: feat=${JSON.stringify(feat)}`);


    // Iterate over each possible VOS
    for (let i = 0; i <= 8; i++) {
      let key = `vos${i}`;
      let minFreq = `vos${i}_min`;
      let maxFreq = `vos${i}_max`;

      if (minFreq in feat)
      {
        // Add the VOS name and min/max frequency to the settings array
        frequencyRanges.push({ voslevel: `VOLT_SCALE_${i}`, interval: {min: Number(feat[minFreq]), max: Number(feat[maxFreq])} , value: i});
      }

    }

    frequencyRanges = frequencyRanges
      .filter(({ interval }) => frequency >= interval.min && frequency <= interval.max);

    console.log(`[INFO] Available voltage scaling values for frequency ${frequency} Hz:`, frequencyRanges);

  } catch (error) {
    console.error(`[ERROR] helper_pwr_get_voltage_scaling: ${error}`);
    return null;
  }
  return frequencyRanges;
}

/**
  * Get the binary status of voltage scaling ranges based on the targeted frequency.
  * @param {Object} feat - Object containing all features
  * @param {String} vos The selected VOS to be checked
  * @param {Number} frequency The MCU Core clock frequency
  * @returns {Boolean} True if VOS is compatible false otherwise.
  */
function helper_pwr_is_voltage_scaling_compatible(feat, vos, frequency) {
  let compatibility = false;
  let vos_selection = helper_pwr_get_voltage_scaling(feat, frequency);

  console.log(`[INFO] helper_pwr_is_voltage_scaling_compatible: vos_selection=${JSON.stringify(vos_selection)}`);
  console.log(`[INFO] helper_pwr_is_voltage_scaling_compatible: vos=${JSON.stringify(vos)}`);

  try {
    // Check if vos_selection is a valid array and contains the specified VOS
    if (Array.isArray(vos_selection) && vos_selection.some(item => item.voslevel === vos))
    {
      compatibility = true;
    }

  } catch (error) {
    console.error(`[ERROR] helper_pwr_is_voltage_scaling_compatible: ${error}`);
    return null;
  }
  return compatibility;
}

/**
  * Get the first available VOS based on the targeted frequency.
  * @param {Object} feat - Object containing all features
  * @param {Number} frequency The MCU Core clock frequency
  * @returns {String} Applicable VOS
  */
function helper_pwr_get_first_voltage_scaling_compatible(feat, frequency) {
  console.log(`[INFO] helper_pwr_get_first_voltage_scaling_compatible: feat=${JSON.stringify(feat)}`);
  console.log(`[INFO] helper_pwr_get_first_voltage_scaling_compatible: targeted_freq=${frequency}`);
  let vos_selection = helper_pwr_get_voltage_scaling(feat, frequency);
  let applicable_vos = "";

  console.log(`[INFO] helper_pwr_get_first_voltage_scaling_compatible: vos_selection=${JSON.stringify(vos_selection)}`);

  try {
    // Check if vos_selection is a valid array and contains the specified VOS
    if (Array.isArray(vos_selection))
    {
      // Find the element with the lowest max frequency
        applicable_vos = (vos_selection.reduce((lowest, current) => {
        return current.interval.max < lowest.interval.max ? current : lowest;
      }, vos_selection[0])).voslevel;
    }

    console.log(`[INFO] helper_pwr_get_first_voltage_scaling_compatible: applicable_vos=${JSON.stringify(applicable_vos)}`);

  } catch (error) {
    console.error(`[ERROR] helper_pwr_get_first_voltage_scaling_compatible: ${error}`);
    return null;
  }
  return applicable_vos;
}

/**
 * Break the javascript execution
 * @note This function is for Debug purpose only - Can be called into the template to watch assigned variables.
You need to toggle a breakpoint for the code to break.
 * @param {Number} code A code to indicate where the function has been called (can be the line number)
 * @param {any} root
 */
function helper_pwr_breakpoint(code, root){
  let ret = code;
}

/**
 * Processes the SRAM retention configuration from the given JSON configuration object
 * and returns an array of objects representing the disabled SRAM pages grouped by consecutive ranges.
 *
 * @param {Object} config - The JSON configuration object containing SRAM retention settings.
 * @param {String} layer - Generation layer chosen by the user.
 * @returns {Array} An array of objects, each representing a disabled SRAM page range or full retention,
 *                  with the following properties:
 *                  - sram: The SRAM identifier (e.g., "SRAM1").
 *                  - mode: The mode name in uppercase (e.g., "RUN", "STOP", "STANDBY").
 *                  - fullretention: Boolean indicating if the SRAM has only one page (true if single page).
 *                  - page_idx: The starting page index of the disabled range (1-based).
 *                  - page_nbr: The number of consecutive disabled pages in the range.
 *                  - enabledPagesStr: String listing the enabled retention pages, formatted as ranges.
 *                  - pageDefinesStr: C expression string listing the disabled pages for the RAM (only for LL).
 */
function helper_pwr_sram_retention_config(config, layer) {
  const configArray = Object.entries(config);
  let ramSettings = [];

  try {
    console.log(`[INFO] helper_pwr_sram_retention_config: config=${JSON.stringify(config)}`);
    console.log(`[INFO] helper_pwr_sram_retention_config: layer=${JSON.stringify(layer)}`);

    // Check if the mode exists
    ['RunMode', 'StopMode', 'StandbyMode'].forEach(mode => {
      const modeshort = mode.replace('Mode', '');
      const modeEntry = configArray.find(setting => setting[0] === mode);

      if(modeEntry) {
        const sramArray = modeEntry[1];

        sramArray.forEach((sram, sramIndex) => {
          const pages = sram.Configuration;
          const nbpages = pages.length;
          const fullretention = (nbpages === 1);

          const disabledPages = [];
          const enabledPages = [];

          for (let i = 0; i < nbpages; i++) {
            if (!pages[i].enable) {
              // Check how many pages in SRAM are disabled
              disabledPages.push(i + 1);
            } else {
              // Check how many pages in SRAM are enabled
              enabledPages.push(i + 1);
            }
          }

          let enabledPagesStr = '';

          if (enabledPages.length > 0) {
            enabledPages.sort((a, b) => a - b);
            let ranges = [];
            let start = enabledPages[0], end = enabledPages[0];
            for (let j = 1; j < enabledPages.length; j++) {
              if (enabledPages[j] === end + 1) {
                end = enabledPages[j];
              } else {
                ranges.push(start === end ? `${start}` : `${start} to ${end}`);
                start = end = enabledPages[j];
              }
            }
            ranges.push(start === end ? `${start}` : `${start} to ${end}`);
            enabledPagesStr = ranges.join(', ');
          }

          let pageDefinesStr = '';
          let allDefines = [];

          if (disabledPages.length !== 0) {
            // At least one page retention is disabled
            if (fullretention) {
              // SRAM only has one page
              ramSettings.push({
                sram: `SRAM${sramIndex + 1}`,
                mode: `${modeshort.toUpperCase()}`,
                fullretention: true
              });
            } else {
              // SRAM has more than one page
              let start = disabledPages[0];
              let end = start;

              for (let idx = 1; idx < disabledPages.length; idx++) {
                const current = disabledPages[idx];
                if (current === end +1) {
                  // The disabled pages are consecutive
                  end = current;
                } else {
                  // Generate the list of disabled pages for this range
                  let disabledPageIndices = [];
                  let sramName = `SRAM${sramIndex + 1}`;
                  for (let i = start; i <= end; i++) {
                    disabledPageIndices.push(i);
                  }
                  let defines = disabledPageIndices.map(idx => `LL_PWR_${sramName}_PAGE${idx}_STOP_RETENTION`);
                  allDefines = allDefines.concat(defines);

                  // Push the previous range and start a new one
                  ramSettings.push({
                    sram: `SRAM${sramIndex + 1}`,
                    mode: `${modeshort.toUpperCase()}`,
                    fullretention: false,
                    page_idx: start,
                    page_nbr: end - start + 1,
                    enabledPagesStr
                  });

                  start = current;
                  end = current;
                }
              }

              // Generate the list of disabled pages for the last range
              let disabledPageIndices = [];
              let sramName = `SRAM${sramIndex + 1}`;
              for (let i = start; i <= end; i++) {
                disabledPageIndices.push(i);
              }
              let defines = disabledPageIndices.map(idx => `LL_PWR_${sramName}_PAGE${idx}_STOP_RETENTION`);
              allDefines = allDefines.concat(defines);

              pageDefinesStr = allDefines.join(' | ');

              // Push the last range
              ramSettings.push({
                sram: `SRAM${sramIndex + 1}`,
                mode: `${modeshort.toUpperCase()}`,
                fullretention: false,
                page_idx: start,
                page_nbr: end - start + 1,
                enabledPagesStr,
                pageDefinesStr
              });
            }
          }
        })
      }
    })
  } catch (e) {
    console.error(`[ERROR] helper_pwr_sram_retention_config: ${e}`);
  }

  let lastKey = '';
  ramSettings.forEach(item => {
    const key = `${item.sram}_${item.mode}`;
    item.isFirstOfGroup = (key !== lastKey);
    lastKey = key;
  });

  return ramSettings;
}

module.exports = {
  helper_pwr_get_lut_table,
  helper_pwr_get_ll_wkup_pin_codegen_init,
  helper_pwr_get_ll_wkup_pin_codegen_core,
  helper_pwr_globalize_API,
  helper_pwr_get_context,
  helper_pwr_get_level_string,
  helper_pwr_pvdin_conf_check,
  helper_pwr_is_exti_configured,
  helper_pwr_is_gpio_configured,
  helper_pwr_get_wakeup_settings,
  helper_pwr_get_max_wakeup_settings_pin_num,
  helper_pwr_concatenate_pins,
  helper_pwr_is_wakeup_available,
  helper_pwr_pull_or_source,
  helper_pwr_reorder_pins,
  helper_pwr_sram_mode_availability,
  helper_pwr_sram_mode_get_info,
  helper_pwr_srampages_info,
  helper_pwr_sram_retention_config,
  helper_pwr_get_voltage_scaling,
  helper_pwr_is_voltage_scaling_compatible,
  helper_pwr_get_first_voltage_scaling_compatible,
  helper_pwr_breakpoint
};