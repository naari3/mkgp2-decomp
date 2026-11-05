/*
 * NetDiag_CounterPage, 0x80067F74..0x8006830C: network diagnostics
 * service-menu page that lists the per-link packet counters.
 * mode 0 = enter, 1 = input, 2 = draw.
 *
 * Compiled as C++ (#pragma cplusplus on, PushPrompt.c precedent): the
 * button polling is a real virtual call (vtable loads through r12).
 * The two item-list loops are one inline helper (DrawMenu) expanded
 * twice; writing them out by hand leaves a copy (`mr r27, r0`) on the
 * first table base. lmw/stmw prologue -> #pragma use_lmw_stmw.
 */
#pragma cplusplus on
#pragma use_lmw_stmw on

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

/* Per-link packet counters; each counter row is 4 ints at stride 8. */
typedef struct NetStats {
    char pad_0x000[0x37C];
    int link[8][8]; /* 0x37C..0x47C */
} NetStats;

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
    NetStats *stats;         /* 0x274 */
} ServiceMenuRec;

extern "C" {
extern MenuItem lbl_803FD71C[];
extern MenuItem lbl_803FD7DC[];
extern const char lbl_80310484[];
extern const float lbl_806D2D44;

void *GetInputManager(void);
InputPlayer *InputMgr_GetPlayer(void *mgr, int index);
void NetDiag_QualityPage(void *self, int mode, int arg);
void DrawText(void *ctx, int x, int y, int color, float scale, const char *fmt, ...);

static inline void DrawMenu(ServiceMenuRec *self, MenuItem *items)
{
    int selected = self->field_0x18 + 11;
    int i;

    for (i = 0; items[i].text != 0; i++) {
        if (i == selected && self->blinkTimer > 30) {
            continue;
        }
        if (self->displayCtx != 0) {
            DrawText(self->displayCtx, items[i].x * 14, items[i].y * 24, 7, lbl_806D2D44, items[i].text);
        }
    }
}

int NetDiag_CounterPage(ServiceMenuRec *self, int mode)
{
    NetStats *s;

    if (mode == 0) {
        self->field_0x18 = 0;
    }
    if (mode == 1) {
        InputPlayer *player = InputMgr_GetPlayer(GetInputManager(), 0);
        if (player->isTriggered(0x800)) {
            self->blinkTimer = 0x1F;
            if (++self->field_0x18 > 1) {
                self->field_0x18 = 0;
            }
        }
        if (player->isTriggered(0x1000)) {
            if (self->field_0x18 == 0) {
                self->pageId = 0x1F;
                NetDiag_QualityPage(self, 0, -1);
            } else {
                self->pageId = 0;
            }
        }
    }
    if (mode == 2) {
        s = self->stats;
        if (self->cabinetType == 0) {
            DrawMenu(self, lbl_803FD71C);
        } else {
            DrawMenu(self, lbl_803FD7DC);
        }
        DrawText(self->displayCtx, 126, 96, 7, lbl_806D2D44, lbl_80310484,
                 s->link[6][0], s->link[6][2], s->link[6][4], s->link[6][6]);
        DrawText(self->displayCtx, 126, 120, 7, lbl_806D2D44, lbl_80310484,
                 s->link[0][0], s->link[0][2], s->link[0][4], s->link[0][6]);
        DrawText(self->displayCtx, 126, 144, 7, lbl_806D2D44, lbl_80310484,
                 s->link[7][0], s->link[7][2], s->link[7][4], s->link[7][6]);
        DrawText(self->displayCtx, 126, 168, 7, lbl_806D2D44, lbl_80310484,
                 s->link[1][0], s->link[1][2], s->link[1][4], s->link[1][6]);
        DrawText(self->displayCtx, 126, 192, 7, lbl_806D2D44, lbl_80310484,
                 s->link[2][0], s->link[2][2], s->link[2][4], s->link[2][6]);
        DrawText(self->displayCtx, 126, 216, 7, lbl_806D2D44, lbl_80310484,
                 s->link[3][0], s->link[3][2], s->link[3][4], s->link[3][6]);
        DrawText(self->displayCtx, 126, 240, 7, lbl_806D2D44, lbl_80310484,
                 s->link[4][0], s->link[4][2], s->link[4][4], s->link[4][6]);
        DrawText(self->displayCtx, 126, 264, 7, lbl_806D2D44, lbl_80310484,
                 s->link[5][0], s->link[5][2], s->link[5][4], s->link[5][6]);
    }
    return 1;
}

}
