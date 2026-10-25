extern void KartItem_SetCarObjectField2d4Float(void *car, float value);
extern const float lbl_806D27F8;
extern const float lbl_806D27FC;
extern const float lbl_806D2800;

typedef struct JumpMtx {
    float m[4][4];
} JumpMtx;

typedef struct JumpOwner {
    unsigned char *car;
} JumpOwner;

typedef struct ItemEffectJump {
    void **vtbl;
    JumpOwner *owner;
    float v8[3];
    JumpMtx a;
    JumpMtx b;
    JumpMtx c;
    float vd4[3];
    int timer;
} ItemEffectJump;

static inline void JumpMtx_Identity(JumpMtx *m, float zero, float one)
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

/* 0x8005399C: reset the jump effect state. */
void ItemEffectJump_Init(ItemEffectJump *self)
{
    float one = lbl_806D27FC;
    float zero = lbl_806D27F8;

    self->v8[0] = zero;
    self->v8[1] = zero;
    self->v8[2] = zero;
    JumpMtx_Identity(&self->a, zero, one);
    JumpMtx_Identity(&self->b, zero, one);
    JumpMtx_Identity(&self->c, zero, one);
    self->vd4[0] = zero;
    self->vd4[1] = zero;
    self->vd4[2] = zero;
    self->timer = 0x22;
    KartItem_SetCarObjectField2d4Float(self->owner->car, lbl_806D2800);
}
