#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <errno.h>

#include <string.h>
#include <stdio.h>

#define DEFAULT_BUFLEN 4096

/* agenda */ /*

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

 */

int createServer(void (*handleConnection)(char *recvbuf, int recvbuflen, char **respbuf, int *respbuflen))
{
    // initialize variables
    int iResult;
    int ListenSocket;
    int AcceptSocket;
    int recvbuflen = DEFAULT_BUFLEN;
    char recvbuf[DEFAULT_BUFLEN] = "";
    int respbuflen;
    char *respbuf;

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
    addr.sin_port = 0x901f;

    // bind socket // first difference to windows is struct sockaddr*, which differs to microsoft documentation
    iResult = bind(ListenSocket, (struct sockaddr *)&addr, sizeof(addr));
    if (iResult == -1)
    {
        printf("bind failed with error: %s\n", strerror(errno));
        close(ListenSocket);
        return 1;
    }

    // listen on socket
    iResult = listen(ListenSocket, SOMAXCONN);
    if (iResult == -1)
    {
        printf("listen failed with error: %s\n", strerror(errno));
        close(ListenSocket);
        return 1;
    }

    while (1)
    {
        // accept socket and store client socket
        AcceptSocket = accept(ListenSocket, NULL, NULL);
        if (AcceptSocket == -1)
        {
            printf("accept failed with error: %s\n", strerror(errno));
            continue;
        }

        // receive data from client and print to console
        do
        {
            iResult = recv(AcceptSocket, recvbuf, recvbuflen, 0); // need timeout interrupt here!
            if (iResult == -1)
            {
                printf("recv failed with error: %s\n", strerror(errno));
                close(AcceptSocket);
                continue;
            }
            else if (iResult > 0)
            {
                // printf("%s\n", recvbuf);

                // check for http request ending: \r\n\r\n
                // if (strstr(recvbuf, "\r\n\r\n"))
                // {
                //     break;
                // }

                break;
            }
        } while (iResult > 0);

        // shutdown receive connection since no more data will be received
        iResult = shutdown(AcceptSocket, SHUT_RD);
        if (iResult == -1)
        {
            printf("shutdown failed with error: %s\n", strerror(errno));
            close(AcceptSocket);
            continue;
        }

        handleConnection(recvbuf, recvbuflen, &respbuf, &respbuflen);

        // send data to client
        iResult = send(AcceptSocket, respbuf, respbuflen, 0);
        if (iResult == -1)
        {
            printf("send failed with error: %s\n", strerror(errno));
            close(AcceptSocket);
            continue;
        }

        // shutdown send connection since no more data will be sent
        iResult = shutdown(AcceptSocket, SHUT_WR);
        if (iResult == -1)
        {
            printf("shutdown failed with error: %s\n", strerror(errno));
            close(AcceptSocket);
            continue;
        }

        // close socket
        close(AcceptSocket);
    }

    close(ListenSocket);
    return 0;
}
