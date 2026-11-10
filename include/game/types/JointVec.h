#ifndef GAME_TYPES_JOINTVEC_H
#define GAME_TYPES_JOINTVEC_H

/* Merged from 2 per-TU views by tools/struct_merge.py: members are
 * the ones some TU accesses; the size is the largest any view declared. */
typedef struct JointVec JointVec;
struct JointVec {
    /* 0x000 */ float x;
    /* 0x004 */ float y;
    /* 0x008 */ float z;
};

#endif /* GAME_TYPES_JOINTVEC_H */
