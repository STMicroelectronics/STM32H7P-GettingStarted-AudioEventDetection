# origin-pack: STMicroelectronics::stm32h7pxx_hal_drivers@2.0.0-alpha.2.0
# created-by: conversion-manager@0.0.64
project(STMicroelectronics_stm32h7pxx_hal_drivers_2_0_0_alpha_2_0)
cmake_minimum_required(VERSION 3.20)
add_library(STMicroelectronics_stm32h7pxx_hal_drivers_2_0_0_alpha_2_0 INTERFACE)

# List of all CMSIS properties that influence conditions for this package
if(NOT DEFINED CMSIS_Dname)
  set(CMSIS_Dname "CMSIS_Dname not set")
  message(DEBUG "CMSIS_Dname is not set to any value")
endif()

if(NOT DEFINED CMSIS_Dvendor)
  set(CMSIS_Dvendor "CMSIS_Dvendor not set")
  message(DEBUG "CMSIS_Dvendor is not set to any value")
endif()


# Device specific defined symbols








# Enable all components in this package
if(CMSIS_ENTIRE_STMicroelectronics_stm32h7pxx_hal_drivers_2_0_0_alpha_2_0)
  set(CMSIS_USE_Device_STM32_HAL_timebases_SYSTICK_0_1_0 true)
  set(CMSIS_USE_Device_STM32_HAL_timebases_RTC_ALARM_0_1_0 true)
  set(CMSIS_USE_Device_STM32_HAL_timebases_RTC_WAKEUP_0_1_0 true)
  set(CMSIS_USE_Device_STM32_HAL_TIM_template_0_1_1 true)
  set(CMSIS_USE_Device_STM32_HAL_timebases_TIM_0_1_0 true)
  set(CMSIS_USE_Device_STM32_HAL_Core_0_4_1 true)
  set(CMSIS_USE_Device_STM32_HAL_UTILS_I2C_0_1_0 true)
  set(CMSIS_USE_Device_STM32_HAL_UTILS_I3C_0_1_0 true)
  set(CMSIS_USE_Device_STM32_HAL_UTILS_FDCAN_0_1_0 true)
  set(CMSIS_USE_Device_STM32_HAL_ASSERT_0_1_1 true)
  set(CMSIS_USE_Device_STM32_HAL_template_0_1_1 true)
  set(CMSIS_USE_Device_STM32_HAL_ADC_0_2_0 true)
  set(CMSIS_USE_Device_STM32_HAL_ADF_0_2_0 true)
  set(CMSIS_USE_Device_STM32_HAL_COMP_0_2_0 true)
  set(CMSIS_USE_Device_STM32_HAL_CORDIC_0_1_0 true)
  set(CMSIS_USE_Device_STM32_HAL_CORTEX_0_2_0 true)
  set(CMSIS_USE_Device_STM32_HAL_CRC_0_3_0 true)
  set(CMSIS_USE_Device_STM32_HAL_CRS_0_2_0 true)
  set(CMSIS_USE_Device_STM32_HAL_DAC_0_4_0 true)
  set(CMSIS_USE_Device_STM32_HAL_DBGMCU_0_2_0 true)
  set(CMSIS_USE_Device_STM32_HAL_DRIVERS_CORE_DLYB_0_1_0 true)
  set(CMSIS_USE_Device_STM32_HAL_DMA_0_5_0 true)
  set(CMSIS_USE_Device_STM32_HAL_DTS_0_2_0 true)
  set(CMSIS_USE_Device_STM32_HAL_EXTI_0_3_0 true)
  set(CMSIS_USE_Device_STM32_HAL_FDCAN_0_2_0 true)
  set(CMSIS_USE_Device_STM32_HAL_FLASH_0_2_0 true)
  set(CMSIS_USE_Device_STM32_HAL_FLASH_ITF_0_1_0 true)
  set(CMSIS_USE_Device_STM32_HAL_FMAC_0_2_0 true)
  set(CMSIS_USE_Device_STM32_HAL_DRIVERS_CORE_FMC_0_1_0 true)
  set(CMSIS_USE_Device_STM32_HAL_GPIO_0_2_2 true)
  set(CMSIS_USE_Device_STM32_HAL_HASH_0_2_0 true)
  set(CMSIS_USE_Device_STM32_HAL_HCD_0_3_0 true)
  set(CMSIS_USE_Device_STM32_HAL_HRTIM_0_1_0 true)
  set(CMSIS_USE_Device_STM32_HAL_HSP_0_0_1 true)
  set(CMSIS_USE_Device_STM32_HAL_I2C_0_3_0 true)
  set(CMSIS_USE_Device_STM32_HAL_I3C_0_1_0 true)
  set(CMSIS_USE_Device_STM32_HAL_I2S_0_3_0 true)
  set(CMSIS_USE_Device_STM32_HAL_IWDG_0_2_0 true)
  set(CMSIS_USE_Device_STM32_HAL_LPTIM_0_2_0 true)
  set(CMSIS_USE_Device_STM32_HAL_MMC_0_1_1 true)
  set(CMSIS_USE_Device_STM32_HAL_PCD_0_3_0 true)
  set(CMSIS_USE_Device_STM32_HAL_PWR_0_3_0 true)
  set(CMSIS_USE_Device_STM32_HAL_Q_0_1_0 true)
  set(CMSIS_USE_Device_STM32_HAL_RAMECC_0_1_0 true)
  set(CMSIS_USE_Device_STM32_HAL_RCC_0_3_0 true)
  set(CMSIS_USE_Device_STM32_HAL_RNG_0_2_0 true)
  set(CMSIS_USE_Device_STM32_HAL_RTC_0_2_0 true)
  set(CMSIS_USE_Device_STM32_HAL_SD_0_5_0 true)
  set(CMSIS_USE_Device_STM32_HAL_SDIO_0_1_0 true)
  set(CMSIS_USE_Device_STM32_HAL_DRIVERS_CORE_SDMMC_0_1_0 true)
  set(CMSIS_USE_Device_STM32_HAL_SMARTCARD_0_1_0 true)
  set(CMSIS_USE_Device_STM32_HAL_SMBUS_0_1_0 true)
  set(CMSIS_USE_Device_STM32_HAL_SPI_0_1_1 true)
  set(CMSIS_USE_Device_STM32_HAL_SBS_0_3_0 true)
  set(CMSIS_USE_Device_STM32_HAL_SRAM_0_2_0 true)
  set(CMSIS_USE_Device_STM32_HAL_TAMP_0_1_4 true)
  set(CMSIS_USE_Device_STM32_HAL_TIM_0_1_2 true)
  set(CMSIS_USE_Device_STM32_HAL_UART_0_3_0 true)
  set(CMSIS_USE_Device_STM32_HAL_UCPD_0_1_0 true)
  set(CMSIS_USE_Device_STM32_HAL_USART_0_2_0 true)
  set(CMSIS_USE_Device_STM32_HAL_DRIVERS_CORE_USB_CORE_DEF_0_1_1 true)
  set(CMSIS_USE_Device_STM32_HAL_DRIVERS_CORE_USB_OTG_0_3_0 true)
  set(CMSIS_USE_Device_STM32_HAL_VREFBUF_0_2_0 true)
  set(CMSIS_USE_Device_STM32_HAL_WWDG_0_2_0 true)
  set(CMSIS_USE_Device_STM32_HAL_XSPI_0_5_0 true)
  set(CMSIS_USE_Device_STM32_LL_Common_0_1_0 true)
  set(CMSIS_USE_Device_STM32_LL_ADC_0_1_1 true)
  set(CMSIS_USE_Device_STM32_LL_BUS_0_1_0 true)
  set(CMSIS_USE_Device_STM32_LL_COMP_0_1_0 true)
  set(CMSIS_USE_Device_STM32_LL_CORDIC_0_1_0 true)
  set(CMSIS_USE_Device_STM32_LL_CRC_0_1_0 true)
  set(CMSIS_USE_Device_STM32_LL_CRS_0_1_0 true)
  set(CMSIS_USE_Device_STM32_LL_DAC_0_1_1 true)
  set(CMSIS_USE_Device_STM32_LL_DBGMCU_0_1_0 true)
  set(CMSIS_USE_Device_STM32_LL_DMA_0_2_1 true)
  set(CMSIS_USE_Device_STM32_LL_FLASH_0_1_0 true)
  set(CMSIS_USE_Device_STM32_LL_EXTI_0_1_0 true)
  set(CMSIS_USE_Device_STM32_LL_FMAC_0_1_0 true)
  set(CMSIS_USE_Device_STM32_LL_GPIO_0_1_0 true)
  set(CMSIS_USE_Device_STM32_LL_HRTIM_0_1_0 true)
  set(CMSIS_USE_Device_STM32_LL_I2C_0_1_0 true)
  set(CMSIS_USE_Device_STM32_LL_I3C_0_1_0 true)
  set(CMSIS_USE_Device_STM32_LL_IWDG_0_1_0 true)
  set(CMSIS_USE_Device_STM32_LL_LPTIM_0_1_0 true)
  set(CMSIS_USE_Device_STM32_LL_LPUART_0_2_0 true)
  set(CMSIS_USE_Device_STM32_LL_PWR_0_1_0 true)
  set(CMSIS_USE_Device_STM32_LL_RAMECC_0_1_0 true)
  set(CMSIS_USE_Device_STM32_LL_RCC_0_1_0 true)
  set(CMSIS_USE_Device_STM32_LL_RNG_0_1_0 true)
  set(CMSIS_USE_Device_STM32_LL_RTC_0_1_1 true)
  set(CMSIS_USE_Device_STM32_LL_TAMP_0_1_0 true)
  set(CMSIS_USE_Device_STM32_LL_SPI_0_1_0 true)
  set(CMSIS_USE_Device_STM32_LL_SBS_0_1_0 true)
  set(CMSIS_USE_Device_STM32_LL_SYSTEM_0_1_1 true)
  set(CMSIS_USE_Device_STM32_LL_TIM_0_1_0 true)
  set(CMSIS_USE_Device_STM32_LL_UCPD_0_1_0 true)
  set(CMSIS_USE_Device_STM32_LL_USART_0_2_0 true)
  set(CMSIS_USE_Device_STM32_LL_UTILS_0_1_1 true)
  set(CMSIS_USE_Device_STM32_LL_VREFBUF_0_1_0 true)
  set(CMSIS_USE_Device_STM32_LL_WWDG_0_1_0 true)
  set(CMSIS_USE_Device_STM32_HAL_HAL_OS_NO_OS_0_0_1 true)
  set(CMSIS_USE_Device_STM32_HAL_HAL_OS_FreeRTOS_0_0_1 true)
  set(CMSIS_USE_Device_STM32_HAL_HAL_OS_TEMPLATE_OS_0_0_1 true)
endif()

# All conditions used by this package

# condition: STMicroelectronics.stm32h7pxx_hal_drivers.2.0.0-alpha.2.0
# description: 
if((CMSIS_Dname MATCHES "STM32H7P.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13"))
  set(STMicroelectronics.stm32h7pxx_hal_drivers.2.0.0-alpha.2.0 true)
  message(DEBUG "CMSIS condition STMicroelectronics.stm32h7pxx_hal_drivers.2.0.0-alpha.2.0 enabled")
endif()


# condition: STMicroelectronics.stm32h7pxx_hal_drivers.2.0.0-alpha.2.0:CMSIS Core
# description: STMicroelectronics STM32H7P and HAL Common
if((CMSIS_Dname MATCHES "STM32H7P.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13"))
  set(STMicroelectronics.stm32h7pxx_hal_drivers.2.0.0-alpha.2.0:CMSIS_Core true)
  message(DEBUG "CMSIS condition STMicroelectronics.stm32h7pxx_hal_drivers.2.0.0-alpha.2.0:CMSIS_Core enabled")
endif()


# condition: STMicroelectronics.stm32h7pxx_hal_drivers.2.0.0-alpha.2.0:HAL ADC
# description: HAL ADC dependencies
if((((CMSIS_Dname MATCHES "STM32H7P.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32H7P.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13")) AND ((CMSIS_Dname MATCHES "STM32H7P.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32H7P.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13"))))
  set(STMicroelectronics.stm32h7pxx_hal_drivers.2.0.0-alpha.2.0:HAL_ADC true)
  message(DEBUG "CMSIS condition STMicroelectronics.stm32h7pxx_hal_drivers.2.0.0-alpha.2.0:HAL_ADC enabled")
endif()


# condition: STMicroelectronics.stm32h7pxx_hal_drivers.2.0.0-alpha.2.0:HAL COMP
# description: HAL COMP dependencies
if(((CMSIS_Dname MATCHES "STM32H7P.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32H7P.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13")))
  set(STMicroelectronics.stm32h7pxx_hal_drivers.2.0.0-alpha.2.0:HAL_COMP true)
  message(DEBUG "CMSIS condition STMicroelectronics.stm32h7pxx_hal_drivers.2.0.0-alpha.2.0:HAL_COMP enabled")
endif()


# condition: STMicroelectronics.stm32h7pxx_hal_drivers.2.0.0-alpha.2.0:HAL CONF
# description: 
set(STMicroelectronics.stm32h7pxx_hal_drivers.2.0.0-alpha.2.0:HAL_CONF true)
message(DEBUG "CMSIS condition STMicroelectronics.stm32h7pxx_hal_drivers.2.0.0-alpha.2.0:HAL_CONF enabled")


# condition: STMicroelectronics.stm32h7pxx_hal_drivers.2.0.0-alpha.2.0:HAL CONF Init
# description: 
set(STMicroelectronics.stm32h7pxx_hal_drivers.2.0.0-alpha.2.0:HAL_CONF_Init true)
message(DEBUG "CMSIS condition STMicroelectronics.stm32h7pxx_hal_drivers.2.0.0-alpha.2.0:HAL_CONF_Init enabled")


# condition: STMicroelectronics.stm32h7pxx_hal_drivers.2.0.0-alpha.2.0:HAL CONF template
# description: 
set(STMicroelectronics.stm32h7pxx_hal_drivers.2.0.0-alpha.2.0:HAL_CONF_template true)
message(DEBUG "CMSIS condition STMicroelectronics.stm32h7pxx_hal_drivers.2.0.0-alpha.2.0:HAL_CONF_template enabled")


# condition: STMicroelectronics.stm32h7pxx_hal_drivers.2.0.0-alpha.2.0:HAL CORDIC
# description: HAL CORDIC dependencies
if((((CMSIS_Dname MATCHES "STM32H7P.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32H7P.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13")) AND ((CMSIS_Dname MATCHES "STM32H7P.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32H7P.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13"))))
  set(STMicroelectronics.stm32h7pxx_hal_drivers.2.0.0-alpha.2.0:HAL_CORDIC true)
  message(DEBUG "CMSIS condition STMicroelectronics.stm32h7pxx_hal_drivers.2.0.0-alpha.2.0:HAL_CORDIC enabled")
endif()


# condition: STMicroelectronics.stm32h7pxx_hal_drivers.2.0.0-alpha.2.0:HAL CORE
# description: STMicroelectronics STM32H7P and HAL system
if(((CMSIS_Dname MATCHES "STM32H7P.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32H7P.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13")))
  set(STMicroelectronics.stm32h7pxx_hal_drivers.2.0.0-alpha.2.0:HAL_CORE true)
  message(DEBUG "CMSIS condition STMicroelectronics.stm32h7pxx_hal_drivers.2.0.0-alpha.2.0:HAL_CORE enabled")
endif()


# condition: STMicroelectronics.stm32h7pxx_hal_drivers.2.0.0-alpha.2.0:HAL CORE DMA
# description: STMicroelectronics STM32H7P and HAL with DMA
if((((CMSIS_Dname MATCHES "STM32H7P.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32H7P.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13")) AND ((CMSIS_Dname MATCHES "STM32H7P.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32H7P.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13"))))
  set(STMicroelectronics.stm32h7pxx_hal_drivers.2.0.0-alpha.2.0:HAL_CORE_DMA true)
  message(DEBUG "CMSIS condition STMicroelectronics.stm32h7pxx_hal_drivers.2.0.0-alpha.2.0:HAL_CORE_DMA enabled")
endif()


# condition: STMicroelectronics.stm32h7pxx_hal_drivers.2.0.0-alpha.2.0:HAL CORE DMA Init
# description: STMicroelectronics HAL CORE and DMA Init dependencies
if(((CMSIS_Dname MATCHES "STM32H7P.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32H7P.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13")))
  set(STMicroelectronics.stm32h7pxx_hal_drivers.2.0.0-alpha.2.0:HAL_CORE_DMA_Init true)
  message(DEBUG "CMSIS condition STMicroelectronics.stm32h7pxx_hal_drivers.2.0.0-alpha.2.0:HAL_CORE_DMA_Init enabled")
endif()


# condition: STMicroelectronics.stm32h7pxx_hal_drivers.2.0.0-alpha.2.0:HAL CORE DMA Init and CORDIC
# description: STMicroelectronics HAL CORDIC Init dependencies
if((((CMSIS_Dname MATCHES "STM32H7P.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32H7P.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13")) AND (((CMSIS_Dname MATCHES "STM32H7P.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32H7P.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13")) AND ((CMSIS_Dname MATCHES "STM32H7P.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32H7P.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13")))))
  set(STMicroelectronics.stm32h7pxx_hal_drivers.2.0.0-alpha.2.0:HAL_CORE_DMA_Init_and_CORDIC true)
  message(DEBUG "CMSIS condition STMicroelectronics.stm32h7pxx_hal_drivers.2.0.0-alpha.2.0:HAL_CORE_DMA_Init_and_CORDIC enabled")
endif()


# condition: STMicroelectronics.stm32h7pxx_hal_drivers.2.0.0-alpha.2.0:HAL CORE DMA Init and FMAC
# description: STMicroelectronics HAL FMAC Init dependencies
if((((CMSIS_Dname MATCHES "STM32H7P.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32H7P.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13")) AND (((CMSIS_Dname MATCHES "STM32H7P.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32H7P.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13")) AND ((CMSIS_Dname MATCHES "STM32H7P.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32H7P.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13")))))
  set(STMicroelectronics.stm32h7pxx_hal_drivers.2.0.0-alpha.2.0:HAL_CORE_DMA_Init_and_FMAC true)
  message(DEBUG "CMSIS condition STMicroelectronics.stm32h7pxx_hal_drivers.2.0.0-alpha.2.0:HAL_CORE_DMA_Init_and_FMAC enabled")
endif()


# condition: STMicroelectronics.stm32h7pxx_hal_drivers.2.0.0-alpha.2.0:HAL CORE DMA Init and HASH
# description: STMicroelectronics HAL HASH Init dependencies
if((((CMSIS_Dname MATCHES "STM32H7P.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32H7P.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13")) AND (((CMSIS_Dname MATCHES "STM32H7P.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32H7P.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13")) AND ((CMSIS_Dname MATCHES "STM32H7P.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32H7P.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13")))))
  set(STMicroelectronics.stm32h7pxx_hal_drivers.2.0.0-alpha.2.0:HAL_CORE_DMA_Init_and_HASH true)
  message(DEBUG "CMSIS condition STMicroelectronics.stm32h7pxx_hal_drivers.2.0.0-alpha.2.0:HAL_CORE_DMA_Init_and_HASH enabled")
endif()


# condition: STMicroelectronics.stm32h7pxx_hal_drivers.2.0.0-alpha.2.0:HAL CORE GPIO DMA Init
# description: STMicroelectronics HAL CORE, GPIO and DMA Init dependencies
if(((CMSIS_Dname MATCHES "STM32H7P.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32H7P.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13")))
  set(STMicroelectronics.stm32h7pxx_hal_drivers.2.0.0-alpha.2.0:HAL_CORE_GPIO_DMA_Init true)
  message(DEBUG "CMSIS condition STMicroelectronics.stm32h7pxx_hal_drivers.2.0.0-alpha.2.0:HAL_CORE_GPIO_DMA_Init enabled")
endif()


# condition: STMicroelectronics.stm32h7pxx_hal_drivers.2.0.0-alpha.2.0:HAL CORE GPIO DMA Init and ADC
# description: STMicroelectronics HAL ADC Init dependencies
if((((CMSIS_Dname MATCHES "STM32H7P.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32H7P.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13")) AND (((CMSIS_Dname MATCHES "STM32H7P.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32H7P.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13")) AND ((CMSIS_Dname MATCHES "STM32H7P.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32H7P.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13")))))
  set(STMicroelectronics.stm32h7pxx_hal_drivers.2.0.0-alpha.2.0:HAL_CORE_GPIO_DMA_Init_and_ADC true)
  message(DEBUG "CMSIS condition STMicroelectronics.stm32h7pxx_hal_drivers.2.0.0-alpha.2.0:HAL_CORE_GPIO_DMA_Init_and_ADC enabled")
endif()


