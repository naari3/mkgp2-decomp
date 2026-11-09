/*
 * SwitchTest_Page @ 0x800715AC..0x80071AE0: the switch test page. Shows the
 * coin counter, the buttons and the analog steering/pedal values (relative
 * to the stored neutral calibration). Holding start + select returns to the
 * monitor test page.
 *
 * The target divides each axis difference by 64 in place (same register).
 * With propagation on, mwcc rematerializes an in-place `x = x / 64` at its
 * first use, so the function is built with opt_propagation off; the menu
 * item loop then has to walk the pointer itself (the shared
 * TestPage_DrawItems inline relies on `i = 0` being propagated).
 */
#include "game/TestMenuPage.h"

struct HandleCalib {
    unsigned char pad_0[0x34];
    int steer; /* 0x34 */
    int pos;   /* 0x38 */
    int brake; /* 0x3C */
    int accel; /* 0x40 */
};

struct SwitchTestPage {
    unsigned char pad_0[0x10];
    int next;               /* 0x10 */
    unsigned char pad_14[0x14];
    int coins;              /* 0x28 */
    unsigned char pad_2C[0x10];
    int flash;              /* 0x3C */
    unsigned int lastCoin;  /* 0x40 */
    int steer;              /* 0x44 */
    int brake;              /* 0x48 */
    int accel;              /* 0x4C */
    unsigned char pad_50[0x220];
    void *text;             /* 0x270 */
    HandleCalib *calib;     /* 0x274 */
};

extern "C" {
extern unsigned short g_jvsOperatorBits[16];
extern MenuItem lbl_803FC654[];
extern const char lbl_80310BF4[];
extern const char lbl_806D2D94[4];  /* off label */
extern const char lbl_806D2DAC[3];  /* on label */
extern const char lbl_806D2DCC[3];  /* "%d" */
extern const char lbl_806D2E50[4];
extern const char lbl_806D2E54[6];
extern const char lbl_806D2E5C[4];
void MonitorTest_Page(SwitchTestPage *self, int phase, int arg);
}

/* Same as TestPage_DrawItems, written as a pointer walk (see the note above). */
static inline void SwitchTest_DrawItems(TestPage *self, MenuItem *it, int sel)
{
    int i;

    for (i = 0; it->text != 0; it++, i++) {
        if (i != sel || self->blink <= 0x1E) {
            if (self->text != 0) {
                DrawText(self->text, it->x * 14, it->y * 24, 7, 1.0f, it->text);
            }
        }
    }
}

#pragma exceptions on

/* fakematch (pragma): natural code would use the default propagation and TestPage_DrawItems */
#pragma push
#pragma opt_propagation off
extern "C" int SwitchTest_Page(SwitchTestPage *self, int phase)
{
    InputPlayer *pl;
    unsigned short coin = g_jvsOperatorBits[12];
    int steer;
    int brake;
    int ac;

    if (phase == 0) {
        self->steer = self->calib->steer;
        self->accel = self->calib->accel;
        self->brake = self->calib->brake;
        self->lastCoin = coin;
        self->coins = 0;
        self->flash = 0;
    }
    if (phase == 1) {
        pl = InputMgr_GetPlayer(GetInputManager(), 0);
        if (coin == self->lastCoin + 1) {
            self->lastCoin = coin;
            self->coins = (self->coins + 1) % 1000;
            self->flash = 16;
        }
        if (self->flash > 0) {
            self->flash--;
        }
        if (pl->Held(0x1000) && pl->Held(0x800)) {
            self->next = 2;
            MonitorTest_Page(self, 0, 1);
        }
    }
    if (phase == 2) {
        pl = InputMgr_GetPlayer(GetInputManager(), 0);
        steer = g_jvsOperatorBits[4] - self->steer;
        /* The phase dispatch is complete; reuse its saved value for acceleration. */
        phase = g_jvsOperatorBits[5] - self->accel;
        brake = g_jvsOperatorBits[6] - self->brake;
        if (phase < 0) {
            phase = 0;
        }
        if (brake < 0) {
            brake = 0;
        }
        steer = steer / 64;
        ac = phase / 64;
        brake = brake / 64;
        if (self->text != 0) {
            DrawText(self->text, 0x134, 0x48, 4, 1.0f, lbl_806D2E50);
            if (self->flash != 0) {
                DrawText(self->text, 0x15E, 0x78, 4, 1.0f, lbl_806D2DCC, self->coins);
            } else {
                DrawText(self->text, 0x15E, 0x78, 7, 1.0f, lbl_806D2DCC, self->coins);
            }
            if (pl->Held(0x800)) {
                DrawText(self->text, 0x15E, 0x90, 4, 1.0f, lbl_806D2DAC);
            } else {
                DrawText(self->text, 0x15E, 0x90, 7, 1.0f, lbl_806D2D94);
            }
            if (pl->Held(0x1000)) {
                DrawText(self->text, 0x15E, 0xA8, 4, 1.0f, lbl_806D2DAC);
            } else {
                DrawText(self->text, 0x15E, 0xA8, 7, 1.0f, lbl_806D2D94);
            }
            DrawText(self->text, 0x15E, 0xC0, 7, 1.0f, lbl_806D2DCC, steer);
            if (steer >= 0x180) {
                DrawText(self->text, 0x1B2, 0xC0, 2, 1.0f, lbl_80310BF4);
            }
            if (steer <= -0x180) {
                DrawText(self->text, 0x1B2, 0xC0, 2, 1.0f, lbl_806D2E54);
            }
            DrawText(self->text, 0x15E, 0xD8, 7, 1.0f, lbl_806D2DCC, ac);
            if (ac >= 0x140) {
                DrawText(self->text, 0x1B2, 0xD8, 2, 1.0f, lbl_806D2E5C);
            }
            DrawText(self->text, 0x15E, 0xF0, 7, 1.0f, lbl_806D2DCC, brake);
            if (brake >= 0x140) {
                DrawText(self->text, 0x1B2, 0xF0, 2, 1.0f, lbl_806D2E5C);
            }
            if (pl->Held(0x2000)) {
                DrawText(self->text, 0x15E, 0x108, 4, 1.0f, lbl_806D2DAC);
            } else {
                DrawText(self->text, 0x15E, 0x108, 7, 1.0f, lbl_806D2D94);
            }
            if (pl->Held(0x400)) {
                DrawText(self->text, 0x15E, 0x120, 4, 1.0f, lbl_806D2DAC);
            } else {
                DrawText(self->text, 0x15E, 0x120, 7, 1.0f, lbl_806D2D94);
            }
        }
        SwitchTest_DrawItems((TestPage *)self, lbl_803FC654, -1);
    }
    return 1;
}

#pragma pop

#pragma exceptions reset
