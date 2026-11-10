extern int acGetLastError(unsigned int socket);

#pragma exceptions on
int TCPConn_LogError(int result, unsigned int socket, const char *context) {
    if (result <= 0 && result == -1) {
        return acGetLastError(socket);
    }
    return result;
}
#pragma exceptions reset
