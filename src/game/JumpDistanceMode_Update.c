/* Bounded native retrofit draft (c11_a17_20261106): 98.28571% text.
 * Three structural approaches: direct body; explicit camera/vector locals;
 * inline camera and timer helpers. Automatic owned extab matches 100%.
 * Residuals include camera stack slots/FP scheduling, constant relocations,
 * and the target's redundant null-to-null transition getter at 0x8021234C.
 * Do not add a no-op null check to force that sequence. The original accepted
 * assembly below remains byte-identical and source-linked; no native gain.
 */
#if 0
#pragma cplusplus on
#include "game/JumpDistanceMode.h"
#include "game/MathInline.h"

struct ScenePos {
    int state;
    void *camera;
    Vec3f position, velocity;
    float angle;
};
struct TimerDisplay {
    int value, unused;
    unsigned char active;
    float phase;
    void *sprites[7];
};
extern "C" {
void *GetRaceContextPtr(void);
void ItemObjectManager_PerFrameUpdate(void *);
void fn_802128F4(JumpGauge *, CarObject *);
void fn_8023E324(void *, int);
void JumpDistanceMode_HandlePhysics(JumpDistanceMode *);
void Fog_UpdateFromCourseScene3D(void);
void CObj_ApplyScissor(void *, Vec3f *);
void CObj_LoadProjMatrix(void *, Vec3f *);
void CObj_LoadIntoGX(void *, Vec3f *);
void Vec3_Subtract(const Vec3f *, const Vec3f *, Vec3f *);
float LUT_Cosine(float);
float LUT_Sine(float);
unsigned char Terrain_RaycastWall(Vec3f *, Vec3f *, Vec3f *, Vec3f *);
void LakituStart_UpdateCountdown(void *);
void CourseEnvironment_UpdateAndCullZones_Timed(void *);
void JumpDistanceMode_UpdateGameplay(JumpDistanceMode *);
void ItemObjectManager_Update(void);
void VfxSlotMgr_Update(Vec3f, Vec3f);
unsigned char IsRaceStarted(void);
void fn_802124FC(void *);
void fn_80253FD8(void *, float);
float CarObject_CalcSpeedRatio(void *);
float KartItem_GetCurrentSpeedWithBonus(void *);
void fn_80253EBC(void *, float);
void fn_80253EC0(void *, float);
void HUD_FrameUpdate(void *);
void fn_8011F804(void *, float, float);
void SpriteLayer_SetResource(void *, int);
void SpriteHandle_RecomputeCull(void *);
void RumbleUpdate(void);
void TransitionEffect_Tick(void *);
void SetCoinCount(int);
int fn_801231AC(void);
int NokoNokoChallenge_CalcResultText(void *, int, int);
void fn_80253C74(void *, int, int, int);
void *CarObject_GetRenderObj(void *);
void KartMovement_ResetOnGoal(void *);
void KartMovement_ResetOnTimeout(void *);
void NokoNokoChallenge_SaveResult(void *, int, int);
void Object_SetByte10_Return1(void *, int);
unsigned char fn_80253C40(void *);
int NokoNokoChallenge_TransitionToResult(void *);
void fn_8016B32C(void *);
extern unsigned char g_raceEnded, g_lakituStartAnimDone;
extern float g_raceTimeRemaining;
extern void *lbl_806D109C, *g_weatherSystem;
extern float lbl_803C3CF0[][2];
}

