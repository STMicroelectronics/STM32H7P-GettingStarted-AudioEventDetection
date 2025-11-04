/**
 * @file CORTEX/NVIC Helpers functions to provide service to the HAL components
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
 * @brief Retrieve the full list of IRQ lines needed for a SW instance (include PPP + DMA + EXTI)
 *
 * @param {object} nvic_api       NvicAPI.getNeedById
 * @param {object} nvic_context   List of tuples: [nvic_need, current_resource_hw, generate_handler]
 * @param {string} hal_component  SW instance component (ex UART or DMA)
 * @returns {object} Full list consolidated inside the following object
 *
 * @note The returned array contains IRQ information objects structured as follows:
 * [
 *   {
 *     description: <string>,        // Description of the IRQ line
 *     line: <string>,               // IRQ line identifier
 *     shared: <boolean>,            // Indicates if the IRQ line is shared
 *     generate_handler: <boolean>,  // Indicates if the IRQ Handler should be generated or not
 *     resource_hw: <string>,        // Associated hardware resource (e.g., I2C1, GPDMA1_CH0)
 *     component: <string>           // Component type (e.g., EXTI, DMA, or the specified hal_component)
 *     irq_suffix: <string>          // IRQ line suffix after removing the hw resource prefix (e.g., "_TRGI_COM_DIR_IDX")
 *   },
 *   ...
 * ]
 *
 * Usage:
 * - Iterate over the 'list_irq' array to access individual IRQ information.
 * - Each entry provides details about the IRQ line, including its component type and associated hardware resource.
 * - Use this information to configure or manage IRQ lines as needed in your application.
 */
function helper_cortex_nvic_get_irqline_info_list(
  nvic_api,
  nvic_context,
  hal_component
) {
  console.log(`[INFO] helper_cortex_nvic_get_irqline_info_list`);
  let list_irq = [];

  try {
    console.log(
      `[INFO] helper_cortex_nvic_get_irqline_info_list: nvic_api=${JSON.stringify(nvic_api)}, ` +
      `nvic_context=${JSON.stringify(nvic_context)}, hal_component=${hal_component}`
    );

    if (!Array.isArray(nvic_context) || nvic_context.length === 0) {
      console.log(`[INFO] helper_cortex_nvic_get_irqline_info_list: nvic_context is empty or not an array`);
      return list_irq;
    }

    nvic_context.forEach(([nvic_need, current_resource_hw, generate_handler]) => {
      const nvic_config = nvic_api.getNeedById(nvic_need.id);

      if (typeof nvic_config === "undefined") {
        console.log(`[INFO] helper_cortex_nvic_get_irqline_info_list: NVIC config not found for id=${nvic_need.id}`);
        return; // Skip this iteration
      }

      const { name: irq_line, description } = nvic_config;

      // Check if this IRQ line is already added
      const found_irq_line = list_irq.some(irq_info => irq_info.line === irq_line);

      if (!found_irq_line) {
        const irq_info = {
          description,
          line: irq_line,
          shared: false,                // Currently hardcoded
          generate_handler: generate_handler,
        };

        // Determine component and resource_hw based on IRQ line naming
        if (irq_line.includes("EXTI")) {
          irq_info.resource_hw = irq_line;
          irq_info.component = "EXTI";
        } else if (irq_line.includes("DMA") && !irq_line.includes("DMA2D")) {
          irq_info.resource_hw = irq_line;
          irq_info.component = "DMA";
        } else {
          irq_info.resource_hw = current_resource_hw;
          irq_info.component = hal_component;
        }

        // Suffix extraction logic (irq_line always starts with resource_hw)
        if (irq_line.includes("DMA") || irq_line.includes("EXTI")) {
          irq_info.irq_suffix = "";
        } else {
          irq_info.irq_suffix = irq_line.substring(irq_info.resource_hw.length);
        }

        list_irq.push(irq_info);
      }
    });
  } catch (e) {
    console.log(`[ERROR] helper_cortex_nvic_get_irqline_info_list: ${e}`);
  }

  console.log(`[INFO] helper_cortex_nvic_get_irqline_info_list: result=${JSON.stringify(list_irq)}`);

  return list_irq;
}

