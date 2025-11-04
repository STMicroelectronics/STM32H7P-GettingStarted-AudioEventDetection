# origin-pack: STMicroelectronics::stfcf@0.6.0
# created-by: conversion-manager@0.0.65
project(STMicroelectronics_stfcf_0_6_0)
cmake_minimum_required(VERSION 3.20)
add_library(STMicroelectronics_stfcf_0_6_0 INTERFACE)

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




# Include Pre_Include_Global.h globally if needed
if(CMSIS_Tcompiler STREQUAL "IAR")
    target_compile_options(STMicroelectronics_stfcf_0_6_0 INTERFACE "SHELL:--preinclude ${CMAKE_CURRENT_LIST_DIR}/Pre_Include_Global.h")
else()
    target_compile_options(STMicroelectronics_stfcf_0_6_0 INTERFACE "SHELL:-include ${CMAKE_CURRENT_LIST_DIR}/Pre_Include_Global.h")
endif()



# Enable all components in this package
if(CMSIS_ENTIRE_STMicroelectronics_stfcf_0_6_0)
  set(CMSIS_USE_Security_STFCF_PSA_API_1_0_0 true)
  set(CMSIS_USE_Security_STFCF_Core_0_6_0 true)
  set(CMSIS_USE_Security_STFCF_MbedTLS_Alt_Common_0_5_0 true)
  set(CMSIS_USE_Security_STFCF_MbedTLS_Alt_STCryptoLib_0_5_0 true)
  set(CMSIS_USE_Security_STFCF_MbedTLS_Alt_HAL_0_5_0 true)
  set(CMSIS_USE_Security_STFCF_KWE_0_6_0 true)
endif()

# All conditions used by this package

# condition: STMicroelectronics.stfcf.0.6.0
# description: 
if((CMSIS_Dname MATCHES "STM32.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13"))
  set(STMicroelectronics.stfcf.0.6.0 true)
  message(DEBUG "CMSIS condition STMicroelectronics.stfcf.0.6.0 enabled")
endif()


# condition: STMicroelectronics.stfcf.0.6.0:KWE condition
# description: Requires CCB HAL driver component
set(STMicroelectronics.stfcf.0.6.0:KWE_condition true)
message(DEBUG "CMSIS condition STMicroelectronics.stfcf.0.6.0:KWE_condition enabled")


# condition: STMicroelectronics.stfcf.0.6.0:Mbed TLS Alt HAL condition
# description: Requires HAL driver component(s)
set(STMicroelectronics.stfcf.0.6.0:Mbed_TLS_Alt_HAL_condition true)
message(DEBUG "CMSIS condition STMicroelectronics.stfcf.0.6.0:Mbed_TLS_Alt_HAL_condition enabled")


# condition: STMicroelectronics.stfcf.0.6.0:Mbed TLS Alt STCryptoLib condition
# description: Requires STCryptoLib component
set(STMicroelectronics.stfcf.0.6.0:Mbed_TLS_Alt_STCryptoLib_condition true)
message(DEBUG "CMSIS condition STMicroelectronics.stfcf.0.6.0:Mbed_TLS_Alt_STCryptoLib_condition enabled")


# condition: STMicroelectronics.stfcf.0.6.0:No STFCF generator
# description: STFCF without config
set(STMicroelectronics.stfcf.0.6.0:No_STFCF_generator true)
message(DEBUG "CMSIS condition STMicroelectronics.stfcf.0.6.0:No_STFCF_generator enabled")


# condition: STMicroelectronics.stfcf.0.6.0:PSA interface conditions
# description: Ensure PSA API are satisfied
set(STMicroelectronics.stfcf.0.6.0:PSA_interface_conditions true)
message(DEBUG "CMSIS condition STMicroelectronics.stfcf.0.6.0:PSA_interface_conditions enabled")


# condition: STMicroelectronics.stfcf.0.6.0:STFCF config condition
# description: STFCF possible implementations
set(STMicroelectronics.stfcf.0.6.0:STFCF_config_condition true)
message(DEBUG "CMSIS condition STMicroelectronics.stfcf.0.6.0:STFCF_config_condition enabled")


# condition: STMicroelectronics.stfcf.0.6.0:alt aes condition
# description: Enable aes_alt implementation
set(STMicroelectronics.stfcf.0.6.0:alt_aes_condition true)
message(DEBUG "CMSIS condition STMicroelectronics.stfcf.0.6.0:alt_aes_condition enabled")


