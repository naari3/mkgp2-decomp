/* Exact asm_fn implementation for the remaining RivalRun unit members. */
/* Generated from the nine dtk auto_RivalRun_* target assembly fragments. */
/* Keep function/extab/extabindex order aligned with the target ranges. */

/* --- shared types for the native C members --- */
typedef struct RRVec3 {
    float x, y, z;
} RRVec3;

/* PathFollower context (0x2C bytes, see RivalRun_PathFollowerInit.c) */
typedef struct RRPathFollower {
    unsigned char needsSearch; /* 0x00 */
    int lane;                  /* 0x04 (row of RivalRun_rodata_8035C1E4) */
    int route;                 /* 0x08 (0/1, toggled by warp zones) */
    int seg;                   /* 0x0C */
    RRVec3 target;             /* 0x10 */
    RRVec3 dir;                /* 0x1C */
    float endDist;             /* 0x28 */
} RRPathFollower;

/* rival driver block (built by RivalRun_RivalInit) */
typedef struct RRRivalAI {
    void *info;                /* 0x00 */
    void *car;                 /* 0x04 */
    RRVec3 pos;                /* 0x08 */
    void *path;                /* 0x14 */
    int pathSlot;              /* 0x18 */
    int raceSlot;              /* 0x1C */
    RRPathFollower *follower;  /* 0x20 */
    int laneCooldown;          /* 0x24 */
    RRVec3 aim;                /* 0x28 */
    int driftDir;              /* 0x34 */
    unsigned char fast;        /* 0x38 */
    int holdFrames;            /* 0x3C */
    int itemCooldown;          /* 0x40 */
    int item;                  /* 0x44 */
    int aimFrames;             /* 0x48 */
    float accelScale;          /* 0x4C */
    void *rivalRender;         /* 0x50 */
} RRRivalAI;

#pragma cplusplus on
/* scene camera object (self->scene) */
struct RRScene {
    virtual void v08();
    virtual unsigned char BeginDraw(); /* vtable +0x0C */
    virtual void EndDraw();            /* vtable +0x10 */
};

#pragma cplusplus reset

typedef struct RRLight {
    struct RRLightInfo *info; /* 0x00 */
    unsigned short references; /* 0x04 */
} RRLight;

typedef struct RRLightInfo {
    unsigned char pad0[0x30];
    void (*release)(RRLight *); /* 0x30 */
    void (*destroy)(RRLight *); /* 0x34 */
} RRLightInfo;

/* per-rival AI block (self->rival) */
typedef struct RRRival {
    unsigned char pad0[4];
    void *car;            /* 0x04 */
    unsigned char pad8[0xC];
    void *path;           /* 0x14 */
    int pathSlot;         /* 0x18 */
    unsigned char pad1C[4];
    void *buffer;         /* 0x20 */
} RRRival;

typedef struct RivalRunState {
    void *vtable;         /* 0x00 */
    unsigned char pad4[4];
    void *car;            /* 0x08 */
    void *lakitu;         /* 0x0C */
    void *environment;    /* 0x10 */
    struct RRScene *scene; /* 0x14 */
    void *goalCamera;     /* 0x18 */
    void *camera;         /* 0x1C */
    RRLight *lights;      /* 0x20 */
    void *participants;   /* 0x24 */
    void *hud;            /* 0x28 */
    void *collision;      /* 0x2C */
    RRRival *rival;       /* 0x30 */
    unsigned char active;  /* 0x34 */
    unsigned char pad35;
    unsigned char finished; /* 0x36 */
    unsigned char won;     /* 0x37 */
    int resultFrames;      /* 0x38 */
} RivalRunState;

#include "game/singleton.h"

/* === extracted from auto_RivalRun_Draw_text === */
/* Copy into the TU between forward decls and function bodies; */
/* keep emit order = target section layout (do not sort). */

/* --- extern decls: branch callees (bl/b targets) --- */
/* Open prototype (`extern void Foo();`) accepts any call signature; */
/* refine if the real prototype matters for header consumers. */
extern void CObj_DebugVizPathFlush();
extern void CourseEnvironment_RenderObjects_Timed();
extern void DrawEffect_TickAndCull();
extern void ItemObjectManager_Render();
extern void KartItem_RenderPipelinedWithEffects();
extern void Object_RenderJObjIfWithinRange();
extern void Subsystem36c_DispatchPass2_Timed();
extern void Subsystem36c_DispatchPass4_Timed();
extern void TransitionEffect_RenderPass();
extern void TransparentDraw_SortAndDispatch();
extern void clDrawMan_Buckets_Dispatch();
extern void clDrawMan_Buckets_Reset();
extern void clDrawMan_EndFrame_NoOp();
extern void clItemBoxManager_Draw();
extern void fn_8016B0C4();
extern void fn_80253448();
extern void fn_802535D4();
extern void HSD_StateInvalidate();

/* --- extern decls: sda21-referenced data --- */
extern void *lbl_806D109C;
extern void *lbl_806D10AC;
extern void *lbl_806D10D0;
extern unsigned int lbl_806DC190;
extern unsigned int lbl_806DC1B0;
extern unsigned int lbl_806DC1B8;

/* --- function index (1 fns, .text 0x8013558C..0x80135734) ---
 * [  0] 0x8013558C size:0x1A8   global RivalRun_Draw
 */

#pragma cplusplus on

#pragma exceptions on

extern "C" void RivalRun_Draw(RivalRunState *self) {
    if (self->active) {
        if (self->scene->BeginDraw() == 1) {
            clDrawMan_Buckets_Reset(SINGLETON_INSTANCE(lbl_806D10AC));
            TransparentDraw_SortAndDispatch();
            CObj_DebugVizPathFlush(self->scene);
            fn_8016B0C4();
            KartItem_RenderPipelinedWithEffects(self->car, 0);
            Object_RenderJObjIfWithinRange(self->lakitu);
            CourseEnvironment_RenderObjects_Timed(self->environment);
            Subsystem36c_DispatchPass2_Timed(self->environment);
            KartItem_RenderPipelinedWithEffects(self->rival->car, 0);
            ItemObjectManager_Render();
            clItemBoxManager_Draw(SINGLETON_INSTANCE(lbl_806D10D0));
            fn_80253448(self->hud, lbl_806DC190);
            DrawEffect_TickAndCull();
            clDrawMan_EndFrame_NoOp(SINGLETON_INSTANCE(lbl_806D10AC));
            clDrawMan_Buckets_Dispatch(SINGLETON_INSTANCE(lbl_806D10AC));
            Subsystem36c_DispatchPass4_Timed(self->environment);
            TransitionEffect_RenderPass(SINGLETON_INSTANCE(lbl_806D109C), 2);
            TransitionEffect_RenderPass(SINGLETON_INSTANCE(lbl_806D109C), 4);
            TransitionEffect_RenderPass(SINGLETON_INSTANCE(lbl_806D109C), 6);
            fn_80253448(self->hud, lbl_806DC1B0 | lbl_806DC190);
            self->scene->EndDraw();
        }
        fn_80253448(self->hud, lbl_806DC1B8);
        fn_802535D4(self->hud);
        TransitionEffect_RenderPass(SINGLETON_INSTANCE(lbl_806D109C), 1);
        HSD_StateInvalidate(0x7F);
    }
}

#pragma exceptions reset
#pragma cplusplus reset

/* === extracted from auto_RivalRun_Update_text === */
/* Copy into the TU between forward decls and function bodies; */
/* keep emit order = target section layout (do not sort). */

/* --- extern decls: branch callees (bl/b targets) --- */
/* Open prototype (`extern void Foo();`) accepts any call signature; */
/* refine if the real prototype matters for header consumers. */
extern void CObj_ApplyScissor();
extern void CObj_LoadProjMatrix();
extern void CarObject_ApplyInput(void *car, float steer, float accel, float brake, unsigned char started);
extern void CarObject_FrameUpdate(void *car, int flag);
extern void *CarObject_GetRenderObj(void *car);
extern void ChallengeGoalCamera_Update();
extern void CourseEnvironment_UpdateAndCullZones_Timed();
extern void Fog_UpdateFromCourseScene3D();
extern void *GetInputManager(void);
extern void GetRaceContextPtr();
extern void HUD_FrameUpdate();
extern void *InputMgr_GetPlayer(void *mgr, int idx);
extern unsigned char IsRaceStarted(void);
extern void ItemObjectManager_PerFrameUpdate();
extern void ItemObjectManager_Update();
extern float *KartDriver_GetKartRootMtx(void *render);
extern void KartItem_UpdateShadowBillboardAndViewport();
extern void KartMovement_ResetOnGoal();
extern void KartMovement_ResetOnTimeout();
extern void KartMovement_SetSpeedScale(void *car, float scale);
extern void LakituStart_UpdateCountdown();
extern int NokoNokoChallenge_CalcResultText(void *self, int success, int arg);
extern int *NokoNokoChallenge_GetCoinDivisor(void);
extern unsigned char NokoNokoChallenge_HandleBrakeInput(void *self, unsigned char brake);
extern void NokoNokoChallenge_SaveResult();
extern int NokoNokoChallenge_TransitionToResult(void *self);
extern void PathManager_UpdateAll();
extern void RivalRun_RivalAIUpdate();
extern void SetCoinCount();
extern void TransitionEffect_Tick();
extern void VfxSlotMgr_Update(RRVec3 a, RRVec3 b);
extern void clItemBoxManager_Update();
extern void fn_8016B32C();
extern void fn_8016C554();
extern void fn_801A1280();
extern unsigned char fn_80253C40(void *hud);
extern void fn_80253C74();
extern void fn_80253FD8(void *hud, float v);

/* --- extern decls: sda21-referenced data --- */
extern unsigned int g_lakituStartAnimDone;
extern unsigned int g_raceEnded;
extern unsigned int g_raceTimeRemaining;
extern unsigned int g_weatherSystem;
extern void *lbl_806D109C;
extern void *lbl_806D10D0;
extern unsigned int lbl_806D1290;
extern unsigned int lbl_806D7380;
extern const float lbl_806D7384;
extern unsigned int lbl_806D7388;
extern const float lbl_806D738C;
extern unsigned int lbl_806D7390;
extern unsigned int lbl_806D7394;

