#include <stdio.h>

void handleConnection(char* receivedData, char* responseData);
void runFunction(void (*handleConnection)(char* receivedData, char* responseData));

int main()
{
    runFunction(*handleConnection);

    return 0;
}

void handleConnection(char* receivedData, char* responseData)
{
    printf("received data inside handle Connection: %s\n", receivedData);

    responseData[0] = 'a';
    responseData[1] = 'b';
    responseData[2] = 0x00;
}

void runFunction(void (*handleConnection)(char* receivedData, char* responseData))
{
    char receivedData[512] = "Hello received data!";
    char responseData[512]; // will be written from handleConnection function

    handleConnection(receivedData, responseData);

    printf("responseData: %s\n", responseData);
}
