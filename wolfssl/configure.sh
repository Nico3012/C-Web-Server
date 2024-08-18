# apt install build-essential

cd wolfssl-5.7.2

./configure \
    --disable-asm \
    --disable-benchmark \
    --disable-sp-asm \
    --enable-singlethreaded \
    \
    --enable-tls13 \
    --enable-curve25519 \
    --enable-ed25519 \
    \
    --disable-chacha \
    --disable-dh \
    --disable-rsa \
    \
    --disable-sni \
    --disable-base64encode \
    --disable-sha224 \
    --disable-sha3 \
    \
    --disable-filesystem \
    --disable-examples \
    --disable-crypttests \
    --disable-pkcs12 \
    --enable-pkcs8 \
    --disable-openssl-compatible-defaults \
    \
    --disable-fastmath \
    --disable-fasthugemath \
