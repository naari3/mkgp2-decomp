/*
 * 0x802161C4..0x80216540: coin bonus getters and the coin milestone
 * unlock check (each milestone is a mileage threshold that can unlock
 * an item for the current character).
 */

#include "game/CoinMilestone.h"

extern int g_extraCoinsToAdd;
extern int g_coinMilageBeforeRace;
extern int extraBattleBonus;
extern int battleBonus;
extern int positionBonus;
extern int winBonus;
extern int baseCoins;
extern int g_earnedCoins;
extern int g_characterId;

extern int lbl_80679BA4[57];
extern int lbl_806D1A48;
extern const char lbl_803C4B4C[];

int GetCoinMilage(void *playerData);
void fn_80209338(int character);
int fn_80209330(void);
void fn_801D5F74(void *playerData, int id, int on);
void DebugPrintf(const char *fmt, ...);

void SetCoinCount(int n) {
    g_extraCoinsToAdd = n;
}

int fn_802161CC(void) {
    return g_coinMilageBeforeRace;
}

int fn_802161D4(void) {
    return extraBattleBonus;
}

int fn_802161DC(void) {
    return battleBonus;
}

int GetCoinCount(void) {
    return g_extraCoinsToAdd;
}

int fn_802161EC(void) {
    return positionBonus;
}

int fn_802161F4(void) {
    return winBonus;
}

int fn_802161FC(void) {
    return baseCoins;
}

int GetEarnedCoins(void) {
    return g_earnedCoins;
}

int fn_8021620C(void) {
    if (lbl_806D1A48 >= 56) {
        return -1;
    }
    return lbl_80679BA4[lbl_806D1A48++];
}

static CoinMilestone *GetMilestone(int i) {
    if (i < 0) {
        return 0;
    }
    if (i >= 93) {
        return 0;
    }
    return &lbl_80679748[i];
}

static int FindMilestone(int mileage) {
    int i;
    for (i = 0; i < 93; i++) {
        if (mileage < lbl_80679748[i].threshold) {
            return i;
        }
    }
    return -1;
}

void CheckCoinMilestones(void *playerData, int add) {
    int i;
    int count;
    int end;
    int index;
    CoinMilestone *m;
    int mileage;

    for (i = 0; i < 57; i++) {
        lbl_80679BA4[i] = -1;
    }
    lbl_806D1A48 = 0;
    count = 0;
    end = add + GetCoinMilage(playerData);
    index = FindMilestone(GetCoinMilage(playerData));
    m = GetMilestone(index);
    if (m == 0) {
        return;
    }
    for (mileage = GetCoinMilage(playerData); mileage <= end; mileage++) {
        if (mileage >= m->threshold) {
            if (m->type == 1) {
                int id;
                fn_80209338(g_characterId);
                id = fn_80209330();
                if (id < 0) {
                    id = 0;
                    DebugPrintf(lbl_803C4B4C, mileage, 323);
                } else {
                    fn_801D5F74(playerData, id, 1);
                }
                lbl_80679BA4[count++] = id;
            }
            m = GetMilestone(++index);
            if (m == 0) {
                return;
            }
        }
    }
    lbl_80679BA4[count] = -1;
}

void fn_8021651C(void *playerData) {
    CheckCoinMilestones(playerData, g_earnedCoins);
}
