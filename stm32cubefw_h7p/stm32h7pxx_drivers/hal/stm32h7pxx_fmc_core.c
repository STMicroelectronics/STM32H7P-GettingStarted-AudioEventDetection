/**
  **********************************************************************************************************************
  * @file    stm32h7pxx_fmc_core.c
  * @author  GPM Application Team
  * @brief   FMC Low Layer HAL module driver.
  *
  *          This file provides firmware functions to manage the following functionalities of the Flexible Memory
  *          Controller (FMC):
  *           - Set the FMC registers configuration functions
  *           - Retrieve the FMC registers configuration functions
  *
  **********************************************************************************************************************
  * @attention
  *
  * Copyright (c) 2024-2025 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  **********************************************************************************************************************
  */

/* Includes ----------------------------------------------------------------------------------------------------------*/
#include "stm32h7pxx_fmc_core.h"


/** @addtogroup FMC_Core
  * @{
  */

/** @defgroup FMC_Core_Private_Constants FMC Core Private Constants
  * @{
  */
#if defined (FMC_NORSRAM_BK1)
/* BCR register configuration mask for static config */
#define BCR_CFG_MSK (FMC_BCRx_MBKEN   | FMC_BCRx_MUXEN     | FMC_BCRx_MTYP    | FMC_BCRx_MWID     | FMC_BCRx_FACCEN | \
                     FMC_BCRx_BURSTEN | FMC_BCRx_WAITPOL   | FMC_BCRx_WAITCFG | FMC_BCRx_WREN     | FMC_BCRx_WAITEN | \
                     FMC_BCRx_EXTMOD  | FMC_BCRx_ASYNCWAIT | FMC_BCRx_CPSIZE  | FMC_BCRx_CBURSTRW | FMC_BCR1_CCLKEN | \
                     FMC_BCR1_WFDIS)

/* BCR register configuration mask for memory config*/
#define MEM_CFG_MSK (FMC_BCRx_MWID    | FMC_BCRx_CPSIZE | FMC_BCRx_MUXEN   | FMC_BCRx_ASYNCWAIT | FMC_BCRx_WAITEN | \
                     FMC_BCRx_WAITCFG | FMC_BCR1_CCLKEN | FMC_BCRx_BURSTEN | FMC_BCRx_CBURSTRW)

/* BWTR register configuration mask */
#define BWTR_CFG_MASK (FMC_BWTRx_ADDSET | FMC_BWTRx_ADDHLD | FMC_BWTRx_DATAST | FMC_BWTRx_BUSTURN | FMC_BWTRx_ACCMOD)
#endif /* defined(FMC_NORSRAM_BK1) */

/* Clock div bitfield shift */
#define FMC_CLKDIV_SHIFT (4U)

/**
  * @}
  */

/* Exported functions ------------------------------------------------------------------------------------------------*/
/** @addtogroup FMC_Core_Exported_Functions
  * @{
This driver contains a set of APIs to interface with the FMC banks in order to run the external devices.
This section provides functions allowing to:
  - Configure the FMC NORSRAM interface
  - Get the FMC NORSRAM interface configuration
  */
#if defined (FMC_NORSRAM_BK1)
/**
  * @brief Set the FMC NORSRAM device according to the specified static FMC parameters.
  * @param p_instance Pointer to NORSRAM device instance.
  * @param config     Contains the static FMC configuration information.
  */
void FMC_NOR_SRAM_SetConfig(fmc_norsram_subbank_t *p_instance, uint32_t config)
{
  STM32_MODIFY_REG(p_instance->BCR, BCR_CFG_MSK, (config | FMC_BCRx_WREN));

  /* Configure Write FIFO mode when Write Fifo is enabled for bank2..4 */
  if ((p_instance != FMC_NORSRAM1_SUBBANK1) && ((config & FMC_BCR1_WFDIS) == FMC_WRITE_FIFO_ENABLE))
  {
    STM32_CLEAR_BIT(FMC_NORSRAM1_SUBBANK1->BCR, FMC_BCR1_WFDIS);
  }
}

/**
  * @brief Retrieve the FMC NORSRAM device static FMC parameters.
  * @param p_instance Pointer to NORSRAM device instance.
  * @param p_config   Contains the static FMC configuration information.
  */
void FMC_NOR_SRAM_GetConfig(const fmc_norsram_subbank_t *p_instance, uint32_t *p_config)
{
  /* Read control register */
  *p_config = p_instance->BCR;

  /* Check FIFO configuration */
  if (STM32_READ_BIT(FMC_NORSRAM1_SUBBANK1->BCR, FMC_BCR1_WFDIS) == 0U)
  {
    STM32_CLEAR_BIT(*p_config, FMC_BCR1_WFDIS);
  }
}