# condition: STMicroelectronics.stm32h7pxx_hal_drivers.2.0.0-alpha.2.0:HAL CORE GPIO DMA Init and DAC
# description: STMicroelectronics HAL DAC Init dependencies
if(((CMSIS_Dname MATCHES "STM32H7P.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32H7P.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13")))
  set(STMicroelectronics.stm32h7pxx_hal_drivers.2.0.0-alpha.2.0:HAL_CORE_GPIO_DMA_Init_and_DAC true)
  message(DEBUG "CMSIS condition STMicroelectronics.stm32h7pxx_hal_drivers.2.0.0-alpha.2.0:HAL_CORE_GPIO_DMA_Init_and_DAC enabled")
endif()


# condition: STMicroelectronics.stm32h7pxx_hal_drivers.2.0.0-alpha.2.0:HAL CORE GPIO DMA Init and HRTIM
# description: STMicroelectronics HAL HRTIM Init dependencies
if((((CMSIS_Dname MATCHES "STM32H7P.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32H7P.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13")) AND (((CMSIS_Dname MATCHES "STM32H7P.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32H7P.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13")) AND ((CMSIS_Dname MATCHES "STM32H7P.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32H7P.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13")))))
  set(STMicroelectronics.stm32h7pxx_hal_drivers.2.0.0-alpha.2.0:HAL_CORE_GPIO_DMA_Init_and_HRTIM true)
  message(DEBUG "CMSIS condition STMicroelectronics.stm32h7pxx_hal_drivers.2.0.0-alpha.2.0:HAL_CORE_GPIO_DMA_Init_and_HRTIM enabled")
endif()


# condition: STMicroelectronics.stm32h7pxx_hal_drivers.2.0.0-alpha.2.0:HAL CORE GPIO DMA Init and I2C
# description: STMicroelectronics HAL I2C Init dependencies
if((((CMSIS_Dname MATCHES "STM32H7P.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32H7P.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13")) AND (((CMSIS_Dname MATCHES "STM32H7P.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32H7P.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13")) AND ((CMSIS_Dname MATCHES "STM32H7P.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32H7P.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13")))))
  set(STMicroelectronics.stm32h7pxx_hal_drivers.2.0.0-alpha.2.0:HAL_CORE_GPIO_DMA_Init_and_I2C true)
  message(DEBUG "CMSIS condition STMicroelectronics.stm32h7pxx_hal_drivers.2.0.0-alpha.2.0:HAL_CORE_GPIO_DMA_Init_and_I2C enabled")
endif()


# condition: STMicroelectronics.stm32h7pxx_hal_drivers.2.0.0-alpha.2.0:HAL CORE GPIO DMA Init and I2S
# description: STMicroelectronics HAL I2S Init dependencies
if((((CMSIS_Dname MATCHES "STM32H7P.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32H7P.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13")) AND (((CMSIS_Dname MATCHES "STM32H7P.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32H7P.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13")) AND ((CMSIS_Dname MATCHES "STM32H7P.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32H7P.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13")))))
  set(STMicroelectronics.stm32h7pxx_hal_drivers.2.0.0-alpha.2.0:HAL_CORE_GPIO_DMA_Init_and_I2S true)
  message(DEBUG "CMSIS condition STMicroelectronics.stm32h7pxx_hal_drivers.2.0.0-alpha.2.0:HAL_CORE_GPIO_DMA_Init_and_I2S enabled")
endif()


# condition: STMicroelectronics.stm32h7pxx_hal_drivers.2.0.0-alpha.2.0:HAL CORE GPIO DMA Init and I3C
# description: STMicroelectronics HAL I3C Init dependencies
if((((CMSIS_Dname MATCHES "STM32H7P.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32H7P.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13")) AND (((CMSIS_Dname MATCHES "STM32H7P.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32H7P.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13")) AND ((CMSIS_Dname MATCHES "STM32H7P.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32H7P.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13")))))
  set(STMicroelectronics.stm32h7pxx_hal_drivers.2.0.0-alpha.2.0:HAL_CORE_GPIO_DMA_Init_and_I3C true)
  message(DEBUG "CMSIS condition STMicroelectronics.stm32h7pxx_hal_drivers.2.0.0-alpha.2.0:HAL_CORE_GPIO_DMA_Init_and_I3C enabled")
endif()


# condition: STMicroelectronics.stm32h7pxx_hal_drivers.2.0.0-alpha.2.0:HAL CORE GPIO DMA Init and LPTIM
# description: STMicroelectronics HAL LPTIM Init dependencies
if(((CMSIS_Dname MATCHES "STM32H7P.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32H7P.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13")))
  set(STMicroelectronics.stm32h7pxx_hal_drivers.2.0.0-alpha.2.0:HAL_CORE_GPIO_DMA_Init_and_LPTIM true)
  message(DEBUG "CMSIS condition STMicroelectronics.stm32h7pxx_hal_drivers.2.0.0-alpha.2.0:HAL_CORE_GPIO_DMA_Init_and_LPTIM enabled")
endif()


# condition: STMicroelectronics.stm32h7pxx_hal_drivers.2.0.0-alpha.2.0:HAL CORE GPIO DMA Init and SMARTCARD
# description: STMicroelectronics HAL SMARTCARD Init dependencies
if((((CMSIS_Dname MATCHES "STM32H7P.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32H7P.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13")) AND (((CMSIS_Dname MATCHES "STM32H7P.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32H7P.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13")) AND ((CMSIS_Dname MATCHES "STM32H7P.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32H7P.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13")))))
  set(STMicroelectronics.stm32h7pxx_hal_drivers.2.0.0-alpha.2.0:HAL_CORE_GPIO_DMA_Init_and_SMARTCARD true)
  message(DEBUG "CMSIS condition STMicroelectronics.stm32h7pxx_hal_drivers.2.0.0-alpha.2.0:HAL_CORE_GPIO_DMA_Init_and_SMARTCARD enabled")
endif()


# condition: STMicroelectronics.stm32h7pxx_hal_drivers.2.0.0-alpha.2.0:HAL CORE GPIO DMA Init and SPI
# description: STMicroelectronics HAL SPI Init dependencies
if((((CMSIS_Dname MATCHES "STM32H7P.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32H7P.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13")) AND (((CMSIS_Dname MATCHES "STM32H7P.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32H7P.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13")) AND ((CMSIS_Dname MATCHES "STM32H7P.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32H7P.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13")))))
  set(STMicroelectronics.stm32h7pxx_hal_drivers.2.0.0-alpha.2.0:HAL_CORE_GPIO_DMA_Init_and_SPI true)
  message(DEBUG "CMSIS condition STMicroelectronics.stm32h7pxx_hal_drivers.2.0.0-alpha.2.0:HAL_CORE_GPIO_DMA_Init_and_SPI enabled")
endif()


# condition: STMicroelectronics.stm32h7pxx_hal_drivers.2.0.0-alpha.2.0:HAL CORE GPIO DMA Init and TIM
# description: STMicroelectronics HAL TIM Init dependencies
if(((CMSIS_Dname MATCHES "STM32H7P.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32H7P.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13")))
  set(STMicroelectronics.stm32h7pxx_hal_drivers.2.0.0-alpha.2.0:HAL_CORE_GPIO_DMA_Init_and_TIM true)
  message(DEBUG "CMSIS condition STMicroelectronics.stm32h7pxx_hal_drivers.2.0.0-alpha.2.0:HAL_CORE_GPIO_DMA_Init_and_TIM enabled")
endif()


# condition: STMicroelectronics.stm32h7pxx_hal_drivers.2.0.0-alpha.2.0:HAL CORE GPIO DMA Init and UART
# description: STMicroelectronics HAL UART Init dependencies
if((((CMSIS_Dname MATCHES "STM32H7P.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32H7P.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13")) AND (((CMSIS_Dname MATCHES "STM32H7P.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32H7P.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13")) AND ((CMSIS_Dname MATCHES "STM32H7P.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32H7P.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13")))))
  set(STMicroelectronics.stm32h7pxx_hal_drivers.2.0.0-alpha.2.0:HAL_CORE_GPIO_DMA_Init_and_UART true)
  message(DEBUG "CMSIS condition STMicroelectronics.stm32h7pxx_hal_drivers.2.0.0-alpha.2.0:HAL_CORE_GPIO_DMA_Init_and_UART enabled")
endif()


# condition: STMicroelectronics.stm32h7pxx_hal_drivers.2.0.0-alpha.2.0:HAL CORE GPIO DMA Init and USART
# description: STMicroelectronics HAL USART Init dependencies
if((((CMSIS_Dname MATCHES "STM32H7P.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32H7P.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13")) AND (((CMSIS_Dname MATCHES "STM32H7P.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32H7P.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13")) AND ((CMSIS_Dname MATCHES "STM32H7P.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32H7P.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13")))))
  set(STMicroelectronics.stm32h7pxx_hal_drivers.2.0.0-alpha.2.0:HAL_CORE_GPIO_DMA_Init_and_USART true)
  message(DEBUG "CMSIS condition STMicroelectronics.stm32h7pxx_hal_drivers.2.0.0-alpha.2.0:HAL_CORE_GPIO_DMA_Init_and_USART enabled")
endif()


# condition: STMicroelectronics.stm32h7pxx_hal_drivers.2.0.0-alpha.2.0:HAL CORE GPIO DMA Init and XSPI
# description: STMicroelectronics HAL SPI Init dependencies
if((((CMSIS_Dname MATCHES "STM32H7P.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32H7P.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13")) AND (((CMSIS_Dname MATCHES "STM32H7P.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32H7P.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13")) AND ((CMSIS_Dname MATCHES "STM32H7P.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32H7P.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13")))))
  set(STMicroelectronics.stm32h7pxx_hal_drivers.2.0.0-alpha.2.0:HAL_CORE_GPIO_DMA_Init_and_XSPI true)
  message(DEBUG "CMSIS condition STMicroelectronics.stm32h7pxx_hal_drivers.2.0.0-alpha.2.0:HAL_CORE_GPIO_DMA_Init_and_XSPI enabled")
endif()


# condition: STMicroelectronics.stm32h7pxx_hal_drivers.2.0.0-alpha.2.0:HAL CORE GPIO Init and COMP
# description: HAL COMP Init dependencies
if(((((CMSIS_Dname MATCHES "STM32H7P.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32H7P.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13")) AND ((CMSIS_Dname MATCHES "STM32H7P.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32H7P.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13"))) AND (((CMSIS_Dname MATCHES "STM32H7P.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32H7P.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13")) AND ((CMSIS_Dname MATCHES "STM32H7P.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32H7P.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13"))) AND ((CMSIS_Dname MATCHES "STM32H7P.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32H7P.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13"))))
  set(STMicroelectronics.stm32h7pxx_hal_drivers.2.0.0-alpha.2.0:HAL_CORE_GPIO_Init_and_COMP true)
  message(DEBUG "CMSIS condition STMicroelectronics.stm32h7pxx_hal_drivers.2.0.0-alpha.2.0:HAL_CORE_GPIO_Init_and_COMP enabled")
endif()


# condition: STMicroelectronics.stm32h7pxx_hal_drivers.2.0.0-alpha.2.0:HAL CORE GPIO Init and FDCAN
# description: STMicroelectronics HAL FDCAN Init dependencies
if(((((CMSIS_Dname MATCHES "STM32H7P.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32H7P.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13")) AND ((CMSIS_Dname MATCHES "STM32H7P.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32H7P.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13"))) AND (((CMSIS_Dname MATCHES "STM32H7P.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32H7P.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13")) AND ((CMSIS_Dname MATCHES "STM32H7P.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32H7P.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13")))))
  set(STMicroelectronics.stm32h7pxx_hal_drivers.2.0.0-alpha.2.0:HAL_CORE_GPIO_Init_and_FDCAN true)
  message(DEBUG "CMSIS condition STMicroelectronics.stm32h7pxx_hal_drivers.2.0.0-alpha.2.0:HAL_CORE_GPIO_Init_and_FDCAN enabled")
endif()


# condition: STMicroelectronics.stm32h7pxx_hal_drivers.2.0.0-alpha.2.0:HAL CORE GPIO Init and HCD
# description: STMicroelectronics HAL HCD Init dependencies
if((((CMSIS_Dname MATCHES "STM32H7P.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32H7P.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13")) AND (((CMSIS_Dname MATCHES "STM32H7P.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32H7P.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13")) AND ((CMSIS_Dname MATCHES "STM32H7P.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32H7P.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13"))) AND (((CMSIS_Dname MATCHES "STM32H7P.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32H7P.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13")) AND ((CMSIS_Dname MATCHES "STM32H7P.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32H7P.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13")))))
  set(STMicroelectronics.stm32h7pxx_hal_drivers.2.0.0-alpha.2.0:HAL_CORE_GPIO_Init_and_HCD true)
  message(DEBUG "CMSIS condition STMicroelectronics.stm32h7pxx_hal_drivers.2.0.0-alpha.2.0:HAL_CORE_GPIO_Init_and_HCD enabled")
endif()


# condition: STMicroelectronics.stm32h7pxx_hal_drivers.2.0.0-alpha.2.0:HAL CORE GPIO Init and MMC
# description: STMicroelectronics HAL MMC Init dependencies
if(((((CMSIS_Dname MATCHES "STM32H7P.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32H7P.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13")) AND ((CMSIS_Dname MATCHES "STM32H7P.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32H7P.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13"))) AND (((CMSIS_Dname MATCHES "STM32H7P.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32H7P.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13")) AND ((CMSIS_Dname MATCHES "STM32H7P.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32H7P.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13")))))
  set(STMicroelectronics.stm32h7pxx_hal_drivers.2.0.0-alpha.2.0:HAL_CORE_GPIO_Init_and_MMC true)
  message(DEBUG "CMSIS condition STMicroelectronics.stm32h7pxx_hal_drivers.2.0.0-alpha.2.0:HAL_CORE_GPIO_Init_and_MMC enabled")
endif()


# condition: STMicroelectronics.stm32h7pxx_hal_drivers.2.0.0-alpha.2.0:HAL CORE GPIO Init and PCD
# description: STMicroelectronics HAL PCD Init dependencies
if((((CMSIS_Dname MATCHES "STM32H7P.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32H7P.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13")) AND (((CMSIS_Dname MATCHES "STM32H7P.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32H7P.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13")) AND ((CMSIS_Dname MATCHES "STM32H7P.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32H7P.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13"))) AND (((CMSIS_Dname MATCHES "STM32H7P.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32H7P.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13")) AND ((CMSIS_Dname MATCHES "STM32H7P.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32H7P.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13")))))
  set(STMicroelectronics.stm32h7pxx_hal_drivers.2.0.0-alpha.2.0:HAL_CORE_GPIO_Init_and_PCD true)
  message(DEBUG "CMSIS condition STMicroelectronics.stm32h7pxx_hal_drivers.2.0.0-alpha.2.0:HAL_CORE_GPIO_Init_and_PCD enabled")
endif()


# condition: STMicroelectronics.stm32h7pxx_hal_drivers.2.0.0-alpha.2.0:HAL CORE GPIO Init and RTC
# description: STMicroelectronics HAL RTC Init dependencies
if((((CMSIS_Dname MATCHES "STM32H7P.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32H7P.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13")) AND (((CMSIS_Dname MATCHES "STM32H7P.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32H7P.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13")) AND ((CMSIS_Dname MATCHES "STM32H7P.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32H7P.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13"))) AND (((CMSIS_Dname MATCHES "STM32H7P.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32H7P.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13")) AND ((CMSIS_Dname MATCHES "STM32H7P.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32H7P.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13")))))
  set(STMicroelectronics.stm32h7pxx_hal_drivers.2.0.0-alpha.2.0:HAL_CORE_GPIO_Init_and_RTC true)
  message(DEBUG "CMSIS condition STMicroelectronics.stm32h7pxx_hal_drivers.2.0.0-alpha.2.0:HAL_CORE_GPIO_Init_and_RTC enabled")
endif()


# condition: STMicroelectronics.stm32h7pxx_hal_drivers.2.0.0-alpha.2.0:HAL CORE GPIO Init and SD
# description: STMicroelectronics HAL SD Init dependencies
if(((((CMSIS_Dname MATCHES "STM32H7P.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32H7P.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13")) AND ((CMSIS_Dname MATCHES "STM32H7P.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32H7P.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13"))) AND (((CMSIS_Dname MATCHES "STM32H7P.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32H7P.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13")) AND ((CMSIS_Dname MATCHES "STM32H7P.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32H7P.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13")))))
  set(STMicroelectronics.stm32h7pxx_hal_drivers.2.0.0-alpha.2.0:HAL_CORE_GPIO_Init_and_SD true)
  message(DEBUG "CMSIS condition STMicroelectronics.stm32h7pxx_hal_drivers.2.0.0-alpha.2.0:HAL_CORE_GPIO_Init_and_SD enabled")
endif()


# condition: STMicroelectronics.stm32h7pxx_hal_drivers.2.0.0-alpha.2.0:HAL CORE GPIO Init and SDIO
# description: STMicroelectronics HAL SDIO Init dependencies
if(((((CMSIS_Dname MATCHES "STM32H7P.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32H7P.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13")) AND ((CMSIS_Dname MATCHES "STM32H7P.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32H7P.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13"))) AND (((CMSIS_Dname MATCHES "STM32H7P.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32H7P.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13")) AND ((CMSIS_Dname MATCHES "STM32H7P.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32H7P.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13")))))
  set(STMicroelectronics.stm32h7pxx_hal_drivers.2.0.0-alpha.2.0:HAL_CORE_GPIO_Init_and_SDIO true)
  message(DEBUG "CMSIS condition STMicroelectronics.stm32h7pxx_hal_drivers.2.0.0-alpha.2.0:HAL_CORE_GPIO_Init_and_SDIO enabled")
endif()


# condition: STMicroelectronics.stm32h7pxx_hal_drivers.2.0.0-alpha.2.0:HAL CORE GPIO Init and SMBUS
# description: STMicroelectronics HAL SMBUS Init dependencies
if((((CMSIS_Dname MATCHES "STM32H7P.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32H7P.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13")) AND (((CMSIS_Dname MATCHES "STM32H7P.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32H7P.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13")) AND ((CMSIS_Dname MATCHES "STM32H7P.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32H7P.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13"))) AND (((CMSIS_Dname MATCHES "STM32H7P.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32H7P.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13")) AND ((CMSIS_Dname MATCHES "STM32H7P.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32H7P.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13")))))
  set(STMicroelectronics.stm32h7pxx_hal_drivers.2.0.0-alpha.2.0:HAL_CORE_GPIO_Init_and_SMBUS true)
  message(DEBUG "CMSIS condition STMicroelectronics.stm32h7pxx_hal_drivers.2.0.0-alpha.2.0:HAL_CORE_GPIO_Init_and_SMBUS enabled")
endif()


# condition: STMicroelectronics.stm32h7pxx_hal_drivers.2.0.0-alpha.2.0:HAL CORE GPIO Init and TAMP
# description: STMicroelectronics HAL TAMP Init dependencies
if((((CMSIS_Dname MATCHES "STM32H7P.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32H7P.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13")) AND (((CMSIS_Dname MATCHES "STM32H7P.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32H7P.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13")) AND ((CMSIS_Dname MATCHES "STM32H7P.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32H7P.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13"))) AND (((CMSIS_Dname MATCHES "STM32H7P.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32H7P.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13")) AND ((CMSIS_Dname MATCHES "STM32H7P.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32H7P.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13")))))
  set(STMicroelectronics.stm32h7pxx_hal_drivers.2.0.0-alpha.2.0:HAL_CORE_GPIO_Init_and_TAMP true)
  message(DEBUG "CMSIS condition STMicroelectronics.stm32h7pxx_hal_drivers.2.0.0-alpha.2.0:HAL_CORE_GPIO_Init_and_TAMP enabled")
endif()


# condition: STMicroelectronics.stm32h7pxx_hal_drivers.2.0.0-alpha.2.0:HAL CORE Init and CORTEX
# description: STMicroelectronics HAL CORTEX Init dependencies
if(((CMSIS_Dname MATCHES "STM32H7P.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32H7P.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13")))
  set(STMicroelectronics.stm32h7pxx_hal_drivers.2.0.0-alpha.2.0:HAL_CORE_Init_and_CORTEX true)
  message(DEBUG "CMSIS condition STMicroelectronics.stm32h7pxx_hal_drivers.2.0.0-alpha.2.0:HAL_CORE_Init_and_CORTEX enabled")
endif()


# condition: STMicroelectronics.stm32h7pxx_hal_drivers.2.0.0-alpha.2.0:HAL CORE Init and CRC
# description: STMicroelectronics HAL CRC Init dependencies
if(((CMSIS_Dname MATCHES "STM32H7P.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32H7P.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13")))
  set(STMicroelectronics.stm32h7pxx_hal_drivers.2.0.0-alpha.2.0:HAL_CORE_Init_and_CRC true)
  message(DEBUG "CMSIS condition STMicroelectronics.stm32h7pxx_hal_drivers.2.0.0-alpha.2.0:HAL_CORE_Init_and_CRC enabled")
endif()


