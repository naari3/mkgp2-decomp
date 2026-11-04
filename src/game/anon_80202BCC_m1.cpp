#include "game/MsgPopupTables_rescue.h"

extern "C" int fn_80202E20(int msg) {
    if (msg <= -1 || msg >= 14) {
        return 0x734;
    }
    return lbl_803C210C[msg];
}

extern "C" int fn_80202E4C(int msg) {
    if (msg <= -1 || msg >= 14) {
        return 0x734;
    }
    return lbl_803C20D4[msg];
}
