/* Send a magnetic-track write command (0x53) to the card reader: a
 * 0x48-byte "00"/"01"-prefixed track image. Returns 1 when the command was
 * queued. */
typedef struct CardRW {
    int busy;                 /* 0x00 */
    unsigned char status[3];  /* 0x04 */
    unsigned char pad07;
    int port;                 /* 0x08 */
    unsigned char header[4];  /* 0x0C */
    unsigned char *rxBuf;     /* 0x10 */
    int rxLen;                /* 0x14 */
    unsigned char pad18[0x4];
    int retries;              /* 0x1C */
} CardRW;

extern unsigned char *FUN_8003b120(unsigned long size);
extern void MemoryManager_Free(void *p);
extern void *memset(void *dst, int c, unsigned long n);
extern void *memcpy(void *dst, const void *src, unsigned long n);
extern unsigned char Sci2Card_BuildPacket(CardRW *self, int port, unsigned char *header, int a, int cmd,
                                          unsigned char *data, int len);

int card_send_track_data(CardRW *self, const void *data, int len, unsigned char track)
{
    unsigned char *pkt;

    if (self->busy != 0) {
        return 0;
    }
    if (len <= 0 || len > 0x45) {
        return 0;
    }
    if (data == 0) {
        return 0;
    }
    pkt = FUN_8003b120(0x48);
    memset(pkt, 0, 0x48);
    pkt[0] = '0';
    if (track == 1) {
        pkt[1] = '0';
    } else {
        pkt[1] = '1';
    }
    pkt[2] = '0';
    memcpy(pkt + 3, data, len);
    if (Sci2Card_BuildPacket(self, self->port, self->header, 2, 0x53, pkt, 0x48) == 1) {
        self->busy = 1;
        self->status[0] = 0;
        self->status[1] = 0;
        self->status[2] = 0;
        memset(self->rxBuf, 0, 0x102);
        self->rxLen = 0;
        self->retries = 8;
        MemoryManager_Free(pkt);
        return 1;
    }
    MemoryManager_Free(pkt);
    return 0;
}
