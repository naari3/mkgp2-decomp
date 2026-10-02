typedef struct ActionSplitResetState {
    void *vtable;
    EffectSteeringResetState *owner;
    unsigned char pad8[4];
    int fieldC;
    int field10;
} ActionSplitResetState;

void ActionSplit_Reset(ActionSplitResetState *self);

/* --- extab (manual emit, .extab_user -> extab via objcopy) --- */
#pragma section R ".extab_user"
__declspec(section ".extab_user") static const unsigned char extab_ActionSplit_Reset[8] = {
    0x10, 0x0A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

/* --- extabindex (manual emit, .extabindex_user -> extabindex via objcopy) --- */
#pragma section R ".extabindex_user"
__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_ActionSplit_Reset = {
    (void *)&ActionSplit_Reset, 0x00000050, (void *)extab_ActionSplit_Reset
};

/* Included by EffectSteering.c; retain its manual EH emission order. */
void ActionSplit_Reset(ActionSplitResetState *self) { /* 0x8005BAB0 size:0x50 */
    EffectSteeringResetState *owner = self->owner;
    KartItem_ResetStrPcbToIdle(owner->owner);
    owner->output = *(float *)&lbl_806D297C;
    self->fieldC = 0;
    self->field10 = 0;
}

