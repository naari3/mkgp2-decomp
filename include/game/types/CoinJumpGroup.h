#ifndef GAME_TYPES_COINJUMPGROUP_H
#define GAME_TYPES_COINJUMPGROUP_H

struct CoinJumpEffect;

/* Merged from 2 per-TU views by tools/struct_merge.py: members are
 * the ones some TU accesses; the size is the largest any view declared. */
typedef struct CoinJumpGroup CoinJumpGroup;
struct CoinJumpGroup {
    /* 0x000 */ unsigned char pad_000[0x10];
    /* 0x010 */ struct CoinJumpEffect *children[5];
    /* 0x024 */ unsigned char pad_024[0x60];
    /* 0x084 */ float phase[5];
};

#endif /* GAME_TYPES_COINJUMPGROUP_H */
