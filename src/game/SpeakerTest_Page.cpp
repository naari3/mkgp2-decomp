/*
 * SpeakerTest_Page @ 0x8006FA1C..0x80070238: the speaker test page. The
 * operator sets the two volume levels (0..15) and picks a request (no sound,
 * left+right, game sample, attract sample) that is played for a while.
 */
#include "game/TestMenuPage.h"

extern "C" {
extern MenuItem lbl_803FC81C[];
extern const char lbl_806D2DA4[6];
extern const char lbl_806D2DC4[7];
extern const char lbl_806D2DCC[3];
extern const char lbl_806D2DD0[8];
extern const char lbl_806D2DD8[8];
extern const char lbl_806D2DE0[8];
extern const char lbl_806D2DE8[6];
extern const char lbl_806D2DF0[5];
void Backup_PublishShadowCopy_Inline(void);
void fn_801934A0(unsigned char vol);
void fn_8019345C(unsigned char vol);
void fn_80193404(unsigned char vol);
void fn_801951E4(unsigned char v);
void fn_801951CC(unsigned char v);
void fn_801933D0(int on);
void fn_80192348(int id);
void fn_801909A4(int id);
void SoundMgr_Play(int id);
void ClSound_PlayBgmStream(int id, int arg);
}

#define TIMER(self) (*(int *)((char *)(self) + 0x20))
#define DATA(self) ((unsigned char *)(self)->data)

#pragma exceptions on

