#include "game/types/c_region.h"
C_REGION_BEGIN
/* Race context unit, .text 0x8009BAC4..0x8009DD64: race/rank/kart-slot
 * accessors, course table getters, SetCourseParams, the player-data
 * wrappers, the cold reset, the RaceContext class (ctor / dtor / singleton)
 * and the static constructor of the driver array.
 * One TU: it owns the .bss pool 0x805AC600..0x805D2AA8, and
 * RaceFlow_ResetState_FullColdInit / RaceContext_InitDefaults reach several
 * pool objects off one section anchor (`addi r5, r30, 0x6348`), which MWCC
 * only does in the unit that defines them. Merged from 14 over-split files;
 * each part keeps its own local views of the pool behind #define/#undef
 * renames (tools/extab_user_renames.json maps X_pN back to X). */

/* .bss pool, in address order. Defined in C++ mode: C orders pooled .bss by
 * first use, C++ by definition. */
typedef struct RaceKartSlot {
    int driverId;               /* 0x00 */
    int charId;                 /* 0x04 */
    int field8;                 /* 0x08 */
    int fieldC;                 /* 0x0C */
    int kartVariant;            /* 0x10 */
    unsigned char items[3];     /* 0x14 */
    unsigned char pad17;
} RaceKartSlot;

C_REGION_END
#pragma cplusplus on
extern "C" {
RaceKartSlot SetCourseParams_bss_805AC600[8];
unsigned char KartDriverArray_StaticCtor_bss_805AC6C0[0xC];     /* global-object registration node */
unsigned char SetCourseParams_bss_805AC6CC[0x5E00];  /* driver array */
unsigned char SetCourseParams_bss_805B24CC[0xA0];    /* rank rows [2][5], 0x10 each */
unsigned char RaceResult_StoreLatest_bss_805B256C[0x14];    /* latest result */
unsigned char SetCourseParams_bss_805B2580[0x20000]; /* four 0x8000 banks */
unsigned char g_playerData[0x1DC];
unsigned char SetCourseParams_bss_805D275C[0x1DC];
unsigned char RaceSlot_ResetAll_bss_805D2938[0x10];    /* per-slot counters (written 8 wide) */
unsigned char SetCourseParams_bss_805D2948[0x160];   /* 8 rank slots, 0x2C each */
}
#pragma cplusplus off
C_REGION_BEGIN

/* ==== RaceSys_8009BAC4.c ==== */
#define RankSlot RankSlot_p1
#define g_courseVariantIdx g_courseVariantIdx_p1
#define g_cupId g_cupId_p1
#define g_currentSceneState g_currentSceneState_p1
#define g_gameMode g_gameMode_p1
#define g_isPcbHost g_isPcbHost_p1
#define g_kartVariant g_kartVariant_p1
#define g_localPcbRole g_localPcbRole_p1
#define g_longRoundFlag g_longRoundFlag_p1
#define g_raceFrameCounterLo2digits g_raceFrameCounterLo2digits_p1
#define TaMode_GetDemoCameraBookend_data_8040DE94 lbl_8040DE94_p1
#define lbl_806D12AD lbl_806D12AD_p1
#define SetCourseParams_bss_806D12D8 lbl_806D12D8_p1
#define lbl_806D4790 lbl_806D4790_p1
#define lbl_806D4794 lbl_806D4794_p1
#define SetCourseParams_bss_805D2948 ((RankSlot *)SetCourseParams_bss_805D2948)
#pragma exceptions off
#pragma use_lmw_stmw off
/* Race/session accessors and setters (0x8009BAC4..0x8009BD04). */

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

extern int g_cupId;
extern int g_longRoundFlag;
extern int g_courseVariantIdx;
extern int g_currentSceneState;
extern int g_gameMode;
extern int g_raceFrameCounterLo2digits;
extern unsigned char lbl_806D12AD;
extern int g_kartVariant;
extern int g_localPcbRole;
extern signed char g_isPcbHost;
extern int SetCourseParams_bss_806D12D8;
extern unsigned char TaMode_GetDemoCameraBookend_data_8040DE94[];

extern const float lbl_806D4790;
extern const float lbl_806D4794;

int Input_IsItemButtonPressed(int buttons)
{
    if ((g_currentSceneState == 4 || g_currentSceneState == 5) && (buttons & 0x2000)) {
        return 1;
    }
    if (buttons & 0xC000) {
        return 1;
    }
    return 0;
}

int BattleRoulette_TickAndGetCounter(void)
{
    if (g_gameMode == 2) {
        g_raceFrameCounterLo2digits++;
    }
    return g_raceFrameCounterLo2digits;
}

void SetCardVolumeFlagByte(unsigned char v)
{
    lbl_806D12AD = v;
}

void SetKartVariant(int v)
{
    g_kartVariant = v;
}

int PcbRole_PromoteToClientConfirmed(int arg)
{
    if (g_localPcbRole < 2 || g_localPcbRole > 4) {
        return 0;
    }
    g_localPcbRole = 5;
    return arg;
}

void SetLocalPcbRole(int role)
{
    g_localPcbRole = role;
    g_isPcbHost = role == 1;
}

void SetSyncTarget(int v)
{
    g_currentSceneState = v;
}

void ItemUse_ResetAllKartUseSlots(void)
{
    int i;

    for (i = 0; i < 8; i++) {
        RankSlot *s = &SetCourseParams_bss_805D2948[i];
        s->active = 0;
        s->count = 0;
        s->target = -1;
        s->source = -1;
        s->flag18 = 0;
        s->flag19 = 0;
        s->timer = 0;
        s->value20 = lbl_806D4790;
        s->value24 = lbl_806D4790;
        s->enabled = 1;
    }
    SetCourseParams_bss_806D12D8 = 0;
}

RankSlot *RankSlot_GetByIndex(int i)
{
    if (i < 0 || i >= 8) {
        return 0;
    }
    return &SetCourseParams_bss_805D2948[i];
}
#undef RankSlot
#undef g_courseVariantIdx
#undef g_cupId
#undef g_currentSceneState
#undef g_gameMode
#undef g_isPcbHost
#undef g_kartVariant
#undef g_localPcbRole
#undef g_longRoundFlag
#undef g_raceFrameCounterLo2digits
#undef TaMode_GetDemoCameraBookend_data_8040DE94
#undef lbl_806D12AD
#undef SetCourseParams_bss_806D12D8
#undef lbl_806D4790
#undef lbl_806D4794
#undef SetCourseParams_bss_805D2948
#pragma cplusplus off

/* ==== RankSlot_AppendOrUpdate.c ==== */
#define RankSlot RankSlot_p2
#define RankSlotTime RankSlotTime_p2
#define SetCourseParams_bss_806D12D8 lbl_806D12D8_p2
#define SetCourseParams_bss_805D2948 ((RankSlot *)SetCourseParams_bss_805D2948)
#pragma exceptions on
#pragma use_lmw_stmw off
typedef struct RankSlotTime {
    unsigned short v[5];
} RankSlotTime;

typedef struct RankSlot {
    unsigned char kart;
    unsigned char pad01;
    unsigned short time[6];
    unsigned char pad0e[2];
    int field10;
    int field14;
    unsigned char field18;
    unsigned char field19;
    unsigned char pad1a[2];
    int field1c;
    float field20;
    float field24;
    unsigned char field28;
    unsigned char pad29[3];
} RankSlot;

extern int SetCourseParams_bss_806D12D8;

int RankSlot_AppendOrUpdate(unsigned char kart, int a1, int a2, RankSlotTime *time,
                            unsigned char b18, unsigned char b19, int a1c, unsigned char b28,
                            float f20, float f24, int index)
{
    int slot = SetCourseParams_bss_806D12D8;
    RankSlot *p;

    if (index > -1) {
        slot = index;
    }
    if (slot >= 8) {
        return -1;
    }
    p = &SetCourseParams_bss_805D2948[slot];
    SetCourseParams_bss_806D12D8 = slot + 1;
    p->kart = kart;
    p->field10 = a1;
    p->field14 = a2;
    p->field18 = b18;
    p->field19 = b19;
    p->field1c = a1c;
    p->field20 = f20;
    p->field24 = f24;
    p->field28 = b28;
    if (time == 0) {
        p->time[0] = 0;
    } else {
        p->time[0] = time->v[0];
        p->time[1] = time->v[1];
        p->time[2] = time->v[2];
        p->time[3] = time->v[3];
        p->time[4] = time->v[4];
        p->time[5] = 0;
    }
    return slot;
}
#undef RankSlot
#undef RankSlotTime
#undef SetCourseParams_bss_806D12D8
#undef SetCourseParams_bss_805D2948
#pragma cplusplus off

/* ==== VSMode_SeedRandomItemSequence.c ==== */
#define KartSlot KartSlot_p3
#define KartSlot_Set KartSlot_Set_p3
#define rand rand_p3
#define SetCourseParams_bss_805AC600 ((KartSlot *)SetCourseParams_bss_805AC600)
#pragma exceptions on
#pragma use_lmw_stmw off
/* VSMode_SeedRandomItemSequence (0x8009BDC0): fill `count` consecutive kart
 * slots starting at `slot` with CPU drivers (driverId 6) whose characters are
 * drawn at random without repetition from the 13 selectable characters;
 * `exclude` (the player's character) is never drawn. Returns the next slot. */

extern int rand(void);

typedef struct KartSlot {
    int driverId;           /* 0x00 */
    int charId;             /* 0x04 */
    int field8;             /* 0x08 */
    int fieldC;             /* 0x0C */
    int kartVariant;        /* 0x10 */
    unsigned char items[3]; /* 0x14 */
    unsigned char pad17;
} KartSlot;

static inline void KartSlot_Set(int i, int driver, int chr)
{
    if (i < 0 || i >= 8 || chr < 0 || chr >= 15) {
        return;
    }
    SetCourseParams_bss_805AC600[i].driverId = driver;
    SetCourseParams_bss_805AC600[i].charId = chr;
    SetCourseParams_bss_805AC600[i].field8 = 1;
    SetCourseParams_bss_805AC600[i].fieldC = 0;
    SetCourseParams_bss_805AC600[i].kartVariant = 0;
}

#pragma use_lmw_stmw on
int VSMode_SeedRandomItemSequence(int slot, int exclude, int count)
{
    unsigned char used[13];
    int i;
    int chr;

    for (i = 0; i < 13; i++) {
        used[i] = 0;
    }
    used[exclude] = 1;
    for (i = 0; i < count; i++) {
        do {
            chr = rand() % 13;
        } while (used[chr]);
        used[chr] = 1;
        KartSlot_Set(slot, 6, chr);
        slot++;
    }
    return slot;
}
#pragma use_lmw_stmw off
#undef KartSlot
#undef KartSlot_Set
#undef rand
#undef SetCourseParams_bss_805AC600
#pragma cplusplus off

