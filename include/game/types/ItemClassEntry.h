#ifndef GAME_TYPES_ITEMCLASSENTRY_H
#define GAME_TYPES_ITEMCLASSENTRY_H

/* Merged from 5 per-TU views by tools/struct_merge.py: members are
 * the ones some TU accesses; the size is the largest any view declared. */
typedef struct ItemClassEntry ItemClassEntry;
struct ItemClassEntry {
    /* 0x000 */ int def;
    /* 0x004 */ unsigned char flag0;
    /* 0x005 */ unsigned char flag1;
    /* 0x006 */ unsigned char pad_006[0x2];
    /* 0x008 */ float radius;
    /* 0x00C */ signed char hasJoint;
    /* 0x00D */ unsigned char pad_00D[0x3];
    /* 0x010 */ const char *joint;
};

#endif /* GAME_TYPES_ITEMCLASSENTRY_H */
