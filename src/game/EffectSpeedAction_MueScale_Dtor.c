extern void MemoryManager_TimedFree(void *p);

extern void *lbl_803FBF34[];
extern void *lbl_803FBF48[];

/* 0x80065084: deleting destructor of the EffectSpeedAction_MueScale. */
void **EffectSpeedAction_MueScale_Dtor(void **self, short flag)
{
    if (self != 0) {
        *self = lbl_803FBF34;
        if (self != 0) {
            *self = lbl_803FBF48;
        }
        if (flag > 0) {
            MemoryManager_TimedFree(self);
        }
    }
    return self;
}
