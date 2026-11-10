#ifndef GAME_TYPES_GROWSET_H
#define GAME_TYPES_GROWSET_H

struct GrowEntry;

/* Merged from 3 per-TU views by tools/struct_merge.py: members are
 * the ones some TU accesses; the size is the largest any view declared. */
typedef struct GrowSet GrowSet;
struct GrowSet {
    /* 0x000 */ void *vtable;
    /* 0x004 */ void *model;
    /* 0x008 */ struct GrowEntry *entries;
    /* 0x00C */ int count;
};

#endif /* GAME_TYPES_GROWSET_H */