# condition: STMicroelectronics.stm32h7pxx_hal_drivers.2.0.0-alpha.2.0:HAL CORE Init and CRS
# description: STMicroelectronics HAL CRS Init dependencies
if(((CMSIS_Dname MATCHES "STM32H7P.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32H7P.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13")))
  set(STMicroelectronics.stm32h7pxx_hal_drivers.2.0.0-alpha.2.0:HAL_CORE_Init_and_CRS true)
  message(DEBUG "CMSIS condition STMicroelectronics.stm32h7pxx_hal_drivers.2.0.0-alpha.2.0:HAL_CORE_Init_and_CRS enabled")
endif()


# condition: STMicroelectronics.stm32h7pxx_hal_drivers.2.0.0-alpha.2.0:HAL CORE Init and DTS
# description: STMicroelectronics HAL DTS Init dependencies
if((((CMSIS_Dname MATCHES "STM32H7P.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32H7P.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13")) AND ((CMSIS_Dname MATCHES "STM32H7P.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32H7P.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13"))))
  set(STMicroelectronics.stm32h7pxx_hal_drivers.2.0.0-alpha.2.0:HAL_CORE_Init_and_DTS true)
  message(DEBUG "CMSIS condition STMicroelectronics.stm32h7pxx_hal_drivers.2.0.0-alpha.2.0:HAL_CORE_Init_and_DTS enabled")
endif()


# condition: STMicroelectronics.stm32h7pxx_hal_drivers.2.0.0-alpha.2.0:HAL CORE Init and FLASH
# description: STMicroelectronics HAL FLASH Init dependencies
if((((CMSIS_Dname MATCHES "STM32H7P.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32H7P.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13")) AND (((CMSIS_Dname MATCHES "STM32H7P.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32H7P.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13")) AND ((CMSIS_Dname MATCHES "STM32H7P.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32H7P.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13")))))
  set(STMicroelectronics.stm32h7pxx_hal_drivers.2.0.0-alpha.2.0:HAL_CORE_Init_and_FLASH true)
  message(DEBUG "CMSIS condition STMicroelectronics.stm32h7pxx_hal_drivers.2.0.0-alpha.2.0:HAL_CORE_Init_and_FLASH enabled")
endif()


# condition: STMicroelectronics.stm32h7pxx_hal_drivers.2.0.0-alpha.2.0:HAL CORE Init and IWDG
# description: STMicroelectronics HAL IWDG Init dependencies
if(((CMSIS_Dname MATCHES "STM32H7P.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32H7P.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13")))
  set(STMicroelectronics.stm32h7pxx_hal_drivers.2.0.0-alpha.2.0:HAL_CORE_Init_and_IWDG true)
  message(DEBUG "CMSIS condition STMicroelectronics.stm32h7pxx_hal_drivers.2.0.0-alpha.2.0:HAL_CORE_Init_and_IWDG enabled")
endif()


# condition: STMicroelectronics.stm32h7pxx_hal_drivers.2.0.0-alpha.2.0:HAL CORE Init and RAMECC
# description: STMicroelectronics HAL RAMECC Init dependencies
if(((CMSIS_Dname MATCHES "STM32H7P.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32H7P.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13")))
  set(STMicroelectronics.stm32h7pxx_hal_drivers.2.0.0-alpha.2.0:HAL_CORE_Init_and_RAMECC true)
  message(DEBUG "CMSIS condition STMicroelectronics.stm32h7pxx_hal_drivers.2.0.0-alpha.2.0:HAL_CORE_Init_and_RAMECC enabled")
endif()


# condition: STMicroelectronics.stm32h7pxx_hal_drivers.2.0.0-alpha.2.0:HAL CORE Init and RNG
# description: STMicroelectronics HAL RNG Init dependencies
if(((CMSIS_Dname MATCHES "STM32H7P.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32H7P.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13")))
  set(STMicroelectronics.stm32h7pxx_hal_drivers.2.0.0-alpha.2.0:HAL_CORE_Init_and_RNG true)
  message(DEBUG "CMSIS condition STMicroelectronics.stm32h7pxx_hal_drivers.2.0.0-alpha.2.0:HAL_CORE_Init_and_RNG enabled")
endif()


# condition: STMicroelectronics.stm32h7pxx_hal_drivers.2.0.0-alpha.2.0:HAL CORE Init and SBS
# description: STMicroelectronics HAL SBS Init dependencies
if(((CMSIS_Dname MATCHES "STM32H7P.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32H7P.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13")))
  set(STMicroelectronics.stm32h7pxx_hal_drivers.2.0.0-alpha.2.0:HAL_CORE_Init_and_SBS true)
  message(DEBUG "CMSIS condition STMicroelectronics.stm32h7pxx_hal_drivers.2.0.0-alpha.2.0:HAL_CORE_Init_and_SBS enabled")
endif()


# condition: STMicroelectronics.stm32h7pxx_hal_drivers.2.0.0-alpha.2.0:HAL CORE Init and SRAM
# description: STMicroelectronics HAL SRAM Init dependencies
if(((CMSIS_Dname MATCHES "STM32H7P.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32H7P.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13")))
  set(STMicroelectronics.stm32h7pxx_hal_drivers.2.0.0-alpha.2.0:HAL_CORE_Init_and_SRAM true)
  message(DEBUG "CMSIS condition STMicroelectronics.stm32h7pxx_hal_drivers.2.0.0-alpha.2.0:HAL_CORE_Init_and_SRAM enabled")
endif()


# condition: STMicroelectronics.stm32h7pxx_hal_drivers.2.0.0-alpha.2.0:HAL CORE Init and VREFBUF
# description: STMicroelectronics HAL VREFBUF Init dependencies
if((((CMSIS_Dname MATCHES "STM32H7P.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32H7P.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13")) AND ((CMSIS_Dname MATCHES "STM32H7P.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32H7P.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13"))))
  set(STMicroelectronics.stm32h7pxx_hal_drivers.2.0.0-alpha.2.0:HAL_CORE_Init_and_VREFBUF true)
  message(DEBUG "CMSIS condition STMicroelectronics.stm32h7pxx_hal_drivers.2.0.0-alpha.2.0:HAL_CORE_Init_and_VREFBUF enabled")
endif()


# condition: STMicroelectronics.stm32h7pxx_hal_drivers.2.0.0-alpha.2.0:HAL CORE Init and WWDG
# description: STMicroelectronics HAL WWDG Init dependencies
if((((CMSIS_Dname MATCHES "STM32H7P.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32H7P.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13")) AND (((CMSIS_Dname MATCHES "STM32H7P.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32H7P.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13")) AND ((CMSIS_Dname MATCHES "STM32H7P.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32H7P.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13")))))
  set(STMicroelectronics.stm32h7pxx_hal_drivers.2.0.0-alpha.2.0:HAL_CORE_Init_and_WWDG true)
  message(DEBUG "CMSIS condition STMicroelectronics.stm32h7pxx_hal_drivers.2.0.0-alpha.2.0:HAL_CORE_Init_and_WWDG enabled")
endif()


# condition: STMicroelectronics.stm32h7pxx_hal_drivers.2.0.0-alpha.2.0:HAL CORE SDMMC
# description: HAL CORE SDMMC dependencies
if(((CMSIS_Dname MATCHES "STM32H7P.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32H7P.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13")))
  set(STMicroelectronics.stm32h7pxx_hal_drivers.2.0.0-alpha.2.0:HAL_CORE_SDMMC true)
  message(DEBUG "CMSIS condition STMicroelectronics.stm32h7pxx_hal_drivers.2.0.0-alpha.2.0:HAL_CORE_SDMMC enabled")
endif()


# condition: STMicroelectronics.stm32h7pxx_hal_drivers.2.0.0-alpha.2.0:HAL CORE SRAM
# description: HAL CORE SRAM dependencies
if((((CMSIS_Dname MATCHES "STM32H7P.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32H7P.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13")) AND ((CMSIS_Dname MATCHES "STM32H7P.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32H7P.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13"))))
  set(STMicroelectronics.stm32h7pxx_hal_drivers.2.0.0-alpha.2.0:HAL_CORE_SRAM true)
  message(DEBUG "CMSIS condition STMicroelectronics.stm32h7pxx_hal_drivers.2.0.0-alpha.2.0:HAL_CORE_SRAM enabled")
endif()


# condition: STMicroelectronics.stm32h7pxx_hal_drivers.2.0.0-alpha.2.0:HAL CORE USB
# description: HAL CORE USB dependencies
if(((CMSIS_Dname MATCHES "STM32H7P.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32H7P.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13")))
  set(STMicroelectronics.stm32h7pxx_hal_drivers.2.0.0-alpha.2.0:HAL_CORE_USB true)
  message(DEBUG "CMSIS condition STMicroelectronics.stm32h7pxx_hal_drivers.2.0.0-alpha.2.0:HAL_CORE_USB enabled")
endif()


# condition: STMicroelectronics.stm32h7pxx_hal_drivers.2.0.0-alpha.2.0:HAL CORE XSPI
# description: HAL CORE XSPI dependencies
if(((CMSIS_Dname MATCHES "STM32H7P.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32H7P.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13")))
  set(STMicroelectronics.stm32h7pxx_hal_drivers.2.0.0-alpha.2.0:HAL_CORE_XSPI true)
  message(DEBUG "CMSIS condition STMicroelectronics.stm32h7pxx_hal_drivers.2.0.0-alpha.2.0:HAL_CORE_XSPI enabled")
endif()


# condition: STMicroelectronics.stm32h7pxx_hal_drivers.2.0.0-alpha.2.0:HAL CORTEX
# description: HAL CORTEX dependencies
if(((CMSIS_Dname MATCHES "STM32H7P.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32H7P.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13")))
  set(STMicroelectronics.stm32h7pxx_hal_drivers.2.0.0-alpha.2.0:HAL_CORTEX true)
  message(DEBUG "CMSIS condition STMicroelectronics.stm32h7pxx_hal_drivers.2.0.0-alpha.2.0:HAL_CORTEX enabled")
endif()


# condition: STMicroelectronics.stm32h7pxx_hal_drivers.2.0.0-alpha.2.0:HAL CRC
# description: HAL CRC dependencies
if(((CMSIS_Dname MATCHES "STM32H7P.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32H7P.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13")))
  set(STMicroelectronics.stm32h7pxx_hal_drivers.2.0.0-alpha.2.0:HAL_CRC true)
  message(DEBUG "CMSIS condition STMicroelectronics.stm32h7pxx_hal_drivers.2.0.0-alpha.2.0:HAL_CRC enabled")
endif()


# condition: STMicroelectronics.stm32h7pxx_hal_drivers.2.0.0-alpha.2.0:HAL CRS
# description: HAL CRS dependencies
if(((CMSIS_Dname MATCHES "STM32H7P.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32H7P.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13")))
  set(STMicroelectronics.stm32h7pxx_hal_drivers.2.0.0-alpha.2.0:HAL_CRS true)
  message(DEBUG "CMSIS condition STMicroelectronics.stm32h7pxx_hal_drivers.2.0.0-alpha.2.0:HAL_CRS enabled")
endif()


# condition: STMicroelectronics.stm32h7pxx_hal_drivers.2.0.0-alpha.2.0:HAL Common
# description: STMicroelectronics STM32H7P and HAL common
if(((CMSIS_Dname MATCHES "STM32H7P.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32H7P.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13")))
  set(STMicroelectronics.stm32h7pxx_hal_drivers.2.0.0-alpha.2.0:HAL_Common true)
  message(DEBUG "CMSIS condition STMicroelectronics.stm32h7pxx_hal_drivers.2.0.0-alpha.2.0:HAL_Common enabled")
endif()


# condition: STMicroelectronics.stm32h7pxx_hal_drivers.2.0.0-alpha.2.0:HAL DAC
# description: HAL DAC dependencies
if((((CMSIS_Dname MATCHES "STM32H7P.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32H7P.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13")) AND ((CMSIS_Dname MATCHES "STM32H7P.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32H7P.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13"))))
  set(STMicroelectronics.stm32h7pxx_hal_drivers.2.0.0-alpha.2.0:HAL_DAC true)
  message(DEBUG "CMSIS condition STMicroelectronics.stm32h7pxx_hal_drivers.2.0.0-alpha.2.0:HAL_DAC enabled")
endif()


# condition: STMicroelectronics.stm32h7pxx_hal_drivers.2.0.0-alpha.2.0:HAL DBGMCU
# description: HAL DBGMCU dependencies
if(((CMSIS_Dname MATCHES "STM32H7P.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32H7P.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13")))
  set(STMicroelectronics.stm32h7pxx_hal_drivers.2.0.0-alpha.2.0:HAL_DBGMCU true)
  message(DEBUG "CMSIS condition STMicroelectronics.stm32h7pxx_hal_drivers.2.0.0-alpha.2.0:HAL_DBGMCU enabled")
endif()


# condition: STMicroelectronics.stm32h7pxx_hal_drivers.2.0.0-alpha.2.0:HAL DMA
# description: HAL DMA dependencies
if(((CMSIS_Dname MATCHES "STM32H7P.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32H7P.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13")))
  set(STMicroelectronics.stm32h7pxx_hal_drivers.2.0.0-alpha.2.0:HAL_DMA true)
  message(DEBUG "CMSIS condition STMicroelectronics.stm32h7pxx_hal_drivers.2.0.0-alpha.2.0:HAL_DMA enabled")
endif()


# condition: STMicroelectronics.stm32h7pxx_hal_drivers.2.0.0-alpha.2.0:HAL EXTI
# description: HAL EXTI dependencies
if(((CMSIS_Dname MATCHES "STM32H7P.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32H7P.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13")))
  set(STMicroelectronics.stm32h7pxx_hal_drivers.2.0.0-alpha.2.0:HAL_EXTI true)
  message(DEBUG "CMSIS condition STMicroelectronics.stm32h7pxx_hal_drivers.2.0.0-alpha.2.0:HAL_EXTI enabled")
endif()


# condition: STMicroelectronics.stm32h7pxx_hal_drivers.2.0.0-alpha.2.0:HAL FLASH
# description: HAL FLASH dependencies
if(((CMSIS_Dname MATCHES "STM32H7P.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32H7P.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13")))
  set(STMicroelectronics.stm32h7pxx_hal_drivers.2.0.0-alpha.2.0:HAL_FLASH true)
  message(DEBUG "CMSIS condition STMicroelectronics.stm32h7pxx_hal_drivers.2.0.0-alpha.2.0:HAL_FLASH enabled")
endif()


# condition: STMicroelectronics.stm32h7pxx_hal_drivers.2.0.0-alpha.2.0:HAL FLASH_ITF
# description: HAL FLASH_ITF dependencies
if(((CMSIS_Dname MATCHES "STM32H7P.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32H7P.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13")))
  set(STMicroelectronics.stm32h7pxx_hal_drivers.2.0.0-alpha.2.0:HAL_FLASH_ITF true)
  message(DEBUG "CMSIS condition STMicroelectronics.stm32h7pxx_hal_drivers.2.0.0-alpha.2.0:HAL_FLASH_ITF enabled")
endif()


# condition: STMicroelectronics.stm32h7pxx_hal_drivers.2.0.0-alpha.2.0:HAL FMAC
# description: HAL FMAC dependencies
if((((CMSIS_Dname MATCHES "STM32H7P.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32H7P.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13")) AND ((CMSIS_Dname MATCHES "STM32H7P.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32H7P.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13"))))
  set(STMicroelectronics.stm32h7pxx_hal_drivers.2.0.0-alpha.2.0:HAL_FMAC true)
  message(DEBUG "CMSIS condition STMicroelectronics.stm32h7pxx_hal_drivers.2.0.0-alpha.2.0:HAL_FMAC enabled")
endif()


# condition: STMicroelectronics.stm32h7pxx_hal_drivers.2.0.0-alpha.2.0:HAL GPIO
# description: HAL GPIO dependencies
if(((CMSIS_Dname MATCHES "STM32H7P.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32H7P.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13")))
  set(STMicroelectronics.stm32h7pxx_hal_drivers.2.0.0-alpha.2.0:HAL_GPIO true)
  message(DEBUG "CMSIS condition STMicroelectronics.stm32h7pxx_hal_drivers.2.0.0-alpha.2.0:HAL_GPIO enabled")
endif()


# condition: STMicroelectronics.stm32h7pxx_hal_drivers.2.0.0-alpha.2.0:HAL GPIO Init
# description: STMicroelectronics HAL Common Init
if((((CMSIS_Dname MATCHES "STM32H7P.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32H7P.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13")) AND ((CMSIS_Dname MATCHES "STM32H7P.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32H7P.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13"))))
  set(STMicroelectronics.stm32h7pxx_hal_drivers.2.0.0-alpha.2.0:HAL_GPIO_Init true)
  message(DEBUG "CMSIS condition STMicroelectronics.stm32h7pxx_hal_drivers.2.0.0-alpha.2.0:HAL_GPIO_Init enabled")
endif()


# condition: STMicroelectronics.stm32h7pxx_hal_drivers.2.0.0-alpha.2.0:HAL Generated code
# description: STMicroelectronics HAL components used for code Generation
if((((CMSIS_Dname MATCHES "STM32H7P.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32H7P.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13")) AND ((CMSIS_Dname MATCHES "STM32H7P.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32H7P.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13"))))
  set(STMicroelectronics.stm32h7pxx_hal_drivers.2.0.0-alpha.2.0:HAL_Generated_code true)
  message(DEBUG "CMSIS condition STMicroelectronics.stm32h7pxx_hal_drivers.2.0.0-alpha.2.0:HAL_Generated_code enabled")
endif()


# condition: STMicroelectronics.stm32h7pxx_hal_drivers.2.0.0-alpha.2.0:HAL HRTIM
# description: HAL HRTIM dependencies
if((((CMSIS_Dname MATCHES "STM32H7P.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32H7P.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13")) AND ((CMSIS_Dname MATCHES "STM32H7P.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32H7P.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13"))))
  set(STMicroelectronics.stm32h7pxx_hal_drivers.2.0.0-alpha.2.0:HAL_HRTIM true)
  message(DEBUG "CMSIS condition STMicroelectronics.stm32h7pxx_hal_drivers.2.0.0-alpha.2.0:HAL_HRTIM enabled")
endif()


# condition: STMicroelectronics.stm32h7pxx_hal_drivers.2.0.0-alpha.2.0:HAL HSP
# description: HAL HSP dependencies
if((((CMSIS_Dname MATCHES "STM32H7P.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32H7P.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13")) AND ((CMSIS_Dname MATCHES "STM32H7P.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32H7P.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13"))))
  set(STMicroelectronics.stm32h7pxx_hal_drivers.2.0.0-alpha.2.0:HAL_HSP true)
  message(DEBUG "CMSIS condition STMicroelectronics.stm32h7pxx_hal_drivers.2.0.0-alpha.2.0:HAL_HSP enabled")
endif()


# condition: STMicroelectronics.stm32h7pxx_hal_drivers.2.0.0-alpha.2.0:HAL I2C
# description: HAL I2C dependencies
if((((CMSIS_Dname MATCHES "STM32H7P.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32H7P.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13")) AND ((CMSIS_Dname MATCHES "STM32H7P.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32H7P.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13"))))
  set(STMicroelectronics.stm32h7pxx_hal_drivers.2.0.0-alpha.2.0:HAL_I2C true)
  message(DEBUG "CMSIS condition STMicroelectronics.stm32h7pxx_hal_drivers.2.0.0-alpha.2.0:HAL_I2C enabled")
endif()


# condition: STMicroelectronics.stm32h7pxx_hal_drivers.2.0.0-alpha.2.0:HAL I2S
# description: HAL I2S dependencies
if((((CMSIS_Dname MATCHES "STM32H7P.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32H7P.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13")) AND ((CMSIS_Dname MATCHES "STM32H7P.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32H7P.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13"))))
  set(STMicroelectronics.stm32h7pxx_hal_drivers.2.0.0-alpha.2.0:HAL_I2S true)
  message(DEBUG "CMSIS condition STMicroelectronics.stm32h7pxx_hal_drivers.2.0.0-alpha.2.0:HAL_I2S enabled")
endif()


# condition: STMicroelectronics.stm32h7pxx_hal_drivers.2.0.0-alpha.2.0:HAL I3C
# description: HAL I3C dependencies
if((((CMSIS_Dname MATCHES "STM32H7P.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32H7P.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13")) AND ((CMSIS_Dname MATCHES "STM32H7P.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32H7P.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13"))))
  set(STMicroelectronics.stm32h7pxx_hal_drivers.2.0.0-alpha.2.0:HAL_I3C true)
  message(DEBUG "CMSIS condition STMicroelectronics.stm32h7pxx_hal_drivers.2.0.0-alpha.2.0:HAL_I3C enabled")
endif()


# condition: STMicroelectronics.stm32h7pxx_hal_drivers.2.0.0-alpha.2.0:HAL IWDG
# description: HAL IWDG dependencies
if(((CMSIS_Dname MATCHES "STM32H7P.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32H7P.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13")))
  set(STMicroelectronics.stm32h7pxx_hal_drivers.2.0.0-alpha.2.0:HAL_IWDG true)
  message(DEBUG "CMSIS condition STMicroelectronics.stm32h7pxx_hal_drivers.2.0.0-alpha.2.0:HAL_IWDG enabled")
endif()


