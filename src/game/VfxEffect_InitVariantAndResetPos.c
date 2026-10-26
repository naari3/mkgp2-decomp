/* Set a VfxEffect's variant byte and re-seed its position from the spawn
 * point. */
typedef struct VfxEffect {
    unsigned char pad00[0x10];
    int variant;             /* 0x10 */
    unsigned char pad14[0x1c];
    float pos[3];            /* 0x30 */
} VfxEffect;

extern void GetSpawnPosition(float *pos);

void VfxEffect_InitVariantAndResetPos(VfxEffect *self, unsigned char variant)
{
    if (self != 0) {
        self->variant = variant;
        GetSpawnPosition(self->pos);
    }
}
