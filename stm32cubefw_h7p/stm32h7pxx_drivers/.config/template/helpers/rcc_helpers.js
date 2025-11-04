
/**
 * @file Helpers functions used for RCC SW component
 * @author GPM Application Team
 * @license
 * Copyright (c) 2025 STMicroelectronics.
 * All rights reserved.
 *
 * This software is licensed under terms that can be found in the LICENSE file
 * in the root directory of this software component.
 * If no LICENSE file comes with this software, it is provided AS-IS.
 */

/* Private constants -----------------------------------------------------------------------------------------------*/

/* Mapping between Clock tree json file and helper file */
const C5_IDS = {
  System_Clock_Source: "System_Clock_Source",
  HCLK: "AHB_Clock"
};

/* Map of the clock source - For kernel clock source generated code*/
const map_clock_source = {
  System: "SYSTEM",
  System_Clock_Source: "SYSTEM",
  System_Clock_Frequency: "SYSTEM",
  LSI_Divider_RTC: "LSI",
  HCLK_Frequency: "HCLK",
  AHB1_Peripheral_Clock: "HCLK1",
  AHB2_Peripheral_Clock: "HCLK2",
  AHB3_Peripheral_Clock: "HCLK3",
  AHB4_Peripheral_Clock: "HCLK4",
  AHB5_Peripheral_Clock: "HCLK5",
  APB1_Peripheral_Clock: "PCLK1",
  PCLK1_Input_Clock: "PCLK1",
  CKPER_Input_Clock: "PER",
  TIM_Input_Clock: "TIMX",
  APB2_Peripheral_Clock: "PCLK2",
  PCLK2_Input_Clock: "PCLK2",
  APB3_Peripheral_Clock: "PCLK3",
  PCLK3_Input_Clock: "PCLK3",
  APB4_Peripheral_Clock: "PCLK4",
  PCLK4_Input_Clock: "PCLK4",
  APB1_divider: "PCLK1",
  APB2_divider: "PCLK2",
  APB3_divider: "PCLK3",
  AUDIO_Source: "AUDIOCLK",
  HSE_Divider_RTC: "HSE_DIV",
  HSEDIV: "HSE_DIV",
  RCC_TIM: "TIM",
  RCC_HRTIM: "HRTIM",
  ADC_DIV:"ADC",
  DIVQ1: 'PLL1Q',
  DIVQ2: 'PLL2Q',
  DIVP2: 'PLL2P',
  DIVR2: 'PLL2R',
  DIVS2: 'PLL2S',
  DIVT2: 'PLL2T',
  DIVP3: 'PLL3P',
  DIVR3: 'PLL3R',
  DIVQ3: 'PLL3Q',
  HSIDIV: "HSI",
  HRTPRE: "HRTIM",
  HPRE: "BUS",
  ADCDIV: "ADC",
  HCLK4_Input_Clock: "HCLK4"
};

const map_divider_source = {
  ADCDIV: 'ADC_Clock_Source',
  HSIDIV: 'HSI',
  DIVQ1: 'PLL1Q',
  DIVQ2: 'PLL2Q',
  DIVP2: 'PLL2P',
  DIVR2: 'PLL2R',
  DIVS2: 'PLL2S',
  DIVT2: 'PLL2T',
  DIVP3: 'PLL3P',
  DIVR3: 'PLL3R',
  DIVQ3: 'PLL3Q'
}

/* Map of the resources kernel clock : used for the kernel clock source selection */
const map_kernel_clock = {
  ADC1:   "ADC",
  ADC2:   "ADC",
  ADC3:   "ADC",
  ADC4:   "ADC",
  FDCAN1: "FDCAN",
  FDCAN2: "FDCAN",
  FDCAN3: "FDCAN",
  I2C1:   "I2C123",
  I2C2:   "I2C123",
  I2C3:   "I2C123",
  SPI2:   "SPI23",
  SPI3:   "SPI23",
  SPI4:   "SPI45",
  SPI5:   "SPI45",
  USART1: "USART16910",
  USART2: "UART234578",
  USART3: "UART234578",
  UART4:  "UART234578",
  UART5:  "UART234578",
  USART6: "USART16910",
  UART7:  "UART234578",
  UART8:  "UART234578",
  UART9:  "USART16910",
  USART10: "USART16910",
  LPTIM2: "LPTIM23",
  LPTIM3: "LPTIM23",
  LPTIM4: "LPTIM45",
  LPTIM5: "LPTIM45"
};

/* Map of the hw resource name: used for bus clock enable / disable */
const map_hw_resource_name = {
  ADC1: "ADC12",
  ADC2: "ADC12",
  ADC3: "ADC34",
  ADC4: "ADC34",
  COMP1: "COMP12",
  COMP2: "COMP12",
  COMP3: "COMP34",
  COMP4: "COMP34",
  COMP5: "COMP56",
  COMP6: "COMP56",
  COMP7: "COMP78",
  COMP8: "COMP78",
  FDCAN1: "FDCAN",
  FDCAN2: "FDCAN",
  FDCAN3: "FDCAN",
  VREFBUF: "VREF",
  RTC:    "RTCAPB",
};

/* Map of the hw resource name that have an inbependant Kernel Clock name */
const map_hw_kernel_resource_name = {

};

/* Map of the sw resource name (used in ll kernel clock source) */
const map_sw_resource_name = {
  RNG: "CK48",
};

/* Map of the resources (peripherals) name - To build the configuration path, form PPP to clock source */
const map_resources_name_for_configuration = {
  ADC1: "ADCDIV",
  FDCAN1: "FDCAN_Clock_Source",
  FDCAN2: "FDCAN_Clock_Source",
  FDCAN3: "FDCAN_Clock_Source",
  USART2: "UART234578_Clock_Source",
  USART3: "UART234578_Clock_Source",
  USART4: "UART234578_Clock_Source",
  USART5: "UART234578_Clock_Source",
  USART7: "UART234578_Clock_Source",
  USART8: "UART234578_Clock_Source",
  USART1: "UART16910_Clock_Source",
  USART6: "UART16910_Clock_Source",
  USART9: "UART16910_Clock_Source",
  USART10: "UART16910_Clock_Source",
  SPI2: "SPI23_Clock_Source",
  SPI3: "SPI23_Clock_Source",
  SPI4: "SPI45_Clock_Source",
  SPI5: "SPI45_Clock_Source",
  I2C1: "I2C123_Clock_Source",
  I2C2: "I2C123_Clock_Source",
  I2C3: "I2C123_Clock_Source",
  SDMMC1: "SDMMC_Clock_Source",
  SDMMC2: "SDMMC_Clock_Source",
  XSPI1: "XSPI_Clock_Source",
  RNG: "HSI48"
};

