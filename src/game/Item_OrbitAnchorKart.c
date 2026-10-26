/* Item_OrbitAnchorKart (0x800D9340): keeps an item orbiting its anchor
 * kart. The offset's height eases toward 50*r, its XZ radius toward a
 * height-dependent target, and it advances 0.314 rad per frame. Once the
 * anchor is gone (or `keep` is clear) the item fades out; returns 1 when
 * fully faded. */
#include "game/DrawEffectAccess.h"

extern const float lbl_806D5AB8; /* 1.0 */
extern const float lbl_806D5AC8; /* 0.0 */
extern const float lbl_806D5ACC; /* 0.5 */
extern const float lbl_806D5AD8; /* 50.0 */
extern const float lbl_806D5ADC; /* 10.0 */
extern const float lbl_806D5AE0; /* 40.0 */
extern const float lbl_806D5AE4; /* 0.314159 */
extern const float lbl_806D5AE8; /* 0.05 */
extern float FAbs_FloatAsDouble(float x);
extern float Vec3_HorizontalMagnitude(const Vec *v);
extern void Vec3_ScaleXZ(Vec *out, const Vec *in, float s);

int Item_OrbitAnchorKart(unsigned char *self, Vec *off, void *keep, float dYaw, float dPitch)
{
    unsigned char *anchor;
    int lost;

    if (self == 0) {
        return;
    }
    anchor = (unsigned char *)P(0x9C);
    if (anchor == 0 || off == 0) {
        lost = 1;
    } else {
        Vec tmp;
        float inner;
        float outer;
        float target;
        float h;
        float len;

        Vec3_Copy(&tmp, (Vec *)(anchor + 0xA0));
        h = lbl_806D5AD8 * *(float *)(anchor + 0xC4);
        {
            unsigned int gainOfs = 0x10C; /* fakematch: keeps the gain load order */
            inner = lbl_806D5ADC * *(float *)(anchor + 0xC4) * *(float *)(anchor + gainOfs);
            outer = lbl_806D5AE0 * *(float *)(anchor + 0xC4) * *(float *)(anchor + gainOfs);
        }
        if (FAbs_FloatAsDouble(h - off->y) < lbl_806D5AB8) {
            off->y = h;
        } else if (off->y < h) {
            off->y += lbl_806D5AB8;
        } else {
            off->y -= lbl_806D5AB8;
        }
        target = inner + off->y * ((outer - inner) / h);
        len = Vec3_HorizontalMagnitude(off);
        Vec3_ScaleXZ(off, off, lbl_806D5AB8 / len);
        if (FAbs_FloatAsDouble(target - len) < lbl_806D5ACC) {
            if (off && off && off) { /* fakematch (permuter): fixes block order */
            }
        } else if (len < target) {
            target = len + lbl_806D5ACC;
        } else {
            target = len - lbl_806D5ACC;
        }
        Vec3_ScaleXZ(off, off, target);
        Vec2_RotateY(off, off, lbl_806D5AE4);
        if ((int)*(unsigned char *)(anchor + 0xC8) == 2) {
            lost = 1;
        } else {
            lost = 0;
        }
    }
    if (lost || keep == 0) {
        F(0x2C) -= lbl_806D5AE8;
        if (F(0x2C) < 0.0f) {
            F(0x2C) = 0.0f;
            return 1;
        }
    }
    Vec3_Add_DestFirst(V(0xA0), (Vec *)((unsigned char *)P(0x9C) + 0xA0), off);
    F(0xAC) = BuildOrientationFromYaw(F(0xAC) + dYaw);
    F(0xB0) = BuildOrientationFromYaw(F(0xB0) + dPitch);
    return 0;
}
