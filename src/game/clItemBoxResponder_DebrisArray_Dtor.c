/* Deleting destructor of the debris holder: destroys the 15 debris
 * particles of the owned block, frees the block, then frees itself when
 * flag > 0. */

typedef struct DebrisParticle {
    unsigned char data[0x2c];
} DebrisParticle;

typedef struct DebrisBlock {
    int header;
    DebrisParticle particles[15];
} DebrisBlock;

typedef struct DebrisArray {
    DebrisBlock *block;
} DebrisArray;

extern void MemoryManager_TimedFree(void *p);
extern void __destroy_arr(void *block, void *dtor, unsigned long size, unsigned long count);
extern void *clItemBoxResponder_DebrisParticle_Dtor(void *self, short flag);

DebrisArray *clItemBoxResponder_DebrisArray_Dtor(DebrisArray *self, short flag)
{
    if (self) {
        DebrisBlock *block = self->block;
        if (block) {
            __destroy_arr(block->particles, (void *)clItemBoxResponder_DebrisParticle_Dtor,
                          sizeof(DebrisParticle), 15);
            MemoryManager_TimedFree(block);
        }
        if (flag > 0) {
            MemoryManager_TimedFree(self);
        }
    }
    return self;
}
