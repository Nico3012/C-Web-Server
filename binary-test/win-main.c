#include <winsock2.h>

#include <string.h>
#include <stdio.h>

#define DEFAULT_BUFLEN 512

/* agenda */ /*

 init API
 create socket
 bind socket
 listen on socket
 while {
     accept client
     while {
         receive data
     }
     shutdown receiving
     send data to client
     shutdown sending
     close client
 }
 close socket
 release API

 */

void printHex(unsigned char *str, int len);

int main()
{
    // char *httpResponse = "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\nContent-Length: 12\r\n\r\nHello World!";
    unsigned char httpResponse[] = {0x48, 0x54, 0x54, 0x50, 0x2f, 0x31, 0x2e, 0x31, 0x20, 0x32, 0x30, 0x30, 0x20, 0x4f, 0x4b, 0xa, 0x43, 0x6f, 0x6e, 0x74, 0x65, 0x6e, 0x74, 0x2d, 0x54, 0x79, 0x70, 0x65, 0x3a, 0x20, 0x74, 0x65, 0x78, 0x74, 0x2f, 0x70, 0x6c, 0x61, 0x69, 0x6e, 0xa, 0x43, 0x6f, 0x6e, 0x74, 0x65, 0x6e, 0x74, 0x2d, 0x4c, 0x65, 0x6e, 0x67, 0x74, 0x68, 0x3a, 0x20, 0x31, 0x32, 0xa, 0xa, 0x48, 0x65, 0x6c, 0x6c, 0x6f, 0x20, 0x57, 0x6f, 0x72, 0x6c, 0x64, 0x21};
    // printHex(httpResponse, 73);

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
    // service.sin_addr.s_addr = inet_addr("127.0.0.1");
    service.sin_addr.s_addr = INADDR_ANY;
    service.sin_port = 0x901f;

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
        printf("accept\n");

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
            printf("recv\n");

            iResult = recv(AcceptSocket, recvbuf, recvbuflen, 0); // need timeout interrupt here!
            if (iResult == SOCKET_ERROR)
            {
                printf("recv failed with error: %d\n", (int)WSAGetLastError());
                closesocket(AcceptSocket);
                continue;
            }
            else if (iResult > 0)
            {
                // printf("%s\n", recvbuf);
                printHex(recvbuf, 512);

                exit(0);

                // check for http request ending: \r\n\r\n
                if (strstr(recvbuf, "\r\n\r\n"))
                {
                    break;
                }
            }
        } while (iResult > 0);

        printf("shutdown receive\n");

        // shutdown receive connection since no more data will be received
        iResult = shutdown(AcceptSocket, SD_RECEIVE);
        if (iResult == SOCKET_ERROR)
        {
            printf("shutdown failed with error: %d\n", (int)WSAGetLastError());
            closesocket(AcceptSocket);
            continue;
        }

        printf("send\n");

        // send data to client
        // iResult = send(AcceptSocket, httpResponse, (int)strlen(httpResponse), 0);
        iResult = send(AcceptSocket, httpResponse, 73, 0);
        if (iResult == SOCKET_ERROR)
        {
            printf("send failed with error: %d\n", (int)WSAGetLastError());
            closesocket(AcceptSocket);
            continue;
        }

        printf("shutdown send\n");

        // shutdown send connection since no more data will be sent
        iResult = shutdown(AcceptSocket, SD_SEND);
        if (iResult == SOCKET_ERROR)
        {
            printf("shutdown failed with error: %d\n", (int)WSAGetLastError());
            closesocket(AcceptSocket);
            continue;
        }

        printf("closesocket\n");

        // close socket
        closesocket(AcceptSocket);
    }

    closesocket(ListenSocket);
    WSACleanup();
    return 0;
}

void printHex(unsigned char *str, int len)
{
    while (len-- > 0) {
        printf("%02x ", *str);
        str++;
    }

    printf("\n");
}
