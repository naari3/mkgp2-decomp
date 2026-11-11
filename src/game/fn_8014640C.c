/*
 * 0x80146410..0x80147468: lap select controller.
 */
#pragma cplusplus on
#include "libc/stdarg.h"

#include "game/types/InputPlayer.h"
#include "game/types/VObjC.h"
#include "game/types/Countdown.h"
#include "game/types/SelSlot.h"
#include "game/types/LapSel.h"
#include "game/types/TripleObj.h"

struct XfSlot {
    float ox, oy, scx, scy;
    float m0, m1, m2, m3;
    float sel;
    float t;
    void Reset() {
        ox = 0.0f;
        oy = 0.0f;
        scx = 1.0f;
        scy = 1.0f;
        m0 = 1.0f;
        m1 = 1.0f;
        m2 = 1.0f;
        m3 = 1.0f;
    }
};
struct XfPanel {
    int ctx;
    char pad4[0x20];
    XfSlot slots[2];
};

/* TOP-END */

class LapItem;
class LapPanel;
extern "C" {
void **GetInputManager(void);
class InputPlayer *InputMgr_GetPlayer(void **mgr, int idx);
void fn_801FE27C(int n);
void fn_801FE390(void);
extern const float lbl_806D7B58;
extern const float lbl_806D7B5C;
void fn_801674AC(void *p);
extern void fn_801675A4(void *p);
#ifdef __MWERKS__
void fn_8016918C(int ctx, int a, int b, float x, float y, float sx, float sy, float c0, float c1, float c2, float c3);
#else
/* The definition orders its int and float parameters differently; see docs/notes/port_abi.md. */
extern void fn_8016918C(int, int, float, float, float, float, float, float, float, float, int);
static inline void fn_8016918C_Reordered(int ctx, int a, int b, float x, float y, float sx, float sy, float c0, float c1, float c2, float c3) { fn_8016918C(ctx, a, x, y, sx, sy, c0, c1, c2, c3, b); }
#define fn_8016918C fn_8016918C_Reordered
#endif
extern void fn_801FEF18(struct Countdown *c, int timer);
extern unsigned int lbl_806D7B60;
extern unsigned int lbl_806D7B64;
extern unsigned int lbl_806D7B68;
extern unsigned int lbl_806D7B6C;
extern unsigned int lbl_806D7B70;
extern unsigned int lbl_806D7B74;
extern unsigned int lbl_806D7B78;
extern unsigned int lbl_806D7B7C;
extern unsigned int lbl_806D7B80;
extern unsigned int lbl_806D7B84;
extern unsigned int lbl_806D7B88;
extern unsigned int lbl_806D7B8C;
extern unsigned int lbl_806D7B90;
extern unsigned int lbl_806D7B94;
extern unsigned int lbl_806D7B98;
extern unsigned int lbl_806D7B9C;
extern unsigned int lbl_806D7BA0;
extern unsigned int lbl_806D7BA4;
extern unsigned int lbl_806D7BA8;
extern unsigned int lbl_806D7BAC;
extern unsigned int lbl_806D7BB0;
extern unsigned int lbl_806D7BB4;
extern unsigned int lbl_806D7BB8;
extern void fn_80146160(LapItem *p);
extern void fn_80146188(LapItem *p);
extern void fn_80167310(void *p);
extern void fn_8016733C(void *p);
extern void fn_801673A8(void *p);
extern void fn_801673D4(void *p);
extern void fn_801FE348(void);
extern void fn_801FEF34(struct Countdown *c, float x, float y);
extern struct Countdown *fn_801FF00C(int a, int b);
extern unsigned int lbl_806D7BBC;
extern unsigned int lbl_806D7BC0;
extern unsigned int lbl_806D7BC4;
extern unsigned int lbl_806D7BC8;
extern unsigned int lbl_806D7BCC;
extern unsigned int lbl_806D7BD0;
extern unsigned int lbl_806D7BD4;
extern unsigned int lbl_806D7BD8;
extern unsigned int lbl_806D7BDC;
extern unsigned int lbl_806D7BE0;
extern unsigned int lbl_806D7BE4;
extern unsigned int lbl_806D7BE8;
extern unsigned int lbl_806D7BEC;
extern unsigned int lbl_806D7BF0;
extern unsigned int lbl_806D7BF4;
extern unsigned int lbl_806D7BF8;
extern unsigned int lbl_806D7BFC;
extern unsigned int lbl_806D7C00;
extern unsigned int lbl_806D7C04;
extern unsigned int lbl_806D7C08;
extern const float lbl_80362620[2][2];
extern const float LapSelect_80146410_rodata_80362630[2][4];
extern const float lbl_8048EFB8[2][2];
void fn_801681E8(int ctx, const char *fmt, ...);
int vsprintf(char *buf, const char *fmt, va_list ap);
int fn_80146410(LapSel *self);
void fn_80146574(LapSel *self);
class LapPanel;
void fn_8014660C(LapPanel *self);
void fn_80146960(LapPanel *self);
void fn_80147200(XfPanel *self, int idx, const char *fmt, float x, float y, float sx, float sy, float c0, float c1, float c2, float c3, ...);
void fn_801473DC(XfPanel *self, int idx, int a, int b, float x, float y, float sx, float sy, float c0, float c1, float c2, float c3);

}

