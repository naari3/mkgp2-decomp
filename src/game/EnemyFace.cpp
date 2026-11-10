#include "game/EnemyFace_tire_private.h"

extern const unsigned int EnemyFace_rodata_803DA278[258] = {0x3F800000, 0x3F333333, 0x3F666666, 0x00000000, 0x00000000, 0x43FA0000, 0x42855556, 0x447A0000, 0x42855556, 0x44FA0000, 0x42855556, 0x453B8000, 0x42855556, 0x457A0000, 0x42855556, 0x459C4000, 0x42855556, 0x00000000, 0x00000000, 0x43FA0000, 0x42855556, 0x447A0000, 0x42855556, 0x44FA0000, 0x42855556, 0x453B8000, 0x42855556, 0x457A0000, 0x42855556, 0x459C4000, 0x42855556, 0x00000000, 0x00000000, 0x43FA0000, 0x42855556, 0x447A0000, 0x42855556, 0x44FA0000, 0x42855556, 0x453B8000, 0x42855556, 0x457A0000, 0x42855556, 0x459C4000, 0x42855556, 0x00000000, 0x00000000, 0x43FA0000, 0x42855556, 0x447A0000, 0x42855556, 0x44FA0000, 0x42855556, 0x453B8000, 0x42855556, 0x457A0000, 0x42855556, 0x459C4000, 0x42855556, 0x00000000, 0x00000000, 0x43FA0000, 0x42855556, 0x447A0000, 0x42855556, 0x44FA0000, 0x42855556, 0x453B8000, 0x42855556, 0x457A0000, 0x42855556, 0x459C4000, 0x42855556, 0x00000000, 0x00000000, 0x43FA0000, 0x42855556, 0x447A0000, 0x42855556, 0x44FA0000, 0x42855556, 0x453B8000, 0x42855556, 0x457A0000, 0x42855556, 0x459C4000, 0x42855556, 0x00000000, 0x00000000, 0x43FA0000, 0x42855556, 0x447A0000, 0x42855556, 0x44FA0000, 0x42855556, 0x453B8000, 0x42855556, 0x457A0000, 0x42855556, 0x459C4000, 0x42855556, 0x00000000, 0x00000000, 0x43FA0000, 0x42855556, 0x447A0000, 0x42855556, 0x44FA0000, 0x42855556, 0x453B8000, 0x42855556, 0x457A0000, 0x42855556, 0x459C4000, 0x42855556, 0x00000000, 0x00000000, 0x43FA0000, 0x42855556, 0x447A0000, 0x42855556, 0x44FA0000, 0x42855556, 0x453B8000, 0x42855556, 0x457A0000, 0x42855556, 0x459C4000, 0x42855556, 0x00000000, 0x00000000, 0x43FA0000, 0x42855556, 0x447A0000, 0x42855556, 0x44FA0000, 0x42855556, 0x453B8000, 0x42855556, 0x457A0000, 0x42855556, 0x459C4000, 0x42855556, 0x00000000, 0x00000000, 0x43FA0000, 0x42855556, 0x447A0000, 0x42855556, 0x44FA0000, 0x42855556, 0x453B8000, 0x42855556, 0x457A0000, 0x42855556, 0x459C4000, 0x42855556, 0x00000000, 0x00000000, 0x43FA0000, 0x42855556, 0x447A0000, 0x42855556, 0x44FA0000, 0x42855556, 0x453B8000, 0x42855556, 0x457A0000, 0x42855556, 0x459C4000, 0x42855556, 0x00000000, 0x00000000, 0x43FA0000, 0x42A6AAAB, 0x447A0000, 0x42A6AAAB, 0x44FA0000, 0x42A6AAAB, 0x453B8000, 0x42A6AAAB, 0x457A0000, 0x42A6AAAB, 0x459C4000, 0x42A6AAAB, 0x00000000, 0x00000000, 0x43FA0000, 0x42A6AAAB, 0x447A0000, 0x42A6AAAB, 0x44FA0000, 0x42A6AAAB, 0x453B8000, 0x42A6AAAB, 0x457A0000, 0x42A6AAAB, 0x459C4000, 0x42A6AAAB, 0x00000000, 0x00000000, 0x43FA0000, 0x42A6AAAB, 0x447A0000, 0x42A6AAAB, 0x44FA0000, 0x42A6AAAB, 0x453B8000, 0x42A6AAAB, 0x457A0000, 0x42A6AAAB, 0x459C4000, 0x42A6AAAB, 0x00000000, 0x00000000, 0x43FA0000, 0x42A6AAAB, 0x447A0000, 0x42A6AAAB, 0x44FA0000, 0x42A6AAAB, 0x453B8000, 0x42A6AAAB, 0x457A0000, 0x42A6AAAB, 0x459C4000, 0x42A6AAAB, 0x00000000, 0x00000000, 0x43FA0000, 0x42A6AAAB, 0x447A0000, 0x42A6AAAB, 0x44FA0000, 0x42A6AAAB, 0x453B8000, 0x42A6AAAB, 0x457A0000, 0x42A6AAAB, 0x459C4000, 0x42A6AAAB, 0x00000000, 0x00000000, 0x43FA0000, 0x42A6AAAB, 0x447A0000, 0x42A6AAAB, 0x44FA0000, 0x42A6AAAB, 0x453B8000, 0x42A6AAAB, 0x457A0000, 0x42A6AAAB, 0x459C4000, 0x42A6AAAB, 0x00000000, 0x00000000, 0x00000000};
extern const float lbl_803DA680[8] = {0.0f, 0.01f, 0.5f, 0.01f, 0.5f, 0.24f, 0.0f, 0.24f};
extern const char lbl_803DA6A0[0x20] = "Start LoadEffect - tire sprite\n";
extern const char lbl_803DA6C0[0x1E] = "End LoadEffect - tire sprite\n";
extern const char lbl_803DA6E0[0xC] = "clEnemyFace";
extern const char lbl_803DA6EC[0x11] = "clCDispInterface";
extern const char lbl_803DA700[0xA] = "clEFace3D";


