extern void __construct_array(void *arr, void *ctor, void *dtor, unsigned long size, unsigned long count);
extern void *DbgScene_AnimSlot_Init(void *);
extern unsigned char lbl_80618C68[];

void DbgScene_InitAnimSlotArray(void)
{
    __construct_array(lbl_80618C68, DbgScene_AnimSlot_Init, 0, 0x100, 0x1F4);
}

__declspec(section ".ctors") static void (*const s_DbgScene_InitAnimSlotArray_ctor)(void) = DbgScene_InitAnimSlotArray;