inline bool Countdown_Tick(Countdown *c) {
    if (c->delay > 0) {
        c->delay--;
        return 0;
    }
    if (c->state == 1) {
        c->state = 2;
    }
    return c->state <= 0;
}
inline bool TickTimer(LapSel *self) {
    if (self->timer > 0) {
        self->timer--;
        fn_801FE27C(self->timer);
        return 1;
    }
    return 0;
}
inline void Select(LapSel *self, int idx) {
    if (self->mode == 1 && self->cur != idx) {
        if (self->slots[self->cur].t >= lbl_806D7B58) {
            self->slots[self->cur].t = lbl_806D7B5C;
        }
        self->cur = idx;
        self->f1C = lbl_806D7B58;
        fn_801FE390();
    }
}





#include "game/CSParts.h"
#include "game/types/VObj14.h"
#include "game/types/LapCtrl.h"
extern "C" void YnSelectSound(void *);
extern "C" void fn_801676AC(void *, int);
struct LapHudText { int f0, f4, f8; LapHudText(int); };
struct HudGaugeData { int kind; char pad4[0x10]; };
class HudGauge : public HudGaugeData {
public:
    virtual ~HudGauge();
    virtual void Start();
    void SetKind(int v) { if (v >= 0 && v < 8) kind = v; }
};
class LapHudGauge : public HudGauge { public: int f18; LapHudGauge(); };
class clCSPartsYNWindow : public clCSPartsInerface {
public:
    int mode;
    float f1C;
    int cur;
    XfSlot slots[2];
    int timer;
    Countdown *cd;
    LapHudText *text;
    LapHudGauge *gauge;
    clCSPartsYNWindow(int n);
    virtual ~clCSPartsYNWindow();
    virtual void Update();
    virtual void Draw();
    virtual void m1C();
    virtual bool IsReady();
    virtual void DrawExtra();
};
void clCSPartsYNWindow::DrawExtra() {}

bool clCSPartsYNWindow::IsReady()
{
    LapSel *self = (LapSel *)this;
    if (!TickTimer(self)) {
        return 1;
    }
    if (self->cur == 0) {
        if (InputMgr_GetPlayer(GetInputManager(), 0)->Pressed(0x20)) {
            Select(self, 1);
        }
    } else {
        if (InputMgr_GetPlayer(GetInputManager(), 0)->Pressed(0x10)) {
            Select(self, 0);
        }
    }
    return 0;
}

void clCSPartsYNWindow::m1C()
{
    LapSel *self = (LapSel *)this;
    fn_801674AC(self->p7c);
    if (self->cd) {
        if (Countdown_Tick(self->cd)) {
            ((VObjC *)self->cd)->v14();
        }
    }
}

struct LapHead {
    int ctx;
    unsigned char done;
    char pad5[0xf];
};
class LapItem : public LapHead {
public:
    virtual void v8();
    virtual void vC();
    virtual void v10();
    virtual void Update();
    virtual void Draw();
};
class LapPanel : public LapHead {
public:
    virtual void v8();
    virtual void vC();
    virtual void v10();
    virtual void v14();
    virtual void v18();
    virtual void v1C();
    virtual bool IsReady();
    virtual void DrawExtra();
    int mode;
    float f1C;
    int cur;
    XfSlot slots[2];
    int timer;
    Countdown *cd;
    void *p7c;
    LapItem *item;
};

inline bool Countdown_Done(Countdown *c) {
    if (c->delay > 0) {
        return 0;
    }
    return c->state <= 0;
}

