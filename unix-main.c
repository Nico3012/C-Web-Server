#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <stdio.h>

#define DEFAULT_BUFLEN 512

/* agenda *//*

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

int main()
{
    return 0;
}
