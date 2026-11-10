#ifndef GAME_TYPES_ITEMPICK_H
#define GAME_TYPES_ITEMPICK_H

struct ItemKart;

/* Merged from 3 per-TU views by tools/struct_merge.py: members are
 * the ones some TU accesses; the size is the largest any view declared. */
typedef struct ItemPick ItemPick;
struct ItemPick {
    /* 0x000 */ struct ItemKart *kart;
    /* 0x004 */ unsigned char pad_004[0x4];
    /* 0x008 */ int field8;
};

#endif /* GAME_TYPES_ITEMPICK_H */
