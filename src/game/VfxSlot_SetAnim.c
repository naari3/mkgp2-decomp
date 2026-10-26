/* VfxSlot animation speed/frame setters; no-ops while the slot is unbound. */

typedef struct VfxSlot {
    unsigned char pad00[0x4];
    void *effect;          /* 0x04 */
    unsigned char pad08[0x2];
    unsigned char playing; /* 0x0A */
    unsigned char pad0B;
    float frame;           /* 0x0C */
    float speed;           /* 0x10 */
} VfxSlot;

void VfxSlot_SetAnimSpeed(VfxSlot *self, float speed)
{
    if (self->effect != 0) {
        self->speed = speed;
    }
}

void VfxSlot_SetAnimFrame(VfxSlot *self, float frame)
{
    if (self->effect != 0) {
        self->playing = 0;
        self->frame = frame;
    }
}
