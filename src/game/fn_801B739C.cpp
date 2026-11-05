#include "game/VoiceBrowser_private.h"

extern "C" int fn_801B739C(VoiceBrowser *self) {
    InputPlayer *input = InputMgr_GetPlayer(GetInputManager(), 0);
    VoiceClip *clip = fn_801B3A50(self->selection);
    float step = lbl_806D9860 * input->v2();
    if (lbl_806D9864 < step && step < lbl_806D9868)
        step = lbl_806D986C;
    self->fraction += step;
    if (self->fraction >= lbl_806D9854) {
        self->selection++;
        self->fraction -= lbl_806D984C;
    } else if (self->fraction <= lbl_806D9848) {
        self->selection--;
        self->fraction += lbl_806D984C;
    }
    float value = input->StickRight();
    if (value > lbl_806D9860)
        clip->length += lbl_806D9870 * (value - lbl_806D9860);
    value = input->StickLeft();
    if (value > lbl_806D9860) {
        float minimum = lbl_806D986C;
        clip->length = clip->length - lbl_806D9870 * (value - lbl_806D9860);
        if (clip->length < minimum)
            clip->length = minimum;
    }
    if (input->Pressed(0x800)) {
        self->selection++;
        self->fraction = lbl_806D986C;
    }
    fn_801B11B8();
    if (input->Pressed(0x2000))
        fn_801B3980(fn_801B3A88(self->selection));
    if (input->Pressed(0x400))
        fn_801B3A4C();
    return -2;
}