# condition: STMicroelectronics.stfcf.0.6.0:alt ccm condition
# description: Enable ccm_alt implementation
set(STMicroelectronics.stfcf.0.6.0:alt_ccm_condition true)
message(DEBUG "CMSIS condition STMicroelectronics.stfcf.0.6.0:alt_ccm_condition enabled")


# condition: STMicroelectronics.stfcf.0.6.0:alt chachapoly condition
# description: Enable chachapoly_alt implementation
set(STMicroelectronics.stfcf.0.6.0:alt_chachapoly_condition true)
message(DEBUG "CMSIS condition STMicroelectronics.stfcf.0.6.0:alt_chachapoly_condition enabled")


# condition: STMicroelectronics.stfcf.0.6.0:alt cmac condition
# description: Enable cmac_alt implementation
set(STMicroelectronics.stfcf.0.6.0:alt_cmac_condition true)
message(DEBUG "CMSIS condition STMicroelectronics.stfcf.0.6.0:alt_cmac_condition enabled")


# condition: STMicroelectronics.stfcf.0.6.0:alt drbg condition
# description: Enable drbg_alt implementation
set(STMicroelectronics.stfcf.0.6.0:alt_drbg_condition true)
message(DEBUG "CMSIS condition STMicroelectronics.stfcf.0.6.0:alt_drbg_condition enabled")


# condition: STMicroelectronics.stfcf.0.6.0:alt ecp condition
# description: Enable ecp_alt implementation
set(STMicroelectronics.stfcf.0.6.0:alt_ecp_condition true)
message(DEBUG "CMSIS condition STMicroelectronics.stfcf.0.6.0:alt_ecp_condition enabled")


# condition: STMicroelectronics.stfcf.0.6.0:alt entropy_hw condition
# description: Enable entropy_hw_alt implementation
set(STMicroelectronics.stfcf.0.6.0:alt_entropy_hw_condition true)
message(DEBUG "CMSIS condition STMicroelectronics.stfcf.0.6.0:alt_entropy_hw_condition enabled")


# condition: STMicroelectronics.stfcf.0.6.0:alt gcm condition
# description: Enable aes_alt implementation
set(STMicroelectronics.stfcf.0.6.0:alt_gcm_condition true)
message(DEBUG "CMSIS condition STMicroelectronics.stfcf.0.6.0:alt_gcm_condition enabled")


# condition: STMicroelectronics.stfcf.0.6.0:alt rsa condition
# description: Enable rsa_alt implementation
set(STMicroelectronics.stfcf.0.6.0:alt_rsa_condition true)
message(DEBUG "CMSIS condition STMicroelectronics.stfcf.0.6.0:alt_rsa_condition enabled")


# condition: STMicroelectronics.stfcf.0.6.0:alt sha1 condition
# description: Enable sha1_alt implementation
set(STMicroelectronics.stfcf.0.6.0:alt_sha1_condition true)
message(DEBUG "CMSIS condition STMicroelectronics.stfcf.0.6.0:alt_sha1_condition enabled")


# condition: STMicroelectronics.stfcf.0.6.0:alt sha256 condition
# description: Enable sha256_alt implementation
set(STMicroelectronics.stfcf.0.6.0:alt_sha256_condition true)
message(DEBUG "CMSIS condition STMicroelectronics.stfcf.0.6.0:alt_sha256_condition enabled")

# Files and components in this package
if(CMSIS_USE_Security_STFCF_PSA_API_1_0_0)  # High level Interface, Platform Security Architecture, as entry point; Link directly the PSA API of Mbed TLS
  message(DEBUG "Using component Security_STFCF_PSA_API_1_0_0")
  if(STMicroelectronics.stfcf.0.6.0:PSA_interface_conditions)
    target_compile_definitions(STMicroelectronics_stfcf_0_6_0 INTERFACE -DCMSIS_USE_Security_STFCF_PSA_API_1_0_0=1)
  endif()
endif()

if(CMSIS_USE_Security_STFCF_Core_0_6_0)  # Templates 
  message(DEBUG "Using component Security_STFCF_Core_0_6_0")
  if(STMicroelectronics.stfcf.0.6.0:No_STFCF_generator)
    target_compile_definitions(STMicroelectronics_stfcf_0_6_0 INTERFACE -DCMSIS_USE_Security_STFCF_Core_0_6_0=1)
    target_include_directories(STMicroelectronics_stfcf_0_6_0 INTERFACE templates)
  endif()
endif()

