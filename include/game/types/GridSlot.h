#ifndef GAME_TYPES_GRIDSLOT_H
#define GAME_TYPES_GRIDSLOT_H

/* Merged from 1 per-TU views by tools/struct_merge.py: members are
 * the ones some TU accesses; the size is the largest any view declared. */
typedef struct GridSlot GridSlot;
struct GridSlot {
    /* 0x000 */ int id;
    /* 0x004 */ unsigned char pad_004[0xC];
};

#endif /* GAME_TYPES_GRIDSLOT_H */