/**
 * Concatenate IRQ contexts to build a unified list of NVIC needs with associated hardware resources and handler flags.
 *
 * @param {Array} global_context              Existing global context array containing tuples of [nvic_need, resource_hw, generate_handler].
 * @param {Array} current_needs               Array of NVIC needs to add.
 * @param {string} current_resource_hw        Hardware resource string associated with the current needs (e.g., "I2C1", "UART3").
 * @param {boolean} current_generate_handler  Flag indicating if the IRQ handler should be generated for these needs.
 * @returns {Array} Updated global context array with new [nvic_need, resource_hw, generate_handler] tuples appended.
 *
 * @note
 * - This function merges the current NVIC needs with the existing global context by creating tuples that associate each need
 *   with its hardware resource and handler generation flag.
 * - The returned array can be used as input for functions expecting a list of IRQ contexts, such as IRQ line info retrieval.
 * - It preserves the original global context and appends new tuples without modifying the input arrays.
 */
function helper_cortex_nvic_concatenate_irq_context(
  global_context,
  current_needs,
  current_resource_hw,
  current_generate_handler
) {
  let result = [];

  try {
    console.log(`[INFO] helper_cortex_nvic_concatenate_irq_context`);
    console.log(
      `[INFO] helper_cortex_nvic_concatenate_irq_context: current_needs=${JSON.stringify(
        current_needs
      )}, global_context=${JSON.stringify(global_context)}, current_resource_hw=${current_resource_hw}, current_generate_handler=${current_generate_handler}`
    );

    // Start with existing global_context if defined and is an array
    if (Array.isArray(global_context)) {
      result = [...global_context];
    }

    // Append tuples for each need in current_needs
    if (Array.isArray(current_needs)) {
      current_needs.forEach((need) => {
        result.push([need, current_resource_hw, current_generate_handler]);
      });
    }
  } catch (e) {
    console.error(`[ERROR] helper_cortex_nvic_concatenate_irq_context: ${e}`);
  }

  return result;
}

/**
 * @brief Retrieve the full list of IRQ lines needed for a SW instance (include PPP + DMA + EXTI)
 *
 * @param {object} nvic_api       NvicAPI.getNeedById
 * @param {object} nvic_needs     list of incremented needs given by interrupt
 * @param {string} hw_resource    current HW resource (ex I2C1 or GPDMA1_CH0)
 * @param {string} hal_component  SW instance component (ex UART or DMA)
 * @param {string} type_component Main function used for the SW component (can be undefined)
 * @returns {object} Full list consolidated inside the following object
 *
 * @note The returned object contains a list of IRQ information, structured as follows:
 * {
 *   list_irq: [
 *     {
 *       description: <string>,  // Description of the IRQ line
 *       line: <string>,         // IRQ line identifier
 *       shared: <boolean>,      // Indicates if the IRQ line is shared
 *       resource_hw: <string>,  // Associated hardware resource (e.g., I2C1, GPDMA1_CH0)
 *       component: <string>     // Component type (e.g., EXTI, DMA, or the specified hal_component)
 *       irq_suffix: <string>    // IRQ line suffix after removing the hw resource prefix (e.g., "_TRGI_COM_DIR_IDX")
 *     },
 *     ...
 *   ]
 * }
 *
 * Usage:
 * - Iterate over the 'list_irq' array to access individual IRQ information.
 * - Each entry provides details about the IRQ line, including its component type and associated hardware resource.
 * - Use this information to configure or manage IRQ lines as needed in your application.
 */
