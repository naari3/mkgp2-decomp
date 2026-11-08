#include "game/CardRewardSelectionPrivate.h"

extern "C" int lbl_804EC568[32];

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
