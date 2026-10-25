/* ItemCollision_Check (0x800DD1EC): resolve the item's hit-registry slot to
 * the kart it touched and classify the contact from the kart's status flags.
 * Returns 0 (no contact), 1 (hit), 2 (blocked/guarded), 3, or 5 (lost).
 * C++ for the virtual-call sequence (lwz r12; lwz r12, 0xC(r12)).
 * NonMatching (99.8%): the owner team id and the RankLog pointer swap
 * callee-saved registers (r29/r27). */
typedef struct Vec { float x, y, z; } Vec;

typedef struct ItemClassEntry {
    unsigned char pad0[8];
    float radius;
    unsigned char padC[8];
} ItemClassEntry;

struct ItemHitSink {
    virtual void f0();
    virtual void onHit(void *kart, int kind); /* vtable +0xC */
};

extern "C" {
extern ItemClassEntry lbl_8041AC24[];
extern void *lbl_806D10A0;

extern void *GetRaceContextPtr(void);
extern unsigned char *RaceContextSlot_GetIfAlive(void *ctx, int idx);
extern void SoundMgr_PlaySE_Positional(int se, Vec pos, int ch);
extern void ItemEffectBus_OrMask(void *bus, unsigned long long mask);
extern void ItemHit_CommonKnockdown(void *owner, int arg);
extern signed char ItemClass_GetFlagByte1(int idx);
extern void RankLog_OnOpponentDefeated(void *log, int team, int flag);
}

#define F(o) (*(float *)(self + (o)))
#define S8(o) (*(signed char *)(self + (o)))
#define U32(o) (*(unsigned int *)(self + (o)))
#define P(o) (*(unsigned char **)(self + (o)))
#define KIND (*(int *)(self + 0x8))
#define FLAGS(st) (*(unsigned long long *)((st) + 0x10))

static inline void Timer_Tick(unsigned int *t)
{
    if (*t != 0) {
        (*t)--;
    }
}

static inline int ItemCollision_IsContactActive(unsigned char *self)
{
    int slot;
    float r;

    if (self == 0) {
        return 0;
    }
    if (S8(0x174) == 0) {
        return 0;
    }
    slot = *(int *)(self + 0x170);
    if (slot == -1) {
        return 0;
    }
    r = 0.05f * (F(0xC4) * lbl_8041AC24[self[0x1C]].radius);
    if (r < 1.0f) {
        r = 1.0f;
    }
    *(float *)(RaceContextSlot_GetIfAlive(GetRaceContextPtr(), slot) + 0xA4) = r;
    if (*(int *)(RaceContextSlot_GetIfAlive(GetRaceContextPtr(), *(int *)(self + 0x170)) + 0x8) == 3) {
        if (*(char *)(self + 0x174) == 1) {
            return 1;
        }
        return 0;
    }
    return 0;
}

static inline unsigned char *ItemCollision_GetContactKart(unsigned char *self)
{
    int slot;

    if (self == 0) {
        return 0;
    }
    if (S8(0x174) == 0) {
        return 0;
    }
    slot = *(int *)(self + 0x170);
    if (slot == -1) {
        return 0;
    }
    return *(unsigned char **)(RaceContextSlot_GetIfAlive(GetRaceContextPtr(), slot) + 0xB8);
}

static inline unsigned char ItemCollision_HasFlag(unsigned char *st, unsigned long long mask)
{
    unsigned char r;

    if ((FLAGS(st) & mask) == 0) {
        r = 0;
    } else {
        r = 1;
    }
    return r;
}

static inline int ItemCollision_Classify(unsigned char *kart)
{
    unsigned char *st = *(unsigned char **)(kart + 0x304);

    if (ItemCollision_HasFlag(st, 0x0080000000000000ULL)) {
        return 2;
    }
    if (FLAGS(st) & 0x0100000000000000ULL) {
        return 2;
    }
    if (FLAGS(st) & 0x40) {
        return 2;
    }
    if (FLAGS(st) & 0x400) {
        return 3;
    }
    if (FLAGS(st) & 0x80) {
        return 5;
    }
    return 1;
}

static inline void *RankLog_Get(void)
{
    void *p = lbl_806D10A0;

    if (p == 0) {
        p = 0;
    }
    return p;
}

static inline void ItemCollision_LogDefeat(unsigned char *self, int team)
{
    void *log = RankLog_Get();

    if (log != 0 && team >= 0 && team <= 3) {
        int t = *(int *)(P(0x184) + 0x1F4);
        RankLog_OnOpponentDefeated(log, t, ItemClass_GetFlagByte1(KIND));
    }
}

static inline int ItemCollision_IsRacer(unsigned char *kart)
{
    if (kart == 0) {
        return 0;
    }
    switch (*(int *)(kart + 0x1F4)) {
    case 0:
        return 1;
    case 1:
        return 1;
    case 2:
        return 1;
    case 3:
        return 1;
    }
    return 0;
}

extern "C" int ItemCollision_Check(unsigned char *self)
{
    unsigned char *kart;
    int result;
    unsigned char *st;
    int team;

    if (self == 0) {
        return 0;
    }
    Timer_Tick((unsigned int *)(self + 0x178));
    if (!ItemCollision_IsContactActive(self)) {
        return 0;
    }
    kart = ItemCollision_GetContactKart(self);
    if (kart == 0) {
        return 5;
    }
    result = ItemCollision_Classify(kart);
    st = *(unsigned char **)(kart + 0x304);
    if (self != 0 && kart != 0) {
        switch (result) {
        case 2:
            if (FLAGS(st) & 0x40) {
                SoundMgr_PlaySE_Positional(0xD4, *(Vec *)(self + 0xA0), 0);
            }
        case 3:
            if (st != 0) {
                ItemEffectBus_OrMask(st, 0x8000000000000000ULL);
            }
            break;
        case 1:
            if (S8(0x17C) == 0 || U32(0x178) != 0) {
                if (P(0x184) != 0) {
                    team = *(int *)(P(0x184) + 0x1F4);
                    if (team != *(int *)(kart + 0x1F4)) {
                        ItemHit_CommonKnockdown(P(0x184), *(int *)(kart + 0x248));
                    }
                    (*(ItemHitSink **)(P(0x184) + 0x308))->onHit(kart, KIND);
                    ItemCollision_LogDefeat(self, team);
                }
            }
            break;
        }
    }
    if (*(unsigned char *)(kart + 0x2B8) != 0) {
        if (ItemCollision_IsRacer(kart)) {
            return 2;
        }
    }
    return result;
}
