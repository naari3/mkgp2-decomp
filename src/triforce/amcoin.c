/* Triforce coin chute / credit manager. */
#include <dolphin.h>
#include <stdio.h>
#include <string.h>

typedef struct CoinConfig {
    /* 0x00 */ u8 creditMax;
    /* 0x01 */ u8 serviceMax;
    /* 0x02 */ u8 numPlayers;
    /* 0x03 */ u8 separate;
    /* 0x04 */ u8 commonService;
    /* 0x05 */ u8 serviceSplit;
    /* 0x06 */ u8 coinSetting;
    /* 0x07 */ u8 freePlay;
    /* 0x08 */ u8 coinMul[2];
    /* 0x0A */ u8 bonusDiv;
    /* 0x0B */ u8 coinsPerCredit;
    /* 0x0C */ u8 startCost[8];
    /* 0x14 */ u8 pad[0xC];
} CoinConfig;

typedef struct CoinSlot {
    /* 0x00 */ u32 credit;
    /* 0x04 */ u32 coin;
    /* 0x08 */ u32 perCredit;
    /* 0x0C */ u16 bonus;
    /* 0x0E */ u16 service;
} CoinSlot;

typedef struct CoinStats {
    /* 0x00 */ u32 coins[4];
    /* 0x10 */ u32 totalCoins;
    /* 0x14 */ u32 paidCredits;
    /* 0x18 */ u32 serviceCredits;
    /* 0x1C */ u32 allCredits;
    /* 0x20 */ u32 pad[8];
} CoinStats;

typedef struct CoinChute {
    /* 0x00 */ u16 count[4];
    /* 0x08 */ u32 timer;
    /* 0x0C */ u32 prev;
    /* 0x10 */ u32 hold[4];
} CoinChute;

typedef struct CoinEvent {
    u32 type;
    u32 chute;
    u32 index;
    u32 value;
} CoinEvent;

typedef struct StatusQueue {
    u32 head;
    u32 tail;
    u32 buf[16];
} StatusQueue;

typedef struct EventQueue {
    u32 head;
    u32 tail;
    CoinEvent buf[16];
} EventQueue;

typedef struct CoinTableEntry {
    u32 freePlay;
    u32 mul0;
    u32 mul1;
    u32 bonusDiv;
    u32 perCredit;
} CoinTableEntry;

typedef struct CoinState {
    /* 0x000 */ CoinConfig cfg;
    /* 0x020 */ CoinSlot slot[4];
    /* 0x060 */ CoinStats stats;
    /* 0x0A0 */ u32 dirty[3];
    /* 0x0AC */ u32 numChutes;
    /* 0x0B0 */ u32 chuteMode[3];
    /* 0x0BC */ CoinChute chute[3];
    /* 0x11C */ StatusQueue status;
    /* 0x164 */ EventQueue event;
    /* 0x26C */ OSSemaphore sem;
} CoinState;

static char StrBuf[0x10];
static CoinEvent Event;
static CoinState Coin;

static const CoinConfig DefaultConfig = {
    99, 9, 4, 0, 1, 1, 1, 0, {1, 1}, 0, 1, {1, 1, 1, 1, 1, 1, 1, 1},
};

static const CoinTableEntry CoinTable[11] = {
    {0, 1, 1, 0, 1}, {0, 1, 1, 0, 1}, {0, 1, 1, 0, 2}, {0, 1, 1, 0, 3},
    {0, 1, 1, 0, 4}, {0, 1, 1, 0, 5}, {0, 2, 1, 0, 1}, {0, 3, 1, 0, 1},
    {0, 4, 1, 0, 1}, {0, 5, 1, 0, 1}, {1, 1, 1, 0, 1},
};

u32 fn_8028911C(u32 slot, u32 n);

char* fn_80288CC8(u32 slot) {
    CoinState* st = &Coin;
    OSSemaphore* sem = &st->sem;
    char* ret;
    CoinSlot* s;

    OSWaitSemaphore(sem);
    if (st->cfg.freePlay == 1) {
        ret = NULL;
    } else {
        if (st->cfg.separate == 0) {
            slot = 0;
        }
        s = &Coin.slot[slot];
        StrBuf[0] = 0;
        if (s->perCredit <= 1 || s->credit != 0) {
            sprintf(StrBuf, "%s%d ", StrBuf, s->credit);
        }
        if (s->perCredit > 1 && (s->credit == 0 || s->coin != 0)) {
            sprintf(StrBuf, "%s%d/%d", StrBuf, s->coin, s->perCredit);
        }
        ret = StrBuf;
    }
    OSSignalSemaphore(sem);
    return ret;
}

