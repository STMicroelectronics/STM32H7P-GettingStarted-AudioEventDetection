/**
  ******************************************************************************
  * @file    ecdsa_alt.c
  * @brief   Implementation of mbedtls_alt ECDSA module
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
  * All rights reserved.
  * Copyright The Mbed TLS Contributors
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */

/**
  * Elliptic curve DSA sign and verify functions
  *
  * This file implements ECDSA sign and verify based on STM32 crypto library.
  */

/* Includes ------------------------------------------------------------------*/
#include "common.h"

#if defined(MBEDTLS_ECDSA_C)
#include "mbedtls/ecdsa.h"
#include <string.h>
#include "mbedtls/platform.h"
#include "mbedtls/platform_util.h"
#include "mbedtls/error.h"

#if defined(MBEDTLS_STCRYPTOLIB_ECDSA_ALT)
#include "cmox_crypto.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
#define ST_PRIVKEY_MAX_SIZE   32
#define ST_BUFFER_SIZE        2000

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/* Convert return value from STCryptoLib to MBED for ecc */
static int ecc_mbed_return_value(cmox_ecc_retval_t retval)
{
  int ret = 0; /* Return value */

  switch (retval)
  {
    case CMOX_ECC_SUCCESS:
      ret = 0;
      break;

    case CMOX_ECC_ERR_INTERNAL:
      ret = MBEDTLS_ERR_PLATFORM_HW_ACCEL_FAILED;
      break;

    case CMOX_ECC_ERR_BAD_PARAMETERS:
      ret = MBEDTLS_ERR_ECP_BAD_INPUT_DATA;
      break;

    case CMOX_ECC_ERR_INVALID_PUBKEY:
      ret = MBEDTLS_ERR_ECP_INVALID_KEY;
      break;

    case CMOX_ECC_ERR_INVALID_SIGNATURE:
      ret = MBEDTLS_ERR_ECP_VERIFY_FAILED;
      break;

    case CMOX_ECC_ERR_WRONG_RANDOM:
      ret = MBEDTLS_ERR_ECP_BAD_INPUT_DATA;
      break;

    case CMOX_ECC_ERR_MEMORY_FAIL:
      ret = MBEDTLS_ERR_MPI_ALLOC_FAILED;
      break;

    case CMOX_ECC_ERR_MATHCURVE_MISMATCH:
      ret = MBEDTLS_ERR_ECP_BAD_INPUT_DATA;
      break;

    case CMOX_ECC_ERR_ALGOCURVE_MISMATCH:
      ret = MBEDTLS_ERR_ECP_BAD_INPUT_DATA;
      break;

    case CMOX_ECC_AUTH_SUCCESS:
      ret = (0);
      break;

    case CMOX_ECC_AUTH_FAIL:
      ret = MBEDTLS_ERR_ECP_VERIFY_FAILED;
      break;

    default :
      ret = MBEDTLS_ERR_ERROR_GENERIC_ERROR;
      break;
  }
  return ret;
}

static cmox_ecc_impl_t ecdsa_alt_curveId(mbedtls_ecp_group_id grp)
{
  cmox_ecc_impl_t retval = 0; /* Return value */

  /* Select correct hash id */
  switch (grp)
  {
    case MBEDTLS_ECP_DP_SECP224R1:
      retval = CMOX_ECC_CURVE_SECP224R1;
      break;

    case MBEDTLS_ECP_DP_SECP256R1:
      retval = CMOX_ECC_CURVE_SECP256R1;
      break;

    case MBEDTLS_ECP_DP_SECP384R1:
      retval = CMOX_ECC_CURVE_SECP384R1;
      break;

    case MBEDTLS_ECP_DP_SECP521R1:
      retval = CMOX_ECC_CURVE_SECP521R1;
      break;

    case MBEDTLS_ECP_DP_BP256R1:
      retval = CMOX_ECC_CURVE_BPP256R1;
      break;

    case MBEDTLS_ECP_DP_BP384R1:
      retval = CMOX_ECC_CURVE_BPP384R1;
      break;

    case MBEDTLS_ECP_DP_BP512R1:
      retval = CMOX_ECC_CURVE_BPP512R1;
      break;

    case MBEDTLS_ECP_DP_SECP256K1:
      retval = CMOX_ECC_CURVE_SECP256K1;
      break;

    default :
      retval = 0;  /* Not supported by STCryptoLib */
      break;
  }
  return retval;
}

#if defined(MBEDTLS_ECDSA_SIGN_ALT)

/*
 * Compute ECDSA signature of a hashed message
 */
