#include "game/KartChoiceOwnerPrivate.h"
KartChoiceOwner::KartChoiceOwner(int layer_)
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
