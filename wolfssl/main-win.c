// #include "user_settings.h"
#include "wolfssl-5.7.2/wolfssl/ssl.h"

#include <stdio.h>
#include <stdlib.h>
#include <math.h> // pow and log functions
#include <string.h>

#include <WinSock2.h>

#define DEFAULT_PORT 4433
// #define CERT_FILE "server_cert.pem"
// #define KEY_FILE "server_key.pem"


// "server_cert.pem":
const char* certStr = "-----BEGIN CERTIFICATE-----\nMIIDMzCCAhugAwIBAgIQY4Dbi7B4HxxJ0zxcXgWvCTANBgkqhkiG9w0BAQsFADAs\nMSowKAYDVQQKDCFMaXF1aXBheSBVRyAoaGFmdHVuZ3NiZXNjaHLDpG5rdCkwHhcN\nMjQwNzI0MDAwMDAwWhcNMjYwNzI0MDAwMDAwWjAsMSowKAYDVQQKDCFMaXF1aXBh\neSBVRyAoaGFmdHVuZ3NiZXNjaHLDpG5rdCkwggEiMA0GCSqGSIb3DQEBAQUAA4IB\nDwAwggEKAoIBAQC6sfl0BBYdxOJczdo7/rKEhYA3zrUVPSyO7amWd+Z07RG6uDSa\nSaDM3VGvcFe3f3QwW4BGaAgqnbcwdrKyqEdun8ZDCUv9HZEIglnGWR0nCkL9k/5g\nX9OFqX4yC+rXvhCfD0xV/+hpXpl/6w9HP73zVTE+a4S1nSkAxYJJVZcJP7X7p7Jr\n2L/P3qEreTwfmVUjfH6/BaZbjswxX6n7VFQWpB3le56aHR8wjzyGde+BdorklLbu\nngSIIaMTVqzNN+f+ug9Kt9DNwtN4DOi1V/3bAH9W/zGE2aBhHiZhTOzEayI/qjOk\nA6BzT11t6wZH42TcrowWAf4GF2wVpiHyDgcPAgMBAAGjUTBPMA4GA1UdDwEB/wQE\nAwIFoDATBgNVHSUEDDAKBggrBgEFBQcDATAMBgNVHRMBAf8EAjAAMBoGA1UdEQQT\nMBGCCWxvY2FsaG9zdIcEfwAAATANBgkqhkiG9w0BAQsFAAOCAQEARD6QztkGIuZQ\n4tF51irqAy5rup55dlGRw+hiRsNa4oqpzQ26MgSH968WBgad8Uiz7d5qv7/bB4GI\nw/C4Xl5v8XBGkw1Xsj7YQHQ1FwLbZodfuLxCUPsKHrZorz2ck8KSFOXz/ZbOK+Nj\nOhs57lYs3fPe/m5MfJTu+aouavzFXtGM2EnTg+Of14G9mMsJug7XjCOwpVXBholi\nuMOjQSxeJ7Ldw87dk0u/e+e2JYIHljsCs0CJlpJJj5wuTfmvYSHMxbm+Z618BgSr\n8rr9Aknonxb7ixbxlVNHpkvKTPX013XJ0zDAN8eccPxsiZJC5hvqyY2837pWf3yb\n/OJqGUaHOQ==\n-----END CERTIFICATE-----\n";

