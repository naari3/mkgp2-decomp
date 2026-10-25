/*
 * 0x8022ACE4..0x8022BFA8: clEnemyFace (rival face icons drawn over the
 * nearest opponents) plus the tire-sprite quad renderer that shares the
 * TU. The TU owns .rodata 0x803DA278..0x803DA710.
 */

void *operator new(unsigned long size);
void operator delete(void *p) throw();

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

struct Vec3c {
    float x, y, z;
    Vec3c();
    ~Vec3c();
};

struct Vec3f {
    float x, y, z;
};

struct KartFlags {
    char pad[0x10];
    unsigned long long bits;
};

struct KartRender {
    char pad0[0x1E8];
    int active;
    char pad1EC[0x1F4 - 0x1EC];
    int slot;
    int course;
    char pad1FC[0x304 - 0x1FC];
    KartFlags *flags;
};

struct PathEntry {
    char pad0[4];
    int id;
    char pad8[0x90 - 8];
    KartRender *kart;
};

struct TireSprite {
    signed char flip;
    char pad01[0x14 - 1];
    signed char visible;
    float alpha;
    char pad1C[0x34 - 0x1C];
    float vx[4];
    float vy[4];
    float vz[4];
    char pad64[0x6C - 0x64];
    float px, py, pz;
};

struct FaceSprite {
    virtual ~FaceSprite();
    char pad04[0x14 - 4];
    float scale;
};

struct FaceIcon : FaceSprite {
    FaceIcon(KartRender *kart, int param);
    void Reset();
    void Place(Vec3c *screen);
    void Update();
};

struct FaceRing : FaceSprite {
    FaceRing(KartRender *kart, int param);
    void Reset();
    void Place(Vec3c *screen);
    void Update();
};

struct FaceModelSub {
    char pad[0x20];
    float scale;
    void Reset();
};

struct clNormal3D;

struct clEFaceModel {
    virtual ~clEFaceModel();
    char pad04[0x14 - 4];
    float x, y, z;
    float scale;
    char pad24[0x2C - 0x24];
    FaceModelSub *sub;
    clNormal3D *models[2];
    int state;

    clEFaceModel(KartRender *kart, int a, int b, int c);
    void Draw();
    void Update();
    void Trigger(int arg);
};

struct clEFace3D {
    virtual ~clEFace3D();
    KartRender *kart;
    float x, y, z;
    float scale;
    int param;
    int slot;
    int a, b, c;
    clEFaceModel *model;

    clEFace3D(KartRender *k, int p) {
        kart = k;
        x = y = z = 0.0f;
        scale = 1.0f;
        param = p;
        c = -1;
        slot = kart->slot;
        c = -1;
        a = -1;
        b = -1;
    }
};

struct FaceHolder {
    FaceSprite *p;
    FaceHolder(FaceSprite *q) : p(q) {}
    ~FaceHolder() throw() {
        if (p) {
            delete p;
        }
    }
};

struct clCDispInterface {
    virtual ~clCDispInterface() {}
    int id;
    clCDispInterface() {
        id = -1;
    }
};

struct clEnemyFace : clCDispInterface {
    int state;
    int param;
    FaceHolder holder;
    FaceIcon *icons[8];
    FaceRing *rings[8];
    clEFace3D *faces[8];
    KartRender *karts[8];
    Vec3c screen[8];
    float dist[8];
    int order[8];
    float iconScale[8];
    Vec3c world[8];
    float faceScale[8];
    char pad1D4[0x1DC - 0x1D4];

    clEnemyFace(void *path, int param);
    virtual ~clEnemyFace();
    virtual void Update();
    virtual void Draw();
    virtual void Enable(int on);
    void Sort();
};

struct FaceRequest {
    KartRender *kart;
    int arg;
};

