#include "game/KartMovement.h"
struct AIItemController {
    char pad[0xEC];
    int itemTimer;
    int hitTimer;
};
struct AIItemOwner {
    void *vtable;
    void *car;
};
struct AIItemRender {
    char pad[0x23C];
    int rank;
    int lap;
};
extern "C" {
extern AIItemController *Read_U32[8];
extern int g_totalLaps;
AIItemRender *KartController_GetRenderObj(void *);
AIItemRender *CarObject_GetRenderObj(void *);
int AI_GetLapDifference(void *);
unsigned char AI_CheckItemSuppression(int, int, int);
unsigned char AI_HasItem(void *);
void *KartDriver_GetJObjRootIfReady(void *);
void Object_GetJObjPositionVec(void *, Vec3 *);
float AI_GetYaw(void *);
int AI_GetItemType(void *);
#ifdef __MWERKS__
unsigned char AI_CheckTargetInRange(int, Vec3, Vec3, float);
#else
/* The definition takes these structs by address; see docs/notes/port_abi.md. */
extern unsigned char AI_CheckTargetInRange(int, Vec3 *, Vec3 *, float);
static inline unsigned char AI_CheckTargetInRange_ByValue(int a0, Vec3 a1, Vec3 a2, float a3) { return AI_CheckTargetInRange(a0, &a1, &a2, a3); }
#define AI_CheckTargetInRange AI_CheckTargetInRange_ByValue
#endif
unsigned char AI_RollItemUseProbability(int);
int GetCourseSectionType(int);
void AI_UseItem(void *, void *);
}
static inline void Decrement(int timer, int &result) {
    result = timer;
    if (timer > 0) result = timer - 1;
}
extern "C" void AI_UpdateItemUseLogic(AIItemOwner *self, int kart) {
    AIItemController *ctrl = Read_U32[kart];
    int rank;
    int laps;
    int difference;
    laps = g_totalLaps - KartController_GetRenderObj(ctrl)->lap;
    difference = AI_GetLapDifference(ctrl);
    rank = KartController_GetRenderObj(ctrl)->rank;
    if (!AI_CheckItemSuppression(kart, laps, difference)) return;
    int hitTimer;
    Decrement(ctrl->hitTimer, hitTimer);
    ctrl->hitTimer = hitTimer;
    if (!AI_HasItem(ctrl)) return;
    int timer;
    Decrement(ctrl->itemTimer, timer);
    ctrl->itemTimer = timer;
    if (hitTimer > 0) return;
    int use = 0;
    AIItemRender *target = KartController_GetRenderObj(ctrl);
    if (timer <= 0) {
        use = 1;
    } else {
        Vec3 from;
        Vec3 to;
        Object_GetJObjPositionVec(KartDriver_GetJObjRootIfReady(KartController_GetRenderObj(ctrl)), &from);
        float yaw = AI_GetYaw(ctrl);
        Object_GetJObjPositionVec(KartDriver_GetJObjRootIfReady(CarObject_GetRenderObj(self->car)), &to);
        if (AI_CheckTargetInRange(AI_GetItemType(ctrl), from, to, yaw)) {
            if (AI_RollItemUseProbability(rank)) {
                use = 1;
                target = CarObject_GetRenderObj(self->car);
            } else {
                ctrl->hitTimer = 120;
                return;
            }
        }
    }
    if (use) {
        switch (GetCourseSectionType(AI_GetItemType(ctrl))) {
        case 1:
        case 2:
        case 3:
        case 4:
            AI_UseItem(ctrl, KartController_GetRenderObj(ctrl));
            return;
        case 5:
        case 6:
        case 7:
            break;
        case 9:
            break;
        default:
            break;
        }
        AI_UseItem(ctrl, target);
    }
}
