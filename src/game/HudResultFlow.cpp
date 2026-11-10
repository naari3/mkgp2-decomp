#include "game/HudResultFlowPrivate.h"
extern "C" void fn_80248904(HudRoot *self, unsigned int state) {
    if (self->child) {
        switch (state) {
        case 0: self->state=2; break;
        case 1: self->state=2; fn_8021A0B0(lbl_806D1A60); break;
        case 2: self->state=4; fn_8021A0B0(lbl_806D1A60); break;
        case 4:
            if (!lbl_806D17F0) self->state=6; else self->state=-1;
            fn_8021A0D0(lbl_806D1A60); break;
        case 6: self->state=-1; break;
        }
        if (self->state == -1 && fn_8019083C(1)) fn_801909A4(1);
        if (self->child) { self->child->Stop(); self->child=0; }
    }
}
extern "C" void fn_80248A08(HudRoot *self, unsigned int state) {
    if (!self->child) {
        fn_8024F43C(fn_8024F588());
        switch (state) {
        case 0:
            if (!fn_8019083C(1)) { ClSound_PlayBgmStream(1,0); clStream_setVolume(1,fn_801932F8()); }
            self->child=fn_8021E0C0(); break;
        case 1:
            fn_8021A0DC(lbl_806D1A60);
            if (!fn_8019083C(1)) { ClSound_PlayBgmStream(1,0); clStream_setVolume(1,fn_801932F8()); }
            self->child=fn_80160238(); break;
        case 2:
            fn_8021A0DC(lbl_806D1A60);
            if (!fn_8019083C(1)) { ClSound_PlayBgmStream(1,0); clStream_setVolume(1,fn_801932F8()); }
            self->child=fn_80223500(); break;
        case 4:
            fn_80219FF4(lbl_806D1A60);
            if (!fn_8019083C(1)) { ClSound_PlayBgmStream(1,0); clStream_setVolume(1,fn_801932F8()); }
            self->child=fn_8024C564(); break;
        case 6:
            if (fn_8019083C(1)) fn_801909A4(1);
            fn_8024F530(); self->child=(HudChild *)new HudSmall; break;
        default: self->child=0; break;
        }
    }
}
extern "C" HudRoot *fn_80248BA8(HudRoot *self, short flag) {
    if (self) {
        self->vptr=HudResultFlow_data_804EEBA8; self->hostVptr=HudResultFlow_data_804EEBA8+6;
        dtor_80249274(self,0);
        if (flag > 0) MemoryManager_TimedFree(self);
    }
    return self;
}
HudResultFlow::HudResultFlow() {
    vptr=HudResultFlow_data_804EEBA8; hostVptr=HudResultFlow_data_804EEBA8+6;
    CalcEarnedCoins();
    if (g_raceEnded == 1) state=0;
    else if (has_title_changed() == 1) state=1;
    else state=2;
    ((HudEnterView *)this)->Enter(state);
}
extern "C" void fn_80248CAC(HudChild *self) { delete (HudDeleteView *)self; }