void clCSPartsYNWindow::Draw()
{
    clCSPartsYNWindow *self = this;
    if (self->mode == 5) {
        return;
    }
    for (int i = 0; i < 2; i++) {
        XfSlot *s = &self->slots[i];
        fn_8016918C(self->obj, 0x8cc, 0, s->ox, s->oy, s->scx, s->scy, s->m0, s->m1, s->m2, s->m3);
        float t = s->t;
        if (t >= 0.0f) {
            float sx, sy;
            if (t <= 15.0f) {
                float k = 0.06666667f * t;
                sx = 0.15f * k + 2.5f;
                sy = 0.1f * k + 2.5f;
            } else if (t <= 20.0f) {
                float r = 0.2f * (t - 15.0f);
                sx = 2.65f - 0.05f * r;
                sy = 2.6f + 0.05f * r;
            } else if (t <= 35.0f) {
                float k = 0.06666667f * (t - 20.0f);
                sx = 2.6f - 0.2f * k;
                sy = 2.65f - 0.3f * k;
            } else if (t <= 40.0f) {
                float r = 0.2f * (t - 35.0f);
                sx = 2.4f - 0.05f * r;
                sy = 2.35f + 0.05f * r;
            } else {
                float k = 0.1f * (t - 40.0f);
                sx = 0.12f * k + 2.35f;
                sy = 0.07f * k + 2.4f;
            }
            float alpha;
            if (t <= 20.0f) {
                alpha = 0.05f * t;
            } else if (t <= 35.0f) {
                alpha = 1.0f;
            } else {
                alpha = 0.06666667f * (50.0f - t);
            }
            fn_8016918C(self->obj, 0x730, 1, s->ox - 9.0f * s->scx, 11.0f * s->scy + s->oy, s->scx * sx, s->scy * sy, s->m0, s->m1, s->m2, s->m3 * alpha);
        }
    }
    self->DrawExtra();
    fn_8016918C(self->obj, 0x8ca, 0, self->slots[0].ox - 12.0f * self->slots[0].scx, self->slots[0].oy - 88.0f * self->slots[0].scy,
                self->slots[0].scx, self->slots[0].scy, self->slots[0].m0, self->slots[0].m1, self->slots[0].m2, self->slots[0].m3);
    fn_8016918C(self->obj, 0x8cb, 0, self->slots[1].ox - 12.0f * self->slots[1].scx, self->slots[1].oy - 88.0f * self->slots[1].scy,
                self->slots[1].scx, self->slots[1].scy, self->slots[1].m0, self->slots[1].m1, self->slots[1].m2, self->slots[1].m3);
    if (self->cd && Countdown_Done(self->cd)) {
        fn_801FEF18(self->cd, self->timer);
        ((VObjC *)self->cd)->v10();
    }
    fn_801675A4(self->text);
    ((LapItem *)self->gauge)->Update();
    ((LapItem *)self->gauge)->Draw();
}

