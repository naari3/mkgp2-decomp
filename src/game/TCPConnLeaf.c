/* External tables remain owned by their original data units. */
extern const char lbl_803123A0[14];
extern const char* lbl_803FE400[12];
extern int lbl_805AC2C0[4][2];

typedef struct MediaBufferRow {
    unsigned char active;
    unsigned char pad[3];
    void* buffer;
} MediaBufferRow;
extern MediaBufferRow g_mediaBuffers[6];

const char* PcbConnStateIdToName(int state)
{
    if (state < 0 || state >= 11) {
        return lbl_803123A0;
    }
    return lbl_803FE400[state];
}

int TCPConn_GetChannelDest(int channel, int index)
{
    if (channel <= 0 || channel >= 5) {
        return 0;
    }
    return lbl_805AC2C0[channel - 1][index];
}

int TCPConn_FreeTxBuffer(void* buffer)
{
    int i;
    for (i = 0; i < 6; ++i) {
        if (g_mediaBuffers[i].buffer == buffer) {
            g_mediaBuffers[i].active = 0;
            return 1;
        }
    }
    return 0;
}
