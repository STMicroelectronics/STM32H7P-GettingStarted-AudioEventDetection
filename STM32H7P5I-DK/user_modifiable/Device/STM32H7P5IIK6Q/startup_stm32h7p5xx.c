/**
  ******************************************************************************
  * @file    startup_stm32h7p5xx.c
  * @brief   Startup File for STM32H7P5xx Devices
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2026 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "stm32h7p5xx.h"

#ifdef __cplusplus
#error "startup_stm32h7p5xx.c file cannot be compiled with C++ compiler"
#endif /* __cplusplus */

/* External References -------------------------------------------------------*/
extern void SystemInit(void);
extern uint32_t __INITIAL_SP;

extern __NO_RETURN void __PROGRAM_START(void);

/* Private function prototypes -----------------------------------------------*/
/* ISR headers */
__NO_RETURN void Reset_Handler(void) __attribute__((weak));
            void Default_IRQHandler(void);
__NO_RETURN void Default_IRQHandler_Hook(void) __attribute__((weak));

/* Cortex-M interrupts */
void NMI_Handler                       (void) __attribute__((weak, alias("Default_IRQHandler")));
void HardFault_Handler                 (void) __attribute__((weak));
void MemManage_Handler                 (void) __attribute__((weak, alias("Default_IRQHandler")));
void BusFault_Handler                  (void) __attribute__((weak, alias("Default_IRQHandler")));
void UsageFault_Handler                (void) __attribute__((weak, alias("Default_IRQHandler")));
void SVC_Handler                       (void) __attribute__((weak, alias("Default_IRQHandler")));
void DebugMon_Handler                  (void) __attribute__((weak, alias("Default_IRQHandler")));
void PendSV_Handler                    (void) __attribute__((weak, alias("Default_IRQHandler")));
void SysTick_Handler                   (void) __attribute__((weak, alias("Default_IRQHandler")));

