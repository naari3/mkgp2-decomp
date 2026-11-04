/* Sprite browser: resource selection, repeat delay, pause and animation tick. */
#include "game/SpriteBrowser_private.h"
extern "C" {
extern const float lbl_806DA030, lbl_806DA03C, lbl_806DA040, lbl_806DA050;
extern const double lbl_806DA048;
void Sprite_SetupAnim(BrowserSprite *, int, int, int);
void fn_8019FF6C(BrowserSprite *, int);
void fn_801A1280();
void Sprite_AdvanceAnim(BrowserSprite *, float);
}

extern "C" int fn_801D35D4(SpriteBrowser *self) {
    float dt = lbl_806DA040;
    unsigned char changed = 0;
    BrowserInput *in = InputMgr_GetPlayer(GetInputManager(), 0);
    if (in->right() > lbl_806DA030) {
        if (in->pressed(0x2000)) {
            if ((self->animation += 10) >= 0x1EC) self->animation -= 0x1EC;
            changed = 1;
        }
        if (in->pressed(0x400)) {
            if ((self->animation -= 10) < 0) self->animation += 0x1EC;
            changed = 1;
        }
        if (self->repeat <= 0) {
            if (in->axis() >= lbl_806DA048) {
                if ((self->animation += 10) >= 0x1EC) self->animation -= 0x1EC;
                changed = 1;
                self->repeat = 10;
            } else if (in->axis() <= lbl_806DA050) {
                if ((self->animation -= 10) < 0) self->animation += 0x1EC;
                changed = 1;
                self->repeat = 10;
            }
        }
    } else {
        if (in->pressed(0x2000)) {
            if ((++self->animation) >= 0x1EC) self->animation = 0;
            changed = 1;
        }
        if (in->pressed(0x400)) {
            if ((--self->animation) < 0) self->animation = 0x1EB;
            changed = 1;
        }
        if (self->repeat <= 0) {
            if (in->axis() >= lbl_806DA048) {
                if ((++self->animation) >= 0x1EC) self->animation -= 0x1EC;
                changed = 1;
                self->repeat = 10;
            } else if (in->axis() <= lbl_806DA050) {
                if ((--self->animation) < 0) self->animation += 0x1EC;
                changed = 1;
                self->repeat = 10;
            }
        }
    }
    if (changed) {
        Sprite_SetupAnim(self->sprite, self->animation, 1, 0);
        fn_8019FF6C(self->sprite, 1);
        dt = lbl_806DA03C;
    }
    if (self->repeat > 0) self->repeat--;
    if (in->pressed(0x800)) {
        if (fn_8019FF50(self->sprite)) fn_8019FF6C(self->sprite, 0);
        else fn_8019FF6C(self->sprite, 1);
    }
    fn_801A1280();
    Sprite_AdvanceAnim(self->sprite, dt);
    return -2;
}
