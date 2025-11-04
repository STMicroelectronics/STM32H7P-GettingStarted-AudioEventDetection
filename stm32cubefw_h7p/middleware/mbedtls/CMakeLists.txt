# origin-pack: STMicroelectronics::mbedtls@0.9.0
# created-by: conversion-manager@0.0.64
project(STMicroelectronics_mbedtls_0_9_0)
cmake_minimum_required(VERSION 3.20)
add_library(STMicroelectronics_mbedtls_0_9_0 INTERFACE)

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
if(CMSIS_ENTIRE_STMicroelectronics_mbedtls_0_9_0)
  set(CMSIS_USE_Security_MbedTLS_PSA_API_3_6_4 true)
  set(CMSIS_USE_Security_MbedTLS_MBED_API_3_6_4 true)
  set(CMSIS_USE_Security_MbedTLS_Core_3_6_4 true)
  set(CMSIS_USE_Security_MbedTLS_SW_Crypto_3_6_4 true)
  set(CMSIS_USE_Security_MbedTLS_Persistent_Storage_3_6_4 true)
  set(CMSIS_USE_Security_MbedTLS_Secure_Element_3_6_4 true)
endif()

# All conditions used by this package

# condition: STMicroelectronics.mbedtls.0.9.0
# description: 
if((CMSIS_Dname MATCHES "STM32.*" AND CMSIS_Dvendor STREQUAL "STMicroelectronics:13"))
  set(STMicroelectronics.mbedtls.0.9.0 true)
  message(DEBUG "CMSIS condition STMicroelectronics.mbedtls.0.9.0 enabled")
endif()


# condition: STMicroelectronics.mbedtls.0.9.0:MBED interface conditions
# description: Ensure Mbed TLS are satisfied
set(STMicroelectronics.mbedtls.0.9.0:MBED_interface_conditions true)
message(DEBUG "CMSIS condition STMicroelectronics.mbedtls.0.9.0:MBED_interface_conditions enabled")


# condition: STMicroelectronics.mbedtls.0.9.0:PSA interface conditions
# description: Ensure PSA APIs are satisfied
set(STMicroelectronics.mbedtls.0.9.0:PSA_interface_conditions true)
message(DEBUG "CMSIS condition STMicroelectronics.mbedtls.0.9.0:PSA_interface_conditions enabled")


# condition: STMicroelectronics.mbedtls.0.9.0:Persistent Storage conditions
# description: Ensure Mbed TLS APIs are selected before
set(STMicroelectronics.mbedtls.0.9.0:Persistent_Storage_conditions true)
message(DEBUG "CMSIS condition STMicroelectronics.mbedtls.0.9.0:Persistent_Storage_conditions enabled")


# condition: STMicroelectronics.mbedtls.0.9.0:ST Secure Element conditions
# description: Ensure Mbed TLS APIs are selected before
set(STMicroelectronics.mbedtls.0.9.0:ST_Secure_Element_conditions true)
message(DEBUG "CMSIS condition STMicroelectronics.mbedtls.0.9.0:ST_Secure_Element_conditions enabled")


# condition: STMicroelectronics.mbedtls.0.9.0:SW Crypto conditions
# description: Ensure Mbed TLS APIs are selected before
set(STMicroelectronics.mbedtls.0.9.0:SW_Crypto_conditions true)
message(DEBUG "CMSIS condition STMicroelectronics.mbedtls.0.9.0:SW_Crypto_conditions enabled")