/* --- extern decls: large-data refs (@ha/@l pairs) --- */
/* Open array (`[]`) avoids sda21 strict-mode link errors when a future */
/* promote rewrites the asm_fn to C and references the symbol as `arr[i]`. */
extern unsigned int RivalRun_Update_bss_80677CA0[];
extern unsigned int RivalRun_Update_bss_80677CAC[];

/* --- function index (1 fns, .text 0x80135734..0x80135B7C) ---
 * [  0] 0x80135734 size:0x448   global RivalRun_Update
 */

/* --- forward decls --- */
#pragma cplusplus on
struct RRInput {
    virtual void slot08();
    virtual void slot0c();
    virtual float steering();
    virtual void slot14();
    virtual float accelerator();
    virtual float brake();
};

#pragma exceptions on
extern "C" int RivalRun_Update(RivalRunState *self)
{

    int mine;
    int rival;

    if (self->active == 0) {
        self->active = 1;
    }
    GetRaceContextPtr();
    ItemObjectManager_PerFrameUpdate();
    {
    unsigned char flag;
    RRInput *input = (RRInput *)InputMgr_GetPlayer(GetInputManager(), 0);
    if (*(unsigned char *)&g_raceEnded != 1) {
        float accelerator;
        float brake;
        if (*(unsigned char *)&lbl_806D1290 == 0) {
            accelerator = input->accelerator();
        } else {
            accelerator = *(const float *)&lbl_806D7380;
        }
        brake = input->brake();
        flag = 0;
        if (accelerator < 0.1f && brake < 0.1f && IsRaceStarted()) {
            flag = 1;
        }
        if (NokoNokoChallenge_HandleBrakeInput(self, flag) == 1) {
            accelerator = lbl_806D7384;
        }
        CarObject_ApplyInput(self->car, input->steering(), accelerator, brake, IsRaceStarted());
        CarObject_FrameUpdate(self->car, 0);
        KartItem_UpdateShadowBillboardAndViewport(self->car, self->scene, 0);
    } else {
        CarObject_ApplyInput(self->car, 0.0f, 0.0f, 0.0f, 1);
        KartMovement_SetSpeedScale(self->car, 0.5f);
        CarObject_FrameUpdate(self->car, 0);
        ChallengeGoalCamera_Update(self->goalCamera, self->scene, KartDriver_GetKartRootMtx(CarObject_GetRenderObj(self->car)));
    }
    }
    RivalRun_RivalAIUpdate(self->rival);
    Fog_UpdateFromCourseScene3D();
    PathManager_UpdateAll(self->participants);
    LakituStart_UpdateCountdown(self->lakitu);
    CourseEnvironment_UpdateAndCullZones_Timed(self->environment);
    CObj_LoadProjMatrix(self->scene, RivalRun_Update_bss_80677CA0);
    CObj_ApplyScissor(self->scene, RivalRun_Update_bss_80677CAC);
    ItemObjectManager_Update();
    VfxSlotMgr_Update(*(RRVec3 *)RivalRun_Update_bss_80677CA0, *(RRVec3 *)RivalRun_Update_bss_80677CAC);
    if (IsRaceStarted() && self->finished == 0 && *(float *)&g_raceTimeRemaining >= 0.0f) {
        mine = *(int *)((char *)CarObject_GetRenderObj(self->car) + 0x240);
        rival = *(int *)((char *)CarObject_GetRenderObj(self->rival->car) + 0x240);
        if (mine <= 0) {
            self->finished = 1;
            self->won = 1;
            KartMovement_ResetOnGoal(CarObject_GetRenderObj(self->car));
        } else if (rival <= 0) {
            self->finished = 1;
            KartMovement_ResetOnTimeout(CarObject_GetRenderObj(self->car));
        } else {
            *(float *)&g_raceTimeRemaining -= 0.016666668f;
            if (*(float *)&g_raceTimeRemaining < 0.0f) {
                *(float *)&g_raceTimeRemaining = 0.0f;
                self->finished = 1;
                KartMovement_ResetOnTimeout(CarObject_GetRenderObj(self->car));
            }
        }
    }
    fn_801A1280();
    fn_80253FD8(self->hud, *(float *)&g_raceTimeRemaining);
    HUD_FrameUpdate(self->hud);
    TransitionEffect_Tick(SINGLETON_INSTANCE(lbl_806D109C));
    if (self->finished) {
        if (self->resultFrames == 0) {
            if (self->won) {
                SetCoinCount(*NokoNokoChallenge_GetCoinDivisor());
                fn_80253C74(self->hud, 1, NokoNokoChallenge_CalcResultText(self, 1, 0), 15);
                fn_8016C554(1);
            } else {
                SetCoinCount(0);
                fn_80253C74(self->hud, 0, NokoNokoChallenge_CalcResultText(self, 0, 0), 0);
                fn_8016C554(0);
            }
            NokoNokoChallenge_SaveResult(self, self->won ? 15 : 0, self->won);
            *(unsigned char *)&g_raceEnded = 1;
            *(unsigned char *)&g_lakituStartAnimDone = 0;
        } else if (fn_80253C40(self->hud)) {
            return NokoNokoChallenge_TransitionToResult(self);
        }
        self->resultFrames++;
    }
    clItemBoxManager_Update(SINGLETON_INSTANCE(lbl_806D10D0));
    if (g_weatherSystem) {
        fn_8016B32C((void *)g_weatherSystem);
    }
    return -2;
}
#pragma exceptions reset
#pragma cplusplus reset

/* === extracted from auto_RivalRun_RivalAIUpda_text === */
/* Copy into the TU between forward decls and function bodies; */
/* keep emit order = target section layout (do not sort). */

/* --- extern decls: branch callees (bl/b targets) --- */
/* Open prototype (`extern void Foo();`) accepts any call signature; */
/* refine if the real prototype matters for header consumers. */
extern void CarObject_ApplyInput(void *car, float steer, float accel, float brake, unsigned char started);
extern void CarObject_FrameUpdate(void *car, int flag);
extern void *CarObject_GetRenderObj(void *car);
extern unsigned char CarObject_IsAirborne(void *car);
extern unsigned char IsRaceStarted(void);
extern void ItemEffectBus_OrMask(void *bus, unsigned long long mask);
extern float *KartDriver_GetKartRootMtx(void *render);
extern float KartItem_GetCurrentSpeedWithBonus(void *car);
extern void KartItem_TryArmBoostOnLanding();
extern void RivalRun_RivalTactics();
extern void RivalRun_UpdatePathFollower();
extern float Saturate_Double(float value, float lo, float hi);
extern float Vec3_Dot(const RRVec3 *a, const RRVec3 *b);
extern void Vec3_Normalize(const RRVec3 *v, RRVec3 *out);
extern void Vec3_Subtract(const RRVec3 *a, const RRVec3 *b, RRVec3 *out);
extern void *WarpDashMgr_GetInstance(int create);
extern int WarpZone_FindContaining(void *mgr, float x, float y, float z);

/* --- extern decls: sda21-referenced data --- */
extern float RivalRun_RivalAIUpdate_data_806CF610;
extern float RivalRun_RivalAIUpdate_data_806CF614;
extern float RivalRun_RivalAIUpdate_data_806CF618;
extern float RivalRun_RivalAIUpdate_data_806CF61C;
extern float RivalRun_RivalAIUpdate_data_806CF620;
extern const float lbl_806D7384;
extern const float lbl_806D738C;
extern const float lbl_806D7398;
extern const float lbl_806D739C;

/* --- function index (1 fns, .text 0x80135B7C..0x80135EFC) ---
 * [  0] 0x80135B7C size:0x380   global RivalRun_RivalAIUpdate
 */

#pragma exceptions on

void RivalRun_RivalAIUpdate(RRRivalAI *self) {
    float steer;
    float accel;
    float *mtx;
    float speed;
    float side;
    float t;
    RRVec3 toAim;
    RRVec3 fwd;
    RRVec3 right;

    accel = steer = lbl_806D738C;

    mtx = KartDriver_GetKartRootMtx(CarObject_GetRenderObj(self->car));
    speed = KartItem_GetCurrentSpeedWithBonus(self->car);
    RivalRun_RivalTactics(self);
    Vec3_Subtract(&self->aim, &self->pos, &toAim);
    toAim.y = lbl_806D738C;
    Vec3_Normalize(&toAim, &toAim);
    right.x = mtx[0];
    right.y = lbl_806D738C;
    right.z = mtx[8];
    fwd.x = mtx[2];
    fwd.y = lbl_806D738C;
    fwd.z = mtx[10];
    Vec3_Normalize(&right, &right);
    Vec3_Normalize(&fwd, &fwd);

    if (IsRaceStarted() == 1) {
        if (self->holdFrames > 0) {
            self->holdFrames--;
        }
        side = Vec3_Dot(&toAim, &right);
        if (Vec3_Dot(&toAim, &fwd) <= lbl_806D738C) {
            if (side > lbl_806D738C) {
                side = lbl_806D7384;
            } else {
                side = lbl_806D7398;
            }
        }
        steer = Saturate_Double(-side * RivalRun_RivalAIUpdate_data_806CF610, lbl_806D7398, lbl_806D7384);
        t = (speed - RivalRun_RivalAIUpdate_data_806CF618) / RivalRun_RivalAIUpdate_data_806CF61C;
        if (steer > RivalRun_RivalAIUpdate_data_806CF614) {
            accel = Saturate_Double(lbl_806D7384 - t * (steer - RivalRun_RivalAIUpdate_data_806CF614), lbl_806D738C, lbl_806D7384);
        } else if (steer < -RivalRun_RivalAIUpdate_data_806CF614) {
            accel = Saturate_Double(t * (steer + RivalRun_RivalAIUpdate_data_806CF614) + lbl_806D7384, lbl_806D738C, lbl_806D7384);
        } else {
            accel = lbl_806D7384;
        }
        accel *= self->accelScale;
        if (self->driftDir == 0) {
            if (speed > lbl_806D739C && !CarObject_IsAirborne(self->car)) {
                if (steer >= RivalRun_RivalAIUpdate_data_806CF620 || steer <= -RivalRun_RivalAIUpdate_data_806CF620) {
                    KartItem_TryArmBoostOnLanding(self->car, 1);
                    if (steer > lbl_806D738C) {
                        self->driftDir = 1;
                    } else {
                        self->driftDir = -1;
                    }
                }
            }
        } else {
            if (self->driftDir == 1 && steer <= lbl_806D738C) {
                self->driftDir = 0;
            }
            if (self->driftDir == -1 && steer >= lbl_806D738C) {
                self->driftDir = 0;
            }
        }
    }

    if (self->holdFrames != 0) {
        unsigned char started = IsRaceStarted();
        CarObject_ApplyInput(self->car, lbl_806D738C, lbl_806D738C, lbl_806D738C, started);
    } else {
        CarObject_ApplyInput(self->car, steer, accel, lbl_806D738C, IsRaceStarted());
    }
    CarObject_FrameUpdate(self->car, 0);
    ItemEffectBus_OrMask(*(void **)((char *)CarObject_GetRenderObj(self->car) + 0x304), 0x0080000000000000ULL);
    self->pos.x = mtx[3];
    self->pos.y = mtx[7];
    self->pos.z = mtx[11];
    if (WarpZone_FindContaining(WarpDashMgr_GetInstance(0), self->pos.x, self->pos.y, self->pos.z) != -1) {
        RRPathFollower *follower = self->follower;
        if (++follower->route >= 2) {
            follower->route = 0;
        }
        follower->seg = 0;
    } else {
        self->follower->endDist = speed;
        RivalRun_UpdatePathFollower(self->follower, &self->pos);
    }
}

