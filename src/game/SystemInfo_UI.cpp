/*
 * SystemInfo_UI @ 0x80066B74..0x80066E10: the system information test page.
 * Draws the item table, the current date/time, the cabinet variant and the
 * boot counters. Its strings live in the shared test-menu .rodata pool at
 * lbl_8030E598 and are addressed by offset from that base.
 */
#include "game/TestMenuPage.h"

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

struct DayNames {
    const char *name[7];
};

struct VariantNames {
    const char *name[3];
};

extern "C" {
extern MenuItem lbl_803FDA94[];
extern const char lbl_806D2D5C[6];
extern const char lbl_806D2D64[3];
extern int lbl_806D1118;
extern int lbl_806D111C;
void *BootStateStruct_Get(void);
OSTime OSGetTime(void);
void OSTicksToCalendarTime(OSTime ticks, OSCalendarTime *td);
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
