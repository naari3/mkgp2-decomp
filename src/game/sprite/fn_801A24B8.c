#include "game/SpriteVoicePrivate.h"
extern int g_currentVoiceDispatchId;
extern signed char lbl_806D1775, lbl_806D1776, lbl_806D1777, lbl_806D177C;
extern unsigned char g_bgmStateId;
void fn_801A24B8(void) {
    if (g_voiceQueueHead == 0 && g_currentVoiceDispatchId == -1) {
        if (lbl_806D1777 > g_raceEntryArray[lbl_806D1775].player) {
            if ((lbl_806D1777 + g_raceEntryArray[lbl_806D1775].player) % 2 == 0) {
                SpriteVoice_Push(SpriteVoice_Select(g_raceEntryArray[lbl_806D1775].character,
                    g_raceEntryArray[lbl_806D1775].id), 14, 1, 1);
                SpriteVoice_Push(0x1E2, 14, 1, 1);
            } else {
                SpriteVoice_Push(SpriteVoice_Select(g_raceEntryArray[lbl_806D1775].character,
                    g_raceEntryArray[lbl_806D1775].id), 14, 1, 1);
                SpriteVoice_Push(0x1D1, 14, 1, 1);
            }
        } else if (lbl_806D177C < g_raceEntryArray[lbl_806D1776].player) {
            if ((lbl_806D177C + g_raceEntryArray[lbl_806D1775].player) % 2 == 0) {
                SpriteVoice_Push(SpriteVoice_Select(g_raceEntryArray[lbl_806D1776].character,
                    g_raceEntryArray[lbl_806D1776].id), 14, 1, 1);
                SpriteVoice_Push(0x1E3, 14, 1, 1);
            } else {
                SpriteVoice_Push(SpriteVoice_Select(g_raceEntryArray[lbl_806D1776].character,
                    g_raceEntryArray[lbl_806D1776].id), 14, 1, 1);
                SpriteVoice_Push(0x1E4, 14, 1, 1);
            }
        }
        g_bgmStateId = 0;
    }
}
