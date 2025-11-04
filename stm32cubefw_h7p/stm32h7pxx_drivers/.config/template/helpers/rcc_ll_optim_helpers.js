/**
 * @file Helpers functions used to optimize the LL code in RCC
 * @author GPM Application Team
 * @license
 * Copyright (c) 2025 STMicroelectronics.
 * All rights reserved.
 *
 * This software is licensed under terms that can be found in the LICENSE file
 * in the root directory of this software component.
 * If no LICENSE file comes with this software, it is provided AS-IS.
 */

const LL_RCC_functions = {
  /* not available yet  */
};

/**
 * Get the LUT table to optimize the LL code
 * @returns LUT table based on the IP version
 */
function helper_rcc_get_lut_table() {
  let selectedTable = LL_RCC_functions;
  return selectedTable;
}

module.exports = {
  helper_rcc_get_lut_table,
};
