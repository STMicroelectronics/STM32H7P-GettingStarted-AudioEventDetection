/**
  * @file Common Helpers functions to provide service to the HAL components
  * @author GPM Application Team
  * @license
  * @attention
  *
  * Copyright (c) 2024-2025 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  */

/** @global */
let CFG_Index = {}; // Save the current index of the configuration
/* Variables used for LL code optimization */
let OptimEnabled = false; //  Save if the LL optimization has been enabled
let LUT_Table = []; // Save the current peripheral LUT table
let PPP_Instance = undefined; // Save the current PPP instance
let Sub_Instances = undefined; // Save the current Sub instances

/*
  Variable to list all the SW compoents not based on
  Handle (return system_status_t)
  */
const ComponentWithNoHandle = ["gpio_default", "GPIO", "HSEM", "PWR", "RTC", "TAMP", "CORTEX_MPU", "CORTEX_NVIC", "CORTEX_SCB", "CORTEX_SYSTICK", "RCC", "SBS", "SYSCFG", "XSPIM", "FMC"];

/**
 * Add string if present in lowercase
 * @param {string} str
 * @returns {string} format _str
 */
function addConfigLC(str) {
  if (str && typeof str === "string") {
    return "_" + str.toLowerCase().replace("-", "_");
  }
  return "";
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
  // let index_str;
  let result = "";
  if (pppi && typeof pppi === "string" && layer && typeof layer === "string") {

    /* Remove index for the moment because of multi-config removal.
       Will be usefull for DV2.1 with multi MCU state. */
    // if (index === undefined) {
    //   index_str = "";
    // } else {
    //   let new_index = index + 1;
    //   index_str = "cfg" + new_index;
    // }
    result =
      "mx_" +
      pppi.toLowerCase() +
      // addConfigLC(index_str) +
      // "_" +
      // layer.toLowerCase() +
      addConfigLC(pppi_fct);
    return result;
  }
  return result;
}

/**
 * Construct the aliases
 * @param {string} resource   HW instance (ex: 'CRC')
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
  let resource_inst = resource;
  /* fct name should have the format pppi_cfgx */
  fct_name = common_get_generated_function_name(
    resource,
    layer,
    index,
    fct_type
  );
  /* provide the handle only it does not exist */
  if ((!save_hal_handle.hasOwnProperty(resource_inst)) && !(ComponentWithNoHandle.includes(resource))) {
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
 * Function to generate the LL code
 * @param {string} ppp_function Function to be checked if it can be commented or not
 * @param {...any} arguments Dynamic of the arguments of the function (can be empty)
 * @returns {string} LL code commented if optimization is enabled and function included in LUT table
 */
function common_gen_ll_code(ppp_function, ...args) {
  try {
    var prefix_comment;
    var suffix_comment;

    /* Add 1st comma after PPP_Instance or Sub-instances*/
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
            /** if ppp_instance or subinstance has been added, need to add a comma */
            if (code.endsWith('(') == false) {
              code = code + ", ";
            }
            code = code + arg;
          });
        }
        return prefix_comment + code + ");" + suffix_comment;
      }
      if (args) {
        current_function = LUT_Table[ppp_function];
        args.forEach((arg, index) => {
          /** if ppp_instance or subinstance has been added, need to add a comma */
          if (code.endsWith('(') == false) {
            code = code + ", ";
          }
          code = code + arg;
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
          /** if ppp_instance or subinstance has been added, need to add a comma */
          if (code.endsWith('(') == false) {
            code = code + ", ";
          }
          code = code + arg;
        });
      }
    }
    return prefix_comment + code + ");" + suffix_comment;
  } catch (e) {
    console.log(`[ERROR] common_gen_ll_code: ${e}`);
  }
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
    //console.log(
    //  `[INFO] helper_common_get_generated_function_name (${pppi}, ${layer}, ${index}, ${pppi_fct}), from ` +
    //    from_where
    //);
    return common_get_generated_function_name(pppi, layer, index, pppi_fct);
  } catch (e) {
    console.log(`[ERROR] helper_common_get_generated_function_name: ${e}`);
    return {};
  }
}

