/*
 * Play session bookkeeping for the operator statistics,
 * 0x8008DC70..0x8008DE60.
 */

typedef struct PlayStatsTimes {
    unsigned int totalPlaySeconds; /* 0x00 */
    unsigned int sessionSeconds; /* 0x04 */
    unsigned int pad08;
    unsigned int coinsInserted; /* 0x0C */
    unsigned int creditsAdded; /* 0x10 */
    unsigned int pad14[14];
    unsigned int grandPrixSeconds; /* 0x4C */
} PlayStatsTimes;

typedef struct BackupShadow {
    unsigned char pad000[0x280];
    unsigned int coinsInserted;
    unsigned int creditsAdded;
} BackupShadow;

extern PlayStatsTimes lbl_805AC2E0;
extern BackupShadow lbl_80598A60;
extern void *lbl_806D11E0; /* daily clock */
extern unsigned char lbl_806D11E4; /* session active */
extern unsigned char lbl_806D11E5;
extern unsigned char lbl_806D11E6;
extern unsigned char lbl_806D11E7;
extern unsigned char lbl_806D11E8;
extern unsigned char lbl_806D11E9;
extern unsigned char lbl_806D11EA;
extern int lbl_806D11EC;
extern int lbl_806D11F0; /* session start seconds */
extern int lbl_806CF00C;
extern int g_gameMode;

int DailyClock_GetCurrentSeconds(void *clock);
void OperationClock_Commit(void);
void Backup_PublishShadowCopy_Inline(void);
void PlayStats_AccumulateFinishByRank(void);

void PlayStats_CopyStatsBlock(void *dst, const void *src);

#pragma exceptions on

int PlayStats_TickActiveSessionSeconds(void)
{
    int delta;

    if (lbl_806D11E4 == 0) {
        return 0;
    }
    delta = DailyClock_GetCurrentSeconds(lbl_806D11E0) - lbl_806D11F0;
    lbl_805AC2E0.sessionSeconds += delta;
    if (g_gameMode == 0) {
        lbl_805AC2E0.grandPrixSeconds += delta;
    }
    OperationClock_Commit();
    return lbl_806D11F0 = DailyClock_GetCurrentSeconds(lbl_806D11E0);
}

int PlayStats_EndPlaySession(void)
{
    int delta;

    if (lbl_806D11E4 == 0) {
        return 0;
    }
    PlayStats_AccumulateFinishByRank();
    delta = DailyClock_GetCurrentSeconds(lbl_806D11E0) - lbl_806D11F0;
    lbl_805AC2E0.sessionSeconds += delta;
    if (g_gameMode == 0) {
        lbl_805AC2E0.grandPrixSeconds += delta;
    }
    OperationClock_Commit();
    lbl_806D11EC = 0;
    lbl_806D11E4 = 0;
    lbl_806D11F0 = 0;
    return 1;
}

int PlayStats_BeginPlaySession(void)
{
    if (lbl_806D11E4 == 1) {
        return 0;
    }
    lbl_806D11F0 = DailyClock_GetCurrentSeconds(lbl_806D11E0);
    lbl_806D11EC = 0;
    lbl_806D11E4 = 1;
    lbl_806CF00C = -1;
    lbl_806D11E5 = 0;
    lbl_806D11E6 = 0;
    lbl_806D11E7 = 0;
    lbl_806D11E8 = 0;
    lbl_806D11E9 = 0;
    lbl_806D11EA = 0;
    return 1;
}

void PlayStats_PublishCoinCreditShadow(void)
{
    lbl_80598A60.coinsInserted = lbl_805AC2E0.coinsInserted;
    lbl_80598A60.creditsAdded = lbl_805AC2E0.creditsAdded;
    Backup_PublishShadowCopy_Inline();
}

int PlayStats_PublishStatsBlockShadow(void)
{
    PlayStats_CopyStatsBlock((char *)&lbl_80598A60 + 0x274, &lbl_805AC2E0);
    Backup_PublishShadowCopy_Inline();
    return 1;
}

#pragma exceptions reset
