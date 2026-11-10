/* Initialize the X/Z bounds of four flash trigger boxes. */
extern const float DNFlash_tail_rodata_803D07BC[24];
extern float lbl_804EE008[12];
extern float lbl_804EE038[12];
extern float fn_80228F80(const float *, const float *);
extern float fn_80228F98(const float *, const float *);
void fn_80228D64(void) {
    lbl_804EE008[0] = fn_80228F98(&DNFlash_tail_rodata_803D07BC[0], &DNFlash_tail_rodata_803D07BC[3]);
    lbl_804EE008[2] = fn_80228F98(&DNFlash_tail_rodata_803D07BC[2], &DNFlash_tail_rodata_803D07BC[5]);
    lbl_804EE008[3] = fn_80228F98(&DNFlash_tail_rodata_803D07BC[6], &DNFlash_tail_rodata_803D07BC[9]);
    lbl_804EE008[5] = fn_80228F98(&DNFlash_tail_rodata_803D07BC[8], &DNFlash_tail_rodata_803D07BC[11]);
    lbl_804EE008[6] = fn_80228F98(&DNFlash_tail_rodata_803D07BC[12], &DNFlash_tail_rodata_803D07BC[15]);
    lbl_804EE008[8] = fn_80228F98(&DNFlash_tail_rodata_803D07BC[14], &DNFlash_tail_rodata_803D07BC[17]);
    lbl_804EE008[9] = fn_80228F98(&DNFlash_tail_rodata_803D07BC[18], &DNFlash_tail_rodata_803D07BC[21]);
    lbl_804EE008[11] = fn_80228F98(&DNFlash_tail_rodata_803D07BC[20], &DNFlash_tail_rodata_803D07BC[23]);
    lbl_804EE038[0] = fn_80228F80(&DNFlash_tail_rodata_803D07BC[0], &DNFlash_tail_rodata_803D07BC[3]);
    lbl_804EE038[2] = fn_80228F80(&DNFlash_tail_rodata_803D07BC[2], &DNFlash_tail_rodata_803D07BC[5]);
    lbl_804EE038[3] = fn_80228F80(&DNFlash_tail_rodata_803D07BC[6], &DNFlash_tail_rodata_803D07BC[9]);
    lbl_804EE038[5] = fn_80228F80(&DNFlash_tail_rodata_803D07BC[8], &DNFlash_tail_rodata_803D07BC[11]);
    lbl_804EE038[6] = fn_80228F80(&DNFlash_tail_rodata_803D07BC[12], &DNFlash_tail_rodata_803D07BC[15]);
    lbl_804EE038[8] = fn_80228F80(&DNFlash_tail_rodata_803D07BC[14], &DNFlash_tail_rodata_803D07BC[17]);
    lbl_804EE038[9] = fn_80228F80(&DNFlash_tail_rodata_803D07BC[18], &DNFlash_tail_rodata_803D07BC[21]);
    lbl_804EE038[11] = fn_80228F80(&DNFlash_tail_rodata_803D07BC[20], &DNFlash_tail_rodata_803D07BC[23]);
}
__declspec(section ".ctors") static void (*const init)(void) = fn_80228D64;
