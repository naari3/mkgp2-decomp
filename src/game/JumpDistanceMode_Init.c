/* JumpDistanceMode_Init (0x80213210): constructor of the jump-distance
 * minigame mode. Builds the player kart, camera, HUD, goal lines and
 * landing-grid objects. */

typedef struct { float x, y, z; } Vec;

void *operator new(unsigned long size);
void operator delete(void *p);

extern "C" {
/* .rodata 0x803C3858..0x803C3DD8 (owned by this TU so the pool base matches) */
static const unsigned int lbl_803C3858[0x102] = {
    0x00000000, 0x00000000, 0x00000000, 0x3F800000, 0x3F333333, 0x3F666666,
    0x00000000, 0x00000000, 0x43FA0000, 0x42855556, 0x447A0000, 0x42855556,
    0x44FA0000, 0x42855556, 0x453B8000, 0x42855556, 0x457A0000, 0x42855556,
    0x459C4000, 0x42855556, 0x00000000, 0x00000000, 0x43FA0000, 0x42855556,
    0x447A0000, 0x42855556, 0x44FA0000, 0x42855556, 0x453B8000, 0x42855556,
    0x457A0000, 0x42855556, 0x459C4000, 0x42855556, 0x00000000, 0x00000000,
    0x43FA0000, 0x42855556, 0x447A0000, 0x42855556, 0x44FA0000, 0x42855556,
    0x453B8000, 0x42855556, 0x457A0000, 0x42855556, 0x459C4000, 0x42855556,
    0x00000000, 0x00000000, 0x43FA0000, 0x42855556, 0x447A0000, 0x42855556,
    0x44FA0000, 0x42855556, 0x453B8000, 0x42855556, 0x457A0000, 0x42855556,
    0x459C4000, 0x42855556, 0x00000000, 0x00000000, 0x43FA0000, 0x42855556,
    0x447A0000, 0x42855556, 0x44FA0000, 0x42855556, 0x453B8000, 0x42855556,
    0x457A0000, 0x42855556, 0x459C4000, 0x42855556, 0x00000000, 0x00000000,
    0x43FA0000, 0x42855556, 0x447A0000, 0x42855556, 0x44FA0000, 0x42855556,
    0x453B8000, 0x42855556, 0x457A0000, 0x42855556, 0x459C4000, 0x42855556,
    0x00000000, 0x00000000, 0x43FA0000, 0x42855556, 0x447A0000, 0x42855556,
    0x44FA0000, 0x42855556, 0x453B8000, 0x42855556, 0x457A0000, 0x42855556,
    0x459C4000, 0x42855556, 0x00000000, 0x00000000, 0x43FA0000, 0x42855556,
    0x447A0000, 0x42855556, 0x44FA0000, 0x42855556, 0x453B8000, 0x42855556,
    0x457A0000, 0x42855556, 0x459C4000, 0x42855556, 0x00000000, 0x00000000,
    0x43FA0000, 0x42855556, 0x447A0000, 0x42855556, 0x44FA0000, 0x42855556,
    0x453B8000, 0x42855556, 0x457A0000, 0x42855556, 0x459C4000, 0x42855556,
    0x00000000, 0x00000000, 0x43FA0000, 0x42855556, 0x447A0000, 0x42855556,
    0x44FA0000, 0x42855556, 0x453B8000, 0x42855556, 0x457A0000, 0x42855556,
    0x459C4000, 0x42855556, 0x00000000, 0x00000000, 0x43FA0000, 0x42855556,
    0x447A0000, 0x42855556, 0x44FA0000, 0x42855556, 0x453B8000, 0x42855556,
    0x457A0000, 0x42855556, 0x459C4000, 0x42855556, 0x00000000, 0x00000000,
    0x43FA0000, 0x42855556, 0x447A0000, 0x42855556, 0x44FA0000, 0x42855556,
    0x453B8000, 0x42855556, 0x457A0000, 0x42855556, 0x459C4000, 0x42855556,
    0x00000000, 0x00000000, 0x43FA0000, 0x42A6AAAB, 0x447A0000, 0x42A6AAAB,
    0x44FA0000, 0x42A6AAAB, 0x453B8000, 0x42A6AAAB, 0x457A0000, 0x42A6AAAB,
    0x459C4000, 0x42A6AAAB, 0x00000000, 0x00000000, 0x43FA0000, 0x42A6AAAB,
    0x447A0000, 0x42A6AAAB, 0x44FA0000, 0x42A6AAAB, 0x453B8000, 0x42A6AAAB,
    0x457A0000, 0x42A6AAAB, 0x459C4000, 0x42A6AAAB, 0x00000000, 0x00000000,
    0x43FA0000, 0x42A6AAAB, 0x447A0000, 0x42A6AAAB, 0x44FA0000, 0x42A6AAAB,
    0x453B8000, 0x42A6AAAB, 0x457A0000, 0x42A6AAAB, 0x459C4000, 0x42A6AAAB,
    0x00000000, 0x00000000, 0x43FA0000, 0x42A6AAAB, 0x447A0000, 0x42A6AAAB,
    0x44FA0000, 0x42A6AAAB, 0x453B8000, 0x42A6AAAB, 0x457A0000, 0x42A6AAAB,
    0x459C4000, 0x42A6AAAB, 0x00000000, 0x00000000, 0x43FA0000, 0x42A6AAAB,
    0x447A0000, 0x42A6AAAB, 0x44FA0000, 0x42A6AAAB, 0x453B8000, 0x42A6AAAB,
    0x457A0000, 0x42A6AAAB, 0x459C4000, 0x42A6AAAB, 0x00000000, 0x00000000,
    0x43FA0000, 0x42A6AAAB, 0x447A0000, 0x42A6AAAB, 0x44FA0000, 0x42A6AAAB,
    0x453B8000, 0x42A6AAAB, 0x457A0000, 0x42A6AAAB, 0x459C4000, 0x42A6AAAB,
};
static const unsigned int lbl_803C3C60[12] = {
    0x44340000, 0x00000000, 0xC5AFF000, 0x43F00000, 0x00000000, 0xC5AFF000,
    0x43F00000, 0x00000000, 0xC505C000, 0x44340000, 0x00000000, 0xC505C000,
};
static const unsigned int lbl_803C3C90[12] = {
    0x44480000, 0x00000000, 0xC5CB2000, 0x43C80000, 0x00000000, 0xC5CB2000,
    0x43C80000, 0x00000000, 0xC4BB8000, 0x44480000, 0x00000000, 0xC4BB8000,
};
static const unsigned int lbl_803C3CC0[12] = {
    0x44480000, 0x00000000, 0xC5D61000, 0x43C80000, 0x00000000, 0xC5D61000,
    0x43C80000, 0x00000000, 0xC48FC000, 0x44480000, 0x00000000, 0xC48FC000,
};
extern const float lbl_803C3CF0[14] = {
    330.0f, 63.25f, 318.0f, 79.25f, 358.0f, 79.25f, 399.0f, 79.25f,
    355.0f, 38.25f, 380.0f, 38.25f, 405.0f, 38.25f,
};
static const float s_gridX[5] = { 490.0f, 523.0f, 556.0f, 589.0f, 622.0f };
static const float s_gridY[3] = { 43.0f, 78.0f, 113.0f };
static const Vec s_markerScale = { 0.0f, 0.0f, -5.0f };
extern const float lbl_803C3D54[4] = { 300.0f, -7500.0f, 1000.0f, -800.0f };
extern const float lbl_803C3D64[7] = { 1900.0f, -7800.0f, 2100.0f, -7400.0f, 0.0f, 0.0f, 0.0f };
extern const unsigned int lbl_803C3D80[3] = { 0, 0, 0 };
extern const char lbl_803C3D8C[] = "clCGameDN";
extern const char lbl_803C3D98[12] = "clJobRunner";
static const char s_lakituFile[20] = "jyugemu_start.dat";
static const char s_coinFile[16] = "mario_coin.dat";
static const char s_kiraFile[16] = "k_kira13.dat";

extern char lbl_8048E144[];
extern char lbl_804ECC08[];
extern int g_ccClass;
extern int g_characterId;
extern int g_kartStartSlot;
extern unsigned char g_lakituStartAnimDone;
extern void *g_playerRenderObj;
extern void *g_raceCamera;
extern unsigned char g_raceEnded;
extern float g_raceTimeRemaining;
extern int g_reverseRoundFlag;
extern void *g_weatherSystem;
extern int lbl_806D12BC;
extern const float lbl_806DAD70;
extern const float lbl_806DAD7C;
extern const float lbl_806DAD88;
extern const float lbl_806DADA4;
extern const float lbl_806DADDC;
extern const float lbl_806DAE08;
extern const float lbl_806DAE0C;

void GameMode_BaseInit(void *self);
void DrawManager_GetOrCreate(void);
void SetResourceLoadingFlag(int on);
void DMAChannelManager_Init(void);
void TransitionEffect_GetOrCreate(void);
void SoundChannels_ClearAll(void);
void ItemObjectManager_Init(void);
void CourseObjectManager_Init(void);
void GetCourseDataPtr(void);
int RenderTarget_Create(void);
void SetActiveCamera(int idx, void *camera);
void ProcessSystemTick(int arg);
void GetRaceContextPtr(void);
void RankingTable_Init(void);
void SoundDriver_GetOrCreate(int arg);
int GetDisplayBufferIndex(void);
int GetKartStartSlot(void);
void GetStartPosition(int idx, float *x, float *y, float *z);
float GetCourseStartYaw(void);
void CarObject_SetPosition(void *car, Vec *pos);
struct RenderObj *CarObject_GetRenderObj(void *car);
void *CarObject_GetKartMovementPtr(void *car);
void KartMovement_EquipItem(void *obj, int item);
void fn_8023E1E4(void *obj, int item, int arg);
void SetPlayerCarObject(void *car);
int *GetKartModelNameEntry(int chara, int arg);
void Vec3_Subtract(const Vec *a, const Vec *b, Vec *out);
void Vec3_Normalize(Vec *src, Vec *dst);
void Scene3D_GetCameraPos(void *scene, float *a, float *b);
void Scene3D_SetupProjection(void *scene, float a, float b);
void HUD_RegisterOverlay(void *hud, int id, int arg);
void SetCourseScene3D(void *scene);
int MiniGame_GetTimerValue(void);
void PreloadEffectResources(int id);
float *MiniGame_GetCourseData(void);
void fn_8013D738(void *obj, float a, float b);
void fn_8013D608(void *obj, float x, float y, float z);
void fn_8013D634(void *obj, float x, float y, float z);
void InitRumbleController(int arg);
void fn_801699D8(int a, int b);
}

