#ifndef ITEM_EFFECT_ARM_PRIVATE_H
#define ITEM_EFFECT_ARM_PRIVATE_H

struct ArmVec { float x, y, z; };
struct ArmMtx { float m[16]; };
struct ArmCar { char pad[0xD4]; unsigned char held; };
struct ArmOwner { ArmCar *car; };

class DampArmState {
public:
    virtual void Reset();
    ArmOwner *owner;
    ArmVec velocity;
    float strength, duration;
    int flags;
};
struct DampArmSlot {
    char pad[0x10];
    DampArmState *state;
    void *other;
    DampArmState *armed;
};

class BossGrabState {
public:
    virtual void Reset();
    ArmOwner *owner;
    ArmVec position;
    int timer;
    float elapsed;
    ArmMtx start, current;
    int duration, flags;
};
struct BossGrabSlot {
    char pad[0x14];
    BossGrabState *state;
    BossGrabState *armed;
};
#endif
