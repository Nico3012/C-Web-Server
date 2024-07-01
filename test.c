#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <stdio.h>

int main()
{
    printf("%d\n", (int)IPPROTO_TCP);
    return 0;
}
