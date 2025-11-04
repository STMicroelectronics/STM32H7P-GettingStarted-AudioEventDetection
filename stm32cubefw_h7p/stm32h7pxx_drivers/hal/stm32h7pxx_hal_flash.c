/**
  **********************************************************************************************************************
  * @file    stm32h7pxx_hal_flash.c
  * @author  GPM Application Team
  * @brief   This file provides FLASH memory services.
  **********************************************************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  **********************************************************************************************************************
  */

/* Includes ----------------------------------------------------------------------------------------------------------*/
#include "stm32_hal.h"
/** @addtogroup STM32U5xx_HAL_Driver
  * @{
  */
/** @addtogroup FLASH
  * @{
This file provides firmware functions to manage the following functionalities of FLASH memory:
- Initialization and De-initialization functions
- Configuration functions
- Lock and Unlock functions
- Process operation functions
- Callbacks functions
- Status functions
The Flash memory interface manages CPU AHB C-Bus accesses to the Flash memory. It implements the erase and program Flash
memory operations and the read and write protection mechanisms.
# FLASH main features
The FLASH memory organization is based on a main area and an information block.
  - The main flash memory block organized as two banks of up to 2 Mbytes each containing up to 256 pages of 8 Kbytes.
  - The information block contains :
    - 32 Kbytes for system memory. It contains the bootloader that is used to reprogram the flash memory.
    - 32 Kbytes immutable secure area containing the root security services (RSS and RSS library).
    - 512 bytes OTP (one-time programmable). The OTP data cannot be erased and can be written only once.
    - Option bytes for user configuration. To configure the option bytes must be used the FLASH_OB drivers.
## Lock mechanism :
  - After reset, the FLASH control registers access are protected.
    The Unlock sequence is necessary to run any operation on the FLASH.
## Programming operation :
  - The flash memory program operation can be performed by two modes :
    - Standard programming mode (Quad-word mode) : Program 128 bits at a time within the flash memory.
    - Burst mode : Program 8 quad word at a time within the flash memory
  - Programming in a previously programmed address is not allowed except if the data to write is full zero.
## Erasing operation :
  - The flash memory erase operation can be performed at page level.
  - The flash memory erase operation can be performed at bank level.
  - The flash memory erase operation can be performed on the whole flash memory.
# How to use the FLASH HAL module driver
## Initialization and De-initialization functions :
- For a given instance, use HAL_FLASH_Init() function to initialize the FLASH handle and associate physical instance.
- Use HAL_FLASH_DeInit() function to de-initialize a FLASH, When called, the FLASH must be in reset.
## Process operation functions :
### Polling mode operations :
- Use the HAL_FLASH_ProgramByAddr() function to program by address any area of FLASH memory in polling mode.
- Use the HAL_FLASH_OTP_ProgramByAddr() function to program by address any OTP area in polling mode.
- Use the HAL_FLASH_EraseByAddr() function to erase by address any area FLASH memory in polling mode.
- Use the HAL_FLASH_ErasePage() function to erase a specifics pages of FLASH memory in polling mode.
- Use HAL_FLASH_EraseBank() function to erase FLASH memory bank after the configuration of bank number to be erased.
- Use HAL_FLASH_MassErase() function to erase all FLASH memory banks.
### Interrupt mode operations :
- Configure the FLASH interrupt priority using HAL_CORTEX_NVIC_SetPriority() function
- Enable the FLASH IRQ handler using HAL_CORTEX_NVIC_EnableIRQ() function
- Use HAL_FLASH_RegisterProgramCpltCallback() function to register the FLASH program complete callback.
- Use HAL_FLASH_RegisterEraseByAddrCpltCallback() function to register the FLASH erase by address complete callback.
- Use HAL_FLASH_RegisterErasePageCpltCallback() function to register the FLASH erase by page complete callback.
- Use HAL_FLASH_RegisterEraseBankCpltCallback() function to register the FLASH bank erase complete callback.
- Use HAL_FLASH_RegisterMassEraseCpltCallback() function to register the FLASH mass erase complete callback.
- Use HAL_FLASH_RegisterErrorCallback() function to register the FLASH error callback.
- Use HAL_FLASH_ProgramByAddr_IT() function to program by address the FLASH memory in interrupt mode.
- Use HAL_FLASH_OTP_ProgramByAddr_IT() function to program by address the OTP area in interrupt mode.
- Use HAL_FLASH_EraseByAddr_IT() function to erase by address the FLASH memory in interrupt mode.
- Use HAL_FLASH_ErasePage_IT() function to erase by page the FLASH memory in interrupt mode.
- Use HAL_FLASH_EraseBank_IT() function to erase a bank of FLASH memory in interrupt mode.
- Use HAL_FLASH_MassErase_IT() function to erase all FLASH memory banks in interrupt mode.
- Use HAL_FLASH_IRQHandler() function called under FLASH_IRQHandler interrupt subroutine to handle any FLASH interrupt.
- Use HAL_FLASH_ProgramByAddr_IRQHandler() function called under FLASH_IRQHandler interrupt subroutine to handle
  any FLASH program interrupt.
- Use HAL_FLASH_EraseByAddr_IRQHandler() function called under FLASH_IRQHandler interrupt subroutine to handle
  any FLASH erase by address interrupt.
- Use HAL_FLASH_ErasePage_IRQHandler() function called under FLASH_IRQHandler interrupt subroutine to handle
  any FLASH erase page interrupt.
- Use HAL_FLASH_EraseBank_IRQHandler() function called under FLASH_IRQHandler interrupt subroutine to handle
  any FLASH erase bank interrupt.
- Use HAL_FLASH_MassErase_IRQHandler() function called under FLASH_IRQHandler interrupt subroutine to handle
  any FLASH mass erase interrupt.
## Status functions :
- Use HAL_FLASH_GetOperation() function to get the last flash operation.
- Use HAL_FLASH_GetProgramOperationInfo() function to get the last flash programming operation information.
- Use HAL_FLASH_GetEraseByAddrOperationInfo() function to get the last flash erase by address operation information.
- Use HAL_FLASH_GetErasePageOperationInfo() function to get the last flash erase by page operation information.
- Use HAL_FLASH_GetEraseBankOperationInfo() function to get the last flash bank erase operation information.
- Use HAL_FLASH_GetInterruptedByResetOperationInfo() function to get the interrupted flash operation information.
- Use HAL_FLASH_GetInfo() function to get the flash information.
- Use HAL_FLASH_GetAddressOffset() function to get the address offset.
- Use HAL_FLASH_GetUserFlashPageSizeByte() function to get the page size.
- Use HAL_FLASH_GetBankSize() function to get the bank size.
- Use HAL_FLASH_GetState() function to get the flash global state.
- Use HAL_FLASH_GetLastErrorCodes() function to get the last error codes.
- Use HAL_FLASH_SetUserData() function to set a user data within the flash handle.
- Use HAL_FLASH_GetUserData() function to get the user data from the flash handle.
## Configuration inside the FLASH driver

Configuration defines           | Description     | Default value   | Note                                             |
--------------------------------| --------------- | --------------- | -------------------------------------------------|
PRODUCT                         | from IDE        |        NA       | The selected device (ex STM32H7P5xx)             |
USE_HAL_FLASH_MODULE            | from hal_conf.h |        1        | Allows to use HAL FLASH module.                  |
USE_ASSERT_DBG_PARAM            | from IDE        |      None       | Allows to use the assert check parameters.       |
USE_ASSERT_DBG_STATE            | from IDE        |      None       | Allows to use the assert check states.           |
USE_HAL_CHECK_PARAM             | from hal_conf.h |        0        | Allows to use the run-time checks parameters.    |
USE_HAL_CHECK_PROCESS_STATE     | from hal_conf.h |        0        | Allows to use the load and store exclusive.      |
USE_HAL_FLASH_REGISTER_CALLBACKS| from hal_conf.h |        0        | Allows to use the register callbacks             |
USE_HAL_FLASH_GET_LAST_ERRORS   | from hal_conf.h |        0        | Allows to use error code mechanism.              |
USE_HAL_FLASH_USER_DATA         | from hal_conf.h |        0        | Allows to use user data.                         |
USE_HAL_FLASH_PROGRAM_BY_ADDR   | from hal_conf.h |        1        | Allows to use program by address feature APIs    |
USE_HAL_FLASH_ERASE_BY_ADDR     | from hal_conf.h |        1        | Allows to use erase by address feature APIs      |
USE_HAL_FLASH_ERASE_PAGE        | from hal_conf.h |        1        | Allows to use erase by page feature APIs         |
USE_HAL_FLASH_ERASE_BANK        | from hal_conf.h |        1        | Allows to use erase by bank feature APIs         |
USE_HAL_FLASH_MASS_ERASE        | from hal_conf.h |        1        | Allows to use mass erase feature APIs            |
USE_HAL_FLASH_COMPUTE_CRC       | from hal_conf.h |        1        | Allows to use compute CRC feature APIs           |
USE_HAL_FLASH_ECC               | from hal_conf.h |        1        | Allows to use ECC errors handling APIs           |
  */

#if defined (USE_HAL_FLASH_MODULE) && (USE_HAL_FLASH_MODULE == 1)
/* Private Constants -------------------------------------------------------------------------------------------------*/
/** @defgroup FLASH_Private_Constants FLASH Private Constants
  * @{
  */
#define FLASH_OPERATION_MAX_TIMEOUT        1000U /*!< FLASH Operation maximum timeout    */
#define FLASH_ERASE_PAGE_OPERATION_TIMEOUT 10U   /*!< FLASH Erase page operation timeout */
/**
  * @}
  */

/* Private Macros ----------------------------------------------------------------------------------------------------*/
/** @defgroup FLASH_Private_Macros FLASH Private Macros
  * @{
  */

/*! Macro to get the FLASH physical instance from the handle */
#define FLASH_GET_INSTANCE(hflash) ((FLASH_TypeDef *)((uint32_t)((hflash)->instance)))

/*! Macro to check FLASH instance */
#define IS_FLASH_INSTANCE(instance) ((instance) == HAL_FLASH)

/*! Macro to check FLASH memory programming mode type */
#define IS_FLASH_PROGRAM_MODE_TYPE(mode) (((mode) == HAL_FLASH_PROGRAM_QUADWORD) \
                                          || ((mode) == HAL_FLASH_PROGRAM_DOUBLEWORD) \
                                          || ((mode) == HAL_FLASH_PROGRAM_WORD) \
                                          || ((mode) == HAL_FLASH_PROGRAM_HALFWORD) \
                                          || ((mode) == HAL_FLASH_PROGRAM_BYTE))

/*! Macro to check FLASH memory bank */
#define IS_FLASH_BANK(value) (((value) == HAL_FLASH_BANK_1)    \
                              || ((value) == HAL_FLASH_BANK_2))

/* Macro to check the FLASH user bank boundary cross */
#define IS_FLASH_NO_USER_CROSS_BANK(addr, size) (((addr) < (FLASH_BASE + FLASH_BANK_SIZE)) \
                                                 ? (((addr) + (size)) <= (FLASH_BASE + FLASH_BANK_SIZE)) \
                                                 : (((addr) + (size)) <= (FLASH_BASE + FLASH_SIZE)))

/*! Macro to check FLASH memory address granularity */
#define IS_FLASH_ADDRESS(value) (((value) >= FLASH_BASE) \
                                 ? (((value) % (uint32_t)HAL_FLASH_PROGRAM_QUADWORD) == 0U) : (0 == 1))

/*! Macro to check FLASH memory size_byte in range */
#define IS_FLASH_SIZE_IN_RANGE(flash_addr, size_byte) (((flash_addr) + (size_byte)) \
                                                       <= (FLASH_BASE + FLASH_SIZE_DEFAULT))

/*! Macro to check FLASH memory address granularity */
#define IS_FLASH_OTP_ADDRESS(value) (((value) >= OTP_AREA_BASE) \
                                     ? (((value) % (uint32_t)HAL_FLASH_PROGRAM_HALFWORD) == 0U) : (0 == 1))

/*! Macro to check FLASH memory size_byte in range */
#define IS_FLASH_OTP_SIZE_IN_RANGE(otp_addr, size_byte) (((otp_addr) + (size_byte)) \
                                                         <= (OTP_AREA_BASE + OTP_SIZE))

/*! Macro to check FLASH USER programming size */
#define IS_FLASH_USER_PROGRAM_SIZE(value) \
  ((((value) % (uint32_t) HAL_FLASH_PROGRAM_QUADWORD) == ((uint32_t) HAL_FLASH_PROGRAM_DOUBLEWORD)) \
   || (((value) % (uint32_t) HAL_FLASH_PROGRAM_QUADWORD) == ((uint32_t) HAL_FLASH_PROGRAM_WORD)) \
   || (((value) % (uint32_t) HAL_FLASH_PROGRAM_QUADWORD) == ((uint32_t) HAL_FLASH_PROGRAM_HALFWORD)) \
   || (((value) % (uint32_t) HAL_FLASH_PROGRAM_QUADWORD) == (1U)) \
   || (((value) % (uint32_t) HAL_FLASH_PROGRAM_QUADWORD) == (0U)))

/*! Macro to check FLASH memory start page and page number in range */
#define IS_FLASH_PAGE_IN_RANGE(page, page_nbr) (((page) + (page_nbr)) <= (uint32_t)FLASH_PAGE_NB)

/*! Macro to get the flash bank index */
#define FLASH_GET_BANK_INDEX(value) (((value) == HAL_FLASH_BANK_1) ? 0U : 1U)

/*! Macro to get the flash bank */
#define FLASH_GET_BANK(value) (((value) == 0U) ? HAL_FLASH_BANK_1 : HAL_FLASH_BANK_2)

/*! Macro to check FLASH CRC burst size */
#define IS_FLASH_CRC_BURST_SIZE(value) (((value) == HAL_FLASH_CRC_BURST_SIZE_4)    \
                                        || ((value) == HAL_FLASH_CRC_BURST_SIZE_16)\
                                        || ((value) == HAL_FLASH_CRC_BURST_SIZE_64)\
                                        || ((value) == HAL_FLASH_CRC_BURST_SIZE_256))
/**
  * @}
  */

/* Private Functions Prototypes --------------------------------------------------------------------------------------*/
/** @defgroup FLASH_Private_Functions FLASH Private Functions
  * @{
  */
static hal_status_t     FLASH_WaitForEndOfOperation(hal_flash_handle_t *hflash,
                                                    hal_flash_bank_t bank,
                                                    uint32_t timeout_msec);

#if defined (USE_HAL_FLASH_PROGRAM_BY_ADDR) && (USE_HAL_FLASH_PROGRAM_BY_ADDR == 1U)
static uint32_t         FLASH_UpdateAdaptiveProgMode(hal_flash_handle_t *hflash, hal_flash_bank_t bank);
static hal_status_t     FLASH_Program(hal_flash_handle_t *hflash, uint32_t flash_addr, const uint32_t *p_data,
                                      uint32_t size_byte, uint32_t is_adaptive_prog, uint32_t timeout_msec);
static hal_status_t     FLASH_Program_IT(hal_flash_handle_t *hflash, uint32_t flash_addr, const uint32_t *p_data,
                                         uint32_t size_byte, uint32_t is_adaptive_prog);
static void             FLASH_ProgramByWord(hal_flash_handle_t *hflash, hal_flash_bank_t bank, uint32_t count);
static void             FLASH_ProgramByHalfWord(hal_flash_handle_t *hflash, hal_flash_bank_t bank, uint32_t count);
static void             FLASH_ProgramByByte(hal_flash_handle_t *hflash, hal_flash_bank_t bank, uint32_t count);
#endif /* USE_HAL_FLASH_PROGRAM_BY_ADDR */

#if defined (USE_HAL_FLASH_ERASE_BY_ADDR) && (USE_HAL_FLASH_ERASE_BY_ADDR == 1U)
static hal_status_t     FLASH_EraseAddr(hal_flash_handle_t *hflash, uint32_t flash_addr, uint32_t size_byte,
                                        uint32_t page_size, uint32_t timeout_msec);
static hal_status_t     FLASH_EraseAddr_IT(hal_flash_handle_t *hflash, uint32_t flash_addr, uint32_t size_byte,
                                           uint32_t page_size);
#endif /* USE_HAL_FLASH_ERASE_BY_ADDR */

#if defined (USE_HAL_FLASH_ERASE_PAGE) && (USE_HAL_FLASH_ERASE_PAGE == 1U)
static hal_status_t     FLASH_ErasePage(hal_flash_handle_t *hflash, hal_flash_bank_t bank, uint32_t start_page,
                                        uint32_t page_nbr, uint32_t timeout_msec);
static hal_status_t     FLASH_ErasePage_IT(hal_flash_handle_t *hflash, hal_flash_bank_t bank, uint32_t start_page,
                                           uint32_t page_nbr);
#endif /* USE_HAL_FLASH_ERASE_PAGE */

#if defined (USE_HAL_FLASH_ERASE_BANK) && (USE_HAL_FLASH_ERASE_BANK == 1U)
static void             FLASH_BankErase(hal_flash_handle_t *hflash, hal_flash_bank_t bank);
#endif /* USE_HAL_FLASH_ERASE_BANK */
#if (defined (USE_HAL_FLASH_PROGRAM_BY_ADDR) || defined (USE_HAL_FLASH_ERASE_BY_ADDR)) \
    && ((USE_HAL_FLASH_PROGRAM_BY_ADDR == 1U) || (USE_HAL_FLASH_ERASE_BY_ADDR == 1U))
static hal_flash_bank_t FLASH_GetBank(const hal_flash_handle_t *hflash, uint32_t flash_addr);
static uint32_t         FLASH_GetPageIndex(const hal_flash_handle_t *hflash, uint32_t flash_addr);
static uint32_t FLASH_IsFlashUSERAddress(const hal_flash_handle_t *hflash, uint32_t flash_addr, uint8_t is_prog_addr);
#endif /* USE_HAL_FLASH_PROGRAM_BY_ADDR || USE_HAL_FLASH_ERASE_BY_ADDR */
#if defined(USE_HAL_FLASH_GET_LAST_ERRORS) && (USE_HAL_FLASH_GET_LAST_ERRORS == 1)
static void             FLASH_FillErrorCode(hal_flash_handle_t *hflash, hal_flash_bank_t bank, uint64_t error_code);
#endif /* USE_HAL_FLASH_GET_LAST_ERRORS */
/**
  * @}
  */

/* Exported Functions ------------------------------------------------------------------------------------------------*/
/** @addtogroup FLASH_Exported_Functions
  * @{
  */

/** @addtogroup FLASH_Exported_Functions_Group1
  * @{
This subsection provides a set of functions allowing to initialize and de-initialize the FLASH peripheral:
- Call the function HAL_FLASH_Init() to initialize the FLASH handle and associate a physical FLASH instance.
  (As optional, FLASH clock is enabled inside the function)
- Call the function HAL_FLASH_DeInit() to de-initialize the FLASH handle.
  */

/**
  * @brief  Initialize the FLASH handle and associate a physical FLASH instance.
  * @param  hflash            Pointer to a \ref hal_flash_handle_t structure.
  * @param  instance          Specifies the FLASH instance based on \ref hal_flash_t enumeration.
  * @retval HAL_INVALID_PARAM Invalid parameter when hflash pointer is NULL.
  * @retval HAL_OK            FLASH is successfully initialized.
  */
hal_status_t HAL_FLASH_Init(hal_flash_handle_t *hflash, hal_flash_t instance)
{
  ASSERT_DBG_PARAM(hflash != NULL);
  ASSERT_DBG_PARAM(IS_FLASH_INSTANCE(instance));

#if defined (USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (hflash == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  hflash->instance = instance;

#if defined (USE_HAL_FLASH_REGISTER_CALLBACKS) && (USE_HAL_FLASH_REGISTER_CALLBACKS == 1)
#if defined (USE_HAL_FLASH_PROGRAM_BY_ADDR) && (USE_HAL_FLASH_PROGRAM_BY_ADDR == 1U)
  hflash->p_program_cplt_cb       = HAL_FLASH_ProgramCpltCallback;
#endif /* USE_HAL_FLASH_PROGRAM_BY_ADDR */
#if defined (USE_HAL_FLASH_ERASE_BY_ADDR) && (USE_HAL_FLASH_ERASE_BY_ADDR == 1U)
  hflash->p_erase_by_addr_cplt_cb = HAL_FLASH_EraseByAddrCpltCallback;
#endif /* USE_HAL_FLASH_ERASE_BY_ADDR */
#if defined (USE_HAL_FLASH_ERASE_PAGE) && (USE_HAL_FLASH_ERASE_PAGE == 1U)
  hflash->p_erase_page_cplt_cb    = HAL_FLASH_ErasePageCpltCallback;
#endif /* USE_HAL_FLASH_ERASE_PAGE */
#if defined (USE_HAL_FLASH_ERASE_BANK) && (USE_HAL_FLASH_ERASE_BANK == 1U)
  hflash->p_erase_bank_cplt_cb    = HAL_FLASH_EraseBankCpltCallback;
#endif /* USE_HAL_FLASH_ERASE_BANK */
#if defined (USE_HAL_FLASH_MASS_ERASE) && (USE_HAL_FLASH_MASS_ERASE == 1U)
  hflash->p_mass_erase_cplt_cb    = HAL_FLASH_MassEraseCpltCallback;
#endif /* USE_HAL_FLASH_MASS_ERASE */
#if defined (USE_HAL_FLASH_COMPUTE_CRC) && (USE_HAL_FLASH_COMPUTE_CRC == 1U)
  hflash->p_compute_crc_cplt_cb   = HAL_FLASH_ComputeCRCCpltCallback;
#endif /* USE_HAL_FLASH_COMPUTE_CRC */
  hflash->p_error_cb              = HAL_FLASH_ErrorCallback;
#if defined (USE_HAL_FLASH_ECC) && (USE_HAL_FLASH_ECC == 1U)
  hflash->p_ecc_error_cb          = HAL_FLASH_ECC_ErrorCallback;
#endif /* USE_HAL_FLASH_ECC */
#endif /* USE_HAL_FLASH_REGISTER_CALLBACKS */
#if defined(USE_HAL_FLASH_USER_DATA) && (USE_HAL_FLASH_USER_DATA == 1)
  hflash->p_user_data = NULL;
#endif /* USE_HAL_FLASH_USER_DATA */
#if defined (USE_HAL_FLASH_GET_LAST_ERRORS) && (USE_HAL_FLASH_GET_LAST_ERRORS == 1)
  hflash->last_error_codes[0] = HAL_FLASH_ERROR_NONE;
  hflash->last_error_codes[1] = HAL_FLASH_ERROR_NONE;
#endif /* USE_HAL_FLASH_GET_LAST_ERRORS */
  hflash->ongoing_operation[0] = HAL_FLASH_NO_OPERATION;
  hflash->ongoing_operation[1] = HAL_FLASH_NO_OPERATION;
  hflash->global_state = HAL_FLASH_STATE_IDLE;
  hflash->bank_state[0] = HAL_FLASH_BANK_STATE_IDLE;
  hflash->bank_state[1] = HAL_FLASH_BANK_STATE_IDLE;
  return HAL_OK;
}

