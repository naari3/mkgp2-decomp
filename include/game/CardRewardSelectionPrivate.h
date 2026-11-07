#ifndef GAME_CARD_REWARD_SELECTION_PRIVATE_H
#define GAME_CARD_REWARD_SELECTION_PRIVATE_H

/* This TU defines the mutable reward tables in .data. The earlier picker
 * header declares const external views of those tables, so share the canonical
 * snapshot type here and mirror its small inline helpers. */
extern "C" {
#include "game/CardLoadShadowPrivate.h"
}
typedef CardPlayerSnapshot PlayerData;

extern "C" {
extern PlayerData g_playerData;
extern int g_roundIndex;
extern int g_ccClass;
extern int lbl_806D02D8;
extern int lbl_806D02DC;
extern int lbl_806D02E0;
unsigned char IsCardValid(void);
unsigned char fn_801D6F30(PlayerData *pd, int item, int mode);
unsigned char fn_801D5B8C(PlayerData *pd, int cc, int course, int stage);
void card_pack(PlayerData *pd, void *buf, int mode);
int CardSnapshot_ResolveCommonItems(void **cards);
int Rand15(void);
int WrapInRange(int v, int lo, int hi);
int fn_80209AC4(int course, int stage);
void fn_80209C88(void);
}

static inline bool CardOK() {
    if (IsCardValid()) {
        return true;
    }
    return false;
}

/* Fills out[0..n) with tbl[0..n) in a random order. */
static inline void Shuffle(int *out, const int *tbl, int n) {
    bool *used = new bool[n];
    for (int i = 0; i < n; i++) {
        out[i] = -1;
        used[i] = 0;
    }
    for (int i = 0; i < n; i++) {
        int r = Rand15() % n;
        while (used[r] == 1) {
            r = WrapInRange(r + 1, 0, n - 1);
        }
        used[r] = 1;
        out[i] = tbl[r];
    }
    delete[] used;
}

#endif