void clCSPartsYNWindow::Update()
{
    clCSPartsYNWindow *self = this;
    if (self->mode == 5) {
        return;
    }
    switch (self->mode) {
    case 0: {
        float k = 0.06666667f * self->f1C;
        for (int i = 0; i < 2; i++) {
            self->slots[i].ox = 0.0f;
            self->slots[i].oy = 0.0f;
            self->slots[i].scx = k;
            self->slots[i].scy = k;
            self->slots[i].m0 = 1.0f;
            self->slots[i].m1 = 1.0f;
            self->slots[i].m2 = 1.0f;
            self->slots[i].m3 = 1.0f;
        }
        if ((self->f1C += 1.0f) >= 15.0f) {
            self->mode = 1;
            self->f1C = 0.0f;
            fn_801673D4(self->text);
            fn_8016733C(self->text);
            if (self->cd == 0) {
                self->cd = fn_801FF00C(0, 0);
                fn_801FEF34(self->cd, 586.0f, 55.0f);
            }
            if (self->cur == 0) {
                fn_80146160(((LapItem *)self->gauge));
            } else {
                fn_80146188(((LapItem *)self->gauge));
            }
        }
        break;
    }
    case 1:
        for (int i = 0; i < 2; i++) {
            XfSlot *s = &self->slots[i];
            s->ox = 0.0f;
            s->oy = 0.0f;
            if (i == self->cur && s->sel == 15.0f) {
                float t = self->f1C;
                if (t < 15.0f) {
                    float k = 0.06666667f * t;
                    s->scx = 0.06f * k + 1.0f;
                    s->scy = 0.04f * k + 1.0f;
                } else if (t < 20.0f) {
                    float r = 0.2f * (t - 15.0f);
                    s->scx = 1.06f - 0.02f * r;
                    s->scy = 1.04f + 0.02f * r;
                } else if (t < 35.0f) {
                    float k = 0.06666667f * (t - 20.0f);
                    s->scx = 1.04f - 0.08f * k;
                    s->scy = 1.06f - 0.12f * k;
                } else if (t < 40.0f) {
                    float r = 0.2f * (t - 35.0f);
                    s->scx = 0.96f - 0.02f * r;
                    s->scy = 0.94f + 0.02f * r;
                } else {
                    float k = 0.1f * (t - 40.0f);
                    s->scx = 0.06f * k + 0.94f;
                    s->scy = 0.04f * k + 0.96f;
                }
                if ((self->f1C += 1.0f) >= 50.0f) {
                    self->f1C = 0.0f;
                }
                if (i == 0) {
                    fn_80146160(((LapItem *)self->gauge));
                } else {
                    fn_80146188(((LapItem *)self->gauge));
                }
            } else {
                s->scx = 1.0f;
                s->scy = 1.0f;
            }
            s->m0 = 1.0f;
            s->m1 = 1.0f;
            s->m2 = 1.0f;
            s->m3 = 1.0f;
        }
        if (self->IsReady()) {
            self->mode = 2;
            self->f1C = 0.0f;
        }
        break;
    case 2:
        for (int i = 0; i < 2; i++) {
            self->slots[i].Reset();
        }
        if (self->slots[self->cur].sel == 15.0f) {
            if (self->cur == 0) {
                self->mode = 3;
                if (self->slots[0].t < 0.0f) {
                    self->slots[0].t = 0.0f;
                }
            } else {
                self->mode = 4;
            }
            self->f1C = 0.0f;
            fn_801673A8(self->text);
            fn_80167310(self->text);
            fn_801FE348();
        }
        break;
    case 3: {
        bool done = true;
        for (int i = 0; i < 2; i++) {
            self->slots[i].Reset();
            if (self->slots[i].t >= 0.0f) {
                done = false;
            }
        }
        if (done) {
            self->mode = 4;
            self->f1C = 0.0f;
        }
        break;
    }
    case 4:
        for (int i = 0; i < 2; i++) {
            XfSlot *s = &self->slots[i];
            if (i == self->cur) {
                float t = self->f1C;
                if (t <= 5.0f) {
                    s->ox = 0.0f;
                    s->oy = 0.0f;
                    s->scx = 1.0f - 0.2f * (0.2f * self->f1C);
                    s->scy = s->scx;
                } else if (t <= 10.0f) {
                    s->ox = 0.0f;
                    s->oy = 0.0f;
                    s->scx = 0.8f - 0.05f * (0.2f * (self->f1C - 5.0f));
                    s->scy = s->scx;
                } else if (t <= 25.0f) {
                    float k = 0.06666667f * (t - 10.0f);
                    s->ox = k * lbl_8048EFB8[i][0];
                    s->oy = k * lbl_8048EFB8[i][1];
                    s->scx = 1.75f * k + 0.75f;
                    s->scy = s->scx;
                }
            } else {
                s->ox = 0.0f;
                s->oy = 0.0f;
                if (self->f1C <= 10.0f) {
                    s->scx = 0.1f * (10.0f - self->f1C);
                    s->scy = s->scx;
                } else {
                    s->scx = 0.0f;
                    s->scy = 0.0f;
                }
            }
            s->m0 = 1.0f;
            s->m1 = 1.0f;
            s->m2 = 1.0f;
            if (self->f1C <= 10.0f) {
                s->m3 = 1.0f;
            } else if (self->f1C <= 25.0f) {
                s->m3 = 0.06666667f * (25.0f - self->f1C);
            } else {
                s->m3 = 0.0f;
            }
        }
        if ((self->f1C += 1.0f) >= 30.0f) {
            self->mode = 5;
            self->f1C = 0.0f;
            self->active = 1;
        }
        break;
    }
    for (int i = 0; i < 2; i++) {
        XfSlot *s = &self->slots[i];
        if (i == self->cur) {
            if (s->sel < 15.0f) {
                s->sel += 1.0f;
                if (s->sel > 15.0f) {
                    s->sel = 15.0f;
                }
            }
        } else {
            if (s->sel > 0.0f) {
                s->sel -= 1.0f;
                if (s->sel < 0.0f) {
                    s->sel = 0.0f;
                }
            }
        }
        s->ox += lbl_80362620[i][0];
        s->oy += lbl_80362620[i][1];
        float k;
        if (s->sel < 5.0f) {
            k = 0.75f - 0.08f * (0.2f * s->sel);
        } else if (s->sel < 10.0f) {
            k = 0.41f * (0.2f * (s->sel - 5.0f)) + 0.67f;
        } else {
            k = 1.08f - 0.08f * (0.2f * (s->sel - 10.0f));
        }
        s->scx *= k;
        s->scy *= k;
        if (i == self->cur) {
            s->m0 *= LapSelect_80146410_rodata_80362630[0][0];
            s->m1 *= LapSelect_80146410_rodata_80362630[0][1];
            s->m2 *= LapSelect_80146410_rodata_80362630[0][2];
            s->m3 *= LapSelect_80146410_rodata_80362630[0][3];
        } else {
            s->m0 *= LapSelect_80146410_rodata_80362630[1][0];
            s->m1 *= LapSelect_80146410_rodata_80362630[1][1];
            s->m2 *= LapSelect_80146410_rodata_80362630[1][2];
            s->m3 *= LapSelect_80146410_rodata_80362630[1][3];
        }
        if (s->t >= 0.0f) {
            s->t += 1.0f;
            if (s->t > 50.0f) {
                if (self->mode == 1 || self->mode == 2) {
                    s->t = 0.0f;
                } else {
                    s->t = -1.0f;
                }
            }
        }
    }
}

