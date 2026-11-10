/*
 * 0x801DEF94..0x801E4524: AI steering manager and its scripted steering
 * actions (spin, jump, wobble...), each a small class with a 4x4 matrix
 * pair and a frame timer, plus a ring buffer used by the steering queue.
 */

struct SteeringRing;

extern "C" double sin(double);
extern "C" double cos(double);

struct Mtx44f {
    float m[4][4];

    void Identity() {
        int i, j;
        for (i = 0; i < 4; i++) {
            for (j = 0; j < 4; j++) {
                m[i][j] = 0.0f;
            }
        }
        m[0][0] = m[1][1] = m[2][2] = m[3][3] = 1.0f;
    }

    void SetTrans(float x, float y, float z) {
        m[3][0] = x;
        m[3][1] = y;
        m[3][2] = z;
    }

    void Copy(const Mtx44f &o) {
        int i, j;
        for (i = 0; i < 4; i++) {
            for (j = 0; j < 4; j++) {
                m[i][j] = o.m[i][j];
            }
        }
    }

    void RotX(float a) {
        float c;
        float s;
        Identity();
        c = cos(a);
        s = sin(a);
        m[2][2] = c;
        m[2][1] = -s;
        m[1][2] = s;
        m[1][1] = c;
    }

    void RotY(float a) {
        float c;
        float s;
        Identity();
        c = cos(a);
        s = sin(a);
        m[0][0] = c;
        m[0][2] = -s;
        m[2][0] = s;
        m[2][2] = c;
    }

    void Mul(const Mtx44f &b) {
        float r[16];
        float *t = r;
        int j;
        int n;
        int i;
        n = 0;
        for (i = 0; i < 4; i++) {
            for (j = 0; j < 4; j++) {
                float s = (&m[0][0])[n + 0] * (&b.m[0][0])[j];
                s += (&m[0][0])[n + 1] * (&b.m[0][0])[4 + j];
                s += (&m[0][0])[n + 2] * (&b.m[0][0])[8 + j];
                s += (&m[0][0])[n + 3] * (&b.m[0][0])[12 + j];
                t[n + j] = s;
            }
            n += 4;
        }
        for (i = 0; i < 16; i++) {
            (&m[0][0])[i] = t[i];
        }
    }
};

class SteerAction {
public:
    virtual ~SteerAction();
    virtual int Start(int item);
    virtual int IsBlocking();
    virtual int IsDone();
    virtual void Update();

    Mtx44f rot;
    Mtx44f trans;
    int arg;
    int timer;
    float scale;
    int phase;
};

#define SET_VT(obj, tbl) (*(void ***)(obj) = (tbl))

typedef struct ItemBus {
    char pad0[0x28];
    float speedScale;
} ItemBus;

typedef struct KartRef {
    char pad0[0x304];
    ItemBus *bus;
} KartRef;

typedef struct SteeringMgr {
    KartRef *kart;
    void *effect;
    int pad08;
    int state;
    unsigned char hold;
    char pad11[0x1c - 0x11];
    float push[3];
    int savedItem;
    int pad2C;
    int item;
    int timer;
    float scale;
    Mtx44f rot;
    Mtx44f trans;
    SteerAction *cur;
    SteerAction *actions[11];
    SteerAction *owned[11];
} SteeringMgr;

#define VFUNC(obj, off, type) ((type)((*(void ***)(obj))[(off) / 4]))

