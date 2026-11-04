#include "game/KartChoiceOwnerPrivate.h"
static inline void HideChoiceChild(ChoiceChild *child) {
    child->hidden = 1;
    for (int i = 0; i < 4; ++i) {
        SpriteHandle_SetActiveFlag(child->sprites[i], 0);
        SpriteHandle_RecomputeCull(child->sprites[i]);
    }
}
extern "C" void fn_8023B838(KartChoiceOwner *self) {
    switch (self->phase) {
    case -1:
        if (g_countdownPhase <= 3) self->phase = 0;
        break;
    case 0:
        self->fade.p->Step();
        if (self->fade.p->Done()) {
            self->phase = 1;
            self->fade.p->Set(lbl_806DB980, lbl_806DB980, 1);
        }
        break;
    case 1:
        if (g_countdownPhase <= 2) {
            self->scale.p->Set(lbl_806DB984, lbl_806DB988, 4);
            self->phase = 2;
        }
        break;
    case 2:
        if (self->scale.p->Done() && lbl_806DB984 == self->scale.p->Value()) self->phase = 3;
        break;
    case 3: break;
    case 4: {
        HideChoiceChild(self->child);
        self->phase = 5;
        self->x = lbl_803DC318[self->choice][0];
        self->y = lbl_803DC318[self->choice][1];
        self->selected = 0;
        self->state = 0;
        break;
    }
    case 5: return;
    default: return;
    }
    if (self->countdown > 0) {
        --self->countdown;
        if (self->countdown <= 0) {
            self->countdown = 0;
            self->phase = 4;
            self->fade.p->Set(lbl_806DB980, lbl_806DB98C, 7);
        }
    }
    float value = self->fade.p->Value();
    float x, y;
    y = lbl_803DC318[self->choice][1];
    x = lbl_803DC318[self->choice][0] - value;
    fn_8023B318(self);
    if (self->state != 0) {
        value = self->fade.p->Value();
        y = self->y;
        x = self->x - value;
    }
    if (self->child) {
        ChoiceChild *child = self->child;
        child->x = x;
        child->y = y;
        self->child->scale = self->scale.p->Value();
        fn_8023BEF0(self->child);
    }
    if (self->other) {
        ChoiceOther *other = self->other;
        other->x = x;
        other->y = y;
        self->other->scale = lbl_806DB990;
        fn_80230ED8(self->other, 1);
    }
    self->scale.p->Step();
    if (self->scale.p->Done()) {
        value = self->scale.p->Value();
        if (lbl_806DB988 == value)
            self->scale.p->Set(lbl_806DB988, lbl_806DB984, 4);
        else if (lbl_806DB984 == value)
            self->scale.p->Set(lbl_806DB984, lbl_806DB984, 1);
    }
}