/* Map of the resources (peripherals) name - to get the kernel clock source */
const map_resources_name_for_kernel_source = {
  ADC1: "ADC_Clock_Source",
  ADC2: "ADC_Clock_Source",
  ADC3: "ADC_Clock_Source",
  ADC4: "ADC_Clock_Source",
  FDCAN1: "FDCAN_Clock_Source",
  FDCAN2: "FDCAN_Clock_Source",
  FDCAN3: "FDCAN_Clock_Source",
  XSPI1: "XSPI_Clock_Source"
};

/* List of the external clock source */
const external_clock_source = [
  "HSE",
  "LSE"
];

/* List of the resources that does not include an enable bit */
/* This bit could be present in some product */
const resource_wo_enable = [
  'PWR',
];

/* List of the resources that does not include an enable switch */
const resource_wo_kernel_enable = [
'AES',
'TIM1',
'TIM2',
'TIM3',
'TIM4',

'TIM5',
'TIM6',
'TIM7',
'TIM8',
'TIM15',
'TIM16',
'RNG'
];

/* List of the resources that share its clock enable / reset bit with another resource */
const resource_sharing_enable_bit = [
  'FDCAN1',
  'FDCAN2',
  'FDCAN3',
  'ADC1',
  'ADC2',
];

/* List of DACs */
const dac_resources = [
  'DAC1',
  'DAC2',
  'DAC3',
  'DAC4',
  'DAC5',
  'DAC6',
  'DAC7',
  'DAC8',
  'DAC9',
  'DAC10'
];

const available_sys_clk_src = {
    HSIDIV: "HSI",
    HSE: "HSE",
    CSI: "CSI",
    DIVP1: "PLLCLK"
  };

const available_systick_src = {
  CPRE_DIV8: "CPU_SYS_INPUT_Clock"
};

const default_systick_src = "CPRE_DIV8";

const map_mco_src = {
  System_Clock_Frequency: 'SYSTEM',
  HSIDIV: 'HSI',
  HSI:    "HSI",
  LSE:    "LSE",
  HSE:    "HSE",
  DIVP1:  'PLL1',
  DIVQ1:  'PLL1',
  DIVP2:  'PLL2',
  HSI48:  "HSI48"
};

/* Peripheral to Group mapping */
  const peripheralBusMapping = {

  /* AHB1 GRP1 PERIPH */
  HSP:      "AHB1_GRP1",
  GPDMA1:   "AHB1_GRP1",
  OTGFS:    "AHB1_GRP1",
  ADF1:     "AHB1_GRP1",

  /* AHB2 GRP1 PERIPH */
  CORDIC:   "AHB2_GRP1",
  FMAC1:    "AHB2_GRP1",
  AHBSRAM1: "AHB2_GRP1",
  AHBSRAM2: "AHB2_GRP1",
  AHBSRAM3: "AHB2_GRP1",
  FMAC:     "AHB2_GRP1",

  /* AHB3 GRP1 PERIPH */
  ADC1:     "AHB3_GRP1",
  ADC2:     "AHB3_GRP1",
  ADC3:     "AHB3_GRP1",
  ADC4:     "AHB3_GRP1",
  DAC1:     "AHB3_GRP1",
  DAC2:     "AHB3_GRP1",
  DAC3:     "AHB3_GRP1",
  DAC4:     "AHB3_GRP1",
  HASH:     "AHB3_GRP1",
  RNG:      "AHB3_GRP1",

  /* AHB4 GRP1 PERIPH */
  GPIOA:    "AHB4_GRP1",
  GPIOB:    "AHB4_GRP1",
  GPIOC:    "AHB4_GRP1",
  GPIOD:    "AHB4_GRP1",
  GPIOE:    "AHB4_GRP1",
  GPIOF:    "AHB4_GRP1",
  GPIOG:    "AHB4_GRP1",
  GPIOH:    "AHB4_GRP1",
  GPIOI:    "AHB4_GRP1",
  CRC:      "AHB4_GRP1",

  /* AHB5 GRP1 PERIPH */
  HPDMA1:   "AHB5_GRP1",
  FMC:      "AHB5_GRP1",
  XSPI1:    "AHB5_GRP1",
  SDMMC1:   "AHB5_GRP1",
  NPU:      "AHB5_GRP1",
  FLASH:    "AHB5_GRP1",
  AXISRAM:  "AHB5_GRP1",
  DTCM1:    "AHB5_GRP1",
  DTCM2:    "AHB5_GRP1",
  ITCM:     "AHB5_GRP1",

  /* APB1 GRP1 PERIPH */
  TIM2:     "APB1_GRP1",
  TIM3:     "APB1_GRP1",
  TIM4:     "APB1_GRP1",
  TIM5:     "APB1_GRP1",
  TIM6:     "APB1_GRP1",
  TIM7:     "APB1_GRP1",
  TIM10:    "APB1_GRP1",
  TIM11:    "APB1_GRP1",
  TIM12:    "APB1_GRP1",
  TIM13:    "APB1_GRP1",
  TIM14:    "APB1_GRP1",
  LPTIM1:   "APB1_GRP1",
  WWDG:     "APB1_GRP1",

  /* APB1 GRP1 PERIPH */
  SPI2:     "APB1_GRP1",
  SPI3:     "APB1_GRP1",
  USART2:   "APB1_GRP1",
  USART3:   "APB1_GRP1",
  UART4:    "APB1_GRP1",
  UART5:    "APB1_GRP1",
  UART4:    "APB1_GRP1",
  UART7:    "APB1_GRP1",
  UART8:    "APB1_GRP1",
  I2C1:     "APB1_GRP1",
  I2C2:     "APB1_GRP1",
  I2C3:     "APB1_GRP1",
  I3C1:     "APB1_GRP1",

  /* APB1 GRP2 PERIPH */
  CRS:      "APB1_GRP2",
  DTS:      "APB1_GRP2",
  FDCAN:    "APB1_GRP2",
  UCPD1:    "APB1_GRP2",

  /* APB2 GRP1 PERIPH */
  TIM1:     "APB2_GRP1",
  TIM8:     "APB2_GRP1",
  TIM2:     "APB2_GRP1",
  USART1:   "APB2_GRP1",
  USART6:   "APB2_GRP1",
  UART9:    "APB2_GRP1",
  USART10:  "APB2_GRP1",
  SPI1:     "APB2_GRP1",
  SPI4:     "APB2_GRP1",
  TIM15:    "APB2_GRP1",
  TIM16:    "APB2_GRP1",
  TIM17:    "APB2_GRP1",
  TIM9:     "APB2_GRP1",
  SPI5:     "APB2_GRP1",
  HRTIM1:   "APB2_GRP1",
  HRTIM2:   "APB2_GRP1",

  /* APB4 GRP1 PERIPH */
  SBS:      "APB4_GRP1",
  LPUART1:  "APB4_GRP1",
  SPI6:     "APB4_GRP1",
  LPTIM2:   "APB4_GRP1",
  LPTIM3:   "APB4_GRP1",
  LPTIM4:   "APB4_GRP1",
  LPTIM5:   "APB4_GRP1",
  VREFBUF:  "APB4_GRP1",
  RTC:      "APB4_GRP1",
  DTS:      "APB4_GRP1",
  COMP1:    "APB4_GRP1",
  COMP2:    "APB4_GRP1",
  COMP3:    "APB4_GRP1",
  COMP4:    "APB4_GRP1",
  COMP5:    "APB4_GRP1",
  COMP6:    "APB4_GRP1",
  COMP7:    "APB4_GRP1",
  COMP8:    "APB4_GRP1"
};