extern "C" {

extern float lbl_806D18E0;
extern float lbl_806D18DC;
extern float lbl_806D18D4;
extern float lbl_806D18D0;
extern float lbl_806D18CC;
extern float lbl_806D18C8;
extern float lbl_803BD0F0[];
extern const float lbl_806DA30C;

extern void *SteerBounce_vtable_804E4834[];
extern void *SteerJump_vtable_804E4884[];
extern void *SteerTurn_vtable_804E48AC[];
extern void *SteerHold_vtable_804E48D4[];
extern void *SteerSquash_vtable_804E48FC[];
extern void *SteerSpinOut_vtable_804E4924[];
extern void *SteerHop_vtable_804E494C[];
extern void *SteerFlip_vtable_804E4974[];
extern void *SteerRollA_vtable_804E499C[];
extern void *SteerRollB_vtable_804E49C4[];
extern void *SteerNone_vtable_804E49EC[];
extern void *SteerBase_vtable_804E4A08[];

typedef struct Vec3f {
    float x, y, z;
} Vec3f;

void Vec3_Copy(Vec3f *dst, const Vec3f *src);
void Vec3_Normalize_SafeXZY(Vec3f *dst, const Vec3f *src);
void Vec3_Scale(Vec3f *dst, const Vec3f *src, float s);
int fn_801DB818(void *tbl, int item);
int fn_801DB890(void *tbl, int item);

void ItemEffectBus_ApplyItemEventClear(ItemBus *bus, int item);
void ItemEffectBus_ApplyItemEventSet(ItemBus *bus, int item, int arg);
void ItemEffectBus_ClearMask(ItemBus *bus, unsigned long long mask);
void ItemEffectBus_OrMask(ItemBus *bus, unsigned long long mask);
void TornadoEffect_ApplyItemVisual_Primary(void *effect, int item);
void TornadoEffect_ApplyItemVisual_Secondary(void *effect, int item, int on);
void *fn_801DB8F0(void);
int fn_801DB8A4(void *tbl, int item);
void MemoryManager_TimedFree(void *p);
void fn_801E411C(SteeringRing *self, unsigned long n);
void fn_801E4524(void *self, int a, int b);
void fn_801E4504(void *self, int n);

static inline float Mul2(float a, float b) {
    return a * b;
}

void fn_801DEF94(SteeringMgr *self) {
    ItemBus *bus = self->kart->bus;
    ItemEffectBus_ApplyItemEventClear(bus, self->item);
    TornadoEffect_ApplyItemVisual_Primary(self->effect, self->item);
    self->item = 0;
    self->timer = 0;
    self->scale = 1.0f;
    ItemEffectBus_ClearMask(bus, 0x20000000000ULL);
}

void fn_801DF008(SteeringMgr *self, unsigned char hold) {
    self->hold = hold;
}

void fn_801DF010(SteeringMgr *self, int item, char *other) {
    ItemBus *bus;
    void *tbl;
    int st;
    int t;
    if (self->state != 0) {
        return;
    }
    if (self->item != 0) {
        fn_801DEF94(self);
    }
    self->item = item;
    if (item <= 0 || item >= 0x115) {
        self->item = 0;
        return;
    }
    bus = self->kart->bus;
    ItemEffectBus_ApplyItemEventSet(bus, self->item, 0);
    TornadoEffect_ApplyItemVisual_Secondary(self->effect, self->item, 1);
    if (item == 0x6b || item == 0x102) {
        ItemEffectBus_OrMask(bus, 0x20000000000ULL);
    }
    if (self->hold) {
        self->state = 7;
        self->savedItem = self->item;
        self->cur = self->owned[7];
        self->cur->Start(0);
        return;
    }
    tbl = fn_801DB8F0();
    if (fn_801DB818(tbl, self->item) && other) {
        Vec3f v;
        Vec3_Copy(&v, (Vec3f *)(other + 0xb8));
        Vec3f tmp = v;
        Vec3_Normalize_SafeXZY(&v, &tmp);
        Vec3_Scale(&v, &v, 6.0f);
        self->push[0] = -v.x;
        self->push[1] = -v.y;
        self->push[2] = -v.z;
    }
    st = fn_801DB890(tbl, self->item);
    self->state = st;
    self->cur = self->actions[st];
    t = self->cur->Start(self->item);
    if (st == 8) {
        bus->speedScale = lbl_806D18E0 / 60.0f;
    }
    self->timer = fn_801DB8A4(tbl, self->item);
    if (self->item != 0x6b && self->item != 0x102) {
        self->timer += t;
    }
}

static inline void ForceAction(SteeringMgr *self, int state) {
    ItemBus *bus;
    int t;
    if (self->item == 0) {
            bus = self->kart->bus;
            fn_801DB8F0();
            self->state = state;
            self->cur = self->actions[state];
            t = self->cur->Start(self->item);
            if (state == 8) {
                bus->speedScale = lbl_806D18E0 / 60.0f;
            }
            self->item = 2;
            self->timer = t;
    }
}

void fn_801DF24C(SteeringMgr *self, int state) {
    if (state <= 0 || state >= 11 || state == 7) {
        return;
    }
    ForceAction(self, state);
}

float *fn_801DF308(SteeringMgr *self) {
    return self->push;
}

float fn_801DF310(SteeringMgr *self) {
    return self->scale;
}

int fn_801DF318(const SteeringMgr *self) {
    SteerAction *a = self->cur;
    if (a) {
        return a->IsDone();
    }
    return 0;
}

int fn_801DF358(const SteeringMgr *self) {
    if (self->cur) {
        return self->cur->IsBlocking();
    }
    return 0;
}

void fn_801DF3B0(SteeringMgr *self) {
    SteerAction *a;
    self->rot.Identity();
    self->trans.Identity();
    if (self->state == 7 && !self->hold) {
        self->state = 6;
        self->cur = self->owned[6];
        self->cur->Start(0);
        self->timer = fn_801DB8A4(fn_801DB8F0(), self->savedItem);
        self->timer += 30;
        self->savedItem = 0;
    }
    a = self->cur;
    if (a) {
        int active = 0;
        a->rot.Identity();
        a->trans.Identity();
        if (a->timer > 0) {
            a->Update();
            a->timer--;
            active = 1;
        }
        self->rot.Copy(self->cur->rot);
        self->trans.Copy(self->cur->trans);
        if (!(unsigned char)active) {
            self->kart->bus->speedScale = 0.0f;
            self->cur = 0;
            self->state = 0;
        }
    }
    if (self->timer > 0) {
        self->timer--;
        if (self->timer <= 0) {
            fn_801DEF94(self);
        }
    }
    self->push[0] = 0.0f;
    self->push[1] = 0.0f;
    self->push[2] = 0.0f;
}

int fn_801DF398(SteeringMgr *self) {
    return self->state;
}

Mtx44f *fn_801DF3A0(SteeringMgr *self) {
    return &self->trans;
}

Mtx44f *fn_801DF3A8(SteeringMgr *self) {
    return &self->rot;
}

/* --- steering actions --- */

void fn_801E08A0(SteerAction *self) {
    float s = sin(Mul2((float)(20 - self->timer) / 20.0f, 3.1415927f));
    /* fakematch: the copy into y gives the product its own FPR.
     * Natural code: s *= 5.0f; self->trans.SetTrans(0.0f, s, 0.0f); */
    float y = s;
    y *= 5.0f;
    self->trans.SetTrans(0.0f, y, 0.0f);
}

int fn_801E091C(SteerAction *self) { return 0; }
int fn_801E0924(SteerAction *self) { return 0; }

int fn_801E092C(SteerAction *self) {
    self->timer = 20;
    return 20;
}

SteerAction *fn_801E093C(SteerAction *self, short flag) {
    if (self) {
        SET_VT(self, SteerBounce_vtable_804E4834);
        if (self) {
            SET_VT(self, SteerBase_vtable_804E4A08);
        }
        if (flag > 0) {
            MemoryManager_TimedFree(self);
        }
    }
    return self;
}

void fn_801E0998(SteerAction *self) {
    int e = 120 - self->timer;
    if (self->phase == 0) {
        float sn;
        float f;
        float spin;
        float r;
        float cs;
        float a;
        f = (float)e / 90.0f;
        a = 3.1415927f;
        a *= f;
        spin = lbl_806DA30C;
        spin *= f;
        r = 20.0f * (float)sin(a);
        sn = sin(spin);
        cs = cos(spin);
        self->trans.m[3][0] = r * sn;
        self->trans.m[3][1] = 50.0f * f;
        self->trans.m[3][2] = r * cs;
        if (e >= 90) {
            self->phase = 1;
            self->trans.m[3][0] = 0.0f;
            self->trans.m[3][1] = 50.0f;
            self->trans.m[3][2] = 0.0f;
        }
    } else if (self->phase == 1) {
        float f = (float)(e - 90) / 15.0f;
        float a = 1.5707964f;
        a *= f;
        float c = cos(a);
        self->trans.m[3][0] = 0.0f;
        self->trans.m[3][1] = 50.0f * c;
        self->trans.m[3][2] = 0.0f;
        if (e >= 105) {
            self->phase = 2;
            self->trans.m[3][0] = 0.0f;
            self->trans.m[3][1] = 0.0f;
            self->trans.m[3][2] = 0.0f;
        }
    } else if (self->phase == 2) {
        float f = (float)(e - 105) / 15.0f;
        float v = 0.5f;
        float base = v;
        v *= f;
        v += base;
        self->rot.m[1][1] = v;
        if (e >= 120) {
            self->rot.m[1][1] = 1.0f;
            self->phase = -1;
        }
    }
}

int fn_801E0B8C(SteerAction *self) { return 0; }
int fn_801E0B94(SteerAction *self) { return 1; }

int fn_801E0B9C(SteerAction *self) {
    self->timer = 120;
    self->phase = 0;
    return 120;
}

SteerAction *fn_801E0BB4(SteerAction *self, short flag) {
    if (self) {
        SET_VT(self, SteerJump_vtable_804E4884);
        if (self) {
            SET_VT(self, SteerBase_vtable_804E4A08);
        }
        if (flag > 0) {
            MemoryManager_TimedFree(self);
        }
    }
    return self;
}

int fn_801E0FBC(SteerAction *self) { return 1; }
int fn_801E0FC4(SteerAction *self) { return 0; }

int fn_801E0FCC(SteerAction *self) {
    self->timer = 60;
    return 60;
}

void fn_801E0C10(SteerAction *self) {
    Mtx44f m;
    m.RotY((1.0f / 60.0f) * (lbl_806D18E0 * (float)(60 - self->timer)));
    m.Mul(self->rot);
    self->rot = m;
}

SteerAction *fn_801E0FDC(SteerAction *self, short flag) {
    if (self) {
        SET_VT(self, SteerTurn_vtable_804E48AC);
        if (self) {
            SET_VT(self, SteerBase_vtable_804E4A08);
        }
        if (flag > 0) {
            MemoryManager_TimedFree(self);
        }
    }
    return self;
}

void fn_801E1038(SteerAction *self) {}
int fn_801E103C(SteerAction *self) { return 0; }
int fn_801E1044(SteerAction *self) { return 1; }

int fn_801E104C(SteerAction *self) {
    self->timer = 60000;
    return 60000;
}

SteerAction *fn_801E1060(SteerAction *self, short flag) {
    if (self) {
        SET_VT(self, SteerHold_vtable_804E48D4);
        if (self) {
            SET_VT(self, SteerBase_vtable_804E4A08);
        }
        if (flag > 0) {
            MemoryManager_TimedFree(self);
        }
    }
    return self;
}

static inline float Lerp(float a, float b, float t) {
    t *= b - a;
    t += a;
    return t;
}

void fn_801E10BC(SteerAction *self) {
    int e = 30 - self->timer;
    if (e < 30) {
        self->rot.m[1][1] = Lerp(0.2f, 1.0f, (1.0f / 30.0f) * (float)(30 - e));
        { float v = Lerp(1.0f, 1.2f, Mul2((float)e, 1.0f / 30.0f)); self->rot.m[0][0] = v; self->rot.m[2][2] = v; }
    } else if (e < 50) {
        self->rot.m[1][1] = Lerp(0.2f, 1.2f, 0.05f * (float)(e - 30));
        { float v = Lerp(0.8f, 1.2f, 0.05f * (float)(50 - e)); self->rot.m[0][0] = v; self->rot.m[2][2] = v; }
    } else if (e < 30) {
        self->rot.m[1][1] = Lerp(1.0f, 1.2f, -0.05f * (float)(30 - e));
        { float v = Lerp(0.8f, 1.0f, -0.05f * (float)(e - 50)); self->rot.m[0][0] = v; self->rot.m[2][2] = v; }
    }
}

int fn_801E123C(SteerAction *self) { return 0; }
int fn_801E1244(SteerAction *self) { return 1; }

int fn_801E124C(SteerAction *self) {
    self->timer = 30;
    return 30;
}

SteerAction *fn_801E125C(SteerAction *self, short flag) {
    if (self) {
        SET_VT(self, SteerSquash_vtable_804E48FC);
        if (self) {
            SET_VT(self, SteerBase_vtable_804E4A08);
        }
        if (flag > 0) {
            MemoryManager_TimedFree(self);
        }
    }
    return self;
}

void fn_801E12B8(SteerAction *self) {
    float k = lbl_806D18DC;
    int d = fn_801DB8A4(fn_801DB8F0(), self->arg);
    int e = d - self->timer;
    float scale = 1.0f;
    float h;
    float ang = k * ((1.0f / (float)d) * (float)e);
    Mtx44f m;
    if (e < 0) {
        h = 0.0f;
        scale -= h;
    } else if (e < d - 10) {
        h = 0.6f * (float)e;
        if (h > 16.0f) {
            h = 16.0f;
        }
        scale -= 0.8f * (h / 16.0f);
    } else {
        h = 16.0f * (float)(d - e) / 10.0f;
        ang = 0.0f;
        scale -= 0.8f * (h / 16.0f);
    }
    m.RotY(ang);
    m.Mul(self->rot);
    self->rot = m;
    self->rot.m[0][0] *= scale;
    self->rot.m[0][1] *= scale;
    self->rot.m[0][2] *= scale;
    self->rot.m[1][0] *= scale;
    self->rot.m[1][1] *= scale;
    self->rot.m[1][2] *= scale;
    self->rot.m[2][0] *= scale;
    self->rot.m[2][1] *= scale;
    self->rot.m[2][2] *= scale;
    self->trans.m[3][0] = 0.0f;
    self->trans.m[3][1] = h;
    self->trans.m[3][2] = 0.0f;
}

int fn_801E17B8(SteerAction *self) { return 0; }
int fn_801E17C0(SteerAction *self) { return 1; }

int fn_801E17C8(SteerAction *self, int item) {
    self->arg = item;
    self->timer = fn_801DB8A4(fn_801DB8F0(), item);
    return self->timer;
}

SteerAction *fn_801E1814(SteerAction *self, short flag) {
    if (self) {
        SET_VT(self, SteerSpinOut_vtable_804E4924);
        if (self) {
            SET_VT(self, SteerBase_vtable_804E4A08);
        }
        if (flag > 0) {
            MemoryManager_TimedFree(self);
        }
    }
    return self;
}

void fn_801E1870(SteerAction *self) {
    Mtx44f m;
    float angle;
    float f;
    angle = lbl_806D18D4;
    f = (1.0f / 60.0f) * (float)(60 - self->timer);
    m.RotX(angle * f);
    m.Mul(self->rot);
    self->rot = m;
    {
        float y = Mul2(sin(Mul2(f, 3.1415927f)), 70.0f);
        self->trans.m[3][0] = 0.0f;
        self->trans.m[3][1] = y;
        self->trans.m[3][2] = 0.0f;
    }
}

int fn_801E1C54(SteerAction *self) { return 0; }
int fn_801E1C5C(SteerAction *self) { return 1; }

int fn_801E1C64(SteerAction *self) {
    self->timer = 60;
    return 60;
}

SteerAction *fn_801E1C74(SteerAction *self, short flag) {
    if (self) {
        SET_VT(self, SteerHop_vtable_804E494C);
        if (self) {
            SET_VT(self, SteerBase_vtable_804E4A08);
        }
        if (flag > 0) {
            MemoryManager_TimedFree(self);
        }
    }
    return self;
}

void fn_801E1CD0(SteerAction *self) {
    Mtx44f m;
    float ang = lbl_806D18D0 * ((float)(90 - self->timer) / 90.0f);
    m.RotX(ang);
    m.Mul(self->rot);
    self->rot = m;
    {
        float n = ang;
        float h;
        while (6.2831855f <= n) {
            n -= 6.2831855f;
        }
        while (n < 0.0f) {
            n += 6.2831855f;
        }
        h = lbl_803BD0F0[1];
        if (ang < 1.5707964f || 4.712389f < ang) {
            float sv = sin(ang);
            self->trans.m[3][0] = 0.0f;
            self->trans.m[3][1] = __fabs(h * sv);
            self->trans.m[3][2] = 0.0f;
        } else {
            self->trans.m[3][0] = 0.0f;
            self->trans.m[3][1] = h;
            self->trans.m[3][2] = 0.0f;
        }
    }
}

int fn_801E210C(SteerAction *self) { return 0; }
int fn_801E2114(SteerAction *self) { return 0; }

int fn_801E211C(SteerAction *self) {
    self->timer = 90;
    return 90;
}

SteerAction *fn_801E212C(SteerAction *self, short flag) {
    if (self) {
        SET_VT(self, SteerFlip_vtable_804E4974);
        if (self) {
            SET_VT(self, SteerBase_vtable_804E4A08);
        }
        if (flag > 0) {
            MemoryManager_TimedFree(self);
        }
    }
    return self;
}

void fn_801E2188(SteerAction *self) {
    Mtx44f m;
    float ang = lbl_806D18CC * ((float)(60 - self->timer) / 60.0f);
    m.RotX(ang);
    m.Mul(self->rot);
    self->rot = m;
    {
        float n = ang;
        float h;
        while (6.2831855f <= n) {
            n -= 6.2831855f;
        }
        while (n < 0.0f) {
            n += 6.2831855f;
        }
        h = lbl_803BD0F0[1];
        if (ang < 1.5707964f || 4.712389f < ang) {
            float sv = sin(ang);
            self->trans.m[3][0] = 0.0f;
            self->trans.m[3][1] = __fabs(h * sv);
            self->trans.m[3][2] = 0.0f;
        } else {
            self->trans.m[3][0] = 0.0f;
            self->trans.m[3][1] = h;
            self->trans.m[3][2] = 0.0f;
        }
    }
}

int fn_801E25C4(SteerAction *self) { return 0; }
int fn_801E25CC(SteerAction *self) { return 0; }

int fn_801E25D4(SteerAction *self) {
    self->timer = 60;
    return 60;
}

SteerAction *fn_801E25E4(SteerAction *self, short flag) {
    if (self) {
        SET_VT(self, SteerRollA_vtable_804E499C);
        if (self) {
            SET_VT(self, SteerBase_vtable_804E4A08);
        }
        if (flag > 0) {
            MemoryManager_TimedFree(self);
        }
    }
    return self;
}

void fn_801E2640(SteerAction *self) {
    Mtx44f m;
    float x = (float)(30 - self->timer);
    float f;
    float ang;
    if (x < 15.0f) {
        f = x / 15.0f;
    } else {
        f = (15.0f - (x - 15.0f)) / 15.0f;
    }
    ang = lbl_806D18C8 * f;
    m.RotX(ang);
    m.Mul(self->rot);
    self->rot = m;
    {
        float n = ang;
        float h;
        while (6.2831855f <= n) {
            n -= 6.2831855f;
        }
        while (n < 0.0f) {
            n += 6.2831855f;
        }
        h = lbl_803BD0F0[1];
        if (ang < 1.5707964f || 4.712389f < ang) {
            float sv = sin(ang);
            self->trans.m[3][0] = 0.0f;
            self->trans.m[3][1] = __fabs(h * sv);
            self->trans.m[3][2] = 0.0f;
        } else {
            self->trans.m[3][0] = 0.0f;
            self->trans.m[3][1] = h;
            self->trans.m[3][2] = 0.0f;
        }
    }
}

int fn_801E2A94(SteerAction *self) { return 0; }
int fn_801E2A9C(SteerAction *self) { return 0; }

int fn_801E2AA4(SteerAction *self) {
    self->timer = 30;
    return 30;
}

SteerAction *fn_801E2AB4(SteerAction *self, short flag) {
    if (self) {
        SET_VT(self, SteerRollB_vtable_804E49C4);
        if (self) {
            SET_VT(self, SteerBase_vtable_804E4A08);
        }
        if (flag > 0) {
            MemoryManager_TimedFree(self);
        }
    }
    return self;
}

void fn_801E2B10(SteerAction *self) {}
int fn_801E2B14(SteerAction *self) { return 0; }
int fn_801E2B1C(SteerAction *self) { return 0; }
int fn_801E2B24(SteerAction *self) { return 0; }

SteerAction *fn_801E2B2C(SteerAction *self, short flag) {
    if (self) {
        SET_VT(self, SteerNone_vtable_804E49EC);
        if (self) {
            SET_VT(self, SteerBase_vtable_804E4A08);
        }
        if (flag > 0) {
            MemoryManager_TimedFree(self);
        }
    }
    return self;
}

SteerAction *fn_801E2B88(SteerAction *self, short flag) {
    if (self) {
        SET_VT(self, SteerBase_vtable_804E4A08);
        if (flag > 0) {
            MemoryManager_TimedFree(self);
        }
    }
    return self;
}

/* --- ring buffer --- */

typedef struct Ring {
    unsigned int cap;
    unsigned int count;
    unsigned int head;
    int *data;
} Ring;

int *fn_801E40C0(Ring *r, unsigned int i) {
    unsigned int idx = i + r->head;
    if (idx >= r->cap) {
        idx -= r->cap;
    }
    return &r->data[idx];
}

void fn_801E40E8(Ring *r);
static inline void RingPopFront(Ring *r) {
    r->count--;
    r->head++;
    if (r->head >= r->cap) {
        r->head -= r->cap;
    }
}

void fn_801E3A4C(char *self);

} /* extern "C" */

