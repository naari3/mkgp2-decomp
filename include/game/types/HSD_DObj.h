#ifndef GAME_TYPES_HSD_DOBJ_H
#define GAME_TYPES_HSD_DOBJ_H

struct HSD_MObj;

/* Merged from 5 per-TU views by tools/struct_merge.py: members are
 * the ones some TU accesses; the size is the largest any view declared. */
typedef struct HSD_DObj HSD_DObj;
struct HSD_DObj {
    /* 0x000 */ void *parent;
    /* 0x004 */ struct HSD_DObj *next;
    /* 0x008 */ struct HSD_MObj *mobj;
};

#endif /* GAME_TYPES_HSD_DOBJ_H */
