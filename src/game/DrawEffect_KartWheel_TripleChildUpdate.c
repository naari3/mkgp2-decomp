/* DrawEffect_KartWheel_TripleChildUpdate (0x800C2AAC): drives one wheel
 * effect and its three sub-children. The parent trails `pos` on a 0.1
 * leash, and each child sits on the parent-to-camera line, scaled per
 * resource type (I(0x10) = 0x5B..0x5D). Children 1 and 2 also cycle a
 * flicker phase. */
#include "game/DrawEffectAccess.h"

typedef struct { float v[3]; } ChildOffsets;

extern unsigned char lbl_805DF3D0[];
extern const ChildOffsets lbl_8032A76C;
extern double sin(double x);

#define CH (*(unsigned char **)(d + 0x10 + i * 4))
#define C(o) (*(float *)(CH + (o)))

void DrawEffect_KartWheel_TripleChildUpdate(unsigned char *self, Vec *pos, float scale, float alpha)
{
    Vec diff;
    Vec dir;
    ChildOffsets offs;
    Vec cpos;
    unsigned char *d;
    float len;
    float s1;
    float s2;
    float s3;
    float k;
    float t;
    float sn;
    float inv;
    float m;
    int i;

    if (self != 0) {
        d = self + 0xCC;
        Vec3_Subtract_DestFirst(&diff, V(0x8C), pos);
        len = Vec3_Magnitude_Wrapper(&diff);
        if (0.1f < len) {
            Vec3_Scale(&diff, &diff, 0.1f * (1.0f / len));
            Vec3_Add_DestFirst(V(0x8C), pos, &diff);
        }
        s1 = 0.5f * scale;
        F(0xB0) = scale;
        s2 = 0.6f * scale;
        s3 = 3.0f * scale;
        F(0x2C) = alpha;
        for (i = 0; i < 3; i++) {
            if (CH != 0) {
                C(0x2C) = alpha;
                switch (I(0x10)) {
                case 0:
                    *(float *)(CH + 0xB0) = scale;
                    break;
                case 0x5B:
                    *(float *)(CH + 0xB0) = s1;
                    break;
                case 0x5C:
                    *(float *)(CH + 0xB0) = s2;
                    break;
                case 0x5D:
                    *(float *)(CH + 0xB0) = s2;
                    break;
                }
                switch (I(0x10)) {
                case 0x5B:
                    k = 3.0f;
                    break;
                case 0x5C:
                    k = 10.0f;
                    break;
                case 0x5D:
                    k = 10.0f;
                    break;
                }
                offs = lbl_8032A76C;
                Vec3_Subtract_DestFirst(&dir, V(0x8C), (Vec *)(lbl_805DF3D0 + 0x80));
                len = Vec3_Magnitude_Wrapper(&dir);
                len = 1.0f / len;
                m = offs.v[i] * len;
                Vec3_Scale(&dir, &dir, k * (C(0xB0) * m));
                Vec3_Add_DestFirst(V_(CH, 0x8C), V(0x8C), &dir);
                if (i != 0) {
                    t = C(0x150);
                    t += 0.008333334f;
                    if (1.0f < t) {
                        t = 0.0f;
                        *(float *)(CH + 0xA0) =
                            0.017453292f * Rand_RangeFloat(-180.0f, 180.0f);
                    }
                    C(0x150) = t;
                    C(0x90) += s3 * t + -1.0f;
                    C(0xA0) = BuildOrientationFromYaw(0.006544983f + C(0xA0));
                    sn = sin(0.017453292f * (360.0f * t + 270.0f));
                    C(0x2C) = C(0x2C) * ((1.0f + sn) / 2.0f);
                }
                if (i != 0) {
                    *(float *)(CH + 0x2C) = 0.0f;
                }
                cpos = *V_(CH, 0x8C);
                VfxSlot_SetPositionFromVec(SLOT(CH), &cpos);
                VfxSlot_SetRotationZ(SLOT(CH), C(0xA0));
                VfxSlot_SetScaleUniform(SLOT(CH), C(0xB0));
                *(unsigned char *)(CH + 0x28) = 1;
            }
        }
    }
}
