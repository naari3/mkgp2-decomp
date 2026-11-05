#ifndef PLAYER_DATA_RESET_PRIVATE_H
#define PLAYER_DATA_RESET_PRIVATE_H
#include "game/PlayerDataProgressPrivate.h"
/* View of the reset fields that the progress-only record leaves opaque. */
typedef struct PlayerDataReset {
    unsigned short name[6];
    unsigned char mode, character;
    unsigned char prefix0E[0xA8-0x0E];
    unsigned char unlockFlags[0x79];
    unsigned char remapFlags[0x69];
    unsigned char align18A[2];
    int selected[3];
    unsigned char speed, field199, field19A, field19B, field19C;
    unsigned char field19D, field19E, volume, field1A0;
    unsigned char align1A1[3];
    int language;
    unsigned char field1A8, align1A9[3];
    int raceCount;
    unsigned char field1B0, field1B1, align1B2[2];
    int coinMilage;
    unsigned char variant, kartVariant, cupRank[3][8];
    unsigned char align1D2[2];
    int field1D4;
    unsigned char field1D8, field1D9, field1DA, field1DB;
} PlayerDataReset;
#endif
