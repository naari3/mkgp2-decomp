/*
 * TripleBladeRing_SetWorldYaw (0x800B3ED4 size:0x1C0)
 *
 * Per-frame pose setter: copies the kart world matrix into self->mtx,
 * stores the yaw, derives the world position, and advances the master
 * phase + sin phase + 3 staggered per-arm blade phases (wrap-normalize
 * against sdata2 limits, staggers from rodata TripleBladeRing_SetWorldYaw_rodata_803292D4).
 *
 * The constants are read directly (no named locals) and the function is
 * built with opt_common_subs off: the target's FPR homes come from the
 * backend's constant temps, not from frontend CSE temps
 * (regalloc_patterns §29).
 */

#include "game/TripleBladeRing.h"

extern void Mtx_TransposeToMtx44(float *dst, void *src);
extern void Mtx44_GetTranslation_ColMajor(TBRVec3 *dst, float *mtx44);
extern double sin(double x); /* sin */

extern TBRVec3 TripleBladeRing_SetWorldYaw_rodata_803292D4; /* per-arm phase staggers (rodata, 3 floats) */

extern const float lbl_806D5028;
extern const float lbl_806D507C;
extern const float lbl_806D50FC;
extern const float lbl_806D5134;
extern const float lbl_806D5138;
extern const float lbl_806D513C;

#pragma opt_common_subs off
void TripleBladeRing_SetWorldYaw(TripleBladeRing *self, float yaw, void *worldMtx)
{
    float stag[3];
    int i;

    if (self != 0) {
        Mtx_TransposeToMtx44(self->mtx, worldMtx);
        self->angle = yaw;
        Mtx44_GetTranslation_ColMajor(&self->pos, self->mtx);

        self->phase0 = self->phase0 + lbl_806D5028;
        if (lbl_806D5134 < self->phase0) {
            self->phase0 = self->phase0 - lbl_806D5134;
        }

        self->phaseSin = self->phase0;
        while (lbl_806D50FC < self->phaseSin) {
            self->phaseSin -= lbl_806D50FC;
        }
        self->phaseSin = self->phaseSin / lbl_806D50FC;
        self->phaseSin = (float)sin(lbl_806D5138 * self->phaseSin);

        *(TBRVec3 *)stag = TripleBladeRing_SetWorldYaw_rodata_803292D4;

        for (i = 0; i < 3; ++i) {
            self->phases[i] = self->phase0 + stag[i];
            while (lbl_806D513C < self->phases[i]) {
                self->phases[i] -= lbl_806D513C;
            }
            self->phases[i] = self->phases[i] / lbl_806D513C;
            self->phases[i] = lbl_806D507C * (lbl_806D5028 - self->phases[i]);
        }
    }
}
#pragma opt_common_subs reset
