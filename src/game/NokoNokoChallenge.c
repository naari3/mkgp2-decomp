/*
 * NokoNokoChallenge: SaveResult and CalcResultText (0x80122C0C..0x80122E58).
 * Both are C with -Cpp_exceptions on, so CW emits their extab entries.
 */

extern int g_characterId;
/* fakematch (permuter): natural code is `extern int g_cupId;`. The target
 * reloads g_cupId for the call after testing the cup index; only volatile
 * stops mwcc from reusing the first load. */
extern volatile int g_cupId;
extern int g_roundIndex;
extern int g_ccClass;
extern char g_playerData[0x1DC];
extern void *lbl_806D10A0[2];

extern unsigned char IsCardValid(void);
extern void SoundMgr_PlaySE(int);
extern void fn_8016C554(int);
extern void fn_80192208(int);
extern unsigned char RoundCupIsCompleted(void *, int, int, int);
extern void fn_801D6558(void *, int, int, int);
extern void PlayStats_OnMissionResult_Stub(void);
extern void Empty_NokoNokoHook(int, int, int);
extern unsigned char *fn_8024F588(void);

#include "game/singleton.h"
/* --- owned .rodata 0x80355840..0x803558A8 (tools/own_data.py) --- */
#pragma force_active on
const int NokoNokoChallenge_SaveResult_rodata_80355840[13][2] = { 234, 219, 255, 249, 268, 270, 297, 293, 318, 303, 340, 338, 361, 345, 382, 367, 403, 397, 424, 420, 445, 441, 467, 452, 488, 473 };
#pragma force_active reset

#pragma exceptions on
void NokoNokoChallenge_SaveResult(void *param_1, int param_2, unsigned int param_3) {
    int characterId = g_characterId;
    if (IsCardValid() == 1) {
        param_3 = ((unsigned int)(-param_2 & ~param_2)) >> 31;
    }
    if ((param_3 & 0xff) == 1) {
        fn_8016C554(1);
        if (g_cupId == 0xe) {
            fn_80192208(g_characterId + 9);
        }
        SoundMgr_PlaySE(NokoNokoChallenge_SaveResult_rodata_80355840[characterId][0]);
    } else {
        fn_8016C554(0);
        if (g_cupId == 0xe) {
            fn_80192208(g_characterId + 9);
        }
        SoundMgr_PlaySE(NokoNokoChallenge_SaveResult_rodata_80355840[characterId][1]);
    }
}

/* Cup number -> index within its group (cups 9+ are the second group). */
static inline int CupIndex(int cup) {
    if (cup >= 9) {
        cup -= 9;
    } else {
        cup -= 1;
    }
    return cup;
}
static inline int CupIndex2(int cup) {
    int idx;
    if (cup >= 9) {
        idx = cup - 9;
    } else {
        /* fakematch (permuter): natural code is `idx = cup - 1;`, which mwcc
         * if-converts (hoists above the branch); the target keeps both arms. */
        idx = cup;
        idx--;
    }
    return idx;
}
static inline void CheckCard(int round, int cc, int cup) {
    if (cup >= 0 && round >= 0 && cc >= 0) {
        IsCardValid();
    }
}
int NokoNokoChallenge_CalcResultText(void *self, unsigned char goal, int text) {
    void *hook = SINGLETON_INSTANCE(lbl_806D10A0[0]);
    int result = 0;
    int afterFinal = g_roundIndex > 3;
    if (goal) {
        if (CupIndex2(g_cupId) >= 0) {
            if (RoundCupIsCompleted(g_playerData, g_ccClass, g_cupId, afterFinal) == 1) {
                result = 1;
            }
            fn_801D6558(g_playerData, g_cupId, afterFinal, 1);
        }
        PlayStats_OnMissionResult_Stub();
        CheckCard(g_roundIndex > 3, g_ccClass, CupIndex(g_cupId));
        if (hook != 0) {
            Empty_NokoNokoHook((int)hook, 0, text);
        }
    } else {
        fn_801D6558(g_playerData, g_cupId, afterFinal, 0);
        if (hook != 0) {
            Empty_NokoNokoHook((int)hook, -1, text);
        }
    }
    fn_8024F588()[0x20] = goal;
    return result;
}
#pragma exceptions reset
