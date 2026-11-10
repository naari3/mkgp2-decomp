#ifndef GAME_TYPES_BITPACKENTRY_H
#define GAME_TYPES_BITPACKENTRY_H

/* Merged from 2 per-TU views by tools/struct_merge.py: members are
 * the ones some TU accesses; the size is the largest any view declared. */
typedef struct BitpackEntry BitpackEntry;
struct BitpackEntry {
    /* 0x000 */ const char *name;  /* also: tag */
    /* 0x004 */ int width;
    /* 0x008 */ int slots;  /* also: count */
    /* 0x00C */ int offset;
};

#endif /* GAME_TYPES_BITPACKENTRY_H */
