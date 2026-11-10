#ifndef GAME_TYPES_COINCOUNTERS_H
#define GAME_TYPES_COINCOUNTERS_H

/* Merged from 2 per-TU views by tools/struct_merge.py: members are
 * the ones some TU accesses; the size is the largest any view declared. */
typedef struct CoinCounters CoinCounters;
struct CoinCounters {
    /* 0x000 */ unsigned int coins[4];
    /* 0x010 */ unsigned int totalCoins;
    /* 0x014 */ unsigned int paidCredits;
    /* 0x018 */ unsigned int serviceCredits;
    /* 0x01C */ unsigned int allCredits;
    /* 0x020 */ unsigned char pad_020[0x20];
};

#endif /* GAME_TYPES_COINCOUNTERS_H */
