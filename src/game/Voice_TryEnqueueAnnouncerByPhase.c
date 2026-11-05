#include "game/VoicePhasePrivate.h"

int Voice_TryEnqueueAnnouncerByPhase(VoicePhaseKart *kart) {
    int entryIndex;

    if (!g_voiceSystemInitDone) return 0;
    if (kart == 0) return 0;
    entryIndex = kart->entryIndex;
    g_raceEntryArray[entryIndex].state = 1;
    if (g_gameMode == 2 && SyncSlot_GetHostSend() == 0) return 1;
    if (g_goalFanfareTriggered) return 1;
    if ((int)g_bgmStateId == 0x6E && lbl_806D177C == -1 && lbl_806D1774 == 0) {
        if (entryIndex == lbl_806D1775) {
            if ((g_voiceTickCounter & 3) == 0) {
                SpriteVoice_Push(0x1C9, 11, 1, 1);
            } else if ((g_voiceTickCounter & 3) == 1) {
                SpriteVoice_Push(0x1CA, 11, 1, 1);
            } else if ((g_voiceTickCounter & 3) == 2) {
                SpriteVoice_Push(0x179, 11, 1, 1);
            } else {
                SpriteVoice_Push(0x17A, 11, 1, 1);
            }
            g_bgmStateId = 0;
        }
        return 1;
    }
    return 1;
}
