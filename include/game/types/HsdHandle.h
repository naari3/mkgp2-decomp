#ifndef GAME_TYPES_HSDHANDLE_H
#define GAME_TYPES_HSDHANDLE_H

/* Merged from 2 per-TU views by tools/struct_merge.py: members are
 * the ones some TU accesses; the size is the largest any view declared. */
typedef struct HsdHandle HsdHandle;
struct HsdHandle {
    /* 0x000 */ unsigned char pad_000[0x8];
    /* 0x008 */ int x8;
    /* 0x00C */ void *xc;
};

#endif /* GAME_TYPES_HSDHANDLE_H */
