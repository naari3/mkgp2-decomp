#ifndef GAME_TESTMENUPAGE_H
#define GAME_TESTMENUPAGE_H

/* Shared declarations for the operator test-menu pages. Each page handler
 * is called by UI_PageDispatcher as Page(self, phase, -1): phase 0 enters
 * the page, 1 handles input, 2 draws. */

struct InputPlayer {
    virtual void v0();
    virtual void v1();
    virtual float v2();
    virtual void v3();
    virtual float StickRight();
    virtual float StickLeft();
    virtual unsigned char Pressed(int mask);
    virtual unsigned char Held(int mask);
};

/* Menu text table entry, in 14x24 character cells; ends at text == 0. */
struct MenuItem {
    int x;
    int y;
    const char *text;
};

struct TestPage {
    unsigned char pad_0[8];
    int blink;              /* 0x08: frames left of the selection blink */
    unsigned char pad_C[4];
    int next;               /* 0x10: page to switch to */
    unsigned char pad_14[4];
    int cursor;             /* 0x18 */
    int sub;                /* 0x1C */
    unsigned char pad_20[0x14];
    int variant;            /* 0x34 */
    unsigned char pad_38[0x238];
    void *text;             /* 0x270 */
    void *data;             /* 0x274 */
};

extern "C" {
/* Shared test-menu string pool in .rodata. */
extern char lbl_8030E598[];
void *GetInputManager(void);
InputPlayer *InputMgr_GetPlayer(void *, int);
void DrawText(void *ctx, int x, int y, int color, float scale, const char *fmt, ...);
}

/* Draws a menu table; entry `sel` blinks. */
static inline void TestPage_DrawItems(TestPage *self, MenuItem *it, int sel)
{
    int i;

    for (i = 0; it[i].text != 0; i++) {
        if (i != sel || self->blink <= 0x1E) {
            if (self->text != 0) {
                DrawText(self->text, it[i].x * 14, it[i].y * 24, 7, 1.0f, it[i].text);
            }
        }
    }
}

#endif
