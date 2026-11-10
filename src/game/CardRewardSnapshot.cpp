#include "game/CardRewardPickersPrivate.h"

static inline bool HasAllItems(PlayerData *pd) {
    for (unsigned int k = 0; k < sizeof(CardSnapshot_ResolveCommonItems_data_804EC7D4) / sizeof(CardSnapshot_ResolveCommonItems_data_804EC7D4[0]); k++) {
        const ItemList &l = CardSnapshot_ResolveCommonItems_data_804EC7D4[k];
        int j = l.count;
        while (j-- > 0) {
            if (!fn_801D6F30(pd, l.items[j], 1)) {
                return false;
            }
        }
    }
    return true;
}

static inline int CountOwners(PlayerData **snaps, int item) {
    int count = 0;
    for (int j = 0; j < 4; j++) {
        if (snaps[j] && fn_801D6F30(snaps[j], item, 1) == 1) {
            count++;
        }
    }
    return count;
}

int CardSnapshot_ResolveCommonItems(void **cards) {
    if (!CardOK()) {
        return 0;
    }
    PlayerData *snaps[4];
    int result = -1;
    int valid = 0;
    for (int i = 0; i < 4; i++) {
        snaps[i] = 0;
        if (cards[i]) {
            snaps[i] = new PlayerData;
            fn_801D7610(snaps[i], 0);
            if (fn_801D4FF4(snaps[i], cards[i], 0) == 1) {
                valid++;
            } else {
                delete snaps[i];
                snaps[i] = 0;
            }
        }
    }
    for (int i = 0; i < 4; i++) {
        if (snaps[i]) {
            if (HasAllItems(snaps[i]) == 1) {
                delete snaps[i];
                valid--;
                snaps[i] = 0;
            }
        }
    }
    if (valid <= 0) {
        return -1;
    }
    int category = g_roundIndex >= 4 ? 1 : 0;
    int n = CardSnapshot_ResolveCommonItems_data_804EC7D4[category].count;
    int *ids = new int[n];
    Shuffle(ids, CardSnapshot_ResolveCommonItems_data_804EC7D4[category].items, n);
    int found[4];
    for (int i = 0; i < 4; i++) found[i] = 0;
    for (int i = 0; i < n; i++) {
        int item = ids[i];
        int c = CountOwners(snaps, item);
        if (c < valid && found[c] == 0) {
            found[c] = item;
        }
    }
    delete[] ids;
    for (int i = 0; i < 4; i++) {
        if (found[i] != 0) {
            result = found[i];
            break;
        }
    }
    for (int i = 0; i < 4; i++) {
        delete snaps[i];
    }
    return result;
}

int fn_80209A84(void) {
    if (!CardOK()) {
        return 0;
    }
    return lbl_806D02E0;
}
