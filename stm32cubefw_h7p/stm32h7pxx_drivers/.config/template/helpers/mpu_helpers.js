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
 * Returns the string representation of the numeric or symbolic value corresponding
 * to a given HAL Cortex MPU macro name, with all shift expressions pre-evaluated.
 *
 * If the hal_value matches "REGION_x" or "ATTR_x" where x is a number, returns x as string.
 *
 * @param   {string} hal_value - The HAL macro name as a string
 * @returns {string|undefined} - String representing the numeric value or symbolic macro
 */
function helper_cortex_mpu_get_arm_cmsis_value(hal_value) {
  if (typeof hal_value !== "string") {
    return undefined;
  }

  // Check if hal_value matches REGION_x or ATTR_x pattern and return number x as string
  const regionMatch = hal_value.match(/^REGION_(\d+)$/);
  if (regionMatch) {
    return regionMatch[1];
  }
  const attrMatch = hal_value.match(/^ATTR_(\d+)$/);
  if (attrMatch) {
    return attrMatch[1];
  }

  const baseMap = {
    "HAL_CORTEX_MPU_ACCESS_FAULT_ALL": "0x00",
    "HAL_CORTEX_MPU_ACCESS_FAULT_ONLY_PRIV": "MPU_CTRL_PRIVDEFENA_Msk",
    "HAL_CORTEX_MPU_HARDFAULT_NMI_DISABLE": "0x00",
    "HAL_CORTEX_MPU_HARDFAULT_NMI_ENABLE": "MPU_CTRL_HFNMIENA_Msk",
    "HAL_CORTEX_MPU_EXECUTION_ATTR_DISABLE": "0x1",
    "HAL_CORTEX_MPU_EXECUTION_ATTR_ENABLE": "0x0",
    "HAL_CORTEX_MPU_DISABLED": "0x00",
    "HAL_CORTEX_MPU_ENABLED": "0x01",
    "HAL_CORTEX_MPU_REGION_DISABLED": "0x00",
    "HAL_CORTEX_MPU_REGION_ENABLED": "0x01",
    "HAL_CORTEX_MPU_SUB_REGION_ENABLE_ALL": "0x00"
  };

  const regionSizeOrMemAttrMap = {
    "HAL_CORTEX_MPU_REGION_SIZE_32B": "0x04",
    "HAL_CORTEX_MPU_REGION_SIZE_64B": "0x05",
    "HAL_CORTEX_MPU_REGION_SIZE_128B": "0x06",
    "HAL_CORTEX_MPU_REGION_SIZE_256B": "0x07",
    "HAL_CORTEX_MPU_REGION_SIZE_512B": "0x08",
    "HAL_CORTEX_MPU_REGION_SIZE_1KB": "0x09",
    "HAL_CORTEX_MPU_REGION_SIZE_2KB": "0x0A",
    "HAL_CORTEX_MPU_REGION_SIZE_4KB": "0x0B",
    "HAL_CORTEX_MPU_REGION_SIZE_8KB": "0x0C",
    "HAL_CORTEX_MPU_REGION_SIZE_16KB": "0x0D",
    "HAL_CORTEX_MPU_REGION_SIZE_32KB": "0x0E",
    "HAL_CORTEX_MPU_REGION_SIZE_64KB": "0x0F",
    "HAL_CORTEX_MPU_REGION_SIZE_128KB": "0x10",
    "HAL_CORTEX_MPU_REGION_SIZE_256KB": "0x11",
    "HAL_CORTEX_MPU_REGION_SIZE_512KB": "0x12",
    "HAL_CORTEX_MPU_REGION_SIZE_1MB": "0x13",
    "HAL_CORTEX_MPU_REGION_SIZE_2MB": "0x14",
    "HAL_CORTEX_MPU_REGION_SIZE_4MB": "0x15",
    "HAL_CORTEX_MPU_REGION_SIZE_8MB": "0x16",
    "HAL_CORTEX_MPU_REGION_SIZE_16MB": "0x17",
    "HAL_CORTEX_MPU_REGION_SIZE_32MB": "0x18",
    "HAL_CORTEX_MPU_REGION_SIZE_64MB": "0x19",
    "HAL_CORTEX_MPU_REGION_SIZE_128MB": "0x1A",
    "HAL_CORTEX_MPU_REGION_SIZE_256MB": "0x1B",
    "HAL_CORTEX_MPU_REGION_SIZE_512MB": "0x1C",
    "HAL_CORTEX_MPU_REGION_SIZE_1GB": "0x1D",
    "HAL_CORTEX_MPU_REGION_SIZE_2GB": "0x1E",
    "HAL_CORTEX_MPU_REGION_SIZE_4GB": "0x1F",
  };

  const memAttrMap = {
    "HAL_CORTEX_MPU_SO_MEM_SHAREABLE": "0x00000000",
    "HAL_CORTEX_MPU_DEVICE_MEM_SHAREABLE": "0x00010000",
    "HAL_CORTEX_MPU_NORMAL_MEM_NSHAREABLE_IO_WT_NWA": "0x00020000",
    "HAL_CORTEX_MPU_NORMAL_MEM_NSHAREABLE_IO_WB_NWA": "0x00030000",
    "HAL_CORTEX_MPU_NORMAL_MEM_SHAREABLE_IO_WT_NWA": "0x00060000",
    "HAL_CORTEX_MPU_NORMAL_MEM_SHAREABLE_IO_WB_NWA": "0x00070000",
    "HAL_CORTEX_MPU_NORMAL_MEM_NSHAREABLE_IO_NCACHEABLE": "0x00080000",
    "HAL_CORTEX_MPU_NORMAL_MEM_SHAREABLE_IO_NCACHEABLE": "0x000C0000",
    "HAL_CORTEX_MPU_NORMAL_MEM_NSHAREABLE_IO_WB_RWA": "0x000B0000",
    "HAL_CORTEX_MPU_NORMAL_MEM_SHAREABLE_IO_WB_RWA": "0x000F0000",
    "HAL_CORTEX_MPU_DEVICE_MEM_NSHAREABLE": "0x00100000",
  };

  const regionAccessAttrMap = {
    "HAL_CORTEX_MPU_REGION_ALL_RW_FAULT": "0x00",
    "HAL_CORTEX_MPU_REGION_ONLY_PRIV_RW": "0x01",
    "HAL_CORTEX_MPU_REGION_NPRIV_W_FAULT": "0x02",
    "HAL_CORTEX_MPU_REGION_ALL_RW": "0x03",
    "HAL_CORTEX_MPU_REGION_ONLY_PRIV_RO": "0x05",
    "HAL_CORTEX_MPU_REGION_ALL_RO": "0x06",
  };


  const combinedMap = {
    ...baseMap,
    ...regionSizeOrMemAttrMap,
    ...memAttrMap,
    ...regionAccessAttrMap,
  };

  return combinedMap[hal_value];
}