#pragma use_lmw_stmw on
static inline void UpdateCamera(ScenePos *scene)
{
    Vec3f normal, hit, previous;
    Vec3f diff, next, cameraTarget, cameraEye;
    switch (scene->state) {
    case 0: break;
    case 1: {
        CObj_ApplyScissor(scene->camera, &cameraEye);
        CObj_LoadProjMatrix(scene->camera, &cameraTarget);
        Vec3_Subtract(&cameraEye, &cameraTarget, &diff);
        float horizontalX = diff.x * diff.x;
        float horizontalZ = diff.z * diff.z;
        float radius = 1.4f * MathInline_sqrtf(horizontalX + horizontalZ);
        next.x = radius * LUT_Cosine(1.570796012878418f) + cameraEye.x;
        float z = radius * LUT_Sine(1.570796012878418f) + cameraEye.z;
        next.y = cameraEye.y;
        next.z = z;
        CObj_LoadIntoGX(scene->camera, &next);
        break;
    }
    case 2:
        scene->state = 3;
        break;
    case 3:
        CObj_LoadIntoGX(scene->camera, &scene->position);
        break;
    case 4:
        if (scene->angle < 90.0f) {
            previous.x = scene->position.x;
            previous.y = scene->position.y;
            previous.z = scene->position.z;
            float scale = LUT_Sine(0.01745329238474369f * scene->angle);
            scene->position.x += scene->velocity.x * scale;
            scene->position.y += scene->velocity.y * scale;
            scene->position.z += scene->velocity.z * scale;
            scene->angle += 3.0f;
            if (Terrain_RaycastWall(&previous, &scene->position, &hit, &normal) == 1) {
                scene->position = previous;
                scene->angle = 90.0f;
            }
        }
        CObj_LoadIntoGX(scene->camera, &scene->position);
        break;
    }
}
static inline void UpdateTimer(TimerDisplay *timer)
{
    if (timer->active == 1) {
        if (timer->phase >= 1.0f) return;
        timer->phase += 0.1f;
        for (int i = 0; i < 7; ++i) {
            fn_8011F804(timer->sprites[i], -640.0f * timer->phase + lbl_803C3CF0[i][0], lbl_803C3CF0[i][1]);
        }
    }
    {
        int hundreds = (timer->value / 100) % 10;
        int tens = (timer->value / 10) % 10;
        int units = timer->value % 10;
        int first = 0x1ecd, second = 0x1ecd;
        if (hundreds != 0) {
            first = hundreds + 0x1b73;
            second = tens + 0x1b73;
        } else if (tens != 0) second = tens + 0x1b73;
        SpriteLayer_SetResource(timer->sprites[1], first);
        SpriteLayer_SetResource(timer->sprites[2], second);
        SpriteLayer_SetResource(timer->sprites[3], units + 0x1b73);
        for (int i = 0; i < 7; ++i) SpriteHandle_RecomputeCull(timer->sprites[i]);
    }
}

extern "C" int JumpDistanceMode_Update(JumpDistanceMode *self)
{
    Vec3f target, eye;
    if (self->ready == 0) self->ready = 1;
    ItemObjectManager_PerFrameUpdate(GetRaceContextPtr());
    fn_802128F4(self->gauge, self->car);
    fn_8023E324(self->itemSlot, self->ready);
    JumpDistanceMode_HandlePhysics(self);
    Fog_UpdateFromCourseScene3D();
    UpdateCamera(self->scenePos);
    LakituStart_UpdateCountdown(self->lakitu);
    CourseEnvironment_UpdateAndCullZones_Timed(self->env);
    if (g_raceEnded == 0) JumpDistanceMode_UpdateGameplay(self);
    CObj_LoadProjMatrix(self->scene, &target);
    CObj_ApplyScissor(self->scene, &eye);
    ItemObjectManager_Update();
    VfxSlotMgr_Update(target, eye);
    if (IsRaceStarted() == 1 && g_raceEnded != 1 && self->x50 < 2 && g_raceTimeRemaining >= 0.0f) {
        if (self->gauge->running == 0) g_raceTimeRemaining -= 0.01666666753590107f;
        else g_raceTimeRemaining -= 0.01666666753590107f * self->gauge->step;
        if (g_raceTimeRemaining < 0.0f) {
            g_raceTimeRemaining = 0.0f;
            g_raceEnded = 1;
        }
    }
    fn_802124FC(self->grid);
    fn_80253FD8(self->hud, g_raceTimeRemaining);
    fn_80253EBC(self->hud, 100.0f * CarObject_CalcSpeedRatio(self->car));
    fn_80253EC0(self->hud, KartItem_GetCurrentSpeedWithBonus(self->car));
    HUD_FrameUpdate(self->hud);
    UpdateTimer(self->timer);
    RumbleUpdate();
    TransitionEffect_Tick(lbl_806D109C);
    if (g_raceEnded == 1) {
        if (self->x48 > 0) --self->x48;
        else {
            if (self->x4C == 0) {
                if (self->x84 > 15) self->x84 = 15;
                self->grid->pending = self->x84 - self->grid->next;
                SetCoinCount(self->x84);
                int best = fn_801231AC();
                float distance = self->x58;
                int record = distance >= (float)best;
                if (self->x45 != 0) {
                    int text = NokoNokoChallenge_CalcResultText(self, 1, record);
                    fn_80253C74(self->hud, 1, text, (int)distance);
                    KartMovement_ResetOnGoal(CarObject_GetRenderObj(self->car));
                } else {
                    int text = NokoNokoChallenge_CalcResultText(self, 0, record);
                    fn_80253C74(self->hud, 0, text, (int)distance);
                    KartMovement_ResetOnTimeout(CarObject_GetRenderObj(self->car));
                }
                NokoNokoChallenge_SaveResult(self, self->x84, self->x45);
                TimerDisplay *resultTimer = self->timer;
                resultTimer->phase = 0.0f;
                resultTimer->active = 1;
                Object_SetByte10_Return1(self->scene, 1);
                g_lakituStartAnimDone = 0;
            } else if (fn_80253C40(self->hud)) return NokoNokoChallenge_TransitionToResult(self);
            ++self->x4C;
        }
    }
    if (g_weatherSystem) fn_8016B32C(g_weatherSystem);
    return -2;
}
#pragma use_lmw_stmw reset

