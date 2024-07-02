#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <fcntl.h>

// Basic TLS handshake constants (not comprehensive)
#define TLS_HANDSHAKE 22
#define TLS_CLIENT_HELLO 1
#define TLS_VERSION_MAJOR 3
#define TLS_VERSION_MINOR 3

// Create a TCP socket and connect to server
int create_socket(char *host, int port) {
    int sockfd;
    struct sockaddr_in server_addr;
    struct hostent *server;

    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("socket");
        exit(EXIT_FAILURE);
    }

    if ((server = gethostbyname(host)) == NULL) {
        perror("gethostbyname");
        exit(EXIT_FAILURE);
    }

    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);
    memcpy(&server_addr.sin_addr.s_addr, server->h_addr, server->h_length);

    if (connect(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("connect");
        close(sockfd);
        exit(EXIT_FAILURE);
    }

    return sockfd;
}

// Send a simple TLS ClientHello message
void send_client_hello(int sockfd) {
    unsigned char client_hello[] = {
        TLS_HANDSHAKE,               // Content type: Handshake
        TLS_VERSION_MAJOR, TLS_VERSION_MINOR,  // TLS Version: 1.2
        0x00, 0x2E,                  // Length of handshake message (46 bytes)
        TLS_CLIENT_HELLO,            // Handshake type: ClientHello
        0x00, 0x00, 0x2A,            // Length of ClientHello (42 bytes)
        TLS_VERSION_MAJOR, TLS_VERSION_MINOR,  // Client Version: TLS 1.2
        // Random (32 bytes)
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00,                       // Session ID Length
        0x00, 0x02,                 // Cipher Suites Length
        0x00, 0x3C,                 // Cipher Suite: TLS_RSA_WITH_AES_128_CBC_SHA
        0x01,                       // Compression Methods Length
        0x00                        // Compression Method: null
    };

    if (send(sockfd, client_hello, sizeof(client_hello), 0) != sizeof(client_hello)) {
        perror("send");
        close(sockfd);
        exit(EXIT_FAILURE);
    }
}

// Main function to create socket and perform a simple TLS handshake
int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <host> <port>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    char *host = argv[1];
    int port = atoi(argv[2]);

    int sockfd = create_socket(host, port);
    printf("Connected to %s on port %d\n", host, port);

    send_client_hello(sockfd);
    printf("ClientHello sent\n");

    // Normally, you would now read the server's response and continue the handshake
    // For simplicity, we will close the socket
    close(sockfd);

    return 0;
}