// Group to Clock mapping
const groupClockMapping = {
  AHB1_GRP1: "HCLK1",
  AHB2_GRP1: "HCLK2",
  AHB3_GRP1: "HCLK3",
  AHB4_GRP1: "HCLK4",
  APB1_GRP1: "PCLK1",
  APB1_GRP2: "PCLK1",
  APB2_GRP1: "PCLK2",
  APB4_GRP1: "PCLK4"
};

/* Definition of the clock configuration strategy */
const rcc_config_codes = {
  CENTRAL: 0,
  CONTROLLED_BY_PERIPHERALS: 1,
  CONTROLLED_BY_USER: 2
};


/* Private Global variables -----------------------------------------------------------------------------------------------*/
let g_rcc_api = null;                     /* The list of global APIs */
let g_core_info = null;                   /* Object containing the core information setting */
let g_rcc_main_config = null;             /* Object containing the rcc json parameter user confguration */
let g_rcc_clock_tree_config = null;       /* Object containing the rcc clock tree user configuration */
let g_rcc_all_resources = null;           /* Object containing the rcc bound resources */
let g_all_perifs_clock_config = null;     /* Object containing the rcc bound resources clock configurations */

const g_rcc_resource_state = {};            /* Object containing the resources that are enabled (clocks, pll, config)*/

/* Private function ------------------------------------------------------------------------------------------------*/

/**
 * Retrieve the clock information of the selected resource and add it in the all_periphs_config_object
 * This function all PPP configuration, from this PPP to clock source.
 * It thus get clock sources, dividers, PLL configurations
 * @param {string} resource_name HW resource name(ex ADC1)
 * @param {object} all_periphs_config_object Current result of the clock configuration
 * @returns {object} Return an updated of the object current_ctxt
 * ex {
 * "HCLK": {
 *    "resources": [
 *       "ADC1",
 *       "ADC4",
 *       "DAC1",
 *       "MDF1"
 *    ],
 *    "frequency": 160000000,
 *    "present": true
 * },
 * "PLL1": {
 *    "resources": [
 *       "FDCAN1"
 *    ],
 *    "Q": {
 *       "resources": [
 *          "FDCAN1"
 *       ],
 *       "present": true
 *    },
 *    "present": true
 * },
 * "PCLK1": {
 *    "resources": [
 *       "I2C1",
 *       "LPTIM2",
 *       "USART3"
 *    ],
 *    "frequency": 160000000,
 *    "present": true
 * },
 *}
 */
function rcc_get_pppi_configurations(
  resource_name,
  all_periphs_config_object
) {
  let result = all_periphs_config_object;
  if (result == null) {
    result = {};
  }

  try {
    console.log(`[INFO] rcc_get_pppi_configurations: resource=${resource_name}`);

    /* Build the configuration path of the resource */
    let current_resource = resource_name;

    let clock_source_id;
    if (map_resources_name_for_configuration.hasOwnProperty(resource_name)) {
      clock_source_id = map_resources_name_for_configuration[resource_name];
    }
    else{
      clock_source_id = resource_name + '_Clock_Source';
    }

    let done = false;
    let loop_counter = 0;

    while (!done)
    {
      /* Is it a PLL ? */
      const pll_output_found = clock_source_id.match(/(PLL)(\d)([A-Z])/);
      if (pll_output_found){
        const pll_name ='PLL' + pll_output_found[2];
        const pll_div_name = 'DIV' + pll_output_found[3] + pll_output_found[2];

        let clock_fy = g_rcc_api.clockAPI.getClockFrequency(pll_div_name);
        add_resource_clock_source(result, pll_name, clock_fy, resource_name);

        clock_source_id = clock_object.value;
        current_resource = pll_name;
      }
      else
      {
        let clock_object = g_rcc_api.clockAPI.getClockInformationById(clock_source_id);
        if(clock_object)
        {
          if (clock_object.type == 'multiplexor')
          {
            clock_source_id = clock_object.value;

            /* remap divider source id if needed */
            if (map_divider_source.hasOwnProperty(clock_source_id)) {
              clock_source_id = map_divider_source[clock_source_id];
            }

            if (map_clock_source.hasOwnProperty(clock_source_id)) {
              clock_source_id = map_clock_source[clock_source_id];
            }

            add_resource_clock_source(result, clock_source_id, clock_object.frequency, resource_name);
            current_resource = clock_source_id;
          }
          else if (clock_object.type == 'divider')
          {
            add_resource_clock_source(result, clock_source_id, clock_object.frequency, current_resource);
            current_resource = clock_source_id;
            if (map_divider_source.hasOwnProperty(clock_source_id))
            {
              clock_source_id = map_divider_source[clock_source_id];
            }
            else
            {
              done = true;
              console.log(`[INFO] rcc_get_pppi_configurations: resource=${resource_name}. DONE`);
            }
          }
          else if (clock_source_id != current_resource)
          {
            add_resource_clock_source(result, clock_source_id, clock_object.frequency, current_resource);
            done = true;
            console.log(`[INFO] rcc_get_pppi_configurations: resource=${resource_name}. DONE`);
          }
          else
          {
            done = true;
            console.log(`[INFO] rcc_get_pppi_configurations: resource=${resource_name}. DONE: Exit 0`);
          }
        }
        else
        {
          /* PPP not present on clock tree - RCC, ICACHE... */
          done = true;
          console.log(`[INFO] rcc_get_pppi_configurations: resource=${resource_name}. DONE: Exit 1`);

        }
      }

      /* Prevent infinite loops */
      loop_counter++;
      if (loop_counter>10)
      {
        done = true;
        console.log(`[INFO] rcc_get_pppi_configurations: resource=${resource_name}. DONE: Exit 2`);
      }
    }

  } catch (error) {
    console.log(`[ERROR] rcc_get_pppi_configurations: ${error}`);
  }
  return result;
}

function add_resource_clock_source(result, source_name, source_frequency, resource_name){


  console.log(`[INFO] rcc_get_pppi_configurations: resource=${resource_name}. New node: ${source_name}`);
  /* Create the Source Name */
  if (!result.hasOwnProperty(source_name)) {
    result[source_name] = { resources: [] };
  }
  /* Populate resource informations if not already done */
  if (result[source_name]["resources"].indexOf(resource_name) < 0) {
    result[source_name]["resources"].push(resource_name);
    result[source_name]["frequency"] = source_frequency;
    if (external_clock_source.includes(source_name)) {
      result[source_name]["is_external"] = true;
    }
    else
    {
      result[source_name]["is_external"] = false;
    }
  }
}

