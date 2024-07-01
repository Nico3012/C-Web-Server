// all errors are named with the function name and error added in PascalCase or CamelCase!
// if a error exists, the error code will be thrown to the console with the error variable name and 1 is returned!

#include <winsock2.h>

int main()
{
    char *httpResponse = "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\nContent-Length: 12\r\n\r\nHello World!";

    // init Winsock 2.2:
    WORD wVersionRequested = MAKEWORD(2, 2);
    WSADATA wsaData;
    int WSAStartupError = WSAStartup(wVersionRequested, &wsaData);
    if (WSAStartupError != 0)
    {
        printf("WSAStartupError: %d\n", WSAStartupError);
        return 1;
    }

    // check for version errors:
    if (LOBYTE(wsaData.wVersion) != 2 || HIBYTE(wsaData.wVersion) != 2)
    {
        printf("Could not find a usable version of Winsock.dll\n");

        // stop usage of Winsock 2-DLL
        int WSACleanupError = 0;
        WSACleanupError = WSACleanup();
        if (WSACleanupError == SOCKET_ERROR)
        {
            int WSACleanupErrorCode = WSAGetLastError();
            printf("WSACleanupError: %d\n", WSACleanupErrorCode);
        }

        return 1;
    }

    // create tcp socket:
    SOCKET sock = INVALID_SOCKET;
    sock = socket(AF_INET, SOCK_STREAM, 6);
    if (sock == INVALID_SOCKET)
    {
        int socketErrorCode = WSAGetLastError();
        printf("socketError: %d\n", socketErrorCode);

        // stop usage of Winsock 2-DLL
        int WSACleanupError = 0;
        WSACleanupError = WSACleanup();
        if (WSACleanupError == SOCKET_ERROR)
        {
            int WSACleanupErrorCode = WSAGetLastError();
            printf("WSACleanupError: %d\n", WSACleanupErrorCode);
        }

        return 1;
    }

    // bind socket: (maybe change htons and inet_addr!)
    struct sockaddr_in service;
    service.sin_family = AF_INET;
    service.sin_addr.s_addr = inet_addr("127.0.0.1");
    service.sin_port = htons(80);
    int bindError = 0;
    bindError = bind(sock, (SOCKADDR *)&service, sizeof(service));
    if (bindError == SOCKET_ERROR)
    {
        int bindErrorCode = WSAGetLastError();
        printf("bindError: %d\n", bindErrorCode);

        // close sock socket
        int closesocketError = 0;
        closesocketError = closesocket(sock);
        if (closesocketError == SOCKET_ERROR)
        {
            int closesocketErrorCode = WSAGetLastError();
            printf("closesocketError: %d\n", closesocketErrorCode);
        }

        // stop usage of Winsock 2-DLL
        int WSACleanupError = 0;
        WSACleanupError = WSACleanup();
        if (WSACleanupError == SOCKET_ERROR)
        {
            int WSACleanupErrorCode = WSAGetLastError();
            printf("WSACleanupError: %d\n", WSACleanupErrorCode);
        }

        return 1;
    }

    // listen on sock socket
    int listenError = 0;
    listenError = listen(sock, SOMAXCONN);
    if (listenError == SOCKET_ERROR)
    {
        int listenErrorCode = WSAGetLastError();
        printf("listenError: %d\n", listenErrorCode);

        // close sock socket
        int closesocketError = 0;
        closesocketError = closesocket(sock);
        if (closesocketError == SOCKET_ERROR)
        {
            int closesocketErrorCode = WSAGetLastError();
            printf("closesocketError: %d\n", closesocketErrorCode);
        }

        // stop usage of Winsock 2-DLL
        int WSACleanupError = 0;
        WSACleanupError = WSACleanup();
        if (WSACleanupError == SOCKET_ERROR)
        {
            int WSACleanupErrorCode = WSAGetLastError();
            printf("WSACleanupError: %d\n", WSACleanupErrorCode);
        }

        return 1;
    }

    SOCKET AcceptSocket;

    while (1)
    {
        // accept client socket
        AcceptSocket = accept(sock, NULL, NULL);
        if (AcceptSocket == INVALID_SOCKET)
        {
            int acceptErrorCode = WSAGetLastError();
            printf("acceptError: %d\n", acceptErrorCode);
            continue;
        }

        // send data to client
        int sendError = send(AcceptSocket, httpResponse, (int)strlen(httpResponse), 0);
        if (sendError == SOCKET_ERROR)
        {
            int sendErrorCode = WSAGetLastError();
            printf("sendError: %d\n", sendErrorCode);

            // close AcceptSocket socket
            int closesocketError = 0;
            closesocketError = closesocket(AcceptSocket);
            if (closesocketError == SOCKET_ERROR)
            {
                int closesocketErrorCode = WSAGetLastError();
                printf("closesocketError: %d\n", closesocketErrorCode);
            }

            continue;
        }

        
    }

    // stop usage of Winsock 2-DLL:
    int WSACleanupError = 0;
    WSACleanupError = WSACleanup();
    if (WSACleanupError == SOCKET_ERROR)
    {
        int WSACleanupErrorCode = WSAGetLastError();
        printf("WSACleanupError: %d\n", WSACleanupErrorCode);
        return 1;
    }

    return 0;
}
