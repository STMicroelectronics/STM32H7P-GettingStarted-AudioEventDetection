/* Register TX, RX, TX node and RX node complete callback */
if (HAL_SD_RegisterXferCpltCallback(&sd_handle, XferCpltCallback) != HAL_OK)
{
}

/* Register transceiver complete callback */
if (HAL_SD_RegisterTransceiverCallback(&sd_handle, sd_transceiver_callback) != HAL_OK)
{
}

/* Callbacks implementation */
void XferCpltCallback(hal_sd_handle_t *hsd, hal_sd_event_cb_t cb_event)
{
    if ((cb_event & HAL_SD_EVENT_CB_TX_CPLT) == 0x01UL)
    {
    }
    else if ((cb_event & HAL_SD_EVENT_CB_RX_CPLT) == 0x02UL)
    {
    }
    else if ((cb_event & HAL_SD_EVENT_CB_TX_NODE_CPLT) == 0x03UL)
    {
    }
    else if ((cb_event & HAL_SD_EVENT_CB_RX_NODE_CPLT) == 0x04UL) {
    }
}

void sd_transceiver_callback(hal_sd_handle_t *hsd, hal_sd_transceiver_state_t state)
{
    if (state == HAL_SD_TRANSCEIVER_DISABLE)
    {
    }
    else /* state == HAL_SD_TRANSCEIVER_ENABLE */
    {
    }
}