#pragma exceptions reset


/* === extracted from auto_RivalRun_UpdatePathF_text === */
/* Copy into the TU between forward decls and function bodies; */
/* keep emit order = target section layout (do not sort). */

/* --- extern decls: branch callees (bl/b targets) --- */
/* Open prototype (`extern void Foo();`) accepts any call signature; */
/* refine if the real prototype matters for header consumers. */
extern float Vec3_Dot(const RRVec3 *a, const RRVec3 *b);
extern void Vec3_Normalize(const RRVec3 *v, RRVec3 *out);
extern float PSVECSquareMag(RRVec3 *v);

/* --- extern decls: sda21-referenced data --- */
extern const float lbl_806D738C;
extern unsigned int lbl_806D73A0;

/* --- extern decls: large-data refs (@ha/@l pairs) --- */
/* Open array (`[]`) avoids sda21 strict-mode link errors when a future */
/* promote rewrites the asm_fn to C and references the symbol as `arr[i]`. */
extern unsigned int RivalRun_rodata_8035C1E4[];

/* --- function index (1 fns, .text 0x80135EFC..0x80136148) ---
 * [  0] 0x80135EFC size:0x24C   global RivalRun_UpdatePathFollower
 */

/* --- forward decls --- */
asm void RivalRun_UpdatePathFollower(void);

