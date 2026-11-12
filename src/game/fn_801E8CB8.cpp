/* clEnemyItemDegu's original file, 0x801E8CB8..0x801E93AC.
 * Deferred generation requires reverse method definitions. The item-selection
 * table precedes the compiler-emitted base list and vtable in .data. */
#include "game/types/clEnemyItemInterface.h"
#include "game/types/Vec3.h"
#include "game/types/RaceSlot.h"
#include "game/types/KartDriver.h"
#include "game/types/size_t.h"
void operator delete(void *) throw();
extern "C" {
void *GetRaceContextPtr();
RaceSlot *RaceContextSlot_GetIfAlive(void *, int);
extern int g_gameMode;
extern unsigned char g_isCommHost;
extern int lbl_806D1918;
void fn_801DC6E4(void *, int);
int fn_801DC6CC(void *);
int GetAnimState(void *);
unsigned char RenderObj_UseItem(void *, int, int);
void *KartDriver_GetJObjRootIfReady(void *);
void Object_GetJObjPositionVec(void *, Vec3 *);
float Vec3_Distance(Vec3 *, Vec3 *);
unsigned char KartMovement_CanReceiveItem(int, int);
unsigned char KartMovement_EquipItem(int, int);
unsigned char IsRaceStarted();
int KartItem_CancelAndQueueDefault(int);
int KartItem_CancelIfNotForced(int);
}
extern const float lbl_806DA3D8;
static int ItemHolder_SetItem_data_804E4B10[10] = {6, 2, 3, 1, 5, 4, 2, 4, 1, 5};
#include "game/types/clEnemyItemDegu.h"
inline clEnemyItemInterface::clEnemyItemInterface(unsigned int o, int a, int b, int c) {
    kart = (KartDriver *)o; x8=a; xC=b; x10=c;
    targetId=-1; pendingItem=0; state=0; grantedItem=0; cooldown=0;
    for (int i=0; i<0x80; i++) {
        char *p=(char *)RaceContextSlot_GetIfAlive(GetRaceContextPtr(),i);
        if (p != 0 && *(unsigned int *)(p+0xB4)==o) { selfId=i; break; }
    }
}
extern "C" void fn_801E93A0() { lbl_806D1918=0; }

void clEnemyItemDegu::Tick() {
    char *obj;
    char *link;
    int kart;

    if (IsRaceStarted()) {
        kart = (int)this->kart;
        grantedItem = 0;
        Update();
        if (state == 2) {
            if (KartMovement_CanReceiveItem(kart, 0)) {
                state = 0;
                grantedItem = pendingItem;
                obj = (char *)RaceContextSlot_GetIfAlive(GetRaceContextPtr(), selfId);
                if (*(char **)(obj + 0x9C) != 0) {
                    *(int *)(*(char **)(obj + 0x9C) + 0x94) = 0;
                    link = *(char **)(obj + 0x9C);
                    if (*(int *)(link + 0x98) > 0) {
                        (*(int *)(link + 0x98))--;
                    }
                }
                *(int *)(obj + 0x90) = -1;
                *(float *)(obj + 0xA0) = lbl_806DA3D8;
                *(char **)(obj + 0x9C) = 0;
                *(int *)(obj + 0xB8) = 0;
                targetId = -1;
                pendingItem = 0;
            }
        } else if (cooldown > 0) {
            cooldown--;
        }
    }
}

unsigned char clEnemyItemDegu::IsIdle() { return state==0; }

void clEnemyItemDegu::SetItem(int item, int arg) {
    if (g_gameMode == 2 && g_isCommHost == 0) {
        char *obj = (char *)RaceContextSlot_GetIfAlive(GetRaceContextPtr(), selfId);
        pendingItem = item;
        *(int *)(obj + 0x90) = 0;
        if (KartMovement_EquipItem((int)kart, item)) {
            state = 1;
            lbl_806D1918++;
            lbl_806D1918 %= 10;
            cooldown = ItemHolder_SetItem_data_804E4B10[lbl_806D1918] * 60 + 120;
            cooldown = 60;
        }
        *(int *)(obj + 0x90) = -1;
        return;
    }
    if (state == 0) {
        pendingItem = item;
        if (KartMovement_CanReceiveItem((int)kart, arg) && item > 0 && item < 0x115) {
            Equip(item);
        }
    }
}

