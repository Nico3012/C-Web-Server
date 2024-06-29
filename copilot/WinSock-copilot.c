#include <winsock2.h>
#include <stdio.h>

int main() {
    WSADATA wsaData;
    int iResult;

    SOCKET ListenSocket = INVALID_SOCKET;
    SOCKET ClientSocket = INVALID_SOCKET;

    struct sockaddr_in server, client;

    char *httpResponse = "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\nContent-Length: 12\r\n\r\nHello World!";

    // Initialize Winsock
    iResult = WSAStartup(MAKEWORD(2,2), &wsaData);
    if (iResult != 0) {
        printf("WSAStartup failed: %d\n", iResult);
        return 1;
    }

    // Create a SOCKET for the server to listen for client connections
    ListenSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(8080);

    // Bind the socket
    bind(ListenSocket, (struct sockaddr *)&server, sizeof(server));

    // Listen on the socket
    listen(ListenSocket, SOMAXCONN);

    printf("Waiting for incoming connections...\n");
    int c = sizeof(struct sockaddr_in);
    while((ClientSocket = accept(ListenSocket, (struct sockaddr *)&client, &c)) != INVALID_SOCKET)
    {
        printf("Connection accepted\n");

        // Send the HTTP response
        send(ClientSocket, httpResponse, strlen(httpResponse), 0);

        printf("Hello message sent to client\n");
    }

    closesocket(ClientSocket);
    WSACleanup();

    return 0;
}
