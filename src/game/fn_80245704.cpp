#include "game/HudSprite2454Private.h"
extern "C" void fn_80245704(HudSprite2457 *self) {
    ResCtrl c;
    if (self->visible) {
        c.resId=0x1CB6;
        float x=self->x;
        float y=self->y;
        c.Show(x,y,lbl_806DBED8);
        c.tail[0]=1;
        c.tail[1]=1;
        c.tail[2]=1;
        fn_8011FAFC(&c,3);
    }
}
