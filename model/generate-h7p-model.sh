#!/bin/bash
steai='C:/ST/STEdgeAI/4.1/Utilities/windows/stedgeai.exe'
$steai --version
$steai generate -m yamnet_256_64x96_tl_int8_5_classes.tflite --target stm32h7 --st-neural-art default-h7@profiles.json

cp st_ai_output/network.h ../STM32H7P5I-DK/generated/ai
cp st_ai_output/network.c ../STM32H7P5I-DK/generated/ai
cp st_ai_output/stai_network.h ../STM32H7P5I-DK/generated/ai
cp st_ai_output/stai_network.c ../STM32H7P5I-DK/generated/ai
cp st_ai_output/network_sysmem.eFlash1.c ../STM32H7P5I-DK/generated/ai
cp st_ai_output/network_sysmem.eFlash2.c ../STM32H7P5I-DK/generated/ai
cp st_ai_output/network_ecblobs.h ../STM32H7P5I-DK/generated/ai
cp st_ai_output/network_generate_report.txt ../STM32H7P5I-DK/generated/ai
cp st_ai_output/network_c_info.json ../STM32H7P5I-DK/generated/ai
