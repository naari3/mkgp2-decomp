extern void MemoryManager_TimedFree(void *);
extern char lbl_80419DC8[];  /* TweenInterp vtable */

#pragma exceptions on
void *TweenInterp_VtableTrim(void *self, short flag)
{
    if (self != 0) {
        *(char **)self = lbl_80419DC8;
        if (flag > 0) {
            MemoryManager_TimedFree(self);
        }
    }
    return self;
}
#pragma exceptions reset
