/* XSPIM configuration as mentioned in the use case :
 Memory initialization using XSPIM configuration */

hal_xspi_handle_t hOCTOSPI1;
HAL_XSPI_Init(&hOCTOSPI1, HAL_OCTOSPI1);

hal_xspi_config_t xspi_config;
hal_xspi_memory_config_t memory_config;
hal_xspi_timing_config_t timing_config;
hal_xspi_hyperbus_config_t hyperbus_config;

memory_config.mode = HAL_XSPI_MEMORY_SINGLE;
memory_config.clock_polarity = HAL_XSPI_CLOCK_LOW;
memory_config.type = HAL_XSPI_MEMORY_TYPE_HYPERBUS;
memory_config.size_bit = HAL_XSPI_MEMORY_SIZE_16BIT;
memory_config.wrap_size_byte = HAL_XSPI_WRAP_NOT_SUPPORTED;
memory_config.cs_boundary = HAL_XSPI_CS_BOUNDARY_NONE;

timing_config.clk_prescaler = 0x1U;
timing_config.shift = HAL_XSPI_SAMPLE_SHIFT_NONE;
timing_config.hold = HAL_XSPI_DELAY_HOLD_NONE;
timing_config.cs_high_time_cycle = 0x1U;
timing_config.cs_release_time_cycle = 0x0U;
timing_config.cs_refresh_time_cycle = 0x0U;
timing_config.dlyb_state = HAL_XSPI_DLYB_ON;

hyperbus_config.rw_recovery_time_cycle = 0x0U;
hyperbus_config.access_time_cycle = 0x0U;
hyperbus_config.write_zero_latency = HAL_XSPI_WRITE_ZERO_LATENCY_DISABLED;
hyperbus_config.latency_mode = HAL_XSPI_LATENCY_VARIABLE;

xspi_config.memory = memory_config;
xspi_config.timing = timing_config;
xspi_config.hyperbus = hyperbus_config;
HAL_XSPI_SetConfig(&hOCTOSPI1, &xspi_config);