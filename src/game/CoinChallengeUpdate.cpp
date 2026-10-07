/* Local observed views; reconstructed from the target DOL disassembly. */
struct Vec3 { float x, y, z; };
struct CoinInput {
    virtual void slot08();
    virtual void slot0c();
    virtual float steering();
    virtual void slot14();
    virtual float accelerator();
    virtual float brake();
};
struct CoinRender { char pad[0x2cc]; int coins; };
struct CoinSprites {
    void *sprite[9];
    unsigned char exiting;
    char pad[3];
    float slide;
};
struct CoinChallengeView {
    void *vptr;
    int base04;
    void *car, *lakitu, *environment, *camera, *goalCamera;
    char pad1c[0xc];
    void *hud;
    CoinSprites *sprites;
    unsigned char active, won;
    char pad32[2];
    int endDelay, resultFrames, targetCoins, awards, divisor;
};
extern "C" {
extern unsigned char g_raceEnded, g_lakituStartAnimDone, lbl_806D1290;
extern unsigned char lbl_806D1548[8];
extern float g_raceTimeRemaining;
extern void *g_weatherSystem, *lbl_806D109C;
extern float lbl_806DAE24, lbl_806DAE28, lbl_806DAE2C, lbl_806DAE30;
extern float lbl_806DAE34, lbl_806DAE38, lbl_806DAE3C, lbl_806DAE40;
extern float lbl_803C3DD8[18];
void *GetRaceContextPtr();
void ItemObjectManager_PerFrameUpdate(void *);
void *GetInputManager();
CoinInput *InputMgr_GetPlayer(void *, int);
bool IsRaceStarted();
unsigned char NokoNokoChallenge_HandleBrakeInput(void *, int);
void CarObject_ApplyInput(void *, bool, float, float, float);
void CarObject_FrameUpdate(void *, int);
void KartItem_UpdateShadowBillboardAndViewport(void *, void *, int);
void KartMovement_SetSpeedScale(void *, float);
CoinRender *CarObject_GetRenderObj(void *);
void *KartDriver_GetKartRootMtx(void *);
void ChallengeGoalCamera_Update(void *, void *, void *);
void Fog_UpdateFromCourseScene3D();
void LakituStart_UpdateCountdown(void *);
void CourseEnvironment_UpdateAndCullZones_Timed(void *);
void fn_8013A534();
int Clamp_Int(int, int, int);
void SpriteLayer_SetResource(void *, int);
unsigned char IsCardValid();
int CObj_LoadProjMatrix(void *, Vec3 *);
int CObj_ApplyScissor(void *, Vec3 *);
void ItemObjectManager_Update();
void VfxSlotMgr_Update(Vec3, Vec3);
void fn_80253FD8(void *, float);
float CarObject_CalcSpeedRatio(void *);
void fn_80253EBC(void *, float);
float KartItem_GetCurrentSpeedWithBonus(void *);
void fn_80253EC0(void *, float);
void HUD_FrameUpdate(void *);
void fn_8011F804(void *, float, float);
void SpriteHandle_RecomputeCull(void *);
void TransitionEffect_Tick(void *);
void SetCoinCount(int);
int NokoNokoChallenge_CalcResultText(void *, int, int);
void fn_80253C74(void *, int, int, int);
void KartMovement_ResetOnGoal(void *);
void KartMovement_ResetOnTimeout(void *);
void NokoNokoChallenge_SaveResult(void *, int, unsigned int);
int Object_SetByte10_Return1(void *, int);
unsigned char fn_80253C40(void *);
int NokoNokoChallenge_TransitionToResult(void *);
void fn_8016B32C(void *);

static inline void *getTransition() {
    void *p = lbl_806D109C;
    if (!p) p = 0;
    return p;
}

int MiniGame_CoinChallenge_Update(CoinChallengeView *self) {
    CoinSprites *sprites;
    int before;
    int after;
    CoinInput *input;
    int i;
    float accelerator, brake;
    Vec3 projection, scissor;
    if (self->active == 0) self->active = 1;
    ItemObjectManager_PerFrameUpdate(GetRaceContextPtr());
    if (g_raceEnded != 1) {
        input = InputMgr_GetPlayer(GetInputManager(), 0);
        if (lbl_806D1290 == 0) accelerator = input->accelerator();
        else accelerator = lbl_806DAE24;
        brake = input->brake();
        int holding = 0;
        if (accelerator < lbl_806DAE2C && brake < lbl_806DAE2C && IsRaceStarted()) holding = 1;
        if (NokoNokoChallenge_HandleBrakeInput(self, holding) == 1) accelerator = lbl_806DAE28;
        bool started = IsRaceStarted();
        float steering = input->steering();
        CarObject_ApplyInput(self->car, started, steering, accelerator, brake);
        CarObject_FrameUpdate(self->car, 0);
        KartItem_UpdateShadowBillboardAndViewport(self->car, self->camera, 0);
    } else {
        CarObject_ApplyInput(self->car, 1, lbl_806DAE30, lbl_806DAE30, lbl_806DAE30);
        KartMovement_SetSpeedScale(self->car, lbl_806DAE34);
        CarObject_FrameUpdate(self->car, 0);
        if (self->endDelay > 0) KartItem_UpdateShadowBillboardAndViewport(self->car, self->camera, 0);
        else ChallengeGoalCamera_Update(self->goalCamera, self->camera, KartDriver_GetKartRootMtx(CarObject_GetRenderObj(self->car)));
    }
    Fog_UpdateFromCourseScene3D();
    LakituStart_UpdateCountdown(self->lakitu);
    CourseEnvironment_UpdateAndCullZones_Timed(self->environment);
    before = CarObject_GetRenderObj(self->car)->coins;
    fn_8013A534();
    if (g_raceEnded != 1) {
        after = CarObject_GetRenderObj(self->car)->coins;
        int shown = Clamp_Int(after, 0, self->targetCoins);
        sprites = self->sprites;
        if (shown > 99) shown = 99;
        int tens = shown / 10;
        SpriteLayer_SetResource(sprites->sprite[5], shown % 10 + 0x14ba);
        short tensResource = 0x1ecd;
        if (tens > 0) tensResource = tens + 0x14ba;
        SpriteLayer_SetResource(sprites->sprite[4], tensResource);
        if (after != before && IsCardValid() == 1) {
            if (self->divisor - 1 == after % self->divisor) lbl_806D1548[0] = 1;
            if (before / self->divisor != after / self->divisor) ++self->awards;
        }
        if (after >= self->targetCoins) {
            self->won = 1;
            self->endDelay = 30;
            g_raceEnded = 1;
        }
    }
    CObj_LoadProjMatrix(self->camera, &projection);
    CObj_ApplyScissor(self->camera, &scissor);
    ItemObjectManager_Update();
    VfxSlotMgr_Update(projection, scissor);
    if (IsRaceStarted() == 1 && g_raceEnded != 1) {
        float zero;
        float remaining;
        remaining = g_raceTimeRemaining;
        zero = lbl_806DAE30;
        if (remaining >= zero) {
            g_raceTimeRemaining = remaining - lbl_806DAE38;
            if (g_raceTimeRemaining < zero) {
                g_raceTimeRemaining = zero;
                g_raceEnded = 1;
            }
        }
    }
    fn_80253FD8(self->hud, g_raceTimeRemaining);
    fn_80253EBC(self->hud, lbl_806DAE3C * CarObject_CalcSpeedRatio(self->car));
    fn_80253EC0(self->hud, KartItem_GetCurrentSpeedWithBonus(self->car));
    HUD_FrameUpdate(self->hud);
    sprites = self->sprites;
    if (sprites->exiting != 0) {
        if (sprites->slide >= lbl_806DAE28) goto sprites_done;
        accelerator = lbl_806DAE40;
        float *positions = lbl_803C3DD8;
        void **cursor = sprites->sprite;
        sprites->slide += lbl_806DAE2C;
        for (i = 0; i < 9; ++i, positions += 2, ++cursor)
            fn_8011F804(*cursor, accelerator * sprites->slide + positions[0], positions[1]);
    }
    {
        for (i = 0; i < 9; ++i, sprites = (CoinSprites *)((char *)sprites + 4))
            SpriteHandle_RecomputeCull(sprites->sprite[0]);
    }
sprites_done:
    TransitionEffect_Tick(getTransition());
    if (g_raceEnded == 1) {
        if (self->endDelay > 0) --self->endDelay;
        else {
            if (self->resultFrames == 0) {
                SetCoinCount(self->awards);
                if (self->won != 0) {
                    CoinRender *render = CarObject_GetRenderObj(self->car);
                    fn_80253C74(self->hud, 1, NokoNokoChallenge_CalcResultText(self, 1, 0), render->coins);
                    KartMovement_ResetOnGoal(CarObject_GetRenderObj(self->car));
                } else {
                    CoinRender *render = CarObject_GetRenderObj(self->car);
                    fn_80253C74(self->hud, 0, NokoNokoChallenge_CalcResultText(self, 0, 0), render->coins);
                    KartMovement_ResetOnTimeout(CarObject_GetRenderObj(self->car));
                }
                NokoNokoChallenge_SaveResult(self, self->awards, self->won);
                self->sprites->exiting = 1;
                Object_SetByte10_Return1(self->camera, 1);
                g_lakituStartAnimDone = 0;
            } else if (fn_80253C40(self->hud)) return NokoNokoChallenge_TransitionToResult(self);
            ++self->resultFrames;
        }
    }
    if (g_weatherSystem) fn_8016B32C(g_weatherSystem);
    return -2;
}
}
