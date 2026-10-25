typedef struct KartCond {
    signed char mode;
    signed char cup;
    signed char ccClass;
    signed char round;
    signed char kart;
} KartCond;

typedef struct HitCooldownEntry {
    KartCond cond;
    int cooldown;
} HitCooldownEntry;

extern int g_gameMode;
extern int g_cupId;
extern int g_ccClass;
extern int g_roundIndex;
extern int lbl_806CFF18;
extern HitCooldownEntry lbl_804E3D4C[];

static inline unsigned char KartCond_Matches(KartCond c, int kart) {
    if (c.mode != -1 && c.mode != g_gameMode) {
        return 0;
    }
    if (c.cup != -1 && c.cup != g_cupId) {
        return 0;
    }
    if (c.ccClass != -1 && c.ccClass != g_ccClass) {
        return 0;
    }
    if (c.round != -1 && c.round != g_roundIndex) {
        return 0;
    }
    if (c.kart != -1 && kart != -1 && c.kart != kart) {
        return 0;
    }
    return 1;
}

int AI_GetHitCooldown(int kart) {
    int i;

    for (i = 0; i < lbl_806CFF18; i++) {
        if (KartCond_Matches(lbl_804E3D4C[i].cond, kart)) {
            return lbl_804E3D4C[i].cooldown;
        }
    }
    return 0;
}
