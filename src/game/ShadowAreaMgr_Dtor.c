extern void MemoryManager_TimedFree(void *);
extern void fn_80270CF4(void *arr, void *dtor, unsigned long size, unsigned long count);
extern void *dtor_800AA980(void *, short);
extern char lbl_80411E04[];  /* ShadowAreaMgr vtable */
extern char lbl_80411E10[];  /* base vtable */

#pragma exceptions on
void *ShadowAreaMgr_Dtor(void *self, short flag)
{
    if (self != 0) {
        *(char **)self = lbl_80411E04;
        fn_80270CF4((char *)self + 4, dtor_800AA980, 0x1B4, 0x40);
        if (self != 0) {
            *(char **)self = lbl_80411E10;
        }
        if (flag > 0) {
            MemoryManager_TimedFree(self);
        }
    }
    return self;
}
#pragma exceptions reset
