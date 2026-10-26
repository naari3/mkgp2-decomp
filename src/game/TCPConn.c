/* TCPConn rx-message peek/consume helpers.
 *
 * conn layout used here (offsets in bytes):
 *   +0x08  role                (1 = incoming connection)
 *   +0x24  rxReadPos
 *   +0x28  rxWritePos
 *   +0x40  rxBuf base pointer
 *
 * Each message in the rx buffer is laid out as:
 *   u16 msg_type
 *   u16 msg_size  (includes the 4-byte header)
 *   u8  payload[msg_size - 4]
 */

int TCPConn_ConsumeRxMessage(int conn) {
    unsigned int avail;
    unsigned short *msgPtr;

    if (*(int *)(conn + 8) != 1) {
        return 0;
    }
    avail = (*(int *)(conn + 0x28) - *(int *)(conn + 0x24)) & 0xffff;
    msgPtr = (unsigned short *)(*(int *)(conn + 0x40) + *(int *)(conn + 0x24));
    if (avail < 4) {
        msgPtr = (unsigned short *)0;
    } else if (avail < msgPtr[1]) {
        msgPtr = (unsigned short *)0;
    } else if (*msgPtr == 0) {
        msgPtr = (unsigned short *)0;
    }
    if (msgPtr == (unsigned short *)0) {
        return 0;
    }
    *(unsigned int *)(conn + 0x24) += msgPtr[1];
    return 1;
}

static inline unsigned short *TCPConn_PeekHeader(int conn)
{
    unsigned short avail = *(int *)(conn + 0x28) - *(int *)(conn + 0x24);
    unsigned short *msgPtr = (unsigned short *)(*(int *)(conn + 0x40) + *(int *)(conn + 0x24));
    if (avail < 4) {
        return (unsigned short *)0;
    }
    if (avail < msgPtr[1]) {
        return (unsigned short *)0;
    }
    if (*msgPtr == 0) {
        return (unsigned short *)0;
    }
    return msgPtr;
}

unsigned short TCPConn_PeekRxMessage(int conn, unsigned short *out_msgType, void **out_payload) {
    unsigned short *msgPtr;

    if (*(int *)(conn + 8) != 1) {
        return 0;
    }
    msgPtr = TCPConn_PeekHeader(conn);
    if (msgPtr == (unsigned short *)0) {
        return 0;
    }
    if (out_msgType) {
        *out_msgType = *msgPtr;
    }
    if (out_payload) {
        *out_payload = msgPtr + 2;
    }
    return msgPtr[1] - 4;
}
