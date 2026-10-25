/* Static cleanup registration for an empty global object, 0x8002FF48..0x8002FFB8. */

extern unsigned char lbl_806D0FB0[8];
extern unsigned char lbl_805940E0[0xC];

extern void __register_global_object(void *object, void *dtor, void *link);
extern void MemoryManager_TimedFree(void *p);

void *Cleanup_DtorMinimal(void *self, short bDelete);

#pragma exceptions on
void fn_8002FF48(void)
{
    __register_global_object(lbl_806D0FB0, (void *)&Cleanup_DtorMinimal, lbl_805940E0);
}

void *Cleanup_DtorMinimal(void *self, short bDelete)
{
    if ((self != 0) && (bDelete > 0)) {
        MemoryManager_TimedFree(self);
    }
    return self;
}
#pragma exceptions reset

__declspec(section ".ctors") static void (*const s_cleanup_ctor)(void) = fn_8002FF48;
