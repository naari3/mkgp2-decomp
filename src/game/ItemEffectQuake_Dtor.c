extern void MemoryManager_TimedFree(void *p);

extern void *lbl_803F7724[];
extern void *lbl_803F7738[];

/* 0x80054834: deleting destructor of the ItemEffectQuake. */
void **ItemEffectQuake_Dtor(void **self, short flag)
{
    if (self != 0) {
        *self = lbl_803F7724;
        if (self != 0) {
            *self = lbl_803F7738;
        }
        if (flag > 0) {
            MemoryManager_TimedFree(self);
        }
    }
    return self;
}
