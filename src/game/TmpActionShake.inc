typedef struct ActionShakeResetState {
    void *vtable;
    EffectSteeringResetState *owner;
    float field8;
    int fieldC;
    unsigned char pad10[0x14];
    float field24;
} ActionShakeResetState;

void ActionShake_Reset(ActionShakeResetState *self);

/* --- extab (manual emit, .extab_user -> extab via objcopy) --- */
#pragma section R ".extab_user"
__declspec(section ".extab_user") static const unsigned char extab_ActionShake_Reset[8] = {
    0x08, 0x0A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

/* --- extabindex (manual emit, .extabindex_user -> extabindex via objcopy) --- */
#pragma section R ".extabindex_user"
__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_ActionShake_Reset = {
    (void *)&ActionShake_Reset, 0x0000004C, (void *)extab_ActionShake_Reset
};

/* Included by EffectSteering.c; retain its manual EH emission order. */
void ActionShake_Reset(ActionShakeResetState *self) { /* 0x8005B880 size:0x4C */
    EffectSteeringResetState *owner;
    /* The shared zero literal can be loaded in the function prologue. */
    float zero = 0.0f;
    self->field8 = zero;
    self->fieldC = 0;
    self->field24 = zero;
    owner = self->owner;
    KartItem_ResetStrPcbToIdle(owner->owner);
    owner->output = *(float *)&lbl_806D297C;
}

