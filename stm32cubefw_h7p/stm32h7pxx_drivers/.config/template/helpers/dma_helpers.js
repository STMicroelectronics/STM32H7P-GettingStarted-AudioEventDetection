module.exports = {
  /**
   * Retrieve the list of DMA channel instances used in the I2Cx instance
   * @param {object} uuid Configurations defined for the a SW instance
   * @param {object} dma_instances List all the dma channel found in different SW instance
   * @returns Concatenate in a array the list of the unique DMA channel instance
   *          ex: dma_instance [{ id: '<uuid-#4>' }, { id: '<uuid-#5>' }]
   */
  helper_dma_get_dma_handle(uuids, dma_instances) {
    let result = [];
    try {
      console.log(
        `[INFO] helper_dma_get_dma_handle: uuid=${JSON.stringify(uuids)}, dma_instances=${JSON.stringify(dma_instances)}`
      );
      if (dma_instances !== "undefined") {
        result = dma_instances;
      }
      let dma_instance = uuids["resourceId"];
      if (result.indexOf(dma_instance) < 0) {
        result.push(dma_instance);
      }
    } catch (e) {
      console.log(`[ERROR] helper_dma_get_dma_handle: ${e}`);
    }
    return result;
  },

  /**
   * Retrieve the list of DMA channel instances used in the I2Cx instance
   * @param {string} dma_instance DMA channel string (ex GPDMA1_CH5)
   * @returns {string} return the DMA instance name (ex GPDMA1 or LPDMA1)
   */
   helper_dma_get_parent(dma_instance) {
    let result;
    try {
      console.log(
        `[INFO] helper_dma_get_parent: dma_instance=${JSON.stringify(dma_instance)}`
      );
      result = dma_instance.split("_");
      result = result[0];
    } catch (e) {
      console.log(`[ERROR] helper_dma_get_parent: ${e}`);
    }
    return result;
  },

  /**
   * Return the value to set in the request parameter
   * @param {string} dma_instance DMA channel string (ex GPDMA1_CH5)
   * @param {string} layer HAL or LL
   * @param {string} request request from DFP (ex: tim8_ch3_dma)
   * @returns {string} HAL or LL value (ex: HAL_GPDMA1_REQUEST_TIM8_CC3 or LL_GPDMA1_REQUEST_TIM8_CC3)
   */
  helper_dma_get_request(dma_instance, layer, request) {
    let result;
    try {
      console.log(`[INFO] helper_dma_get_request: dma_instance=${dma_instance}, layer=${layer}, request=${request}`);

      let dma_parent = dma_instance.split("_");
      dma_parent = dma_parent[0];

      const map_dma_request = {
        dac1_dma: "DAC1_CH1",
        dac2_dma: "DAC1_CH2",
        dcmi_dma_pssi_dma: "DCMI_PSSI",
      };

      let req;
      if (map_dma_request.hasOwnProperty(request)) {
        req = map_dma_request[request].toUpperCase();
      }
      else {
        req = request.split("_dma");
        req = req[0].toUpperCase();
      }

      result = layer + '_' + dma_parent  + '_REQUEST_'+ req;
    } catch (e) {
      console.log(`[ERROR] helper_dma_get_request: ${e}`);
    }
    return result;
  },

  /**
   * Return the value to set in the trigger parameter
   * @param {string} dma_instance DMA channel string (ex GPDMA1_CH5)
   * @param {string} layer HAL or LL
   * @param {string} trigger trigger from DFP (ex: exti5)
   * @returns {string} HAL or LL value (ex: HAL_GPDMA1_TRIGGER_EXTI5 or LL_GPDMA1_TRIGGER_EXTI5)
   */
  helper_dma_get_trigger(dma_instance, layer, trigger) {
    let result;
    try {
      console.log(`[INFO] helper_dma_get_trigger`);

      let dma_parent = dma_instance.split("_");
      dma_parent = dma_parent[0];

      const map_dma_trigger = {
        'gpu2d_flag[0]': "GPU2D_FLAG0",
        'gpu2d_flag[1]': "GPU2D_FLAG1",
        'gpu2d_flag[2]': "GPU2D_FLAG2",
        'gpu2d_flag[3]': "GPU2D_FLAG3",
        'comp1_out_dma': "COMP1_OUT",
        'comp2_out_dma': "COMP2_OUT",
        'spi6_it or spi6_ait': "SPI6_IT_OR_SPI6_AIT",
      };

      let trig;
      if (map_dma_trigger.hasOwnProperty(trigger)) {
        trig = map_dma_trigger[trigger];
      }
      else {
        trig = trigger;
      }
      trig = trig.toUpperCase();

      result = layer + '_' + dma_parent + '_TRIGGER_' + trig;
    } catch (e) {
      console.log(`[ERROR] helper_dma_get_trigger: ${e}`);
    }
    return result;
  },

  /**
   * Convert data width defined in string to a integer value for calculation
   * @param {string} data_width Data width in string format (BYTE, HALFWORD, WORD or DOUBLEWORD)
   * @returns {integer} Data width converted in number of bytes (1, 2, 4 or 8)
   */
  helper_dma_convert_data_width(data_width) {
    let result = 1; // Default value
    try {
      console.log(`[INFO] helper_dma_convert_data_width`);

      const map_data_width = {
        'BYTE': 1,
        'HALFWORD': 2,
        'WORD': 4,
        'DOUBLEWORD': 8,
      };

      if (map_data_width.hasOwnProperty(data_width)) {
        result = map_data_width[data_width];
      }
    } catch (e) {
      console.log(`[ERROR] helper_dma_convert_data_width: ${e}`);
    }
    return result;
  },

  /**
   * Return DMA mode.
   * @note set the USE_HAL_DMA_LINKEDLIST macro
   * @param {boolean} use_dma_linkedlist dma configuration returned by CORE Init
   * @param {object} dma_standalone_configuration dma configuration returned by SWConfigurationAPI.getSwInstancesConfiguration getter from "DMA Init"
   * @returns {boolean} true or false
   */
  helper_dma_standalone_linkedlist(use_dma_linkedlist, dma_standalone_configuration) {
    let result = 0;
    let standalone_mode = 0;
    try {
      console.log(
        `[INFO] helper_dma_standalone_linkedlist: use_dma_linkedlist=${use_dma_linkedlist}, dma_standalone_configuration=${JSON.stringify(dma_standalone_configuration)}`
      );
      dma_standalone_configuration.forEach(configuration => {
        if (standalone_mode !== 1) {
          standalone_mode = configuration.Main_configuration.DMA_Mode;
        }
      });

      if (
        (typeof use_dma_linkedlist === "undefined" && standalone_mode != 0) ||
        (typeof use_dma_linkedlist !== "undefined" && use_dma_linkedlist != 0) ||
        (standalone_mode != 0)
      ) {
        result = 1;
      }
    } catch (e) {
      console.error(`[ERROR] helper_dma_standalone_linkedlist: ${e}`);
    }
    return result;
  },

  /**
    * Retrieve the id for DMA configuration
    * @param {object} AllocatedResourceNeedsByComponent DMA Needs
    * @returns {array} return the the id for DMA configuration
    */
  helper_dma_get_need_id(AllocatedResourceNeedsByComponent) {
    const result = Array.from({ length: AllocatedResourceNeedsByComponent.length }, () => 0);
    try {
      for (let i = 0; i < AllocatedResourceNeedsByComponent.length; i++) {
        result[i] = AllocatedResourceNeedsByComponent[i].needId;
      }
    } catch (e) {
      console.error(`[ERROR] helper_dma_get_need_id: ${e}`);
    }
    return result;
  },

  /**
   * Return DMA mode.
   * @note set the USE_HAL_DMA_LINKEDLIST macro
   * @param {object} dma_need_configuration dma configuration returned by maAPI.getNeedById getter
   * @returns {boolean} true or false
   */
  helper_dma_need_linkedlist(dma_need_configuration) {
    let result = 0;
    try {
      if ((dma_need_configuration !== undefined)
          && (dma_need_configuration.configuration !== undefined)
          && (dma_need_configuration.configuration.Main_configuration !== undefined)
          && (dma_need_configuration.configuration.Main_configuration.DMA_Mode !== undefined)) {
        if (dma_need_configuration.configuration.Main_configuration.DMA_Mode != 0) {
          result = 1;
        }
      }
    } catch (e) {
      console.error(`[ERROR] helper_dma_need_linkedlist: ${e}`);
    }
    return result;
  },

  /**
   * Retrieve the DMA Node name
   * @param {string} request request from DFP (ex: tim8_ch3_dma)
   * @returns {string} HAL value (ex: DMA_Node_I2C1_TX or DMA_Node_SPI1_RX)
   */
  helper_dma_get_node( request) {
    let result;
    try {
        let req;
        req = request.split("_dma");
        req = req[0].toUpperCase();
        result = 'DMA_Node_' + req;
        console.log(`[INFO] helper_dma_get_node, DMA_Node=${result}`);
    } catch (e) {
        console.error(`[ERROR] helper_dma_get_node: ${e}`);
    }
    return result;
  },

  /**
   * Return DMA mode.
   * @param {object} dma_need_configuration dma configuration returned by maAPI.getNeedById getter
   * @returns {integer} DMA transfer mode (0:Direct, 1: linked-list or 2: circular)
   */
  helper_dma_transfer_mode(DMA_Mode) {
    let result = 0;
    try {
      if (DMA_Mode !== undefined) {
          result = DMA_Mode;
          console.log(`[INFO] helper_dma_transfer_mode, DMA_transfer_mode=${result}`);
      }
    } catch (e) {
      console.error(`[ERROR] helper_dma_transfer_mode: ${e}`);
    }
    return result;
  },

  /**
   *
   * @param {*} nvic_api
   * @param {*} resource
   * @param {*} channel_id
   * @param {*} config
   * @returns
{
  resource: "USART1",
  channel_id: "GPDMA1_CH1",
  alias: "",
  nvic_config: {
    name: "GPDMA1_CH1",
    description: "GPDMA1 channel1 global interrupt",
    priority: 0,
    subpriority: 0,
    shared: true,
    shared_with: [
      undefined,
      "GPDMA1_CH1",
    ],
  },
  generated: false,
}
   */
  helper_dma_get_irq_handler(nvic_api, resource, channel_id, config) {
  const result = [];
  try {
    console.log(
      `[INFO] helper_dma_get_irq_handler: resource=${resource}, config=${JSON.stringify(config)}`
    );

    /** Check the peripheral interruptions have been generated or not */
    const enableInterruption = config?.System_configuration?.enable_interrupt;
    if (!enableInterruption) return result;

    const irqHandlerGeneration = config?.System_configuration?.irq_handler_generation_dma ?? true;

    if (!irqHandlerGeneration) {
      const labels = config.info?.labels || [];
      const nvic_config = nvic_api.getNeedById(config.System_configuration.nvicConfig.needs[0].id);
      if (labels.length) {
        let first_label = true;
        for (const label of labels) {
          result.push({
            resource,
            channel_id: channel_id,
            labels,
            first_label,
            alias: label.toUpperCase() + '_IRQHANDLER',
            nvic_config,
            generated: false
          });
          first_label = false;
        }
      } else {
        result.push({
          resource,
          channel_id: channel_id,
          alias: "",
          nvic_config,
          generated: false
        });
      }
    }
  } catch (e) {
    console.log(`[ERROR] helper_dma_get_irq_handler: ${e}`);
  }
  return result;
}

};
