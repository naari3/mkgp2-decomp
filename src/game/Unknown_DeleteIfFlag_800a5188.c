extern void MemoryManager_TimedFree(void *);

#pragma exceptions on
void *Unknown_DeleteIfFlag_800a5188(void *self, short flag)
{
    if (self != 0 && flag > 0) {
        MemoryManager_TimedFree(self);
    }
    return self;
}
#pragma exceptions reset
