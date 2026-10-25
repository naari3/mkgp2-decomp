/* ItemObject_Tick_Kind2d_ChainShellPair (0x800E5FC0): chain shell (Wanwan)
 * with its two chain children. State 1 runs the hold/throw logic
 * (ItemObject_ChainShell_GrabAndArc_Sub); state 2 plays the ending picked
 * by the end code in 0xCB (orbit the bound kart, tether back, fall and fade
 * out). Every frame the children follow the parent's null joint, scaled by
 * a keyframe curve of the parent's animation. */
typedef struct Vec { float x, y, z; } Vec;

typedef struct ChainScaleKey {
    float t[4];
    float v[4];
} ChainScaleKey;

extern const char lbl_8032EA98[];
extern ChainScaleKey lbl_80421120[2];
extern void fn_800D748C(unsigned char *self);
extern unsigned char *ItemObject_AllocFromPool(void (*fn)(unsigned char *));
extern void SpriteSlot_InitNonLoop(void *slot, int animId);
extern void SpriteSlot_SetMatrixSourceEnabled_WithReseed(void *slot, int en);
extern void SpriteSlot_SetAnimFrameAndApplyScale(void *slot, int frame, float f);
extern void SpriteSlot_SetScale(void *slot, float s);
extern void SpriteSlot_SetTransform(void *slot, Vec pos, Vec rot, float scale);
extern void SpriteSlot_TickAnim(void *slot);
extern void SpriteSlot_Container_Free(void *self);
extern void ItemObject_DecrementCategoryBudget(unsigned char *self);
extern void ItemObject_ChainShell_GrabAndArc_Sub(unsigned char *self, unsigned char *sub);
extern void ItemObject_ChainShell_BoundOrbit_Sub(unsigned char *self, unsigned char *sub);
extern void GetSpawnPosition(Vec *out, float x, float y, float z);
extern signed char ItemObject_GetGroundTypeAt(Vec *pos, float *outGroundY, int mode);
extern float BuildOrientationFromYaw(float yaw);
extern void Vec3_Copy(Vec *dst, const Vec *src);
extern void Vec3_Subtract_DestFirst(Vec *out, const Vec *a, const Vec *b);
extern void Vec3_Add_DestFirst(Vec *out, const Vec *a, const Vec *b);
extern void Item_DecayVelocityScalar(unsigned char *self, float k);
extern int Item_AdvanceTetherToJoint13(unsigned char *self, float *tether, float scale, float a, float b);
extern int Item_OrbitAnchorKart(unsigned char *self, void *off, unsigned int t, float a, float b);
extern void JointByName_GetMatrix4x4Transposed(float dst[4][4], void *slot, const char *name);
extern void Matrix4_Identity(float m[4][4]);
extern void Mtx44_Scale_Uniform(float dst[4][4], float src[4][4], float s);
extern void Matrix4_Multiply(float a[4][4], float b[4][4], float out[4][4]);
extern void DbgScene_CopyMatrix3x4Transpose(void *dst, float src[4][4]);

#define F(o) (*(float *)(self + (o)))
#define S8(o) (*(signed char *)(self + (o)))
#define P(o) (*(unsigned char **)(self + (o)))
#define SF(o) (*(float *)(sub + (o)))
#define SU32(o) (*(unsigned int *)(sub + (o)))
#define CP(o) (*(unsigned char **)(c + (o)))

static inline void Timer_Tick(unsigned int *t)
{
    if (*t != 0) {
        (*t)--;
    }
}

static inline void ChainShell_FallAndFade(unsigned char *self, unsigned char *sub)
{
    Vec ground;
    Vec probe;
    float groundY;

    switch (S8(0xC9)) {
    case 0:
        ground = *(Vec *)(self + 0xA0);
        ItemObject_GetGroundTypeAt(&ground, (float *)(sub + 0x14), 0);
        if ((int)self[0xCB] != 5) {
            SU32(0x4) = 10;
        } else {
            SU32(0x4) = 0;
        }
        S8(0xC9)++;
    case 1:
        break;
    }
    if (SU32(0x4) == 0) {
        F(0x2C) -= 0.05f;
        if (F(0x2C) < 0.0f) {
            self[0x28] = 0;
            S8(0xC8) = 3;
            S8(0xC9) = 0;
            return;
        }
    }
    Item_DecayVelocityScalar(self, 1.0f);
    if ((int)self[0xCB] == 5) {
        return;
    }
    probe = *(Vec *)(self + 0xA0);
    if (ItemObject_GetGroundTypeAt(&probe, &groundY, 0)) {
        F(0xA4) = F(0xA4) + (groundY - SF(0x14));
        SF(0x14) = groundY;
    }
    F(0xBC) += -0.1f;
    switch (S8(0xCB)) {
    case 4:
        F(0xAC) = BuildOrientationFromYaw(F(0xAC) - 0.052359864f);
        break;
    case 9:
        F(0xAC) = BuildOrientationFromYaw(0.052359864f + F(0xAC));
        break;
    }
}

