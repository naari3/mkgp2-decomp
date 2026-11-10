/* RaceContext ctor (RaceContext_InitDefaults, 0x8009D6CC): resets the race
 * globals, the per-player slot table and (once) the aux/wide-row tables. */
/* Genuine C++ reconstruction of the observed RaceContext constructor.
 * Only the vptr/base lifetime and global storage accesses are established.
 * Authoritative target/callee assembly was used (Ghidra unavailable). */
#pragma cplusplus on
#pragma exceptions on
#pragma use_lmw_stmw on

extern "C" {
void ItemTable_PopulateAliasedSlots(void);
int CreditMgr_GetCreditCount(int);
void *TitleTracker_GetOrCreateSingleton(void);
void fn_8018CC64(void);
void fn_801D7610(void *, unsigned char);
void *memset(void *, int, unsigned long);
extern int g_ccClass, g_consecutiveWinsTier, g_courseVariantIdx;
extern volatile int g_cupId;
extern int g_currentSceneState, g_gameMode, g_humanPlayerCount, g_kartVariant;
extern volatile int g_longRoundFlag;
extern int g_localPcbRole, g_reverseRoundFlag, g_timerModeEnabled;
extern int SetCourseParams_data_806CF10C, lbl_806CF110, lbl_806CF12C, SetCourseParams_bss_806D1280, SetCourseParams_bss_806D12D8;
extern unsigned char g_isCommHost, g_isPcbHost, g_lakituStartAnimDone, g_raceStarted;
extern unsigned char lbl_806D117C, SetCourseParams_bss_806D1258, RaceContext_InitDefaults_bss_806D1259, lbl_806D1290;
extern unsigned char lbl_806D12B0, lbl_806D12E1, lbl_806D12E2;
extern unsigned char lbl_806D1264[3], lbl_806D12E4[3];
extern unsigned char SetCourseParams_bss_805AC600[], lbl_80598A60[], SetCourseParams_bss_805B2580[];
extern const float lbl_806D4790, lbl_806D4798;
}

struct RaceContextBase;
extern "C" RaceContextBase *lbl_806D12DC;
struct RaceContextBase {
    RaceContextBase() { lbl_806D12DC = this; }
    virtual ~RaceContextBase();
};
struct RaceContext : RaceContextBase {
    RaceContext();
    virtual ~RaceContext();
};
struct RaceSlot {
    int type, selection, enabled, pending, count;
    unsigned char item[3], unused;
};
struct RaceAux {
    int value, enabled;
    float current, limit;
};
struct RaceWideRow {
    unsigned char active, pad1;
    unsigned short count;
    unsigned char pad4[12];
    int selection, state;
    unsigned char flag18, flag19, pad1A[2];
    int value;
    float x, y;
    unsigned char enabled, pad29[3];
};

static inline void InitializeWideRow(RaceWideRow *row) {
    row->active = 0;
    row->count = 0;
    row->selection = -1;
    row->state = -1;
    row->flag18 = 0;
    row->flag19 = 0;
    row->value = 0;
    row->x = lbl_806D4790;
    row->y = lbl_806D4790;
    row->enabled = 1;
}

