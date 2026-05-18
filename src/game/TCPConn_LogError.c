extern int acGetLastError(unsigned int socket);

#pragma exceptions on
void TCPConn_LogError(int result, unsigned int socket, const char *context) {
    if (result <= 0 && result == -1) {
        acGetLastError(socket);
    }
}
#pragma exceptions reset