inline void clEnemyItemDegu::Equip(int item) {
    char *obj = (char *)RaceContextSlot_GetIfAlive(GetRaceContextPtr(), selfId);
    *(int *)(obj + 0x90) = 0;
    if (KartMovement_EquipItem((int)kart, item)) {
        state = 1;
        lbl_806D1918++;
        lbl_806D1918 %= 10;
        cooldown = ItemHolder_SetItem_data_804E4B10[lbl_806D1918] * 60 + 120;
        cooldown = 60;
    }
    *(int *)(obj + 0x90) = -1;
}

void clEnemyItemDegu::Cancel() { if (state==1) { KartItem_CancelIfNotForced((int)kart); KartItem_CancelAndQueueDefault((int)kart); state=0; } }

unsigned int clEnemyItemDegu::GetEffectCategory() { return grantedItem; }

unsigned int clEnemyItemDegu::HasItem() { return state==1 ? 1 : 0; }

unsigned int clEnemyItemDegu::GetItemType() { return pendingItem; }

clEnemyItemDegu::clEnemyItemDegu(AIDriver *o,AITornado *a,int b,int c) : clEnemyItemInterface((unsigned int)o,(int)a,b,c) {}

clEnemyItemDegu::~clEnemyItemDegu() {}

void clEnemyItemDegu::Update()
{
    RaceSlot *src;
    RaceSlot *dst;
    void *dstDriver;
    void *link;
    int target;
    KartDriver *k;
    k = kart;
    link = k->raceSlot;
    if (g_gameMode == 2) {
        if (g_isCommHost == 1) {
            fn_801DC6E4(link, -1);
            if (CanUse() && GetAnimState(k) == 0 && targetId >= 0 && RenderObj_UseItem(k, 0, 0)) {
                state = 2;
                fn_801DC6E4(link, targetId);
            }
        } else {
            targetId = fn_801DC6CC(link);
            if (targetId != -1 && RenderObj_UseItem(k, 1, 0)) {
                state = 2;
            }
        }
    } else if (CanUse() && GetAnimState(k) == 0) {
        target = targetId;
        if (target >= 0) {
            src = RaceContextSlot_GetIfAlive(GetRaceContextPtr(), selfId);
            dst = RaceContextSlot_GetIfAlive(GetRaceContextPtr(), target);
            dstDriver = dst->driver;
            Vec3 b, a;
            Object_GetJObjPositionVec(KartDriver_GetJObjRootIfReady(kart), &a);
            Object_GetJObjPositionVec(KartDriver_GetJObjRootIfReady(dstDriver), &b);
            src->targetId = target;
            src->target = dst;
            src->targetDriver = dst->driver;
            src->distance = Vec3_Distance(&b, &a);
            dst->sourceId = selfId;
            dst->hitCount++;
            if (RenderObj_UseItem(k, 0, 0)) {
                state = 2;
            }
        }
    }
}

void clEnemyItemDegu::SetTarget(unsigned int id) {
    int i;
    char *obj;

    if (state == 1) {
        targetId = -1;
        for (i = 0; i < 0x80; i++) {
            obj = (char *)RaceContextSlot_GetIfAlive(GetRaceContextPtr(), i);
            if (obj != 0 && *(unsigned int *)(obj + 0xB4) == id) {
                targetId = i;
                return;
            }
        }
    }
}

void clEnemyItemDegu::ResetTarget() { targetId=-1; }

bool clEnemyItemDegu::CanUse() { if (cooldown>0) return 0; if (pendingItem<=0 || pendingItem>=0x115) return 0; return state==1; }

int clEnemyItemDegu::IsEnabled() { return 1; }
