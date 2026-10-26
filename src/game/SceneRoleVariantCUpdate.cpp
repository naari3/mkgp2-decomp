#include "game/SceneRoleVariantCPrivate.h"
extern "C" {
void fn_8021A0D0(SceneRoleVariantCContext *);
void fn_802043B8(FlowSceneList *, int);
void fn_8011FAFC(ResCtrl *, int);
}
extern "C" void fn_8024CD54(SceneRoleVariantC *self)
{
    self->list.p->Update();
    if (!self->child) {
        if (self->route == 10) {
            fn_8021A0D0(lbl_806D1A60);
            if (lbl_806DBFC8 == lbl_806D1A60->value && self->fader.p->Value() == 255) {
                fn_802043B8(self->list.p, 0);
                self->done = 1;
            }
        } else self->Start(self->route);
    }
    if (self->child) {
        if (!self->child->done) self->child->Update();
        else self->Finish(self->route);
    }
    ResCtrl ctrl;
    unsigned char color = self->fader.p->Value();
    ctrl.mode = 2;
    ctrl.SetSize(lbl_806DBFCC, lbl_806DBFD0);
    ctrl.Show(lbl_806DBFD4, lbl_806DBFD8, lbl_806DBFDC);
    ctrl.SetColor(color);
    fn_8011FAFC(&ctrl, 7);
    self->fader.p->Step();
}
