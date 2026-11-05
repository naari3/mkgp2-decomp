#include "game/RaceVoiceGoalPrivate.h"

/* Mid-race checkpoint trigger: rank to watch and whether a trigger line must
 * also be crossed. */
typedef struct MidRaceTrigger {
    signed char rank;
    unsigned char useLine;
} MidRaceTrigger;

extern int lbl_806D176C;
extern int g_currentVoiceSubId;
extern int g_voiceMidRaceCheckpoint;
extern int g_lastPlayerIndexCrossingCheckpoint;
extern MidRaceTrigger lbl_80498158[5][2];
extern float lbl_80498058[64];
extern const float lbl_806D9818;
extern void *g_raceRankingPathObject;

extern int fn_801B0F20(short id, short arg);
extern short fn_801B0CE4(int character, int id, short variant);
extern float fn_801B0D80(void);
extern SpriteVoiceRaceEntry *fn_801A1D40(int rank);
extern int Race_CompareKartProgress(void *path, void *a, void *b);

#define ME g_raceEntryArray[g_taMinLapPlayerIndex]
#define PUSH(id) fn_801B0F20((id), 4)
#define ME_VOICE() fn_801B0CE4(ME.character, -1, 1)
#define KART_VOICE(e) fn_801B0CE4((e)->character, (e)->id, 1)
#define COMPARE(a, b) Race_CompareKartProgress(g_raceRankingPathObject, RACE_VOICE_PROGRESS(a), RACE_VOICE_PROGRESS(b))
#define MID_LINE() (lbl_80498058 + ((g_cupId - 1) * 8 + g_longRoundFlag * 4))

static inline short RankVoice(int rank) {
    short voice;
    if (rank >= 0 && rank <= 5) {
        voice = rank + 0x113;
    } else {
        voice = 0x113;
    }
    return voice;
}