// "server_key.pem":
const char* keyStr = "-----BEGIN PRIVATE KEY-----\nMIIEvgIBADANBgkqhkiG9w0BAQEFAASCBKgwggSkAgEAAoIBAQC6sfl0BBYdxOJc\nzdo7/rKEhYA3zrUVPSyO7amWd+Z07RG6uDSaSaDM3VGvcFe3f3QwW4BGaAgqnbcw\ndrKyqEdun8ZDCUv9HZEIglnGWR0nCkL9k/5gX9OFqX4yC+rXvhCfD0xV/+hpXpl/\n6w9HP73zVTE+a4S1nSkAxYJJVZcJP7X7p7Jr2L/P3qEreTwfmVUjfH6/BaZbjswx\nX6n7VFQWpB3le56aHR8wjzyGde+BdorklLbungSIIaMTVqzNN+f+ug9Kt9DNwtN4\nDOi1V/3bAH9W/zGE2aBhHiZhTOzEayI/qjOkA6BzT11t6wZH42TcrowWAf4GF2wV\npiHyDgcPAgMBAAECggEBAKqFMjYAIX8xPBvNvX28xar7EMBoYcczZ8ZoVtRjUTAM\n9HuaEhm2FFPp9dkLAGNO233rpT8peAQMp6xxTgiWYSAuePTzwd8/qR+fh4X+EP1+\nhu97xAScoeNcizIE5owFQsM1QuDt64aKbCOFPCA0nTdq4Z6Er+L919ynibeXoGtF\noVyy/nKf9NWwczKO1TyWHrGEQbvMv+XDpRLzICB0kPc5Z/Hy4b+zy8FW16uHJQM3\nljGApiEW+QykQjZB13GMLiZPjymMU5tega/m6OwOJcOTSd1i965JBgzvh/5l3xjs\n9TOnc8xmEc33eUhtMI3EJX7XHyD+0qywk8B/YliH8AECgYEA4K0MHAdiyVFSKSEX\nuKQDmuEiFwg5khflPaKHLzIUgke/mORrXZL0Ycgus/H9ohso+zLHXLnOtZwAsiHp\nBio5A5DC4Bt5njh6VBsTyzg60LktGPPIr4+MH3SempOEQbEiXVi8TVj5ovo70c9m\n7Ou5z39rTOxfRMZDayaY8Qm+GAECgYEA1LlZTDf7MG66WIIezDX3igcmmI3Ng13v\nqD/9nBlp0/S7QLZG/AVImo5ht9ci3TLKqGV/Zd/Rc0jgY5hqsm4jFmNX6+/eVH2B\nEL6ARv15nTEdZNHDMtIdfMrtg31+TF5I6ORtzBGlY1cFCI4sMyT/k5BZhjcr8YmL\neilKkR8Cnw8CgYEApCaKdGgJCuE5UAd3l1VttNjL2VwPA+gletSmRBso1M6q83/f\n2awmlNJ3HM2u66NAW9eLxPmURyfFcmBIKlLq+OnpF2e7gZft+EkYOx/ICPtiMZrb\ngzkzvT+tKW6h8IUEgIL2gOSC70o4LmCD6JGJXkrQEJGaQVtBoqW+lEzz8AECgYBs\nIEpjk5D6bU4K7xj4c/X/EuNrZ6iuvXCz9NLUJZbFRgBoRD6Qm57r8LN63r+577dT\nIURAZCPylXh5J2AUkicDmjt2kdZQ2/peqHZLn0vRusVWGck+a87RP9S6oW8xIjut\nJW8p605F0FWeo6WT2ZqPRzA6KJENlPxwe8yLN1f9wQKBgG0fTdcdN3R55BZ/ORhE\ntX1c6CXKKa+imvCsDhM6LKyERUY0I5eXhPFUk8yrkELwn9Xl30wx72MvTJsb+RZi\n2ezCPJBn0JvTDEUg5pivAvqVTcJCEixvyK+TDqgZuvRIV0QSPpagKeSRVYmKwsK8\nOYfApRcH2zConBjRh9IEzX3d\n-----END PRIVATE KEY-----\n";








void error(const char *msg)
{
    perror(msg);
    exit(1);
}

int main()
{
    // initialize variables
    int iResult;
    WSADATA wsaData;
    SOCKET sockfd;
    SOCKET newsockfd;

    // init Winsock
    iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (iResult != NO_ERROR)
    {
        printf("WSAStartup failed with error: %d\n", iResult);
        return 1;
    }


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




    // create socket for listening for
    sockfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (sockfd == INVALID_SOCKET)
    {
        printf("socket failed with error: %d\n", (int)WSAGetLastError());
        WSACleanup();
        return 1;
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
        closesocket(newsockfd);
    }

    closesocket(sockfd);
    wolfSSL_CTX_free(ctx);
    wolfSSL_Cleanup();

    return 0;
}
