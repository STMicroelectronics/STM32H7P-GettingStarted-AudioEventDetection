/**
 * @file Helpers functions used for HRTIM SW component
 * @author GPM Application Team
 * @license
 * Copyright (c) 2024 STMicroelectronics.
 * All rights reserved.
 *
 * This software is licensed under terms that can be found in the LICENSE file
 * in the root directory of this software component.
 * If no LICENSE file comes with this software, it is provided AS-IS.
 */


/**
 * Get the list of timers supported by the HR-Timer
 * @param {integer} nb_slave_timers number of slave timers
 * @returns Array of timer descriptors
 */
function helper_hrtim_get_timers(nb_slave_timers) {
  const timers = [
    { name: "Timer M", type: "master" }
  ];
  try {
    //console.log(`[-INFO-] helper_hrtim_get_timers: nb_slave_timers=${nb_slave_timers}`);

    for (let itimer = 0; itimer < nb_slave_timers; itimer++) {
      const timer_name = `Timer ${String.fromCharCode(65 + itimer)}`;
      const slave_timer = {
        name: timer_name,
        type: "slave"
      };
      timers.push(slave_timer);
    }
  } catch (error) {
    console.log(`[ERROR] helper_hrtim_get_timers: ${error}`);
  }

  return timers;
}

/**
 * Get the list of output channels supported by the HR-Timer
 * @param {string} instance_name name of the HRTIM instance
 * @param {integer} nb_slave_timers number of slave timers
 * @returns Array of HR-Timer output channels
 */
function helper_hrtim_get_output_channels(instance_name, nb_slave_timers) {
  const output_channels = [];
  const timerNames = ["A", "B", "C", "D", "E", "F"];

  try {
    //console.log(`[INFO] helper_hrtim_get_output_channels: instance=${instance_name} nb_slave_timers=${nb_slave_timers}`);

    for (let i = 0; i < nb_slave_timers; i++) {
      const timer = `T${timerNames[i]}`;
      output_channels.push({ source: timer, name: `${instance_name}_CH${timerNames[i]}1` });
      output_channels.push({ source: timer, name: `${instance_name}_CH${timerNames[i]}2` });
    }
  } catch (error) {
    console.log(`[ERROR] helper_hrtim_get_output_channels: ${error}`);
  }

  return output_channels;
}

/**
 * Get the list of compare units supported by a slave timer
 * @param {string} timer_name master or slave timer
 * @returns Array of compare unit descriptors
 */
function helper_hrtim_get_compare_units(timer_name) {
  const compare_units = [
    {
      name: "Compare unit 1",
      features: {
        greater_than_comparison_mode: true,
        auto_delayed_mode: false,
        triggered_half_mode: false,
      }
    },
    {
      name: "Compare unit 2",
      features: {
        greater_than_comparison_mode: false,
        auto_delayed_mode: true,
        triggered_half_mode: true,
      }
    },
    {
      name: "Compare unit 3",
      features: {
        greater_than_comparison_mode: true,
        auto_delayed_mode: false,
        triggered_half_mode: false,
      }
    },
    {
      name: "Compare unit 4",
      features: {
        greater_than_comparison_mode: false,
        auto_delayed_mode: true,
        triggered_half_mode: false,
      }
    }
  ];

  try {
    //console.log(`[INFO] helper_hrtim_get_compare_units: timer_name=${timer_name}`);

    if (timer_name === "Timer M") {
      compare_units.forEach(unit => {
        unit.features.greater_than_comparison_mode = false;
        unit.features.auto_delayed_mode = false;
        unit.features.triggered_half_mode = false;
      });
    }

    //console.log(`[INFO] helper_hrtim_get_compare_units: compare_units=${JSON.stringify(compare_units)}`);
  } catch (error) {
    console.log(`[ERROR] helper_hrtim_get_compare_units: ${error}`);
  }

  return compare_units;
}

/**
 * Get the list of capture units supported by a slave timer
 * @returns Array of capture unit descriptors
 */
function helper_hrtim_get_capture_units() {
  const capture_units = [
    {
      name: "Capture unit 1"
    },
    {
      name: "Capture unit 2"
    }
  ];

  try {
    // console.log(`[INFO] helper_hrtim_get_capture_units`);

  } catch (error) {
    console.log(`[ERROR] helper_hrtim_get_capture_units: ${error}`);
  }

  return capture_units;
}

/**
 * Get the list of ADC triggers
 * @returns {object[]} Array of adc triggers descriptors
 */
function helper_hrtim_get_adc_tiggers() {
  const adc_triggers = [
    {
      name: "ADC trigger 1",
      number: 1,
      combined_sources: true
    },
    {
      name: "ADC trigger 2",
      number: 2,
      combined_sources: true
    },
    {
      name: "ADC trigger 3",
      number: 3,
      combined_sources: true
    },
    {
      name: "ADC trigger 4",
      number: 4,
      combined_sources: true
    },
    {
      name: "ADC trigger 5",
      number: 5,
      combined_sources: false
    },
    {
      name: "ADC trigger 6",
      number: 6,
      combined_sources: false
    },
    {
      name: "ADC trigger 7",
      number: 7,
      combined_sources: false
    },
    {
      name: "ADC trigger 8",
      number: 8,
      combined_sources: false
    },
    {
      name: "ADC trigger 9",
      number: 9,
      combined_sources: false
    },
    {
      name: "ADC trigger 10",
      number: 10,
      combined_sources: false
    }
  ];

  try {
    // console.log(`[INFO] helper_hrtim_get_adc_tiggers`);

  } catch (error) {
    console.log(`[ERROR] helper_hrtim_get_adc_tiggers: ${error}`);
  }

  return adc_triggers;
}

/**
 * Get the list of events counters supported by a slave timer as per hrtim version number.
 * @param {integer} version_number Version of the HRTIM preipheral
 * @returns Array of event counter descriptors
 */
function helper_hrtim_get_event_counters(version_number) {
  let event_counters;
  // console.log(`[INFO] helper_hrtim_get_event_counters version_number=${version_number}`);
  /*
   try {
      console.log(`[INFO] helper_hrtim_get_event_counters version_number=${version_number}`);
  
      if (version_number < 3) {
        event_counters = [
          { 
            name: "Event counter 1"
          },
          { 
            name: "Event counter 2"
          }
        ];
      } else {
        event_counters = [
          { 
            name: "Event counter A"
          },
          { 
            name: "Event counter B"
          }
        ];
      }
    } catch (error) {
      console.log(`[ERROR] helper_hrtim_get_event_counters: ${error}`);
    }
  */
  return event_counters;
}

/**
 * Format the source
 * @param {string} instance_name name of the HRTIM instance
 * @returns Array of HR-Timer output channels
 */
function helper_hrtim_get_output_set_reset_sources(set_reset_triggers) {

  try {
    // console.log(`[INFO] helper_hrtim_get_output_set_reset_sources: set_reset_triggers=${JSON.stringify(set_reset_triggers)}`);
  } catch (error) {
    console.log(`[ERROR] helper_hrtim_get_output_set_reset_sources: ${error}`);
  }

  return false;
}

/**
 * Identify the candidate interrupt requests based on the current HR-Timer configuration
 * @param {object} Timers configuration
 * @param {object} Burst mode configuration
 * @returns Array of HR-Timer interrupt request descriptors
 */
function helper_hrtim_get_hrtim_interrupt_requests(timers, burst_mode) {
  const interruptRequests = [
    {
      id: "FLT",
      name: "HRTIM global interrupts",
    }
  ];

  const timerTable = [
    { key: "Timer M", id: "Master", name: "Master timer interrupts" },
    { key: "Timer A", id: "Timer A", name: "Timer A interrupts" },
    { key: "Timer B", id: "Timer B", name: "Timer B interrupts" },
    { key: "Timer C", id: "Timer C", name: "Timer C interrupts" },
    { key: "Timer D", id: "Timer D", name: "Timer D interrupts" },
    { key: "Timer E", id: "Timer E", name: "Timer E interrupts" },
    { key: "Timer F", id: "Timer F", name: "Timer F interrupts" }
  ];

  try {
    // console.log(`[INFO] helper_hrtim_get_hrtim_interrupt_requests: timers=${JSON.stringify(timers)}, burst_mode=${JSON.stringify(burst_mode)}`);

    timerTable.forEach(timerEntry => {
      const timer = timers.Timers.find(t => t._foreignKey === timerEntry.key);
      if (timer && timer.use) {
        interruptRequests.push({
          id: timerEntry.id,
          name: timerEntry.name,
        });
      } else if (timerEntry.key === "Timer M" && burst_mode.use) {
        interruptRequests.push({
          id: "Master",
          name: "Master timer interrupts",
        });
      }
    });
  } catch (error) {
    console.log(`[ERROR] helper_hrtim_get_hrtim_interrupt_requests: ${error}`);
  }

  return interruptRequests;
}

/**
 * Check if the at least one GPIO must be configured
 * @param {object} inputs_outputs list of configured HRTIM I/Os
 * @returns true or false
 */
function helper_hrtim_need_at_least_one_gpio(inputs_outputs) {
  let result = true;/*false;*/
  let should_break = false;
  try {
    /*console.log(
      `[INFO] helper_hrtim_need_at_least_one_gpio: channels=${JSON.stringify(
        inputs_outputs
      )}`
    );*/
    if (inputs_outputs === undefined) {
      return false;
    }
    /*
    inputs_outputs.forEach((config_ch) => {
      if (should_break) return;
      result = tim_need_gpio(config_ch, config_ch._foreignKey);
      if (result) {
        should_break = true;
        return;
      }
    });
    */
  } catch (error) {
    console.log(`[ERROR] helper_hrtim_need_at_least_one_gpio: ${error}`);
  }
  //console.log(`[INFO] helper_hrtim_need_at_least_one_gpio: result=${result}`);
  return result;
}

/**
 * Check whether the timer is used
 * @param {string} timer_name name of the timer
 * @param {object} config_timers timers configuration array
 * @returns true or false
 */
function helper_hrtim_is_used_timer(timer_name, config_timers) {
  let isUsed = true;

  try {
    // console.log(`[+INFO+] helper_hrtim_is_used_timer: timer_name=${timer_name}, config_timers=${JSON.stringify(config_timers)}`);

    if (timer_name === undefined || config_timers === undefined) {
      return false;
    }

    const timersArray = config_timers.Timers;

    //console.log(`[++INFO++] helper_hrtim_is_used_timer: timersArray=${JSON.stringify(timersArray)}` );

    const timer = timersArray.find(timer => timer._foreignKey === timer_name);

    //console.log(`[+++INFO+++] helper_hrtim_is_used_timer: timer_name=${timer_name}, timer=${JSON.stringify(timer)}`); 
    if (timer) {
      //console.log(`[---INFO---] helper_hrtim_is_used_timer: timer=${timer._foreignKey}, isUsed=${timer.use}`);

      //const tmp = timer ? timer.use === true : false;
      //isUsed = timer.use;
      let tmp = false;
      tmp = timer.use;
      //console.log(`[-+-INFO-+-] helper_hrtim_is_used_timer: tmp=${tmp}`);
      return tmp;
    }
  } catch (error) {
    console.log(`[ERROR] helper_hrtim_is_used_timer: ${error}`);
  }

  //console.log(`[---INFO---] helper_hrtim_is_used_timer: timer_name=${timer_name}, isUsed=${isUsed}`);

  return isUsed;
}

function helper_hrtim_get_timing_unit(output_channel) {
  console.log(`[+INFO+] helper_hrtim_get_timing_unit: output_chanel=${output_channel}`);

  return true;
}

/**
 * Determine whether at least one resource is used
 * @param {object} resources resources array
 * @returns true or false
 */
