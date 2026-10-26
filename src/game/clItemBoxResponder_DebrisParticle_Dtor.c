/* Debris particle deleting destructor. */
typedef struct DebrisParticle {
    unsigned char pad00[0x1c];
    float life; /* 0x1C */
} DebrisParticle;

extern const float lbl_806D29A8;
extern void MemoryManager_TimedFree(void *p);

DebrisParticle *clItemBoxResponder_DebrisParticle_Dtor(DebrisParticle *self, short flag)
{
    if (self != 0) {
        self->life = lbl_806D29A8;
        if (flag > 0) {
            MemoryManager_TimedFree(self);
        }
    }
    return self;
}
