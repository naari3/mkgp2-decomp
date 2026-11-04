#include "game/MsgPopupTables_rescue.h"

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
