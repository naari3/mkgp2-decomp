/*
 * 0x80218D98..0x80218F1C: credit counter HUD dtor and ctor.
 */

#include "game/CreditHud.h"

extern "C" {
extern int lbl_806D1A58;
extern const float lbl_806DAF34;
extern const float lbl_806DAF38;
void fn_80120A08(int res);
short *fn_801A0310(AnimSprite *s, int id);
}

CreditHud::~CreditHud() {
    fn_80120A08(0x46);
}

CreditHud::CreditHud(int mode) : sprite(new AnimSprite(0x17E, 1, 0)) {
    sprite.p->layer = 7;
    sprite.p->SetPos(lbl_806DAF34, lbl_806DAF38);
    coin10 = fn_801A0310(sprite.p, 0x1D63);
    coin1 = fn_801A0310(sprite.p, 0x1D64);
    per10 = fn_801A0310(sprite.p, 0x1D65);
    per1 = fn_801A0310(sprite.p, 0x1D66);
    slash = fn_801A0310(sprite.p, 0x1D62);
    int m = mode;
    if (m <= -1 || m >= 4) {
        m = 0;
    }
    lbl_806D1A58 = m;
    Update();
}
