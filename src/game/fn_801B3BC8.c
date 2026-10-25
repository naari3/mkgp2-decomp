#include "game/os_time.h"

typedef struct RaceEntry {
    char pad00[0x34];
    signed char pending;
    char pad35[0x1F];
    unsigned char ready;
    char pad55[3];
    OSTime lastTime;
    char pad60[8];
} RaceEntry;

extern unsigned char g_voiceSystemInitDone;
extern RaceEntry g_raceEntryArray[];

int fn_801B3BC8(int kart) {
    OSTime now;

    if (!g_voiceSystemInitDone) {
        return 0;
    }
    if (kart < 0 || kart >= 8) {
        return 0;
    }
    now = OSGetTime();
    if ((float)OSTicksToMilliseconds(now - g_raceEntryArray[kart].lastTime) / 1000.0f >= 30.0f) {
        if (--g_raceEntryArray[kart].pending == 0) {
            g_raceEntryArray[kart].ready = 1;
            g_raceEntryArray[kart].lastTime = now;
            g_raceEntryArray[kart].pending = -76;
        }
    }
    return 1;
}
