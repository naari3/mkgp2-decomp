/*
 * 0x802151C8..0x80215508: coin challenge score display setup.
 */

#include "game/FlowScene.h"

struct ScoreDisplay {
    int sprites[9];
    unsigned char dirty;
    float value;
};

extern "C" {
extern const float lbl_803C3DD8[18];
extern const float lbl_806DAE24;
extern const float lbl_806DAE28;
extern const float lbl_806DAE30;
extern const float lbl_806DAE58;
void PreloadResource(int res);
int SpriteHandle_CreateDefault(ResCtrl *ctrl, int layer);
void fn_80121E10(ResCtrl *ctrl);
}

extern "C" ScoreDisplay *ScoreDisplay_Init(ScoreDisplay *d, int n) {
    PreloadResource(0x14B9);
    PreloadResource(0x14C4);
    PreloadResource(0x14C6);
    ResCtrl rc;
    rc.resId = 0x14B9;
    rc.Show(lbl_803C3DD8[0], lbl_803C3DD8[1], lbl_806DAE28);
    d->sprites[0] = SpriteHandle_CreateDefault(&rc, 0);
    fn_80121E10(&rc);
    rc.resId = 0x14C6;
    rc.Show(lbl_803C3DD8[2], lbl_803C3DD8[3], lbl_806DAE28);
    d->sprites[1] = SpriteHandle_CreateDefault(&rc, 0);
    fn_80121E10(&rc);
    rc.resId = 0x14C8;
    rc.Show(lbl_803C3DD8[4], lbl_803C3DD8[5], lbl_806DAE28);
    d->sprites[2] = SpriteHandle_CreateDefault(&rc, 0);
    fn_80121E10(&rc);
    rc.resId = 0x14C5;
    rc.Show(lbl_803C3DD8[6], lbl_803C3DD8[7], lbl_806DAE28);
    d->sprites[3] = SpriteHandle_CreateDefault(&rc, 0);
    fn_80121E10(&rc);
    rc.resId = 0x14BA;
    rc.Show(lbl_803C3DD8[8], lbl_803C3DD8[9], lbl_806DAE28);
    d->sprites[4] = SpriteHandle_CreateDefault(&rc, 0);
    fn_80121E10(&rc);
    rc.resId = 0x14BA;
    rc.Show(lbl_803C3DD8[10], lbl_803C3DD8[11], lbl_806DAE28);
    d->sprites[5] = SpriteHandle_CreateDefault(&rc, 0);
    fn_80121E10(&rc);
    rc.resId = 0x14C4;
    float s = lbl_806DAE24;
    rc.Show(lbl_803C3DD8[12], lbl_803C3DD8[13], lbl_806DAE28);
    rc.SetScale(s);
    d->sprites[6] = SpriteHandle_CreateDefault(&rc, 0);
    fn_80121E10(&rc);
    rc.resId = n / 10 + 0x14BA;
    rc.Show(lbl_803C3DD8[14], lbl_803C3DD8[15], lbl_806DAE28);
    rc.SetScale(lbl_806DAE58);
    d->sprites[7] = SpriteHandle_CreateDefault(&rc, 0);
    fn_80121E10(&rc);
    rc.resId = n % 10 + 0x14BA;
    rc.Show(lbl_803C3DD8[16], lbl_803C3DD8[17], lbl_806DAE28);
    rc.SetScale(lbl_806DAE58);
    d->sprites[8] = SpriteHandle_CreateDefault(&rc, 0);
    d->dirty = 0;
    d->value = lbl_806DAE30;
    return d;
}
