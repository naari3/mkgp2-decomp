#pragma cplusplus on
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
#pragma exceptions on
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
#pragma exceptions reset
#pragma cplusplus off