/**
  * @brief  De-initialize the FLASH handle.
  * @param  hflash Pointer to a \ref hal_flash_handle_t structure.
  * @retval None.
  */
void HAL_FLASH_DeInit(hal_flash_handle_t *hflash)
{
  ASSERT_DBG_PARAM(hflash != NULL);
  ASSERT_DBG_PARAM(IS_FLASH_INSTANCE(hflash->instance));

  (void)FLASH_WaitForEndOfOperation(hflash, HAL_FLASH_BANK_1, FLASH_OPERATION_MAX_TIMEOUT);
  (void)FLASH_WaitForEndOfOperation(hflash, HAL_FLASH_BANK_2, FLASH_OPERATION_MAX_TIMEOUT);

  hflash->global_state = HAL_FLASH_STATE_RESET;
  hflash->bank_state[0] = HAL_FLASH_BANK_STATE_RESET;
  hflash->bank_state[1] = HAL_FLASH_BANK_STATE_RESET;
}
/**
  * @}
  */

#if defined (USE_HAL_FLASH_PROGRAM_BY_ADDR) && (USE_HAL_FLASH_PROGRAM_BY_ADDR == 1U)
/** @addtogroup FLASH_Exported_Functions_Group2
  * @{
This subsection provides a set of functions allowing to configure the FLASH peripheral:

- Call the function HAL_FLASH_SetProgrammingMode() to set the programming mode according to selected parameter within
  @ref hal_flash_program_mode_t enumeration.

- Call the function HAL_FLASH_GetProgrammingMode() to get the current configured programming mode.
  */

/**
  * @brief  Set the FLASH programming mode configuration.
  * @param  hflash           Pointer to a \ref hal_flash_handle_t structure.
  * @param  bank             This parameter is one element of \ref hal_flash_bank_t enumeration.
  * @param  programming_mode This parameter is one element of \ref hal_flash_program_mode_t enumeration.
  * @retval HAL_OK           Programming mode is successfully configured.
  */
hal_status_t HAL_FLASH_SetProgrammingMode(hal_flash_handle_t *hflash,
                                          hal_flash_bank_t bank,
                                          hal_flash_program_mode_t programming_mode)
{
  ASSERT_DBG_PARAM(hflash != NULL);
  ASSERT_DBG_PARAM(IS_FLASH_BANK(bank));
  ASSERT_DBG_PARAM(IS_FLASH_PROGRAM_MODE_TYPE(programming_mode));

  ASSERT_DBG_STATE(hflash->global_state, (uint32_t)HAL_FLASH_STATE_IDLE);
  ASSERT_DBG_STATE(hflash->bank_state[FLASH_GET_BANK_INDEX(bank)], (uint32_t)HAL_FLASH_BANK_STATE_IDLE);

  hflash->programming_mode[FLASH_GET_BANK_INDEX(bank)] = programming_mode;

  return HAL_OK;
}

/**
  * @brief  Get the FLASH programming mode configuration.
  * @param  hflash Pointer to a \ref hal_flash_handle_t structure.
  * @param  bank   This parameter is one element of \ref hal_flash_bank_t enumeration.
  * @retval hal_flash_program_mode_t Programming mode value.
  */
hal_flash_program_mode_t HAL_FLASH_GetProgrammingMode(const hal_flash_handle_t *hflash, hal_flash_bank_t bank)
{
  ASSERT_DBG_PARAM(hflash != NULL);
  ASSERT_DBG_PARAM(IS_FLASH_BANK(bank));

  ASSERT_DBG_STATE(hflash->global_state, (uint32_t)HAL_FLASH_STATE_IDLE);
  ASSERT_DBG_STATE(hflash->bank_state[FLASH_GET_BANK_INDEX(bank)], (uint32_t)HAL_FLASH_BANK_STATE_IDLE);

  return (hflash->programming_mode[FLASH_GET_BANK_INDEX(bank)]);
}

/**
  * @}
  */

#endif /* USE_HAL_FLASH_PROGRAM_BY_ADDR */

/** @addtogroup FLASH_Exported_Functions_Group3
  * @{
This subsection provides a set of functions allowing to program and erase the FLASH memory:
- Call the function HAL_FLASH_ProgramByAddr() to program the FLASH memory by address in polling mode.
- Call the function HAL_FLASH_ProgramByAddr_IT() to program the FLASH memory by address in interrupt mode.
- Call the function HAL_FLASH_OTP_ProgramByAddr() to program the OTP area by address in polling mode.
- Call the function HAL_FLASH_OTP_ProgramByAddr_IT() to program the OTP area by address in interrupt mode.
- Call the function HAL_FLASH_EraseByAddr() to erase the FLASH memory by address in polling mode.
- Call the function HAL_FLASH_EraseByAddr_IT() to erase the FLASH memory by address in interrupt mode.
- Call the function HAL_FLASH_ErasePage() to erase the FLASH memory by page in polling mode.
- Call the function HAL_FLASH_ErasePage_IT() to erase the FLASH memory by page in interrupt mode.
- Call the function HAL_FLASH_EraseBank() to erase the FLASH memory by bank in polling mode.
- Call the function HAL_FLASH_EraseBank_IT() to erase the FLASH memory by bank in interrupt mode.
- Call the function HAL_FLASH_MassErase() to mass erase the complete FLASH memoryin polling mode.
- Call the function HAL_FLASH_MassErase_IT() to mass erase the complete FLASH memory in interrupt mode.
- Call the function HAL_FLASH_IRQHandler() to handle any enabled interrupt and call its corresponding callback.
- Call the function HAL_FLASH_ProgramByAddr_IRQHandler() to handle any enabled interrupt and call its corresponding
  callback.
- Call the function HAL_FLASH_EraseByAddr_IRQHandler() to handle any enabled interrupt and call its corresponding
  callback.
- Call the function HAL_FLASH_ErasePage_IRQHandler() to handle any enabled interrupt and call its corresponding
  callback.
- Call the function HAL_FLASH_EraseBank_IRQHandler() to handle any enabled interrupt and call its corresponding
  callback.
- Call the function HAL_FLASH_MassErase_IRQHandler() to handle any enabled interrupt and call its corresponding
  callback.
  */

#if defined (USE_HAL_FLASH_PROGRAM_BY_ADDR) && (USE_HAL_FLASH_PROGRAM_BY_ADDR == 1U)
/**
  * @brief  Program the FLASH memory at specified user address in polling mode.
  * @param  hflash            Pointer to a \ref hal_flash_handle_t structure.
  * @param  flash_addr        Start address of flash to be programmed.
  * @param  p_data            Pointer to the data to be programmed.
  * @param  size_byte         Size of the data to be programmed (in bytes).
  * @param  timeout_msec      Timeout value for programming.
  * @retval HAL_INVALID_PARAM Returned when an invalid input parameter selected.
  * @retval HAL_ERROR         Returned when the FLASH access registers locked.
  * @retval HAL_TIMEOUT       Internal processing exceeded the timeout.
  * @retval HAL_OK            Returned when the programming operation complete successfully.
  */
