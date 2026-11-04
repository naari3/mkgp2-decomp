#include "game/CardModeRoot_private.h"

void CardModeRoot::OnTaskDone(int st) {
    if (task != 0) {
        if (st == 3) {
            CardMenuRoot *menu = dynamic_cast<CardMenuRoot *>(task);
            mode = fn_801FE404()->mode;
            chara = fn_801FE404()->chara;
            f08 = menu->f08;
            f0C = menu->f0C;
            f10 = menu->f10;
            f14 = menu->f14;
            f48 = menu->f48;
        }
        task->Destroy();
        task = 0;
        switch (st) {
        case 0:
            fn_80218F1C();
            ServiceMode_UpdateScheduleGate();
            if (GetInput() == 0) {
                CreateInputState();
            }
            if (fn_801FE404()->f194) {
                f28 = 0;
                SetLocalPcbRole(0);
                {
                    FlowMgrInfo *st = fn_801FE404();
                    st->f168 = 0;
                }
                StrPcb_ForceRun_Neutral(StrPcb_GetInstance());
                StrPcb_ResetCommands_Neutral(StrPcb_GetInstance(), 1);
                state = 3;
            } else {
                state = 1;
            }
            break;
        case 1:
            f28 = fn_801FE404()->f168;
            if (lbl_806D12B0) {
                if (f28 > 0) {
                    mode = 2;
                    fn_801FE404()->mode = mode;
                }
                state = 3;
            } else {
                state = 0;
            }
            break;
        case 2:
            f28 = fn_801FE404()->f168;
            if (lbl_806D12B0) {
                state = 3;
            } else {
                state = 0;
            }
            break;
        case 3: {
            int i;
            for (i = 0; i < 3; i++) {
                f30[i] = fn_801FE404()->f188[i];
            }
            state = 4;
            break;
        }
        case 4:
            state = -1;
            break;
        }
    }
}
