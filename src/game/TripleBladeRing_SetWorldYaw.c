/*
 * TripleBladeRing_SetWorldYaw (0x800B3ED4 size:0x1C0) - NonMatching, 97.72%
 *
 * Per-frame pose setter: copies the kart world matrix into self->mtx,
 * stores the yaw, derives the world position, and advances the master
 * phase + sin phase + 3 staggered per-arm blade phases (wrap-normalize
 * against sdata2 limits, staggers from rodata lbl_803292D4).
 *
 * PARKED: fp-numbering tie-break family (see
 * docs/notes/cw132-fp-scratch-web-order-levers.md and
 * per_fn_matching_strategy.md sec 14.2 fp-scratch numbering family).
 * Instruction sequence, schedule, stack layout and instruction count are
 * byte-exact; the residual is ONLY fp scratch register naming:
 *   block1: target (5028=f0, lim134=f1, phase0tmp=f2) vs mine (f0, f2, f1)
 *   tail:   target (wk=f0, one=f1, amp=f2, limit=f3, stag=f4)
 *           vs mine (stag=f0, wk=f1, one=f2, amp=f3, limit=f4)
 * Probes tried (all allocation-invariant, 8 builds):
 *   - const init order permutations (limit/amp/one x2 orders)
 *   - decl order permutations (incl. stag first/last)
 *   - Vec3 struct copy vs float[3] array copy for the staggers
 *   - direct stag[i] reads vs single reused named local `s`
 *   - assign-in-condition for the block-1 limit
 *   - named local vs direct const for block-1 limit, before/after `+=`
 *   - explicit `x = x - k` vs compound `-=` in while bodies
 *     (the compound form IS load-bearing: it keeps the redundant
 *     re-load in the while body that the explicit form CSEs away)
 * If the fp-numbering family gets a lever later, this TU should
 * self-correct; flip Object() to Matching and verify.
 */

#include "game/TripleBladeRing.h"

extern void Mtx_TransposeToMtx44(float *dst, void *src);
extern void Mtx44_GetTranslation_ColMajor(TBRVec3 *dst, float *mtx44);
extern double fn_8027E9E8(double x); /* sin */

extern TBRVec3 lbl_803292D4; /* per-arm phase staggers (rodata, 3 floats) */

extern const float lbl_806D5028;
extern const float lbl_806D507C;
extern const float lbl_806D50FC;
extern const float lbl_806D5134;
extern const float lbl_806D5138;
extern const float lbl_806D513C;

void TripleBladeRing_SetWorldYaw(TripleBladeRing *self, float yaw, void *worldMtx)
{
    float one; /* reused as the block-1 wrap limit */
    float amp;
    float limit;
    float s;
    float stag[3];

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
        self->phaseSin = (float)fn_8027E9E8(lbl_806D5138 * self->phaseSin);

        *(TBRVec3 *)stag = lbl_803292D4;
        s = stag[0];
        limit = lbl_806D513C;
        amp = lbl_806D507C;
        one = lbl_806D5028;

        self->phases[0] = self->phase0 + s;
        while (limit < self->phases[0]) {
            self->phases[0] -= limit;
        }
        self->phases[0] = self->phases[0] / limit;
        self->phases[0] = amp * (one - self->phases[0]);

        s = stag[1];
        self->phases[1] = self->phase0 + s;
        while (limit < self->phases[1]) {
            self->phases[1] -= limit;
        }
        self->phases[1] = self->phases[1] / limit;
        self->phases[1] = amp * (one - self->phases[1]);

        s = stag[2];
        self->phases[2] = self->phase0 + s;
        while (limit < self->phases[2]) {
            self->phases[2] -= limit;
        }
        self->phases[2] = self->phases[2] / limit;
        self->phases[2] = amp * (one - self->phases[2]);
    }
}
