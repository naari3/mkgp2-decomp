/* Time-attack update, 0x800A2B90..0x800A38F8; retained NonMatching. */
#include "game/TaMode_FrameUpdate_private.h"


extern "C" {
extern char lbl_80321D7C[];
extern char lbl_80321D8C[];
extern char lbl_80321D9C[];
extern char lbl_80321DAC[];
extern char lbl_80321DBC[];
extern char lbl_80321DCC[];
extern char lbl_80321DDC[];
extern char lbl_80321DEC[];
extern char lbl_80321DFC[];
extern char lbl_80321E0C[];
extern char lbl_80321E1C[];
extern char lbl_80321E2C[];
extern char lbl_80321E3C[];
extern char lbl_80321E4C[];
extern char lbl_80321E5C[];
extern char lbl_80321E6C[];
extern char lbl_80321E7C[];
extern char lbl_80321E90[];
extern char lbl_80321EA0[];
extern char lbl_80321EB4[];
extern char lbl_80321EC4[];
extern char lbl_80321ED8[];
extern char lbl_80321EE8[];
extern char lbl_80321EFC[];
extern char lbl_80321F0C[];
extern char lbl_80321F20[];
extern char lbl_80321F30[];
extern char lbl_80321F44[];
extern char lbl_80321F54[];
extern char lbl_80321F68[];
extern char lbl_80321F78[];
extern char lbl_80321F8C[];
}

/* Shared BATTLE prefix, followed by the time-attack record tables. */
struct TaRaceParams { unsigned char laps; float timeLimit, lapBonus; };
struct TaBattlePrefix { TaRaceParams params[48]; TaRecord records[16]; };
extern "C" TaBattlePrefix BATTLE = {
    {
        { 6, 120.0f, 15.0f },
        { 4, 120.0f, 20.0f },
        { 6, 120.0f, 15.0f },
        { 4, 120.0f, 20.0f },
        { 9, 90.0f, 15.0f },
        { 6, 90.0f, 20.0f },
        { 8, 120.0f, 10.0f },
        { 4, 120.0f, 20.0f },
        { 8, 120.0f, 10.0f },
        { 4, 120.0f, 20.0f },
        { 9, 90.0f, 10.0f },
        { 6, 90.0f, 20.0f },
        { 4, 120.0f, 20.0f },
        { 4, 120.0f, 30.0f },
        { 4, 120.0f, 20.0f },
        { 4, 120.0f, 30.0f },
        { 6, 90.0f, 20.0f },
        { 5, 90.0f, 30.0f },
        { 3, 120.0f, 40.0f },
        { 3, 120.0f, 50.0f },
        { 3, 120.0f, 40.0f },
        { 3, 120.0f, 50.0f },
        { 4, 100.0f, 40.0f },
        { 4, 100.0f, 50.0f },
        { 4, 120.0f, 30.0f },
        { 4, 120.0f, 35.0f },
        { 4, 120.0f, 30.0f },
        { 4, 120.0f, 35.0f },
        { 5, 100.0f, 30.0f },
        { 5, 100.0f, 35.0f },
        { 2, 120.0f, 90.0f },
        { 2, 120.0f, 100.0f },
        { 2, 120.0f, 90.0f },
        { 2, 120.0f, 100.0f },
        { 3, 100.0f, 90.0f },
        { 3, 100.0f, 100.0f },
        { 3, 120.0f, 90.0f },
        { 2, 150.0f, 100.0f },
        { 3, 120.0f, 90.0f },
        { 2, 150.0f, 100.0f },
        { 4, 100.0f, 90.0f },
        { 3, 150.0f, 100.0f },
        { 4, 120.0f, 30.0f },
        { 4, 120.0f, 30.0f },
        { 4, 120.0f, 30.0f },
        { 4, 120.0f, 30.0f },
        { 5, 100.0f, 30.0f },
        { 5, 100.0f, 30.0f },
    },
    {
        { 0, lbl_80321D7C, 7128, 117.0f },
        { 1, lbl_80321D8C, 7192, 118.0f },
        { 6, lbl_80321D9C, 6653, 111.0f },
        { 6, lbl_80321DAC, 6976, 120.0f },
        { 2, lbl_80321DBC, 7052, 119.0f },
        { 2, lbl_80321DCC, 8605, 144.0f },
        { 8, lbl_80321DDC, 7793, 127.0f },
        { 8, lbl_80321DEC, 8983, 150.0f },
        { 4, lbl_80321DFC, 7730, 130.0f },
        { 4, lbl_80321E0C, 7086, 119.0f },
        { 3, lbl_80321E1C, 8575, 140.0f },
        { 10, lbl_80321E2C, 8784, 147.0f },
        { 3, lbl_80321E3C, 8575, 140.0f },
        { 10, lbl_80321E2C, 8784, 147.0f },
        { 3, lbl_80321E1C, 8575, 140.0f },
        { 10, lbl_80321E2C, 8784, 147.0f },
    }
};