#define slots ((RaceSlot *)SetCourseParams_bss_805AC600)
RaceContext::RaceContext() {
    unsigned char *storage = SetCourseParams_bss_805AC600;
    unsigned char *farBank = storage + 0x20000;

    ItemTable_PopulateAliasedSlots();
    if (RaceContext_InitDefaults_bss_806D1259 != 1) {
        unsigned char *destination = SetCourseParams_bss_805B2580;
        int bank = 0;
        unsigned char *settings = lbl_80598A60;
        do {
            memset(destination, (signed char)((signed char)settings[0x21] - 1), 0x8000);
            ++bank;
            destination += 0x8000;
        } while (bank <= 3);
        RaceContext_InitDefaults_bss_806D1259 = 1;
    }

    g_timerModeEnabled = 1;
    g_cupId = 1;
    g_longRoundFlag = 0;
    g_courseVariantIdx = 0;
    g_reverseRoundFlag = 0;
    {
        int *counts = (int *)(farBank + 0x6338);
        for (int i = 0; i < 8; ++i) {
            slots[i].type = -1;
            slots[i].selection = -1;
            slots[i].enabled = 1;
            slots[i].item[0] = 0x24;
            slots[i].item[1] = 0x25;
            slots[i].item[2] = 0x26;
            slots[i].count = 0;
            counts[i] = 0;
        }
    }
    if (g_cupId >= 0 && g_longRoundFlag >= 0) {
        g_raceStarted = 0;
    }

    unsigned char initialized = SetCourseParams_bss_806D1258;
    SetCourseParams_data_806CF10C = 0;
    if (initialized == 0) {
        RaceAux *aux = (RaceAux *)(storage + 0x5ECC);
        RaceWideRow *rows = (RaceWideRow *)(farBank + 0x6348);
        for (int i = 0; i < 5; ++i) {
            aux[i].value = 0;
            aux[i].enabled = 0;
            aux[i].current = lbl_806D4790;
            aux[i].limit = lbl_806D4798;
        }
        for (int i = 5; i < 10; ++i) {
            aux[i].value = 0;
            aux[i].enabled = 1;
            aux[i].current = lbl_806D4790;
            aux[i].limit = lbl_806D4798;
        }
        RaceAux *last = (RaceAux *)(storage + 0x5F6C);
        last->value = 0;
        last->enabled = 0;
        last->current = lbl_806D4790;
        last->limit = lbl_806D4798;
        SetCourseParams_bss_806D1280 = 4;
        SetCourseParams_bss_806D1258 = 1;
        InitializeWideRow(&rows[0]);
        InitializeWideRow(&rows[1]);
        InitializeWideRow(&rows[2]);
        InitializeWideRow(&rows[3]);
        InitializeWideRow(&rows[4]);
        InitializeWideRow(&rows[5]);
        InitializeWideRow(&rows[6]);
        InitializeWideRow(&rows[7]);
        SetCourseParams_bss_806D12D8 = 0;
    }

    g_ccClass = 0;
    for (int i = 0; i < 7; ++i) {
        slots[i].type = 6;
        slots[i].selection = i + 1;
        slots[i].enabled = 1;
        slots[i].pending = 0;
        slots[i].count = 0;
    }
    slots[7].type = 0;
    slots[7].selection = 0;
    slots[7].enabled = 1;
    slots[7].pending = 0;
    slots[7].count = 0;
    slots[7].item[0] = 0x2B;
    slots[7].item[1] = 0x2D;
    slots[7].item[2] = 0x32;
    lbl_806D1264[0] = 0x2B;
    lbl_806D1264[1] = 0x2D;
    lbl_806D1264[2] = 0x32;
    g_lakituStartAnimDone = 0;
    lbl_806D1290 = 0;
    lbl_806CF110 = 1;
    g_gameMode = 0;
    g_isCommHost = 0;
    g_currentSceneState = 2;
    g_isPcbHost = 0;
    g_localPcbRole = 0;
    lbl_806D12B0 = 0;
    g_kartVariant = -1;
    g_humanPlayerCount = -1;
    g_consecutiveWinsTier = 0;
    lbl_806CF12C = -1;
    memset(farBank + 0x5F80, 0, 0x1DC);
    fn_801D7610(farBank + 0x5F80, 1);
    fn_8018CC64();
    TitleTracker_GetOrCreateSingleton();
    bool noCredit = CreditMgr_GetCreditCount(0) == 0;
    lbl_806D12E1 = 0;
    lbl_806D117C = noCredit;
    lbl_806D12E2 = 0;
    lbl_806D12E4[0] = 0;
    lbl_806D12E4[1] = 0;
    lbl_806D12E4[2] = 0;
}
#pragma exceptions reset
