typedef unsigned char u8;
typedef unsigned long u32;

__declspec(section ".init") void __fill_mem(void *dst, int c, unsigned long n) {
    u8 *cdest;
    u32 *idest;
    u32 i;
    u32 cval;

    cval = (u8)c;
    cdest = (u8 *)dst - 1;

    if (n >= 32) {
        i = ~(u32)cdest & 3;
        if (i != 0) {
            n = n - i;
            do {
                *(++cdest) = (u8)cval;
            } while (--i);
        }
        if (cval != 0) {
            cval = cval << 24 | cval << 16 | cval << 8 | cval;
        }

        idest = (u32 *)(cdest - 3);
        i = n >> 5;
        if (i != 0) {
            do {
                idest[1] = cval;
                idest[2] = cval;
                idest[3] = cval;
                idest[4] = cval;
                idest[5] = cval;
                idest[6] = cval;
                idest[7] = cval;
                *(idest += 8) = cval;
            } while (--i);
        }

        i = (n >> 2) & 7;

        if (i != 0) {
            do {
                *++idest = cval;
            } while (--i);
        }

        cdest = (u8 *)idest + 3;
        n &= 3;
    }
    if (n != 0) {
        do {
            *++cdest = (u8)cval;
        } while (--n);
    }
}
