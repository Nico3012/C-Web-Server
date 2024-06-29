// all errors are named with the function name and error added in PascalCase or CamelCase!
// if a error exists, the error code will be thrown to the console with the error variable name and 1 is returned!

#include <winsock2.h>

int main()
{
    // init Winsock 2.2
    WORD wVersionRequested = MAKEWORD(2, 2);
    WSADATA wsaData;
    int WSAStartupError = WSAStartup(wVersionRequested, &wsaData);
    if (WSAStartupError != 0)
    {
        printf("WSAStartupError: %d\n", WSAStartupError);
        return 1;
    }

    // check for version errors:
    if (LOBYTE(wsaData.wVersion) != 2 || HIBYTE(wsaData.wVersion) != 2)
    {
        printf("Could not find a usable version of Winsock.dll\n");

        // stop usage of Winsock 2-DLL
        int WSACleanupError = WSACleanup();
        if (WSACleanupError == SOCKET_ERROR)
        {
            int WSACleanupErrorCode = WSAGetLastError();
            printf("WSACleanupError: %d\n", WSACleanupErrorCode);
        }

        return 1;
    }



    // stop usage of Winsock 2-DLL
    int WSACleanupError = WSACleanup();
    if (WSACleanupError == SOCKET_ERROR)
    {
        int WSACleanupErrorCode = WSAGetLastError();
        printf("WSACleanupError: %d\n", WSACleanupErrorCode);
        return 1;
    }

    return 0;
}