extern "C" {
extern void *lbl_806D05F0[2];
extern TPLPalette *lbl_806D05F8[2];
extern void *lbl_806D0600[2];
extern const int lbl_806DB590[2];

extern void *lbl_806D10AC;
extern FaceRequest lbl_80679CA0[4];
extern int g_gameMode;
extern KartRender *g_playerRenderObj;
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
float HSD_CObjGetNear(void *cobj);
float HSD_CObjGetFar(void *cobj);
void *GetCourseScene3D(void);
void CObj_LoadProjMatrix(void *cobj, Vec3c *pos);
void CObj_ProjectPoint(void *cobj, float *x, float *y, float *w, float *z, float fx, float fy, float fz);
void clNormal3D_SetScale(clNormal3D *m, int anim, float t, float a, float b, float c);
void clDrawMan_AddSorted_DepthRange(void *man, void (*fn)(TireSprite *), TireSprite *obj, float x, float y, float z, float bias);
unsigned char IsRaceStarted(void);
const float *KartDriver_GetKartRootMtx(KartRender *k);
void PreloadResource(int id);
PathEntry *PathManager_GetEntrySubStruct(void *path, int idx);
int GetDisplayBufferIndex(KartRender *k);
unsigned char fn_80231644(int *b, int *a, int *c, int slot, int course);
int fn_80231BD4(int kind, int course, int z);
}

extern const unsigned int lbl_803DA278[258] = {0x3F800000, 0x3F333333, 0x3F666666, 0x00000000, 0x00000000, 0x43FA0000, 0x42855556, 0x447A0000, 0x42855556, 0x44FA0000, 0x42855556, 0x453B8000, 0x42855556, 0x457A0000, 0x42855556, 0x459C4000, 0x42855556, 0x00000000, 0x00000000, 0x43FA0000, 0x42855556, 0x447A0000, 0x42855556, 0x44FA0000, 0x42855556, 0x453B8000, 0x42855556, 0x457A0000, 0x42855556, 0x459C4000, 0x42855556, 0x00000000, 0x00000000, 0x43FA0000, 0x42855556, 0x447A0000, 0x42855556, 0x44FA0000, 0x42855556, 0x453B8000, 0x42855556, 0x457A0000, 0x42855556, 0x459C4000, 0x42855556, 0x00000000, 0x00000000, 0x43FA0000, 0x42855556, 0x447A0000, 0x42855556, 0x44FA0000, 0x42855556, 0x453B8000, 0x42855556, 0x457A0000, 0x42855556, 0x459C4000, 0x42855556, 0x00000000, 0x00000000, 0x43FA0000, 0x42855556, 0x447A0000, 0x42855556, 0x44FA0000, 0x42855556, 0x453B8000, 0x42855556, 0x457A0000, 0x42855556, 0x459C4000, 0x42855556, 0x00000000, 0x00000000, 0x43FA0000, 0x42855556, 0x447A0000, 0x42855556, 0x44FA0000, 0x42855556, 0x453B8000, 0x42855556, 0x457A0000, 0x42855556, 0x459C4000, 0x42855556, 0x00000000, 0x00000000, 0x43FA0000, 0x42855556, 0x447A0000, 0x42855556, 0x44FA0000, 0x42855556, 0x453B8000, 0x42855556, 0x457A0000, 0x42855556, 0x459C4000, 0x42855556, 0x00000000, 0x00000000, 0x43FA0000, 0x42855556, 0x447A0000, 0x42855556, 0x44FA0000, 0x42855556, 0x453B8000, 0x42855556, 0x457A0000, 0x42855556, 0x459C4000, 0x42855556, 0x00000000, 0x00000000, 0x43FA0000, 0x42855556, 0x447A0000, 0x42855556, 0x44FA0000, 0x42855556, 0x453B8000, 0x42855556, 0x457A0000, 0x42855556, 0x459C4000, 0x42855556, 0x00000000, 0x00000000, 0x43FA0000, 0x42855556, 0x447A0000, 0x42855556, 0x44FA0000, 0x42855556, 0x453B8000, 0x42855556, 0x457A0000, 0x42855556, 0x459C4000, 0x42855556, 0x00000000, 0x00000000, 0x43FA0000, 0x42855556, 0x447A0000, 0x42855556, 0x44FA0000, 0x42855556, 0x453B8000, 0x42855556, 0x457A0000, 0x42855556, 0x459C4000, 0x42855556, 0x00000000, 0x00000000, 0x43FA0000, 0x42855556, 0x447A0000, 0x42855556, 0x44FA0000, 0x42855556, 0x453B8000, 0x42855556, 0x457A0000, 0x42855556, 0x459C4000, 0x42855556, 0x00000000, 0x00000000, 0x43FA0000, 0x42A6AAAB, 0x447A0000, 0x42A6AAAB, 0x44FA0000, 0x42A6AAAB, 0x453B8000, 0x42A6AAAB, 0x457A0000, 0x42A6AAAB, 0x459C4000, 0x42A6AAAB, 0x00000000, 0x00000000, 0x43FA0000, 0x42A6AAAB, 0x447A0000, 0x42A6AAAB, 0x44FA0000, 0x42A6AAAB, 0x453B8000, 0x42A6AAAB, 0x457A0000, 0x42A6AAAB, 0x459C4000, 0x42A6AAAB, 0x00000000, 0x00000000, 0x43FA0000, 0x42A6AAAB, 0x447A0000, 0x42A6AAAB, 0x44FA0000, 0x42A6AAAB, 0x453B8000, 0x42A6AAAB, 0x457A0000, 0x42A6AAAB, 0x459C4000, 0x42A6AAAB, 0x00000000, 0x00000000, 0x43FA0000, 0x42A6AAAB, 0x447A0000, 0x42A6AAAB, 0x44FA0000, 0x42A6AAAB, 0x453B8000, 0x42A6AAAB, 0x457A0000, 0x42A6AAAB, 0x459C4000, 0x42A6AAAB, 0x00000000, 0x00000000, 0x43FA0000, 0x42A6AAAB, 0x447A0000, 0x42A6AAAB, 0x44FA0000, 0x42A6AAAB, 0x453B8000, 0x42A6AAAB, 0x457A0000, 0x42A6AAAB, 0x459C4000, 0x42A6AAAB, 0x00000000, 0x00000000, 0x43FA0000, 0x42A6AAAB, 0x447A0000, 0x42A6AAAB, 0x44FA0000, 0x42A6AAAB, 0x453B8000, 0x42A6AAAB, 0x457A0000, 0x42A6AAAB, 0x459C4000, 0x42A6AAAB, 0x00000000, 0x00000000, 0x00000000};
extern const unsigned int lbl_803DA680[8] = {0x00000000, 0x3C23D70A, 0x3F000000, 0x3C23D70A, 0x3F000000, 0x3E75C28F, 0x00000000, 0x3E75C28F};
extern const char lbl_803DA6A0[0x20] = "Start LoadEffect - tire sprite\n";
extern const char lbl_803DA6C0[0x20] = "End LoadEffect - tire sprite\n";
extern const char lbl_803DA6E0[0xC] = "clEnemyFace";
extern const char lbl_803DA6EC[0x14] = "clCDispInterface";
extern const char lbl_803DA700[0x10] = "clEFace3D";

