/* Observed 0xBC-byte slot view; unknown fields remain padding. */
typedef struct RaceContextSlot {
    int type;
    int id;
    unsigned int word08, word0C;
    unsigned char pad10[0x60];
    void* driver;
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
    int indexAC;
    int state;
    unsigned int payloadB4;
    unsigned int wordB8;
} RaceContextSlot;

extern const float lbl_806D4898;

static inline unsigned int Slot_IsAlive(RaceContextSlot* slot)
{
    return slot->type != -1;
}

static inline void Slot_InitDriver(RaceContextSlot* slots, int index, int type,
                                  int id, void* driver, unsigned int payload,
                                  int driverIndex)
{
    RaceContextSlot* slot = &slots[index];
    if (Slot_IsAlive(slot) != 1) {
        slot->type = type;
        slot->id = id;
        slot->driver = driver;
        slot->position = 0;
        slot->item = 0;
        slot->index84 = driverIndex;
        slot->indexAC = -1;
        slot->state = 0x30;
        slot->scale = lbl_806D4898;
        slot->word9C = 0;
        slot->payloadB4 = payload;
        slot->wordB8 = 0;
    }
}

int RaceContextSlot_AllocDriver(RaceContextSlot* slots, int type, int id,
                                void* driver, unsigned int payload,
                                int driverIndex)
{
    int index;
    for (index = 0; index < 128; index++) {
        if (slots[index].type == -1) {
            Slot_InitDriver(slots, index, type, id, driver, payload, driverIndex);
            return index;
        }
    }
    return -1;
}

static inline void Slot_Clear(RaceContextSlot* slot)
{
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

void RankingTable_Init(RaceContextSlot* slots)
{
    int index;
    for (index = 0; index < 128; index++) {
        Slot_Clear(&slots[index]);
    }
}
