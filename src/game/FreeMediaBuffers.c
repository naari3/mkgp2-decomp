/*
 * FreeMediaBuffers: walks the 6-entry g_mediaBuffers table (stride 8, flag at
 * +0 / ptr at +4) and frees each slot's pointer via MemoryManager_Free,
 * zeroing both fields.
 */

typedef struct MediaBuffer {
    unsigned char busy;
    void *data;
} MediaBuffer;

extern void MemoryManager_Free(void *p);
extern MediaBuffer g_mediaBuffers[6];

void FreeMediaBuffers(void)
{
    int i;

    for (i = 0; i < 6; i++) {
        MemoryManager_Free(g_mediaBuffers[i].data);
        g_mediaBuffers[i].busy = 0;
        g_mediaBuffers[i].data = 0;
    }
}
