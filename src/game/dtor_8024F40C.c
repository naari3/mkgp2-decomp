extern void *memset(void *dst, int c, unsigned int n);

extern unsigned char lbl_80679E00[0x24];

#pragma exceptions on
void dtor_8024F40C(void) {
    memset(lbl_80679E00, 0, 0x24);
}
#pragma exceptions reset
