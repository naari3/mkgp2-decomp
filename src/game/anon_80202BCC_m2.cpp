#include "game/MsgPopupTables_rescue.h"

extern "C" int fn_80202F28(int msg) {
    if (msg <= -1 || msg >= 30) {
        return 0;
    }
    return lbl_803C1650[msg];
}

MsgPopupCoin::~MsgPopupCoin() {
}

extern "C" void fn_802030DC(MsgPopupCoin *self) {
    TexMgr_SetTexture(&self->texts[1], fn_80202E78(self->msgId + (lbl_80598A60[0x27] != 0), 1), lbl_806D19F0);
    self->Tick();
}
