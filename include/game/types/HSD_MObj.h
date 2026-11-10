#ifndef GAME_TYPES_HSD_MOBJ_H
#define GAME_TYPES_HSD_MOBJ_H

/* Merged from 2 per-TU views by tools/struct_merge.py: members are
 * the ones some TU accesses; the size is the largest any view declared. */
typedef struct HSD_MObj HSD_MObj;
struct HSD_MObj {
    /* 0x000 */ unsigned char pad_000[0x10];
    /* 0x010 */ void *buf;
    /* 0x014 */ unsigned char pad_014[0xF];
    /* 0x023 */ unsigned char x23;
};

#endif /* GAME_TYPES_HSD_MOBJ_H */
