/**
 * @file Common Helpers functions to provide service to the HAL components
 * @license
 * Copyright (c) 2025 STMicroelectronics.
 * All rights reserved.
 *
 * This software is licensed under terms that can be found in the LICENSE file
 * in the root directory of this software component.
 * If no LICENSE file comes with this software, it is provided AS-IS.
 */

/** @global */
let CFG_Index = {}; // Save the current index of the configuration
/* Variables used for LL code optimization */
let OptimEnabled = false; //  Save if the LL optimization has been enabled
let LUT_Table = []; // Save the current peripheral LUT table
let PPP_Instance = ""; // Save the current PPP instance
/**
 * Add string if present in lowercase
 * @param {string} str
 * @returns {string} format _str
 */
function addConfigLC(str) {
  if (str && typeof str === "string") {
    return str.toLowerCase().replace("-", "_");
  }
  return "";
}

function helper_stfcf_get_generated_function_name(
  pppi,
  layer,
  index,
  pppi_fct,
  from_where
) {
  try {
    console.log(
      `[INFO] helper_stfcf_get_generated_function_name (${pppi}, ${layer}, ${index}, ${pppi_fct}), from ` +
        from_where
    );
    return common_stfcf_get_generated_function_name(pppi, layer, index, pppi_fct);
  } catch (e) {
    console.log(`[ERROR] helper_stfcf_get_generated_function_name: ${e}`);
    return {};
  }
}

function common_stfcf_get_generated_function_name(pppi, layer, index, pppi_fct) {
  let index_str;
  let result = "";
  if (pppi && typeof pppi === "string" && layer && typeof layer === "string") {
    if (index === undefined) {
      index_str = "";
    } else {
      let new_index = index + 1;
      index_str = "cfg" + new_index;
    }
    result =
      "mx_" +
      pppi.toLowerCase() +
      addConfigLC(index_str) +
      "_" +
      layer.toLowerCase() +
      addConfigLC(pppi_fct);
    return result;
  }
  return result;
}

/**
 * Construct the name of the generated function
 * @param {string} pppi        PPPi instance (ex: 'CRC')
 * @param {string} layer       SW layer (ex: 'HAL')
 * @param {number} index       Index of current configuration (ex: 0)
 * @param {string} pppi_fct    Function used for the PPPi (optional)
 * @returns {string} Name of the config name (ex: "crc_cfg1_hal")
 */
function common_get_generated_function_name(pppi, layer, index, pppi_fct) {
  let index_str;
  let result = "";
  if (pppi && typeof pppi === "string" && layer && typeof layer === "string") {
    if (index === undefined) {
      index_str = "";
    } else {
      let new_index = index + 1;
      index_str = "cfg" + new_index;
    }
    result =
      "mx_" +
      pppi.toLowerCase() +
      addConfigLC(index_str) +
      "_" +
      layer.toLowerCase() +
      addConfigLC(pppi_fct);
    return result;
  }
  return result;
}

/**
 * Construct the aliases
 * @param {string} resource   HW instance (ex: 'CRC')
 * @param {number} instanceIndex index of SW instance (ex: 0)
 * @param {array} labels      array of labels for this SW instance (ex: ["CRC_SwInst0"])
 * @param {boolean} generated indicate if initialization should be generated (ex: true)
 * @param {object} config     current configuration (ex: {
  hal_crc_config_t: {
    DefaultPolynomialUse: false,
    DefaultInitValueUse: true,
    input_data_reverse_mode: "HAL_CRC_INDATA_REVERSE_NONE",
    CRC_Polynomial: {
      value: 16385,
      size: 16,
    },
    output_data_reverse_mode: true,
  },
  cfg_name: "my_cfg_crc",
})
 * @param {number} index      index of the current configuration (start at 0)
 * @param {object} save_hal_handle   Keep in memory the different HAL handles (ex {crc_instance0: true})
 * @returns {object} periph     {
  resource: "CRC",
  resource_inst: "crc_instance0",
  fct_name: "crc_cfg1_hal",
  fct_name_gethandle: "crc_hal",
  fct_name_aliases: [
    "crc_swinst0_my_cfg_crc",
  ],
  labels: [
    "CRC_SwInst0",
  ],
  cfg_name: "my_cfg_crc",
  layer: "HAL",
  generated: true,
  default: false,
}
 */