# Files and components in this package
if(CMSIS_USE_Security_MbedTLS_PSA_API_3_6_4)  # PSA crypto interface
  message(DEBUG "Using component Security_MbedTLS_PSA_API_3_6_4")
  if(STMicroelectronics.mbedtls.0.9.0:PSA_interface_conditions)
    target_compile_definitions(STMicroelectronics_mbedtls_0_9_0 INTERFACE -DCMSIS_USE_Security_MbedTLS_PSA_API_3_6_4=1)
    target_include_directories(STMicroelectronics_mbedtls_0_9_0 INTERFACE include/psa)
    target_include_directories(STMicroelectronics_mbedtls_0_9_0 INTERFACE include/psa/)
    target_include_directories(STMicroelectronics_mbedtls_0_9_0 INTERFACE library)
    target_include_directories(STMicroelectronics_mbedtls_0_9_0 INTERFACE library/)
    target_sources(STMicroelectronics_mbedtls_0_9_0 INTERFACE library/psa_crypto.c)
    target_sources(STMicroelectronics_mbedtls_0_9_0 INTERFACE library/psa_crypto_aead.c)
    target_sources(STMicroelectronics_mbedtls_0_9_0 INTERFACE library/psa_crypto_cipher.c)
    target_sources(STMicroelectronics_mbedtls_0_9_0 INTERFACE library/psa_crypto_client.c)
    target_sources(STMicroelectronics_mbedtls_0_9_0 INTERFACE library/psa_crypto_driver_wrappers_no_static.c)
    target_sources(STMicroelectronics_mbedtls_0_9_0 INTERFACE library/psa_crypto_ecp.c)
    target_sources(STMicroelectronics_mbedtls_0_9_0 INTERFACE library/psa_crypto_hash.c)
    target_sources(STMicroelectronics_mbedtls_0_9_0 INTERFACE library/psa_crypto_mac.c)
    target_sources(STMicroelectronics_mbedtls_0_9_0 INTERFACE library/psa_crypto_pake.c)
    target_sources(STMicroelectronics_mbedtls_0_9_0 INTERFACE library/psa_crypto_rsa.c)
    target_sources(STMicroelectronics_mbedtls_0_9_0 INTERFACE library/psa_crypto_slot_management.c)
    target_sources(STMicroelectronics_mbedtls_0_9_0 INTERFACE library/psa_its_file.c)
    target_sources(STMicroelectronics_mbedtls_0_9_0 INTERFACE library/psa_util.c)
  endif()
endif()

if(CMSIS_USE_Security_MbedTLS_MBED_API_3_6_4)  # Legacy crypto interface
  message(DEBUG "Using component Security_MbedTLS_MBED_API_3_6_4")
  if(STMicroelectronics.mbedtls.0.9.0:MBED_interface_conditions)
    target_compile_definitions(STMicroelectronics_mbedtls_0_9_0 INTERFACE -DCMSIS_USE_Security_MbedTLS_MBED_API_3_6_4=1)
    target_include_directories(STMicroelectronics_mbedtls_0_9_0 INTERFACE configs/)
    target_include_directories(STMicroelectronics_mbedtls_0_9_0 INTERFACE include/mbedtls)
    target_include_directories(STMicroelectronics_mbedtls_0_9_0 INTERFACE include/mbedtls/)
  endif()
endif()

