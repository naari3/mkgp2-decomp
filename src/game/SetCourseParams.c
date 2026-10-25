/* SetCourseParams (0x8009CBFC): select cup/round/variant and reset the
 * per-race kart, lap and rank slots.
 *
 * NonMatching: the target addresses these .bss objects pooled off one base
 * (they were defined in the original TU, which spans RaceSys_8009B98C ..
 * SetCourseParams). Defining them here gets the pooling, but MWCC lays the
 * pooled objects out in first-use order, which only matches when the whole
 * original TU (with its earlier references) is compiled together. */

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
    if (g_cupId >= 0 && g_longRoundFlag >= 0) {
        g_raceStarted = 0;
    }
    lbl_806CF10C = 0;
    if (lbl_806D1258 == 0) {
        for (i = 0; i < 5; i++) {
            lbl_805B24CC[i].a = 0;
            lbl_805B24CC[i].b = 0;
            lbl_805B24CC[i].c = lbl_806D4790;
            lbl_805B24CC[i].d = lbl_806D4798;
        }
        for (i = 5; i < 10; i++) {
            lbl_805B24CC[i].a = 0;
            lbl_805B24CC[i].b = 1;
            lbl_805B24CC[i].c = lbl_806D4790;
            lbl_805B24CC[i].d = lbl_806D4798;
        }
        lbl_805B256C.e.a = 0;
        lbl_805B256C.e.b = 0;
        lbl_805B256C.e.c = lbl_806D4790;
        lbl_805B256C.e.d = lbl_806D4798;
        lbl_806D1280 = 4;
        lbl_806D1258 = 1;
        for (i = 0; i < 8; i++) {
            lbl_805D2948[i].active = 0;
            lbl_805D2948[i].count = 0;
            lbl_805D2948[i].target = -1;
            lbl_805D2948[i].source = -1;
            lbl_805D2948[i].flag18 = 0;
            lbl_805D2948[i].flag19 = 0;
            lbl_805D2948[i].timer = 0;
            lbl_805D2948[i].value20 = lbl_806D4790;
            lbl_805D2948[i].value24 = lbl_806D4790;
            lbl_805D2948[i].enabled = 1;
        }
        lbl_806D12D8 = 0;
    }
    return 1;
}
