#include <sys/socket.h>
#include <netinet/in.h>
#include <errno.h>

#include <string.h>
#include <stdio.h>

#define DEFAULT_BUFLEN 512

/* agenda *//*

create socket                   [1]
bind socket                     [0]
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

*/

int main()
{
    char *httpResponse = "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\nContent-Length: 12\r\n\r\nHello World!";

    // initialize variables
    int iResult;
    int ListenSocket;
    int AcceptSocket;
    int recvbuflen = DEFAULT_BUFLEN;
    char recvbuf[DEFAULT_BUFLEN] = "";

    // create socket for listening for
    ListenSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (ListenSocket == -1)
    {
        printf("socket failed with error: %s\n", strerror(errno));
        return 1;
    }

    // create addr
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    // addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    addr.sin_addr.s_addr = INADDR_ANY;
    addr.sin_port = htons(80);

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