static inline void LoadTireSpriteResources() {
    DebugPrintf(lbl_803DA6A0);
    void **tluts;
    const int *resources;
    TPLPalette **palettes;
    void **textures;
    int i;
    i = 0;
    textures = lbl_806D05F0;
    palettes = lbl_806D05F8;
    resources = lbl_806DB590;
    tluts = lbl_806D0600;
    for (; i < 2; ++i) {
        if (*textures != 0 || *palettes != 0) return;
        const char *path = ResourceTable_GetFilePathPtr(*resources);
        if (path == 0) return;
        TEXLoadPalette_Retry(palettes, path);
        if (*palettes == 0) return;
        unsigned int count = (*palettes)->count;
        *textures = FUN_8003b120(count << 5);
        *tluts = FUN_8003b120(count * 0xC);
        for (unsigned int k = 0; k < count; ++k) {
            if (TEXGetPaletteEntry(*palettes, k)->clut) {
                TEXBindPaletteEntry_CI(*palettes, *textures, *tluts, 0, k);
            } else {
                TEXBindPaletteEntry_RGB(*palettes, *textures, k);
            }
        }
        ++palettes;
        ++resources;
        ++tluts;
        ++textures;
    }
    DebugPrintf(lbl_803DA6C0);
}

static inline void TirePosition(float x, float y, float z) {
    GXFIFO.f32 = x;
    GXFIFO.f32 = y;
    GXFIFO.f32 = z;
}

static inline void TireTexCoord(float u, float v) {
    GXFIFO.f32 = u;
    GXFIFO.f32 = v;
}

static inline void DrawTireVertices(TireSprite *s, unsigned int color, float u, float v) {
    TireSprite *p = s;
    const float *uv = lbl_803DA680;
    for (int i = 0; i < 2; i++) {
        TirePosition(p->vx[0], p->vy[0], p->vz[0]);
        GXFIFO.u32 = color;
        float tu = u + uv[0];
        float tv = v + uv[1];
        TireTexCoord(tu, tv);
        TireTexCoord(tu, tv);
        TirePosition(p->vx[1], p->vy[1], p->vz[1]);
        GXFIFO.u32 = color;
        tu = u + uv[2];
        tv = v + uv[3];
        TireTexCoord(tu, tv);
        TireTexCoord(tu, tv);
        uv += 4;
        p = (TireSprite *)((char *)p + 8);
    }
}

#pragma push
#pragma opt_lifetimes off
void TireSprite_Draw(TireSprite *s) {
    Mtx m;

    if (lbl_806D05F0[0] == 0) {
        LoadTireSpriteResources();
        if (lbl_806D05F0[0] == 0) {
            return;
        }
    }
    GXSetCullMode(2);
    GXClearVtxDesc();
    GXSetVtxDesc(9, 1);
    GXSetVtxAttrFmt(0, 9, 1, 4, 0);
    GXSetVtxDesc(0xB, 1);
    GXSetVtxAttrFmt(0, 0xB, 1, 5, 0);
    GXSetVtxDesc(0xD, 1);
    GXSetVtxAttrFmt(0, 0xD, 1, 4, 0);
    GXSetVtxDesc(0xE, 1);
    GXSetVtxAttrFmt(0, 0xE, 1, 4, 0);
    GXSetNumChans(1);
    GXSetChanCtrl(4, 0, 1, 1, 0, 0, 2);
    GXSetNumTevStages(2);
    GXSetBlendMode(1, 4, 5, 0);
    GXSetTevOrder(0, 0, 0, 4);
    GXSetTevOrder(1, 1, 1, 0xFF);
    GXSetTevOp(0, 0);
    GXSetNumTexGens(2);
    GXSetTexCoordGen2(0, 1, 4, 0x3C, 0, 0x7D);
    GXSetTexCoordGen2(1, 1, 5, 0x3C, 0, 0x7D);
    GXSetTevColorIn(1, 0, 0xF, 0xF, 0xF);
    GXSetTevColorOp(1, 0, 0, 0, 1, 0);
    GXSetTevAlphaIn(1, 7, 4, 0, 7);
    GXSetTevAlphaOp(1, 0, 0, 0, 1, 0);
    GXLoadTexObj(lbl_806D05F0[0], 0);
    GXLoadTlut(lbl_806D0600[0], 0);
    GXLoadTexObj(lbl_806D05F0[1], 1);
    int flip = s->flip;
    float u = 0.0f;
    float v = u;
    if (flip & 1) {
        u = 0.5f;
    }
    if (flip & 2) {
        v = 0.25f;
    }
    if (flip & 4) {
        v = 0.5f;
    }
    HSD_CObjGetViewingMtx(*(void **)((char *)GetCourseScene3D() + 4), m);
    GXSetCurrentMtx(0);
    GXLoadPosMtxImm(m, 0);
    unsigned int color = 0xFFFFFF00;
    color = (color & ~0xFF) | ((int)(255.0f * s->alpha) & 0xFF);
    GXBegin(0x80, 0, 4);
    DrawTireVertices(s, color, u, v);
    HSD_StateInvalidate(-1);
}
#pragma pop


