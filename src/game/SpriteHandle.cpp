/*
 * 0x8011EB1C..0x801223E8: sprite handles (creation, per-handle setters,
 * resource preload and pool GC) and the ResCtrl resource list.
 */
#pragma cplusplus on

struct TexObjData {
    unsigned int words[8];
};

struct TlutObjData {
    unsigned int words[3];
};

struct ResEntry {
    int id;
    int prev;
    void *palette;
    int fC;
    TexObjData *data0;
    TlutObjData *data1;
    unsigned char *data2;
};


#include "game/types/TEXHeader.h"

#include "game/types/TEXDescriptor.h"

#include "game/types/SavedGXState.h"
extern "C" void MemoryManager_TimedFree(void *p);

#include "game/types/Vec3.h"

struct LNode {
    LNode *prev;
    LNode *next;
};

class LListImp {
public:
    int count;
    LNode end;

    inline ~LListImp() {
        LNode *first = end.next;
        LNode *last = &end;
        if (first != last) {
            LNode *lp = last->prev;
            first->prev->next = lp->next;
            lp->next->prev = first->prev;
            while (first != last) {
                LNode *n = first;
                first = first->next;
                MemoryManager_TimedFree(n);
                count--;
            }
        }
    }
};

class LList : public LListImp {
public:
    inline ~LList() {}
};

struct ProfTimer {
    int slot;
    unsigned int start;
};

#include "game/types/SpriteNode.h"
void *operator new(unsigned long size);
void *operator new[](unsigned long size);
void operator delete(void *p) throw();

struct SpriteList {
    int capacity;
    int count;
    SpriteNode *nodes;
    SpriteNode *freeHead;
    SpriteNode *freeTail;
    SpriteNode *head;
    SpriteNode *tail;

    inline SpriteList(int n) {
        int i;
        capacity = n;
        nodes = new SpriteNode[n];
        for (i = 0; i < n; i++) {
            nodes[i].index = i;
        }
        count = 0;
        freeHead = nodes;
        freeTail = &nodes[capacity - 1];
        for (i = 0; i < capacity; i++) {
            if (i == 0) {
                nodes[i].prev = 0;
            } else {
                nodes[i].prev = &nodes[i - 1];
            }
            if (i == capacity - 1) {
                nodes[i].next = 0;
            } else {
                nodes[i].next = &nodes[i + 1];
            }
        }
        head = 0;
        tail = 0;
    }
};


struct ResCtrl {
    int id;
    int prev;
    int f8;
    int fC;
    unsigned char f10;
    char pad11[3];
    float f14;
    float f18;
    float f1C;
    float f20;
    float f24;
    float f28;
    float f2C;
    float f30;
    unsigned char slots[0x10];
    unsigned char f44;
    unsigned char f45;
    char pad46[2];
    int f48;
    int f4C;
    int f50;
    int f54;
};


#include "game/types/SpriteHandle.h"


