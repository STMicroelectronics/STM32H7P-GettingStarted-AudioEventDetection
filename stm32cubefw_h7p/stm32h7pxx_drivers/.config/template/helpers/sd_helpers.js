/**
 * Calculate the SD output frequency based on kernel clock frequency and user input clock values
 * @note  This api is used directly in the sd_parameters.json in advanced view
 * @param {integer} kernel_clock_frequency System clock frequency in Hz
 * @param {integer} clock_freq clock frequency set by the user
 * @returns {integer} SD output frequency in Hz
 */
function helper_sd_compute_frequency(
    kernel_clock_frequency,
    clock_freq,
  ) {
    let result = 0;
    let clock_div = 0;
    let output_frequency = 0;
    try {
      console.log(
        `[INFO] helper_sd_compute_frequency: sd_configuration=${JSON.stringify(kernel_clock_frequency)}`
      );
      
      if ((2 * clock_freq) > kernel_clock_frequency)
      {
        clock_div = 0;
        output_frequency = kernel_clock_frequency;
      }
      else
      {
        /* Calculate the actual timer frequency */
        clock_div = kernel_clock_frequency / (2 * clock_freq);
        clock_div = Math.floor(kernel_clock_frequency / (2 * clock_freq)) + (clock_div > Math.floor(clock_div) ? 1 : 0);
        /* Calculate the actual output frequency */
        output_frequency = kernel_clock_frequency / (2 * clock_div);
      }
      /* Return the output frequency */
      result = Math.floor(output_frequency);
    } catch (e) {
      console.log(`[ERROR] helper_sd_compute_frequency: ${e}`);
    }
    return result;
  }

module.exports = {

    helper_sd_compute_frequency,
};