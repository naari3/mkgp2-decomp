extern const float lbl_806D27F8;
extern const float lbl_806D27FC;

typedef struct ImpactMtx {
    float m[4][4];
} ImpactMtx;

typedef struct ItemEffectImpact {
    void **vtbl;
    void *owner;
    float v8[3];
    ImpactMtx a;
    ImpactMtx b;
    ImpactMtx c;
    int timer;
    float vd8[3];
    float te4;
    int flags;
} ItemEffectImpact;

static inline void ImpactMtx_Identity(ImpactMtx *m, float zero, float one)
{
    int i;
    int j;

    for (i = 0; i < 4; i++) {
        for (j = 0; j < 4; j++) {
            m->m[i][j] = zero;
        }
    }
    m->m[3][3] = one;
    m->m[2][2] = one;
    m->m[1][1] = one;
    m->m[0][0] = one;
}

/* 0x8005453C: reset the impact effect state. */
void ItemEffectImpact_Init(ItemEffectImpact *self)
{
    float one = lbl_806D27FC;
    float zero = lbl_806D27F8;

    self->v8[0] = zero;
    self->v8[1] = zero;
    self->v8[2] = zero;
    ImpactMtx_Identity(&self->a, zero, one);
    ImpactMtx_Identity(&self->b, zero, one);
    ImpactMtx_Identity(&self->c, zero, one);
    self->vd8[0] = zero;
    self->vd8[1] = zero;
    self->vd8[2] = zero;
    self->timer = 0;
    self->te4 = zero;
    self->flags = 0;
}
