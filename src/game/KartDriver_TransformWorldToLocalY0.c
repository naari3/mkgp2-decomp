/* Transform a world-space point into the kart's local frame with its x
 * component cleared, then back through the kart matrix. */

#include "game/types/Vec3.h"

extern float *KartDriver_GetKartRootMtx(void *kart);
extern void Mtx44_Inverse_GaussJordan(float inv[4][4], float m[4][4]);
#ifdef __MWERKS__
extern void Mtx44_TransformVec3(Vec3 *out, float m[4][4], Vec3 v);
#else
/* The definition takes these structs by address; see docs/notes/port_abi.md. */
extern void Mtx44_TransformVec3(Vec3 *, float m[4][4], Vec3 *);
static inline void Mtx44_TransformVec3_ByValue(Vec3 *out, float m[4][4], Vec3 v) { Mtx44_TransformVec3(out, m, &v); }
#define Mtx44_TransformVec3 Mtx44_TransformVec3_ByValue
#endif
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
