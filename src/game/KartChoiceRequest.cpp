#include "game/types/clFRnkDisp.h"

extern "C" const float lbl_803DC318[2][2] = {
    {64.399994f, 372.8f},
    {64.399994f, 408.2f}
};

clFRnkDisp::clFRnkDisp(int layer_)
    : layer(layer_), phase(-1), choice(1), child(0), other(0),
      fade(new FlowFaderF(lbl_806DB980)), scale(new FlowFaderF(lbl_806DB980)),
      render(0), state(0), selected(0), x(lbl_806DB980), y(lbl_806DB980),
      vx(lbl_806DB980), vy(lbl_806DB980) {
    PreloadResource(0xc2f);
    PreloadResource(0xc30);
    PreloadResource(0xc31);
    fade.p->Set(lbl_806DB98C, lbl_806DB980, 7);
    scale.p->Set(lbl_806DB984, lbl_806DB984, 1);
    if (ServiceEnable_Get() && !ServiceValue_Get() && Sci2Card_GetByteFlag1224())
        choice = 0;
    void *car = GetPlayerCarObject();
    if (car) {
        render = CarObject_GetRenderObj(car);
        child = new ChoiceChild(render, layer_);
        other = new ChoiceOther(render, layer_);
    }
}

clFRnkDisp::~clFRnkDisp() {
    if (other) { delete other; other = 0; }
    /* The child vtable is owned elsewhere; deletion uses its virtual root view. */
    if (child) { delete (VObject *)child; child = 0; }
}

extern "C" clFRnkDisp *fn_8023BB6C(int layer) {
    return new clFRnkDisp(layer);
}

static inline void HideChoiceChild(ChoiceChild *child) {
    child->hidden = 1;
    for (int i = 0; i < 4; ++i) {
        SpriteHandle_SetActiveFlag(child->sprites[i], 0);
        SpriteHandle_RecomputeCull(child->sprites[i]);
    }
}
void clFRnkDisp::Update() {
    switch (this->phase) {
    case -1:
        if (g_countdownPhase <= 3) this->phase = 0;
        break;
    case 0:
        this->fade.p->Step();
        if (this->fade.p->Done()) {
            this->phase = 1;
            this->fade.p->Set(lbl_806DB980, lbl_806DB980, 1);
        }
        break;
    case 1:
        if (g_countdownPhase <= 2) {
            this->scale.p->Set(lbl_806DB984, lbl_806DB988, 4);
            this->phase = 2;
        }
        break;
    case 2:
        if (this->scale.p->Done() && lbl_806DB984 == this->scale.p->Value()) this->phase = 3;
        break;
    case 3: break;
    case 4: {
        HideChoiceChild(this->child);
        this->phase = 5;
        this->x = lbl_803DC318[this->choice][0];
        this->y = lbl_803DC318[this->choice][1];
        this->selected = 0;
        this->state = 0;
        break;
    }
    case 5: return;
    default: return;
    }
    if (this->id > 0) {
        --this->id;
        if (this->id <= 0) {
            this->id = 0;
            this->phase = 4;
            this->fade.p->Set(lbl_806DB980, lbl_806DB98C, 7);
        }
    }
    float value = this->fade.p->Value();
    float x, y;
    y = lbl_803DC318[this->choice][1];
    x = lbl_803DC318[this->choice][0] - value;
    fn_8023B318((KartChoiceOwner *)this);
    if (this->state != 0) {
        value = this->fade.p->Value();
        y = this->y;
        x = this->x - value;
    }
    if (this->child) {
        ChoiceChild *child = this->child;
        child->x = x;
        child->y = y;
        this->child->scale = this->scale.p->Value();
        fn_8023BEF0(this->child);
    }
    if (this->other) {
        ChoiceOther *other = this->other;
        other->x = x;
        other->y = y;
        this->other->scale = lbl_806DB990;
        fn_80230ED8(this->other, 1);
    }
    this->scale.p->Step();
    if (this->scale.p->Done()) {
        value = this->scale.p->Value();
        if (lbl_806DB988 == value)
            this->scale.p->Set(lbl_806DB988, lbl_806DB984, 4);
        else if (lbl_806DB984 == value)
            this->scale.p->Set(lbl_806DB984, lbl_806DB984, 1);
    }
}

void clFRnkDisp::Draw() {
    if (this->phase < 5) {
        if (this->other) fn_80230ED4(this->other, 1);
    }
}

void clFRnkDisp::Request() {
    if (this->phase < 4) this->phase = 4;
}
