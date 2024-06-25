#ifdef _WIN32 // WinSock
    // winsock2.h must be included before Windows.h
    // Windows.h is not needed in this project
    #include <winsock2.h>
#else // POSIX
    #include <sys/socket.h>
    #include <netinet/in.h>
#endif

int main()
{
    #ifdef _WIN32
        WSADATA wsadata;

        WSAStartup(MAKEWORD(2, 2), &wsadata);
    #endif

    return 0;
}
