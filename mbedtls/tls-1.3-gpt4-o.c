#include "mbedtls/net_sockets.h"
#include "mbedtls/ssl.h"
#include "mbedtls/ssl_ticket.h"
#include "mbedtls/ssl_cache.h"
#include "mbedtls/entropy.h"
#include "mbedtls/ctr_drbg.h"
#include "mbedtls/error.h"
// #include "mbedtls/certs.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SERVER_PORT "4433"
#define BUFFER_SIZE 1024

void my_debug(void *ctx, int level, const char *file, int line, const char *str) {
    ((void) level);
    fprintf((FILE *) ctx, "%s:%04d: %s", file, line, str);
}

int my_verify(void *data, mbedtls_x509_crt *crt, int depth, uint32_t *flags) {
    char buf[1024];
    mbedtls_x509_crt_info(buf, sizeof(buf) - 1, "", crt);
    printf("Verify requested for (Depth %d):\n%s\n", depth, buf);

    if (*flags != 0) {
        mbedtls_x509_crt_verify_info(buf, sizeof(buf), "  ! ", *flags);
        printf("%s\n", buf);
    }

    return 0; // Ignore verification for testing
}

int main(void) {
    int ret;
    mbedtls_net_context listen_fd, client_fd;
    mbedtls_ssl_context ssl;
    mbedtls_ssl_config conf;
    mbedtls_x509_crt srvcert, cacert;
    mbedtls_pk_context pkey;
    mbedtls_entropy_context entropy;
    mbedtls_ctr_drbg_context ctr_drbg;
    unsigned char buf[BUFFER_SIZE];
    const char *pers = "ssl_server";

    mbedtls_net_init(&listen_fd);
    mbedtls_net_init(&client_fd);
    mbedtls_ssl_init(&ssl);
    mbedtls_ssl_config_init(&conf);
    mbedtls_x509_crt_init(&srvcert);
    mbedtls_x509_crt_init(&cacert);
    mbedtls_pk_init(&pkey);
    mbedtls_entropy_init(&entropy);
    mbedtls_ctr_drbg_init(&ctr_drbg);

    if ((ret = mbedtls_ctr_drbg_seed(&ctr_drbg, mbedtls_entropy_func, &entropy, (const unsigned char *)pers, strlen(pers))) != 0) {
        printf("mbedtls_ctr_drbg_seed returned %d\n", ret);
        goto exit;
    }

    // Load the certificates and private key
    if ((ret = mbedtls_x509_crt_parse_file(&srvcert, "openssl_cert.pem")) != 0) {
        printf("mbedtls_x509_crt_parse_file returned %d\n", ret);
        goto exit;
    }

    if ((ret = mbedtls_x509_crt_parse_file(&cacert, "openssl_cert.pem")) != 0) {
        printf("mbedtls_x509_crt_parse_file(cacert) returned %d\n", ret);
        goto exit;
    }

    if ((ret = mbedtls_pk_parse_keyfile(&pkey, "openssl_key.pem", NULL, mbedtls_ctr_drbg_random, &ctr_drbg)) != 0) {
        printf("mbedtls_pk_parse_keyfile returned %d\n", ret);
        goto exit;
    }

    // Bind to the HTTPS port
    if ((ret = mbedtls_net_bind(&listen_fd, NULL, SERVER_PORT, MBEDTLS_NET_PROTO_TCP)) != 0) {
        printf("mbedtls_net_bind returned %d\n", ret);
        goto exit;
    }

    // Setup SSL
    if ((ret = mbedtls_ssl_config_defaults(&conf, MBEDTLS_SSL_IS_SERVER, MBEDTLS_SSL_TRANSPORT_STREAM, MBEDTLS_SSL_PRESET_DEFAULT)) != 0) {
        printf("mbedtls_ssl_config_defaults returned %d\n", ret);
        goto exit;
    }

    mbedtls_ssl_conf_ca_chain(&conf, &cacert, NULL);
    if ((ret = mbedtls_ssl_conf_own_cert(&conf, &srvcert, &pkey)) != 0) {
        printf("mbedtls_ssl_conf_own_cert returned %d\n", ret);
        goto exit;
    }

    mbedtls_ssl_conf_rng(&conf, mbedtls_ctr_drbg_random, &ctr_drbg);
    mbedtls_ssl_conf_dbg(&conf, my_debug, stdout);
    mbedtls_debug_set_threshold(4);

    // Optional: Ignore verification for testing
    mbedtls_ssl_conf_verify(&conf, my_verify, NULL);
    mbedtls_ssl_conf_authmode(&conf, MBEDTLS_SSL_VERIFY_OPTIONAL);

    if ((ret = mbedtls_ssl_setup(&ssl, &conf)) != 0) {
        printf("mbedtls_ssl_setup returned %d\n", ret);
        goto exit;
    }

    // Accept client connection
    if ((ret = mbedtls_net_accept(&listen_fd, &client_fd, NULL, 0, NULL)) != 0) {
        printf("mbedtls_net_accept returned %d\n", ret);
        goto exit;
    }

    mbedtls_ssl_set_bio(&ssl, &client_fd, mbedtls_net_send, mbedtls_net_recv, NULL);

    // Handshake
    while ((ret = mbedtls_ssl_handshake(&ssl)) != 0) {
        if (ret != MBEDTLS_ERR_SSL_WANT_READ && ret != MBEDTLS_ERR_SSL_WANT_WRITE) {
            printf("mbedtls_ssl_handshake returned -0x%x\n", (unsigned int) -ret);
            goto exit;
        }
    }

    // Read and respond to HTTP request
    memset(buf, 0, sizeof(buf));
    if ((ret = mbedtls_ssl_read(&ssl, buf, sizeof(buf) - 1)) <= 0) {
        printf("mbedtls_ssl_read returned %d\n", ret);
        goto exit;
    }

    printf("Received request: %s\n", buf);

    const char *response = "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\n\r\nHello, world!";
    if ((ret = mbedtls_ssl_write(&ssl, (const unsigned char *)response, strlen(response))) <= 0) {
        printf("mbedtls_ssl_write returned %d\n", ret);
        goto exit;
    }

exit:
    mbedtls_ssl_free(&ssl);
    mbedtls_ssl_config_free(&conf);
    mbedtls_x509_crt_free(&srvcert);
    mbedtls_x509_crt_free(&cacert);
    mbedtls_pk_free(&pkey);
    mbedtls_entropy_free(&entropy);
    mbedtls_ctr_drbg_free(&ctr_drbg);
    mbedtls_net_free(&client_fd);
    mbedtls_net_free(&listen_fd);

    if (ret != 0) {
        char error_buf[100];
        mbedtls_strerror(ret, error_buf, 100);
        printf("Last error was: %d - %s\n", ret, error_buf);
    }

    return ret;
}
