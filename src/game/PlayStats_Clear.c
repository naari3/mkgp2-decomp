extern void *memset(void *dst, int value, unsigned int size);

extern unsigned char lbl_805AC2E0[];

void PlayStats_Clear(void) {
    memset(lbl_805AC2E0, 0, 0x26C);
}
