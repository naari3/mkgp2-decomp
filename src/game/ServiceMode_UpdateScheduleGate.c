#include "game/types/OSCalendarTime.h"

typedef struct ServiceSlot {
    signed char hour;
    signed char minute;
} ServiceSlot;

typedef struct ServiceSettings {
    unsigned char pad[0x53];
    ServiceSlot schedule[7];
} ServiceSettings;

extern ServiceSettings lbl_80598A60;
extern unsigned char lbl_806CEF68;
extern unsigned char lbl_806CEF69;
extern unsigned char PcbSync_AlwaysZero_Stub(void);
extern unsigned char ServiceValue_Get(void);
extern void ServiceValue_Set(int);
extern unsigned char ServiceEnable_Get(void);
extern long long OSGetTime(void);
extern void OSTicksToCalendarTime(long long ticks, OSCalendarTime *td);

static inline int in_window(OSCalendarTime *time) {
    int now = time->hour * 60 + time->min;
    int start;
    int day = time->wday;

    start = lbl_80598A60.schedule[day].hour * 60 + lbl_80598A60.schedule[day].minute;
    if (lbl_80598A60.schedule[day].hour != 0 && start - 10 <= now && now <= start + 10) {
        return 1;
    }
    if (time->hour != 0) {
        return 0;
    }
    day -= 1;
    if (day == -1) {
        day = 6;
    }
    if (lbl_80598A60.schedule[day].hour != 0) {
        start = lbl_80598A60.schedule[day].hour * 60 + lbl_80598A60.schedule[day].minute;
        now += 0x5A0;
        if (start - 10 <= now && now <= start + 10) {
            return 1;
        }
    }
    return 0;
}

void ServiceMode_UpdateScheduleGate(void) {
    OSCalendarTime time;

    if (PcbSync_AlwaysZero_Stub() || lbl_806CEF68 != 0) {
        lbl_806CEF69 = ServiceValue_Get();
        lbl_806CEF68 = 0;
    }
    if (ServiceEnable_Get() && lbl_806CEF69 != 1) {
        OSTicksToCalendarTime(OSGetTime(), &time);
        ServiceValue_Set(in_window(&time));
    }
}
