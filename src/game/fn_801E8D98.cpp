struct Vec3 {
    float x, y, z;
};
struct RaceSlot {
    char pad0[0x90];
    int targetId;
    int sourceId;
    int hitCount;
    void *target;
    float distance;
    char padA4[0x10];
    void *driver;
    void *targetDriver;
};
extern "C" {
extern int g_gameMode;
extern unsigned char g_isCommHost;
void fn_801DC6E4(void *link, int id);
int fn_801DC6CC(void *link);
int GetAnimState(void *kart);
unsigned char RenderObj_UseItem(void *kart, int a, int b);
void *GetRaceContextPtr(void);
RaceSlot *RaceContextSlot_GetIfAlive(void *ctx, int id);
void *KartDriver_GetJObjRootIfReady(void *driver);
void Object_GetJObjPositionVec(void *jobj, Vec3 *out);
float Vec3_Distance(Vec3 *a, Vec3 *b);
}
struct Kart {
    char pad0[0x248];
    void *link;
};
class ItemUser {
public:
    virtual void v08();
    virtual void v0C();
    virtual void v10();
    virtual void v14();
    virtual bool CanUse();
    Kart *kart;
    char pad08[0xC];
    int selfId;
    int targetId;
    char pad1C[4];
    int state;
    void Update();
};

void ItemUser::Update()
{
    RaceSlot *src;
    RaceSlot *dst;
    void *dstDriver;
    void *link;
    int target;
    Kart *k;
    k = kart;
    link = k->link;
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
