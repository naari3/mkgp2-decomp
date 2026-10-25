typedef struct DisplayContext {
    void *fifo;
    int f4;
    int f8;
    unsigned char alpha;
    char padD[3];
    float f10;
    char f14[0x74];
    void *buf88;
    int f8C;
} DisplayContext;

extern void *lbl_806CF010;
extern const float lbl_806DA288;
extern void *memset(void *dst, int c, unsigned long n);
extern unsigned short OSGetFontEncode(void);
extern void *OSAllocFromHeap(void *heap, unsigned long size);
extern void OSFreeToHeap(void *heap, void *p);
extern int OSInitFont(void *fifo);

DisplayContext *DisplayContext_Init(DisplayContext *self) {
    self->fifo = 0;
    self->f4 = 0;
    self->f8 = 0;
    self->alpha = 0xFF;
    self->f10 = lbl_806DA288;
    memset(self->f14, 0, 0x74);
    self->f8C = 0;
    if (self->fifo == 0) {
        if (OSGetFontEncode() == 1) {
            self->fifo = OSAllocFromHeap(lbl_806CF010, 0x120F00);
        } else {
            self->fifo = OSAllocFromHeap(lbl_806CF010, 0x20120);
        }
        if (OSInitFont(self->fifo) == 0) {
            OSFreeToHeap(lbl_806CF010, self->fifo);
            self->fifo = 0;
        }
    }
    memset(&self->f4, 0, 0x84);
    self->buf88 = OSAllocFromHeap(lbl_806CF010, 0x4200);
    return self;
}
