/* Transform a world-space point into the kart's local frame with its x
 * component cleared, then back through the kart matrix. */

typedef struct Vec3 {
    float x, y, z;
} Vec3;

extern float *KartDriver_GetKartRootMtx(void *kart);
extern void Mtx44_Inverse_GaussJordan(float inv[4][4], float m[4][4]);
extern void Mtx44_TransformVec3(Vec3 *out, float m[4][4], Vec3 v);
extern void Mtx_TransposeToMtx44(float out[4][4], float *m);
extern void Vec3_Copy(Vec3 *dst, const Vec3 *src);

extern const float lbl_806D5AC8;

void KartDriver_TransformWorldToLocalY0(Vec3 *out, const Vec3 *world, void *kart)
{
    float m[4][4];
    float inv[4][4];
    Vec3 v;

    Vec3_Copy(&v, world);
    Mtx_TransposeToMtx44(m, KartDriver_GetKartRootMtx(kart));
    Mtx44_Inverse_GaussJordan(inv, m);
    Mtx44_TransformVec3(&v, inv, v);
    v.x = lbl_806D5AC8;
    Mtx44_TransformVec3(out, m, v);
}
