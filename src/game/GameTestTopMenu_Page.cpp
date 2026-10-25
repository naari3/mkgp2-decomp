/*
 * GameTestTopMenu_Page, 0x80073878..0x80073B00: the service menu's
 * top-level page (cursor movement on mode 1, item list on mode 2).
 *
 * NonMatching: one extra `mr` when the cabinet-type-2 list base is set up
 * (the target loads it straight into r28).
 */

typedef struct MenuItem {
    int x;
    int y;
    const char *text;
} MenuItem;

/* Only the slot used here matters: isTriggered sits at vtable +0x20. */
class InputPlayer {
public:
    virtual void vf08();
    virtual void vf0C();
    virtual void vf10();
    virtual void vf14();
    virtual void vf18();
    virtual void vf1C();
    virtual unsigned char isTriggered(int mask);
};

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

void *GetInputManager(void);
InputPlayer *InputMgr_GetPlayer(void *mgr, int index);
void Game_Shutdown(void);
void UI_PageDispatcher(void *self, int mode);
void DrawText(void *ctx, int x, int y, int color, float scale, const char *fmt, ...);

int GameTestTopMenu_Page(ServiceMenuRec *self, int mode)
{
    InputPlayer *player;
    MenuItem *item;
    int selected;
    int i;

    if (mode == 1) {
        player = InputMgr_GetPlayer(GetInputManager(), 0);
        if (player->isTriggered(0x800)) {
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
        if (player->isTriggered(0x1000)) {
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
            selected += 2;
            for (i = 0, item = lbl_803FC0D8; item->text != 0; item++, i++) {
                if (i == selected && self->blinkTimer > 30) {
                    continue;
                }
                if (self->displayCtx != 0) {
                    DrawText(self->displayCtx, item->x * 14, item->y * 24, 7, lbl_806D2D44, item->text);
                }
            }
        } else {
            selected = self->cursor + 2;
            for (i = 0, item = lbl_803FC018; item->text != 0; item++, i++) {
                int color;

                if (i == selected && self->blinkTimer > 30) {
                    continue;
                }
                color = 7;
                if (i == 6 && (self->cfg[0x23] == 0 || self->cfg[0x24] == 0)) {
                    color = 8;
                }
                if (self->displayCtx != 0) {
                    DrawText(self->displayCtx, item->x * 14, item->y * 24, (unsigned char)color, lbl_806D2D44, item->text);
                }
            }
        }
    }
    return 1;
}

}
