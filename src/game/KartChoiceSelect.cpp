#include "game/KartChoiceOwnerPrivate.h"
/* Keep the event test and choice validation in the same inline operation. */
static inline unsigned char TestChoiceFlag(ChoiceStatus *status, unsigned long long mask) {
    unsigned char hit;
    if ((status->bits & mask) == 0) hit = 0;
    else hit = 1;
    return hit;
}
static inline unsigned char ChoiceChanged(ChoiceStatus *status, int choice) {
    unsigned char changed = TestChoiceFlag(status, 0x10000ULL);
    if (changed) changed = choice != -1;
    return changed;
}
extern "C" void fn_8023B318(KartChoiceOwner *self) {
    ChoiceStatus *status = self->render->status;
    int choice = -1;
    if (TestChoiceFlag(status, 0x800000000ULL)) choice = 0;
    else if (status->bits & 0x1000000000ULL) choice = 4;
    else if (status->bits & 0x200ULL) choice = 2;
    else if (status->bits & 0x80000000000ULL) choice = 3;
    else if (status->bits & 0x4000000000000ULL) choice = 5;
    else if (status->bits & 0x8000000000000ULL) choice = 6;
    else if (status->bits & 0x10000000000000ULL) {
        int n = fn_8023D1B4(self->render);
        if (n < 0) choice = 7;
        else choice = n + 7;
    } else if (status->bits & 0x100000ULL) choice = -2;
    else if (status->bits & 0x200000ULL) choice = -2;
    else if (status->bits & 0x400000ULL) choice = -2;
    unsigned char changed = ChoiceChanged(status, choice);
    if (changed) self->selected = choice;
    if (choice == -2) {
        self->state = 4;
        fn_8023066C(self->other);
    }
    switch (self->state) {
    case 0:
        if (changed) {
            self->selected = choice;
            self->x = lbl_803DC318[self->choice][0];
            self->y = lbl_803DC318[self->choice][1];
            self->vx = lbl_806DB978 * (lbl_806DB970[0] - self->x);
            self->vy = lbl_806DB978 * (lbl_806DB970[1] - self->y);
            self->state = 1;
            fn_802306B0(self->other, self->selected);
        }
        break;
    case 1:
        self->vx *= lbl_806DB97C;
        self->vy *= lbl_806DB97C;
        self->x += self->vx;
        self->y += self->vy;
        if (self->x >= lbl_806DB970[0]) {
            self->x = lbl_806DB970[0];
            self->y = lbl_806DB970[1];
            self->state = 2;
            fn_802306A0(self->other, self->selected);
        }
        break;
    case 2:
        if (changed) fn_80230684(self->other, self->selected);
        if (fn_80230644(self->other) == 1) {
            self->vx = lbl_806DB978 * (lbl_803DC318[self->choice][0] - self->x);
            self->vy = lbl_806DB978 * (lbl_803DC318[self->choice][1] - self->y);
            self->state = 3;
        }
        break;
    case 3:
        if (changed) {
            self->vx = lbl_806DB978 * (lbl_806DB970[0] - self->x);
            self->vy = lbl_806DB978 * (lbl_806DB970[1] - self->y);
            self->state = 1;
        } else {
            self->vx *= lbl_806DB97C;
            self->vy *= lbl_806DB97C;
            self->x += self->vx;
            self->y += self->vy;
            if (self->x <= lbl_803DC318[self->choice][0]) {
                self->x = lbl_803DC318[self->choice][0];
                self->y = lbl_803DC318[self->choice][1];
                self->state = 4;
                fn_80230678(self->other);
            }
        }
        break;
    case 4:
        self->x = lbl_803DC318[self->choice][0];
        self->y = lbl_803DC318[self->choice][1];
        self->state = 0;
        self->selected = 0;
        break;
    }
}