function helper_hrtim_any_resource_used(resources) {
  let anyUsed = false;

  if (!resources || !Array.isArray(resources)) {
    return false;
  }

  try {
    //console.log(`[INFO] helper_hrtim_any_resource_used: resources=${JSON.stringify(resources)}`);

    anyUsed = resources.some(event => event.use);
  } catch (error) {
    console.log(`[ERROR] helper_hrtim_any_resource_used: ${error}`);
  }

  return anyUsed;
}

/**
 * Check whether the resource is used
 * @param {object} config resource configuration
 * @param {string} resource (output channel, external event, fault input or timer)
 * @returns true if the resource is used, false otherwise.
 */
function helper_hrtim_is_used_resource(config, resource) {
  let isUsed = false;

  try {
    // console.log(`[INFO] helper_hrtim_is_used_resource: config=${JSON.stringify(config)},  resource=${resource}`);

    if (resource === undefined || config === undefined) {
      return false;
    }

    const item = config.find(item => item._foreignKey === resource);

    if (item) {
      isUsed = item.use;
    }
  } catch (error) {
    console.log(`[ERROR] helper_hrtim_is_used_resource: ${error}`);
  }

  return isUsed;
}

/**
 * Determine whether at least one fault is enabled
 * @param {object} fault_inputs fault inputs array
 * @returns true or false
 */
function helper_hrtim_any_fault_input_enabled(fault_inputs) {
  let anyFaultInputEnabled = false;

  if (!fault_inputs || !Array.isArray(fault_inputs)) {
    return false;
  }

  try {
    //console.log(`[INFO] helper_hrtim_any_fault_input_enabled: fault_inputs=${JSON.stringify(fault_inputs)}`);

    anyFaultInputEnabled = fault_inputs.some(fault_input => fault_input.fault_input_config.enable);
  } catch (error) {
    console.log(`[ERROR] helper_hrtim_any_fault_input_enabled: ${error}`);
  }

  return anyFaultInputEnabled;
}

/**
 * Get the number of enabled fault inputs
 * @param {object} fault_inputs fault inputs array
 * @returns number of enabled fault inputs
 */
function helper_hrtim_get_enabled_fault_count(fault_inputs) {
  let enabledFaultInputsCount = 0;

  if (!fault_inputs || !Array.isArray(fault_inputs)) {
    return false;
  }

  try {
    //console.log(`[INFO] helper_hrtim_get_enabled_fault_count: fault_inputs=${JSON.stringify(fault_inputs)}`);

    enabledFaultInputsCount = fault_inputs.filter(fault_input => fault_input.fault_input_config && fault_input.fault_input_config.enable).length;
  } catch (error) {
    console.log(`[ERROR] helper_hrtim_get_enabled_fault_count: ${error}`);
  }

  return enabledFaultInputsCount;
}

/**
 * Get the number of locked fault inputs
 * @param {object} fault_inputs fault inputs array
 * @returns number of locked fault inputs
 */
function helper_hrtim_get_locked_fault_count(fault_inputs) {
  let lockedFaultInputsCount = 0;

  if (!fault_inputs || !Array.isArray(fault_inputs)) {
    return false;
  }

  try {
    //console.log(`[INFO] helper_hrtim_get_locked_fault_count: fault_inputs=${JSON.stringify(fault_inputs)}`);

    lockedFaultInputsCount = fault_inputs.filter(fault_input => fault_input.fault_input_config && faultInput.lock).length;
  } catch (error) {
    console.log(`[ERROR] helper_hrtim_get_locked_fault_count: ${error}`);
  }

  return lockedFaultInputsCount;
}

/**
 * Convert a timer name into a timer identifier
 * @param {string} timer name
 * @returns timer identifier
 */
function helper_hrtim_convert_timer(timer) {
  try {
    // console.log(`[INFO] helper_hrtim_convert_timer: timer=${timer}`);

    const timerMap = {
      "Timer M": "MASTER",
      "Timer A": "TIMA",
      "Timer B": "TIMB",
      "Timer C": "TIMC",
      "Timer D": "TIMD",
      "Timer E": "TIME",
      "Timer F": "TIMF"
    };

    return timerMap[timer];
  } catch (error) {
    console.log(`[ERROR] helper_hrtim_convert_timer: ${error}`);
    return "";
  }
}

/**
 * Extract the capture/compare unit number from the capture/compare string
 * @param {string} capture/compare unit name
 * @returns capture/compare unit identifier
 */
function helper_hrtim_extract_unit_number(cc_unit) {
  try {
    // console.log(`[INFO] helper_hrtim_extract_unit_number: cc_unit=${cc_unit}`);

    const match = cc_unit.match(/(?:Compare|Capture) unit (\d+)/);
    return match ? match[1] : '';
  } catch (error) {
    console.log(`[ERROR] helper_hrtim_extract_unit_number: ${error}`);
    return "";
  }
}

/**
 * Check whether the event can be used to set or reset the output
 * @param {string} Output channel
 * @param {string} event from timing unit
 * @returns true if the event can be usedto set or reset the output, false otherwise
 */
function helper_hrtim_is_event_relevant_to_output(output, event) {
  const lookupTable = {
    "CHA": ["TACMP1", "TACMP2", "TACMP3", "TACMP4", "TBCMP1", "TBCMP2", "TCCMP2", "TCCMP3", "TDCMP1", "TDCMP2", "TECMP3", "TECMP4", "TFCMP4"],
    "CHB": ["TACMP1", "TACMP2", "TBCMP1", "TBCMP2", "TBCMP3", "TBCMP4", "TCCMP3", "TCCMP4", "TDCMP3", "TDCMP4", "TECMP1", "TECMP2", "TFCMP3"],
    "CHC": ["TACMP2", "TACMP3", "TBCMP2", "TBCMP3", "TCCMP1", "TCCMP2", "TCCMP3", "TCCMP4", "TDCMP2", "TDCMP4", "TECMP3", "TECMP4", "TFCMP2"],
    "CHD": ["TACMP1", "TACMP4", "TBCMP2", "TBCMP4", "TCCMP4", "TDCMP1", "TDCMP2", "TDCMP3", "TDCMP4", "TECMP1", "TECMP4", "TFCMP1", "TFCMP3"],
    "CHE": ["TACMP4", "TBCMP3", "TBCMP4", "TCCMP1", "TCCMP2", "TDCMP1", "TDCMP2", "TECMP1", "TECMP2", "TECMP3", "TECMP4", "TFCMP3", "TFCMP4"],
    "CHF": ["TACMP3", "TBCMP1", "TBCMP4", "TCCMP1", "TCCMP4", "TDCMP3", "TDCMP4", "TECMP2", "TECMP3", "TFCMP1", "TFCMP2", "TFCMP3", "TFCMP4"]
  };
  let isRelevantEvent = false;

  try {
    // console.log(`[INFO] helper_hrtim_is_event_relevant_to_output: output=${output}, event=${event}`);

    const baseOutput = output.slice(0, 3);
    if (!lookupTable[baseOutput]) {
      return false;
    }

    isRelevantEvent = lookupTable[baseOutput].includes(event)
  } catch (error) {
    console.log(`[ERROR] helper_hrtim_is_event_relevant_to_output: ${error}`);
    return false;
  }

  return isRelevantEvent;
}

/**
 * Check whether the event can be used to trigger a capture fr a given timer
 * @param {string} Timing unit
 * @param {string} capture trigger source
 * @returns true if the event can be used to set or reset the output, false otherwise
 */
function helper_hrtim_is_event_relevant_to_capture(timer, event) {
  const lookupTable = {
    'Timer A': ['TA', 'CHA'],
    'Timer B': ['TB', 'CHB'],
    'Timer C': ['TC', 'CHC'],
    'Timer D': ['TD', 'CHD'],
    'Timer E': ['TE', 'CHE'],
    'Timer F': ['TF', 'CHF']
  };
  let isRelevantEvent = true;

  try {
    // console.log(`[INFO] helper_hrtim_is_event_relevant_to_capture: timer=${timer}, event=${event}`);

    if (lookupTable[timer]) {
      for (let pattern of lookupTable[timer]) {
        if (event.includes(pattern)) {
          isRelevantEvent = false;
          break;
        }
      }
    }
  } catch (error) {
    isRelevantEvent = false;
    console.log(`[ERROR] helper_hrtim_is_event_relevant_to_capture: ${error}`);
  }

  return isRelevantEvent;
}

/**
 * Check whether the blanking configuration can be used to filter an event at timing unit level
 * @param {string} timing unit
 * @param {string} blanking configuration
 * @returns true if the blanking configuration can be used, false otherwise
 */
function helper_hrtim_is_blanking_relevant_to_timer(timer, blanking) {
  const lookupTable = {
    'Timer A': ['TBRST_TBCMP1', 'TBRST_TBCMP4', 'CHB2', 'TCRST_TCCMP1', 'TCRST_TCCMP4', 'TFRST_TFCMP1', 'TDRST_TDCMP1', 'TERST_TECMP2'],
    'Timer B': ['TARST_TACMP1', 'TARST_TACMP4', 'CHA2', 'TCRST_TCCMP1', 'TCRST_TCCMP2', 'TFRST_TFCMP2', 'TDRST_TDCMP2', 'TERST_TECMP1'],
    'Timer C': ['TARST_TACMP2', 'TBRST_TBCMP1', 'TBRST_TBCMP4', 'TFRST_TFCMP1', 'TDRST_TDCMP1', 'TDRST_TDCMP4', 'CHD2', 'TERST_TECMP4'],
    'Timer D': ['TARST_TACMP1', 'TBRST_TBCMP2', 'TCRST_TCCMP1', 'TCRST_TCCMP2', 'CHC2', 'TERST_TECMP1', 'TERST_TECMP4', 'TFRST_TFCMP4'],
    'Timer E': ['TARST_TACMP2', 'TBRST_TBCMP1', 'TCRST_TCCMP1', 'TFRST_TFCMP4', 'CHF2', 'TDRST_TDCMP1', 'TDRST_TDCMP4', 'CHD2'],
    'Timer F': ['TARST_TACMP4', 'TBRST_TBCMP2', 'TCRST_TCCMP4', 'TDRST_TDCMP2', 'TDRST_TDCMP4', 'TERST_TECMP1', 'TERST_TECMP4', 'CHE2']
  };

  let isRelevantBlanking = false;

  try {
    // console.log(`[INFO] helper_hrtim_is_blanking_relevant_to_timer: timer=${timer}, blanking=${blanking}`);

    if (lookupTable.hasOwnProperty(timer)) {
      isRelevantBlanking = lookupTable[timer].includes(blanking);
    }
  } catch (error) {
    console.log(`[ERROR] helper_hrtim_is_blanking_relevant_to_timer: ${error}`);
  }

  return isRelevantBlanking;
}

/**
 * Check whether the windowing configuration can be used to filter an event at timing unit level
 * @param {string} timing unit
 * @param {string} windowing configuration
 * @returns true if the windowing configuration can be used, false otherwise
 */
function helper_hrtim_is_windowing_relevant_to_timer(timer, windowing) {
  const lookupTable = {
    'Timer A': ['TBRST_TBCMP2', 'TBCMP2_TBRST', 'TBCMP1_TBRST'],
    'Timer B': ['TARST_TACMP2', 'TACMP2_TARST', 'TACMP1_TARST'],
    'Timer C': ['TDRST_TDCMP2', 'TDCMP2_TDRST', 'TDCMP1_TDRST'],
    'Timer D': ['TCRST_TCCMP2', 'TCCMP2_TCRST', 'TCCMP1_TCRST'],
    'Timer E': ['TFRST_TFCMP2', 'TFCMP2_TFRST', 'TFCMP1_TFRST'],
    'Timer F': ['TERST_TECMP2', 'TECMP2_TERST', 'TECMP1_TERST']
  };

  let isRelevantWindowing = false;

  try {
    // console.log(`[INFO] helper_hrtim_is_windowing_relevant_to_timer: timer=${timer}, blanking=${windowing}`);

    if (lookupTable.hasOwnProperty(timer)) {
      isRelevantWindowing = lookupTable[timer].includes(windowing);
    }
  } catch (error) {
    console.log(`[ERROR] helper_hrtim_is_windowing_relevant_to_timer: ${error}`);
  }

  return isRelevantWindowing;
}

