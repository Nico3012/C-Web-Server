// #include "user_settings.h"
#include "wolfssl-5.7.2/wolfssl/ssl.h"

#include <stdio.h>
#include <stdlib.h>
#include <math.h> // pow and log functions
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define DEFAULT_PORT 4433
#define CERT_FILE "server_cert.pem"
#define KEY_FILE "server_key.pem"

void error(const char *msg)
{
    perror(msg);
    exit(1);
}

int main()
{
    int sockfd, newsockfd;
    socklen_t clilen;
    struct sockaddr_in serv_addr, cli_addr;
    char buffer[4096];

    wolfSSL_Init();

    WOLFSSL_CTX *ctx = wolfSSL_CTX_new(wolfTLSv1_3_server_method());
    if (ctx == NULL)
    {
        error("wolfSSL_CTX_new error");
    }

    if (wolfSSL_CTX_use_certificate_file(ctx, CERT_FILE, SSL_FILETYPE_PEM) != SSL_SUCCESS)
    {
        error("wolfSSL_CTX_use_certificate_file error");
    }

    if (wolfSSL_CTX_use_PrivateKey_file(ctx, KEY_FILE, SSL_FILETYPE_PEM) != SSL_SUCCESS)
    {
        error("wolfSSL_CTX_use_PrivateKey_file error");
    }

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0)
    {
        error("ERROR opening socket");
    }



    memset((char *)&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(DEFAULT_PORT);

    if (bind(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
    {
        error("ERROR on binding");
    }

    listen(sockfd, 5);
    clilen = sizeof(cli_addr);







    while (1)
    {
        newsockfd = accept(sockfd, (struct sockaddr *)&cli_addr, &clilen);
        if (newsockfd < 0)
        {
            error("ERROR on accept");
        }

        WOLFSSL *ssl = wolfSSL_new(ctx);
        if (ssl == NULL)
        {
            error("wolfSSL_new error");
        }

        wolfSSL_set_fd(ssl, newsockfd);

        if (wolfSSL_accept(ssl) != SSL_SUCCESS)
        {
            error("wolfSSL_accept error");
        }

        memset(buffer, 0, 4096);
        int n = wolfSSL_read(ssl, buffer, 4095);
        if (n < 0)
        {
            error("ERROR reading from socket");
        }

        // printf("Here is the message: %s\n", buffer);

        char *httpResponse = "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\nContent-Length: 12\r\n\r\nHello World!";

        n = wolfSSL_write(ssl, httpResponse, (int)strlen(httpResponse));
        if (n < 0)
        {
            error("ERROR writing to socket");
        }

        wolfSSL_shutdown(ssl);
        wolfSSL_free(ssl);
        close(newsockfd);
    }

    close(sockfd);
    wolfSSL_CTX_free(ctx);
    wolfSSL_Cleanup();

    return 0;
}
