/**
 * Check if a number is a power of two.
 *
 * @param {number} n - The number to check.
 * @returns {boolean} - Returns `true` if the number is a power of two, otherwise `false`.
 */
function isPowerOfTwo(n) {
  if (n <= 0) {
    return false;
  }
  return (n & (n - 1)) === 0;
}

/**
 * Return if SW component has been enabled in the project (or at least its dependencies)
 * @param {object} used_components used components returned by SWProjectAPI.getUsedComponents getter
 * @param {string} component component to be check
 */
 function helper_levelx_if_component_is_enabled(used_components, component) {
  let result = 0;
  try {
    used_components.forEach((comp) => {
      if (
        comp["cgroup"] === "LevelX" &&
        comp["csub"].toUpperCase() === component.toUpperCase()
      ) {
        result = 1;
        return;
      }
    });
  } catch (e) {
    console.error(`[ERROR] helper_levelx_if_component_is_enabled: ${e}`);
  }
  return result;
}

/**
 * Return if SW component has been enabled in the project (or at least its dependencies)
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
  isPowerOfTwo,
  helper_levelx_if_component_is_enabled,
  helper_if_component_os_is_enabled,  
};