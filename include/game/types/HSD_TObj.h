#ifndef GAME_TYPES_HSD_TOBJ_H
#define GAME_TYPES_HSD_TOBJ_H

/* Merged from 2 per-TU views by tools/struct_merge.py: members are
 * the ones some TU accesses; the size is the largest any view declared. */
typedef struct HSD_TObj HSD_TObj;
struct HSD_TObj {
    /* 0x000 */ unsigned char pad_000[0x40];
    /* 0x040 */ int wrap_s;
    /* 0x044 */ int wrap_t;
    /* 0x048 */ unsigned char repeat_s;
    /* 0x049 */ unsigned char repeat_t;
    /* 0x04A */ unsigned char pad_04A[0x2A];
    /* 0x074 */ float mtx[3][4];
};

#endif /* GAME_TYPES_HSD_TOBJ_H */
