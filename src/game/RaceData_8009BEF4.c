/* Race/course data accessors (0x8009BEF4..0x8009CBFC): display buffers,
 * race result ranking, the per-course data table (lbl_8040B90C, indexed
 * [cup][longRound], with per-reverse and per-variant sub-arrays), kart
 * slots and debug overlay labels. */

typedef struct Vec3f {
    float x, y, z;
} Vec3f;

typedef struct RankEntry {
    int a;
    int b;
    float score;
    float time;
} RankEntry;

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

typedef struct KartSlot {
    int driverId;               /* 0x00 */
    int charId;                 /* 0x04 */
    int field8;                 /* 0x08 */
    int fieldC;                 /* 0x0C */
    int kartVariant;            /* 0x10 */
    unsigned char items[3];     /* 0x14 */
    unsigned char pad17;
} KartSlot;

typedef struct CharacterData {
    void *name;
    unsigned char rest[0x28];
} CharacterData;

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
extern void *lbl_806D1278;
extern void *lbl_806D1280;
extern const float lbl_806D4790;

extern unsigned char lbl_805B2580[];
extern DisplayState lbl_80598A60;
extern RankEntry lbl_805B256C;
extern RankEntry lbl_805B24CC[2][5];
extern unsigned char lbl_805AC6CC[];
extern CourseData lbl_8040B90C[][2];
extern void *lbl_8040B218[][2][2][2];
extern KartSlot lbl_805AC600[8];
extern int lbl_805D2938[8];
extern unsigned char lbl_80401118[];
extern CharacterData g_characterDataTable[15];
extern void *lbl_8040E1C4[4];
extern void *lbl_806CF100[2];
extern void *lbl_8040B318[17];

void *GetDisplayContext(int i)
{
    if (i < 0 || i > 3) {
        return 0;
    }
    return lbl_805B2580 + (i << 15);
}

int GetDisplayBufferIndex(void)
{
    return lbl_80598A60.bufferIndex - 1;
}

void SetRaceResultLatestPtr(void *p)
{
    lbl_806D1280 = p;
}

void RaceResult_StoreLatest(int a, int b, float score, float time)
{
    lbl_805B256C.a = a;
    lbl_805B256C.b = b;
    lbl_805B256C.score = score;
    lbl_805B256C.time = time;
}

RankEntry *RaceResult_GetRankEntry(int i)
{
    if (i < 0 || i >= 5) {
        return 0;
    }
    return &lbl_805B24CC[g_longRoundFlag][i];
}

int RaceResult_InsertSortedRank(int a, int b, float score, float time)
{
    RankEntry *e;
    int off;
    int i;
    int j;

    off = g_longRoundFlag * 0x50;
    e = (RankEntry *)((unsigned char *)lbl_805B24CC + off);

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
        unsigned char *u = (unsigned char *)lbl_805B24CC;
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
    return lbl_805AC6CC;
}

void SetPlayerCarObject(void *p)
{
    lbl_806D1278 = p;
}

void *GetPlayerCarObject(void)
{
    return lbl_806D1278;
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
    return lbl_8040B90C[g_cupId][g_longRoundFlag].dir[g_reverseRoundFlag].bgmPath;
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
        return lbl_8040B218[cup][lr][rev][cc];
    }
    return lbl_8040B218[cup][lr][rev][0];
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
    return lbl_8040B90C[g_cupId][g_longRoundFlag].dir[g_reverseRoundFlag].bgm[g_courseVariantIdx];
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
    return lbl_8040B90C[g_cupId][g_longRoundFlag].variantTable[g_courseVariantIdx];
}

void *GetFinishLineSegment(void)
{
    if (g_cupId < 0) {
        return 0;
    }
    if (g_longRoundFlag < 0) {
        return 0;
    }
    return lbl_8040B90C[g_cupId][g_longRoundFlag].dir[g_reverseRoundFlag].finishLine;
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
        return lbl_8040B90C[g_cupId][g_longRoundFlag].dir[g_reverseRoundFlag].model[g_courseVariantIdx];
    }
    return lbl_8040B90C[g_cupId][g_longRoundFlag].dir[g_reverseRoundFlag].modelTimer[g_courseVariantIdx];
}

