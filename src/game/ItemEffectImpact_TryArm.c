extern void ItemEffectImpact_TryArmInit(void *state);

typedef struct ItemEffectImpactSlot {
    unsigned char pad_0[4];
    void *state;
    unsigned char pad_8[0x10];
    void *armed;
} ItemEffectImpactSlot;

/* 0x80053E8C: arm the impact effect with its state if the slot is free. */
int ItemEffectImpact_TryArm(ItemEffectImpactSlot *slot)
{
    if (slot->armed != 0) {
        return 0;
    }
    slot->armed = slot->state;
    ItemEffectImpact_TryArmInit(slot->state);
    return 1;
}