function common_get_periph_labels(
  resource,
  instanceIndex,
  labels,
  generated,
  config,
  index,
  fct_type,
  layer,
  save_hal_handle
) {
  let fct_name;
  let fct_name_aliases = [];
  let cfg_name = config["cfg_name"];
  if (typeof resource !== "string") {
    console.log("[ERROR] resource is not a string");
    return {};
  }
  let resource_inst = resource + "_" + instanceIndex;
  /* fct name should have the format pppi_cfgx */
  fct_name = common_get_generated_function_name(
    resource,
    layer,
    index,
    fct_type
  );
  /* provide the handle only it does not exist */
  if (!save_hal_handle.hasOwnProperty(resource_inst)) {
    fct_name_gethandle = common_get_generated_function_name(
      resource,
      layer,
      undefined,
      fct_type
    );
    save_hal_handle[resource_inst] = true;
  } else {
    fct_name_gethandle = "";
  }
  labels.forEach((label) => {
    let fct_name_alias;
    fct_name_alias =
      label.toLowerCase().replace("-", "_").replace(" ", "_") +
      addConfigLC(cfg_name);
    fct_name_aliases.push(fct_name_alias);
    fct_name_alias = label.toLowerCase().replace("-", "_").replace(" ", "_");
  });
  let periph = {
    resource: resource,
    resource_inst: resource_inst,
    fct_name: fct_name,
    fct_name_gethandle: fct_name_gethandle,
    fct_name_aliases: fct_name_aliases,
    labels: labels,
    cfg_name: cfg_name,
    layer: layer,
    generated: generated,
    default: false,
  };
  return periph;
}

/**
 * Initialize the global index used for the function name definition inside mx_ppp.c/h
 */
function helper_common_initialize_index() {
  CFG_Index = {};
}

/**
 * Get the index to be used for function name construction
 * @param {string} resource HW resource used in PPP component
 * @returns {{integer}} 0 if 1st call of the function inside mx_ppp_template.c/h.hbs or index linked to the resource
 */
function helper_common_get_index(resource) {
  if (!CFG_Index.hasOwnProperty(resource)) {
    CFG_Index[resource] = 0;
  }

  return CFG_Index[resource];
}

/**
 * Increment the current index for the HW resource and return it to the template
 * @param {string} resource HW resource used in PPP component
 * @returns {{integer}} new index to be applied for the function name construction used for cfg
 */
function helper_common_inc_index(resource) {
  CFG_Index[resource] = CFG_Index[resource] + 1;
  return CFG_Index[resource];
}

/**
 * Construct the name of the generated function
 * @note Function called in every stm32_ppp_template.c/h.hbs
 * @param {string} pppi        PPPi instance
 * @param {string} layer       SW layer
 * @param {number} index       Index of current configuration
 * @param {string} pppi_fct    Function used for the PPPi (optional)
 * @param {string} from_where    Function used for the PPPi (optional)
 * @returns
 */
function helper_common_get_generated_function_name(
  pppi,
  layer,
  index,
  pppi_fct,
  from_where
) {
  try {
    console.log(
      `[INFO] helper_common_get_generated_function_name (${pppi}, ${layer}, ${index}, ${pppi_fct}), from ` +
        from_where
    );
    return common_get_generated_function_name(pppi, layer, index, pppi_fct);
  } catch (e) {
    console.log(`[ERROR] helper_common_get_generated_function_name: ${e}`);
    return {};
  }
}

/**
 * Return if hal define has been enabled for the module to hal_conf.h
 * @note  use to check for USE_HAL_PPP_REGISTER_CALLBACKS, USE_HAL_PPP_USER_DATA, USE_HAL_PPP_GET_LAST_ERRORS, USE_HAL_PPP_DMA
 * @param {*} Settings settings of system parameters
 * @param {*} Module module to check
 * @returns Output='' => 1 or 0
 */