function helper_cortex_nvic_get_irqline_info_list_legacy(
  nvic_api,
  nvic_needs,
  hw_resource,
  hal_component,
  type_component
) {
  console.log(`[INFO] helper_cortex_nvic_get_irqline_info_list_legacy`);
  let result = { list_irq: [] };

  try {
    console.log(
      `[INFO] helper_cortex_nvic_get_irqline_info_list_legacy: nvic_api=${JSON.stringify(nvic_api)}, ` +
      `nvic_needs=${JSON.stringify(nvic_needs)}, hw_resource=${hw_resource}, ` +
      `hal_component=${hal_component}, type_component=${type_component}`
    );

    // Check if nvic_needs is a non-empty array
    if (!Array.isArray(nvic_needs) || nvic_needs.length === 0) {
      console.log(`[INFO] helper_cortex_nvic_get_irqline_info_list_legacy: nvic_needs is empty or not an array`);
      return result;
    }

    nvic_needs.forEach((need) => {

      let nvic_config = nvic_api.getNeedById(need.id);

      if (typeof nvic_config === "undefined") {
        console.log(`[INFO] helper_cortex_nvic_get_irqline_info_list_legacy: NVIC config not found`);
      }

      const irq_line = nvic_config["name"];
      let found_irq_line = false;

      result["list_irq"].forEach((irq_info) => {
        if (irq_info["line"] === irq_line) {
          found_irq_line = true;
        }
      });

      // IRQ line did not belong to the IRQ lines list - add it
      if (!found_irq_line) {
        const irq_info = {
          description: nvic_config["description"],
          line: irq_line,
          shared: false, // Currently hardcoded, adjust if shared IRQ detection is added
        };

        if (irq_line.includes("EXTI")) {
          irq_info["resource_hw"] = irq_line;
          irq_info["component"] = "EXTI";
        } else if (irq_line.includes("DMA") && !irq_line.includes("DMA2D")) {
          irq_info["resource_hw"] = irq_line;
          irq_info["component"] = "DMA";
        } else {
          let resource_hw = hw_resource;
          if (type_component !== undefined && type_component !== "undefined") {
          resource_hw += `_${type_component}`;
          }
          console.log(
            `[INFO] helper_cortex_nvic_get_irqline_info_list_legacy: resource_hw=${resource_hw}, ` + `irq_line=${irq_line}`
          );
          irq_info["component"] = hal_component;
          irq_info["resource_hw"] = resource_hw;
        }

        // Extract suffix of irq_line after removing resource_hw prefix
        irq_info["irq_suffix"] = irq_line.slice(irq_info["resource_hw"].length);

        result["list_irq"].push(irq_info);
      }
    });
  } catch (e) {
    console.log(`[ERROR] helper_cortex_nvic_get_irqline_info_list_legacy: ${e}`);
  }

  console.log(`[INFO] helper_cortex_nvic_get_irqline_info_list_legacy: result=${JSON.stringify(result)}`);

  return result;
}

/**
 * @brief Convert priority grouping from NVIC getter to value to be used by NVIC CMSIS driver
 *
 * @param {integer} prio_grouping priority grouping returned by NVIC getter
 * @returns {integer} value to set in NVIC CMSIS driver
 */
function helper_cortex_nvic_retrieve_ll_priority_grouping(prio_grouping) {
  try {
    const map_ll_prio_grouping = {
      0: 3,
      1: 4,
      2: 5,
      3: 6,
      4: 7,
    };
    return map_ll_prio_grouping[prio_grouping];
  } catch (e) {
    console.log(`[ERROR] helper_cortex_nvic_retrieve_ll_priority_grouping: ${e}`);
  }
  return {};
}

/**
 * @brief Convert priority grouping from NVIC getter to value to be used by HAL driver
 *
 * @param {integer} prio_grouping priority grouping returned by NVIC getter
 * @returns {integer} value to set in HAL driver
 */
function helper_cortex_nvic_retrieve_hal_priority_grouping(prio_grouping) {
  try {
    const map_hal_prio_grouping = {
      0: 4,
      1: 3,
      2: 2,
      3: 1,
      4: 0,
    };
    return map_hal_prio_grouping[prio_grouping];
  } catch (e) {
    console.log(`[ERROR] helper_cortex_nvic_retrieve_hal_priority_grouping: ${e}`);
  }
  return {};
}

/**
 * @brief Convert System lines retrieved in NVIC store by the System line to be used for DFP
 *
 * @param {string} string Name of system lines returned by NVIC getter
 * @returns {string} Convert System lines to lines interpreted by DFP
 */
function helper_cortex_nvic_convert_system_lines(string) {
  const map_system_lines = {
    "Debug Monitor": "DebugMonitor",
    MemManage: "MemoryManagement",
    SVC: "SVCall",
  };

  if (map_system_lines.hasOwnProperty(string)) {
    string = map_system_lines[string];
  }
  return string;
}

module.exports = {
  helper_cortex_nvic_get_irqline_info_list_legacy,

  helper_cortex_nvic_get_irqline_info_list,

  helper_cortex_nvic_concatenate_irq_context,

  helper_cortex_nvic_retrieve_ll_priority_grouping,

  helper_cortex_nvic_retrieve_hal_priority_grouping,

  helper_cortex_nvic_convert_system_lines,
};
