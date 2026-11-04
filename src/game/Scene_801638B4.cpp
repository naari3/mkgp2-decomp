#include "game/Scene_801638B4Private.h"

extern "C" LoaderDelete162 *fn_801638B4(LoaderDelete162 *s, short flag) {
    if (s) {
        if (s->trace == 1 && s->traceTime <= lbl_806D88F0) {
            DebugPrintf(lbl_80369C94);
            for (int i = 0; i < 2700; i++) {
                Trace162 *p = &s->positions[i];
                DebugPrintf(lbl_80369CCC, p->x, p->y, p->z, p->n);
            }
            DebugPrintf(lbl_80369C94);
        }
        MemoryManager_Free(s->positions);
        ProcessSystemTick(0);
        SetActiveCamera(0, 0);
        AI_SystemDtor(s->ai, 1);
        fn_80208FE4(s->system, 1);
        ItemSelect_Dtor(g_itemSelects[0], 1);
        SetCourseScene3D(0);
        delete s->scene;
        LakituStart_Dtor(s->object, 1);
        Jyugemu_Flag_Dtor(s->flag, 1);
        Jyugemu_ReverseFlag_Dtor(s->reverseFlag, 1);
        LapBannerScene_Dtor(s->banner, 1);
        PathParticipantArray_Dtor(s->paths, 1);
        SceneFlow_SetFlag1048(0);
        ProcessSystemTick(0);
        delete g_carObjects[0];
        if (s->child) delete s->child;
        CourseEnvironment_Dtor(s->environment, 1);
        ProcessSystemTick(0);
        if (s->resource) {
            Release(s->resource);
            s->resource = 0;
        }
        ItemObjectManager_Reset();
        VfxSlotMgr_Shutdown();
        RankingTable_Init(GetRaceContextPtr());
        ClRomTable_PurgeAll();
        ProcessSystemTick(0);
        s->object = 0;
        s->flag = 0;
        s->reverseFlag = 0;
        s->banner = 0;
        g_carObjects[0] = 0;
        s->paths = 0;
        s->scene = 0;
        s->environment = 0;
        SetPlayerCarObject(0);
        delete lbl_806D10D0;
        lbl_806D10D0 = 0;
        fn_8013A6F8();
        g_raceCamera = 0;
        ProcessSystemTick(0);
        CourseBgm_Free();
        SceneDrawList_Reset();
        delete lbl_806D109C;
        lbl_806D109C = 0;
        delete g_courseData[0];
        g_courseData[0] = 0;
        ProcessSystemTick(0);
        SetResourceLoadingFlag(0);
        HSD_FObjForceLinearInterp(0);
        HSD_RandSeedPtr = s->seed;
        RandSeedDebug_SetEnable(s->randDebug);
        ProcessSystemTick(0);
        delete lbl_806D10AC;
        lbl_806D10AC = 0;
        fn_80121210();
        clRom_PurgeAll();
        ProcessSystemTick(0);
        if (flag > 0) MemoryManager_TimedFree(s);
    }
    return s;
}