BOOL fn_80288DEC(u32 type, u32 chute, u32 index, u32 value) {
    OSSemaphore* sem = &Coin.sem;
    EventQueue* q = &Coin.event;
    BOOL full;
    CoinEvent* e;

    OSWaitSemaphore(sem);
    if (q->tail == q->head - 1 || (q->tail == 15 && q->head == 0)) {
        full = TRUE;
    } else {
        full = FALSE;
        e = &q->buf[q->tail];
        e->type = type;
        e->chute = chute;
        e->index = index;
        e->value = value;
        if (++q->tail >= 16) {
            q->tail = 0;
        }
    }
    OSSignalSemaphore(sem);
    return full;
}

CoinEvent* fn_80288EAC(void) {
    OSSemaphore* sem = &Coin.sem;
    EventQueue* q = &Coin.event;
    CoinEvent* ret = NULL;

    OSWaitSemaphore(sem);
    if (q->head != q->tail) {
        Event = q->buf[q->head];
        if (++q->head >= 16) {
            q->head = 0;
        }
        ret = &Event;
    }
    OSSignalSemaphore(sem);
    return ret;
}

u32 fn_80289040(u32 slot, u32 game);

BOOL fn_80288F6C(u32 slot, u32 game) {
    CoinConfig* cfg = &Coin.cfg;
    OSSemaphore* sem;
    CoinSlot* s;

    if (fn_80289040(slot, game) == 2) {
        sem = &Coin.sem;
        OSWaitSemaphore(sem);
        if (cfg->separate == 0) {
            slot = 0;
        }
        s = &Coin.slot[slot];
        if (cfg->freePlay != 1) {
            s->credit -= cfg->startCost[game];
            s->bonus = 0;
            Coin.dirty[1] = 1;
        }
        OSSignalSemaphore(sem);
        return TRUE;
    }
    return FALSE;
}

u32 fn_80289040(u32 slot, u32 game) {
    CoinConfig* cfg = &Coin.cfg;
    OSSemaphore* sem = &Coin.sem;
    u32 ret = 0;
    CoinSlot* s;

    OSWaitSemaphore(sem);
    if (slot <= Coin.cfg.numPlayers - 1 && game <= 7) {
        if (cfg->separate == 0) {
            slot = 0;
        }
        s = &Coin.slot[slot];
        if (cfg->freePlay == 1 || s->credit >= cfg->startCost[game]) {
            ret = 2;
        } else if (s->credit != 0 || s->coin != 0) {
            ret = 1;
        } else {
            ret = 0;
        }
    }
    OSSignalSemaphore(sem);
    return ret;
}

static inline void PushStatus(OSSemaphore* sem, u32 status) {
    StatusQueue* q = &Coin.status;

    OSWaitSemaphore(sem);
    if (q->tail != q->head - 1 && (q->tail != 15 || q->head != 0)) {
        q->buf[q->tail] = status;
        if (++q->tail >= 16) {
            q->tail = 0;
        }
    }
    OSSignalSemaphore(sem);
}

static inline u32 AddService(CoinConfig* cfg, u32 slot, u32 n) {
    CoinSlot* s = &Coin.slot[slot];
    u32 prev = s->credit;

    if (s->service < cfg->serviceMax && prev < cfg->creditMax) {
        s->service++;
        s->credit += n;
        if (s->credit >= cfg->creditMax) {
            s->credit = cfg->creditMax;
            s->coin = 0;
        }
    }
    prev = s->credit - prev;
    return prev;
}