/* ==== RaceData_8009BEF4.c ==== */
#define CharacterData CharacterData_p4
#define CourseData CourseData_p4
#define CourseDir CourseDir_p4
#define DisplayState DisplayState_p4
#define GetStartPositionPtr GetStartPositionPtr_p4
#define RankEntry RankEntry_p4
#define Vec3f Vec3f_p4
#define g_ccClass g_ccClass_p4
#define g_characterDataTable g_characterDataTable_p4
#define g_courseScene3D g_courseScene3D_p4
#define g_courseVariantIdx g_courseVariantIdx_p4
#define g_cupId g_cupId_p4
#define g_gameMode g_gameMode_p4
#define g_longRoundFlag g_longRoundFlag_p4
#define g_raceStarted g_raceStarted_p4
#define g_reverseRoundFlag g_reverseRoundFlag_p4
#define g_timerModeEnabled g_timerModeEnabled_p4
#define SetCourseParams_rodata_80320604 lbl_80320604_p4
#define RaceScene_GetPerspFovyForCup_data_80401118 lbl_80401118_p4
#define GetCoinSpawnTable_data_8040B218 lbl_8040B218_p4
#define DebugOverlay_GetCupLabel_data_8040B318 lbl_8040B318_p4
#define SetCourseParams_data_8040B90C lbl_8040B90C_p4
#define lbl_80598A60 lbl_80598A60_p4
#define DebugOverlay_GetLongRoundLabel_data_806CF100 lbl_806CF100_p4
#define SetCourseParams_bss_806D1278 lbl_806D1278_p4
#define SetCourseParams_bss_806D1280 lbl_806D1280_p4
#define lbl_806D46CC lbl_806D46CC_p4
#define lbl_806D46D4 lbl_806D46D4_p4
#define lbl_806D46DC lbl_806D46DC_p4
#define lbl_806D4790 lbl_806D4790_p4
#define SetCourseParams_bss_805B2580 ((unsigned char *)SetCourseParams_bss_805B2580)
#define RaceResult_StoreLatest_bss_805B256C (*(RankEntry *)RaceResult_StoreLatest_bss_805B256C)
#define SetCourseParams_bss_805B24CC ((RankEntry (*)[5])SetCourseParams_bss_805B24CC)
#define SetCourseParams_bss_805AC6CC ((unsigned char *)SetCourseParams_bss_805AC6CC)
#define RaceSlot_ResetAll_bss_805D2938 ((int *)RaceSlot_ResetAll_bss_805D2938)
#pragma exceptions off
#pragma use_lmw_stmw off
/* --- owned .data 0x8040E1C4..0x8040E450 (tools/own_data.py) --- */
extern char lbl_806D46CC[];
extern char lbl_806D46D4[];
extern char lbl_806D46DC[];
extern const unsigned int SetCourseParams_rodata_80320604[6];
#pragma force_active on
void *DebugOverlay_GetDaytimeLabel_data_8040E1C4[163] = {
    (void *)&lbl_806D46CC,
    (void *)&lbl_806D46D4,
    (void *)&lbl_806D46DC,
    (void *)&SetCourseParams_rodata_80320604,
    (void *)0x4552524F,
    (void *)0x5221204E,
    (void *)0x6F207374,
    (void *)0x61676520,
    (void *)0x6E756D62,
    (void *)0x65722E00,
    (void *)0x4552524F,
    (void *)0x5221204E,
    (void *)0x6F207374,
    (void *)0x61676520,
    (void *)0x74797065,
    (void *)0x2E000000,
    (void *)0x2B,
    (void *)0x2D,
    (void *)0x39,
    (void *)0x2B,
    (void *)0x5D,
    (void *)0x39,
    (void *)0x2D,
    (void *)0x5C,
    (void *)0x73,
    (void *)0x5D,
    (void *)0x5B,
    (void *)0x71,
    (void *)0x73,
    (void *)0x71,
    (void *)0x3C,
    (void *)0x73,
    (void *)0x71,
    (void *)0x3C,
    (void *)0x73,
    (void *)0x71,
    (void *)0x3C,
    (void *)0x73,
    (void *)0x71,
    (void *)0x3C,
    (void *)0x73,
    (void *)0x71,
    (void *)0x3C,
    (void *)0x39,
    (void *)0x5B,
    (void *)0x4E,
    (void *)0x3D,
    (void *)0x4E,
    (void *)0x3E,
    (void *)0x8,
    (void *)0x22,
    (void *)0x2B,
    (void *)0x3E,
    (void *)0x22,
    (void *)0x1B,
    (void *)0x3E,
    (void *)0x22,
    (void *)0x1B,
    (void *)0x3E,
    (void *)0x22,
    (void *)0x1B,
    (void *)0x3E,
    (void *)0x22,
    (void *)0x1B,
    (void *)0x3E,
    (void *)0x22,
    (void *)0x1B,
    (void *)0x3D,
    (void *)0x2D,
    (void *)0x5C,
    (void *)0x2B,
    (void *)0x32,
    (void *)0x69,
    (void *)0x46,
    (void *)0x50,
    (void *)0x40,
    (void *)0x69,
    (void *)0x40,
    (void *)0x6C,
    (void *)0x69,
    (void *)0x40,
    (void *)0x6C,
    (void *)0x69,
    (void *)0x40,
    (void *)0x6C,
    (void *)0x69,
    (void *)0x40,
    (void *)0x6C,
    (void *)0x69,
    (void *)0x40,
    (void *)0x6C,
    (void *)0x39,
    (void *)0x5B,
    (void *)0x4A,
    (void *)0x31,
    (void *)0x2E,
    (void *)0x32,
    (void *)0x1A,
    (void *)0x46,
    (void *)0x50,
    (void *)0x31,
    (void *)0x1A,
    (void *)0x19,
    (void *)0x31,
    (void *)0x1A,
    (void *)0x19,
    (void *)0x31,
    (void *)0x1A,
    (void *)0x19,
    (void *)0x31,
    (void *)0x1A,
    (void *)0x19,
    (void *)0x31,
    (void *)0x1A,
    (void *)0x19,
    (void *)0x2B,
    (void *)0x39,
    (void *)0x32,
    (void *)0x72,
    (void *)0x4E,
    (void *)0x46,
    (void *)0x72,
    (void *)0x54,
    (void *)0x8,
    (void *)0x72,
    (void *)0x54,
    (void *)0x1C,
    (void *)0x72,
    (void *)0x54,
    (void *)0x1C,
    (void *)0x72,
    (void *)0x54,
    (void *)0x1C,
    (void *)0x72,
    (void *)0x54,
    (void *)0x1C,
    (void *)0x72,
    (void *)0x54,
    (void *)0x1C,
    (void *)0x3D,
    (void *)0x2D,
    (void *)0x5C,
    (void *)0x17,
    (void *)0x17,
    (void *)0x17,
    (void *)0x8,
    (void *)0x8,
    (void *)0x8,
    (void *)0x3D,
    (void *)0x3E,
    (void *)0x3F,
    (void *)0x3D,
    (void *)0x3E,
    (void *)0x3F,
    (void *)0x3D,
    (void *)0x3E,
    (void *)0x3F,
    (void *)0x3D,
    (void *)0x3E,
    (void *)0x3F,
    (void *)0x3D,
    (void *)0x3E,
    (void *)0x3F
};
#pragma force_active reset
/* Race/course data accessors (0x8009BEF4..0x8009CBFC): display buffers,
 * race result ranking, the per-course data table (SetCourseParams_data_8040B90C, indexed
 * [cup][longRound], with per-reverse and per-variant sub-arrays), kart
 * slots and debug overlay labels. */

#include "game/types/Vec3f.h"

#include "game/types/RankEntry.h"

typedef struct CourseDir {
    void *finishLine;           /* 0x00 */
    Vec3f *startPos;            /* 0x04 */
    float startYaw;             /* 0x08 */
    void *bgmPath;              /* 0x0C */
    void *model[4];             /* 0x10 */
    void *modelTimer[4];        /* 0x20 */
    void *objectTable[4];       /* 0x30 */
    void *bgm[4];               /* 0x40 */
    void *unk50[4];             /* 0x50 */
    void *collision[4];         /* 0x60 */
} CourseDir;

typedef struct CourseData {
    void *unk0;                 /* 0x000 */
    void *jointNames[4];        /* 0x004 */
    void *collisionBin[4];      /* 0x014 */
    CourseDir dir[2];           /* 0x024 */
    void *variantTable[4];      /* 0x104 */
} CourseData;

typedef RaceKartSlot KartSlot;

#include "game/types/CharacterData.h"

typedef struct DisplayState {
    unsigned char pad[0x21];
    signed char bufferIndex;
} DisplayState;

extern int g_cupId;
extern int g_longRoundFlag;
extern int g_courseVariantIdx;
extern int g_reverseRoundFlag;
extern int g_timerModeEnabled;
extern int g_ccClass;
extern int g_gameMode;
extern unsigned char g_raceStarted;
extern void *g_courseScene3D;
extern void *SetCourseParams_bss_806D1278;
extern void *SetCourseParams_bss_806D1280;
extern const float lbl_806D4790;

extern DisplayState lbl_80598A60;

extern CourseData SetCourseParams_data_8040B90C[][2];
extern void *GetCoinSpawnTable_data_8040B218[][2][2][2];

extern unsigned char RaceScene_GetPerspFovyForCup_data_80401118[];
extern CharacterData g_characterDataTable[15];
extern void *DebugOverlay_GetLongRoundLabel_data_806CF100[2];
extern void *DebugOverlay_GetCupLabel_data_8040B318[17];

void *GetDisplayContext(int i)
{
    if (i < 0 || i > 3) {
        return 0;
    }
    return SetCourseParams_bss_805B2580 + (i << 15);
}

int GetDisplayBufferIndex(void)
{
    return lbl_80598A60.bufferIndex - 1;
}

void SetRaceResultLatestPtr(void *p)
{
    SetCourseParams_bss_806D1280 = p;
}

void RaceResult_StoreLatest(int a, int b, float score, float time)
{
    RaceResult_StoreLatest_bss_805B256C.a = a;
    RaceResult_StoreLatest_bss_805B256C.b = b;
    RaceResult_StoreLatest_bss_805B256C.score = score;
    RaceResult_StoreLatest_bss_805B256C.time = time;
}

RankEntry *RaceResult_GetRankEntry(int i)
{
    if (i < 0 || i >= 5) {
        return 0;
    }
    return &SetCourseParams_bss_805B24CC[g_longRoundFlag][i];
}

int RaceResult_InsertSortedRank(int a, int b, float score, float time)
{
    RankEntry *e;
    int off;
    int i;
    int j;

    off = g_longRoundFlag * 0x50;
    e = (RankEntry *)((unsigned char *)SetCourseParams_bss_805B24CC + off);

    for (i = 0; i < 5; i++) {
        if (lbl_806D4790 == e[i].time || time <= e[i].time) {
            break;
        }
    }
    if (i >= 5) {
        return -1;
    }
    if (i != 4) {
        for (j = 4; j > i; j--) {
            e[j].a = e[j - 1].a;
            e[j].b = e[j - 1].b;
            e[j].score = e[j - 1].score;
            e[j].time = e[j - 1].time;
        }
    }
    e[i].a = a;
    {
        unsigned char *u = (unsigned char *)SetCourseParams_bss_805B24CC;
        RankEntry *t;

        u += off;
        t = (RankEntry *)u + i;
        t->b = b;
        t->score = score;
        t->time = time;
    }
    return i;
}

