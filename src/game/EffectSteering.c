/* nsEffectSteering action family, 0x8005B288..0x8005D954.
 *
 * Nondeferred code generation preserves address-order function definitions.
 * Each derived destructor is the first non-inline virtual (the vtable key).
 * The base destructor becomes inline before the derived destructors are
 * generated: its first vptr reference is therefore lazy. The class-action
 * stack emits Delay/Scale/InputViscosity/Shake/Split/Viscosity/Vibrate/base/Lock.
 * Keep the base definition here and the derived destructors in target order.
 *
 * The constructor's cleanup references emit the weak base destructor after
 * the constructor. ESRing's extra weak destructor and EH are discarded by
 * MWLD. All Reset/Step slots below are real members.
 *
 * The original constructor/destructor views of the enclosing steering owner
 * retain their distinct ownership wrappers and existing external bridges.
 */
#include "game/types/size_t.h"
void *operator new(size_t); void *operator new[](size_t);
void operator delete(void *); void operator delete[](void *);
#include "game/types/nsEffectSteering_clAction.h"
inline nsEffectSteering::clAction::~clAction() {}
struct ESKart { char pad0[0x9C]; float speed; };
struct ESCtor;
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
struct ESRing {
    ESRing(int n) : count(n)
    {
        if (count < 3) count = 3;
        count++;
        samples = 0;
        samples = new float[count];
        writeIndex = 0;
        readIndex = 0;
        remaining = 0;
    }
    ~ESRing() { delete[] samples; samples = 0; }
    int count;
    float *samples;
    int writeIndex, readIndex, remaining;

