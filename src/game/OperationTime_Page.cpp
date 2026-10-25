/*
 * OperationTime_Page @ 0x8006A160..0x8006A500: the operation time test
 * page. Shows the cabinet lifetime, the total play time and the average
 * play time as h:m:s, the play ratio and the play counters.
 */
#include "game/TestMenuPage.h"

struct OperationStats {
    unsigned char pad_0[0x278];
    unsigned int playSeconds; /* 0x278 */
    unsigned int counters[3]; /* 0x27C: [0] = play count */
};

extern "C" {
extern MenuItem lbl_803FCE88[];
extern const char lbl_80310478[]; /* ratio format */
extern const char lbl_803104C4[]; /* h:m:s format */
extern const char lbl_806D2D80[5]; /* "%08d" */
unsigned int OperationClock_GetLifetimeSeconds(void);
void OperationClock_Commit(void);
void NetDiag_PacketRatioPage(TestPage *self, int phase, int arg);
}

static inline void OperationTime_DrawHMS(TestPage *self, int y, unsigned int secs)
{
    DrawText(self->text, 0x1A4, y, 7, 1.0f, lbl_803104C4, secs / 3600, (secs / 60) % 60, secs % 60);
}

#pragma exceptions on

extern "C" int OperationTime_Page(TestPage *self, int phase)
{
    InputPlayer *pl;
    OperationStats *st;
    unsigned int life;
    unsigned int play;
    unsigned int avg;
    float ratio;

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
            OperationClock_Commit();
            if (self->cursor == 0) {
                self->next = 0x1A;
                NetDiag_PacketRatioPage(self, 0, -1);
            } else {
                self->next = 0;
            }
        }
    }
    if (phase == 2) {
        TestPage_DrawItems(self, lbl_803FCE88, self->cursor + 8);
        if (self->text != 0) {
            life = OperationClock_GetLifetimeSeconds();
            st = (OperationStats *)self->data;
            play = st->playSeconds;
            avg = play / st->counters[0];
            ratio = (float)play / (float)life;
            if (life == 0) {
                ratio = 0.0f;
            }
            if (st->counters[0] == 0) {
                avg = 0;
            }
            OperationTime_DrawHMS(self, 0x30, life);
            OperationTime_DrawHMS(self, 0x48, play);
            OperationTime_DrawHMS(self, 0x60, avg);
            DrawText(self->text, 0x1A4, 0x78, 7, 1.0f, lbl_80310478, 100.0f * ratio);
            DrawText(self->text, 0x1A4, 0x90, 7, 1.0f, lbl_806D2D80, ((OperationStats *)self->data)->counters[0]);
            DrawText(self->text, 0x1A4, 0xA8, 7, 1.0f, lbl_806D2D80, ((OperationStats *)self->data)->counters[1]);
            DrawText(self->text, 0x1A4, 0xC0, 7, 1.0f, lbl_806D2D80, ((OperationStats *)self->data)->counters[2]);
        }
    }
    return 1;
}

#pragma exceptions reset
