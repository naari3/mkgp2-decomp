/*
 * Operator play statistics accumulated per race, 0x8008CB3C..0x8008D87C.
 */

#define PLAYSTATS_MAX 99999999u
#define PLAYSTATS_MAX6 999999u

typedef struct TaCourseStats {
    unsigned int plays;
    unsigned int best;
} TaCourseStats;

typedef struct PlayStatsRace {
    unsigned char pad00[0x14];
    unsigned int wins; /* 0x14 */
    unsigned int playFrames; /* 0x18 */
    unsigned char pad1C[0x2C - 0x1C];
    unsigned int gpByCc[3]; /* 0x2C */
    unsigned int mode2ByCc[3]; /* 0x38 */
    unsigned int mode1Cc1; /* 0x44 */
    unsigned int mode1Cc2; /* 0x48 */
    unsigned char pad4C[4];
    unsigned int gpFrames; /* 0x50 */
    unsigned char pad54[0x6C - 0x54];
    unsigned int mode2Frames; /* 0x6C */
    unsigned int vsPeers2; /* 0x70 */
    unsigned int vsPeers3; /* 0x74 */
    unsigned int vsPeers4; /* 0x78 */
    unsigned char pad7C[4];
    unsigned int vsPlays[8][4]; /* 0x80 */
    unsigned int mode1Frames; /* 0x100 */
    TaCourseStats ta[8][4]; /* 0x104 */
    unsigned int rankByChar[13][2]; /* 0x204 */
} PlayStatsRace;

extern PlayStatsRace lbl_805AC2E0;
extern unsigned char lbl_80598A60[];
extern unsigned char g_playerData[];
extern unsigned char lbl_806CF008; /* stats enabled */
extern int lbl_806CF00C; /* finish rank */
extern int lbl_806D11EC;
extern int g_gameMode;
extern int g_ccClass;
extern int g_cupId;
extern int g_characterId;
extern int g_reverseRoundFlag;
extern int g_longRoundFlag;
extern int g_localPcbRole;

int CountPeersWithRole(int role);

#define PLAYSTATS_INC(field)                       \
    do {                                           \
        if (++lbl_805AC2E0.field > PLAYSTATS_MAX) { \
            lbl_805AC2E0.field = PLAYSTATS_MAX;    \
        }                                          \
    } while (0)

#define PLAYSTATS_INC6(field)                       \
    do {                                            \
        if (++lbl_805AC2E0.field > PLAYSTATS_MAX6) { \
            lbl_805AC2E0.field = PLAYSTATS_MAX6;    \
        }                                           \
    } while (0)

void PlayStats_AccumulatePlayTime(unsigned char catchUp) {
    int n;
    int i;

    if ((int)lbl_80598A60[0x20] == 2 || g_playerData[0x19F] == 0) {
        lbl_806CF00C = 1;
        return;
    }
    n = 1;
    if (catchUp == 1) {
        n = lbl_806D11EC + 1;
    }
    for (i = 0; i < n; i++) {
        if (lbl_806CF008 != 0) {
            PLAYSTATS_INC(playFrames);
        }
        if (g_gameMode == 0) {
            if (lbl_806CF008 != 0) {
                PLAYSTATS_INC(gpFrames);
            }
        } else if (g_gameMode == 2) {
            if (lbl_806CF008 != 0) {
                PLAYSTATS_INC(mode2Frames);
            }
        } else if (g_gameMode == 1) {
            if (lbl_806CF008 != 0) {
                PLAYSTATS_INC(mode1Frames);
            }
        }
    }
}

void PlayStats_AccumulateCcClassPlay(void) {
    if (g_gameMode == 0) {
        if (lbl_806CF008 == 0) {
            return;
        }
        if (g_ccClass == 0) {
            PLAYSTATS_INC(gpByCc[0]);
        } else if (g_ccClass == 1) {
            PLAYSTATS_INC(gpByCc[1]);
        } else if (g_ccClass == 2) {
            PLAYSTATS_INC(gpByCc[2]);
        }
    } else if (g_gameMode == 1) {
        if (lbl_806CF008 == 0) {
            return;
        }
        if (g_ccClass == 1) {
            PLAYSTATS_INC(mode1Cc1);
        } else if (g_ccClass == 2) {
            PLAYSTATS_INC(mode1Cc2);
        }
    } else if (g_gameMode == 2) {
        if (lbl_806CF008 == 0) {
            return;
        }
        if (g_ccClass == 0) {
            PLAYSTATS_INC(mode2ByCc[0]);
        } else if (g_ccClass == 1) {
            PLAYSTATS_INC(mode2ByCc[1]);
        } else if (g_ccClass == 2) {
            PLAYSTATS_INC(mode2ByCc[2]);
        }
    }
}

