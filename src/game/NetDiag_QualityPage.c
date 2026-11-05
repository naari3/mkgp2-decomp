/*
 * NetDiag_QualityPage, 0x80067494..0x80067F74: network diagnostics
 * service-menu page that shows per-link reception quality as percentages.
 * mode 0 = enter, 1 = input, 2 = draw.
 *
 * Compiled as C++ (#pragma cplusplus on) so the button polling is a real
 * virtual call; sibling of Stats_PacketStats_UI.cpp (same menu tables in
 * the lbl_803FBF80 service-menu data block, same item-list inline).
 * The second ratio set (variant != 2 only) fetches self->data again in
 * its own block; with a single shared pointer the first set is scheduled
 * with one more GPR than the target (8 hoisted loads instead of 7).
 */
#pragma cplusplus on

#include "game/TestMenuPage.h"

extern "C" {
extern char lbl_803FBF80[];
extern const char lbl_80310448[], lbl_80310478[];
extern const float lbl_806D2D44, lbl_806D2D70, lbl_806D2D74;
int OperationTime_Page(TestPage *self, int phase, int arg);

int NetDiag_QualityPage(TestPage *self, int phase, int arg)
{
    char *tables = lbl_803FBF80;

    if (phase == 0) self->cursor = 0;
    if (phase == 1) {
        InputPlayer *input = InputMgr_GetPlayer(GetInputManager(), 0);
        if (input->Pressed(0x800)) {
            self->blink = 31;
            if (++self->cursor > 1) self->cursor = 0;
        }
        if (input->Pressed(0x1000)) {
            if (self->cursor == 0) {
                self->next = 8;
                OperationTime_Page(self, 0, -1);
            } else self->next = 0;
        }
    }
    if (phase == 2) {
        unsigned int *stats = (unsigned int *)self->data;
        float a0 = (float)stats[0x47C/4] / (float)stats[0x288/4];
        float a1 = (float)stats[0x484/4] / (float)stats[0x288/4];
        float a2 = (float)stats[0x48C/4] / (float)stats[0x288/4];
        float a3 = (float)stats[0x494/4] / (float)stats[0x288/4];
        float a4 = (float)stats[0x49C/4] / (float)stats[0x288/4];
        float a5 = (float)stats[0x4A4/4] / (float)stats[0x288/4];
        float a6 = (float)stats[0x4AC/4] / (float)stats[0x288/4];
        float a7 = (float)stats[0x4B4/4] / (float)stats[0x288/4];
        float a8 = (float)stats[0x4BC/4] / (float)stats[0x288/4];
        float a9 = (float)stats[0x4C4/4] / (float)stats[0x288/4];
        float a10 = (float)stats[0x4CC/4] / (float)stats[0x288/4];
        float a11 = (float)stats[0x4D4/4] / (float)stats[0x288/4];
        float a12 = (float)stats[0x4DC/4] / (float)stats[0x288/4];
        if (stats[0x288/4] == 0) {
            a0 = a1 = a2 = a3 = a4 = a5 = a6 = a7 = a8 = a9 = a10 = a11 = a12 = lbl_806D2D70;
        }
        if (self->variant != 2) {
            unsigned int *s = (unsigned int *)self->data;
            float b0 = (float)s[0x478/4] / (float)s[0x290/4];
            float b1 = (float)s[0x480/4] / (float)s[0x290/4];
            float b2 = (float)s[0x488/4] / (float)s[0x290/4];
            float b3 = (float)s[0x490/4] / (float)s[0x290/4];
            float b4 = (float)s[0x498/4] / (float)s[0x290/4];
            float b5 = (float)s[0x4A0/4] / (float)s[0x290/4];
            float b6 = (float)s[0x4A8/4] / (float)s[0x290/4];
            float b7 = (float)s[0x4B0/4] / (float)s[0x290/4];
            float b8 = (float)s[0x4B8/4] / (float)s[0x290/4];
            float b9 = (float)s[0x4C0/4] / (float)s[0x290/4];
            float b10 = (float)s[0x4C8/4] / (float)s[0x290/4];
            float b11 = (float)s[0x4D0/4] / (float)s[0x290/4];
            float b12 = (float)s[0x4D8/4] / (float)s[0x290/4];
            if (s[0x290/4] == 0) {
                b0 = b1 = b2 = b3 = b4 = b5 = b6 = b7 = b8 = b9 = b10 = b11 = b12 = lbl_806D2D70;
            }
            if (self->variant == 0)
                TestPage_DrawItems(self, (MenuItem *)(tables + 0x191C), self->cursor + 12);
            else
                TestPage_DrawItems(self, (MenuItem *)(tables + 0x19DC), self->cursor + 12);
            DrawText(self->text, 98, 120, 7, lbl_806D2D44, lbl_80310448, lbl_806D2D74 * b0, lbl_806D2D74 * b1, lbl_806D2D74 * b2, lbl_806D2D74 * b3);
            DrawText(self->text, 98, 144, 7, lbl_806D2D44, lbl_80310448, lbl_806D2D74 * b4, lbl_806D2D74 * b5, lbl_806D2D74 * b6, lbl_806D2D74 * b7);
            DrawText(self->text, 98, 168, 7, lbl_806D2D44, lbl_80310448, lbl_806D2D74 * b8, lbl_806D2D74 * b9, lbl_806D2D74 * b10, lbl_806D2D74 * b11);
            DrawText(self->text, 98, 192, 7, lbl_806D2D44, lbl_80310478, lbl_806D2D74 * b12);
            DrawText(self->text, 98, 240, 7, lbl_806D2D44, lbl_80310448, lbl_806D2D74 * a0, lbl_806D2D74 * a1, lbl_806D2D74 * a2, lbl_806D2D74 * a3);
            DrawText(self->text, 98, 264, 7, lbl_806D2D44, lbl_80310448, lbl_806D2D74 * a4, lbl_806D2D74 * a5, lbl_806D2D74 * a6, lbl_806D2D74 * a7);
            DrawText(self->text, 98, 288, 7, lbl_806D2D44, lbl_80310448, lbl_806D2D74 * a8, lbl_806D2D74 * a9, lbl_806D2D74 * a10, lbl_806D2D74 * a11);
            DrawText(self->text, 98, 312, 7, lbl_806D2D44, lbl_80310478, lbl_806D2D74 * a12);
        } else {
            TestPage_DrawItems(self, (MenuItem *)(tables + 0x1A9C), self->cursor + 6);
            DrawText(self->text, 98, 96, 7, lbl_806D2D44, lbl_80310448, lbl_806D2D74 * a0, lbl_806D2D74 * a1, lbl_806D2D74 * a2, lbl_806D2D74 * a3);
            DrawText(self->text, 98, 120, 7, lbl_806D2D44, lbl_80310448, lbl_806D2D74 * a4, lbl_806D2D74 * a5, lbl_806D2D74 * a6, lbl_806D2D74 * a7);
            DrawText(self->text, 98, 144, 7, lbl_806D2D44, lbl_80310448, lbl_806D2D74 * a8, lbl_806D2D74 * a9, lbl_806D2D74 * a10, lbl_806D2D74 * a11);
            DrawText(self->text, 98, 168, 7, lbl_806D2D44, lbl_80310478, lbl_806D2D74 * a12);
        }
    }
    return 1;
}

}
