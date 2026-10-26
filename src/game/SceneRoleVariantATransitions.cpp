#include "game/SceneRoleVariantA.h"

extern "C" {
extern unsigned char lbl_806D17F0;
unsigned char ServiceEnable_Get();
unsigned char ServiceValue_Get();
VariantAChild *fn_8024D140();
VariantAChild *fn_8024B0D8();

void fn_8024C3AC(VariantABase *self, int route) {
    if (self->child) {
        switch (route) {
        case 5:
            if (lbl_806D17F0) {
                self->fader.p->Set(0, 255, 15);
                self->route = 10;
            } else if (ServiceEnable_Get() && !ServiceValue_Get()) {
                self->route = 7;
            } else {
                self->fader.p->Set(0, 255, 15);
                self->route = 10;
            }
            break;
        case 6: break;
        case 7:
            self->fader.p->Set(0, 255, 15);
            self->route = 10;
            break;
        }
        if (self->child) {
            self->child->Finish();
            self->child = 0;
        }
    }
}
void fn_8024C4B4(VariantABase *self, int route) {
    if (!self->child) {
        switch (route) {
        case 5: self->child = fn_8024D140(); break;
        case 7: self->child = fn_8024B0D8(); break;
        case 6:
        default: self->child = 0; break;
        }
    }
}
void fn_8024C52C(VObject *p) { delete p; }
}
