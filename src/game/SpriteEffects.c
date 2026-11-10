#include "game/types/c_region.h"
C_REGION_BEGIN
/*
 * Three small sprite effects that share one base (vtable lbl_8048EB44, at
 * +0x14 after the base fields): each has a render that picks a sprite frame
 * from its timer, an update that advances the timer, a ctor and a dtor.
 * The vtables stay in data, so the vptr stores are spelled out by hand
 * (volatile, so the derived store before the inlined base dtor survives).
 * The three render functions draw a frame-picked sprite and then a scaled,
 * offset overlay; their float literals are written inline (the shared
 * Effect_DrawSprite helper mirrors the repeated draw call).
 */
#include "game/types/size_t.h"
C_REGION_END
#pragma cplusplus on

extern "C" {
extern char SpriteEffects_data_8048EB24[];
extern char lbl_8048EB44[];
extern char SpriteEffects_data_8048EB70[];
extern char SpriteEffects_data_8048EB9C[];
extern const float lbl_806D76F0, lbl_806D76F4, lbl_806D76F8, lbl_806D76FC;
extern const float lbl_806D7700, lbl_806D7704, lbl_806D7708, lbl_806D770C;
extern const float lbl_806D7710, lbl_806D7714, lbl_806D7718, lbl_806D771C;
extern const float lbl_806D7720, lbl_806D7724, lbl_806D7728, lbl_806D772C;
extern const float lbl_806D7730, lbl_806D7734, lbl_806D7738, lbl_806D773C;
extern const float lbl_806D7740, lbl_806D7744, lbl_806D7748, lbl_806D774C;
extern const float lbl_806D7750, lbl_806D7754, lbl_806D7758, lbl_806D775C;
extern const float lbl_806D7760, lbl_806D7764, lbl_806D7768, lbl_806D776C;
extern const float lbl_806D7770, lbl_806D7774, lbl_806D7778, lbl_806D777C;
extern const float lbl_806D7780, lbl_806D7784, lbl_806D7788, lbl_806D778C;
extern const float lbl_806D7790, lbl_806D7794, lbl_806D7798, lbl_806D779C;
extern const float lbl_806D77A0, lbl_806D77A4;
#ifdef __MWERKS__
extern void fn_80169468(void *obj, int id, int flag, float x, float y, float sx, float sy, float sz, float a);
#else
/* The definition orders its int and float parameters differently; see docs/notes/port_abi.md. */
extern void fn_80169468(void *, int, float, float, float, float, float, float, int);
static inline void fn_80169468_Reordered(void *obj, int id, int flag, float x, float y, float sx, float sy, float sz, float a) { fn_80169468(obj, id, x, y, sx, sy, sz, a, flag); }
#define fn_80169468 fn_80169468_Reordered
#endif
#ifdef __MWERKS__
extern void fn_8016918C(void *obj, int id, int flag, float x, float y, float sx, float sy, float r, float g, float b, float a);
#else
/* The definition orders its int and float parameters differently; see docs/notes/port_abi.md. */
extern void fn_8016918C(void *, int, float, float, float, float, float, float, float, float, int);
static inline void fn_8016918C_Reordered(void *obj, int id, int flag, float x, float y, float sx, float sy, float r, float g, float b, float a) { fn_8016918C(obj, id, x, y, sx, sy, r, g, b, a, flag); }
#define fn_8016918C fn_8016918C_Reordered
#endif
extern void fn_801A0004(void *p);
}

void *operator new(size_t size);
inline void *operator new(size_t, void *p) { return p; }
void operator delete(void *p);

struct EffectBase {
    void *obj;
    unsigned char active;
    float x, y;
    float alpha;
    void *volatile vptr;
    unsigned int flags;
    float t;
    EffectBase() {
        vptr = lbl_8048EB44;
        obj = 0;
        active = 0;
        x = lbl_806D770C;
        y = lbl_806D770C;
        alpha = lbl_806D76F4;
    }
    ~EffectBase() { vptr = lbl_8048EB44; }
};