/**
 * @brief Retrieve the list of MPU attributes actually used by regions.
 *
 * @param {Array<object>} regions     Array of MPU region objects, each potentially referencing an attribute number.
 * @param {Array<object>} attributes  Array of all attribute objects.
 *
 * @returns {Array<object>} Filtered array of attribute objects that are referenced by at least one used region.
 *
 * @note
 * - Only regions with 'use_region' set to true are considered.
 * - Attributes not referenced by any region are excluded.
 * - Returned attributes retain all their original properties for code generation.
 *
 * Usage:
 * - Use the returned filtered attributes to generate MPU attribute configuration code.
 */
function helper_cortex_mpu_get_used_attributes(regions, attributes) {
  console.log(`[INFO] helper_cortex_mpu_get_used_attributes`);

  let filteredAttributes = [];

  try {
    console.log(`[INFO] helper_cortex_mpu_get_used_attributes: regions=${JSON.stringify(regions)}`);

    // Collect unique attribute numbers referenced by used regions
    const usedAttributeNumbers = new Set();

    regions.forEach(region => {
      if (region.use_region && region.AttributeNumber !== undefined && region.AttributeNumber !== null) {
        usedAttributeNumbers.add(region.AttributeNumber);
      }
    });

    // Convert to sorted array of attribute keys matching '_foreignKey' format
    const usedKeys = Array.from(usedAttributeNumbers)
      .sort((a, b) => a - b)
      .map(num => `ATTR_${num}`);

    console.log(`[INFO] helper_cortex_mpu_get_used_attributes: usedKeys=${JSON.stringify(usedKeys)}`);

    // Filter attributes to only those used by regions
    filteredAttributes = attributes.filter(attr => usedKeys.includes(attr._foreignKey));

  } catch (e) {
    console.log(`[ERROR] helper_cortex_mpu_get_used_attributes: ${e}`);
  }

  console.log(`[INFO] helper_cortex_mpu_get_used_attributes: filteredAttributes=${JSON.stringify(filteredAttributes)}`);

  return filteredAttributes;
}