/* --- C++ side: the manager's constructor/destructor and its owning pointers --- */

extern "C" void fn_801DB8BC(void);

template <class T>
class SteerPtr {
public:
    T *p;

    SteerPtr() throw() : p(0) {}
    ~SteerPtr() throw() { delete p; }
    T *get() const throw() { return p; }
    void reset(T *q) throw() {
        if (p != q) {
            delete p;
            p = q;
        }
    }
};

struct Mtx44c {
    float m[4][4];

    void Init() {
        int i;
        for (i = 0; i < 16; i++) {
            (&m[0][0])[i] = 0.0f;
        }
        m[0][0] = m[1][1] = m[2][2] = m[3][3] = 1.0f;
    }
};

class SteerBase {
public:
    SteerBase() : timer(0), scale(0.0f) {
        rot.Init();
        trans.Init();
    }
    virtual ~SteerBase();
    virtual int Start(int item) = 0;
    virtual int IsBlocking() = 0;
    virtual int IsDone() = 0;
    virtual void Update() = 0;

    Mtx44c rot;
    Mtx44c trans;
    int arg;
    int timer;
    float scale;
};

#define STEER_CLASS(name)                     \
    class name : public SteerBase {           \
    public:                                   \
        name() {}                             \
        virtual ~name();                      \
        virtual int Start(int item);          \
        virtual int IsBlocking();             \
        virtual int IsDone();                 \
        virtual void Update();                \
    };

