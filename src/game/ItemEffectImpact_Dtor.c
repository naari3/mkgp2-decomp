extern void MemoryManager_TimedFree(void *p);

extern void *lbl_803F7738[];
extern void *lbl_803F7758[];

/* 0x800547D8: deleting destructor of the impact item effect. */
void **ItemEffectImpact_Dtor(void **self, short flag)
{
    if (self != 0) {
        *self = lbl_803F7758;
        if (self != 0) {
            *self = lbl_803F7738;
        }
        if (flag > 0) {
            MemoryManager_TimedFree(self);
        }
    }
    return self;
}