void *GetCourseObjectTable(void)
{
    if (g_cupId < 0) {
        return 0;
    }
    if (g_longRoundFlag < 0) {
        return 0;
    }
    return lbl_8040B90C[g_cupId][g_longRoundFlag].dir[g_reverseRoundFlag].objectTable[g_courseVariantIdx];
}

void *GetCollisionFilename(void)
{
    if (g_cupId < 0) {
        return 0;
    }
    if (g_longRoundFlag < 0) {
        return 0;
    }
    return lbl_8040B90C[g_cupId][g_longRoundFlag].dir[g_reverseRoundFlag].collision[g_courseVariantIdx];
}

void *GetJointNameTable(void)
{
    if (g_cupId < 0) {
        return 0;
    }
    if (g_longRoundFlag < 0) {
        return 0;
    }
    return lbl_8040B90C[g_cupId][g_longRoundFlag].jointNames[g_courseVariantIdx];
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
    return lbl_8040B90C[g_cupId][g_longRoundFlag].collisionBin[g_courseVariantIdx];
}

float GetCourseStartYaw(void)
{
    if (g_cupId < 0) {
        return lbl_806D4790;
    }
    if (g_longRoundFlag < 0) {
        return lbl_806D4790;
    }
    return lbl_8040B90C[g_cupId][g_longRoundFlag].dir[g_reverseRoundFlag].startYaw;
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
    return &lbl_8040B90C[g_cupId][g_longRoundFlag].dir[g_reverseRoundFlag].startPos[i];
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
        if (driver == lbl_805AC600[i].driverId) {
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
    return lbl_80401118 + k * 0x9C + chara * 0xC;
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
    return lbl_805AC600[i].charId;
}

int RaceSlot_GetDriverId(int i)
{
    if (i < 0 || i >= 8) {
        return -1;
    }
    return lbl_805AC600[i].driverId;
}

int GetKartSlotKartVariant(int i)
{
    if (i < 0 || i >= 8) {
        return 0;
    }
    return lbl_805AC600[i].kartVariant;
}

int RaceSlot_SetDriverPtr(int i, int v)
{
    if (i < 0 || i >= 8) {
        return 0;
    }
    lbl_805AC600[i].kartVariant = v;
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
    lbl_805AC600[i].items[slot] = v;
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
    lbl_805AC600[i].driverId = driver;
    lbl_805AC600[i].charId = chara;
    lbl_805AC600[i].field8 = f8;
    lbl_805AC600[i].fieldC = fc;
    lbl_805AC600[i].kartVariant = 0;
    return 1;
}

void RaceSlot_ResetAll(void)
{
    int i;

    for (i = 0; i < 8; i++) {
        lbl_805AC600[i].driverId = -1;
        lbl_805AC600[i].charId = -1;
        lbl_805AC600[i].field8 = 1;
        lbl_805AC600[i].items[0] = 0x24;
        lbl_805AC600[i].items[1] = 0x25;
        lbl_805AC600[i].items[2] = 0x26;
        lbl_805AC600[i].kartVariant = 0;
        lbl_805D2938[i] = 0;
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
    return lbl_8040E1C4[i];
}

void *DebugOverlay_GetLongRoundLabel(int i)
{
    if (i <= -1) {
        i = g_longRoundFlag;
    }
    if (i >= 2) {
        return 0;
    }
    return lbl_806CF100[i];
}

void *DebugOverlay_GetCupLabel(int i)
{
    if (i <= -1) {
        i = g_cupId;
    }
    if (i >= 17) {
        return 0;
    }
    return lbl_8040B318[i];
}

void SetReverseRoundFlag(int v)
{
    g_reverseRoundFlag = v;
}
