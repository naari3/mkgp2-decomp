#include "game/types/clCGameDemoWC_private.h"
#include "game/singleton.h"
extern "C" {
extern const float lbl_806D4F90, lbl_806D4F9C, lbl_806D4FA0, lbl_806D4FA4, lbl_806D4F94, lbl_806D4F98, lbl_806D4FA8, lbl_806D4FAC, lbl_806D4FC0;
extern const char *clCGameDemoWC_Ctor_data_806CF2C8, *clCGameDemoWC_Ctor_data_806CF2CC;
extern char lbl_806D4FB0[7], lbl_806D4FB8[5];
void KartItem_CancelAndQueueDefault(DemoDriver *);
void SetAnimWallHitA(DemoDriver *);
void SetAnimWallHitB(DemoDriver *);
}
struct DemoWCAux {
    virtual ~DemoWCAux();
    virtual void Tick();
    virtual void Render();
    unsigned char opaque[0x20];
    DemoWCAux();
};
struct clCGameDemoWC : clCGameDemo {
    unsigned char first, pad5[3];
    float frame;
    clACamera *scene;
    int drawHandle;
    DemoNormal *normal;
    DemoDriver *driver;
    DemoTornado *tornado;
    Mtx matrix;
    HSD_JObj *joint;
    int event;
    DemoWCAux *aux;
    clCGameDemoWC();
    virtual int Update();
    virtual void Draw();
    virtual ~clCGameDemoWC();
};
float clCGameDemoWC_Tick_data_80419E88[6] = {0.0f,30.0f,120.0f,130.0f,220.0f,-1.0f};
int clCGameDemoWC_Tick_data_80419EA0[6] = {0,2,0,1,2,0};
void clCGameDemo::Draw() {}
int clCGameDemo::Update() {}
clCGameDemoWC::clCGameDemoWC()
{
    first = 1;
    frame = lbl_806D4F94;
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
    scene = new clACamera(clCGameDemoWC_Ctor_data_806CF2C8, lbl_806D4FA8, lbl_806D4F94);
    scene->Start(lbl_806D4F94, lbl_806D4F98);
    normal = new DemoNormal(clCGameDemoWC_Ctor_data_806CF2C8, 0);
    clNormal3D_SetScale(normal, 0, lbl_806D4F94, lbl_806D4F98, lbl_806D4F94, lbl_806D4F94);
    ProcessSystemTick(0);
    driver = new DemoDriver(g_characterId, matrix);
    tornado = new DemoTornado(0, driver, g_characterId, 0, lbl_806D4F94, lbl_806D4F94, lbl_806D4F94);
    joint = ResolveJointByName(normal, clCGameDemoWC_Ctor_data_806CF2CC);
    event = 0;
    aux = new DemoWCAux;
    g_raceCamera = 0;
    g_lakituStartAnimDone = 0;
    SetCourseScene3D(scene);
    drawHandle = SceneDrawList_RegisterArchive(normal->archive, 4);
    SetResourceLoadingFlag(1);
}

/* HSD jobj.h inlines retain their independent argument assertions. */
static inline int JointMatrixIsDirty(HSD_JObj *joint)
{
    unsigned char dirty;
    if (!joint) __assert(lbl_806D4FB0, 0x25d, lbl_806D4FB8);
    dirty = 0;
    if (!(joint->flags & 0x800000) && (joint->flags & 0x40)) dirty = 1;
    return dirty;
}
static inline void JointSetupMatrix(HSD_JObj *joint)
{
    if (!joint) __assert(lbl_806D4FB0, 0x47c, lbl_806D4FB8);
    if (joint && JointMatrixIsDirty(joint)) HSD_JObjSetupMatrixSub(joint);
}
static inline void SceneSetFrame(clACamera *scene, float frame)
{
    if (!(scene->frame < 0.0f) && !(frame < 0.0f)) {
        scene->active = 1;
        scene->frame = frame;
    }
}