extern "C" int SpeakerTest_Page(TestPage *self, int phase)
{
    char *pool = lbl_8030E598;
    int streams[2] = { 5, 0 };
    InputPlayer *pl;

    if (phase == 0) {
        self->cursor = 7;
        self->sub = 0;
        TIMER(self) = -1;
    }
    if (phase == 1) {
        pl = InputMgr_GetPlayer(GetInputManager(), 0);
        if (TIMER(self) == -1) {
            if (pl->Pressed(0x800)) {
                self->blink = 0x1F;
                if (++self->cursor > 7) {
                    self->cursor = 0;
                }
                if (self->cursor == 2) {
                    self->cursor = 6;
                }
            }
            if (pl->Pressed(0x1000)) {
                if (self->cursor == 0) {
                    if (++DATA(self)[0x2C] > 15) {
                        DATA(self)[0x2C] = 0;
                    }
                }
                if (self->cursor == 1) {
                    if (++DATA(self)[0x2D] > 15) {
                        DATA(self)[0x2D] = 0;
                    }
                }
                if (self->cursor == 6) {
                    self->blink = 0x1F;
                    TIMER(self) = 0;
                }
                if (self->cursor == 7) {
                    Backup_PublishShadowCopy_Inline();
                    self->next = 0;
                }
            }
        } else if (TIMER(self) == 0) {
            if (pl->Pressed(0x800)) {
                if (++self->sub > 3) {
                    self->sub = 0;
                }
            }
            if (pl->Pressed(0x1000)) {
                if (self->sub != 0) {
                    fn_801934A0((DATA(self)[0x2C] << 7) / 15);
                    fn_8019345C((DATA(self)[0x2C] << 7) / 15);
                    fn_80193404((DATA(self)[0x2D] << 7) / 15);
                    fn_801951E4(DATA(self)[0x2E]);
                    fn_801951CC(DATA(self)[0x30]);
                    if (self->sub == 3) {
                        fn_801933D0(1);
                    } else {
                        fn_801933D0(0);
                    }
                    if (self->sub == 1) {
                        TIMER(self) = 0xB4;
                        SoundMgr_Play(0);
                    } else {
                        TIMER(self) = 0x258;
                        ClSound_PlayBgmStream(streams[self->sub - 2], 0);
                    }
                } else {
                    TIMER(self) = 0x258;
                }
            }
        } else {
            self->blink = 0;
            TIMER(self)--;
            if (TIMER(self) <= 0 || pl->Pressed(0x1000)) {
                self->blink = 0x1F;
                TIMER(self) = -1;
                if (self->sub != 0) {
                    if (self->sub == 1) {
                        fn_80192348(0);
                    } else {
                        fn_801909A4(streams[self->sub - 2]);
                    }
                }
                fn_801933D0(0);
            }
        }
    }
    if (phase == 2) {
        TestPage_DrawItems(self, lbl_803FC81C, self->cursor + 2);
        if (self->text != 0) {
            DrawText(self->text, 0x16C, 0x30, 2, 1.0f, lbl_806D2DA4);
            DrawText(self->text, 0x2A, 0x60, 7, 1.0f, lbl_806D2DC4);
            if (DATA(self)[0x2C] == 12) {
                DrawText(self->text, 0x1DC, 0x60, 2, 1.0f, lbl_806D2DCC, DATA(self)[0x2C]);
            } else {
                DrawText(self->text, 0x1DC, 0x60, 4, 1.0f, lbl_806D2DCC, DATA(self)[0x2C]);
            }
            if (DATA(self)[0x2D] == 8) {
                DrawText(self->text, 0x1DC, 0x78, 2, 1.0f, lbl_806D2DCC, DATA(self)[0x2D]);
            } else {
                DrawText(self->text, 0x1DC, 0x78, 4, 1.0f, lbl_806D2DCC, DATA(self)[0x2D]);
            }
            DrawText(self->text, 0x2A, 0x108, 7, 1.0f, lbl_806D2DD0);
            if (self->cursor != 6 || TIMER(self) != -1) {
                DrawText(self->text, 0xB6, 0x108, 7, 1.0f, lbl_806D2DD8);
            } else if (self->blink <= 0x1E) {
                DrawText(self->text, 0xB6, 0x108, 7, 1.0f, lbl_806D2DD8);
            }
            DrawText(self->text, 0x2A, 0x138, 7, 1.0f, lbl_806D2DE0);
            if (TIMER(self) != 0) {
                DrawText(self->text, 0x1DC, 0x108, 7, 1.0f, lbl_806D2DCC, self->sub);
                if (self->sub == 0) {
                    DrawText(self->text, 0xB6, 0x138, 7, 1.0f, pool + 0x248C);
                } else if (self->sub == 1) {
                    if (TIMER(self) > 0x78) {
                        DrawText(self->text, 0xB6, 0x138, 7, 1.0f, lbl_806D2DE8);
                    } else if (TIMER(self) > 0x3C) {
                        DrawText(self->text, 0xB6, 0x138, 7, 1.0f, lbl_806D2DF0);
                    } else {
                        DrawText(self->text, 0xB6, 0x138, 7, 1.0f, pool + 0x2498);
                    }
                } else if (self->sub == 2) {
                    DrawText(self->text, 0xB6, 0x138, 7, 1.0f, pool + 0x24A4);
                } else {
                    DrawText(self->text, 0xB6, 0x138, 7, 1.0f, pool + 0x24B4);
                }
            } else if (self->blink <= 0x1E) {
                DrawText(self->text, 0x1DC, 0x108, 7, 1.0f, lbl_806D2DCC, self->sub);
                if (self->sub == 0) {
                    DrawText(self->text, 0xB6, 0x138, 7, 1.0f, pool + 0x248C);
                } else if (self->sub == 1) {
                    if (TIMER(self) > 0x2D) {
                        DrawText(self->text, 0xB6, 0x138, 7, 1.0f, lbl_806D2DF0);
                    } else if (TIMER(self) > 0x19) {
                        DrawText(self->text, 0xB6, 0x138, 7, 1.0f, lbl_806D2DE8);
                    } else {
                        DrawText(self->text, 0xB6, 0x138, 7, 1.0f, pool + 0x2498);
                    }
                } else if (self->sub == 2) {
                    DrawText(self->text, 0xB6, 0x138, 7, 1.0f, pool + 0x24A4);
                } else {
                    DrawText(self->text, 0xB6, 0x138, 7, 1.0f, pool + 0x24B4);
                }
            }
        }
    }
    return 1;
}

#pragma exceptions reset
