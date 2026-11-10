/* Native reconstruction of the assigned single-function TU. */
extern "C" {
#include "game/AISpeedPrivate.h"
#include "game/KartMovement.h"
#include "game/AIPairItemUsePrivate.h"
extern unsigned char AI_HasItem(void *);
extern unsigned char AI_CheckItemSuppression(int, int, int);
extern void *KartDriver_GetJObjRootIfReady(void *);
extern void Object_GetJObjPositionVec(void *, Vec3 *);
extern float AI_GetYaw(void *);
extern int AI_GetItemType(void *);
#ifdef __MWERKS__
extern unsigned char AI_CheckTargetInRange(int, Vec3, Vec3, float);
#else
/* The definition takes these structs by address; see docs/notes/port_abi.md. */
extern unsigned char AI_CheckTargetInRange(int, Vec3 *, Vec3 *, float);
static inline unsigned char AI_CheckTargetInRange_ByValue(int a0, Vec3 a1, Vec3 a2, float a3) { return AI_CheckTargetInRange(a0, &a1, &a2, a3); }
#define AI_CheckTargetInRange AI_CheckTargetInRange_ByValue
#endif
extern unsigned char AI_RollItemUseProbability(int);
extern void fn_801DC6B4(int, int);
extern void fn_801DC6E4(int, int);
extern int GetCourseSectionType(int);
extern void AI_UseItem(void *, void *);
static inline void Decrement(int timer, int &result) {
    result = timer;
    if (timer > 0) result = timer - 1;
}
void AI_DecideAndUseItem_PairTracking(AISpeedOwner *self, int kart) {
    PairItemController *ctrl = (PairItemController *)Read_U32[kart];
    AIPairRecord *record = &lbl_806793D8[kart];
    int decisionValue;
    Decrement(ctrl->hitTimer, decisionValue);
    ctrl->hitTimer = decisionValue;
    if (AI_HasItem(ctrl)) {
        int timer;
        Decrement(ctrl->itemTimer, timer);
        ctrl->itemTimer = timer;
        if (decisionValue <= 0) {
            int laps = g_totalLaps - KartController_GetRenderObj(ctrl)->lap;
            int use;
            int difference = AI_GetLapDifference(ctrl);
            void *target;
            decisionValue = KartController_GetRenderObj(ctrl)->rank;
            use = 0;
            target = KartController_GetRenderObj(ctrl);
            if (AI_CheckItemSuppression(kart, laps, difference)) {
                if (timer <= 0) use = 1;
                else if (record->nearestDriver) {
                    Vec3 from, to;
                    float yaw;
                    Object_GetJObjPositionVec(KartDriver_GetJObjRootIfReady(KartController_GetRenderObj(ctrl)), &from);
                    yaw = AI_GetYaw(ctrl);
                    Object_GetJObjPositionVec(KartDriver_GetJObjRootIfReady(record->nearestDriver), &to);
                    if (AI_CheckTargetInRange(AI_GetItemType(ctrl), from, to, yaw)) {
                        if (AI_RollItemUseProbability(decisionValue)) { use = 1; target = record->nearestDriver; }
                        else { ctrl->hitTimer = 120; return; }
                    }
                }
            }
            if (use) {
                fn_801DC6B4(kart, 1);
                switch (GetCourseSectionType(AI_GetItemType(ctrl))) {
                case 1: case 2: case 3: case 4:
                    AI_UseItem(ctrl, KartController_GetRenderObj(ctrl));
                    fn_801DC6E4(kart, ((PairItemRender *)KartController_GetRenderObj(ctrl))->kartId);
                    return;
                case 5: case 6: case 7: break;
                case 9: break;
                default: break;
                }
                AI_UseItem(ctrl, target);
                fn_801DC6E4(kart, ((PairItemRender *)target)->kartId);

            }
        }
    }
}

}
