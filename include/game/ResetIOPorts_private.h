#ifndef RESET_IO_PORTS_PRIVATE_H
#define RESET_IO_PORTS_PRIVATE_H
#include "game/types/bitfields.h"

/* PCB port descriptor: the reset state occupies the low seven status bits. */
typedef struct ResetIOPort {
    unsigned char header;
    unsigned char pad_001[0xA34];
    BITFIELDS2(unsigned char highStatus:1, unsigned char status:7)
    unsigned char pad_A36[6];
} ResetIOPort; /* 0xA3C */

#endif