extern "C" void fn_80147200(XfPanel *self, int idx, const char *fmt, float x, float y, float sx, float sy, float c0, float c1, float c2, float c3, ...)
{
    if (idx < 0 || idx >= 2) {
        return;
    }
    char buf[256] = {0};
    va_list ap;
    va_start(ap, c3);
    vsprintf(buf, fmt, ap);
    va_end(ap);
    fn_801681E8(self->ctx, buf, x * self->slots[idx].scx + self->slots[idx].ox, y * self->slots[idx].scy + self->slots[idx].oy, sx * self->slots[idx].scx, sy * self->slots[idx].scy, c0 * self->slots[idx].m0, c1 * self->slots[idx].m1, c2 * self->slots[idx].m2, c3 * self->slots[idx].m3);
}

extern "C" void fn_801473DC(XfPanel *self, int idx, int a, int b, float x, float y, float sx, float sy, float c0, float c1, float c2, float c3)
{
    if (idx < 0 || idx >= 2) {
        return;
    }
    fn_8016918C(self->ctx, a, b, x * self->slots[idx].scx + self->slots[idx].ox, y * self->slots[idx].scy + self->slots[idx].oy, sx * self->slots[idx].scx, sy * self->slots[idx].scy, c0 * self->slots[idx].m0, c1 * self->slots[idx].m1, c2 * self->slots[idx].m2, c3 * self->slots[idx].m3);
}


typedef struct Obj {
    unsigned char pad_0[0x20];
    int f_20;
} Obj;

extern "C" int fn_80147468(Obj *obj) {
    return obj->f_20;
}

extern "C" int fn_80147470(LapCtrl *self, int idx) {
    if (idx < 0 || idx >= 2) {
        return 0;
    }
    if (self->mode == 1) {
        if (self->cur != idx) {
            if (self->slots[self->cur].t >= 0.0f) {
                self->slots[self->cur].t = -1.0f;
            }
            self->cur = idx;
            self->f1C = 0.0f;
            YnSelectSound(self);
        }
        return 1;
    }
    return 0;
}

extern "C" void fn_801474FC(LapCtrl *self, int idx) {
    if (idx < 0 || idx >= 2) {
        return;
    }
    if (self->slots[idx].t < 0.0f) {
        self->slots[idx].t = 0.0f;
    }
}

extern "C" int fn_80147530(char *self) {
    if (*(int *)(self + 0x74) > 0) {
        *(int *)(self + 0x74) = *(int *)(self + 0x74) - 1;
        fn_801FE27C(*(int *)(self + 0x74));
        return 1;
    }
    return 0;
}

extern "C" void fn_80147574(char *self, int v) {
    if (v < 0) {
        return;
    }
    *(int *)(self + 0x74) = v;
}

clCSPartsYNWindow::~clCSPartsYNWindow() {
    if (cd != 0) ((VObjC *)cd)->vC();
    fn_801676AC(text, 1);
    delete (VObj14 *)gauge;
}
clCSPartsYNWindow::clCSPartsYNWindow(int n) {
    int i;
    mode = 0;
    f1C = 0.0f;
    cur = n;
    timer = 1200;
    cd = 0;
    text = new LapHudText(0);
    gauge = new LapHudGauge;
    gauge->SetKind(obj);
    for (i = 0; i < 2; i++) {
        slots[i].ox = 0.0f;
        slots[i].oy = 0.0f;
        slots[i].scx = 0.0f;
        slots[i].scy = 0.0f;
        if (i == cur) slots[i].sel = 15.0f;
        else slots[i].sel = 0.0f;
        slots[i].t = -1.0f;
    }
}
