extern void TRK_fill_mem(void *dst, int c, unsigned long n);

__declspec(section ".init") void *TRK_memset(void *dst, int c, unsigned long n) {
    TRK_fill_mem(dst, c, n);
    return dst;
}
