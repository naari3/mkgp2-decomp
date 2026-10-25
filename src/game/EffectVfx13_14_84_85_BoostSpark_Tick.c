/* EffectVfx13_14_84_85_BoostSpark_Tick (0x800BE8E4): boost spark (resources
 * 0x13/0x14, or 0x84/0x85 for the type-4 variant) thrown from a wheel
 * joint. Sparks burst out, slow down, drop and fade. */
#include "game/DrawEffectAccess.h"

extern int Rand_RangeIntMax(int max);
extern float Mtx44_GetYawOfPosZ(float m[4][4]);
extern float Vec3_ToYaw(const Vec *v);
extern void Mtx44_TransformVec3(Vec *out, float m[4][4], Vec *in);
extern void Mtx44_GetTranslation_ColMajor(Vec *out, float m[4][4]);

void EffectVfx13_14_84_85_BoostSpark_Tick(unsigned char *self)
{
    float root[4][4];
    Vec joint;
    Vec trans;
    Vec dir;
    Vec local;
    Vec pos;

    if (!S8(0x191)) {
        if (I(0x10) == 0) {
            Mtx44_GetTranslation_RowMajor(&joint, KartDriver_GetJointByIdx(P(0x11C), 6));
        } else {
            Mtx44_GetTranslation_RowMajor(&joint, KartDriver_GetJointByIdx(P(0x11C), 7));
        }
    } else {
        if (I(0x10) == 0) {
            Mtx44_GetTranslation_RowMajor(&joint, KartDriver_GetJointByIdx(P(0x11C), 2));
        } else {
            Mtx44_GetTranslation_RowMajor(&joint, KartDriver_GetJointByIdx(P(0x11C), 3));
        }
    }

    switch (STATE) {
    case 0: {
        float yaw;

        if ((int)U8(0x190) == 4) {
            if (Rand_RangeIntMax(0x10) % 2 != 0) {
                VfxSlot_BindResourceEx(SLOT(self), 0x84, 0);
            } else {
                VfxSlot_BindResourceEx(SLOT(self), 0x85, 0);
            }
        } else {
            if (Rand_RangeIntMax(0x10) % 2 != 0) {
                VfxSlot_BindResourceEx(SLOT(self), 0x14, 0);
            } else {
                VfxSlot_BindResourceEx(SLOT(self), 0x13, 0);
            }
        }
        if ((int)U8(0x190) == 4) {
            F(0x2C) = 1.0f;
        } else {
            F(0x2C) = 0.8f;
        }
        F(0x150) = Rand_RangeFloat(0.6f, 1.4f);
        F(0x154) = 1.0f;
        switch ((int)U8(0x1C)) {
        case 0x84:
            F(0x150) *= 0.4f;
            break;
        case 0x85:
            F(0x150) *= 0.4f;
            break;
        case 0x14:
            F(0x150) *= 0.4f;
            break;
        case 0x13:
            F(0x150) *= 0.1f;
            break;
        }
        Mtx_TransposeToMtx44(root, KartDriver_GetKartRootMtx(P(0x11C)));
        Mtx44_GetTranslation_ColMajor(&trans, root);
        yaw = Mtx44_GetYawOfPosZ(root);
        if ((int)U8(0x190) == 4) {
            if (!S8(0x191)) {
                GetSpawnPosition(&dir, 0.0f, 0.0f, Rand_RangeFloat(1.0f, 1.5f));
                Vec2_RotateX(&dir, &dir, 0.017453292f * Rand_RangeFloat(-60.0f, -45.0f));
                Vec2_RotateY(&dir, &dir, 0.017453292f * (180.0f + Rand_RangeFloat(-20.0f, 20.0f)));
            } else {
                GetSpawnPosition(&dir, 0.0f, 0.0f, Rand_RangeFloat(1.5f, 2.0f));
                Vec2_RotateX(&dir, &dir, 0.017453292f * Rand_RangeFloat(-45.0f, -20.0f));
                Vec2_RotateY(&dir, &dir, 0.017453292f * (180.0f + Rand_RangeFloat(-20.0f, 20.0f)));
            }
        } else {
            float rel = BuildOrientationFromYaw(Vec3_ToYaw(V(0xA4)) - yaw);
            GetSpawnPosition(&dir, 0.0f, 0.0f, Rand_RangeFloat(0.7f, 1.3f));
            Vec2_RotateX(&dir, &dir, 0.017453292f * Rand_RangeFloat(-50.0f, -45.0f));
            Vec2_RotateY(&dir, &dir, rel);
            Vec2_RotateY(&dir, &dir, 0.017453292f * (180.0f + Rand_RangeFloat(-15.0f, 15.0f)));
        }
        local = dir;
        Mtx44_TransformVec3(&dir, root, &local);
        Vec3_Subtract_DestFirst(V(0xA4), &dir, &trans);
        F(0x120) = Rand_RangeFloat(-2.0f, 2.0f);
        F(0x124) = Rand_RangeFloat(-2.0f, 2.0f);
        F(0x128) = Rand_RangeFloat(-2.0f, 2.0f);
        U32(0x180) = 0;
        Vec3_Scale(V(0xA4), V(0xA4), 0.2f);
        F(0xA0) = 0.017453292f * Rand_RangeFloat(-180.0f, 180.0f);
        F(0x158) = 0.017453292f * Rand_RangeFloat(-10.0f, 10.0f);
        STATE++;
    }
    case 1:
        if (U32(0x180) == 0) {
            Vec3_Scale(V(0xA4), V(0xA4), 5.0f);
            U32(0x180) = 5;
            STATE++;
        }
        break;
    case 2:
        if ((int)U8(0x190) == 4) {
            F(0xA8) -= 0.07f;
        } else {
            F(0xA8) -= 0.11f;
        }
        if (U32(0x180) == 0) {
            F(0x154) -= 0.34f;
            if (F(0x154) < 0.0f) {
                DrawEffect_Free(self);
                return;
            }
        }
        break;
    }

    Vec3_Add_DestFirst(V(0x120), V(0x120), V(0xA4));
    Vec3_Add_DestFirst(V(0x8C), &joint, V(0x120));
    F(0xA0) = BuildOrientationFromYaw(F(0xA0) + F(0x158));
    F(0xB0) = F(0x150) * F(0x154);
    pos = *V(0x8C);
    VfxSlot_SetPositionFromVec(SLOT(self), &pos);
    VfxSlot_SetRotationZ(SLOT(self), F(0xA0));
    VfxSlot_SetScaleUniform(SLOT(self), F(0xB0));
    TICK_TIMERS();
    if (FinalLapCoinJump_CheckActiveForObject(P(0x11C))) {
        U8(0x28) = 0;
    } else {
        U8(0x28) = 1;
    }
}
