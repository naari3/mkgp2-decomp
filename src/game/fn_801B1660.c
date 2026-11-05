#include "game/VoicePhasePrivate.h"

int fn_801B1660(VoicePhaseKart *kart, VoicePhaseKart *target) {
    int priority;
    int selectedEntry;
    short voice;
    void *item;

    if (!g_voiceSystemInitDone) return 0;
    if (kart == 0) return 0;
    if (target == 0) return 0;
    item = g_raceEntryArray[target->entryIndex].item;
    if (item != 0 && KartItem_GetByte_f4(item)) {
        g_bgmStateId = 0;
        return 0;
    }
    g_raceEntryArray[kart->entryIndex].state = 5;
    g_raceEntryArray[kart->entryIndex].voiceTarget = target;
    if (g_gameMode == 2 && SyncSlot_GetHostSend() == 0) return 1;
    if (g_goalFanfareTriggered) return 1;
    if (target->flags->bits & 0x0080000000000000ULL) {
        g_bgmStateId = 0;
        return 1;
    }
    priority = -1;
    if ((signed char)g_bgmStateId == 7) {
        if (lbl_806D1775 == kart->entryIndex && lbl_806D1776 == target->entryIndex) {
            selectedEntry = lbl_806D1776;
            priority = 7;
        }
    } else if ((signed char)g_bgmStateId == 0x6E) {
        if (lbl_806D177C == -1 && lbl_806D1775 == kart->entryIndex) {
            selectedEntry = target->entryIndex;
            priority = 11;
        }
    } else if ((signed char)g_bgmStateId == 0x6F) {
        if (lbl_806D1776 == -1 && lbl_806D1775 == kart->entryIndex) {
            priority = 11;
            selectedEntry = target->entryIndex;
        }
    }
    if (priority != -1) {
        voice = SpriteVoice_Select(g_raceEntryArray[selectedEntry].character,
                                   g_raceEntryArray[selectedEntry].id);
        SpriteVoice_Push(voice, priority, 1, 1);
        if ((g_voiceTickCounter & 1) == 0) {
            SpriteVoice_Push(0x1CB, priority, 1, 1);
        } else {
            SpriteVoice_Push(0x1CC, priority, 1, 1);
        }
        g_raceEntryArray[kart->entryIndex].state = 0;
        g_raceEntryArray[kart->entryIndex].voiceTarget = 0;
        g_bgmStateId = 0;
    }
    return 1;
}
