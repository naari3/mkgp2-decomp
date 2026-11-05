#include "game/FlashFx_rescue.h"

void FlashFx::Update() {
    if (state == 0 && !fn_8019FE78(ring.p)) {
        Sprite_SetupAnim(ring.p, 0x4C, 1, 0);
        fn_8019FF6C(ring.p, 1);
        state = 1;
    }
    alpha += speed;
    if (alpha > 1.0f) {
        alpha = 1.0f;
        speed = 0.0f;
    }
    if (alpha < 0.0f) {
        alpha = 0.0f;
        speed = 0.0f;
    }
    body.p->alpha = alpha;
    ring.p->alpha = alpha;
    if (alpha > 0.0f) {
        Sprite_AdvanceAnim(body.p, 0.0165f);
        Sprite_AdvanceAnim(ring.p, 0.0165f);
    }
}


extern "C" void fn_8021A2B4(void) {
    if (lbl_806D1A60 != 0) {
        delete lbl_806D1A60;
        lbl_806D1A60 = 0;
    }
}
