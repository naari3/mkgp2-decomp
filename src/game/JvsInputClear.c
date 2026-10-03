extern unsigned short g_jvsPlayerButtons[16];
extern unsigned short g_jvsOperatorBits[16];
extern void *memset(void *dest, int value, unsigned long size);

void JvsInput_ClearBuffers(void) {
    memset(g_jvsPlayerButtons, 0, sizeof(g_jvsPlayerButtons));
    memset(g_jvsOperatorBits, 0, sizeof(g_jvsOperatorBits));
}