/**
 * Retrieve the Flash latency from system targeted frequency
 * @returns null if latency not found, the latency [string] otherwise
 */
function find_system_clock_src() {
  let ok = false;
  let object = {
    HSI: false,
    HSE: false,
    CSI: false,
    PLLCLK: false,
    name:"HSI",
    frequency: 64000000,
  }

  try {
    let clock_source_object = g_rcc_api.clockAPI.getClockInformationById('System_Clock_Source');
    let clock_source_name = clock_source_object.value;

    if (available_sys_clk_src.hasOwnProperty(clock_source_name)) {
      ok = true;
      let remapped_name = available_sys_clk_src[clock_source_name];
      object.name = remapped_name;
      object[remapped_name] = true;
      object.frequency = clock_source_object.frequency;
    } else {
      console.log(
        `[ERROR] helper_rcc find_system_clock_src: ${clock_source_name} not part of the available_sys_clk_src - using default`
      );
    }
  } catch  (error) {
    console.error(`[ERROR] find_system_clock_src: ${error}`);
  }

  return {ok, object};
}

/**
 * Retrieve the system prescalers
 * @returns {object} Returns "ok", the execution status (true/false) and "object" containing the prescalers
 * ex:
 * {
 *   ok: true,
 *   object:{
 *     cpu: 1,
 *     ahb: 1,
 *     apb1: 2,
 *     apb2: 4,
 *     apb4: 8
 *    }
 * }
 */
function find_system_prescaler() {
  let ok = false;
  let object = {
    cpu: 1,
    ahb: 1,
    apb1: 1,
    apb2: 1,
    apb4: 1,
  }

  try {
    object.cpu = g_rcc_api.clockAPI.getClockInformationById('CPRE').value;
    object.ahb = g_rcc_api.clockAPI.getClockInformationById('BMPRE').value;
    object.apb1 = g_rcc_api.clockAPI.getClockInformationById('APB1_Clock_Divider').value;
    object.apb2 = g_rcc_api.clockAPI.getClockInformationById('APB2_Clock_Divider').value;
    object.apb4 = g_rcc_api.clockAPI.getClockInformationById('APB4_Clock_Divider').value;
    ok = true;
  }
  catch  (error) {
    console.error(`[ERROR] find_system_prescaler: ${error}`);
  }
  return {ok, object};
}

function find_clock_divider(){
  let ok = false;
  let object = {
    hsi: '1',
    adc: '1',
  }

  try {
    object.hsi = g_rcc_api.clockAPI.getClockInformationById('HSIDIV')?.value;
    object.adc = g_rcc_api.clockAPI.getClockInformationById('ADCDIV')?.value;

    ok = true;
  }
  catch  (error) {
    console.error(`[ERROR] find_clock_divider: ${error}`);
  }

  return {ok, object};
}


/**
 * Retrieve the systick clock source
 * @returns {object} Returns "ok", the execution status (true/false) and "object" containing the prescalers
 * ex:
 * {
 *   ok: true,
 *   object:{
 *     ahb: 1,
 *     apb1: 2,
 *     apb2: 4,
 *     apb4: 8
 *    }
 * }
 */
function find_systick_clock_src() {
  let ok = false;
  let object = {
    CPRE_DIV8: false,
    name:"CPRE_DIV8",
    is_default: false
  }

  try {
    let clock_source_object = g_rcc_api.clockAPI.getClockInformationById('CPRE_DIV8');
    let clock_source_name = clock_source_object.id;

    if (available_systick_src.hasOwnProperty(clock_source_name)) {
      ok = true;
      let remapped_name = available_systick_src[clock_source_name];
      object.name = remapped_name;
      object[remapped_name] = true;
      //if (remapped_name == default_systick_src)
      //  object.is_default = true;
    } else {
      console.log(
        `[ERROR] helper_rcc find_systick_clock_src: ${clock_source_name} not part of the available_systick_src - using default`
      );
    }
  } catch  (error) {
    console.error(`[ERROR] find_systick_clock_src: ${error}`);
  }

  return {ok, object};
}

function find_clk_outputs_config() {
  let ok = false;
  let object = {
    mco1: {src: 'HSI', div: 1},
    mco2: {src: 'SYSTEM', div: 1}
  }

  try {
    let src = g_rcc_api.clockAPI.getClockInformationById('MCO1_Clock_Source').value;
    if (map_mco_src.hasOwnProperty(src)) {
      src = map_mco_src[src];
    }
    object.mco1.src = src;

    src = g_rcc_api.clockAPI.getClockInformationById('MCO2_Clock_Source').value;
    if (map_mco_src.hasOwnProperty(src)) {
      src = map_mco_src[src];
    }
    object.mco2.src = src;

    object.mco1.div = g_rcc_api.clockAPI.getClockInformationById('MCO1_div_Clock').value;
    object.mco2.div = g_rcc_api.clockAPI.getClockInformationById('MCO2_div_Clock').value;

    ok = true;
  }
  catch  (error) {
    console.error(`[ERROR] find_clk_outputs_config: ${error}`);
  }
  return {ok, object};
}


/**
 * Retrieve the configuration of the PLLx (x = 1, 2 or 3)
 * @param {integer} pll_id PLL id value ("", 2 or 3) => for PLL1 id is empty
 * @returns Object => {
 *    "PLLFRACN": "",
 *    "PLLSource": "HAL_RCC_PLL_SRC_MSIS",
 *    "MSIS": true,
 *    "PLL1N": 129,
 *    "PLL1M": 1,
 *    "PLL1P": 2,
 *    "PLL1Q": 2,
 *    "PLL1R": 2,
 *    "PLL1S": 2
 *    "PLL1T": 2
 *}
 */
function find_pll_config(pll_name) {

  let ok = false;
  let object = {
    src: 'HSI',
    m: 1,
    n: 1,
    p: 1,
    q: 1,
    r: 1,
    s: 1,
    t: 1,
    fracn: 1,
    input_range: "1_2",
    vco_range: "128_560",
  }

  const map_pll_clk_src = {
    HSE: "HSE",
    HSIDIV: "HSI",
    CSI: "CSI",
  };

  try {
    let src = g_rcc_api.clockAPI.getClockInformationById('PLL_Clock_Source').value;
    if (map_pll_clk_src.hasOwnProperty(src)) {
      src = map_pll_clk_src[src];
    }
    object.src = src;

    object.m = g_rcc_api.clockAPI.getClockInformationById('DIVM' + pll_name).value;
    object.n = g_rcc_api.clockAPI.getClockInformationById('DIVN' + pll_name).value;
    object.p = g_rcc_api.clockAPI.getClockInformationById('DIVP' + pll_name).value;
    object.q = g_rcc_api.clockAPI.getClockInformationById('DIVQ' + pll_name).value;
    object.r = g_rcc_api.clockAPI.getClockInformationById('DIVR' + pll_name).value;
    object.s = g_rcc_api.clockAPI.getClockInformationById('DIVS' + pll_name).value;
    object.t = g_rcc_api.clockAPI.getClockInformationById('DIVT' + pll_name).value;
    object.fracn = g_rcc_api.clockAPI.getClockInformationById('PLL' + pll_name + 'FRACN').value;

    ok = true;
  }
  catch  (error) {
    console.error(`[ERROR] find_pll_config: ${error}`);
  }
  return {ok, object};
}

