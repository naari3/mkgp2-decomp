#include "game/DrawEffectPool.h"

extern void *lbl_80419FB8[];  /* DrawEffect callback table by type */

DrawEffect *DrawEffect_SpawnByType(unsigned char type)
{
    DrawEffect *e = DrawEffect_SpawnInline(lbl_80419FB8[type]);
    if (e != 0) {
        e->type = type;
    }
    return e;
}
