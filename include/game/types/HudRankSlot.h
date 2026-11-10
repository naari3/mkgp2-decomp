#ifndef GAME_TYPES_HUDRANKSLOT_H
#define GAME_TYPES_HUDRANKSLOT_H

/* Merged from 2 per-TU views by tools/struct_merge.py: members are
 * the ones some TU accesses; the size is the largest any view declared. */
typedef struct HudRankSlot HudRankSlot;
struct HudRankSlot {
    /* 0x000 */ unsigned char active;
    /* 0x001 */ unsigned char pad_001[0x1];
    /* 0x002 */ unsigned short name[7];
    /* 0x010 */ int chr;
    /* 0x014 */ int kart;
    /* 0x018 */ unsigned char pad_018[0x4];
    /* 0x01C */ int icon;
    /* 0x020 */ unsigned char pad_020[0x8];
    /* 0x028 */ unsigned char f28;
    /* 0x029 */ unsigned char pad_029[0x3];
};

#endif /* GAME_TYPES_HUDRANKSLOT_H */
