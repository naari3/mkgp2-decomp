extern void MemoryManager_TimedFree(void *);
extern char lbl_80411DB4[];  /* TitleTracker vtable */
extern char lbl_80411DC0[];  /* base vtable */

#pragma exceptions on
void *TitleTracker_Dtor(void *self, short flag)
{
    if (self != 0) {
        *(char **)self = lbl_80411DB4;
        if (self != 0) {
            *(char **)self = lbl_80411DC0;
        }
        if (flag > 0) {
            MemoryManager_TimedFree(self);
        }
    }
    return self;
}
#pragma exceptions reset
