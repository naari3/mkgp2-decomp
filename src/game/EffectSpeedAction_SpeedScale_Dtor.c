extern void MemoryManager_TimedFree(void *p);

extern void *SpeedInitAction_vtable_803FBF48[];
extern void *SpeedInitScale_vtable_803FBF68[];

/* 0x80065028: deleting destructor of the EffectSpeedAction_SpeedScale. */
void **EffectSpeedAction_SpeedScale_Dtor(void **self, short flag)
{
    if (self != 0) {
        *self = SpeedInitScale_vtable_803FBF68;
        if (self != 0) {
            *self = SpeedInitAction_vtable_803FBF48;
        }
        if (flag > 0) {
            MemoryManager_TimedFree(self);
        }
    }
    return self;
}
