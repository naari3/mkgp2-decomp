/* Card reader/writer test menu: enter, update and draw phases. */
#pragma cplusplus on
#include "game/CardRW_TestTopMenu_Private.h"

extern "C" {
extern int lbl_806D1108;
extern const float lbl_806D2D44;
extern const char lbl_80310118[], lbl_80310A0C[];
extern MenuItem lbl_803FC8B8[];
extern CardRWStep lbl_803FDB18[];
void CardPrintJob_KickFontTransfer(void);
unsigned char CardPrintJob_TickFontTransfer(void);
int Sci2Card_GetPrintErrorCode(void);
unsigned char Sci2Card_BeginSpace(void);
unsigned char Sci2Card_WaitPingStatus(void);
unsigned char Sci2Card_GetByteFlag1224(void);
void CardRW_ErrorDisplay(CardRWTestPage *, int, int, int);
void UI_PageDispatcher(CardRWTestPage *, int, int);

int CardRW_TestTopMenu_Page(CardRWTestPage *self, int phase, int arg)
{
    if (phase == 0) {
        self->step = 0;
        self->error = 1;
        if (arg == -1) self->cursor = 9;
        else self->cursor = arg;
        if (lbl_806D1108 == 0) CardPrintJob_KickFontTransfer();
    }
    if (phase == 1) {
        InputPlayer *input = InputMgr_GetPlayer(GetInputManager(), 0);
        if (self->error != 1) {
            if (input->Pressed(0x1000)) self->next = 0;
            return 1;
        }
        if (lbl_806D1108 == 0) {
            if (!CardPrintJob_TickFontTransfer()) return 1;
            self->error = Sci2Card_GetPrintErrorCode();
            if (self->error != 1) self->state = -2;
            else if (self->state == -2) {
                if (!Sci2Card_BeginSpace()) self->state = -1;
                else self->state = 0;
            }
            if (self->error != 101) {
                lbl_806D1108 = 1;
                self->error = 1;
            }
            return 1;
        }
        if (self->state == -1) {
            if (Sci2Card_BeginSpace() == 1) self->state = 0;
            return 1;
        }
        if (self->state == 0) {
            if (!Sci2Card_WaitPingStatus()) return 1;
            if (Sci2Card_GetPrintErrorCode() != 1) {
                self->state = -2;
                return 1;
            }
            if (!Sci2Card_GetByteFlag1224()) self->state = -2;
            else {
                self->state = 5;
                self->step = lbl_803FDB18[self->state].run;
            }
            return 1;
        }
        if (self->state >= 1) {
            if (self->step() == 1) {
                ++self->state;
                self->step = lbl_803FDB18[self->state].run;
                if (self->step == 0) self->state = -2;
            }
            return 1;
        }
        if (input->Pressed(0x800)) {
            self->blink = 31;
            if (++self->cursor > 9) self->cursor = 0;
        }
        if (input->Pressed(0x1000)) {
            if (self->cursor == 9) self->next = 0;
            else {
                self->field_2C = 0;
                int selected = self->cursor;
                self->next = selected + 15;
                UI_PageDispatcher(self, 0, selected);
            }
        }
    }
    if (phase == 2) {
        if (self->error != 1) {
            int blink = self->blink;
            self->blink = 31;
            CardRW_ErrorDisplay(self, 1, 1, 0);
            self->blink = blink;
            if (self->blink <= 30)
                DrawText(self->text, 84, 264, 7, lbl_806D2D44, lbl_80310118);
        } else if (lbl_806D1108 == 0) {
            if (self->blink <= 30)
                DrawText(self->text, 154, 216, 7, lbl_806D2D44, lbl_80310A0C);
        } else {
            TestPage_DrawItems((TestPage *)self, lbl_803FC8B8, self->cursor + 1);
        }
    }
    return 1;
}
}
