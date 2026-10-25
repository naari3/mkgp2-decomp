/*
 * CabinetSetting_Page @ 0x8006AA84..0x8006AD0C: the cabinet setting test
 * page. Two on/off switches in the settings block (data + 0x50/0x51) and
 * an exit entry that publishes the backup shadow copy.
 */
#include "game/TestMenuPage.h"

struct CabinetSettings {
    unsigned char pad_0[0x50];
    unsigned char flagA; /* 0x50 */
    unsigned char flagB; /* 0x51 */
};

extern "C" {
extern MenuItem lbl_803FCDEC[];
extern const char lbl_806D2D94[4]; /* off label */
extern const char lbl_806D2DA4[6]; /* header */
extern const char lbl_806D2DAC[3]; /* on label */
void Backup_PublishShadowCopy_Inline(void);
}

#pragma exceptions on

extern "C" int CabinetSetting_Page(TestPage *self, int phase)
{
    InputPlayer *pl;
    CabinetSettings *cs;

    if (phase == 0) {
        self->cursor = 2;
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
                cs = (CabinetSettings *)self->data;
                if (cs->flagA != 0) {
                    cs->flagA = 0;
                } else {
                    cs->flagA = 1;
                }
            }
            if (self->cursor == 1) {
                cs = (CabinetSettings *)self->data;
                if (cs->flagB != 0) {
                    cs->flagB = 0;
                } else {
                    cs->flagB = 1;
                }
            }
            if (self->cursor == 2) {
                Backup_PublishShadowCopy_Inline();
                self->next = 0;
            }
        }
    }
    if (phase == 2) {
        TestPage_DrawItems(self, lbl_803FCDEC, self->cursor + 2);
        if (self->text != 0) {
            DrawText(self->text, 0x16C, 0x30, 2, 1.0f, lbl_806D2DA4);
            if (((CabinetSettings *)self->data)->flagA != 0) {
                DrawText(self->text, 0x1DC, 0x60, 4, 1.0f, lbl_806D2DAC);
            } else {
                DrawText(self->text, 0x1DC, 0x60, 2, 1.0f, lbl_806D2D94);
            }
            if (((CabinetSettings *)self->data)->flagB != 0) {
                DrawText(self->text, 0x1DC, 0x78, 4, 1.0f, lbl_806D2DAC);
            } else {
                DrawText(self->text, 0x1DC, 0x78, 2, 1.0f, lbl_806D2D94);
            }
        }
    }
    return 1;
}

#pragma exceptions reset
