#include "game/anon_801FC1E0_private.h"

extern "C" void fn_801FC614(FlowScene *self) {
    self->task->f10();
}

extern "C" void fn_801FC644(CardFlowScene *self) {
    CardInput *input = InputMgr_GetPlayer(GetInputManager(), 0);
    int state = self->state;
    if (state != 1 && state != 8) {
        if (input->Pressed(lbl_806DA860)) self->field44 = 10;
        if (self->field44 > 0) {
            --self->field44;
            { CardMode *mode = fn_801DAEC0(); mode->light = 4; }
        } else {
            { CardMode *mode = fn_801DAEC0(); mode->light = 1; }
        }
    }
    switch (state) {
    case 0:
        if (self->arg2C == 1) {
            if (!g_playerData[0x1A0]) {
                self->slot = 3;
                fn_80203F5C(6);
            } else {
                self->slot = 4;
                fn_80203F5C(27);
            }
        } else {
            if (!g_playerData[0x1A0]) {
                self->slot = 3;
                fn_80203F5C(7);
            } else {
                self->slot = 4;
                fn_80203F5C(26);
            }
        }
        CreditMgr_SetActiveSlot(self->slot);
        fn_8020A7CC(self->fader, 0, lbl_806D19C8[0], (short)lbl_806D19C8[0]);
        self->state = 1;
        break;
    case 1:
        if (input->Pressed(lbl_806DA860)) { CardMode *mode = fn_801DAEC0(); mode->light = 0; }
        else { CardMode *mode = fn_801DAEC0(); mode->light = 1; }
        CardFadeTick(self->fader);
        if (self->fader->time >= self->fader->duration || input->Pressed(lbl_806DA860)) {
            if (Sci2Card_GetReceiptTestFlag()) {
                fn_80203F5C(10);
                fn_8020A7CC(self->fader, 0, lbl_806D19C8[0], (short)lbl_806D19C8[0]);
                self->field30 = 180;
                self->state = 2;
            } else {
                fn_80203EA0();
                self->state = 3;
            }
        }
        break;
    case 2:
        if (input->Pressed(lbl_806DA860)) { CardMode *mode = fn_801DAEC0(); mode->light = 0; }
        else { CardMode *mode = fn_801DAEC0(); mode->light = 1; }
        CardFadeTick(self->fader);
        if (self->field30 != 0) --self->field30;
        else if (self->fader->time >= self->fader->duration || input->Pressed(lbl_806DA860)) {
            fn_80203EA0();
            PlayerData_ResetForFlow();
            fn_801FE3BC();
            fn_801FE404();
            lbl_806D19C0 = 0;
            self->state = 8;
            self->subState = 0;
        }
        break;
    case 3:
        if (fn_80203E30() == -1) {
            if (g_currentSceneState < 44) {
                if (self->slot == 3) fn_80207AD8(10, 1);
                else fn_80207AD8(12, 1);
            } else {
                if (self->slot == 3) fn_80207AD8(2, 1);
                else fn_80207AD8(11, 1);
            }
            fn_8020A7CC(self->fader, 0, 30, 30);
            self->state = 4;
        }
        break;
    case 4:
        CardFadeTick(self->fader);
        if (self->fader->time >= self->fader->duration) {
            int coins = CreditMgr_GetCoinCount(0, -1);
            if (self->coins != coins) self->timer = 1201;
            self->coins = coins;
            self->field41 = CardCreditUnavailable(self);
            self->state = 5;
        }
        break;
    case 5:
        fn_801FCF58(self);
        break;
    case 6:
        fn_80207CC4(0);
        CardFadeTick(self->fader);
        if (self->fader->time >= self->fader->duration) {
            self->cursor = 0;
            fn_801FE348();
            self->state = self->kind;
        }
        break;
    case 7:
        fn_80207CC4(1);
        CardFadeTick(self->fader);
        if (self->fader->time >= self->fader->duration) {
            self->cursor = 1;
            fn_801FE348();
            self->state = self->kind;
        }
        break;
    case 8:
        { CardMode *mode = fn_801DAEC0(); mode->light = 0; }
        fn_801FCD9C(self);
        break;
    case 9:
        fn_801FCBCC(self);
        break;
    case 10:
        fn_802078F8();
        self->state = 11;
        break;
    case 11:
        if (self->task->count <= 0 && !fn_80207880()) {
            self->done = 1;
            self->state = -1;
        }
        break;
    }
    self->task->f0C();
}

