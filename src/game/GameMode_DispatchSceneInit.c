/* GameMode_DispatchSceneInit (0x800A0950): builds the race game mode.
 * Cups 9..16 go to the mini-game path. Otherwise it refreshes the player
 * record, saves the backup, and creates the BtMode / TaMode / RaceScene
 * child for the current game mode. */
#pragma cplusplus on
void *operator new(unsigned long);
void operator delete(void *);

struct GMPlayerRecord;

extern "C" {
extern int g_cupId;
extern int g_gameMode;
extern GMPlayerRecord *lbl_806D10A0;
extern int lbl_806D134C;
extern int lbl_806D1350;
extern void fn_8024F530(void);
extern void fn_8024F588(void);
extern void *fn_80124DF8(void);
extern void RankLog_InitStartRace(GMPlayerRecord *rec);
extern void PlayerData_RefreshDerivedStats(GMPlayerRecord *rec);
extern void card_force_backup_now(void);
extern void fn_802C8B48(int on);
extern void *DrawManager_GetOrCreate(void);
extern void PlayStats_AccumulateCcClassPlay(void);
extern void PlayStats_AccumulatePlayTime(int);
extern void Backup_PublishShadowCopy_Inline(void);
extern void fn_80190720(void);
}

struct GMBtMode { unsigned char opaque[0x38]; GMBtMode(); };
struct GMTaMode { unsigned char opaque[0x40]; GMTaMode(); };
struct GMRaceScene { unsigned char opaque[0x40]; GMRaceScene(); };

struct GMRoot {
    GMRoot();
    virtual ~GMRoot();
};

struct GMRace : GMRoot {
    void *mode;

    GMRace() {
        card_force_backup_now();
        fn_802C8B48(1);
        DrawManager_GetOrCreate();
        PlayStats_AccumulateCcClassPlay();
        PlayStats_AccumulatePlayTime(0);
        Backup_PublishShadowCopy_Inline();
        fn_80190720();
        lbl_806D134C = 0;
        lbl_806D1350 = 0;
        if (g_gameMode == 2) {
            mode = new GMBtMode;
        } else if (g_gameMode == 1) {
            mode = new GMTaMode;
        } else {
            mode = new GMRaceScene;
        }
    }
    virtual ~GMRace();
};

#pragma exceptions on
extern "C" void *GameMode_DispatchSceneInit(void)
{
    GMPlayerRecord *rec;

    fn_8024F530();
    fn_8024F588();
    switch (g_cupId) {
    case 9:
    case 10:
    case 11:
    case 12:
    case 13:
    case 14:
    case 15:
    case 16:
        return fn_80124DF8();
    }
    rec = lbl_806D10A0 == 0 ? (GMPlayerRecord *)0 : lbl_806D10A0;
    if (rec != 0) {
        RankLog_InitStartRace(rec);
        PlayerData_RefreshDerivedStats(rec);
    }
    return new GMRace;
}
#pragma exceptions reset
#pragma cplusplus off
