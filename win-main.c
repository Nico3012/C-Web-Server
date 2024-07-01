#include <winsock2.h>
#include <string.h>
#include <stdio.h>

#define DEFAULT_BUFLEN 512

int main()
{
    char *httpResponse = "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\nContent-Length: 12\r\n\r\nHello World!";
    
    // initialize variables
    int iResult;
    WSADATA wsaData;
    SOCKET ListenSocket;
    SOCKET AcceptSocket;
    int recvbuflen = DEFAULT_BUFLEN;
    char recvbuf[DEFAULT_BUFLEN] = "";

    // init Winsock
    iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (iResult != NO_ERROR)
    {
        printf("WSAStartup failed with error: %d\n", iResult);
        return 1;
    }

    // check Winsock version
    if (LOBYTE(wsaData.wVersion) != 2 || HIBYTE(wsaData.wVersion) != 2)
    {
        printf("Could not find a usable version of Winsock.dll\n");
        WSACleanup();
        return 1;
    }

    // create socket for listening for
    ListenSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (ListenSocket == INVALID_SOCKET)
    {
        printf("socket failed with error: %d\n", (int)WSAGetLastError());
        WSACleanup();
        return 1;
    }

    // create service
    struct sockaddr_in service;
    service.sin_family = AF_INET;
    service.sin_addr.s_addr = inet_addr("127.0.0.1");
    service.sin_port = htons(80);

    // bind socket
    iResult = bind(ListenSocket, (SOCKADDR *)&service, sizeof(service));
    if (iResult == SOCKET_ERROR)
    {
        printf("bind failed with error: %d\n", (int)WSAGetLastError());
        closesocket(ListenSocket);
        WSACleanup();
        return 1;
    }

    // listen on socket
    iResult = listen(ListenSocket, SOMAXCONN);
    if (iResult == SOCKET_ERROR)
    {
        printf("listen failed with error: %d\n", (int)WSAGetLastError());
        closesocket(ListenSocket);
        WSACleanup();
        return 1;
    }

    while (1)
    {
        // accept socket and store client socket
        AcceptSocket = accept(ListenSocket, NULL, NULL);
        if (AcceptSocket == INVALID_SOCKET)
        {
            printf("accept failed with error: %d\n", (int)WSAGetLastError());
            continue;
        }

        // receive data from client and print to console
        do
        {
            iResult = recv(AcceptSocket, recvbuf, recvbuflen, 0); // always stops here, since no more is sent and connection in not closed!
            if (iResult == SOCKET_ERROR)
            {
                printf("recv failed with error: %d\n", (int)WSAGetLastError());
                closesocket(AcceptSocket);
                continue;
            }
            else if (iResult > 0)
            {
                printf("%s\n", recvbuf);

                // check for http request ending: \r\n\r\n
                if (strstr(recvbuf, "\r\n\r\n")) {
                    break;
                }
            }
        } while (iResult > 0);

        // shutdown receive connection since no more data will be received
        iResult = shutdown(AcceptSocket, SD_RECEIVE);
        if (iResult == SOCKET_ERROR)
        {
            printf("shutdown failed with error: %d\n", (int)WSAGetLastError());
            closesocket(AcceptSocket);
            continue;
        }

        // send data to client
        iResult = send(AcceptSocket, httpResponse, (int)strlen(httpResponse), 0);
        if (iResult == SOCKET_ERROR)
        {
            printf("send failed with error: %d\n", (int)WSAGetLastError());
            closesocket(AcceptSocket);
            continue;
        }

        // shutdown send connection since no more data will be sent
        iResult = shutdown(AcceptSocket, SD_SEND);
        if (iResult == SOCKET_ERROR)
        {
            printf("shutdown failed with error: %d\n", (int)WSAGetLastError());
            closesocket(AcceptSocket);
            continue;
        }

        // close socket
        closesocket(AcceptSocket);
    }

    closesocket(ListenSocket);
    WSACleanup();
    return 0;
}
