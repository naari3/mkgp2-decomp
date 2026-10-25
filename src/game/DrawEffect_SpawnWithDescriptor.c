#include "game/DrawEffectPool.h"

extern void *lbl_80419FB8[];  /* DrawEffect callback table by type */
extern void Vec3_Copy(DrawEffectVec3 *dst, const DrawEffectVec3 *src);

DrawEffect *DrawEffect_SpawnWithDescriptor(unsigned char type, const DrawEffectVec3 *pos)
{
    DrawEffect *e = DrawEffect_SpawnInline(lbl_80419FB8[type]);
    if (e != 0) {
        e->type = type;
    }
    if (e != 0) {
        Vec3_Copy(&e->pos, pos);
    }
    return e;
}
