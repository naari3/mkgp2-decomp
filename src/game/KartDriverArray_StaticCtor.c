extern void *RaceContextArray_Init(void *);
extern void *RaceContextArray_Dtor(void *, short);
extern void __register_global_object(void *object, void *dtor, void *regmem);
extern unsigned char lbl_805AC6C0[];
extern unsigned char lbl_805AC6CC[];

void KartDriverArray_StaticCtor(void)
{
    __register_global_object(RaceContextArray_Init(lbl_805AC6CC), RaceContextArray_Dtor, lbl_805AC6C0);
}

__declspec(section ".ctors") static void (*const s_KartDriverArray_StaticCtor_ctor)(void) = KartDriverArray_StaticCtor;
