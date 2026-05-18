/*
 * card_eject @ 0x80077A54 (size 0xA8).
 *
 * Issues an Sci2Card EJECT frame (opcode 2, sub-cmd 0x80) when the
 * underlying card session is idle (state == 0). On success ack from
 * Sci2Card_BuildPacket (low-byte returns 1), transitions the session
 * to state 1, clears the per-session status bytes, zeroes the 0x102-byte
 * data buffer pointed at by self->buf, and primes the next-step
 * counters (self[5]=0, self[7]=8). Returns 1 on accepted eject, 0
 * otherwise.
 *
 * Sci2Card_BuildPacket is still under its placeholder name fn_80076910
 * in symbols.txt; this batch renames it to Sci2Card_BuildPacket (the
 * Ghidra-side label, signature already known: 7-arg packet builder
 * with frameType / subCmd / data / dataLen).
 */

extern unsigned int Sci2Card_BuildPacket(int *card, unsigned char *outBuf,
                                         int *outLen, unsigned char frameType,
                                         unsigned char subCmd, unsigned char *data,
                                         int dataLen);
extern void *memset(void *dst, int val, unsigned int n);

#pragma exceptions on
unsigned int card_eject(int *self) {
    if (*self != 0) {
        return 0;
    }
    if ((Sci2Card_BuildPacket(self, (unsigned char *)self[2], self + 3,
                              2, 0x80, (unsigned char *)0, 0) & 0xFF) == 1) {
        *self = 1;
        *(unsigned char *)((char *)self + 4) = 0;
        *(unsigned char *)((char *)self + 5) = 0;
        *(unsigned char *)((char *)self + 6) = 0;
        memset((void *)self[4], 0, 0x102);
        self[5] = 0;
        self[7] = 8;
        return 1;
    }
    return 0;
}
#pragma exceptions reset
