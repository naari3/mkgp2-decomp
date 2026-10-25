/* RaceFlow_ResetState_FullColdInit (0x8009D07C): cold reset of the race
 * flow state. Clears the player data, the eight race entries and the kart
 * slots and the flow flags; on the very first call it also resets the
 * ranking table. The race globals all live in one pooled .bss block that
 * starts at lbl_805AC600, so they are modelled as one struct here.
 * NonMatching (90%): the target is compiled in the TU that defines that
 * block (see SetCourseParams.c), so it keeps base and base+0x20000 in
 * registers and reloads the globals it just stored; the struct model
 * folds the addresses and propagates the constants instead. */

typedef struct KartSlot {
    int character;      /* 0x00 */
    int variant;        /* 0x04 */
    int active;         /* 0x08 */
    int pad0C;
    int score;          /* 0x10 */
    unsigned char colorA;  /* 0x14 */
    unsigned char colorB;  /* 0x15 */
    unsigned char colorC;  /* 0x16 */
    unsigned char pad17;
} KartSlot;

typedef struct RankRow {
    int id;
    int group;
    float time;
    float best;
} RankRow;

typedef struct RaceEntry {
    unsigned char used;    /* 0x00 */
    unsigned char pad01;
    short count;           /* 0x02 */
    unsigned char pad04[0xC];
    int kart;              /* 0x10 */
    int driver;            /* 0x14 */
    unsigned char flagA;   /* 0x18 */
    unsigned char flagB;   /* 0x19 */
    unsigned char pad1A[2];
    int lap;               /* 0x1C */
    float time;            /* 0x20 */
    float lapTime;         /* 0x24 */
    unsigned char alive;   /* 0x28 */
    unsigned char pad29[3];
} RaceEntry;

typedef struct RaceGlobals {
    KartSlot slots[8];                         /* 0x00000 */
    unsigned char pad000C0[0x5ECC - 0xC0];
    RankRow ranks[10];                         /* 0x05ECC */
    RankRow rankTail;                          /* 0x05F6C */
    unsigned char pad05F7C[0x25F80 - 0x5F7C];
    unsigned char playerData[0x1DC];           /* 0x25F80 */
    unsigned char playerData2[0x1DC];          /* 0x2615C */
    int slotScore[4];                          /* 0x26338 */
    RaceEntry entries[8];                      /* 0x26348 */
} RaceGlobals;

extern RaceGlobals lbl_805AC600;
extern const float lbl_806D4790; /* 0.0 */
extern const float lbl_806D4798; /* 1000.0 */

extern unsigned char lbl_806D12AD;
extern unsigned char lbl_806D12AE;
extern unsigned char lbl_806D12AF;
extern unsigned char lbl_806D12B0;
extern int lbl_806D12C0;
extern int lbl_806D12D8;
extern unsigned char lbl_806D12E4[3];
extern unsigned char lbl_806D1258;
extern int lbl_806D1280;
extern int lbl_806CF10C;
extern unsigned char g_namCamFlag;
extern unsigned char g_isCommHost;
extern unsigned char g_isPcbHost;
extern unsigned char g_raceStarted;
extern unsigned char g_nonFirstFinishFlag;
extern unsigned char g_finalLapCoinJumpEnabled;
extern int g_currentSceneState;
extern int g_localPcbRole;
extern int g_consecutiveWinsTier;
extern int g_cupId;
extern int g_longRoundFlag;
extern int g_courseVariantIdx;
extern int g_reverseRoundFlag;
extern int g_ccClass;

extern void *memset(void *, int, unsigned long);
extern void fn_801D7610(void *playerData, int flag);
extern void fn_8018CC64(void);

static inline void RaceEntry_Init(RaceEntry *e, float zero)
{
    e->used = 0;
    e->count = 0;
    e->kart = -1;
    e->driver = -1;
    e->flagA = 0;
    e->flagB = 0;
    e->lap = 0;
    e->time = zero;
    e->lapTime = zero;
    e->alive = 1;
}

static inline void RaceEntries_Reset(RaceGlobals *g)
{
    int i;

    for (i = 0; i < 8; i++) {
        RaceEntry_Init(&g->entries[i], lbl_806D4790);
    }
    lbl_806D12D8 = 0;
}

void RaceFlow_ResetState_FullColdInit(void)
{
    RaceGlobals *g = &lbl_805AC600;
    int i;

    memset(g->playerData, 0, 0x1DC);
    fn_801D7610(g->playerData, 1);
    RaceEntries_Reset(g);
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

    for (i = 0; i < 8; i++) {
        KartSlot *s = &g->slots[i];
        s->character = -1;
        s->variant = -1;
        s->active = 1;
        s->colorA = 0x24;
        s->colorB = 0x25;
        s->colorC = 0x26;
        s->score = 0;
        g->slotScore[i] = 0;
    }

    if (g_cupId >= 0 && g_longRoundFlag >= 0) {
        g_raceStarted = 0;
    }

    lbl_806CF10C = 0;
    if (!lbl_806D1258) {
        for (i = 0; i < 5; i++) {
            g->ranks[i].id = 0;
            g->ranks[i].group = 0;
            g->ranks[i].time = lbl_806D4790;
            g->ranks[i].best = lbl_806D4798;
        }
        for (i = 5; i < 10; i++) {
            g->ranks[i].id = 0;
            g->ranks[i].group = 1;
            g->ranks[i].time = lbl_806D4790;
            g->ranks[i].best = lbl_806D4798;
        }
        g->rankTail.id = 0;
        g->rankTail.group = 0;
        g->rankTail.time = lbl_806D4790;
        g->rankTail.best = lbl_806D4798;
        lbl_806D1280 = 4;
        lbl_806D1258 = 1;
        RaceEntries_Reset(g);
    }

    g_ccClass = 0;
    g_nonFirstFinishFlag = 0;
    g_finalLapCoinJumpEnabled = 0;
    lbl_806D12E4[0] = 0;
    lbl_806D12E4[1] = 0;
    lbl_806D12E4[2] = 0;
}
