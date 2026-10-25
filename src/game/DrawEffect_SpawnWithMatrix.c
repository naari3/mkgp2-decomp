#include "game/DrawEffectPool.h"

extern void *lbl_80419FB8[];  /* DrawEffect callback table by type */
extern void Mtx_TransposeToMtx44(float dst[4][4], const void *src);
extern void Mtx44_GetTranslation_ColMajor(DrawEffectVec3 *out, float m[4][4]);
extern void Mtx44_GetYawPitchOfPosZ(float m[4][4], float *pitch, float *yaw);

DrawEffect *DrawEffect_SpawnWithMatrix(unsigned char type, const void *mtx)
{
    float m[4][4];
    DrawEffect *e = DrawEffect_SpawnInline(lbl_80419FB8[type]);
    if (e != 0) {
        e->type = type;
    }
    if (e != 0) {
        Mtx_TransposeToMtx44(m, mtx);
        Mtx44_GetTranslation_ColMajor(&e->pos, m);
        Mtx44_GetYawPitchOfPosZ(m, (float *)((char *)e + 0x98), &e->yaw);
    }
    return e;
}
