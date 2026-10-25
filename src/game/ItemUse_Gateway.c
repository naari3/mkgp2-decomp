typedef struct ItemFlags {
    unsigned char pad[0x10];
    unsigned long long flags;
} ItemFlags;

typedef struct KartMovementView {
    unsigned char pad[0x304];
    ItemFlags *itemFlags;
} KartMovementView;

typedef struct ItemGuardHolder {
    unsigned char pad[4];
    void *guard;
} ItemGuardHolder;

typedef struct KartItemUser {
    unsigned char pad_00[0x10];
    int player;
    unsigned char pad_14[0x18];
    KartMovementView *movement;
    unsigned char pad_30[0x10];
    ItemGuardHolder *guards;
    unsigned char pad_44[0xC];
    void *carObject;
    void *slot;
} KartItemUser;

extern void *lbl_806D10A0;
extern unsigned char Field4NotMinusOne(void *);
extern unsigned char ItemStateGuard_IsActive(void *);
extern unsigned char KartMovement_CanReceiveItem(void *, int);
extern int CarObject_HandleItemEffect(void *, int);
extern unsigned char RenderObj_UseItem(void *, unsigned char, unsigned char);
extern signed char ItemClass_GetFlagByte1(int);
extern void RankLog_OnPlayerVictory(void *, int, int);

static inline unsigned char has_flag(ItemFlags *flags, unsigned long long mask) {
    unsigned char result;

    if ((flags->flags & mask) == 0) {
        result = 0;
    } else {
        result = 1;
    }
    return result;
}

static inline void *rank_log(void) {
    void *log = lbl_806D10A0;

    if (log == 0) {
        return 0;
    }
    return log;
}

int ItemUse_Gateway(KartItemUser *kart, int item, float distance) {
    int effect;
    unsigned char strong;
    unsigned char close;
    void *log;

    if (Field4NotMinusOne(kart->slot) == 1) {
        return 0;
    }
    if (has_flag(kart->movement->itemFlags, 0x40000000) == 1) {
        return 0;
    }
    if (ItemStateGuard_IsActive(kart->guards->guard) == 1) {
        return 0;
    }
    if (item == 0x7D) {
        item = 0x17;
    }
    if (!KartMovement_CanReceiveItem(kart->movement, 1)) {
        return 0;
    }
    effect = CarObject_HandleItemEffect(kart->carObject, item);
    if (effect == 1) {
        return 0;
    }
    strong = 0;
    close = 0;
    if (effect == 2) {
        strong = 1;
    }
    if (distance < 0.1f) {
        close = 1;
    }
    if (!RenderObj_UseItem(kart->movement, strong, close)) {
        return 0;
    }
    log = rank_log();
    if (log != 0 && item < 0x115) {
        RankLog_OnPlayerVictory(log, kart->player, ItemClass_GetFlagByte1(item));
    }
    return 1;
}
