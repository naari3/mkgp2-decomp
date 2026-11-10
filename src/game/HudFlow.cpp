#include "game/HudFlowPrivate.h"
extern "C" void fn_802483B4(HudRoot *self, unsigned int state) {
    if (self->child) {
        switch (state) {
        case 0: if (fn_8024F588()->flag) self->state=-1; else self->state=2; break;
        case 1: self->state=2; break;
        case 2:
            self->state=4;
            if (fn_8024F588()->mode == 1 && g_roundIndex != 3 && g_roundIndex != 7 && g_cupId < 9) {
                fn_8021A0D0(lbl_806D1A60); self->state=3;
            }
            if ((unsigned char)(fn_8024F588()->index >= 0) == 1) {
                if (fn_8019083C(1)) fn_801909A4(1);
                self->state=5;
            }
            fn_8021A0B0(lbl_806D1A60); break;
        case 3: self->state=4; fn_8021A0DC(lbl_806D1A60); break;
        case 4:
            fn_8021A0D0(lbl_806D1A60); ItemDisplay_Stop(ItemDisplay_GetOrCreate());
            if (!lbl_806D17F0) self->state=6; else self->state=-1; break;
        case 5:
            ClSound_PlayBgmStream(1,0); clStream_setVolume(1,fn_801932F8()); self->state=4; break;
        case 6: self->state=-1; break;
        }
        if (self->state == -1 && fn_8019083C(1)) fn_801909A4(1);
        if (self->child) { self->child->Stop(); self->child=0; }
    }
}
extern "C" void fn_8024858C(HudRoot *self, unsigned int state) {
    if (!self->child) {
        fn_8024F43C(fn_8024F588());
        switch (state) {
        case 0:
            if (!fn_8019083C(1)) { ClSound_PlayBgmStream(1,0); clStream_setVolume(1,fn_801932F8()); }
            self->child=fn_8014CEAC(); break;
        case 1:
            if (!fn_8019083C(1)) { ClSound_PlayBgmStream(1,0); clStream_setVolume(1,fn_801932F8()); }
            fn_8021A0DC(lbl_806D1A60); self->child=fn_80160238(); break;
        case 2:
            if (!fn_8019083C(1)) { ClSound_PlayBgmStream(1,0); clStream_setVolume(1,fn_801932F8()); }
            fn_8021A0DC(lbl_806D1A60); self->child=fn_80223500(); break;
        case 3:
            if (!fn_8019083C(1)) { ClSound_PlayBgmStream(1,0); clStream_setVolume(1,fn_801932F8()); }
            self->child=fn_802253B0(); break;
        case 4:
            if (!fn_8019083C(1)) { ClSound_PlayBgmStream(1,0); clStream_setVolume(1,fn_801932F8()); }
            fn_80219FF4(lbl_806D1A60); self->child=fn_8024CA18(); break;
        case 5: self->child=fn_8015CB5C(fn_8024F588()->index); break;
        case 6:
            if (fn_8019083C(1)) fn_801909A4(1);
            fn_8024F530(); self->child=(HudChild *)new HudSmall; break;
        default: self->child=0; break;
        }
    }
}
extern "C" HudRoot *fn_80248778(HudRoot *self, short flag) {
    if (self) {
        self->vptr=HudFlow_data_804EEB20; self->hostVptr=HudFlow_data_804EEB20+6;
        dtor_80249274(self,0);
        if (flag > 0) MemoryManager_TimedFree(self);
    }
    return self;
}
HudFlow::HudFlow() {
    vptr=HudFlow_data_804EEB20; hostVptr=HudFlow_data_804EEB20+6;
    int cup=g_cupId;
    fn_801DC870(0);
    if (cup >= 9) {
        if (has_title_changed() == 1) state=1; else state=2;
    } else if (!g_raceEnded) {
        if (has_title_changed() == 1) state=1; else state=2;
        fn_801DC870(1);
    } else state=0;
    ((HudEnterView *)this)->Enter(state);
}
extern "C" void fn_802488C4(HudChild *self) { delete (HudDeleteView *)self; }