/* This function checks if the user selected flash latency is possible. If no, it returns the optimal flash latency for current frequency */
function adjust_flash_latency(system_clock_frequency, selected_latency)
{
  let latency = selected_latency;
  const optimal_latency = helper_rcc_get_optimal_latency(system_clock_frequency);
  if (latency < optimal_latency)
  {
    latency = optimal_latency;
  }
  return latency;
}

/* This function checks if the user selected flash programming delay is possible. If no, it returns the optimal flash programming delay for current frequency */
function adjust_flash_programming_delay(system_clock_frequency, selected_programming_delay)
{
  let programming_delay = selected_programming_delay;
  const optimal_programming_delay = helper_rcc_get_optimal_programming_delay(system_clock_frequency);
  if (programming_delay < optimal_programming_delay)
  {
    programming_delay = optimal_programming_delay;
  }
  return programming_delay;
}



/* Exported functions ----------------------------------------------------------------------------------------------*/

/**
 * Globalize the application API, for them to be usable anywhere in helpers
 * @param {object} root is program root
 * @returns None
 */
function helper_rcc_init_codegen(root){
  if (g_rcc_api == null){
    g_rcc_api = {}

    g_rcc_api['SWConfigurationAPI'] = root.SWConfigurationAPI;
    g_rcc_api['peripheralsResourceManagerAPI'] = root.peripheralsResourceManagerAPI;
    g_rcc_api['clockAPI'] = root.clockAPI;

    console.log(`[INFO] helper_rcc_init_codegen: initialization successful`);
  }
}

/**
 * Retrieve context information (user inputs)
 * @param {string} componentId is the identifier of the component as referenced by SW Config in its store,
 *                             or a meaningful subpart of the full componentId.
*                              example: "STMicroelectronics::Device:STM32CubeMX2 Config:RCC"
 * @returns {object} The context (user input)
 */
function helper_rcc_get_context(componentId) {
  let context;
  try {
    const instance = g_rcc_api.SWConfigurationAPI.getInstances(componentId);
    const configuration = g_rcc_api.SWConfigurationAPI.getInstanceConfiguration(instance[0]);
    context = configuration.settings.parameters;
  } catch (error) {
    console.error(`[ERROR] helper_rcc_get_context: ${error}`);
    return null;
  }
  return context;
}

/**
 * Retrieve RCC main configuration
 * @param  None
 * @returns The RCC config (user input)
 */
function helper_rcc_get_rcc_main_config() {
  if (g_rcc_main_config == null){
    try {
      let json = '{"cgroup": "STM32CubeMX2 Config", "csub": "RCC"}';
      let json_obj =JSON.parse(json);
      let configuration = g_rcc_api.SWConfigurationAPI.getInstancesConfiguration(json_obj);
      g_rcc_main_config = configuration[0].settings.parameters;
    } catch (error) {
      console.error(`[ERROR] helper_rcc_get_rcc_main_config: ${error}`);
      return null;
    }
  }
  return g_rcc_main_config;
}

/**
 * Retrieve information for system clock config function generation
 * @details Call in mx_rcc_template.c.hbs (object system_clk_config_object) to fill the function mx_rcc_cfg1_hal_init
 *          This function selects the latency depending on the targeted frequency and VCORE value.
 *          If the targeted frequency does not allow to select a latency, an error will occur
 * @param  None
 * @returns {object} rcc_config, an object containing all information for system configuration
 *{
 *    clock_source,
 *    latency,
 *    prescaler,
 *    frequencies,
 *}
 */
function helper_rcc_get_system_config(main_config) {

  if (g_rcc_clock_tree_config == null){

    try {
      console.log(
        `[INFO] helper_rcc_get_system_config`
      );

      const rcc_config =
      {
        clock_source: undefined,
        systick_source:undefined,
        prescaler:null,
        frequencies:{},
        clk_outputs: null,
        divider: null,
        flash_latency:1,
        flash_programming_delay:0,
        pll_list: [],
      }

      let result;

      /* Build system clcok source object */
      result = find_system_clock_src();
      rcc_config.clock_source = result.object;
      if (result.ok === false){
        console.log(`[ERROR] helper_rcc_get_hal_clock_config_object: default system clock source used`);
      }

      /* Adjust Flash Latency and programming delay */
      rcc_config.flash_latency = adjust_flash_latency(rcc_config.clock_source.frequency, main_config.main.flash_latency);
      rcc_config.flash_programming_delay = adjust_flash_programming_delay(rcc_config.clock_source.frequency, main_config.main.flash_programming_delay);

      /* Find Prescalers */
      result = find_system_prescaler();
      rcc_config.prescaler = result.object;
      if (result.ok === false){
        console.log(`[ERROR] helper_rcc_get_hal_clock_config_object: bus prescaler parsing error`);
      }

      /* Find Systick source */
      result = find_systick_clock_src();
      rcc_config.systick_source = result.object;
      if (result.ok === false){
        console.log(`[ERROR] helper_rcc_get_hal_clock_config_object: systick parsing error`);
      }

      /* Find the clock dividers */
      result = find_clock_divider();
      rcc_config.divider = result.object;
      if (result.ok === false){
        console.log(`[ERROR] helper_rcc_get_hal_clock_config_object: clock divider parsing error`);
      }

      /* Fill in Frequencies */
      rcc_config.frequencies['default'] = g_rcc_api.clockAPI.getClockFrequency("HSI"); /* Default clock is HSI */
      rcc_config.frequencies['system'] = rcc_config.clock_source.frequency;
      rcc_config.frequencies['ahb'] = g_rcc_api.clockAPI.getClockFrequency("AHB1_Peripheral_Clock");
      rcc_config.frequencies['cpu'] = g_rcc_api.clockAPI.getClockFrequency("CPU_Sys_Input_Clock");

      /* Find MCO configs */
      result = find_clk_outputs_config();
      rcc_config.clk_outputs = result.object;
      if (result.ok === false){
        console.log(`[ERROR] helper_rcc_get_hal_clock_config_object: mco parsing error`);
      }

      /* Build pll_list */
      const pll1_object = {
        name: "PLL1",
        idx: 1,
        config: null,
        factors: ['m', 'n'],
        outputs: ['p', 'q', 'r', 's', 't'],
      };

      result = find_pll_config('1');
      pll1_object.config = result.object;
      if (result.ok === false){
        console.log(`[ERROR] helper_rcc_get_hal_clock_config_object: pll1 parsing error`);
      }
      rcc_config.pll_list.push(pll1_object);

      const pll2_object = {
        name: "PLL2",
        idx: 2,
        config: null,
        factors: ['m', 'n'],
        outputs: ['p', 'q', 'r', 's', 't'],
      };

      result = find_pll_config('2');
      pll2_object.config = result.object;
      if (result.ok === false){
        console.log(`[ERROR] helper_rcc_get_hal_clock_config_object: pll2 parsing error`);
      }
      rcc_config.pll_list.push(pll2_object);


      const pll3_object = {
        name: "PLL3",
        idx: 3,
        config: null,
        factors: ['m', 'n'],
        outputs: ['p', 'q', 'r', 's', 't'],
      };

      result = find_pll_config('3');
      pll3_object.config = result.object;
      if (result.ok === false){
        console.log(`[ERROR] helper_rcc_get_hal_clock_config_object: pll3 parsing error`);
      }
      rcc_config.pll_list.push(pll3_object);

      console.log(`[INFO] helper_rcc_get_system_config: ${JSON.stringify(rcc_config)}`);
        g_rcc_clock_tree_config = rcc_config;
    } catch (error) {
      console.error(`[ERROR] helper_rcc_get_system_config: ${error}`);
        g_rcc_clock_tree_config = {};
    }
  }
  return g_rcc_clock_tree_config;
}

