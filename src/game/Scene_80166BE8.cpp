#include "game/TestMenuPage.h"
#include "game/Scene_80166BE8_private.h"

extern "C" {
extern char Scene_801661FC_rodata_80369D78[];
extern char lbl_806D89CC[4];
extern void *lbl_806D10A0;
extern unsigned char g_playerData[];
char *fn_8013C26C(int, int);
char *get_title_name(void *, int, unsigned char, int, int);
void fn_80168A4C(void *, char *, float, float, ...);
TitlePreview *fn_80252D90(void *);
#pragma exceptions on
void fn_80166BE8(TitlePreviewScene *self) {
    char *strings = Scene_801661FC_rodata_80369D78;
    if (InputMgr_GetPlayer(GetInputManager(), 0)->StickRight() > 0.7f) {
        if (self->repeat < 0) self->repeat = 0;
        else if (++self->repeat > 20) self->repeat = 18;
    } else if (InputMgr_GetPlayer(GetInputManager(), 0)->StickLeft() > 0.7f) {
        if (self->repeat > 0) self->repeat = 0;
        else if (--self->repeat < -20) self->repeat = -18;
    } else self->repeat = 0;
    unsigned char changed = 0;
    int step = 0;
    if (InputMgr_GetPlayer(GetInputManager(), 0)->Pressed(1)) {
        ++self->cursor;
        if (self->cursor > 2) self->cursor = 0;
    } else if (InputMgr_GetPlayer(GetInputManager(), 0)->Pressed(2)) {
        --self->cursor;
        if (self->cursor < 0) self->cursor = 2;
    } else if (self->repeat == 1) step = 1;
    else if (self->repeat == -1) step = -1;
    if (step != 0) {
        changed = 1;
        switch (self->cursor) {
        case 0:
            self->character += step;
            if (self->character < 0) self->character = 10;
            if (self->character > 10) self->character = 0;
            break;
        case 1:
            self->title += step;
            self->variant = 0;
            if (self->title < 0) self->title = 204;
            if (self->title > 204) self->title = 0;
            break;
        case 2:
            self->variant += step;
            if (self->variant < 0) self->variant = 15;
            if (self->variant > 15) self->variant = 0;
            break;
        }
    }
    fn_80168A4C(self->text, lbl_806D89CC, 20.0f, 24.0f * self->cursor + 140.0f);
    fn_80168A4C(self->text, strings + 0x5a4, 40.0f, 140.0f, fn_8013C26C(self->character, -1));
    fn_80168A4C(self->text, strings + 0x5b8, 40.0f, 164.0f, self->title);
    fn_80168A4C(self->text, strings + 0x5cc, 40.0f, 188.0f, self->variant);
    void *db;
    if ((db = lbl_806D10A0) == 0) db = 0;
    if (db) {
        char *name = get_title_name(db, self->title, self->variant, self->character, 0);
        fn_80168A4C(self->text, strings + 0x5e0, 40.0f, 236.0f, name);
    }
    if (changed) {
        if (self->preview) {
            delete self->preview;
            self->preview = 0;
        }
    }
    if (!self->preview) {
        g_playerData[0x1b8] = self->character;
        g_playerData[0x19b] = self->title;
        g_playerData[0x19c] = self->variant;
        self->preview = fn_80252D90(self->text);
        if (!self->preview) return;
    }
    self->preview->Update();
}
#pragma exceptions reset
}
