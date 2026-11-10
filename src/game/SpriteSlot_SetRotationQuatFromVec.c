#include "game/types/SpriteSlot.h"

#include "game/types/Vec3.h"

extern void JObj_SetRotationQuat(void *object, float x, float y, float z);

static inline void SpriteSlot_SetRotationQuatFromVec_Apply(void *object, float x, float y, float z)
{
    if (object != 0) {
        JObj_SetRotationQuat(object, x, y, z);
    }
}

void SpriteSlot_SetRotationQuatFromVec(SpriteSlot *self, const Vec3 *v)
{
    SpriteSlot_SetRotationQuatFromVec_Apply(self->object, v->x, v->y, v->z);
}
