#ifdef _WIN32
    /* Windows-specific includes */
    // winsock2.h must be included before windows.h | Windows.h
    // windows.h | Windows.h is not needed in this project
    #include <winsock2.h>
#else
    /* Unix-specific includes */
    #include <sys/socket.h>
    #include <netinet/in.h>
#endif

#include <stdio.h>

int main()
{
    #ifdef _WIN32
        // Initialize WSA variables
        WSADATA wsaData;
        int wsaerr = WSAStartup(MAKEWORD(2, 2), &wsaData);

        // Check for initialization errors
        if (wsaerr != 0) {
            printf("ws2_32.dll was not found!");
            return 1;
        }

        // Create a socket
        SOCKET serverSocket;
        serverSocket = INVALID_SOCKET;
        serverSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

        // Check for socket creation error
        if (serverSocket == INVALID_SOCKET) {
            printf("creating serverSocket failed!");
            WSACleanup();
            return 1;
        }

        // Bind the socket to an IP address and port number
        struct sockaddr_in addr;
        addr.sin_family = AF_INET;
        addr.sin_addr.s_addr = inet_addr("127.0.0.1"); // inet_addr("127.0.0.1") | 0
        addr.sin_port = htons(80);

        // Use bind function and check for errors
        if (bind(serverSocket, &addr, sizeof(addr)) == SOCKET_ERROR) {
            printf("bind() failed!");
            return 1;
        }

        // Listen for incoming connections and check for errors
        if (listen(serverSocket, 1) == SOCKET_ERROR) {
            printf("listen() function failed! Error listening on socket!");
            return 1;
        }

        // Accept incoming connections
        SOCKET acceptSocket;
        acceptSocket = accept(serverSocket, 0, 0);
    #endif

    return 0;
}