/**
 * @brief Compute the address range title of a MPU subregion.
 *
 * @param {string|number} regionSize        Region size as string (e.g., "HAL_CORTEX_MPU_REGION_SIZE_256B") or numeric bytes.
 * @param {number|string} baseAddress       Base address of the MPU region (number or hex string).
 * @param {number} subregionIndex           Subregion index (1 to 8).
 *
 * @returns {string} Title string describing subregion address range.
 *
 * @note
 * - Assumes valid inputs: region size >= 256 bytes, subregionIndex in [1..8].
 * - The region is divided into 8 equal subregions.
 * - Subregion index 1 corresponds to the lowest address subregion.
 * - Base address can be a number or hex string (e.g., "0x20000000").
 */
function helper_cortex_mpu_get_subregion_title(regionSize, baseAddress, subregionIndex) {
  try {
    console.log(
      `[INFO] helper_cortex_mpu_get_subregion_title called with regionSize=${regionSize}, ` +
      `subregionIndex=${subregionIndex}, baseAddress=${baseAddress}`
    );

    // Map from region size define string to numeric bytes
    const sizeMap = {
      "HAL_CORTEX_MPU_REGION_SIZE_256B": 256,
      "HAL_CORTEX_MPU_REGION_SIZE_512B": 512,
      "HAL_CORTEX_MPU_REGION_SIZE_1KB": 1024,
      "HAL_CORTEX_MPU_REGION_SIZE_2KB": 2048,
      "HAL_CORTEX_MPU_REGION_SIZE_4KB": 4096,
      "HAL_CORTEX_MPU_REGION_SIZE_8KB": 8192,
      "HAL_CORTEX_MPU_REGION_SIZE_16KB": 16384,
      "HAL_CORTEX_MPU_REGION_SIZE_32KB": 32768,
      "HAL_CORTEX_MPU_REGION_SIZE_64KB": 65536,
      "HAL_CORTEX_MPU_REGION_SIZE_128KB": 131072,
      "HAL_CORTEX_MPU_REGION_SIZE_256KB": 262144,
      "HAL_CORTEX_MPU_REGION_SIZE_512KB": 524288,
      "HAL_CORTEX_MPU_REGION_SIZE_1MB": 1048576,
      "HAL_CORTEX_MPU_REGION_SIZE_2MB": 2097152,
      "HAL_CORTEX_MPU_REGION_SIZE_4MB": 4194304,
      "HAL_CORTEX_MPU_REGION_SIZE_8MB": 8388608,
      "HAL_CORTEX_MPU_REGION_SIZE_16MB": 16777216,
      "HAL_CORTEX_MPU_REGION_SIZE_32MB": 33554432,
      "HAL_CORTEX_MPU_REGION_SIZE_64MB": 67108864,
      "HAL_CORTEX_MPU_REGION_SIZE_128MB": 134217728,
      "HAL_CORTEX_MPU_REGION_SIZE_256MB": 268435456,
      "HAL_CORTEX_MPU_REGION_SIZE_512MB": 536870912,
      "HAL_CORTEX_MPU_REGION_SIZE_1GB": 1073741824,
      "HAL_CORTEX_MPU_REGION_SIZE_2GB": 2147483648,
      "HAL_CORTEX_MPU_REGION_SIZE_4GB": 4294967296
    };

    // Convert regionSize to numeric bytes if string
    let sizeBytes = typeof regionSize === "string" ? (sizeMap[regionSize] || 0) : regionSize;

    // Parse baseAddress if string (hex)
    let baseAddrNum = typeof baseAddress === "string"
      ? (isNaN(Number(baseAddress)) ? parseInt(baseAddress, 16) : Number(baseAddress))
      : baseAddress;

    // The region is divided into 8 equal subregions.
    const subregionSize = sizeBytes / 8;

    // Subregion index 1 corresponds to the lowest address subregion.
    const startAddr = baseAddrNum + (subregionIndex - 1) * subregionSize;
    const endAddr = startAddr + subregionSize - 1;

    // Format addresses as 0xXXXXXXXX uppercase hex, padded to 8 digits
    const toHex = (num) => "0x" + num.toString(16).toUpperCase().padStart(8, "0");

    return `Subregion ${subregionIndex}: from ${toHex(startAddr)} to ${toHex(endAddr)}`;

  } catch (e) {
    console.log(`[ERROR] helper_cortex_mpu_get_subregion_title: ${e}`);
    return `Error computing subregion title`;
  }
}

