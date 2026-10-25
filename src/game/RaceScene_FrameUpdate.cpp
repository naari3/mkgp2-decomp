/* RaceScene_FrameUpdate (0x800A0EF4): per-frame update of the race scene.
 * Reads the player's pad (or steers automatically once the race is over),
 * drives the kart, item pickup, Lakitu, flags and lap banner, counts the
 * time limit down, and handles the finish: result ranking, the 1st place
 * Jyugemu and the exit timer. Returns the next scene id (0xD after the
 * finish wait, 2 on the debug exit button) or -2 to stay.
 * NonMatching (99.99%): the hold-reset branch materialises its 0 in r3
 * instead of r0. */

typedef struct Vec {
    float x, y, z;
} Vec;

struct InputPlayer {
    virtual void v0();
    virtual void v1();
    virtual float Accel();
    virtual void v3();
    virtual float Steer();
    virtual float Brake();
    virtual unsigned char Pressed(int mask);
    virtual void v7();
    virtual unsigned int Held(int mask);
};

struct RaceScene {
    void *vtable;
    void *lakitu;          /* 0x04 */
    void *jyugemuFlag;     /* 0x08 */
    void *jyugemuReverse;  /* 0x0C */
    void *lapBanner;       /* 0x10 */
    void *environment;     /* 0x14 */
    void *pad18;
    void *scene;           /* 0x1C */
    void *pad20[3];
    void *hud;             /* 0x2C */
    void *pad30;
    void *ai;              /* 0x34 */
    void *coll;            /* 0x38 */
    void *overlay;         /* 0x3C */
};

