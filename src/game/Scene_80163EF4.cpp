#include "game/Scene_80163EF4Private.h"

static inline void CapTime(float limit, float &value) { if (value > limit) value = limit; }

extern "C" int fn_80163EF4(LoaderTick163 *s) {
    if (s->done || s->time <= lbl_806D88F0) {
        s->done = 1;
        return 1;
    }
    g_raceFrameCounterLo2digits = (BattleRoulette_TickAndGetCounter() * 3 + 1) % 100;
    ItemObjectManager_PerFrameUpdate(GetRaceContextPtr());
    float pedal;
    CalcSoundDirection(CarObject_GetRenderObj(g_carObjects[0]), s->paths, &pedal, 0);
    pedal = lbl_806D88F8;
    if (KartMovement_GetCurrentItemId(CarObject_GetRenderObj(g_carObjects[0])) != -1)
        s->heldItemFrames++;
    else s->heldItemFrames = 0;
    if (s->recording == 1) {
        RecordedPlayer163 *p = (RecordedPlayer163 *)InputMgr_GetPlayer(GetInputManager(), 0);
        s->inputs[s->inputIndex].steer = p->Steering();
        s->inputs[s->inputIndex].pedal = p->Pedal();
        s->inputs[s->inputIndex].brake = p->Brake();
        s->inputs[s->inputIndex].buttons = p->Buttons(0xe3ff);
    }
    float steer = s->inputs[s->inputIndex].steer;
    pedal = s->inputs[s->inputIndex].pedal;
    float brake = s->inputs[s->inputIndex].brake;
    int buttons = s->inputs[s->inputIndex].buttons;
    if (s->inputIndex < 2699) s->inputIndex++;
    if (g_raceEnded) {
        steer = CalcSoundDirection(CarObject_GetRenderObj(g_carObjects[0]), s->paths, &pedal, 0);
        brake = lbl_806D88F0;
        buttons = 0;
    }
    CarObject_ApplyInput(g_carObjects[0], IsRaceStarted(), steer, pedal, brake);
    CarObject_FrameUpdate(g_carObjects[0], 0);
    ItemBox_ProcessPickup(g_itemSelects[0], g_carObjects[0], 0, buttons, 0, brake);
    RankingMgr_UpdatePositions(s->ai);
    if ((unsigned char)IsRaceStarted() == 1) {
        Checkpoint163 *a = Path_LookupCheckpointOffset(s->paths, 0, 0);
        Checkpoint163 *b = Path_LookupCheckpointOffset(s->paths, 0, 1);
        Vec v = lbl_80369C44;
        v.x = a->x;
        v.z = a->z;
        Vec w = lbl_80369C50;
        w.x = b->x;
        w.z = b->z;
        if (JObj_IsForwardDotBelowThreshold(CarObject_GetRenderObj(g_carObjects[0]), &v, &w) == 1)
            Jyugemu_ReverseFlag_SetState(s->reverseFlag, 1);
        else Jyugemu_ReverseFlag_SetState(s->reverseFlag, 0);
    }
    fn_80208E30(s->system);
    if (!s->ready) s->ready = 1;
    KartItem_UpdateShadowBillboardAndViewport(g_carObjects[0], s->scene, 0);
    Fog_UpdateFromCourseScene3D();
    PathManager_UpdateAll(s->paths);
    LakituStart_UpdateCountdown(s->object);
    Jyugemu_Flag_Tick(s->flag);
    Jyugemu_ReverseFlag_Tick(s->reverseFlag);
    LapBannerScene_UpdateAndDriveAnim(s->banner);
    CourseEnvironment_UpdateAndCullZones_Timed(s->environment);
    CObj_LoadProjMatrix(s->scene, &lbl_80677CE8);
    CObj_ApplyScissor(s->scene, &lbl_80677CF4);
    ItemObjectManager_Update();
    VfxSlotMgr_Update(lbl_80677CE8, lbl_80677CF4);
    if (g_rendererGateFlag == 1 && (unsigned char)IsRaceStarted() == 1 && !g_raceEnded) {
        float zero = lbl_806D88F0;
        float raceTime = g_raceTimeRemaining;
        if (raceTime > zero) {
            g_raceTimeRemaining -= lbl_806D88FC;
            if (g_raceTimeRemaining < lbl_806D88F0) {
                g_raceTimeRemaining = lbl_806D88F0;
                CapTime(lbl_806D8900, s->time);
            }
        }
    }
    TransitionEffect_Tick(Transition());
    if (!g_finalLapBannerShown && g_currentLap >= g_totalLaps) g_finalLapBannerShown = 1;
    if (lbl_806D88F0 != g_raceTimeRemaining && g_raceResultCode == -2) {
        if (g_currentLap >= g_totalLaps + 1) {
            KartItem_OnFallOffOrDeath(g_carObjects[0]);
            CoinJumpFlasher_SetArmed(g_carObjects[0], 0);
            ItemSelect_Reset(g_itemSelects[0], 0);
            g_finalRacePosition = ((ResultKart163 *)g_playerRenderObj)->position;
            RaceResult_StoreLatest(GetKartSlotCharId(s->slot), g_finalRacePosition, g_bestLapTime, g_totalRaceTime);
            g_raceResultCode = RaceResult_InsertSortedRank(GetKartSlotCharId(s->slot), g_finalRacePosition, g_bestLapTime, g_totalRaceTime);
            SetRaceResultLatestPtr();
            Object_SetByte10_Return1(s->scene, 1);
            if (g_finalRacePosition == 0) {
                Jyugemu_Flag_SetKartDriver(s->flag, CarObject_GetRenderObj(g_carObjects[0]));
                KartMovement_ResetOnGoal(CarObject_GetRenderObj(g_carObjects[0]));
                fn_8016C554(1);
            } else {
                KartMovement_ResetOnTimeout(CarObject_GetRenderObj(g_carObjects[0]));
                fn_8016C554(0);
            }
            g_raceEnded = 1;
            g_lakituStartAnimDone = 0;
            CapTime(lbl_806D8900, s->time);
        } else if (g_lapChangePending) {
            if (g_finalLapBannerShown) {
                fn_8016C598();
                LapBannerScene_TriggerBannerAnim(s->banner);
            } else fn_8016C5CC();
            g_lapChangePending = 0;
        }
    }
    clItemBoxManager_Update(BoxManager());
    fn_8013A534();
    if (g_weatherSystem) fn_8016B32C(g_weatherSystem);
    if (s->time > lbl_806D88F0) s->time -= lbl_806D88F8;
    float duration = lbl_806D8060;
    float threshold = lbl_806D8904 - duration;
    float remaining = s->time;
    if (remaining > threshold)
        s->fade = Saturate_Double((remaining - threshold) / duration, lbl_806D88F0, lbl_806D88F8);
    else if (remaining < duration)
        s->fade = Saturate_Double(lbl_806D88F8 - remaining / duration, lbl_806D88F0, lbl_806D88F8);
    else s->fade = lbl_806D88F0;
    return 0;
}
