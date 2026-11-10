#ifndef GAME_TYPES_CLASSFLOW_H
#define GAME_TYPES_CLASSFLOW_H

/* Merged from 1 per-TU views by tools/struct_merge.py: members are
 * the ones some TU accesses; the size is the largest any view declared. */
typedef struct ClassFlow ClassFlow;
struct ClassFlow {
    /* 0x000 */ void *vt;
    /* 0x004 */ unsigned char pad_004[0x28];
    /* 0x02C */ void *sprites[4];
};

#endif /* GAME_TYPES_CLASSFLOW_H */
