/*
 * BackupMemoryInitialize_Page @ 0x80066E10..0x80067494: the backup memory
 * initialize test page. The cursor picks high scores / bookkeeping / all /
 * exit; a confirm step (sub-state 1..2) runs the clear and publishes the
 * shadow copy, then shows a done message for 90 frames. Strings come from
 * the shared test-menu .rodata pool at lbl_8030E598.
 */
#include "game/TestMenuPage.h"

extern "C" {
extern MenuItem lbl_803FDAE8[];
extern const char lbl_806D2D68[5];
void Backup_ClearHiScores(void);
void Backup_ClearBookkeeping(void);
void Backup_ClearAll(void);
void Backup_PublishShadowCopy_Inline(void);
}

#pragma exceptions on

extern "C" int BackupMemoryInitialize_Page(TestPage *self, int phase)
{
    char *pool = lbl_8030E598;
    InputPlayer *pl;

    if (phase == 0) {
        self->cursor = 3;
        self->sub = 0;
    }
    if (phase == 1) {
        pl = InputMgr_GetPlayer(GetInputManager(), 0);
        if (self->sub == 0) {
            if (pl->Pressed(0x800)) {
                self->blink = 0x1F;
                if (++self->cursor > 3) {
                    self->cursor = 0;
                }
            }
            if (pl->Pressed(0x1000)) {
                self->blink = 0x1F;
                if (self->cursor == 3) {
                    self->next = 0;
                } else {
                    self->sub = 1;
                }
            }
        } else if (self->sub == 1 || self->sub == 2) {
            if (pl->Pressed(0x800)) {
                self->blink = 0x1F;
                if (++self->sub > 2) {
                    self->sub = 1;
                }
            }
            if (pl->Pressed(0x1000)) {
                self->blink = 0x1F;
                if (self->sub == 1) {
                    self->sub = 0;
                } else {
                    self->sub = 3;
                    if (self->cursor == 0) {
                        Backup_ClearHiScores();
                    }
                    if (self->cursor == 1) {
                        Backup_ClearBookkeeping();
                    }
                    if (self->cursor == 2) {
                        Backup_ClearAll();
                    }
                    Backup_PublishShadowCopy_Inline();
                }
            }
        } else if (++self->sub > 0x5A) {
            self->sub = 0;
        }
    }
    if (phase == 2) {
        TestPage_DrawItems(self, lbl_803FDAE8, -1);
        if (self->text != 0) {
            if (self->cursor == 0) {
                if (self->sub == 0) {
                    if (self->blink <= 0x1E) {
                        DrawText(self->text, 0x2A, 0x48, 7, 1.0f, pool + 0x1CFC);
                    }
                } else if (self->sub == 1) {
                    if (self->blink <= 0x1E) {
                        DrawText(self->text, 0x2A, 0x48, 7, 1.0f, pool + 0x1D10);
                    } else {
                        DrawText(self->text, 0x2A, 0x48, 7, 1.0f, pool + 0x1D2C);
                    }
                } else if (self->sub == 2) {
                    if (self->blink <= 0x1E) {
                        DrawText(self->text, 0x2A, 0x48, 7, 1.0f, pool + 0x1D44);
                    } else {
                        DrawText(self->text, 0x2A, 0x48, 7, 1.0f, pool + 0x1D2C);
                    }
                } else {
                    DrawText(self->text, 0x2A, 0x48, 7, 1.0f, pool + 0x1D60);
                }
            } else {
                DrawText(self->text, 0x2A, 0x48, 7, 1.0f, pool + 0x1CFC);
            }
            if (self->cursor == 1) {
                if (self->sub == 0) {
                    if (self->blink <= 0x1E) {
                        DrawText(self->text, 0x2A, 0x78, 7, 1.0f, pool + 0x1D80);
                    }
                } else if (self->sub == 1) {
                    if (self->blink <= 0x1E) {
                        DrawText(self->text, 0x2A, 0x78, 7, 1.0f, pool + 0x1D98);
                    } else {
                        DrawText(self->text, 0x2A, 0x78, 7, 1.0f, pool + 0x1DB4);
                    }
                } else if (self->sub == 2) {
                    if (self->blink <= 0x1E) {
                        DrawText(self->text, 0x2A, 0x78, 7, 1.0f, pool + 0x1DCC);
                    } else {
                        DrawText(self->text, 0x2A, 0x78, 7, 1.0f, pool + 0x1DB4);
                    }
                } else {
                    DrawText(self->text, 0x2A, 0x78, 7, 1.0f, pool + 0x1DEC);
                }
            } else {
                DrawText(self->text, 0x2A, 0x78, 7, 1.0f, pool + 0x1D80);
            }
            if (self->cursor == 2) {
                if (self->sub == 0) {
                    if (self->blink <= 0x1E) {
                        DrawText(self->text, 0x2A, 0xA8, 7, 1.0f, pool + 0x1E10);
                    }
                } else if (self->sub == 1) {
                    if (self->blink <= 0x1E) {
                        DrawText(self->text, 0x2A, 0xA8, 7, 1.0f, pool + 0x1E2C);
                    } else {
                        DrawText(self->text, 0x2A, 0xA8, 7, 1.0f, pool + 0x1E4C);
                    }
                } else if (self->sub == 2) {
                    if (self->blink <= 0x1E) {
                        DrawText(self->text, 0x2A, 0xA8, 7, 1.0f, pool + 0x1E68);
                    } else {
                        DrawText(self->text, 0x2A, 0xA8, 7, 1.0f, pool + 0x1E4C);
                    }
                } else {
                    DrawText(self->text, 0x2A, 0xA8, 7, 1.0f, pool + 0x1E88);
                }
            } else {
                DrawText(self->text, 0x2A, 0xA8, 7, 1.0f, pool + 0x1E10);
            }
            if (self->cursor == 3) {
                if (self->blink <= 0x1E) {
                    DrawText(self->text, 0x2A, 0xF0, 7, 1.0f, lbl_806D2D68);
                }
            } else {
                DrawText(self->text, 0x2A, 0xF0, 7, 1.0f, lbl_806D2D68);
            }
        }
    }
    return 1;
}

#pragma exceptions reset
