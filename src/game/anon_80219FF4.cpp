#include "game/FlashFx_rescue.h"

void FlashFx::Restart() {
    speed = lbl_806DAF60;
    alpha = lbl_806DAF60;
    body.p->alpha = lbl_806DAF60;
    ring.p->alpha = lbl_806DAF60;
    if (!(speed > lbl_806DAF60) && lbl_806DAF64 != alpha) {
        speed = lbl_806DAF68;
        state = 0;
        Sprite_SetupAnim(ring.p, 0x4B, 1, 0);
        fn_8019FF6C(ring.p, 0);
        Sprite_SetupAnim(body.p, lbl_803C4E50[g_gameMode], 1, 0);
    }
    alpha = lbl_806DAF64;
}

void FlashFx::Hide() {
    speed = lbl_806DAF60;
    alpha = lbl_806DAF60;
    body.p->alpha = lbl_806DAF60;
    ring.p->alpha = lbl_806DAF60;
}

void FlashFx::FadeOut() {
    speed = lbl_806DAF6C;
}

void FlashFx::Show() {
    if (speed > lbl_806DAF60 || lbl_806DAF64 == alpha) {
        return;
    }
    speed = lbl_806DAF68;
    state = 0;
    Sprite_SetupAnim(ring.p, 0x4B, 1, 0);
    fn_8019FF6C(ring.p, 0);
    Sprite_SetupAnim(body.p, lbl_803C4E50[g_gameMode], 1, 0);
}

void FlashFx::Draw() {
    if (alpha > lbl_806DAF60) {
        fn_801A0004(body.p);
        fn_801A0004(ring.p);
    }
}
