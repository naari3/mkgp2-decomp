extern void KartItem_SetCarObjectField2d4Float(void *car, float value);
extern void *CarObject_GetRenderObj(void *car);
extern void ItemEffectBus_ClearMask(void *bus, unsigned long long mask);
extern const float lbl_806D27F8;
extern const float lbl_806D27FC;
extern const float lbl_806D2800;

typedef struct KeyframeMtx {
    float m[4][4];
} KeyframeMtx;

typedef struct KeyframeOwner {
    unsigned char *car;
} KeyframeOwner;

typedef struct ItemStateKeyframe {
    void **vtbl;
    KeyframeOwner *owner;
    float v8[3];
    unsigned char pad_14[8];
    KeyframeMtx a;
    KeyframeMtx b;
    int timer;
    int armed;
} ItemStateKeyframe;

static inline void KeyframeMtx_Identity(KeyframeMtx *m, float zero, float one)
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

/* 0x80053168: reset the keyframe buffers and arm the owner's car. */
void ItemState_InitKeyframeBufferAndArm(ItemStateKeyframe *self)
{
    float one = lbl_806D27FC;
    float zero = lbl_806D27F8;

    self->v8[0] = zero;
    self->v8[1] = zero;
    self->v8[2] = zero;
    KeyframeMtx_Identity(&self->a, zero, one);
    KeyframeMtx_Identity(&self->b, zero, one);
    self->timer = 0;
    KartItem_SetCarObjectField2d4Float(self->owner->car, lbl_806D2800);
    self->owner->car[0xD4] = 1;
    ItemEffectBus_ClearMask(*(void **)((char *)CarObject_GetRenderObj(self->owner->car) + 0x304), 0x20000000000ULL);
    self->armed = 0;
}