function helper_common_if_value_is_enabled(Settings, Module) {
  let result = 0;
  //console.log(`[INFO] helper_common_get_user_data`);
  try {
    for (let resource in Settings) {
      component = resource.split("_")[0];
      if (component === Module.toLowerCase()) {
        if (Settings[resource]) {
          result = 1;
          break;
        }
      }
    }
  } catch (e) {
    console.error(`[ERROR] helper_common_get_user_data: ${e}`);
  }
  return result;
}

/**
 * Return if SW component has been enabled in the project (or at least its dependancies)
 * @note  use hal_conf.h for USE_HAL_PPP_MODULE
 * @param {object} used_components used components returned by SWProjectAPI.getUsedComponents getter
 * @param {string} component component to be check
 */
function helper_common_if_component_is_enabled(used_components, component) {
  let result = 0;
  //console.log(`[INFO] helper_common_if_component_is_enabled`);
  try {
    used_components.forEach((comp) => {
      if (
        (comp["cgroup"] === "STM32 HAL" ||
          comp["cgroup"] === "STM32 HAL DRIVERS CORE") &&
        comp["csub"].toUpperCase() === component.toUpperCase()
      ) {
        result = 1;
        return;
      }
    });
  } catch (e) {
    console.error(`[ERROR] helper_common_if_component_is_enabled: ${e}`);
  }
  return result;
}

/**
 * Check if RCC clock must be enabled inside the mx_pppi_init function
 * @param {object} clock_activation used components returned by SWProjectAPI.getUsedComponents getter
 * @param {string} component component to be check
 * @returns clock activation value:
 *          @arg 0  HAL_CLK_ENABLE_NO                 No clock activation in PPP
 *          @arg 1  HAL_CLK_ENABLE_PERIPH_ONLY        PERIPH Clock activation only
 *          @arg 2  HAL_CLK_ENABLE_PERIPH_PWR_SYSTEM  PERIPH Clock activation including PWR and/or system
 */
function helper_common_if_rcc_clock_activated(clock_activation, component) {
  let result = 0;
  console.log(
    `[INFO] helper_common_if_rcc_clock_activated: component=${component})} `
  );
  try {
    const clock_key = component.toLowerCase() + "_feature";
    if (Object.hasOwnProperty.call(clock_activation, clock_key)) {
      current_config = clock_activation[clock_key];
      if (current_config["clk_enable_model"] === "HAL_CLK_ENABLE_NO") {
        result = 0;
      } else if (
        current_config["clk_enable_model"] === "HAL_CLK_ENABLE_PERIPH_ONLY"
      ) {
        result = 1;
      } else {
        /* HAL_CLK_ENABLE_PERIPH_PWR_SYSTEM */
        result = 2;
      }
    }
  } catch (e) {
    console.error(`[ERROR] helper_common_if_rcc_clock_activated: ${e}`);
  }
  return result;
}

