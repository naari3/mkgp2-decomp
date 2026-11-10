#ifndef GAME_TYPES_SHADOWBILLBOARD_H
#define GAME_TYPES_SHADOWBILLBOARD_H

#include "game/types/Vec3f.h"

struct ShadowBillboardSrc;

/* Merged from 3 per-TU views by tools/struct_merge.py: members are
 * the ones some TU accesses; the size is the largest any view declared. */
typedef struct ShadowBillboard ShadowBillboard;
struct ShadowBillboard {
    /* 0x000 */ unsigned char active;
    /* 0x001 */ unsigned char pad_001[0x3];
    /* 0x004 */ int mode;
    /* 0x008 */ unsigned char pad_008[0x4];
    /* 0x00C */ int level;
    /* 0x010 */ unsigned char pad_010[0x4];
    /* 0x014 */ struct ShadowBillboardSrc *src;
    /* 0x018 */ unsigned char flag18;
    /* 0x019 */ unsigned char flag19;
    /* 0x01A */ unsigned char pad_01A[0x2];
    /* 0x01C */ float mtx1C[16];
    /* 0x05C */ float *mtx;
    /* 0x060 */ float fade60;
    /* 0x064 */ float fade64;
    /* 0x068 */ int fadeMode;
    /* 0x06C */ int field6C;
    /* 0x070 */ Vec3f vec70;
    /* 0x07C */ Vec3f camPos;
    /* 0x088 */ Vec3f axis;
    /* 0x094 */ float field94;
    /* 0x098 */ float targetSaturation;
    /* 0x09C */ float saturation;
    /* 0x0A0 */ float renderAlpha;
    /* 0x0A4 */ float heightA4;
    /* 0x0A8 */ float bumpA8;
    /* 0x0AC */ unsigned char spinFlash;
    /* 0x0AD */ unsigned char pad_0AD[0x3];
    /* 0x0B0 */ float spinB0;
    /* 0x0B4 */ float spinB4;
    /* 0x0B8 */ unsigned char shake[20];
    /* 0x0CC */ int courseCam;
    /* 0x0D0 */ float fxD0;
};

#endif /* GAME_TYPES_SHADOWBILLBOARD_H */
