#ifndef GAME_TYPES_LISTHEAD_H
#define GAME_TYPES_LISTHEAD_H

struct LNode;

/* Merged from 1 per-TU views by tools/struct_merge.py: members are
 * the ones some TU accesses; the size is the largest any view declared. */
typedef struct ListHead ListHead;
struct ListHead {
    /* 0x000 */ int count;
    /* 0x004 */ struct LNode *f4;
    /* 0x008 */ struct LNode *head;
};

#endif /* GAME_TYPES_LISTHEAD_H */
