/*
 * 0x80219FF4..0x8021A430: fading two-sprite flash (singleton lbl_806D1A60).
 */

#include "game/CreditHud.h"

extern "C" {
extern const int lbl_803C4E50[];
extern const float lbl_806DAF60;
extern const float lbl_806DAF64;
extern const float lbl_806DAF68;
extern const float lbl_806DAF6C;
extern const float lbl_806DAF70;
extern int g_gameMode;
void Sprite_SetupAnim(AnimSprite *s, int res, int a, int b);
void fn_8019FF6C(AnimSprite *s, int loop);
unsigned char fn_8019FE78(AnimSprite *s);
void fn_801A0004(AnimSprite *s);
void Sprite_AdvanceAnim(AnimSprite *s, float step);
}

struct FlashFx {
    OwnPtr<AnimSprite> body;
    OwnPtr<AnimSprite> ring;
    int state;
    float alpha;
    float speed;
    FlashFx() : body(new AnimSprite(lbl_803C4E50[g_gameMode], 1, 0)), ring(new AnimSprite(0x4B, 1, 0)) {
        state = 0;
        alpha = lbl_806DAF60;
        speed = lbl_806DAF60;
        body.p->alpha = lbl_806DAF60;
        ring.p->alpha = lbl_806DAF60;
        body.p->layer = 0;
        ring.p->layer = 0;
    }
    void Restart();
    void Hide();
    void FadeOut();
    void Show();
    void Draw();
    void Update();
};

extern "C" FlashFx *lbl_806D1A60;

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

extern "C" FlashFx *fn_8021A354(void) {
    if (lbl_806D1A60 == 0) {
        lbl_806D1A60 = new FlashFx;
    }
    return lbl_806D1A60;
}