void ItemObject_Tick_Kind2d_ChainShellPair(unsigned char *self)
{
    float m[4][4];
    float s44[4][4];
    unsigned char *sub = self + 0xEC;
    unsigned char *c;
    ChainScaleKey *k;
    float s;
    int i;
    int j;

    switch (S8(0xC8)) {
    case 0:
        SpriteSlot_InitNonLoop(self + 0x14, 0x2D);
        self[0x14] = 4;
        {
        unsigned char *c;
        c = sub;
        for (i = 0; i < 2; i++) {
            CP(0x5C) = ItemObject_AllocFromPool(fn_800D748C);
            if (CP(0x5C) != 0) {
                if (i == 0) {
                    SpriteSlot_InitNonLoop(CP(0x5C) + 0x14, 0x2E);
                } else {
                    SpriteSlot_InitNonLoop(CP(0x5C) + 0x14, 0x2F);
                }
                CP(0x5C)[0x14] = 4;
                SpriteSlot_SetMatrixSourceEnabled_WithReseed(CP(0x5C) + 0x14, 1);
                CP(0x5C)[0x28] = 0;
            }
            c += 4;
        }
        }
        self[0x8C] = 3;
        self[0x8D] = 0;
        S8(0xC8) = 1;
        S8(0xC9) = 0;
    case 1:
        ItemObject_ChainShell_GrabAndArc_Sub(self, sub);
        break;
    case 2:
        switch (S8(0xCB)) {
        case 0:
            ItemObject_ChainShell_BoundOrbit_Sub(self, sub);
            break;
        case 3:
            switch (S8(0xC9)) {
            case 0:
                GetSpawnPosition((Vec *)(self + 0xB8), 0.0f, 0.0f, 0.0f);
                self[0x3C] = 0;
                SpriteSlot_SetAnimFrameAndApplyScale(self + 0x14, 3, 0.0f);
                SpriteSlot_SetScale(self + 0x14, 1.0f);
                SF(0x14) = 0.0f;
                SF(0x18) = F(0xC4);
                S8(0xC9)++;
            case 1:
                break;
            }
            if (Item_AdvanceTetherToJoint13(self, (float *)(sub + 0x14), SF(0x18), 0.08726645f, 0.08726645f) != 0) {
                self[0x28] = 0;
                S8(0xC8) = 3;
                S8(0xC9) = 0;
            }
            break;
        case 4:
            ChainShell_FallAndFade(self, sub);
            break;
        case 6:
            switch (S8(0xC9)) {
            case 0:
                GetSpawnPosition((Vec *)(self + 0xB8), 0.0f, 0.0f, 0.0f);
                self[0x3C] = 0;
                SpriteSlot_SetAnimFrameAndApplyScale(self + 0x14, 3, 0.0f);
                SpriteSlot_SetScale(self + 0x14, 1.0f);
                Vec3_Subtract_DestFirst((Vec *)(sub + 0x34), (Vec *)(self + 0xA0), (Vec *)(P(0x9C) + 0xA0));
                SU32(0x4) = 30;
                S8(0xC9)++;
            case 1:
                break;
            }
            Item_DecayVelocityScalar(self, 1.0f);
            if (Item_OrbitAnchorKart(self, sub + 0x34, SU32(0x4), 0.52359867f, 0.2617993f) != 0) {
                self[0x28] = 0;
                S8(0xC8) = 3;
                S8(0xC9) = 0;
            }
            break;
        case 9:
            ChainShell_FallAndFade(self, sub);
            break;
        case 5:
            ChainShell_FallAndFade(self, sub);
            break;
        }
        break;
    case 3:
        c = sub;
        for (i = 0; i < 2; i++) {
            SpriteSlot_Container_Free(CP(0x5C));
            CP(0x5C) = 0;
            c += 4;
        }
        ItemObject_DecrementCategoryBudget(self);
        SpriteSlot_Container_Free(self);
        return;
    }

    Vec3_Add_DestFirst((Vec *)(self + 0xA0), (Vec *)(self + 0xA0), (Vec *)(self + 0xB8));
    SpriteSlot_SetTransform(self + 0x14, *(Vec *)(self + 0xA0), *(Vec *)(self + 0xAC), F(0xC4));
    SpriteSlot_TickAnim(self + 0x14);
    JointByName_GetMatrix4x4Transposed(m, self + 0x14, lbl_8032EA98);
    c = sub;
    for (i = 0; i < 2; i++) {
        if (CP(0x5C) != 0) {
            CP(0x5C)[0x28] = self[0x28];
            if (*(signed char *)(CP(0x5C) + 0x28)) {
                k = &lbl_80421120[i];
                s = 1.0f;
                switch (S8(0x1D)) {
                case 0:
                case 1:
                    s = k->v[0];
                    break;
                case 2:
                    if (F(0x20) <= k->t[0]) {
                        s = k->v[0];
                    } else if (k->t[3] <= F(0x20)) {
                        s = k->v[3];
                    } else {
                        for (j = 0; j < 3; j++) {
                            if (k->t[j] <= F(0x20) && F(0x20) <= k->t[j + 1]) {
                                s = (F(0x20) - k->t[j]) * ((k->v[j + 1] - k->v[j]) / (k->t[j + 1] - k->t[j])) + k->v[j];
                            }
                        }
                    }
                    break;
                default:
                    s = k->v[3];
                    break;
                }
                s *= 1.2f;
                Matrix4_Identity(s44);
                Mtx44_Scale_Uniform(s44, s44, s);
                Matrix4_Multiply(s44, s44, m);
                DbgScene_CopyMatrix3x4Transpose(CP(0x5C) + 0x48, s44);
                Vec3_Copy((Vec *)(CP(0x5C) + 0xA0), (Vec *)(self + 0xA0));
                *(float *)(CP(0x5C) + 0xC4) = F(0xC4);
                *(float *)(CP(0x5C) + 0x2C) = F(0x2C);
                SpriteSlot_TickAnim(CP(0x5C) + 0x14);
            }
        }
        c += 4;
    }
    Timer_Tick((unsigned int *)(sub + 0x4));
    Timer_Tick((unsigned int *)(sub + 0x8));
    Timer_Tick((unsigned int *)(sub + 0xC));
    Timer_Tick((unsigned int *)(sub + 0x10));
}