int clCGameDemoWC::Update()
{
    Vec previous, current, delta, eye, target;
    float distance;
    HSD_JObj *joint;
    if (this->first) this->first = 0;
    else {
        if (270.0f <= (this->frame += 1.0f)) return 15;
    }
    Object_SetField8_AndDirty(this->normal, this->frame);
    clNormal3D_Exec(this->normal);
    SceneSetFrame(this->scene, this->frame);
    this->scene->Tick(lbl_806D4FA8);
    this->aux->Tick();
    previous.x = this->matrix[0][3];
    previous.y = this->matrix[1][3];
    previous.z = this->matrix[2][3];
    PSMTXScale(this->matrix, lbl_806D4FAC, lbl_806D4FAC, lbl_806D4FAC);
    joint = this->joint;
    JointSetupMatrix(joint);
    PSMTXConcat(joint->mtx, this->matrix, this->matrix);
    current.x = this->matrix[0][3];
    current.y = this->matrix[1][3];
    current.z = this->matrix[2][3];
    Vec3_Subtract(&current, &previous, &delta);
    distance = lbl_806D4FA8 * Vec3_Magnitude(&delta);
    if (0.0f <= clCGameDemoWC_Tick_data_80419E88[this->event] && clCGameDemoWC_Tick_data_80419E88[this->event] <= this->frame) {
        DemoDriver *driver = this->driver;
        switch (clCGameDemoWC_Tick_data_80419EA0[this->event]) {
        case 0: KartItem_CancelAndQueueDefault(driver); break;
        case 1: SetAnimWallHitB(driver); break;
        case 2: SetAnimWallHitA(driver); break;
        }
        this->event++;
    }
    RenderObj_ItemStateMachine_Timed(this->driver, 0, 0.0f, lbl_806D4FC0 * distance);
    TornadoEffect_Tick(this->tornado, GetDisplayBufferIndex());
    CObj_LoadProjMatrix(this->scene, &eye);
    CObj_ApplyScissor(this->scene, &target);
    ItemObjectManager_Update();
    VfxSlotMgr_Update(eye, target);
    return InputMgr_GetPlayer(GetInputManager(), 0)->Pressed(0x400) ? 15 : -2;
}

static inline float Clamp(float v, float lo, float hi)
{
    if (v < lo) return lo;
    if (v > hi) return hi;
    return v;
}


void clCGameDemoWC::Draw()
{
    unsigned char alpha;
    float frame;
    if (this->scene->Ready() == 1) {
        clDrawMan_Buckets_Reset(SINGLETON_INSTANCE(lbl_806D10AC));
        TransparentDraw_SortAndDispatch();
        CObj_DebugVizPathFlush(this->scene);
        fn_8016B0C4();
        Object_RenderJObjTree(this->normal, 7);
        KartDriver_RenderTimed(this->driver, 0, 1);
        this->aux->Render();
        ItemObjectManager_Render();
        DrawEffect_TickAndCull();
        clDrawMan_EndFrame_NoOp(SINGLETON_INSTANCE(lbl_806D10AC));
        clDrawMan_Buckets_Dispatch(SINGLETON_INSTANCE(lbl_806D10AC));
        alpha = 0;
        frame = this->frame;
        if (frame < 30.0f)
            alpha = 255.0f - 255.0f * Clamp(frame / 30.0f, 0.0f, 1.0f);
        if (frame > 240.0f)
            alpha = 255.0f - 255.0f * Clamp((270.0f - frame) / 30.0f, 0.0f, 1.0f);
        if (alpha) fn_80181790(this->scene, 0, 1.0f, 0, 0, alpha, 0);
        this->scene->Render();
        HSD_StateInvalidate(0x7f);
    }
}

clCGameDemoWC::~clCGameDemoWC()
{
    SetActiveCamera(0, 0);
    if (drawHandle >= 0) TransparentDraw_RemoveByOwner(drawHandle);
    SetPlayerCarObject(0);
    SetCourseScene3D(0);
    delete scene;
    Object_DtorWithGXSync(normal, 1);
    delete aux;
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
