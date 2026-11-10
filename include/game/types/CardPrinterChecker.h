#ifndef GAME_TYPES_CARDPRINTERCHECKER_H
#define GAME_TYPES_CARDPRINTERCHECKER_H

#include "game/types/CardPrinterStatePtr.h"

typedef struct CardPrinterChecker {
    CardPrinterStatePtr state;
    int stage;
    int errorCode;
} CardPrinterChecker;

#endif /* GAME_TYPES_CARDPRINTERCHECKER_H */
