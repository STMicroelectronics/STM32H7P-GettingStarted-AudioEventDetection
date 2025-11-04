/**
 * @file Helpers functions used for FMAC SW component
 * @author GPM Application Team
 * @license
$LICENSE

/**
 * Autofill the base address of the buffer (e.g. X2) Once base address and size of the previous buffer is configured (e.g. X1).
 * @param {string} previous_base - The input base address of the previous buffer.
 * @param {integer} previous_size - The input size of the previous buffer.
 * @returns {string} - Returns the autofilled base address of the next buffer.
 */

function helper_fmac_autofill_base(previous_base, previous_size) {
    try {
        let actuel_base;
        actuel_base = previous_base + previous_size;
        console.log(`[INFO] helper_fmac_autofill_base: ${actuel_base}`);
        return previous_base;
    } catch (e) {
    console.log(`[ERROR] helper_fmac_autofill_base: ${e}`);
    return {};
    }
}

module.exports = {
    helper_fmac_autofill_base
}