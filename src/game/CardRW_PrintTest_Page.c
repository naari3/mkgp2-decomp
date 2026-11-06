/* Card reader print test: enter, update, and draw phases. */
#pragma cplusplus on
#pragma use_lmw_stmw on
#include "game/CardRWPrintPagePrivate.h"

extern "C" int CardRW_PrintTest_Page(PrintPage *self, int phase, int arg)
{
    char *strings = lbl_8030E598;
    if (phase == 0) {
        self->selection = 1;
        self->step = 0;
        self->tick = 0;
        self->error = 1;
    }
    if (phase == 1) {
        if (self->step == 0) {
            InputPlayer *input = InputMgr_GetPlayer(GetInputManager(), 0);
            if (self->error == 1 && input->Pressed(0x800)) {
                self->blink = 31;
                if (++self->selection > 1) self->selection = 0;
            }
            if (input->Pressed(0x1000)) {
                if (self->selection == 0) {
                    self->selection = 100;
                    self->step = 1;
                    self->blink = 0;
                    self->tick = lbl_803FDC18[self->step].tick;
                    self->error = 1;
                    self->error = Print_CheckError();
                    if (self->error != 1) {
                        self->failed = 1;
                        self->blink = 31;
                        self->step = 0;
                    }
                } else {
                    self->next = 5;
                    CardRW_TestTopMenu_Page(self, 0, 3);
                }
            }
        } else {
            if (self->tick() == 1) {
                if (lbl_803FDC18[self->step].checkError)
                    self->error = Sci2Card_GetPrintErrorCode();
                if (self->error != 1) self->step = 0;
                else {
                    ++self->step;
                    self->tick = lbl_803FDC18[self->step].tick;
                    if (self->tick == 0) {
                        self->next = 5;
                        CardRW_TestTopMenu_Page(self, 0, 3);
                    }
                }
            }
        }
    }
    if (phase == 2) {
        Print_DrawItems(self, lbl_803FCB40, self->selection + 3);
        if (self->text != 0) {
            unsigned char c, b, a;
            Sci2Card_GetResponseStatus(Sci2Card_Singleton_Get(), &a, &b, &c);
            DrawText(self->text, 168, 72, 7, 1.0f, strings + 0x1c78, a, b, c);
        }
        if (!CardRW_ErrorDisplay(self, 1, 1, 0) && self->text != 0) {
            switch (self->step) {
            case 1: case 2:
                DrawText(self->text, 84, 192, 7, 1.0f, strings + 0x2314);
                if (self->blink <= 30)
                    DrawText(self->text, 84, 240, 7, 1.0f, strings + 0x2334);
                break;
            case 3: case 4:
                DrawText(self->text, 84, 192, 7, 1.0f, strings + 0x2104);
                if (self->blink <= 30)
                    DrawText(self->text, 84, 240, 7, 1.0f, strings + 0x2064);
                break;
            case 5: case 6:
                DrawText(self->text, 84, 192, 7, 1.0f, strings + 0x2348);
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
