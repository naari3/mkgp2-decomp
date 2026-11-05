#include "game/cxc_card_flow.h"
extern "C" void fn_801FA310(CardStep *self) {
    int n4;
    void *p4;
    CardInput *input = InputMgr_GetPlayer(GetInputManager(), 0);
    switch (self->state) {
    case 0: fn_801FA864(self); break;
    case 1:
        if (input->Pressed(lbl_806DA860)) { CardMode *m = fn_801DAEC0(); m->light = 0; }
        else { CardMode *m = fn_801DAEC0(); m->light = 1; }
        CardFadeTick(self->fader);
        if (input->Pressed(lbl_806DA860) || self->fader->time >= self->fader->duration) {
            fn_80203EA0(); self->state = 8;
        }
        break;
    case 2:
        CardFadeTick(self->fader);
        if (self->fader->time >= self->fader->duration) {
            fn_8020A7CC(self->fader, 0, 0, 1);
            if (fn_801F4DC0(self->seq, 4)) {
                self->state = 5; fn_80202A5C(0x10);
            } else { self->state = 3; fn_80202A5C(0x12); }
        }
        break;
    case 3: fn_801FA6A4(self); break;
    case 4: {
        p4 = fn_801F4DC0(self->seq, 3);
        if (p4) self->result = *(int *)(fn_80271340(p4, 0, &lbl_806D00F8, &lbl_806D00C8, 0) + 0x24);
        n4 = 0;
        if (p4) n4 = *(int *)(fn_80271340(p4, 0, &lbl_806D00F8, &lbl_806D00C8, 0) + 0x20);
        void *q = fn_801F4DC0(self->seq, 8);
        if (q) fn_801FEF18(fn_80271340(q, 0, &lbl_806D00D0, &lbl_806D00C8, 0), n4);
        if (!p4) self->state = 8;
        break;
    }
    case 5: {
        int n;
        void *p = fn_801F4DC0(self->seq, 4);
        if (p) self->result = *(int *)(fn_80271340(p, 0, &lbl_806D0100, &lbl_806D00C8, 0) + 0x24);
        n = 0;
        if (p) n = *(int *)(fn_80271340(p, 0, &lbl_806D0100, &lbl_806D00C8, 0) + 0x20);
        void *q = fn_801F4DC0(self->seq, 8);
        if (q) fn_801FEF18(fn_80271340(q, 0, &lbl_806D00D0, &lbl_806D00C8, 0), n);
        if (!p) self->state = 8;
        break;
    }
    case 8: {
        fn_802043B8(self->seq, 8);
        void *p = fn_801F4DC0(self->seq, 9);
        if (p) fn_801FFFF4(fn_80271340(p, 0, &lbl_806D00D8, &lbl_806D00C8, 0));
        p = fn_801F4DC0(self->seq, 10);
        if (p) fn_80201148(fn_80271340(p, 0, &lbl_806D00E0, &lbl_806D00C8, 0));
        fn_80203EA0(); self->state = 9;
        break;
    }
    case 9:
        if (self->seq->count <= 0 && fn_80203E30() == -1) { self->done = 1; self->state = -1; }
        break;
    }
    self->seq->Tick();
}
