#include <triforce/amcoin_private.h>
#include <stdio.h>
#include <string.h>

s32 fn_80289A90(CoinStats* stats) {
    OSSemaphore* sem;

    if (stats == NULL) {
        return 1;
    }
    sem = &Coin.sem;
    OSWaitSemaphore(sem);
    memcpy(stats, &Coin.stats, sizeof(CoinStats));
    OSSignalSemaphore(sem);
    return 0;
}

s32 fn_80289B04(CoinSlot* slots) {
    OSSemaphore* sem;

    if (slots == NULL) {
        return 1;
    }
    sem = &Coin.sem;
    OSWaitSemaphore(sem);
    memcpy(slots, Coin.slot, Coin.cfg.numPlayers * sizeof(CoinSlot));
    OSSignalSemaphore(sem);
    return 0;
}

s32 fn_80289B7C(CoinConfig* cfg) {
    OSSemaphore* sem;

    if (cfg == NULL) {
        return 1;
    }
    sem = &Coin.sem;
    OSWaitSemaphore(sem);
    memcpy(cfg, &Coin.cfg, sizeof(CoinConfig));
    OSSignalSemaphore(sem);
    return 0;
}

u32 fn_80289BEC(u32 i) {
    OSSemaphore* sem;
    u32 ret;

    if (i > 2) {
        return 0;
    }
    sem = &Coin.sem;
    OSWaitSemaphore(sem);
    ret = Coin.dirty[i];
    Coin.dirty[i] = 0;
    OSSignalSemaphore(sem);
    return ret;
}

s32 fn_80289C68(u32 mode1, u32 mode2) {
    OSSemaphore* sem = &Coin.sem;

    OSWaitSemaphore(sem);
    Coin.numChutes = 0;
    Coin.chuteMode[0] = 0x20;
    OSSignalSemaphore(sem);
    if (mode1 == 0) {
        return 0;
    }
    OSWaitSemaphore(sem);
    Coin.numChutes = 1;
    Coin.chuteMode[1] = mode1;
    OSSignalSemaphore(sem);
    if (mode2 == 0) {
        return 0;
    }
    OSWaitSemaphore(sem);
    Coin.numChutes = 2;
    Coin.chuteMode[2] = mode2;
    OSSignalSemaphore(sem);
    return 0;
}

s32 fn_80289D4C(u8 max) {
    CoinConfig* cfg = &Coin.cfg;
    OSSemaphore* sem;
    CoinSlot* slots = Coin.slot;
    s32 i;

    if (max < 9 || max > 99) {
        return 1;
    }
    sem = &Coin.sem;
    OSWaitSemaphore(sem);
    cfg->creditMax = max;
    Coin.dirty[0] = 1;
    for (i = 0; i < cfg->numPlayers; i++) {
        if (slots[i].credit > cfg->creditMax) {
            slots[i].credit = cfg->creditMax;
            slots[i].coin = 0;
            Coin.dirty[1] = 1;
        }
    }
    OSSignalSemaphore(sem);
    return 0;
}

s32 fn_80289E20(void) {
    memset(&Coin, 0, sizeof(CoinState));
    return 0;
}

BOOL fn_80289E54(CoinSlot* slots, CoinConfig* cfg) {
    CoinSlot* s;
    s32 i;

    if (slots == NULL || cfg == NULL) {
        return FALSE;
    }
    for (i = 0, s = slots; i < cfg->numPlayers; i++, s++) {
        if (cfg->coinsPerCredit != s->perCredit) {
            return FALSE;
        }
    }
    for (i = 0; i < cfg->numPlayers; i++) {
        if (slots->credit > cfg->creditMax) {
            slots->credit = cfg->creditMax;
        }
        slots++;
    }
    return TRUE;
}

