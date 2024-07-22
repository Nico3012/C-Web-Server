#include <stdio.h>
#include <string.h>
#include "server/server.h" // dont start include with "./" instead imediately type foldername && "/" seperator works on any platform (including windows)

void printHex(unsigned char *str, int len);

void handleConnection(char *recvbuf, int recvbuflen, char **respbuf, int *respbuflen);

int connectionIndex = 0;

int main()
{
    return createServer(*handleConnection);
}

void printHex(unsigned char *str, int len)
{
    while (len-- > 0)
    {
        printf("%02x ", *str);
        str++;
    }

    printf("\n");
}

void handleConnection(char *recvbuf, int recvbuflen, char **respbuf, int *respbuflen)
{
    // printf("connection %d\n", connectionIndex);

    /*if (connectionIndex == 0 || connectionIndex == 1)
    {
        printHex(recvbuf, recvbuflen);

        char res[] = {
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

            // Server Random
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

            // Session ID
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

            // Cipher Suite
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


    }*/

    *respbuf = "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\nContent-Length: 12\r\n\r\nHello World!";
    *respbuflen = 78;

    // connectionIndex++;
}
