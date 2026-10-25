/*
 * Sci2Card command senders and response-status predicates,
 * 0x80077AFC..0x80077E24.
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

extern unsigned int Sci2Card_BuildPacket(Sci2Card *card, unsigned char *outBuf,
                                         int *outLen, unsigned char frameType,
                                         unsigned char subCmd, unsigned char *data,
                                         int dataLen);
extern void *memset(void *dst, int val, unsigned int n);

#pragma exceptions on
unsigned char Sci2Card_SendCmdSpace(Sci2Card *card)
{
    if (card->state != 0) {
        return 0;
    }
    if ((Sci2Card_BuildPacket(card, card->txBuf, &card->txLen, 2, 0x20, 0, 0) & 0xFF) == 1) {
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

unsigned char Sci2Card_SendCmdRetry(Sci2Card *card, unsigned char flag)
{
    unsigned char data;

    if (card->state != 0) {
        return 0;
    }
    data = '0';
    if (flag == 1) {
        data = '1';
    }
    if ((Sci2Card_BuildPacket(card, card->txBuf, &card->txLen, 2, 0x10, &data, 1) & 0xFF) == 1) {
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

unsigned char Sci2Card_GetResponseStatus(Sci2Card *card, unsigned char *status1,
                                         unsigned char *status2, unsigned char *status3)
{
    if (status1 == 0) {
        return 0;
    }
    *status1 = card->status1;
    *status2 = card->status2;
    *status3 = card->status3;
    return 1;
}

unsigned char Sci2Card_IsStatus3Zero(Sci2Card *card)
{
    return card->status3 == '0';
}

unsigned char Sci2Card_IsStatus1Zero(Sci2Card *card)
{
    return card->status1 == '0';
}

unsigned char Sci2Card_IsStatus1OneTwoThree(Sci2Card *card)
{
    if (card->status1 == '1' || card->status1 == '2' || card->status1 == '3') {
        return 1;
    }
    return 0;
}

unsigned char Sci2Card_IsStatus3Five(Sci2Card *card)
{
    return card->status3 == '5';
}

unsigned char Sci2Card_IsStatus2A(Sci2Card *card)
{
    return card->status2 == 'A';
}

unsigned char Sci2Card_IsStatus2Five(Sci2Card *card)
{
    return card->status2 == '5';
}

unsigned char Sci2Card_IsStatus2Three(Sci2Card *card)
{
    return card->status2 == '3';
}

unsigned char Sci2Card_IsStatus2One(Sci2Card *card)
{
    return card->status2 == '1';
}

unsigned char Sci2Card_IsStatus2Two(Sci2Card *card)
{
    return card->status2 == '2';
}

unsigned char Sci2Card_IsRetryExhausted(Sci2Card *card)
{
    return card->retry < 0;
}

unsigned char Sci2Card_IsStatusOk02(Sci2Card *card)
{
    if (card->status2 == '0' && card->status3 == '2') {
        return 1;
    }
    return 0;
}

unsigned char Sci2Card_IsStatusOkNonTerm(Sci2Card *card)
{
    if (card->retry < 0) {
        return 0;
    }
    if (card->status2 == '0' && card->status3 != '2' && card->status3 != '5') {
        return 1;
    }
    return 0;
}

void Sci2Card_ResetRetryCount(Sci2Card *card)
{
    card->retry = 8;
}

unsigned char Sci2Card_IsIdleOrExhausted(Sci2Card *card)
{
    if (card->retry < 0) {
        return 1;
    }
    if (card->state != 5 && card->state != 0) {
        return 0;
    }
    return 1;
}
