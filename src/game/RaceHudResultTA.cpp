#include "game/types/RaceHud_support.h"
extern "C" {
extern const float taRankCurve[263] = {
    1.0f, 0.7f, 0.9f, 0.0f, 0.0f, 500.0f, 66.66667f, 1000.0f,
    66.66667f, 2000.0f, 66.66667f, 3000.0f, 66.66667f, 4000.0f, 66.66667f, 5000.0f,
    66.66667f, 0.0f, 0.0f, 500.0f, 66.66667f, 1000.0f, 66.66667f, 2000.0f,
    66.66667f, 3000.0f, 66.66667f, 4000.0f, 66.66667f, 5000.0f, 66.66667f, 0.0f,
    0.0f, 500.0f, 66.66667f, 1000.0f, 66.66667f, 2000.0f, 66.66667f, 3000.0f,
    66.66667f, 4000.0f, 66.66667f, 5000.0f, 66.66667f, 0.0f, 0.0f, 500.0f,
    66.66667f, 1000.0f, 66.66667f, 2000.0f, 66.66667f, 3000.0f, 66.66667f, 4000.0f,
    66.66667f, 5000.0f, 66.66667f, 0.0f, 0.0f, 500.0f, 66.66667f, 1000.0f,
    66.66667f, 2000.0f, 66.66667f, 3000.0f, 66.66667f, 4000.0f, 66.66667f, 5000.0f,
    66.66667f, 0.0f, 0.0f, 500.0f, 66.66667f, 1000.0f, 66.66667f, 2000.0f,
    66.66667f, 3000.0f, 66.66667f, 4000.0f, 66.66667f, 5000.0f, 66.66667f, 0.0f,
    0.0f, 500.0f, 66.66667f, 1000.0f, 66.66667f, 2000.0f, 66.66667f, 3000.0f,
    66.66667f, 4000.0f, 66.66667f, 5000.0f, 66.66667f, 0.0f, 0.0f, 500.0f,
    66.66667f, 1000.0f, 66.66667f, 2000.0f, 66.66667f, 3000.0f, 66.66667f, 4000.0f,
    66.66667f, 5000.0f, 66.66667f, 0.0f, 0.0f, 500.0f, 66.66667f, 1000.0f,
    66.66667f, 2000.0f, 66.66667f, 3000.0f, 66.66667f, 4000.0f, 66.66667f, 5000.0f,
    66.66667f, 0.0f, 0.0f, 500.0f, 66.66667f, 1000.0f, 66.66667f, 2000.0f,
    66.66667f, 3000.0f, 66.66667f, 4000.0f, 66.66667f, 5000.0f, 66.66667f, 0.0f,
    0.0f, 500.0f, 66.66667f, 1000.0f, 66.66667f, 2000.0f, 66.66667f, 3000.0f,
    66.66667f, 4000.0f, 66.66667f, 5000.0f, 66.66667f, 0.0f, 0.0f, 500.0f,
    66.66667f, 1000.0f, 66.66667f, 2000.0f, 66.66667f, 3000.0f, 66.66667f, 4000.0f,
    66.66667f, 5000.0f, 66.66667f, 0.0f, 0.0f, 500.0f, 83.333336f, 1000.0f,
    83.333336f, 2000.0f, 83.333336f, 3000.0f, 83.333336f, 4000.0f, 83.333336f, 5000.0f,
    83.333336f, 0.0f, 0.0f, 500.0f, 83.333336f, 1000.0f, 83.333336f, 2000.0f,
    83.333336f, 3000.0f, 83.333336f, 4000.0f, 83.333336f, 5000.0f, 83.333336f, 0.0f,
    0.0f, 500.0f, 83.333336f, 1000.0f, 83.333336f, 2000.0f, 83.333336f, 3000.0f,
    83.333336f, 4000.0f, 83.333336f, 5000.0f, 83.333336f, 0.0f, 0.0f, 500.0f,
    83.333336f, 1000.0f, 83.333336f, 2000.0f, 83.333336f, 3000.0f, 83.333336f, 4000.0f,
    83.333336f, 5000.0f, 83.333336f, 0.0f, 0.0f, 500.0f, 83.333336f, 1000.0f,
    83.333336f, 2000.0f, 83.333336f, 3000.0f, 83.333336f, 4000.0f, 83.333336f, 5000.0f,
    83.333336f, 0.0f, 0.0f, 500.0f, 83.333336f, 1000.0f, 83.333336f, 2000.0f,
    83.333336f, 3000.0f, 83.333336f, 4000.0f, 83.333336f, 5000.0f, 83.333336f, 37.0f,
    75.0f, 113.0f, 151.0f, 189.0f, 227.0f, 265.0f, 303.0f
};
}
struct HudGaugeData {
    int kind;
    char pad4[0x10];
};

