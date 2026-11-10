#include "game/types/SpriteSlot.h"

#include "game/types/Vec3.h"

extern void Object_SetJObjPositionXYZ(void *object, float x, float y, float z);

static inline void SpriteSlot_SetPositionFromVec_Apply(void *object, float x, float y, float z)
{
    if (object != 0) {
        Object_SetJObjPositionXYZ(object, x, y, z);
    }
}

void SpriteSlot_SetPositionFromVec(SpriteSlot *self, const Vec3 *v)
{
    SpriteSlot_SetPositionFromVec_Apply(self->object, v->x, v->y, v->z);
}
