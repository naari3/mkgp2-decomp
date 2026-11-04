/* Resource-parameter browser controls. */
#include "game/SpriteBrowser_private.h"
extern "C" {
extern short lbl_806CFEA8;
extern const float lbl_806DA058, lbl_806DA068, lbl_806DA06C, lbl_806DA070, lbl_806DA074, lbl_806DA078;
extern const double lbl_806DA060;
int fn_801A0500(BrowserSprite *);
int fn_801A0584(BrowserSprite *, int, int, short *);
void fn_801A1280();
void Sprite_AdvanceAnim(BrowserSprite *, float);
}

struct ParameterBrowser {
    void *vtable;
    int resource;
    BrowserSprite *sprite;
    int repeat;
    void Reload() {
        fn_801A0500(sprite);
        lbl_806CFEA8 = resource;
        fn_801A0584(sprite, 0x1EB, 1, &lbl_806CFEA8);
    }
    void Reload(int value) {
        fn_801A0500(sprite);
        lbl_806CFEA8 = value;
        fn_801A0584(sprite, 0x1EB, 1, &lbl_806CFEA8);
    }
};
extern "C" int fn_801D3B7C(ParameterBrowser *self) {
    BrowserInput *in = InputMgr_GetPlayer(GetInputManager(), 0);
    if (in->right() > lbl_806DA058) {
        if (in->pressed(0x2000)) {
            if ((self->resource += 50) >= 0x2B00) self->resource -= 0x2B00;
            self->Reload();
        }
        if (in->pressed(0x400)) {
            if ((self->resource -= 50) < 0) self->resource += 0x2B00;
            self->Reload();
        }
        if (self->repeat <= 0) {
            if (in->axis() >= lbl_806DA060) {
                if ((self->resource += 50) >= 0x2B00) self->resource -= 0x2B00;
                self->Reload(self->resource);
                self->repeat += 10;
            } else if (in->axis() <= lbl_806DA068) {
                if ((self->resource -= 50) < 0) self->resource += 0x2B00;
                self->Reload(self->resource);
                self->repeat += 10;
            }
        }
    } else {
        if (in->pressed(0x2000)) {
            if ((++self->resource) >= 0x2B00) self->resource -= 0x2B00;
            self->Reload();
        }
        if (in->pressed(0x400)) {
            if ((--self->resource) < 0) self->resource += 0x2B00;
            self->Reload();
        }
        if (self->repeat <= 0) {
            if (in->axis() >= lbl_806DA060) {
                if ((++self->resource) >= 0x2B00) self->resource -= 0x2B00;
                self->Reload(self->resource);
                self->repeat += 10;
            } else if (in->axis() <= lbl_806DA068) {
                if ((--self->resource) < 0) self->resource += 0x2B00;
                self->Reload(self->resource);
                self->repeat += 10;
            }
        }
    }
    if (in->pressed(0x800)) self->resource = 0;
    if (in->left() > lbl_806DA058) {
        self->sprite->SetPos(lbl_806DA06C, lbl_806DA070);
    } else {
        self->sprite->SetPos(lbl_806DA074, lbl_806DA070);
    }
    if (self->repeat > 0) self->repeat--;
    fn_801A1280();
    Sprite_AdvanceAnim(self->sprite, lbl_806DA078);
    return -2;
}
