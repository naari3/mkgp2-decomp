typedef struct SpriteSlot {
    unsigned char pad00[0x4];
    void *object; /* 0x04 */
} SpriteSlot;

typedef struct Vec3 {
    float x, y, z;
} Vec3;

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
