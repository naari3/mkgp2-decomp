/*
 * TCPConn_AllocTxBuffer: scans the 6-slot g_mediaBuffers pool for a slot
 * whose busy flag is clear and pointer is non-NULL, marks it busy, zero-
 * fills the 0xA000-byte buffer, and returns the buffer pointer. Writes
 * 0xA000 to *out_size on success, 0 on exhaustion (when out_size != NULL).
 */

typedef struct MediaBuffer {
    unsigned char busy;
    void *data;
} MediaBuffer;

extern MediaBuffer g_mediaBuffers[6];

extern void *memset(void *dst, int c, unsigned int n);

void *TCPConn_AllocTxBuffer(unsigned int *out_size)
{
    MediaBuffer *buf = g_mediaBuffers;
    int i;

    for (i = 0; i < 6; buf++, i++) {
        if (buf->busy == 0 && buf->data != 0) {
            g_mediaBuffers[i].busy = 1;
            if (out_size) {
                *out_size = 0xA000;
            }
            memset(g_mediaBuffers[i].data, 0, 0xA000);
            return g_mediaBuffers[i].data;
        }
    }
    if (out_size) {
        *out_size = 0;
    }
    return 0;
}
