/*
 * 0x801EB708..0x801EB91C: shuffled pseudo random tables. In a link
 * battle (game mode 2) the shared seed byte from the sync slot is used
 * instead so every cabinet draws the same value.
 *
 * Built with deferred inlining, which emits the functions in reverse
 * source order while the table data keeps source order.
 */

typedef struct SyncSlot {
    char pad00[0x1B];
    unsigned char seed;
} SyncSlot;

extern int g_gameMode;
extern int g_pseudoRandomCounter;
extern SyncSlot *SyncSlot_GetRecv(void);

float PseudoRandom_Next(void)
{
    float tbl[16] = {0.625f, 0.25f, 1.0f, 0.0625f, 0.125f, 0.75f, 0.4375f, 0.9375f,
                     0.375f, 0.6875f, 0.1875f, 0.875f, 0.5625f, 0.8125f, 0.3125f, 0.5f};
    if (g_gameMode == 2) {
        return SyncSlot_GetRecv()->seed / 255.0f;
    }
    return tbl[g_pseudoRandomCounter++ % 16];
}

int fn_801EB708(void)
{
    int tbl[16] = {13, 7, 8, 9, 10, 12, 2, 1, 3, 14, 11, 4, 6, 0, 15, 5};
    if (g_gameMode == 2) {
        return SyncSlot_GetRecv()->seed % 16;
    }
    return tbl[g_pseudoRandomCounter++ % 16];
}
