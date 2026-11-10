/*
 * 0x8022ACE4..0x8022BFA8: clEnemyFace (rival face icons drawn over the
 * nearest opponents) plus the tire-sprite quad renderer that shares the
 * TU. The TU owns .rodata 0x803DA278..0x803DA710.
 */

#include "game/types/size_t.h"
void *operator new(size_t size);
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
#ifdef ENEMYFACE_INLINE_VEC_DTOR
    Vec3c(float a, float b, float c) : x(a), y(b), z(c) {}
    ~Vec3c() {}
#else
    ~Vec3c();
#endif
};

#include "game/types/Vec3f.h"

#include "game/types/KartFlags.h"

struct KartRender {
    char pad0[0x1E8];
    int active;
    char pad1EC[0x1F4 - 0x1EC];
    int slot;
    int course;
    char pad1FC[0x304 - 0x1FC];
    KartFlags *flags;
};

static inline bool KartHidden(KartRender *k) {
    return (k->flags->bits & 0x8000000000ULL) != 0;
}

struct PathEntry {
    char pad0[4];
    int id;
    char pad8[0x90 - 8];
    KartRender *kart;
};

#include "game/types/TireSprite.h"

#include "game/types/FaceSprite.h"

struct FaceIcon : FaceSprite {
    virtual ~FaceIcon();
    FaceIcon(KartRender *kart, int param);
    void Reset();
    void Place(Vec3c *screen);
    void Update();
};

struct FaceRing : FaceSprite {
    virtual ~FaceRing();
    FaceRing(KartRender *kart, int param);
    void Reset();
    void Place(Vec3c *screen);
    void Update();
};

#include "game/types/FaceModelSub.h"

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

#include "game/types/FaceHolder.h"

#include "game/types/clCDispInterface.h"

struct clEnemyFace : clCDispInterface {
#ifdef ENEMYFACE_INLINE_VEC_DTOR
    virtual void _EnemyFaceKey();
#endif
    virtual void Update();
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

extern const unsigned int EnemyFace_rodata_803DA278[258];
extern const unsigned int lbl_803DA680[8];
extern const char lbl_803DA6A0[0x20];
extern const char lbl_803DA6C0[0x20];
extern const char lbl_803DA6E0[0xC];
extern const char lbl_803DA6EC[0x14];
extern const char lbl_803DA700[0x10];

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

