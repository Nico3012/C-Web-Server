#ifdef _WIN32
    // Windows-specific includes
    // winsock2.h must be included before windows.h | Windows.h
    // windows.h | Windows.h is not needed in this project
    #include <winsock2.h>
#else
    // Unix-specific includes
    #include <sys/socket.h>
    #include <netinet/in.h>
#endif

// imports from c default library
#include <stdio.h>
#include <string.h>

int main()
{
    char *httpResponse = "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\nContent-Length: 12\r\n\r\nHello World!";

    // init winsocket in windown with version 2.2
    #ifdef _WIN32
        WSADATA wsaData;
        WSAStartup(MAKEWORD(2, 2), &wsaData);
    #endif

    printf("initialized\n");

    // create socket and store it in s variable
    // create client variable c
    #ifdef _WIN32
        SOCKET s = socket(AF_INET, SOCK_STREAM, 0);
        SOCKET c;
    #else
        int s = socket(AF_INET, SOCK_STREAM, 0);
        int c;
    #endif

    printf("created socket\n");

    // bind socket
    #ifdef _WIN32
        struct sockaddr_in addr;
        addr.sin_family = AF_INET;
        addr.sin_addr.s_addr = 0; // use all local interfaces
        addr.sin_port = htons(8080);
        bind(s, (struct sockaddr *)&addr, sizeof(addr));
    #else
        struct sockaddr_in addr = {
            AF_INET,
            0x901f // port number in opposite direction (8080)
        };
        bind(s, &addr, sizeof(addr));
    #endif

    printf("binded\n");

    // listen socket
    #ifdef _WIN32
        listen(s, 10); // ten is the number of connections that can wait until we are rejecting new connections
    #else
        listen(s, 10); // ten is the number of connections that can wait until we are rejecting new connections
    #endif

    printf("listend\n");

    while (1) {
        // accept client socket
        #ifdef _WIN32
            c = accept(s, 0, 0);
        #else
            c = accept(s, 0, 0);
        #endif

        // send data
        #ifdef _WIN32
            send(c, httpResponse, strlen(httpResponse), 0);
        #else
            write(c, httpResponse, strlen(httpResponse));
            // close(c);
            // close(s);
        #endif
    }

    return 0;
}
