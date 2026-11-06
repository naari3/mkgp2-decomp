#include "game/AISystemInitPrivate.h"
static inline void ResetRecord(AIPairRecord *p) {
    p->kartId = -1;
    p->driver = 0;
    p->field08 = 0;
    p->waypoint = 0;
    p->field1C = 0;
    p->field20 = lbl_806DA3F4;
    p->nearestKart = -1;
    p->nearestDriver = 0;
    p->distanceSquared = lbl_806DA3F4;
    p->field24 = 0;
    p->field28 = -1;
}
struct SlotTuning { char pad[0x50]; int mode; };
static inline SlotTuning *GetSlotTuning(int i) {
    int round = g_roundIndex;
    int cup = g_cupId;
    return (SlotTuning *)GetKartTuningEntry(GetEnemyParam(), cup, round, i);
}
static inline void InitializeSlot(int i, int flag) {
    ProcessSystemTick(0);
    Read_U32[i] = 0;
    int driver = RaceSlot_GetDriverId(i);
    if (driver == 6) {
        int character = GetKartSlotCharId(i);
        if (g_pathSystem && !Read_U32[i]) {
            AIKart *ctrl = new AIKart((void *)character, i, flag, i);
            Read_U32[i] = ctrl;
            lbl_806793D8[i].kartId = fn_801E6E18(ctrl);
            lbl_806793D8[i].driver = KartController_GetRenderObj(ctrl);
            if (g_gameMode == 0) {
                SlotTuning *tuning = GetSlotTuning(i);
                if (tuning->mode == 1) fn_801E6C68(ctrl, 0);
                else fn_801E6C68(ctrl, 1);
            } else fn_801E6C68(ctrl, 0);
            fn_801E6E20(ctrl);
        }
    } else if (driver >= 0 && driver <= 3) {
        lbl_806793D8[i].driver = CarObjects_FindByEventType(driver, &lbl_806793D8[i].kartId);
    }
    lbl_806793D8[i].field24 = 0;
    lbl_806793D8[i].field28 = -1;
}
AISystemInitOwner::AISystemInitOwner(void *path, void *coll, int flag) {
    g_pseudoRandomCounter = 0;
    g_pathSystem = path;
    for (int i = 0; i < 8; ++i) ResetRecord(&lbl_806793D8[i]);
    if (g_gameMode != 1) {
        lbl_806D1928 = coll;
        GetEnemyParam();
        fn_801DE1B0();
        PathFollower_EnsureGlobalAlloc();
        fn_801DC664();
        fn_801DB95C();
        fn_801DE810();
        for (int i = 0; i < 8; ++i) InitializeSlot(i, flag);
        box.reset(ThinkBox_Create());
    } else {
        lbl_806D1928 = 0;
        if (box.p) { MemoryManager_TimedFree(box.p); box.p = 0; }
    }
}
