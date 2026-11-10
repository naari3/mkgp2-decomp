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

#include "game/types/GameModeBase.h"

struct JobRunnerMode : GameModeBase {
    JobTask *task;
    unsigned int updateStart;
    unsigned int updateEnd;
    unsigned int drawStart;
    unsigned int drawEnd;
    int sel;
    /* First non-inline virtual keeps the compiler vtable external. */
    virtual void _key2();
    JobRunnerMode() : task(0), sel(3) {}
    virtual int Update();
    virtual void Draw();
    virtual ~JobRunnerMode();
};

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

struct Tween : FlowFader {
    float from;
    float to;
    float rate;
    Tween(float v) : from(v), to(v), rate(v) {}
    float Value();
    void Set(float f, float t, short d);
};

#include "game/types/FadeSeq.h"

extern "C" const float lbl_806DABD8;
extern "C" const float lbl_806DABE8;
extern "C" const float lbl_806DABEC;











struct TweenI : FlowFader {
    int from;
    int to;
    int rate;
    int Value();
    void Set(int f, int t, short d);
};







/* ---- decimal digit helpers ---- */

extern "C" {
extern const unsigned int lbl_803C2DE8[7];
extern const unsigned int lbl_803C2E04[7];
extern const float lbl_806DABF0;
}






/* Deferred emission reverses definitions; keep target text in address order. */
extern "C" GameModeBase *fn_8020A3FC(void) {
    return new JobRunnerMode;
}

JobRunnerMode::~JobRunnerMode() {
}

int JobRunnerMode::Update() {
    InputPlayer *in;

    updateStart = OSGetTick();
    in = InputMgr_GetPlayer(GetInputManager(), 0);
    if (task == 0) {
        if (in->Pressed(1) == 1) {
            task = CreateJob(lbl_803C2D20[sel].type);
        } else if (in->Pressed(0x400) == 1) {
            return -4;
        } else if (in->Pressed(0x80) == 1) {
            sel = (sel + 1) % 14;
        } else if (in->Pressed(0x40) == 1) {
            sel = sel > 0 ? sel - 1 : 13;
        }
    } else if (!task->done) {
        task->Update();
    } else {
        if (task != 0) {
            if (task != 0) {
                task->Kill();
                task = 0;
            }
        }
        clRom_PurgeAll();
    }
    updateEnd = OSGetTick();
    return -2;
}

void JobRunnerMode::Draw() {
    const JobRodata *rd = &lbl_803C2840;
    const JobEntry *e;
    int i;
    char buf[0x40];
    unsigned int runUs;
    unsigned int drawUs;

    drawStart = OSGetTick();
    if (task == 0) {
        OverlayText(1, 3, 5, rd->selectFmt, sel);
        OverlayText(1, 3, sel + 7, lbl_806DABC8);
        for (i = 0, e = rd->entries; i < 14; i++, e++) {
            sprintf(buf, lbl_806DABCC, i, e->name);
            OverlayText(1, 5, i + 7, buf);
        }
    } else if (!task->done) {
        task->Draw();
    }
    drawEnd = OSGetTick();
    runUs = OSTicksToMicroseconds(updateEnd - updateStart);
    drawUs = OSTicksToMicroseconds(drawEnd - drawStart);
    DeadCounter_Set_ced48(4);
    OverlayText(1, 5, 0x1C, rd->runFmt, runUs);
    OverlayText(1, 5, 0x1D, rd->drawFmt, drawUs);
    DeadCounter_Set_ced48(7);
}

extern "C" JobRunner *fn_80209FE8(void) {
    if (lbl_806D1A00 == 0) {
        lbl_806D1A00 = &lbl_806D1A20;
    }
    return lbl_806D1A00;
}

extern "C" void fn_80209FA4(void) {
    if (lbl_806D1A00 != 0) {
        if (lbl_806D1A00 != 0) {
            memset(&lbl_806D1A20, 0, sizeof(JobRunner));
        }
        lbl_806D1A00 = 0;
    }
}













/* Target vtable includes its existing RTTI descriptor with RTTI disabled. */
extern "C" {
extern const char JobRunnerMode_data_806D02F0[];
int fn_8020A194(void *);
void fn_8020A004(void *);
void *fn_8020A39C(void *, short);
const void *JobRunnerMode_vtable_804EC7F4[5] = {
    JobRunnerMode_data_806D02F0, 0, (const void *)fn_8020A194,
    (const void *)fn_8020A004, (const void *)fn_8020A39C
};
}