STEER_CLASS(SteerNone)
STEER_CLASS(SteerRollB)
STEER_CLASS(SteerRollA)
STEER_CLASS(SteerFlip)
STEER_CLASS(SteerHop)
STEER_CLASS(SteerSpinOut)
STEER_CLASS(SteerSquash)
STEER_CLASS(SteerHold)
STEER_CLASS(SteerTurn)
class SteerJump : public SteerBase {
public:
    SteerJump() : phase(-1) {}
    virtual ~SteerJump();
    virtual int Start(int item);
    virtual int IsBlocking();
    virtual int IsDone();
    virtual void Update();

    int phase;
};
STEER_CLASS(SteerBounce)

class SteerMgr {
public:
    SteerMgr(KartRef *kart, void *effect);
    ~SteerMgr();

    KartRef *kart;
    void *effect;
    int pad08;
    int state;
    unsigned char hold;
    int pad14;
    int pad18;
    float push[3];
    int savedItem;
    int pad2C;
    int item;
    int timer;
    float scale;
    Mtx44c rot;
    Mtx44c trans;
    SteerBase *cur;
    SteerBase *actions[11];
    SteerPtr<SteerNone> a0;
    SteerPtr<SteerRollB> a1;
    SteerPtr<SteerRollA> a2;
    SteerPtr<SteerFlip> a3;
    SteerPtr<SteerHop> a4;
    SteerPtr<SteerSpinOut> a5;
    SteerPtr<SteerSquash> a6;
    SteerPtr<SteerHold> a7;
    SteerPtr<SteerTurn> a8;
    SteerPtr<SteerJump> a9;
    SteerPtr<SteerBounce> a10;
};

