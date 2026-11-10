#ifndef GAME_ENEMYFACE_TIRE_PRIVATE_H
#define GAME_ENEMYFACE_TIRE_PRIVATE_H

// TireSprite ABI and SDK declarations mirror EnemyFace_private.h.
// Keep pool declarations in EnemyFace.cpp so string sizes exclude alignment.
typedef float Mtx[3][4];

struct TPLClut;
struct TPLDescriptor {
    void *image;
    TPLClut *clut;
};
struct TPLPalette {
    unsigned int version;
    unsigned int count;
    TPLDescriptor *descriptors;
};

union WGPipe {
    float f32;
    unsigned int u32;
};
#define GXFIFO (*(volatile WGPipe *)0xCC008000)

#include "game/types/TireSprite.h"

extern "C" {
extern void *lbl_806D05F0[2];
extern TPLPalette *lbl_806D05F8[2];
extern void *lbl_806D0600[2];
extern const int lbl_806DB590[2];

void DebugPrintf(const char *fmt, ...);
const char *ResourceTable_GetFilePathPtr(int id);
void TEXLoadPalette_Retry(TPLPalette **out, const char *path);
void TEXReleasePalette(TPLPalette **pal);
TPLDescriptor *TEXGetPaletteEntry(TPLPalette *pal, unsigned int idx);
void TEXBindPaletteEntry_CI(TPLPalette *pal, void *texObjs, void *tluts, int a, unsigned int idx);
void TEXBindPaletteEntry_RGB(TPLPalette *pal, void *texObjs, unsigned int idx);
void *FUN_8003b120(unsigned int size);
void MemoryManager_Free(void *p);
void GXSetCullMode(int mode);
void GXClearVtxDesc(void);
void GXSetVtxDesc(int attr, int type);
void GXSetVtxAttrFmt(int fmt, int attr, int cnt, int type, int frac);
void GXSetNumChans(int n);
void GXSetChanCtrl(int chan, int enable, int amb, int mat, int lights, int diff, int attn);
void GXSetNumTevStages(int n);
void GXSetBlendMode(int type, int src, int dst, int op);
void GXSetTevOrder(int stage, int coord, int map, int color);
void GXSetTevOp(int stage, int mode);
void GXSetNumTexGens(int n);
void GXSetTexCoordGen2(int dst, int func, int src, int mtx, int norm, int pt);
void GXSetTevColorIn(int stage, int a, int b, int c, int d);
void GXSetTevColorOp(int stage, int op, int bias, int scale, int clamp, int reg);
void GXSetTevAlphaIn(int stage, int a, int b, int c, int d);
void GXSetTevAlphaOp(int stage, int op, int bias, int scale, int clamp, int reg);
void GXLoadTexObj(void *obj, int map);
void GXLoadTlut(void *obj, int name);
void GXSetCurrentMtx(int id);
void GXLoadPosMtxImm(Mtx m, int id);
void GXBegin(int prim, int fmt, int n);
void HSD_StateInvalidate(int state);
void HSD_CObjGetViewingMtx(void *cobj, Mtx m);
void *GetCourseScene3D(void);
}

#endif
