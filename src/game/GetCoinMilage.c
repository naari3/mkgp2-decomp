#include "game/types/PlayerData.h"

int GetCoinMilage(PlayerData *p) {
    return p->coinMilage;
}

void AddCoinMilage(PlayerData *p, int n) {
    p->coinMilage += n;
    if (p->coinMilage >= 99999) {
        p->coinMilage = 99999;
    }
}

void SetKartVariantOnPlayer(PlayerData *p, int v) {
    if (v < 0 || v >= 4) {
        v = 0;
    }
    p->kartVariant = v;
}

void fn_801D5DB4(PlayerData *p, int v) {
    if (v < 0 || v >= 13) {
        v = 0;
    }
    p->variant = v;
}

void fn_801D5DD0(PlayerData *p) {
    if (p->raceCount < 50) {
        p->raceCount++;
    }
}

#define PAIR(a, b) (p->unlockFlags[a] == 1 && p->unlockFlags[b] == 1)

static inline int ExcludePairs(PlayerData *p, int n) {
    if (PAIR(0x3D, 0x3E)) {
        n--;
    }
    if (PAIR(0x3F, 0x40)) {
        n--;
    }
    if (PAIR(0x41, 0x42)) {
        n--;
    }
    if (PAIR(0x43, 0x44)) {
        n--;
    }
    if (PAIR(0x64, 0x65)) {
        n--;
    }
    return n;
}

int fn_801D5DE8(PlayerData *p) {
    return ExcludePairs(p, 0x79);
}

int fn_801D5E80(PlayerData *p) {
    int n = 0;
    int i;
    for (i = 0; i < 0x79; i++) {
        if (p->unlockFlags[i] == 1) {
            n++;
        }
    }
    return ExcludePairs(p, n);
}

int fn_801D5F40(PlayerData *p) {
    if (p->unk_121[0] == 1 || p->unk_121[1] == 1 || p->unk_121[2] == 1) {
        return 1;
    }
    return 0;
}
