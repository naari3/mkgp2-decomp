#ifndef GAME_TYPES_SPRITEHANDLE_H
#define GAME_TYPES_SPRITEHANDLE_H

/* Merged from 2 per-TU views by tools/struct_merge.py: members are
 * the ones some TU accesses; the size is the largest any view declared. */
typedef struct SpriteHandle SpriteHandle;
struct SpriteHandle {
    /* 0x000 */ signed char active;
    /* 0x001 */ unsigned char pad_001[0x3];
    /* 0x004 */ int type;
    /* 0x008 */ int next;
    /* 0x00C */ unsigned char keep;
    /* 0x00D */ unsigned char released;
    /* 0x00E */ unsigned char pad_00E[0x2];
    /* 0x010 */ int resId;
    /* 0x014 */ void *texObj;
    /* 0x018 */ void *tlut;
    /* 0x01C */ unsigned char texFmt;
    /* 0x01D */ unsigned char pad_01D[0x3];
    /* 0x020 */ int baseResId;
    /* 0x024 */ signed char tevMode;
    /* 0x025 */ char posMode;
    /* 0x026 */ unsigned char posMode_026;  /* also: posMode */
    /* 0x027 */ unsigned char pad_027[0x1];
    /* 0x028 */ float sizeX;
    /* 0x02C */ float sizeY;
    /* 0x030 */ char z[4];
    /* 0x034 */ float rot;
    /* 0x038 */ float texW;
    /* 0x03C */ float texH;
    /* 0x040 */ float posX;
    /* 0x044 */ float posY;
    /* 0x048 */ unsigned char clipFlags;  /* also: uvFlip */
    /* 0x049 */ unsigned char hasUV;
    /* 0x04A */ unsigned char pad_04A[0x2];
    /* 0x04C */ float uv[6];
    /* 0x064 */ unsigned int color[4];
    /* 0x074 */ unsigned char flip;
    /* 0x075 */ unsigned char pad_075[0x3];
    /* 0x078 */ int blendType;  /* also: uvMode */
    /* 0x07C */ int blendSrc;  /* also: uvA */
    /* 0x080 */ int blendDst;  /* also: uvB */
    /* 0x084 */ int blendOp;  /* also: uvC */
    /* 0x088 */ float corner[4][2];
    /* 0x0A8 */ float texUV[2][2];  /* also: uv */
    /* 0x0B8 */ unsigned char hasTex2;
    /* 0x0B9 */ unsigned char pad_0B9[0x3];
    /* 0x0BC */ int resId2;
    /* 0x0C0 */ void *texObj2;
    /* 0x0C4 */ void *tlut2;
    /* 0x0C8 */ float uv2[4];
    /* 0x0D8 */ unsigned char hasCallback;  /* also: activeFlag */
    /* 0x0D9 */ unsigned char callbackOn;  /* also: visible */
    /* 0x0DA */ signed char dirty;
    /* 0x0DB */ unsigned char pad_0DB[0x1];
    /* 0x0DC */ int callback;  /* also: fDC */
    /* 0x0E0 */ int callbackArg;
};

#endif /* GAME_TYPES_SPRITEHANDLE_H */