class HudGauge : public HudGaugeData {
public:
    virtual ~HudGauge();
    virtual void Start();
    void SetKind(int v) {
        if (v >= 0 && v < 8) {
            kind = v;
        }
    }
};

#include "game/types/clResultTask.h"

struct CountText {
    char pad0[0x1C];
    CountText(int layer, int flag);
};


#include "game/types/clCSPartsMsgWindow.h"
struct clCSPartsAppearGhost;
class StrDigit : public HudGauge {
public:
    int f18;
    StrDigit(char *res);
};

class StrGauge : public HudGauge {
public:
    char pad18[0x10];
    StrGauge();
};

struct StrBox {
    char pad0[0x20];
    StrBox(int a, int b, int c, int d, int e);
};

class clCSResultTA : public clCTaskInterface {
public:
    int layer;
    float f14;
    float f18;
    float f1C;
    int f20;
    int rank;
    unsigned char f28;
    unsigned char f29;
    float time;
    float f30;
    CountText *text;
    StrGauge *gauge;
    StrDigit *digits[9];
    clCSPartsAppearGhost *f60;
    int f64;
    StrBox *box;
    int f6C;
    short f70[6];
    clCSResultTA(int layer, int id);
    virtual void Draw();
    virtual ~clCSResultTA();
    virtual void Delete();
    virtual void Update();
};

struct clCSPartsAppearGhost : clCSPartsMsgWindow {
    clCSPartsAppearGhost() : clCSPartsMsgWindow() {}
    virtual void m20();
    virtual ~clCSPartsAppearGhost();
    void PrintClassNames();
    void SetKind(int v) { if (v >= 0 && v < 8) obj = v; }
};



struct GaugePos {
    int kind;
    unsigned char done;
    char pad5[3];
    float x;
    float y;
    float alpha;
    void SetPos(float px, float py) {
        x = px;
        y = py;
    }
};

inline bool Countdown_IsDone(Countdown *c) {
    if (c->delay > 0) {
        return 0;
    }
    return c->state <= 0;
}

#include "game/types/TaEntry.h"

inline void *StrTitle_GetInstance() {
    if (lbl_806D10A0 == 0) {
        return 0;
    }
    return lbl_806D10A0;
}

inline unsigned char clCSResultTA_Pressed(int mask) {
    return InputMgr_GetPlayer(GetInputManager(), 0)->Pressed(mask);
}

inline void clCSResultTA_DrawRank(clCSResultTA *self, float a) {
    int i;
    float t;
    LUT_Sin12Bit(3.0f * self->f1C);
    if (self->f18 > 10.0f) {
        t = Saturate_Double((self->f18 - 10.0f) / 25.0f, 0.0f, 1.0f);
        fn_80169468(self->layer, 0x9A4, 0, 173.0f - 320.0f * (1.0f - t), 112.0f, 1.0f, 1.0f, 1.0f, a);
    }
    for (i = 0; i < 9; i++) {
        if (!(self->f18 < 10.0f + 2.0f * (float)i)) {
            t = Saturate_Double((self->f18 - (8.0f + 2.0f * (float)i)) / 25.0f, 0.0f, 1.0f);
            if (0.0f == t) {
                self->digits[i]->Start();
            }
            ((GaugePos *)self->digits[i])->SetPos((40.0f * (float)i + 139.0f) - 320.0f * (1.0f - t), 155.0f);
            ((GaugePos *)self->digits[i])->alpha = a;
            ((VObj14 *)self->digits[i])->v14();
            ((VObj14 *)self->digits[i])->v18();
        }
    }
    self->f18 += 1.0f;
    self->f1C += 1.0f;
    if (self->f1C >= 60.0f) {
        self->f1C = 0.0f;
    }
    ((GaugePos *)self->gauge)->alpha = a;
    ((VObj14 *)self->gauge)->v14();
    ((VObj14 *)self->gauge)->v18();
}


















void clCSResultTA::Delete() {
    delete this;
}

