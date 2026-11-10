#ifndef GAME_TYPES_RESOURCESLOT_H
#define GAME_TYPES_RESOURCESLOT_H

struct GXTexObj;
struct GXTlutObj;
struct TEXPalette;

/* Merged from 2 per-TU views by tools/struct_merge.py: members are
 * the ones some TU accesses; the size is the largest any view declared. */
typedef struct ResourceSlot ResourceSlot;
struct ResourceSlot {
    /* 0x000 */ int id;
    /* 0x004 */ int group;
    /* 0x008 */ struct TEXPalette *palette;
    /* 0x00C */ int count;
    /* 0x010 */ struct GXTexObj *texObjs;
    /* 0x014 */ struct GXTlutObj *tlutObjs;
    /* 0x018 */ unsigned char *tlutNames;
};

#endif /* GAME_TYPES_RESOURCESLOT_H */
