#include "game/types/c_region.h"
C_REGION_BEGIN
/*
 * 0x8011DF98..0x8011EB1C: sprite handle pool. Releasing a handle runs its
 * draw-release callback, frees the pool slot and walks the chain of linked
 * handles (the self-recursion is inlined four levels deep). fn_8011E9C0
 * releases every live handle of one type under the frame profiler.
 */
C_REGION_END
#pragma cplusplus on
extern "C" {
void GXBegin(int type, int vtxfmt, unsigned short nverts);
void GXClearVtxDesc(void);
void GXLoadTexObj(void *obj, int id);
void GXLoadTlut(void *obj, unsigned int name);
void GXSetAlphaCompare(int comp0, unsigned char ref0, int op, int comp1, unsigned char ref1);
void GXSetBlendMode(int type, int src, int dst, int op);
void GXSetChanCtrl(int chan, unsigned char enable, int amb, int mat, unsigned int mask, int diff, int attn);
void GXSetCullMode(int mode);
void GXSetNumChans(unsigned char n);
void GXSetNumTevStages(unsigned char n);
void GXSetNumTexGens(unsigned char n);
void GXSetProjectionv(const float *p);
void GXSetScissor(unsigned int left, unsigned int top, unsigned int wd, unsigned int ht);
void GXSetTevAlphaIn(int stage, int a, int b, int c, int d);
void GXSetTevAlphaOp(int stage, int op, int bias, int scale, unsigned char clamp, int reg);
void GXSetTevColorIn(int stage, int a, int b, int c, int d);
void GXSetTevColorOp(int stage, int op, int bias, int scale, unsigned char clamp, int reg);
void GXSetTevOp(int stage, int mode);
void GXSetTevOrder(int stage, int coord, int map, int color);
void GXSetTexCoordGen2(int dst, int func, int src, unsigned int mtx, unsigned char normalize, unsigned int ptmtx);
void GXSetViewport(float x, float y, float w, float h, float nearz, float farz);
void GXSetVtxAttrFmt(int vtxfmt, int attr, int cnt, int type, unsigned char frac);
void GXSetVtxDesc(int attr, int type);
void GXSetZCompLoc(unsigned char before);
void GXSetZMode(unsigned char compare, int func, unsigned char update);
}

union GXFifoPipe {
    unsigned int u32;
    float f32;
};
#include "game/types/at_address.h"
volatile GXFifoPipe GXWGFifo AT_ADDRESS(0xCC008000);

static inline void GXPosition2f32(float x, float y) {
    GXWGFifo.f32 = x;
    GXWGFifo.f32 = y;
}

static inline void GXPosition3f32(float x, float y, float z) {
    GXWGFifo.f32 = x;
    GXWGFifo.f32 = y;
    GXWGFifo.f32 = z;
}

static inline void GXColor1u32(unsigned int c) {
    GXWGFifo.u32 = c;
}

static inline void GXTexCoord2f32(float s, float t) {
    GXWGFifo.f32 = s;
    GXWGFifo.f32 = t;
}

extern "C" {
unsigned int OSGetTick(void);
void Profiler_RecordFrame(int slot, float value);
extern const float lbl_806D6D98;
extern const float lbl_806D6D9C;
extern float lbl_80657208[];
}

typedef struct SpriteHandle {
    signed char active;
    char pad1[3];
    int type;
    int next;
    unsigned char keep;
    unsigned char released;
    char padE[0x14 - 0xE];
    void *texObj;
    void *tlut;
    char pad1C[0x24 - 0x1C];
    signed char tevMode;
    unsigned char posMode;
    char pad26[0x30 - 0x26];
    float z;
    char pad34[0x48 - 0x34];
    signed char uvFlip;
    char pad49[0x64 - 0x49];
    unsigned int color[4];
    char pad74[4];
    int blendType;
    int blendSrc;
    int blendDst;
    int blendOp;
    float corner[4][2];
    float uv[2][2];
    unsigned char hasTex2;
    char padB9[0xC0 - 0xB9];
    void *texObj2;
    void *tlut2;
    float uv2[2][2];
    unsigned char hasCallback;
    unsigned char callbackOn;
    char padDA[2];
    void (*callback)(void *arg);
    void *callbackArg;
} SpriteHandle;


extern "C" {
extern SpriteHandle g_SpriteHandlePool[];
extern int SpriteHandlePool_bss_80677C38[];
}

#include "game/types/SpriteNode.h"

#include "game/types/SpriteList.h"

extern "C" SpriteList *lbl_806D1500;

