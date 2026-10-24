typedef struct DrawEffect {
    unsigned char pad_00[0x28];
    unsigned char active;
    unsigned char pad_29[3];
    float intensity;
    unsigned char pad_30[0x5C];
    float position[3];
    unsigned char pad_98[0x18];
    float scale;
} DrawEffect;

extern void Vec3_Copy(float *dst, float *src);

void DrawEffect_ApplyScaleAndIntensity(DrawEffect *effect, float scale, float intensity,
                                       float *position) {
    if (effect != 0) {
        Vec3_Copy(effect->position, position);
        effect->scale = scale;
        effect->intensity = intensity;
        if (0.0f < intensity) {
            effect->active = 1;
        } else {
            effect->active = 0;
        }
    }
}