extern "C" {
extern unsigned char g_lakituDropOrderIssued;
extern int g_currentSceneState;
extern int g_raceFrameCounterLo2digits;
extern int g_sceneTransitionTimer;
extern void *g_pathManager;
extern void *lbl_806D10A0;
extern void *lbl_806D109C;
extern void *lbl_806D10D0;
extern unsigned char g_raceEnded;
extern int g_ccClass;
extern unsigned int g_prevFrameTimestampHi;
extern unsigned int g_prevFrameTimestampLo;
extern unsigned char g_fullThrottleHoldFlag;
extern void *g_carObjects[];
extern void *g_itemSelects[];
extern unsigned char g_playerData[];
extern Vec lbl_803215D4;
extern Vec lbl_803215E0;
extern unsigned char g_rendererActivated;
extern Vec lbl_805D2B10;
extern Vec lbl_805D2B1C;
extern unsigned char g_rendererGateFlag;
extern float g_raceTimeRemaining;
extern unsigned char g_nonFirstFinishFlag;
extern int g_currentLap;
extern int g_totalLaps;
extern float g_currentLapTime;
extern float g_bestLapTime;
extern float g_totalRaceTime;
extern int g_finalRacePosition;
extern unsigned char g_finalLapBannerShown;
extern int g_raceResultCode;
extern unsigned char g_finalLapCoinJumpEnabled;
extern unsigned char lbl_806CF270;
extern void *g_playerRenderObj;
extern int g_playerKartSlot;
extern int g_cupId;
extern int g_roundIndex;
extern int g_raceEndExitTimer;
extern unsigned char g_lakituStartAnimDone;
extern unsigned char g_lapChangePending;
extern void *g_weatherSystem;
extern unsigned char lbl_806D0051;

void Race_PerFrameTickAndAudio(void);
unsigned char Live_IsConnectReady(void);
void LakituStart_SetCountdownHoldFrames(void *lakitu, int frames);
unsigned char fn_8020B07C(void *overlay);
void fn_8020AF08(void *overlay, int flag);
int rand(void);
void SetSyncTarget(int target);
void PathManager_RefreshFinishPositions(void *path);
void TitleStats_FinalizeRace_WithRankSnapshot(void *stats);
void *GetInputManager(void);
InputPlayer *InputMgr_GetPlayer(void *mgr, int index);
void *GetRaceContextPtr(void);
void ItemObjectManager_PerFrameUpdate(void *ctx);
long long OSGetTime(void);
unsigned char IsRaceStarted(void);
void *CarObject_GetRenderObj(void *car);
float CalcSoundDirection(void *render, void *path, float *steer, int flag);
void CarObject_ApplyInput(void *car, float accel, float steer, float brake, unsigned char started);
void CarObject_FrameUpdate(void *car, unsigned int held);
void ItemBox_ProcessPickup(void *sel, void *car, int a, unsigned int held, int b, float steer);
int GetCoinMilage(unsigned char *playerData);
void CoinJumpFlasher_Toggle(void *car);
void RankingMgr_UpdatePositions(void *ai);
float *Path_LookupCheckpointOffset(void *path, int a, int b);
unsigned char JObj_IsForwardDotBelowThreshold(void *render, Vec *a, Vec *b);
void Jyugemu_ReverseFlag_SetState(void *flag, int state);
void fn_801B3BC8(void *p);
void fn_801B3B7C(void *p);
int GetDisplayBufferIndex(void);
void TitleStats_AccumDistanceCounter(void *stats, int display, int reverse);
void fn_80208E30(void *coll);
void KartItem_UpdateShadowBillboardAndViewport(void *car, void *scene, int flag);
void Fog_UpdateFromCourseScene3D(void);
void PathManager_UpdateAll(void *path);
unsigned char LakituStart_UpdateCountdown(void *lakitu);
void LakituStart_Dtor(void *lakitu, int flag);
void Jyugemu_Flag_Tick(void *flag);
void Jyugemu_ReverseFlag_Tick(void *flag);
void LapBannerScene_UpdateAndDriveAnim(void *banner);
void CourseEnvironment_UpdateAndCullZones_Timed(void *env);
void CObj_LoadProjMatrix(void *scene, Vec *v);
void CObj_ApplyScissor(void *scene, Vec *v);
void ItemObjectManager_Update(void);
void VfxSlotMgr_Update(Vec a, Vec b);
void fn_80253BE4(void *hud);
void fn_8016C554(int flag);
void fn_801B12A0(void);
void Tachometer_RenderDigits(void);
void HitMessageOverlay_FrameUpdate(void);
void HUD_SetCurrentLap(void *hud, int lap);
void fn_80253FD8(void *hud, float time);
float CarObject_CalcSpeedRatio(void *car);
void fn_80253EBC(void *hud, float v);
float KartItem_GetCurrentSpeedWithBonus(void *car);
void fn_80253EC0(void *hud, float v);
void fn_80253EC4(void *hud, float v);
void fn_80253F2C(void *hud, float v);
void HUD_SetRacePosition(void *hud, int pos);
void fn_80253E18(void *hud, int v);
void TransitionEffect_Tick(void *fx);
void fn_80253DF0(void *hud);
void KartItem_OnFallOffOrDeath(void *car);
void CoinJumpFlasher_SetArmed(void *car, int armed);
void ItemSelect_Reset(void *sel, int flag);
int GetKartSlotCharId(int slot);
void RaceResult_StoreLatest(int charId, int pos, float best, float total);
int RaceResult_InsertSortedRank(int charId, int pos, float best, float total);
void SetRaceResultLatestPtr(void);
void fn_801D680C(unsigned char *playerData, int cup, int round, int win);
void fn_801D67F4(unsigned char *playerData);
void fn_80253D00(void *hud);
void Object_SetByte10_Return1(void *scene, int v);
void Jyugemu_Flag_SetKartDriver(void *flag, void *render);
void PlayStats_OnRace1stPlace_Stub(void);
void CoinEvent_PlayResultSE(void *car, int pos);
void RankLog_SetRaceResult(void *stats, int display, int pos, int time);
void fn_8016C598(void);
void LapBannerScene_TriggerBannerAnim(void *banner);
void fn_8016C5CC(void);
void TitleTracker_ResetPerRound(void *stats, int display, int lap);
void HUD_FrameUpdate(void *hud);
void clItemBoxManager_Update(void *mgr);
void fn_8013A534(void);
void fn_8016B32C(void *weather);
}

