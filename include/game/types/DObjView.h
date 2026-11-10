#ifndef GAME_TYPES_DOBJVIEW_H
#define GAME_TYPES_DOBJVIEW_H

struct MObjView;

/* Merged from 2 per-TU views by tools/struct_merge.py: members are
 * the ones some TU accesses; the size is the largest any view declared. */
typedef struct DObjView DObjView;
struct DObjView {
    /* 0x000 */ void *parent;
    /* 0x004 */ struct DObjView *next;
    /* 0x008 */ struct MObjView *mobj;
};

#endif /* GAME_TYPES_DOBJVIEW_H */
