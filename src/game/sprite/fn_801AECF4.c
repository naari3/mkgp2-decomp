#include "game/SpriteVoiceGoalPrivate.h"
extern int g_taMinLapPlayerIndex;
extern int g_cupId, g_longRoundFlag, g_reverseRoundFlag;
extern unsigned char fn_801A1BD0(float *, SpriteVoiceRaceEntry *);
extern unsigned char lbl_806D178D, lbl_806D17B4;
extern int g_lastPlayerCurrentCheckpoint, g_goalTriggerCheckpoint;
extern int g_lastPlayerIndexCrossingCheckpoint, g_currentVoiceSubId;
extern int g_goalFanfareVariant, g_goalFanfarePlayerIndex, lbl_806D17BC, lbl_806D17C0;
extern unsigned int lbl_806D17E0, lbl_806D17E4, lbl_806D17E8, lbl_806D17EC;
extern SpriteVoiceRaceEntry *lbl_80679260[8];
extern unsigned char VoiceQueue_Push(short, short, unsigned char, unsigned char);
extern void *g_raceRankingPathObject;
extern int Race_CompareKartProgress(void *, void *, void *);

extern int g_ccClass;
#define PUSH(id) VoiceQueue_Push((id), -1, 0, 1)
#define SELECT(entry) Goal_Select(tables, (entry)->character, (entry)->id)
static inline short Goal_Select(short *tables, int character, int id) {
    short *normal = tables + 14;
    short *special = tables + 94;
    short voice = 0x43;
    if (character > -1 && character < 13) {
        if (g_gameMode == 2) {
            if (id >= 0 && id <= 3) voice = special[character + id * 13];
            else voice = normal[character];
        } else voice = normal[character];
    }
    return voice;
}
static inline float *Goal_Line(float *lines) {
    return &lines[g_ccClass * 128 + ((g_cupId - 1) * 16 + (g_longRoundFlag * 8 + g_reverseRoundFlag * 4))];
}
int fn_801AECF4(void) {
    short *tables = lbl_80496C38;
    int rank;
    if (lbl_806D178D) return 1;
    if (g_lastPlayerCurrentCheckpoint != g_goalTriggerCheckpoint) return 0;
    if (!fn_801A1BD0(Goal_Line((float *)(tables + 0x4C6)),         &g_raceEntryArray[g_lastPlayerIndexCrossingCheckpoint])) return 0;
    lbl_806D178D = 1;
    g_currentVoiceSubId = -1;
    g_goalFanfareVariant = 0;
    lbl_806D17B4 = 0;
    g_goalFanfarePlayerIndex = g_taMinLapPlayerIndex;
    lbl_806D17BC = g_lastPlayerIndexCrossingCheckpoint;
    lbl_806D17C0 = g_raceEntryArray[g_taMinLapPlayerIndex].player;
    {
        OSTime time = OSGetTime();
        lbl_806D17E4 = (unsigned int)time;
        lbl_806D17E0 = (unsigned long long)time >> 32;
    }
    {
        OSTime time = OSGetTime();
        lbl_806D17EC = (unsigned int)time;
        lbl_806D17E8 = (unsigned long long)time >> 32;
    }
    for (rank = 0; rank < 8; rank++) lbl_80679260[rank] = VoiceGoal_Find(rank);
    rank = g_raceEntryArray[g_taMinLapPlayerIndex].player;
    switch (rank) {
        case 0: {
            int d1 = lbl_80679260[1]->distance;
            if (d1 >= 7) {
                {
                    unsigned int variant = g_voiceTickCounter % 3;
                    if (variant == 0) {
                        PUSH(0x20D);
                        PUSH(SELECT(&g_raceEntryArray[g_taMinLapPlayerIndex]));
                        PUSH(0x20E);
                    }
                    else if (variant == 1) {
                        PUSH(SELECT(&g_raceEntryArray[g_taMinLapPlayerIndex]));
                        PUSH(0x20F);
                        PUSH(0x210);
                    }
                    else {
                        PUSH(SELECT(&g_raceEntryArray[g_taMinLapPlayerIndex]));
                        PUSH(0x20F);
                        PUSH(0x211);
                    }
                }
            }
            else {
                int sum = d1 + lbl_80679260[2]->distance;
                if (sum + lbl_80679260[3]->distance <= 2) {
                    if ((g_voiceTickCounter & 1) == 0) {
                        PUSH(0x212);
                        PUSH(0x213);
                    }
                    else {
                        PUSH(0x212);
                        PUSH(0x217);
                    }
                }
                else if (d1 <= 0 || sum <= 0) {
                    PUSH(0x214);
                    {
                        unsigned int variant = g_voiceTickCounter % 3;
                        if (variant == 0) {
                            PUSH(0x215);
                        }
                        else if (variant == 1) {
                            PUSH(0x216);
                            PUSH(0x217);
                        }
                        else {
                            PUSH(0x216);
                            PUSH(0x218);
                        }
                    }
                }
                else if (d1 < 3) {
                    PUSH(0x20D);
                    {
                        unsigned int variant = g_voiceTickCounter % 3;
                        if (variant == 0) {
                            PUSH(SELECT(&g_raceEntryArray[g_taMinLapPlayerIndex]));
                            PUSH(0x219);
                        }
                        else if (variant == 1) {
                            PUSH(SELECT(&g_raceEntryArray[g_taMinLapPlayerIndex]));
                            PUSH(0x21A);
                        }
                        else {
                            PUSH(SELECT(lbl_80679260[1]));
                            PUSH(0x21B);
                        }
                    }
                }
                else PUSH(0x20D);
            }
            break;
        }
        case 1: case 2: case 3: {
            int d1 = lbl_80679260[1]->distance;
            int sum = d1 + lbl_80679260[2]->distance;
            if (sum + lbl_80679260[3]->distance <= 2) {
                if ((g_voiceTickCounter & 1) == 0) {
                    PUSH(0x212);
                    PUSH(0x213);
                }
                else {
                    PUSH(0x212);
                    PUSH(0x217);
                }
                break;
            }
            if (rank != 3 && (d1 <= 0 || sum <= 0)) {
                PUSH(0x214);
                {
                    unsigned int variant = g_voiceTickCounter % 3;
                    if (variant == 0) {
                        PUSH(0x215);
                    }
                    else if (variant == 1) {
                        PUSH(0x216);
                        PUSH(0x217);
                    }
                    else {
                        PUSH(0x216);
                        PUSH(0x218);
                    }
                }
                break;
            }
        }
        default: {
            int diff = Race_CompareKartProgress(g_raceRankingPathObject,             VoiceGoal_Kart(lbl_80679260[0])->progress, VoiceGoal_Kart(&g_raceEntryArray[g_taMinLapPlayerIndex])->progress);
            if (diff < 3) {
                PUSH(0x20D);
                PUSH(SELECT(&g_raceEntryArray[g_taMinLapPlayerIndex]));
                {
                    unsigned int variant = g_voiceTickCounter % 3;
                    if (variant == 0) {
                        PUSH(0x21C);
                    }
                    else if (variant == 1) {
                        PUSH(0x21D);
                    }
                    else {
                        PUSH(0x21E);
                    }
                }
            }
            else if (diff >= 3) {
                PUSH(0x21F);
                PUSH(SELECT(&g_raceEntryArray[g_taMinLapPlayerIndex]));
                {
                    unsigned int variant = g_voiceTickCounter % 3;
                    if (variant == 0) {
                        PUSH(0x220);
                    }
                    else if (variant == 1) {
                        PUSH(0x221);
                    }
                    else {
                        PUSH(0x222);
                    }
                }
            }
            else PUSH(0x21F);
            break;
        }
    }
    return 0;
}