#endif

/* === extracted from auto_JumpDistanceMode_Upd_text_1 === */
/* Copy into the TU between forward decls and function bodies; */
/* keep emit order = target section layout (do not sort). */

/* --- extern decls: branch callees (bl/b targets) --- */
/* Open prototype (`extern void Foo();`) accepts any call signature; */
/* refine if the real prototype matters for header consumers. */
extern void CObj_ApplyScissor();
extern void CObj_LoadIntoGX();
extern void CObj_LoadProjMatrix();
extern void CarObject_CalcSpeedRatio();
extern void CarObject_GetRenderObj();
extern void CourseEnvironment_UpdateAndCullZones_Timed();
extern void Fog_UpdateFromCourseScene3D();
extern void GetRaceContextPtr();
extern void HUD_FrameUpdate();
extern void IsRaceStarted();
extern void ItemObjectManager_PerFrameUpdate();
extern void ItemObjectManager_Update();
extern void JumpDistanceMode_HandlePhysics();
extern void JumpDistanceMode_UpdateGameplay();
extern void KartItem_GetCurrentSpeedWithBonus();
extern void KartMovement_ResetOnGoal();
extern void KartMovement_ResetOnTimeout();
extern void LUT_Cosine();
extern void LUT_Sine();
extern void LakituStart_UpdateCountdown();
extern void NokoNokoChallenge_CalcResultText();
extern void NokoNokoChallenge_SaveResult();
extern void NokoNokoChallenge_TransitionToResult();
extern void Object_SetByte10_Return1();
extern void RumbleUpdate();
extern void SetCoinCount();
extern void SpriteHandle_RecomputeCull();
extern void SpriteLayer_SetResource();
extern void Terrain_RaycastWall();
extern void TransitionEffect_Tick();
extern void Vec3_Subtract();
extern void VfxSlotMgr_Update();
extern void fn_8011F804();
extern void fn_801231AC();
extern void fn_8016B32C();
extern void fn_802124FC();
extern void fn_802128F4();
extern void fn_8023E324();
extern void fn_80253C40();
extern void fn_80253C74();
extern void fn_80253EBC();
extern void fn_80253EC0();
extern void fn_80253FD8();

