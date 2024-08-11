/* options.h.in
 *
 * Copyright (C) 2006-2023 wolfSSL Inc.
 *
 * This file is part of wolfSSL.
 *
 * wolfSSL is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * wolfSSL is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1335, USA
 */


/* default blank options for autoconf */

#ifndef WOLFSSL_OPTIONS_H
#define WOLFSSL_OPTIONS_H


#ifdef __cplusplus
extern "C" {
#endif

// custom code:



#undef  TFM_NO_ASM
#define TFM_NO_ASM

#undef  WOLFSSL_NO_ASM
#define WOLFSSL_NO_ASM




#undef  SINGLE_THREADED
#define SINGLE_THREADED

#undef  TFM_TIMING_RESISTANT
#define TFM_TIMING_RESISTANT

#undef  ECC_TIMING_RESISTANT
#define ECC_TIMING_RESISTANT

#undef  WC_RSA_BLINDING
#define WC_RSA_BLINDING

#undef  WOLFSSL_SHA512
#define WOLFSSL_SHA512

#undef  WOLFSSL_SHA384
#define WOLFSSL_SHA384

#undef  HAVE_HKDF
#define HAVE_HKDF

#undef  NO_DSA
#define NO_DSA

#undef  HAVE_ECC
#define HAVE_ECC

#undef  ECC_SHAMIR
#define ECC_SHAMIR

#undef  HAVE_CURVE25519
#define HAVE_CURVE25519

#undef  NO_OLD_TLS
#define NO_OLD_TLS

#undef  WC_RSA_PSS
#define WC_RSA_PSS

#undef  WOLFSSL_PSS_LONG_SALT
#define WOLFSSL_PSS_LONG_SALT

#undef  NO_DH
#define NO_DH

#undef  WOLFSSL_ASN_TEMPLATE
#define WOLFSSL_ASN_TEMPLATE

#undef  WOLFSSL_ASN_PRINT
#define WOLFSSL_ASN_PRINT

#undef  WOLFSSL_NO_SHAKE128
#define WOLFSSL_NO_SHAKE128

#undef  WOLFSSL_NO_SHAKE256
#define WOLFSSL_NO_SHAKE256

#undef  HAVE_POLY1305
#define HAVE_POLY1305

#undef  NO_CHACHA_ASM
#define NO_CHACHA_ASM

#undef  HAVE_HASHDRBG
#define HAVE_HASHDRBG

#undef  NO_FILESYSTEM
#define NO_FILESYSTEM

#undef  HAVE_TLS_EXTENSIONS
#define HAVE_TLS_EXTENSIONS

#undef  HAVE_SUPPORTED_CURVES
#define HAVE_SUPPORTED_CURVES

#undef  HAVE_SUPPORTED_CURVES
#define HAVE_SUPPORTED_CURVES

#undef  WOLFSSL_TLS13
#define WOLFSSL_TLS13

#undef  HAVE_TLS_EXTENSIONS
#define HAVE_TLS_EXTENSIONS

#undef  HAVE_EXTENDED_MASTER
#define HAVE_EXTENDED_MASTER

#undef  NO_RC4
#define NO_RC4

#undef  HAVE_ENCRYPT_THEN_MAC
#define HAVE_ENCRYPT_THEN_MAC

#undef  NO_PSK
#define NO_PSK

#undef  NO_MD4
#define NO_MD4

#undef  NO_PKCS12
#define NO_PKCS12

#undef  NO_PWDBASED
#define NO_PWDBASED

#undef  WC_NO_ASYNC_THREADING
#define WC_NO_ASYNC_THREADING

#undef  HAVE_ED25519
#define HAVE_ED25519

#undef  NO_DES3
#define NO_DES3

#undef  NO_DES3_TLS_SUITES
#define NO_DES3_TLS_SUITES

#undef  GCM_TABLE_4BIT
#define GCM_TABLE_4BIT

#undef  HAVE_AESGCM
#define HAVE_AESGCM

#undef  HAVE_TLS_EXTENSIONS
#define HAVE_TLS_EXTENSIONS

// problems with msvc:
// #undef  HAVE___UINT128_T
// #define HAVE___UINT128_T 1

// problems with msvc:
// #undef  HAVE_WC_INTROSPECTION
// #define HAVE_WC_INTROSPECTION



// end of custom code

#ifdef __cplusplus
}
#endif


#endif /* WOLFSSL_OPTIONS_H */