if(CMSIS_USE_Security_STFCF_MbedTLS_Alt_Common_0_5_0)  # Router for the Mbed TLS and STMicroelectronics' alternatives according to the configuration choices
  message(DEBUG "Using component Security_STFCF_MbedTLS_Alt_Common_0_5_0")
  target_compile_definitions(STMicroelectronics_stfcf_0_6_0 INTERFACE -DCMSIS_USE_Security_STFCF_MbedTLS_Alt_Common_0_5_0=1)
  target_include_directories(STMicroelectronics_stfcf_0_6_0 INTERFACE mbedtls_alt/include/common/)
  if(STMicroelectronics.stfcf.0.6.0:alt_aes_condition)
    target_include_directories(STMicroelectronics_stfcf_0_6_0 INTERFACE mbedtls_alt/include/common)
  endif()
  if(STMicroelectronics.stfcf.0.6.0:alt_ccm_condition)
    target_include_directories(STMicroelectronics_stfcf_0_6_0 INTERFACE mbedtls_alt/include/common)
  endif()
  if(STMicroelectronics.stfcf.0.6.0:alt_chachapoly_condition)
    target_include_directories(STMicroelectronics_stfcf_0_6_0 INTERFACE mbedtls_alt/include/common)
  endif()
  if(STMicroelectronics.stfcf.0.6.0:alt_cmac_condition)
    target_include_directories(STMicroelectronics_stfcf_0_6_0 INTERFACE mbedtls_alt/include/common)
  endif()
  if(STMicroelectronics.stfcf.0.6.0:alt_drbg_condition)
    target_include_directories(STMicroelectronics_stfcf_0_6_0 INTERFACE mbedtls_alt/include/common)
  endif()
  if(STMicroelectronics.stfcf.0.6.0:alt_ecp_condition)
    target_include_directories(STMicroelectronics_stfcf_0_6_0 INTERFACE mbedtls_alt/include/common)
  endif()
  if(STMicroelectronics.stfcf.0.6.0:alt_entropy_hw_condition)
    target_include_directories(STMicroelectronics_stfcf_0_6_0 INTERFACE mbedtls_alt/include/common)
  endif()
  if(STMicroelectronics.stfcf.0.6.0:alt_gcm_condition)
    target_include_directories(STMicroelectronics_stfcf_0_6_0 INTERFACE mbedtls_alt/include/common)
  endif()
  if(STMicroelectronics.stfcf.0.6.0:alt_rsa_condition)
    target_include_directories(STMicroelectronics_stfcf_0_6_0 INTERFACE mbedtls_alt/include/common)
  endif()
  if(STMicroelectronics.stfcf.0.6.0:alt_sha1_condition)
    target_include_directories(STMicroelectronics_stfcf_0_6_0 INTERFACE mbedtls_alt/include/common)
  endif()
  if(STMicroelectronics.stfcf.0.6.0:alt_sha256_condition)
    target_include_directories(STMicroelectronics_stfcf_0_6_0 INTERFACE mbedtls_alt/include/common)
  endif()
endif()

if(CMSIS_USE_Security_STFCF_MbedTLS_Alt_STCryptoLib_0_5_0)  # Mbed TLS alternative implementation thanks STM32 Cryptographic library (STCryptoLib)
  message(DEBUG "Using component Security_STFCF_MbedTLS_Alt_STCryptoLib_0_5_0")
  if(STMicroelectronics.stfcf.0.6.0:Mbed_TLS_Alt_STCryptoLib_condition)
    target_compile_definitions(STMicroelectronics_stfcf_0_6_0 INTERFACE -DCMSIS_USE_Security_STFCF_MbedTLS_Alt_STCryptoLib_0_5_0=1)
    target_include_directories(STMicroelectronics_stfcf_0_6_0 INTERFACE mbedtls_alt/include/stcryptolib)
    target_sources(STMicroelectronics_stfcf_0_6_0 INTERFACE mbedtls_alt/source/stcryptolib/aes_alt.c)
    target_sources(STMicroelectronics_stfcf_0_6_0 INTERFACE mbedtls_alt/source/stcryptolib/chachapoly_alt.c)
    target_sources(STMicroelectronics_stfcf_0_6_0 INTERFACE mbedtls_alt/source/stcryptolib/cmac_alt.c)
    target_sources(STMicroelectronics_stfcf_0_6_0 INTERFACE mbedtls_alt/source/stcryptolib/drbg_alt.c)
    target_sources(STMicroelectronics_stfcf_0_6_0 INTERFACE mbedtls_alt/source/stcryptolib/ecdh_alt.c)
    target_sources(STMicroelectronics_stfcf_0_6_0 INTERFACE mbedtls_alt/source/stcryptolib/ecdsa_alt.c)
    target_sources(STMicroelectronics_stfcf_0_6_0 INTERFACE mbedtls_alt/source/stcryptolib/gcm_alt.c)
    target_sources(STMicroelectronics_stfcf_0_6_0 INTERFACE mbedtls_alt/source/stcryptolib/rsa_alt.c)
    target_sources(STMicroelectronics_stfcf_0_6_0 INTERFACE mbedtls_alt/source/stcryptolib/sha256_alt.c)
  endif()
