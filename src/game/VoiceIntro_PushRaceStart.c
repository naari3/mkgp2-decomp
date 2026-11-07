/* VoiceIntro_PushRaceStart: queues the race-start jingles and the cup call. */
#include "game/RaceVoiceEventsPrivate.h"

extern int g_cupId, g_longRoundFlag;
extern unsigned char *SyncSlot_GetHostSend(void);
extern void VoiceIntro_PushForRaceMode(void);
extern void fn_801AF850(void);

void VoiceIntro_PushRaceStart(void) {
    int cup;
    int longRound;

    if (g_gameMode == 2 && SyncSlot_GetHostSend() == 0) {
        return;
    }
    cup = g_cupId;
    longRound = g_longRoundFlag;
    SpriteVoice_Push(0x280, -1, 0, 0);
    SpriteVoice_Push(0x189, -1, 0, 0);
    SpriteVoice_Push(0x280, -1, 0, 0);
    SpriteVoice_Push(longRound + (cup - 1) * 2, -1, 0, 1);
    if (g_gameMode == 0) {
        VoiceIntro_PushForRaceMode();
    }
    if (g_gameMode == 2) {
        fn_801AF850();
    }
}
