/* Inflate a zlib stream (after an 8-byte header) from src into dst, staging
 * input and output through two static 0x6000-byte buffers. */
typedef struct ZStream {
    unsigned char *next_in;      /* 0x00 */
    unsigned int avail_in;       /* 0x04 */
    unsigned int total_in;       /* 0x08 */
    unsigned char *next_out;     /* 0x0C */
    unsigned int avail_out;      /* 0x10 */
    unsigned int total_out;      /* 0x14 */
    char *msg;                   /* 0x18 */
    void *state;                 /* 0x1C */
    void *zalloc;                /* 0x20 */
    void *zfree;                 /* 0x24 */
    void *opaque;                /* 0x28 */
    int data_type;               /* 0x2C */
    unsigned int adler;          /* 0x30 */
    unsigned int reserved;       /* 0x34 */
} ZStream;

extern const char lbl_806D4E88[6];        /* zlib version string */
extern unsigned char lbl_805D3338[0x6000];  /* input staging buffer */
extern unsigned char lbl_805D9338[0x6000];  /* output staging buffer */

extern int fn_802E630C(ZStream *strm, const char *version, int size); /* inflateInit_ */
extern int fn_802E6508(ZStream *strm, int flush);                     /* inflate */
extern int fn_802E7BFC(ZStream *strm);                                /* inflateEnd */
extern void *memset(void *dst, int c, unsigned long n);
extern void *memcpy(void *dst, const void *src, unsigned long n);

void *ZlibInflate_BufferToBuffer(const unsigned char *src, void *dst, int srcLen)
{
    int remain;
    unsigned char *out;
    int err;
    ZStream strm;

    strm.zalloc = 0;
    strm.zfree = 0;
    strm.opaque = 0;
    strm.next_in = 0;
    strm.avail_in = 0;
    if (fn_802E630C(&strm, lbl_806D4E88, sizeof(ZStream)) != 0) {
        return 0;
    }
    strm.avail_out = 0x6000;
    out = dst;
    remain = srcLen - 8;
    strm.next_out = lbl_805D9338;
    src += 8;
    err = 0;
    while (err != 1) {
        if (strm.avail_in == 0) {
            strm.next_in = lbl_805D3338;
            err = 0x6000;
            if (remain < 0x6000) {
                err = remain;
            }
            memset(lbl_805D3338, 0, 0x6000);
            memcpy(lbl_805D3338, src, err);
            strm.avail_in = err;
            remain -= err;
            src += err;
        }
        err = fn_802E6508(&strm, 0);
        if (err == 1) {
            break;
        }
        if (err != 0) {
            return 0;
        }
        if (strm.avail_out == 0) {
            memcpy(out, lbl_805D9338, 0x6000);
            strm.avail_out = 0x6000;
            out += 0x6000;
            strm.next_out = lbl_805D9338;
        }
    }
    err = 0x6000 - strm.avail_out;
    if (err != 0) {
        memcpy(out, lbl_805D9338, err);
    }
    if (fn_802E7BFC(&strm) != 0) {
        return 0;
    }
    return dst;
}
