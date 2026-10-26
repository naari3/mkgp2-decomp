/* Item roulette state of a kart: cancel a pending drop, hand over an item
 * (or queue it while one is held), and start a roulette spin. */
typedef struct ItemSelect {
    unsigned char pad00[0x1c];
    int itemId;            /* 0x1C */
    int hasItem;           /* 0x20 */
    unsigned char pad24[0x30];
    int slot;              /* 0x54 */
    int lastSlot;          /* 0x58 */
    int result;            /* 0x5C */
    unsigned char spinning; /* 0x60 */
    unsigned char active;  /* 0x61 */
    unsigned char pad62[0x2];
    int timer;             /* 0x64 */
    unsigned char pad68[0x4];
    int state;             /* 0x6C */
    int queuedItem;        /* 0x70 */
    unsigned char pad74[0x4];
    void *hud;             /* 0x78 */
    unsigned char playSE;  /* 0x7C */
    unsigned char pad7d[0x3];
    int cooldown;          /* 0x80 */
    unsigned char dropped; /* 0x84 */
} ItemSelect;

typedef struct Kart {
    unsigned char pad000[0x2b1];
    unsigned char noItems; /* 0x2B1 */
} Kart;

extern int g_gameMode;
extern unsigned char g_isCommHost;
extern int BattleRoulette_TickAndGetCounter(void);
extern void KartItem_CancelAndQueueDefault(Kart *kart);
extern int KartMovement_GetCurrentItemId(Kart *kart);
extern void SoundMgr_PlaySE(unsigned int id);
extern void fn_8023E19C(void *hud);
extern void fn_8023E1E4(void *hud, int a, int b);

static inline unsigned char ItemSelect_IsBusy(ItemSelect *self, Kart *kart)
{
    if (KartMovement_GetCurrentItemId(kart) != -1) {
        return 1;
    }
    if (self->timer != 0) {
        return 1;
    }
    return 0;
}

static inline void ItemSelect_RollSlot(ItemSelect *self)
{
    self->slot = BattleRoulette_TickAndGetCounter() % 3;
    if (self->slot == self->lastSlot) {
        self->slot = (self->slot + 1) % 3;
    }
}

int ItemSelect_OnDropAllCancel(ItemSelect *self, Kart *kart)
{
    if (self->slot == -1) {
        return 0;
    }
    self->slot = -1;
    self->queuedItem = -1;
    self->state = 0;
    self->timer = 0;
    if (self->hud != 0) {
        fn_8023E1E4(self->hud, -1, 0);
    }
    KartItem_CancelAndQueueDefault(kart);
    self->cooldown = 0x1e;
    self->dropped = 1;
    return 1;
}

int ItemSelect_GiveItemOrQueueDrop(ItemSelect *self, Kart *kart, int item, unsigned char queue)
{
    if (ItemSelect_IsBusy(self, kart) == 1) {
        if (queue == 1 && self->queuedItem == -1) {
            if (KartMovement_GetCurrentItemId(kart) == 0x7a || KartMovement_GetCurrentItemId(kart) == 0xef) {
                self->queuedItem = item;
            }
        }
        return 0;
    }
    self->itemId = item;
    self->hasItem = 1;
    self->slot = 3;
    self->lastSlot = 3;
    self->timer = 1;
    self->active = 1;
    self->state = 1;
    switch (self->itemId) {
    case 0x7b:
    case 0x7c:
    case 0x7d:
    case 0x7e:
    case 0x7f:
    case 0x80:
    case 0x81:
    case 0x82:
    case 0x83:
    case 0x84:
    case 0x85:
    case 0x86:
    case 0x87:
        self->state = 3;
        break;
    }
    return 1;
}

int ItemSelect_StartRouletteSpin(ItemSelect *self, Kart *kart, int unused, int forced)
{
    if (self->queuedItem != -1) {
        return -1;
    }
    if (self->state != 0) {
        return -1;
    }
    if (ItemSelect_IsBusy(self, kart) == 1) {
        return -1;
    }
    if (kart->noItems == 1) {
        return -1;
    }
    if (g_gameMode == 2) {
        if (g_isCommHost == 1) {
            ItemSelect_RollSlot(self);
        } else if (forced > 0) {
            self->slot = forced - 1;
        } else {
            return -1;
        }
    } else {
        ItemSelect_RollSlot(self);
    }
    self->lastSlot = self->slot;
    self->result = -1;
    self->timer = 0x78;
    if (self->hud != 0) {
        fn_8023E19C(self->hud);
    }
    if (self->playSE != 0) {
        SoundMgr_PlaySE(0x4d);
    }
    self->state = -2;
    self->active = 1;
    self->spinning = 1;
    return self->slot;
}
