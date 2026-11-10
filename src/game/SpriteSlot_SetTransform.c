/* Sprite-slot vector setters pass their vectors by value. */
#include "game/types/Vec3.h"

#include "game/types/SpriteSlot.h"

extern void Object_SetJObjPositionXYZ(void *, float, float, float);
extern void JObj_SetRotationQuat(void *, float, float, float);
extern void Object_SetJObjScaleXYZ(void *, float, float, float);

static inline void position_xyz(void *joint, float x, float y, float z)
{
    if (joint) {
        Object_SetJObjPositionXYZ(joint, x, y, z);
    }
}

static inline void set_position(SpriteSlot *slot, Vec3 v)
{
    position_xyz(slot->object, v.x, v.y, v.z);
}

static inline void rotation_xyz(void *joint, float x, float y, float z)
{
    if (joint) {
        JObj_SetRotationQuat(joint, x, y, z);
    }
}

static inline void set_rotation(SpriteSlot *slot, Vec3 v)
{
    rotation_xyz(slot->object, v.x, v.y, v.z);
}

void SpriteSlot_SetTransform(SpriteSlot *slot, const Vec3 *position,
                             const Vec3 *rotation, float scale)
{
    set_position(slot, *position);
    set_rotation(slot, *rotation);
    if (slot->object) {
        Object_SetJObjScaleXYZ(slot->object, scale, scale, scale);
    }
}
