/*
 * ShadowBillboard matrix blend toward a target, 0x8006181C..0x80061918.
 */

typedef struct ShadowBillboard {
    unsigned char pad00[0x5C];
    float *mtx; /* 4x4 */
} ShadowBillboard;

extern const float lbl_806D2B88;
extern const float lbl_806D2B8C;
extern const float lbl_806D2B6C;
extern const float lbl_802EE4CC[];

float Saturate_Double(float v, float lo, float hi);
void Mtx34_Orthonormalize(float *mtx);

#pragma exceptions on

void ShadowBillboard_LerpMtx4x4(ShadowBillboard *sb, const float *target, float t)
{
    int i;
    int j;

    t = Saturate_Double(lbl_806D2B88 * t, lbl_806D2B8C, lbl_806D2B6C);
    for (i = 0; i < 3; i++) {
        for (j = 0; j < 3; j++) {
            sb->mtx[i * 4 + j] += t * (lbl_802EE4CC[i] * (target[i * 4 + j] - sb->mtx[i * 4 + j]));
        }
    }
    Mtx34_Orthonormalize(sb->mtx);
    sb->mtx[12] = target[12];
    sb->mtx[13] = target[13];
    sb->mtx[14] = target[14];
}

#pragma exceptions reset