hal_status_t HAL_FLASH_ProgramByAddr(hal_flash_handle_t *hflash,
                                     uint32_t flash_addr,
                                     const uint32_t *p_data,
                                     uint32_t size_byte,
                                     uint32_t timeout_msec)
{
  ASSERT_DBG_PARAM(hflash != NULL);
  ASSERT_DBG_PARAM(p_data != NULL);
  ASSERT_DBG_PARAM(FLASH_IsFlashUSERAddress(hflash, flash_addr, 1U) != 0U);
  ASSERT_DBG_PARAM(FLASH_IsFlashUSERAddress(hflash, flash_addr + size_byte - 1U, 0U) != 0U);
  ASSERT_DBG_PARAM(IS_FLASH_USER_PROGRAM_SIZE(size_byte));
  ASSERT_DBG_PARAM(IS_FLASH_NO_USER_CROSS_BANK(flash_addr, size_byte));
  ASSERT_DBG_PARAM(IS_FLASH_PROGRAM_MODE_TYPE(hflash->programming_mode[FLASH_GET_BANK_INDEX(FLASH_GetBank(hflash, \
                                                                       flash_addr))]));

  ASSERT_DBG_STATE(hflash->global_state, (uint32_t)HAL_FLASH_STATE_IDLE);
  ASSERT_DBG_STATE(hflash->bank_state[FLASH_GET_BANK_INDEX(FLASH_GetBank(hflash, flash_addr))], \
                   (uint32_t)HAL_FLASH_BANK_STATE_IDLE);

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (p_data == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  return FLASH_Program(hflash, flash_addr, p_data, size_byte, 0U, timeout_msec);
}

/**
  * @brief  Program the FLASH memory at specified address in interrupt mode.
  * @param  hflash            Pointer to a \ref hal_flash_handle_t structure.
  * @param  flash_addr        Start address of flash to be programmed.
  * @param  p_data            Pointer to the data to be programmed.
  * @param  size_byte         Size of the data to be programmed (in bytes).
  * @retval HAL_INVALID_PARAM Returned when an invalid input parameter selected.
  * @retval HAL_ERROR         Returned when the FLASH access registers locked.
  * @retval HAL_OK            Returned when the programming operation complete successfully.
  */
hal_status_t HAL_FLASH_ProgramByAddr_IT(hal_flash_handle_t *hflash,
                                        uint32_t flash_addr,
                                        const uint32_t *p_data,
                                        uint32_t size_byte)
{
  ASSERT_DBG_PARAM(hflash != NULL);
  ASSERT_DBG_PARAM(p_data != NULL);
  ASSERT_DBG_PARAM(FLASH_IsFlashUSERAddress(hflash, flash_addr, 1U) != 0U);
  ASSERT_DBG_PARAM(FLASH_IsFlashUSERAddress(hflash, flash_addr + size_byte - 1U, 0U) != 0U);
  ASSERT_DBG_PARAM(IS_FLASH_USER_PROGRAM_SIZE(size_byte));
  ASSERT_DBG_PARAM(IS_FLASH_NO_USER_CROSS_BANK(flash_addr, size_byte));
  ASSERT_DBG_PARAM(IS_FLASH_PROGRAM_MODE_TYPE(hflash->programming_mode[FLASH_GET_BANK_INDEX(FLASH_GetBank(hflash,
                                                                       flash_addr))]));

  ASSERT_DBG_STATE(hflash->global_state, (uint32_t)HAL_FLASH_STATE_IDLE);
  ASSERT_DBG_STATE(hflash->bank_state[FLASH_GET_BANK_INDEX(FLASH_GetBank(hflash, flash_addr))],
                   (uint32_t)HAL_FLASH_BANK_STATE_IDLE);

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (p_data == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  return FLASH_Program_IT(hflash, flash_addr, p_data, size_byte, 0U);
}

/**
  * @brief  Program the FLASH memory at specified user address using adaptive width in polling mode.
  * @param  hflash            Pointer to a \ref hal_flash_handle_t structure.
  * @param  flash_addr        Start address of flash to be programmed.
  * @param  p_data            Pointer to the data to be programmed.
  * @param  size_byte         Size of the data to be programmed (in bytes).
  * @param  timeout_msec      Timeout value for programming.
  * @retval HAL_INVALID_PARAM Returned when an invalid input parameter selected.
  * @retval HAL_ERROR         Returned when the FLASH access registers locked.
  * @retval HAL_TIMEOUT       Internal processing exceeded the timeout.
  * @retval HAL_OK            Returned when the programming operation complete successfully.
  */
hal_status_t HAL_FLASH_ProgramByAddrAdapt(hal_flash_handle_t *hflash,
                                          uint32_t flash_addr,
                                          const uint32_t *p_data,
                                          uint32_t size_byte,
                                          uint32_t timeout_msec)
{
  ASSERT_DBG_PARAM(hflash != NULL);
  ASSERT_DBG_PARAM(p_data != NULL);
  ASSERT_DBG_PARAM(FLASH_IsFlashUSERAddress(hflash, flash_addr, 1U) != 0U);
  ASSERT_DBG_PARAM(FLASH_IsFlashUSERAddress(hflash, flash_addr + size_byte - 1U, 0U) != 0U);
  ASSERT_DBG_PARAM(IS_FLASH_USER_PROGRAM_SIZE(size_byte));
  ASSERT_DBG_PARAM(IS_FLASH_NO_USER_CROSS_BANK(flash_addr, size_byte));
  ASSERT_DBG_STATE(hflash->global_state, (uint32_t)HAL_FLASH_STATE_IDLE);

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (p_data == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  return FLASH_Program(hflash, flash_addr, p_data, size_byte, 1U, timeout_msec);
}

/**
  * @brief  Program the FLASH memory at specified address using adaptive width in interrupt mode.
  * @param  hflash            Pointer to a \ref hal_flash_handle_t structure.
  * @param  flash_addr        Start address of flash to be programmed.
  * @param  p_data            Pointer to the data to be programmed.
  * @param  size_byte         Size of the data to be programmed (in bytes).
  * @retval HAL_INVALID_PARAM Returned when an invalid input parameter selected.
  * @retval HAL_ERROR         Returned when the FLASH access registers locked.
  * @retval HAL_OK            Returned when the programming operation complete successfully.
  */
hal_status_t HAL_FLASH_ProgramByAddrAdapt_IT(hal_flash_handle_t *hflash,
                                             uint32_t flash_addr,
                                             const uint32_t *p_data,
                                             uint32_t size_byte)
{
  ASSERT_DBG_PARAM(hflash != NULL);
  ASSERT_DBG_PARAM(p_data != NULL);
  ASSERT_DBG_PARAM(FLASH_IsFlashUSERAddress(hflash, flash_addr, 1U) != 0U);
  ASSERT_DBG_PARAM(FLASH_IsFlashUSERAddress(hflash, flash_addr + size_byte - 1U, 0U) != 0U);
  ASSERT_DBG_PARAM(IS_FLASH_USER_PROGRAM_SIZE(size_byte));
  ASSERT_DBG_PARAM(IS_FLASH_NO_USER_CROSS_BANK(flash_addr, size_byte));
  ASSERT_DBG_STATE(hflash->global_state, (uint32_t)HAL_FLASH_STATE_IDLE);

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (p_data == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  return FLASH_Program_IT(hflash, flash_addr, p_data, size_byte, 1U);
}

/**
  * @brief  Program the OTP area at specified address in polling mode.
  * @param  hflash            Pointer to a \ref hal_flash_handle_t structure.
  * @param  otp_addr          OTP address.
  * @param  p_data            Pointer to the data to be programmed.
  * @param  size_byte         Size of the data to be programmed (in bytes).
  * @param  timeout_msec      Timeout value for programming.
  * @retval HAL_INVALID_PARAM Returned when an invalid input parameter selected.
  * @retval HAL_ERROR         Returned when the FLASH access registers locked or when the TrustZone enabled.
  * @retval HAL_TIMEOUT       Internal processing exceeded the timeout.
  * @retval HAL_OK            Returned when the programming operation complete successfully.
  */
hal_status_t HAL_FLASH_OTP_ProgramByAddr(hal_flash_handle_t *hflash,
                                         uint32_t otp_addr,
                                         const uint32_t *p_data,
                                         uint32_t size_byte,
                                         uint32_t timeout_msec)
{
  ASSERT_DBG_PARAM(hflash != NULL);
  ASSERT_DBG_PARAM(p_data != NULL);
  ASSERT_DBG_PARAM(IS_FLASH_OTP_ADDRESS(otp_addr));
  ASSERT_DBG_PARAM(IS_FLASH_OTP_SIZE_IN_RANGE(otp_addr, size_byte));
  ASSERT_DBG_PARAM((size_byte % (uint32_t)HAL_FLASH_PROGRAM_HALFWORD) == 0U);

  ASSERT_DBG_STATE(hflash->global_state, (uint32_t)HAL_FLASH_STATE_IDLE);

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (p_data == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  return FLASH_Program(hflash, otp_addr, p_data, size_byte, 0U, timeout_msec);
}

/**
  * @brief  Program the OTP area at specified address in interrupt mode.
  * @param  hflash            Pointer to a \ref hal_flash_handle_t structure.
  * @param  otp_addr          OTP address.
  * @param  p_data            Pointer to the data to be programmed.
  * @param  size_byte         Size of the data to be programmed (in bytes).
  * @retval HAL_INVALID_PARAM Returned when an invalid input parameter selected.
  * @retval HAL_ERROR         Returned when the FLASH access registers locked or when the TrustZone enabled.
  * @retval HAL_OK            Returned when the programming operation complete successfully.
  */
hal_status_t HAL_FLASH_OTP_ProgramByAddr_IT(hal_flash_handle_t *hflash,
                                            uint32_t otp_addr,
                                            const uint32_t *p_data,
                                            uint32_t size_byte)
{
  ASSERT_DBG_PARAM(hflash != NULL);
  ASSERT_DBG_PARAM(p_data != NULL);
  ASSERT_DBG_PARAM(IS_FLASH_OTP_ADDRESS(otp_addr));
  ASSERT_DBG_PARAM(IS_FLASH_OTP_SIZE_IN_RANGE(otp_addr, size_byte));
  ASSERT_DBG_PARAM((size_byte % (uint32_t)HAL_FLASH_PROGRAM_HALFWORD) == 0U);

  ASSERT_DBG_STATE(hflash->global_state, (uint32_t)HAL_FLASH_STATE_IDLE);

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (p_data == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  return FLASH_Program_IT(hflash, otp_addr, p_data, size_byte, 0U);
}

/**
  * @brief  Program the OTP area at specified address using adaptive width in polling mode.
  * @param  hflash            Pointer to a \ref hal_flash_handle_t structure.
  * @param  otp_addr          OTP address.
  * @param  p_data            Pointer to the data to be programmed.
  * @param  size_byte         Size of the data to be programmed (in bytes).
  * @param  timeout_msec      Timeout value for programming.
  * @retval HAL_INVALID_PARAM Returned when an invalid input parameter selected.
  * @retval HAL_ERROR         Returned when the FLASH access registers locked or when the TrustZone enabled.
  * @retval HAL_TIMEOUT       Internal processing exceeded the timeout.
  * @retval HAL_OK            Returned when the programming operation complete successfully.
  */
hal_status_t HAL_FLASH_OTP_ProgramByAddrAdapt(hal_flash_handle_t *hflash,
                                              uint32_t otp_addr,
                                              const uint32_t *p_data,
                                              uint32_t size_byte,
                                              uint32_t timeout_msec)
{
  ASSERT_DBG_PARAM(hflash != NULL);
  ASSERT_DBG_PARAM(p_data != NULL);
  ASSERT_DBG_PARAM(IS_FLASH_OTP_ADDRESS(otp_addr));
  ASSERT_DBG_PARAM(IS_FLASH_OTP_SIZE_IN_RANGE(otp_addr, size_byte));
  ASSERT_DBG_PARAM((size_byte % (uint32_t)HAL_FLASH_PROGRAM_HALFWORD) == 0U);
  ASSERT_DBG_STATE(hflash->global_state, (uint32_t)HAL_FLASH_STATE_IDLE);

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (p_data == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  return FLASH_Program(hflash, otp_addr, p_data, size_byte, 1U, timeout_msec);
}

/**
  * @brief  Program the OTP area at specified address using adaptive width in interrupt mode.
  * @param  hflash            Pointer to a \ref hal_flash_handle_t structure.
  * @param  otp_addr          OTP address.
  * @param  p_data            Pointer to the data to be programmed.
  * @param  size_byte         Size of the data to be programmed (in bytes).
  * @retval HAL_INVALID_PARAM Returned when an invalid input parameter selected.
  * @retval HAL_ERROR         Returned when the FLASH access registers locked or when the TrustZone enabled.
  * @retval HAL_OK            Returned when the programming operation complete successfully.
  */
hal_status_t HAL_FLASH_OTP_ProgramByAddrAdapt_IT(hal_flash_handle_t *hflash,
                                                 uint32_t otp_addr,
                                                 const uint32_t *p_data,
                                                 uint32_t size_byte)
{
  ASSERT_DBG_PARAM(hflash != NULL);
  ASSERT_DBG_PARAM(p_data != NULL);
  ASSERT_DBG_PARAM(IS_FLASH_OTP_ADDRESS(otp_addr));
  ASSERT_DBG_PARAM(IS_FLASH_OTP_SIZE_IN_RANGE(otp_addr, size_byte));
  ASSERT_DBG_PARAM((size_byte % (uint32_t)HAL_FLASH_PROGRAM_HALFWORD) == 0U);
  ASSERT_DBG_STATE(hflash->global_state, (uint32_t)HAL_FLASH_STATE_IDLE);

#if defined(USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (p_data == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  return FLASH_Program_IT(hflash, otp_addr, p_data, size_byte, 1U);
}
#endif /* USE_HAL_FLASH_PROGRAM_BY_ADDR */
#if defined (USE_HAL_FLASH_ERASE_BY_ADDR) && (USE_HAL_FLASH_ERASE_BY_ADDR == 1U)
/**
  * @brief  Erase the FLASH memory at specified address in polling mode.
  * @param  hflash            Pointer to a \ref hal_flash_handle_t structure.
  * @param  flash_addr        Start address of flash page to be erased.
  *                           This parameter must be aligned with the start of a page.
  * @param  size_byte         Size of the area to be erased (in bytes).
  *                           This parameter must be a multiple of the page size.
  * @param  timeout_msec      Timeout value for erasing.
  * @warning Since the smallest erase granularity is at page level, this function will erase a greater area than the one
  *          defined by flash_addr and size_byte if these parameters do not represent an area aligned with the start
  *          and the end of flash pages.
  * @retval HAL_INVALID_PARAM Returned when an invalid input parameter selected.
  * @retval HAL_ERROR         Returned when the FLASH access registers locked.
  * @retval HAL_TIMEOUT       Internal processing exceeded the timeout.
  * @retval HAL_OK            Returned when the erasing operation complete successfully.
  */
hal_status_t HAL_FLASH_EraseByAddr(hal_flash_handle_t *hflash,
                                   uint32_t flash_addr,
                                   uint32_t size_byte,
                                   uint32_t timeout_msec)
{
  ASSERT_DBG_PARAM(hflash != NULL);
  ASSERT_DBG_PARAM(FLASH_IsFlashUSERAddress(hflash, flash_addr, 1U) != 0U);
  ASSERT_DBG_PARAM(FLASH_IsFlashUSERAddress(hflash, flash_addr  + size_byte - 1U, 0U) != 0U);
  ASSERT_DBG_PARAM(IS_FLASH_NO_USER_CROSS_BANK(flash_addr, size_byte));

  ASSERT_DBG_STATE(hflash->global_state, (uint32_t)HAL_FLASH_STATE_IDLE);
  ASSERT_DBG_STATE(hflash->bank_state[FLASH_GET_BANK_INDEX(FLASH_GetBank(hflash, flash_addr))], \
                   (uint32_t)HAL_FLASH_BANK_STATE_IDLE);

  return FLASH_EraseAddr(hflash, flash_addr, size_byte, FLASH_PAGE_SIZE, timeout_msec);
}

/**
  * @brief  Erase the FLASH memory at specified address in interrupt mode.
  * @param  hflash            Pointer to a \ref hal_flash_handle_t structure.
  * @param  flash_addr        Start address of flash page to be erased.
  *                           This parameter must be aligned with the start of a page.
  * @param  size_byte         Size of the data to be erased (in bytes).
  *                           This parameter must be a multiple of the page size.
  * @warning Since the smallest erase granularity is at page level, this function will erase a greater area than the one
  *          defined by flash_addr and size_byte if these parameters do not represent an area aligned with the start
  *          and the end of flash pages.
  * @retval HAL_INVALID_PARAM Returned when an invalid input parameter selected.
  * @retval HAL_ERROR         Returned when the FLASH access registers locked.
  * @retval HAL_OK            Returned when the erasing operation complete successfully.
  */
hal_status_t HAL_FLASH_EraseByAddr_IT(hal_flash_handle_t *hflash,
                                      uint32_t flash_addr,
                                      uint32_t size_byte)
{
  ASSERT_DBG_PARAM(hflash != NULL);
  ASSERT_DBG_PARAM(FLASH_IsFlashUSERAddress(hflash, flash_addr, 1U) != 0U);
  ASSERT_DBG_PARAM(FLASH_IsFlashUSERAddress(hflash, flash_addr  + size_byte - 1U, 0U) != 0U);
  ASSERT_DBG_PARAM(IS_FLASH_NO_USER_CROSS_BANK(flash_addr, size_byte));

  ASSERT_DBG_STATE(hflash->global_state, (uint32_t)HAL_FLASH_STATE_IDLE);
  ASSERT_DBG_STATE(hflash->bank_state[FLASH_GET_BANK_INDEX(FLASH_GetBank(hflash, flash_addr))], \
                   (uint32_t)HAL_FLASH_BANK_STATE_IDLE);

  return FLASH_EraseAddr_IT(hflash, flash_addr, size_byte, FLASH_PAGE_SIZE);
}
#endif /* USE_HAL_FLASH_ERASE_BY_ADDR */
#if defined (USE_HAL_FLASH_ERASE_PAGE) && (USE_HAL_FLASH_ERASE_PAGE == 1U)
/**
  * @brief  Erase the FLASH memory by page in polling mode.
  * @param  hflash            Pointer to a \ref hal_flash_handle_t structure.
  * @param  bank              This parameter is one element of \ref hal_flash_bank_t enumeration.
  * @param  page            First page to be erased.
  * @param  page_nbr        Number of pages to be erased.
  * @param  timeout_msec      Timeout value for page erasing.
  * @retval HAL_INVALID_PARAM Returned when an invalid input parameter selected.
  * @retval HAL_ERROR         Returned when the FLASH access registers locked.
  * @retval HAL_TIMEOUT       Internal processing exceeded the timeout.
  * @retval HAL_OK            Returned when the erasing operation complete successfully.
  */
hal_status_t HAL_FLASH_ErasePage(hal_flash_handle_t *hflash,
                                 hal_flash_bank_t bank,
                                 uint32_t page,
                                 uint32_t page_nbr,
                                 uint32_t timeout_msec)
{
  ASSERT_DBG_PARAM(hflash != NULL);
  ASSERT_DBG_PARAM(IS_FLASH_BANK(bank));
  ASSERT_DBG_PARAM(IS_FLASH_PAGE_IN_RANGE(page, page_nbr));

  ASSERT_DBG_STATE(hflash->global_state, (uint32_t)HAL_FLASH_STATE_IDLE);
  ASSERT_DBG_STATE(hflash->bank_state[FLASH_GET_BANK_INDEX(bank)], (uint32_t)HAL_FLASH_BANK_STATE_IDLE);

  return FLASH_ErasePage(hflash, bank, page, page_nbr, timeout_msec);
}

/**
  * @brief  Erase the FLASH memory by page in interrupt mode.
  * @param  hflash            Pointer to a \ref hal_flash_handle_t structure.
  * @param  bank              This parameter is one element of \ref hal_flash_bank_t enumeration.
  * @param  page              First page to be erased.
  * @param  page_nbr          Number of pages to be erased.
  * @retval HAL_INVALID_PARAM Returned when an invalid input parameter selected.
  * @retval HAL_ERROR         Returned when the FLASH access registers locked.
  * @retval HAL_OK            Returned when the erasing operation complete successfully.
  */
hal_status_t HAL_FLASH_ErasePage_IT(hal_flash_handle_t *hflash,
                                    hal_flash_bank_t bank,
                                    uint32_t page,
                                    uint32_t page_nbr)
{
  ASSERT_DBG_PARAM(hflash != NULL);
  ASSERT_DBG_PARAM(IS_FLASH_BANK(bank));
  ASSERT_DBG_PARAM(IS_FLASH_PAGE_IN_RANGE(page, page_nbr));

  ASSERT_DBG_STATE(hflash->global_state, (uint32_t)HAL_FLASH_STATE_IDLE);
  ASSERT_DBG_STATE(hflash->bank_state[FLASH_GET_BANK_INDEX(bank)], (uint32_t)HAL_FLASH_BANK_STATE_IDLE);

  return FLASH_ErasePage_IT(hflash, bank, page, page_nbr);
}
#endif /* USE_HAL_FLASH_ERASE_PAGE */
#if defined (USE_HAL_FLASH_ERASE_BANK) && (USE_HAL_FLASH_ERASE_BANK == 1U)
/**
  * @brief  Erase the FLASH_GET_INSTANCE(hflash) memory by bank in polling mode.
  * @param  hflash            Pointer to a \ref hal_flash_handle_t structure.
  * @param  bank              Bank to be erased.
  * @param  timeout_msec      Timeout value for bank erasing.
  * @retval HAL_INVALID_PARAM Returned when an invalid input parameter selected.
  * @retval HAL_ERROR         Returned when the FLASH access registers locked.
  * @retval HAL_TIMEOUT       Internal processing exceeded the timeout.
  * @retval HAL_OK            Returned when the erasing operation complete successfully.
  */
hal_status_t HAL_FLASH_EraseBank(hal_flash_handle_t *hflash, hal_flash_bank_t bank, uint32_t timeout_msec)
{
  hal_status_t status;
  uint32_t     error_code;
  uint32_t     bank_idx;

  ASSERT_DBG_PARAM(hflash != NULL);
  ASSERT_DBG_PARAM(IS_FLASH_BANK(bank));

  bank_idx = FLASH_GET_BANK_INDEX(bank);

  ASSERT_DBG_STATE(hflash->global_state, (uint32_t)HAL_FLASH_STATE_IDLE);
  ASSERT_DBG_STATE(hflash->bank_state[bank_idx], (uint32_t)HAL_FLASH_BANK_STATE_IDLE);

  if (LL_FLASH_IsLocked(FLASH_GET_INSTANCE(hflash), (uint32_t)bank) != 0U)
  {
    return HAL_ERROR;
  }

  HAL_CHECK_UPDATE_STATE(hflash, bank_state[bank_idx], HAL_FLASH_BANK_STATE_IDLE, HAL_FLASH_BANK_STATE_ACTIVE);

  status = FLASH_WaitForEndOfOperation(hflash, bank, timeout_msec);

  if (status == HAL_OK)
  {
#if defined (USE_HAL_FLASH_GET_LAST_ERRORS) && (USE_HAL_FLASH_GET_LAST_ERRORS == 1)
    hflash->last_error_codes[bank_idx] = HAL_FLASH_ERROR_NONE;
#endif /* USE_HAL_FLASH_GET_LAST_ERRORS */

    LL_FLASH_ClearFlag(FLASH_GET_INSTANCE(hflash), (uint32_t)bank, LL_FLASH_FLAG_ERRORS_ALL);

    /* Fill the operation information structure */
    hflash->ongoing_operation[bank_idx]  = HAL_FLASH_BANK_ERASE;

    FLASH_BankErase(hflash, bank);

    status = FLASH_WaitForEndOfOperation(hflash, bank, timeout_msec);

    error_code = LL_FLASH_ReadFlag(FLASH_GET_INSTANCE(hflash), (uint32_t)bank, LL_FLASH_FLAG_ERRORS_ALL);

    if (error_code != 0U)
    {
#if defined(USE_HAL_FLASH_GET_LAST_ERRORS) && (USE_HAL_FLASH_GET_LAST_ERRORS == 1)
      FLASH_FillErrorCode(hflash, bank, error_code);
#endif /* USE_HAL_FLASH_GET_LAST_ERRORS */

      LL_FLASH_ClearFlag(FLASH_GET_INSTANCE(hflash), (uint32_t)bank, LL_FLASH_FLAG_ERRORS_ALL);

      status = HAL_ERROR;
    }
  }

  LL_FLASH_ClearFlag_EOPF(FLASH_GET_INSTANCE(hflash), (uint32_t)bank);
  LL_FLASH_DisableBankErase(FLASH_GET_INSTANCE(hflash), (uint32_t)bank);

  hflash->ongoing_operation[bank_idx] = HAL_FLASH_NO_OPERATION;
  hflash->global_state = HAL_FLASH_STATE_IDLE;
  hflash->bank_state[bank_idx] = HAL_FLASH_BANK_STATE_IDLE;

  return status;
}

/**
  * @brief  Erase the FLASH memory by bank in interrupt mode.
  * @param  hflash            Pointer to a \ref hal_flash_handle_t structure.
  * @param  bank              Bank to be erased.
  * @retval HAL_INVALID_PARAM Returned when an invalid input parameter selected.
  * @retval HAL_ERROR         Returned when the FLASH access registers locked.
  * @retval HAL_OK            Returned when the erasing operation complete successfully.
  */
hal_status_t HAL_FLASH_EraseBank_IT(hal_flash_handle_t *hflash, hal_flash_bank_t bank)
{
  ASSERT_DBG_PARAM(hflash != NULL);
  ASSERT_DBG_PARAM(IS_FLASH_BANK(bank));

  uint32_t bank_idx = FLASH_GET_BANK_INDEX(bank);

  ASSERT_DBG_STATE(hflash->global_state, (uint32_t)HAL_FLASH_STATE_IDLE);
  ASSERT_DBG_STATE(hflash->bank_state[bank_idx], (uint32_t)HAL_FLASH_BANK_STATE_IDLE);

  if (LL_FLASH_IsLocked(FLASH_GET_INSTANCE(hflash), (uint32_t)bank) != 0U)
  {
    return HAL_ERROR;
  }

  HAL_CHECK_UPDATE_STATE(hflash, bank_state[bank_idx], HAL_FLASH_BANK_STATE_IDLE, HAL_FLASH_BANK_STATE_ACTIVE);

  if (FLASH_WaitForEndOfOperation(hflash, bank, FLASH_OPERATION_MAX_TIMEOUT) == HAL_OK)
  {
#if defined (USE_HAL_FLASH_GET_LAST_ERRORS) && (USE_HAL_FLASH_GET_LAST_ERRORS == 1)
    hflash->last_error_codes[bank_idx] = HAL_FLASH_ERROR_NONE;
#endif /* USE_HAL_FLASH_GET_LAST_ERRORS */

    /* Fill the operation information structure */
    hflash->ongoing_operation[bank_idx]  = HAL_FLASH_BANK_ERASE;

    LL_FLASH_EnableIT(FLASH_GET_INSTANCE(hflash), (uint32_t)bank, LL_FLASH_IT_ALL);
    FLASH_BankErase(hflash, bank);
    return HAL_OK;
  }
  else
  {
    hflash->global_state = HAL_FLASH_STATE_IDLE;
    hflash->bank_state[bank_idx] = HAL_FLASH_BANK_STATE_IDLE;
    return HAL_ERROR;
  }
}
#endif /* USE_HAL_FLASH_ERASE_BANK */
#if defined (USE_HAL_FLASH_MASS_ERASE) && (USE_HAL_FLASH_MASS_ERASE == 1U)
/**
  * @brief  Mass erase the FLASH memory in polling mode.
  * @param  hflash            Pointer to a \ref hal_flash_handle_t structure.
  * @param  timeout_msec      Timeout value for mass erasing.
  * @retval HAL_INVALID_PARAM Returned when an invalid input parameter selected.
  * @retval HAL_ERROR         Returned when the FLASH access registers locked.
  * @retval HAL_TIMEOUT       Internal processing exceeded the timeout.
  * @retval HAL_OK            Returned when the erasing operation complete successfully.
  */
hal_status_t HAL_FLASH_MassErase(hal_flash_handle_t *hflash, uint32_t timeout_msec)
{
  hal_status_t     status = HAL_OK;
  uint32_t         error_code;
  uint32_t         bank_idx;
  hal_flash_bank_t bank;

  ASSERT_DBG_PARAM(hflash != NULL);

  ASSERT_DBG_STATE(hflash->global_state, (uint32_t)HAL_FLASH_STATE_IDLE);
  ASSERT_DBG_STATE(hflash->bank_state[0], (uint32_t)HAL_FLASH_BANK_STATE_IDLE);
  ASSERT_DBG_STATE(hflash->bank_state[1], (uint32_t)HAL_FLASH_BANK_STATE_IDLE);

  for (bank_idx = 0U; bank_idx <= 1U; bank_idx ++)
  {
    bank = FLASH_GET_BANK(bank_idx);

    if (LL_FLASH_IsLocked(FLASH_GET_INSTANCE(hflash), (uint32_t)bank) != 0U)
    {
      return HAL_ERROR;
    }

    HAL_CHECK_UPDATE_STATE(hflash, bank_state[bank_idx], HAL_FLASH_BANK_STATE_IDLE, HAL_FLASH_BANK_STATE_ACTIVE);

    status = FLASH_WaitForEndOfOperation(hflash, bank, timeout_msec);

    if (status == HAL_OK)
    {
#if defined (USE_HAL_FLASH_GET_LAST_ERRORS) && (USE_HAL_FLASH_GET_LAST_ERRORS == 1)
      hflash->last_error_codes[bank_idx] = HAL_FLASH_ERROR_NONE;
#endif /* USE_HAL_FLASH_GET_LAST_ERRORS */

      LL_FLASH_ClearFlag(FLASH_GET_INSTANCE(hflash), (uint32_t)bank, LL_FLASH_FLAG_ERRORS_ALL);

      /* Fill the operation information structure */
      hflash->ongoing_operation[bank_idx]  = HAL_FLASH_MASS_ERASE;
    }
  }

  LL_FLASH_EnableBankErase(FLASH_GET_INSTANCE(hflash), LL_FLASH_BANK_1);
  LL_FLASH_EnableBankErase(FLASH_GET_INSTANCE(hflash), LL_FLASH_BANK_2);

  LL_FLASH_StartEraseOperation(FLASH_GET_INSTANCE(hflash), LL_FLASH_BANK_1);
  LL_FLASH_StartEraseOperation(FLASH_GET_INSTANCE(hflash), LL_FLASH_BANK_2);

  for (bank_idx = 0U; bank_idx <= 1U; bank_idx ++)
  {
    bank = FLASH_GET_BANK(bank_idx);

    status = FLASH_WaitForEndOfOperation(hflash, bank, timeout_msec);

    error_code = LL_FLASH_ReadFlag(FLASH_GET_INSTANCE(hflash), (uint32_t)bank, LL_FLASH_FLAG_ERRORS_ALL);

    if (error_code != 0U)
    {
#if defined(USE_HAL_FLASH_GET_LAST_ERRORS) && (USE_HAL_FLASH_GET_LAST_ERRORS == 1)
      FLASH_FillErrorCode(hflash, bank, error_code);
#endif /* USE_HAL_FLASH_GET_LAST_ERRORS */

      LL_FLASH_ClearFlag(FLASH_GET_INSTANCE(hflash), (uint32_t)bank, LL_FLASH_FLAG_ERRORS_ALL);

      status = HAL_ERROR;
    }
    LL_FLASH_ClearFlag_EOPF(FLASH_GET_INSTANCE(hflash), (uint32_t)bank);
    LL_FLASH_DisableBankErase(FLASH_GET_INSTANCE(hflash), (uint32_t)bank);
  }

  hflash->ongoing_operation[0] = HAL_FLASH_NO_OPERATION;
  hflash->ongoing_operation[1] = HAL_FLASH_NO_OPERATION;
  hflash->global_state = HAL_FLASH_STATE_IDLE;
  hflash->bank_state[0] = HAL_FLASH_BANK_STATE_IDLE;
  hflash->bank_state[1] = HAL_FLASH_BANK_STATE_IDLE;

  return status;
}

/**
  * @brief  Mass erase the FLASH memory in interrupt mode.
  * @param  hflash            Pointer to a \ref hal_flash_handle_t structure.
  * @retval HAL_INVALID_PARAM Returned when an invalid input parameter selected.
  * @retval HAL_ERROR         Returned when the FLASH access registers locked.
  * @retval HAL_OK            Returned when the erasing operation complete successfully.
  */
hal_status_t HAL_FLASH_MassErase_IT(hal_flash_handle_t *hflash)
{
  uint32_t bank_idx;
  hal_flash_bank_t bank;

  ASSERT_DBG_PARAM(hflash != NULL);

  ASSERT_DBG_STATE(hflash->global_state, (uint32_t)HAL_FLASH_STATE_IDLE);
  ASSERT_DBG_STATE(hflash->bank_state[0], (uint32_t)HAL_FLASH_BANK_STATE_IDLE);
  ASSERT_DBG_STATE(hflash->bank_state[1], (uint32_t)HAL_FLASH_BANK_STATE_IDLE);

  for (bank_idx = 0U; bank_idx <= 1U; bank_idx ++)
  {
    bank = FLASH_GET_BANK(bank_idx);

    if (LL_FLASH_IsLocked(FLASH_GET_INSTANCE(hflash), (uint32_t)bank) != 0U)
    {
      return HAL_ERROR;
    }

    HAL_CHECK_UPDATE_STATE(hflash, bank_state[bank_idx], HAL_FLASH_BANK_STATE_IDLE, HAL_FLASH_BANK_STATE_ACTIVE);

    if (FLASH_WaitForEndOfOperation(hflash, bank, FLASH_OPERATION_MAX_TIMEOUT) == HAL_OK)
    {
#if defined (USE_HAL_FLASH_GET_LAST_ERRORS) && (USE_HAL_FLASH_GET_LAST_ERRORS == 1)
      hflash->last_error_codes[bank_idx] = HAL_FLASH_ERROR_NONE;
#endif /* USE_HAL_FLASH_GET_LAST_ERRORS */

      /* Fill the operation information structure */
      hflash->ongoing_operation[bank_idx]  = HAL_FLASH_MASS_ERASE;

      LL_FLASH_EnableIT(FLASH_GET_INSTANCE(hflash), (uint32_t)bank, LL_FLASH_IT_ALL);
    }
    else
    {
      hflash->global_state = HAL_FLASH_STATE_IDLE;
      hflash->bank_state[bank_idx] = HAL_FLASH_BANK_STATE_IDLE;
      return HAL_ERROR;
    }
  }

  LL_FLASH_EnableBankErase(FLASH_GET_INSTANCE(hflash), LL_FLASH_BANK_1);
  LL_FLASH_EnableBankErase(FLASH_GET_INSTANCE(hflash), LL_FLASH_BANK_2);

  LL_FLASH_StartEraseOperation(FLASH_GET_INSTANCE(hflash), LL_FLASH_BANK_1);
  LL_FLASH_StartEraseOperation(FLASH_GET_INSTANCE(hflash), LL_FLASH_BANK_2);

  return HAL_OK;
}
#endif /* USE_HAL_FLASH_MASS_ERASE */
#if defined (USE_HAL_FLASH_COMPUTE_CRC) && (USE_HAL_FLASH_COMPUTE_CRC == 1U)
/**
  * @brief  Set the FLASH CRC Burst size.
  * @param  hflash     Pointer to a \ref hal_flash_handle_t structure.
  * @param  burst_size This parameter is one element of \ref hal_flash_crc_burst_size_t enumeration.
  * @retval HAL_OK     CRC burst size is successfully configured.
  */
hal_status_t HAL_FLASH_SetCRCBurstSize(hal_flash_handle_t *hflash, hal_flash_crc_burst_size_t burst_size)
{
  ASSERT_DBG_PARAM(hflash != NULL);
  ASSERT_DBG_PARAM(IS_FLASH_CRC_BURST_SIZE(burst_size));

  hflash->crc_burst_size = burst_size;

  return HAL_OK;
}

/**
  * @brief  Get the FLASH CRC Burst size.
  * @param  hflash     Pointer to a \ref hal_flash_handle_t structure.
  * @param  burst_size This parameter is one element of \ref hal_flash_crc_burst_size_t enumeration.
  * @retval HAL_OK            Returned when the erasing operation complete successfully.
  */
hal_flash_crc_burst_size_t HAL_FLASH_GetCRCBurstSize(const hal_flash_handle_t *hflash)
{
  ASSERT_DBG_PARAM(hflash != NULL);

  return hflash->crc_burst_size;
}

/**
  * @brief  Perform CRC computation on an address range in polling mode.
  * @param  hflash            Pointer to a \ref hal_flash_handle_t structure.
  * @param  bank              This parameter is one element of \ref hal_flash_bank_t enumeration.
  * @param  burst_size        This parameter is one element of \ref hal_flash_crc_burst_size_t enumeration.
  * @param  start_addr        Start address of the CRC computation area.
  * @param  end_addr          End address of the CRC computation area.
  * @param  timeout_msec      Timeout value for page erasing.
  * @retval HAL_INVALID_PARAM Returned when an invalid input parameter selected.
  * @retval HAL_ERROR         Returned when the FLASH access registers locked.
  * @retval HAL_TIMEOUT       Internal processing exceeded the timeout.
  * @retval HAL_OK            Returned when the erasing operation complete successfully.
  */
hal_status_t HAL_FLASH_CalculateCRCByAddr(hal_flash_handle_t *hflash,
                                          uint32_t start_addr,
                                          uint32_t size_byte,
                                          uint32_t *p_result,
                                          uint32_t timeout_msec)
{
  hal_status_t     status;
  uint32_t         tickstart;
  uint32_t         bank_idx;
  hal_flash_bank_t bank;

  ASSERT_DBG_PARAM(hflash != NULL);
  ASSERT_DBG_PARAM(p_result != NULL);
  ASSERT_DBG_PARAM(FLASH_IsFlashUSERAddress(hflash, start_addr, 1U) != 0U);
  ASSERT_DBG_PARAM(FLASH_IsFlashUSERAddress(hflash, start_addr + size_byte - 1U, 0U) != 0U);
  ASSERT_DBG_PARAM(IS_FLASH_NO_USER_CROSS_BANK(start_addr, size_byte));
  ASSERT_DBG_PARAM(IS_FLASH_CRC_BURST_SIZE(hflash->crc_burst_size));

  bank_idx = FLASH_GET_BANK_INDEX(FLASH_GetBank(hflash, start_addr));
  bank = FLASH_GetBank(hflash, start_addr);

  ASSERT_DBG_PARAM(hflash->ongoing_operation[bank_idx ^ 1U] != HAL_FLASH_COMPUTE_CRC);

  ASSERT_DBG_STATE(hflash->global_state, (uint32_t)HAL_FLASH_STATE_IDLE);
  ASSERT_DBG_STATE(hflash->bank_state[bank_idx], (uint32_t)HAL_FLASH_BANK_STATE_IDLE);

  if (LL_FLASH_IsLocked(FLASH_GET_INSTANCE(hflash), (uint32_t)bank) != 0U)
  {
    return HAL_ERROR;
  }

  HAL_CHECK_UPDATE_STATE(hflash, bank_state[bank_idx], HAL_FLASH_BANK_STATE_IDLE, HAL_FLASH_BANK_STATE_ACTIVE);

  status = FLASH_WaitForEndOfOperation(hflash, bank, FLASH_OPERATION_MAX_TIMEOUT);

  if (status == HAL_OK)
  {
    hflash->bank_state[bank_idx] = HAL_FLASH_BANK_STATE_ACTIVE;
    hflash->ongoing_operation[bank_idx] = HAL_FLASH_COMPUTE_CRC;

    LL_FLASH_EnableCRC(FLASH_GET_INSTANCE(hflash), (uint32_t)bank);

    LL_FLASH_SetCRCBurstSize(FLASH_GET_INSTANCE(hflash), (uint32_t)bank, (uint32_t)hflash->crc_burst_size);

    LL_FLASH_DisableCRCByPage(FLASH_GET_INSTANCE(hflash), (uint32_t)bank);
    LL_FLASH_SetCRCStartAddr(FLASH_GET_INSTANCE(hflash), (uint32_t)bank, start_addr);
    LL_FLASH_SetCRCEndAddr(FLASH_GET_INSTANCE(hflash), (uint32_t)bank, start_addr + size_byte);

    LL_FLASH_StartCRCComputation(FLASH_GET_INSTANCE(hflash), (uint32_t)bank);

    tickstart = HAL_GetTick();

    while (LL_FLASH_IsActiveFlag_CRC_BUSY(FLASH_GET_INSTANCE(hflash), (uint32_t)bank) == 1U)
    {
      if ((HAL_GetTick() - tickstart) > timeout_msec)
      {
        status = HAL_TIMEOUT;
      }
    }

    hflash->global_state = HAL_FLASH_STATE_IDLE;
    hflash->bank_state[bank_idx] = HAL_FLASH_BANK_STATE_IDLE;
    hflash->ongoing_operation[bank_idx] = HAL_FLASH_NO_OPERATION;

    *p_result = LL_FLASH_GetCRCData(FLASH_GET_INSTANCE(hflash));

    LL_FLASH_ClearFlag_CRCENDF(FLASH_GET_INSTANCE(hflash), (uint32_t)bank);
    LL_FLASH_DisableCRC(FLASH_GET_INSTANCE(hflash), (uint32_t)bank);
  }
  else
  {
    hflash->global_state = HAL_FLASH_STATE_IDLE;
    hflash->bank_state[bank_idx] = HAL_FLASH_BANK_STATE_IDLE;
  }

  return status;
}

/**
  * @brief  Perform CRC computation on an address range in interrupt mode.
  * @param  hflash            Pointer to a \ref hal_flash_handle_t structure.
  * @param  bank              This parameter is one element of \ref hal_flash_bank_t enumeration.
  * @param  burst_size        This parameter is one element of \ref hal_flash_crc_burst_size_t enumeration.
  * @param  start_addr        Start address of the CRC computation area.
  * @param  end_addr          End address of the CRC computation area.
  * @retval HAL_INVALID_PARAM Returned when an invalid input parameter selected.
  * @retval HAL_ERROR         Returned when the FLASH access registers locked.
  * @retval HAL_OK            Returned when the erasing operation complete successfully.
  */
hal_status_t HAL_FLASH_CalculateCRCByAddr_IT(hal_flash_handle_t *hflash,
                                             uint32_t start_addr,
                                             uint32_t size_byte,
                                             uint32_t *p_result)
{
  hal_status_t     status;
  uint32_t         bank_idx;
  hal_flash_bank_t bank;

  ASSERT_DBG_PARAM(hflash != NULL);
  ASSERT_DBG_PARAM(p_result != NULL);
  ASSERT_DBG_PARAM(FLASH_IsFlashUSERAddress(hflash, start_addr, 1U) != 0U);
  ASSERT_DBG_PARAM(FLASH_IsFlashUSERAddress(hflash, start_addr + size_byte - 1U, 0U) != 0U);
  ASSERT_DBG_PARAM(IS_FLASH_NO_USER_CROSS_BANK(start_addr, size_byte));
  ASSERT_DBG_PARAM(IS_FLASH_CRC_BURST_SIZE(hflash->crc_burst_size));

  bank_idx = FLASH_GET_BANK_INDEX(FLASH_GetBank(hflash, start_addr));
  bank = FLASH_GetBank(hflash, start_addr);

  ASSERT_DBG_PARAM(hflash->ongoing_operation[bank_idx ^ 1U] != HAL_FLASH_COMPUTE_CRC);

  ASSERT_DBG_STATE(hflash->global_state, (uint32_t)HAL_FLASH_STATE_IDLE);
  ASSERT_DBG_STATE(hflash->bank_state[bank_idx], (uint32_t)HAL_FLASH_BANK_STATE_IDLE);

  if (LL_FLASH_IsLocked(FLASH_GET_INSTANCE(hflash), (uint32_t)bank) != 0U)
  {
    return HAL_ERROR;
  }

  HAL_CHECK_UPDATE_STATE(hflash, bank_state[bank_idx], HAL_FLASH_BANK_STATE_IDLE, HAL_FLASH_BANK_STATE_ACTIVE);

  status = FLASH_WaitForEndOfOperation(hflash, bank, FLASH_OPERATION_MAX_TIMEOUT);

  if (status == HAL_OK)
  {
    hflash->bank_state[bank_idx] = HAL_FLASH_BANK_STATE_ACTIVE;
    hflash->ongoing_operation[bank_idx] = HAL_FLASH_COMPUTE_CRC;
    LL_FLASH_EnableIT(FLASH_GET_INSTANCE(hflash), (uint32_t)bank, LL_FLASH_IT_ALL);

    LL_FLASH_EnableCRC(FLASH_GET_INSTANCE(hflash), (uint32_t)bank);

    LL_FLASH_SetCRCBurstSize(FLASH_GET_INSTANCE(hflash), (uint32_t)bank, (uint32_t)hflash->crc_burst_size);

    LL_FLASH_DisableCRCByPage(FLASH_GET_INSTANCE(hflash), (uint32_t)bank);
    LL_FLASH_SetCRCStartAddr(FLASH_GET_INSTANCE(hflash), (uint32_t)bank, start_addr);
    LL_FLASH_SetCRCEndAddr(FLASH_GET_INSTANCE(hflash), (uint32_t)bank, start_addr + size_byte);

    LL_FLASH_StartCRCComputation(FLASH_GET_INSTANCE(hflash), (uint32_t)bank);
  }
  else
  {
    hflash->global_state = HAL_FLASH_STATE_IDLE;
    hflash->bank_state[bank_idx] = HAL_FLASH_BANK_STATE_IDLE;
  }

  return status;
}

/**
  * @brief  Perform CRC computation on a number of pages in polling mode.
  * @param  hflash            Pointer to a \ref hal_flash_handle_t structure.
  * @param  bank              This parameter is one element of \ref hal_flash_bank_t enumeration.
  * @param  burst_size        This parameter is one element of \ref hal_flash_crc_burst_size_t enumeration.
  * @param  start_page        Start page of the CRC computation area.
  * @param  nb_pages          Number of pages in the CRC computation area.
  * @param  timeout_msec      Timeout value for page erasing.
  * @retval HAL_INVALID_PARAM Returned when an invalid input parameter selected.
  * @retval HAL_ERROR         Returned when the FLASH access registers locked.
  * @retval HAL_TIMEOUT       Internal processing exceeded the timeout.
  * @retval HAL_OK            Returned when the erasing operation complete successfully.
  */
hal_status_t HAL_FLASH_CalculateCRCByPage(hal_flash_handle_t *hflash,
                                          hal_flash_bank_t bank,
                                          uint32_t page,
                                          uint32_t page_nbr,
                                          uint32_t *p_result,
                                          uint32_t timeout_msec)
{
  hal_status_t status;
  uint32_t     tickstart;
  uint32_t     bank_idx;

  ASSERT_DBG_PARAM(hflash != NULL);
  ASSERT_DBG_PARAM(p_result != NULL);
  ASSERT_DBG_PARAM(IS_FLASH_CRC_BURST_SIZE(hflash->crc_burst_size));

  bank_idx = FLASH_GET_BANK_INDEX(bank);

  ASSERT_DBG_PARAM(hflash->ongoing_operation[bank_idx ^ 1U] != HAL_FLASH_COMPUTE_CRC);

  ASSERT_DBG_STATE(hflash->global_state, (uint32_t)HAL_FLASH_STATE_IDLE);
  ASSERT_DBG_STATE(hflash->bank_state[bank_idx], (uint32_t)HAL_FLASH_BANK_STATE_IDLE);

  if (LL_FLASH_IsLocked(FLASH_GET_INSTANCE(hflash), (uint32_t)bank) != 0U)
  {
    return HAL_ERROR;
  }

  HAL_CHECK_UPDATE_STATE(hflash, bank_state[bank_idx], HAL_FLASH_BANK_STATE_IDLE, HAL_FLASH_BANK_STATE_ACTIVE);

  status = FLASH_WaitForEndOfOperation(hflash, bank, FLASH_OPERATION_MAX_TIMEOUT);

  if (status == HAL_OK)
  {
    hflash->bank_state[bank_idx] = HAL_FLASH_BANK_STATE_ACTIVE;
    hflash->ongoing_operation[bank_idx] = HAL_FLASH_COMPUTE_CRC;

    LL_FLASH_EnableCRC(FLASH_GET_INSTANCE(hflash), (uint32_t)bank);
    LL_FLASH_SetCRCBurstSize(FLASH_GET_INSTANCE(hflash), (uint32_t)bank, (uint32_t)hflash->crc_burst_size);
    LL_FLASH_EnableCRCByPage(FLASH_GET_INSTANCE(hflash), (uint32_t)bank);

    for (uint32_t page_idx = page; page_idx < (page + page_nbr); page_idx++)
    {
      LL_FLASH_SetCRCPage(FLASH_GET_INSTANCE(hflash), (uint32_t)bank, page_idx);
      LL_FLASH_AddCRCPageToList(FLASH_GET_INSTANCE(hflash), (uint32_t)bank);
    }

    LL_FLASH_StartCRCComputation(FLASH_GET_INSTANCE(hflash), (uint32_t)bank);

    tickstart = HAL_GetTick();

    while (LL_FLASH_IsActiveFlag_CRC_BUSY(FLASH_GET_INSTANCE(hflash), (uint32_t)bank) == 1U)
    {
      if ((HAL_GetTick() - tickstart) > timeout_msec)
      {
        status = HAL_TIMEOUT;
      }
    }


    *p_result = LL_FLASH_GetCRCData(FLASH_GET_INSTANCE(hflash));

    LL_FLASH_ClearFlag_CRCENDF(FLASH_GET_INSTANCE(hflash), (uint32_t)bank);
    LL_FLASH_DisableCRCByPage(FLASH_GET_INSTANCE(hflash), (uint32_t)bank);
    LL_FLASH_DisableCRC(FLASH_GET_INSTANCE(hflash), (uint32_t)bank);
    hflash->global_state = HAL_FLASH_STATE_IDLE;
    hflash->bank_state[bank_idx] = HAL_FLASH_BANK_STATE_IDLE;
    hflash->ongoing_operation[bank_idx] = HAL_FLASH_NO_OPERATION;

  }
  else
  {
    hflash->global_state = HAL_FLASH_STATE_IDLE;
    hflash->bank_state[bank_idx] = HAL_FLASH_BANK_STATE_IDLE;
  }

  return status;
}

/**
  * @brief  Perform CRC computation on a number of pages in interrupt mode.
  * @param  hflash            Pointer to a \ref hal_flash_handle_t structure.
  * @param  bank              This parameter is one element of \ref hal_flash_bank_t enumeration.
  * @param  burst_size        This parameter is one element of \ref hal_flash_crc_burst_size_t enumeration.
  * @param  start_page        Start page of the CRC computation area.
  * @param  nb_pages          Number of pages in the CRC computation area.
  * @retval HAL_INVALID_PARAM Returned when an invalid input parameter selected.
  * @retval HAL_ERROR         Returned when the FLASH access registers locked.
  * @retval HAL_OK            Returned when the erasing operation complete successfully.
  */
hal_status_t HAL_FLASH_CalculateCRCByPage_IT(hal_flash_handle_t *hflash,
                                             hal_flash_bank_t bank,
                                             uint32_t page,
                                             uint32_t page_nbr,
                                             uint32_t *p_result)
{
  hal_status_t status;
  uint32_t     bank_idx;

  ASSERT_DBG_PARAM(hflash != NULL);
  ASSERT_DBG_PARAM(p_result != NULL);
  ASSERT_DBG_PARAM(IS_FLASH_CRC_BURST_SIZE(hflash->crc_burst_size));

  bank_idx = FLASH_GET_BANK_INDEX(bank);

  ASSERT_DBG_PARAM(hflash->ongoing_operation[bank_idx ^ 1U] != HAL_FLASH_COMPUTE_CRC);

  ASSERT_DBG_STATE(hflash->global_state, (uint32_t)HAL_FLASH_STATE_IDLE);
  ASSERT_DBG_STATE(hflash->bank_state[bank_idx], (uint32_t)HAL_FLASH_BANK_STATE_IDLE);

  if (LL_FLASH_IsLocked(FLASH_GET_INSTANCE(hflash), (uint32_t)bank) != 0U)
  {
    return HAL_ERROR;
  }

  HAL_CHECK_UPDATE_STATE(hflash, bank_state[bank_idx], HAL_FLASH_BANK_STATE_IDLE, HAL_FLASH_BANK_STATE_ACTIVE);

  status = FLASH_WaitForEndOfOperation(hflash, bank, FLASH_OPERATION_MAX_TIMEOUT);

  if (status == HAL_OK)
  {
    hflash->bank_state[bank_idx] = HAL_FLASH_BANK_STATE_ACTIVE;
    hflash->ongoing_operation[bank_idx] = HAL_FLASH_COMPUTE_CRC;
    LL_FLASH_EnableIT(FLASH_GET_INSTANCE(hflash), (uint32_t)bank, LL_FLASH_IT_ALL);

    LL_FLASH_EnableCRC(FLASH_GET_INSTANCE(hflash), (uint32_t)bank);

    LL_FLASH_SetCRCBurstSize(FLASH_GET_INSTANCE(hflash), (uint32_t)bank, (uint32_t)hflash->crc_burst_size);

    LL_FLASH_EnableCRCByPage(FLASH_GET_INSTANCE(hflash), (uint32_t)bank);

    for (uint32_t page_idx = page; page_idx < (page + page_nbr); page_idx++)
    {
      LL_FLASH_SetCRCPage(FLASH_GET_INSTANCE(hflash), (uint32_t)bank, page_idx);
      LL_FLASH_AddCRCPageToList(FLASH_GET_INSTANCE(hflash), (uint32_t)bank);
    }

    LL_FLASH_StartCRCComputation(FLASH_GET_INSTANCE(hflash), (uint32_t)bank);
  }
  else
  {
    hflash->global_state = HAL_FLASH_STATE_IDLE;
    hflash->bank_state[bank_idx] = HAL_FLASH_BANK_STATE_IDLE;
  }

  return status;
}

/**
  * @brief  Perform CRC computation on a bank in polling mode.
  * @param  hflash            Pointer to a \ref hal_flash_handle_t structure.
  * @param  bank              This parameter is one element of \ref hal_flash_bank_t enumeration.
  * @param  burst_size        This parameter is one element of \ref hal_flash_crc_burst_size_t enumeration.
  * @param  timeout_msec      Timeout value for page erasing.
  * @retval HAL_INVALID_PARAM Returned when an invalid input parameter selected.
  * @retval HAL_ERROR         Returned when the FLASH access registers locked.
  * @retval HAL_TIMEOUT       Internal processing exceeded the timeout.
  * @retval HAL_OK            Returned when the erasing operation complete successfully.
  */
hal_status_t HAL_FLASH_CalculateCRCByBank(hal_flash_handle_t *hflash,
                                          hal_flash_bank_t bank,
                                          uint32_t *p_result,
                                          uint32_t timeout_msec)
{
  hal_status_t status;
  uint32_t     bank_idx;
  uint32_t     tickstart;

  ASSERT_DBG_PARAM(hflash != NULL);
  ASSERT_DBG_PARAM(p_result != NULL);
  ASSERT_DBG_PARAM(IS_FLASH_BANK(bank));
  ASSERT_DBG_PARAM(IS_FLASH_CRC_BURST_SIZE(hflash->crc_burst_size));

  bank_idx = FLASH_GET_BANK_INDEX(bank);

  ASSERT_DBG_STATE(hflash->global_state, (uint32_t)HAL_FLASH_STATE_IDLE);
  ASSERT_DBG_STATE(hflash->bank_state[bank_idx], (uint32_t)HAL_FLASH_BANK_STATE_IDLE);

  if (LL_FLASH_IsLocked(FLASH_GET_INSTANCE(hflash), (uint32_t)bank) != 0U)
  {
    return HAL_ERROR;
  }

  HAL_CHECK_UPDATE_STATE(hflash, bank_state[bank_idx], HAL_FLASH_BANK_STATE_IDLE, HAL_FLASH_BANK_STATE_ACTIVE);

  status = FLASH_WaitForEndOfOperation(hflash, bank, FLASH_OPERATION_MAX_TIMEOUT);

  if (status == HAL_OK)
  {
    hflash->ongoing_operation[bank_idx] = HAL_FLASH_COMPUTE_CRC;

    LL_FLASH_EnableCRC(FLASH_GET_INSTANCE(hflash), (uint32_t)bank);

    LL_FLASH_SetCRCBurstSize(FLASH_GET_INSTANCE(hflash), (uint32_t)bank, (uint32_t)hflash->crc_burst_size);

    LL_FLASH_EnableCRCByPage(FLASH_GET_INSTANCE(hflash), (uint32_t)bank);
    LL_FLASH_EnableCRCAllBank(FLASH_GET_INSTANCE(hflash), (uint32_t)bank);

    LL_FLASH_StartCRCComputation(FLASH_GET_INSTANCE(hflash), (uint32_t)bank);

    tickstart = HAL_GetTick();

    while (LL_FLASH_IsActiveFlag_CRC_BUSY(FLASH_GET_INSTANCE(hflash), (uint32_t)bank) == 1U)
    {
      if ((HAL_GetTick() - tickstart) > timeout_msec)
      {
        status = HAL_TIMEOUT;
      }
    }

    hflash->global_state = HAL_FLASH_STATE_IDLE;
    hflash->bank_state[bank_idx] = HAL_FLASH_BANK_STATE_IDLE;
    hflash->ongoing_operation[bank_idx] = HAL_FLASH_NO_OPERATION;

    *p_result = LL_FLASH_GetCRCData(FLASH_GET_INSTANCE(hflash));
    LL_FLASH_ClearFlag_CRCENDF(FLASH_GET_INSTANCE(hflash), (uint32_t)bank);
    LL_FLASH_DisableCRCByPage(FLASH_GET_INSTANCE(hflash), (uint32_t)bank);
    LL_FLASH_DisableCRC(FLASH_GET_INSTANCE(hflash), (uint32_t)bank);
  }
  else
  {
    hflash->global_state = HAL_FLASH_STATE_IDLE;
    hflash->bank_state[bank_idx] = HAL_FLASH_BANK_STATE_IDLE;
  }

  return status;
}

/**
  * @brief  Perform CRC computation on a bank in interrupt mode.
  * @param  hflash            Pointer to a \ref hal_flash_handle_t structure.
  * @param  bank              This parameter is one element of \ref hal_flash_bank_t enumeration.
  * @param  burst_size        This parameter is one element of \ref hal_flash_crc_burst_size_t enumeration.
  * @retval HAL_INVALID_PARAM Returned when an invalid input parameter selected.
  * @retval HAL_ERROR         Returned when the FLASH access registers locked.
  * @retval HAL_OK            Returned when the erasing operation complete successfully.
  */
hal_status_t HAL_FLASH_CalculateCRCByBank_IT(hal_flash_handle_t *hflash,
                                             hal_flash_bank_t bank,
                                             uint32_t *p_result)
{
  hal_status_t status;
  uint32_t     bank_idx;

  ASSERT_DBG_PARAM(hflash != NULL);
  ASSERT_DBG_PARAM(p_result != NULL);
  ASSERT_DBG_PARAM(IS_FLASH_BANK(bank));
  ASSERT_DBG_PARAM(IS_FLASH_CRC_BURST_SIZE(hflash->crc_burst_size));

  bank_idx = FLASH_GET_BANK_INDEX(bank);

  ASSERT_DBG_STATE(hflash->global_state, (uint32_t)HAL_FLASH_STATE_IDLE);
  ASSERT_DBG_STATE(hflash->bank_state[bank_idx], (uint32_t)HAL_FLASH_BANK_STATE_IDLE);

  if (LL_FLASH_IsLocked(FLASH_GET_INSTANCE(hflash), (uint32_t)bank) != 0U)
  {
    return HAL_ERROR;
  }

  HAL_CHECK_UPDATE_STATE(hflash, bank_state[bank_idx], HAL_FLASH_BANK_STATE_IDLE, HAL_FLASH_BANK_STATE_ACTIVE);

  status = FLASH_WaitForEndOfOperation(hflash, bank, FLASH_OPERATION_MAX_TIMEOUT);

  if (status == HAL_OK)
  {
    hflash->bank_state[bank_idx] = HAL_FLASH_BANK_STATE_ACTIVE;
    hflash->ongoing_operation[bank_idx] = HAL_FLASH_COMPUTE_CRC;
    LL_FLASH_EnableIT(FLASH_GET_INSTANCE(hflash), (uint32_t)bank, LL_FLASH_IT_ALL);

    LL_FLASH_EnableCRC(FLASH_GET_INSTANCE(hflash), (uint32_t)bank);

    LL_FLASH_SetCRCBurstSize(FLASH_GET_INSTANCE(hflash), (uint32_t)bank, (uint32_t)hflash->crc_burst_size);

    LL_FLASH_EnableCRCByPage(FLASH_GET_INSTANCE(hflash), (uint32_t)bank);
    LL_FLASH_EnableCRCAllBank(FLASH_GET_INSTANCE(hflash), (uint32_t)bank);

    LL_FLASH_StartCRCComputation(FLASH_GET_INSTANCE(hflash), (uint32_t)bank);
  }
  else
  {
    hflash->global_state = HAL_FLASH_STATE_IDLE;
    hflash->bank_state[bank_idx] = HAL_FLASH_BANK_STATE_IDLE;
  }

  return status;
}
#endif /* USE_HAL_FLASH_COMPUTE_CRC */

/**
  * @brief  Handle the FLASH interrupt request.
  * @param  hflash Pointer to a \ref hal_flash_handle_t structure.
  * @retval None.
  */
void HAL_FLASH_IRQHandler(hal_flash_handle_t *hflash)
{
  uint32_t flags;
  uint32_t its;
#if defined (USE_HAL_FLASH_ERASE_BY_ADDR) && (USE_HAL_FLASH_ERASE_BY_ADDR == 1U)
  uint32_t page_size;
#endif /* USE_HAL_FLASH_ERASE_BY_ADDR */
#if defined (USE_HAL_FLASH_PROGRAM_BY_ADDR) && (USE_HAL_FLASH_PROGRAM_BY_ADDR == 1U)
  uint32_t count;
#endif /* USE_HAL_FLASH_PROGRAM_BY_ADDR */

  ASSERT_DBG_PARAM(hflash != NULL);

  for (uint32_t bank_idx = 0U; bank_idx < 2U; bank_idx ++)
  {
    hal_flash_bank_t bank = (bank_idx == 0U) ? HAL_FLASH_BANK_1 : HAL_FLASH_BANK_2;
    if (bank == HAL_FLASH_BANK_1)
    {
      its   = LL_FLASH_READ_REG(FLASH_GET_INSTANCE(hflash), AIER) & (LL_FLASH_IT_ALL | LL_FLASH_IT_ECC_ALL);
    }
    else
    {
      its   = LL_FLASH_READ_REG(FLASH_GET_INSTANCE(hflash), BIER) & (LL_FLASH_IT_ALL | LL_FLASH_IT_ECC_ALL);
    }

    flags = LL_FLASH_ReadFlag(FLASH_GET_INSTANCE(hflash), (uint32_t)bank, LL_FLASH_FLAG_ERRORS_ALL \
                              | LL_FLASH_FLAG_EOPF | LL_FLASH_FLAG_CRCENDF | LL_FLASH_FLAG_ECC_ALL);

#if defined (USE_HAL_FLASH_PROGRAM_BY_ADDR) && (USE_HAL_FLASH_PROGRAM_BY_ADDR == 1U)
    if (hflash->ongoing_operation[bank_idx] == HAL_FLASH_PROGRAM)
    {
      if (IS_FLASH_OTP_ADDRESS(hflash->prog_flash_addr[bank_idx]))
      {
        LL_FLASH_DisableOTPProgramming(FLASH_GET_INSTANCE(hflash), (uint32_t)bank);
      }
      else
      {
        LL_FLASH_DisableProgramming(FLASH_GET_INSTANCE(hflash), (uint32_t)bank);
      }
    }
#endif /* USE_HAL_FLASH_PROGRAM_BY_ADDR */

    /* Check if End of operation event has occurred while its interrupt is enabled */
    if (((flags & its) & (LL_FLASH_FLAG_EOPF | LL_FLASH_FLAG_CRCENDF)) != 0U)
    {
      /* End of operation interrupt management */
#if defined (USE_HAL_FLASH_PROGRAM_BY_ADDR) && (USE_HAL_FLASH_PROGRAM_BY_ADDR == 1U)
      if (hflash->ongoing_operation[bank_idx] == HAL_FLASH_PROGRAM) /* Handle end of Program operation */
      {
        LL_FLASH_ClearFlag_EOPF(FLASH_GET_INSTANCE(hflash), (uint32_t)bank);
        /* Update program count */
        count = ((hflash->count[bank_idx] >= (uint32_t)HAL_FLASH_PROGRAM_QUADWORD) ? \
                 (uint32_t)HAL_FLASH_PROGRAM_QUADWORD : \
                 hflash->count[bank_idx]);
        hflash->count[bank_idx] -= count;

        /* Check if there are still data to program */
        if (hflash->count[bank_idx] > 0U)
        {
          /* Prepare and call next program operation */
          hflash->prog_data_addr[bank_idx]  += count;
          hflash->prog_flash_addr[bank_idx] += count;
          if ((hflash->count[bank_idx] >= (uint32_t)HAL_FLASH_PROGRAM_QUADWORD)
              || ((hflash->count[bank_idx] % (uint32_t)HAL_FLASH_PROGRAM_WORD) == 0U))
          {
            FLASH_ProgramByWord(hflash, bank, count / (uint32_t)HAL_FLASH_PROGRAM_WORD);
          }
          /* 16-bit only OTP flash programming or USER FLASH remaining programming size is equal to 32 bits */
          else if (IS_FLASH_OTP_ADDRESS(hflash->prog_flash_addr[bank_idx]) \
                   || (hflash->count[bank_idx] == (uint32_t)HAL_FLASH_PROGRAM_HALFWORD))
          {
            FLASH_ProgramByHalfWord(hflash, bank, count / (uint32_t)HAL_FLASH_PROGRAM_HALFWORD);
          }
          else /* Program by successive 8-bit accesses */
          {
            FLASH_ProgramByByte(hflash, bank, count);
          }
        }
        else /* No more program operations to perform */
        {
          hflash->ongoing_operation[bank_idx] = HAL_FLASH_NO_OPERATION;

#if defined (USE_HAL_FLASH_REGISTER_CALLBACKS) && (USE_HAL_FLASH_REGISTER_CALLBACKS == 1)
          hflash->p_program_cplt_cb(hflash, (hflash->prog_flash_addr[bank_idx]),
                                    hflash->size[bank_idx]);
#else
          HAL_FLASH_ProgramCpltCallback(hflash, (hflash->prog_flash_addr[bank_idx] - hflash->size[bank_idx] + 1U),
                                        hflash->size[bank_idx]);
#endif /* USE_HAL_FLASH_REGISTER_CALLBACKS */
        }
      }
#endif /* USE_HAL_FLASH_PROGRAM_BY_ADDR */
#if defined (USE_HAL_FLASH_ERASE_BY_ADDR) && (USE_HAL_FLASH_ERASE_BY_ADDR == 1U)
      if (hflash->ongoing_operation[bank_idx] == HAL_FLASH_ADDR_ERASE) /* Handle end of EraseByAddr operation */
      {
        LL_FLASH_ClearFlag_EOPF(FLASH_GET_INSTANCE(hflash), (uint32_t)bank);

        /* Update erase count */
        page_size = HAL_FLASH_GetUserFlashPageSizeByte(hflash, FLASH_GetBank(hflash, hflash->erase_page[bank_idx]), \
                                                       FLASH_GetPageIndex(hflash, hflash->erase_page[bank_idx]));
        hflash->count[bank_idx] -= page_size;

        /* Check if there are still pages to erase */
        if (hflash->count[bank_idx] > 0U)
        {
          /* Prepare and call next erase operation */
          hflash->erase_page[bank_idx] += page_size;
          LL_FLASH_StartErasePage(FLASH_GET_INSTANCE(hflash), (uint32_t)bank, \
                                  (hflash->erase_page[bank_idx] / FLASH_PAGE_SIZE));
        }
        else /* No more pages to erase */
        {
          LL_FLASH_DisablePageErase(FLASH_GET_INSTANCE(hflash), (uint32_t)bank);

          hflash->ongoing_operation[bank_idx] = HAL_FLASH_NO_OPERATION;

#if defined (USE_HAL_FLASH_REGISTER_CALLBACKS) && (USE_HAL_FLASH_REGISTER_CALLBACKS == 1)
          hflash->p_erase_by_addr_cplt_cb(hflash,
                                          (hflash->erase_page[bank_idx] + (FLASH_BANK_SIZE * bank_idx) + FLASH_BASE),
                                          hflash->size[bank_idx]);
#else
          HAL_FLASH_EraseByAddrCpltCallback(hflash, (hflash->erase_page[bank] - hflash->size[bank] + 1U),
                                            hflash->size[bank]);
#endif /* USE_HAL_FLASH_REGISTER_CALLBACKS */
        }
      }
#endif /* USE_HAL_FLASH_ERASE_BY_ADDR */
#if defined (USE_HAL_FLASH_ERASE_PAGE) && (USE_HAL_FLASH_ERASE_PAGE == 1U)
      if (hflash->ongoing_operation[bank_idx] == HAL_FLASH_PAGE_ERASE) /* Handle end of ErasePage operation */
      {
        LL_FLASH_ClearFlag_EOPF(FLASH_GET_INSTANCE(hflash), (uint32_t)bank);

        /* Update erase page count */
        hflash->count[bank_idx]--;

        /* Check if there are still pages to erase */
        if (hflash->count[bank_idx] > 0U)
        {
          /* Prepare and call next erase operation */
          hflash->erase_page[bank_idx]++;
          LL_FLASH_StartErasePage(FLASH_GET_INSTANCE(hflash), (uint32_t)bank, \
                                  (hflash->erase_page[bank_idx] % FLASH_PAGE_NB));
        }
        else /* No more pages to erase */
        {
          LL_FLASH_DisablePageErase(FLASH_GET_INSTANCE(hflash), (uint32_t)bank);

          hflash->ongoing_operation[bank_idx] = HAL_FLASH_NO_OPERATION;

#if defined (USE_HAL_FLASH_REGISTER_CALLBACKS) && (USE_HAL_FLASH_REGISTER_CALLBACKS == 1)
          hflash->p_erase_page_cplt_cb(hflash,
                                       bank,
                                       hflash->erase_page[bank_idx],
                                       hflash->count[bank_idx]);
#else
          HAL_FLASH_ErasePageCpltCallback(hflash,
                                          bank,
                                          hflash->erase_page[bank_idx],
                                          hflash->count[bank_idx]);
#endif /* USE_HAL_FLASH_REGISTER_CALLBACKS */
        }
      }
#endif /* USE_HAL_FLASH_ERASE_PAGE */
#if defined (USE_HAL_FLASH_ERASE_BANK) && (USE_HAL_FLASH_ERASE_BANK == 1U)
      if (hflash->ongoing_operation[bank_idx] == HAL_FLASH_BANK_ERASE)
      {
        LL_FLASH_ClearFlag_EOPF(FLASH_GET_INSTANCE(hflash), (uint32_t)bank);

        LL_FLASH_DisableBankErase(FLASH_GET_INSTANCE(hflash), (uint32_t)bank);

        hflash->ongoing_operation[bank_idx] = HAL_FLASH_NO_OPERATION;

#if defined (USE_HAL_FLASH_REGISTER_CALLBACKS) && (USE_HAL_FLASH_REGISTER_CALLBACKS == 1)
        hflash->p_erase_bank_cplt_cb(hflash, bank);
#else
        HAL_FLASH_EraseBankCpltCallback(hflash, bank);
#endif /* USE_HAL_FLASH_REGISTER_CALLBACKS */
      }
#endif /* USE_HAL_FLASH_ERASE_BANK */
#if defined (USE_HAL_FLASH_MASS_ERASE) && (USE_HAL_FLASH_MASS_ERASE == 1U)
      if (hflash->ongoing_operation[bank_idx] == HAL_FLASH_MASS_ERASE)
      {
        LL_FLASH_ClearFlag_EOPF(FLASH_GET_INSTANCE(hflash), (uint32_t)bank);

        LL_FLASH_DisableBankErase(FLASH_GET_INSTANCE(hflash), (uint32_t)bank);

        hflash->ongoing_operation[bank_idx] = HAL_FLASH_NO_OPERATION;
        if (hflash->ongoing_operation[(bank_idx + 1U) % 2U] != HAL_FLASH_MASS_ERASE)
        {
#if defined (USE_HAL_FLASH_REGISTER_CALLBACKS) && (USE_HAL_FLASH_REGISTER_CALLBACKS == 1)
          hflash->p_mass_erase_cplt_cb(hflash);
#else
          HAL_FLASH_MassEraseCpltCallback(hflash);
#endif /* USE_HAL_FLASH_REGISTER_CALLBACKS */
        }
      }
#endif /* USE_HAL_FLASH_MASS_ERASE */
#if defined (USE_HAL_FLASH_COMPUTE_CRC) && (USE_HAL_FLASH_COMPUTE_CRC == 1U)
      if (hflash->ongoing_operation[bank_idx] == HAL_FLASH_COMPUTE_CRC)
      {
        LL_FLASH_ClearFlag_CRCENDF(FLASH_GET_INSTANCE(hflash), (uint32_t)bank);
        /* hflash->crc_result[bank_idx] = LL_FLASH_GetCRCData(FLASH_GET_INSTANCE(hflash)); */

        LL_FLASH_DisableCRCByPage(FLASH_GET_INSTANCE(hflash), (uint32_t)bank);
        LL_FLASH_DisableCRC(FLASH_GET_INSTANCE(hflash), (uint32_t)bank);
        hflash->ongoing_operation[bank_idx] = HAL_FLASH_NO_OPERATION;
#if defined (USE_HAL_FLASH_REGISTER_CALLBACKS) && (USE_HAL_FLASH_REGISTER_CALLBACKS == 1)
        hflash->p_compute_crc_cplt_cb(hflash, bank);
#else
        HAL_FLASH_ComputeCRCCpltCallback(hflash, bank);
#endif /* USE_HAL_FLASH_REGISTER_CALLBACKS */
      }
#endif /* USE_HAL_FLASH_COMPUTE_CRC */
    }

    /* Check if an error whose interrupt is enabled has occurred */
    if (((flags & its) & LL_FLASH_FLAG_ERRORS_ALL) != 0U)
    {
      /* Error interrupt management */
#if defined(USE_HAL_FLASH_GET_LAST_ERRORS) && (USE_HAL_FLASH_GET_LAST_ERRORS == 1)
      FLASH_FillErrorCode(hflash, bank, flags);
#endif /* USE_HAL_FLASH_GET_LAST_ERRORS */
      LL_FLASH_ClearFlag(FLASH_GET_INSTANCE(hflash), (uint32_t)bank, LL_FLASH_FLAG_ERRORS_ALL);

      LL_FLASH_DisableProgramming(FLASH_GET_INSTANCE(hflash), (uint32_t)bank);

      LL_FLASH_DisablePageErase(FLASH_GET_INSTANCE(hflash), (uint32_t)bank);

      hflash->ongoing_operation[bank_idx] = HAL_FLASH_NO_OPERATION;

#if defined (USE_HAL_FLASH_REGISTER_CALLBACKS) && (USE_HAL_FLASH_REGISTER_CALLBACKS == 1)
      hflash->p_error_cb(hflash, bank);
#else
      HAL_FLASH_ErrorCallback(hflash, bank);
#endif /* USE_HAL_FLASH_REGISTER_CALLBACKS */
    }

#if defined (USE_HAL_FLASH_ECC) && (USE_HAL_FLASH_ECC == 1U)
    /* ECC correction Error Interrupt management **********************************************************************/
    if (((flags & its) & LL_FLASH_FLAG_SNECCERR) != 0U)
    {
      LL_FLASH_ClearFlag_SNECCERRF(FLASH_GET_INSTANCE(hflash), (uint32_t)bank);

#if defined (USE_HAL_FLASH_REGISTER_CALLBACKS) && (USE_HAL_FLASH_REGISTER_CALLBACKS == 1)
      hflash->p_ecc_error_cb(hflash, bank);
#else
      HAL_FLASH_ECC_ErrorCallback(hflash, bank);
#endif /* USE_HAL_FLASH_REGISTER_CALLBACKS */
    }

    if (((flags & its) & LL_FLASH_FLAG_DBECCERR) != 0U)
    {
      LL_FLASH_ClearFlag_DBECCERRF(FLASH_GET_INSTANCE(hflash), (uint32_t)bank);

#if defined (USE_HAL_FLASH_REGISTER_CALLBACKS) && (USE_HAL_FLASH_REGISTER_CALLBACKS == 1)
      hflash->p_ecc_error_cb(hflash, bank);
#else
      HAL_FLASH_ECC_ErrorCallback(hflash, bank);
#endif /* USE_HAL_FLASH_REGISTER_CALLBACKS */
    }
#endif /* USE_HAL_FLASH_ECC */

    if (hflash->ongoing_operation[bank_idx] == HAL_FLASH_NO_OPERATION)
    {
      LL_FLASH_DisableIT(FLASH_GET_INSTANCE(hflash), (uint32_t)bank, LL_FLASH_IT_ALL);
      hflash->global_state = HAL_FLASH_STATE_IDLE;
      hflash->bank_state[bank_idx] = HAL_FLASH_BANK_STATE_IDLE;
    }
  }
}

/**
  * @}
  */
/** @addtogroup FLASH_Exported_Functions_Group4
  * @{
This subsection provides a set of functions allowing to register the FLASH callbacks:
- The function HAL_FLASH_ProgramCpltCallback() to be redefined within application for the program complete callback.
- The function HAL_FLASH_EraseByAddrCpltCallback() to be redefined within application for the erase by address complete
  callback.
- The function HAL_FLASH_ErasePageCpltCallback() to be redefined within application for the erase by page complete
  callback.
- The function HAL_FLASH_EraseBankCpltCallback() to be redefined within application for the bank erase complete
  callback.
- The function HAL_FLASH_MassEraseCpltCallback() to be redefined within application for the mass erase complete
  callback.
- The function HAL_FLASH_ErrorCallback() to be redefined within application for the error callback.
- Call the function HAL_FLASH_RegisterProgramCpltCallback() to register the FLASH program complete callback.
- Call the function HAL_FLASH_RegisterEraseByAddrCpltCallback() to register the FLASH erase by address complete
  callback.
- Call the function HAL_FLASH_RegisterErasePageCpltCallback() to register the FLASH erase by page complete callback.
- Call the function HAL_FLASH_RegisterEraseBankCpltCallback() to register the FLASH bank erase complete callback.
- Call the function HAL_FLASH_RegisterMassEraseCpltCallback() to register the FLASH as erase complete callback.
- Call the function HAL_FLASH_RegisterErrorCallback() to register the FLASH error callback.
  */
#if defined (USE_HAL_FLASH_PROGRAM_BY_ADDR) && (USE_HAL_FLASH_PROGRAM_BY_ADDR == 1U)
/**
  * @brief  FLASH program complete callback.
  * @param  hflash Pointer to a \ref hal_flash_handle_t structure.
  * @retval None.
  */
__WEAK void HAL_FLASH_ProgramCpltCallback(hal_flash_handle_t *hflash, uint32_t flash_addr, uint32_t size_byte)
{
  /* Prevent unused argument(s) compilation warning */
  STM32_UNUSED(hflash);
  STM32_UNUSED(flash_addr);
  STM32_UNUSED(size_byte);

  /*! <b>WARNING:</b> When the HAL_FLASH_ProgramCpltCallback() callback is needed, it must be implemented within
                      user application for the program complete callback. */
}
#endif /* USE_HAL_FLASH_PROGRAM_BY_ADDR */
#if defined (USE_HAL_FLASH_ERASE_BY_ADDR) && (USE_HAL_FLASH_ERASE_BY_ADDR == 1U)
/**
  * @brief  FLASH erase by address complete callback.
  * @param  hflash     Pointer to a \ref hal_flash_handle_t structure.
  * @param  flash_addr Erased address.
  * @param  size_byte  Erased size in byte.
  * @retval None.
  */
__WEAK void HAL_FLASH_EraseByAddrCpltCallback(hal_flash_handle_t *hflash,
                                              uint32_t flash_addr,
                                              uint32_t size_byte)
{
  /* Prevent unused argument(s) compilation warning */
  STM32_UNUSED(hflash);
  STM32_UNUSED(flash_addr);
  STM32_UNUSED(size_byte);

  /*! <b>WARNING:</b> When the HAL_FLASH_EraseByAddrCpltCallback() callback is needed, it must be implemented within
                      user application for the erase by address complete callback. */
}
#endif /* USE_HAL_FLASH_ERASE_BY_ADDR */
#if defined (USE_HAL_FLASH_ERASE_PAGE) && (USE_HAL_FLASH_ERASE_PAGE == 1U)
/**
  * @brief  FLASH erase by page complete callback.
  * @param  hflash   Pointer to a \ref hal_flash_handle_t structure.
  * @param  bank     This parameter is one element of \ref hal_flash_bank_t enumeration.
  * @param  page     Index of erased page.
  * @param  page_nbr Number of erased pages.
  * @retval None.
  */
__WEAK void HAL_FLASH_ErasePageCpltCallback(hal_flash_handle_t *hflash,
                                            hal_flash_bank_t bank,
                                            uint32_t page,
                                            uint32_t page_nbr)
{
  /* Prevent unused argument(s) compilation warning */
  STM32_UNUSED(hflash);
  STM32_UNUSED(bank);
  STM32_UNUSED(page);
  STM32_UNUSED(page_nbr);

  /*! <b>WARNING:</b> When the HAL_FLASH_ErasePageCpltCallback() callback is needed, it must be implemented within
                      user application for the erase page complete callback. */
}
#endif /* USE_HAL_FLASH_ERASE_PAGE */
#if defined (USE_HAL_FLASH_ERASE_BANK) && (USE_HAL_FLASH_ERASE_BANK == 1U)
/**
  * @brief  FLASH bank erase complete callback.
  * @param  hflash Pointer to a \ref hal_flash_handle_t structure.
  * @param  bank   Pointer to a \ref hal_flash_bank_t structure.
  * @retval None.
  */
__WEAK void HAL_FLASH_EraseBankCpltCallback(hal_flash_handle_t *hflash, hal_flash_bank_t bank)
{
  /* Prevent unused argument(s) compilation warning */
  STM32_UNUSED(hflash);
  STM32_UNUSED(bank);

  /*! <b>WARNING:</b> When the HAL_FLASH_EraseBankCpltCallback() callback is needed, it must be implemented within
                      user application for the erase bank complete callback. */
}
#endif /* USE_HAL_FLASH_ERASE_BANK */
#if defined (USE_HAL_FLASH_MASS_ERASE) && (USE_HAL_FLASH_MASS_ERASE == 1U)
/**
  * @brief  FLASH mass erase complete callback.
  * @param  hflash Pointer to a \ref hal_flash_handle_t structure.
  * @retval None.
  */
__WEAK void HAL_FLASH_MassEraseCpltCallback(hal_flash_handle_t *hflash)
{
  /* Prevent unused argument(s) compilation warning */
  STM32_UNUSED(hflash);

  /*! <b>WARNING:</b> When the HAL_FLASH_MassEraseCpltCallback() callback is needed, it must be implemented within
                      user application for the mass erase complete callback. */
}
#endif /* USE_HAL_FLASH_MASS_ERASE */
#if defined (USE_HAL_FLASH_COMPUTE_CRC) && (USE_HAL_FLASH_COMPUTE_CRC == 1U)
/**
  * @brief  FLASH compute CRC complete callback.
  * @param  hflash Pointer to a \ref hal_flash_handle_t structure.
  * @retval None.
  */
__WEAK void HAL_FLASH_ComputeCRCCpltCallback(hal_flash_handle_t *hflash, hal_flash_bank_t bank)
{
  /* Prevent unused argument(s) compilation warning */
  STM32_UNUSED(hflash);
  STM32_UNUSED(bank);

  /*! <b>WARNING:</b> When the HAL_FLASH_ComputeCRCCpltCallback() callback is needed, it must be implemented within
                      user application for the compute CRC complete callback. */
}
#endif /* USE_HAL_FLASH_COMPUTE_CRC */
/**
  * @brief  FLASH error callback.
  * @param  hflash Pointer to a \ref hal_flash_handle_t structure.
  * @retval None.
  */
__WEAK void HAL_FLASH_ErrorCallback(hal_flash_handle_t *hflash, hal_flash_bank_t bank)
{
  /* Prevent unused argument(s) compilation warning */
  STM32_UNUSED(hflash);
  STM32_UNUSED(bank);

  /*! <b>WARNING:</b> When the HAL_FLASH_ErrorCallback() callback is needed, it must be implemented within
                      user application for the error callback. */
}

#if defined (USE_HAL_FLASH_ECC) && (USE_HAL_FLASH_ECC == 1)
/**
  * @brief  FLASH error code correction callback.
  *
  * @param  hflash Pointer to a \ref hal_flash_handle_t structure.
  * @retval HAL_ERROR Returned when this callback did not manage the ECC interrupt.
  * @retval HAL_OK    Returned when this callback managed the ECC interrupt.
  */
__WEAK hal_status_t HAL_FLASH_ECC_ErrorCallback(hal_flash_handle_t *hflash, hal_flash_bank_t bank)
{
  /* Prevent unused argument(s) compilation warning */
  STM32_UNUSED(hflash);
  STM32_UNUSED(bank);

  /*! <b>WARNING:</b> This function must not be modified, when the callback is needed, the
                      HAL_FLASH_ECC_ErrorCallback() could be implemented in the user file */

  return HAL_ERROR;
}
#endif /* USE_HAL_FLASH_ECC */

#if defined (USE_HAL_FLASH_REGISTER_CALLBACKS) && (USE_HAL_FLASH_REGISTER_CALLBACKS == 1)
#if defined (USE_HAL_FLASH_PROGRAM_BY_ADDR) && (USE_HAL_FLASH_PROGRAM_BY_ADDR == 1U)
/**
  * @brief  Register the FLASH program complete callback.
  * @param  hflash            Pointer to a \ref hal_flash_handle_t structure.
  * @param  callback          Specifies the program complete callback.
  * @retval HAL_INVALID_PARAM Returned when an invalid input parameter selected.
  * @retval HAL_OK            Returned when the register of the callback complete successfully.
  */
hal_status_t HAL_FLASH_RegisterProgramCpltCallback(hal_flash_handle_t *hflash, hal_flash_program_cplt_cb_t callback)
{
  ASSERT_DBG_PARAM(hflash   != NULL);
  ASSERT_DBG_PARAM(callback != NULL);
#if defined (USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (callback == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */
  hflash->p_program_cplt_cb = callback;
  return HAL_OK;
}
#endif /* USE_HAL_FLASH_PROGRAM_BY_ADDR */
#if defined (USE_HAL_FLASH_ERASE_BY_ADDR) && (USE_HAL_FLASH_ERASE_BY_ADDR == 1U)
/**
  * @brief  Register the FLASH erase by address complete callback.
  * @param  hflash            Pointer to a \ref hal_flash_handle_t structure.
  * @param  callback          Specifies the erase by address complete callback.
  * @retval HAL_INVALID_PARAM Returned when an invalid input parameter selected.
  * @retval HAL_OK            Returned when the register of the callback complete successfully.
  */
hal_status_t HAL_FLASH_RegisterEraseByAddrCpltCallback(hal_flash_handle_t *hflash,
                                                       hal_flash_erase_by_addr_cplt_cb_t callback)
{
  ASSERT_DBG_PARAM(hflash   != NULL);
  ASSERT_DBG_PARAM(callback != NULL);
#if defined (USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (callback == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */
  hflash->p_erase_by_addr_cplt_cb = callback;
  return HAL_OK;
}
#endif /* USE_HAL_FLASH_ERASE_BY_ADDR */
#if defined (USE_HAL_FLASH_ERASE_PAGE) && (USE_HAL_FLASH_ERASE_PAGE == 1U)
/**
  * @brief  Register the FLASH erase by page complete callback.
  * @param  hflash            Pointer to a \ref hal_flash_handle_t structure.
  * @param  callback          Specifies the erase by page complete callback.
  * @retval HAL_INVALID_PARAM Returned when an invalid input parameter selected.
  * @retval HAL_OK            Returned when the register of the callback complete successfully.
  */
hal_status_t HAL_FLASH_RegisterErasePageCpltCallback(hal_flash_handle_t *hflash,
                                                     hal_flash_erase_page_cplt_cb_t callback)
{
  ASSERT_DBG_PARAM(hflash   != NULL);
  ASSERT_DBG_PARAM(callback != NULL);
#if defined (USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (callback == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */
  hflash->p_erase_page_cplt_cb = callback;
  return HAL_OK;
}
#endif /* USE_HAL_FLASH_ERASE_PAGE */
#if defined (USE_HAL_FLASH_ERASE_BANK) && (USE_HAL_FLASH_ERASE_BANK == 1U)
/**
  * @brief  Register the FLASH ban erase complete callback.
  * @param  hflash            Pointer to a \ref hal_flash_handle_t structure.
  * @param  callback          Specifies the bank erase complete callback.
  * @retval HAL_INVALID_PARAM Returned when an invalid input parameter selected.
  * @retval HAL_OK            Returned when the register of the callback complete successfully.
  */
hal_status_t HAL_FLASH_RegisterEraseBankCpltCallback(hal_flash_handle_t *hflash,
                                                     hal_flash_erase_bank_cplt_cb_t callback)
{
  ASSERT_DBG_PARAM(hflash   != NULL);
  ASSERT_DBG_PARAM(callback != NULL);
#if defined (USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (callback == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */
  hflash->p_erase_bank_cplt_cb = callback;
  return HAL_OK;
}
#endif /* USE_HAL_FLASH_ERASE_BANK */
#if defined (USE_HAL_FLASH_MASS_ERASE) && (USE_HAL_FLASH_MASS_ERASE == 1U)
/**
  * @brief  Register the FLASH mass erase complete callback.
  * @param  hflash            Pointer to a \ref hal_flash_handle_t structure.
  * @param  callback          Specifies the mass erase complete callback.
  * @retval HAL_INVALID_PARAM Returned when an invalid input parameter selected.
  * @retval HAL_OK            Returned when the register of the callback complete successfully.
  */
hal_status_t HAL_FLASH_RegisterMassEraseCpltCallback(hal_flash_handle_t *hflash,
                                                     hal_flash_mass_erase_cplt_cb_t callback)
{
  ASSERT_DBG_PARAM(hflash   != NULL);
  ASSERT_DBG_PARAM(callback != NULL);
#if defined (USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (callback == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */
  hflash->p_mass_erase_cplt_cb = callback;
  return HAL_OK;
}
#endif /* USE_HAL_FLASH_MASS_ERASE */
#if defined (USE_HAL_FLASH_COMPUTE_CRC) && (USE_HAL_FLASH_COMPUTE_CRC == 1U)
/**
  * @brief  Register the FLASH compute CRC complete callback.
  * @param  hflash            Pointer to a \ref hal_flash_handle_t structure.
  * @param  callback          Specifies the computeCRC complete callback.
  * @retval HAL_INVALID_PARAM Returned when an invalid input parameter selected.
  * @retval HAL_OK            Returned when the register of the callback complete successfully.
  */
hal_status_t HAL_FLASH_RegisterComputeCRCCpltCallback(hal_flash_handle_t *hflash,
                                                      hal_flash_compute_crc_cplt_cb_t callback)
{
  ASSERT_DBG_PARAM(hflash   != NULL);
  ASSERT_DBG_PARAM(callback != NULL);
#if defined (USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (callback == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */
  hflash->p_compute_crc_cplt_cb = callback;
  return HAL_OK;
}
#endif /* USE_HAL_FLASH_COMPUTE_CRC */
/**
  * @brief  Register the FLASH error callback.
  * @param  hflash            Pointer to a \ref hal_flash_handle_t structure.
  * @param  callback          Specifies the error callback.
  * @retval HAL_INVALID_PARAM Returned when an invalid input parameter selected.
  * @retval HAL_OK            Returned when the register of the callback complete successfully.
  */
hal_status_t HAL_FLASH_RegisterErrorCallback(hal_flash_handle_t *hflash, hal_flash_error_cb_t callback)
{
  ASSERT_DBG_PARAM(hflash   != NULL);
  ASSERT_DBG_PARAM(callback != NULL);
#if defined (USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (callback == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */
  hflash->p_error_cb = callback;
  return HAL_OK;
}

#if defined (USE_HAL_FLASH_ECC) && (USE_HAL_FLASH_ECC == 1)
/**
  * @brief  Register the FLASH ECC error callback.
  * @param  hflash            Pointer to a \ref hal_flash_handle_t structure.
  * @param  callback          Specifies the error callback.
  * @retval HAL_INVALID_PARAM Returned when an invalid input parameter selected.
  * @retval HAL_OK            Returned when the register of the callback complete successfully.
  */
hal_status_t HAL_FLASH_RegisterECCErrorCallback(hal_flash_handle_t *hflash, hal_flash_ecc_error_cb_t callback)
{
  ASSERT_DBG_PARAM(hflash   != NULL);
  ASSERT_DBG_PARAM(callback != NULL);

#if defined (USE_HAL_CHECK_PARAM) && (USE_HAL_CHECK_PARAM == 1)
  if (callback == NULL)
  {
    return HAL_INVALID_PARAM;
  }
#endif /* USE_HAL_CHECK_PARAM */

  /* Register the FLASH error callback  */
  hflash->p_ecc_error_cb = callback;

  return HAL_OK;
}
#endif /* USE_HAL_FLASH_ECC */
#endif /* USE_HAL_FLASH_REGISTER_CALLBACKS */
/**
  * @}
  */
/** @addtogroup FLASH_Exported_Functions_Group5
  * @{
This subsection provides a set of functions allowing to get the FLASH data information and status:
- Call the function HAL_FLASH_GetCurrentOperation() to get the last operation.
- Call the function HAL_FLASH_GetCurrentProgrammedAddr() to get the last program operation information.
- Call the function HAL_FLASH_GetCurrentErasedAddr() to get the last erase by address operation information.
- Call the function HAL_FLASH_GetCurrentErasedPage() to get the last erase by page operation information.
- Call the function HAL_FLASH_GetInterruptedByResetOperationInfo() to get the FLASH interrupted operation information.
- Call the function HAL_FLASH_GetInfo() to get the FLASH information.
- Call the function HAL_FLASH_GetAddressOffset() to get the address offset of a specific page.
- Call the function HAL_FLASH_GetUserFlashPageSizeByte() to get the size of a given page.
- Call the function HAL_FLASH_GetBankSize() to get the size of a given bank.
- Call the function HAL_FLASH_GetState() to get the FLASH current state.
- Call the function HAL_FLASH_GetLastErrorCodes() to get the FLASH last errors codes.
- Call the function HAL_FLASH_SetUserData() to set a user data in the FLASH handle.
- Call the function HAL_FLASH_GetUserData() to get a user data from the FLASH handle.
  */
/**
  * @brief  Get the current operation on the given bank.
  * @param  hflash Pointer to a \ref hal_flash_handle_t structure.
  * @param  bank   This parameter is one element of \ref hal_flash_bank_t enumeration.
  * @retval hal_flash_operation_t Operation ongoing.
  */
hal_flash_operation_t HAL_FLASH_GetCurrentOperation(const hal_flash_handle_t *hflash, hal_flash_bank_t bank)
{
  ASSERT_DBG_PARAM(hflash != NULL);
  ASSERT_DBG_STATE(hflash->bank_state[FLASH_GET_BANK_INDEX(bank)],
                   HAL_FLASH_BANK_STATE_IDLE | HAL_FLASH_BANK_STATE_ACTIVE);

  return (hflash->ongoing_operation[bank]);
}

#if defined (USE_HAL_FLASH_PROGRAM_BY_ADDR) && (USE_HAL_FLASH_PROGRAM_BY_ADDR == 1U)
/**
  * @brief  Get the last programming operation information.
  *
  * @param  hflash   Pointer to a \ref hal_flash_handle_t structure.
  * @param  bank     This parameter is one element of \ref hal_flash_bank_t enumeration.
  * @retval uint32_t FLASH address currently being programmed.
  *                  0xFFFFFFFF if no program by address operation is ongoing on the given bank.
  */
uint32_t HAL_FLASH_GetCurrentProgrammedAddr(const hal_flash_handle_t *hflash, hal_flash_bank_t bank)
{
  ASSERT_DBG_PARAM(hflash != NULL);
  ASSERT_DBG_STATE(hflash->bank_state[FLASH_GET_BANK_INDEX(bank)],
                   HAL_FLASH_BANK_STATE_IDLE | HAL_FLASH_BANK_STATE_ACTIVE);

  if ((hflash->ongoing_operation[bank] != HAL_FLASH_PROGRAM))
  {
    return 0xFFFFFFFFU;
  }

  return hflash->prog_flash_addr[bank];
}
#endif /* USE_HAL_FLASH_PROGRAM_BY_ADDR */

#if defined (USE_HAL_FLASH_ERASE_BY_ADDR) && (USE_HAL_FLASH_ERASE_BY_ADDR == 1U)
/**
  * @brief  Get the last address erase operation information.
  *
  * @param  hflash   Pointer to a \ref hal_flash_handle_t structure.
  * @param  bank     This parameter is one element of \ref hal_flash_bank_t enumeration.
  * @retval uint32_t Address of the FLASH page currently being erased.
  *                  0xFFFFFFFF if no erase page by address operation is ongoing on the given bank.
  */
uint32_t HAL_FLASH_GetCurrentErasedAddr(const hal_flash_handle_t *hflash, hal_flash_bank_t bank)
{
  ASSERT_DBG_PARAM(hflash != NULL);
  ASSERT_DBG_STATE(hflash->bank_state[FLASH_GET_BANK_INDEX(bank)],
                   HAL_FLASH_BANK_STATE_IDLE | HAL_FLASH_BANK_STATE_ACTIVE);

  if ((hflash->ongoing_operation[bank] != HAL_FLASH_ADDR_ERASE))
  {
    return 0xFFFFFFFFU;
  }

  return hflash->erase_page[bank];
}
#endif /* USE_HAL_FLASH_ERASE_BY_ADDR */

#if defined (USE_HAL_FLASH_ERASE_PAGE) && (USE_HAL_FLASH_ERASE_PAGE == 1U)
/**
  * @brief  Get the last page erase operation information.
  * @param  hflash   Pointer to a \ref hal_flash_handle_t structure.
  * @param  bank     This parameter is one element of \ref hal_flash_bank_t enumeration.
  * @note   This function must be called during or directly after an ErasePage operation, otherwise the returned
  *         information could not be true anymore.
  * @retval uint32_t FLASH page currently being erased.
  *                  0xFFFFFFFF if no erase page operation is ongoing on the given bank.
  */
uint32_t HAL_FLASH_GetCurrentErasedPage(const hal_flash_handle_t *hflash, hal_flash_bank_t bank)
{
  ASSERT_DBG_PARAM(hflash != NULL);
  ASSERT_DBG_STATE(hflash->bank_state[FLASH_GET_BANK_INDEX(bank)],
                   HAL_FLASH_BANK_STATE_IDLE | HAL_FLASH_BANK_STATE_ACTIVE);

  if ((hflash->ongoing_operation[bank] != HAL_FLASH_PAGE_ERASE))
  {
    return 0xFFFFFFFFU;
  }

  return hflash->erase_page[bank];
}
#endif /* USE_HAL_FLASH_ERASE_PAGE */

/**
  * @brief  Get the user FLASH info (size, number and size of banks, number and size of pages).
  * @param  hflash Pointer to a \ref hal_flash_handle_t structure.
  * @param  p_info Pointer to a \ref hal_flash_info_t structure.
  */
void HAL_FLASH_GetInfo(const hal_flash_handle_t *hflash, hal_flash_info_t *p_info)
{
  ASSERT_DBG_PARAM(hflash != NULL);
  ASSERT_DBG_PARAM(p_info != NULL);

  p_info->bank_nbr = FLASH_BANK_NB;

  for (uint32_t bank = 0; bank < FLASH_BANK_NB; bank++)
  {
    p_info->bank[bank].area_nbr = 2;
    p_info->bank[bank].user_flash.base_addr      = FLASH_BASE + (bank * FLASH_BANK_SIZE);
    p_info->bank[bank].user_flash.area_size_byte = FLASH_BANK_SIZE;
    p_info->bank[bank].user_flash.page_nbr       = (uint16_t)FLASH_PAGE_NB;
  }

  STM32_UNUSED(hflash);
}

/**
  * @brief  Get the total FLASH size.
  * @param  hflash Pointer to a \ref hal_flash_handle_t structure.
  * @retval The size in bytes of total FLASH.
  */
uint32_t HAL_FLASH_GetSizeByte(const hal_flash_handle_t *hflash)
{
  ASSERT_DBG_PARAM(hflash != NULL);

  STM32_UNUSED(hflash);

  return (FLASH_SIZE);
}

/**
  * @brief  Get the number of FLASH banks.
  * @param  hflash Pointer to a \ref hal_flash_handle_t structure.
  * @retval The number of bank.
  */
uint8_t HAL_FLASH_GetBankNbr(const hal_flash_handle_t *hflash)
{
  ASSERT_DBG_PARAM(hflash != NULL);

  STM32_UNUSED(hflash);

  return (uint8_t)FLASH_BANK_NB;
}

/**
  * @brief  Get the total size in bytes of the given FLASH bank.
  * @param  hflash Pointer to a \ref hal_flash_handle_t structure.
  * @param  bank   Pointer to a \ref hal_flash_bank_t structure.
  * @retval The total size in bytes of the given bank.
  */
uint32_t HAL_FLASH_GetBankSizeByte(const hal_flash_handle_t *hflash, hal_flash_bank_t bank)
{
  ASSERT_DBG_PARAM(hflash != NULL);
  ASSERT_DBG_PARAM(IS_FLASH_BANK(bank));

  ASSERT_DBG_STATE(hflash->bank_state[FLASH_GET_BANK_INDEX(bank)],
                   HAL_FLASH_BANK_STATE_IDLE | HAL_FLASH_BANK_STATE_ACTIVE);

  STM32_UNUSED(hflash);
  STM32_UNUSED(bank);

  return (FLASH_BANK_SIZE);
}

/**
  * @brief  Get the size in bytes of the user flash area of the given bank.
  * @param  hflash Pointer to a \ref hal_flash_handle_t structure.
  * @param  bank   Selected bank.
  * @retval The size in bytes of the user flash area of the given bank.
  */
uint32_t HAL_FLASH_GetUserFlashSizeByte(const hal_flash_handle_t *hflash, hal_flash_bank_t bank)
{
  ASSERT_DBG_PARAM(hflash != NULL);
  ASSERT_DBG_PARAM(IS_FLASH_BANK(bank));
  ASSERT_DBG_STATE(hflash->bank_state[FLASH_GET_BANK_INDEX(bank)],
                   HAL_FLASH_BANK_STATE_IDLE | HAL_FLASH_BANK_STATE_ACTIVE);

  STM32_UNUSED(hflash);
  STM32_UNUSED(bank);

  return FLASH_BANK_SIZE;
}

/**
  * @brief  Get the number of pages of the user flash area of the given bank.
  * @param  hflash Pointer to a \ref hal_flash_handle_t structure.
  * @param  bank   Selected bank.
  * @retval The number of pages of the user flash area of the given bank.
  */
uint16_t HAL_FLASH_GetUserFlashPageNbr(const hal_flash_handle_t *hflash, hal_flash_bank_t bank)
{
  ASSERT_DBG_PARAM(hflash != NULL);
  ASSERT_DBG_PARAM(IS_FLASH_BANK(bank));
  ASSERT_DBG_STATE(hflash->bank_state[FLASH_GET_BANK_INDEX(bank)],
                   HAL_FLASH_BANK_STATE_IDLE | HAL_FLASH_BANK_STATE_ACTIVE);

  STM32_UNUSED(hflash);
  STM32_UNUSED(bank);

  return (uint16_t)FLASH_PAGE_NB;
}

/**
  * @brief  Get the size in bytes of the given user area page.
  * @param  hflash Pointer to a \ref hal_flash_handle_t structure.
  * @param  bank   Selected bank.
  * @param  page   Selected page
  * @retval The size in bytes of the given user area page.
  */
uint32_t HAL_FLASH_GetUserFlashPageSizeByte(const hal_flash_handle_t *hflash, hal_flash_bank_t bank, uint32_t page)
{
  ASSERT_DBG_PARAM(hflash != NULL);
  ASSERT_DBG_PARAM(IS_FLASH_BANK(bank));
  ASSERT_DBG_PARAM(page < FLASH_PAGE_NB);
  ASSERT_DBG_STATE(hflash->bank_state[FLASH_GET_BANK_INDEX(bank)],
                   HAL_FLASH_BANK_STATE_IDLE | HAL_FLASH_BANK_STATE_ACTIVE);

  STM32_UNUSED(hflash);
  STM32_UNUSED(bank);
  STM32_UNUSED(page);

  return FLASH_PAGE_SIZE;
}

/**
  * @brief  Get the offset address of the given user area page.
  * @param  hflash  Pointer to a \ref hal_flash_handle_t structure.
  * @param  bank    Selected bank.
  * @param  page  Page within selected bank.
  * @retval Address The offset address of the given user area page.
  */
uint32_t HAL_FLASH_GetUserFlashAddrOffset(const hal_flash_handle_t *hflash, hal_flash_bank_t bank, uint32_t page)
{
  ASSERT_DBG_PARAM(hflash != NULL);
  ASSERT_DBG_PARAM(IS_FLASH_BANK(bank));
  ASSERT_DBG_PARAM(page < FLASH_PAGE_NB);
  ASSERT_DBG_STATE(hflash->bank_state[FLASH_GET_BANK_INDEX(bank)],
                   HAL_FLASH_BANK_STATE_IDLE | HAL_FLASH_BANK_STATE_ACTIVE);

  STM32_UNUSED(hflash);

  return ((uint32_t)bank * FLASH_BANK_SIZE) + (page * FLASH_PAGE_SIZE);
}

#if defined (USE_HAL_FLASH_ECC) && (USE_HAL_FLASH_ECC == 1U)
/**
  * @brief  Get the ECC fail information.
  * @param  hflash Pointer to a \ref hal_flash_handle_t structure.
  * @param  p_info Pointer to a \ref hal_flash_ecc_fail_info_t structure.
  */
void HAL_FLASH_ECC_GetFailInfo(const hal_flash_handle_t *hflash,
                               hal_flash_bank_t bank,
                               hal_flash_ecc_fail_info_t *p_info)
{
  ASSERT_DBG_PARAM(hflash != NULL);
  ASSERT_DBG_PARAM(p_info != NULL);
  ASSERT_DBG_STATE(hflash->bank_state[FLASH_GET_BANK_INDEX(bank)],
                   HAL_FLASH_BANK_STATE_IDLE | HAL_FLASH_BANK_STATE_ACTIVE);

  STM32_UNUSED(hflash);

  if (LL_FLASH_IsActiveFlag_SNECCERRF(FLASH_GET_INSTANCE(hflash), (uint32_t)bank) != 0U)
  {
    p_info->type = HAL_FLASH_ECC_FAIL_SINGLE_ERROR;
    p_info->addr = LL_FLASH_GetECCCFailAddress(FLASH_GET_INSTANCE(hflash), (uint32_t)bank) ;
  }
  else if (LL_FLASH_IsActiveFlag_DBECCERRF(FLASH_GET_INSTANCE(hflash), (uint32_t)bank) != 0U)
  {
    p_info->type = HAL_FLASH_ECC_FAIL_DOUBLE_ERROR;
    p_info->addr = LL_FLASH_GetECCDFailAddress(FLASH_GET_INSTANCE(hflash), (uint32_t)bank) ;
  }
  else /* No ECC */
  {
    p_info->type = HAL_FLASH_ECC_FAIL_NONE;
  }
}
#endif /* USE_HAL_FLASH_ECC */

/**
  * @brief  Get the FLASH current state.
  * @param  hflash Pointer to a \ref hal_flash_handle_t structure.
  * @retval State  The FLASH global state.
  */
hal_flash_state_t HAL_FLASH_GetState(const hal_flash_handle_t *hflash)
{
  ASSERT_DBG_PARAM(hflash != NULL);

  return (hflash->global_state);
}

/**
  * @brief  Get the FLASH current bank state.
  * @param  hflash Pointer to a \ref hal_flash_handle_t structure.
  * @param  bank   Pointer to a \ref hal_flash_bank_t structure.
  * @retval hal_flash_bank_state_t The FLASH bank state.
  */
hal_flash_bank_state_t HAL_FLASH_GetBankState(const hal_flash_handle_t *hflash, hal_flash_bank_t bank)
{
  ASSERT_DBG_PARAM(hflash != NULL);

  return (hflash->bank_state[FLASH_GET_BANK_INDEX(bank)]);
}

#if defined(USE_HAL_FLASH_GET_LAST_ERRORS) && (USE_HAL_FLASH_GET_LAST_ERRORS == 1)
/**
  * @brief  Get the FLASH last error codes.
  * @param  hflash      Pointer to a \ref hal_flash_handle_t structure.
  * @retval Error codes The FLASH last error codes.
  */
uint32_t HAL_FLASH_GetLastErrorCodes(const hal_flash_handle_t *hflash)
{
  uint32_t last_error_codes;

  ASSERT_DBG_PARAM(hflash != NULL);

  last_error_codes = hflash->last_error_codes[0];
  last_error_codes |= hflash->last_error_codes[1];

  return last_error_codes;
}
#endif /* USE_HAL_FLASH_GET_LAST_ERRORS */

#if defined (USE_HAL_FLASH_USER_DATA) && (USE_HAL_FLASH_USER_DATA == 1)
/**
  * @brief  Store User Data pointer within the FLASH handle.
  * @param  hflash      Pointer to a \ref hal_flash_handle_t structure.
  * @param  p_user_data Pointer to the user data.
  */
void HAL_FLASH_SetUserData(hal_flash_handle_t *hflash, const void *p_user_data)
{
  ASSERT_DBG_PARAM(hflash != NULL);

  hflash->p_user_data = p_user_data;
}

/**
  * @brief  Retrieve the user data pointer from the FLASH handle.
  * @param  hflash  Pointer to a \ref hal_flash_handle_t structure.
  * @retval Pointer to the user data.
  */
const void *HAL_FLASH_GetUserData(const hal_flash_handle_t *hflash)
{
  ASSERT_DBG_PARAM(hflash != NULL);

  return (hflash->p_user_data);
}
#endif /* USE_HAL_FLASH_USER_DATA */
/**
  * @}
  */

/**
  * @}
  */

/** @defgroup FLASH_Private_Functions FLASH Private Functions
  * @{
  */

/**
  * @brief  Wait for a FLASH operation to complete.
  * @param  hflash       Pointer to a \ref hal_flash_handle_t structure.
  * @param  timeout_msec Maximum flash operation timeout.
  * @retval HAL_ERROR    There is an operation in progress.
  * @retval HAL_OK       No operation to be waiting.
  */
static hal_status_t FLASH_WaitForEndOfOperation(hal_flash_handle_t *hflash,
                                                hal_flash_bank_t bank,
                                                uint32_t timeout_msec)
{
  uint32_t tickstart;
  uint32_t error_code;

  tickstart = HAL_GetTick();
  while (LL_FLASH_IsActiveFlag(FLASH_GET_INSTANCE(hflash), (uint32_t)bank, LL_FLASH_FLAG_STATUS_ALL) != 0U)
  {
    if ((HAL_GetTick() - tickstart) > timeout_msec)
    {
      return HAL_TIMEOUT;
    }
  }

  error_code = LL_FLASH_ReadFlag(FLASH_GET_INSTANCE(hflash), (uint32_t)bank, LL_FLASH_FLAG_ERRORS_ALL);

  if (error_code != 0U)
  {
#if defined (USE_HAL_FLASH_GET_LAST_ERRORS) && (USE_HAL_FLASH_GET_LAST_ERRORS == 1)
    FLASH_FillErrorCode(hflash, bank, error_code);
#else
    /* Prevent unused argument compilation warning */
    STM32_UNUSED(hflash);
#endif /* USE_HAL_FLASH_GET_LAST_ERRORS */

    /* Check error flags */
    LL_FLASH_ClearFlag(FLASH_GET_INSTANCE(hflash), (uint32_t)bank, LL_FLASH_FLAG_ERRORS_ALL);

    return HAL_ERROR;
  }

  /* Clear FLASH End of Operation pending bit */
  LL_FLASH_ClearFlag_EOPF(FLASH_GET_INSTANCE(hflash), (uint32_t)bank);

  /* If no error flag is set */
  return HAL_OK;
}

#if defined (USE_HAL_FLASH_PROGRAM_BY_ADDR) && (USE_HAL_FLASH_PROGRAM_BY_ADDR == 1U)
/**
  * @brief  Update the adaptive programming mode and compute the number of elementary writes to perform.
  * @param  hflash   Pointer to a \ref hal_flash_handle_t structure.
  * @retval uint32_t Number of elementary writes to perform.
  */
static uint32_t FLASH_UpdateAdaptiveProgMode(hal_flash_handle_t *hflash, hal_flash_bank_t bank)
{
  uint32_t programming_mode;
  uint32_t count;
  uint32_t bank_idx;

  bank_idx = FLASH_GET_BANK_INDEX(bank);
  count = hflash->count[bank_idx];

  if (FLASH_IsFlashUSERAddress(hflash, hflash->prog_flash_addr[bank_idx], 1U) != 0U)
  {
    if (hflash->count[bank_idx] >= (uint32_t)HAL_FLASH_PROGRAM_QUADWORD)
    {
      programming_mode = (uint32_t)HAL_FLASH_PROGRAM_QUADWORD;
      count = (uint32_t)HAL_FLASH_PROGRAM_QUADWORD;
    }
    else
    {
      programming_mode = (uint32_t)HAL_FLASH_PROGRAM_DOUBLEWORD;
      while (((hflash->count[bank_idx] % programming_mode) != 0U) \
             && (programming_mode != (uint32_t)HAL_FLASH_PROGRAM_BYTE))
      {
        programming_mode >>= 1U;
      }
    }
  }
  else
  {
    if ((hflash->count[bank_idx] % (uint32_t)HAL_FLASH_PROGRAM_WORD) == 0U)
    {
      programming_mode = (uint32_t)HAL_FLASH_PROGRAM_WORD;
      count = (uint32_t)HAL_FLASH_PROGRAM_WORD;
    }
    else
    {
      programming_mode = (uint32_t)HAL_FLASH_PROGRAM_HALFWORD;
      count = (uint32_t)HAL_FLASH_PROGRAM_HALFWORD;
    }
  }

  hflash->programming_mode[bank_idx] = (hal_flash_program_mode_t) programming_mode;
  return count;
}

/**
  * @brief  Program up to a quad-word (128-bit) at a specified address by successive write operations in polling mode.
  * @param  hflash           Pointer to a \ref hal_flash_handle_t structure.
  * @param  flash_addr       FLASH address to program.
  * @param  p_data           Pointer to the data to be programmed.
  * @param  size_byte        Size of the data to be programmed.
  * @param  is_adaptive_prog Adaptive Programming Mode Value.
  * @param  timeout_msec     Maximum user timeout value for program operation in milliseconds.
  * @retval HAL_ERROR        Error during programming.
  * @retval HAL_TIMEOUT      User timeout.
  * @retval HAL_OK           No operation to be waiting.
  */
static hal_status_t FLASH_Program(hal_flash_handle_t *hflash,
                                  uint32_t flash_addr,
                                  const uint32_t *p_data,
                                  uint32_t size_byte,
                                  uint32_t is_adaptive_prog,
                                  uint32_t timeout_msec)
{
  hal_status_t status;
  uint32_t prog_size;
  uint32_t tickstart;
  hal_flash_bank_t bank = FLASH_GetBank(hflash, flash_addr);
  uint32_t bank_idx = FLASH_GET_BANK_INDEX(bank);

  if (LL_FLASH_IsLocked(FLASH_GET_INSTANCE(hflash), (uint32_t)bank) != 0U)
  {
    return HAL_ERROR;
  }

  HAL_CHECK_UPDATE_STATE(hflash, bank_state[bank_idx], HAL_FLASH_BANK_STATE_IDLE, HAL_FLASH_BANK_STATE_ACTIVE);

  status = FLASH_WaitForEndOfOperation(hflash, bank, timeout_msec);

  if (status == HAL_OK)
  {
#if defined (USE_HAL_FLASH_GET_LAST_ERRORS) && (USE_HAL_FLASH_GET_LAST_ERRORS == 1)
    hflash->last_error_codes[bank_idx] = HAL_FLASH_ERROR_NONE;
#endif /* USE_HAL_FLASH_GET_LAST_ERRORS */

    /* Fill the operation information in the handle */
    hflash->ongoing_operation[bank_idx] = HAL_FLASH_PROGRAM;
    hflash->prog_data_addr[bank_idx]    = (uint32_t)p_data;
    hflash->prog_flash_addr[bank_idx]   = flash_addr;
    hflash->count[bank_idx]             = size_byte;
    hflash->size[bank_idx]              = size_byte;
    hflash->is_adaptive_prog[bank_idx]  = is_adaptive_prog;

    while ((status == HAL_OK) && (hflash->count[bank_idx] > 0U))
    {
      if (hflash->is_adaptive_prog[bank_idx] != 0U)
      {
        prog_size = FLASH_UpdateAdaptiveProgMode(hflash, bank);
      }
      else
      {
        prog_size = (uint32_t)(hflash->programming_mode[bank_idx]);
      }

      tickstart = HAL_GetTick();

      if (hflash->programming_mode[bank_idx] >= HAL_FLASH_PROGRAM_WORD)
      {
        FLASH_ProgramByWord(hflash, bank, prog_size / (uint32_t)HAL_FLASH_PROGRAM_WORD);
      }
      else if (hflash->programming_mode[bank_idx] == HAL_FLASH_PROGRAM_HALFWORD)
      {
        FLASH_ProgramByHalfWord(hflash, bank, prog_size / (uint32_t)HAL_FLASH_PROGRAM_HALFWORD);
      }
      else /* Program by successive 8-bit accesses */
      {
        FLASH_ProgramByByte(hflash, bank, prog_size);
      }

      status = FLASH_WaitForEndOfOperation(hflash, bank, timeout_msec);

      if (((HAL_GetTick() - tickstart) > timeout_msec) && (status == HAL_OK))
      {
        status = HAL_TIMEOUT;
      }

      /* Update handle programming elements and reset programming flags if no error occurred */
      if (status == HAL_OK)
      {
        if (IS_FLASH_OTP_ADDRESS(hflash->prog_flash_addr[bank_idx]))
        {
          LL_FLASH_DisableOTPProgramming(FLASH_GET_INSTANCE(hflash), (uint32_t)bank);
        }
        else
        {
          LL_FLASH_DisableProgramming(FLASH_GET_INSTANCE(hflash), (uint32_t)bank);
        }

        hflash->count[bank_idx]           -= prog_size;
        hflash->prog_data_addr[bank_idx]  += prog_size;
        hflash->prog_flash_addr[bank_idx] += prog_size;
      }
    }
  }

  if (status == HAL_OK)
  {
    hflash->ongoing_operation[bank_idx] = HAL_FLASH_NO_OPERATION;
  }
  hflash->global_state = HAL_FLASH_STATE_IDLE;
  hflash->bank_state[bank_idx] = HAL_FLASH_BANK_STATE_IDLE;

  return status;
}

/**
  * @brief  Program up to a quad-word (128-bit) at a specified address by successive write operations.
  * @param  hflash Pointer to a \ref hal_flash_handle_t structure.
  * @retval None.
  */
static hal_status_t FLASH_Program_IT(hal_flash_handle_t *hflash, uint32_t flash_addr, const uint32_t *p_data,
                                     uint32_t size_byte, uint32_t is_adaptive_prog)
{
  hal_flash_bank_t bank = FLASH_GetBank(hflash, flash_addr);
  uint32_t bank_idx = FLASH_GET_BANK_INDEX(bank);
  uint32_t prog_size;

  if (LL_FLASH_IsLocked(FLASH_GET_INSTANCE(hflash), (uint32_t)bank) != 0U)
  {
    return HAL_ERROR;
  }

  HAL_CHECK_UPDATE_STATE(hflash, bank_state[bank_idx], HAL_FLASH_BANK_STATE_IDLE, HAL_FLASH_BANK_STATE_ACTIVE);

  if (FLASH_WaitForEndOfOperation(hflash, bank, FLASH_OPERATION_MAX_TIMEOUT) == HAL_OK)
  {
#if defined (USE_HAL_FLASH_GET_LAST_ERRORS) && (USE_HAL_FLASH_GET_LAST_ERRORS == 1)
    hflash->last_error_codes[bank_idx] = HAL_FLASH_ERROR_NONE;
#endif /* USE_HAL_FLASH_GET_LAST_ERRORS */

    /* Fill the operation information structure */
    hflash->ongoing_operation[bank_idx] = HAL_FLASH_PROGRAM;
    hflash->prog_data_addr[bank_idx]    = (uint32_t)p_data;
    hflash->prog_flash_addr[bank_idx]   = flash_addr;
    hflash->count[bank_idx]             = size_byte;
    hflash->size[bank_idx]              = size_byte;
    hflash->is_adaptive_prog[bank_idx]  = is_adaptive_prog;

    if (hflash->is_adaptive_prog[bank_idx] != 0U)
    {
      prog_size = FLASH_UpdateAdaptiveProgMode(hflash, bank);
    }
    else
    {
      prog_size = (uint32_t)(hflash->programming_mode[bank_idx]);
    }

    LL_FLASH_EnableIT(FLASH_GET_INSTANCE(hflash), (uint32_t)bank, LL_FLASH_IT_ALL);

    if (hflash->programming_mode[bank_idx] >= HAL_FLASH_PROGRAM_WORD)
    {
      FLASH_ProgramByWord(hflash, bank, prog_size / (uint32_t)HAL_FLASH_PROGRAM_WORD);
    }
    else if (hflash->programming_mode[bank_idx] == HAL_FLASH_PROGRAM_HALFWORD)
    {
      FLASH_ProgramByHalfWord(hflash, bank, prog_size / (uint32_t)HAL_FLASH_PROGRAM_HALFWORD);
    }
    else /* Program by successive 8-bit accesses */
    {
      FLASH_ProgramByByte(hflash, bank, prog_size);
    }

    return HAL_OK;
  }
  else
  {
    hflash->global_state = HAL_FLASH_STATE_IDLE;
    hflash->bank_state[bank_idx] = HAL_FLASH_BANK_STATE_IDLE;
    return HAL_ERROR;
  }
}

/**
  * @brief  Program up to a quad-word (128-bit) at a specified address by successive word write operations.
  * @param  hflash Pointer to a \ref hal_flash_handle_t structure.
  * @retval None.
  */
static void FLASH_ProgramByWord(hal_flash_handle_t *hflash, hal_flash_bank_t bank, uint32_t count)
{
  uint32_t bank_idx = FLASH_GET_BANK_INDEX(bank);

  uint32_t increment_index = count;
  uint32_t *dest_addr      = (uint32_t *)(hflash->prog_flash_addr[bank_idx]);
  uint32_t *src_addr       = (uint32_t *)(hflash->prog_data_addr[bank_idx]);
  uint32_t primask_bit;

  LL_FLASH_EnableProgramming(FLASH_GET_INSTANCE(hflash), (uint32_t)bank);

  /* Enter critical section: Disable interrupts to avoid any interruption during the loop */
  primask_bit = __get_PRIMASK();
  __disable_irq();

  /* Program */
  do
  {
    *dest_addr = *src_addr;
    dest_addr++;
    src_addr++;
    increment_index--;
  } while (increment_index != 0U);

  __ISB();
  __DSB();

  /* Set FW bit when less than a quad-word is written */
  if ((count * (uint32_t)HAL_FLASH_PROGRAM_WORD) < (uint32_t)HAL_FLASH_PROGRAM_QUADWORD)
  {
    LL_FLASH_EnableForceWrite(FLASH_GET_INSTANCE(hflash), (uint32_t)bank);
  }
  /* Exit critical section: restore previous priority mask */
  __set_PRIMASK(primask_bit);
}

/**
  * @brief  Program up to a quad-word (128-bit) at a specified address by successive word write operations.
  * @param  hflash Pointer to a \ref hal_flash_handle_t structure.
  * @retval None.
  */
static void FLASH_ProgramByHalfWord(hal_flash_handle_t *hflash, hal_flash_bank_t bank, uint32_t count)
{
  uint32_t bank_idx = FLASH_GET_BANK_INDEX(bank);

  uint32_t increment_index = count;
  uint16_t *dest_addr      = (uint16_t *)(hflash->prog_flash_addr[bank_idx]);
  uint16_t *src_addr       = (uint16_t *)(hflash->prog_data_addr[bank_idx]);
  uint32_t primask_bit;

  if (IS_FLASH_OTP_ADDRESS(hflash->prog_flash_addr[bank_idx]))
  {
    LL_FLASH_EnableOTPProgramming(FLASH_GET_INSTANCE(hflash), (uint32_t)bank);
  }
  else
  {
    LL_FLASH_EnableProgramming(FLASH_GET_INSTANCE(hflash), (uint32_t)bank);
  }

  /* Enter critical section: Disable interrupts to avoid any interruption during the loop */
  primask_bit = __get_PRIMASK();
  __disable_irq();

  /* Program */
  do
  {
    *dest_addr = *src_addr;
    dest_addr++;
    src_addr++;
    increment_index--;
  } while (increment_index != 0U);

  __ISB();
  __DSB();

  /* Set FW bit when less than a quad-word is written */
  if ((FLASH_IsFlashUSERAddress(hflash, hflash->prog_flash_addr[bank_idx], 1U) != 0U))
  {
    LL_FLASH_EnableForceWrite(FLASH_GET_INSTANCE(hflash), (uint32_t)bank);
  }
  /* Exit critical section: restore previous priority mask */
  __set_PRIMASK(primask_bit);
}

/**
  * @brief  Program up to a quad-word (128-bit) at a specified address by successive byte write operations.
  * @param  hflash Pointer to a \ref hal_flash_handle_t structure.
  * @retval None.
  */
static void FLASH_ProgramByByte(hal_flash_handle_t *hflash, hal_flash_bank_t bank, uint32_t count)
{
  uint32_t bank_idx = FLASH_GET_BANK_INDEX(bank);

  uint32_t increment_index = count;
  uint8_t *dest_addr       = (uint8_t *)(hflash->prog_flash_addr[bank_idx]);
  uint8_t *src_addr        = (uint8_t *)(hflash->prog_data_addr[bank_idx]);
  uint32_t primask_bit;

  LL_FLASH_EnableProgramming(FLASH_GET_INSTANCE(hflash), (uint32_t)bank);

  /* Enter critical section: Disable interrupts to avoid any interruption during the loop */
  primask_bit = __get_PRIMASK();
  __disable_irq();

  /* Program */
  do
  {
    *dest_addr = *src_addr;
    dest_addr++;
    src_addr++;
    increment_index--;
  } while (increment_index != 0U);

  __ISB();
  __DSB();

  /* Set FW bit when less than a quad-word is written */
  LL_FLASH_EnableForceWrite(FLASH_GET_INSTANCE(hflash), (uint32_t)bank);

  /* Exit critical section: restore previous priority mask */
  __set_PRIMASK(primask_bit);
}
#endif /* USE_HAL_FLASH_PROGRAM_BY_ADDR */

#if defined (USE_HAL_FLASH_ERASE_BY_ADDR) && (USE_HAL_FLASH_ERASE_BY_ADDR == 1U)
/**
  * @brief  Erase pages of FLASH memory by address in polling mode.
  * @param  hflash         Pointer to a \ref hal_flash_handle_t structure.
  * @param  flash_addr     FLASH address to erase.
  * @param  size_byte      Size of the data to be erased.
  * @param  page_size      Page size of the erased area.
  * @param  timeout_msec   Maximum user timeout value for erase operation in milliseconds.
  * @retval HAL_ERROR      Error during erasing.
  * @retval HAL_TIMEOUT    User timeout.
  * @retval HAL_OK         No operation to be waiting.
  */
static hal_status_t FLASH_EraseAddr(hal_flash_handle_t *hflash,
                                    uint32_t flash_addr,
                                    uint32_t size_byte,
                                    uint32_t page_size,
                                    uint32_t timeout_msec)
{
  uint32_t start_page;
  uint32_t end_page;
  hal_status_t status;
  uint32_t tickstart;
  hal_flash_bank_t bank;
  uint32_t         bank_idx;

  bank     = FLASH_GetBank(hflash, flash_addr);
  bank_idx = FLASH_GET_BANK_INDEX(bank);

  if (LL_FLASH_IsLocked(FLASH_GET_INSTANCE(hflash), (uint32_t)bank) != 0U)
  {
    return HAL_ERROR;
  }

  HAL_CHECK_UPDATE_STATE(hflash, bank_state[bank_idx], HAL_FLASH_BANK_STATE_IDLE, HAL_FLASH_BANK_STATE_ACTIVE);

#if defined (USE_HAL_FLASH_GET_LAST_ERRORS) && (USE_HAL_FLASH_GET_LAST_ERRORS == 1)
  hflash->last_error_codes[bank_idx] = HAL_FLASH_ERROR_NONE;
#endif /* USE_HAL_FLASH_GET_LAST_ERRORS */

  status = FLASH_WaitForEndOfOperation(hflash, bank, timeout_msec);

  if (status == HAL_OK)
  {
    /* Fill the operation information structure */
    start_page = FLASH_GetPageIndex(hflash, flash_addr);
    end_page = FLASH_GetPageIndex(hflash, flash_addr + size_byte - 1U);

    hflash->ongoing_operation[bank_idx] = HAL_FLASH_ADDR_ERASE;
    hflash->erase_page[bank_idx]        = ((start_page % FLASH_PAGE_NB) * page_size);
    hflash->count[bank_idx]             = (end_page - start_page + 1U) * page_size;
    hflash->size[bank_idx]              = hflash->count[bank_idx];

    LL_FLASH_ClearFlag(FLASH_GET_INSTANCE(hflash), (uint32_t)bank, LL_FLASH_FLAG_ERRORS_ALL);

    while ((status == HAL_OK) && (hflash->count[bank_idx] > 0U))
    {
      tickstart = HAL_GetTick();

      LL_FLASH_StartErasePage(FLASH_GET_INSTANCE(hflash), (uint32_t)bank, \
                              (FLASH_GetPageIndex(hflash, hflash->erase_page[bank_idx]) % FLASH_PAGE_NB));

      status = FLASH_WaitForEndOfOperation(hflash, bank, FLASH_ERASE_PAGE_OPERATION_TIMEOUT);

      hflash->count[bank_idx] -= page_size;
      if (hflash->count[bank_idx] != 0U)
      {
        hflash->erase_page[bank_idx] += page_size;
      }

      if (((HAL_GetTick() - tickstart) > timeout_msec) && (status == HAL_OK))
      {
        status = HAL_TIMEOUT;
      }
    }
  }

  LL_FLASH_ClearFlag_EOPF(FLASH_GET_INSTANCE(hflash), (uint32_t)bank);
  LL_FLASH_DisablePageErase(FLASH_GET_INSTANCE(hflash), (uint32_t)bank);

  hflash->ongoing_operation[bank_idx] = HAL_FLASH_NO_OPERATION;
  hflash->global_state = HAL_FLASH_STATE_IDLE;
  hflash->bank_state[bank_idx] = HAL_FLASH_BANK_STATE_IDLE;

  return status;
}

/**
  * @brief  Erase pages of FLASH memory by address in interrupt mode.
  * @param  hflash         Pointer to a \ref hal_flash_handle_t structure.
  * @param  flash_addr     FLASH address to erase.
  * @param  size_byte      Size of the data to be erased.
  * @param  page_size      Page size of the erased area.
  * @retval HAL_ERROR      Error during erasing.
  * @retval HAL_OK         No operation to be waiting.
  */
static hal_status_t FLASH_EraseAddr_IT(hal_flash_handle_t *hflash,
                                       uint32_t flash_addr,
                                       uint32_t size_byte,
                                       uint32_t page_size)
{
  uint32_t         start_page;
  uint32_t         end_page;
  hal_flash_bank_t bank;
  uint32_t         bank_idx;

  bank = FLASH_GetBank(hflash, flash_addr);
  bank_idx  = FLASH_GET_BANK_INDEX(bank);

  if (LL_FLASH_IsLocked(FLASH_GET_INSTANCE(hflash), (uint32_t)bank) != 0U)
  {
    return HAL_ERROR;
  }

  HAL_CHECK_UPDATE_STATE(hflash, bank_state[bank_idx], HAL_FLASH_BANK_STATE_IDLE, HAL_FLASH_BANK_STATE_ACTIVE);

#if defined (USE_HAL_FLASH_GET_LAST_ERRORS) && (USE_HAL_FLASH_GET_LAST_ERRORS == 1)
  hflash->last_error_codes[bank_idx] = HAL_FLASH_ERROR_NONE;
#endif /* USE_HAL_FLASH_GET_LAST_ERRORS */

  if (FLASH_WaitForEndOfOperation(hflash, bank, FLASH_OPERATION_MAX_TIMEOUT) == HAL_OK)
  {
    /* Fill the operation information structure */
    start_page = FLASH_GetPageIndex(hflash, flash_addr);
    end_page = FLASH_GetPageIndex(hflash, flash_addr + size_byte - 1U);

    hflash->ongoing_operation[bank_idx]  = HAL_FLASH_ADDR_ERASE;
    hflash->erase_page[bank_idx]         = ((start_page % FLASH_PAGE_NB) * page_size);
    hflash->count[bank_idx]              = (end_page - start_page + 1U) * page_size;
    hflash->size[bank_idx]               = hflash->count[bank_idx];

    LL_FLASH_EnableIT(FLASH_GET_INSTANCE(hflash), (uint32_t)bank, LL_FLASH_IT_ALL);
    LL_FLASH_StartErasePage(FLASH_GET_INSTANCE(hflash), (uint32_t)bank, (start_page % FLASH_PAGE_NB));
    return HAL_OK;
  }
  else
  {
    hflash->global_state = HAL_FLASH_STATE_IDLE;
    hflash->bank_state[bank_idx] = HAL_FLASH_BANK_STATE_IDLE;
    return HAL_ERROR;
  }
}
#endif /* USE_HAL_FLASH_ERASE_BY_ADDR */

#if defined (USE_HAL_FLASH_ERASE_PAGE) && (USE_HAL_FLASH_ERASE_PAGE == 1U)
/**
  * @brief  Erase pages of FLASH memory by address in polling mode.
  * @param  hflash       Pointer to a \ref hal_flash_handle_t structure.
  * @param  bank         Bank to erase.
  * @param  start_page   Index of the first page to erase.
  * @param  page_nbr     The number of pages to erase.
  * @param  timeout_msec Maximum user timeout value for erase operation in milliseconds.
  * @retval HAL_ERROR    Error during erasing.
  * @retval HAL_TIMEOUT  User timeout.
  * @retval HAL_OK       No operation to be waiting.
  */
static hal_status_t FLASH_ErasePage(hal_flash_handle_t *hflash,
                                    hal_flash_bank_t bank,
                                    uint32_t start_page,
                                    uint32_t page_nbr,
                                    uint32_t timeout_msec)
{
  hal_status_t status;
  uint32_t     tickstart;
  uint32_t     bank_idx;

  bank_idx = FLASH_GET_BANK_INDEX(bank);

  if (LL_FLASH_IsLocked(FLASH_GET_INSTANCE(hflash), (uint32_t)bank) != 0U)
  {
    return HAL_ERROR;
  }

  HAL_CHECK_UPDATE_STATE(hflash, bank_state[bank_idx], HAL_FLASH_BANK_STATE_IDLE, HAL_FLASH_BANK_STATE_ACTIVE);

#if defined (USE_HAL_FLASH_GET_LAST_ERRORS) && (USE_HAL_FLASH_GET_LAST_ERRORS == 1)
  hflash->last_error_codes[bank_idx] = HAL_FLASH_ERROR_NONE;
#endif /* USE_HAL_FLASH_GET_LAST_ERRORS */

  status = FLASH_WaitForEndOfOperation(hflash, bank, timeout_msec);

  if (status == HAL_OK)
  {
    /* Fill the operation information structure */
    hflash->ongoing_operation[bank_idx] = HAL_FLASH_PAGE_ERASE;
    hflash->erase_page[bank_idx] = start_page;
    hflash->count[bank_idx]      = page_nbr;
    hflash->size[bank_idx]       = page_nbr;

    LL_FLASH_ClearFlag(FLASH_GET_INSTANCE(hflash), (uint32_t)bank, LL_FLASH_FLAG_ERRORS_ALL);

    while ((status == HAL_OK) && (hflash->count[bank_idx] > 0U))
    {
      tickstart = HAL_GetTick();
      LL_FLASH_StartErasePage(FLASH_GET_INSTANCE(hflash), (uint32_t)bank, \
                              hflash->erase_page[bank_idx] % FLASH_PAGE_NB);
      status = FLASH_WaitForEndOfOperation(hflash, bank, FLASH_ERASE_PAGE_OPERATION_TIMEOUT);

      hflash->count[bank_idx]--;
      if (hflash->count[bank_idx] != 0U)
      {
        hflash->erase_page[bank_idx]++;
      }

      if (((HAL_GetTick() - tickstart) > timeout_msec) && (status == HAL_OK))
      {
        status = HAL_TIMEOUT;
      }
    }
  }

  LL_FLASH_ClearFlag_EOPF(FLASH_GET_INSTANCE(hflash), (uint32_t)bank);
  LL_FLASH_DisablePageErase(FLASH_GET_INSTANCE(hflash), (uint32_t)bank);

  hflash->ongoing_operation[bank_idx] = HAL_FLASH_NO_OPERATION;
  hflash->global_state = HAL_FLASH_STATE_IDLE;
  hflash->bank_state[bank_idx] = HAL_FLASH_BANK_STATE_IDLE;

  return status;
}

/**
  * @brief  Erase pages of FLASH memory by address in interrupt mode.
  * @param  hflash       Pointer to a \ref hal_flash_handle_t structure.
  * @param  bank         Bank to erase.
  * @param  start_page   Index of the first page to erase.
  * @param  page_nbr     Number of pages to erase.
  * @retval HAL_ERROR    Error during erasing.
  * @retval HAL_OK       No operation to be waiting.
  */
static hal_status_t FLASH_ErasePage_IT(hal_flash_handle_t *hflash,
                                       hal_flash_bank_t bank,
                                       uint32_t start_page,
                                       uint32_t page_nbr)
{
  uint32_t bank_idx;

  bank_idx = FLASH_GET_BANK_INDEX(bank);

  if (LL_FLASH_IsLocked(FLASH_GET_INSTANCE(hflash), (uint32_t)bank) != 0U)
  {
    return HAL_ERROR;
  }

  HAL_CHECK_UPDATE_STATE(hflash, bank_state[bank_idx], HAL_FLASH_BANK_STATE_IDLE, HAL_FLASH_BANK_STATE_ACTIVE);

  if (FLASH_WaitForEndOfOperation(hflash, bank, FLASH_OPERATION_MAX_TIMEOUT) == HAL_OK)
  {
#if defined (USE_HAL_FLASH_GET_LAST_ERRORS) && (USE_HAL_FLASH_GET_LAST_ERRORS == 1)
    hflash->last_error_codes[bank_idx] = HAL_FLASH_ERROR_NONE;
#endif /* USE_HAL_FLASH_GET_LAST_ERRORS */

    /* Fill the operation information structure */
    hflash->ongoing_operation[bank_idx]  = HAL_FLASH_PAGE_ERASE;
    hflash->erase_page[bank_idx]         = start_page;
    hflash->count[bank_idx]              = page_nbr;
    hflash->size[bank_idx]               = page_nbr;

    LL_FLASH_EnableIT(FLASH_GET_INSTANCE(hflash), (uint32_t)bank, LL_FLASH_IT_ALL);
    LL_FLASH_StartErasePage(FLASH_GET_INSTANCE(hflash), (uint32_t)bank, \
                            hflash->erase_page[bank_idx] % FLASH_PAGE_NB);
    return HAL_OK;
  }
  else
  {
    hflash->global_state = HAL_FLASH_STATE_IDLE;
    hflash->bank_state[bank_idx] = HAL_FLASH_BANK_STATE_IDLE;
    return HAL_ERROR;
  }
}
#endif /* USE_HAL_FLASH_ERASE_PAGE */

#if defined (USE_HAL_FLASH_ERASE_BANK) && (USE_HAL_FLASH_ERASE_BANK == 1U)
/**
  * @brief  Bank erase of FLASH memory.
  * @param  hflash Pointer to a \ref hal_flash_handle_t structure.
  * @retval None.
  */
static void FLASH_BankErase(hal_flash_handle_t *hflash, hal_flash_bank_t bank)
{
  LL_FLASH_EnableBankErase(FLASH_GET_INSTANCE(hflash), (uint32_t)bank);
  LL_FLASH_StartEraseOperation(FLASH_GET_INSTANCE(hflash), (uint32_t)bank);
}
#endif /* USE_HAL_FLASH_ERASE_BANK */
#if (defined (USE_HAL_FLASH_PROGRAM_BY_ADDR) || defined (USE_HAL_FLASH_ERASE_BY_ADDR)) \
    && ((USE_HAL_FLASH_PROGRAM_BY_ADDR == 1U) || (USE_HAL_FLASH_ERASE_BY_ADDR == 1U))
/**
  * @brief Get the bank which contains the given flash address.
  * @param flash_addr Flash Address
  * @retval hal_bank_t the bank containing the given address.
  *                    This parameter is one element of \ref hal_flash_bank_t enumeration.
  */
static hal_flash_bank_t FLASH_GetBank(const hal_flash_handle_t *hflash, uint32_t flash_addr)
{
  STM32_UNUSED(hflash);

  if ((flash_addr >= OTP_AREA_BASE) && (flash_addr < (OTP_AREA_BASE + OTP_SIZE)))
  {
    return HAL_FLASH_BANK_1;
  }
  else
  {
    return (((flash_addr - FLASH_BASE) < FLASH_BANK_SIZE) ? HAL_FLASH_BANK_1 : HAL_FLASH_BANK_2);
  }
}

/**
  * @brief Get the page index associated to the given flash address.
  * @param flash_addr Flash Address.
  * @retval uint32_t The index of the page containing the given address.
  */
static uint32_t FLASH_GetPageIndex(const hal_flash_handle_t *hflash, uint32_t flash_addr)
{
  STM32_UNUSED(hflash);

  return (((flash_addr - FLASH_BASE) / FLASH_PAGE_SIZE) % FLASH_PAGE_NB);
}

/**
  * @brief  Check if a FLASH address is part of the user FLASH area.
  * @param  hflash Pointer to a \ref hal_flash_handle_t structure.
  * @param  flash_addr The FLASH address to check.
  * @param  is_prog_addr The flag indicating if the address must be aligned for programming.
  * @retval The status of the FLASH address test (1: address is in user FLASH, 0: otherwise)
  */
static uint32_t FLASH_IsFlashUSERAddress(const hal_flash_handle_t *hflash, uint32_t flash_addr, uint8_t is_prog_addr)
{
  uint32_t user_flash = ((flash_addr >= FLASH_BASE) && (flash_addr < (FLASH_BASE + FLASH_SIZE))) ? 1U : 0U;

  STM32_UNUSED(hflash);

  return (((user_flash == 1U) && ((is_prog_addr == 0U) ? (1U == 1U) : (((flash_addr) % 16U) == 0U))) ? 1U : 0U);
}
#endif /* USE_HAL_FLASH_PROGRAM_BY_ADDR || USE_HAL_FLASH_ERASE_BY_ADDR */

#if defined(USE_HAL_FLASH_GET_LAST_ERRORS) && (USE_HAL_FLASH_GET_LAST_ERRORS == 1)
/**
  * @brief  Update last error element of FLASH handle.
  * @param  hflash Pointer to a \ref hal_flash_handle_t structure.
  * @param  error_code Bitfield containing the error flags.
  * @retval None.
  */
static void FLASH_FillErrorCode(hal_flash_handle_t *hflash, hal_flash_bank_t bank, uint64_t error_code)
{
#if defined (USE_HAL_FLASH_PROGRAM_BY_ADDR) && (USE_HAL_FLASH_PROGRAM_BY_ADDR == 1U)
  if ((error_code & LL_FLASH_FLAG_STRBERR) != 0U)
  {
    hflash->last_error_codes[FLASH_GET_BANK_INDEX(bank)] |= (HAL_FLASH_BANK_1_ERROR_STRB << ((uint32_t)bank / 4U));
  }

  if ((error_code & LL_FLASH_FLAG_INCERR) != 0U)
  {
    hflash->last_error_codes[FLASH_GET_BANK_INDEX(bank)] |= (HAL_FLASH_BANK_1_ERROR_INC << ((uint32_t)bank / 4U));
  }
#endif /* USE_HAL_FLASH_PROGRAM_BY_ADDR */
#if (defined (USE_HAL_FLASH_PROGRAM_BY_ADDR) || defined (USE_HAL_FLASH_ERASE_BY_ADDR) \
    || defined (USE_HAL_FLASH_ERASE_PAGE) || defined (USE_HAL_FLASH_ERASE_BANK) \
    || defined (USE_HAL_FLASH_MASS_ERASE)) && ((USE_HAL_FLASH_PROGRAM_BY_ADDR == 1U) \
    || (USE_HAL_FLASH_ERASE_BY_ADDR == 1U) || (USE_HAL_FLASH_ERASE_PAGE == 1U) \
    || (USE_HAL_FLASH_ERASE_BANK == 1U) || (USE_HAL_FLASH_MASS_ERASE == 1U))
  if ((error_code & LL_FLASH_FLAG_WRPERR) != 0U)
  {
    hflash->last_error_codes[FLASH_GET_BANK_INDEX(bank)] |= (HAL_FLASH_BANK_1_ERROR_WRP << ((uint32_t)bank / 4U));
  }

  if ((error_code & LL_FLASH_FLAG_PGSERR) != 0U)
  {
    hflash->last_error_codes[FLASH_GET_BANK_INDEX(bank)] |= (HAL_FLASH_BANK_1_ERROR_PGS << ((uint32_t)bank / 4U));
  }
#endif /* USE_HAL_FLASH_PROGRAM_BY_ADDR || USE_HAL_FLASH_ERASE_BY_ADDR || USE_HAL_FLASH_ERASE_PAGE
          || USE_HAL_FLASH_ERASE_BANK || USE_HAL_FLASH_MASS_ERASE */

  if ((error_code & LL_FLASH_FLAG_RDSERR) != 0U)
  {
    hflash->last_error_codes[FLASH_GET_BANK_INDEX(bank)] |= (HAL_FLASH_BANK_1_ERROR_RDS << ((uint32_t)bank / 4U));
  }

#if defined (USE_HAL_FLASH_COMPUTE_CRC) && (USE_HAL_FLASH_COMPUTE_CRC == 1U)
  if ((error_code & LL_FLASH_FLAG_CRCRDERR) != 0U)
  {
    hflash->last_error_codes[FLASH_GET_BANK_INDEX(bank)] |= (HAL_FLASH_BANK_1_ERROR_CRC << ((uint32_t)bank / 4U));
  }
#endif /* USE_HAL_FLASH_COMPUTE_CRC */
}
#endif /* USE_HAL_FLASH_GET_LAST_ERRORS */
/**
  * @}
  */
#endif /* USE_HAL_FLASH_MODULE */
/**
  * @}
  */

/**
  * @}
  */
