/*
 * 0x801DEF94..0x801E4524: AI steering manager and its scripted steering
 * actions (spin, jump, wobble...), each a small class with a 4x4 matrix
 * pair and a frame timer, plus a ring buffer used by the steering queue.
 */

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

extern void *lbl_804E4834[];
extern void *lbl_804E4884[];
extern void *lbl_804E48AC[];
extern void *lbl_804E48D4[];
extern void *lbl_804E48FC[];
extern void *lbl_804E4924[];
extern void *lbl_804E494C[];
extern void *lbl_804E4974[];
extern void *lbl_804E499C[];
extern void *lbl_804E49C4[];
extern void *lbl_804E49EC[];
extern void *lbl_804E4A08[];

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
void fn_801E411C(void *self, int n);
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
    if (state == 7) {
        return;
    }
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
    if (state > 0 && state < 11) {
        ForceAction(self, state);
    }
}

float *fn_801DF308(SteeringMgr *self) {
    return self->push;
}

float fn_801DF310(SteeringMgr *self) {
    return self->scale;
}

int fn_801DF318(SteeringMgr *self) {
    SteerAction *a = self->cur;
    if (a) {
        return a->IsDone();
    }
    return 0;
}

int fn_801DF358(SteeringMgr *self) {
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
    float y = Mul2(s, 5.0f);
    self->trans.m[3][0] = 0.0f;
    self->trans.m[3][1] = y;
    self->trans.m[3][2] = 0.0f;
}

int fn_801E091C(SteerAction *self) { return 0; }
int fn_801E0924(SteerAction *self) { return 0; }

int fn_801E092C(SteerAction *self) {
    self->timer = 20;
    return 20;
}

SteerAction *fn_801E093C(SteerAction *self, short flag) {
    if (self) {
        SET_VT(self, lbl_804E4834);
        if (self) {
            SET_VT(self, lbl_804E4A08);
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
        float f = (float)e / 90.0f;
        float a = 3.1415927f * f;
        float spin = 37.699112f * f;
        float r = 20.0f * (float)sin(a);
        float sn = sin(spin);
        float cs = cos(spin);
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
        float c = cos(1.5707964f * f);
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
        self->rot.m[1][1] = 0.5f * f + 0.5f;
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
        SET_VT(self, lbl_804E4884);
        if (self) {
            SET_VT(self, lbl_804E4A08);
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
        SET_VT(self, lbl_804E48AC);
        if (self) {
            SET_VT(self, lbl_804E4A08);
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
        SET_VT(self, lbl_804E48D4);
        if (self) {
            SET_VT(self, lbl_804E4A08);
        }
        if (flag > 0) {
            MemoryManager_TimedFree(self);
        }
    }
    return self;
}

static inline float Lerp(float a, float b, float t) {
    float d = t * (b - a);
    return d + a;
}

void fn_801E10BC(SteerAction *self) {
    int e = 30 - self->timer;
    if (e < 30) {
        self->rot.m[1][1] = Lerp(0.2f, 1.0f, (1.0f / 30.0f) * (float)(30 - e));
        { float v = Lerp(1.0f, 1.2f, (float)e * (1.0f / 30.0f)); self->rot.m[0][0] = v; self->rot.m[2][2] = v; }
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
        SET_VT(self, lbl_804E48FC);
        if (self) {
            SET_VT(self, lbl_804E4A08);
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
        SET_VT(self, lbl_804E4924);
        if (self) {
            SET_VT(self, lbl_804E4A08);
        }
        if (flag > 0) {
            MemoryManager_TimedFree(self);
        }
    }
    return self;
}

void fn_801E1870(SteerAction *self) {
    Mtx44f m;
    float f = (1.0f / 60.0f) * (float)(60 - self->timer);
    m.RotX(lbl_806D18D4 * f);
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
        SET_VT(self, lbl_804E494C);
        if (self) {
            SET_VT(self, lbl_804E4A08);
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
        SET_VT(self, lbl_804E4974);
        if (self) {
            SET_VT(self, lbl_804E4A08);
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
        SET_VT(self, lbl_804E499C);
        if (self) {
            SET_VT(self, lbl_804E4A08);
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
        SET_VT(self, lbl_804E49C4);
        if (self) {
            SET_VT(self, lbl_804E4A08);
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
        SET_VT(self, lbl_804E49EC);
        if (self) {
            SET_VT(self, lbl_804E4A08);
        }
        if (flag > 0) {
            MemoryManager_TimedFree(self);
        }
    }
    return self;
}

SteerAction *fn_801E2B88(SteerAction *self, short flag) {
    if (self) {
        SET_VT(self, lbl_804E4A08);
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

void fn_801E40E8(Ring *r) {
    r->count--;
    r->head++;
    if (r->head >= r->cap) {
        r->head -= r->cap;
    }
}

void fn_801E3A4C(char *self) {
    fn_801E4504(self + 4, 2);
    fn_801E4524(self + 4, 1, 0);
}

void fn_801E4504(void *self, int n) {
    fn_801E411C(self, n);
}

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
