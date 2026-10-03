/*
 * Complete NonMatching draft for 0x80039780..0x80039A34.
 * Three bounded approaches reached 63.231213%, not byte-identical.
 * CW groups snapshot/edge loads before stores, removes the target reloads,
 * retains an extra player-buffer base web, and saves r21 instead of r22.
 * Observed 16-halfword buffers, not a complete runtime class definition.
 */
enum { CURRENT, PREVIOUS, PRESSED, RELEASED };
enum { PLAYER_STRIDE = 4, ANALOG_BASE = 4, COUNTER_BASE = 12 };

extern unsigned short g_jvsPlayerButtons[16];
extern unsigned short g_jvsOperatorBits[16];
extern int fn_8028B090(void);
extern int fn_8028B0B4(void);
extern int fn_8028AF48(int node, unsigned char *players, unsigned char *width);
extern int fn_8028A808(int node, unsigned char *channels, unsigned char *width);
extern int fn_8028ACEC(int node, unsigned char *counters);
extern int fn_8028AE64(int node, unsigned char player, unsigned char byte);
extern int fn_8028A740(int node, unsigned char channel);
extern int fn_8028AC1C(int node, unsigned char counter);
extern int fn_80293580(void);

int JvsInput_PollAndUpdate(void)
{
    unsigned short *operatorEdges;
    unsigned short operatorBits;
    int node;
    unsigned char playerIndex, analogIndex, counterIndex;
    unsigned char playerCount, buttonWidth, analogCount, counterCount;

    operatorBits = (unsigned short)fn_8028B090();
    operatorBits = (unsigned char)~operatorBits << 8;
    playerIndex = 0;
    analogIndex = 0;
    counterIndex = 0;
    g_jvsPlayerButtons[PREVIOUS] = g_jvsPlayerButtons[CURRENT];
    operatorEdges = g_jvsOperatorBits;
    operatorEdges[PREVIOUS] = operatorEdges[CURRENT];
    g_jvsPlayerButtons[PLAYER_STRIDE + PREVIOUS] = g_jvsPlayerButtons[PLAYER_STRIDE + CURRENT];
    g_jvsPlayerButtons[2 * PLAYER_STRIDE + PREVIOUS] = g_jvsPlayerButtons[2 * PLAYER_STRIDE + CURRENT];
    g_jvsPlayerButtons[3 * PLAYER_STRIDE + PREVIOUS] = g_jvsPlayerButtons[3 * PLAYER_STRIDE + CURRENT];
    node = fn_8028B0B4();
    for (;;) {
        int i;
        fn_8028AF48(node, &playerCount, &buttonWidth);
        if (playerCount > 4) playerCount = 4;
        fn_8028A808(node, &analogCount, 0);
        if (analogCount > 8) analogCount = 8;
        fn_8028ACEC(node, &counterCount);
        if (counterCount > 4) counterCount = 4;
        operatorBits |= fn_8028AE64(node, 0xFF, 0);
        for (i = 0; i < playerCount; ++i) {
            if (playerIndex < 4) {
                unsigned short *base = g_jvsPlayerButtons;
                unsigned int offset = (unsigned char)playerIndex++ * (PLAYER_STRIDE * sizeof(unsigned short));
                *(unsigned short *)((char *)base + offset) = fn_8028AE64(node, (unsigned char)i, 0);
                *(unsigned short *)((char *)base + offset) |= fn_8028AE64(node, (unsigned char)i, 1) << 8;
            }
        }
        for (i = 0; i < analogCount; ++i) {
            if (analogIndex < 8) {
                g_jvsOperatorBits[ANALOG_BASE + analogIndex++] = fn_8028A740(node, (unsigned char)i);
            }
        }
        for (i = 0; i < counterCount; ++i) {
            if (counterIndex < 4) {
                g_jvsOperatorBits[COUNTER_BASE + counterIndex++] = fn_8028AC1C(node, (unsigned char)i);
            }
        }
        if (node <= fn_8028B0B4() - 2) break;
        --node;
    }
    {
        unsigned short previous = operatorEdges[PREVIOUS];
        g_jvsOperatorBits[PRESSED] = operatorBits & ~previous;
        g_jvsPlayerButtons[PRESSED] = g_jvsPlayerButtons[CURRENT] & ~g_jvsPlayerButtons[PREVIOUS];
        g_jvsOperatorBits[CURRENT] = operatorBits;
        g_jvsPlayerButtons[RELEASED] = g_jvsPlayerButtons[PREVIOUS] & ~g_jvsPlayerButtons[CURRENT];
        g_jvsOperatorBits[RELEASED] = previous & ~operatorBits;
        g_jvsPlayerButtons[PLAYER_STRIDE + PRESSED] = g_jvsPlayerButtons[PLAYER_STRIDE + CURRENT] & ~g_jvsPlayerButtons[PLAYER_STRIDE + PREVIOUS];
        g_jvsPlayerButtons[PLAYER_STRIDE + RELEASED] = g_jvsPlayerButtons[PLAYER_STRIDE + PREVIOUS] & ~g_jvsPlayerButtons[PLAYER_STRIDE + CURRENT];
        g_jvsPlayerButtons[2 * PLAYER_STRIDE + PRESSED] = g_jvsPlayerButtons[2 * PLAYER_STRIDE + CURRENT] & ~g_jvsPlayerButtons[2 * PLAYER_STRIDE + PREVIOUS];
        g_jvsPlayerButtons[2 * PLAYER_STRIDE + RELEASED] = g_jvsPlayerButtons[2 * PLAYER_STRIDE + PREVIOUS] & ~g_jvsPlayerButtons[2 * PLAYER_STRIDE + CURRENT];
        g_jvsPlayerButtons[3 * PLAYER_STRIDE + PRESSED] = g_jvsPlayerButtons[3 * PLAYER_STRIDE + CURRENT] & ~g_jvsPlayerButtons[3 * PLAYER_STRIDE + PREVIOUS];
        g_jvsPlayerButtons[3 * PLAYER_STRIDE + RELEASED] = g_jvsPlayerButtons[3 * PLAYER_STRIDE + PREVIOUS] & ~g_jvsPlayerButtons[3 * PLAYER_STRIDE + CURRENT];
    }
    fn_80293580();
    return 1;
}