/**
 * Retrieve the list of resources (IPs) bound to at least one software component instance
 * @param  None
 * @returns {object} A list of resources name
 */
function helper_rcc_get_all_resources() {
  if (g_rcc_all_resources == null){
    g_rcc_all_resources = g_rcc_api.peripheralsResourceManagerAPI.getPeripheralsBoundToSoftwareInstances();
  }
  return g_rcc_all_resources;
}

/**
* Retrieve the clock information of the all bound resources
* @param {object} all_resources, the list of bound resources name (get with helper_rcc_get_all_resources)
* @returns {object} A list of clock objects. Each clock object includes the clock frequency, the is_external property and the list of resource using this clock as source
 * ex {
 * "HCLK": {
 *    "resources": [
 *       "ADC1",
 *       "ADC4",
 *       "DAC1",
 *       "MDF1"
 *    ],
 *    "frequency": 160000000,
 * },
 * "PCLK1": {
 *    "resources": [
 *       "I2C1",
 *       "LPTIM2",
 *       "USART3"
 *    ],
 *    "frequency": 160000000,
 * },
 * "LSE": {
 *    "resources": [
 *       "I2C2",
 *       "LPTIM1",
 *       "USART5"
 *    ],
 *    "frequency": 32768,
 * },
 *}
 */
function helper_rcc_get_all_perifs_clock_config(all_resources) {
  if (g_all_perifs_clock_config == null){
    try {
      let result_object = null;
      all_resources.forEach((/** @type {string} */ resource_name) => {
        result_object = rcc_get_pppi_configurations(resource_name, result_object);
      });
      g_all_perifs_clock_config = result_object;
      console.log(`All perif clock config =${JSON.stringify(g_all_perifs_clock_config)}`);
    }catch (error) {
        console.error(`[ERROR] helper_rcc_get_all_perifs_clock_config: ${error}`);
    }
  }
  return g_all_perifs_clock_config;
}

/**
 * Retrieve the clock information of the one resource
* @param {string} resource_name, the resources name
* @returns {object} One clock object. This clock object includes the clock frequency and the resource using this clock as source.
 */
function helper_rcc_get_one_perif_clock_config(resource_name) {
  let perif_clock_config = rcc_get_pppi_configurations(resource_name, null);

  return perif_clock_config;
}

/**
 * Retrieve the clock source object from the resource name
 * @param {string} resource_name HW resource name(ex ADC1)
 * @returns {object} Return an updated of the object current_ctxt
 */
function helper_rcc_get_clock_source_object(resource_name){
  let clock_source_id
  if (map_resources_name_for_kernel_source.hasOwnProperty(resource_name)) {
    clock_source_id = map_resources_name_for_kernel_source[resource_name];
  }
  else {
    let input_clock_object = g_rcc_api.clockAPI.getClockInformationByHwInstance(resource_name);
    if (input_clock_object){
      clock_source_id = input_clock_object.inputs;
    }
  }
  const clock_source_object = g_rcc_api.clockAPI.getClockInformationById(clock_source_id);
  return clock_source_object;
}

/**
 * Remap the dfp clock source name to driver name
 * @param {string} clock_source, the dfp name of the clock
 * @returns {string} The remapped name
 */
function helper_rcc_remap_clock_source(clock_source)
{
  if (map_clock_source.hasOwnProperty(clock_source)) {
    clock_source = map_clock_source[clock_source];
  }
  return clock_source;
}

/**
 * Remap the hw_resource dfp kernel clock name to driver kernel clock name
 * @param {string} hw_resource, the dfp name of the kernel clock
 * @returns {string} The remapped name
 */
function helper_rcc_remap_kernel_clock_source(hw_resource)
{
  if (map_kernel_clock.hasOwnProperty(hw_resource)) {
    hw_resource = map_kernel_clock[hw_resource];
  }
  return hw_resource;
}

/**
 * Remap the hw_resource name to driver resource name
 * @param {string} hw_resource, the hw resource name
 * @returns {string} The remapped name
 */
function helper_rcc_remap_hw_resource(hw_resource)
{
  if (map_hw_resource_name.hasOwnProperty(hw_resource)) {
    hw_resource = map_hw_resource_name[hw_resource];
  }
  return hw_resource;
}

/**
 * Remap the hw_resource name to driver kernel clock resource name
 * @param {string} hw_resource, the hw resource name
 * @returns {string} The remapped name
 */
function helper_rcc_remap_hw_resource_kernel(hw_resource)
{
  if (map_hw_kernel_resource_name.hasOwnProperty(hw_resource)) {
    hw_resource = map_hw_kernel_resource_name[hw_resource];
  }
  return hw_resource;
}

/**
 * Remap the sw_resource name to driver resource name
 * @param {string} sw_resource, the sw resource name
 * @returns {string} The remapped name
 */
function helper_rcc_remap_sw_resource(sw_resource)
{
  if (map_sw_resource_name.hasOwnProperty(sw_resource)) {
    sw_resource = map_sw_resource_name[sw_resource];
  }
  return sw_resource;
}

/**
 * Retrieve the power voltage scaling
 * @param {{ configs: { pwr_voltage_scaling: string; }[]; }} rcc_cxt the rcc context
 * @returns {string} the power voltage scaling, temporary it does not exist, set to default to range 4
 */
function helper_rcc_get_power_voltage_scaling(rcc_cxt) {
  let pwr_scaling = '1';
  try {
    let pwr_ctx = helper_rcc_get_context('STMicroelectronics::Device:STM32CubeMX2 Config:PWR');
    if (pwr_ctx){
      pwr_scaling = pwr_ctx.configs[0].pwr_voltage_scaling;
    }
  } catch (error) {
    console.error(`[ERROR] helper_rcc_get_power_voltage_scaling: ${error}`);
  }
  return pwr_scaling;
}

