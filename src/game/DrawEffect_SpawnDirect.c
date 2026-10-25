#include "game/DrawEffectPool.h"

DrawEffect *DrawEffect_SpawnDirect(void *callback)
{
    return DrawEffect_SpawnInline(callback);
}
