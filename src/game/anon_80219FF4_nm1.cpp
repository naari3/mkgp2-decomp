#include "game/FlashFx_rescue.h"

void FlashFx::Update() {
    if (state == 0 && !fn_8019FE78(ring.p)) {
        Sprite_SetupAnim(ring.p, 0x4C, 1, 0);
        fn_8019FF6C(ring.p, 1);
        state = 1;
    }
    alpha += speed;
    if (alpha > lbl_806DAF64) {
        alpha = lbl_806DAF64;
        speed = lbl_806DAF60;
    }
    if (alpha < lbl_806DAF60) {
        alpha = lbl_806DAF60;
        speed = lbl_806DAF60;
    }
    body.p->alpha = alpha;
    ring.p->alpha = alpha;
    if (alpha > lbl_806DAF60) {
        Sprite_AdvanceAnim(body.p, lbl_806DAF70);
        Sprite_AdvanceAnim(ring.p, lbl_806DAF70);
    }
}


extern "C" void fn_8021A2B4(void) {
    if (lbl_806D1A60 != 0) {
        delete lbl_806D1A60;
        lbl_806D1A60 = 0;
    }
}