u32 fn_8028911C(u32 slot, u32 n) {
    CoinConfig* cfg = &Coin.cfg;
    OSSemaphore* sem = &Coin.sem;
    u32 status = 0;
    u32 added = 0;
    u32 prev;
    CoinSlot* s;

    OSWaitSemaphore(sem);
    if (Coin.cfg.freePlay != 1) {
        if (cfg->separate == 1 && cfg->commonService == 0) {
            for (slot = 0; slot < cfg->numPlayers; slot++) {
                s = &Coin.slot[slot];
                prev = s->credit;
                if (Coin.slot[0].service < cfg->serviceMax && prev < cfg->creditMax) {
                    s->credit = prev + n;
                    if (s->credit >= cfg->creditMax) {
                        s->credit = cfg->creditMax;
                        s->coin = 0;
                    }
                }
                added += s->credit - prev;
            }
            if (added != 0) {
                Coin.slot[0].service++;
            }
        } else {
            added = AddService(cfg, slot, n);
        }
        Coin.dirty[1] = 1;
        if (added != 0) {
            status = 2;
        }
    }
    OSSignalSemaphore(sem);
    if (status != 0) {
        PushStatus(sem, status);
    }
    return added;
}

s32 fn_80289324(u32 slot, u32 coins) {
    CoinConfig* cfg = &Coin.cfg;
    OSSemaphore* sem;
    CoinSlot* s;
    u32 status;
    s32 added;
    u32 prev;
    u32 bonus;
    u32 credits;
    u32 n;

    status = 0;
    s = &Coin.slot[slot];
    sem = &Coin.sem;
    added = 0;

    OSWaitSemaphore(sem);
    if (cfg->freePlay != 1) {
        bonus = 0;
        prev = s->credit;
        if (cfg->bonusDiv != 0) {
            bonus = (s->bonus + coins) / cfg->bonusDiv;
            s->bonus = (s->bonus + coins) % cfg->bonusDiv;
        }
        credits = (coins + bonus + s->coin) / cfg->coinsPerCredit;
        s->coin = (coins + bonus + s->coin) % cfg->coinsPerCredit;
        s->credit += credits;
        if (s->credit >= cfg->creditMax) {
            s->credit = cfg->creditMax;
            s->coin = 0;
        }
        if (cfg->separate == 1 && cfg->commonService == 0) {
            Coin.slot[0].service = 0;
        } else {
            s->service = 0;
        }
        Coin.dirty[1] = 1;
        if (prev < cfg->creditMax) {
            if (credits != 0) {
                status = 2;
            } else if (coins != 0) {
                status = 1;
            }
        }
        added = s->credit - prev;
    }
    OSSignalSemaphore(sem);
    if (status != 0) {
        PushStatus(sem, status);
    }
    return added;
}

u32 fn_802894EC(u32 chute, u32 index) {
    CoinState* st = &Coin;
    OSSemaphore* sem = &st->sem;
    u32 slot;
    u32 mode;

    OSWaitSemaphore(sem);
    if (Coin.cfg.separate == 0) {
        slot = 0;
    } else {
        if (!(chute <= 2)) {
            chute = 1;
        }
        mode = Coin.chuteMode[chute];
        switch (mode & ~0xF) {
        case 0x10:
            slot = mode & 0xF;
            break;
        case 0x20:
            slot = (mode & 0xF) + index;
            break;
        default:
            slot = 0;
            break;
        }
    }
    if (slot >= st->cfg.numPlayers) {
        slot = 0;
    }
    OSSignalSemaphore(sem);
    return slot;
}

static inline u32 GetCoinMul(OSSemaphore* sem, s32 i) {
    CoinConfig* cfg = &Coin.cfg;
    u32 mul;

    OSWaitSemaphore(sem);
    if (Coin.cfg.separate == 1) {
        mul = cfg->coinMul[0];
    } else {
        mul = cfg->coinMul[i & 1];
    }
    OSSignalSemaphore(sem);
    return mul;
}

static inline void AddCoinStats(OSSemaphore* sem, u32 buttons, u32 idx, s32 coins, s32 credits) {
    CoinStats* stats = &Coin.stats;

    if (!(buttons & 0x80000000) && idx <= 3) {
        OSWaitSemaphore(sem);
        stats->coins[idx] += coins;
        stats->totalCoins += coins;
        stats->paidCredits += credits;
        stats->allCredits += credits;
        Coin.dirty[2] = 1;
        OSSignalSemaphore(sem);
    }
}

