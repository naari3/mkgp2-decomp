/* Card reader reprint test: enter, update, and draw phases. */
#pragma cplusplus on
#pragma use_lmw_stmw on
#include "game/CardRWReprintPagePrivate.h"

extern "C" int CardRW_Reprint_Page(ReprintPage *self, int phase, int arg)
{
    char *strings = lbl_8030E598;
    if (phase == 0) {
        self->selection = 1;
        self->step = 0;
        self->tick = 0;
        self->error = 1;
        self->failed = 0;
    }
    if (phase == 1) {
        InputPlayer *input = InputMgr_GetPlayer(GetInputManager(), 0);
        if (self->step == 0) {
            if (self->error == 1 && input->Pressed(0x800)) {
                self->blink = 31;
                if (++self->selection > 1) self->selection = 0;
            }
            if (input->Pressed(0x1000)) {
                if (self->selection == 0) {
                    self->selection = 100;
                    self->step = 1;
                    self->blink = 0;
                    self->tick = lbl_803FDD88[self->step].tick;
                    self->error = 1;
                    self->failed = 0;
                    self->error = Reprint_CheckError();
                    if (self->error != 1) {
                        self->failed = 1;
                        self->blink = 31;
                        self->step = 0;
                    }
                } else {
                    self->next = 5;
                    CardRW_TestTopMenu_Page(self, 0, 7);
                }
            }
        } else {
            if (self->tick != 0) {
                if (self->tick() == 1) {
                    if (!self->failed && lbl_803FDD88[self->step].checkError) {
                        self->error = Sci2Card_GetPrintErrorCode();
                        if (CardRW_ErrorDisplay(self, 0, 1, 1)) {
                            self->step = 6;
                            self->failed = 1;
                        }
                    }
                    if (self->step == 2 && !Sci2Card_GetByteFlag1224()) {
                        self->step = 0;
                        self->failed = 0;
                    }
                    ++self->step;
                    self->tick = lbl_803FDD88[self->step].tick;
                }
                if (self->failed && Reprint_HasFatalError(self)) self->blink = 31;
            } else {
                unsigned char leave = 1;
                if (CardRW_ErrorDisplay(self, 0, 1, 0) && !input->Pressed(0x1000)) leave = 0;
                if (!Reprint_HasFatalError(self) || leave) {
                    self->next = 5;
                    CardRW_TestTopMenu_Page(self, 0, 7);
                }
            }
        }
    }
    if (phase == 2) {
        Reprint_DrawItems(self, lbl_803FCCCC, self->selection + 3);
        if (self->text != 0) {
            unsigned char c, b, a;
            Sci2Card_GetResponseStatus(Sci2Card_Singleton_Get(), &a, &b, &c);
            DrawText(self->text, 168, 72, 7, 1.0f, strings + 0x1c78, a, b, c);
        }
        if (!CardRW_ErrorDisplay(self, 1, 1, 1) && self->text != 0) {
            switch (self->step) {
            case 1: case 2:
                DrawText(self->text, 84, 192, 7, 1.0f, strings + 0x20ec);
                if (self->blink <= 30)
                    DrawText(self->text, 84, 240, 7, 1.0f, strings + 0x2038);
                break;
            case 3: case 4: case 5: case 6:
                DrawText(self->text, 84, 192, 7, 1.0f, strings + 0x2104);
                if (self->blink <= 30)
                    DrawText(self->text, 84, 240, 7, 1.0f, strings + 0x2064);
                break;
            case 7: case 8:
                DrawText(self->text, 84, 192, 7, 1.0f, strings + 0x2114);
                if (self->blink <= 30)
                    DrawText(self->text, 84, 240, 7, 1.0f, strings + 0x1c58);
                DrawText(self->text, 84, 288, 7, 1.0f, strings + 0x212c);
                break;
            }
        }
    }
    return 1;
}
#pragma use_lmw_stmw reset