SteerMgr::SteerMgr(KartRef *kart, void *effect) {
    int i;
    fn_801DB8F0();
    this->kart = kart;
    this->effect = effect;
    state = 0;
    hold = 0;
    pad18 = 0;
    scale = 1.0f;
    cur = 0;
    pad08 = 0;
    item = 0;
    timer = 0;
    savedItem = 0;
    pad2C = 0;
    rot.Init();
    trans.Init();
    a0.reset(new SteerNone);
    a1.reset(new SteerRollB);
    a2.reset(new SteerRollA);
    a3.reset(new SteerFlip);
    a4.reset(new SteerHop);
    a5.reset(new SteerSpinOut);
    a6.reset(new SteerSquash);
    a7.reset(new SteerHold);
    a8.reset(new SteerTurn);
    a9.reset(new SteerJump);
    a10.reset(new SteerBounce);
    for (i = 0; i < 11; i++) {
        actions[i] = 0;
    }
    actions[0] = a0.get();
    actions[1] = a1.get();
    actions[2] = a2.get();
    actions[3] = a3.get();
    actions[4] = a4.get();
    actions[5] = a5.get();
    actions[6] = a6.get();
    actions[7] = a7.get();
    actions[8] = a8.get();
    actions[9] = a9.get();
    actions[10] = a10.get();
    push[0] = 0.0f;
    push[1] = 0.0f;
    push[2] = 0.0f;
}

