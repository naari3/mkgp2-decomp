#include "game/CardRewardPickersPrivate.h"

int fn_80209338(int cat) {
    if (cat < 0 || cat >= 13) {
        return -1;
    }
    int result = -1;
    PlayerData *pd = &g_playerData;
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
