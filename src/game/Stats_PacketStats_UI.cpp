#include "game/TestMenuPage.h"
extern "C" {
extern char lbl_803FBF80[];
extern const char lbl_80310478[], lbl_8031049C[], lbl_806D2D80[5];
extern const float lbl_806D2D44, lbl_806D2D70, lbl_806D2D74;
int NetDiag_CounterPage(TestPage *, int, int);
}
#pragma exceptions on
extern "C" int Stats_PacketStats_UI(TestPage *self, int phase, int unused)
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
                self->next = 30;
                NetDiag_CounterPage(self, 0, -1);
            } else self->next = 0;
        }
    }
    if (phase == 2) {
        unsigned int *stats = (unsigned int *)self->data;
        float total = (float)(stats[0x2B8/4] + stats[0x2BC/4]);
        float ratio0 = (float)stats[0x374/4] / total;
        float ratio1 = (float)stats[0x378/4] / total;
        float ratio2 = (float)stats[0x380/4] / total;
        float ratio3 = (float)stats[0x388/4] / total;
        float ratio4 = (float)stats[0x390/4] / total;
        float ratio5 = (float)stats[0x398/4] / total;
        float ratio6 = (float)stats[0x3A0/4] / total;
        float ratio7 = (float)stats[0x3A8/4] / total;
        float ratio8 = (float)stats[0x3B0/4] / total;
        float ratio9 = (float)stats[0x3B8/4] / total;
        float ratio10 = (float)stats[0x3C0/4] / total;
        float ratio11 = (float)stats[0x3C8/4] / total;
        float ratio12 = (float)stats[0x3D0/4] / total;
        float ratio13 = (float)stats[0x3D8/4] / total;
        float ratio14 = (float)stats[0x3E0/4] / total;
        float ratio15 = (float)stats[0x3E8/4] / total;
        float ratio16 = (float)stats[0x3F0/4] / total;
        float ratio17 = (float)stats[0x3F8/4] / total;
        float ratio18 = (float)stats[0x400/4] / total;
        float ratio19 = (float)stats[0x408/4] / total;
        float ratio20 = (float)stats[0x410/4] / total;
        float ratio21 = (float)stats[0x418/4] / total;
        float ratio22 = (float)stats[0x420/4] / total;
        float ratio23 = (float)stats[0x428/4] / total;
        float ratio24 = (float)stats[0x430/4] / total;
        float ratio25 = (float)stats[0x438/4] / total;
        float ratio26 = (float)stats[0x440/4] / total;
        float ratio27 = (float)stats[0x448/4] / total;
        float ratio28 = (float)stats[0x450/4] / total;
        float ratio29 = (float)stats[0x458/4] / total;
        float ratio30 = (float)stats[0x460/4] / total;
        float ratio31 = (float)stats[0x468/4] / total;
        float ratio32 = (float)stats[0x470/4] / total;
        if (lbl_806D2D70 == total) {
            ratio0 = lbl_806D2D70;
            ratio1 = ratio2 = ratio3 = ratio4 = ratio5 = ratio6 = ratio7 = ratio8 = lbl_806D2D70;
            ratio9 = ratio10 = ratio11 = ratio12 = ratio13 = ratio14 = ratio15 = ratio16 = lbl_806D2D70;
            ratio17 = ratio18 = ratio19 = ratio20 = ratio21 = ratio22 = ratio23 = ratio24 = lbl_806D2D70;
            ratio25 = ratio26 = ratio27 = ratio28 = ratio29 = ratio30 = ratio31 = ratio32 = lbl_806D2D70;
        }
        int row;
        if (self->variant != 2) {
            if (self->variant == 0)
                TestPage_DrawItems(self, (MenuItem *)(tables + 0x1520), self->cursor + 13);
            else
                TestPage_DrawItems(self, (MenuItem *)(tables + 0x15F8), self->cursor + 13);
            DrawText(self->text, 420, 96, 7, lbl_806D2D44, lbl_80310478, lbl_806D2D74 * ratio0);
            row = 7;
        } else {
            TestPage_DrawItems(self, (MenuItem *)(tables + 0x16D0), self->cursor + 12);
            row = 6;
        }
        DrawText(self->text, 420, 72, 7, lbl_806D2D44, lbl_806D2D80, (int)total);
        DrawText(self->text, 126, (row)*24, 7, lbl_806D2D44, lbl_8031049C, lbl_806D2D74 * ratio25, lbl_806D2D74 * ratio26, lbl_806D2D74 * ratio27, lbl_806D2D74 * ratio28);
        DrawText(self->text, 126, (row + 1)*24, 7, lbl_806D2D44, lbl_8031049C, lbl_806D2D74 * ratio1, lbl_806D2D74 * ratio2, lbl_806D2D74 * ratio3, lbl_806D2D74 * ratio4);
        DrawText(self->text, 126, (row + 2)*24, 7, lbl_806D2D44, lbl_8031049C, lbl_806D2D74 * ratio29, lbl_806D2D74 * ratio30, lbl_806D2D74 * ratio31, lbl_806D2D74 * ratio32);
        DrawText(self->text, 126, (row + 3)*24, 7, lbl_806D2D44, lbl_8031049C, lbl_806D2D74 * ratio5, lbl_806D2D74 * ratio6, lbl_806D2D74 * ratio7, lbl_806D2D74 * ratio8);
        DrawText(self->text, 126, (row + 4)*24, 7, lbl_806D2D44, lbl_8031049C, lbl_806D2D74 * ratio9, lbl_806D2D74 * ratio10, lbl_806D2D74 * ratio11, lbl_806D2D74 * ratio12);
        DrawText(self->text, 126, (row + 5)*24, 7, lbl_806D2D44, lbl_8031049C, lbl_806D2D74 * ratio13, lbl_806D2D74 * ratio14, lbl_806D2D74 * ratio15, lbl_806D2D74 * ratio16);
        DrawText(self->text, 126, (row + 6)*24, 7, lbl_806D2D44, lbl_8031049C, lbl_806D2D74 * ratio17, lbl_806D2D74 * ratio18, lbl_806D2D74 * ratio19, lbl_806D2D74 * ratio20);
        DrawText(self->text, 126, (row + 7)*24, 7, lbl_806D2D44, lbl_8031049C, lbl_806D2D74 * ratio21, lbl_806D2D74 * ratio22, lbl_806D2D74 * ratio23, lbl_806D2D74 * ratio24);
    }
    return 1;
}
#pragma exceptions reset