class ScopedTimer {
public:
    inline ScopedTimer(int slot) {
        m_slot = slot;
        m_startTick = OSGetTick();
    }
    inline ~ScopedTimer() {
        Profiler_RecordFrame(m_slot,
            (float)(((OSGetTick() - m_startTick) * 8) /
                ((*(unsigned int *)0x800000F8 / 4) / 125000)) / lbl_806D6D98);
    }

private:
    unsigned int m_startTick;
    volatile int m_slot;
};

class ScopedAccum {
public:
    inline ScopedAccum(int slot) {
        m_slot = slot;
        m_startTick = OSGetTick();
    }
    inline ~ScopedAccum() {
        lbl_80657208[m_slot] +=
            (float)(((OSGetTick() - m_startTick) * 8) /
                ((*(unsigned int *)0x800000F8 / 4) / 125000)) / lbl_806D6D9C;
    }

private:
    volatile int m_slot;
    unsigned int m_startTick;
};

struct SpriteUVTable {
    int idx[4][4][2];
};

#include "game/types/SavedGXState.h"

extern "C" {
void fn_8011EC18(unsigned char a);
void HSD_StateInvalidate(int state);
extern unsigned char lbl_806D14F0;
extern signed char lbl_806D14F1;
extern void *lbl_806D14F4;
extern void *lbl_806D14F8;
extern signed char lbl_806D14FC;
extern const SpriteUVTable SpriteHandlePool_rodata_803325D0;
extern SavedGXState SpriteHandle_bss_806573A0;
void fn_8011E31C(SpriteHandle *h);
}


extern "C" void fn_8011DF98(SpriteHandle *h) {
    if (h && h->active && !h->released) {
        if (h->hasCallback == 1 && h->callbackOn == 1) {
            if (h->callback) {
                h->callback(h->callbackArg);
            } else {
                fn_8011E31C(h);
            }
        }
        h->released = 1;
        if (!h->keep) {
            h->active = 0;
            SpriteHandlePool_bss_80677C38[h->type]--;
        }
        if (h->next != -1) {
            fn_8011DF98(&g_SpriteHandlePool[h->next]);
        }
    }
}

