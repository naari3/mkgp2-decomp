#ifndef GAME_VOICEBROWSER_PRIVATE_H
#define GAME_VOICEBROWSER_PRIVATE_H
#include "game/TestMenuPage.h"
#include "game/os_time.h"
#include "game/types/VoiceClip.h"
struct VoiceBrowser {
    void *vtable;
    void *context;
    int selection;
    float fraction;
};
extern "C" {
VoiceClip *fn_801B3A50(int);
int fn_801B3A88(int);
void fn_801B3980(int);
void fn_801B3A4C();
int fn_801B11B8();
void DisplayContext_Flush(void *);
extern const char lbl_803993A0[];
extern OSTime g_voiceStreamLastPollTime, g_voiceStreamStartTime;
extern const float lbl_806D9848, lbl_806D984C, lbl_806D9850;
extern const float lbl_806D9854, lbl_806D9858, lbl_806D985C;
extern const float lbl_806D9860, lbl_806D9864, lbl_806D9868, lbl_806D986C;
extern const float lbl_806D9870;
}
#endif

