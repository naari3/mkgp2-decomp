#include "game/MenuDraw_private.h"
extern "C" const float lbl_806D9890;
extern "C" void fn_801B8BD8(MenuOwnerView *self) {
    if (lbl_806D17F8) fn_801A0004(lbl_806D17F8);
    if (lbl_806D17FC) fn_801A0004(lbl_806D17FC);
    if (lbl_806D1800) fn_801A0004(lbl_806D1800);
    if (lbl_806D180C) fn_801A0004(lbl_806D180C);
    if (self->child) self->child->Draw();
    if (lbl_806D184F || lbl_806D1850) {
        fn_801A1174(2, 6, 0, 0, 0);
        fn_801A10DC(640.0f, 480.0f);
        fn_801A1128(320.0f, 240.0f);
        fn_801A0FD4(255.0f, 255.0f, 255.0f, (float)(255 - lbl_806D1858 * 25));
        fn_801A0DF0();
        fn_801A1174(0x1B12, 6, 0, 0, 0);
        fn_801A1128(0.0f, 374.0f + lbl_806D1854);
        fn_801A0DF0();
        fn_801A1174(0x1B13, 6, 0, 0, 0);
        fn_801A1128(0.0f, 366.0f + lbl_806D1854);
        fn_801A0DF0();
    }
    if (lbl_806D181D != -1 && lbl_8067928C[lbl_806D181D]) fn_801A0004(lbl_8067928C[lbl_806D181D]);
    if (lbl_806D181C != -1 && lbl_80679280[lbl_806D181C]) fn_801A0004(lbl_80679280[lbl_806D181C]);
    if (lbl_806D1820) fn_801A0004(lbl_806D1820);
    if (lbl_806D1848 > lbl_806D9890) {
        if (lbl_806D1840) { lbl_806D1840->alpha = lbl_806D1848; fn_801A0004(lbl_806D1840); }
        if (lbl_806D1844) { lbl_806D1844->alpha = lbl_806D1848; fn_801A0004(lbl_806D1844); }
        if (lbl_806D184D == 0) fn_801A1174(0x1875, 5, 0, 0, 0);
        else fn_801A1174(0x1875, 5, 0, 0, 0);
        fn_801A1128(244.0f, 450.0f);
        fn_801A0FD4(1.0f, 1.0f, 1.0f, lbl_806D1848);
        fn_801A0DF0();
        if (lbl_806D184D == 0) fn_801A1174(0x1874, 5, 0, 0, 0);
        else fn_801A1174(0x1874, 5, 0, 0, 0);
        fn_801A1128(400.0f, 450.0f);
        fn_801A0FD4(1.0f, 1.0f, 1.0f, lbl_806D1848);
        fn_801A0DF0();
    }
    fn_8011FA98();
}
