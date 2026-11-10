/*
 * NonMatching draft for 0x80039780..0x80039A34 (direct objdiff 93.36994%).
 * Player button accesses are volatile, including the edge helper reads.
 * Reusing operatorBits for the raw input avoids an extra register copy.
 * The final three players share an unrolled edge-update loop.
 * All polling loops match; snapshot scheduling and edge-block registers
 * still differ. The emitted function and target are both 692 bytes.
 */
enum { CURRENT, PREVIOUS, PRESSED, RELEASED };
enum { PLAYER_STRIDE = 4, ANALOG_BASE = 4, COUNTER_BASE = 12 };

extern volatile unsigned short g_jvsPlayerButtons[16];
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

static inline int PressedButtons(volatile unsigned short *p)
{
    int current = p[CURRENT];
    int previous = p[PREVIOUS];
    return current & ~previous;
}

static inline int ReleasedButtons(volatile unsigned short *p)
{
    int previous = p[PREVIOUS];
    int current = p[CURRENT];
    return previous & ~current;
}

int JvsInput_PollAndUpdate(void)
{
    unsigned short *operatorEdges;
    unsigned short operatorBits;
    int node;
    unsigned char playerIndex, analogIndex, counterIndex;
    unsigned char playerCount, buttonWidth, analogCount, counterCount;

    operatorBits = fn_8028B090();
    playerIndex = 0;
    analogIndex = 0;
    counterIndex = 0;
    g_jvsPlayerButtons[PREVIOUS] = g_jvsPlayerButtons[CURRENT];
    operatorEdges = g_jvsOperatorBits;
    operatorEdges[PREVIOUS] = operatorEdges[CURRENT];
    g_jvsPlayerButtons[PLAYER_STRIDE + PREVIOUS] = g_jvsPlayerButtons[PLAYER_STRIDE + CURRENT];
    g_jvsPlayerButtons[2 * PLAYER_STRIDE + PREVIOUS] = g_jvsPlayerButtons[2 * PLAYER_STRIDE + CURRENT];
    g_jvsPlayerButtons[3 * PLAYER_STRIDE + PREVIOUS] = g_jvsPlayerButtons[3 * PLAYER_STRIDE + CURRENT];
    operatorBits = (unsigned char)~operatorBits << 8;
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
                volatile unsigned short *p = &g_jvsPlayerButtons[(unsigned char)playerIndex++ * 4];
                *p = fn_8028AE64(node, (unsigned char)i, 0);
                *p |= fn_8028AE64(node, (unsigned char)i, 1) << 8;
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
        g_jvsPlayerButtons[PRESSED] = PressedButtons(g_jvsPlayerButtons);
        g_jvsOperatorBits[CURRENT] = operatorBits;
        g_jvsPlayerButtons[RELEASED] = ReleasedButtons(g_jvsPlayerButtons);
        g_jvsOperatorBits[RELEASED] = previous & ~operatorBits;
        {
            int player;
            for (player = 1; player < 4; ++player) {
                g_jvsPlayerButtons[player * PLAYER_STRIDE + PRESSED] = PressedButtons(&g_jvsPlayerButtons[player * PLAYER_STRIDE]);
                g_jvsPlayerButtons[player * PLAYER_STRIDE + RELEASED] = ReleasedButtons(&g_jvsPlayerButtons[player * PLAYER_STRIDE]);
            }
        }
    }
    fn_80293580();
    return 1;
}
