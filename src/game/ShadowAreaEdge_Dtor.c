extern void MemoryManager_TimedFree(void *);

#pragma exceptions on
void *ShadowAreaEdge_Dtor(void *self, short flag)
{
    if (self != 0 && flag > 0) {
        MemoryManager_TimedFree(self);
    }
    return self;
}
#pragma exceptions reset