s32 fn_802895E4(u32 chute, s32 n, u16* counters, u32 buttons) {
    u32 idx;
    s32 added;
    OSSemaphore* sem;
    s32 i;
    CoinState* st = &Coin;
    s32 d;
    CoinChute* c;
    u32 slot;
    u32 bits;

    if (chute > st->numChutes || (chute != 0 && counters == NULL)) {
        return 1;
    }
    c = &Coin.chute[chute];
    if (chute != 0 && Coin.chuteMode[chute] != 0) {
        if (n > 4) {
            n = 4;
        }
        sem = &Coin.sem;
        for (i = 0; i < n; i++) {
            if (!((counters[i] | c->count[i]) & ~0x3FFF)) {
                d = (counters[i] - c->count[i]) & 0xFFF;
                if (d > 0) {
                    slot = fn_802894EC(chute, i);
                    idx = i;
                    if (chute == 2) {
                        idx = i + 2;
                    }
                    added = fn_80289324(slot, d * GetCoinMul(sem, i));
                    AddCoinStats(sem, buttons, idx, d, added);
                    if (!(counters[i] & 0xFFF)) {
                        fn_80288DEC(1, chute, i + 1, counters[i] & ~0xFFF);
                    }
                }
            }
            c->count[i] = counters[i];
        }
    }
    if (chute == 0 && Coin.chuteMode[chute] != 0) {
        sem = &Coin.sem;
        for (i = 0; i < 4; i++) {
            if ((1 << i) & (c->prev & ~buttons)) {
                slot = fn_802894EC(chute, i);
                added = fn_80289324(slot, GetCoinMul(sem, i));
                AddCoinStats(sem, buttons, i, 1, added);
                if (st->cfg.serviceSplit == 0) {
                    c->count[0]++;
                } else {
                    c->count[i]++;
                }
            }
        }
        if (c->timer == 0) {
            bits = 0;
            for (i = 0; i < 4; i++) {
                if (c->count[i] != 0) {
                    c->count[i]--;
                    bits |= 1 << i;
                }
            }
            if (bits != 0) {
                fn_80288DEC(2, 0, bits, 0);
                c->timer = 13;
            }
        } else {
            c->timer--;
        }
    }
    if (Coin.chuteMode[chute] != 0) {
        sem = &Coin.sem;
        for (i = 0; i < 4; i++) {
            if (buttons & (1 << (i + 4))) {
                if (++c->hold[i] == 7) {
                    added = fn_8028911C(fn_802894EC(chute, i), 1);
                    if (!(buttons & 0x80000000)) {
                        OSWaitSemaphore(sem);
                        Coin.stats.serviceCredits += added;
                        Coin.stats.allCredits += added;
                        Coin.dirty[2] = 1;
                        OSSignalSemaphore(sem);
                    }
                }
            } else {
                c->hold[i] = 0;
            }
        }
    }
    c->prev = buttons;
    return 0;
}

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

s32 fn_8028A3EC(CoinConfig* dst, u8* src) {
    CoinConfig tmp;
    const CoinTableEntry* t;
    u8 flags;

    if (src == NULL || dst == NULL) {
        return 1;
    }
    memcpy(&tmp, dst, sizeof(CoinConfig));
    if (src[0] == 0) {
        return 0;
    }
    flags = src[1];
    if (flags & 2) {
        tmp.separate = flags & 1;
    }
    flags >>= 2;
    if (flags & 2) {
        tmp.commonService = flags & 1;
    }
    flags >>= 2;
    if (flags & 2) {
        tmp.serviceSplit = flags & 1;
    }
    tmp.coinSetting = src[3];
    if (tmp.coinSetting == 10) {
        tmp.freePlay = 1;
    } else {
        tmp.freePlay = 0;
    }
    tmp.coinMul[0] = src[4];
    tmp.coinMul[1] = src[5];
    tmp.bonusDiv = src[6];
    tmp.coinsPerCredit = src[7];
    if (tmp.coinSetting != 0) {
        t = &CoinTable[tmp.coinSetting];
        tmp.coinMul[0] = t->mul0;
        if (tmp.separate == 0 && t->perCredit != 1) {
            tmp.coinMul[1] = t->mul1;
        }
        tmp.bonusDiv = t->bonusDiv;
        tmp.coinsPerCredit = t->perCredit;
    }
    tmp.startCost[0] = src[8];
    tmp.startCost[1] = src[9];
    tmp.startCost[2] = src[10];
    tmp.startCost[3] = src[11];
    tmp.startCost[4] = src[12];
    tmp.startCost[5] = src[13];
    tmp.startCost[6] = src[14];
    tmp.startCost[7] = src[15];
    if (!fn_80289ED8(&tmp)) {
        return 2;
    }
    memcpy(dst, &tmp, sizeof(CoinConfig));
    return 0;
}