# condition: STMicroelectronics.stm32h7pxx_hal_drivers.2.0.0-alpha.2.0:HAL LPTIM
# description: HAL LPTIM dependencies
if(((CMSIS_Dname MATCHES "STM32H7P.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32H7P.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13")))
  set(STMicroelectronics.stm32h7pxx_hal_drivers.2.0.0-alpha.2.0:HAL_LPTIM true)
  message(DEBUG "CMSIS condition STMicroelectronics.stm32h7pxx_hal_drivers.2.0.0-alpha.2.0:HAL_LPTIM enabled")
endif()


# condition: STMicroelectronics.stm32h7pxx_hal_drivers.2.0.0-alpha.2.0:HAL PWR
# description: HAL PWR dependencies
if(((CMSIS_Dname MATCHES "STM32H7P.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32H7P.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13")))
  set(STMicroelectronics.stm32h7pxx_hal_drivers.2.0.0-alpha.2.0:HAL_PWR true)
  message(DEBUG "CMSIS condition STMicroelectronics.stm32h7pxx_hal_drivers.2.0.0-alpha.2.0:HAL_PWR enabled")
endif()


# condition: STMicroelectronics.stm32h7pxx_hal_drivers.2.0.0-alpha.2.0:HAL RAMECC
# description: HAL RAMECC dependencies
if(((CMSIS_Dname MATCHES "STM32H7P.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32H7P.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13")))
  set(STMicroelectronics.stm32h7pxx_hal_drivers.2.0.0-alpha.2.0:HAL_RAMECC true)
  message(DEBUG "CMSIS condition STMicroelectronics.stm32h7pxx_hal_drivers.2.0.0-alpha.2.0:HAL_RAMECC enabled")
endif()


# condition: STMicroelectronics.stm32h7pxx_hal_drivers.2.0.0-alpha.2.0:HAL RCC
# description: HAL RCC dependencies
if(((CMSIS_Dname MATCHES "STM32H7P.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32H7P.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13")))
  set(STMicroelectronics.stm32h7pxx_hal_drivers.2.0.0-alpha.2.0:HAL_RCC true)
  message(DEBUG "CMSIS condition STMicroelectronics.stm32h7pxx_hal_drivers.2.0.0-alpha.2.0:HAL_RCC enabled")
endif()


# condition: STMicroelectronics.stm32h7pxx_hal_drivers.2.0.0-alpha.2.0:HAL RNG
# description: HAL RNG dependencies
if(((CMSIS_Dname MATCHES "STM32H7P.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32H7P.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13")))
  set(STMicroelectronics.stm32h7pxx_hal_drivers.2.0.0-alpha.2.0:HAL_RNG true)
  message(DEBUG "CMSIS condition STMicroelectronics.stm32h7pxx_hal_drivers.2.0.0-alpha.2.0:HAL_RNG enabled")
endif()


# condition: STMicroelectronics.stm32h7pxx_hal_drivers.2.0.0-alpha.2.0:HAL RTC
# description: HAL RTC dependencies
if(((CMSIS_Dname MATCHES "STM32H7P.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32H7P.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13")))
  set(STMicroelectronics.stm32h7pxx_hal_drivers.2.0.0-alpha.2.0:HAL_RTC true)
  message(DEBUG "CMSIS condition STMicroelectronics.stm32h7pxx_hal_drivers.2.0.0-alpha.2.0:HAL_RTC enabled")
endif()


# condition: STMicroelectronics.stm32h7pxx_hal_drivers.2.0.0-alpha.2.0:HAL SBS
# description: HAL SBS dependencies
if(((CMSIS_Dname MATCHES "STM32H7P.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32H7P.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13")))
  set(STMicroelectronics.stm32h7pxx_hal_drivers.2.0.0-alpha.2.0:HAL_SBS true)
  message(DEBUG "CMSIS condition STMicroelectronics.stm32h7pxx_hal_drivers.2.0.0-alpha.2.0:HAL_SBS enabled")
endif()


# condition: STMicroelectronics.stm32h7pxx_hal_drivers.2.0.0-alpha.2.0:HAL SMARTCARD
# description: HAL SMARTCARD dependencies
if((((CMSIS_Dname MATCHES "STM32H7P.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32H7P.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13")) AND ((CMSIS_Dname MATCHES "STM32H7P.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32H7P.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13"))))
  set(STMicroelectronics.stm32h7pxx_hal_drivers.2.0.0-alpha.2.0:HAL_SMARTCARD true)
  message(DEBUG "CMSIS condition STMicroelectronics.stm32h7pxx_hal_drivers.2.0.0-alpha.2.0:HAL_SMARTCARD enabled")
endif()


# condition: STMicroelectronics.stm32h7pxx_hal_drivers.2.0.0-alpha.2.0:HAL SMBUS
# description: HAL SMBUS dependencies
if((((CMSIS_Dname MATCHES "STM32H7P.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32H7P.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13")) AND ((CMSIS_Dname MATCHES "STM32H7P.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32H7P.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13"))))
  set(STMicroelectronics.stm32h7pxx_hal_drivers.2.0.0-alpha.2.0:HAL_SMBUS true)
  message(DEBUG "CMSIS condition STMicroelectronics.stm32h7pxx_hal_drivers.2.0.0-alpha.2.0:HAL_SMBUS enabled")
endif()


# condition: STMicroelectronics.stm32h7pxx_hal_drivers.2.0.0-alpha.2.0:HAL SPI
# description: HAL SPI dependencies
if((((CMSIS_Dname MATCHES "STM32H7P.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32H7P.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13")) AND ((CMSIS_Dname MATCHES "STM32H7P.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32H7P.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13"))))
  set(STMicroelectronics.stm32h7pxx_hal_drivers.2.0.0-alpha.2.0:HAL_SPI true)
  message(DEBUG "CMSIS condition STMicroelectronics.stm32h7pxx_hal_drivers.2.0.0-alpha.2.0:HAL_SPI enabled")
endif()


# condition: STMicroelectronics.stm32h7pxx_hal_drivers.2.0.0-alpha.2.0:HAL System Init
# description: STMicroelectronics HAL Common Init
if((((CMSIS_Dname MATCHES "STM32H7P.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32H7P.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13")) AND ((CMSIS_Dname MATCHES "STM32H7P.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32H7P.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13"))))
  set(STMicroelectronics.stm32h7pxx_hal_drivers.2.0.0-alpha.2.0:HAL_System_Init true)
  message(DEBUG "CMSIS condition STMicroelectronics.stm32h7pxx_hal_drivers.2.0.0-alpha.2.0:HAL_System_Init enabled")
endif()


# condition: STMicroelectronics.stm32h7pxx_hal_drivers.2.0.0-alpha.2.0:HAL TAMP
# description: HAL TAMP dependencies
if(((CMSIS_Dname MATCHES "STM32H7P.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32H7P.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13")))
  set(STMicroelectronics.stm32h7pxx_hal_drivers.2.0.0-alpha.2.0:HAL_TAMP true)
  message(DEBUG "CMSIS condition STMicroelectronics.stm32h7pxx_hal_drivers.2.0.0-alpha.2.0:HAL_TAMP enabled")
endif()


# condition: STMicroelectronics.stm32h7pxx_hal_drivers.2.0.0-alpha.2.0:HAL TIM
# description: HAL TIM dependencies
if((((CMSIS_Dname MATCHES "STM32H7P.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32H7P.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13")) AND ((CMSIS_Dname MATCHES "STM32H7P.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32H7P.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13"))))
  set(STMicroelectronics.stm32h7pxx_hal_drivers.2.0.0-alpha.2.0:HAL_TIM true)
  message(DEBUG "CMSIS condition STMicroelectronics.stm32h7pxx_hal_drivers.2.0.0-alpha.2.0:HAL_TIM enabled")
endif()


# condition: STMicroelectronics.stm32h7pxx_hal_drivers.2.0.0-alpha.2.0:HAL UART
# description: HAL UART dependencies
if((((CMSIS_Dname MATCHES "STM32H7P.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32H7P.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13")) AND ((CMSIS_Dname MATCHES "STM32H7P.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32H7P.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13"))))
  set(STMicroelectronics.stm32h7pxx_hal_drivers.2.0.0-alpha.2.0:HAL_UART true)
  message(DEBUG "CMSIS condition STMicroelectronics.stm32h7pxx_hal_drivers.2.0.0-alpha.2.0:HAL_UART enabled")
endif()


# condition: STMicroelectronics.stm32h7pxx_hal_drivers.2.0.0-alpha.2.0:HAL UCPD
# description: HAL UCPD dependencies
if((((CMSIS_Dname MATCHES "STM32H7P.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32H7P.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13")) AND ((CMSIS_Dname MATCHES "STM32H7P.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32H7P.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13"))))
  set(STMicroelectronics.stm32h7pxx_hal_drivers.2.0.0-alpha.2.0:HAL_UCPD true)
  message(DEBUG "CMSIS condition STMicroelectronics.stm32h7pxx_hal_drivers.2.0.0-alpha.2.0:HAL_UCPD enabled")
endif()


# condition: STMicroelectronics.stm32h7pxx_hal_drivers.2.0.0-alpha.2.0:HAL USART
# description: HAL USART dependencies
if((((CMSIS_Dname MATCHES "STM32H7P.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32H7P.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13")) AND ((CMSIS_Dname MATCHES "STM32H7P.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32H7P.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13"))))
  set(STMicroelectronics.stm32h7pxx_hal_drivers.2.0.0-alpha.2.0:HAL_USART true)
  message(DEBUG "CMSIS condition STMicroelectronics.stm32h7pxx_hal_drivers.2.0.0-alpha.2.0:HAL_USART enabled")
endif()


# condition: STMicroelectronics.stm32h7pxx_hal_drivers.2.0.0-alpha.2.0:HAL VREFBUF
# description: HAL VREFBUF dependencies
if(((CMSIS_Dname MATCHES "STM32H7P.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32H7P.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13")))
  set(STMicroelectronics.stm32h7pxx_hal_drivers.2.0.0-alpha.2.0:HAL_VREFBUF true)
  message(DEBUG "CMSIS condition STMicroelectronics.stm32h7pxx_hal_drivers.2.0.0-alpha.2.0:HAL_VREFBUF enabled")
endif()


# condition: STMicroelectronics.stm32h7pxx_hal_drivers.2.0.0-alpha.2.0:HAL WWDG
# description: HAL WWDG dependencies
if(((CMSIS_Dname MATCHES "STM32H7P.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32H7P.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13")))
  set(STMicroelectronics.stm32h7pxx_hal_drivers.2.0.0-alpha.2.0:HAL_WWDG true)
  message(DEBUG "CMSIS condition STMicroelectronics.stm32h7pxx_hal_drivers.2.0.0-alpha.2.0:HAL_WWDG enabled")
endif()


# condition: STMicroelectronics.stm32h7pxx_hal_drivers.2.0.0-alpha.2.0:LL
# description: STMicroelectronics STM32H7P and LL
if((CMSIS_Dname MATCHES "STM32H7P.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13"))
  set(STMicroelectronics.stm32h7pxx_hal_drivers.2.0.0-alpha.2.0:LL true)
  message(DEBUG "CMSIS condition STMicroelectronics.stm32h7pxx_hal_drivers.2.0.0-alpha.2.0:LL enabled")
endif()


# condition: STMicroelectronics.stm32h7pxx_hal_drivers.2.0.0-alpha.2.0:MW FreeRTOS
# description: MW FreeRTOS used for HAL OS
if((CMSIS_Dname MATCHES "STM32H7P.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13"))
  set(STMicroelectronics.stm32h7pxx_hal_drivers.2.0.0-alpha.2.0:MW_FreeRTOS true)
  message(DEBUG "CMSIS condition STMicroelectronics.stm32h7pxx_hal_drivers.2.0.0-alpha.2.0:MW_FreeRTOS enabled")
endif()


# condition: STMicroelectronics.stm32h7pxx_hal_drivers.2.0.0-alpha.2.0:NO OS
# description: NO MW used for HAL OS
if((CMSIS_Dname MATCHES "STM32H7P.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13"))
  set(STMicroelectronics.stm32h7pxx_hal_drivers.2.0.0-alpha.2.0:NO_OS true)
  message(DEBUG "CMSIS condition STMicroelectronics.stm32h7pxx_hal_drivers.2.0.0-alpha.2.0:NO_OS enabled")
endif()


# condition: STMicroelectronics.stm32h7pxx_hal_drivers.2.0.0-alpha.2.0:RCC Init
# description: STMicroelectronics HAL Common Init
if((((CMSIS_Dname MATCHES "STM32H7P.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32H7P.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13")) AND ((CMSIS_Dname MATCHES "STM32H7P.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32H7P.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13"))))
  set(STMicroelectronics.stm32h7pxx_hal_drivers.2.0.0-alpha.2.0:RCC_Init true)
  message(DEBUG "CMSIS condition STMicroelectronics.stm32h7pxx_hal_drivers.2.0.0-alpha.2.0:RCC_Init enabled")
endif()


# condition: STMicroelectronics.stm32h7pxx_hal_drivers.2.0.0-alpha.2.0:STM32H7P
# description: STMicroelectronics STM32H7P
if((CMSIS_Dname MATCHES "STM32H7P.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13"))
  set(STMicroelectronics.stm32h7pxx_hal_drivers.2.0.0-alpha.2.0:STM32H7P true)
  message(DEBUG "CMSIS condition STMicroelectronics.stm32h7pxx_hal_drivers.2.0.0-alpha.2.0:STM32H7P enabled")
endif()


# condition: STMicroelectronics.stm32h7pxx_hal_drivers.2.0.0-alpha.2.0:TEMPLATE OS
# description: TEMPLATE OS used for HAL OS
if((CMSIS_Dname MATCHES "STM32H7P.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13"))
  set(STMicroelectronics.stm32h7pxx_hal_drivers.2.0.0-alpha.2.0:TEMPLATE_OS true)
  message(DEBUG "CMSIS condition STMicroelectronics.stm32h7pxx_hal_drivers.2.0.0-alpha.2.0:TEMPLATE_OS enabled")
endif()


# condition: STMicroelectronics.stm32h7pxx_hal_drivers.2.0.0-alpha.2.0:Timebase
# description: 
set(STMicroelectronics.stm32h7pxx_hal_drivers.2.0.0-alpha.2.0:Timebase true)
message(DEBUG "CMSIS condition STMicroelectronics.stm32h7pxx_hal_drivers.2.0.0-alpha.2.0:Timebase enabled")


# condition: STMicroelectronics.stm32h7pxx_hal_drivers.2.0.0-alpha.2.0:Timebase HAL RTC ALARM
# description: HAL timebase based on RTC ALARM
if((CMSIS_Dname MATCHES "STM32H7P.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13"))
  set(STMicroelectronics.stm32h7pxx_hal_drivers.2.0.0-alpha.2.0:Timebase_HAL_RTC_ALARM true)
  message(DEBUG "CMSIS condition STMicroelectronics.stm32h7pxx_hal_drivers.2.0.0-alpha.2.0:Timebase_HAL_RTC_ALARM enabled")
endif()


# condition: STMicroelectronics.stm32h7pxx_hal_drivers.2.0.0-alpha.2.0:Timebase HAL RTC WKUP
# description: HAL timebase based on RTC WKUP
if((CMSIS_Dname MATCHES "STM32H7P.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13"))
  set(STMicroelectronics.stm32h7pxx_hal_drivers.2.0.0-alpha.2.0:Timebase_HAL_RTC_WKUP true)
  message(DEBUG "CMSIS condition STMicroelectronics.stm32h7pxx_hal_drivers.2.0.0-alpha.2.0:Timebase_HAL_RTC_WKUP enabled")
endif()


# condition: STMicroelectronics.stm32h7pxx_hal_drivers.2.0.0-alpha.2.0:Timebase HAL TIM
# description: HAL timebase based on TIM
if((CMSIS_Dname MATCHES "STM32H7P.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13"))
  set(STMicroelectronics.stm32h7pxx_hal_drivers.2.0.0-alpha.2.0:Timebase_HAL_TIM true)
  message(DEBUG "CMSIS condition STMicroelectronics.stm32h7pxx_hal_drivers.2.0.0-alpha.2.0:Timebase_HAL_TIM enabled")
endif()


# condition: STMicroelectronics.stm32h7pxx_hal_drivers.2.0.0-alpha.2.0:Timebase Init
# description: 
set(STMicroelectronics.stm32h7pxx_hal_drivers.2.0.0-alpha.2.0:Timebase_Init true)
message(DEBUG "CMSIS condition STMicroelectronics.stm32h7pxx_hal_drivers.2.0.0-alpha.2.0:Timebase_Init enabled")


# condition: STMicroelectronics.stm32h7pxx_hal_drivers.2.0.0-alpha.2.0:Timebase NONE
# description: HAL timebase NONE
if((CMSIS_Dname MATCHES "STM32H7P.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13"))
  set(STMicroelectronics.stm32h7pxx_hal_drivers.2.0.0-alpha.2.0:Timebase_NONE true)
  message(DEBUG "CMSIS condition STMicroelectronics.stm32h7pxx_hal_drivers.2.0.0-alpha.2.0:Timebase_NONE enabled")
endif()


# condition: STMicroelectronics.stm32h7pxx_hal_drivers.2.0.0-alpha.2.0:Timebase template
# description: 
set(STMicroelectronics.stm32h7pxx_hal_drivers.2.0.0-alpha.2.0:Timebase_template true)
message(DEBUG "CMSIS condition STMicroelectronics.stm32h7pxx_hal_drivers.2.0.0-alpha.2.0:Timebase_template enabled")


# condition: STMicroelectronics.stm32h7pxx_hal_drivers.2.0.0-alpha.2.0:Use external env
# description: STMicroelectronics HAL condition to check if stm32_external_env.h must be generated
set(STMicroelectronics.stm32h7pxx_hal_drivers.2.0.0-alpha.2.0:Use_external_env true)
message(DEBUG "CMSIS condition STMicroelectronics.stm32h7pxx_hal_drivers.2.0.0-alpha.2.0:Use_external_env enabled")


# condition: STMicroelectronics.stm32h7pxx_hal_drivers.2.0.0-alpha.2.0:Use mutex
# description: STMicroelectronics HAL condition to check if USE_HAL_MUTEX is enabled
if(((CMSIS_Dname MATCHES "STM32H7P.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13") AND (CMSIS_Dname MATCHES "STM32H7P.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13")))
  set(STMicroelectronics.stm32h7pxx_hal_drivers.2.0.0-alpha.2.0:Use_mutex true)
  message(DEBUG "CMSIS condition STMicroelectronics.stm32h7pxx_hal_drivers.2.0.0-alpha.2.0:Use_mutex enabled")
endif()

# Files and components in this package
if(CMSIS_USE_Device_STM32_HAL_timebases_SYSTICK_0_1_0)  # HAL timebases based on Systick
  message(DEBUG "Using component Device_STM32_HAL_timebases_SYSTICK_0_1_0")
  if(STMicroelectronics.stm32h7pxx_hal_drivers.2.0.0-alpha.2.0:Timebase_NONE)
    target_compile_definitions(STMicroelectronics_stm32h7pxx_hal_drivers_2_0_0_alpha_2_0 INTERFACE -DCMSIS_USE_Device_STM32_HAL_timebases_SYSTICK_0_1_0=1)
    target_include_directories(STMicroelectronics_stm32h7pxx_hal_drivers_2_0_0_alpha_2_0 INTERFACE timebases/)
  endif()
endif()

if(CMSIS_USE_Device_STM32_HAL_timebases_RTC_ALARM_0_1_0)  # HAL timebases based on RTC alarm
  message(DEBUG "Using component Device_STM32_HAL_timebases_RTC_ALARM_0_1_0")
  if(STMicroelectronics.stm32h7pxx_hal_drivers.2.0.0-alpha.2.0:Timebase_HAL_RTC_WKUP)
    target_compile_definitions(STMicroelectronics_stm32h7pxx_hal_drivers_2_0_0_alpha_2_0 INTERFACE -DCMSIS_USE_Device_STM32_HAL_timebases_RTC_ALARM_0_1_0=1)
    target_include_directories(STMicroelectronics_stm32h7pxx_hal_drivers_2_0_0_alpha_2_0 INTERFACE timebases/)
    target_sources(STMicroelectronics_stm32h7pxx_hal_drivers_2_0_0_alpha_2_0 INTERFACE timebases/stm32_hal_timebase_rtc_alarm.c)
  endif()
endif()

if(CMSIS_USE_Device_STM32_HAL_timebases_RTC_WAKEUP_0_1_0)  # HAL timebases based on RTC wakeup
  message(DEBUG "Using component Device_STM32_HAL_timebases_RTC_WAKEUP_0_1_0")
  if(STMicroelectronics.stm32h7pxx_hal_drivers.2.0.0-alpha.2.0:Timebase_HAL_RTC_ALARM)
    target_compile_definitions(STMicroelectronics_stm32h7pxx_hal_drivers_2_0_0_alpha_2_0 INTERFACE -DCMSIS_USE_Device_STM32_HAL_timebases_RTC_WAKEUP_0_1_0=1)
    target_include_directories(STMicroelectronics_stm32h7pxx_hal_drivers_2_0_0_alpha_2_0 INTERFACE timebases/)
    target_sources(STMicroelectronics_stm32h7pxx_hal_drivers_2_0_0_alpha_2_0 INTERFACE timebases/stm32_hal_timebase_rtc_wakeup.c)
  endif()