int mbedtls_ecdsa_sign(mbedtls_ecp_group *grp, mbedtls_mpi *r, mbedtls_mpi *s,
                       const mbedtls_mpi *d,
                       const unsigned char *buf, size_t blen,
                       int (*f_rng)(void *, unsigned char *, size_t),
                       void *p_rng)
{
  int ret = MBEDTLS_ERR_ERROR_CORRUPTION_DETECTED;
  cmox_rsa_retval_t retval;             /* STCryptoLib return value */
  cmox_ecc_impl_t curve_id = 0;         /* Curve ID for STCryptoLib */
  uint8_t *p_working_buffer = NULL;     /* ECDSA working buffer for STCryptoLib */
  uint16_t buff_size = ST_BUFFER_SIZE;  /* Max space needed by STCryptoLib */
  cmox_ecc_handle_t ecc_ctx;            /* Ecc ctx for STCryptoLib */
  cmox_init_arg_t init_arg;             /* Init structure for STCryptoLib */
  uint8_t a_private_key[ST_PRIVKEY_MAX_SIZE] = {0}; /* Private key */
  uint8_t priv_key_size;                /* Private key size */
  uint8_t computed_signature[2 * ST_PRIVKEY_MAX_SIZE] = {0}; /*Signature R + S*/
  size_t computed_size; /* Size of the calculated signature by STCryptoLib */
  mbedtls_mpi k;        /* K, the random with mbed format */
  uint8_t a_k_binary[ST_PRIVKEY_MAX_SIZE] = {0}; /* K as array of bytes */
  uint32_t k_size = 0; /* Size of K */
  uint8_t pos = 0;     /* Internal counter for K derivation */

  /* Fail cleanly on curves such as Curve25519 that can't be used for ECDSA */
  if (! mbedtls_ecdsa_can_do(grp->id) || grp->N.MBEDTLS_PRIVATE(p) == NULL)
  {
    return MBEDTLS_ERR_ECP_BAD_INPUT_DATA;
  }

  /* Make sure d is in range 1..n-1 */
  if (mbedtls_mpi_cmp_int(d, 1) < 0
      || mbedtls_mpi_cmp_mpi(d, &grp->N) >= 0)
  {
    return MBEDTLS_ERR_ECP_INVALID_KEY;
  }

  /* Select curve id */
  curve_id = ecdsa_alt_curveId(grp->id);

  if (curve_id == 0)
  {
    return MBEDTLS_ERR_PLATFORM_FEATURE_UNSUPPORTED;
  }

  /* Allocate the working buffer for the STCryptoLib */
  p_working_buffer = mbedtls_calloc(buff_size, sizeof(uint8_t));
  if (p_working_buffer == NULL)
  {
    return MBEDTLS_ERR_MPI_ALLOC_FAILED;
  }

  mbedtls_mpi_init(&k);

  /* Generate the random of length random_length */
  ret = mbedtls_ecp_gen_privkey(grp, &k, f_rng, p_rng);
  if (ret != 0)
  {
    goto exit;
  }

  k_size = grp->nbits / 8U ;

  ret = mbedtls_mpi_write_binary(&k, a_k_binary, k_size);
  if (ret != 0)
  {
    goto exit;
  }

  /* StyCryptoLib use k-1 and not k */
  pos = k_size - 1u;
  a_k_binary[pos]--;
  if (a_k_binary[k_size - 1u] == 0xFFu)
  {
    do
    {
      pos--; /* Manage overflow */
      a_k_binary[pos]--;
    } while ((a_k_binary[pos] == 0xFFu) && (pos > 1));
  }

  /* Init the STCryptoLib */
  init_arg.target = CMOX_INIT_TARGET_AUTO;
  init_arg.pArg = NULL;
  cmox_initialize(&init_arg);

  cmox_ecc_construct(&ecc_ctx, CMOX_ECC256_MATH_FUNCS, p_working_buffer,
                     buff_size);

  /* Use mbedtls_mpi_size for the size and not sizeof(d) for avoid zero
     padding in output buffer. */
  priv_key_size =  mbedtls_mpi_size(d);
  /* Convert private key from mpi to binary */
  if (mbedtls_mpi_size(d) > sizeof(a_private_key))
  {
    ret = MBEDTLS_ERR_MPI_BUFFER_TOO_SMALL;
    goto exit;
  }
  ret = mbedtls_mpi_write_binary(d, a_private_key, priv_key_size);
  if (ret != 0)
  {
    goto exit;
  }

  retval = cmox_ecdsa_sign(&ecc_ctx, curve_id, a_k_binary, k_size,
                           a_private_key, priv_key_size,
                           buf, blen, computed_signature, &computed_size);

  if (retval != CMOX_ECC_SUCCESS)
  {
    ret = ecc_mbed_return_value(retval);
    goto exit;
  }

  /* Convert the signature into mpi format */
  ret = mbedtls_mpi_read_binary(r, &computed_signature[0], computed_size / 2);
  if (ret == 0)
  {
    ret = mbedtls_mpi_read_binary(s, &computed_signature[computed_size / 2],
                                  computed_size / 2);
  }

exit:
  mbedtls_free(p_working_buffer);
  return ret;
}

