#ifndef _MSL_COMMON_WMEM_H
#define _MSL_COMMON_WMEM_H

#include <cstddef>

#ifdef __cplusplus
extern "C" {
#endif

void wmemcpy(wchar_t* dst, const wchar_t* src, size_t n);
wchar_t* wmemset(wchar_t* dst, wchar_t val, size_t n);
const wchar_t* wmemchr(const wchar_t* str, wchar_t needle, size_t n);

#ifdef __cplusplus
}
#endif

#endif /* _MSL_COMMON_WMEM_H */
