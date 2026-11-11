/* clCSResultGP: .text 0x801493B0..0x80149D90.
 * Split from RaceHud_80147470.cpp to keep this original file's distinct
 * clYTaskInterface/clCTaskInterface RTTI copies and compiler-emitted vtable.
 * GC/2.6, non-deferred: static positions precede the RTTI names.
 */
#include "game/types/RaceHud_support.h"
#include "game/types/clResultTask.h"
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

struct CountText {
    char pad0[0x1C];
    CountText(int layer, int flag);
};

class CountGauge : public HudGauge {
public:
    char pad18[0x10];
    CountGauge();
};

struct clCSResultGPEntry {
    int count;
    float t;
    VObj *obj;
};

class clCSResultGP : public clCTaskInterface {
public:
    int layer;
    float t;
    unsigned char on;
    RecordCounter *f1C;
    int f20;
    VObj14 *f24;
    int f28;
    clCSResultGPEntry e[6];
    int highlight;
    clCSResultGP(int layer, int id);
    virtual ~clCSResultGP();
    virtual void Delete();
    virtual void Update();
    virtual void Draw();
};


extern const float RaceHud_80147470_rodata_80362858[6] = {80.0f,176.0f,272.0f,368.0f,464.0f,560.0f};
extern "C" void fn_801493B0(CountList *self) {
    if (self->on) {
        int i;
        for (i = 0; i < 6; i++) {
            if (self->e[i].count > 1) {
                self->e[i].obj->vC();
            }
        }
    }
}

void clCSResultGP::Draw() {
    if (((Countdown *)f1C) != 0) {
        if (Countdown_Tick(((Countdown *)f1C))) {
            ((VObjC *)((Countdown *)f1C))->v14();
        }
    }
}

