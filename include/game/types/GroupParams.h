#ifndef GAME_TYPES_GROUPPARAMS_H
#define GAME_TYPES_GROUPPARAMS_H

struct ItemParams;

/* Merged from 2 per-TU views by tools/struct_merge.py: members are
 * the ones some TU accesses; the size is the largest any view declared. */
typedef struct GroupParams GroupParams;
struct GroupParams {
    /* 0x000 */ const char *model;
    /* 0x004 */ struct ItemParams *items;
    /* 0x008 */ int count;
};

#endif /* GAME_TYPES_GROUPPARAMS_H */
