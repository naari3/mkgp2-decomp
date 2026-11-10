#ifndef GAME_TYPES_NOKOKIND_H
#define GAME_TYPES_NOKOKIND_H

/* Merged from 2 per-TU views by tools/struct_merge.py: members are
 * the ones some TU accesses; the size is the largest any view declared. */
typedef struct NokoKind NokoKind;
struct NokoKind {
    /* 0x000 */ int state;  /* also: model */
    /* 0x004 */ int model;  /* also: anim */
    /* 0x008 */ int timer;  /* also: extra */
    /* 0x00C */ float speed;
    /* 0x010 */ float radius;  /* also: turn */
};

#endif /* GAME_TYPES_NOKOKIND_H */
