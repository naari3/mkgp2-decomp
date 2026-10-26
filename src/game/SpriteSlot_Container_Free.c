/* Free the sprite slot embedded in a container and mark the container
 * unused. */
typedef struct SpriteSlot {
    unsigned char pad00[0x8];
} SpriteSlot;

typedef struct SpriteSlotContainer {
    unsigned char used;
    unsigned char pad01[0x13];
    SpriteSlot slot; /* 0x14 */
} SpriteSlotContainer;

extern void SpriteSlot_Destroy(SpriteSlot *slot);

void SpriteSlot_Container_Free(SpriteSlotContainer *self)
{
    if (self != 0) {
        if (self != 0) {
            SpriteSlot_Destroy(&self->slot);
            self->used = 0;
        }
    }
}
