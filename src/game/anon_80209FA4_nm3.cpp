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

struct JobRunner {
    char pad;
};

extern "C" JobRunner *lbl_806D1A00;
extern "C" JobRunner lbl_806D1A20;





/* ---- clJobRunner debug mode ---- */

struct InputPlayer {
    virtual void v0();
    virtual void v1();
    virtual float v2();
    virtual void v3();
    virtual float StickRight();
    virtual float StickLeft();
    virtual unsigned char Pressed(int mask);
};

extern "C" InputPlayer *InputMgr_GetPlayer(void *mgr, int index);

struct JobTask {
    virtual void v0();
    virtual void Kill();
    virtual void Update();
    virtual void Draw();
    unsigned char done;
};

extern "C" {
JobTask *fn_8020CEAC(void);
JobTask *fn_80254F74(void);
}

struct JobTask15 : JobTask {
    char pad[0x18 - 0x8];
    JobTask15();
};

struct JobEntry {
    int type;
    const char *name;
};

struct JobRodata {
    char pad000[0x4E0];
    JobEntry entries[14];
    char pad550[0x568 - 0x550];
    char selectFmt[0x14];
    char runFmt[0x14];
    char drawFmt[0x14];
};

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

struct JobRunnerMode : GameModeBase {
    JobTask *task;
    unsigned int updateStart;
    unsigned int updateEnd;
    unsigned int drawStart;
    unsigned int drawEnd;
    int sel;
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

struct FadeKeyBase {
    virtual ~FadeKeyBase();
    int dur;
    FadeKeyBase(int d) : dur(d) {}
};

struct FadeKey : FadeKeyBase {
    float from;
    float to;
    VHolder<FadeKey> next;
    FadeKey(int d, float f, float t) : FadeKeyBase(d), from(f), to(t) {}
    ~FadeKey();
    void Append(int dur, float to);
};

struct FadeSeqBase {
    virtual ~FadeSeqBase();
    bool loop;
    FadeSeqBase(bool l) : loop(l) {}
};

struct Tween : FlowFader {
    float from;
    float to;
    float rate;
    Tween(float v) : from(v), to(v), rate(v) {}
    virtual void _key2();
    float Value();
    void Set(float f, float t, short d);
};

struct FadeSeq : FadeSeqBase {
    FadeKey *head;
    FadeKey *cur;
    Tween *tween;
    FadeSeq(FadeKey *h, bool l);
    ~FadeSeq();
    void Update();
    bool Done();
    void Load() {
        float t = cur->to;
        tween->Set(cur->from, t, cur->dur);
        cur = cur->next.p;
    }
};

extern "C" const float lbl_806DABD8;
extern "C" const float lbl_806DABE8;
extern "C" const float lbl_806DABEC;











struct TweenI : FlowFader {
    int from;
    int to;
    int rate;
    virtual void _key2();
    int Value();
    void Set(int f, int t, short d);
};







/* ---- decimal digit helpers ---- */

extern "C" {
extern const unsigned int lbl_803C2DE8[7];
extern const unsigned int lbl_803C2E04[7];
extern const float lbl_806DABF0;
}






extern "C" int fn_8020A788(TweenI *self) {
    short n = self->a;
    short t = self->b;
    int value;
    if (t <= 0) {
        value = self->from;
    } else if (t >= n) {
        value = self->to;
    } else {
        value = self->rate * t;
        value >>= 16;
        value += self->from;
    }
    return value;
}
    if (t >= n) {
        return self->to;
    }
    int value = self->rate * t;
    value >>= 16;
    value += self->from;
    return value;
}
