/* Inflate a zlib stream (after an 8-byte header) from src into dst, staging
 * input and output through two static 0x6000-byte buffers. */
#include "zlib.h"

extern const char lbl_806D4E88[6];        /* zlib version string */
extern unsigned char ZlibInflate_BufferToBuffer_bss_805D3338[0x6000];  /* input staging buffer */
extern unsigned char ZlibInflate_BufferToBuffer_bss_805D9338[0x6000];  /* output staging buffer */

extern void *memset(void *dst, int c, unsigned long n);
extern void *memcpy(void *dst, const void *src, unsigned long n);

void *ZlibInflate_BufferToBuffer(const unsigned char *src, void *dst, int srcLen)
{
    int remain;
    unsigned char *out;
    const unsigned char *input;
    int err;
    z_stream strm;

    strm.zalloc = 0;
    strm.zfree = 0;
    strm.opaque = 0;
    strm.next_in = 0;
    strm.avail_in = 0;
    if (inflateInit_(&strm, lbl_806D4E88, sizeof(z_stream)) != 0) {
        return 0;
    }
    strm.next_out = ZlibInflate_BufferToBuffer_bss_805D9338;
    strm.avail_out = 0x6000;
    out = dst;
    remain = srcLen - 8;
    input = src + 8;
    err = 0;
    while (err != 1) {
        if (strm.avail_in == 0) {
            strm.next_in = ZlibInflate_BufferToBuffer_bss_805D3338;
            err = 0x6000;
            if (remain < 0x6000) {
                err = remain;
            }
            memset(ZlibInflate_BufferToBuffer_bss_805D3338, 0, 0x6000);
            memcpy(ZlibInflate_BufferToBuffer_bss_805D3338, input, err);
            strm.avail_in = err;
            remain -= err;
            input += err;
        }
        err = inflate(&strm, 0);
        if (err == 1) {
            break;
        }
        if (err != 0) {
            return 0;
        }
        if (strm.avail_out == 0) {
            memcpy(out, ZlibInflate_BufferToBuffer_bss_805D9338, 0x6000);
            strm.next_out = ZlibInflate_BufferToBuffer_bss_805D9338;
            strm.avail_out = 0x6000;
            out += 0x6000;
        }
    }
    err = 0x6000 - strm.avail_out;
    if (err != 0) {
        memcpy(out, ZlibInflate_BufferToBuffer_bss_805D9338, err);
    }
    if (inflateEnd(&strm) != 0) {
        return 0;
    }
    return dst;
}
