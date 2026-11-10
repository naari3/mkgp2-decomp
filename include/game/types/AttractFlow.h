#ifndef GAME_TYPES_ATTRACTFLOW_H
#define GAME_TYPES_ATTRACTFLOW_H

/* Merged from 1 per-TU views by tools/struct_merge.py: members are
 * the ones some TU accesses; the size is the largest any view declared. */
typedef struct AttractFlow AttractFlow;
struct AttractFlow {
    /* 0x000 */ void *vt;
    /* 0x004 */ unsigned char pad_004[0x1];
    /* 0x005 */ signed char kind;
    /* 0x006 */ unsigned char pad_006[0x1A];
    /* 0x020 */ void *sprites[5];
};

#endif /* GAME_TYPES_ATTRACTFLOW_H */
