/*
 * 0x80127584..0x80127ECC: challenge demo where the kart spins up its
 * tornado at frame 150 and releases it at frame 190.
 */
#pragma cplusplus on
#include "game/DemoKartScene.h"

extern "C" {
extern const char lbl_80356150[];
extern const char *lbl_806CF500;
extern const char *lbl_806CF504;
void TireEffect_ResetSpin(DemoTornado *t, float a, float b);
void TornadoEffect_SetColorPairC8CC(DemoTornado *t, int a, int b);
void ItemEffectBus_TickTornadoCooldown(void *bus);
void ItemEffectBus_SnapshotAndFullReset(void *bus);
void SetAnimSpin(DemoDriver *d);
void TornadoEffect_SetFlagC0(DemoTornado *t);
void TornadoEffect_ClearFlagC0AndSetC4(DemoTornado *t, float f);
void clNormal3D_SetFlags(DemoNormal *n, unsigned int flags, int b);
extern char lbl_806D6FE8[7];
extern char lbl_806D6FF0[5];
}

struct RoboDemoScene : DemoBase {
    unsigned char first;
    float time;
    DemoScene *scene;
    int drawHandle;
    DemoNormal *normal;
    DemoNormal *obj;
    DemoDriver *driver;
    DemoTornado *tornado;
    Mtx matrix;
    HSD_JObj *joint;
    RoboDemoScene();
    virtual void _keyR();
    virtual int Update();
    virtual void Draw();
    virtual ~RoboDemoScene();
};

static inline void SetupJointMatrix(HSD_JObj *jobj) {
    if (jobj == 0) {
        __assert(lbl_806D6FE8, 0x47C, lbl_806D6FF0);
    }
    if (jobj != 0) {
        if (jobj == 0) {
            __assert(lbl_806D6FE8, 0x25D, lbl_806D6FF0);
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

void RoboDemoScene::Draw() {
    if (scene->Ready() == 1) {
        clDrawMan_Buckets_Reset(GetDrawMan());
        TransparentDraw_SortAndDispatch();
        CObj_DebugVizPathFlush(scene);
        fn_8016B0C4();
        Object_RenderJObjTree(normal, 7);
        KartDriver_RenderTimed(driver, 0, 1);
        ItemObjectManager_Render();
        DrawEffect_TickAndCull();
        clDrawMan_EndFrame_NoOp(GetDrawMan());
        clDrawMan_Buckets_Dispatch(GetDrawMan());
        Object_RenderJObjTree(obj, 7);
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

int RoboDemoScene::Update() {
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
    Object_SetField8_AndDirty(obj, time);
    clNormal3D_Exec(obj);
    Vec prev;
    prev.x = matrix[0][3];
    prev.y = matrix[1][3];
    prev.z = matrix[2][3];
    float angle = 0.0f;
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
        angle = 4.0f * (float)asin(c.x + c.y + c.z);
    }
    ItemEffectBus_SnapshotAndFullReset(*(void **)((char *)driver + 0x304));
    RenderObj_ItemStateMachine_Timed(driver, 0, angle, 0.06981111f * dist);
    TornadoEffect_Tick(tornado, GetDisplayBufferIndex());
    if (150.0f == time) {
        SetAnimSpin(driver);
        TornadoEffect_SetFlagC0(tornado);
    }
    if (190.0f == time) {
        TornadoEffect_ClearFlagC0AndSetC4(tornado, 1.0f);
    }
    ItemEffectBus_TickTornadoCooldown(*(void **)((char *)driver + 0x304));
    Vec eye;
    Vec target;
    CObj_LoadProjMatrix(scene, &eye);
    CObj_ApplyScissor(scene, &target);
    ItemObjectManager_Update();
    VfxSlotMgr_Update(eye, target);
    if (InputMgr_GetPlayer(GetInputManager(), 0)->Pressed(0x400)) {
        return 0xF;
    }
    return -2;
}

RoboDemoScene::~RoboDemoScene() {
    SetActiveCamera(0, 0);
    if (drawHandle >= 0) {
        TransparentDraw_RemoveByOwner(drawHandle);
    }
    SetPlayerCarObject(0);
    SetCourseScene3D(0);
    delete scene;
    Object_DtorWithGXSync(normal, 1);
    Object_DtorWithGXSync(obj, 1);
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

RoboDemoScene::RoboDemoScene() {
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
    scene = new DemoScene(lbl_806CF500, -1.0f, 0.0f);
    scene->Start(0.0f, 1.0f);
    normal = new DemoNormal(lbl_806CF500, 0);
    clNormal3D_SetScale(normal, 0, 0.0f, 1.0f, 0.0f, 0.0f);
    ProcessSystemTick(0);
    driver = new DemoDriver(g_characterId, matrix);
    tornado = new DemoTornado(0, driver, g_characterId, 1, 0.0f, 0.0f, 0.0f);
    TireEffect_ResetSpin(tornado, 0.0f, 1.0f);
    TornadoEffect_SetColorPairC8CC(tornado, 1, 1);
    joint = ResolveJointByName(normal, lbl_806CF504);
    ProcessSystemTick(0);
    obj = new DemoNormal(lbl_80356150, 0);
    clNormal3D_SetScale(obj, 0, 0.0f, 1.0f, 0.0f, 0.0f);
    clNormal3D_SetFlags(obj, 0x40000000, 0);
    g_raceCamera = 0;
    g_lakituStartAnimDone = 0;
    SetCourseScene3D(scene);
    drawHandle = SceneDrawList_RegisterArchive(normal->archive, 4);
    SetResourceLoadingFlag(1);
}
