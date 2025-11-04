hal_xspi_handle_t xspi;
hal_xspi_xspim_config_t sOspiManagerCfg;
sOspiManagerCfg.port1.clk = HAL_XSPI_XSPIM_XSPI1;
sOspiManagerCfg.port1.dqs = HAL_XSPI_XSPIM_XSPI1;
sOspiManagerCfg.port1.ncs = HAL_XSPI_XSPIM_XSPI1;
sOspiManagerCfg.port1.io_low = HAL_XSPI_XSPIM_XSPI1_IO_LOW;
sOspiManagerCfg.port1.io_high = HAL_XSPI_XSPIM_XSPI1_IO_HIGH;
sOspiManagerCfg.req_ack_cycle = 1U;
HAL_XSPI_XSPIM_SetConfig(&sOspiManagerCfg);

















HAL_XSPI_Init(&xspi, HAL_OCTOSPI1);

hal_xspi_config_t HAL_XSPI_Global_Cfg_Struct;
HAL_XSPI_Global_Cfg_Struct.memory = HAL_XSPI_Mem_Cfg_Struct;
HAL_XSPI_Global_Cfg_Struct.timing = HAL_XSPI_Timing_Cfg_Struct;
HAL_XSPI_SetConfig(&xspi, &HAL_XSPI_Global_Cfg_Struct);