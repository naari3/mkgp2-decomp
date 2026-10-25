/*
 * Round result record @ 0x8024F43C..0x8024F618.
 *
 * A single RoundResult lives in the static buffer lbl_80679E00 (placement
 * through a class operator new); lbl_806D1AC8 points at it while alive.
 */

extern "C" {
extern unsigned char lbl_80679E00[0x24];
extern const char lbl_803F0A40[];
extern const char lbl_803F0A58[];
extern int g_gameMode;
extern int g_cupId;
extern int g_roundIndex;
extern int g_ccClass;
extern int g_finalRacePosition;
extern unsigned char g_raceEnded;
struct PlayerData { char body[0x1DC]; };
extern PlayerData g_playerData;
void DebugPrintf(const char *fmt, ...);
void *memset(void *dst, int c, unsigned long n);
unsigned char fn_801D5C88(PlayerData *data, int cc);
unsigned char RoundCupIsCompleted(PlayerData *data, int cc, int cup, int mode);
}

inline void *operator new(unsigned long, void *p) { return p; }

struct RoundResult {
    unsigned char flag0;
    unsigned char flag1;
    unsigned char pending;
    int cup;
    int round;
    unsigned char flagC;
    unsigned char showResult;
    unsigned char flagE;
    unsigned char flagF;
    int field10;
    unsigned char done;
    int field18;
    int field1C;
    RoundResult() {
        flag0 = 0;
        flag1 = 0;
        pending = 0;
        cup = -1;
        round = -1;
        flagC = 0;
        showResult = 0;
        flagE = 0;
        flagF = 0;
        field10 = -1;
        done = 0;
        field18 = 0;
        field1C = 0;
        DebugPrintf(lbl_803F0A58);
    }
    ~RoundResult() { DebugPrintf(lbl_803F0A40); }
    static void operator delete(void *) { memset(lbl_80679E00, 0, 0x24); }
};

extern "C" RoundResult *lbl_806D1AC8;

extern "C" RoundResult *fn_8024F588(void) {
    if (lbl_806D1AC8 == 0) {
        lbl_806D1AC8 = new (lbl_80679E00) RoundResult;
    }
    return lbl_806D1AC8;
}

extern "C" void fn_8024F530(void) {
    if (lbl_806D1AC8) {
        delete lbl_806D1AC8;
        lbl_806D1AC8 = 0;
    }
}

static inline bool ShouldShowResult(PlayerData &pd) {
    int mode = g_gameMode;
    int cup = g_cupId;
    int round = g_roundIndex;
    if (mode == 0) {
        if (cup >= 1 && cup <= 8) {
            if (round >= 0 && round <= 2 && g_finalRacePosition == 0) {
                return 1;
            }
        } else {
            int cc = g_ccClass;
            if (!RoundCupIsCompleted(&pd, cc, cup, fn_801D5C88(&pd, cc)) && g_raceEnded) {
                return 1;
            }
        }
    } else if (mode == 2) {
        if (g_finalRacePosition == 0) {
            return 1;
        }
    }
    return 0;
}

extern "C" void fn_8024F43C(RoundResult *r) {
    r->showResult = ShouldShowResult(g_playerData);
}
