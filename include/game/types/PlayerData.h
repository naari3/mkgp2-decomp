#ifndef GAME_TYPES_PLAYERDATA_H
#define GAME_TYPES_PLAYERDATA_H

typedef struct PlayerData {
    char pad000[0xA8];
    unsigned char unlockFlags[0x79];
    unsigned char extraFlags[3];
    char pad124[0x1AC - 0x124];
    int raceCount;
    char pad1B0[4];
    int coinMilage;
    unsigned char variant;
    unsigned char kartVariant;
    unsigned char cupRank[3][8];
    char pad1D2[0x1DA - 0x1D2];
    signed char streak;
} PlayerData;

#endif /* GAME_TYPES_PLAYERDATA_H */