static TaRecord taNormalRecords[16][2] = {
    { { 0, lbl_80321D7C, 7443, 122.0999984741211f }, { 1, lbl_80321D8C, 7714, 126.5f } },
    { { 10, lbl_80321D9C, 6472, 105.9000015258789f }, { 8, lbl_80321DAC, 7686, 126.0999984741211f } },
    { { 2, lbl_80321DBC, 7847, 128.6999969482422f }, { 12, lbl_80321DCC, 7876, 129.1999969482422f } },
    { { 8, lbl_80321DDC, 7373, 120.80000305175781f }, { 9, lbl_80321DEC, 8542, 140.3000030517578f } },
    { { 7, lbl_80321DFC, 7400, 121.30000305175781f }, { 3, lbl_80321E0C, 8932, 146.8000030517578f } },
    { { 11, lbl_80321E1C, 9052, 148.8000030517578f }, { 5, lbl_80321E2C, 9548, 154.10000610351562f } },
    { { 4, lbl_80321E3C, 7528, 123.4000015258789f }, { 2, lbl_80321E4C, 8170, 132.0f } },
    { { 0, lbl_80321E5C, 7746, 127.0999984741211f }, { 4, lbl_80321E6C, 7580, 125.30000305175781f } },
    { { 0, lbl_80321E7C, 7146, 117.5f }, { 1, lbl_80321E90, 7316, 118.5f } },
    { { 6, lbl_80321EA0, 6748, 112.0f }, { 6, lbl_80321EB4, 7067, 119.5f } },
    { { 2, lbl_80321EC4, 7143, 118.5f }, { 2, lbl_80321ED8, 8652, 142.0f } },
    { { 8, lbl_80321EE8, 7727, 127.0f }, { 8, lbl_80321EFC, 9021, 152.0f } },
    { { 4, lbl_80321F0C, 7880, 130.5f }, { 4, lbl_80321F20, 7216, 118.5f } },
    { { 7, lbl_80321F30, 8577, 138.5f }, { 5, lbl_80321F44, 8829, 146.5f } },
    { { 7, lbl_80321F30, 8577, 138.5f }, { 5, lbl_80321F44, 8829, 146.5f } },
    { { 7, lbl_80321F30, 8577, 138.5f }, { 5, lbl_80321F44, 8829, 146.5f } },
};

static TaRecord taReverseRecords[8][2] = {
    { { 6, lbl_80321E7C, 7503, 123.0999984741211f }, { 1, lbl_80321E90, 7627, 125.0999984741211f } },
    { { 7, lbl_80321EA0, 6487, 106.0999984741211f }, { 12, lbl_80321EB4, 7626, 125.0999984741211f } },
    { { 6, lbl_80321EC4, 7929, 130.10000610351562f }, { 5, lbl_80321ED8, 7818, 131.3000030517578f } },
    { { 3, lbl_80321EE8, 7526, 123.4000015258789f }, { 10, lbl_80321EFC, 8630, 141.8000030517578f } },
    { { 10, lbl_80321F0C, 7372, 120.80000305175781f }, { 12, lbl_80321F20, 8836, 145.1999969482422f } },
    { { 9, lbl_80321F30, 9018, 148.1999969482422f }, { 7, lbl_80321F44, 9888, 162.6999969482422f } },
    { { 2, lbl_80321F54, 7558, 123.9000015258789f }, { 4, lbl_80321F68, 8199, 134.60000610351562f } },
    { { 11, lbl_80321F78, 7708, 126.4000015258789f }, { 0, lbl_80321F8C, 7687, 126.0999984741211f } },
};

static unsigned int taMemberFunction[3] = { 0, 16, 0 };

