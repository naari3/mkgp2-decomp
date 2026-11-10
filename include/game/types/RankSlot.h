#ifndef GAME_TYPES_RANKSLOT_H
#define GAME_TYPES_RANKSLOT_H

/* Merged from 3 per-TU views by tools/struct_merge.py: members are
 * the ones some TU accesses; the size is the largest any view declared. */
typedef struct RankSlot RankSlot;
struct RankSlot {
    /* 0x000 */ unsigned char active;
    /* 0x001 */ unsigned char pad_001[0x1];
    /* 0x002 */ unsigned short count;
    /* 0x004 */ unsigned char pad_004[0xC];
    /* 0x010 */ int target;
    /* 0x014 */ int source;
    /* 0x018 */ unsigned char pad_018[0x4];
    /* 0x01C */ int timer;
    /* 0x020 */ unsigned char pad_020[0x8];
    /* 0x028 */ unsigned char enabled;
    /* 0x029 */ unsigned char pad_029[0x3];
};

#endif /* GAME_TYPES_RANKSLOT_H */
