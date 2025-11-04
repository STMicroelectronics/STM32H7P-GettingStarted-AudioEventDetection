/**
 * Return if SW component has been enabled in the project (or at least its dependancies)
 * @param {object} used_components used components returned by SWProjectAPI.getUsedComponents getter
 * @param {string} component component to be check
 */
function helper_USBX_Class_Selected(used_components, component) {
  let result = 0;
  try {
    used_components.forEach((comp) => {
      if (
        comp["cgroup"] === "STM32CubeMX2 Codegen" &&
        comp["csub"].toUpperCase() === component.toUpperCase()
      ) {
        result = 1;
        return;
      }
    });
  } catch (e) {
    console.error(`[ERROR] usbx_helpers: ${e}`);
  }
  return result;
}

function helper_USBX_Core_is_enabled(used_components, component) {
  let result = 0;
  try {
    used_components.forEach((comp) => {
      if (
        comp["cgroup"] === "USBX Core" &&
        comp["csub"].toUpperCase() === component.toUpperCase()
      ) {
        result = 1;
        return;
      }
    });
  } catch (e) {
    console.error(`[ERROR] usbx_helpers: ${e}`);
  }
  return result;
}

function helper_USBX_Controllers_is_enabled(used_components, component) {
  let result = 0;
  try {
    used_components.forEach((comp) => {
      if (
        comp["cgroup"] === "USBX Controllers Driver" &&
        comp["csub"].toUpperCase() === component.toUpperCase()
      ) {
        result = 1;
        return;
      }
    });
  } catch (e) {
    console.error(`[ERROR] usbx_helpers: ${e}`);
  }
  return result;
}

module.exports = {
  helper_USBX_Class_Selected,
  helper_USBX_Core_is_enabled,
  helper_USBX_Controllers_is_enabled,
};
