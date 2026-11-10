#ifndef GAME_TYPES_DRAWNODE_H
#define GAME_TYPES_DRAWNODE_H

/* Merged from 2 per-TU views by tools/struct_merge.py: members are
 * the ones some TU accesses; the size is the largest any view declared. */
typedef struct DrawNode DrawNode;
struct DrawNode {
    /* 0x000 */ struct DrawNode *a;
    /* 0x004 */ struct DrawNode *next;
    /* 0x008 */ unsigned short flags;
    /* 0x00A */ unsigned char pad_00A[0x2];
    /* 0x00C */ struct DrawNode *prev;
    /* 0x010 */ struct DrawNode *next_010;
};

#endif /* GAME_TYPES_DRAWNODE_H */
