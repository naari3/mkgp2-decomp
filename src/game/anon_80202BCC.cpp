/*
 * Class-selector list lifetime and message tables @ 0x80202BCC..0x8020314C.
 */

#define MSGPOPUP_INLINE_DTOR
#include "game/FlowMsgPopup.h"

extern "C" {
extern FlowSceneList *lbl_806D19E0;
extern int lbl_806D19E4;
extern int lbl_806D19F0;
extern const int lbl_803C210C[14];
extern const int lbl_803C20D4[14];
extern const int lbl_803C1650[30];
extern unsigned char lbl_80598A60[0x2A];
void fn_80120A08(int id);
void PreloadResource(int id);
}

extern "C" void fn_80202BCC(void) {
    if (lbl_806D19E0) {
        delete lbl_806D19E0;
        lbl_806D19E0 = 0;
    }
    lbl_806D19E4 = 0;
    fn_80120A08(0x867);
    fn_80120A08(0x868);
    fn_80120A08(0x8A9);
}

extern "C" void fn_80202C34(int layer) {
    if (lbl_806D19E0 == 0) {
        lbl_806D19E0 = new SceneListImpl;
    }
    lbl_806D19E4 = layer;
    PreloadResource(0x867);
    PreloadResource(0x868);
    PreloadResource(0x8A9);
}

struct MsgTables {
    char pad0000[0x16A0];
    const char *msgEN[30][4];
    char pad1880[0x1B64 - 0x1880];
    const char *msgJP[30][4];
    char pad1D44[0x1E2C - 0x1D44];
    const char *titleEN[14][2];
    char pad1E9C[0x1F40 - 0x1E9C];
    const char *subEN[14][2];
    char pad1FB0[0x2000 - 0x1FB0];
    const char *titleJP[14][2];
    char pad2070[0x20B4 - 0x2070];
    const char *subJP[14][2];
    const char *fallback[4];
};

extern "C" const MsgTables lbl_803C0390;

extern "C" const char *fn_80202CC0(int msg, int line) {
    const MsgTables *t = &lbl_803C0390;
    if (line > 1 || line < 0) {
        line = 0;
    }
    if (msg <= -1 || msg >= 14) {
        return t->fallback[line];
    }
    if (isJapanese() == 0) {
        return t->subEN[msg][line];
    }
    return t->subJP[msg][line];
}

extern "C" const char *fn_80202D70(int msg, int line) {
    const MsgTables *t = &lbl_803C0390;
    if (line > 1 || line < 0) {
        line = 0;
    }
    if (msg <= -1 || msg >= 14) {
        return t->fallback[line];
    }
    if (isJapanese() == 0) {
        return t->titleEN[msg][line];
    }
    return t->titleJP[msg][line];
}

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

extern "C" const char *fn_80202E78(int msg, int line) {
    const MsgTables *t = &lbl_803C0390;
    if (line > 3 || line < 0) {
        line = 0;
    }
    if (msg <= -1 || msg >= 30) {
        return t->fallback[line];
    }
    if (isJapanese() == 0) {
        return t->msgEN[msg][line];
    }
    return t->msgJP[msg][line];
}

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
