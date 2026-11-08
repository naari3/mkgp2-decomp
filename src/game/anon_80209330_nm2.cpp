#include "game/CardRewardSelectionPrivate.h"

// Shared reward tables: 0x804EC568..0x804EC754.
// The category table is also read by the preceding picker TU.
extern "C" {
int lbl_804EC568[32] = {
    115, 113, 60, 44, 62, 34, 155, 29,
    105, 64, 108, 82, 49, 150, 25, 48,
    114, 109, 28, 89, 116, 110, 35, 85,
    148, 147, 149, 153, 152, 157, 151, 154
};
int lbl_804EC5E8[65] = {
    2, 68, 38, 95, 77, 1, 67, 37,
    96, 77, 11, 81, 13, 117, 76, 10,
    86, 12, 120, 66, 18, 111, 20, 65,
    59, 3, 88, 24, 71, 72, 6, 52,
    19, 55, 42, 9, 119, 17, 56, 122,
    4, 97, 39, 118, 107, 5, 97, 39,
    118, 107, 7, 121, 15, 106, 33, 136,
    137, 138, 139, 140, 142, 143, 144, 145,
    146
};
static int specialItems[4] = {
    155, 150, 48, 109
};
static int specialRows[4] = {
    2, 4, 4, 5
};
static int specialCols[4] = {
    2, 1, 3, 1
};
int lbl_804EC71C[14] = {
    123, 124, 127, 128, 129, 126, 130, 131,
    132, 133, 134, 135, 94, 47
};
}

#pragma push
#pragma opt_common_subs off
#pragma opt_propagation off
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
    cc += b >= 4 ? 1 : 0;
    switch (cc) {
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
#pragma pop


static inline void FillSpecialItems(int *list) {
    int i;
    const int *cols;
    int k;
    const int *rows;
    const int *items;
    PlayerData *pd;
    pd = &g_playerData;
    items = specialItems;
    cols = specialCols;
    rows = specialRows;
    k = 0;
    for (i = 0; i < 4; i++) {
        if (!fn_801D6F30(pd, items[i], 0) &&
            fn_801D5B8C(pd, 0, rows[i], cols[i]) &&
            fn_801D5B8C(pd, 1, rows[i], cols[i])) {
            list[k++] = items[i];
        }
    }
}

void fn_80209C88(void) {
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
            tbl = lbl_804EC71C;
            n = 14;
        } else {
            tbl = lbl_804EC568;
            n = 32;
        }
    } else if (round >= 4) {
        tbl = lbl_804EC71C;
        n = 14;
    } else {
        FillSpecialItems(list);
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
