#ifndef GAME_DEMOKARTSCENE_H
#define GAME_DEMOKARTSCENE_H

/*
 * Kart demo scenes (0x8020F44C..0x80210A50): a course scene, a kart driver
 * with its tornado effect and some extra models, run for a fixed time with
 * a fade in / fade out.
 *
 *   DemoRoot (ctor GameMode_BaseInit, dtor dtor_8002CDF4)
 *     DemoBase (vtable lbl_80419F0C, inline)
 */

void *operator new(unsigned long size);
void operator delete(void *p) throw();

typedef float Mtx[3][4];

struct Vec {
    float x;
    float y;
    float z;
};

struct HSD_JObj {
    char pad00[0x14];
    unsigned int flags;
    char pad18[0x38 - 0x18];
    float tx;
    float ty;
    float tz;
    Mtx mtx;
};

struct DemoAnimLeaf {
    void *value;
};
struct DemoAnimNode {
    void *opaque;
    DemoAnimLeaf *next;
};
struct DemoDescriptor {
    void *opaque;
    DemoAnimNode *next;
};

static inline void *leaf_value(DemoAnimLeaf *leaf) {
    if (leaf == 0) {
        return 0;
    }
    return leaf->value;
}
static inline void *node_value(DemoAnimNode *node) {
    if (node == 0) {
        return 0;
    }
    return leaf_value(node->next);
}
static inline void *descriptor_value(DemoDescriptor *descriptor) {
    if (descriptor == 0) {
        return 0;
    }
    return node_value(descriptor->next);
}

extern "C" {
void HSD_CObjAddAnim(void *cobj, void *anim);
void HSD_CObjReqAnim(void *cobj, float frame);
void HSD_CObjAnim(void *cobj);
}

/* Scene3D (0x3090 bytes, ctor Scene3D_Init). */
struct DemoSceneBase {
    virtual ~DemoSceneBase();
    virtual unsigned char Ready();
    virtual void Render();
    void *camera;
    unsigned char opaque8[0x2C - 0x8];
    DemoDescriptor *descriptor;
    unsigned char opaque30[0x3084 - 0x30];
    unsigned char active;
    DemoSceneBase(const char *path);
};

/* Course scene with a camera animation (vtable lbl_80419EF8). */
struct DemoScene : DemoSceneBase {
    float speed;
    float frame;
    DemoScene(const char *path, float s, float f) : DemoSceneBase(path) {
        speed = s;
        frame = f;
    }
    virtual ~DemoScene();
    void Start(float f, float s) {
        if (camera) {
            active = 1;
            frame = f;
            speed = s;
            HSD_CObjAddAnim(camera, descriptor_value(descriptor));
            HSD_CObjReqAnim(camera, frame);
            HSD_CObjAnim(camera);
        }
    }
    void Tick(float still) {
        if (still != speed) {
            if (active) {
                active = 0;
            } else {
                frame += speed;
            }
            HSD_CObjReqAnim(camera, frame);
            HSD_CObjAnim(camera);
        }
    }
};

struct DemoNormal {
    unsigned char opaque[0x24];
    void *archive;
    unsigned char opaque28[0x5C - 0x28];
    DemoNormal(const char *path, int flags);
};

struct DemoDriverBase {
    unsigned char opaque[0x384];
    DemoDriverBase(int disp, int character, Mtx matrix, int a, int b, int c);
};

extern "C" int GetDisplayBufferIndex(void);

struct DemoDriver : DemoDriverBase {
    DemoDriver(int character, Mtx matrix) : DemoDriverBase(GetDisplayBufferIndex(), character, matrix, 0, 0, 0) {}
};

struct DemoTornado {
    unsigned char opaque[0x154];
    DemoTornado(unsigned char a, DemoDriver *driver, int character, unsigned char b, float x, float y, float z);
};

struct DemoRoot {
    DemoRoot();
    virtual int Update();
    virtual void Draw();
    virtual ~DemoRoot();
};

struct DemoBase : DemoRoot {
    DemoBase() {}
    virtual ~DemoBase() {}
    virtual void _keyB();
};

