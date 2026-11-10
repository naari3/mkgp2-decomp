#include "game/types/c_region.h"
C_REGION_BEGIN
/*
 * A small sprite animation object (resource 0x139F): two layers of the
 * same sprite are scaled and faded in, held, and scaled back out from a
 * frame timer. Three classes deep (vtables lbl_8048ECF8, lbl_8048ED10,
 * LogoAnim_data_8048ECE0, all in data), so the vptr stores are spelled out by hand.
 *
 * The update keeps its seven scale/alpha temps at function scope, declared
 * in the order below: MWCC numbers locals in reverse declaration order and
 * hands out f28..f31 from that (regalloc_patterns 51). The release helper
 * is C++ `delete` through the virtual destructor.
 */
C_REGION_END
#pragma cplusplus on

extern "C" {
extern char LogoAnim_data_8048ECE0[];
extern char lbl_8048ECF8[];
extern char lbl_8048ED10[];
extern void fn_8016918C(void *obj, int id, int flag, float x, float y, float sx, float sy, float r, float g, float b, float a);
extern void fn_80169468(void *obj, int id, int flag, float x, float y, float sx, float sy, float sz, float a);
extern void fn_801697C0(void *obj, int id, int flag, float x, float y, float sx, float sy);
extern void fn_801698B4(void *obj, int id, int flag, float x, float y);
extern void PreloadResource(int resId);
extern void MemoryManager_TimedFree(void *p);
}

struct AnimBase {
    void *volatile vptr;
    int arg;
    int f8;
    int fc;
    AnimBase(int a) {
        vptr = lbl_8048ECF8;
        arg = a;
        f8 = 0;
        fc = 0;
    }
    ~AnimBase() { vptr = lbl_8048ECF8; }
};

struct AnimMid : AnimBase {
    AnimMid(int a) : AnimBase(a) { vptr = lbl_8048ED10; }
    ~AnimMid() { vptr = lbl_8048ED10; }
};

struct LogoAnim : AnimMid {
    void *obj;
    int done;
    float t;
    LogoAnim(void *o, int a);
    ~LogoAnim();
};

extern "C" void fn_80141450(void) {
}

extern "C" void fn_80141454(LogoAnim *self) {
    float t;
    float a;
    float s;
    float splitY, splitT, splitSy, splitSx, outSx, outSy, outT;

    if (self->done) {
        self->fc = 1;
        return;
    }
    t = self->t;
    if (t >= 6.0f) {
        if (t < 15.0f) {
            a = (t - 6.0f) / 9.0f;
            s = 0.7f * a + 0.3f;
            fn_8016918C(self->obj, 0x139F, 2, 320.0f, 300.0f, s, s, 1.0f, 1.0f, 1.0f, a);
        } else if (t < 18.0f) {
            s = 0.08f * ((t - 15.0f) / 3.0f) + 1.0f;
            fn_8016918C(self->obj, 0x139F, 2, 320.0f, 300.0f, s, s, 1.0f, 1.0f, 1.0f, 1.0f);
        } else if (t < 21.0f) {
            s = 1.08f - 0.08f * ((t - 18.0f) / 3.0f);
            fn_8016918C(self->obj, 0x139F, 2, 320.0f, 300.0f, s, s, 1.0f, 1.0f, 1.0f, 1.0f);
        } else if (t < 35.0f) {
            fn_801698B4(self->obj, 0x139F, 0, 320.0f, 300.0f);
            fn_80169468(self->obj, 0x139F, 2, 320.0f, 300.0f, 1.0f, 1.0f, 1.0f, 1.0f - (t - 21.0f) / 14.0f);
        } else if (t < 100.0f) {
            fn_801698B4(self->obj, 0x139F, 0, 320.0f, 300.0f);
        } else if (t < 105.0f) {
            outT = (t - 100.0f) / 5.0f;
            outSx = 1.0f - 0.05f * outT;
            outSy = 0.15f * outT + 1.0f;
            fn_801697C0(self->obj, 0x139F, 0, 320.0f, 300.0f, outSx, outSy);
            fn_8016918C(self->obj, 0x139F, 2, 320.0f, 300.0f, outSx, outSy, 1.0f, 1.0f, 1.0f, outT);
        }
    }
    t = self->t;
    if (t < 12.0f) {
        a = t / 12.0f;
        s = 0.8f * a + 0.3f;
        fn_8016918C(self->obj, 0x139F, 1, 320.0f, 300.0f, s, s, 1.0f, 1.0f, 1.0f, a);
    } else if (t < 18.0f) {
        a = (t - 12.0f) / 6.0f;
        s = 0.15f * a + 1.1f;
        fn_8016918C(self->obj, 0x139F, 1, 320.0f, 300.0f, s, s, 1.0f, 1.0f, 1.0f, 1.0f - 0.5f * a);
    } else if (t < 23.0f) {
        a = (t - 18.0f) / 5.0f;
        s = 0.25f * a + 1.25f;
        fn_8016918C(self->obj, 0x139F, 1, 320.0f, 300.0f, s, s, 1.0f, 1.0f, 1.0f, 0.5f - 0.5f * a);
    } else if (t >= 105.0f) {
        splitT = (t - 105.0f) / 10.0f;
        splitSx = 0.85f * splitT + 0.95f;
        splitSy = 1.15f - 0.75f * splitT;
        fn_8016918C(self->obj, 0x139F, 1, 320.0f - 106.0f * splitT, splitY = 300.0f - 4.0f * splitT, splitSx, splitSy, 1.0f, 1.0f, 1.0f, splitT);
        fn_8016918C(self->obj, 0x139F, 1, 114.0f * splitT + 320.0f, splitY, splitSx, splitSy, 1.0f, 1.0f, 1.0f, splitT);
    }
    self->t += 1.0f;
    if (self->t > 115.0f) {
        self->done = 1;
        self->t = 115.0f;
    }
}



LogoAnim::~LogoAnim() {
    vptr = LogoAnim_data_8048ECE0;
}

LogoAnim::LogoAnim(void *o, int a) : AnimMid(a) {
    vptr = LogoAnim_data_8048ECE0;
    obj = o;
    done = 0;
    t = 0.0f;
}

extern "C" void fn_8014196C(void) {
    PreloadResource(0x139F);
}

struct LogoAnimOwned {
    virtual ~LogoAnimOwned();
};

extern "C" void fn_80141990(LogoAnimOwned *p) {
    delete p;
}

extern "C" AnimMid *dtor_801419C8(AnimMid *p, short flag) {
    if (p) {
        p->vptr = lbl_8048ED10;
        if (p) {
            p->vptr = lbl_8048ECF8;
        }
        if (flag > 0) {
            MemoryManager_TimedFree(p);
        }
    }
    return p;
}

extern "C" AnimBase *fn_80141A24(AnimBase *p, short flag) {
    if (p) {
        p->vptr = lbl_8048ECF8;
        if (flag > 0) {
            MemoryManager_TimedFree(p);
        }
    }
    return p;
}
