/* RaceFlow_ResetState_FullColdInit (0x8009D07C): cold reset of the race
 * flow state. Clears player data, eight race entries, kart slots and flow
 * flags; on the first call it also resets the ranking table.
 *
 * These objects share the .bss pool defined in SetCourseParams.c. Keep a
 * byte-addressed view because the eight score stores at pool+0x26338
 * extend into the first race entry at pool+0x26348. A four-element score
 * member indexed eight times would exceed that member's bounds.
 *
 * NonMatching (90%): the target retains separate entry/rank bases and
 * reloads cup/round globals after the slot stores. This view retains the
 * upper pool base across the initial calls, but still folds field offsets
 * and propagates the just-stored globals. */

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

/* The score view extends into the race-entry storage. */
extern unsigned char lbl_805AC600[];

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

static inline void RaceEntries_Reset(unsigned char *bank)
{
    int i;

    for (i = 0; i < 8; i++) {
        RaceEntry_Init(&((RaceEntry *)(bank + 0x6348))[i], lbl_806D4790);
    }
    lbl_806D12D8 = 0;
}

void RaceFlow_ResetState_FullColdInit(void)
{
    int i_;
    unsigned char *base = lbl_805AC600;
    unsigned char *bank = base + 0x20000;
    int i;

    memset(bank + 0x5F80, 0, 0x1DC);
    fn_801D7610(bank + 0x5F80, 1);
    for (i_ = 0; i_ < 8; i_++) {
    RaceEntry_Init(&((RaceEntry *)(bank + 0x6348))[i_], lbl_806D4790);
    }
    lbl_806D12D8 = 0;
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
        KartSlot *s = &((KartSlot *)base)[i];
        s->character = -1;
        s->variant = -1;
        s->active = 1;
        s->colorA = 0x24;
        s->colorB = 0x25;
        s->colorC = 0x26;
        s->score = 0;
        ((int *)(bank + 0x6338))[i] = 0;
    }

    if (g_cupId >= 0 && g_longRoundFlag >= 0) {
        g_raceStarted = 0;
    }

    lbl_806CF10C = 0;
    if (!lbl_806D1258) {
        for (i = 0; i < 5; i++) {
            ((RankRow *)(base + 0x5ECC))[i].id = 0;
            ((RankRow *)(base + 0x5ECC))[i].group = 0;
            ((RankRow *)(base + 0x5ECC))[i].time = lbl_806D4790;
            ((RankRow *)(base + 0x5ECC))[i].best = lbl_806D4798;
        }
        for (i = 5; i < 10; i++) {
            ((RankRow *)(base + 0x5ECC))[i].id = 0;
            ((RankRow *)(base + 0x5ECC))[i].group = 1;
            ((RankRow *)(base + 0x5ECC))[i].time = lbl_806D4790;
            ((RankRow *)(base + 0x5ECC))[i].best = lbl_806D4798;
        }
        ((RankRow *)(base + 0x5F6C))->id = 0;
        ((RankRow *)(base + 0x5F6C))->group = 0;
        ((RankRow *)(base + 0x5F6C))->time = lbl_806D4790;
        ((RankRow *)(base + 0x5F6C))->best = lbl_806D4798;
        lbl_806D1280 = 4;
        lbl_806D1258 = 1;
        RaceEntries_Reset(bank);
    }

    g_ccClass = 0;
    g_nonFirstFinishFlag = 0;
    g_finalLapCoinJumpEnabled = 0;
    lbl_806D12E4[0] = 0;
    lbl_806D12E4[1] = 0;
    lbl_806D12E4[2] = 0;
}
