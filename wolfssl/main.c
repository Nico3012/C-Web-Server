// c stdlib includes:
#include <stdio.h>
#include <stdlib.h>

// tls library specific includes:
#include <wolfssl/ssl.h>

// platform specific includes:
#include <winsock2.h>

#define CERTIFICATE_CHAIN_FILENAME "certificate_chain.pem"
#define PRIVATE_KEY_FILENAME "private_key.pem"
#define CERTIFICATE_CHAIN_BUFFER_SIZE 4096
#define PRIVATE_KEY_BUFFER_SIZE 4096

int main()
{
    // wolfssl memory abstraction layer:
    wolfSSL_SetAllocators(malloc, free, realloc);

    // wolfssl socket io abstraction layer:
    wolfSSL_SetIORecv(ctx, recv);
    wolfSSL_SetIOSend(ctx, send);

    // initialize wolfSSL
    WOLFSSL_METHOD *method = wolfTLSv1_3_server_method();
    WOLFSSL_CTX *ctx = wolfSSL_CTX_new(method);

    // read certificate chain buffer from file:
    char certificateChainBuffer[CERTIFICATE_CHAIN_BUFFER_SIZE];
    FILE *certificateChainFile = fopen(CERTIFICATE_CHAIN_FILENAME, "r");
    fread(&certificateChainBuffer, sizeof(char), CERTIFICATE_CHAIN_BUFFER_SIZE, certificateChainFile);
    fclose(certificateChainFile);

    // read private key buffer from file:
    char privateKeyBuffer[PRIVATE_KEY_BUFFER_SIZE];
    FILE *privateKeyFile = fopen(PRIVATE_KEY_FILENAME, "r");
    fread(&privateKeyBuffer, sizeof(char), PRIVATE_KEY_BUFFER_SIZE, privateKeyFile);
    fclose(privateKeyFile);

    // use certificate_chain and private_key
    wolfSSL_CTX_use_certificate_chain_buffer(ctx, certificateChainBuffer, CERTIFICATE_CHAIN_BUFFER_SIZE);
    wolfSSL_CTX_use_PrivateKey_buffer(ctx, privateKeyBuffer, PRIVATE_KEY_BUFFER_SIZE, SSL_FILETYPE_PEM);

    return 0;
}
