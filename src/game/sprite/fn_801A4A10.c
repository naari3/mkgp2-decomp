#include "game/SpriteVoicePrivate.h"
/* The low word is the adjacent g_bgmStateTimeLo symbol. */
extern OSTime g_bgmStateTimeHi;
extern const float lbl_806D9804, lbl_806D980C;
extern signed char lbl_806D1776;
extern unsigned int g_voiceTickCounter;
extern unsigned char g_bgmStateId;

void fn_801A4A10(void) {
    if ((float)OSTicksToMilliseconds(OSGetTime() - g_bgmStateTimeHi) / lbl_806D9804 > lbl_806D980C) {
        SpriteVoice_Push(SpriteVoice_Select(g_raceEntryArray[lbl_806D1776].character,
                         g_raceEntryArray[lbl_806D1776].id), 7, 1, 1);
        if ((g_voiceTickCounter % 2) == 0) SpriteVoice_Push(0x1D9, 7, 1, 1);
        else SpriteVoice_Push(0x1DA, 7, 1, 1);
        g_bgmStateId = 0;
    }
}
