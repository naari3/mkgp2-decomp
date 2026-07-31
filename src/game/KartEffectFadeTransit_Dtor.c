typedef struct KartEffectFadeTransit KartEffectFadeTransit;

extern void MemoryManager_TimedFree(void *ptr);

KartEffectFadeTransit *KartEffectFadeTransit_Dtor(
    KartEffectFadeTransit *self, short shouldFree)
{
    if (self != 0) {
        if (shouldFree > 0) {
            MemoryManager_TimedFree(self);
        }
    }
    return self;
}