/* Device interrupts */
void PWR_PVD_AVD_IRQHandler            (void) __attribute__((weak, alias("Default_IRQHandler")));
void DTS_IRQHandler                    (void) __attribute__((weak, alias("Default_IRQHandler")));
void IWDG_IRQHandler                   (void) __attribute__((weak, alias("Default_IRQHandler")));
void WWDG_IRQHandler                   (void) __attribute__((weak, alias("Default_IRQHandler")));
void RCC_IRQHandler                    (void) __attribute__((weak, alias("Default_IRQHandler")));
void FLASH_IRQHandler                  (void) __attribute__((weak, alias("Default_IRQHandler")));
void RAMECC_IRQHandler                 (void) __attribute__((weak, alias("Default_IRQHandler")));
void FPU_IRQHandler                    (void) __attribute__((weak, alias("Default_IRQHandler")));
void LSECSS_IRQHandler                 (void) __attribute__((weak, alias("Default_IRQHandler")));
void TAMP_IRQHandler                   (void) __attribute__((weak, alias("Default_IRQHandler")));
void CTI0_IRQHandler                   (void) __attribute__((weak, alias("Default_IRQHandler")));
void CTI1_IRQHandler                   (void) __attribute__((weak, alias("Default_IRQHandler")));
void EXTI0_IRQHandler                  (void) __attribute__((weak, alias("Default_IRQHandler")));
void EXTI1_IRQHandler                  (void) __attribute__((weak, alias("Default_IRQHandler")));
void EXTI2_IRQHandler                  (void) __attribute__((weak, alias("Default_IRQHandler")));
void EXTI3_IRQHandler                  (void) __attribute__((weak, alias("Default_IRQHandler")));
void EXTI4_IRQHandler                  (void) __attribute__((weak, alias("Default_IRQHandler")));
void EXTI5_IRQHandler                  (void) __attribute__((weak, alias("Default_IRQHandler")));
void EXTI6_IRQHandler                  (void) __attribute__((weak, alias("Default_IRQHandler")));
void EXTI7_IRQHandler                  (void) __attribute__((weak, alias("Default_IRQHandler")));
void EXTI8_IRQHandler                  (void) __attribute__((weak, alias("Default_IRQHandler")));
void EXTI9_IRQHandler                  (void) __attribute__((weak, alias("Default_IRQHandler")));
void EXTI10_IRQHandler                 (void) __attribute__((weak, alias("Default_IRQHandler")));
void EXTI11_IRQHandler                 (void) __attribute__((weak, alias("Default_IRQHandler")));
void EXTI12_IRQHandler                 (void) __attribute__((weak, alias("Default_IRQHandler")));
void EXTI13_IRQHandler                 (void) __attribute__((weak, alias("Default_IRQHandler")));
void EXTI14_IRQHandler                 (void) __attribute__((weak, alias("Default_IRQHandler")));
void EXTI15_IRQHandler                 (void) __attribute__((weak, alias("Default_IRQHandler")));
void RTC_IRQHandler                    (void) __attribute__((weak, alias("Default_IRQHandler")));
void ADC2_IRQHandler                   (void) __attribute__((weak, alias("Default_IRQHandler")));
void ADC4_IRQHandler                   (void) __attribute__((weak, alias("Default_IRQHandler")));
void HASH_IRQHandler                   (void) __attribute__((weak, alias("Default_IRQHandler")));
void RNG_IRQHandler                    (void) __attribute__((weak, alias("Default_IRQHandler")));
void ADC1_IRQHandler                   (void) __attribute__((weak, alias("Default_IRQHandler")));
void GPDMA1_CH0_IRQHandler             (void) __attribute__((weak, alias("Default_IRQHandler")));
void GPDMA1_CH1_IRQHandler             (void) __attribute__((weak, alias("Default_IRQHandler")));
void GPDMA1_CH2_IRQHandler             (void) __attribute__((weak, alias("Default_IRQHandler")));
void GPDMA1_CH3_IRQHandler             (void) __attribute__((weak, alias("Default_IRQHandler")));
void GPDMA1_CH4_IRQHandler             (void) __attribute__((weak, alias("Default_IRQHandler")));
void GPDMA1_CH5_IRQHandler             (void) __attribute__((weak, alias("Default_IRQHandler")));
void GPDMA1_CH6_IRQHandler             (void) __attribute__((weak, alias("Default_IRQHandler")));
void GPDMA1_CH7_IRQHandler             (void) __attribute__((weak, alias("Default_IRQHandler")));
void TIM1_BRK_TERR_IERR_IRQHandler     (void) __attribute__((weak, alias("Default_IRQHandler")));
void TIM1_UPD_IRQHandler               (void) __attribute__((weak, alias("Default_IRQHandler")));
void TIM1_TRGI_COM_DIR_IDX_IRQHandler  (void) __attribute__((weak, alias("Default_IRQHandler")));
void TIM1_CC_IRQHandler                (void) __attribute__((weak, alias("Default_IRQHandler")));
void TIM2_IRQHandler                   (void) __attribute__((weak, alias("Default_IRQHandler")));
void TIM3_IRQHandler                   (void) __attribute__((weak, alias("Default_IRQHandler")));
void TIM4_IRQHandler                   (void) __attribute__((weak, alias("Default_IRQHandler")));
void TIM5_IRQHandler                   (void) __attribute__((weak, alias("Default_IRQHandler")));
void TIM6_IRQHandler                   (void) __attribute__((weak, alias("Default_IRQHandler")));
void TIM7_IRQHandler                   (void) __attribute__((weak, alias("Default_IRQHandler")));
void TIM9_IRQHandler                   (void) __attribute__((weak, alias("Default_IRQHandler")));
void SPI1_IRQHandler                   (void) __attribute__((weak, alias("Default_IRQHandler")));
void SPI2_IRQHandler                   (void) __attribute__((weak, alias("Default_IRQHandler")));
void SPI3_IRQHandler                   (void) __attribute__((weak, alias("Default_IRQHandler")));
void SPI4_IRQHandler                   (void) __attribute__((weak, alias("Default_IRQHandler")));
void SPI5_IRQHandler                   (void) __attribute__((weak, alias("Default_IRQHandler")));
void SPI6_IRQHandler                   (void) __attribute__((weak, alias("Default_IRQHandler")));
void HPDMA1_CH0_IRQHandler             (void) __attribute__((weak, alias("Default_IRQHandler")));
void HPDMA1_CH1_IRQHandler             (void) __attribute__((weak, alias("Default_IRQHandler")));
void HPDMA1_CH2_IRQHandler             (void) __attribute__((weak, alias("Default_IRQHandler")));
void HPDMA1_CH3_IRQHandler             (void) __attribute__((weak, alias("Default_IRQHandler")));
void HPDMA1_CH4_IRQHandler             (void) __attribute__((weak, alias("Default_IRQHandler")));
void HPDMA1_CH5_IRQHandler             (void) __attribute__((weak, alias("Default_IRQHandler")));
void HPDMA1_CH6_IRQHandler             (void) __attribute__((weak, alias("Default_IRQHandler")));
void HPDMA1_CH7_IRQHandler             (void) __attribute__((weak, alias("Default_IRQHandler")));
void TIM8_BRK_TERR_IERR_IRQHandler     (void) __attribute__((weak, alias("Default_IRQHandler")));
void TIM8_UPD_IRQHandler               (void) __attribute__((weak, alias("Default_IRQHandler")));
void TIM8_TRGI_COM_DIR_IDX_IRQHandler  (void) __attribute__((weak, alias("Default_IRQHandler")));
void TIM8_CC_IRQHandler                (void) __attribute__((weak, alias("Default_IRQHandler")));
void I2C1_EV_IRQHandler                (void) __attribute__((weak, alias("Default_IRQHandler")));
void I2C1_ERR_IRQHandler               (void) __attribute__((weak, alias("Default_IRQHandler")));
void I2C2_EV_IRQHandler                (void) __attribute__((weak, alias("Default_IRQHandler")));
void I2C2_ERR_IRQHandler               (void) __attribute__((weak, alias("Default_IRQHandler")));
void I2C3_EV_IRQHandler                (void) __attribute__((weak, alias("Default_IRQHandler")));
void I2C3_ERR_IRQHandler               (void) __attribute__((weak, alias("Default_IRQHandler")));
void USART1_IRQHandler                 (void) __attribute__((weak, alias("Default_IRQHandler")));
void USART2_IRQHandler                 (void) __attribute__((weak, alias("Default_IRQHandler")));
void USART3_IRQHandler                 (void) __attribute__((weak, alias("Default_IRQHandler")));
void UART4_IRQHandler                  (void) __attribute__((weak, alias("Default_IRQHandler")));
void UART5_IRQHandler                  (void) __attribute__((weak, alias("Default_IRQHandler")));
void UART7_IRQHandler                  (void) __attribute__((weak, alias("Default_IRQHandler")));
void UART8_IRQHandler                  (void) __attribute__((weak, alias("Default_IRQHandler")));
void I3C1_EV_IRQHandler                (void) __attribute__((weak, alias("Default_IRQHandler")));
void I3C1_ERR_IRQHandler               (void) __attribute__((weak, alias("Default_IRQHandler")));
void FMAC1_IRQHandler                  (void) __attribute__((weak, alias("Default_IRQHandler")));
void CORDIC_IRQHandler                 (void) __attribute__((weak, alias("Default_IRQHandler")));
void ADC3_IRQHandler                   (void) __attribute__((weak, alias("Default_IRQHandler")));
void TIM20_BRK_TERR_IERR_IRQHandler    (void) __attribute__((weak, alias("Default_IRQHandler")));
void TIM20_UPD_IRQHandler              (void) __attribute__((weak, alias("Default_IRQHandler")));
void TIM20_TRGI_COM_DIR_IDX_IRQHandler (void) __attribute__((weak, alias("Default_IRQHandler")));
void TIM20_CC_IRQHandler               (void) __attribute__((weak, alias("Default_IRQHandler")));
void TIM10_IRQHandler                  (void) __attribute__((weak, alias("Default_IRQHandler")));
void TIM11_IRQHandler                  (void) __attribute__((weak, alias("Default_IRQHandler")));
void I3C1_WKUP_IRQHandler              (void) __attribute__((weak, alias("Default_IRQHandler")));
void NPU_IT0_IRQHandler                (void) __attribute__((weak, alias("Default_IRQHandler")));
void NPU_IT1_IRQHandler                (void) __attribute__((weak, alias("Default_IRQHandler")));
void NPU_IT2_IRQHandler                (void) __attribute__((weak, alias("Default_IRQHandler")));
void XSPI1_IRQHandler                  (void) __attribute__((weak, alias("Default_IRQHandler")));
void HSP1_IRQHandler                   (void) __attribute__((weak, alias("Default_IRQHandler")));
void FMC_IRQHandler                    (void) __attribute__((weak, alias("Default_IRQHandler")));
void SDMMC1_IRQHandler                 (void) __attribute__((weak, alias("Default_IRQHandler")));
void HSP1_ERR_IRQHandler               (void) __attribute__((weak, alias("Default_IRQHandler")));
void HSP1_EVT_IRQHandler               (void) __attribute__((weak, alias("Default_IRQHandler")));
void HSP1_FWEVT_IRQHandler             (void) __attribute__((weak, alias("Default_IRQHandler")));
void USB_OTG_FS_IRQHandler             (void) __attribute__((weak, alias("Default_IRQHandler")));
void TIM12_IRQHandler                  (void) __attribute__((weak, alias("Default_IRQHandler")));
void TIM13_IRQHandler                  (void) __attribute__((weak, alias("Default_IRQHandler")));
void TIM14_IRQHandler                  (void) __attribute__((weak, alias("Default_IRQHandler")));
void TIM15_IRQHandler                  (void) __attribute__((weak, alias("Default_IRQHandler")));
void TIM16_IRQHandler                  (void) __attribute__((weak, alias("Default_IRQHandler")));
void TIM17_IRQHandler                  (void) __attribute__((weak, alias("Default_IRQHandler")));
void LPTIM1_IRQHandler                 (void) __attribute__((weak, alias("Default_IRQHandler")));
void LPTIM2_IRQHandler                 (void) __attribute__((weak, alias("Default_IRQHandler")));
void LPTIM3_IRQHandler                 (void) __attribute__((weak, alias("Default_IRQHandler")));
void LPTIM4_IRQHandler                 (void) __attribute__((weak, alias("Default_IRQHandler")));
void LPTIM5_IRQHandler                 (void) __attribute__((weak, alias("Default_IRQHandler")));
void UART9_IRQHandler                  (void) __attribute__((weak, alias("Default_IRQHandler")));
void USART10_IRQHandler                (void) __attribute__((weak, alias("Default_IRQHandler")));
void ADF1_FLT0_IRQHandler              (void) __attribute__((weak, alias("Default_IRQHandler")));
void CRS_IRQHandler                    (void) __attribute__((weak, alias("Default_IRQHandler")));
void UCPD1_IRQHandler                  (void) __attribute__((weak, alias("Default_IRQHandler")));
void WKUP5_8_IRQHandler                (void) __attribute__((weak, alias("Default_IRQHandler")));
void USART6_IRQHandler                 (void) __attribute__((weak, alias("Default_IRQHandler")));
void LPUART1_IRQHandler                (void) __attribute__((weak, alias("Default_IRQHandler")));
void WKUP1_4_IRQHandler                (void) __attribute__((weak, alias("Default_IRQHandler")));
void GPDMA1_CH8_IRQHandler             (void) __attribute__((weak, alias("Default_IRQHandler")));
void GPDMA1_CH9_IRQHandler             (void) __attribute__((weak, alias("Default_IRQHandler")));
void GPDMA1_CH10_IRQHandler            (void) __attribute__((weak, alias("Default_IRQHandler")));
void GPDMA1_CH11_IRQHandler            (void) __attribute__((weak, alias("Default_IRQHandler")));
void GPDMA1_CH12_IRQHandler            (void) __attribute__((weak, alias("Default_IRQHandler")));
void GPDMA1_CH13_IRQHandler            (void) __attribute__((weak, alias("Default_IRQHandler")));
void GPDMA1_CH14_IRQHandler            (void) __attribute__((weak, alias("Default_IRQHandler")));
void GPDMA1_CH15_IRQHandler            (void) __attribute__((weak, alias("Default_IRQHandler")));
void HPDMA1_CH8_IRQHandler             (void) __attribute__((weak, alias("Default_IRQHandler")));
void HPDMA1_CH9_IRQHandler             (void) __attribute__((weak, alias("Default_IRQHandler")));
void HPDMA1_CH10_IRQHandler            (void) __attribute__((weak, alias("Default_IRQHandler")));
void HPDMA1_CH11_IRQHandler            (void) __attribute__((weak, alias("Default_IRQHandler")));
void HPDMA1_CH12_IRQHandler            (void) __attribute__((weak, alias("Default_IRQHandler")));
void HPDMA1_CH13_IRQHandler            (void) __attribute__((weak, alias("Default_IRQHandler")));
void HPDMA1_CH14_IRQHandler            (void) __attribute__((weak, alias("Default_IRQHandler")));
void HPDMA1_CH15_IRQHandler            (void) __attribute__((weak, alias("Default_IRQHandler")));
void FDCAN3_IT0_IRQHandler             (void) __attribute__((weak, alias("Default_IRQHandler")));
void FDCAN3_IT1_IRQHandler             (void) __attribute__((weak, alias("Default_IRQHandler")));
void FDCAN1_IT0_IRQHandler             (void) __attribute__((weak, alias("Default_IRQHandler")));
void FDCAN1_IT1_IRQHandler             (void) __attribute__((weak, alias("Default_IRQHandler")));
void FDCAN2_IT0_IRQHandler             (void) __attribute__((weak, alias("Default_IRQHandler")));
void FDCAN2_IT1_IRQHandler             (void) __attribute__((weak, alias("Default_IRQHandler")));
void DAC1_IRQHandler                   (void) __attribute__((weak, alias("Default_IRQHandler")));
void DAC2_IRQHandler                   (void) __attribute__((weak, alias("Default_IRQHandler")));
void DAC3_IRQHandler                   (void) __attribute__((weak, alias("Default_IRQHandler")));
void DAC4_IRQHandler                   (void) __attribute__((weak, alias("Default_IRQHandler")));
void COMP1_IRQHandler                  (void) __attribute__((weak, alias("Default_IRQHandler")));
void COMP2_IRQHandler                  (void) __attribute__((weak, alias("Default_IRQHandler")));
void COMP3_IRQHandler                  (void) __attribute__((weak, alias("Default_IRQHandler")));
void COMP4_IRQHandler                  (void) __attribute__((weak, alias("Default_IRQHandler")));
void HRTIM1_M_IRQHandler               (void) __attribute__((weak, alias("Default_IRQHandler")));
void HRTIM1_TIMA_IRQHandler            (void) __attribute__((weak, alias("Default_IRQHandler")));
void HRTIM1_TIMB_IRQHandler            (void) __attribute__((weak, alias("Default_IRQHandler")));
void HRTIM1_TIMC_IRQHandler            (void) __attribute__((weak, alias("Default_IRQHandler")));
void HRTIM1_TIMD_IRQHandler            (void) __attribute__((weak, alias("Default_IRQHandler")));
void HRTIM1_TIME_IRQHandler            (void) __attribute__((weak, alias("Default_IRQHandler")));
void HRTIM1_TIMF_IRQHandler            (void) __attribute__((weak, alias("Default_IRQHandler")));
void HRTIM1_FLT_IRQHandler             (void) __attribute__((weak, alias("Default_IRQHandler")));
void HRTIM2_M_IRQHandler               (void) __attribute__((weak, alias("Default_IRQHandler")));
void HRTIM2_TIMA_IRQHandler            (void) __attribute__((weak, alias("Default_IRQHandler")));
void HRTIM2_TIMB_IRQHandler            (void) __attribute__((weak, alias("Default_IRQHandler")));
void HRTIM2_TIMC_IRQHandler            (void) __attribute__((weak, alias("Default_IRQHandler")));
void HRTIM2_TIMD_IRQHandler            (void) __attribute__((weak, alias("Default_IRQHandler")));
void HRTIM2_TIME_IRQHandler            (void) __attribute__((weak, alias("Default_IRQHandler")));
void HRTIM2_TIMF_IRQHandler            (void) __attribute__((weak, alias("Default_IRQHandler")));
void HRTIM2_FLT_IRQHandler             (void) __attribute__((weak, alias("Default_IRQHandler")));
void COMP5_IRQHandler                  (void) __attribute__((weak, alias("Default_IRQHandler")));
void COMP6_IRQHandler                  (void) __attribute__((weak, alias("Default_IRQHandler")));
void COMP7_IRQHandler                  (void) __attribute__((weak, alias("Default_IRQHandler")));
void COMP8_IRQHandler                  (void) __attribute__((weak, alias("Default_IRQHandler")));