if(CMSIS_USE_Security_MbedTLS_Core_3_6_4)  # Mbed TLS core implementations
  message(DEBUG "Using component Security_MbedTLS_Core_3_6_4")
  target_compile_definitions(STMicroelectronics_mbedtls_0_9_0 INTERFACE -DCMSIS_USE_Security_MbedTLS_Core_3_6_4=1)
  target_include_directories(STMicroelectronics_mbedtls_0_9_0 INTERFACE include/)
  target_include_directories(STMicroelectronics_mbedtls_0_9_0 INTERFACE library)
  target_sources(STMicroelectronics_mbedtls_0_9_0 INTERFACE library/asn1parse.c)
  target_sources(STMicroelectronics_mbedtls_0_9_0 INTERFACE library/asn1write.c)
  target_sources(STMicroelectronics_mbedtls_0_9_0 INTERFACE library/base64.c)
  target_sources(STMicroelectronics_mbedtls_0_9_0 INTERFACE library/bignum.c)
  target_sources(STMicroelectronics_mbedtls_0_9_0 INTERFACE library/bignum_core.c)
  target_sources(STMicroelectronics_mbedtls_0_9_0 INTERFACE library/cipher.c)
  target_sources(STMicroelectronics_mbedtls_0_9_0 INTERFACE library/cipher_wrap.c)
  target_sources(STMicroelectronics_mbedtls_0_9_0 INTERFACE library/constant_time.c)
  target_sources(STMicroelectronics_mbedtls_0_9_0 INTERFACE library/ctr_drbg.c)
  target_sources(STMicroelectronics_mbedtls_0_9_0 INTERFACE library/debug.c)
  target_sources(STMicroelectronics_mbedtls_0_9_0 INTERFACE library/entropy.c)
  target_sources(STMicroelectronics_mbedtls_0_9_0 INTERFACE library/entropy_poll.c)
  target_sources(STMicroelectronics_mbedtls_0_9_0 INTERFACE library/error.c)
  target_sources(STMicroelectronics_mbedtls_0_9_0 INTERFACE library/hkdf.c)
  target_sources(STMicroelectronics_mbedtls_0_9_0 INTERFACE library/hmac_drbg.c)
  target_sources(STMicroelectronics_mbedtls_0_9_0 INTERFACE library/md.c)
  target_sources(STMicroelectronics_mbedtls_0_9_0 INTERFACE library/memory_buffer_alloc.c)
  target_sources(STMicroelectronics_mbedtls_0_9_0 INTERFACE library/oid.c)
  target_sources(STMicroelectronics_mbedtls_0_9_0 INTERFACE library/pem.c)
  target_sources(STMicroelectronics_mbedtls_0_9_0 INTERFACE library/pk.c)
  target_sources(STMicroelectronics_mbedtls_0_9_0 INTERFACE library/pk_ecc.c)
  target_sources(STMicroelectronics_mbedtls_0_9_0 INTERFACE library/pk_wrap.c)
  target_sources(STMicroelectronics_mbedtls_0_9_0 INTERFACE library/pkcs12.c)
  target_sources(STMicroelectronics_mbedtls_0_9_0 INTERFACE library/pkcs5.c)
  target_sources(STMicroelectronics_mbedtls_0_9_0 INTERFACE library/pkparse.c)
  target_sources(STMicroelectronics_mbedtls_0_9_0 INTERFACE library/pkwrite.c)
  target_sources(STMicroelectronics_mbedtls_0_9_0 INTERFACE library/platform.c)
  target_sources(STMicroelectronics_mbedtls_0_9_0 INTERFACE library/platform_util.c)
  target_sources(STMicroelectronics_mbedtls_0_9_0 INTERFACE library/psa_crypto_ffdh.c)
  target_sources(STMicroelectronics_mbedtls_0_9_0 INTERFACE library/rsa_alt_helpers.c)
  target_sources(STMicroelectronics_mbedtls_0_9_0 INTERFACE library/ssl_cache.c)
  target_sources(STMicroelectronics_mbedtls_0_9_0 INTERFACE library/ssl_ciphersuites.c)
  target_sources(STMicroelectronics_mbedtls_0_9_0 INTERFACE library/ssl_client.c)
  target_sources(STMicroelectronics_mbedtls_0_9_0 INTERFACE library/ssl_cookie.c)
  target_sources(STMicroelectronics_mbedtls_0_9_0 INTERFACE library/ssl_debug_helpers_generated.c)
  target_sources(STMicroelectronics_mbedtls_0_9_0 INTERFACE library/ssl_msg.c)
  target_sources(STMicroelectronics_mbedtls_0_9_0 INTERFACE library/ssl_ticket.c)
  target_sources(STMicroelectronics_mbedtls_0_9_0 INTERFACE library/ssl_tls.c)
  target_sources(STMicroelectronics_mbedtls_0_9_0 INTERFACE library/ssl_tls12_client.c)
  target_sources(STMicroelectronics_mbedtls_0_9_0 INTERFACE library/ssl_tls12_server.c)
  target_sources(STMicroelectronics_mbedtls_0_9_0 INTERFACE library/ssl_tls13_client.c)
  target_sources(STMicroelectronics_mbedtls_0_9_0 INTERFACE library/ssl_tls13_generic.c)
  target_sources(STMicroelectronics_mbedtls_0_9_0 INTERFACE library/ssl_tls13_keys.c)
  target_sources(STMicroelectronics_mbedtls_0_9_0 INTERFACE library/ssl_tls13_server.c)
  target_sources(STMicroelectronics_mbedtls_0_9_0 INTERFACE library/threading.c)
  target_sources(STMicroelectronics_mbedtls_0_9_0 INTERFACE library/timing.c)
  target_sources(STMicroelectronics_mbedtls_0_9_0 INTERFACE library/version.c)
  target_sources(STMicroelectronics_mbedtls_0_9_0 INTERFACE library/version_features.c)
  target_sources(STMicroelectronics_mbedtls_0_9_0 INTERFACE library/x509.c)
  target_sources(STMicroelectronics_mbedtls_0_9_0 INTERFACE library/x509_create.c)
  target_sources(STMicroelectronics_mbedtls_0_9_0 INTERFACE library/x509_crl.c)
  target_sources(STMicroelectronics_mbedtls_0_9_0 INTERFACE library/x509_crt.c)
  target_sources(STMicroelectronics_mbedtls_0_9_0 INTERFACE library/x509_csr.c)
  target_sources(STMicroelectronics_mbedtls_0_9_0 INTERFACE library/x509write.c)
  target_sources(STMicroelectronics_mbedtls_0_9_0 INTERFACE library/x509write_crt.c)
  target_sources(STMicroelectronics_mbedtls_0_9_0 INTERFACE library/x509write_csr.c)
endif()

