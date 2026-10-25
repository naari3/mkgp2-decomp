#include <wmem.h>

#include <cstddef>
#include <cstring>

void wmemcpy(wchar_t* dst, const wchar_t* src, size_t n) {
    memcpy(dst, src, n * 2);
}

wchar_t* wmemset(wchar_t* dst, wchar_t val, size_t n) {
    wchar_t* save = dst;

    while (n--) {
        *dst++ = val;
    }
    return save;
}

const wchar_t* wmemchr(const wchar_t* str, wchar_t needle, size_t n) {
    for (; n != 0; n--) {
        if (*str == needle) {
            return str;
        }
        str++;
    }
    return NULL;
}
