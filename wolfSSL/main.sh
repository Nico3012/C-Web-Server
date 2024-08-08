# sudo sh main.sh

# apt install libwolfssl-dev
rm a.out
gcc main.c -I./wolfssl -L./wolfssl -lwolfssl
# gcc main.c -I./wolfssl ./wolfssl/src/*.c -I./wolfssl/wolfcrypt ./wolfssl/wolfcrypt/src/*.c
# gcc main.c -I./wolfssl wolfssl/src/internal.c wolfssl/src/ssl.c
# ./a.out