SteerMgr::~SteerMgr() {
    fn_801DB8BC();
}

/* The queue stores eight-byte values in separately allocated blocks. Its
 * block map uses the same circular storage as the neighbouring ring TUs. */
#define STEERING_RING_INSERT_OPERATORS
#include "game/SteeringQueueMatchPrivate.h"

extern "C" void *dtor_801E2BD0(SteeringQueue *s, short flag) {
    if (s) {
        fn_801E2C40(s);
        if (&s->blocks) {
            if (&s->blocks) {
                if (s->blocks.data) MemoryManager_TimedFree(s->blocks.data);
            }
        }
        if (flag > 0) MemoryManager_TimedFree(s);
    }
    return s;
}

static inline SteeringRingIter RingEndB(SteeringRing *r) {
    unsigned long n;
    unsigned long i = r->head + (n = r->count);
    SteeringRingIter it(0, 0, 0);
    if (i < r->capacity) it = SteeringRingIter(r, n, r->data + i);
    else it = SteeringRingIter(r, n, r->data + (i - r->capacity));
    return it;
}

extern "C" void fn_801E2C40(SteeringQueue *s) {
    if (s->blocks.count) {
        fn_801E36A8(s, fn_801E35FC(s, s->first), fn_801E35FC(s, s->first + s->count));
        SteeringRingIter last = --RingEndB(&s->blocks);
        for (SteeringRingIter p = s->blocks.begin(); p.index != last.index; ++p) {
            MemoryManager_TimedFree((void *)*p);
        }
    }
}

