/* DrawEffect_Cb_KartItemTrail_4Phase (0x800C8490): item trail sparkle
 * (resource 0x6D) with a colour per item type (I(0x10) = 0x65..0x67).
 * Phase 1 pulses outward, 2 scatters and fades, 3 is pulled into the
 * kart's joint 13 and 4 homes onto the tracked item at P(0xCC). FINISHED
 * picks the next phase. With S8(0x191) set, it also fades by distance from
 * the camera. */
#include "game/DrawEffectAccess.h"

typedef struct { float v[4]; } PeriodTable;

extern const PeriodTable lbl_8032A7D0;
extern unsigned char lbl_805DF3D0[];
extern void KartDriver_GetJoint13_WorldPos(Vec *out, void *driver);
extern int Item_AdvanceTrackedHomingState(void *item, Vec *offset, float k);
extern float fn_800D3184(const Vec *a, const Vec *b);

void DrawEffect_Cb_KartItemTrail_4Phase(unsigned char *self)
{
    PeriodTable periods;
    Vec joint;
    Vec pos;
    float d;

    switch (STATE) {
    case 0:
        VfxSlot_BindResourceEx(SLOT(self), 0x6D, 0);
        U8(0x14) = 1;
        switch (I(0x10)) {
        case 0x66:
            GetSpawnPosition(V(0x30), 0.7f, 0.3f, 1.0f);
            break;
        case 0x65:
            GetSpawnPosition(V(0x30), 1.0f, 0.3f, 0.5f);
            break;
        case 0x67:
            GetSpawnPosition(V(0x30), 1.0f, 0.8f, 0.0f);
            break;
        }
        F(0x150) = 0.0f;
        S8(0x191) = 1;
        S8(0x192) = 0;
        STATE++;
        S8(0xB5) = 0;
    case 1:
        switch (S8(0xB5)) {
        case 0:
            GetSpawnPosition(V(0x12C), Rand_RangeFloat(-1.0f, 1.0f), Rand_RangeFloat(-1.0f, 1.0f),
                             Rand_RangeFloat(-1.0f, 1.0f));
            Vec3_Scale(V(0x12C), V(0x12C), 16.0f);
            F(0x150) = 0.0f;
            F(0x154) = 8.0f * Rand_RangeFloat(0.7f, 1.3f);
            F(0x158) = 0.3f;
            periods = lbl_8032A7D0;
            if (S8(0x192) == 0) {
                F(0x15C) = 1.0f / (periods.v[S8(0x190)] + Rand_RangeFloat(-10.0f, 10.0f));
            } else {
                F(0x15C) = 1.0f / Rand_RangeFloat(70.0f, 80.0f);
            }
            F(0xA0) = 0.017453292f * Rand_RangeFloat(-180.0f, 180.0f);
            U32(0x180) = 90;
            S8(0x192) = 1;
            S8(0xB5)++;
        case 1:
            break;
        }
        switch (FINISHED) {
        case 1:
            DrawEffect_Free(self);
            return;
        case 2:
            STATE = 3;
            S8(0xB5) = 0;
            break;
        case 3:
            STATE = 4;
            S8(0xB5) = 0;
            break;
        }
        Vec3_Add_DestFirst(V(0x8C), V(0x120), V(0x12C));
        F(0x158) = F(0x158) + F(0x15C);
        F(0xB0) = F(0x154) * F(0x158);
        if (F(0x158) < 1.0f) {
            F(0x150) += 0.05f;
            if (1.0f < F(0x150)) {
                F(0x150) = 1.0f;
            }
        } else {
            F(0x150) = F(0x150) - 2.0f * F(0x15C);
            if (F(0x150) < 0.0f) {
                F(0x150) = 0.0f;
                S8(0xB5) = 0;
            }
        }
        break;
    case 2:
        switch (S8(0xB5)) {
        case 0:
            S8(0xB5)++;
        case 1:
            break;
        }
        F(0x150) -= 0.05f;
        if (F(0x150) < 0.0f) {
            DrawEffect_Free(self);
            return;
        }
        Vec3_Scale(V(0xA4), V(0xA4), 0.9f);
        Vec3_Add_DestFirst(V(0x8C), V(0x8C), V(0xA4));
        F(0x158) = 3.0f * F(0x15C) + F(0x158);
        F(0xB0) = F(0x154) * F(0x158);
        break;
    case 3:
        switch (S8(0xB5)) {
        case 0:
            GetSpawnPosition(V(0xA4), 0.0f, 0.0f, 0.0f);
            F(0x154) = 0.0f;
            F(0x158) = F(0xB0);
            F(0x15C) = 0.017453292f * Rand_RangeFloat(-5.0f, 5.0f);
            if (S8(0x190) == 0) {
                S8(0x191) = 0;
            }
            S8(0xB5)++;
        case 1:
            break;
        }
        F(0x154) += 0.04f;
        if (1.0f < F(0x154)) {
            DrawEffect_Free(self);
            return;
        }
        KartDriver_GetJoint13_WorldPos(&joint, P(0x11C));
        Vec3_Subtract_DestFirst(V(0xA4), &joint, V(0x8C));
        Vec3_Scale(V(0xA4), V(0xA4), F(0x154));
        Vec3_Add_DestFirst(V(0x8C), V(0x8C), V(0xA4));
        F(0xA0) = BuildOrientationFromYaw(F(0xA0) + F(0x15C));
        F(0xB0) = F(0x158) * (1.0f - F(0x154));
        F(0x150) += 0.03f;
        if (1.0f < F(0x150)) {
            F(0x150) = 1.0f;
        }
        break;
    case 4:
        switch (S8(0xB5)) {
        case 0:
            Vec3_Subtract_DestFirst(V(0x120), V(0x8C), V_(P(0xCC), 0xA0));
            U32(0x180) = 30;
            S8(0xB5)++;
        case 1:
            break;
        }
        if (Item_AdvanceTrackedHomingState(P(0xCC), V(0x120), 1.0f) == 1 || U32(0x180) == 0) {
            F(0x150) -= 0.05f;
            if (F(0x150) < 0.0f) {
                U8(0x28) = 0;
                DrawEffect_Free(self);
                return;
            }
        }
        Vec3_Add_DestFirst(V(0x8C), V_(P(0xCC), 0xA0), V(0x120));
        break;
    }

    if (S8(0x191)) {
        d = (fn_800D3184(V(0x8C), (Vec *)(lbl_805DF3D0 + 0x80)) - 40.0f) / 20.0f;
        if (1.0f < d) {
            d = 1.0f;
        }
        if (d < 0.0f) {
            d = 0.0f;
        }
        F(0x2C) = F(0x150) * d;
    } else {
        F(0x2C) = F(0x150);
    }
    pos = *V(0x8C);
    VfxSlot_SetPositionFromVec(SLOT(self), &pos);
    VfxSlot_SetRotationZ(SLOT(self), F(0xA0));
    VfxSlot_SetScaleUniform(SLOT(self), F(0xB0));
    TICK_TIMERS();
}
