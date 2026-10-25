extern void MemoryManager_TimedFree(void *p);

extern void *lbl_803F76C4[];
extern void *lbl_803F7738[];

/* 0x80054948: deleting destructor of the ItemEffectSpin. */
void **ItemEffectSpin_Dtor(void **self, short flag)
{
    if (self != 0) {
        *self = lbl_803F76C4;
        if (self != 0) {
            *self = lbl_803F7738;
        }
        if (flag > 0) {
            MemoryManager_TimedFree(self);
        }
    }
    return self;
}