/**
  * @brief Set the FMC NORSRAM device according to the specified memory parameters.
  * @param p_instance  Pointer to NORSRAM device instance.
  * @param control_cfg Contains the control configuration information.
  * @param timing_cfg  Contains the timing configuration information.
  */
void FMC_NOR_SRAM_SetConfigMemory(fmc_norsram_subbank_t *p_instance, uint32_t control_cfg, uint32_t timing_cfg)
{
  /* Set configuration mask value */
  STM32_MODIFY_REG(p_instance->BCR, MEM_CFG_MSK, control_cfg);
  STM32_WRITE_REG(p_instance->BTR, timing_cfg);
  STM32_WRITE_REG(p_instance->BWTR, FMC_WR_TIMING_VALUE);
}

/**
  * @brief Retrieve the FMC NORSRAM device memory parameters.
  * @param p_instance    Pointer to NORSRAM device instance.
  * @param p_control_cfg Contains the control configuration information.
  * @param p_timing_cfg  Contains the timing configuration information.
  */
void FMC_NOR_SRAM_GetConfigMemory(const fmc_norsram_subbank_t *p_instance, uint32_t *p_control_cfg,
                                  uint32_t *p_timing_cfg)
{
  /* Read control register */
  *p_control_cfg = p_instance->BCR;

  /* Check FIFO configuration */
  if (STM32_READ_BIT(FMC_NORSRAM1_SUBBANK1->BCR, FMC_BCR1_WFDIS) == 0U)
  {
    STM32_CLEAR_BIT(*p_control_cfg, FMC_BCR1_WFDIS);
  }

  /* Read timing register */
  *p_timing_cfg = p_instance->BTR;

  /* Check continuous clock and clock div configuration */
  if (STM32_READ_BIT(FMC_NORSRAM1_SUBBANK1->BCR, FMC_BCR1_CCLKEN) == FMC_BCR1_CCLKEN)
  {
    STM32_SET_BIT(*p_control_cfg, FMC_BCR1_CCLKEN);
    STM32_MODIFY_REG(*p_timing_cfg, FMC_BTRx_CLKDIV, STM32_READ_BIT(FMC_NORSRAM1_SUBBANK1->BTR, FMC_BTRx_CLKDIV));
  }
}

/**
  * @brief Set the FMC NORSRAM device clock configuration.
  * @param clock_cfg     Contains the clock configuration information.
  * @param clock_div_cfg Contains the clock division configuration information.
  */
void FMC_NOR_SRAM_SetClock(uint32_t clock_cfg, uint32_t clock_div_cfg)
{
  /* Configure the continuous clock when Continuous clock is enabled for bank2..4 */
  STM32_SET_BIT(FMC_NORSRAM1_SUBBANK1->BCR, clock_cfg | FMC_BCR1_CCLKEN);

  /* Align the clock div to the lowest frequency when the continuous clock is enabled */
  if (clock_cfg != 0U)
  {
    if (clock_div_cfg > STM32_READ_BIT(FMC_NORSRAM1_SUBBANK1->BTR, FMC_BTRx_CLKDIV))
    {
      STM32_MODIFY_REG(FMC_NORSRAM1_SUBBANK1->BTR, FMC_BTRx_CLKDIV, clock_div_cfg);
    }
  }
}

/**
  * @brief Set the FMC NORSRAM device according to the specified write timing parameters.
  * @param p_instance     Pointer to NORSRAM device instance.
  * @param rd_access_mode Contains the read access mode information.
  * @param wr_timing_cfg  Contains the write timing configuration information.
  */
void FMC_NOR_SRAM_SetWrTiming(fmc_norsram_subbank_t *p_instance, uint32_t rd_access_mode, uint32_t wr_timing_cfg)
{
  /* Set timing value */
  STM32_SET_BIT(p_instance->BCR, FMC_BCRx_EXTMOD);
  STM32_MODIFY_REG(p_instance->BTR, FMC_BTRx_ACCMOD, rd_access_mode);
  STM32_MODIFY_REG(p_instance->BWTR, BWTR_CFG_MASK, wr_timing_cfg);
}

/**
  * @brief Retrieve the FMC NORSRAM device write timing parameters.
  * @param p_instance       Pointer to NORSRAM device instance.
  * @param p_rd_access_mode Contains the read access mode information.
  * @param p_wr_timing_cfg  Contains the write timing configuration information.
  */
void FMC_NOR_SRAM_GetWrTiming(const fmc_norsram_subbank_t *p_instance, uint32_t *p_rd_access_mode,
                              uint32_t *p_wr_timing_cfg)
{
  *p_rd_access_mode = STM32_READ_BIT(p_instance->BTR, FMC_BTRx_ACCMOD);
  /* Read write timing register */
  *p_wr_timing_cfg = p_instance->BWTR;
}

#endif /* defined(FMC_NORSRAM_BK1) */
/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */
