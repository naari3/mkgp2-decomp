extern void __register_global_object(void *object, void *dtor, void *block);
extern void dtor_8002F978(void *self, int flag);

extern int lbl_806D122C;
extern int lbl_806D1244;
extern unsigned char lbl_805AC550[];
extern unsigned char lbl_805AC5E4[];

/* 0x8009990C: register the destructors of the two receipt line buffers. */
void Sci2Card_RegisterReceiptBuffersCleanup(void)
{
    __register_global_object(&lbl_806D122C, dtor_8002F978, lbl_805AC550);
    __register_global_object(&lbl_806D1244, dtor_8002F978, lbl_805AC5E4);
}

__declspec(section ".ctors") static void (*const s_Sci2Card_RegisterReceiptBuffersCleanup_ctor)(void) = Sci2Card_RegisterReceiptBuffersCleanup;