static inline void LoadTireSprites() {
    DebugPrintf(lbl_803DA6A0);
    for (int i = 0; i < 2; i++) {
        if (lbl_806D05F0[i] != 0 || lbl_806D05F8[i] != 0) {
            return;
        }
        const char *path = ResourceTable_GetFilePathPtr(lbl_806DB590[i]);
        if (path == 0) {
            return;
        }
        TEXLoadPalette_Retry(&lbl_806D05F8[i], path);
        if (lbl_806D05F8[i] == 0) {
            return;
        }
        unsigned int n = lbl_806D05F8[i]->count;
        lbl_806D05F0[i] = FUN_8003b120(n << 5);
        lbl_806D0600[i] = FUN_8003b120(n * 0xC);
        for (unsigned int k = 0; k < n; k++) {
            if (TEXGetPaletteEntry(lbl_806D05F8[i], k)->clut) {
                TEXBindPaletteEntry_CI(lbl_806D05F8[i], lbl_806D05F0[i], lbl_806D0600[i], 0, k);
            } else {
                TEXBindPaletteEntry_RGB(lbl_806D05F8[i], lbl_806D05F0[i], k);
            }
        }
    }
    DebugPrintf(lbl_803DA6C0);
}

void TireSprite_Draw(TireSprite *s) {
    Mtx m;

    if (lbl_806D05F0[0] == 0) {
        LoadTireSprites();
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
    const float *uv = (const float *)lbl_803DA680;
    TireSprite *p = s;
    for (int i = 0; i < 2; i++) {
        GXFIFO.f32 = p->vx[0];
        GXFIFO.f32 = p->vy[0];
        GXFIFO.f32 = p->vz[0];
        GXFIFO.u32 = color;
        GXFIFO.f32 = u + uv[0];
        GXFIFO.f32 = v + uv[1];
        GXFIFO.f32 = u + uv[0];
        GXFIFO.f32 = v + uv[1];
        GXFIFO.f32 = p->vx[1];
        GXFIFO.f32 = p->vy[1];
        GXFIFO.f32 = p->vz[1];
        GXFIFO.u32 = color;
        GXFIFO.f32 = u + uv[2];
        GXFIFO.f32 = v + uv[3];
        GXFIFO.f32 = u + uv[2];
        GXFIFO.f32 = v + uv[3];
        uv += 4;
        p = (TireSprite *)((char *)p + 8);
    }
    HSD_StateInvalidate(-1);
}

void TireSprite_Queue(TireSprite *s) {
    if (s && s->visible && !(s->alpha <= 0.0f)) {
        void *man = lbl_806D10AC;
        if (man == 0) {
            man = 0;
        }
        clDrawMan_AddSorted_DepthRange(man, TireSprite_Draw, s, s->px, s->py - 1.0f, s->pz, 0.0f);
    }
}

void TireSprite_Release() {
    for (int i = 0; i < 2; i++) {
        if (lbl_806D05F8[i]) {
            TEXReleasePalette(&lbl_806D05F8[i]);
            lbl_806D05F8[i] = 0;
        }
        if (lbl_806D05F0[i]) {
            MemoryManager_Free(lbl_806D05F0[i]);
            lbl_806D05F0[i] = 0;
        }
        if (lbl_806D0600[i]) {
            MemoryManager_Free(lbl_806D0600[i]);
            lbl_806D0600[i] = 0;
        }
    }
}

void TireSprite_Load() {
    LoadTireSprites();
}

void EnemyFace_Request(KartRender *kart, int arg) {
    if (kart == 0) {
        return;
    }
    if (*((unsigned char *)kart + 0x2D0) == 1) {
        return;
    }
    for (int i = 0; i < 4; i++) {
        if (lbl_80679CA0[i].kart == 0) {
            lbl_80679CA0[i].kart = kart;
            lbl_80679CA0[i].arg = arg;
            return;
        }
    }
}

void clEnemyFace::Enable(int on) {
    if (state < 2) {
        state = 2;
    }
}

void clEnemyFace::Draw() {
    if (!IsRaceStarted() || state >= 3) {
        return;
    }
    Sort();
    GetCourseScene3D();
    for (int i = 0; i < 4; i++) {
        int k = order[i];
        if (faces[k]) {
            icons[k]->Reset();
            rings[k]->Reset();
            faces[k]->x = world[k].x;
            faces[k]->y = world[k].y;
            faces[k]->z = world[k].z;
            icons[k]->Place(&screen[k]);
            rings[k]->Place(&screen[k]);
            faces[k]->scale = faceScale[k];
            icons[k]->scale = iconScale[k];
            rings[k]->scale = iconScale[k];
        }
    }
    for (int i = 0; i < 4; i++) {
        if (faces[order[i]]) {
            faces[order[i]]->model->Draw();
        }
    }
}

static inline bool KartHidden(KartRender *k) {
    return (k->flags->bits & 0x8000000000ULL) != 0;
}

void clEnemyFace::Update() {
    if (!IsRaceStarted()) {
        return;
    }
    switch (state) {
    case 2:
        state = 3;
        break;
    case 3:
        return;
    }
    if (state >= 3) {
        return;
    }
    for (int i = 0; i < 4; i++) {
        if (lbl_80679CA0[i].kart) {
            for (int k = 0; k < 4; k++) {
                if (faces[k] && karts[k] == lbl_80679CA0[i].kart) {
                    faces[k]->model->Trigger(lbl_80679CA0[i].arg);
                    break;
                }
            }
            lbl_80679CA0[i].kart = 0;
        }
    }
    for (int i = 0; i < 4; i++) {
        int k = order[i];
        clEFace3D *f = faces[k];
        if (f) {
            if (KartHidden(f->kart) == 1) {
                f->model->scale = 0.0f;
                f->model->sub->scale = 0.0f;
                f->model->Update();
            } else {
                f->model->x = f->x;
                f->model->y = f->y;
                f->model->z = f->z;
                float s = 1.224f * f->scale;
                f->model->scale = s;
                f->model->sub->scale = s;
                f->model->Update();
            }
            icons[k]->Update();
            rings[k]->Update();
        }
    }
}

void clEnemyFace::Sort() {
    void *scene = GetCourseScene3D();
    if (scene == 0) {
        return;
    }
    void *cobj = *(void **)((char *)scene + 4);
    HSD_CObjGetNear(cobj);
    HSD_CObjGetFar(cobj);
    Vec3c eye;
    CObj_LoadProjMatrix(scene, &eye);
    KartRender *player = g_playerRenderObj;
    for (int i = 0; i < 4; i++) {
        if (karts[i]) {
            const float *m = KartDriver_GetKartRootMtx(karts[i]);
            world[i].x = m[3];
            world[i].y = 60.0f + m[7];
            world[i].z = m[11];
            float w;
            Vec3f p = *(Vec3f *)&world[i];
            CObj_ProjectPoint(scene, &screen[i].x, &screen[i].y, &w, &screen[i].z, p.x, p.y, p.z);
            if (screen[i].z > 1.0f) {
                iconScale[i] = 0.0f;
                faceScale[i] = 0.0f;
            } else if (karts[i]->active == 0) {
                iconScale[i] = 0.0f;
                faceScale[i] = 0.0f;
                dist[i] = 0.0f;
            } else {
                float d = -1.0f * w;
                if (d > 3000.0f || d < 60.0f) {
                    iconScale[i] = 0.0f;
                    faceScale[i] = 0.0f;
                    dist[i] = 0.0f;
                } else {
                    faceScale[i] = (500.0f + d) / 1000.0f;
                    iconScale[i] = (2500.0f - d) / 2500.0f;
                    world[i].y = -(15.0f * iconScale[i] - world[i].y);
                    p.y = 38.0f * faceScale[i] + world[i].y;
                    CObj_ProjectPoint(scene, &screen[i].x, &screen[i].y, &w, &screen[i].z, p.x, p.y, p.z);
                    float dx = m[3] - KartDriver_GetKartRootMtx(player)[3];
                    float dz = m[11] - KartDriver_GetKartRootMtx(player)[11];
                    dist[i] = dx * dx + dz * dz;
                }
            }
        }
    }
    order[0] = 0;
    order[1] = 1;
    order[2] = 2;
    order[3] = 3;
    for (int i = 0; i < 3; i++) {
        for (int j = i + 1; j < 4; j++) {
            if (dist[i] < dist[j]) {
                int t = order[i];
                order[i] = order[j];
                order[j] = t;
            }
        }
    }
}

void EnemyFace_Preload() {
    PreloadResource(0xC2F);
    PreloadResource(0xC30);
    PreloadResource(0xC31);
    PreloadResource(0xC29);
    PreloadResource(0xC49);
    PreloadResource(0xC32);
}

clEnemyFace *EnemyFace_Create(void *path, int param) {
    return new clEnemyFace(path, param);
}

clEnemyFace::~clEnemyFace() {
    for (int i = 3; i >= 0; i--) {
        if (faces[i]) {
            delete faces[i];
            faces[i] = 0;
            delete icons[i];
            icons[i] = 0;
            delete rings[i];
            rings[i] = 0;
        }
    }
}

clEnemyFace::clEnemyFace(void *path, int p) : state(1), param(p), holder(0) {
    for (int i = 0; i < 4; i++) {
        karts[i] = 0;
        faces[i] = 0;
        icons[i] = 0;
        rings[i] = 0;
        order[i] = 0;
    }
    if (path == 0) {
        return;
    }
    for (int i = 0; i < 4; i++) {
        PathEntry *e = PathManager_GetEntrySubStruct(path, i);
        karts[i] = 0;
        if (e && e->id != -1) {
            int slot = e->kart->slot;
            if (slot != GetDisplayBufferIndex(e->kart) && slot != 6) {
                karts[i] = e->kart;
                clEFace3D *f = new clEFace3D(e->kart, param);
                if (f) {
                    if (g_gameMode == 2 && !fn_80231644(&f->b, &f->a, &f->c, f->slot, e->kart->course)) {
                        f->a = fn_80231BD4(6, e->kart->course, 0);
                    }
                    f->model = new clEFaceModel(e->kart, f->a, f->b, f->c);
                }
                faces[i] = f;
                icons[i] = new FaceIcon(e->kart, param);
                rings[i] = new FaceRing(e->kart, param);
            }
        }
        dist[i] = 0.0f;
        order[i] = i;
        iconScale[i] = 1.0f;
        lbl_80679CA0[i].kart = 0;
        lbl_80679CA0[i].arg = 0;
    }
}

clEFace3D::~clEFace3D() {
    delete model;
}

void clEFaceModel::Trigger(int arg) {
    sub->Reset();
    for (int i = 0; i < 2; i++) {
        clNormal3D_SetScale(models[i], 0, 0.0f, 1.0f, 0.0f, 0.0f);
    }
    state = 0;
}
