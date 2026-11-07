#include "game/CardRewardPickersPrivate.h"

int fn_80209AC4(int a, int b) {
    if (!CardOK()) {
        return 0;
    }
    if (a < 1 || a > 8) {
        return 0;
    }
    if (b < 0 || b > 7) {
        return 0;
    }
    int result = 0;
    int row = a - 1;
    int cc = g_ccClass == 2 ? 2 : 0;
    int group = b >= 4 ? 1 : 0;
    switch (cc + group) {
    case 0:
        if (fn_801D5B8C(&g_playerData, g_ccClass, a, b) == 1) {
            result = lbl_806D02DC;
        } else {
            result = (lbl_804EC568 + row * 4)[b];
            if (fn_801D6F30(&g_playerData, result, 0) == 1) {
                result = lbl_806D02DC;
            }
        }
        break;
    case 1:
        if (b == 7 && !fn_801D5B8C(&g_playerData, g_ccClass, a, 7)) {
            result = lbl_806D02DC;
        }
        break;
    case 2:
        result = lbl_806D02DC;
        break;
    case 3:
        if (b == 7 && !fn_801D5B8C(&g_playerData, g_ccClass, a, 7)) {
            result = lbl_806D02DC;
        }
        break;
    }
    lbl_806D02E0 = result;
    return result;
}

static inline void FillSpecialItems(int *list, const int *pool) {
    PlayerData *pd = &g_playerData;
    int k = 0;
    const int *items = pool + 0x61;
    const int *rows = pool + 0x65;
    const int *cols = pool + 0x69;
    for (int i = 0; i < 4; i++) {
        if (!fn_801D6F30(pd, items[i], 0) &&
            fn_801D5B8C(pd, 0, rows[i], cols[i]) &&
            fn_801D5B8C(pd, 1, rows[i], cols[i])) {
            list[k++] = items[i];
        }
    }
}

void fn_80209C88(void) {
    const int *pool = lbl_804EC568;
    char buf[0x45];
    void *cards[4] = {0, 0, 0, 0};
    cards[0] = buf;
    card_pack(&g_playerData, buf, 1);
    lbl_806D02D8 = CardSnapshot_ResolveCommonItems(cards);
    int list[4] = {0, 0, 0, 0};
    int result = -1;
    PlayerData *pd = &g_playerData;
    const int *tbl;
    int n;
    int round = g_roundIndex;
    if (g_ccClass == 2) {
        if (round >= 4) {
            tbl = pool + 0x6D;
            n = 14;
        } else {
            tbl = pool;
            n = 32;
        }
    } else if (round >= 4) {
        tbl = pool + 0x6D;
        n = 14;
    } else {
        FillSpecialItems(list, pool);
        tbl = list;
        n = 4;
    }
    int *ids = new int[n];
    Shuffle(ids, tbl, n);
    for (int i = 0; i < n; i++) {
        if (!fn_801D6F30(pd, ids[i], 0)) {
            result = ids[i];
            break;
        }
    }
    delete[] ids;
    lbl_806D02DC = result;
}
