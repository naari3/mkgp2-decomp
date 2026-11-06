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


struct TEXHeader {
    unsigned short height;
    unsigned short width;
};

struct TEXDescriptor {
    TEXHeader *tex;
    void *clut;
};

struct SavedGXState {
    int cullMode;
    float proj[7];
    float viewport[6];
    unsigned int scissor[4];
};
extern "C" void MemoryManager_TimedFree(void *p);

struct Vec3 {
    float x;
    float y;
    float z;
};

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

struct SpriteNode {
    int index;
    SpriteNode *prev;
    SpriteNode *next;
};
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


struct SpriteHandle {
    signed char active;
    char pad1[3];
    int type;
    int next;
    unsigned char keep;
    unsigned char released;
    char padE[2];
    int resId;
    void *texObj;
    void *tlut;
    unsigned char texFmt;
    char pad1D[3];
    int baseResId;
    signed char tevMode;
    char pad25[3];
    float sizeX;
    float sizeY;
    char pad30[4];
    float rot;
    float texW;
    float texH;
    float posX;
    float posY;
    char pad48;
    unsigned char hasUV;
    char pad4A[2];
    float uv[6];
    unsigned int color[4];
    unsigned char flip;
    char pad75[0x88 - 0x75];
    float corner[4][2];
    float texUV[2][2];
    unsigned char hasTex2;
    char padB9[3];
    int resId2;
    void *texObj2;
    void *tlut2;
    float uv2[4];
    unsigned char activeFlag;
    unsigned char visible;
    signed char dirty;
    char padDB[0xE4 - 0xDB];
};


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
extern SavedGXState lbl_806573A0;
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
extern float g_glyphClipMinXY;
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
extern unsigned int lbl_80657360[];
extern SpriteHandle g_SpriteHandlePool[];
unsigned char IsValidResourceId(int id);
int ResourceTable_GetChainNextId(int id);
int ResourceTable_GetGroupKey(int id);
void ResourceTable_GetOffsetXY(int id, float *x, float *y);
void ResourceTable_GetSizeXY(int id, float *x, float *y);
int ResourceTable_GetSlotIndex(int id);
TEXDescriptor *TEXGetPaletteEntry(void *pal, unsigned int idx);
extern unsigned int lbl_806D6D88;
extern unsigned int lbl_806D6D90;
extern ResEntry lbl_806573E8[600];
unsigned int OSGetTick(void);
void Profiler_RecordFrame(int slot, float value);
extern SpriteList *lbl_806D1500;
extern const float lbl_806D6D98;
extern const float lbl_806D6D9C;
extern float lbl_80657208[];
extern void __dt__11ScopedTimerFv();
void MemoryManager_Free(void *p);
void TEXReleasePalette(void **pal);
extern int lbl_8065B588[600];
extern void fn_8011DC20();
extern void ResourceSlot_Load();
extern void Alloc();
extern void FUN_8003b120();
void MemoryManager_TimedFree(void *p);
void fn_801F6494(void);
extern unsigned char lbl_806D14FD;
extern void LUT_Cosine();
extern void LUT_Sine();
extern void ResourceTable_GetFlagsByte();
extern void ResourceTable_GetScaleXY();
extern unsigned int lbl_80332528[];
void *memset(void *p, int c, unsigned long n);
void __destroy_arr(void *, void *, unsigned long, unsigned long);
void DoublyLinkedList_Init(void *);
extern unsigned int lbl_80657234[];
void __construct_array(void *, void *, void *, unsigned long, unsigned long);
void *__register_global_object(void *, void *, void *);
extern unsigned int fn_8011DF70[];
extern unsigned int lbl_80657228[];
void fn_8011EB1C(void);
void fn_8011EC18(unsigned char a);
void SpriteHandle_RecomputeCull(int h);
void SpriteLayer_SetResource(int h, int id);
void fn_8011F870(unsigned int mask);
void fn_8011F994(int type);
asm int SpriteHandle_CreateEx(int a, int b, int c);
void fn_8012094C(void);
asm void fn_80120A08(void);
asm unsigned char PreloadResource(int id);
void SpriteHandlePool_GC(void);
void fn_80121210(void);
void fn_801213EC(void);
asm void fn_801217E8(SpriteHandle *s);
void Stub_NoOp_80121c34(void);
asm void fn_80121C38(void);
void fn_80121E10(ResCtrl *r);
ResCtrl *ResCtrl_Init(ResCtrl *r);
void *fn_80121F54(void *self, short flag);
LList *fn_80121FB4(LList *l, short flag);
ProfTimer *dtor_80122068(ProfTimer *t, short flag);
asm void fn_8012215C(void);
LListImp *fn_801221D4(LListImp *l);
void fn_80122204(void);
LList *fn_8012223C(LList *l, short flag);
LListImp *fn_801222F0(LListImp *l);
void fn_80122320(LListImp *l);
asm void fn_80122338(void);

#pragma section R ".extab_user"











__declspec(section ".extab_user") static const struct { unsigned int f0; unsigned int f1; unsigned int f2; unsigned int f3; unsigned int f4; unsigned int f5; unsigned int f6; unsigned int f7; unsigned int f8; unsigned int f9; unsigned int f10; unsigned int f11; unsigned int f12; unsigned int f13; unsigned int f14; unsigned int f15; unsigned int f16; unsigned int f17; unsigned int f18; unsigned int f19; unsigned int f20; unsigned int f21; unsigned int f22; void *f23; unsigned int f24; void *f25; } extab_SpriteHandle_CreateEx = { 0x488A0000, 0x00000048, 0x001C0060, 0x00000138, 0x00150060, 0x00000210, 0x00000058, 0x0000021C, 0x00150060, 0x0000030C, 0x00000058, 0x00000318, 0x00150060, 0x000003E8, 0x00190058, 0x00000458, 0x00150060, 0x00000528, 0x01600058, 0x00000CCC, 0x00150060, 0x00000000, 0x02000010, (void *)&__dt__11ScopedTimerFv, 0x82000018, (void *)&dtor_80122068 };