void *GetRaceContextPtr(void)
{
    return SetCourseParams_bss_805AC6CC;
}

void SetPlayerCarObject(void *p)
{
    SetCourseParams_bss_806D1278 = p;
}

void *GetPlayerCarObject(void)
{
    return SetCourseParams_bss_806D1278;
}

void SetCourseScene3D(void *p)
{
    g_courseScene3D = p;
}

void *GetCourseScene3D(void)
{
    return g_courseScene3D;
}

void SetRaceStartFlag(unsigned char v)
{
    if (g_cupId < 0) {
        return;
    }
    if (g_longRoundFlag < 0) {
        return;
    }
    g_raceStarted = v;
}

int IsRaceStarted(void)
{
    if (g_cupId < 0) {
        return 0;
    }
    if (g_longRoundFlag < 0) {
        return 0;
    }
    return g_raceStarted;
}

void *GetCourseBgmFilePath(void)
{
    if (g_cupId < 0) {
        return 0;
    }
    if (g_longRoundFlag < 0) {
        return 0;
    }
    if (g_courseVariantIdx < 0) {
        return 0;
    }
    return SetCourseParams_data_8040B90C[g_cupId][g_longRoundFlag].dir[g_reverseRoundFlag].bgmPath;
}

void *GetCoinSpawnTable(void)
{
    int cup = g_cupId - 1;
    int cc = g_ccClass == 2;
    int lr = g_longRoundFlag;
    int rev = g_reverseRoundFlag;

    if (cup < 0) {
        return 0;
    }
    if (lr < 0) {
        return 0;
    }
    if (rev < 0) {
        return 0;
    }
    if (cc < 0) {
        return 0;
    }
    if (g_gameMode == 1) {
        return GetCoinSpawnTable_data_8040B218[cup][lr][rev][cc];
    }
    return GetCoinSpawnTable_data_8040B218[cup][lr][rev][0];
}

void *GetCourseBgmEntry(void)
{
    if (g_cupId < 0) {
        return 0;
    }
    if (g_longRoundFlag < 0) {
        return 0;
    }
    if (g_courseVariantIdx < 0) {
        return 0;
    }
    return SetCourseParams_data_8040B90C[g_cupId][g_longRoundFlag].dir[g_reverseRoundFlag].bgm[g_courseVariantIdx];
}

void *CourseVariantTableLookup(void)
{
    if (g_cupId < 0) {
        return 0;
    }
    if (g_longRoundFlag < 0) {
        return 0;
    }
    if (g_courseVariantIdx < 0) {
        return 0;
    }
    return SetCourseParams_data_8040B90C[g_cupId][g_longRoundFlag].variantTable[g_courseVariantIdx];
}

void *GetFinishLineSegment(void)
{
    if (g_cupId < 0) {
        return 0;
    }
    if (g_longRoundFlag < 0) {
        return 0;
    }
    return SetCourseParams_data_8040B90C[g_cupId][g_longRoundFlag].dir[g_reverseRoundFlag].finishLine;
}

void *GetCourseModelFilename(void)
{
    if (g_cupId < 0) {
        return 0;
    }
    if (g_longRoundFlag < 0) {
        return 0;
    }
    if (g_timerModeEnabled == 0) {
        return SetCourseParams_data_8040B90C[g_cupId][g_longRoundFlag].dir[g_reverseRoundFlag].model[g_courseVariantIdx];
    }
    return SetCourseParams_data_8040B90C[g_cupId][g_longRoundFlag].dir[g_reverseRoundFlag].modelTimer[g_courseVariantIdx];
}

void *GetCourseObjectTable(void)
{
    if (g_cupId < 0) {
        return 0;
    }
    if (g_longRoundFlag < 0) {
        return 0;
    }
    return SetCourseParams_data_8040B90C[g_cupId][g_longRoundFlag].dir[g_reverseRoundFlag].objectTable[g_courseVariantIdx];
}

void *GetCollisionFilename(void)
{
    if (g_cupId < 0) {
        return 0;
    }
    if (g_longRoundFlag < 0) {
        return 0;
    }
    return SetCourseParams_data_8040B90C[g_cupId][g_longRoundFlag].dir[g_reverseRoundFlag].collision[g_courseVariantIdx];
}

void *GetJointNameTable(void)
{
    if (g_cupId < 0) {
        return 0;
    }
    if (g_longRoundFlag < 0) {
        return 0;
    }
    return SetCourseParams_data_8040B90C[g_cupId][g_longRoundFlag].jointNames[g_courseVariantIdx];
}

void *GetCollisionBinFilename(void)
{
    if (g_cupId < 0) {
        return 0;
    }
    if (g_longRoundFlag < 0) {
        return 0;
    }
    if (g_courseVariantIdx < 0) {
        return 0;
    }
    return SetCourseParams_data_8040B90C[g_cupId][g_longRoundFlag].collisionBin[g_courseVariantIdx];
}

float GetCourseStartYaw(void)
{
    if (g_cupId < 0) {
        return lbl_806D4790;
    }
    if (g_longRoundFlag < 0) {
        return lbl_806D4790;
    }
    return SetCourseParams_data_8040B90C[g_cupId][g_longRoundFlag].dir[g_reverseRoundFlag].startYaw;
}

static inline Vec3f *GetStartPositionPtr(int i)
{
    if (i < 0) {
        return 0;
    }
    if (g_cupId < 0) {
        return 0;
    }
    if (g_longRoundFlag < 0) {
        return 0;
    }
    return &SetCourseParams_data_8040B90C[g_cupId][g_longRoundFlag].dir[g_reverseRoundFlag].startPos[i];
}

int GetStartPosition(int i, float *x, float *y, float *z)
{
    Vec3f *p = GetStartPositionPtr(i);

    if (p == 0) {
        return 0;
    }
    if (x != 0) {
        *x = p->x;
    }
    if (y != 0) {
        *y = p->y;
    }
    if (z != 0) {
        *z = p->z;
    }
    return 1;
}

int GetKartStartSlot(int driver)
{
    int i;

    if (driver <= -1 || driver >= 6) {
        return -1;
    }
    for (i = 0; i < 8; i++) {
        if (driver == SetCourseParams_bss_805AC600[i].driverId) {
            return i;
        }
    }
    return -1;
}

void *GetKartModelNameEntry(int chara, int kart)
{
    int k;

    if (chara < 0 || chara >= 15) {
        return 0;
    }
    k = kart;
    if (kart == -1) {
        k = 0;
    }
    if (kart == 3) {
        k = 2;
    }
    return RaceScene_GetPerspFovyForCup_data_80401118 + k * 0x9C + chara * 0xC;
}

void *GetCharacterName(int i)
{
    if (i < 0 || i >= 15) {
        return 0;
    }
    return g_characterDataTable[i].name;
}

CharacterData *GetCharacterDataEntry(int i)
{
    if (i < 0 || i >= 15) {
        return 0;
    }
    return &g_characterDataTable[i];
}

int GetKartSlotCharId(int i)
{
    if (i < 0 || i >= 8) {
        return -1;
    }
    return SetCourseParams_bss_805AC600[i].charId;
}

int RaceSlot_GetDriverId(int i)
{
    if (i < 0 || i >= 8) {
        return -1;
    }
    return SetCourseParams_bss_805AC600[i].driverId;
}

int GetKartSlotKartVariant(int i)
{
    if (i < 0 || i >= 8) {
        return 0;
    }
    return SetCourseParams_bss_805AC600[i].kartVariant;
}

int RaceSlot_SetDriverPtr(int i, int v)
{
    if (i < 0 || i >= 8) {
        return 0;
    }
    SetCourseParams_bss_805AC600[i].kartVariant = v;
    return 1;
}

int RaceSlot_SetItemSlotByte(int i, int slot, unsigned char v)
{
    if (i < 0 || i >= 8) {
        return 0;
    }
    if (slot < 0 || slot >= 3) {
        return 0;
    }
    SetCourseParams_bss_805AC600[i].items[slot] = v;
    return 1;
}

int RaceSlot_InitSlot(int i, int driver, int chara, int f8, int fc)
{
    if (i < 0 || i >= 8) {
        return 0;
    }
    if (driver < 0 || driver >= 8) {
        return 0;
    }
    if (chara < 0 || chara >= 15) {
        return 0;
    }
    SetCourseParams_bss_805AC600[i].driverId = driver;
    SetCourseParams_bss_805AC600[i].charId = chara;
    SetCourseParams_bss_805AC600[i].field8 = f8;
    SetCourseParams_bss_805AC600[i].fieldC = fc;
    SetCourseParams_bss_805AC600[i].kartVariant = 0;
    return 1;
}

void RaceSlot_ResetAll(void)
{
    int i;

    for (i = 0; i < 8; i++) {
        SetCourseParams_bss_805AC600[i].driverId = -1;
        SetCourseParams_bss_805AC600[i].charId = -1;
        SetCourseParams_bss_805AC600[i].field8 = 1;
        SetCourseParams_bss_805AC600[i].items[0] = 0x24;
        SetCourseParams_bss_805AC600[i].items[1] = 0x25;
        SetCourseParams_bss_805AC600[i].items[2] = 0x26;
        SetCourseParams_bss_805AC600[i].kartVariant = 0;
        RaceSlot_ResetAll_bss_805D2938[i] = 0;
    }
}

int IsTimerModeEnabled(void)
{
    return g_timerModeEnabled;
}

int SetTimerModeEnabled(int v)
{
    g_timerModeEnabled = v;
    return 1;
}

void *DebugOverlay_GetDaytimeLabel(int i)
{
    if (i <= -1) {
        i = g_courseVariantIdx;
    }
    if (i >= 4) {
        return 0;
    }
    return DebugOverlay_GetDaytimeLabel_data_8040E1C4[i];
}

void *DebugOverlay_GetLongRoundLabel(int i)
{
    if (i <= -1) {
        i = g_longRoundFlag;
    }
    if (i >= 2) {
        return 0;
    }
    return DebugOverlay_GetLongRoundLabel_data_806CF100[i];
}

void *DebugOverlay_GetCupLabel(int i)
{
    if (i <= -1) {
        i = g_cupId;
    }
    if (i >= 17) {
        return 0;
    }
    return DebugOverlay_GetCupLabel_data_8040B318[i];
}