BOOL fn_80289ED8(CoinConfig* cfg) {
    const CoinTableEntry* t;
    u8 bonusDiv;
    u8 freePlay;
    u8 setting;
    u8 mul0;
    u8 separate;
    u8 perCredit;
    u8 mul1;

    if (cfg == NULL) {
        return FALSE;
    }
    if (cfg->creditMax < 9 || cfg->creditMax > 99) {
        return FALSE;
    }
    if (cfg->numPlayers < 1 || cfg->numPlayers > 4) {
        return FALSE;
    }
    if (cfg->serviceMax < 1 || cfg->serviceMax > 99) {
        return FALSE;
    }
    separate = cfg->separate;
    if (separate > 1) {
        return FALSE;
    }
    if (cfg->commonService > 1) {
        return FALSE;
    }
    if (cfg->serviceSplit > 1) {
        return FALSE;
    }
    setting = cfg->coinSetting;
    if (setting > 10) {
        return FALSE;
    }
    freePlay = cfg->freePlay;
    if (freePlay > 1) {
        return FALSE;
    }
    mul0 = cfg->coinMul[0];
    if (mul0 < 1 || mul0 > 9) {
        return FALSE;
    }
    mul1 = cfg->coinMul[1];
    if (mul1 < 1 || mul1 > 9) {
        return FALSE;
    }
    bonusDiv = cfg->bonusDiv;
    if (bonusDiv > 9 || bonusDiv == 1) {
        return FALSE;
    }
    perCredit = cfg->coinsPerCredit;
    if (perCredit < 1 || perCredit > 9) {
        return FALSE;
    }
    if (cfg->startCost[0] < 1 || cfg->startCost[0] > 9) {
        return FALSE;
    }
    if (cfg->startCost[1] < 1 || cfg->startCost[1] > 9) {
        return FALSE;
    }
    if (cfg->startCost[2] < 1 || cfg->startCost[2] > 9) {
        return FALSE;
    }
    if (cfg->startCost[3] < 1 || cfg->startCost[3] > 9) {
        return FALSE;
    }
    if (cfg->startCost[4] < 1 || cfg->startCost[4] > 9) {
        return FALSE;
    }
    if (cfg->startCost[5] < 1 || cfg->startCost[5] > 9) {
        return FALSE;
    }
    if (cfg->startCost[6] < 1 || cfg->startCost[6] > 9) {
        return FALSE;
    }
    if (cfg->startCost[7] < 1 || cfg->startCost[7] > 9) {
        return FALSE;
    }
    t = &CoinTable[setting];
    if (freePlay != t->freePlay) {
        return FALSE;
    }
    if (setting != 0 &&
        (mul0 != t->mul0 || (separate == 0 && perCredit != 1 && mul1 != t->mul1) ||
         bonusDiv != t->bonusDiv || perCredit != t->perCredit))
    {
        return FALSE;
    }
    return TRUE;
}

s32 fn_8028A16C(CoinConfig* cfg, CoinSlot* slots, CoinStats* stats) {
    s32 ret = 0;
    s32 i;
    s32 n;
    CoinChute* c;

    memset(&Coin, 0, sizeof(CoinState));
    OSInitSemaphore(&Coin.sem, 1);
    for (i = 0; i < 3; i++) {
        c = &Coin.chute[i];
        Coin.chuteMode[i] = 0x20;
        if (i == 0) {
            c->count[0] = 0;
            c->count[1] = 0;
            c->count[2] = 0;
            c->count[3] = 0;
        } else {
            c->count[0] = 0x8000;
            c->count[1] = 0x8000;
            c->count[2] = 0x8000;
            c->count[3] = 0x8000;
        }
        c->timer = 13;
    }
    if (cfg != NULL) {
        memcpy(&Coin.cfg, cfg, sizeof(CoinConfig));
    }
    if (cfg == NULL || !fn_80289ED8(&Coin.cfg)) {
        Coin.dirty[0] = 1;
        ret = 2;
        memcpy(&Coin.cfg, &DefaultConfig, sizeof(CoinConfig));
    }
    n = Coin.cfg.numPlayers;
    if (slots != NULL) {
        memcpy(Coin.slot, slots, n * sizeof(CoinSlot));
    }
    if (ret == 2 || !fn_80289E54(Coin.slot, &Coin.cfg)) {
        Coin.dirty[1] = 1;
        memset(Coin.slot, 0, n * sizeof(CoinSlot));
        for (i = 0; i < n; i++) {
            Coin.slot[i].perCredit = Coin.cfg.coinsPerCredit;
        }
    }
    if (stats == NULL) {
        Coin.dirty[2] = 1;
    } else {
        memcpy(&Coin.stats, stats, sizeof(CoinStats));
    }
    return ret;
}

