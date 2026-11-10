#ifndef GAME_CARD_REWARD_PICKERS_PRIVATE_H
#define GAME_CARD_REWARD_PICKERS_PRIVATE_H

/*
 * Card reward item pickers (0x80209330..0x80209FA4): pick an item the
 * player does not own yet, in a shuffled order.
 */

extern "C" {
#include "game/CardLoadShadowPrivate.h"
}
typedef CardPlayerSnapshot PlayerData;

struct ItemList {
    const int *items;
    int count;
};

extern "C" {
extern PlayerData g_playerData;
extern int g_roundIndex;
extern int lbl_806D02E4;
extern const int lbl_804EC5E8[];
extern const ItemList CardSnapshot_ResolveCommonItems_data_804EC7D4[2];
unsigned char fn_801D6F30(PlayerData *pd, int item, int mode);
void fn_801D7610(PlayerData *pd, int a);
unsigned char fn_801D4FF4(PlayerData *pd, void *src, int a);
unsigned char IsCardValid(void);
int Rand15(void);
int WrapInRange(int v, int lo, int hi);

extern int g_ccClass;
extern int lbl_806D02D8;
extern int lbl_806D02DC;
extern int lbl_806D02E0;
extern const int lbl_804EC568[];
unsigned char fn_801D5B8C(PlayerData *pd, int cc, int a, int b);
void card_pack(PlayerData *pd, void *buf, int a);

int fn_80209330(void);
int fn_80209A84(void);
int fn_80209AC4(int a, int b);
void fn_80209C88(void);
int fn_80209338(int cat);
int CardSnapshot_ResolveCommonItems(void **cards);
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