void SetReverseRoundFlag(int v)
{
    g_reverseRoundFlag = v;
}
#undef CharacterData
#undef CourseData
#undef CourseDir
#undef DisplayState
#undef GetStartPositionPtr
#undef RankEntry
#undef Vec3f
#undef g_ccClass
#undef g_characterDataTable
#undef g_courseScene3D
#undef g_courseVariantIdx
#undef g_cupId
#undef g_gameMode
#undef g_longRoundFlag
#undef g_raceStarted
#undef g_reverseRoundFlag
#undef g_timerModeEnabled
#undef SetCourseParams_rodata_80320604
#undef RaceScene_GetPerspFovyForCup_data_80401118
#undef GetCoinSpawnTable_data_8040B218
#undef DebugOverlay_GetCupLabel_data_8040B318
#undef SetCourseParams_data_8040B90C
#undef lbl_80598A60
#undef DebugOverlay_GetLongRoundLabel_data_806CF100
#undef SetCourseParams_bss_806D1278
#undef SetCourseParams_bss_806D1280
#undef lbl_806D46CC
#undef lbl_806D46D4
#undef lbl_806D46DC
#undef lbl_806D4790
#undef SetCourseParams_bss_805AC6CC
#undef SetCourseParams_bss_805B24CC
#undef RaceResult_StoreLatest_bss_805B256C
#undef SetCourseParams_bss_805B2580
#undef RaceSlot_ResetAll_bss_805D2938
#pragma cplusplus off

/* ==== SetCourseParams.c ==== */
C_REGION_END
#pragma cplusplus on
#define KartSlot KartSlot_p5
#define LapEntry LapEntry_p5
#define LapExtra LapExtra_p5
#define RankSlot RankSlot_p5
#define ResetRankSlot ResetRankSlot_p5
#define g_courseVariantIdx g_courseVariantIdx_p5
#define g_cupId g_cupId_p5
#define g_longRoundFlag g_longRoundFlag_p5
#define g_raceStarted g_raceStarted_p5
#define g_reverseRoundFlag g_reverseRoundFlag_p5
#define SetCourseParams_data_806CF10C lbl_806CF10C_p5
#define SetCourseParams_bss_806D1258 lbl_806D1258_p5
#define SetCourseParams_bss_806D1280 lbl_806D1280_p5
#define SetCourseParams_bss_806D12D8 lbl_806D12D8_p5
#define lbl_806D4790 lbl_806D4790_p5
#define lbl_806D4798 lbl_806D4798_p5
#define SetCourseParams_bss_805AC600 ((KartSlot *)SetCourseParams_bss_805AC600)
#define KartDriverArray_StaticCtor_bss_805AC6C0 ((unsigned char *)KartDriverArray_StaticCtor_bss_805AC6C0)
#define SetCourseParams_bss_805AC6CC ((unsigned char *)SetCourseParams_bss_805AC6CC)
#define SetCourseParams_bss_805B24CC ((LapEntry *)SetCourseParams_bss_805B24CC)
#define RaceResult_StoreLatest_bss_805B256C (*(struct LapExtra *)RaceResult_StoreLatest_bss_805B256C)
#define SetCourseParams_bss_805B2580 ((unsigned char *)SetCourseParams_bss_805B2580)
#define g_playerData ((unsigned char *)g_playerData)
#define SetCourseParams_bss_805D275C ((unsigned char *)SetCourseParams_bss_805D275C)
#define RaceSlot_ResetAll_bss_805D2938 ((int *)RaceSlot_ResetAll_bss_805D2938)
#define SetCourseParams_bss_805D2948 ((RankSlot *)SetCourseParams_bss_805D2948)
#pragma exceptions on
#pragma use_lmw_stmw off
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

}
#undef KartSlot
#undef LapEntry
#undef LapExtra
#undef RankSlot
#undef ResetRankSlot
#undef g_courseVariantIdx
#undef g_cupId
#undef g_longRoundFlag
#undef g_raceStarted
#undef g_reverseRoundFlag
#undef SetCourseParams_data_806CF10C
#undef SetCourseParams_bss_806D1258
#undef SetCourseParams_bss_806D1280
#undef SetCourseParams_bss_806D12D8
#undef lbl_806D4790
#undef lbl_806D4798
#undef g_playerData
#undef SetCourseParams_bss_805AC600
#undef KartDriverArray_StaticCtor_bss_805AC6C0
#undef SetCourseParams_bss_805AC6CC
#undef SetCourseParams_bss_805B24CC
#undef RaceResult_StoreLatest_bss_805B256C
#undef SetCourseParams_bss_805B2580
#undef SetCourseParams_bss_805D275C
#undef RaceSlot_ResetAll_bss_805D2938
#undef SetCourseParams_bss_805D2948
#pragma cplusplus off
C_REGION_BEGIN

/* ==== PlayerData_ApplyItemUnlockById.c ==== */
#define fn_801D5F74 fn_801D5F74_p6
#define g_playerData ((unsigned char *)g_playerData)
#pragma exceptions on
#pragma use_lmw_stmw off
extern void fn_801D5F74(void *playerData, int id, int value);

void PlayerData_ApplyItemUnlockById(int id)
{
    fn_801D5F74(g_playerData, id, 1);
}
#undef fn_801D5F74
#undef g_playerData
#pragma cplusplus off

/* ==== PlayerData_GetUnlockedItemIdByIndex_U8.c ==== */
#define PlayerData_ResolveUnlockedIdByIndex PlayerData_ResolveUnlockedIdByIndex_p7
#define g_playerData ((unsigned char *)g_playerData)
#pragma exceptions on
#pragma use_lmw_stmw off
extern int PlayerData_ResolveUnlockedIdByIndex(void *playerData, int index);

unsigned char PlayerData_GetUnlockedItemIdByIndex_U8(int index)
{
    return PlayerData_ResolveUnlockedIdByIndex(g_playerData, index);
}
#undef PlayerData_ResolveUnlockedIdByIndex
#undef g_playerData
#pragma cplusplus off

/* ==== PlayerData_ResetForFlow.c ==== */
#define fn_801D7610 fn_801D7610_p8
#define memset memset_p8
#define g_playerData ((unsigned char *)g_playerData)
#pragma exceptions on
#pragma use_lmw_stmw off
extern void *memset(void *, int, unsigned long);
extern void fn_801D7610(void *playerData, int flag);

void PlayerData_ResetForFlow(void)
{
    memset(g_playerData, 0, 0x1DC);
    fn_801D7610(g_playerData, 1);
}
#undef fn_801D7610
#undef memset
#undef g_playerData
#pragma cplusplus off

/* ==== RaceFlow_ResetState_FullColdInit.c ==== */
#define KartSlot KartSlot_p9
#define RaceEntries_Reset RaceEntries_Reset_p9
#define RaceEntry RaceEntry_p9
#define RaceEntry_Init RaceEntry_Init_p9
#define RankRow RankRow_p9
#define fn_8018CC64 fn_8018CC64_p9
#define fn_801D7610 fn_801D7610_p9
#define g_ccClass g_ccClass_p9
#define g_consecutiveWinsTier g_consecutiveWinsTier_p9
#define g_courseVariantIdx g_courseVariantIdx_p9
#define g_cupId g_cupId_p9
#define g_currentSceneState g_currentSceneState_p9
#define g_finalLapCoinJumpEnabled g_finalLapCoinJumpEnabled_p9
#define g_isCommHost g_isCommHost_p9
#define g_isPcbHost g_isPcbHost_p9
#define g_localPcbRole g_localPcbRole_p9
#define g_longRoundFlag g_longRoundFlag_p9
#define g_namCamFlag g_namCamFlag_p9
#define g_nonFirstFinishFlag g_nonFirstFinishFlag_p9
#define g_raceStarted g_raceStarted_p9
#define g_reverseRoundFlag g_reverseRoundFlag_p9
#define SetCourseParams_data_806CF10C lbl_806CF10C_p9
#define SetCourseParams_bss_806D1258 lbl_806D1258_p9
#define SetCourseParams_bss_806D1280 lbl_806D1280_p9
#define lbl_806D12AD lbl_806D12AD_p9
#define lbl_806D12AE lbl_806D12AE_p9
#define lbl_806D12AF lbl_806D12AF_p9
#define lbl_806D12B0 lbl_806D12B0_p9
#define lbl_806D12C0 lbl_806D12C0_p9
#define SetCourseParams_bss_806D12D8 lbl_806D12D8_p9
#define lbl_806D12E4 lbl_806D12E4_p9
#define lbl_806D4790 lbl_806D4790_p9
#define lbl_806D4798 lbl_806D4798_p9
#define memset memset_p9
#define SetCourseParams_bss_805AC600 ((KartSlot *)SetCourseParams_bss_805AC600)
#define SetCourseParams_bss_805D2948 ((RaceEntry *)SetCourseParams_bss_805D2948)
#define RaceSlot_ResetAll_bss_805D2938 ((int *)RaceSlot_ResetAll_bss_805D2938)
#define SetCourseParams_bss_805B24CC ((RankRow *)SetCourseParams_bss_805B24CC)
#define RaceResult_StoreLatest_bss_805B256C (*(RankRow *)RaceResult_StoreLatest_bss_805B256C)
#define g_playerData ((unsigned char *)g_playerData)
#pragma exceptions on
#pragma use_lmw_stmw off
/* RaceFlow_ResetState_FullColdInit (0x8009D07C): cold reset of the race
 * flow state. Clears player data, eight race entries, kart slots and flow
 * flags; on the first call it also resets the ranking table.
 *
 * These objects share the .bss pool defined in SetCourseParams.c. Keep a
 * byte-addressed view because the eight score stores at pool+0x26338
 * extend into the first race entry at pool+0x26348. A four-element score
 * member indexed eight times would exceed that member's bounds.
 *
 * NonMatching (95%): left are the anchor/upper-bank saved registers (r31/r30
 * swapped), row/entries pointer numbering (r8/r7) and an early `li r0,-1`
 * in the last block. Levers that got here: explicit `RankRow *row` local
 * (all unrolled stores go through the pointer) and the entry reset loop as
 * an inline taking the array pointer. */

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

extern const float lbl_806D4790; /* 0.0 */
extern const float lbl_806D4798; /* 1000.0 */

extern unsigned char lbl_806D12AD;
extern unsigned char lbl_806D12AE;
extern unsigned char lbl_806D12AF;
extern unsigned char lbl_806D12B0;
extern int lbl_806D12C0;
extern int SetCourseParams_bss_806D12D8;
extern unsigned char lbl_806D12E4[3];
extern unsigned char SetCourseParams_bss_806D1258;
extern int SetCourseParams_bss_806D1280;
extern int SetCourseParams_data_806CF10C;
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

static inline void RaceEntries_Reset(RaceEntry *e)
{
    int i;

    for (i = 0; i < 8; i++) {
        RaceEntry_Init(&e[i], lbl_806D4790);
    }
    SetCourseParams_bss_806D12D8 = 0;
}

