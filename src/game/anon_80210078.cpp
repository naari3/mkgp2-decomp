/*
 * 0x80210078..0x80210A50: kart demo scene on a course with collision and a
 * line of coins.
 */

#include "game/DemoKartScene.h"

struct LineBuffer {
    unsigned int words[12];
    float rect[4];
    unsigned int tail[2];
};

struct DemoCollision {
    char pad[8];
    void *data;
    DemoCollision(const char *file);
};

struct CoinEntry {
    float x;
    float y;
    float z;
    int active;
};

struct CoinSet {
    CoinEntry entries[50];
    char pad320[0x32C - 0x320];
    int mode;
};

extern "C" {
extern const char *lbl_806D03B8;
extern const char *lbl_806D03BC;
extern const char *lbl_806D03C0;
extern const char lbl_803C384C[];
extern char lbl_806DAD54[7];
extern char lbl_806DAD5C[5];
int sprintf(char *s, const char *format, ...);
LineBuffer *CObj_GetLineBufferPtr(DemoSceneBase *scene);
void *CObj_GetViewMatrix_Cached(DemoSceneBase *scene);
void fn_80137C8C(void *view, LineBuffer *buf);
void fn_80139810(void);
void fn_8013A534(void);
void fn_8013A6F8(void);
void fn_80138D48(void);
const char *GetCollisionFilename(void);
void Collision_SetGlobalData(void *data, int arg);
void fn_801F98E8(DemoCollision *c, int del);
void CoinSystem_Init(CoinSet *coins, int arg);
}

static inline float HSD_JObjGetTranslationX(HSD_JObj *jobj) {
    if (jobj == 0) {
        __assert(lbl_806DAD54, 0x3F1, lbl_806DAD5C);
    }
    return jobj->tx;
}

static inline float HSD_JObjGetTranslationY(HSD_JObj *jobj) {
    if (jobj == 0) {
        __assert(lbl_806DAD54, 0x3FD, lbl_806DAD5C);
    }
    return jobj->ty;
}

static inline float HSD_JObjGetTranslationZ(HSD_JObj *jobj) {
    if (jobj == 0) {
        __assert(lbl_806DAD54, 0x409, lbl_806DAD5C);
    }
    return jobj->tz;
}

static inline void SetupJointMatrix(HSD_JObj *jobj) {
    if (jobj == 0) {
        __assert(lbl_806DAD54, 0x47C, lbl_806DAD5C);
    }
    if (jobj != 0) {
        if (jobj == 0) {
            __assert(lbl_806DAD54, 0x25D, lbl_806DAD5C);
        }
        unsigned int flags = jobj->flags;
        unsigned char dirty = 0;
        if (!(flags & 0x00800000) && (flags & 0x40)) {
            dirty = 1;
        }
        if (dirty) {
            HSD_JObjSetupMatrixSub(jobj);
        }
    }
}

struct CoinDemoScene : DemoBase {
    unsigned char first;
    float time;
    DemoScene *scene;
    int drawHandle;
    DemoNormal *normal;
    DemoCollision *collision;
    DemoDriver *driver;
    DemoTornado *tornado;
    Mtx matrix;
    HSD_JObj *joint;
    CoinSet coins;
    CoinDemoScene();
    virtual int Update();
    virtual void Draw();
    virtual ~CoinDemoScene();
};

void CoinDemoScene::Draw() {
    if (scene->Ready() == 1) {
        clDrawMan_Buckets_Reset(GetDrawMan());
        TransparentDraw_SortAndDispatch();
        CObj_DebugVizPathFlush(scene);
        LineBuffer buf = *CObj_GetLineBufferPtr(scene);
        buf.rect[0] += 20.0f;
        buf.rect[1] += 20.0f;
        buf.rect[2] += 20.0f;
        buf.rect[3] += 20.0f;
        fn_80137C8C(CObj_GetViewMatrix_Cached(scene), &buf);
        fn_8016B0C4();
        Object_RenderJObjTree(normal, 7);
        KartDriver_RenderTimed(driver, 0, 1);
        fn_80139810();
        ItemObjectManager_Render();
        DrawEffect_TickAndCull();
        clDrawMan_EndFrame_NoOp(GetDrawMan());
        clDrawMan_Buckets_Dispatch(GetDrawMan());
        float t = time;
        unsigned char alpha = 0;
        if (t < 30.0f) {
            alpha = 255.0f - 255.0f * DemoClamp(t / 30.0f, 0.0f, 1.0f);
        }
        if (t > 270.0f) {
            alpha = 255.0f - 255.0f * DemoClamp((300.0f - t) / 30.0f, 0.0f, 1.0f);
        }
        if (alpha) {
            fn_80181790(scene, 0, 1.0f, 0, 0, alpha, 0);
        }
        scene->Render();
        HSD_StateInvalidate(0x7F);
    }
}