typedef EffectBase Effect;

struct Effect1 : Effect {
    Effect1();
    ~Effect1();
};

struct Effect2 : Effect {
    Effect2(int mode);
    ~Effect2();
};

struct Effect3 : Effect {
    Effect3();
    ~Effect3();
};

Effect1::~Effect1() {
    vptr = SpriteEffects_data_8048EB24;
}

static inline void Effect_DrawSprite(Effect *e, int id, float alpha) {
    fn_80169468(e->obj, id, 0, e->x, e->y, 1.0f, 1.0f, 1.0f, alpha);
}

extern "C" void fn_8013DD94(Effect *e) {
    float s;
    float t;
    float sx;
    float a;
    float dx;
    float dy;
    float u;

    t = e->t;
    if (t < 10.0f) {
        Effect_DrawSprite(e, 0x883, e->alpha);
    } else if (t < 14.0f) {
        Effect_DrawSprite(e, 0x884, e->alpha);
    } else if (t < 18.0f) {
        Effect_DrawSprite(e, 0x885, e->alpha);
    } else if (t < 40.0f) {
        Effect_DrawSprite(e, 0x886, e->alpha);
    } else if (t < 44.0f) {
        Effect_DrawSprite(e, 0x885, e->alpha);
    } else if (t < 50.0f) {
        Effect_DrawSprite(e, 0x884, e->alpha);
    } else {
        Effect_DrawSprite(e, 0x883, e->alpha);
    }

    t = e->t;
    if (t < 18.0f) {
        s = 0.0f;
    } else if (t < 30.0f) {
        s = (t - 18.0f) / 12.0f;
    } else if (t < 44.0f) {
        s = 1.0f - (t - 30.0f) / 14.0f;
    } else {
        s = 0.0f;
    }
    if (s > 0.0f) {
        Effect_DrawSprite(e, 0x88A, s * e->alpha);
    }

    t = e->t;
    if (t < 10.0f) {
        u = t / 10.0f;
        a = 0.8f;
        sx = a - 0.1f * u;
        dx = 7.0f * u + -54.0f;
        dy = -2.0f;
    } else if (t < 26.0f) {
        u = (t - 10.0f) / 16.0f;
        sx = 0.5f * u + 0.7f;
        a = 0.2f * u + 0.8f;
        dx = -47.0f - 27.0f * u;
        dy = -2.0f;
    } else if (t < 40.0f) {
        u = (t - 26.0f) / 14.0f;
        sx = 1.2f - 0.5f * u;
        a = 1.0f - 0.2f * u;
        dx = 27.0f * u + -74.0f;
        dy = -2.0f;
    } else if (t < 50.0f) {
        u = (t - 40.0f) / 10.0f;
        sx = 0.1f * u + 0.7f;
        a = 0.8f;
        dx = -47.0f - 7.0f * u;
        dy = -2.0f;
    } else {
        sx = 0.8f;
        a = sx;
        dx = -54.0f;
        dy = -2.0f;
    }
    fn_8016918C(e->obj, 0x8A2, 0, e->x + dx, e->y + dy, sx, sx, 1.0f, 1.0f, 1.0f, a * e->alpha);
}

extern "C" void fn_8013E108(Effect *e) {
    if (e->flags & 2) {
        e->flags &= ~2;
        return;
    }
    float t = e->t + lbl_806D76F4;
    e->t = t;
    if (t >= lbl_806D7750) {
        e->t = lbl_806D770C;
    }
}

Effect1::Effect1() {
    vptr = SpriteEffects_data_8048EB24;
    flags = 2;
    t = lbl_806D770C;
}

