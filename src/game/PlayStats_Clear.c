extern void *memset(void *dst, int value, unsigned int size);

extern unsigned char PlayStats_bss_805AC2E0[];

void PlayStats_Clear(void) {
    memset(PlayStats_bss_805AC2E0, 0, 0x26C);
}