#endif /* MBEDTLS_ECDSA_SIGN_ALT*/

#if defined(MBEDTLS_ECDSA_VERIFY_ALT)


/*
 * Verify ECDSA signature of hashed message
 */
int mbedtls_ecdsa_verify(mbedtls_ecp_group *grp, const unsigned char *buf,
                         size_t blen, const mbedtls_ecp_point *Q,
                         const mbedtls_mpi *r, const mbedtls_mpi *s)
{
  int ret = MBEDTLS_ERR_ERROR_CORRUPTION_DETECTED;
  cmox_rsa_retval_t retval;             /* STCryptoLib return value */
  cmox_ecc_impl_t curve_id = 0;         /* Curve ID for STCryptoLib */
  uint8_t *p_working_buffer = NULL;     /* ECDSA working buffer for STCryptoLib */
  uint16_t buff_size = ST_BUFFER_SIZE;  /* Max space needed by STCryptoLib */
  cmox_ecc_handle_t ecc_ctx;            /* Ecc ctx for STCryptoLib */
  cmox_init_arg_t init_arg;             /* Init structure for STCryptoLib */
  uint32_t fault_check = CMOX_ECC_AUTH_FAIL;  /* Fault check variable */
  uint8_t a_public_key[2 * ST_PRIVKEY_MAX_SIZE + 1u] = {0}; /* Public key X + Y */
  uint8_t known_signature[2 * ST_PRIVKEY_MAX_SIZE] = {0}; /* Signature X + Y */
  size_t public_key_size; /* Length of public key in bytes set by mbed */

  /* Fail cleanly on curves such as Curve25519 that can't be used for ECDSA */
  if (grp->G.MBEDTLS_PRIVATE(Y).MBEDTLS_PRIVATE(p) == NULL)
  {
    return MBEDTLS_ERR_ECP_BAD_INPUT_DATA;
  }

  /* Make sure r and s are in range 1..n-1 */
  if (mbedtls_mpi_cmp_int(r, 1) < 0
      || mbedtls_mpi_cmp_mpi(r, &grp->N) >= 0
      || mbedtls_mpi_cmp_int(s, 1) < 0
      || mbedtls_mpi_cmp_mpi(s, &grp->N) >= 0)
  {
    return MBEDTLS_ERR_ECP_VERIFY_FAILED;
  }

  /* Select curve id */
  curve_id = ecdsa_alt_curveId(grp->id);

  if (curve_id == 0)
  {
    return MBEDTLS_ERR_PLATFORM_FEATURE_UNSUPPORTED;
  }

  /* Allocate the working buffer for the STCryptoLib */
  p_working_buffer = mbedtls_calloc(buff_size, sizeof(uint8_t));
  if (p_working_buffer == NULL)
  {
    return MBEDTLS_ERR_MPI_ALLOC_FAILED;
  }

  /* Init the STCryptoLib */
  init_arg.target = CMOX_INIT_TARGET_AUTO;
  init_arg.pArg = NULL;
  cmox_initialize(&init_arg);

  cmox_ecc_construct(&ecc_ctx, CMOX_ECC256_MATH_FUNCS, p_working_buffer,
                     buff_size);

  /* Convert public key to an array */
  mbedtls_ecp_point_write_binary(grp, Q, MBEDTLS_ECP_PF_UNCOMPRESSED,
                                 &public_key_size, a_public_key,
                                 sizeof(a_public_key));

  /* Convert signature R+S from mpi to array of bytes */
  ret = mbedtls_mpi_write_binary(r, &known_signature[0], ST_PRIVKEY_MAX_SIZE);
  ret |= mbedtls_mpi_write_binary(s, &known_signature[ST_PRIVKEY_MAX_SIZE],
                                  ST_PRIVKEY_MAX_SIZE);
  if (ret != 0)
  {
    goto cleanup;
  }

  public_key_size--; /* Remove first byte at 0x04, it's a byte for format */

  retval = cmox_ecdsa_verify(&ecc_ctx, curve_id, &a_public_key[1],
                             public_key_size, buf, blen, known_signature,
                             sizeof(known_signature), &fault_check);


  if (retval != CMOX_ECC_AUTH_SUCCESS)
  {
    /* Problem occur return retval value,
       fault check could be a dirty value */
    ret = ecc_mbed_return_value(retval);
  }
  else
  {
    /* retval is good, it's not means verify success,
       check the fault check to conclude */
    ret = ecc_mbed_return_value(fault_check);
  }


cleanup:
  mbedtls_free(p_working_buffer);
  return ret;
}

#endif /* MBEDTLS_ECDSA_VERIFY_ALT*/
#endif /* MBEDTLS_STCRYPTOLIB_ECDSA_ALT */
#endif /* MBEDTLS_ECDSA_C */
