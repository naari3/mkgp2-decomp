#ifndef GAME_PCBSLOTRESET_PRIVATE_H
#define GAME_PCBSLOTRESET_PRIVATE_H
#include "game/types/bitfields.h"

/* Same observed slot layout used by PCBCheckProcess. */
typedef struct PcbScratchSlot {
    unsigned char header[0x2C];
    unsigned char samples[64][0x28];
    void *primary;
    void *secondary;
    struct {
        BITFIELDS2(unsigned char local:1, unsigned char remaining:7)
    } flags;
    unsigned char reservedA35;
    short timeout;
    signed char readIndex, writeIndex;
    unsigned char reservedA3A[2];
} PcbScratchSlot;

#endif
