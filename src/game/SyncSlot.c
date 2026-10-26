/*
 * msg_type 4 sync slot helpers.
 *
 * Two 0x1C-byte slots sit back-to-back at lbl_805AC258 (recv) and
 * lbl_805AC258 + 0x1C (host send).
 */

extern unsigned char g_isCommHost;
extern int g_localPcbRole;
extern unsigned char lbl_805AC258[0x38];

extern void memset(void *dst, int value, unsigned long size);

void *SyncSlot_GetHostSend(void) {
    unsigned char *p;
    if (g_isCommHost == 0) return (void *)0;
    p = &lbl_805AC258[0x1c];
    if (g_localPcbRole != 0) return p;
    return (void *)0;
}

void *SyncSlot_GetRecv(void) {
    return lbl_805AC258;
}

void SyncSlot_Reset(void) {
    int i;

    for (i = 0; i < 2; i++) {
        memset(lbl_805AC258 + i * 0x1c, 0, 0x1c);
    }
}
