extern void MemoryManager_TimedFree(void *p);

extern void *lbl_803F76E4[];
extern void *lbl_803F7738[];

/* 0x800548EC: deleting destructor of the ItemEffectDamp. */
void **ItemEffectDamp_Dtor(void **self, short flag)
{
    if (self != 0) {
        *self = lbl_803F76E4;
        if (self != 0) {
            *self = lbl_803F7738;
        }
        if (flag > 0) {
            MemoryManager_TimedFree(self);
        }
    }
    return self;
}
