/*
 * TripleBladeRing_Draw (0x800B3C8C size:0x1AC) +
 * TripleBladeRing_DrawCb (0x800B3E38 size:0x9C)
 *
 * Draw path of the rotating 6-blade ring item effect. DrawCb computes a
 * camera-biased depth-sort position and registers Draw with the draw
 * manager; Draw renders 3 arms x 2 mirrored blades via cLNormal3DWrap.
 *
 * Both matched 100% (SHA-1 OK). Notes:
 * - lbl_805DF3D0+0x80 camera position: the two-step addi (lis/addi + addi
 *   0x80) reproduces from the plain `(TBRVec3 *)(lbl_805DF3D0 + 0x80)`
 *   byte-array read.
 * - lbl_806D5034 is declared `extern const float` (repo convention for
 *   sdata2 literal-pool floats), but Draw must RELOAD it at each call
 *   site inside the loop (target has no loop-invariant hoist). The
 *   `*(volatile float *)&lbl_806D5034` read into a local defeats the
 *   const hoist while keeping the lfs+fmr arg pattern.
 * - Draw GPR callee-saved webs follow decl order (fx, i, slot ->
 *   r30, r29, r28); m must be declared before xf for the stack layout
 *   (later decl = lower address).
 */

#include "game/TripleBladeRing.h"

/* callees */
extern void cLNormal3DWrap_Slot_SetRotationQuat(void *slot, float x, float y, float z, float w);
extern void cLNormal3DWrap_Slot_SetMatrixSource(void *slot, float *mtx3x4);
extern void cLNormal3DWrap_Slot_Render(void *slot);
extern void Matrix4_Identity(float *m);
extern void Matrix4_PreMultiplyTranslation(float x, float y, float z, float *dst, float *src);
extern void Matrix4_PreMultiplyRotZ(float angle, float *dst, float *src);
extern void Mtx44_Scale_Uniform(float scale, float *dst, float *src);
extern void Matrix4_Multiply(float *dst, float *a, float *b);
extern void DbgScene_CopyMatrix3x4Transpose(float *dst, float *src);
extern void Vec3_Subtract_DestFirst(TBRVec3 *dst, TBRVec3 *a, TBRVec3 *b);
extern float Vec3_Magnitude_Wrapper(TBRVec3 *v);
extern void Vec3_Scale(TBRVec3 *dst, const TBRVec3 *src, float scale);
extern void Vec3_Add_DestFirst(TBRVec3 *dst, TBRVec3 *a, TBRVec3 *b);
extern void clDrawMan_AddSorted_DepthRange(void *mgr, void (*fn)(TripleBladeRing *), TripleBladeRing *self,
                                           float x, float y, float z, float depth);

/* data */
extern unsigned char lbl_805DF3D0[0x98]; /* camera block; +0x80 = camera position Vec3 */
extern void *lbl_806D10AC;               /* draw manager instance */

/* sdata2 literal pool constants */
extern const float lbl_806D5028;
extern const float lbl_806D5034;
extern const float lbl_806D50BC;
extern const float lbl_806D511C;
extern const float lbl_806D5120;
extern const float lbl_806D5124;
extern const float lbl_806D5128;
extern const float lbl_806D512C;
extern const float lbl_806D5130;

void TripleBladeRing_Draw(TripleBladeRing *self)
{
    float m[16];
    float xf[12];
    TripleBladeRingFx *fx;
    int i;
    void *slot;
    float scale;
    float kv;
    DrawEffectActor *actor;

    actor = self->slotB;
    fx = (TripleBladeRingFx *)&self->slotA;
    if (actor != 0) {
        slot = actor->wrapSlot;
        cLNormal3DWrap_Slot_SetRotationQuat(slot, lbl_806D5028, lbl_806D5028, lbl_806D5028, self->angle);
        for (i = 0; i < 3; i++) {
            scale = lbl_806D50BC * fx->phases[i];
            Matrix4_Identity(m);
            kv = *(volatile float *)&lbl_806D5034;
            Matrix4_PreMultiplyTranslation(lbl_806D511C, kv, kv, m, m);
            Mtx44_Scale_Uniform(scale, m, m);
            Matrix4_PreMultiplyTranslation(lbl_806D5120, lbl_806D5124, lbl_806D5128, m, m);
            Matrix4_Multiply(m, m, fx->mtx);
            DbgScene_CopyMatrix3x4Transpose(xf, m);
            cLNormal3DWrap_Slot_SetMatrixSource(slot, xf);
            cLNormal3DWrap_Slot_Render(slot);

            Matrix4_Identity(m);
            kv = *(volatile float *)&lbl_806D5034;
            Matrix4_PreMultiplyTranslation(lbl_806D511C, kv, kv, m, m);
            Matrix4_PreMultiplyRotZ(lbl_806D512C, m, m);
            Mtx44_Scale_Uniform(scale, m, m);
            Matrix4_PreMultiplyTranslation(lbl_806D5130, lbl_806D5124, lbl_806D5128, m, m);
            Matrix4_Multiply(m, m, fx->mtx);
            DbgScene_CopyMatrix3x4Transpose(xf, m);
            cLNormal3DWrap_Slot_SetMatrixSource(slot, xf);
            cLNormal3DWrap_Slot_Render(slot);
        }
    }
}

void TripleBladeRing_DrawCb(TripleBladeRing *self)
{
    TBRVec3 pos;
    TBRVec3 tmp;
    void *mgr;
    float mag;

    Vec3_Subtract_DestFirst(&tmp, (TBRVec3 *)(lbl_805DF3D0 + 0x80), &self->pos);
    mag = Vec3_Magnitude_Wrapper(&tmp);
    Vec3_Scale(&tmp, &tmp, lbl_806D5028 / mag);
    Vec3_Add_DestFirst(&pos, &self->pos, &tmp);
    if ((mgr = lbl_806D10AC) == 0) {
        mgr = 0;
    }
    clDrawMan_AddSorted_DepthRange(mgr, TripleBladeRing_Draw, self, pos.x, pos.y, pos.z, lbl_806D5034);
}
