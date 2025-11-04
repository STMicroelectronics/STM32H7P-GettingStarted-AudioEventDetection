/* Register TX complete callback */
if (HAL_SD_RegisterCallback(&sd_handle, HAL_SD_TX_CPLT_CB_ID, tx_callback) != HAL_OK)
{
}

/* Register Tx node complete callback */
if (HAL_SD_RegisterCallback(&sd_handle, HAL_SD_WRITE_DMA_LNKLST_BUF_CPLT_CB_ID, tx_callback) != HAL_OK)
{
}

/* Register RX callback */
if (HAL_SD_RegisterCallback(&sd_handle, HAL_SD_RX_CPLT_CB_ID, rx_callback) != HAL_OK)
{
}

/* Register Rx node complete callback */
if (HAL_SD_RegisterCallback(&sd_handle, HAL_SD_READ_DMA_LNKLST_BUF_CPLT_CB_ID, rx_callback) != HAL_OK)
{
}

/* Register transceiver complete callback */
if (HAL_SD_RegisterTransceiverCallback(&sd_handle, sd_transceiver_callback) != HAL_OK)
{
}

/* Callbacks implementation */
void tx_callback(hal_sd_handle_t *hsd)
{
}

void rx_callback(hal_sd_handle_t *hsd)
{
}

void sd_transceiver_callback(FlagStatus status)
{
}