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
#include "game/types/PlayerData.h"
extern PlayerData g_playerData;
void DebugPrintf(const char *fmt, ...);
void *memset(void *dst, int c, unsigned long n);
unsigned char fn_801D5C88(PlayerData *data, int cc);
unsigned char RoundCupIsCompleted(PlayerData *data, int cc, int cup, int mode);
}

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
    static void *operator new(unsigned long) { void *p = lbl_80679E00; return p; }
    /* Clears the static buffer (dtor_8024F40C). */
    static void operator delete(void *);
};

extern "C" RoundResult *lbl_806D1AC8;

extern "C" RoundResult *fn_8024F588(void) {
    if (lbl_806D1AC8 == 0) {
        lbl_806D1AC8 = new RoundResult;
    }
    return lbl_806D1AC8;
}

