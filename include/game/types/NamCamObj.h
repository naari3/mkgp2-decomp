#ifndef GAME_TYPES_NAMCAMOBJ_H
#define GAME_TYPES_NAMCAMOBJ_H

/* Merged from 1 per-TU views by tools/struct_merge.py: members are
 * the ones some TU accesses; the size is the largest any view declared. */
typedef struct NamCamObj NamCamObj;
struct NamCamObj {
    /* 0x000 */ unsigned char active;
    /* 0x001 */ unsigned char loaded;
    /* 0x002 */ unsigned char pad_002[0x2];
    /* 0x004 */ void *buf;
};

#endif /* GAME_TYPES_NAMCAMOBJ_H */
