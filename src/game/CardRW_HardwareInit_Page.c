/* Card reader hardware initialization: enter, update, and draw phases. */
#pragma cplusplus on
#pragma use_lmw_stmw on
#include "game/CardRWHardwareInitPagePrivate.h"

extern "C" int CardRW_HardwareInit_Page(HardwareInitPage *self, int phase, int arg)
{
    char *strings = lbl_8030E598;
    if (phase == 0) {
        self->selection = 1;
        self->step = 0;
        self->error = 0;
        self->field27C = 0;
    }
    if (phase == 1) {
        if (self->step == 0) {
            InputPlayer *input = InputMgr_GetPlayer(GetInputManager(), 0);
            if (input->Pressed(0x800)) {
                self->blink = 31;
                if (++self->selection > 1) self->selection = 0;
            }
            if (input->Pressed(0x1000)) {
                if (self->selection == 0) {
                    self->selection = 100;
                    self->step = 1;
                    self->blink = 0;
                } else {
                    self->next = 5;
                    CardRW_TestTopMenu_Page(self, 0, 8);
                }
            }
        } else if (self->error != 0) {
            InputPlayer *input = InputMgr_GetPlayer(GetInputManager(), 0);
            if (input->Pressed(0x1000)) {
                self->next = 5;
                CardRW_TestTopMenu_Page(self, 0, 8);
            }
        } else if (self->step == 1) {
            Sci2Card_SendCmdRetry(Sci2Card_Singleton_Get(), 1);
            ++self->step;
        } else if (self->step == 2) {
            void *card = Sci2Card_Singleton_Get();
            if (Sci2Card_IsIdleOrExhausted(card) == 1) {
                if (Sci2Card_IsStatusOkNonTerm(card)) ++self->step;
                else {
                    if (Sci2Card_IsRetryExhausted(card) == 1) self->error = 1;
                    else if (Sci2Card_IsStatus2Two(card) == 1) self->error = 2;
                    else if (Sci2Card_IsStatus2Three(card) == 1) self->error = 3;
                    else if (Sci2Card_IsStatus2Five(card) == 1) self->error = 4;
                    else if (Sci2Card_IsStatus2A(card) == 1) self->error = 5;
                    else if (Sci2Card_IsStatus3Five(card) == 1) self->error = 6;
                    self->step = 5;
                    self->selection = 1;
                }
            }
        } else if (self->step == 3) {
            if (CardPrintJob_KickFontTransfer() == 1) ++self->step;
        } else if (self->step == 4) {
            if (CardPrintJob_TickFontTransfer() == 1) ++self->step;
        } else {
            if (++self->step >= 63) {
                self->next = 5;
                CardRW_TestTopMenu_Page(self, 0, 8);
            }
        }
    }
    if (phase == 2) {
        HardwareInit_DrawItems(self, lbl_803FCD2C, self->selection + 3);
        if (self->text != 0) {
            unsigned char c, b, a;
            Sci2Card_GetResponseStatus(Sci2Card_Singleton_Get(), &a, &b, &c);
            DrawText(self->text, 168, 72, 7, 1.0f, strings + 0x1c78, a, b, c);
        }
        if (!CardRW_ErrorDisplay(self, 1, 1, 0) && self->text != 0) {
            if (self->step == 1 || self->step == 2 || self->step == 3 || self->step == 4) {
                DrawText(self->text, 84, 192, 7, 1.0f, strings + 0x20bc);
                if (self->blink <= 30)
                    DrawText(self->text, 84, 240, 7, 1.0f, strings + 0x2064);
            } else if (self->step >= 5) {
                if (self->error == 0) {
                    DrawText(self->text, 84, 192, 7, 1.0f, strings + 0x20d0);
                } else {
                    DrawText(self->text, 84, 168, 7, 1.0f, lbl_806D2DB4, self->error);
                    if (self->error == 1)
                        DrawText(self->text, 84, 192, 7, 1.0f, strings + 0x1b6c);
                    if (self->error == 2)
                        DrawText(self->text, 84, 192, 7, 1.0f, strings + 0x1b9c);
                    if (self->error == 3)
                        DrawText(self->text, 84, 192, 7, 1.0f, strings + 0x1bb8);
                    if (self->error == 4)
                        DrawText(self->text, 84, 192, 7, 1.0f, strings + 0x1bd0);
                    if (self->error == 5)
                        DrawText(self->text, 84, 192, 7, 1.0f, strings + 0x1be8);
                    if (self->error == 6)
                        DrawText(self->text, 84, 192, 7, 1.0f, strings + 0x1c00);
                    if (self->blink <= 30)
                        DrawText(self->text, 84, 240, 7, 1.0f, strings + 0x1b80);
                }
            }
        }
    }
    return 1;
}
#pragma use_lmw_stmw reset