/* --- extern decls: sda21-referenced data --- */
extern unsigned int g_lakituStartAnimDone;
extern unsigned int g_raceEnded;
extern unsigned int g_raceTimeRemaining;
extern unsigned int g_weatherSystem;
extern unsigned int lbl_806D109C;
extern unsigned int lbl_806DAD70;
extern unsigned int lbl_806DAD74;
extern unsigned int lbl_806DAD7C;
extern unsigned int lbl_806DAD88;
extern unsigned int lbl_806DAD90;
extern unsigned int lbl_806DAD98;
extern unsigned int lbl_806DADA4;
extern unsigned int lbl_806DADB0;
extern unsigned int lbl_806DADD8;
extern unsigned int lbl_806DADE0;
extern unsigned int lbl_806DADE8;
extern unsigned int lbl_806DADEC;
extern unsigned int lbl_806DADF0;
extern unsigned int lbl_806DADF4;

/* --- extern decls: large-data refs (@ha/@l pairs) --- */
/* Open array (`[]`) avoids sda21 strict-mode link errors when a future */
/* promote rewrites the asm_fn to C and references the symbol as `arr[i]`. */
extern unsigned int lbl_803C3CF0[];

/* --- function index (1 fns, .text 0x80211E6C..0x802124FC) ---
 * [  0] 0x80211E6C size:0x690   global JumpDistanceMode_Update
 */

/* --- forward decls --- */
asm void JumpDistanceMode_Update(void);

