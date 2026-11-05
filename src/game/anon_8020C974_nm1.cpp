#include "game/CardModeRootUnlock_private.h"

CardModeRoot::~CardModeRoot() {
    g_cupId = f08;
    g_longRoundFlag = f0C;
    SetReverseRoundFlag(f14);
    g_courseVariantIdx = f10;
    g_roundIndex = f48;
    lbl_806D1264[0] = f30[0];
    lbl_806D1264[1] = f30[1];
    lbl_806D1264[2] = f30[2];
    fn_8011F86C();
    clRom_DumpListOverlay();
    if (fn_8019083C(1)) {
        fn_801909A4(1);
    }
    fn_80121210();
    fn_801DAE54();
    delete (VObject *)g_pInputState;
    g_pInputState = 0;
}
