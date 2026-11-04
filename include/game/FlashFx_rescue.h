#ifndef GAME_FLASHFX_RESCUE_H
#define GAME_FLASHFX_RESCUE_H
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
    ~FlashFx() {}
    void Restart();
    void Hide();
    void FadeOut();
    void Show();
    void Draw();
    void Update();
};

extern "C" FlashFx *lbl_806D1A60;


#endif
