# sudo sh main.sh

# apt install libwolfssl-dev
rm a.out
# gcc main.c -I./wolfssl -L./wolfssl -lwolfssl


gcc main.c -Iwolfssl-5.7.2 \
    wolfssl-5.7.2/src/crl.c \
    wolfssl-5.7.2/src/internal.c \
    wolfssl-5.7.2/src/keys.c \
    wolfssl-5.7.2/src/ocsp.c \
    wolfssl-5.7.2/src/sniffer.c \
    wolfssl-5.7.2/src/ssl.c \
    wolfssl-5.7.2/src/tls.c \
    wolfssl-5.7.2/src/tls13.c \
    wolfssl-5.7.2/src/wolfio.c \
    \
    wolfssl-5.7.2/wolfcrypt/src/aes.c \
    wolfssl-5.7.2/wolfcrypt/src/asn.c \
    wolfssl-5.7.2/wolfcrypt/src/async.c \
    wolfssl-5.7.2/wolfcrypt/src/cmac.c \
    wolfssl-5.7.2/wolfcrypt/src/coding.c \
    wolfssl-5.7.2/wolfcrypt/src/compress.c \
    wolfssl-5.7.2/wolfcrypt/src/cpuid.c \
    wolfssl-5.7.2/wolfcrypt/src/cryptocb.c \
    wolfssl-5.7.2/wolfcrypt/src/curve25519.c \
    wolfssl-5.7.2/wolfcrypt/src/des3.c \
    wolfssl-5.7.2/wolfcrypt/src/dsa.c \
    wolfssl-5.7.2/wolfcrypt/src/ecc.c \
    wolfssl-5.7.2/wolfcrypt/src/ecc_fp.c \
    wolfssl-5.7.2/wolfcrypt/src/eccsi.c \
    wolfssl-5.7.2/wolfcrypt/src/ed25519.c \
    wolfssl-5.7.2/wolfcrypt/src/error.c \
    wolfssl-5.7.2/wolfcrypt/src/ext_kyber.c \
    wolfssl-5.7.2/wolfcrypt/src/ext_lms.c \
    wolfssl-5.7.2/wolfcrypt/src/ext_xmss.c \
    wolfssl-5.7.2/wolfcrypt/src/falcon.c \
    wolfssl-5.7.2/wolfcrypt/src/fe_448.c \
    wolfssl-5.7.2/wolfcrypt/src/fe_low_mem.c \
    wolfssl-5.7.2/wolfcrypt/src/fe_operations.c \
    wolfssl-5.7.2/wolfcrypt/src/fips.c \
    wolfssl-5.7.2/wolfcrypt/src/fips_test.c \
    wolfssl-5.7.2/wolfcrypt/src/ge_448.c \
    wolfssl-5.7.2/wolfcrypt/src/ge_low_mem.c \
    wolfssl-5.7.2/wolfcrypt/src/ge_operations.c \
    wolfssl-5.7.2/wolfcrypt/src/hash.c \
    wolfssl-5.7.2/wolfcrypt/src/hmac.c \
    wolfssl-5.7.2/wolfcrypt/src/hpke.c \
    wolfssl-5.7.2/wolfcrypt/src/integer.c \
    wolfssl-5.7.2/wolfcrypt/src/kdf.c \
    wolfssl-5.7.2/wolfcrypt/src/logging.c \
    wolfssl-5.7.2/wolfcrypt/src/md2.c \
    wolfssl-5.7.2/wolfcrypt/src/md4.c \
    wolfssl-5.7.2/wolfcrypt/src/md5.c \
    wolfssl-5.7.2/wolfcrypt/src/memory.c \
    wolfssl-5.7.2/wolfcrypt/src/pkcs12.c \
    wolfssl-5.7.2/wolfcrypt/src/pkcs7.c \
    wolfssl-5.7.2/wolfcrypt/src/poly1305.c \
    wolfssl-5.7.2/wolfcrypt/src/pwdbased.c \
    wolfssl-5.7.2/wolfcrypt/src/random.c \
    wolfssl-5.7.2/wolfcrypt/src/rc2.c \
    wolfssl-5.7.2/wolfcrypt/src/ripemd.c \
    wolfssl-5.7.2/wolfcrypt/src/rsa.c \
    wolfssl-5.7.2/wolfcrypt/src/sakke.c \
    wolfssl-5.7.2/wolfcrypt/src/selftest.c \
    wolfssl-5.7.2/wolfcrypt/src/sha.c \
    wolfssl-5.7.2/wolfcrypt/src/sha256.c \
    wolfssl-5.7.2/wolfcrypt/src/sha3.c \
    wolfssl-5.7.2/wolfcrypt/src/sha512.c \
    wolfssl-5.7.2/wolfcrypt/src/signature.c \
    wolfssl-5.7.2/wolfcrypt/src/siphash.c \
    wolfssl-5.7.2/wolfcrypt/src/sm2.c \
    wolfssl-5.7.2/wolfcrypt/src/sm3.c \
    wolfssl-5.7.2/wolfcrypt/src/sm4.c \
    wolfssl-5.7.2/wolfcrypt/src/sp_arm32.c \
    wolfssl-5.7.2/wolfcrypt/src/sp_arm64.c \
    wolfssl-5.7.2/wolfcrypt/src/sp_armthumb.c \
    wolfssl-5.7.2/wolfcrypt/src/sp_c32.c \
    wolfssl-5.7.2/wolfcrypt/src/sp_c64.c \
    wolfssl-5.7.2/wolfcrypt/src/sp_cortexm.c \
    wolfssl-5.7.2/wolfcrypt/src/sp_dsp32.c \
    wolfssl-5.7.2/wolfcrypt/src/sp_int.c \
    wolfssl-5.7.2/wolfcrypt/src/sp_sm2_arm32.c \
    wolfssl-5.7.2/wolfcrypt/src/sp_sm2_arm64.c \
    wolfssl-5.7.2/wolfcrypt/src/sp_sm2_armthumb.c \
    wolfssl-5.7.2/wolfcrypt/src/sp_sm2_c32.c \
    wolfssl-5.7.2/wolfcrypt/src/sp_sm2_c64.c \
    wolfssl-5.7.2/wolfcrypt/src/sp_sm2_cortexm.c \
    wolfssl-5.7.2/wolfcrypt/src/sp_sm2_x86_64.c \
    wolfssl-5.7.2/wolfcrypt/src/sp_x86_64.c \
    wolfssl-5.7.2/wolfcrypt/src/sphincs.c \
    wolfssl-5.7.2/wolfcrypt/src/srp.c \
    wolfssl-5.7.2/wolfcrypt/src/tfm.c \
    wolfssl-5.7.2/wolfcrypt/src/wc_dsp.c \
    wolfssl-5.7.2/wolfcrypt/src/wc_encrypt.c \
    wolfssl-5.7.2/wolfcrypt/src/wc_kyber.c \
    wolfssl-5.7.2/wolfcrypt/src/wc_kyber_poly.c \
    wolfssl-5.7.2/wolfcrypt/src/wc_lms.c \
    wolfssl-5.7.2/wolfcrypt/src/wc_lms_impl.c \
    wolfssl-5.7.2/wolfcrypt/src/wc_pkcs11.c \
    wolfssl-5.7.2/wolfcrypt/src/wc_port.c \
    wolfssl-5.7.2/wolfcrypt/src/wc_xmss.c \
    wolfssl-5.7.2/wolfcrypt/src/wc_xmss_impl.c \
    wolfssl-5.7.2/wolfcrypt/src/wolfcrypt_first.c \
    wolfssl-5.7.2/wolfcrypt/src/wolfcrypt_last.c \
    wolfssl-5.7.2/wolfcrypt/src/wolfevent.c \
    wolfssl-5.7.2/wolfcrypt/src/wolfmath.c \
    -lm


#gcc main.c -I./wolfssl wolfssl/src/internal.c wolfssl/src/ssl.c
#./a.out