void fn_801A9D58(void) {
    SpriteVoiceRaceEntry *byRank[8];
    int first;
    int second;
    int count;
    int i;
    int j;
    int third;
    int gap;
    SpriteVoiceRaceEntry *other;
    MidRaceTrigger *trigger;

    if (lbl_806D176C < 2 && g_currentVoiceSubId == -1 && IsRaceStarted() &&
        g_lastPlayerIndexCrossingCheckpoint != -1 && g_voiceMidRaceCheckpoint != -1) {
        if (g_gameMode == 0) {
            trigger = &lbl_80498158[g_voiceMidRaceCheckpoint][lbl_806D176C];
            if (trigger->rank == g_raceEntryArray[g_lastPlayerIndexCrossingCheckpoint].f32 &&
                (!trigger->useLine || fn_801A1BD0(MID_LINE(), &g_raceEntryArray[g_lastPlayerIndexCrossingCheckpoint]))) {
                if (fn_801B0D80() < lbl_806D9818) {
                    switch (ME.player) {
                    case 0:
                        other = fn_801A1D40(1);
                        if (other) {
                            if (other->distance >= 7) {
                                switch (g_voiceTickCounter % 3) {
                                case 0:
                                    PUSH(0x1B5);
                                    PUSH(ME_VOICE());
                                    PUSH(0x1B6);
                                    break;
                                case 1:
                                    PUSH(0x1B5);
                                    PUSH(ME_VOICE());
                                    PUSH(0x1B7);
                                    PUSH(fn_801B0CE4(other->character, -1, 1));
                                    break;
                                default:
                                    PUSH(ME_VOICE());
                                    PUSH(0x1A1);
                                    break;
                                }
                            } else {
                                gap = 1000;
                                if (fn_801A1D40(1)) gap = fn_801A1D40(1)->distance;
                                if (fn_801A1D40(2)) gap += fn_801A1D40(2)->distance;
                                if (gap <= 0) {
                                    switch (g_voiceTickCounter % 2) {
                                    case 0:
                                            PUSH(ME_VOICE());
                                            PUSH(RankVoice(ME.player));
                                            PUSH(0x1A0);
                                        break;
                                    default:
                                            PUSH(0x1B2);
                                            PUSH(ME_VOICE());
                                            PUSH(0x1AC);
                                        break;
                                    }
                                }
                            }
                        }
                        break;
                    case 1:
                    case 2:
                        other = fn_801A1D40(ME.player + 1);
                        if (other) {
                            if (ME.distance >= 7 && other->distance >= 7) {
                                PUSH(ME_VOICE());
                                PUSH(RankVoice(ME.player));
                                if (g_voiceTickCounter % 2 == 0) {
                                    PUSH(0x1B3);
                                } else {
                                    PUSH(0x1B4);
                                }
                            } else {
                                gap = 1000;
                                if (fn_801A1D40(1)) gap = fn_801A1D40(1)->distance;
                                if (fn_801A1D40(2)) gap += fn_801A1D40(2)->distance;
                                if (gap <= 0) {
                                    switch (g_voiceTickCounter % 2) {
                                    case 0:
                                            PUSH(ME_VOICE());
                                            PUSH(RankVoice(ME.player));
                                            PUSH(0x1A0);
                                        break;
                                    default:
                                            PUSH(0x1B2);
                                            PUSH(ME_VOICE());
                                            PUSH(0x1AC);
                                        break;
                                    }
                                }
                            }
                        }
                        break;
                    case 3:
                    case 4:
                        other = fn_801A1D40(ME.player + 1);
                        if (other) {
                            if (ME.distance >= 7 && other->distance >= 7) {
                                PUSH(ME_VOICE());
                                PUSH(RankVoice(ME.player));
                                if (g_voiceTickCounter % 2 == 0) {
                                    PUSH(0x1A3);
                                } else {
                                    PUSH(0x1AA);
                                }
                            } else if (ME.distance <= 0 || other->distance <= 0) {
                                switch (g_voiceTickCounter % 2) {
                                case 0:
                                        PUSH(ME_VOICE());
                                        PUSH(RankVoice(ME.player));
                                        PUSH(0x1A0);
                                    break;
                                default:
                                        PUSH(0x1B1);
                                        PUSH(ME_VOICE());
                                        PUSH(0x1AC);
                                    break;
                                }
                            }
                        }
                        break;
                    default:
                        if (ME.distance >= 7) {
                            PUSH(ME_VOICE());
                            PUSH(RankVoice(ME.player));
                            if (g_voiceTickCounter % 2 == 0) {
                                PUSH(0x1A6);
                            } else {
                                PUSH(0x1A5);
                            }
                        } else if (ME.distance <= 0) {
                            switch (g_voiceTickCounter % 2) {
                            case 0:
                                    PUSH(ME_VOICE());
                                    PUSH(RankVoice(ME.player));
                                    PUSH(0x1A0);
                                break;
                            default:
                                    PUSH(0x1B1);
                                    PUSH(ME_VOICE());
                                    PUSH(0x1AC);
                                break;
                            }
                        }
                        break;
                    }
                }
                lbl_806D176C++;
            }
        } else {
            trigger = &lbl_80498158[g_voiceMidRaceCheckpoint][lbl_806D176C];
            count = 0;
            for (i = 0; i < 8; i++) {
                byRank[i] = fn_801A1D40(i);
                if (byRank[i] && byRank[i]->active) count++;
            }
            if (trigger->rank != g_raceEntryArray[g_lastPlayerIndexCrossingCheckpoint].f32) return;
            if (trigger->useLine && !fn_801A1BD0(MID_LINE(), &g_raceEntryArray[g_lastPlayerIndexCrossingCheckpoint])) return;

            if (count == 2) {
                first = -1;
                second = -1;
                for (j = 0; j < 8; j++) {
                    if (byRank[j] && byRank[j]->active) {
                        if (first == -1) first = j;
                        else second = j;
                    }
                }
                gap = COMPARE(byRank[first], byRank[second]);
                if (gap >= 7) {
                    if (g_voiceTickCounter % 3 == 0) {
                        PUSH(KART_VOICE(byRank[second]));
                        PUSH(0x1A5);
                    } else if (g_voiceTickCounter % 3 == 1) {
                        PUSH(KART_VOICE(byRank[second]));
                        PUSH(0x1A6);
                    } else {
                        PUSH(0x1A7);
                    }
                    lbl_806D176C++;
                    return;
                }
                if (gap <= 0) {
                    PUSH(KART_VOICE(byRank[first]));
                    PUSH(KART_VOICE(byRank[second]));
                    if (g_voiceTickCounter % 2 == 0) {
                        PUSH(0x1A8);
                    } else {
                        PUSH(0x1A9);
                    }
                    lbl_806D176C++;
                    return;
                }
            }
            if (count == 3) {
                first = -1;
                second = -1;
                third = -1;
                for (j = 0; j < 8; j++) {
                    if (byRank[j] && byRank[j]->active) {
                        if (first == -1) first = j;
                        else if (second == -1) second = j;
                        else third = j;
                    }
                }
                if (COMPARE(byRank[first], byRank[third]) <= 0) {
                    PUSH(KART_VOICE(byRank[first]));
                    PUSH(KART_VOICE(byRank[second]));
                    PUSH(KART_VOICE(byRank[third]));
                    if (g_voiceTickCounter % 2 == 0) {
                        PUSH(0x19D);
                    } else {
                        PUSH(0x1A0);
                    }
                    lbl_806D176C++;
                    return;
                }
                if (COMPARE(byRank[second], byRank[third]) >= 7) {
                    PUSH(KART_VOICE(byRank[third]));
                    if (g_voiceTickCounter % 2 == 0) {
                        PUSH(0x1A5);
                    } else {
                        PUSH(0x1A6);
                    }
                    lbl_806D176C++;
                    return;
                }
                if (COMPARE(byRank[first], byRank[second]) >= 7 && COMPARE(byRank[second], byRank[third]) <= 0) {
                    PUSH(KART_VOICE(byRank[second]));
                    PUSH(KART_VOICE(byRank[third]));
                    if (g_voiceTickCounter % 2 == 0) {
                        PUSH(0x1A8);
                    } else {
                        PUSH(0x1A0);
                    }
                    lbl_806D176C++;
                    return;
                }
                if (COMPARE(byRank[first], byRank[second]) >= 7 && COMPARE(byRank[second], byRank[third]) >= 7) {
                    if (g_voiceTickCounter % 3 == 0) {
                        PUSH(KART_VOICE(byRank[third]));
                        PUSH(0x1A3);
                    } else if (g_voiceTickCounter % 3 == 1) {
                        PUSH(KART_VOICE(byRank[third]));
                        PUSH(0x1AA);
                    } else {
                        PUSH(0x1A7);
                    }
                    lbl_806D176C++;
                    return;
                }
            }
            if (count == 4) {
                if (byRank[1]->distance + byRank[2]->distance + byRank[3]->distance <= 0) {
                    if (g_voiceTickCounter % 2 == 0) {
                        PUSH(0x1AB);
                        PUSH(KART_VOICE(byRank[3]));
                        PUSH(0x1AC);
                    } else {
                        PUSH(0x1AD);
                        PUSH(KART_VOICE(byRank[3]));
                        PUSH(0x1AE);
                    }
                    lbl_806D176C++;
                    return;
                }
                if (byRank[3]->distance <= 0) {
                    PUSH(KART_VOICE(byRank[3]));
                    if (g_voiceTickCounter % 2 == 0) {
                        PUSH(0x1A5);
                    } else {
                        PUSH(0x1A6);
                    }
                    lbl_806D176C++;
                    return;
                }
                if (byRank[2]->distance >= 7 && byRank[3]->distance <= 0) {
                    PUSH(KART_VOICE(byRank[2]));
                    PUSH(KART_VOICE(byRank[3]));
                    if (g_voiceTickCounter % 2 == 0) {
                        PUSH(0x1AF);
                    } else {
                        PUSH(0x1B0);
                    }
                    lbl_806D176C++;
                    return;
                }
                if (byRank[1]->distance >= 7 && byRank[2]->distance <= 0 && byRank[3]->distance >= 7) {
                    PUSH(KART_VOICE(byRank[1]));
                    PUSH(KART_VOICE(byRank[2]));
                    if (g_voiceTickCounter % 2 == 0) {
                        PUSH(0x1A8);
                    } else {
                        PUSH(0x1A0);
                    }
                    lbl_806D176C++;
                    return;
                }
                if (byRank[1]->distance >= 7 && byRank[2]->distance > 0 && byRank[3]->distance >= 7) {
                    if (g_voiceTickCounter % 3 == 0) {
                        PUSH(KART_VOICE(byRank[3]));
                        PUSH(0x1A3);
                    } else if (g_voiceTickCounter % 3 == 1) {
                        PUSH(KART_VOICE(byRank[3]));
                        PUSH(0x1AA);
                    } else {
                        PUSH(0x1A7);
                    }
                    lbl_806D176C++;
                    return;
                }
            }
            lbl_806D176C++;
        }
    }
}
