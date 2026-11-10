#ifndef GAME_TYPES_CARDPRINTERSTATEPTR_H
#define GAME_TYPES_CARDPRINTERSTATEPTR_H

typedef struct CardPrinterStatePtr {
    int thisDelta;
    int vtblOffset;
    void *func;
} CardPrinterStatePtr;

#endif /* GAME_TYPES_CARDPRINTERSTATEPTR_H */
