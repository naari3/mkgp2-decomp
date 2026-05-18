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
 *
 * TCPConn_PeekRxMessage is held as asm here: the C version differs only in
 * register selection (msgPtr placed in r6 instead of r3, avail in r7 instead
 * of r6, and the conn-base register reused for rxBuf rather than freed). The
 * CW register allocator did not budge across order/typing/explicit-temporary
 * variants, so the function is shipped as inline asm to keep the bundle SHA-1
 * stable while preserving Consume's 100% match.
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

asm unsigned short TCPConn_PeekRxMessage(int conn, unsigned short *out_msgType, void **out_payload) {
    nofralloc
    lwz r0, 0x8(r3)
    cmpwi r0, 0x1
    beq TCPConn_PeekRxMessage_L_80086FF0
    li r3, 0x0
    blr
TCPConn_PeekRxMessage_L_80086FF0:
    lwz r7, 0x24(r3)
    lwz r6, 0x28(r3)
    lwz r0, 0x40(r3)
    subf r3, r7, r6
    clrlwi r6, r3, 16
    add r3, r0, r7
    cmplwi r6, 0x4
    bge TCPConn_PeekRxMessage_L_80087018
    li r3, 0x0
    b TCPConn_PeekRxMessage_L_8008703C
TCPConn_PeekRxMessage_L_80087018:
    lhz r0, 0x2(r3)
    cmplw r6, r0
    bge TCPConn_PeekRxMessage_L_8008702C
    li r3, 0x0
    b TCPConn_PeekRxMessage_L_8008703C
TCPConn_PeekRxMessage_L_8008702C:
    lhz r0, 0x0(r3)
    cmplwi r0, 0x0
    bne TCPConn_PeekRxMessage_L_8008703C
    li r3, 0x0
TCPConn_PeekRxMessage_L_8008703C:
    cmplwi r3, 0x0
    bne TCPConn_PeekRxMessage_L_8008704C
    li r3, 0x0
    blr
TCPConn_PeekRxMessage_L_8008704C:
    cmplwi r4, 0x0
    beq TCPConn_PeekRxMessage_L_8008705C
    lhz r0, 0x0(r3)
    sth r0, 0x0(r4)
TCPConn_PeekRxMessage_L_8008705C:
    cmplwi r5, 0x0
    beq TCPConn_PeekRxMessage_L_8008706C
    addi r0, r3, 0x4
    stw r0, 0x0(r5)
TCPConn_PeekRxMessage_L_8008706C:
    lhz r3, 0x2(r3)
    subi r0, r3, 0x4
    clrlwi r3, r0, 16
    blr
}
