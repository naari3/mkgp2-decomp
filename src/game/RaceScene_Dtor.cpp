/* RaceScene_Dtor (0x800A1A1C): deleting destructor of the race scene.
 * Tears down the HUD, the karts, the course and the per-race managers in
 * the reverse order of RaceScene_Init, logging each step, then falls back
 * to the GameModeBase vtable. */

struct Deletable {
    virtual ~Deletable();
};

struct CarObject {
    virtual void v0();
    virtual void Destroy(int flag);
};

struct HsdClass {
    unsigned char pad0[0x30];
    void (*release)(void *obj);
    void (*destroy)(void *obj);
};

struct HsdObj {
    HsdClass *klass;
    unsigned short pad4;
};

struct HsdRefObj {
    HsdClass *klass;
    unsigned short ref;
};

struct RaceScene {
    void *vtable;
    void *lakitu;          /* 0x04 */
    void *jyugemuFlag;     /* 0x08 */
    void *jyugemuReverse;  /* 0x0C */
    void *lapBanner;       /* 0x10 */
    void *environment;     /* 0x14 */
    void *pad18;
    Deletable *camera;     /* 0x1C */
    void *pad20[2];
    Deletable *shadow;     /* 0x28 */
    void *hud;             /* 0x2C */
    void *pad30;
    void *ai;              /* 0x34 */
    void *hud38;           /* 0x38 */
    void *overlay;         /* 0x3C */
};

extern "C" {
extern char lbl_803211D8[];
extern char g_RaceModeVtable[];
extern char lbl_8040E76C[];
extern void *g_weatherSystem;
extern CarObject *g_carObjects[];
extern void *g_itemSelects[];
extern void *g_pathManager;
extern HsdRefObj *g_raceRenderTarget;
extern Deletable *lbl_806D10D0;
extern Deletable *lbl_806D109C;
extern Deletable *g_courseData;
extern void *g_raceCamera;

void fn_801B6B94(void);
void fn_8016C634(void *p, int flag);
void SetActiveCamera(void *cam, int flag);
void fn_8020AF08(void *p, int flag);
void ProcessSystemTick(const char *msg);
void AI_SystemDtor(void *p, int flag);
void fn_80208FE4(void *p, int flag);
void ItemSelect_Dtor(void *p, int flag);
void Tachometer_Destroy(void);
void HitMessageOverlay_Destroy(void);
void fn_80254134(void *p, int flag);
void LakituStart_Dtor(void *p, int flag);
void Jyugemu_Flag_Dtor(void *p, int flag);
void Jyugemu_ReverseFlag_Dtor(void *p, int flag);
void LapBannerScene_Dtor(void *p, int flag);
void PathParticipantArray_Dtor(void *p, int flag);
void CourseEnvironment_Dtor(void *p, int flag);
void ItemObjectManager_Reset(void);
void VfxSlotMgr_Shutdown(void);
void *GetRaceContextPtr(void);
void RankingTable_Init(void *ctx);
void ClRomTable_PurgeAll(void);
void SetPlayerCarObject(void *car);
void fn_8013A6F8(void);
void CourseBgm_Free(void);
void SceneDrawList_Reset(void);
void SetResourceLoadingFlag(int flag);
void clRom_PurgeAll(void);
void SetCourseScene3D(void *scene);
void MemoryManager_TimedFree(void *p);
}

static inline int HsdRef_Dec(HsdRefObj *o)
{
    int done = o->ref == (unsigned short)-1;
    if (done) {
        return done;
    }
    return o->ref-- == 0;
}

static inline void HsdRef_Unref(HsdRefObj *o)
{
    if (o == 0) {
        return;
    }
    if (HsdRef_Dec(o)) {
        if (o != 0) {
            o->klass->release(o);
            o->klass->destroy(o);
        }
    }
}

extern "C" RaceScene *RaceScene_Dtor(RaceScene *self, short flag)
{
    const char *log = lbl_803211D8;

    if (self != 0) {
        self->vtable = g_RaceModeVtable;
        fn_801B6B94();
        if (g_weatherSystem != 0) {
            fn_8016C634(g_weatherSystem, 1);
            g_weatherSystem = 0;
        }
        SetActiveCamera(0, 0);
        if (self->overlay != 0) {
            fn_8020AF08(self->overlay, 1);
            self->overlay = 0;
        }
        ProcessSystemTick(log + 0x430);
        AI_SystemDtor(self->ai, 1);
        fn_80208FE4(self->hud38, 1);
        ProcessSystemTick(log + 0x440);
        ItemSelect_Dtor(g_itemSelects[0], 1);
        Tachometer_Destroy();
        HitMessageOverlay_Destroy();
        ProcessSystemTick(log + 0x44C);
        fn_80254134(self->hud, 1);
        delete self->camera;
        LakituStart_Dtor(self->lakitu, 1);
        Jyugemu_Flag_Dtor(self->jyugemuFlag, 1);
        Jyugemu_ReverseFlag_Dtor(self->jyugemuReverse, 1);
        LapBannerScene_Dtor(self->lapBanner, 1);
        PathParticipantArray_Dtor(g_pathManager, 1);
        ProcessSystemTick(log + 0x470);
        if (g_carObjects[0] != 0) {
            g_carObjects[0]->Destroy(1);
        }
        if (self->shadow != 0) {
            delete self->shadow;
        }
        CourseEnvironment_Dtor(self->environment, 1);
        ProcessSystemTick(log + 0x484);
        if (g_raceRenderTarget != 0) {
            HsdRef_Unref(g_raceRenderTarget);
            g_raceRenderTarget = 0;
        }
        ItemObjectManager_Reset();
        VfxSlotMgr_Shutdown();
        RankingTable_Init(GetRaceContextPtr());
        ClRomTable_PurgeAll();
        self->lakitu = 0;
        self->jyugemuFlag = 0;
        self->jyugemuReverse = 0;
        self->lapBanner = 0;
        g_carObjects[0] = 0;
        g_pathManager = 0;
        self->camera = 0;
        self->environment = 0;
        SetPlayerCarObject(0);
        delete lbl_806D10D0;
        lbl_806D10D0 = 0;
        fn_8013A6F8();
        g_raceCamera = 0;
        CourseBgm_Free();
        SceneDrawList_Reset();
        delete lbl_806D109C;
        lbl_806D109C = 0;
        delete g_courseData;
        g_courseData = 0;
        ProcessSystemTick(log + 0x49C);
        SetResourceLoadingFlag(0);
        clRom_PurgeAll();
        SetCourseScene3D(0);
        ProcessSystemTick(log + 0x4B8);
        if (self != 0) {
            self->vtable = lbl_8040E76C;
        }
        if (flag > 0) {
            MemoryManager_TimedFree(self);
        }
    }
    return self;
}
