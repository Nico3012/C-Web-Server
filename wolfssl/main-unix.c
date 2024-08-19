// #include "nico-options.h"
#include <wolfssl/ssl.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <unistd.h>
#include <arpa/inet.h>

#define DEFAULT_PORT 4433
// #define CERT_FILE "server_cert.pem"
// #define KEY_FILE "server_key.pem"


// "server_cert.pem":
// const char* certStr = "-----BEGIN CERTIFICATE-----\nMIIDMzCCAhugAwIBAgIQY4Dbi7B4HxxJ0zxcXgWvCTANBgkqhkiG9w0BAQsFADAs\nMSowKAYDVQQKDCFMaXF1aXBheSBVRyAoaGFmdHVuZ3NiZXNjaHLDpG5rdCkwHhcN\nMjQwNzI0MDAwMDAwWhcNMjYwNzI0MDAwMDAwWjAsMSowKAYDVQQKDCFMaXF1aXBh\neSBVRyAoaGFmdHVuZ3NiZXNjaHLDpG5rdCkwggEiMA0GCSqGSIb3DQEBAQUAA4IB\nDwAwggEKAoIBAQC6sfl0BBYdxOJczdo7/rKEhYA3zrUVPSyO7amWd+Z07RG6uDSa\nSaDM3VGvcFe3f3QwW4BGaAgqnbcwdrKyqEdun8ZDCUv9HZEIglnGWR0nCkL9k/5g\nX9OFqX4yC+rXvhCfD0xV/+hpXpl/6w9HP73zVTE+a4S1nSkAxYJJVZcJP7X7p7Jr\n2L/P3qEreTwfmVUjfH6/BaZbjswxX6n7VFQWpB3le56aHR8wjzyGde+BdorklLbu\nngSIIaMTVqzNN+f+ug9Kt9DNwtN4DOi1V/3bAH9W/zGE2aBhHiZhTOzEayI/qjOk\nA6BzT11t6wZH42TcrowWAf4GF2wVpiHyDgcPAgMBAAGjUTBPMA4GA1UdDwEB/wQE\nAwIFoDATBgNVHSUEDDAKBggrBgEFBQcDATAMBgNVHRMBAf8EAjAAMBoGA1UdEQQT\nMBGCCWxvY2FsaG9zdIcEfwAAATANBgkqhkiG9w0BAQsFAAOCAQEARD6QztkGIuZQ\n4tF51irqAy5rup55dlGRw+hiRsNa4oqpzQ26MgSH968WBgad8Uiz7d5qv7/bB4GI\nw/C4Xl5v8XBGkw1Xsj7YQHQ1FwLbZodfuLxCUPsKHrZorz2ck8KSFOXz/ZbOK+Nj\nOhs57lYs3fPe/m5MfJTu+aouavzFXtGM2EnTg+Of14G9mMsJug7XjCOwpVXBholi\nuMOjQSxeJ7Ldw87dk0u/e+e2JYIHljsCs0CJlpJJj5wuTfmvYSHMxbm+Z618BgSr\n8rr9Aknonxb7ixbxlVNHpkvKTPX013XJ0zDAN8eccPxsiZJC5hvqyY2837pWf3yb\n/OJqGUaHOQ==\n-----END CERTIFICATE-----\n";
const char* certStr = "-----BEGIN CERTIFICATE-----\nMIIBejCCASCgAwIBAgIRALiXDPndgl9p3p61rbHLHvMwCgYIKoZIzj0EAwIwEjEQ\nMA4GA1UEChMHQWNtZSBDbzAeFw0yNDA4MTQyMTI0MTBaFw0yNTA4MTQyMTI0MTBa\nMBIxEDAOBgNVBAoTB0FjbWUgQ28wWTATBgcqhkjOPQIBBggqhkjOPQMBBwNCAATf\nZhMb2pN7SDR9BtL9ar0+4rpHW0B5yu6BgbOJQ9pxoBUjCmPt4f2PWv9voarhdJuP\nv9YF8Ni0GA3cq4goy9hno1cwVTAOBgNVHQ8BAf8EBAMCB4AwEwYDVR0lBAwwCgYI\nKwYBBQUHAwEwDAYDVR0TAQH/BAIwADAgBgNVHREEGTAXgglsb2NhbGhvc3SHBH8A\nAAGHBMCoAjUwCgYIKoZIzj0EAwIDSAAwRQIhAIPn+CqPEwbZL+0SdcsJobj8+E3q\nHlLGkr74G7egnbvrAiB3eXtIAPs9bUPm0Ugwp/78GVj5rLScahWGVr5QPuyhbQ==\n-----END CERTIFICATE-----\n";

