/* Time-attack update, 0x800A2B90..0x800A38F8. */
#include "game/TaMode_FrameUpdate_private.h"

extern "C" int TaMode_FrameUpdate(RaceScene *self)
{
    TaBattleTables *battle = &BATTLE;
    InputPlayer *pad = InputMgr_GetPlayer(GetInputManager(), 0);
    if (g_sceneTransitionTimer > 0 && --g_sceneTransitionTimer == 0) {
        SetSyncTarget(0x2d);
        void *stats = TitleStats();
        if (stats) TitleStats_FinalizeRace_PlayCountThenTitle(stats);
        return 13;
    }
    float steer = 0.0f;
    float accel, brake;
    signed char coins;
    signed char started;
    ItemObjectManager_PerFrameUpdate(GetRaceContextPtr());
    if (lbl_806D13B4) fn_8023E324(lbl_806D13B4, __ptmf_test(battle->memberFunction) != 0);
    if (g_raceEnded != 1) {
        long long now = OSGetTime();
        steer = QuantizeInput(pad->Steer());
        accel = QuantizeInput(pad->Brake());
        brake = accel;
        if (g_ccClass != 2) {
            if (!IsRaceStarted()) {
                lbl_806D13C4 = (unsigned int)now;
                lbl_806D13C0 = (unsigned int)(now >> 32);
            } else if (steer < 0.1f && accel < 0.1f) {
                if (!lbl_806D13B8) {
                    long long prev = ((long long)lbl_806D13C0 << 32) | lbl_806D13C4;
                    long long ms = (now - prev) / ((*(unsigned int *)0x800000f8 / 4) / 1000);
                    if ((float)ms / 1000.0f >= 4.0f) lbl_806D13B8 = 1;
                }
                if (lbl_806D13B8) steer = 1.0f;
            } else {
                lbl_806D13C4 = (unsigned int)now;
                lbl_806D13B8 = 0;
                lbl_806D13C0 = (unsigned int)(now >> 32);
            }
        }
        accel = QuantizeInput(pad->Accel());
        started = IsRaceStarted();
        if (IsRaceStarted() == 1 && lbl_806D13AC > 0) {
            TaRender *render = CarObject_GetRenderObj(g_carObjects[0]);
            if (KartMovement_GetCurrentItemId(render) != -1) {
                if (!KartItem_GetByte_f4(g_carObjects[0])) {
                    pad->Held(0xe3ff);
                    if (Input_IsItemButtonPressed() && RenderObj_UseItem(render, 0, 0)) {
                        void *stats = TitleStats();
                        if (stats) RankLog_OnPlayerVictory(stats, GetDisplayBufferIndex(), 0);
                        CarObject_ApplyDriftBoost(g_carObjects[0], 5, 3.0f);
                        --lbl_806D13AC;
                        if (lbl_806D13B4) {
                            if (lbl_806D13AC == 2) fn_8023E1E4(lbl_806D13B4, 0x116, 0);
                            if (lbl_806D13AC == 1) fn_8023E1E4(lbl_806D13B4, 0x17, 0);
                            if (lbl_806D13AC == 0) fn_8023E1E4(lbl_806D13B4, -1, 0);
                        }
                        lbl_806D13B0 = 30;
                    }
                }
            } else KartMovement_EquipItem(render, 0x17);
        }
    } else {
        accel = CalcSoundDirection(CarObject_GetRenderObj(g_carObjects[0]), lbl_806D13A4, &steer, 0);
        brake = 0.0f;
        started = 1;
    }
    CarObject_ApplyInput(g_carObjects[0], accel, steer, brake, started != 0);
    CarObject_FrameUpdate(g_carObjects[0], 0);
    if (!g_raceEnded && pad->Held(0x400) && GetCoinMilage(g_playerData) >= 4000)
        CoinJumpFlasher_Toggle(g_carObjects[0]);
    fn_8013A534();
    if (lbl_806D13A0) {
        coins = 0;
        if (lbl_806D1394 < lbl_806D138C) {
            accel = ((float *)lbl_806D1388)[lbl_806D1394 * 4];
            TaGhostFrame *frame = &lbl_806D1388[lbl_806D1394];
            steer = frame->steer;
            brake = frame->brake;
            started = frame->started;
            signed char item = frame->item;
            coins = frame->coins;
            ++lbl_806D1394;
            if (lbl_806D1398 && lbl_806CF198 > 0) {
                TaRender *render = CarObject_GetRenderObj(lbl_806D1398);
                if (KartMovement_GetCurrentItemId(render) != -1) {
                    if (item == 1) {
                        RenderObj_UseItem(render, 0, 0);
                        CarObject_ApplyDriftBoost(lbl_806D1398, 5, 3.0f);
                        --lbl_806CF198;
                    }
                } else KartMovement_EquipItem(render, 0x17);
            }
        } else if (lbl_806D1398) {
            accel = CalcSoundDirection(CarObject_GetRenderObj(lbl_806D1398), lbl_806D13A4, &steer, lbl_806D139C);
            brake = 0.0f;
            started = IsRaceStarted();
        }
        if (lbl_806D1398) {
            if (IsRaceStarted() == 1) {
                void *bus = CarObject_GetRenderObj(lbl_806D1398)->itemBus;
                if (!CarObject_GetRenderObj(lbl_806D1398)->effectActive)
                    ItemEffectBus_ClearMask(bus, 0x8000000000ULL);
                else ItemEffectBus_OrMask(bus, 0x8000000000ULL);
            }
            CarObject_ApplyInput(lbl_806D1398, accel, steer, brake, started != 0);
            CarObject_FrameUpdate(lbl_806D1398, 0);
            TaRender *render = CarObject_GetRenderObj(lbl_806D1398);
            render->coins += coins;
        }
    }
    if (lbl_806D13B0 != 0) {
        if (--lbl_806D13B0 == 0) {
            if (lbl_806D13AC != 0) {
                StrPcb_SetStatusBits(StrPcb_GetInstance(), 4, 0);
                StrPcb_SetStatusBits(StrPcb_GetInstance(), 8, 0);
            } else {
                StrPcb_ClearStatusBits(StrPcb_GetInstance(), 4);
                StrPcb_ClearStatusBits(StrPcb_GetInstance(), 8);
            }
        } else if (!(lbl_806D13B0 & 1)) {
            StrPcb_SetStatusBits(StrPcb_GetInstance(), 4, 0);
            StrPcb_SetStatusBits(StrPcb_GetInstance(), 8, 0);
        } else {
            StrPcb_ClearStatusBits(StrPcb_GetInstance(), 4);
            StrPcb_ClearStatusBits(StrPcb_GetInstance(), 8);
        }
    }
    if (!lbl_806D13A1) lbl_806D13A1 = 1;
    if (self->demoCamera) {
        Object_SetByte10_Return1(self->scene, 0);
        TaBookend *book = TaMode_GetDemoCameraBookend();
        if (book) {
            Vec direction;
            Vec3_Subtract(&book->eye, &book->target, &direction);
            Vec3_Normalize(&direction, &direction);
            direction.x = 1000.0f * direction.x + book->target.x;
            direction.y = 100.0f + (1000.0f * direction.y + book->target.y);
            direction.z = 1000.0f * direction.z + book->target.z;
            CObj_LoadIntoGX(self->scene, &direction);
            CObj_ApplyViewport(self->scene, &book->target);
        }
        void *camera = g_raceCamera;
        SceneRender_SetViewportRect(camera,
            CarObject_GetTransformMatrix(g_carObjects[0])[12],
            CarObject_GetTransformMatrix(g_carObjects[0])[13],
            CarObject_GetTransformMatrix(g_carObjects[0])[14],
            CarObject_GetTransformMatrix(g_carObjects[0])[8],
            CarObject_GetTransformMatrix(g_carObjects[0])[9],
            CarObject_GetTransformMatrix(g_carObjects[0])[10]);
    } else KartItem_UpdateShadowBillboardAndViewport(g_carObjects[0], self->scene, 0);
    Fog_UpdateFromCourseScene3D();
    PathManager_UpdateAll(lbl_806D13A4);
    LakituStart_UpdateCountdown(self->lakitu);
    Jyugemu_Flag_Tick(self->jyugemuFlag);
    Jyugemu_ReverseFlag_Tick(self->jyugemuReverse);
    LapBannerScene_UpdateAndDriveAnim(self->lapBanner);
    CourseEnvironment_UpdateAndCullZones_Timed(self->environment);
    CObj_LoadProjMatrix(self->scene, &lbl_805D2B28);
    CObj_ApplyScissor(self->scene, &lbl_805D2B34);
    ItemObjectManager_Update();
    VfxSlotMgr_Update(lbl_805D2B28, lbl_805D2B34);
    if (g_rendererGateFlag == 1 && IsRaceStarted() == 1 && !g_raceEnded && g_raceTimeRemaining > 0.0f) {
        g_raceTimeRemaining -= 0.016666668f;
        if (g_raceTimeRemaining <= 0.0f) {
            g_raceTimeRemaining = 0.0f;
            fn_80253BE4(self->hud);
            g_sceneTransitionTimer = 180;
            fn_8016C554(0);
        }
    }
    Tachometer_RenderDigits();
    HUD_SetCurrentLap(self->hud, g_currentLap);
    fn_80253FD8(self->hud, g_raceTimeRemaining);
    fn_80253EBC(self->hud, 100.0f * CarObject_CalcSpeedRatio(g_carObjects[0]));
    fn_80253EC0(self->hud, KartItem_GetCurrentSpeedWithBonus(g_carObjects[0]));
    fn_80253EC4(self->hud, g_currentLapTime);
    fn_80253F2C(self->hud, g_bestLapTime);
    HUD_SetRacePosition(self->hud, g_finalRacePosition);
    fn_80253E18(self->hud, CarObject_GetRenderObj(g_carObjects[0])->coins);
    TransitionEffect_Tick(Transition());
    if (!g_finalLapBannerShown && g_currentLap >= g_totalLaps) {
        g_finalLapBannerShown = 1;
        fn_80253DF0(self->hud);
    }
    if (0.0f != g_raceTimeRemaining && g_raceResultCode == -2) {
        if (g_currentLap >= g_totalLaps + 1) {
            if (g_finalLapCoinJumpEnabled == 1) CoinJumpFlasher_Toggle(g_carObjects[0]);
            KartItem_OnFallOffOrDeath(g_carObjects[0]);
            CoinJumpFlasher_SetArmed(g_carObjects[0], 0);
            g_finalRacePosition = ((TaRender *)g_playerRenderObj)->position;
            g_raceResultCode = -1;
            int rank = TaRecord_InsertResult(g_playerData, g_playerData[0x19b], g_playerData[0x19c], g_playerData[0x1b1], GetKartSlotCharId(lbl_806D13A8), g_totalRaceTime);
            Jyugemu_Flag_SetKartDriver(self->jyugemuFlag, CarObject_GetRenderObj(g_carObjects[0]));
            if (g_ccClass == 2) {
                if (lbl_806D13A0) {
                    if (g_finalRacePosition == 0) fn_801D670C(g_playerData);
                } else {
                    TaRecord (*reverse)[2] = battle->reverse;
                    int cup = g_cupId - 1;
                    int round = g_longRoundFlag;
                    TaRecord *record = &reverse[cup][round];
                    float time = g_totalRaceTime;
                    if (g_reverseRoundFlag == 0) {
                        TaRecord (*normal)[2] = battle->normal;
                        record = &normal[cup][round];
                    }
                    if (time < record->time) {
                        fn_801D676C(g_playerData);
                        PlayStats_IncTaBestRecord();
                    }
                }
            } else if (g_ccClass == 1 && rank < 3) fn_801D597C(g_playerData);
            void *stats = TitleStats();
            if (stats) {
                RankLog_SetRaceResult(stats, GetDisplayBufferIndex(), g_finalRacePosition, (int)g_raceTimeRemaining);
                TitleStats_CaptureRoundContext(stats, rank, g_totalRaceTime);
                TitleStats_FinalizeRace_PlayCountThenTitle(stats);
            }
            fn_80253D00(self->hud);
            Object_SetByte10_Return1(self->scene, 1);
            fn_8016C554(1);
            g_raceEnded = 1;
            g_lakituStartAnimDone = 0;
            ++self->finishFrames;
            lbl_806CF19C = g_totalRaceTime;
        } else if (g_lapChangePending) {
            if (g_finalLapBannerShown) {
                fn_8016C598();
                LapBannerScene_TriggerBannerAnim(self->lapBanner);
            } else fn_8016C5CC();
            void *stats = TitleStats();
            if (stats) TitleTracker_ResetPerRound(stats, GetDisplayBufferIndex(), g_currentLap - 1);
            g_lapChangePending = 0;
        }
    } else if (self->finishFrames != 0) {
        if (++self->finishFrames > 300) self->demoCamera = 1;
        if (fn_80253C40(self->hud)) {
            SetSyncTarget(0x2d);
            return 13;
        }
    }
    HUD_FrameUpdate(self->hud);
    clItemBoxManager_Update(ItemBoxMgr());
    if (g_weatherSystem) fn_8016B32C(g_weatherSystem);
    if (!lbl_806D0051 && pad->Pressed(0x400) == 1) return 2;
    return -2;
}
