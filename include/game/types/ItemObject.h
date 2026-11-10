#ifndef GAME_TYPES_ITEMOBJECT_H
#define GAME_TYPES_ITEMOBJECT_H

struct ItemBehavior;

/* Merged from 6 per-TU views by tools/struct_merge.py: members are
 * the ones some TU accesses; the size is the largest any view declared. */
typedef struct ItemObject ItemObject;
struct ItemObject {
    /* 0x000 */ signed char inUse;
    /* 0x001 */ unsigned char pad_001[0x3];
    /* 0x004 */ int owner;
    /* 0x008 */ int kind;
    /* 0x00C */ int released;
    /* 0x010 */ unsigned char pad_010[0x90];
    /* 0x0A0 */ float position[3];
    /* 0x0AC */ unsigned char pad_0AC[0x1C];
    /* 0x0C8 */ unsigned char homingMode;
    /* 0x0C9 */ unsigned char pad_0C9[0x23];
    /* 0x0EC */ unsigned char bytes[4];
    /* 0x0F0 */ unsigned char pad_0F0[0x78];
    /* 0x168 */ int field168;
    /* 0x16C */ unsigned char pad_16C[0x14];
    /* 0x180 */ int pair180[2];
    /* 0x188 */ unsigned char pad_188[0x54];
    /* 0x1DC */ signed char aliased;
    /* 0x1DD */ unsigned char pad_1DD[0x3];
    /* 0x1E0 */ int arg;
    /* 0x1E4 */ unsigned char pad_1E4[0x124];
    /* 0x308 */ struct ItemBehavior *behavior;
};

#endif /* GAME_TYPES_ITEMOBJECT_H */
