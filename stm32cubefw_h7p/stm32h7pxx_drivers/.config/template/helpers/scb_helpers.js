/**
 * @file CORTEX/MPU Helpers functions to provide service to the HAL components
 * @author GPM Application Team
 * @license
 * Copyright (c) 2025 STMicroelectronics.
 * All rights reserved.
 *
 * This software is licensed under terms that can be found in the LICENSE file
 * in the root directory of this software component.
 * If no LICENSE file comes with this software, it is provided AS-IS.
 */

/**
 * @brief Generate SCB fault disable flags string based on FaultManagement object and driver level.
 *
 * @param {object} faultManagement  Object with boolean properties EnableUsageFault, EnableBusFault, etc.
 * @param {string} driverLevel      Driver level string: 'LL' or 'HAL'.
 *
 * @returns {string} Bitwise OR '|' joined string of disable flags, or 'NONE' if all faults are enabled.
 *
 * @note
 * - Fault enabled = true means no disable flag.
 * - Fault disabled = false means disable flag should be set.
 * - The returned string can be used directly in C code to configure SCB fault enable bits.
 */
function helper_cortex_scb_get_enable_fault(faultManagement, driverLevel) {
  console.log(`[INFO] helper_cortex_scb_get_enable_fault`);

  try {
    if (typeof faultManagement !== 'object' || faultManagement === null) {
      console.log(`[WARN] helper_cortex_scb_get_enable_fault: invalid input`);
      return '';
    }

    if (typeof driverLevel !== 'string' || (driverLevel.toUpperCase() !== 'LL' && driverLevel.toUpperCase() !== 'HAL')) {
      throw new Error("Invalid or missing driverLevel argument: expected 'LL' or 'HAL'");
    }

    // Define disable flags map for LL driver
    const disableFlagsMapLL = {
      EnableUsageFault:         'SCB_SHCSR_USGFAULTENA_Msk',
      EnableBusFault:           'SCB_SHCSR_BUSFAULTENA_Msk',
      EnableMemManagementFault: 'SCB_SHCSR_MEMFAULTENA_Msk',
    };

    // Define disable flags map for HAL driver (example placeholders, adjust as needed)
    const disableFlagsMapHAL = {
      EnableUsageFault:         'HAL_CORTEX_SCB_USAGE_FAULT',
      EnableBusFault:           'HAL_CORTEX_SCB_BUS_FAULT',
      EnableMemManagementFault: 'HAL_CORTEX_SCB_MEM_MANAGEMENT_FAULT',
    };

    // Select map based on driverLevel argument (case-insensitive)
    let disableFlagsMap;
    switch (driverLevel.toUpperCase()) {
      case 'HAL':
        disableFlagsMap = disableFlagsMapHAL;
        break;
      case 'LL':
      default:
        disableFlagsMap = disableFlagsMapLL;
        break;
    }

    let disableFlags = [];

    // If fault is disabled (false), set the corresponding disable flag
    for (const [key, flag] of Object.entries(disableFlagsMap)) {
      if (faultManagement[key] === false) {
        disableFlags.push(flag);
      }
    }

    if (disableFlags.length === 0) {
      return 'NONE';
    }

    const result = disableFlags.join(' | ');
    console.log(`[INFO] helper_cortex_scb_get_enable_fault: result = ${result}`);
    return result;

  } catch (e) {
    console.log(`[ERROR] helper_cortex_scb_get_enable_fault: ${e}`);
    return '';
  }
}

module.exports = {
  helper_cortex_scb_get_enable_fault
};
