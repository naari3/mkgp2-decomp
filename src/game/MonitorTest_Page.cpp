/*
 * MonitorTest_Page @ 0x80071E1C..0x80072074: the monitor test top page.
 * Entry 3 is skipped and replaced by a countdown while lbl_806D1114 (the
 * boot settle timer, decremented by FrameUpdate) is running.
 */
#include "game/TestMenuPage.h"

extern "C" {
extern MenuItem lbl_803FC588[];
extern const char lbl_80310C74[];
extern const char lbl_80310C90[];
extern int lbl_806D1114;
int UI_PageDispatcher(TestPage *self, int phase);
}

static inline unsigned char MonitorTest_IsSettled(void)
{
    if (lbl_806D1114 == 0) {
        return 1;
    }
    return 0;
}

#pragma exceptions on

extern "C" int MonitorTest_Page(TestPage *self, int phase, int arg)
{
    InputPlayer *pl;

    if (phase == 0) {
        if (arg == -1) {
            self->cursor = 4;
        } else {
            self->cursor = arg;
        }
    }
    if (phase == 1) {
        pl = InputMgr_GetPlayer(GetInputManager(), 0);
        if (pl->Pressed(0x800)) {
            self->blink = 0x1F;
            self->cursor++;
            if (lbl_806D1114 != 0 && self->cursor == 3) {
                self->cursor++;
            }
            if (self->cursor > 4) {
                self->cursor = 0;
            }
        }
        if (pl->Pressed(0x1000)) {
            if (self->cursor == 4) {
                self->next = 0;
            } else {
                self->next = self->cursor + 11;
                UI_PageDispatcher(self, 0);
            }
        }
    }
    if (phase == 2) {
        TestPage_DrawItems(self, lbl_803FC588, self->cursor + 1);
        if (!MonitorTest_IsSettled()) {
            DrawText(self->text, 0x2A, 0xA8, 3, 1.0f, lbl_80310C74, lbl_806D1114 / 60);
        } else if (self->cursor != 3) {
            DrawText(self->text, 0x2A, 0xA8, 7, 1.0f, lbl_80310C90);
        } else if (self->blink <= 0x1E) {
            DrawText(self->text, 0x2A, 0xA8, 7, 1.0f, lbl_80310C90);
        }
    }
    return 1;
}

#pragma exceptions reset