/**
   * Prepare an object will be used by stm32_system_template.c.hbs & stm32_hal_def_template.h.hbs templates
   * @note  Function called inside stm32_system_template.c.hbs & stm32_hal_def_template.h.hbs
   * @param {object} instance SW instance of the current component (list of the configs of the SW instance)
   * @param {string} current_component name of the code gen component (ex UART Init)
   * @param {string} current_name name of the SW instance
   * @param {object} current_ctxt use to provide the context all the SW instance already analysed (set to 'undefined' if no SW instance analysed yet)
   * @returns {object}
    {
        "component": [
            "CRC",
            "GPIO",
            "UART",
            "USART",
            "CORE"
        ],
        "periphs": [
            {
                "resource": "CRC",
                "resource_inst": "crc_instance0",
                "fct_name": "stm32_crc_cfg1_hal",
                "fct_name_gethandle": "stm32_crc_hal",
                "fct_name_aliases": [
                    "crc"
                ],
                "labels": [
                    "CRC"
                ],
                "layer": "HAL",
                "generated": true,
                "default": true,
                "component": "CRC"
            },
            {
                "resource": "USART1",
                "resource_inst": "usart1_instance2",
                "fct_name": "stm32_usart1_cfg1_hal_usart",
                "fct_name_gethandle": "stm32_usart1_hal_usart",
                "fct_name_aliases": [
                    "multi_sync_hal_one_test_one",
                    "multi_sync_hal_two_test_one"
                ],
                "labels": [
                    "multi_sync_hal_one",
                    "multi_sync_hal_two"
                ],
                "cfg_name": "test_one",
                "layer": "HAL",
                "generated": true,
                "default": true,
                "component": "UART"
            }(...)
        ],
        "cfg_index": {
            "CRC_CRC": 1,
            "GPIO_gpio_default": 1,
            "UART_USART1": 7,
            "USART_USART1": 3
        },
        "save_hal_handle": {
            "crc_instance0": true,
            "gpio_default_instance1": true,
            "usart1_instance2": true,
            "usart1_instance3": true,
            "usart1_instance4": true,
            "usart1_instance5": true
        },
        "instanceIndex": 7,
        "CRC": true,
        "gpio_default": true,
        "USART1": true
    }
   */
function helper_common_get_sw_config_context(
  instance,
  current_component,
  current_name,
  current_ctxt
) {
  let result = {
    component: [],
    periphs: [],
    cfg_index: {},
    save_hal_handle: {},
    instanceIndex: 0,
  };
  try {
    let cfg_index = {};
    let save_hal_handle = {};
    console.log(`[INFO] helper_common_get_sw_config_context`);
    //console.log(`[INFO]         instance=${JSON.stringify(instance)}`);
    //console.log(`[INFO]         id_sw_instance=${id_sw_instance}`);
    //console.log(`[INFO]         current_ctxt=${JSON.stringify(current_ctxt)}`);
    console.log(`[INFO]         current_name=${current_name}`);
    if (current_ctxt !== "undefined") {
      result = current_ctxt;
    }
    cfg_index = result["cfg_index"];
    save_hal_handle = result["save_hal_handle"];
    current_component = current_component.split(" ");
    current_component = current_component[0];
    console.log(`[INFO]         current_component=${current_component}`);
    if (result["component"].indexOf(current_component) === -1) {
      result["component"].push(current_component);
    }
    let labels = [];
    if (
      instance.blocks !== undefined &&
      instance.blocks.info !== undefined &&
      instance.resources !== undefined &&
      Object.keys(instance.resources).length !== 0
    ) {
      let resourcesObj = instance.resources;
      let resource;
      if (current_component === "GPIO")
        resource = resourcesObj[Object.keys(resourcesObj)[0]]["label"];
      else resource = resourcesObj[Object.keys(resourcesObj)[0]]["id"];

      /* save the list of labels used for this SW instance */
      if (current_name !== undefined) {
        labels.push(current_name);
      }
      if (
        instance.blocks.info.labels !== undefined &&
        instance.blocks.info.labels.length != 0
      ) {
        instance.blocks.info.labels.forEach((label) => {
          labels.push(label.toLowerCase().replace("-", "_"));
        });
      }
      // index of the config depends on the current HW resource and current component
      let resource_component = current_component + "_" + resource;
      if (!cfg_index.hasOwnProperty(resource_component)) {
        cfg_index[resource_component] = 0;
      }
      /* Save function if exist */
      let fct_type = undefined;
      if (instance.blocks.info.function_type !== undefined) {
        fct_type = instance.blocks.info.function_type;
      }
      /* Save function if exist */
      let layer = undefined;
      if (instance.blocks.info.layer !== undefined) {
        layer = instance.blocks.info.layer;
      }
      let generated = false;
      let default_to_be_called = false;
      if (instance.blocks.info.init_type != "disabled") {
        generated = true;
        if (instance.blocks.info.init_type === "called") {
          default_to_be_called = true;
        }
      }
      if (instance.blocks.configs !== undefined) {
        /* Loop on the different config for this SW instance */
        if (instance.blocks.configs.length > 1)
          console.log(
            `[INFO] several configs in ${resource} (${resource_component})`
          );
        instance.blocks.configs.forEach((config) => {
          let periph = common_get_periph_labels(
            resource,
            current_name,
            labels,
            generated,
            config,
            cfg_index[resource_component],
            fct_type,
            layer,
            save_hal_handle
          );
          periph["component"] = current_component;
          cfg_index[resource_component] = cfg_index[resource_component] + 1;
          if (!result.hasOwnProperty(resource)) {
            result[resource] = false;
          }
          if (default_to_be_called && !result[resource]) {
            periph["default"] = true;
            result[resource] = true;
          }
          /* ICACHE should be initialized 1st inside the peripheral_init function */
          if (periph["resource"] == "ICACHE") {
            /* save the interruption configuration */
            periph["interruption"] = config.System.EnableInterruption;
            result["periphs"].unshift(periph);
          } else {
            result["periphs"].push(periph);
          }
        });
      } else {
        /* There are no config set by user - should not happen*/
        console.log(
          `[WARNING] helper_common_get_sw_config_context: no configs block`
        );
      }
    } else {
      /* There are no blocks information */
      console.log(
        `[WARNING] helper_common_get_sw_config_context: no blocks or info block`
      );
    }
  } catch (e) {
    console.log(`[ERROR] helper_common_get_sw_config_context ${e}`);
  }
  console.log(`[INFO]         result      =${JSON.stringify(result)}`);
  return result;
}

