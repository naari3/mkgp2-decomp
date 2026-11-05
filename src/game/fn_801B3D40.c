#include "game/RaceVoiceEventsPrivate.h"

extern unsigned char g_voiceSystemInitDone;
extern unsigned char g_goalFanfareTriggered;
extern int g_currentRaceEventPlayer[2];
extern unsigned int lbl_806D17C8, lbl_806D17CC;
extern unsigned int lbl_806D17D0, lbl_806D17D4;
extern void *SyncSlot_GetHostSend(void);

static inline short SelectPlayerVoice(int player) {
    if (player >= 0 && player <= 5) return player + 0x113;
    return 0x113;
}

int fn_801B3D40(int kart) {
    OSTime now;
    int player;
    if (!g_voiceSystemInitDone) return 0;
    if (kart < 0 || kart >= 8) return 0;
    if (g_goalFanfareTriggered) {
        SpriteVoice_Push(SpriteVoice_Select(g_raceEntryArray[kart].character, g_raceEntryArray[kart].id), -1, 0, 1);
        SpriteVoice_Push(0x245, -1, 0, 1);
        return 1;
    }
    g_currentRaceEventPlayer[0] = kart;
    now = OSGetTime();
    lbl_806D17CC = (unsigned int)now;
    lbl_806D17C8 = (unsigned long long)now >> 32;
    now = OSGetTime();
    lbl_806D17D4 = (unsigned int)now;
    lbl_806D17D0 = (unsigned long long)now >> 32;
    if (g_gameMode == 2 && SyncSlot_GetHostSend() == 0) return 1;
    player = g_raceEntryArray[kart].player;
    switch (player) {
    case 0:
        SpriteVoice_Push(0x246, -1, 0, 1);
        SpriteVoice_Push(SpriteVoice_Select(g_raceEntryArray[kart].character, g_raceEntryArray[kart].id), -1, 0, 1);
        SpriteVoice_Push(0x247, -1, 0, 1);
        break;
    case 1:
        SpriteVoice_Push(SpriteVoice_Select(g_raceEntryArray[kart].character, g_raceEntryArray[kart].id), -1, 0, 1);
        SpriteVoice_Push(0x248, -1, 0, 1);
        break;
    default:
        SpriteVoice_Push(SpriteVoice_Select(g_raceEntryArray[kart].character, g_raceEntryArray[kart].id), -1, 0, 1);
        SpriteVoice_Push(0x249, -1, 0, 1);
        SpriteVoice_Push(SelectPlayerVoice(player), -1, 0, 1);
        SpriteVoice_Push(0x24A, -1, 0, 1);
        break;
    }
    return 1;
}
