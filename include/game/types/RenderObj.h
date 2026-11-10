#ifndef GAME_TYPES_RENDEROBJ_H
#define GAME_TYPES_RENDEROBJ_H

struct ItemEffectBus;

/* Merged from 6 per-TU views by tools/struct_merge.py: members are
 * the ones some TU accesses; the size is the largest any view declared. */
typedef struct RenderObj RenderObj;
struct RenderObj {
    /* 0x000 */ unsigned char pad_000[0x1F4];
    /* 0x1F4 */ int eventType;
    /* 0x1F8 */ unsigned char pad_1F8[0x40];
    /* 0x238 */ int x238;
    /* 0x23C */ int airState;
    /* 0x240 */ unsigned char pad_240[0x8C];
    /* 0x2CC */ int section;
    /* 0x2D0 */ unsigned char x2D0;
    /* 0x2D1 */ unsigned char pad_2D1[0x33];
    /* 0x304 */ struct ItemEffectBus *status;
};

#endif /* GAME_TYPES_RENDEROBJ_H */
