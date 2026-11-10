#ifndef GAME_TYPES_ENTRYFLOW_H
#define GAME_TYPES_ENTRYFLOW_H

/* Merged from 1 per-TU views by tools/struct_merge.py: members are
 * the ones some TU accesses; the size is the largest any view declared. */
typedef struct EntryFlow EntryFlow;
struct EntryFlow {
    /* 0x000 */ void *vt;
    /* 0x004 */ unsigned char pad_004[0x4];
    /* 0x008 */ int kind;
    /* 0x00C */ unsigned char pad_00C[0x8];
    /* 0x014 */ void *sprite14;
    /* 0x018 */ void *sprite18;
    /* 0x01C */ void *anim1C;
};

#endif /* GAME_TYPES_ENTRYFLOW_H */
