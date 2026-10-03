/* Only fields accessed by these two functions are modeled. */
typedef struct RaceContextSlot {
    int type;
    int id;
    unsigned int word08, word0C;
    unsigned char pad10[0x60];
    void* object70;
    unsigned char pad74[0x0C];
    void* position;
    int index84;
    unsigned int word88, word8C;
    int index90, index94;
    unsigned char pad98[4];
    unsigned int word9C;
    unsigned char padA0[4];
    float scale;
    void* item;
    unsigned int argument6;
    int state;
    unsigned int argument7;
    unsigned int wordB8;
} RaceContextSlot;

extern void* ItemObject_GetPositionPtr(void* item);
extern const float lbl_806D4898;

static inline unsigned int Slot_IsAlive(RaceContextSlot* slot)
{
    return slot->type != -1;
}

int RaceContextSlot_Free(RaceContextSlot* slots, int index)
{
    RaceContextSlot* slot;
    if (index < 0 || index >= 128) {
        return index;
    }
    slot = &slots[index];
    if (Slot_IsAlive(slot) == 1) {
        slot->type = -1;
        slot->id = -1;
        slot->word08 = 0;
        slot->word0C = 0;
        slot->object70 = 0;
        slot->index84 = 0;
        slot->word88 = 0;
        slot->word8C = 0;
        slot->index90 = -1;
        slot->index94 = -1;
    }
    return -1;
}

static inline void Slot_InitItem(RaceContextSlot* slots, int index, int id,
                                void* item, unsigned int argument6,
                                unsigned int argument7)
{
    void* position = ItemObject_GetPositionPtr(item);
    RaceContextSlot* slot = &slots[index];
    /* The external getter can invalidate the free-slot observation. */
    if (Slot_IsAlive(slot) != 1) {
        slot->type = 7;
        slot->id = id;
        slot->object70 = 0;
        slot->position = position;
        slot->item = item;
        slot->index84 = -1;
        slot->argument6 = argument6;
        slot->state = 0x30;
        slot->scale = lbl_806D4898;
        slot->word9C = 0;
        slot->argument7 = argument7;
        slot->wordB8 = 0;
    }
}

int RaceContextSlot_AllocItem(RaceContextSlot* slots, int id, void* item,
                              unsigned int argument6, unsigned int argument7)
{
    int index;
    for (index = 0; index < 128; index++) {
        if (slots[index].type == -1) {
            Slot_InitItem(slots, index, id, item, argument6, argument7);
            return index;
        }
    }
    return -1;
}
