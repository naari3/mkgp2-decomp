/* Card reader read/write test: enter, update, and draw phases. */
#pragma cplusplus on
#pragma use_lmw_stmw on
#include "game/CardRWReadWritePagePrivate.h"

extern "C" int CardRW_ReadWriteTest_Page(ReadWritePage *self, int phase, int arg)
{
    char *strings = lbl_8030E598;
    if (phase == 0) {
        self->selection = 1;
        self->step = 0;
        self->tick = 0;
        self->error = 1;
        CardCheckData *backup = (CardCheckData *)((char *)self->data + 0x64);
        CardCheckData *page = &self->cardData;
        page->enabled = backup->enabled;
        page->settings = backup->settings;
        page->records = backup->records;
        page->count = backup->count;
        page->flag = backup->flag;
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
                    self->tick = lbl_803FDB98[self->step].tick;
                    self->error = 1;
                    self->error = ReadWrite_CheckError();
                    if (self->error != 1) {
                        self->failed = 1;
                        self->blink = 31;
                        self->step = 0;
                    }
                } else {
                    self->next = 5;
                    CardRW_TestTopMenu_Page(self, 0, 1);
                }
            }
        } else {
            if (self->tick() == 1) {
                if (lbl_803FDB98[self->step].checkError)
                    self->error = Sci2Card_GetPrintErrorCode();
                if (self->error != 1) self->step = 0;
                else {
                    ++self->step;
                    self->tick = lbl_803FDB98[self->step].tick;
                    if (self->tick == 0) {
                        CardCheckData *backup = (CardCheckData *)((char *)self->data + 0x64);
                        CardCheckData *page = &self->cardData;
                        backup->enabled = page->enabled;
                        backup->settings = page->settings;
                        backup->records = page->records;
                        backup->count = page->count;
                        backup->flag = page->flag;
                        Backup_PublishShadowCopy_Inline();
                        self->next = 5;
                        CardRW_TestTopMenu_Page(self, 0, 1);
                    }
                }
            }
        }
    }
    if (phase == 2) {
        ReadWrite_DrawItems(self, lbl_803FCA80, self->selection + 3);
        if (self->text != 0) {
            unsigned char c, b, a;
            Sci2Card_GetResponseStatus(Sci2Card_Singleton_Get(), &a, &b, &c);
            DrawText(self->text, 168, 72, 7, 1.0f, strings + 0x1c78, a, b, c);
        }
        if (!CardRW_ErrorDisplay(self, 1, 1, 0) && self->text != 0) {
            switch (self->step) {
            case 1: case 2:
                DrawText(self->text, 84, 192, 7, 1.0f, strings + 0x23a0);
                if (self->blink <= 30)
                    DrawText(self->text, 84, 240, 7, 1.0f, strings + 0x2334);
                break;
            case 3: case 4: case 5: case 6:
                DrawText(self->text, 84, 192, 7, 1.0f, strings + 0x23c0);
                if (self->blink <= 30)
                    DrawText(self->text, 84, 240, 7, 1.0f, strings + 0x2064);
                break;
            case 7: case 8:
                DrawText(self->text, 84, 192, 7, 1.0f, strings + 0x23e0);
                if (self->blink <= 30)
                    DrawText(self->text, 84, 240, 7, 1.0f, strings + 0x1c58);
                break;
            }
        }
    }
    return 1;
}
#pragma use_lmw_stmw reset
