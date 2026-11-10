#include "game/types/c_region.h"
C_REGION_BEGIN
/* ReverseChallenge_Update (0x800AD134..0x800AD910): per-frame update of the
 * reverse-run challenge (drive the course backwards inside the start quad,
 * reach the goal plane before the timer runs out). Same frame as
 * MiniGame_CoinChallenge_Update. */

typedef struct RCVec3 { float x, y, z; } RCVec3;
#include "game/types/RCQuadPtsC.h"

C_REGION_END
#pragma cplusplus on
struct RCInput {
    virtual void slot08();
    virtual void slot0c();
    virtual float steering();
    virtual void slot14();
    virtual float accelerator();
    virtual float brake();
};
extern "C" {

typedef struct RCCarData { char pad0[0x1c8]; float yaw; } RCCarData;
typedef struct RCCar { char pad0[0x28]; RCCarData *data; } RCCar;
typedef struct RCGoal { RCVec3 pos; char padC[0x18]; RCVec3 normal; } RCGoal;
typedef struct RCBanana { char pad0[0xc]; unsigned char hit; } RCBanana;
typedef struct RCHitInfo {
    char pad0[8];
    int kind;
    char padC[0x94];
    RCVec3 pos;
    char padAC[0x1ec - 0xac];
} RCHitInfo;
typedef struct RCCoinTier { int limit; int coins; } RCCoinTier;

typedef struct ReverseChallengeUpdateView {
    void *vtable;
    char pad4[4];
    void *environment;
    char padC[8];
    RCCar *car;
    void *lakitu;
    void *camera;
    void *goalCamera;
    void *hud;
    RCGoal *goal;
    float *quadNormals;
    RCBanana *banana;
    RCVec3 lastPos;
    unsigned char active;
    unsigned char finished;
    unsigned char won;
    char pad43;
    int resultFrames;
} ReverseChallengeUpdateView;

extern void *CarObject_GetRenderObj(void *car);
extern void BananaField_CheckCollision(RCBanana *field, void *mtx, RCVec3 *delta);
extern void CObj_ApplyScissor(void *cam, void *out);
extern void CObj_ApplyViewport(void *cam, void *in);
extern void CObj_LoadIntoGX(void *cam, void *in);
extern void CObj_LoadProjMatrix(void *cam, void *out);
#ifdef __MWERKS__
extern void CarObject_ApplyInput(RCCar *car, float steer, float accel, float brake, unsigned char started);
#else
/* The definition orders its int and float parameters differently; see docs/notes/port_abi.md. */
extern void CarObject_ApplyInput(RCCar *, unsigned char, float, float, float);
static inline void CarObject_ApplyInput_Reordered(RCCar * a0, float a1, float a2, float a3, unsigned char a4) { CarObject_ApplyInput(a0, a4, a1, a2, a3); }
#define CarObject_ApplyInput CarObject_ApplyInput_Reordered
#endif
extern float CarObject_CalcSpeedRatio(RCCar *car);
extern void CarObject_FrameUpdate(RCCar *car, int arg);
extern void CarObject_HandleObstacleHit(RCCar *car, RCHitInfo *info);
extern void ChallengeGoalCamera_Update(void *goalCam, void *cam, void *mtx);
extern void CourseEnvironment_UpdateAndCullZones_Timed(void *env);
extern void Fog_UpdateFromCourseScene3D(void);
extern void *GetInputManager(void);
extern void HUD_FrameUpdate(void *hud);
extern RCInput *InputMgr_GetPlayer(void *mgr, int index);
extern unsigned char IsRaceStarted(void);
extern void ItemObjectManager_PerFrameUpdate(void *ctx);
extern void ItemObjectManager_Update(void);
extern float (*KartDriver_GetKartRootMtx(void *obj))[4];
extern float KartItem_GetCurrentSpeedWithBonus(RCCar *car);
extern void KartItem_UpdateShadowBillboardAndViewport(RCCar *car, void *cam, int arg);
extern void KartMovement_ResetOnGoal(void *obj);
extern void KartMovement_ResetOnTimeout(void *obj);
extern void KartMovement_SetSpeedScale(RCCar *car, float scale);
extern void LakituStart_UpdateCountdown(void *lakitu);
extern int MiniGame_GetTimerValue(void);
extern void Mtx44_GetTranslation_RowMajor(RCVec3 *out, void *mtx);
extern int NokoNokoChallenge_CalcResultText(void *self, int won, int arg);
extern RCCoinTier **NokoNokoChallenge_GetCoinDivisor(void);
extern unsigned char NokoNokoChallenge_HandleBrakeInput(void *self, int holding);
extern void NokoNokoChallenge_SaveResult(void *self, int coins, unsigned char won);
extern int NokoNokoChallenge_TransitionToResult(void *self);
extern int Object_SetByte10_Return1(void *obj, int value);
extern void SetCoinCount(int coins);
extern void TransitionEffect_Tick(void *fx);
extern void Vec2_RotateY(RCVec3 *out, RCVec3 *in, float angle);
extern void Vec3_Add_DestFirst(RCVec3 *out, RCVec3 *a, RCVec3 *b);
extern float Vec3_Dot(RCVec3 *a, RCVec3 *b);
extern void Vec3_Subtract(void *a, void *b, void *out);
extern void Vec3_Subtract_DestFirst(RCVec3 *out, RCVec3 *a, RCVec3 *b);
#ifdef __MWERKS__
extern void VfxSlotMgr_Update(RCVec3 proj, RCVec3 scissor);
#else
/* The definition takes these structs by address; see docs/notes/port_abi.md. */
extern void VfxSlotMgr_Update(RCVec3 *, RCVec3 *);
static inline void VfxSlotMgr_Update_ByValue(RCVec3 proj, RCVec3 scissor) { VfxSlotMgr_Update(&proj, &scissor); }
#define VfxSlotMgr_Update VfxSlotMgr_Update_ByValue
#endif
extern void fn_8016B32C(void *weather);
extern unsigned char fn_80253C40(void *hud);
extern void fn_80253C74(void *hud, int won, int text, int time);
extern void fn_80253EBC(void *hud, float v);
extern void fn_80253EC0(void *hud, float v);
extern void fn_80253FD8(void *hud, float v);
extern void *memset(void *p, int c, unsigned long n);

extern unsigned int g_lakituStartAnimDone;
extern unsigned int g_raceEnded;
extern unsigned int g_raceTimeRemaining;
extern unsigned int g_weatherSystem;
extern unsigned int lbl_806D109C;
extern unsigned char lbl_806D1290;
extern unsigned int lbl_806D4F48;
extern unsigned int lbl_806D4F4C;
extern unsigned int lbl_806D4F50;
extern unsigned int lbl_806D4F54;
extern unsigned int lbl_806D4F58;
extern unsigned int lbl_806D4F5C;
extern unsigned int lbl_806D4F60;
extern unsigned int lbl_806D4F64;
extern unsigned int lbl_806D4F68;

extern const RCQuadPtsC ReverseChallenge_rodata_80328DD8;
extern RCVec3 ReverseChallenge_Update_bss_805DF338;
extern RCVec3 ReverseChallenge_Update_bss_805DF344;

#define RCF(x) (*(const float *)&(x))
#define RC_ENDED (*(unsigned char *)&g_raceEnded)
#define RC_TIME (*(float *)&g_raceTimeRemaining)

static inline unsigned char RC_InsideStartQuad(RCVec3 *p, float *n)
{
    float dx = p->x - ReverseChallenge_rodata_80328DD8.p[1][0];
    float dz = -(p->z - ReverseChallenge_rodata_80328DD8.p[1][1]);
    float zero = RCF(lbl_806D4F54);
    if (dz * n[0] + dx * n[1] > zero) {
        return 0;
    }
    if (dz * n[2] + dx * n[3] > zero) {
        return 0;
    }
    dx = p->x - ReverseChallenge_rodata_80328DD8.p[3][0];
    dz = -(p->z - ReverseChallenge_rodata_80328DD8.p[3][1]);
    if (dz * n[4] + dx * n[5] > zero) {
        return 0;
    }
    if (dz * n[6] + dx * n[7] > zero) {
        return 0;
    }
    return 1;
}

static inline int RC_PastGoal(RCVec3 *p, RCGoal *goal)
{
    RCVec3 v;
    Vec3_Subtract(p, goal, &v);
    return Vec3_Dot(&v, &goal->normal) > RCF(lbl_806D4F54);
}

/* --- function index (1 fns, .text 0x800AD134..0x800AD910) ---
 * [  0] 0x800AD134 size:0x7DC   global ReverseChallenge_Update
 */
int ReverseChallenge_Update(ReverseChallengeUpdateView *self);
}

