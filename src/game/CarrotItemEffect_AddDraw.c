/* CarrotItemEffect_AddDraw: queue CarrotItemEffect_Render in the sorted draw
 * list at the camera-transformed anchor (same shape as
 * TwinSpriteOverlay_AddDraw). */
#include "game/types/Vec3.h"

#ifdef __MWERKS__
extern Vec3 Mtx44_TransformVec3(const float *m, Vec3 v);
#else
/* The definition takes these structs by address; see docs/notes/port_abi.md. */
extern void Mtx44_TransformVec3(Vec3 *, const float *, Vec3 *);
static inline Vec3 Mtx44_TransformVec3_ByValue(const float *m, Vec3 v) { Vec3 port_ret; Mtx44_TransformVec3(&port_ret, m, &v); return port_ret; }
#define Mtx44_TransformVec3 Mtx44_TransformVec3_ByValue
#endif
extern void clDrawMan_AddSorted_NoDepthBias(void *mgr, void (*fn)(char *), char *obj,
                                            float x, float y, float z, float bias);
extern void CarrotItemEffect_Render(char *self);

extern void *lbl_806D10AC;
extern const float lbl_806D5034;
extern Vec3 CarrotItemEffect_AddDraw_rodata_803293DC;
extern float lbl_805DF3D0[];

#pragma exceptions on

void CarrotItemEffect_AddDraw(char *self) {
    Vec3 p = CarrotItemEffect_AddDraw_rodata_803293DC;
    p = Mtx44_TransformVec3(lbl_805DF3D0, p);
    clDrawMan_AddSorted_NoDepthBias(lbl_806D10AC == 0 ? 0 : lbl_806D10AC,
                                    CarrotItemEffect_Render, self, p.x, p.y, p.z,
                                    lbl_806D5034);
}

#pragma exceptions reset
