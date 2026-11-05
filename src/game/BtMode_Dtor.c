#pragma cplusplus on
#include "game/BtMode_DtorPrivate.h"
extern "C" {
extern void *g_weatherSystem;
extern int g_currentSceneState, lbl_806D129C;
extern void *lbl_806D12F4;
extern RefObject162 *lbl_806D12F8;
extern char lbl_80320960[];
extern int lbl_8040E734[], lbl_8040E76C[];
void fn_801B6B94();
void fn_8016C634(void *, int);
void fn_8020AF08(void *, int);
void fn_80254134(void *, int);

void Tachometer_Destroy();
void HitMessageOverlay_Destroy();





}
static inline void baseDtor(BtModeView *p) {
    if (p) p->vt = lbl_8040E76C;
}
#pragma use_lmw_stmw on
extern "C" BtModeView *BtMode_Dtor(BtModeView *self, short deleting) {
    const char *messages = lbl_80320960;
    if (self) {
        self->vt = lbl_8040E734;
        fn_801B6B94();
        lbl_806D129C = 0;
        if (g_currentSceneState != 0x2a) {
            if (g_weatherSystem) {
                fn_8016C634(g_weatherSystem, 1);
                g_weatherSystem = 0;
            }
            SetActiveCamera(0, 0);
            if (self->field34) {
                fn_8020AF08(self->field34, 1);
                self->field34 = 0;
            }
            ProcessSystemTick((int)messages + 0x4e4);
            AI_SystemDtor(self->ai, 1);
            fn_80208FE4(self->system, 1);
            ProcessSystemTick((int)messages + 0x4f4);
            for (int i=0; i<4; ++i) {
                if (g_itemSelects[i]) ItemSelect_Dtor(g_itemSelects[i], 1);
                g_itemSelects[i] = 0;
            }
            Tachometer_Destroy();
            HitMessageOverlay_Destroy();
            ProcessSystemTick((int)messages + 0x500);
            fn_80254134(self->field24, 1);
            delete self->child;
            LakituStart_Dtor(self->start, 1);
            Jyugemu_Flag_Dtor(self->flag, 1);
            Jyugemu_ReverseFlag_Dtor(self->reverseFlag, 1);
            LapBannerScene_Dtor(self->banner, 1);
            PathParticipantArray_Dtor(lbl_806D12F4, 1);
            ProcessSystemTick((int)messages + 0x524);
            for (int i=0; i<4; ++i) {
                if (g_carObjects[i]) delete g_carObjects[i];
                g_carObjects[i] = 0;
            }
            if (self->child20) delete self->child20;
            CourseEnvironment_Dtor(self->environment, 1);
            ProcessSystemTick((int)messages + 0x548);
            if (lbl_806D12F8) {
                Release(lbl_806D12F8);
                lbl_806D12F8 = 0;
            }
            ItemObjectManager_Reset();
            VfxSlotMgr_Shutdown();
            RankingTable_Init(GetRaceContextPtr());
            ClRomTable_PurgeAll();
            self->start = 0;
            self->flag = 0;
            self->reverseFlag = 0;
            self->banner = 0;
            lbl_806D12F4 = 0;
            self->child = 0;
            self->environment = 0;
            SetPlayerCarObject(0);
            delete lbl_806D10D0;
            lbl_806D10D0 = 0;
            fn_8013A6F8();
            g_raceCamera = 0;
            delete lbl_806D109C;
            lbl_806D109C = 0;
            CourseBgm_Free();
            SceneDrawList_Reset();
            ProcessSystemTick((int)messages + 0x55c);
            delete g_courseData[0];
            g_courseData[0] = 0;
            SetResourceLoadingFlag(0);
            clRom_PurgeAll();
            SetCourseScene3D(0);
            ProcessSystemTick((int)messages + 0x578);
        }
        baseDtor(self);
        if (deleting > 0) MemoryManager_TimedFree(self);
    }
    return self;
}
#pragma use_lmw_stmw reset
