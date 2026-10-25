/* RaceScene_Init (0x800A1D80): constructor of the race scene. Builds the
 * course, camera, player kart, path manager, Lakitu, HUD and the per-race
 * managers, logging the heap use after each step, then preloads the
 * effect and item resources the race can need.
 * NonMatching (99.98%): in the first item preload loop the slot item id
 * is copied to its callee-saved register after the zero test instead of
 * before it. */

typedef struct RaceParams {
    signed char laps;
    float timeLimit;
    float lapBonus;
} RaceParams;

struct GameModeBase {
    GameModeBase() {}
    virtual ~GameModeBase();
};

struct EnvironmentMgr {
    unsigned char data[0x37C];
    EnvironmentMgr();
};

struct RaceCamera {
    unsigned char data[0x2C];
    RaceCamera(float fovy, int width, float aspect, int height, void *renderTarget);
};

struct CarObject {
    unsigned char data[0x118];
    CarObject(int displayIdx, int charId, float x, float y, float yaw, int ccClass, int variant, int human,
              int team, int local, int ghost);
};

struct PathManager {
    unsigned char data[0x4E8];
    PathManager(void *pathKey, CarObject *car, void *renderObj, float *x, float *y, float *z);
};

struct LakituStart {
    unsigned char data[0x58];
    LakituStart(const char *name, int slot, float x, float y, float z);
};

struct Scene3D {
    unsigned char data[0x3084];
    Scene3D(const char *modelName);
};

struct JyugemuFlag {
    unsigned char data[0xC];
    JyugemuFlag(Scene3D *scene);
};

struct JyugemuReverseFlag {
    unsigned char data[0x14];
    JyugemuReverseFlag(void *renderObj);
};

struct FinalLapBanner {
    unsigned char data[0x10];
    FinalLapBanner(void *renderObj);
};

struct ObjCollChecker {
    unsigned char data[0x18];
    ObjCollChecker();
};

struct AISystem {
    unsigned char data[0x4];
    AISystem(PathManager *path, ObjCollChecker *coll, int flag);
};

struct ItemSelect {
    unsigned char data[0x88];
    ItemSelect(int slot, int flag);
};

struct WeatherSystem {
    unsigned char data[0x1B4];
    WeatherSystem(int flag);
};

struct RaceHud {
    unsigned char data[0x80];
    RaceHud(PathManager *path);
};

struct SceneOverlay {
    unsigned char data[0x24];
    SceneOverlay(int frames);
};

struct RaceScene : GameModeBase {
    LakituStart *lakitu;           /* 0x04 */
    JyugemuFlag *jyugemuFlag;      /* 0x08 */
    JyugemuReverseFlag *jyugemuReverse; /* 0x0C */
    FinalLapBanner *lapBanner;     /* 0x10 */
    EnvironmentMgr *environment;   /* 0x14 */
    void *pad18;
    Scene3D *scene;                /* 0x1C */
    void *pad20[2];
    RaceCamera *camera;            /* 0x28 */
    RaceHud *hud;                  /* 0x2C */
    void *pad30;
    AISystem *ai;                  /* 0x34 */
    ObjCollChecker *coll;          /* 0x38 */
    SceneOverlay *overlay;         /* 0x3C */

    RaceScene();
    virtual ~RaceScene();
};