struct DrawMan {
    virtual ~DrawMan();
};

struct InputPlayer {
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void v3();
    virtual void v4();
    virtual void v5();
    virtual unsigned char Pressed(int mask);
};

extern "C" {
extern DrawMan *lbl_806D10AC;
extern int g_characterId;
extern unsigned char g_lakituStartAnimDone;
extern void *g_raceCamera;
extern void *g_playerRenderObj;
void __assert(char *file, int line, char *expr);
void *GetInputManager(void);
InputPlayer *InputMgr_GetPlayer(void *mgr, int index);
void PSMTXIdentity(Mtx m);
void PSMTXScale(Mtx m, float x, float y, float z);
void PSMTXConcat(const Mtx a, const Mtx b, Mtx ab);
void PSVECCrossProduct(const Vec *a, const Vec *b, Vec *axb);
void Vec3_Subtract(const Vec *a, const Vec *b, Vec *out);
float Vec3_Magnitude(const Vec *v);
void Vec3_Normalize(const Vec *v, Vec *out);
double asin(double x);
void HSD_JObjSetupMatrixSub(HSD_JObj *jobj);
void HSD_StateInvalidate(int state);
void SetResourceLoadingFlag(unsigned char on);
DrawMan *DrawManager_GetOrCreate(void);
void DMAChannelManager_Init(void);
void SoundChannels_ClearAll(void);
void ItemObjectManager_Init(void);
void ItemObjectManager_Update(void);
void ItemObjectManager_Render(void);
void ItemObjectManager_Reset(void);
void CourseObjectManager_Init(void);
void ProcessSystemTick(int arg);
unsigned char clNormal3D_SetScale(DemoNormal *n, void *a, float x, float y, float z, float w);
void clNormal3D_Exec(DemoNormal *n);
void Object_SetField8_AndDirty(DemoNormal *n, float t);
void Object_RenderJObjTree(DemoNormal *n, int mask);
void Object_DriveAnimMatrix(DemoNormal *n);
void Object_DtorWithGXSync(DemoNormal *n, int del);
HSD_JObj *ResolveJointByName(DemoNormal *n, const char *name);
void SetCourseScene3D(DemoSceneBase *scene);
int SceneDrawList_RegisterArchive(void *archive, int layer);
void SceneDrawList_Reset(void);
void TransparentDraw_RemoveByOwner(int handle);
void TransparentDraw_SortAndDispatch(void);
void SetActiveCamera(int a, int b);
void SetPlayerCarObject(void *obj);
void clDrawMan_Buckets_Reset(DrawMan *dm);
void clDrawMan_EndFrame_NoOp(DrawMan *dm);
void clDrawMan_Buckets_Dispatch(DrawMan *dm);
void CObj_DebugVizPathFlush(DemoSceneBase *scene);
void CObj_LoadProjMatrix(DemoSceneBase *scene, Vec *out);
void CObj_ApplyScissor(DemoSceneBase *scene, Vec *out);
void fn_8016B0C4(void);
void fn_80181790(DemoSceneBase *scene, int a, float f, int b, int c, unsigned char alpha, int d);
void KartDriver_RenderTimed(DemoDriver *driver, int a, int b);
void KartDriver_Dtor(DemoDriver *driver, int del);
void RenderObj_ItemStateMachine_Timed(DemoDriver *driver, int a, float b, float c);
void TornadoEffect_Tick(DemoTornado *t, int disp);
void VisualEffectHolder_Dtor(DemoTornado *t, int del);
void DrawEffect_TickAndCull(void);
void VfxSlotMgr_Update(Vec eye, Vec target);
void VfxSlotMgr_Shutdown(void);
void ClRomTable_PurgeAll(void);
void clRom_PurgeAll(void);
}

static inline DrawMan *GetDrawMan() {
    return lbl_806D10AC == 0 ? (DrawMan *)0 : lbl_806D10AC;
}

static inline float DemoClamp(float v, float lo, float hi) {
    if (v < lo) {
        return lo;
    }
    if (v > hi) {
        return hi;
    }
    return v;
}

#endif