/**
 * Construct an object describing all the generated function calls
 * @param {object} list_functions        Object returned by $get('sw-config.instances',$modelId)
 * example
 *
 [
    {
        "instanceId": "b36b9ddb-d0c3-4bd6-897e-78a2dfe524f1",
        "instanceName": "MyCORE_1",
        "componentId": "STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-alpha.8.0$STMicroelectronics::Device:STM32 MX Config:CORE@0.1.6#HAL Generated code",
        "validationStatus": {
            "severity": "ok"
        }
    },
    {
        "instanceId": "8ae87def-5810-4e10-bcac-3587e23a9ea8",
        "instanceName": "MyICACHE_bis",
        "componentId": "STMicroelectronics.stm32u5xx_hal_drivers.2.0.0-alpha.8.0$STMicroelectronics::Device:STM32 MX Config:ICACHE@0.5.0#HAL CORE Init and ICACHE",
        "validationStatus": {
            "severity": "ok"
        }
    }
 ]
 * @returns {object} structure describing the function names
 * example
 *
 */
function helper_common_get_generated_function_calls(sw_config_object) {
  try {
    console.log(
      `[INFO] helper_common_get_generated_function_calls: ${JSON.stringify(
        sw_config_object
      )}`
    );

    let list_functions = [];

    /*
      Retrieve only the components linked to HAL configurable components which can be ranking:
        - System, RCC, ICACHE cannot be ranked
     */
    const excludedTags = ["STM32CubeMX2 Config:System", "STM32CubeMX2 Config:RCC", "STM32CubeMX2 Config:ICACHE", "STM32CubeMX2 Config:CORE", "STM32CubeMX2 Config:CORTEX MPU"];

    list_functions = sw_config_object
      .filter((ins) => ins.componentId.includes(":STM32CubeMX2 Config:"))
      .filter(
        (item) => !excludedTags.some((tag) => item.componentId.includes(tag))
      );
    /* From the previous list, convert it to the peripheral initialization function:
     - name (format: mx_<label>_init)
     - retrieve the SW component thanks a regular expression which to retrieve the Csub block between STM32CubeMX2 Config: and @
     */
    list_functions = list_functions.map((ins) => ({
      name: `mx_${ins.instanceName.toLowerCase()}_init`, sw_instance: ins.componentId.match(/STM32CubeMX2 Config:(.*?)@/)[1]
    }));

    console.log(
      `[INFO] helper_common_get_generated_function_calls: list_functions ${JSON.stringify(
        list_functions
      )}`
    );

    return list_functions;
  } catch (e) {
    console.log(`[ERROR] helper_common_get_generated_function_calls: ${e}`);
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
        (comp["cgroup"] === "STM32 HAL" || comp["cgroup"] === "STM32 LL" ||
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
 * Get the PPP clock mode defined in CORE
 * @param {string} hw_resource hw_resource to be checked
 * @returns clock mode value:
 *          @arg 0  HAL_CLK_ENABLE_NO                 No clock activation in PPP
 *          @arg 1  HAL_CLK_ENABLE_PERIPH_ONLY        PERIPH Clock activation only
 *          @arg 2  HAL_CLK_ENABLE_PERIPH_PWR_SYSTEM  PERIPH Clock activation including PWR and/or system
 */
function helper_common_get_clk_enable_mode(root, hw_resource) {
  let result = 0;
  console.log(
    `[INFO] helper_common_get_clk_enable_mode: hw_resource=${hw_resource})} `
  );
 try {
    /* Get CORE information settings */
    const json = '{"cgroup": "STM32CubeMX2 Config", "csub": "CORE"}';
    const json_obj =JSON.parse(json);
    const core_configuration = root.SWConfigurationAPI.getInstancesConfiguration(json_obj);
    const core_info = core_configuration[0].settings.parameters.info;

    /* Get component key */
    /* Component is the hw_resource without terminating index except for PPP including several functions (e.g: USART1 can be UART) */
    let component = hw_resource.replace(/\d+$/, '');  /* Remove numbers at the end of string */
    const sw_instance = root.peripheralsResourceManagerAPI.getSoftwareInstancesBoundToPeripheral(hw_resource);
    const sw_config = root.SWConfigurationAPI.getSwInstanceConfiguration(sw_instance[0]);
    if (sw_config.info.function_type) {
      component = sw_config.info.function_type;
    }
    const component_key = component.toLowerCase() + "_feature";

    if (Object.hasOwnProperty.call(core_info, component_key)) {
      current_config = core_info[component_key];
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
    console.error(`[ERROR] helper_common_get_clk_enable_mode: ${e}`);
  }

  return result;
}


/**
  * Prepare an object will be used by stm32_system_template.c.hbs & stm32_hal_def_template.h.hbs templates
  * @note  Function called inside stm32_system_template.c.hbs & stm32_hal_def_template.h.hbs
  * @param {object} sw_project_api Getters to SWProjectAPI
  * @param {object} dma_api        Getters to DmaAPI
  * @param {object} sw_config_api  Getters to SWConfigurationAPI
  * @param {object} pinout_api     Getters to pinoutAPI
  * @param {object} periph_api     Getters to peripheralsResourceManagerAPI
  * @param {object} strategy       Code generation strategy (HW or SW)
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
function helper_common_get_sw_config_ctxt(
  sw_project_api,
  dma_api,
  sw_config_api,
  pinout_api,
  periph_api,
  strategy
) {
  let result = {
    component: [],
    includes: [],
    periphs: [],
    cfg_index: {},
    save_hal_handle: {},
    instanceIndex: 0,
  };
  try {
    let cfg_index = {};
    let save_hal_handle = {};
    console.log(`[INFO] helper_common_get_sw_config_ctxt`);

    components = sw_project_api.getUsedComponents('asObject', { hash: { cgroup: 'STM32CubeMX2 Config'}});
    console.log(`[INFO]         components=${JSON.stringify(components)}`);

    components.forEach((component) => {
      let hw_instances = [];
      current_component = component.csub;
      console.log(`[INFO]         current_component=${current_component}`);
      /* Retrieve the list of HW instances linked to the current component */
      if (current_component === 'GPIO') {
        hw_instances = pinout_api.getGpioGroupsIdentifiers(component.original_id);
      }
      else if (current_component === 'DMA') {
        hw_instances = dma_api.getAllAllocatedDMAResourcesBoundToStandalone(component.original_id);
        result["dma_cxt"] = hw_instances;
      }
      else if (current_component === 'System') {
        let system_ctxt = sw_config_api.getInstances(component.original_id);
        result["system_cxt"] = sw_config_api.getSwInstanceConfiguration(system_ctxt[0]);
      }
      else {
        hw_instances = periph_api.getPeripheralsBoundToSoftwareComponent(component.original_id);
      }
      /* Save the current component if not seen yet */
      if (result["component"].indexOf(current_component) === -1) {
        result["component"].push(current_component);
      }
      /* if there are no HW instances linked to the current component, do not retrieve the configuration */
      if (hw_instances.length) {
        let resource = undefined;
        let components_instances_id;
        components_instances_id = sw_config_api.getInstances(component.original_id);

        components_instances_id.forEach((instance_id, index) => {
          let labels = [];
          let config = sw_config_api.getSwInstanceConfiguration(instance_id);

          /* Retrieve the HW resource */
          if (current_component === "GPIO")
            resource = hw_instances[index].name;
          else if (current_component === "DMA")
            resource = hw_instances[index].resourceId;
          else {
            resource = periph_api.getPeripheralBoundToSoftwareInstance(instance_id);
            if (resource.includes('.')) {
              // Split at the first dot and return the part after it
              resource = resource.split('.', 2)[0];
            }
            if (current_component === "ICACHE") {
              /* Save only the context for ICACHE */
              result["icache_instance"] = resource;
              result["icache_layer"] = config.info.layer;
            }
            else if (current_component === "RCC") {
              /* Save only the context for RCC */
              result["rcc_cxt"] = config;
            }
            else if (current_component === "PWR") {
              /* Save only the context for PWR */
              result["pwr_cxt"] = config;
            }
          }

          /* For dummy parameters, there are no layer inside info block */
          if (
            config.info !== undefined && config.info.layer !== undefined &&
            resource !== undefined
          ) {
            /* Save the includes to generate */
            if (strategy === 'SW') {
              if (current_component === "RIF") {
                result["includes"].push("tee");
              } else {
                if (!result["includes"].includes(current_component)) {
                  result["includes"].push(current_component);
                }
              }
            }
            else {
             if (current_component === "RIF") {
                result["includes"].push("tee");
              } else {
                if (!result["includes"].includes(resource)) {
                  result["includes"].push(resource);
                }
              }
            }

            /* save the list of labels used for this SW instance */
            if (
              config.info.labels !== undefined &&
              config.info.labels.length != 0
            ) {
              config.info.labels.forEach((label) => {
                labels.push(label.replace("-", "_"));
              });
            }
            // index of the config depends on the current HW resource and current component
            let resource_component = current_component + "_" + resource;
            if (!cfg_index.hasOwnProperty(resource_component)) {
              cfg_index[resource_component] = 0;
            }
            /* Save function if exist */
            let fct_type = undefined;
            if (config.info.function_type !== undefined) {
              fct_type = config.info.function_type;
            }
            /* Save function if exist */
            let layer = undefined;
            if (config.info.layer !== undefined) {
              layer = config.info.layer;
            }
            let generated = false;
            let default_to_be_called = false;
            /* RCC & PWR are called early in the startup */
            if ((config.info.init_type != "disabled") && (current_component !== "RCC") && (current_component !== "PWR")) {
              generated = true;
              if (config.info.init_type === "called") {
                default_to_be_called = true;
              }
            }
            if ((generated || (current_component === "RCC") || (current_component === "PWR")) && !result.hasOwnProperty(resource)) {
              result[resource] = false;
            }
            /* Do not generate aliases inside mx_hal_def.h for timebase functions */
            if (!config.hasOwnProperty('hal_timebase')) {
              let periph = common_get_periph_labels(
                resource,
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
              if (default_to_be_called && !result[resource]) {
                periph["default"] = true;
                result[resource] = true;
              }
              /* Check if initialization function return system_status_t or hal_ppp_handle_t */
              periph["NoHandle"] = false;
              if (ComponentWithNoHandle.includes(current_component)) {
                periph["NoHandle"] = true;
              }
              /* ICACHE should be initialized 1st inside the peripheral_init function */
              if (periph["resource"] == "ICACHE") {
              let enabledInterrupts = [];
                let interruptFlagMap;

                // Map monitor property names to their corresponding HAL_DCACHE flag names
                if(config.info.layer == "HAL") {
                  interruptFlagMap = {
                    SingleECCError: 'HAL_ICACHE_IT_SINGLE_ECC',
                    DoubleECCError: 'HAL_ICACHE_IT_DOUBLE_ECC',
                    CacheError: 'HAL_ICACHE_IT_ERROR'
                  };
                } else {
                  interruptFlagMap = {
                    SingleECCError: 'LL_ICACHE_IER_SERRIE',
                    DoubleECCError: 'LL_ICACHE_IER_DERRIE',
                    CacheError: 'LL_ICACHE_IER_ERRIE'
                  };
                }

                // Iterate over the monitor flags and collect enabled ones
                for (const [key, flagName] of Object.entries(interruptFlagMap)) {
                  if (config.System.ChoseErrorInterrupt?.[key] === true) {
                    enabledInterrupts.push(flagName);
                  }
                }

                /* save the interruption configuration */
                if (enabledInterrupts.length === Object.keys(interruptFlagMap).length) {
                  // All monitors enabled
                  if(config.info.layer == "HAL") {
                    periph["interruption"] = 'HAL_ICACHE_IT_ALL';
                  } else {
                    periph["interruption"] = 'LL_ICACHE_IER_ALL';
                  }
                } else if (enabledInterrupts.length === 0 && config.info.layer == "HAL") {
                  periph["interruption"] = 'HAL_ICACHE_IT_NONE';
                } else {
                  periph["interruption"] = enabledInterrupts.join(' | ');
                }

                result["periphs"].unshift(periph);
              } else if (periph["component"] == "XSPIM") {
                if ((result["periphs"].length == 0) || (result["periphs"][0].component == "XSPI")) {
                  result["periphs"].splice(0, 0, periph);
                } else {
                  result["periphs"].splice(1, 0, periph);
                }
              } else {
                result["periphs"].push(periph);
              }
            }
          } else {
            /* There are no blocks information */
            console.log(
              `[WARNING] helper_common_get_sw_config_ctxt: no blocks or info block`
            );
          }
        });
      }
    });
  } catch (e) {
    console.log(`[ERROR] helper_common_get_sw_config_ctxt ${e}`);
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
    if (global_needs !== "undefined" && global_needs !== undefined) {
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
 * @param {string} ppp_instance HW instance of PPP (ex I2C1), 'undefined' is not necessary
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
 * Add sub-instances to be generated for LL code optimization
 * @param {string} sub_instances Sub instances of PPP (ex GPIO_PIN)
 * @returns
 */
function helper_common_gen_ll_code_add_subinst(sub_instances) {
  try {
    /*console.log(`[INFO] helper_common_gen_ll_code_add_subinst: sub_instances=${sub_instances}`);*/
    Sub_Instances = sub_instances;
  } catch (e) {
    console.log(`[ERROR] helper_common_gen_ll_code_add_subinst: ${e}`);
  }
  return;
}

const LL_OPTIM_LUT_ACCESSOR = {
  RCC: {file: './rcc_ll_optim_helpers.js', func: 'helper_rcc_get_lut_table', lut: undefined},
  PWR: {file: './pwr_helpers.js', func: 'helper_pwr_get_lut_table', lut: undefined},
  /*GPIO: {func: 'helper_rcc_get_lut_table', file: './rcc_ll_optim_helpers.js', lut: undefined},*/
};

/**
 * Construct the LL code to be generated with or without comments depends if the LL functions
 * @detail  This API must be used when driver does not have sub-instances
 * @param {string} ppp_function Function to be checked if it can be commented or not
 * @param {...any} arguments Dynamic of the arguments of the function (can be empty)
 * @returns {string} Code to be generated in LL function (with or without comments)
 */
function helper_common_gen_ll_code(ppp_function, ...args) {
  try {
    /*console.log(`[INFO] helper_common_gen_ll_code: ppp_function=${ppp_function}`);*/
    let ret;
    const ppp = ppp_function.split("_")[1];
    const usefulArgs = args.slice(0, -1); /* Remove last argument (caller informations) */
    code = ppp_function + "(";

    /* PARTIAL Management */
    if (ppp in LL_OPTIM_LUT_ACCESSOR)
    {
      const accessor = LL_OPTIM_LUT_ACCESSOR[ppp];

      /* Load LUT if not already loaded */
      if ( accessor.lut === undefined){
        const all_functions = require(accessor.file);
        if (typeof all_functions[accessor.func] === "function"){
          accessor.lut = all_functions[accessor.func]();
        }
      }

      /* Temporarily update LUT_Table */
      const saved_LUT = LUT_Table;
      LUT_Table = accessor.lut || LUT_Table;
      ret = common_gen_ll_code(ppp_function, ...usefulArgs);
      LUT_Table = saved_LUT;
    }
    else if(typeof PPP_Instance !== "undefined") {
      code += PPP_Instance;
      ret = common_gen_ll_code(ppp_function, ...usefulArgs);
    }
    else {
      ret = common_gen_ll_code(ppp_function, ...usefulArgs);
    }

    return ret;
  } catch (e) {
    console.log(`[ERROR] helper_common_gen_ll_code: ${e}`);
  }
}

/**
 * Construct the LL code to be generated with or without comments depends if the LL functions
 * @detail  This API must be used when driver has sub-instances
 * @param {string} ppp_function Function to be checked if it can be commented or not
 * @param {...any} arguments Dynamic of the arguments of the function (can be empty)
 * @returns {string} Code to be generated in LL function (with or without comments)
 */
function helper_common_gen_ll_code_subinst(ppp_function) {
  try {
    /*console.log(`[INFO] helper_common_gen_ll_code_subinst: ppp_function=${ppp_function}`);*/
    /* exclude options + 1st argument */
    var args = Array.prototype.slice.call(arguments, 1, -1);

    if (Sub_Instances === undefined) {
      console.log(`[WARNING] helper_common_gen_ll_code_subinst: sub instances is undefined`);
    }

    code = ppp_function + "(";
    if (PPP_Instance !== "undefined") {
      code = code + PPP_Instance;
      if (Sub_Instances !== undefined) {
        code = code + ", " + Sub_Instances;
      }
    } else {
      if (Sub_Instances !== undefined) {
        code = code + Sub_Instances;
      }
    }
    return common_gen_ll_code(ppp_function, ...args);
  } catch (e) {
    console.log(`[ERROR] helper_common_gen_ll_code_subinst: ${e}`);
  }
}

function concat() {
  var args = Array.prototype.slice.call(arguments, 0, -1); /* Exclude arguments options */
  return args.join("");
}

/**
  * Get the element of the array at index value
  * @param {array} array Array used to get the element
  * @param {integer} index Index of the element inside the array
  * @returns Element saved at the index of the array
  */
function helper_common_get_elt_in_array(array, index) {
  try {
    console.log(`[INFO] helper_common_get_elt_in_array: array=${JSON.stringify(array)}`);
    return array[index];
  } catch (e) {
    console.log(`[ERROR] helper_common_get_elt_in_array: ${e}`);
    return false;
  }
}

/**
 * @detail  This API checks if a value is undefined or not
 * @param {...any} value any object, boolen, string...
 * @returns {boolean} returns true if the value exists
 */
function helper_common_is_defined(value) {
  return (value !== undefined);
}

function helper_common_display_object(object) {
  console.log(`[INFO] helper_common_display_object: object=${JSON.stringify(object)}`);
  return true;
}


module.exports = {
  helper_common_initialize_index,

  helper_common_get_index,

  helper_common_inc_index,

  helper_common_get_generated_function_name,

  helper_common_get_generated_function_calls,

  helper_common_if_value_is_enabled,

  helper_common_if_component_is_enabled,

  helper_common_if_rcc_clock_activated,

  helper_common_get_clk_enable_mode,

  helper_common_get_sw_config_ctxt,

  helper_common_concatenate_needs,

  helper_common_concatenate_elt_in_array,

  helper_common_get_object_by_key,

  helper_common_initialize_ll_code,

  helper_common_gen_ll_code_add_subinst,

  helper_common_gen_ll_code,

  helper_common_gen_ll_code_subinst,

  concat,

  helper_common_get_elt_in_array,

  helper_common_is_defined,

  helper_common_display_object
};
