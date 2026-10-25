/*
 * ClockSetting_Page @ 0x8006A500..0x8006AA84: the clock setting test page.
 * Each weekday has an operation hour/minute entry (data + 0x53, two signed
 * bytes per day); sub-state 1 edits the hour (0 = off), 2 the minute in
 * 15-minute steps. The page also shows the current date and time.
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

struct ClockEntry {
    signed char hour;
    signed char min;
};

struct ClockSettings {
    unsigned char pad_0[0x53];
    ClockEntry day[7]; /* 0x53 */
};

extern "C" {
extern MenuItem lbl_803FCE4C[];
extern const char lbl_806D2D64[3];
extern const char lbl_806D2D68[5];
extern const char lbl_806D2D90[2];
extern const char lbl_806D2D94[4];
extern const char lbl_806D2D98[4];
extern const char lbl_806D2D9C[5];
void Backup_PublishShadowCopy_Inline(void);
OSTime OSGetTime(void);
void OSTicksToCalendarTime(OSTime ticks, OSCalendarTime *td);
}

#define CLOCK_DAY(self, i) (((ClockSettings *)(self)->data)->day[i])
#define CLOCK_EDIT(self, i) (((ClockEntry *)((char *)(self)->data + 0x53))[i])

static inline ClockEntry *ClockSetting_Entry(TestPage *self)
{
    return &((ClockSettings *)self->data)->day[self->cursor];
}

#pragma exceptions on

extern "C" int ClockSetting_Page(TestPage *self, int phase)
{
    char *pool = lbl_8030E598;
    DayNames days;
    OSCalendarTime t;
    int y;
    InputPlayer *pl;
    int i;

    if (phase == 0) {
        self->cursor = 7;
        self->sub = 0;
    }
    if (phase == 1) {
        pl = InputMgr_GetPlayer(GetInputManager(), 0);
        if (self->sub == 0) {
            if (pl->Pressed(0x800)) {
                self->blink = 0x1F;
                if (++self->cursor > 7) {
                    self->cursor = 0;
                }
            }
            if (pl->Pressed(0x1000)) {
                if (self->cursor != 7) {
                    self->sub = 1;
                } else {
                    Backup_PublishShadowCopy_Inline();
                    self->next = 0;
                }
            }
        } else {
            if (pl->Pressed(0x800)) {
                if (self->sub == 1) {
                    if (++CLOCK_EDIT(self, self->cursor).hour > 0x18) {
                        CLOCK_EDIT(self, self->cursor).hour = 0;
                    }
                } else if ((CLOCK_EDIT(self, self->cursor).min += 15) >= 60) {
                    CLOCK_EDIT(self, self->cursor).min = 0;
                }
            }
            if (pl->Pressed(0x1000)) {
                if (self->sub == 1 && CLOCK_EDIT(self, self->cursor).hour == 0) {
                    self->sub = 0;
                } else {
                    self->sub = (self->sub + 1) % 3;
                }
            }
        }
    }
    if (phase == 2) {
        days = *(DayNames *)(pool + 0x1B10);
        TestPage_DrawItems(self, lbl_803FCE4C, -1);
        if (self->text != 0) {
            for (i = 0; i < 7; i++) {
                if (i != self->cursor || self->sub != 0 || self->blink <= 0x1E) {
                    DrawText(self->text, 0x2A, (i + 5) * 24, 7, 1.0f, lbl_806D2D64, days.name[i]);
                }
                y = (i + 5) * 24;
                DrawText(self->text, 0x7E, y, 7, 1.0f, lbl_806D2D90);
                if (i != self->cursor || self->sub != 1 || self->blink <= 0x1E) {
                    int h = CLOCK_DAY(self, i).hour;
                    if (CLOCK_DAY(self, i).hour == 0) {
                        DrawText(self->text, 0xE0, y, 7, 1.0f, lbl_806D2D94);
                    } else {
                        DrawText(self->text, 0xE0, y, 4, 1.0f, lbl_806D2D98, h);
                    }
                }
                if (CLOCK_DAY(self, i).hour != 0) {
                    DrawText(self->text, 0xFC, y, 4, 1.0f, lbl_806D2D90);
                }
                if (i != self->cursor || self->sub != 2 || self->blink <= 0x1E) {
                    if (CLOCK_DAY(self, i).hour != 0) {
                        DrawText(self->text, 0x10A, y, 4, 1.0f, lbl_806D2D9C, CLOCK_DAY(self, i).min);
                    }
                }
                if (CLOCK_DAY(self, i).hour != 0) {
                    int h = CLOCK_DAY(self, i).hour;
                    int m = CLOCK_DAY(self, i).min;
                    int startH = h;
                    int startM = m - 10;
                    int endH = h;
                    int endM = m + 10;
                    if (startM < 0) {
                        startM = 50;
                        startH = h - 1;
                    }
                    if (endM >= 60) {
                        endM = 0;
                        endH = endH + 1;
                    }
                    DrawText(self->text, 0x142, y, 7, 1.0f, pool + 0x1F3C, startH, startM, endH, endM);
                }
            }
            if (self->cursor != 7 || self->blink <= 0x1E) {
                DrawText(self->text, 0x2A, 0x138, 7, 1.0f, lbl_806D2D68);
            }
            OSTicksToCalendarTime(OSGetTime(), &t);
            DrawText(self->text, 0xE0, 0x48, 7, 1.0f, pool + 0x1C90, t.year, t.mon + 1, t.mday,
                     days.name[t.wday], t.hour, t.min, t.sec);
        }
    }
    return 1;
}

#pragma exceptions reset