/* --- extab (manual emit, .extab_user -> extab via objcopy) --- */
#pragma section R ".extab_user"
__declspec(section ".extab_user") static const unsigned char extab_ReverseChallenge_Update[8] = {
    0x18, 0xCA, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

/* --- extabindex (manual emit, .extabindex_user -> extabindex via objcopy) --- */
#pragma section R ".extabindex_user"
__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_ReverseChallenge_Update = {
    (void *)&ReverseChallenge_Update, 0x000007DC, (void *)extab_ReverseChallenge_Update
};

extern "C" int ReverseChallenge_Update(ReverseChallengeUpdateView *self)
{
    RCHitInfo info;
    RCVec3 pos;
    RCVec3 eye;
    RCVec3 at;
    RCVec3 dir;
    RCVec3 kartPos;
    RCVec3 off;
    RCVec3 delta;
    RCVec3 cur;
    RCVec3 p;
    RCInput *input;
    float accel;
    float brake;
    float steer;
    float a;
    int holding;

    if (self->active == 0) {
        self->active = 1;
    }
    ItemObjectManager_PerFrameUpdate(GetRaceContextPtr());
    input = InputMgr_GetPlayer(GetInputManager(), 0);
    if (RC_ENDED != 1) {
        if (lbl_806D1290 == 0) {
            a = input->accelerator();
        } else {
            a = RCF(lbl_806D4F48);
        }
        accel = a;
        brake = input->brake();
        steer = input->steering();
        holding = 0;
        if (a < RCF(lbl_806D4F50) && brake < RCF(lbl_806D4F50) && IsRaceStarted()) {
            holding = 1;
        }
        if (NokoNokoChallenge_HandleBrakeInput(self, holding) == 1) {
            accel = RCF(lbl_806D4F4C);
        }
        Mtx44_GetTranslation_RowMajor(&pos, KartDriver_GetKartRootMtx(CarObject_GetRenderObj(self->car)));
        if (RC_InsideStartQuad(&pos, self->quadNormals) == 1) {
            int yaw = self->car->data->yaw;
            if (yaw < 0) {
                yaw = -yaw % 360 - 360;
            } else {
                yaw = yaw % 360;
            }
            if (yaw >= 0 && yaw < 170) {
                steer = RCF(lbl_806D4F4C);
            }
            if (yaw > 190 && yaw < 360) {
                steer = RCF(lbl_806D4F58);
            }
            accel = RCF(lbl_806D4F4C);
        }
        CarObject_ApplyInput(self->car, steer, accel, brake, IsRaceStarted());
        CarObject_FrameUpdate(self->car, 0);
        KartItem_UpdateShadowBillboardAndViewport(self->car, self->camera, 0);
        CObj_LoadProjMatrix(self->camera, &eye);
        CObj_ApplyScissor(self->camera, &at);
        Vec3_Subtract_DestFirst(&dir, &at, &eye);
        Mtx44_GetTranslation_RowMajor(&kartPos, KartDriver_GetKartRootMtx(CarObject_GetRenderObj(self->car)));
        Vec3_Subtract_DestFirst(&off, &eye, &kartPos);
        Vec2_RotateY(&off, &off, RCF(lbl_806D4F5C));
        Vec3_Add_DestFirst(&eye, &kartPos, &off);
        Vec2_RotateY(&dir, &dir, RCF(lbl_806D4F5C));
        Vec3_Add_DestFirst(&at, &eye, &dir);
        CObj_LoadIntoGX(self->camera, &eye);
        CObj_ApplyViewport(self->camera, &at);
    } else {
        CarObject_ApplyInput(self->car, RCF(lbl_806D4F54), RCF(lbl_806D4F54), RCF(lbl_806D4F54), 1);
        KartMovement_SetSpeedScale(self->car, RCF(lbl_806D4F60));
        CarObject_FrameUpdate(self->car, 0);
        ChallengeGoalCamera_Update(self->goalCamera, self->camera,
                                   KartDriver_GetKartRootMtx(CarObject_GetRenderObj(self->car)));
    }
    Fog_UpdateFromCourseScene3D();
    LakituStart_UpdateCountdown(self->lakitu);
    CourseEnvironment_UpdateAndCullZones_Timed(self->environment);
    {
        float (*m)[4] = KartDriver_GetKartRootMtx(CarObject_GetRenderObj(self->car));
        cur.x = m[0][3];
        cur.y = m[1][3];
        cur.z = m[2][3];
        Vec3_Subtract(&cur, &self->lastPos, &delta);
        self->lastPos.x = cur.x;
        self->lastPos.y = cur.y;
        self->lastPos.z = cur.z;
        BananaField_CheckCollision(self->banana, m, &delta);
        if (self->banana->hit) {
            memset(&info, 0, sizeof(info));
            info.pos.x = cur.x;
            info.pos.y = cur.y;
            info.pos.z = cur.z;
            info.kind = 0x32;
            CarObject_HandleObstacleHit(self->car, &info);
        }
    }
    if (self->finished == 0) {
        RCGoal *goal;
        Mtx44_GetTranslation_RowMajor(&p, KartDriver_GetKartRootMtx(CarObject_GetRenderObj(self->car)));
        goal = self->goal;
        if (RC_PastGoal(&p, goal)) {
            self->won = 1;
            self->finished = 1;
            KartMovement_ResetOnGoal(CarObject_GetRenderObj(self->car));
        }
    }
    CObj_LoadProjMatrix(self->camera, &ReverseChallenge_Update_bss_805DF338);
    CObj_ApplyScissor(self->camera, &ReverseChallenge_Update_bss_805DF344);
    ItemObjectManager_Update();
    VfxSlotMgr_Update(ReverseChallenge_Update_bss_805DF338, ReverseChallenge_Update_bss_805DF344);
    if (IsRaceStarted() && self->finished == 0) {
        float t;
        float zero;
        zero = RCF(lbl_806D4F54);
        t = RC_TIME;
        if (zero <= t) {
            RC_TIME = t - RCF(lbl_806D4F64);
            if (RC_TIME < zero) {
                RC_TIME = zero;
                self->finished = 1;
                KartMovement_ResetOnTimeout(CarObject_GetRenderObj(self->car));
            }
        }
    }
    fn_80253FD8(self->hud, RC_TIME);
    fn_80253EBC(self->hud, RCF(lbl_806D4F68) * CarObject_CalcSpeedRatio(self->car));
    fn_80253EC0(self->hud, KartItem_GetCurrentSpeedWithBonus(self->car));
    HUD_FrameUpdate(self->hud);
    TransitionEffect_Tick(*(void **)&lbl_806D109C == 0 ? 0 : *(void **)&lbl_806D109C);
    if (self->finished) {
        if (self->resultFrames == 0) {
            int t;
            int coins;
            t = (float)MiniGame_GetTimerValue() - RC_TIME;
            coins = 0;
            RCCoinTier **tbl = NokoNokoChallenge_GetCoinDivisor();
            if (tbl != 0 && self->won == 1) {
                int i;
                for (i = 0; (*tbl)[i].coins > 0; i++) {
                    if (t <= (*tbl)[i].limit) {
                        coins = (*tbl)[i].coins;
                        break;
                    }
                }
            }
            SetCoinCount(coins);
            if (self->won) {
                fn_80253C74(self->hud, 1, NokoNokoChallenge_CalcResultText(self, 1, 0), (int)RC_TIME);
                Object_SetByte10_Return1(self->camera, 1);
            } else {
                fn_80253C74(self->hud, 0, NokoNokoChallenge_CalcResultText(self, 0, 0), (int)RC_TIME);
                Object_SetByte10_Return1(self->camera, 1);
            }
            NokoNokoChallenge_SaveResult(self, coins, self->won);
            RC_ENDED = 1;
            *(unsigned char *)&g_lakituStartAnimDone = 0;
        } else if (fn_80253C40(self->hud)) {
            return NokoNokoChallenge_TransitionToResult(self);
        }
        self->resultFrames++;
    }
    if (*(void **)&g_weatherSystem != 0) {
        fn_8016B32C(*(void **)&g_weatherSystem);
    }
    return -2;
}
#pragma cplusplus reset