void PlayStats_AccumulateFinishByRank(void) {
    int rank;

    if (lbl_806CF008 == 0) {
        return;
    }
    rank = lbl_806CF00C;
    if (rank == -1) {
        return;
    }
    if (rank == 1) {
        PLAYSTATS_INC6(wins);
    }
    if (g_characterId == 0) {
        PLAYSTATS_INC6(rankByChar[0][rank]);
    } else if (g_characterId == 1) {
        PLAYSTATS_INC6(rankByChar[1][rank]);
    } else if (g_characterId == 3) {
        PLAYSTATS_INC6(rankByChar[2][rank]);
    } else if (g_characterId == 4) {
        PLAYSTATS_INC6(rankByChar[3][rank]);
    } else if (g_characterId == 5) {
        PLAYSTATS_INC6(rankByChar[4][rank]);
    } else if (g_characterId == 2) {
        PLAYSTATS_INC6(rankByChar[5][rank]);
    } else if (g_characterId == 6) {
        PLAYSTATS_INC6(rankByChar[6][rank]);
    } else if (g_characterId == 7) {
        PLAYSTATS_INC6(rankByChar[7][rank]);
    } else if (g_characterId == 8) {
        PLAYSTATS_INC6(rankByChar[8][rank]);
    } else if (g_characterId == 9) {
        PLAYSTATS_INC6(rankByChar[9][rank]);
    } else if (g_characterId == 10) {
        PLAYSTATS_INC6(rankByChar[10][rank]);
    } else if (g_characterId == 12) {
        PLAYSTATS_INC6(rankByChar[11][rank]);
    } else if (g_characterId == 11) {
        PLAYSTATS_INC6(rankByChar[12][rank]);
    }
}

void PlayStats_IncTaBestRecord(void) {
    int course;

    if (lbl_806CF008 == 0) {
        return;
    }
    course = g_longRoundFlag + g_reverseRoundFlag * 2;
    if (g_cupId == 1) {
        PLAYSTATS_INC6(ta[0][course].best);
    } else if (g_cupId == 2) {
        PLAYSTATS_INC6(ta[1][course].best);
    } else if (g_cupId == 3) {
        PLAYSTATS_INC6(ta[2][course].best);
    } else if (g_cupId == 4) {
        PLAYSTATS_INC6(ta[3][course].best);
    } else if (g_cupId == 5) {
        PLAYSTATS_INC6(ta[4][course].best);
    } else if (g_cupId == 6) {
        PLAYSTATS_INC6(ta[5][course].best);
    } else if (g_cupId == 7) {
        PLAYSTATS_INC6(ta[6][course].best);
    } else if (g_cupId == 8) {
        PLAYSTATS_INC6(ta[7][course].best);
    }
}

void PlayStats_IncTaPlay(void) {
    int course;

    if (lbl_806CF008 == 0) {
        return;
    }
    course = g_longRoundFlag + g_reverseRoundFlag * 2;
    if (g_cupId == 1) {
        PLAYSTATS_INC6(ta[0][course].plays);
    } else if (g_cupId == 2) {
        PLAYSTATS_INC6(ta[1][course].plays);
    } else if (g_cupId == 3) {
        PLAYSTATS_INC6(ta[2][course].plays);
    } else if (g_cupId == 4) {
        PLAYSTATS_INC6(ta[3][course].plays);
    } else if (g_cupId == 5) {
        PLAYSTATS_INC6(ta[4][course].plays);
    } else if (g_cupId == 6) {
        PLAYSTATS_INC6(ta[5][course].plays);
    } else if (g_cupId == 7) {
        PLAYSTATS_INC6(ta[6][course].plays);
    } else if (g_cupId == 8) {
        PLAYSTATS_INC6(ta[7][course].plays);
    }
}

void PlayStats_IncVsPlay(void) {
    int course;

    if (lbl_806CF008 == 0) {
        return;
    }
    course = g_longRoundFlag + g_reverseRoundFlag * 2;
    if (g_cupId == 1) {
        PLAYSTATS_INC6(vsPlays[0][course]);
    } else if (g_cupId == 2) {
        PLAYSTATS_INC6(vsPlays[1][course]);
    } else if (g_cupId == 3) {
        PLAYSTATS_INC6(vsPlays[2][course]);
    } else if (g_cupId == 4) {
        PLAYSTATS_INC6(vsPlays[3][course]);
    } else if (g_cupId == 5) {
        PLAYSTATS_INC6(vsPlays[4][course]);
    } else if (g_cupId == 6) {
        PLAYSTATS_INC6(vsPlays[5][course]);
    } else if (g_cupId == 7) {
        PLAYSTATS_INC6(vsPlays[6][course]);
    } else if (g_cupId == 8) {
        PLAYSTATS_INC6(vsPlays[7][course]);
    }
}

#pragma exceptions on

void PlayStats_IncVsPeerCount(void) {
    int peers;

    if (lbl_806CF008 == 0) {
        return;
    }
    if (g_localPcbRole <= 1) {
        return;
    }
    peers = CountPeersWithRole(-1);
    if (peers == 2) {
        PLAYSTATS_INC(vsPeers2);
    }
    if (peers == 3) {
        PLAYSTATS_INC(vsPeers3);
    }
    if (peers == 4) {
        PLAYSTATS_INC(vsPeers4);
    }
}

#pragma exceptions reset
