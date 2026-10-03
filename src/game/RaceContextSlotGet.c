/* Observed slot view; the complete runtime class is not yet established. */
typedef struct RaceContextSlot {
    int type;
    unsigned char remaining[0xB8];
} RaceContextSlot;

static inline unsigned char Slot_IsAlive(RaceContextSlot* slot)
{
    return slot->type != -1;
}

RaceContextSlot* RaceContextSlot_GetIfAlive(RaceContextSlot* slots, int index)
{
    RaceContextSlot* slot;
    if (index < 0 || index >= 128) {
        return 0;
    }
    slot = &slots[index];
    if (Slot_IsAlive(slot) & 1) {
        return slot;
    }
    return 0;
}
