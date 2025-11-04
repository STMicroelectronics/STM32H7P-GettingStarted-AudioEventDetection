/**
  * @file GPIO Helpers functions to provide service to the HAL components
  * @author GPM Application Team
  * @attention
  *
  * Copyright (c) 2024-2025 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
**/

/** @global */
const map_mode = {
  ANALOG: "HAL_GPIO_MODE_ANALOG",
  INPUT: "HAL_GPIO_MODE_INPUT",
  OUTPUT: "HAL_GPIO_MODE_OUTPUT",
  ALTERNATE: "HAL_GPIO_MODE_ALTERNATE",
};

const map_output = {
  OPENDRAIN: "HAL_GPIO_OUTPUT_OPENDRAIN",
  PUSHPULL: "HAL_GPIO_OUTPUT_PUSHPULL",
};

const map_speed = {
  FREQ_LOW: "HAL_GPIO_SPEED_FREQ_LOW",
  FREQ_MEDIUM: "HAL_GPIO_SPEED_FREQ_MEDIUM",
  FREQ_HIGH: "HAL_GPIO_SPEED_FREQ_HIGH",
  FREQ_VERY_HIGH: "HAL_GPIO_SPEED_FREQ_VERY_HIGH",
};

const map_pull = {
  NO: "HAL_GPIO_PULL_NO",
  UP: "HAL_GPIO_PULL_UP",
  DOWN: "HAL_GPIO_PULL_DOWN",
};

const map_lpgio = {
  PA1: 0,
  PA3: 1,
  PA6: 2,
  PB1: 3,
  PB10: 4,
  PC2: 5,
  PD13: 6,
  PD2: 7,
  PC10: 8,
  PB0: 9,
  PC12: 10,
  PB3: 11,
  PB3: 12,
  PE0: 13,
  PE2: 14,
  PE3: 15,
};

/**
 * Retrieve all the EXTI lines configured inside the GPIO SW component.
 * @param {string} layer     Current layer (HAL or LL)
 * @param {object} gpio_ctxt GPIO configuration of a pin
 * @param {object} pin       PIN configuration retrieved thanks to @ref @root.pinoutAPI.getPinData getter
 * @param {object} exti_object current id list of EXTI (undefined if 1st call)
 * @returns {object} EXTI object
 * {
 *     "list_exti": [
 *         "0",
 *         "8"
 *     ],
 *     "list_uuid": [
 *         {
 *             "layer": "HAL",
 *             "id": "<uuid-#1>"
 *         },
 *         {
 *             "layer": "HAL",
 *             "id": "<uuid-#2>"
 *         },
 *         {
 *             "layer": "LL",
 *             "id": "<uuid-#3>"
 *         }
 *     ]
 * }
 */
function helper_gpio_retrieve_exti_object(layer, gpio_ctxt, pin, exti_object) {
  let result = { list_exti: [], list_uuid: [] };
  try {
    console.log(
      `[INFO] helper_gpio_retrieve_exti_object: gpio_ctxt=${JSON.stringify(
        gpio_ctxt
      )}, exti_object=${JSON.stringify(exti_object)}, pin=${JSON.stringify(
        pin
      )}`
    );
    if (exti_object !== "undefined") {
      result = exti_object;
    }
    let gpio_pad = pin;
    /** Save only a unique list of EXTI for HAL only */
    let exti_name = "EXTI" + gpio_pad["index"].toString();
    if (layer === "HAL" && result["list_exti"].indexOf(exti_name) < 0) {
      result["list_exti"].push(exti_name);
    }
    let gpio_config = gpio_ctxt["basic"];
    /** Save only a unique list of uuid for all the config */
    if (
      gpio_config.hasOwnProperty("extiConfig") &&
      gpio_config["extiConfig"].hasOwnProperty("needs")
    ) {
      result.list_uuid.push({
        layer: layer,
        id: gpio_config["extiConfig"]["needs"][0]["id"],
      });
    }
    /* Generate only IRQ handler for */
  } catch (e) {
    console.log(`[ERROR] helper_gpio_retrieve_exti_object: ${e}`);
  }
  //console.log(`[INFO] helper_gpio_retrieve_exti_object: result=${JSON.stringify(result)}`);
  return result;
}

