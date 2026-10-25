extern void *GetRaceContextPtr(void);
extern void *RaceContextSlot_GetIfAlive(void *ctx, int slot);

typedef struct SlotTracker {
    char pad_0[0x18];
    int slot;
    char pad_1C[4];
    int mode;
} SlotTracker;

void x10(SlotTracker *self, unsigned int id) {
    int i;
    char *obj;

    if (self->mode == 1) {
        self->slot = -1;
        for (i = 0; i < 0x80; i++) {
            obj = RaceContextSlot_GetIfAlive(GetRaceContextPtr(), i);
            if (obj != 0 && *(unsigned int *)(obj + 0xB4) == id) {
                self->slot = i;
                return;
            }
        }
    }
}
