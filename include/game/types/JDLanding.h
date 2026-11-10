#ifndef GAME_TYPES_JDLANDING_H
#define GAME_TYPES_JDLANDING_H

/* Merged from 2 per-TU views by tools/struct_merge.py: members are
 * the ones some TU accesses; the size is the largest any view declared. */
typedef struct JDLanding JDLanding;
struct JDLanding {
    /* 0x000 */ unsigned char active;
    /* 0x001 */ unsigned char slowed;
    /* 0x002 */ unsigned char pad_002[0x2];
    /* 0x004 */ int x4;
    /* 0x008 */ int x8;
    /* 0x00C */ float scale;
};

#endif /* GAME_TYPES_JDLANDING_H */
