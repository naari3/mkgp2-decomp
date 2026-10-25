/* Apply a hit item's effect to its target kart: mode 2/3 raise the
 * target's effect-bus spin flag (2 also plays the positional hit SE),
 * mode 1 knocks the target down, notifies the owner's item handler and
 * logs the defeat for rank tracking. */
#pragma cplusplus on

struct Vec3 {
    float x, y, z;
};

struct ItemHandler {
    virtual void Slot08();
    virtual void OnHit(void *target, int kind);
};

struct EffectBus {
    unsigned char pad00[0x10];
    unsigned long long flags;    /* 0x10 */
};

extern "C" {
void SoundMgr_PlaySE_Positional(int id, Vec3 pos, int flags);
void ItemEffectBus_OrMask(EffectBus *bus, unsigned long long mask);
void ItemHit_CommonKnockdown(unsigned char *owner, void *arg);
signed char ItemClass_GetFlagByte1(int kind);
void RankLog_OnOpponentDefeated(void *log, int team, int flag);
extern void *lbl_806D10A0;
}

static inline void *RankLog_Get(void)
{
    void *log = lbl_806D10A0;
    if (log == 0) {
        log = 0;
    }
    return log;
}

extern "C" void KartItem_ApplyEffectToTarget(unsigned char *item, unsigned char *target, int mode)
{
    EffectBus *bus;

    if (item == 0 || target == 0) {
        return;
    }
    bus = *(EffectBus **)(target + 0x304);
    switch (mode) {
    case 2:
        if (bus->flags & 0x40) {
            SoundMgr_PlaySE_Positional(0xD4, *(Vec3 *)(item + 0xA0), 0);
        }
    case 3:
        if (bus != 0) {
            ItemEffectBus_OrMask(bus, 0x8000000000000000ULL);
        }
        break;
    case 1: {
        int ownerTeam;
        unsigned char *owner;
        int team;
        void *log;

        if (*(signed char *)(item + 0x17C) && *(unsigned int *)(item + 0x178) == 0) {
            break;
        }
        owner = *(unsigned char **)(item + 0x184);
        if (owner == 0) {
            break;
        }
        team = *(int *)(owner + 0x1F4);
        if (team != *(int *)(target + 0x1F4)) {
            ItemHit_CommonKnockdown(owner, *(void **)(target + 0x248));
        }
        (*(ItemHandler **)(*(unsigned char **)(item + 0x184) + 0x308))->OnHit(target, *(int *)(item + 0x8));
        log = RankLog_Get();
        if (log != 0 && team >= 0 && team <= 3) {
            ownerTeam = *(int *)(*(unsigned char **)(item + 0x184) + 0x1F4);
            RankLog_OnOpponentDefeated(log, ownerTeam, ItemClass_GetFlagByte1(*(int *)(item + 0x8)));
        }
        break;
    }
    }
}
#pragma cplusplus off
