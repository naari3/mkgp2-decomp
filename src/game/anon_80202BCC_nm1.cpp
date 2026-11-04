#include "game/MsgPopupTables_rescue.h"

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
