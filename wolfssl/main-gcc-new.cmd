@echo off

del .\a.exe

start /WAIT /B gcc main.c -DWOLFSSL_USER_SETTINGS -I. -Iwolfssl-5.7.2^
    -M
    wolfssl-5.7.2\src\crl.c^
    wolfssl-5.7.2\src\internal.c^
    wolfssl-5.7.2\src\keys.c^
    wolfssl-5.7.2\src\ocsp.c^
    wolfssl-5.7.2\src\sniffer.c^
    wolfssl-5.7.2\src\ssl.c^
    wolfssl-5.7.2\src\tls.c^
    wolfssl-5.7.2\src\tls13.c^
    wolfssl-5.7.2\src\wolfio.c^
    ^
    wolfssl-5.7.2\wolfcrypt\src\aes.c^
    wolfssl-5.7.2\wolfcrypt\src\asn.c^
    wolfssl-5.7.2\wolfcrypt\src\coding.c^
    wolfssl-5.7.2\wolfcrypt\src\curve25519.c^
    wolfssl-5.7.2\wolfcrypt\src\ecc.c^
    wolfssl-5.7.2\wolfcrypt\src\ed25519.c^
    wolfssl-5.7.2\wolfcrypt\src\error.c^
    wolfssl-5.7.2\wolfcrypt\src\fe_operations.c^
    wolfssl-5.7.2\wolfcrypt\src\ge_operations.c^
    wolfssl-5.7.2\wolfcrypt\src\hash.c^
    wolfssl-5.7.2\wolfcrypt\src\hmac.c^
    wolfssl-5.7.2\wolfcrypt\src\kdf.c^
    wolfssl-5.7.2\wolfcrypt\src\md5.c^
    wolfssl-5.7.2\wolfcrypt\src\memory.c^
    wolfssl-5.7.2\wolfcrypt\src\pwdbased.c^
    wolfssl-5.7.2\wolfcrypt\src\random.c^
    wolfssl-5.7.2\wolfcrypt\src\rsa.c^
    wolfssl-5.7.2\wolfcrypt\src\sha.c^
    wolfssl-5.7.2\wolfcrypt\src\sha256.c^
    wolfssl-5.7.2\wolfcrypt\src\sha512.c^
    wolfssl-5.7.2\wolfcrypt\src\sp_int.c^
    wolfssl-5.7.2\wolfcrypt\src\wc_encrypt.c^
    wolfssl-5.7.2\wolfcrypt\src\wc_port.c^
    wolfssl-5.7.2\wolfcrypt\src\wolfmath.c^
    -lws2_32
