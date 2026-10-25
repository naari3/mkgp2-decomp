/*
 * 0x8020F44C..0x80210078: kart demo scene with extra course objects and
 * three background models.
 */

#include "game/DemoKartScene.h"

extern "C" void PtrVec_InsertFill(void *v, void *pos, int n, const void *val);

template <class T> struct PtrVecData {
    int cap;
    int count;
    T *data;
    PtrVecData() : cap(0), count(0), data(0) {}
    ~PtrVecData() {
        if (data) {
            operator delete(data);
        }
    }
};

template <class T> struct PtrVecBase : PtrVecData<T> {
    PtrVecBase() {}
    ~PtrVecBase() {}
};

template <class T> struct PtrVec : PtrVecBase<T> {
    PtrVec() {}
    ~PtrVec() {}
    T *begin() { return this->data; }
    T *end() { return this->data + this->count; }
    void push_back(const T &v) { PtrVec_InsertFill(this, end(), 1, &v); }
};

struct DemoObj {
    virtual ~DemoObj();
    virtual void Update();
    virtual void Draw();
};

struct DemoObjA : DemoObj {
    char pad[0x1300 - 4];
    DemoObjA(HSD_JObj *joint);
};

struct DemoObjB : DemoObj {
    char pad[0x14 - 4];
    DemoObjB();
};

struct DemoObjC : DemoObj {
    char pad[0x158 - 4];
    DemoObjC(HSD_JObj *joint);
};

extern "C" {
extern const char *lbl_806D0398;
extern const char *lbl_806D039C;
extern const char lbl_803C37BC[];
extern const char *lbl_804ECB58[9];
extern char lbl_806DAD1C[7];
extern char lbl_806DAD24[5];
}

struct ObjDemoScene : DemoBase {
    unsigned char first;
    float time;
    DemoScene *scene;
    int drawHandle;
    DemoNormal *normal;
    DemoDriver *driver;
    DemoTornado *tornado;
    Mtx matrix;
    HSD_JObj *joint;
    PtrVec<DemoObj *> objs;
    PtrVec<DemoNormal *> models;
    ObjDemoScene();
    virtual int Update();
    virtual void Draw();
    virtual ~ObjDemoScene();
};

static inline void SetupJointMatrix(HSD_JObj *jobj) {
    if (jobj == 0) {
        __assert(lbl_806DAD1C, 0x47C, lbl_806DAD24);
    }
    if (jobj != 0) {
        if (jobj == 0) {
            __assert(lbl_806DAD1C, 0x25D, lbl_806DAD24);
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

void ObjDemoScene::Draw() {
    if (scene->Ready() == 1) {
        clDrawMan_Buckets_Reset(GetDrawMan());
        TransparentDraw_SortAndDispatch();
        CObj_DebugVizPathFlush(scene);
        fn_8016B0C4();
        Object_RenderJObjTree(normal, 7);
        for (DemoNormal **m = models.begin(); m != models.end(); m++) {
            Object_RenderJObjTree(*m, 7);
        }
        for (DemoObj **o = objs.begin(); o != objs.end(); o++) {
            (*o)->Draw();
        }
        KartDriver_RenderTimed(driver, 0, 1);
        ItemObjectManager_Render();
        DrawEffect_TickAndCull();
        clDrawMan_EndFrame_NoOp(GetDrawMan());
        clDrawMan_Buckets_Dispatch(GetDrawMan());
        float t = time;
        unsigned char alpha = 0;
        if (t < 30.0f) {
            alpha = 255.0f - 255.0f * DemoClamp(t / 30.0f, 0.0f, 1.0f);
        }
        if (t > 240.0f) {
            alpha = 255.0f - 255.0f * DemoClamp((270.0f - t) / 30.0f, 0.0f, 1.0f);
        }
        if (alpha) {
            fn_80181790(scene, 0, 1.0f, 0, 0, alpha, 0);
        }
        scene->Render();
        HSD_StateInvalidate(0x7F);
    }
}

int ObjDemoScene::Update() {
    if (first) {
        first = 0;
    } else {
        if ((time += 1.0f) >= 270.0f) {
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
    PSMTXScale(matrix, 1.0f, 1.0f, 1.0f);
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
    Vec eye;
    Vec target;
    CObj_LoadProjMatrix(scene, &eye);
    CObj_ApplyScissor(scene, &target);
    ItemObjectManager_Update();
    VfxSlotMgr_Update(eye, target);
    for (DemoNormal **m = models.begin(); m != models.end(); m++) {
        clNormal3D_Exec(*m);
        Object_DriveAnimMatrix(*m);
    }
    for (DemoObj **o = objs.begin(); o != objs.end(); o++) {
        (*o)->Update();
    }
    return InputMgr_GetPlayer(GetInputManager(), 0)->Pressed(0x400) ? 0xF : -2;
}

ObjDemoScene::~ObjDemoScene() {
    SetActiveCamera(0, 0);
    g_playerRenderObj = 0;
    if (drawHandle >= 0) {
        TransparentDraw_RemoveByOwner(drawHandle);
    }
    SetPlayerCarObject(0);
    SetCourseScene3D(0);
    for (DemoObj **o = objs.begin(); o != objs.end(); o++) {
        delete *o;
    }
    for (DemoNormal **m = models.begin(); m != models.end(); m++) {
        Object_DtorWithGXSync(*m, 1);
    }
    delete scene;
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

ObjDemoScene::ObjDemoScene() {
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
    scene = new DemoScene(lbl_806D0398, -1.0f, 0.0f);
    scene->Start(0.0f, 1.0f);
    normal = new DemoNormal(lbl_806D0398, 0);
    clNormal3D_SetScale(normal, 0, 0.0f, 1.0f, 0.0f, 0.0f);
    ProcessSystemTick(0);
    driver = new DemoDriver(g_characterId, matrix);
    tornado = new DemoTornado(0, driver, g_characterId, 0, 0.0f, 0.0f, 0.0f);
    joint = ResolveJointByName(normal, lbl_806D039C);
    g_playerRenderObj = driver;
    objs.push_back(new DemoObjA(ResolveJointByName(normal, lbl_803C37BC)));
    objs.push_back(new DemoObjB);
    objs.push_back(new DemoObjC(ResolveJointByName(normal, lbl_803C37BC)));
    ProcessSystemTick(0);
    DemoNormal *m = 0;
    for (int i = 0; i < 3; i++) {
        m = new DemoNormal(lbl_804ECB58[i], 0);
        clNormal3D_SetScale(m, 0, 0.0f, 1.0f, 0.0f, 0.0f);
        models.push_back(m);
    }
    g_raceCamera = 0;
    g_lakituStartAnimDone = 0;
    SetCourseScene3D(scene);
    drawHandle = SceneDrawList_RegisterArchive(normal->archive, 4);
    SetResourceLoadingFlag(1);
}
