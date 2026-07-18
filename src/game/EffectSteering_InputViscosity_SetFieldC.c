typedef struct InputViscosity {
    unsigned char padding[0xc];
    float field_c;
} InputViscosity;

typedef struct EffectSteering {
    unsigned char padding[0x38];
    InputViscosity *input_viscosity;
} EffectSteering;

void EffectSteering_InputViscosity_SetFieldC(EffectSteering *self, float value)
{
    self->input_viscosity->field_c = value;
}
