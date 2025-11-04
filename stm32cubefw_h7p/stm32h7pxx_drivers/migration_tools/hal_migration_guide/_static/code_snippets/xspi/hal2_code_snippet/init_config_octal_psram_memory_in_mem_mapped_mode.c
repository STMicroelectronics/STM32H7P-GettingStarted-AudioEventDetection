HAL_XSPI_Init(&xspi, HAL_OCTOSPI1);


/* Main peripheral configuration */
memory_config.mode = HAL_XSPI_MEMORY_SINGLE;
memory_config.type = HAL_XSPI_MEMORY_TYPE_APMEM_16BIT;
memory_config.size_bit = HAL_XSPI_MEMORY_SIZE_256MBIT;
memory_config.wrap_size_byte = HAL_XSPI_WRAP_NOT_SUPPORTED;
memory_config.clock_polarity = HAL_XSPI_CLOCK_LOW;
memory_config.cs_boundary = HAL_XSPI_CS_BOUNDARY_NONE;

timing_config.clk_prescaler = 0x1U;
timing_config.shift = HAL_XSPI_SAMPLE_SHIFT_NONE;
timing_config.hold = HAL_XSPI_DELAY_HOLD_NONE;
timing_config.cs_high_time_cycle = 0x1U;
timing_config.cs_release_time_cycle = 0x0U;
timing_config.cs_refresh_time_cycle = 0x0U;
timing_config.dlyb_state = HAL_XSPI_DLYB_ON;

xspi_config.memory = memory_config;
xspi_config.timing = timing_config;
if (HAL_XSPI_SetConfig(&hOCTOSPI1, &xspi_config) != HAL_OK)
{
  return NULL;
}

command.operation_type = HAL_XSPI_OPERATION_COMMON_CFG;
command.io_select = HAL_XSPI_IO_7_0;
command.instruction = WRITE_REG_CMD;
command.instruction_mode = HAL_XSPI_INSTRUCTION_8LINES;
command.instruction_width = HAL_XSPI_INSTRUCTION_8BIT;
command.instruction_dtr_mode_status = HAL_XSPI_INSTRUCTION_DTR_DISABLED;
command.addr = 0xFFFFFFFF;
command.addr_mode = HAL_XSPI_ADDR_8LINES;
command.addr_width = HAL_XSPI_ADDR_8BIT;
command.addr_dtr_mode_status = HAL_XSPI_ADDR_DTR_ENABLED;
command.alternate_bytes_mode = HAL_XSPI_ALTERNATE_BYTES_NONE;
command.data_mode = HAL_XSPI_REGULAR_DATA_8LINES;
command.data_dtr_mode_status = HAL_XSPI_DATA_DTR_ENABLED;
command.size_byte = 2;
command.dummy_cycle = 0;
command.dqs_mode_status = HAL_XSPI_DQS_DISABLED;
HAL_XSPI_SendRegularCmd(&xspi, &command, XSPI_TIMEOUT);

hal_xspi_memory_mapped_config_t mem_mapped_cfg;
mem_mapped_cfg.timeout_activation = HAL_XSPI_TIMEOUT_ENABLE;
mem_mapped_cfg.timeout_period_cycle = 0x34;
HAL_XSPI_StartMemoryMappedMode(&xspi, &mem_mapped_cfg);
HAL_XSPI_StopMemoryMappedMode(&xspi);