/*
 * Sci2Card forced-failure and option/cleaning commands, 0x80077840..0x80077A54.
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

#pragma exceptions on
unsigned char Sci2Card_ForceFailState(Sci2Card *card)
{
    if (card->state != 0) {
        return 0;
    }
    card->state = 1;
    card->status1 = 0;
    card->status2 = 0;
    card->status3 = 0;
    memset(card->rxBuf, 0, 0x102);
    card->rxLen = 0;
    card->retry = 8;
    card->state = 3;
    return 1;
}

unsigned char Sci2Card_SendCmdOptions(Sci2Card *card, unsigned char a, unsigned char b)
{
    unsigned char data[3];

    if (card->state != 0) {
        return 0;
    }
    data[0] = (a == 1) ? '0' : '2';
    if (b == 1) {
        data[1] = '0';
    } else {
        data[1] = '1';
    }
    data[2] = '0';
    if (Sci2Card_BuildPacket(card, card->txBuf, &card->txLen, 2, 0x33, data, 3) == 1) {
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

unsigned char Sci2Card_SendCmdCleaning(Sci2Card *card)
{
    if (card->state != 0) {
        return 0;
    }
    if (Sci2Card_BuildPacket(card, card->txBuf, &card->txLen, 2, 0xB0, 0, 0) == 1) {
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
#pragma exceptions reset