void RaceFlow_ResetState_FullColdInit(void)
{
    int i;

    memset(g_playerData, 0, 0x1DC);
    fn_801D7610(g_playerData, 1);
    RaceEntries_Reset(SetCourseParams_bss_805D2948);
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
        SetCourseParams_bss_805AC600[i].character = -1;
        SetCourseParams_bss_805AC600[i].variant = -1;
        SetCourseParams_bss_805AC600[i].active = 1;
        SetCourseParams_bss_805AC600[i].colorA = 0x24;
        SetCourseParams_bss_805AC600[i].colorB = 0x25;
        SetCourseParams_bss_805AC600[i].colorC = 0x26;
        SetCourseParams_bss_805AC600[i].score = 0;
        RaceSlot_ResetAll_bss_805D2938[i] = 0;
    }

    if (g_cupId >= 0 && g_longRoundFlag >= 0) {
        g_raceStarted = 0;
    }

    SetCourseParams_data_806CF10C = 0;
    if (!SetCourseParams_bss_806D1258) {
        RankRow *extra = &RaceResult_StoreLatest_bss_805B256C;
        RaceEntry *e = SetCourseParams_bss_805D2948;
        RankRow *row = SetCourseParams_bss_805B24CC;
        for (i = 0; 5 > i; ++i) {
            row[i].id = 0;
            row[i].group = 0;
            row[i].time = lbl_806D4790;
            row[i].best = lbl_806D4798;
        }
        for (i = 5; i < 10; i++) {
            row[i].id = 0;
            row[i].group = 1;
            row[i].time = lbl_806D4790;
            row[i].best = lbl_806D4798;
        }
        RaceResult_StoreLatest_bss_805B256C.id = 0;
        extra->group = 0;
        extra->time = lbl_806D4790;
        extra->best = lbl_806D4798;
        SetCourseParams_bss_806D1280 = 4;
        SetCourseParams_bss_806D1258 = 1;
        RaceEntries_Reset(e);
    }

    g_ccClass = 0;
    g_nonFirstFinishFlag = 0;
    g_finalLapCoinJumpEnabled = 0;
    lbl_806D12E4[0] = 0;
    lbl_806D12E4[1] = 0;
    lbl_806D12E4[2] = 0;
}
#undef KartSlot
#undef RaceEntries_Reset
#undef RaceEntry
#undef RaceEntry_Init
#undef RankRow
#undef fn_8018CC64
#undef fn_801D7610
#undef g_ccClass
#undef g_consecutiveWinsTier
#undef g_courseVariantIdx
#undef g_cupId
#undef g_currentSceneState
#undef g_finalLapCoinJumpEnabled
#undef g_isCommHost
#undef g_isPcbHost
#undef g_localPcbRole
#undef g_longRoundFlag
#undef g_namCamFlag
#undef g_nonFirstFinishFlag
#undef g_raceStarted
#undef g_reverseRoundFlag
#undef SetCourseParams_data_806CF10C
#undef SetCourseParams_bss_806D1258
#undef SetCourseParams_bss_806D1280
#undef lbl_806D12AD
#undef lbl_806D12AE
#undef lbl_806D12AF
#undef lbl_806D12B0
#undef lbl_806D12C0
#undef SetCourseParams_bss_806D12D8
#undef lbl_806D12E4
#undef lbl_806D4790
#undef lbl_806D4798
#undef memset
#undef g_playerData
#undef SetCourseParams_bss_805AC600
#undef SetCourseParams_bss_805B24CC
#undef RaceResult_StoreLatest_bss_805B256C
#undef RaceSlot_ResetAll_bss_805D2938
#undef SetCourseParams_bss_805D2948
#pragma cplusplus off

/* ==== ProcessSystemTick.c ==== */
#define Frame_Begin Frame_Begin_p10
#define Frame_PostDrawOverlay Frame_PostDrawOverlay_p10
#define Frame_PostDraw_BackupBuffer Frame_PostDraw_BackupBuffer_p10
#define Frame_UpdatePerFrameState Frame_UpdatePerFrameState_p10
#define PCBComm_Process PCBComm_Process_p10
#define SpriteHandlePool_GC SpriteHandlePool_GC_p10
#define Timer_Decrement Timer_Decrement_p10
#pragma exceptions on
#pragma use_lmw_stmw off
/*
 * ProcessSystemTick @ 0x8009D5F8 (size 0x40).
 *
 * Per-frame system tick: fan-out wrapper that drives the frame-begin/end
 * helpers, the sprite-handle GC pass, the global decrementing timer, and the
 * PCB communication subsystem in a fixed order.
 *
 * The TU sits in `game` lib (CW 1.3.2). #pragma exceptions on/reset wraps
 * the function so CW auto-emits the extab/extabindex entries (matching the
 * AI_GetYaw / Vtable_CallSlot2.cpp pattern).
 */

extern void Frame_Begin(void);
extern void SpriteHandlePool_GC(void);
extern void Frame_PostDraw_BackupBuffer(void);
extern void Timer_Decrement(void);
extern void PCBComm_Process(int a, int b);
extern void Frame_PostDrawOverlay(void);
extern void Frame_UpdatePerFrameState(void);

#pragma exceptions on
void ProcessSystemTick(void) {
    Frame_Begin();
    SpriteHandlePool_GC();
    Frame_PostDraw_BackupBuffer();
    Timer_Decrement();
    PCBComm_Process(1, 1);
    Frame_PostDrawOverlay();
    Frame_UpdatePerFrameState();
}
#pragma exceptions on
#undef Frame_Begin
#undef Frame_PostDrawOverlay
#undef Frame_PostDraw_BackupBuffer
#undef Frame_UpdatePerFrameState
#undef PCBComm_Process
#undef SpriteHandlePool_GC
#undef Timer_Decrement
#pragma cplusplus off

/* ==== RaceContext_Dtor.c ==== */
#define MemoryManager_TimedFree MemoryManager_TimedFree_p11
#define PolymorphicOwner PolymorphicOwner_p11
#define RaceContextView RaceContextView_p11
#define SetCourseParams_data_8040E4D0 lbl_8040E4D0_p11
#define SetCourseParams_data_8040E4DC lbl_8040E4DC_p11
#define lbl_806D10A0 lbl_806D10A0_p11
#pragma exceptions off
#pragma use_lmw_stmw off
/* === extracted from auto_RaceContext_Dtor_text === */
/* Copy into the TU between forward decls and function bodies; */
/* keep emit order = target section layout (do not sort). */

/* --- extern decls: branch callees (bl/b targets) --- */
/* Open prototype (`extern void Foo();`) accepts any call signature; */
/* refine if the real prototype matters for header consumers. */
extern void MemoryManager_TimedFree(void *);

/* --- extern decls: sda21-referenced data --- */
C_REGION_END
#pragma cplusplus on
struct PolymorphicOwner {
    virtual ~PolymorphicOwner();
};
struct RaceContextView {
    void *vtable;
};
extern PolymorphicOwner *lbl_806D10A0;
#pragma cplusplus off
C_REGION_BEGIN

/* --- extern decls: large-data refs (@ha/@l pairs) --- */
/* Open array (`[]`) avoids sda21 strict-mode link errors when a future */
/* promote rewrites the asm_fn to C and references the symbol as `arr[i]`. */
extern unsigned int SetCourseParams_data_8040E4D0[];
extern unsigned int SetCourseParams_data_8040E4DC[];

/* --- function index (1 fns, .text 0x8009D638..0x8009D6CC) ---
 * [  0] 0x8009D638 size:0x94    global RaceContext_Dtor
 */

/* --- forward decls --- */
C_REGION_END
#pragma cplusplus on
extern "C" void *RaceContext_Dtor(RaceContextView *, short);
#pragma cplusplus off
C_REGION_BEGIN

