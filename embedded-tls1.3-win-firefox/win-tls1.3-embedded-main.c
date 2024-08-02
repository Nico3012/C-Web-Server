#include <winsock2.h>

#include <string.h>
#include <stdio.h>

#define DEFAULT_BUFLEN 4096

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

void printHex(unsigned char *str, int offset, int len);

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
        // accept socket and store client socket
        AcceptSocket = accept(ListenSocket, NULL, NULL);
        if (AcceptSocket == INVALID_SOCKET)
        {
            printf("accept failed with error: %d\n", (int)WSAGetLastError());
            continue;
        }

        /////////////////////////////////////////////////////////////////////////////////////////////////////////
        /////////////////////////////////////////////////////////////////////////////////////////////////////////
        /////////////////////////////////////////////////////////////////////////////////////////////////////////
        /////////////////////////////////////////////////////////////////////////////////////////////////////////
        /////////////////////////////////////////////////////////////////////////////////////////////////////////
        /////////////////////////////////////////////////////////////////////////////////////////////////////////
        /////////////////////////////////////////////////////////////////////////////////////////////////////////
        /////////////////////////////////////////////////////////////////////////////////////////////////////////
        /////////////////////////////////////////////////////////////////////////////////////////////////////////
        /////////////////////////////////////////////////////////////////////////////////////////////////////////

        // receive data from client and print to console
        iResult = recv(AcceptSocket, recvbuf, recvbuflen, 0);
        if (iResult == SOCKET_ERROR)
        {
            printf("recv failed with error: %d\n", (int)WSAGetLastError());
            closesocket(AcceptSocket);
            continue;
        }

        if (1) // verify client hello
        {
            if (recvbuf[0] != 0x16 && recvbuf[1] != 0x03 && recvbuf[2] != 0x01)
            {
                printf("Error on tls client hello\n");
                continue;
            }

            printHex(recvbuf, 0, 700);
        }

        int serverHelloLen = 127;
        char serverHello[] = {
            // Record Header
            0x16,
            0x03,
            0x03,
            0x00,
            0x7a,

            // Handshake Header
            0x02,
            0x00,
            0x00,
            0x76,

            // Server Version
            0x03,
            0x03,

            // Server Random (just generate random data)
            0x70,
            0x71,
            0x72,
            0x73,
            0x74,
            0x75,
            0x76,
            0x77,
            0x78,
            0x79,
            0x7a,
            0x7b,
            0x7c,
            0x7d,
            0x7e,
            0x7f,
            0x80,
            0x81,
            0x82,
            0x83,
            0x84,
            0x85,
            0x86,
            0x87,
            0x88,
            0x89,
            0x8a,
            0x8b,
            0x8c,
            0x8d,
            0x8e,
            0x8f,

            // Session ID (just generate random data)
            0x20,
            0xe0,
            0xe1,
            0xe2,
            0xe3,
            0xe4,
            0xe5,
            0xe6,
            0xe7,
            0xe8,
            0xe9,
            0xea,
            0xeb,
            0xec,
            0xed,
            0xee,
            0xef,
            0xf0,
            0xf1,
            0xf2,
            0xf3,
            0xf4,
            0xf5,
            0xf6,
            0xf7,
            0xf8,
            0xf9,
            0xfa,
            0xfb,
            0xfc,
            0xfd,
            0xfe,
            0xff,

            // Cipher Suite // (TLS_AES_256_GCM_SHA384)
            0x13,
            0x02,

            // Compression Method
            0x00,

            // Extensions Length
            0x00,
            0x2e,

            // Extension - Supported Versions
            0x00,
            0x2b,
            0x00,
            0x02,
            0x03,
            0x04,

            // Extension - Key Share
            0x00,
            0x33,
            0x00,
            0x24,
            0x00,
            0x1d,
            0x00,
            0x20,

            // public key
            0x9f,
            0xd7,
            0xad,
            0x6d,
            0xcf,
            0xf4,
            0x29,
            0x8d,
            0xd3,
            0xf9,
            0x6d,
            0x5b,
            0x1b,
            0x2a,
            0xf9,
            0x10,
            0xa0,
            0x53,
            0x5b,
            0x14,
            0x88,
            0xd7,
            0xf8,
            0xfa,
            0xbb,
            0x34,
            0x9a,
            0x98,
            0x28,
            0x80,
            0xb6,
            0x15,
        };

        // send data to client
        iResult = send(AcceptSocket, serverHello, serverHelloLen, 0);
        if (iResult == SOCKET_ERROR)
        {
            printf("send failed with error: %d\n", (int)WSAGetLastError());
            closesocket(AcceptSocket);
            continue;
        }

        // receive data from client and print to console
        iResult = recv(AcceptSocket, recvbuf, recvbuflen, 0);
        if (iResult == SOCKET_ERROR)
        {
            printf("recv failed with error: %d\n", (int)WSAGetLastError());
            closesocket(AcceptSocket);
            continue;
        }

        /////////////////////////////////////////////////////////////////////////////////////////////////////////
        /////////////////////////////////////////////////////////////////////////////////////////////////////////
        /////////////////////////////////////////////////////////////////////////////////////////////////////////
        /////////////////////////////////////////////////////////////////////////////////////////////////////////
        /////////////////////////////////////////////////////////////////////////////////////////////////////////
        /////////////////////////////////////////////////////////////////////////////////////////////////////////
        /////////////////////////////////////////////////////////////////////////////////////////////////////////
        /////////////////////////////////////////////////////////////////////////////////////////////////////////
        /////////////////////////////////////////////////////////////////////////////////////////////////////////
        /////////////////////////////////////////////////////////////////////////////////////////////////////////

        // shutdown receive connection since no more data will be received
        iResult = shutdown(AcceptSocket, SD_RECEIVE);
        if (iResult == SOCKET_ERROR)
        {
            printf("shutdown failed with error: %d\n", (int)WSAGetLastError());
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

void printHex(unsigned char *str, int offset, int len)
{
    str += offset;

    while (len-- > 0)
    {
        printf("%02x ", *str);
        str++;
    }

    printf("\n");
}
