/**
 * Return if SW component has been enabled in the project (or at least its dependancies)
 * @param {object} used_components used components returned by SWProjectAPI.getUsedComponents getter
 * @param {string} component component to be check
 */
 function helper_filex_if_component_is_enabled(used_components, component) {
  let result = 0;
  try {
    used_components.forEach((comp) => {
      if (
        comp["cgroup"] === "FileX" &&
        comp["csub"].toUpperCase() === component.toUpperCase()
      ) {
        result = 1;
        return;
      }
    });
  } catch (e) {
    console.error(`[ERROR] helper_filex_if_component_is_enabled: ${e}`);
  }
  return result;
}
/**
 * Return if SW component has been enabled in the project (or at least its dependancies)
 * @note  use hal_conf.h for USE_HAL_PPP_MODULE
 * @param {object} used_components used components returned by SWProjectAPI.getUsedComponents getter
 * @param {string} component component to be check
 */
 function helper_if_component_HAL_is_enabled(used_components, component) {
  let result = 0;
  try {
    used_components.forEach((comp) => {
      if (
        (comp["cgroup"] === "STM32 HAL" || comp["cgroup"] === "STM32 HAL DRIVERS CORE") &&
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
 * Return if SW component has been enabled in the project (or at least its dependancies)
 * @param {object} used_components used components returned by SWProjectAPI.getUsedComponents getter
 * @param {string} component component to be check
 */
 function helper_if_component_os_is_enabled(used_components, component) {
  let result = 0;
  try {
    used_components.forEach((comp) => {
      if (
        comp["cgroup"] === "FreeRTOS" &&
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



module.exports = {
  helper_filex_if_component_is_enabled,
  helper_if_component_HAL_is_enabled,
  helper_if_component_os_is_enabled,
};
