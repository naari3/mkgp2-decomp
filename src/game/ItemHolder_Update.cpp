extern "C" void *GetRaceContextPtr(void);
extern "C" unsigned char IsRaceStarted(void);
extern "C" unsigned char KartMovement_CanReceiveItem(int kart, int arg);
extern "C" char *RaceContextSlot_GetIfAlive(void *ctx, int slot);
extern const float lbl_806DA3D8;

class ItemHolder {
public:
    virtual void v8();
    virtual void Tick();

    int kart;
    char pad_8[0xC];
    int slot;
    int targetSlot;
    int pendingItem;
    int state;
    int cooldown;
    int grantedItem;
};

extern "C" void ItemHolder_Update(ItemHolder *self) {
    char *obj;
    char *link;
    int kart;

    if (IsRaceStarted()) {
        kart = self->kart;
        self->grantedItem = 0;
        self->Tick();
        if (self->state == 2) {
            if (KartMovement_CanReceiveItem(kart, 0)) {
                self->state = 0;
                self->grantedItem = self->pendingItem;
                obj = RaceContextSlot_GetIfAlive(GetRaceContextPtr(), self->slot);
                if (*(char **)(obj + 0x9C) != 0) {
                    *(int *)(*(char **)(obj + 0x9C) + 0x94) = 0;
                    link = *(char **)(obj + 0x9C);
                    if (*(int *)(link + 0x98) > 0) {
                        (*(int *)(link + 0x98))--;
                    }
                }
                *(int *)(obj + 0x90) = -1;
                *(float *)(obj + 0xA0) = lbl_806DA3D8;
                *(char **)(obj + 0x9C) = 0;
                *(int *)(obj + 0xB8) = 0;
                self->targetSlot = -1;
                self->pendingItem = 0;
            }
        } else if (self->cooldown > 0) {
            self->cooldown--;
        }
    }
}
