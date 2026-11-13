const plugins_list = [
  {
    "id": 0,
    "name": "FFT 2048",
    "features": {
      "supported_crom_cram": [
          {"crom": "1.1.10", "cram": "1.6"},
          {"crom": "2.1.4", "cram": "1.0"}
      ],
      "size": "1kB"
    }
  },
  {
    "id": 1,
    "name": "Audio analysis",
    "features": {
      "supported_crom_cram": [
          {"crom": "2.1.4", "cram": "1.0"}
        ],
      "size": "2kB"
    }
  },
  {
    "id": 2,
    "name": "PID filter",
    "features": {
      "supported_crom_cram": [
          {"crom": "1.1.10", "cram": "1.6"}
      ],
      "size": "3kB"
    }
  },
  {
    "id": 3,
    "name": "Matrix convolution",
    "features": {
      "supported_crom_cram": [
          {"crom": "2.1.4", "cram": "1.0"}
        ],
      "size": "1kB"
    }
  }
];


/**
 * Determines if the provided string contains the word 'HSP'.
 * @param {string} inputParameter - The string to inspect.
 * @returns {boolean} - Returns true if 'HSP' is found in the string, otherwise false.
 */
function helper_hsp_engine_is_hsp_instance(inputParameter) {
  if (typeof inputParameter?.selection !== 'string') {
    return false;
  }

  if (inputParameter.selection.includes('HSP')) {
    return true;
  }
  return false;
}

/**
 * Gets the plugins available for the specified CROM and CRAM versions.
 * @param {string} crom_version - The CROM version.
 * @param {string} cram_version - The CRAM version.
 * @returns {Array} - The available plugins for the specified CROM and CRAM versions.
 */
function helper_hsp_get_plugins_list(crom_version, cram_version) {
  try {
    console.info(`helper_get_plugins_list: crom_version=${crom_version}, cram_version=${cram_version}`);

    const available_plugins = plugins_list.filter(plugin =>
      plugin.features.supported_crom_cram.some(
        feature => feature.crom === crom_version && feature.cram === cram_version
      )
    );

    console.info(`helper_get_plugins_list: available_plugins=${JSON.stringify(available_plugins)}`);
    return available_plugins;
  } catch (error) {
    console.error(`helper_get_plugins_list: ${error}`);
    return [];
  }
}

/**
 * Safely gets the hardware IP description for the given IP name, returning
 * undefined instead of throwing when no matching peripheral is found.
 * @param {object} peripheralsResourceManagerAPI - The peripherals resource manager API.
 * @param {string} ip_name - The IP name to look up (e.g. "CM7").
 * @returns {object|undefined} - The hardware IP description, or undefined if not found.
 */
function helper_hsp_engine_get_hardware_ip_description(peripheralsResourceManagerAPI, ip_name) {
  try {
    return peripheralsResourceManagerAPI.getHardwareIpDescription(ip_name);
  } catch (error) {
    console.error(`helper_hsp_engine_get_hardware_ip_description: ${error}`);
    return undefined;
  }
}

module.exports = {
  helper_hsp_engine_is_hsp_instance,
  helper_hsp_get_plugins_list,
  helper_hsp_engine_get_hardware_ip_description,
};
