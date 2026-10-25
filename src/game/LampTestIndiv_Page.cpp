/*
 * LampTestIndiv_Page @ 0x800712D8..0x800715AC: the individual lamp test
 * page. Toggles two lamp outputs of the steering PCB (status bits 4 and 8).
 */
#include "game/TestMenuPage.h"


extern "C" {
extern MenuItem lbl_803FC708[];
extern const char lbl_806D2D94[4]; /* off label */
extern const char lbl_806D2DAC[3]; /* on label */
void *StrPcb_GetInstance(void);
void StrPcb_SetStatusBits(void *pcb, int bits, int on);
void StrPcb_ClearStatusBits(void *pcb, int bits);
void MonitorTest_Page(TestPage *self, int phase, int arg);
}

#define LAMP_A(self) (((unsigned char *)(self))[0x51])
#define LAMP_B(self) (((unsigned char *)(self))[0x52])

#pragma exceptions on

extern "C" int LampTestIndiv_Page(TestPage *self, int phase)
{
    InputPlayer *pl;

    if (phase == 0) {
        self->cursor = 2;
        LAMP_A(self) = 0;
        LAMP_B(self) = 0;
        StrPcb_ClearStatusBits(StrPcb_GetInstance(), 4);
        StrPcb_ClearStatusBits(StrPcb_GetInstance(), 8);
    }
    if (phase == 1) {
        pl = InputMgr_GetPlayer(GetInputManager(), 0);
        if (pl->Pressed(0x800)) {
            self->blink = 0x1F;
            if (++self->cursor > 2) {
                self->cursor = 0;
            }
        }
        if (pl->Pressed(0x1000)) {
            if (self->cursor == 0) {
                if (LAMP_A(self) == 0) {
                    LAMP_A(self) = 1;
                    StrPcb_SetStatusBits(StrPcb_GetInstance(), 4, 1);
                } else {
                    LAMP_A(self) = 0;
                    StrPcb_ClearStatusBits(StrPcb_GetInstance(), 4);
                }
            }
            if (self->cursor == 1) {
                if (LAMP_B(self) == 0) {
                    LAMP_B(self) = 1;
                    StrPcb_SetStatusBits(StrPcb_GetInstance(), 8, 1);
                } else {
                    LAMP_B(self) = 0;
                    StrPcb_ClearStatusBits(StrPcb_GetInstance(), 8);
                }
            }
            if (self->cursor == 2) {
                StrPcb_ClearStatusBits(StrPcb_GetInstance(), 4);
                StrPcb_ClearStatusBits(StrPcb_GetInstance(), 8);
                self->next = 2;
                MonitorTest_Page(self, 0, 2);
            }
        }
    }
    if (phase == 2) {
        TestPage_DrawItems(self, lbl_803FC708, self->cursor + 2);
        if (self->text != 0) {
            if (LAMP_A(self) == 1) {
                DrawText(self->text, 0x15E, 0x78, 4, 1.0f, lbl_806D2DAC);
            } else {
                DrawText(self->text, 0x15E, 0x78, 7, 1.0f, lbl_806D2D94);
            }
            if (LAMP_B(self) == 1) {
                DrawText(self->text, 0x15E, 0x90, 4, 1.0f, lbl_806D2DAC);
            } else {
                DrawText(self->text, 0x15E, 0x90, 7, 1.0f, lbl_806D2D94);
            }
        }
    }
    return 1;
}

#pragma exceptions reset
