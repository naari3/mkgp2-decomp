#include "game/FlowScene.h"

/* Owner and child views observed in the target. */
struct TransitionChild {
    virtual ~TransitionChild();
    virtual void Finish();
};
struct TransitionOwner {
    void *vtable;
    int flags;
    TransitionChild *child;
    int route;
    int field10;
    FlowFaderI *fader;
};
extern "C" {
extern unsigned char lbl_806D17F0, lbl_806D17F1;
unsigned char ServiceEnable_Get();
unsigned char ServiceValue_Get();
TransitionChild *fn_80225F6C();
TransitionChild *fn_8024D140();
TransitionChild *fn_8021EFB4();
TransitionChild *fn_8024B0D8();
void SetLocalPcbRole(int);
void SetSyncTarget(int);

void fn_8024BE64(VObject *p) { delete p; }

void fn_8024BE9C(TransitionOwner *self, int route) {
    if (self->child) {
        switch (route) {
        case 4:
            if (lbl_806D17F1) {
                self->fader->Set(0, 255, 15);
                self->route = 10;
            } else self->route = 6;
            break;
        case 5:
            if (lbl_806D17F0) {
                if (lbl_806D17F1) {
                    self->fader->Set(0, 255, 15);
                    self->route = 10;
                } else self->route = 6;
            } else {
                if (ServiceEnable_Get() && !ServiceValue_Get()) {
                    self->route = 7;
                } else {
                    self->fader->Set(0, 255, 15);
                    self->route = 10;
                }
            }
            break;
        case 6:
            self->fader->Set(0, 255, 15);
            self->route = 10;
            break;
        case 7:
            self->fader->Set(0, 255, 15);
            self->route = 10;
            break;
        }
        if (self->child) {
            self->child->Finish();
            self->child = 0;
        }
    }
}
void fn_8024C018(TransitionOwner *self, int route) {
    if (!self->child) {
        switch (route) {
        case 4: self->child = fn_80225F6C(); break;
        case 5: self->child = fn_8024D140(); break;
        case 6: self->child = fn_8021EFB4(); break;
        case 7:
            SetLocalPcbRole(0);
            SetSyncTarget(0x33);
            self->child = fn_8024B0D8();
            break;
        default: self->child = 0; break;
        }
    }
}
void fn_8024C0BC(VObject *p) { delete p; }
}
