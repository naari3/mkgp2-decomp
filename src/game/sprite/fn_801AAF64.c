#include "game/RaceVoiceGoalPrivate.h"

extern unsigned char lbl_806D1768;
extern int g_currentVoiceSubId;
extern int g_voiceFinalLapCheckpoint;
extern int g_lastPlayerIndexCrossingCheckpoint;

#define PUSH(id) RaceVoice_PushDirect((id), 4, 0)
#define KART_VOICE(e) SpriteVoice_Select((e)->character, (e)->id)

static inline short SelectCharacter(int character) {
    short *table = lbl_80496C54;
    short voice = 0x43;
    if (character > -1 && character < 13) {
        if (g_gameMode == 2) voice = table[character];
        else voice = table[character];
    }
    return voice;
}

void fn_801AAF64(void) {
    SpriteVoiceRaceEntry *byRank[8];
    int first;
    int second;
    int i;
    int gap;
    SpriteVoiceRaceEntry *entry;

    if (!lbl_806D1768 && g_currentVoiceSubId == -1 && IsRaceStarted() && g_voiceFinalLapCheckpoint != -1) {
        if (g_gameMode == 0) {
            if (g_voiceFinalLapCheckpoint == g_raceEntryArray[g_lastPlayerIndexCrossingCheckpoint].f32) {
                PUSH(0x19B);
                PUSH(SelectCharacter(g_raceEntryArray[g_taMinLapPlayerIndex].character));
                switch (g_raceEntryArray[g_taMinLapPlayerIndex].player) {
                case 0:
                    entry = RaceVoice_FindByRank(1);
                    if (entry) {
                        if (entry->distance <= 0) {
                            PUSH(0x19C);
                        } else if (entry->distance >= 7) {
                            PUSH(0x1A4);
                        } else {
                            PUSH(0x1A1);
                        }
                    }
                    break;
                case 1:
                    if (g_raceEntryArray[g_taMinLapPlayerIndex].distance <= 0) {
                        PUSH(0x19C);
                    } else {
                        PUSH(0x1C3);
                    }
                    break;
                default:
                    PUSH(0x1A3);
                    break;
                }
                lbl_806D1768 = 1;
            }
        } else {
            for (i = 0; i < 8; i++) {
                byRank[i] = RaceVoice_FindByRank(i);
            }
            if (byRank[0]->f32 == g_voiceFinalLapCheckpoint) {
                if (byRank[0]->active && byRank[1]->active && byRank[2]->active &&
                    byRank[1]->distance + byRank[2]->distance <= 0) {
                    PUSH(0x19B);
                    PUSH(KART_VOICE(byRank[0]));
                    PUSH(KART_VOICE(byRank[1]));
                    PUSH(KART_VOICE(byRank[2]));
                    PUSH(0x19E);
                    lbl_806D1768 = 1;
                } else if (byRank[0]->active && byRank[1]->active && byRank[1]->distance <= 0) {
                    PUSH(0x19B);
                    PUSH(KART_VOICE(byRank[0]));
                    PUSH(KART_VOICE(byRank[1]));
                    PUSH(0x19C);
                    lbl_806D1768 = 1;
                } else if (byRank[0]->active && byRank[1]->active && byRank[2]->active && byRank[3]->active &&
                           byRank[1]->distance + byRank[2]->distance + byRank[3]->distance < 2) {
                    PUSH(0x19F);
                    lbl_806D1768 = 1;
                } else {
                    gap = -1;
                    if (byRank[1]->active && byRank[2]->active) {
                        gap = byRank[2]->distance;
                        first = 1;
                        second = 2;
                    } else if (byRank[2]->active && byRank[3]->active) {
                        gap = byRank[3]->distance;
                        first = 2;
                        second = 3;
                    } else if (byRank[1]->active && byRank[3]->active) {
                        gap = byRank[2]->distance + byRank[3]->distance;
                        first = 1;
                        second = 3;
                    }
                    if (gap != -1 && gap <= 0) {
                        PUSH(0x19B);
                        PUSH(KART_VOICE(byRank[first]));
                        PUSH(KART_VOICE(byRank[second]));
                        PUSH(0x1A0);
                        lbl_806D1768 = 1;
                    } else if ((byRank[0]->active || byRank[1]->active) && byRank[1]->distance > 0 && byRank[1]->distance <= 3) {
                        PUSH(0x19B);
                        PUSH(0x1B5);
                        PUSH(KART_VOICE(byRank[0]));
                        PUSH(0x1B7);
                        PUSH(KART_VOICE(byRank[1]));
                        lbl_806D1768 = 1;
                    } else if (byRank[0]->active && byRank[1]->distance >= 7) {
                        PUSH(0x19B);
                        PUSH(KART_VOICE(byRank[0]));
                        PUSH(0x1A4);
                        lbl_806D1768 = 1;
                    } else if (byRank[0]->active) {
                        PUSH(0x19B);
                        PUSH(KART_VOICE(byRank[0]));
                        PUSH(0x1A1);
                        lbl_806D1768 = 1;
                    } else {
                        PUSH(0x19B);
                        PUSH(0x1A2);
                        lbl_806D1768 = 1;
                    }
                }
            }
        }
    }
}
