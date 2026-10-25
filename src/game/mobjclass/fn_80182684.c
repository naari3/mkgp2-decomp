typedef struct ObjWithBuf {
    unsigned char pad[0x10];
    void *buf;
} ObjWithBuf;

extern void *hsdAllocMemPiece(unsigned int size);
extern void *memcpy(void *dst, const void *src, unsigned long n);

void fn_80182684(ObjWithBuf *obj, void *src) {
    if (obj != 0 && src != 0) {
        if (obj->buf == 0) {
            obj->buf = hsdAllocMemPiece(0xc);
            if (obj->buf == 0) {
                return;
            }
        }
        memcpy(obj->buf, src, 0xc);
    }
}
