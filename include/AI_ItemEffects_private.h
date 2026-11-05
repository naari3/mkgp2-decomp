#ifndef AI_ITEMEFFECTS_PRIVATE_H
#define AI_ITEMEFFECTS_PRIVATE_H

typedef struct AIItemDriver {
    unsigned char reserved[0x304];
    void *bus;
} AIItemDriver;
struct AIIncomingItem;
typedef struct AIItemController {
    unsigned char reserved00[0x10];
    AIItemDriver *driver;
    void *visual;
    void *audio;
    void *reserved1C;
    void *movement;
    void *holder;
    void *steering;
    void *follower;
    unsigned char reserved30[0x68];
    int restoreTimer, restoreItem, cooldown;
    float speed;
    int category;
    int timer52, timer1B, timer23, timer1D, timer1C;
    int timer1A, timer22, timer55, timer75, speedTimer;
    int timer26, timer99, timer9A, timer8C, timer9B, timer9D;
#ifdef __cplusplus
    int ApplyIncomingItem(AIIncomingItem *);
#endif
} AIItemController;
#ifdef __cplusplus
extern "C" {
#endif
extern void *fn_801DB8F0(void);
extern int fn_801DB800(void *, int);
extern int fn_801DB8A4(void *, int);
extern void ItemHolder_SetItem(void *, int, int);
extern void ItemHolder_Update(void *);
extern int ItemHolder_GetEffectCategory(void *);
extern void ItemEffectBus_OrMask(void *, unsigned long long);
extern void ItemEffectBus_ClearMask(void *, unsigned long long);
extern void ItemEffectBus_ApplyItemConfirm(void *, int);
extern void ItemEffectBus_ApplyItemEventClear(void *, int);
extern void TornadoEffect_ApplyItemVisual_Compact(void *, int, int);
extern void TornadoEffect_ApplyItemVisual_Primary(void *, int);
extern void fn_801EC7F0(void *, int);
extern void fn_801EC7E8(void *, float);
extern void fn_801DEF94(void *);
extern const float lbl_806DA398, lbl_806DA390;
#ifdef __cplusplus
}
#endif
#endif