void clCSPartsAppearGhost::m20() {
    Put(0x580, 0, 134.0f, lbl_806D7D68, lbl_806D7D60, lbl_806D7D60, lbl_806D7D60, lbl_806D7D60, lbl_806D7D60, lbl_806D7D60);
    if (isJapanese() == 1) {
        Print(-212.0f, -52.0f, lbl_806D7D60, lbl_806D7D60, lbl_806D7D60, lbl_806D7D60, lbl_806D7D60, lbl_806D7D60, "Staff ghost car");
        Print(-212.0f, -22.0f, lbl_806D7D60, lbl_806D7D60, lbl_806D7D60, lbl_806D7D60, lbl_806D7D60, lbl_806D7D60, "     is available !");
    } else {
        Print(-212.0f, -52.0f, lbl_806D7D60, lbl_806D7D60, lbl_806D7D60, lbl_806D7D60, lbl_806D7D60, lbl_806D7D60, "\203X\203^\203b\203t\203S\201[\203X\203g\202\252\217o\214\273");
        Print(-212.0f, -22.0f, lbl_806D7D60, lbl_806D7D60, lbl_806D7D60, lbl_806D7D60, lbl_806D7D60, lbl_806D7D60, "\202\267\202\351\202\346\202\244\202\311\202\310\202\350\202\334\202\265\202\275\201I");
    }
}

/* fakematch: uncalled diagnostic member places the shared class-name pool,
 * following clLineManager::PrintLines. */
extern "C" int printf(const char *, ...);
void clCSPartsAppearGhost::PrintClassNames() {
    printf("clCSPartsAppearGhost");
    printf("clCSPartsInerface");
    printf("clCSPartsMsgWindow");
}

#pragma use_lmw_stmw on
clCSResultTA::clCSResultTA(int ly, int id) : clCTaskInterface(id) {
    int i;
    layer = ly;
    f14 = lbl_806D7D68;
    f18 = lbl_806D7D68;
    f1C = lbl_806D7D68;
    f20 = 0;
    time = g_totalRaceTime;
    f30 = lbl_806D7E00;
    rank = TaRecord_GetLastInsertedRank();
    f28 = fn_80169DF0();
    f29 = fn_8024F588()[1];
    f60 = 0;
    for (i = 0; i < 6; i++) {
        f70[i] = 0;
    }
    for (i = 0; i < 9; i++) {
        char *res = fn_80167744(8 - i, time) + 0x998;
        digits[i] = new StrDigit(res);
        digits[i]->SetKind(ly);
        digits[i]->Start();
    }
    text = new CountText(ly, 0);
    gauge = new StrGauge;
    f64 = 0;
    gauge->SetKind(ly);
    box = new StrBox(0x74, -1, 0x1872, -1, 4);
    fn_8023CEB4(box);
    fn_8023CD3C(box, 286.0f, 454.0f);
    fn_8023CCF8(box, 345.0f, 450.0f);
    f6C = 0;
    StrPcb_ClearStatusBits(StrPcb_GetInstance(), 4);
    StrPcb_ClearStatusBits(StrPcb_GetInstance(), 8);
}
#pragma use_lmw_stmw reset

clCSResultTA::~clCSResultTA() {
    int i;
    StrPcb_ClearStatusBits(StrPcb_GetInstance(), 4);
    if (text != 0) ((VObjC *)text)->vC();
    delete (VObj14 *)gauge;
    fn_8023CFE0(box, 1);
    if (f60 != 0) delete (VObj14 *)f60;
    for (i = 0; i < 9; i++) delete (VObj14 *)digits[i];
}

clCSPartsAppearGhost::~clCSPartsAppearGhost() {
    fn_80120A08(0x580);
}