endif()

if(CMSIS_USE_Device_STM32_HAL_TIM_template_0_1_1)  # HAL templates
  message(DEBUG "Using component Device_STM32_HAL_TIM_template_0_1_1")
  if(STMicroelectronics.stm32h7pxx_hal_drivers.2.0.0-alpha.2.0:HAL_Common)
    target_compile_definitions(STMicroelectronics_stm32h7pxx_hal_drivers_2_0_0_alpha_2_0 INTERFACE -DCMSIS_USE_Device_STM32_HAL_TIM_template_0_1_1=1)
    target_include_directories(STMicroelectronics_stm32h7pxx_hal_drivers_2_0_0_alpha_2_0 INTERFACE ./)
  endif()
endif()

if(CMSIS_USE_Device_STM32_HAL_timebases_TIM_0_1_0)  # HAL timebases based on TIM
  message(DEBUG "Using component Device_STM32_HAL_timebases_TIM_0_1_0")
  if(STMicroelectronics.stm32h7pxx_hal_drivers.2.0.0-alpha.2.0:Timebase_HAL_TIM)
    target_compile_definitions(STMicroelectronics_stm32h7pxx_hal_drivers_2_0_0_alpha_2_0 INTERFACE -DCMSIS_USE_Device_STM32_HAL_timebases_TIM_0_1_0=1)
    target_include_directories(STMicroelectronics_stm32h7pxx_hal_drivers_2_0_0_alpha_2_0 INTERFACE timebases/)
    target_sources(STMicroelectronics_stm32h7pxx_hal_drivers_2_0_0_alpha_2_0 INTERFACE timebases/stm32_hal_timebase_tim.c)
  endif()
endif()

if(CMSIS_USE_Device_STM32_HAL_Core_0_4_1)  # Common HAL driver
  message(DEBUG "Using component Device_STM32_HAL_Core_0_4_1")
  if(STMicroelectronics.stm32h7pxx_hal_drivers.2.0.0-alpha.2.0:HAL_Common)
    target_compile_definitions(STMicroelectronics_stm32h7pxx_hal_drivers_2_0_0_alpha_2_0 INTERFACE -DCMSIS_USE_Device_STM32_HAL_Core_0_4_1=1)
    target_include_directories(STMicroelectronics_stm32h7pxx_hal_drivers_2_0_0_alpha_2_0 INTERFACE hal)
    target_include_directories(STMicroelectronics_stm32h7pxx_hal_drivers_2_0_0_alpha_2_0 INTERFACE hal/)
    target_include_directories(STMicroelectronics_stm32h7pxx_hal_drivers_2_0_0_alpha_2_0 INTERFACE ll/)
    target_sources(STMicroelectronics_stm32h7pxx_hal_drivers_2_0_0_alpha_2_0 INTERFACE hal/stm32h7pxx_hal.c)
  endif()
endif()

if(CMSIS_USE_Device_STM32_HAL_UTILS_I2C_0_1_0)  # Utilities I2C
  message(DEBUG "Using component Device_STM32_HAL_UTILS_I2C_0_1_0")
  if(STMicroelectronics.stm32h7pxx_hal_drivers.2.0.0-alpha.2.0:HAL_Common)
    target_compile_definitions(STMicroelectronics_stm32h7pxx_hal_drivers_2_0_0_alpha_2_0 INTERFACE -DCMSIS_USE_Device_STM32_HAL_UTILS_I2C_0_1_0=1)
    target_include_directories(STMicroelectronics_stm32h7pxx_hal_drivers_2_0_0_alpha_2_0 INTERFACE utils/i2c_timing)
    target_sources(STMicroelectronics_stm32h7pxx_hal_drivers_2_0_0_alpha_2_0 INTERFACE utils/i2c_timing/stm32_utils_i2c.c)
  endif()
endif()

if(CMSIS_USE_Device_STM32_HAL_UTILS_I3C_0_1_0)  # Utilities I3C
  message(DEBUG "Using component Device_STM32_HAL_UTILS_I3C_0_1_0")
  if(STMicroelectronics.stm32h7pxx_hal_drivers.2.0.0-alpha.2.0:HAL_Common)
    target_compile_definitions(STMicroelectronics_stm32h7pxx_hal_drivers_2_0_0_alpha_2_0 INTERFACE -DCMSIS_USE_Device_STM32_HAL_UTILS_I3C_0_1_0=1)
    target_include_directories(STMicroelectronics_stm32h7pxx_hal_drivers_2_0_0_alpha_2_0 INTERFACE utils/i3c_timing)
    target_sources(STMicroelectronics_stm32h7pxx_hal_drivers_2_0_0_alpha_2_0 INTERFACE utils/i3c_timing/stm32_utils_i3c.c)
  endif()
endif()

if(CMSIS_USE_Device_STM32_HAL_UTILS_FDCAN_0_1_0)  # Utilities FDCAN
  message(DEBUG "Using component Device_STM32_HAL_UTILS_FDCAN_0_1_0")
  if(STMicroelectronics.stm32h7pxx_hal_drivers.2.0.0-alpha.2.0:HAL_Common)
    target_compile_definitions(STMicroelectronics_stm32h7pxx_hal_drivers_2_0_0_alpha_2_0 INTERFACE -DCMSIS_USE_Device_STM32_HAL_UTILS_FDCAN_0_1_0=1)
    target_include_directories(STMicroelectronics_stm32h7pxx_hal_drivers_2_0_0_alpha_2_0 INTERFACE utils/fdcan_timing)
    target_sources(STMicroelectronics_stm32h7pxx_hal_drivers_2_0_0_alpha_2_0 INTERFACE utils/fdcan_timing/stm32_utils_fdcan.c)
  endif()
endif()

if(CMSIS_USE_Device_STM32_HAL_ASSERT_0_1_1)  # HAL ASSERT template
  message(DEBUG "Using component Device_STM32_HAL_ASSERT_0_1_1")
  if(STMicroelectronics.stm32h7pxx_hal_drivers.2.0.0-alpha.2.0:HAL_Common)
    target_compile_definitions(STMicroelectronics_stm32h7pxx_hal_drivers_2_0_0_alpha_2_0 INTERFACE -DCMSIS_USE_Device_STM32_HAL_ASSERT_0_1_1=1)
    target_include_directories(STMicroelectronics_stm32h7pxx_hal_drivers_2_0_0_alpha_2_0 INTERFACE templates/common)
  endif()
endif()

if(CMSIS_USE_Device_STM32_HAL_template_0_1_1)  # HAL templates
  message(DEBUG "Using component Device_STM32_HAL_template_0_1_1")
  if(STMicroelectronics.stm32h7pxx_hal_drivers.2.0.0-alpha.2.0:HAL_Common)
    target_compile_definitions(STMicroelectronics_stm32h7pxx_hal_drivers_2_0_0_alpha_2_0 INTERFACE -DCMSIS_USE_Device_STM32_HAL_template_0_1_1=1)
    target_include_directories(STMicroelectronics_stm32h7pxx_hal_drivers_2_0_0_alpha_2_0 INTERFACE templates/common)
    target_include_directories(STMicroelectronics_stm32h7pxx_hal_drivers_2_0_0_alpha_2_0 INTERFACE templates/common/)
  endif()
endif()

if(CMSIS_USE_Device_STM32_HAL_ADC_0_2_0)  # Analog-to-digital converter (ADC) HAL driver
  message(DEBUG "Using component Device_STM32_HAL_ADC_0_2_0")
  if(STMicroelectronics.stm32h7pxx_hal_drivers.2.0.0-alpha.2.0:HAL_ADC)
    target_compile_definitions(STMicroelectronics_stm32h7pxx_hal_drivers_2_0_0_alpha_2_0 INTERFACE -DCMSIS_USE_Device_STM32_HAL_ADC_0_2_0=1)
    target_include_directories(STMicroelectronics_stm32h7pxx_hal_drivers_2_0_0_alpha_2_0 INTERFACE hal)
    target_sources(STMicroelectronics_stm32h7pxx_hal_drivers_2_0_0_alpha_2_0 INTERFACE hal/stm32h7pxx_hal_adc.c)
  endif()
endif()

if(CMSIS_USE_Device_STM32_HAL_ADF_0_2_0)  # ADF HAL driver
  message(DEBUG "Using component Device_STM32_HAL_ADF_0_2_0")
  if(STMicroelectronics.stm32h7pxx_hal_drivers.2.0.0-alpha.2.0:HAL_CORE_DMA)
    target_compile_definitions(STMicroelectronics_stm32h7pxx_hal_drivers_2_0_0_alpha_2_0 INTERFACE -DCMSIS_USE_Device_STM32_HAL_ADF_0_2_0=1)
    target_include_directories(STMicroelectronics_stm32h7pxx_hal_drivers_2_0_0_alpha_2_0 INTERFACE hal)
    target_sources(STMicroelectronics_stm32h7pxx_hal_drivers_2_0_0_alpha_2_0 INTERFACE hal/stm32h7pxx_hal_adf.c)
  endif()
endif()

if(CMSIS_USE_Device_STM32_HAL_COMP_0_2_0)  # Comparator (COMP) HAL driver
  message(DEBUG "Using component Device_STM32_HAL_COMP_0_2_0")
  if(STMicroelectronics.stm32h7pxx_hal_drivers.2.0.0-alpha.2.0:HAL_COMP)
    target_compile_definitions(STMicroelectronics_stm32h7pxx_hal_drivers_2_0_0_alpha_2_0 INTERFACE -DCMSIS_USE_Device_STM32_HAL_COMP_0_2_0=1)
    target_include_directories(STMicroelectronics_stm32h7pxx_hal_drivers_2_0_0_alpha_2_0 INTERFACE hal)
    target_sources(STMicroelectronics_stm32h7pxx_hal_drivers_2_0_0_alpha_2_0 INTERFACE hal/stm32h7pxx_hal_comp.c)
  endif()
endif()

if(CMSIS_USE_Device_STM32_HAL_CORDIC_0_1_0)  # CORDIC HAL driver
  message(DEBUG "Using component Device_STM32_HAL_CORDIC_0_1_0")
  if(STMicroelectronics.stm32h7pxx_hal_drivers.2.0.0-alpha.2.0:HAL_CORDIC)
    target_compile_definitions(STMicroelectronics_stm32h7pxx_hal_drivers_2_0_0_alpha_2_0 INTERFACE -DCMSIS_USE_Device_STM32_HAL_CORDIC_0_1_0=1)
    target_include_directories(STMicroelectronics_stm32h7pxx_hal_drivers_2_0_0_alpha_2_0 INTERFACE hal)
    target_sources(STMicroelectronics_stm32h7pxx_hal_drivers_2_0_0_alpha_2_0 INTERFACE hal/stm32h7pxx_hal_cordic.c)
  endif()
endif()

if(CMSIS_USE_Device_STM32_HAL_CORTEX_0_2_0)  # Cortex (CORTEX) HAL driver
  message(DEBUG "Using component Device_STM32_HAL_CORTEX_0_2_0")
  if(STMicroelectronics.stm32h7pxx_hal_drivers.2.0.0-alpha.2.0:HAL_CORTEX)
    target_compile_definitions(STMicroelectronics_stm32h7pxx_hal_drivers_2_0_0_alpha_2_0 INTERFACE -DCMSIS_USE_Device_STM32_HAL_CORTEX_0_2_0=1)
    target_include_directories(STMicroelectronics_stm32h7pxx_hal_drivers_2_0_0_alpha_2_0 INTERFACE hal)
    target_sources(STMicroelectronics_stm32h7pxx_hal_drivers_2_0_0_alpha_2_0 INTERFACE hal/stm32h7pxx_hal_cortex.c)
  endif()
endif()

if(CMSIS_USE_Device_STM32_HAL_CRC_0_3_0)  # CRC calculation unit (CRC) HAL driver
  message(DEBUG "Using component Device_STM32_HAL_CRC_0_3_0")
  if(STMicroelectronics.stm32h7pxx_hal_drivers.2.0.0-alpha.2.0:HAL_CRC)
    target_compile_definitions(STMicroelectronics_stm32h7pxx_hal_drivers_2_0_0_alpha_2_0 INTERFACE -DCMSIS_USE_Device_STM32_HAL_CRC_0_3_0=1)
    target_include_directories(STMicroelectronics_stm32h7pxx_hal_drivers_2_0_0_alpha_2_0 INTERFACE hal)
    target_sources(STMicroelectronics_stm32h7pxx_hal_drivers_2_0_0_alpha_2_0 INTERFACE hal/stm32h7pxx_hal_crc.c)
  endif()
endif()

if(CMSIS_USE_Device_STM32_HAL_CRS_0_2_0)  # Clock Recovery CORE (CRS) HAL driver
  message(DEBUG "Using component Device_STM32_HAL_CRS_0_2_0")
  if(STMicroelectronics.stm32h7pxx_hal_drivers.2.0.0-alpha.2.0:HAL_CRS)
    target_compile_definitions(STMicroelectronics_stm32h7pxx_hal_drivers_2_0_0_alpha_2_0 INTERFACE -DCMSIS_USE_Device_STM32_HAL_CRS_0_2_0=1)
    target_include_directories(STMicroelectronics_stm32h7pxx_hal_drivers_2_0_0_alpha_2_0 INTERFACE hal)
    target_sources(STMicroelectronics_stm32h7pxx_hal_drivers_2_0_0_alpha_2_0 INTERFACE hal/stm32h7pxx_hal_crs.c)
  endif()
endif()

if(CMSIS_USE_Device_STM32_HAL_DAC_0_4_0)  # Digital-to-analog converter (DAC) HAL driver
  message(DEBUG "Using component Device_STM32_HAL_DAC_0_4_0")
  if(STMicroelectronics.stm32h7pxx_hal_drivers.2.0.0-alpha.2.0:HAL_DAC)
    target_compile_definitions(STMicroelectronics_stm32h7pxx_hal_drivers_2_0_0_alpha_2_0 INTERFACE -DCMSIS_USE_Device_STM32_HAL_DAC_0_4_0=1)
    target_include_directories(STMicroelectronics_stm32h7pxx_hal_drivers_2_0_0_alpha_2_0 INTERFACE hal)
    target_sources(STMicroelectronics_stm32h7pxx_hal_drivers_2_0_0_alpha_2_0 INTERFACE hal/stm32h7pxx_hal_dac.c)
  endif()
endif()

if(CMSIS_USE_Device_STM32_HAL_DBGMCU_0_2_0)  # Microcontroller debug unit (DBGMCU) HAL driver
  message(DEBUG "Using component Device_STM32_HAL_DBGMCU_0_2_0")
  if(STMicroelectronics.stm32h7pxx_hal_drivers.2.0.0-alpha.2.0:HAL_DBGMCU)
    target_compile_definitions(STMicroelectronics_stm32h7pxx_hal_drivers_2_0_0_alpha_2_0 INTERFACE -DCMSIS_USE_Device_STM32_HAL_DBGMCU_0_2_0=1)
    target_include_directories(STMicroelectronics_stm32h7pxx_hal_drivers_2_0_0_alpha_2_0 INTERFACE hal)
    target_sources(STMicroelectronics_stm32h7pxx_hal_drivers_2_0_0_alpha_2_0 INTERFACE hal/stm32h7pxx_hal_dbgmcu.c)
  endif()
endif()

if(CMSIS_USE_Device_STM32_HAL_DRIVERS_CORE_DLYB_0_1_0)  # Delay Block (DLYB) HAL driver
  message(DEBUG "Using component Device_STM32_HAL_DRIVERS_CORE_DLYB_0_1_0")
  if(STMicroelectronics.stm32h7pxx_hal_drivers.2.0.0-alpha.2.0:HAL_CORE)
    target_compile_definitions(STMicroelectronics_stm32h7pxx_hal_drivers_2_0_0_alpha_2_0 INTERFACE -DCMSIS_USE_Device_STM32_HAL_DRIVERS_CORE_DLYB_0_1_0=1)
    target_include_directories(STMicroelectronics_stm32h7pxx_hal_drivers_2_0_0_alpha_2_0 INTERFACE hal)
    target_sources(STMicroelectronics_stm32h7pxx_hal_drivers_2_0_0_alpha_2_0 INTERFACE hal/stm32h7pxx_dlyb_core.c)
  endif()
endif()

if(CMSIS_USE_Device_STM32_HAL_DMA_0_5_0)  # DMA controller (DMA) HAL driver
  message(DEBUG "Using component Device_STM32_HAL_DMA_0_5_0")
  if(STMicroelectronics.stm32h7pxx_hal_drivers.2.0.0-alpha.2.0:HAL_DMA)
    target_compile_definitions(STMicroelectronics_stm32h7pxx_hal_drivers_2_0_0_alpha_2_0 INTERFACE -DCMSIS_USE_Device_STM32_HAL_DMA_0_5_0=1)
    target_include_directories(STMicroelectronics_stm32h7pxx_hal_drivers_2_0_0_alpha_2_0 INTERFACE hal)
    target_sources(STMicroelectronics_stm32h7pxx_hal_drivers_2_0_0_alpha_2_0 INTERFACE hal/stm32h7pxx_hal_dma.c)
  endif()
endif()

if(CMSIS_USE_Device_STM32_HAL_DTS_0_2_0)  # DTS HAL driver
  message(DEBUG "Using component Device_STM32_HAL_DTS_0_2_0")
  if(STMicroelectronics.stm32h7pxx_hal_drivers.2.0.0-alpha.2.0:HAL_CORE)
    target_compile_definitions(STMicroelectronics_stm32h7pxx_hal_drivers_2_0_0_alpha_2_0 INTERFACE -DCMSIS_USE_Device_STM32_HAL_DTS_0_2_0=1)
    target_include_directories(STMicroelectronics_stm32h7pxx_hal_drivers_2_0_0_alpha_2_0 INTERFACE hal)
    target_sources(STMicroelectronics_stm32h7pxx_hal_drivers_2_0_0_alpha_2_0 INTERFACE hal/stm32h7pxx_hal_dts.c)
  endif()
endif()

if(CMSIS_USE_Device_STM32_HAL_EXTI_0_3_0)  # External interrupts and events (EXTI) controller
  message(DEBUG "Using component Device_STM32_HAL_EXTI_0_3_0")
  if(STMicroelectronics.stm32h7pxx_hal_drivers.2.0.0-alpha.2.0:HAL_EXTI)
    target_compile_definitions(STMicroelectronics_stm32h7pxx_hal_drivers_2_0_0_alpha_2_0 INTERFACE -DCMSIS_USE_Device_STM32_HAL_EXTI_0_3_0=1)
    target_include_directories(STMicroelectronics_stm32h7pxx_hal_drivers_2_0_0_alpha_2_0 INTERFACE hal)
    target_sources(STMicroelectronics_stm32h7pxx_hal_drivers_2_0_0_alpha_2_0 INTERFACE hal/stm32h7pxx_hal_exti.c)
  endif()
endif()

if(CMSIS_USE_Device_STM32_HAL_FDCAN_0_2_0)  # FDCAN HAL Driver
  message(DEBUG "Using component Device_STM32_HAL_FDCAN_0_2_0")
  if(STMicroelectronics.stm32h7pxx_hal_drivers.2.0.0-alpha.2.0:HAL_CORE)
    target_compile_definitions(STMicroelectronics_stm32h7pxx_hal_drivers_2_0_0_alpha_2_0 INTERFACE -DCMSIS_USE_Device_STM32_HAL_FDCAN_0_2_0=1)
    target_include_directories(STMicroelectronics_stm32h7pxx_hal_drivers_2_0_0_alpha_2_0 INTERFACE hal)
    target_sources(STMicroelectronics_stm32h7pxx_hal_drivers_2_0_0_alpha_2_0 INTERFACE hal/stm32h7pxx_hal_fdcan.c)
  endif()
endif()

if(CMSIS_USE_Device_STM32_HAL_FLASH_0_2_0)  # Embedded FLASH memory HAL driver
  message(DEBUG "Using component Device_STM32_HAL_FLASH_0_2_0")
  if(STMicroelectronics.stm32h7pxx_hal_drivers.2.0.0-alpha.2.0:HAL_FLASH)
    target_compile_definitions(STMicroelectronics_stm32h7pxx_hal_drivers_2_0_0_alpha_2_0 INTERFACE -DCMSIS_USE_Device_STM32_HAL_FLASH_0_2_0=1)
    target_include_directories(STMicroelectronics_stm32h7pxx_hal_drivers_2_0_0_alpha_2_0 INTERFACE hal)
    target_sources(STMicroelectronics_stm32h7pxx_hal_drivers_2_0_0_alpha_2_0 INTERFACE hal/stm32h7pxx_hal_flash.c)
  endif()
endif()

