#ifndef GAME_TYPES_ROUNDINFO_H
#define GAME_TYPES_ROUNDINFO_H

/* Merged from 1 per-TU views by tools/struct_merge.py: members are
 * the ones some TU accesses; the size is the largest any view declared. */
typedef struct RoundInfo RoundInfo;
struct RoundInfo {
    /* 0x000 */ unsigned char pad_000[0x18];
    /* 0x018 */ int lapA;
    /* 0x01C */ int lapB;
};

#endif /* GAME_TYPES_ROUNDINFO_H */