struct RenderObj {
    char pad0[0x238];
    int x238;
    char pad23C[0x94];
    unsigned char x2D0;
};

struct InputManager { char data[0x37C]; InputManager(); };
struct Camera { char data[0x2C]; Camera(float a, float b, int w, int h, int target); };
struct CarObject {
    char data[0x118];
    CarObject(int disp, int chara, int cc, int a, int b, int c, int d, int e, float x, float z, float yaw);
};
static inline int GetCC() { return g_ccClass; }
static inline int GetChara() { return g_characterId; }
struct PlayerCar : CarObject {
    PlayerCar(Vec *pos, int chara, int cc)
        : CarObject(GetDisplayBufferIndex(), chara, cc, 0, 1, 7, 0, 0, pos->x, pos->z, GetCourseStartYaw()) {}
};
struct ItemSlot { char data[0x44]; ItemSlot(int arg); };
struct LakituStart { char data[0x58]; LakituStart(const void *data, int arg, float x, float y, float z); };
struct Scene3D { char data[0x3084]; Scene3D(int name); };
struct ChallengeGoalCamera { char data[8]; ChallengeGoalCamera(); };
struct KartMovement {
    char data[0x324];
    KartMovement(const KartMovement &src);
};
struct HUD { char data[0x80]; HUD(int arg); };
struct TimerDisplay { char data[0x2C]; TimerDisplay(int value); };
struct WeatherSystem { char data[0x1B4]; WeatherSystem(int arg); };
struct LandingMarker { char data[0x20]; LandingMarker(const void *data, int arg); };

