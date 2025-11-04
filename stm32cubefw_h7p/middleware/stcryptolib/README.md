# STM32 Cryptographic Libraries (STCryptoLib)

> **Copyright (c) 2025 STMicroelectronics. All rights reserved.**  
> This software is licensed under terms that can be found in the [LICENSE.md] file in the root directory of this software component.  
> If no LICENSE file comes with this software, it is provided AS-IS.

This Pack contains the header files of the Cryptographic services exposed by the STM32 Cryptographic libraries.
It contains Configuration & Code generation of the configuration file through STM32CubeMX2.

## Cryptographic Services Provided

- **AES-128/192/256** Encryption/Decryption in ECB, CBC, CFB, CTR, OFB, XTS, KeyWrap modes
- **AES-128/192/256 CCM/GCM** Authenticated Encryption/Decryption
- **SM4** Encryption/Decryption in ECB, CBC, CFB, CTR, OFB modes
- **ChaCha20-Poly1305** Authenticated Encryption/Decryption
- **CTR-DRBG** based on AES-128/256
- **SHA1/SHA2/SHA3/SHAKE/SM3** Hash functions
- **HMAC/CMAC/KMAC** Message Authentication Code functions
- **RSA PKCS#1 v1.5/v2.2** Signature Creation/Verification and Encryption/Decryption functions
- **ECDSA/EdDSA/SM2** Key Generation and Signature Creation/Verification functions
- **ECDH** Key Exchange functions

## Third-Party Software Components

Some parts of the STM32 Cryptographic libraries have been inspired by third-party software components from:

- **muNaCl** by Michael Hutter, Peter Schwabe, Björn Haase, and Ana Helena Sánchez
- **libtomcrypt** by T. St-Denis
- **eXtended Keccak Code Package** by Guido Bertoni, Joan Daemen, Seth Hoffert, Michaël Peeters, Gilles Van Assche, and Ronny Van Keer
- **poly1305-donna** by Andrew Moon
- **chacha-ref.c** by D. J. Bernstein

## See also

More details from the online documentation: https://wiki.st.com/stm32mcu/wiki/Security:Introduction_to_the_cryptographic_library_with_STM32

