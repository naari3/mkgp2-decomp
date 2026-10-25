#include "game/os_time.h"

extern unsigned char g_voiceSystemInitDone;
extern signed char lbl_806D178F;
extern OSTime lbl_806D1798;

void fn_801B377C(void) {
    OSTime now;

    if (g_voiceSystemInitDone) {
        now = OSGetTime();
        if ((float)OSTicksToMilliseconds(now - lbl_806D1798) / 1000.0f <= 0.8f) {
            lbl_806D178F = lbl_806D178F + 1;
        } else {
            lbl_806D178F = 1;
        }
        lbl_806D1798 = now;
    }
}
