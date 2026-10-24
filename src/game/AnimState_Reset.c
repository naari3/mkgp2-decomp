typedef struct AnimVec3 {
    float x, y, z;
} AnimVec3;

typedef struct AnimState {
    unsigned char pad00[0x28];
    float weight;
    unsigned char pad2c[0x44 - 0x2C];
    int current;
    AnimVec3 pos[4];
    AnimVec3 rot[4];
    AnimVec3 scale[4];
    float alpha[4];
} AnimState;

extern void AnimState_Init(AnimState *, float);

void AnimState_Reset(AnimState *self)
{
    int i;

    self->current = -1;
    for (i = 0; i < 4; i++) {
        self->pos[i].x = 0.0f;
        self->pos[i].y = 0.0f;
        self->pos[i].z = 0.0f;
        self->rot[i].x = 0.0f;
        self->rot[i].y = 0.0f;
        self->rot[i].z = 0.0f;
        self->scale[i].x = 1.0f;
        self->scale[i].y = 1.0f;
        self->scale[i].z = 1.0f;
        self->alpha[i] = 1.0f;
    }
    self->weight = 1.0f;
    AnimState_Init(self, 0.0f);
}