if(CMSIS_USE_Device_STM32_HAL_FLASH_ITF_0_1_0)  # Embedded FLASH Option Bytes HAL driver
  message(DEBUG "Using component Device_STM32_HAL_FLASH_ITF_0_1_0")
  if(STMicroelectronics.stm32h7pxx_hal_drivers.2.0.0-alpha.2.0:HAL_FLASH_ITF)
    target_compile_definitions(STMicroelectronics_stm32h7pxx_hal_drivers_2_0_0_alpha_2_0 INTERFACE -DCMSIS_USE_Device_STM32_HAL_FLASH_ITF_0_1_0=1)
    target_include_directories(STMicroelectronics_stm32h7pxx_hal_drivers_2_0_0_alpha_2_0 INTERFACE hal)
    target_sources(STMicroelectronics_stm32h7pxx_hal_drivers_2_0_0_alpha_2_0 INTERFACE hal/stm32h7pxx_hal_flash_itf.c)
  endif()
endif()

if(CMSIS_USE_Device_STM32_HAL_FMAC_0_2_0)  # FMAC HAL Driver
  message(DEBUG "Using component Device_STM32_HAL_FMAC_0_2_0")
  if(STMicroelectronics.stm32h7pxx_hal_drivers.2.0.0-alpha.2.0:HAL_FMAC)
    target_compile_definitions(STMicroelectronics_stm32h7pxx_hal_drivers_2_0_0_alpha_2_0 INTERFACE -DCMSIS_USE_Device_STM32_HAL_FMAC_0_2_0=1)
    target_include_directories(STMicroelectronics_stm32h7pxx_hal_drivers_2_0_0_alpha_2_0 INTERFACE hal)
    target_sources(STMicroelectronics_stm32h7pxx_hal_drivers_2_0_0_alpha_2_0 INTERFACE hal/stm32h7pxx_hal_fmac.c)
  endif()
endif()

if(CMSIS_USE_Device_STM32_HAL_DRIVERS_CORE_FMC_0_1_0)  # FMC low layer (FMC) HAL driver
  message(DEBUG "Using component Device_STM32_HAL_DRIVERS_CORE_FMC_0_1_0")
  if(STMicroelectronics.stm32h7pxx_hal_drivers.2.0.0-alpha.2.0:HAL_CORE)
    target_compile_definitions(STMicroelectronics_stm32h7pxx_hal_drivers_2_0_0_alpha_2_0 INTERFACE -DCMSIS_USE_Device_STM32_HAL_DRIVERS_CORE_FMC_0_1_0=1)
    target_include_directories(STMicroelectronics_stm32h7pxx_hal_drivers_2_0_0_alpha_2_0 INTERFACE hal)
    target_sources(STMicroelectronics_stm32h7pxx_hal_drivers_2_0_0_alpha_2_0 INTERFACE hal/stm32h7pxx_fmc_core.c)
  endif()
endif()

if(CMSIS_USE_Device_STM32_HAL_GPIO_0_2_2)  # General-purpose I/O (GPIO) HAL driver
  message(DEBUG "Using component Device_STM32_HAL_GPIO_0_2_2")
  if(STMicroelectronics.stm32h7pxx_hal_drivers.2.0.0-alpha.2.0:HAL_GPIO)
    target_compile_definitions(STMicroelectronics_stm32h7pxx_hal_drivers_2_0_0_alpha_2_0 INTERFACE -DCMSIS_USE_Device_STM32_HAL_GPIO_0_2_2=1)
    target_include_directories(STMicroelectronics_stm32h7pxx_hal_drivers_2_0_0_alpha_2_0 INTERFACE hal)
    target_sources(STMicroelectronics_stm32h7pxx_hal_drivers_2_0_0_alpha_2_0 INTERFACE hal/stm32h7pxx_hal_gpio.c)
  endif()
endif()

if(CMSIS_USE_Device_STM32_HAL_HASH_0_2_0)  # HASH HAL driver
  message(DEBUG "Using component Device_STM32_HAL_HASH_0_2_0")
  if(STMicroelectronics.stm32h7pxx_hal_drivers.2.0.0-alpha.2.0:HAL_CORE_DMA)
    target_compile_definitions(STMicroelectronics_stm32h7pxx_hal_drivers_2_0_0_alpha_2_0 INTERFACE -DCMSIS_USE_Device_STM32_HAL_HASH_0_2_0=1)
    target_include_directories(STMicroelectronics_stm32h7pxx_hal_drivers_2_0_0_alpha_2_0 INTERFACE hal)
    target_sources(STMicroelectronics_stm32h7pxx_hal_drivers_2_0_0_alpha_2_0 INTERFACE hal/stm32h7pxx_hal_hash.c)
  endif()
endif()

if(CMSIS_USE_Device_STM32_HAL_HCD_0_3_0)  # HCD HAL driver
  message(DEBUG "Using component Device_STM32_HAL_HCD_0_3_0")
  if(STMicroelectronics.stm32h7pxx_hal_drivers.2.0.0-alpha.2.0:HAL_CORE_USB)
    target_compile_definitions(STMicroelectronics_stm32h7pxx_hal_drivers_2_0_0_alpha_2_0 INTERFACE -DCMSIS_USE_Device_STM32_HAL_HCD_0_3_0=1)
    target_include_directories(STMicroelectronics_stm32h7pxx_hal_drivers_2_0_0_alpha_2_0 INTERFACE hal)
    target_sources(STMicroelectronics_stm32h7pxx_hal_drivers_2_0_0_alpha_2_0 INTERFACE hal/stm32h7pxx_hal_hcd.c)
  endif()
endif()

if(CMSIS_USE_Device_STM32_HAL_HRTIM_0_1_0)  # High Resolution Timer (HRTIM) HAL driver
  message(DEBUG "Using component Device_STM32_HAL_HRTIM_0_1_0")
  if(STMicroelectronics.stm32h7pxx_hal_drivers.2.0.0-alpha.2.0:HAL_HRTIM)
    target_compile_definitions(STMicroelectronics_stm32h7pxx_hal_drivers_2_0_0_alpha_2_0 INTERFACE -DCMSIS_USE_Device_STM32_HAL_HRTIM_0_1_0=1)
    target_include_directories(STMicroelectronics_stm32h7pxx_hal_drivers_2_0_0_alpha_2_0 INTERFACE hal)
    target_sources(STMicroelectronics_stm32h7pxx_hal_drivers_2_0_0_alpha_2_0 INTERFACE hal/stm32h7pxx_hal_hrtim.c)
  endif()
endif()

if(CMSIS_USE_Device_STM32_HAL_HSP_0_0_1)  # Hardware Signal Processor (HSP) HAL driver
  message(DEBUG "Using component Device_STM32_HAL_HSP_0_0_1")
  if(STMicroelectronics.stm32h7pxx_hal_drivers.2.0.0-alpha.2.0:HAL_HSP)
    target_compile_definitions(STMicroelectronics_stm32h7pxx_hal_drivers_2_0_0_alpha_2_0 INTERFACE -DCMSIS_USE_Device_STM32_HAL_HSP_0_0_1=1)
    target_include_directories(STMicroelectronics_stm32h7pxx_hal_drivers_2_0_0_alpha_2_0 INTERFACE hal)
    target_sources(STMicroelectronics_stm32h7pxx_hal_drivers_2_0_0_alpha_2_0 INTERFACE hal/stm32h7pxx_hal_hsp.c)
  endif()
endif()

if(CMSIS_USE_Device_STM32_HAL_I2C_0_3_0)  # Inter-integrated circuit (I2C) interface HAL driver
  message(DEBUG "Using component Device_STM32_HAL_I2C_0_3_0")
  if(STMicroelectronics.stm32h7pxx_hal_drivers.2.0.0-alpha.2.0:HAL_I2C)
    target_compile_definitions(STMicroelectronics_stm32h7pxx_hal_drivers_2_0_0_alpha_2_0 INTERFACE -DCMSIS_USE_Device_STM32_HAL_I2C_0_3_0=1)
    target_include_directories(STMicroelectronics_stm32h7pxx_hal_drivers_2_0_0_alpha_2_0 INTERFACE hal)
    target_sources(STMicroelectronics_stm32h7pxx_hal_drivers_2_0_0_alpha_2_0 INTERFACE hal/stm32h7pxx_hal_i2c.c)
  endif()
endif()

if(CMSIS_USE_Device_STM32_HAL_I3C_0_1_0)  # Improved inter-integrated circuit (I3C) interface HAL driver
  message(DEBUG "Using component Device_STM32_HAL_I3C_0_1_0")
  if(STMicroelectronics.stm32h7pxx_hal_drivers.2.0.0-alpha.2.0:HAL_I3C)
    target_compile_definitions(STMicroelectronics_stm32h7pxx_hal_drivers_2_0_0_alpha_2_0 INTERFACE -DCMSIS_USE_Device_STM32_HAL_I3C_0_1_0=1)
    target_include_directories(STMicroelectronics_stm32h7pxx_hal_drivers_2_0_0_alpha_2_0 INTERFACE hal)
    target_sources(STMicroelectronics_stm32h7pxx_hal_drivers_2_0_0_alpha_2_0 INTERFACE hal/stm32h7pxx_hal_i3c.c)
  endif()
endif()

if(CMSIS_USE_Device_STM32_HAL_I2S_0_3_0)  # Integrated Inter-IC Sound Bus (I2S) interface HAL driver
  message(DEBUG "Using component Device_STM32_HAL_I2S_0_3_0")
  if(STMicroelectronics.stm32h7pxx_hal_drivers.2.0.0-alpha.2.0:HAL_I2S)
    target_compile_definitions(STMicroelectronics_stm32h7pxx_hal_drivers_2_0_0_alpha_2_0 INTERFACE -DCMSIS_USE_Device_STM32_HAL_I2S_0_3_0=1)
    target_include_directories(STMicroelectronics_stm32h7pxx_hal_drivers_2_0_0_alpha_2_0 INTERFACE hal)
    target_sources(STMicroelectronics_stm32h7pxx_hal_drivers_2_0_0_alpha_2_0 INTERFACE hal/stm32h7pxx_hal_i2s.c)
  endif()
endif()

if(CMSIS_USE_Device_STM32_HAL_IWDG_0_2_0)  # Independent watchdog (IWDG) HAL driver
  message(DEBUG "Using component Device_STM32_HAL_IWDG_0_2_0")
  if(STMicroelectronics.stm32h7pxx_hal_drivers.2.0.0-alpha.2.0:HAL_IWDG)
    target_compile_definitions(STMicroelectronics_stm32h7pxx_hal_drivers_2_0_0_alpha_2_0 INTERFACE -DCMSIS_USE_Device_STM32_HAL_IWDG_0_2_0=1)
    target_include_directories(STMicroelectronics_stm32h7pxx_hal_drivers_2_0_0_alpha_2_0 INTERFACE hal)
    target_sources(STMicroelectronics_stm32h7pxx_hal_drivers_2_0_0_alpha_2_0 INTERFACE hal/stm32h7pxx_hal_iwdg.c)
  endif()
endif()

if(CMSIS_USE_Device_STM32_HAL_LPTIM_0_2_0)  # Low-power timer (LPTIM) HAL driver
  message(DEBUG "Using component Device_STM32_HAL_LPTIM_0_2_0")
  if(STMicroelectronics.stm32h7pxx_hal_drivers.2.0.0-alpha.2.0:HAL_LPTIM)
    target_compile_definitions(STMicroelectronics_stm32h7pxx_hal_drivers_2_0_0_alpha_2_0 INTERFACE -DCMSIS_USE_Device_STM32_HAL_LPTIM_0_2_0=1)
    target_include_directories(STMicroelectronics_stm32h7pxx_hal_drivers_2_0_0_alpha_2_0 INTERFACE hal)
    target_sources(STMicroelectronics_stm32h7pxx_hal_drivers_2_0_0_alpha_2_0 INTERFACE hal/stm32h7pxx_hal_lptim.c)
  endif()
endif()

if(CMSIS_USE_Device_STM32_HAL_MMC_0_1_1)  # MMC HAL driver
  message(DEBUG "Using component Device_STM32_HAL_MMC_0_1_1")
  if(STMicroelectronics.stm32h7pxx_hal_drivers.2.0.0-alpha.2.0:HAL_CORE_SDMMC)
    target_compile_definitions(STMicroelectronics_stm32h7pxx_hal_drivers_2_0_0_alpha_2_0 INTERFACE -DCMSIS_USE_Device_STM32_HAL_MMC_0_1_1=1)
    target_include_directories(STMicroelectronics_stm32h7pxx_hal_drivers_2_0_0_alpha_2_0 INTERFACE hal)
    target_sources(STMicroelectronics_stm32h7pxx_hal_drivers_2_0_0_alpha_2_0 INTERFACE hal/stm32h7pxx_hal_mmc.c)
  endif()
endif()

if(CMSIS_USE_Device_STM32_HAL_PCD_0_3_0)  # USB Peripheral controller (PCD) HAL driver
  message(DEBUG "Using component Device_STM32_HAL_PCD_0_3_0")
  if(STMicroelectronics.stm32h7pxx_hal_drivers.2.0.0-alpha.2.0:HAL_CORE_USB)
    target_compile_definitions(STMicroelectronics_stm32h7pxx_hal_drivers_2_0_0_alpha_2_0 INTERFACE -DCMSIS_USE_Device_STM32_HAL_PCD_0_3_0=1)
    target_include_directories(STMicroelectronics_stm32h7pxx_hal_drivers_2_0_0_alpha_2_0 INTERFACE hal)
    target_sources(STMicroelectronics_stm32h7pxx_hal_drivers_2_0_0_alpha_2_0 INTERFACE hal/stm32h7pxx_hal_pcd.c)
  endif()
endif()

if(CMSIS_USE_Device_STM32_HAL_PWR_0_3_0)  # Power controller (PWR) HAL driver
  message(DEBUG "Using component Device_STM32_HAL_PWR_0_3_0")
  if(STMicroelectronics.stm32h7pxx_hal_drivers.2.0.0-alpha.2.0:HAL_PWR)
    target_compile_definitions(STMicroelectronics_stm32h7pxx_hal_drivers_2_0_0_alpha_2_0 INTERFACE -DCMSIS_USE_Device_STM32_HAL_PWR_0_3_0=1)
    target_include_directories(STMicroelectronics_stm32h7pxx_hal_drivers_2_0_0_alpha_2_0 INTERFACE hal)
    target_sources(STMicroelectronics_stm32h7pxx_hal_drivers_2_0_0_alpha_2_0 INTERFACE hal/stm32h7pxx_hal_pwr.c)
  endif()
endif()

if(CMSIS_USE_Device_STM32_HAL_Q_0_1_0)  # Queue (Q) HAL driver
  message(DEBUG "Using component Device_STM32_HAL_Q_0_1_0")
  if(STMicroelectronics.stm32h7pxx_hal_drivers.2.0.0-alpha.2.0:HAL_CORE)
    target_compile_definitions(STMicroelectronics_stm32h7pxx_hal_drivers_2_0_0_alpha_2_0 INTERFACE -DCMSIS_USE_Device_STM32_HAL_Q_0_1_0=1)
    target_include_directories(STMicroelectronics_stm32h7pxx_hal_drivers_2_0_0_alpha_2_0 INTERFACE hal)
    target_sources(STMicroelectronics_stm32h7pxx_hal_drivers_2_0_0_alpha_2_0 INTERFACE hal/stm32h7pxx_hal_q.c)
  endif()
endif()

if(CMSIS_USE_Device_STM32_HAL_RAMECC_0_1_0)  # RAMECC HAL driver
  message(DEBUG "Using component Device_STM32_HAL_RAMECC_0_1_0")
  if(STMicroelectronics.stm32h7pxx_hal_drivers.2.0.0-alpha.2.0:HAL_RAMECC)
    target_compile_definitions(STMicroelectronics_stm32h7pxx_hal_drivers_2_0_0_alpha_2_0 INTERFACE -DCMSIS_USE_Device_STM32_HAL_RAMECC_0_1_0=1)
    target_include_directories(STMicroelectronics_stm32h7pxx_hal_drivers_2_0_0_alpha_2_0 INTERFACE hal)
    target_sources(STMicroelectronics_stm32h7pxx_hal_drivers_2_0_0_alpha_2_0 INTERFACE hal/stm32h7pxx_hal_ramecc.c)
  endif()
endif()

if(CMSIS_USE_Device_STM32_HAL_RCC_0_3_0)  # Reset and clock control (RCC) HAL driver
  message(DEBUG "Using component Device_STM32_HAL_RCC_0_3_0")
  if(STMicroelectronics.stm32h7pxx_hal_drivers.2.0.0-alpha.2.0:HAL_RCC)
    target_compile_definitions(STMicroelectronics_stm32h7pxx_hal_drivers_2_0_0_alpha_2_0 INTERFACE -DCMSIS_USE_Device_STM32_HAL_RCC_0_3_0=1)
    target_include_directories(STMicroelectronics_stm32h7pxx_hal_drivers_2_0_0_alpha_2_0 INTERFACE hal)
    target_sources(STMicroelectronics_stm32h7pxx_hal_drivers_2_0_0_alpha_2_0 INTERFACE hal/stm32h7pxx_hal_rcc.c)
  endif()
endif()

if(CMSIS_USE_Device_STM32_HAL_RNG_0_2_0)  # Random number generator (RNG) HAL driver
  message(DEBUG "Using component Device_STM32_HAL_RNG_0_2_0")
  if(STMicroelectronics.stm32h7pxx_hal_drivers.2.0.0-alpha.2.0:HAL_RNG)
    target_compile_definitions(STMicroelectronics_stm32h7pxx_hal_drivers_2_0_0_alpha_2_0 INTERFACE -DCMSIS_USE_Device_STM32_HAL_RNG_0_2_0=1)
    target_include_directories(STMicroelectronics_stm32h7pxx_hal_drivers_2_0_0_alpha_2_0 INTERFACE hal)
    target_sources(STMicroelectronics_stm32h7pxx_hal_drivers_2_0_0_alpha_2_0 INTERFACE hal/stm32h7pxx_hal_rng.c)
  endif()
endif()

if(CMSIS_USE_Device_STM32_HAL_RTC_0_2_0)  # Real-time clock (RTC) HAL driver
  message(DEBUG "Using component Device_STM32_HAL_RTC_0_2_0")
  if(STMicroelectronics.stm32h7pxx_hal_drivers.2.0.0-alpha.2.0:HAL_RTC)
    target_compile_definitions(STMicroelectronics_stm32h7pxx_hal_drivers_2_0_0_alpha_2_0 INTERFACE -DCMSIS_USE_Device_STM32_HAL_RTC_0_2_0=1)
    target_include_directories(STMicroelectronics_stm32h7pxx_hal_drivers_2_0_0_alpha_2_0 INTERFACE hal)
    target_sources(STMicroelectronics_stm32h7pxx_hal_drivers_2_0_0_alpha_2_0 INTERFACE hal/stm32h7pxx_hal_rtc.c)
  endif()
endif()

if(CMSIS_USE_Device_STM32_HAL_SD_0_5_0)  # SD HAL driver
  message(DEBUG "Using component Device_STM32_HAL_SD_0_5_0")
  if(STMicroelectronics.stm32h7pxx_hal_drivers.2.0.0-alpha.2.0:HAL_CORE_SDMMC)
    target_compile_definitions(STMicroelectronics_stm32h7pxx_hal_drivers_2_0_0_alpha_2_0 INTERFACE -DCMSIS_USE_Device_STM32_HAL_SD_0_5_0=1)
    target_include_directories(STMicroelectronics_stm32h7pxx_hal_drivers_2_0_0_alpha_2_0 INTERFACE hal)
    target_sources(STMicroelectronics_stm32h7pxx_hal_drivers_2_0_0_alpha_2_0 INTERFACE hal/stm32h7pxx_hal_sd.c)
  endif()
endif()

if(CMSIS_USE_Device_STM32_HAL_SDIO_0_1_0)  # SDIO HAL driver
  message(DEBUG "Using component Device_STM32_HAL_SDIO_0_1_0")
  if(STMicroelectronics.stm32h7pxx_hal_drivers.2.0.0-alpha.2.0:HAL_CORE_SDMMC)
    target_compile_definitions(STMicroelectronics_stm32h7pxx_hal_drivers_2_0_0_alpha_2_0 INTERFACE -DCMSIS_USE_Device_STM32_HAL_SDIO_0_1_0=1)
    target_include_directories(STMicroelectronics_stm32h7pxx_hal_drivers_2_0_0_alpha_2_0 INTERFACE hal)
    target_sources(STMicroelectronics_stm32h7pxx_hal_drivers_2_0_0_alpha_2_0 INTERFACE hal/stm32h7pxx_hal_sdio.c)
  endif()
endif()