void clCSResultTA::Update() {
    clCSResultTA *self = this;
    int i;
    float a;
    float t;
    float x;
    switch (self->f20) {
    case 0:
        clCSResultTA_DrawRank(self, 1.0f);
        if (145.0f == self->f14) {
            StrPcb_SetStatusBits(StrPcb_GetInstance(), 4, 0);
            fn_8023CFD4(self->box);
        }
        if ((self->f14 += 1.0f) >= 450.0f || (self->f14 > 145.0f && (clCSResultTA_Pressed(0x100) || clCSResultTA_Pressed(0x2000)))) {
            fn_8023CFC8(self->box);
            self->f14 = 0.0f;
            self->fC = 1;
            self->f20 = 5;
        }
        break;
    case 1:
        a = 1.0f - self->f14 / 30.0f;
        clCSResultTA_DrawRank(self, a);
        fn_801678FC(self->layer, 0.0f, 0.0f, 0.0f, 0.5f * (1.0f - a));
        if ((self->f14 += 1.0f) >= 30.0f) {
            self->f14 = 0.0f;
            if (self->f29 == 1) {
                self->f20 = 2;
            } else if (self->f28 == 0) {
                self->f20 = 3;
            } else {
                self->f20 = 5;
            }
        }
        break;
    case 2:
        fn_801678FC(self->layer, 0.0f, 0.0f, 0.0f, 0.5f);
        if (self->f60 == 0) {
            clCSPartsAppearGhost *m = new clCSPartsAppearGhost;
            self->f60 = m;
            if (m != 0) {
                self->f60->SetKind(self->layer);
            }
        } else {
            ((VObj14 *)self->f60)->v14();
            if (self->f60->active) {
                delete (VObj14 *)self->f60;
                self->f60 = 0;
                self->f14 = 0.0f;
                if (self->rank >= 0 && self->rank < 10) {
                    if (self->f28 == 0) {
                        self->f20 = 3;
                    } else {
                        self->f20 = 5;
                    }
                } else {
                    self->fC = 1;
                    self->f20 = 6;
                }
            }
        }
        break;
    case 3: {
        TaEntry *e;
        void *p;
        self->f14 += 1.0f;
        fn_801678FC(self->layer, 0.0f, 0.0f, 0.0f, 0.5f);
        t = self->f14;
        x = 284.0f;
        if (t < 10.0f) {
            x += 640.0f;
        } else if (t < 25.0f) {
            x += 640.0f + -660.0f * (t - 10.0f) / 15.0f;
        } else if (t < 30.0f) {
            x += -20.0f + 21.0f * (t - 25.0f) / 5.0f;
        }
        fn_801698B4(self->layer, 0x8AE, 0, x, 60.0f);
        self->f6C = 0;
        e = TaRecord_GetEntry_Current(self->rank);
        wcscpy(e, self->f70);
        p = StrTitle_GetInstance();
        if (p != 0) {
            int ra;
            int rb;
            if (get_title_result(p, &ra, &rb, 0)) {
                e->titleA = ra;
                e->titleB = rb;
            }
        }
        self->f20 = 4;
        self->f14 = 0.0f;
        break;
    }
    case 4:
        self->f14 += 1.0f;
        fn_801678FC(self->layer, 0.0f, 0.0f, 0.0f, 0.5f);
        t = self->f14;
        if (t < 7.0f) {
            x = 50.0f * (t / 7.0f) + 284.0f;
        } else if (t < 13.0f) {
            x = 334.0f - 167.0f * ((t - 7.0f) / 6.0f);
        } else if (t < 17.0f) {
            x = 167.0f - 192.0f * ((t - 13.0f) / 4.0f);
        } else if (t < 20.0f) {
            x = -25.0f - 331.0f * ((t - 17.0f) / 3.0f);
        } else {
            x = -356.0f;
        }
        fn_801698B4(self->layer, 0x8AE, 0, x, 60.0f);
        if (self->f14 > 20.0f) {
            self->f20 = 5;
            self->f14 = 0.0f;
        }
        break;
    case 5:
        if (0.0f == self->f14) {
            fn_80120A08(0x8AE);
        }
        fn_801678FC(self->layer, 0.0f, 0.0f, 0.0f, 0.5f);
        if ((self->f14 += 1.0f) >= 600.0f || clCSResultTA_Pressed(0x100) || clCSResultTA_Pressed(0x2000)) {
            self->fC = 1;
            self->f14 = 0.0f;
            self->f20 = 6;
        }
        break;
    }
    fn_8023CDA8(self->box);
    if (self->text != 0) {
        if (Countdown_IsDone((Countdown *)self->text)) {
            ((VObjC *)self->text)->v10();
        }
    }
    if (self->f60 != 0) {
        ((VObj14 *)self->f60)->v18();
    }
    RumbleUpdate();
}

void clCSResultTA::Draw() {
    fn_8023CD54(box);
    if (text != 0) {
        if (Countdown_Tick((Countdown *)text)) {
            ((VObjC *)text)->v14();
        }
    }
    if (f60 != 0) {
        ((VObj14 *)f60)->v1C();
    }
}
