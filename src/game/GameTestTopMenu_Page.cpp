/*
 * GameTestTopMenu_Page, 0x80073878..0x80073B00: the service menu's
 * top-level page (cursor movement on mode 1, item list on mode 2).
 */

#include "game/TestMenuPage.h"

typedef struct ServiceMenuRec {
    void *vtbl;              /* 0x000 */
    int isJapanese;          /* 0x004 */
    int blinkTimer;          /* 0x008 */
    int clockTimer;          /* 0x00C */
    int pageId;              /* 0x010 */
    int cursor;              /* 0x014 */
    int field_0x18;          /* 0x018 */
    char pad_0x1C[0x34 - 0x1C];
    int cabinetType;         /* 0x034 */
    char pad_0x38[0x270 - 0x38];
    void *displayCtx;        /* 0x270 */
    unsigned char *cfg;      /* 0x274 */
} ServiceMenuRec;

extern "C" {
extern MenuItem lbl_803FC018[]; /* standard menu */
extern MenuItem lbl_803FC0D8[]; /* cabinet type 2 menu */
extern float lbl_806D2D44;

void Game_Shutdown(void);
void UI_PageDispatcher(void *self, int mode);

static inline void DrawStandardItems(ServiceMenuRec *self, MenuItem *items)
{
    int i;
    int selected = self->cursor + 2;
    for (i = 0; items[i].text != 0; i++) {
        if (i == selected && self->blinkTimer > 30) {
            continue;
        }
        int color = 7;
        if (i == 6 && (self->cfg[0x23] == 0 || self->cfg[0x24] == 0)) {
            color = 8;
        }
        if (self->displayCtx != 0) {
            DrawText(self->displayCtx, items[i].x * 14, items[i].y * 24,
                     (unsigned char)color, lbl_806D2D44, items[i].text);
        }
    }
}

int GameTestTopMenu_Page(ServiceMenuRec *self, int mode)
{
    InputPlayer *player;
    int selected;

    if (mode == 1) {
        player = InputMgr_GetPlayer(GetInputManager(), 0);
        if (player->Pressed(0x800)) {
            signed char coinA = (signed char)self->cfg[0x23];
            signed char coinB = (signed char)self->cfg[0x24];

            self->blinkTimer = 0x1F;
            if (++self->cursor > 10) {
                self->cursor = 0;
            }
            if (self->cabinetType == 2 && self->cursor == 4) {
                self->cursor = 7;
            }
            if (coinA == 0 && self->cursor == 4) {
                self->cursor = 5;
            }
            if (coinB == 0 && self->cursor == 4) {
                self->cursor = 5;
            }
        }
        if (player->Pressed(0x1000)) {
            if (self->cursor == 10) {
                Game_Shutdown();
                return 0;
            }
            self->pageId = self->cursor + 1;
            self->field_0x18 = 0;
            UI_PageDispatcher(self, 0);
        }
    }
    if (mode == 2) {
        if (self->cabinetType == 2) {
            selected = self->cursor;
            if (selected > 4) {
                selected -= 3;
            }
            TestPage_DrawItems((TestPage *)self, lbl_803FC0D8, selected + 2);
        } else {
            DrawStandardItems(self, lbl_803FC018);
        }
    }
    return 1;
}

}