struct ScenePos {
    int x0;
    void *scene;
    Vec a;
    Vec b;
    float x20;
    ScenePos(void *s) {
        x0 = 0;
        scene = s;
        a.x = a.y = a.z = x20 = lbl_806DAD7C;
        b.x = b.y = b.z = lbl_806DAD7C;
    }
};

struct GoalLinePair {
    Vec fwd[2];
    Vec rev[2];
};

struct GoalLine {
    const Vec *pts;
    Vec normal;
    Vec dir;
    GoalLine(const GoalLinePair *pair) {
        pts = g_reverseRoundFlag == 0 ? pair->fwd : pair->rev;
        Vec3_Subtract(&pts[1], &pts[0], &dir);
        Vec3_Normalize(&dir, &dir);
        normal.x = -dir.z;
        normal.y = dir.y;
        normal.z = dir.x;
    }
};

struct JumpGauge {
    unsigned char x0, x1, x2;
    int count;
    int div;
    float step;
    float x10;
    float x14;
    char pad18[0x80];
    void Set(int n) {
        count = n;
        div = n;
        step = lbl_806DAD70 / div;
    }
    JumpGauge() {
        x0 = 0;
        x1 = 0;
        x2 = 0;
        count = 0;
        div = 1;
        step = lbl_806DAD70;
        x10 = lbl_806DAD7C;
        x14 = lbl_806DAD7C;
        Set(3);
    }
};

