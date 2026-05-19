__declspec(section ".init") void *memcpy_bytewise(void *dst, const void *src, unsigned long n) {
    unsigned char *__src;
    unsigned char *__dst;
    int i;

    __src = ((unsigned char *)src) - 1;
    __dst = ((unsigned char *)dst) - 1;
    i = n + 1;
    while (--i) {
        *((unsigned char *)++__dst) = *((unsigned char *)++__src);
    }
    return dst;
}
