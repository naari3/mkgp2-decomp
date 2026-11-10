extern void ExplosionTumble_Init(void *state, void *position, void *velocity, void *pose);

typedef struct ItemStateSlotC {
    unsigned char pad_0[0xC];
    void *state;
    unsigned char pad_10[8];
    void *armed;
} ItemStateSlotC;

/* 0x80053290: arm slot C with its explosion tumble state if it is free. */
int ItemStateSlotC_TryArm(ItemStateSlotC *slot, void *position, void *velocity, void *pose)
{
    if (slot->armed != 0) {
        return 0;
    }
    slot->armed = slot->state;
    ExplosionTumble_Init(slot->state, position, velocity, pose);
    return 1;
}