extern "C" {
extern char lbl_803211D8[];
extern const char lbl_806D4800[4];  /* "map" */
extern const char lbl_806D4804[6];  /* "light" */
extern const char lbl_806D480C[8];  /* "itembox" */
extern const char lbl_806D4814[5];  /* "coin" */
extern const char lbl_806D481C[7];  /* "center" */
extern const char lbl_806D4828[8];  /* "sprite2" */
extern const float lbl_806D47DC;
extern const float lbl_806D47E0;
extern const float lbl_806D47EC;
extern const float lbl_806D47F4;
extern const float lbl_806D4824;
extern RaceParams kRaceParamsTable[][3][2];

extern int *HSD_RandSeedPtr;
extern int g_raceSceneContextSwitch;
extern int lbl_806D1110;
extern int g_gameMode;
extern unsigned char g_isCommHost;
extern int g_spawnedKartCount;
extern unsigned char g_finalLapCoinJumpEnabled;
extern int lbl_806D1050;
extern int g_cupId;
extern int g_longRoundFlag;
extern int g_reverseRoundFlag;
extern int g_ccClass;
extern int g_kartVariant;
extern int g_playerKartSlot;
extern int g_kartStartSlot;
extern void *g_raceRenderTarget;
extern RaceCamera *g_raceCamera;
extern CarObject *g_carObjects[4];
extern ItemSelect *g_itemSelects[4];
extern unsigned char g_playerData[];
extern unsigned char g_namCamFlag;
extern void *g_playerRenderObj;
extern PathManager *g_pathManager;
extern unsigned char g_lakituDropOrderIssued;
extern unsigned char g_lakituStartAnimDone;
extern ObjCollChecker *g_objCollChecker;
extern int g_sceneTransitionTimer;
extern int lbl_806CF110;
extern unsigned char lbl_806D1264[3];
extern unsigned char g_raceEnded;
extern int g_raceEndExitTimer;
extern unsigned char g_rendererActivated;
extern int g_finalRacePosition;
extern float g_bestLapTime;
extern float g_currentLapTime;
extern float g_totalRaceTime;
extern int g_currentLap;
extern int g_raceResultCode;
extern unsigned char g_finalLapBannerShown;
extern unsigned char g_lapChangePending;
extern int g_totalLaps;
extern float g_raceTimeRemaining;
extern float g_lapBonusTimeDelta;
extern WeatherSystem *g_weatherSystem;
extern int g_raceFrameCounterLo2digits;
extern int g_roundIndex;
extern RaceHud *g_raceHud;
extern unsigned char g_fullThrottleHoldFlag;
extern unsigned int g_prevFrameTimestampLo;
extern unsigned int g_prevFrameTimestampHi;
extern int g_humanPlayerCount;
extern PathManager *g_raceRankingPathObject;

void SetSyncTarget(int target);
void ItemUse_ResetAllKartUseSlots(void);
void RaceScene_ClearPlayerSlotPointers(void);
void ProcessSystemTick(const char *msg);
void VoiceSystem_Init(void);
void SetResourceLoadingFlag(int flag);
void DMAChannelManager_Init(void);
int HeapStats_DumpForTag(const char *tag, int prev);
void TransitionEffect_GetOrCreate(void);
void SoundChannels_ClearAll(void);
void ItemObjectManager_Init(void);
void CourseObjectManager_Init(void);
void *CourseData_GetOrCreate(int cup, int longRound, int reverse);
void *GetCourseDataPtr(void);
void *HSD_LObjLoadDesc(void *desc);
void SetActiveCamera(int index, RaceCamera *cam);
void *GetRaceContextPtr(void);
void RankingTable_Init(void *ctx);
void *GetCourseBgmEntry(void);
void SoundDriver_GetOrCreate(void *entry);
void CoinSystem_Init(int a, int b);
int GetDisplayBufferIndex(void);
int GetKartStartSlot(int displayIdx);
void GetStartPosition(int slot, float *x, int flag, float *y);
float GetCourseStartYaw(void);
int GetKartSlotCharId(int slot);
void *CarObject_GetRenderObj(CarObject *car);
void KartItem_SetShortArray34a(void *renderObj, unsigned char *playerData);
void VoiceSystem_BindKartCarObject(int slot, CarObject *car);
void KartItem_SetField358(void *renderObj, int displayIdx);
void SetPlayerCarObject(CarObject *car);
float *CarObject_GetTransformMatrix(CarObject *car);
void *CourseData_GetDefaultPathKey_Safe(void);
void LakituStart_SetCountdownHoldFrames(LakituStart *lakitu, int frames);
const char **GetKartModelNameEntry(int charId, int variant);
void Scene3D_GetCameraPos(Scene3D *scene, float *x, float *y);
void Scene3D_SetupProjection(Scene3D *scene, float x, float y);
float RaceScene_GetPerspFovyForCup(void);
void CObj_UpdatePerspParam(Scene3D *scene, float fovy);
unsigned char *GetKartSlotKartVariant(int slot);
void ItemSelect_AddSlotItem(ItemSelect *sel, int item, int flag);
void SetCourseScene3D(Scene3D *scene);
void CourseBgm_Load(void);
void PreloadEffectResources(int set);
unsigned char ItemSelect_GetSlotItemId(ItemSelect *sel, int slot);
void PreloadItemResources(int item);
int fn_8023DBEC(int item);
void PreloadResource(int id);
void *GetEnemyParam(void);
void clEnemyParam_FillItemListIds(void *param, int mode, int cup, int round);
int *AI_GetItemList(void *param, int mode, int cup, int round, int index);
void PlayStats_OnRaceSceneInit_Stub(void);
void DebugPrintf(const char *fmt, ...);
void Tachometer_Init(void);
void HitMessageOverlay_Init(void);
void HUD_RegisterOverlay(RaceHud *hud, int id, int flag);
void fn_80253EB8(RaceHud *hud, float scale);
void HUD_SetTotalLaps(RaceHud *hud, int laps);
long long OSGetTime(void);
int TEXPalette_GetTotalLoadedSize(void);
int fn_80209A84(void);
void VoiceSystem_SetCheckpointsForTotalLaps(int laps);
void VoiceQueue_Clear(int flag);
}

