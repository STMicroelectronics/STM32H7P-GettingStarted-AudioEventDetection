/* */
hal_xspi_config_t HAL_XSPI_Global_Cfg_Struct;

HAL_XSPI_Init(&xspi, HAL_OCTOSPI);

HAL_XSPI_SetConfig(&xspi, &HAL_XSPI_Global_Cfg_Struct);

HAL_XSPI_DLYB_SetConfigDelay(&xspi, 2);
HAL_XSPI_DLYB_Enable(&xspi);