extern "C" {
void GXSetAlphaCompare(int, int, int, int, int);
void GXSetChanCtrl(int, int, int, int, int, int, int);
void GXSetCullMode(int);
void GXSetProjectionv(const float *p);
void GXSetScissor(unsigned int, unsigned int, unsigned int, unsigned int);
void GXSetViewport(float, float, float, float, float, float);
void GXSetZCompLoc(int);
void GXSetZMode(int, int, int);
void HSD_StateInvalidate(int);
void fn_8011E9C0(int type);
extern unsigned char lbl_806D14F0;
extern SavedGXState SpriteHandle_bss_806573A0;
void C_MTXLookAt(float (*)[4], const Vec3 *, const Vec3 *, const Vec3 *);
void C_MTXOrtho(float (*)[4], float, float, float, float, float, float);
void GXGetCullMode(int *);
void GXGetProjectionv(float *);
void GXGetScissor(unsigned int *, unsigned int *, unsigned int *, unsigned int *);
void GXGetViewportv(float *);
void GXLoadPosMtxImm(float (*)[4], unsigned int);
void GXSetCurrentMtx(unsigned int);
void GXSetProjection(float (*)[4], int);
extern float g_glyphClipMaxX;
extern float g_glyphClipMaxY;
extern const float g_glyphClipMinXY;
extern unsigned char lbl_806D14F1;
extern unsigned int lbl_806D14F4;
extern unsigned int lbl_806D14F8;
extern unsigned char lbl_806D14FC;
extern const float lbl_806D6D8C;
extern const float lbl_806D6DAC;
extern const float lbl_806D6DB0;
extern const float lbl_806D6DB4;
extern const float lbl_806D6DB8;
extern const float lbl_806D6DBC;
extern const float lbl_806D6DC0;
extern const float lbl_806D6DC4;
extern const float lbl_806D6DC8;
extern const float lbl_806D6DCC;
extern const float lbl_806D6DD0;
extern unsigned int SpriteHandle_bss_80657360[];
extern SpriteHandle g_SpriteHandlePool[];
unsigned char IsValidResourceId(int id);
int ResourceTable_GetChainNextId(int id);
int ResourceTable_GetGroupKey(int id);
void ResourceTable_GetOffsetXY(int id, float *x, float *y);
void ResourceTable_GetSizeXY(int id, float *x, float *y);
int ResourceTable_GetSlotIndex(int id);
TEXDescriptor *TEXGetPaletteEntry(void *pal, unsigned int idx);
extern const float lbl_806D6D88;
extern unsigned int lbl_806D6D90;
extern ResEntry SpriteHandle_bss_806573E8[600];
unsigned int OSGetTick(void);
void Profiler_RecordFrame(int slot, float value);
extern SpriteList *lbl_806D1500;
extern const float lbl_806D6D98;
extern const float lbl_806D6D9C;
extern float lbl_80657208[];
extern void __dt__11ScopedTimerFv();
void MemoryManager_Free(void *p);
void TEXReleasePalette(void **pal);
extern int SpriteHandle_bss_8065B588[600];
void fn_8011DC20(ResEntry *e);
unsigned char ResourceSlot_Load(ResEntry *e, int id);
extern void Alloc();
extern void FUN_8003b120();
void MemoryManager_TimedFree(void *p);
void fn_801F6494(void);
extern unsigned char lbl_806D14FD;
float LUT_Cosine(float);
float LUT_Sine(float);
signed char ResourceTable_GetFlagsByte(int id);
void ResourceTable_GetScaleXY(int id, float *x, float *y);
extern unsigned int SpriteHandle_rodata_80332528[];
void *memset(void *p, int c, unsigned long n);
void __destroy_arr(void *, void *, unsigned long, unsigned long);
void DoublyLinkedList_Init(void *);
extern unsigned int SpriteHandle_bss_80657234[];
void __construct_array(void *, void *, void *, unsigned long, unsigned long);
void *__register_global_object(void *, void *, void *);
extern unsigned int fn_8011DF70[];
extern unsigned int SpriteHandle_bss_80657228[];
/* .bss 0x80657228..0x80677C38 is owned by this unit (definition order). */
unsigned int SpriteHandle_bss_80657228[3];
unsigned int SpriteHandle_bss_80657234[0x18];
unsigned int lbl_80657294[3];
unsigned int lbl_806572A0[0x30];
unsigned int SpriteHandle_bss_80657360[0x10];
SavedGXState SpriteHandle_bss_806573A0;
ResEntry SpriteHandle_bss_806573E8[600];
int SpriteHandle_bss_8065B588[600];
SpriteHandle g_SpriteHandlePool[500];
void fn_8011EB1C(void);
void fn_8011EC18(unsigned char a);
void SpriteHandle_RecomputeCull(int h);
void SpriteLayer_SetResource(int h, int id);
void fn_8011F870(unsigned int mask);
void fn_8011F994(int type);
int SpriteHandle_CreateEx(ResCtrl *a, int b, unsigned char c);
void fn_8012094C(void);
int fn_80120A08(int id);
unsigned char PreloadResource(int id);
void SpriteHandlePool_GC(void);
void fn_80121210(void);
void fn_801213EC(void);
void fn_801217E8(SpriteHandle *s);
int Stub_NoOp_80121c34(int x);
unsigned char fn_80121C38(ResCtrl *r);
void fn_80121E10(ResCtrl *r);
ResCtrl *ResCtrl_Init(ResCtrl *r);
void *fn_80121F54(void *self, short flag);
LList *fn_80121FB4(LList *l, short flag);
ProfTimer *dtor_80122068(ProfTimer *t, short flag);
struct LIter;
struct LListImp;
void fn_8012215C(LIter *ret, LListImp *l, LIter *it);
LListImp *fn_801221D4(LListImp *l);
void fn_80122204(void);
LList *fn_8012223C(LList *l, short flag);
LListImp *fn_801222F0(LListImp *l);
void fn_80122320(LListImp *l);
void fn_80122338(void);

#pragma section R ".extab_user"











__declspec(section ".extab_user") static const struct { unsigned int f0; unsigned int f1; unsigned int f2; unsigned int f3; unsigned int f4; unsigned int f5; unsigned int f6; unsigned int f7; unsigned int f8; unsigned int f9; unsigned int f10; unsigned int f11; unsigned int f12; unsigned int f13; unsigned int f14; unsigned int f15; unsigned int f16; unsigned int f17; unsigned int f18; unsigned int f19; unsigned int f20; unsigned int f21; unsigned int f22; void *f23; unsigned int f24; void *f25; } extab_SpriteHandle_CreateEx = { 0x488A0000, 0x00000048, 0x001C0060, 0x00000138, 0x00150060, 0x00000210, 0x00000058, 0x0000021C, 0x00150060, 0x0000030C, 0x00000058, 0x00000318, 0x00150060, 0x000003E8, 0x00190058, 0x00000458, 0x00150060, 0x00000528, 0x01600058, 0x00000CCC, 0x00150060, 0x00000000, 0x02000010, (void *)&__dt__11ScopedTimerFv, 0x82000018, (void *)&dtor_80122068 };



__declspec(section ".extab_user") static const unsigned char extab_fn_80120A08[8] = {
    0x28, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

__declspec(section ".extab_user") static const unsigned char extab_PreloadResource[8] = {
    0x28, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

__declspec(section ".extab_user") static const struct { unsigned int f0; unsigned int f1; unsigned int f2; unsigned int f3; unsigned int f4; void *f5; } extab_fn_80121210 = { 0x180A0000, 0x0000005C, 0x00060010, 0x00000000, 0x82000008, (void *)&__dt__11ScopedTimerFv };
















#pragma section R ".extabindex_user"











__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_SpriteHandle_CreateEx = {
    (void *)&SpriteHandle_CreateEx, 0x00000DB4, (void *)&extab_SpriteHandle_CreateEx
};



__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_fn_80120A08 = {
    (void *)&fn_80120A08, 0x00000378, (void *)extab_fn_80120A08
};

__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_PreloadResource = {
    (void *)&PreloadResource, 0x000003A0, (void *)extab_PreloadResource
};

















}

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

inline void SpriteList_Release(SpriteList *l, SpriteNode *n) {
    if (n->prev != 0) {
        n->prev->next = n->next;
    }
    if (n->next != 0) {
        n->next->prev = n->prev;
    }
    if (l->head == n) {
        l->head = n->next;
    }
    if (l->tail == n) {
        l->tail = n->prev;
    }
    n->prev = 0;
    n->next = 0;
    if (l->freeTail != 0) {
        l->freeTail->next = n;
    }
    n->prev = l->freeTail;
    if (l->freeHead == 0) {
        l->freeHead = n;
    }
    l->freeTail = n;
    l->count--;
}

inline void SpriteList_Clear(SpriteList *l) {
    if (l->count != 0) {
        SpriteNode *n = l->head;
        while (n != 0) {
            SpriteNode *next = n->next;
            SpriteList_Release(l, n);
            n = next;
        }
    }
}

static inline void ResCtrl_Reset(ResCtrl *r) {
    r->id = -1;
    r->prev = -1;
    r->f8 = 0;
    r->fC = 0;
    r->f10 = 1;
    r->f1C = 0.0f;
    r->f18 = 0.0f;
    r->f14 = 0.0f;
    r->f24 = 1.0f;
    r->f20 = 1.0f;
    r->f28 = 0.0f;
    r->f30 = 1.0f;
    r->f2C = 1.0f;
    r->f45 = 0;
    r->f44 = 0;
    r->f48 = 1;
    r->f4C = 4;
    r->f50 = 5;
    r->f54 = 0xF;
    memset(r->slots, -1, 0x10);
}

static inline SpriteHandle *GetHandle(int h) {
    return &g_SpriteHandlePool[(h - 1) % 500];
}


#pragma auto_inline off
extern "C" void fn_8011EB1C(void) {
    int i;
    fn_8011EC18(lbl_806D14F0);
    for (i = 0; i < 8; i++) {
        fn_8011E9C0(i);
    }
    GXSetChanCtrl(4, 1, 1, 1, 1, 2, 2);
    GXSetAlphaCompare(7, 0, 0, 7, 0);
    GXSetZCompLoc(1);
    GXSetZMode(1, 3, 1);
    GXSetScissor(SpriteHandle_bss_806573A0.scissor[0], SpriteHandle_bss_806573A0.scissor[1], SpriteHandle_bss_806573A0.scissor[2], SpriteHandle_bss_806573A0.scissor[3]);
    GXSetViewport(SpriteHandle_bss_806573A0.viewport[0], SpriteHandle_bss_806573A0.viewport[1], SpriteHandle_bss_806573A0.viewport[2], SpriteHandle_bss_806573A0.viewport[3], SpriteHandle_bss_806573A0.viewport[4], SpriteHandle_bss_806573A0.viewport[5]);
    GXSetProjectionv(SpriteHandle_bss_806573A0.proj);
    GXSetCullMode(SpriteHandle_bss_806573A0.cullMode);
    HSD_StateInvalidate(-1);
}
#pragma auto_inline reset

extern "C" void fn_8011EC18(unsigned char a) {
    float proj[4][4];
    float view[3][4];
    Vec3 pos;
    Vec3 up;
    Vec3 at;
    float n;
    float f;
    int i;

    lbl_806D14F0 = a;
    GXSetZCompLoc(0);
    if (a == 1) {
        GXSetZMode(1, 3, 1);
    } else {
        GXSetZMode(0, 7, 1);
    }
    GXGetCullMode(&SpriteHandle_bss_806573A0.cullMode);
    GXGetProjectionv(SpriteHandle_bss_806573A0.proj);
    GXGetViewportv(SpriteHandle_bss_806573A0.viewport);
    GXGetScissor(&SpriteHandle_bss_806573A0.scissor[0], &SpriteHandle_bss_806573A0.scissor[1], &SpriteHandle_bss_806573A0.scissor[2], &SpriteHandle_bss_806573A0.scissor[3]);
    GXSetCullMode(0);
    GXSetViewport(g_glyphClipMinXY, g_glyphClipMinXY, g_glyphClipMaxX, g_glyphClipMaxY, g_glyphClipMinXY, lbl_806D6D8C);
    if (!a) {
        n = lbl_806D6DAC;
        f = lbl_806D6DB0;
    } else {
        n = lbl_806D6DB4;
        f = lbl_806D6DB8;
    }
    C_MTXOrtho(proj, lbl_806D6DBC, lbl_806D6DC0, lbl_806D6DC4, lbl_806D6DC8, n, f);
    GXSetProjection(proj, 1);
    GXSetScissor(0, 0, 640, 480);
    up.x = g_glyphClipMinXY;
    up.y = lbl_806D6DCC;
    up.z = g_glyphClipMinXY;
    pos.x = lbl_806D6DC8 - up.y * up.x;
    pos.y = lbl_806D6DBC - up.y * up.x;
    pos.z = lbl_806D6DD0;
    at.x = pos.x;
    at.y = pos.y;
    at.z = g_glyphClipMinXY;
    C_MTXLookAt(view, &pos, &up, &at);
    GXLoadPosMtxImm(view, 0);
    GXSetCurrentMtx(0);
    GXSetAlphaCompare(4, 0, 1, 4, 0);
    GXSetChanCtrl(4, 0, 1, 1, 0, 0, 2);
    lbl_806D14F1 = 5;
    for (i = 0; i < 15; i++) {
        SpriteHandle_bss_80657360[i] = 0;
    }
    lbl_806D14F4 = 0;
    lbl_806D14F8 = 0;
    lbl_806D14FC = 0;
    SpriteHandle_bss_80657360[15] = 0;
}

extern "C" void SpriteHandle_Destroy(int h) {
    if (h != 0) {
        SpriteHandle *s = GetHandle(h);
        s->keep = 0;
        s->hasCallback = 0;
    }
}

extern "C" void SpriteHandle_RecomputeCull(int h) {
    if (h != 0) {
        SpriteHandle *s = GetHandle(h);
        if (s->dirty) {
            int i;
            float maxY, maxX, minX, minY;
            fn_801217E8(s);
            minX = s->corner[0][0];
            minY = s->corner[0][1];
            maxX = minX;
            maxY = minY;
            for (i = 0; i < 4; i++) {
                float x = s->corner[i][0];
                float y;
                if (x < minX) {
                    minX = x;
                }
                if (maxX < x) {
                    maxX = x;
                }
                y = s->corner[i][1];
                if (y < minY) {
                    minY = y;
                }
                if (maxY < y) {
                    maxY = y;
                }
            }
            s->callbackOn = 1;
            if (g_glyphClipMaxX < minX) {
                s->callbackOn = 0;
            }
            if (maxX < g_glyphClipMinXY) {
                s->callbackOn = 0;
            }
            if (g_glyphClipMaxY < minY) {
                s->callbackOn = 0;
            }
            if (maxY < g_glyphClipMinXY) {
                s->callbackOn = 0;
            }
            s->dirty = 0;
        }
    }
}

extern "C" void SpriteHandle_SetActiveFlag(int h, unsigned char on) {
    if (h != 0) {
        GetHandle(h)->hasCallback = on;
    }
}

static inline ResEntry *FindResEntry(int id) {
    int key = ResourceTable_GetGroupKey(id);
    int i;
    for (i = 0; i < 600; i++) {
        if (key == SpriteHandle_bss_806573E8[i].prev) {
            return &SpriteHandle_bss_806573E8[i];
        }
    }
    return 0;
}

#pragma use_lmw_stmw on
extern "C" void SpriteLayer_SetResource(int h, int id) {
    if (h != 0) {
        SpriteHandle *s = &g_SpriteHandlePool[(h - 1) % 500];
        if (s->tevMode != 2 && s->resId != id && IsValidResourceId(id)) {
            ResEntry *e = FindResEntry(id);
            unsigned int slot;
            TEXDescriptor *d;
            float texW, texH;
            float iw, ih;
            if (e == 0) {
                if (!PreloadResource(id)) {
                    return;
                }
                e = FindResEntry(id);
            }
            s->baseResId = id;
            s->resId = id;
            slot = ResourceTable_GetSlotIndex(id);
            d = TEXGetPaletteEntry(e->palette, slot);
            s->texObj = &e->data0[slot];
            if (d->clut != 0) {
                s->tlut = &e->data1[slot];
            } else {
                s->tlut = 0;
            }
            s->texFmt = e->data2[slot];
            ResourceTable_GetSizeXY(id, &s->texW, &s->texH);
            unsigned int texSlot = ResourceTable_GetSlotIndex(id);
            d = TEXGetPaletteEntry(e->palette, texSlot);
            texW = d->tex->width;
            texH = d->tex->height;
            ResourceTable_GetOffsetXY(id, &s->texUV[0][0], &s->texUV[0][1]);
            iw = 1.0f / texW;
            ih = 1.0f / texH;
            s->texUV[0][0] += 0.5f;
            s->texUV[0][1] += 0.5f;
            s->texUV[0][0] = iw * s->texUV[0][0];
            s->texUV[0][1] = ih * s->texUV[0][1];
            s->texUV[1][0] = iw * (s->texW - 1.0f) + s->texUV[0][0];
            s->texUV[1][1] = ih * (s->texH - 1.0f) + s->texUV[0][1];
            if (s->flip & 1) {
                float t = s->texUV[0][0];
                s->texUV[0][0] = s->texUV[1][0];
                s->texUV[1][0] = t;
            }
            if (s->flip & 2) {
                float t = s->texUV[0][1];
                s->texUV[0][1] = s->texUV[1][1];
                s->texUV[1][1] = t;
            }
            s->hasTex2 = 0;
            id = ResourceTable_GetChainNextId(id);
            if (id != -1) {
                ResEntry *e2 = FindResEntry(id);
                if (e2 == 0) {
                    PreloadResource(id);
                    e2 = FindResEntry(id);
                }
                if (e2 != 0) {
                    float w2, h2;
                    float uv[4];
                    float tw, th;
                    float iw2, ih2;
                    s->hasTex2 = 1;
                    s->resId2 = id;
                    unsigned int slot2 = ResourceTable_GetSlotIndex(id);
                    d = TEXGetPaletteEntry(e2->palette, slot2);
                    s->texObj2 = &e2->data0[slot2];
                    if (d->clut != 0) {
                        s->tlut2 = &e2->data1[slot2];
                    } else {
                        s->tlut2 = 0;
                    }
                    ResourceTable_GetSizeXY(id, &w2, &h2);
                    tw = d->tex->width;
                    th = d->tex->height;
                    ResourceTable_GetOffsetXY(id, &uv[0], &uv[1]);
                    uv[0] += 0.5f;
                    uv[1] += 0.5f;
                    iw2 = 1.0f / tw;
                    ih2 = 1.0f / th;
                    uv[0] = iw2 * uv[0];
                    uv[1] = ih2 * uv[1];
                    uv[2] = iw2 * (w2 - 1.0f) + uv[0];
                    uv[3] = ih2 * (h2 - 1.0f) + uv[1];
                    if (s->flip & 1) {
                        float t = uv[0];
                        uv[0] = uv[2];
                        uv[2] = t;
                    }
                    if (s->flip & 2) {
                        float t = uv[1];
                        uv[1] = uv[3];
                        uv[3] = t;
                    }
                    s->uv2[0] = uv[0];
                    s->uv2[1] = uv[1];
                    s->uv2[2] = uv[2];
                    s->uv2[3] = uv[3];
                }
            }
            s->dirty = 1;
        }
    }
}
#pragma use_lmw_stmw reset

extern "C" void SpriteHandle_SetCornerAlpha(int h, unsigned char a) {
    if (h != 0) {
        SpriteHandle *s = GetHandle(h);
        s->color[0] = (s->color[0] & 0xFFFFFF00) | a;
        s->color[1] = (s->color[1] & 0xFFFFFF00) | a;
        s->color[2] = (s->color[2] & 0xFFFFFF00) | a;
        s->color[3] = (s->color[3] & 0xFFFFFF00) | a;
    }
}

extern "C" void fn_8011F610(int h, unsigned char r, unsigned char g, unsigned char b) {
    if (h != 0) {
        SpriteHandle *s = GetHandle(h);
        s->color[0] = (s->color[0] & 0xFF) | (r << 24) | (g << 16) | (b << 8);
        s->color[1] = (s->color[1] & 0xFF) | (r << 24) | (g << 16) | (b << 8);
        s->color[2] = (s->color[2] & 0xFF) | (r << 24) | (g << 16) | (b << 8);
        s->color[3] = (s->color[3] & 0xFF) | (r << 24) | (g << 16) | (b << 8);
    }
}

extern "C" void fn_8011F6C8(int h, float *uv) {
    if (h != 0) {
        SpriteHandle *s = GetHandle(h);
        s->hasUV = 1;
        s->uv[0] = uv[0];
        s->uv[1] = uv[1];
        s->uv[2] = uv[2];
        s->uv[3] = uv[3];
        s->uv[4] = uv[4];
        s->uv[5] = uv[5];
        s->dirty = 1;
    }
}

extern "C" void fn_8011F744(int h, float x, float y) {
    if (h != 0) {
        SpriteHandle *s = GetHandle(h);
        if (s->posX != x || s->posY != y) {
            s->posX = x;
            s->posY = y;
            s->dirty = 1;
        }
    }
}

extern "C" void fn_8011F7AC(int h, float r) {
    if (h != 0) {
        SpriteHandle *s = GetHandle(h);
        if (s->rot != r) {
            s->rot = r;
            s->dirty = 1;
        }
    }
}

extern "C" void fn_8011F804(int h, float x, float y) {
    if (h != 0) {
        SpriteHandle *s = GetHandle(h);
        if (s->sizeX != x || s->sizeY != y) {
            s->sizeX = x;
            s->sizeY = y;
            s->dirty = 1;
        }
    }
}

extern "C" void fn_8011F86C(void) {
}

extern "C" void fn_8011F870(unsigned int mask) {
    int i;
    if (mask == 0) {
        return;
    }
    fn_8011EC18(lbl_806D14F0);
    for (i = 0; i < 8; i++) {
        if (mask & (1 << i)) {
            fn_8011E9C0(i);
        }
    }
    GXSetChanCtrl(4, 1, 1, 1, 1, 2, 2);
    GXSetAlphaCompare(7, 0, 0, 7, 0);
    GXSetZCompLoc(1);
    GXSetZMode(1, 3, 1);
    GXSetScissor(SpriteHandle_bss_806573A0.scissor[0], SpriteHandle_bss_806573A0.scissor[1], SpriteHandle_bss_806573A0.scissor[2], SpriteHandle_bss_806573A0.scissor[3]);
    GXSetViewport(SpriteHandle_bss_806573A0.viewport[0], SpriteHandle_bss_806573A0.viewport[1], SpriteHandle_bss_806573A0.viewport[2], SpriteHandle_bss_806573A0.viewport[3], SpriteHandle_bss_806573A0.viewport[4], SpriteHandle_bss_806573A0.viewport[5]);
    GXSetProjectionv(SpriteHandle_bss_806573A0.proj);
    GXSetCullMode(SpriteHandle_bss_806573A0.cullMode);
    HSD_StateInvalidate(-1);
}

extern "C" void fn_8011F994(int type) {
    int t = type;
    if (type < 0 || type >= 8) {
        t = 0;
    }
    fn_8011EC18(lbl_806D14F0);
    fn_8011E9C0(t);
    GXSetChanCtrl(4, 1, 1, 1, 1, 2, 2);
    GXSetAlphaCompare(7, 0, 0, 7, 0);
    GXSetZCompLoc(1);
    GXSetZMode(1, 3, 1);
    GXSetScissor(SpriteHandle_bss_806573A0.scissor[0], SpriteHandle_bss_806573A0.scissor[1], SpriteHandle_bss_806573A0.scissor[2], SpriteHandle_bss_806573A0.scissor[3]);
    GXSetViewport(SpriteHandle_bss_806573A0.viewport[0], SpriteHandle_bss_806573A0.viewport[1], SpriteHandle_bss_806573A0.viewport[2], SpriteHandle_bss_806573A0.viewport[3], SpriteHandle_bss_806573A0.viewport[4], SpriteHandle_bss_806573A0.viewport[5]);
    GXSetProjectionv(SpriteHandle_bss_806573A0.proj);
    GXSetCullMode(SpriteHandle_bss_806573A0.cullMode);
    HSD_StateInvalidate(-1);
}

extern "C" void fn_8011FA98(void) {
    fn_8011EB1C();
}

extern "C" void fn_8011FAB8(void) {
    fn_8011EB1C();
}

extern "C" int SpriteHandle_CreateDefault(int a, int b) {
    return SpriteHandle_CreateEx((ResCtrl *)a, b, 1);
}

extern "C" unsigned char fn_8011FAFC(int a, int b) {
    return SpriteHandle_CreateEx((ResCtrl *)a, b, 0) != 0;
}

class AccumTimer {
public:
    inline AccumTimer(int slot) {
        m_slot = slot;
        m_startTick = OSGetTick();
    }
    inline ~AccumTimer() {
        lbl_80657208[m_slot] += (float)(((OSGetTick() - m_startTick) * 8) /
            ((*(unsigned int *)0x800000F8 / 4) / 125000)) / lbl_806D6D9C;
    }

private:
    volatile int m_slot;
    unsigned int m_startTick;
};

inline SpriteNode *SpriteList_Alloc(SpriteList *l) {
    if (l->capacity <= l->count) {
        return 0;
    }
    SpriteNode *n = l->freeHead;
    if (n->prev != 0) {
        n->prev->next = n->next;
    }
    if (n->next != 0) {
        n->next->prev = n->prev;
    }
    if (l->freeHead == n) {
        l->freeHead = n->next;
    }
    if (l->freeTail == n) {
        l->freeTail = n->prev;
    }
    n->prev = 0;
    n->next = 0;
    if (l->tail != 0) {
        l->tail->next = n;
    }
    n->prev = l->tail;
    if (l->head == 0) {
        l->head = n;
    }
    l->tail = n;
    l->count++;
    return n;
}

static inline int MakeHandleId(int type, int idx) {
    return type * 500 + idx + 1;
}

/* exceptions off: the extab entry above (actions for the two timers) stays manual. */
#pragma exceptions off
#pragma use_lmw_stmw on
extern "C" int SpriteHandle_CreateEx(ResCtrl *a, int b, unsigned char c) {
    AccumTimer total(0);
    ScopedTimer timer(0xD);
    if (lbl_806D1500->count >= lbl_806D1500->capacity) {
        return 0;
    }
    if (a == 0) {
        return 0;
    }
    if (!c && !fn_80121C38(a)) {
        return 0;
    }
    int id = a->id;
    int resId = id;
    int baseId = id;
    if (a->f8 == 2) {
        resId = 0x1B8C;
        baseId = 0x1B8C;
    }
    if (!IsValidResourceId(baseId)) {
        return 0;
    }
    ResourceTable_GetGroupKey(baseId);
    ResEntry *e = FindResEntry(resId);
    if (e == 0) {
        if (!PreloadResource(resId)) {
            return 0;
        }
        e = FindResEntry(resId);
    }
    SpriteNode *node = SpriteList_Alloc(lbl_806D1500);
    int index = node->index;
    SpriteHandle *h = &g_SpriteHandlePool[index];
    h->active = 1;
    h->type = b;
    h->next = -1;
    h->keep = c;
    h->callback = 0;
    h->callbackArg = 0;
    h->baseResId = baseId;
    h->resId = resId;
    int slot = ResourceTable_GetSlotIndex(baseId);
    TEXDescriptor *d = TEXGetPaletteEntry(e->palette, slot);
    h->texObj = &e->data0[slot];
    if (d->clut != 0) {
        h->tlut = &e->data1[slot];
    } else {
        h->tlut = 0;
    }
    h->texFmt = e->data2[slot];
    h->tevMode = a->f8;
    h->posMode = a->fC != 0;
    h->posMode_026 = a->f10;
    h->sizeX = a->f14;
    h->sizeY = a->f18;
    *(float *)h->z = a->f1C;
    h->rot = a->f28;
    if (h->tevMode == 2) {
        h->texW = a->f20;
        h->texH = a->f24;
    } else {
        ResourceTable_GetSizeXY(baseId, &h->texW, &h->texH);
    }
    h->posX = a->f2C;
    h->posY = a->f30;
    h->color[0] = ((unsigned int *)a->slots)[0];
    h->color[1] = ((unsigned int *)a->slots)[1];
    h->color[2] = ((unsigned int *)a->slots)[2];
    h->color[3] = ((unsigned int *)a->slots)[3];
    h->flip = 0;
    if (a->f44) {
        h->flip |= 1;
    }
    if (a->f45) {
        h->flip |= 2;
    }
    h->hasUV = 0;
    h->uv[0] = lbl_806D6D8C;
    h->uv[1] = g_glyphClipMinXY;
    h->uv[2] = g_glyphClipMinXY;
    h->uv[3] = g_glyphClipMinXY;
    h->uv[4] = lbl_806D6D8C;
    h->uv[5] = g_glyphClipMinXY;
    if (a->f48 == 1) {
        h->blendType = 1;
        h->blendSrc = a->f4C;
        h->blendDst = a->f50;
    } else {
        h->blendType = 2;
        h->blendOp = a->f54;
    }
    fn_801217E8(h);
    if (h->tevMode != 2) {
        int slot0 = ResourceTable_GetSlotIndex(baseId);
        TEXDescriptor *d0 = TEXGetPaletteEntry(e->palette, slot0);
        float tw = d0->tex->width;
        float th = d0->tex->height;
        ResourceTable_GetOffsetXY(baseId, &h->texUV[0][0], &h->texUV[0][1]);
        float iw = lbl_806D6D8C / tw;
        float ih = lbl_806D6D8C / th;
        h->texUV[0][0] += lbl_806D6D88;
        h->texUV[0][1] += lbl_806D6D88;
        h->texUV[0][0] = iw * h->texUV[0][0];
        h->texUV[0][1] = ih * h->texUV[0][1];
        h->texUV[1][0] = iw * (h->texW - lbl_806D6D8C) + h->texUV[0][0];
        h->texUV[1][1] = ih * (h->texH - lbl_806D6D8C) + h->texUV[0][1];
        if (h->flip & 1) {
            float t = h->texUV[0][0];
            h->texUV[0][0] = h->texUV[1][0];
            h->texUV[1][0] = t;
        }
        if (h->flip & 2) {
            float t = h->texUV[0][1];
            h->texUV[0][1] = h->texUV[1][1];
            h->texUV[1][1] = t;
        }
    }
    if (a->prev == -1) {
        a->prev = ResourceTable_GetChainNextId(baseId);
    }
    h->hasTex2 = 0;
    if (h->tevMode != 2) {
        resId = a->prev;
        if (resId != -1) {
            ResEntry *e2 = FindResEntry(resId);
            if (e2 == 0) {
                PreloadResource(resId);
                e2 = FindResEntry(resId);
            }
            if (e2 != 0) {
                float w2;
                float h2;
                float uv[2][2];
                h->hasTex2 = 1;
                h->resId2 = resId;
                int slot2 = ResourceTable_GetSlotIndex(resId);
                TEXDescriptor *d2 = TEXGetPaletteEntry(e2->palette, slot2);
                h->texObj2 = &e2->data0[slot2];
                if (d2->clut != 0) {
                    h->tlut2 = &e2->data1[slot2];
                } else {
                    h->tlut2 = 0;
                }
                ResourceTable_GetSizeXY(resId, &w2, &h2);
                float tw2 = d2->tex->width;
                float th2 = d2->tex->height;
                ResourceTable_GetOffsetXY(resId, &uv[0][0], &uv[0][1]);
                float iw2 = lbl_806D6D8C / tw2;
                float ih2 = lbl_806D6D8C / th2;
                uv[0][0] += lbl_806D6D88;
                uv[0][1] += lbl_806D6D88;
                uv[0][0] = iw2 * uv[0][0];
                uv[0][1] = ih2 * uv[0][1];
                uv[1][0] = iw2 * (w2 - lbl_806D6D8C) + uv[0][0];
                uv[1][1] = ih2 * (h2 - lbl_806D6D8C) + uv[0][1];
                if (a->f44) {
                    float t = uv[0][0];
                    uv[0][0] = uv[1][0];
                    uv[1][0] = t;
                }
                if (a->f45) {
                    float t = uv[0][1];
                    uv[0][1] = uv[1][1];
                    uv[1][1] = t;
                }
                h->uv2[0] = uv[0][0];
                h->uv2[1] = uv[0][1];
                h->uv2[2] = uv[1][0];
                h->uv2[3] = uv[1][1];
            }
        }
    }
    h->hasCallback = 1;
    if (!c) {
        h->callbackOn = 1;
    } else {
        float maxY;
        float maxX;
        float minX = h->corner[0][0];
        float minY = h->corner[0][1];
        maxX = minX;
        maxY = minY;
        for (int i = 0; i < 4; i++) {
            float x = h->corner[i][0];
            if (x < minX) {
                minX = x;
            }
            if (maxX < x) {
                maxX = x;
            }
            float y = h->corner[i][1];
            if (y < minY) {
                minY = y;
            }
            if (maxY < y) {
                maxY = y;
            }
        }
        h->callbackOn = 1;
        if (g_glyphClipMaxX < minX) {
            h->callbackOn = 0;
        }
        if (maxX < g_glyphClipMinXY) {
            h->callbackOn = 0;
        }
        if (g_glyphClipMaxY < minY) {
            h->callbackOn = 0;
        }
        if (maxY < g_glyphClipMinXY) {
            h->callbackOn = 0;
        }
    }
    h->dirty = 0;
    return MakeHandleId(b, index);
}
#pragma use_lmw_stmw reset
#pragma exceptions reset

extern "C" void fn_801208E0(int id, float *x, float *y) {
    if (!IsValidResourceId(id)) {
        float v = g_glyphClipMinXY;
        *y = v;
        *x = v;
    } else {
        ResourceTable_GetSizeXY(id, x, y);
    }
}

extern "C" void fn_8012094C(void) {
    int i;
    for (i = 0; i < 600; i++) {
        ResEntry *e = &SpriteHandle_bss_806573E8[i];
        if (e->palette != 0 && e->id < 0x2B00) {
            TEXReleasePalette(&e->palette);
        }
        MemoryManager_Free(e->data0);
        MemoryManager_Free(e->data1);
        MemoryManager_Free(e->data2);
        e->id = 0;
        e->prev = -1;
        e->palette = 0;
        e->fC = 0;
        e->data0 = 0;
        e->data1 = 0;
        e->data2 = 0;
        SpriteHandle_bss_8065B588[i] = 0;
    }
}

/*
 * fn_80120A08 is a self-recursive inline: MWCC expands it into itself three
 * levels deep and only calls itself at the fourth. Stub_NoOp_80121c34 (an
 * identity) and fn_8011DC20 (the slot release, strong copy in ResourceSlot.c)
 * are inlines that hit the depth limit in the inner levels, so their weak
 * out-of-line copies are emitted here and folded by the linker.
 * PreloadResource (0x80120D80) is the same pattern.
 * exceptions off: both keep their manual extab entries above, whose address
 * references are also what make MWCC emit the weak functions at all.
 */
#pragma exceptions off
#pragma use_lmw_stmw on
extern "C" inline int Stub_NoOp_80121c34(int x) { return x; }
extern "C" inline void fn_8011DC20(ResEntry *r) {
    if (r->palette != 0 && Stub_NoOp_80121c34(r->id) < 0x2B00) {
        TEXReleasePalette(&r->palette);
    }
    MemoryManager_Free(r->data0);
    MemoryManager_Free(r->data1);
    MemoryManager_Free(r->data2);
    r->id = 0; r->prev = -1; r->palette = 0; r->fC = 0;
    r->data0 = 0; r->data1 = 0; r->data2 = 0;
}
extern "C" inline int fn_80120A08(int id) {
    int a = Stub_NoOp_80121c34(id);
    int n = ResourceTable_GetChainNextId(a);
    if (n != -1) {
        fn_80120A08(n);
    }
    int key = ResourceTable_GetGroupKey(Stub_NoOp_80121c34(a));
    ResEntry *e = SpriteHandle_bss_806573E8;
    for (int i = 0; i < 600; e++, i++) {
        if (key == e->prev) {
            SpriteHandle_bss_8065B588[i]--;
            if (SpriteHandle_bss_8065B588[i] == 0) {
                fn_8011DC20(&SpriteHandle_bss_806573E8[i]);
            }
            return 1;
        }
    }
    return 0;
}

extern "C" inline unsigned char PreloadResource(int id) {
    int a = Stub_NoOp_80121c34(id);
    if (!IsValidResourceId(a)) {
        return 0;
    }
    int n = ResourceTable_GetChainNextId(a);
    if (n != -1) {
        PreloadResource(n);
    }
    int key = ResourceTable_GetGroupKey(a);
    int i;
    for (i = 0; i < 600; i++) {
        if (key == SpriteHandle_bss_806573E8[i].prev) {
            SpriteHandle_bss_8065B588[i]++;
            return 1;
        }
    }
    for (i = 0; i < 600; i++) {
        if (SpriteHandle_bss_806573E8[i].prev == -1) {
            unsigned char ok = ResourceSlot_Load(&SpriteHandle_bss_806573E8[i], id);
            if (ok == 1) {
                SpriteHandle_bss_8065B588[i]++;
            }
            return ok;
        }
    }
    return 0;
}
#pragma use_lmw_stmw reset
#pragma exceptions reset

extern "C" void SpriteHandlePool_GC(void) {
    SpriteNode *n = lbl_806D1500->head;
    while (n != 0) {
        SpriteNode *next = n->next;
        g_SpriteHandlePool[n->index].released = 0;
        SpriteHandle *h = &g_SpriteHandlePool[n->index];
        if (!h->keep) {
            h->active = 0;
            SpriteList *l = lbl_806D1500;
            if (n->prev != 0) {
                n->prev->next = n->next;
            }
            if (n->next != 0) {
                n->next->prev = n->prev;
            }
            if (l->head == n) {
                l->head = n->next;
            }
            if (l->tail == n) {
                l->tail = n->prev;
            }
            n->prev = 0;
            n->next = 0;
            if (l->freeTail != 0) {
                l->freeTail->next = n;
            }
            n->prev = l->freeTail;
            if (l->freeHead == 0) {
                l->freeHead = n;
            }
            l->freeTail = n;
            l->count--;
        }
        n = next;
    }
}

extern "C" void fn_80121210(void) {
    ScopedTimer timer(0xD);
    fn_8012094C();
    SpriteList_Clear(lbl_806D1500);
}

#pragma use_lmw_stmw on
extern "C" void fn_801213EC(void) {
    lbl_806D1500 = new SpriteList(500);
    fn_80121210();
    lbl_806D14FD = 0;
    fn_801F6494();
}
#pragma use_lmw_stmw reset

extern "C" void fn_801217E8(SpriteHandle *s) {
    float sx;
    float sy;
    int i;
    ResourceTable_GetScaleXY(s->resId, &sx, &sy);
    signed char kind = ResourceTable_GetFlagsByte(s->resId);
    s->clipFlags = 0;
    if (s->posX < g_glyphClipMinXY) {
        s->clipFlags |= 1;
    }
    if (s->posY < g_glyphClipMinXY) {
        s->clipFlags |= 2;
    }
    float w = sx * (s->texW * (float)__fabs(s->posX));
    float h = sy * (s->texH * (float)__fabs(s->posY));
    float cs = LUT_Cosine(s->rot);
    float sn = LUT_Sine(s->rot);
    if (kind == 9) {
        float c9[4][2] = { { -0.5f, 0.5f }, { -0.5f, -0.5f }, { 0.5f, -0.5f }, { 0.5f, 0.5f } };
        for (i = 0; i < 4; i++) {
            s->corner[i][0] = sn * (w * c9[i][0]) - cs * (h * c9[i][1]);
            s->corner[i][1] = cs * (w * c9[i][0]) + sn * (h * c9[i][1]);
            if (s->posMode_026 == 1) {
                s->corner[i][0] += s->sizeX;
                s->corner[i][1] += s->sizeY;
            } else {
                s->corner[i][0] += s->texW * lbl_806D6D88 + s->sizeX;
                s->corner[i][1] += s->texH * lbl_806D6D88 + s->sizeY;
            }
        }
    } else if (s->hasUV) {
        float cm[4][2] = { { -0.5f, 0.5f }, { -0.5f, -0.5f }, { 0.5f, -0.5f }, { 0.5f, 0.5f } };
        for (i = 0; i < 4; i++) {
            float xx = w * cm[i][0];
            float yy = h * cm[i][1];
            s->corner[i][0] = xx * s->uv[0] + yy * s->uv[1] + s->uv[2];
            s->corner[i][1] = xx * s->uv[3] + yy * s->uv[4] + s->uv[5];
        }
    } else {
        float cb[4][2] = { { 0.0f, 1.0f }, { 0.0f, 0.0f }, { 1.0f, 0.0f }, { 1.0f, 1.0f } };
        float off[9][2] = {
            { 0.0f, 0.0f }, { -0.5f, 0.0f }, { -1.0f, 0.0f },
            { 0.0f, -0.5f }, { -0.5f, -0.5f }, { -1.0f, -0.5f },
            { 0.0f, -1.0f }, { -0.5f, -1.0f }, { -1.0f, -1.0f },
        };
        float *o = off[kind];
        for (i = 0; i < 4; i++) {
            float xx = w * cb[i][0];
            float yy = h * cb[i][1];
            xx += w * o[0];
            yy += h * o[1];
            s->corner[i][0] = xx * sn - yy * cs;
            s->corner[i][1] = xx * cs + yy * sn;
            s->corner[i][0] += s->sizeX;
            s->corner[i][1] += s->sizeY;
        }
    }
}


static inline void SortPair(float &a, float &b) {
    if (a > b) {
        float t = a;
        a = b;
        b = t;
    }
}

extern "C" unsigned char fn_80121C38(ResCtrl *r) {
    int id;
    float sx;
    float sy;
    float w;
    float h;
    float minX;
    float maxX;
    float minY;
    float maxY;
    float c;
    float sn;
    float hh;
    float hw;
    float ex;
    float ey;
    float x;
    float y;

    id = 0x1B8C;
    if (r->f8 != 2) {
        id = r->id;
    }
    sx = r->f2C;
    sy = r->f30;
    w = r->f20;
    h = r->f24;
    if (r->id != 2) {
        ResourceTable_GetSizeXY(id, &w, &h);
    }
    x = r->f14;
    y = r->f18;
    minX = x;
    maxX = x;
    minY = y;
    maxY = y;
    c = LUT_Cosine(r->f28);
    sn = LUT_Sine(r->f28);
    hw = w * sx;
    hh = h * sy;
    ex = 0.5f * (sn * hw - c * hh);
    ey = 0.5f * (c * hw + sn * hh);
    if (!r->f10) {
        minX += 0.5f * hw;
        minY += 0.5f * hh;
        maxX += 0.5f * hw;
        maxY += 0.5f * hh;
    }
    minX -= ex;
    maxX += ex;
    minY -= ey;
    maxY += ey;
    SortPair(minX, maxX);
    SortPair(minY, maxY);
    if (minX >= g_glyphClipMaxX || maxX < g_glyphClipMinXY) {
        return 0;
    }
    if (minY >= g_glyphClipMaxY || maxY < g_glyphClipMinXY) {
        return 0;
    }
    return 1;
}

extern "C" void fn_80121E10(ResCtrl *r) {
    ResCtrl_Reset(r);
}

extern "C" ResCtrl *ResCtrl_Init(ResCtrl *r) {
    ResCtrl_Reset(r);
    return r;
}

extern "C" void *fn_80121F54(void *self, short flag) {
    if (self != 0) {
        __destroy_arr(self, (void *)fn_80121FB4, 0xC, 0x10);
        if (flag > 0) {
            MemoryManager_TimedFree(self);
        }
    }
    return self;
}

extern "C" LList *fn_80121FB4(LList *l, short flag) {
    if (l != 0) {
        l->~LList();
        if (flag > 0) {
            MemoryManager_TimedFree(l);
        }
    }
    return l;
}

extern "C" ProfTimer *dtor_80122068(ProfTimer *t, short flag) {
    if (t != 0) {
        lbl_80657208[t->slot] += (float)(((OSGetTick() - t->start) * 8) /
            ((*(unsigned int *)0x800000F8 / 4) / 125000)) / lbl_806D6D9C;
        if (flag > 0) {
            MemoryManager_TimedFree(t);
        }
    }
    return t;
}

extern "C" void *dtor_80122120(void *self, short flag) {
    if (self != 0) {
        if (flag > 0) {
            MemoryManager_TimedFree(self);
        }
    }
    return self;
}

#include "game/types/LIter.h"

extern "C" void fn_8012215C(LIter *ret, LListImp *l, LIter *it) {
    LNode *p = it->n;
    LNode *next = p->next;
    LNode *prev = p->prev;
    it->n = next;
    prev->next = next;
    p->next->prev = p->prev;
    MemoryManager_TimedFree(p);
    LNode *r = it->n;
    int c = l->count;
    l->count = --c;
    ret->n = r;
}

extern "C" LListImp *fn_801221D4(LListImp *l) {
    DoublyLinkedList_Init(l);
    return l;
}

extern "C" void fn_80122204(void) {
    __destroy_arr(SpriteHandle_bss_80657234, (void *)fn_8012223C, 0xC, 8);
}

extern "C" LList *fn_8012223C(LList *l, short flag) {
    if (l != 0) {
        l->~LList();
        if (flag > 0) {
            MemoryManager_TimedFree(l);
        }
    }
    return l;
}

extern "C" LListImp *fn_801222F0(LListImp *l) {
    fn_80122320(l);
    return l;
}

extern "C" void fn_80122320(LListImp *l) {
    LNode *e;
    l->count = 0;
    e = &l->end;
    e->next = e;
    e->prev = e;
}

/* __sinit for this unit's static lists: LList[8] (SpriteHandle_bss_80657234), the 16-list
 * holder (lbl_806572A0) and the 600 resource slots (SpriteHandle_bss_806573E8), with their
 * destructor-chain records. Written out by hand like the other generated
 * helpers here (fn_80122204, fn_80121F54). */
extern "C" void fn_80122338(void) {
    __construct_array(SpriteHandle_bss_80657234, (void *)fn_801222F0, (void *)fn_8012223C, 0xC, 8);
    __register_global_object(0, (void *)fn_80122204, SpriteHandle_bss_80657228);
    __construct_array(lbl_806572A0, (void *)fn_801221D4, (void *)fn_80121FB4, 0xC, 0x10);
    __register_global_object(lbl_806572A0, (void *)fn_80121F54, lbl_80657294);
    __construct_array(SpriteHandle_bss_806573E8, (void *)fn_8011DF70, 0, 0x1C, 0x258);
}

__declspec(section ".ctors") static void *const fn_80122338_ctor_ref = (void *)fn_80122338;