// "server_key.pem":
// const char* keyStr = "-----BEGIN PRIVATE KEY-----\nMIIEvgIBADANBgkqhkiG9w0BAQEFAASCBKgwggSkAgEAAoIBAQC6sfl0BBYdxOJc\nzdo7/rKEhYA3zrUVPSyO7amWd+Z07RG6uDSaSaDM3VGvcFe3f3QwW4BGaAgqnbcw\ndrKyqEdun8ZDCUv9HZEIglnGWR0nCkL9k/5gX9OFqX4yC+rXvhCfD0xV/+hpXpl/\n6w9HP73zVTE+a4S1nSkAxYJJVZcJP7X7p7Jr2L/P3qEreTwfmVUjfH6/BaZbjswx\nX6n7VFQWpB3le56aHR8wjzyGde+BdorklLbungSIIaMTVqzNN+f+ug9Kt9DNwtN4\nDOi1V/3bAH9W/zGE2aBhHiZhTOzEayI/qjOkA6BzT11t6wZH42TcrowWAf4GF2wV\npiHyDgcPAgMBAAECggEBAKqFMjYAIX8xPBvNvX28xar7EMBoYcczZ8ZoVtRjUTAM\n9HuaEhm2FFPp9dkLAGNO233rpT8peAQMp6xxTgiWYSAuePTzwd8/qR+fh4X+EP1+\nhu97xAScoeNcizIE5owFQsM1QuDt64aKbCOFPCA0nTdq4Z6Er+L919ynibeXoGtF\noVyy/nKf9NWwczKO1TyWHrGEQbvMv+XDpRLzICB0kPc5Z/Hy4b+zy8FW16uHJQM3\nljGApiEW+QykQjZB13GMLiZPjymMU5tega/m6OwOJcOTSd1i965JBgzvh/5l3xjs\n9TOnc8xmEc33eUhtMI3EJX7XHyD+0qywk8B/YliH8AECgYEA4K0MHAdiyVFSKSEX\nuKQDmuEiFwg5khflPaKHLzIUgke/mORrXZL0Ycgus/H9ohso+zLHXLnOtZwAsiHp\nBio5A5DC4Bt5njh6VBsTyzg60LktGPPIr4+MH3SempOEQbEiXVi8TVj5ovo70c9m\n7Ou5z39rTOxfRMZDayaY8Qm+GAECgYEA1LlZTDf7MG66WIIezDX3igcmmI3Ng13v\nqD/9nBlp0/S7QLZG/AVImo5ht9ci3TLKqGV/Zd/Rc0jgY5hqsm4jFmNX6+/eVH2B\nEL6ARv15nTEdZNHDMtIdfMrtg31+TF5I6ORtzBGlY1cFCI4sMyT/k5BZhjcr8YmL\neilKkR8Cnw8CgYEApCaKdGgJCuE5UAd3l1VttNjL2VwPA+gletSmRBso1M6q83/f\n2awmlNJ3HM2u66NAW9eLxPmURyfFcmBIKlLq+OnpF2e7gZft+EkYOx/ICPtiMZrb\ngzkzvT+tKW6h8IUEgIL2gOSC70o4LmCD6JGJXkrQEJGaQVtBoqW+lEzz8AECgYBs\nIEpjk5D6bU4K7xj4c/X/EuNrZ6iuvXCz9NLUJZbFRgBoRD6Qm57r8LN63r+577dT\nIURAZCPylXh5J2AUkicDmjt2kdZQ2/peqHZLn0vRusVWGck+a87RP9S6oW8xIjut\nJW8p605F0FWeo6WT2ZqPRzA6KJENlPxwe8yLN1f9wQKBgG0fTdcdN3R55BZ/ORhE\ntX1c6CXKKa+imvCsDhM6LKyERUY0I5eXhPFUk8yrkELwn9Xl30wx72MvTJsb+RZi\n2ezCPJBn0JvTDEUg5pivAvqVTcJCEixvyK+TDqgZuvRIV0QSPpagKeSRVYmKwsK8\nOYfApRcH2zConBjRh9IEzX3d\n-----END PRIVATE KEY-----\n";
const char* keyStr = "-----BEGIN PRIVATE KEY-----\nMIGHAgEAMBMGByqGSM49AgEGCCqGSM49AwEHBG0wawIBAQQg4qOVE+o6+RFVDFzJ\nHsP4yOsRRSUtW1pylj6EdB3c8xahRANCAATfZhMb2pN7SDR9BtL9ar0+4rpHW0B5\nyu6BgbOJQ9pxoBUjCmPt4f2PWv9voarhdJuPv9YF8Ni0GA3cq4goy9hn\n-----END PRIVATE KEY-----\n";


