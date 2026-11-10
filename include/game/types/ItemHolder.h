#ifndef GAME_TYPES_ITEMHOLDER_H
#define GAME_TYPES_ITEMHOLDER_H

/* Merged from 2 per-TU views by tools/struct_merge.py: members are
 * the ones some TU accesses; the size is the largest any view declared. */
typedef struct ItemHolder ItemHolder;
struct ItemHolder {
    /* 0x000 */ void *vt;
    /* 0x004 */ int kart;
    /* 0x008 */ unsigned char pad_008[0xC];
    /* 0x014 */ int slot;
    /* 0x018 */ int targetSlot;
    /* 0x01C */ unsigned int itemType;  /* also: item */
    /* 0x020 */ unsigned int hasItem;  /* also: state */
    /* 0x024 */ int cooldown;
    /* 0x028 */ unsigned int effectCategory;
};

#endif /* GAME_TYPES_ITEMHOLDER_H */