extern "C" void fn_801E2DF0(SteeringQueue *s) {
    if (s->blocks.count) {
        fn_801E36A8(s, fn_801E35FC(s, s->first), fn_801E35FC(s, s->first + s->count));
        s->count = 0;
        QueueTrim(s);
    }
}

extern "C" void fn_801E2F28(SteeringQueue *s) {
    ++s->first;
    if (--s->count == 0) QueueTrim(s);
}

static inline void RingSwap(SteeringRing &a, SteeringRing &b) {
    if (&a != &b) {
        unsigned long t = a.capacity; a.capacity = b.capacity; b.capacity = t;
        t = a.count; a.count = b.count; b.count = t;
        t = a.head; a.head = b.head; b.head = t;
        int *p = a.data; a.data = b.data; b.data = p;
    }
}

static inline void QueueAssignDispatch(SteeringRing *s, SteeringRingIter first,
        SteeringRingIter last, QueueAssignTag tag) {
    fn_801E4544(s, QueueAssignIter(first), QueueAssignIter(last), tag);
}

static inline void QueueAssignRange(SteeringRing *s, SteeringRingIter first, SteeringRingIter last) {
    QueueAssignDispatch(s, first, last, QueueAssignTag());
}

extern "C" unsigned char fn_801E32C8(SteeringQueue *s, unsigned long oldFirst,
        SteeringRing *saved, unsigned long *added, unsigned long n) {
    unsigned char swapped = 0;
    unsigned long remaining = n - s->first;
    for (;;) {
        int block = (int)Alloc(s->blockSize * sizeof(SteeringQueueValue));
        try {
            if (!swapped && s->blocks.count == s->blocks.capacity) {
                RingSwap(s->blocks, *saved);
                swapped = 1;
                fn_801E4504(&s->blocks, saved->capacity * 2);
                QueueAssignRange(&s->blocks, saved->begin(), saved->end());
            }
            fn_801E5724(&s->blocks, block);
            ++*added;
            s->first += s->blockSize;
            if (remaining <= s->blockSize) {
                if (s->count) s->first -= n;
                else s->first = (s->blockSize * (s->blocks.count - 1) - n) / 2;
                break;
            }
            remaining -= s->blockSize;
        } catch (...) {
            MemoryManager_TimedFree((void *)block);
            for (unsigned long i = 0; i < *added; ++i) {
                MemoryManager_TimedFree((void *)s->blocks.data[s->blocks.head]);
                RingPopFront((Ring *)&s->blocks);
            }
            if (swapped) RingSwap(s->blocks, *saved);
            s->first = oldFirst;
            throw;
        }
    }
    return swapped;
}

extern "C" void fn_801E2FD4(SteeringQueue *s, const SteeringQueueValue &value) {
    if (s->count > 0x1ffffffeUL) throw std::length_error(lbl_803BD208);
    if (!s->blocks.count) {
        fn_801E411C(&s->blocks, 2);
        fn_801E435C(&s->blocks, 1, 0);
    }
    unsigned long added = 0;
    QueueBlockMap saved;
    if (s->first == 0) fn_801E32C8(s, s->first, &saved, &added, 1);
    else --s->first;
    SteeringQueueValue *out = QueueAt(s, s->first);
    new (out) SteeringQueueValue(value);
    ++s->count;
    while (s->first >= s->blockSize * 3 / 2) {
        MemoryManager_TimedFree((void *)s->blocks.data[s->blocks.head]);
        fn_801E40E8((Ring *)&s->blocks);
        s->first -= s->blockSize;
    }
}

extern "C" SteeringQueue *fn_801E3260(SteeringQueue *s, unsigned long n) {
    s->blockSize = lbl_806DA360;
    s->blocks.capacity = 0;
    s->blocks.count = 0;
    s->blocks.head = 0;
    s->blocks.data = 0;
    s->first = 0;
    s->count = 0;
    SteeringQueueValue value;
    value.first = lbl_806D1904;
    value.second = lbl_806D1908;
    fn_801E3848(s, n, value);
    return s;
}

static inline SteeringQueueIter QueueIterAt(const SteeringQueue *s, unsigned long i) {
    unsigned long size = s->blockSize;
    unsigned long blockIndex = 0;
    SteeringRing *map = (SteeringRing *)&s->blocks;
    int *block = s->blocks.data + s->blocks.head;
    SteeringQueueValue *base, *ptr;
    if (i < size) {
        base = s->blocks.count == 0 ? 0 : (SteeringQueueValue *)*block;
        ptr = base + i;
    } else {
        blockIndex = i / size;
        unsigned long j = map->head + blockIndex;
        if (j >= map->capacity) j -= map->capacity;
        block = map->data + j;
        base = (SteeringQueueValue *)*block;
        ptr = base + i % size;
    }
    return SteeringQueueIter(map, blockIndex, block, ptr, base + size, i);
}

extern "C" SteeringQueueIter fn_801E35FC(SteeringQueue *s, unsigned long i) {
    SteeringRing *map = (SteeringRing *)&s->blocks;
    unsigned long blockIndex = 0;
    SteeringQueueValue *ptr;
    int *block = s->blocks.data + s->blocks.head;
    unsigned long size = s->blockSize;
    SteeringQueueValue *base;
    if (i < size) {
        if (s->blocks.count == 0) base = 0; else base = (SteeringQueueValue *)*block;
        ptr = base + i;
    } else {
        blockIndex = i / size;
        unsigned long j = map->head + blockIndex;
        unsigned long capacity = map->capacity;
        if (j >= capacity) j -= capacity;
        block = map->data + j;
        base = (SteeringQueueValue *)*block;
        ptr = base + i % size;
    }
    return SteeringQueueIter(map, blockIndex, block, ptr, base + size, i);
}

