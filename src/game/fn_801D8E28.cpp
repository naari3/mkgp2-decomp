#include "game/FlowKartPosition_private.h"
// Text offsets are formed in component order before the by-value setter copy.
static inline FKPosition FKTextOffset(float x, float y, const FKPosition &b) {
    FKPosition r;
    r.y = y + b.y;
    r.x = x + b.x;
    return r;
}

extern "C" void fn_801D8E28(FKPositionPanel *self, float x, float y) {
    if (self->labelA) self->labelA->SetPosition(x,y);
    if (self->mode == 1) {
        FKPlaceText(self->texts[0],FKTextOffset(x,y,lbl_8039FC60[1]));
        FKPlaceText(self->texts[1],FKTextOffset(x,y,lbl_8039FC60[2]));
        FKPlaceText(self->texts[2],FKOffset(x,y,lbl_8039FC60[3]));
    } else {
        FKPlaceText(self->texts[0],FKTextOffset(x,y,lbl_8039FC60[4]));
        FKPlaceText(self->texts[1],FKTextOffset(x,y,lbl_8039FC60[5]));
        FKPlaceText(self->texts[2],FKOffset(x,y,lbl_8039FC60[6]));
    }
    self->icons[1]->SetPosition(FKOffset(x,y,lbl_8039FC60[7]));
    self->icons[0]->SetPosition(FKOffset(x,y,lbl_8039FC60[9]));
    self->icons[2]->SetPosition(FKOffset(x,y,lbl_8039FC60[8]));
    if (self->state == 2) self->icons[1]->SetPosition(FKOffset(x,y,lbl_8039FC60[9]));
    if (self->state == 3) self->labelB->SetPosition(FKOffset(x,y,lbl_8039FC60[7]));
}