/**
 * Check if a resource is a DAC
 * @param {string} resource, the name of the resource
 * @returns {boolean} True or False
 */
function helper_rcc_is_dac(resource){
  let ret = (dac_resources.includes(resource));
  return ret;
}

/**
 * Retrieve the dac sample and hold clock source
 * @param  None
 * @returns {string} The dac sample/hold clock name
 */
function helper_rcc_get_dac_sh_clock(hw_resource){
  let dac_sh_clock_src = ''
  try {
    if (hw_resource == 'DAC1')
       dac_sh_clock_src = g_rcc_api.clockAPI.getClockInformationById('DAC1SH_Clock_Source').value;

  } catch (error) {
    console.error(`[ERROR] helper_rcc_get_dac_sh_clock: ${error}`);
  }
  return dac_sh_clock_src;
}

/**
 * Return True if the resource has an enable. Otherwise, return False;
 * @param {string} hw_resource, the name of the resource
 * @returns {boolean} True or False
 */
function helper_rcc_has_enable(hw_resource) {
  let ret = !(resource_wo_enable.includes(hw_resource));
  return ret;
}

/**
 * Return True if the resource has a kernel clock mux. Otherwise, return False;
 * @param {string} resource, the name of the resource
 * @returns {boolean} True or False
 */
function helper_rcc_has_kernel_clock_mux(resource){
  let ret = !(resource_wo_kernel_enable.includes(resource));
  return ret;
}

/**
 * Return True if the resource shared the same enable/reset bit as another PPP. Otherwise, return False;
 * @param {string} resource, the name of the resource
 * @returns {boolean} True or False
 */
function helper_rcc_is_not_shared_ppp(resource){
  let ret = !(resource_sharing_enable_bit.includes(resource));
  return ret;
}

/**
 * Set the resource 'resource_name' enable state to True
 * @param {string} path_name, the name of the resource (clock, pll, config)
 * @returns None
 */
function helper_rcc_set_resource_enabled(resource_name){
  g_rcc_resource_state[resource_name] = true;
}

/**
 * Get the 'resource_name' enable status
 * @param {string} resource_name, the name of the resource
 * @returns {boolean} True or False
 */
function helper_rcc_is_resource_enabled(resource_name){
  let resource_enable = false;
  if (g_rcc_resource_state.hasOwnProperty(resource_name))
  {
    resource_enable = g_rcc_resource_state[resource_name];
  }
  return resource_enable;
}

/**
 * Check if the SW configuration is "central"
 * @param {object} config, The RCC config
 * @returns {boolean} True or False
 */
function helper_rcc_is_central(config){
  try {
    return (config.main.periph_clocks_init == rcc_config_codes.CENTRAL);
  } catch (error) {
    console.log(`[ERROR] helper_rcc_is_central: ${error}`);
  }
  return false;
}

/**
 * Check if the SW configuration is "controlled by peripheral"
 * @param {object} config, The RCC config
 * @returns {boolean} True or False
 */
function helper_rcc_is_controlled_by_periph(config){
  try {
    return (config.main.periph_clocks_init == rcc_config_codes.CONTROLLED_BY_PERIPHERALS);
  } catch (error) {
    console.log(`[ERROR] helper_rcc_is_controlled_by_periph: ${error}`);
  }
  return false;
}

/**
 * Check if the SW configuration is "controlled by user"
 * @param {object} config, The RCC config
 * @returns {boolean} True or False
 */
function helper_rcc_is_controlled_by_user(config){
  try {
    return (config.main.periph_clocks_init == rcc_config_codes.CONTROLLED_BY_USER);
  } catch (error) {
    console.log(`[ERROR] helper_rcc_is_controlled_by_user: ${error}`);
  }
  return false;
}

/**
 * Get the PPP clock mode defined in CORE
 * @param {string} hw_resource hw_resource to be checked
 * @returns clock mode value:
 *          @arg 0  HAL_CLK_ENABLE_NO                 No clock activation in PPP
 *          @arg 1  HAL_CLK_ENABLE_PERIPH_ONLY        PERIPH Clock activation only
 *          @arg 2  HAL_CLK_ENABLE_PERIPH_PWR_SYSTEM  PERIPH Clock activation including PWR and/or system
 */
function helper_rcc_get_clk_enable_mode(hw_resource) {
  let result = 0;
  console.log(
    `[INFO] helper_common_get_clk_enable_mode: hw_resource=${hw_resource}`
  );
  try {

    /* Get CORE information settings, if not already done */
    if (g_core_info == null){
      const json = '{"cgroup": "STM32CubeMX2 Config", "csub": "CORE"}';
      const json_obj =JSON.parse(json);
      const core_configuration = g_rcc_api.SWConfigurationAPI.getInstancesConfiguration(json_obj);
      g_core_info = core_configuration[0].settings.parameters;
    }

    /* Get component key */
    /* Component is the hw_resource without terminating index except for PPP including several functions (e.g: USART1 can be UART) */
    let component = hw_resource.replace(/\d+$/, '');  /* Remove numbers at the end of string */
    const sw_instance = g_rcc_api.peripheralsResourceManagerAPI.getSoftwareInstancesBoundToPeripheral(hw_resource);
    const sw_config = g_rcc_api.SWConfigurationAPI.getSwInstanceConfiguration(sw_instance[0]);
    if (sw_config.info.function_type) {
      component = sw_config.info.function_type;
    }
    const component_key = component.toLowerCase() + "_feature";

    if (Object.hasOwnProperty.call(g_core_info, component_key)) {
      current_config = g_core_info[component_key];
      if (current_config["clk_enable_model"] === "HAL_CLK_ENABLE_NO") {
        result = 0;
      } else if (
        current_config["clk_enable_model"] === "HAL_CLK_ENABLE_PERIPH_ONLY"
      ) {
        result = 1;
      } else {
        /* HAL_CLK_ENABLE_PERIPH_PWR_SYSTEM */
        result = 2;
      }
    }
  } catch (e) {
    console.error(`[ERROR] helper_rcc_get_clk_enable_mode: ${e}`);
  }

  return result;
}

/**
 * Check if the startup time is available in the configuration
 * @param {any} device
 * @param {{}} board
 * @param {any} vdd
 * @returns {boolean} True or False
 */
function helper_rcc_is_startup_time_available(board){
  let is_available = false;
  console.log(`[INFO] helper_rcc_is_startup_time_available. Board is: ${JSON.stringify(board)}`);
  if (board == null)
  {
    is_available = false;
  }
  else
  {
    is_available = true;
  }
  return is_available;
}

/**
 * Get the startup time
 * @param {any} device
 * @param {null} board
 * @returns {Number} The start-up time
 */