/**
 * Check whether the event can be used as trigger source for an ADC trigger
 * @param {integer} adc_trigger_num - ADC trigger number (1..10)
 * @param {string} source - ADC trigger source
 * @returns true if the event can be used, false otherwise
 */
function helper_hrtim_is_event_relevant_to_adc_trigger(adc_trigger_num, source) {
  const lookupTable = [
    {
      "adc_triggers": [1, 3, 5, 7, 9],
      "events": [
        "TAPER", "TARST", "TACMP3", "TACMP4",
        "TBPER", "TBRST", "TBCMP3", "TBCMP4",
        "TCPER", "TCCMP3", "TCCMP4",
        "TDPER", "TDCMP3", "TDCMP4",
        "TEPER", "TECMP3", "TECMP4",
        "TFPER", "TFRST", "TFCMP2", "TFCMP3", "TFCMP4",
        "EEV1", "EEV2", "EEV3", "EEV4", "EEV5"
      ]
    },
    {
      "adc_triggers": [2, 4, 6, 8, 10],
      "events": [
        "TAPER", "TACMP2", "TACMP4",
        "TBPER", "TBCMP2", "TBCMP4",
        "TCPER", "TCRST", "TCCMP2", "TCCMP4",
        "TDPER", "TDRST", "TDCMP2", "TDCMP4",
        "TERST", "TECMP2", "TECMP3", "TECMP4",
        "TFPER", "TFCMP2", "TFCMP3", "TFCMP4",
        "EEV6", "EEV7", "EEV8", "EEV9", "EEV10"
      ]
    }
  ];

  let isRelevantEvent = false;

  try {
    // console.log(`[INFO] helper_hrtim_is_event_relevant_to_adc_trigger: adc_trigger_num=${adc_trigger_num}, source=${source}`);

    for (const entry of lookupTable) {
      if (entry.adc_triggers.includes(adc_trigger_num)) {
        isRelevantEvent = entry.events.includes(source);
        break;
      }
    }
  } catch (error) {
    console.log(`[ERROR] helper_hrtim_is_event_relevant_to_adc_trigger: ${error}`);
  }

  return isRelevantEvent;
}

/**
 * Indicate whether or not an interrupt source has been enabled
 * @param {object} HR-Timer interrupts configuration
 * @param {string} Interrupt vector
 * @param {string} Interrupt source
 * @returns true if the source has already been enabled, false otherwise
 */
function helper_hrtim_is_enabled_interrupt_source(config, interrupt, source) {
  let isEnabled = false;

  try {
    // console.log(`[INFO] helper_hrtim_is_enabled_interrupt_source: config=${JSON.stringify(config)}, interrupt=${interrupt}, source=${source}`);

    isEnabled = config.some(item => 
          item._foreignKey === interrupt && 
          item.interrupt_sources && 
          item.interrupt_sources.some(interruptSource => interruptSource.source === source)
      );
    } catch (error) {
      console.log(`[ERROR] helper_hrtim_is_enabled_interrupt_source: ${error}`);
    }

    // console.log(`[++INFO++] helper_hrtim_is_enabled_interrupt_source: isEnabled=${isEnabled}`);
  return isEnabled;
}

/**
 * Get the fault blanking mode as per fault input (FLTx) and blanking mode
 * @param {string} Fault input
 * @param {string} reset aligned or mowing window
 * @returns true if the event can be usedto set or reset the output, false otherwise
 */
function helper_hrtim_get_fault_blanking_mode(fault, blanking_mode) {

  const mapping = {
    "FLT1": {
      "RESET_ALIGNED_BLANKING": "TARST_TACMP3",
      "MOVING_BLANKING": "TACMP4_TACMP3"
    },
    "FLT2": {
      "RESET_ALIGNED_BLANKING": "TBRST_TBCMP3",
      "MOVING_BLANKING": "TBCMP4_TBCMP3"
    },
    "FLT3": {
      "RESET_ALIGNED_BLANKING": "TCRST_TCCMP3",
      "MOVING_BLANKING": "TCCMP4_TCCMP3"
    },
    "FLT4": {
      "RESET_ALIGNED_BLANKING": "TDRST_TDCMP3",
      "MOVING_BLANKING": "TDCMP4_TDCMP3"
    },
    "FLT5": {
      "RESET_ALIGNED_BLANKING": "TERST_TECMP3",
      "MOVING_BLANKING": "TECMP4_TECMP3"
    },
    "FLT6": {
      "RESET_ALIGNED_BLANKING": "TFRST_TFCMP3",
      "MOVING_BLANKING": "TFCMP4_TFCMP3"
    }
  };

  let faultBlankingMode;

  try {
    // console.log(`[INFO] helper_hrtim_get_fault_blanking_mode: fault=${fault}, blanking_mode=${blanking_mode}`);

    if (mapping[fault] && mapping[fault][blanking_mode]) {
      faultBlankingMode = mapping[fault][blanking_mode];
    } else {
      throw new Error(`Invalid combination of fault: ${fault} and blanking_mode: ${blanking_mode}`);
    }
  } catch (error) {
    console.log(`[ERROR] helper_hrtim_get_fault_blanking_mode: ${error}`);
    faultBlankingMode = null;
  }

  return faultBlankingMode;
}

/**
 * Convert a DFP like source into a HAL/LL source related constant suffix
 * @param {string} DFP like source
 * @returns HAL/LL source related constant suffix
 */
