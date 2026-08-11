/* === extracted from EffectSteering === */
/* Copy into the TU between forward decls and function bodies; */
/* keep emit order = target section layout (do not sort). */

/* --- extern decls: branch callees (bl/b targets) --- */
/* Open prototype (`extern void Foo();`) accepts any call signature; */
/* refine if the real prototype matters for header consumers. */
extern void DebugPrintf(const char *, ...);
extern void KartItem_ResetStrPcbToIdle();
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
asm void EffectSteering_InitForDelay(void);
asm void ActionDelay_Reset(void);
#pragma cplusplus on
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

/* --- asm function bodies (.text order = fn address order) --- */
asm void EffectSteering_InitForDelay(void) { /* 0x8005B288 size:0x1B4 */
    nofralloc
    stwu r1, -0x30(r1)
    mflr r0
    stw r0, 0x34(r1)
    stfd f31, 0x20(r1)
    psq_st f31, 0x28(r1), 0, 0
    stw r31, 0x1c(r1)
    stw r30, 0x18(r1)
    mr r30, r3
    fmr f31, f1
    lwz r0, 0x1c(r3)
    mr r31, r4
    cmpwi r0, 0x0
    beq EffectSteering_InitForDelay_L_8005B2D0
    lwz r3, 0x20(r30)
    lwz r12, 0x0(r3)
    lwz r12, 0xc(r12)
    mtctr r12
    bctrl
    EffectSteering_InitForDelay_L_8005B2D0:
    li r0, 0x9
    stw r0, 0x1c(r30)
    lwz r0, 0x14(r30)
    cmpwi r0, 0x0
    ble EffectSteering_InitForDelay_L_8005B2F8
    lwz r3, 0xc(r30)
    lwz r0, 0x8(r30)
    cmpw r3, r0
    bge EffectSteering_InitForDelay_L_8005B308
    b EffectSteering_InitForDelay_L_8005B33C
    EffectSteering_InitForDelay_L_8005B2F8:
    lwz r3, 0xc(r30)
    lwz r0, 0x8(r30)
    cmpw r3, r0
    bgt EffectSteering_InitForDelay_L_8005B33C
    EffectSteering_InitForDelay_L_8005B308:
    lfs f0, lbl_806D2978(r2)
    li r0, 0x0
    stw r0, 0x8(r30)
    li r0, 0x1
    fmuls f0, f0, f31
    lwz r3, 0x8(r30)
    fctiwz f0, f0
    stw r3, 0x10(r30)
    stfd f0, 0x8(r1)
    lwz r3, 0xc(r1)
    stw r3, 0xc(r30)
    stw r0, 0x14(r30)
    stb r0, 0x18(r30)
    EffectSteering_InitForDelay_L_8005B33C:
    lwz r0, 0x1c(r30)
    cmplwi r0, 0x9
    bgt EffectSteering_InitForDelay_L_8005B3C0
    lis r3, jumptable_803F99E0@ha
    slwi r0, r0, 2
    addi r3, r3, jumptable_803F99E0@l
    lwzx r0, r3, r0
    mtctr r0
    bctr
    lwz r0, 0x24(r30)
    stw r0, 0x20(r30)
    b EffectSteering_InitForDelay_L_8005B3D8
    lwz r0, 0x28(r30)
    stw r0, 0x20(r30)
    b EffectSteering_InitForDelay_L_8005B3D8
    lwz r0, 0x2c(r30)
    stw r0, 0x20(r30)
    b EffectSteering_InitForDelay_L_8005B3D8
    lwz r0, 0x30(r30)
    stw r0, 0x20(r30)
    b EffectSteering_InitForDelay_L_8005B3D8
    lwz r0, 0x34(r30)
    stw r0, 0x20(r30)
    b EffectSteering_InitForDelay_L_8005B3D8
    lwz r0, 0x38(r30)
    stw r0, 0x20(r30)
    b EffectSteering_InitForDelay_L_8005B3D8
    lwz r0, 0x3c(r30)
    stw r0, 0x20(r30)
    b EffectSteering_InitForDelay_L_8005B3D8
    lwz r0, 0x40(r30)
    stw r0, 0x20(r30)
    b EffectSteering_InitForDelay_L_8005B3D8
    EffectSteering_InitForDelay_L_8005B3C0:
    lis r3, lbl_802EDD98@ha
    addi r3, r3, lbl_802EDD98@l
    crxor 6, 6, 6
    bl DebugPrintf
    li r0, 0x0
    b EffectSteering_InitForDelay_L_8005B3DC
    EffectSteering_InitForDelay_L_8005B3D8:
    li r0, 0x1
    EffectSteering_InitForDelay_L_8005B3DC:
    clrlwi. r0, r0, 24
    bne EffectSteering_InitForDelay_L_8005B3EC
    li r3, 0x0
    b EffectSteering_InitForDelay_L_8005B41C
    EffectSteering_InitForDelay_L_8005B3EC:
    lwz r3, 0x40(r30)
    stw r31, 0x1c(r3)
    lwz r0, 0x1c(r3)
    cmpwi r0, 0xd
    blt EffectSteering_InitForDelay_L_8005B408
    li r0, 0xc
    stw r0, 0x1c(r3)
    EffectSteering_InitForDelay_L_8005B408:
    lwz r12, 0x0(r3)
    lwz r12, 0xc(r12)
    mtctr r12
    bctrl
    li r3, 0x1
    EffectSteering_InitForDelay_L_8005B41C:
    psq_l f31, 0x28(r1), 0, 0
    lwz r0, 0x34(r1)
    lfd f31, 0x20(r1)
    lwz r31, 0x1c(r1)
    lwz r30, 0x18(r1)
    mtlr r0
    addi r1, r1, 0x30
    blr
}



asm void ActionDelay_Reset(void) { /* 0x8005B43C size:0x54 */
    nofralloc
    stwu r1, -0x10(r1)
    mflr r0
    stw r0, 0x14(r1)
    stw r31, 0xc(r1)
    stw r30, 0x8(r1)
    mr r30, r3
    lwz r31, 0x4(r3)
    lwz r3, 0x0(r31)
    bl KartItem_ResetStrPcbToIdle
    lfs f0, lbl_806D297C(r2)
    li r0, 0x0
    stfs f0, 0x48(r31)
    stw r0, 0x10(r30)
    stw r0, 0x14(r30)
    stw r0, 0x18(r30)
    lwz r31, 0xc(r1)
    lwz r30, 0x8(r1)
    lwz r0, 0x14(r1)
    mtlr r0
    addi r1, r1, 0x10
    blr
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
#pragma cplusplus off
