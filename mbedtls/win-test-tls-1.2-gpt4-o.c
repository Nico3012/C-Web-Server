// gcc win-test-tls-1.2-gpt4-o.c -I./mbedtls/include -I./mbedtls/library ./mbedtls/library/*.c -lws2_32 -lbcrypt

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <WinSock2.h>

#include <mbedtls/net_sockets.h>
#include <mbedtls/ssl.h>
#include <mbedtls/ssl_cache.h>
#include <mbedtls/ssl_cookie.h>
#include <mbedtls/entropy.h>
#include <mbedtls/ctr_drbg.h>
#include <mbedtls/x509.h>
#include <mbedtls/x509_crt.h>
#include <mbedtls/error.h>

#define SERVER_PORT "4433"
#define BUFFER_SIZE 1024

void handle_client(mbedtls_ssl_context *ssl) {
    unsigned char buf[BUFFER_SIZE];
    int ret;

    memset(buf, 0, sizeof(buf));
    ret = mbedtls_ssl_read(ssl, buf, sizeof(buf) - 1);
    if (ret <= 0) {
        return;
    }

    printf("Received message from client: %s\n", buf);

    const char *response = "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\nContent-Length: 12\r\n\r\nHello WORld";
    mbedtls_ssl_write(ssl, (unsigned char *)response, strlen(response));
}

int main() {
    int ret;
    mbedtls_net_context listen_fd, client_fd;
    mbedtls_ssl_context ssl;
    mbedtls_ssl_config conf;
    mbedtls_x509_crt srvcert;
    mbedtls_pk_context pkey;
    mbedtls_entropy_context entropy;
    mbedtls_ctr_drbg_context ctr_drbg;
    const char *pers = "ssl_server";

    mbedtls_net_init(&listen_fd);
    mbedtls_net_init(&client_fd);
    mbedtls_ssl_init(&ssl);
    mbedtls_ssl_config_init(&conf);
    mbedtls_x509_crt_init(&srvcert);
    mbedtls_pk_init(&pkey);
    mbedtls_entropy_init(&entropy);
    mbedtls_ctr_drbg_init(&ctr_drbg);

    if ((ret = mbedtls_ctr_drbg_seed(&ctr_drbg, mbedtls_entropy_func, &entropy, (const unsigned char *)pers, strlen(pers))) != 0) {
        printf("mbedtls_ctr_drbg_seed returned %d\n", ret);
        return 1;
    }

    if ((ret = mbedtls_x509_crt_parse_file(&srvcert, "server_cert.pem")) != 0) {
        printf("mbedtls_x509_crt_parse_file returned %d\n", ret);
        return 1;
    }

    if ((ret = mbedtls_pk_parse_keyfile(&pkey, "server_key.pem", NULL, NULL, NULL)) != 0) {
        printf("mbedtls_pk_parse_keyfile returned %d\n", ret);
        return 1;
    }

    if ((ret = mbedtls_net_bind(&listen_fd, NULL, SERVER_PORT, MBEDTLS_NET_PROTO_TCP)) != 0) {
        printf("mbedtls_net_bind returned %d\n", ret);
        return 1;
    }

    if ((ret = mbedtls_ssl_config_defaults(&conf, MBEDTLS_SSL_IS_SERVER, MBEDTLS_SSL_TRANSPORT_STREAM, MBEDTLS_SSL_PRESET_DEFAULT)) != 0) {
        printf("mbedtls_ssl_config_defaults returned %d\n", ret);
        return 1;
    }

    // Specify the supported cipher suites
    const int ciphersuites[] = {
        MBEDTLS_TLS_RSA_WITH_AES_128_GCM_SHA256,
        MBEDTLS_TLS_RSA_WITH_AES_256_GCM_SHA384,
        0 // end of list
    };
    mbedtls_ssl_conf_ciphersuites(&conf, ciphersuites);

    // Specify the SSL/TLS version to use
    mbedtls_ssl_conf_min_version(&conf, MBEDTLS_SSL_MAJOR_VERSION_3, MBEDTLS_SSL_MINOR_VERSION_3); // TLS 1.2
    mbedtls_ssl_conf_max_version(&conf, MBEDTLS_SSL_MAJOR_VERSION_3, MBEDTLS_SSL_MINOR_VERSION_3); // TLS 1.2

    mbedtls_ssl_conf_rng(&conf, mbedtls_ctr_drbg_random, &ctr_drbg);
    mbedtls_ssl_conf_ca_chain(&conf, srvcert.next, NULL);
    if ((ret = mbedtls_ssl_conf_own_cert(&conf, &srvcert, &pkey)) != 0) {
        printf("mbedtls_ssl_conf_own_cert returned %d\n", ret);
        return 1;
    }

    if ((ret = mbedtls_ssl_setup(&ssl, &conf)) != 0) {
        printf("mbedtls_ssl_setup returned %d\n", ret);
        return 1;
    }

    printf("Server listening on port %s\n", SERVER_PORT);

    while (1) {
        if ((ret = mbedtls_net_accept(&listen_fd, &client_fd, NULL, 0, NULL)) != 0) {
            printf("mbedtls_net_accept returned %d\n", ret);
            continue;
        }

        mbedtls_ssl_set_bio(&ssl, &client_fd, mbedtls_net_send, mbedtls_net_recv, NULL);

        if ((ret = mbedtls_ssl_handshake(&ssl)) != 0) {
            printf("mbedtls_ssl_handshake returned -0x%x\n", -ret);
            char error_buf[100];
            mbedtls_strerror(ret, error_buf, 100);
            printf("Last error was: %s\n", error_buf);
            mbedtls_net_free(&client_fd);
            continue;
        }

        handle_client(&ssl);
        mbedtls_ssl_session_reset(&ssl);
        mbedtls_net_free(&client_fd);
    }

    mbedtls_net_free(&listen_fd);
    mbedtls_ssl_free(&ssl);
    mbedtls_ssl_config_free(&conf);
    mbedtls_x509_crt_free(&srvcert);
    mbedtls_pk_free(&pkey);
    mbedtls_entropy_free(&entropy);
    mbedtls_ctr_drbg_free(&ctr_drbg);

    return 0;
}