/* Private variables ---------------------------------------------------------*/
/**
  Vector table
  */

#if defined ( __GNUC__ )
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wpedantic"
#endif /* __GNUC__ */

extern const VECTOR_TABLE_Type __VECTOR_TABLE[];
const VECTOR_TABLE_Type __VECTOR_TABLE[] __VECTOR_TABLE_ATTRIBUTE =
{
  (VECTOR_TABLE_Type)(&__INITIAL_SP), /* The initial stack pointer */
  Reset_Handler,
  NMI_Handler,
  HardFault_Handler,
  MemManage_Handler,
  BusFault_Handler,
  UsageFault_Handler,
  0,
  0,
  0,
  0,
  SVC_Handler,
  DebugMon_Handler,
  0,
  PendSV_Handler,
  SysTick_Handler,
  PWR_PVD_AVD_IRQHandler,
  0,
  DTS_IRQHandler,
  IWDG_IRQHandler,
  WWDG_IRQHandler,
  RCC_IRQHandler,
  0,
  0,
  FLASH_IRQHandler,
  RAMECC_IRQHandler,
  FPU_IRQHandler,
  0,
  LSECSS_IRQHandler,
  TAMP_IRQHandler,
  CTI0_IRQHandler,
  CTI1_IRQHandler,
  EXTI0_IRQHandler,
  EXTI1_IRQHandler,
  EXTI2_IRQHandler,
  EXTI3_IRQHandler,
  EXTI4_IRQHandler,
  EXTI5_IRQHandler,
  EXTI6_IRQHandler,
  EXTI7_IRQHandler,
  EXTI8_IRQHandler,
  EXTI9_IRQHandler,
  EXTI10_IRQHandler,
  EXTI11_IRQHandler,
  EXTI12_IRQHandler,
  EXTI13_IRQHandler,
  EXTI14_IRQHandler,
  EXTI15_IRQHandler,
  RTC_IRQHandler,
  0,
  ADC2_IRQHandler,
  ADC4_IRQHandler,
  HASH_IRQHandler,
  RNG_IRQHandler,
  ADC1_IRQHandler,
  GPDMA1_CH0_IRQHandler,
  GPDMA1_CH1_IRQHandler,
  GPDMA1_CH2_IRQHandler,
  GPDMA1_CH3_IRQHandler,
  GPDMA1_CH4_IRQHandler,
  GPDMA1_CH5_IRQHandler,
  GPDMA1_CH6_IRQHandler,
  GPDMA1_CH7_IRQHandler,
  TIM1_BRK_TERR_IERR_IRQHandler,
  TIM1_UPD_IRQHandler,
  TIM1_TRGI_COM_DIR_IDX_IRQHandler,
  TIM1_CC_IRQHandler,
  TIM2_IRQHandler,
  TIM3_IRQHandler,
  TIM4_IRQHandler,
  TIM5_IRQHandler,
  TIM6_IRQHandler,
  TIM7_IRQHandler,
  TIM9_IRQHandler,
  SPI1_IRQHandler,
  SPI2_IRQHandler,
  SPI3_IRQHandler,
  SPI4_IRQHandler,
  SPI5_IRQHandler,
  SPI6_IRQHandler,
  HPDMA1_CH0_IRQHandler,
  HPDMA1_CH1_IRQHandler,
  HPDMA1_CH2_IRQHandler,
  HPDMA1_CH3_IRQHandler,
  HPDMA1_CH4_IRQHandler,
  HPDMA1_CH5_IRQHandler,
  HPDMA1_CH6_IRQHandler,
  HPDMA1_CH7_IRQHandler,
  TIM8_BRK_TERR_IERR_IRQHandler,
  TIM8_UPD_IRQHandler,
  TIM8_TRGI_COM_DIR_IDX_IRQHandler,
  TIM8_CC_IRQHandler,
  I2C1_EV_IRQHandler,
  I2C1_ERR_IRQHandler,
  I2C2_EV_IRQHandler,
  I2C2_ERR_IRQHandler,
  I2C3_EV_IRQHandler,
  I2C3_ERR_IRQHandler,
  USART1_IRQHandler,
  USART2_IRQHandler,
  USART3_IRQHandler,
  UART4_IRQHandler,
  UART5_IRQHandler,
  UART7_IRQHandler,
  UART8_IRQHandler,
  I3C1_EV_IRQHandler,
  I3C1_ERR_IRQHandler,
  0,
  FMAC1_IRQHandler,
  CORDIC_IRQHandler,
  ADC3_IRQHandler,
  TIM20_BRK_TERR_IERR_IRQHandler,
  TIM20_UPD_IRQHandler,
  TIM20_TRGI_COM_DIR_IDX_IRQHandler,
  TIM20_CC_IRQHandler,
  TIM10_IRQHandler,
  TIM11_IRQHandler,
  I3C1_WKUP_IRQHandler,
  NPU_IT0_IRQHandler,
  NPU_IT1_IRQHandler,
  NPU_IT2_IRQHandler,
  XSPI1_IRQHandler,
  HSP1_IRQHandler,
  FMC_IRQHandler,
  SDMMC1_IRQHandler,
  HSP1_ERR_IRQHandler,
  HSP1_EVT_IRQHandler,
  HSP1_FWEVT_IRQHandler,
  USB_OTG_FS_IRQHandler,
  TIM12_IRQHandler,
  TIM13_IRQHandler,
  TIM14_IRQHandler,
  TIM15_IRQHandler,
  TIM16_IRQHandler,
  TIM17_IRQHandler,
  LPTIM1_IRQHandler,
  LPTIM2_IRQHandler,
  LPTIM3_IRQHandler,
  LPTIM4_IRQHandler,
  LPTIM5_IRQHandler,
  UART9_IRQHandler,
  USART10_IRQHandler,
  ADF1_FLT0_IRQHandler,
  CRS_IRQHandler,
  UCPD1_IRQHandler,
  WKUP5_8_IRQHandler,
  USART6_IRQHandler,
  LPUART1_IRQHandler,
  WKUP1_4_IRQHandler,
  GPDMA1_CH8_IRQHandler,
  GPDMA1_CH9_IRQHandler,
  GPDMA1_CH10_IRQHandler,
  GPDMA1_CH11_IRQHandler,
  GPDMA1_CH12_IRQHandler,
  GPDMA1_CH13_IRQHandler,
  GPDMA1_CH14_IRQHandler,
  GPDMA1_CH15_IRQHandler,
  HPDMA1_CH8_IRQHandler,
  HPDMA1_CH9_IRQHandler,
  HPDMA1_CH10_IRQHandler,
  HPDMA1_CH11_IRQHandler,
  HPDMA1_CH12_IRQHandler,
  HPDMA1_CH13_IRQHandler,
  HPDMA1_CH14_IRQHandler,
  HPDMA1_CH15_IRQHandler,
  0,
  FDCAN3_IT0_IRQHandler,
  FDCAN3_IT1_IRQHandler,
  FDCAN1_IT0_IRQHandler,
  FDCAN1_IT1_IRQHandler,
  FDCAN2_IT0_IRQHandler,
  FDCAN2_IT1_IRQHandler,
  DAC1_IRQHandler,
  DAC2_IRQHandler,
  DAC3_IRQHandler,
  DAC4_IRQHandler,
  COMP1_IRQHandler,
  COMP2_IRQHandler,
  COMP3_IRQHandler,
  COMP4_IRQHandler,
  HRTIM1_M_IRQHandler,
  HRTIM1_TIMA_IRQHandler,
  HRTIM1_TIMB_IRQHandler,
  HRTIM1_TIMC_IRQHandler,
  HRTIM1_TIMD_IRQHandler,
  HRTIM1_TIME_IRQHandler,
  HRTIM1_TIMF_IRQHandler,
  HRTIM1_FLT_IRQHandler,
  HRTIM2_M_IRQHandler,
  HRTIM2_TIMA_IRQHandler,
  HRTIM2_TIMB_IRQHandler,
  HRTIM2_TIMC_IRQHandler,
  HRTIM2_TIMD_IRQHandler,
  HRTIM2_TIME_IRQHandler,
  HRTIM2_TIMF_IRQHandler,
  HRTIM2_FLT_IRQHandler,
  COMP5_IRQHandler,
  COMP6_IRQHandler,
  COMP7_IRQHandler,
  COMP8_IRQHandler
};