struct GridSlot {
    int id;
    int pad[3];
};

struct GridCell {
    float x, y, z, w;
    int x10, x14;
    GridSlot slots[5];
};

struct LandingGrid {
    LandingMarker *markers[2];
    int x8, xC, x10;
    float x14;
    int x18;
    GridCell cells[15];
    GridCell cells2[15];
    LandingGrid(const char *m0, const char *m1, const Vec *pos, const float *xs, const float *ys);
};

inline LandingGrid::LandingGrid(const char *m0, const char *m1, const Vec *pos, const float *xs, const float *ys) {
    int i;

    markers[0] = 0;
    x8 = 0;
    xC = 0;
    x10 = 0;
    x14 = lbl_806DAD7C;
    x18 = 0;
    markers[0] = new LandingMarker(m0, 1);
    fn_8013D738(markers[0], lbl_806DAD7C, lbl_806DAD70);
    fn_8013D608(markers[0], lbl_806DAE0C, lbl_806DAE0C, lbl_806DAE0C);
    fn_8013D634(markers[0], pos->x, pos->y, pos->z);
    markers[1] = new LandingMarker(m1, 1);
    fn_8013D738(markers[1], lbl_806DAD7C, lbl_806DAD70);
    fn_8013D608(markers[1], lbl_806DAE0C, lbl_806DAE0C, lbl_806DAE0C);
    fn_8013D634(markers[1], pos->x, pos->y, pos->z);
    for (i = 0; i < 15; i++) {
        cells[i].x = cells2[i].x = xs[i % 5];
        cells[i].y = cells2[i].y = ys[i / 5];
        cells[i].z = cells2[i].z = lbl_806DAD7C;
        cells[i].w = cells2[i].w = lbl_806DAD7C;
        cells[i].x10 = cells2[i].x10 = 0;
        cells[i].x14 = cells2[i].x14 = 0;
        cells[i].slots[0].id = cells2[i].slots[0].id = -1;
        cells[i].slots[1].id = cells2[i].slots[1].id = -1;
        cells[i].slots[2].id = cells2[i].slots[2].id = -1;
        cells[i].slots[3].id = cells2[i].slots[3].id = -1;
        cells[i].slots[4].id = cells2[i].slots[4].id = -1;
    }
}

struct GameModeBase {
    virtual void _key();
    virtual ~GameModeBase();
    GameModeBase();
};

struct ModeBase : GameModeBase {
    float x4;
    ModeBase() {
        x4 = lbl_806DAD7C;
    }
    virtual void _key2();
    virtual ~ModeBase();
};

struct JumpDistanceMode : ModeBase {
    virtual void _key3();
    CarObject *car;
    LakituStart *lakitu;
    InputManager *input;
    Scene3D *scene;
    ChallengeGoalCamera *goalCam;
    ItemSlot *itemSlot;
    Camera *camera;
    int renderTarget;
    HUD *hud;
    TimerDisplay *timer;
    GoalLine *lines[3];
    JumpGauge *gauge;
    ScenePos *scenePos;
    unsigned char x44, x45;
    int x48, x4C, x50;
    float x54, x58, x5C, x60, x64, x68;
    unsigned char x6C, x6D;
    KartMovement *movement;
    float x74;
    unsigned char x78;
    LandingGrid *grid;
    int x80, x84;
    unsigned char x88;
    JumpDistanceMode();
};

extern "C" JumpDistanceMode *JumpDistanceMode_Init(JumpDistanceMode *self);

