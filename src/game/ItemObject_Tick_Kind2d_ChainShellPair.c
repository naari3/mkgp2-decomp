#include "game/ChainShellPairState.h"

/* ItemObject_Tick_Kind2d_ChainShellPair (0x800E5FC0): chain shell (Wanwan)
 * with its two chain children. State 1 runs the hold/throw logic
 * (ItemObject_ChainShell_GrabAndArc_Sub); state 2 plays the ending picked
 * by the end code in 0xCB (orbit the bound kart, tether back, fall and fade
 * out). Every frame the children follow the parent's null joint, scaled by
 * a keyframe curve of the parent's animation. */
#include "game/types/Vec.h"

#include "game/types/ChainScaleKey.h"

extern const char lbl_8032EA98[];
extern ChainScaleKey ItemObject_Tick_Kind2d_ChainShellPair_data_80421120[2];
extern void fn_800D748C(unsigned char *self);
extern unsigned char *ItemObject_AllocFromPool(void (*fn)(unsigned char *));
extern void SpriteSlot_InitNonLoop(void *slot, int animId);
extern void SpriteSlot_SetMatrixSourceEnabled_WithReseed(void *slot, int en);
extern void SpriteSlot_SetAnimFrameAndApplyScale(void *slot, int frame, float f);
extern void SpriteSlot_SetScale(void *slot, float s);
#ifdef __MWERKS__
extern void SpriteSlot_SetTransform(void *slot, Vec pos, Vec rot, float scale);
#else
/* The definition takes these structs by address; see docs/notes/port_abi.md. */
extern void SpriteSlot_SetTransform(void *, Vec *, Vec *, float);
static inline void SpriteSlot_SetTransform_ByValue(void *slot, Vec pos, Vec rot, float scale) { SpriteSlot_SetTransform(slot, &pos, &rot, scale); }
#define SpriteSlot_SetTransform SpriteSlot_SetTransform_ByValue
#endif
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
    ChainShellPairState *sub = (ChainShellPairState *)(self + 0xEC);
    ChainScaleKey *k;
    float s;
    int i;
    int j;

    switch (S8(0xC8)) {
    case 0:
        SpriteSlot_InitNonLoop(self + 0x14, 0x2D);
        self[0x14] = 4;
        for (i = 0; i < 2; i++) {
            sub->children[i] = ItemObject_AllocFromPool(fn_800D748C);
            if (sub->children[i] != 0) {
                if (i == 0) {
                    SpriteSlot_InitNonLoop(sub->children[i] + 0x14, 0x2E);
                } else {
                    SpriteSlot_InitNonLoop(sub->children[i] + 0x14, 0x2F);
                }
                sub->children[i][0x14] = 4;
                SpriteSlot_SetMatrixSourceEnabled_WithReseed(sub->children[i] + 0x14, 1);
                sub->children[i][0x28] = 0;
            }
        }
        self[0x8C] = 3;
        self[0x8D] = 0;
        S8(0xC8) = 1;
        S8(0xC9) = 0;
    case 1:
        ItemObject_ChainShell_GrabAndArc_Sub(self, (unsigned char *)sub);
        break;
    case 2:
        switch (S8(0xCB)) {
        case 0:
            ItemObject_ChainShell_BoundOrbit_Sub(self, (unsigned char *)sub);
            break;
        case 3:
            switch (S8(0xC9)) {
            case 0:
                GetSpawnPosition((Vec *)(self + 0xB8), 0.0f, 0.0f, 0.0f);
                self[0x3C] = 0;
                SpriteSlot_SetAnimFrameAndApplyScale(self + 0x14, 3, 0.0f);
                SpriteSlot_SetScale(self + 0x14, 1.0f);
                sub->groundY = 0.0f;
                sub->tetherScale = F(0xC4);
                S8(0xC9)++;
            case 1:
                break;
            }
            if (Item_AdvanceTetherToJoint13(self, &sub->groundY, sub->tetherScale, 0.08726645f, 0.08726645f) != 0) {
                self[0x28] = 0;
                S8(0xC8) = 3;
                S8(0xC9) = 0;
            }
            break;
        case 4:
            ChainShell_FallAndFade(self, (unsigned char *)sub);
            break;
        case 6:
            switch (S8(0xC9)) {
            case 0:
                GetSpawnPosition((Vec *)(self + 0xB8), 0.0f, 0.0f, 0.0f);
                self[0x3C] = 0;
                SpriteSlot_SetAnimFrameAndApplyScale(self + 0x14, 3, 0.0f);
                SpriteSlot_SetScale(self + 0x14, 1.0f);
                Vec3_Subtract_DestFirst((Vec *)sub->anchorOffset, (Vec *)(self + 0xA0), (Vec *)(P(0x9C) + 0xA0));
                sub->timers[0] = 30;
                S8(0xC9)++;
            case 1:
                break;
            }
            Item_DecayVelocityScalar(self, 1.0f);
            if (Item_OrbitAnchorKart(self, sub->anchorOffset, sub->timers[0], 0.52359867f, 0.2617993f) != 0) {
                self[0x28] = 0;
                S8(0xC8) = 3;
                S8(0xC9) = 0;
            }
            break;
        case 9:
            ChainShell_FallAndFade(self, (unsigned char *)sub);
            break;
        case 5:
            ChainShell_FallAndFade(self, (unsigned char *)sub);
            break;
        }
        break;
    case 3:
        for (i = 0; i < 2; i++) {
            SpriteSlot_Container_Free(sub->children[i]);
            sub->children[i] = 0;
        }
        ItemObject_DecrementCategoryBudget(self);
        SpriteSlot_Container_Free(self);
        return;
    }

    Vec3_Add_DestFirst((Vec *)(self + 0xA0), (Vec *)(self + 0xA0), (Vec *)(self + 0xB8));
    SpriteSlot_SetTransform(self + 0x14, *(Vec *)(self + 0xA0), *(Vec *)(self + 0xAC), F(0xC4));
    SpriteSlot_TickAnim(self + 0x14);
    JointByName_GetMatrix4x4Transposed(m, self + 0x14, lbl_8032EA98);
    for (i = 0; i < 2; i++) {
        if (sub->children[i] != 0) {
            sub->children[i][0x28] = self[0x28];
            if (*(signed char *)(sub->children[i] + 0x28)) {
                k = &ItemObject_Tick_Kind2d_ChainShellPair_data_80421120[i];
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
                DbgScene_CopyMatrix3x4Transpose(sub->children[i] + 0x48, s44);
                Vec3_Copy((Vec *)(sub->children[i] + 0xA0), (Vec *)(self + 0xA0));
                *(float *)(sub->children[i] + 0xC4) = F(0xC4);
                *(float *)(sub->children[i] + 0x2C) = F(0x2C);
                SpriteSlot_TickAnim(sub->children[i] + 0x14);
            }
        }
    }
    Timer_Tick(&sub->timers[0]);
    Timer_Tick(&sub->timers[1]);
    Timer_Tick(&sub->timers[2]);
    Timer_Tick(&sub->timers[3]);
}
