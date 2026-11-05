#include "game/RaceVoiceGoalPrivate.h"

extern unsigned char lbl_806D175F;
extern int lbl_806D1764;

#define GOAL_LINE() GetGoalLine(tables->goalLines)

static inline float *GetGoalLine(float *lines) {
    return &lines[(g_cupId - 1) * 16 + g_longRoundFlag * 8 + g_reverseRoundFlag * 4];
}

static inline short SelectCharacter(RaceVoiceTables *tables, int character) {
    short *table = tables->normal;
    short voice = 0x43;
    if (character > -1 && character < 13) {
        if (g_gameMode == 2) voice = table[character];
        else voice = table[character];
    }
    return voice;
}

static inline short SelectKartVoice(RaceVoiceTables *tables, int character, int id) {
    short *normal = tables->normal;
    short *special = tables->special;
    short voice = 0x43;
    if (character > -1 && character < 13) {
        if (g_gameMode == 2) {
            if (id >= 0 && id <= 3) voice = special[character + id * 13];
            else voice = normal[character];
        } else voice = normal[character];
    }
    return voice;
}

void fn_801AC208(void) {
    RaceVoiceTables *tables = &lbl_80496C38;
    int count;
    int i;

    if (!lbl_806D175F && IsRaceStarted()) {
        if (g_gameMode == 0) {
            if (fn_801A1BD0(GOAL_LINE(), &g_raceEntryArray[g_taMinLapPlayerIndex])) {
                if (!g_raceEntryArray[g_taMinLapPlayerIndex].pad1[0]) {
                    switch (g_voiceTickCounter % 3) {
                    case 0:
                        RaceVoice_Push(SelectCharacter(tables, g_raceEntryArray[g_taMinLapPlayerIndex].character), 1, 0, 0);
                        RaceVoice_Push(0x198, 1, 0, 0);
                        break;
                    case 1:
                        RaceVoice_Push(SelectCharacter(tables, g_raceEntryArray[g_taMinLapPlayerIndex].character), 1, 0, 0);
                        RaceVoice_Push(0x199, 1, 0, 0);
                        break;
                    default:
                        RaceVoice_Push(0x19A, 1, 0, 0);
                        break;
                    }
                }
                lbl_806D175F = 1;
            }
        } else {
            count = 0;
            for (i = 0; i < 8; i++) {
                if (g_raceEntryArray[i].active) {
                    count++;
                    if (fn_801A1BD0(GOAL_LINE(), &g_raceEntryArray[i]) && !g_raceEntryArray[i].pad1[0]) {
                        switch (g_voiceTickCounter % 3) {
                        case 0:
                            RaceVoice_Push(SelectKartVoice(tables, g_raceEntryArray[i].character, g_raceEntryArray[i].id), 1, 0, 0);
                            RaceVoice_Push(0x198, 1, 0, 0);
                            break;
                        case 1:
                            RaceVoice_Push(SelectKartVoice(tables, g_raceEntryArray[i].character, g_raceEntryArray[i].id), 1, 0, 0);
                            RaceVoice_Push(0x199, 1, 0, 0);
                            break;
                        default:
                            RaceVoice_Push(0x19A, 1, 0, 0);
                            break;
                        }
                        lbl_806D175F = 1;
                        break;
                    }
                }
            }
            if (count == lbl_806D1764) lbl_806D175F = 1;
        }
    }
}