/**
 * Concatenate needs to be able to generate them in 1 time
 * @param {object} current_needs Current needs to add in the global needs
 * @param {object} global_needs Global needs
 * @returns {object} Current added in the global needs.
 */
function helper_common_concatenate_needs(current_needs, global_needs) {
  let result = [];
  try {
    console.log(`[INFO] helper_common_concatenate_needs`);
    console.log(
      `[INFO] helper_common_concatenate_needs: current_needs=${JSON.stringify(
        current_needs
      )}, global_needs=${JSON.stringify(global_needs)}`
    );
    if (global_needs !== "undefined") {
      result = global_needs;
    }
    current_needs.forEach((need) => {
      result.push(need);
    });
    //console.log(`[INFO] helper_common_concatenate_needs: result=${JSON.stringify(result)}`);
  } catch (e) {
    console.error(`[ERROR] helper_common_concatenate_needs: ${e}`);
  }
  return result;
}

/**
 * Add an element inside an array
 * @param {object} current_elt Current element to add in the array
 * @param {object} global_elt Current array ('undefined' by default)
 * @returns {Array} list of elements inside an array
 */
function helper_common_concatenate_elt_in_array(current_elt, global_elt) {
  let result = [];
  try {
    if (global_elt !== "undefined") {
      result = global_elt;
    }
    result.push(current_elt);
    /*console.log(
      `[INFO] helper_common_concatenate_elt_in_array: result=${JSON.stringify(
        result
      )}`
    );*/
  } catch (e) {
    console.error(`[ERROR] helper_common_concatenate_elt_in_array: ${e}`);
  }
  return result;
}

/**
 * Find inside an array if the value is well set to the associated key
 * @param {array} array array provided as input
 * @param {string} key element to be found inside the array
 * @param {string} value value expected in the key
 * @returns {object} contain the object containing the targeted value.
 */
function helper_common_get_object_by_key(array, key, value) {
  try {
    console.log(
      `[INFO] helper_common_get_object_by_key: array=${JSON.stringify(
        array
      )}, key=${key}, value=${value}`
    );
    return array?.find(function (objet) {
      return objet[key] === value;
    });
  } catch (e) {
    console.error(`[ERROR] helper_common_get_object_by_key: ${e}`);
    return undefined;
  }
}

/**
 * Function to be called to prepare the LL code optimization
 * @param {boolean} optim_enabled User configuration to enable or not the LL optimzation
 * @param {object} lut_table LUT table used for the LL code optimizatoin
 * @param {string} ppp_instance HW instance of I2C (ex I2C1), 'undefined' is not necessary
 * @returns
 */