if(CMSIS_USE_Device_STM32_HAL_DRIVERS_CORE_SDMMC_0_1_0)  # SD/MMC low layer (SDMMC) HAL driver
  message(DEBUG "Using component Device_STM32_HAL_DRIVERS_CORE_SDMMC_0_1_0")
  if(STMicroelectronics.stm32h7pxx_hal_drivers.2.0.0-alpha.2.0:HAL_CORE)
    target_compile_definitions(STMicroelectronics_stm32h7pxx_hal_drivers_2_0_0_alpha_2_0 INTERFACE -DCMSIS_USE_Device_STM32_HAL_DRIVERS_CORE_SDMMC_0_1_0=1)
    target_include_directories(STMicroelectronics_stm32h7pxx_hal_drivers_2_0_0_alpha_2_0 INTERFACE hal)
    target_sources(STMicroelectronics_stm32h7pxx_hal_drivers_2_0_0_alpha_2_0 INTERFACE hal/stm32h7pxx_sdmmc_core.c)
  endif()
endif()

if(CMSIS_USE_Device_STM32_HAL_SMARTCARD_0_1_0)  # SMARTCARD HAL driver
  message(DEBUG "Using component Device_STM32_HAL_SMARTCARD_0_1_0")
  if(STMicroelectronics.stm32h7pxx_hal_drivers.2.0.0-alpha.2.0:HAL_SMARTCARD)
    target_compile_definitions(STMicroelectronics_stm32h7pxx_hal_drivers_2_0_0_alpha_2_0 INTERFACE -DCMSIS_USE_Device_STM32_HAL_SMARTCARD_0_1_0=1)
    target_include_directories(STMicroelectronics_stm32h7pxx_hal_drivers_2_0_0_alpha_2_0 INTERFACE hal)
    target_sources(STMicroelectronics_stm32h7pxx_hal_drivers_2_0_0_alpha_2_0 INTERFACE hal/stm32h7pxx_hal_smartcard.c)
  endif()
endif()

if(CMSIS_USE_Device_STM32_HAL_SMBUS_0_1_0)  # SMBus (SMBUS) interface HAL driver
  message(DEBUG "Using component Device_STM32_HAL_SMBUS_0_1_0")
  if(STMicroelectronics.stm32h7pxx_hal_drivers.2.0.0-alpha.2.0:HAL_SMBUS)
    target_compile_definitions(STMicroelectronics_stm32h7pxx_hal_drivers_2_0_0_alpha_2_0 INTERFACE -DCMSIS_USE_Device_STM32_HAL_SMBUS_0_1_0=1)
    target_include_directories(STMicroelectronics_stm32h7pxx_hal_drivers_2_0_0_alpha_2_0 INTERFACE hal)
    target_sources(STMicroelectronics_stm32h7pxx_hal_drivers_2_0_0_alpha_2_0 INTERFACE hal/stm32h7pxx_hal_smbus.c)
  endif()
endif()

if(CMSIS_USE_Device_STM32_HAL_SPI_0_1_1)  # Serial peripheral interface (SPI) HAL driver
  message(DEBUG "Using component Device_STM32_HAL_SPI_0_1_1")
  if(STMicroelectronics.stm32h7pxx_hal_drivers.2.0.0-alpha.2.0:HAL_SPI)
    target_compile_definitions(STMicroelectronics_stm32h7pxx_hal_drivers_2_0_0_alpha_2_0 INTERFACE -DCMSIS_USE_Device_STM32_HAL_SPI_0_1_1=1)
    target_include_directories(STMicroelectronics_stm32h7pxx_hal_drivers_2_0_0_alpha_2_0 INTERFACE hal)
    target_sources(STMicroelectronics_stm32h7pxx_hal_drivers_2_0_0_alpha_2_0 INTERFACE hal/stm32h7pxx_hal_spi.c)
  endif()
endif()

if(CMSIS_USE_Device_STM32_HAL_SBS_0_3_0)  # CORE configuration controller (SBS) HAL driver
  message(DEBUG "Using component Device_STM32_HAL_SBS_0_3_0")
  if(STMicroelectronics.stm32h7pxx_hal_drivers.2.0.0-alpha.2.0:HAL_SBS)
    target_compile_definitions(STMicroelectronics_stm32h7pxx_hal_drivers_2_0_0_alpha_2_0 INTERFACE -DCMSIS_USE_Device_STM32_HAL_SBS_0_3_0=1)
    target_include_directories(STMicroelectronics_stm32h7pxx_hal_drivers_2_0_0_alpha_2_0 INTERFACE hal)
    target_sources(STMicroelectronics_stm32h7pxx_hal_drivers_2_0_0_alpha_2_0 INTERFACE hal/stm32h7pxx_hal_sbs.c)
  endif()
endif()

if(CMSIS_USE_Device_STM32_HAL_SRAM_0_2_0)  # SRAM controller (SRAM) HAL driver
  message(DEBUG "Using component Device_STM32_HAL_SRAM_0_2_0")
  if(STMicroelectronics.stm32h7pxx_hal_drivers.2.0.0-alpha.2.0:HAL_CORE_SRAM)
    target_compile_definitions(STMicroelectronics_stm32h7pxx_hal_drivers_2_0_0_alpha_2_0 INTERFACE -DCMSIS_USE_Device_STM32_HAL_SRAM_0_2_0=1)
    target_include_directories(STMicroelectronics_stm32h7pxx_hal_drivers_2_0_0_alpha_2_0 INTERFACE hal)
    target_sources(STMicroelectronics_stm32h7pxx_hal_drivers_2_0_0_alpha_2_0 INTERFACE hal/stm32h7pxx_hal_sram.c)
  endif()
endif()

if(CMSIS_USE_Device_STM32_HAL_TAMP_0_1_4)  # Tampers (TAMP) HAL driver
  message(DEBUG "Using component Device_STM32_HAL_TAMP_0_1_4")
  if(STMicroelectronics.stm32h7pxx_hal_drivers.2.0.0-alpha.2.0:HAL_TAMP)
    target_compile_definitions(STMicroelectronics_stm32h7pxx_hal_drivers_2_0_0_alpha_2_0 INTERFACE -DCMSIS_USE_Device_STM32_HAL_TAMP_0_1_4=1)
    target_include_directories(STMicroelectronics_stm32h7pxx_hal_drivers_2_0_0_alpha_2_0 INTERFACE hal)
    target_sources(STMicroelectronics_stm32h7pxx_hal_drivers_2_0_0_alpha_2_0 INTERFACE hal/stm32h7pxx_hal_tamp.c)
  endif()
endif()

if(CMSIS_USE_Device_STM32_HAL_TIM_0_1_2)  # Timers (TIM) HAL driver
  message(DEBUG "Using component Device_STM32_HAL_TIM_0_1_2")
  if(STMicroelectronics.stm32h7pxx_hal_drivers.2.0.0-alpha.2.0:HAL_TIM)
    target_compile_definitions(STMicroelectronics_stm32h7pxx_hal_drivers_2_0_0_alpha_2_0 INTERFACE -DCMSIS_USE_Device_STM32_HAL_TIM_0_1_2=1)
    target_include_directories(STMicroelectronics_stm32h7pxx_hal_drivers_2_0_0_alpha_2_0 INTERFACE hal)
    target_sources(STMicroelectronics_stm32h7pxx_hal_drivers_2_0_0_alpha_2_0 INTERFACE hal/stm32h7pxx_hal_tim.c)
  endif()
endif()

if(CMSIS_USE_Device_STM32_HAL_UART_0_3_0)  # Universal asynchronous receiver transmitter (UART) HAL driver
  message(DEBUG "Using component Device_STM32_HAL_UART_0_3_0")
  if(STMicroelectronics.stm32h7pxx_hal_drivers.2.0.0-alpha.2.0:HAL_UART)
    target_compile_definitions(STMicroelectronics_stm32h7pxx_hal_drivers_2_0_0_alpha_2_0 INTERFACE -DCMSIS_USE_Device_STM32_HAL_UART_0_3_0=1)
    target_include_directories(STMicroelectronics_stm32h7pxx_hal_drivers_2_0_0_alpha_2_0 INTERFACE hal)
    target_sources(STMicroelectronics_stm32h7pxx_hal_drivers_2_0_0_alpha_2_0 INTERFACE hal/stm32h7pxx_hal_uart.c)
  endif()
endif()

if(CMSIS_USE_Device_STM32_HAL_UCPD_0_1_0)  # USB Type-C / USB Power Delivery (UCPD) interface HAL driver
  message(DEBUG "Using component Device_STM32_HAL_UCPD_0_1_0")
  if(STMicroelectronics.stm32h7pxx_hal_drivers.2.0.0-alpha.2.0:HAL_UCPD)
    target_compile_definitions(STMicroelectronics_stm32h7pxx_hal_drivers_2_0_0_alpha_2_0 INTERFACE -DCMSIS_USE_Device_STM32_HAL_UCPD_0_1_0=1)
    target_include_directories(STMicroelectronics_stm32h7pxx_hal_drivers_2_0_0_alpha_2_0 INTERFACE hal)
    target_sources(STMicroelectronics_stm32h7pxx_hal_drivers_2_0_0_alpha_2_0 INTERFACE hal/stm32h7pxx_hal_ucpd.c)
  endif()
endif()

if(CMSIS_USE_Device_STM32_HAL_USART_0_2_0)  # Universal synchronous asynchronous receiver transmitter (USART) HAL driver
  message(DEBUG "Using component Device_STM32_HAL_USART_0_2_0")
  if(STMicroelectronics.stm32h7pxx_hal_drivers.2.0.0-alpha.2.0:HAL_USART)
    target_compile_definitions(STMicroelectronics_stm32h7pxx_hal_drivers_2_0_0_alpha_2_0 INTERFACE -DCMSIS_USE_Device_STM32_HAL_USART_0_2_0=1)
    target_include_directories(STMicroelectronics_stm32h7pxx_hal_drivers_2_0_0_alpha_2_0 INTERFACE hal)
    target_sources(STMicroelectronics_stm32h7pxx_hal_drivers_2_0_0_alpha_2_0 INTERFACE hal/stm32h7pxx_hal_usart.c)
  endif()
endif()

if(CMSIS_USE_Device_STM32_HAL_DRIVERS_CORE_USB_CORE_DEF_0_1_1)  # USB Core Def (USB CORE DEF) HAL driver
  message(DEBUG "Using component Device_STM32_HAL_DRIVERS_CORE_USB_CORE_DEF_0_1_1")
  if(STMicroelectronics.stm32h7pxx_hal_drivers.2.0.0-alpha.2.0:HAL_CORE)
    target_compile_definitions(STMicroelectronics_stm32h7pxx_hal_drivers_2_0_0_alpha_2_0 INTERFACE -DCMSIS_USE_Device_STM32_HAL_DRIVERS_CORE_USB_CORE_DEF_0_1_1=1)
    target_include_directories(STMicroelectronics_stm32h7pxx_hal_drivers_2_0_0_alpha_2_0 INTERFACE hal)
  endif()
endif()

if(CMSIS_USE_Device_STM32_HAL_DRIVERS_CORE_USB_OTG_0_3_0)  # USB OTG Core (USB OTG) HAL driver
  message(DEBUG "Using component Device_STM32_HAL_DRIVERS_CORE_USB_OTG_0_3_0")
  if(STMicroelectronics.stm32h7pxx_hal_drivers.2.0.0-alpha.2.0:HAL_CORE)
    target_compile_definitions(STMicroelectronics_stm32h7pxx_hal_drivers_2_0_0_alpha_2_0 INTERFACE -DCMSIS_USE_Device_STM32_HAL_DRIVERS_CORE_USB_OTG_0_3_0=1)
    target_include_directories(STMicroelectronics_stm32h7pxx_hal_drivers_2_0_0_alpha_2_0 INTERFACE hal)
    target_sources(STMicroelectronics_stm32h7pxx_hal_drivers_2_0_0_alpha_2_0 INTERFACE hal/stm32h7pxx_usb_otg_core.c)
  endif()
endif()

if(CMSIS_USE_Device_STM32_HAL_VREFBUF_0_2_0)  # Voltage reference buffer (VREFBUF) HAL driver
  message(DEBUG "Using component Device_STM32_HAL_VREFBUF_0_2_0")
  if(STMicroelectronics.stm32h7pxx_hal_drivers.2.0.0-alpha.2.0:HAL_VREFBUF)
    target_compile_definitions(STMicroelectronics_stm32h7pxx_hal_drivers_2_0_0_alpha_2_0 INTERFACE -DCMSIS_USE_Device_STM32_HAL_VREFBUF_0_2_0=1)
    target_include_directories(STMicroelectronics_stm32h7pxx_hal_drivers_2_0_0_alpha_2_0 INTERFACE hal)
    target_sources(STMicroelectronics_stm32h7pxx_hal_drivers_2_0_0_alpha_2_0 INTERFACE hal/stm32h7pxx_hal_vrefbuf.c)
  endif()
endif()

if(CMSIS_USE_Device_STM32_HAL_WWDG_0_2_0)  # Window watchdog (WWDG) HAL driver
  message(DEBUG "Using component Device_STM32_HAL_WWDG_0_2_0")
  if(STMicroelectronics.stm32h7pxx_hal_drivers.2.0.0-alpha.2.0:HAL_WWDG)
    target_compile_definitions(STMicroelectronics_stm32h7pxx_hal_drivers_2_0_0_alpha_2_0 INTERFACE -DCMSIS_USE_Device_STM32_HAL_WWDG_0_2_0=1)
    target_include_directories(STMicroelectronics_stm32h7pxx_hal_drivers_2_0_0_alpha_2_0 INTERFACE hal)
    target_sources(STMicroelectronics_stm32h7pxx_hal_drivers_2_0_0_alpha_2_0 INTERFACE hal/stm32h7pxx_hal_wwdg.c)
  endif()
endif()

if(CMSIS_USE_Device_STM32_HAL_XSPI_0_5_0)  # Octo-SPI/Hexa-SPI (XSPI) HAL driver
  message(DEBUG "Using component Device_STM32_HAL_XSPI_0_5_0")
  if(STMicroelectronics.stm32h7pxx_hal_drivers.2.0.0-alpha.2.0:HAL_CORE_XSPI)
    target_compile_definitions(STMicroelectronics_stm32h7pxx_hal_drivers_2_0_0_alpha_2_0 INTERFACE -DCMSIS_USE_Device_STM32_HAL_XSPI_0_5_0=1)
    target_include_directories(STMicroelectronics_stm32h7pxx_hal_drivers_2_0_0_alpha_2_0 INTERFACE hal)
    target_sources(STMicroelectronics_stm32h7pxx_hal_drivers_2_0_0_alpha_2_0 INTERFACE hal/stm32h7pxx_hal_xspi.c)
  endif()
endif()

if(CMSIS_USE_Device_STM32_LL_Common_0_1_0)  # Common LL driver
  message(DEBUG "Using component Device_STM32_LL_Common_0_1_0")
  if(STMicroelectronics.stm32h7pxx_hal_drivers.2.0.0-alpha.2.0:CMSIS_Core)
    target_compile_definitions(STMicroelectronics_stm32h7pxx_hal_drivers_2_0_0_alpha_2_0 INTERFACE -DCMSIS_USE_Device_STM32_LL_Common_0_1_0=1)
    target_include_directories(STMicroelectronics_stm32h7pxx_hal_drivers_2_0_0_alpha_2_0 INTERFACE ll/)
  endif()
endif()

if(CMSIS_USE_Device_STM32_LL_ADC_0_1_1)  # Analog-to-digital converter (ADC) LL driver
  message(DEBUG "Using component Device_STM32_LL_ADC_0_1_1")
  if(STMicroelectronics.stm32h7pxx_hal_drivers.2.0.0-alpha.2.0:LL)
    target_compile_definitions(STMicroelectronics_stm32h7pxx_hal_drivers_2_0_0_alpha_2_0 INTERFACE -DCMSIS_USE_Device_STM32_LL_ADC_0_1_1=1)
    target_include_directories(STMicroelectronics_stm32h7pxx_hal_drivers_2_0_0_alpha_2_0 INTERFACE ll)
  endif()
endif()

if(CMSIS_USE_Device_STM32_LL_BUS_0_1_0)  # LL BUS driver
  message(DEBUG "Using component Device_STM32_LL_BUS_0_1_0")
  if(STMicroelectronics.stm32h7pxx_hal_drivers.2.0.0-alpha.2.0:LL)
    target_compile_definitions(STMicroelectronics_stm32h7pxx_hal_drivers_2_0_0_alpha_2_0 INTERFACE -DCMSIS_USE_Device_STM32_LL_BUS_0_1_0=1)
    target_include_directories(STMicroelectronics_stm32h7pxx_hal_drivers_2_0_0_alpha_2_0 INTERFACE ll)
  endif()
endif()

if(CMSIS_USE_Device_STM32_LL_COMP_0_1_0)  # COMP LL driver
  message(DEBUG "Using component Device_STM32_LL_COMP_0_1_0")
  if(STMicroelectronics.stm32h7pxx_hal_drivers.2.0.0-alpha.2.0:LL)
    target_compile_definitions(STMicroelectronics_stm32h7pxx_hal_drivers_2_0_0_alpha_2_0 INTERFACE -DCMSIS_USE_Device_STM32_LL_COMP_0_1_0=1)
    target_include_directories(STMicroelectronics_stm32h7pxx_hal_drivers_2_0_0_alpha_2_0 INTERFACE ll)
  endif()
endif()

if(CMSIS_USE_Device_STM32_LL_CORDIC_0_1_0)  # CORDIC LL driver
  message(DEBUG "Using component Device_STM32_LL_CORDIC_0_1_0")
  if(STMicroelectronics.stm32h7pxx_hal_drivers.2.0.0-alpha.2.0:LL)
    target_compile_definitions(STMicroelectronics_stm32h7pxx_hal_drivers_2_0_0_alpha_2_0 INTERFACE -DCMSIS_USE_Device_STM32_LL_CORDIC_0_1_0=1)
    target_include_directories(STMicroelectronics_stm32h7pxx_hal_drivers_2_0_0_alpha_2_0 INTERFACE ll)
  endif()
endif()

if(CMSIS_USE_Device_STM32_LL_CRC_0_1_0)  # CRC calculation unit (CRC) LL driver
  message(DEBUG "Using component Device_STM32_LL_CRC_0_1_0")
  if(STMicroelectronics.stm32h7pxx_hal_drivers.2.0.0-alpha.2.0:LL)
    target_compile_definitions(STMicroelectronics_stm32h7pxx_hal_drivers_2_0_0_alpha_2_0 INTERFACE -DCMSIS_USE_Device_STM32_LL_CRC_0_1_0=1)
    target_include_directories(STMicroelectronics_stm32h7pxx_hal_drivers_2_0_0_alpha_2_0 INTERFACE ll)
  endif()
endif()

if(CMSIS_USE_Device_STM32_LL_CRS_0_1_0)  # (CRS) LL driver
  message(DEBUG "Using component Device_STM32_LL_CRS_0_1_0")
  if(STMicroelectronics.stm32h7pxx_hal_drivers.2.0.0-alpha.2.0:LL)
    target_compile_definitions(STMicroelectronics_stm32h7pxx_hal_drivers_2_0_0_alpha_2_0 INTERFACE -DCMSIS_USE_Device_STM32_LL_CRS_0_1_0=1)
    target_include_directories(STMicroelectronics_stm32h7pxx_hal_drivers_2_0_0_alpha_2_0 INTERFACE ll)
  endif()
endif()

if(CMSIS_USE_Device_STM32_LL_DAC_0_1_1)  # Digital-to-analog converter (DAC) LL driver
  message(DEBUG "Using component Device_STM32_LL_DAC_0_1_1")
  if(STMicroelectronics.stm32h7pxx_hal_drivers.2.0.0-alpha.2.0:LL)
    target_compile_definitions(STMicroelectronics_stm32h7pxx_hal_drivers_2_0_0_alpha_2_0 INTERFACE -DCMSIS_USE_Device_STM32_LL_DAC_0_1_1=1)
    target_include_directories(STMicroelectronics_stm32h7pxx_hal_drivers_2_0_0_alpha_2_0 INTERFACE ll)
  endif()
endif()

if(CMSIS_USE_Device_STM32_LL_DBGMCU_0_1_0)  # System configuration (DBGMCU) LL driver
  message(DEBUG "Using component Device_STM32_LL_DBGMCU_0_1_0")
  if(STMicroelectronics.stm32h7pxx_hal_drivers.2.0.0-alpha.2.0:LL)
    target_compile_definitions(STMicroelectronics_stm32h7pxx_hal_drivers_2_0_0_alpha_2_0 INTERFACE -DCMSIS_USE_Device_STM32_LL_DBGMCU_0_1_0=1)
    target_include_directories(STMicroelectronics_stm32h7pxx_hal_drivers_2_0_0_alpha_2_0 INTERFACE ll)
  endif()
endif()

if(CMSIS_USE_Device_STM32_LL_DMA_0_2_1)  # DMA controller (DMA) LL driver
  message(DEBUG "Using component Device_STM32_LL_DMA_0_2_1")
  if(STMicroelectronics.stm32h7pxx_hal_drivers.2.0.0-alpha.2.0:LL)
    target_compile_definitions(STMicroelectronics_stm32h7pxx_hal_drivers_2_0_0_alpha_2_0 INTERFACE -DCMSIS_USE_Device_STM32_LL_DMA_0_2_1=1)
    target_include_directories(STMicroelectronics_stm32h7pxx_hal_drivers_2_0_0_alpha_2_0 INTERFACE ll)
  endif()
