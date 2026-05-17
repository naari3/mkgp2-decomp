extern void __fill_mem(void *dst, int c, unsigned long n);

__declspec(section ".init") void *memset(void *dst, int c, unsigned long n) {
    __fill_mem(dst, c, n);
    return dst;
}
