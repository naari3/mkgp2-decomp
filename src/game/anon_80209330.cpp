/*
 * Card reward item pickers (0x80209330..0x80209A84): pick an item the
 * player does not own yet, in a shuffled order.
 */

struct PlayerData {
    char data[0x1DC];
};

struct ItemList {
    const int *items;
    int count;
};

extern "C" {
extern PlayerData g_playerData;
extern int g_roundIndex;
extern int lbl_806D02E4;
extern const int lbl_804EC5E8[];
extern const ItemList lbl_804EC7D4[2];
unsigned char fn_801D6F30(PlayerData *pd, int item, int mode);
void fn_801D7610(PlayerData *pd, int a);
unsigned char fn_801D4FF4(PlayerData *pd, void *src, int a);
unsigned char IsCardValid(void);
int Rand15(void);
int WrapInRange(int v, int lo, int hi);

int fn_80209330(void);
int fn_80209338(int cat);
int CardSnapshot_ResolveCommonItems(void **cards);
}

int fn_80209330(void) {
    return lbl_806D02E4;
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
        int *ids = new int[65];
        Shuffle(ids, lbl_804EC5E8, 65);
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

static inline bool HasAllItems(PlayerData *pd) {
    for (unsigned int k = 0; k < sizeof(lbl_804EC7D4) / sizeof(lbl_804EC7D4[0]); k++) {
        const ItemList &l = lbl_804EC7D4[k];
        int j = l.count;
        while (j-- > 0) {
            if (!fn_801D6F30(pd, l.items[j], 1)) {
                return false;
            }
        }
    }
    return true;
}

int CardSnapshot_ResolveCommonItems(void **cards) {
    if (!IsCardValid()) {
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
        PlayerData *p = snaps[i];
        if (p) {
            if (HasAllItems(p) == 1) {
                delete snaps[i];
                valid--;
                snaps[i] = 0;
            }
        }
    }
    if (valid <= 0) {
        return -1;
    }
    const ItemList &l = lbl_804EC7D4[g_roundIndex >= 4];
    int n = l.count;
    int *ids = new int[n];
    Shuffle(ids, l.items, n);
    int found[4] = {0, 0, 0, 0};
    for (int i = 0; i < n; i++) {
        int item = ids[i];
        int c = 0;
        for (int j = 0; j < 4; j++) {
            if (snaps[j] && fn_801D6F30(snaps[j], item, 1) == 1) {
                c++;
            }
        }
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
