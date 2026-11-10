#ifndef GAME_TYPES_ITEMBOXSET_H
#define GAME_TYPES_ITEMBOXSET_H

struct ItemBoxSlot;
struct ListNode;

/* Merged from 2 per-TU views by tools/struct_merge.py: members are
 * the ones some TU accesses; the size is the largest any view declared. */
typedef struct ItemBoxSet ItemBoxSet;
struct ItemBoxSet {
    /* 0x000 */ void *vtable;
    /* 0x004 */ void *sound;
    /* 0x008 */ void *modelA;
    /* 0x00C */ void *modelB;
    /* 0x010 */ void *archive;
    /* 0x014 */ struct ListNode *nodes;
    /* 0x018 */ int selected;
    /* 0x01C */ struct ItemBoxSlot *slots;
    /* 0x020 */ int count;
};

#endif /* GAME_TYPES_ITEMBOXSET_H */
