/*
 * 0x80171754..0x8017218C: clLensFlare, a screen-space flare that follows a
 * world position: draw, update (projects the anchor to the screen and fades
 * in or out), destructor and two constructors. Real C++ ctors for their EH
 * actions. Deferred generation emits the definitions in reverse source order;
 * the compiler owns the vtable and RTTI. Mangled names are bridged in
 * tools/extab_user_renames.json.
 */

#include "game/types/Vec3f.h"

struct HSD_JObj {
    char pad00[0x14];
    unsigned int flags;
    char pad18[0x20];
    Vec3f translate;
};

#include "game/types/HSD_DObj.h"

struct GXRenderModeObj {
    unsigned int viTVmode;
    unsigned short fbWidth;
    unsigned short efbHeight;
    unsigned short xfbHeight;
};

struct ProjParams {
    float x0;
    float pad04;
    float x8;
    char pad0C[0x18];
    float x24;
    float x28;
};

#include "game/types/clNormal3D.h"

struct FlareState {
    unsigned char visible;
    char pad01;
    short x;
    short y;
    char pad06[0x2];
    unsigned int frame;

    FlareState();
    ~FlareState();
};

#include "game/types/clMapEffectParts.h"

struct clLensFlare : clMapEffectParts {
    float screenW;
    float screenH;
    Vec3f pos;
    Vec3f edge;
    Vec3f edgeNeg;
    clNormal3D *model;
    HSD_DObj *dobjs[10];
    int dobjCount;
    int alpha;
    float scale;
    float spread;
    FlareState state;

    clLensFlare(const char *res, HSD_JObj *at, float scale, float spread);
    clLensFlare(const char *res, float x, float y, float z, float scale, float spread);
    virtual ~clLensFlare();
    virtual void Update();
    virtual void Draw();
};

extern "C" {
extern char lbl_806D8D80[7];
extern char lbl_806D8D88[5];
extern GXRenderModeObj HSD_VIData;
void __assert(char *, int, char *);
void DebugPrintf(const char *, ...);
void Object_DtorWithGXSync(void *, int);
void dtor_8018F088(void *, int);
void MemoryManager_TimedFree(void *);
void *Archive_GetRootJObj(void *);
HSD_DObj *HSD_JObjGetDObj(void *);
void fn_801825FC(void);
void fn_801825C8(void);
void fn_80182644(void *, unsigned int);
void fn_80182578(void *, int);
void HSD_DObjSetFlags(HSD_DObj *, int);
void HSD_DObjClearFlags(HSD_DObj *, int);
void Object_SetJObjScaleXYZ(void *, float, float, float);
void Object_SetJObjPositionXYZ(void *, float, float, float);
void Object_RenderJObjTree(void *, int);
void Object_SetJObjRotationZ(void *, float);
void *GetCourseScene3D(void);
void *CObj_GetViewMatrix_Cached(void *);
void *CObj_GetProjMatrix_Cached(void *);
ProjParams *CObj_GetLineBufferPtr(void *);
void PSMTXMultVec(void *, Vec3f *, Vec3f *);
void Vec3_Subtract(Vec3f *, Vec3f *, Vec3f *);
double atan2(double, double);
}

static inline void HSD_JObjGetTranslation(HSD_JObj *jobj, Vec3f *translate) {
    if (jobj == 0) {
        __assert(lbl_806D8D80, 0x3E4, lbl_806D8D88);
    }
    if (translate == 0) {
        __assert(lbl_806D8D80, 0x3E5, "translate");
    }
    *translate = jobj->translate;
}

static inline void *HSD_DObjGetMObj(HSD_DObj *dobj) {
    return dobj ? dobj->mobj : 0;
}

static inline HSD_DObj *HSD_DObjGetNext(HSD_DObj *dobj) {
    if (dobj != 0) {
        return dobj->next;
    }
    return 0;
}

clLensFlare::clLensFlare(const char *res, float x, float y, float z, float scale, float spread) {
    HSD_DObj *dobj;

    DebugPrintf(" CreateMapEffect : clLensFlare\n");
    model = 0;
    dobjs[0] = 0;
    dobjs[1] = 0;
    dobjs[2] = 0;
    dobjs[3] = 0;
    dobjs[4] = 0;
    dobjs[5] = 0;
    dobjs[6] = 0;
    dobjs[7] = 0;
    dobjs[8] = 0;
    dobjs[9] = 0;
    dobjCount = 0;
    alpha = 0xFF;
    pos.x = 0.0f;
    pos.y = 0.0f;
    pos.z = 0.0f;
    edge.x = 0.0f;
    edge.y = 0.0f;
    edge.z = 0.0f;
    edgeNeg.x = 0.0f;
    edgeNeg.y = 0.0f;
    edgeNeg.z = 0.0f;
    state.visible = 0;
    pos.x = x;
    pos.y = y;
    pos.z = z;
    this->scale = scale;
    this->spread = spread;
    screenW = HSD_VIData.fbWidth;
    screenH = HSD_VIData.xfbHeight;
    fn_801825FC();
    model = new clNormal3D(res, 0);
    fn_801825C8();
    if (model) {
        Object_SetJObjScaleXYZ(model, 0.01f, 0.01f, 0.01f);
        for (dobj = HSD_JObjGetDObj(Archive_GetRootJObj(model)); dobj; dobj = HSD_DObjGetNext(dobj)) {
            if (dobjCount < 10) {
                fn_80182644(HSD_DObjGetMObj(dobj), 0x28000000);
                dobjs[dobjCount] = dobj;
                dobjCount++;
            } else {
                HSD_DObjSetFlags(dobj, 1);
            }
        }
    }
}


