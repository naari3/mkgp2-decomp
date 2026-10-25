/*
 * SystemInfo_UI @ 0x80066B74..0x80066E10: the system information test page.
 * Draws the item table, the current date/time, the cabinet variant and the
 * boot counters. Its strings live in the shared test-menu .rodata pool at
 * lbl_8030E598 and are addressed by offset from that base.
 */

typedef long long OSTime;

struct OSCalendarTime {
    int sec;
    int min;
    int hour;
    int mday;
    int mon;
    int year;
    int wday;
    int yday;
    int msec;
    int usec;
};

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

struct MenuItem {
    int x;
    int y;
    const char *text;
};

struct TestPage {
    unsigned char pad_0[8];
    int blink;              /* 0x08 */
    unsigned char pad_C[4];
    int next;               /* 0x10 */
    unsigned char pad_14[0x20];
    int variant;            /* 0x34 */
    unsigned char pad_38[0x238];
    void *text;             /* 0x270 */
};

struct DayNames {
    const char *name[7];
};

struct VariantNames {
    const char *name[3];
};

extern "C" {
extern char lbl_8030E598[];
extern MenuItem lbl_803FDA94[];
extern const char lbl_806D2D5C[6];
extern const char lbl_806D2D64[3];
extern int lbl_806D1118;
extern int lbl_806D111C;
void *GetInputManager(void);
InputPlayer *InputMgr_GetPlayer(void *, int);
void DrawText(void *ctx, int x, int y, int color, float scale, const char *fmt, ...);
void *BootStateStruct_Get(void);
OSTime OSGetTime(void);
void OSTicksToCalendarTime(OSTime ticks, OSCalendarTime *td);
}

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

#pragma exceptions on

extern "C" int SystemInfo_UI(TestPage *self, int phase)
{
    char *pool = lbl_8030E598;
    DayNames days;
    VariantNames variants;
    OSCalendarTime t;
    void *boot;

    if (phase == 1) {
        if (InputMgr_GetPlayer(GetInputManager(), 0)->Pressed(0x1000)) {
            self->next = 0;
        }
    }
    if (phase == 2) {
        TestPage_DrawItems(self, lbl_803FDA94, 4);
        if (self->text != 0) {
            days = *(DayNames *)(pool + 0x1B2C);
            variants = *(VariantNames *)(pool + 0x1B48);
            boot = BootStateStruct_Get();
            OSTicksToCalendarTime(OSGetTime(), &t);
            DrawText(self->text, 0xB6, 0x48, 7, 1.0f, pool + 0x1C90, t.year, t.mon + 1, t.mday,
                     days.name[t.wday], t.hour, t.min, t.sec);
            if (boot != 0) {
                if (self->variant == 0) {
                    DrawText(self->text, 0xB6, 0x60, 7, 1.0f, pool + 0x1CB4);
                } else if (self->variant == 1) {
                    DrawText(self->text, 0xB6, 0x60, 7, 1.0f, pool + 0x1CCC);
                } else {
                    DrawText(self->text, 0xB6, 0x60, 7, 1.0f, pool + 0x1CE4);
                }
                DrawText(self->text, 0xB6, 0x78, 7, 1.0f, lbl_806D2D5C, lbl_806D111C, lbl_806D1118);
            }
            DrawText(self->text, 0xB6, 0x90, 7, 1.0f, lbl_806D2D64, variants.name[self->variant]);
        }
    }
    return 1;
}

#pragma exceptions reset
