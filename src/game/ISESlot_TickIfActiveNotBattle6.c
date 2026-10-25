typedef struct ISESlot {
    unsigned char pad_00[4];
    unsigned char active;
    unsigned char pad_05[0x13];
    void *item;
} ISESlot;

typedef struct SlotKart {
    unsigned char pad[0x1F4];
    int eventType;
} SlotKart;

extern int g_gameMode;
extern void ItemObject_SetField168(void *item, int value);

int ISESlot_TickIfActiveNotBattle6(ISESlot *slot, int value, SlotKart *kart) {
    if (!slot->active) {
        return 0;
    }
    if (kart != 0 && kart->eventType == 6 && g_gameMode == 2) {
        return 0;
    }
    if (slot->item != 0) {
        ItemObject_SetField168(slot->item, value);
    }
    return 1;
}
