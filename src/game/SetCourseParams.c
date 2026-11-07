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

extern KartSlot lbl_805AC600[8];
extern unsigned char lbl_805AC6C0[0xC];
extern unsigned char lbl_805AC6CC[0x5E00];
extern LapEntry lbl_805B24CC[10];
extern struct LapExtra lbl_805B256C;
extern unsigned char lbl_805B2580[0x20000];
extern unsigned char g_playerData[0x1DC];
extern unsigned char lbl_805D275C[0x1DC];
extern int lbl_805D2938[4];
extern RankSlot lbl_805D2948[8];

KartSlot lbl_805AC600[8];
unsigned char lbl_805AC6C0[0xC];
unsigned char lbl_805AC6CC[0x5E00];
LapEntry lbl_805B24CC[10];
struct LapExtra lbl_805B256C;
unsigned char lbl_805B2580[0x20000];
unsigned char g_playerData[0x1DC];
unsigned char lbl_805D275C[0x1DC];
int lbl_805D2938[4];
RankSlot lbl_805D2948[8];

extern int g_cupId;
extern int g_longRoundFlag;
extern int g_courseVariantIdx;
extern int g_reverseRoundFlag;
extern unsigned char g_raceStarted;
extern unsigned char lbl_806D1258;
extern int lbl_806CF10C;
extern int lbl_806D1280;
extern int lbl_806D12D8;
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
        lbl_805AC600[i].driverId = -1;
        lbl_805AC600[i].charId = -1;
        lbl_805AC600[i].field8 = 1;
        lbl_805AC600[i].items[0] = 0x24;
        lbl_805AC600[i].items[1] = 0x25;
        { lbl_805AC600[i].items[2] = 0x26;
        lbl_805AC600[i].kartVariant = 0; }
        lbl_805D2938[i] = 0;
    }
    /* fakematch: the target reloads both globals after the slot loop;
     * natural code: if (g_cupId >= 0 && g_longRoundFlag >= 0) */
    if (*(volatile int *)&g_cupId >= 0 && *(volatile int *)&g_longRoundFlag >= 0) {
        g_raceStarted = 0;
    }
    lbl_806CF10C = 0;
    if (0 == lbl_806D1258) {
        struct LapExtra *extra = &lbl_805B256C;
        RankSlot *rank = lbl_805D2948;
        LapEntry *lap = lbl_805B24CC;
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
        lbl_805B256C.e.a = 0;
        extra->e.b = 0;
        extra->e.c = lbl_806D4790;
        extra->e.d = lbl_806D4798;
        lbl_806D1280 = 4;
        lbl_806D1258 = 1;
        /* The original resets each rank explicitly rather than retaining a loop. */
        ResetRankSlot(&rank[0]);
        ResetRankSlot(&rank[1]);
        ResetRankSlot(&rank[2]);
        ResetRankSlot(&rank[3]);
        ResetRankSlot(&rank[4]);
        ResetRankSlot(&rank[5]);
        ResetRankSlot(&rank[6]);
        ResetRankSlot(&rank[7]);
        lbl_806D12D8 = 0;
    }
    return 1;
}

}
