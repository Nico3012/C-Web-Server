// https://tls13.xargs.org/#client-hello/annotated

#include <stdio.h>

int main()
{
    printf("Hallo Welt!\n");
    return 0;
}

void getClientHello()
{
    unsigned char clientHello[67];

    // Record Header:
    clientHello[0] = 0x16;
    clientHello[1] = 0x03;
    clientHello[2] = 0x01;
    clientHello[3] = 0xf8;

    // Handshake Header:
    clientHello[4] = 0x01;
    clientHello[5] = 0x00;
    clientHello[6] = 0x00;
    clientHello[7] = 0xf4;

    // Client Version:
    clientHello[8] = 0x03;
    clientHello[9] = 0x03;

    // Client Random:
    clientHello[10] = 0x00;
    clientHello[11] = 0x01;
    clientHello[12] = 0x02;
    clientHello[13] = 0x03;
    clientHello[14] = 0x04;
    clientHello[15] = 0x05;
    clientHello[16] = 0x06;
    clientHello[17] = 0x07;
    clientHello[18] = 0x08;
    clientHello[19] = 0x09;
    clientHello[20] = 0x0a;
    clientHello[21] = 0x0b;
    clientHello[22] = 0x0c;
    clientHello[23] = 0x0d;
    clientHello[24] = 0x0e;
    clientHello[25] = 0x0f;
    clientHello[26] = 0x10;
    clientHello[27] = 0x11;
    clientHello[28] = 0x12;
    clientHello[29] = 0x13;
    clientHello[30] = 0x14;
    clientHello[31] = 0x15;
    clientHello[32] = 0x16;
    clientHello[33] = 0x17;
    clientHello[34] = 0x18;
    clientHello[35] = 0x19;
    clientHello[36] = 0x1a;
    clientHello[37] = 0x1b;
    clientHello[38] = 0x1c;
    clientHello[39] = 0x1d;
    clientHello[40] = 0x1e;
    clientHello[41] = 0x1f;

    // Session ID:
    clientHello[42] = 0x20;
    clientHello[43] = 0xe0;
    clientHello[44] = 0xe1;
    clientHello[45] = 0xe2;
    clientHello[46] = 0xe3;
    clientHello[47] = 0xe4;
    clientHello[48] = 0xe5;
    clientHello[49] = 0xe6;
    clientHello[50] = 0xe7;
    clientHello[51] = 0xe8;
    clientHello[52] = 0xe9;
    clientHello[53] = 0xea;
    clientHello[54] = 0xeb;
    clientHello[55] = 0xec;
    clientHello[56] = 0xed;
    clientHello[57] = 0xee;
    clientHello[58] = 0xef;
    clientHello[59] = 0xf0;
    clientHello[60] = 0xf1;
    clientHello[61] = 0xf2;
    clientHello[62] = 0xf3;
    clientHello[63] = 0xf4;
    clientHello[64] = 0xf5;
    clientHello[65] = 0xf6;
    clientHello[66] = 0xf7;
    clientHello[67] = 0xf8;
    clientHello[68] = 0xf9;
    clientHello[69] = 0xfa;
    clientHello[70] = 0xfb;
    clientHello[71] = 0xfc;
    clientHello[72] = 0xfd;
    clientHello[73] = 0xfe;
    clientHello[74] = 0xff;

    // Cipher Suites:
    clientHello[75] = 0x00;
    clientHello[76] = 0x08;
    clientHello[77] = 0x13;
    clientHello[78] = 0x02;
    clientHello[79] = 0x13;
    clientHello[80] = 0x03;
    clientHello[81] = 0x13;
    clientHello[82] = 0x01;
    clientHello[83] = 0x00;
    clientHello[84] = 0xff;

    // Compression Methods:
    clientHello[85] = 0x01;
    clientHello[86] = 0x00;

    // Extensions Length:
    clientHello[85] = 0x00;
    clientHello[86] = 0xa3;

    // ...
}

void getServerHello()
{
    unsigned char serverHello[] = {
        // Record Header:
        0x16,
        0x03,
        0x03,
        0x00,
        0x7a,

        // Handshake Header:
        0x02,
        0x00,
        0x00,
        0x76,

        // Server Version:
        0x03,
        0x03,
    };
}