/* --- extab (manual emit, .extab_user -> extab via objcopy) --- */
#pragma section R ".extab_user"
__declspec(section ".extab_user") static const unsigned char extab_JumpDistanceMode_Update[8] = {
    0x28, 0x4A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

/* --- extabindex (manual emit, .extabindex_user -> extabindex via objcopy) --- */
#pragma section R ".extabindex_user"
__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_JumpDistanceMode_Update = {
    (void *)&JumpDistanceMode_Update, 0x00000690, (void *)extab_JumpDistanceMode_Update
};

/* --- asm function bodies (.text order = fn address order) --- */
asm void JumpDistanceMode_Update(void) { /* 0x80211E6C size:0x690 */
    nofralloc
    stwu r1, -0xc0(r1)
    mflr r0
    stw r0, 0xc4(r1)
    stfd f31, 0xb0(r1)
    psq_st f31, 0xb8(r1), 0, 0
    stmw r27, 0x9c(r1)
    mr r29, r3
    lbz r0, 0x44(r3)
    cmplwi r0, 0x0
    bne JumpDistanceMode_Update_L_80211E9C
    li r0, 0x1
    stb r0, 0x44(r29)
    JumpDistanceMode_Update_L_80211E9C:
    bl GetRaceContextPtr
    bl ItemObjectManager_PerFrameUpdate
    lwz r3, 0x3c(r29)
    lwz r4, 0x8(r29)
    bl fn_802128F4
    lwz r3, 0x1c(r29)
    lbz r4, 0x44(r29)
    bl fn_8023E324
    mr r3, r29
    bl JumpDistanceMode_HandlePhysics
    bl Fog_UpdateFromCourseScene3D
    lwz r30, 0x40(r29)
    lwz r0, 0x0(r30)
    cmpwi r0, 0x2
    beq JumpDistanceMode_Update_L_80211FD8
    bge JumpDistanceMode_Update_L_80211EEC
    cmpwi r0, 0x0
    beq JumpDistanceMode_Update_L_802120B8
    bge JumpDistanceMode_Update_L_80211EFC
    b JumpDistanceMode_Update_L_802120B8
    JumpDistanceMode_Update_L_80211EEC:
    cmpwi r0, 0x4
    beq JumpDistanceMode_Update_L_80211FF4
    bge JumpDistanceMode_Update_L_802120B8
    b JumpDistanceMode_Update_L_80211FE4
    JumpDistanceMode_Update_L_80211EFC:
    lwz r3, 0x4(r30)
    addi r4, r1, 0xc
    bl CObj_ApplyScissor
    lwz r3, 0x4(r30)
    addi r4, r1, 0x18
    bl CObj_LoadProjMatrix
    addi r3, r1, 0xc
    addi r4, r1, 0x18
    addi r5, r1, 0x30
    bl Vec3_Subtract
    lfs f0, 0x30(r1)
    lfs f2, 0x38(r1)
    fmuls f1, f0, f0
    lfs f0, lbl_806DAD7C(r2)
    fmuls f2, f2, f2
    fadds f4, f1, f2
    fcmpo cr0, f4, f0
    ble JumpDistanceMode_Update_L_80211F90
    frsqrte f1, f4
    lfd f3, lbl_806DAD90(r2)
    lfd f2, lbl_806DAD98(r2)
    fmul f0, f1, f1
    fmul f1, f3, f1
    fnmsub f0, f4, f0, f2
    fmul f1, f1, f0
    fmul f0, f1, f1
    fmul f1, f3, f1
    fnmsub f0, f4, f0, f2
    fmul f1, f1, f0
    fmul f0, f1, f1
    fmul f1, f3, f1
    fnmsub f0, f4, f0, f2
    fmul f0, f1, f0
    fmul f0, f4, f0
    frsp f0, f0
    stfs f0, 0x8(r1)
    lfs f4, 0x8(r1)
    JumpDistanceMode_Update_L_80211F90:
    lfs f0, lbl_806DADE8(r2)
    lfs f1, lbl_806DADEC(r2)
    fmuls f31, f0, f4
    bl LUT_Cosine
    lfs f0, 0xc(r1)
    fmadds f0, f31, f1, f0
    lfs f1, lbl_806DADEC(r2)
    stfs f0, 0x24(r1)
    bl LUT_Sine
    lfs f2, 0x14(r1)
    addi r4, r1, 0x24
    lfs f0, 0x10(r1)
    fmadds f1, f31, f1, f2
    stfs f0, 0x28(r1)
    stfs f1, 0x2c(r1)
    lwz r3, 0x4(r30)
    bl CObj_LoadIntoGX
    b JumpDistanceMode_Update_L_802120B8
    JumpDistanceMode_Update_L_80211FD8:
    li r0, 0x3
    stw r0, 0x0(r30)
    b JumpDistanceMode_Update_L_802120B8
    JumpDistanceMode_Update_L_80211FE4:
    lwz r3, 0x4(r30)
    addi r4, r30, 0x8
    bl CObj_LoadIntoGX
    b JumpDistanceMode_Update_L_802120B8
    JumpDistanceMode_Update_L_80211FF4:
    lfs f1, 0x20(r30)
    lfs f0, lbl_806DADF0(r2)
    fcmpo cr0, f1, f0
    bge JumpDistanceMode_Update_L_802120AC
    lfs f0, 0x8(r30)
    lfs f1, lbl_806DADD8(r2)
    stfs f0, 0x3c(r1)
    lfs f0, 0xc(r30)
    stfs f0, 0x40(r1)
    lfs f0, 0x10(r30)
    stfs f0, 0x44(r1)
    lfs f0, 0x20(r30)
    fmuls f1, f1, f0
    bl LUT_Sine
    lfs f3, 0x14(r30)
    addi r3, r1, 0x3c
    lfs f2, 0x8(r30)
    addi r4, r30, 0x8
    lfs f0, lbl_806DADB0(r2)
    addi r5, r1, 0x48
    fmadds f2, f3, f1, f2
    addi r6, r1, 0x54
    stfs f2, 0x8(r30)
    lfs f3, 0x18(r30)
    lfs f2, 0xc(r30)
    fmadds f2, f3, f1, f2
    stfs f2, 0xc(r30)
    lfs f3, 0x1c(r30)
    lfs f2, 0x10(r30)
    fmadds f1, f3, f1, f2
    stfs f1, 0x10(r30)
    lfs f1, 0x20(r30)
    fadds f0, f1, f0
    stfs f0, 0x20(r30)
    bl Terrain_RaycastWall
    clrlwi r0, r3, 24
    cmplwi r0, 0x1
    bne JumpDistanceMode_Update_L_802120AC
    lfs f1, 0x3c(r1)
    lfs f0, lbl_806DADF0(r2)
    stfs f1, 0x8(r30)
    lfs f1, 0x40(r1)
    stfs f1, 0xc(r30)
    lfs f1, 0x44(r1)
    stfs f1, 0x10(r30)
    stfs f0, 0x20(r30)
    JumpDistanceMode_Update_L_802120AC:
    lwz r3, 0x4(r30)
    addi r4, r30, 0x8
    bl CObj_LoadIntoGX
    JumpDistanceMode_Update_L_802120B8:
    lwz r3, 0xc(r29)
    bl LakituStart_UpdateCountdown
    lwz r3, 0x10(r29)
    bl CourseEnvironment_UpdateAndCullZones_Timed
    lbz r0, g_raceEnded(r13)
    cmplwi r0, 0x0
    bne JumpDistanceMode_Update_L_802120DC
    mr r3, r29
    bl JumpDistanceMode_UpdateGameplay
    JumpDistanceMode_Update_L_802120DC:
    lwz r3, 0x14(r29)
    addi r4, r1, 0x84
    bl CObj_LoadProjMatrix
    lwz r3, 0x14(r29)
    addi r4, r1, 0x78
    bl CObj_ApplyScissor
    bl ItemObjectManager_Update
    lwz r9, 0x78(r1)
    addi r3, r1, 0x6c
    lwz r8, 0x7c(r1)
    addi r4, r1, 0x60
    lwz r7, 0x80(r1)
    lwz r6, 0x84(r1)
    lwz r5, 0x88(r1)
    lwz r0, 0x8c(r1)
    stw r9, 0x60(r1)
    stw r8, 0x64(r1)
    stw r7, 0x68(r1)
    stw r6, 0x6c(r1)
    stw r5, 0x70(r1)
    stw r0, 0x74(r1)
    bl VfxSlotMgr_Update
    bl IsRaceStarted
    clrlwi r0, r3, 24
    cmplwi r0, 0x1
    bne JumpDistanceMode_Update_L_802121B8
    lbz r0, g_raceEnded(r13)
    cmplwi r0, 0x1
    beq JumpDistanceMode_Update_L_802121B8
    lwz r0, 0x50(r29)
    cmpwi r0, 0x2
    bge JumpDistanceMode_Update_L_802121B8
    lfs f2, g_raceTimeRemaining(r13)
    lfs f0, lbl_806DAD7C(r2)
    fcmpo cr0, f2, f0
    cror eq, gt, eq
    bne JumpDistanceMode_Update_L_802121B8
    lwz r3, 0x3c(r29)
    lbz r0, 0x1(r3)
    cmplwi r0, 0x0
    bne JumpDistanceMode_Update_L_8021218C
    lfs f0, lbl_806DAD74(r2)
    fsubs f2, f2, f0
    b JumpDistanceMode_Update_L_80212198
    JumpDistanceMode_Update_L_8021218C:
    lfs f1, lbl_806DAD74(r2)
    lfs f0, 0xc(r3)
    fnmsubs f2, f1, f0, f2
    JumpDistanceMode_Update_L_80212198:
    frsp f1, f2
    lfs f0, lbl_806DAD7C(r2)
    stfs f2, g_raceTimeRemaining(r13)
    fcmpo cr0, f1, f0
    bge JumpDistanceMode_Update_L_802121B8
    li r0, 0x1
    stfs f0, g_raceTimeRemaining(r13)
    stb r0, g_raceEnded(r13)
    JumpDistanceMode_Update_L_802121B8:
    lwz r3, 0x7c(r29)
    bl fn_802124FC
    lwz r3, 0x28(r29)
    lfs f1, g_raceTimeRemaining(r13)
    bl fn_80253FD8
    lwz r3, 0x8(r29)
    bl CarObject_CalcSpeedRatio
    lfs f0, lbl_806DADA4(r2)
    lwz r3, 0x28(r29)
    fmuls f1, f0, f1
    bl fn_80253EBC
    lwz r3, 0x8(r29)
    bl KartItem_GetCurrentSpeedWithBonus
    lwz r3, 0x28(r29)
    bl fn_80253EC0
    lwz r3, 0x28(r29)
    bl HUD_FrameUpdate
    lwz r30, 0x2c(r29)
    lbz r0, 0x8(r30)
    cmplwi r0, 0x1
    bne JumpDistanceMode_Update_L_8021226C
    lfs f1, 0xc(r30)
    lfs f0, lbl_806DAD70(r2)
    fcmpo cr0, f1, f0
    cror eq, gt, eq
    beq JumpDistanceMode_Update_L_80212344
    lfs f0, lbl_806DAD88(r2)
    lis r3, lbl_803C3CF0@ha
    lfs f31, lbl_806DADF4(r2)
    addi r31, r3, lbl_803C3CF0@l
    fadds f0, f1, f0
    mr r27, r30
    li r28, 0x0
    stfs f0, 0xc(r30)
    JumpDistanceMode_Update_L_80212240:
    lfs f1, 0xc(r30)
    lfs f0, 0x0(r31)
    lwz r3, 0x10(r27)
    fmadds f1, f31, f1, f0
    lfs f2, 0x4(r31)
    bl fn_8011F804
    addi r28, r28, 0x1
    addi r27, r27, 0x4
    cmpwi r28, 0x7
    addi r31, r31, 0x8
    blt JumpDistanceMode_Update_L_80212240
    JumpDistanceMode_Update_L_8021226C:
    lis r3, 0x51ec
    lwz r0, 0x0(r30)
    subi r4, r3, 0x7ae1
    mulhw r5, r4, r0
    lis r3, 0x6666
    li r4, 0x1ecd
    addi r6, r3, 0x6667
    mr r31, r4
    srawi r3, r5, 5
    srwi r5, r3, 31
    add r10, r3, r5
    mulhw r3, r6, r10
    srawi r3, r3, 2
    srwi r5, r3, 31
    add r9, r3, r5
    mulhw r7, r6, r0
    srawi r3, r7, 2
    srwi r5, r3, 31
    add r8, r3, r5
    mulhw r3, r6, r8
    srawi r6, r3, 2
    srawi r3, r7, 2
    srwi r7, r6, 31
    srwi r5, r3, 31
    add r3, r3, r5
    add r6, r6, r7
    mulli r9, r9, 0xa
    mulli r5, r6, 0xa
    subf. r7, r9, r10
    mulli r3, r3, 0xa
    subf r5, r5, r8
    subf r28, r3, r0
    beq JumpDistanceMode_Update_L_802122FC
    addi r4, r7, 0x1b73
    addi r31, r5, 0x1b73
    b JumpDistanceMode_Update_L_80212308
    JumpDistanceMode_Update_L_802122FC:
    cmpwi r5, 0x0
    beq JumpDistanceMode_Update_L_80212308
    addi r31, r5, 0x1b73
    JumpDistanceMode_Update_L_80212308:
    lwz r3, 0x14(r30)
    bl SpriteLayer_SetResource
    lwz r3, 0x18(r30)
    mr r4, r31
    bl SpriteLayer_SetResource
    lwz r3, 0x1c(r30)
    addi r4, r28, 0x1b73
    bl SpriteLayer_SetResource
    li r31, 0x0
    JumpDistanceMode_Update_L_8021232C:
    lwz r3, 0x10(r30)
    bl SpriteHandle_RecomputeCull
    addi r31, r31, 0x1
    addi r30, r30, 0x4
    cmpwi r31, 0x7
    blt JumpDistanceMode_Update_L_8021232C
    JumpDistanceMode_Update_L_80212344:
    bl RumbleUpdate
    lwz r3, lbl_806D109C(r13)
    cmplwi r3, 0x0
    bne JumpDistanceMode_Update_L_80212358
    li r3, 0x0
    JumpDistanceMode_Update_L_80212358:
    bl TransitionEffect_Tick
    lbz r0, g_raceEnded(r13)
    cmplwi r0, 0x1
    bne JumpDistanceMode_Update_L_802124CC
    lwz r3, 0x48(r29)
    cmpwi r3, 0x0
    ble JumpDistanceMode_Update_L_80212380
    subi r0, r3, 0x1
    stw r0, 0x48(r29)
    b JumpDistanceMode_Update_L_802124CC
    JumpDistanceMode_Update_L_80212380:
    lwz r0, 0x4c(r29)
    cmpwi r0, 0x0
    bne JumpDistanceMode_Update_L_802124A4
    lwz r0, 0x84(r29)
    cmpwi r0, 0xf
    ble JumpDistanceMode_Update_L_802123A0
    li r0, 0xf
    stw r0, 0x84(r29)
    JumpDistanceMode_Update_L_802123A0:
    lwz r4, 0x7c(r29)
    lwz r0, 0x84(r29)
    lwz r3, 0x8(r4)
    subf r0, r3, r0
    stw r0, 0xc(r4)
    lwz r3, 0x84(r29)
    bl SetCoinCount
    bl fn_801231AC
    xoris r3, r3, 0x8000
    lis r0, 0x4330
    stw r3, 0x94(r1)
    lfd f1, lbl_806DADE0(r2)
    stw r0, 0x90(r1)
    lfs f31, 0x58(r29)
    lfd f0, 0x90(r1)
    fsubs f0, f0, f1
    fcmpo cr0, f31, f0
    cror eq, gt, eq
    mfcr r3
    lbz r0, 0x45(r29)
    extrwi r5, r3, 1, 2
    cmplwi r0, 0x0
    beq JumpDistanceMode_Update_L_80212434
    mr r3, r29
    li r4, 0x1
    bl NokoNokoChallenge_CalcResultText
    fctiwz f0, f31
    mr r5, r3
    lwz r3, 0x28(r29)
    li r4, 0x1
    stfd f0, 0x90(r1)
    lwz r6, 0x94(r1)
    bl fn_80253C74
    lwz r3, 0x8(r29)
    bl CarObject_GetRenderObj
    bl KartMovement_ResetOnGoal
    b JumpDistanceMode_Update_L_80212468
    JumpDistanceMode_Update_L_80212434:
    mr r3, r29
    li r4, 0x0
    bl NokoNokoChallenge_CalcResultText
    fctiwz f0, f31
    mr r5, r3
    lwz r3, 0x28(r29)
    li r4, 0x0
    stfd f0, 0x90(r1)
    lwz r6, 0x94(r1)
    bl fn_80253C74
    lwz r3, 0x8(r29)
    bl CarObject_GetRenderObj
    bl KartMovement_ResetOnTimeout
    JumpDistanceMode_Update_L_80212468:
    lwz r4, 0x84(r29)
    mr r3, r29
    lbz r5, 0x45(r29)
    bl NokoNokoChallenge_SaveResult
    lwz r3, 0x2c(r29)
    li r0, 0x1
    lfs f0, lbl_806DAD7C(r2)
    li r4, 0x1
    stfs f0, 0xc(r3)
    stb r0, 0x8(r3)
    lwz r3, 0x14(r29)
    bl Object_SetByte10_Return1
    li r0, 0x0
    stb r0, g_lakituStartAnimDone(r13)
    b JumpDistanceMode_Update_L_802124C0
    JumpDistanceMode_Update_L_802124A4:
    lwz r3, 0x28(r29)
    bl fn_80253C40
    clrlwi. r0, r3, 24
    beq JumpDistanceMode_Update_L_802124C0
    mr r3, r29
    bl NokoNokoChallenge_TransitionToResult
    b JumpDistanceMode_Update_L_802124E0
    JumpDistanceMode_Update_L_802124C0:
    lwz r3, 0x4c(r29)
    addi r0, r3, 0x1
    stw r0, 0x4c(r29)
    JumpDistanceMode_Update_L_802124CC:
    lwz r3, g_weatherSystem(r13)
    cmplwi r3, 0x0
    beq JumpDistanceMode_Update_L_802124DC
    bl fn_8016B32C
    JumpDistanceMode_Update_L_802124DC:
    li r3, -0x2
    JumpDistanceMode_Update_L_802124E0:
    psq_l f31, 0xb8(r1), 0, 0
    lfd f31, 0xb0(r1)
    lmw r27, 0x9c(r1)
    lwz r0, 0xc4(r1)
    mtlr r0
    addi r1, r1, 0xc0
    blr
}

