extern void MemoryManager_TimedFree(void *);
extern void __destroy_arr(void *arr, void *dtor, unsigned long size, unsigned long count);
extern void *ShadowAreaEdge_Dtor(void *, short);

#pragma exceptions on
void *dtor_800AA980(void *self, short flag)
{
    if (self != 0) {
        __destroy_arr((char *)self + 0x124, ShadowAreaEdge_Dtor, 0x18, 6);
        if (flag > 0) {
            MemoryManager_TimedFree(self);
        }
    }
    return self;
}
#pragma exceptions reset