/**
 * Retrieve from the GPIO context the list of GPIO to be generated for a mx_pppi.c
 * @detail Used only for other PPP through �GPIO_HAL_partial init|deinit�
 * @param {object} gpio_ctxt GPIO configuration of a pin (retrieved thanks to pinoutAPI.getNeedById)
 * ex
 *  {
 *      AFid: 2,
 *      componentInstanceId: 'instanceTwo',
 *      gpioPad: {
 *        hslv: false,
 *        lowPower: false,
 *        index: 2,
 *        port: 'Two'
 *      },
 *      hwInstance: 'instanceTwo',
 *      needId: 'someNeedId',
 *      pinType: 'gpio',
 *      signalName: 'signalTwo',
 *      signalType: 'alternate',
 *      labels: [],
 *      configuration: { someConfig: 'someConfig' }
 *    }
 * @param {object} gpio_config HAL parameters to be managed inside the generated code (undefined if 1st call)
 * @returns {object} HAL parameters to be set in the mx_pppi_template.c.hbs file through GPIO_HAL_partial.hbs
 *  ex
 *  {
 *      "list_port": [
 *          "B"
 *      ],
 *      "list_config_pins": [
 *          {
 *              "mode": "HAL_GPIO_MODE_ALTERNATE",
 *              "outputType": "HAL_GPIO_OUTPUT_PUSHPULL",
 *              "pullMode": "HAL_GPIO_PULL_UP",
 *              "port": "B",
 *              "pin": 6,
 *              "extInterrupt": true,
 *              "af": 4,
 *              "signalName": "I2C1_SCL",
 *              "labels": []
 *          },
 *          {
 *              "mode": "HAL_GPIO_MODE_ALTERNATE",
 *              "outputType": "HAL_GPIO_OUTPUT_PUSHPULL",
 *              "pullMode": "HAL_GPIO_PULL_UP",
 *              "port": "B",
 *              "pin": 7,
 *              "extInterrupt": true,
 *              "af": 4,
 *              "signalName": "I2C1_SDA",
 *              "labels": []
 *          }
 *      ]
 *  }
 */