#if defined ( __GNUC__ )
#pragma GCC diagnostic pop
#endif /* __GNUC__ */

/* Private functions ---------------------------------------------------------*/

/**
  * @brief  This function is the Reset Handler called on controller reset.
  * @param  None
  * @retval None
  */
__WEAK __NO_RETURN void Reset_Handler(void)
{

  SystemInit();         /* CMSIS System Initialization */
  __PROGRAM_START();    /* Enter PreMain (C library entry point) */
}

#if defined(__ARMCC_VERSION) && (__ARMCC_VERSION >= 6010050)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wmissing-noreturn"
#endif /* __ARMCC_VERSION */

/**
  * @brief  Hard Fault Handler.
  * @param  None
  * @retval None
  */
__WEAK void HardFault_Handler(void)
{
  while (1);
}

/**
  * @brief  This function is the default IRQ handler
  *         when the IRQ line is not used by the application.
  * @param  None
  * @retval None
  */
void Default_IRQHandler(void)
{
  Default_IRQHandler_Hook();
}

/**
  * @brief  This function is the default IRQHandler implementation hook
  *         could be overridden by the application.
  * @param  None
  * @retval None
  */
__WEAK void Default_IRQHandler_Hook(void)
{
  while (1);
}

#if defined(__ARMCC_VERSION) && (__ARMCC_VERSION >= 6010050)
#pragma clang diagnostic pop
#endif /* __ARMCC_VERSION */