extern "C" void fn_801FCBCC(CardFlowScene *self) {
    CardInput *input = InputMgr_GetPlayer(GetInputManager(), 0);
    switch (self->subState) {
    case 4:
        if (fn_80203E30() == -1) {
            card_save_trigger(1);
            fn_80203F5C(8);
            self->subState = 5;
            lbl_806D19C0 = 1;
            lbl_806D19C4 = 0;
        }
        break;
    case 5:
        if (CardSave_Tick()) {
            switch (fn_801FDA78(Sci2Card_GetPrintErrorCode())) {
            case 0:
                self->subState = 6;
                fn_8020A7CC(self->fader, 0, lbl_806D19C8[0], (short)lbl_806D19C8[0]);
                break;
            case 6: case 7:
                fn_80203E4C();
                fn_802078B4();
                self->state = -1;
                break;
            }
        } else {
            if (lbl_806D19C4 == 0) {
                if (CardRW_GetSubState() == 1) {
                    fn_80203F5C(1);
                    lbl_806D19C4 = 1;
                }
            } else if (lbl_806D19C4 == 1) {
                if (CardRW_GetSubState() == 2) {
                    fn_80203E4C();
                    lbl_806D19C4 = 2;
                }
            }
        }
        break;
    case 6:
        CardFadeTick(self->fader);
        if (input->Pressed(lbl_806DA860) || self->fader->time >= self->fader->duration) {
            fn_80203EA0();
            self->subState = 7;
        }
        break;
    case 7:
        if (fn_80203E30() == -1) {
            self->state = 10;
            self->subState = 8;
        }
        break;
    }
}

extern "C" void fn_801FCD9C(CardFlowScene *self) {
    CardInput *input = InputMgr_GetPlayer(GetInputManager(), 0);
    switch (self->subState) {
    case 0:
        if (fn_80203E30() == -1) {
            self->subState = 1;
            fn_8020A7CC(self->fader, 0, lbl_806D19C8[0], (short)lbl_806D19C8[0]);
            if (lbl_806D19C0 == 1) fn_80203F5C(20);
            else fn_80203F5C(1);
            card_eject_init();
            fn_801D7610(g_playerData, 1);
        }
        break;
    case 1:
        if (card_eject_state_machine()) {
            switch (fn_801FDCA8(Sci2Card_GetPrintErrorCode())) {
            case 0:
                fn_8020A7CC(self->fader, 0, lbl_806D19C8[0], (short)lbl_806D19C8[0]);
                self->subState = 2;
                break;
            case 6: case 7:
                fn_80203E4C();
                fn_802078B4();
                self->state = -1;
                break;
            }
        }
        break;
    case 2:
        CardFadeTick(self->fader);
        if (input->Pressed(lbl_806DA860) || self->fader->time >= self->fader->duration) {
            fn_80203EA0();
            self->subState = 3;
        }
        break;
    case 3:
        if (fn_80203E30() == -1) self->subState = 7;
        break;
    case 7:
        self->state = 10;
        self->subState = 8;
        break;
    }
}

extern "C" void fn_801FCF58(CardFlowScene *self) {
    CardInput *input = InputMgr_GetPlayer(GetInputManager(), 0);
    unsigned char promptActive = fn_80207C64();
    int previous = self->cursor;
    self->cursor += fn_801FE858(input);
    int selected = self->cursor;
    if (selected < 0) self->cursor = 0;
    if (selected > 1) self->cursor = 1;
    fn_80207CC4(self->cursor);
    int coins = CreditMgr_GetCoinCount(0, -1);
    if (self->coins != coins) self->timer = 1201;
    self->coins = coins;
    unsigned char unavailable = CardCreditUnavailable(self);
    if (unavailable && self->field41 != unavailable && !self->field40 && self->cursor > 0) {
        fn_8020A7CC(self->fader, 0, 15, 15);
        self->field40 = 1;
        self->state = 6;
        self->kind = 5;
    }
    if (input->Pressed(lbl_806DA860)) {
        if (self->cursor == 0) {
            fn_801FE348();
            if (CreditMgr_TryConfirmPlay(self->slot)) {
                self->state = 9;
                self->subState = 4;
            } else {
                if (self->field38) {
                    self->field38 = 0;
                    self->timer = 1201;
                }
                if (!promptActive) fn_80207B28(1);
            }
        } else {
            fn_801FE348();
            PlayerData_ResetForFlow();
            fn_801FE3BC();
            fn_801FE404();
            lbl_806D19C0 = 0;
            self->state = 8;
            self->subState = 0;
        }
    }
    if (self->timer > 0) --self->timer;
    fn_801FE27C(self->timer);
    if (previous != self->cursor) fn_801FE390();
    if (self->timer <= 0) {
        PlayerData_ResetForFlow();
        fn_801FE3BC();
        fn_801FE404();
        if (self->cursor == 0) {
            fn_8020A7CC(self->fader, 0, 15, 15);
            self->state = 7;
            self->kind = 8;
            self->subState = 0;
        } else {
            fn_801FE348();
            self->state = 8;
            self->subState = 0;
        }
        lbl_806D19C0 = 0;
    }
    self->field41 = unavailable;
}

CardFlowScene::~CardFlowScene() {
    CreditMgr_SetActiveSlot(0);
}

CardFlowScene::CardFlowScene(int arg, int base) : FlowScene(base) {
    kind = 5;
    arg2C = arg;
    field30 = 0;
    coins = CreditMgr_GetCoinCount(0, -1);
    field38 = 1;
    slot = 3;
    field40 = 0;
    field41 = 0;
    field44 = 0;
    state = 0;
    subState = 0;
    timer = 0x4B1;
    CreditMgr_SetActiveSlot(slot);
}

extern "C" void fn_801FD2E8(VObject *obj) {
    delete obj;
}
