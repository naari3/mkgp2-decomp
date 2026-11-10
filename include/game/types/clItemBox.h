#ifndef GAME_TYPES_CLITEMBOX_H
#define GAME_TYPES_CLITEMBOX_H

/* Merged from 1 per-TU views by tools/struct_merge.py: members are
 * the ones some TU accesses; the size is the largest any view declared. */
typedef struct clItemBox clItemBox;
struct clItemBox {
    /* 0x000 */ unsigned char pad_000[0x24];
    /* 0x024 */ int state;
    /* 0x028 */ unsigned char pad_028[0x4];
    /* 0x02C */ float timer;
};

#endif /* GAME_TYPES_CLITEMBOX_H */
