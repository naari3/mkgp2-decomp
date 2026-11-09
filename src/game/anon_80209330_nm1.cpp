#include "game/CommonRewardPickerPrivate.h"

static inline void Shuffle(int *out, int *tbl, int n) {
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

static inline int *MakeShuffledItems(int *table, int count) {
    int *items = new int[count];
    bool *used = new bool[count];
    for (int i = 0; i < count; i++) {
        items[i] = -1;
        used[i] = 0;
    }
    for (int i = 0; i < count; i++) {
        int r = Rand15() % count;
        while (used[r] == 1) {
            r = WrapInRange(r + 1, 0, count - 1);
        }
        used[r] = 1;
        items[i] = table[r];
    }
    delete[] used;
    return items;
}

int fn_80209338(int cat) {
    if (cat < 0 || cat >= 13) {
        return -1;
    }
    PlayerData *pd = &g_playerData;
    int result = -1;
    if (!fn_801D6F30(pd, 0x24, 0)) {
        result = 0x24;
    }
    if (result < 0) {
        int *ids = new int[5];
        Shuffle(ids, lbl_804EC5E8 + cat * 5, 5);
        for (int i = 0; i < 5; i++) {
            if (!fn_801D6F30(pd, ids[i], 0)) {
                result = ids[i];
                break;
            }
        }
        delete[] ids;
    }
    if (result < 0) {
        int *ids = MakeShuffledItems(lbl_804EC5E8, 65);
        for (int i = 0; i < 65; i++) {
            if (!fn_801D6F30(pd, ids[i], 0)) {
                result = ids[i];
                break;
            }
        }
        delete[] ids;
    }
    lbl_806D02E4 = result;
    return result;
}