clLensFlare::clLensFlare(const char *res, HSD_JObj *at, float scale, float spread) {
    HSD_DObj *dobj;

    DebugPrintf(" CreateMapEffect : clLensFlare\n");
    model = 0;
    dobjs[0] = 0;
    dobjs[1] = 0;
    dobjs[2] = 0;
    dobjs[3] = 0;
    dobjs[4] = 0;
    dobjs[5] = 0;
    dobjs[6] = 0;
    dobjs[7] = 0;
    dobjs[8] = 0;
    dobjs[9] = 0;
    dobjCount = 0;
    alpha = 0xFF;
    pos.x = 0.0f;
    pos.y = 0.0f;
    pos.z = 0.0f;
    edge.x = 0.0f;
    edge.y = 0.0f;
    edge.z = 0.0f;
    edgeNeg.x = 0.0f;
    edgeNeg.y = 0.0f;
    edgeNeg.z = 0.0f;
    state.visible = 0;
    this->scale = scale;
    this->spread = spread;
    if (at) {
        HSD_JObjGetTranslation(at, &pos);
        screenW = HSD_VIData.fbWidth;
        screenH = HSD_VIData.xfbHeight;
        fn_801825FC();
        model = new clNormal3D(res, 0);
        fn_801825C8();
        if (model) {
            Object_SetJObjScaleXYZ(model, 0.01f, 0.01f, 0.01f);
            for (dobj = HSD_JObjGetDObj(Archive_GetRootJObj(model)); dobj; dobj = HSD_DObjGetNext(dobj)) {
                if (dobjCount < 10) {
                    fn_80182644(HSD_DObjGetMObj(dobj), 0x28000000);
                    dobjs[dobjCount] = dobj;
                    dobjCount++;
                } else {
                    HSD_DObjSetFlags(dobj, 1);
                }
            }
        }
    }
}

clLensFlare::~clLensFlare() {
    if (model) {
        Object_DtorWithGXSync(model, 1);
        model = 0;
    }
    DebugPrintf(" DeleteMapEffect : clLensFlare\n");
}

void clLensFlare::Update() {
    void *scene;
    void *view;
    void *proj;
    ProjParams *pp;
    Vec3f v;
    float halfW;
    float halfH;
    int a;

    if (model == 0) {
        state.visible = 0;
        return;
    }
    scene = GetCourseScene3D();
    if (scene == 0) {
        state.visible = 0;
        return;
    }
    view = CObj_GetViewMatrix_Cached(scene);
    proj = CObj_GetProjMatrix_Cached(scene);
    pp = CObj_GetLineBufferPtr(scene);
    PSMTXMultVec(view, &pos, &v);
    if (v.z > 0.0f) {
        state.visible = 0;
        alpha -= 0x20;
        a = alpha;
        alpha = a < 0 ? 0 : (a > 0xFF ? 0xFF : a);
        return;
    }
    halfW = -v.z * pp->x8 / pp->x0;
    halfH = -v.z * pp->x28 / pp->x24;
    edge.x = pp->x8 / pp->x0 * (v.x / halfW);
    edge.y = pp->x28 / pp->x24 * (v.y / halfH);
    edge.z = -1.0f;
    edgeNeg.x = -edge.x;
    edgeNeg.y = -edge.y;
    edgeNeg.z = -1.0f;
    PSMTXMultVec(proj, &edge, &edge);
    PSMTXMultVec(proj, &edgeNeg, &edgeNeg);
    Vec3_Subtract(&edgeNeg, &edge, &edgeNeg);
    Object_SetJObjRotationZ(model, 4.712389f + (float)atan2(v.y, v.x));
    if (state.frame < 0xFFFD34) {
        alpha -= 0x20;
    } else {
        alpha += 0x20;
    }
    a = alpha;
    alpha = a < 0 ? 0 : (a > 0xFF ? 0xFF : a);
    if (v.x < halfW || v.x > -halfW || v.y > halfH || v.y < -halfH) {
        state.visible = 0;
    } else {
        float d;
        d = (v.x - halfW) / (2.0f * halfW);
        if (d < 0.0f) {
            d = -d;
        }
        state.x = 640.0f * d;
        d = (v.y - halfH) / (2.0f * halfH);
        if (d < 0.0f) {
            d = -d;
        }
        state.y = 480.0f * d;
        state.visible = 1;
    }
}

void clLensFlare::Draw() {
    int j;
    int frame;
    int i;
    float t;

    if (model != 0 && alpha != 0) {
        frame = (int)((float)alpha * spread);
        for (i = 0; i < dobjCount; i++) {
            if (dobjs[i]) {
                for (j = 0; j < dobjCount; j++) {
                    if (j == i) {
                        HSD_DObjClearFlags(dobjs[j], 1);
                    } else {
                        HSD_DObjSetFlags(dobjs[j], 1);
                    }
                }
                fn_80182578(HSD_DObjGetMObj(dobjs[i]), frame);
                if (i < 2) {
                    t = 0.0f;
                } else {
                    t = (float)(i - 1) / (float)(dobjCount - 2);
                }
                Object_SetJObjPositionXYZ(model, edgeNeg.x * t + edge.x,
                                          edgeNeg.y * t + edge.y,
                                          edgeNeg.z * t + edge.z);
                t = scale * (0.01f * (1.5f * ((float)i / (float)dobjCount) + 1.0f));
                Object_SetJObjScaleXYZ(model, t, t, t);
                Object_RenderJObjTree(model, 7);
            }
        }
    }
}
