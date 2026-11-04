#include "game/cxc_card_flow.h"
struct ReadCardStep : CardStep {
    int timeout, active, next;
    int pad2c;
    unsigned char reading;
    char pad31[3];
    int flash;
};
extern "C" {
extern unsigned char lbl_806D14A0;
void fn_80207AD8(int, int); void fn_80207760(int);
void card_send_cleaning_cmd_init();
void fn_801FB418(ReadCardStep *);
unsigned char card_cleaning_state_machine();
int Sci2Card_GetPrintErrorCode(); int fn_801FE030(int, int);
void fn_80207CC4(int); void fn_801FE348();
void fn_801F4D3C(void *); void fn_80203E4C(); void fn_802078B4();
void card_send_ping_cmd_init(); unsigned char card_ping_state_machine();
int fn_801FDF20(); void Sci2Card_ResetRetryAndStatus();
unsigned char Sci2Card_GetByteFlag1224();
void card_send_read_cmd_init(); void fn_801FAFFC(ReadCardStep *);
void fn_802078F8(); unsigned char fn_80207880();
int Sci2Card_PollResponseStatusTri(); void fn_801FE27C(int);
}
extern "C" void fn_801FAB88(ReadCardStep *self) {
    CardInput *input = InputMgr_GetPlayer(GetInputManager(), 0);
    int state = self->state;
    if (state != 7 && state != 8) {
        if (input->Pressed(lbl_806DA860)) self->flash = 10;
        if (self->flash > 0) {
            self->flash--;
            CardMode *m = fn_801DAEC0(); m->light = 4;
        } else { CardMode *m = fn_801DAEC0(); m->light = 1; }
    }
    switch (state) {
    case -1: break;
    case 0:
        fn_80207AD8(0, 1);
        if (lbl_806D14A0) fn_80207760(0);
        card_send_cleaning_cmd_init();
        fn_8020A7CC(self->fader, 0, 30, 30);
        self->state = 1;
        break;
    case 1:
        CardFadeTick(self->fader);
        if (self->fader->time >= self->fader->duration) self->state = 2;
        break;
    case 2: fn_801FB418(self); break;
    case 3:
        if (card_cleaning_state_machine() == 1) {
            switch (fn_801FE030(Sci2Card_GetPrintErrorCode(), 0)) {
            case 0:
                fn_80203EA0(); fn_80207CC4(0); self->active = 0;
                fn_801FE348(); self->state = 7;
                break;
            case 6: case 7:
                fn_801F4D3C(self->seq); fn_80203E4C(); fn_802078B4(); self->state = -1;
                break;
            case 9:
                card_send_ping_cmd_init(); self->state = 4;
                break;
            case 8: break;
            }
        }
        break;
    case 4:
        if (card_ping_state_machine()) {
            switch (fn_801FDF20()) {
            default:
                fn_80207CC4(0); self->active = 0; fn_80203EA0();
                Sci2Card_ResetRetryAndStatus(); self->state = 8; self->result = 0;
                break;
            case 0:
                if (!Sci2Card_GetByteFlag1224()) {
                    if (self->active == 0) { fn_80207CC4(1); self->active = 1; }
                    fn_801FE348(); fn_80203EA0(); self->state = 9;
                } else {
                    fn_80207CC4(0); self->active = 0; fn_80203EA0(); self->state = 7;
                }
                break;
            case 6: case 7:
                fn_801F4D3C(self->seq); fn_80203E4C(); fn_802078B4(); self->state = -1;
                break;
            }
        }
        break;
    case 5:
        fn_80207CC4(0);
        CardFadeTick(self->fader);
        if (self->fader->time >= self->fader->duration) {
            self->active = 0; fn_801FE348(); self->state = self->next;
        }
        break;
    case 6:
        fn_80207CC4(1);
        CardFadeTick(self->fader);
        if (self->fader->time >= self->fader->duration) {
            self->active = 1; fn_801FE348(); self->state = self->next;
        }
        break;
    case 7:
        if (fn_80203E30() == -1) { CardMode *m = fn_801DAEC0(); m->light = 4; }
        else { CardMode *m = fn_801DAEC0(); m->light = 0; }
        self->reading = 1; card_send_read_cmd_init(); self->state = 8; self->result = 0;
        break;
    case 8: fn_801FAFFC(self); break;
    case 9: fn_802078F8(); self->state = 10; break;
    case 10:
        if (self->seq->count <= 0 && !fn_80207880()) { self->done = 1; self->state = -1; }
        break;
    }
    if (self->state >= 2 && self->timeout > 0 && !self->reading) self->timeout--;
    if (self->timeout <= 0 && Sci2Card_PollResponseStatusTri() == 2) self->timeout = 1;
    fn_801FE27C(self->timeout);
    self->seq->Tick();
}
