/*
 * Sci2Card command senders, 0x8007723C..0x800776CC.
 */

typedef struct Sci2Card {
    int state;
    unsigned char status1;
    unsigned char status2;
    unsigned char status3;
    unsigned char pad_07;
    unsigned char *txBuf;
    int txLen;
    unsigned char *rxBuf;
    int rxLen;
    int pad_18;
    int retry;
} Sci2Card;

extern unsigned char Sci2Card_BuildPacket(Sci2Card *card, unsigned char *outBuf,
                                          int *outLen, unsigned char frameType,
                                          unsigned char subCmd, unsigned char *data,
                                          int dataLen);
extern void *memset(void *dst, int val, unsigned int n);
extern void *memcpy(void *dst, const void *src, unsigned int n);
extern unsigned int strlen(const char *s);
extern void *FUN_8003b120(unsigned int size);
extern void MemoryManager_Free(void *ptr);

#pragma exceptions on
unsigned char Sci2Card_SendCmdPing(Sci2Card *card)
{
    if (Sci2Card_BuildPacket(card, card->txBuf, &card->txLen, 2, 0x40, 0, 0) == 1) {
        card->state = 1;
        card->status1 = 0;
        card->status2 = 0;
        card->status3 = 0;
        memset(card->rxBuf, 0, 0x102);
        card->rxLen = 0;
        card->retry = 8;
        return 1;
    }
    return 0;
}

unsigned char Sci2Card_SendCmdPrint(Sci2Card *card, int len, const void *text)
{
    unsigned char *buf;

    if (card->state != 0) {
        return 0;
    }
    if (len < 1 || len > 150) {
        return 0;
    }
    buf = (unsigned char *)FUN_8003b120(0x49);
    memset(buf, 0, 0x49);
    buf[0] = len;
    memcpy(buf + 1, text, 0x48);
    if (Sci2Card_BuildPacket(card, card->txBuf, &card->txLen, 2, 0x7A, buf, 0x49) == 1) {
        card->state = 1;
        card->status1 = 0;
        card->status2 = 0;
        card->status3 = 0;
        memset(card->rxBuf, 0, 0x102);
        card->rxLen = 0;
        card->retry = 8;
        MemoryManager_Free(buf);
        return 1;
    }
    MemoryManager_Free(buf);
    return 0;
}

unsigned char Sci2Card_SendCmdReset(Sci2Card *card)
{
    if (Sci2Card_BuildPacket(card, card->txBuf, &card->txLen, 2, 0xA0, 0, 0) == 1) {
        card->state = 1;
        card->status1 = 0;
        card->status2 = 0;
        card->status3 = 0;
        memset(card->rxBuf, 0, 0x102);
        card->rxLen = 0;
        card->retry = 8;
        return 1;
    }
    return 0;
}

unsigned char Sci2Card_SendCmdLedSet(Sci2Card *card, int last, int first)
{
    unsigned char data[2];

    if (card->state != 0) {
        return 0;
    }
    if (first < 1 || first > 23) {
        return 0;
    }
    if (last < 1 || last > 23) {
        return 0;
    }
    if (first > last) {
        return 0;
    }
    data[0] = first;
    data[1] = last;
    if (Sci2Card_BuildPacket(card, card->txBuf, &card->txLen, 2, 0x7D, data, 2) == 1) {
        card->state = 1;
        card->status1 = 0;
        card->status2 = 0;
        card->status3 = 0;
        memset(card->rxBuf, 0, 0x102);
        card->rxLen = 0;
        card->retry = 8;
        return 1;
    }
    return 0;
}

unsigned char Sci2Card_SendCmdRegister(Sci2Card *card, const char *name, unsigned char kind,
                                       unsigned char flagA, unsigned char flagB)
{
    int len;
    unsigned char *buf;
    unsigned char ok;

    if (card->state != 0) {
        return 0;
    }
    len = strlen(name) + 3;
    if (len > 0xF6) {
        return 0;
    }
    buf = (unsigned char *)FUN_8003b120(len + 1);
    memset(buf, 0, len + 1);
    if (flagA == 1) {
        buf[0] = '0';
    } else {
        buf[0] = '1';
    }
    if (flagB == 1) {
        buf[1] = '0';
    } else {
        buf[1] = '1';
    }
    buf[2] = kind;
    memcpy(buf + 3, name, strlen(name));
    ok = Sci2Card_BuildPacket(card, card->txBuf, &card->txLen, 2, 0x7C, buf, len);
    MemoryManager_Free(buf);
    if (ok == 1) {
        card->state = 1;
        card->status1 = 0;
        card->status2 = 0;
        card->status3 = 0;
        memset(card->rxBuf, 0, 0x102);
        card->rxLen = 0;
        card->retry = 8;
    }
    return ok;
}
#pragma exceptions reset