function helper_hrtim_convert_source(source) {
  let conversionResult = null;

  try {
    //console.log(`[INFO] helper_hrtim_convert_source: source=${fsource}`);

    if (!source) {
      return 'GPIO';
    }

    let preFormatedSource = source
      .toUpperCase()
      .replace(/ /g, '_')
      .replace(/\[.*$/, '')
      .replace(/\(.*$/, '')
      .replace(/_OUT$/, ''); 

    console.log(`[DBG] helper_hrtim_convert_source: preFormatedSource=${preFormatedSource}`);

    if (preFormatedSource.includes('TGO_CKTIM')) {
      conversionResult = preFormatedSource.replace(/TGO_CKTIM/g, 'TRGO');
    } else if (preFormatedSource.includes('AFI')) {
      conversionResult = preFormatedSource.replace(/AFI/g, 'GPIO');
    } else if (preFormatedSource.includes('_CKTRGO')) {
      conversionResult = preFormatedSource.replace(/_CKTRGO/g, '');
    } else if (preFormatedSource.includes('AWDG')) {
      conversionResult = preFormatedSource.replace(/AWDG/g, 'AWD');
    } else {
      conversionResult = preFormatedSource;
    }
  } catch (error) {
    console.log(`[ERROR] helper_hrtim_convert_source: ${error}`);
  }

  return conversionResult;
}

/**
 * Convert configured update gating into corresponding HAL/LL constant
 * @param {string} update gating 
 * @param {string} update enable input 
 * @returns HAL/LL update gating related constant suffix
 */
function helper_hrtim_convert_update_gating(updgat, upden) {
  let conversionResult = "";

  try {
    // console.log(`[INFO] helper_hrtim_convert_update_gating: updgat=${updgat}, upden=${upden}`);

    if (updgat.includes('ENABLE_INPUT') && upden !== undefined) {
      conversionResult = helper_hrtim_convert_source(upden);

      if (updgat.includes('UPDATE')) {
        conversionResult += '_UPDATE';
      }
    } else {
      conversionResult = updgat;
    }
  } catch (error) {
    console.log(`[ERROR] helper_hrtim_convert_update_gating: ${error}`);
  }

  return conversionResult;
}

/**
 * Convert configured reset source into into corresponding HAL/LL constant
 * @param {string} timer name 
 * @param {string} reset trigger source 
 * @returns HAL/LL reset related constant suffix
 */
function helper_hrtim_convert_reset_trigger_source(timer, event) {
  let conversionResult = null;

  try {
    // console.log(`[INFO] helper_hrtim_convert_reset_trigger_source: timer=${timer}, event=${event}`);

    const timx = helper_hrtim_convert_timer(timer);

    if (!timx) {
      throw new Error('Invalid timer value');
    }

    const commonEvents = ['NONE', 'EEV', 'MASTER'];
    const containsCommonEvent = commonEvents.some(commonEvent => event.includes(commonEvent));

    if (containsCommonEvent) {
      conversionResult = event;
    } else if (event.includes(timx + '_')) {
      conversionResult = event.replace(timx + '_', '');
    } else {
      conversionResult = event.replace(/TIM([A-F])_/, `${timx}_T$1`);
    }
  } catch (error) {
    console.log(`[ERROR] helper_hrtim_convert_reset_trigger_source: ${error}`);
  }

  return conversionResult;
}

/**
 * Convert configured capture source into into corresponding HAL/LL constant
 * @param {string} timer name 
 * @param {string} capture trigger source 
 * @returns HAL/LL capture source related constant suffix
 */
function helper_hrtim_convert_capture_trigger_source(timer, event) {
  let conversionResult = null;

  try {
    // console.log(`[INFO] helper_hrtim_convert_capture_trigger_source: timer=${timer}, event=${event}`);

    const timx = helper_hrtim_convert_timer(timer);

    if (!timx) {
      throw new Error('Invalid timer value');
    }

    const commonEvents = ['NONE', 'EEV'];
    const containsCommonEvent = commonEvents.some(commonEvent => event.includes(commonEvent));

    if (containsCommonEvent) {
      conversionResult = event;
    } else if (event.includes(timx + '_')) {
      conversionResult = event.replace(timx + '_', '');
    } else if (event.includes('CH')) {
      conversionResult = event.replace('CH', `${timx}_CH`);
    } else {
      conversionResult = event.replace(/TIM([A-F])_/, `${timx}_T$1`);
    }
  } catch (error) {
    console.log(`[ERROR] helper_hrtim_convert_capture_trigger_source: ${error}`);
  }

  return conversionResult;
}

/**
 * Convert configured ADC trigger into into corresponding HAL/LL constant
 * @param {string} layer - HAL or LL
 * @param {string} adc_trigger - ADC trigger id ('ADC trigger n')
 * @returns HAL/LL ADC trigger related constant
 */
function helper_hrtim_convert_adc_trigger_id(layer, adc_trigger) {
  let conversionResult = null;

  try {
    // console.log(`[INFO] helper_hrtim_convert_adc_trigger_id: layer=${layer}, adc_trigger=${adc_trigger}`);

    const triggerNumber = adc_trigger.match(/\d+/)[0];

      if (layer === 'HAL') {
          conversionResult = `HAL_HRTIM_ADC_TRIGGER${triggerNumber}`;
      } else if (layer === 'LL') {
          conversionResult = `LL_HRTIM_ADCTRIG${triggerNumber}`;
      } else {
          throw new Error('Invalid layer. Must be "HAL" or "LL".');
      }
  } catch (error) {
    console.log(`[ERROR] helper_hrtim_convert_adc_trigger_id: ${error}`);
  }

  return conversionResult;
}

/**
 * Convert configured ADC trigger source into into corresponding HAL/LL constant
 * @param {string} layer (HAL or LL) 
 * @param {string} ADC trigger 
 * @param {string} ADC trigger source 
 * @returns HAL/LL ADC trigger source related constant
 */
function helper_hrtim_convert_adc_trigger_source(layer, adc_trigger, event) {
  let conversionResult = null;

  try {
    // console.log(`[INFO] helper_hrtim_convert_adc_trigger_source: layer=${layer}, adc_trigger=${adc_trigger}, event=${event}`);

    let adcTriggerNum;
    let cstSuffix;

    if (event !== undefined) {
      cstSuffix = event;
    } else {
      cstSuffix = 'NONE';
    }

    const triggerNum = parseInt(adc_trigger.replace('ADC trigger ', ''));
    if ([1, 3].includes(triggerNum)) {
      adcTriggerNum = '13';
    } else if ([2, 4].includes(triggerNum)) {
      adcTriggerNum = '24';
    } else if ([5, 7, 9].includes(triggerNum)) {
      adcTriggerNum = '579';
      if (event === 'NONE') {
        cstSuffix = 'MASTER_CMP1';
      }
    } else if ([6, 8, 10].includes(triggerNum)) {
      adcTriggerNum = '6810';
      if (event === 'NONE') {
        cstSuffix = 'MASTER_CMP1';
      }
    } else {
      throw new Error('Invalid ADC trigger number');
    }

    let cstPrefix;
    if (layer === 'LL') {
      cstPrefix = 'LL_HRTIM_ADCTRIG_SRC' + adcTriggerNum + '_';
    } else if (layer === 'HAL') {
      cstPrefix = 'HAL_HRTIM_ADC' + adcTriggerNum + '_TRIGGER_';
    } else {
      throw new Error('Invalid layer');
    }

    conversionResult = cstPrefix + cstSuffix;
  } catch (error) {
    console.log(`[ERROR] helper_hrtim_convert_adc_trigger_source: ${error}`);
  }

  return conversionResult;
}

/**
 * Convert configured external event filtering into into corresponding HAL/LL constant
 * @param {string} timer name 
 * @param {string} substitution pattern for filtering modes from another timing unit  
 * @param {string} external event filtering mode 
 * @returns HAL/LL update gating related constant suffix
 */
function helper_hrtim_convert_event_filter(timer, pattern, filter) {
  let conversionResult = filter;

  try {
    // console.log(`[INFO] helper_hrtim_convert_event_filter: timer=${timer}, pattern=${pattern}, filter=${filter}`);

    if (typeof filter === 'string' && filter.includes(pattern)) {
      let timerName = helper_hrtim_convert_timer(timer);
      conversionResult = filter.replace(new RegExp(pattern, 'g'), timerName);
    }
  } catch (error) {
    console.log(`[ERROR] helper_hrtim_convert_event_filter: ${error}`);
  }

  return conversionResult;
}

/**
 * Convert configured output set/reset event into corresponding HAL/LL constant
 * @param {string} output channel 
 * @param {string} output set/reset event
 * @returns HAL/LL output set/reset event related constant suffix
 */
function helper_hrtim_convert_output_set_reset_event(output, set_reset_event) {
  let conversionResult = null;

  try {
    // console.log(`[INFO] helper_hrtim_convert_output_set_reset_event: output=${output}, set_reset_event=${set_reset_event}`);

    const timx = output.replace(/CH(\w)\w/g, 'TIM$1');

    if (!timx) {
      throw new Error('Invalid output value');
    }

    const commonEvents = ['NONE', 'EEV', 'MASTER'];
    const containsCommonEvent = commonEvents.some(commonEvent => set_reset_event.includes(commonEvent));

    if (containsCommonEvent) {
      conversionResult = set_reset_event;
    } else if (set_reset_event.includes(timx + '_')) {
      conversionResult = set_reset_event.replace(timx + '_', '');
    } else {
      conversionResult = set_reset_event.replace(/TIM([A-F])_/, `${timx}_T$1`);
    }
  } catch (error) {
    console.log(`[ERROR] helper_hrtim_convert_output_set_reset_event: ${error}`);
  }

  return conversionResult;
}

/**
 * Convert configured dual channel DAC mode into corresponding step/reset triggers HAL/LL constant
 * @param {string} step or reset trigger 
 * @param {string} dual channel DAC mode
 * @returns HAL/LL dual channel DAC step/reset triggers related constant suffix
 */
function helper_hrtim_convert_dual_channel_dac_trigger(trigger, mode) {
  let dualChannelDacTrigger = null;

  try {
    // console.log(`[INFO] helper_hrtim_convert_dual_channel_dac_trigger: trigger=${trigger}, mode=${mode}`);

    if (trigger === 'STEP') {
      if (mode.includes('SLOPE')) {
        dualChannelDacTrigger = 'CMP2';
      } else {
        dualChannelDacTrigger = 'OUT1_RESET';
      }
    } else if (trigger === 'RESET') {
      if (mode.includes('CENTER')) {
        dualChannelDacTrigger = 'OUT1_SET';
      } else {
        dualChannelDacTrigger = 'RESET';
      }
    } else {
      throw new Error('Invalid trigger value');
    }
  } catch (error) {
    console.log(`[ERROR] helper_hrtim_convert_dual_channel_dac_trigger: ${error}`);
  }

  return dualChannelDacTrigger;
}

/**
 * Convert configured burst mode clock into corresponding HAL/LL constant
 * @param {string} burst mode controller clock source 
 * @param {string} burst mode clock (on-chip interconnect)
 * @returns HAL/LL burst mode clock related constant suffix
 */
function helper_hrtim_convert_burst_mode_clock(clock, bm_ck) {
  let conversionResult = null;

  try {
    // console.log(`[INFO] helper_hrtim_convert_burst_mode_clock: clock=${clock}, bm_ck=${bm_ck}`);

    if (clock === 'ONCHIP') {
      conversionResult = helper_hrtim_convert_source(bm_ck.source);
    } else {
      conversionResult = clock;
    }
  } catch (error) {
    console.log(`[ERROR] helper_hrtim_convert_burst_mode_clock: ${error}`);
  }

  return conversionResult;
}

/**
 * Convert configured burst trigger into corresponding HAL/LL constant
 * @param {string} burst mode trigger 
 * @param {string} burst mode trigger (on-chip interconnect)
 * @returns HAL/LL burst mode trigger related constant suffix
 */
function helper_hrtim_convert_burst_mode_trigger(trigger, bm_trg) {

  let conversionResult = null;

  try {
    // console.log(`[INFO] helper_hrtim_convert_burst_mode_trigger: trigger=${trigger}, bm_trg=${bm_trg}`);

    if (trigger === 'ONCHIP') {
      if (bm_trg === undefined) {
        throw new Error('bm_ck is undefined for ONCHIP trigger');
      }
      conversionResult = helper_hrtim_convert_source(bm_trg.source);
    } else {
      conversionResult = trigger;
    }
  } catch (error) {
    console.log(`[ERROR] helper_hrtim_convert_burst_mode_trigger: ${error}`);
  }

  return conversionResult;
}

/**
 * Get the output channel identifier from the timing unit and the output number
 * @param {string} timing unit (TIMx, x: A..F)
 * @param {number} Output channel (y: 1 or 2)
 * @returns output channel identifier (CHxy)
 */
function helper_hrtim_get_output_channel(timer, output) {
  let outputChannel = '';

  try {
    // console.log(`[INFO] helper_hrtim_get_output_channel: timer=${timer}, output=${output}`);

    const validTimers = ['TIMA', 'TIMB', 'TIMC', 'TIMD', 'TIME', 'TIMF'];
    if (!validTimers.includes(timer)) {
      throw new Error(`Invalid timer: ${timer}`);
    }

    if (output !== 1 && output !== 2) {
      throw new Error(`Invalid output: ${output}`);
    }

    outputChannel = timer.replace('TIM', 'CH') + output;
  } catch (error) {
    console.log(`[ERROR] helper_hrtim_get_output_channel: ${error}`);
  }

  return outputChannel;
}

/**
 * Get the maximum number of interrupt request sources supported by the timer.
 * @param {string} timer - Timing unit to configure.
 * @param {integer} version - HR-Timer version.
 * @returns number of interrupt request sources available for the timer
 */
function helper_hrtim_get_max_interrupt_request_sources(timer, version) {
  let interruptSourcesNumber = 0;

  try {
    // console.log(`[INFO] helper_hrtim_get_max_interrupt_request_sources: timer=${timer}, version=${version}`);

    if (timer === 'Timer M') {
      interruptSourcesNumber = 7;
    } else {
      interruptSourcesNumber = 14;
      if (version >= 3) {
        interruptSourcesNumber += 2;
      }
    }
  } catch (error) {
    console.log(`[ERROR] helper_hrtim_get_max_interrupt_request_sources: ${error}`);
  }

  return interruptSourcesNumber;
}

/**
 * Get the maximum number of DMA requests sources supported by the timer.
 * @param {string} timer - Timing unit to configure.
 * @param {integer} version - HR-Timer version.
 * @returns number of interrupt sources available for the timer
 */
function helper_hrtim_get_max_dma_request_sources(timer, version) {
  let dmaSourcesNumber = 0;

  try {
    // console.log(`[INFO] helper_hrtim_get_max_dma_request_sources: timer=${timer}, version=${version}`);

    if (timer === 'Timer M') {
      dmaSourcesNumber = 7;
    } else {
      dmaSourcesNumber = 14;
      if (version >= 3) {
        dmaSourcesNumber += 2;
      }
    }
  } catch (error) {
    console.log(`[ERROR] helper_hrtim_get_max_dma_request_sources: ${error}`);
  }

  return dmaSourcesNumber;
}

/**
 * Check whether GPIO configuration is needed for a given HRTIM input/output.
 * @param {object} Actual HRTIM input/output configuration.
 * @param {string} HRTIM input/output name.
 * @returns {boolean} true if GPIO configuration is needed, false otherwise.
 */
function helper_hrtim_is_hrtim_io_connected_to_gpio(hrtim_io_config, hrtim_io_name) {
  let isGpioNeeded = false;
  try {
    //console.log(`[INFO] helper_hrtim_is_hrtim_io_connected_to_gpio: hrtim_io_config=${JSON.stringify(hrtim_io_config)}, hrtim_io_name=${hrtim_io_name}`);

    const configArray = Object.values(hrtim_io_config);

    if (hrtim_io_name.startsWith('CH')) {
      const config = configArray.find(config => config._foreignKey === hrtim_io_name && config.use === true && config.output_config.use_gpio === true);
      if (config) {
        isGpioNeeded = true;
      }
    }
    else if (hrtim_io_name.startsWith('EEV')) {
      const config = configArray.find(config => config._foreignKey === hrtim_io_name && config.use === true && config.external_event_config.source.source === 'AFI');
      if (config) {
        isGpioNeeded = true;
      }
    }
    else if (hrtim_io_name.startsWith('FLT')) {
      const config = configArray.find(config => config._foreignKey === hrtim_io_name && config.use === true && config.fault_input_config.source.source === 'AFI');
      if (config) {
        isGpioNeeded = true;
      }
    }
    else if (hrtim_io_name.startsWith('SYNCIN')) {
      if (hrtim_io_config.use !== undefined && hrtim_io_config.source.source === 'AFI') {
        isGpioNeeded = hrtim_io_config.use;
      }
    }
    else if (hrtim_io_config.use !== undefined) {
      isGpioNeeded = hrtim_io_config.use;
    }
  } catch (error) {
    console.log(`[ERROR] helper_hrtim_is_hrtim_io_connected_to_gpio: ${error}`);
  }

  return isGpioNeeded;
}

/**
 * Check whether at least one GPIO must be configured.
 * @param {object} Actual HRTIM input/output configuration.
 * @returns {boolean} true if at least one HRTIM input/output requiring a GPIO is used, false otherwise.
 */
function helper_hrtim_is_needed_gpio_settings(hrtim_io_config) {

  try {
    //console.log(`[INFO] helper_hrtim_is_needed_gpio_settings: hrtim_io_config=${JSON.stringify(hrtim_io_config)}`);

    // Check if any output channel is used
    if (hrtim_io_config.output_channels.some(output => output.use && output.output_config.use_gpio)) {
      return true;
    }

    // Check if any external event is used and its source is AFI
    if (hrtim_io_config.external_events_conditioning.external_events.some(event => event.use && event.external_event_config.source.source === "AFI")) {
      return true;
    }

    // Check if any fault input is used and its source is AFI
    if (hrtim_io_config.fault_inputs_conditioning.fault_inputs.some(fault => fault.use && fault.fault_input_config.source.source === "AFI")) {
      return true;
    }

    // Check if syncin is used and its source is AFI
    if (hrtim_io_config.syncin.use && hrtim_io_config.syncin.source.source === "AFI") {
      return true;
    }

    // Check if syncout is used
    if (hrtim_io_config.syncout.use) {
      return true;
    }
  } catch (error) {
    console.log(`[ERROR] helper_hrtim_is_needed_gpio_settings: ${error}`);
  }

  return false;
}

function helper_hrtim_dbg_log(object) {
  if (object === undefined) {
    console.log(`[ERROR] helper_hrtim_dbg_log: object is undefined!`);
  }
  else {
    console.log(`[INFO] helper_hrtim_dbg_log: object=${JSON.stringify(object)}`);
  }
  return true;
}

/**
 * Check whether the interrupt source has already been selected.
 * @param {object} Selected interrupt source.
 * @param {string} interrupt.
 * @returns {boolean} true the interrupt source has already been selected, false otherwise.
 */
function helper_hrtim_is_selected_interrupt_source(selected_interrupt_sources, interrupt_source) {
  let isSelected = false;

  if (!selected_interrupt_sources || selected_interrupt_sources.length === 0) {
    return false;
  }
  
  try {
    // console.log(`[INFO] helper_hrtim_is_selected_interrupt_source: selected_interrupt_sources=${JSON.stringify(selected_interrupt_sources)}, interrupt_source = ${interrupt_source}`);

    isSelected = selected_interrupt_sources.some(item => item.source === interrupt_source);
  } catch (error) {
    console.log(`[ERROR] helper_hrtim_is_selected_interrupt_source: ${error}`);
  }

  return isSelected;
}

/**
 * Indicate whether or not the given value can be selected.
 * @param {object[]} selection - Selected values array.
 * @param {string} value - Value to check for selection.
 * @returns {boolean} true if the value is selectable, false otherwise.
 */
function helper_hrtim_is_selectable_value(selection, value) {
  let isSelectable = true;

  if (!selection || selection.length === 0) {
    return true;
  }

  try {
    // console.log(`[INFO] helper_hrtim_is_selectable_value: selection=${JSON.stringify(selection)}, value=${value}`);

    isSelectable = !selection.some(selectionItem => selectionItem.source === value);
  } catch (error) {
    console.log(`[ERROR] helper_hrtim_is_selectable_value: ${error}`);
  }
  
  return isSelectable;
}

/**
 * Indicate whether or not the given output set/reset source can be selected.
 * @param {object[]} outputs_config - HRTIM outputs configuration.
 * @param {string} output - HRTIM output to configure.
 * @param {string} crossbar - Output set or reset crossbar.
 * @param {string} source - Output set/reset source to check for selection.
 * @returns {boolean} true if the output set/reset source is selectable, false otherwise.
 */
function helper_hrtim_is_selectable_set_reset_source(outputs_config, output, crossbar, source) {
  let isSelectable = false;

  try {
    // console.log(`[INFO] helper_hrtim_is_selectable_set_reset_source: outputs_config=${JSON.stringify(outputs_config)}, output=${output}, crossbar=${crossbar}, event=${event}`);

    const result = outputs_config.find(config => config._foreignKey === output);

    if (result) {
      if (crossbar === 'set_crossbar') {
        isSelectable = helper_hrtim_is_selectable_value(result.output_config.set_crossbar, source);
      } else if (crossbar === 'reset_crossbar') {
        isSelectable = helper_hrtim_is_selectable_value(result.output_config.reset_crossbar, source);
      }
    }
  } catch (error) {
    console.log(`[ERROR] helper_hrtim_is_selectable_set_reset_source: ${error}`);
  }

  return isSelectable;
}

/**
 * Indicate whether or not the given counter reset source can be selected.
 * @param {object[]} timers_config - Timers configuration.
 * @param {string} timer - Timing unit to configure.
 * @param {string} source - Counter reset source to check for selection.
 * @returns {boolean} true if the counter reset source is selectable, false otherwise.
 */
function helper_hrtim_is_selectable_counter_reset_source(timers_config, timer, source) {
  let isSelectable = false;

  try {
    // console.log(`[INFO] helper_hrtim_is_selectable_counter_reset_source: timers_config=${JSON.stringify(timers_config)}, timer=${timer}, source=${source}`);

    const result = timers_config.find(config => config._foreignKey === timer);

    if (result) {
      isSelectable = helper_hrtim_is_selectable_value(result.timer_config.reset_triggers, source);
    }
  } catch (error) {
    console.log(`[ERROR] helper_hrtim_is_selectable_counter_reset_source: ${error}`);
  }

  return isSelectable;
}

/**
 * Indicate whether or not the given timer event can be selected.
 * @param {object[]} timers_config - Timers configuration.
 * @param {string} timer - Timing unit to configure.
 * @param {string} events - Name of the timer events array.
 * @param {string} event - Timer event to check for selection.
 * @returns {boolean} true if the timer event is selectable, false otherwise.
 */
function helper_hrtim_is_selectable_timer_event(timers_config, timer, events, event) {
  let isSelectable = false;

  try {
    // console.log(`[INFO] helper_hrtim_is_selectable_timer_event: timers_config=${JSON.stringify(timers_config)}, timer=${timer}, events=${events}, event=${event}`);

    const result = timers_config.find(config => config._foreignKey === timer);

    if (result && Array.isArray(result.timer_config[events])) {
      isSelectable = helper_hrtim_is_selectable_value(result.timer_config[events], event);
    }
  } catch (error) {
    console.log(`[ERROR] helper_hrtim_is_selectable_timer_event: ${error}`);
  }

  return isSelectable;
}

/**
 * Indicate whether or not the given update source can be selected.
 * @param {object[]} timers_config - Timers configuration.
 * @param {string} timer - Timing unit to configure.
 * @param {string} source - Update source to check for selection.
 * @returns {boolean} true if the update source is selectable, false otherwise.
 */
function helper_hrtim_is_selectable_update_source(timers_config, timer, source) {
  let isSelectable = false;

  try {
    // console.log(`[INFO] helper_hrtim_is_selectable_update_source: timers_config=${JSON.stringify(timers_config)}, timer=${timer}, source=${source}`);

    const result = timers_config.find(config => config._foreignKey === timer);

    if (result) {
      isSelectable = helper_hrtim_is_selectable_value(result.timer_config.update_management.update_sources, source);
    }
  } catch (error) {
    console.log(`[ERROR] helper_hrtim_is_selectable_update_source: ${error}`);
  }

  return isSelectable;
}

/**
 * Indicate whether or not the given capture trigger source can be selected.
 * @param {object[]} timers_config - Timers configuration.
 * @param {string} timer - Timing unit to configure.
 * @param {string} capture_unit - capture unit to configure to configure.
 * @param {string} source - Update source to check for selection.
 * @returns {boolean} true if the update source is selectable, false otherwise.
 */
function helper_hrtim_is_selectable_capture_trigger_source(timers_config, timer, capture_unit, source) {
  let isSelectable = false;

  try {
    // console.log(`[INFO] helper_hrtim_is_selectable_capture_trigger_source: timers_config=${JSON.stringify(timers_config)}, timer=${timer}, capture_unit=${capture_unit}, source=${source}`);
    
    const timerConfig = timers_config.find(config => config._foreignKey === timer);

    if (timerConfig) {
      const captureUnitConfig = timerConfig.timer_config.capture_units.find(unit => unit._foreignKey === capture_unit);

      if (captureUnitConfig) {
        isSelectable = helper_hrtim_is_selectable_value(captureUnitConfig.triggers, source);
      }
    }
  } catch (error) {
    console.log(`[ERROR] helper_hrtim_is_selectable_capture_trigger_source: ${error}`);
  }

  return isSelectable;
}

/**
 * Indicate whether or not the given external event source can be selected.
 * @param {object[]} timers_config - Timers configuration.
 * @param {string} timer - Timing unit to configure.
 * @param {string} event - External event to check for selection.
 * @returns {boolean} true if the external event is selectable, false otherwise.
 */
function  helper_hrtim_is_selectable_external_event(timers_config, timer, event) {
  let isSelectable = false;

  try {
    // console.log(`[INFO] helper_hrtim_is_selectable_external_event: timers_config=${JSON.stringify(timers_config)}, timer=${timer}, event=${event}`);

    const timerConfig = timers_config.find(config => config._foreignKey === timer);

    if (timerConfig) {
      const externalEvents = timerConfig.timer_config?.external_events_config?.external_events || [];
      isSelectable = !externalEvents.some(externalEvent => externalEvent.eev === event);
    }
  } catch (error) {
    console.log(`[ERROR] helper_hrtim_is_selectable_external_event: ${error}`);
  }

  return isSelectable;
}


/**
 * Indicate whether or not the given ADC trigger update source can be selected.
 * @param {object[]} adc_triggers_config - ADC triggers configuration.
 * @param {string} adc_trigger - ADC trigger to configure.
 * @param {string} source - ADC trigger update source to check for selection.
 * @returns {boolean} true if the ADC trigger update source is selectable, false otherwise.
 */
function helper_hrtim_is_selectable_adc_trigger_update_source(adc_triggers_config, adc_trigger, source) {
  let isSelectable = false;

  try {
    // console.log(`[INFO] helper_hrtim_is_selectable_adc_trigger_update_source: adc_triggers_config=${JSON.stringify(adc_triggers_config)}, adc_trigger=${adc_trigger}, source=${source}`);
    
    const adcTriggerConfig = adc_triggers_config.find(config => config._foreignKey === adc_trigger);

    if (adcTriggerConfig) {
      isSelectable = helper_hrtim_is_selectable_value(adcTriggerConfig.config.update_sources, source);
    }
  } catch (error) {
    console.log(`[ERROR] helper_hrtim_is_selectable_adc_trigger_update_source: ${error}`);
  }

  return isSelectable;
}

/**
 * Indicate whether or not the given ADC trigger source can be selected.
 * @param {object[]} adc_triggers_config - ADC triggers configuration.
 * @param {string} adc_trigger - ADC trigger to configure.
 * @param {string} source - Trigger source.
 * @returns {boolean} true if the ADC trigger source is selectable, false otherwise.
 */
function helper_hrtim_is_selectable_adc_trigger_source(adc_triggers_config, adc_trigger, source) {
  let isSelectable = false;
  try {
    //console.log(`[INFO] helper_hrtim_is_selectable_adc_trigger_source: adc_triggers_config=${JSON.stringify(adc_triggers_config)}, adc_trigger=${adc_trigger}, source=${source}`);

    const adcTriggerConfig = adc_triggers_config.find(config => config._foreignKey === adc_trigger);
 
    if (adcTriggerConfig) {
      isSelectable = helper_hrtim_is_selectable_value(adcTriggerConfig.config.trigger_sources, source);
    }
  } catch (error) {
    console.log(`[ERROR] helper_hrtim_is_selectable_adc_trigger_source: ${error}`);
  }
  return isSelectable;
}

/**
 * Indicate whether or not the given crossbar override trigger source can be selected.
 * @param {object[]} timers_config - Array of timer configurations.
 * @param {string} timer - Timer to configure.
 * @param {string} source - Crossbar override trigger source to check for selection.
 * @returns {boolean} true if the crossbar override trigger source is selectable, false otherwise.
 */
function helper_hrtim_is_selectable_crossbar_override_trigger_source(timers_config, timer, source) {
  let isSelectable = false;

  try {
    // console.log(`[INFO] helper_hrtim_is_selectable_crossbar_override_trigger_source: timers_config=${JSON.stringify(timers_config)}, timer=${timer}, source=${source}`);
    
    const timerConfig = timers_config.find(config => config._foreignKey === timer);

    if (timerConfig) {
      const crossbarOverrideConfig = timerConfig.timer_config?.crossbar_override?.config || [];
 
      if (crossbarOverrideConfig) {
        isSelectable = helper_hrtim_is_selectable_value(crossbarOverrideConfig.triggers, source);
      }
    }
  } catch (error) {
    console.log(`[ERROR] helper_hrtim_is_selectable_crossbar_override_trigger_source: ${error}`);
  }

  return isSelectable;
}

/**
 * Indicate whether or not the given forcing event is selectable for the specified output.
 * @param {Array} timers_config - Array of timer configurations.
 * @param {string} timer - The timer's foreign key to look for (e.g., "Timer A").
 * @param {string} output - The output's foreign key to look for (e.g., "Output1").
 * @param {string} event - The event to check for in the forcing events array.
 * @returns {boolean} - Returns true if the event is NOT found in the forcing events array, otherwise false.
 */
function helper_hrtim_is_selectable_crossbar_override_forcing_event(timers_config, timer, output, event) {
  let isSelectable = true;

  try {
    // console.log(`[INFO] helper_hrtim_is_selectable_crossbar_override_forcing_event: timers_config=${JSON.stringify(timers_config)}, timer=${timer}, output=${output}, event=${event}`);

    const timerConfig = timers_config.find(t => t._foreignKey === timer);

    // Check if the timer configuration exists
    if (timerConfig) {
      // Access the crossbar_override configuration
      const crossbarOverride = timerConfig.timer_config.crossbar_override;

      // Check if the crossbar_override configuration exists
      if (crossbarOverride) {
        // Find the output configuration that matches the specified output
        const forceModeConfig = crossbarOverride.config.force_mode_config.find(o => o._foreignKey === output);

        // Check if the output configuration is valid and has forcing events
        if (forceModeConfig && forceModeConfig.force_mode === "EVENT" && forceModeConfig["forcing_events"]) {
          // Check if the event exists in the forcing events array
          const eventExists = forceModeConfig["forcing_events"].some(e => e.source === event);

          // Update isSelectable based on whether the event exists
          isSelectable = !eventExists;
        }
      }
    }
  } catch (error) {
    console.log(`[ERROR] helper_hrtim_is_selectable_crossbar_override_forcing_event: ${error}`);
  }

  return isSelectable;
}

/**
 * Indicate whether or not the given DMA trigger can be selected.
 * @param {object[]} triggers - Selected DMA triggers.
 * @param {string} trigger - DMA trigger.
 * @returns {boolean} true if the DMA trigger is selectable, false otherwise.
 */
function helper_hrtim_is_selectable_dma_trigger(triggers, trigger) {
  let isSelectable = true;

  if (!triggers || triggers.length === 0) {
    return true;
  }

  try {
    // console.log(`[INFO] helper_hrtim_is_selectable_dma_trigger: triggers=${JSON.stringify(triggers)}, trigger=${trigger}`);

    isSelectable = !triggers.some(item => item.source === trigger);
  } catch (error) {
    console.log(`[ERROR] helper_hrtim_is_selectable_dma_trigger: ${error}`);
  }

  return isSelectable;
}

/**
 * Indicate whether delayed protection is used for a given timing unit.
 * @param {object[]} config - Timing unit configuration.
 * @param {string} timer - Timing unit.
 * @returns {boolean} true if the delayed protection is used, false otherwise.
 */
function helper_hrtim_is_used_delayed_protection(config, timer) {
  let isUsed = false;
  try {
      // console.log(`[INFO] helper_hrtim_is_used_delayed_protection: config=${JSON.stringify(config)}, timer = ${timer}`);
      isUsed = config.some(item => 
          item._foreignKey === timer && item.timer_config.output_stage.delayed_prot.use === true
      );
  } catch (error) {
    console.log(`[ERROR] helper_hrtim_is_used_delayed_protection: ${error}`);
  }
  return isUsed;
}

/**
 * Indicate whether the fast mode feature is available for a given external event.
 * @param {string} event - External event.
 * @param {string} feature - External event feature (FILTER of FAST_MODE).
 * @returns {boolean} true if fast mode is supported by the external event.
 */
function helper_hrtim_is_supported_event_feature(event, feature) {
  let isSupported = false;

  try {
    // console.log(`[INFO] helper_hrtim_is_supported_event_feature: event = ${event}, feature = ${feature}`);

    const fastModeEvents = ["EEV1", "EEV2", "EEV3", "EEV4", "EEV5", "EEV11", "EEV12", "EEV13"];
    const filterModeEvents = ["EEV6", "EEV7", "EEV8", "EEV9", "EEV10", "EEV14", "EEV15", "EEV16"];

    if (feature === "FAST_MODE" && fastModeEvents.includes(event)) {
      isSupported = true;
    } else if (feature === "FILTER" && filterModeEvents.includes(event)) {
      isSupported = true;
    }
  } catch (error) {
    console.log(`[ERROR] helper_hrtim_is_supported_event_feature: ${error}`);
  }

  return isSupported;
}

/**
 * Indicate whether the push-pull mode is enabled for a given timing unit.
 * @param {object[]} config - Timing unit configuration.
 * @param {string} timer - Timing unit.
 * @returns {boolean} true if push-pull mode is enabled for the timing unit.
 */
function helper_hrtim_is_enabled_pushpull(config, timer) {
  let isEnabled = false;

  try {
    // console.log(`[INFO] helper_hrtim_is_enabled_pushpull: timers_config=${JSON.stringify(config)}, timer=${timer}`);

     isEnabled = config.some(item => 
          item._foreignKey === timer && item.timer_config.output_stage.push_pull_mode === true
      );
      } catch (error) {
    console.log(`[ERROR] helper_hrtim_is_enabled_pushpull: ${error}`);
  }

  return isEnabled;
}

/**
 * Returns the combined event source default value.
 * @param {object} event - External event.
 * @param {integer} source - Selected source.
 * @returns {string} Combined event source name.
 */
function helper_hrtim_get_combined_event_source_name(event, source) {
  let sourceName = null;

  try {
    // console.log(`[INFO] helper_hrtim_get_combined_event_source_name: event=${event}, source=${source}`);

    const eventMapping = {
      "EEVA": [ "External event 1"  , "External event 11" , "External event 1 AND external event 2"   , "External event 1 AND external event 11" ],
      "EEVB": [ "External event 2"  , "External event 12" , "External event 2 AND external event 3"   , "External event 2 AND external event 12" ],
      "EEVC": [ "External event 3"  , "External event 13" , "External event 3 AND external event 4"   , "External event 3 AND external event 13" ],
      "EEVD": [ "External event 4"  , "External event 14" , "External event 4 AND external event 5"   , "External event 4 AND external event 14" ],
      "EEVE": [ "External event 5"  , "External event 15" , "External event 5 AND external event 6"   , "External event 5 AND external event 15" ],
      "EEVF": [ "External event 6"  , "External event 16" , "External event 6 AND external event 7"   , "External event 6 AND external event 16" ],
      "EEVG": [ "External event 7"  , "External event 11" , "External event 7 AND external event 8"   , "External event 7 AND external event 11" ],
      "EEVH": [ "External event 8"  , "External event 12" , "External event 8 AND external event 9"   , "External event 8 AND external event 12" ],
      "EEVI": [ "External event 9"  , "External event 13" , "External event 9 AND external event 10"  , "External event 9 AND external event 13" ],
      "EEVJ": [ "External event 10" , "External event 14" , "External event 10 AND external event 11" , "External event 10 AND external event 14"],
    };

    if (!eventMapping.hasOwnProperty(event)) {
      throw new Error(`Invalid event: ${event}`);
    }

    if (source > 3) {
      throw new Error(`Invalid selection: ${source}`);
    }

    sourceName = eventMapping[event][source];

  } catch (error) {
    console.log(`[ERROR] helper_hrtim_get_combined_event_source_name: ${error}`);
  }

  return sourceName;
}

/**
 * Returns the combined event source default value.
 * @param {object} event - External event.
 * @param {integer} source - Selected source.
 * @returns {string} Combined event source value.
 */
function helper_hrtim_get_combined_event_source_value(event, source) {
  let sourceValue = null;

  try {
    //console.log(`[INFO] helper_hrtim_get_combined_event_source_value: event=${event}, source=${source}`);

    const eventMapping = {
      "EEVA": [ "EEV1"  , "EEV11" , "EEV1_EEV2"   , "EEV1_EV11"  ],
      "EEVB": [ "EEV2"  , "EEV12" , "EEV2_EEV3"   , "EEV2_EEV12" ],
      "EEVC": [ "EEV3"  , "EEV13" , "EEV3_EEV4"   , "EEV3_EEV13" ],
      "EEVD": [ "EEV4"  , "EEV14" , "EEV4_EEV5"   , "EEV4_EEV14" ],
      "EEVE": [ "EEV5"  , "EEV15" , "EEV5_EEV6"   , "EEV5_EEV15" ],
      "EEVF": [ "EEV6"  , "EEV16" , "EEV6_EEV7"   , "EEV6_EEV16" ],
      "EEVG": [ "EEV7"  , "EEV11" , "EEV7_EEV8"   , "EEV7_EEV11" ],
      "EEVH": [ "EEV8"  , "EEV12" , "EEV8_EEV9"   , "EEV8_EEV12" ],
      "EEVI": [ "EEV9"  , "EEV13" , "EEV9_EEV10"  , "EEV9_EEV13" ],
      "EEVJ": [ "EEV10" , "EEV14" , "EEV10_EEV11" , "EEV10_EEV14"],
    };

    if (!eventMapping.hasOwnProperty(event)) {
      throw new Error(`Invalid event: ${event}`);
    }

    if (source > 3) {
      throw new Error(`Invalid selection: ${source}`);
    }

    sourceValue = eventMapping[event][source];

  } catch (error) {
    console.log(`[ERROR] helper_hrtim_get_combined_event_source_value: ${error}`);
  }

  return sourceValue;
}

/**
 * Searches for an object in the interconnect array where the ip_signal matches the given key.
 * If found, returns the capitalized source string. If not found, returns the capitalized key.
 * @param {object[]} interconnect - Array of interconnect objects.
 * @param {string} key - The ip_signal key to search for.
 * @returns {string} - Capitalized source string if found, otherwise capitalized key.
 */
function helper_hrtim_get_crossbar_override_external_trigger(interconnect, key) {
  let externalTrigger;

  try {
    //console.log(`[INFO] helper_hrtim_get_crossbar_override_external_trigger: interconnect=${JSON.stringify(interconnect)}, key=${key}`);

    // Validate input
    if (!Array.isArray(interconnect)) {
      throw new Error("Invalid interconnect: Expected an array.");
    }
    if (typeof key !== "string") {
      throw new Error("Invalid key: Expected a string.");
    }

    // Find the object in the interconnect array where ip_signal matches the key
    const foundObject = interconnect.find(obj => obj.ip_signal === key);

    // Determine the value to return
    externalTrigger = foundObject
      ? foundObject.source.toUpperCase()
      : key.toUpperCase();
  } catch (error) {
    console.error(`[ERROR] helper_hrtim_get_crossbar_override_external_trigger: ${error.message}`);

    // Assign fallback value to externalTrigger in case of an error
    externalTrigger = key.toUpperCase();
  }

  return externalTrigger;
}

/**
 * Generates set/reset crossbar configuration string.
 * 
 * @param {string} prefix - constant name prefix.
 * @param {object[]} sources - array of set/reset crossbar sources.
 * @param {string} key - key.
 * @returns {string} set/reset crossbar configuration (combination of sources).
 */
function helper_hrtim_get_crossbar_configuration(prefix, sources, key) {
  let crossbarConfiguration = "";

  try {
    // console.log(`[INFO] helper_hrtim_get_crossbar_configuration: prefix=${prefix}, sources=${JSON.stringify(sources)}, key=${key}`);

    if (Array.isArray(sources) && sources.length > 0) {
      const combinedSources = [];

      for (let i = 0; i < sources.length; i++) {
        try {
          const sourceName = sources[i].source;
          const convertedEvent = helper_hrtim_convert_output_set_reset_event(key, sourceName);
          combinedSources.push(`${prefix}_${convertedEvent}`);
        } catch (innerError) {
          console.error(`[ERROR] Failed to process source at index ${i}:`, innerError);
          // Continue processing other sources despite errors
        }
      }

      crossbarConfiguration = combinedSources.join(" | ");
    }

  } catch (error) {
    console.error(`[ERROR] helper_hrtim_get_crossbar_configuration: ${error.message}`);
  }

  return crossbarConfiguration;
}

/**
 * Converts a generic HAL digital filter string to a generic LL digital filter string.
 * @param {string} filter - Generic HAL digital filter.
 * @returns {string} Generic LL digital filter
 */
function helper_hrtim_convert_to_ll_filter(filter) {
  let llFilter = "NONE";
  const map = {
    "FDIV1": "NONE",
    "FDIV1_N2": "1",
    "FDIV1_N4": "2",
    "FDIV1_N8": "3",
    "FDIV2_N6": "4",
    "FDIV2_N8": "5",
    "FDIV4_N6": "6",
    "FDIV4_N8": "7",
    "FDIV8_N6": "8",
    "FDIV8_N8": "9",
    "FDIV16_N5": "10",
    "FDIV16_N6": "11",
    "FDIV16_N8": "12",
    "FDIV32_N5": "13",
    "FDIV32_N6": "14",
    "FDIV32_N8": "15"
  };

  try {
    // console.log(`[INFO] helper_hrtim_convert_to_ll_filter: filter=${filter}`);
    if (!(filter in map)) {
      throw new Error(`Unknown filter: ${filter}`);
    }
    llFilter = map[filter];
  } catch (error) {
    console.error(`[ERROR] helper_hrtim_convert_to_ll_filter: ${error.message}`);
  }

  return llFilter;
}

/**
 * Removes all occurrences of a specified substring from a given string.
 * @param {string} str - The original string from which to remove the substring.
 * @param {string} substr - The substring to be removed from the original string.
 * @returns {string} The resulting string after all occurrences of the substring have been removed.
 *                   If either parameter is not a string, returns the original string unchanged.
 */
function helper_hrtim_remove_substring(str, substr) {
  if (typeof str !== 'string' || typeof substr !== 'string') {
    return str;
  }
  return str.split(substr).join('');
}

/**
 * Formats an array of trigger objects into a string of LL HRTIM trigger constants.
 *
 * This function processes an array of trigger objects, each expected to have a `source` property,
 * and converts them into a formatted string of Low-Level (LL) Hardware Timer (HRTIM) constants.
 * It prepends each valid trigger source with the provided prefix and joins them with `" | "` as a separator.
 *
 * @param {string} prefix - The LL HRTIM constant prefix to prepend to each trigger source (e.g., "LL_HRTIM_UPDATETRIG_").
 * @param {Array<{source: string}>} triggers - Array of trigger objects, each with a `source` string property.
 * @param {string} property - The property name in each trigger object to use (e.g., "source").
 * @returns {string} A string of formatted trigger constants separated by `" | "`, or `"prefixNONE"` if no valid triggers are present.
 */
function helper_hrtim_format_ll_triggers_selection(prefix, triggers, property) {
  let selectedTriggers = prefix + 'NONE';

  try {
    //console.log(`[INFO] helper_hrtim_format_ll_triggers_selection: prefix=${prefix}, triggers=${JSON.stringify(triggers)}, property=${property}`);
    // Check if triggers exists and is a non-empty array
    if (
      Array.isArray(triggers) &&
      triggers.length > 0
    ) {
      // Filter out sources with value "NONE"
      const filteredTriggers = triggers.filter(item => item[property] !== 'NONE');

      // If after filtering there are valid sources, build the string
      if (filteredTriggers.length > 0) {
        selectedTriggers = filteredTriggers
          .map(item => prefix + `${item[property]}`)
          .join(' | ');
      }
    }
  } catch (error) {
    console.error(`[ERROR] helper_hrtim_format_ll_triggers_selection: ${error.message}`);
  }

  return selectedTriggers;
}

/**
 * Converts an array of trigger objects into a formatted string of LL HRTIM capture trigger constants.
 *
 * @param {string} timer - The timer name.
 * @param {Array<{source: string}>} triggers - Array of trigger sources.
 * @returns {string} A string of LL capture trigger constants separated by `" | "`, or `"LL_HRTIM_CAPTURETRIG_NONE"` 
 *                   if no valid triggers are found.
 */
function helper_hrtim_format_ll_capture_triggers_selection(timer, triggers) {
  let selectedTriggers = 'LL_HRTIM_CAPTURETRIG_' + 'NONE';

  try {
    //console.log(`[INFO] helper_hrtim_format_ll_capture_triggers_selection: timer=${timer}, triggers=${JSON.stringify(triggers)}`);
    // Check if triggers exists and is a non-empty array
    if (Array.isArray(triggers) && triggers.length > 0 ) {
      // Filter out sources with value "NONE"
      const filteredTriggers = triggers.filter(item => item.source !== 'NONE');

      // If after filtering there are valid sources, build the string
      if (filteredTriggers.length > 0) {
        selectedTriggers = filteredTriggers
          .map(item => 'LL_HRTIM_CAPTURETRIG_' + helper_hrtim_convert_capture_trigger_source(timer, item.source))
          .join(' | ');
      }
    }
  } catch (error) {
    console.error(`[ERROR] helper_hrtim_format_ll_capture_triggers_selection: ${error.message}`);
  }

  return selectedTriggers;
}

/**
 * Formats the LL update gating string based on update_gating and update_enable_source.
 * @param {string} update_gating - The update gating mode.
 * @param {string} update_enable_source - The update enable source string.
 * @returns {string} Formatted update gating string.
 */
function helper_hrtim_format_ll_update_gating(update_gating, update_enable_source) {
  let updateGating = 'LL_HRTIM_UPDATEGAT_INDEPENDENT';

  try {
    //console.log(`[INFO] helper_hrtim_format_ll_update_gating: update_gating=${update_gating}, update_enable_source=${update_enable_source}, dbg=${JSON.stringify(update_enable_source)}`);
    switch (update_gating) {
      case 'DMABURST_COMPLETE':
        updateGating = 'LL_HRTIM_UPDATEGAT_DMABURST_COMPLETE';
        break;

      case 'DMABURST_UPDATE':
        updateGating = 'LL_HRTIM_UPDATEGAT_DMABURST_UPDATE';
        break;

      case 'ENABLE_INPUT':
        updateGating = 'LL_HRTIM_UPDATEGAT_' + helper_hrtim_convert_source(update_enable_source);
        break;

      case 'ENABLE_INPUT_UPDATE':
        updateGating = 'LL_HRTIM_UPDATEGAT_' + helper_hrtim_convert_source(update_enable_source) + '_UPDATE';
        break;
    }
  } catch (error) {
    console.error(`[ERROR] helper_hrtim_format_ll_update_gating: ${error.message}`);
  }

  return updateGating;
}

/**
 * Formats the LL roll over mode string string based on roll over mode.
 * @param {string} roll_over_mode - The roll_over_mode mode.
 * @returns {string} Formatted roll over mode string.
 */
function helper_hrtim_format_ll_roll_over_mode(roll_over_mode) {
  let rollOverMode = 'LL_HRTIM_ROLLOVER_MODE_BOTH';

  try {
    //console.log(`[INFO] helper_hrtim_format_ll_roll_over_mode: roll_over_mode=${roll_over_mode}`);
    switch (roll_over_mode) {
      case 'VALLEY':
        rollOverMode = 'LL_HRTIM_ROLLOVER_MODE_RST';
        break;

      case 'CREST':
        rollOverMode = 'LL_HRTIM_ROLLOVER_MODE_PER';
        break;
    }
  } catch (error) {
    console.error(`[ERROR] helper_hrtim_format_ll_roll_over_mode: ${error.message}`);
  }

  return rollOverMode;
}

/**
 * Converts an auto delayed mode identifier into the corresponding LL HRTIM compare mode constant string.
 *
 * This function maps a given auto delayed mode string to its corresponding Low-Level (LL) Hardware Timer (HRTIM)
 * compare mode constant. If the input mode does not match any predefined cases, it returns a default constant.
 *
 * @param {string} auto_delayed_mode - The auto delayed mode identifier string.
 * @returns {string} The corresponding LL HRTIM compare mode constant string.
 */
function helper_hrtim_format_ll_auto_delayed_mode(auto_delayed_mode) {
  let autoDelayedMode = 'LL_HRTIM_COMPAREMODE_REGULAR';

  try {
    //console.log(`[INFO] helper_hrtim_format_ll_auto_delayed_mode: auto_delayed_mode=${auto_delayed_mode}`);
    switch (auto_delayed_mode) {
      case 'TIMEOUT_NONE':
        autoDelayedMode = 'LL_HRTIM_COMPAREMODE_DELAY_NOTIMEOUT';
        break;

      case 'TIMEOUT_CMP1':
        autoDelayedMode = 'LL_HRTIM_COMPAREMODE_DELAY_CMP1';
        break;

      case 'TIMEOUT_CMP3':
        autoDelayedMode = 'LL_HRTIM_COMPAREMODE_DELAY_CMP3';
        break;
    }
  } catch (error) {
    console.error(`[ERROR] helper_hrtim_format_ll_auto_delayed_mode: ${error.message}`);
  }

  return autoDelayedMode;
}

/**
 * Generates the LL delayed protection related constant name based on input parameters.
 * 
 * @param {string} mode - The configured delayed prtection mode.
 * @param {string} outputs - The output(s) delayed protectyion mode is applied to.
 * @param {string} eev - The external event selected in delayed idle mode.
 * @returns {string} The generated LL delayed protection constant name.
 */
function helper_hrtim_format_ll_delayed_protection_mode(mode, outputs, eev) {
  // Initialize with default value
  let delayedProtectionMode = `LL_HRTIM_DLYPRT_DELAYOUT1_${eev}`;

  try {
    //console.log(`[INFO] helper_hrtim_format_ll_delayed_protection_mode: mode=${mode}, outputs=${outputs}, eev=${eev}`);
    // Check for undefined parameters explicitly
    if (mode === undefined || eev === undefined) {
      throw new Error("One or more parameters are undefined");
    }

    if (mode === "DELAYED_IDLE") {
      if (outputs === undefined) {
        throw new Error("eev parameter is undefined for DELAYED_IDLE mode");
      }

      if (outputs === "OUT1") {
        delayedProtectionMode = `LL_HRTIM_DLYPRT_DELAYOUT1_${eev}`;
      } else if (outputs === "OUT2") {
        delayedProtectionMode = `LL_HRTIM_DLYPRT_DELAYOUT2_${eev}`;
      } else if (outputs === "OUT1_OUT2") {
        delayedProtectionMode = `LL_HRTIM_DLYPRT_DELAYBOTH_${eev}`;
      }
    } else if (mode === "BALANCED_IDLE" || mode === "BALANCED_IDLE_AUTO_RESUME") {
      delayedProtectionMode = `LL_HRTIM_DLYPRT_BALANCED_${eev}`;
    }
  } catch (error) {
    console.error(`[ERROR] helper_hrtim_format_ll_delayed_protection_mode: ${error.message}`);
  }

  return delayedProtectionMode;
}

/**
 * Generates a concatenated string of fault constants separated by ' | '.
 * 
 * @param {Array<{enable: string}>} faults - Array of objects with an 'enable' string property.
 * @returns {string} Concatenated string of fault constants prefixed with 'LL_HRTIM_'.
 *                   Defaults to "LL_HRTIM_FLT1" if input is invalid, empty, or on error.
 */
function helper_hrtim_format_ll_faults_selection(faults) {
  let faultSelection = "LL_HRTIM_FLT1";

  try {
    //console.log(`[INFO] helper_hrtim_format_ll_faults_selection: faults=${JSON.stringify(faults)}`);
    if (Array.isArray(faults) && faults.length > 0) {
      const faultStrings = faults
        .map(fault => fault && typeof fault.enable === 'string' ? `LL_HRTIM_${fault.enable}` : null)
        .filter(Boolean);

      if (faultStrings.length > 0) {
        faultSelection = faultStrings.join(' | ');
      }
    }
  } catch (error) {
    console.error(`[ERROR] helper_hrtim_format_ll_faults_selection: ${error.message}`);
  }

  return faultSelection;
}

/**
 * Replaces all occurrences of a substring within a string with another substring.
 * 
 * @param {string} str - The original string.
 * @param {string} searchValue - The substring to search for.
 * @param {string} replaceValue - The substring to replace with.
 * @returns {string} The resulting string after replacements.
 */
function helper_hrtim_replace_substring(str, searchValue, replaceValue) {
  if (typeof str !== 'string' || typeof searchValue !== 'string' || typeof replaceValue !== 'string') {
    return str;
  }
  return str.split(searchValue).join(replaceValue);
}

/**
 * Constructs a bitmask string of HRTIM interrupt enable flags.
 *
 * @param {Object} fault_events - Object representing HRTIM fault interrupts configuration.
 * @param {Object} global_events - Object representing HRTIM global interrupts configuration.
 *
 * @returns {string} A concatenated string of interrupt enable flags separated by " | ", or an empty string on error.
 */
function helper_hrtim_define_ll_hrtim_dier_mask(fault_events, global_events) {
  try {
    // console.log(`[INFO] helper_hrtim_define_ll_hrtim_dier_mask: fault_events=${JSON.stringify(fault_events)}, global_events=${JSON.stringify(global_events)}`);

    let dierMask = [];

    // Single lookup table mapping all source names to base bit field names
    const sourceMap = {
      "SYSFLT": "LL_HRTIM_IER_SYSFLTIE",
      "FLT1": "LL_HRTIM_IER_FLT1IE",
      "FLT2": "LL_HRTIM_IER_FLT2IE",
      "FLT3": "LL_HRTIM_IER_FLT3IE",
      "FLT4": "LL_HRTIM_IER_FLT4IE",
      "FLT5": "LL_HRTIM_IER_FLT5IE",
      "FLT6": "LL_HRTIM_IER_FLT6IE",
      "FLT7": "LL_HRTIM_IER_FLT7IE",
      "FLT8": "LL_HRTIM_IER_FLT8IE",
      "DLL_CALIBRATION": "LL_HRTIM_IER_DLLRDYIE",
      "BURST_MODE_PERIOD": "LL_HRTIM_IER_BMPERIE",
    };

    // Process fault_events array
    if (Array.isArray(fault_events)) {
      fault_events.forEach(({ source }) => {
        if (sourceMap[source]) {
          dierMask.push(sourceMap[source]);
        }
      });
    }

    // Process global_events array
    if (Array.isArray(global_events)) {
      global_events.forEach(({ source }) => {
        if (sourceMap[source]) {
          dierMask.push(sourceMap[source]);
        }
      });
    }

    // Join all parts with " | "
    return dierMask.join(" | ");
  } catch (error) {
    console.error(`[ERROR] helper_hrtim_define_ll_hrtim_dier_mask: ${error.message}`);
    return "";
  }
}

/**
 * Constructs a bitmask string of master timer interrupt/DMA request enable flags.
 *
 * @param {Object} timer_events - Object representing master timer interrupts/DMA requests configuration.
 * @param {string} suffix - Suffix string to append to each flag ("IE" or "DE").
 *
 * @returns {string} A concatenated string of interrupt enable flags separated by " | ", or an empty string on error.
 */
function helper_hrtim_define_ll_master_timer_dier_mask(timer_events, suffix) {
  try {
    console.log(`[INFO] helper_hrtim_define_ll_master_timer_dier_mask: timer_events=${JSON.stringify(timer_events)}, suffix=${suffix}`);

    let dierMask = [];

    // Helper function to append constant suffix to flag base name
    const withSuffix = (base) => base + suffix;

    // Single lookup table mapping all source names to base bit field names
    const sourceMap = {
      "SYNCHRO": "LL_HRTIM_MDIER_SYNC",
      "UPDATE": "LL_HRTIM_MDIER_MUPD",
      "REPETITION": "LL_HRTIM_MDIER_MREP",
      "CMP1": "LL_HRTIM_MDIER_MCMP1",
      "CMP2": "LL_HRTIM_MDIER_MCMP2",
      "CMP3": "LL_HRTIM_MDIER_MCMP3",
      "CMP4": "LL_HRTIM_MDIER_MCMP4",
    };

    // Process timer events
    if (Array.isArray(timer_events)) {
      const sources = timer_events.map(src => src.source);
      sources.forEach(source => {
        if (sourceMap[source]) {
          dierMask.push(withSuffix(sourceMap[source]));
        }
      });
    }

    // Join all parts with " | "
    return dierMask.join(" | ");
  } catch (error) {
    console.error(`[ERROR] helper_hrtim_define_ll_master_timer_dier_mask: ${error.message}`);
    return "";
  }
}

/**
 * Constructs a bitmask string of timing unit interrupt/DMA request enable flags.
 *
 * @param {Object} timer_events - Object representing timing unit interrupts/DMA requests configuration.
 * @param {string} suffix - Suffix string to append to each flag ("IE" or "DE").
 *
 * @returns {string} A concatenated string of interrupt enable flags separated by " | ", or an empty string on error.
 */
function helper_hrtim_define_ll_timx_dier_mask(timer_events, suffix) {
  try {
    console.log(`[INFO] helper_hrtim_define_ll_timx_dier_mask: timer_events=${JSON.stringify(timer_events)}, suffix=${suffix}`);

    let dierMask = [];

    // Helper function to append constant suffix to flag base name
    const withSuffix = (base) => base + suffix;

    // Single lookup table mapping all source names to base bit field names
    const sourceMap = {
      "UPDATE": "LL_HRTIM_TIMDIER_UPD",
      "REPETITION": "LL_HRTIM_TIMDIER_REP",
      "RESET": "LL_HRTIM_TIMDIER_RSTIE",
      "DELAYED_PROT": "LL_HRTIM_TIMDIER_DLYPRT",
      "CMP1": "LL_HRTIM_TIMDIER_CMP1",
      "CMP2": "LL_HRTIM_TIMDIER_CMP2",
      "CMP3": "LL_HRTIM_TIMDIER_CMP3",
      "CMP4": "LL_HRTIM_TIMDIER_CMP4",
      "CPT1": "LL_HRTIM_TIMDIER_CPT1",
      "CPT2": "LL_HRTIM_TIMDIER_CPT2",
      "SET1" : "LL_HRTIM_TIMDIER_SET1",
      "RESET1": "LL_HRTIM_TIMDIER_RST1",
      "SET2" : "LL_HRTIM_TIMDIER_SET2",
      "RESET2": "LL_HRTIM_TIMDIER_RST2IE",
      "XBAR_OVR_TRIGGER": "LL_HRTIM_TIMDIER_COT",
      "XBAR_OVR_REARM": "LL_HRTIM_TIMDIER_CORDE",
    };

    // Process timer events
    if (Array.isArray(timer_events)) {
      const sources = timer_events.map(src => src.source);
      sources.forEach(source => {
        if (sourceMap[source]) {
          dierMask.push(withSuffix(sourceMap[source]));
        }
      });
    }

    // Join all parts with " | "
    return dierMask.join(" | ");
  } catch (error) {
    console.error(`[ERROR] helper_hrtim_define_ll_timx_dier_mask: ${error.message}`);
    return "";
  }
}

module.exports = {

  helper_hrtim_get_timers,

  helper_hrtim_get_output_channels,

  helper_hrtim_get_compare_units,

  helper_hrtim_get_capture_units,

  helper_hrtim_get_adc_tiggers,

  helper_hrtim_get_event_counters,

  helper_hrtim_get_output_set_reset_sources,

  helper_hrtim_get_hrtim_interrupt_requests,

  helper_hrtim_need_at_least_one_gpio,

  helper_hrtim_is_used_timer,

  helper_hrtim_get_timing_unit,

  helper_hrtim_any_resource_used,

  helper_hrtim_is_used_resource,

  helper_hrtim_get_enabled_fault_count,

  helper_hrtim_get_locked_fault_count,

  helper_hrtim_convert_timer,

  helper_hrtim_extract_unit_number,

  helper_hrtim_is_event_relevant_to_output,

  helper_hrtim_is_event_relevant_to_capture,

  helper_hrtim_is_blanking_relevant_to_timer,

  helper_hrtim_is_windowing_relevant_to_timer,

  helper_hrtim_is_event_relevant_to_adc_trigger,

  helper_hrtim_is_enabled_interrupt_source,

  helper_hrtim_get_fault_blanking_mode,

  helper_hrtim_convert_source,

  helper_hrtim_convert_update_gating,

  helper_hrtim_convert_reset_trigger_source,

  helper_hrtim_convert_capture_trigger_source,

  helper_hrtim_convert_adc_trigger_id,

  helper_hrtim_convert_adc_trigger_source,

  helper_hrtim_convert_event_filter,

  helper_hrtim_convert_output_set_reset_event,

  helper_hrtim_convert_dual_channel_dac_trigger,

  helper_hrtim_convert_burst_mode_clock,

  helper_hrtim_convert_burst_mode_trigger,

  helper_hrtim_get_output_channel,

  helper_hrtim_get_max_interrupt_request_sources,

  helper_hrtim_get_max_dma_request_sources,

  helper_hrtim_is_hrtim_io_connected_to_gpio,

  helper_hrtim_is_needed_gpio_settings,

  helper_hrtim_dbg_log,

  helper_hrtim_is_selected_interrupt_source,

  helper_hrtim_is_selectable_value,

  helper_hrtim_is_selectable_set_reset_source,

  helper_hrtim_is_selectable_counter_reset_source,

  helper_hrtim_is_selectable_timer_event,

  helper_hrtim_is_selectable_update_source,

  helper_hrtim_is_selectable_capture_trigger_source,

  helper_hrtim_is_selectable_external_event,

  helper_hrtim_is_selectable_adc_trigger_update_source,

  helper_hrtim_is_selectable_adc_trigger_source,

  helper_hrtim_is_selectable_crossbar_override_trigger_source,
  
  helper_hrtim_is_selectable_crossbar_override_forcing_event,
  
  helper_hrtim_is_selectable_dma_trigger,

  helper_hrtim_is_used_delayed_protection,

  helper_hrtim_is_supported_event_feature,

  helper_hrtim_is_enabled_pushpull,

  helper_hrtim_get_combined_event_source_name,

  helper_hrtim_get_combined_event_source_value,

  helper_hrtim_get_crossbar_override_external_trigger,

  helper_hrtim_get_crossbar_configuration,

  helper_hrtim_convert_to_ll_filter,

  helper_hrtim_remove_substring,

  helper_hrtim_format_ll_triggers_selection,

  helper_hrtim_format_ll_capture_triggers_selection,

  helper_hrtim_format_ll_update_gating,

  helper_hrtim_format_ll_roll_over_mode,

  helper_hrtim_format_ll_auto_delayed_mode,

  helper_hrtim_format_ll_delayed_protection_mode,

  helper_hrtim_format_ll_faults_selection,

  helper_hrtim_replace_substring,

  helper_hrtim_define_ll_hrtim_dier_mask,

  helper_hrtim_define_ll_master_timer_dier_mask,

  helper_hrtim_define_ll_timx_dier_mask,
};
