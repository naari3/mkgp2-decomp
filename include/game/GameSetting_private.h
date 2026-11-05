#ifndef GAME_GAMESETTING_PRIVATE_H
#define GAME_GAMESETTING_PRIVATE_H

/* Target-observed settings fields; the backup block is shared by all pages. */
struct GameSettings {
    unsigned char pad0[0x21];
    signed char cabinet;
    signed char mode;
    unsigned char serviceEnabled;
    unsigned char serviceValue;
    unsigned char vblank;
    unsigned char option26;
    unsigned char option27;
    unsigned char pad28;
    unsigned char linkOption;
    unsigned char pad2A[0x1A];
    unsigned char flag44;
    unsigned char flag45;
};
struct GamePcbSlot {
    unsigned char pad0[3];
    unsigned char flags;
};

#endif
