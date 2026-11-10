#ifndef GAME_TYPES_JDCOINS_H
#define GAME_TYPES_JDCOINS_H

/* Merged from 2 per-TU views by tools/struct_merge.py: members are
 * the ones some TU accesses; the size is the largest any view declared. */
typedef struct JDCoins JDCoins;
struct JDCoins {
    /* 0x000 */ unsigned char pad_000[0x8];
    /* 0x008 */ int base;
    /* 0x00C */ int earned;
};

#endif /* GAME_TYPES_JDCOINS_H */