function helper_gpio_get_gpioconfig_object(gpio_ctxt, gpio_config) {
  let result = { list_port: [], list_config_pins: [] };
  try {
    console.log(
      `[INFO] helper_gpio_get_gpioconfig_object: gpio_ctxt=${JSON.stringify(
        gpio_ctxt
      )}, gpio_config=${JSON.stringify(gpio_config)}`
    );

    // If gpio_config is defined and not the string "undefined", use it as the initial result
    if (gpio_config !== undefined && gpio_config !== "undefined") {
      result = gpio_config;
    }

    let current_config = {};

    // Check if gpio_ctxt contains a 'basic' configuration
    if (
      gpio_ctxt.hasOwnProperty("configuration") &&
      gpio_ctxt["configuration"].hasOwnProperty("basic")
    ) {
      // Clone the basic configuration to avoid mutating the original object
      current_config = { ...gpio_ctxt["configuration"]["basic"] };

      // Initialize label_name as an array of arrays (labels per pin)
      if (gpio_ctxt["configuration"].hasOwnProperty("label_name")) {
        let labels = gpio_ctxt["configuration"]["label_name"];
        if (!Array.isArray(labels)) {
          labels = [labels];
        }
        current_config["label_name"] = [labels]; // wrap in outer array for this pin
      } else {
        current_config["label_name"] = [];
      }

      // Initialize userLabels as an array of arrays (labels per pin)
      if (gpio_ctxt.hasOwnProperty("userLabels")) {
        let userlabel = gpio_ctxt["userLabels"];
        if (!Array.isArray(userlabel)) {
          userlabel = [userlabel];
        }
        current_config["userLabels"] = [userlabel]; // wrap in outer array for this pin
      } else {
        current_config["userLabels"] = [];
      }
    } else {
      // Use hardcoded default configuration if none found in gpio_ctxt
      console.log(
        `[INFO] helper_gpio_get_gpioconfig_object: hard coded pin config`
      );
      current_config = {
        mode: "ALTERNATE",
        outputType: "OPENDRAIN",
        pullMode: "NONE",
        maxSpeed: "HIGH",
        label_name: [],
        userLabels: [],
      };
    }

    let current_gpio = {};

    // Retrieve GPIO port and index, or use defaults if missing
    if (gpio_ctxt.hasOwnProperty("gpioPad")) {
      current_gpio = gpio_ctxt["gpioPad"];
    } else {
      console.log(`[INFO] helper_gpio_get_gpioconfig_object: hard coded pin`);
      current_gpio = {
        port: "B",
        index: 6,
      };
    }

    // Add the GPIO port to list_port if not already present
    if (result["list_port"].indexOf(current_gpio["port"]) < 0) {
      result["list_port"].push(current_gpio["port"]);
    }

    // Add optional properties if they exist
    if (gpio_ctxt.hasOwnProperty("AFid")) {
      current_config["af"] = gpio_ctxt["AFid"];
    }
    if (gpio_ctxt.hasOwnProperty("labels")) {
      current_config["hw_label"] = gpio_ctxt["labels"];
    }
    current_config["port"] = current_gpio["port"];

    // Harmonize property names to match those used in comparison
    if (
      current_config.hasOwnProperty("maxSpeed") &&
      !current_config.hasOwnProperty("speed")
    ) {
      current_config["speed"] = current_config["maxSpeed"];
    }
    if (
      current_config.hasOwnProperty("outputType") &&
      !current_config.hasOwnProperty("output_type")
    ) {
      current_config["output_type"] = current_config["outputType"];
    }
    if (
      current_config.hasOwnProperty("pullMode") &&
      !current_config.hasOwnProperty("pull")
    ) {
      current_config["pull"] = current_config["pullMode"];
    }

    let found_same_config = false;

    // Iterate over existing pin configurations to find a matching one
    result["list_config_pins"].forEach((gpio_config) => {
      if (
        gpio_config["port"] == current_config["port"] &&
        gpio_config["mode"] == current_config["mode"] &&
        gpio_config["speed"] == current_config["speed"] &&
        gpio_config["output_type"] == current_config["output_type"] &&
        gpio_config["af"] == current_config["af"] &&
        gpio_config["pull"] == current_config["pull"]
      ) {
        found_same_config = true;

        // Add current pin index to existing config's pin list
        gpio_config["pin"].push(current_gpio["index"].toString());

        // Create EXTI config object for this pin
        let exti_config = {};
        exti_config["pin"] = current_gpio["index"].toString();
        exti_config["port"] = current_config["port"];
        exti_config["exti_enabled"] = current_config["EnableEXTI"];
        exti_config["config"] = current_config.extiConfig;

        // Add EXTI config and signal name to existing config
        gpio_config["exti_cfg"].push(exti_config);
        gpio_config["signalName"].push(gpio_ctxt["signalName"]);

        // Add label_name array for this pin as a new element (array of labels)
        if (
          gpio_ctxt["configuration"] &&
          gpio_ctxt["configuration"].hasOwnProperty("label_name")
        ) {
          let newLabels = gpio_ctxt["configuration"]["label_name"];
          if (!Array.isArray(newLabels)) {
            newLabels = [newLabels];
          }
          gpio_config["label_name"].push(newLabels);
        }

        // Add userLabels array for this pin as a new element (array of labels)
        if (gpio_ctxt.hasOwnProperty("userLabels")) {
          let newuserLabels = gpio_ctxt["userLabels"];
          if (!Array.isArray(newuserLabels)) {
            newuserLabels = [newuserLabels];
          }
          gpio_config["userLabels"].push(newuserLabels);
        }
      }
    });

    // If no matching configuration found, create a new one
    if (!found_same_config) {
      // Initialize signalName array and add current signalName if present
      if (gpio_ctxt.hasOwnProperty("signalName")) {
        current_config["signalName"] = [];
        current_config["signalName"].push(gpio_ctxt["signalName"]);
      }

      // Initialize pin and exti_cfg arrays and add current pin and EXTI config
      current_config["pin"] = [];
      current_config["exti_cfg"] = [];
      current_config["pin"].push(current_gpio["index"].toString());

      let exti_config = {};
      exti_config["pin"] = current_gpio["index"].toString();
      exti_config["port"] = current_config["port"];
      exti_config["exti_enabled"] = current_config["EnableEXTI"];
      exti_config["config"] = current_config.extiConfig;

      current_config["exti_cfg"].push(exti_config);

      // Initialize label_name as array of arrays for this pin
      if (
        gpio_ctxt["configuration"] &&
        gpio_ctxt["configuration"].hasOwnProperty("label_name")
      ) {
        let labels = gpio_ctxt["configuration"]["label_name"];
        if (!Array.isArray(labels)) {
          labels = [labels];
        }
        current_config["label_name"] = [labels]; // wrap in outer array
      } else if (!current_config.hasOwnProperty("label_name")) {
        current_config["label_name"] = [];
      }

      // Initialize userLabels as array of arrays for this pin
      if (gpio_ctxt.hasOwnProperty("userLabels")) {
        let userlabel = gpio_ctxt["userLabels"];
        if (!Array.isArray(userlabel)) {
          userlabel = [userlabel];
        }
        current_config["userLabels"] = [userlabel]; // wrap in outer array
      } else if (!current_config.hasOwnProperty("userLabels")) {
        current_config["userLabels"] = [];
      }

      // Add the newly created config to the list
      result["list_config_pins"].push(current_config);
    }
    // console.log(
    //   `[INFO] helper_gpio_get_gpioconfig_object: result=${JSON.stringify(
    //     result
    //   )}`
    // );
  } catch (e) {
    console.log(`[ERROR] helper_gpio_get_gpioconfig_object: ${e}`);
  }
  return result;
}

