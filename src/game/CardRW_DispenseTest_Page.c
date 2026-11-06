/* Card reader dispense test: enter, update, and draw phases. */
#pragma cplusplus on
#pragma use_lmw_stmw on
#include "game/CardRWDispensePagePrivate.h"

extern "C" int CardRW_DispenseTest_Page(DispensePage *self, int phase, int arg)
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
                    self->tick = lbl_803FDBE8[self->step].tick;
                    self->error = 1;
                    self->error = Dispense_CheckError();
                    if (self->error != 1) {
                        self->failed = 1;
                        self->blink = 31;
                        self->step = 0;
                    }
                } else {
                    self->next = 5;
                    CardRW_TestTopMenu_Page(self, 0, 2);
                }
            }
        } else {
            if (self->tick() == 1) {
                if (lbl_803FDBE8[self->step].checkError)
                    self->error = Sci2Card_GetPrintErrorCode();
                if (self->error != 1) self->step = 0;
                else {
                    ++self->step;
                    self->tick = lbl_803FDBE8[self->step].tick;
                    if (self->tick == 0) {
                        self->next = 5;
                        CardRW_TestTopMenu_Page(self, 0, 2);
                    }
                }
            }
        }
    }
    if (phase == 2) {
        Dispense_DrawItems(self, lbl_803FCAE0, self->selection + 3);
        if (self->text != 0) {
            unsigned char c, b, a;
            Sci2Card_GetResponseStatus(Sci2Card_Singleton_Get(), &a, &b, &c);
            DrawText(self->text, 168, 72, 7, 1.0f, strings + 0x1c78, a, b, c);
        }
        if (!CardRW_ErrorDisplay(self, 1, 1, 0) && self->text != 0) {
            switch (self->step) {
            case 1: case 2:
                DrawText(self->text, 84, 192, 7, 1.0f, strings + 0x2360);
                if (self->blink <= 30)
                    DrawText(self->text, 84, 240, 7, 1.0f, strings + 0x2334);
                break;
            case 3: case 4:
                DrawText(self->text, 84, 192, 7, 1.0f, strings + 0x2380);
                if (self->blink <= 30)
                    DrawText(self->text, 84, 240, 7, 1.0f, strings + 0x1c58);
                break;
            }
        }
    }
    return 1;
}
#pragma use_lmw_stmw reset
