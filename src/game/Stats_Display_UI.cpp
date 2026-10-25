/*
 * Stats_Display_UI @ 0x80069720..0x80069AB0: the network statistics test
 * page (between NetDiag_PacketPage and NetDiag_PacketRatioPage). Phase 0
 * resets the cursor, phase 1 handles input, phase 2 draws the item table,
 * the packet error ratio and the counters.
 */
#include "game/TestMenuPage.h"

struct NetStats {
    unsigned char pad_0[0x2A0];
    unsigned int received;  /* 0x2A0 */
    unsigned int dropped;   /* 0x2A4 */
    unsigned int corrupted; /* 0x2A8 */
    unsigned char pad_2AC[0x18];
    unsigned int errors;    /* 0x2C4 */
    int counters[6];        /* 0x2C8 */
};

extern "C" {
extern MenuItem lbl_803FD0C8[];
extern MenuItem lbl_803FD17C[];
extern const char lbl_80310478[];
extern const char lbl_806D2D80[5]; /* "%08d" */
extern const char lbl_806D2D88[5]; /* "%04d" */
void NetDiag_PacketPage(TestPage *self, int phase, int arg);
}

#pragma exceptions on

extern "C" int Stats_Display_UI(TestPage *self, int phase)
{
    InputPlayer *pl;
    NetStats *st;
    unsigned int total;
    float ratio;
    int row;

    if (phase == 0) {
        self->cursor = 0;
    }
    if (phase == 1) {
        pl = InputMgr_GetPlayer(GetInputManager(), 0);
        if (pl->Pressed(0x800)) {
            self->blink = 0x1F;
            if (++self->cursor > 1) {
                self->cursor = 0;
            }
        }
        if (pl->Pressed(0x1000)) {
            if (self->cursor == 0) {
                self->next = 0x1C;
                NetDiag_PacketPage(self, 0, -1);
            } else {
                self->next = 0;
            }
        }
    }
    if (phase == 2) {
        st = (NetStats *)self->data;
        total = st->received + st->dropped + st->corrupted;
        ratio = (float)st->errors / (float)total;
        if (total == 0) {
            ratio = 0.0f;
        }
        if (self->variant != 2) {
            TestPage_DrawItems(self, lbl_803FD0C8, self->cursor + 10);
            DrawText(self->text, 0x1A4, 0x60, 7, 1.0f, lbl_80310478, 100.0f * ratio);
            row = 6;
        } else {
            TestPage_DrawItems(self, lbl_803FD17C, self->cursor + 9);
            row = 5;
        }
        DrawText(self->text, 0x1A4, 0x48, 7, 1.0f, lbl_806D2D80, total);
        DrawText(self->text, 0x1C0, row * 24, 7, 1.0f, lbl_806D2D88, ((NetStats *)self->data)->counters[0]);
        DrawText(self->text, 0x1C0, (row + 1) * 24, 7, 1.0f, lbl_806D2D88, ((NetStats *)self->data)->counters[1]);
        DrawText(self->text, 0x1C0, (row + 2) * 24, 7, 1.0f, lbl_806D2D88, ((NetStats *)self->data)->counters[2]);
        DrawText(self->text, 0x1C0, (row + 4) * 24, 7, 1.0f, lbl_806D2D88, ((NetStats *)self->data)->counters[3]);
        DrawText(self->text, 0x1C0, (row + 5) * 24, 7, 1.0f, lbl_806D2D88, ((NetStats *)self->data)->counters[4]);
        DrawText(self->text, 0x1C0, (row + 6) * 24, 7, 1.0f, lbl_806D2D88, ((NetStats *)self->data)->counters[5]);
    }
    return 1;
}

#pragma exceptions reset
