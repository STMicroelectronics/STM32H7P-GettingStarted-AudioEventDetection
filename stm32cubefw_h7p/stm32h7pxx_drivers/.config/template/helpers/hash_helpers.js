/**
 * @file Helpers functions used for HASH SW component
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
 * Convert HEX String to Vector
 * @param {string} inputString - The input string containing hexadecimal digits.
 * @returns {string} - The input string split into bytes (2 hexadecimal digits),
 *                     each prefixed with '0x' and joined by commas.
 */
function helper_hash_string_to_hex(inputString) {
    try {
        console.log(`[INFO] helper_hash_string_to_hex: Input String=${inputString}`);

        if (typeof inputString !== 'string') {
            console.log('[ERROR] Input is not a valid string');
            return '';
        }

        // Ensure the input string has an even number of characters (pad with 0 if necessary)
        if (inputString.length % 2 !== 0) {
            inputString = '0' + inputString;
        }

        // Check if the input is a valid hexadecimal string
        if (!/^[0-9a-fA-F]+$/.test(inputString)) {
            console.log('[ERROR] Input is not a valid hexadecimal string');
            return '';
        }

        // Split the string into bytes (2 hexadecimal characters each)
        const bufferString = inputString
            .match(/.{1,2}/g) // Match every 2 characters
            .map(byte => `0x${byte.toUpperCase()}`) // Convert to uppercase and prefix with '0x'
            .join(', ');

        return bufferString;

    } catch (e) {
        console.log(`[ERROR] helper_hash_string_to_hex: ${e}`);
        return '';
    }
}

/**
 * Calculate the size of the input key in bytes.
 * @param {string} inputString - The input key, either as a regular string or a hexadecimal string.
 * @returns {number} - The size of the input key in bytes.
 */
function helper_hash_calculatekeysize(inputString) {
    try {
        console.log(`[INFO] helper_hash_calculatekeysize: Input String=${inputString}`);

        if (typeof inputString !== 'string') {
            throw new Error("Input must be a string.");
        }

        let keySize;

        // Check if the input is a valid hexadecimal string
        if (/^[0-9a-fA-F]+$/.test(inputString)) {
            // Ensure the input string has an even number of characters (pad with 0 if necessary)
            if (inputString.length % 2 !== 0) {
                inputString = '0' + inputString;
            }

            // Calculate the size for a hexadecimal string
            keySize = inputString.length / 2;
        } else {
            // Calculate the size for a regular string
            keySize = new TextEncoder().encode(inputString).length;
        }

        return keySize;

    } catch (e) {
        console.log(`[ERROR] helper_hash_calculatekeysize: ${e}`);
        throw e;
    }
}

module.exports = {
    helper_hash_string_to_hex,

    helper_hash_calculatekeysize,
}