/**
 * Convert the GPIO user settings to the GPIO data to be used inside mx_gpio_template.c.hbs template
 * @param {object} config current config of the pin
 * {
 *  "mode": "OUTPUT",
 *  "pull": "NO",
 *  "output_init_state": "LOW",
 *  "speed": "LOW",
 *  "output_type": "PUSHPULL",
 *  "FastMode": false,
 *  "HighSpeedLowVoltage": false
 *  }
 * @param {object} pin PIN configuration retrieved thanks to @root.pinoutAPI.getPinData getter
 * @param {object} gpio_config HAL parameters to be managed inside the generated code (undefined if 1st call)
 *  {
 *    "list_port": [
 *        "D"
 *    ],
 *    "list_config_pins": [
 *        {
 *            "mode": "OUTPUT",
 *            "pull": "NO",
 *            "output_init_state": "LOW",
 *            "speed": "LOW",
 *            "output_type": "PUSHPULL",
 *            "FastMode": false,
 *            "HighSpeedLowVoltage": false,
 *            "EnableEXTI": false,
 *            "labels": [],
 *            "port": "D",
 *            "pin": 13
 *        }
 *     ]
 *  }
 * @returns {object} HAL parameters to be set in the mx_gpio_template.c.hbs file (based on gpio_config object)
 */
function helper_gpio_get_gpioconfig_standalone_object(
  label_name,
  config,
  pin,
  gpio_config
) {
  let result = { list_port: [], list_config_pins: [] };
  try {
    console.log(
      `[INFO] helper_gpio_get_gpioconfig_standalone_object: config=${JSON.stringify(
        config
      )}, pin=${JSON.stringify(pin)}, gpio_config=${JSON.stringify(
        gpio_config
      )}`
    );
    if (gpio_config !== "undefined") {
      result = gpio_config;
    }
    let current_config = config;
    let current_gpio = pin;
    /** Save only a unique list of GPIO port */
    if (result["list_port"].indexOf(current_gpio["port"]) < 0) {
      result["list_port"].push(current_gpio["port"]);
    }

    if (pin.hasOwnProperty("signal")) {
      current_config["signalName"] = pin["signal"]["name"];
    }
    if (pin.hasOwnProperty("labels")) {
      current_config["labels"] = pin["labels"];
    }
    current_config["port"] = current_gpio["port"];
    current_config["pin"] = current_gpio["index"];
    current_config["aliases"] = helper_gpio_create_aliases(
      pin.labels,
      label_name
    );
    result["list_config_pins"].push(current_config);
    /*     console.log(
      `[INFO] helper_gpio_get_gpioconfig_standalone_object: result=${JSON.stringify(
        result
      )}`
    ); */
  } catch (e) {
    console.log(`[ERROR] helper_gpio_get_gpioconfig_standalone_object: ${e}`);
  }
  return result;
}

/**
 * Need to create the master label and secondary ones based on HW and SW labels
 * @param {Array} hwLabels: Array of hardware label strings (or arrays)
 * @param {Array} swLabels: Array of software label strings (or arrays)
 * @returns {object} return the master label and the secondary ones
 * {"other_labels":["SECONDARY"],"master_label":"GPIO_USER"}
 */