if(CMSIS_USE_Security_MbedTLS_SW_Crypto_3_6_4)  # Mbed TLS SW crypto implementations
  message(DEBUG "Using component Security_MbedTLS_SW_Crypto_3_6_4")
  if(STMicroelectronics.mbedtls.0.9.0:SW_Crypto_conditions)
    target_compile_definitions(STMicroelectronics_mbedtls_0_9_0 INTERFACE -DCMSIS_USE_Security_MbedTLS_SW_Crypto_3_6_4=1)
    target_include_directories(STMicroelectronics_mbedtls_0_9_0 INTERFACE include/)
    target_sources(STMicroelectronics_mbedtls_0_9_0 INTERFACE library/aes.c)
    target_sources(STMicroelectronics_mbedtls_0_9_0 INTERFACE library/aria.c)
    target_sources(STMicroelectronics_mbedtls_0_9_0 INTERFACE library/camellia.c)
    target_sources(STMicroelectronics_mbedtls_0_9_0 INTERFACE library/ccm.c)
    target_sources(STMicroelectronics_mbedtls_0_9_0 INTERFACE library/chacha20.c)
    target_sources(STMicroelectronics_mbedtls_0_9_0 INTERFACE library/chachapoly.c)
    target_sources(STMicroelectronics_mbedtls_0_9_0 INTERFACE library/cmac.c)
    target_sources(STMicroelectronics_mbedtls_0_9_0 INTERFACE library/des.c)
    target_sources(STMicroelectronics_mbedtls_0_9_0 INTERFACE library/dhm.c)
    target_sources(STMicroelectronics_mbedtls_0_9_0 INTERFACE library/ecdh.c)
    target_sources(STMicroelectronics_mbedtls_0_9_0 INTERFACE library/ecdsa.c)
    target_sources(STMicroelectronics_mbedtls_0_9_0 INTERFACE library/ecjpake.c)
    target_sources(STMicroelectronics_mbedtls_0_9_0 INTERFACE library/ecp.c)
    target_sources(STMicroelectronics_mbedtls_0_9_0 INTERFACE library/ecp_curves.c)
    target_sources(STMicroelectronics_mbedtls_0_9_0 INTERFACE library/gcm.c)
    target_sources(STMicroelectronics_mbedtls_0_9_0 INTERFACE library/md5.c)
    target_sources(STMicroelectronics_mbedtls_0_9_0 INTERFACE library/nist_kw.c)
    target_sources(STMicroelectronics_mbedtls_0_9_0 INTERFACE library/poly1305.c)
    target_sources(STMicroelectronics_mbedtls_0_9_0 INTERFACE library/ripemd160.c)
    target_sources(STMicroelectronics_mbedtls_0_9_0 INTERFACE library/rsa.c)
    target_sources(STMicroelectronics_mbedtls_0_9_0 INTERFACE library/sha1.c)
    target_sources(STMicroelectronics_mbedtls_0_9_0 INTERFACE library/sha256.c)
    target_sources(STMicroelectronics_mbedtls_0_9_0 INTERFACE library/sha3.c)
    target_sources(STMicroelectronics_mbedtls_0_9_0 INTERFACE library/sha512.c)
  endif()
endif()

if(CMSIS_USE_Security_MbedTLS_Persistent_Storage_3_6_4)  # Storage
  message(DEBUG "Using component Security_MbedTLS_Persistent_Storage_3_6_4")
  if(STMicroelectronics.mbedtls.0.9.0:Persistent_Storage_conditions)
    target_compile_definitions(STMicroelectronics_mbedtls_0_9_0 INTERFACE -DCMSIS_USE_Security_MbedTLS_Persistent_Storage_3_6_4=1)
    target_include_directories(STMicroelectronics_mbedtls_0_9_0 INTERFACE include/)
    target_include_directories(STMicroelectronics_mbedtls_0_9_0 INTERFACE library)
    target_sources(STMicroelectronics_mbedtls_0_9_0 INTERFACE library/psa_crypto_storage.c)
  endif()
endif()

if(CMSIS_USE_Security_MbedTLS_Secure_Element_3_6_4)  # Secure Element
  message(DEBUG "Using component Security_MbedTLS_Secure_Element_3_6_4")
  if(STMicroelectronics.mbedtls.0.9.0:ST_Secure_Element_conditions)
    target_compile_definitions(STMicroelectronics_mbedtls_0_9_0 INTERFACE -DCMSIS_USE_Security_MbedTLS_Secure_Element_3_6_4=1)
    target_include_directories(STMicroelectronics_mbedtls_0_9_0 INTERFACE include/)
    target_include_directories(STMicroelectronics_mbedtls_0_9_0 INTERFACE library)
    target_sources(STMicroelectronics_mbedtls_0_9_0 INTERFACE library/psa_crypto_se.c)
  endif()
endif()

