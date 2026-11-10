#ifndef GAME_TYPES_PLAYERDATA_H
#define GAME_TYPES_PLAYERDATA_H

/* Merged from 10 per-TU views by tools/struct_merge.py: members are
 * the ones some TU accesses; the size is the largest any view declared. */
typedef struct PlayerData PlayerData;
struct PlayerData {
    /* 0x000 */ unsigned int word000;
    /* 0x004 */ unsigned int word004;
    /* 0x008 */ unsigned int word008;
    /* 0x00C */ unsigned char byte00C;
    /* 0x00D */ unsigned char byte00D;
    /* 0x00E */ unsigned short wins;
    /* 0x010 */ unsigned short losses;
    /* 0x012 */ unsigned char pad_012[0x2];
    /* 0x014 */ unsigned int word014;
    /* 0x018 */ unsigned char byte018;
    /* 0x019 */ unsigned char byte019;
    /* 0x01A */ unsigned char byte01A;
    /* 0x01B */ unsigned char pad_01B[0x1];
    /* 0x01C */ unsigned int w01C;
    /* 0x020 */ unsigned int w020;
    /* 0x024 */ unsigned int w024;
    /* 0x028 */ unsigned int w028;
    /* 0x02C */ unsigned int w02C;
    /* 0x030 */ unsigned int w030;
    /* 0x034 */ unsigned int w034;
    /* 0x038 */ unsigned int w038;
    /* 0x03C */ unsigned int w03C;
    /* 0x040 */ unsigned int w040;
    /* 0x044 */ unsigned int w044;
    /* 0x048 */ unsigned char cleared[32];
    /* 0x068 */ unsigned int w068;
    /* 0x06C */ unsigned int w06C;
    /* 0x070 */ unsigned int w070;
    /* 0x074 */ unsigned int w074;
    /* 0x078 */ unsigned int w078;
    /* 0x07C */ unsigned int w07C;
    /* 0x080 */ unsigned int w080;
    /* 0x084 */ unsigned int w084;
    /* 0x088 */ unsigned int w088;
    /* 0x08C */ unsigned int w08C;
    /* 0x090 */ unsigned int w090;
    /* 0x094 */ unsigned int w094;
    /* 0x098 */ unsigned int w098;
    /* 0x09C */ unsigned int w09C;
    /* 0x0A0 */ unsigned int w0A0;
    /* 0x0A4 */ unsigned int w0A4;
    /* 0x0A8 */ unsigned char unlockFlags[0x79];
    /* 0x121 */ unsigned char unk_121[0x69];
    /* 0x18A */ unsigned char pad_18A[0x2];
    /* 0x18C */ int selected[3];
    /* 0x198 */ unsigned char b198;
    /* 0x199 */ unsigned char b199;
    /* 0x19A */ unsigned char b19A;
    /* 0x19B */ unsigned char b19B;
    /* 0x19C */ unsigned char b19C;
    /* 0x19D */ unsigned char b19D;
    /* 0x19E */ unsigned char b19E;
    /* 0x19F */ unsigned char b19F;
    /* 0x1A0 */ unsigned char b1A0;
    /* 0x1A1 */ unsigned char pad_1A1[0x3];
    /* 0x1A4 */ unsigned int word1A4;
    /* 0x1A8 */ unsigned char byte1A8;
    /* 0x1A9 */ unsigned char pad_1A9[0x3];
    /* 0x1AC */ int raceCount;
    /* 0x1B0 */ unsigned char byte1B0;
    /* 0x1B1 */ unsigned char byte1B1;
    /* 0x1B2 */ unsigned char pad_1B2[0x2];
    /* 0x1B4 */ int coinMilage;
    /* 0x1B8 */ unsigned char variant;
    /* 0x1B9 */ unsigned char kartVariant;
    /* 0x1BA */ unsigned char cupRank[3][8];
    /* 0x1D2 */ unsigned char pad_1D2[0x2];
    /* 0x1D4 */ unsigned int word1D4;
    /* 0x1D8 */ unsigned char byte1D8;
    /* 0x1D9 */ signed char cardState;
    /* 0x1DA */ signed char streak;
    /* 0x1DB */ unsigned char pad_1DB[0x1];
};

#endif /* GAME_TYPES_PLAYERDATA_H */
