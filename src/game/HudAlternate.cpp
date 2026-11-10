#include "game/HudAlternatePrivate.h"
extern "C" void fn_80248CEC(HudRoot *self, unsigned int state) {
    if (self->child) {
        switch (state) {
        case 0: self->state=2; break;
        case 2: self->state=4; fn_8021A0B0(lbl_806D1A60); break;
        case 4:
            fn_8021A0D0(lbl_806D1A60);
            if (lbl_806D17F0) {
                if (fn_8019083C(1)) fn_801909A4(1);
                self->state=-1;
            } else self->state=6;
            fn_8021A0D0(lbl_806D1A60); break;
        case 6:
            lbl_806D17F0=0; lbl_806D17F1=0; lbl_806D17F2=0;
            self->state=-1; break;
        }
        if (self->child) { self->child->Stop(); self->child=0; }
    }
}
extern "C" void fn_80248DE8(HudRoot *self, unsigned int state) {
    if (!self->child) {
        fn_8024F43C(fn_8024F588());
        switch (state) {
        case 0:
            if (!fn_8019083C(1)) { ClSound_PlayBgmStream(1,0); clStream_setVolume(1,fn_801932F8()); }
            self->child=fn_8014CEAC(); break;
        case 2:
            fn_8021A0DC(lbl_806D1A60);
            if (!fn_8019083C(1)) { ClSound_PlayBgmStream(1,0); clStream_setVolume(1,fn_801932F8()); }
            self->child=fn_80223500(); break;
        case 4:
            fn_8021A0DC(lbl_806D1A60);
            if (!fn_8019083C(1)) { ClSound_PlayBgmStream(1,0); clStream_setVolume(1,fn_801932F8()); }
            self->child=fn_8024C0F4(); break;
        case 6:
            if (fn_8019083C(1)) fn_801909A4(1);
            fn_8024F530(); self->child=(HudChild *)new HudSmall; break;
        default: self->child=0; break;
        }
    }
}
extern "C" HudRoot *fn_80248F48(HudRoot *self, short flag) {
    if (self) {
        self->vptr=HudAlternate_data_804EEC30; self->hostVptr=HudAlternate_data_804EEC30+6;
        dtor_80249274(self,0);
        if (flag>0) MemoryManager_TimedFree(self);
    }
    return self;
}
HudAlternate::HudAlternate() {
    vptr=HudAlternate_data_804EEC30; hostVptr=HudAlternate_data_804EEC30+6;
    state=0;
    ((HudEnterView *)this)->Enter(state);
}
extern "C" void fn_80249014(HudChild *self) { delete (HudDeleteView *)self; }
