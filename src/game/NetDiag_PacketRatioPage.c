/*
 * NetDiag_PacketRatioPage, 0x80069AB0..0x8006A160: network diagnostics
 * service-menu page that shows each packet class as a share of all sent
 * packets (stats +0x27C). mode 0 = enter, 1 = input, 2 = draw.
 *
 * Sibling of NetDiag_PacketPage / NetDiag_QualityPage: compiled as C++
 * (#pragma cplusplus on) for the virtual button poll, same item-list inline.
 */
#pragma cplusplus on
#pragma exceptions on

#include "game/TestMenuPage.h"

extern "C" {
extern MenuItem lbl_803FCF24[], lbl_803FD014[];
extern const char lbl_80310478[], lbl_806D2D80[5];
extern const float lbl_806D2D44, lbl_806D2D70, lbl_806D2D74;
int Stats_Display_UI(TestPage *self, int phase, int arg);

int NetDiag_PacketRatioPage(TestPage *self, int phase, int arg)
{
    if (phase == 0) self->cursor = 0;
    if (phase == 1) {
        InputPlayer *input = InputMgr_GetPlayer(GetInputManager(), 0);
        if (input->Pressed(0x800)) {
            self->blink = 31;
            if (++self->cursor > 1) self->cursor = 0;
        }
        if (input->Pressed(0x1000)) {
            if (self->cursor == 0) {
                self->next = 27;
                Stats_Display_UI(self, 0, -1);
            } else self->next = 0;
        }
    }
    if (phase == 2) {
        unsigned int *stats = (unsigned int *)self->data;
        unsigned int total = stats[0x27C/4];
        float r0 = (float)stats[0x28C/4] / (float)total;
        float r1 = (float)stats[0x294/4] / (float)total;
        float r2 = (float)stats[0x2A0/4] / (float)total;
        float r3 = (float)stats[0x2A4/4] / (float)total;
        float r4 = (float)stats[0x2A8/4] / (float)total;
        float r5 = (float)stats[0x2AC/4] / (float)total;
        float r6 = (float)stats[0x2B0/4] / (float)total;
        float r7 = (float)stats[0x2B4/4] / (float)total;
        float r8 = (float)stats[0x2B8/4] / (float)total;
        float r9 = (float)stats[0x2BC/4] / (float)total;
        int row;
        if (total == 0) {
            r0 = r1 = r8 = r9 = r5 = r6 = r7 = r2 = r3 = r4 = lbl_806D2D70;
        }
        if (self->variant != 2) {
            TestPage_DrawItems(self, lbl_803FCF24, self->cursor + 15);
            DrawText(self->text, 420, 48, 7, lbl_806D2D44, lbl_806D2D80, ((unsigned int *)self->data)[0x28C/4]);
            DrawText(self->text, 420, 72, 7, lbl_806D2D44, lbl_80310478, lbl_806D2D74 * r0);
            DrawText(self->text, 420, 96, 7, lbl_806D2D44, lbl_806D2D80, ((unsigned int *)self->data)[0x294/4]);
            DrawText(self->text, 420, 120, 7, lbl_806D2D44, lbl_80310478, lbl_806D2D74 * r1);
            DrawText(self->text, 420, 144, 7, lbl_806D2D44, lbl_806D2D80, ((unsigned int *)self->data)[0x29C/4]);
            row = 8;
        } else {
            TestPage_DrawItems(self, lbl_803FD014, self->cursor + 10);
            row = 3;
        }
        DrawText(self->text, 420, row * 24, 7, lbl_806D2D44, lbl_80310478, lbl_806D2D74 * r2);
        DrawText(self->text, 420, (row + 1) * 24, 7, lbl_806D2D44, lbl_80310478, lbl_806D2D74 * r3);
        DrawText(self->text, 420, (row + 2) * 24, 7, lbl_806D2D44, lbl_80310478, lbl_806D2D74 * r4);
        DrawText(self->text, 420, (row + 3) * 24, 7, lbl_806D2D44, lbl_80310478, lbl_806D2D74 * r5);
        DrawText(self->text, 420, (row + 4) * 24, 7, lbl_806D2D44, lbl_80310478, lbl_806D2D74 * r6);
        DrawText(self->text, 420, (row + 5) * 24, 7, lbl_806D2D44, lbl_80310478, lbl_806D2D74 * r7);
        DrawText(self->text, 420, (row + 6) * 24, 7, lbl_806D2D44, lbl_80310478, lbl_806D2D74 * r8);
        DrawText(self->text, 420, (row + 7) * 24, 7, lbl_806D2D44, lbl_80310478, lbl_806D2D74 * r9);
    }
    return 1;
}

}

#pragma exceptions reset
