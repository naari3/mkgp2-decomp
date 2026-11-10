#ifndef GAME_TYPES_SHADOWBILLBOARDSRC_H
#define GAME_TYPES_SHADOWBILLBOARDSRC_H

/* Merged from 2 per-TU views by tools/struct_merge.py: members are
 * the ones some TU accesses; the size is the largest any view declared. */
typedef struct ShadowBillboardSrc ShadowBillboardSrc;
struct ShadowBillboardSrc {
    /* 0x000 */ unsigned char pad_000[0x58];
    /* 0x058 */ float mtx58[16];
    /* 0x098 */ unsigned char pad_098[0x40];
    /* 0x0D8 */ float mtx[16];
    /* 0x118 */ unsigned char pad_118[0xC0];
    /* 0x1D8 */ float lerpT;
};

#endif /* GAME_TYPES_SHADOWBILLBOARDSRC_H */
