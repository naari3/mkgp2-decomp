/*
 * Sci2Card frame builder, 0x80076910..0x80076A80.
 * Frame: type, length, sub-command, three zero bytes, payload, ETX (3),
 * then an XOR checksum over the length byte through the ETX.
 */

extern void *memcpy(void *dst, const void *src, unsigned int n);

#pragma exceptions on
unsigned char Sci2Card_BuildPacket(void *card, unsigned char *buf, int *outLen,
                                   unsigned char frameType, unsigned char subCmd,
                                   unsigned char *data, int dataLen)
{
    unsigned char *p;
    unsigned char *q;
    int sum;
    int i;

    if (data == 0 && dataLen > 0) {
        return 0;
    }
    if (data != 0 && dataLen <= 0) {
        return 0;
    }
    if (dataLen > 0xFF) {
        return 0;
    }
    buf[0] = frameType;
    buf[1] = 6;
    buf[1] += (unsigned char)dataLen;
    buf[2] = subCmd;
    buf[3] = 0;
    buf[4] = 0;
    buf[5] = 0;
    p = buf + 6;
    if (dataLen > 0) {
        memcpy(p, data, dataLen);
        p += dataLen;
    }
    *p = 3;
    q = buf + 2;
    sum = buf[1];
    for (i = dataLen + 5; i > 0; i--) {
        sum ^= *q++;
    }
    p[1] = sum;
    *outLen = dataLen + 8;
    return 1;
}
#pragma exceptions reset
