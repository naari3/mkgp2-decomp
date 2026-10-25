/* AnimState accessors (0x800AE71C..0x800AE854): two empty stubs, the
 * per-axis product of the four layer scales, the product of the four layer
 * alphas, and the global-scale / timer setters. */

typedef struct AnimVec3 {
    float x, y, z;
} AnimVec3;

typedef struct AnimState {
    unsigned char pad00[0x08];
    float timer[8];
    float weight;
    unsigned char pad2c[0x3C - 0x2C];
    signed char timerOn[8];
    int current;
    AnimVec3 pos[4];
    AnimVec3 rot[4];
    AnimVec3 scale[4];
    float alpha[4];
} AnimState;

void fn_800AE71C(void)
{
}

void fn_800AE720(void)
{
}

float AnimState_GetTotalWeight(AnimState *self)
{
    return self->alpha[3] * (self->alpha[2] * (self->alpha[0] * self->alpha[1]));
}

float AnimState_GetTotalScaleZ(AnimState *self)
{
    return self->scale[3].z * (self->scale[2].z * (self->scale[0].z * self->scale[1].z));
}

float AnimState_GetTotalScaleY(AnimState *self)
{
    return self->scale[3].y * (self->scale[2].y * (self->scale[0].y * self->scale[1].y));
}

float AnimState_GetTotalScaleX(AnimState *self)
{
    return self->scale[3].x * (self->scale[2].x * (self->scale[0].x * self->scale[1].x));
}

void AnimState_SetGlobalScale(AnimState *self, float scale)
{
    self->weight = scale;
}

void AnimState_SetEnabledTimers(AnimState *self, float t)
{
    int i;

    for (i = 0; i < 8; i++) {
        if (self->timerOn[i]) {
            self->timer[i] = t;
            self->timerOn[i] = 1;
        }
    }
}