JumpDistanceMode::JumpDistanceMode() {
    Vec pos;
    float camA, camB;
    float *course;

    car = 0;
    lakitu = 0;
    input = 0;
    scene = 0;
    goalCam = 0;
    itemSlot = 0;
    camera = 0;
    renderTarget = 0;
    hud = 0;
    timer = 0;
    lines[0] = 0;
    lines[1] = 0;
    lines[2] = 0;
    gauge = 0;
    scenePos = 0;
    x44 = 0;
    x45 = 0;
    x48 = 0;
    x4C = 0;
    x50 = 0;
    x54 = lbl_806DADA4;
    x58 = lbl_806DAD7C;
    x68 = lbl_806DAD7C;
    x6C = 0;
    x6D = 0;
    movement = 0;
    x74 = lbl_806DAD7C;
    x78 = 0;
    x88 = 0;
    DrawManager_GetOrCreate();
    SetResourceLoadingFlag(0);
    DMAChannelManager_Init();
    TransitionEffect_GetOrCreate();
    SoundChannels_ClearAll();
    ItemObjectManager_Init();
    CourseObjectManager_Init();
    input = new InputManager;
    GetCourseDataPtr();
    renderTarget = RenderTarget_Create();
    camera = new Camera(lbl_806DAE08, lbl_806DAD88, 0x100, 0x100, renderTarget);
    SetActiveCamera(0, camera);
    g_raceCamera = camera;
    ProcessSystemTick(0);
    GetRaceContextPtr();
    RankingTable_Init();
    lbl_806D12BC = 0;
    SoundDriver_GetOrCreate(0);
    GetDisplayBufferIndex();
    g_kartStartSlot = GetKartStartSlot();
    GetStartPosition(0, &pos.x, &pos.y, &pos.z);
    car = new PlayerCar(&pos, GetChara(), GetCC());
    CarObject_SetPosition(car, &pos);
    {
        RenderObj *r = CarObject_GetRenderObj(car);
        r->x238 = 1;
    }
    {
        RenderObj *r = CarObject_GetRenderObj(car);
        r->x2D0 = 1;
    }
    KartMovement_EquipItem(CarObject_GetRenderObj(car), 0x17);
    itemSlot = new ItemSlot(0);
    fn_8023E1E4(itemSlot, 0x17, 0);
    SetPlayerCarObject(car);
    g_playerRenderObj = CarObject_GetRenderObj(car);
    lakitu = new LakituStart(s_lakituFile, 0, lbl_806DAD7C, lbl_806DAD7C, lbl_806DAD7C);
    scene = new Scene3D(*GetKartModelNameEntry(g_characterId, -1));
    goalCam = new ChallengeGoalCamera;
    movement = new KartMovement(*(KartMovement *)CarObject_GetKartMovementPtr(car));
    scenePos = new ScenePos(scene);
    lines[0] = new GoalLine((const GoalLinePair *)lbl_803C3C60);
    lines[1] = new GoalLine((const GoalLinePair *)lbl_803C3C90);
    lines[2] = new GoalLine((const GoalLinePair *)lbl_803C3CC0);
    ProcessSystemTick(0);
    Scene3D_GetCameraPos(scene, &camA, &camB);
    camA += lbl_806DADDC;
    Scene3D_SetupProjection(scene, camA, camB);
    hud = new HUD(0);
    HUD_RegisterOverlay(hud, 6, 0);
    HUD_RegisterOverlay(hud, 0x11, 0);
    HUD_RegisterOverlay(hud, 0x12, 0);
    HUD_RegisterOverlay(hud, 0xE, 0);
    g_lakituStartAnimDone = 0;
    SetCourseScene3D(scene);
    g_raceEnded = 0;
    g_raceTimeRemaining = MiniGame_GetTimerValue();
    x5C = x60 = x64 = lbl_806DAD7C;
    PreloadEffectResources(1);
    PreloadEffectResources(9);
    PreloadEffectResources(0xA);
    course = MiniGame_GetCourseData();
    if (course != 0) {
        x54 = *course;
    }
    timer = new TimerDisplay(x54);
    gauge = new JumpGauge;
    grid = new LandingGrid(s_coinFile, s_kiraFile, &s_markerScale, s_gridX, s_gridY);
    x80 = 0;
    x84 = 0;
    if (g_weatherSystem == 0) {
        g_weatherSystem = new WeatherSystem(1);
    }
    SetResourceLoadingFlag(1);
    InitRumbleController(0);
    fn_801699D8(0, 1);
    fn_801699D8(1, 1);
}
