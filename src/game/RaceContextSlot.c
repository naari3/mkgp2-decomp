/* Only fields accessed by these two functions are modeled. */
#include "game/types/RaceContextSlot.h"

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
        slot->driver = 0;
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
        slot->driver = 0;
        slot->position = position;
        slot->item = item;
        slot->index84 = -1;
        slot->indexAC = argument6;
        slot->state = 0x30;
        slot->scale = lbl_806D4898;
        slot->word9C = 0;
        slot->payloadB4 = argument7;
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