static inline int CcClass_Get(void)
{
    return g_ccClass;
}

static inline int KartVariant_Get(void)
{
    return g_kartVariant;
}

static inline int GameMode_Get(void)
{
    return g_gameMode;
}

static inline int CupId_Get(void)
{
    return g_cupId;
}

static inline int RoundIndex_Get(void)
{
    return g_roundIndex;
}

static inline void PreloadItem(int item)
{
    PreloadItemResources(item);
    PreloadResource(fn_8023DBEC(item));
}

static inline void KartRender_SetItemSelect(void *render, ItemSelect *sel)
{
    *(ItemSelect **)((char *)render + 0x364) = sel;
}

RaceScene::RaceScene()
{
    char *const log = lbl_803211D8;
    int heap;
    float startX;
    float startY;
    int i;

    HSD_RandSeedPtr = &g_raceSceneContextSwitch;
    *HSD_RandSeedPtr = lbl_806D1110;
    g_gameMode = 0;
    SetSyncTarget(0x2A);
    g_isCommHost = 0;
    g_spawnedKartCount = 6;
    ItemUse_ResetAllKartUseSlots();
    g_finalLapCoinJumpEnabled = 0;
    lbl_806D1050 = 0;
    RaceScene_ClearPlayerSlotPointers();
    ProcessSystemTick(log + 0x4C8);
    VoiceSystem_Init();
    ProcessSystemTick(log + 0x4E0);
    SetResourceLoadingFlag(0);
    DMAChannelManager_Init();
    heap = HeapStats_DumpForTag(log + 0x4F0, 0);
    TransitionEffect_GetOrCreate();
    SoundChannels_ClearAll();
    heap = HeapStats_DumpForTag(log + 0x508, heap);
    ProcessSystemTick(log + 0x530);
    ItemObjectManager_Init();
    heap = HeapStats_DumpForTag(log + 0x554, heap);
    CourseObjectManager_Init();
    heap = HeapStats_DumpForTag(log + 0x568, heap);
    environment = new EnvironmentMgr;
    heap = HeapStats_DumpForTag(lbl_806D4800, heap);
    CourseData_GetOrCreate(g_cupId, g_longRoundFlag, g_reverseRoundFlag);
    heap = HeapStats_DumpForTag(log + 0x57C, heap);
    g_raceRenderTarget = HSD_LObjLoadDesc(GetCourseDataPtr());
    heap = HeapStats_DumpForTag(lbl_806D4804, heap);
    camera = new RaceCamera(lbl_806D47E0, 0x200, lbl_806D47DC, 0x200, g_raceRenderTarget);
    SetActiveCamera(0, camera);
    g_raceCamera = camera;
    heap = HeapStats_DumpForTag(log + 0x588, heap);
    ProcessSystemTick(log + 0x59C);
    RankingTable_Init(GetRaceContextPtr());
    SoundDriver_GetOrCreate(GetCourseBgmEntry());
    heap = HeapStats_DumpForTag(lbl_806D480C, heap);
    CoinSystem_Init(0, 2);
    heap = HeapStats_DumpForTag(lbl_806D4814, heap);
    g_playerKartSlot = GetKartStartSlot(GetDisplayBufferIndex());
    g_kartStartSlot = g_playerKartSlot;
    GetStartPosition(g_playerKartSlot, &startX, 0, &startY);
    g_carObjects[0] = new CarObject(GetDisplayBufferIndex(), GetKartSlotCharId(g_playerKartSlot), startX, startY,
                                    GetCourseStartYaw(), CcClass_Get(), KartVariant_Get(), 1, -1, 1, 0);
    {
        char *render = (char *)CarObject_GetRenderObj(g_carObjects[0]);
        *(int *)(render + 0x238) = 1;
    }
    KartItem_SetShortArray34a(CarObject_GetRenderObj(g_carObjects[0]), g_playerData);
    VoiceSystem_BindKartCarObject(g_playerKartSlot, g_carObjects[0]);
    if (g_namCamFlag) {
        KartItem_SetField358(CarObject_GetRenderObj(g_carObjects[0]), GetDisplayBufferIndex());
    }
    g_playerRenderObj = CarObject_GetRenderObj(g_carObjects[0]);
    heap = HeapStats_DumpForTag(log + 0x5A8, heap);
    ProcessSystemTick(log + 0x5B4);
    SetPlayerCarObject(g_carObjects[0]);
    {
        float *m = CarObject_GetTransformMatrix(g_carObjects[0]);
        g_pathManager = new PathManager(CourseData_GetDefaultPathKey_Safe(), g_carObjects[0],
                                        CarObject_GetRenderObj(g_carObjects[0]), &m[12], &m[13], &m[14]);
    }
    heap = HeapStats_DumpForTag(lbl_806D481C, heap);
    lakitu = new LakituStart(log + 0x5C4, g_playerKartSlot, lbl_806D47EC, lbl_806D47EC, lbl_806D47EC);
    LakituStart_SetCountdownHoldFrames(lakitu, 10000);
    scene = new Scene3D(*GetKartModelNameEntry(GetKartSlotCharId(g_playerKartSlot), -1));
    jyugemuFlag = new JyugemuFlag(scene);
    jyugemuReverse = new JyugemuReverseFlag(CarObject_GetRenderObj(g_carObjects[0]));
    lapBanner = new FinalLapBanner(CarObject_GetRenderObj(g_carObjects[0]));
    heap = HeapStats_DumpForTag(log + 0x5D8, heap);
    g_lakituDropOrderIssued = 0;
    ProcessSystemTick(log + 0x5E8);
    {
        float x;
        float y;
        Scene3D_GetCameraPos(scene, &x, &y);
        x += lbl_806D4824;
        Scene3D_SetupProjection(scene, x, y);
    }
    CObj_UpdatePerspParam(scene, RaceScene_GetPerspFovyForCup());
    g_lakituStartAnimDone = 0;
    coll = new ObjCollChecker;
    heap = HeapStats_DumpForTag(log + 0x5FC, heap);
    g_objCollChecker = coll;
    ai = new AISystem(g_pathManager, coll, 0);
    heap = HeapStats_DumpForTag(log + 0x610, heap);
    ProcessSystemTick(log + 0x624);
    g_sceneTransitionTimer = -1;
    heap = HeapStats_DumpForTag(lbl_806D4828, heap);
    g_itemSelects[0] = 0;
    g_itemSelects[1] = 0;
    g_itemSelects[2] = 0;
    g_itemSelects[3] = 0;
    {
        unsigned char *variant = GetKartSlotKartVariant(g_playerKartSlot);
        variant[0x2D0] = 1;
    }
    g_itemSelects[0] = new ItemSelect(g_playerKartSlot, 1);
    heap = HeapStats_DumpForTag(log + 0x640, heap);
    *(ItemSelect **)((char *)g_carObjects[0] + 0x104) = g_itemSelects[0];
    KartRender_SetItemSelect(CarObject_GetRenderObj(g_carObjects[0]), g_itemSelects[0]);
    if (lbl_806CF110 == 1) {
        ItemSelect_AddSlotItem(g_itemSelects[0], lbl_806D1264[0], 1);
        ItemSelect_AddSlotItem(g_itemSelects[0], lbl_806D1264[1], 1);
        ItemSelect_AddSlotItem(g_itemSelects[0], lbl_806D1264[2], 1);
    } else {
        ItemSelect_AddSlotItem(g_itemSelects[0], lbl_806D1264[0], 1);
        ItemSelect_AddSlotItem(g_itemSelects[0], 0x3D, 1);
        ItemSelect_AddSlotItem(g_itemSelects[0], 0x2B, 1);
        ItemSelect_AddSlotItem(g_itemSelects[0], 0x17, 1);
        ItemSelect_AddSlotItem(g_itemSelects[0], 0x32, 1);
    }
    ProcessSystemTick(log + 0x64C);
    SetCourseScene3D(scene);
    {
        g_raceEnded = 0;
        g_raceEndExitTimer = 0;
        g_rendererActivated = 0;
        g_finalRacePosition = 6;
        g_bestLapTime = lbl_806D47EC;
        g_currentLapTime = lbl_806D47EC;
        g_totalRaceTime = lbl_806D47EC;
        g_currentLap = 1;
        g_raceResultCode = -2;
        g_finalLapBannerShown = 0;
        g_lapChangePending = 0;
        g_totalLaps = kRaceParamsTable[g_cupId - 1][g_ccClass][g_longRoundFlag].laps;
        g_raceTimeRemaining = kRaceParamsTable[g_cupId - 1][g_ccClass][g_longRoundFlag].timeLimit;
        g_lapBonusTimeDelta = kRaceParamsTable[g_cupId - 1][g_ccClass][g_longRoundFlag].lapBonus;
    }
    ProcessSystemTick(log + 0x65C);
    CourseBgm_Load();
    if (g_weatherSystem == 0) {
        g_weatherSystem = new WeatherSystem(1);
    }
    SetResourceLoadingFlag(1);
    g_raceFrameCounterLo2digits = 0;
    switch (g_cupId) {
    case 1:
        PreloadEffectResources(1);
        break;
    case 2:
        PreloadEffectResources(2);
        break;
    case 3:
        PreloadEffectResources(3);
        break;
    case 4:
        PreloadEffectResources(4);
        break;
    case 5:
        PreloadEffectResources(5);
        break;
    case 6:
        PreloadEffectResources(6);
        break;
    case 7:
        PreloadEffectResources(7);
        break;
    case 8:
        PreloadEffectResources(8);
        break;
    }
    ProcessSystemTick(log + 0x670);
    PreloadEffectResources(9);
    ProcessSystemTick(log + 0x690);
    PreloadEffectResources(10);
    ProcessSystemTick(log + 0x6B0);
    for (i = 0; i < (lbl_806CF110 == 1 ? 3 : 5); i++) {
        unsigned char item = ItemSelect_GetSlotItemId(g_itemSelects[0], i);
        if (item != 0) {
            PreloadItemResources(item);
            PreloadResource(fn_8023DBEC(item));
        }
    }
    ProcessSystemTick(log + 0x6D0);
    clEnemyParam_FillItemListIds(GetEnemyParam(), GameMode_Get(), CupId_Get(), RoundIndex_Get());
    for (i = 0; i < 6; i++) {
        int *list = AI_GetItemList(GetEnemyParam(), GameMode_Get(), CupId_Get(), RoundIndex_Get(), i);
        while (*list != -1) {
            PreloadItemResources(*list);
            PreloadResource(fn_8023DBEC(*list));
            list++;
        }
    }
    ProcessSystemTick(log + 0x6EC);
    SetSyncTarget(0x2C);
    PlayStats_OnRaceSceneInit_Stub();
    DebugPrintf(log + 0x708);
    Tachometer_Init();
    HitMessageOverlay_Init();
    hud = new RaceHud(g_pathManager);
    g_raceHud = hud;
    HUD_RegisterOverlay(hud, 6, 0);
    HUD_RegisterOverlay(hud, 3, 0);
    HUD_RegisterOverlay(hud, 5, 0);
    HUD_RegisterOverlay(hud, 1, 0);
    HUD_RegisterOverlay(hud, 2, 0);
    HUD_RegisterOverlay(hud, 0xA, 0);
    HUD_RegisterOverlay(hud, 0xC, 0);
    HUD_RegisterOverlay(hud, 0xB, 0);
    HUD_RegisterOverlay(hud, 7, 0);
    HUD_RegisterOverlay(hud, 0, 0);
    HUD_RegisterOverlay(hud, 0xF, 0);
    HUD_RegisterOverlay(hud, 0x10, 0);
    HUD_RegisterOverlay(hud, 0xE, 0);
    HUD_RegisterOverlay(hud, 4, 0);
    HUD_RegisterOverlay(hud, 0xD, 0);
    fn_80253EB8(hud, lbl_806D47F4);
    HUD_RegisterOverlay(hud, 8, 0);
    HUD_RegisterOverlay(hud, 9, 0);
    HUD_SetTotalLaps(hud, g_totalLaps);
    HUD_RegisterOverlay(hud, 0x15, 0);
    ProcessSystemTick(log + 0x73C);
    DebugPrintf(log + 0x750);
    g_fullThrottleHoldFlag = 0;
    {
        long long t = OSGetTime();
        g_prevFrameTimestampLo = (unsigned int)t;
        g_prevFrameTimestampHi = (unsigned int)(t >> 32);
    }
    {
        int texSize = TEXPalette_GetTotalLoadedSize();
        DebugPrintf(log + 0x784, texSize);
    }
    ProcessSystemTick(log + 0x794);
    g_humanPlayerCount = fn_80209A84();
    overlay = new SceneOverlay(0x168);
    VoiceSystem_SetCheckpointsForTotalLaps(g_totalLaps);
    g_raceRankingPathObject = g_pathManager;
    VoiceQueue_Clear(0);
}
