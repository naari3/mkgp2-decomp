/* Static init for the two StrPcb tick timers at 0x806D1008/0x806D100C. */

extern void dtor_8002F978(void *self, short flag);
extern void __register_global_object(void *object, void *dtor, void *regmem);
extern unsigned int lbl_806D1008;
extern unsigned int lbl_806D100C;
extern unsigned char lbl_80598530[];
extern unsigned char lbl_8059853C[];

void StrPcb_RegisterAtExitCleanup(void)
{
    __register_global_object(&lbl_806D1008, dtor_8002F978, lbl_80598530);
    __register_global_object(&lbl_806D100C, dtor_8002F978, lbl_8059853C);
}

__declspec(section ".ctors") static void (*const s_StrPcb_RegisterAtExitCleanup_ctor)(void) = StrPcb_RegisterAtExitCleanup;
