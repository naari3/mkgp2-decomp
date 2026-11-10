#ifndef GAME_TYPES_JOINTENTRY_H
#define GAME_TYPES_JOINTENTRY_H

/* Merged from 2 per-TU views by tools/struct_merge.py: members are
 * the ones some TU accesses; the size is the largest any view declared. */
typedef struct JointEntry JointEntry;
struct JointEntry {
    /* 0x000 */ char name[0x10];
    /* 0x010 */ int a;
    /* 0x014 */ int b;
};

#endif /* GAME_TYPES_JOINTENTRY_H */
