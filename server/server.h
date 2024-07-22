int createServer(void (*handleConnection)(char *recvbuf, int recvbuflen, char **respbuf, int *respbuflen));
