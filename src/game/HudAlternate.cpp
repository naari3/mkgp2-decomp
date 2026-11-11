/* Deferred generation: definitions are in reverse target-address order. */
#include "game/HudFlowPrivate.h"
#include "game/types/clResultType02.h"
extern "C" {
extern unsigned char lbl_806D17F1, lbl_806D17F2;
HudChild *fn_8024C0F4();
}
void clResultType02::Destroy() { delete this; }
clResultType02::clResultType02() {
    state=0;
    Enter(state);
}
clResultType02::~clResultType02() {}
void clResultType02::Enter(unsigned int state) {
    if (!this->child) {
        fn_8024F43C(fn_8024F588());
        switch (state) {
        case 0:
            if (!fn_8019083C(1)) { ClSound_PlayBgmStream(1,0); clStream_setVolume(1,fn_801932F8()); }
            this->child=fn_8014CEAC(); break;
        case 2:
            fn_8021A0DC(lbl_806D1A60);
            if (!fn_8019083C(1)) { ClSound_PlayBgmStream(1,0); clStream_setVolume(1,fn_801932F8()); }
            this->child=fn_80223500(); break;
        case 4:
            fn_8021A0DC(lbl_806D1A60);
            if (!fn_8019083C(1)) { ClSound_PlayBgmStream(1,0); clStream_setVolume(1,fn_801932F8()); }
            this->child=fn_8024C0F4(); break;
        case 6:
            if (fn_8019083C(1)) fn_801909A4(1);
            fn_8024F530(); this->child=(HudChild *)new HudSmall; break;
        default: this->child=0; break;
        }
    }
}
void clResultType02::Leave(unsigned int state) {
    if (this->child) {
        switch (state) {
        case 0: this->state=2; break;
        case 2: this->state=4; fn_8021A0B0(lbl_806D1A60); break;
        case 4:
            fn_8021A0D0(lbl_806D1A60);
            if (lbl_806D17F0) {
                if (fn_8019083C(1)) fn_801909A4(1);
                this->state=-1;
            } else this->state=6;
            fn_8021A0D0(lbl_806D1A60); break;
        case 6:
            lbl_806D17F0=0; lbl_806D17F1=0; lbl_806D17F2=0;
            this->state=-1; break;
        }
        if (this->child) { this->child->Stop(); this->child=0; }
    }
}
