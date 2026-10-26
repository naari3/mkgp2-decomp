/* Destroy a sprite slot's object. */
typedef struct SpriteSlot {
    unsigned char pad00[0x4];
    void *object; /* 0x04 */
} SpriteSlot;

extern void Object_DtorWithGXSync(void *object, int del);

void SpriteSlot_Destroy(SpriteSlot *self)
{
    if (self->object != 0) {
        Object_DtorWithGXSync(self->object, 1);
        self->object = 0;
    }
}
