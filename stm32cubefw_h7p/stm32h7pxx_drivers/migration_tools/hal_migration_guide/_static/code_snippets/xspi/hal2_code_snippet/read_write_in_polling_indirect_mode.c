/* Perform the init and configuration as per the first use case*/

hal_xspi_handle_t xspi;

command.operation_type = HAL_XSPI_OPERATION_COMMON_CFG;
command.io_select = HAL_XSPI_IO_7_0;
command.alternate_bytes = 0U;
command.alternate_bytes_width = HAL_XSPI_ALTERNATE_BYTES_8BIT;
command.alternate_bytes_mode = HAL_XSPI_ALTERNATE_BYTES_NONE;
command.alternate_bytes_dtr_mode_status = HAL_XSPI_ALTERNATE_BYTES_DTR_DISABLED;
/* Specific parameters for the Sector Erase command */
command.instruction = WRITE_REG_CMD;
command.instruction_mode = HAL_XSPI_INSTRUCTION_8LINES;
command.instruction_width = HAL_XSPI_INSTRUCTION_32BIT;
command.instruction_dtr_mode_status = HAL_XSPI_INSTRUCTION_DTR_DISABLED;
command.addr = MX25_FIRST_BLOCK_ADDR;
command.addr_mode = HAL_XSPI_ADDR_8LINES;
command.addr_width = HAL_XSPI_ADDR_32BIT;
command.addr_dtr_mode_status = HAL_XSPI_ADDR_DTR_ENABLED;
command.data_mode = HAL_XSPI_REGULAR_DATA_NONE;
command.data_dtr_mode_status = HAL_XSPI_DATA_DTR_ENABLED;
command.dummy_cycle = 0;
command.dqs_mode_status = HAL_XSPI_DQS_DISABLED;
command.size_byte = 2U;
HAL_XSPI_SendRegularCmd(&xspi, &command, XSPI_TIMEOUT);

HAL_XSPI_ExecRegularAutoPoll(&xspi, &pPollingModeCfg, XSPI_TIMEOUT);

HAL_XSPI_SetFifoThreshold(&xspi, 4);

HAL_XSPI_SendRegularCmd(&xspi, &command, XSPI_TIMEOUT);

HAL_XSPI_Transmit(&xspi, p_data, XSPI_TIMEOUT);

HAL_XSPI_SendRegularCmd(&xspi, &command, XSPI_TIMEOUT);

HAL_XSPI_ExecRegularAutoPoll(&xspi, &pPollingModeCfg, XSPI_TIMEOUT);

HAL_XSPI_SendRegularCmd(&xspi, &command, XSPI_TIMEOUT);

HAL_XSPI_Receive(&xspi, (uint8_t *)aRxBuffer, XSPI_TIMEOUT);
