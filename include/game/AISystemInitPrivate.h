#ifndef GAME_AI_SYSTEM_INIT_PRIVATE_H
#define GAME_AI_SYSTEM_INIT_PRIVATE_H
#include "game/AIKartInitPrivate.h"
#include "game/AIPairPrivate.h"
struct ThinkBoxBase;
extern "C" {
void MemoryManager_TimedFree(void *);
extern int g_gameMode, g_roundIndex, g_cupId, g_pseudoRandomCounter;
extern void *g_pathSystem, *lbl_806D1928;
extern AIKart *Read_U32[8];
extern AIPairRecord lbl_806793D8[8];
extern const float lbl_806DA3F4;
void *GetEnemyParam();
void fn_801DE1B0();
void PathFollower_EnsureGlobalAlloc();
void fn_801DC664();
void fn_801DB95C();
void fn_801DE810();
void ProcessSystemTick(int);
int RaceSlot_GetDriverId(int);
int GetKartSlotCharId(int);
int fn_801E6E18(AIKart *);
void *KartController_GetRenderObj(AIKart *);
void *GetKartTuningEntry(void *, int, int, int);
void fn_801E6C68(AIKart *, int);
void fn_801E6E20(AIKart *);
void *CarObjects_FindByEventType(int, int *);
ThinkBoxBase *ThinkBox_Create();
}
struct AISystemBox {
    ThinkBoxBase *p;
    AISystemBox() : p(0) {}
    ~AISystemBox() { MemoryManager_TimedFree(p); }
    void reset(ThinkBoxBase *q) {
        if (p != q) { MemoryManager_TimedFree(p); p = q; }
    }
};
struct AISystemInitOwner {
    AISystemBox box;
    AISystemInitOwner(void *, void *, int);
};
#endif