__declspec(section ".extab_user") static const unsigned char extab_fn_80120A08[8] = {
    0x28, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

__declspec(section ".extab_user") static const unsigned char extab_PreloadResource[8] = {
    0x28, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

__declspec(section ".extab_user") static const struct { unsigned int f0; unsigned int f1; unsigned int f2; unsigned int f3; unsigned int f4; void *f5; } extab_fn_80121210 = { 0x180A0000, 0x0000005C, 0x00060010, 0x00000000, 0x82000008, (void *)&__dt__11ScopedTimerFv };


__declspec(section ".extab_user") static const unsigned char extab_fn_801217E8[8] = {
    0x18, 0xCA, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

__declspec(section ".extab_user") static const unsigned char extab_fn_80121C38[8] = {
    0x09, 0xCA, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};







__declspec(section ".extab_user") static const unsigned char extab_fn_8012215C[8] = {
    0x18, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};





__declspec(section ".extab_user") static const unsigned char extab_fn_80122338[8] = {
    0x08, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

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



__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_fn_801217E8 = {
    (void *)&fn_801217E8, 0x0000044C, (void *)extab_fn_801217E8
};

__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_fn_80121C38 = {
    (void *)&fn_80121C38, 0x000001D8, (void *)extab_fn_80121C38
};







__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_fn_8012215C = {
    (void *)&fn_8012215C, 0x00000078, (void *)extab_fn_8012215C
};





__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_fn_80122338 = {
    (void *)&fn_80122338, 0x000000B0, (void *)extab_fn_80122338
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
    GXSetScissor(lbl_806573A0.scissor[0], lbl_806573A0.scissor[1], lbl_806573A0.scissor[2], lbl_806573A0.scissor[3]);
    GXSetViewport(lbl_806573A0.viewport[0], lbl_806573A0.viewport[1], lbl_806573A0.viewport[2], lbl_806573A0.viewport[3], lbl_806573A0.viewport[4], lbl_806573A0.viewport[5]);
    GXSetProjectionv(lbl_806573A0.proj);
    GXSetCullMode(lbl_806573A0.cullMode);
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
    GXGetCullMode(&lbl_806573A0.cullMode);
    GXGetProjectionv(lbl_806573A0.proj);
    GXGetViewportv(lbl_806573A0.viewport);
    GXGetScissor(&lbl_806573A0.scissor[0], &lbl_806573A0.scissor[1], &lbl_806573A0.scissor[2], &lbl_806573A0.scissor[3]);
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
        lbl_80657360[i] = 0;
    }
    lbl_806D14F4 = 0;
    lbl_806D14F8 = 0;
    lbl_806D14FC = 0;
    lbl_80657360[15] = 0;
}

extern "C" void SpriteHandle_Destroy(int h) {
    if (h != 0) {
        SpriteHandle *s = GetHandle(h);
        s->keep = 0;
        s->activeFlag = 0;
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
            s->visible = 1;
            if (g_glyphClipMaxX < minX) {
                s->visible = 0;
            }
            if (maxX < g_glyphClipMinXY) {
                s->visible = 0;
            }
            if (g_glyphClipMaxY < minY) {
                s->visible = 0;
            }
            if (maxY < g_glyphClipMinXY) {
                s->visible = 0;
            }
            s->dirty = 0;
        }
    }
}

extern "C" void SpriteHandle_SetActiveFlag(int h, unsigned char on) {
    if (h != 0) {
        GetHandle(h)->activeFlag = on;
    }
}

static inline ResEntry *FindResEntry(int id) {
    int key = ResourceTable_GetGroupKey(id);
    int i;
    for (i = 0; i < 600; i++) {
        if (key == lbl_806573E8[i].prev) {
            return &lbl_806573E8[i];
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
    GXSetScissor(lbl_806573A0.scissor[0], lbl_806573A0.scissor[1], lbl_806573A0.scissor[2], lbl_806573A0.scissor[3]);
    GXSetViewport(lbl_806573A0.viewport[0], lbl_806573A0.viewport[1], lbl_806573A0.viewport[2], lbl_806573A0.viewport[3], lbl_806573A0.viewport[4], lbl_806573A0.viewport[5]);
    GXSetProjectionv(lbl_806573A0.proj);
    GXSetCullMode(lbl_806573A0.cullMode);
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
    GXSetScissor(lbl_806573A0.scissor[0], lbl_806573A0.scissor[1], lbl_806573A0.scissor[2], lbl_806573A0.scissor[3]);
    GXSetViewport(lbl_806573A0.viewport[0], lbl_806573A0.viewport[1], lbl_806573A0.viewport[2], lbl_806573A0.viewport[3], lbl_806573A0.viewport[4], lbl_806573A0.viewport[5]);
    GXSetProjectionv(lbl_806573A0.proj);
    GXSetCullMode(lbl_806573A0.cullMode);
    HSD_StateInvalidate(-1);
}

extern "C" void fn_8011FA98(void) {
    fn_8011EB1C();
}

extern "C" void fn_8011FAB8(void) {
    fn_8011EB1C();
}

extern "C" int SpriteHandle_CreateDefault(int a, int b) {
    return SpriteHandle_CreateEx(a, b, 1);
}

extern "C" unsigned char fn_8011FAFC(int a, int b) {
    return SpriteHandle_CreateEx(a, b, 0) != 0;
}

extern "C" asm int SpriteHandle_CreateEx(int a, int b, int c) { /* 0x8011FB2C size:0xDB4 */
    nofralloc
    stwu r1, -0x90(r1)
    mflr r0
    stw r0, 0x94(r1)
    stfd f31, 0x80(r1)
    psq_st f31, 0x88(r1), 0, 0
    stfd f30, 0x70(r1)
    psq_st f30, 0x78(r1), 0, 0
    stmw r23, 0x4c(r1)
    li r0, 0x0
    mr r23, r3
    stw r0, 0x18(r1)
    mr r24, r4
    mr r25, r5
    bl OSGetTick
    li r0, 0xd
    stw r3, 0x1c(r1)
    stw r0, 0x14(r1)
    bl OSGetTick
    lwz r4, lbl_806D1500(r13)
    stw r3, 0x10(r1)
    lwz r3, 0x4(r4)
    lwz r0, 0x0(r4)
    cmpw r3, r0
    blt SpriteHandle_CreateEx_L_8011FC58
    bl OSGetTick
    lis r5, 0x8000
    lis r4, 0x431c
    lwz r5, 0xf8(r5)
    lis r0, 0x4330
    subi r6, r4, 0x217d
    lwz r7, 0x10(r1)
    srwi r4, r5, 2
    stw r0, 0x30(r1)
    mulhwu r0, r6, r4
    subf r3, r7, r3
    lfd f2, lbl_806D6D90(r2)
    slwi r4, r3, 3
    lfs f0, lbl_806D6D98(r2)
    lwz r3, 0x14(r1)
    srwi r0, r0, 15
    divwu r0, r4, r0
    stw r0, 0x34(r1)
    lfd f1, 0x30(r1)
    fsubs f1, f1, f2
    fdivs f1, f1, f0
    bl Profiler_RecordFrame
    bl OSGetTick
    lis r4, 0x8000
    lis r6, 0x431c
    lwz r0, 0xf8(r4)
    lis r5, 0x4330
    lwz r7, 0x1c(r1)
    lis r4, lbl_80657208@ha
    srwi r0, r0, 2
    subi r6, r6, 0x217d
    mulhwu r6, r6, r0
    subf r3, r7, r3
    lwz r0, 0x18(r1)
    addi r4, r4, lbl_80657208@l
    slwi r7, r3, 3
    stw r5, 0x38(r1)
    srwi r3, r6, 15
    slwi r0, r0, 2
    divwu r5, r7, r3
    lfd f3, lbl_806D6D90(r2)
    lfs f1, lbl_806D6D9C(r2)
    li r3, 0x0
    lfsx f0, r4, r0
    stw r5, 0x3c(r1)
    lfd f2, 0x38(r1)
    fsubs f2, f2, f3
    fdivs f1, f2, f1
    fadds f0, f0, f1
    stfsx f0, r4, r0
    b SpriteHandle_CreateEx_L_801208BC
    SpriteHandle_CreateEx_L_8011FC58:
    cmplwi r23, 0x0
    bne SpriteHandle_CreateEx_L_8011FD2C
    bl OSGetTick
    lis r5, 0x8000
    lis r4, 0x431c
    lwz r5, 0xf8(r5)
    lis r0, 0x4330
    subi r6, r4, 0x217d
    lwz r7, 0x10(r1)
    srwi r4, r5, 2
    stw r0, 0x38(r1)
    mulhwu r0, r6, r4
    subf r3, r7, r3
    lfd f2, lbl_806D6D90(r2)
    slwi r4, r3, 3
    lfs f0, lbl_806D6D98(r2)
    lwz r3, 0x14(r1)
    srwi r0, r0, 15
    divwu r0, r4, r0
    stw r0, 0x3c(r1)
    lfd f1, 0x38(r1)
    fsubs f1, f1, f2
    fdivs f1, f1, f0
    bl Profiler_RecordFrame
    bl OSGetTick
    lis r4, 0x8000
    lis r6, 0x431c
    lwz r0, 0xf8(r4)
    lis r5, 0x4330
    lwz r7, 0x1c(r1)
    lis r4, lbl_80657208@ha
    srwi r0, r0, 2
    subi r6, r6, 0x217d
    mulhwu r6, r6, r0
    subf r3, r7, r3
    lwz r0, 0x18(r1)
    addi r4, r4, lbl_80657208@l
    slwi r7, r3, 3
    stw r5, 0x30(r1)
    srwi r3, r6, 15
    slwi r0, r0, 2
    divwu r5, r7, r3
    lfd f3, lbl_806D6D90(r2)
    lfs f1, lbl_806D6D9C(r2)
    li r3, 0x0
    lfsx f0, r4, r0
    stw r5, 0x34(r1)
    lfd f2, 0x30(r1)
    fsubs f2, f2, f3
    fdivs f1, f2, f1
    fadds f0, f0, f1
    stfsx f0, r4, r0
    b SpriteHandle_CreateEx_L_801208BC
    SpriteHandle_CreateEx_L_8011FD2C:
    clrlwi. r0, r25, 24
    bne SpriteHandle_CreateEx_L_8011FE10
    mr r3, r23
    bl fn_80121C38
    clrlwi. r0, r3, 24
    bne SpriteHandle_CreateEx_L_8011FE10
    bl OSGetTick
    lis r5, 0x8000
    lis r4, 0x431c
    lwz r5, 0xf8(r5)
    lis r0, 0x4330
    subi r6, r4, 0x217d
    lwz r7, 0x10(r1)
    srwi r4, r5, 2
    stw r0, 0x38(r1)
    mulhwu r0, r6, r4
    subf r3, r7, r3
    lfd f2, lbl_806D6D90(r2)
    slwi r4, r3, 3
    lfs f0, lbl_806D6D98(r2)
    lwz r3, 0x14(r1)
    srwi r0, r0, 15
    divwu r0, r4, r0
    stw r0, 0x3c(r1)
    lfd f1, 0x38(r1)
    fsubs f1, f1, f2
    fdivs f1, f1, f0
    bl Profiler_RecordFrame
    bl OSGetTick
    lis r4, 0x8000
    lis r6, 0x431c
    lwz r0, 0xf8(r4)
    lis r5, 0x4330
    lwz r7, 0x1c(r1)
    lis r4, lbl_80657208@ha
    srwi r0, r0, 2
    subi r6, r6, 0x217d
    mulhwu r6, r6, r0
    subf r3, r7, r3
    lwz r0, 0x18(r1)
    addi r4, r4, lbl_80657208@l
    slwi r7, r3, 3
    stw r5, 0x30(r1)
    srwi r3, r6, 15
    slwi r0, r0, 2
    divwu r5, r7, r3
    lfd f3, lbl_806D6D90(r2)
    lfs f1, lbl_806D6D9C(r2)
    li r3, 0x0
    lfsx f0, r4, r0
    stw r5, 0x34(r1)
    lfd f2, 0x30(r1)
    fsubs f2, f2, f3
    fdivs f1, f2, f1
    fadds f0, f0, f1
    stfsx f0, r4, r0
    b SpriteHandle_CreateEx_L_801208BC
    SpriteHandle_CreateEx_L_8011FE10:
    lwz r0, 0x8(r23)
    lwz r3, 0x0(r23)
    cmpwi r0, 0x2
    mr r30, r3
    mr r29, r3
    bne SpriteHandle_CreateEx_L_8011FE30
    li r30, 0x1b8c
    li r29, 0x1b8c
    SpriteHandle_CreateEx_L_8011FE30:
    mr r3, r29
    bl IsValidResourceId
    clrlwi. r0, r3, 24
    bne SpriteHandle_CreateEx_L_8011FF0C
    bl OSGetTick
    lis r5, 0x8000
    lis r4, 0x431c
    lwz r5, 0xf8(r5)
    lis r0, 0x4330
    subi r6, r4, 0x217d
    lwz r7, 0x10(r1)
    srwi r4, r5, 2
    stw r0, 0x38(r1)
    mulhwu r0, r6, r4
    subf r3, r7, r3
    lfd f2, lbl_806D6D90(r2)
    slwi r4, r3, 3
    lfs f0, lbl_806D6D98(r2)
    lwz r3, 0x14(r1)
    srwi r0, r0, 15
    divwu r0, r4, r0
    stw r0, 0x3c(r1)
    lfd f1, 0x38(r1)
    fsubs f1, f1, f2
    fdivs f1, f1, f0
    bl Profiler_RecordFrame
    bl OSGetTick
    lis r4, 0x8000
    lis r6, 0x431c
    lwz r0, 0xf8(r4)
    lis r5, 0x4330
    lwz r7, 0x1c(r1)
    lis r4, lbl_80657208@ha
    srwi r0, r0, 2
    subi r6, r6, 0x217d
    mulhwu r6, r6, r0
    subf r3, r7, r3
    lwz r0, 0x18(r1)
    addi r4, r4, lbl_80657208@l
    slwi r7, r3, 3
    stw r5, 0x30(r1)
    srwi r3, r6, 15
    slwi r0, r0, 2
    divwu r5, r7, r3
    lfd f3, lbl_806D6D90(r2)
    lfs f1, lbl_806D6D9C(r2)
    li r3, 0x0
    lfsx f0, r4, r0
    stw r5, 0x34(r1)
    lfd f2, 0x30(r1)
    fsubs f2, f2, f3
    fdivs f1, f2, f1
    fadds f0, f0, f1
    stfsx f0, r4, r0
    b SpriteHandle_CreateEx_L_801208BC
    SpriteHandle_CreateEx_L_8011FF0C:
    mr r3, r29
    bl ResourceTable_GetGroupKey
    mr r3, r30
    bl ResourceTable_GetGroupKey
    lis r4, lbl_806573E8@ha
    li r0, 0x258
    addi r31, r4, lbl_806573E8@l
    li r4, 0x0
    mr r5, r31
    mtctr r0
    SpriteHandle_CreateEx_L_8011FF34:
    lwz r0, 0x4(r5)
    cmpw r3, r0
    bne SpriteHandle_CreateEx_L_8011FF54
    mulli r4, r4, 0x1c
    lis r3, lbl_806573E8@ha
    addi r0, r3, lbl_806573E8@l
    add r0, r0, r4
    b SpriteHandle_CreateEx_L_8011FF64
    SpriteHandle_CreateEx_L_8011FF54:
    addi r5, r5, 0x1c
    addi r4, r4, 0x1
    bdnz SpriteHandle_CreateEx_L_8011FF34
    li r0, 0x0
    SpriteHandle_CreateEx_L_8011FF64:
    cmplwi r0, 0x0
    mr r28, r0
    bne SpriteHandle_CreateEx_L_80120098
    mr r3, r30
    bl PreloadResource
    clrlwi. r0, r3, 24
    bne SpriteHandle_CreateEx_L_8012004C
    bl OSGetTick
    lis r5, 0x8000
    lis r4, 0x431c
    lwz r5, 0xf8(r5)
    lis r0, 0x4330
    subi r6, r4, 0x217d
    lwz r7, 0x10(r1)
    srwi r4, r5, 2
    stw r0, 0x38(r1)
    mulhwu r0, r6, r4
    subf r3, r7, r3
    lfd f2, lbl_806D6D90(r2)
    slwi r4, r3, 3
    lfs f0, lbl_806D6D98(r2)
    lwz r3, 0x14(r1)
    srwi r0, r0, 15
    divwu r0, r4, r0
    stw r0, 0x3c(r1)
    lfd f1, 0x38(r1)
    fsubs f1, f1, f2
    fdivs f1, f1, f0
    bl Profiler_RecordFrame
    bl OSGetTick
    lis r4, 0x8000
    lis r6, 0x431c
    lwz r0, 0xf8(r4)
    lis r5, 0x4330
    lwz r7, 0x1c(r1)
    lis r4, lbl_80657208@ha
    srwi r0, r0, 2
    subi r6, r6, 0x217d
    mulhwu r6, r6, r0
    subf r3, r7, r3
    lwz r0, 0x18(r1)
    addi r4, r4, lbl_80657208@l
    slwi r7, r3, 3
    stw r5, 0x30(r1)
    srwi r3, r6, 15
    slwi r0, r0, 2
    divwu r5, r7, r3
    lfd f3, lbl_806D6D90(r2)
    lfs f1, lbl_806D6D9C(r2)
    li r3, 0x0
    lfsx f0, r4, r0
    stw r5, 0x34(r1)
    lfd f2, 0x30(r1)
    fsubs f2, f2, f3
    fdivs f1, f2, f1
    fadds f0, f0, f1
    stfsx f0, r4, r0
    b SpriteHandle_CreateEx_L_801208BC
    SpriteHandle_CreateEx_L_8012004C:
    mr r3, r30
    bl ResourceTable_GetGroupKey
    li r0, 0x258
    mr r5, r31
    li r4, 0x0
    mtctr r0
    SpriteHandle_CreateEx_L_80120064:
    lwz r0, 0x4(r5)
    cmpw r3, r0
    bne SpriteHandle_CreateEx_L_80120084
    mulli r4, r4, 0x1c
    lis r3, lbl_806573E8@ha
    addi r0, r3, lbl_806573E8@l
    add r0, r0, r4
    b SpriteHandle_CreateEx_L_80120094
    SpriteHandle_CreateEx_L_80120084:
    addi r5, r5, 0x1c
    addi r4, r4, 0x1
    bdnz SpriteHandle_CreateEx_L_80120064
    li r0, 0x0
    SpriteHandle_CreateEx_L_80120094:
    mr r28, r0
    SpriteHandle_CreateEx_L_80120098:
    lwz r5, lbl_806D1500(r13)
    lwz r3, 0x0(r5)
    lwz r0, 0x4(r5)
    cmpw r3, r0
    bgt SpriteHandle_CreateEx_L_801200B4
    li r4, 0x0
    b SpriteHandle_CreateEx_L_8012014C
    SpriteHandle_CreateEx_L_801200B4:
    lwz r4, 0xc(r5)
    lwz r3, 0x4(r4)
    cmplwi r3, 0x0
    beq SpriteHandle_CreateEx_L_801200CC
    lwz r0, 0x8(r4)
    stw r0, 0x8(r3)
    SpriteHandle_CreateEx_L_801200CC:
    lwz r3, 0x8(r4)
    cmplwi r3, 0x0
    beq SpriteHandle_CreateEx_L_801200E0
    lwz r0, 0x4(r4)
    stw r0, 0x4(r3)
    SpriteHandle_CreateEx_L_801200E0:
    lwz r0, 0xc(r5)
    cmplw r0, r4
    bne SpriteHandle_CreateEx_L_801200F4
    lwz r0, 0x8(r4)
    stw r0, 0xc(r5)
    SpriteHandle_CreateEx_L_801200F4:
    lwz r0, 0x10(r5)
    cmplw r0, r4
    bne SpriteHandle_CreateEx_L_80120108
    lwz r0, 0x4(r4)
    stw r0, 0x10(r5)
    SpriteHandle_CreateEx_L_80120108:
    li r0, 0x0
    stw r0, 0x4(r4)
    stw r0, 0x8(r4)
    lwz r3, 0x18(r5)
    cmplwi r3, 0x0
    beq SpriteHandle_CreateEx_L_80120124
    stw r4, 0x8(r3)
    SpriteHandle_CreateEx_L_80120124:
    lwz r0, 0x18(r5)
    stw r0, 0x4(r4)
    lwz r0, 0x14(r5)
    cmplwi r0, 0x0
    bne SpriteHandle_CreateEx_L_8012013C
    stw r4, 0x14(r5)
    SpriteHandle_CreateEx_L_8012013C:
    stw r4, 0x18(r5)
    lwz r3, 0x4(r5)
    addi r0, r3, 0x1
    stw r0, 0x4(r5)
    SpriteHandle_CreateEx_L_8012014C:
    lwz r27, 0x0(r4)
    lis r3, g_SpriteHandlePool@ha
    addi r6, r3, g_SpriteHandlePool@l
    li r5, 0x1
    mulli r7, r27, 0xe4
    li r4, -0x1
    li r0, 0x0
    mr r3, r29
    add r26, r6, r7
    stb r5, 0x0(r26)
    stw r24, 0x4(r26)
    stw r4, 0x8(r26)
    stb r25, 0xc(r26)
    stw r0, 0xdc(r26)
    stw r0, 0xe0(r26)
    stw r29, 0x20(r26)
    stw r30, 0x10(r26)
    bl ResourceTable_GetSlotIndex
    mr r0, r3
    lwz r3, 0x8(r28)
    mr r30, r0
    mr r4, r30
    bl TEXGetPaletteEntry
    lwz r4, 0x10(r28)
    slwi r0, r30, 5
    add r0, r4, r0
    stw r0, 0x14(r26)
    lwz r0, 0x4(r3)
    cmplwi r0, 0x0
    beq SpriteHandle_CreateEx_L_801201D8
    mulli r0, r30, 0xc
    lwz r3, 0x14(r28)
    add r0, r3, r0
    stw r0, 0x18(r26)
    b SpriteHandle_CreateEx_L_801201E0
    SpriteHandle_CreateEx_L_801201D8:
    li r0, 0x0
    stw r0, 0x18(r26)
    SpriteHandle_CreateEx_L_801201E0:
    lwz r3, 0x18(r28)
    lbzx r0, r3, r30
    stb r0, 0x1c(r26)
    lwz r0, 0x8(r23)
    stb r0, 0x24(r26)
    lwz r3, 0xc(r23)
    neg r0, r3
    or r0, r0, r3
    srwi r0, r0, 31
    stb r0, 0x25(r26)
    lbz r0, 0x10(r23)
    stb r0, 0x26(r26)
    lfs f0, 0x14(r23)
    stfs f0, 0x28(r26)
    lfs f0, 0x18(r23)
    stfs f0, 0x2c(r26)
    lfs f0, 0x1c(r23)
    stfs f0, 0x30(r26)
    lfs f0, 0x28(r23)
    stfs f0, 0x34(r26)
    lbz r0, 0x24(r26)
    cmpwi r0, 0x2
    bne SpriteHandle_CreateEx_L_80120250
    lfs f0, 0x20(r23)
    stfs f0, 0x38(r26)
    lfs f0, 0x24(r23)
    stfs f0, 0x3c(r26)
    b SpriteHandle_CreateEx_L_80120260
    SpriteHandle_CreateEx_L_80120250:
    mr r3, r29
    addi r4, r26, 0x38
    addi r5, r26, 0x3c
    bl ResourceTable_GetSizeXY
    SpriteHandle_CreateEx_L_80120260:
    lfs f0, 0x2c(r23)
    li r0, 0x0
    stfs f0, 0x40(r26)
    lfs f0, 0x30(r23)
    stfs f0, 0x44(r26)
    lwz r3, 0x34(r23)
    stw r3, 0x64(r26)
    lwz r3, 0x38(r23)
    stw r3, 0x68(r26)
    lwz r3, 0x3c(r23)
    stw r3, 0x6c(r26)
    lwz r3, 0x40(r23)
    stw r3, 0x70(r26)
    stb r0, 0x74(r26)
    lbz r0, 0x44(r23)
    cmplwi r0, 0x0
    beq SpriteHandle_CreateEx_L_801202B0
    lbz r0, 0x74(r26)
    ori r0, r0, 0x1
    stb r0, 0x74(r26)
    SpriteHandle_CreateEx_L_801202B0:
    lbz r0, 0x45(r23)
    cmplwi r0, 0x0
    beq SpriteHandle_CreateEx_L_801202C8
    lbz r0, 0x74(r26)
    ori r0, r0, 0x2
    stb r0, 0x74(r26)
    SpriteHandle_CreateEx_L_801202C8:
    li r0, 0x0
    lfs f1, lbl_806D6D8C(r2)
    stb r0, 0x49(r26)
    lfs f0, g_glyphClipMinXY(r2)
    stfs f1, 0x4c(r26)
    stfs f0, 0x50(r26)
    stfs f0, 0x54(r26)
    stfs f0, 0x58(r26)
    stfs f1, 0x5c(r26)
    stfs f0, 0x60(r26)
    lwz r0, 0x48(r23)
    cmpwi r0, 0x1
    bne SpriteHandle_CreateEx_L_80120318
    li r0, 0x1
    stw r0, 0x78(r26)
    lwz r0, 0x4c(r23)
    stw r0, 0x7c(r26)
    lwz r0, 0x50(r23)
    stw r0, 0x80(r26)
    b SpriteHandle_CreateEx_L_80120328
    SpriteHandle_CreateEx_L_80120318:
    li r0, 0x2
    stw r0, 0x78(r26)
    lwz r0, 0x54(r23)
    stw r0, 0x84(r26)
    SpriteHandle_CreateEx_L_80120328:
    mr r3, r26
    bl fn_801217E8
    lbz r0, 0x24(r26)
    cmpwi r0, 0x2
    beq SpriteHandle_CreateEx_L_80120438
    mr r3, r29
    bl ResourceTable_GetSlotIndex
    mr r0, r3
    lwz r3, 0x8(r28)
    mr r4, r0
    bl TEXGetPaletteEntry
    lwz r5, 0x0(r3)
    lis r6, 0x4330
    stw r6, 0x38(r1)
    mr r3, r29
    lhz r7, 0x2(r5)
    addi r4, r26, 0xa8
    lhz r0, 0x0(r5)
    addi r5, r26, 0xac
    stw r7, 0x3c(r1)
    lfd f1, lbl_806D6D90(r2)
    lfd f0, 0x38(r1)
    stw r0, 0x34(r1)
    fsubs f31, f0, f1
    stw r6, 0x30(r1)
    lfd f0, 0x30(r1)
    fsubs f30, f0, f1
    bl ResourceTable_GetOffsetXY
    lfs f2, lbl_806D6D8C(r2)
    lfs f0, 0xa8(r26)
    fdivs f3, f2, f31
    lfs f1, lbl_806D6D88(r2)
    fadds f0, f0, f1
    fdivs f4, f2, f30
    stfs f0, 0xa8(r26)
    lfs f0, 0xac(r26)
    fadds f0, f0, f1
    stfs f0, 0xac(r26)
    lfs f0, 0xa8(r26)
    fmuls f0, f3, f0
    stfs f0, 0xa8(r26)
    lfs f0, 0xac(r26)
    fmuls f0, f4, f0
    stfs f0, 0xac(r26)
    lfs f1, 0x38(r26)
    lfs f0, 0xa8(r26)
    fsubs f1, f1, f2
    fmadds f0, f3, f1, f0
    stfs f0, 0xb0(r26)
    lfs f1, 0x3c(r26)
    lfs f0, 0xac(r26)
    fsubs f1, f1, f2
    fmadds f0, f4, f1, f0
    stfs f0, 0xb4(r26)
    lbz r0, 0x74(r26)
    clrlwi. r0, r0, 31
    beq SpriteHandle_CreateEx_L_8012041C
    lfs f1, 0xa8(r26)
    lfs f0, 0xb0(r26)
    stfs f0, 0xa8(r26)
    stfs f1, 0xb0(r26)
    SpriteHandle_CreateEx_L_8012041C:
    lbz r0, 0x74(r26)
    rlwinm. r0, r0, 0, 30, 30
    beq SpriteHandle_CreateEx_L_80120438
    lfs f1, 0xac(r26)
    lfs f0, 0xb4(r26)
    stfs f0, 0xac(r26)
    stfs f1, 0xb4(r26)
    SpriteHandle_CreateEx_L_80120438:
    lwz r0, 0x4(r23)
    cmpwi r0, -0x1
    bne SpriteHandle_CreateEx_L_80120450
    mr r3, r29
    bl ResourceTable_GetChainNextId
    stw r3, 0x4(r23)
    SpriteHandle_CreateEx_L_80120450:
    li r0, 0x0
    stb r0, 0xb8(r26)
    lbz r0, 0x24(r26)
    cmpwi r0, 0x2
    beq SpriteHandle_CreateEx_L_8012067C
    lwz r30, 0x4(r23)
    cmpwi r30, -0x1
    beq SpriteHandle_CreateEx_L_8012067C
    mr r3, r30
    bl ResourceTable_GetGroupKey
    li r0, 0x258
    mr r5, r31
    li r4, 0x0
    mtctr r0
    SpriteHandle_CreateEx_L_80120488:
    lwz r0, 0x4(r5)
    cmpw r3, r0
    bne SpriteHandle_CreateEx_L_801204A8
    mulli r4, r4, 0x1c
    lis r3, lbl_806573E8@ha
    addi r0, r3, lbl_806573E8@l
    add r0, r0, r4
    b SpriteHandle_CreateEx_L_801204B8
    SpriteHandle_CreateEx_L_801204A8:
    addi r5, r5, 0x1c
    addi r4, r4, 0x1
    bdnz SpriteHandle_CreateEx_L_80120488
    li r0, 0x0
    SpriteHandle_CreateEx_L_801204B8:
    cmplwi r0, 0x0
    mr r29, r0
    bne SpriteHandle_CreateEx_L_80120514
    mr r3, r30
    bl PreloadResource
    mr r3, r30
    bl ResourceTable_GetGroupKey
    li r0, 0x258
    li r4, 0x0
    mtctr r0
    SpriteHandle_CreateEx_L_801204E0:
    lwz r0, 0x4(r31)
    cmpw r3, r0
    bne SpriteHandle_CreateEx_L_80120500
    mulli r4, r4, 0x1c
    lis r3, lbl_806573E8@ha
    addi r0, r3, lbl_806573E8@l
    add r0, r0, r4
    b SpriteHandle_CreateEx_L_80120510
    SpriteHandle_CreateEx_L_80120500:
    addi r31, r31, 0x1c
    addi r4, r4, 0x1
    bdnz SpriteHandle_CreateEx_L_801204E0
    li r0, 0x0
    SpriteHandle_CreateEx_L_80120510:
    mr r29, r0
    SpriteHandle_CreateEx_L_80120514:
    cmplwi r29, 0x0
    beq SpriteHandle_CreateEx_L_8012067C
    li r0, 0x1
    mr r3, r30
    stb r0, 0xb8(r26)
    stw r30, 0xbc(r26)
    bl ResourceTable_GetSlotIndex
    mr r0, r3
    lwz r3, 0x8(r29)
    mr r31, r0
    mr r4, r31
    bl TEXGetPaletteEntry
    lwz r4, 0x10(r29)
    slwi r0, r31, 5
    mr r28, r3
    add r0, r4, r0
    stw r0, 0xc0(r26)
    lwz r0, 0x4(r3)
    cmplwi r0, 0x0
    beq SpriteHandle_CreateEx_L_80120578
    mulli r0, r31, 0xc
    lwz r3, 0x14(r29)
    add r0, r3, r0
    stw r0, 0xc4(r26)
    b SpriteHandle_CreateEx_L_80120580
    SpriteHandle_CreateEx_L_80120578:
    li r0, 0x0
    stw r0, 0xc4(r26)
    SpriteHandle_CreateEx_L_80120580:
    mr r3, r30
    addi r4, r1, 0xc
    addi r5, r1, 0x8
    bl ResourceTable_GetSizeXY
    lwz r7, 0x0(r28)
    lis r6, 0x4330
    stw r6, 0x38(r1)
    addi r5, r1, 0x24
    lhz r4, 0x2(r7)
    mr r3, r30
    lhz r0, 0x0(r7)
    stw r4, 0x3c(r1)
    addi r4, r1, 0x20
    lfd f1, lbl_806D6D90(r2)
    lfd f0, 0x38(r1)
    stw r0, 0x34(r1)
    fsubs f30, f0, f1
    stw r6, 0x30(r1)
    lfd f0, 0x30(r1)
    fsubs f31, f0, f1
    bl ResourceTable_GetOffsetXY
    lfs f4, lbl_806D6D8C(r2)
    lfs f1, 0xc(r1)
    fdivs f6, f4, f30
    lfs f0, 0x8(r1)
    lfs f3, 0x20(r1)
    lfs f5, lbl_806D6D88(r2)
    lfs f2, 0x24(r1)
    fadds f3, f3, f5
    fadds f2, f2, f5
    fdivs f5, f4, f31
    stfs f3, 0x20(r1)
    stfs f2, 0x24(r1)
    fmuls f3, f6, f3
    fmuls f2, f5, f2
    fsubs f1, f1, f4
    fsubs f0, f0, f4
    stfs f3, 0x20(r1)
    fmadds f1, f6, f1, f3
    stfs f2, 0x24(r1)
    fmadds f0, f5, f0, f2
    stfs f1, 0x28(r1)
    stfs f0, 0x2c(r1)
    lbz r0, 0x44(r23)
    cmplwi r0, 0x0
    beq SpriteHandle_CreateEx_L_80120640
    stfs f1, 0x20(r1)
    stfs f3, 0x28(r1)
    SpriteHandle_CreateEx_L_80120640:
    lbz r0, 0x45(r23)
    cmplwi r0, 0x0
    beq SpriteHandle_CreateEx_L_8012065C
    lfs f1, 0x24(r1)
    lfs f0, 0x2c(r1)
    stfs f0, 0x24(r1)
    stfs f1, 0x2c(r1)
    SpriteHandle_CreateEx_L_8012065C:
    lfs f1, 0x20(r1)
    lfs f0, 0x24(r1)
    stfs f1, 0xc8(r26)
    lfs f1, 0x28(r1)
    stfs f0, 0xcc(r26)
    lfs f0, 0x2c(r1)
    stfs f1, 0xd0(r26)
    stfs f0, 0xd4(r26)
    SpriteHandle_CreateEx_L_8012067C:
    li r3, 0x1
    clrlwi. r0, r25, 24
    stb r3, 0xd8(r26)
    bne SpriteHandle_CreateEx_L_80120694
    stb r3, 0xd9(r26)
    b SpriteHandle_CreateEx_L_801207E0
    SpriteHandle_CreateEx_L_80120694:
    lfs f3, 0x88(r26)
    lfs f4, 0x8c(r26)
    fmr f2, f3
    fmr f1, f4
    fmr f0, f3
    fcmpo cr0, f3, f3
    fcmpo cr0, f2, f0
    bge SpriteHandle_CreateEx_L_801206B8
    fmr f2, f0
    SpriteHandle_CreateEx_L_801206B8:
    lfs f0, 0x8c(r26)
    fcmpo cr0, f0, f4
    bge SpriteHandle_CreateEx_L_801206C8
    fmr f4, f0
    SpriteHandle_CreateEx_L_801206C8:
    fcmpo cr0, f1, f0
    bge SpriteHandle_CreateEx_L_801206D4
    fmr f1, f0
    SpriteHandle_CreateEx_L_801206D4:
    addi r3, r26, 0x8
    lfs f0, 0x90(r26)
    fcmpo cr0, f0, f3
    bge SpriteHandle_CreateEx_L_801206E8
    fmr f3, f0
    SpriteHandle_CreateEx_L_801206E8:
    fcmpo cr0, f2, f0
    bge SpriteHandle_CreateEx_L_801206F4
    fmr f2, f0
    SpriteHandle_CreateEx_L_801206F4:
    lfs f0, 0x8c(r3)
    fcmpo cr0, f0, f4
    bge SpriteHandle_CreateEx_L_80120704
    fmr f4, f0
    SpriteHandle_CreateEx_L_80120704:
    fcmpo cr0, f1, f0
    bge SpriteHandle_CreateEx_L_80120710
    fmr f1, f0
    SpriteHandle_CreateEx_L_80120710:
    lfs f0, 0x90(r3)
    addi r3, r3, 0x8
    fcmpo cr0, f0, f3
    bge SpriteHandle_CreateEx_L_80120724
    fmr f3, f0
    SpriteHandle_CreateEx_L_80120724:
    fcmpo cr0, f2, f0
    bge SpriteHandle_CreateEx_L_80120730
    fmr f2, f0
    SpriteHandle_CreateEx_L_80120730:
    lfs f0, 0x8c(r3)
    fcmpo cr0, f0, f4
    bge SpriteHandle_CreateEx_L_80120740
    fmr f4, f0
    SpriteHandle_CreateEx_L_80120740:
    fcmpo cr0, f1, f0
    bge SpriteHandle_CreateEx_L_8012074C
    fmr f1, f0
    SpriteHandle_CreateEx_L_8012074C:
    lfs f0, 0x90(r3)
    addi r3, r3, 0x8
    fcmpo cr0, f0, f3
    bge SpriteHandle_CreateEx_L_80120760
    fmr f3, f0
    SpriteHandle_CreateEx_L_80120760:
    fcmpo cr0, f2, f0
    bge SpriteHandle_CreateEx_L_8012076C
    fmr f2, f0
    SpriteHandle_CreateEx_L_8012076C:
    lfs f0, 0x8c(r3)
    fcmpo cr0, f0, f4
    bge SpriteHandle_CreateEx_L_8012077C
    fmr f4, f0
    SpriteHandle_CreateEx_L_8012077C:
    fcmpo cr0, f1, f0
    bge SpriteHandle_CreateEx_L_80120788
    fmr f1, f0
    SpriteHandle_CreateEx_L_80120788:
    lfs f0, g_glyphClipMaxX(r2)
    li r0, 0x1
    stb r0, 0xd9(r26)
    fcmpo cr0, f0, f3
    bge SpriteHandle_CreateEx_L_801207A4
    li r0, 0x0
    stb r0, 0xd9(r26)
    SpriteHandle_CreateEx_L_801207A4:
    lfs f0, g_glyphClipMinXY(r2)
    fcmpo cr0, f2, f0
    bge SpriteHandle_CreateEx_L_801207B8
    li r0, 0x0
    stb r0, 0xd9(r26)
    SpriteHandle_CreateEx_L_801207B8:
    lfs f0, g_glyphClipMaxY(r2)
    fcmpo cr0, f0, f4
    bge SpriteHandle_CreateEx_L_801207CC
    li r0, 0x0
    stb r0, 0xd9(r26)
    SpriteHandle_CreateEx_L_801207CC:
    lfs f0, g_glyphClipMinXY(r2)
    fcmpo cr0, f1, f0
    bge SpriteHandle_CreateEx_L_801207E0
    li r0, 0x0
    stb r0, 0xd9(r26)
    SpriteHandle_CreateEx_L_801207E0:
    mulli r3, r24, 0x1f4
    li r0, 0x0
    stb r0, 0xda(r26)
    addi r31, r3, 0x1
    add r31, r27, r31
    bl OSGetTick
    lis r5, 0x8000
    lis r4, 0x431c
    lwz r5, 0xf8(r5)
    lis r0, 0x4330
    subi r6, r4, 0x217d
    lwz r7, 0x10(r1)
    srwi r4, r5, 2
    stw r0, 0x38(r1)
    mulhwu r0, r6, r4
    subf r3, r7, r3
    lfd f2, lbl_806D6D90(r2)
    slwi r4, r3, 3
    lfs f0, lbl_806D6D98(r2)
    lwz r3, 0x14(r1)
    srwi r0, r0, 15
    divwu r0, r4, r0
    stw r0, 0x3c(r1)
    lfd f1, 0x38(r1)
    fsubs f1, f1, f2
    fdivs f1, f1, f0
    bl Profiler_RecordFrame
    bl OSGetTick
    lis r4, 0x8000
    lis r6, 0x431c
    lwz r0, 0xf8(r4)
    lis r5, 0x4330
    lwz r7, 0x1c(r1)
    lis r4, lbl_80657208@ha
    srwi r0, r0, 2
    subi r6, r6, 0x217d
    mulhwu r6, r6, r0
    subf r3, r7, r3
    lwz r0, 0x18(r1)
    addi r4, r4, lbl_80657208@l
    slwi r7, r3, 3
    stw r5, 0x30(r1)
    srwi r3, r6, 15
    slwi r0, r0, 2
    divwu r5, r7, r3
    lfd f3, lbl_806D6D90(r2)
    lfs f1, lbl_806D6D9C(r2)
    mr r3, r31
    lfsx f0, r4, r0
    stw r5, 0x34(r1)
    lfd f2, 0x30(r1)
    fsubs f2, f2, f3
    fdivs f1, f2, f1
    fadds f0, f0, f1
    stfsx f0, r4, r0
    SpriteHandle_CreateEx_L_801208BC:
    psq_l f31, 0x88(r1), 0, 0
    lfd f31, 0x80(r1)
    psq_l f30, 0x78(r1), 0, 0
    lfd f30, 0x70(r1)
    lmw r23, 0x4c(r1)
    lwz r0, 0x94(r1)
    mtlr r0
    addi r1, r1, 0x90
    blr
}

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
        ResEntry *e = &lbl_806573E8[i];
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
        lbl_8065B588[i] = 0;
    }
}

extern "C" asm void fn_80120A08(void) { /* 0x80120A08 size:0x378 */
    nofralloc
    stwu r1, -0x20(r1)
    mflr r0
    stw r0, 0x24(r1)
    stmw r27, 0xc(r1)
    mr r30, r3
    bl ResourceTable_GetChainNextId
    mr r31, r3
    cmpwi r31, -0x1
    beq fn_80120A08_L_80120C68
    bl ResourceTable_GetChainNextId
    mr r29, r3
    cmpwi r29, -0x1
    beq fn_80120A08_L_80120BA0
    bl ResourceTable_GetChainNextId
    cmpwi r3, -0x1
    beq fn_80120A08_L_80120AD4
    bl Stub_NoOp_80121c34
    mr r28, r3
    bl ResourceTable_GetChainNextId
    cmpwi r3, -0x1
    beq fn_80120A08_L_80120A60
    bl fn_80120A08
    fn_80120A08_L_80120A60:
    mr r3, r28
    bl Stub_NoOp_80121c34
    bl ResourceTable_GetGroupKey
    lis r4, lbl_806573E8@ha
    li r0, 0x258
    addi r4, r4, lbl_806573E8@l
    li r6, 0x0
    mtctr r0
    fn_80120A08_L_80120A80:
    lwz r0, 0x4(r4)
    cmpw r3, r0
    bne fn_80120A08_L_80120AC8
    lis r3, lbl_8065B588@ha
    slwi r5, r6, 2
    addi r4, r3, lbl_8065B588@l
    lwzx r3, r4, r5
    subi r0, r3, 0x1
    stwx r0, r4, r5
    lwzx r0, r4, r5
    cmpwi r0, 0x0
    bne fn_80120A08_L_80120AD4
    mulli r4, r6, 0x1c
    lis r3, lbl_806573E8@ha
    addi r0, r3, lbl_806573E8@l
    add r3, r0, r4
    bl fn_8011DC20
    b fn_80120A08_L_80120AD4
    fn_80120A08_L_80120AC8:
    addi r4, r4, 0x1c
    addi r6, r6, 0x1
    bdnz fn_80120A08_L_80120A80
    fn_80120A08_L_80120AD4:
    mr r3, r29
    bl ResourceTable_GetGroupKey
    lis r4, lbl_806573E8@ha
    li r0, 0x258
    addi r4, r4, lbl_806573E8@l
    li r6, 0x0
    mtctr r0
    fn_80120A08_L_80120AF0:
    lwz r0, 0x4(r4)
    cmpw r3, r0
    bne fn_80120A08_L_80120B94
    lis r3, lbl_8065B588@ha
    slwi r5, r6, 2
    addi r4, r3, lbl_8065B588@l
    lwzx r3, r4, r5
    subi r0, r3, 0x1
    stwx r0, r4, r5
    lwzx r0, r4, r5
    cmpwi r0, 0x0
    bne fn_80120A08_L_80120BA0
    mulli r4, r6, 0x1c
    lis r3, lbl_806573E8@ha
    addi r0, r3, lbl_806573E8@l
    add r28, r0, r4
    lwz r0, 0x8(r28)
    cmplwi r0, 0x0
    beq fn_80120A08_L_80120B54
    lwz r3, 0x0(r28)
    bl Stub_NoOp_80121c34
    cmpwi r3, 0x2b00
    bge fn_80120A08_L_80120B54
    addi r3, r28, 0x8
    bl TEXReleasePalette
    fn_80120A08_L_80120B54:
    lwz r3, 0x10(r28)
    bl MemoryManager_Free
    lwz r3, 0x14(r28)
    bl MemoryManager_Free
    lwz r3, 0x18(r28)
    bl MemoryManager_Free
    li r3, 0x0
    li r0, -0x1
    stw r3, 0x0(r28)
    stw r0, 0x4(r28)
    stw r3, 0x8(r28)
    stw r3, 0xc(r28)
    stw r3, 0x10(r28)
    stw r3, 0x14(r28)
    stw r3, 0x18(r28)
    b fn_80120A08_L_80120BA0
    fn_80120A08_L_80120B94:
    addi r4, r4, 0x1c
    addi r6, r6, 0x1
    bdnz fn_80120A08_L_80120AF0
    fn_80120A08_L_80120BA0:
    mr r3, r31
    bl ResourceTable_GetGroupKey
    lis r4, lbl_806573E8@ha
    li r0, 0x258
    addi r4, r4, lbl_806573E8@l
    li r6, 0x0
    mtctr r0
    fn_80120A08_L_80120BBC:
    lwz r0, 0x4(r4)
    cmpw r3, r0
    bne fn_80120A08_L_80120C5C
    lis r3, lbl_8065B588@ha
    slwi r5, r6, 2
    addi r4, r3, lbl_8065B588@l
    lwzx r3, r4, r5
    subi r0, r3, 0x1
    stwx r0, r4, r5
    lwzx r0, r4, r5
    cmpwi r0, 0x0
    bne fn_80120A08_L_80120C68
    mulli r4, r6, 0x1c
    lis r3, lbl_806573E8@ha
    addi r0, r3, lbl_806573E8@l
    add r29, r0, r4
    lwz r0, 0x8(r29)
    cmplwi r0, 0x0
    beq fn_80120A08_L_80120C1C
    lwz r0, 0x0(r29)
    cmpwi r0, 0x2b00
    bge fn_80120A08_L_80120C1C
    addi r3, r29, 0x8
    bl TEXReleasePalette
    fn_80120A08_L_80120C1C:
    lwz r3, 0x10(r29)
    bl MemoryManager_Free
    lwz r3, 0x14(r29)
    bl MemoryManager_Free
    lwz r3, 0x18(r29)
    bl MemoryManager_Free
    li r3, 0x0
    li r0, -0x1
    stw r3, 0x0(r29)
    stw r0, 0x4(r29)
    stw r3, 0x8(r29)
    stw r3, 0xc(r29)
    stw r3, 0x10(r29)
    stw r3, 0x14(r29)
    stw r3, 0x18(r29)
    b fn_80120A08_L_80120C68
    fn_80120A08_L_80120C5C:
    addi r4, r4, 0x1c
    addi r6, r6, 0x1
    bdnz fn_80120A08_L_80120BBC
    fn_80120A08_L_80120C68:
    mr r3, r30
    bl ResourceTable_GetGroupKey
    lis r4, lbl_806573E8@ha
    li r0, 0x258
    addi r4, r4, lbl_806573E8@l
    li r6, 0x0
    mtctr r0
    fn_80120A08_L_80120C84:
    lwz r0, 0x4(r4)
    cmpw r3, r0
    bne fn_80120A08_L_80120D5C
    lis r3, lbl_8065B588@ha
    slwi r5, r6, 2
    addi r4, r3, lbl_8065B588@l
    lwzx r3, r4, r5
    subi r0, r3, 0x1
    stwx r0, r4, r5
    lwzx r0, r4, r5
    cmpwi r0, 0x0
    bne fn_80120A08_L_80120D54
    mulli r28, r6, 0x1c
    lis r3, lbl_806573E8@ha
    addi r3, r3, lbl_806573E8@l
    add r29, r3, r28
    lwzu r0, 0x8(r29)
    cmplwi r0, 0x0
    beq fn_80120A08_L_80120CE8
    add r3, r3, r28
    lwz r0, 0x0(r3)
    cmpwi r0, 0x2b00
    bge fn_80120A08_L_80120CE8
    addi r3, r3, 0x8
    bl TEXReleasePalette
    fn_80120A08_L_80120CE8:
    lis r3, lbl_806573E8@ha
    addi r0, r3, lbl_806573E8@l
    add r30, r0, r28
    lwzu r3, 0x10(r30)
    bl MemoryManager_Free
    lis r3, lbl_806573E8@ha
    addi r0, r3, lbl_806573E8@l
    add r31, r0, r28
    lwzu r3, 0x14(r31)
    bl MemoryManager_Free
    lis r3, lbl_806573E8@ha
    addi r0, r3, lbl_806573E8@l
    add r27, r0, r28
    lwzu r3, 0x18(r27)
    bl MemoryManager_Free
    lis r3, lbl_806573E8@ha
    li r4, 0x0
    addi r3, r3, lbl_806573E8@l
    li r0, -0x1
    stwx r4, r3, r28
    add r3, r3, r28
    stw r0, 0x4(r3)
    stw r4, 0x0(r29)
    stw r4, 0xc(r3)
    stw r4, 0x0(r30)
    stw r4, 0x0(r31)
    stw r4, 0x0(r27)
    fn_80120A08_L_80120D54:
    li r3, 0x1
    b fn_80120A08_L_80120D6C
    fn_80120A08_L_80120D5C:
    addi r4, r4, 0x1c
    addi r6, r6, 0x1
    bdnz fn_80120A08_L_80120C84
    li r3, 0x0
    fn_80120A08_L_80120D6C:
    lmw r27, 0xc(r1)
    lwz r0, 0x24(r1)
    mtlr r0
    addi r1, r1, 0x20
    blr
}

extern "C" asm unsigned char PreloadResource(int id) { /* 0x80120D80 size:0x3A0 */
    nofralloc
    stwu r1, -0x20(r1)
    mflr r0
    stw r0, 0x24(r1)
    stmw r27, 0xc(r1)
    mr r29, r3
    bl IsValidResourceId
    clrlwi. r0, r3, 24
    bne PreloadResource_L_80120DA8
    li r3, 0x0
    b PreloadResource_L_8012110C
    PreloadResource_L_80120DA8:
    mr r3, r29
    bl ResourceTable_GetChainNextId
    mr r30, r3
    cmpwi r30, -0x1
    beq PreloadResource_L_8012104C
    bl IsValidResourceId
    clrlwi. r0, r3, 24
    beq PreloadResource_L_8012104C
    mr r3, r30
    bl ResourceTable_GetChainNextId
    mr r31, r3
    cmpwi r31, -0x1
    beq PreloadResource_L_80120F94
    bl IsValidResourceId
    clrlwi. r0, r3, 24
    beq PreloadResource_L_80120F94
    mr r3, r31
    bl ResourceTable_GetChainNextId
    mr r28, r3
    cmpwi r28, -0x1
    beq PreloadResource_L_80120EDC
    bl Stub_NoOp_80121c34
    mr r27, r3
    bl IsValidResourceId
    clrlwi. r0, r3, 24
    beq PreloadResource_L_80120EDC
    mr r3, r27
    bl ResourceTable_GetChainNextId
    cmpwi r3, -0x1
    beq PreloadResource_L_80120E24
    bl PreloadResource
    PreloadResource_L_80120E24:
    mr r3, r27
    bl ResourceTable_GetGroupKey
    lis r4, lbl_806573E8@ha
    li r0, 0x258
    addi r6, r4, lbl_806573E8@l
    li r4, 0x0
    mr r5, r6
    mtctr r0
    PreloadResource_L_80120E44:
    lwz r0, 0x4(r5)
    cmpw r3, r0
    bne PreloadResource_L_80120E6C
    lis r3, lbl_8065B588@ha
    slwi r5, r4, 2
    addi r4, r3, lbl_8065B588@l
    lwzx r3, r4, r5
    addi r0, r3, 0x1
    stwx r0, r4, r5
    b PreloadResource_L_80120EDC
    PreloadResource_L_80120E6C:
    addi r5, r5, 0x1c
    addi r4, r4, 0x1
    bdnz PreloadResource_L_80120E44
    li r0, 0x258
    li r27, 0x0
    mtctr r0
    PreloadResource_L_80120E84:
    lwz r0, 0x4(r6)
    cmpwi r0, -0x1
    bne PreloadResource_L_80120ED0
    mulli r5, r27, 0x1c
    lis r3, lbl_806573E8@ha
    mr r4, r28
    addi r0, r3, lbl_806573E8@l
    add r3, r0, r5
    bl ResourceSlot_Load
    clrlwi r0, r3, 24
    cmplwi r0, 0x1
    bne PreloadResource_L_80120EDC
    lis r3, lbl_8065B588@ha
    slwi r5, r27, 2
    addi r4, r3, lbl_8065B588@l
    lwzx r3, r4, r5
    addi r0, r3, 0x1
    stwx r0, r4, r5
    b PreloadResource_L_80120EDC
    PreloadResource_L_80120ED0:
    addi r6, r6, 0x1c
    addi r27, r27, 0x1
    bdnz PreloadResource_L_80120E84
    PreloadResource_L_80120EDC:
    mr r3, r31
    bl ResourceTable_GetGroupKey
    lis r4, lbl_806573E8@ha
    li r0, 0x258
    addi r6, r4, lbl_806573E8@l
    li r4, 0x0
    mr r5, r6
    mtctr r0
    PreloadResource_L_80120EFC:
    lwz r0, 0x4(r5)
    cmpw r3, r0
    bne PreloadResource_L_80120F24
    lis r3, lbl_8065B588@ha
    slwi r5, r4, 2
    addi r4, r3, lbl_8065B588@l
    lwzx r3, r4, r5
    addi r0, r3, 0x1
    stwx r0, r4, r5
    b PreloadResource_L_80120F94
    PreloadResource_L_80120F24:
    addi r5, r5, 0x1c
    addi r4, r4, 0x1
    bdnz PreloadResource_L_80120EFC
    li r0, 0x258
    li r27, 0x0
    mtctr r0
    PreloadResource_L_80120F3C:
    lwz r0, 0x4(r6)
    cmpwi r0, -0x1
    bne PreloadResource_L_80120F88
    mulli r5, r27, 0x1c
    lis r3, lbl_806573E8@ha
    mr r4, r31
    addi r0, r3, lbl_806573E8@l
    add r3, r0, r5
    bl ResourceSlot_Load
    clrlwi r0, r3, 24
    cmplwi r0, 0x1
    bne PreloadResource_L_80120F94
    lis r3, lbl_8065B588@ha
    slwi r5, r27, 2
    addi r4, r3, lbl_8065B588@l
    lwzx r3, r4, r5
    addi r0, r3, 0x1
    stwx r0, r4, r5
    b PreloadResource_L_80120F94
    PreloadResource_L_80120F88:
    addi r6, r6, 0x1c
    addi r27, r27, 0x1
    bdnz PreloadResource_L_80120F3C
    PreloadResource_L_80120F94:
    mr r3, r30
    bl ResourceTable_GetGroupKey
    lis r4, lbl_806573E8@ha
    li r0, 0x258
    addi r6, r4, lbl_806573E8@l
    li r4, 0x0
    mr r5, r6
    mtctr r0
    PreloadResource_L_80120FB4:
    lwz r0, 0x4(r5)
    cmpw r3, r0
    bne PreloadResource_L_80120FDC
    lis r3, lbl_8065B588@ha
    slwi r5, r4, 2
    addi r4, r3, lbl_8065B588@l
    lwzx r3, r4, r5
    addi r0, r3, 0x1
    stwx r0, r4, r5
    b PreloadResource_L_8012104C
    PreloadResource_L_80120FDC:
    addi r5, r5, 0x1c
    addi r4, r4, 0x1
    bdnz PreloadResource_L_80120FB4
    li r0, 0x258
    li r27, 0x0
    mtctr r0
    PreloadResource_L_80120FF4:
    lwz r0, 0x4(r6)
    cmpwi r0, -0x1
    bne PreloadResource_L_80121040
    mulli r5, r27, 0x1c
    lis r3, lbl_806573E8@ha
    mr r4, r30
    addi r0, r3, lbl_806573E8@l
    add r3, r0, r5
    bl ResourceSlot_Load
    clrlwi r0, r3, 24
    cmplwi r0, 0x1
    bne PreloadResource_L_8012104C
    lis r3, lbl_8065B588@ha
    slwi r5, r27, 2
    addi r4, r3, lbl_8065B588@l
    lwzx r3, r4, r5
    addi r0, r3, 0x1
    stwx r0, r4, r5
    b PreloadResource_L_8012104C
    PreloadResource_L_80121040:
    addi r6, r6, 0x1c
    addi r27, r27, 0x1
    bdnz PreloadResource_L_80120FF4
    PreloadResource_L_8012104C:
    mr r3, r29
    bl ResourceTable_GetGroupKey
    lis r4, lbl_806573E8@ha
    li r0, 0x258
    addi r5, r4, lbl_806573E8@l
    li r6, 0x0
    mr r4, r5
    mtctr r0
    PreloadResource_L_8012106C:
    lwz r0, 0x4(r4)
    cmpw r3, r0
    bne PreloadResource_L_80121098
    lis r3, lbl_8065B588@ha
    slwi r6, r6, 2
    addi r5, r3, lbl_8065B588@l
    li r3, 0x1
    lwzx r4, r5, r6
    addi r0, r4, 0x1
    stwx r0, r5, r6
    b PreloadResource_L_8012110C
    PreloadResource_L_80121098:
    addi r4, r4, 0x1c
    addi r6, r6, 0x1
    bdnz PreloadResource_L_8012106C
    li r0, 0x258
    li r27, 0x0
    mtctr r0
    PreloadResource_L_801210B0:
    lwz r0, 0x4(r5)
    cmpwi r0, -0x1
    bne PreloadResource_L_801210FC
    mulli r5, r27, 0x1c
    lis r3, lbl_806573E8@ha
    mr r4, r29
    addi r0, r3, lbl_806573E8@l
    add r3, r0, r5
    bl ResourceSlot_Load
    clrlwi r0, r3, 24
    cmplwi r0, 0x1
    bne PreloadResource_L_8012110C
    lis r4, lbl_8065B588@ha
    slwi r6, r27, 2
    addi r5, r4, lbl_8065B588@l
    lwzx r4, r5, r6
    addi r0, r4, 0x1
    stwx r0, r5, r6
    b PreloadResource_L_8012110C
    PreloadResource_L_801210FC:
    addi r5, r5, 0x1c
    addi r27, r27, 0x1
    bdnz PreloadResource_L_801210B0
    li r3, 0x0
    PreloadResource_L_8012110C:
    lmw r27, 0xc(r1)
    lwz r0, 0x24(r1)
    mtlr r0
    addi r1, r1, 0x20
    blr
}

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

extern "C" asm void fn_801217E8(SpriteHandle *s) { /* 0x801217E8 size:0x44C */
    nofralloc
    stwu r1, -0x100(r1)
    mflr r0
    stw r0, 0x104(r1)
    stfd f31, 0xf0(r1)
    psq_st f31, 0xf8(r1), 0, 0
    stfd f30, 0xe0(r1)
    psq_st f30, 0xe8(r1), 0, 0
    stfd f29, 0xd0(r1)
    psq_st f29, 0xd8(r1), 0, 0
    stw r31, 0xcc(r1)
    stw r30, 0xc8(r1)
    stw r29, 0xc4(r1)
    mr r29, r3
    lis r4, lbl_80332528@ha
    lwz r3, 0x10(r3)
    addi r30, r4, lbl_80332528@l
    addi r4, r1, 0xc
    addi r5, r1, 0x8
    bl ResourceTable_GetScaleXY
    lwz r3, 0x10(r29)
    bl ResourceTable_GetFlagsByte
    li r0, 0x0
    lfs f0, g_glyphClipMinXY(r2)
    stb r0, 0x48(r29)
    mr r31, r3
    lfs f1, 0x40(r29)
    fcmpo cr0, f1, f0
    bge fn_801217E8_L_80121864
    lbz r0, 0x48(r29)
    ori r0, r0, 0x1
    stb r0, 0x48(r29)
    fn_801217E8_L_80121864:
    lfs f1, 0x44(r29)
    lfs f0, g_glyphClipMinXY(r2)
    fcmpo cr0, f1, f0
    bge fn_801217E8_L_80121880
    lbz r0, 0x48(r29)
    ori r0, r0, 0x2
    stb r0, 0x48(r29)
    fn_801217E8_L_80121880:
    lfs f1, 0x40(r29)
    lfs f0, 0x44(r29)
    fabs f1, f1
    lfs f5, 0x38(r29)
    fabs f0, f0
    lfs f2, 0x3c(r29)
    lfs f6, 0xc(r1)
    frsp f4, f1
    frsp f0, f0
    lfs f3, 0x8(r1)
    lfs f1, 0x34(r29)
    fmuls f4, f5, f4
    fmuls f0, f2, f0
    fmuls f30, f6, f4
    fmuls f29, f3, f0
    bl LUT_Cosine
    fmr f31, f1
    lfs f1, 0x34(r29)
    bl LUT_Sine
    extsb r0, r31
    cmpwi r0, 0x9
    bne fn_801217E8_L_801219C4
    lwz r10, 0x0(r30)
    li r0, 0x4
    lwz r9, 0x4(r30)
    mr r12, r29
    lwz r8, 0x8(r30)
    addi r11, r1, 0x50
    lwz r7, 0xc(r30)
    lwz r6, 0x10(r30)
    lwz r5, 0x14(r30)
    lwz r4, 0x18(r30)
    lwz r3, 0x1c(r30)
    stw r10, 0x50(r1)
    stw r9, 0x54(r1)
    stw r8, 0x58(r1)
    stw r7, 0x5c(r1)
    stw r6, 0x60(r1)
    stw r5, 0x64(r1)
    stw r4, 0x68(r1)
    stw r3, 0x6c(r1)
    mtctr r0
    fn_801217E8_L_80121928:
    lfs f0, 0x4(r11)
    lfs f2, 0x0(r11)
    fmuls f0, f29, f0
    fmuls f3, f30, f2
    fmuls f2, f31, f0
    fmuls f0, f1, f0
    fmsubs f2, f1, f3, f2
    fmadds f0, f31, f3, f0
    stfs f2, 0x88(r12)
    stfs f0, 0x8c(r12)
    lbz r0, 0x26(r29)
    cmplwi r0, 0x1
    bne fn_801217E8_L_80121980
    lfs f2, 0x88(r12)
    lfs f0, 0x28(r29)
    fadds f0, f2, f0
    stfs f0, 0x88(r12)
    lfs f2, 0x8c(r12)
    lfs f0, 0x2c(r29)
    fadds f0, f2, f0
    stfs f0, 0x8c(r12)
    b fn_801217E8_L_801219B4
    fn_801217E8_L_80121980:
    lfs f2, 0x38(r29)
    lfs f4, lbl_806D6D88(r2)
    lfs f0, 0x28(r29)
    lfs f3, 0x88(r12)
    fmadds f0, f2, f4, f0
    fadds f0, f3, f0
    stfs f0, 0x88(r12)
    lfs f2, 0x3c(r29)
    lfs f0, 0x2c(r29)
    lfs f3, 0x8c(r12)
    fmadds f0, f2, f4, f0
    fadds f0, f3, f0
    stfs f0, 0x8c(r12)
    fn_801217E8_L_801219B4:
    addi r11, r11, 0x8
    addi r12, r12, 0x8
    bdnz fn_801217E8_L_80121928
    b fn_801217E8_L_80121C00
    fn_801217E8_L_801219C4:
    lbz r0, 0x49(r29)
    cmplwi r0, 0x0
    beq fn_801217E8_L_80121AC0
    lwz r10, 0x20(r30)
    li r0, 0x2
    lwz r9, 0x24(r30)
    mr r12, r29
    lwz r8, 0x28(r30)
    addi r11, r1, 0x30
    lwz r7, 0x2c(r30)
    lwz r6, 0x30(r30)
    lwz r5, 0x34(r30)
    lwz r4, 0x38(r30)
    lwz r3, 0x3c(r30)
    stw r10, 0x30(r1)
    stw r9, 0x34(r1)
    stw r8, 0x38(r1)
    stw r7, 0x3c(r1)
    stw r6, 0x40(r1)
    stw r5, 0x44(r1)
    stw r4, 0x48(r1)
    stw r3, 0x4c(r1)
    mtctr r0
    fn_801217E8_L_80121A20:
    lfs f3, 0x4(r11)
    lfs f4, 0x0(r11)
    fmuls f6, f29, f3
    lfs f0, 0x50(r29)
    fmuls f5, f30, f4
    lfs f1, 0x4c(r29)
    lfs f2, 0x54(r29)
    fmuls f0, f6, f0
    lfs f3, 0xc(r11)
    lfs f4, 0x8(r11)
    addi r11, r11, 0x10
    fmadds f0, f5, f1, f0
    fadds f0, f2, f0
    stfs f0, 0x88(r12)
    lfs f0, 0x5c(r29)
    lfs f1, 0x58(r29)
    fmuls f0, f6, f0
    lfs f2, 0x60(r29)
    fmuls f6, f29, f3
    fmadds f0, f5, f1, f0
    fmuls f5, f30, f4
    fadds f0, f2, f0
    stfs f0, 0x8c(r12)
    lfs f0, 0x50(r29)
    lfs f1, 0x4c(r29)
    fmuls f0, f6, f0
    lfs f2, 0x54(r29)
    fmadds f0, f5, f1, f0
    fadds f0, f2, f0
    stfs f0, 0x90(r12)
    lfs f0, 0x5c(r29)
    lfs f1, 0x58(r29)
    fmuls f0, f6, f0
    lfs f2, 0x60(r29)
    fmadds f0, f5, f1, f0
    fadds f0, f2, f0
    stfs f0, 0x94(r12)
    addi r12, r12, 0x10
    bdnz fn_801217E8_L_80121A20
    b fn_801217E8_L_80121C00
    fn_801217E8_L_80121AC0:
    lwz r12, 0x40(r30)
    li r0, 0x9
    lwz r11, 0x44(r30)
    addi r5, r1, 0x6c
    lwz r10, 0x48(r30)
    addi r4, r30, 0x5c
    lwz r9, 0x4c(r30)
    lwz r8, 0x50(r30)
    lwz r7, 0x54(r30)
    lwz r6, 0x58(r30)
    lwz r3, 0x5c(r30)
    stw r12, 0x10(r1)
    stw r11, 0x14(r1)
    stw r10, 0x18(r1)
    stw r9, 0x1c(r1)
    stw r8, 0x20(r1)
    stw r7, 0x24(r1)
    stw r6, 0x28(r1)
    stw r3, 0x2c(r1)
    mtctr r0
    fn_801217E8_L_80121B10:
    lwz r3, 0x4(r4)
    lwzu r0, 0x8(r4)
    stw r3, 0x4(r5)
    stwu r0, 0x8(r5)
    bdnz fn_801217E8_L_80121B10
    extsb r0, r31
    addi r6, r1, 0x70
    slwi r3, r0, 3
    mr r5, r29
    li r0, 0x2
    addi r4, r1, 0x10
    add r6, r6, r3
    mtctr r0
    fn_801217E8_L_80121B44:
    lfs f3, 0x4(r4)
    lfs f4, 0x0(r4)
    fmuls f6, f29, f3
    lfs f0, 0x4(r6)
    fmuls f5, f30, f4
    lfs f2, 0x0(r6)
    lfs f3, 0xc(r4)
    fmadds f6, f29, f0, f6
    fmadds f5, f30, f2, f5
    lfs f4, 0x8(r4)
    addi r4, r4, 0x10
    fmuls f2, f6, f31
    fmuls f0, f6, f1
    fmuls f6, f29, f3
    fmsubs f2, f5, f1, f2
    fmadds f0, f5, f31, f0
    fmuls f5, f30, f4
    stfs f2, 0x88(r5)
    stfs f0, 0x8c(r5)
    lfs f2, 0x88(r5)
    lfs f0, 0x28(r29)
    fadds f0, f2, f0
    stfs f0, 0x88(r5)
    lfs f2, 0x8c(r5)
    lfs f0, 0x2c(r29)
    fadds f0, f2, f0
    stfs f0, 0x8c(r5)
    lfs f0, 0x4(r6)
    lfs f2, 0x0(r6)
    fmadds f6, f29, f0, f6
    fmadds f5, f30, f2, f5
    fmuls f2, f6, f31
    fmuls f0, f6, f1
    fmsubs f2, f5, f1, f2
    fmadds f0, f5, f31, f0
    stfs f2, 0x90(r5)
    stfs f0, 0x94(r5)
    lfs f2, 0x90(r5)
    lfs f0, 0x28(r29)
    fadds f0, f2, f0
    stfs f0, 0x90(r5)
    lfs f2, 0x94(r5)
    lfs f0, 0x2c(r29)
    fadds f0, f2, f0
    stfs f0, 0x94(r5)
    addi r5, r5, 0x10
    bdnz fn_801217E8_L_80121B44
    fn_801217E8_L_80121C00:
    psq_l f31, 0xf8(r1), 0, 0
    lfd f31, 0xf0(r1)
    psq_l f30, 0xe8(r1), 0, 0
    lfd f30, 0xe0(r1)
    psq_l f29, 0xd8(r1), 0, 0
    lfd f29, 0xd0(r1)
    lwz r31, 0xcc(r1)
    lwz r30, 0xc8(r1)
    lwz r0, 0x104(r1)
    lwz r29, 0xc4(r1)
    mtlr r0
    addi r1, r1, 0x100
    blr
}

extern "C" void Stub_NoOp_80121c34(void) {
}

extern "C" asm void fn_80121C38(void) { /* 0x80121C38 size:0x1D8 */
    nofralloc
    stwu r1, -0x90(r1)
    mflr r0
    stw r0, 0x94(r1)
    stfd f31, 0x80(r1)
    psq_st f31, 0x88(r1), 0, 0
    stfd f30, 0x70(r1)
    psq_st f30, 0x78(r1), 0, 0
    stfd f29, 0x60(r1)
    psq_st f29, 0x68(r1), 0, 0
    stfd f28, 0x50(r1)
    psq_st f28, 0x58(r1), 0, 0
    stfd f27, 0x40(r1)
    psq_st f27, 0x48(r1), 0, 0
    stfd f26, 0x30(r1)
    psq_st f26, 0x38(r1), 0, 0
    stfd f25, 0x20(r1)
    psq_st f25, 0x28(r1), 0, 0
    stw r31, 0x1c(r1)
    mr r31, r3
    li r3, 0x1b8c
    lwz r0, 0x8(r31)
    cmpwi r0, 0x2
    beq fn_80121C38_L_80121C98
    lwz r3, 0x0(r31)
    fn_80121C38_L_80121C98:
    lfs f26, 0x2c(r31)
    lfs f25, 0x30(r31)
    lfs f0, 0x20(r31)
    stfs f0, 0xc(r1)
    lfs f0, 0x24(r31)
    stfs f0, 0x8(r1)
    lwz r0, 0x0(r31)
    cmpwi r0, 0x2
    beq fn_80121C38_L_80121CC8
    addi r4, r1, 0xc
    addi r5, r1, 0x8
    bl ResourceTable_GetSizeXY
    fn_80121C38_L_80121CC8:
    lfs f0, 0x14(r31)
    lfs f2, 0x18(r31)
    fmr f31, f0
    lfs f1, 0x28(r31)
    fmr f30, f0
    fmr f29, f2
    fmr f28, f2
    bl LUT_Cosine
    fmr f27, f1
    lfs f1, 0x28(r31)
    bl LUT_Sine
    lfs f0, 0x8(r1)
    lfs f2, 0xc(r1)
    fmuls f4, f0, f25
    lbz r0, 0x10(r31)
    fmuls f5, f2, f26
    lfs f3, lbl_806D6D88(r2)
    cmplwi r0, 0x0
    fmuls f2, f27, f4
    fmuls f0, f1, f4
    fmsubs f1, f1, f5, f2
    fmadds f0, f27, f5, f0
    fmuls f2, f3, f1
    fmuls f6, f3, f0
    bne fn_80121C38_L_80121D44
    fmuls f0, f3, f5
    fmuls f1, f3, f4
    fadds f31, f31, f0
    fadds f29, f29, f1
    fadds f30, f30, f0
    fadds f28, f28, f1
    fn_80121C38_L_80121D44:
    fsubs f31, f31, f2
    fadds f30, f30, f2
    fsubs f29, f29, f6
    fadds f28, f28, f6
    fcmpo cr0, f31, f30
    ble fn_80121C38_L_80121D68
    fmr f0, f31
    fmr f31, f30
    fmr f30, f0
    fn_80121C38_L_80121D68:
    fcmpo cr0, f29, f28
    ble fn_80121C38_L_80121D7C
    fmr f0, f29
    fmr f29, f28
    fmr f28, f0
    fn_80121C38_L_80121D7C:
    lfs f0, g_glyphClipMaxX(r2)
    fcmpo cr0, f31, f0
    cror eq, gt, eq
    beq fn_80121C38_L_80121D98
    lfs f1, g_glyphClipMinXY(r2)
    fcmpo cr0, f30, f1
    bge fn_80121C38_L_80121DA0
    fn_80121C38_L_80121D98:
    li r3, 0x0
    b fn_80121C38_L_80121DC4
    fn_80121C38_L_80121DA0:
    lfs f0, g_glyphClipMaxY(r2)
    fcmpo cr0, f29, f0
    cror eq, gt, eq
    beq fn_80121C38_L_80121DB8
    fcmpo cr0, f28, f1
    bge fn_80121C38_L_80121DC0
    fn_80121C38_L_80121DB8:
    li r3, 0x0
    b fn_80121C38_L_80121DC4
    fn_80121C38_L_80121DC0:
    li r3, 0x1
    fn_80121C38_L_80121DC4:
    psq_l f31, 0x88(r1), 0, 0
    lfd f31, 0x80(r1)
    psq_l f30, 0x78(r1), 0, 0
    lfd f30, 0x70(r1)
    psq_l f29, 0x68(r1), 0, 0
    lfd f29, 0x60(r1)
    psq_l f28, 0x58(r1), 0, 0
    lfd f28, 0x50(r1)
    psq_l f27, 0x48(r1), 0, 0
    lfd f27, 0x40(r1)
    psq_l f26, 0x38(r1), 0, 0
    lfd f26, 0x30(r1)
    psq_l f25, 0x28(r1), 0, 0
    lfd f25, 0x20(r1)
    lwz r0, 0x94(r1)
    lwz r31, 0x1c(r1)
    mtlr r0
    addi r1, r1, 0x90
    blr
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

extern "C" asm void fn_8012215C(void) { /* 0x8012215C size:0x78 */
    nofralloc
    stwu r1, -0x20(r1)
    mflr r0
    stw r0, 0x24(r1)
    stw r31, 0x1c(r1)
    mr r31, r5
    stw r30, 0x18(r1)
    mr r30, r4
    stw r29, 0x14(r1)
    mr r29, r3
    lwz r3, 0x0(r5)
    lwz r0, 0x4(r3)
    lwz r4, 0x0(r3)
    stw r0, 0x0(r5)
    stw r0, 0x4(r4)
    lwz r0, 0x0(r3)
    lwz r4, 0x4(r3)
    stw r0, 0x0(r4)
    bl MemoryManager_TimedFree
    lwz r3, 0x0(r30)
    lwz r0, 0x0(r31)
    subi r3, r3, 0x1
    stw r3, 0x0(r30)
    stw r0, 0x0(r29)
    lwz r31, 0x1c(r1)
    lwz r30, 0x18(r1)
    lwz r29, 0x14(r1)
    lwz r0, 0x24(r1)
    mtlr r0
    addi r1, r1, 0x20
    blr
}

extern "C" LListImp *fn_801221D4(LListImp *l) {
    DoublyLinkedList_Init(l);
    return l;
}

extern "C" void fn_80122204(void) {
    __destroy_arr(lbl_80657234, (void *)fn_8012223C, 0xC, 8);
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

extern "C" asm void fn_80122338(void) { /* 0x80122338 size:0xB0 */
    nofralloc
    stwu r1, -0x10(r1)
    mflr r0
    lis r4, fn_801222F0@ha
    lis r5, lbl_80657228@ha
    stw r0, 0x14(r1)
    lis r3, fn_8012223C@ha
    li r6, 0xc
    addi r4, r4, fn_801222F0@l
    stw r31, 0xc(r1)
    addi r31, r5, lbl_80657228@l
    addi r5, r3, fn_8012223C@l
    li r7, 0x8
    addi r3, r31, 0xc
    bl __construct_array
    lis r3, fn_80122204@ha
    addi r5, r31, 0x0
    addi r4, r3, fn_80122204@l
    li r3, 0x0
    bl __register_global_object
    lis r3, fn_801221D4@ha
    lis r5, fn_80121FB4@ha
    addi r4, r3, fn_801221D4@l
    li r6, 0xc
    addi r3, r31, 0x78
    addi r5, r5, fn_80121FB4@l
    li r7, 0x10
    bl __construct_array
    lis r4, fn_80121F54@ha
    addi r3, r31, 0x78
    addi r4, r4, fn_80121F54@l
    addi r5, r31, 0x6c
    bl __register_global_object
    lis r4, fn_8011DF70@ha
    addi r3, r31, 0x1c0
    addi r4, r4, fn_8011DF70@l
    li r5, 0x0
    li r6, 0x1c
    li r7, 0x258
    bl __construct_array
    lwz r0, 0x14(r1)
    lwz r31, 0xc(r1)
    mtlr r0
    addi r1, r1, 0x10
    blr
}

__declspec(section ".ctors") static void *const fn_80122338_ctor_ref = (void *)fn_80122338;
