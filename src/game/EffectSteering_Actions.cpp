/* Steering action Reset/Step methods and owner-holder destructors,
 * 0x8005CCBC..0x8005D954. Layout views match EffectSteeringCtor.cpp.
 * The holder destructors are the out-of-line copies the constructor's
 * cleanup calls; their extab entries come first (extab_order.json).
 *
 * NonMatching: ActionDelay_Step allocates r4/r5 the other way round in the
 * push half. The target also keeps `out` in a stack slot, which the
 * volatile reproduces.
 */
void operator delete(void *);

extern "C" {
void KartItem_ResetStrPcbToIdle(void *kart);
void KartItem_SetStrPcbIntensityFromSpeed(void *kart, float value);
void KartItem_SetStrPcbCmd2dFromFloat(void *kart, float value);
void KartItem_SetStrPcbCmd2eFromFloat(void *kart, float value);
void KartItem_SetStrPcbCmd2fFromFloat(void *kart, float value);
void *StrPcb_GetInstance(void);
float StrPcb_GetIntensityScale(void *pcb);
float Saturate_Double(float v, float lo, float hi);
int Clamp_Int(int v, int lo, int hi);
int abs(int v);

extern const float lbl_806D297C; /* 0.0f */
extern const float lbl_806D2984; /* 0.7f */
extern const float lbl_806D2988; /* 1.0f */
extern const float lbl_806D2990; /* 0.01f */
extern const float lbl_806D2994; /* -0.01f */
extern const float lbl_806D2998; /* 1000.0f */
}

struct ESKart {
    char pad0[0x9C];
    float speed;
};

struct ESSteer {
    ESKart *kart;
    char pad4[0x40];
    float out44;
    float out48;

    float Speed() { return kart->speed; }
};

static inline void ESCmd2d(ESSteer *s, float v)
{
    KartItem_SetStrPcbCmd2dFromFloat(s->kart, v * StrPcb_GetIntensityScale(StrPcb_GetInstance()));
}

static inline void ESCmd2e(ESSteer *s, float v)
{
    KartItem_SetStrPcbCmd2eFromFloat(s->kart, v * StrPcb_GetIntensityScale(StrPcb_GetInstance()));
}

static inline void ESCmd2f(ESSteer *s, float v)
{
    KartItem_SetStrPcbCmd2fFromFloat(s->kart, v * StrPcb_GetIntensityScale(StrPcb_GetInstance()));
}

struct ESCounter {
    int start, end, cur, step;
    unsigned char active;

    unsigned char Tick()
    {
        if (!active) {
            return 0;
        }
        cur += step;
        if (step > 0) {
            if (end < cur) {
                active = 0;
                cur = end;
            }
        } else if (end > cur) {
            active = 0;
            cur = end;
        }
        return active;
    }
};

struct ESBase {
    virtual ~ESBase();
    virtual void Reset();
    virtual void Step();
};

ESBase::~ESBase() {}

struct ESRing {
    int count;
    float *samples;
    int writeIndex, readIndex, remaining;

    int Next(int i) { i++; if (i >= count) i = 0; return i; }
    unsigned char IsFull() { return Next(writeIndex) == readIndex; }
    unsigned char IsEmpty() { return writeIndex == readIndex; }

    void Pop(float *out)
    {
        if (IsFull() == 1 && IsEmpty() != 1) {
            *out = samples[readIndex++];
            if (readIndex >= count) {
                readIndex = 0;
            }
            remaining--;
        }
    }

    void Push(float in)
    {
        if (IsFull() != 1) {
            samples[writeIndex++] = in;
            if (writeIndex >= count) {
                writeIndex = 0;
            }
            remaining++;
        }
    }
};

struct ESDelayState {
    void *vtable;
    ESSteer *steer;
    ESRing ring;
};

extern "C" void ActionDelay_Step(ESDelayState *self)
{
    volatile float out = lbl_806D297C;

    self->ring.Pop((float *)&out);
    self->ring.Push(self->steer->kart->speed);
    self->steer->out44 = out;
}

struct ESScaleState {
    void *vtable;
    ESSteer *steer;
    float scale;
};

extern "C" void ActionScale_Reset(ESScaleState *self)
{
    ESSteer *s = self->steer;
    KartItem_ResetStrPcbToIdle(s->kart);
    s->out48 = lbl_806D297C;
}

extern "C" void ActionScale_Step(ESScaleState *self)
{
    self->steer->out44 = self->scale * self->steer->Speed();
}

struct ESInputViscosityState {
    void *vtable;
    ESSteer *steer;
    float value, target, hi, lo, out;
};

extern "C" void ActionInputViscosity_Reset(ESInputViscosityState *self)
{
    ESSteer *s = self->steer;
    KartItem_ResetStrPcbToIdle(s->kart);
    s->out48 = lbl_806D297C;
}

extern "C" void ActionInputViscosity_Step(ESInputViscosityState *self)
{
    self->value = Saturate_Double(self->value + (self->target > self->value ? lbl_806D2990 : lbl_806D2994),
                                  self->lo, self->hi);
    ESCmd2e(self->steer, self->value);
    self->steer->out44 = self->steer->kart->speed;
    self->steer->out48 = lbl_806D297C;
    ESCmd2d(self->steer, self->out);
}

