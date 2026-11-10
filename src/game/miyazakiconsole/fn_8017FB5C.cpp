#include "game/FlowScene.h"

#include "game/miyazakiconsole/console_update_private.h"
extern "C" {
void fn_80180100();
void CGameCoin_ProcessInput(InputState *);
void *GetInputManager();
ConsoleInput *InputMgr_GetPlayer(void *, int);
extern ConsolePage *lbl_806D15FC;
extern int lbl_806D1600;
extern int lbl_806D15F8;
extern unsigned char lbl_806CFBA1;
void fn_80202BCC();
void fn_80202A24();
void *fn_801DAEC0();
void fn_801DABFC(void *);
void fn_8014F5E0();
void fn_80181144();
}
extern "C" int fn_8017FB5C() {
    fn_80180100();
    if (GetInput() != 0) CGameCoin_ProcessInput(GetInput());
    if (lbl_806D15FC != 0) {
        unsigned char close = 0;
        if (InputMgr_GetPlayer(GetInputManager(), 0)->IsHeld(0x400)) {
            if (++lbl_806D1600 >= 60) close = 1;
        } else {
            lbl_806D1600 = 0;
        }
        if (lbl_806D15FC->closed != 0 || close) {
            lbl_806D15FC->Release();
            lbl_806D15FC = 0;
            fn_80202BCC();
            if (lbl_806CFBA1 != 1) lbl_806CFBA1 = 1;
        } else {
            fn_80202A24();
            lbl_806D15FC->Update();
            fn_801DABFC(fn_801DAEC0());
        }
        fn_8014F5E0();
    } else {
        fn_80181144();
    }
    if (lbl_806D15F8 != 0) {
        switch (lbl_806D15F8) {
        case 1:
            return -4;
        }
    }
    return -2;
}
