extern void KartItem_SetCarObjectField2d4Float(void *car, float value);
extern const float lbl_806D27F8;
extern const float lbl_806D27FC;
extern const float lbl_806D2800;

typedef struct QuakeMtx {
    float m[4][4];
} QuakeMtx;

typedef struct QuakeOwner {
    unsigned char *car;
} QuakeOwner;

typedef struct ItemEffectQuake {
    void **vtbl;
    QuakeOwner *owner;
    float v8[3];
    unsigned char pad_14[4];
    float v18[3];
    QuakeMtx a;
    QuakeMtx b;
    int timer;
} ItemEffectQuake;

static inline void QuakeMtx_Identity(QuakeMtx *m, float zero, float one)
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

/* 0x80053C70: reset the quake effect and flag the owner's car. */
void ItemEffectQuake_Init(ItemEffectQuake *self)
{
    float one = lbl_806D27FC;
    float zero = lbl_806D27F8;

    self->v8[0] = zero;
    self->v8[1] = zero;
    self->v8[2] = zero;
    self->v18[0] = zero;
    self->v18[1] = zero;
    self->v18[2] = zero;
    QuakeMtx_Identity(&self->a, zero, one);
    QuakeMtx_Identity(&self->b, zero, one);
    self->timer = 0;
    KartItem_SetCarObjectField2d4Float(self->owner->car, lbl_806D2800);
    self->owner->car[0xD4] = 1;
}