endif()

if(CMSIS_USE_Device_STM32_LL_FLASH_0_1_0)  # FLASH LL driver
  message(DEBUG "Using component Device_STM32_LL_FLASH_0_1_0")
  if(STMicroelectronics.stm32h7pxx_hal_drivers.2.0.0-alpha.2.0:LL)
    target_compile_definitions(STMicroelectronics_stm32h7pxx_hal_drivers_2_0_0_alpha_2_0 INTERFACE -DCMSIS_USE_Device_STM32_LL_FLASH_0_1_0=1)
    target_include_directories(STMicroelectronics_stm32h7pxx_hal_drivers_2_0_0_alpha_2_0 INTERFACE ll)
  endif()
endif()

if(CMSIS_USE_Device_STM32_LL_EXTI_0_1_0)  # Extended interrupts and events controller (EXTI) LL driver
  message(DEBUG "Using component Device_STM32_LL_EXTI_0_1_0")
  if(STMicroelectronics.stm32h7pxx_hal_drivers.2.0.0-alpha.2.0:LL)
    target_compile_definitions(STMicroelectronics_stm32h7pxx_hal_drivers_2_0_0_alpha_2_0 INTERFACE -DCMSIS_USE_Device_STM32_LL_EXTI_0_1_0=1)
    target_include_directories(STMicroelectronics_stm32h7pxx_hal_drivers_2_0_0_alpha_2_0 INTERFACE ll)
  endif()
endif()

if(CMSIS_USE_Device_STM32_LL_FMAC_0_1_0)  #  (FMAC) LL driver
  message(DEBUG "Using component Device_STM32_LL_FMAC_0_1_0")
  if(STMicroelectronics.stm32h7pxx_hal_drivers.2.0.0-alpha.2.0:LL)
    target_compile_definitions(STMicroelectronics_stm32h7pxx_hal_drivers_2_0_0_alpha_2_0 INTERFACE -DCMSIS_USE_Device_STM32_LL_FMAC_0_1_0=1)
    target_include_directories(STMicroelectronics_stm32h7pxx_hal_drivers_2_0_0_alpha_2_0 INTERFACE ll)
  endif()
endif()

if(CMSIS_USE_Device_STM32_LL_GPIO_0_1_0)  # General-purpose I/O (GPIO) LL driver
  message(DEBUG "Using component Device_STM32_LL_GPIO_0_1_0")
  if(STMicroelectronics.stm32h7pxx_hal_drivers.2.0.0-alpha.2.0:LL)
    target_compile_definitions(STMicroelectronics_stm32h7pxx_hal_drivers_2_0_0_alpha_2_0 INTERFACE -DCMSIS_USE_Device_STM32_LL_GPIO_0_1_0=1)
    target_include_directories(STMicroelectronics_stm32h7pxx_hal_drivers_2_0_0_alpha_2_0 INTERFACE ll)
  endif()
endif()

if(CMSIS_USE_Device_STM32_LL_HRTIM_0_1_0)  # High Resolution Timer (HRTIM) LL driver
  message(DEBUG "Using component Device_STM32_LL_HRTIM_0_1_0")
  if(STMicroelectronics.stm32h7pxx_hal_drivers.2.0.0-alpha.2.0:LL)
    target_compile_definitions(STMicroelectronics_stm32h7pxx_hal_drivers_2_0_0_alpha_2_0 INTERFACE -DCMSIS_USE_Device_STM32_LL_HRTIM_0_1_0=1)
    target_include_directories(STMicroelectronics_stm32h7pxx_hal_drivers_2_0_0_alpha_2_0 INTERFACE ll)
  endif()
endif()

if(CMSIS_USE_Device_STM32_LL_I2C_0_1_0)  # Inter-integrated circuit (I2C) interface LL driver
  message(DEBUG "Using component Device_STM32_LL_I2C_0_1_0")
  if(STMicroelectronics.stm32h7pxx_hal_drivers.2.0.0-alpha.2.0:LL)
    target_compile_definitions(STMicroelectronics_stm32h7pxx_hal_drivers_2_0_0_alpha_2_0 INTERFACE -DCMSIS_USE_Device_STM32_LL_I2C_0_1_0=1)
    target_include_directories(STMicroelectronics_stm32h7pxx_hal_drivers_2_0_0_alpha_2_0 INTERFACE ll)
  endif()
endif()

if(CMSIS_USE_Device_STM32_LL_I3C_0_1_0)  # Improved inter-integrated circuit (I3C) interface LL driver
  message(DEBUG "Using component Device_STM32_LL_I3C_0_1_0")
  if(STMicroelectronics.stm32h7pxx_hal_drivers.2.0.0-alpha.2.0:LL)
    target_compile_definitions(STMicroelectronics_stm32h7pxx_hal_drivers_2_0_0_alpha_2_0 INTERFACE -DCMSIS_USE_Device_STM32_LL_I3C_0_1_0=1)
    target_include_directories(STMicroelectronics_stm32h7pxx_hal_drivers_2_0_0_alpha_2_0 INTERFACE ll)
  endif()
endif()

if(CMSIS_USE_Device_STM32_LL_IWDG_0_1_0)  # Independent watchdog (IWDG) LL driver
  message(DEBUG "Using component Device_STM32_LL_IWDG_0_1_0")
  if(STMicroelectronics.stm32h7pxx_hal_drivers.2.0.0-alpha.2.0:LL)
    target_compile_definitions(STMicroelectronics_stm32h7pxx_hal_drivers_2_0_0_alpha_2_0 INTERFACE -DCMSIS_USE_Device_STM32_LL_IWDG_0_1_0=1)
    target_include_directories(STMicroelectronics_stm32h7pxx_hal_drivers_2_0_0_alpha_2_0 INTERFACE ll)
  endif()
endif()

if(CMSIS_USE_Device_STM32_LL_LPTIM_0_1_0)  # Low-power timer (LPTIM) interface LL driver
  message(DEBUG "Using component Device_STM32_LL_LPTIM_0_1_0")
  if(STMicroelectronics.stm32h7pxx_hal_drivers.2.0.0-alpha.2.0:LL)
    target_compile_definitions(STMicroelectronics_stm32h7pxx_hal_drivers_2_0_0_alpha_2_0 INTERFACE -DCMSIS_USE_Device_STM32_LL_LPTIM_0_1_0=1)
    target_include_directories(STMicroelectronics_stm32h7pxx_hal_drivers_2_0_0_alpha_2_0 INTERFACE ll)
  endif()
endif()

if(CMSIS_USE_Device_STM32_LL_LPUART_0_2_0)  # Low-power universal asynchronous receiver transmitter (LPUART) LL driver
  message(DEBUG "Using component Device_STM32_LL_LPUART_0_2_0")
  if(STMicroelectronics.stm32h7pxx_hal_drivers.2.0.0-alpha.2.0:LL)
    target_compile_definitions(STMicroelectronics_stm32h7pxx_hal_drivers_2_0_0_alpha_2_0 INTERFACE -DCMSIS_USE_Device_STM32_LL_LPUART_0_2_0=1)
    target_include_directories(STMicroelectronics_stm32h7pxx_hal_drivers_2_0_0_alpha_2_0 INTERFACE ll)
  endif()
endif()

if(CMSIS_USE_Device_STM32_LL_PWR_0_1_0)  # Power controller (PWR) LL driver
  message(DEBUG "Using component Device_STM32_LL_PWR_0_1_0")
  if(STMicroelectronics.stm32h7pxx_hal_drivers.2.0.0-alpha.2.0:LL)
    target_compile_definitions(STMicroelectronics_stm32h7pxx_hal_drivers_2_0_0_alpha_2_0 INTERFACE -DCMSIS_USE_Device_STM32_LL_PWR_0_1_0=1)
    target_include_directories(STMicroelectronics_stm32h7pxx_hal_drivers_2_0_0_alpha_2_0 INTERFACE ll)
  endif()
endif()

if(CMSIS_USE_Device_STM32_LL_RAMECC_0_1_0)  # RAM ECC controller (RAMECC) LL driver
  message(DEBUG "Using component Device_STM32_LL_RAMECC_0_1_0")
  if(STMicroelectronics.stm32h7pxx_hal_drivers.2.0.0-alpha.2.0:LL)
    target_compile_definitions(STMicroelectronics_stm32h7pxx_hal_drivers_2_0_0_alpha_2_0 INTERFACE -DCMSIS_USE_Device_STM32_LL_RAMECC_0_1_0=1)
    target_include_directories(STMicroelectronics_stm32h7pxx_hal_drivers_2_0_0_alpha_2_0 INTERFACE ll)
  endif()
endif()

if(CMSIS_USE_Device_STM32_LL_RCC_0_1_0)  # Reset and clock control (RCC) LL driver
  message(DEBUG "Using component Device_STM32_LL_RCC_0_1_0")
  if(STMicroelectronics.stm32h7pxx_hal_drivers.2.0.0-alpha.2.0:LL)
    target_compile_definitions(STMicroelectronics_stm32h7pxx_hal_drivers_2_0_0_alpha_2_0 INTERFACE -DCMSIS_USE_Device_STM32_LL_RCC_0_1_0=1)
    target_include_directories(STMicroelectronics_stm32h7pxx_hal_drivers_2_0_0_alpha_2_0 INTERFACE ll)
  endif()
endif()

if(CMSIS_USE_Device_STM32_LL_RNG_0_1_0)  # Random number generator (RNG) LL driver
  message(DEBUG "Using component Device_STM32_LL_RNG_0_1_0")
  if(STMicroelectronics.stm32h7pxx_hal_drivers.2.0.0-alpha.2.0:LL)
    target_compile_definitions(STMicroelectronics_stm32h7pxx_hal_drivers_2_0_0_alpha_2_0 INTERFACE -DCMSIS_USE_Device_STM32_LL_RNG_0_1_0=1)
    target_include_directories(STMicroelectronics_stm32h7pxx_hal_drivers_2_0_0_alpha_2_0 INTERFACE ll)
  endif()
endif()

if(CMSIS_USE_Device_STM32_LL_RTC_0_1_1)  # Real-time clock (RTC) LL driver
  message(DEBUG "Using component Device_STM32_LL_RTC_0_1_1")
  if(STMicroelectronics.stm32h7pxx_hal_drivers.2.0.0-alpha.2.0:LL)
    target_compile_definitions(STMicroelectronics_stm32h7pxx_hal_drivers_2_0_0_alpha_2_0 INTERFACE -DCMSIS_USE_Device_STM32_LL_RTC_0_1_1=1)
    target_include_directories(STMicroelectronics_stm32h7pxx_hal_drivers_2_0_0_alpha_2_0 INTERFACE ll)
  endif()
endif()

if(CMSIS_USE_Device_STM32_LL_TAMP_0_1_0)  # (TAMP) LL driver
  message(DEBUG "Using component Device_STM32_LL_TAMP_0_1_0")
  if(STMicroelectronics.stm32h7pxx_hal_drivers.2.0.0-alpha.2.0:LL)
    target_compile_definitions(STMicroelectronics_stm32h7pxx_hal_drivers_2_0_0_alpha_2_0 INTERFACE -DCMSIS_USE_Device_STM32_LL_TAMP_0_1_0=1)
    target_include_directories(STMicroelectronics_stm32h7pxx_hal_drivers_2_0_0_alpha_2_0 INTERFACE ll)
  endif()
endif()

if(CMSIS_USE_Device_STM32_LL_SPI_0_1_0)  # Serial peripheral interface (SPI) LL driver
  message(DEBUG "Using component Device_STM32_LL_SPI_0_1_0")
  if(STMicroelectronics.stm32h7pxx_hal_drivers.2.0.0-alpha.2.0:LL)
    target_compile_definitions(STMicroelectronics_stm32h7pxx_hal_drivers_2_0_0_alpha_2_0 INTERFACE -DCMSIS_USE_Device_STM32_LL_SPI_0_1_0=1)
    target_include_directories(STMicroelectronics_stm32h7pxx_hal_drivers_2_0_0_alpha_2_0 INTERFACE ll)
  endif()
endif()

if(CMSIS_USE_Device_STM32_LL_SBS_0_1_0)  # System configuration (SBS) LL driver
  message(DEBUG "Using component Device_STM32_LL_SBS_0_1_0")
  if(STMicroelectronics.stm32h7pxx_hal_drivers.2.0.0-alpha.2.0:LL)
    target_compile_definitions(STMicroelectronics_stm32h7pxx_hal_drivers_2_0_0_alpha_2_0 INTERFACE -DCMSIS_USE_Device_STM32_LL_SBS_0_1_0=1)
    target_include_directories(STMicroelectronics_stm32h7pxx_hal_drivers_2_0_0_alpha_2_0 INTERFACE ll)
  endif()
endif()

if(CMSIS_USE_Device_STM32_LL_SYSTEM_0_1_1)  # System configuration LL driver
  message(DEBUG "Using component Device_STM32_LL_SYSTEM_0_1_1")
  if(STMicroelectronics.stm32h7pxx_hal_drivers.2.0.0-alpha.2.0:LL)
    target_compile_definitions(STMicroelectronics_stm32h7pxx_hal_drivers_2_0_0_alpha_2_0 INTERFACE -DCMSIS_USE_Device_STM32_LL_SYSTEM_0_1_1=1)
    target_include_directories(STMicroelectronics_stm32h7pxx_hal_drivers_2_0_0_alpha_2_0 INTERFACE ll)
  endif()
endif()

if(CMSIS_USE_Device_STM32_LL_TIM_0_1_0)  # Timers (TIM) LL driver
  message(DEBUG "Using component Device_STM32_LL_TIM_0_1_0")
  if(STMicroelectronics.stm32h7pxx_hal_drivers.2.0.0-alpha.2.0:LL)
    target_compile_definitions(STMicroelectronics_stm32h7pxx_hal_drivers_2_0_0_alpha_2_0 INTERFACE -DCMSIS_USE_Device_STM32_LL_TIM_0_1_0=1)
    target_include_directories(STMicroelectronics_stm32h7pxx_hal_drivers_2_0_0_alpha_2_0 INTERFACE ll)
  endif()
endif()

if(CMSIS_USE_Device_STM32_LL_UCPD_0_1_0)  # USB Type-C / USB Power Delivery interface (UCPD) LL driver
  message(DEBUG "Using component Device_STM32_LL_UCPD_0_1_0")
  if(STMicroelectronics.stm32h7pxx_hal_drivers.2.0.0-alpha.2.0:LL)
    target_compile_definitions(STMicroelectronics_stm32h7pxx_hal_drivers_2_0_0_alpha_2_0 INTERFACE -DCMSIS_USE_Device_STM32_LL_UCPD_0_1_0=1)
    target_include_directories(STMicroelectronics_stm32h7pxx_hal_drivers_2_0_0_alpha_2_0 INTERFACE ll)
  endif()
endif()

if(CMSIS_USE_Device_STM32_LL_USART_0_2_0)  # Universal synchronous asynchronous receiver transmitter (USART) LL driver
  message(DEBUG "Using component Device_STM32_LL_USART_0_2_0")
  if(STMicroelectronics.stm32h7pxx_hal_drivers.2.0.0-alpha.2.0:LL)
    target_compile_definitions(STMicroelectronics_stm32h7pxx_hal_drivers_2_0_0_alpha_2_0 INTERFACE -DCMSIS_USE_Device_STM32_LL_USART_0_2_0=1)
    target_include_directories(STMicroelectronics_stm32h7pxx_hal_drivers_2_0_0_alpha_2_0 INTERFACE ll)
  endif()
endif()

if(CMSIS_USE_Device_STM32_LL_UTILS_0_1_1)  # Utils LL driver
  message(DEBUG "Using component Device_STM32_LL_UTILS_0_1_1")
  if(STMicroelectronics.stm32h7pxx_hal_drivers.2.0.0-alpha.2.0:STM32H7P)
    target_compile_definitions(STMicroelectronics_stm32h7pxx_hal_drivers_2_0_0_alpha_2_0 INTERFACE -DCMSIS_USE_Device_STM32_LL_UTILS_0_1_1=1)
    target_include_directories(STMicroelectronics_stm32h7pxx_hal_drivers_2_0_0_alpha_2_0 INTERFACE ll)
  endif()
endif()

if(CMSIS_USE_Device_STM32_LL_VREFBUF_0_1_0)  # Voltage reference buffer (VREFBUF) LL driver
  message(DEBUG "Using component Device_STM32_LL_VREFBUF_0_1_0")
  if(STMicroelectronics.stm32h7pxx_hal_drivers.2.0.0-alpha.2.0:LL)
    target_compile_definitions(STMicroelectronics_stm32h7pxx_hal_drivers_2_0_0_alpha_2_0 INTERFACE -DCMSIS_USE_Device_STM32_LL_VREFBUF_0_1_0=1)
    target_include_directories(STMicroelectronics_stm32h7pxx_hal_drivers_2_0_0_alpha_2_0 INTERFACE ll)
  endif()
endif()

if(CMSIS_USE_Device_STM32_LL_WWDG_0_1_0)  # System window watchdog (WWDG) LL driver
  message(DEBUG "Using component Device_STM32_LL_WWDG_0_1_0")
  if(STMicroelectronics.stm32h7pxx_hal_drivers.2.0.0-alpha.2.0:LL)
    target_compile_definitions(STMicroelectronics_stm32h7pxx_hal_drivers_2_0_0_alpha_2_0 INTERFACE -DCMSIS_USE_Device_STM32_LL_WWDG_0_1_0=1)
    target_include_directories(STMicroelectronics_stm32h7pxx_hal_drivers_2_0_0_alpha_2_0 INTERFACE ll)
  endif()
endif()

if(CMSIS_USE_Device_STM32_HAL_HAL_OS_NO_OS_0_0_1)  # HAL OS port without OS
  message(DEBUG "Using component Device_STM32_HAL_HAL_OS_NO_OS_0_0_1")
  if(STMicroelectronics.stm32h7pxx_hal_drivers.2.0.0-alpha.2.0:NO_OS)
    target_compile_definitions(STMicroelectronics_stm32h7pxx_hal_drivers_2_0_0_alpha_2_0 INTERFACE -DCMSIS_USE_Device_STM32_HAL_HAL_OS_NO_OS_0_0_1=1)
    target_include_directories(STMicroelectronics_stm32h7pxx_hal_drivers_2_0_0_alpha_2_0 INTERFACE os_port/no_os)
    target_include_directories(STMicroelectronics_stm32h7pxx_hal_drivers_2_0_0_alpha_2_0 INTERFACE os_port/no_os/)
    target_sources(STMicroelectronics_stm32h7pxx_hal_drivers_2_0_0_alpha_2_0 INTERFACE os_port/no_os/stm32_hal_os.c)
  endif()
endif()

if(CMSIS_USE_Device_STM32_HAL_HAL_OS_FreeRTOS_0_0_1)  # HAL OS port with MW FreeRTOS
  message(DEBUG "Using component Device_STM32_HAL_HAL_OS_FreeRTOS_0_0_1")
  if(STMicroelectronics.stm32h7pxx_hal_drivers.2.0.0-alpha.2.0:MW_FreeRTOS)
    target_compile_definitions(STMicroelectronics_stm32h7pxx_hal_drivers_2_0_0_alpha_2_0 INTERFACE -DCMSIS_USE_Device_STM32_HAL_HAL_OS_FreeRTOS_0_0_1=1)
    target_include_directories(STMicroelectronics_stm32h7pxx_hal_drivers_2_0_0_alpha_2_0 INTERFACE os_port/freertos)
    target_include_directories(STMicroelectronics_stm32h7pxx_hal_drivers_2_0_0_alpha_2_0 INTERFACE os_port/freertos/)
    target_sources(STMicroelectronics_stm32h7pxx_hal_drivers_2_0_0_alpha_2_0 INTERFACE os_port/freertos/stm32_hal_os.c)
  endif()
endif()

if(CMSIS_USE_Device_STM32_HAL_HAL_OS_TEMPLATE_OS_0_0_1)  # HAL OS port with CMSIS OS
  message(DEBUG "Using component Device_STM32_HAL_HAL_OS_TEMPLATE_OS_0_0_1")
  if(STMicroelectronics.stm32h7pxx_hal_drivers.2.0.0-alpha.2.0:TEMPLATE_OS)
    target_compile_definitions(STMicroelectronics_stm32h7pxx_hal_drivers_2_0_0_alpha_2_0 INTERFACE -DCMSIS_USE_Device_STM32_HAL_HAL_OS_TEMPLATE_OS_0_0_1=1)
    target_include_directories(STMicroelectronics_stm32h7pxx_hal_drivers_2_0_0_alpha_2_0 INTERFACE templates/os_port)
    target_sources(STMicroelectronics_stm32h7pxx_hal_drivers_2_0_0_alpha_2_0 INTERFACE templates/os_port/stm32_hal_os.c)
  endif()
endif()

