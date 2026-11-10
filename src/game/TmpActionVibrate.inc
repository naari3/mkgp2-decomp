void ActionVibrate_Reset(EffectActionResetState *self);

/* --- extab (manual emit, .extab_user -> extab via objcopy) --- */
#pragma section R ".extab_user"
__declspec(section ".extab_user") static const unsigned char extab_ActionVibrate_Reset[8] = {
    0x08, 0x0A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

/* --- extabindex (manual emit, .extabindex_user -> extabindex via objcopy) --- */
#pragma section R ".extabindex_user"
__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_ActionVibrate_Reset = {
    (void *)&ActionVibrate_Reset, 0x00000038, (void *)extab_ActionVibrate_Reset
};

/* Included by EffectSteering.c; retain its manual EH emission order. */
void ActionVibrate_Reset(EffectActionResetState *self) { /* 0x8005C0C4 size:0x38 */
    EffectSteeringResetState *owner = self->owner;
    KartItem_ResetStrPcbToIdle(owner->owner);
    owner->output = *(float *)&lbl_806D297C;
}