extern "C" void fn_8013E194(Effect *e) {
    float t;
    float u;
    float dx;
    float dy;
    float sx;
    float a;

    t = e->t;
    if (t < 24.0f) {
        Effect_DrawSprite(e, 0x89D, e->alpha);
    } else if (t < 28.0f) {
        Effect_DrawSprite(e, 0x89E, e->alpha);
    } else if (t < 32.0f) {
        Effect_DrawSprite(e, 0x89F, e->alpha);
    } else if (t < 45.0f) {
        Effect_DrawSprite(e, 0x8A0, e->alpha);
    } else if (t < 50.0f) {
        Effect_DrawSprite(e, 0x89F, e->alpha);
    } else if (t < 58.0f) {
        Effect_DrawSprite(e, 0x89E, e->alpha);
    } else if (t < 84.0f) {
        Effect_DrawSprite(e, 0x89D, e->alpha);
    } else if (t < 88.0f) {
        Effect_DrawSprite(e, 0x89C, e->alpha);
    } else if (t < 92.0f) {
        Effect_DrawSprite(e, 0x89B, e->alpha);
    } else if (t < 105.0f) {
        Effect_DrawSprite(e, 0x8A1, e->alpha);
    } else if (t < 110.0f) {
        Effect_DrawSprite(e, 0x89B, e->alpha);
    } else if (t < 116.0f) {
        Effect_DrawSprite(e, 0x89C, e->alpha);
    } else {
        Effect_DrawSprite(e, 0x89D, e->alpha);
    }

    t = e->t;
    if (t >= 60.0f) {
        t -= 60.0f;
    }
    if ((e->flags & 4) == 4) {
        if (t < 10.0f) {
            u = t / 10.0f;
            sx = 0.8f - 0.1f * u;
            a = 0.8f;
        } else if (t < 26.0f) {
            u = (t - 10.0f) / 16.0f;
            sx = 0.5f * u + 0.7f;
            a = 0.2f * u + 0.8f;
        } else if (t < 40.0f) {
            u = (t - 26.0f) / 14.0f;
            sx = 1.2f - 0.5f * u;
            a = 1.0f - 0.2f * u;
        } else if (t < 50.0f) {
            u = (t - 40.0f) / 10.0f;
            sx = 0.1f * u + 0.7f;
            a = 0.8f;
        } else {
            sx = 0.8f;
            a = sx;
        }
        dx = 1.0f;
        dy = 41.0f;
    } else {
        if (t < 10.0f) {
            u = t / 10.0f;
            sx = 0.8f - 0.1f * u;
            a = 0.8f;
            dx = 51.0f - 7.0f * u;
            dy = 0.0f;
        } else if (t < 26.0f) {
            u = (t - 10.0f) / 16.0f;
            sx = 0.5f * u + 0.7f;
            a = 0.2f * u + 0.8f;
            dx = 27.0f * u + 44.0f;
            dy = 0.0f;
        } else if (t < 40.0f) {
            u = (t - 26.0f) / 14.0f;
            sx = 1.2f - 0.5f * u;
            a = 1.0f - 0.2f * u;
            dx = 71.0f - 27.0f * u;
            dy = 0.0f;
        } else if (t < 50.0f) {
            u = (t - 40.0f) / 10.0f;
            sx = 0.1f * u + 0.7f;
            dx = 7.0f * u + 44.0f;
            a = 0.8f;
            dy = 0.0f;
        } else {
            sx = 0.8f;
            dx = 51.0f;
            a = sx;
            dy = 0.0f;
        }
    }
    fn_8016918C(e->obj, 0x8A2, 0, e->x + dx, e->y + dy, sx, sx, 1.0f, 1.0f, 1.0f, a * e->alpha);
}

extern "C" void fn_8013E6B4(Effect *e) {
    if (e->flags & 2) {
        e->flags &= ~2;
        return;
    }
    float t = e->t + lbl_806D76F4;
    e->t = t;
    if (t >= lbl_806D778C) {
        e->t = lbl_806D770C;
    }
}

Effect2::Effect2(int mode) {
    vptr = SpriteEffects_data_8048EB70;
    flags = ((mode << 2) & 4) | 2;
    t = lbl_806D770C;
}

