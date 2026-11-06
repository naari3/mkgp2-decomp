#pragma cplusplus on
#include "game/CardRW_TestTopMenu_Private.h"

extern "C" {
extern const char lbl_806D2D48[4];
extern const char lbl_806D2D4C[4];
extern const char lbl_806D2D50[4];
extern const char lbl_806D2D54[4];
extern const char lbl_806D2D58[4];

unsigned char CardRW_ErrorDisplay(CardRWTestPage *self, unsigned char draw,
                                  unsigned char retry, unsigned char recover)
{
    const char *strings = lbl_8030E598;
    int error = self->error;
    if (error == 1) return 0;
    if (self->text == 0) return 1;
    if (error == 101) {
        if (draw) {
            DrawText(self->text, 84, 192, 7, 1.0f, lbl_806D2D48);
            DrawText(self->text, 84, 216, 7, 1.0f, strings + 0x1b6c);
            if (self->blink <= 30) {
                DrawText(self->text, 84, 264, 7, 1.0f, strings + 0x1b80);
            }
        }
        return 1;
    }
    if (error == 102) {
        if (draw) {
            DrawText(self->text, 84, 192, 7, 1.0f, lbl_806D2D4C);
            DrawText(self->text, 84, 216, 7, 1.0f, strings + 0x1b9c);
            if (self->blink <= 30) {
                DrawText(self->text, 84, 264, 7, 1.0f, strings + 0x1b80);
            }
        }
        return 1;
    }
    if (error == 104 || error == 100) {
        if (draw) {
            DrawText(self->text, 84, 192, 7, 1.0f, lbl_806D2D50);
            DrawText(self->text, 84, 216, 7, 1.0f, strings + 0x1bb8);
            if (self->blink <= 30) {
                DrawText(self->text, 84, 264, 7, 1.0f, strings + 0x1b80);
            }
        }
        return 1;
    }
    if (error == 105) {
        if (draw) {
            DrawText(self->text, 84, 192, 7, 1.0f, lbl_806D2D54);
            DrawText(self->text, 84, 216, 7, 1.0f, strings + 0x1bd0);
            if (self->blink <= 30) {
                DrawText(self->text, 84, 264, 7, 1.0f, strings + 0x1b80);
            }
        }
        return 1;
    }
    if (error == 106) {
        if (draw) {
            DrawText(self->text, 84, 192, 7, 1.0f, lbl_806D2D58);
            DrawText(self->text, 84, 216, 7, 1.0f, strings + 0x1be8);
            if (self->blink <= 30) {
                DrawText(self->text, 84, 264, 7, 1.0f, strings + 0x1b80);
            }
        }
        return 1;
    }
    if (error == 2) {
        if (draw) {
            DrawText(self->text, 84, 216, 7, 1.0f, strings + 0x1c00);
            if (self->blink <= 30) {
                DrawText(self->text, 84, 264, 7, 1.0f, strings + 0x1b80);
            }
        }
        return 1;
    }
    if (error == 6) {
        if (draw) {
            DrawText(self->text, 84, 216, 7, 1.0f, strings + 0x1c14);
            if (self->blink <= 30) {
                DrawText(self->text, 84, 264, 7, 1.0f, strings + 0x1b80);
            }
        }
        return 1;
    }
    if (error == 7) {
        if (draw) {
            DrawText(self->text, 84, 216, 7, 1.0f, strings + 0x1c24);
            if (self->blink <= 30) {
                DrawText(self->text, 84, 264, 7, 1.0f, strings + 0x1b80);
            }
        }
        return 1;
    }
    if (retry && error == 103) {
        if (draw) {
            DrawText(self->text, 84, 216, 7, 1.0f, strings + 0x1c34);
            if (self->blink <= 30) {
                DrawText(self->text, 84, 264, 7, 1.0f, strings + 0x1c58);
            }
        }
        return 1;
    }
    if (retry && error == 5) {
        if (draw) {
            DrawText(self->text, 84, 216, 7, 1.0f, strings + 0x1c34);
            if (self->blink <= 30) {
                DrawText(self->text, 84, 264, 7, 1.0f, strings + 0x1c58);
            }
        }
        return 1;
    }
    if (retry && recover && error == 4) {
        if (draw) {
            DrawText(self->text, 84, 216, 7, 1.0f, strings + 0x1c34);
            if (self->blink <= 30) {
                DrawText(self->text, 84, 264, 7, 1.0f, strings + 0x1c58);
            }
        }
        return 1;
    }
    if (error == 255) {
        if (draw) {
            DrawText(self->text, 84, 216, 7, 1.0f, strings + 0x1c6c);
            if (self->blink <= 30) {
                DrawText(self->text, 84, 264, 7, 1.0f, strings + 0x1b80);
            }
        }
        return 1;
    }
    return 0;
}
}