function helper_gpio_create_aliases(hwLabels, swLabels) {
  // Flatten arrays (only 1 level deep) to handle both flat arrays and arrays of arrays
  const flatten = (arr) => (Array.isArray(arr) ? arr.flat() : []);
  let flat_hwLabels = flatten(hwLabels);
  let flat_swLabels = flatten(swLabels);

  // Initialize result object
  let result = { other_labels: [] };
  let master_label = null;

  try {
    // Check if HW label exists and is not an empty string; set as master label if so
    if (flat_hwLabels.length > 0 && flat_hwLabels[0] !== "") {
      master_label = flat_hwLabels[0].toUpperCase();
    }
    // If no HW label, check if SW label exists and is not an empty string; set as master label if so
    else if (flat_swLabels.length > 0 && flat_swLabels[0] !== "") {
      master_label = flat_swLabels[0].toUpperCase();
    }

    // If a master label was found, build the list of other (secondary) labels
    if (master_label) {
      result.master_label = master_label;
      // Combine all HW and SW labels, filter out empty and master label, and convert to uppercase
      const all_labels = [...flat_hwLabels, ...flat_swLabels];
      result.other_labels = all_labels
        .filter((label) => label && label.toUpperCase() !== master_label)
        .map((label) => label.toUpperCase());
    }
    // Uncomment for debugging:
    // console.log(`[INFO] helper_gpio_create_aliases: result=${JSON.stringify(result)}`);
  } catch (e) {
    // Log any errors that occur during processing
    console.log(`[ERROR] helper_gpio_create_aliases: ${e}`);
  }
  return result;
}

function helper_gpio_add_pad_right(str, length) {
  str = String(str);
  while (str.length < length) {
    str = str + " ";
  }
  return str;
}

/**
 * Retrieve from the GPIO context the list of GPIO pins grouped by their port.
 * @detail This helper is used to accumulate and group GPIO pin indices by their port,
 *         based on the GPIO context of each pin. It is typically called iteratively
 *         (e.g., in a Handlebars loop) to build up a list of grouped pins for a given peripheral.
 *         The result is intended for use in GPIO_HAL_partial deinit code generation.
 * @param {object} gpio_ctxt - GPIO context for a single pin (as returned by pinoutAPI.getNeedById).
 * @param {Array} groupedPins - Accumulator array of grouped pins by port (should be undefined or [] on first call).
 * @returns {Array} Array of objects, each with the shape { port: string, pins: number[] },
 *                  suitable for use in mx_pppi_template.c.hbs via GPIO_HAL_partial.hbs.
 */
function helper_gpio_group_pins_by_port(gpio_ctxt, groupedPins) {
  // Use the provided groupedPins array or start with an empty array
  let result = Array.isArray(groupedPins) ? groupedPins : [];

  try {
    // Check if gpio_ctxt and gpioPad with port and index exist
    if (
      gpio_ctxt &&
      gpio_ctxt.gpioPad &&
      typeof gpio_ctxt.gpioPad.port !== "undefined" &&
      typeof gpio_ctxt.gpioPad.index !== "undefined"
    ) {
      const port = gpio_ctxt.gpioPad.port;
      const index = gpio_ctxt.gpioPad.index;

      // Try to find an existing entry for this port
      let portEntry = result.find((entry) => entry.port === port);

      if (portEntry) {
        // Add the pin index if not already present
        if (!portEntry.pins.includes(index)) {
          portEntry.pins.push(index);
          // Sort the pins array after adding
          portEntry.pins.sort((a, b) => a - b);
        }
      } else {
        // Create a new entry for this port
        result.push({ port: port, pins: [index] });
      }
    }
    // If port or index is missing, do nothing (skip this gpio_ctxt)
  } catch (e) {
    console.log(`[ERROR] helper_gpio_group_pins_by_port: ${e}`);
  }

  return result;
}

module.exports = {
  helper_gpio_retrieve_exti_object,

  helper_gpio_get_gpioconfig_object,

  helper_gpio_get_gpioconfig_standalone_object,

  helper_gpio_create_aliases,

  helper_gpio_add_pad_right,

  helper_gpio_group_pins_by_port,
};
