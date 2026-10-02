/* === extracted from EffectSteering === */
/* Copy into the TU between forward decls and function bodies; */
/* keep emit order = target section layout (do not sort). */

/* --- extern decls: branch callees (bl/b targets) --- */
/* Open prototype (`extern void Foo();`) accepts any call signature; */
/* refine if the real prototype matters for header consumers. */
extern void DebugPrintf(const char *, ...);
extern void KartItem_ResetStrPcbToIdle(void *owner);
extern void StrPcb_GetInstance();
extern void StrPcb_GetIntensityScale();
extern void KartItem_SetStrPcbCmd2dFromFloat();
extern void KartItem_SetStrPcbCmd2eFromFloat();
extern unsigned int lbl_806D2984;
extern unsigned int lbl_806D2988;

/* --- extern decls: sda21-referenced data --- */
extern const float lbl_806D2978;
extern unsigned int lbl_806D297C;
extern char lbl_806D298C;
extern const float lbl_806D2980;

/* --- extern decls: large-data refs (@ha/@l pairs) --- */
/* Open array (`[]`) avoids sda21 strict-mode link errors when a future */
/* promote rewrites the asm_fn to C and references the symbol as `arr[i]`. */
extern unsigned int jumptable_803F99E0[];
extern unsigned int jumptable_803F9A08[];
extern void *jumptable_803F9A58[];
extern unsigned int lbl_802EDD98[];

/* --- function index (1 fns, .text 0x8005B288..0x8005B43C) ---
 * [  0] 0x8005B288 size:0x1B4   global EffectSteering_InitForDelay
 */

/* --- forward decls --- */
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

void ActionDelay_Reset(EffectActionResetState *self);
#pragma cplusplus on
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
#pragma cplusplus off