static inline const unsigned long &QueueMinRef(const unsigned long &a, const unsigned long &b) {
    return a < b ? a : b;
}

#pragma push
#pragma opt_propagation off /* pragmasweep: 149 -> 102 lines; the dtor loops keep the ring loads hoisted */
extern "C" void fn_801E36A8(SteeringQueue *s, const SteeringQueueConstIter &first,
        const SteeringQueueConstIter &last) {
    if (first.ptr != last.ptr) {
        unsigned long blockIndex = first.index / s->blockSize;
        unsigned long offset = first.index % s->blockSize;
        unsigned long n = last.index - first.index;
        unsigned long end = offset + n;
        unsigned long take = QueueMinRef(end, s->blockSize);
        SteeringRingIter it = RingAdvance(s->blocks.begin(), blockIndex);
        SteeringQueueValue *p = (SteeringQueueValue *)*it + offset;
        SteeringQueueValue *stop = (SteeringQueueValue *)*it + take;
        for (; p < stop; ++p) p->~SteeringQueueValue();
        n -= take - offset;
        if (n) {
            ++it;
            while (n >= s->blockSize) {
                p = (SteeringQueueValue *)*it;
                stop = p + s->blockSize;
                for (; p < stop; ++p) p->~SteeringQueueValue();
                ++it;
                n -= s->blockSize;
            }
            if (n) {
                p = (SteeringQueueValue *)*it;
                stop = p + n;
                for (; p < stop; ++p) p->~SteeringQueueValue();
            }
        }
    }
}

#pragma pop

static inline void QueueUninitializedFillN(SteeringQueueValue *out,
        unsigned long n, const SteeringQueueValue &value) {
    SteeringQueueValue *current = out;
    try {
        for (; n--; ++current) new (current) SteeringQueueValue(value);
    } catch (...) {
        for (; out != current; ++out) out->~SteeringQueueValue();
        throw;
    }
}

extern "C" void fn_801E3848(SteeringQueue *s, unsigned long n,
        const SteeringQueueValue &value) {
    if (n > 0x1fffffffUL) throw std::length_error(lbl_803BD280);
    if (n) {
        fn_801E3A4C((char *)s);
        if (s->blockSize < n) s->blockSize = n;
        SteeringQueueValue *block = (SteeringQueueValue *)Alloc(s->blockSize * sizeof(SteeringQueueValue));
        try {
            s->blocks.data[s->blocks.head] = (int)block;
            int zero = 0;
            fn_801E5454(&s->blocks, zero);
            s->count = n;
            s->first = (s->blockSize - s->count) / 2;
            SteeringQueueValue *out = block + s->first;
            QueueUninitializedFillN(out, s->count, value);
        } catch (...) {
            MemoryManager_TimedFree(block);
            throw;
        }
    }
}

extern "C" void fn_801E3A4C(char *self) {
    fn_801E4504(self + 4, 2);
    fn_801E4524(self + 4, 1, 0);
}

inline SteeringRingIter &SteeringRingIter::operator+=(unsigned long n) {
    index += n;
    unsigned long i = ring->head + index;
    if (i >= ring->capacity) i -= ring->capacity;
    ptr = ring->data + i;
    return *this;
}

inline SteeringRingIter SteeringRingIter::operator+(unsigned long n) const {
    SteeringRingIter copy = *this;
    return copy += n;
}

static inline SteeringRingIter ResizeEnd(SteeringRing *s) {
    const SteeringRingIter &it = s->end();
    SteeringRing *ring = it.ring;
    unsigned long index = it.index;
    int * ptr;
    return SteeringRingIter(ring, index, (it.ptr));
}

static inline void QueueResizeGrow(SteeringRing *s, unsigned long n, const int &value) {
    fn_801E4AF4(s, ResizeEnd(s), n - s->count, value);
}

extern "C" void fn_801E435C(void *self, unsigned long n, int value) {
    SteeringRing *s = (SteeringRing *)self;
    if (n > s->count) QueueResizeGrow(s, n, value);
    else if (n < s->count) {
        const SteeringRingIter &first = s->begin() + n;
        fn_801E4824(s, first, ResizeEnd(s));
    }
}

extern "C" void fn_801E4504(void *self, int n) {
    fn_801E411C((SteeringRing *)self, n);
}

extern "C" void fn_801E411C(SteeringRing *s, unsigned long n) {
    if (n > fn_801E5A00(s)) throw std::length_error(lbl_803BD260);
    if (n > s->capacity) {
        int *data = (int *)Alloc(n * sizeof(int));
        if (s->data) {
            RingCopy(s->begin(), s->end(), data);
            if (s->data) MemoryManager_TimedFree(s->data);
        }
        s->capacity = n;
        s->data = data;
        s->head = 0;
    }
}

extern "C" {
void fn_801E40E8(Ring *r) {
    r->count--;
    r->head++;
    if (r->head >= r->cap) {
        r->head -= r->cap;
    }
}
}
