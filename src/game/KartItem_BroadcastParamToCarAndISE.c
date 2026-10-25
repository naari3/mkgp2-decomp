extern void *GetPlayerCarObject(void *item);
extern void *CarObject_GetRenderObj(void *car);
extern void fn_80250AE8(void *target, int param, void *item);
extern void fn_8024F650(void *ise, int param);

typedef struct KartItemBroadcast {
    unsigned char pad_0[0x2D0];
    unsigned char hasIse;
    unsigned char pad_2D1[0xA3];
    int param;
    void *ise;
} KartItemBroadcast;

/* 0x8003F2D8: pass a parameter to the player car's render object and ISE. */
void KartItem_BroadcastParamToCarAndISE(KartItemBroadcast *item, int param)
{
    void *car = GetPlayerCarObject(item);
    void *target;

    if (car != 0) {
        target = *(void **)((char *)CarObject_GetRenderObj(car) + 0x380);
        if (target != 0) {
            fn_80250AE8(target, param, item);
        }
    }
    if (item->hasIse && item->ise != 0) {
        if (item->param == -1) {
            fn_8024F650(item->ise, param);
        }
        item->param = param;
    }
}