/**
 * @brief Generate MPU subregion disable flags string or hex number based on enabled/disabled subregions.
 *
 * @param {object} subregions  Object with boolean properties EnableSubregion1..8 indicating enabled subregions.
 * @param {string} driverLayer 'HAL' to return macros string, 'LL' to return hex number.
 *
 * @returns {string|number}
 * - For 'HAL': Bitwise OR '|' joined string of disable flags, or HAL_CORTEX_MPU_SUB_REGION_DISABLE_ALL if all disabled.
 * - For 'LL': Hexadecimal number representing disabled subregions bits (bit 0 for Subregion1, etc.).
 *
 * @note
 * - Subregion enabled = false means disabled flag should be set.
 * - The returned value can be used directly in C code to configure MPU subregions.
 */
function helper_cortex_mpu_get_disable_subregion(subregions, driverLayer) {
  console.log(`[INFO] helper_cortex_mpu_get_disable_subregion`);

  try {
    // Validate driverLayer argument
    if (driverLayer !== 'HAL' && driverLayer !== 'LL') {
      console.log(`[WARN] helper_cortex_mpu_get_disable_subregion: invalid driverLayer '${driverLayer}'`);
      return '';
    }

    if (typeof subregions !== 'object' || subregions === null) {
      console.log(`[WARN] helper_cortex_mpu_get_disable_subregion: invalid subregions input`);
      return '';
    }

    const disableFlagsMap = {
      EnableSubregion1: 'HAL_CORTEX_MPU_SUB_REGION_DISABLE_0',
      EnableSubregion2: 'HAL_CORTEX_MPU_SUB_REGION_DISABLE_1',
      EnableSubregion3: 'HAL_CORTEX_MPU_SUB_REGION_DISABLE_2',
      EnableSubregion4: 'HAL_CORTEX_MPU_SUB_REGION_DISABLE_3',
      EnableSubregion5: 'HAL_CORTEX_MPU_SUB_REGION_DISABLE_4',
      EnableSubregion6: 'HAL_CORTEX_MPU_SUB_REGION_DISABLE_5',
      EnableSubregion7: 'HAL_CORTEX_MPU_SUB_REGION_DISABLE_6',
      EnableSubregion8: 'HAL_CORTEX_MPU_SUB_REGION_DISABLE_7'
    };

    if (driverLayer === 'LL') {
      // For LL, build a hex number where each bit corresponds to a disabled subregion
      let hexValue = 0;
      let index = 0;

      for (const key of Object.keys(disableFlagsMap)) {
        if (subregions[key] === false) {
          hexValue |= (1 << index);
        }
        index++;
      }

      return hexValue;
    } else {
      // For HAL, return string macros joined by '|'
      let disabledFlags = [];

      for (const [key, flag] of Object.entries(disableFlagsMap)) {
        if (subregions[key] === false) {
          disabledFlags.push(flag);
        }
      }

      if (disabledFlags.length === 8) {
        return 'HAL_CORTEX_MPU_SUB_REGION_DISABLE_ALL';
      }

      return disabledFlags.join(' | ');
    }

  } catch (e) {
    console.log(`[ERROR] helper_cortex_mpu_get_disable_subregion: ${e}`);
    return '';
  }
}

module.exports = {
  helper_cortex_mpu_get_arm_cmsis_value,
  helper_cortex_mpu_get_subregion_title,
  helper_cortex_mpu_get_disable_subregion
};
