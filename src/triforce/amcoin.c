#include <triforce/amcoin_private.h>
#include <stdio.h>
#include <string.h>

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
            sprintf(StrBuf, lbl_806DC920, StrBuf, s->credit);
        }
        if (s->perCredit > 1 && (s->credit == 0 || s->coin != 0)) {
            sprintf(StrBuf, lbl_806DC928, StrBuf, s->coin, s->perCredit);
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