extern "C" void fn_8013E744(Effect *e) {
    float t;
    float u;
    float dx;
    float dy;
    float sx;
    float a;

    t = e->t;
    if (t < 10.0f) {
        Effect_DrawSprite(e, 0x896, e->alpha);
    } else if (t < 15.0f) {
        Effect_DrawSprite(e, 0x897, e->alpha);
    } else if (t < 25.0f) {
        Effect_DrawSprite(e, 0x898, e->alpha);
        u = (t - 15.0f) / 10.0f;
        Effect_DrawSprite(e, 0x899, u * e->alpha);
    } else if (t < 35.0f) {
        Effect_DrawSprite(e, 0x898, e->alpha);
        u = (t - 25.0f) / 10.0f;
        Effect_DrawSprite(e, 0x899, (1.0f - u) * e->alpha);
    } else if (t < 40.0f) {
        Effect_DrawSprite(e, 0x897, e->alpha);
    } else if (t < 45.0f) {
        Effect_DrawSprite(e, 0x896, e->alpha);
    } else {
        Effect_DrawSprite(e, 0x896, e->alpha);
    }

    t = e->t;
    if (t < 10.0f) {
        u = t / 10.0f;
        sx = 0.8f - 0.1f * u;
        a = 0.8f;
        dx = 71.0f - 7.0f * u;
        dy = -4.0f;
    } else if (t < 26.0f) {
        u = (t - 10.0f) / 16.0f;
        sx = 0.5f * u + 0.7f;
        a = 0.2f * u + 0.8f;
        dx = 32.0f * u + 64.0f;
        dy = -4.0f;
    } else if (t < 40.0f) {
        u = (t - 26.0f) / 14.0f;
        sx = 1.2f - 0.5f * u;
        a = 1.0f - 0.2f * u;
        dx = 96.0f - 32.0f * u;
        dy = -4.0f;
    } else if (t < 50.0f) {
        u = (t - 40.0f) / 10.0f;
        sx = 0.1f * u + 0.7f;
        dx = 7.0f * u + 64.0f;
        a = 0.8f;
        dy = -4.0f;
    } else {
        sx = 0.8f;
        dx = 71.0f;
        a = sx;
        dy = -4.0f;
    }
    fn_8016918C(e->obj, 0x8A8, 0, e->x + dx, e->y + dy, sx, sx, 1.0f, 1.0f, 1.0f, a * e->alpha);
}

extern "C" void fn_8013EAB4(Effect *e) {
    if (e->flags & 2) {
        e->flags &= ~2;
        return;
    }
    e->t += lbl_806D76F4;
    if (e->t >= lbl_806D7750) {
        e->t = lbl_806D770C;
    }
}

Effect3::Effect3() {
    vptr = SpriteEffects_data_8048EB9C;
    flags = 2;
    t = lbl_806D770C;
}

extern "C" void fn_8013EB44(void) {
}

extern "C" void fn_8013EB48(void) {
}

extern "C" void fn_8013EB4C(void) {
}

extern "C" EffectBase *dtor_8013EB50(EffectBase *e, short flag) {
    if (e) {
        e->vptr = lbl_8048EB44;
        if (flag > 0) {
            operator delete(e);
        }
    }
    return e;
}

extern "C" void fn_8013EB98(void) {
}

extern "C" void fn_8013EB9C(void) {
}

Effect2::~Effect2() {
    vptr = SpriteEffects_data_8048EB70;
}

Effect3::~Effect3() {
    vptr = SpriteEffects_data_8048EB9C;
}

struct EffectHolder {
    char pad[0x2c];
    void **items[3];
};

extern "C" void fn_8013EC58(EffectHolder *h) {
    int i;
    for (i = 0; i < 3; i++) {
        if (h->items[i]) {
            fn_801A0004(*h->items[i]);
        }
    }
}
