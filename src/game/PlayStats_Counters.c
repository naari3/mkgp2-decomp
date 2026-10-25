/*
 * Operator play statistics counters, 0x8008D87C..0x8008DC70.
 * Every counter saturates at 99999999.
 */

#define PLAYSTATS_MAX 99999999u

typedef struct PlayStats {
    unsigned int totalPlaySeconds; /* 0x00 */
    unsigned int pad04;
    unsigned int singlePlayJoins; /* 0x08 */
    unsigned int coinsInserted; /* 0x0C */
    unsigned int creditsAdded; /* 0x10 */
    unsigned int pad14[2];
    unsigned int vs2PJoins; /* 0x1C */
    unsigned int vs2PlusJoins; /* 0x20 */
    unsigned int vs3PlusJoins; /* 0x24 */
    unsigned int vs4PJoins; /* 0x28 */
    unsigned int pad2C[10];
    unsigned int allCups3rd[3]; /* 0x54, per cc class */
    unsigned int allCupsFinal[3]; /* 0x60, per cc class */
} PlayStats;

extern PlayStats lbl_805AC2E0;
extern unsigned char lbl_806CF008; /* stats enabled */
extern int lbl_806CF00C;
extern int lbl_806D11EC;
extern unsigned char lbl_806D11E5;
extern unsigned char lbl_806D11E6;
extern unsigned char lbl_806D11E7;
extern unsigned char lbl_806D11E8;
extern unsigned char lbl_806D11E9;
extern unsigned char lbl_806D11EA;
extern int g_ccClass;
extern int g_roundIndex;

#define PLAYSTATS_INC(field)                       \
    do {                                           \
        if (++lbl_805AC2E0.field > PLAYSTATS_MAX) { \
            lbl_805AC2E0.field = PLAYSTATS_MAX;    \
        }                                          \
    } while (0)

void PlayStats_OnAllItemsUnlocked_Stub(void)
{
    if (lbl_806CF008 == 0) {
        return;
    }
}

void PlayStats_IncAllCupsClearedFinalMilestone(void)
{
    if (lbl_806CF008 == 0) {
        return;
    }
    if (g_ccClass == 0) {
        if (lbl_806D11E6 == 0) {
            lbl_806D11E6 = 1;
            PLAYSTATS_INC(allCupsFinal[0]);
        }
    } else if (g_ccClass == 1) {
        if (lbl_806D11E8 == 0) {
            lbl_806D11E8 = 1;
            PLAYSTATS_INC(allCupsFinal[1]);
        }
    } else {
        if (lbl_806D11EA == 0) {
            lbl_806D11EA = 1;
            PLAYSTATS_INC(allCupsFinal[2]);
        }
    }
}

void PlayStats_IncAllCupsCleared3rdMilestone(void)
{
    if (lbl_806CF008 == 0) {
        return;
    }
    if (g_ccClass == 0) {
        if (lbl_806D11E5 == 0) {
            lbl_806D11E5 = 1;
            PLAYSTATS_INC(allCups3rd[0]);
        }
    } else if (g_ccClass == 1) {
        if (lbl_806D11E7 == 0) {
            lbl_806D11E7 = 1;
            PLAYSTATS_INC(allCups3rd[1]);
        }
    } else {
        if (lbl_806D11E9 == 0) {
            lbl_806D11E9 = 1;
            PLAYSTATS_INC(allCups3rd[2]);
        }
    }
}

void PlayStats_OnMissionResult_Stub(void)
{
    if (lbl_806CF008 == 0) {
        return;
    }
    if (g_roundIndex == 4) {
        return;
    }
}

void PlayStats_OnMissionSceneInit_Stub(void)
{
    if (lbl_806CF008 == 0) {
        return;
    }
    if (g_roundIndex == 4) {
        return;
    }
}

void PlayStats_OnRace1stPlace_Stub(void)
{
    if (lbl_806CF008 == 0) {
        return;
    }
    if (g_roundIndex == 4) {
        return;
    }
}

void PlayStats_OnRaceSceneInit_Stub(void)
{
    if (lbl_806CF008 == 0) {
        return;
    }
    if (g_roundIndex == 4) {
        return;
    }
}

void PlayStats_IncVs3PlusJoin(void)
{
    if (lbl_806CF008 == 0) {
        return;
    }
    PLAYSTATS_INC(vs3PlusJoins);
}

void PlayStats_IncVs4PJoin(void)
{
    if (lbl_806CF008 == 0) {
        return;
    }
    PLAYSTATS_INC(vs4PJoins);
}

void PlayStats_IncVs2PlusJoin(void)
{
    if (lbl_806CF008 == 0) {
        return;
    }
    PLAYSTATS_INC(vs2PlusJoins);
}

void PlayStats_IncVs2PJoin(void)
{
    if (lbl_806CF008 == 0) {
        return;
    }
    PLAYSTATS_INC(vs2PJoins);
    lbl_806CF00C = 0;
}

void PlayStats_IncSinglePlayJoin(void)
{
    if (lbl_806CF008 == 0) {
        return;
    }
    PLAYSTATS_INC(singlePlayJoins);
    lbl_806D11EC++;
}

void PlayStats_IncCreditAdded(void)
{
    if (lbl_806CF008 == 0) {
        return;
    }
    PLAYSTATS_INC(creditsAdded);
}

void PlayStats_IncCoinInserted(void)
{
    if (lbl_806CF008 == 0) {
        return;
    }
    PLAYSTATS_INC(coinsInserted);
}

void PlayStats_AddTotalPlaySeconds(unsigned int seconds)
{
    if ((lbl_805AC2E0.totalPlaySeconds += seconds) > PLAYSTATS_MAX) {
        lbl_805AC2E0.totalPlaySeconds = PLAYSTATS_MAX;
    }
}
