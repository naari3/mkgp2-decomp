/*
 * 0x80209FA4..0x8020AA98: job-runner singleton, the clJobRunner debug mode
 * (mode select menu + per-frame timing overlay), the fade keyframe
 * sequence, the float/int tween helpers and decimal digit helpers.
 */

#include "game/FlowScene.h"

extern "C" {
void *memset(void *dst, int c, unsigned long n);
int sprintf(char *s, const char *format, ...);
unsigned int OSGetTick(void);
void OverlayText(int layer, int x, int y, const char *fmt, ...);
void DeadCounter_Set_ced48(unsigned int v);
void clRom_PurgeAll(void);
void *GetInputManager(void);
}

/* ---- job runner singleton ---- */

#include "game/types/JobRunner.h"

extern "C" JobRunner *lbl_806D1A00;
extern "C" JobRunner lbl_806D1A20;





/* ---- clJobRunner debug mode ---- */

#include "game/types/InputPlayer.h"

extern "C" InputPlayer *InputMgr_GetPlayer(void *mgr, int index);

#include "game/types/JobTask.h"

extern "C" {
JobTask *fn_8020CEAC(void);
JobTask *fn_80254F74(void);
}

#include "game/types/JobTask15.h"

#include "game/types/JobEntry.h"

#include "game/types/JobRodata.h"

extern "C" {
extern const JobRodata lbl_803C2840;
extern const JobEntry lbl_803C2D20[14];
extern const char lbl_806DABC8[2];
extern const char lbl_806DABCC[8];
}

#define OS_BUS_CLOCK (*(unsigned int *)0x800000F8)
#define OS_TIMER_CLOCK (OS_BUS_CLOCK / 4)
#define OSTicksToMicroseconds(ticks) (((ticks) * 8) / (OS_TIMER_CLOCK / 125000))

struct GameModeBase {
    GameModeBase();
    virtual int Update();
    virtual void Draw();
    virtual ~GameModeBase();
};

#include "game/types/JobRunnerMode.h"

static inline JobTask *CreateJob(int type) {
    switch (type) {
    case 6:
        return fn_80254F74();
    case 0:
    case 1:
    case 2:
    case 3:
    case 4:
    case 5:
    case 7:
    case 8:
    case 9:
    case 10:
    case 11:
    case 12:
    case 13:
    case 14:
        return fn_8020CEAC();
    case 15:
        return new JobTask15;
    default:
        return 0;
    }
}









/* ---- fade keyframe sequence ---- */

#include "game/types/FadeKeyBase.h"

#include "game/types/FadeKey.h"

#include "game/types/FadeSeqBase.h"

#include "game/types/Tween.h"

#include "game/types/FadeSeq.h"

extern "C" const float lbl_806DABD8;
extern "C" const float lbl_806DABE8;
extern "C" const float lbl_806DABEC;











#include "game/types/TweenI.h"







/* ---- decimal digit helpers ---- */

extern "C" {
extern const unsigned int lbl_803C2DE8[7];
extern const unsigned int lbl_803C2E04[7];
extern const float lbl_806DABF0;
}






/* Deferred emission reverses definitions; keep target text in address order. */
extern "C" unsigned int fn_8020A9EC(int pos, float time) {
    unsigned int r = 0;
    unsigned int v;
    int i;

    if ((pos | (6 - pos)) >= 0) {
        v = lbl_806DABF0 * time;
        if (v >= lbl_803C2DE8[0]) {
            if (pos & ~2) {
                r = 9;
            } else {
                r = 5;
            }
        } else {
            for (i = 0; i <= pos; i++) {
                unsigned int u = lbl_803C2DE8[i];
                while (v >= u) {
                    v -= u;
                }
            }
            r = v / lbl_803C2E04[pos];
        }
    }
    return r;
}

extern "C" unsigned int fn_8020A900(unsigned int value, int pos) {
    unsigned int digit = 0;
    if ((pos & ~3) == 0) {
        unsigned int p = 10;
        int i;
        for (i = 0; i < pos; i++) {
            p = (p << 3) + (p << 1);
        }
        while (value >= p) {
            value -= p;
        }
        digit = ((value << 3) + (value << 1)) / p;
    }
    return digit;
}

void FadeKey::Append(int dur, float to) {
    FadeKey *tail = this;
    FadeKey *n = next.p;
    while (n != 0) {
        tail = n;
        n = n->next.p;
    }
    float from = tail->to;
    tail->next.Reset(new FadeKey(dur, from, to));
}

void TweenI::Set(int f, int t, short d) {
    from = f;
    to = t;
    a = d;
    b = 0;
    rate = ((t - f) << 16) / d;
}