function helper_common_initialize_ll_code(
  optim_enabled,
  lut_table,
  ppp_instance
) {
  try {
    /*console.log(
      `[INFO] helper_common_initialize_ll_code: optim_enabled=${optim_enabled}, lut_table=${JSON.stringify(
        lut_table
      )}, ppp_instance=${ppp_instance}`
    );*/
    /* Save the different parameters used for the LL code optimization */
    OptimEnabled = optim_enabled;
    LUT_Table = lut_table;
    PPP_Instance = ppp_instance;
  } catch (e) {
    console.log(`[ERROR] helper_common_initialize_ll_code: ${e}`);
  }
  return;
}

/**
 * Construct the LL code to be generated with or without comments depends if the LL functions
 * @detail  A LUT is provided as input of this function and when optimization is requested
 *          a check on this LUT is done.
 *          On the fly, the C code is constructed with the inputs and commented if this line is
 *          detected as function why does not have impact on the peripheral
 * @param {string} ppp_function Function to be checked if it can be commented or not
 * @param {...any} arguments Dynamic of the arguments of the function (can be empty)
 * @returns {string} Code to be generated in LL function (with or without comments)
 */
function helper_common_generate_ll_code(ppp_function) {
  try {
    /*console.log(
      `[INFO] helper_common_generate_ll_code: OptimEnabled=${OptimEnabled}, LUT_Table=${JSON.stringify(
        LUT_Table
      )}, PPP_Instance=${PPP_Instance}, ppp_function=${ppp_function}`
    );*/
    /* exclude options + 1st argument */
    var args = Array.prototype.slice.call(arguments, 1, -1);
    var prefix_comment;
    var suffix_comment;

    code = ppp_function + "(";
    if (PPP_Instance !== "undefined") {
      code = code + PPP_Instance;
    }
    if (OptimEnabled) {
      prefix_comment = "/* ";
      suffix_comment = " */";
      if (LUT_Table === undefined || !LUT_Table.hasOwnProperty(ppp_function)) {
        /* optimization not requested */
        console.log(
          `[INFO] helper_common_generate_ll_code: Optimization not requested`
        );
        prefix_comment = "";
        suffix_comment = "";
        if (args) {
          args.forEach((arg) => {
            code = code + ", " + arg;
          });
        }
        return prefix_comment + code + ");" + suffix_comment;
      }
      if (args) {
        current_function = LUT_Table[ppp_function];
        args.forEach((arg, index) => {
          code = code + ", " + arg;
          /* Several defines possible for the reset value
            - list of reset values is in array*/
          if (
            (Array.isArray(current_function[index]) &&
              !current_function[index].includes(arg)) ||
            (!Array.isArray(current_function[index]) &&
              current_function[index] !== arg)
          ) {
            /* one of the argument is not identical */
            prefix_comment = "";
            suffix_comment = "";
          }
        });
      }
    } else {
      /* optimization not requested */
      prefix_comment = "";
      suffix_comment = "";
      if (args) {
        args.forEach((arg) => {
          code = code + ", " + arg;
        });
      }
    }
    return prefix_comment + code + ");" + suffix_comment;
  } catch (e) {
    console.log(`[ERROR] helper_common_generate_ll_code: ${e}`);
  }
}

function concat() {
  var args = Array.prototype.slice.call(arguments, 0, -1); // Exclure l'argument options
  return args.join("");
}

module.exports = {
  helper_common_initialize_index,

  helper_common_get_index,

  helper_common_inc_index,

  helper_common_get_generated_function_name,

  helper_stfcf_get_generated_function_name,

  helper_common_if_value_is_enabled,

  helper_common_if_component_is_enabled,

  helper_common_if_rcc_clock_activated,

  helper_common_get_sw_config_context,

  helper_common_concatenate_needs,

  helper_common_concatenate_elt_in_array,

  helper_common_get_object_by_key,

  helper_common_initialize_ll_code,

  helper_common_generate_ll_code,

  concat,
};
