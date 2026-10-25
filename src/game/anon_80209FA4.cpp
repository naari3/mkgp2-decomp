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

extern "C" void fn_80209FA4(void) {
    if (lbl_806D1A00 != 0) {
        if (lbl_806D1A00 != 0) {
            memset(&lbl_806D1A20, 0, sizeof(JobRunner));
        }
        lbl_806D1A00 = 0;
    }
}

extern "C" JobRunner *fn_80209FE8(void) {
    if (lbl_806D1A00 == 0) {
        lbl_806D1A00 = &lbl_806D1A20;
    }
    return lbl_806D1A00;
}

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

JobRunnerMode::~JobRunnerMode() {
}

extern "C" GameModeBase *fn_8020A3FC(void) {
    return new JobRunnerMode;
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

void FadeSeq::Update() {
    tween->Step();
    if (tween->Done()) {
        if (cur != 0) {
            Load();
        } else if (loop) {
            cur = head;
            Load();
        }
    }
}

bool FadeSeq::Done() {
    if (!loop) {
        Tween *t = tween;
        return t->Done() && cur == 0;
    }
    return false;
}

FadeSeq::FadeSeq(FadeKey *h, bool l) : FadeSeqBase(l), head(h), cur(head), tween(new Tween(lbl_806DABE8)) {
    Load();
}

float Tween::Value() {
    short t = b;
    short n = a;
    if (t <= 0) {
        return from;
    }
    if (t >= n) {
        return to;
    }
    return from + lbl_806DABEC * (rate * t);
}

void Tween::Set(float f, float t, short d) {
    from = f;
    to = t;
    a = d;
    b = 0;
    rate = (lbl_806DABD8 * (t - f)) / d;
}

struct TweenI : FlowFader {
    int from;
    int to;
    int rate;
    virtual void _key2();
    int Value();
    void Set(int f, int t, short d);
};

int TweenI::Value() {
    short n = a;
    short t = b;
    return t <= 0 ? from : (t >= n ? to : ((rate * t) >> 16) + from);
}

void TweenI::Set(int f, int t, short d) {
    from = f;
    to = t;
    a = d;
    b = 0;
    rate = ((t - f) << 16) / d;
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

/* ---- decimal digit helpers ---- */

extern "C" {
extern const unsigned int lbl_803C2DE8[7];
extern const unsigned int lbl_803C2E04[7];
extern const float lbl_806DABF0;
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
