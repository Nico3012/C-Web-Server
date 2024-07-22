#include <stdio.h>
#include <string.h>
#include "server/server.h" // dont start include with "./" instead imediately type foldername && "/" seperator works on any platform (including windows)

void handleConnection(char* recvbuf, char* respbuf);

int main()
{
    return createServer(*handleConnection);
}

void handleConnection(char* recvbuf, char* respbuf)
{
    // printf("%s\n", recvbuf);

    char *httpResponse = "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\nContent-Length: 36\r\n\r\nHello from handleConnection function";
    strcpy(respbuf, httpResponse);
}
