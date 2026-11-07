/*
 * TripleBladeRing_SetWorldYaw (0x800B3ED4 size:0x1C0) - NonMatching, 98.71%
 *
 * Per-frame pose setter: copies the kart world matrix into self->mtx,
 * stores the yaw, derives the world position, and advances the master
 * phase + sin phase + 3 staggered per-arm blade phases (wrap-normalize
 * against sdata2 limits, staggers from rodata lbl_803292D4).
 *
 * NonMatching: FP scratch register identities differ from the target.
 * A counted three-arm loop is fully unrolled by CW 1.3.2 and places the
 * working value in f0, improving 97.72321% to 98.70536% (c19_u238).
 * Instruction order, count, stack layout, and EH remain exact.
 * Remaining differences:
 *   master: target phase=f2, wrap limit=f1; source phase=f1, limit=f2
 *   arms: target one=f1, amp=f2, limit=f3, stagger=f4;
 *         source stagger=f1, one=f2, amp=f3, limit=f4
 * Compound master assignments and a cached-argument inline arm helper
 * were allocation-invariant. Prior probes and compiler observations:
 * docs/notes/cw132-fp-scratch-web-order-levers.md and
 * docs/notes/cw132-const-float-hoist-vs-reload.md.
 */

#include "game/TripleBladeRing.h"

extern void Mtx_TransposeToMtx44(float *dst, void *src);
extern void Mtx44_GetTranslation_ColMajor(TBRVec3 *dst, float *mtx44);
extern double sin(double x); /* sin */

extern TBRVec3 lbl_803292D4; /* per-arm phase staggers (rodata, 3 floats) */

extern const float lbl_806D5028;
extern const float lbl_806D507C;
extern const float lbl_806D50FC;
extern const float lbl_806D5134;
extern const float lbl_806D5138;
extern const float lbl_806D513C;

void TripleBladeRing_SetWorldYaw(TripleBladeRing *self, float yaw, void *worldMtx)
{
    float one; /* also used as the master-phase wrap limit */
    float amp;
    float limit;
    float stag[3];
    int i;

    if (self != 0) {
        Mtx_TransposeToMtx44(self->mtx, worldMtx);
        self->angle = yaw;
        Mtx44_GetTranslation_ColMajor(&self->pos, self->mtx);

        self->phase0 = self->phase0 + lbl_806D5028;
        if ((one = lbl_806D5134) < self->phase0) {
            self->phase0 = self->phase0 - one;
        }

        self->phaseSin = self->phase0;
        while (lbl_806D50FC < self->phaseSin) {
            self->phaseSin -= lbl_806D50FC;
        }
        self->phaseSin = self->phaseSin / lbl_806D50FC;
        self->phaseSin = (float)sin(lbl_806D5138 * self->phaseSin);

        *(TBRVec3 *)stag = lbl_803292D4;
        limit = lbl_806D513C;
        amp = lbl_806D507C;
        one = lbl_806D5028;

        for (i = 0; i < 3; ++i) {
            self->phases[i] = self->phase0 + stag[i];
            while (limit < self->phases[i]) {
                self->phases[i] -= limit;
            }
            self->phases[i] = self->phases[i] / limit;
            self->phases[i] = amp * (one - self->phases[i]);
        }
    }
}