/* --- extab (manual emit, .extab_user -> extab via objcopy) --- */
#pragma section R ".extab_user"
__declspec(section ".extab_user") static const unsigned char extab_EffectSteering_InitForDelay[8] = {
    0x10, 0x4A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

/* --- extabindex (manual emit, .extabindex_user -> extabindex via objcopy) --- */
#pragma section R ".extabindex_user"
__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_EffectSteering_InitForDelay = {
    (void *)&EffectSteering_InitForDelay, 0x000001B4, (void *)extab_EffectSteering_InitForDelay
};

/* --- extab (manual emit, .extab_user -> extab via objcopy) --- */
#pragma section R ".extab_user"
__declspec(section ".extab_user") static const unsigned char extab_ActionDelay_Reset[8] = {
    0x10, 0x0A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

/* --- extabindex (manual emit, .extabindex_user -> extabindex via objcopy) --- */
#pragma section R ".extabindex_user"
__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_ActionDelay_Reset = {
    (void *)&ActionDelay_Reset, 0x00000054, (void *)extab_ActionDelay_Reset
};

/* --- extab (manual emit, .extab_user -> extab via objcopy) --- */
#pragma section R ".extab_user"
__declspec(section ".extab_user") static const unsigned char extab_EffectSteering_InitForScale[8] = {
    0x08, 0x8A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

/* --- extabindex (manual emit, .extabindex_user -> extabindex via objcopy) --- */
#pragma section R ".extabindex_user"
__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_EffectSteering_InitForScale = {
    (void *)&EffectSteering_InitForScale, 0x00000198, (void *)extab_EffectSteering_InitForScale
};

#pragma section R ".extab_user"
__declspec(section ".extab_user") static const unsigned char extab_EffectSteering_InitForShake[8] = {
    0x09, 0x0A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

#pragma section R ".extabindex_user"
__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_EffectSteering_InitForShake = {
    (void *)&EffectSteering_InitForShake, 0x00000258, (void *)extab_EffectSteering_InitForShake
};

/* Function bodies follow target .text order. Manual EH records are retained. */
#pragma cplusplus on
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
#pragma cplusplus off
void ActionDelay_Reset(EffectActionResetState *self) { /* 0x8005B43C size:0x54 */
    EffectSteeringResetState *owner = self->owner;
    KartItem_ResetStrPcbToIdle(owner->owner);
    owner->output = *(float *)&lbl_806D297C;
    self->field10 = 0;
    self->field14 = 0;
    self->field18 = 0;
}



#pragma cplusplus on
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
#pragma cplusplus off

/* Exact asm_fn bridges for the contiguous partial-matching range. */
#include "src/game/TmpActionShake.c"
#include "src/game/TmpSplit.c"
#include "src/game/TmpActionSplit.c"

#pragma cplusplus on
#pragma section RW ".data"
__declspec(section ".data") void *jumptable_803F9A58[10] = {
    (char *)&EffectSteering_InitForSplit + 0x13C,
    (char *)&EffectSteering_InitForSplit + 0x0DC,
    (char *)&EffectSteering_InitForSplit + 0x0E8,
    (char *)&EffectSteering_InitForSplit + 0x0F4,
    (char *)&EffectSteering_InitForSplit + 0x0E8,
    (char *)&EffectSteering_InitForSplit + 0x100,
    (char *)&EffectSteering_InitForSplit + 0x10C,
    (char *)&EffectSteering_InitForSplit + 0x118,
    (char *)&EffectSteering_InitForSplit + 0x124,
    (char *)&EffectSteering_InitForSplit + 0x130
};

extern "C" void EffectSteering_InputViscosity_SetFieldC(EffectSteeringScale *self, float value) {
    ((EffectInputViscosity *)self->inputs[5])->fieldC = value;
}

extern "C" int EffectSteering_InitForViscosity(EffectSteeringScale *self, float duration,
                                                float value8, float value10,
                                                float valueC, float value14,
                                                float value18);
#pragma section R ".extab_user"
__declspec(section ".extab_user") static const unsigned char extab_EffectSteering_InitForViscosity[8] = {
    0x09, 0x8A, 0, 0, 0, 0, 0, 0
};
#pragma section R ".extabindex_user"
__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_EffectSteering_InitForViscosity = {
    (void *)&EffectSteering_InitForViscosity, 0x1F8, (void *)extab_EffectSteering_InitForViscosity
};

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
#pragma section R ".extab_user"
__declspec(section ".extab_user") static const unsigned char extab_EffectSteering_InitForViscosity_Uniform[8] = {
    0x08, 0xCA, 0, 0, 0, 0, 0, 0
};
#pragma section R ".extabindex_user"
__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_EffectSteering_InitForViscosity_Uniform = {
    (void *)&EffectSteering_InitForViscosity_Uniform, 0x1C0, (void *)extab_EffectSteering_InitForViscosity_Uniform
};

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
#pragma section R ".extab_user"
__declspec(section ".extab_user") static const unsigned char extab_EffectSteering_InitForVibrate_Sub[8] = {
    0x08, 0x8A, 0, 0, 0, 0, 0, 0
};
#pragma section R ".extabindex_user"
__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_EffectSteering_InitForVibrate_Sub = {
    (void *)&EffectSteering_InitForVibrate_Sub, 0x200, (void *)extab_EffectSteering_InitForVibrate_Sub
};

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
#pragma cplusplus off

#include "src/game/TmpActionVibrate.c"

#pragma cplusplus on
extern "C" int EffectSteering_InitForVibrate(EffectSteeringScale *self, float duration,
                                              float value, float input_duration);
#pragma section R ".extab_user"
__declspec(section ".extab_user") static const unsigned char extab_EffectSteering_InitForVibrate[8] = {
    0x08, 0xCA, 0, 0, 0, 0, 0, 0
};
#pragma section R ".extabindex_user"
__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_EffectSteering_InitForVibrate = {
    (void *)&EffectSteering_InitForVibrate, 0x23C, (void *)extab_EffectSteering_InitForVibrate
};

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
#pragma section R ".extab_user"
__declspec(section ".extab_user") static const unsigned char extab_EffectSteering_InitForLock[8] = {
    0x08, 0x8A, 0, 0, 0, 0, 0, 0
};
#pragma section R ".extabindex_user"
__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_EffectSteering_InitForLock = {
    (void *)&EffectSteering_InitForLock, 0x1AC, (void *)extab_EffectSteering_InitForLock
};

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
#pragma cplusplus off

void ActionLock_Reset(EffectActionResetState *self);
#pragma section R ".extab_user"
__declspec(section ".extab_user") static const unsigned char extab_ActionLock_Reset[8] = {
    0x08, 0x0A, 0, 0, 0, 0, 0, 0
};
#pragma section R ".extabindex_user"
__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_ActionLock_Reset = {
    (void *)&ActionLock_Reset, 0x38, (void *)extab_ActionLock_Reset
};
void ActionLock_Reset(EffectActionResetState *self) {
    EffectSteeringResetState *owner = self->owner;
    KartItem_ResetStrPcbToIdle(owner->owner);
    owner->output = *(float *)&lbl_806D297C;
}
