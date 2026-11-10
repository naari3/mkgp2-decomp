#include "game/types/Entry_806792D8.h"

extern Entry_806792D8 lbl_806792D8[];
extern void *memcpy(void *dst, const void *src, unsigned long n);

void fn_801DC740(int idx, const void *src) {
    memcpy(&lbl_806792D8[idx], src, 0xC);
}