#pragma use_lmw_stmw on
void clCSResultGP::Update() {
    int i;
    if (this->f1C != 0 && this->f1C->count >= 2) {
        this->f1C->vC();
        this->f1C = 0;
    }
    if (this->on) {
        for (i = 0; i < 6; i++) {
            HudRankSlot *slot = RankSlot_GetByIndex(i);
            if (slot->kart >= 0 && this->e[i].count == 0) {
                this->e[i].count = 1;
                this->e[i].obj = (VObj *)new HudModel(slot->kart, 1);
                if (slot->active) {
                    fn_8013C6EC(this->e[i].obj, 0.014f, 0.014f, 0.014f);
                    fn_8013C534(this->e[i].obj, 1.0f, 1.0f, 1.0f, 1.0f);
                    this->highlight = i;
                } else {
                    fn_8013C6EC(this->e[i].obj, 0.007f, 0.007f, 0.007f);
                    fn_8013C534(this->e[i].obj, 1.0f, 1.0f, 1.0f, 1.0f);
                }
            }
        }
        if (this->t > 300.0f) {
            for (i = 0; i < 6; i++) {
                HudRankSlot *slot;
                float x;
                float y;
                float sy;
                float sx;
                float off;
                if (this->e[i].count == 0) {
                    continue;
                }
                slot = RankSlot_GetByIndex(i);
                off = lbl_806D7CE8;
                if (i < this->highlight) {
                    off = -25.0f;
                }
                if (i > this->highlight) {
                    off = 25.0f;
                }
                switch (this->e[i].count) {
                case 1:
                    if (i == 0) {
                        this->e[i].count++;
                        this->e[i].t = lbl_806D7CE8;
                    } else if (this->e[i - 1].count == 2) {
                        if (-18.0f * this->e[i - 1].t + 718.0f < 510.0f) {
                            this->e[i].count++;
                            this->e[i].t = lbl_806D7CE8;
                        }
                    } else if (this->e[i - 1].count > 2) {
                        this->e[i].count++;
                        this->e[i].t = lbl_806D7CE8;
                    }
                    x = 718.0f;
                    y = 350.0f;
                    break;
                case 2:
                    this->e[i].t += 1.0f;
                    x = -18.0f * this->e[i].t + 718.0f;
                    y = 350.0f + LUT_Sin12Bit(45.0f * this->e[i].t);
                    sy = lbl_806D7CE8;
                    sx = -1.570796f;
                    if (x < off + RaceHud_80147470_rodata_80362858[i]) {
                        x = off + RaceHud_80147470_rodata_80362858[i];
                        this->e[i].count++;
                        this->e[i].t = lbl_806D7CE8;
                    }
                    break;
                case 3: {
                    float s;
                    this->e[i].t += 1.0f;
                    x = off + RaceHud_80147470_rodata_80362858[i];
                    y = 350.0f;
                    sy = 0.1f * (0.17453292f * this->e[i].t);
                    sx = 1.4311696f * (this->e[i].t / 10.0f) + -1.570796f;
                    if (this->e[i].t <= 8.0f) {
                        s = 1.5f * LUT_Sin12Bit(11.25f * this->e[i].t);
                    } else {
                        s = 0.5f * fn_80186960(45.0f * (this->e[i].t - 8.0f)) + 1.0f;
                    }
                    fn_801697C0(this->layer + 1, i + 0x96B, 0, -20.0f + x, 380.0f, s, s);
                    if (this->e[i].t >= 10.0f) {
                        this->e[i].count++;
                        this->e[i].t = lbl_806D7CE8;
                        if (i == 0) {
                            fn_8013CA70(this->e[i].obj);
                        } else {
                            fn_8013CA04(this->e[i].obj);
                        }
                    }
                    break;
                }
                case 4: {
                    float nx;
                    this->e[i].t += 1.0f;
                    y = 350.0f;
                    x = off + RaceHud_80147470_rodata_80362858[i];
                    sy = 0.17453292f;
                    sx = -0.13962634f;
                    if (slot->icon >= 0) {
                        float ix = 10.0f + x;
                        fn_801697C0(this->layer + 1, slot->icon + 0x2B00, 0, ix, 370.0f, 0.75f * lbl_806D6DE4, 0.75f * lbl_806D6DE8);
                        fn_801697C0(this->layer + 1, fn_80231BD4(slot->chr, slot->kart, 0), 0, ix, 370.0f, 0.75f, 0.75f);
                    }
                    fn_801680A0(this->layer + 1, slot->name, -30.0f + x, 408.0f);
                    nx = -20.0f + x;
                    fn_801698B4(this->layer + 1, i + 0x96B, 0, nx, 380.0f);
                    if (slot->active) {
                        fn_80169468(this->layer + 1, i + 0x96B, 2, nx, 380.0f, 1.0f, 1.0f, 1.0f, 0.8f * LUT_Sin12Bit(lbl_806D7D4C * this->e[i].t));
                    }
                    if (this->e[i].t >= lbl_806D7D50) {
                        this->e[i].t = lbl_806D7CE8;
                    }
                    break;
                }
                }
                fn_8013C7B0(this->e[i].obj, x, y);
                fn_8013C5FC(this->e[i].obj, sx);
                fn_8013C674(this->e[i].obj, sy);
                fn_8013C91C(this->e[i].obj);
            }
        }
    }
    this->f24->v14();
    this->f24->v18();
    if (this->f1C != 0 && this->f1C->Idle()) {
        this->f1C->Start();
    }
    this->t += 1.0f;
}
#pragma use_lmw_stmw reset

clCSResultGP::~clCSResultGP() {
    int i;
    if (f1C != 0) f1C->vC();
    delete f24;
    for (i = 0; i < 6; i++) {
        if (e[i].obj != 0) delete e[i].obj;
    }
}

clCSResultGP::clCSResultGP(int ly, int id) : clCTaskInterface(id) {
    int i;
    layer = ly;
    t = lbl_806D7CE8;
    f1C = (RecordCounter *)new CountText(ly, 0);
    f24 = (VObj14 *)new CountGauge;
    ((CountGauge *)f24)->SetKind(ly);
    ((CountGauge *)f24)->Start();
    f28 = 0;
    for (i = 0; i < 6; i++) {
        e[i].count = 0;
        e[i].t = lbl_806D7CE8;
        e[i].obj = 0;
    }
    highlight = 6;
    on = 0;
}

extern "C" void fn_80149CD8(void) {
    if (g_gameMode == 2) {
        int i;
        for (i = 0; i < 8; i++) {
            KartVariant *k = GetKartSlotKartVariant(i);
            if (k != 0) {
                int kind = k->kind;
                int sub = k->sub;
                if (kind >= 0 && kind <= 3) {
                    PreloadResource(fn_80231BD4(kind, sub, 0));
                }
            }
        }
    }
    fn_8014196C();
    fn_80143DB0();
}

void clCSResultGP::Delete() {
    delete this;
}

