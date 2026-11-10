#ifndef GAME_TYPES_ITEMPARAMS_H
#define GAME_TYPES_ITEMPARAMS_H

/* Merged from 2 per-TU views by tools/struct_merge.py: members are
 * the ones some TU accesses; the size is the largest any view declared. */
typedef struct ItemParams ItemParams;
struct ItemParams {
    /* 0x000 */ const char *name;
    /* 0x004 */ float x4;
    /* 0x008 */ float x8;
};

#endif /* GAME_TYPES_ITEMPARAMS_H */
