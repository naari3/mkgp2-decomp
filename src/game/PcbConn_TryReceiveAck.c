/* Wait for and consume a pending TCP acknowledgement, 0x80086CCC..0x80086D6C. */

typedef struct PcbConnAckView {
    int socket;
    unsigned char pad_04[0x48];
    unsigned char ackPending;
} PcbConnAckView;

extern int acPollResponse(int socket);
extern int acReadResponse(int socket);
extern int TCPConn_LogError(int result, int socket, const char *message);
extern const char lbl_806D31C8[5];

#pragma exceptions on
int PcbConn_TryReceiveAck(PcbConnAckView *conn)
{
    int tries;
    int result;

    if (conn->ackPending == 0) {
        return 0;
    }
    tries = 0;
    while (acPollResponse(conn->socket) != 1) {
        if (++tries > 0x800) {
            return 0;
        }
    }
    result = acReadResponse(conn->socket);
    if (result < 0) {
        TCPConn_LogError(result, conn->socket, lbl_806D31C8);
        return 0;
    }
    conn->ackPending = 0;
    return 1;
}
#pragma exceptions reset
