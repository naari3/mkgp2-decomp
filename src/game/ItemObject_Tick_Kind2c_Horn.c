/* ItemObject_Tick_Kind2c_Horn (0x800E4F18): horn held in the character's
 * hand. It fades in and out with the hold state, hits drivers in range and
 * spawns a blast trail when triggered, and scales its two bell joints along
 * keyframe curves while the second animation plays. */
typedef struct Vec { float x, y, z; } Vec;
typedef struct { float v[3]; } FloatTriple;
typedef struct { float v[6]; } FloatSix;
typedef struct { unsigned char b[0x1EC]; } ItemObjectCopy;

typedef struct ScaleKey {
    float t[5];
    float v[5];
} ScaleKey;

extern const unsigned char lbl_8032E648[];
extern ScaleKey lbl_80421030[2][3];
extern void SpriteSlot_InitNonLoop(void *slot, int animId);
extern void SpriteSlot_SetMatrixSourceEnabled_WithReseed(void *slot, int en);
extern void SpriteSlot_SetAnimFrameAndApplyScale(void *slot, int frame, float f);
extern void SpriteSlot_SetScale(void *slot, float s);
extern void SpriteSlot_SetJointScaleByName(void *slot, const unsigned char *name, float x, float y, float z);
extern void SpriteSlot_Container_Free(void *self);
extern void ItemObject_DecrementCategoryBudget(unsigned char *self);
extern void Item_RenderCharacterScaledFromJoint12(unsigned char *self, FloatTriple *a, FloatTriple *b, int c, float d);
extern void *memset(void *dst, int c, unsigned long n);
extern void Vec3_Copy(Vec *dst, const Vec *src);
extern void Item_PropagateHitToDriversInRadius(void *item, void *driver);
extern unsigned char *DrawEffect_SpawnDirect(void (*callback)(unsigned char *));
extern void Effect_KartTrailRes3A_Update(unsigned char *self);
extern void SoundMgr_PlaySE_Positional(int se, Vec *pos, int ch);
extern unsigned char FinalLapCoinJump_CheckActiveForObject(void *driver);

static inline void ScaleKey_Eval(ScaleKey *k, float x, float *out)
{
    int j;

    for (j = 0; j < 4; j++) {
        if (k->t[j] <= x && x < k->t[j + 1]) {
            *out = (x - k->t[j]) * ((k->v[j + 1] - k->v[j]) / (k->t[j + 1] - k->t[j])) + k->v[j];
        }
    }
}

#define F(o) (*(float *)(self + (o)))
#define S8(o) (*(signed char *)(self + (o)))
#define P(o) (*(unsigned char **)(self + (o)))

void ItemObject_Tick_Kind2c_Horn(unsigned char *self)
{
    ItemObjectCopy hit;
    FloatSix scale;
    Vec pos;
    FloatTriple a;
    FloatTriple b;
    Vec sePos;
    const unsigned char *base = lbl_8032E648;
    unsigned char *e;
    float *out;
    ScaleKey *k;
    float x;
    int i;
    int n;

    switch (S8(0xC8)) {
    case 0:
        SpriteSlot_InitNonLoop(self + 0x14, 0x2C);
        SpriteSlot_SetMatrixSourceEnabled_WithReseed(self + 0x14, 1);
        SpriteSlot_SetAnimFrameAndApplyScale(self + 0x14, 0, 0.0f);
        SpriteSlot_SetScale(self + 0x14, 1.0f);
        F(0x2C) = 0.0f;
        S8(0xC8) = 1;
        S8(0xC9) = 0;
    case 1:
        break;
    }

    switch (S8(0x18C)) {
    case 0:
        F(0x2C) += 0.1f;
        if (1.0f < F(0x2C)) {
            F(0x2C) = 1.0f;
        }
        break;
    case 1:
        F(0x2C) -= 0.02f;
        if (F(0x2C) < 0.0f) {
            ItemObject_DecrementCategoryBudget(self);
            SpriteSlot_Container_Free(self);
            return;
        }
        break;
    case 2:
        ItemObject_DecrementCategoryBudget(self);
        SpriteSlot_Container_Free(self);
        return;
    }

    b = *(const FloatTriple *)(base + 0x408);
    a = *(const FloatTriple *)(base + 0x3FC);
    Item_RenderCharacterScaledFromJoint12(self, &a, &b, 0, 1.3f);
    if (self[0xEC] != 0) {
        Vec3_Copy(&pos, (Vec *)(self + 0xA0));
        SpriteSlot_SetAnimFrameAndApplyScale(self + 0x14, 1, 0.0f);
        SpriteSlot_SetScale(self + 0x14, 1.0f);
        memset(&hit, 0, sizeof(ItemObjectCopy));
        *(int *)(hit.b + 0x8) = 0x2C;
        hit.b[0x1C] = 0x9B;
        *(void **)(hit.b + 0x184) = P(0x184);
        Vec3_Copy((Vec *)(hit.b + 0xA0), &pos);
        *(float *)(hit.b + 0xC4) = 200.0f;
        Item_PropagateHitToDriversInRadius(&hit, P(0x184));
        e = DrawEffect_SpawnDirect(Effect_KartTrailRes3A_Update);
        if (e != 0) {
            Vec3_Copy((Vec *)(e + 0x8C), &pos);
            *(void **)(e + 0x11C) = P(0x184);
            Effect_KartTrailRes3A_Update(e);
        }
        sePos = *(Vec *)(self + 0xA0);
        SoundMgr_PlaySE_Positional(0x8D, &sePos, 0);
        self[0xEC] = 0;
    }
    if ((int)self[0x1D] == 1 && (int)self[0x1E] == 1) {
        SpriteSlot_SetAnimFrameAndApplyScale(self + 0x14, 0, 0.0f);
        SpriteSlot_SetScale(self + 0x14, 1.0f);
    }
    if ((int)self[0x1D] == 1) {
        scale = *(const FloatSix *)(base + 0x414);
        x = F(0x20);
        for (n = 0; n < 2; n++) {
            k = lbl_80421030[n];
            out = &scale.v[n * 3];
            for (i = 0; i < 3; i++) {
                ScaleKey_Eval(&k[i], x, &out[i]);

            }
        }
        SpriteSlot_SetJointScaleByName(self + 0x14, base + 0x42C, scale.v[0], scale.v[1], scale.v[2]);
        SpriteSlot_SetJointScaleByName(self + 0x14, base + 0x43C, scale.v[3], scale.v[4], scale.v[5]);
    }
    if (FinalLapCoinJump_CheckActiveForObject(P(0x184))) {
        self[0x28] = 0;
    } else {
        self[0x28] = 1;
    }
}