struct ESShakeState {
    void *vtable;
    ESSteer *steer;
    float amp;
    int period;
    ESCounter counter;
    float accum;
    float out;
};

extern "C" void ActionShake_Step(ESShakeState *self)
{
    if (!self->counter.Tick()) {
        int period = self->period;
        if (self->counter.step > 0) {
            if (self->counter.end >= self->counter.start) {
                goto reset;
            }
            goto skip;
        } else if (self->counter.end > self->counter.start) {
            goto skip;
        }
    reset:
        self->counter.start = 0;
        self->counter.cur = self->counter.start;
        self->counter.end = period;
        self->counter.step = 1;
        self->counter.active = 1;
    skip:
        self->amp = -self->amp;
    }
    self->accum += self->amp;
    KartItem_SetStrPcbIntensityFromSpeed(self->steer->kart, self->accum);
    self->steer->out44 = self->steer->kart->speed;
    self->steer->out48 = self->accum;
    ESCmd2d(self->steer, self->out);
}

struct ESSplitState {
    void *vtable;
    ESSteer *steer;
    int steps;
    int value;
    int timer;

    unsigned char SetValue(int v)
    {
        unsigned char grew = 0;
        if (abs(v) > abs(value)) {
            grew = 1;
        }
        value = v;
        return grew;
    }
};

extern "C" void ActionSplit_Step(ESSplitState *self)
{
    float k = lbl_806D2998;
    ESSteer *s = self->steer;
    float speed = s->kart->speed;
    int t = k * speed;

    if (t != 0) {
        int q = 1000 / self->steps;
        int n = t / q;
        s->out44 = (float)(n * q) / k;
    } else {
        s->out44 = lbl_806D297C;
    }
    if (self->SetValue(Clamp_Int(speed * self->steps, -self->steps, self->steps)) == 1) {
        self->timer = 2;
        ESCmd2e(self->steer, lbl_806D297C);
        self->steer->out48 = lbl_806D297C;
        ESCmd2d(self->steer, lbl_806D297C);
    }
    if (self->timer > 0) {
        self->timer--;
        if (self->timer <= 0) {
            self->timer = 0;
            s = self->steer;
            KartItem_ResetStrPcbToIdle(s->kart);
            s->out48 = lbl_806D297C;
            ESCmd2d(self->steer, lbl_806D2984);
            ESCmd2e(self->steer, lbl_806D2988);
        }
    }
}

struct ESViscosityState {
    void *vtable;
    ESSteer *steer;
    float value, hi, lo, vel, out;
};

extern "C" void ActionViscosity_Reset(ESViscosityState *self)
{
    ESSteer *s = self->steer;
    KartItem_ResetStrPcbToIdle(s->kart);
    s->out48 = lbl_806D297C;
}

extern "C" void ActionViscosity_Step(ESViscosityState *self)
{
    float v = self->value + self->vel;

    if (v > self->hi) {
        self->value = self->hi;
        self->vel = -self->vel;
    } else if (v < self->lo) {
        self->value = self->lo;
        self->vel = -self->vel;
    } else {
        self->value = v;
    }
    ESCmd2e(self->steer, self->value);
    self->steer->out44 = self->steer->kart->speed;
    self->steer->out48 = lbl_806D297C;
    ESCmd2d(self->steer, self->out);
}

struct ESVibrateState {
    void *vtable;
    ESSteer *steer;
    ESCounter counter;
    float amp;
};

extern "C" void ActionVibrate_Step(ESVibrateState *self)
{
    if (!self->counter.Tick()) {
        self->amp = -self->amp;
        self->counter.cur = self->counter.start;
        self->counter.active = 1;
    }
    self->steer->out44 = self->steer->kart->speed;
    ESCmd2f(self->steer, self->amp);
    self->steer->out48 = self->amp;
    ESCmd2d(self->steer, lbl_806D297C);
}

struct ESLockState {
    void *vtable;
    ESSteer *steer;
    float offset;
};

extern "C" void ActionLock_Step(ESLockState *self)
{
    self->steer->out44 = self->steer->kart->speed - self->offset;
    self->steer->out48 = self->steer->kart->speed - self->offset;
    KartItem_SetStrPcbIntensityFromSpeed(self->steer->kart, -self->offset);
}

struct ESOwn7 { ESBase *p; ~ESOwn7() throw(); };
struct ESOwn6 { ESBase *p; ~ESOwn6() throw(); };
struct ESOwn5 { ESBase *p; ~ESOwn5() throw(); };
struct ESOwn4 { ESBase *p; ~ESOwn4() throw(); };
struct ESOwn3 { ESBase *p; ~ESOwn3() throw(); };
struct ESOwn2 { ESBase *p; ~ESOwn2() throw(); };
struct ESOwn1 { ESBase *p; ~ESOwn1() throw(); };

ESOwn7::~ESOwn7() throw() { delete p; }
ESOwn6::~ESOwn6() throw() { delete p; }
ESOwn5::~ESOwn5() throw() { delete p; }
ESOwn4::~ESOwn4() throw() { delete p; }
ESOwn3::~ESOwn3() throw() { delete p; }
ESOwn2::~ESOwn2() throw() { delete p; }
ESOwn1::~ESOwn1() throw() { delete p; }
