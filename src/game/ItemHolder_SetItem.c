extern void *GetRaceContextPtr(void);
extern unsigned char KartMovement_CanReceiveItem(int kart, int arg);
extern unsigned char KartMovement_EquipItem(int kart, int item);
extern char *RaceContextSlot_GetIfAlive(void *ctx, int slot);
extern int g_gameMode;
extern unsigned char g_isCommHost;
extern int lbl_804E4B10[10];
extern int lbl_806D1918;

typedef struct ItemHolder {
    void *vt;
    int kart;
    char pad_8[0xC];
    int slot;
    int targetSlot;
    int item;
    int state;
    int cooldown;
} ItemHolder;

static inline void ItemHolder_Equip(ItemHolder *self, int item) {
    char *obj = RaceContextSlot_GetIfAlive(GetRaceContextPtr(), self->slot);
    *(int *)(obj + 0x90) = 0;
    if (KartMovement_EquipItem(self->kart, item)) {
        self->state = 1;
        lbl_806D1918++;
        lbl_806D1918 %= 10;
        self->cooldown = lbl_804E4B10[lbl_806D1918] * 60 + 120;
        self->cooldown = 60;
    }
    *(int *)(obj + 0x90) = -1;
}

void ItemHolder_SetItem(ItemHolder *self, int item, int arg) {
    if (g_gameMode == 2 && g_isCommHost == 0) {
        char *obj = RaceContextSlot_GetIfAlive(GetRaceContextPtr(), self->slot);
        self->item = item;
        *(int *)(obj + 0x90) = 0;
        if (KartMovement_EquipItem(self->kart, item)) {
            self->state = 1;
            lbl_806D1918++;
            lbl_806D1918 %= 10;
            self->cooldown = lbl_804E4B10[lbl_806D1918] * 60 + 120;
            self->cooldown = 60;
        }
        *(int *)(obj + 0x90) = -1;
        return;
    }
    if (self->state == 0) {
        self->item = item;
        if (KartMovement_CanReceiveItem(self->kart, arg) && item > 0 && item < 0x115) {
            ItemHolder_Equip(self, item);
        }
    }
}