/* --- extab (manual emit, .extab_user -> extab via objcopy) --- */
#pragma section R ".extab_user"
__declspec(section ".extab_user") static const unsigned char extab_RivalRun_UpdatePathFollower[8] = {
    0x39, 0x0A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

/* --- extabindex (manual emit, .extabindex_user -> extabindex via objcopy) --- */
#pragma section R ".extabindex_user"
__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_RivalRun_UpdatePathFollower = {
    (void *)&RivalRun_UpdatePathFollower, 0x0000024C, (void *)extab_RivalRun_UpdatePathFollower
};

/* --- asm function bodies (.text order = fn address order) --- */
asm void RivalRun_UpdatePathFollower(void) { /* 0x80135EFC size:0x24C */
    nofralloc
    stwu r1, -0x80(r1)
    mflr r0
    stw r0, 0x84(r1)
    stfd f31, 0x70(r1)
    psq_st f31, 0x78(r1), 0, 0
    stfd f30, 0x60(r1)
    psq_st f30, 0x68(r1), 0, 0
    stfd f29, 0x50(r1)
    psq_st f29, 0x58(r1), 0, 0
    stfd f28, 0x40(r1)
    psq_st f28, 0x48(r1), 0, 0
    stmw r25, 0x24(r1)
    mr r30, r3
    lis r3, RivalRun_rodata_8035C1E4@ha
    lwz r0, 0x4(r30)
    addi r5, r3, RivalRun_rodata_8035C1E4@l
    lwz r3, 0x8(r30)
    mr r25, r4
    slwi r4, r0, 4
    lbz r0, 0x0(r30)
    add r4, r5, r4
    slwi r5, r3, 3
    add r3, r4, r5
    cmplwi r0, 0x0
    lwzx r31, r4, r5
    lwz r26, 0x4(r3)
    beq RivalRun_UpdatePathFollower_L_80135FE4
    li r28, 0x0
    lfs f31, lbl_806D738C(r2)
    stb r28, 0x0(r30)
    mr r29, r28
    lfs f30, 0x0(r25)
    mr r27, r31
    lfs f29, 0x4(r25)
    lfs f28, 0x8(r25)
    b RivalRun_UpdatePathFollower_L_80135FD8
    RivalRun_UpdatePathFollower_L_80135F8C:
    lfs f0, 0x0(r27)
    addi r3, r1, 0x8
    fsubs f0, f0, f30
    stfs f0, 0x8(r1)
    lfs f0, 0x4(r27)
    fsubs f0, f0, f29
    stfs f0, 0xc(r1)
    lfs f0, 0x8(r27)
    fsubs f0, f0, f28
    stfs f0, 0x10(r1)
    bl PSVECSquareMag
    cmpwi r29, 0x0
    beq RivalRun_UpdatePathFollower_L_80135FC8
    fcmpo cr0, f1, f31
    bge RivalRun_UpdatePathFollower_L_80135FD0
    RivalRun_UpdatePathFollower_L_80135FC8:
    mr r28, r29
    fmr f31, f1
    RivalRun_UpdatePathFollower_L_80135FD0:
    addi r27, r27, 0xc
    addi r29, r29, 0x1
    RivalRun_UpdatePathFollower_L_80135FD8:
    cmpw r29, r26
    blt RivalRun_UpdatePathFollower_L_80135F8C
    stw r28, 0xc(r30)
    RivalRun_UpdatePathFollower_L_80135FE4:
    lfs f28, 0x0(r25)
    subi r29, r26, 0x1
    lfs f29, lbl_806D738C(r2)
    lfs f30, 0x8(r25)
    lfs f31, lbl_806D73A0(r2)
    RivalRun_UpdatePathFollower_L_80135FF8:
    lwz r0, 0xc(r30)
    mulli r0, r0, 0xc
    lfsx f0, r31, r0
    stfs f0, 0x10(r30)
    stfs f29, 0x14(r30)
    lwz r0, 0xc(r30)
    mulli r3, r0, 0xc
    addi r0, r3, 0x8
    lfsx f0, r31, r0
    stfs f0, 0x18(r30)
    lwz r0, 0xc(r30)
    cmpw r0, r29
    bne RivalRun_UpdatePathFollower_L_8013605C
    mulli r0, r0, 0xc
    add r3, r31, r0
    lfs f1, 0x0(r3)
    lfs f0, -0xc(r3)
    fsubs f0, f1, f0
    stfs f0, 0x1c(r30)
    stfs f29, 0x20(r30)
    lfs f1, 0x8(r3)
    lfs f0, -0x4(r3)
    fsubs f0, f1, f0
    stfs f0, 0x24(r30)
    b RivalRun_UpdatePathFollower_L_80136088
    RivalRun_UpdatePathFollower_L_8013605C:
    mulli r0, r0, 0xc
    add r3, r31, r0
    lfs f1, 0xc(r3)
    lfs f0, 0x0(r3)
    fsubs f0, f1, f0
    stfs f0, 0x1c(r30)
    stfs f29, 0x20(r30)
    lfs f1, 0x14(r3)
    lfs f0, 0x8(r3)
    fsubs f0, f1, f0
    stfs f0, 0x24(r30)
    RivalRun_UpdatePathFollower_L_80136088:
    addi r3, r30, 0x1c
    mr r4, r3
    bl Vec3_Normalize
    lfs f0, 0x10(r30)
    addi r3, r1, 0x14
    addi r4, r30, 0x1c
    fsubs f0, f0, f28
    stfs f29, 0x18(r1)
    stfs f0, 0x14(r1)
    lfs f0, 0x18(r30)
    fsubs f0, f0, f30
    stfs f0, 0x1c(r1)
    bl Vec3_Dot
    lwz r3, 0xc(r30)
    cmpw r3, r29
    bne RivalRun_UpdatePathFollower_L_80136100
    lfs f0, 0x28(r30)
    fcmpo cr0, f1, f0
    bge RivalRun_UpdatePathFollower_L_80136114
    lfs f0, lbl_806D73A0(r2)
    lfs f2, 0x1c(r30)
    fsubs f3, f0, f1
    lfs f0, 0x10(r30)
    fmadds f0, f2, f3, f0
    stfs f0, 0x10(r30)
    lfs f1, 0x24(r30)
    lfs f0, 0x18(r30)
    fmadds f0, f1, f3, f0
    stfs f0, 0x18(r30)
    b RivalRun_UpdatePathFollower_L_80136114
    RivalRun_UpdatePathFollower_L_80136100:
    fcmpo cr0, f1, f31
    bge RivalRun_UpdatePathFollower_L_80136114
    addi r0, r3, 0x1
    stw r0, 0xc(r30)
    b RivalRun_UpdatePathFollower_L_80135FF8
    RivalRun_UpdatePathFollower_L_80136114:
    psq_l f31, 0x78(r1), 0, 0
    lfd f31, 0x70(r1)
    psq_l f30, 0x68(r1), 0, 0
    lfd f30, 0x60(r1)
    psq_l f29, 0x58(r1), 0, 0
    lfd f29, 0x50(r1)
    psq_l f28, 0x48(r1), 0, 0
    lfd f28, 0x40(r1)
    lmw r25, 0x24(r1)
    lwz r0, 0x84(r1)
    mtlr r0
    addi r1, r1, 0x80
    blr
}

/* === extracted from auto_RivalRun_RivalTactic_text === */
/* Copy into the TU between forward decls and function bodies; */
/* keep emit order = target section layout (do not sort). */

/* --- extern decls: branch callees (bl/b targets) --- */
/* Open prototype (`extern void Foo();`) accepts any call signature; */
/* refine if the real prototype matters for header consumers. */
extern void CarObject_ApplyDriftBoost();
extern void *CarObject_GetRenderObj(void *car);
extern void GetRaceContextPtr();
extern unsigned char IsRaceStarted(void);
extern float *KartDriver_GetKartRootMtx(void *render);
extern void KartItem_CancelAndQueueDefault();
extern void KartItem_CancelIfNotForced();
extern void KartMovement_EquipItem();
extern void OSGetTick();
extern void RaceContextSlot_GetIfAlive();
extern void RenderObj_UseItem();
extern float RivalRun_CalcPathDistance();
extern void Terrain_RaycastWall();
extern float Vec3_Dot(const RRVec3 *a, const RRVec3 *b);
extern void Vec3_Normalize(const RRVec3 *v, RRVec3 *out);
extern void Vec3_Subtract(const RRVec3 *a, const RRVec3 *b, RRVec3 *out);

/* --- extern decls: sda21-referenced data --- */
extern unsigned int g_raceEnded;
extern const float lbl_806D738C;
extern unsigned int lbl_806D73A4;
extern unsigned int lbl_806D73A8;
extern unsigned int lbl_806D73AC;
extern unsigned int lbl_806D73B0;
extern unsigned int lbl_806D73B4;
extern unsigned int lbl_806D73B8;
extern unsigned int lbl_806D73BC;
extern unsigned int lbl_806D73C0;
extern unsigned int lbl_806D73C4;
extern unsigned int lbl_806D73C8;

/* --- extern decls: large-data refs (@ha/@l pairs) --- */
/* Open array (`[]`) avoids sda21 strict-mode link errors when a future */
/* promote rewrites the asm_fn to C and references the symbol as `arr[i]`. */
extern unsigned int lbl_80495994[];

/* --- function index (1 fns, .text 0x80136148..0x801367F4) ---
 * [  0] 0x80136148 size:0x6AC   global RivalRun_RivalTactics
 */

/* --- forward decls --- */
asm void RivalRun_RivalTactics(void);

/* --- extab (manual emit, .extab_user -> extab via objcopy) --- */
#pragma section R ".extab_user"
__declspec(section ".extab_user") static const unsigned char extab_RivalRun_RivalTactics[8] = {
    0x10, 0x4A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

/* --- extabindex (manual emit, .extabindex_user -> extabindex via objcopy) --- */
#pragma section R ".extabindex_user"
__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_RivalRun_RivalTactics = {
    (void *)&RivalRun_RivalTactics, 0x000006AC, (void *)extab_RivalRun_RivalTactics
};

/* --- asm function bodies (.text order = fn address order) --- */
asm void RivalRun_RivalTactics(void) { /* 0x80136148 size:0x6AC */
    nofralloc
    stwu r1, -0x90(r1)
    mflr r0
    stw r0, 0x94(r1)
    stfd f31, 0x80(r1)
    psq_st f31, 0x88(r1), 0, 0
    stw r31, 0x7c(r1)
    stw r30, 0x78(r1)
    mr r30, r3
    lwz r0, 0x0(r3)
    cmplwi r0, 0x0
    beq RivalRun_RivalTactics_L_801367D4
    bl IsRaceStarted
    clrlwi. r0, r3, 24
    beq RivalRun_RivalTactics_L_801367D4
    lwz r0, 0x3c(r30)
    cmpwi r0, 0x0
    ble RivalRun_RivalTactics_L_80136190
    b RivalRun_RivalTactics_L_801367D4
    RivalRun_RivalTactics_L_80136190:
    lbz r0, 0x38(r30)
    cmplwi r0, 0x0
    beq RivalRun_RivalTactics_L_801361C0
    lwz r5, 0x0(r30)
    li r4, 0x4
    lwz r3, 0x4(r30)
    lfs f1, 0x4(r5)
    bl CarObject_ApplyDriftBoost
    clrlwi. r0, r3, 24
    beq RivalRun_RivalTactics_L_801361C0
    li r0, 0x0
    stb r0, 0x38(r30)
    RivalRun_RivalTactics_L_801361C0:
    lwz r3, 0x20(r30)
    lfs f0, 0x10(r3)
    stfs f0, 0x28(r30)
    lfs f0, 0x14(r3)
    stfs f0, 0x2c(r30)
    lfs f0, 0x18(r3)
    stfs f0, 0x30(r30)
    lwz r3, 0x20(r30)
    lfs f0, 0x1c(r3)
    stfs f0, 0x38(r1)
    fneg f0, f0
    lfs f2, 0x20(r3)
    stfs f2, 0x3c(r1)
    lfs f1, 0x24(r3)
    stfs f1, 0x40(r1)
    stfs f1, 0x44(r1)
    stfs f2, 0x48(r1)
    stfs f0, 0x4c(r1)
    lwz r0, 0x50(r30)
    cmplwi r0, 0x0
    beq RivalRun_RivalTactics_L_801367D4
    lwz r3, 0x4(r30)
    bl CarObject_GetRenderObj
    lwz r4, 0x50(r30)
    lwz r0, 0x24c(r3)
    lwz r3, 0x24c(r4)
    cmpw r3, r0
    bne RivalRun_RivalTactics_L_801367D4
    lwz r3, 0x4(r30)
    bl CarObject_GetRenderObj
    bl KartDriver_GetKartRootMtx
    mr r31, r3
    lwz r3, 0x50(r30)
    bl KartDriver_GetKartRootMtx
    lfs f0, 0xc(r31)
    addi r4, r1, 0x5c
    addi r5, r1, 0x50
    stfs f0, 0x50(r1)
    lfs f0, 0x1c(r31)
    stfs f0, 0x54(r1)
    lfs f0, 0x2c(r31)
    stfs f0, 0x58(r1)
    lfs f0, 0xc(r3)
    stfs f0, 0x5c(r1)
    lfs f0, 0x1c(r3)
    stfs f0, 0x60(r1)
    lfs f0, 0x2c(r3)
    stfs f0, 0x64(r1)
    lwz r3, 0x20(r30)
    bl RivalRun_CalcPathDistance
    fmr f31, f1
    addi r3, r1, 0x5c
    addi r4, r1, 0x50
    addi r5, r1, 0x38
    bl Vec3_Subtract
    addi r3, r1, 0x38
    addi r4, r1, 0x2c
    bl Vec3_Normalize
    addi r3, r1, 0x38
    addi r4, r1, 0x44
    bl Vec3_Dot
    lfs f2, lbl_806D73A4(r2)
    fcmpo cr0, f31, f2
    ble RivalRun_RivalTactics_L_801362D0
    lwz r3, 0x0(r30)
    lfs f0, 0x10(r3)
    stfs f0, 0x4c(r30)
    b RivalRun_RivalTactics_L_80136360
    RivalRun_RivalTactics_L_801362D0:
    lfs f0, lbl_806D73A8(r2)
    fcmpo cr0, f31, f0
    ble RivalRun_RivalTactics_L_80136304
    fsubs f2, f31, f0
    lwz r3, 0x0(r30)
    lfs f0, lbl_806D73AC(r2)
    lfs f3, 0xc(r3)
    fdivs f2, f2, f0
    lfs f0, 0x10(r3)
    fsubs f0, f0, f3
    fmadds f0, f2, f0, f3
    stfs f0, 0x4c(r30)
    b RivalRun_RivalTactics_L_80136360
    RivalRun_RivalTactics_L_80136304:
    lfs f0, lbl_806D73B0(r2)
    fcmpo cr0, f31, f0
    ble RivalRun_RivalTactics_L_80136320
    lwz r3, 0x0(r30)
    lfs f0, 0xc(r3)
    stfs f0, 0x4c(r30)
    b RivalRun_RivalTactics_L_80136360
    RivalRun_RivalTactics_L_80136320:
    lfs f0, lbl_806D73B4(r2)
    fcmpo cr0, f31, f0
    ble RivalRun_RivalTactics_L_80136354
    fadds f2, f2, f31
    lwz r3, 0x0(r30)
    lfs f0, lbl_806D73AC(r2)
    lfs f3, 0x8(r3)
    fdivs f2, f2, f0
    lfs f0, 0xc(r3)
    fsubs f0, f0, f3
    fmadds f0, f2, f0, f3
    stfs f0, 0x4c(r30)
    b RivalRun_RivalTactics_L_80136360
    RivalRun_RivalTactics_L_80136354:
    lwz r3, 0x0(r30)
    lfs f0, 0x8(r3)
    stfs f0, 0x4c(r30)
    RivalRun_RivalTactics_L_80136360:
    lwz r4, 0x20(r30)
    lfs f0, lbl_806D73AC(r2)
    lwz r3, 0x4(r4)
    fcmpo cr0, f31, f0
    mr r5, r3
    bgt RivalRun_RivalTactics_L_80136384
    lfs f0, lbl_806D73B8(r2)
    fcmpo cr0, f31, f0
    bge RivalRun_RivalTactics_L_801363B4
    RivalRun_RivalTactics_L_80136384:
    lwz r0, 0x24(r30)
    cmpwi r0, 0x0
    bne RivalRun_RivalTactics_L_80136414
    lwz r0, 0x4(r4)
    cmpwi r0, 0x1
    beq RivalRun_RivalTactics_L_801363A8
    li r0, 0x1
    stw r0, 0x4(r4)
    stb r0, 0x0(r4)
    RivalRun_RivalTactics_L_801363A8:
    li r0, 0x78
    stw r0, 0x24(r30)
    b RivalRun_RivalTactics_L_80136414
    RivalRun_RivalTactics_L_801363B4:
    lfs f0, lbl_806D738C(r2)
    fcmpo cr0, f31, f0
    ble RivalRun_RivalTactics_L_80136414
    fcmpo cr0, f1, f0
    ble RivalRun_RivalTactics_L_801363E8
    lfs f0, lbl_806D73BC(r2)
    fcmpo cr0, f1, f0
    bge RivalRun_RivalTactics_L_801363E8
    cmpwi r3, 0x2
    bne RivalRun_RivalTactics_L_801363E4
    subi r5, r3, 0x1
    b RivalRun_RivalTactics_L_801363E8
    RivalRun_RivalTactics_L_801363E4:
    addi r5, r3, 0x1
    RivalRun_RivalTactics_L_801363E8:
    lfs f0, lbl_806D738C(r2)
    fcmpo cr0, f1, f0
    bge RivalRun_RivalTactics_L_80136414
    lfs f0, lbl_806D73C0(r2)
    fcmpo cr0, f1, f0
    ble RivalRun_RivalTactics_L_80136414
    cmpwi r5, 0x0
    bne RivalRun_RivalTactics_L_80136410
    addi r5, r5, 0x1
    b RivalRun_RivalTactics_L_80136414
    RivalRun_RivalTactics_L_80136410:
    subi r5, r5, 0x1
    RivalRun_RivalTactics_L_80136414:
    lwz r3, 0x24(r30)
    cmpwi r3, 0x0
    ble RivalRun_RivalTactics_L_8013642C
    subi r0, r3, 0x1
    stw r0, 0x24(r30)
    b RivalRun_RivalTactics_L_80136468
    RivalRun_RivalTactics_L_8013642C:
    lwz r3, 0x20(r30)
    lwz r0, 0x4(r3)
    cmpw r5, r0
    beq RivalRun_RivalTactics_L_80136468
    cmpwi r5, 0x0
    blt RivalRun_RivalTactics_L_80136460
    cmpwi r5, 0x3
    bge RivalRun_RivalTactics_L_80136460
    cmpw r0, r5
    beq RivalRun_RivalTactics_L_80136460
    stw r5, 0x4(r3)
    li r0, 0x1
    stb r0, 0x0(r3)
    RivalRun_RivalTactics_L_80136460:
    li r0, 0x78
    stw r0, 0x24(r30)
    RivalRun_RivalTactics_L_80136468:
    lbz r0, g_raceEnded(r13)
    cmplwi r0, 0x0
    bne RivalRun_RivalTactics_L_801367D4
    lwz r3, 0x40(r30)
    cmpwi r3, 0x0
    ble RivalRun_RivalTactics_L_8013648C
    subi r0, r3, 0x1
    stw r0, 0x40(r30)
    b RivalRun_RivalTactics_L_801367D4
    RivalRun_RivalTactics_L_8013648C:
    lwz r0, 0x44(r30)
    cmpwi r0, 0x0
    bne RivalRun_RivalTactics_L_80136618
    lfs f0, lbl_806D73C0(r2)
    fcmpo cr0, f31, f0
    bge RivalRun_RivalTactics_L_801364B0
    li r0, 0x32
    stw r0, 0x44(r30)
    b RivalRun_RivalTactics_L_801365C4
    RivalRun_RivalTactics_L_801364B0:
    lfs f0, lbl_806D73BC(r2)
    fcmpo cr0, f31, f0
    ble RivalRun_RivalTactics_L_801365C4
    lfs f0, lbl_806D73A8(r2)
    fcmpo cr0, f31, f0
    bge RivalRun_RivalTactics_L_80136548
    bl OSGetTick
    lis r4, 0x8000
    lwz r7, 0x0(r30)
    lwz r5, 0xf8(r4)
    lis r4, 0x1062
    addi r6, r4, 0x4dd3
    lwz r0, 0x24(r7)
    srwi r4, r5, 2
    lwz r8, 0x20(r7)
    mulhwu r5, r6, r4
    lwz r6, 0x1c(r7)
    add r0, r8, r0
    add r4, r6, r0
    srwi r0, r5, 6
    divwu r3, r3, r0
    divw r0, r3, r4
    mullw r0, r0, r4
    subf r0, r0, r3
    cmpw r0, r6
    bge RivalRun_RivalTactics_L_80136524
    li r0, 0x3e
    stw r0, 0x44(r30)
    b RivalRun_RivalTactics_L_801365C4
    RivalRun_RivalTactics_L_80136524:
    subf r0, r6, r0
    cmpw r0, r8
    bge RivalRun_RivalTactics_L_8013653C
    li r0, 0x6c
    stw r0, 0x44(r30)
    b RivalRun_RivalTactics_L_801365C4
    RivalRun_RivalTactics_L_8013653C:
    li r0, 0x3d
    stw r0, 0x44(r30)
    b RivalRun_RivalTactics_L_801365C4
    RivalRun_RivalTactics_L_80136548:
    bl OSGetTick
    lis r4, 0x8000
    lwz r7, 0x0(r30)
    lwz r5, 0xf8(r4)
    lis r4, 0x1062
    addi r6, r4, 0x4dd3
    lwz r0, 0x30(r7)
    srwi r4, r5, 2
    lwz r8, 0x2c(r7)
    mulhwu r5, r6, r4
    lwz r6, 0x28(r7)
    add r0, r8, r0
    add r4, r6, r0
    srwi r0, r5, 6
    divwu r3, r3, r0
    divw r0, r3, r4
    mullw r0, r0, r4
    subf r0, r0, r3
    cmpw r0, r6
    bge RivalRun_RivalTactics_L_801365A4
    li r0, 0x3e
    stw r0, 0x44(r30)
    b RivalRun_RivalTactics_L_801365C4
    RivalRun_RivalTactics_L_801365A4:
    subf r0, r6, r0
    cmpw r0, r8
    bge RivalRun_RivalTactics_L_801365BC
    li r0, 0x6c
    stw r0, 0x44(r30)
    b RivalRun_RivalTactics_L_801365C4
    RivalRun_RivalTactics_L_801365BC:
    li r0, 0x3d
    stw r0, 0x44(r30)
    RivalRun_RivalTactics_L_801365C4:
    lwz r0, 0x44(r30)
    cmpwi r0, 0x0
    beq RivalRun_RivalTactics_L_801367D4
    bl GetRaceContextPtr
    lwz r4, 0x1c(r30)
    bl RaceContextSlot_GetIfAlive
    li r0, 0x0
    stw r0, 0x90(r3)
    lwz r3, 0x4(r30)
    bl CarObject_GetRenderObj
    lwz r4, 0x44(r30)
    bl KartMovement_EquipItem
    clrlwi. r0, r3, 24
    beq RivalRun_RivalTactics_L_8013660C
    lwz r3, 0x0(r30)
    lwz r0, 0x18(r3)
    stw r0, 0x48(r30)
    b RivalRun_RivalTactics_L_801367D4
    RivalRun_RivalTactics_L_8013660C:
    li r0, 0x0
    stw r0, 0x44(r30)
    b RivalRun_RivalTactics_L_801367D4
    RivalRun_RivalTactics_L_80136618:
    lfs f0, lbl_806D73BC(r2)
    fcmpo cr0, f31, f0
    bge RivalRun_RivalTactics_L_801366AC
    lfs f0, lbl_806D73C0(r2)
    fcmpo cr0, f31, f0
    ble RivalRun_RivalTactics_L_801366AC
    lwz r3, 0x4(r30)
    bl CarObject_GetRenderObj
    bl KartItem_CancelIfNotForced
    lwz r3, 0x4(r30)
    bl CarObject_GetRenderObj
    bl KartItem_CancelAndQueueDefault
    li r0, 0x0
    stw r0, 0x44(r30)
    bl OSGetTick
    lis r4, 0x8000
    lis r6, 0x1062
    lwz r0, 0xf8(r4)
    lis r5, lbl_80495994@ha
    lwz r4, 0x0(r30)
    addi r6, r6, 0x4dd3
    srwi r0, r0, 2
    addi r5, r5, lbl_80495994@l
    mulhwu r0, r6, r0
    lfs f0, lbl_806D73C4(r2)
    lwz r4, 0x14(r4)
    srwi r0, r0, 6
    divwu r0, r3, r0
    clrlslwi r0, r0, 26, 2
    lfsx f1, r5, r0
    fmuls f0, f0, f1
    fctiwz f0, f0
    stfd f0, 0x68(r1)
    lwz r0, 0x6c(r1)
    add r0, r4, r0
    stw r0, 0x40(r30)
    b RivalRun_RivalTactics_L_801367D4
    RivalRun_RivalTactics_L_801366AC:
    lwz r3, 0x48(r30)
    cmpwi r3, 0x0
    ble RivalRun_RivalTactics_L_80136758
    subi r0, r3, 0x1
    addi r3, r1, 0x20
    stw r0, 0x48(r30)
    mr r4, r3
    lfs f0, lbl_806D738C(r2)
    lfs f1, 0x8(r31)
    stfs f1, 0x20(r1)
    stfs f0, 0x24(r1)
    lfs f0, 0x28(r31)
    stfs f0, 0x28(r1)
    bl Vec3_Normalize
    addi r3, r1, 0x2c
    addi r4, r1, 0x20
    bl Vec3_Dot
    lfs f0, lbl_806D73C8(r2)
    fcmpo cr0, f1, f0
    ble RivalRun_RivalTactics_L_80136708
    li r0, 0x0
    stw r0, 0x48(r30)
    b RivalRun_RivalTactics_L_801367D4
    RivalRun_RivalTactics_L_80136708:
    lwz r0, 0x44(r30)
    cmpwi r0, 0x32
    beq RivalRun_RivalTactics_L_801367D4
    lfs f0, lbl_806D73BC(r2)
    fcmpo cr0, f31, f0
    ble RivalRun_RivalTactics_L_801367D4
    addi r3, r1, 0x5c
    addi r4, r1, 0x50
    addi r5, r1, 0x14
    addi r6, r1, 0x8
    bl Terrain_RaycastWall
    clrlwi. r0, r3, 24
    bne RivalRun_RivalTactics_L_801367D4
    lfs f0, 0x5c(r1)
    stfs f0, 0x28(r30)
    lfs f0, 0x60(r1)
    stfs f0, 0x2c(r30)
    lfs f0, 0x64(r1)
    stfs f0, 0x30(r30)
    b RivalRun_RivalTactics_L_801367D4
    RivalRun_RivalTactics_L_80136758:
    lwz r3, 0x4(r30)
    bl CarObject_GetRenderObj
    li r4, 0x0
    li r5, 0x0
    bl RenderObj_UseItem
    clrlwi. r0, r3, 24
    beq RivalRun_RivalTactics_L_801367D4
    li r0, 0x0
    stw r0, 0x44(r30)
    bl OSGetTick
    lis r4, 0x8000
    lis r6, 0x1062
    lwz r0, 0xf8(r4)
    lis r5, lbl_80495994@ha
    lwz r4, 0x0(r30)
    addi r6, r6, 0x4dd3
    srwi r0, r0, 2
    addi r5, r5, lbl_80495994@l
    mulhwu r0, r6, r0
    lfs f0, lbl_806D73C4(r2)
    lwz r4, 0x14(r4)
    srwi r0, r0, 6
    divwu r0, r3, r0
    clrlslwi r0, r0, 26, 2
    lfsx f1, r5, r0
    fmuls f0, f0, f1
    fctiwz f0, f0
    stfd f0, 0x68(r1)
    lwz r0, 0x6c(r1)
    add r0, r4, r0
    stw r0, 0x40(r30)
    RivalRun_RivalTactics_L_801367D4:
    psq_l f31, 0x88(r1), 0, 0
    lwz r0, 0x94(r1)
    lfd f31, 0x80(r1)
    lwz r31, 0x7c(r1)
    lwz r30, 0x78(r1)
    mtlr r0
    addi r1, r1, 0x90
    blr
}

/* === extracted from auto_RivalRun_CalcPathDis_text === */
/* Copy into the TU between forward decls and function bodies; */
/* keep emit order = target section layout (do not sort). */

/* --- extern decls: branch callees (bl/b targets) --- */
/* Open prototype (`extern void Foo();`) accepts any call signature; */
/* refine if the real prototype matters for header consumers. */
extern float Vec3_Dot(const RRVec3 *a, const RRVec3 *b);
extern float Vec3_Magnitude(const RRVec3 *v);
extern void Vec3_Normalize(const RRVec3 *v, RRVec3 *out);
extern void Vec3_Subtract(const RRVec3 *a, const RRVec3 *b, RRVec3 *out);
extern float PSVECSquareMag(RRVec3 *v);

/* --- extern decls: sda21-referenced data --- */
extern const float lbl_806D738C;

/* --- extern decls: large-data refs (@ha/@l pairs) --- */
/* Open array (`[]`) avoids sda21 strict-mode link errors when a future */
/* promote rewrites the asm_fn to C and references the symbol as `arr[i]`. */
extern unsigned int RivalRun_rodata_8035C1E4[];

/* --- function index (1 fns, .text 0x801367F4..0x80136BA8) ---
 * [  0] 0x801367F4 size:0x3B4   global RivalRun_CalcPathDistance
 */

typedef struct RRPathRoute2 {
    RRVec3 *pts;
    int count;
} RRPathRoute2;

#pragma exceptions on

float RivalRun_CalcPathDistance(RRPathFollower *pf, RRVec3 *from, RRVec3 *to) {
    RRVec3 *pts = ((RRPathRoute2 (*)[2])RivalRun_rodata_8035C1E4)[pf->lane][pf->route].pts;
    int count = ((RRPathRoute2 (*)[2])RivalRun_rodata_8035C1E4)[pf->lane][pf->route].count;
    RRVec3 rel;
    RRVec3 dir;
    float dist;
    int a;
    int b;
    int i;
    RRVec3 *c;

    dist = lbl_806D738C;
    {
        float px, py, pz;
        float bestDist;
        int best;
        bestDist = dist;
        best = 0;
        i = best;
        px = from->x;
        py = from->y;
        pz = from->z;
        for (; i < count; i++) {
            RRVec3 d;
            float m;
            d.x = pts[i].x - px;
            d.y = pts[i].y - py;
            d.z = pts[i].z - pz;
            m = PSVECSquareMag(&d);
            if (i == 0 || m < bestDist) {
                best = i;
                bestDist = m;
            }
        }
        a = best;
    }
    {
        float pz, py, px;
        float bestDist;
        int best;
        bestDist = lbl_806D738C;
        best = 0;
        i = best;
        px = to->x;
        py = to->y;
        pz = to->z;
        for (; i < count; i++) {
            RRVec3 d;
            float m;
            d.x = pts[i].x - px;
            d.y = pts[i].y - py;
            d.z = pts[i].z - pz;
            m = PSVECSquareMag(&d);
            if (i == 0 || m < bestDist) {
                best = i;
                bestDist = m;
            }
        }
        b = best;
    }

    if (a != b) {
        if (a > b) {
            for (i = b; i < a; i++) {
                rel.x = pts[i + 1].x - pts[i].x;
                rel.y = pts[i + 1].y - pts[i].y;
                rel.z = pts[i + 1].z - pts[i].z;
                dist += Vec3_Magnitude(&rel);
            }
        } else {
            for (i = a; i < b; i++) {
                rel.x = pts[i + 1].x - pts[i].x;
                rel.y = pts[i + 1].y - pts[i].y;
                rel.z = pts[i + 1].z - pts[i].z;
                dist -= Vec3_Magnitude(&rel);
            }
        }
    }

    c = &pts[a];
    rel = *c;
    Vec3_Subtract(from, &rel, &rel);
    if (a == count - 1) {
        dir.x = c[0].x - c[-1].x;
        dir.y = lbl_806D738C;
        dir.z = c[0].z - c[-1].z;
    } else {
        dir.x = c[1].x - c[0].x;
        dir.y = lbl_806D738C;
        dir.z = c[1].z - c[0].z;
    }
    Vec3_Normalize(&dir, &dir);
    dist += Vec3_Dot(&rel, &dir);

    c = &pts[b];
    rel = *c;
    Vec3_Subtract(to, &rel, &rel);
    if (b == count - 1) {
        dir.x = c[0].x - c[-1].x;
        dir.y = lbl_806D738C;
        dir.z = c[0].z - c[-1].z;
    } else {
        dir.x = c[1].x - c[0].x;
        dir.y = lbl_806D738C;
        dir.z = c[1].z - c[0].z;
    }
    Vec3_Normalize(&dir, &dir);
    dist -= Vec3_Dot(&rel, &dir);
    return dist;
}

#pragma exceptions reset


/* === extracted from auto_RivalRun_Destroy_text === */
/* Copy into the TU between forward decls and function bodies; */
/* keep emit order = target section layout (do not sort). */

/* --- extern decls: branch callees (bl/b targets) --- */
/* Open prototype (`extern void Foo();`) accepts any call signature; */
/* refine if the real prototype matters for header consumers. */
extern void ClRomTable_PurgeAll();
extern void CourseEnvironment_Dtor();
extern void GetRaceContextPtr();
extern void ItemObjectManager_Reset();
extern void LakituStart_Dtor();
extern void MemoryManager_TimedFree();
extern void PathParticipantArray_Dtor();
extern void Path_ResetCursorForKart();
extern void RankingTable_Init();
extern void SceneDrawList_Reset();
extern void SetActiveCamera();
extern void SetPlayerCarObject();
extern void SetResourceLoadingFlag();
extern void VfxSlotMgr_Shutdown();
extern void clRom_PurgeAll();
extern void dtor_80122FD8();
extern void fn_80124C84();
extern void fn_8016C634();
extern void fn_80208FE4();
extern void fn_80254134();

/* --- extern decls: sda21-referenced data --- */
extern unsigned int g_courseData;
extern unsigned int g_objCollChecker;
extern unsigned int g_raceCamera;
extern unsigned int g_weatherSystem;
extern void *lbl_806D109C;
extern void *lbl_806D10AC;
extern void *lbl_806D10D0;

/* --- extern decls: large-data refs (@ha/@l pairs) --- */
/* Open array (`[]`) avoids sda21 strict-mode link errors when a future */
/* promote rewrites the asm_fn to C and references the symbol as `arr[i]`. */
extern unsigned int RivalRun_vtable_8048E4A0[];

/* --- function index (1 fns, .text 0x80136BA8..0x80136EA0) ---
 * [  0] 0x80136BA8 size:0x2F8   global RivalRun_Destroy
 */

/* --- native C++ island (deleting-destructor shape, see BiribiriLand.c) --- */

void *RivalRun_Destroy(RivalRunState *, short);

#pragma cplusplus on
struct RRVirtual {
    virtual ~RRVirtual();
};
struct RRCarVirtual {
    virtual void key();
    virtual ~RRCarVirtual();
};

/* ref_DEC follows the canonical HSD object.h inline. */
static inline int RRLightRefDec(RRLight *obj)
{
    unsigned char unreferenced;
    if ((unreferenced = (obj->references == (unsigned short)0xFFFF)))
        return unreferenced;
    return obj->references-- == 0;
}
static inline void RRLightDelete(RRLight *obj)
{
    if (obj) {
        obj->info->release(obj);
        obj->info->destroy(obj);
    }
}
static inline void RRLightUnref(RRLight *obj)
{
    if (obj && RRLightRefDec(obj))
        RRLightDelete(obj);
}
static inline void RRCameraRelease(RRVirtual *camera)
{
    if (camera)
        delete camera;
}

static inline void RRDestroyRival(RRRival *rival)
{
    if (rival) {
        if (rival->path && rival->pathSlot >= 0)
            Path_ResetCursorForKart(rival->path, rival->pathSlot);
        delete (RRCarVirtual *)rival->car;
        if (rival->buffer)
            MemoryManager_TimedFree(rival->buffer);
        MemoryManager_TimedFree(rival);
    }
}

#pragma exceptions on
extern "C" void *RivalRun_Destroy(RivalRunState *self, short freeMemory)
{
    if (self) {
        self->vtable = RivalRun_vtable_8048E4A0;
        if (g_weatherSystem) {
            fn_8016C634((void *)g_weatherSystem, 1);
            g_weatherSystem = 0;
        }
        SetActiveCamera(0, 0);
        g_objCollChecker = 0;
        fn_80208FE4(self->collision, 1);
        delete (RRVirtual *)self->scene;
        LakituStart_Dtor(self->lakitu, 1);
        fn_80124C84(self->goalCamera, 1);
        SetPlayerCarObject(0);
        delete (RRCarVirtual *)self->car;
        RRDestroyRival(self->rival);
        g_raceCamera = 0;
        RRCameraRelease((RRVirtual *)self->camera);
        if (self->lights)
            RRLightUnref(self->lights);
        CourseEnvironment_Dtor(self->environment, 1);
        fn_80254134(self->hud, 1);
        PathParticipantArray_Dtor(self->participants, 1);
        ItemObjectManager_Reset();
        VfxSlotMgr_Shutdown();
        ClRomTable_PurgeAll();
        GetRaceContextPtr();
        RankingTable_Init();
        delete (RRVirtual *)lbl_806D10D0;
        lbl_806D10D0 = 0;
        SceneDrawList_Reset();
        delete (RRVirtual *)lbl_806D109C;
        lbl_806D109C = 0;
        SetResourceLoadingFlag(0);
        clRom_PurgeAll();
        delete (RRVirtual *)g_courseData;
        g_courseData = 0;
        delete (RRVirtual *)lbl_806D10AC;
        lbl_806D10AC = 0;
        dtor_80122FD8(self, 0);
        if (freeMemory > 0)
            MemoryManager_TimedFree(self);
    }
    return self;
}
#pragma exceptions reset
#pragma cplusplus reset

/* === extracted from auto_RivalRun_Init_text === */
/* Copy into the TU between forward decls and function bodies; */
/* keep emit order = target section layout (do not sort). */

/* --- extern decls: branch callees (bl/b targets) --- */
/* Open prototype (`extern void Foo();`) accepts any call signature; */
/* refine if the real prototype matters for header consumers. */
extern void *CarObject_GetRenderObj(void *car);
extern float *CarObject_GetTransformMatrix(void *car);
extern void CarObject_SetPosition(void *car, void *pos);
extern int CourseData_GetDefaultPathKey_Safe(void);
extern void CourseData_GetOrCreate(int a, int b, int c);
extern void CourseObjectManager_Init();
extern void DMAChannelManager_Init();
extern void DrawManager_GetOrCreate();
extern void GetCourseDataPtr();
extern float GetCourseStartYaw(void);
extern int GetDisplayBufferIndex(void);
extern int *GetKartModelNameEntry(int chara, int arg);
extern void GetRaceContextPtr();
extern void GetStartPosition(int idx, float *x, float *y, float *z);
extern void HUD_RegisterOverlay(void *hud, int id, int arg);
extern void ItemObjectManager_Init();
extern void *MiniGame_GetCourseData(void);
extern int MiniGame_GetTimerValue(void);
extern void PreloadEffectResources(int id);
extern void PreloadItemResources(int id);
extern void ProcessSystemTick(int arg);
extern void RankingTable_Init();
extern int HSD_LObjLoadDesc(void);
extern void Scene3D_GetCameraPos(void *scene, float *a, float *b);
extern void Scene3D_SetupProjection(void *scene, float a, float b);
extern void SetActiveCamera();
extern void SetCourseScene3D(void *scene);
extern void SetPlayerCarObject();
extern void SetResourceLoadingFlag();
extern void SetReverseRoundFlag(int flag);
extern void SoundChannels_ClearAll();
extern void SoundDriver_GetOrCreate(int arg);
extern void TransitionEffect_GetOrCreate();

/* --- extern decls: sda21-referenced data --- */
extern unsigned int g_ccClass;
extern unsigned int g_characterId;
extern unsigned int g_kartStartSlot;
extern unsigned int g_lakituStartAnimDone;
extern unsigned int g_objCollChecker;
extern unsigned int g_playerRenderObj;
extern unsigned int g_raceCamera;
extern unsigned int g_raceEnded;
extern unsigned int g_raceTimeRemaining;
extern unsigned int g_totalLaps;
extern unsigned int g_weatherSystem;
extern unsigned int lbl_806D12BC;
extern unsigned int lbl_806D7388;
extern const float lbl_806D738C;
extern unsigned int lbl_806D73CC;
extern unsigned int lbl_806D73D0;
extern unsigned int lbl_806D73D8;

/* --- extern decls: large-data refs (@ha/@l pairs) --- */
/* Open array (`[]`) avoids sda21 strict-mode link errors when a future */
/* promote rewrites the asm_fn to C and references the symbol as `arr[i]`. */
extern unsigned int lbl_8035C22C[];
extern unsigned int lbl_8048E144[];
extern unsigned int RivalRun_vtable_8048E4A0[];

/* --- native C++ ctor (same shape as ReverseChallenge_Init / JumpDistanceMode_Init) --- */
#pragma cplusplus on
void *operator new(unsigned long size);
void operator delete(void *p);

typedef struct RIVec { float x, y, z; } RIVec;
struct RIInputManager { char data[0x37C]; RIInputManager(); };
struct RICamera { char data[0x2C]; RICamera(float a, float b, int w, int h, int target); };
struct RICarObject {
    char data[0x118];
    RICarObject(int disp, int chara, int cc, int a, int b, int c, int d, int e, float x, float z, float yaw);
};
static inline int RIGetCC() { return (int)g_ccClass; }
static inline int RIGetChara() { return (int)g_characterId; }
struct RIPlayerCar : RICarObject {
    RIPlayerCar(RIVec *pos, int chara, int cc)
        : RICarObject(GetDisplayBufferIndex(), chara, cc, 0, 1, -1, 0, 0, pos->x, pos->z, GetCourseStartYaw()) {}
};
struct RIRenderObj { char pad0[0x238]; int x238; };
struct RIPathManager {
    char data[0x4E8];
    RIPathManager(int key, void *car, void *render, float *x, float *y, float *z);
};
struct RICollChecker { char data[0x18]; RICollChecker(); };
struct RIRival {
    char pad0[0x50];
    void *render;
    RIRival(RIPathManager *path, int arg, void *course);
};
struct RILakituStart { char data[0x58]; RILakituStart(const void *data, int arg, float x, float y, float z); };
struct RIScene3D { char data[0x3084]; RIScene3D(int name); };
struct RIGoalCamera { char data[8]; RIGoalCamera(); };
struct RIHUD { char data[0x80]; RIHUD(RIPathManager *path); };
struct RIWeatherSystem { char data[0x1B4]; RIWeatherSystem(int arg); };

struct GameModeBase {
    virtual void _key();
    virtual ~GameModeBase();
    GameModeBase();
};

struct ModeBase : GameModeBase {
    float x4;
    ModeBase() {
        x4 = 0.0f;
    }
    virtual void _key2();
    virtual ~ModeBase();
};

struct RivalRun : ModeBase {
    virtual void _key3();
    RICarObject *car;
    RILakituStart *lakitu;
    RIInputManager *input;
    RIScene3D *scene;
    RIGoalCamera *goalCam;
    RICamera *camera;
    int renderTarget;
    RIPathManager *path;
    RIHUD *hud;
    RICollChecker *collChecker;
    RIRival *rival;
    unsigned char x34, x35, x36, x37;
    int x38;
    RivalRun();
};

#pragma exceptions on
RivalRun::RivalRun() {
    RIVec pos;
    float camA, camB;
    void *course;
    float *mtx;

    car = 0;
    lakitu = 0;
    input = 0;
    scene = 0;
    goalCam = 0;
    camera = 0;
    renderTarget = 0;
    path = 0;
    hud = 0;
    collChecker = 0;
    rival = 0;
    x34 = 0;
    x35 = 0;
    x36 = 0;
    x37 = 0;
    x38 = 0;
    course = MiniGame_GetCourseData();
    DrawManager_GetOrCreate();
    SetResourceLoadingFlag(0);
    DMAChannelManager_Init();
    TransitionEffect_GetOrCreate();
    SoundChannels_ClearAll();
    ItemObjectManager_Init();
    CourseObjectManager_Init();
    SetReverseRoundFlag(0);
    input = new RIInputManager;
    CourseData_GetOrCreate(6, 0, 0);
    GetCourseDataPtr();
    renderTarget = HSD_LObjLoadDesc();
    camera = new RICamera(1000.0f, 0.1f, 0x100, 0x100, renderTarget);
    SetActiveCamera(0, camera);
    *(RICamera **)&g_raceCamera = camera;
    ProcessSystemTick(0);
    GetRaceContextPtr();
    RankingTable_Init();
    lbl_806D12BC = 0;
    SoundDriver_GetOrCreate(0);
    g_kartStartSlot = 0;
    GetStartPosition(0, &pos.x, &pos.y, &pos.z);
    car = new RIPlayerCar(&pos, RIGetChara(), RIGetCC());
    CarObject_SetPosition(car, &pos);
    {
        RIRenderObj *r = (RIRenderObj *)CarObject_GetRenderObj(car);
        r->x238 = 1;
    }
    *(void **)&g_playerRenderObj = CarObject_GetRenderObj(car);
    SetPlayerCarObject(car);
    mtx = CarObject_GetTransformMatrix(car);
    path = new RIPathManager(CourseData_GetDefaultPathKey_Safe(), car, CarObject_GetRenderObj(car), &mtx[12], &mtx[13], &mtx[14]);
    collChecker = new RICollChecker;
    *(RICollChecker **)&g_objCollChecker = collChecker;
    rival = new RIRival(path, 1, course);
    rival->render = CarObject_GetRenderObj(car);
    lakitu = new RILakituStart(lbl_8035C22C, 0, 0.0f, 0.0f, 0.0f);
    scene = new RIScene3D(*GetKartModelNameEntry((int)g_characterId, -1));
    goalCam = new RIGoalCamera;
    ProcessSystemTick(0);
    Scene3D_GetCameraPos(scene, &camA, &camB);
    camA += 10.0f;
    Scene3D_SetupProjection(scene, camA, camB);
    hud = new RIHUD(path);
    HUD_RegisterOverlay(hud, 6, 0);
    HUD_RegisterOverlay(hud, 0xA, 0);
    HUD_RegisterOverlay(hud, 0xC, 0);
    HUD_RegisterOverlay(hud, 0x11, 0);
    HUD_RegisterOverlay(hud, 0x12, 0);
    HUD_RegisterOverlay(hud, 0xE, 0);
    *(unsigned char *)&g_lakituStartAnimDone = 0;
    SetCourseScene3D(scene);
    *(unsigned char *)&g_raceEnded = 0;
    *(float *)&g_raceTimeRemaining = MiniGame_GetTimerValue();
    g_totalLaps = 1;
    PreloadEffectResources(9);
    PreloadEffectResources(0xA);
    PreloadItemResources(0x32);
    PreloadItemResources(0x3D);
    PreloadItemResources(0x3E);
    PreloadItemResources(0x6C);
    if (*(void **)&g_weatherSystem == 0) {
        *(void **)&g_weatherSystem = new RIWeatherSystem(1);
    }
    SetResourceLoadingFlag(1);
}
#pragma exceptions reset
#pragma cplusplus reset

/* === extracted from auto_RivalRun_RivalInit_text === */
/* Copy into the TU between forward decls and function bodies; */
/* keep emit order = target section layout (do not sort). */

/* --- extern decls: branch callees (bl/b targets) --- */
/* Open prototype (`extern void Foo();`) accepts any call signature; */
/* refine if the real prototype matters for header consumers. */
extern void Alloc();
extern void *CarObject_GetRenderObj(void *car);
extern void CarObject_Init();
extern void CarObject_SetPosition();
extern float GetCourseStartYaw(void);
extern void GetRaceContextPtr();
extern void GetStartPosition();
extern void ItemEffectBus_OrMask(void *bus, unsigned long long mask);
extern void PathManager_RegisterCarObject();
extern void RaceContextSlot_GetIfAlive();
extern void RivalRun_PathFollowerInit();

/* --- extern decls: sda21-referenced data --- */
extern unsigned int g_ccClass;
extern const float lbl_806D738C;

/* --- function index (1 fns, .text 0x8013732C..0x80137588) ---
 * [  0] 0x8013732C size:0x25C   global RivalRun_RivalInit
 */

/* --- forward decls --- */
asm void RivalRun_RivalInit(void);

/* --- extern decls: extab symbolic refs (dtors / typeids) --- */
extern void MemoryManager_TimedFree();

/* --- extab (manual emit, .extab_user -> extab via objcopy) --- */
#pragma section R ".extab_user"
__declspec(section ".extab_user") static const struct { unsigned int f0; unsigned int f1; unsigned int f2; unsigned int f3; unsigned int f4; unsigned int f5; unsigned int f6; unsigned int f7; unsigned int f8; void *f9; unsigned int f10; void *f11; unsigned int f12; void *f13; } extab_RivalRun_RivalInit = { 0x200A0000, 0x0000006C, 0x000E0020, 0x000000C4, 0x000E0028, 0x00000178, 0x00000030, 0x00000000, 0x8A80001C, (void *)&MemoryManager_TimedFree, 0x8A80001C, (void *)&MemoryManager_TimedFree, 0x8A80001C, (void *)&MemoryManager_TimedFree };

/* --- extabindex (manual emit, .extabindex_user -> extabindex via objcopy) --- */
#pragma section R ".extabindex_user"
__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_RivalRun_RivalInit = {
    (void *)&RivalRun_RivalInit, 0x0000025C, (void *)&extab_RivalRun_RivalInit
};

/* --- asm function bodies (.text order = fn address order) --- */
asm void RivalRun_RivalInit(void) { /* 0x8013732C size:0x25C */
    nofralloc
    stwu r1, -0x20(r1)
    mflr r0
    stw r0, 0x24(r1)
    li r0, 0x0
    stw r31, 0x1c(r1)
    mr r31, r6
    stw r30, 0x18(r1)
    mr r30, r3
    addi r6, r30, 0x10
    stw r29, 0x14(r1)
    stw r28, 0x10(r1)
    stw r31, 0x0(r3)
    mr r3, r5
    addi r5, r30, 0xc
    stw r0, 0x4(r30)
    stw r4, 0x14(r30)
    addi r4, r30, 0x8
    bl GetStartPosition
    lwz r0, g_ccClass(r13)
    cmpwi r0, 0x2
    bne RivalRun_RivalInit_L_801373D8
    li r3, 0x118
    bl Alloc
    mr. r28, r3
    beq RivalRun_RivalInit_L_801373D0
    lwz r29, g_ccClass(r13)
    bl GetCourseStartYaw
    li r0, 0x0
    fmr f3, f1
    stw r0, 0x8(r1)
    mr r3, r28
    mr r6, r29
    li r4, 0x6
    lfs f1, 0x8(r30)
    lfs f2, 0x10(r30)
    li r5, 0x0
    li r7, 0x0
    li r8, 0x0
    li r9, 0x5
    li r10, 0x0
    bl CarObject_Init
    RivalRun_RivalInit_L_801373D0:
    stw r28, 0x4(r30)
    b RivalRun_RivalInit_L_8013742C
    RivalRun_RivalInit_L_801373D8:
    li r3, 0x118
    bl Alloc
    mr. r28, r3
    beq RivalRun_RivalInit_L_80137428
    lwz r29, g_ccClass(r13)
    bl GetCourseStartYaw
    li r0, 0x0
    fmr f3, f1
    stw r0, 0x8(r1)
    mr r3, r28
    mr r6, r29
    li r4, 0x6
    lfs f1, 0x8(r30)
    lfs f2, 0x10(r30)
    li r5, 0x0
    li r7, 0x0
    li r8, 0x0
    li r9, -0x1
    li r10, 0x0
    bl CarObject_Init
    RivalRun_RivalInit_L_80137428:
    stw r28, 0x4(r30)
    RivalRun_RivalInit_L_8013742C:
    lwz r3, 0x4(r30)
    addi r4, r30, 0x8
    bl CarObject_SetPosition
    lwz r3, 0x4(r30)
    bl CarObject_GetRenderObj
    lwz r3, 0x304(r3)
    li r6, 0x0
    lis r5, 0x80
    bl ItemEffectBus_OrMask
    li r0, -0x1
    stw r0, 0x18(r30)
    lwz r3, 0x4(r30)
    bl CarObject_GetRenderObj
    mr r8, r3
    lwz r3, 0x14(r30)
    lwz r7, 0x4(r30)
    addi r4, r30, 0x8
    addi r5, r30, 0xc
    addi r6, r30, 0x10
    li r9, -0x1
    bl PathManager_RegisterCarObject
    stw r3, 0x18(r30)
    li r0, 0x0
    li r3, 0x2c
    stw r0, 0x1c(r30)
    bl Alloc
    mr. r28, r3
    beq RivalRun_RivalInit_L_801374A4
    addi r4, r30, 0x8
    bl RivalRun_PathFollowerInit
    RivalRun_RivalInit_L_801374A4:
    stw r28, 0x20(r30)
    li r3, 0x0
    lfs f0, lbl_806D738C(r2)
    li r0, 0xb4
    stw r3, 0x24(r30)
    li r28, 0x0
    stfs f0, 0x28(r30)
    stfs f0, 0x2c(r30)
    stfs f0, 0x30(r30)
    stw r3, 0x34(r30)
    stb r3, 0x38(r30)
    stw r3, 0x3c(r30)
    stw r0, 0x40(r30)
    stw r3, 0x44(r30)
    stfs f0, 0x4c(r30)
    stw r3, 0x50(r30)
    RivalRun_RivalInit_L_801374E4:
    bl GetRaceContextPtr
    mr r4, r28
    bl RaceContextSlot_GetIfAlive
    mr. r29, r3
    beq RivalRun_RivalInit_L_80137514
    lwz r3, 0x4(r30)
    bl CarObject_GetRenderObj
    lwz r0, 0xb4(r29)
    cmplw r0, r3
    bne RivalRun_RivalInit_L_80137514
    stw r28, 0x1c(r30)
    b RivalRun_RivalInit_L_80137520
    RivalRun_RivalInit_L_80137514:
    addi r28, r28, 0x1
    cmpwi r28, 0x80
    blt RivalRun_RivalInit_L_801374E4
    RivalRun_RivalInit_L_80137520:
    lwz r3, 0x0(r30)
    cmplwi r3, 0x0
    beq RivalRun_RivalInit_L_80137564
    lwz r0, 0x0(r3)
    lfs f1, 0x4(r31)
    stw r0, 0x3c(r30)
    lfs f0, lbl_806D738C(r2)
    lwz r3, 0x0(r30)
    fcmpo cr0, f1, f0
    lwz r0, 0x14(r3)
    stw r0, 0x40(r30)
    ble RivalRun_RivalInit_L_8013755C
    li r0, 0x1
    stb r0, 0x38(r30)
    b RivalRun_RivalInit_L_80137564
    RivalRun_RivalInit_L_8013755C:
    li r0, 0x0
    stb r0, 0x38(r30)
    RivalRun_RivalInit_L_80137564:
    lwz r0, 0x24(r1)
    mr r3, r30
    lwz r31, 0x1c(r1)
    lwz r30, 0x18(r1)
    lwz r29, 0x14(r1)
    lwz r28, 0x10(r1)
    mtlr r0
    addi r1, r1, 0x20
    blr
}