/* --- extab (manual emit, .extab_user -> extab via objcopy) --- */
#pragma section R ".extab_user"
__declspec(section ".extab_user") static const unsigned char extab_RaceContext_Dtor[8] = {
    0x10, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

/* --- extabindex (manual emit, .extabindex_user -> extabindex via objcopy) --- */
#pragma section R ".extabindex_user"
__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_RaceContext_Dtor = {
    (void *)&RaceContext_Dtor, 0x00000094, (void *)extab_RaceContext_Dtor
};

/* --- asm function bodies (.text order = fn address order) --- */
C_REGION_END
#pragma cplusplus on
#pragma exceptions off
extern "C" void *RaceContext_Dtor(RaceContextView *self, short freeFlag) { /* 0x8009D638 size:0x94 */
    if (self != 0) {
        self->vtable = (void *)SetCourseParams_data_8040E4D0;
        delete lbl_806D10A0;
        lbl_806D10A0 = 0;
        if (self != 0) {
            self->vtable = (void *)SetCourseParams_data_8040E4DC;
        }
        if (freeFlag > 0) {
            MemoryManager_TimedFree(self);
        }
    }
    return self;
}
#pragma exceptions off
#pragma cplusplus off
C_REGION_BEGIN
#undef MemoryManager_TimedFree
#undef PolymorphicOwner
#undef RaceContextView
#undef SetCourseParams_data_8040E4D0
#undef SetCourseParams_data_8040E4DC
#undef lbl_806D10A0
#pragma cplusplus off

/* ==== RaceContext_InitDefaults.c ==== */
#define CreditMgr_GetCreditCount CreditMgr_GetCreditCount_p12
#define InitializeWideRow InitializeWideRow_p12
#define ItemTable_PopulateAliasedSlots ItemTable_PopulateAliasedSlots_p12
#define RaceAux RaceAux_p12
#define RaceContext RaceContext_p12
#define RaceContextBase RaceContextBase_p12
#define RaceSlot RaceSlot_p12
#define RaceWideRow RaceWideRow_p12
#define TitleTracker_GetOrCreateSingleton TitleTracker_GetOrCreateSingleton_p12
#define fn_8018CC64 fn_8018CC64_p12
#define fn_801D7610 fn_801D7610_p12
#define g_ccClass g_ccClass_p12
#define g_consecutiveWinsTier g_consecutiveWinsTier_p12
#define g_courseVariantIdx g_courseVariantIdx_p12
#define g_cupId g_cupId_p12
#define g_currentSceneState g_currentSceneState_p12
#define g_gameMode g_gameMode_p12
#define g_humanPlayerCount g_humanPlayerCount_p12
#define g_isCommHost g_isCommHost_p12
#define g_isPcbHost g_isPcbHost_p12
#define g_kartVariant g_kartVariant_p12
#define g_lakituStartAnimDone g_lakituStartAnimDone_p12
#define g_localPcbRole g_localPcbRole_p12
#define g_longRoundFlag g_longRoundFlag_p12
#define g_raceStarted g_raceStarted_p12
#define g_reverseRoundFlag g_reverseRoundFlag_p12
#define g_timerModeEnabled g_timerModeEnabled_p12
#define SetCourseParams_data_8040E4D0 lbl_8040E4D0_p12
#define SetCourseParams_data_8040E4DC lbl_8040E4DC_p12
#define lbl_80598A60 lbl_80598A60_p12
#define SetCourseParams_data_806CF10C lbl_806CF10C_p12
#define lbl_806CF110 lbl_806CF110_p12
#define lbl_806CF12C lbl_806CF12C_p12
#define lbl_806D117C lbl_806D117C_p12
#define SetCourseParams_bss_806D1258 lbl_806D1258_p12
#define RaceContext_InitDefaults_bss_806D1259 lbl_806D1259_p12
#define lbl_806D1264 lbl_806D1264_p12
#define SetCourseParams_bss_806D1280 lbl_806D1280_p12
#define lbl_806D1290 lbl_806D1290_p12
#define lbl_806D12B0 lbl_806D12B0_p12
#define SetCourseParams_bss_806D12D8 lbl_806D12D8_p12
#define lbl_806D12DC lbl_806D12DC_p12
#define lbl_806D12E1 lbl_806D12E1_p12
#define lbl_806D12E2 lbl_806D12E2_p12
#define lbl_806D12E4 lbl_806D12E4_p12
#define lbl_806D4790 lbl_806D4790_p12
#define lbl_806D4798 lbl_806D4798_p12
#define memset memset_p12
#pragma exceptions off
#pragma use_lmw_stmw off
/* Bounded genuine C++ retrofit draft: approach 2, 88.20822% text,
 * 1428B versus 1460B target. Natural DESTROYBASE r29 begins PC40;
 * saved range r24..31 and end PC554 differ from target r22..31/PC570.
 * Original exact ASM follows unchanged. This draft is NOT a promotion. */
C_REGION_END
#if 0
C_REGION_BEGIN
/* Genuine C++ reconstruction of the observed RaceContext constructor.
 * Only the vptr/base lifetime and global storage accesses are established.
 * Authoritative target/callee assembly was used (Ghidra unavailable). */
C_REGION_END
#pragma cplusplus on
#pragma exceptions on

extern "C" {
void ItemTable_PopulateAliasedSlots(void);
int CreditMgr_GetCreditCount(int);
void *TitleTracker_GetOrCreateSingleton(void);
void fn_8018CC64(void);
void fn_801D7610(void *, unsigned char);
void *memset(void *, int, unsigned long);
extern int g_ccClass, g_consecutiveWinsTier, g_courseVariantIdx, g_cupId;
extern int g_currentSceneState, g_gameMode, g_humanPlayerCount, g_kartVariant;
extern int g_localPcbRole, g_longRoundFlag, g_reverseRoundFlag, g_timerModeEnabled;
extern int SetCourseParams_data_806CF10C, lbl_806CF110, lbl_806CF12C, SetCourseParams_bss_806D1280, SetCourseParams_bss_806D12D8;
extern unsigned char g_isCommHost, g_isPcbHost, g_lakituStartAnimDone, g_raceStarted;
extern unsigned char lbl_806D117C, SetCourseParams_bss_806D1258, RaceContext_InitDefaults_bss_806D1259, lbl_806D1290;
extern unsigned char lbl_806D12B0, lbl_806D12E1, lbl_806D12E2;
extern unsigned char lbl_806D1264[3], lbl_806D12E4[3];
extern unsigned char lbl_80598A60[];
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
#include "game/types/RaceSlot.h"
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

RaceContext::RaceContext() {
    unsigned char *farBank = SetCourseParams_bss_805AC600 + 0x20000;
    unsigned char *storage = SetCourseParams_bss_805AC600;
    RaceSlot *slots = (RaceSlot *)storage;

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
#pragma exceptions off
#pragma cplusplus off
#endif
C_REGION_BEGIN

/* === extracted from auto_RaceContext_InitDefa_text === */
/* Copy into the TU between forward decls and function bodies; */
/* keep emit order = target section layout (do not sort). */

/* --- extern decls: branch callees (bl/b targets) --- */
/* Open prototype (`extern void Foo();`) accepts any call signature; */
/* refine if the real prototype matters for header consumers. */
#ifdef NON_MATCHING
extern int CreditMgr_GetCreditCount(int idx);
extern void ItemTable_PopulateAliasedSlots(void);
extern void *TitleTracker_GetOrCreateSingleton(void);
extern void fn_8018CC64(void);
extern void fn_801D7610(void *playerData, unsigned char flag);
extern void *memset(void *dst, int c, unsigned long n);
#else
extern void CreditMgr_GetCreditCount();
extern void ItemTable_PopulateAliasedSlots();
extern void TitleTracker_GetOrCreateSingleton();
extern void fn_8018CC64();
extern void fn_801D7610();
extern void memset();
#endif

/* --- extern decls: sda21-referenced data --- */
extern unsigned int g_ccClass;
extern unsigned int g_consecutiveWinsTier;
extern unsigned int g_courseVariantIdx;
extern unsigned int g_cupId;
extern unsigned int g_currentSceneState;
extern unsigned int g_gameMode;
extern unsigned int g_humanPlayerCount;
extern unsigned int g_isCommHost;
extern unsigned int g_isPcbHost;
extern unsigned int g_kartVariant;
extern unsigned int g_lakituStartAnimDone;
extern unsigned int g_localPcbRole;
extern unsigned int g_longRoundFlag;
extern unsigned int g_raceStarted;
extern unsigned int g_reverseRoundFlag;
extern unsigned int g_timerModeEnabled;
extern unsigned int SetCourseParams_data_806CF10C;
extern unsigned int lbl_806CF110;
extern unsigned int lbl_806CF12C;
extern unsigned int lbl_806D117C;
extern unsigned int SetCourseParams_bss_806D1258;
extern unsigned int RaceContext_InitDefaults_bss_806D1259;
extern unsigned int lbl_806D1264;
extern unsigned int SetCourseParams_bss_806D1280;
extern unsigned int lbl_806D1290;
extern unsigned int lbl_806D12B0;
extern unsigned int SetCourseParams_bss_806D12D8;
extern unsigned int lbl_806D12DC;
extern unsigned int lbl_806D12E1;
extern unsigned int lbl_806D12E2;
extern unsigned int lbl_806D12E4;
extern unsigned int lbl_806D4790;
extern unsigned int lbl_806D4798;

/* --- extern decls: large-data refs (@ha/@l pairs) --- */
/* Open array (`[]`) avoids sda21 strict-mode link errors when a future */
/* promote rewrites the asm_fn to C and references the symbol as `arr[i]`. */
extern unsigned int SetCourseParams_data_8040E4D0[];
extern unsigned int SetCourseParams_data_8040E4DC[];
extern unsigned int lbl_80598A60[];

/* --- function index (1 fns, .text 0x8009D6CC..0x8009DC80) ---
 * [  0] 0x8009D6CC size:0x5B4   global RaceContext_InitDefaults
 */

/* --- forward decls --- */
#ifdef NON_MATCHING
void *RaceContext_InitDefaults(void *self);
#else
void RaceContext_InitDefaults(void);
#endif

/* --- extern decls: extab symbolic refs (dtors / typeids) --- */
C_REGION_END
#pragma cplusplus on
struct RaceContext_p13;
extern "C" RaceContext_p13 *dtor_8009DCE0(RaceContext_p13 *, short);
#pragma cplusplus off
C_REGION_BEGIN

/* --- extab (manual emit, .extab_user -> extab via objcopy) --- */
#pragma section R ".extab_user"
__declspec(section ".extab_user") static const struct { unsigned int f0; unsigned int f1; unsigned int f2; unsigned int f3; unsigned int f4; unsigned int f5; void *f6; } extab_RaceContext_InitDefaults = { 0x500A0000, 0x00000040, 0x014C0010, 0x00000000, 0x8680001D, 0x00000000, (void *)&dtor_8009DCE0 };

/* --- extabindex (manual emit, .extabindex_user -> extabindex via objcopy) --- */
#pragma section R ".extabindex_user"
__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_RaceContext_InitDefaults = {
    (void *)&RaceContext_InitDefaults, 0x000005B4, (void *)&extab_RaceContext_InitDefaults
};

/* --- asm function bodies (.text order = fn address order) --- */
#ifdef NON_MATCHING
/* NON_MATCHING: equivalent C for the RaceContext ctor, 75 % (the rank-row loop is
 * not unrolled, savegpr instead of stmw; the C++ ctor draft
 * notes/merge_gen/SetCourseParams/InitDefaults_draft_v1_93.79.txt is closer): resets the race
 * globals, the kart slot table and (once) the rank rows. Globals are reached
 * through width casts because this part of the merged TU declares them as words. */
typedef struct NMKartSlot {
    int driverId, charId, field8, fieldC, kartVariant;
    unsigned char items[3], pad17;
} NMKartSlot;
typedef struct NMRaceAux {
    int value, enabled;
    float current, limit;
} NMRaceAux;
typedef struct NMRaceWideRow {
    unsigned char active, pad1;
    unsigned short count;
    unsigned char pad4[12];
    int selection, state;
    unsigned char flag18, flag19, pad1A[2];
    int value;
    float x, y;
    unsigned char enabled, pad29[3];
} NMRaceWideRow;
#define NM_B(x) (*(unsigned char *)&(x))
#define NM_I(x) (*(int *)&(x))
#define NM_A(x) ((unsigned char *)&(x))
static void NM_InitializeWideRow(NMRaceWideRow *row) {
    row->active = 0;
    row->count = 0;
    row->selection = -1;
    row->state = -1;
    row->flag18 = 0;
    row->flag19 = 0;
    row->value = 0;
    row->x = 0.0f;
    row->y = 0.0f;
    row->enabled = 1;
}
void *RaceContext_InitDefaults(void *self) {
    int i;
    int j;
    unsigned char noCredit;
    NMKartSlot *slots = (NMKartSlot *)(void *)SetCourseParams_bss_805AC600;
    int *counters = (int *)(void *)RaceSlot_ResetAll_bss_805D2938;
    NMRaceAux *latest = (NMRaceAux *)(void *)RaceResult_StoreLatest_bss_805B256C;

    /* base-class ctor, then the derived vtable */
    *(void **)self = (void *)SetCourseParams_data_8040E4DC;
    *(void **)&lbl_806D12DC = self;
    *(void **)self = (void *)SetCourseParams_data_8040E4D0;

    ItemTable_PopulateAliasedSlots();
    if (NM_B(RaceContext_InitDefaults_bss_806D1259) != 1) {
        for (i = 0; i <= 3; i++) {
            memset((unsigned char *)(void *)SetCourseParams_bss_805B2580 + i * 0x8000, (signed char)((signed char)((unsigned char *)(void *)lbl_80598A60)[0x21] - 1), 0x8000);
        }
        NM_B(RaceContext_InitDefaults_bss_806D1259) = 1;
    }

    NM_I(g_timerModeEnabled) = 1;
    NM_I(g_cupId) = 1;
    NM_I(g_longRoundFlag) = 0;
    NM_I(g_courseVariantIdx) = 0;
    NM_I(g_reverseRoundFlag) = 0;
    for (i = 0; i < 8; i++) {
        slots[i].driverId = -1;
        slots[i].charId = -1;
        slots[i].field8 = 1;
        slots[i].items[0] = 0x24;
        slots[i].items[1] = 0x25;
        slots[i].items[2] = 0x26;
        slots[i].kartVariant = 0;
        counters[i] = 0;
    }
    if (NM_I(g_cupId) >= 0 && NM_I(g_longRoundFlag) >= 0) {
        NM_B(g_raceStarted) = 0;
    }

    NM_I(SetCourseParams_data_806CF10C) = 0;
    if (!NM_B(SetCourseParams_bss_806D1258)) {
        NMRaceAux *row = (NMRaceAux *)(void *)SetCourseParams_bss_805B24CC;
        NMRaceWideRow *e = (NMRaceWideRow *)(void *)SetCourseParams_bss_805D2948;
        for (i = 0; i < 5; i++) {
            row[i].value = 0;
            row[i].enabled = 0;
            row[i].current = 0.0f;
            row[i].limit = 1000.0f;
        }
        for (i = 5; i < 10; i++) {
            row[i].value = 0;
            row[i].enabled = 1;
            row[i].current = 0.0f;
            row[i].limit = 1000.0f;
        }
        latest->value = 0;
        latest->enabled = 0;
        latest->current = 0.0f;
        latest->limit = 1000.0f;
        NM_I(SetCourseParams_bss_806D1280) = 4;
        NM_B(SetCourseParams_bss_806D1258) = 1;
        for (j = 0; j < 8; j++) {
            NM_InitializeWideRow(&e[j]);
        }
        NM_I(SetCourseParams_bss_806D12D8) = 0;
    }

    NM_I(g_ccClass) = 0;
    for (i = 0; i < 7; i++) {
        slots[i].driverId = 6;
        slots[i].charId = i + 1;
        slots[i].field8 = 1;
        slots[i].fieldC = 0;
        slots[i].kartVariant = 0;
    }
    slots[7].driverId = 0;
    slots[7].charId = 0;
    slots[7].field8 = 1;
    slots[7].fieldC = 0;
    slots[7].kartVariant = 0;
    slots[7].items[0] = 0x2B;
    slots[7].items[1] = 0x2D;
    slots[7].items[2] = 0x32;
    NM_A(lbl_806D1264)[0] = 0x2B;
    NM_A(lbl_806D1264)[1] = 0x2D;
    NM_A(lbl_806D1264)[2] = 0x32;
    NM_B(g_lakituStartAnimDone) = 0;
    NM_B(lbl_806D1290) = 0;
    NM_I(lbl_806CF110) = 1;
    NM_I(g_gameMode) = 0;
    NM_B(g_isCommHost) = 0;
    NM_I(g_currentSceneState) = 2;
    NM_B(g_isPcbHost) = 0;
    NM_I(g_localPcbRole) = 0;
    NM_B(lbl_806D12B0) = 0;
    NM_I(g_kartVariant) = -1;
    NM_I(g_humanPlayerCount) = -1;
    NM_I(g_consecutiveWinsTier) = 0;
    NM_I(lbl_806CF12C) = -1;
    memset((void *)g_playerData, 0, 0x1DC);
    fn_801D7610((void *)g_playerData, 1);
    fn_8018CC64();
    TitleTracker_GetOrCreateSingleton();
    noCredit = CreditMgr_GetCreditCount(0) <= 0; /* target: (1 rotl cntlzw(n)) & 1 */
    NM_B(lbl_806D12E1) = 0;
    NM_B(lbl_806D117C) = noCredit;
    NM_B(lbl_806D12E2) = 0;
    NM_A(lbl_806D12E4)[0] = 0;
    NM_A(lbl_806D12E4)[1] = 0;
    NM_A(lbl_806D12E4)[2] = 0;
    return self;
}
#undef NM_B
#undef NM_I
#undef NM_A
#else
asm void RaceContext_InitDefaults(void) { /* 0x8009D6CC size:0x5B4 */
    nofralloc
    stwu r1, -0x30(r1)
    mflr r0
    lis r5, SetCourseParams_data_8040E4DC@ha
    lis r4, SetCourseParams_data_8040E4D0@ha
    stw r0, 0x34(r1)
    lis r6, SetCourseParams_bss_805AC600@ha
    addi r0, r4, SetCourseParams_data_8040E4D0@l
    stmw r22, 0x8(r1)
    mr r29, r3
    addi r3, r5, SetCourseParams_data_8040E4DC@l
    addi r30, r6, SetCourseParams_bss_805AC600@l
    addis r31, r30, 0x2
    stw r3, 0x0(r29)
    stw r29, lbl_806D12DC(r13)
    stw r0, 0x0(r29)
    bl ItemTable_PopulateAliasedSlots
    lbz r0, RaceContext_InitDefaults_bss_806D1259(r13)
    cmplwi r0, 0x1
    beq RaceContext_InitDefaults_L_8009D768
    lis r4, SetCourseParams_bss_805B2580@ha
    lis r3, lbl_80598A60@ha
    addi r24, r4, SetCourseParams_bss_805B2580@l
    li r25, 0x0
    addi r23, r3, lbl_80598A60@l
    lis r22, 0x1
    RaceContext_InitDefaults_L_8009D730:
    lbz r0, 0x21(r23)
    mr r3, r24
    addi r5, r22, -0x8000
    extsb r4, r0
    subi r0, r4, 0x1
    extsb r4, r0
    bl memset
    addi r25, r25, 0x1
    addis r24, r24, 0x1
    cmpwi r25, 0x3
    addi r24, r24, -0x8000
    ble RaceContext_InitDefaults_L_8009D730
    li r0, 0x1
    stb r0, RaceContext_InitDefaults_bss_806D1259(r13)
    RaceContext_InitDefaults_L_8009D768:
    li r8, 0x0
    addi r6, r30, 0x0
    li r7, -0x1
    li r9, 0x1
    li r5, 0x24
    li r4, 0x25
    li r0, 0x26
    addi r3, r31, 0x6338
    stw r9, g_timerModeEnabled(r13)
    stw r9, g_cupId(r13)
    stw r8, g_longRoundFlag(r13)
    stw r8, g_courseVariantIdx(r13)
    stw r8, g_reverseRoundFlag(r13)
    stw r7, 0x0(r30)
    stw r7, 0x4(r6)
    stw r9, 0x8(r6)
    stb r5, 0x14(r6)
    stb r4, 0x15(r6)
    stb r0, 0x16(r6)
    stw r8, 0x10(r6)
    stw r8, 0x6338(r31)
    stw r7, 0x18(r6)
    stw r7, 0x1c(r6)
    stw r9, 0x20(r6)
    stb r5, 0x2c(r6)
    stb r4, 0x2d(r6)
    stb r0, 0x2e(r6)
    stw r8, 0x28(r6)
    stw r8, 0x4(r3)
    stw r7, 0x30(r6)
    stw r7, 0x34(r6)
    stw r9, 0x38(r6)
    stb r5, 0x44(r6)
    stb r4, 0x45(r6)
    stb r0, 0x46(r6)
    stw r8, 0x40(r6)
    stw r8, 0x8(r3)
    stw r7, 0x48(r6)
    stw r7, 0x4c(r6)
    stw r9, 0x50(r6)
    stb r5, 0x5c(r6)
    stb r4, 0x5d(r6)
    stb r0, 0x5e(r6)
    stw r8, 0x58(r6)
    stw r8, 0xc(r3)
    stw r7, 0x60(r6)
    stw r7, 0x64(r6)
    stw r9, 0x68(r6)
    stb r5, 0x74(r6)
    stb r4, 0x75(r6)
    stb r0, 0x76(r6)
    stw r8, 0x70(r6)
    stw r8, 0x10(r3)
    stw r7, 0x78(r6)
    stw r7, 0x7c(r6)
    stw r9, 0x80(r6)
    stb r5, 0x8c(r6)
    stb r4, 0x8d(r6)
    stb r0, 0x8e(r6)
    stw r8, 0x88(r6)
    stw r8, 0x14(r3)
    stw r7, 0x90(r6)
    stw r7, 0x94(r6)
    stw r9, 0x98(r6)
    stb r5, 0xa4(r6)
    stb r4, 0xa5(r6)
    stb r0, 0xa6(r6)
    stw r8, 0xa0(r6)
    stw r8, 0x18(r3)
    stw r7, 0xa8(r6)
    stw r7, 0xac(r6)
    stw r9, 0xb0(r6)
    stb r5, 0xbc(r6)
    stb r4, 0xbd(r6)
    stb r0, 0xbe(r6)
    stw r8, 0xb8(r6)
    stw r8, 0x1c(r3)
    lwz r0, g_cupId(r13)
    cmpwi r0, 0x0
    blt RaceContext_InitDefaults_L_8009D8B8
    lwz r0, g_longRoundFlag(r13)
    cmpwi r0, 0x0
    blt RaceContext_InitDefaults_L_8009D8B8
    stb r8, g_raceStarted(r13)
    RaceContext_InitDefaults_L_8009D8B8:
    lbz r0, SetCourseParams_bss_806D1258(r13)
    li r5, 0x0
    stw r5, SetCourseParams_data_806CF10C(r13)
    cmplwi r0, 0x0
    bne RaceContext_InitDefaults_L_8009DAE8
    addi r9, r30, 0x5ecc
    addi r8, r31, 0x6348
    stw r5, 0x0(r9)
    li r0, -0x1
    lfs f1, lbl_806D4790(r2)
    li r7, 0x1
    stw r5, 0x4(r9)
    addi r4, r30, 0x5f6c
    lfs f0, lbl_806D4798(r2)
    li r3, 0x4
    stfs f1, 0x8(r9)
    stfs f0, 0xc(r9)
    stw r5, 0x10(r9)
    stw r5, 0x14(r9)
    stfs f1, 0x18(r9)
    stfs f0, 0x1c(r9)
    stw r5, 0x20(r9)
    stw r5, 0x24(r9)
    stfs f1, 0x28(r9)
    stfs f0, 0x2c(r9)
    stw r5, 0x30(r9)
    stw r5, 0x34(r9)
    stfs f1, 0x38(r9)
    stfs f0, 0x3c(r9)
    stw r5, 0x40(r9)
    stw r5, 0x44(r9)
    stfs f1, 0x48(r9)
    stfs f0, 0x4c(r9)
    stw r5, 0x50(r9)
    stw r7, 0x54(r9)
    stfs f1, 0x58(r9)
    stfs f0, 0x5c(r9)
    stw r5, 0x60(r9)
    stw r7, 0x64(r9)
    stfs f1, 0x68(r9)
    stfs f0, 0x6c(r9)
    stw r5, 0x70(r9)
    stw r7, 0x74(r9)
    stfs f1, 0x78(r9)
    stfs f0, 0x7c(r9)
    stw r5, 0x80(r9)
    stw r7, 0x84(r9)
    stfs f1, 0x88(r9)
    stfs f0, 0x8c(r9)
    stw r5, 0x90(r9)
    stw r7, 0x94(r9)
    stfs f1, 0x98(r9)
    stfs f0, 0x9c(r9)
    stw r5, 0x5f6c(r30)
    stw r5, 0x4(r4)
    stfs f1, 0x8(r4)
    stfs f0, 0xc(r4)
    stw r3, SetCourseParams_bss_806D1280(r13)
    stb r7, SetCourseParams_bss_806D1258(r13)
    stb r5, 0x0(r8)
    sth r5, 0x2(r8)
    stw r0, 0x10(r8)
    stw r0, 0x14(r8)
    stb r5, 0x18(r8)
    stb r5, 0x19(r8)
    stw r5, 0x1c(r8)
    stfs f1, 0x20(r8)
    stfs f1, 0x24(r8)
    stb r7, 0x28(r8)
    stb r5, 0x2c(r8)
    sth r5, 0x2e(r8)
    stw r0, 0x3c(r8)
    stw r0, 0x40(r8)
    stb r5, 0x44(r8)
    stb r5, 0x45(r8)
    stw r5, 0x48(r8)
    stfs f1, 0x4c(r8)
    stfs f1, 0x50(r8)
    stb r7, 0x54(r8)
    stb r5, 0x58(r8)
    sth r5, 0x5a(r8)
    stw r0, 0x68(r8)
    stw r0, 0x6c(r8)
    stb r5, 0x70(r8)
    stb r5, 0x71(r8)
    stw r5, 0x74(r8)
    stfs f1, 0x78(r8)
    stfs f1, 0x7c(r8)
    stb r7, 0x80(r8)
    stb r5, 0x84(r8)
    sth r5, 0x86(r8)
    stw r0, 0x94(r8)
    stw r0, 0x98(r8)
    stb r5, 0x9c(r8)
    stb r5, 0x9d(r8)
    stw r5, 0xa0(r8)
    stfs f1, 0xa4(r8)
    stfs f1, 0xa8(r8)
    stb r7, 0xac(r8)
    stb r5, 0xb0(r8)
    sth r5, 0xb2(r8)
    stw r0, 0xc0(r8)
    stw r0, 0xc4(r8)
    stb r5, 0xc8(r8)
    stb r5, 0xc9(r8)
    stw r5, 0xcc(r8)
    stfs f1, 0xd0(r8)
    stfs f1, 0xd4(r8)
    stb r7, 0xd8(r8)
    stb r5, 0xdc(r8)
    sth r5, 0xde(r8)
    stw r0, 0xec(r8)
    stw r0, 0xf0(r8)
    stb r5, 0xf4(r8)
    stb r5, 0xf5(r8)
    stw r5, 0xf8(r8)
    stfs f1, 0xfc(r8)
    stfs f1, 0x100(r8)
    stb r7, 0x104(r8)
    stb r5, 0x108(r8)
    sth r5, 0x10a(r8)
    stw r0, 0x118(r8)
    stw r0, 0x11c(r8)
    stb r5, 0x120(r8)
    stb r5, 0x121(r8)
    stw r5, 0x124(r8)
    stfs f1, 0x128(r8)
    stfs f1, 0x12c(r8)
    stb r7, 0x130(r8)
    stb r5, 0x134(r8)
    sth r5, 0x136(r8)
    stw r0, 0x144(r8)
    stw r0, 0x148(r8)
    stb r5, 0x14c(r8)
    stb r5, 0x14d(r8)
    stw r5, 0x150(r8)
    stfs f1, 0x154(r8)
    stfs f1, 0x158(r8)
    stb r7, 0x15c(r8)
    stw r5, SetCourseParams_bss_806D12D8(r13)
    RaceContext_InitDefaults_L_8009DAE8:
    li r22, 0x0
    li r24, 0x1
    addi r25, r30, 0x0
    li r23, 0x6
    li r0, -0x1
    li r26, 0x2
    li r10, 0x2b
    li r27, 0x3
    li r28, 0x4
    li r12, 0x5
    li r11, 0x7
    li r9, 0x2d
    li r8, 0x32
    la r7, lbl_806D1264(r13)  /* lbl_806D1264 */
    stw r22, g_ccClass(r13)
    addi r3, r31, 0x5f80
    li r4, 0x0
    li r5, 0x1dc
    stw r23, 0x0(r30)
    stw r24, 0x4(r6)
    stw r24, 0x8(r6)
    stw r22, 0xc(r25)
    stw r22, 0x10(r6)
    stw r23, 0x18(r6)
    stw r26, 0x1c(r6)
    stw r24, 0x20(r6)
    stw r22, 0x24(r25)
    stw r22, 0x28(r6)
    stw r23, 0x30(r6)
    stw r27, 0x34(r6)
    stw r24, 0x38(r6)
    stw r22, 0x3c(r25)
    stw r22, 0x40(r6)
    stw r23, 0x48(r6)
    stw r28, 0x4c(r6)
    stw r24, 0x50(r6)
    stw r22, 0x54(r25)
    stw r22, 0x58(r6)
    stw r23, 0x60(r6)
    stw r12, 0x64(r6)
    stw r24, 0x68(r6)
    stw r22, 0x6c(r25)
    stw r22, 0x70(r6)
    stw r23, 0x78(r6)
    stw r23, 0x7c(r6)
    stw r24, 0x80(r6)
    stw r22, 0x84(r25)
    stw r22, 0x88(r6)
    stw r23, 0x90(r6)
    stw r11, 0x94(r6)
    stw r24, 0x98(r6)
    stw r22, 0x9c(r25)
    stw r22, 0xa0(r6)
    stw r22, 0xa8(r6)
    stw r22, 0xac(r6)
    stw r24, 0xb0(r6)
    stw r22, 0xb4(r25)
    stw r22, 0xb8(r6)
    stb r10, 0xbc(r6)
    stb r9, 0xbd(r6)
    stb r8, 0xbe(r6)
    stb r10, lbl_806D1264(r13)
    stb r9, 0x1(r7)
    stb r8, 0x2(r7)
    stb r22, g_lakituStartAnimDone(r13)
    stb r22, lbl_806D1290(r13)
    stw r24, lbl_806CF110(r13)
    stw r22, g_gameMode(r13)
    stb r22, g_isCommHost(r13)
    stw r26, g_currentSceneState(r13)
    stb r22, g_isPcbHost(r13)
    stw r22, g_localPcbRole(r13)
    stb r22, lbl_806D12B0(r13)
    stw r0, g_kartVariant(r13)
    stw r0, g_humanPlayerCount(r13)
    stw r22, g_consecutiveWinsTier(r13)
    stw r0, lbl_806CF12C(r13)
    bl memset
    addi r3, r31, 0x5f80
    li r4, 0x1
    bl fn_801D7610
    bl fn_8018CC64
    bl TitleTracker_GetOrCreateSingleton
    li r3, 0x0
    bl CreditMgr_GetCreditCount
    cntlzw r3, r3
    li r5, 0x1
    li r0, 0x0
    la r4, lbl_806D12E4(r13)  /* lbl_806D12E4 */
    rlwnm r5, r5, r3, 31, 31
    stb r0, lbl_806D12E1(r13)
    mr r3, r29
    stb r5, lbl_806D117C(r13)
    stb r0, lbl_806D12E2(r13)
    stb r0, lbl_806D12E4(r13)
    stb r0, 0x1(r4)
    stb r0, 0x2(r4)
    lmw r22, 0x8(r1)
    lwz r0, 0x34(r1)
    mtlr r0
    addi r1, r1, 0x30
    blr
}
#endif
#undef CreditMgr_GetCreditCount
#undef InitializeWideRow
#undef ItemTable_PopulateAliasedSlots
#undef RaceAux
#undef RaceContext
#undef RaceContextBase
#undef RaceSlot
#undef RaceWideRow
#undef TitleTracker_GetOrCreateSingleton
#undef fn_8018CC64
#undef fn_801D7610
#undef g_ccClass
#undef g_consecutiveWinsTier
#undef g_courseVariantIdx
#undef g_cupId
#undef g_currentSceneState
#undef g_gameMode
#undef g_humanPlayerCount
#undef g_isCommHost
#undef g_isPcbHost
#undef g_kartVariant
#undef g_lakituStartAnimDone
#undef g_localPcbRole
#undef g_longRoundFlag
#undef g_raceStarted
#undef g_reverseRoundFlag
#undef g_timerModeEnabled
#undef SetCourseParams_data_8040E4D0
#undef SetCourseParams_data_8040E4DC
#undef lbl_80598A60
#undef SetCourseParams_data_806CF10C
#undef lbl_806CF110
#undef lbl_806CF12C
#undef lbl_806D117C
#undef SetCourseParams_bss_806D1258
#undef RaceContext_InitDefaults_bss_806D1259
#undef lbl_806D1264
#undef SetCourseParams_bss_806D1280
#undef lbl_806D1290
#undef lbl_806D12B0
#undef SetCourseParams_bss_806D12D8
#undef lbl_806D12DC
#undef lbl_806D12E1
#undef lbl_806D12E2
#undef lbl_806D12E4
#undef lbl_806D4790
#undef lbl_806D4798
#undef memset
#pragma cplusplus off

/* ==== RaceContext_EnsureSingleton.c ==== */
#define RaceContext RaceContext_p13
#define SetCourseParams_data_8040E4DC lbl_8040E4DC_p13
#define lbl_806D12DC lbl_806D12DC_p13
#pragma exceptions on
#pragma use_lmw_stmw off
#include "game/singleton.h"
/* Lazily created race context singleton and its deleting destructor. */
C_REGION_END
#pragma cplusplus on

struct RaceContext {
    void *vtable;
    RaceContext();
};

extern "C" {
void MemoryManager_TimedFree(void *p);
extern RaceContext *lbl_806D12DC;
extern void *SetCourseParams_data_8040E4DC[];
}

extern "C" RaceContext *RaceContext_EnsureSingleton(void)
{
    RaceContext *instance = SINGLETON_INSTANCE(lbl_806D12DC);
    if (instance == 0) {
        new RaceContext;
    }
    return SINGLETON_INSTANCE(lbl_806D12DC);
}

extern "C" RaceContext *dtor_8009DCE0(RaceContext *self, short flag)
{
    if (self) {
        self->vtable = SetCourseParams_data_8040E4DC;
        if (flag > 0) {
            MemoryManager_TimedFree(self);
        }
    }
    return self;
}
#undef RaceContext
#undef SetCourseParams_data_8040E4DC
#undef lbl_806D12DC
#pragma cplusplus off
C_REGION_BEGIN

/* ==== KartDriverArray_StaticCtor.c ==== */
#define RaceContextArray_Dtor RaceContextArray_Dtor_p14
#define RaceContextArray_Init RaceContextArray_Init_p14
#define __register_global_object __register_global_object_p14
#define KartDriverArray_StaticCtor_bss_805AC6C0 ((unsigned char *)KartDriverArray_StaticCtor_bss_805AC6C0)
#define SetCourseParams_bss_805AC6CC ((unsigned char *)SetCourseParams_bss_805AC6CC)
#pragma exceptions on
#pragma use_lmw_stmw off
extern void *RaceContextArray_Init(void *);
extern void *RaceContextArray_Dtor(void *, short);
extern void __register_global_object(void *object, void *dtor, void *regmem);

void KartDriverArray_StaticCtor(void)
{
    __register_global_object(RaceContextArray_Init(SetCourseParams_bss_805AC6CC), RaceContextArray_Dtor, KartDriverArray_StaticCtor_bss_805AC6C0);
}

__declspec(section ".ctors") static void (*const s_KartDriverArray_StaticCtor_ctor)(void) = KartDriverArray_StaticCtor;
#undef RaceContextArray_Dtor
#undef RaceContextArray_Init
#undef __register_global_object
#undef KartDriverArray_StaticCtor_bss_805AC6C0
#undef SetCourseParams_bss_805AC6CC
#pragma cplusplus off
C_REGION_END
