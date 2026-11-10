#ifndef GAME_TYPES_MARKERCHAIN_H
#define GAME_TYPES_MARKERCHAIN_H

struct HSD_JObj;

/* Merged from 1 per-TU views by tools/struct_merge.py: members are
 * the ones some TU accesses; the size is the largest any view declared. */
typedef struct MarkerChain MarkerChain;
struct MarkerChain {
    /* 0x000 */ void *vtable;
    /* 0x004 */ void *model;
    /* 0x008 */ struct HSD_JObj *chain;
};

#endif /* GAME_TYPES_MARKERCHAIN_H */
