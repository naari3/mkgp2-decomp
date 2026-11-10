#ifndef GAME_TYPES_OBJLIST_H
#define GAME_TYPES_OBJLIST_H

struct Entry;

/* Merged from 2 per-TU views by tools/struct_merge.py: members are
 * the ones some TU accesses; the size is the largest any view declared. */
typedef struct ObjList ObjList;
struct ObjList {
    /* 0x000 */ void *vt;
    /* 0x004 */ struct Entry *items;
    /* 0x008 */ int count;
    /* 0x00C */ void *child;
    /* 0x010 */ void *buf;
};

#endif /* GAME_TYPES_OBJLIST_H */