    int Next(int i) { int n = i + 1; if (n >= count) n = 0; return n; }
    unsigned char IsFull() { return Next(writeIndex) == readIndex; }
    unsigned char IsEmpty() { return readIndex == writeIndex; }

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
namespace nsEffectSteering {

struct clActionDelay : clAction {
    virtual ~clActionDelay();
    virtual void Reset();
    virtual void Step();
    ESCtor *owner;
    ESRing ring;
    int field1C;
    clActionDelay(ESCtor*p,int n):owner(p),ring(n){}
};

struct clActionScale : clAction {
    virtual ~clActionScale();
    virtual void Reset();
    virtual void Step();
    ESCtor *owner;
    float scale;
    clActionScale(ESCtor*p):owner(p){}
};

struct clActionInputViscosity : clAction {
    virtual ~clActionInputViscosity();
    virtual void Reset();
    virtual void Step();
    ESCtor *owner;
    float value,target,hi,lo,out;
    clActionInputViscosity(ESCtor*p):owner(p){}
};

struct clActionShake : clAction {
    virtual ~clActionShake();
    virtual void Reset();
    virtual void Step();
    ESCtor *owner;
    float amp;
    int period;
    ESCounter counter;
    float accum,out;
    clActionShake(ESCtor*p):owner(p){counter.start=0;counter.end=0;counter.step=0;counter.active=0;}
};

struct clActionSplit : clAction {
    virtual ~clActionSplit();
    virtual void Reset();
    virtual void Step();
    ESCtor *owner;
    int steps,value,timer;
    clActionSplit(ESCtor*p):owner(p){} unsigned char SetValue(int v);
};

struct clActionViscosity : clAction {
    virtual ~clActionViscosity();
    virtual void Reset();
    virtual void Step();
    ESCtor *owner;
    float value,hi,lo,vel,out;
    clActionViscosity(ESCtor*p):owner(p){}
};

struct clActionVibrate : clAction {
    virtual ~clActionVibrate();
    virtual void Reset();
    virtual void Step();
    ESCtor *owner;
    ESCounter counter;
    float amp;
    int field20;
    clActionVibrate(ESCtor*p):owner(p) {counter.start=0;counter.end=0;counter.step=0;counter.active=0;}
};

struct clActionLock : clAction {
    virtual ~clActionLock();
    virtual void Reset();
    virtual void Step();
    ESCtor *owner;
    float offset;
    clActionLock(ESCtor*p):owner(p){}
};
}
using namespace nsEffectSteering;
struct ESOwn1 {clActionLock *p; ESOwn1(ESCtor*s):p(new clActionLock(s)){} ~ESOwn1() throw();};
struct ESOwn2 {clActionVibrate *p; ESOwn2(ESCtor*s):p(new clActionVibrate(s)){} ~ESOwn2() throw();};
struct ESOwn3 {clActionViscosity *p; ESOwn3(ESCtor*s):p(new clActionViscosity(s)){} ~ESOwn3() throw();};
struct ESOwn4 {clActionSplit *p; ESOwn4(ESCtor*s):p(new clActionSplit(s)){} ~ESOwn4() throw();};
struct ESOwn5 {clActionShake *p; ESOwn5(ESCtor*s):p(new clActionShake(s)){} ~ESOwn5() throw();};
struct ESOwn6 {clActionInputViscosity *p; ESOwn6(ESCtor*s):p(new clActionInputViscosity(s)){} ~ESOwn6() throw();};
struct ESOwn7 {clActionScale *p; ESOwn7(ESCtor*s):p(new clActionScale(s)){} ~ESOwn7() throw();};
struct ESCtor {
ESKart *owner; unsigned char mode; char pad5[3]; int field8,fieldC,field10,field14;
unsigned char active; char pad19[3]; int field1C,field20;
ESOwn1 scale;ESOwn2 shake;ESOwn3 split;ESOwn4 viscosity;ESOwn5 vibrate;ESOwn6 lock;ESOwn7 range;
clActionDelay *delay; float out44,out48;
ESCtor(void*,unsigned char); float Speed(){return owner->speed;}
};
template <class T> struct ESOwn {
    T *p;
    ~ESOwn() throw() { delete p; }
};

struct ESListener {
    virtual void f0();
    virtual void Release();
};

struct ESDtor {
    void *owner; unsigned char mode; char pad5[3];
    int field8, fieldC, field10, field14;
    unsigned char active; char pad19[3]; int field1C; ESListener *listener;
    ESOwn<clActionLock> scale; ESOwn<clActionVibrate> shake; ESOwn<clActionViscosity> split; ESOwn<clActionSplit> viscosity;
    ESOwn<clActionShake> vibrate; ESOwn<clActionInputViscosity> lock; ESOwn<clActionScale> range; ESOwn<clActionDelay> delay;
    float value;
    ~ESDtor();
};

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

static inline void ESCmd2d(ESCtor *s, float v)
{
    KartItem_SetStrPcbCmd2dFromFloat(s->owner, v * StrPcb_GetIntensityScale(StrPcb_GetInstance()));
}

static inline void ESCmd2e(ESCtor *s, float v)
{
    KartItem_SetStrPcbCmd2eFromFloat(s->owner, v * StrPcb_GetIntensityScale(StrPcb_GetInstance()));
}

static inline void ESCmd2f(ESCtor *s, float v)
{
    KartItem_SetStrPcbCmd2fFromFloat(s->owner, v * StrPcb_GetIntensityScale(StrPcb_GetInstance()));
}



extern "C" void DebugPrintf(const char *, ...);
extern "C" void KartItem_ResetStrPcbToIdle(void *owner);
extern "C" void *StrPcb_GetInstance(void);
extern "C" float StrPcb_GetIntensityScale(void *pcb);
extern "C" void KartItem_SetStrPcbCmd2dFromFloat(void *kart, float value);
extern "C" void KartItem_SetStrPcbCmd2eFromFloat(void *kart, float value);
extern "C" const float lbl_806D2984;
extern "C" const float lbl_806D2988;

/* --- extern decls: sda21-referenced data --- */
extern "C" const float lbl_806D2978;
extern "C" const float lbl_806D297C;
extern "C" char lbl_806D298C;
extern "C" const float lbl_806D2980;

/* --- extern decls: large-data refs (@ha/@l pairs) --- */
/* Open array (`[]`) avoids sda21 strict-mode link errors when a future */
/* promote rewrites the asm_fn to C and references the symbol as `arr[i]`. */
extern "C" unsigned int jumptable_803F99E0[];
extern "C" unsigned int jumptable_803F9A08[];
extern "C" unsigned int lbl_802EDD98[];


/* Reset callbacks use the enclosing steering state and its output at +0x48. */
typedef struct EffectSteeringResetState {
    void *owner;
    unsigned char pad4[0x44];
    float output;
} EffectSteeringResetState;

typedef struct EffectActionResetState {
    void *vtable;
    EffectSteeringResetState *owner;
    unsigned char pad8[8];
    int field10;
    int field14;
    int field18;
} EffectActionResetState;

struct EffectInputDelay {
    /* As with Scale/Shake, reset is the second virtual slot (+0x0C). */
    virtual void v0();
    virtual void reset();
    unsigned char pad4[0x18];
    int sample_count;
};
struct EffectInputScale {
    virtual void v0();
    virtual void reset();
    unsigned char pad4[4];
    float field8;
};
struct EffectSteeringScale {
    void *owner; unsigned char pad4[4]; int start; int end; int current; int step;
    unsigned char active; unsigned char pad19[3]; volatile int mode;
    EffectInputScale *input; EffectInputScale *inputs[8]; float output;
};
struct EffectInputShake {
    virtual void v0();
    virtual void reset();
    unsigned char pad4[4];
    float field8;
    int fieldC;
    int field10;
    int field14;
    int field18;
    int field1C;
    unsigned char field20;
    unsigned char pad21[7];
    float field28;
};
struct EffectInputViscosity {
    virtual void v0();
    virtual void reset();
    unsigned char pad4[4];
    float field8;
    float fieldC;
    float field10;
    float field14;
    float field18;
};
struct EffectInputVibrate {
    virtual void v0();
    virtual void reset();
    void *owner;
    int start;
    int end;
    int current;
    int step;
    unsigned char active;
    unsigned char pad19[3];
    float field1C;
    int field20;
};
extern "C" int EffectSteering_InitForDelay(EffectSteeringScale *self, int sample_count, float duration);
extern "C" int EffectSteering_InitForScale(EffectSteeringScale *self, float duration, float value);
extern "C" int EffectSteering_InitForShake(EffectSteeringScale *self, float duration, float value, float cycle, float final_value);









/* Initialization methods and Reset slots follow target text order. */
extern "C" int EffectSteering_InitForDelay(EffectSteeringScale *self, int sample_count, float duration) {
    unsigned char ok;
    EffectInputDelay *input;
    if (self->mode != 0) self->input->reset();
    self->mode = 9;
    if (self->step > 0) {
        if (self->end >= self->start) goto reset_delay;
        goto no_reset_delay;
    } else if (self->end > self->start) goto no_reset_delay;
reset_delay:
    self->start = 0;
    self->current = self->start;
    self->end = (int)(lbl_806D2978 * duration);
    self->step = 1;
    self->active = 1;
no_reset_delay:
    switch (self->mode) {
    case 1: self->input = self->inputs[0]; break;
    case 2:
    case 4: self->input = self->inputs[1]; break;
    case 3: self->input = self->inputs[2]; break;
    case 5: self->input = self->inputs[3]; break;
    case 6: self->input = self->inputs[4]; break;
    case 7: self->input = self->inputs[5]; break;
    case 8: self->input = self->inputs[6]; break;
    case 9: self->input = self->inputs[7]; break;
    default: DebugPrintf((const char *)lbl_802EDD98); ok = 0; goto selected_delay;
    }
    ok = 1;
selected_delay:
    if (!ok) return 0;
    input = (EffectInputDelay *)self->inputs[7];
    input->sample_count = sample_count;
    if (input->sample_count >= 13) input->sample_count = 12;
    input->reset();
    return 1;
}
void clActionDelay::Reset() { /* 0x8005B43C size:0x54 */
    ESCtor *s = owner;
    KartItem_ResetStrPcbToIdle(s->owner);
    s->out48 = *(float *)&lbl_806D297C;
    ring.writeIndex = 0;
    ring.readIndex = 0;
    ring.remaining = 0;
}



extern "C" int EffectSteering_InitForScale(EffectSteeringScale *self, float duration, float value) {
    unsigned char ok;
    if (self->mode != 0) {
        self->input->reset();
    }
    self->mode = 8;
    if (self->step > 0) {
        if (self->end >= self->start) goto reset;
        goto no_reset;
    } else {
        if (self->end > self->start) goto no_reset;
    }
reset:
    self->start = 0;
    self->current = self->start;
    self->end = (int)(lbl_806D2978 * duration);
    self->step = 1;
    self->active = 1;
no_reset:
    switch (self->mode) {
    case 1: self->input = self->inputs[0]; break;
    case 2:
    case 4: self->input = self->inputs[1]; break;
    case 3: self->input = self->inputs[2]; break;
    case 5: self->input = self->inputs[3]; break;
    case 6: self->input = self->inputs[4]; break;
    case 7: self->input = self->inputs[5]; break;
    case 8: self->input = self->inputs[6]; break;
    case 9: self->input = self->inputs[7]; break;
    default: DebugPrintf((const char *)lbl_802EDD98); ok = 0; goto selected;
    }
    ok = 1;
selected:
    if (!ok) return 0;
    self->inputs[6]->field8 = value;
    return 1;
}

extern "C" int EffectSteering_InitForShake(EffectSteeringScale *self, float duration, float value, float cycle, float final_value) {
    unsigned char ok;
    EffectInputShake *shake;
    int half;
    if (self->mode != 0) {
        self->input->reset();
    }
    self->mode = 6;
    if (self->step > 0) {
        if (self->end >= self->start) goto reset;
        goto no_reset;
    } else {
        if (self->end > self->start) goto no_reset;
    }
reset:
    self->start = 0;
    self->current = self->start;
    self->end = (int)(lbl_806D2978 * duration);
    self->step = 1;
    self->active = 1;
no_reset:
    switch (self->mode) {
    case 1: self->input = self->inputs[0]; break;
    case 2:
    case 4: self->input = self->inputs[1]; break;
    case 3: self->input = self->inputs[2]; break;
    case 5: self->input = self->inputs[3]; break;
    case 6: self->input = self->inputs[4]; break;
    case 7: self->input = self->inputs[5]; break;
    case 8: self->input = self->inputs[6]; break;
    case 9: self->input = self->inputs[7]; break;
    default: DebugPrintf((const char *)lbl_802EDD98); ok = 0; goto selected;
    }
    ok = 1;
selected:
    if (!ok) return 0;
    shake = (EffectInputShake *)self->inputs[4];
    shake->reset();
    shake->field8 = value;
    shake->field28 = final_value;
    shake->fieldC = (int)(lbl_806D2980 * (lbl_806D2978 * cycle));
    half = shake->fieldC / 2;
    if (shake->field1C > 0) {
        if (shake->field14 >= shake->field10) goto shake_reset;
        goto done;
    } else {
        if (shake->field14 > shake->field10) goto done;
    }
shake_reset:
    shake->field10 = 0;
    shake->field18 = shake->field10;
    shake->field14 = half;
    shake->field1C = 1;
    shake->field20 = 1;
done:
    return 1;
}

/* Exact asm_fn bridges for the contiguous partial-matching range. */
typedef struct ActionShakeResetState {
    void *vtable;
    EffectSteeringResetState *owner;
    float field8;
    int fieldC;
    unsigned char pad10[0x14];
    float field24;
} ActionShakeResetState;





void clActionShake::Reset() { /* 0x8005B880 size:0x4C */
    ESCtor *s;
    /* The shared zero literal can be loaded in the function prologue. */
    float zero = 0.0f;
    amp = zero;
    period = 0;
    accum = zero;
    s = owner;
    KartItem_ResetStrPcbToIdle(s->owner);
    s->out48 = *(float *)&lbl_806D297C;
}


struct EffectInputSplit {
    virtual void v0();
    virtual void reset();
    EffectSteeringResetState *owner;
    int value;
};
static inline void SplitCmd2d(EffectSteeringResetState *owner, float value) {
    KartItem_SetStrPcbCmd2dFromFloat(owner->owner,
        value * StrPcb_GetIntensityScale(StrPcb_GetInstance()));
}
static inline void SplitCmd2e(EffectSteeringResetState *owner, float value) {
    KartItem_SetStrPcbCmd2eFromFloat(owner->owner,
        value * StrPcb_GetIntensityScale(StrPcb_GetInstance()));
}
extern "C" int EffectSteering_InitForSplit(EffectSteeringScale *self, int value, float duration) {
    unsigned char ok;
    EffectInputSplit *input;
    if (self->mode != 0) self->input->reset();
    self->mode = 5;
    if (self->step > 0) {
        if (self->end >= self->start) goto reset_split;
        goto no_reset_split;
    } else if (self->end > self->start) goto no_reset_split;
reset_split:
    self->start = 0;
    self->current = self->start;
    self->end = (int)(lbl_806D2978 * duration);
    self->step = 1;
    self->active = 1;
no_reset_split:
    switch (self->mode) {
    case 1: self->input = self->inputs[0]; break;
    case 2:
    case 4: self->input = self->inputs[1]; break;
    case 3: self->input = self->inputs[2]; break;
    case 5: self->input = self->inputs[3]; break;
    case 6: self->input = self->inputs[4]; break;
    case 7: self->input = self->inputs[5]; break;
    case 8: self->input = self->inputs[6]; break;
    case 9: self->input = self->inputs[7]; break;
    default: DebugPrintf((const char *)lbl_802EDD98); ok = 0; goto selected_split;
    }
    ok = 1;
selected_split:
    if (!ok) return 0;
    input = (EffectInputSplit *)self->inputs[3];
    input->reset();
    input->value = value;
    SplitCmd2d(input->owner, 0.7f);
    SplitCmd2e(input->owner, 1.0f);
    return 1;
}

typedef struct ActionSplitResetState {
    void *vtable;
    EffectSteeringResetState *owner;
    unsigned char pad8[4];
    int fieldC;
    int field10;
} ActionSplitResetState;





void clActionSplit::Reset() { /* 0x8005BAB0 size:0x50 */
    ESCtor *s = owner;
    KartItem_ResetStrPcbToIdle(s->owner);
    s->out48 = *(float *)&lbl_806D297C;
    value = 0;
    timer = 0;
}




extern "C" void EffectSteering_InputViscosity_SetFieldC(EffectSteeringScale *self, float value) {
    ((EffectInputViscosity *)self->inputs[5])->fieldC = value;
}

extern "C" int EffectSteering_InitForViscosity(EffectSteeringScale *self, float duration,
                                                float value8, float value10,
                                                float valueC, float value14,
                                                float value18);

extern "C" int EffectSteering_InitForViscosity(EffectSteeringScale *self, float duration,
                                                float value8, float value10,
                                                float valueC, float value14,
                                                float value18) {
    unsigned char ok;
    EffectInputViscosity *input;
    if (self->mode != 0) self->input->reset();
    self->mode = 3;
    if (self->step > 0) {
        if (self->end >= self->start) goto reset_viscosity;
        goto no_reset_viscosity;
    } else if (self->end > self->start) goto no_reset_viscosity;
reset_viscosity:
    self->start = 0;
    self->current = self->start;
    self->end = (int)(lbl_806D2978 * duration);
    self->step = 1;
    self->active = 1;
no_reset_viscosity:
    switch (self->mode) {
    case 1: self->input = self->inputs[0]; break;
    case 2:
    case 4: self->input = self->inputs[1]; break;
    case 3: self->input = self->inputs[2]; break;
    case 5: self->input = self->inputs[3]; break;
    case 6: self->input = self->inputs[4]; break;
    case 7: self->input = self->inputs[5]; break;
    case 8: self->input = self->inputs[6]; break;
    case 9: self->input = self->inputs[7]; break;
    default: DebugPrintf((const char *)lbl_802EDD98); ok = 0; goto selected_viscosity;
    }
    ok = 1;
selected_viscosity:
    if (!ok) return 0;
    input = (EffectInputViscosity *)self->inputs[2];
    input->field8 = value8;
    input->fieldC = valueC;
    input->field10 = value10;
    input->field14 = value14;
    input->field18 = value18;
    return 1;
}

extern "C" int EffectSteering_InitForViscosity_Uniform(EffectSteeringScale *self, float duration,
                                                        float uniform_value, float value18);

extern "C" int EffectSteering_InitForViscosity_Uniform(EffectSteeringScale *self, float duration,
                                                        float uniform_value, float value18) {
    unsigned char ok;
    EffectInputViscosity *input;
    float zero;
    if (self->mode != 0) self->input->reset();
    self->mode = 3;
    if (self->step > 0) {
        if (self->end >= self->start) goto reset_uniform;
        goto no_reset_uniform;
    } else if (self->end > self->start) goto no_reset_uniform;
reset_uniform:
    self->start = 0;
    self->current = self->start;
    self->end = (int)(lbl_806D2978 * duration);
    self->step = 1;
    self->active = 1;
no_reset_uniform:
    switch (self->mode) {
    case 1: self->input = self->inputs[0]; break;
    case 2:
    case 4: self->input = self->inputs[1]; break;
    case 3: self->input = self->inputs[2]; break;
    case 5: self->input = self->inputs[3]; break;
    case 6: self->input = self->inputs[4]; break;
    case 7: self->input = self->inputs[5]; break;
    case 8: self->input = self->inputs[6]; break;
    case 9: self->input = self->inputs[7]; break;
    default: DebugPrintf((const char *)lbl_802EDD98); ok = 0; goto selected_uniform;
    }
    ok = 1;
selected_uniform:
    if (!ok) return 0;
    input = (EffectInputViscosity *)self->inputs[2];
    zero = *(float *)&lbl_806D297C;
    input->field8 = uniform_value;
    input->fieldC = uniform_value;
    input->field10 = uniform_value;
    input->field14 = zero;
    input->field18 = value18;
    return 1;
}

extern "C" int EffectSteering_InitForVibrate_Sub(EffectSteeringScale *self, float duration, float value);

extern "C" int EffectSteering_InitForVibrate_Sub(EffectSteeringScale *self, float duration, float value) {
    unsigned char ok;
    EffectInputVibrate *input;
    if (self->mode != 0) self->input->reset();
    self->mode = 4;
    if (self->step > 0) {
        if (self->end >= self->start) goto reset_vibrate_sub;
        goto no_reset_vibrate_sub;
    } else if (self->end > self->start) goto no_reset_vibrate_sub;
reset_vibrate_sub:
    self->start = 0;
    self->current = self->start;
    self->end = (int)(lbl_806D2978 * duration);
    self->step = 1;
    self->active = 1;
no_reset_vibrate_sub:
    switch (self->mode) {
    case 1: self->input = self->inputs[0]; break;
    case 2:
    case 4: self->input = self->inputs[1]; break;
    case 3: self->input = self->inputs[2]; break;
    case 5: self->input = self->inputs[3]; break;
    case 6: self->input = self->inputs[4]; break;
    case 7: self->input = self->inputs[5]; break;
    case 8: self->input = self->inputs[6]; break;
    case 9: self->input = self->inputs[7]; break;
    default: DebugPrintf((const char *)lbl_802EDD98); ok = 0; goto selected_vibrate_sub;
    }
    ok = 1;
selected_vibrate_sub:
    if (!ok) return 0;
    input = (EffectInputVibrate *)self->inputs[1];
    input->reset();
    input->field1C = value;
    if (input->step > 0) {
        if (input->end >= input->start) goto reset_input_vibrate;
        goto done_vibrate_sub;
    } else if (input->end > input->start) goto done_vibrate_sub;
reset_input_vibrate:
    input->start = 0;
    input->current = input->start;
    input->end = 10000;
    input->step = 1;
    input->active = 1;
done_vibrate_sub:
    return 1;
}





void clActionVibrate::Reset() { /* 0x8005C0C4 size:0x38 */
    ESCtor *s = owner;
    KartItem_ResetStrPcbToIdle(s->owner);
    s->out48 = *(float *)&lbl_806D297C;
}



extern "C" int EffectSteering_InitForVibrate(EffectSteeringScale *self, float duration,
                                              float value, float input_duration);

extern "C" int EffectSteering_InitForVibrate(EffectSteeringScale *self, float duration,
                                              float value, float input_duration) {
    unsigned char ok;
    EffectInputVibrate *input;
    int input_end;
    if (self->mode != 0) self->input->reset();
    self->mode = 2;
    if (self->step > 0) {
        if (self->end >= self->start) goto reset_vibrate;
        goto no_reset_vibrate;
    } else if (self->end > self->start) goto no_reset_vibrate;
reset_vibrate:
    self->start = 0;
    self->current = self->start;
    self->end = (int)(lbl_806D2978 * duration);
    self->step = 1;
    self->active = 1;
no_reset_vibrate:
    switch (self->mode) {
    case 1: self->input = self->inputs[0]; break;
    case 2:
    case 4: self->input = self->inputs[1]; break;
    case 3: self->input = self->inputs[2]; break;
    case 5: self->input = self->inputs[3]; break;
    case 6: self->input = self->inputs[4]; break;
    case 7: self->input = self->inputs[5]; break;
    case 8: self->input = self->inputs[6]; break;
    case 9: self->input = self->inputs[7]; break;
    default: DebugPrintf((const char *)lbl_802EDD98); ok = 0; goto selected_vibrate;
    }
    ok = 1;
selected_vibrate:
    if (!ok) return 0;
    input = (EffectInputVibrate *)self->inputs[1];
    input->reset();
    input->field1C = value;
    input->field20 = (int)(lbl_806D2978 * input_duration);
    input_end = input->field20;
    if (input->step > 0) {
        if (input->end >= input->start) goto reset_input_vibrate;
        goto done_input_vibrate;
    } else if (input->end > input->start) goto done_input_vibrate;
reset_input_vibrate:
    input->start = 0;
    input->current = input->start;
    input->end = input_end;
    input->step = 1;
    input->active = 1;
done_input_vibrate:
    DebugPrintf(&lbl_806D298C, value);
    return 1;
}

extern "C" int EffectSteering_InitForLock(EffectSteeringScale *self, float duration, float value);

extern "C" int EffectSteering_InitForLock(EffectSteeringScale *self, float duration, float value) {
    unsigned char ok;
    EffectInputScale *input;
    if (self->mode != 0) self->input->reset();
    self->mode = 1;
    if (self->step > 0) {
        if (self->end >= self->start) goto reset_lock;
        goto no_reset_lock;
    } else if (self->end > self->start) goto no_reset_lock;
reset_lock:
    self->start = 0;
    self->current = self->start;
    self->end = (int)(lbl_806D2978 * duration);
    self->step = 1;
    self->active = 1;
no_reset_lock:
    switch (self->mode) {
    case 1: self->input = self->inputs[0]; break;
    case 2:
    case 4: self->input = self->inputs[1]; break;
    case 3: self->input = self->inputs[2]; break;
    case 5: self->input = self->inputs[3]; break;
    case 6: self->input = self->inputs[4]; break;
    case 7: self->input = self->inputs[5]; break;
    case 8: self->input = self->inputs[6]; break;
    case 9: self->input = self->inputs[7]; break;
    default: DebugPrintf((const char *)lbl_802EDD98); ok = 0; goto selected_lock;
    }
    ok = 1;
selected_lock:
    if (!ok) return 0;
    input = self->inputs[0];
    input->reset();
    input->field8 = value;
    return 1;
}

void clActionLock::Reset() {
    ESCtor *s = owner;
    KartItem_ResetStrPcbToIdle(s->owner);
    s->out48 = *(float *)&lbl_806D297C;
}

ESDtor::~ESDtor()
{
    if (field1C != 0) {
        listener->Release();
    }
}

clActionLock::~clActionLock() {}
clActionVibrate::~clActionVibrate() {}
clActionViscosity::~clActionViscosity() {}
clActionSplit::~clActionSplit() {}
clActionShake::~clActionShake() {}
clActionInputViscosity::~clActionInputViscosity() {}
clActionScale::~clActionScale() {}
clActionDelay::~clActionDelay() {}
ESCtor::ESCtor(void *p, unsigned char m)
    : owner((ESKart*)p), mode(m), field8(0), fieldC(0), field14(0), active(0),
      field1C(0), field20(0), scale(this), shake(this), split(this),
      viscosity(this), vibrate(this), lock(this), range(this)
{
    delay = new clActionDelay(this, 13);
    out44 = lbl_806D297C;
}
inline unsigned char clActionSplit::SetValue(int v)
    {
        unsigned char grew = 0;
        if (abs(v) > abs(value)) {
            grew = 1;
        }
        value = v;
        return grew;
    }
void clActionDelay::Step() {
    volatile float out = lbl_806D297C;

    ring.Pop((float *)&out);
    ring.Push(owner->owner->speed);
    owner->out44 = out;
}
void clActionScale::Reset() {
    ESCtor *s = owner;
    KartItem_ResetStrPcbToIdle(s->owner);
    s->out48 = lbl_806D297C;
}
void clActionScale::Step() {
    owner->out44 = scale * owner->Speed();
}
void clActionInputViscosity::Reset() {
    ESCtor *s = owner;
    KartItem_ResetStrPcbToIdle(s->owner);
    s->out48 = lbl_806D297C;
}
void clActionInputViscosity::Step() {
    value = Saturate_Double(value + (target > value ? lbl_806D2990 : lbl_806D2994),
                                  lo, hi);
    ESCmd2e(owner, value);
    owner->out44 = owner->owner->speed;
    owner->out48 = lbl_806D297C;
    ESCmd2d(owner, out);
}
void clActionShake::Step() {
    if (!counter.Tick()) {
        int period = this->period;
        if (counter.step > 0) {
            if (counter.end >= counter.start) {
                goto reset;
            }
            goto skip;
        } else if (counter.end > counter.start) {
            goto skip;
        }
    reset:
        counter.start = 0;
        counter.cur = counter.start;
        counter.end = period;
        counter.step = 1;
        counter.active = 1;
    skip:
        amp = -amp;
    }
    accum += amp;
    KartItem_SetStrPcbIntensityFromSpeed(owner->owner, accum);
    owner->out44 = owner->owner->speed;
    owner->out48 = accum;
    ESCmd2d(owner, out);
}
void clActionSplit::Step() {
    float k = lbl_806D2998;
    ESCtor *s = owner;
    float speed = s->owner->speed;
    int t = k * speed;

    if (t != 0) {
        int q = 1000 / steps;
        int n = t / q;
        s->out44 = (float)(n * q) / k;
    } else {
        s->out44 = lbl_806D297C;
    }
    if (SetValue(Clamp_Int(speed * steps, -steps, steps)) == 1) {
        timer = 2;
        ESCmd2e(owner, lbl_806D297C);
        owner->out48 = lbl_806D297C;
        ESCmd2d(owner, lbl_806D297C);
    }
    if (timer > 0) {
        timer--;
        if (timer <= 0) {
            timer = 0;
            s = owner;
            KartItem_ResetStrPcbToIdle(s->owner);
            s->out48 = lbl_806D297C;
            ESCmd2d(owner, lbl_806D2984);
            ESCmd2e(owner, lbl_806D2988);
        }
    }
}
void clActionViscosity::Reset() {
    ESCtor *s = owner;
    KartItem_ResetStrPcbToIdle(s->owner);
    s->out48 = lbl_806D297C;
}
void clActionViscosity::Step() {
    float v = value + vel;

    if (v > hi) {
        value = hi;
        vel = -vel;
    } else if (v < lo) {
        value = lo;
        vel = -vel;
    } else {
        value = v;
    }
    ESCmd2e(owner, value);
    owner->out44 = owner->owner->speed;
    owner->out48 = lbl_806D297C;
    ESCmd2d(owner, out);
}
void clActionVibrate::Step() {
    if (!counter.Tick()) {
        amp = -amp;
        counter.cur = counter.start;
        counter.active = 1;
    }
    owner->out44 = owner->owner->speed;
    ESCmd2f(owner, amp);
    owner->out48 = amp;
    ESCmd2d(owner, lbl_806D297C);
}
void clActionLock::Step() {
    owner->out44 = owner->owner->speed - offset;
    owner->out48 = owner->owner->speed - offset;
    KartItem_SetStrPcbIntensityFromSpeed(owner->owner, -offset);
}
ESOwn7::~ESOwn7() throw() { delete p; }
ESOwn6::~ESOwn6() throw() { delete p; }
ESOwn5::~ESOwn5() throw() { delete p; }
ESOwn4::~ESOwn4() throw() { delete p; }
ESOwn3::~ESOwn3() throw() { delete p; }
ESOwn2::~ESOwn2() throw() { delete p; }
ESOwn1::~ESOwn1() throw() { delete p; }
