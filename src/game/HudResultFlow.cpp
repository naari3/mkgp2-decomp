/* Deferred generation emits definitions in reverse target-address order.
 * The compiler emits the primary/secondary vtables and destructor thunk. */
#include "game/HudFlowPrivate.h"
#include "game/types/clResultType01.h"
extern "C" {
HudChild *fn_8021E0C0();
HudChild *fn_8024C564();
void CalcEarnedCoins();
}
void clResultType01::Destroy() { delete this; }
clResultType01::clResultType01() {
    CalcEarnedCoins();
    if (g_raceEnded == 1) this->state=0;
    else if (has_title_changed() == 1) this->state=1;
    else this->state=2;
    Enter(this->state);
}
clResultType01::~clResultType01() {}
void clResultType01::Enter(unsigned int state) {
    if (!this->child) {
        fn_8024F43C(fn_8024F588());
        switch (state) {
        case 0:
            if (!fn_8019083C(1)) { ClSound_PlayBgmStream(1,0); clStream_setVolume(1,fn_801932F8()); }
            this->child=fn_8021E0C0(); break;
        case 1:
            fn_8021A0DC(lbl_806D1A60);
            if (!fn_8019083C(1)) { ClSound_PlayBgmStream(1,0); clStream_setVolume(1,fn_801932F8()); }
            this->child=fn_80160238(); break;
        case 2:
            fn_8021A0DC(lbl_806D1A60);
            if (!fn_8019083C(1)) { ClSound_PlayBgmStream(1,0); clStream_setVolume(1,fn_801932F8()); }
            this->child=fn_80223500(); break;
        case 4:
            fn_80219FF4(lbl_806D1A60);
            if (!fn_8019083C(1)) { ClSound_PlayBgmStream(1,0); clStream_setVolume(1,fn_801932F8()); }
            this->child=fn_8024C564(); break;
        case 6:
            if (fn_8019083C(1)) fn_801909A4(1);
            fn_8024F530(); this->child=(HudChild *)new HudSmall; break;
        default: this->child=0; break;
        }
    }
}
void clResultType01::Leave(unsigned int state) {
    if (this->child) {
        switch (state) {
        case 0: this->state=2; break;
        case 1: this->state=2; fn_8021A0B0(lbl_806D1A60); break;
        case 2: this->state=4; fn_8021A0B0(lbl_806D1A60); break;
        case 4:
            if (!lbl_806D17F0) this->state=6; else this->state=-1;
            fn_8021A0D0(lbl_806D1A60); break;
        case 6: this->state=-1; break;
        }
        if (this->state == -1 && fn_8019083C(1)) fn_801909A4(1);
        if (this->child) { this->child->Stop(); this->child=0; }
    }
}