#pragma use_lmw_stmw on
extern "C" void fn_8011E31C(SpriteHandle *h) {
    int is3D = 0;
    int useColor = 0;
    int useTex = 0;
    int useTex2 = 0;
    int modeChanged = 0;
    int tevChanged = 0;
    SpriteUVTable tbl = SpriteHandlePool_rodata_803325D0;
    int i;
    int coord;
    int map;

    if (lbl_806D14F0 != h->posMode) {
        modeChanged = 1;
    }
    lbl_806D14F0 = h->posMode;
    if (h->tevMode != lbl_806D14F1) {
        tevChanged = 1;
    }
    lbl_806D14F1 = h->tevMode;
    if (h->posMode == 1) {
        is3D = 1;
    }
    if (h->tevMode != 1) {
        useColor = 1;
    }
    if (h->tevMode != 2) {
        useTex = 1;
    }
    if (h->hasTex2 != 0) {
        useTex2 = 1;
    }
    if (useTex2 != lbl_806D14FC) {
        tevChanged = 1;
    }
    lbl_806D14FC = useTex2;

    if (modeChanged) {
        GXSetChanCtrl(4, 1, 1, 1, 1, 2, 2);
        GXSetAlphaCompare(7, 0, 0, 7, 0);
        GXSetZCompLoc(1);
        GXSetZMode(1, 3, 1);
        GXSetScissor(SpriteHandle_bss_806573A0.scissor[0], SpriteHandle_bss_806573A0.scissor[1], SpriteHandle_bss_806573A0.scissor[2], SpriteHandle_bss_806573A0.scissor[3]);
        GXSetViewport(SpriteHandle_bss_806573A0.viewport[0], SpriteHandle_bss_806573A0.viewport[1], SpriteHandle_bss_806573A0.viewport[2],
            SpriteHandle_bss_806573A0.viewport[3], SpriteHandle_bss_806573A0.viewport[4], SpriteHandle_bss_806573A0.viewport[5]);
        GXSetProjectionv(SpriteHandle_bss_806573A0.proj);
        GXSetCullMode(SpriteHandle_bss_806573A0.cullMode);
        HSD_StateInvalidate(-1);
        fn_8011EC18(h->posMode);
    }
    GXSetBlendMode(h->blendType, h->blendSrc, h->blendDst, h->blendOp);

    if (tevChanged) {
        if (useTex2) {
            GXSetNumTexGens(2);
            GXSetTexCoordGen2(0, 1, 4, 0x3C, 0, 0x7D);
            GXSetTexCoordGen2(1, 1, 5, 0x3C, 0, 0x7D);
        } else if (useTex) {
            GXSetNumTexGens(1);
            GXSetTexCoordGen2(0, 1, 4, 0x3C, 0, 0x7D);
        } else {
            GXSetNumTexGens(0);
        }
    }
    if (tevChanged) {
        if (!useColor) {
            GXSetNumChans(0);
        } else {
            GXSetNumChans(1);
        }
    }
    if (tevChanged) {
        if (useTex2) {
            GXSetNumTevStages(2);
        } else {
            GXSetNumTevStages(1);
        }
        if (!useTex) {
            coord = 0xFF;
            map = 0xFF;
        } else {
            coord = 0;
            map = 0;
        }
        GXSetTevOrder(0, coord, map, useColor ? 4 : 0xFF);
        if (useTex2) {
            GXSetTevOrder(1, 1, 1, 0xFF);
        }
        switch (h->tevMode) {
        case 1:
            GXSetTevOp(0, 3);
            break;
        case 2:
            GXSetTevOp(0, 4);
            break;
        case 3:
            GXSetTevColorIn(0, 8, 9, 0xB, 0xA);
            GXSetTevColorOp(0, 0, 0, 0, 1, 0);
            break;
        case 4:
            GXSetTevColorIn(0, 8, 0xF, 0xF, 0xA);
            GXSetTevColorOp(0, 0, 0, 0, 1, 0);
            break;
        default:
            GXSetTevOp(0, 0);
            break;
        }
        if (useTex2) {
            GXSetTevColorIn(1, 0, 0xF, 0xF, 0xF);
            GXSetTevColorOp(1, 0, 0, 0, 1, 0);
            GXSetTevAlphaIn(1, 7, 4, 0, 7);
            GXSetTevAlphaOp(1, 0, 0, 0, 1, 0);
        }
    }

    if (tevChanged || modeChanged) {
        GXClearVtxDesc();
        GXSetVtxDesc(9, 1);
        if (!is3D) {
            GXSetVtxAttrFmt(0, 9, 0, 4, 0);
        } else {
            GXSetVtxAttrFmt(0, 9, 1, 4, 0);
        }
        if (useColor) {
            GXSetVtxDesc(0xB, 1);
            GXSetVtxAttrFmt(0, 0xB, 1, 5, 0);
        }
    }
    if (useTex) {
        if (h->texObj != lbl_806D14F4) {
            if (h->tlut != 0) {
                GXLoadTlut(h->tlut, 0);
            }
            GXLoadTexObj(h->texObj, 0);
            lbl_806D14F4 = h->texObj;
        }
        if (tevChanged || modeChanged) {
            GXSetVtxDesc(0xD, 1);
            GXSetVtxAttrFmt(0, 0xD, 1, 4, 0);
        }
    }
    if (useTex2) {
        if (h->tlut2 != 0) {
            GXLoadTlut(h->tlut2, 1);
        }
        GXLoadTexObj(h->texObj2, 1);
        lbl_806D14F8 = h->texObj2;
        GXSetVtxDesc(0xE, 1);
        GXSetVtxAttrFmt(0, 0xE, 1, 4, 0);
    }

    GXBegin(0x80, 0, 4);
    for (i = 0; i < 4; i++) {
        if (!is3D) {
            GXPosition2f32(h->corner[i][0], h->corner[i][1]);
        } else {
            GXPosition3f32(h->corner[i][0], h->corner[i][1], h->z);
        }
        if (useColor) {
            GXColor1u32(h->color[i]);
        }
        if (useTex) {
            GXTexCoord2f32(h->uv[tbl.idx[h->uvFlip][i][0]][0], h->uv[tbl.idx[h->uvFlip][i][1]][1]);
        }
        if (useTex2) {
            GXTexCoord2f32(h->uv2[tbl.idx[h->uvFlip][i][0]][0], h->uv2[tbl.idx[h->uvFlip][i][1]][1]);
        }
    }
}
#pragma use_lmw_stmw reset

extern "C" void fn_8011E9C0(int type) {
    ScopedAccum accum(1);
    ScopedTimer timer(13);
    SpriteNode *node;
    SpriteNode *next;
    SpriteHandle *h;

    for (node = lbl_806D1500->head; node; node = next) {
        next = node->next;
        h = &g_SpriteHandlePool[node->index];
        if (type == h->type) {
            fn_8011DF98(h);
        }
    }
}