int sockfd, newsockfd;


// strg c interrupt to use
#include <signal.h>
void releaseFn() {
    close(sockfd);
    // wolfSSL_CTX_free(ctx);
    wolfSSL_Cleanup();
    printf("cleaned\n");
}




void error(const char *msg)
{
    perror(msg);
    exit(1);
}

// Custom read function
int my_IORecv(WOLFSSL *ssl, char *buf, int sz, void *ctx) {
    int iResult = recv(newsockfd, buf, sz, 0);
    // Implement your custom read logic here
    // Return the number of bytes read or an error code
    return iResult;
}

// Custom write function
int my_IOSend(WOLFSSL *ssl, char *buf, int sz, void *ctx) {
    int iResult = send(newsockfd, buf, sz, 0);
    // Implement your custom write logic here
    // Return the number of bytes written or an error code
    return iResult;
}

int main()
{
    // strg c interupt:
    signal(SIGINT, releaseFn);

    // wolfssl memory abstraction layer:
    wolfSSL_SetAllocators(malloc, free, realloc);

    // int sockfd, newsockfd;
    socklen_t clilen;
    struct sockaddr_in serv_addr, cli_addr;
    char buffer[4096];

    wolfSSL_Init();

    WOLFSSL_CTX *ctx = wolfSSL_CTX_new(wolfTLSv1_3_server_method());
    if (ctx == NULL)
    {
        error("wolfSSL_CTX_new error");
    }

    // wolfssl socket io abstraction layer:
    wolfSSL_SetIORecv(ctx, my_IORecv);
    wolfSSL_SetIOSend(ctx, my_IOSend);

    if (wolfSSL_CTX_use_certificate_buffer(ctx, certStr, strlen(certStr), SSL_FILETYPE_PEM) != SSL_SUCCESS)
    {
        error("nico error on certificate read");
    }

    /*if (wolfSSL_CTX_use_certificate_file(ctx, CERT_FILE, SSL_FILETYPE_PEM) != SSL_SUCCESS)
    {
        error("wolfSSL_CTX_use_certificate_file error");
    }*/


    if (wolfSSL_CTX_use_PrivateKey_buffer(ctx, keyStr, strlen(keyStr), SSL_FILETYPE_PEM) != SSL_SUCCESS)
    {
        error("nico error read privkey");
    }

    /*if (wolfSSL_CTX_use_PrivateKey_file(ctx, KEY_FILE, SSL_FILETYPE_PEM) != SSL_SUCCESS)
    {
        error("wolfSSL_CTX_use_PrivateKey_file error");
    }*/







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
