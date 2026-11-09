/*
 * A small sprite animation object (resource 0x139F): two layers of the
 * same sprite are scaled and faded in, held, and scaled back out from a
 * frame timer. Three classes deep (vtables lbl_8048ECF8, lbl_8048ED10,
 * lbl_8048ECE0, all in data), so the vptr stores are spelled out by hand.
 *
 * Still asm: the update (float register assignment: a C form gets the
 * instruction stream but MWCC colors the compare-chain constants and the
 * block-local scale temps differently, ~95 %). The release helper is C++
 * `delete` through the virtual destructor.
 */
#pragma cplusplus on

extern "C" {
extern char lbl_8048ECE0[];
extern char lbl_8048ECF8[];
extern char lbl_8048ED10[];
extern const float lbl_806D7900, lbl_806D7904, lbl_806D7908, lbl_806D790C;
extern const float lbl_806D7910, lbl_806D7914, lbl_806D7918, lbl_806D791C;
extern const float lbl_806D7920, lbl_806D7924, lbl_806D7928, lbl_806D792C;
extern const float lbl_806D7930, lbl_806D7934, lbl_806D7938, lbl_806D793C;
extern const float lbl_806D7940, lbl_806D7944, lbl_806D7948, lbl_806D794C;
extern const float lbl_806D7950, lbl_806D7954, lbl_806D7958, lbl_806D795C;
extern const float lbl_806D7960, lbl_806D7964, lbl_806D7968, lbl_806D796C;
extern const float lbl_806D7970, lbl_806D7974, lbl_806D7978, lbl_806D797C;
extern const float lbl_806D7980, lbl_806D7984, lbl_806D7988, lbl_806D798C;
extern const float lbl_806D7990;
extern void fn_8016918C(void *obj, int id, int flag, float x, float y, float sx, float sy, float r, float g, float b, float a);
extern void fn_80169468(void *obj, int id, int flag, float x, float y, float sx, float sy, float sz, float a);
extern void fn_801697C0(void *obj, int id, int flag, float x, float y, float sx, float sy);
extern void fn_801698B4(void *obj, int id, int flag, float x, float y);
extern void PreloadResource(int resId);
extern void MemoryManager_TimedFree(void *p);
}

extern "C" {


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

extern "C" void fn_80141454(LogoAnim *self) {
    float t;
    float a;
    float s;

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
            float sx;
            float a;
            float sy;
            a = (t - 100.0f) / 5.0f;
            sx = 1.0f - 0.05f * a;
            sy = 0.15f * a + 1.0f;
            fn_801697C0(self->obj, 0x139F, 0, 320.0f, 300.0f, sx, sy);
            fn_8016918C(self->obj, 0x139F, 2, 320.0f, 300.0f, sx, sy, 1.0f, 1.0f, 1.0f, a);
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
        float sy;
        float a;
        float y;
        float sx;
        a = (t - 105.0f) / 10.0f;
        sx = 0.85f * a + 0.95f;
        sy = 1.15f - 0.75f * a;
        fn_8016918C(self->obj, 0x139F, 1, 320.0f - 106.0f * a, y = 300.0f - 4.0f * a, sx, sy, 1.0f, 1.0f, 1.0f, a);
        fn_8016918C(self->obj, 0x139F, 1, 114.0f * a + 320.0f, y, sx, sy, 1.0f, 1.0f, 1.0f, a);
    }
    self->t += 1.0f;
    if (self->t > 115.0f) {
        self->done = 1;
        self->t = 115.0f;
    }
}

extern "C" void fn_80141450(void) {
}


LogoAnim::~LogoAnim() {
    vptr = lbl_8048ECE0;
}

LogoAnim::LogoAnim(void *o, int a) : AnimMid(a) {
    vptr = lbl_8048ECE0;
    obj = o;
    done = 0;
    t = lbl_806D7990;
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
