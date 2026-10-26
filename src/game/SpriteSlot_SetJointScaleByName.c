/* Scale a named joint of the slot's object. */
typedef struct SpriteSlot {
    unsigned char pad00[0x4];
    void *object; /* 0x04 */
} SpriteSlot;

extern void *ResolveJointByName(void *object, const char *name);
extern void JObj_SetScale(void *object, void *jobj, float x, float y, float z);

void SpriteSlot_SetJointScaleByName(SpriteSlot *self, const char *name, float x, float y, float z)
{
    void *jobj;

    if (self != 0) {
        jobj = ResolveJointByName(self->object, name);
        if (jobj != 0) {
            JObj_SetScale(self->object, jobj, x, y, z);
        }
    }
}
