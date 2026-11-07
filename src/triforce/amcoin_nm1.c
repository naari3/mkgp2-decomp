#include <triforce/amcoin_private.h>
#include <stdio.h>
#include <string.h>

static inline u32 GetCoinMul(s32 i) {
    CoinConfig* cfg = &Coin.cfg;
    OSSemaphore* sem = &Coin.sem;
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

static inline void AddCoinStats(u32 buttons, u32 idx, s32 coins, s32 credits) {
    CoinStats* stats = &Coin.stats;
    OSSemaphore* sem = &Coin.sem;

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
        for (i = 0; i < n; i++) {
            if (!((counters[i] | c->count[i]) & ~0x3FFF)) {
                d = (counters[i] - c->count[i]) & 0xFFF;
                if (d > 0) {
                    slot = fn_802894EC(chute, i);
                    idx = i;
                    if (chute == 2) {
                        idx = i + 2;
                    }
                    added = fn_80289324(slot, d * GetCoinMul(i));
                    AddCoinStats(buttons, idx, d, added);
                    if (!(counters[i] & 0xFFF)) {
                        fn_80288DEC(1, chute, i + 1, counters[i] & ~0xFFF);
                    }
                }
            }
            c->count[i] = counters[i];
        }
    }
    if (chute == 0 && Coin.chuteMode[chute] != 0) {
        for (i = 0; i < 4; i++) {
            if ((1 << i) & (c->prev & ~buttons)) {
                slot = fn_802894EC(chute, i);
                added = fn_80289324(slot, GetCoinMul(i));
                AddCoinStats(buttons, i, 1, added);
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

