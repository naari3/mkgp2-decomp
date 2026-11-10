#ifndef GAME_TYPES_SPRCTX_H
#define GAME_TYPES_SPRCTX_H

/* Merged from 3 per-TU views by tools/struct_merge.py: members are
 * the ones some TU accesses; the size is the largest any view declared. */
typedef struct SprCtx SprCtx;
struct SprCtx {
    /* 0x000 */ float a;
    /* 0x004 */ float b;
    /* 0x008 */ float c;
    /* 0x00C */ float d;
    /* 0x010 */ float e;
    /* 0x014 */ float f;
    /* 0x018 */ unsigned char pad_018[0x4];
    /* 0x01C */ float r;
    /* 0x020 */ float g;
    /* 0x024 */ float b2;
    /* 0x028 */ float alpha;
};

#endif /* GAME_TYPES_SPRCTX_H */