static inline void *TitleStats(void)
{
    if (lbl_806D10A0 == 0) {
        return 0;
    }
    return lbl_806D10A0;
}

static inline void *Transition(void)
{
    if (lbl_806D109C == 0) {
        return 0;
    }
    return lbl_806D109C;
}

static inline void *ItemBoxMgr(void)
{
    if (lbl_806D10D0 == 0) {
        return 0;
    }
    return lbl_806D10D0;
}

static inline float QuantizeInput(float v)
{
    return (float)(int)(10000.0f * v) / 10000.0f;
}

extern "C" int RaceScene_FrameUpdate(RaceScene *self)
{
    InputPlayer *pad;
    float steer;
    float accel;
    float brake;
    unsigned int held;
    unsigned char started;

    Race_PerFrameTickAndAudio();
    if (!g_lakituDropOrderIssued && Live_IsConnectReady()) {
        g_lakituDropOrderIssued = 1;
        if (self->lakitu != 0) {
            LakituStart_SetCountdownHoldFrames(self->lakitu, -1);
        }
    }
    if (self->overlay != 0 && fn_8020B07C(self->overlay)) {
        fn_8020AF08(self->overlay, 1);
        self->overlay = 0;
    }

    g_raceFrameCounterLo2digits = rand() % 100;
    if (g_currentSceneState == 0x2D) {
        if (Live_IsConnectReady()) {
            if (--g_sceneTransitionTimer <= 0) {
                PathManager_RefreshFinishPositions(g_pathManager);
                void *stats = TitleStats();
                if (stats != 0) {
                    TitleStats_FinalizeRace_WithRankSnapshot(stats);
                }
                return 0xD;
            }
        } else {
            g_sceneTransitionTimer = 0xB4;
        }
    }
    if (g_currentSceneState != 0x2D && g_sceneTransitionTimer > 0) {
        if (--g_sceneTransitionTimer <= 0) {
            g_sceneTransitionTimer = 0xB4;
            SetSyncTarget(0x2D);
        }
    }

    pad = InputMgr_GetPlayer(GetInputManager(), 0);
    ItemObjectManager_PerFrameUpdate(GetRaceContextPtr());
    if (g_raceEnded != 1) {
        long long now = OSGetTime();

        steer = QuantizeInput(pad->Steer());
        brake = QuantizeInput(pad->Brake());
        if (g_ccClass != 2) {
            if (!IsRaceStarted()) {
                g_prevFrameTimestampLo = (unsigned int)now;
                g_prevFrameTimestampHi = (unsigned int)(now >> 32);
            } else if (steer < 0.1f && brake < 0.1f) {
                if (!g_fullThrottleHoldFlag) {
                    long long prev = ((long long)g_prevFrameTimestampHi << 32) | g_prevFrameTimestampLo;
                    long long ms = (now - prev) / ((*(unsigned int *)0x800000F8 / 4) / 1000);
                    if ((float)ms / 1000.0f >= 4.0f) {
                        g_fullThrottleHoldFlag = 1;
                    }
                }
                if (g_fullThrottleHoldFlag) {
                    steer = 1.0f;
                }
            } else {
                g_prevFrameTimestampLo = (unsigned int)now;
                g_fullThrottleHoldFlag = 0;
                g_prevFrameTimestampHi = (unsigned int)(now >> 32);
            }
        }
        accel = QuantizeInput(pad->Accel());
        started = IsRaceStarted();
        held = pad->Held(0xE7FF);
    } else {
        accel = CalcSoundDirection(CarObject_GetRenderObj(g_carObjects[0]), g_pathManager, &steer, 0);
        brake = 0.0f;
        started = 1;
        held = 0;
    }
    CarObject_ApplyInput(g_carObjects[0], accel, steer, brake, started);
    CarObject_FrameUpdate(g_carObjects[0], held);
    ItemBox_ProcessPickup(g_itemSelects[0], g_carObjects[0], 0, held, 1, steer);
    if (!g_raceEnded && pad->Held(0x400) && GetCoinMilage(g_playerData) >= 4000) {
        CoinJumpFlasher_Toggle(g_carObjects[0]);
    }
    RankingMgr_UpdatePositions(self->ai);

    if (IsRaceStarted() == 1) {
        float *cp0 = Path_LookupCheckpointOffset(g_pathManager, 0, 0);
        float *cp1 = Path_LookupCheckpointOffset(g_pathManager, 0, 1);
        Vec a = lbl_803215D4;
        a.x = cp0[1];
        a.z = cp0[3];
        Vec b = lbl_803215E0;
        b.x = cp1[1];
        b.z = cp1[3];
        if (JObj_IsForwardDotBelowThreshold(CarObject_GetRenderObj(g_carObjects[0]), &a, &b) == 1) {
            Jyugemu_ReverseFlag_SetState(self->jyugemuReverse, 1);
            fn_801B3BC8(*(void **)((char *)CarObject_GetRenderObj(g_carObjects[0]) + 0x248));
            void *stats = TitleStats();
            if (stats != 0) {
                TitleStats_AccumDistanceCounter(stats, GetDisplayBufferIndex(), 1);
            }
        } else {
            Jyugemu_ReverseFlag_SetState(self->jyugemuReverse, 0);
            fn_801B3B7C(*(void **)((char *)CarObject_GetRenderObj(g_carObjects[0]) + 0x248));
            void *stats = TitleStats();
            if (stats != 0) {
                TitleStats_AccumDistanceCounter(stats, GetDisplayBufferIndex(), 0);
            }
        }
    }

    fn_80208E30(self->coll);
    if (!g_rendererActivated) {
        g_rendererActivated = 1;
    }
    KartItem_UpdateShadowBillboardAndViewport(g_carObjects[0], self->scene, 0);
    Fog_UpdateFromCourseScene3D();
    PathManager_UpdateAll(g_pathManager);
    if (self->lakitu != 0 && !LakituStart_UpdateCountdown(self->lakitu)) {
        LakituStart_Dtor(self->lakitu, 1);
        self->lakitu = 0;
    }
    Jyugemu_Flag_Tick(self->jyugemuFlag);
    Jyugemu_ReverseFlag_Tick(self->jyugemuReverse);
    LapBannerScene_UpdateAndDriveAnim(self->lapBanner);
    CourseEnvironment_UpdateAndCullZones_Timed(self->environment);
    CObj_LoadProjMatrix(self->scene, &lbl_805D2B10);
    CObj_ApplyScissor(self->scene, &lbl_805D2B1C);
    ItemObjectManager_Update();
    VfxSlotMgr_Update(lbl_805D2B10, lbl_805D2B1C);

    if (g_currentSceneState != 0x2D && g_rendererGateFlag == 1 && IsRaceStarted() == 1 &&
        g_raceTimeRemaining > 0.0f) {
        g_raceTimeRemaining -= 0.016666668f;
        if (g_raceTimeRemaining < 0.0f) {
            g_raceTimeRemaining = 0.0f;
            if (!g_raceEnded) {
                fn_80253BE4(self->hud);
                g_sceneTransitionTimer = 0x3C;
                fn_8016C554(0);
                fn_801B12A0();
                g_nonFirstFinishFlag = 1;
            }
        }
    }

    Tachometer_RenderDigits();
    HitMessageOverlay_FrameUpdate();
    HUD_SetCurrentLap(self->hud, g_currentLap);
    fn_80253FD8(self->hud, g_raceTimeRemaining);
    fn_80253EBC(self->hud, 100.0f * CarObject_CalcSpeedRatio(g_carObjects[0]));
    fn_80253EC0(self->hud, KartItem_GetCurrentSpeedWithBonus(g_carObjects[0]));
    fn_80253EC4(self->hud, g_currentLapTime);
    fn_80253F2C(self->hud, g_bestLapTime);
    HUD_SetRacePosition(self->hud, g_finalRacePosition);
    fn_80253E18(self->hud, *(int *)((char *)CarObject_GetRenderObj(g_carObjects[0]) + 0x2CC));
    TransitionEffect_Tick(Transition());
    if (!g_finalLapBannerShown && g_currentLap >= g_totalLaps) {
        g_finalLapBannerShown = 1;
        fn_80253DF0(self->hud);
    }

    if (0.0f != g_raceTimeRemaining && g_raceResultCode == -2) {
        if (g_currentLap >= g_totalLaps + 1) {
            void *stats;

            if (g_finalLapCoinJumpEnabled == 1) {
                CoinJumpFlasher_Toggle(g_carObjects[0]);
            }
            lbl_806CF270 = 0;
            KartItem_OnFallOffOrDeath(g_carObjects[0]);
            CoinJumpFlasher_SetArmed(g_carObjects[0], 0);
            ItemSelect_Reset(g_itemSelects[0], 0);
            g_finalRacePosition = *(int *)((char *)g_playerRenderObj + 0x23C);
            RaceResult_StoreLatest(GetKartSlotCharId(g_playerKartSlot), g_finalRacePosition, g_bestLapTime,
                                   g_totalRaceTime);
            g_raceResultCode = RaceResult_InsertSortedRank(GetKartSlotCharId(g_playerKartSlot),
                                                           g_finalRacePosition, g_bestLapTime, g_totalRaceTime);
            SetRaceResultLatestPtr();
            if (g_finalRacePosition == 0) {
                fn_801D680C(g_playerData, g_cupId - 1, g_roundIndex, 1);
            } else {
                fn_801D680C(g_playerData, g_cupId - 1, g_roundIndex, 0);
                fn_801D67F4(g_playerData);
            }
            fn_80253D00(self->hud);
            Object_SetByte10_Return1(self->scene, 1);
            if (g_finalRacePosition == 0) {
                Jyugemu_Flag_SetKartDriver(self->jyugemuFlag, CarObject_GetRenderObj(g_carObjects[0]));
                fn_8016C554(1);
                PlayStats_OnRace1stPlace_Stub();
                g_nonFirstFinishFlag = 0;
            } else {
                fn_8016C554(0);
                g_nonFirstFinishFlag = 1;
            }
            CoinEvent_PlayResultSE(g_carObjects[0], g_finalRacePosition);
            g_raceEnded = 1;
            g_lakituStartAnimDone = 0;
            g_raceEndExitTimer++;
            stats = TitleStats();
            if (stats != 0) {
                RankLog_SetRaceResult(stats, GetDisplayBufferIndex(), g_finalRacePosition, (int)g_raceTimeRemaining);
            }
        } else if (g_lapChangePending) {
            if (g_finalLapBannerShown) {
                fn_8016C598();
                LapBannerScene_TriggerBannerAnim(self->lapBanner);
            } else {
                fn_8016C5CC();
            }
            void *stats = TitleStats();
            if (stats != 0) {
                TitleTracker_ResetPerRound(stats, GetDisplayBufferIndex(), g_currentLap - 1);
            }
            g_lapChangePending = 0;
        }
    } else if (g_raceEndExitTimer != 0 && g_currentSceneState != 0x2D) {
        if (++g_raceEndExitTimer >= 0x3C) {
            g_sceneTransitionTimer = 0xB4;
            SetSyncTarget(0x2D);
        }
    }

    HUD_FrameUpdate(self->hud);
    clItemBoxManager_Update(ItemBoxMgr());
    fn_8013A534();
    if (g_weatherSystem != 0) {
        fn_8016B32C(g_weatherSystem);
    }
    if (!lbl_806D0051 && pad->Pressed(0x400) == 1) {
        return 2;
    }
    return -2;
}
