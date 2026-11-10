#ifndef GAME_TYPES_BOOSTKART_H
#define GAME_TYPES_BOOSTKART_H

struct BoostFlags;

/* Merged from 2 per-TU views by tools/struct_merge.py: members are
 * the ones some TU accesses; the size is the largest any view declared. */
typedef struct BoostKart BoostKart;
struct BoostKart {
    /* 0x000 */ unsigned char pad_000[0x8];
    /* 0x008 */ int level;
    /* 0x00C */ float timer;
    /* 0x010 */ unsigned char pad_010[0x18];
    /* 0x028 */ int levelCount;
    /* 0x02C */ unsigned char pad_02C[0x1AC];
    /* 0x1D8 */ float accelScale;
    /* 0x1DC */ unsigned char pad_1DC[0x128];
    /* 0x304 */ struct BoostFlags *flags;
};

#endif /* GAME_TYPES_BOOSTKART_H */
