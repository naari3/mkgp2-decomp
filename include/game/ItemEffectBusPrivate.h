#ifndef ITEM_EFFECT_BUS_PRIVATE_H
#define ITEM_EFFECT_BUS_PRIVATE_H

typedef unsigned long long ItemEffectMask;
typedef struct ItemEffectBus {
    void *driver;
    unsigned char bonkPending;
    unsigned char pad05[3];
    unsigned int eventFlags;
    unsigned int pad0C;
    ItemEffectMask mask;
    ItemEffectMask snapshot;
    unsigned char positionPending;
    unsigned char pad21[3];
    float timer24;
    float timer28;
    int actionMode;
    float position[3];
    float bonkPosition[3];
    float timer48;
    int field4C;
    int tornadoCooldown;
} ItemEffectBus;

#endif
