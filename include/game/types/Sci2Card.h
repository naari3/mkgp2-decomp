#ifndef GAME_TYPES_SCI2CARD_H
#define GAME_TYPES_SCI2CARD_H

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

#endif /* GAME_TYPES_SCI2CARD_H */