function helper_rcc_get_startup_time(board, clock){
  let startup_time = 100;
  if (board != null)
  {
    /* Need to get startup time from board information */
    if (clock == 'hse')
    {
      startup_time = 100;
      console.log(`[WARNING] helper_rcc_get_startup_time. HSE startup time not found in dataset`);
    }
    else if (clock == 'lse')
    {
      startup_time = 5000;
      console.log(`[WARNING] helper_rcc_get_startup_time. LSE startup time not found in dataset`);
    }
    else
    {
      startup_time = 100;
    }
  }
  return startup_time;
}

/* Minimum recommanded flash latency wait states for a given frequency */
const flash_latencies = {

  optimal_values: {
    0: 40000000,
    1: 80000000,
    2: 120000000,
    3: 160000000,
    4: 200000000,
    5: 240000000,
    6: 260000000,
    7: 275000000
    },
  maximum: 15
};

function helper_rcc_is_flash_latency_possible(system_clock_frequency, latency)
{
  let ret = false;

  if (latency <= flash_latencies.maximum)
  {
    if (latency in flash_latencies.optimal_values)
    {
      if (system_clock_frequency <= flash_latencies.optimal_values[latency])
      {
        ret = true;
      }
    }
    else
    {
      ret = true;
    }
  }
  console.log(`[WARNING] helper_rcc_is_flash_latency_possible (${system_clock_frequency}, ${latency}) is ${ret}`);
  return ret;
}

function helper_rcc_get_optimal_latency(system_clock_frequency) {
  let latency = flash_latencies.maximum;
  console.log(`[WARNING] helper_rcc_get_optimal_latency (${system_clock_frequency})`);

  for(const [lat, frequency] of Object.entries(flash_latencies.optimal_values)) {
    if (system_clock_frequency <= frequency){
      latency = lat;
      break;}
  }

  console.log(`[WARNING] helper_rcc_get_optimal_latency (${latency})`);
  return Number(latency);
}

/* Minimum recommanded flash latency wait states for a given frequency
   From Spec Table FLASH recommended number of wait states and programming delays */
const programming_delays = {
  optimal_values: {
    0: 80000000,
    1: 160000000,
    2: 240000000,
    3: 275000000,
    },
  maximum: 3
};

function helper_rcc_is_flash_programming_delay_possible(system_clock_frequency, programming_delay)
{
  let ret = false;
  if (programming_delay <= programming_delays.maximum)
  {
    if (programming_delay in programming_delays.optimal_values)
    {
      if (system_clock_frequency <= programming_delays.optimal_values[programming_delay])
      {
        ret = true;
      }
    }
    else
    {
      ret = true;
    }
  }
  console.log(`[INFO] helper_rcc_is_flash_programming_delay_possible. For ${system_clock_frequency} and ${programming_delay} is ${ret}`);
  return ret;
}

function helper_rcc_get_optimal_programming_delay(system_clock_frequency) {
  let programming_delay = programming_delays.maximum;

  for(const [delay, frequency] of Object.entries(programming_delays.optimal_values)) {
    if (system_clock_frequency <= frequency){
      programming_delay = delay;
      break;}
  }
  console.log(`[INFO] helper_rcc_get_optimal_programming_delay. For ${system_clock_frequency} is ${programming_delay}`);
  return Number(programming_delay);
}

/**
 * Get the bus group for a given peripheral instance and context.
 * @param {string} peripheralInstance The name of the peripheral instance.
 * @returns {string|null} The bus group and bus mapping, or null if not found.
 */
function helper_rcc_get_bus_group(peripheralInstance) {
  return peripheralBusMapping[peripheralInstance] || null;
}

/**
 * Get the bus clock name for a given peripheral instance.
 * @param {string} peripheralInstance The name of the peripheral instance.
 * @returns {string} The bus clock name (e.g.: "PCLK1_Input_Clock") (empty if not found).
 */
function helper_rcc_get_bus_clock_name(peripheralInstance) {
  const group = peripheralBusMapping[peripheralInstance];
  const clock = group ? groupClockMapping[group] : null;
  return clock ? `${clock}_Input_Clock` : "";
}

// Convert the frequency to a readable string
// param: frequency in hertz
function helper_rcc_display_frequency(frequency)
{
  let result;
  if (frequency >= 1e6) {
    result = (frequency / 1e6) + ' MHz';
  } else if (frequency >= 1e3) {
    result = (frequency / 1e3) + ' kHz';
  } else {
    result = frequency + ' Hz';
  }

  if (result.includes('.')) {
    result = result.replace(/(\.\d*?[1-9])0+$/, '$1'); // Suppress zeros
    result = result.replace(/\.0+$/, '');              // Suppress point
  }
  return result;
}

/**
 * Display some values
 * @returns True or False
 * @param {any[]} arg
 */
function helper_rcc_display_values(...arg){
    for (var i = 0; i < arg.length; i++)
    {
      console.log(`[INFO] helper_rcc_display_values. Variable #${i} is ${arg[i]}`);
    }
    return 222;
}

/**
 * Break the javascript execution
 * @note This function is for Debug purpose only - Can be called into the template to watch assigned variables.
You need to toggle a breakpoint for the code to break.
 * @param {Number} code A code to indicate where the function has been called (can be the line number)
 * @param {any} root
 */
function helper_breakpoint(code, root){
  let ret = code;
}

function include(object, key){
  return object.hasOwnProperty(key);
}

module.exports = {
  helper_rcc_init_codegen,
  helper_rcc_get_context,
  helper_rcc_get_rcc_main_config,
  helper_rcc_get_system_config,
  helper_rcc_get_all_resources,
  helper_rcc_get_all_perifs_clock_config,
  helper_rcc_get_one_perif_clock_config,
  helper_rcc_get_clock_source_object,
  helper_rcc_remap_clock_source,
  helper_rcc_remap_kernel_clock_source,
  helper_rcc_remap_hw_resource,
  helper_rcc_remap_hw_resource_kernel,
  helper_rcc_remap_sw_resource,
  helper_rcc_get_power_voltage_scaling,
  helper_rcc_is_dac,
  helper_rcc_get_dac_sh_clock,
  helper_rcc_has_enable,
  helper_rcc_has_kernel_clock_mux,
  helper_rcc_is_not_shared_ppp,
  helper_rcc_set_resource_enabled,
  helper_rcc_is_resource_enabled,
  helper_rcc_is_central,
  helper_rcc_is_controlled_by_periph,
  helper_rcc_is_controlled_by_user,
  helper_rcc_get_clk_enable_mode,
  helper_rcc_is_startup_time_available,
  helper_rcc_get_startup_time,
  helper_rcc_is_flash_latency_possible,
  helper_rcc_get_optimal_latency,
  helper_rcc_is_flash_programming_delay_possible,
  helper_rcc_get_optimal_programming_delay,
  helper_rcc_get_bus_group,
  helper_rcc_get_bus_clock_name,
  helper_rcc_display_frequency,
  helper_rcc_display_values,
  helper_breakpoint,
  include,
  adjust_flash_latency,
};
