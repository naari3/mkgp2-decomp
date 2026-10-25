/*
 * 0x80126CC4..0x80127584: challenge demo that drives the kart past the
 * challenge object model (MH_challenge_obj.dat).
 */
#pragma cplusplus on
#include "game/DemoKartScene.h"

extern "C" {
extern const char lbl_803560D4[];
extern const char *lbl_806CF4E0;
extern const char *lbl_806CF4E4;
extern char lbl_806D6FB0[7];
extern char lbl_806D6FB8[5];
}

struct MapDemoScene : DemoBase {
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
    MapDemoScene();
    virtual void _keyM();
    virtual int Update();
    virtual void Draw();
    virtual ~MapDemoScene();
};

static inline void SetupJointMatrix(HSD_JObj *jobj) {
    if (jobj == 0) {
        __assert(lbl_806D6FB0, 0x47C, lbl_806D6FB8);
    }
    if (jobj != 0) {
        if (jobj == 0) {
            __assert(lbl_806D6FB0, 0x25D, lbl_806D6FB8);
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

void MapDemoScene::Draw() {
    if (scene->Ready() == 1) {
        clDrawMan_Buckets_Reset(GetDrawMan());
        TransparentDraw_SortAndDispatch();
        CObj_DebugVizPathFlush(scene);
        fn_8016B0C4();
        Object_RenderJObjTree(normal, 7);
        Object_RenderJObjTree(obj, 7);
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
        if (t > 230.0f) {
            alpha = 255.0f - 255.0f * DemoClamp((260.0f - t) / 30.0f, 0.0f, 1.0f);
        }
        if (alpha) {
            fn_80181790(scene, 0, 1.0f, 0, 0, alpha, 0);
        }
        scene->Render();
        HSD_StateInvalidate(0x7F);
    }
}

int MapDemoScene::Update() {
    if (first) {
        first = 0;
    } else {
        if ((time += 1.0f) >= 260.0f) {
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
    RenderObj_ItemStateMachine_Timed(driver, 0, angle, 0.06981111f * dist);
    TornadoEffect_Tick(tornado, GetDisplayBufferIndex());
    Vec eye;
    Vec target;
    CObj_LoadProjMatrix(scene, &eye);
    CObj_ApplyScissor(scene, &target);
    ItemObjectManager_Update();
    VfxSlotMgr_Update(eye, target);
    return InputMgr_GetPlayer(GetInputManager(), 0)->Pressed(0x400) ? 0xF : -2;
}

MapDemoScene::~MapDemoScene() {
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

MapDemoScene::MapDemoScene() {
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
    scene = new DemoScene(lbl_806CF4E0, -1.0f, 0.0f);
    scene->Start(0.0f, 1.0f);
    normal = new DemoNormal(lbl_806CF4E0, 0);
    clNormal3D_SetScale(normal, 0, 0.0f, 1.0f, 0.0f, 0.0f);
    ProcessSystemTick(0);
    driver = new DemoDriver(g_characterId, matrix);
    tornado = new DemoTornado(0, driver, g_characterId, 0, 0.0f, 0.0f, 0.0f);
    joint = ResolveJointByName(normal, lbl_806CF4E4);
    ProcessSystemTick(0);
    obj = new DemoNormal(lbl_803560D4, 0);
    clNormal3D_SetScale(obj, 0, 0.0f, 1.0f, 0.0f, 0.0f);
    g_raceCamera = 0;
    g_lakituStartAnimDone = 0;
    SetCourseScene3D(scene);
    drawHandle = SceneDrawList_RegisterArchive(normal->archive, 4);
    SetResourceLoadingFlag(1);
}
