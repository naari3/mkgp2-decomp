#include "game/RaceVoiceEventsPrivate.h"
extern unsigned char lbl_806D175E;
extern unsigned int lbl_806D17A0, lbl_806D17A4;
extern const float lbl_806D9804, lbl_806D9814;
extern int g_taMinLapPlayerIndex;
extern unsigned int g_voiceTickCounter;
extern unsigned char IsRaceStarted(void);
extern int KartItem_AdvanceAnim3c(void *);

#define RACE_ENTRIES g_raceEntryArray
#define ITEM_STATE(index) KartItem_AdvanceAnim3c(RACE_ENTRIES[index].item)
static inline short SelectCharacter(int character) {
    short *table = lbl_80496C54;
    short voice = 0x43;
    if (character > -1 && character < 13) {
        if (g_gameMode == 2) voice = table[character];
        else voice = table[character];
    }
    return voice;
}
void fn_801ACC18(void) {
    OSTime now = OSGetTime();
    int count, finished, i;
    if (!lbl_806D175E) {
        if (!IsRaceStarted()) {
            lbl_806D17A4 = (unsigned int)now;
            lbl_806D17A0 = (unsigned long long)now >> 32;
        } else {
            if ((float)OSTicksToMilliseconds(now - (OSTime)(((unsigned long long)lbl_806D17A0 << 32) | lbl_806D17A4)) / lbl_806D9804 < lbl_806D9814) return;
            if (g_gameMode == 0) {
                if (ITEM_STATE(g_taMinLapPlayerIndex) == 4) {
                    SpriteVoice_Push(SelectCharacter(RACE_ENTRIES[g_taMinLapPlayerIndex].character), 0, 0, 0);
                    switch (g_voiceTickCounter % 3) {
                    case 0: SpriteVoice_Push(0x190, 0, 0, 0); break;
                    case 1: SpriteVoice_Push(0x191, 0, 0, 0); break;
                    default: SpriteVoice_Push(0x192, 0, 0, 0); break;
                    }
                    lbl_806D175E = 1;
                } else {
                    switch (g_voiceTickCounter % 3) {
                    case 0:
                        SpriteVoice_Push(SelectCharacter(RACE_ENTRIES[g_taMinLapPlayerIndex].character), 0, 0, 0);
                        SpriteVoice_Push(0x193, 0, 0, 0); break;
                    case 1:
                        SpriteVoice_Push(SelectCharacter(RACE_ENTRIES[g_taMinLapPlayerIndex].character), 0, 0, 0);
                        SpriteVoice_Push(0x194, 0, 0, 0); break;
                    default: SpriteVoice_Push(0x195, 0, 0, 0); break;
                    }
                    lbl_806D175E = 1;
                }
            } else if (g_gameMode == 2) {
                count = 0;
                finished = 0;
                for (i = 0; i < 8; i++) {
                    if (RACE_ENTRIES[i].participant) {
                        count++;
                        if (ITEM_STATE(i) == 4) finished++;
                    }
                }
                if (finished == 1 || finished == 2) {
                    for (i = 0; i < 8; i++) {
                        if (RACE_ENTRIES[i].participant && ITEM_STATE(i) == 4)
                            SpriteVoice_Push(SpriteVoice_Select(RACE_ENTRIES[i].character, RACE_ENTRIES[i].id), 0, 0, 0);
                    }
                    switch (g_voiceTickCounter % 3) {
                    case 0: SpriteVoice_Push(0x190, 0, 0, 0); break;
                    case 1: SpriteVoice_Push(0x191, 0, 0, 0); break;
                    default: SpriteVoice_Push(0x192, 0, 0, 0); break;
                    }
                } else if (count == 4 && finished == 3) {
                    for (i = 0; i < 8; i++) {
                        if (RACE_ENTRIES[i].participant && ITEM_STATE(i) != 4)
                            SpriteVoice_Push(SpriteVoice_Select(RACE_ENTRIES[i].character, RACE_ENTRIES[i].id), 0, 0, 0);
                    }
                    SpriteVoice_Push(0x196, 0, 0, 0);
                } else if (count == 4 && finished == 4) {
                    SpriteVoice_Push(0x197, 0, 0, 0);
                } else {
                    SpriteVoice_Push(0x195, 0, 0, 0);
                }
                lbl_806D175E = 1;
            }
        }
    }
}
