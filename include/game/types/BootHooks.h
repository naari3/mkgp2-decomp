#ifndef GAME_TYPES_BOOTHOOKS_H
#define GAME_TYPES_BOOTHOOKS_H

/* Merged from 1 per-TU views by tools/struct_merge.py: members are
 * the ones some TU accesses; the size is the largest any view declared. */
typedef struct BootHooks BootHooks;
struct BootHooks {
    /* 0x000 */ void *begin;
    /* 0x004 */ void *end;
};

#endif /* GAME_TYPES_BOOTHOOKS_H */
