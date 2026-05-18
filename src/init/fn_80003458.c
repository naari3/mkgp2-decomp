extern void fn_8026D9C4(void *dst, int c, unsigned long n);

__declspec(section ".init") void *memset_returning_dst(void *dst, int c, unsigned long n) {
    fn_8026D9C4(dst, c, n);
    return dst;
}