static inline TaRecord *SelectTaRecord(int round, int reversed, int cup)
{
    TaRecord *record = &taReverseRecords[cup - 1][round];
    if (!reversed) record = &taNormalRecords[cup - 1][round];
    return record;
}

#pragma push
#pragma opt_propagation off
extern "C" int TaMode_FrameUpdate(RaceScene *self)
{
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
    if (g_taSound) fn_8023E324(g_taSound, __ptmf_test(taMemberFunction) != 0);
    if (g_raceEnded != 1) {
        long long now = OSGetTime();
        steer = QuantizeInput(pad->Steer());
        accel = QuantizeInput(pad->Brake());
        brake = accel;
        if (g_ccClass != 2) {
            if (!IsRaceStarted()) {
                TaMode_FrameUpdate_bss_806D13C4 = (unsigned int)now;
                TaMode_FrameUpdate_bss_806D13C0 = (unsigned int)(now >> 32);
            } else if (steer < 0.1f && accel < 0.1f) {
                if (!TaMode_FrameUpdate_bss_806D13B8) {
                    long long prev = ((long long)TaMode_FrameUpdate_bss_806D13C0 << 32) | TaMode_FrameUpdate_bss_806D13C4;
                    long long ms = (now - prev) / ((*(unsigned int *)0x800000f8 / 4) / 1000);
                    if ((float)ms / 1000.0f >= 4.0f) TaMode_FrameUpdate_bss_806D13B8 = 1;
                }
                if (TaMode_FrameUpdate_bss_806D13B8) steer = 1.0f;
            } else {
                TaMode_FrameUpdate_bss_806D13C4 = (unsigned int)now;
                TaMode_FrameUpdate_bss_806D13B8 = 0;
                TaMode_FrameUpdate_bss_806D13C0 = (unsigned int)(now >> 32);
            }
        }
        accel = QuantizeInput(pad->Accel());
        started = IsRaceStarted();
        if (IsRaceStarted() == 1 && TaMode_FrameUpdate_bss_806D13AC > 0) {
            TaRender *render = CarObject_GetRenderObj(g_carObjects[0]);
            if (KartMovement_GetCurrentItemId(render) != -1) {
                if (!KartItem_GetByte_f4(g_carObjects[0])) {
                    pad->Held(0xe3ff);
                    if (Input_IsItemButtonPressed() && RenderObj_UseItem(render, 0, 0)) {
                        void *stats = TitleStats();
                        if (stats) RankLog_OnPlayerVictory(stats, GetDisplayBufferIndex(), 0);
                        CarObject_ApplyDriftBoost(g_carObjects[0], 5, 3.0f);
                        --TaMode_FrameUpdate_bss_806D13AC;
                        if (g_taSound) {
                            if (TaMode_FrameUpdate_bss_806D13AC == 2) fn_8023E1E4(g_taSound, 0x116, 0);
                            if (TaMode_FrameUpdate_bss_806D13AC == 1) fn_8023E1E4(g_taSound, 0x17, 0);
                            if (TaMode_FrameUpdate_bss_806D13AC == 0) fn_8023E1E4(g_taSound, -1, 0);
                        }
                        TaMode_FrameUpdate_bss_806D13B0 = 30;
                    }
                }
            } else KartMovement_EquipItem(render, 0x17);
        }
    } else {
        accel = CalcSoundDirection(CarObject_GetRenderObj(g_carObjects[0]), TaMode_FrameUpdate_bss_806D13A4, &steer, 0);
        brake = 0.0f;
        started = 1;
    }
    CarObject_ApplyInput(g_carObjects[0], accel, steer, brake, started != 0);
    CarObject_FrameUpdate(g_carObjects[0], 0);
    if (!g_raceEnded && pad->Held(0x400) && GetCoinMilage(g_playerData) >= 4000)
        CoinJumpFlasher_Toggle(g_carObjects[0]);
    fn_8013A534();
    if (TaMode_FrameUpdate_bss_806D13A0) {
        coins = 0;
        if (TaMode_FrameUpdate_bss_806D1394 < TaMode_FrameUpdate_bss_806D138C) {
            accel = ((float *)TaMode_FrameUpdate_bss_806D1388)[TaMode_FrameUpdate_bss_806D1394 * 4];
            TaGhostFrame *frame = &TaMode_FrameUpdate_bss_806D1388[TaMode_FrameUpdate_bss_806D1394];
            steer = frame->steer;
            brake = frame->brake;
            started = frame->started;
            signed char item = frame->item;
            coins = frame->coins;
            ++TaMode_FrameUpdate_bss_806D1394;
            if (g_taGhostCar && TaMode_FrameUpdate_data_806CF198 > 0) {
                TaRender *render = CarObject_GetRenderObj(g_taGhostCar);
                if (KartMovement_GetCurrentItemId(render) != -1) {
                    if (item == 1) {
                        RenderObj_UseItem(render, 0, 0);
                        CarObject_ApplyDriftBoost(g_taGhostCar, 5, 3.0f);
                        --TaMode_FrameUpdate_data_806CF198;
                    }
                } else KartMovement_EquipItem(render, 0x17);
            }
        } else if (g_taGhostCar) {
            accel = CalcSoundDirection(CarObject_GetRenderObj(g_taGhostCar), TaMode_FrameUpdate_bss_806D13A4, &steer, TaMode_FrameUpdate_bss_806D139C);
            brake = 0.0f;
            started = IsRaceStarted();
        }
        if (g_taGhostCar) {
            if (IsRaceStarted() == 1) {
                void *bus = CarObject_GetRenderObj(g_taGhostCar)->itemBus;
                if (!CarObject_GetRenderObj(g_taGhostCar)->effectActive)
                    ItemEffectBus_ClearMask(bus, 0x8000000000ULL);
                else ItemEffectBus_OrMask(bus, 0x8000000000ULL);
            }
            CarObject_ApplyInput(g_taGhostCar, accel, steer, brake, started != 0);
            CarObject_FrameUpdate(g_taGhostCar, 0);
            TaRender *render = CarObject_GetRenderObj(g_taGhostCar);
            render->coins += coins;
        }
    }
    if (TaMode_FrameUpdate_bss_806D13B0 != 0) {
        if (--TaMode_FrameUpdate_bss_806D13B0 == 0) {
            if (TaMode_FrameUpdate_bss_806D13AC != 0) {
                StrPcb_SetStatusBits(StrPcb_GetInstance(), 4, 0);
                StrPcb_SetStatusBits(StrPcb_GetInstance(), 8, 0);
            } else {
                StrPcb_ClearStatusBits(StrPcb_GetInstance(), 4);
                StrPcb_ClearStatusBits(StrPcb_GetInstance(), 8);
            }
        } else if (!(TaMode_FrameUpdate_bss_806D13B0 & 1)) {
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
    PathManager_UpdateAll(TaMode_FrameUpdate_bss_806D13A4);
    LakituStart_UpdateCountdown(self->lakitu);
    Jyugemu_Flag_Tick(self->jyugemuFlag);
    Jyugemu_ReverseFlag_Tick(self->jyugemuReverse);
    LapBannerScene_UpdateAndDriveAnim(self->lapBanner);
    CourseEnvironment_UpdateAndCullZones_Timed(self->environment);
    CObj_LoadProjMatrix(self->scene, &TaMode_FrameUpdate_bss_805D2B28);
    CObj_ApplyScissor(self->scene, &TaMode_FrameUpdate_bss_805D2B34);
    ItemObjectManager_Update();
    VfxSlotMgr_Update(TaMode_FrameUpdate_bss_805D2B28, TaMode_FrameUpdate_bss_805D2B34);
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
            int rank = TaRecord_InsertResult(g_playerData, g_playerData[0x19b], g_playerData[0x19c], g_playerData[0x1b1], GetKartSlotCharId(TaMode_FrameUpdate_bss_806D13A8), g_totalRaceTime);
            Jyugemu_Flag_SetKartDriver(self->jyugemuFlag, CarObject_GetRenderObj(g_carObjects[0]));
            if (g_ccClass == 2) {
                if (TaMode_FrameUpdate_bss_806D13A0) {
                    if (g_finalRacePosition == 0) fn_801D670C(g_playerData);
                } else {
                    float time = g_totalRaceTime;
                    TaRecord *record = SelectTaRecord(g_longRoundFlag, g_reverseRoundFlag, g_cupId);
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
            TaMode_FrameUpdate_data_806CF19C = g_totalRaceTime;
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
#pragma pop

