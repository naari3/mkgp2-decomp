/* Time-attack mode: update (0x800A2B90), deleting dtor (0x800A38F8) and ctor (0x800A3C38).
 * One TU: it owns .rodata 0x80321980..0x80322120 and .data 0x8040EA58..0x8040F0E8. */
#include "game/TaMode_FrameUpdate_private.h"


extern "C" {
extern const char lbl_80321D7C[];
extern const char lbl_80321D8C[];
extern const char lbl_80321D9C[];
extern const char lbl_80321DAC[];
extern const char lbl_80321DBC[];
extern const char lbl_80321DCC[];
extern const char lbl_80321DDC[];
extern const char lbl_80321DEC[];
extern const char lbl_80321DFC[];
extern const char lbl_80321E0C[];
extern const char lbl_80321E1C[];
extern const char lbl_80321E2C[];
extern const char lbl_80321E3C[];
extern const char lbl_80321E4C[];
extern const char lbl_80321E5C[];
extern const char lbl_80321E6C[];
extern const char lbl_80321E7C[];
extern const char lbl_80321E90[];
extern const char lbl_80321EA0[];
extern const char lbl_80321EB4[];
extern const char lbl_80321EC4[];
extern const char lbl_80321ED8[];
extern const char lbl_80321EE8[];
extern const char lbl_80321EFC[];
extern const char lbl_80321F0C[];
extern const char lbl_80321F20[];
extern const char lbl_80321F30[];
extern const char lbl_80321F44[];
extern const char lbl_80321F54[];
extern const char lbl_80321F68[];
extern const char lbl_80321F78[];
extern const char lbl_80321F8C[];
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

/* ==== .rodata 0x80321980..0x80322120 ==== */
extern "C" const unsigned int TaMode_FrameUpdate_rodata_80321980[255] = {
    0x3F800000, 0x3F333333, 0x3F666666, 0x00000000, 0x00000000, 0x43FA0000,
    0x42855556, 0x447A0000, 0x42855556, 0x44FA0000, 0x42855556, 0x453B8000,
    0x42855556, 0x457A0000, 0x42855556, 0x459C4000, 0x42855556, 0x00000000,
    0x00000000, 0x43FA0000, 0x42855556, 0x447A0000, 0x42855556, 0x44FA0000,
    0x42855556, 0x453B8000, 0x42855556, 0x457A0000, 0x42855556, 0x459C4000,
    0x42855556, 0x00000000, 0x00000000, 0x43FA0000, 0x42855556, 0x447A0000,
    0x42855556, 0x44FA0000, 0x42855556, 0x453B8000, 0x42855556, 0x457A0000,
    0x42855556, 0x459C4000, 0x42855556, 0x00000000, 0x00000000, 0x43FA0000,
    0x42855556, 0x447A0000, 0x42855556, 0x44FA0000, 0x42855556, 0x453B8000,
    0x42855556, 0x457A0000, 0x42855556, 0x459C4000, 0x42855556, 0x00000000,
    0x00000000, 0x43FA0000, 0x42855556, 0x447A0000, 0x42855556, 0x44FA0000,
    0x42855556, 0x453B8000, 0x42855556, 0x457A0000, 0x42855556, 0x459C4000,
    0x42855556, 0x00000000, 0x00000000, 0x43FA0000, 0x42855556, 0x447A0000,
    0x42855556, 0x44FA0000, 0x42855556, 0x453B8000, 0x42855556, 0x457A0000,
    0x42855556, 0x459C4000, 0x42855556, 0x00000000, 0x00000000, 0x43FA0000,
    0x42855556, 0x447A0000, 0x42855556, 0x44FA0000, 0x42855556, 0x453B8000,
    0x42855556, 0x457A0000, 0x42855556, 0x459C4000, 0x42855556, 0x00000000,
    0x00000000, 0x43FA0000, 0x42855556, 0x447A0000, 0x42855556, 0x44FA0000,
    0x42855556, 0x453B8000, 0x42855556, 0x457A0000, 0x42855556, 0x459C4000,
    0x42855556, 0x00000000, 0x00000000, 0x43FA0000, 0x42855556, 0x447A0000,
    0x42855556, 0x44FA0000, 0x42855556, 0x453B8000, 0x42855556, 0x457A0000,
    0x42855556, 0x459C4000, 0x42855556, 0x00000000, 0x00000000, 0x43FA0000,
    0x42855556, 0x447A0000, 0x42855556, 0x44FA0000, 0x42855556, 0x453B8000,
    0x42855556, 0x457A0000, 0x42855556, 0x459C4000, 0x42855556, 0x00000000,
    0x00000000, 0x43FA0000, 0x42855556, 0x447A0000, 0x42855556, 0x44FA0000,
    0x42855556, 0x453B8000, 0x42855556, 0x457A0000, 0x42855556, 0x459C4000,
    0x42855556, 0x00000000, 0x00000000, 0x43FA0000, 0x42855556, 0x447A0000,
    0x42855556, 0x44FA0000, 0x42855556, 0x453B8000, 0x42855556, 0x457A0000,
    0x42855556, 0x459C4000, 0x42855556, 0x00000000, 0x00000000, 0x43FA0000,
    0x42A6AAAB, 0x447A0000, 0x42A6AAAB, 0x44FA0000, 0x42A6AAAB, 0x453B8000,
    0x42A6AAAB, 0x457A0000, 0x42A6AAAB, 0x459C4000, 0x42A6AAAB, 0x00000000,
    0x00000000, 0x43FA0000, 0x42A6AAAB, 0x447A0000, 0x42A6AAAB, 0x44FA0000,
    0x42A6AAAB, 0x453B8000, 0x42A6AAAB, 0x457A0000, 0x42A6AAAB, 0x459C4000,
    0x42A6AAAB, 0x00000000, 0x00000000, 0x43FA0000, 0x42A6AAAB, 0x447A0000,
    0x42A6AAAB, 0x44FA0000, 0x42A6AAAB, 0x453B8000, 0x42A6AAAB, 0x457A0000,
    0x42A6AAAB, 0x459C4000, 0x42A6AAAB, 0x00000000, 0x00000000, 0x43FA0000,
    0x42A6AAAB, 0x447A0000, 0x42A6AAAB, 0x44FA0000, 0x42A6AAAB, 0x453B8000,
    0x42A6AAAB, 0x457A0000, 0x42A6AAAB, 0x459C4000, 0x42A6AAAB, 0x00000000,
    0x00000000, 0x43FA0000, 0x42A6AAAB, 0x447A0000, 0x42A6AAAB, 0x44FA0000,
    0x42A6AAAB, 0x453B8000, 0x42A6AAAB, 0x457A0000, 0x42A6AAAB, 0x459C4000,
    0x42A6AAAB, 0x00000000, 0x00000000, 0x43FA0000, 0x42A6AAAB, 0x447A0000,
    0x42A6AAAB, 0x44FA0000, 0x42A6AAAB, 0x453B8000, 0x42A6AAAB, 0x457A0000,
    0x42A6AAAB, 0x459C4000, 0x42A6AAAB,
};
extern "C" const char lbl_80321D7C[16] = "ta_mr_short.bin";
extern "C" const char lbl_80321D8C[16] = "ta_mr_long.bin";
extern "C" const char lbl_80321D9C[16] = "ta_dk_short.bin";
extern "C" const char lbl_80321DAC[16] = "ta_dk_long.bin";
extern "C" const char lbl_80321DBC[16] = "ta_wc_short.bin";
extern "C" const char lbl_80321DCC[16] = "ta_wc_long.bin";
extern "C" const char lbl_80321DDC[16] = "ta_pc_short.bin";
extern "C" const char lbl_80321DEC[16] = "ta_pc_long.bin";
extern "C" const char lbl_80321DFC[16] = "ta_kp_short.bin";
extern "C" const char lbl_80321E0C[16] = "ta_kp_long.bin";
extern "C" const char lbl_80321E1C[16] = "ta_rb_short.bin";
extern "C" const char lbl_80321E2C[16] = "ta_rb_long.bin";
extern "C" const char lbl_80321E3C[16] = "ta_yi_short.bin";
extern "C" const char lbl_80321E4C[16] = "ta_yi_long.bin";
extern "C" const char lbl_80321E5C[16] = "ta_dn_short.bin";
extern "C" const char lbl_80321E6C[16] = "ta_dn_long.bin";
extern "C" const char lbl_80321E7C[20] = "ta_mr_shortR.bin";
extern "C" const char lbl_80321E90[16] = "ta_mr_longR.bin";
extern "C" const char lbl_80321EA0[20] = "ta_dk_shortR.bin";
extern "C" const char lbl_80321EB4[16] = "ta_dk_longR.bin";
extern "C" const char lbl_80321EC4[20] = "ta_wc_shortR.bin";
extern "C" const char lbl_80321ED8[16] = "ta_wc_longR.bin";
extern "C" const char lbl_80321EE8[20] = "ta_pc_shortR.bin";
extern "C" const char lbl_80321EFC[16] = "ta_pc_longR.bin";
extern "C" const char lbl_80321F0C[20] = "ta_kp_shortR.bin";
extern "C" const char lbl_80321F20[16] = "ta_kp_longR.bin";
extern "C" const char lbl_80321F30[20] = "ta_rb_shortR.bin";
extern "C" const char lbl_80321F44[16] = "ta_rb_longR.bin";
extern "C" const char lbl_80321F54[20] = "ta_yi_shortR.bin";
extern "C" const char lbl_80321F68[16] = "ta_yi_longR.bin";
extern "C" const char lbl_80321F78[20] = "ta_dn_shortR.bin";
extern "C" const char lbl_80321F8C[16] = "ta_dn_longR.bin";
extern "C" const unsigned int lbl_80321F9C[5] = {
    0x636C4761, 0x6D655469, 0x6D654174, 0x7461636B, 0x00000000,
};
extern "C" const unsigned int lbl_80321FB0[92] = {
    0x636C4761, 0x6D65576F, 0x726C6400, 0x4F4B2067, 0x686F7374, 0x21000000,
    0x63616D65, 0x7261206A, 0x7567656D, 0x75207368, 0x61646F77, 0x20667265,
    0x65210000, 0x6D617020, 0x66726565, 0x21000000, 0x65666665, 0x63742061,
    0x75746F72, 0x756E206C, 0x69676874, 0x20667265, 0x65210000, 0x4F4B2063,
    0x6C47616D, 0x653A3A73, 0x65747469, 0x6E672829, 0x00000000, 0x4F4B204F,
    0x626A6563, 0x74576F72, 0x6B496E69, 0x74202620, 0x45666665, 0x6374576F,
    0x726B496E, 0x69740000, 0x4F4B2073, 0x6861646F, 0x77210000, 0x4F4B2050,
    0x6C617965, 0x72206361, 0x72000000, 0x4F4B2067, 0x686F7374, 0x21210000,
    0x6A797567, 0x656D755F, 0x73746172, 0x742E6461, 0x74000000, 0x4F4B206A,
    0x7567656D, 0x75202620, 0x65746321, 0x21000000, 0x4F4B2073, 0x70726974,
    0x65206364, 0x69737028, 0x29000000, 0x4F4B2054, 0x494D4520, 0x73657474,
    0x696E6721, 0x00000000, 0x4F4B2045, 0x4E454D59, 0x20497465, 0x6D204D6F,
    0x64656C20, 0x6C6F6164, 0x21000000, 0x4F4B2065, 0x66666563, 0x74206C6F,
    0x61640000, 0x2D2D2D52, 0x41434520, 0x2D2D2D2D, 0x2D2D2D2D, 0x2D2D2D2D,
    0x2D2D2D2D, 0x2D2D2D2D, 0x2D2D2D2D, 0x2D2D2D2D, 0x2D2D2D2D, 0x2D2D2D2D,
    0x2D2D2D2D, 0x0A000000,
};

/* RTTI base record and the TaMode vtable (0x8040F0A4..0x8040F0C4). */
struct TaDtorScene;
extern "C" {
extern char GameModeBase_RTTI_806CF1A0[];
extern char TaMode_RTTI_806CF1A8[];
extern void *TaMode_FrameUpdate_bss_806D13C8;
void BtMode_RenderFrame(void);
TaDtorScene *TaMode_Dtor(TaDtorScene *self, short flag);
}
extern "C" void *sdata_806CEFE0_data_8040F0A4[3] = {GameModeBase_RTTI_806CF1A0, 0, 0};
extern "C" void *TaMode_vtable_8040F0B0[5] = {TaMode_RTTI_806CF1A8, 0, (void *)TaMode_Dtor, (void *)TaMode_FrameUpdate, (void *)BtMode_RenderFrame};

/* ==== TaMode_Dtor (0x800A38F8) ==== */
#define g_carObjects (*(TaDtorCar *(*)[4])&g_carObjects)
#define g_taGhostCar (*(TaDtorCar **)&g_taGhostCar)
#define lbl_806D10D0 (*(Deletable **)&lbl_806D10D0)
#define lbl_806D109C (*(Deletable **)&lbl_806D109C)
#define TaMode_FrameUpdate_bss_806D13C8 (*(HsdRefObj **)&TaMode_FrameUpdate_bss_806D13C8)
/* TaMode_Dtor (0x800A38F8): deleting destructor of the time-attack mode
 * scene; the time-attack counterpart of RaceScene_Dtor (ghost kart, ghost
 * buffer and TA HUD instead of the AI and item HUD). */

struct Deletable {
    virtual ~Deletable();
};

struct TaDtorCar {
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

struct TaDtorScene {
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
extern char GameModeBase_vtable_8040E76C[];
extern void *g_weatherSystem;
extern void *g_itemSelects[];
extern void *TaMode_FrameUpdate_bss_806D13A4;
extern void *TaMode_FrameUpdate_bss_806D1390;
extern void *g_taSound;
extern Deletable *g_courseData;
extern void *g_raceCamera;

void fn_801B6B94(void);
void fn_8016C634(void *p, int flag);
void SetActiveCamera(int index, struct RaceCamera *cam);
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
void MemoryManager_Free(void *p);
void fn_8023E808(void *p, int flag);
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

#pragma push
#pragma use_lmw_stmw off
extern "C" TaDtorScene *TaMode_Dtor(TaDtorScene *self, short flag)
{
    const char *log = (const char *)TaMode_FrameUpdate_rodata_80321980;

    if (self != 0) {
        self->vtable = TaMode_vtable_8040F0B0;
        if (g_weatherSystem != 0) {
            fn_8016C634(g_weatherSystem, 1);
            g_weatherSystem = 0;
        }
        SetActiveCamera(0, 0);
        if (g_taGhostCar != 0) {
            g_taGhostCar->Destroy(1);
        }
        MemoryManager_Free(TaMode_FrameUpdate_bss_806D1390);
        g_taGhostCar = 0;
        TaMode_FrameUpdate_bss_806D1390 = 0;
        ProcessSystemTick(log + 0x63C);
        Tachometer_Destroy();
        fn_80254134(self->hud, 1);
        delete self->camera;
        LakituStart_Dtor(self->lakitu, 1);
        Jyugemu_Flag_Dtor(self->jyugemuFlag, 1);
        Jyugemu_ReverseFlag_Dtor(self->jyugemuReverse, 1);
        LapBannerScene_Dtor(self->lapBanner, 1);
        PathParticipantArray_Dtor(TaMode_FrameUpdate_bss_806D13A4, 1);
        if (g_carObjects[0] != 0) {
            g_carObjects[0]->Destroy(1);
        }
        if (self->shadow != 0) {
            delete self->shadow;
        }
        ProcessSystemTick(log + 0x648);
        CourseEnvironment_Dtor(self->environment, 1);
        fn_8023E808(g_taSound, 1);
        ProcessSystemTick(log + 0x664);
        if (TaMode_FrameUpdate_bss_806D13C8 != 0) {
            HsdRef_Unref(TaMode_FrameUpdate_bss_806D13C8);
            TaMode_FrameUpdate_bss_806D13C8 = 0;
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
        TaMode_FrameUpdate_bss_806D13A4 = 0;
        self->camera = 0;
        self->environment = 0;
        g_taSound = 0;
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
        ProcessSystemTick(log + 0x670);
        SetResourceLoadingFlag(0);
        clRom_PurgeAll();
        SetCourseScene3D(0);
        if (self != 0) {
            self->vtable = GameModeBase_vtable_8040E76C;
        }
        if (flag > 0) {
            MemoryManager_TimedFree(self);
        }
    }
    return self;
}
#pragma pop
#undef g_carObjects
#undef g_taGhostCar
#undef lbl_806D10D0
#undef lbl_806D109C
#undef TaMode_FrameUpdate_bss_806D13C8

/* ==== TaMode_Init (0x800A3C38) ==== */
#include "game/TaModeInitPrivate.h"
#include "game/TaModeInitTablesPrivate.h"

static inline int CcClass_Get() { return g_ccClass; }
static inline int KartVariant_Get() { return g_kartVariant; }
static inline void Render_SetReady(void *p) { *(int *)((char *)p + 0x238) = 1; }

static inline int RegisterGhost(float *matrix, void *render) {
    return PathManager_RegisterCarObject(TaMode_FrameUpdate_bss_806D13A4, matrix + 12, matrix + 13, matrix + 14, g_taGhostCar, render, 1);
}

TaMode::TaMode() {
    const char *log = (const char *)TaMode_FrameUpdate_rodata_80321980;
    const char *data = (const char *)&BATTLE;
    float startX, startY;
    HSD_RandSeedPtr = &TaMode_Init_bss_806D13CC;
    *HSD_RandSeedPtr = lbl_806D1110;
    g_gameMode = 1;
    SetSyncTarget(0x2a);
    g_isCommHost = 0;
    ItemUse_ResetAllKartUseSlots();
    RaceScene_ClearPlayerSlotPointers();
    RaceSlot_ResetAll();
    g_spawnedKartCount = 1;
    int character = g_characterId;
    lbl_806D1050 = 0;
    RaceSlot_InitSlot(0, GetDisplayBufferIndex(), character, 1, 0);
    g_finalLapCoinJumpEnabled = 0;
    ProcessSystemTick(log + 0x68c);
    SetResourceLoadingFlag(0);
    DMAChannelManager_Init();
    TransitionEffect_GetOrCreate();
    SoundChannels_ClearAll();
    ItemObjectManager_Init();
    CourseObjectManager_Init();
    ProcessSystemTick(log + 0x6a4);
    environment = new EnvironmentMgr;
    CourseData_GetOrCreate(g_cupId, g_longRoundFlag, g_reverseRoundFlag);
    TaMode_FrameUpdate_bss_806D13C8 = HSD_LObjLoadDesc(GetCourseDataPtr());
    camera = new RaceCamera(lbl_806D483C, 0x200, lbl_806D4838, 0x200, TaMode_FrameUpdate_bss_806D13C8);
    SetActiveCamera(0, camera);
    g_raceCamera = camera;
    ProcessSystemTick(log + 0x6c8);
    RankingTable_Init(GetRaceContextPtr());
    SoundDriver_GetOrCreate(0);
    CoinSystem_Init(0, 2);
    TaMode_FrameUpdate_bss_806D13A8 = GetKartStartSlot(GetDisplayBufferIndex());
    g_kartStartSlot = TaMode_FrameUpdate_bss_806D13A8;
    GetStartPosition(TaMode_FrameUpdate_bss_806D13A8, &startX, 0, &startY);
    g_carObjects[0] = new CarObject(GetDisplayBufferIndex(), GetKartSlotCharId(TaMode_FrameUpdate_bss_806D13A8), startX, startY, GetCourseStartYaw(), CcClass_Get(), KartVariant_Get(), 1, -1, 0, 0);
    Render_SetReady(CarObject_GetRenderObj(g_carObjects[0]));
    KartItem_SetShortArray34a(CarObject_GetRenderObj(g_carObjects[0]), g_playerData);
    if (GetVBlankFlag() && !g_playerData[0x19d]) KartItem_SetField358(CarObject_GetRenderObj(g_carObjects[0]), 0);
    g_playerRenderObj = CarObject_GetRenderObj(g_carObjects[0]);
    ProcessSystemTick(log + 0x6d4);
    SetPlayerCarObject(g_carObjects[0]);
    {
    float *matrix = CarObject_GetTransformMatrix(g_carObjects[0]);
    TaMode_FrameUpdate_bss_806D13A4 = new PathManager(CourseData_GetDefaultPathKey_Safe(), g_carObjects[0], CarObject_GetRenderObj(g_carObjects[0]), matrix + 12, matrix + 13, matrix + 14);
    }
    int cup = g_cupId - 1;
    int reverse = g_reverseRoundFlag;
    int cc = g_ccClass;
    int round = g_longRoundFlag;
    int index = round + (cup * 4 + reverse * 2);
    if (cc == 2) {
        if (g_playerData[0x48 + index] == 1) TaMode_FrameUpdate_bss_806D13A0 = 1;
        else TaMode_FrameUpdate_bss_806D13A0 = 0;
    }
    TaMode_FrameUpdate_bss_806D1394 = 0;
    if (cc == 2 && TaMode_FrameUpdate_bss_806D13A0) {
        const TaGhostSource *ghost = (const TaGhostSource *)(data + 0x540 + cup * 32 + round * 16);
        if (!reverse) ghost = (const TaGhostSource *)(data + 0x340 + cup * 32 + round * 16);
        g_taGhostCar = new CarObject(4, ghost->character, startX, startY, GetCourseStartYaw(), 2, 3, 0, -1, 0, 0);
        float *matrix = CarObject_GetTransformMatrix(g_taGhostCar);
        TaMode_FrameUpdate_bss_806D139C = RegisterGhost(matrix, CarObject_GetRenderObj(g_taGhostCar));
        TaMode_FrameUpdate_data_806CF198 = 3;
        TaMode_FrameUpdate_bss_806D1390 = DVDFile_LoadSync(ghost->file);
        TaMode_FrameUpdate_bss_806D1388 = TaMode_FrameUpdate_bss_806D1390;
        TaMode_FrameUpdate_bss_806D138C = ghost->size;
        if (g_taGhostCar) {
            KartMovement_EquipItem(CarObject_GetRenderObj(g_taGhostCar), 0x17);
            ItemEffectBus_OrMask(*(void **)((char *)CarObject_GetRenderObj(g_taGhostCar) + 0x304), 0x8000000000ULL);
        }
    } else { g_taGhostCar = 0; TaMode_FrameUpdate_bss_806D1390 = 0; }
    ProcessSystemTick(log + 0x6e4);
    lakitu = new LakituStart(log + 0x6f0, TaMode_FrameUpdate_bss_806D13A8, lbl_806D4830, lbl_806D4830, lbl_806D4830);
    scene = new Scene3D(*GetKartModelNameEntry(GetKartSlotCharId(TaMode_FrameUpdate_bss_806D13A8), -1));
    jyugemuFlag = new JyugemuFlag(scene);
    jyugemuReverse = new JyugemuReverseFlag(CarObject_GetRenderObj(g_carObjects[0]));
    lapBanner = new FinalLapBanner(CarObject_GetRenderObj(g_carObjects[0]));
    ProcessSystemTick(log + 0x704);
    float cameraX, cameraY;
    Scene3D_GetCameraPos(scene, &cameraX, &cameraY);
    cameraX += lbl_806D4860;
    Scene3D_SetupProjection(scene, cameraX, cameraY);
    Tachometer_Init();
    hud = new RaceHud(TaMode_FrameUpdate_bss_806D13A4);
    g_raceHud = hud;
    HUD_RegisterOverlay(hud, 6, 0);
    HUD_RegisterOverlay(hud, 3, 0);
    HUD_RegisterOverlay(hud, 5, 0);
    HUD_RegisterOverlay(hud, 1, 0);
    HUD_RegisterOverlay(hud, 2, 0);
    HUD_RegisterOverlay(hud, 10, 0);
    HUD_RegisterOverlay(hud, 11, 0);
    HUD_RegisterOverlay(hud, 7, 0);
    HUD_RegisterOverlay(hud, 15, 0);
    HUD_RegisterOverlay(hud, 16, 0);
    HUD_RegisterOverlay(hud, 14, 0);
    if (IsTimerModeEnabled() == 1) HUD_RegisterOverlay(hud, 4, 0);
    HUD_RegisterOverlay(hud, 13, 0);
    fn_80253EB8(hud, lbl_806D484C);
    HUD_RegisterOverlay(hud, 8, 0);
    HUD_RegisterOverlay(hud, 9, 0);
    HUD_RegisterOverlay(hud, 21, 0);
    ProcessSystemTick(log + 0x718);
    g_sceneTransitionTimer = -1;
    g_lakituStartAnimDone = 0;
    SetCourseScene3D(scene);
    g_raceEnded = 0;
    ai = 0;
    flag38 = 0;
    /* Cups are one-based; one cup contains six (class, round) records. */
    const RaceParams *params = &BATTLE.cups[g_cupId][g_ccClass][g_longRoundFlag];
    g_bestLapTime = lbl_806D4830;
    g_currentLapTime = lbl_806D4830;
    g_totalRaceTime = lbl_806D4830;
    lbl_806D13A1 = 0;
    g_finalRacePosition = 0;
    int laps = params[-6].laps;
    float bonus, time;
    time = params[-6].timeLimit;
    bonus = params[-6].lapBonus;
    g_currentLap = 1;
    g_raceResultCode = -2;
    g_finalLapBannerShown = 0;
    g_lapChangePending = 0;
    g_totalLaps = laps;
    g_raceTimeRemaining = time;
    g_lapBonusTimeDelta = bonus;
    TaMode_FrameUpdate_data_806CF19C = lbl_806D4834;
    HUD_SetTotalLaps(hud, g_totalLaps);
    ProcessSystemTick(log + 0x72c);
    CourseBgm_Load();
    if (!g_weatherSystem) g_weatherSystem = new WeatherSystem(1);
    TaMode_FrameUpdate_bss_806D13B0 = 0;
    TaMode_FrameUpdate_bss_806D13AC = 3;
    PreloadItemResources(0x17);
    KartMovement_EquipItem(CarObject_GetRenderObj(g_carObjects[0]), 0x17);
    g_taSound = new TaSound(0);
    if (g_taSound) fn_8023E1E4(g_taSound, 0x117, 0);
    StrPcb_SetStatusBits(StrPcb_GetInstance(), 4, 0);
    StrPcb_SetStatusBits(StrPcb_GetInstance(), 8, 0);
    ProcessSystemTick(log + 0x740);
    SetResourceLoadingFlag(1);
    g_raceFrameCounterLo2digits = 0;
    switch (g_cupId) {
    case 1: PreloadEffectResources(1); break;
    case 2: PreloadEffectResources(2); break;
    case 3: PreloadEffectResources(3); break;
    case 4: PreloadEffectResources(4); break;
    case 5: PreloadEffectResources(5); break;
    case 6: PreloadEffectResources(6); break;
    case 7: PreloadEffectResources(7); break;
    case 8: PreloadEffectResources(8); break;
    }
    PreloadEffectResources(9);
    PreloadEffectResources(10);
    ProcessSystemTick(log + 0x75c);
    TaMode_FrameUpdate_bss_806D13B8 = 0;
    long long timestamp = OSGetTime();
    TaMode_FrameUpdate_bss_806D13C0 = (unsigned long)(timestamp >> 32);
    TaMode_FrameUpdate_bss_806D13C4 = (unsigned long)timestamp;
    SetSyncTarget(0x2c);
    PlayStats_IncTaPlay();
    DebugPrintf(log + 0x76c);
}