endif()

if(CMSIS_USE_Security_STFCF_MbedTLS_Alt_HAL_0_5_0)  # Mbed TLS alternative implementation thanks hardware acceleration (HAL API)
  message(DEBUG "Using component Security_STFCF_MbedTLS_Alt_HAL_0_5_0")
  if(STMicroelectronics.stfcf.0.6.0:Mbed_TLS_Alt_HAL_condition)
    target_compile_definitions(STMicroelectronics_stfcf_0_6_0 INTERFACE -DCMSIS_USE_Security_STFCF_MbedTLS_Alt_HAL_0_5_0=1)
    target_include_directories(STMicroelectronics_stfcf_0_6_0 INTERFACE mbedtls_alt/include/hal)
    target_sources(STMicroelectronics_stfcf_0_6_0 INTERFACE mbedtls_alt/source/hal/aes_aes_alt.c)
    target_sources(STMicroelectronics_stfcf_0_6_0 INTERFACE mbedtls_alt/source/hal/aes_ccm_alt.c)
    target_sources(STMicroelectronics_stfcf_0_6_0 INTERFACE mbedtls_alt/source/hal/aes_gcm_alt.c)
    target_sources(STMicroelectronics_stfcf_0_6_0 INTERFACE mbedtls_alt/source/hal/cryp_aes_alt.c)
    target_sources(STMicroelectronics_stfcf_0_6_0 INTERFACE mbedtls_alt/source/hal/cryp_ccm_alt.c)
    target_sources(STMicroelectronics_stfcf_0_6_0 INTERFACE mbedtls_alt/source/hal/cryp_gcm_alt.c)
    target_sources(STMicroelectronics_stfcf_0_6_0 INTERFACE mbedtls_alt/source/hal/ecdh_alt.c)
    target_sources(STMicroelectronics_stfcf_0_6_0 INTERFACE mbedtls_alt/source/hal/ecdsa_alt.c)
    target_sources(STMicroelectronics_stfcf_0_6_0 INTERFACE mbedtls_alt/source/hal/ecp_alt.c)
    target_sources(STMicroelectronics_stfcf_0_6_0 INTERFACE mbedtls_alt/source/hal/ecp_curves_alt.c)
    target_sources(STMicroelectronics_stfcf_0_6_0 INTERFACE mbedtls_alt/source/hal/entropy_hardware_alt.c)
    target_sources(STMicroelectronics_stfcf_0_6_0 INTERFACE mbedtls_alt/source/hal/rsa_alt.c)
    target_sources(STMicroelectronics_stfcf_0_6_0 INTERFACE mbedtls_alt/source/hal/sha1_alt.c)
    target_sources(STMicroelectronics_stfcf_0_6_0 INTERFACE mbedtls_alt/source/hal/sha256_alt.c)
  endif()
endif()

if(CMSIS_USE_Security_STFCF_KWE_0_6_0)  # Key Wrapping Engine
  message(DEBUG "Using component Security_STFCF_KWE_0_6_0")
  if(STMicroelectronics.stfcf.0.6.0:KWE_condition)
    target_compile_definitions(STMicroelectronics_stfcf_0_6_0 INTERFACE -DCMSIS_USE_Security_STFCF_KWE_0_6_0=1)
    target_include_directories(STMicroelectronics_stfcf_0_6_0 INTERFACE kwe/core)
    target_include_directories(STMicroelectronics_stfcf_0_6_0 INTERFACE kwe/interface)
    target_sources(STMicroelectronics_stfcf_0_6_0 INTERFACE kwe/README.md)
    target_sources(STMicroelectronics_stfcf_0_6_0 INTERFACE kwe/core/kwe_core.c)
    target_sources(STMicroelectronics_stfcf_0_6_0 INTERFACE kwe/interface/kwe_psa_driver_interface.c)
    target_sources(STMicroelectronics_stfcf_0_6_0 INTERFACE kwe/interface/kwe_psa_driver_key_management.c)
  endif()
endif()