int CoinDemoScene::Update() {
    if (first) {
        first = 0;
    } else {
        if ((time += 1.0f) >= 300.0f) {
            return 0xF;
        }
    }
    Object_SetField8_AndDirty(normal, time);
    clNormal3D_Exec(normal);
    {
        DemoScene *s = scene;
        float t = time;
        if (!(s->frame < 0.0f) && !(t < 0.0f)) {
            s->active = 1;
            s->frame = t;
        }
    }
    scene->Tick(-1.0f);
    Vec prev;
    prev.x = matrix[0][3];
    prev.y = matrix[1][3];
    prev.z = matrix[2][3];
    PSMTXScale(matrix, 1.45f, 1.45f, 1.45f);
    HSD_JObj *j = joint;
    SetupJointMatrix(j);
    PSMTXConcat(j->mtx, matrix, matrix);
    Vec cur;
    cur.x = matrix[0][3];
    cur.y = matrix[1][3];
    cur.z = matrix[2][3];
    Vec d;
    Vec3_Subtract(&cur, &prev, &d);
    float dist = Vec3_Magnitude(&d);
    if (0.0f != dist && time > 0.0f) {
        Vec fwd;
        fwd.x = matrix[0][2];
        fwd.y = matrix[1][2];
        fwd.z = matrix[2][2];
        Vec3_Normalize(&d, &d);
        Vec3_Normalize(&fwd, &fwd);
        Vec c;
        PSVECCrossProduct(&d, &fwd, &c);
        asin(c.x + c.y + c.z);
    }
    float speed = 0.06981111f * dist;
    RenderObj_ItemStateMachine_Timed(driver, 0, 0.0f, speed);
    TornadoEffect_Tick(tornado, GetDisplayBufferIndex());
    fn_8013A534();
    Vec eye;
    Vec target;
    CObj_LoadProjMatrix(scene, &eye);
    CObj_ApplyScissor(scene, &target);
    ItemObjectManager_Update();
    VfxSlotMgr_Update(eye, target);
    return InputMgr_GetPlayer(GetInputManager(), 0)->Pressed(0x400) ? 0xF : -2;
}

CoinDemoScene::~CoinDemoScene() {
    SetActiveCamera(0, 0);
    if (drawHandle >= 0) {
        TransparentDraw_RemoveByOwner(drawHandle);
    }
    fn_8013A6F8();
    SetPlayerCarObject(0);
    SetCourseScene3D(0);
    delete scene;
    fn_801F98E8(collision, 1);
    Object_DtorWithGXSync(normal, 1);
    VisualEffectHolder_Dtor(tornado, 1);
    KartDriver_Dtor(driver, 1);
    ItemObjectManager_Reset();
    VfxSlotMgr_Shutdown();
    ClRomTable_PurgeAll();
    SceneDrawList_Reset();
    delete lbl_806D10AC;
    lbl_806D10AC = 0;
    SetResourceLoadingFlag(0);
    clRom_PurgeAll();
}

CoinDemoScene::CoinDemoScene() {
    first = 1;
    time = 0.0f;
    scene = 0;
    drawHandle = -1;
    normal = 0;
    driver = 0;
    tornado = 0;
    joint = 0;
    PSMTXIdentity(matrix);
    SetResourceLoadingFlag(0);
    DrawManager_GetOrCreate();
    DMAChannelManager_Init();
    SoundChannels_ClearAll();
    ItemObjectManager_Init();
    CourseObjectManager_Init();
    scene = new DemoScene(lbl_806D03B8, -1.0f, 0.0f);
    scene->Start(0.0f, 1.0f);
    normal = new DemoNormal(lbl_806D03B8, 0);
    clNormal3D_SetScale(normal, 0, 0.0f, 1.0f, 0.0f, 0.0f);
    ProcessSystemTick(0);
    collision = new DemoCollision(GetCollisionFilename());
    Collision_SetGlobalData(collision->data, 0);
    driver = new DemoDriver(g_characterId, matrix);
    tornado = new DemoTornado(0, driver, g_characterId, 0, 0.0f, 0.0f, 0.0f);
    joint = ResolveJointByName(normal, lbl_806D03BC);
    ProcessSystemTick(0);
    g_raceCamera = 0;
    g_lakituStartAnimDone = 0;
    SetCourseScene3D(scene);
    drawHandle = SceneDrawList_RegisterArchive(normal->archive, 4);
    SetResourceLoadingFlag(1);
    for (int i = 0; i < 50; i++) {
        char name[0x40];
        sprintf(name, lbl_803C384C, lbl_806D03C0, i);
        HSD_JObj *jobj = ResolveJointByName(normal, name);
        if (jobj) {
            coins.entries[i].x = HSD_JObjGetTranslationX(jobj);
            coins.entries[i].y = HSD_JObjGetTranslationY(jobj);
            coins.entries[i].z = HSD_JObjGetTranslationZ(jobj);
        } else {
            coins.entries[i].x = 0.0f;
            coins.entries[i].y = 0.0f;
            coins.entries[i].z = 0.0f;
        }
        coins.entries[i].active = 1;
    }
    coins.mode = 2;
    CoinSystem_Init(&coins, 1);
    fn_80138D48();
}
