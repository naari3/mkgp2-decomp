#include "game/SpriteVoicePrivate.h"
extern int g_currentVoiceDispatchId;
extern signed char lbl_806D1775, lbl_806D1777;
extern unsigned char g_bgmStateId;
void fn_801A1D98(void) {
    if (g_voiceQueueHead == 0 && g_currentVoiceDispatchId == -1) {
        if (lbl_806D1777 > g_raceEntryArray[lbl_806D1775].player) {
            if ((lbl_806D1777 + g_raceEntryArray[lbl_806D1775].player) % 2 == 0) {
                SpriteVoice_Push(SpriteVoice_Select(g_raceEntryArray[lbl_806D1775].character,
                    g_raceEntryArray[lbl_806D1775].id), 15, 1, 1);
                SpriteVoice_Push(0x1E3, 15, 1, 1);
            } else {
                SpriteVoice_Push(SpriteVoice_Select(g_raceEntryArray[lbl_806D1775].character,
                    g_raceEntryArray[lbl_806D1775].id), 15, 1, 1);
                SpriteVoice_Push(0x1D1, 15, 1, 1);
            }
        }
        g_bgmStateId = 0;
    }
}
