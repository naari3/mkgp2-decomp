#ifndef GAME_TYPES_LITER_H
#define GAME_TYPES_LITER_H

struct LNode;

/* Merged from 2 per-TU views by tools/struct_merge.py: members are
 * the ones some TU accesses; the size is the largest any view declared. */
typedef struct LIter LIter;
struct LIter {
    /* 0x000 */ struct LNode *n;
};

#endif /* GAME_TYPES_LITER_H */
