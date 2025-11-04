#!/bin/bash

stedgeai generate -m yamnet_256_64x96_tl_int8_5_classes.tflite --target stm32h7 --st-neural-art default-h7@profiles.json
cp st_ai_output/network.h .
cp st_ai_output/network.c .
cp st_ai_output/stai_network.h .
cp st_ai_output/stai_network.c .
cp st_ai_output/network_sysmem.eFlash2.c network_data.c
cp st_ai_output/network_ecblobs.h .