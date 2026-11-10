/* SetCourseParams (0x8009CBFC): select cup/round/variant and reset the
 * per-race kart, lap and rank slots.
 *
 * The target addresses these .bss objects pooled off one base. Compiled as
 * C++ (-lang=c++, extern "C" names) MWCC lays uninitialized globals out in
 * definition order, which matches; as C it uses first-use order.
 * NonMatching: ~50 lines of constant/pointer register order left in the
 * lap/rank reset block. */

extern "C" {
typedef struct KartSlot {
    int driverId;
    int charId;
    int field8;
    int fieldC;
    int kartVariant;
    unsigned char items[3];
    unsigned char pad17;
} KartSlot;

typedef struct LapEntry {
    int a;
    int b;
    float c;
    float d;
} LapEntry;

struct LapExtra {
    LapEntry e;
    int f10;
};

typedef struct RankSlot {
    unsigned char active;
    unsigned char pad1;
    unsigned short count;
    unsigned char pad4[0xC];
    int target;
    int source;
    unsigned char flag18;
    unsigned char flag19;
    unsigned char pad1A[2];
    int timer;
    float value20;
    float value24;
    unsigned char enabled;
    unsigned char pad29[3];
} RankSlot;

extern KartSlot SetCourseParams_bss_805AC600[8];
extern unsigned char KartDriverArray_StaticCtor_bss_805AC6C0[0xC];
extern unsigned char SetCourseParams_bss_805AC6CC[0x5E00];
extern LapEntry SetCourseParams_bss_805B24CC[10];
extern struct LapExtra RaceResult_StoreLatest_bss_805B256C;
extern unsigned char SetCourseParams_bss_805B2580[0x20000];
extern unsigned char g_playerData[0x1DC];
extern unsigned char SetCourseParams_bss_805D275C[0x1DC];
extern int RaceSlot_ResetAll_bss_805D2938[4];
extern RankSlot SetCourseParams_bss_805D2948[8];

KartSlot SetCourseParams_bss_805AC600[8];
unsigned char KartDriverArray_StaticCtor_bss_805AC6C0[0xC];
unsigned char SetCourseParams_bss_805AC6CC[0x5E00];
LapEntry SetCourseParams_bss_805B24CC[10];
struct LapExtra RaceResult_StoreLatest_bss_805B256C;
unsigned char SetCourseParams_bss_805B2580[0x20000];
unsigned char g_playerData[0x1DC];
unsigned char SetCourseParams_bss_805D275C[0x1DC];
int RaceSlot_ResetAll_bss_805D2938[4];
RankSlot SetCourseParams_bss_805D2948[8];

extern int g_cupId;
extern int g_longRoundFlag;
extern int g_courseVariantIdx;
extern int g_reverseRoundFlag;
extern unsigned char g_raceStarted;
extern unsigned char SetCourseParams_bss_806D1258;
extern int SetCourseParams_data_806CF10C;
extern int SetCourseParams_bss_806D1280;
extern int SetCourseParams_bss_806D12D8;
extern const float lbl_806D4790;
extern const float lbl_806D4798;

static inline void ResetRankSlot(RankSlot *slot)
{
    slot->active = 0;
    slot->count = 0;
    slot->target = -1;
    slot->source = -1;
    slot->flag18 = 0;
    slot->flag19 = 0;
    slot->timer = 0;
    slot->value20 = lbl_806D4790;
    slot->value24 = lbl_806D4790;
    slot->enabled = 1;
}

int SetCourseParams(int cup, int longRound, int variant, int reverse)
{
    int i;

    if (cup < 0 || cup >= 17) {
        return 0;
    }
    if (longRound < 0 || longRound >= 2) {
        return 0;
    }
    g_cupId = cup;
    g_longRoundFlag = longRound;
    g_courseVariantIdx = variant;
    g_reverseRoundFlag = reverse;
    for (i = 0; i < 8; ++i) {
        SetCourseParams_bss_805AC600[i].driverId = -1;
        SetCourseParams_bss_805AC600[i].charId = -1;
        SetCourseParams_bss_805AC600[i].field8 = 1;
        SetCourseParams_bss_805AC600[i].items[0] = 0x24;
        SetCourseParams_bss_805AC600[i].items[1] = 0x25;
        { SetCourseParams_bss_805AC600[i].items[2] = 0x26;
        SetCourseParams_bss_805AC600[i].kartVariant = 0; }
        RaceSlot_ResetAll_bss_805D2938[i] = 0;
    }
    /* fakematch: the target reloads both globals after the slot loop;
     * natural code: if (g_cupId >= 0 && g_longRoundFlag >= 0) */
    if (*(volatile int *)&g_cupId >= 0 && *(volatile int *)&g_longRoundFlag >= 0) {
        g_raceStarted = 0;
    }
    SetCourseParams_data_806CF10C = 0;
    if (0 == SetCourseParams_bss_806D1258) {
        struct LapExtra *extra = &RaceResult_StoreLatest_bss_805B256C;
        RankSlot *rank = SetCourseParams_bss_805D2948;
        LapEntry *lap = SetCourseParams_bss_805B24CC;
        for (i = 0; 5 > i; ++i) {
            lap[i].a = 0;
            lap[i].b = 0;
            lap[i].c = lbl_806D4790;
            lap[i].d = lbl_806D4798;
        }
        for (i = 5; i < 10; i++) {
            lap[i].a = 0;
            lap[i].b = 1;
            lap[i].c = lbl_806D4790;
            lap[i].d = lbl_806D4798;
        }
        RaceResult_StoreLatest_bss_805B256C.e.a = 0;
        extra->e.b = 0;
        extra->e.c = lbl_806D4790;
        extra->e.d = lbl_806D4798;
        SetCourseParams_bss_806D1280 = 4;
        SetCourseParams_bss_806D1258 = 1;
        /* The original resets each rank explicitly rather than retaining a loop. */
        ResetRankSlot(&rank[0]);
        ResetRankSlot(&rank[1]);
        ResetRankSlot(&rank[2]);
        ResetRankSlot(&rank[3]);
        ResetRankSlot(&rank[4]);
        ResetRankSlot(&rank[5]);
        ResetRankSlot(&rank[6]);
        ResetRankSlot(&rank[7]);
        SetCourseParams_bss_806D12D8 = 0;
    }
    return 1;
}


extern unsigned char lbl_806D12AD;
extern unsigned char lbl_806D12AE;
extern unsigned char lbl_806D12AF;
extern unsigned char lbl_806D12B0;
extern int lbl_806D12C0;
extern unsigned char lbl_806D12E4[3];
extern unsigned char g_namCamFlag;
extern unsigned char g_isCommHost;
extern unsigned char g_isPcbHost;
extern unsigned char g_nonFirstFinishFlag;
extern unsigned char g_finalLapCoinJumpEnabled;
extern int g_currentSceneState;
extern int g_localPcbRole;
extern int g_consecutiveWinsTier;
extern int g_ccClass;
extern void *memset(void *, int, unsigned long);
extern void fn_801D7610(void *playerData, int flag);
extern void fn_8018CC64(void);

void RaceFlow_ResetState_FullColdInit(void)
{
    int i;

    memset(g_playerData, 0, 0x1DC);
    fn_801D7610(g_playerData, 1);
    {
        RankSlot *rank = SetCourseParams_bss_805D2948;
        ResetRankSlot(&rank[0]);
        ResetRankSlot(&rank[1]);
        ResetRankSlot(&rank[2]);
        ResetRankSlot(&rank[3]);
        ResetRankSlot(&rank[4]);
        ResetRankSlot(&rank[5]);
        ResetRankSlot(&rank[6]);
        ResetRankSlot(&rank[7]);
        SetCourseParams_bss_806D12D8 = 0;
    }
    fn_8018CC64();

    lbl_806D12AD = 0;
    lbl_806D12AE = 0;
    lbl_806D12AF = 0;
    g_namCamFlag = 0;
    lbl_806D12C0 = 0;
    g_isCommHost = 0;
    g_currentSceneState = 2;
    g_isPcbHost = 0;
    g_localPcbRole = 0;
    g_consecutiveWinsTier = 0;
    lbl_806D12B0 = 0;
    g_cupId = 1;
    g_longRoundFlag = 0;
    g_courseVariantIdx = 0;
    g_reverseRoundFlag = 0;
    for (i = 0; i < 8; ++i) {
        SetCourseParams_bss_805AC600[i].driverId = -1;
        SetCourseParams_bss_805AC600[i].charId = -1;
        SetCourseParams_bss_805AC600[i].field8 = 1;
        SetCourseParams_bss_805AC600[i].items[0] = 0x24;
        SetCourseParams_bss_805AC600[i].items[1] = 0x25;
        SetCourseParams_bss_805AC600[i].items[2] = 0x26;
        SetCourseParams_bss_805AC600[i].kartVariant = 0;
        RaceSlot_ResetAll_bss_805D2938[i] = 0;
    }
    if (*(volatile int *)&g_cupId >= 0 && *(volatile int *)&g_longRoundFlag >= 0) {
        g_raceStarted = 0;
    }
    SetCourseParams_data_806CF10C = 0;
    if (0 == SetCourseParams_bss_806D1258) {
        struct LapExtra *extra = &RaceResult_StoreLatest_bss_805B256C;
        RankSlot *rank = SetCourseParams_bss_805D2948;
        LapEntry *lap = SetCourseParams_bss_805B24CC;
        for (i = 0; 5 > i; ++i) {
            lap[i].a = 0;
            lap[i].b = 0;
            lap[i].c = lbl_806D4790;
            lap[i].d = lbl_806D4798;
        }
        for (i = 5; i < 10; i++) {
            lap[i].a = 0;
            lap[i].b = 1;
            lap[i].c = lbl_806D4790;
            lap[i].d = lbl_806D4798;
        }
        RaceResult_StoreLatest_bss_805B256C.e.a = 0;
        extra->e.b = 0;
        extra->e.c = lbl_806D4790;
        extra->e.d = lbl_806D4798;
        SetCourseParams_bss_806D1280 = 4;
        SetCourseParams_bss_806D1258 = 1;
        ResetRankSlot(&rank[0]);
        ResetRankSlot(&rank[1]);
        ResetRankSlot(&rank[2]);
        ResetRankSlot(&rank[3]);
        ResetRankSlot(&rank[4]);
        ResetRankSlot(&rank[5]);
        ResetRankSlot(&rank[6]);
        ResetRankSlot(&rank[7]);
        SetCourseParams_bss_806D12D8 = 0;
    }
    g_ccClass = 0;
    g_nonFirstFinishFlag = 0;
    g_finalLapCoinJumpEnabled = 0;
    lbl_806D12E4[0] = 0;
    lbl_806D12E4[1] = 0;
    lbl_806D12E4[2] = 0;
}

}
